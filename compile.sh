#!/bin/bash

mkdir -p build/
cd build/
cmake ..
make
if [[ -f ./libclazzy.a ]]; then
    cp ./libclazzy.a ..
fi

