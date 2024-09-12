<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<DonateRangeModel>" %>
<%@ Import Namespace="ControlCenter.Areas.EventTool.Models" %>


<%--AmountFrom--%>
<div class="editor-label"><%= Html.LabelFor(m => m.AmountFrom)%> <em>(set -1 if you don't want to set the lower bound)</em>:</div>
<div class="editor-field">
  <%= Html.TextBoxFor(m => m.AmountFrom)%>
  <%= Html.ValidationMessageFor(m => m.AmountFrom)%>
</div>

<%--AmountTo--%>
<div class="editor-label"><%= Html.LabelFor(m => m.AmountTo)%> <em>(set -1 if you don't want to set the upper bound)</em>:</div>
<div class="editor-field">
  <%= Html.TextBoxFor(m => m.AmountTo)%>
  <%= Html.ValidationMessageFor(m => m.AmountTo)%>
</div>

<%--Rewards--%>
<div class="editor-label">
  <strong><%= Html.LabelFor(m => m.Rewards)%>*:</strong>
  <button name="command" type="submit" value="<%=Model.CommandPrefix%>reward_add:0" style="color: darkgreen">ADD</button>
</div>
<% if (Model.Rewards.Count > 0)
   { %>
  <div>
    <% for (int i = 0; i < Model.Rewards.Count; i++)
       { %>
      <fieldset style="border: solid darkgoldenrod 2px;">
        <legend>
          <span>Reward #<%=i+1 %></span>
          <button name="command" type="submit" value="<%=Model.CommandPrefix%>reward_up:<%=i %>"<%= (i == 0) ? " disabled=\"disabled\"" : "" %>>&uarr;</button>
          <button name="command" type="submit" value="<%=Model.CommandPrefix%>reward_down:<%=i %>"<%= (i == Model.Rewards.Count - 1) ? " disabled=\"disabled\"" : "" %>>&darr;</button>
          <button name="command" type="submit" value="<%=Model.CommandPrefix%>reward_clone:<%=i %>" style="color: darkgreen">COPY</button>
          <button name="command" type="submit" value="<%=Model.CommandPrefix%>reward_remove:<%=i %>" style="color: darkred">DEL</button>
        </legend>
          <details open="open">
          <summary>Expand</summary>
          <%= Html.EditorFor(m => m.Rewards[i])%>
        </details>
      </fieldset>
    <% } %>
  </div>
<% } %>