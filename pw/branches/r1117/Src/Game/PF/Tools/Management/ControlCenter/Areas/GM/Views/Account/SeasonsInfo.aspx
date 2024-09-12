<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<IEnumerable<SeasonInfoModel>>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	SeasonsInfo
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    
  <div style="font-size: 1.2em; color: #000000; margin-bottom: 15px;">
    <p><%= Html.Encode(String.Format("Edit Seasons Info, Account: {0}, Hero: {1}", ViewData["login"], ViewData["heroName"]))%></p>
  </div>
  
  <div id="pagecontent" style="width: 70%">
    <% using ( Html.BeginForm( "EditSeasonInfo", "Account", new { auid = ViewData["auid"] }, FormMethod.Post, new { id = "theform" } ) ) { %>   
    
    <table id="friends">
      <thead>
        <tr>
          <th align = "right" width="5%">SeasonName</th>
          <th align = "center" width="30%">Season Dates, utc+3</th>
          <th align = "center" width="10%"><%= Html.LabelFor(m => m.FirstOrDefault().SeasonRating)%></th>
          <th align = "center" width="10%"><%= Html.LabelFor(m => m.FirstOrDefault().LeagueIndex)%></th>
          <th align = "center" width="10%"><%= Html.LabelFor( m => m.FirstOrDefault().CurLeaguePlace )%></th>
          <th align = "center" width="10%"><%= Html.LabelFor( m => m.FirstOrDefault().BestLeaguePlace )%></th>
        </tr>
      </thead>
      <tbody>
        <% foreach (var item in Model) { %>
        <tr>
          <td class="display-label"> <%= Html.Encode( item.SeasonName )%></td>
          <% if (item.StartDate != null)
           { %>
             <td class="display-label" align = "left"> 
                <label class="utcdateText display-label"><%= Html.Encode(item.StartDate.Value.ToString( "dd'.'MM'.'yyyy HH:mm:ss" ) )%></label> - 
                <label class="utcdateText display-label"><%= Html.Encode(item.EndDate.Value.ToString("dd'.'MM'.'yyyy HH:mm:ss"))%></label> </td>
            <% }
               else
               { %>
                 <td class="display-label">0 - <%= Html.Encode(item.EndDate.Value.ToString("dd'.'MM'.'yyyy HH:mm:ss"))%></td>
            <% } %>   
            <td class="display-label" align = "right"> <%= Html.Encode(item.SeasonRating)%></td>  
            <td class="display-label" align = "right"> <%= Html.Encode(item.LeagueIndex)%></td>  
         <% if (item.CurLeaguePlace > 0)
           { %>
            <td class="display-label" align = "right"> <%= Html.Encode(item.CurLeaguePlace)%></td>
        <% }
           else
           { %>
             <td class="display-label"> </td>
        <% } %>
        <% if (item.BestLeaguePlace > 0)
           { %>
            <td class="display-label" align = "right"> <%= Html.Encode(item.BestLeaguePlace)%></td>
        <% }
           else
           { %>
             <td class="display-label"> </td>
        <% } %>
        <% if (((GMToolsPrincipal)User).HasPermission("GM_AccountEdit")) { %>
          <td>
            <%= Html.ActionLink("edit", "EditSeasonInfo", new
{
    login = ViewData["login"],
    heroInstanceId = ViewData["heroInstanceId"],
    heroName = ViewData["heroName"],
                                                                  SeasonId = item.SeasonId,
                                                                  SeasonName = item.SeasonName,
                                                                  StartDate = item.StartDate,
                                                        SeasonRating = item.SeasonRating,
                                                        LeagueIndex = item.LeagueIndex,
                                                        BestLeaguePlace = item.BestLeaguePlace
})%>
          </td>
        <% } %>
        </tr>
        <% } %>
      </tbody>
    </table>
  </div>
  <% } %>

  <p>
      <%= Html.ActionLink("back to hero list", "Heroes", new { login = ViewData["login"] })%>
    </p>
</asp:Content>

