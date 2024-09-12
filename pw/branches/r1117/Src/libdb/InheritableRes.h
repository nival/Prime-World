namespace NDb
{

struct LofSimpleInheritable : public DbResource
{
    DBRESOURCE_METHODS( LofSimpleInheritable );
public:
    bool _bool;
    int _int;
    float _float;
    string _string;

    LofSimpleInheritable();

    int operator&( IBinSaver &saver );
    int operator&( IXmlSaver &saver );

    DWORD CalcCheckSum() const { return 0; }

    bool operator==( const LofSimpleInheritable &_lofSimpleInheritable ) const { return IsEqual( _lofSimpleInheritable ); }
    bool operator!=( const LofSimpleInheritable &_lofSimpleInheritable ) const { return !IsEqual( _lofSimpleInheritable ); }
    bool IsEqual ( const LofSimpleInheritable &_lofSimpleInheritable ) const;

    LofSimpleInheritable& operator = ( const LofSimpleInheritable &_lofSimpleInheritable ) { Assign( _lofSimpleInheritable ); return *this; }
    LofSimpleInheritable( const LofSimpleInheritable &_lofSimpleInheritable ) { Assign( _lofSimpleInheritable ); }
    void Assign( const LofSimpleInheritable &_lofSimpleInheritable );
    virtual void OverridableAssign( const DbResource * _pResource )
    {
        const LofSimpleInheritable * pOther = dynamic_cast< const LofSimpleInheritable * > ( _pResource );
        if ( pOther ) LofSimpleInheritable::Assign( *pOther );
    }
};

LofSimpleInheritable::LofSimpleInheritable() :
_bool( false )
, _int( 0 )
, _float( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LofSimpleInheritable::operator&( IBinSaver &saver )
{
  saver.Add( 2, &_bool );
  saver.Add( 3, &_int );
  saver.Add( 4, &_float );
  saver.Add( 5, &_string );

  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LofSimpleInheritable::operator&( IXmlSaver &saver )
{
  if ( saver.HasParentAttr() )
  {
    string parent_str = saver.GetParentAttrValue();
    __parent = NDb::Get<LofSimpleInheritable>( NDb::DBID::DBID(parent_str) );
    if ( __parent.GetPtr() )
    {
      Assign(*(LofSimpleInheritable*)__parent.GetPtr());
    }
  }
  saver.Add( "_bool", &_bool );
  saver.Add( "_int", &_int );
  saver.Add( "_float", &_float );
  saver.Add( "_string", &_string );

  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LofSimpleInheritable::IsEqual( const LofSimpleInheritable& _lofSimpleInheritable ) const
{
  return _bool == _lofSimpleInheritable._bool
    && _int == _lofSimpleInheritable._int
    && _float == _lofSimpleInheritable._float
    && _string == _lofSimpleInheritable._string;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LofSimpleInheritable::Assign( const LofSimpleInheritable& _lofSimpleInheritable )
{
  _bool = _lofSimpleInheritable._bool;
  _int = _lofSimpleInheritable._int;
  _float = _lofSimpleInheritable._float;
  _string = _lofSimpleInheritable._string;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct LofHardInheritable : public DbResource
{
  DBRESOURCE_METHODS( LofHardInheritable );
public:
  int _int;
  vector<int> _list;

  LofHardInheritable();

  int operator&( IBinSaver &saver );
  int operator&( IXmlSaver &saver );

  DWORD CalcCheckSum() const { return 0; }

  bool operator==( const LofHardInheritable &_lofHardInheritable ) const { return IsEqual( _lofHardInheritable ); }
  bool operator!=( const LofHardInheritable &_lofHardInheritable ) const { return !IsEqual( _lofHardInheritable ); }
  bool IsEqual ( const LofHardInheritable &_lofHardInheritable ) const;

  LofHardInheritable& operator = ( const LofHardInheritable &_lofHardInheritable ) { Assign( _lofHardInheritable ); return *this; }
  LofHardInheritable( const LofHardInheritable &_lofHardInheritable ) { Assign( _lofHardInheritable ); }
  void Assign( const LofHardInheritable &_lofHardInheritable );
  virtual void OverridableAssign( const DbResource * _pResource )
  {
    const LofHardInheritable * pOther = dynamic_cast< const LofHardInheritable * > ( _pResource );
    if ( pOther ) LofHardInheritable::Assign( *pOther );
  }
};

LofHardInheritable::LofHardInheritable() :
_int( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LofHardInheritable::operator&( IBinSaver &saver )
{
  saver.Add( 2, &_int );
  saver.Add( 3, &_list );

  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LofHardInheritable::operator&( IXmlSaver &saver )
{
  if ( saver.HasParentAttr() )
  {
    string parent_str = saver.GetParentAttrValue();
    __parent = NDb::Get<LofHardInheritable>( NDb::DBID::DBID(parent_str) );
    if ( __parent.GetPtr() )
    {
      Assign(*(LofHardInheritable*)__parent.GetPtr());
    }
  }
  saver.Add( "_int", &_int );
  saver.Add( "_list", &_list );

  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LofHardInheritable::IsEqual( const LofHardInheritable& _lofHardInheritable ) const
{
  return _int == _lofHardInheritable._int
    && _list == _lofHardInheritable._list;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LofHardInheritable::Assign( const LofHardInheritable& _lofHardInheritable )
{
  _int = _lofHardInheritable._int;
  _list = _lofHardInheritable._list;
}

struct PseudoStruct
{
  int x;
  int y;

  PseudoStruct();

  int operator&( IBinSaver &saver );
  int operator&( IXmlSaver &saver );

  DWORD CalcCheckSum() const { return 0; }

  bool operator==( const PseudoStruct &_pseudoStruct ) const { return IsEqual( _pseudoStruct ); }
  bool operator!=( const PseudoStruct &_pseudoStruct ) const { return !IsEqual( _pseudoStruct ); }
  bool IsEqual ( const PseudoStruct &_pseudoStruct ) const;
};

PseudoStruct::PseudoStruct() :
x( 0 )
, y( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PseudoStruct::operator&( IBinSaver &saver )
{
  saver.Add( 2, &x );
  saver.Add( 3, &y );

  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PseudoStruct::operator&( IXmlSaver &saver )
{
  saver.Add( "x", &x );
  saver.Add( "y", &y );

  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PseudoStruct::IsEqual( const PseudoStruct& _pseudoStruct ) const
{
  return x == _pseudoStruct.x
    && y == _pseudoStruct.y;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct LofComplexInheritable : public DbResource
{
  DBRESOURCE_METHODS( LofComplexInheritable );
public:
  int _int;
  vector<PseudoStruct> _list;

  LofComplexInheritable();

  int operator&( IBinSaver &saver );
  int operator&( IXmlSaver &saver );

  DWORD CalcCheckSum() const { return 0; }

  bool operator==( const LofComplexInheritable &_lofComplexInheritable ) const { return IsEqual( _lofComplexInheritable ); }
  bool operator!=( const LofComplexInheritable &_lofComplexInheritable ) const { return !IsEqual( _lofComplexInheritable ); }
  bool IsEqual ( const LofComplexInheritable &_lofComplexInheritable ) const;

  LofComplexInheritable& operator = ( const LofComplexInheritable &_lofComplexInheritable ) { Assign( _lofComplexInheritable ); return *this; }
  LofComplexInheritable( const LofComplexInheritable &_lofComplexInheritable ) { Assign( _lofComplexInheritable ); }
  void Assign( const LofComplexInheritable &_lofComplexInheritable );
  virtual void OverridableAssign( const DbResource * _pResource )
  {
    const LofComplexInheritable * pOther = dynamic_cast< const LofComplexInheritable * > ( _pResource );
    if ( pOther ) LofComplexInheritable::Assign( *pOther );
  }
};

LofComplexInheritable::LofComplexInheritable() :
_int( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LofComplexInheritable::operator&( IBinSaver &saver )
{
  saver.Add( 2, &_int );
  saver.Add( 3, &_list );

  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LofComplexInheritable::operator&( IXmlSaver &saver )
{
  if ( saver.HasParentAttr() )
  {
    string parent_str = saver.GetParentAttrValue();
    __parent = NDb::Get<LofComplexInheritable>( NDb::DBID::DBID(parent_str) );
    if ( __parent.GetPtr() )
    {
      Assign(*(LofComplexInheritable*)__parent.GetPtr());
    }
  }
  saver.Add( "_int", &_int );
  saver.Add( "_list", &_list );

  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LofComplexInheritable::IsEqual( const LofComplexInheritable& _lofComplexInheritable ) const
{
  return _int == _lofComplexInheritable._int
    && _list == _lofComplexInheritable._list;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LofComplexInheritable::Assign( const LofComplexInheritable& _lofComplexInheritable )
{
  _int = _lofComplexInheritable._int;
  _list = _lofComplexInheritable._list;
}

struct LofSimpleChild : public LofSimpleInheritable
{
  DBRESOURCE_METHODS( LofSimpleChild );
public:
  Ptr<LofSimpleInheritable> twin;
  PseudoStruct _data;

  LofSimpleChild();

  int operator&( IBinSaver &saver );
  int operator&( IXmlSaver &saver );

  DWORD CalcCheckSum() const { return 0; }

  bool operator==( const LofSimpleChild &_lofSimpleChild ) const { return IsEqual( _lofSimpleChild ); }
  bool operator!=( const LofSimpleChild &_lofSimpleChild ) const { return !IsEqual( _lofSimpleChild ); }
  bool IsEqual ( const LofSimpleChild &_lofSimpleChild ) const;

  LofSimpleChild& operator = ( const LofSimpleChild &_lofSimpleChild ) { Assign( _lofSimpleChild ); return *this; }
  LofSimpleChild( const LofSimpleChild &_lofSimpleChild ) { Assign( _lofSimpleChild ); }
  void Assign( const LofSimpleChild &_lofSimpleChild );
  virtual void OverridableAssign( const DbResource * _pResource )
  {
    const LofSimpleChild * pOther = dynamic_cast< const LofSimpleChild * > ( _pResource );
    if ( pOther ) LofSimpleChild::Assign( *pOther );
  }
};

LofSimpleChild::LofSimpleChild()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LofSimpleChild::operator&( IBinSaver &saver )
{
  saver.Add( 1, (LofSimpleInheritable*)this );
  saver.Add( 2, &twin );
  saver.Add( 3, &_data );

  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LofSimpleChild::operator&( IXmlSaver &saver )
{
  if ( saver.HasParentAttr() )
  {
    string parent_str = saver.GetParentAttrValue();
    __parent = ReadResource( saver, DBID::DBID(parent_str) );
    if ( __parent.GetPtr() )
    {
      Assign(*(LofSimpleChild*)__parent.GetPtr());
    }
  }
  saver.AddTypedSuper( (LofSimpleInheritable*)this );
  saver.Add( "twin", &twin );
  saver.Add( "_data", &_data );

  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LofSimpleChild::IsEqual( const LofSimpleChild& _lofSimpleChild ) const
{
  return twin == _lofSimpleChild.twin
    && _data.x == _lofSimpleChild._data.x
    && _data.y == _lofSimpleChild._data.y
    && _bool == _lofSimpleChild._bool
    && _int == _lofSimpleChild._int
    && _float == _lofSimpleChild._float
    && _string == _lofSimpleChild._string;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LofSimpleChild::Assign( const LofSimpleChild& _lofSimpleChild )
{
  twin = _lofSimpleChild.twin;
  _data.x = _lofSimpleChild._data.x;
  _data.y = _lofSimpleChild._data.y;
  _bool = _lofSimpleChild._bool;
  _int = _lofSimpleChild._int;
  _float = _lofSimpleChild._float;
  _string = _lofSimpleChild._string;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


struct TestStatedObject : public DbResource
{
  DBRESOURCE_METHODS( TestStatedObject );
protected:
  mutable DBResourceStateManager stateManager;
  virtual DBResourceStateManager* GetStatesManager() const { return &stateManager; }
public:
  int _int;
  vector<PseudoStruct> _list;

  TestStatedObject();

  int operator&( IBinSaver &saver );
  int operator&( IXmlSaver &saver );
  void SerializeSelf( IXmlSaver &saver );

  DWORD CalcCheckSum() const { return 0; }

  bool operator==( const TestStatedObject &_testStatedObject ) const { return IsEqual( _testStatedObject ); }
  bool operator!=( const TestStatedObject &_testStatedObject ) const { return !IsEqual( _testStatedObject ); }
  bool IsEqual ( const TestStatedObject &_testStatedObject ) const;

  TestStatedObject& operator = ( const TestStatedObject &_testStatedObject ) { Assign( _testStatedObject ); return *this; }
  TestStatedObject( const TestStatedObject &_testStatedObject ) { Assign( _testStatedObject ); }
  void Assign( const TestStatedObject &_testStatedObject );
  virtual void OverridableAssign( const DbResource * _pResource )
  {
    const TestStatedObject * pOther = dynamic_cast< const TestStatedObject * > ( _pResource );
    if ( pOther ) TestStatedObject::Assign( *pOther );
  }

};

TestStatedObject::TestStatedObject()
:_int( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TestStatedObject::operator&( IBinSaver &saver )
{
  saver.Add( 2, &_int );
  saver.Add( 3, &_list );

  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TestStatedObject::operator&( IXmlSaver &saver )
{
  bool inheritedStates = false;
  if ( saver.HasParentAttr() )
  {
    string parent_str = saver.GetParentAttrValue();
    __parent = ReadResource( saver, DBID::DBID(parent_str) );
    if ( __parent.GetPtr() )
    {
      TestStatedObject* parentPtr = (TestStatedObject*)__parent.GetPtr();
      Assign( *parentPtr );
      StateSerializeHelper<TestStatedObject> parentStateCopier( this, stateManager.states, &TestStatedObject::NewTestStatedObject );
      parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
      inheritedStates = true;
    }
  }

  SerializeSelf( saver );

  if ( !inheritedStates )
  {
    StateSerializeHelper<TestStatedObject> reader( this, stateManager.states, &TestStatedObject::NewTestStatedObject );
    saver.AddPolymorphicBase( "states", &reader );
  }

  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestStatedObject::SerializeSelf( IXmlSaver &saver )
{
  saver.Add( "_int", &_int );
  saver.Add( "_list", &_list );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TestStatedObject::IsEqual( const TestStatedObject& _lofComplexInheritable ) const
{
  return _int == _lofComplexInheritable._int
    && _list == _lofComplexInheritable._list;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestStatedObject::Assign( const TestStatedObject& _lofComplexInheritable )
{
  _int = _lofComplexInheritable._int;
  _list = _lofComplexInheritable._list;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct TestStatedObject2 : public TestStatedObject
{
  DBRESOURCE_METHODS( TestStatedObject2 );
public:
  string name;
  Ptr<TestStatedObject2> ref;

  TestStatedObject2();

  int operator&( IBinSaver &saver );
  int operator&( IXmlSaver &saver );
  void SerializeSelf( IXmlSaver &saver );

  DWORD CalcCheckSum() const { return 0; }

  bool operator==( const TestStatedObject2 &_testStatedObject ) const { return IsEqual( _testStatedObject ); }
  bool operator!=( const TestStatedObject2 &_testStatedObject ) const { return !IsEqual( _testStatedObject ); }
  bool IsEqual ( const TestStatedObject2 &_testStatedObject ) const;

  TestStatedObject2& operator = ( const TestStatedObject2 &_testStatedObject ) { Assign( _testStatedObject ); return *this; }
  TestStatedObject2( const TestStatedObject2 &_testStatedObject ) { Assign( _testStatedObject ); }
  void Assign( const TestStatedObject2 &_testStatedObject );
  virtual void OverridableAssign( const DbResource * _pResource )
  {
    const TestStatedObject2 * pOther = dynamic_cast< const TestStatedObject2 * > ( _pResource );
    if ( pOther ) TestStatedObject2::Assign( *pOther );
  }

};
TestStatedObject2::TestStatedObject2() 
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TestStatedObject2::operator&( IBinSaver &saver )
{
  saver.Add( 1, (TestStatedObject*)this );
  saver.Add( 2, &name );
  saver.Add( 3, &ref );
  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TestStatedObject2::operator&( IXmlSaver &saver )
{
  if ( saver.HasParentAttr() )
  {
    string parent_str = saver.GetParentAttrValue();
    __parent = ReadResource( saver, DBID::DBID(parent_str) );
    if ( __parent.GetPtr() )
    {
      Assign(*((TestStatedObject2*)__parent.GetPtr()));
    }
  }

  SerializeSelf(saver);

  StateSerializeHelper<TestStatedObject2> reader( this, stateManager.states, &TestStatedObject2::NewTestStatedObject2 );
  saver.AddPolymorphicBase( "__states", &reader );

  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestStatedObject2::SerializeSelf( IXmlSaver &saver )
{
  TestStatedObject::SerializeSelf( saver );
  saver.Add( "name", &name );
  saver.Add( "ref", &ref );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TestStatedObject2::IsEqual( const TestStatedObject2& _lofComplexInheritable ) const
{
  return _int == _lofComplexInheritable._int
    && _list == _lofComplexInheritable._list
    && name == _lofComplexInheritable.name
    && ref == _lofComplexInheritable.ref;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestStatedObject2::Assign( const TestStatedObject2& _lofComplexInheritable )
{
  _int = _lofComplexInheritable._int;
  _list = _lofComplexInheritable._list;
  name = _lofComplexInheritable.name;
  ref = _lofComplexInheritable.ref;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct TestMultipleDeserialize : public DbResource
{
  DBRESOURCE_METHODS( TestMultipleDeserialize );
public:
  int _int;

  TestMultipleDeserialize();

  int operator&( IBinSaver &saver );
  int operator&( IXmlSaver &saver );
  void SerializeSelf( IXmlSaver &saver );

  DWORD CalcCheckSum() const { return 0; }

  bool operator==( const TestMultipleDeserialize &_testStatedObject ) const { return IsEqual( _testStatedObject ); }
  bool operator!=( const TestMultipleDeserialize &_testStatedObject ) const { return !IsEqual( _testStatedObject ); }
  bool IsEqual ( const TestMultipleDeserialize &_testStatedObject ) const;

  TestMultipleDeserialize& operator = ( const TestMultipleDeserialize &_testStatedObject ) { Assign( _testStatedObject ); return *this; }
  TestMultipleDeserialize( const TestMultipleDeserialize &_testStatedObject ) { Assign( _testStatedObject ); }
  void Assign( const TestMultipleDeserialize &_testStatedObject );
  virtual void OverridableAssign( const DbResource * _pResource )
  {
    const TestMultipleDeserialize * pOther = dynamic_cast< const TestMultipleDeserialize * > ( _pResource );
    if ( pOther ) TestMultipleDeserialize::Assign( *pOther );
  }

};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TestMultipleDeserialize::TestMultipleDeserialize()
:_int( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TestMultipleDeserialize::operator&( IBinSaver &saver )
{
  saver.Add( 2, &_int );

  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TestMultipleDeserialize::operator&( IXmlSaver &saver )
{
  SerializeSelf( saver );
  _int -= 999;
  SerializeSelf( saver );

  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestMultipleDeserialize::SerializeSelf( IXmlSaver &saver )
{
  saver.Add( "_int", &_int );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TestMultipleDeserialize::IsEqual( const TestMultipleDeserialize& _lofComplexInheritable ) const
{
  return _int == _lofComplexInheritable._int;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestMultipleDeserialize::Assign( const TestMultipleDeserialize& _lofComplexInheritable )
{
  _int = _lofComplexInheritable._int;
}


}