#ifndef __CRANBERRY_PARSER_H__
#define __CRANBERRY_PARSER_H__

#include "class_def.h"
#include "method.h"
#include "type_hint.h"
#include "type_util.h"
#include "member.h"
#include <vector>
#include <map>
#include <string>
#include <mutex>

class FlexLexer;

namespace cranberry {
    class language;

    class parser {
        public:
            parser(FlexLexer *lexer);
            ~parser();
            
            void set_debug(bool);
            void parse();
            void write() const;

        private:
            bool                                _debug_enabled = false;
            int                                 _lookahead;
            FlexLexer                           *_lex;
            std::vector<class_def>              _classes;
            std::vector<language*>              _langs;
            std::map<std::string, std::string>  _properties;
            std::mutex                          *_io_mutex;
            type_util                           _types;
            
            void next_token(bool exit_on_eof = true);
            std::string token_text() const;

            void parse_statement();
            void parse_property();
            class_def parse_type_definition();
            void parse_definition_list(class_def&);
            void parse_definition(class_def&);
            void parse_action_list(class_def&);
            method parse_action();
            void parse_parameter_list(method&);
            void parse_attribute_list(class_def&);
            member parse_attribute();
            type_hint parse_type_hint();
            std::vector<type_hint> parse_generic_type_list();
            
            void debug(std::string) const;
            void error(std::string) const;
    };
}

#endif
