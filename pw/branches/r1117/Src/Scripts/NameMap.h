#ifndef _NAMEMAP_H_
#define _NAMEMAP_H_

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>

#ifdef WIN32
  #pragma warning( disable : 4121 )
#endif  

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScript
{
	class VariantValue;

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class VariantValue
	{
	public:
		enum EType
		{
			NIL,
			BOOL,
			INT,
			FLOAT,
			STRING,
			TEXT
		};

	private:
		ZDATA
		EType type;
		bool b;
		int n;
		float f;
		string s;
		wstring t;
	public:
		ZEND int operator&( IBinSaver &f ) { f.Add(2,&type); f.Add(3,&b); f.Add(4,&n); f.Add(5,&f); f.Add(6,&s); f.Add(7,&t); return 0; }

	public:
		VariantValue(): type(NIL), b(false), n(0), f(0.0f) {}

	public:
		VariantValue( int val ) { Set(val); }
		VariantValue( float val ) { Set(val); }
		VariantValue( const char *val ) { Set(val); }
		VariantValue( const string & val ) { Set(val); }
		VariantValue( const CTextRef & val ) { Set(val); }
		VariantValue( const wstring & val ) { Set(val); }

		void Set( int _n ) { type = INT; n = _n; }
    void Set( bool _b ) { type = BOOL; b = _b; }
		void Set( float _f ) { type = FLOAT; f = _f; }
		void Set( const char *_s ) { type = STRING; s = _s; }
		void Set( const string & _s ) { type = STRING; s = _s; }
		void Set( const CTextRef & _t ) { type = TEXT; t = _t.GetText(); }
		void Set( const wstring & _t ) { type = TEXT; t = _t; }
		void Set( const VariantValue & v ) { *this = v; }

		EType GetType() const { return type; }

		int GetInt() const { return n; }
		float GetFloat() const { return f; }
		const string & GetString() const { return s; }
		const wstring & GetText() const { return t; }

		void SetBool( bool _b ) { b = _b; type = BOOL; }
		bool GetBool() const { return b; }
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class NamedValues
	{
    friend class NamedValuesIterator;
    friend class NamedValuesConstIterator;

		typedef hash_map<string,VariantValue> TValues;
		ZDATA
		TValues values;
	public:
		ZEND int operator&( IBinSaver &f ) { f.Add(2,&values); return 0; }

		void Clear()
		{
			values.clear();
		}

		const VariantValue & GetValue( const string & name ) const
		{
			static VariantValue nil;
			TValues::const_iterator it = values.find( name );
			if ( it == values.end() )
				return nil;
			return it->second;
		}

		bool HasValue( const string & name ) const
		{
			return values.find( name ) != values.end();
		}

		template<typename T>
		void SetValue( const string & name, const T & value )
		{
			values[ name ].Set( value );
		}

		void RemoveValue( const string & name )
		{
			TValues::iterator it = values.find( name );
			if ( it == values.end() )
				return;
			values.erase( it );
		}
	};

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //TODO: NamedValuesConstIterator
  class NamedValuesIterator
  {
  public:
    NamedValuesIterator( NamedValues & obj ) : pObj( &obj ), it( pObj->values.begin() ) {}
    NamedValuesIterator( NamedValuesIterator const& other ) : pObj( other.pObj ), it( other.it ) {}
    bool Valid() const { return it != pObj->values.end(); }
    const string & GetKey() const { NI_ASSERT( Valid(), ""); return it->first; }
    VariantValue & GetValue() const { NI_ASSERT( Valid(), ""); return it->second; }
    NamedValuesIterator& operator ++ () { ++it; return *this;}
    NamedValuesIterator  operator ++ (int) { NamedValuesIterator tmp(*this); ++*this; return tmp; }
  private:
    NamedValues * pObj;
    NamedValues::TValues::iterator it;
  };

  class NamedValuesConstIterator
  {
  public:
    NamedValuesConstIterator( NamedValues const& obj ) : pObj( &obj ), it( pObj->values.begin() ) {}
    NamedValuesConstIterator( NamedValuesConstIterator const& other ) : pObj( other.pObj ), it( other.it ) {}

    bool Valid() const { return it != pObj->values.end(); }
    const string & GetKey() const { NI_ASSERT( Valid(), ""); return it->first; }
    VariantValue const& GetValue() const { NI_ASSERT( Valid(), ""); return it->second; }
    NamedValuesConstIterator& operator ++ () { ++it; return *this;}
    NamedValuesConstIterator  operator ++ (int) { NamedValuesConstIterator tmp(*this); ++*this; return tmp; }
  private:
    NamedValues const* pObj;
    NamedValues::TValues::const_iterator it;
  };

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define PROCESS_DB_VALUE( valueName ) // if ( strcmp( key, #valueName ) == 0 ) { value.Set( valueName ); return true; }
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif

