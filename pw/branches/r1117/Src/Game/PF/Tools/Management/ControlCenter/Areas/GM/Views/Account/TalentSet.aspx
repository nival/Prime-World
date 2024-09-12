<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<IEnumerable<TalentInfoModel>>" %>

<%@ Import Namespace="ControlCenter.Areas.GM.Models" %>
<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
  TalentSet
</asp:Content>
<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">
  <div id="pagemenu" style="width: 30%; float: right; margin-right: 0px">
    <p>
      <%= Html.ActionLink("back to hero list", "Heroes", new { login = ViewData["login"] })%>
    </p>
    <p>
      <%= Html.ActionLink("to library", "Library", new { login = ViewData["login"] })%>
    </p>
  </div>
  <div id="pagecontent" style="width: 70%">
    <h2>
      Talent Set</h2>
    <div style="font-size: 1.2em; color: #000000; margin-bottom: 15px;">
      <%= Html.Encode( String.Format( "Account : {0}, Hero : {1}", ViewData["login"], ViewData["heroName"] ) )%>
    </div>
    <table>
      <tr>
        <th>
          <%= Html.LabelFor(m => m.FirstOrDefault().TalentClassId) %>
        </th>
        <th>
          <%= Html.LabelFor(m => m.FirstOrDefault().TalentName)%>
        </th>
        <th>
          <%= Html.LabelFor(m => m.FirstOrDefault().RefineRate)%>
        </th>
        <th>
          <%= Html.LabelFor(m => m.FirstOrDefault().BoundHeroClassName)%>
        </th>
        <th>TalentSet1</th>
        <th>TalentSet2</th>
        <th>TalentSet3</th>
      </tr>
      <% foreach ( var item in Model )
         { %>
      <tr>
        <td>
          <%= Html.Encode(item.TalentClassId) %>
        </td>
        <td>
          <%= Html.Encode(item.TalentName) %>
        </td>
        <td>
          <%= Html.Encode(item.RefineRate) %>
        </td>
        <td>
          <%= Html.Encode(item.BoundHeroClassName) %>
        </td>
        <td>
          <% if (item.TalentSets[0]) { %>             
               <%= Html.ActionLink( "remove from set", "RemoveFromSet", new { login = ViewData["login"], heroInstanceId = ViewData["heroInstanceId"], TalentInstanceId = item.TalentInstanceId, talentSetId = 0, heroName = ViewData["heroName"] } )%>
            <% } %>
        </td>
        <td>
          <% if (item.TalentSets[1]) { %>             
               <%= Html.ActionLink( "remove from set", "RemoveFromSet", new { login = ViewData["login"], heroInstanceId = ViewData["heroInstanceId"], TalentInstanceId = item.TalentInstanceId, talentSetId = 1, heroName = ViewData["heroName"] } )%>
            <% } %>
        </td>
        <td>
          <% if (item.TalentSets[2]) { %>             
               <%= Html.ActionLink( "remove from set", "RemoveFromSet", new { login = ViewData["login"], heroInstanceId = ViewData["heroInstanceId"], TalentInstanceId = item.TalentInstanceId, talentSetId = 2, heroName = ViewData["heroName"] } )%>
            <% } %>
        </td>
        <td>
          <%= Html.ActionLink( "edit", "EditTalent", new { login = ViewData["login"], item.TalentInstanceId, cameFrom = "TalentSet", heroInstanceId = ViewData["heroInstanceId"], heroName = ViewData["heroName"] } )%>
        </td>
        <td>
          <%= Html.ActionLink( "move to library", "MoveSetToLib", new { login = ViewData["login"], heroInstanceId = ViewData["heroInstanceId"], TalentInstanceId = item.TalentInstanceId, heroName = ViewData["heroName"] } )%>
        </td>
      </tr>
    <% } %>
    </table>
  </div>
</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>
