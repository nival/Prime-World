#pragma once

namespace avmplus
{
  typedef __int32	int32_t;
  typedef int32_t Atom;

  class ScriptObject;
  class AvmCore;
  class Toplevel;
}

namespace UI
{

class FlashContainer2;

static const wstring stubString;
static const nstl::vector<wstring> stubStringArray;
static const nstl::vector<int> stubIntArray;
static const nstl::vector<uint> stubUintArray;

class FVar : public NonCopyable
{
public:

  explicit FVar( bool _val ) : valueBool(_val), type(Bool), valueIntArray(stubIntArray), valueWString(stubString), valueWSArray(stubStringArray), valueUintArray(stubUintArray) {}
  explicit FVar( int _val ) : valueInt(_val), type(Int), valueIntArray(stubIntArray), valueWString(stubString), valueWSArray(stubStringArray), valueUintArray(stubUintArray) {}
  explicit FVar( const nstl::vector<int>& _val ) : valueIntArray(_val), type(IntArray), valueWString(stubString), valueWSArray(stubStringArray), valueUintArray(stubUintArray)  {}
  explicit FVar( uint _val ) : valueUint(_val), type(Uint), valueIntArray(stubIntArray), valueWString(stubString), valueWSArray(stubStringArray) , valueUintArray(stubUintArray){}
  explicit FVar( const nstl::vector<uint>& _val ) : valueUintArray(_val), type(UintArray), valueIntArray(stubIntArray), valueWString(stubString), valueWSArray(stubStringArray) {}
  explicit FVar( float _val ) : valueFloat(_val), type(Float), valueIntArray(stubIntArray), valueWString(stubString), valueWSArray(stubStringArray), valueUintArray(stubUintArray) {}
  explicit FVar( const char* _val ) : valueChar(_val), type(ConstChar), valueIntArray(stubIntArray), valueWString(stubString), valueWSArray(stubStringArray), valueUintArray(stubUintArray) {}
  explicit FVar( const wstring& _val ) : valueWString(_val), type(WString), valueIntArray(stubIntArray), valueWSArray(stubStringArray), valueUintArray(stubUintArray) {}
  explicit FVar( const nstl::vector<wstring>& _val ) : valueWSArray(_val), type(WStringArray), valueIntArray(stubIntArray), valueWString(stubString), valueUintArray(stubUintArray) {}
  explicit FVar( const string& _val ) : valueChar(_val.c_str()), type(ConstChar), valueIntArray(stubIntArray), valueWString(stubString), valueWSArray(stubStringArray), valueUintArray(stubUintArray) {}

  avmplus::Atom GetAtom( avmplus::Toplevel * _toplevel ) const;

private:

  enum Type
  {
    Bool,
    Int,
    IntArray,
    Uint,
    UintArray,
    Float,
    ConstChar,
    WString,
    WStringArray
  };

  bool  valueBool;
  int   valueInt;
  uint  valueUint;
  float valueFloat;
  const char* valueChar;
  const wstring& valueWString;
  const nstl::vector<wstring>& valueWSArray;
  const nstl::vector<int>& valueIntArray;
  const nstl::vector<uint>& valueUintArray;

  Type type;
};

class FlashInterface : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( FlashInterface, BaseObjectST );

public:
  FlashInterface( UI::FlashContainer2 * _flashWnd, const char* _className );

  avmplus::Atom CallMethod( const char * method )
  {
    return CallMethodI( method );
  }

  template<typename T1>
  avmplus::Atom CallMethod( const char * method, T1 p1 )
  {
    return CallMethodI( method, FVar( p1 ) );
  }

  template<typename T1, typename T2>
  avmplus::Atom CallMethod( const char * method, T1 p1, T2 p2 )
  {
    return CallMethodI( method, FVar( p1 ), FVar( p2 ) );
  }

  template<typename T1, typename T2, typename T3>
  avmplus::Atom CallMethod( const char * method, T1 p1, T2 p2, T3 p3 )
  {
    return CallMethodI( method, FVar( p1 ), FVar( p2 ), FVar( p3 ) );
  }

  template<typename T1, typename T2, typename T3, typename T4>
  avmplus::Atom CallMethod( const char * method, T1 p1, T2 p2, T3 p3, T4 p4 )
  {
    return CallMethodI( method, FVar( p1 ), FVar( p2 ), FVar( p3 ), FVar( p4 ) );
  }

  template<typename T1, typename T2, typename T3, typename T4, typename T5>
  avmplus::Atom CallMethod( const char * method, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5 )
  {
    return CallMethodI( method, FVar( p1 ), FVar( p2 ), FVar( p3 ), FVar( p4 ), FVar( p5 )  );
  }

  template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
  avmplus::Atom CallMethod( const char * method, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6 )
  {
    return CallMethodI( method, FVar( p1 ), FVar( p2 ), FVar( p3 ), FVar( p4 ), FVar( p5 ), FVar( p6 ) );
  }

