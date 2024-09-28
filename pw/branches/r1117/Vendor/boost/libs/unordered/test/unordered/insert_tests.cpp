
// Copyright 2006-2010 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "../helpers/prefix.hpp"

#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>
#include "../helpers/test.hpp"
#include <boost/next_prior.hpp>
#include "../objects/test.hpp"
#include "../helpers/random_values.hpp"
#include "../helpers/tracker.hpp"
#include "../helpers/equivalent.hpp"
#include "../helpers/invariants.hpp"
#include "../helpers/input_iterator.hpp"

#include <iostream>

namespace insert_tests {
    
test::seed_t seed(243432);

template <class X>
void unique_insert_tests1(X*,
    test::random_generator generator = test::default_generator)
{
    typedef BOOST_DEDUCED_TYPENAME X::iterator iterator;
    typedef test::ordered<X> ordered;

    std::cerr<<"insert(value) tests for containers with unique keys.\n";

    X x;
    test::ordered<X> tracker = test::create_ordered(x);

    test::random_values<X> v(1000, generator);

    for(BOOST_DEDUCED_TYPENAME test::random_values<X>::iterator it = v.begin();
            it != v.end(); ++it)
    {

        BOOST_DEDUCED_TYPENAME X::size_type old_bucket_count = x.bucket_count();
        float b = x.max_load_factor();

        std::pair<iterator, bool> r1 = x.insert(*it);
        std::pair<BOOST_DEDUCED_TYPENAME ordered::iterator, bool>
            r2 = tracker.insert(*it);

        BOOST_TEST(r1.second == r2.second);
        BOOST_TEST(*r1.first == *r2.first);

        tracker.compare_key(x, *it);

        if(static_cast<double>(x.size()) < b * static_cast<double>(old_bucket_count))
            BOOST_TEST(x.bucket_count() == old_bucket_count);
    }

    test::check_equivalent_keys(x);
}

template <class X>
void equivalent_insert_tests1(X*,
    test::random_generator generator = test::default_generator)
{
    std::cerr<<"insert(value) tests for containers with equivalent keys.\n";

    X x;
    test::ordered<X> tracker = test::create_ordered(x);

    test::random_values<X> v(1000, generator);
    for(BOOST_DEDUCED_TYPENAME test::random_values<X>::iterator it = v.begin();
            it != v.end(); ++it)
    {
        BOOST_DEDUCED_TYPENAME X::size_type old_bucket_count = x.bucket_count();
        float b = x.max_load_factor();

        BOOST_DEDUCED_TYPENAME X::iterator r1 = x.insert(*it);
        BOOST_DEDUCED_TYPENAME test::ordered<X>::iterator r2
            = tracker.insert(*it);

        BOOST_TEST(*r1 == *r2);

        tracker.compare_key(x, *it);

        if(static_cast<double>(x.size()) < b * static_cast<double>(old_bucket_count))
            BOOST_TEST(x.bucket_count() == old_bucket_count);
    }

    test::check_equivalent_keys(x);
}

template <class X>
void insert_tests2(X*,
    test::random_generator generator = test::default_generator)
{
    typedef BOOST_DEDUCED_TYPENAME test::ordered<X> tracker_type;
    typedef BOOST_DEDUCED_TYPENAME X::iterator iterator;
    typedef BOOST_DEDUCED_TYPENAME X::const_iterator const_iterator;
    typedef BOOST_DEDUCED_TYPENAME tracker_type::iterator tracker_iterator;

    std::cerr<<"insert(begin(), value) tests.\n";

    {
        X x;
        tracker_type tracker = test::create_ordered(x);

        test::random_values<X> v(1000, generator);
        for(BOOST_DEDUCED_TYPENAME test::random_values<X>::iterator
            it = v.begin(); it != v.end(); ++it)
        {
            BOOST_DEDUCED_TYPENAME X::size_type
                old_bucket_count = x.bucket_count();
            float b = x.max_load_factor();

            iterator r1 = x.insert(x.begin(), *it);
            tracker_iterator r2 = tracker.insert(tracker.begin(), *it);
            BOOST_TEST(*r1 == *r2);
            tracker.compare_key(x, *it);

            if(static_cast<double>(x.size()) < b * static_cast<double>(old_bucket_count))
                BOOST_TEST(x.bucket_count() == old_bucket_count);
        }

        test::check_equivalent_keys(x);
    }

    std::cerr<<"insert(end(), value) tests.\n";

    {
        X x;
        X const& x_const = x;
        tracker_type tracker = test::create_ordered(x);

        test::random_values<X> v(100, generator);
        for(BOOST_DEDUCED_TYPENAME test::random_values<X>::iterator
            it = v.begin(); it != v.end(); ++it)
        {
            BOOST_DEDUCED_TYPENAME X::size_type
                old_bucket_count = x.bucket_count();
            float b = x.max_load_factor();

            const_iterator r1 = x.insert(x_const.end(), *it);
            tracker_iterator r2 = tracker.insert(tracker.end(), *it);
            BOOST_TEST(*r1 == *r2);
            tracker.compare_key(x, *it);

            if(static_cast<double>(x.size()) < b * static_cast<double>(old_bucket_count))
                BOOST_TEST(x.bucket_count() == old_bucket_count);
        }

        test::check_equivalent_keys(x);
    }

    std::cerr<<"insert(pos, value) tests.\n";

    {
        X x;
        const_iterator pos = x.begin();
        tracker_type tracker = test::create_ordered(x);

        test::random_values<X> v(1000, generator);
        for(BOOST_DEDUCED_TYPENAME test::random_values<X>::iterator
            it = v.begin(); it != v.end(); ++it)
        {
            BOOST_DEDUCED_TYPENAME X::size_type
                old_bucket_count = x.bucket_count();
            float b = x.max_load_factor();

            pos = x.insert(pos, *it);
            tracker_iterator r2 = tracker.insert(tracker.begin(), *it);
            BOOST_TEST(*pos == *r2);
            tracker.compare_key(x, *it);

            if(static_cast<double>(x.size()) < b * static_cast<double>(old_bucket_count))
                BOOST_TEST(x.bucket_count() == old_bucket_count);
        }

        test::check_equivalent_keys(x);
    }

    std::cerr<<"insert single item range tests.\n";

    {
        X x;
        tracker_type tracker = test::create_ordered(x);

        test::random_values<X> v(1000, generator);
        for(BOOST_DEDUCED_TYPENAME test::random_values<X>::iterator
            it = v.begin(); it != v.end(); ++it)
        {
            BOOST_DEDUCED_TYPENAME X::size_type
                old_bucket_count = x.bucket_count();
            float b = x.max_load_factor();

            x.insert(it, boost::next(it));
            tracker.insert(*it);
            tracker.compare_key(x, *it);

            if(static_cast<double>(x.size()) < b * static_cast<double>(old_bucket_count))
                BOOST_TEST(x.bucket_count() == old_bucket_count);
        }

        test::check_equivalent_keys(x);
    }

    std::cerr<<"insert range tests.\n";

    {
        X x;

        test::random_values<X> v(1000, generator);
        x.insert(v.begin(), v.end());

        test::check_container(x, v);
        test::check_equivalent_keys(x);
    }

    std::cerr<<"insert input iterator range tests.\n";

    {
        X x;

        test::random_values<X> v(1000, generator);
        BOOST_DEDUCED_TYPENAME test::random_values<X>::const_iterator
            begin = v.begin(), end = v.end();
        x.insert(test::input_iterator(begin), test::input_iterator(end));
        test::check_container(x, v);

        test::check_equivalent_keys(x);
    }

    std::cerr<<"insert copy iterator range tests.\n";

    {
        X x;

        test::random_values<X> v(1000, generator);
        x.insert(test::copy_iterator(v.begin()), test::copy_iterator(v.end()));
        test::check_container(x, v);

        test::check_equivalent_keys(x);
    }
}

#if !defined(BOOST_NO_RVALUE_REFERENCES) && !defined(BOOST_NO_VARIADIC_TEMPLATES)

template <class X>
void unique_emplace_tests1(X*,
    test::random_generator generator = test::default_generator)
{
    typedef BOOST_DEDUCED_TYPENAME X::iterator iterator;
    typedef test::ordered<X> ordered;

    std::cerr<<"emplace(value) tests for containers with unique keys.\n";

    X x;
    test::ordered<X> tracker = test::create_ordered(x);

    test::random_values<X> v(1000, generator);

    for(BOOST_DEDUCED_TYPENAME test::random_values<X>::iterator it = v.begin();
            it != v.end(); ++it)
    {

        BOOST_DEDUCED_TYPENAME X::size_type old_bucket_count = x.bucket_count();
        float b = x.max_load_factor();

        std::pair<iterator, bool> r1 = x.emplace(*it);
        std::pair<BOOST_DEDUCED_TYPENAME ordered::iterator, bool>
            r2 = tracker.insert(*it);

        BOOST_TEST(r1.second == r2.second);
        BOOST_TEST(*r1.first == *r2.first);

        tracker.compare_key(x, *it);

        if(static_cast<double>(x.size()) < b * static_cast<double>(old_bucket_count))
            BOOST_TEST(x.bucket_count() == old_bucket_count);
    }

    test::check_equivalent_keys(x);
}

template <class X>
void equivalent_emplace_tests1(X*,
    test::random_generator generator = test::default_generator)
{
    std::cerr<<"emplace(value) tests for containers with equivalent keys.\n";

    X x;
    test::ordered<X> tracker = test::create_ordered(x);

    test::random_values<X> v(1000, generator);
    for(BOOST_DEDUCED_TYPENAME test::random_values<X>::iterator it = v.begin();
            it != v.end(); ++it)
    {
        BOOST_DEDUCED_TYPENAME X::size_type old_bucket_count = x.bucket_count();
        float b = x.max_load_factor();

        BOOST_DEDUCED_TYPENAME X::iterator r1 = x.emplace(*it);
        BOOST_DEDUCED_TYPENAME test::ordered<X>::iterator
            r2 = tracker.insert(*it);

        BOOST_TEST(*r1 == *r2);

        tracker.compare_key(x, *it);

        if(static_cast<double>(x.size()) < b * static_cast<double>(old_bucket_count))
            BOOST_TEST(x.bucket_count() == old_bucket_count);
    }

    test::check_equivalent_keys(x);
}

#endif

template <class X>
void map_tests(X*, test::random_generator generator = test::default_generator)
{
    std::cerr<<"map tests.\n";

    X x;
    test::ordered<X> tracker = test::create_ordered(x);

    test::random_values<X> v(1000, generator);
    for(BOOST_DEDUCED_TYPENAME test::random_values<X>::iterator it = v.begin();
            it != v.end(); ++it)
    {
        BOOST_DEDUCED_TYPENAME X::size_type old_bucket_count = x.bucket_count();
        float b = x.max_load_factor();

        x[it->first] = it->second;
        tracker[it->first] = it->second;

        tracker.compare_key(x, *it);

        if(static_cast<double>(x.size()) < b * static_cast<double>(old_bucket_count))
            BOOST_TEST(x.bucket_count() == old_bucket_count);
    }

    test::check_equivalent_keys(x);   
}

// Some tests for when the range's value type doesn't match the container's
// value type.

template <class X>
void map_insert_range_test1(X*,
    test::random_generator generator = test::default_generator)
{
    std::cerr<<"map_insert_range_test1\n";

    typedef test::list<
        std::pair<
            BOOST_DEDUCED_TYPENAME X::key_type,
            BOOST_DEDUCED_TYPENAME X::mapped_type
        >
    > list;
    test::random_values<X> v(1000, generator);
    list l(v.begin(), v.end());

    X x; x.insert(l.begin(), l.end());

    test::check_equivalent_keys(x);
}

template <class X>
void map_insert_range_test2(X*,
    test::random_generator generator = test::default_generator)
{
    std::cerr<<"map_insert_range_test2\n";

    typedef test::list<
        std::pair<BOOST_DEDUCED_TYPENAME X::key_type const, int>
    > list;
    test::random_values<
        boost::unordered_map<BOOST_DEDUCED_TYPENAME X::key_type, int>
    > v(1000, generator);
    list l(v.begin(), v.end());

    X x; x.insert(l.begin(), l.end());

    test::check_equivalent_keys(x);
}

boost::unordered_set<test::object,
    test::hash, test::equal_to,
    test::allocator<test::object> >* test_set;
boost::unordered_multiset<test::object,
    test::hash, test::equal_to,
    test::allocator<test::object> >* test_multiset;
boost::unordered_map<test::object, test::object,
    test::hash, test::equal_to,
    test::allocator<test::object> >* test_map;
boost::unordered_multimap<test::object, test::object,
    test::hash, test::equal_to,
    test::allocator<test::object> >* test_multimap;

using test::default_generator;
using test::generate_collisions;

UNORDERED_TEST(unique_insert_tests1,
    ((test_set)(test_map))
    ((default_generator)(generate_collisions))
)

UNORDERED_TEST(equivalent_insert_tests1,
    ((test_multiset)(test_multimap))
    ((default_generator)(generate_collisions))
)

UNORDERED_TEST(insert_tests2,
    ((test_set)(test_multiset)(test_map)(test_multimap))
    ((default_generator)(generate_collisions))
)

#if !defined(BOOST_NO_RVALUE_REFERENCES) && !defined(BOOST_NO_VARIADIC_TEMPLATES)
UNORDERED_TEST(unique_emplace_tests1,
    ((test_set)(test_map))
    ((default_generator)(generate_collisions))
)

UNORDERED_TEST(equivalent_emplace_tests1,
    ((test_multiset)(test_multimap))
    ((default_generator)(generate_collisions))
)
#endif

UNORDERED_TEST(map_tests,
    ((test_map))
    ((default_generator)(generate_collisions))
)

UNORDERED_TEST(map_insert_range_test1,
    ((test_map)(test_multimap))
    ((default_generator)(generate_collisions))
)

UNORDERED_TEST(map_insert_range_test2,
    ((test_map)(test_multimap))
    ((default_generator)(generate_collisions))
)

#if !defined(BOOST_NO_0X_HDR_INITIALIZER_LIST) && \
    !defined(BOOST_NO_INITIALIZER_LISTS)

UNORDERED_AUTO_TEST(insert_initializer_list_set)
{
    boost::unordered_set<int> set;
    set.insert({1,2,3,1});
    BOOST_TEST_EQ(set.size(), 3u);
    BOOST_TEST(set.find(1) != set.end());
    BOOST_TEST(set.find(4) == set.end());
}

UNORDERED_AUTO_TEST(insert_initializer_list_multiset)
{
    boost::unordered_multiset<std::string> multiset;
    //multiset.insert({});
    BOOST_TEST(multiset.empty());
    multiset.insert({"a"});
    BOOST_TEST_EQ(multiset.size(), 1u);
    BOOST_TEST(multiset.find("a") != multiset.end());
    BOOST_TEST(multiset.find("b") == multiset.end());
    multiset.insert({"a","b"});
    BOOST_TEST(multiset.size() == 3);
    BOOST_TEST_EQ(multiset.count("a"), 2u);
    BOOST_TEST_EQ(multiset.count("b"), 1u);
    BOOST_TEST_EQ(multiset.count("c"), 0u);
}

UNORDERED_AUTO_TEST(insert_initializer_list_map)
{
    boost::unordered_map<std::string, std::string> map;
    //map.insert({});
    BOOST_TEST(map.empty());
    map.insert({{"a", "b"},{"a", "b"},{"d", ""}});
    BOOST_TEST_EQ(map.size(), 2u);
}

UNORDERED_AUTO_TEST(insert_initializer_list_multimap)
{
    boost::unordered_multimap<std::string, std::string> multimap;
    //multimap.insert({});
    BOOST_TEST(multimap.empty());
    multimap.insert({{"a", "b"},{"a", "b"},{"d", ""}});
    BOOST_TEST_EQ(multimap.size(), 3u);
    BOOST_TEST_EQ(multimap.count("a"), 2u);
}

#endif

}

RUN_TESTS()
