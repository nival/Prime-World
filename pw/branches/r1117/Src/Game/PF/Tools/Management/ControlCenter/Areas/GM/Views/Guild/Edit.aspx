<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.GM.Models.GuildEditModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
Edit Guild
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <h2>Edit</h2>

  <% using (Html.BeginForm()) {%>
  <%= Html.ValidationSummary(true) %>

  <fieldset>
    <legend>Fields</legend>
    <%= Html.HiddenFor(model => model.GuildId) %>

    <div class="editor-label">
      <%= Html.LabelFor(model => model.ShortName) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.ShortName) %>
      <%= Html.ValidationMessageFor(model => model.ShortName) %>
    </div>
    
    <div class="editor-label">
      <%= Html.LabelFor(model => model.FullName) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.FullName) %>
      <%= Html.ValidationMessageFor(model => model.FullName) %>
    </div>
    
    <div class="editor-label">
      <%= Html.LabelFor(model => model.MessageOfTheDay) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.MessageOfTheDay) %>
      <%= Html.ValidationMessageFor(model => model.MessageOfTheDay) %>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.GuildRating) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.GuildRating)%>
      <%= Html.ValidationMessageFor(model => model.GuildRating)%>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.GuildExperience) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.GuildExperience) %>
      <%= Html.ValidationMessageFor(model => model.GuildExperience) %>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.CWPoints)%>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.CWPoints) %>
      <%= Html.ValidationMessageFor(model => model.CWPoints) %>
    </div>
    
    <p>
      <input type="submit" value="Save" />
    </p>
  </fieldset>
  <% } %>
  <div>
    <%= Html.ActionLink("Back to guild details", "Details", new { id = Model.GuildId }) %>
  </div>
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>
