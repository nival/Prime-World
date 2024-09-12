<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<PlayerResourceFilterModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	ResourcesChangeHistory
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
  
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
    .filter { border: 0; }
    .filter td { border: 0; }
    .filter-field
    {
      float: left;
      clear: both;
      border-top: solid 1px;
      border-bottom: solid 1px;
      margin: 1px;
    }
    .filter-submit
    {
      clear: both;
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

      TalentChangeClick();
      $('.talentsChange').click(TalentChangeClick);

      ResourceChangeClick();
      $('.resourceChange').click(ResourceChangeClick);
    });

    function TalentChangeClick() {
      var talentsChangeChecked = false;
      $('.talentsChange:checked').each(function() {
        talentsChangeChecked = true;
      });
      if (talentsChangeChecked) {
        $('#TalentsFilterDetails').removeAttr("hidden");
      } else {
        $('#TalentsFilterDetails').attr("hidden", true);
      }
    }

    function ResourceChangeClick() {
      var resourceChangeChecked = false;
      $('.resourceChange:checked').each(function() {
        resourceChangeChecked = true;
      });
      if (resourceChangeChecked) {
        $('#ResourceFilterDetails').removeAttr("hidden");
      } else {
        $('#ResourceFilterDetails').attr("hidden", true);
      }
    }
  </script>

</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

<h2>Resources/talents change for player (auid = <%= Model.Auid %>)</h2>
<% if (!String.IsNullOrEmpty(Model.MessageToUser))
  { %>
    <p style="color: red">Warning!</p>
    <p style="color: red"><%= Model.MessageToUser %></p>
  <% } %>

<div id="pagemenu" style="width: 30%; float: right; margin-right: 0px; padding-left: 30px;">
  <%= Html.ActionLink("Back to account details", "Details", "Account", new { Model.Auid }, null)%>
</div>

<% using (Html.BeginForm()) { %>
  
  <%= Html.ValidationSummary() %>
  
  <fieldset>
    <legend>Filter</legend>
    
    <%= Html.HiddenFor(m => m.Auid) %>
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
      <div id="ResourceFilter" class="filter-field">
        <div style="float: left">
          <table class="filter">
            <tr>
              <td><%= Html.LabelFor(m => m.Type)%></td>
              <td><%= Html.DropDownListFor(m => m.Type, Model.GetAllTypes())%></td>
            </tr>
            <tr>
              <td><%= Html.LabelFor(m => m.SpentGold) %></td>
              <td><%= Html.CheckBoxFor(m => m.SpentGold, new Dictionary<string, object> { { "class", "resourceChange" } })%></td>
            </tr>
            <tr>
              <td><%= Html.LabelFor(m => m.SpentSilver) %></td>
              <td><%= Html.CheckBoxFor(m => m.SpentSilver, new Dictionary<string, object> { { "class", "resourceChange" } })%></td>
            </tr>
            <tr>
              <td><%= Html.LabelFor(m => m.SpentPerl) %></td>
              <td><%= Html.CheckBoxFor(m => m.SpentPerl, new Dictionary<string, object> { { "class", "resourceChange" } })%></td>
            </tr>
            <tr>
              <td><%= Html.LabelFor(m => m.SpentRedPerl) %></td>
              <td><%= Html.CheckBoxFor(m => m.SpentRedPerl, new Dictionary<string, object> { { "class", "resourceChange" } })%></td>
            </tr>
            <tr>
              <td><%= Html.LabelFor(m => m.SpentResourceN) %></td>
              <td><%= Html.CheckBoxFor(m => m.SpentResourceN, new Dictionary<string, object> { { "class", "resourceChange" } })%></td>
            </tr>
          </table>
        </div>
        <div id="ResourceFilterDetails" style="float: left">
          <table class="filter">
            <tr>
              <td><%= Html.LabelFor(m => m.ResourcesEventIndex) %></td>
              <td><%= Html.DropDownListFor(m => m.ResourcesEventIndex, Model.ResourcesEventList)%></td>
            </tr>
          </table>
        </div>
      </div>
      <div id="TalentsFilter" class="filter-field">
        <div style="margin: 7px; float: left">
          <%= Html.LabelFor(m => m.TalentsChange) %> <%= Html.CheckBoxFor(m => m.TalentsChange, new Dictionary<string, object> { { "class", "talentsChange" } })%>
        </div>
        <div id="TalentsFilterDetails" style="float: left">
          <table class="filter">
            <tr>
              <td><%= Html.LabelFor(m => m.TalentName) %></td>
              <td><%= Html.TextBoxFor(m => m.TalentName) %></td>
            </tr>
            <tr>
              <td><%= Html.LabelFor(m => m.TalentsEventIndex) %></td>
              <td><%= Html.DropDownListFor(m => m.TalentsEventIndex, Model.TalentsEventList)%></td>
            </tr>
          </table>
        </div>
      </div>
      <div id="SubmitFilters" class="filter-submit">
        <input type="submit" value="Search" style="margin-top: 10px;" />
      </div>
    </div>
  </fieldset>
<% } %>

