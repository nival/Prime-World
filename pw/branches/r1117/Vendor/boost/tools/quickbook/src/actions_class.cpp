/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    Copyright (c) 2005 Thomas Guest
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include "actions_class.hpp"
#include "markups.hpp"
#include "quickbook.hpp"
#include "grammar.hpp"

#if (defined(BOOST_MSVC) && (BOOST_MSVC <= 1310))
#pragma warning(disable:4355)
#endif

namespace quickbook
{
    actions::actions(char const* filein_, fs::path const& outdir_, string_stream& out_)
        : grammar_()

    // header info
        , doc_type()
        , doc_title()
        , doc_version()
        , doc_id()
        , doc_dirname()
        , doc_copyrights()
        , doc_purpose()
        , doc_categories()
        , doc_authors()
        , doc_license()
        , doc_last_revision()
        , include_doc_id()

    // main output stream
        , out(out_)

    // auxilliary streams
        , phrase()
        , list_buffer()

    // state
        , filename(fs::absolute(fs::path(filein_)))
        , outdir(outdir_)
        , macro_change_depth(0)
        , macro()
        , section_level(0)
        , min_section_level(0)
        , section_id()
        , qualified_section_id()
        , source_mode("c++")

    // temporary or global state
        , element_id()
        , table_title()
        , table_span(0)
        , table_header()
        , macro_id()
        , list_marks()
        , list_indent(-1)
        , template_identifier()
        , template_info()
        , template_depth(0)
        , template_escape(false)
        , templates()
        , error_count(0)
        , image_fileref()
        , attribute_name()
        , attributes()
        , anchors()
        , saved_anchors()
        , no_eols(true)
        , suppress(false)

    // actions
        , error(error_count)
        , extract_doc_title(doc_title, phrase, *this)
        , extract_doc_license(doc_license, phrase, *this)
        , extract_doc_purpose(doc_purpose, phrase, *this)
        , extract_doc_version(doc_version, phrase, *this)
        , extract_doc_id(doc_id_tmp, phrase, *this)
        , extract_doc_dirname(doc_dirname, phrase, *this)
        , extract_copyright_second(copyright.second, phrase, *this)
        , extract_name_second(name.second, phrase, *this)
        , extract_name_first(name.first, phrase, *this)
        , extract_doc_last_revision(doc_last_revision, phrase, *this)
        , extract_doc_category(doc_category, phrase, *this)
        , extract_doc_biblioid(doc_biblioid.second, phrase, *this)
        , extract_doc_lang(doc_lang, phrase, *this)
        , scoped_block(*this)
        , code(out, phrase, *this)
        , code_block(phrase, phrase, *this)
        , inline_code(phrase, *this)
        , inside_paragraph(out, phrase, paragraph_pre, paragraph_post, *this)
        , h(out, phrase, element_id, doc_id, section_id, qualified_section_id, section_level, *this)
        , h1(out, phrase, element_id, doc_id, section_id, qualified_section_id, h1_pre, h1_post, *this)
        , h2(out, phrase, element_id, doc_id, section_id, qualified_section_id, h2_pre, h2_post, *this)
        , h3(out, phrase, element_id, doc_id, section_id, qualified_section_id, h3_pre, h3_post, *this)
        , h4(out, phrase, element_id, doc_id, section_id, qualified_section_id, h4_pre, h4_post, *this)
        , h5(out, phrase, element_id, doc_id, section_id, qualified_section_id, h5_pre, h5_post, *this)
        , h6(out, phrase, element_id, doc_id, section_id, qualified_section_id, h6_pre, h6_post, *this)
        , hr(out, hr_, *this)
        , blurb(out, blurb_pre, blurb_post, *this)
        , blockquote(out, blockquote_pre, blockquote_post, *this)
        , set_no_eols(*this)
        , preformatted(out, phrase, preformatted_pre, preformatted_post, *this)
        , warning(out, warning_pre, warning_post, *this)
        , caution(out, caution_pre, caution_post, *this)
        , important(out, important_pre, important_post, *this)
        , note(out, note_pre, note_post, *this)
        , tip(out, tip_pre, tip_post, *this)
        , space_char(phrase)
        , plain_char(phrase, *this)
        , raw_char(phrase, *this)
        , escape_unicode(phrase, *this)
        , attribute(attributes, attribute_name, error_count)
        , image(phrase, attributes, image_fileref, *this)
        , cond_phrase_pre(condition, macro)
        , scoped_cond_phrase(*this)

        , list(out, list_buffer, list_indent, list_marks, *this)
        , list_format(list_buffer, list_indent, list_marks, error_count, *this)
        , list_item(list_buffer, phrase, list_item_pre, list_item_post, *this)

        , funcref_pre(phrase, funcref_pre_, *this)
        , funcref_post(phrase, funcref_post_, *this)
        , classref_pre(phrase, classref_pre_, *this)
        , classref_post(phrase, classref_post_, *this)
        , memberref_pre(phrase, memberref_pre_, *this)
        , memberref_post(phrase, memberref_post_, *this)
        , enumref_pre(phrase, enumref_pre_, *this)
        , enumref_post(phrase, enumref_post_, *this)
        , macroref_pre(phrase, macroref_pre_, *this)
        , macroref_post(phrase, macroref_post_, *this)
        , headerref_pre(phrase, headerref_pre_, *this)
        , headerref_post(phrase, headerref_post_, *this)
        , conceptref_pre(phrase, conceptref_pre_, *this)
        , conceptref_post(phrase, conceptref_post_, *this)
        , globalref_pre(phrase, globalref_pre_, *this)
        , globalref_post(phrase, globalref_post_, *this)