  template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
  avmplus::Atom CallMethod( const char * method, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7 )
  {
    return CallMethodI( method, FVar( p1 ), FVar( p2 ), FVar( p3 ), FVar( p4 ), FVar( p5 ), FVar( p6 ), FVar( p7 ) );
  }

  template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
  avmplus::Atom CallMethod( const char * method, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8 )
  {
    return CallMethodI( method, FVar( p1 ), FVar( p2 ), FVar( p3 ), FVar( p4 ), FVar( p5 ), FVar( p6 ), FVar( p7 ), FVar( p8 ) );
  }

  template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
  avmplus::Atom CallMethod( const char * method, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,  T9 p9)
  {
    return CallMethodI( method, FVar( p1 ), FVar( p2 ), FVar( p3 ), FVar( p4 ), FVar( p5 ), FVar( p6 ), FVar( p7 ), FVar( p8 ), FVar( p9 ) );
  }

  template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
  avmplus::Atom CallMethod( const char * method, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,  T9 p9, T10 p10)
  {
	  return CallMethodI( method, FVar( p1 ), FVar( p2 ), FVar( p3 ), FVar( p4 ), FVar( p5 ), FVar( p6 ), FVar( p7 ), FVar( p8 ), FVar( p9 ), FVar( p10 ) );
  }

  template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
  avmplus::Atom CallMethod( const char * method, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,  T9 p9, T10 p10, T11 p11)
  {
    return CallMethodI( method, FVar( p1 ), FVar( p2 ), FVar( p3 ), FVar( p4 ), FVar( p5 ), FVar( p6 ), FVar( p7 ), FVar( p8 ), FVar( p9 ), FVar( p10 ),  FVar( p11 )  );
  }


  template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
  avmplus::Atom CallMethod( const char * method, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,  T9 p9, T10 p10, T11 p11, T12 p12)
  {
    return CallMethodI( method, FVar( p1 ), FVar( p2 ), FVar( p3 ), FVar( p4 ), FVar( p5 ), FVar( p6 ), FVar( p7 ), FVar( p8 ), FVar( p9 ), FVar( p10 ),  FVar( p11 ), FVar( p12 )  );
  }

  template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
  avmplus::Atom CallMethod( const char * method, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,  T9 p9, T10 p10, T11 p11, T12 p12, T13 p13)
  {
  	return CallMethodI( method, FVar( p1 ), FVar( p2 ), FVar( p3 ), FVar( p4 ), FVar( p5 ), FVar( p6 ), FVar( p7 ), FVar( p8 ), FVar( p9 ), FVar( p10 ),  FVar( p11 ), FVar( p12 ), FVar( p13 )   );
  }

  template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
  avmplus::Atom CallMethod( const char * method, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,  T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14)
  {
	  return CallMethodI( method, FVar( p1 ), FVar( p2 ), FVar( p3 ), FVar( p4 ), FVar( p5 ), FVar( p6 ), FVar( p7 ), FVar( p8 ), FVar( p9 ), FVar( p10 ),  FVar( p11 ), FVar( p12 ), FVar( p13 ), FVar( p14 )  );
  }

  template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
  avmplus::Atom CallMethod( const char * method, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,  T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15)
  {
    return CallMethodI( method, FVar( p1 ), FVar( p2 ), FVar( p3 ), FVar( p4 ), FVar( p5 ), FVar( p6 ), FVar( p7 ), FVar( p8 ), FVar( p9 ), FVar( p10 ),  FVar( p11 ), FVar( p12 ), FVar( p13 ), FVar( p14 ). FVar( p15 )  );
  }
  template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14,typename T15, typename T16>
  avmplus::Atom CallMethod( const char * method, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,  T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16)
  {
    return CallMethodI( method, FVar( p1 ), FVar( p2 ), FVar( p3 ), FVar( p4 ), FVar( p5 ), FVar( p6 ), FVar( p7 ), FVar( p8 ), FVar( p9 ), FVar( p10 ),  FVar( p11 ), FVar( p12 ), FVar( p13 ), FVar( p14 ), FVar( p15 ), FVar( p16 )  );
  }

  template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14,typename T15, typename T16, typename T17>
  avmplus::Atom CallMethod( const char * method, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,  T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17)
  {
    return CallMethodI( method, FVar( p1 ), FVar( p2 ), FVar( p3 ), FVar( p4 ), FVar( p5 ), FVar( p6 ), FVar( p7 ), FVar( p8 ), FVar( p9 ), FVar( p10 ),  FVar( p11 ), FVar( p12 ), FVar( p13 ), FVar( p14 ), FVar( p15 ), FVar( p16 ), FVar( p17 ) );
  }

