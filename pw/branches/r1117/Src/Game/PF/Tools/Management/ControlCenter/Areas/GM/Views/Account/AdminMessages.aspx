<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<IEnumerable<AdminMessageInfoModel>>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	Admin Messages History
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
      <%= Html.ActionLink("Back to account details", "Details", "Account", new { login = ViewData["login"], auid = ViewData["auid"] }, new { })%>
    </p>
  </div>
  <div id="pagecontent" style="width: 70%">
    <h2>Administration messages history for account <%= ViewData["login"] ?? String.Format("(auid = {0})", ViewData["auid"]) %></h2>
    <table>
      <tr>
        <th>Title</th>
        <th>Text</th>
        <th>GMLogin</th>
        <th><label class="timeZoneLabel">DateTime, utc+0</label></th>
      </tr>
      <% foreach (var item in Model) { %>
      <tr>
        <td><%= Html.Encode(item.MessageTitle) %></td>
        <td><%= Html.Encode(item.MessageText) %></td>
        <td><%= Html.Encode(item.GMLogin) %></td>
        <td class="utcdateText"><%= Html.Encode( item.Timestamp.ToString( "dd'.'MM'.'yyyy HH:mm:ss" ) )%></td>
      </tr>
      <% }  %>
    </table>
    <div class="pager">
      Page :
      <%= Html.PageLinks( (int)ViewData["CurrentPage"], (int)ViewData["TotalPages"], x => Url.Action( "AdminMessages", new { pageNum = x, auid = ViewData["auid"], login = ViewData["login"] } ) )%>
    </div>
  </div>
</asp:Content>
