<%@ Page Title="Roll Event" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<RollEventModel>" %>
<%@ Import Namespace="ControlCenter.Areas.EventTool.Models" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
Roll Events
</asp:Content>

<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">
  
    <link rel="stylesheet" href="/Content/pager.css" />
    <link href="../../../../Content/jquery-ui-1.8.17.custom.css" rel="stylesheet" type="text/css" />
    <style type="text/css">
    /* css for timepicker */
        .ui-timepicker-div .ui-widget-header { margin-bottom: 8px; }
        .ui-timepicker-div dl { text-align: left; }
        .ui-timepicker-div dl dt { height: 25px; margin-bottom: -25px; }
        .ui-timepicker-div dl dd { margin: 0 10px 10px 65px; }
        .ui-timepicker-div td { font-size: 90%; }
        .ui-tpicker-grid-label { background: none; border: none; margin: 0; padding: 0; }
    </style>
  
    <style type="text/css">
        .filter { border: 0; }
        .filter td { border: 0; }
        .saveButton { font-size: 150%; font-weight: bold; }
    </style>
  
    <script type="text/javascript" src="../../../../Scripts/jquery-ui-1.8.16.custom.min.js"></script>
    <script type="text/javascript" src="../../../../Scripts/jquery-ui-timepicker-addon.js"></script>
    <script type="text/javascript" src="../../../../Scripts/jquery-ui-sliderAccess.js"></script>

    <script type="text/javascript">
        $(document).ready(function () {
            $('#StartTime').datetimepicker({ dateFormat: 'dd.mm.yy', timeFormat: 'hh:mm:ss', showSecond: true });
            $('#EndTime').datetimepicker({ dateFormat: 'dd.mm.yy', timeFormat: 'hh:mm:ss', showSecond: true });
        });
    </script>
</asp:Content>

<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">


<div id="pagemenu" style="width: 30%; float: right; margin-left: 15px">
    
  <div class = "menublock">
      
    <% if (!Model.New) { %>
      <p><%= Html.ActionLink("Delete", "Delete", new { id = Model.EventId }, new { @class = "link-delete" }) %></p>
    <% } %>
    <p><%= Html.ActionLink("Back to list", "Index") %></p>

  </div>

</div> 

