<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.GM.Models.GuildTalentsListModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
FreeTalents
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <h2>Free GuildBank talents</h2>  
    <table>
      <tr>
        <th>ClassId</th>
        <th>Name</th>
        <th>Owner</th>
        <th>Points</th>
        <th>Soulbound</th>
      </tr>
      <% foreach (var talent in Model.Talents.OrderByDescending(m => m.Name))
         { %>
        <tr>
          <td><%= Html.Encode(talent.PersistentId) %></td>
          <td><%= Html.Encode(talent.Name) %></td>
          <td><%= Html.Encode(talent.OwnerAuid) %></td>
          <td><%= Html.Encode(talent.Points) %></td>
          <td><%= Html.Encode(talent.HeroClassId) %></td>
          <td><%= Html.ActionLink("Return to owner", "ReturnTalentToOwner", new { guildid = Model.GuildId, talentInstanceId = talent.InstanceId }, new { @class = "link-delete" })%></td>
        </tr>
      <% } %>
    </table> 
  <div>
    <%= Html.ActionLink("Back", "Details", new { id = Model.GuildId }) %>
  </div>
  
</asp:Content>