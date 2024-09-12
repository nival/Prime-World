<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<IEnumerable<GMOperationInfoModel>>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
GM operations history
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
      <%= Html.ActionLink( "Back to account details", "Details", "Account", new { auid = ViewData["auid"] }, new { } )%>
    </p>
  </div>
  <div id="pagecontent" style="width: 70%">
    <h2>GM operations for auid = <%= ViewData["auid"] %></h2>
    <table>
      <tr>
        <th><label class="timeZoneLabel">DateTime, utc+0</label></th>
        <th>Operation</th>
        <th>Details</th>
        <th>GmLogin</th>
      </tr>
      <% foreach (var item in Model)
         { %>
      <tr>
        <td class="utcdateText"><%= Html.Encode(item.Timestamp.ToString( "dd'.'MM'.'yyyy HH:mm:ss" ) ) %></td>
        <td><%= Html.Encode(item.Type) %></td>
        <td><%= Html.Encode(item.Data) %></td>
        <td><%= Html.Encode(item.GMLogin) %></td>
      </tr>
      <% }  %>
    </table>
    <div class="pager">
      Page : <%= Html.PageLinks( (int)ViewData["CurrentPage"], (int)ViewData["TotalPages"], x => Url.Action( "GMOperationsHistory", new { pageNum = x, login = ViewData["login"], auid = ViewData["auid"] } ) )%>
    </div>
  </div>
</asp:Content>
