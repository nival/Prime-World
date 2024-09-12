<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.GM.Models.GuildInfoModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
  View guild info
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
  <style type="text/css">
    p { margin: 6px 0 10px 10px }
    .display-label { text-align: left; width: 200px;}
    .display-field { font-weight: bold; width: 200px;}
  </style>
</asp:Content>


<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

<div id="pagemenu" style="width: 30%; float: right; margin-right: 0">
  <% var gmUser = (GMToolsPrincipal) User; %>
  
  <%if (gmUser.HasPermission("GM_AccountEdit")) {%>
    <p><%= Html.ActionLink( "Edit guild info", "Edit", new { id = Model.GuildId } )%></p>
    <p><%= Html.ActionLink( "Change Leader", "ChangeLeader", new { id = Model.GuildId } )%></p>
    <% if (Model.Members != null && Model.Members.Count > 0) { %>
      <p><%= Html.ActionLink( "Edit members", "ViewMembers", new { id = Model.GuildId } )%></p>
      <p><%= Html.ActionLink( "Remove members", "RemoveMembers", new { id = Model.GuildId } )%></p>
    <% } %>
    <p><%= Html.ActionLink( "Set icon", "SetIcon", new { id = Model.GuildId } )%></p>
    <p><%= Html.ActionLink( "Free guild talents", "FreeGuildBankTalents", new { id = Model.GuildId } )%></p>
    <p><%= Html.ActionLink( "Taken guild talents", "TakenGuildBankTalents", new { id = Model.GuildId } )%></p>
    <p><%= Html.ActionLink("Guild points change history", "CWGuildResourcesHistory", "HistoryUI", new { Model.GuildId }, null)%></p>
    <p><%= Html.ActionLink( "Get full guild dump", "GetFullGuildDump", new { id = Model.GuildId } )%></p>

    <% if (Model.ReleaseLockTime == null) { %>
         <p><%= Html.ActionLink("Acquire guild lock", "AcquireGuildLock", new { id = Model.GuildId })%></p>
    <% } else { %>
         <p><%= Html.ActionLink("Release guild lock", "ReleaseGuildLock", new { id = Model.GuildId })%></p>
    <% } %>
    
    <% if (Model.SiegeEndTime != null) { %>
         <p><%= Html.ActionLink("Stop guild siege", "StopGuildSiege", new { id = Model.GuildId })%></p>
    <% } %>
    
    <%if (Model.Suzerain.GuildId == 0) 
      { %>
      <p><%= Html.ActionLink("Add guild suzerain", "AddGuildSuzerain", new { guildId = Model.GuildId }) %></p>
      <% } 
      else 
      { %>
      <p><%= Html.ActionLink("Remove guild suzerain", "RemoveGuildSuzerain", new {id = Model.GuildId}) %></p>
      <% } %>
    
    <p><%= Html.ActionLink("GWEventPoolPointsHistoryToGuild", "GWEventPoolPointsHistoryToGuild", "HistoryUI", new { guildAuid = Model.GuildId }, null)%></p>
  <%}%>

</div>

