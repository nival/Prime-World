<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<IEnumerable<ControlCenter.Areas.GM.Models.QuestInfoModel>>" %>
<%@ Import Namespace="AccountLib" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
  Quests
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  
<div id="pagemenu" style="width: 30%; float: right; margin-right: 0px">
  <p><%= Html.ActionLink("Back to account details", "Details", new { auid = ViewData["auid"] })%></p>
</div>

<div id="pagecontent" style="width: 70%">
  <h2>Quests for player (auid=<%= Html.Encode(ViewData["auid"]) %>)</h2>

  <table>
    <tr>
      <th><%= Html.LabelFor(m => m.FirstOrDefault().Name) %></th>
      <th><%= Html.LabelFor(m => m.FirstOrDefault().Desc) %></th>
      <th><%= Html.LabelFor(m => m.FirstOrDefault().Status) %></th>
    </tr>
    <% foreach (var item in Model.Where(m => m.Status != QuestStatus.NotIssued).OrderBy(m => m.Status)) { %>
    <tr>
      <td><%= Html.Encode(item.Name) %></td>
      <td><%= Html.Encode(item.Desc) %></td>
      <td><%= Html.Encode(item.Status) %></td>

      <% if (((GMToolsPrincipal)User).HasPermission("GM_AccountEdit")) { %>
        <td>
          <% if (item.Status == QuestStatus.New) { %>
            <%= Html.ActionLink(QuestChangeAction.Accept.ToString(), "QuestChange", new { item.Auid, item.QuestId, act = QuestChangeAction.Accept.ToString() })%> |
          <% } %>
          
          <% if (item.Status == QuestStatus.New || item.Status == QuestStatus.Accepted) { %>
            <%= Html.ActionLink(QuestChangeAction.Complete.ToString(), "QuestChange", new { item.Auid, item.QuestId, act = QuestChangeAction.Complete.ToString() })%> |
          <% } %>

          <%= Html.ActionLink(QuestChangeAction.Delete.ToString(), "QuestChange", new { item.Auid, item.QuestId, act = QuestChangeAction.Delete.ToString() })%>
        </td>
      <% } %>

    </tr>
    <% } %>
  </table>
  

  <% if (((GMToolsPrincipal)User).HasPermission("GM_AccountEdit") && Model.Any(m => m.Status == QuestStatus.NotIssued)) { %>

    <br>
    <h4>Not issued quests</h4>
    <table>
      <tr>
        <th><%= Html.LabelFor(m => m.FirstOrDefault().Name) %></th>
        <th><%= Html.LabelFor(m => m.FirstOrDefault().Desc) %></th>
        <th><%= Html.LabelFor(m => m.FirstOrDefault().Status) %></th>
      </tr>
      <% foreach (var item in Model.Where(m => m.Status == QuestStatus.NotIssued).OrderBy(m => m.Name)) { %>
      <tr>
        <td><%= Html.Encode(item.Name) %></td>
        <td><%= Html.Encode(item.Desc) %></td>
        <td><%= Html.Encode(item.Status) %></td>
        <td><%= Html.ActionLink(QuestChangeAction.Add.ToString(), "QuestChange", new { item.Auid, item.QuestId, act = QuestChangeAction.Add.ToString() })%></td>
      </tr>
      <% } %>
    </table>
    
  <% } %>
</div>
</asp:Content>
