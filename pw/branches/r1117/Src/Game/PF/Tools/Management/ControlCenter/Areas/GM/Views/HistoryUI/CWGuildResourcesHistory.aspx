<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<CWGuildResourcesFilterModel>" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
ClanWars guild resources change history
</asp:Content>

<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">
  
  <link rel="stylesheet" href="/Content/pager.css" />
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

  <script type="text/javascript" src="../../Scripts/jquery-ui-1.8.16.custom.min.js"></script>
  <script type="text/javascript" src="../../Scripts/jquery.localizeDate.js"></script>
  <script type="text/javascript" src="../../Scripts/jquery-ui-timepicker-addon.js"></script>
  <script type="text/javascript" src="../../Scripts/jquery-ui-sliderAccess.js"></script>

  <script type="text/javascript">
    $(document).ready(function() {
      localizeDate();
      $('#DateFrom').datetimepicker({ dateFormat: 'dd.mm.yy', timeFormat: 'hh:mm:ss', showSecond: true });
      $('#DateTo').datetimepicker({ dateFormat: 'dd.mm.yy', timeFormat: 'hh:mm:ss', showSecond: true });
    });
  </script>
  
</asp:Content>



<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">
  
<h2>Guild points changes history for guild (id = <%= Model.GuildId %>)</h2>

<div id="pagemenu" style="width: 30%; float: right; margin-right: 0px; padding-left: 30px;">
  <%= Html.ActionLink("Back to guild details", "Details", "Guild", new { id = Model.GuildId}, null)%>
</div>

<% using (Html.BeginForm()) { %>

  <%= Html.HiddenFor(m => m.GuildId) %>
  <%= Html.HiddenFor(m => m.TimeZone) %>

  <div class="filter">
    <div id="DateFilter" class="filter-field">
      <table class="filter">
        <tr>
          <td><label for="DateFrom" class="timeZoneLabel">From date, UTC+0</label></td>
          <td><%= Html.TextBoxFor(m => m.DateFrom, new Dictionary<string, object> { { "class", "utcdateVal" }, { "Value", Model.DateFrom.ToString("dd.MM.yyyy HH:mm:ss") } })%></td>
        </tr>
        <tr>
          <td><label for="DateTo" class="timeZoneLabel">To date, UTC+0</label></td>
          <td><%= Html.TextBoxFor(m => m.DateTo, new Dictionary<string, object> { { "class", "utcdateVal" }, { "Value", Model.DateTo.ToString("dd.MM.yyyy HH:mm:ss") } })%></td>
        </tr>
      </table>
    </div>
    <input type="submit" value="Search" style="margin-top: 10px;" />
  </div>
  
  <table style="margin-top: 10px">
    <tr>
      <th class="timeZoneLabel">Timestamp, UTC+0</th>
      <th>Type</th>
      <th>Player</th>
      <th>GuildPointsChange</th>
      <th>GuildPointsTotal</th>
      <th>GuildShopItemName</th>
      <th>SiegeId</th>
      <th>TargetGuild</th>
    </tr>
    <% if (Model.Results != null) { %>
      <% foreach (var result in Model.Results) { %>
        <tr>
          <td class="utcdateVal"><%= Html.Encode(result.Timestamp.ToString("dd.MM.yyyy HH:mm:ss"))%></td>
          <td><%= Html.Encode(result.Type) %></td>
          <td><%= Html.Encode(result.Player) %></td>
          <td><%= Html.Encode(result.GuildPointsChange)%></td>
          <td><%= Html.Encode(result.GuildPointsTotal)%></td>
          <td><%= Html.Encode(result.GuildShopItemName)%></td>
          <td><%= Html.Encode(result.SiegeId != 0 ? result.SiegeId.ToString() : "")%></td>
          <td><%= Html.Encode(result.TargetGuild != 0 ? result.TargetGuild.ToString() : "")%></td>
        </tr>
      <% } %>
    <% } %>
    
  </table>
  
    <% if (Model.TotalPages == 0)
     {
       Model.TotalPages = 1;
       Model.Page = 1;
     } %>
  <div class="pager">
    Page :
    <% for (int i = 1; i <= Model.TotalPages; i++) { %>
      <%= Html.ActionLink(i.ToString(), "CWGuildResourcesHistory", 
                          new { Model.GuildId, Model.DateFrom, Model.DateTo, Model.TimeZone, page = i },
                          i == Model.Page ? new { @class = "selected" } : null) %>
    <% } %>
  </div>

  
<% } %>  
  
</asp:Content>

