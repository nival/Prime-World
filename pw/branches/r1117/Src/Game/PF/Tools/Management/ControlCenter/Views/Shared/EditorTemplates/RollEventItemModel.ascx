<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<RollEventItemModel>" %>
<%@ Import Namespace="ControlCenter.Areas.EventTool.Models" %>

<% if (Model.IsRatioRequired) { %>
  <%--Ratio--%>
  <div class="editor-label"><strong><%= Html.LabelFor(m => m.Ratio)%> <em>(in range [0.001 to 10000.0])</em>*:</strong></div>
  <div class="editor-field">
    <%= Html.TextBoxFor(m => m.Ratio)%>
    <%= Html.ValidationMessageFor(m => m.Ratio)%>
  </div>
<% } %>

<%--ItemType--%>
<div class="display-field"><strong><%= Html.LabelFor(m => m.ItemType)%>*:</strong></div>
<div class="editor-field">
  <%= Html.DropDownListFor(m => m.ItemType, Model.ItemType.ToSelectList())%>
  <%= Html.ValidationMessageFor(m => m.ItemType)%>
</div>

<%--PersistentId--%>
<div class="editor-label"><%= Html.LabelFor(m => m.PersistentId)%> <em>(for talent, hero, skin or lootbox)</em>:</div>
<div class="editor-field">
  <%= Html.TextBoxFor(m => m.PersistentId)%>
  <%= Html.ValidationMessageFor(m => m.PersistentId)%>
</div>

<%--ResourcesTableSmallModel--%>
<fieldset style="border-color: #008800; border-style: solid; border-width:1.5px;">
  <legend><%= Html.LabelFor(m => m.Resource)%></legend>
  <details><summary>Used in <strong>Resource</strong> type only</summary>
  <%= Html.EditorFor(m => m.Resource) %>
  </details>
</fieldset>
