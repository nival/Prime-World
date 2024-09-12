using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Web.Mvc;
using System.Xml;

namespace ControlCenter.Areas.GM.Models
{
    /// <summary>
    /// Quest information from server
    /// </summary>
    public class DynamicQuestRawInfo
    {
        public string Json;
        public string Locale;
        public int Index;
        public int PullId;
    }

    /// <summary>
    /// Class with information about a quests to remove
    /// </summary>
    public class RemoveDynamicQuestModel
    {
        [DisplayName("Quest name")]
        public string QuestName { get; set; }
        [DisplayName("Start time")]
        public String QuestStartTime { get; set; }
        [DisplayName("End time")]
        public String QuestEndTime { get; set; }
        public string Message { get; set; }
        public string Locale { get; set; }
        public int QuestId { get; set; }
        public bool AutoAccept { get; set; }
        public int PullId { get; set; }

        public RemoveDynamicQuestModel()
        {
            Message = null;
        }
    }

    /// <summary>
    /// Class with list of all quests in json
    /// </summary>
    public class DynamicQuestRawInfoModel
    {
        public string NewQuestJson { get; set; }
        public List<DynamicQuestRawInfo> JsonQuestData { get; set; }
        public Int32 WrongJsons { get; set; }
        public Dictionary<DynamicQuestRawInfo, DynamicQuestInfoModel> ParcedQuestsList { get; set; }
        public List<DynamicQuestRawInfo> WrongJsonsList { get; set; }

        public DynamicQuestRawInfoModel()
        {
            JsonQuestData = new List<DynamicQuestRawInfo>();
            WrongJsons = 0;
        }

        public void ProcessData()
        {
            WrongJsonsList = new List<DynamicQuestRawInfo>();
            ParcedQuestsList = new Dictionary<DynamicQuestRawInfo, DynamicQuestInfoModel>();
            foreach (var questData in JsonQuestData)
            {
                var parced = true;
                DynamicQuestInfoModel temp = null;
                try
                {
                    temp = new DynamicQuestInfoModel(questData.Json, questData.Locale, questData.PullId);
                    temp.FillFromData();
                }
                catch (XmlException)
                {
                    parced = false;
                    WrongJsonsList.Add(questData);
                }
                if (parced) ParcedQuestsList.Add(questData, temp);
            }
            WrongJsons = WrongJsonsList.Count;
        }
    }

    /// <summary>
    /// Class with all quest info
    /// </summary>
    [DataContract]
    public class DynamicQuestDataModel
    {
        public int QuestId { get; set; }

        [DataMember]
        [DisplayName("URL to quest portrait")]
        [DisplayFormat(ConvertEmptyStringToNull = false)]
        public string NPCPortret { get; set; }

        [DataMember]
        [DisplayName("Header")]
        [DisplayFormat(ConvertEmptyStringToNull = false)]
        public string QuestName { get; set; }

        [DataMember]
        [DisplayName("Description")]
        [DisplayFormat(ConvertEmptyStringToNull = false)]
        public string QuestDescription { get; set; }

        [DataMember]
        public long QuestStartTime { get; set; }

        [DataMember]
        public long QuestEndTime { get; set; }

        [DataMember]
        public string AutoAccept { get; set; }

        [DataMember(IsRequired = false)]
        public string RepeatOnMiss { get; set; }

        [DataMember]
        public AcceptFilter AcceptFilter { get; set; }

        [DataMember]
        public List<QuestData> QuestData { get; set; }

        [DataMember]
        public List<DynamicQuestAward> Awards { get; set; }

        [DataMember(IsRequired = false)]
        public List<QuestData> AlternativeQuestData { get; set; }

        [DataMember(IsRequired = false)]
        public List<DynamicQuestAward> AlternativeAwards { get; set; }

        [DataMember(IsRequired = false)]
        public List<PreCondition> PreConditions { get; set; }

        [DataMember]
        [DisplayName("Completion Text (show in award dialog if not empty")]
        [DisplayFormat(ConvertEmptyStringToNull = false)]
        public string CompletionText { get; set; }

