#ifndef __cxxtest__ErrorFormatter_h__
#define __cxxtest__ErrorFormatter_h__

//
// The ErrorFormatter is a TestListener that
// prints reports of the errors to an output
// stream.  Since we cannot rely ou the standard
// iostreams, this header defines a base class
// analogout to std::ostream.
//

#include <cxxtest/TestRunner.h>
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/ValueTraits.h>
#include <iostream>

namespace CxxTest
{
    class OutputStream
    {
    public:
        virtual ~OutputStream() {}
        virtual void flush() {};
        virtual OutputStream &operator<<( unsigned /*number*/ ) { return *this; }
        virtual OutputStream &operator<<( const char * /*string*/ ) { return *this; }

        typedef void (*Manipulator)( OutputStream & );
        
        virtual OutputStream &operator<<( Manipulator m ) { m( *this ); return *this; }
        static void endl( OutputStream &o ) { (o << "\n").flush(); }
    };

    class ErrorFormatter : public TestListener
    {
    public:
        ErrorFormatter( OutputStream *o, const char *preLine = ":", const char *postLine = "" ) :
            _dotting( true ),
            _reported( false ),
            _o(o),
            _preLine(preLine),
            _postLine(postLine)
        {
        }

        int run( const std::vector<std::string>& params, int runCount = 1 )
        {
            for (int i=0;i<runCount;++i)
            {
                TestRunner::runAllTests( params, *this );
            }
            return tracker().failedTests();
        }

        void enterWorld( const WorldDescription & /*desc*/ )
        {
          char running[2156];
          char s[WorldDescription::MAX_STRLEN_TOTAL_TESTS];
          sprintf_s( running, "Running %s%s", tracker().world().strTotalTests( s ),tracker().world().numTotalTests() == 1 ? " test" : " tests" );
          OutputDebugString( running );
            (*_o) << "Running " << totalTests;
            _o->flush();
            _dotting = true;
            _reported = false;
        }

        static void totalTests( OutputStream &o )
        {
            char s[WorldDescription::MAX_STRLEN_TOTAL_TESTS];
            const WorldDescription &wd = tracker().world();
            o << wd.strTotalTests( s ) << (wd.numTotalTests() == 1 ? " test" : " tests");
        }

        void enterSuite( const SuiteDescription & )
        {
            _reported = false;
        }

        void enterTest( const TestDescription & )
        {
            _reported = false;
        }

        void leaveTest( const TestDescription & )
        {
            if ( !tracker().testFailed() ) 
            {
              OutputDebugString( "." );
              ((*_o) << ".").flush();
              _dotting = true;
            }
        }

        void leaveWorld( const WorldDescription &desc )
        {
          if ( !tracker().failedTests() ) 
          {
            OutputDebugString( "OK!" );
            (*_o) << "OK!" << endl;
            return;
          }
          newLine();

          char message[1256];
          char s[WorldDescription::MAX_STRLEN_TOTAL_TESTS];

          sprintf_s( message, "Failed %d of %s",tracker().failedTests(),tracker().world().strTotalTests( s ));
          OutputDebugString(message);
          (*_o) << "Failed " << tracker().failedTests() << " of " << totalTests << endl;

          unsigned numPassed = desc.numTotalTests() - tracker().failedTests();

          sprintf_s( message, "Success rate: %d",(numPassed * 100 / desc.numTotalTests()));
          OutputDebugString(message);
          (*_o) << "Success rate: " << (numPassed * 100 / desc.numTotalTests()) << "%" << endl;
        }

        void trace( const char *file, unsigned line, const char *expression )
        {
            stop( file, line ) << "Trace: " <<
                expression << endl;
            char message[1256];
            sprintf_s( message, "Trace: %s\n",expression);
            OutputDebugString(message);
        }

        void trace2( const char *file, unsigned line, const char *expression )
        {
            std::cout<< "File: " << file << " line(" << line << ") " << "Trace: " <<
                expression << endl;
            char message[1256];
            sprintf_s( message, "File: %s line(%d) Trace: %s\n",file,line,expression);
            OutputDebugString(message);
        }

