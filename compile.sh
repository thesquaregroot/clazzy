#!/bin/bash

mkdir -p build/
cd build/
cmake ..
make
if [[ -f ./clazzy ]]; then
    cp ./clazzy ../clazzy
fi

