<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<IEnumerable<ControlCenter.Areas.GM.Models.TalentUpgradeEntityInfoModel>>" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
	Talent Upgrade Entities
</asp:Content>

<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">

<% var auid = (long) ViewData["auid"]; %>

<div id="pagemenu" style="width: 30%; float: right; margin-right: 0px">
  <p><%= Html.ActionLink("Back to account details", "Details", new { auid })%></p>
</div>

<div id="pagecontent" style="width: 70%">
  
  <h2>Entities list (auid=<%= auid %>)</h2>
  
  <table>
      <tr>
      <th>InstanceId</th>
      <th>PersistentId</th>
      <th>Chance</th>
      <th>TalentLevelLimit</th>
      </tr>
      <% foreach (var entity in Model.OrderBy(m => m.Type).ThenByDescending(m => m.TalentLevelLimit).ThenByDescending(m => m.Chance))
          { %>
      <tr>
          <td><%= Html.Encode(entity.InstanceId) %></td>
          <td><%= Html.Encode(entity.PersistentId) %></td>
          <td><%= Html.Encode(entity.Chance)%></td>
          <td><%= Html.Encode(entity.TalentLevelLimit)%></td>
          <% if (((GMToolsPrincipal)User).HasPermission("GM_AccountEdit")) { %>
          <td><%= Html.ActionLink("Delete", "DeleteTalentUpgradeEntity", new { auid, entity.InstanceId }) %></td>
          <% } %>
      </tr>
      <% } %>
  </table>
 
</div>
</asp:Content>
