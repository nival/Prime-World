<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<IEnumerable<UserInfoModel>>" %>
<%@ Import Namespace="ControlCenter.Areas.Admin.Models"%>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
  Users
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <h2>Users</h2>
  <table>
    <tr>
      <th>UserName</th>
      <th>FullName</th>
      <th>Email</th>
      <th>Superuser</th>
    </tr>
    <% foreach (var item in Model.OrderBy(m => m.UserName)) { %>
    <tr>
      <td>
        <%= Html.ActionLink(item.UserName, "Details", new { id = item.UserId })%>
        <%--<%= Html.Encode(item.UserName) %>--%>
      </td>
      <td>
        <%= Html.Encode(item.FullName) %>
      </td>
      <td>
        <%= Html.Encode(item.Email) %>
      </td>
      <td>
        <%= item.Superuser ? "Y" : "N" %>
      </td>
      <td>
        <%= Html.ActionLink( "delete", "DeleteUser", new { UserId = item.UserId }, new { @class = "link-delete" } )%>
      </td>
    </tr>
    <% } %>
  </table>
  <p>
    <%= Html.ActionLink("Create New", "Create") %>
  </p>
</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>
