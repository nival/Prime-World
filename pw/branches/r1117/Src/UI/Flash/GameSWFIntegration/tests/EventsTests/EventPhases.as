import flash.events.*;
import flash.display.*;
import testing.*;

//this file is without test suit. cause its a simple use case

var sprite:Sprite = new Sprite();
var spriteParent:Sprite = new Sprite();
var spriteGrandParent:Sprite = new Sprite();
spriteGrandParent.addChild(spriteParent);
spriteParent.addChild(sprite);
			  			  		  
			  
spriteParent.addEventListener("SomeType", listenerParent);
spriteGrandParent.addEventListener("SomeType", listenerGrand, true);
sprite.addEventListener("SomeType", listener);

var eventCapture:Boolean = false;						  			  		  
var eventBubling:Boolean = false;						  			  		  
var eventAtTarget:Boolean = false;						  			  		  

sprite.dispatchEvent(new Event("SomeType", true));
            
function listenerParent(event:Event):void
{
  eventBubling = true;							  			  		 
}
            
function listenerGrand(event:Event):void
{
  eventCapture = true;						  			  		 
}

function listener(event:Event):void
{
  eventAtTarget = true;						  			  		 
}

FlashAssert(eventCapture, "capturing phase");
FlashAssert(eventAtTarget, "at target phase");
FlashAssert(eventBubling, "bubling phase");


