#ifndef CMDLINE_H_
#define CMDLINE_H_

#include <assert.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NCmdLine
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// dbcodegen -all --dry-run --types-path "c:\b2\data\" --config "dbconfig.xml"
// cl.AddOption( "all", cl.CreateObserver(&eType, MYVAL_ALL), "generate types.xml and sources" );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CCmdLine
{
public:
	_interface IObserver;
	enum EProcessResult
	{
		PROC_RESULT_OK,										// command line processed successfully
		PROC_RESULT_UNKNOWN_OPTION,				// processing failed - unknown option in command line
		PROC_RESULT_AMBIGUITY,						// processing failed - ambiguity parameter
		PROC_RESULT_VALUE_NOT_FOUND,			// value for option not found in command line
		PROC_RESULT_NO_ARGUMENTS,					// arguments required, but doesn't provided
	};
private:
	template <class TYPE> class CObserver;
	struct SObserver
	{
		string szName;
		string szDescription;
		CObj<IObserver> pObserver;
	};
	typedef list<SObserver> CObserversList;
	CObserversList observers;
	string szHeader;
  bool ignoreUnknownOpts;
	//
	const SObserver *Find( const char *pszName ) const;
	bool AddOptionInternal( const char *pszName, IObserver *pObserver, const char *pszDescription );
	// observer with external value
	IObserver *MakeIntObserver( int *pRes ) const;
	IObserver *MakeBoolObserver( bool *pRes ) const;
	IObserver *MakeFloatObserver( float *pRes ) const;
	IObserver *MakeStringObserver( string *pRes ) const;
	IObserver *MakeWStringObserver( wstring *pRes ) const;
	// observer with internal value
	IObserver *MakeIntObserver( int *pRes, const int &setval ) const;
	IObserver *MakeBoolObserver( bool *pRes, const bool &setval ) const;
	IObserver *MakeFloatObserver( float *pRes, const float &setval ) const;
	IObserver *MakeStringObserver( string *pRes, const string &setval ) const;
	IObserver *MakeWStringObserver( wstring *pRes, const wstring &setval ) const;
public:
	CCmdLine( const string &_szHeader, bool _ignoreUnknownOpts=false ): szHeader( _szHeader ), ignoreUnknownOpts(_ignoreUnknownOpts) {}
	// add option with internal value
	// common case for enums only!
	template <class TVal>
		bool AddOption( const char *pszName, TVal *pRes, const TVal &setval, const char *pszDescription )
	{
		//assert( sizeof(TVal) == 4 );
		return AddOption<int>( pszName, (int*)pRes, *((int*)&setval), pszDescription );
	}
	// add option with external value
	// common case for enums only!
	template <class TVal>
		bool AddOption( const char *pszName, TVal *pRes, const char *pszDescription )
	{
		assert( sizeof(TVal) == 4 );
		return AddOption<int>( pszName, (int*)pRes, pszDescription );
	}
	//! process command line
	EProcessResult Process( const vector<string> &args ) const;
	EProcessResult Process( const char *pszCommandLine ) const;
	EProcessResult Process( int argc, char *argv[] ) const;

  void Split(const char *pszCommandLine, vector<string> &args) const;

	//! print usage help
	int PrintUsage( const char *pszAdd ) const; // always return 0xDEAD
	//! print copyright info
	int PrintHeader() const;
	//! get help string for option 'pszName'
	string GetHelp( const char *pszName ) const;
};

template <>
inline bool CCmdLine::AddOption<bool>( const char *pszName, bool *pRes, const bool &setval, const char *pszDescription )
{
  return AddOptionInternal( pszName, MakeBoolObserver(pRes, setval), pszDescription );
}

template <>
inline bool CCmdLine::AddOption<int>( const char *pszName, int *pRes, const int &setval, const char *pszDescription )
{
  return AddOptionInternal( pszName, MakeIntObserver(pRes, setval), pszDescription );
}
template <>
inline bool CCmdLine::AddOption<float>( const char *pszName, float *pRes, const float &setval, const char *pszDescription )
{
  return AddOptionInternal( pszName, MakeFloatObserver(pRes, setval), pszDescription );
}
template <>
inline bool CCmdLine::AddOption<string>( const char *pszName, string *pRes, const string &setval, const char *pszDescription )
{
  return AddOptionInternal( pszName, MakeStringObserver(pRes, setval), pszDescription );
}
template <>
inline bool CCmdLine::AddOption<wstring>( const char *pszName, wstring *pRes, const wstring &setval, const char *pszDescription )
{
  return AddOptionInternal( pszName, MakeWStringObserver(pRes, setval), pszDescription );
}

template <>
inline bool CCmdLine::AddOption<bool>( const char *pszName, bool *pRes, const char *pszDescription )
{
  return AddOptionInternal( pszName, MakeBoolObserver(pRes), pszDescription );
}
template <>
inline bool CCmdLine::AddOption<int>( const char *pszName, int *pRes, const char *pszDescription )
{
  return AddOptionInternal( pszName, MakeIntObserver(pRes), pszDescription );
}
template <>
inline bool CCmdLine::AddOption<float>( const char *pszName, float *pRes, const char *pszDescription )
{
  return AddOptionInternal( pszName, MakeFloatObserver(pRes), pszDescription );
}
template <>
inline bool CCmdLine::AddOption<string>( const char *pszName, string *pRes, const char *pszDescription )
{
  return AddOptionInternal( pszName, MakeStringObserver(pRes), pszDescription );
}
template <>
inline bool CCmdLine::AddOption<wstring>( const char *pszName, wstring *pRes, const char *pszDescription )
{
  return AddOptionInternal( pszName, MakeWStringObserver(pRes), pszDescription );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif

