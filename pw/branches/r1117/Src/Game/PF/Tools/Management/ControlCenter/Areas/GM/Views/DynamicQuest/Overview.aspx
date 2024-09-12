<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<DynamicQuestRawInfoModel>" %>
<%@ Import Namespace="System.Globalization" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
  Overview
</asp:Content>

<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">
    <link href="/Content/jquery-ui-1.8.17.custom.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Scripts/jquery-ui-1.8.16.custom.min.js"></script>
    <script type="text/javascript" src="/Scripts/jquery.localizeDate.js"></script>
    <script type="text/javascript" src="/Scripts/jquery-ui-timepicker-addon.js"></script>
    <script type="text/javascript" src="/Scripts/jquery-ui-sliderAccess.js"></script>
    <script type="text/javascript" src="/Scripts/CommonScripts.js"></script>
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <script type="text/javascript">
      function OnReady() {
          localizeDate();
          $("#addItem").click(function () {
              window.SwitchVisibility($("#AddItemBox"));
          });
          window.SwitchVisibility($("#AddItemBox"));

          $("#startFilter, #endFilter").datetimepicker({
              dateFormat: "dd.mm.yy",
              separator: " ",
              timeFormat: "hh:mm:ss",
              ampm: false,
              showSecond: true
          });

          var locales = GetAllValues("locale");
          $(".AddListBoxLocale").each(function () {
              CommonScripts.AddListBox($(this), locales.valuesArray, locales.namesArray, false);
          });
          var types = GetAllValues("type");
          $(".AddListBoxType").each(function () {
              CommonScripts.AddListBox($(this), types.valuesArray, types.namesArray, false);
          });
          var packs = GetAllValues("pullId");
          $(".AddListBoxPack").each(function () {
              CommonScripts.AddListBox($(this), packs.valuesArray, packs.namesArray, false);
          });

          $("#filter :input").each(function() {
              $(this).change(function () {
                  ApplyFilter(GetFilterData());
              });
          });
      }

      function GetAllValues(label) {
          var resultObject = {};
          resultObject.namesArray = ["All"];
          resultObject.valuesArray = ["All"];
          $("." + label).each(function () {
              var tempValue = $(this).text();
              tempValue.split(", ").forEach(function (element) {
                  if ($.inArray(element, resultObject.valuesArray) === -1 && element !== "") {
                      resultObject.namesArray.push(element);
                      resultObject.valuesArray.push(element);
                  }
              });
              
          });
          return resultObject;
      }

      function SwitchVisibility(elements) {
          if (elements.hasClass("hidden")) {
              elements.removeClass("hidden").addClass("visible");
          } else {
              if (elements.hasClass("visible")) {
                  elements.removeClass("visible");
              }
              elements.addClass("hidden");
          }
      }

      function ForceVisibility(elements, visibility) {
          var oldVisibility = "visible";
          var newVisibility = "hidden";
          if (visibility) {
              oldVisibility = "hidden";
              newVisibility = "visible";
          }

          if (elements.hasClass(oldVisibility)) {
              elements.removeClass(oldVisibility);
          }
          if (elements.hasClass(newVisibility)) {
              elements.removeClass(newVisibility);
          }
          elements.addClass(newVisibility);
      }

      function ApplyFilter(data) {
          console.log("data: " + JSON.stringify(data));
          var dynamicQuests = $("#dynamicQuests>tbody>tr").slice(1);
          dynamicQuests.each(function () {
              var quest = $(this);
              var localeCheck = data.locale === "" || data.locale === " " || data.locale === "All" || $(this).find("td.locale").text().indexOf(data.locale) > -1;

              var startDate = parseStringToDate($(this).find("td.startDate").text());
              var endDate = parseStringToDate($(this).find("td.endDate").text());
              var startCheck = data.start === 0 || startDate >= data.start || endDate >= data.start;
              var endCheck = data.end === 0 || startDate <= data.end || endDate <= data.end;

              var typeCheck = data.questType === "" || data.questType === " " || data.questType === "All" || $(this).find("td.type").text().indexOf(data.questType) > -1;

              var pullIdCheck = data.pack === "" || data.pack === " " || data.pack === "All" || $(this).find("td.pullId").val().indexOf(data.pack) > -1;

              var rawCheck = data.raw === "" || $(this).find("td.raw").text().indexOf(data.raw) > -1;

              ForceVisibility(quest, localeCheck && startCheck && endCheck && typeCheck && pullIdCheck && rawCheck);
          });
      }

      function parseStringToDate(string) {
          var resultValue = 0;
          if (string !== "" && string !== " ") {
              resultValue = stringToUtcTicks(string);
          }
          return resultValue;
      }

      function GetFilterData() {
          var data = {}
          data.locale = $("#localeFilter").val();
          data.start = parseStringToDate($("#startFilter").val());
          data.end = parseStringToDate($("#endFilter").val());
          data.questType = $("#typeFilter").val();
          data.pack = $("#packFilter").val();
          data.raw = $("#rawFilter").val();
          return data;
      }

      $(document).ready(OnReady);
      document.onkeypress = function(e) {
          var focusedId = ($("*:focus").attr("id"));
          if (focusedId === "rawFilter") {
              var code = e.keyCode || e.which;
              if (code === 13) {
                  e.preventDefault();
                  ApplyFilter(GetFilterData());
                  return false;
              }
          }
          return true;
      };
  </script>
  <h2>Overview</h2>
  <% using (Html.BeginForm(null, null, FormMethod.Post, new { name = "QuestsTableForm", id = "QuestsTableForm" }))
  { %>

    <div class="pagemenu">
      <%= Html.ActionLink("Quest pulls", "QuestPulls")%><br/>
      <br/>
      <%= Html.ActionLink("Add quest (empty)", "DynamicQuestInfo", new { json = "", operation = "Add" })%><br/>
      <div id="addItem">
        <a href="javascript: void(0)">Add quest (from json)</a>
      </div>
      <div id="AddItemBox">
        <%= Html.TextAreaFor(model => model.NewQuestJson) %><br/>
        <input type="submit" value="Add"/>
      </div>
      <br/>
      <%= Html.ActionLink("Auid lists", "Index", "AuidList")%><br/>
    </div>

    <fieldset>
        <table id="filter">
            <tr>
                <td>
                    <p>Locale</p>
                </td>
                <td>
                    <div class="AddListBoxLocale">
                        <input type="text" id="localeFilter"/>
                    </div>
                </td>
            </tr>
            <tr>
                <td>
                    <p>From</p>
                </td>
                <td>
                    <input type="text" id="startFilter"/>
                </td>
            </tr>
            <tr>
                <td>
                    <p>To</p>
                </td>
                <td>
                    <input type="text" id="endFilter"/>
                </td>
            </tr>
            <tr>
                <td>
                    <p>Objective type</p>
                </td>
                <td>
                    <div class="AddListBoxType">
                        <input type="text" id="typeFilter"/>
                    </div>
                </td>
            </tr>
            <tr>
                <td>
                    
                        <p>Pack</p>
                    
                </td>
                <td>
                    <div class="AddListBoxPack">
                        <input type="text" id="packFilter"/>
                    </div>
                </td>
            </tr>
            <tr>
                <td>
                    <p>Raw json</p>
                </td>
                <td>
                    <input type="text" id="rawFilter"/>
                </td>
            </tr>
        </table>
    </fieldset>

    <div>
      <h2>Dynamic quests</h2>
      <table id="dynamicQuests">
        <tr>
          <th>Quest index</th>
          <th>Quest pull index</th>
          <th>Quest name</th>
          <th class="timeZoneLabel">Start date, utc+0</th>
          <th class="timeZoneLabel">End date, utc+0</th>
          <th>Info</th>
        </tr>
      <%
        int objIndex = 0;
        foreach (var jsonQuestPair in Model.ParcedQuestsList.OrderBy( q => q.Key.Index ))
        { %>
          <tr class="objective-container visible" id="ObjectiveContainer<%= Html.Encode(objIndex) %>">
            <td><%= Html.Encode(jsonQuestPair.Key.Index)%></td>
            <td class="pullId"><%= Html.Encode( jsonQuestPair.Value.PullId == 0 ? " " : jsonQuestPair.Value.PullId.ToString() )%></td>
            <td><%= Html.Label(jsonQuestPair.Value.Data.QuestName)%></td>
            <td class="startDate utcdateText"><%= Html.Encode(jsonQuestPair.Value.QuestStartTimeView)%></td>
            <td class="endDate utcdateText"><%= Html.Encode(jsonQuestPair.Value.QuestEndTimeView)%></td>
            <td><%= Html.ActionLink("Info", "DynamicQuestInfo", new
                    {
                      index = jsonQuestPair.Key.Index,
                      operation = "Info"
                    })%></td>
            <td><%= Html.ActionLink("Edit", "DynamicQuestInfo", new
                    {
                      index = jsonQuestPair.Key.Index,
                      operation = "Edit"
                    })%></td>
            <td><%= Html.ActionLink("Remove", "RemoveDynamicQuest", new
                    {
                      questName = jsonQuestPair.Value.Data.QuestName,
                      questEndTime = jsonQuestPair.Value.Data.QuestEndTime,
                      questStartTime = jsonQuestPair.Value.Data.QuestStartTime,
                      locale = jsonQuestPair.Key.Locale,
                      questId = jsonQuestPair.Key.Index,
                      pullId = jsonQuestPair.Key.PullId
                    })%></td>
              <td class="locale hidden"><%=jsonQuestPair.Key.Locale%></td>
              <td class="type hidden"><%=jsonQuestPair.Value.GetObjectiveTypes()%></td>
              <td class="raw hidden"><%=jsonQuestPair.Key.Json%></td>
          </tr>
          <% objIndex++;
        } %>
      </table>
      <% if (Model.WrongJsonsList.Count > 0)
         { %>
           <p style="color:red;">Wrong parsed: <%= Html.Label(Model.WrongJsonsList.Count.ToString(CultureInfo.InvariantCulture))%>/<%= Html.Label((Model.WrongJsonsList.Count + Model.JsonQuestData.Count).ToString(CultureInfo.InvariantCulture))%>
           </p>
        <table id="Table1">
        <tr>
          <th>Quest index</th>
          <th>Info</th>
        </tr>
          <%
            foreach (var currentJson in Model.WrongJsonsList)
            { %>
              <tr class="objective-container" id="Tr1">
                <td><%= Html.Encode(currentJson.Index)%></td>
                <td><%= Html.Label(currentJson.Json)%></td>
                <td><%= Html.ActionLink("Remove", "RemoveWrongQuest", new
                        {
                          locale = currentJson.Locale,
                          questId = currentJson.Index
                        })%></td>
              </tr>
              <% objIndex++;
            } %>
          </table>
         <% } %>
    </div>
  <% } %>
</asp:Content>
