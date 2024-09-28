<%@ Page Title="" Language="C#" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.GM.Models.UpgradeHeroTalentsInfoModel>" MasterPageFile="~/Views/Shared/Site.Master" %>

<asp:Content runat="server" ID="Title" ContentPlaceHolderID="TitleContent">
Give UpgradeHeroTalentsInfo
</asp:Content>

<asp:Content runat="server" ID="Main" ContentPlaceHolderID="MainContent">
  <h2 style="color:Red">UpgradeHeroTalentsInfo for user <%= ViewData["login"] %></h2>

  <% using (Html.BeginForm()) {%>
  <%= Html.ValidationSummary(true) %>
  <fieldset>
    <legend>Fields</legend>
    <%= Html.HiddenFor(model => model.Login) %>
    
    <div class="editor-label">
      <%= Html.LabelFor(model => model.CountRunes) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor( model => model.CountRunes )%>
      <%= Html.ValidationMessageFor( model => model.CountRunes )%>
    </div>

    <input type="submit" name="Edit" id="Edit" value="Give" style="margin:15px 0 0 0"/>
  </fieldset>
  <% } %>
  
  <div>
    <%= Html.ActionLink("Back to account details", "Details", new { login = ViewData["login"] })%>
  </div>

</asp:Content>
