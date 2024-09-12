/*
#about Расшаривание условий квестов между фракциями
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
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;
using DBTypes;

public class ShareQuestConditions
{
    private const string AdorQuestLinesRoot = "/Dialog/CastleTutorial/Ador";
    private const string DoktQuestLinesRoot = "/Dialog/CastleTutorial/Dokt";
    private const string QuestConditionsRoot = "/Dialog/CastleTutorial/Conditions/";

    public IEnumerable Main(IEditorCommonApplication app, string[] parameters)
    {
        var questsAdorDbids = new List<DBID>();
        ObjectsSelector.CollectObjects(app, AdorQuestLinesRoot, typeof(Quest), true, true, out questsAdorDbids);
        Log.TraceMessage("Collected {0} quest at {1}", questsAdorDbids.Count, AdorQuestLinesRoot);
        var questsDoktDbids = new List<DBID>();
        ObjectsSelector.CollectObjects(app, DoktQuestLinesRoot, typeof(Quest), true, true, out questsDoktDbids);
        Log.TraceMessage("Collected {0} quest at {1}", questsDoktDbids.Count, DoktQuestLinesRoot);

        Dictionary<string, Quest> adorQuests = new Dictionary<string, Quest>();
        foreach (var questAdorDbid in questsAdorDbids)
        {
            Quest questAdor = DataBase.Get<Quest>(questAdorDbid).Get();
            if (questAdor == null)
                continue;
            var questKey = Regex.Replace(questAdor.persistentId, "(_.*)", "");
            if (adorQuests.ContainsKey(questKey))
            {
                Log.TraceWarning("Quest with id {0} was already added", questAdor.DBId);
                continue;
            }
            adorQuests.Add(questKey, questAdor);
        }
        Dictionary<string, Quest> doktQuests = new Dictionary<string, Quest>();
        foreach (var questDoktDbid in questsDoktDbids)
        {
            Quest questDokt = DataBase.Get<Quest>(questDoktDbid).Get();
            if (questDokt == null)
                continue;
            var questKey = Regex.Replace(questDokt.persistentId, "(_.*)", "");
            if (doktQuests.ContainsKey(questKey))
            {
                Log.TraceWarning("Quest with id {0} was already added", questDokt.DBId);
                continue;
            }
            doktQuests.Add(questKey, questDokt);
        }

        foreach (var adorQuest in adorQuests)
        {
            if (adorQuest.Value.objectives.Count == 0)
            {
                Log.TraceWarning("Quest with id {0} has 0 objectives", adorQuest.Value.DBId);
                continue;
            }
            if (!doktQuests.ContainsKey(adorQuest.Key))
            {
                Log.TraceWarning("Quest with id {0} has no pair", adorQuest.Value.DBId);
                continue;
            }
            if (doktQuests[adorQuest.Key].objectives.Count != adorQuest.Value.objectives.Count)
            {
                Log.TraceWarning("Quest with id {0} has a pair with different numbers of objectives", adorQuest.Value.DBId);
                continue;
            }
            int objIndex = 0;
            foreach (var adorObj in adorQuest.Value.objectives)
            {
                if (adorObj.condition.DBId.IsInlined)
                {
                    var oldCondition = adorObj.condition.Get();
                    if (oldCondition != null)
                    {
                        QuestCondition newCondition =
                            TypeUtils.CreateInstance(oldCondition.GetType()) as QuestCondition;
                        var tmpDbid =
                            DBID.FromFileName(
                                String.Format("{0}{1}_{2}", QuestConditionsRoot, adorQuest.Key, objIndex), false);
                        DBPtr<QuestCondition> newConditionPtr = DataBase.Create(tmpDbid, newCondition);
                        DBCopy.Copy(newConditionPtr.Get(), oldCondition);
                        adorObj.condition = newConditionPtr;
                        doktQuests[adorQuest.Key].objectives[objIndex].condition = newConditionPtr;
                        Log.TraceMessage("Quest condition {0} was copied", newConditionPtr);
                    }
                }
                if (adorObj.autoCompleteCondition.DBId.IsInlined)
                {
                    var oldAutoCondition = adorObj.autoCompleteCondition.Get();
                    if (oldAutoCondition != null)
                    {
                        ModelDataCondition newAutoCondition =
                            TypeUtils.CreateInstance(oldAutoCondition.GetType()) as ModelDataCondition;
                        var tmpDbid =
                            DBID.FromFileName(
                                String.Format("{0}{1}_auto_{2}", QuestConditionsRoot, adorQuest.Key, objIndex),
                                false);
                        DBPtr<ModelDataCondition> newAutoConditionPtr = DataBase.Create(tmpDbid, newAutoCondition);
                        DBCopy.Copy(newAutoConditionPtr.Get(), oldAutoCondition);
                        adorObj.autoCompleteCondition = newAutoConditionPtr;
                        doktQuests[adorQuest.Key].objectives[objIndex].autoCompleteCondition = newAutoConditionPtr;
                        Log.TraceMessage("Quest condition {0} was copied", newAutoConditionPtr);
                    }
                }
                objIndex++;
            }
        }
        Log.TraceMessage("Save results..");
        DataBase.Store();

        yield return true;
    }
}