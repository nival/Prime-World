/*=============================================================================
    Copyright (c) 2009 Daniel James
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#if !defined(BOOST_SPIRIT_QUICKBOOK_QUICKBOOK_HPP)
#define BOOST_SPIRIT_QUICKBOOK_QUICKBOOK_HPP

#include <time.h>
#include <vector>
#include <string>
#include "fwd.hpp"

namespace quickbook
{
    extern tm* current_time; // the current time
    extern tm* current_gm_time; // the current UTC time
    extern bool debug_mode;
    extern std::vector<std::string> include_path;
    extern std::vector<std::string> preset_defines;

    int parse_file(char const* filein_, actions& actor, bool ignore_docinfo = false);
}

#endif
