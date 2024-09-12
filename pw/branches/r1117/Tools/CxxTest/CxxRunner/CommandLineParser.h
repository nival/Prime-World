#pragma once

#include <string>
#include <hash_map>
using namespace std;
using namespace stdext;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CCommandLineParser
{
	struct SDefaultArgument
	{
		string szDescription;
		SDefaultArgument() {}
		SDefaultArgument( const string &_szDescription ) : szDescription( _szDescription ) {}
	};
	template<typename T>
	struct SValuedArgument : public SDefaultArgument
	{
		T value;
		bool bDefined;
		string szParamDescription;
		SValuedArgument() : bDefined( false ) {}
		SValuedArgument( const string &_szDescription, const T &_value ) : SDefaultArgument( _szDescription ), value( _value ), bDefined( false ) {}
		SValuedArgument( const string &_szParamDescription, const string &_szDescription, const T &_value )
			: SDefaultArgument( _szDescription ), value( _value ), bDefined( false ), szParamDescription( _szParamDescription ) {}
	};

	string szAction;
	string szExecutable;
	vector<string> params;
	hash_map<string, SDefaultArgument> actions;
	hash_map<string, SValuedArgument<bool>> boolOptions;
	hash_map<string, SValuedArgument<string>> stringOptions;
public:
	void RegisterAction( const string &szName, const string &szDescription );
	void RegisterOption( const string &szName, const string &szDescription );
	void RegisterOption( const string &szName, const string &szParamDescription, const string &szDescription );

	const bool ProcessCommandLine();
	const void ShowHelp( const string &szHeader, const string &szUsage, const bool bHasDefaultAction ) const;

	const string &GetExecutable() const { return szExecutable; }
	const string &GetAction() const { return szAction; }
	const vector<string> &GetParams() const { return params; }
	const bool GetOption( const string &szName, const bool bDefault ) const;
	const string &GetOption( const string &szName, const string &szDefault ) const;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
