import flash.events.*;
import flash.display.*;
import testing.*;

//Setup data. TODO: consider to move it into test suit functionality
var parent: DisplayObjectContainer = new DisplayObjectContainer();
var child1: DisplayObject = new DisplayObject();
var child2: DisplayObject = new DisplayObject();
var child3: DisplayObject = new DisplayObject();
			
child1.name = "child1";
child2.name = "child2";
child3.name = "child3";

parent.addChild(child1);
parent.addChild(child2);
parent.addChild(child3);

FlashAssert( parent.contains(child1), "child1 isnt here");
FlashAssert( parent.contains(child2), "child2 isnt here");
FlashAssert( parent.contains(child3), "child3 isnt here");
			
//verifies work with indexes      
function TestIndex():void
{
  parent.swapChildrenAt(parent.getChildIndex(child1), parent.getChildIndex(child3));
  FlashAssert(  parent.getChildIndex(child1) == 2 && parent.getChildIndex(child3) == 0, "children swap indexes");
					
  parent.swapChildren(child1, child3);
  FlashAssert(  parent.getChildIndex(child1) == 0 && parent.getChildIndex(child3) == 2, "children revert indexes");
			
  parent.setChildIndex(child1, 2);
  FlashAssert(  parent.getChildIndex(child1) == 2 , "setIndex::wrong child1 index");
  FlashAssert(  parent.getChildIndex(child2) == 0 , "setIndex::wrong child2 index");
  FlashAssert(  parent.getChildIndex(child3) == 1 , "setIndex::wrong child3 index");
			
  parent.setChildIndex(child1, 0);
  FlashAssert(  parent.getChildIndex(child1) == 0 , "child1 Index is wrong");
  FlashAssert(  parent.getChildIndex(child2) == 1 , "child2 Index is wrong");
  FlashAssert(  parent.getChildIndex(child3) == 2 , "child3 Index is wrong");


  FlashAssert(  parent.getChildIndex(parent.getChildAt(2)) == 2 , "getChild is incorrect");		
}

//verifies add/remove logic
function TestAddRemove():void
{
  FlashAssert(parent.getChildByName("child1") == child1, "getChildByName");
  FlashAssert(parent.getChildIndex(child2) == 1, "child2 index is not 1");

  FlashAssert(parent.removeChildAt(1) == child2, "removeChildAt");
  FlashAssert(parent.getChildIndex(child3) == 1 && !parent.contains(child2) , "removeChild failed");
  parent.addChildAt(child2, 1); 			
			
  FlashAssert(parent.getChildIndex(child2) == 1 && parent.contains(child2) , "addChildAt");
			
  parent.removeChild(child3);
  FlashAssert(!parent.contains(child3) , "removeChild");
  FlashAssert(!child3.parent , "parent was reseted");
			
  parent.addChild(child3);
  FlashAssert(parent.contains(child3) , "addChild");
  FlashAssert(parent.getChildIndex(child3) == 2  , "child was inserted on the wrong position");
}


//verifies that parenting changes while adding to another container
function TestParenting():void
{ 
  FlashAssert(child1.parent == parent && parent.contains(child1), "child1.parent");
  var parent2: DisplayObjectContainer = new DisplayObjectContainer();
  parent2.addChild(child1);
  
  FlashAssert(child1.parent == parent2 && parent2.contains(child1), "child1.parent now parent2");
  FlashAssert(!parent.contains(child1), "parent contains child1");
  
  parent.addChildAt(child1,0);
}

var testSuit: TestingFacility = new TestingFacility();

testSuit.AddTest(TestIndex, "TestIndex");
testSuit.AddTest(TestAddRemove, "TestAddRemove");
testSuit.AddTest(TestParenting, "TestParenting");


testSuit.RunTests();
