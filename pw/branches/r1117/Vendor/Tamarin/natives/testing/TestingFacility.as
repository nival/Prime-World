package testing
{

class TestInfo
{
  public var test:Function;
  public var name:String;
  public function TestInfo(testFunction:Function, testName:String)
  {
    test = testFunction;
    name = testName;
  }
}

[native(cls="TestingFacilityClass", instance="TestingFacilityObject", methods="auto")]
public class TestingFacility
{
  ///////////////////////////////////////////////////
  public static var currentTestName:String = "not specified";
  public static native function AssertImpl(expression:Boolean, msg:String);
  ///////////////////////////////////////////////////
  

  private var tests:Array = new Array();
    
  public function AddTest(test:Function, testName:String  = "Test name not specified"):void
  {
    tests.push(new TestInfo(test, testName));
  }
  
  private function RunSingleTest(item:*, index:int, array:Array):void
  {
    var test:Function = item.test;
    currentTestName = item.name;
    test.call(test);
  }
  
  public function RunTests():void
  {
    tests.forEach(RunSingleTest);
  }
}


public function FlashAssert(expression:Boolean, msg:String)
{
  TestingFacility.AssertImpl(expression, TestingFacility.currentTestName + " : " + msg);
}

}