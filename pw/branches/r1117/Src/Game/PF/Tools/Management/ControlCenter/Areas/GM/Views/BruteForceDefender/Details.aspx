<%@ Page Title="" Language="C#" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.GM.Models.BruteForceAccountModel>" MasterPageFile="~/Views/Shared/Site.Master" %>
<%@ Import Namespace="AccountLib" %>

<asp:Content runat="server" ID="Title" ContentPlaceHolderID="TitleContent">
Bruteforce accounts
</asp:Content>

<asp:Content runat="server" ID="Main" ContentPlaceHolderID="MainContent">
  <table>
  <tr><td>
  <h2 style="color:Red">Search bruteforce accounts</h2>
  <p>You need to enter a email only for pwconnect (pwc)-account.</p>
  <% using (Html.BeginForm()) {%>
  <%= Html.ValidationSummary(true) %>
  <fieldset>
    <legend>Fields</legend>
    
    <div class="editor-label">
      <%= Html.LabelFor(model => model.Email) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor( model => model.Email )%>
      <%= Html.ValidationMessageFor( model => model.Email )%>
    </div>
    <input type="submit" value="Search" style="margin:15px 0 0 0"/>
  </fieldset>
  <% } %>
  </td>
  </tr>
  </table>

  <% if (Model.Visible)
     {%>
          <h2 style="color:Red">Results</h2>
     
              <table style="border-style: none">
              <tr>
                <td class="display-label">  <%= Html.LabelFor(model => model.Email) %></td>
                <td class="display-field"> <%= Html.Encode(Model.Email) %></td>
                <td><%= Html.ActionLink("UnBan account", "Unban", "BruteForceDefender", new { email = Model.Email }, null)%></td>
              </tr>
              <tr>
                <td class="display-label"> <%= Html.LabelFor(model => model.BanTime)%></td>
                <td class="display-field"> <%= Html.Encode(Model.BanTime) %></td>
              </tr>
              <tr>
                <td class="display-label"> <%= Html.LabelFor(model => model.Ip) %></td>
                <td class="display-field"> <%= Html.Encode(Model.Ip) %></td>
              </tr>
              <tr>
                <td class="display-label"> <%= Html.LabelFor(model => model.Count) %></td>
                <td class="display-field"> <%= Html.Encode(Model.Count) %></td>
              </tr>
              </table>
   <% } %>
</asp:Content>