        [DataMember]
        [DisplayName("Show image under description if url not empty")]
        [DisplayFormat(ConvertEmptyStringToNull = false)]
        public string DescriptionImageUrl { get; set; }
       
    public DynamicQuestDataModel()
        {
            QuestStartTime =
              Convert.ToInt64((DateTime.UtcNow - new DateTime(1970, 1, 1, 0, 0, 0, 0, DateTimeKind.Utc)).TotalSeconds);
            QuestEndTime =
              Convert.ToInt64(
                (DateTime.UtcNow - new DateTime(1970, 1, 1, 0, 0, 0, 0, DateTimeKind.Utc) + TimeSpan.FromDays(14))
                  .TotalSeconds);
            AutoAccept = "False";
            RepeatOnMiss = "False";
            AcceptFilter = new AcceptFilter();
            AcceptFilter.MaxLordLevel = 40;
            QuestData = new List<QuestData>();
            Awards = new List<DynamicQuestAward>();
            AlternativeQuestData = new List<QuestData>();
            AlternativeAwards = new List<DynamicQuestAward>();
            PreConditions = new List<PreCondition>();
            
        }

        public static DynamicQuestDataModel Deserialize(string json)
        {
            var serializer = new DataContractJsonSerializer(typeof(DynamicQuestDataModel));
            var stream = new MemoryStream(Encoding.UTF8.GetBytes(json)) { Position = 0 };
            return (DynamicQuestDataModel)serializer.ReadObject(stream);
        }

        public static string Serialize(DynamicQuestDataModel data)
        {
            var serializer = new DataContractJsonSerializer(typeof(DynamicQuestDataModel));
            var stream = new MemoryStream();
            serializer.WriteObject(stream, data);
            return Encoding.UTF8.GetString(stream.ToArray());
        }
    }

    /// <summary>
    /// Base preCondition for dynamic quests
    /// </summary>
    [DataContract]
    public class PreCondition
    {

        [DataMember]
        [DisplayName("PreCondition type")]
        public DynamicQuestPreConditionType PreConditionType { get; set; }


        [DataMember]
        [DisplayName("Tournament map")]
        [DisplayFormat(ConvertEmptyStringToNull = false)]
        public string TournamentMapType { get; set; }
       
        
        [OnDeserializing]
        private void OnDeserializing(StreamingContext context)
        {
            SetDefaults();
        }

        [OnSerializing]
        private void OnSerializing(StreamingContext context)
        {
            SetDefaults();
        }

        private void SetDefaults()
        {
            if (PreConditionType == 0 )
                PreConditionType = DynamicQuestPreConditionType.Usual;
            if (TournamentMapType == null) TournamentMapType = "";
        }

        public PreCondition()
        {
            SetDefaults();
        }
    }


    /// <summary>
    /// AcceptConditions for dynamic quests
    /// </summary>
    [DataContract]
    public class AcceptFilter
    {
        [DataContract]
        public struct ItemsValuePair
        {
            [DataMember]
            [DisplayFormat(ConvertEmptyStringToNull = false)]
            public string Items { get; set; }
            [DataMember]
            public int Value { get; set; }
        }

        [DataMember]
        [DisplayName("Minimal Lord level required for a quest")]
        public int MinLordLevel { get; set; }

        [DataMember]
        [DefaultValue( 40 )]
        [DisplayName("Maximal Lord level required for a quest")]
        public int MaxLordLevel { get; set; }

        [DataMember]
        [DisplayName("Faction")]
        [DisplayFormat(ConvertEmptyStringToNull = false)]
        public string Faction { get; set; }

        [DataMember]
        [DisplayName("LastLoginTime")]
        public int LastLoginTime { get; set; }

        [DataMember]
        [DisplayName("Paying user")]
        [DisplayFormat(ConvertEmptyStringToNull = false)]
        public string Donate { get; set; }

        [DataMember]
        [DisplayName("Doesn't have a hero")]
        [DisplayFormat(ConvertEmptyStringToNull = false)]
        public string NoHero { get; set; }

