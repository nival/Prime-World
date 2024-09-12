<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<RoleInfoModel>" %>
<%@ Import Namespace="ControlCenter.Areas.Admin.Models"%>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	RoleCreate
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <h2>RoleCreate</h2>
  
  <% using (Html.BeginForm()) { %>
  <%= Html.ValidationSummary(true) %>
  
  <fieldset>
    <legend>New role</legend>
    
    <div class="editor-label">
      <%= Html.LabelFor(model => model.RoleName) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.RoleName) %>
      <%= Html.ValidationMessageFor(model => model.RoleName) %>
    </div>
    
    <div class="editor-label">
      <%= Html.LabelFor(model => model.Description) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.Description) %>
      <%= Html.ValidationMessageFor(model => model.Description) %>
    </div>
    
    <div class="editor-label">
      <%= Html.LabelFor(model => model.Locale) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.Locale)%>
      <%= Html.ValidationMessageFor(model => model.Locale)%>
    </div>
    
    <div class="editor-label">
      <%= Html.LabelFor(model => model.Muid) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.Muid)%>
      <%= Html.ValidationMessageFor(model => model.Muid)%>
    </div>
    
    <div style="margin-top: 15px;">
      <% var permissions = (Dictionary<int, string>)ViewData["AllPermissions"]; %>
      <% foreach (var p in permissions.OrderBy(k => k.Value)) { %>
        <div class="editor-field">
          <input type="checkbox" name="chkPermissions" value="<%= p.Key %>" />
          <%= Html.Encode(p.Value) %>
        </div>
      <% } %>
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

