<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.GM.Models.PayChangeFactionModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
Paid faction change
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <h2 style="color:Red">Paid faction change for user <%= Model.Login %></h2>

  <% using (Html.BeginForm()) {%>
  <%= Html.ValidationSummary(true) %>
  <fieldset>
    <legend>Fields</legend>
    
    <%= Html.HiddenFor(model => model.Login) %>
    
    <div class="editor-label">
      <%= Html.LabelFor(model => model.Login) %>
    </div>
    <div class="editor-field">
      <%= Html.DropDownListFor(model => model.NewFaction, new SelectList((Enum.GetValues(typeof(FractionEnum))).Cast<FractionEnum>().Take(2)))%>
      <%= Html.ValidationMessageFor(model => model.NewFaction) %>
    </div>
    <p>
      <input type="submit" value="Save" />
    </p>
  </fieldset>
  <% } %>
  
  <div>
    <%= Html.ActionLink("Back to account details", "Details", new { login = Model.Login })%>
  </div>
</asp:Content>
