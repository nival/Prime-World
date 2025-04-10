/*=============================================================================
    Copyright (c) 2009 Daniel James

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include <boost/program_options.hpp>
#include "input_path.hpp"

#if !(defined(__cygwin__) || defined(__CYGWIN__))

// Everything but cygwin

namespace quickbook { namespace detail
{
    void validate(boost::any& v,
            const std::vector<std::string>& values,
            input_path*, int)
    {
        std::string path
            = boost::program_options::validators::get_single_string(values);

        v = input_path(path);
    }
}}

#else

// Cygwin 1.7.x
    
#include <boost/filesystem/v3/config.hpp>
#include <boost/scoped_array.hpp>
#include <boost/program_options/errors.hpp>
#include <windows.h>
#include <sys/cygwin.h>

namespace quickbook { namespace detail
{
    void validate(boost::any& v,
            const std::vector<std::string>& values,
            input_path*, int)
    {
        std::string path
            = boost::program_options::validators::get_single_string(values);

#if defined(BOOST_WINDOWS_PATH)
        cygwin_conv_path_t flags = CCP_POSIX_TO_WIN_A | CCP_RELATIVE;
#elif defined(BOOST_POSIX_PATH)
        cygwin_conv_path_t flags = CCP_WIN_A_TO_POSIX | CCP_RELATIVE;
#else
#    error "Boost filesystem path type doesn't seem to be set."
#endif

        ssize_t size = cygwin_conv_path(flags, path.c_str(), NULL, 0);
        
        if (size < 0) {
            throw boost::program_options::validation_error(
                boost::program_options::validation_error::invalid_option_value);
        }

        boost::scoped_array<char> result(new char[size]);

        if(cygwin_conv_path(flags, path.c_str(), result.get(), size)) {
            throw boost::program_options::validation_error(
                boost::program_options::validation_error::invalid_option_value);
        }

        v = input_path(result.get());
    }
}}

#endif