  template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14,typename T15, typename T16, typename T17, typename T18>
  avmplus::Atom CallMethod( const char * method, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,  T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18)
  {
    return CallMethodI( method, FVar( p1 ), FVar( p2 ), FVar( p3 ), FVar( p4 ), FVar( p5 ), FVar( p6 ), FVar( p7 ), FVar( p8 ), FVar( p9 ), FVar( p10 ),  FVar( p11 ), FVar( p12 ), FVar( p13 ), FVar( p14 ), FVar( p15 ), FVar( p16 ), FVar( p17 ), FVar( p18 ) );
  }

  template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14,typename T15, typename T16, typename T17, typename T18, typename T19>
  avmplus::Atom CallMethod( const char * method, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,  T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19)
  {
    return CallMethodI( method, FVar( p1 ), FVar( p2 ), FVar( p3 ), FVar( p4 ), FVar( p5 ), FVar( p6 ), FVar( p7 ), FVar( p8 ), FVar( p9 ), FVar( p10 ),  FVar( p11 ), FVar( p12 ), FVar( p13 ), FVar( p14 ), FVar( p15 ), FVar( p16 ), FVar( p17 ), FVar( p18 ), FVar( p19 ) );
  }

  template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14,typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
  avmplus::Atom CallMethod( const char * method, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,  T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20)
  {
    return CallMethodI( method, FVar( p1 ), FVar( p2 ), FVar( p3 ), FVar( p4 ), FVar( p5 ), FVar( p6 ), FVar( p7 ), FVar( p8 ), FVar( p9 ), FVar( p10 ),  FVar( p11 ), FVar( p12 ), FVar( p13 ), FVar( p14 ), FVar( p15 ), FVar( p16 ), FVar( p17 ), FVar( p18 ), FVar( p19 ), FVar( p20 ) );
  }

  bool AtomGetBool( avmplus::Atom atom );
  int AtomGetInt( avmplus::Atom atom );

protected:
  FlashInterface() {};

  avmplus::ScriptObject * AtomToObject( avmplus::Atom atom );

private:
  avmplus::ScriptObject * mainInterface;

  avmplus::Atom CallMethodI( const char * method );
  avmplus::Atom CallMethodI( const char * method, const FVar& p1 );
  avmplus::Atom CallMethodI( const char * method, const FVar& p1, const FVar& p2 );
  avmplus::Atom CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3 );
  avmplus::Atom CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4 );
  avmplus::Atom CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5 );
  avmplus::Atom CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6 );
  avmplus::Atom CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7 );
  avmplus::Atom CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7, const FVar& p8 );
  avmplus::Atom CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7, const FVar& p8,  const FVar& p9);
  avmplus::Atom CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7, const FVar& p8,  const FVar& p9, const FVar& p10);
  avmplus::Atom CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7, const FVar& p8,  const FVar& p9, const FVar& p10, const FVar& p11);
  avmplus::Atom CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7, const FVar& p8,  const FVar& p9, const FVar& p10, const FVar& p11, const FVar& p12 );
  avmplus::Atom CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7, const FVar& p8,  const FVar& p9, const FVar& p10, const FVar& p11, const FVar& p12, const FVar& p13 );
  avmplus::Atom CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7, const FVar& p8,  const FVar& p9, const FVar& p10, const FVar& p11, const FVar& p12, const FVar& p13, const FVar& p14 );
  avmplus::Atom CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7, const FVar& p8,  const FVar& p9, const FVar& p10, const FVar& p11, const FVar& p12, const FVar& p13, const FVar& p14, const FVar& p15 );
  avmplus::Atom CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7, const FVar& p8,  const FVar& p9, const FVar& p10, const FVar& p11, const FVar& p12, const FVar& p13, const FVar& p14, const FVar& p15, const FVar& p16 );
  avmplus::Atom CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7, const FVar& p8,  const FVar& p9, const FVar& p10, const FVar& p11, const FVar& p12, const FVar& p13, const FVar& p14, const FVar& p15, const FVar& p16, const FVar& p17 );
  avmplus::Atom CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7, const FVar& p8,  const FVar& p9, const FVar& p10, const FVar& p11, const FVar& p12, const FVar& p13, const FVar& p14, const FVar& p15, const FVar& p16, const FVar& p17, const FVar& p18 );  
  avmplus::Atom CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7, const FVar& p8,  const FVar& p9, const FVar& p10, const FVar& p11, const FVar& p12, const FVar& p13, const FVar& p14, const FVar& p15, const FVar& p16, const FVar& p17, const FVar& p18, const FVar& p19 );  
  avmplus::Atom CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7, const FVar& p8,  const FVar& p9, const FVar& p10, const FVar& p11, const FVar& p12, const FVar& p13, const FVar& p14, const FVar& p15, const FVar& p16, const FVar& p17, const FVar& p18, const FVar& p19, const FVar& p20 );  
};

}
