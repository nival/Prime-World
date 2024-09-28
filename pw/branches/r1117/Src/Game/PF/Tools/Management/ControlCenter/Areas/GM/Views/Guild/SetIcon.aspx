<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.GM.Models.GuildSetIconModel>" %>
<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	SetIcon
</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <h2>Set icon for guild <%= Model.FullName%></h2>
  
  <%= Html.ValidationSummary() %>
  
  <% using (Html.BeginForm("SetIcon", "Guild", FormMethod.Post, new { enctype = "multipart/form-data" })) { %>
    <%= Html.HiddenFor(model => model.FullName) %>
    <%= Html.HiddenFor(model => model.GuildId) %>
    <%= Html.HiddenFor(model => model.LeaderAuid) %>
    <%= Html.HiddenFor(model => model.IconChangesCount) %>

    <input type="file" name="image" id="image" />
    <br/>
    <input type="submit" value="Upload"/>

  <% } %>
  <br/>
  <br/>
  <div>
    <%= Html.ActionLink("Back to guild details", "Details", new { id = Model.GuildId }) %>
  </div>
</asp:Content>
