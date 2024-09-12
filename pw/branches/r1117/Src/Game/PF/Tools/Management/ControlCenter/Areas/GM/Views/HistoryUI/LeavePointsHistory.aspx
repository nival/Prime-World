<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<LeavePointsFilterModel>" %>


<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
Leave points history
</asp:Content>


<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">
  <link rel="stylesheet" href="/Content/pager.css" />
  <link rel="stylesheet" href="/Content/jquery-ui-1.8.17.custom.css" />

  <script type="text/javascript" src="/Scripts/jquery-ui-1.8.16.custom.min.js"></script>
  <script type="text/javascript" src="/Scripts/jquery.localizeDate.js"></script>
  <script type="text/javascript" src="/Scripts/jquery-ui-timepicker-addon.js"></script>
  <script type="text/javascript" src="/Scripts/jquery-ui-sliderAccess.js"></script>

  <script type="text/javascript">
      $(document).ready(function () {
        localizeDate();
        $('#DateFrom').datetimepicker({ dateFormat: 'dd.mm.yy', timeFormat: 'hh:mm:ss', showSecond: true });
        $('#DateTo').datetimepicker({ dateFormat: 'dd.mm.yy', timeFormat: 'hh:mm:ss', showSecond: true });
      });
  </script>
</asp:Content>


<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

  <div class="pagemenu">
    <p>
      <%= Html.ActionLink( "Back to account details", "Details", "Account", new { Model.Auid }, new { } )%>
    </p>
  </div>
  
  <div>
    <h2>Leave points change history for player (auid=<%= Model.Auid %>)</h2>
    <h4>Became leaver: <%= Model.LeaverCount %></h4>
    <h4>Became leaver by GM: <%= Model.LeaverGMCount %></h4>
  </div>

  <% using (Html.BeginForm()) { %>

    <%= Html.HiddenFor(m => m.Auid) %>
    <%= Html.HiddenFor(m => m.TimeZone) %>

    <div class="filter">
      <div id="DateFilter" class="filter-field">
        <table class="filter">
          <tr>
            <td><label for="DateFrom" class="timeZoneLabel">From date, UTC+0</label></td>
            <td><%= Html.TextBoxFor(m => m.DateFrom, new Dictionary<string, object> { { "class", "utcdateVal" }, { "Value", Model.DateFrom.ToString("dd.MM.yyyy HH:mm:ss") } }) %></td>
          </tr>
          <tr>
            <td><label for="DateTo" class="timeZoneLabel">To date, UTC+0</label></td>
            <td><%= Html.TextBoxFor(m => m.DateTo, new Dictionary<string, object> { { "class", "utcdateVal" }, { "Value", Model.DateTo.ToString("dd.MM.yyyy HH:mm:ss") } }) %></td>
          </tr>
        </table>
      </div>
      <input type="submit" value="Search" style="margin-top: 10px;" />
    </div>

  <% } %>
  
  <table style="margin-top: 10px">
    <tr>
      <th class="timeZoneLabel">Timestamp, UTC+0</th>
      <th>Type</th>
      <th>Game session id</th>
      <th>Leaver points change</th>
      <th>Leaver points total</th>
      <th>Is leaver</th>
      <th>Changed</th>
      <th>Bad behaviour</th>
    </tr>
    <% if (Model.Results != null) { %>
      <% foreach (var result in Model.Results) { %>
        <tr>
          <td class="utcdateVal"><%= Html.Encode(result.Timestamp.ToString("dd.MM.yyyy HH:mm:ss"))%></td>
          <td><%= Html.Encode(result.Type ?? "Auto") %></td>
          <td><%= Html.Encode(result.PersistentId) %></td>
          <td><%= Html.Encode(result.LeaverPointsChange) %></td>
          <td><%= Html.Encode(result.LeaverPointsTotal) %></td>
          <td><%= Html.Encode(result.IsLeaver) %></td>
          <td><%= Html.Encode(result.IsLeaverChanged) %></td>
          <td><%= Html.Encode(result.IsBadBehaviour) %></td>
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
      <%= Html.ActionLink(i.ToString(), "LeavePointsHistory", 
                          new { Model.Auid, Model.DateFrom, Model.DateTo, Model.TimeZone, page = i },
                          i == Model.Page ? new { @class = "selected" } : null) %>
    <% } %>
  </div>


</asp:Content>
