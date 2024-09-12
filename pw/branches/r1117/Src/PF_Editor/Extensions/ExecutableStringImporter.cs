using System;
using System.Collections.Generic;
using System.Text;
using EditorLib;
using EditorLib.Operations;
using libdb;
using libdb.DB;
using DBTypes;
using EditorLib.Extensions;
using System.Reflection;
using System.Runtime.InteropServices; // DllImport

namespace PF_Editor
{
  //@Ivn@TODO: waiting for structure inheritance and merge these 3 importers into one
  [ApplicableForDeriverAttribute]
  public sealed class ExecutableFloatStringSpellImporter : StructImporter<Spell, ExecutableFloatString>
  {
    [DllImport("FormulaBuilder.dll", CallingConvention = CallingConvention.StdCall)]
    public static extern int BuildFormula(string cpFormula, [MarshalAs(UnmanagedType.LPStr)] StringBuilder buf, int nMaxCount, string cpReturnType, int altSecond);
    protected override bool KnownDuration { get { return false; } }
    protected override bool Process(ExecutableFloatString importStruct, DBPtr<Spell> resource, IEditorCommonApplication application, bool fast)
    {
      int nSize = 4096 * 2;
      StringBuilder sb = new StringBuilder(nSize);
      while (0 == BuildFormula(importStruct.sString, sb, sb.Capacity, importStruct.returnType, 0))
      {
        nSize *= 2;
        sb = new StringBuilder(nSize);
      }
      importStruct.compiledString = sb.ToString();
      return importStruct.compiledString != "";
    }
  }
  [ApplicableForDeriverAttribute]
  public sealed class ExecutableFloatStringConstantsImporter : StructImporter<UnitConstant, ExecutableFloatString>
  {
    [DllImport("FormulaBuilder.dll", CallingConvention = CallingConvention.StdCall)]
    public static extern int BuildFormula(string cpFormula, [MarshalAs(UnmanagedType.LPStr)] StringBuilder buf, int nMaxCount, string cpReturnType, int altSecond);
    protected override bool KnownDuration { get { return false; } }
    protected override bool Process(ExecutableFloatString importStruct, DBPtr<UnitConstant> resource, IEditorCommonApplication application, bool fast)
    {
      int nSize = 4096 * 2;
      StringBuilder sb = new StringBuilder(nSize);
      while (0 == BuildFormula(importStruct.sString, sb, sb.Capacity, importStruct.returnType, 0))
      {
        nSize *= 2;
        sb = new StringBuilder(nSize);
      }
      importStruct.compiledString = sb.ToString();
      return importStruct.compiledString != "";
    }
  }
  [ApplicableForDeriverAttribute]
  public sealed class ExecutableFloatStringImporter : StructImporter<BaseApplicator, ExecutableFloatString>
  {
    [DllImport("FormulaBuilder.dll", CallingConvention = CallingConvention.StdCall)]
    public static extern int BuildFormula(string cpFormula, [MarshalAs(UnmanagedType.LPStr)] StringBuilder buf, int nMaxCount, string cpReturnType, int altSecond);
    protected override bool KnownDuration { get { return false; } }
    protected override bool Process(ExecutableFloatString importStruct, DBPtr<BaseApplicator> resource, IEditorCommonApplication application, bool fast)
    {
      int nSize = 4096 * 2;
      StringBuilder sb = new StringBuilder(nSize);
      while (0 == BuildFormula(importStruct.sString, sb, sb.Capacity, importStruct.returnType, 0))
      {
        nSize *= 2;
        sb = new StringBuilder(nSize);
      }
      importStruct.compiledString = sb.ToString();
      return importStruct.compiledString != "";
    }
  }
  [ApplicableForDeriverAttribute]
  public sealed class ExecutableIntStringImporter : StructImporter<BaseApplicator, ExecutableIntString>
  {
    [DllImport("FormulaBuilder.dll", CallingConvention = CallingConvention.StdCall)]
    public static extern int BuildFormula(string cpFormula, [MarshalAs(UnmanagedType.LPStr)] StringBuilder buf, int nMaxCount, string cpReturnType, int altSecond);
    protected override bool KnownDuration { get { return false; } }
    protected override bool Process(ExecutableIntString importStruct, DBPtr<BaseApplicator> resource, IEditorCommonApplication application, bool fast)
    {
      int nSize = 4096 * 2;
      StringBuilder sb = new StringBuilder(nSize);
      while (0 == BuildFormula(importStruct.sString, sb, sb.Capacity, importStruct.returnType, 0))
      {
        nSize *= 2;
        sb = new StringBuilder(nSize);
      }
      importStruct.compiledString = sb.ToString();
      return importStruct.compiledString != "";
    }
  }
  [ApplicableForDeriverAttribute]
  public sealed class ExecutableBoolStringImporter : StructImporter<BaseApplicator, ExecutableBoolString>
  {
    [DllImport("FormulaBuilder.dll", CallingConvention = CallingConvention.StdCall)]
    public static extern int BuildFormula(string cpFormula, [MarshalAs(UnmanagedType.LPStr)] StringBuilder buf, int nMaxCount, string cpReturnType, int altSecond);
    protected override bool KnownDuration { get { return false; } }
    protected override bool Process(ExecutableBoolString importStruct, DBPtr<BaseApplicator> resource, IEditorCommonApplication application, bool fast)
    {
      int nSize = 4096 * 2;
      StringBuilder sb = new StringBuilder(nSize);
      while (0 == BuildFormula(importStruct.sString, sb, sb.Capacity, importStruct.returnType, 0))
      {
        nSize *= 2;
        sb = new StringBuilder(nSize);
      }
      importStruct.compiledString = sb.ToString();
      return importStruct.compiledString != "";
    }
  }

  [ApplicableForDeriverAttribute]
  public sealed class ExecutableBooleanStringImporter : StructImporter<BaseApplicator, ExecutableBooleanString>
  {
    [DllImport("FormulaBuilder.dll", CallingConvention = CallingConvention.StdCall)]
    public static extern int BuildFormula(string cpFormula, [MarshalAs(UnmanagedType.LPStr)] StringBuilder buf, int nMaxCount, string cpReturnType, int altSecond);
    protected override bool KnownDuration { get { return false; } }
    protected override bool Process(ExecutableBooleanString importStruct, DBPtr<BaseApplicator> resource, IEditorCommonApplication application, bool fast)
    {
      int nSize = 4096 * 2;
      StringBuilder sb = new StringBuilder(nSize);

      int altSecond = 0;
      string returnType = importStruct.returnType;
      if (returnType == "boolean")
      {
        altSecond = 1;
        returnType = "bool";
      }

      while (0 == BuildFormula(importStruct.sString, sb, sb.Capacity, returnType, altSecond))
      {
        nSize *= 2;
        sb = new StringBuilder(nSize);
      }
      importStruct.compiledString = sb.ToString();
      return importStruct.compiledString != "";
    }
  }

}
