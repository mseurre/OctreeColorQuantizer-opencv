#!/bin/bash

OPTIONS="--options=.astylerc"
ASTYLE=$(which astyle)

if [ $? -ne 0 ]; then
  echo "[!] astyle not installed. Unable to check source file format policy." >&2
  exit 1
fi

if [ $# -ne 1 ]
then
  echo "Formatting option : "
  echo "  * all : format all source code"
  echo "  * check : check all source code is formatted"
  exit 1;
fi

#formatting things
if [ $1 = "all" ]
then
  echo "Formatting all source code..."
  astyle --options=.astylerc --recursive "*.cpp" "*.hpp" "*.tpp"
  exit $?

elif [ $1 = "check" ]
then
  astyle --options=.astylerc --recursive "*.cpp" "*.hpp" "*.tpp" | grep "^Formatted"
  if [ $? -eq 0 ]; then #is eq 0 ==> grep success ==> file formatted ==> anormal
    exit 1
  fi

else
  echo "Invalid argument : $1"
fi
