<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<RoleInfoModel>" %>
<%@ Import Namespace="ControlCenter.Areas.Admin.Models"%>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
  RoleDetails
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <h2>RoleDetails</h2>
  
  <fieldset>
    <legend>Fields</legend>
    
    <table>
      <tr>
        <td><span class="display-label"><%= Html.LabelFor(m => m.RoleName) %></span></td>
        <td><span class="display-field"><%= Html.Encode(Model.RoleName) %></span></td>
      </tr>
      <tr>
        <td><span class="display-label"><%= Html.LabelFor(m => m.Description) %></span></td>
        <td><span class="display-field"><%= Html.Encode(Model.Description) %></span></td>
      </tr>
      <tr>
        <td><span class="display-label"><%= Html.LabelFor(m => m.Locale) %></span></td>
        <td><span class="display-field"><%= Html.Encode(Model.Locale) %></span></td>
      </tr>
      <tr>
        <td><span class="display-label"><%= Html.LabelFor(m => m.Muid) %></span></td>
        <td><span class="display-field"><%= Html.Encode(Model.Muid) %></span></td>
      </tr>
    </table>
    
    <table style="margin-top: 20px">
      <tr>
        <td width="150">Role permissions</td>
        <td>
        <% foreach (var r in Model.Permissions) { %>
           <%= Html.Encode(r.Value) %> <br />
        <% } %>
        </td>
      </tr>
    </table>
    
    <table style="margin-top: 20px">
      <tr>
        <td width="150">Role members</td>
        <td>
        <% foreach (var r in Model.Users) { %>
           <%= Html.ActionLink(r.Value, "Details", "Users", new { id = r.Key }, null)%> <br />
        <% } %>
        </td>
      </tr>
    </table>
    
  </fieldset>
  <p>
    <%= Html.ActionLink("Edit", "Edit", new { id=Model.RoleId }) %> |
    <%= Html.ActionLink("Edit Members", "Members", new { id=Model.RoleId }) %> |
    <%= Html.ActionLink("Back to List", "Index") %>
  </p>
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>