        , bold_pre(phrase, bold_pre_, *this)
        , bold_post(phrase, bold_post_, *this)
        , italic_pre(phrase, italic_pre_, *this)
        , italic_post(phrase, italic_post_, *this)
        , underline_pre(phrase, underline_pre_, *this)
        , underline_post(phrase, underline_post_, *this)
        , teletype_pre(phrase, teletype_pre_, *this)
        , teletype_post(phrase, teletype_post_, *this)
        , strikethrough_pre(phrase, strikethrough_pre_, *this)
        , strikethrough_post(phrase, strikethrough_post_, *this)
        , quote_pre(phrase, quote_pre_, *this)
        , quote_post(phrase, quote_post_, *this)
        , replaceable_pre(phrase, replaceable_pre_, *this)
        , replaceable_post(phrase, replaceable_post_, *this)
        , footnote_pre(phrase, footnote_pre_, *this)
        , footnote_post(phrase, footnote_post_, *this)

        , simple_bold(phrase, bold_pre_, bold_post_, macro, *this)
        , simple_italic(phrase, italic_pre_, italic_post_, macro, *this)
        , simple_underline(phrase, underline_pre_, underline_post_, macro, *this)
        , simple_teletype(phrase, teletype_pre_, teletype_post_, macro, *this)
        , simple_strikethrough(phrase, strikethrough_pre_, strikethrough_post_, macro, *this)

        , variablelist(*this)
        , start_varlistentry(phrase, start_varlistentry_, *this)
        , end_varlistentry(phrase, end_varlistentry_, *this)
        , start_varlistterm(phrase, start_varlistterm_, *this)
        , end_varlistterm(phrase, end_varlistterm_, *this)
        , varlistitem(phrase, start_varlistitem_, end_varlistitem_, *this)

        , break_(phrase, *this)
        , macro_identifier(*this)
        , macro_definition(*this)
        , do_macro(phrase, *this)
        , template_body(*this)
        , template_arg(*this)
        , do_template(*this)
        , url_pre(phrase, url_pre_, *this)
        , url_post(phrase, url_post_, *this)
        , link_pre(phrase, link_pre_, *this)
        , link_post(phrase, link_post_, *this)
        , table(*this)
        , start_row(phrase, table_span, table_header, *this)
        , end_row(phrase, end_row_, *this)
        , cell(phrase, table_span, *this)
        , anchor(*this)

        , begin_section(out, phrase, doc_id, section_id, section_level, qualified_section_id, element_id, *this)
        , end_section(out, section_level, min_section_level, qualified_section_id, error_count, *this)
        , xinclude(out, *this)
        , include(*this)
        , import(out, *this)

        , escape_pre(phrase, escape_pre_, *this)
        , escape_post(phrase, escape_post_, *this)
        
        , inner_phrase_pre(*this)
        , inner_phrase_post(*this)
        , output_pre(*this)
    {
        // turn off __FILENAME__ macro on debug mode = true
        std::string filename_str = debug_mode ?
            std::string("NO_FILENAME_MACRO_GENERATED_IN_DEBUG_MODE") :
            filename.string();

        // add the predefined macros
        macro.add
            ("__DATE__", std::string(quickbook_get_date))
            ("__TIME__", std::string(quickbook_get_time))
            ("__FILENAME__", filename_str)
        ;
        
        boost::scoped_ptr<quickbook_grammar> g(
            new quickbook_grammar(*this));
        grammar_.swap(g);
    }
    
    void actions::push()
    {
        state_stack.push(
            boost::make_tuple(
                filename
              , outdir
              , macro_change_depth
              , section_level
              , min_section_level
              , section_id
              , qualified_section_id
              , source_mode
            )
        );

        out.push();
        phrase.push();
        list_buffer.push();
        templates.push();        
    }
    
    // Pushing and popping the macro symbol table is pretty expensive, so
    // instead implement a sort of 'stack on write'. Call this whenever a
    // change is made to the macro table, and it'll stack the current macros
    // if necessary. Would probably be better to implement macros in a less
    // expensive manner.
    void actions::copy_macros_for_write()
    {
        if(macro_change_depth != state_stack.size())
        {
            macro_stack.push(macro);
            macro_change_depth = state_stack.size();
        }
    }

    void actions::pop()
    {
        if(macro_change_depth == state_stack.size())
        {
            macro = macro_stack.top();
            macro_stack.pop();
        }
    
        boost::tie(
            filename
          , outdir
          , macro_change_depth
          , section_level
          , min_section_level
          , section_id
          , qualified_section_id
          , source_mode
        ) = state_stack.top();
        state_stack.pop();

        out.pop();
        phrase.pop();
        list_buffer.pop();
        templates.pop();
    }
    
    quickbook_grammar& actions::grammar() const {
        return *grammar_;
    }
}
