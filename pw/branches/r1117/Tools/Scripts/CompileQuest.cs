/*
#about Компиляция условий для скриптов
#ref PF_Types.DBTypes.dll
#ref SocialTypes.DBTypes.dll
#ref PF_EditorC.exe
#ref EditorPlugins.dll
#ref GOLDEngine.dll
#include CompileQuestUtils.cs
*/
using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using System.Xml;
using EditorLib;
using EditorLib.IO;
using EditorLib.Plugin;
using EditorPlugins.Importer.Texture;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;
using DBTypes;
using System.CodeDom.Compiler;

public class CompileQuest
{
    private const string SocialRootHRef = "/Social.ROOT";

    public IEnumerable Main(IEditorCommonApplication app, string[] parameters)
    {
        string resultCSFilePath = string.Empty;
        string resultPYFilePath = string.Empty;
        string resultDllFilePath = string.Empty;
        string usingFilePath = string.Empty;

        bool isDllMode = false;

        if (parameters.Length == 1) //generate .cs or *.py
        {
            FillFilesPath(parameters[0], ref resultPYFilePath, ref resultCSFilePath);

        }
        else if (parameters.Length == 2) //generate .cs or *.py
        {
            FillFilesPath(parameters[0], ref resultPYFilePath, ref resultCSFilePath);
            FillFilesPath(parameters[1], ref resultPYFilePath, ref resultCSFilePath);
        }
        else if (parameters.Length == 3) //generate .dll
        {
            isDllMode = true;
            resultCSFilePath = Path.Combine(Path.GetTempPath(), Path.GetRandomFileName());
            usingFilePath = parameters[0];
            resultDllFilePath = parameters[1];
            resultPYFilePath = parameters[2];
            if (!File.Exists(usingFilePath))
            {
                Log.TraceError("IScriptData file is not found at {0}", usingFilePath);
                yield return false;
            }
        }
        else
        {
            Log.TraceMessage("Usage for dll generation: PF_EditorC.exe run ../Tools/Scripts/CompileQuest.cs <source IScriptData.cs> <result_dll_path> <python_file>");
            Log.TraceMessage("Usage .cs generation: PF_EditorC.exe run ../Tools/Scripts/CompileQuest.cs <result_cs_path> <result_py_path>");
            yield break;
        }

        if (!CompileQuestUtils.InitGramma())
            yield return false;

        Dictionary<DBID, string> dbIDs = new Dictionary<DBID, string>();
        StringBuilder resultCSCode = new StringBuilder();
        StringBuilder resultPYCode = new StringBuilder();
        FileHeader(resultCSCode, resultPYCode);

        Log.TraceMessage("Processing object {0}...", SocialRootHRef);
        SocialRoot root = DataBase.Get<SocialRoot>(DBID.FromFileName(SocialRootHRef, false));
        if (root == null)
        {
            Log.TraceError("Social root is not found");
            yield return false;
        }
        foreach (var questLine in root.Quests)
        {
            foreach (var quest in questLine.Get().quests)
            {
                foreach (var obj in quest.Get().objectives)
                {
                    var cond = obj.condition.Get();
                    if (cond is ModelDataCondition)
                    {
                        if (dbIDs.ContainsKey(cond.DBId))
                        {
                            Log.TraceMessage("Condition {0} was already processed", cond.DBId);
                        }
                        else
                        {
                            Log.TraceMessage("Processing condition {0}...", cond.DBId);
                            string id = cond.DBId.Name.Replace("-", "_").Replace("/", "_").Replace(".", "_").Replace(":", "_");
                            if (!CompileQuestUtils.FillConditionCode(resultCSCode, resultPYCode, cond as ModelDataCondition, id))
                            {
                                Log.TraceError("Parse failed for {0} condition", cond.DBId);
                            }
                            else
                                dbIDs[cond.DBId] = id;
                        }
                    }
                    cond = obj.autoCompleteCondition.Get();
                    if (cond is ModelDataCondition)
                    {
                        if (dbIDs.ContainsKey(cond.DBId))
                        {
                            Log.TraceMessage("Condition {0} was already processed", cond.DBId);
                        }
                        else
                        {
                            Log.TraceMessage("Processing condition {0}...", cond.DBId);
                            string id = cond.DBId.Name.Replace("-", "_").Replace("/", "_").Replace(".", "_").Replace(":", "_");
                            if (!CompileQuestUtils.FillConditionCode(resultCSCode, resultPYCode, cond as ModelDataCondition, id))
                            {
                                Log.TraceError("Parse failed for {0} condition", cond.DBId);
                            }
                            else
                                dbIDs[cond.DBId] = id;
                        }
                    }
					var repCond = obj.repeatableCondition.Get();
					if (repCond is RepeatableCondition)
					{
						var trigger = repCond.trigger.Get();
						if ( trigger is ModelDataCondition)
						{
							if (dbIDs.ContainsKey(trigger.DBId))
							{
								Log.TraceMessage("Condition {0} was already processed", trigger.DBId);
							}
							else
							{
								Log.TraceMessage("Processing condition {0}...", trigger.DBId);
								string id = trigger.DBId.Name.Replace("-", "_").Replace("/", "_").Replace(".", "_").Replace(":", "_");
								if (!CompileQuestUtils.FillConditionCode(resultCSCode, resultPYCode, trigger as ModelDataCondition, id))
								{
									Log.TraceError("Parse failed for {0} condition", trigger.DBId);
								}
								else
									dbIDs[trigger.DBId] = id;
							}
						}
					}
                }
            }
        }
        FillConditionConnecter(resultCSCode, resultPYCode, dbIDs);
        FileBottom(resultCSCode);
        if (!string.IsNullOrEmpty(resultCSFilePath))
        {
            Log.TraceMessage("Save genereted CS code to {0}...", resultCSFilePath);
            File.WriteAllText(resultCSFilePath, resultCSCode.ToString(), Encoding.GetEncoding(1251));
        }

        if (!string.IsNullOrEmpty(resultPYFilePath.Trim()))
        {
            Log.TraceMessage("Save genereted PY code to {0}...", resultPYFilePath);
            File.WriteAllText(resultPYFilePath, resultPYCode.ToString(), Encoding.GetEncoding(1251));
        }

        if (isDllMode)
        {
            Log.TraceMessage("Compile dll to {0}...", resultDllFilePath);
            if (!CompileForDll(new string[] { resultCSFilePath, usingFilePath }, resultDllFilePath))
                Log.TraceError("Compilation failed");
            File.Delete(resultCSFilePath);
        }

        yield return true;
    }

