using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Web.Mvc;
using System.Web.Routing;
using System.Xml;
using AccountLib;
using ControlCenter.Areas.GM.Models;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.GM.Controllers
{
  [Authorize]
  public class DynamicQuestController : Controller
  {
    public IDynamicQuestService DynamicQuestSvc { get; set; }
    public IAccountService AccountSvc { get; set; }

    protected override void Initialize(RequestContext requestContext)
    {
      base.Initialize(requestContext);

      if (DynamicQuestSvc == null)
        DynamicQuestSvc = new DynamicQuestService();

      if (AccountSvc == null)
        AccountSvc = new AccountService();
    }

    [AuthorizeWithPermission(Permission = "GM_DynamicQuests")]
    public ActionResult Overview()
    {        
      var model = DynamicQuestSvc.GetDynamicQuestInfo();
      model.ProcessData();
      return View(model);
    }

    [HttpPost, ValidateInput(false)]
    [AuthorizeWithPermission(Permission = "GM_DynamicQuests")]
    public ActionResult Overview(DynamicQuestRawInfoModel model)
    {
      return RedirectToAction("DynamicQuestInfo",
        new { index = -1, json = model.NewQuestJson, operation = "AddRaw" });
    }

    [AuthorizeWithPermission(Permission = "GM_DynamicQuests")]
    public ActionResult RemoveDynamicQuest(string questStartTime, string questEndTime,
      string questName, string locale, int questId, int pullId)
    {
      var model = new RemoveDynamicQuestModel
      {
        QuestStartTime = questStartTime,
        QuestEndTime = questEndTime,
        QuestName = questName,
        Locale = locale,
        QuestId = questId,
        PullId = pullId
      };
      return View(model);
    }

    [HttpPost]
    [AuthorizeWithPermission(Permission = "GM_DynamicQuests")]
    public ActionResult RemoveDynamicQuest( RemoveDynamicQuestModel model )
    {
      model.Message = DynamicQuestSvc.RemoveQuest(model.QuestId, model.Locale);
      if (model.Message != null)
      {
        return View(model);
      }
      model.Message = DynamicQuestSvc.RemoveDynamicQuestsFromPull( model.PullId, model.Locale,
                                                                   new List<int>{model.QuestId}, model.Locale );
      if ( model.Message != null )
      {
        return View( model );
      }
      return RedirectToAction("Overview");
    }

    [AuthorizeWithPermission(Permission = "GM_DynamicQuests")]
    public ActionResult RemoveWrongQuest(int questId, string locale)
    {
      var message = DynamicQuestSvc.RemoveQuest(questId, locale);
      if (message != null)
      {
        return RedirectToAction("ShowError", "Account", new { message });
      }
      return RedirectToAction("Overview");
    }

    [ValidateInput(false)]
    [AuthorizeWithPermission(Permission = "GM_DynamicQuests")]
    public ActionResult DynamicQuestInfo(int? index, string json, string operation)
    {
      var model = new DynamicQuestInfoModel();
      if (operation == "Add")
      {
        json = "";
      }
      if (operation == "AddRaw")
      {
        try
        {
          model = new DynamicQuestInfoModel(json, "", 0);
        }
        catch (FormatException)
        {
          model.Warning = "Error in parsing json!";
        }
        catch (XmlException)
        {
          model.Warning = "Error in parsing json!";
        }
        catch (SerializationException)
        {
          model.Warning = "Error in parsing json!";
        }
      }
      if ((new[] { "Info", "Edit" }).Contains(operation))
      {
        if (index == null)
        {
          model.Warning = "Unexpected error";
          json = "";
        }
        else
        {
          var quest = DynamicQuestSvc.GetDynamicQuestById(index.Value);
          if (quest == null)
          {
            model.Warning = "Error in server response!";
            json = "";
          }
          else
          {
            try
            {
              model = new DynamicQuestInfoModel(quest.Json, quest.Locale, quest.PullId);
            }
            catch (FormatException)
            {
              model.Warning = "Error in parsing json!";
            }
            catch (XmlException)
            {
              model.Warning = "Error in parsing json!";
            }
            catch (SerializationException)
            {
              model.Warning = "Error in parsing json!";
            }
            json = quest.Json;
          }
        }
      }

      model.Editable = !(new[] { "Info" }).Contains(operation);
      model.ExistingQuest = !(new[] {"Add", "AddRaw"}).Contains(operation);
      model.FillSelectLists(AccountSvc, DynamicQuestSvc);
      model.FillFromData();
      model.ResultJson = json;
      model.Data.QuestId = index ?? 0;
      return View(model);
    }

    [HttpPost, ValidateInput(false)]
    [AuthorizeWithPermission(Permission = "GM_DynamicQuests")]
    public ActionResult DynamicQuestInfo(DynamicQuestInfoModel model, string operation)
    {
      if (ModelState.IsValid)
      {
        int[] completedQuestsList;
        int[] notCompletedQuestsList;
        int[] missedQuestsList;
        int[] dependedTournamentQuests;
        if (!DynamicQuestInfoModel.ConvertStringToArrayOfInt(model.CompletedQuests, out completedQuestsList) ||
            !DynamicQuestInfoModel.ConvertStringToArrayOfInt(model.NotCompletedQuests, out notCompletedQuestsList) || 
            !DynamicQuestInfoModel.ConvertStringToArrayOfInt(model.MissedQuests, out missedQuestsList) ||
            !DynamicQuestInfoModel.ConvertStringToArrayOfInt(model.DependedTournamentQuests, out dependedTournamentQuests)
            )
        {
          model.Warning = "Unexpected error in quests dependencies";
        } 
        else if (model.Data.QuestName.Length == 0) // NUM_TASK
        {
            model.Warning = "Error: QuestName (Header) is empty!";
        }
        else 
        { 
          // форма заполнена верно, можно постить запрос
          UpdateModel(model);
          ModelState.Clear();
          model.Data.AcceptFilter.CompletedQuests = completedQuestsList;
          model.Data.AcceptFilter.NotCompletedQuests = notCompletedQuestsList;
          model.Data.AcceptFilter.MissedQuests = missedQuestsList;
          model.Data.AcceptFilter.DependedTournamentQuests = dependedTournamentQuests;
          model.CorrectData();
          model.FillFromData();

          var questError = "Error in server response! ";
          var questId = 0;
          if (operation == "SentNew")
          {
            var response = DynamicQuestSvc.AddQuest(model.ResultJson, model.Locale, User.Identity.Name);
            if (response != null)
            {
                model.Warning = response.Result.ToString() ?? "Success";
                questId = response.QuestId;
                if (questId == 0)
                  model.Warning += "\nError in server response! Bad: " + ParseDynamicQuestDetails(response.Details) + ".";
            }
          }
          if (operation == "SentEdit")
          {
            var errorIfExistToShow = DynamicQuestSvc.EditQuest(model.Data.QuestId, model.Locale, model.ResultJson);
            model.Warning = errorIfExistToShow ?? "Success";
            questId = model.Data.QuestId;

          }
          if (operation == "Preview")
          {
            model.Warning = "Quest Json Preview!";
          }
          else
          {
            var quest = DynamicQuestSvc.GetDynamicQuestById(questId);
            if (quest == null)
            {
              model.Warning = "Error in server response! ";
            }
            else
            {
              try
              {
                model = new DynamicQuestInfoModel(quest.Json, quest.Locale, quest.PullId);
                model.Data.QuestId = quest.Index;
                model.ResultJson = quest.Json;
              }
              catch (FormatException)
              {
                model.Warning = "Error in parsing json!";
              }
              catch (XmlException)
              {
                model.Warning = "Error in parsing json!";
              }
              catch (SerializationException)
              {
                model.Warning = "Error in parsing json!";
              }
            }
          }
        }

      }
      else
      {
        model.Warning = "Unexpected error in data";
      }

      if (model.Warning.Length == 0)
      {
          model.Warning = "New Quest created successfully!";
      }
      model.Editable = true;
      model.ExistingQuest = true;
      model.FillSelectLists(AccountSvc, DynamicQuestSvc);
      model.FillFromData();
      return View(model);
    }

    private static string ParseDynamicQuestDetails(string details)
    {
      var linesInDetails = details.Split('\n');
      var lastLine = linesInDetails[linesInDetails.Length - 2];
      var valuesInLastLine = lastLine.Split(':');
      var lastValueInLastLineValues = valuesInLastLine[valuesInLastLine.Length - 1];
      return lastValueInLastLineValues;
    }

    [AuthorizeWithPermission( Permission = "GM_DynamicQuests" )]
    public ActionResult AddQuestPull( )
    {
      var model = new DynamicQuestPullModel {SvcLocales = new SelectList( AccountSvc.GetBroadcastLocales() )};
      return View( model );
    }

    [HttpPost]
    [AuthorizeWithPermission( Permission = "GM_DynamicQuests" )]
    public ActionResult AddQuestPull( DynamicQuestPullModel newPull )
    {

      var error = DynamicQuestSvc.AddQuestPull( newPull, User.Identity.Name );
      if ( error != null )
      {
        return RedirectToAction( "ShowError", "Account", new { error } );
      }
      return RedirectToAction( "QuestPulls" );
    }

    [AuthorizeWithPermission( Permission = "GM_DynamicQuests" )]
    public ActionResult RemoveQuestPull( int pullId, string locale )
    {
      string error = DynamicQuestSvc.RemoveQuestPull( pullId, locale, User.Identity.Name );
      if ( error != null )
        return RedirectToAction( "ShowError", "Account", new { error } );

      return RedirectToAction( "QuestPulls" );
    }

    [AuthorizeWithPermission( Permission = "GM_DynamicQuests" )]
    public ActionResult EditQuestPull( int pullId )
    {

      var pullResponse = DynamicQuestSvc.GetDynamicQuestPullById( pullId );
      if (pullResponse.Result != RequestResult.Success )
      {
        var error = pullResponse.Result.ToString();
        return RedirectToAction( "ShowError", "Account", new { error } );
      }
      var model = new DynamicQuestPullModel()
              {
                HasRotation = pullResponse.QuestPull.HasRotation,
                IsWorking = pullResponse.QuestPull.IsActive,
                Locale = pullResponse.QuestPull.Locale,
                PullId = pullResponse.QuestPull.PersistentId,
                Quests = pullResponse.QuestPull.Quests,
                RotationStartTime = pullResponse.QuestPull.StartTime.FromUnixTimestamp(),
                RotationEndTime = pullResponse.QuestPull.EndTime.FromUnixTimestamp(),
                SvcLocales = new SelectList( AccountSvc.GetBroadcastLocales() )
              };
      return View( model );
    }

    [HttpPost]
    [AuthorizeWithPermission( Permission = "GM_DynamicQuests" )]
    public ActionResult EditQuestPull( DynamicQuestPullModel newPull )
    {

      var error = DynamicQuestSvc.EditQuestPull( newPull, User.Identity.Name );
      if ( error != null )
      {
        return RedirectToAction( "ShowError", "Account", new { error } );
      }
      return RedirectToAction( "QuestPulls" );
    }

    [AuthorizeWithPermission( Permission = "GM_DynamicQuests" )]
    public ActionResult QuestPulls()
    {
      var model = new List<DynamicQuestPullModel>();
      var response = DynamicQuestSvc.GetDynamicQuestPullsInfo();
      foreach( var pull in response.QuestPulls )
      {
        model.Add( new DynamicQuestPullModel()
                   {
                     HasRotation = pull.HasRotation,
                     IsWorking = pull.IsActive,
                     Locale = pull.Locale,
                     PullId = pull.PersistentId,
                     Quests = pull.Quests,
                     RotationStartTime = pull.StartTime.FromUnixTimestamp(),
                     RotationEndTime = pull.EndTime.FromUnixTimestamp()
                   } );
      }
      return View( model );
    }

    [AuthorizeWithPermission( Permission = "GM_DynamicQuests" )]
    public ActionResult AddQuestsToPull( string quests, string locale, int pullId )
    {
      var model = new List<DynamicQuestShortInfoModel>();
      var separateQuests = quests.Split( ' ' );
      var questId = 0;
      var allQuests = DynamicQuestSvc.GetDynamicQuestInfo();
      var intQuestIds = new List<int>();
      ViewData["pullId"] = pullId;
      allQuests.ProcessData();
      
      foreach ( var strQuest in separateQuests )
      {
        if ( int.TryParse( strQuest, out questId ) )
          intQuestIds.Add( questId );
      }
      foreach (var quest in allQuests.ParcedQuestsList)
      {
        if ( !intQuestIds.Contains( quest.Key.Index ) && quest.Value.Locale == locale && quest.Value.PullId == 0)
          model.Add( new DynamicQuestShortInfoModel()
                     {
                       QuestId = quest.Key.Index,
                       QuestName = quest.Value.Data.QuestName
                     });
      }
      return View( model );
    }

    [HttpPost]
    [AuthorizeWithPermission( Permission = "GM_DynamicQuests" )]
    public ActionResult AddQuestsToPull( int[] selected, string locale, int pullId )
    {
      string error = DynamicQuestSvc.AddDynamicQuestsToPull( pullId, locale, new List<int>(selected), User.Identity.Name );
      if ( error != null )
        return RedirectToAction( "ShowError", "Account", new { error } );

      return RedirectToAction( "QuestPulls" );
    }

    [AuthorizeWithPermission( Permission = "GM_DynamicQuests" )]
    public ActionResult RemoveQuestsFromPull( string quests, int pullId )
    {
      var model = new List<DynamicQuestShortInfoModel>();
      var separateQuests = quests.Split( ' ' );
      var questId = 0;
      var allQuests = DynamicQuestSvc.GetDynamicQuestInfo();
      var intQuestIds = new List<int>();
      ViewData["pullId"] = pullId;
      allQuests.ProcessData();

      foreach ( var strQuest in separateQuests )
      {
        if ( int.TryParse( strQuest, out questId ) )
          intQuestIds.Add( questId );
      }
      foreach ( var quest in allQuests.ParcedQuestsList )
      {
        if ( intQuestIds.Contains( quest.Key.Index ) )
          model.Add( new DynamicQuestShortInfoModel()
          {
            QuestId = quest.Key.Index,
            QuestName = quest.Value.Data.QuestName
          } );
      }
      return View( model );
    }

    [HttpPost]
    [AuthorizeWithPermission( Permission = "GM_DynamicQuests" )]
    public ActionResult RemoveQuestsFromPull( int[] selected, string locale, int pullId )
    {
      string error = DynamicQuestSvc.RemoveDynamicQuestsFromPull( pullId, locale, new List<int>( selected ), User.Identity.Name );
      if ( error != null )
        return RedirectToAction( "ShowError", "Account", new { error } );

      return RedirectToAction( "QuestPulls" );
    }
 
  }
}
