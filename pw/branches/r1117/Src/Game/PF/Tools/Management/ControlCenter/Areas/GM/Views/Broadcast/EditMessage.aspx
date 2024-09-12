<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<BroadcastModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
  Edit broadcast
</asp:Content>

<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">
  <link href="/Content/jquery-ui-1.8.17.custom.css" rel="stylesheet" type="text/css" />
  <style type="text/css">
    /* css for timepicker */
    .ui-timepicker-div .ui-widget-header { margin-bottom: 8px; }
    .ui-timepicker-div dl { text-align: left; }
    .ui-timepicker-div dl dt { height: 25px; margin-bottom: -25px; }
    .ui-timepicker-div dl dd { margin: 0 10px 10px 65px; }
    .ui-timepicker-div td { font-size: 90%; }
    .ui-tpicker-grid-label { background: none; border: none; margin: 0; padding: 0; }
  </style>
  <script type="text/javascript" src="/Scripts/jquery-ui-1.8.16.custom.min.js"></script>
  <script type="text/javascript" src="/Scripts/jquery-ui-timepicker-addon.js"></script>
  <script type="text/javascript" src="/Scripts/jquery-ui-sliderAccess.js"></script>
  <script type="text/javascript" src="/Scripts/jquery.localizeDate.js"></script>
  <script type="text/javascript">
    $(document).ready(function() {
      localizeDate();
      $('#TimeStart').datetimepicker({ dateFormat: 'dd.mm.yy', timeFormat: 'hh:mm:ss', showSecond: true });
      $('#TimeFinish').datetimepicker({ dateFormat: 'dd.mm.yy', timeFormat: 'hh:mm:ss', showSecond: true });
    });
   </script>
</asp:Content>


<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <h2>Edit broadcast</h2>

  <% using (Html.BeginForm("EditMessage", "Broadcast")) { %>
    <%= Html.ValidationSummary(true) %>

    <%= Html.HiddenFor(m => m.TimeZone) %>

    <div class="editor-label">
     <%= Html.LabelFor(model => model.Title) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.Title) %>
      <%= Html.ValidationMessageFor(model => model.Title) %>
    </div>
    
    <fieldset>
      <legend>Enter text for each locale (leave field blank to prevent broadcasting on this locale)</legend>
      <% for (int i = 0; i < Model.Messages.Count; i++) { %>
        <div class="editor-label">
          <%= Html.HiddenFor(m => m.Messages[i].Locale)%>
          <%= Html.Encode(Model.Messages[i].Locale + " text") %>
        </div>
        <div class="editor-field">
          <%= Html.TextAreaFor(m => m.Messages[i].Text)%>
        </div>
      <% } %>
    </fieldset>
    
    <div class="editor-label">
        <label class="timeZoneLabel">TimeStart, utc+0</label>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor( model => model.TimeStart, new Dictionary<string, object> { { "class", "utcdateVal" }, { "Value", Model.TimeStart.ToString( "dd'.'MM'.'yyyy HH:mm:ss" ) } } )%>
      <%= Html.ValidationMessageFor( model => model.TimeStart ) %>
    </div>
    
    <div class="editor-label">
      <label class="timeZoneLabel">TimeFinish, utc+0</label>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor( model => model.TimeFinish, new Dictionary<string, object> { { "class", "utcdateVal" }, { "Value", Model.TimeFinish.ToString( "dd'.'MM'.'yyyy HH:mm:ss" ) } } )%>
      <%= Html.ValidationMessageFor(model => model.TimeFinish) %>
    </div>
    
    <div class="editor-label">
      <%= Html.LabelFor(model => model.Interval) %>, sec
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.Interval) %>
      <%= Html.ValidationMessageFor(model => model.Interval) %>
    </div>
    
    <div class="editor-label">
      <%= Html.LabelFor(model => model.EnabledNow) %>
    </div>
    <div class="editor-field">
      <%= Html.CheckBoxFor(model => model.EnabledNow) %>
      <%= Html.ValidationMessageFor(model => model.EnabledNow) %>
    </div>
    
    <div style="margin-top: 10px">
      <input type="submit" value="Save" id="editMessage" />
    </div>
  <% } %>

  <div style="margin-top: 20px">
    <%= Html.ActionLink("Back to list", "GetBroadcastList") %>
  </div>

</asp:Content>