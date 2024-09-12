using System;
using System.Collections.Generic;
using System.ComponentModel;
using Scene.DBScene;
using libdb.DB;
using PF_Core.DBEffect;
using PF_GameLogic.DBStats;
using PF_GameLogic.DBUnit;

namespace PF_GameLogic.DBAbility
{
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // ExecutableString
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  [NoCode]
  [NonTerminal]
  [DBVersion( 21 )] // this DBVersion manually duplicated in FormulaPars.h under #define FORMULA_VERSION
  [Custom( "Social" )]
  public class BaseExecutableString 
  {
    public string sString = "0";

    [ReadOnly( true )] 
    public string compiledString = string.Empty;

    [Abstract]
    [ReadOnly(true)]
    public string returnType;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [NoCode]
  [Custom( "Social" )]
  public class ExecutableFloatString : BaseExecutableString
  {
    public new string returnType = "float";

    public ExecutableFloatString( string sStr )
    {
      sString = sStr;
    }

    public ExecutableFloatString()
    {
    }
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [NoCode]
  [Custom( "Social" )]
  public class ExecutableIntString : BaseExecutableString
  {
    public new string returnType = "int";

    public ExecutableIntString(string sStr)
    {
      sString = sStr;
    }

    public ExecutableIntString()
    {
    }
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [NoCode]
  [Custom("Social")]
  public class ExecutableBoolString : BaseExecutableString
  {
    public new string returnType = "bool";

    public ExecutableBoolString(string sStr)
    {
      sString = sStr;
    }

    public ExecutableBoolString()
    {
      sString = "false";
    }
  }

  [NoCode]
  [Custom("Social")]
  public class ExecutableBooleanString : BaseExecutableString
  {
    public new string returnType = "boolean";

    public ExecutableBooleanString(string sStr)
    {
      sString = sStr;
    }

    public ExecutableBooleanString()
    {
      sString = "false";
    }
  }


  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Default formulas
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xF664BC9)]
  [UseTypeName("DFSC")]
  public class DefaultFormulas : DBResource
  {
    public List<ExecutableFloatString> floatFormulas = new List<ExecutableFloatString>();
    public List<ExecutableBoolString> boolFormulas = new List<ExecutableBoolString>();
    public List<ExecutableIntString> intFormulas = new List<ExecutableIntString>();
  }

  [IndexField("name")]
  [Custom("Social")]
  public class ConditionFormula : DBResource
  {
    public string name = string.Empty;
    public ExecutableBoolString condition = new ExecutableBoolString("true");
  }
}
