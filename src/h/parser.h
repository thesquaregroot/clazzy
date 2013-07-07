#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>

class FlexLexer;
class class_def;
class language;

class parser {
    private:
        bool                    debug_enabled = false;
        FlexLexer               *lex;
        std::vector<class_def>  classes;
        std::vector<language*>  langs;

        void parse_statement(int);
        void parse_property(int);
        class_def parse_type_definition(int) const;
        void parse_definition_section(int, class_def&) const;
        void parse_definition_list(int, class_def&) const;
        void parse_definition(int, class_def&) const;
        void parse_action_list(int, class_def&) const;
        void parse_action(int, class_def&) const;
        void parse_attribute_list(int, class_def&) const;
        void parse_parameters(int, class_def&) const;
        void parse_parameter_list(int, class_def&) const;
        
        void debug(std::string) const;
        void error(std::string) const;

    public:
        parser(FlexLexer *lexer);
        ~parser();
        
        void set_debug(bool);
        void parse();
        void write() const;
};

#endif
