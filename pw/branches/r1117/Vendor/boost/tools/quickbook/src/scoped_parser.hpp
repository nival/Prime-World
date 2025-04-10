/*=============================================================================
    Copyright (c) 2010 Daniel James
    Copyright (c) 2003 Martin Wille
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/
 
// Used to store variables/state while parsing 

#ifndef BOOST_QUICKBOOK_SCOPED_PARSER_HPP
#define BOOST_QUICKBOOK_SCOPED_PARSER_HPP

#include <boost/spirit/include/classic_core.hpp>

namespace quickbook {
    namespace cl = boost::spirit::classic;
    
    template <typename ScopeT, typename DataT, typename ParserT>
    struct scoped_parser_impl
        : public cl::unary< ParserT, cl::parser< scoped_parser_impl<ScopeT, DataT, ParserT> > >
    {
        typedef scoped_parser_impl<ScopeT, DataT, ParserT> self_t;
        typedef cl::unary< ParserT, cl::parser< scoped_parser_impl<ScopeT, DataT, ParserT> > > base_t;

        template <typename ScannerT>
        struct result :
            ScopeT::template result<
                typename cl::parser_result<ParserT, ScannerT>::type
            >
        {
        };

        scoped_parser_impl(DataT& actions, ParserT const &p)
            : base_t(p)
            , actions(actions)
        {}

        template <typename ScannerT>
        typename result<ScannerT>::type parse(ScannerT const &scan) const
        {
            typedef typename ScannerT::iterator_t iterator_t;
            iterator_t save = scan.first;

            ScopeT scope(actions);
            typename cl::parser_result<ParserT, ScannerT>::type result
                = this->subject().parse(scan);

            if (result) {
                return scan.create_match(result.length(), scope.success(result), save, scan.first);
            }
            else {
                scope.failure();
                return scan.no_match();
            }
        }
        
        DataT& actions;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    // scoped_parser
    //
    //      generator for scoped_parser_impl objects
    //      operator[] returns scoped_parser_impl according to its argument
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ScopeT>
    struct scoped_parser
    {
        typedef typename ScopeT::data_type data_type;
    
        explicit scoped_parser(data_type& actions)
            : actions(actions) {}

        template<typename ParserT>
        scoped_parser_impl
        <
            ScopeT,
            data_type,
            typename cl::as_parser<ParserT>::type
        >
        operator[](ParserT const &p) const
        {
            typedef cl::as_parser<ParserT> as_parser_t;
            typedef typename as_parser_t::type parser_t;

            return scoped_parser_impl<ScopeT, data_type, parser_t>
                (actions, as_parser_t::convert(p));
        }
        
        data_type& actions;
    };
}
#endif // BOOST_QUICKBOOK_SCOPED_BLOCK_HPP
