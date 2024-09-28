<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<GuildChangeLeaderModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
ChangeLeader
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <h2>Change leader from guild "<%= Html.Encode(Model.FullName) %>"</h2>
  <% using (Html.BeginForm()) { %>
  <%= Html.ValidationSummary(true) %>
  <fieldset>
    <legend>Select the new leader</legend>
    <%= Html.HiddenFor(m => m.GuildId) %>
    <%= Html.HiddenFor(m => m.OldLeader) %>
    <p>
      <%= Html.DropDownListFor(m => m.NewLeader, new SelectList(Model.Members, "Auid", "Nickname"))%>
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
