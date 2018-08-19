#!/bin/bash

#PrintArray() {
  #for (( i=0; i<${tLen}; i++ ));
  #do
    #echo ${NAMESERVERS[$i]}
  #done
#}

class_name=
declare -a var_names
declare -a var_types

while [[ $# -gt 0 ]]
do
key="$1"

case $key in
    -c|--class_name)
    class_name=$2
    shift; shift ;;

    -v|--var)
    i=${#var_types[@]}
    var_types[i]=$2
    var_names[i]=$3
    shift; shift; shift; ;;

    -*)
    echo "Invalid flag: $1"
    exit ;;
    *)
    break ;;
esac
done

Uppercase() {
  echo $1 | tr '[a-z]' '[A-Z]'
}

Lowercase() {
  echo $1 | tr '[A-Z]' '[a-z]'
}

TitleCaseToUnderscore() {
  echo "$1" | sed -e 's/^\(.\)/\L\1/g' | sed -r 's/([a-z0-9])([A-Z])/\1_\L\2/g'
}

UnderscoreToTitleCase() {
  echo "$1" | sed -r 's/(^|_)([a-z])/\U\2/g'  
}

BuildHeaderFile() {
  export HEADER_FILE_NAME="$class_name_underscore.h"
  export CONSTRUCTOR_SIGNATURE_DEFAULT="$class_name()"
  export CONSTRUCTOR_SIGNATURE_ARGS="$class_name($(for (( i=0; i<$NUM_VARS; i++ )); do [ $i -gt 0 ] && echo -n ", "; echo -n "const ${var_types[$i]}& ${var_names[$i]}"; done))"
  export INIT_SIGNATURE="Init($(for (( i=0; i<$NUM_VARS; i++ )); do [ $i -gt 0 ] && echo -n ", "; echo -n "const ${var_types[$i]}& ${var_names[$i]}"; done))"

  cat <<EOF
#ifndef __$(Uppercase $class_name_underscore)_H__
#define __$(Uppercase $class_name_underscore)_H__

class $class_name {
 public:
   $CONSTRUCTOR_SIGNATURE_DEFAULT;

   $CONSTRUCTOR_SIGNATURE_ARGS;

   void $INIT_SIGNATURE;

 private:
$(for (( i=0; i<$NUM_VARS; i++ )); do echo "  ${var_types[$i]} ${var_names[$i]}_;"; done)
};

#endif
EOF
}

BuildCppFile() {
  CONSTRUCTOR_ARGS_BODY="  Init($(for (( i=0; i<$NUM_VARS; i++ )); do [ $i -gt 0 ] && echo -n ", "; echo -n "${var_names[$i]}"; done));"
  INIT_BODY="$(for (( i=0; i<$NUM_VARS; i++ )); do echo "  ${var_names[$i]}_ = ${var_names[$i]};"; done)"

  # Start of file
  cat <<EOF
#include $HEADER_FILE_NAME

$class_name::$CONSTRUCTOR_SIGNATURE_DEFAULT {
  // TODO
}

$class_name::$CONSTRUCTOR_SIGNATURE_ARGS {
$CONSTRUCTOR_ARGS_BODY
}

void $class_name::$INIT_SIGNATURE {
$INIT_BODY
}
EOF

}


######################################

class_name=$(UnderscoreToTitleCase "$class_name")
class_name_underscore=$(TitleCaseToUnderscore "$class_name")
echo "Class name: $class_name"
NUM_VARS=${#var_types[@]}
for (( i=0; i<${NUM_VARS}; i++ ));
do
  echo "Variable: ${var_types[$i]} : ${var_names[$i]}"
done

echo "HEADER ==============================="
BuildHeaderFile 
echo "CPP ==============================="
BuildCppFile
