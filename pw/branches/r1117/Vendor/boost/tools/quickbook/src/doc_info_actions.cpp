/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    Copyright (c) 2005 Thomas Guest
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include <sstream>
#include <boost/bind.hpp>
#include <boost/algorithm/string/join.hpp>
#include "quickbook.hpp"
#include "utils.hpp"
#include "actions_class.hpp"

namespace quickbook
{
    std::string const& docinfo_string::get(unsigned version) const
    {
        return (qbk_version_n < version) ? raw : encoded;
    }

    static void write_document_title(collector& out, quickbook::actions& actions);
    static void write_document_info(collector& out, quickbook::actions& actions);

    void pre(collector& out, quickbook::actions& actions, bool ignore_docinfo)
    {
        // The doc_info in the file has been parsed. Here's what we'll do
        // *before* anything else.

        if (!actions.doc_id_tmp.empty())
            actions.doc_id = actions.doc_id_tmp.get(106);

        if (actions.doc_id.empty())
            actions.doc_id = detail::make_identifier(
                actions.doc_title.raw.begin(),actions.doc_title.raw.end());

        if (actions.doc_dirname.empty() && actions.doc_type == "library") {
            if (!actions.doc_id_tmp.empty()) {
                actions.doc_dirname = actions.doc_id_tmp;
            }
            else {
                actions.doc_dirname.raw = actions.doc_dirname.encoded = actions.doc_id;
            }
        }

        actions.doc_id_tmp.clear();

        if (actions.doc_last_revision.empty())
        {
            // default value for last-revision is now

            char strdate[64];
            strftime(
                strdate, sizeof(strdate),
                (debug_mode ?
                    "DEBUG MODE Date: %Y/%m/%d %H:%M:%S $" :
                    "$" /* prevent CVS substitution */ "Date: %Y/%m/%d %H:%M:%S $"),
                current_gm_time
            );
            actions.doc_last_revision.raw = actions.doc_last_revision.encoded = strdate;
        }

        // if we're ignoring the document info, we're done.
        if (ignore_docinfo)
        {
            return;
        }

        // Quickbook version

        if (qbk_major_version == -1)
        {
            // hard code quickbook version to v1.1
            qbk_major_version = 1;
            qbk_minor_version = 1;
            qbk_version_n = 101;
            detail::outwarn(actions.filename.string(),1)
                << "Warning: Quickbook version undefined. "
                "Version 1.1 is assumed" << std::endl;
        }
        else
        {
            qbk_version_n = ((unsigned) qbk_major_version * 100) +
                (unsigned) qbk_minor_version;
        }
        
        if (qbk_version_n == 106)
        {
            detail::outwarn(actions.filename.string(),1)
                << "Quickbook 1.6 is still under development and is "
                "likely to change in the future." << std::endl;
        }
        else if(qbk_version_n < 100 || qbk_version_n > 106)
        {
            detail::outerr(actions.filename.string(),1)
                << "Unknown version of quickbook: quickbook "
                << qbk_major_version
                << "."
                << qbk_minor_version
                << std::endl;
            ++actions.error_count;
        }

        // Warn about invalid fields

        if (actions.doc_type != "library")
        {
            std::vector<std::string> invalid_attributes;

            if (!actions.doc_purpose.empty())
                invalid_attributes.push_back("purpose");

            if (!actions.doc_categories.empty())
                invalid_attributes.push_back("category");

            if (!actions.doc_dirname.empty())
                invalid_attributes.push_back("dirname");

            if(!invalid_attributes.empty())
            {
                detail::outwarn(actions.filename.string(),1)
                    << (invalid_attributes.size() > 1 ?
                        "Invalid attributes" : "Invalid attribute")
                    << " for '" << actions.doc_type << " document info': "
                    << boost::algorithm::join(invalid_attributes, ", ")
                    << "\n"
                    ;
            }
        }

        // Write out header

        out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            << "<!DOCTYPE "
            << actions.doc_type
            << " PUBLIC \"-//Boost//DTD BoostBook XML V1.0//EN\"\n"
            << "     \"http://www.boost.org/tools/boostbook/dtd/boostbook.dtd\">\n"
            << '<' << actions.doc_type << "\n"
            << "    id=\""
            << actions.doc_id
            << "\"\n";
        
        if(!actions.doc_lang.empty())
        {
            out << "    lang=\""
                << actions.doc_lang.get(106)
                << "\"\n";
        }

        if(actions.doc_type == "library")
        {
            out << "    name=\"" << actions.doc_title.get(106) << "\"\n";
        }

        if(!actions.doc_dirname.empty())
        {
            out << "    dirname=\""
                << actions.doc_dirname.get(106)
                << "\"\n";
        }

        out << "    last-revision=\""
            << actions.doc_last_revision.get(106)
            << "\" \n"
            << "    xmlns:xi=\"http://www.w3.org/2001/XInclude\">\n";
            
        if(actions.doc_type == "library") {
            write_document_info(out, actions);
            write_document_title(out, actions);
        }
        else {
            write_document_title(out, actions);
            write_document_info(out, actions);
        }
    }
    