    private void FillFilesPath(string parameter, ref string resultPYFilePath, ref string resultCSFilePath)
    {
        if (parameter.IndexOf(".py") != -1)
        {
            resultPYFilePath = parameter;
        }
        else
        {
            resultCSFilePath = parameter;
        }
    }

    private bool CompileForDll(string[] files, string resultDllpath)
    {
        CompilerParameters compilerParameters = new CompilerParameters();
        compilerParameters.GenerateInMemory = false;
        compilerParameters.OutputAssembly = resultDllpath;

        CodeDomProvider provider;
        var providerOptions = new Dictionary<string, string> { { "CompilerVersion", "v3.5" } };
        provider = new Microsoft.CSharp.CSharpCodeProvider(providerOptions);
        CompilerResults results = provider.CompileAssemblyFromFile(compilerParameters, files);
        if (results.Errors.HasErrors)
        {
            foreach (CompilerError error in results.Errors)
                Log.TraceError("{0}({1}): {2}: {3}", Path.GetFileName(error.FileName), error.Line, error.ErrorNumber, error.ErrorText);
            return false;
        }
        return true;
    }

    private void FileHeader(StringBuilder csCode, StringBuilder pyCode)
    {
        csCode.AppendLine("// Automatically generated file, don't change it manually!");
        csCode.AppendLine("using System;");
        csCode.AppendLine("using System.Collections.Generic;");
        csCode.AppendLine();
        csCode.AppendLine("namespace QuestConditions");
        csCode.AppendLine("{\r\n\tpublic interface IConditionHelper\r\n\t{");
        csCode.AppendLine("\t\tint Condition( string dbid, IScriptData data );\r\n\t}");
        csCode.AppendLine("\tpublic class ConditionHelper : IConditionHelper\r\n\t{");
    }

    private void FileBottom(StringBuilder csCode)
    {
        csCode.AppendLine("\t}\r\n}");
    }

    private void FillConditionConnecter(StringBuilder csCode, StringBuilder pyCode, Dictionary<DBID, string> dbIDs)
    {
        csCode.AppendLine("\t\tpublic int Condition( string dbid, IScriptData data )\r\n\t\t{\r\n\t\t\tswitch( dbid )\r\n\t\t\t{");
        foreach (var pair in dbIDs)
        {
            csCode.AppendFormat("\t\t\t\tcase \"{0}\":\r\n", pair.Key);
            csCode.AppendFormat("\t\t\t\t\treturn Condition{0}( data );\r\n", pair.Value);
        }
        csCode.AppendLine("\t\t\t\tdefault:");
        csCode.AppendLine("\t\t\t\t\treturn -1;");
        csCode.AppendLine("\t\t\t}\r\n\t\t}");
    }
}