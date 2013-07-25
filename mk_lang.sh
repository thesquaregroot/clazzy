#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 langauge_name code_name"
    exit 1
fi

language=$1
code_name=$2

class_name="lang_$code_name"
upper_case_lang_name=`echo $code_name | tr '[a-z]' '[A-Z]'`

header_file="src/h/${class_name}.h"
code_file="src/${class_name}.cpp"

### H ###
echo "Creating src/h/${class_name}.h..."

echo "#ifndef __CRANBERRY_LANG_${upper_case_lang_name}_H__" > $header_file
echo "#define __CRANBERRY_LANG_${upper_case_lang_name}_H__" >> $header_file
echo >> $header_file
echo "#include \"language.h\"" >> $header_file
echo "#include <vector>" >> $header_file
echo "#include <map>" >> $header_file
echo "#include <string>" >> $header_file
echo >> $header_file
echo "namespace cranberry {" >> $header_file
echo "    class ${class_name} : public language {" >> $header_file
echo "        public:" >> $header_file
echo "            ${class_name}(std::mutex *io, bool debug) : language(io, debug) { }" >> $header_file
echo >> $header_file
echo "            std::string get_name() const;" >> $header_file
echo "            void create(" >> $header_file
echo "                        const std::vector<class_def>&," >> $header_file
echo "                        const std::map<std::string,std::string>&" >> $header_file
echo "                    ) const;" >> $header_file
echo "    };" >> $header_file
echo "}" >> $header_file
echo >> $header_file
echo "#endif" >> $header_file

###  CPP  ###
echo "Creating src/${class_name}.cpp..."

echo > $code_file
echo "#include \"h/${class_name}.h\"" >> $code_file
echo "#include \"h/class_def.h\"" >> $code_file
echo "#include \"h/method.h\"" >> $code_file
echo "#include \"h/member.h\"" >> $code_file
echo "#include <vector>" >> $code_file
echo "#include <map>" >> $code_file
echo "#include <string>" >> $code_file
echo "#include <mutex>" >> $code_file
echo "using namespace cranberry;" >> $code_file
echo "using namespace std;" >> $code_file
echo >> $code_file
echo "string ${class_name}::get_name() const" >> $code_file
echo "{" >> $code_file
echo "        return \"${language}\";" >> $code_file
echo "}" >> $code_file
echo >> $code_file
echo "void ${class_name}::create(" >> $code_file
echo "                        const vector<class_def> &classes," >> $code_file
echo "                        const map<string,string> &properties" >> $code_file
echo "        ) const" >> $code_file
echo "{" >> $code_file
echo "        // TODO: Implement code generation" >> $code_file
echo "}" >> $code_file


### OTHER ###
echo "Updating language factory..."

language_factory_file="./src/language_factory.cpp"

sed -i.bak "s/\(\/\/ ### Language Includes ###\)/#include \"h/$class_name.h\"\n\1/" $language_factory_file
rm ${language_factory_file}.bak
sed -i.bak "s/\(\/\/ ### Language Instantiations ###\)/} else if (name == \"$language\") {\n                return new $class_name(io_mutex, debug_enabled);\n        \1/" $language_factory_file
rm ${langauge_factory_file}.bak

echo "Complete."
