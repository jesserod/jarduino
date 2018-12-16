#!/bin/bash

g++.exe \
  -O3 \
  line_drawer_test.cpp\
  point.cpp\
  line_drawer.cpp\
  -o line_drawer_test && ./line_drawer_test

#  line_drawer.cpp\
# grid_printer.cpp\
