#!/bin/bash

class_name=
declare -a var_names
declare -a var_types
declare -a includes

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

    #-i|--include)
    #i=${#includes[@]}
    #includes[i]=$2
    #shift; shift ;;

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

ToUnderscored() {
  echo "$1" | sed -e 's/^\(.\)/\L\1/g' | sed -r 's/([a-z0-9])([A-Z])/\1_\L\2/g'
}

ToTitleCase() {
  echo "$1" | sed -r 's/(^|_)([a-z])/\U\2/g'  
}

# Args: $1=i, $2="cpp" or empty
Setter() {
  i=$1
  name=${var_names[$i]}
  T=${var_types[$i]}
  if [[ $2 == "cpp" ]]; then
    prefix="void $class_name::"
    body=" {\n  ${name}_ = $name;\n}"
  else
    prefix="  void "
    body=";"
  fi
  printf "${prefix}Set$(ToTitleCase $name)(const $T& $name)$body\n\n"
}

# Args: $1=i, $2="cpp" or empty
Getter() {
  i=$1
  name=${var_names[$i]}
  T=${var_types[$i]}
  if [[ $2 == "cpp" ]]; then
    prefix="$T $class_name::"
    body=" {\n  return ${name}_;\n}"
  else
    prefix="  $T "
    body=";"
  fi
  printf "${prefix}$(ToTitleCase $name)()$body\n\n"
}



BuildHeaderFile() {
  export CONSTRUCTOR_SIGNATURE_DEFAULT="$class_name()"
  export CONSTRUCTOR_SIGNATURE_ARGS="$class_name($(for (( i=0; i<$NUM_VARS; i++ )); do [ $i -gt 0 ] && echo -n ", "; echo -n "const ${var_types[$i]}& ${var_names[$i]}"; done))"
  export INIT_SIGNATURE="Init($(for (( i=0; i<$NUM_VARS; i++ )); do [ $i -gt 0 ] && echo -n ", "; echo -n "const ${var_types[$i]}& ${var_names[$i]}"; done))"

  cat <<EOF
#ifndef __$(Uppercase $class_name_underscore)_H__
#define __$(Uppercase $class_name_underscore)_H__

#include <string>

class $class_name {
 public:
  $CONSTRUCTOR_SIGNATURE_DEFAULT;

  $CONSTRUCTOR_SIGNATURE_ARGS;

  void $INIT_SIGNATURE;

$(for (( i=0; i<$NUM_VARS; i++ )); do Getter $i; Setter $i; done)

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
#include "$HEADER_SRC_NAME"

$class_name::$CONSTRUCTOR_SIGNATURE_DEFAULT {
  // TODO
}

$class_name::$CONSTRUCTOR_SIGNATURE_ARGS {
$CONSTRUCTOR_ARGS_BODY
}

void $class_name::$INIT_SIGNATURE {
$INIT_BODY
}

$(for (( i=0; i<$NUM_VARS; i++ )); do Getter $i cpp; Setter $i cpp; done)
EOF
}


BuildTestFile() {
  cat <<EOF
#include <iostream>

#include "$HEADER_SRC_NAME"
#include "test_helpers.h"

void TestExample1() {
  EXPECT_FLOAT_EQ(1.0, 1.00000001);
}

void TestExample2() {
  EXPECT_GT(2.0, 1);
}

int main ()
{
  // using namespace jarduino;
  TEST(TestExample1);
  TEST(TestExample2);

  std::cout << "Tests passed!" << std::endl;
  return 0;
}

EOF
}

BuildRunTestScript() {
  cat <<EOF
#!/bin/bash

g++.exe \\
  $CPP_SRC_NAME\\
  $TEST_SRC_NAME\\
  -o $TEST_BINARY_NAME && ./$TEST_BINARY_NAME
EOF
}


######################################

class_name=$(ToTitleCase "$class_name")
class_name_underscore=$(ToUnderscored "$class_name")
echo "Class name: $class_name"
NUM_VARS=${#var_types[@]}
for (( i=0; i<${NUM_VARS}; i++ ));
do
  echo "Variable: ${var_types[$i]} : ${var_names[$i]}"
done

HEADER_SRC_NAME="$class_name_underscore.h"
CPP_SRC_NAME="$class_name_underscore.cpp"
TEST_SRC_NAME="${class_name_underscore}_test.cpp"
TEST_BINARY_NAME="${class_name_underscore}_test"
RUN_TEST_SCRIPT="run_${class_name_underscore}_test.sh"
echo "HEADER ==============================="
BuildHeaderFile 
BuildHeaderFile > $HEADER_SRC_NAME
echo
echo "CPP ==============================="
BuildCppFile 
BuildCppFile > $CPP_SRC_NAME
echo "TEST ==============================="
echo
BuildTestFile
BuildTestFile > $TEST_SRC_NAME
echo "RUN_SCRIPT ==============================="
echo
BuildRunTestScript
BuildRunTestScript > $RUN_TEST_SCRIPT
chmod +x $RUN_TEST_SCRIPT
