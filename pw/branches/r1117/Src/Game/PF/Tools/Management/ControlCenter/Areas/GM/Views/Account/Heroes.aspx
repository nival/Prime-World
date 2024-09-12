<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<IEnumerable<HeroInfoModel>>" %>

<%@ Import Namespace="ControlCenter.Areas.GM.Models" %>
<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
  Heroes
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
      Heroes info</h2>
    <% using ( Html.BeginForm() )
       { %>
    <div style="font-size: 1.2em; color: #000000; margin-bottom: 15px;">
      <%= Html.Encode( String.Format( "Account: {0}", ViewData["login"] ) )%>
    </div>
    <table>
      <tr>
        <th>
          <%= Html.LabelFor( m => m.FirstOrDefault().HeroName )%>
        </th>
        <th>
          <%= Html.LabelFor( m => m.FirstOrDefault().Experience )%>
        </th>
        <th>
          <%= Html.LabelFor( m => m.FirstOrDefault().Rating )%>
        </th>
        <th>
          <%= Html.LabelFor( m => m.FirstOrDefault().EpicWins )%>
        </th>
      </tr>
      <% foreach ( var item in Model )
         { %>
      <tr>
        <td>
          <%= Html.Encode( item.HeroName )%>
        </td>
        <td>
          <%= Html.Encode( item.Experience )%>
        </td>
        <td>
          <%= Html.Encode( item.Rating )%>
        </td>
        <td>
          <%= Html.Encode( item.EpicWins )%>
        </td>
        <td>
          <%= Html.ActionLink( "talents", "TalentSet", new { login = ViewData["login"], HeroClassId = item.HeroClassId, HeroInstanceId = item.HeroInstanceId, heroName = item.HeroName } )%>
        </td>

        <td>
          <%= Html.ActionLink("seasons", "SeasonsInfo", new { login = ViewData["login"], HeroClassId = item.HeroClassId, HeroInstanceId = item.HeroInstanceId, heroName = item.HeroName })%>
        </td>

        <% if (((GMToolsPrincipal)User).HasPermission("GM_AccountEdit")) { %>
          <td>
            <%= Html.ActionLink( "edit", "EditHero", new { HeroClassId = item.HeroClassId, HeroInstanceId = item.HeroInstanceId, HeroName = item.HeroName, Experience = item.Experience, Rating = item.Rating, EpicWins = item.EpicWins, login = ViewData["login"], } )%>
          </td>
          <td>
            <%= Html.ActionLink( "lock hero", "LockHero", new { login = ViewData["login"], HeroClassId = item.HeroClassId, HeroInstanceId = item.HeroInstanceId }, new { @class = "link-delete" } )%>
          </td>
        <% } %>

      </tr>
      <% } %>
    </table>

    <% if (((GMToolsPrincipal)User).HasPermission("GM_AccountEdit")) { %>
      <p>
        <input type="submit" value="Unlock hero " />
        <%= Html.DropDownList( "selClassHero" )%>
        <%= Html.ActionLink( "refresh", "RefreshHeroesCatalog", new { login = ViewData["login"] } )%>
      </p>
    <% } %>
    
    <% } %>
  </div>
</asp:Content>
