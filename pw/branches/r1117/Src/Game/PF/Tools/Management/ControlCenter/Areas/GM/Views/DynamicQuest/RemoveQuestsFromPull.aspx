<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<List<DynamicQuestShortInfoModel>>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	AddQuestsToPull
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

    <h2>Remove Quests from pull</h2>
    <% var pullId = (int)ViewData["pullId"]; %>
    <div><%=Html.ActionLink( "Back to pull", "EditQuestPull", new { pullId } )%></div>
    <% using ( Html.BeginForm( "RemoveQuestsFromPull", "DynamicQuest", new { pullId = ViewData["pullId"] }, FormMethod.Post, new { id = "theform" } ) ) { %>
    <input type="hidden" name="pullId" value="<%= ViewData["pullId"] %>"/>
    <table id="quests">
        <tr>
          <% if (((GMToolsPrincipal) User).HasPermission("GM_AccountEdit")) { %>
            <th><input type="checkbox" id="chkall"/></th>
          <% } %>
          <th><%= Html.LabelFor( m => m.FirstOrDefault().QuestId )%></th>
          <th><%= Html.LabelFor( m => m.FirstOrDefault().QuestName )%></th>
        </tr>
      <tbody>
        <% foreach (var item in Model) { %>
        <tr>
          <% if (((GMToolsPrincipal) User).HasPermission("GM_AccountEdit")) { %>
            <td><input type="checkbox" class="chktalent" name="selected" value="<%= item.QuestId %>" /></td>
          <% } %>
          <td><%= Html.Encode( item.QuestId )%></td>
          <td><%= Html.Encode( item.QuestName )%></td>          
        </tr>
        <% } %>
      </tbody>
    </table>
    
    <p><input type="submit" value="Remove selected"/></p>
  <% } %>

</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>
