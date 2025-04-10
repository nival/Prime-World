/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    Copyright (c) 2010 Daniel James
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_QUICKBOOK_GRAMMARS_IMPL_HPP)
#define BOOST_SPIRIT_QUICKBOOK_GRAMMARS_IMPL_HPP

#include "grammar.hpp"
#include "rule_store.hpp"
#include <boost/spirit/include/classic_symbols.hpp>

namespace quickbook
{
    namespace cl = boost::spirit::classic;

    struct element_info
    {
        enum context {
            in_block = 1,
            in_phrase = 2,
            in_conditional = 4,
        };

        enum type_enum {
            block = 1,
            phrase = 2,
            conditional_or_block = 5
        };

        element_info(type_enum t, cl::rule<scanner>* r)
            : type(t), rule(r) {}

        type_enum type;
        cl::rule<scanner>* rule;
    };

    struct quickbook_grammar::impl
    {
        quickbook::actions& actions;
        rule_store store_;

        // Main Grammar
        cl::rule<scanner> block_start;
        cl::rule<scanner> block_skip_initial_spaces;
        cl::rule<scanner> common;
        cl::rule<scanner> simple_phrase;
        cl::rule<scanner> phrase;
        cl::rule<scanner> extended_phrase;
        cl::rule<scanner> inside_paragraph;
        cl::rule<scanner> command_line;

        // Miscellaneous stuff
        cl::rule<scanner> hard_space;
        cl::rule<scanner> space;
        cl::rule<scanner> blank;
        cl::rule<scanner> eol;
        cl::rule<scanner> phrase_end;
        cl::rule<scanner> comment;
        cl::rule<scanner> macro_identifier;

        // Element Symbols       
        cl::symbols<element_info> elements;
        
        // Doc Info
        cl::rule<scanner> doc_info_details;
        
        impl(quickbook::actions&);

    private:

        void init_main();
        void init_block_elements();
        void init_phrase_elements();
        void init_doc_info();
    };
}

#endif // BOOST_SPIRIT_QUICKBOOK_GRAMMARS_HPP
