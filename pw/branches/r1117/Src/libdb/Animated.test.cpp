//!Component("libdb/Database")
//!Component("libdb/XMLSaver")
#include "stdafx.h"
#include "Animated.h"
#include "AnimatedAlgorithms.h"

#include <CxxTest.h>
#include "XmlSaver.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NDb
{
struct AnimatedResource1 : DbResource
{
    DBRESOURCE_METHODS( AnimatedResource1 );

    Animated<int, AnimatedAlgorithms::Linear> _int;
    Animated<float, AnimatedAlgorithms::Linear> _floats;
    Animated<string, AnimatedAlgorithms::Discrete> _string;
    Animated<CVec3, AnimatedAlgorithms::Linear> _vecs;

    virtual int GetTypeId() const { return 0; }
    virtual int operator&( IXmlSaver &saver )
    {
        saver.Add( "_int", &_int );
        saver.Add( "_floats", &_floats );
        saver.Add( "_string", &_string );
        saver.Add( "_vecs", &_vecs );

        return 0;
    }
    virtual DWORD CalcCheckSum() const { return 0; }
};
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
T* CreateResource( const char* xml )
{
    CPtr<Stream> pStream = new FixedMemoryStream( (void*)xml, strlen( xml ) );
    CPtr<IXmlSaver> pSaver = CreateXmlSaver( pStream, true );

    T* result = new T();
    pSaver->AddPolymorphicBase( T::GetTypeName(), result );

    return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class AnimatedTest : public CxxTest::TestSuite
{
public:
    void TestBackwardCompatibility();
    void TestDeserialization();
    void TestLinearAlgorithms();
    void TestDiscreteAlgorithms();
    void TestBackwardCompatibilityVec3();
  void TestDiscreteChanges();
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimatedTest::TestBackwardCompatibility()
{
    NDb::AnimatedResource1* pRes = CreateResource<NDb::AnimatedResource1>( "<AnimatedResource1><_int>1</_int><_string>Test</_string><_vecs><x>1</x><y>2</y><z>3</z></_vecs></AnimatedResource1>" );
    TS_ASSERT_EQUALS( pRes->_int, 1 );
    TS_ASSERT_EQUALS( (string)(pRes->_string), "Test" );
    TS_ASSERT_EQUALS( ((CVec3)(pRes->_vecs)).x, 1.0f );
    delete pRes;

    pRes = CreateResource<NDb::AnimatedResource1>( "<AnimatedResource1><_int>12</_int></AnimatedResource1>" );
    TS_ASSERT_EQUALS( pRes->_int, 12 );
    delete pRes;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimatedTest::TestBackwardCompatibilityVec3()
{
    NDb::AnimatedResource1* pRes = CreateResource<NDb::AnimatedResource1>( "<AnimatedResource1><_vecs><x>1</x><y>2</y><z>3</z></_vecs></AnimatedResource1>" );
    TS_ASSERT_EQUALS( ((CVec3)(pRes->_vecs)).x, 1.0f );
    delete pRes;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimatedTest::TestDeserialization()
{
    NDb::AnimatedResource1* pRes = CreateResource<NDb::AnimatedResource1>(
        "<AnimatedResource1>"                                                                                                                                                                                                           \
        "  <_int Animated=\"True\">"                                                                                                                                                                                            \
        "    <Type>None</Type>"                                                                                                                                                                                                     \
        "    <Values>"                                                                                                                                                                                                                      \
        "      <Item>"                                                                                                                                                                                                                      \
        "        <Key>0</Key>"                                                                                                                                                                                                      \
        "        <Value>12</Value>"                                                                                                                                                                                             \
        "      </Item>"                                                                                                                                                                                                                     \
        "    </Values>"                                                                                                                                                                                                                     \
        "  </_int>"                                                                                                                                                                                                                             \
        "</AnimatedResource1>" );
    TS_ASSERT_EQUALS( pRes->_int.IsAnimated(), false );
    TS_ASSERT_EQUALS( pRes->_int, 12 );
    delete pRes;

    pRes = CreateResource<NDb::AnimatedResource1>(
        "<AnimatedResource1>"                                                                                                                                                                                                           \
        "  <_int Animated=\"True\">"                                                                                                                                                                                            \
        "    <Type>Wrap</Type>"                                                                                                                                                                                                     \
        "    <Values>"                                                                                                                                                                                                                      \
        "      <Item>"                                                                                                                                                                                                                      \
        "        <Key>0</Key>"                                                                                                                                                                                                      \
        "        <Value>12</Value>"                                                                                                                                                                                             \
        "      </Item>"                                                                                                                                                                                                                     \
        "      <Item>"                                                                                                                                                                                                                      \
        "        <Key>10</Key>"                                                                                                                                                                                                     \
        "        <Value>120</Value>"                                                                                                                                                                                            \
        "      </Item>"                                                                                                                                                                                                                     \
        "    </Values>"                                                                                                                                                                                                                     \
        "  </_int>"                                                                                                                                                                                                                             \
        "</AnimatedResource1>" );
    TS_ASSERT_EQUALS( pRes->_int.IsAnimated(), true );
    TS_ASSERT_EQUALS( pRes->_int, 12 );
    delete pRes;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimatedTest::TestLinearAlgorithms()
{
    NDb::AnimatedResource1* pRes = CreateResource<NDb::AnimatedResource1>(
        "<AnimatedResource1>"                                                                                                                                                                                                           \
        "  <_int Animated=\"True\">"                                                                                                                                                                                            \
        "    <Type>Clamp</Type>"                                                                                                                                                                                                    \
        "    <Values>"                                                                                                                                                                                                                      \
        "      <Item>"                                                                                                                                                                                                                      \
        "        <Key>0</Key>"                                                                                                                                                                                                      \
        "        <Value>20</Value>"                                                                                                                                                                                             \
        "      </Item>"                                                                                                                                                                                                                     \
        "      <Item>"                                                                                                                                                                                                                      \
        "        <Key>10</Key>"                                                                                                                                                                                                     \
        "        <Value>50</Value>"                                                                                                                                                                                             \
        "      </Item>"                                                                                                                                                                                                                     \
        "      <Item>"                                                                                                                                                                                                                      \
        "        <Key>30</Key>"                                                                                                                                                                                                     \
        "        <Value>60</Value>"                                                                                                                                                                                             \
        "      </Item>"                                                                                                                                                                                                                     \
        "    </Values>"                                                                                                                                                                                                                     \
        "  </_int>"                                                                                                                                                                                                                             \
        "</AnimatedResource1>" );
    TS_ASSERT_EQUALS( pRes->_int.IsAnimated(), true );
    TS_ASSERT_EQUALS( pRes->_int.GetValue( 0 ), 20 );
    TS_ASSERT_EQUALS( pRes->_int.GetValue( 10 ), 50 );
    TS_ASSERT_EQUALS( pRes->_int.GetValue( 30 ), 60 );
    
    TS_ASSERT_EQUALS( pRes->_int.GetValue( 5 ), 35 );
    TS_ASSERT_EQUALS( pRes->_int.GetValue( 9 ), 47 );
    TS_ASSERT_EQUALS( pRes->_int.GetValue( 20 ), 55 );
    TS_ASSERT_EQUALS( pRes->_int.GetValue( 29 ), 59 );
    
    delete pRes;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimatedTest::TestDiscreteAlgorithms()
{
    NDb::AnimatedResource1* pRes = CreateResource<NDb::AnimatedResource1>(
        "<AnimatedResource1>"                                                                                                                                                                                                           \
        "  <_string Animated=\"True\">"                                                                                                                                                                                     \
        "    <Type>Clamp</Type>"                                                                                                                                                                                                    \
        "    <Values>"                                                                                                                                                                                                                      \
        "      <Item>"                                                                                                                                                                                                                      \
        "        <Key>0</Key>"                                                                                                                                                                                                      \
        "        <Value>Revival</Value>"                                                                                                                                                                                    \
        "      </Item>"                                                                                                                                                                                                                     \
        "      <Item>"                                                                                                                                                                                                                      \
        "        <Key>10</Key>"                                                                                                                                                                                                     \
        "        <Value>Radio</Value>"                                                                                                                                                                                      \
        "      </Item>"                                                                                                                                                                                                                     \
        "      <Item>"                                                                                                                                                                                                                      \
        "        <Key>30</Key>"                                                                                                                                                                                                     \
        "        <Value>Music Festival</Value>"                                                                                                                                                                     \
        "      </Item>"                                                                                                                                                                                                                     \
        "    </Values>"                                                                                                                                                                                                                     \
        "  </_string>"                                                                                                                                                                                                                      \
        "</AnimatedResource1>" );
    TS_ASSERT_EQUALS( pRes->_string.IsAnimated(), true );
    TS_ASSERT_EQUALS( pRes->_string.GetValue( 0 ), "Revival" );
    TS_ASSERT_EQUALS( pRes->_string.GetValue( 10 ), "Radio" );
    TS_ASSERT_EQUALS( pRes->_string.GetValue( 30 ), "Music Festival" );
    
    TS_ASSERT_EQUALS( pRes->_string.GetValue( 5 ), "Revival" );
    TS_ASSERT_EQUALS( pRes->_string.GetValue( 9 ), "Revival" );
    TS_ASSERT_EQUALS( pRes->_string.GetValue( 20 ), "Radio" );
    TS_ASSERT_EQUALS( pRes->_string.GetValue( 29 ), "Radio" );
    
    delete pRes;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimatedTest::TestDiscreteChanges()
{
    NDb::AnimatedResource1* pRes = CreateResource<NDb::AnimatedResource1>(
        "<AnimatedResource1>"                                                                                                                                                                                                           \
        "  <_floats Animated=\"True\">"                                                                                                                                                                                     \
        "    <Type>Clamp</Type>"                                                                                                                                                                                                    \
        "    <Values>"                                                                                                                                                                                                                      \
        "        <Item>"                                                                                                            \
        "            <Key>0</Key>"                                                                                                    \
        "            <Value>0</Value>"                                                                                                \
        "        </Item>"                                                                                                           \
        "        <Item>"                                                                                                            \
        "            <Key>5</Key>"                                                                                                    \
        "            <Value>0</Value>"                                                                                              \
        "        </Item>"                                                                                                           \
        "        <Item>"                                                                                                            \
        "            <Key>5</Key>"                                                                                                    \
        "            <Value>1.2</Value>"                                                                                              \
        "        </Item>"                                                                                                           \
        "        <Item>"                                                                                                            \
        "            <Key>10</Key>"                                                                                                   \
        "            <Value>1.2</Value>"                                                                                              \
        "        </Item>"                                                                                                           \
        "    </Values>"                                                                                                                                                                                                                     \
        "  </_floats>"                                                                                                                                                                                                                      \
        "</AnimatedResource1>" );

    TS_ASSERT_EQUALS( pRes->_floats.IsAnimated(), true );
    TS_ASSERT_EQUALS( pRes->_floats.GetValue( 0 ), 0.0f );
    TS_ASSERT_EQUALS( pRes->_floats.GetValue( 2.5f ), 0.0f );
    TS_ASSERT_EQUALS( pRes->_floats.GetValue( 4.9f ), 0.0f );
    TS_ASSERT_EQUALS( pRes->_floats.GetValue( 5.0f ), 1.2f );
    TS_ASSERT_EQUALS( pRes->_floats.GetValue( 5.1f ), 1.2f );
    TS_ASSERT_EQUALS( pRes->_floats.GetValue( 7.5f ), 1.2f );
    TS_ASSERT_EQUALS( pRes->_floats.GetValue( 9.9f ), 1.2f );
    
    delete pRes;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CXX_REGISTER_TEST_SUITE( AnimatedTest )
{
    CXX_REGISTER_TEST_FUNCTION( TestBackwardCompatibility );
    CXX_REGISTER_TEST_FUNCTION( TestDeserialization );
    CXX_REGISTER_TEST_FUNCTION( TestLinearAlgorithms );
    CXX_REGISTER_TEST_FUNCTION( TestDiscreteAlgorithms );
    CXX_REGISTER_TEST_FUNCTION( TestBackwardCompatibilityVec3 );
    CXX_REGISTER_TEST_FUNCTION( TestDiscreteChanges );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( AnimatedResource1 );