        [DataMember]
        [DisplayName("Doesn't have a skin")]
        [DisplayFormat(ConvertEmptyStringToNull = false)]
        public string NoSkin { get; set; }

        [DataMember]
        [DisplayName("Doesn't have a flag")]
        [DisplayFormat(ConvertEmptyStringToNull = false)]
        public string NoFlag { get; set; }

        [DataMember]
        [DisplayName("Doesn't have a construction")]
        [DisplayFormat(ConvertEmptyStringToNull = false)]
        public string NoBuilding { get; set; }

        [DataMember]
        [DisplayName("Has heroes with rating more than")]
        public ItemsValuePair HeroesOfMinRating { get; set; }

        [DataMember]
        [DisplayName("All heroes has rating less than")]
        public ItemsValuePair HeroesOfMaxRating { get; set; }

        [DataMember]
        [DisplayName("Has heroes with power")]
        public ItemsValuePair HeroesOfForce { get; set; }

        [DataMember]
        [DisplayName("Has heroes with level")]
        public ItemsValuePair HeroesOfLevel { get; set; }

        [DataMember]
        [DisplayName("Has golden age")]
        [DisplayFormat(ConvertEmptyStringToNull = false)]
        public string HasPremium { get; set; }

        [DataMember]
        [DisplayName("Last payment time")]
        public int LastPaymentTime { get; set; }

        [DataMember]
        [DisplayName("Has construction with level")]
        public ItemsValuePair BuildingOfLevel { get; set; }

        [DataMember]
        [DisplayName("Has guild")]
        [DisplayFormat(ConvertEmptyStringToNull = false)]
        public string InGuild { get; set; }

        //[DataMember]
        //[DisplayName("Has talents with quality")]
        //public ItemsValuePair HasTalentsWithQuality { get; set; }

        [DataMember]
        [DisplayName("Has lamp")]
        [DisplayFormat(ConvertEmptyStringToNull = false)]
        public string HasLamp { get; set; }

        [DataMember]
        public int[] CompletedQuests { get; set; }

        [DataMember]
        public int[] NotCompletedQuests { get; set; }

        [DataMember]
        public int[] MissedQuests { get; set; }

        [DataMember]
        public int[] DependedTournamentQuests { get; set; }


        [DataMember]
        public string AuidList { get; set; }
    }

    [DataContract]
    public class QuestData
    {
        [DataMember(IsRequired = false)]
        [DisplayName("Objective ID")]
        public int EditId { get; set; }

        [DataMember]
        [DisplayName("Objective type")]
        public DynamicQuestCheckType QuestCheckType { get; set; }

        [DataMember]
        [DisplayName("Objective description")]
        [DisplayFormat(ConvertEmptyStringToNull = false)]
        public string Description { get; set; }

        [DataMember]
        [DisplayName("Objective button description")]
        [DisplayFormat(ConvertEmptyStringToNull = false)]
        public string ButtonDescription { get; set; }

        // Условия выполнения квеста
        [DataMember(IsRequired = false, EmitDefaultValue = false)]
        public SessionCondition SessionCondition { get; set; }

        [DataMember(IsRequired = false, EmitDefaultValue = false)]
        public InstantCondition InstantCondition { get; set; }

        [DataMember(IsRequired = false, EmitDefaultValue = false)]
        public ModelDataCondition ModelDataCondition { get; set; }

        [OnDeserializing]
        private void OnDeserializing(StreamingContext context)
        {
            SetDefaults();
        }

        [OnSerializing]
        private void OnSerializing(StreamingContext context)
        {
            SetDefaults();
        }

        private void SetDefaults()
        {
            if (Description == null) Description = "";
            if (ButtonDescription == null) ButtonDescription = "";
        }

        public QuestData()
        {
            SetDefaults();
        }
    }

    public class DynamicQuestAward
    {
        [DataMember]
        [DisplayName("Award type")]
        public DynamicQuestAwardType AwardType { get; set; }

        [DataMember(IsRequired = false, EmitDefaultValue = false)]
        [DisplayName("Value or persistentId")]
        public string Value { get; set; }

