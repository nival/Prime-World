#include "XmlListener.h"

#include "FileGuard.h"
#include "ErrorFormatter.h"
#include "Log.h"

#include <stdarg.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TestResult : public CxxTest::Link
{
	char name[MAX_PATH];
	unsigned time;

	char failFile[MAX_PATH];
	unsigned failLine;
	char failMessage[512];

public:
	TestResult( const char* _name ) { strcpy_s( name, _name ); failFile[0] = 0; failLine = 0; failMessage[0] = 0; time = 0; }
	
	void Start() { time = ::GetTickCount(); }
	void Fail( const char* file, unsigned line, const char* message ) { if ( IsFailed() ) return; strcpy_s( failFile, file ); failLine = line; strcpy_s( failMessage, message ); }
	void Finish() { time = ::GetTickCount() - time; }

	const char* Name() const { return name; }

	bool IsFailed() const { return failMessage[0] != 0; }

	const char* FailMessage() const { return failMessage; }
	const char* FailFile() const { return failFile; }
	unsigned FailLine() const { return failLine; }
	unsigned Time() const { return time; }

  bool setUp() { return true; }
	bool tearDown() { return true; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SuiteResult : public CxxTest::Link
{
	CxxTest::List tests;
	TestResult* activeTest;

	unsigned total;
	unsigned failed;
	unsigned time;

	char name[MAX_PATH];
public:
	SuiteResult( const char* _name ) : total( 0 ), failed( 0 ), time( 0 ) { strcpy_s( name, _name ); tests.initialize(); }
	~SuiteResult()
	{
		for ( TestResult* tr = ((TestResult*)tests.head()); tr != 0; )
		{
			TestResult *pTemp = tr;
			tr = ((TestResult*)tr->next());
			delete pTemp;
		}
	}

	void Start( const char* _name ) { activeTest = new TestResult( _name ); activeTest->attach( tests ); activeTest->Start(); }
	void Fail( const char* _file, unsigned _line, const char* message ) { if ( activeTest ) activeTest->Fail( _file, _line, message ); }
	void Finish()
	{
		if ( activeTest )
		{
			activeTest->Finish();
			++total;
			if ( activeTest->IsFailed() )
				++failed;
			time += activeTest->Time();
		}
		activeTest = 0;
	}

	const TestResult* Tests() const { return ((TestResult*)tests.head()); }
	const TestResult* ActiveTest() const { return activeTest; }

	const char* Name() const { return name; }

	unsigned Total() const { return total; }
	unsigned Failed() const { return failed; }
	unsigned Time() const { return time; }

  bool setUp() { return true; }
	bool tearDown() { return true; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *StrFmt( const char *pszFormat, ... )
{
	static char charBuff[16384] = { '\0' };
	va_list va;
	va_start( va, pszFormat );
	_vsnprintf_s( charBuff, 16384 - 1, pszFormat, va );
	va_end( va );
	return charBuff;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace CxxTest
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CXmlListener::~CXmlListener()
{
	for ( SuiteResult* sr = ((SuiteResult*)suites.head()); sr != 0; )
	{
		SuiteResult *pTemp = sr;
		sr = ((SuiteResult*)sr->next());
		delete pTemp;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlListener::enterWorld( const WorldDescription &desc )
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlListener::enterSuite( const SuiteDescription &desc )
{
	SuiteResult* suite = new SuiteResult( desc.suiteName() );
	suite->attach( suites );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlListener::enterTest( const TestDescription &desc )
{
	((SuiteResult*)(suites.tail()))->Start( desc.testName() );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlListener::trace( const char *file, unsigned line, const char *expression )
{

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlListener::warning( const char *file, unsigned line, const char *expression )
{

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlListener::failedTest( const char *file, unsigned line, const char *expression )
{
	((SuiteResult*)(suites.tail()))->Fail( file, line, StrFmt( "%s", expression ) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlListener::failedAssert( const char *file, unsigned line, const char *expression )
{
	((SuiteResult*)(suites.tail()))->Fail( file, line, StrFmt( "%s", expression ) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlListener::failedAssertEquals( const char *file, unsigned line, const char *xStr, const char *yStr, const char *x, const char *y )
{
	((SuiteResult*)(suites.tail()))->Fail( file, line, StrFmt( "Expected \"%s\" == \"%s\", found \"%s\" != \"%s\"", xStr, yStr, x, y ) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlListener::failedAssertSameData( const char *file, unsigned line, const char *xStr, const char *yStr, const char *sizeStr, const void *x, const void *y, unsigned size )
{
	//stop( file, line ) << "error : expected" << sizeStr << " (" << size << ") bytes to be equal at (" << xStr << ") and (" << yStr << "), found:\n"; 
	//dump( x, size );
	//GetLog() << "differs from\n";
	//dump( y, size );
	//GetLog() << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlListener::failedAssertDelta( const char *file, unsigned line, const char *xStr, const char *yStr, const char *dStr, const char *x, const char *y, const char *d )
{
	((SuiteResult*)(suites.tail()))->Fail( file, line, StrFmt( "Expected \"%s\" == \"%s\" up to %s (\"%s\"), found \"%s\" != \"%s\"", xStr, yStr, dStr, d, x, y ) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlListener::failedAssertDiffers( const char *file, unsigned line, const char *xStr, const char *yStr, const char *value )
{
  //stop( file, line ) << "error : expected (" << xStr << " != " << yStr << "), found (" << value << ")" << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlListener::failedAssertLessThan( const char *file, unsigned line, const char *xStr, const char *yStr, const char *x, const char *y )
{
  //stop( file, line ) << "error : expected (" << xStr << " < " << yStr << "), found (" << x << " >= " << y << ")" << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlListener::failedAssertLessThanEquals( const char *file, unsigned line, const char *xStr, const char *yStr, const char *x, const char *y )
{
  //stop( file, line ) << "error : expected (" << xStr << " <= " << yStr << "), found (" << x << " > " << y << ")" << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlListener::failedAssertPredicate( const char *file, unsigned line, const char *predicate, const char *xStr, const char *x )
{
  //stop( file, line ) << "error: expected " << predicate << "( " << xStr << " ), found !" << predicate << "( " << x << " )" << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlListener::failedAssertRelation( const char *file, unsigned line, const char *relation, const char *xStr, const char *yStr, const char *x, const char *y )
{
  //stop( file, line ) << "error: expected " << relation << "( " << xStr << ", " << yStr << " ), found !" << relation << "( " << x << ", " << y << " )" << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlListener::failedAssertThrows( const char *file, unsigned line, const char *expression, const char *type, bool otherThrown )
{
  //stop( file, line ) << "error: expected (" << expression << ") to throw (" << type << ") but it " << (otherThrown ? "threw something else" : "didn't throw") << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlListener::failedAssertThrowsNot( const char *file, unsigned line, const char *expression )
{
  //stop( file, line ) << "Error: Expected (" << expression << ") not to throw, but it did" << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlListener::leaveTest( const TestDescription &desc )
{
	++total;
	if ( ((SuiteResult*)(suites.tail()))->ActiveTest()->IsFailed() )
		++failed;
	((SuiteResult*)(suites.tail()))->Finish();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlListener::leaveSuite( const SuiteDescription &desc )
{

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlListener::leaveWorld( const WorldDescription &desc )
{
	NHelpers::CFileGuard file( fileName, true );
	if ( !file.IsValid() )
	{
		log( LEVEL_CRITICAL ) << "Cannot create file \"" << fileName << "\". " << NHelpers::GetLastError() << endl;
		return;
	}

	file.WriteString( "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n" );
	file.WriteString( StrFmt( "<test-results name=\"%s\" total=\"%d\" failures=\"%d\">\n", worldName, total, failed ) );
	for ( SuiteResult* sr = ((SuiteResult*)suites.head()); sr != 0; sr = ((SuiteResult*)sr->next()) )
	{
		file.WriteString( StrFmt( "  <test-suite name=\"%s\" success=\"%s\" time=\"%.3f\">\n", sr->Name(), ( sr->Failed() > 0 ) ? "False" : "True", (float)(sr->Time()) / 1000.0f ) );
		file.WriteString( "    <results>\n" );
		
		for ( TestResult* tr = ((TestResult*)sr->Tests()); tr != 0; tr = ((TestResult*)tr->next()) )
		{
			file.WriteString( StrFmt( "      <test-case name=\"%s::%s\" success=\"%s\" time=\"%.3f\"", sr->Name(), tr->Name(), ( tr->IsFailed() ? "False" : "True" ), (float)(tr->Time()) / 1000.0f ) );
			if ( !tr->IsFailed() )
				file.WriteString( "/>\n" );
			else
			{
				file.WriteString( ">\n" );
				file.WriteString( "        <failure>\n" );
				file.WriteString( "          <message><![CDATA[" );
				file.WriteString( tr->FailMessage() );
				file.WriteString( "\n]]</message>\n" );
				file.WriteString( "          <stack-trace><![CDATA[" );
				file.WriteString( StrFmt( "%s (%d)", tr->FailFile(), tr->FailLine() ) );
				file.WriteString( "\n]]</stack-trace>\n" );
				file.WriteString( "        </failure>\n" );
				file.WriteString( "      </test-case>\n" );
			}
		}
		
		file.WriteString( "    </results>\n" );
		file.WriteString( "  </test-suite>\n" );
	}
	file.WriteString( "</test-results>\n" );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}