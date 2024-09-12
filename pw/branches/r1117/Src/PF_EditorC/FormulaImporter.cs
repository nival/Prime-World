using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using EditorLib;
using EditorLib.IO;
using EditorLib.Plugin;
using libdb.DB;
using libdb.Diagnostics;

namespace PF_EditorC.Extensions
{
  public static class FormulaBuilder
  {
    [DllImport("FormulaBuilder.dll", CallingConvention = CallingConvention.StdCall)]
    public static extern int BuildFormula(string cpFormula, [MarshalAs(UnmanagedType.LPStr)] StringBuilder buf, int nMaxCount, string cpReturnType, int altSecond);
  }

  public sealed class FormulaGatherer<T>
  {
    class DefaultFormulaImporter<U> where U: T
    {

      static DBPtr<DBTypes.DefaultFormulas> defaulFormulas;

      private static string MakeKey<UU>(UU execString) where UU : DBTypes.BaseExecutableString 
      {
        return execString.sString + execString.returnType;
      }

      private static void ImportFloat(ref Dictionary<string, string> storage)
      {
        var formulaList = defaulFormulas.Get().floatFormulas;
        foreach (var formula in formulaList)
        {
          string key = MakeKey(formula);
          storage[key] = formula.compiledString;
        }
      }

      private static void ImportFloat(ref List<string> storage)
      {
        var formulaList = defaulFormulas.Get().floatFormulas;
        foreach (var formula in formulaList)
        {
          string key = MakeKey(formula);
          storage.Add(key);
        }
      }

      private static void ImportBool(ref Dictionary<string, string> storage)
      {
        var formulaList = defaulFormulas.Get().boolFormulas;
        foreach (var formula in formulaList)
        {
          string key = MakeKey(formula);
          storage[key] = formula.compiledString;
        }
      }

      private static void ImportBool(ref List<string> storage)
      {
        var formulaList = defaulFormulas.Get().boolFormulas;
        foreach (var formula in formulaList)
        {
          string key = MakeKey(formula);
          storage.Add(key);
        }
      }

      private static void ImportInt(ref Dictionary<string, string> storage)
      {
        var formulaList = defaulFormulas.Get().intFormulas;
        foreach (var formula in formulaList)
        {
          string key = MakeKey(formula);
          storage[key] = formula.compiledString;
        }
      }

      private static void ImportInt(ref List<string> storage)
      {
        var formulaList = defaulFormulas.Get().intFormulas;
        foreach (var formula in formulaList)
        {
          string key = MakeKey(formula);
          storage.Add(key) ;
        }
      }

      public static void Import(ref Dictionary<string, string> storage)
      {
        if (!LoadDb())
          return;

        System.Type type = typeof(T);
        if (type == typeof(DBTypes.ExecutableFloatString))
        {
          ImportFloat(ref storage);
        }
        else if (type == typeof(DBTypes.ExecutableBoolString))
        {
          ImportBool(ref storage);
        }
        else if (type == typeof(DBTypes.ExecutableBooleanString))
        {
          ImportBool(ref storage);
        }
        else if (type == typeof(DBTypes.ExecutableIntString))
        {
          ImportInt(ref storage);
        }
      }

      public static void Import(ref List<string> storage)
      {
        if (!LoadDb())
          return;

        System.Type type = typeof(T);
        if (type == typeof(DBTypes.ExecutableFloatString))
        {
          ImportFloat(ref storage);
        }
        else if (type == typeof(DBTypes.ExecutableBoolString))
        {
          ImportBool(ref storage);
        }
        else if (type == typeof(DBTypes.ExecutableBooleanString))
        {
          ImportBool(ref storage);
        }
        else if (type == typeof(DBTypes.ExecutableIntString))
        {
          ImportInt(ref storage);
        }
      }

      private static bool LoadDb()
      {
        defaulFormulas = DataBase.Get<DBTypes.DefaultFormulas>(DBID.FromString("/GameLogic/DefaultFormulas.DFSC"));
        System.Type type = typeof(T);

        if (!defaulFormulas.IsValid)
        {
          Log.TraceError("DefaultFormulas.DFSC not found");
          return false; ;
        }

        return true;
      }
    }

    private static Dictionary<string, string> formulaCache = new Dictionary<string, string>();
    private static List<string> defaultFormuls = new List<string>();
    

    public FormulaGatherer()
    {
      DefaultFormulaImporter<T>.Import(ref formulaCache);
      DefaultFormulaImporter<T>.Import(ref defaultFormuls);
    }

