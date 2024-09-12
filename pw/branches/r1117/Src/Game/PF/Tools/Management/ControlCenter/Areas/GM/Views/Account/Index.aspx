<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<SearchBySNModel>" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
  Index
</asp:Content>

<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">
</asp:Content>

<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">
<style type="text/css">
  div#pagecontent form {
    margin-right: 30px;
  }
</style>

<div id="pagemenu" style="width: 30%; float: right; margin-right: 0px">
  <h2>Actions</h2>
  
  <% if (((GMToolsPrincipal)User).HasPermission("GM_AccountView")) { %>
    <p><%=Html.ActionLink("Guild search", "Search", "Guild") %></p>
  <% } %>

  <% if (((GMToolsPrincipal)User).HasPermission("GM_Broadcast")) { %>
    <p><%=Html.ActionLink("Broadcast Messages", "GetBroadcastList", "Broadcast") %></p>
  <% } %>

  <% if (((GMToolsPrincipal)User).HasPermission("GM_Complains")) { %>
    <p><%=Html.ActionLink("Complaints overview", "Overview", "Complaint") %></p>
  <% } %>
  <% if (((GMToolsPrincipal)User).HasPermission("GM_DynamicQuests")) { %>
    <p><%=Html.ActionLink("DynamicQuests overview", "Overview", "DynamicQuest")%></p>
  <% } %>
  <% if ( ( (GMToolsPrincipal)User ).HasPermission( "GM_AccountView" ) )
     { %>
    <p><%=Html.ActionLink("Broken accounts", "BrokenAccounts", "Account") %></p>
  <% } %>
  <%if ( ( (GMToolsPrincipal)User ).HasPermission( "GM_GameSessionView" ) )
  { %>
    <p><%= Html.ActionLink("Session replays", "GameReplays", "GameSession") %><p>
  <%} %>
  <%if ( ( (GMToolsPrincipal)User ).HasPermission( "GM_BruteForceDefenderView" ) )
  { %>
    <p><%= Html.ActionLink("Search bruteforce accounts", "Details", "BruteForceDefender")%><p>
    <p><%= Html.ActionLink("View banned ip", "BannedIp", "BruteForceDefender")%><p>    


  <%} %>
    <%if (((GMToolsPrincipal)User).HasPermission("GM_PlayerWipe"))
      { %>
        <p><%= Html.ActionLink("Player Wipe", "PlayerWipe", "PlayerWipe")%><p>


    <%} %>

</div>

<div id="pagecontent" style="width: 70%">
  <h2>Account search</h2>
<% if (((GMToolsPrincipal)User).HasPermission("GM_AccountView")) { %>
  <%= Html.ValidationSummary() %>
  <% using ( Html.BeginForm() ) { %>
  <fieldset>
    <legend>Search by SN ID</legend>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.SNid) %>
    </div>
    <div class="editor-field">
      <%= Html.DropDownListFor(model => model.SNid, new SelectList((List<string>)ViewData["all_sn"])) %>
      <%--<%= Html.ValidationMessageFor(model => model.SNid) %>--%>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.SNUid) %>
    </div>
    <div>
      <div class="editor-field" style="float: left">
        <%= Html.TextBoxFor(model => model.SNUid) %>
        <%--<%= Html.ValidationMessageFor(model => model.SNUid) %>--%>
      </div>
      <div style="float: left">
        <input type="submit" name="submitSnid" value="Show Info" style="margin: 0.5em;"/>
      </div>
    </div>
  </fieldset>
  <input style="display: none;" id="hiddenForIEBug" type="text" />
  <% } %>
  
  <% using ( Html.BeginForm() ) { %>
  <fieldset>
    <legend>Search By Auid</legend>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.Auid) %>
    </div>
    <div>
      <div class="editor-field" style="float: left">
        <%= Html.TextBoxFor(model => model.Auid) %>
        <%= Html.ValidationMessageFor(model => model.Auid) %>
      </div>
      <div style="float: left">
        <input type="submit" name="submitAuid" value="Show Info" style="margin: 0.5em;"/>
      </div>
    </div>
  </fieldset>
  <input style="display: none;" id="hiddenForIEBug2" type="text" />
  <% } %>
  
  <% using ( Html.BeginForm() ) { %>
  <fieldset id="search_by_nickname">
    <legend>Search By NickName</legend>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.NickName ) %>
    </div>
    <div>
      <div class="editor-field" style="float: left">
        <%= Html.TextBoxFor(model => model.NickName ) %>
        <%= Html.ValidationMessageFor(model => model.NickName ) %>
      </div>
      <div style="float: left">
        <input type="submit" name="submitNickName" value="Show Info"  style="margin: 0.5em;"/>
      </div>
    </div>
  </fieldset>
  <input style="display: none;" id="hiddenForIEBug3" type="text" />
  <% } %>
<% } %>
</div>

</asp:Content>
