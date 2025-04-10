/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include "grammar_impl.hpp"
#include "actions_class.hpp"
#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_actor.hpp>
#include <boost/spirit/include/classic_loops.hpp>
#include <boost/spirit/include/classic_symbols.hpp>
#include <boost/spirit/include/classic_chset.hpp>

namespace quickbook
{
    namespace cl = boost::spirit::classic;

    struct doc_info_grammar_local
    {
        cl::rule<scanner>
                        doc_title, doc_version, doc_id, doc_dirname,
                        doc_copyright, doc_purpose, doc_category, doc_authors,
                        doc_author, doc_license,
                        doc_last_revision, doc_source_mode, doc_biblioid, doc_lang,
                        quickbook_version, char_;
        cl::symbols<> doc_types;
    };

    void quickbook_grammar::impl::init_doc_info()
    {
        doc_info_grammar_local& local = store_.create();

        typedef cl::uint_parser<int, 10, 1, 2>  uint2_t;

        local.doc_types =
            "book", "article", "library", "chapter", "part"
          , "appendix", "preface", "qandadiv", "qandaset"
          , "reference", "set"
        ;
        
        doc_info_details =
            space
            >> '[' >> space
            >> (local.doc_types >> cl::eps_p)
                                            [cl::assign_a(actions.doc_type)]
            >> hard_space
            >>  (  *(~cl::eps_p(cl::ch_p('[') | ']' | cl::eol_p) >> local.char_)
                )                           [actions.extract_doc_title]
            >>  !(
                    space >> '[' >>
                        local.quickbook_version
                    >> space >> ']'
                )
            >>
                *(
                    space >> '[' >>
                    (
                      local.doc_version
                    | local.doc_id
                    | local.doc_dirname
                    | local.doc_copyright   [cl::push_back_a(actions.doc_copyrights, actions.copyright)]
                    | local.doc_purpose
                    | local.doc_category
                    | local.doc_authors
                    | local.doc_license
                    | local.doc_last_revision
                    | local.doc_source_mode
                    | local.doc_biblioid
                    | local.doc_lang
                    )
                    >> space >> ']' >> +cl::eol_p
                )
            >> space >> ']' >> +cl::eol_p
            ;

        local.quickbook_version =
                "quickbook" >> hard_space
            >>  (   cl::uint_p              [assign_qbk_version(qbk_major_version)]
                    >> '.' 
                    >>  uint2_t()           [assign_qbk_version(qbk_minor_version)]
                )
            ;

        local.doc_version =
                "version" >> hard_space
            >> (*(~cl::eps_p(']') >> local.char_))
                                            [actions.extract_doc_version]
            ;

        // TODO: Restrictions on doc_id?
        local.doc_id =
                "id" >> hard_space
            >> (*(~cl::eps_p(']') >> local.char_))
                                            [actions.extract_doc_id]
            ;

        // TODO: Restrictions on doc_dirname?
        local.doc_dirname =
                "dirname" >> hard_space
            >> (*(~cl::eps_p(']') >> local.char_))
                                            [actions.extract_doc_dirname]
            ;

        local.doc_copyright =
                "copyright"
            >> hard_space                   [cl::clear_a(actions.copyright.first)]
            >> +( cl::repeat_p(4)[cl::digit_p]
                                            [cl::push_back_a(actions.copyright.first)]
                  >> space
                )
            >> space
            >> (*(~cl::eps_p(']') >> local.char_))
                                            [actions.extract_copyright_second]
            ;

        local.doc_purpose =
                "purpose" >> hard_space
            >> simple_phrase                [actions.extract_doc_purpose]
            ;

        local.doc_category =
                "category" >> hard_space
            >> (*(~cl::eps_p(']') >> local.char_))
                                            [actions.extract_doc_category]
                                            [cl::push_back_a(actions.doc_categories, actions.doc_category)]
            ;

        local.doc_author =
                '[' >> space
            >>  (*(~cl::eps_p(',') >> local.char_))
                                            [actions.extract_name_second]
            >>  ',' >> space
            >>  (*(~cl::eps_p(']') >> local.char_))
                                            [actions.extract_name_first]
            >>  ']'
            ;

        local.doc_authors =
                "authors"
            >>  hard_space
            >>  local.doc_author            [cl::push_back_a(actions.doc_authors, actions.name)]
            >>  space
            >>  *(  !(cl::ch_p(',') >> space)
                >>  local.doc_author        [cl::push_back_a(actions.doc_authors, actions.name)]
                >>  space
                )
            ;

        local.doc_license =
                "license" >> hard_space
            >> simple_phrase                [actions.extract_doc_license]
            ;

        local.doc_last_revision =
                "last-revision" >> hard_space
            >> (*(~cl::eps_p(']') >> local.char_))
                                            [actions.extract_doc_last_revision]
            ;

        local.doc_source_mode =
                "source-mode" >> hard_space
            >>  (
                   cl::str_p("c++") 
                |  "python"
                |  "teletype"
                )                           [cl::assign_a(actions.source_mode)]
            ;

        local.doc_biblioid =
                "biblioid"
            >>  hard_space
            >>  (+cl::alnum_p)              [cl::assign_a(actions.doc_biblioid.first)]
            >>  hard_space
            >>  (+(~cl::eps_p(']') >> local.char_))
                                            [actions.extract_doc_biblioid]
                                            [cl::push_back_a(actions.doc_biblioid_items, actions.doc_biblioid)]
            ;

        local.doc_lang =
                "lang" >> hard_space
            >> (*(~cl::eps_p(']') >> local.char_))
                                            [actions.extract_doc_lang]
            ;

        local.char_ =
                cl::str_p("\\n")            [actions.break_]
            |   "\\ "                       // ignore an escaped space
            |   '\\' >> cl::punct_p         [actions.raw_char]
            |   "\\u" >> cl::repeat_p(4)
                    [cl::chset<>("0-9a-fA-F")]
                                            [actions.escape_unicode]
            |   "\\U" >> cl::repeat_p(8)
                    [cl::chset<>("0-9a-fA-F")]
                                            [actions.escape_unicode]
            |   (
                    ("'''" >> !cl::eol_p)   [actions.escape_pre]
                >>  *(cl::anychar_p - "'''")[actions.raw_char]
                >>  cl::str_p("'''")        [actions.escape_post]
                )
            |   cl::anychar_p               [actions.plain_char]
            ;
    }
}
