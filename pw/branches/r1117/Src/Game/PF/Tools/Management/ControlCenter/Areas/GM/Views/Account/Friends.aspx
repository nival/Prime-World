<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<IEnumerable<FriendInfoModel>>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	Friends
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    
  <div id="pagemenu" style="width: 30%; float: right; margin-right: 0px">
    <p><%= Html.ActionLink( "Back to account details", "Details", new { auid = ViewData["auid"] } )%></p>
  </div>
  
  <div id="pagecontent" style="width: 70%">
    <h2>Friends</h2>

    <% using ( Html.BeginForm( "Friends", "Account", new { auid = ViewData["auid"] }, FormMethod.Post, new { id = "theform" } ) ) { %>
    <div style="font-size: 1.2em; color: #000000; margin-bottom: 15px;">
      <%= Html.Encode( String.Format( "Account: {0}", ViewData["auid"] ) )%>
    </div>
    
    <table id="friends">
      <thead>
        <tr>
          <% if (((GMToolsPrincipal) User).HasPermission("GM_AccountEdit")) { %>
            <th><input type="checkbox" id="chkall"/></th>
          <% } %>
          <th><%= Html.LabelFor( m => m.FirstOrDefault().Auid )%></th>
          <th><%= Html.LabelFor( m => m.FirstOrDefault().GuildShortName )%></th>
          <th><%= Html.LabelFor( m => m.FirstOrDefault().Nickname )%></th>>
        </tr>
      </thead>
      <tbody>
        <% foreach (var item in Model) { %>
        <tr>
          <% if (((GMToolsPrincipal) User).HasPermission("GM_AccountEdit")) { %>
            <td><input type="checkbox" class="chkfriend" name="selected" value="<%= item.Auid %>" /></td>
          <% } %>
          <td><%= Html.Encode( item.Auid.ToString() )%></td>
          <td><%= Html.Encode( item.GuildShortName )%></td>
          <td><%= Html.Encode( item.Nickname )%></td>
          <% if (((GMToolsPrincipal) User).HasPermission("GM_AccountEdit")) { %>
            <td><%= Html.ActionLink("remove", "RemoveFriend", new { auid = ViewData["auid"], friendAuid = item.Auid }) %></td>
          <% } %>
        </tr>
        <% } %>
      </tbody>
    </table>
    
    <p><input type="submit" value="Delete selected"/></p>
  </div>
  <% } %>

</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
  <script type="text/javascript">
    $(document).ready(
      function () {
        $('#chkall').change(
          function () {
            $('#friends td :checkbox:visible').attr('checked', this.checked);
          });        

      });
  </script>
</asp:Content>
