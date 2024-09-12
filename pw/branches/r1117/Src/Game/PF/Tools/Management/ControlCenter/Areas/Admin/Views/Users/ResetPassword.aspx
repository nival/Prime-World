<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<AdminUserResetPasswordModel>" %>
<%@ Import Namespace="ControlCenter.Areas.Admin.Models"%>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
  UserResetPassword
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <h2>Reset password for user <%= Html.Encode(Model.UserName) %></h2>

  <% using (Html.BeginForm()) {%>
    <%= Html.ValidationSummary(true) %>
    <fieldset>
    
      <legend>Enter new password</legend>
      
      <%= Html.HiddenFor(model => model.UserId) %>
      <%= Html.HiddenFor(model => model.UserName) %>

      <div class="editor-label">
        <%= Html.LabelFor(model => model.NewPassword) %>
      </div>
      <div class="editor-field">
        <%= Html.PasswordFor(model => model.NewPassword) %>
        <%= Html.ValidationMessageFor(model => model.NewPassword) %>
      </div>

      <div class="editor-label">
        <%= Html.LabelFor(model => model.ConfirmPassword) %>
      </div>
      <div class="editor-field">
        <%= Html.PasswordFor(model => model.ConfirmPassword)%>
        <%= Html.ValidationMessageFor(model => model.ConfirmPassword) %>
      </div>

      <p>
        <input type="submit" value="Change" />
      </p>
    </fieldset>
  <% } %>
  <div>
    <%= Html.ActionLink("Back to info", "Details", new { id = Model.UserId }) %>
  </div>
</asp:Content>
