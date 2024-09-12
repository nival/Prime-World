<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.GM.Models.UserOperationModel>" %>
<%@ Import Namespace="AccountLib" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
  <%= Html.Encode(Model.Type) %> users
</asp:Content>

<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">

  <h2>
      <% if (Model.Type == UserOperationType.SetLeave) { %>
        <p><%= Model.Negative ? "REMOVE" : "ADD" %> LEAVE POINTS for these users</p>
      <% }
         else
         { %>
      <%= Html.Encode(Model.Type).ToUpper() %> these users
      <% } %>
  </h2>

  <% using (Html.BeginForm("ApplyOperation", "Account")) { %>
    <%= Html.HiddenFor(m => m.Type) %>
    <%= Html.HiddenFor(m => m.Negative) %>
    <div style="margin: 0 0 20px 20px">
      <% for (int i = 0; i < Model.Users.Count; i++ ) { %>
        <div>
          <%= Html.DisplayFor(m => m.Users[i].Nickname) %> (auid = <%= Html.DisplayFor(m => m.Users[i].Auid) %>)
          <% if (Model.Users[i].Complaints > 0) { %>
            <%= Html.ActionLink(String.Format("{0} complaints", Model.Users[i].Complaints), "Complaints", new { Model.Users[i].Auid, Model.Users[i].Nickname })%>
          <% } %>
          <%= Html.HiddenFor(m => m.Users[i].Auid) %>
          <%= Html.HiddenFor(m => m.Users[i].Nickname) %>
          <%= Html.HiddenFor(m => m.Users[i].Complaints) %>
        </div>
      <% } %>
    </div>

    <%
        switch (Model.Type)
        {
            case UserOperationType.Ban:
            case UserOperationType.Mute:
    %>
    <div class="editor-label">
        Minutes (0 for infinite)
    </div>
    <div class="editor-field">
        <%= Html.TextBoxFor(m => m.Value) %>
        <%= Html.ValidationMessageFor(m => m.Value) %>
    </div>
    <%
                break;
            case UserOperationType.SetLeave:
    %>
    <div class="editor-label">
        Number
    </div>
    <div class="editor-field">
        <%= Html.TextBoxFor(m => m.Value) %>
        <%= Html.ValidationMessageFor(m => m.Value) %>
    </div>
    <%
                break;
        }
    %>
    <div class="editor-label">
      <%= Html.LabelFor(m => m.Reason) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(m => m.Reason) %>
    </div>

    <%= Html.Hidden("returnUrl", ViewState["returnUrl"]) %>
    
    <p><input type="submit" value="Submit"/></p>
    
    <p><a href="<%= ViewData["returnUrl"] %>">Back</a></p>
    
  <% } %>

</asp:Content>
