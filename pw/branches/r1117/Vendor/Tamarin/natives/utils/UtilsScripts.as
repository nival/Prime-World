package flash.utils
{

  //Cancels a specified setInterval() call.
  [native("UtilsScripts::clearInterval")]
  public native function clearInterval(id:uint):void;
  
   	 	
  //Cancels a specified setTimeout() call.
  [native("UtilsScripts::clearTimeout")]
  public native function clearTimeout(id:uint):void;
  
   	 	
  //Produces an XML object that describes the ActionScript object named as the parameter of the method.
  [native("UtilsScripts::describeType")]
  public native function describeType(value:*):XML;
  
   	 	
  //Returns an escaped copy of the input string encoded as either UTF-8 or system code page, depending on the value of System.useCodePage.
  [native("UtilsScripts::escapeMultiByte")]
  public native function escapeMultiByte(value:String):String;
  
   	 	
  //Returns a reference to the class object of the class specified by the name parameter.
  [native("UtilsScripts::getDefinitionByName")]
  public native function getDefinitionByName(name:String):Object;
  
   	 	
  //Returns the fully qualified class name of an object.
  [native("UtilsScripts::getQualifiedClassName")]
  public native function getQualifiedClassName(value:*):String;
  
   	 	
  //Returns the fully qualified class name of the base class of the object specified by the value parameter.
  [native("UtilsScripts::getQualifiedSuperclassName")]
  public native function getQualifiedSuperclassName(value:*):String;
  
   	 	
  //Used to compute relative time.
  [native("UtilsScripts::getTimer")]
  public native function getTimer():int;
  
   	 	
  //Runs a function at a specified interval (in milliseconds).
  [native("UtilsScripts::setInterval")]
  public native function setInterval(closure:Function, delay:Number, ... arguments):uint;
  
   	 	
  //Runs a specified function after a specified delay (in milliseconds).
  [native("UtilsScripts::setTimeout")]
  public native function setTimeout(closure:Function, delay:Number, ... arguments):uint;
     	 	
  
  //Returns an unescaped copy of the input string, which is decoded from either system code page page or UTF-8 depending on the value of System.useCodePage.
  [native("UtilsScripts::unescapeMultiByte")]
  public native function unescapeMultiByte(value:String):String;

}

package 
{

  [native("UtilsScripts::trace")]
  public native function trace(...s);
}