        void warning( const char *file, unsigned line, const char *expression )
        {
            stop( file, line ) << "Warning: " <<
                expression << endl;
            char message[1256];
            sprintf_s( message, "Warning: %s\n",expression);
            OutputDebugString(message);
        }

        void failedTest( const char *file, unsigned line, const char *expression )
        {
            stop( file, line ) << "Error: Test failed: " <<
                expression << endl;
            char message[1256];
            sprintf_s( message, "Error: Test failed: %s\n",expression);
            OutputDebugString(message);
        }

        void failedAssert( const char *file, unsigned line, const char *expression )
        {
            stop( file, line ) << "Error: Assertion failed: " <<
                expression << endl;
            char message[1256];
            sprintf_s( message, "Error: Assertion failed: %s\n",expression);
            OutputDebugString(message);
        }

        void failedAssertEquals( const char *file, unsigned line,
                                 const char *xStr, const char *yStr,
                                 const char *x, const char *y )
        {
            stop( file, line ) << "Error: Expected (" <<
                xStr << " == " << yStr << "), found (" <<
                x << " != " << y << ")" << endl;
            char message[1256];
            sprintf_s( message, "Error: Expected (%s == %s), found (%s != %s)\n",xStr,yStr,x,y);
            OutputDebugString(message);
        }

        void failedAssertSameData( const char *file, unsigned line,
                                   const char *xStr, const char *yStr,
                                   const char *sizeStr, const void *x,
                                   const void *y, unsigned size )
        {
            stop( file, line ) << "Error: Expected " << sizeStr << " (" << size << ") bytes to be equal at (" <<
                xStr << ") and (" << yStr << "), found:" << endl;
            dump( x, size );
            (*_o) << "     differs from" << endl;
            dump( y, size );

            char message[1256];
            sprintf_s( message, "Error: Expected %s (%d) bytes bytes to be equal at (%s) and (%s), found:\n",sizeStr,size,xStr,yStr);
            OutputDebugString(message);

        }

        void failedAssertDelta( const char *file, unsigned line,
                                const char *xStr, const char *yStr, const char *dStr,
                                const char *x, const char *y, const char *d )
        {
            stop( file, line ) << "Error: Expected (" <<
                xStr << " == " << yStr << ") up to " << dStr << " (" << d << "), found (" <<
                x << " != " << y << ")" << endl;

            char message[1256];
            sprintf_s( message, "Error: Expected (%s == %s) up to %s (%s), found (%s != %s)\n",xStr,yStr,dStr,d,x,y);            
            OutputDebugString(message);
        }

        void failedAssertDiffers( const char *file, unsigned line,
                                  const char *xStr, const char *yStr,
                                  const char *value )
        {
            stop( file, line ) << "Error: Expected (" <<
                xStr << " != " << yStr << "), found (" <<
                value << ")" << endl;

            char message[1256];
            sprintf_s( message, "Error: Expected (%s != %s), found (%s)\n",xStr,yStr,value);            
            OutputDebugString(message);
        }

        void failedAssertLessThan( const char *file, unsigned line,
                                   const char *xStr, const char *yStr,
                                   const char *x, const char *y )
        {
            stop( file, line ) << "Error: Expected (" <<
                xStr << " < " << yStr << "), found (" <<
                x << " >= " << y << ")" << endl;

            char message[1256];
            sprintf_s( message, "Error: Expected (%s < %s), found (%s >= %s)\n",xStr,yStr,x,y);            
            OutputDebugString(message);
        }

        void failedAssertLessThanEquals( const char *file, unsigned line,
                                         const char *xStr, const char *yStr,
                                         const char *x, const char *y )
        {
            stop( file, line ) << "Error: Expected (" <<
                xStr << " <= " << yStr << "), found (" <<
                x << " > " << y << ")" << endl;
            char message[1256];
            sprintf_s( message, "Error: Expected (%s <= %s), found (%s > %s)\n",xStr,yStr,x,y);            
            OutputDebugString(message);
        }

