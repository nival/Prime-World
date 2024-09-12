<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<QuestEventStageStepChoiceModel>" %>
<%@ Import namespace="ControlCenter.Areas.EventTool.Models" %>

<%--Title--%>
<div class="editor-label"><strong><%= Html.LabelFor(m => m.Title) %>*:</strong></div>
<div class="editor-field">
  <%= Html.EditorFor(m => m.Title) %>
  <%= Html.ValidationMessageFor(m => m.Title) %>
</div>

<%--WinMessage--%>
<div class="editor-label"><strong><%= Html.LabelFor(m => m.WinMessage) %>*:</strong></div>
<div class="editor-field">
  <%= Html.EditorFor(m => m.WinMessage) %>
  <%= Html.ValidationMessageFor(m => m.WinMessage) %>
</div>

<%--LoseMessage--%>
<div class="editor-label"><strong><%= Html.LabelFor(m => m.LoseMessage) %>*:</strong></div>
<div class="editor-field">
  <%= Html.EditorFor(m => m.LoseMessage) %>
  <%= Html.ValidationMessageFor(m => m.LoseMessage) %>
</div>

<%--WinRatioBase--%>
<div class="editor-label"><strong><%= Html.LabelFor(m => m.WinRatioBase) %>*:</strong></div>
<div class="editor-field">
  <%= Html.EditorFor(m => m.WinRatioBase) %>
  <%= Html.ValidationMessageFor(m => m.WinRatioBase) %>
</div>

<%--WinRatioGold--%>
<div class="editor-label"><strong><%= Html.LabelFor(m => m.WinRatioGold) %>*:</strong></div>
<div class="editor-field">
  <%= Html.EditorFor(m => m.WinRatioGold) %>
  <%= Html.ValidationMessageFor(m => m.WinRatioGold) %>
</div>

<%--Price--%>
<div class="editor-label"><strong><%= Html.LabelFor(m => m.Price) %>*:</strong></div>
<%= Html.EditorFor(m => m.Price) %>
