<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<UserCreateModel>" %>
<%@ Import Namespace="ControlCenter.Areas.Admin.Models"%>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
  UserCreate
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <h2>UserCreate</h2>
  
  <% using (Html.BeginForm()) { %>
  <%= Html.ValidationSummary(true) %>
    <fieldset>
      <legend>Fields</legend>
      
      <div class="editor-label">
        <%= Html.LabelFor(model => model.UserName) %>
      </div>
      <div class="editor-field">
        <%= Html.TextBoxFor(model => model.UserName) %>
        <%= Html.ValidationMessageFor(model => model.UserName) %>
      </div>
      
      <div class="editor-label">
        <%= Html.LabelFor(model => model.FullName) %>
      </div>
      <div class="editor-field">
        <%= Html.TextBoxFor(model => model.FullName) %>
        <%= Html.ValidationMessageFor(model => model.FullName) %>
      </div>
      
      <div class="editor-label">
        <%= Html.LabelFor(model => model.Email) %>
      </div>
      <div class="editor-field">
        <%= Html.TextBoxFor(model => model.Email) %>
        <%= Html.ValidationMessageFor(model => model.Email) %>
      </div>
      
      <div class="editor-label">
        <%= Html.LabelFor(model => model.Superuser) %>
      </div>
      <div class="editor-field">
        <%= Html.CheckBoxFor(model => model.Superuser) %>
      </div>
      
      <div class="editor-label">
        <%= Html.LabelFor(model => model.Password) %>
      </div>
      <div class="editor-field">
        <%= Html.PasswordFor(model => model.Password) %>
        <%= Html.ValidationMessageFor(model => model.Password) %>
      </div>
      
      <div class="editor-label">
        <%= Html.LabelFor(model => model.ConfirmPassword) %>
      </div>
      <div class="editor-field">
        <%= Html.PasswordFor(model => model.ConfirmPassword)%>
        <%= Html.ValidationMessageFor(model => model.ConfirmPassword) %>
      </div>
      
      <p>
        <input type="submit" value="Create" />
      </p>
    </fieldset>
  <% } %>
  <div>
    <%= Html.ActionLink("Back to List", "Index") %>
  </div>
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>
