<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<UserInfoModel>" %>
<%@ Import Namespace="ControlCenter.Areas.Admin.Models"%>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
  UserEdit
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

  <h2>UserEdit</h2>

  <% using (Html.BeginForm()) {%>
  <%= Html.ValidationSummary(true) %>
  <fieldset>
    <legend>Fields</legend>

    <%= Html.HiddenFor(model => model.UserId) %>
    <%= Html.HiddenFor(model => model.UserName) %>

    <div class="editor-label">
      <%= Html.LabelFor(model => model.UserName) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.UserName, new { disabled = true }) %>
      <%= Html.ValidationMessageFor(model => model.UserName)%>
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
    
    <p>
      <input type="submit" value="Save" />
    </p>
  </fieldset>
  <% } %>
  
  <div>
    <%= Html.ActionLink("Cancel", "Details", new { id = Model.UserId }) %>
  </div>
  
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>