        [DataMember(IsRequired = false, EmitDefaultValue = false)]
        [DisplayName("Additional text data")]
        public string TextData { get; set; }

        [DataMember(IsRequired = false, EmitDefaultValue = false)]
        [DisplayName("Additional text data")]
        public string AdditionalData2 { get; set; }

        [DataMember]
        [DisplayName("Award condition")]
        public DynamicQuestAwardConditionType AwardConditionType { get; set; }
        
        /// <summary>
        /// Cheat for dealing with fields absent in javascript
        /// </summary>
        public void FillNullWithEmpty()
        {
            if (Value == null) Value = "";
            if (TextData == null) TextData = "";
            if (AdditionalData2 == null) AdditionalData2 = "";
        }
    }

    //CollectingType and IncrementPerBattle was harcoded in AddDynamicQuest.aspx
    [DataContract]
    public class SessionCondition
    {
        [DataMember]
        [DisplayName("Selected hero")]
        [DisplayFormat(ConvertEmptyStringToNull = false)]
        public string PickedHero { get; set; }     // Герой, которым надо выиграть бой (для сессионных квестов)

        [DataMember]
        [DisplayName("Game type")]
        [DisplayFormat(ConvertEmptyStringToNull = false)]
        public string GameType { get; set; }       // Тип игры, в который надо сходить (PvP, PvE..)

        [DataMember]
        [DisplayName("Type to collect")]
        [DisplayFormat(ConvertEmptyStringToNull = false)]
        public string CollectingType { get; set; } // Тип стата, который нужно набрать (kills, assists..)

        [DataMember]
        [DisplayName("Amount to collect")]
        public int TotalValue { get; set; }        // Кол-во, которое надо набрать

        /// <summary>
        /// Размер пати, в составе которой нужно сходить
        /// </summary>
        [DataMember(IsRequired = false)]
        [DefaultValue(1)]
        [DisplayName("Player party size !!!")]
        [Range(1, 5, ErrorMessage = "Party size must be from 1 to 5")]
        public int PlayerPartySize { get; set; }

        // NUM_TASK:
        [DataMember]
        [DefaultValue(0)]
        [DisplayName("Player party size - strong condition")]
        [Range(0, 1, ErrorMessage = "Value must be 0 or 1")]
        public int IsPlayerPartySizeStrongCond { get; set; }

        /// <summary>
        /// Размер пати, против которой которой нужно сходить
        /// </summary>
        [DataMember(IsRequired = false)]
        [DefaultValue(1)]
        [DisplayName("Enemy party size")]
        [Range(1, 5, ErrorMessage = "Party size must be from 1 to 5")]
        public int EnemyPartySize { get; set; }

        // NUM_TASK:
        [DataMember]
        [DefaultValue(0)]
        [DisplayName("Enemy party size - strong condition")]
        [Range(0, 1, ErrorMessage = "Value must be 0 or 1")]
        public int IsEnemyPartySizeStrongCond { get; set; }   

        [DataMember]
        [DisplayName("Increment per battle")]
        public int IncrementPerBattle { get; set; }// Максимальный прирост за одну битву

        [DataMember]
        [DisplayName("Session result influence")]
        public SessionCheckType SessionCheckType   // Засчитывать квесты за победу, за победу/поражение, или за поражение
        { get; set; }

        /// <summary>
        /// Засчитывать победу только в клановой игре или не учитывать тип игры
        /// </summary>
        [DataMember]
        [DefaultValue(0)]
        [DisplayName("Guild fight only")]
        [Range(0, 1, ErrorMessage = "Value must be 0 or 1")]
        public int IsGuildGame { get; set; }
    }

    [DataContract]
    public class InstantCondition
    {
        [DataMember]
        [DisplayName("Resource type")]
        public ResourcesEnum ResourceType { get; set; }

        [DataMember]
        [DisplayName("Amount")]
        public string TotalValue { get; set; }
    }

