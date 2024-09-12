<%@ Page Title="Quest Event" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<QuestEventModel>" %>
<%@ Import namespace="ControlCenter.Areas.EventTool.Models" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
Quest Events
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
  <h1><% if (Model.EventId == 0) { %>Create new quest event<% } else { %>Edit quest event<% } %></h1>
  <fieldset>
    <legend><%= Html.LabelFor(m => m.EventId) %>: <%= Model.New ? "New" : Model.EventId.ToString() %></legend>
    <%= Html.ValidationSummary(true) %>
    <% using (Html.BeginForm()) { %>

      <%= Html.HiddenFor(m => m.EventId) %>
      <button name="command" type="submit" value="pass">Reload model (debug)</button>

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

      <%--StartTime--%>
      <div class="editor-label"><strong><%= Html.LabelFor(m => m.StartTime) %> UTC*:</strong></div>
      <div class="editor-field">
        <%= Html.EditorFor(m => m.StartTime) %>
        <%= Html.ValidationMessageFor(m => m.StartTime) %>
      </div>

      <%--EndTime--%>
      <div class="editor-label"><strong><%= Html.LabelFor(m => m.EndTime) %> UTC*:</strong></div>
      <div class="editor-field">
        <%= Html.EditorFor(m => m.EndTime) %>
        <%= Html.ValidationMessageFor(m => m.EndTime) %>
      </div>

      <hr/>

      <%--Title--%>
      <div class="editor-label"><%= Html.LabelFor(model => model.Title)%>:</div>
      <div class="editor-field">
        <%= Html.TextBoxFor(model => model.Title) %>
        <%= Html.ValidationMessageFor(model => model.Title) %>
      </div>

      <%--Text--%>
      <div class="editor-label"><%= Html.LabelFor(model => model.Text)%>:</div>
      <div class="editor-field">
        <%= Html.TextAreaFor(model => model.Text) %>
        <%= Html.ValidationMessageFor(model => model.Text) %>
      </div>

      <%--CurrencyIds--%>
      <div class="editor-label"><%= Html.LabelFor(model => model.CurrencyIds)%> <em>(separate with ',' if many: e.g. 'RUB, EUR, USD')</em></div>
      <div class="editor-field">
        <%= Html.TextBoxFor(m => m.CurrencyIds) %>
        <%= Html.ValidationMessageFor(m => m.CurrencyIds) %>
      </div>

      <%--Completion Talent Id--%>
      <div class="editor-label"><%= Html.LabelFor(m => m.CompletionTalentId)%>:</div>
      <div class="editor-field">
        <%= Html.TextAreaFor(m => m.CompletionTalentId)%>
        <%= Html.ValidationMessageFor(m => m.CompletionTalentId)%>
      </div>

      <%--Completion Talent Ratio--%>
      <div class="editor-label"><%= Html.LabelFor(m => m.CompletionTalentRatio)%>:</div>
      <div class="editor-field">
        <%= Html.TextAreaFor(m => m.CompletionTalentRatio)%>
        <%= Html.ValidationMessageFor(m => m.CompletionTalentRatio)%>
      </div>

      <div class="editor-label">
        <strong><%= Html.LabelFor(m => m.Stages)%>*:</strong>
        <button name="command" type="submit" value="stage_add:0" style="color: darkgreen">ADD</button>
      </div>

      <%--Stages--%>
      <% if (Model.Stages.Count != 0) { %>
        <div>
        <% for (int i = 0; i < Model.Stages.Count; i++) { %>
          <fieldset style="border: solid darkred 2px;">
            <legend>
              <span>Stage #<%=i+1 %></span>
              <button name="command" type="submit" value="stage_up:<%=i %>"<%= (i == 0) ? " disabled=\"disabled\"" : "" %>>&uarr;</button>
              <button name="command" type="submit" value="stage_down:<%=i %>"<%= (i == Model.Stages.Count - 1) ? " disabled=\"disabled\"" : "" %>>&darr;</button>
              <button name="command" type="submit" value="stage_clone:<%=i %>" style="color: darkgreen">COPY</button>
              <button name="command" type="submit" value="stage_remove:<%=i %>" style="color: darkred">DEL</button>
            </legend>
            <details open="open">
              <summary>Expand</summary>
              <%= Html.EditorFor(m => m.Stages[i]) %>
            </details>
          </fieldset>
        <% } %>
        </div>
      <% } %>

      <button class="saveButton" type="submit" name="command" value=""><%= Model.New ? "Save new Quest Event" : "Save Quest Event #" + Model.EventId %></button>
      <% if (!Model.New) { %>
        <button type="submit" name="command" value="clone">Clone event</button>
      <% } %>

    <% } %>
  </fieldset>
</div>

</asp:Content>

