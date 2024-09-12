<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<UserInfoModel>" %>
<%@ Import Namespace="ControlCenter.Areas.Admin.Models"%>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	EditRoles
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <h2>Roles of user <%= Html.Encode(Model.UserName) %></h2>

  <% using (Html.BeginForm()) {%>
    <fieldset>
      <legend>Roles</legend>
      
      <%= Html.HiddenFor(model => model.UserId) %>
      <%= Html.HiddenFor(model => model.UserName) %>
      
      <div style="margin-top: 15px;">
      <% var roles = (Dictionary<int, string>) ViewData["AllRoles"];
         foreach (var p in roles.OrderBy(pair => pair.Value))
         { %>
           <div class="editor-field">
             <%-- Html.CheckBox too weird to use it --%>
             <% if (Model.Roles.ContainsKey(p.Key)) { %>
               <input type="checkbox" name="chkRoles" value="<%= p.Key %>" checked="checked" />
             <% } else { %>
               <input type="checkbox" name="chkRoles" value="<%= p.Key %>" />
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
    <%= Html.ActionLink("Cancel", "Details", new { id = Model.UserId}) %>
  </div>


</asp:Content>