    [DataContract]
    public class ModelDataCondition
    {
        [DataMember]
        public ModelDataConditionType TypeToCollect { get; set; }
        [DataMember]
        [DisplayFormat(ConvertEmptyStringToNull = false)]
        public string PersistentId { get; set; }
        [DataMember]
        public int TotalValue { get; set; }
    }

    /// <summary>
    /// Model for showing dynamic quests in view
    /// </summary>
    public class DynamicQuestInfoModel
    {
        public DynamicQuestDataModel Data { get; set; }

        [DisplayName("PullId")]
        public int PullId { get; set; }

        [DisplayName("Locale")]
        public string Locale { get; set; }

        [DisplayName("Start time")]
        public string QuestStartTimeView { get; set; }

        [DisplayName("End time")]
        public string QuestEndTimeView { get; set; }

        /// <summary>
        /// Here stored int[] Quests in string for edit
        /// </summary>
        [DisplayName("Depends on completed quests (comma separated) (ex.: 1,2,3)")]
        [RegularExpression(@"((\d)+(,))*(\d)+")]
        public string CompletedQuests { get; set; }

        /// <summary>
        /// Here stored int[] Quests in string for edit
        /// </summary>
        [DisplayName("Depends on not completed quests (comma separated) (ex.: 1,2,3)")]
        [RegularExpression(@"((\d)+(,))*(\d)+")]
        public string NotCompletedQuests { get; set; }

        /// <summary>
        /// Here stored int[] Quests in string for edit
        /// </summary>
        [DisplayName("Depends on missed quests (comma separated) (ex.: 1,2,3)")]
        [RegularExpression(@"((\d)+(,))*(\d)+")]
        public string MissedQuests { get; set; }

        [DisplayName("Depends on tournaments quests (comma separated) (ex.: 1,2,3)")]
        [RegularExpression(@"((\d)+(,))*(\d)+")]
        public string DependedTournamentQuests { get; set; }


        /// <summary>
        /// Field for store result json
        /// </summary>
        [DisplayName("Raw quest data")]
        public String ResultJson { get; set; }

        /// <summary>
        /// You can edit this quest
        /// </summary>
        public Boolean Editable { get; set; }

        /// <summary>
        /// It's new quest (you can't edit ID, but can add new awards/objectives)
        /// </summary>
        public Boolean ExistingQuest { get; set; }

        /// <summary>
        /// Field to show warning
        /// </summary>
        public String Warning { get; set; }
        
        public SelectList SvcLocales;
        public SelectList AutoAcceptOptions;
        public SelectList RepeatOnMissOptions;
        public SelectList DonateOptions;
        public SelectList HasPremiumOptions;
        public SelectList InGuildOptions;
        public SelectList HasLampOptions;
        public SelectList FactionList;
        public SelectList HeroList;
        public SelectList ConstructionList;
        public SelectList MapList;

        public SelectList AwardTypes;
        public SelectList AwardConditionTypes;
        public SelectList QuestDataTypes;
        public SelectList SessionCheckType;
        public SelectList ResourcesEnum;
        public SelectList ModelDataConditionType;
        public SelectList DynamicQuestCollectingTypeEnum;
        public SelectList CWPointsType;
        public SelectList AuidLists;
        public SelectList PreConditionTypeList;
        public SelectList TournamentMapList;
        

        public DynamicQuestInfoModel()
        {
            Data = new DynamicQuestDataModel();
            ResultJson = "";
            Editable = true;
            ExistingQuest = false;
            Warning = "";
        }

        public DynamicQuestInfoModel(string json, string locale, int pullId)
        {
            Data = DynamicQuestDataModel.Deserialize(json);
            Locale = locale;
            PullId = pullId;
            ResultJson = "";
            Editable = true;
            ExistingQuest = true;
            Warning = "";
        }

        public void CorrectData()
        {
            if (Data.AcceptFilter.AuidList == null)
            {
                Data.AcceptFilter.AuidList = "0";
            }
            if (Data.Awards != null)
            {
                foreach (var award in Data.Awards)
                {
                    award.FillNullWithEmpty();
                }
            }
            if (Data.AlternativeAwards != null)
            {
                foreach (var award in Data.AlternativeAwards)
                {
                    award.FillNullWithEmpty();
                }
            }
        }

