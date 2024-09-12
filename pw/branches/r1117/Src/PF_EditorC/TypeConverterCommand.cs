using EditorLib;
using EditorLib.Plugin;
using EditorPlugins.Console;
using libdb.DB;
using libdb.IO;
using DBTypes;
using System.Text;
using System.Runtime.InteropServices;
using System.Globalization;

namespace PF_Editor
{
    //[CommandName("convert", "c", "Types conversion.")]
    //public sealed class TypeConverterCommand : TypeConverterAbstractCommand<Quest, Quest>
    //{
    //    protected override bool Convert(IEditorCommonApplication application, DBPtr<Quest> oldResource, out Quest newResource)
    //    {
    //        newResource = oldResource.Get();

    //        newResource.answers = newResource.altRewards;

    //        if(newResource.reward != null)
    //        {
    //            var simpleReward = new GiveRewardAction();
    //            simpleReward.fame = newResource.reward.fame;
    //            simpleReward.heroes = newResource.reward.heroes;
    //            simpleReward.resources = newResource.reward.resources;
    //            simpleReward.talents = newResource.reward.talents;
    //            simpleReward.constructions = newResource.reward.constructions;

    //            newResource.rewards.Add(DataBase.Create<QuestAction>(DBID.FromDBID(oldResource.DBId, true), simpleReward));

    //            foreach (var action in newResource.reward.actions)
    //            {
    //                newResource.rewards.Add( action );
    //            }
    //        }
            
    //        return true;
    //    }
    //}
}
