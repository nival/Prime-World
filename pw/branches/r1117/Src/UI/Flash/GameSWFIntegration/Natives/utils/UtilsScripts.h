#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"

namespace avmplus
{

class UtilsScripts
{
public:
  //Cancels a specified setInterval() call.
  static void clearInterval(ScriptObject* self, uint id);

  //Cancels a specified setTimeout() call.
  static void clearTimeout(ScriptObject* self, uint id);

  //Produces an XML object that describes the ActionScript object named as the parameter of the method.
  static XMLObject * describeType(ScriptObject* self, AvmBox value);

  //Returns an escaped copy of the input string encoded as either UTF-8 or system code page, depending on the value of System.useCodePage.
  static AvmString escapeMultiByte(ScriptObject* self, AvmString value);

  //Returns a reference to the class object of the class specified by the name parameter.
  static AvmBox getDefinitionByName(ScriptObject* self, AvmString name);

  //Returns the fully qualified class name of an object.
  static AvmString getQualifiedClassName(ScriptObject* self, AvmBox value);

  //Returns the fully qualified class name of the base class of the object specified by the value parameter.
  static AvmString getQualifiedSuperclassName(ScriptObject* self, AvmBox value);

  //Used to compute relative time.
  static int getTimer(ScriptObject* self);

  //Runs a function at a specified interval (in milliseconds).
  static uint setInterval(ScriptObject* self, FunctionObject* closure, double delay, AvmBox arguments);

  //Runs a specified function after a specified delay (in milliseconds).
  static uint setTimeout(ScriptObject* self, FunctionObject* closure, double delay, AvmBox arguments);

  //Returns an unescaped copy of the input string, which is decoded from either system code page page or UTF-8 depending on the value of System.useCodePage.
  static AvmString unescapeMultiByte(ScriptObject* self, AvmString value);

  static AvmBox trace( ScriptObject* self, AvmBox* argv, int argc );
};

}



