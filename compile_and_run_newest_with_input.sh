#!/bin/bash

CPP=`ls -t *.cpp | head -1`

# Try compilation, with debug info enabled
g++ -g ./$CPP
if [ "$?" != "0" ]; then
    echo Complilation unsuccessful!
    exit 1
fi

# Running a.out with input
./a.out < input
