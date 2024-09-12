<%@ Page Title="GWEventsHistory" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<ControlCenter.Areas.GWEvents.Models.GWEventHistory>" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
	GWEventHistory
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
  <script type="text/javascript" src="../../../../Scripts/jquery.localizeDate.js"></script>

  <script type="text/javascript">
    $(document).ready(function () {
      localizeDate();
      $('#StartTime').datetimepicker({ dateFormat: 'dd.mm.yy', timeFormat: 'hh:mm:ss', showSecond: true });
      $('#EndTime').datetimepicker({ dateFormat: 'dd.mm.yy', timeFormat: 'hh:mm:ss', showSecond: true });
    });
  </script>
</asp:Content>

<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">
    
    <div id="pagemenu" style="width: 30%; float: right; margin-right: 0px">
        <p><%= Html.ActionLink("Back to GWEvents", "GWEvent", new { })%></p>
    </div>
    
  <h3>PoolPoints History for Event: <%= Model.EventIdx %> </h3>
  <% using (Html.BeginForm()) { %>
  
    <%= Html.ValidationSummary(true) %>
    <div style="margin-top: 10px">
      <div >Start Time</div>
      <td><%= Html.TextBoxFor(m => m.StartTime, new Dictionary<string, object> { { "Value", Model.StartTime.ToString("dd.MM.yyyy HH:mm:ss") } })%></td>
      <%= Html.ValidationMessageFor(m => m.StartTime)%>
    </div>
    <div style="margin-top: 10px">
      <div >End time</div>
      <td><%= Html.TextBoxFor(m => m.EndTime, new Dictionary<string, object> { { "Value", Model.EndTime.ToString("dd.MM.yyyy HH:mm:ss") } })%></td>
      <%= Html.ValidationMessageFor(m => m.EndTime)%>
    </div>
    
    <br/>
    <input type="submit" value="Set time interval"/>

  <% } %>
  <br/>
  <br/>

    <%= Html.HiddenFor(m => m.Page) %>
    <%= Html.HiddenFor(m => m.TotalPages) %>

     <table>
        <tr>
            <td></td>
            <td><b>GuildId</b></td>
            <td><b>Points</b></td>
            <td><b>TimeStamp</b></td>
        </tr>
    <% for (int i = 0; i < Model.GwEvents.Count; i++){ %>
        
        
         <tr>
           <td style="background-color: gold; color: black">
             <%= i + 1 %>
           </td>
           <td>
             <%= Model.GwEvents[i].GuildId %>
           </td>
           <td>
             <%= Model.GwEvents[i].CurrentPoints %>
           </td>
           <td>
             <%= Model.GwEvents[i].TimeStamp %>
           </td>
         </tr>
    
    <% } %>
    </table>
    
  
     <% if (Model.TotalPages == 0)
     {
       Model.TotalPages = 1;
       Model.Page = 1;
     } %>
    <br/>
    <br/>
    <div class="pager">
      Page :
      <% for (int i = 1; i <= Model.TotalPages; i++) { %>
        <%= Html.ActionLink(i.ToString(), "GWEventHistory", new { eventIdx = Model.EventIdx, page = i }, i == Model.Page ? new { @class = "selected" } : null)%>
      <% } %>
    </div>

</asp:Content>
