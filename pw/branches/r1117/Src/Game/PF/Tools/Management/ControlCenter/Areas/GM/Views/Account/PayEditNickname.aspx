<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<PayEditNicknameModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
Paid nickname change
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <h2 style="color:Red">Paid nickname change for user <%= Model.Login %></h2>

  <% using (Html.BeginForm()) {%>
  <%= Html.ValidationSummary(true) %>
  <fieldset>
    <legend>Fields</legend>
    
    <%= Html.HiddenFor(model => model.Login) %>
    
    <div class="editor-label">
      <%= Html.LabelFor(model => model.Nickname) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.Nickname) %>
      <%= Html.ValidationMessageFor(model => model.Nickname) %>
    </div>
    <p>
      <input type="submit" value="Create" />
    </p>
  </fieldset>
  <% } %>
  
  <div>
    <%= Html.ActionLink("Back to account details", "Details", new { login = Model.Login })%>
  </div>
</asp:Content>
