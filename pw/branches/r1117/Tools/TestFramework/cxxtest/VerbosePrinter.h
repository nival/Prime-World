#ifndef __cxxtest__VerbosePrinter_h__
#define __cxxtest__VerbosePrinter_h__

//
// The VerbosePrinter is a simple TestListener that
// just prints "OK" if everything goes well, otherwise
// reports the error in the format of compiler messages.
// The VerbosePrinter uses std::cout
//

#include <cxxtest/Flags.h>

#ifndef _CXXTEST_HAVE_STD
#   define _CXXTEST_HAVE_STD
#endif // _CXXTEST_HAVE_STD

#include <cxxtest/VerboseFormatter.h>
#include <cxxtest/StdValueTraits.h>

#ifdef _CXXTEST_OLD_STD
#   include <iostream.h>
#else // !_CXXTEST_OLD_STD
#   include <iostream>
#endif // _CXXTEST_OLD_STD

namespace CxxTest 
{
    class VerbosePrinter : public VerboseFormatter
    {
    public:
        VerbosePrinter( CXXTEST_STD(ostream) &o = CXXTEST_STD(cout), const char *preLine = "(", const char *postLine = ")" ) :
            VerboseFormatter( new Adapter(o), preLine, postLine ) {}
        virtual ~VerbosePrinter() { delete outputStream(); }

    private:
        class Adapter : public OutputStream
        {
            CXXTEST_STD(ostream) &_o;
        public:
            Adapter( CXXTEST_STD(ostream) &o ) : _o(o) {}
            void flush() { _o.flush(); }
            OutputStream &operator<<( const char *s ) { _o << s; return *this; }
            OutputStream &operator<<( Manipulator m ) { return OutputStream::operator<<( m ); }
            OutputStream &operator<<( unsigned i )
            {
                char s[1 + 3 * sizeof(unsigned)];
                numberToString( i, s );
                _o << s;
                return *this;
            }
        };
    };
}

#endif // __cxxtest__VerbosePrinter_h__
