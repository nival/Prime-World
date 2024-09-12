<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<PlayerComplaintInfosModel>" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
  Complaints
</asp:Content>

<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">
  <script type="text/javascript" src="../../Scripts/jquery.localizeDate.js"></script>
  <script type="text/javascript">
    $(document).ready(function() {
      localizeDate();
    });
  </script>
</asp:Content>

<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">

<h2>Complaints for user <%= Model.Nickname %> (auid = <%= Model.Auid %>)</h2>
<% if (Model.Results.Count > 0) { %>
  <table style="table-layout: fixed; width:100%">
    <tr>
      <th><%= Html.SortingLink(m => m.Results[0].FromPlayerNickname, "Complaints", Model, true)%></th>
      <th><%= Html.SortingLink(m => m.Results[0].Source, "Complaints", Model, true)%></th>
      <th><%= Html.SortingLink(m => m.Results[0].Category, "Complaints", Model, true)%></th>
      <th><%= Html.SortingLink(m => m.Results[0].Locale, "Complaints", Model, true)%></th>
      <th style="width: 80px" class="timeZoneLabel"><%= Html.SortingLink(m => m.Results[0].Timestamp, "Complaints", Model, true)%></th>
      <th><%= Html.SortingLink(m => m.Results[0].Comment, "Complaints", Model, true)%></th>
      <th width="45%">ChatLog</th>
      <th width="15%">GameSessionInfo</th>
    </tr>
    <% foreach (var item in Model.Results) { %>
      <tr>
        <td><%= Html.Encode(String.Format("{0} (auid={1})", item.FromPlayerNickname, item.FromPlayerAuid))%></td>
        <td><%= Html.Encode(item.Source) %></td>
        <td><%= Html.Encode(item.Category) %></td>
        <td><%= Html.Encode(item.Locale) %></td>
        <td class="utcdateVal"><%= Html.Encode(item.Timestamp.ToString("dd.MM.yyyy HH:mm:ss"))%></td>
        <td><%= Html.Encode(item.Comment).Replace("\n", "<br/>")%></td>
        <td><%= Html.Encode(item.ChatLog).Replace("\n", "<br/>")%></td>
        <td><%= Html.Encode(item.GameSessionInfo).Replace("\n", "<br/>")%></td>
       </tr>
    <% } %>
  </table>
<% } %>
</asp:Content>
