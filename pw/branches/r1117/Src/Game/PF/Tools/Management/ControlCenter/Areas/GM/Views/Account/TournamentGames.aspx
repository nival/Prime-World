<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<IEnumerable<ControlCenter.Areas.GM.Models.TournamentGamesInfoModel>>" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
	TournamentGames
</asp:Content>

<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">
 

<div id="pagemenu" style="width: 30%; float: right; margin-right: 0px">
  <p><%= Html.ActionLink("Back to account details", "Details", new { login = ViewData["login"] })%></p>
</div>

<div id="pagecontent" style="width: 70%">
  <h2>Tournament games list (auid=<%= ViewData["login"] %>)</h2>
  
    <table>
      <tr>
        <th>
          <%= Html.LabelFor(m => m.FirstOrDefault().GameStartTime) %>
        </th>
        <th>
          <%= Html.LabelFor(m => m.FirstOrDefault().GameDuration)%>
        </th>
        <th>
          <%= Html.LabelFor(m => m.FirstOrDefault().SessionId)%>
        </th>
      </tr>
      <% foreach (var item in Model)
         { %>
        <tr>
            <td>
              <%= Html.Encode(item.GameStartTime)%>
            </td>
            <td>
              <%= Html.Encode(item.GameDuration)%>
            </td>
            <td>
              <%= Html.Encode(item.SessionId)%>
            </td>
        </tr>
      <% } %>
    </table>

</div>
</asp:Content>


