#include "CommandLineParser.h"
#include <windows.h>
#include <shellapi.h>
#include <algorithm>
#include "Log.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCommandLineParser::RegisterAction( const string &szName, const string &szDescription )
{
	char szBuffer[256];
	strcpy_s( szBuffer, szName.c_str() );
	CharLower( szBuffer );

	if ( actions.find( szBuffer ) == actions.end() )
		actions[szBuffer] = SDefaultArgument( szDescription );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCommandLineParser::RegisterOption( const string &szName, const string &szDescription )
{
	char szBuffer[256];
	strcpy_s( szBuffer, szName.c_str() );
	CharLower( szBuffer );

	if ( boolOptions.find( szBuffer ) == boolOptions.end() )
		boolOptions[szBuffer] = SValuedArgument<bool>( szDescription, false );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCommandLineParser::RegisterOption( const string &szName, const string &szParamDescription, const string &szDescription )
{
	char szBuffer[256];
	strcpy_s( szBuffer, szName.c_str() );
	CharLower( szBuffer );

	if ( stringOptions.find( szBuffer ) == stringOptions.end() )
		stringOptions[szBuffer] = SValuedArgument<string>( szParamDescription, szDescription, "" );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const bool CCommandLineParser::GetOption( const string &szName, bool bDefault ) const
{
	hash_map<string, SValuedArgument<bool>>::const_iterator pos = boolOptions.find( szName );
	if ( pos == boolOptions.end() || !pos->second.bDefined )
		return bDefault;
	else
		return pos->second.value;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string &CCommandLineParser::GetOption( const string &szName, const string &szDefault ) const
{
	hash_map<string, SValuedArgument<string>>::const_iterator pos = stringOptions.find( szName );
	if ( pos == stringOptions.end() || !pos->second.bDefined )
		return szDefault;
	else
		return pos->second.value;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const bool CCommandLineParser::ProcessCommandLine()
{
	int nArgs = 0;
	const LPWSTR *args = CommandLineToArgvW( GetCommandLineW(), &nArgs );
	
	char szBuffer[MAX_PATH];
	WideCharToMultiByte( CP_ACP, WC_COMPOSITECHECK, args[0], -1, szBuffer, sizeof( szBuffer ), NULL, NULL );
	szExecutable = szBuffer;
	
	for ( int i = 1; i < nArgs; ++i )
	{
		WideCharToMultiByte( CP_ACP, WC_COMPOSITECHECK, args[i], -1, szBuffer, sizeof( szBuffer ), NULL, NULL );

		const string szArg = szBuffer;
		CharLower( szBuffer );
		const string szLowArg = szBuffer;

		if ( szLowArg.size() > 2 && szLowArg[0] == '-' && szLowArg[1] == '-' )
		{
			const size_t nEqualPos = szLowArg.find( '=' );
			const string szOption = szLowArg.substr( 2, nEqualPos == string::npos ? string::npos : nEqualPos - 2 );
			if ( actions.find( szOption ) != actions.end() )
			{
				if ( nEqualPos != string::npos )
				{
					log( LEVEL_CRITICAL ) << "Invalid argument \"" << szArg << "\"" << endl;
					return false;
				}
				if ( GetAction().size() != 0 )
				{
					log( LEVEL_CRITICAL ) << "Invalid argument \"" << szArg << "\". Action \"" << GetAction() << "\" already specified" << endl;
					return false;
				}

				szAction = szOption;
			}
			else
			{
				hash_map<string, SValuedArgument<bool>>::iterator posBool = boolOptions.find( szOption );
				if ( posBool != boolOptions.end() )
				{
					if ( nEqualPos != string::npos )
					{
						log( LEVEL_CRITICAL ) << "Invalid argument \"" << szArg << "\"" << endl;
						return false;
					}
					posBool->second.value = true;
					posBool->second.bDefined = true;
				}
				else
				{
					hash_map<string, SValuedArgument<string>>::iterator posString = stringOptions.find( szOption );
					if ( posString == stringOptions.end() || nEqualPos == string::npos )
					{
						log( LEVEL_CRITICAL ) << "Invalid argument \"" << szArg << "\"" << endl;
						return false;
					}
					string szValue = szArg.substr( nEqualPos + 1 );
					posString->second.value = szValue;
					posString->second.bDefined = true;
				}
			}
		}
		else
			params.push_back( szArg );
	}

	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const void CCommandLineParser::ShowHelp( const string &szHeader, const string &szUsage, const bool bHasDefaultAction ) const
{
	printf( "%s\n", szHeader.c_str() );
	const string szActionsHelp = actions.empty() ? "" : bHasDefaultAction ? " [<action>]" : " <action>";
	const string szOptionsHelp = boolOptions.empty() && stringOptions.empty() ? "" : " [<options>]";
	printf( "Usage: %s%s%s\n", szUsage.c_str(), szActionsHelp.c_str(), szOptionsHelp.c_str() );
	if ( !actions.empty() )
	{
		printf( "Actions:\n" );
		vector<string> sortedActions;
		for ( hash_map<string, SDefaultArgument>::const_iterator it = actions.begin(); it != actions.end(); ++it )
			sortedActions.push_back( it->first );
		sort( sortedActions.begin(), sortedActions.end() );
		for ( vector<string>::const_iterator it = sortedActions.begin(); it != sortedActions.end(); ++it )
		{
			hash_map<string, SDefaultArgument>::const_iterator pos = actions.find( *it );
			printf( "  --%s : %s\n", it->c_str(), pos->second.szDescription.c_str() );
		}
	}
	if ( !boolOptions.empty() || !stringOptions.empty() )
	{
		printf( "Options:\n" );
		vector<string> sortedOptions;
		for ( hash_map<string, SValuedArgument<bool>>::const_iterator it = boolOptions.begin(); it != boolOptions.end(); ++it )
			sortedOptions.push_back( it->first );
		for ( hash_map<string, SValuedArgument<string>>::const_iterator it = stringOptions.begin(); it != stringOptions.end(); ++it )
			sortedOptions.push_back( it->first );
		sort( sortedOptions.begin(), sortedOptions.end() );
		for ( vector<string>::const_iterator it = sortedOptions.begin(); it != sortedOptions.end(); ++it )
		{
			hash_map<string, SValuedArgument<bool>>::const_iterator pos = boolOptions.find( *it );
			if ( pos == boolOptions.end() )
			{
				hash_map<string, SValuedArgument<string>>::const_iterator posString = stringOptions.find( *it );
				printf( " --%s=<%s> : %s\n", it->c_str(), posString->second.szParamDescription.c_str(), posString->second.szDescription.c_str() );
			}
			else
				printf( "  --%s : %s\n", it->c_str(), pos->second.szDescription.c_str() );
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
