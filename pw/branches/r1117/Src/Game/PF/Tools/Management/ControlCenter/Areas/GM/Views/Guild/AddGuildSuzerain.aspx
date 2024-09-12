<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.GM.Models.GuildChangeSuzerainModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
  AddSuzerain
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

  <h2>AddSuzerain to guild "<%= Html.Encode("[" + Model.ShortName + "] " + Model.FullName)%>"</h2>
  <% using (Html.BeginForm()) { %>
  <%= Html.ValidationSummary(true) %>
  <fieldset>
    <legend>Select the new suzerain</legend>
    <%= Html.HiddenFor(model => model.GuildId) %>
    <%= Html.HiddenFor(model => model.ShortName)%>
    <%= Html.HiddenFor(model => model.FullName)%>
    <p>
      <%= Html.TextBoxFor(model => model.SuzerainId)%>
    </p>
    <p>
      <input type="submit" value="Change" />
    </p>
  </fieldset>
  <% } %>
  <div>
    <%= Html.ActionLink("Cancel", "Details", new { id = Model.GuildId }) %>
  </div>
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>
