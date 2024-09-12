using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using AccountLib;
using ControlCenter.Helpers;
using log4net;

namespace ControlCenter.Areas.GM.Models
{
  public interface IDynamicQuestService
  {
    AddDynamicQuestResponse AddQuest( string json, string locale, string gmLogin );
    string RemoveQuest( int questId, string locale );
    string EditQuest( int questId, string locale, string json);
    DynamicQuestRawInfoModel GetDynamicQuestInfo();
    DynamicQuestRawInfo GetDynamicQuestById(int id);

    string AddQuestPull( DynamicQuestPullModel questPull, string gmLogin );
    string RemoveQuestPull( int questId, string locale, string gmLogin );
    string EditQuestPull( DynamicQuestPullModel questPull, string gmLogin );
    DynamicQuestPullsInfoResponse GetDynamicQuestPullsInfo();
    DynamicQuestPullByIdResponse GetDynamicQuestPullById( int pullId );
    string AddDynamicQuestsToPull( int pullId, string locale, List<int> questIds, string gmLogin );
    string RemoveDynamicQuestsFromPull( int pullId, string locale, List<int> questIds, string gmLogin );

    AuidListModel GetAuidsLists();
    AuidListMemberModel GetAuidsListById(int index);
    string AddAuidsList(AuidsList auidsList, string gmLogin);
    string EditAuidsList(AuidsList auidsList, string gmLogin);
    string RemoveAuidsList(int index);
  }

  /// <summary>
  /// Class for working with thrift - get quests and send them
  /// </summary>
  public class DynamicQuestService : IDynamicQuestService
  {
    private readonly IAccountManagementService _accountManagementService;
    public static string GmAccountingAddress { get; set; }

    private static readonly ILog Log = LogManager.GetLogger( typeof( DynamicQuestService ) );

    public DynamicQuestService()
    {
      Uri gmAccountingUrl;
      if (GmAccountingAddress != null && Uri.TryCreate(GmAccountingAddress, UriKind.Absolute, out gmAccountingUrl))
      {
        _accountManagementService = new AccountManagementService(gmAccountingUrl);
      }
      else
      {
        Log.ErrorFormat("Invalid cluster address {0}", GmAccountingAddress ?? "(null)");
      }
    }

    private static string PerformAndGetError(Expression<Func<RequestResult>> function)
    {
      string errorString = null;
      Func<RequestResult> toExecute = function.Compile();
      RequestResult requestResult = toExecute();
      if (requestResult != RequestResult.Success)
      {
        errorString = GetVerboseErrorMessage(requestResult);
        Log.Error(string.Format("{0}, was in : {1}", errorString, ((MethodCallExpression)function.Body).Method));
      }
      return errorString;
    }

    /// <summary>
    /// Creates user-friendly error message from error code
    /// </summary>
    public static string GetVerboseErrorMessage(RequestResult result)
    {
      if (result == RequestResult.TransportException)
        return "Transport exception during server request";
      if (result == RequestResult.BadResponseFromDatabase)
        return "Server was unable to connect to database";
      if (result == RequestResult.BadResult)
        return "This SN Uid doesn't exist";
      if (result == RequestResult.ServerReturnedNull)
        return "Request to server failed";
      return Enum.GetName(typeof(RequestResult), result);
    }

    /// <summary>
    /// Send json with quest
    /// </summary>
    public AddDynamicQuestResponse AddQuest(string json, string locale, string gmLogin)
    {
      var result = _accountManagementService.AddDynamicQuest(json, locale, gmLogin);
      return result;
    }

    /// <summary>
    /// Remove selected quest
    /// </summary>
    public string RemoveQuest( int questId, string locale )
    {
      var result = PerformAndGetError(() => _accountManagementService.RemoveDynamicQuest(questId, locale));
      return result;
    }

