<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
  CheckAccountValidity
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <% using ( Html.BeginForm() ) { %>
  
  <h2>
    Check Account <%= ViewData["login"]%>
  </h2>
  
  <p>
    <%= ViewData["checkResult"]%>
  </p>
  <p>
    <%= ViewData["fixResult"]%>
  </p>
  <% if ( ViewData["checkResult"] != "Account is OK" ) { %>
  <p>
    <input type="submit" value="Fix Account" />
  </p>
  <% } %>
  
  <p>
    <%= Html.ActionLink( "Back to account details", "Details", new { login = ViewData["login"] } )%>
  </p>
  
  <% } %>
</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>
