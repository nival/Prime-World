import testing.*;

var firstChildCtorWasCalled: Boolean = false;

class EmptyClass extends Object
{
    public function EmptyClass()
    {}
}

class TestClass
{
  public function TestFunc():void
  {

    var emptyClass: EmptyClass = new EmptyClass();

    //should be crush here
    emptyClass.nonExistProp = true;
  }
}

var testObj: TestClass = new TestClass();


testObj.TestFunc();