<div id="pagecontent" style="width: 70%">
  <h2><%= Html.Encode(String.Format("[{0}] {1}", Model.ShortName, Model.FullName)) %> </h2>
  
  <table>
    <tr>
      <td class="display-label"> <%= Html.LabelFor(m => m.GuildId)%></td>
      <td class="display-field"> <%= Html.Encode(Model.GuildId)%></td>
    </tr>
    <tr>
      <td class="display-label"> <%= Html.LabelFor(m => m.ShortName)%></td>
      <td class="display-field"> <%= Html.Encode(Model.ShortName)%></td>
    </tr>
    <tr>
      <td class="display-label"> <%= Html.LabelFor(m => m.FullName)%></td>
      <td class="display-field"> <%= Html.Encode(Model.FullName)%></td>
    </tr>
    <tr>
      <td class="display-label"> <%= Html.LabelFor(m => m.MessageOfTheDay)%></td>
      <td class="display-field"> <%= Html.Encode(Model.MessageOfTheDay)%></td>
    </tr>
    <tr>
      <td class="display-label"> <%= Html.LabelFor(m => m.GuildExperience)%></td>
      <td class="display-field"> <%= Html.Encode(Model.GuildExperience)%></td>
    </tr>
    <tr>
      <td class="display-label"> <%= Html.LabelFor(m => m.GuildLevel)%></td>
      <td class="display-field"> <%= Html.Encode( Model.GuildLevel )%></td>
    </tr>
    <tr>
      <td class="display-label"> <%= Html.LabelFor(m => m.IconChangesCount)%></td>
      <td class="display-field"> <%= Html.Encode( Model.IconChangesCount)%></td>
    </tr>
    <tr>
      <td class="display-label"> <%= Html.LabelFor(m => m.CWPoints)%></td>
      <td class="display-field"> <%= Html.Encode(Model.CWPoints)%></td>
    </tr>
    <tr>
      <td class="display-label"> <%= Html.LabelFor(m => m.CWRating)%></td>
      <td class="display-field"> <%= Html.Encode(Model.CWRating)%></td>
    </tr>
    <% if (Model.SiegeEndTime != null)
       { %>
          <tr>
            <td class="display-label"> <%= Html.LabelFor(m => m.SiegeEndTime)%></td>
            <td class="display-field"> <%= Html.Encode(Model.SiegeEndTime)%></td>
          </tr>
    <% } %>
    <% if (Model.ReleaseLockTime != null)
       { %>
          <tr>
            <td class="display-label"> <%= Html.LabelFor(m => m.ReleaseLockTime)%></td>
            <td class="display-field"> <%= Html.Encode(Model.ReleaseLockTime)%></td>
          </tr>
    <% } %>
    <tr>
      <td class="display-label"> Leader </td>
      <td class="display-field"> 
        <%= Html.ActionLink(Model.LeaderNickname, "Details", "Account", new { auid = Model.LeaderAuid }, null) %>
        <%= String.Format(" (auid={0})", Model.LeaderAuid) %>
      </td>
    </tr>
    <% if (Model.Members != null)  {%>
      <% if (Model.Members.Any(m => m.IsOfficer)) { %>
        <tr>
          <td class="display-label">Officers</td>
          <td class="display-field">
            <% foreach (var member in Model.Members.Where(m => m.IsOfficer).OrderBy(m => m.Nickname)) { %>
              <%= Html.ActionLink(member.Nickname, "Details", "Account", new { auid = member.Auid }, null) %>
              <%= String.Format(" (auid={0})", member.Auid) %>
              <br />
            <% } %>
          </td>
        </tr>
      <% } %>
      <% if (Model.Members.Any(m => !m.IsOfficer)) { %>
        <tr>
          <td class="display-label">Members</td>
          <td class="display-field">
            <% foreach (var member in Model.Members.Where(m => !m.IsOfficer).OrderBy(m => m.Nickname)) { %>
              <%= Html.ActionLink(member.Nickname, "Details", "Account", new { auid = member.Auid }, null) %>
              <%= String.Format(" (auid={0})", member.Auid) %>
              <br />
            <% } %>
          </td>
        </tr>
      <% } %>
    <% } %>
    <% if (Model.Suzerain != null)
      {
        if (Model.Suzerain.GuildId != 0)
        { %>
          <tr>
            <td class="display-label"> Suzerain </td>
            <td class="display-field"> 
              <%= Html.ActionLink("[" + Model.Suzerain.ShortName + "] " + Model.Suzerain.FullName, "Details", "Guild",
                    new {id = Model.Suzerain.GuildId, shortname = Model.Suzerain.ShortName, fullname = Model.Suzerain.FullName}, null) %>
            </td>
          </tr>
        <% }
      } %>
    <% if (Model.Vassals != null)
       {
         if (Model.Vassals.Count > 0)
         { %>
          <tr>
            <td class="display-label">Vassals</td>
            <td class="display-field">
              <% foreach (var member in Model.Vassals.OrderBy(v => v.FullName))
                 { %>
                <%= Html.ActionLink("[" + member.ShortName + "] " + member.FullName, "Details", "Guild",
                      new {id= member.GuildId, shortname = member.ShortName, fullname = member.FullName}, null) %>
                <br />
              <% } %>
            </td>
          </tr>
        <% }
       } %>
  </table>
</div>

</asp:Content>