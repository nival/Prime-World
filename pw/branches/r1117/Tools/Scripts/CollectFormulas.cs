/*
#about Пройтись по формулам прописать id и сгенерить файлы AllFormulas.h/cpp 
#ref PF_Types.DBTypes.dll
*/
using System;
using System.Collections;
using System.Collections.Generic;
using DBTypes;
using libdb.DB;
using libdb.IO;
using libdb.Diagnostics;
using EditorLib;
using EditorLib.IO;
using EditorLib.Plugin;
using System.Text;
using System.Globalization;
using System.Runtime.InteropServices;

namespace Scripts
{
    public class FormulaImporter
    {
        [DllImport("FormulaBuilder.dll", CallingConvention = CallingConvention.StdCall)]
        public static extern int PrepareFormula(string cpFormula, [MarshalAs(UnmanagedType.LPStr)] StringBuilder buf, int nMaxCount, string cpReturnType);

        public static int formulaId = 0;
        public static StringBuilder cppText = new StringBuilder("#include \"stdafx.h\"\r\n\r\n#include <math.h>\r\n#include \"AllFormulas.h\"\r\n\r\n#pragma warning(push)\r\n#pragma warning(disable: 4305)\r\n\r\n");
        public static StringBuilder hText = new StringBuilder("#pragma once\r\n\r\n#include \"../../Data/GameLogic/FormulaPars.h\"\r\n\r\nstruct AllFormulas\r\n{\r\n\r\n");
        public static string cppTextEnd =
@"}

void* AllFormulas::GetFormula(string formulaString)
{
  if ( instance == 0 )
  {
    instance = new AllFormulas;
  }

  hash_map<string, void*>::iterator it = formulas.find( formulaString );

  if ( it != formulas.end() )
  {
    return it->second;
  }

  return 0;
}

hash_map<string, void*> AllFormulas::formulas;
AllFormulas* AllFormulas::instance = 0;
";

        public static string hTextEnd =
@"static void* GetFormula(string formulaString);
private:
  AllFormulas();
  static hash_map<string, void*> formulas;
  static AllFormulas* instance;
};
";
        public static StringBuilder cppHashesText = new StringBuilder("\r\nAllFormulas::AllFormulas()\r\n{\r\n");
        public static string cppHashInsert = "  formulas.insertUnique( \"{0}\", abilityFunctor{1} );\r\n";

        public static string allFormulas = "AllFormulas::";

        public static string abilityFunctorDeclaration = "static {0} abilityFunctor{1}(IUnitFormulaPars const *pFirst, IUnitFormulaPars const *pSecond, IMiscFormulaPars const *pMisc);\r\n";

        private static string strAFText = "abilityFunctor";

        public class FormulaGatherer<T>
        {
            private static Dictionary<string, string> formulaCache = new Dictionary<string, string>();
            private static Dictionary<string, int> idsCache = new Dictionary<string, int>();

            public bool Functor(ref T obj)
            {
                DBTypes.BaseExecutableString execString = obj as DBTypes.BaseExecutableString;
                if (execString == null || (execString.HasParent() && execString.IsDerivedFromParent()))
                    return true;

                string cacheKey = execString.sString + execString.returnType;
                string formula;
                int currentId;
                if (!formulaCache.TryGetValue(cacheKey, out formula))
                {
                    StringBuilder sb = new StringBuilder(8192);
                    while (PrepareFormula(execString.sString, sb, sb.Capacity, execString.returnType) == 0)
                        sb = new StringBuilder(sb.Capacity * 2);

                    formula = sb.ToString();
                    formulaCache[cacheKey] = formula;

                    int namePos = formula.IndexOf(strAFText);
                    int declPos = namePos + strAFText.Length;

                    formula = formula.Insert(declPos, formulaId.ToString()); // place id after name
                    formula = formula.Insert(namePos, allFormulas); // place AllFormulas:: before name
                    formula = formula.Replace("f2l", "(int)"); // no f2l in source code!!!

                    currentId = formulaId;

                    string declName = string.Format(abilityFunctorDeclaration, execString.returnType, currentId);

                    cppText.Append(formula);
                    hText.Append(declName);

                    string hashString = cacheKey.Replace( "\n", "\\r\\n" );
                    hashString = hashString.Replace( "\"", "\\\"" );

                    hashString = string.Format(cppHashInsert, hashString, currentId);
                    cppHashesText.Append(hashString);
                    formulaId++;
                }

                return true;
            }
        }

        public IEnumerable Main( EditorLib.IEditorCommonApplication application )
        {
            List<DBID> dbids = new List<DBID>();
            DateTime start = DateTime.Now;
            {
                Log.TraceMessage("Loading database... ");
                ObjectsSelector.CollectObjects(application, string.Empty, typeof(DBResource), true, true, out dbids);
            }

            FieldsWalker.DepthController depth = new FieldsWalker.DepthController(0, FieldsWalker.ObjectType.DBPtr, FieldsWalker.ObjectType.All);
            FormulaGatherer<DBTypes.ExecutableFloatString> floatImport = new FormulaGatherer<DBTypes.ExecutableFloatString>();
            FormulaGatherer<DBTypes.ExecutableBoolString> boolImport = new FormulaGatherer<DBTypes.ExecutableBoolString>();
            FormulaGatherer<DBTypes.ExecutableIntString> intImport = new FormulaGatherer<DBTypes.ExecutableIntString>();
            DateTime logTime = DateTime.Now + TimeSpan.FromSeconds(1.0);
            Log.TraceMessage("Generating cpp text...");
            for (int i = 0; i < dbids.Count; ++i)
            {
                if (i == dbids.Count - 1 || DateTime.Now > logTime)
                {
                    logTime = DateTime.Now + TimeSpan.FromSeconds(5.0);
                    Log.TraceMessage("{0} ({1}%)", dbids[i], i * 100 / dbids.Count);
                }

                var resource = DataBase.Get<DBResource>(dbids[i]).Get();
                FieldsWalker.VisitFields<DBTypes.ExecutableFloatString>(resource, floatImport.Functor, depth.Functor);
                FieldsWalker.VisitFields<DBTypes.ExecutableBoolString>(resource, boolImport.Functor, depth.Functor);
                FieldsWalker.VisitFields<DBTypes.ExecutableIntString>(resource, intImport.Functor, depth.Functor);
            }
            Log.TraceMessage("Generating cpp text finished in {0:F0}s", (DateTime.Now - start).TotalSeconds);

            System.IO.Stream stream = application.FileSystem.CreateFile("../Src/PF_GameLogic/AllFormulas.cpp");

            cppText.Append("#pragma warning(pop)\r\n");
            cppText.Append(cppHashesText);
            cppText.Append(cppTextEnd);

            byte[] data = Encoding.UTF8.GetBytes(cppText.ToString());
            stream.Write(data, 0, data.Length);

            stream.Close();

            hText.Append(hTextEnd);

            stream = application.FileSystem.CreateFile("../Src/PF_GameLogic/AllFormulas.h");

            data = Encoding.UTF8.GetBytes( hText.ToString() );
            stream.Write(data, 0, data.Length);

            stream.Close();

            yield return true;
        }
    }
}