    /// <summary>
    /// Edit selected quest
    /// </summary>
    public string EditQuest( int questId, string locale, string json )
    {
      var result = PerformAndGetError( () => _accountManagementService.EditDynamicQuest( questId, locale, json ) );
      return result;
    }

    /// <summary>
    /// Get list of all quests
    /// </summary>
    /// <returns>Model with list of jsons with quest infos</returns>
    public DynamicQuestRawInfoModel GetDynamicQuestInfo()
    {
      var model = new DynamicQuestRawInfoModel();
      var quests = _accountManagementService.GetDynamicQuestInfo();
      if (quests.Quests != null)
      {
        foreach (var jsonQuest in quests.Quests)
        {
          model.JsonQuestData.Add(new DynamicQuestRawInfo
          {
            Index = jsonQuest.Index,
            Locale = jsonQuest.Locale,
            Json = jsonQuest.QuestText,
            PullId = jsonQuest.PullId
          });
        }
      }
      return model;
    }

    public DynamicQuestRawInfo GetDynamicQuestById(int id)
    {
      var result = _accountManagementService.GetDynamicQuestById(id);
      if (result == null)
      {
        Log.Error("Unknown error. See previous log.");
        return null;
      }
      if (result.Result != RequestResult.Success)
      {
        var errorString = GetVerboseErrorMessage(result.Result);
        Log.Error(string.Format("{0}, was in : GetDynamicQuestById({1})", errorString, id));
        return null;
      }
      return new DynamicQuestRawInfo
      {
        Index = result.Quest.Index,
        Locale = result.Quest.Locale,
        Json = result.Quest.QuestText,
        PullId = result.Quest.PullId
      };
    }

    /// <summary>
    /// Send new quest pull info
    /// </summary>
    public string AddQuestPull( DynamicQuestPullModel questPull, string gmLogin )
    {
      var result = PerformAndGetError( () =>_accountManagementService.AddDynamicQuestPull( new DynamicQuestPull()
                                                              {
                                                                EndTime = questPull.RotationEndTime.ToUnixTimestamp(),
                                                                StartTime = questPull.RotationStartTime.ToUnixTimestamp(),
                                                                HasRotation = questPull.HasRotation,
                                                                IsActive = questPull.IsWorking,
                                                                Locale = questPull.Locale,
                                                                PersistentId = questPull.PullId
                                                              }, gmLogin ));
      return result;
    }

    /// <summary>
    /// Remove selected quest pull
    /// </summary>
    public string RemoveQuestPull( int questId, string locale, string gmLogin )
    {
      var result = PerformAndGetError( () => _accountManagementService.RemoveDynamicQuestPull( questId, locale, gmLogin ) );
      return result;
    }

    /// <summary>
    /// Edit selected quest pull
    /// </summary>
    public string EditQuestPull( DynamicQuestPullModel questPull, string gmLogin )
    {
      var result = PerformAndGetError( () => _accountManagementService.EditDynamicQuestPull( new DynamicQuestPull()
                                                              {
                                                                EndTime = questPull.RotationEndTime.ToUnixTimestamp(),
                                                                StartTime = questPull.RotationStartTime.ToUnixTimestamp(),
                                                                HasRotation = questPull.HasRotation,
                                                                IsActive = questPull.IsWorking,
                                                                Locale = questPull.Locale,
                                                                PersistentId = questPull.PullId
                                                              }, gmLogin ));
      return result;
    }

    /// <summary>
    /// Get list of all quest pulls
    /// </summary>
    /// <returns>Model with list quest pull infos</returns>
    public DynamicQuestPullsInfoResponse GetDynamicQuestPullsInfo()
    {
      var pulls = _accountManagementService.GetDynamicQuestPullsInfo();
      return pulls;
    }

    
    /// <summary>
    /// Get quest pull with persistentId
    /// </summary>
    /// <returns>Model with list quest pull infos</returns>
    public DynamicQuestPullByIdResponse GetDynamicQuestPullById(int pullId)
    {
      return _accountManagementService.GetDynamicQuestPullById(pullId);
    }
    /// <summary>
    /// Add selected quests to pull
    /// </summary>
    public string AddDynamicQuestsToPull( int pullId, string locale, List<int> questIds, string gmLogin )
    {
      var result = PerformAndGetError( () => _accountManagementService.AddDynamicQuestsToPull( pullId, questIds, locale, gmLogin ) );
      return result;
    }

