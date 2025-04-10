/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_QUICKBOOK_SYNTAX_HIGHLIGHT_HPP)
#define BOOST_SPIRIT_QUICKBOOK_SYNTAX_HIGHLIGHT_HPP

#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_confix.hpp>
#include <boost/spirit/include/classic_chset.hpp>
#include <boost/spirit/include/classic_symbols.hpp>
#include <boost/spirit/include/classic_loops.hpp>
#include "grammar.hpp"

namespace quickbook
{
    namespace cl = boost::spirit::classic;

    // Grammar for C++ highlighting
    template <
        typename Process
      , typename Space
      , typename Macro
      , typename DoMacro
      , typename PreEscape
      , typename PostEscape
      , typename Unexpected
      , typename Out>
    struct cpp_highlight
    : public cl::grammar<cpp_highlight<Process, Space, Macro, DoMacro, PreEscape, PostEscape, Unexpected, Out> >
    {
        cpp_highlight(Out& out, Macro const& macro, DoMacro do_macro, actions& escape_actions)
        : out(out), macro(macro), do_macro(do_macro), escape_actions(escape_actions) {}

        template <typename Scanner>
        struct definition
        {
            definition(cpp_highlight const& self)
                : g(self.escape_actions.grammar())
            {
                program
                    =
                    *(  (+cl::space_p)  [Space(self.out)]
                    |   macro
                    |   escape
                    |   preprocessor    [Process("preprocessor", self.out)]
                    |   comment         [Process("comment", self.out)]
                    |   keyword         [Process("keyword", self.out)]
                    |   identifier      [Process("identifier", self.out)]
                    |   special         [Process("special", self.out)]
                    |   string_         [Process("string", self.out)]
                    |   char_           [Process("char", self.out)]
                    |   number          [Process("number", self.out)]
                    |   cl::repeat_p(1)[cl::anychar_p]
                                        [Unexpected(self.out)]
                    )
                    ;

                macro =
                    // must not be followed by alpha or underscore
                    cl::eps_p(self.macro                  
                        >> (cl::eps_p - (cl::alpha_p | '_')))
                    >> self.macro                       [self.do_macro]
                    ;

                qbk_phrase =
                   *(   g.common
                    |   (cl::anychar_p - cl::str_p("``"))
                                        [self.escape_actions.plain_char]
                    )
                    ;

                escape =
                    cl::str_p("``")     [PreEscape(self.escape_actions, save)]
                    >>
                    (
                        (
                            (
                                (+(cl::anychar_p - "``") >> cl::eps_p("``"))
                                & qbk_phrase
                            )
                            >>  cl::str_p("``")
                        )
                        |
                        (
                            cl::eps_p   [self.escape_actions.error]
                            >> *cl::anychar_p
                        )
                    )                   [PostEscape(self.out, self.escape_actions, save)]
                    ;

                preprocessor
                    =   '#' >> *cl::space_p >> ((cl::alpha_p | '_') >> *(cl::alnum_p | '_'))
                    ;

                comment
                    =   cl::comment_p("//") | cl::comment_p("/*", "*/")
                    ;

                keyword
                    =   keyword_ >> (cl::eps_p - (cl::alnum_p | '_'))
                    ;   // make sure we recognize whole words only

                keyword_
                    =   "and_eq", "and", "asm", "auto", "bitand", "bitor",
                        "bool", "break", "case", "catch", "char", "class",
                        "compl", "const_cast", "const", "continue", "default",
                        "delete", "do", "double", "dynamic_cast",  "else",
                        "enum", "explicit", "export", "extern", "false",
                        "float", "for", "friend", "goto", "if", "inline",
                        "int", "long", "mutable", "namespace", "new", "not_eq",
                        "not", "operator", "or_eq", "or", "private",
                        "protected", "public", "register", "reinterpret_cast",
                        "return", "short", "signed", "sizeof", "static",
                        "static_cast", "struct", "switch", "template", "this",
                        "throw", "true", "try", "typedef", "typeid",
                        "typename", "union", "unsigned", "using", "virtual",
                        "void", "volatile", "wchar_t", "while", "xor_eq", "xor"
                    ;

                special
                    =   +cl::chset_p("~!%^&*()+={[}]:;,<.>?/|\\-")
                    ;

                string_char = ('\\' >> cl::anychar_p) | (cl::anychar_p - '\\');

                string_
                    =   !cl::as_lower_d['l'] >> cl::confix_p('"', *string_char, '"')
                    ;

                char_
                    =   !cl::as_lower_d['l'] >> cl::confix_p('\'', *string_char, '\'')
                    ;

                number
                    =   (
                            cl::as_lower_d["0x"] >> cl::hex_p
                        |   '0' >> cl::oct_p
                        |   cl::real_p
                        )
                        >>  *cl::as_lower_d[cl::chset_p("ldfu")]
                    ;

                identifier
                    =   (cl::alpha_p | '_') >> *(cl::alnum_p | '_')
                    ;
            }

            cl::rule<Scanner>
                            program, macro, preprocessor, comment, special, string_, 
                            char_, number, identifier, keyword, qbk_phrase, escape,
                            string_char;

            cl::symbols<> keyword_;
            quickbook_grammar& g;
            std::string save;

            cl::rule<Scanner> const&
            start() const { return program; }
        };

        Out& out;
        Macro const& macro;
        DoMacro do_macro;
        actions& escape_actions;
    };

