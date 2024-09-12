<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<ResourcesTableSmallModel>" %>
<%@ Import Namespace="ControlCenter.Areas.EventTool.Models" %>

<div class="editor-field">
  <%= Html.TextBoxFor(m => m.Resource1)%> <%= Html.ValidationMessageFor(m => m.Resource1)%>
  <%= Html.LabelFor(m => m.Resource1)%>
</div>

<div class="editor-field">
  <%= Html.TextBoxFor(m => m.Resource2)%> <%= Html.ValidationMessageFor(m => m.Resource2)%>
  <%= Html.LabelFor(m => m.Resource2)%>
</div>

<div class="editor-field">
  <%= Html.TextBoxFor(m => m.Resource3)%> <%= Html.ValidationMessageFor(m => m.Resource3)%>
  <%= Html.LabelFor(m => m.Resource3)%>
</div>

<div class="editor-field">
  <%= Html.TextBoxFor(m => m.Silver)%> <%= Html.ValidationMessageFor(m => m.Silver)%>
  <%= Html.LabelFor(m => m.Silver)%>
</div>

<div class="editor-field">
  <%= Html.TextBoxFor(m => m.Gold)%> <%= Html.ValidationMessageFor(m => m.Gold)%>
  <%= Html.LabelFor(m => m.Gold)%>
</div>

<div class="editor-field">
  <%= Html.TextBoxFor(m => m.Perl)%> <%= Html.ValidationMessageFor(m => m.Perl)%>
  <%= Html.LabelFor(m => m.Perl)%>
</div>

<div class="editor-field">
  <%= Html.TextBoxFor(m => m.RedPerl)%> <%= Html.ValidationMessageFor(m => m.RedPerl)%>
  <%= Html.LabelFor(m => m.RedPerl)%>
</div>

<div class="editor-field">
  <%= Html.TextBoxFor(m => m.CurrencyId)%> <%= Html.ValidationMessageFor(m => m.CurrencyId)%>
  <%= Html.LabelFor(m => m.CurrencyId)%>
</div>

<div class="editor-field">
  <%= Html.TextBoxFor(m => m.Currency)%> <%= Html.ValidationMessageFor(m => m.Currency)%>
  <%= Html.LabelFor(m => m.Currency)%>
</div>
