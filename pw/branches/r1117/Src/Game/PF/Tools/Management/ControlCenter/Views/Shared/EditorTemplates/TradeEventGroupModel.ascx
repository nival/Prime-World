<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<TradeEventGroupModel>" %>
<%@ Import namespace="ControlCenter.Areas.EventTool.Models" %>

<%--Name--%>
<div class="editor-label"><strong><%= Html.LabelFor(m => m.Name)%>*:</strong></div>
<div class="editor-field">
  <%= Html.EditorFor(m => m.Name)%>
  <%= Html.ValidationMessageFor(m => m.Name)%>
</div>

<%--TradeGroupMembers--%>
<div class="editor-label">
  <strong><%= Html.LabelFor(m => m.TradeGroupMembers)%>*:</strong>
  <button name="command" type="submit" value="<%=Model.CommandPrefix + TradeEventModel.MemberNameCommand %>_add:0" style="color: darkgreen">ADD</button>
</div>
<% if (Model.TradeGroupMembers.Count > 0)
   { %>
  <div>
    <% for (int i = 0; i < Model.TradeGroupMembers.Count; i++)
       { %>
      <fieldset style="border: solid darkgoldenrod 2px;">
        <legend>
          <span>TradeGroupMember #<%=i+1 %></span>
          <button name="command" type="submit" value="<%=Model.CommandPrefix + TradeEventModel.MemberNameCommand%>_up:<%=i %>"<%= (i == 0) ? " disabled=\"disabled\"" : "" %>>&uarr;</button>
          <button name="command" type="submit" value="<%=Model.CommandPrefix + TradeEventModel.MemberNameCommand%>_down:<%=i %>"<%= (i == Model.TradeGroupMembers.Count - 1) ? " disabled=\"disabled\"" : "" %>>&darr;</button>
          <button name="command" type="submit" value="<%=Model.CommandPrefix + TradeEventModel.MemberNameCommand%>_clone:<%=i %>" style="color: darkgreen">COPY</button>
          <button name="command" type="submit" value="<%=Model.CommandPrefix + TradeEventModel.MemberNameCommand%>_remove:<%=i %>" style="color: darkred">DEL</button>
        </legend>
          <details open="open">
          <summary>Expand</summary>
          <%= Html.EditorFor(m => m.TradeGroupMembers[i])%>
        </details>
      </fieldset>
    <% } %>
  </div>
<% } %>
