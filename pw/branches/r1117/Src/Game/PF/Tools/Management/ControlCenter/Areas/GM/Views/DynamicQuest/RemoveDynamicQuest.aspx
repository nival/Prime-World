<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<RemoveDynamicQuestModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	RemoveDynamicQuest
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

    <h2>RemoveDynamicQuest</h2>
    <p><%=Html.ActionLink("Back to list", "Overview", "DynamicQuest")%></p>
    <% if (Model.Message == null) 
    {%>
        <p>Are you sure you want to remove selected quest?</p>
        <% using (Html.BeginForm())
        { %>
            <%= Html.HiddenFor(model => model.Locale) %>
            <%= Html.HiddenFor(model => model.QuestId)%>
            <table>
            <tr>
                <th>Quest name</th>
                <th>Start date</th>
                <th>End date</th>
            </tr>
            <tr>
                <td><%= Html.Label(Model.QuestName)%></td>
                <td><%= Html.Label(Model.QuestStartTime)%></td>
                <td><%= Html.Label(Model.QuestEndTime)%></td>                
            </tr>
            </table>
            <p style="margin-top: 30px">
                <input type="submit" value="Remove" />
            </p>
        <% } %>
     <% } 
       else
       {%> 
         <%= Html.Label(Model.Message)%>
     <%  }%>

</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>
