/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TEST_TYPE_LISTS_HPP_JOFA_080916
#define BOOST_ICL_TEST_TYPE_LISTS_HPP_JOFA_080916

//#define BOOST_ICL_TEST_XINT
//#define BOOST_ICL_TEST_CHRONO

#include <boost/mpl/list.hpp>

// interval instance types
#include <boost/icl/gregorian.hpp> 
#include <boost/icl/ptime.hpp> 

#ifdef BOOST_ICL_TEST_XINT
#include <boost/icl/xint.hpp>
#endif

#ifdef BOOST_ICL_TEST_CHRONO
//JODO not working: #define BOOST_CHRONO_INLINED
#include <boost/icl/chrono.hpp>
#endif

#include <boost/icl/rational.hpp> 


#if(_MSC_VER < 1500 && defined(_DEBUG) ) // 1500 = MSVC-9.0
typedef int boost_posix_time_ptime;
typedef int boost_posix_time_duration;
typedef int boost_gregorian_date; 
typedef int boost_gregorian_date_duration;
#else
typedef boost::posix_time::ptime         boost_posix_time_ptime;
typedef boost::posix_time::time_duration boost_posix_time_duration;
typedef boost::gregorian::date           boost_gregorian_date;
typedef boost::gregorian::date_duration  boost_gregorian_date_duration;
#endif

typedef ::boost::mpl::list<
     unsigned short, unsigned int, unsigned long  
    ,short, int, long, long long
    ,float, double, long double
    ,boost::rational<int>
#ifdef BOOST_ICL_TEST_XINT
    ,boost::xint::integer
    ,boost::rational<boost::xint::integer>
#endif
#ifdef BOOST_ICL_TEST_CHRONO
    ,boost::chrono::duration<int>
    ,boost::chrono::duration<double>
#endif
    ,boost_posix_time_ptime
    ,boost_posix_time_duration
    ,boost_gregorian_date
    ,boost_gregorian_date_duration
    ,int*
> bicremental_types;

typedef unsigned int             bicremental_type_1;
typedef          int             bicremental_type_2;
typedef          double          bicremental_type_3;
typedef boost::rational<int>     bicremental_type_4;
typedef boost_posix_time_ptime   bicremental_type_5;
typedef          short           bicremental_type_6;
typedef          float           bicremental_type_7;
typedef          int*            bicremental_type_8;


typedef ::boost::mpl::list<
     short, int, long, long long
    ,float, double, long double
    ,boost::rational<int>
#ifdef BOOST_ICL_TEST_XINT
    ,boost::xint::integer
    ,boost::rational<boost::xint::integer>
#endif
#ifdef BOOST_ICL_TEST_CHRONO
    ,boost::chrono::duration<int>
    ,boost::chrono::duration<float>
#endif
> signed_bicremental_types;

typedef          int             signed_bicremental_type_1;
typedef          double          signed_bicremental_type_2;
typedef boost::rational<int>     signed_bicremental_type_3;
typedef          short           signed_bicremental_type_4;
typedef          float           signed_bicremental_type_5;

//DBG short list for debugging
typedef ::boost::mpl::list<
    int
> debug_types;

typedef ::boost::mpl::list<
    float, double, long double
    ,boost::rational<int>
#ifdef BOOST_ICL_TEST_XINT
    ,boost::rational<boost::xint::integer>
#endif
#ifdef BOOST_ICL_TEST_CHRONO
    ,boost::chrono::duration<double>
#endif
> bicremental_continuous_types;

typedef float                bicremental_continuous_type_1;
typedef double               bicremental_continuous_type_2;
typedef boost::rational<int> bicremental_continuous_type_3;


typedef ::boost::mpl::list<
    unsigned short, unsigned int
    ,unsigned long, unsigned long long  
    ,short, int, long, long long
#ifdef BOOST_ICL_TEST_XINT
    ,boost::xint::integer
#endif
> integral_types;

typedef int           integral_type_1;
typedef unsigned int  integral_type_2;
typedef short         integral_type_3;
typedef unsigned int  integral_type_4;

typedef ::boost::mpl::list<
    unsigned short, unsigned int
    ,unsigned long, unsigned long long  
    ,short, int, long
#ifdef BOOST_ICL_TEST_XINT
    ,boost::xint::integer
#endif
#ifdef BOOST_ICL_TEST_CHRONO
    ,boost::chrono::duration<unsigned short>
#endif
    ,boost_posix_time_ptime
    ,boost_posix_time_ptime
    ,boost_posix_time_duration
    ,boost_gregorian_date
    ,boost_gregorian_date_duration
    ,int*
> discrete_types;

typedef int                      discrete_type_1;
typedef boost_posix_time_ptime   discrete_type_2;
typedef unsigned int             discrete_type_3;
typedef short                    discrete_type_4;
typedef unsigned int             discrete_type_5;

typedef ::boost::mpl::list<
     short, int, long
> signed_discrete_types;

typedef int                      signed_discrete_type_1;
typedef short                    signed_discrete_type_2;
typedef long                     signed_discrete_type_3;

typedef ::boost::mpl::list<
    float, double, long double
    ,boost::rational<int>
#ifdef BOOST_ICL_TEST_XINT
    ,boost::rational<boost::xint::integer>
#endif
#ifdef BOOST_ICL_TEST_CHRONO
    ,boost::chrono::duration<long double>
#endif
> numeric_continuous_types;

typedef double               numeric_continuous_type_1;
typedef float                numeric_continuous_type_2;
typedef boost::rational<int> numeric_continuous_type_3;
typedef long double          numeric_continuous_type_4;

typedef ::boost::mpl::list<
    float, double, long double
    ,boost::rational<int>
#ifdef BOOST_ICL_TEST_XINT
    ,boost::rational<boost::xint::integer>
#endif
#ifdef BOOST_ICL_TEST_CHRONO
    ,boost::chrono::duration<double>
#endif
    ,std::string
> continuous_types;

typedef double               continuous_type_1;
typedef float                continuous_type_2;
typedef boost::rational<int> continuous_type_3;
typedef std::string          continuous_type_4;

typedef ::boost::mpl::list<
    unsigned short, unsigned int
    ,unsigned long, unsigned long long  
    ,short, int, long, long long
    ,float, double, long double
    ,boost::rational<int>
#ifdef BOOST_ICL_TEST_XINT
    ,boost::xint::integer
#endif
#ifdef BOOST_ICL_TEST_CHRONO
    ,boost::chrono::duration<short>
    ,boost::chrono::duration<long double>
#endif
    ,boost_posix_time_ptime
    ,boost_posix_time_duration
    ,boost_gregorian_date
    ,boost_gregorian_date_duration
    ,int*
    ,std::string
> ordered_types;

typedef int                      ordered_type_1;
typedef std::string              ordered_type_2;
typedef boost_posix_time_ptime   ordered_type_3;
typedef boost::rational<int>     ordered_type_4;
typedef double                   ordered_type_5;

#endif 

