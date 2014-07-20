
#include "string_functions.h"
#include <cctype>
using namespace std;

string clazzy::to_lower_case(const string &text) {
    string output;
    if (isupper(text[0])) {
        output = tolower(text[0]);
    } else {
        output = text[0];
    }
    // turn subsequent caps into underscores and lower case chars
    for (unsigned int i=1; i<text.size(); i++) {
        if (isupper(text[i])) {
            output += "_" + tolower(text[i]);
        } else {
            output += text[i];
        }
    }
    return output;
}

string clazzy::to_camel_case(const string &text) {
    string output;
    output += text[0];
    // turn subsequent underscores followed by chars to just the upper case
    for (unsigned int i=1; i<text.size(); i++) {
        if (text[i] == '_' && i != text.size()-1 && isalpha(text[i+1])) {
            output += toupper(text[i+1]);
            i++;
        } else {
            output += text[i];
        }
    }
    return output;
}

string clazzy::to_full_camel_case(const string &text) {
    string output = to_camel_case(text);
    // convert first char as well
    if (islower(text[0])) {
        output[0] = toupper(text[0]);
    }
    return output;
}

