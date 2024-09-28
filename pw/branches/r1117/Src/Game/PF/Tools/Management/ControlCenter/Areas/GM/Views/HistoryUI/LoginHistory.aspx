<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<IEnumerable<ControlCenter.Areas.GM.Models.LoginInfoModel>>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
  LoginHistory
</asp:Content>

<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">
  <link rel="stylesheet" href="/Content/pager.css" />
  <script type="text/javascript" src="../../Scripts/jquery.localizeDate.js"></script>
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <script type="text/javascript">
    $(document).ready(function() {
      localizeDate();
    });
  </script>

  <div id="pagemenu" style="width: 30%; float: right; margin-right: 0px">
    <p>
      <%= Html.ActionLink( "Back to account details", "Details", "Account", new { login = ViewData["login"] }, new { } )%></p>
  </div>
  <div id="pagecontent" style="width: 70%">
    <h2>Login history for account <%= ViewData["login"] %></h2>
    <table>
      <tr>
        <th>SocialSessionId</th>
        <th>PlayerIp</th>
        <th>Cluster</th>
        <th><label class="timeZoneLabel">LoginTime, utc+0</label></th>
        <th><label class="timeZoneLabel">LogoutTime, utc+0</label></th>
      </tr>
      <% foreach (var item in Model)
         { %>
      <tr>
        <td><%= Html.Encode(item.SocialSessionId) %></td>
        <td><%= Html.Encode(item.PlayerIp) %></td>
        <td><%= Html.Encode(item.Cluster) %></td>
        <td class="utcdateText"><%= Html.Encode( item.LoginTime.ToString( "dd'.'MM'.'yyyy HH:mm:ss" ) ) %></td>
        <td class="utcdateText"><% if ( item.LogoutTime.HasValue ) { %><%= Html.Encode( ((DateTime)item.LogoutTime).ToString( "dd'.'MM'.'yyyy HH:mm:ss" ) )%><% } %></td>
      </tr>
      <% }  %>
    </table>
    <div class="pager">
      Page :
      <%= Html.PageLinks( (int)ViewData["CurrentPage"], (int)ViewData["TotalPages"], x => Url.Action( "LoginHistory", new { pageNum = x, auid = ViewData["auid"], login = ViewData["login"] } ) )%>
    </div>
  </div>
</asp:Content>