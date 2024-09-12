<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<AccountInfoModel>" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
  Details
</asp:Content>

<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">
  <script type="text/javascript" src="../../Scripts/jquery.localizeDate.js"></script>
</asp:Content>

<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">
  <script type="text/javascript">
    $(document).ready(function() {
      localizeDate();
    });
  </script>
  <style type="text/css">
    p { margin: 6px 0px 10px 10px }
    .display-label { text-align: left; width: 200px;}
    .display-field { font-weight: bold; width: 200px;}
    

  </style>
  
  <% var gmUser = (GMToolsPrincipal) User; %>
  
  <div id="pagemenu" style="width: 30%; float: right; margin-right: 0px">
    
    <div class = "menublock">
      <h4>More details</h4>
      <p><%= Html.ActionLink("Heroes", "Heroes", new { login = Model.Login })%></p>
      <p><%= Html.ActionLink("Library", "Library", new { login = Model.Login })%></p>
      <p><%= Html.ActionLink("Skins", "Skins", new { Model.Auid })%></p>
      <p><%= Html.ActionLink("Buildings", "Buildings", new { Model.Auid })%></p>
      <p><%= Html.ActionLink("Quests", "Quests", new { Model.Auid })%></p>
      <p><%= Html.ActionLink("All DynamicQuests", "QuestsForTalents", new { auid = Model.Auid, login = Model.Login })%></p>
      <p><%= Html.ActionLink("Geolocation", "Geolocation", new { Model.Auid })%></p>
      <p><%= Html.ActionLink("Talent Upgrade Entities", "TalentUpgradeEntities", new { Model.Auid })%></p>
    </div>
    
    <%if (gmUser.HasPermission("GM_AccountEdit")) {%>
    <div class = "menublock">
      <h4>Edit operations</h4>
      <p><%= Html.ActionLink("Edit account", "EditAccount", new { Model.Auid })%></p>
      <p><%= Html.ActionLink("Reset User", "ResetUser", new { login = Model.Login }, new { @class = "link-delete" })%></p>
      <p><%= Html.ActionLink("Give Lamp", "LampInfo", new { login = Model.Login })%></p>
      <p><%= Html.ActionLink("Give Winner Rune", "UpgradeHeroTalentsInfo", new { login = Model.Login })%></p>
      <p><%= Html.ActionLink("View tournament info", "TournamentInfo", new { login = Model.Login, auid = Model.Auid })%></p>
      <p><%= Html.ActionLink("Remove fake auid", "RemoveFakeAuid", new { login = Model.Login }, new { @class = "link-delete" })%></p>
       <%if (Model.SNid == "pwc" && Model.Email != "TODO") {%>
         <p><%= Html.ActionLink( "Activate Email", "ActivateEmail", new { login = Model.Login, email = Model.Email } )%></p>
       <%}%>
    </div>
    <%}%>
      
    <%if (gmUser.HasPermission("GM_PlayerWipe"))
      {%>
        <div class = "menublock">
            <h4>Player Wipe</h4>
            <p style="font-weight:bold;"><%= Html.ActionLink("Remove SA auid record", "DeleteSaAccount", "PlayerWipe", new { auid = Model.Auid }, null) %></p>
        </div>
    <%}%>
    
    <% if (gmUser.HasPermission("GM_AccountBanMute") || (gmUser.HasPermission("GM_AccountKick") && Model.Online && Model.CurrentSession == 0)) { %>
    <div class = "menublock">
      <h4>Ban operations</h4>
      <% if (gmUser.HasPermission("GM_AccountBanMute")) { %>
        <p><%= Html.ActionLink("Ban user", "UserOperation", new { op = "ban", Model.Auid, returnUrl = Request.Url.PathAndQuery })%></p>
        <p><%= Html.ActionLink("Mute user", "UserOperation", new { op = "mute", Model.Auid, returnUrl = Request.Url.PathAndQuery })%></p>
        <p><%= Html.ActionLink("Add leave points", "UserOperation", new { op = "SetLeave", Model.Auid, returnUrl = Request.Url.PathAndQuery })%></p>
        <p><%= Html.ActionLink("Remove leave points", "UserOperation", new { op = "SetLeave", Model.Auid, negative = true, returnUrl = Request.Url.PathAndQuery })%></p>
      <% } %>
      <% if (gmUser.HasPermission("GM_AccountKick") && Model.Online && Model.CurrentSession == 0) { %>
       <p><%= Html.ActionLink("Kick user", "KickUser", new { Model.Login })%></p>
      <% } %>
    </div>
    <% } %>
    
    <%if (gmUser.HasPermission("GM_AccountLoginHistory")) {%>
    <div class = "menublock">
      <h4>History</h4>
      <p><%= Html.ActionLink("Login history", "LoginHistory", "HistoryUI", new { auid = Model.Auid, login = Model.Login }, null)%></p>
      <p><%= Html.ActionLink("Resources/talents change history", "ResourcesHistory", "HistoryUI", new { auid = Model.Auid }, null)%></p>
      <p><%= Html.ActionLink("Guild points change history", "CWPlayerResourcesHistory", "HistoryUI", new { auid = Model.Auid }, null)%></p>
      <p><%= Html.ActionLink("GM ban and mute history", "BanAndMuteHistory", "HistoryUI", new { auid = Model.Auid, login = Model.Login }, null)%></p>
      <p><%= Html.ActionLink("GM operations history", "GMOperationsHistory", "HistoryUI", new { auid = Model.Auid }, null)%></p>
      <p><%= Html.ActionLink("Fraction change history", "FractionChangeHistory", "HistoryUI", new { auid = Model.Auid }, null)%></p>
      <p><%= Html.ActionLink("Leaver points history", "LeavePointsHistory", "HistoryUI", new { auid = Model.Auid }, null)%></p>
      <p><%= Html.ActionLink("Runes history", "RuneHistory", "HistoryUI", new { auid = Model.Auid }, null)%></p>
      <p><%= Html.ActionLink("Admin messages history", "AdminMessages", new { login = Model.Login }, null)%></p>
      <p><%= Html.ActionLink("QuestRoll CustomEvents history", "QuestEventsStepsHistory", "HistoryUI", new { auid = Model.Auid }, null)%></p>
      <%--<p><%= Html.ActionLink("GWEventPoolPointsHistory", "GWEventPoolPointsHistory", "HistoryUI", new { auid = Model.Auid }, null)%></p>--%>
    </div>
    <%}%>
    
    <%if (gmUser.HasPermission("GM_PayOperation")) {%>
    <div class = "menublock">
      <h4>Paid operations</h4>
      <p><%= Html.ActionLink("Paid nickname change", "PayEditNickname", new { login = Model.Login })%></p>
      <p><%= Html.ActionLink("Paid faction change", "PayChangeFaction", new { login = Model.Login })%></p>
      <p><%= Html.ActionLink("Purchase paid service", "PayService", new { login = Model.Login })%></p>
      <p><%= Html.ActionLink("Flags", "Flags", new { login = Model.Login })%></p>
    </div>
    <%}%>

    <div class = "menublock">
      <h4>Miscellaneous</h4>
      <%if (gmUser.HasPermission("GM_AccountSendMessage")) {%>
        <p><%= Html.ActionLink("Send message", "SendMessageUser", new { auid = Model.Auid, login = Model.Login })%></p>
      <%}%>
      <p><%= Html.ActionLink("Get full user dump", "GetFullUserDump", new { login = Model.Login })%></p>
      <p><%= Html.ActionLink("Apply full user dump", "ApplyUserDump", new { login = Model.Login })%></p>
      <p><%= Html.ActionLink("Check account validity", "CheckAccountValidity", new { login = Model.Login })%></p>
      <p><%= Html.ActionLink("Friends", "Friends", new { auid = Model.Auid })%></p>
    </div>

    <div style="margin-bottom: 60px">
      <%= Html.ActionLink("Back to the search", "Index")%>
    </div>

  </div>
  
  <div id="pagecontent" style="width: 70%">
    <h2>Details</h2>
    <div style="font-size: 1.2em; color: #000000; margin-bottom: 15px;">
      <%= Html.Encode( String.Format( "auid : {0}, snid : {1}, snuid : {2}", Model.Auid, Model.SNid, Model.SNUid ) )%>
    </div>
    
    <% if ( Model.Fraction == FractionEnum.notSelected ) { %>
      <h2 style="color: #E58300;">Не выбрана фракция</h2>
    <% } %>
    
    <div style="margin-bottom: 10px; font-weight: bold">
      <% if ( Model.Online ) { %>
        <% if (Model.CurrentSession == 0)
           { %>
             <span style="color: #009900">ONLINE</span>
        <% }
           else
           { %>
             <span style="color: #009900">IN SESSION</span>
        <% } %>
      <% } else { %>
        <span style="color: #CC0000">OFFLINE</span>
      <% } %>
    </div>

    <div style="margin: 20px 0 10px 0;">Registration info</div>

    <table style="border-style: none">
      <tr>
        <td class="display-label"> <%= Html.LabelFor(m => m.Login) %></td>
        <td class="display-field"> <%= Html.Encode(Model.Login) %></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor(m => m.NickName) %></td>
        <td class="display-field"> <%= Html.Encode(Model.NickName) %></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor(m => m.JoinedSNids) %></td>
        <td class="display-field"> <%= String.Join("<br />", Model.JoinedSNids.ToArray()) %></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor(m => m.GuildFullName) %></td>
        <td class="display-field">
          <% if (!String.IsNullOrEmpty(Model.GuildFullName)) { %>
            <%= Html.ActionLink(Model.GuildFullName, "Details", "Guild", new { id = Model.GuildId }, null) %>
          <% } %>
        </td>
      </tr>
      <% if (Model.GuildBuildingLevel != -1) { %>
        <tr>
          <td class="display-label"> <%= Html.LabelFor(m => m.GuildBuildingLevel)%></td>
          <td class="display-field"> <%= Html.Encode(Model.GuildBuildingLevel)%></td>
        </tr>
      <% } %>

      <tr>
        <td class="display-label"> <label class="timeZoneLabel">Register Date, utc+0</label></td>
        <td class="display-field">
          <label class="utcdateText display-field"><%= Html.Encode( Model.RegisterDate.Value.ToString( "dd'.'MM'.'yyyy HH:mm:ss" ) )%></label>
        </td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.Email )%></td>
        <td class="display-field"> <%= Html.Encode( Model.Email )%></td>
      </tr>
      <tr>
        <td class="display-label"> <label class="timeZoneLabel">Banned, utc+0</label></td>
        <td class="display-field"> <label class="utcdateText display-field"><%= Html.Encode( Model.Banned )%></label></td>
        <% if (gmUser.HasPermission("GM_AccountBanMute") && !String.IsNullOrEmpty(Model.Banned)) { %>
          <td style="border-style: none"><%= Html.ActionLink("Unban", "UserOperation", new { op = "unban", Model.Auid }) %></td>
        <% } %>
      </tr>
      <tr>
        <td class="display-label"> <label class="timeZoneLabel">Muted, utc+0</label></td>
        <td class="display-field"> <label class="utcdateText display-field"><%= Html.Encode( Model.Muted )%></label></td>
        <% if (gmUser.HasPermission("GM_AccountBanMute") && !String.IsNullOrEmpty(Model.Muted)) { %>
          <td style="border-style: none"><%= Html.ActionLink("Unmute", "UserOperation", new { op = "unmute", Model.Auid }) %></td>
        <% } %>
      </tr>
      <tr>
        <td class="display-label">Leaver info</td>
        <td class="display-field">
          <% if (Model.IsLeaver) { %>"Leaver"<br/><% } %>
          <% if (Model.IsBadBehaviour) { %>"Bad behaviour"<br/><% } %>
          Points: <%= Model.LeaverPoints %>
        </td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.Fame )%></td>
        <td class="display-field"> <%= Html.Encode( Model.Fame )%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.Fraction )%></td>
        <td class="display-field"> <%= Html.Encode( Model.Fraction )%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor(m => m.SwitchQuant)%></td>
        <td class="display-field"> <%= Html.Encode( Model.SwitchQuant )%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor(m => m.NickChangesQuant)%></td>
        <td class="display-field"> <%= Html.Encode( Model.NickChangesQuant )%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.Gender )%></td>
        <td class="display-field"> <%= Html.Encode( Model.Gender )%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.Location )%></td>
        <td class="display-field"> <%= Html.Encode( Model.Location )%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.Locale )%></td>
        <td class="display-field"> <%= Html.Encode( Model.Locale )%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.Muid )%></td>
        <td class="display-field"> <%= Html.Encode( Model.Muid )%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.Reliability )%></td>
        <td class="display-field"> <%= Html.Encode( Model.Reliability )%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.CurrentSession )%></td>
        <td class="display-field"> <%= Html.Encode( Model.CurrentSession )%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor(m => m.PremiumAccountDate)%></td>
        <td class="display-field"> <%= Html.Encode(Model.PremiumAccountDate)%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.LordRating )%></td>
        <td class="display-field"> <%= Html.Encode( Model.LordRating )%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.DailyRating )%></td>
        <td class="display-field"> <%= Html.Encode(Model.DailyRating)%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.NumberOfWins )%></td>
        <td class="display-field"> <%= Html.Encode( Model.NumberOfWins )%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.NumberOfWinsForPR )%></td>
        <td class="display-field"> <%= Html.Encode( Model.NumberOfWinsForPR )%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.PlayerRating )%></td>
        <td class="display-field"> <%= Html.Encode( Model.PlayerRating )%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor(m => m.PlayerRatingHeroLastPlayed)%></td>
        <td class="display-field"> <%= Html.Encode(Model.PlayerRatingHeroLastPlayed)%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor(m => m.PlayerRatingHero)%></td>
        <td class="display-field"> <%= Html.Encode(Model.PlayerRatingHero)%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.Dodges )%></td>
        <td class="display-field"> <%= Html.Encode( Model.Dodges )%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor(m => m.RetiredTime)%></td>
        <td class="display-field"> <%= Html.Encode( Model.RetiredTime )%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.IsRegularMMAllowed )%></td>
        <td class="display-field"> <%= Html.Encode(Model.IsRegularMMAllowed)%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.IsDeveloper )%></td>
        <td class="display-field"> <%= Html.Encode( Model.IsDeveloper )%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.IsSpectator )%></td>
        <td class="display-field"> <%= Html.Encode( Model.IsSpectator )%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.ExtraComplaints )%></td>
        <td class="display-field"> <%= Html.Encode( Model.ExtraComplaints )%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.ExtraSessionComplaints)%></td>
        <td class="display-field"> <%= Html.Encode(Model.ExtraSessionComplaints)%></td>
      </tr>


      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.CanMute )%></td>
        <td class="display-field"> <%= Html.Encode( Model.CanMute )%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.HasLamp )%></td>
        <td class="display-field"> <%= Html.Encode( Model.HasLamp )%></td>
      </tr>
      <tr>
        <td class="display-label"> <label class="timeZoneLabel">Last payment time, utc+0</label></td>
        <td class="display-field">
          <% if (Model.LastPaymentTime.HasValue) { %>
            <label class="utcdateText display-field"><%= Html.Encode(Model.LastPaymentTime.Value.ToString("dd'.'MM'.'yyyy HH:mm:ss")) %></label>
          <% } %>
        </td>
      </tr>
      <tr>
        <td class="display-label"> <label class="timeZoneLabel">Last lamp drop time, utc+0</label></td>
        <td class="display-field">
          <% if (Model.LastLampDropTime.HasValue) { %>
            <label class="utcdateText display-field"><%= Html.Encode(Model.LastLampDropTime.Value.ToString("dd'.'MM'.'yyyy HH:mm:ss"))%></label>
          <% } %>
        </td>
      </tr>
    </table>

    <div style="margin: 40px 0 10px 0;">Resources</div>
    <table>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.Silver )%></td>
        <td class="display-field"> <%= Html.Encode( Model.Silver )%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.Resource1 )%></td>
        <td class="display-field"> <%= Html.Encode( Model.Resource1 )%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.Resource2 )%></td>
        <td class="display-field"> <%= Html.Encode( Model.Resource2 )%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.Resource3 )%></td>
        <td class="display-field"> <%= Html.Encode( Model.Resource3 )%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.Perl )%></td>
        <td class="display-field"> <%= Html.Encode( Model.Perl )%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.RedPerl )%></td>
        <td class="display-field"> <%= Html.Encode( Model.RedPerl )%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.CWPoints )%></td>
        <td class="display-field"> <%= Html.Encode( Model.CWPoints )%></td>
      </tr>
      <tr>
        <td class="display-label"> <%= Html.LabelFor( m => m.Shard )%></td>
        <td class="display-field"> <%= Html.Encode( Model.Shard )%></td>
      </tr>
    </table>
  
  <div style="margin: 40px 0 10px 0;">Custom Currencies</div>
  <table>
      <% foreach (var currency in Model.Currencies){ %>
          <tr>
              <td class="display-label"> <%= Html.Encode( currency.Key )%></td>
              <td class="display-field"> <%= Html.Encode( currency.Value )%></td>
          </tr>
      <% } %>
  </table>

    <div style="margin: 40px 0 10px 0;">Seasons Awards</div>
    <table id="awards" cols=5>
    <tr>
      <th align = "right" width="5%">SeasonName</th>
      <th align = "center" width="30%">Season Dates, utc+3</th>
      <th align = "center" width="5%">Perls</th>
      <th align = "center" width="5%">Skin</th>
      <th align = "center" width="5%">Flag</th>
      <th align = "center" width="50%">Talents</th>
        <th align = "center" width="50%">Lootboxes</th>
    </tr>
    <% foreach (var item in Model.ListSeasonsAwards)
         { %>
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
        <% if (item.Perls > 0)
           { %>
             <td class="display-label" align = "right"> <%= Html.Encode( item.Perls )%></td>
        <% }
           else
           { %>
             <td class="display-label"> </td>
        <% } %>
        <td class="display-label"> <%= Html.Encode( item.Skin )%> </td>     
        <td class="display-label"> <%= Html.Encode( item.Flag )%> </td>    
        <td class="display-label"> <%= Html.Encode(item.Talents)%> </td>    
        <td class="display-label"> <%= Html.Encode(item.Lootboxes)%> </td>    
      <% if (((GMToolsPrincipal)User).HasPermission("GM_AccountEdit")) { %>
          <td>
            <%= Html.ActionLink("edit", "EditSeasonAwards", new { login = Model.Login, SeasonId = item.SeasonId,
                                                                  SeasonName = item.SeasonName,
                                                                  StartDate = item.StartDate,
                                                                  EndDate = item.EndDate,
                                                                  Perls = item.Perls,
                                                                  Skin = item.Skin,
                                                                  Flag = item.Flag,
                                                                  Talents = item.Talents})%>
          </td>
        <% } %>
           </tr>  
    <% } %>
    </table>
  </div>

</asp:Content>
