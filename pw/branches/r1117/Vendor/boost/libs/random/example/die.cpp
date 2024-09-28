// die.cpp
//
// Copyright (c) 2009
// Steven Watanabe
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//[die
/*`
    For the source of this example see
    [@boost://libs/random/example/die.cpp die.cpp].
    First we include the headers we need for __mt19937
    and __uniform_int.
*/
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

/*`
  We use __mt19937 with the default seed as a source of
  randomness.  The numbers produced will be the same
  every time the program is run.  One common method to
  change this is to seed with the current time (`std::time(0)`
  defined in ctime).
*/
boost::mt19937 gen;
/*`
  [note We are using a /global/ generator object here.  This
  is important because we don't want to create a new [prng
  pseudo-random number generator] at every call]
*/
/*`
  Now we can define a function that simulates an ordinary
  six-sided die.
*/
int roll_die() {
    /*<< __mt19937 produces integers in the range [0, 2[sup 32]-1].
        However, we want numbers in the range [1, 6].  The distribution
        __uniform_int performs this transformation.
        [warning Contrary to common C++ usage __uniform_int
        does not take a /half-open range/.  Instead it takes a /closed range/.
        Given the parameters 1 and 6, __uniform_int can
        can produce any of the values 1, 2, 3, 4, 5, or 6.]
    >>*/
    boost::uniform_int<> dist(1, 6);
    /*<< __variate_generator combines a generator with a distribution.
        [important We pass [classref boost::mt19937 boost::mt19937&] to
        __variate_generator instead of just [classref boost::mt19937]
        (note the reference).  Without the reference, __variate_generator
        would make a copy of the generator and would leave the global
        `gen` unchanged.  Consequently, `roll_die` would produce *the same value*
        every time it was called.]
    >>*/
    boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(gen, dist);
    /*<< A __variate_generator is a function object. >>*/
    return die();
}
//]

#include <iostream>

int main() {
    for(int i = 0; i < 10; ++i) {
        std::cout << roll_die() << std::endl;
    }
}
