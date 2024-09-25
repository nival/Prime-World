//  common_type_test.cpp  ----------------------------------------------------//

//  Copyright 2010 Beman Dawes

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#include "test.hpp"
#include "check_type.hpp"
#ifdef TEST_STD
#  include <type_traits>
#else
#  include <boost/type_traits/common_type.hpp>
#endif
#include <iostream>

#ifdef BOOST_INTEL
#pragma warning(disable: 304 383)
#endif

struct C1 {};
    
struct C2 {};

    
struct C3 : C2 {};
struct C1C2 {
    C1C2() {}
    C1C2(C1 const&) {}
    C1C2(C2 const&) {}
    C1C2& operator=(C1C2 const&) {
        return *this;
    }
};

template <typename C, typename A>
void proc2(typename boost::common_type<A, C>::type const& ) {}

template <typename C, typename A, typename B>
void proc3(typename boost::common_type<C, A, B>::type const& ) {}

template <typename C, typename A>
void assignation_2() {
typedef typename boost::common_type<A, C>::type AC;
    A a;
    C c;
    AC ac;
    ac=a;
    ac=c;

    proc2<C, A>(a);
    proc2<C, A>(c);
    
}

template <typename C, typename A, typename B>
void assignation_3() {
typedef typename boost::common_type<C, A, B>::type ABC;
    A a;
    B b;
    C c;
    ABC abc;
    
    abc=a;
    abc=b;
    abc=c;
    
    proc3<C, A, B>(a);
    proc3<C, A, B>(b);
    proc3<C, A, B>(c);
}

C1C2 c1c2;
C1 c1;

int f(C1C2 ) { return 1;}
int f(C1 ) { return 2;}
template <typename OSTREAM>
OSTREAM& operator<<(OSTREAM& os, C1 const&) {return os;}

C1C2& declval_C1C2() {return c1c2;}
C1& declval_C1(){return c1;}
bool declval_bool(){return true;}


TT_TEST_BEGIN(common_type)
{
    assignation_2<C1C2, C1>();
    typedef tt::common_type<C1C2&, C1&>::type T1;
    typedef tt::common_type<C3*, C2*>::type T2;
    typedef tt::common_type<int*, int const*>::type T3;
#if defined(BOOST_NO_DECLTYPE) && !defined(BOOST_COMMON_TYPE_DONT_USE_TYPEOF)
    // fails if BOOST_COMMON_TYPE_DONT_USE_TYPEOF:
    typedef tt::common_type<int volatile*, int const*>::type T4;
#endif
    typedef tt::common_type<int*, int volatile*>::type T5;

    assignation_2<C1, C1C2>();
    assignation_2<C1C2, C2>();
    assignation_2<C2, C1C2>();
    assignation_3<C1, C1C2, C2>();
    assignation_3<C1C2, C1, C2>();
    assignation_3<C2, C1C2, C1>();
    assignation_3<C1C2, C2, C1>();
    //assignation_3<C1, C2, C1C2>(); // fails because the common type is the third
}
TT_TEST_END
