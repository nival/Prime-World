<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<IEnumerable<ControlCenter.Areas.GM.Models.SkinInfoModel>>" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
	Skins
</asp:Content>

<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">

<% var auid = (long) ViewData["auid"]; %>

<div id="pagemenu" style="width: 30%; float: right; margin-right: 0px">
  <p><%= Html.ActionLink("Back to account details", "Details", new { auid })%></p>
</div>

<div id="pagecontent" style="width: 70%">
  
  <h2>Skins list (auid=<%= auid %>)</h2>
  
  <% if (Model.Any(m => m.Owned)) { %>
    <h3>Owned skins</h3>
    <table>
      <tr>
        <th>PersistentId</th>
        <th>Hero</th>
        <th>Available</th>
        <th>Cost</th>
      </tr>
      <% foreach (var skin in Model.Where(m => m.Owned).OrderBy(m => m.PersistentId)) { %>
        <tr>
          <td><%= Html.Encode(skin.PersistentId) %></td>
          <td><%= Html.Encode(skin.HeroClassName) %></td>
          <td><%= Html.Encode(skin.Available) %></td>
          <td><%= Html.Encode(skin.Cost) %></td>
          <% if (((GMToolsPrincipal	)User).HasPermission("GM_AccountEdit")) { %>
            <td><%= Html.ActionLink("Delete", "DeleteSkin", new { auid, skin.PersistentId }) %></td>
          <% } %>
        </tr>
      <% } %>
    </table>
  <% } %>
  
  <% if (Model.Any(m => !m.Owned)) { %>
    <h3>Not owned skins</h3>
    <table>
      <tr>
        <th>PersistentId</th>
        <th>Hero</th>
        <th>Available</th>
        <th>Cost</th>
      </tr>
      <% foreach (var skin in Model.Where(m => !m.Owned).OrderBy(m => m.PersistentId)) { %>
        <tr>
          <td><%= Html.Encode(skin.PersistentId) %></td>
          <td><%= Html.Encode(skin.HeroClassName) %></td>
          <td><%= Html.Encode(skin.Available)%></td>
          <td><%= Html.Encode(skin.Cost) %></td>
          <% if (((GMToolsPrincipal)User).HasPermission("GM_AccountEdit")) { %>
            <td><%= Html.ActionLink("Add", "AddSkin", new { auid, skin.PersistentId })%></td>
          <% } %>
        </tr>
      <% } %>
    </table>
  <% } %>

</div>
</asp:Content>