        public void FillFromData()
        {
            QuestStartTimeView = (new DateTime(1970, 1, 1, 0, 0, 0, 0, DateTimeKind.Utc)).AddSeconds(Data.QuestStartTime).ToString("dd'.'MM'.'yyyy HH:mm:ss");
            QuestEndTimeView = (new DateTime(1970, 1, 1, 0, 0, 0, 0, DateTimeKind.Utc)).AddSeconds(Data.QuestEndTime).ToString("dd'.'MM'.'yyyy HH:mm:ss");
            ResultJson = DynamicQuestDataModel.Serialize(Data);
            if (Data.AcceptFilter.CompletedQuests != null)
                CompletedQuests = String.Join(",", Data.AcceptFilter.CompletedQuests.Select(x => x.ToString()).ToArray());
            if (Data.AcceptFilter.NotCompletedQuests != null)
                NotCompletedQuests = String.Join(",", Data.AcceptFilter.NotCompletedQuests.Select(x => x.ToString()).ToArray());
            if (Data.AcceptFilter.MissedQuests != null)
                MissedQuests = String.Join(",", Data.AcceptFilter.MissedQuests.Select(x => x.ToString()).ToArray());
            if (Data.AcceptFilter.DependedTournamentQuests != null)
                DependedTournamentQuests = String.Join(",", Data.AcceptFilter.DependedTournamentQuests.Select(x => x.ToString()).ToArray());

        }

        public static bool ConvertStringToArrayOfInt(string source, out int[] array)
        {
            var list = new List<int>();
            array = new int[0];
            if (String.IsNullOrEmpty(source)) return true;
            foreach (var number in source.Split(','))
            {
                int temp;
                if (!Int32.TryParse(number.Trim(), out temp)) return false;
                list.Add(temp);
            }

            array = list.ToArray();
            return true;
        }

