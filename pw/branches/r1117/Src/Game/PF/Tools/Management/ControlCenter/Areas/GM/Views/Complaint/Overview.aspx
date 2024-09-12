<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.GM.Models.ComplaintOverviewModel>" %>
<%@ Import Namespace="ControlCenter.Areas.GM.Views" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
	Overview
</asp:Content>

<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">

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

      $('.checkAll').click(
        function() {
          $('#chkTable td input:checkbox').attr('checked', this.checked);
        });
    });
  </script>

</asp:Content>

<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">

  <h2>Overview</h2>

  <% using (Html.BeginForm()) { %>
  <%= Html.ValidationSummary(true) %>
    
    <fieldset>
      <legend>Filter</legend>
      
      <%= Html.HiddenFor(m => m.TimeZone) %>
      <%= Html.HiddenFor(m => m.OrderBy) %>
      <%= Html.HiddenFor(m => m.Asc) %>
      
      <table class="filter">
        <tr>
          <td colspan="2"><label for="DateFrom" class="timeZoneLabel">From date, UTC+0</label></td>
          <td><%= Html.TextBoxFor(m => m.DateFrom, new Dictionary<string, object> { { "class", "utcdateVal" }, { "Value", Model.DateFrom.ToString("dd.MM.yyyy HH:mm:ss") } })%></td>
        </tr>
        <tr>
          <td colspan="2"><label for="DateTo" class="timeZoneLabel">To date, UTC+0</label></td>
          <td><%= Html.TextBoxFor(m => m.DateTo, new Dictionary<string, object> { { "class", "utcdateVal" }, { "Value", Model.DateTo.ToString("dd.MM.yyyy HH:mm:ss") } })%></td>
        </tr>
        <tr>
          <td colspan="2"><%= Html.LabelFor(m => m.ComplaintType)%></td>
          <td><%= Html.DropDownListFor(m => m.ComplaintType, Model.ComplaintTypesList)%></td>
        </tr>
        <tr>
          <td style="text-align:right" colspan="2"><%= Html.LabelFor(m => m.MinComplaints)%></td>
          <td><%= Html.TextBoxFor(m => m.MinComplaints)%></td>
          <td><%= Html.ValidationMessageFor(m => m.MinComplaints)%></td>
        </tr>
        <tr>
          <td style="text-align:right" colspan="2"><%= Html.LabelFor(m => m.MaxComplaints)%></td>
          <td><%= Html.TextBoxFor(m => m.MaxComplaints)%></td>
          <td><%= Html.ValidationMessageFor(m => m.MaxComplaints)%></td>
        </tr>
        <tr>
          <td colspan="2"><%= Html.LabelFor(m => m.HistoryType)%></td>
          <td><%= Html.DropDownListFor(m => m.HistoryType, Model.HistoryTypesList)%></td>
        </tr>
        <tr>
          <td style="text-align:right" colspan="2"><%= Html.LabelFor(m => m.MinHistory)%></td>
          <td><%= Html.TextBoxFor(m => m.MinHistory)%></td>
          <td><%= Html.ValidationMessageFor(m => m.MinHistory)%></td>
        </tr>
        <tr>
          <td style="text-align:right" colspan="2"><%= Html.LabelFor(m => m.MaxHistory)%></td>
          <td><%= Html.TextBoxFor(m => m.MaxHistory)%></td>
          <td><%= Html.ValidationMessageFor(m => m.MaxHistory)%></td>
        </tr>
        <tr>
          <td colspan="2"><%= Html.LabelFor(m => m.ReportedBy)%></td>
          <td><%= Html.TextBoxFor(m => m.ReportedBy)%></td>
        </tr>
        <tr>
          <td colspan="2"><%= Html.LabelFor(m => m.UsersPerPage)%></td>
          <td><%= Html.TextBoxFor(m => m.UsersPerPage)%></td>
        </tr>
        <tr>
          <td colspan="2"><%= Html.LabelFor(m => m.Locale)%></td>
          <% var allLocales = ComplaintOverviewModel.AllLocales.Where(l => ((GMToolsPrincipal) User).HasLocale(l)).ToList(); %>
          <% if (!allLocales.Contains(Model.Locale)) Model.Locale = allLocales.FirstOrDefault(); %>
          <td><%= Html.DropDownListFor(m => m.Locale, allLocales.Select(l => new SelectListItem {Text = l, Value = l}))%></td>
        </tr>
        <tr>
          <td>Leaver points</td>
          <td style="text-align:right"><%= Html.LabelFor(m => m.MinLeaverPoints)%></td>
          <td><%= Html.TextBoxFor(m => m.MinLeaverPoints)%></td>
        </tr>
        <tr>
          <td style="text-align:right" colspan="2"><%= Html.LabelFor(m => m.MaxLeaverPoints)%></td>
          <td><%= Html.TextBoxFor(m => m.MaxLeaverPoints)%></td>
        </tr>
        <tr>
          <td>Leaver status<br/>change</td>
          <td style="text-align:right"><%= Html.LabelFor(m => m.MinLeaverStatusChanges)%></td>
          <td><%= Html.TextBoxFor(m => m.MinLeaverStatusChanges)%></td>
        </tr>
        <tr>
          <td style="text-align:right" colspan="2"><%= Html.LabelFor(m => m.MaxLeaverStatusChanges)%></td>
          <td><%= Html.TextBoxFor(m => m.MaxLeaverStatusChanges)%></td>
        </tr>
        <tr>
          <td>Leaver status<br/>change by GM</td>
          <td style="text-align:right"><%= Html.LabelFor(m => m.MinLeaverStatusChangesByGM)%></td>
          <td><%= Html.TextBoxFor(m => m.MinLeaverStatusChangesByGM)%></td>
        </tr>
        <tr>
          <td style="text-align:right" colspan="2"><%= Html.LabelFor(m => m.MaxLeaverStatusChangesByGM)%></td>
          <td><%= Html.TextBoxFor(m => m.MaxLeaverStatusChangesByGM)%></td>
        </tr>
        <tr>
            <td colspan="2"><%= Html.LabelFor(m => m.BanAmnistia)%></td>
            <td><%= Html.DropDownListFor(m => m.BanAmnistia, Model.YesNoList)%></td>
        </tr>
        <tr>
            <td colspan="2"><%= Html.LabelFor(m => m.MuteTimeAmnistia)%></td>
            <td><%= Html.DropDownListFor(m => m.MuteTimeAmnistia, Model.YesNoList)%></td>
        </tr>
        <tr>
            <td colspan="2"><%= Html.LabelFor(m => m.LeaveAmnistia)%></td>
            <td><%= Html.DropDownListFor(m => m.LeaveAmnistia, Model.YesNoList)%></td>
        </tr>
      </table>
    
      <input type="submit" value="Search" style="margin-top: 10px;" />
      
    </fieldset>
  <% } %>


  <%-- RESULTS --%>

