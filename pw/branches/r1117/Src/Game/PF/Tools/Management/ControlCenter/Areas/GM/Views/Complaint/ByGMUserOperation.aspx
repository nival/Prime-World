<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<IEnumerable<ControlCenter.Areas.GM.Models.ComplaintInfoModel>>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	Complaints for ban/mute
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

<h2>Complaints for ban/mute</h2>
<% var banmuteModel = (BanOrMuteHistoryModel) ViewData["gmuseroperation"]; %>
<div style="margin-bottom: 20px">
  auid : <%= banmuteModel.Auid %><br/>
  type : <%= banmuteModel.EventType %><br/>
  time : <%= banmuteModel.Time %><br/>
  reason : <%= banmuteModel.Reason %><br/>
</div>

  <table>
    <tr>
      <th>Player</th>
      <th>Source</th>
      <th>Category</th>
      <th class="timeZoneLabel">Timestamp, UTC+0</th>
      <th>Comment</th>
      <th>ChatLog</th>
      <th>GameSessionInfo</th>
    </tr>
    <% foreach (var item in Model) { %>
      <tr>
        <td><%= Html.Encode(String.Format("{0} (auid={1})", item.FromPlayerNickname, item.FromPlayerAuid))%></td>
        <td><%= Html.Encode(item.Source) %></td>
        <td><%= Html.Encode(item.Category) %></td>
        <td class="utcdateVal"><%= Html.Encode(item.Timestamp.ToString("dd.MM.yyyy HH:mm:ss"))%></td>
        <td><%= Html.Encode(item.Comment).Replace("\n", "<br/>")%></td>
        <td><%= Html.Encode(item.ChatLog).Replace("\n", "<br/>")%></td>
        <td><%= Html.Encode(item.GameSessionInfo).Replace("\n", "<br/>")%></td>
       </tr>
    <% } %>
  </table>
  
  <div style="margin-top: 20px">
    <%= Html.ActionLink("Back to the ban/mute history", "BanAndMuteHistory", "HistoryUI", new {banmuteModel.Auid}, null) %>
  </div>

</asp:Content>
