/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_ACTIONS_CLASS_HPP)
#define BOOST_SPIRIT_ACTIONS_CLASS_HPP

#include "actions.hpp"
#include "scoped_parser.hpp"
#include <boost/tuple/tuple.hpp>
#include <boost/scoped_ptr.hpp>

namespace quickbook
{
    namespace cl = boost::spirit::classic;
    namespace fs = boost::filesystem;

    struct actions
    {
        actions(char const* filein_, fs::path const& outdir, string_stream& out_);

    private:
        boost::scoped_ptr<quickbook_grammar> grammar_;

    public:
    ///////////////////////////////////////////////////////////////////////////
    // State
    ///////////////////////////////////////////////////////////////////////////

        typedef std::vector<std::string> string_list;

        typedef std::vector<docinfo_string> docinfo_list;
        typedef std::pair<docinfo_string, docinfo_string> author;
        typedef std::vector<author> author_list;
        typedef std::pair<string_list, docinfo_string> copyright_item;
        typedef std::vector<copyright_item> copyright_list;
        typedef std::pair<std::string, docinfo_string> biblioid_item;
        typedef std::vector<biblioid_item> biblioid_list;
        typedef std::pair<char, int> mark_type;
        static int const max_template_depth = 100;

    // header info
        std::string             doc_type;
        docinfo_string          doc_title;
        docinfo_string          doc_version;
        std::string             doc_id;
        docinfo_string          doc_dirname;
        copyright_list          doc_copyrights;
        docinfo_string          doc_purpose;
        docinfo_list            doc_categories;
        author_list             doc_authors;
        docinfo_string          doc_license;
        docinfo_string          doc_last_revision;
        biblioid_list           doc_biblioid_items;
        docinfo_string          doc_lang;
        std::string             include_doc_id;
        //temporary state
        biblioid_item           doc_biblioid;
        docinfo_string          doc_id_tmp;
        author                  name;
        copyright_item          copyright;
        docinfo_string          doc_category;


    // main output stream
        collector               out;

    // auxilliary streams
        collector               phrase;
        collector               list_buffer;

    // state
        fs::path                filename;
        fs::path                outdir;
        std::size_t             macro_change_depth;
        string_symbols          macro;
        int                     section_level;
        int                     min_section_level;
        std::string             section_id;
        std::string             qualified_section_id;
        std::string             source_mode;

        typedef boost::tuple<
            fs::path
          , fs::path
          , std::size_t
          , int
          , int
          , std::string
          , std::string
          , std::string>
        state_tuple;

        std::stack<state_tuple> state_stack;
        // Stack macros separately as copying macros is expensive.
        std::stack<string_symbols> macro_stack;

    // temporary or global state
        std::string             element_id;
        std::string             table_title;
        unsigned                table_span;
        std::string             table_header;
        std::string             macro_id;
        std::stack<mark_type>   list_marks;
        int                     list_indent;
        bool                    condition;
        std::string             template_identifier;
        string_list             template_info;
        int                     template_depth;
        bool                    template_escape;
        bool                    template_block;
        std::vector<quickbook::template_body>
                                template_args;
        template_stack          templates;
        int                     error_count;
        std::string             image_fileref;
        std::string             attribute_name;
        attribute_map           attributes;
        string_list             anchors;
        string_list             saved_anchors;
        bool                    no_eols;
        bool                    suppress;

    // push/pop the states and the streams
        void copy_macros_for_write();
        void push();
        void pop();
        quickbook_grammar& grammar() const;

