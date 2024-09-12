<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.Admin.Models.UserInfoModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
  My profile
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <h2>My profile</h2>
  
  <table>
    <tr>
      <td><span class="display-label">UserName</span></td>
      <td><span class="display-field" style="font-weight:bold; font-size:120%"><%= Html.Encode(Model.UserName) %></span></td>
    </tr>
    <tr>
      <td><span class="display-label">FullName</span></td>
      <td><span class="display-field" style="font-weight:bold; font-size:120%"><%= Html.Encode(Model.FullName)%></span></td>
    </tr>
    <tr>
      <td><span class="display-label">Email</span></td>
      <td><span class="display-field" style="font-weight:bold; font-size:120%"><%= Html.Encode(Model.Email)%></span></td>
    </tr>
    <tr>
      <td><span class="display-label">Superuser</span></td>
      <td><span class="display-field" style="font-weight:bold; font-size:120%"><%= Model.Superuser ? "Y" : "N" %></span></td>
    </tr>
  </table>

  <table style="margin-top: 20px">
    <tr>
      <td width="150">Member of roles</td>
      <td>
      <% foreach (var r in Model.Roles) { %>
         <%= Html.Encode(r.Value) %> <br />
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

  <p><%= Html.ActionLink("Change password", "ChangePassword")%></p>
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>
