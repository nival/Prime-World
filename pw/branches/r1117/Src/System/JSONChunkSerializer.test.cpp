//!Component("System/JSONSerializer")
//!Component("System/Commands")

#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include "System/TestAssertDumper.h"
#include "FileSystem/FileUtils.h"
#include "System/JSONSerializer.h"

const char* fileName = "test.json";

class SubTest : public CObjectBase
{
  OBJECT_METHODS( 0x9D6BBBC3, SubTest );

  JDATA
  list<unsigned> floats;
  //float floats;
  
public:
  JEND int operator&( IJsonSerializerBase &f )
	{ 
		f.Add("floats",&floats); 
		return 0; 
	}

  SubTest() {}
  SubTest(float ff) 
  {
    for(int i=0; i<5; ++i)
      floats.push_back(i*2.5 + ff);
  }

  bool operator==( const SubTest& other) 
  {
    return floats.size() == other.floats.size();
  }

friend class TestJson;
};

class SubTestMT : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( SubTestMT, BaseObjectMT );

  JDATA
    
  float somePropery;

public:
  JEND int operator&( IJsonSerializerBase &f )
	{ 
		f.Add("somePropery",&somePropery); 
		return 0; 
	}

  SubTestMT() : somePropery(0.0f) {}

  SubTestMT(float f) : somePropery(f) {}

  bool operator==( const SubTestMT& other) 
  {
    return somePropery == other.somePropery;
  }
friend class TestJson;
};


class SubTestST : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( SubTestST, BaseObjectST );

  JDATA

  int someIntPropery;

public:
  JEND int operator&( IJsonSerializerBase &f )
	{ 
		f.Add("someIntPropery",&someIntPropery); 
		return 0; 
	}

  SubTestST() : someIntPropery(0) {}

  SubTestST(int d) : someIntPropery(d) {}

  bool operator==( const SubTestST& other) 
  {
    return someIntPropery == other.someIntPropery;
  }
friend class TestJson;
};

class TestJson : public CObjectBase
{
  OBJECT_METHODS( 0x9D6BBBC3, TestJson );

  JDATA
  vector<SubTest> ints;
  SubTest sub;
  CObj<SubTest> pSubTest;
  CPtr<SubTest> pSubTest2;
  StrongMT<SubTestMT> pStrongSub;
  WeakMT<SubTestMT> pWeakSub;

  Strong<SubTestST> pStrongSubST;
  Weak<SubTestST> pWeakSubST;
  string testStr;

  int b,b1;
  float d;
  
public:
  JEND int operator&( IJsonSerializerBase &f )
	{ 
		f.Add("ints",&ints); 
		f.Add("sub",&sub); 
		f.Add("pSubTest",&pSubTest); 
		f.Add("pSubTest2",&pSubTest2); 
		f.Add("pStrongSub",&pStrongSub); 
		f.Add("pWeakSub",&pWeakSub); 
		f.Add("pStrongSubST",&pStrongSubST); 
		f.Add("pWeakSubST",&pWeakSubST); 
		f.Add("testStr",&testStr); 
		f.Add("b",&b); 
		f.Add("b1",&b1); 
		f.Add("d",&d); 
		return 0; 
	}
	
  TestJson() : b(0), d(0.0f) {}
  TestJson( int _b, float _d ) : b(_b), d(_d) 
  {
    pSubTest = new SubTest(77);
    pSubTest2 = pSubTest;
    pStrongSub = new SubTestMT(-10.6f);
    pWeakSub = pStrongSub;

    pStrongSubST = new SubTestST(-777);
    pWeakSubST = pStrongSubST;

    testStr = "test string тестовая строка";

    for(int i=0; i < 5; i++) 
      ints.push_back(SubTest(i*10 + 2.45));
  }

  bool operator==( const TestJson& other) 
  {
    bool res = other.b == b;
    res = res && other.d == d; 
    res = res && *pSubTest == *other.pSubTest;
    res = res && *pSubTest2 == *other.pSubTest2;
    res = res && *pStrongSub == *other.pStrongSub;
    res = res && *pWeakSub.Lock() == *other.pStrongSub;
    res = res && *pStrongSubST == *other.pStrongSubST;
    res = res && *pWeakSubST == *other.pWeakSubST;
    res = res && testStr == other.testStr;
    res = res && ints.size() == other.ints.size();
    return res; 
  }
};

TestJson testOrg(10, 14.5f);

struct Test_JSONChunkSerializer : public CxxTest::TestSuite
{
  void test_read()
  {

    StrongMT<JsonSerializer> pJsonLoader = new JsonSerializer();
    pJsonLoader->SerializeToFile(fileName, &testOrg);

    TestJson test;

    pJsonLoader->SerializeFromFile(fileName, &test);

    TS_ASSERT( test == testOrg );  
  }
};
