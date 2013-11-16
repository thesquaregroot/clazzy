#!/bin/bash

if [[ $# -ne 1 ]]; then
    echo "Usage: $0 new_version"
fi

version="src/h/version.h"
echo "#ifndef __CLAZZY_VERSION__" > $version
echo "const char * CLAZZY_VERSION = \"$1\";" >> $version
echo "#endif" >> $version

echo "Clazzy version set to $1."