    // Grammar for Python highlighting
    // See also: The Python Reference Manual
    // http://docs.python.org/ref/ref.html
    template <
        typename Process
      , typename Space
      , typename Macro
      , typename DoMacro
      , typename PreEscape
      , typename PostEscape
      , typename Unexpected
      , typename Out>
    struct python_highlight
    : public cl::grammar<python_highlight<Process, Space, Macro, DoMacro, PreEscape, PostEscape, Unexpected, Out> >
    {
        python_highlight(Out& out, Macro const& macro, DoMacro do_macro, actions& escape_actions)
        : out(out), macro(macro), do_macro(do_macro), escape_actions(escape_actions) {}

        template <typename Scanner>
        struct definition
        {
            definition(python_highlight const& self)
                : g(self.escape_actions.grammar())
            {
                program
                    =
                    *(  (+cl::space_p)  [Space(self.out)]
                    |   macro
                    |   escape          
                    |   comment         [Process("comment", self.out)]
                    |   keyword         [Process("keyword", self.out)]
                    |   identifier      [Process("identifier", self.out)]
                    |   special         [Process("special", self.out)]
                    |   string_         [Process("string", self.out)]
                    |   number          [Process("number", self.out)]
                    |   cl::repeat_p(1)[cl::anychar_p]
                                        [Unexpected(self.out)]
                    )
                    ;

                macro = 
                    // must not be followed by alpha or underscore
                    cl::eps_p(self.macro
                        >> (cl::eps_p - (cl::alpha_p | '_')))
                    >> self.macro                       [self.do_macro]
                    ;

                qbk_phrase =
                   *(   g.common
                    |   (cl::anychar_p - cl::str_p("``"))
                                        [self.escape_actions.plain_char]
                    )
                    ;

                escape =
                    cl::str_p("``")     [PreEscape(self.escape_actions, save)]
                    >>
                    (
                        (
                            (
                                (+(cl::anychar_p - "``") >> cl::eps_p("``"))
                                & qbk_phrase
                            )
                            >>  cl::str_p("``")
                        )
                        |
                        (
                            cl::eps_p   [self.escape_actions.error]
                            >> *cl::anychar_p
                        )
                    )                   [PostEscape(self.out, self.escape_actions, save)]
                    ;

                comment
                    =   cl::comment_p("#")
                    ;

                keyword
                    =   keyword_ >> (cl::eps_p - (cl::alnum_p | '_'))
                    ;   // make sure we recognize whole words only

                keyword_
                    =
                    "and",       "del",       "for",       "is",        "raise",    
                    "assert",    "elif",      "from",      "lambda",    "return",   
                    "break",     "else",      "global",    "not",       "try",  
                    "class",     "except",    "if",        "or",        "while",    
                    "continue",  "exec",      "import",    "pass",      "yield",   
                    "def",       "finally",   "in",        "print",

                    // Technically "as" and "None" are not yet keywords (at Python
                    // 2.4). They are destined to become keywords, and we treat them 
                    // as such for syntax highlighting purposes.
                    
                    "as", "None"
                    ;

                special
                    =   +cl::chset_p("~!%^&*()+={[}]:;,<.>/|\\-")
                    ;

                string_prefix
                    =    cl::as_lower_d[cl::str_p("u") >> ! cl::str_p("r")]
                    ;
                
                string_
                    =   ! string_prefix >> (long_string | short_string)
                    ;

                string_char = ('\\' >> cl::anychar_p) | (cl::anychar_p - '\\');
            
                short_string
                    =   cl::confix_p('\'', * string_char, '\'') |
                        cl::confix_p('"', * string_char, '"')
                    ;
            
                long_string
                    // Note: the "cl::str_p" on the next two lines work around
                    // an INTERNAL COMPILER ERROR when using VC7.1
                    =   cl::confix_p(cl::str_p("'''"), * string_char, "'''") |
                        cl::confix_p(cl::str_p("\"\"\""), * string_char, "\"\"\"")
                    ;
                
                number
                    =   (
                            cl::as_lower_d["0x"] >> cl::hex_p
                        |   '0' >> cl::oct_p
                        |   cl::real_p
                        )
                        >>  *cl::as_lower_d[cl::chset_p("lj")]
                    ;

                identifier
                    =   (cl::alpha_p | '_') >> *(cl::alnum_p | '_')
                    ;
            }

            cl::rule<Scanner>
                            program, macro, comment, special, string_, string_prefix, 
                            short_string, long_string, number, identifier, keyword, 
                            qbk_phrase, escape, string_char;

            cl::symbols<> keyword_;
            quickbook_grammar& g;
            std::string save;

            cl::rule<Scanner> const&
            start() const { return program; }
        };

        Out& out;
        Macro const& macro;
        DoMacro do_macro;
        actions& escape_actions;
    };

