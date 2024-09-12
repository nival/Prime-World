<%@ Page Title="Donate Event" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<DonateEventModel>" %>
<%@ Import Namespace="ControlCenter.Areas.EventTool.Models" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
Donate Event
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
      <p><%= Html.ActionLink("Delete", "Delete", new { id = Model.Id }, new { @class = "link-delete" }) %></p>
    <% } %>
    <p><%= Html.ActionLink("Back to list", "Index") %></p>

  </div>

</div>

<div id="pagecontent" style="width: 70%">
  
  <h1>Donate event</h1>
  
  <h1><% if (Model.Id == 0) { %>Create new event<% } else { %>Edit event<% } %></h1>

  <fieldset>

    <legend><%= Html.LabelFor(m => m.Id) %>: <%= Model.New ? "New" : Model.Id.ToString() %></legend>
    <%= Html.ValidationSummary(true) %>

  <% using (Html.BeginForm()) { %>

    <%= Html.ValidationSummary(true) %>

    <%= Html.HiddenFor(m => m.Id) %>
    <%= Html.HiddenFor(m => m.Enabled) %>
   
    <div class="editor-label">
      <%= Html.LabelFor(m => m.Description) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(m => m.Description) %>
      <%= Html.ValidationMessageFor(m => m.Description) %>
    </div>

    <div style="margin-top: 10px">
      <div class="timeZoneLabel">Start time, utc+0</div>
      <div class="editor-field"><%= Html.TextBoxFor(m => m.StartTime, new Dictionary<string, object> { { "class", "utcdateVal" }, { "Value", Model.StartTime.ToString("dd'.'MM'.'yyyy HH:mm:ss")} }) %></div>
    </div>
  
    <div style="margin-top: 10px">
      <div class="timeZoneLabel">End time, utc+0</div>
      <div class="editor-field"><%= Html.TextBoxFor(m => m.EndTime, new Dictionary<string, object> { { "class", "utcdateVal" }, { "Value", Model.EndTime.ToString("dd'.'MM'.'yyyy HH:mm:ss") } }) %></div>
    </div>
    
    <%--Ranges--%>
    <div class="editor-label">
      <strong><%= Html.LabelFor(m => m.Ranges)%>*:</strong>
      <button name="command" type="submit" value="<%= DonateEventModel.RangeCommand%>_add:0" style="color: darkgreen">ADD</button>
    </div>
    
    <div style="margin-left: 20px">
      <% if (Model.Ranges.Count != 0)
          { %>
            <% for (int i = 0; i < Model.Ranges.Count; i++) { %>
              <fieldset style="border-color: #BB4400; border-style: solid; border-width:1.5px;">
                <legend>
                  <span>Range #<%=i+1 %></span>
                  <button name="command" type="submit" value="<%=DonateEventModel.RangeCommand%>_up:<%=i %>"<%= (i == 0) ? " disabled=\"disabled\"" : "" %>>&uarr;</button>
                  <button name="command" type="submit" value="<%=DonateEventModel.RangeCommand%>_down:<%=i %>"<%= (i == Model.Ranges.Count - 1) ? " disabled=\"disabled\"" : "" %>>&darr;</button>
                  <button name="command" type="submit" value="<%=DonateEventModel.RangeCommand%>_clone:<%=i %>" style="color: darkgreen">COPY</button>
                  <button name="command" type="submit" value="<%=DonateEventModel.RangeCommand%>_remove:<%=i %>" style="color: darkred">DEL</button>
                </legend>
        
                <details open="open">
                   <summary>Expand</summary>
                   <%= Html.EditorFor(m => m.Ranges[i]) %>
                </details>
              </fieldset>
            <% } %>
      <% } %>
    </div>

    <br/><br/>
    <button class="saveButton" type="submit" name="command" value=""><%= Model.New ? "Save new Donate Event" : "Save Donate Event #" + Model.Id %></button>
    <% if (!Model.New) { %>
      <button type="submit" name="command" value="Clone">Clone event</button>
    <% } %>
  <% } %>
  
  </fieldset>

</div>

</asp:Content>