<%-- RESULTS --%>
<% if (Model.Results != null) { %>

  <table> <%-- todo: put this out to a separate view --%>
    <tr>
      <th rowspan="2" class="timeZoneLabel">Timestamp, UTC+0</th>
      <th rowspan="2">Type</th>
      <th rowspan="2">Info</th>
      <th colspan="10" style="text-align: center">Resources change</th>
      <th colspan="9" style="text-align: center">Resources before</th>
    </tr>
    <tr>
      <th>Gold</th>
      <th>Silver</th>
      <th>Perl</th>
      <th>RedPerl</th>
      <th>R1</th>
      <th>R2</th>
      <th>R3</th>
      <th>Shard</th>
      <th>CurrencyName</th>
      <th>Currency</th>
      <th>Gold</th>
      <th>Silver</th>
      <th>Perl</th>
      <th>RedPerl</th>
      <th>R1</th>
      <th>R2</th>
      <th>R3</th>
      <th>Shard</th>
      <th>Currency</th>
    </tr>
    <% foreach (var result in Model.Results) { %>
      <tr>
        <td class="utcdateVal"><%= Html.Encode(result.Timestamp.ToString("dd.MM.yyyy HH:mm:ss"))%></td>
        <td><%= Html.Encode(result.Type) %></td>
        <td><%= Html.Encode(result.Info) %></td>
        <td><%= Html.Encode(result.GoldChange) %></td>
        <td><%= Html.Encode(result.SilverChange) %></td>
        <td><%= Html.Encode(result.PerlChange) %></td>
        <td><%= Html.Encode(result.RedPerlChange) %></td>
        <td><%= Html.Encode(result.Resource1Change) %></td>
        <td><%= Html.Encode(result.Resource2Change) %></td>
        <td><%= Html.Encode(result.Resource3Change) %></td>
        <td><%= Html.Encode(result.ShardChange)%></td>
        <td><%= Html.Encode(result.CurrencyChange)%></td>
        <td><%= Html.Encode(result.CurrencyChangeValue)%></td>
        <td><%= Html.Encode(result.GoldBefore)%></td>
        <td><%= Html.Encode(result.SilverBefore) %></td>
        <td><%= Html.Encode(result.PerlBefore)%></td>
        <td><%= Html.Encode(result.RedPerlBefore)%></td>
        <td><%= Html.Encode(result.Resource1Before)%></td>
        <td><%= Html.Encode(result.Resource2Before)%></td>
        <td><%= Html.Encode(result.Resource3Before)%></td>
        <td><%= Html.Encode(result.ShardBefore)%></td>
        <td><%= Html.Encode(result.CurrencyBeforeValue)%></td>
      </tr>
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
      <%= Html.ActionLink(i.ToString(), "ResourcesHistory", 
                          new { Model.Auid, Model.DateFrom, Model.DateTo, Model.TimeZone, Model.Type, Model.SpentGold, Model.SpentSilver, Model.SpentPerl, Model.SpentRedPerl, Model.SpentResourceN, Model.TalentsChange, Model.TalentName, page = i },
                          i == Model.Page ? new { @class = "selected" } : null) %>
    <% } %>
  </div>

<% } %>

</asp:Content>
