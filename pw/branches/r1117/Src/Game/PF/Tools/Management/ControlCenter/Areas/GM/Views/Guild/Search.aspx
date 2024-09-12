<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.GM.Models.GuildSearchModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
  Search
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
  <style type="text/css">
    table, table td {
      border: 0px;
    }
  </style>
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <h2>Guild Search</h2>
  <% using (Html.BeginForm()) {%>
  <%= Html.ValidationSummary(true) %>
  <fieldset>
    <legend>Search by id</legend>
    <table>
      <tr>
        <td><%= Html.LabelFor(model => model.GuildId) %></td>
        <td>
          <%= Html.TextBoxFor(model => model.GuildId) %>
          <%= Html.ValidationMessageFor(model => model.GuildId) %>
        </td>
      </tr>
      <tr>
        <td><input type="submit" name="searchById" value="Search" /></td>
      </tr>
    </table>
  </fieldset>
  <% } %>
  
  <% using (Html.BeginForm()) {%>
  <%= Html.ValidationSummary(true) %>
  <fieldset>
    <legend>Search by name</legend>
    <table>
      <tr>
        <td><%= Html.LabelFor(model => model.ShortName)%></td>
        <td>
          <%= Html.TextBoxFor(model => model.ShortName)%>
          <%= Html.ValidationMessageFor(model => model.ShortName)%>
        </td>
      </tr>
      <tr>
        <td><%= Html.LabelFor(model => model.FullName)%></td>
        <td>
          <%= Html.TextBoxFor(model => model.FullName)%>
          <%= Html.ValidationMessageFor(model => model.FullName)%>
        </td>
      </tr>
      <tr>
        <td><input type="submit" name="searchByName" value="Search" /></td>
      </tr>
    </table>
  </fieldset>
  <% } %>

</asp:Content>