// weighted_die.cpp
//
// Copyright (c) 2009
// Steven Watanabe
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//[weighted_die
/*`
    For the source of this example see
    [@boost://libs/random/example/weighted_die.cpp weighted_die.cpp].
*/
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <vector>
#include <algorithm>
#include <numeric>

boost::mt19937 gen;

/*`
   This time, instead of a fair die, the probability of
   rolling a 1 is 50% (!).  The other five faces are all
   equally likely.
*/
static const double probabilities[] = {
    0.5, 0.1, 0.1, 0.1, 0.1, 0.1
};

/*`
  Now define a function that simulates rolling this die.
  Note that the C++0x library contains a `discrete_distribution`
  class which would be a better way to do this.
*/
int roll_weighted_die() {
    std::vector<double> cumulative;
    std::partial_sum(&probabilities[0], &probabilities[0] + 6,
                     std::back_inserter(cumulative));
    boost::uniform_real<> dist(0, cumulative.back());
    boost::variate_generator<boost::mt19937&, boost::uniform_real<> > die(gen, dist);
    /*<< Find the position within the sequence and add 1
         (to make sure that the result is in the range [1,6]
         instead of [0,5])
    >>*/
    return (std::lower_bound(cumulative.begin(), cumulative.end(), die()) - cumulative.begin()) + 1;
}

//]

#include <iostream>

int main() {
    for(int i = 0; i < 10; ++i) {
        std::cout << roll_weighted_die() << std::endl;
    }
}
