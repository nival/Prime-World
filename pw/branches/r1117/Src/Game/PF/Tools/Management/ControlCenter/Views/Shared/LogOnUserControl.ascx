<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl" %>
<%
    if (Request.IsAuthenticated) {
%>
        Welcome, <b><%= Html.ActionLink(Page.User.Identity.Name, "Profile", "Authentication", new { area = "Admin" }, new {})%></b>!
        [ <%= Html.ActionLink("Log Off", "LogOff", "Authentication", new { area = "" }, new {}) %> ]
<%
    }
    else {
%> 
        [ <%= Html.ActionLink("Log On", "LogOn", "Authentication", new { area = "" }, new {}) %> ]
<%
    }
%>
