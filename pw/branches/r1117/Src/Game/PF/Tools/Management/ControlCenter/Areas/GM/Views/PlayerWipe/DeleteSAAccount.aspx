<%@ Page Title="Delete SA Account" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<DeleteSaAccountModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
Delete SocAggr Account
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <div id="pagemenu" style="width: 30%; float: right; margin-right: 0px">
    <div class = "menublock">
      <h4>Menu</h4>
      <% if (!Model.Done) { %>
      <p><%= Html.ActionLink("Back to account details", "Details", "Account", new { auid = Model.Auid }, null) %></p>
      <% } %>
    </div>
  </div>
  
  <div id="pagecontent" style="width: 70%">
    <h2>Delete all authorization data on SocAggr for account with AUID = <%= Model.Auid %></h2>
    <% if (Model.Done) { %>
      <% if (string.IsNullOrEmpty(Model.Result)) { %>
        <h3>Account successfully deleted.</h3>
        <%= Html.ActionLink("Return", "Index", "Account", null, null) %>
      <% } else { %>
        <h3>Can't delete account: <%=Model.Result %></h3>
        <%= Html.ActionLink("Back", "DeleteSaAccount", new {auid = Model.Auid}) %>
      <% } %>
    <% } else { %>
      <% using (Html.BeginForm()) { %>
        <div class="editor-label"><strong>Are you serious?</strong></div>
        <div class="editor-field"><%= Html.EditorFor(m => m.Confirm1) %>&nbsp;<%= Html.LabelFor(m => m.Confirm1) %></div>
        <div class="editor-field"><%= Html.EditorFor(m => m.Confirm2) %>&nbsp;<%= Html.LabelFor(m => m.Confirm2) %></div>
        <div class="editor-field"><%= Html.EditorFor(m => m.Confirm3) %>&nbsp;<%= Html.LabelFor(m => m.Confirm3) %></div>
        <button name="command" type="submit" value="confirm" style="background-color: red;">Confrim</button>
      <% } %>
    <% } %>
  </div>
</asp:Content>
