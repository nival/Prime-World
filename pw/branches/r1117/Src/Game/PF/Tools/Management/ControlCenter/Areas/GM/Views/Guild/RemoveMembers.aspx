<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.GM.Models.GuildRemoveMembersModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
RemoveMembers
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
  <style type="text/css">
    table, table td {
      border: 0px;
    }
  </style>
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <h2>Remove members from guild "<%= Html.Encode(Model.FullName) %>"</h2>
  <% using (Html.BeginForm()) {%>
  <%= Html.ValidationSummary(true) %>
  <fieldset>
    <%= Html.HiddenFor(m => m.GuildId) %>
    <%= Html.HiddenFor(m => m.FullName) %>
    <legend>Select members to delete</legend>
    <table>
      <% foreach (var member in Model.Members) { %>
        <tr>
          <td><%= String.Format("{0} (auid={1})", Html.Encode(member.Nickname), member.Auid) %></td>
          <td><input type="checkbox" name="RemoveMembers" value="<%= member.Auid %>" /></td>
        </tr>
      <% } %>
    </table>
    <p>
      <input type="submit" value="Save" />
    </p>
  </fieldset>
  <% } %>
  
  <div>
    <%= Html.ActionLink("Cancel", "Details", new { id = Model.GuildId }) %>
  </div>
</asp:Content>
