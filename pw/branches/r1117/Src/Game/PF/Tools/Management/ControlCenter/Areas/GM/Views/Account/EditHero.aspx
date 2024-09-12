<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<HeroInfoModel>" %>
<%@ Import Namespace="ControlCenter.Areas.GM.Models" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
  EditHero
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <div style="font-size: 1.2em; color: #000000; margin-bottom: 15px;">
    <%= Html.Encode( String.Format( "Edit Hero: {0}, Account: {1}", ViewData["heroName"], ViewData["login"] ) )%>
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
      <%= Html.LabelFor(model => model.Experience) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.Experience) %>
      <%= Html.ValidationMessageFor(model => model.Experience) %>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.Rating) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.Rating) %>
      <%= Html.ValidationMessageFor(model => model.Rating) %>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.EpicWins) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor( model => model.EpicWins )%>
      <%= Html.ValidationMessageFor( model => model.EpicWins )%>
    </div>
    <p>
      <input type="submit" value="Save" />
    </p>
  </fieldset>
  <% } %>
  <div>
    <%= Html.ActionLink( "Back to List", "Heroes", new { login = ViewData["login"] } )%>
  </div>
</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>
