<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Models.WarningModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	Warning!
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

    <h2>Warning!</h2>
    <% using (Html.BeginForm())
       { %>
      <p><%= Model.Message %></p>
      <% if (!String.IsNullOrEmpty(Model.RedirectUrl))
         { %>
          <a href="<%= Model.RedirectUrl %>">Proceed</a>
        <% }
         else
         { %>
      <%= Html.ActionLink("Proceed", Model.Action, Model.Controller, Model.RedirectRoute, null) %>
      <% } %>
    <% } %>

</asp:Content>