<% using (Html.BeginForm("UserOperation", "Account")) { %>
  
  <% if (Model.Results != null) { %>
    <% if (((GMToolsPrincipal)User).HasPermission("GM_AccountBanMute"))
       { %>
      <input type="submit" name="op" value="Ban"/>
      <input type="submit" name="op" value="Mute"/>
      <input type="submit" name="op" value="Forgive"/>
      <button type="submit" name="op" value="SetLeave">Add leave points</button>
    <% } %>

    <table id="chkTable">
      <tr>
        <th><input type="checkbox" class="checkAll" /></th>
        <th>Player</th>
        <th class="results"><%= Html.SortingLink(m => m.Results[0].ClaimsCount, "Overview", Model, false)%></th>
        <th class="results"><%= Html.SortingLink(m => m.Results[0].OffenceClaimsCount, "Overview", Model, false)%></th>
        <th class="results"><%= Html.SortingLink(m => m.Results[0].UnfairClaimsCount, "Overview", Model, false)%></th>
        <th class="results"><%= Html.SortingLink(m => m.Results[0].BotClaimsCount, "Overview", Model, false)%></th>
        <th class="results"><%= Html.SortingLink(m => m.Results[0].GMUserOperationsCount, "Overview", Model, false)%></th>
        <th class="results"><%= Html.LabelFor(m => m.Results[0].Status)%></th>
        <th class="results">LeaverPoints<br/>ChangedByGm/AllChanges</th>
        <th class="results">LastBanMuteTimeAmnistia</th>
        <th class="results">Amnistia</th>
      </tr>
    <% foreach (var result in Model.Results) { %>
      <tr>
        <td><input type="checkbox" name="selected" value="<%= String.Format("{0}_{1}_{2}", result.Auid, result.Nickname, result.ClaimsCount) %>"/></td>
        <td><%= Html.Encode(String.Format("{0} (auid={1})", result.Nickname, result.Auid)) %></td>
        <td>
          <% if (String.IsNullOrEmpty(Model.Locale)) { %>
            <%= result.ClaimsLocaleCount.Replace("\n","<br>") %>
          <% } %>
          <%= Html.ActionLink("Total: " + result.ClaimsCount, "Complaints", "Account", new { result.Auid, result.Nickname, Model.Locale }, null) %>
        </td>
        <td><%= Html.Encode(result.OffenceClaimsCount) %></td>
        <td><%= Html.Encode(result.UnfairClaimsCount) %></td>
        <td><%= Html.Encode(result.BotClaimsCount) %></td>
        <td>
          <% if (result.GMUserOperationsCount > 0) { %>
            <% if (result.GMBansCount > 0) { %> 
              <%= Html.Encode(result.GMBansCount) %> <%= Html.LabelFor(m => m.Results[0].GMBansCount)%><br/>
            <% } %>
            <% if (result.GMMutesCount > 0) { %> 
              <%= Html.Encode(result.GMMutesCount)%> <%= Html.LabelFor(m => m.Results[0].GMMutesCount)%><br/>
            <% } %>
            <% if (result.GMUnbansCount > 0) { %> 
              <%= Html.Encode(result.GMUnbansCount)%> <%= Html.LabelFor(m => m.Results[0].GMUnbansCount)%><br/>
            <% } %>
            <% if (result.GMUnmutesCount > 0) { %> 
              <%= Html.Encode(result.GMUnmutesCount)%> <%= Html.LabelFor(m => m.Results[0].GMUnmutesCount)%><br/>
            <% } %>
            <% if (result.GMForgivesCount > 0) { %> 
              <%= Html.Encode(result.GMForgivesCount)%> <%= Html.LabelFor(m => m.Results[0].GMForgivesCount)%><br/>
            <% } %>
            <%= Html.ActionLink("view all", "BanAndMuteHistory", "HistoryUI", new { result.Auid }, null)%>
          <% } %>
        </td>
        <td>
          <% if (!String.IsNullOrEmpty(result.Status)) { %>
            <%= result.Status.Replace("\n", "<br>") %>
          <% } %>
        </td>
        <td><%= Html.Encode(result.LeaverPoints)%><br/><%= Html.Encode(result.LeaverChangedByGM) %>/<%= Html.Encode(result.LeaverChanged) %></td>
        <td><%= result.LastBanMuteTime%></td>
        <td><%= result.Amnistia%></td>
      </tr>
    <% } %>
    </table>
    
    <%= Html.Hidden("returnUrl", Request.Url.PathAndQuery)%>
    
    <div class="pager">
      Page : <%= Html.PageLinks( Model.PageNum, Model.TotalPages, x => Url.Action( "Overview", new
                 {
                   pageNum = x, 
                   Model.DateFrom, 
                   Model.DateTo,
                   Model.TimeZone,
                   Model.ComplaintType, 
                   Model.MinComplaints, 
                   Model.MaxComplaints, 
                   Model.HistoryType, 
                   Model.MinHistory,
                   Model.MaxHistory,
                   Model.ReportedBy, 
                   Model.MinLeaverPoints,
                   Model.MaxLeaverPoints,
                   Model.MinLeaverStatusChanges,
                   Model.MaxLeaverStatusChanges,
                   Model.MinLeaverStatusChangesByGM,
                   Model.MaxLeaverStatusChangesByGM,
                   Model.UsersPerPage, 
                   Model.OrderBy, 
                   Model.Asc
                 } ) )%>
    </div>
    
  <% } %>

<% } %>


</asp:Content>