    // Grammar for plain text (no actual highlighting)
    template <
        typename CharProcess
      , typename Macro
      , typename DoMacro
      , typename PreEscape
      , typename PostEscape
      , typename Out>
    struct teletype_highlight
    : public cl::grammar<teletype_highlight<CharProcess, Macro, DoMacro, PreEscape, PostEscape, Out> >
    {
        teletype_highlight(Out& out, Macro const& macro, DoMacro do_macro, actions& escape_actions)
        : out(out), macro(macro), do_macro(do_macro), escape_actions(escape_actions) {}

        template <typename Scanner>
        struct definition
        {
            definition(teletype_highlight const& self)
                : g(self.escape_actions.grammar())
            {
                program
                    =
                    *(  macro
                    |   escape          
                    |   cl::repeat_p(1)[cl::anychar_p]  [CharProcess(self.out, self.escape_actions)]
                    )
                    ;

                macro =
                    // must not be followed by alpha or underscore
                    cl::eps_p(self.macro                    
                        >> (cl::eps_p - (cl::alpha_p | '_')))
                    >> self.macro       [self.do_macro]
                    ;

                qbk_phrase =
                   *(   g.common
                    |   (cl::anychar_p - cl::str_p("``"))
                                        [self.escape_actions.plain_char]
                    )
                    ;

                escape =
                    cl::str_p("``")     [PreEscape(self.escape_actions, save)]
                    >>
                    (
                        (
                            (
                                (+(cl::anychar_p - "``") >> cl::eps_p("``"))
                                & qbk_phrase
                            )
                            >>  cl::str_p("``")
                        )
                        |
                        (
                            cl::eps_p   [self.escape_actions.error]
                            >> *cl::anychar_p
                        )
                    )                   [PostEscape(self.out, self.escape_actions, save)]
                    ;
            }

            cl::rule<Scanner> program, macro, qbk_phrase, escape;

            quickbook_grammar& g;
            std::string save;

            cl::rule<Scanner> const&
            start() const { return program; }
        };

        Out& out;
        Macro const& macro;
        DoMacro do_macro;
        actions& escape_actions;
    };

}

#endif // BOOST_SPIRIT_QUICKBOOK_SYNTAX_HIGHLIGHT_HPP