    void post(collector& out, quickbook::actions& actions, bool ignore_docinfo)
    {
        // if we're ignoring the document info, do nothing.
        if (ignore_docinfo)
        {
            return;
        }

        // We've finished generating our output. Here's what we'll do
        // *after* everything else.
        out << "\n</" << actions.doc_type << ">\n\n";
    }

    void write_document_title(collector& out, quickbook::actions& actions)
    {
        if (!actions.doc_title.empty())
        {
            out << "  <title>"
                << actions.doc_title.get(106);
            if (!actions.doc_version.empty()) {
                out << ' ' << actions.doc_version.get(106);
            }
            out<< "</title>\n\n\n";
        }
    }

    void write_document_info(collector& out, quickbook::actions& actions)
    {
        std::ostringstream tmp;

        if(!actions.doc_authors.empty())
        {
            tmp << "    <authorgroup>\n";
            for(actions::author_list::const_iterator
                it = actions.doc_authors.begin(),
                end = actions.doc_authors.end();
                it != end; ++it)
            {
                tmp << "      <author>\n"
                    << "        <firstname>"
                    << it->first.get(106)
                    << "</firstname>\n"
                    << "        <surname>"
                    << it->second.get(106)
                    << "</surname>\n"
                    << "      </author>\n";
            }
            tmp << "    </authorgroup>\n";
        }

        if (!actions.doc_copyrights.empty())
        {
            for(actions::copyright_list::const_iterator
                it = actions.doc_copyrights.begin(),
                end = actions.doc_copyrights.end();
                it != end; ++it)
            {
                tmp << "\n" << "    <copyright>\n";
        
                for(actions::string_list::const_iterator
                    it2 = it->first.begin(),
                    end = it->first.end();
                    it2 != end; ++it2)
                {
                    tmp << "      <year>" << *it2 << "</year>\n";
                }
        
                tmp << "      <holder>"
                    << it->second.get(106)
                    << "</holder>\n"
                    << "    </copyright>\n"
                    << "\n"
                ;
            }
        }

        if (!actions.doc_license.empty())
        {
            tmp << "    <legalnotice>\n"
                << "      <para>\n"
                << "        " << actions.doc_license.get(103) << "\n"
                << "      </para>\n"
                << "    </legalnotice>\n"
                << "\n"
            ;
        }

        if (!actions.doc_purpose.empty())
        {
            tmp << "    <" << actions.doc_type << "purpose>\n"
                << "      " << actions.doc_purpose.get(103)
                << "    </" << actions.doc_type << "purpose>\n"
                << "\n"
                ;
        }

        if (!actions.doc_categories.empty())
        {
            for(actions::docinfo_list::const_iterator
                it = actions.doc_categories.begin(),
                end = actions.doc_categories.end();
                it != end; ++it)
            {
                tmp << "    <" << actions.doc_type << "category name=\"category:"
                    << it->get(106)
                    << "\"></" << actions.doc_type << "category>\n"
                    << "\n"
                ;
            }
        }

        for (actions::biblioid_list::const_iterator
            it = actions.doc_biblioid_items.begin(),
            end = actions.doc_biblioid_items.end();
            it != end; ++it)
        {
            tmp << "    <biblioid class=\""
                << it->first
                << "\">"
                << it->second.get(103)
                << "</biblioid>"
                << "\n"
                ;
        }

        std::string value = tmp.str();
        if(!value.empty())
        {
            out << "  <" << actions.doc_type << "info>\n"
                << value
                << "  </" << actions.doc_type << "info>\n"
                << "\n"
            ;
        }
    }
}
