#include "LogListener.h"
#include "Log.h"
#include "TestTracker.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const unsigned int maxDumpSize = 16;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void dump( const void *data, const unsigned size )
{
	if ( !data )
	{
		GetLog() << "(null)";
	}
	else
	{
		const char *p = (const char *)data;
		for ( unsigned i = 0; i < size && i < maxDumpSize; ++i )
		{
			if ( i > 0 )
			{
				GetLog() << " ";
			}
			GetLog() << *p++;
		}
		if ( size > maxDumpSize )
			GetLog() << "... ";
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static NLogg::CLoggerStream &fileLine( const char *file, unsigned line )
{
	return GetLog() << file << "(" << line << ") : ";
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace CxxTest
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NLogg::CLoggerStream &CLogListener::stop( const char *file, unsigned line )
{
	if ( !bTestReported )
	{
		log( LEVEL_MESSAGE ) << TestTracker::tracker().suite().suiteName() << "::" << TestTracker::tracker().test().testName() << endl;
		bTestReported = true;
	}
	GetLog().Lock( file, line, LEVEL_CRITICAL );
	return fileLine( file, line );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLogListener::enterWorld( const WorldDescription &desc )
{
	log( LEVEL_MESSAGE ) << "Running " << desc.numTotalTests() << " test(s) ..." << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLogListener::enterSuite( const SuiteDescription &desc )
{
	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLogListener::enterTest( const TestDescription &desc )
{
	bTestReported = false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLogListener::trace( const char *file, unsigned line, const char *expression )
{
	GetLog().Lock( file, line, LEVEL_MESSAGE );
	fileLine( file, line ) << expression << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLogListener::warning( const char *file, unsigned line, const char *expression )
{
	GetLog().Lock( file, line, LEVEL_MESSAGE );
	fileLine( file, line ) << "warning: " << expression << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLogListener::failedTest( const char *file, unsigned line, const char *expression )
{
	stop( file, line ) << "error (test failed): " << expression << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLogListener::failedAssert( const char *file, unsigned line, const char *expression )
{
	stop( file, line ) << "error (assertion failed): " << expression << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLogListener::failedAssertEquals( const char *file, unsigned line, const char *xStr, const char *yStr, const char *x, const char *y )
{
	stop( file, line ) << "error : expected (" << xStr << " == " << yStr << "), found (" << x << "!=" << y << ")" << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLogListener::failedAssertSameData( const char *file, unsigned line, const char *xStr, const char *yStr, const char *sizeStr, const void *x, const void *y, unsigned size )
{
	stop( file, line ) << "error : expected" << sizeStr << " (" << size << ") bytes to be equal at (" << xStr << ") and (" << yStr << "), found:\n"; 
	dump( x, size );
	GetLog() << "differs from\n";
	dump( y, size );
	GetLog() << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLogListener::failedAssertDelta( const char *file, unsigned line, const char *xStr, const char *yStr, const char *dStr, const char *x, const char *y, const char *d )
{
	stop( file, line ) << "error : expected (" <<	xStr << " == " << yStr << ") up to " << dStr << " (" << d << "), found (" << x << " != " << y << ")" << endl; }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLogListener::failedAssertDiffers( const char *file, unsigned line, const char *xStr, const char *yStr, const char *value )
{
  stop( file, line ) << "error : expected (" << xStr << " != " << yStr << "), found (" << value << ")" << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLogListener::failedAssertLessThan( const char *file, unsigned line, const char *xStr, const char *yStr, const char *x, const char *y )
{
  stop( file, line ) << "error : expected (" << xStr << " < " << yStr << "), found (" << x << " >= " << y << ")" << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLogListener::failedAssertLessThanEquals( const char *file, unsigned line, const char *xStr, const char *yStr, const char *x, const char *y )
{
  stop( file, line ) << "error : expected (" << xStr << " <= " << yStr << "), found (" << x << " > " << y << ")" << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLogListener::failedAssertPredicate( const char *file, unsigned line, const char *predicate, const char *xStr, const char *x )
{
  stop( file, line ) << "error: expected " << predicate << "( " << xStr << " ), found !" << predicate << "( " << x << " )" << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLogListener::failedAssertRelation( const char *file, unsigned line, const char *relation, const char *xStr, const char *yStr, const char *x, const char *y )
{
  stop( file, line ) << "error: expected " << relation << "( " << xStr << ", " << yStr << " ), found !" << relation << "( " << x << ", " << y << " )" << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLogListener::failedAssertThrows( const char *file, unsigned line, const char *expression, const char *type, bool otherThrown )
{
  stop( file, line ) << "error: expected (" << expression << ") to throw (" << type << ") but it " << (otherThrown ? "threw something else" : "didn't throw") << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLogListener::failedAssertThrowsNot( const char *file, unsigned line, const char *expression )
{
  stop( file, line ) << "Error: Expected (" << expression << ") not to throw, but it did" << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLogListener::leaveTest( const TestDescription &desc )
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLogListener::leaveSuite( const SuiteDescription &desc )
{
	if ( TestTracker::tracker().suiteFailedTests() == 0 )
	{
		log( LEVEL_MESSAGE ) << TestTracker::tracker().suite().suiteName() << " : ok " << endl;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLogListener::leaveWorld( const WorldDescription &desc )
{

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}