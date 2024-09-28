import testing.*;

//use FlashAssert(bool expression, string message) for assert

function testcase1():void
{
  FlashAssert(true, "succeed test");
}

function testcase2():void
{                                                           	
  FlashAssert(false, "failed test");
}

var testSuit: TestingFacility = new TestingFacility();

testSuit.AddTest(testcase1, "testcase1");
testSuit.AddTest(testcase2, "testcase2");

testSuit.RunTests();
