#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "DllTestCollector.h"
#include "Log.h"
#include "CommandLineParser.h"
#include "FilePath.h"
#include "ErrorFormatter.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main( int argc, char *argv[] )
{
	CCommandLineParser commandLine;
	
	commandLine.RegisterAction( "help", "Show help screen" );
	commandLine.RegisterOption( "dir", "directory", "Specify additional directory for lookind dependend dlls" );
	commandLine.RegisterOption( "run", "suite::[test]", "Specify test suite and test (optinal) to run" );
	commandLine.RegisterOption( "xml", "fileName", "Output results as XML instead console" );

	const bool bResult = commandLine.ProcessCommandLine();
	if ( !bResult )
	{
		return -1;
	}
	else if ( commandLine.GetParams().size() != 1 || commandLine.GetAction() == "help" )
	{
		commandLine.ShowHelp( "Run unit-tests utility. (C) Nival Network, 2008", "CxxRunner.exe <test_library>", true );
		return 0;
	}

	CxxTest::CDllTestCollector testCollector( commandLine.GetParams()[0].c_str() );
	if ( !testCollector.initialize() )
		return -1;

	const string &szAdditionalDir = commandLine.GetOption( "dir", string() );
	if ( !szAdditionalDir.empty() )
		testCollector.SetAdditionalDir( szAdditionalDir.c_str() );
	const string &szTestsToRun = commandLine.GetOption( "run", string() );
	if ( szTestsToRun.empty() )
		testCollector.activateAllTests();
	else
	{
		const string::size_type pos = szTestsToRun.find( "::" );
		if ( pos == string::npos )
			testCollector.leaveOnly( szTestsToRun.c_str(), 0 );
		else
		{
			const string szSuiteToRun = szTestsToRun.substr( 0, pos - 1 );
			const string szTestToRun = szTestsToRun.substr( pos + 1 );
			testCollector.leaveOnly( szSuiteToRun.c_str(), szTestToRun.c_str() );
		}
	}
	testCollector.run( commandLine.GetOption( "xml", string() ).c_str(), commandLine.GetParams()[0].c_str() );

	return CxxTest::TestTracker::tracker().failedTests();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
