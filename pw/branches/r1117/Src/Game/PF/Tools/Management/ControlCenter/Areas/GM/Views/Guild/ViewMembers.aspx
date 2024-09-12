<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.GM.Models.GuildInfoModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
Members
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <h2>Edit members for guild "<%= Html.Encode(Model.FullName)%>"</h2>  
    <table>
      <tr>
        <th>Auid</th>
        <th>Nickname</th>
        <th>IsOfficer</th>
        <th>Added talents amount (Guild Bank add limit = <%= Model.GuildBankAddLimit %>)</th>
        <th>Taken talents amount (Guild Bank take limit = <%= Model.GuildBankTakeLimit %>)</th>
      </tr>
      <% foreach (var member in Model.Members.OrderByDescending(m => m.IsOfficer)) { %>
        <tr>
          <td><%= Html.Encode(member.Auid) %></td>
          <td><%= Html.Encode(member.Nickname) %></td>
          <td><%= Html.Encode(member.IsOfficer) %></td>
          <td><%= Html.Encode(member.AddedTalentsDailyCount) %></td>
          <td><%= Html.Encode(member.TakenTalentsDailyCount) %></td>
          <% if ( ( (GMToolsPrincipal)User ).HasPermission( "GM_AccountEdit" ) )
           { %>
        <td>
          <%= Html.ActionLink("edit", "EditMember", new { Model.GuildId, member.Auid })%>
        </td>
           <% } %>
        </tr>
      <% } %>
    </table> 
  <div>
    <%= Html.ActionLink("Cancel", "Details", new { id = Model.GuildId }) %>
  </div>
  
</asp:Content>