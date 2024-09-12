<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<TradeGroupMemberModel>" %>
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

<%--CurrencyName--%>
<div class="editor-label"><strong><%= Html.LabelFor(m => m.CurrencyName)%>*:</strong></div>
<div class="editor-field">
    <%= Html.EditorFor(m => m.CurrencyName)%>
    <%= Html.ValidationMessageFor(m => m.CurrencyName)%>
</div>

<%--CurrencyCostPerExp--%>
<div class="editor-label"><strong><%= Html.LabelFor(m => m.CurrencyCostPerExp)%>*:</strong></div>
<div class="editor-field">
    <%= Html.EditorFor(m => m.CurrencyCostPerExp)%>
    <%= Html.ValidationMessageFor(m => m.CurrencyCostPerExp)%>
</div>
<fieldset style="border: solid blue 2px;">
<legend>
<%--RewardA--%>
<div class="editor-label"><strong><%= Html.LabelFor(m => m.RewardA)%>*:</strong></div>
</legend>

<%= Html.EditorFor(m => m.RewardA)%>

<%--RewardACost--%>
<div class="editor-label"><strong><%= Html.LabelFor(m => m.RewardACost)%>*:</strong></div>
<div class="editor-field">
    <%= Html.EditorFor(m => m.RewardACost)%>
    <%= Html.ValidationMessageFor(m => m.RewardACost)%>
</div>
</fieldset>

<fieldset style="border: solid blue 2px;">
<legend>
<%--RewardB--%>
<div class="editor-label"><strong><%= Html.LabelFor(m => m.RewardB)%>*:</strong></div>
</legend>

<%= Html.EditorFor(m => m.RewardB)%>

<%--RewardBCost--%>
<div class="editor-label"><strong><%= Html.LabelFor(m => m.RewardBCost)%>*:</strong></div>
<div class="editor-field">
    <%= Html.EditorFor(m => m.RewardBCost)%>
    <%= Html.ValidationMessageFor(m => m.RewardBCost)%>
</div>

</fieldset>


