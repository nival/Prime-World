<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<List<DynamicQuestPullModel>>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	Quest pulls
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

    <h2>Quest pulls</h2>

    <div><%=Html.ActionLink("DynamicQuests overview", "Overview", "DynamicQuest")%></div>
    <div><%=Html.ActionLink("Add new pull", "AddQuestPull")%></div>
    <% using ( Html.BeginForm() )
       { %>
    <table>
      <tr>
        <th>
          <%= Html.LabelFor( m => m.FirstOrDefault().PullId )%>
        </th>
        <th>
          <%= Html.LabelFor( m => m.FirstOrDefault().Locale )%>
        </th>
        <th>
          <%= Html.LabelFor( m => m.FirstOrDefault().RotationStartTime )%>
        </th>
        <th>
          <%= Html.LabelFor( m => m.FirstOrDefault().RotationEndTime )%>
        </th>
        <th>
          <%= Html.LabelFor( m => m.FirstOrDefault().Quests )%>
        </th>
        <th>
          <%= Html.LabelFor( m => m.FirstOrDefault().HasRotation )%>
        </th>
        <th>
          <%= Html.LabelFor( m => m.FirstOrDefault().IsWorking )%>
        </th>
      </tr>
      <% foreach ( var item in Model )
         { %>
      <tr>
        <td>
          <%= Html.Encode( item.PullId )%>
        </td>
        <td>
          <%= Html.Encode( item.Locale )%>
        </td>
        <td>
          <%= Html.Encode( item.RotationStartTime )%>
        </td>
        <td>
          <%= Html.Encode( item.RotationEndTime )%>
        </td>
        <td>
          <%= Html.Encode( item.GetQuests() )%>
        </td>
        <td>
          <%= Html.Encode( item.HasRotation )%>
        </td>
        <td>
          <%= Html.Encode( item.IsWorking )%>
        </td>

        <% if (((GMToolsPrincipal)User).HasPermission("GM_DynamicQuests")) { %>
          <td>
            <%= Html.ActionLink( "edit", "EditQuestPull", new { item.PullId} )%>
          </td>
          <td>
            <%= Html.ActionLink( "remove", "RemoveQuestPull", new { pullId = item.PullId, locale = item.Locale }, new { @class = "link-delete" } )%>
          </td>
        <% } %>

      </tr>
      <% } %>
    </table>
    <% } %>
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>
