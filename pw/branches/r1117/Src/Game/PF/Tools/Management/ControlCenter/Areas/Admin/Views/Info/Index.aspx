<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	Index
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="Links" runat="server">
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="MainContent" runat="server">

  <h2>Admin information overview</h2>
  <%
    var all_users = (Dictionary<int, string>) ViewData["AllUsers"];
    var all_roles = (Dictionary<int, string>) ViewData["AllRoles"];
  %>
  
  <style type="text/css">
    .simplelist * {
      border-style: none;
    }
    .simplelist {
      border-style: none;
    }
  </style>
  
  <div style="float:left; width: 210px">
    <table class="simplelist">
      <tr>
        <th>Users</th>
      </tr>
    <%foreach (var u in all_users) { %>
      <tr>
        <td><%= Html.ActionLink(u.Value, "Details", "Users", new { id = u.Key }, null)%></td>
      </tr>
    <%}%>
    </table>
    <br />
    <%= Html.ActionLink(String.Format("View all {0} users", all_users.Count), "Index", "Users")%>
  </div>
  
  <div style="margin-left: 215px">
    <table class="simplelist">
      <tr>
        <th>Roles</th>
      </tr>
    <%foreach (var r in all_roles) { %>
      <tr>
        <td><%= Html.ActionLink(r.Value, "Details", "Roles", new { id = r.Key }, null)%></td>
      </tr>
    <%}%>
    </table>
    <br />
    <%= Html.ActionLink(String.Format("View all {0} roles", all_roles.Count), "Index", "Roles")%>
  </div>

  <div style="clear:both"></div>

</asp:Content>