    /// <summary>
    /// Remove selected quests from pull
    /// </summary>
    public string RemoveDynamicQuestsFromPull( int pullId, string locale, List<int> questIds, string gmLogin )
    {
      var result = PerformAndGetError( () => _accountManagementService.RemoveDynamicQuestsFromPull( pullId, questIds, locale, gmLogin ) );
      return result;
    }

    public AuidListModel GetAuidsLists()
    {
      var result = new AuidListModel();

      var lists = _accountManagementService.GetAuidsLists();
      if (lists == null)
      {
        Log.Error("Unknown error. See previous log.");
        return result;
      }
      if (lists.Result != RequestResult.Success)
      {
        var errorString = GetVerboseErrorMessage(lists.Result);
        Log.Error(string.Format("{0}, was in : GetAuidsLists()", errorString));
        return result;
      }

      foreach (var list in lists.AuidsLists)
      {
        result.Lists.Add(new AuidListMemberModel
        {
          Auids = String.Join(", ", list.Auids.Select(x => x.ToString()).ToArray()),
          Description = list.Description,
          Index = list.Index,
          Links = 0
        });
      }

      FillUsageInDynamicQuests(result);

      return result;
    }

    public AuidListMemberModel GetAuidsListById(int index)
    {
      var result = _accountManagementService.GetAuidsListById(index);
      if (result == null)
      {
        Log.Error("Unknown error. See previous log.");
        return new AuidListMemberModel();
      }
      if (result.Result != RequestResult.Success)
      {
        var errorString = GetVerboseErrorMessage(result.Result);
        Log.Error(string.Format("{0}, was in : GetAuidsListById({1})", errorString, index));
        return new AuidListMemberModel();
      }

      var tempList = new AuidListModel();
      tempList.Lists.Add(new AuidListMemberModel
      {
        Auids = String.Join(", ", result.AuidsLists.Auids.Select(x => x.ToString()).ToArray()),
        Description = result.AuidsLists.Description,
        Index = result.AuidsLists.Index,
        Links = 0
      });
      FillUsageInDynamicQuests(tempList);
      return tempList.Lists.First();
    }

    private void FillUsageInDynamicQuests(AuidListModel auidListModel)
    {
      //Выглядит немного дико, но нам надо знать, сколько квестов ссылаются на каждый список
      var dynamicQuests = GetDynamicQuestInfo();
      dynamicQuests.ProcessData();
      foreach (
        var quest in
          dynamicQuests.ParcedQuestsList.Values.Where(quest => quest.Data.AcceptFilter.AuidList != "-1")
            .Where(quest => auidListModel.Lists.Any(x => x.Index.ToString() == quest.Data.AcceptFilter.AuidList)))
      {
        auidListModel.Lists.First(x => x.Index.ToString() == quest.Data.AcceptFilter.AuidList).Links++;
      }
    }

    public string AddAuidsList(AuidsList auidsList, string gmLogin)
    {
      var result = PerformAndGetError(() => _accountManagementService.AddAuidsList(auidsList, gmLogin));
      return result;
    }

    public string EditAuidsList(AuidsList auidsList, string gmLogin)
    {
      var result = PerformAndGetError(() => _accountManagementService.EditAuidsList(auidsList, gmLogin));
      return result;
    }

    public string RemoveAuidsList(int index)
    {
      var result = PerformAndGetError(() => _accountManagementService.RemoveAuidsList(index));
      return result;
    }
  }
}