        void failedAssertRelation( const char *file, unsigned line,
                                   const char *relation, const char *xStr, const char *yStr,
                                   const char *x, const char *y )
        {
            stop( file, line ) << "Error: Expected " << relation << "( " <<
                xStr << ", " << yStr << " ), found !" << relation << "( " << x << ", " << y << " )" << endl;
            char message[1256];
            sprintf_s( message, "Error: Expected %s( %s, %s ), found !%s( %s, %s )\n",relation,xStr,yStr,relation,x,y);
            OutputDebugString(message);
        }

        void failedAssertPredicate( const char *file, unsigned line,
                                    const char *predicate, const char *xStr, const char *x )
        {
            stop( file, line ) << "Error: Expected " << predicate << "( " <<
                xStr << " ), found !" << predicate << "( " << x << " )" << endl;
            char message[1256];
            sprintf_s( message, "Error: Expected %s( %s ), found !%s( %s )\n",predicate,xStr,predicate,x);
            OutputDebugString(message);
        }

        void failedAssertThrows( const char *file, unsigned line,
                                 const char *expression, const char *type,
                                 bool otherThrown )
        {
            stop( file, line ) << "Error: Expected (" << expression << ") to throw (" <<
                type << ") but it " << (otherThrown ? "threw something else" : "didn't throw") <<
                endl;
            char message[1256];
            sprintf_s( message, "Error: Expected (%s) to throw (%s) but it %s\n",expression,type,(otherThrown ? "threw something else" : "didn't throw"));
            OutputDebugString(message);
        }

        void failedAssertThrowsNot( const char *file, unsigned line, const char *expression )
        {
            stop( file, line ) << "Error: Expected (" << expression << ") not to throw, but it did" <<
                endl;
            char message[1256];
            sprintf_s( message, "Error: Expected (%s) not to throw, but it did\n",expression);
            OutputDebugString(message);
        }

    protected:
        OutputStream *outputStream() const
        {
            return _o;
        }

    private:
        ErrorFormatter( const ErrorFormatter & );
        ErrorFormatter &operator=( const ErrorFormatter & );
        
        OutputStream &stop( const char *file, unsigned line )
        {
            newLine();
            reportTest();

            char message[1256];
            sprintf_s( message, "%s%s%d%s: ",file,_preLine,line,_postLine);
            OutputDebugString(message);

            return (*_o) << file << _preLine << line << _postLine << ": ";
        }

        void newLine( void )
        {
            if ( _dotting ) {
                (*_o) << endl;
                _dotting = false;
            }
        }

        void reportTest( void )
        {
            if( _reported )
                return;
            (*_o) << "In " << tracker().suite().suiteName() << "::" << tracker().test().testName() << ":" << endl;
            _reported = true;
        }

        void dump( const void *buffer, unsigned size )
        {
            if ( !buffer )
                dumpNull();
            else
                dumpBuffer( buffer, size );
        }

        void dumpNull()
        {
            (*_o) << "   (null)" << endl;
        }
        
        void dumpBuffer( const void *buffer, unsigned size )
        {
            unsigned dumpSize = size;
            if ( maxDumpSize() && dumpSize > maxDumpSize() )
                dumpSize = maxDumpSize();

            const unsigned char *p = (const unsigned char *)buffer;
            (*_o) << "   { ";
            for ( unsigned i = 0; i < dumpSize; ++ i )
                (*_o) << byteToHex( *p++ ) << " ";
            if ( dumpSize < size )
                (*_o) << "... ";
            (*_o) << "}" << endl;
        }

        static void endl( OutputStream &o )
        {
            OutputStream::endl( o );
        }

        bool _dotting;
        bool _reported;
        OutputStream *_o;
        const char *_preLine;
        const char *_postLine;
    };
};

#endif // __cxxtest__ErrorFormatter_h__
