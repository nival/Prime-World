<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<RuneOperationsFilterModel>" %>


<asp:Content runat="server" ID="Title" ContentPlaceHolderID="TitleContent">
Runes history
</asp:Content>


<asp:Content runat="server" ID="Links" ContentPlaceHolderID="Links">
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


<asp:Content runat="server" ID="Main" ContentPlaceHolderID="MainContent">

  <div class="pagemenu">
    <p>
      <%= Html.ActionLink( "Back to account details", "Details", "Account", new { Model.Auid }, new { } )%>
    </p>
  </div>
  
  <h2>Runes history for player (auid=<%= Model.Auid %>)</h2>

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
      <th>Operation</th>
      <th>Percent</th>
      <th>Additional data</th>
      <th>Old count</th>
      <th>New count</th>
    </tr>
    <% if (Model.Results != null) { %>
      <% foreach (var result in Model.Results) { %>
        <tr>
          <td class="utcdateVal"><%= Html.Encode(result.Timestamp.ToString("dd.MM.yyyy HH:mm:ss"))%></td>
          <td><%= Html.Encode(result.Operation) %></td>
          <td><%= Html.Encode(result.RunePercent) %></td>
          <td><%= Html.Encode(result.Data) %></td>
          <td><%= Html.Encode(result.RunesCountOld)%></td>
          <td><%= Html.Encode(result.RunesCountNew)%></td>
        </tr>
      <% } %>
    <% } %>
  </table>

</asp:Content>