<div id="pagecontent" style="width: 70%">

  <h1><% if (Model.EventId == 0) { %>Create new event<% } else { %>Edit event<% } %></h1>

  <fieldset>

    <legend><%= Html.LabelFor(m => m.EventId) %>: <%= Model.New ? "New" : Model.EventId.ToString() %></legend>
    <%= Html.ValidationSummary(true) %>

    <% using (Html.BeginForm()) { %>

    <%= Html.HiddenFor(m => m.EventId) %>

    <%--Description--%>
    <div class="editor-label"><strong><%= Html.LabelFor(m => m.Description) %>*:</strong></div>
    <div class="editor-field">
      <%= Html.EditorFor(m => m.Description) %>
      <%= Html.ValidationMessageFor(m => m.Description) %>
    </div>

    <%--Enabled--%>
    <div class="editor-label"><strong><%= Html.LabelFor(model => model.Enabled) %>*:</strong></div>
    <div class="editor-field">
      <%= Html.CheckBoxFor(model => model.Enabled) %>
    </div>
      
      <%--GUID--%>
      <div class="editor-label"><strong><%= Html.LabelFor(model => model.GUID) %>*:</strong></div>
      <div class="editor-field">
          <%= Html.EditorFor(model => model.GUID)%>
          <%= Html.ValidationMessageFor(m => m.GUID)%>
      </div>

    <%-- Locale --%>
    <div class="editor-label"><strong><%= Html.LabelFor(model => model.Locale) %>*:</strong></div>
    <div class="editor-field">
      <%= Html.DropDownListFor(model => model.Locale, Model.AvailableLocales) %>
    </div>

    <hr/>

    <%--Title--%>
    <div class="editor-label"><strong><%= Html.LabelFor(model => model.Title)%>*:</strong></div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.Title)%>
      <%= Html.ValidationMessageFor(model => model.Title)%>
    </div>

    <%--Text--%>
    <div class="editor-label"><%= Html.LabelFor(model => model.Text)%>:</div>
    <div class="editor-field">
      <%= Html.TextAreaFor(model => model.Text)%>
      <%= Html.ValidationMessageFor(model => model.Text)%>
    </div>

    <%--Image--%>
    <div class="editor-label"><%= Html.LabelFor(model => model.Image)%> <em>(exactly 924x350px)</em>:</div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.Image)%>
      <%= Html.ValidationMessageFor(model => model.Image)%>
    </div>

    <%--StartTime--%>
    <div class="editor-label"><%= Html.LabelFor(m => m.StartTime) %> UTC:</div>
    <div class="editor-field">
      <%= Html.EditorFor(m => m.StartTime) %>
      <%= Html.ValidationMessageFor(m => m.StartTime) %>
    </div>

    <%--EndTime--%>
    <div class="editor-label"><%= Html.LabelFor(m => m.EndTime) %> UTC:</div>
    <div class="editor-field">
      <%= Html.EditorFor(m => m.EndTime) %>
      <%= Html.ValidationMessageFor(m => m.EndTime) %>
    </div>

    <%--CompletionTalentId--%>
    <div class="editor-label"><%= Html.LabelFor(model => model.CompletionTalentId)%>:</div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.CompletionTalentId)%>
      <%= Html.ValidationMessageFor(model => model.CompletionTalentId)%>
    </div>

    <%--Completion Talent Ratio--%>
    <div class="editor-label"><%= Html.LabelFor(m => m.CompletionTalentRatio)%>:</div>
    <div class="editor-field">
      <%= Html.TextAreaFor(m => m.CompletionTalentRatio)%>
      <%= Html.ValidationMessageFor(m => m.CompletionTalentRatio)%>
    </div>

    <%--CurrencyIds--%>
    <div class="editor-label"><%= Html.LabelFor(model => model.CurrencyIds)%> <em>(separate with ',' if many: e.g. 'RUB, EUR, USD')</em></div>
    <div class="editor-field">
        <%= Html.TextBoxFor(model => model.CurrencyIds)%>
        <%= Html.ValidationMessageFor(model => model.CurrencyIds)%>
    </div>

    <h2><%= Html.LabelFor(m => m.Rolls) %></h2>
    <button name="command" type="submit" value="AddRoll">Append new Rolling Rule</button>

    <%--Rolls--%>
    <% if (Model.Rolls.Count != 0) { %>
      <div>
      <% for (int i = 0; i < Model.Rolls.Count; i++) { %>
        <fieldset style="border-color: #000088; border-style: solid; border-width:1.5px;">
          <legend>Roll rule #<%= i+1 %> Title: 
              <%= Html.TextBoxFor(m => m.Rolls[i].Title) %>
              <%= Html.ValidationMessageFor(m => m.Rolls[i].Title) %>
              <button name="command" type="submit" value="RemoveRoll_<%= i %>">Remove roll rule</button>
          </legend>
          <details open="open"> <summary>Expand</summary>

            <%--RuleType--%>
            <div class="editor-label"><strong><%= Html.LabelFor(m => m.Rolls[i].RuleType) %>*:</strong></div>
            <div class="editor-field">
              <%= Html.DropDownListFor(m => m.Rolls[i].RuleType, Model.Rolls[i].RuleType.ToSelectList()) %>
              <%= Html.ValidationMessageFor(m => m.Rolls[i].RuleType) %>
            </div>

            <%--Description--%>
            <div class="editor-label"><%= Html.LabelFor(m => m.Rolls[i].Description) %> <em>(unused at the moment)</em>:</div>
            <div class="editor-field">
                <%= Html.TextBoxFor(m => m.Rolls[i].Description) %>
                <%= Html.ValidationMessageFor(m => m.Rolls[i].Description) %>
            </div>

            <%--Text--%>
            <div class="editor-label"><%= Html.LabelFor(model => model.Rolls[i].Text) %> <em>(unused at the moment)</em>:</div>
            <div class="editor-field">
                <%= Html.TextBoxFor(model => model.Rolls[i].Text) %>
                <%= Html.ValidationMessageFor(model => model.Rolls[i].Text) %>
            </div>

            <%--ResourcesTableSmallModel--%>
            <fieldset style="border-color: #008800; border-style: solid; border-width:1.5px;">
              <legend><%= Html.LabelFor(model => model.Rolls[i].Price) %>*</legend>
              <%= Html.EditorFor(m => m.Rolls[i].Price) %>
            </fieldset>

            <%--Rewards--%>
            <hr/>
            <h3><%= Html.LabelFor(m => m.Rolls[i].Rewards) %></h3>
            <button name="command" type="submit" value="AddReward_<%= i %>">Add Reward</button>
            <% for (int q = 0; q < Model.Rolls[i].Rewards.Count; q++) { %>
              <fieldset style="border-color: #BB4400; border-style: solid; border-width:1.5px;">
                <legend>
                  Reward #<%= q+1 %>
                  <button name="command" type="submit" value="RemoveReward_<%= i %>_<%= q %>">Remove reward</button>
                </legend>
                <details open="open"> <summary>Expand</summary>
                  <%= Html.EditorFor(m => m.Rolls[i].Rewards[q]) %>
                </details>
              </fieldset>
            <% } %>

            <%--ReforgeSources--%>
            <hr/>
            <h3><%= Html.LabelFor(m => m.Rolls[i].ReforgeSource) %></h3>
            <button name="command" type="submit" value="AddReforgeSource_<%= i %>">Add ReforgeSource</button>
            <% for (int q = 0; q < Model.Rolls[i].ReforgeSource.Count; q++) { %>
              <fieldset style="border-color: #8800BB; border-style: solid; border-width:1.5px;">
                <legend>
                  Reforge Source #<%= q+1 %>
                  <button name="command" type="submit" value="RemoveReforgeSource_<%= i %>_<%= q %>">Remove reforge source</button>
                </legend>
                <details open="open"> <summary>Expand</summary>
                  <%= Html.EditorFor(m => m.Rolls[i].ReforgeSource[q]) %>
                </details>
              </fieldset>
            <% } %>
          </details>
        </fieldset>
      <% } %>
      </div>
    <% } %>

    <button class="saveButton" type="submit" name="command" value=""><%= Model.New ? "Save new Roll Event" : "Save Roll Event #" + Model.EventId %></button>
      <% if (!Model.New) { %>
        <button type="submit" name="command" value="Clone">Clone event</button>
      <% } %>
    <% } %>

  </fieldset>

</div>

</asp:Content>

