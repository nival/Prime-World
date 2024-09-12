<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<IEnumerable<ControlCenter.Areas.GM.Models.BuildingInfoModel>>" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
	Buildings
</asp:Content>

<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">
  
<% var auid = (long) ViewData["auid"]; %>

<div id="pagemenu" style="width: 30%; float: right; margin-right: 0px">
  <p><%= Html.ActionLink("Add new building", "AddBuilding", new { auid })%></p>
  <p><%= Html.ActionLink("Back to account details", "Details", new { auid })%></p>
</div>

<div id="pagecontent" style="width: 70%">
  <h2>Buildings list (auid=<%= auid %>)</h2>
  
  <% if (Model.Any(m => !m.InStorage)) { %>
    <h3>Placed buildings</h3>
    <table>
      <tr>
        <th>InstanceId</th>
        <th>Name</th>
        <th>Level</th>
      </tr>
      <% foreach (var building in Model.Where(m => !m.InStorage).OrderBy(m => m.Name)) { %>
        <tr>
          <td><%= building.InstanceId %></td>
          <td><%= Html.Encode(String.Format("{0} ({1})", building.Name, building.Description)) %></td>
          <td><%= building.MaxLevel > 1 ? building.Level.ToString() : String.Empty %></td>
          <% if (((GMToolsPrincipal)User).HasPermission("GM_AccountEdit")) { %>
            <td>
              <%= Html.ActionLink("Delete", "DeleteBuilding", new { auid, building.InstanceId })%> |
              <%= Html.ActionLink("To storage", "MoveBuilding", new { auid, building.InstanceId })%>
            </td>
          <% } %>
        </tr>
      <% } %>
    </table>
  <% } %>
  
  <% if (Model.Any(m => m.InStorage)) { %>
    <h3>Storage</h3>
    <table>
      <tr>
        <th>InstanceId</th>
        <th>Name</th>
        <th>Level</th>
      </tr>
      <% foreach (var building in Model.Where(m => m.InStorage).OrderBy(m => m.Name)) { %>
        <tr>
          <td><%= building.InstanceId %></td>
          <td><%= Html.Encode(String.Format("{0} ({1})", building.Name, building.Description)) %></td>
          <td><%= building.MaxLevel > 1 ? building.Level.ToString() : String.Empty %></td>
          <% if (((GMToolsPrincipal)User).HasPermission("GM_AccountEdit")) { %>
            <td><%= Html.ActionLink("Delete", "DeleteBuilding", new { auid, building.InstanceId })%></td>
          <% } %>
        </tr>
      <% } %>
    </table>
  <% } %>

</div>
</asp:Content>


