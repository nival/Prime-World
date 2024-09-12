#pragma once

#include "../CxxTest/TestListener.h"
#include "LoggerStream.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace CxxTest
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CXmlListener : public TestListener
{
	List suites;

	unsigned total;
	unsigned failed;

	char fileName[MAX_PATH];
	char worldName[MAX_PATH];

public:
	CXmlListener( const char* _fileName, const char *_worldName ) : total( 0 ), failed( 0 ) { suites.initialize(); strcpy_s( fileName, _fileName ); strcpy_s( worldName, _worldName );  }
	~CXmlListener();

	void enterWorld( const WorldDescription &desc );
	void enterSuite( const SuiteDescription &desc );
	void enterTest( const TestDescription &desc );
	void trace( const char *file, unsigned line, const char *expression );
	void warning( const char *file, unsigned line, const char *expression );
	void failedTest( const char *file, unsigned line, const char *expression );
	void failedAssert( const char *file, unsigned line, const char *expression );
	void failedAssertEquals( const char *file, unsigned line, const char *xStr, const char *yStr, const char *x, const char *y );
	void failedAssertSameData( const char *file, unsigned line, const char *xStr, const char *yStr, const char *sizeStr, const void *x, const void *y, unsigned size );
	void failedAssertDelta( const char *file, unsigned line, const char *xStr, const char *yStr, const char *dStr, const char *x, const char *y, const char *d );
	void failedAssertDiffers( const char *file, unsigned line, const char *xStr, const char *yStr, const char *value );
	void failedAssertLessThan( const char *file, unsigned line, const char *xStr, const char *yStr, const char *x, const char *y );
	void failedAssertLessThanEquals( const char *file, unsigned line, const char *xStr, const char *yStr, const char *x, const char *y );
	void failedAssertPredicate( const char *file, unsigned line, const char *predicate, const char *xStr, const char *x );
	void failedAssertRelation( const char *file, unsigned line, const char *relation, const char *xStr, const char *yStr, const char *x, const char *y );
	void failedAssertThrows( const char *file, unsigned line, const char *expression, const char *type, bool otherThrown );
	void failedAssertThrowsNot( const char *file, unsigned line, const char *expression );
	void leaveTest( const TestDescription &desc );
	void leaveSuite( const SuiteDescription &desc );
	void leaveWorld( const WorldDescription &desc );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}