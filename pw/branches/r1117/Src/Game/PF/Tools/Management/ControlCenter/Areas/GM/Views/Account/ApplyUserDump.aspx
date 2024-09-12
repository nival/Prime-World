<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
  ApplyUserDump
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <% using ( Html.BeginForm( "ApplyUserDump", "Account", new { login = ViewData["login"] }, FormMethod.Post, new { enctype = "multipart/form-data" } ) ) { %>
  <h2>
    Apply User Dump for<%= ViewData["login"]%></h2>
  <div>
    <% if ( (int)ViewData["noNeedToShowResult"] == 0 )
       { %>
    <b>Successfully applied</b>
    <% }
       else if ( (int)ViewData["noNeedToShowResult"] == -1 )
       { %>
    <b>Errors In applying</b>
    <% } %>
  </div>
  <p>
    Select dump location
    <input type="file" name="dumpUpload">
  </p>
  <p>
    <input type="submit" value="Upload and Apply" />
  </p>
  <%--<%= Html.TextArea("dump", "", 30, 80, null) %>--%>
  <p>
    <%= Html.ActionLink( "Back to account details", "Details", new { login = ViewData["login"] } )%>
  </p>
  <% } %>
</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>
