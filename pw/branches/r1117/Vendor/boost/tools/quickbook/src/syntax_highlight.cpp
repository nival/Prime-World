/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include "syntax_highlight.hpp"
#include "actions_class.hpp"

namespace quickbook
{
    typedef cpp_highlight<
        span
      , space
      , string_symbols
      , do_macro_action
      , pre_escape_back
      , post_escape_back
      , unexpected_char
      , collector>
    cpp_p_type;

    typedef python_highlight<
        span
      , space
      , string_symbols
      , do_macro_action
      , pre_escape_back
      , post_escape_back
      , unexpected_char
      , collector>
    python_p_type;
    
    typedef teletype_highlight<
        plain_char_action
      , string_symbols
      , do_macro_action
      , pre_escape_back
      , post_escape_back
      , collector>
    teletype_p_type;
    
    std::string syntax_highlight(
        iterator first, iterator last,
        actions& escape_actions,
        std::string const& source_mode)
    {
        quickbook::collector temp;

        // print the code with syntax coloring
        if (source_mode == "c++")
        {
            cpp_p_type cpp_p(temp, escape_actions.macro, do_macro_action(temp, escape_actions), escape_actions);
            boost::spirit::classic::parse(first, last, cpp_p);
        }
        else if (source_mode == "python")
        {
            python_p_type python_p(temp, escape_actions.macro, do_macro_action(temp, escape_actions), escape_actions);
            boost::spirit::classic::parse(first, last, python_p);
        }
        else if (source_mode == "teletype")
        {
            teletype_p_type teletype_p(temp, escape_actions.macro, do_macro_action(temp, escape_actions), escape_actions);
            boost::spirit::classic::parse(first, last, teletype_p);
        }
        else
        {
            BOOST_ASSERT(0);
        }

        std::string str;
        temp.swap(str);
        
        return str;
    }
}
