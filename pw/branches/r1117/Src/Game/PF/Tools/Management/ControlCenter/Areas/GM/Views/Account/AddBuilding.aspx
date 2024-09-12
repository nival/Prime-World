<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.GM.Models.BuildingAddModel>" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
	AddBuilding
</asp:Content>

<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">

<div id="pagemenu" style="width: 30%; float: right; margin-right: 0px">
  <p><%= Html.ActionLink("Back to account details", "Details", new { Model.Auid })%></p>
</div>

<div id="pagecontent" style="width: 70%">
  <h2>AddBuilding</h2>

  <% using (Html.BeginForm()) {%>
    <%= Html.ValidationSummary(true) %>
    <fieldset>
      <legend>Fields</legend>

      <%= Html.HiddenFor(model => model.Auid) %>
      
      <div class="editor-label">
        <%= Html.LabelFor(model => model.ClassId) %>
      </div>
      <div class="editor-field">
        <%= Html.DropDownListFor(model => model.ClassId, (SelectList)ViewData["allbuildings"]) %>
        <%= Html.ValidationMessageFor(model => model.ClassId) %>
      </div>
      
      <div class="editor-label">
        <%= Html.LabelFor(model => model.Level) %>
      </div>
      <div class="editor-field">
        <%= Html.TextBoxFor(model => model.Level) %>
        <%= Html.ValidationMessageFor(model => model.Level) %>
      </div>
      
      <p>
        <input type="submit" value="Create" />
      </p>
    </fieldset>
  <% } %>
</div>
</asp:Content>
