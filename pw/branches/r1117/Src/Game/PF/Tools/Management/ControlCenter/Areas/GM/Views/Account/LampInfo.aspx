<%@ Page Title="" Language="C#" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.GM.Models.LampInfoModel>" MasterPageFile="~/Views/Shared/Site.Master" %>

<asp:Content runat="server" ID="Title" ContentPlaceHolderID="TitleContent">
Give Lamp
</asp:Content>

<asp:Content runat="server" ID="Main" ContentPlaceHolderID="MainContent">
  <h2 style="color:Red">Lamp for user <%= ViewData["login"] %></h2>

  <% using (Html.BeginForm()) {%>
  <%= Html.ValidationSummary(true) %>
  <fieldset>
    <legend>Fields</legend>
    <%= Html.HiddenFor(model => model.Login) %>
    
    <div class="editor-label">
      <%= Html.LabelFor(model => model.Bonus) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor( model => model.Bonus )%>
      <%= Html.ValidationMessageFor( model => model.Bonus )%>
    </div>

    <div class="editor-label">
      <%= Html.LabelFor(model => model.Gold) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor( model => model.Gold )%>
      <%= Html.ValidationMessageFor( model => model.Gold )%>
    </div>

    <div class="editor-label">
      <%= Html.LabelFor(model => model.Transaction) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor( model => model.Transaction )%>
      <%= Html.ValidationMessageFor( model => model.Transaction )%>
    </div>

    <div class="editor-label">
      <%= Html.LabelFor(model => model.Duration) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor( model => model.Duration )%>
      <%= Html.ValidationMessageFor( model => model.Duration )%>
    </div>

    <input type="submit" value="Give" style="margin:15px 0 0 0"/>
  </fieldset>
  <% } %>
  
  <div>
    <%= Html.ActionLink("Back to account details", "Details", new { login = ViewData["login"] })%>
  </div>

</asp:Content>
