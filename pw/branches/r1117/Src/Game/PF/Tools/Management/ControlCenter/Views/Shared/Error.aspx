<%@ Page Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<System.Web.Mvc.HandleErrorInfo>" %>

<asp:Content ID="errorTitle" ContentPlaceHolderID="TitleContent" runat="server">
    Error
</asp:Content>

<asp:Content ID="errorContent" ContentPlaceHolderID="MainContent" runat="server">
    <h2>
        Sorry, an error occurred while processing your request.
    </h2>
    
    <% if (Model != null) { %>
      <p>Action :     <%= Html.Encode(Model.ActionName) %></p>
      <p>Controller : <%= Html.Encode(Model.ControllerName) %></p>
      <p>Exception:   <%= Html.Encode(Model.Exception).Replace("\n","<br>") %></p>
    <% } %>
</asp:Content>
