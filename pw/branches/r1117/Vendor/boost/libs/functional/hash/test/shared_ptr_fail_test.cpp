
// Copyright 2010 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/functional/hash.hpp>
#include <boost/shared_ptr.hpp>

// This should obviously pass if shared_ptr ever supports Boost.Hash.

int main() {
    boost::hash<boost::shared_ptr<int> > hash;
    boost::shared_ptr<int> x(new int(10));
    
    hash(x);
}
