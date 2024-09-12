<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<DonateRewardModel>" %>
<%@ Import Namespace="ControlCenter.Areas.EventTool.Models" %>

<%--Lootboxes--%>
<div class="editor-label"><%= Html.LabelFor(m => m.Lootboxes)%> <em>(список лутбоксов в формате lootboxId,lootboxId:count,...)</em>:</div>
<div class="editor-field">
  <%= Html.TextBoxFor(m => m.Lootboxes)%>
  <%= Html.ValidationMessageFor(m => m.Lootboxes)%>
</div>

