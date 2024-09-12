<%@ Page Title="" Language="C#" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.GM.Models.BannedIpFullListModel>" MasterPageFile="~/Views/Shared/Site.Master" %>
<%@ Import Namespace="AccountLib" %>

<asp:Content runat="server" ID="Title" ContentPlaceHolderID="TitleContent">
Banned Ip
</asp:Content>

<asp:Content runat="server" ID="Main" ContentPlaceHolderID="MainContent">
    <h2 style="color:Black">Banned Ip</h2>
    <div class="pager">
      Page :
      <%= Html.PageLinksForMongo((int)Model.Limit, (int)Model.Skip, (int) Model.Count, (l, s) => Url.Action("BannedIp", "BruteForceDefender", new { limit = l, skip = s }))%>
    </div>
    <table style="border-style: none">
    <tr>
         <th>Ip</th>
         <th>BanTime</th> 
         <th>Accounts</th>
         <th>Tryes</th> 
         <th>Action</th> 
    </tr>
    <% foreach (var info in Model.IpList)
       { %>
    <tr>
    <td class="display-field"> <%= Html.Encode( info.Ip)%></td>
    <td class="display-field"> <%= Html.Encode( info.BanTime)%></td>
    <td class="display-field"> <%= Html.Encode( info.Accounts)%></td>
    <td class="display-field"> <%= Html.Encode(info.Tryes)%></td>
    <td><%= Html.ActionLink("UnBan", "UnbanIp", "BruteForceDefender", new { ip = info.Ip }, null)%></td>
    </tr>
    
    
    <% } %>

    </table>
    <div class="pager">
      Page :
      <%= Html.PageLinksForMongo((int)Model.Limit, (int)Model.Skip, (int) Model.Count, (l, s) => Url.Action("BannedIp", "BruteForceDefender", new { limit = l, skip = s }))%>
    </div>
</asp:Content>
