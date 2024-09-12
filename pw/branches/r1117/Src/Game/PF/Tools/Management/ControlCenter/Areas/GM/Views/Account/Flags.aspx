<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<List<FlagModel>>" %>

<%@ Import Namespace="ControlCenter.Areas.GM.Models" %>
<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
  Paid Flags
</asp:Content>
<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">
</asp:Content>
<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">
  <div id="pagemenu" style="width: 30%; float: right; margin-right: 0px">
    <p>
      <%= Html.ActionLink("Back to account details", "Details", new { login = ViewData["login"] })%></p>
  </div>
  <div id="pagecontent" style="width: 70%">
    <h2>
      Flags info</h2>
    <div style="font-size: 1.2em; color: #000000; margin-bottom: 15px;">
      <%= Html.Encode( String.Format( "Account: {0}", ViewData["login"] ) )%>
    </div>
    <table>
      <tr>
        <th>
          <%= Html.Label( "PersistentId" )%>
        </th>
        <th>
          <%= Html.Label("Price")%>
        </th>
      </tr>
      <% foreach ( var item in Model )
         { %>
      <tr>
        <td>
          <%= Html.Encode(item.FlagPersistentId)%>
        </td>
        <td>
          <%= Html.Encode(item.FlagPrice)%>
        </td>
        <% if (((GMToolsPrincipal)User).HasPermission("GM_AccountEdit")) { %>
          <td>
            <%= Html.ActionLink("lock flag", "LockFlag", new { login = ViewData["login"], flagPersistentId = item.FlagPersistentId }, new { @class = "link-delete" })%>
          </td>
        <% } %>
      </tr>
      <% } %>
    </table>
    <% using ( Html.BeginForm() )
       { %>
        <% if (((GMToolsPrincipal)User).HasPermission("GM_AccountEdit")) { %>
          <p>
            <input type="submit" value="Unlock flag " />
            <%= Html.DropDownList( "selPaidFlag" )%>
          </p>
        <% } %>    
    <% } %>
    <% using ( Html.BeginForm() )
       { %>
        <% if (((GMToolsPrincipal)User).HasPermission("GM_AccountEdit")) { %>
          <p>
            <input type="submit" value="Unlock administration flag " />
            <%= Html.DropDownList( "selAdminFlag" )%>
          </p>
        <% } %>    
    <% } %>
  </div>
</asp:Content>
