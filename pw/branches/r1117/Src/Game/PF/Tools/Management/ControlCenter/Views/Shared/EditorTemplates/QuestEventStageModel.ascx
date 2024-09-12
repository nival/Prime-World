<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<QuestEventStageModel>" %>
<%@ Import namespace="ControlCenter.Areas.EventTool.Models" %>

<%--Title--%>
<div class="editor-label"><%= Html.LabelFor(m => m.Title) %>:</div>
<div class="editor-field">
  <%= Html.EditorFor(m => m.Title) %>
  <%= Html.ValidationMessageFor(m => m.Title) %>
</div>

<%--Text--%>
<div class="editor-label"><%= Html.LabelFor(m => m.Text) %>:</div>
<div class="editor-field">
  <%= Html.EditorFor(m => m.Text) %>
  <%= Html.ValidationMessageFor(m => m.Text) %>
</div>

<%--Image--%>
<div class="editor-label"><%= Html.LabelFor(m => m.Image) %>:</div>
<div class="editor-field">
  <%= Html.EditorFor(m => m.Image) %>
  <%= Html.ValidationMessageFor(m => m.Image) %>
</div>

<%--Reward--%>
<div class="editor-label"><strong><%= Html.LabelFor(m => m.Reward) %>*</strong> <em>(only "Lootbox" type supported)</em>:</div>
<fieldset style="border: solid green 2px;">
  <%= Html.EditorFor(m => m.Reward) %>
</fieldset>

<%--LoseReward--%>
<div class="editor-label"><strong><%= Html.LabelFor(m => m.LoseReward) %>*</strong> <em>(only "Lootbox" type supported)</em>:</div>
<fieldset style="border: solid green 2px;">
  <%= Html.EditorFor(m => m.LoseReward) %>
</fieldset>

<%--Steps--%>
<div class="editor-label">
  <strong><%= Html.LabelFor(m => m.Steps) %>*:</strong>
  <button name="command" type="submit" value="<%=Model.CommandPrefix %>step_add:0" style="color: darkgreen">ADD</button>
</div>
<% if (Model.Steps.Count > 0) { %>
  <div>
    <% for (int i = 0; i < Model.Steps.Count; i++) { %>
      <fieldset style="border: solid blue 2px;">
        <legend>
          <span>Step #<%=Model.Index+1 %>-<%=i+1 %></span>
          <button name="command" type="submit" value="<%=Model.CommandPrefix %>step_up:<%=i %>"<%= (i == 0) ? " disabled=\"disabled\"" : "" %>>&uarr;</button>
          <button name="command" type="submit" value="<%=Model.CommandPrefix %>step_down:<%=i %>"<%= (i == Model.Steps.Count - 1) ? " disabled=\"disabled\"" : "" %>>&darr;</button>
          <button name="command" type="submit" value="<%=Model.CommandPrefix %>step_clone:<%=i %>" style="color: darkgreen">COPY</button>
          <button name="command" type="submit" value="<%=Model.CommandPrefix %>step_remove:<%=i %>" style="color: darkred">DEL</button>
        </legend>
        <details open="open">
          <summary>Expand</summary>
          <%= Html.EditorFor(m => m.Steps[i]) %>
        </details>
      </fieldset>
    <% } %>
  </div>
<% } %>
