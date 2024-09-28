<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<QuestEventStageStepModel>" %>
<%@ Import namespace="ControlCenter.Areas.EventTool.Models" %>

<%--Title--%>
<div class="editor-label"><strong><%= Html.LabelFor(m => m.Title) %>*:</strong></div>
<div class="editor-field">
  <%= Html.EditorFor(m => m.Title) %>
  <%= Html.ValidationMessageFor(m => m.Title) %>
</div>

<%--Choices--%>
<div class="editor-label">
  <strong><%= Html.LabelFor(m => m.Choices) %>*:</strong>
  <button name="command" type="submit" value="<%=Model.CommandPrefix %>choice_add:0" style="color: darkgreen">ADD</button>
</div>
<% if (Model.Choices.Count > 0) { %>
  <div>
    <% for (int i = 0; i < Model.Choices.Count; i++) { %>
      <fieldset style="border: solid darkgoldenrod 2px;">
        <legend>
          <span>Choice #<%=i+1 %></span>
          <button name="command" type="submit" value="<%=Model.CommandPrefix %>choice_up:<%=i %>"<%= (i == 0) ? " disabled=\"disabled\"" : "" %>>&uarr;</button>
          <button name="command" type="submit" value="<%=Model.CommandPrefix %>choice_down:<%=i %>"<%= (i == Model.Choices.Count - 1) ? " disabled=\"disabled\"" : "" %>>&darr;</button>
          <button name="command" type="submit" value="<%=Model.CommandPrefix %>choice_remove:<%=i %>" style="color: darkred">DEL</button>
        </legend>
        <details open="open">
          <summary>Expand</summary>
          <%= Html.EditorFor(m => m.Choices[i]) %>
        </details>
      </fieldset>
    <% } %>
  </div>
<% } %>