    ///////////////////////////////////////////////////////////////////////////
    // actions
    ///////////////////////////////////////////////////////////////////////////
        error_action            error;
        phrase_to_docinfo_action extract_doc_title;
        phrase_to_docinfo_action extract_doc_license;
        phrase_to_docinfo_action extract_doc_purpose;
        phrase_to_docinfo_action extract_doc_version;
        phrase_to_docinfo_action extract_doc_id;
        phrase_to_docinfo_action extract_doc_dirname;
        phrase_to_docinfo_action extract_copyright_second;
        phrase_to_docinfo_action extract_name_second;
        phrase_to_docinfo_action extract_name_first;
        phrase_to_docinfo_action extract_doc_last_revision;
        phrase_to_docinfo_action extract_doc_category;
        phrase_to_docinfo_action extract_doc_biblioid;
        phrase_to_docinfo_action extract_doc_lang;

        scoped_parser<scoped_block_push>
                                scoped_block;

        code_action             code;
        code_action             code_block;
        inline_code_action      inline_code;
        implicit_paragraph_action inside_paragraph;
        generic_header_action   h;
        header_action           h1, h2, h3, h4, h5, h6;
        markup_action           hr;
        tagged_action           blurb, blockquote;
        scoped_parser<set_no_eols_scoped>
                                set_no_eols;
        phrase_action           preformatted;
        tagged_action           warning, caution, important, note, tip;
        space                   space_char;
        plain_char_action       plain_char;
        raw_char_action         raw_char;
        escape_unicode_action   escape_unicode;
        attribute_action        attribute;
        image_action            image;
        cond_phrase_action_pre  cond_phrase_pre;
        scoped_parser<cond_phrase_push>
                                scoped_cond_phrase;

        list_action             list;
        list_format_action      list_format;
        phrase_action           list_item;

        link_action             funcref_pre;
        markup_action           funcref_post;
        link_action             classref_pre;
        markup_action           classref_post;
        link_action             memberref_pre;
        markup_action           memberref_post;
        link_action             enumref_pre;
        markup_action           enumref_post;
        link_action             macroref_pre;
        markup_action           macroref_post;
        link_action             headerref_pre;
        markup_action           headerref_post;
        link_action             conceptref_pre;
        markup_action           conceptref_post;
        link_action             globalref_pre;
        markup_action           globalref_post;

        markup_action           bold_pre;
        markup_action           bold_post;
        markup_action           italic_pre;
        markup_action           italic_post;
        markup_action           underline_pre;
        markup_action           underline_post;
        markup_action           teletype_pre;
        markup_action           teletype_post;
        markup_action           strikethrough_pre;
        markup_action           strikethrough_post;
        markup_action           quote_pre;
        markup_action           quote_post;
        markup_action           replaceable_pre;
        markup_action           replaceable_post;
        markup_action           footnote_pre;
        markup_action           footnote_post;

        simple_phrase_action    simple_bold;
        simple_phrase_action    simple_italic;
        simple_phrase_action    simple_underline;
        simple_phrase_action    simple_teletype;
        simple_phrase_action    simple_strikethrough;

        variablelist_action     variablelist;
        markup_action           start_varlistentry;
        markup_action           end_varlistentry;
        markup_action           start_varlistterm;
        markup_action           end_varlistterm;
        tagged_action           varlistitem;

        break_action            break_;
        macro_identifier_action macro_identifier;
        macro_definition_action macro_definition;
        do_macro_action         do_macro;
        template_body_action    template_body;
        template_arg_action     template_arg;
        do_template_action      do_template;
        link_action             url_pre;
        markup_action           url_post;
        link_action             link_pre;
        markup_action           link_post;
        table_action            table;
        start_row_action        start_row;
        markup_action           end_row;
        col_action              cell;
        anchor_action           anchor;

        begin_section_action    begin_section;
        end_section_action      end_section;
        element_id_warning_action element_id_warning;
        xinclude_action         xinclude;
        include_action          include;
        import_action           import;

        markup_action           escape_pre;
        markup_action           escape_post;

        inner_phrase_action_pre inner_phrase_pre;
        inner_phrase_action_post inner_phrase_post;
        pre_output_action       output_pre;
    };
}

#endif // BOOST_SPIRIT_ACTIONS_CLASS_HPP

