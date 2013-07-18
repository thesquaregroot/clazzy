#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 langauge_name code_name"
    exit 1
fi

language=$1
code_name=$2

class_name="lang_$code_name"

echo "Creating src/${class_name}.cpp..."

echo "Creating src/h/${class_name}.h..."


echo "Updating language includes..."
cat ./src/h/language_includes.h | sed "s/\(\/\/ ### Language Includes ###\)/#include \"$class_name.h\"\n\1/"
echo "Updating language factory..."
cat ./src/language_factory.cpp | sed "s/\(\/\/ ### Language Instantiations ###\)/} else if (name == \"$language\") {\n                return new $class_name(io_mutex, debug_enabled);\n        \1/"

