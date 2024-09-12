<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<SeasonAwardsModel>" %>
<%@ Import Namespace="ControlCenter.Areas.GM.Models" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
  EditSeasonAwards
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <div style="font-size: 1.2em; color: #000000; margin-bottom: 15px;">
    <%= Html.Encode(String.Format("Edit Season Awards, Season: {0}, Account: {1}", ViewData["seasonName"], ViewData["login"]))%>
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
      <%= Html.LabelFor(model => model.Flag) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.Flag) %>
      <%= Html.ValidationMessageFor(model => model.Flag)%>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.Perls) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.Perls)%>
      <%= Html.ValidationMessageFor(model => model.Perls)%>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.Skin) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.Skin)%>
      <%= Html.ValidationMessageFor(model => model.Skin)%>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.Talents)%>
    </div>
    <div class="editor-field" width="100%">
      <%= Html.TextBoxFor(model => model.Talents)%>
      <%= Html.ValidationMessageFor(model => model.Talents)%>
    </div>
    <p>
      <input type="submit" value="Save" />
    </p>
  </fieldset>
  <% } %>
  <div>
    <%= Html.ActionLink("Back to account details", "Details", new { login = ViewData["login"] })%>
  </div>
</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>
