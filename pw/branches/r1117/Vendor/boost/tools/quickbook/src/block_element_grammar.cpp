/*=============================================================================
    Copyright (c) 2002 2004  2006Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include "utils.hpp"
#include "actions_class.hpp"
#include "grammar_impl.hpp"
#include <boost/spirit/include/classic_assign_actor.hpp>
#include <boost/spirit/include/classic_if.hpp>
#include <boost/spirit/include/classic_clear_actor.hpp>

namespace quickbook
{
    namespace cl = boost::spirit::classic;

    struct block_element_grammar_local
    {
        cl::rule<scanner>
                        h, h1, h2, h3, h4, h5, h6, blurb, blockquote,
                        warning, caution, important, note, tip,
                        inner_phrase, def_macro,
                        table, table_row, variablelist,
                        varlistentry, varlistterm, varlistitem, table_cell,
                        preformatted, begin_section, end_section,
                        xinclude, include,
                        template_, template_id, template_formal_arg,
                        template_body, identifier, import,
                        element_id, element_id_1_5, element_id_1_6;
    };

    void quickbook_grammar::impl::init_block_elements()
    {
        using detail::var;

        block_element_grammar_local& local = store_.create();

        local.element_id =
                ':'
            >>
                (
                    cl::if_p(qbk_since(105u)) [space]
                >>  (+(cl::alnum_p | '_'))      [cl::assign_a(actions.element_id)]
                |   cl::eps_p                   [actions.element_id_warning]
                                                [cl::assign_a(actions.element_id)]
                )
            | cl::eps_p                         [cl::assign_a(actions.element_id)]
            ;
        
        local.element_id_1_5 =
                cl::if_p(qbk_since(105u)) [
                    local.element_id
                ]
                .else_p [
                    cl::eps_p                   [cl::assign_a(actions.element_id)]
                ]
                ;

        local.element_id_1_6 =
                cl::if_p(qbk_since(106u)) [
                    local.element_id
                ]
                .else_p [
                    cl::eps_p                   [cl::assign_a(actions.element_id)]
                ]
                ;

        elements.add
            ("section", element_info(element_info::block, &local.begin_section))
            ("endsect", element_info(element_info::block, &local.end_section))
            ;

        local.begin_section =
                space
            >>  local.element_id
            >>  space
            >>  local.inner_phrase              [actions.begin_section]
            ;

        local.end_section =
                cl::eps_p                       [actions.end_section]
            ;

        elements.add
            ("heading", element_info(element_info::block, &local.h))
            ("h1", element_info(element_info::block, &local.h1))
            ("h2", element_info(element_info::block, &local.h2))
            ("h3", element_info(element_info::block, &local.h3))
            ("h4", element_info(element_info::block, &local.h4))
            ("h5", element_info(element_info::block, &local.h5))
            ("h6", element_info(element_info::block, &local.h6))
            ;

        local.h  = space >> local.element_id_1_6 >> space >> local.inner_phrase [actions.h];
        local.h1 = space >> local.element_id_1_6 >> space >> local.inner_phrase [actions.h1];
        local.h2 = space >> local.element_id_1_6 >> space >> local.inner_phrase [actions.h2];
        local.h3 = space >> local.element_id_1_6 >> space >> local.inner_phrase [actions.h3];
        local.h4 = space >> local.element_id_1_6 >> space >> local.inner_phrase [actions.h4];
        local.h5 = space >> local.element_id_1_6 >> space >> local.inner_phrase [actions.h5];
        local.h6 = space >> local.element_id_1_6 >> space >> local.inner_phrase [actions.h6];
        
        static const bool true_ = true;
        static const bool false_ = false;

        elements.add("blurb", element_info(element_info::block, &local.blurb));

        local.blurb =
            actions.scoped_block[inside_paragraph]
                                                [actions.blurb]
            ;

        elements.add
            (":", element_info(element_info::block, &local.blockquote))
            ;

        local.blockquote =
            blank >> actions.scoped_block[inside_paragraph]
                                                [actions.blockquote]
            ;

        elements.add
            ("warning", element_info(element_info::block, &local.warning))
            ("caution", element_info(element_info::block, &local.caution))
            ("important", element_info(element_info::block, &local.important))
            ("note", element_info(element_info::block, &local.note))
            ("tip", element_info(element_info::block, &local.tip))
            ;

        local.warning =
            actions.scoped_block[inside_paragraph]
                                                [actions.warning]
            ;

        local.caution =
            actions.scoped_block[inside_paragraph]
                                                [actions.caution]
            ;

        local.important =
            actions.scoped_block[inside_paragraph]
                                                [actions.important]
            ;

        local.note =
            actions.scoped_block[inside_paragraph]
                                                [actions.note]
            ;

        local.tip =
            actions.scoped_block[inside_paragraph]
                                                [actions.tip]
            ;

        elements.add
            ("pre", element_info(element_info::block, &local.preformatted))
            ;

        local.preformatted =
                space
            >>  !eol
            >>  actions.set_no_eols[phrase]     [actions.preformatted]
            ;

        elements.add
            ("def", element_info(element_info::block, &local.def_macro))
            ;

        local.def_macro =
               space
            >> macro_identifier                 [actions.macro_identifier]
            >> blank >> phrase                  [actions.macro_definition]
            ;

        local.identifier =
            (cl::alpha_p | '_') >> *(cl::alnum_p | '_')
            ;

        local.template_id =
            local.identifier | (cl::punct_p - (cl::ch_p('[') | ']'))
            ;

        elements.add
            ("template", element_info(element_info::block, &local.template_))
            ;

        local.template_ =
               space
            >> local.template_id                [cl::assign_a(actions.template_identifier)]
                                                [cl::clear_a(actions.template_info)]
            >>
            !(
                space >> '['
                >> *(
                        space
                    >>  local.template_id       [cl::push_back_a(actions.template_info)]
                    )
                >> space >> ']'
            )
            >>  (   cl::eps_p(*cl::blank_p >> cl::eol_p)
                                                [cl::assign_a(actions.template_block, true_)]
                |   cl::eps_p                   [cl::assign_a(actions.template_block, false_)]
                )
            >>  local.template_body             [actions.template_body]
            ;

        local.template_body =
           *(('[' >> local.template_body >> ']') | (cl::anychar_p - ']'))
            >> cl::eps_p(space >> ']')
            >> space
            ;

        elements.add
            ("variablelist", element_info(element_info::block, &local.variablelist))
            ;

        local.variablelist =
                (cl::eps_p(*cl::blank_p >> cl::eol_p) | space)
            >>  (*(cl::anychar_p - eol))        [cl::assign_a(actions.table_title)]
            >>  (+eol)                          [actions.output_pre]
            >>  *local.varlistentry
            >>  cl::eps_p                       [actions.variablelist]
            ;

        local.varlistentry =
            space
            >>  cl::ch_p('[')                   [actions.start_varlistentry]
            >>
            (
                (
                    local.varlistterm
                    >>  (   actions.scoped_block [+local.varlistitem]
                                                [actions.varlistitem]
                        |   cl::eps_p           [actions.error]
                        )
                    >>  cl::ch_p(']')           [actions.end_varlistentry]
                    >>  space
                )
                | cl::eps_p                     [actions.error]
            )
            ;

        local.varlistterm =
            space
            >>  cl::ch_p('[')                   [actions.start_varlistterm]
            >>
            (
                (
                    phrase
                    >>  cl::ch_p(']')           [actions.end_varlistterm]
                    >>  space
                )
                | cl::eps_p                     [actions.error]
            )
            ;

        local.varlistitem =
            space
            >>  cl::ch_p('[')
            >>
            (
                (
                    inside_paragraph
                    >>  cl::ch_p(']')
                    >>  space
                )
                | cl::eps_p                     [actions.error]
            )
            ;

        elements.add
            ("table", element_info(element_info::block, &local.table))
            ;

        local.table =
                (cl::eps_p(*cl::blank_p >> cl::eol_p) | space)
            >>  local.element_id_1_5
            >>  (cl::eps_p(*cl::blank_p >> cl::eol_p) | space)
            >>  (*(cl::anychar_p - eol))        [cl::assign_a(actions.table_title)]
            >>  (+eol)                          [actions.output_pre]
            >>  *local.table_row
            >>  cl::eps_p                       [actions.table]
            ;

        local.table_row =
            space
            >>  cl::ch_p('[')                   [actions.start_row]
            >>
            (
                (
                    *local.table_cell
                    >>  cl::ch_p(']')           [actions.end_row]
                    >>  space
                )
                | cl::eps_p                     [actions.error]
            )
            ;

        local.table_cell =
                space
            >>  cl::ch_p('[')
            >>  (   actions.scoped_block [
                        inside_paragraph
                    >>  cl::ch_p(']')
                    >>  space
                    ]                           [actions.cell]
                | cl::eps_p                     [actions.error]
                )
            ;

        elements.add
            ("xinclude", element_info(element_info::conditional_or_block, &local.xinclude))
            ("import", element_info(element_info::conditional_or_block, &local.import))
            ("include", element_info(element_info::conditional_or_block, &local.include))
            ;

        local.xinclude =
               space
            >> (*(cl::anychar_p - phrase_end))
                                                [actions.xinclude]
            ;

        local.import =
               space
            >> (*(cl::anychar_p - phrase_end))
                                                [actions.import]
            ;

        local.include =
               space
            >>
           !(
                ':'
                >> (*((cl::alnum_p | '_') - cl::space_p))
                                                [cl::assign_a(actions.include_doc_id)]
                >> space
            )
            >> (*(cl::anychar_p - phrase_end))
                                                [actions.include]
            ;

        local.inner_phrase =
                cl::eps_p                       [actions.inner_phrase_pre]
            >>  phrase
            >>  cl::eps_p                       [actions.inner_phrase_post]
            ;
    }
}
