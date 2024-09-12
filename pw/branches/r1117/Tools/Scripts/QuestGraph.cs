/*
#about Построение графа зависимостей квестов  в формате dot 
#ref PF_Types.DBTypes.dll
#ref SocialTypes.DBTypes.dll
#ref PF_EditorC.exe
#ref EditorPlugins.dll
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
using libdb;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;
using DBTypes;

public class QuestGraph
{
    private const string AdorQuestLinesRoot = "/Dialog/CastleTutorial/Ador";
    private const string DoktQuestLinesRoot = "/Dialog/CastleTutorial/Dokt";
    private const string DotArrow = "->";

    public IEnumerable Main(IEditorCommonApplication app, string[] parameters)
    {
        if (parameters.Length < 1)
        {
            Log.TraceMessage(
                "Usage for quest graph generation: PF_EditorC.exe run ../Tools/Scripts/QuestGraph.cs <result_dot_files_directory_path>");
            yield break;
        }

        string resultFilePath = parameters[0];
        if (!Directory.Exists(resultFilePath))
        {
            Log.TraceMessage("Wrong directory: {0}", resultFilePath);
            yield break;
        }
        var questLinesAdorDbids = new List<DBID>();
        ObjectsSelector.CollectObjects(app, AdorQuestLinesRoot, typeof(QuestLine), true, true, out questLinesAdorDbids);
        Log.TraceMessage("Collected {0} quest lines at {1}", questLinesAdorDbids.Count, AdorQuestLinesRoot);

        var questLinesDoktDbids = new List<DBID>();
        ObjectsSelector.CollectObjects(app, DoktQuestLinesRoot, typeof(QuestLine), true, true, out questLinesDoktDbids);
        Log.TraceMessage("Collected {0} quest lines at {1}", questLinesDoktDbids.Count, DoktQuestLinesRoot);

        File.WriteAllText(Path.Combine(resultFilePath, "QuestGraphAdor.dot"), GenerateDotGraph(questLinesAdorDbids, "Ador"), Encoding.GetEncoding(1251));
        File.WriteAllText(Path.Combine(resultFilePath, "QuestGraphDokt.dot"), GenerateDotGraph(questLinesDoktDbids, "Dokt"), Encoding.GetEncoding(1251));

        yield return true;
    }
    private static string GenerateDotGraph(List<DBID> questLinesDbids, string name)
    {
        StringBuilder resultDot = new StringBuilder();
        StringBuilder resultSubQuestDot = new StringBuilder();
        resultDot.AppendFormat("digraph {0} {{", name);
        resultDot.AppendLine();
        foreach (var questAdorDbid in questLinesDbids)
        {
            QuestLine questLineAdor = DataBase.Get<QuestLine>(questAdorDbid).Get();
            if (questLineAdor == null)
                continue;
            bool isFirst = true;
            for (int i = 0; i < questLineAdor.quests.Count; i++)
            {
                var questDBID = questLineAdor.quests[i];
                Quest quest = questDBID.Get();
                if (quest == null)
                    continue;
                CheckForDependencies(quest, resultSubQuestDot);
                if (!isFirst)
                    resultDot.Append(DotArrow);
                if (isFirst)
                    isFirst = false;
                resultDot.Append(quest.persistentId);
            }
            resultDot.AppendLine(";");
        }
        resultDot.Append(resultSubQuestDot);
        resultDot.AppendLine("}");
        return resultDot.ToString();
    }
    private static void CheckForDependencies(Quest quest, StringBuilder result)
    {
        int depCount = 0;
        depCount += CheckActions(quest, result, quest.rewards, "red");
        foreach (var altReward in quest.answers)
        {
            depCount += CheckActions(quest, result, altReward.actions, "forestgreen");
        }
        foreach (var obj in quest.objectives)
        {
            depCount += CheckActions(quest, result, obj.skip, "blue");
        }
        if(depCount!=0)
            Log.TraceMessage("Quest {0} has {1} dependencies but lines", quest.DBId, depCount);
    }
    private static int CheckActions(Quest quest, StringBuilder result, IChangeableList<DBPtr<QuestAction>> actions, string label)
    {
        int depCount = 0;
        foreach (var actionDBID in actions)
        {
            var action = actionDBID.Get();
            if (action is NextQuestAction)
            {
                var nextQuest = (action as NextQuestAction).quest.Get();
                result.AppendFormat("{0}{1}{2}[color={3}];", quest.persistentId, DotArrow, nextQuest.persistentId, label);
                result.AppendLine();
                depCount++;
            }
        }
        return depCount;
    }
}
