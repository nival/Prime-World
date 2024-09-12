<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<DynamicQuestInfoModel>" %>
<%@ Import Namespace="NHibernate.Type" %>
<%@ Import Namespace="log4net" %>
<%@ Import Namespace="AccountLib" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	DynamicQuestInfo
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <link href="../../../../Content/jquery-ui-1.8.17.custom.css" rel="stylesheet" type="text/css" />
  <style type="text/css">
    .filter { border: 0; }
    .filter td { border: 0; }

    select
    {
      width: 200px;
      border: 1px solid #CCC;
    }
    p
    {
      margin: 0;
    }

    .DynamicQuestsInfoBlocs
    {
      float: left;
      margin: 5px;
    }

    .LayoutTable
    {
      padding: 0;
      border: 0;
    }

    .hidden {
        display:none;
    }

    .visible {
        display:block;
    }
  </style>
  <script type="text/javascript" src="/Scripts/jquery-ui-1.8.16.custom.min.js"></script>
  <script type="text/javascript" src="/Scripts/jquery.localizeDate.js"></script>
  <script type="text/javascript" src="/Scripts/jquery-ui-timepicker-addon.js"></script>
  <script type="text/javascript" src="/Scripts/jquery-ui-sliderAccess.js"></script>
  <script type="text/javascript" src="/Scripts/PageSpecific/DynamicQuestInfo.js?version=2"></script>
  <script type="text/javascript" src="/Scripts/CommonScripts.js"></script>

  <script type="text/javascript">

      function GlobalToUtc(string) {
          var utcTicks = stringToUtcTicks(string);
          utcTicks -= getGlobalTicksOffcet();
          return utcTicks;
      };

      var DynamicQuestEnum = DynamicQuestEnum || {};
      DynamicQuestEnum.QuestTypeEnum = "";
      DynamicQuestEnum.SessionCheckTypeEnum = "";
      DynamicQuestEnum.CollectingTypeEnum = "";
      DynamicQuestEnum.ResourcesEnum = "";
      DynamicQuestEnum.DynamicQuestAwardType = "";
      DynamicQuestEnum.DynamicQuestAwardConditionType = "";
      DynamicQuestEnum.DynamicQuestMaps = "";
      DynamicQuestEnum.DynamicQuestMapsValues = "";
      DynamicQuestEnum.DynamicQuestHeroes = "";
      DynamicQuestEnum.DynamicQuestHeroesValues = "";
      DynamicQuestEnum.DynamicQuestConstructions = "";
      DynamicQuestEnum.ModelDataConditionEnum = "";
      DynamicQuestEnum.DynamicQuestPreConditionType = "";
      DynamicQuestEnum.DynamicQuestTournamentMaps = "";
      DynamicQuestEnum.DynamicQuestTournamentMapsValues = "";


      function FillDynamicQuestEnum() {
          DynamicQuestEnum.QuestTypeEnum = eval([<% ="\"" + DynamicQuestInfoModel.GetAllTexts(Model.QuestDataTypes) + "\"" %>]);
          DynamicQuestEnum.SessionCheckTypeEnum = eval([<% ="\"" + DynamicQuestInfoModel.GetAllTexts(Model.SessionCheckType) + "\"" %>]);
          DynamicQuestEnum.CollectingTypeEnum = eval([<% ="\"" + DynamicQuestInfoModel.GetAllTexts(Model.DynamicQuestCollectingTypeEnum) + "\"" %>]);
          DynamicQuestEnum.ResourcesEnum = eval([<% ="\"" + DynamicQuestInfoModel.GetAllTexts(Model.ResourcesEnum) + "\"" %>]);
          DynamicQuestEnum.DynamicQuestAwardType = eval([<% ="\"" + DynamicQuestInfoModel.GetAllTexts(Model.AwardTypes) + "\"" %>]);
          DynamicQuestEnum.DynamicQuestAwardConditionType = eval([<% ="\"" + DynamicQuestInfoModel.GetAllTexts(Model.AwardConditionTypes) + "\"" %>]);
          DynamicQuestEnum.DynamicQuestMaps = eval([<%="\"" + DynamicQuestInfoModel.GetAllTexts(Model.MapList) + "\"" %>]);
          DynamicQuestEnum.DynamicQuestMapsValues = eval([<% ="\"" + DynamicQuestInfoModel.GetAllValues(Model.MapList) + "\"" %>]);
          DynamicQuestEnum.DynamicQuestHeroes = eval([<% ="\"" + DynamicQuestInfoModel.GetAllTexts(Model.HeroList) + "\"" %>]);
          DynamicQuestEnum.DynamicQuestHeroesValues = eval([<% ="\"" + DynamicQuestInfoModel.GetAllValues(Model.HeroList) + "\"" %>]);
          DynamicQuestEnum.DynamicQuestConstructions = eval([<% ="\"" + DynamicQuestInfoModel.GetAllTexts(Model.ConstructionList) + "\"" %>]);
          DynamicQuestEnum.ModelDataConditionEnum = eval([<% ="\"" + DynamicQuestInfoModel.GetAllTexts(Model.ModelDataConditionType) + "\"" %>]);
          DynamicQuestEnum.DynamicQuestPreConditionType = eval([<% = "\"" + DynamicQuestInfoModel.GetAllTexts(Model.PreConditionTypeList) + "\"" %>]);
          DynamicQuestEnum.DynamicQuestTournamentMaps = eval([<%="\"" + DynamicQuestInfoModel.GetAllTexts(Model.TournamentMapList) + "\"" %>]);;
          DynamicQuestEnum.DynamicQuestTournamentMapsValues = eval([<% ="\"" + DynamicQuestInfoModel.GetAllValues(Model.TournamentMapList) + "\"" %>]);;

      }

      function OnDocumentReady() {
          FillDynamicQuestEnum();
          localizeDate();
          $("#QuestStartTimeView, #QuestEndTimeView").datetimepicker({
              dateFormat: "dd.mm.yy",
              separator: " ",
              timeFormat: "hh:mm:ss",
              ampm: false,
              showSecond: true
          });

          $("#ShowJson").click(function () {
              var $this = $("#ResultJson");
              if ($this.hasClass("hidden")) {
                  $this.removeClass("hidden").addClass("visible");
              } else {
                  $this.removeClass("visible").addClass("hidden");
              }
          });

          $("#QuestStartTimeView").change(function () {
              $("#Data_QuestStartTime")[0].value = GlobalToUtc($(this)[0].value) / 1000;
          });
          $("#QuestEndTimeView").change(function () {
              $("#Data_QuestEndTime")[0].value = GlobalToUtc($(this)[0].value) / 1000;
          });
          
          AddPreConditions();
          AddCommonObjectives();
          AddAlternativeObjectives();
          AddCommonAwards();
          AddAlternativeAwards();
          AddListBoxes();
          

      };

      $(document).ready(OnDocumentReady);
  </script>
 
  <h2>AddQuest</h2>
  <% using (Html.BeginForm(null, null, FormMethod.Post, new {name = "AddDynamicQuest", id = "AddDynamicQuest"}))
     { %>
  <% if (!String.IsNullOrEmpty(Model.Warning))
     { %>
       <p style="background-color:yellow;color:red"><b>
      <%= Html.Label(Model.Warning) %>
    </b></p>
     <% } %>
    <div class="pagemenu">
        <p><%= Html.ActionLink("Back to list", "Overview", "DynamicQuest") %></p>
        <br/>
        <p><%= Html.ActionLink("Auid lists", "Index", "AuidList") %></p>
        <p>
            <%= Html.ActionLink("Add new auid list", "AuidListMember", "AuidList") %>
            <br/>
            After adding new list on another tab, use "Preview" button to refresh
        </p>
    </div>

    <div>
      <div class="editor-field">
        <%= Html.TextBoxFor(model => model.Data.QuestId, new {hidden = true}) %>
      </div>
      <div class="editor-field">
        <%= Html.TextBoxFor(model => model.ExistingQuest, new {hidden = true}) %>
      </div>
      <div class="editor-field">
        <%= Html.TextBoxFor(model => model.Editable, new {hidden = true}) %>
      </div>
      <div class="editor-label">
        <%= Html.LabelFor(model => model.Locale) %>
      </div>
      <div class="editor-field">
          <%= Html.DropDownListFor(model => model.Locale, Model.SvcLocales) %>
          <%= Html.ValidationMessageFor(model => model.Locale) %>
      </div>
      <div class="editor-label">
        <%= Html.LabelFor(model => model.Data.NPCPortret) %>
      </div>
      <div class="editor-field">
        <%= Html.TextBoxFor(model => model.Data.NPCPortret, new {@value = ""}) %>
        <%= Html.ValidationMessageFor(model => model.Data.NPCPortret) %>
      </div>
      <div class="editor-label">
        <%= Html.LabelFor(model => model.Data.QuestName) %>
      </div>
      <div class="editor-field">
        <%= Html.TextBoxFor(model => model.Data.QuestName) %>
        <%= Html.ValidationMessageFor(model => model.Data.QuestName) %>
      </div>
      <div class="editor-label">
        <%= Html.LabelFor(model => model.Data.QuestDescription) %>
      </div>
      <div class="editor-field">
        <%= Html.TextAreaFor(model => model.Data.QuestDescription) %>
        <%= Html.ValidationMessageFor(model => model.Data.QuestDescription) %>
      </div>

      <div class="editor-label">
        <%= Html.LabelFor(model => model.Data.DescriptionImageUrl) %>
      </div>
      <div class="editor-field">
        <%= Html.TextBoxFor(model => model.Data.DescriptionImageUrl, new {@value = ""}) %>
        <%= Html.ValidationMessageFor(model => model.Data.DescriptionImageUrl) %>
      </div>
      <div class="editor-label">
        <%= Html.LabelFor(model => model.Data.CompletionText) %>
      </div>
      <div class="editor-field">
        <%= Html.TextAreaFor(model => model.Data.CompletionText) %>
        <%= Html.ValidationMessageFor(model => model.Data.CompletionText) %>
      </div>
      <div class="editor-label">
        <%-- ReSharper disable once Html.IdNotResolved --%>
        <label for="QuestStartTimeView" class="timeZoneLabel">Quest start time, UTC+0</label>
      </div>
      <div class="editor-field">
        <%--При изменении QuestStartTimeView javascript переводит время в UTC и пишет в QuestStartTime--%>
        <%--Так сделано потому, что я хочу, чтобы при правках скрипта localizeDate у нас ничего не поломалось--%>
        <%= Html.HiddenFor(model => model.Data.QuestStartTime) %>
        <%= Html.TextBoxFor(m => m.QuestStartTimeView, new {@class = "utcdateVal"}) %>
      </div>
      <div class="editor-label">
        <%-- ReSharper disable once Html.IdNotResolved --%>
        <label for="QuestEndTimeView" class="timeZoneLabel">  Quest end time, UTC+0</label>
      </div>
      <div class="editor-field">
        <%--При изменении QuestEndTimeView javascript переводит время в UTC и пишет в QuestEndTime--%>
        <%--Так сделано потому, что я хочу, чтобы при правках скрипта localizeDate у нас ничего не поломалось--%>
        <%= Html.HiddenFor(model => model.Data.QuestEndTime) %>
        <%= Html.TextBoxFor(m => m.QuestEndTimeView, new {@class = "utcdateVal"}) %>
      </div>
      <div class="editor-label">
        <%= Html.LabelFor(model => model.Data.AutoAccept) %>
      </div>
      <div class="editor-field">
        <%= Html.DropDownListFor(model => model.Data.AutoAccept, Model.AutoAcceptOptions) %>
      </div>
      <div class="editor-label">
        <%= Html.LabelFor( model => model.Data.RepeatOnMiss )%>
      </div>
      <div class="editor-field">
        <%= Html.DropDownListFor( model => model.Data.RepeatOnMiss, Model.RepeatOnMissOptions )%>
      </div>
      <div>
      <%= Html.Partial("_preconditions", Model) %>
          <br/>
      </div>

      <div>
        <table>
          <tr>
            <th>Accept conditions</th>
          </tr>
          <tr>
            <td>
              <div class="editor-label">
                <%= Html.LabelFor(model => model.Data.AcceptFilter.MinLordLevel)%>
              </div>
              <div class="editor-field">
                <%= Html.TextBoxFor(model => model.Data.AcceptFilter.MinLordLevel)%>
                <%= Html.ValidationMessageFor(model => model.Data.AcceptFilter.MinLordLevel)%>
              </div>
            </td>
            <td>
              <div class="editor-label">
                <%= Html.LabelFor(model => model.Data.AcceptFilter.MaxLordLevel)%>
              </div>
              <div class="editor-field">
                <%= Html.TextBoxFor(model => model.Data.AcceptFilter.MaxLordLevel)%>
                <%= Html.ValidationMessageFor(model => model.Data.AcceptFilter.MaxLordLevel)%>
              </div>
            </td>
            <td>
              <div class="editor-label">
                <%= Html.LabelFor(model => model.Data.AcceptFilter.Faction)%>
              </div>
              <div class="editor-field">
                <%= Html.DropDownListFor(model => model.Data.AcceptFilter.Faction, (Model.FactionList).Items.OfType<SelectListItem>())%>
              </div>
            </td>
          </tr>
          <tr>
            <td>
              <div class="editor-label">
                <%= Html.LabelFor(model => model.Data.AcceptFilter.NoHero)%>
              </div>
              <div class="editor-field">
                <%= Html.TextBoxFor(model => model.Data.AcceptFilter.NoHero)%>
                <%= Html.ValidationMessageFor(model => model.Data.AcceptFilter.NoHero)%>
              </div>
            </td>
            <td>
              <div class="editor-label">
                <%= Html.LabelFor(model => model.Data.AcceptFilter.NoSkin)%>
              </div>
              <div class="editor-field">
                <%= Html.TextBoxFor(model => model.Data.AcceptFilter.NoSkin)%>
                <%= Html.ValidationMessageFor(model => model.Data.AcceptFilter.NoSkin)%>
              </div>
            </td>
            <td>
              <div class="editor-label">
                <%= Html.LabelFor(model => model.Data.AcceptFilter.NoFlag)%>
              </div>
              <div class="editor-field">
                <%= Html.TextBoxFor( model => model.Data.AcceptFilter.NoFlag )%>
                <%= Html.ValidationMessageFor( model => model.Data.AcceptFilter.NoFlag )%>
              </div>
            </td>
          </tr>
          <tr>
            <td>
              <div class="editor-label">
                <%= Html.LabelFor(model => model.Data.AcceptFilter.NoBuilding)%>
              </div>
              <div class="editor-field">
                <%= Html.TextBoxFor( model => model.Data.AcceptFilter.NoBuilding )%>
                <%= Html.ValidationMessageFor( model => model.Data.AcceptFilter.NoBuilding )%>
              </div>
            </td>
            <td>
              <div>
                <div class="editor-label">
                  <%= Html.LabelFor(model => model.Data.AcceptFilter.LastPaymentTime)%>
                </div>
                <div class="editor-field">
                  <%= Html.TextBoxFor(model => model.Data.AcceptFilter.LastPaymentTime)%>
                  <%= Html.ValidationMessageFor(model => model.Data.AcceptFilter.LastPaymentTime)%>
                </div>
              </div>
            </td>
            <td>
              <div class="editor-label">
                <%= Html.LabelFor(model => model.Data.AcceptFilter.LastLoginTime)%>
              </div>
              <div class="editor-field">
                <%= Html.TextBoxFor(model => model.Data.AcceptFilter.LastLoginTime)%>
                <%= Html.ValidationMessageFor(model => model.Data.AcceptFilter.LastLoginTime)%>
              </div>
            </td>
          </tr>
          <tr>
            <td>
              <div id="HasHeroesWithRating">
                <div class="editor-label">
                  <%= Html.LabelFor(model => model.Data.AcceptFilter.HeroesOfMinRating)%>
                </div>
                <table>
                  <tr>
                    <td class="LayoutTable">
                      Heroes:
                    </td>
                    <td class="LayoutTable">
                      <div class="editor-field" id="HasHeroesWithMinRating.Items">
                        <%= Html.TextBoxFor( model => model.Data.AcceptFilter.HeroesOfMinRating.Items )%>
                        <%= Html.ValidationMessageFor( model => model.Data.AcceptFilter.HeroesOfMinRating.Items )%>
                      </div>
                    </td>
                  </tr>
                  <tr>
                    <td class="LayoutTable">
                      Rating:
                    </td>
                    <td class="LayoutTable">
                      <div class="editor-field" id="HasHeroesWithMinRating.Value">
                        <%= Html.TextBoxFor( model => model.Data.AcceptFilter.HeroesOfMinRating.Value )%>
                        <%= Html.ValidationMessageFor( model => model.Data.AcceptFilter.HeroesOfMinRating.Value )%>
                      </div>
                    </td>
                  </tr>
                </table>
              </div>
            </td>
            <td>
              <div id="HasHeroesWithPower">
                <div class="editor-label">
                  <%= Html.LabelFor(model => model.Data.AcceptFilter.HeroesOfForce)%>
                </div>
                <table>
                  <tr>
                    <td class="LayoutTable">
                      Heroes:
                    </td>
                    <td class="LayoutTable">
                      <div class="editor-field" id="HasHeroesWithPower.Items">
                        <%= Html.TextBoxFor(model => model.Data.AcceptFilter.HeroesOfForce.Items)%>
                        <%= Html.ValidationMessageFor(model => model.Data.AcceptFilter.HeroesOfForce.Items)%>
                      </div>
                    </td>
                  </tr>
                  <tr>
                    <td class="LayoutTable">
                      Power:
                    </td>
                    <td class="LayoutTable">
                      <div class="editor-field" id="HasHeroesWithPower.Value">
                        <%= Html.TextBoxFor(model => model.Data.AcceptFilter.HeroesOfForce.Value)%>
                        <%= Html.ValidationMessageFor(model => model.Data.AcceptFilter.HeroesOfForce.Value)%>
                      </div>
                    </td>
                  </tr>
                </table>
              </div>
            </td>
            <td>
              <div id="HasHeroesWithLevel">
                <div class="editor-label">
                  <%= Html.LabelFor(model => model.Data.AcceptFilter.HeroesOfLevel)%>
                </div>
                <table>
                  <tr>
                    <td class="LayoutTable">
                      Heroes count:
                    </td>
                    <td class="LayoutTable">
                      <div class="editor-field" id="HasHeroesWithLevel.Items">
                        <%= Html.TextBoxFor(model => model.Data.AcceptFilter.HeroesOfLevel.Items)%>
                        <%= Html.ValidationMessageFor(model => model.Data.AcceptFilter.HeroesOfLevel.Items)%>
                      </div>
                    </td>
                  </tr>
                  <tr>
                    <td class="LayoutTable">
                      Level:
                    </td>
                    <td class="LayoutTable">
                      <div class="editor-field" id="HasHeroesWithLevel.Value">
                        <%= Html.TextBoxFor(model => model.Data.AcceptFilter.HeroesOfLevel.Value)%>
                        <%= Html.ValidationMessageFor(model => model.Data.AcceptFilter.HeroesOfLevel.Value)%>
                      </div>
                    </td>
                  </tr>
                </table>
              </div>
            </td>
          </tr>
          <tr>
            <td>
              <div id="Div1">
                <div class="editor-label">
                  <%= Html.LabelFor( model => model.Data.AcceptFilter.HeroesOfMaxRating )%>
                </div>
                <table>
                  <tr>
                    <td class="LayoutTable">
                      Heroes:
                    </td>
                    <td class="LayoutTable">
                      <div class="editor-field" id="HasHeroesWithMaxRating.Items">
                        <%= Html.TextBoxFor( model => model.Data.AcceptFilter.HeroesOfMaxRating.Items )%>
                        <%= Html.ValidationMessageFor( model => model.Data.AcceptFilter.HeroesOfMaxRating.Items )%>
                      </div>
                    </td>
                  </tr>
                  <tr>
                    <td class="LayoutTable">
                      Rating:
                    </td>
                    <td class="LayoutTable">
                      <div class="editor-field" id="HasHeroesWithMaxRating.Value">
                        <%= Html.TextBoxFor( model => model.Data.AcceptFilter.HeroesOfMaxRating.Value )%>
                        <%= Html.ValidationMessageFor( model => model.Data.AcceptFilter.HeroesOfMaxRating.Value )%>
                      </div>
                    </td>
                  </tr>
                </table>
              </div>
            </td>            
            <td>
              <div id="HasConstructionsWithLevel">
                <div class="editor-label">
                  <%= Html.LabelFor(model => model.Data.AcceptFilter.BuildingOfLevel)%>
                </div>
                <table>
                  <tr>
                    <td class="LayoutTable">
                      Constructions:
                    </td>
                    <td class="LayoutTable">
                      <div class="editor-field" id="HasConstructionsWithLevel.Items">
                        <%= Html.TextBoxFor(model => model.Data.AcceptFilter.BuildingOfLevel.Items)%>
                        <%= Html.ValidationMessageFor(model => model.Data.AcceptFilter.BuildingOfLevel.Items)%>
                      </div>
                    </td>
                  </tr>
                  <tr>
                    <td class="LayoutTable">
                      Level:
                    </td>
                    <td class="LayoutTable">
                      <div class="editor-field" id="HasConstructionsWithLevel.Value">
                        <%= Html.TextBoxFor(model => model.Data.AcceptFilter.BuildingOfLevel.Value)%>
                        <%= Html.ValidationMessageFor(model => model.Data.AcceptFilter.BuildingOfLevel.Value)%>
                      </div>
                    </td>
                  </tr>
                </table>
              </div>
            </td>
            <td>
              <div class="editor-label">
                <%= Html.LabelFor(model => model.Data.AcceptFilter.InGuild)%>
              </div>
              <div class="editor-field">
                <%= Html.DropDownListFor(model => model.Data.AcceptFilter.InGuild, Model.InGuildOptions)%>
              </div>
            </td>
          </tr>
          <tr>
            <td>
              <div class="editor-label">
                <%= Html.LabelFor(model => model.Data.AcceptFilter.Donate)%>
              </div>
              <div class="editor-field">
                <%= Html.DropDownListFor(model => model.Data.AcceptFilter.Donate, Model.DonateOptions)%>
              </div>
            </td>
            <td>
              <div class="editor-label">
                <%= Html.LabelFor(model => model.Data.AcceptFilter.HasPremium)%>
              </div>
              <div class="editor-field">
                <%= Html.DropDownListFor(model => model.Data.AcceptFilter.HasPremium, Model.HasPremiumOptions)%>
              </div>
            </td>
            <td>
              <div class="editor-label">
                <%= Html.LabelFor(model => model.Data.AcceptFilter.HasLamp)%>
              </div>
              <div class="editor-field">
                <%= Html.DropDownListFor(model => model.Data.AcceptFilter.HasLamp, Model.HasLampOptions)%>
              </div>
            </td>
          </tr>
          <tr>
            <td>
              <div class="editor-label">
                <%= Html.LabelFor(model => model.CompletedQuests)%>
              </div>
              <div class="editor-field">
                <%= Html.TextBoxFor(model => model.CompletedQuests)%>
                <%= Html.ValidationMessageFor(model => model.CompletedQuests)%>
              </div>
            </td>
            <td>
              <div class="editor-label">
                <%= Html.LabelFor(model => model.NotCompletedQuests)%>
              </div>
              <div class="editor-field">
                <%= Html.TextBoxFor(model => model.NotCompletedQuests)%>
                <%= Html.ValidationMessageFor(model => model.NotCompletedQuests)%>
              </div>
            </td>
            <td>
              <div class="editor-label">
                <%= Html.LabelFor(model => model.MissedQuests)%>
              </div>
              <div class="editor-field">
                <%= Html.TextBoxFor(model => model.MissedQuests)%>
                <%= Html.ValidationMessageFor(model => model.MissedQuests)%>
              </div>
            </td>
            <td>
              <div class="editor-label">
                <%= Html.LabelFor(model => model.DependedTournamentQuests)%>
              </div>
              <div class="editor-field">
                <%= Html.TextBoxFor(model => model.DependedTournamentQuests)%>
                <%= Html.ValidationMessageFor(model => model.DependedTournamentQuests)%>
              </div>
            </td>

          </tr>
        <tr>
          <td>
              <div class="editor-label">
                <%= Html.LabelFor(model => model.Data.AcceptFilter.AuidList)%>
              </div>
              <div class="editor-field">
                <%= Html.DropDownListFor(model => model.Data.AcceptFilter.AuidList,
                  Model.SetSelected(Model.AuidLists, Model.Data.AcceptFilter.AuidList))%>
                <%= Html.ValidationMessageFor(model => model.Data.AcceptFilter.AuidList)%>
              </div>
            </td>
        </tr>
        </table>
      </div>
      <% for (var i = 0; i < 2; i++)
         {
           List<QuestData> questDataList;
           string questDataListString;
        %>
      <div>
        <% if (i == 0)
           {
             questDataList = Model.Data.QuestData;
             questDataListString = "QuestData";
             %>
        <h3>Objectives</h3>
        <% if (Model.Editable && !Model.ExistingQuest)
        { %>
            <div class="add-objective" id="AddObjective">
              <a href="javascript: void(0)">Add new objective</a>
            </div>
        <% } %>
        <%
        }
        else
        {
             questDataList = Model.Data.AlternativeQuestData;
             questDataListString = "AlternativeQuestData";
             %>
        <h3>Alternative objectives</h3>
        <% if (Model.Editable && !Model.ExistingQuest)
        { %>
            <div class="add-alternative-objective" id="AddAlternativeObjective">
              <a href="javascript: void(0)">Add new alternative objective</a>
            </div>
        <% } %>
        <%
        }
        %>
        <table id="<%=questDataListString%>">
        <%
          QuestData questData = null;
          var objIndex = 0;
          if (questDataList == null) continue;
          foreach (var objective in questDataList)
          {
              questData = objective; %>
            <tr>
              <td>
                <table>
                  <tr>
                    <th>Objective type</th>
                    <th>Description</th>
                    <th>ButtonDescription</th>
                  </tr>
                  <tr class="<%=questDataListString%>-container" id="<%=questDataListString%>Container<%= Html.Encode(objIndex) %>">
                    <td>
                      <%= Html.TextBox( "Data." + questDataListString + "[" + objIndex + "].EditId",
                        objIndex, new { id = "Data_" + questDataListString + "[" + objIndex + "]_EditId",
                        hidden = true } )%>
                      <% if (Model.ExistingQuest || !Model.Editable) { %>
                      <%= Html.DropDownList("Data." + questDataListString + "[" + objIndex + "].QuestCheckType",
                          Model.SetSelected(Model.QuestDataTypes, objective.QuestCheckType.ToString()),
                          new { id = "Data_" + questDataListString + "[" + objIndex + "]_QuestCheckType",
                          disabled = Model.ExistingQuest && Model.Editable })%>
                      <%=Html.Hidden("Data." + questDataListString + "[" + objIndex + "].QuestCheckType",
                        objective.QuestCheckType.ToString(),
                        new {id = "Data_" + questDataListString + "[" + objIndex + "]_QuestCheckType"})%>
                      <% } else {%>
                      <%= Html.DropDownList("Data." + questDataListString + "[" + objIndex + "].QuestCheckType",
                          Model.SetSelected(Model.QuestDataTypes, objective.QuestCheckType.ToString()),
                          new { id = "Data_" + questDataListString + "[" + objIndex + "]_QuestCheckType"})%>
                      <% } %>
                    </td>
                    <td><%= Html.TextBox("Data." + questDataListString + "[" + objIndex + "].Description",
                        objective.Description,
                        new { id = "Data_" + questDataListString + "[" + objIndex + "]_Description" })%></td>
                    <td><%= Html.TextBox("Data." + questDataListString + "[" + objIndex + "].ButtonDescription",
                        objective.ButtonDescription,
                          new { id = "Data_" + questDataListString + "[" + objIndex + "]_ButtonDescription" })%></td>
                    <% if (Model.Editable && !Model.ExistingQuest)
                    { %>
                        <td class="remove-<%=questDataListString%>"><a href="javascript: void(0)">Remove</a></td>
                    <% } %>
                    </tr>
                  <tr class="<%=questDataListString%>-condition">
                    <td colspan="4">
                      <table>
                        <tr>
                          <th>Conditions</th>
                        </tr>
                        <% if (Equals(objective.QuestCheckType.ToString(), "SessionResult"))
                          { %>
                            <tr>
                              <td class="AddListBoxMaps">
                                <p>Game type</p>
                                <%= Html.TextBox("Data." + questDataListString + "[" + objIndex + "].SessionCondition.GameType",
                                  objective.SessionCondition.GameType,
                                  new { id = "Data_" + questDataListString + "[" + objIndex + "]_SessionCondition_GameType" })%>
                              </td>
                              <td class="AddListBoxHeroes">
                                <p>Hero</p>
                                <%= Html.TextBox("Data." + questDataListString + "[" + objIndex + "].SessionCondition.PickedHero",
                                  objective.SessionCondition.PickedHero,
                                  new { id = "Data_" + questDataListString + "[" + objIndex + "]_SessionCondition_PickedHero" })%>
                              </td>
                              <td>
                                <p>Total amount</p>
                                <%= Html.TextBox("Data." + questDataListString + "[" + objIndex + "].SessionCondition.TotalValue",
                                  objective.SessionCondition.TotalValue,
                                  new { id = "Data_" + questDataListString + "[" + objIndex + "]_SessionCondition_TotalValue" })%>
                              </td>
                            </tr>
                            <tr>
                              <td>
                                <p>Type to collect</p>
                                <%= Html.DropDownList("Data." + questDataListString + "[" + objIndex + "].SessionCondition.CollectingType",
                                  Model.SetSelected(Model.DynamicQuestCollectingTypeEnum, objective.SessionCondition.CollectingType),
                                  new { id = "Data_" + questDataListString + "[" + objIndex + "]_SessionCondition_CollectingType" })%>
                              </td>
                              <td>
                                <p>Increment per battle</p>
                                <%= Html.TextBox("Data." + questDataListString + "[" + objIndex + "].SessionCondition.IncrementPerBattle",
                                  objective.SessionCondition.IncrementPerBattle,
                                  new { id = "Data_" + questDataListString + "[" + objIndex + "]_SessionCondition_IncrementPerBattle" })%>
                              </td>
                               <td>
                                 <p>Session result influence</p>
                                 <%= Html.DropDownList("Data." + questDataListString + "[" + objIndex + "].SessionCondition.SessionCheckType",
                                   Model.SetSelected(Model.SessionCheckType, objective.SessionCondition.SessionCheckType.ToString()),
                                   new { id = "Data_" + questDataListString + "[" + objIndex + "]_SessionCondition_SessionCheckType" })%>
                               </td>
                            </tr>
                            <tr>
                              <td>
                              <p>Player party size</p>
                              <%= Html.TextBox("Data." + questDataListString + "[" + objIndex + "].SessionCondition.PlayerPartySize",
                                  objective.SessionCondition.PlayerPartySize,
                                  new { id = "Data_" + questDataListString + "[" + objIndex + "]_SessionCondition_PlayerPartySize" })%>
                              <%= Html.ValidationMessage("Data." + questDataListString + "[" + objIndex + "].SessionCondition.PlayerPartySize")%>
                              </td>
                              
                              <td>
                              <p>Enemy party size</p>
                              <%= Html.TextBox("Data." + questDataListString + "[" + objIndex + "].SessionCondition.EnemyPartySize",
                                  objective.SessionCondition.EnemyPartySize,
                                  new { id = "Data_" + questDataListString + "[" + objIndex + "]_SessionCondition_EnemyPartySize" })%>
                              <%= Html.ValidationMessage("Data." + questDataListString + "[" + objIndex + "].SessionCondition.EnemyPartySize")%>
                              </td>
                              <td>
                              <p>Check only for guild games (0 - false, 1 - true)</p>
                              <%= Html.TextBox( "Data." + questDataListString + "[" + objIndex + "].SessionCondition.IsGuildGame",
                                  objective.SessionCondition.IsGuildGame,
                                  new { id = "Data_" + questDataListString + "[" + objIndex + "]_SessionCondition_IsGuildGame" })%>
                              <%= Html.ValidationMessage( "Data." + questDataListString + "[" + objIndex + "].SessionCondition.IsGuildGame" )%>
                              </td>
                            </tr>
                            <tr>
                                <td>
                                    <p>Player party size strong condition</p>
                                     <%= Html.TextBox("Data." + questDataListString + "[" + objIndex + "].SessionCondition.IsPlayerPartySizeStrongCond", 
                                        objective.SessionCondition.IsPlayerPartySizeStrongCond, 
                                        new { id = "Data_" + questDataListString + "[" + objIndex + "]_SessionCondition_IsPlayerPartySizeStrongCond" })%>
                                     <%= Html.ValidationMessage("Data." + questDataListString + "[" + objIndex + "].SessionCondition.IsPlayerPartySizeStrongCond")%>
                                </td>
                                <td>
                                    <p>Enemy party size strong condition: </p>
                                     <%= Html.TextBox("Data." + questDataListString + "[" + objIndex + "].SessionCondition.IsEnemyPartySizeStrongCond", 
                                        objective.SessionCondition.IsEnemyPartySizeStrongCond,
                                        new { id = "Data_" + questDataListString + "[" + objIndex + "]_SessionCondition_IsEnemyPartySizeStrongCond" })%>
                                     <%= Html.ValidationMessage("Data." + questDataListString + "[" + objIndex + "].SessionCondition.IsEnemyPartySizeStrongCond")%>
                                </td>
                                <td>
                                    <p>Strong conditions: 0 - false, 1 - true </p>
                                </td>
                            </tr>            
                            
                        <% } %>
                        <% if (Equals(objective.QuestCheckType.ToString(), "SessionInfo"))
                           { %>
                            <tr>
                              <td class="AddListBoxMaps">
                                <p>Game type</p>
                                <%= Html.TextBox("Data." + questDataListString + "[" + objIndex + "].SessionCondition.GameType",
                                  objective.SessionCondition.GameType,
                                  new { id = "Data_" + questDataListString + "[" + objIndex + "]_SessionCondition_GameType" })%>
                              </td>
                              <td class="AddListBoxHeroes">
                                <p>Hero</p>
                                <%= Html.TextBox("Data." + questDataListString + "[" + objIndex + "].SessionCondition.PickedHero",
                                  objective.SessionCondition.PickedHero,
                                  new { id = "Data_" + questDataListString + "[" + objIndex + "]_SessionCondition_PickedHero" })%>
                              </td>
                              <td>
                                <p>Total amount</p>
                                <%= Html.TextBox("Data." + questDataListString + "[" + objIndex + "].SessionCondition.TotalValue",
                                  objective.SessionCondition.TotalValue,
                                  new { id = "Data_" + questDataListString + "[" + objIndex + "]_SessionCondition_TotalValue" })%>
                              </td>
                              <td>
                                <p>Session result influence</p>
                                <%= Html.DropDownList("Data." + questDataListString + "[" + objIndex + "].SessionCondition.SessionCheckType",
                                  Model.SetSelected(Model.SessionCheckType, objective.SessionCondition.SessionCheckType.ToString()),
                                  new { id = "Data_" + questDataListString + "[" + objIndex + "]_SessionCondition_SessionCheckType" })%>
                                <%= Html.TextBox("Data." + questDataListString + "[" + objIndex + "].SessionCondition.CollectingType",
                                  objective.SessionCondition.CollectingType,
                                  new { id = "Data_" + questDataListString + "[" + objIndex + "]_SessionCondition_SessionCheckType", @class = "hidden" })%>
                              </td>
                            </tr>
                            <tr>
                              <td>
                              <h2>Player party size</h2>
                              <%= Html.TextBox("Data." + questDataListString + "[" + objIndex + "].SessionCondition.PlayerPartySize",
                                  objective.SessionCondition.PlayerPartySize,
                                  new { id = "Data_" + questDataListString + "[" + objIndex + "]_SessionCondition_PlayerPartySize" })%>
                              
                              </td>
                              <td>
                              <h2>Enemy party size</h2>
                              <%= Html.TextBox("Data." + questDataListString + "[" + objIndex + "].SessionCondition.EnemyPartySize",
                                  objective.SessionCondition.EnemyPartySize,
                                  new { id = "Data_" + questDataListString + "[" + objIndex + "]_SessionCondition_EnemyPartySize" })%>
                              <%= Html.ValidationMessage("Data." + questDataListString + "[" + objIndex + "].SessionCondition.EnemyPartySize")%>
                              </td>
                              <td>
                              <h2>Check only for guild games (0 - false, 1 - true)</h2>
                              <%= Html.TextBox( "Data." + questDataListString + "[" + objIndex + "].SessionCondition.IsGuildGame",
                                  objective.SessionCondition.IsGuildGame,
                                  new { id = "Data_" + questDataListString + "[" + objIndex + "]_SessionCondition_IsGuildGame" })%>
                              <%= Html.ValidationMessage( "Data." + questDataListString + "[" + objIndex + "].SessionCondition.IsGuildGame" )%>
                              </td>
                            </tr> 
                            <tr>
                                <td>
                                    <p>Player party size strong condition (0 - false, 1 - true)</p>
                                     <%= Html.TextBox("Data." + questDataListString + "[" + objIndex + "].SessionCondition.IsPlayerPartySizeStrongCond", 
                                        objective.SessionCondition.IsPlayerPartySizeStrongCond, 
                                        new { id = "Data_" + questDataListString + "[" + objIndex + "]_SessionCondition_IsPlayerPartySizeStrongCond" })%>
                                     <%= Html.ValidationMessage("Data." + questDataListString + "[" + objIndex + "].SessionCondition.IsPlayerPartySizeStrongCond")%>
                                    
                                </td>
                                <td>
                                    <h2>Enemy party size strong condition: </h2>
                                     <%= Html.TextBox("Data." + questDataListString + "[" + objIndex + "].SessionCondition.IsEnemyPartySizeStrongCond", 
                                        objective.SessionCondition.IsEnemyPartySizeStrongCond,
                                        new { id = "Data_" + questDataListString + "[" + objIndex + "]_SessionCondition_IsEnemyPartySizeStrongCond" })%>
                                    <%= Html.ValidationMessage("Data." + questDataListString + "[" + objIndex + "].SessionCondition.IsEnemyPartySizeStrongCond")%>
                                    
                                </td>
                                <td>
                                    <p>Strong conditions: 0 - false, 1 - true </p>
                                </td>
                            </tr>                           
                        <% } %>

                        <% if (Equals(objective.QuestCheckType.ToString(), "Instant"))
                           { %>
                            <tr>
                              <td>
                                <p>Resource type</p>
                                <%= Html.DropDownList("Data." + questDataListString + "[" + objIndex + "].InstantCondition.ResourceType",
                                  Model.SetSelected(Model.ResourcesEnum, objective.InstantCondition.ResourceType.ToString()),
                                  new { id = "Data_" + questDataListString + "[" + objIndex + "]_InstantCondition_ResourceType" })%>
                              </td>
                              <td>
                                <p>Total amount or String data if TalentsToPay/CustomCurrency</p>
                                <%= Html.TextBox("Data." + questDataListString + "[" + objIndex + "].InstantCondition.TotalValue",
                                  objective.InstantCondition.TotalValue,
                                  new { id = "Data_" + questDataListString + "[" + objIndex + "]_InstantCondition_TotalValue" })%>
                              </td>
                            </tr>
                        <% } %>
                        <% if (Equals(objective.QuestCheckType.ToString(), "ModelData"))
                          { %>
                            <tr>
                              <td>
                                <p>Condition type</p>
                                <%= Html.DropDownList("Data." + questDataListString + "[" + objIndex + "].ModelDataCondition.TypeToCollect",
                                  Model.SetSelected(Model.ModelDataConditionType, objective.ModelDataCondition.TypeToCollect.ToString()),
                                  new { id = "Data_" + questDataListString + "[" + objIndex + "]_ModelDataCondition_ResourceType" })%>
                              </td>
                              <td>
                                <p>Total amount</p>
                                <%= Html.TextBox("Data." + questDataListString + "[" + objIndex + "].ModelDataCondition.TotalValue",
                                  objective.ModelDataCondition.TotalValue,
                                  new { id = "Data_" + questDataListString + "[" + objIndex + "]_ModelDataCondition_TotalValue" })%>
                              </td>
                              <td>
                                <p>PersistentId or string data</p>
                                <%= Html.TextBox("Data." + questDataListString + "[" + objIndex + "].ModelDataCondition.PersistentId",
                                  objective.ModelDataCondition.PersistentId,
                                  new { id = "Data_" + questDataListString + "[" + objIndex + "]_ModelDataCondition_PersistentId" })%>
                              </td>
                            </tr>
                             
                        <% } %>
                      </table>
                    </td>
                  </tr>
                </table>
              </td>
            </tr>
            <% objIndex++;
          } %>
        </table>
      </div>
      <% } %>
      <% for (var i = 0; i < 2; i++)
         {
           List<DynamicQuestAward> awardsList;
           string awardsListString;
      %>
      <div>
        <% if (i == 0)
           {
             awardsList = Model.Data.Awards;
             awardsListString = "Awards";
        %>
        <h3>Awards</h3>
        <% if (Model.Editable && !Model.ExistingQuest)
           { %>
            <div class="add-Awards" id="AddAwards">
              <a href="javascript: void(0)">Add new award</a>
            </div>
        <% } %>
        <%
           }
           else
           {
             awardsList = Model.Data.AlternativeAwards;
             awardsListString = "AlternativeAwards";
        %>
        <h3>Alternative awards</h3>
        <% if (Model.Editable && !Model.ExistingQuest)
           { %>
            <div class="add-AlternativeAwards" id="AddAlternativeAwards">
              <a href="javascript: void(0)">Add new alternative award</a>
            </div>
        <% } %>
        <%
           }
        %>
        <table id="<%= awardsListString %>">
          <% var awIndex = 0;
             if (awardsList == null) continue;
             foreach (var award in awardsList)
             { %>
          <tr>
            <td>
              <table>
                <tr>
                  <th>Award type</th><th>Award condition</th>
                </tr>
                  <tr class="<%= awardsListString %>-container" id="<%= awardsListString %>Container<%= Html.Encode(awIndex) %>">
                    <td>
                      <%
                        if (Model.ExistingQuest || !Model.Editable)
                        { %>
                          <%= Html.DropDownList("Data." + awardsListString + "[" + awIndex + "].AwardType",
                                Model.SetSelected(Model.AwardTypes, award.AwardType.ToString()),
                                new {id = "Data_" + awardsListString + "[" + awIndex + "]_AwardType", disabled = Model.ExistingQuest && Model.Editable}) %>
                          <%= Html.Hidden("Data." + awardsListString + "[" + awIndex + "].AwardType",
                                award.AwardType.ToString(),
                                new {id = "Data_" + awardsListString + "[" + awIndex + "]_AwardType"}) %>
                      <% }
                        else
                        { %>
                      <%= Html.DropDownList("Data." + awardsListString + "[" + awIndex + "].AwardType",
                            Model.SetSelected(Model.AwardTypes, award.AwardType.ToString()),
                            new {id = "Data_" + awardsListString + "[" + awIndex + "]_AwardType"}) %>
                      <% } %>
                    </td>
                    <td>
                          <%= Html.DropDownList("Data." + awardsListString + "[" + awIndex + "].AwardConditionType",
                                Model.SetSelected(Model.AwardConditionTypes, award.AwardConditionType.ToString()),
                                new {id = "Data_" + awardsListString + "[" + awIndex + "]_AwardConditionType"}) %>
                          <%= Html.Hidden("Data." + awardsListString + "[" + awIndex + "].AwardConditionType",
                                award.AwardConditionType.ToString(),
                                new {id = "Data_" + awardsListString + "[" + awIndex + "]_AwardConditionType"}) %>
                    </td>
                    <% if (Model.Editable && !Model.ExistingQuest)
                       { %>
                      <td class="remove-<%= awardsListString %>"><a href="javascript: void(0)">Remove</a></td>
                    <% } %>
                  </tr>
                  <tr class="<%= awardsListString %>-input" >
                    <%
                        if ((new[] { "HeroExperience", "Talent", "RandomTalent", "Lamp", "RandomSkin", "RandomTalentFromPool", "AlreadyCompletedQuest", "CustomCurrency", "Lootbox" }.Contains(award.AwardType.ToString())))
                      {
                        var textDataName = "";
                        if (award.AwardType.ToString().Equals("CustomCurrency")) textDataName = "Currency Id";
                        if (award.AwardType.ToString().Equals("Lootbox")) textDataName = "Lootbox persistentId";
                        if (award.AwardType.ToString().Equals("HeroExperience")) textDataName = "Hero";
                        if (award.AwardType.ToString().Equals("Talent")) textDataName = "Talent";
                        if (award.AwardType.ToString().Equals("RandomTalent")) textDataName = "Quality (if you want to set pack for exclusive talents, use following format: exclusive:NativeTerrain)";
                        if (award.AwardType.ToString().Equals("Lamp")) textDataName = "Lamp settings in format lampType:goldBonus:transactions:duration, ex: 20:1000:5:86400";
                        if (award.AwardType.ToString().Equals("RandomSkin")) textDataName = "Available skins";
                        if (award.AwardType.ToString().Equals("RandomTalentFromPool")) textDataName = "Talents pools";
                        if (award.AwardType.ToString().Equals("AlreadyCompletedQuest")) textDataName = "Quests to remove";
                    %>
                    <td>
                      <p><%= textDataName %></p>
                      <%= Html.TextBox("Data." + awardsListString + "[" + awIndex + "].TextData", award.TextData, new {id = "Data_" + awardsListString + "[" + awIndex + "]_TextData"}) %>
                    </td>
                    <% } %>
                    <%
                      if (award.AwardType.ToString().Contains("RandomHero"))
                      { %>
                      <td class="AddListBoxHeroes">
                          <p>Available heroes</p>
                          <%= Html.TextBox("Data." + awardsListString + "[" + awIndex + "].TextData",
                                award.TextData,
                                new {id = "Data_" + awardsListString + "[" + awIndex + "]_TextData"}) %>
                      </td>
                    <% } %>
                    <%
                      if ((new[]
                      {
                        "HeroExperience", "Talent", "RandomTalent", "PremiumAcc", "Resource1", "Gold",
                        "Resource2", "Resource3", "Perl", "RedPerl", "Silver", "Experience", "CustomFlag", "Skin",
                        "Hero", "HeroStatsReset", "Construction", "Quest","RandomTalentFromPool","AlreadyCompletedQuest", "UpgradeHeroTalentsEvent", "Shard", "CustomCurrency", "Lootbox"
                      }.Contains(award.AwardType.ToString())))
                      {
                    %>
                    <td>
                      <%
                          if (new[] { "HeroExperience", "Talent", "RandomTalent", "Quest", "Skin", "CustomFlag", "RandomTalentFromPool", "AlreadyCompletedQuest", "UpgradeHeroTalentsEvent", "Shard", "CustomCurrency", "Lootbox" }.Contains(award.AwardType.ToString()))
                        {
                          var valueName = "";
                          if (award.AwardType.ToString().Equals("CustomCurrency")) valueName = "CustomCurrency";
                          if (award.AwardType.ToString().Equals("Shard")) valueName = "ShardsCount";
                          if (award.AwardType.ToString().Equals("UpgradeHeroTalentsEvent")) valueName = "HeroCount";
                          if (award.AwardType.ToString().Equals("Lootbox")) valueName = "Lootboxes count";
                          if (award.AwardType.ToString().Equals("HeroExperience")) valueName = "Experience";
                          if (award.AwardType.ToString().Equals("Talent")) valueName = "Count";
                          if (award.AwardType.ToString().Equals("RandomTalentFromPool")) valueName = "Count";
                          if (award.AwardType.ToString().Equals("RandomTalent")) valueName = "Count";
                          if (award.AwardType.ToString().Equals("Quest")) valueName = "Dynamic quest id";
                          if (award.AwardType.ToString().Equals("Skin")) valueName = "PersistentId";
                          if (award.AwardType.ToString().Equals("CustomFlag")) valueName = "PersistentId";
                          if (award.AwardType.ToString().Equals("AlreadyCompletedQuest")) valueName = "Dynamic quest id";
                      %>
                      <p><%= valueName %></p>
                      <% } %>
                      <% if (new[] {"Hero", "HeroStatsReset", "HeroExperience"}.Contains(award.AwardType.ToString()))
                         { %>
                      <%= Html.DropDownList("Data." + awardsListString + "[" + awIndex + "].Value",
                            Model.SetSelected(Model.HeroList, award.Value),
                            new {id = "Data_" + awardsListString + "[" + awIndex + "]_Value"}) %>
                      <% }
                         else
                         { %>
                            <%= Html.TextBox("Data." + awardsListString + "[" + awIndex + "].Value", award.Value, new {id = "Data_" + awardsListString + "[" + awIndex + "]_Value"}) %>
                      <% } %>
                        <% if (new [] {"Talent", "RandomTalent", "RandomTalentFromPool"}.Contains(award.AwardType.ToString()))
                           { %>
                            <p><%= "RefinePoints"%></p>
                            <% var currentPoints = award.AdditionalData2 != null && !award.AdditionalData2.Equals(string.Empty) ? award.AdditionalData2 : "0"; %>
                            <%= Html.TextBox("Data." + awardsListString + "[" + awIndex + "].AdditionalData2", currentPoints, new { id = "Data_" + awardsListString + "[" + awIndex + "]_AdditionalData2" })%>
                        <% } %>
                    </td>
                    <% } %>
                  </tr>
              </table>
            </td>
          </tr>
            <% awIndex++;
             } %>
        </table>
      </div>
  <% } %>
  </div>
    <br/>
    <div>
      <div id="ShowJson">
        <a href="javascript: void(0)">JSON:</a>
      </div>
      <div class="hidden" id="ResultJson">
        <%=Html.TextAreaFor(model => model.ResultJson, new { @readonly = true, cols = 120, rows = 15 })%>
      </div>
    </div>
    <br/>
    <div>
      <% if (Model.Editable && !Model.ExistingQuest) { %>
      <input type="submit" name="operation" value="Preview" />
      <input type="submit" name="operation" value="SentNew" />
      <% } %>
      <% if (Model.Editable && Model.ExistingQuest) { %>
      <input type="submit" name="operation" value="Preview" />
      <input type="submit" name="operation" value="SentEdit" />
      <% } %>
  </div>
  <% } %>

</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>