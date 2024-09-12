<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<SeasonInfoModel>" %>
<%@ Import Namespace="ControlCenter.Areas.GM.Models" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
  EditSeasonInfo
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <div style="font-size: 1.2em; color: #000000; margin-bottom: 15px;">
    <%= Html.Encode(String.Format("Edit Season Info, Season: {0}, Account: {1}, Hero: {2}", ViewData["seasonName"], ViewData["login"], ViewData["heroName"]))%>
  </div>
  <div>
    <% if ( (int)ViewData["noNeedToShowEditResult"] == 0 ) { %>
    <b>Successfully Edited</b>
    <% } else if ( (int)ViewData["noNeedToShowEditResult"] == -1 ) { %>
    <b>Errors In Editing</b>
    <% } %>
  </div>
  <% using (Html.BeginForm()) {%>
  <%= Html.ValidationSummary(true) %>
  <fieldset>
    <legend>Fields</legend>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.SeasonRating) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.SeasonRating)%>
      <%= Html.ValidationMessageFor(model => model.SeasonRating)%>
    </div>
        <div class="editor-label">
      <%= Html.LabelFor(model => model.LeagueIndex) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.LeagueIndex)%>
      <%= Html.ValidationMessageFor(model => model.LeagueIndex)%>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.BestLeaguePlace) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.BestLeaguePlace)%>
      <%= Html.ValidationMessageFor(model => model.BestLeaguePlace)%>
    </div>
    <p>
      <input type="submit" value="Save" />
    </p>
  </fieldset>
  <% } %>
  <div>
    <%= Html.ActionLink("back to season info list", "SeasonsInfo", new { login = ViewData["login"], HeroClassId = ViewData["HeroClassId"], HeroInstanceId = ViewData["HeroInstanceId"], heroName = ViewData["heroName"] })%>
  </div>
</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>
