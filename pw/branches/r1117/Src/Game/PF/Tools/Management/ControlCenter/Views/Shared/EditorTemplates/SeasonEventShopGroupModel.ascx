<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<SeasonEventShopGroupModel>" %>
<%@ Import namespace="ControlCenter.Areas.EventTool.Models" %>

<%--Name--%>
<div class="editor-label"><strong><%= Html.LabelFor(m => m.Name)%>*:</strong></div>
<div class="editor-field">
  <%= Html.EditorFor(m => m.Name)%>
  <%= Html.ValidationMessageFor(m => m.Name)%>
</div>

<%--TradeGroupMembers--%>
<div class="editor-label">
  <strong><%= Html.LabelFor(m => m.Items)%>*:</strong>
  <button name="command" type="submit" value="<%=Model.CommandPrefix + SeasonEventModel.MemberNameCommand %>_add:0" style="color: darkgreen">ADD</button>
</div>
<% if (Model.Items.Count > 0)
   { %>
  <div>
    <% for (int i = 0; i < Model.Items.Count; i++)
       { %>
      <fieldset style="border: solid darkgoldenrod 2px;">
        <legend>
          <span>ShopItem #<%=i+1 %></span>
          <button name="command" type="submit" value="<%=Model.CommandPrefix + SeasonEventModel.MemberNameCommand%>_up:<%=i %>"<%= (i == 0) ? " disabled=\"disabled\"" : "" %>>&uarr;</button>
          <button name="command" type="submit" value="<%=Model.CommandPrefix + SeasonEventModel.MemberNameCommand%>_down:<%=i %>"<%= (i == Model.Items.Count - 1) ? " disabled=\"disabled\"" : "" %>>&darr;</button>
          <button name="command" type="submit" value="<%=Model.CommandPrefix + SeasonEventModel.MemberNameCommand%>_clone:<%=i %>" style="color: darkgreen">COPY</button>
          <button name="command" type="submit" value="<%=Model.CommandPrefix + SeasonEventModel.MemberNameCommand%>_remove:<%=i %>" style="color: darkred">DEL</button>
        </legend>
          <details open="open">
          <summary>Expand</summary>
          <%= Html.EditorFor(m => m.Items[i])%>
        </details>
      </fieldset>
    <% } %>
  </div>
<% } %>
