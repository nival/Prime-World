<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<IEnumerable<EventShortInfo>>" %>
<%@ Import Namespace="ControlCenter.Areas.EventTool.Models" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
Events list
</asp:Content>

<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">
  
  <style type="text/css">
    .enablednow {
      background: rgb(240, 255, 244);
    }
  </style>
  <script type="text/javascript" src="/Scripts/jquery.localizeDate.js"></script>
  
  <script type="text/javascript">
    
    $(document).ready(function() {
      localizeDate();

      $("#filter").change(function () {
        var selected = $("#filter").val();
        sessionStorage.setItem("selectedEventGroup", selected);
        if (selected == 'ALL') {
          $("table tr.datarow").show();
        } else {
          $("table tr.datarow").hide();
          $("table tr.datarow." + selected).show();
        }
      });

      var selectedEventGroup = sessionStorage.getItem("selectedEventGroup");
      if (selectedEventGroup) {
          $("#filter [value='" + selectedEventGroup + "']").attr("selected", "selected").change();
      }
    });

  </script>

</asp:Content>

<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">
  
  <div id="pagemenu" class="pagemenu">
    
    <div class = "menublock">
      <h4>Add new event</h4>
      <% foreach (var evt in Enum.GetValues(typeof(EventType)).OfType<EventType>().OrderBy(e => e.ToString())) { %>
        <p><%= Html.ActionLink(evt.GetDescription(), evt.ToString())%></p>
      <% } %>
    </div>

  </div>

  <div id="pagecontent" style="width: 70%">
    <h1>Events list</h1>
    
    <div style="margin: 15px">
      Show events:
      <select id="filter">
        <option value="ALL" selected="selected">ALL</option>
        <% foreach (var evt in Enum.GetValues(typeof(EventType)).OfType<EventType>().OrderBy(e => e.ToString())) { %>
          <option value="<%= evt.ToString().ToLower() %>"><%= evt.GetDescription() %></option>
        <% } %>
      </select>
    </div>

    <% if (Model.Any(m => m.Enabled)) { %>
      <div style="margin-top: 20px">
        <h2>Active events</h2>
        <table>
          <tr>
            <th><%= Html.LabelFor(m => m.FirstOrDefault().Id) %></th>
            <th><%= Html.LabelFor(m => m.FirstOrDefault().Type) %></th>
            <th class="timeZoneLabel">Start date, utc+0</th>
            <th class="timeZoneLabel">End date, utc+0</th>
            <th><%= Html.LabelFor(m => m.FirstOrDefault().Description) %></th>
            <th>Edit</th>
            <th>Stop</th>
            <th>Delete</th>
          </tr>
          <% foreach (var m in Model.Where(m => m.Enabled)) { %>
             <%
               string htmlClass = "datarow " + m.Type.ToString().ToLower();
               if ( DateTime.Now.ToUniversalTime() >= m.StartTime && DateTime.Now.ToUniversalTime() <= m.EndTime.AddHours( -m.TimeZone ) )
                 htmlClass += " enablednow";
             %>
            <tr class="<%= htmlClass %>">
              <td><%= Html.Encode(m.Id) %></td>
              <td><%= Html.Encode(m.Type.GetDescription()) %></td>
              <td class="utcdateText"><%= Html.Encode(m.StartTime.ToString("dd'.'MM'.'yyyy HH:mm:ss")) %></td>
              <td class="utcdateText"><%= Html.Encode(m.EndTime.ToString("dd'.'MM'.'yyyy HH:mm:ss")) %></td>
              <td><%= Html.Encode(m.Description) %></td>
              <td><%= Html.ActionLink(">>", m.Type.ToString(), new { id = m.Id }) %></td>
              <td><%= Html.ActionLink("stop", "Stop", new { id = m.Id }) %></td>
              <td><%= Html.ActionLink("delete", "Delete", new { id = m.Id }, new { @class = "link-delete" }) %></td>
            </tr>
          <% } %>
        </table>
      </div>
    <% } %>

    <% if (Model.Any(m => !m.Enabled)) { %>
      <div style="margin-top: 20px">
        <h2>Stopped events</h2>
        <table>
          <tr>
            <th><%= Html.LabelFor(m => m.FirstOrDefault().Id) %></th>
            <th><%= Html.LabelFor(m => m.FirstOrDefault().Type) %></th>
            <th class="timeZoneLabel">Start date, utc+0</th>
            <th class="timeZoneLabel">End date, utc+0</th>
            <th><%= Html.LabelFor(m => m.FirstOrDefault().Description) %></th>
            <th>Edit</th>
            <th>Start</th>
            <th>Delete</th>
          </tr>
          <% foreach (var m in Model.Where(m => !m.Enabled)) { %>
             <% string htmlClass = "datarow " + m.Type.ToString().ToLower(); %>
            <tr class="<%= htmlClass %>">
              <td><%= Html.Encode(m.Id) %></td>
              <td><%= Html.Encode(m.Type.GetDescription()) %></td>
              <td class="utcdateText"><%= Html.Encode(m.StartTime.ToString("dd'.'MM'.'yyyy HH:mm:ss")) %></td>
              <td class="utcdateText"><%= Html.Encode(m.EndTime.ToString("dd'.'MM'.'yyyy HH:mm:ss")) %></td>
              <td><%= Html.Encode(m.Description) %></td>
              <td><%= Html.ActionLink(">>", m.Type.ToString(), new { id = m.Id }) %></td>
              <td><%= Html.ActionLink("start", "Start", new { id = m.Id }) %></td>
              <td><%= Html.ActionLink("delete", "Delete", new { id = m.Id }, new { @class = "link-delete" }) %></td>
            </tr>
          <% } %>
        </table>
      </div>
    <% } %>

    <% if (!Model.Any()) { %>
      <h2>Nothing here =(</h2>
    <% } %>
  
  </div>

</asp:Content>
