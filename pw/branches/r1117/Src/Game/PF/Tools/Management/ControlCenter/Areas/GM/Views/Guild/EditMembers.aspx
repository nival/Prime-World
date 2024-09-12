<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.GM.Models.GuildInfoModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
Members
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <h2>Edit members for guild "<%= Html.Encode(Model.FullName)%>"</h2>
  
  <% using (Html.BeginForm()) {%>
  <%= Html.ValidationSummary(true) %>
    <%= Html.HiddenFor(model => model.GuildId) %>

    <table>
      <tr>
        <th>Auid</th>
        <th>Nickname</th>
        <th>IsOfficer</th>
        
      </tr>
      <% foreach (var member in Model.Members.OrderByDescending(m => m.IsOfficer)) { %>
        <tr>
          <td><%= Html.Encode(member.Auid) %></td>
          <td><%= Html.Encode(member.Nickname) %></td>
          <td>
            <% if (member.IsOfficer) { %>
              <input type="checkbox" name="chkOfficers" value="<%= member.Auid %>" checked="checked" />
              <input type="hidden" name="originalOfficers" value="<%= member.Auid %>"/>
            <% } else { %>
              <input type="checkbox" name="chkOfficers" value="<%= member.Auid %>" />
            <% } %>
          </td>
        </tr>
      <% } %>
    </table>
    <p>
      <input type="submit" value="Save" />
    </p>
  
  <div>
    <%= Html.ActionLink("Cancel", "Details", new { id = Model.GuildId }) %>
  </div>
  
  <% } %>
</asp:Content>