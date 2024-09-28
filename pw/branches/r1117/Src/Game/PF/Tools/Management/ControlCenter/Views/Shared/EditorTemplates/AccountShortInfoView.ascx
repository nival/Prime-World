<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<AccountShortInfoModel>" %>

<div class="editor-label"><strong><%= Html.LabelFor(m => m.Email) %></strong></div>
<div class="editor-field"><%= Model.Email %></div>

<div class="editor-label"><strong><%= Html.LabelFor(m => m.NickName) %></strong></div>
<div class="editor-field"><%= Model.NickName %></div>

<div class="editor-label"><strong><%= Html.LabelFor(m => m.SNUid) %></strong></div>
<div class="editor-field"><%= Model.SNUid %></div>

<div class="editor-label"><strong><%= Html.LabelFor(m => m.SNid) %></strong></div>
<div class="editor-field"><%= Model.SNid%></div>