<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<IEnumerable<RoleInfoModel>>" %>
<%@ Import Namespace="ControlCenter.Areas.Admin.Models"%>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
  Roles
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <h2>Roles</h2>
  <table>
    <tr>
      <th><%= Html.LabelFor(m => m.FirstOrDefault().RoleName) %></th>
      <th><%= Html.LabelFor(m => m.FirstOrDefault().Description) %></th>
      <th><%= Html.LabelFor(m => m.FirstOrDefault().Locale) %></th>
      <th><%= Html.LabelFor(m => m.FirstOrDefault().Muid) %></th>
    </tr>
    <% foreach (var item in Model) { %>
    <tr>
      <td><%= Html.ActionLink(item.RoleName, "Details", new { id = item.RoleId })%></td>
      <td><%= Html.Encode(item.Description) %></td>
      <td><%= Html.Encode(item.Locale)%></td>
      <td><%= Html.Encode(item.Muid)%></td>
      <td><%= Html.ActionLink( "delete", "DeleteRole", new { roleId = item.RoleId }, new { @class = "link-delete" } )%></td>
    </tr>
    <% } %>
  </table>
  <p>
    <%= Html.ActionLink("Create New", "Create") %>
  </p>
</asp:Content>