    public bool Functor(ref T obj, bool skipEmptyCS)
    {
      DBTypes.BaseExecutableString execString = obj as DBTypes.BaseExecutableString;
      if ( execString == null || ( execString.HasParent() && execString.IsDerivedFromParent() ) )
        return true;

      int altSecond = 0;
      string returnType = execString.returnType;
      if (returnType == "boolean")
      {
        altSecond = 1;
        returnType = "bool";
      }

      if ( skipEmptyCS && execString.compiledString.Length == 0 )
        return true;

      string cacheKey = execString.sString + execString.returnType;

      if (!defaultFormuls.Contains(cacheKey))
      {
        string formula = string.Empty;
        if (!formulaCache.TryGetValue(cacheKey, out formula))
        {
          StringBuilder sb = new StringBuilder(8192);
          while (FormulaBuilder.BuildFormula(execString.sString, sb, sb.Capacity, returnType, altSecond) == 0)
            sb = new StringBuilder(sb.Capacity * 2);

          formula = sb.ToString();
          formulaCache[cacheKey] = formula;
        }

        execString.compiledString = formula;
      }
      return true;
    }
    public bool Functor(ref T obj)
    {
      return Functor( ref obj, false );
    }
  }

  [CommandName( "importformulas", "", "Import all formulas from database." )]
  public class FormulaImporter : IConsoleCommand
  {

      [CommandArgumentAttribute("root_path", "rp", "")]
      public string root_path = string.Empty;

    public int Execute(IEditorCommonApplication application, string[] parameters)
    {
      List<DBID> dbids = new List<DBID>();
      DateTime start = DateTime.Now;

      if (parameters.Length == 0)
      {
        Log.TraceMessage( "Loading database... " );
        ObjectsSelector.CollectObjects(application, root_path, typeof(DBResource), true, true, out dbids);
      }
      else
      {
        FieldsWalker.DepthController uninlined = new FieldsWalker.DepthController(0, FieldsWalker.ObjectType.DBPtrUninlined, FieldsWalker.ObjectType.All);
        foreach ( string param in parameters )
        {
          var ptr = DataBase.Get<DBResource>( DBID.FromString( param ) );
          if ( ptr == null || ptr.Get() == null )
            continue;
          dbids.Add( ptr.DBId );
          foreach( var link in ptr.GetLinks().Keys )
          {
            if ( link.IsInlined )
              dbids.Add( link );
          }
        }
      }

      FieldsWalker.DepthController depth = new FieldsWalker.DepthController(0, FieldsWalker.ObjectType.DBPtr, FieldsWalker.ObjectType.All);
      FormulaGatherer<DBTypes.ExecutableFloatString> floatImport = new FormulaGatherer<DBTypes.ExecutableFloatString>();
      FormulaGatherer<DBTypes.ExecutableBoolString> boolImport = new FormulaGatherer<DBTypes.ExecutableBoolString>();
      FormulaGatherer<DBTypes.ExecutableIntString> intImport = new FormulaGatherer<DBTypes.ExecutableIntString>();
      FormulaGatherer<DBTypes.ExecutableBooleanString> booleanImport = new FormulaGatherer<DBTypes.ExecutableBooleanString>();
      DateTime logTime = DateTime.Now + TimeSpan.FromSeconds(1.0);
      Log.TraceMessage( "Importing formulas..." );
      for ( int i = 0; i < dbids.Count; ++ i)
      {
        if ( i == dbids.Count - 1 || DateTime.Now > logTime )
        {
          logTime = DateTime.Now + TimeSpan.FromSeconds( 5.0 );
          Log.TraceMessage( "{0} ({1}%)", dbids[i], i * 100 / dbids.Count );
        }

        var resource = DataBase.Get<DBResource>( dbids[i] ).Get();
        FieldsWalker.VisitFields<DBTypes.ExecutableFloatString>( resource, floatImport.Functor, depth.Functor );
        FieldsWalker.VisitFields<DBTypes.ExecutableBoolString>( resource, boolImport.Functor, depth.Functor );
        FieldsWalker.VisitFields<DBTypes.ExecutableIntString>( resource, intImport.Functor, depth.Functor );
        FieldsWalker.VisitFields<DBTypes.ExecutableBooleanString>(resource, booleanImport.Functor, depth.Functor);
      }
      Log.TraceMessage( "Importing formulas finished in {0:F0}s", ( DateTime.Now - start ).TotalSeconds );
     
      Log.TraceMessage( "Store database... " );
      DataBase.Store();

      return 0;
    }
  }
}
