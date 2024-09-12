<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<AuidListModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
  Index
</asp:Content>

<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">
    <link href="/Content/jquery-ui-1.8.17.custom.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Scripts/jquery-ui-1.8.16.custom.min.js"></script>
    <script type="text/javascript" src="/Scripts/jquery.localizeDate.js"></script>
    <script type="text/javascript" src="/Scripts/jquery-ui-timepicker-addon.js"></script>
    <script type="text/javascript" src="/Scripts/jquery-ui-sliderAccess.js"></script>
    <script type="text/javascript" src="/Scripts/CommonScripts.js"></script>
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <div class="pagemenu">
        <p><%= Html.ActionLink("Back to dynamic quests", "Overview", "DynamicQuest")%></p>
        <br/>
        <p><%= Html.ActionLink("Add", "AuidListMember", new {id = -1})%></p>
    </div>
    <div>
        <h2>Auid lists</h2>
        <table>
            <tr>
                <th>Id</th>
                <th>Name</th>
            </tr>
            <% foreach (var list in Model.Lists)
               {
                   %>
            <tr>
                <td><%=list.Index %></td>
                <td><%=list.Description %></td>
                <td><%=Html.ActionLink("Edit", "AuidListMember", new {id = list.Index}) %></td>
                <td><%=Html.ActionLink("Remove (" + list.Links +  " links)", "RemoveAuidListMember", new {id = list.Index}) %></td>
            </tr>
            <% } %>
        </table>
    </div>
    
</asp:Content>
