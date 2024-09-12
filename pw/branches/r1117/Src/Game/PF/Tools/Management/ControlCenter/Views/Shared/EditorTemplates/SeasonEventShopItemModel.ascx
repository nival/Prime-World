<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<SeasonEventShopItemModel>" %>
<%@ Import namespace="ControlCenter.Areas.EventTool.Models" %>

<%--Name--%>
<div class="editor-label"><strong><%= Html.LabelFor(m => m.Name) %>:</strong></div>
<div class="editor-field">
    <%= Html.EditorFor(m => m.Name) %>
    <%= Html.ValidationMessageFor(m => m.Name) %>
</div>

<%--Image--%>
<div class="editor-label"><strong><%= Html.LabelFor(m => m.Image)%>:</strong></div>
<div class="editor-field">
    <%= Html.EditorFor(m => m.Image)%>
    <%= Html.ValidationMessageFor(m => m.Image)%>
</div>

<fieldset style="border: solid blue 2px;">
<legend>
<%--LootboxId--%>
<div class="editor-label"><strong><%= Html.LabelFor(m => m.LootboxId) %>:</strong></div>
<div class="editor-field">
    <%= Html.EditorFor(m => m.LootboxId) %>
    <%= Html.ValidationMessageFor(m => m.LootboxId) %>
</div>
</legend>
<%--Cost--%>
<div class="editor-label"><strong><%= Html.LabelFor(m => m.Cost)%>*:</strong></div>
<div class="editor-field">
    <%= Html.EditorFor(m => m.Cost)%>
    <%= Html.ValidationMessageFor(m => m.Cost)%>
</div>
<div class="editor-label"><strong><%= Html.LabelFor(m => m.Limit)%>*:</strong></div>
<div class="editor-field">
    <%= Html.EditorFor(m => m.Limit)%>
    <%= Html.ValidationMessageFor(m => m.Limit)%>
</div>
</fieldset>

