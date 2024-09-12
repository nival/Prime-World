<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<DynamicQuestPullModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	EditQuestPull
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  
  <link rel="stylesheet" href="/Content/pager.css" />
  <link href="../../Content/jquery-ui-1.8.17.custom.css" rel="stylesheet" type="text/css" />
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
    .filter { border: 0px; }
    .filter td { border: 0px; }
    
    select
    {
        width: 200px;
        border: 1px solid #CCC;
    }
    
    th.results {
       width: 100px
    }
  </style>
  
  <script type="text/javascript" src="../../Scripts/jquery-ui-1.8.16.custom.min.js"></script>
  <script type="text/javascript" src="../../Scripts/jquery.localizeDate.js"></script>
  <script type="text/javascript" src="../../Scripts/jquery-ui-timepicker-addon.js"></script>
  <script type="text/javascript" src="../../Scripts/jquery-ui-sliderAccess.js"></script>

  <script type="text/javascript">
    $(document).ready(function () {
      localizeDate();
      $('#RotationStartTime').datetimepicker({ dateFormat: 'dd.mm.yy', timeFormat: 'hh:mm:ss', showSecond: true });
      $('#RotationEndTime').datetimepicker({ dateFormat: 'dd.mm.yy', timeFormat: 'hh:mm:ss', showSecond: true });

    });
  </script>
  <% var quests = Model.GetQuests(); %>
    <h2>EditQuestPull</h2>
    <% using ( Html.BeginForm() )
       { %>
    <div><%=Html.ActionLink("Back to list", "QuestPulls", "DynamicQuest")%><br/>
      <%=Html.ActionLink("Add quests to pull", "AddQuestsToPull", new { quests, Model.Locale, Model.PullId})%><br/>
      <%=Html.ActionLink( "Remove quests from pull", "RemoveQuestsFromPull", new { quests, Model.PullId } )%>
    </div>
    <div class="editor-label">
      <%= Html.HiddenFor(model => model.PullId) %>
      <%= Html.HiddenFor(model => model.Quests) %>
      <div class="editor-label">
        <%= Html.LabelFor( m => m.Quests )%>
      </div>
      <div class="editor-label">
        <%= Html.Encode( Model.GetQuests() )%>
      </div>
        <%-- ReSharper disable once Html.IdNotResolved --%>
        <label for="RotationStartTime" class="timeZoneLabel">Rotation start time, UTC+0</label>
      </div>
      <div class="editor-field">
        <%= Html.TextBoxFor( m => m.RotationStartTime, new Dictionary<string, object> { { "class", "utcdateVal" }, { "Value", Model.RotationStartTime.ToString( "dd.MM.yyyy HH:mm:ss" ) } } )%>
      </div>
      <div class="editor-label">
        <%-- ReSharper disable once Html.IdNotResolved --%>
        <label for="RotationEndTime" class="timeZoneLabel">Rotation end time, UTC+0</label>
      </div>
      <div class="editor-field">
        <%= Html.TextBoxFor( m => m.RotationEndTime, new Dictionary<string, object> { { "class", "utcdateVal" }, { "Value", Model.RotationEndTime.ToString( "dd.MM.yyyy HH:mm:ss" ) } } )%>
      </div>
      <div class="editor-label">
        <%= Html.LabelFor(model => model.Locale) %>
      </div>
      <div class="editor-field">
        <%= Html.DropDownListFor(model => model.Locale, Model.SvcLocales)%>
        <%= Html.ValidationMessageFor( model => model.Locale )%>
      </div>
      <div class="editor-label">
        <%= Html.LabelFor( model => model.IsWorking )%>
      </div>
      <div class="editor-field">
        <%= Html.CheckBoxFor( model => model.IsWorking )%>
        <%= Html.ValidationMessageFor( model => model.IsWorking )%>
      </div>
      <div class="editor-label">
        <%= Html.LabelFor(model => model.HasRotation) %>
      </div>
      <div class="editor-field">
        <%= Html.CheckBoxFor( model => model.HasRotation )%>
        <%= Html.ValidationMessageFor( model => model.HasRotation )%>
      </div>
      <p>
      <input type="submit" value="Save" />
    </p>
    <% } %>
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>