        public void FillSelectLists(IAccountService accountSvc, IDynamicQuestService dynamicQuestService)
        {
            SvcLocales = new SelectList(accountSvc.GetBroadcastLocales());
            AutoAcceptOptions = new SelectList(new List<string> { "False", "True" });
            RepeatOnMissOptions = new SelectList( new List<string> { "False", "True" } );
            DonateOptions = new SelectList(new List<string> { "", "False", "True" });
            HasPremiumOptions = new SelectList(new List<string> { "", "False", "True" });
            InGuildOptions = new SelectList(new List<string> { "", "False", "True" });
            HasLampOptions = new SelectList(new List<string> { "", "False", "True" });
            FactionList = new SelectList(new List<SelectListItem>
      {
        new SelectListItem {Text = "All", Value = "All"},
        new SelectListItem {Text = "Doct", Value = "A"},
        new SelectListItem {Text = "Adornian", Value = "B"}
      });
            HeroList = new SelectList(accountSvc.GetHeroesCatalog().Select(x => new SelectListItem { Text = x.HeroName, Value = x.HeroName }));
            ConstructionList = CastleBuildingsCatalog.GetPersistentIdOnlySelectList();
            MapList = new SelectList(new List<SelectListItem>
      {
        new SelectListItem {Text = "Borderland", Value = "/Maps/Multiplayer/MOBA/_.ADMPDSCR" },// Пограничье
        new SelectListItem {Text = "Dragonwald", Value = "/Maps/Multiplayer/CTE/PVP.ADMPDSCR" },// Драгонвальд
        new SelectListItem {Text = "NativeEarth", Value = "/Maps/Multiplayer/MOBA/Mod1/_.ADMPDSCR" },// Родная земля
        new SelectListItem {Text = "Outpost", Value = "/Maps/Multiplayer/MidOnly/_.ADMPDSCR" },// Форпост
        new SelectListItem {Text = "Leapfrog", Value = "/Maps/Multiplayer/MOBA/Mod3/_.ADMPDSCR" },// Чехарда
        new SelectListItem {Text = "Zombieland", Value = "/Maps/Multiplayer/MOBA/Mod2/_.ADMPDSCR" },// Конец света
        new SelectListItem {Text = "Blue PvE", Value = "/Maps/PvE/Series/Coop1/Blue.ADMPDSCR" },// Синее
        new SelectListItem {Text = "Green PvE", Value = "/Maps/PvE/Series/Coop1/Green.ADMPDSCR" },// Зелёное
        new SelectListItem {Text = "Orange PvE", Value = "/Maps/PvE/Series/Coop1/Orange.ADMPDSCR" },// Рыжее
        new SelectListItem {Text = "Violet PvE", Value = "/Maps/PvE/Series/Coop1/Violet.ADMPDSCR" },// Фиолетовое
        new SelectListItem {Text = "Red PvE", Value = "/Maps/PvE/Series/Coop1/Red.ADMPDSCR" },// Красное
        
        // Турнирные карты 
        new SelectListItem {Text = "Bronze", Value = "/Maps/Multiplayer/MOBA/Mod5/_.ADMPDSCR" },
        new SelectListItem {Text = "Silver", Value = "/Maps/Multiplayer/MOBA/Mod7/_.ADMPDSCR" },
        new SelectListItem {Text = "Gold", Value = "/Maps/Multiplayer/MOBA/Mod8/_.ADMPDSCR" }, 
      });

      TournamentMapList = new SelectList(new List<SelectListItem>
          {
              new SelectListItem {Text = "Bronze", Value = "/Maps/Multiplayer/MOBA/Mod5/_.ADMPDSCR"},
              new SelectListItem {Text = "Silver", Value = "/Maps/Multiplayer/MOBA/Mod7/_.ADMPDSCR"},
              new SelectListItem {Text = "Gold", Value = "/Maps/Multiplayer/MOBA/Mod8/_.ADMPDSCR"},
              new SelectListItem {Text = "NoMap", Value = "", Selected = true},

          });
        
       PreConditionTypeList =
                new SelectList(
                    Enum.GetValues(typeof(DynamicQuestPreConditionType))
                        .Cast<Enum>()
                        .Select(e => new SelectListItem { Text = e.ToString(), Value = e.ToString() }));


            AwardTypes =
              new SelectList(
                Enum.GetValues(typeof(DynamicQuestAwardType))
                  .Cast<Enum>()
                  .Select(e => new SelectListItem { Text = e.ToString(), Value = e.ToString() }));
            
            AwardConditionTypes =
              new SelectList(
                Enum.GetValues(typeof(DynamicQuestAwardConditionType))
                  .Cast<Enum>()
                  .Select(e => new SelectListItem { Text = e.ToString(), Value = e.ToString() })); 

            QuestDataTypes =
              new SelectList(
                Enum.GetValues(typeof(DynamicQuestCheckType))
                  .Cast<Enum>()
                  .Select(e => new SelectListItem { Text = e.ToString(), Value = e.ToString() }));
            
            SessionCheckType =
              new SelectList(
                Enum.GetValues(typeof(SessionCheckType))
                  .Cast<Enum>()
                  .Select(e => new SelectListItem { Text = e.ToString(), Value = e.ToString() }));
            
            ResourcesEnum =
              new SelectList(
                Enum.GetValues(typeof(ResourcesEnum))
                  .Cast<Enum>()
                  .Select(e => new SelectListItem { Text = e.ToString(), Value = e.ToString() }));
            
            ModelDataConditionType =
              new SelectList(
                Enum.GetValues(typeof(ModelDataConditionType))
                  .Cast<Enum>()
                  .Select(e => new SelectListItem { Text = e.ToString(), Value = e.ToString() }));
            
            DynamicQuestCollectingTypeEnum =
              new SelectList(
                Enum.GetValues(typeof(DynamicQuestCollectingTypeEnum))
                  .Cast<Enum>()
                  .Select(e => new SelectListItem { Text = e.ToString(), Value = e.ToString() }));
            
            CWPointsType = new SelectList(new List<SelectListItem>
      {
        new SelectListItem {Text = "CWPoints_Clan", Value = "CWPoints_Clan" },
        new SelectListItem {Text = "CWPoints_Player", Value = "CWPoints_Player" }
      });
            AuidLists =
              new SelectList(
                (new List<SelectListItem> { new SelectListItem { Text = "", Value = "" } }).Concat(
                  dynamicQuestService.GetAuidsLists()
                    .Lists.Select(x => new SelectListItem { Text = x.Description, Value = x.Index.ToString() })));
        
        
            
        }

