<%@ Page Language="C#" Inherits="System.Web.Mvc.ViewPage<LogOnModel>" %>
<%@ Import Namespace="ControlCenter.Areas.Admin.Models"%>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
  <title>Log On</title>
  <link href="~/Content/Site.css" rel="stylesheet" type="text/css" />
  <style type="text/css">
    div#loginpanel {
      width: 300px;
      margin: 0 auto;
    }
    div#loginpanel .editor-field input {
      width: 270px;
    }
  </style>
</head>
<body>
<div id="loginpanel">

  <p>Please enter your username and password.</p>

  <% using (Html.BeginForm()) {%>

  <%= Html.ValidationSummary(true, "Login was unsuccessful. Please correct the errors and try again.") %>
  
  <fieldset>
    <legend>Account Information</legend>

    <div class="editor-label">
      <%= Html.LabelFor(m => m.UserName) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(m => m.UserName) %>
      <%= Html.ValidationMessageFor(m => m.UserName) %>
    </div>

    <div class="editor-label">
      <%= Html.LabelFor(m => m.Password) %>
    </div>
    <div class="editor-field">
      <%= Html.PasswordFor(m => m.Password) %>
      <%= Html.ValidationMessageFor(m => m.Password) %>
    </div>

    <div class="editor-label">
      <%= Html.CheckBoxFor(m => m.RememberMe) %>
      <%= Html.LabelFor(m => m.RememberMe) %>
    </div>
    <p>
      <input type="submit" value="Log On" />
    </p>
  </fieldset>
  <% } %>
</div>
</body>
</html>
