#!/bin/bash

if [[ $# -ne 1 ]]; then
    echo "Usage: $0 new_version"
fi

# re-create version.h
version="src/h/version.h"
echo "#ifndef __CLAZZY_VERSION__" > $version
echo "const char * CLAZZY_VERSION = \"$1\";" >> $version
echo "#endif" >> $version

# update PKGBUILD
sed -i "s/pkgver=.*/pkgver=$1/" build/PKGBUILD

echo "Clazzy version set to $1."
