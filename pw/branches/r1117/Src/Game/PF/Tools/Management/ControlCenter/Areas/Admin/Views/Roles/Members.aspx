<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<RoleInfoModel>" %>
<%@ Import Namespace="ControlCenter.Areas.Admin.Models"%>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	RoleMembers
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <h2>Members of role "<%= Html.Encode(Model.RoleName) %>"</h2>
  <% using (Html.BeginForm()) {%>
    <fieldset>
      <legend>Members</legend>
      
      <%= Html.HiddenFor(model => model.RoleId) %>
      <%= Html.HiddenFor(model => model.RoleName) %>
      <%= Html.HiddenFor(model => model.Description) %>
      
      <div style="margin-top: 15px;">
      <% var users = (Dictionary<int, string>) ViewData["AllUsers"];
         foreach (var p in users.OrderBy(pair => pair.Value))
         { %>
           <div class="editor-field">
             <%-- Html.CheckBox too weird to use it --%>
             <% if (Model.Users.ContainsKey(p.Key)) { %>
               <input type="checkbox" name="chkUsers" value="<%= p.Key %>" checked="checked" />
             <% } else { %>
               <input type="checkbox" name="chkUsers" value="<%= p.Key %>" />
             <% } %>
             <%= Html.Encode(p.Value) %>
           </div>
      <% } %>
      </div>

      <p>
        <input type="submit" value="Save" />
      </p>
    </fieldset>
  <% } %>

  <div>
    <%= Html.ActionLink("Cancel", "Details", new { id = Model.RoleId }) %>
  </div>

</asp:Content>