        public List<SelectListItem> SetSelected(SelectList list, string selectedItem)
        {
            var tempList = list.Items.OfType<SelectListItem>().ToList();
            foreach (var item in tempList)
            {
                item.Selected = item.Value == selectedItem;
            }

            return tempList;
        }

        public static string GetAllTexts(SelectList list)
        {
            return String.Join("\", \"",
              list.Items.OfType<SelectListItem>().ToList().Count == 0
                ? list.Select(x => x.Text).ToArray()
                : list.Items.OfType<SelectListItem>().ToList().Select(x => x.Text).ToArray());
        }

        public static string GetAllValues(SelectList list)
        {
            return String.Join("\", \"", list.Items.OfType<SelectListItem>().ToList().Select(x => x.Value).ToArray());
        }

        public string GetObjectiveTypes()
        {
            var objectiveTypes = new Dictionary<DynamicQuestCheckType, int>();
            objectiveTypes = GetAllCheckTypes(objectiveTypes, Data.QuestData);
            objectiveTypes = GetAllCheckTypes(objectiveTypes, Data.AlternativeQuestData);
            return String.Join(", ", objectiveTypes.Keys.Select(x => x.ToString()).ToArray());
        }

        private Dictionary<DynamicQuestCheckType, int> GetAllCheckTypes(
          Dictionary<DynamicQuestCheckType, int> objectiveTypes, List<QuestData> questData)
        {
            if (questData == null) return objectiveTypes;
            foreach (var objective in questData)
            {
                if (objectiveTypes.ContainsKey(objective.QuestCheckType))
                {
                    objectiveTypes[objective.QuestCheckType]++;
                }
                else
                {
                    objectiveTypes.Add(objective.QuestCheckType, 1);
                }
            }
            return objectiveTypes;
        }
    }

    /// <summary>
    /// Class with information about quest pull
    /// </summary>
    public class DynamicQuestPullModel
    {
        [DisplayName("Rotation start")]
        public DateTime RotationStartTime { get; set; }
        [DisplayName("Rotation end")]
        public DateTime RotationEndTime { get; set; }
        [DisplayName("Reset pull after all quests are done")]
        public bool HasRotation { get; set; }
        [DisplayName("Locale")]
        public string Locale { get; set; }
        [DisplayName("PersistentId")]
        public int PullId { get; set; }
        [DisplayName("Active")]
        public bool IsWorking { get; set; }
        [DisplayName("Quests")]
        public List<int> Quests { get; set; }

        public SelectList SvcLocales { get; set; }

        public string GetQuests()
        {
            if (Quests.Count != 0)
            {
                return Quests.Aggregate("", (current, questId) => current + (questId.ToString() + " "));
            }
            return " ";
        }

        public DynamicQuestPullModel()
        {
            Quests = new List<int>();
            RotationStartTime = DateTime.Now;
            RotationEndTime = DateTime.Now;
        }
        public DynamicQuestPullModel(DynamicQuestPullModel pull)
        {
            RotationStartTime = pull.RotationStartTime;
            RotationEndTime = pull.RotationEndTime;
            HasRotation = pull.HasRotation;
            PullId = pull.PullId;
            Locale = pull.Locale;
            IsWorking = pull.IsWorking;
            Quests = new List<int>(pull.Quests);
        }
    }

    // Model for AddQuestsToPull/RemoveQuestsFromPull views
    public class DynamicQuestShortInfoModel
    {
        [DisplayName("Description")]
        public string QuestName { get; set; }
        [DisplayName("QuestId")]
        public int QuestId { get; set; }
    }
}