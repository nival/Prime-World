<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<UserInfoModel>" %>
<%@ Import Namespace="ControlCenter.Areas.Admin.Models"%>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
  UserEdit
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <h2>UserDetails</h2>

  <fieldset>
    <legend>Fields</legend>

    <table>
      <tr>
        <td><span class="display-label">UserName</span></td>
        <td><span class="display-field"><%= Html.Encode(Model.UserName) %></span></td>
      </tr>
      <tr>
        <td><span class="display-label">FullName</span></td>
        <td><span class="display-field"><%= Html.Encode(Model.FullName)%></span></td>
      </tr>
      <tr>
        <td><span class="display-label">Email</span></td>
        <td><span class="display-field"><%= Html.Encode(Model.Email)%></span></td>
      </tr>
      <tr>
        <td><span class="display-label">Superuser</span></td>
        <td><span class="display-field"><%= Model.Superuser ? "Y" : "N" %></span></td>
      </tr>
    </table>
    
    <table style="margin-top: 20px">
      <tr>
        <td width="150">Member of roles</td>
        <td>
        <% foreach (var r in Model.Roles) { %>
           <%= Html.ActionLink(r.Value, "Details", "Roles", new { id = r.Key }, null)%> <br />
        <% } %>
        </td>
      </tr>
    </table>
    
    <table style="margin-top: 20px">
      <tr>
        <td width="150">Have permissions<br />(through roles)</td>
        <td>
        <% if (!Model.Superuser) { %>
          <% foreach (var p in Model.Permissions) { %>
             <%= Html.Encode(p.Value) %> <br />
          <% } %>
        <% } else { %>
          All permissions are allowed to superuser.
        <% } %>
        </td>
      </tr>
    </table>

  </fieldset>

  <p>
    <%= Html.ActionLink("Edit", "Edit", new { id = Model.UserId }) %> |
    <%= Html.ActionLink("Edit roles", "EditRoles", new { id = Model.UserId }) %> |
    <%= Html.ActionLink("Reset password", "ResetPassword", new { id = Model.UserId }) %> |
    <%= Html.ActionLink("Back to List", "Index") %>
  </p>
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>
