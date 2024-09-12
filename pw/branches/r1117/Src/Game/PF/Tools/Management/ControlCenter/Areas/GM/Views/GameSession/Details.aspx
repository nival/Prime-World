<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<GameSessionShortInfoModel>" %>

<%@ Import Namespace="ControlCenter.Areas.GM.Models" %>
<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
  Game session info
</asp:Content>
<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">
  <link rel="stylesheet" href="/Content/gm-sessions.css" />
</asp:Content>
<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">
  <div id="pagemenu" style="width: 30%; float: right; margin-right: 0px">
  </div>
  <div id="pagecontent" style="width: 70%">
    <h2>Game session info</h2>
    <div style="font-size: 1.2em; color: #000000; margin-bottom: 15px;">
      <%= Html.Encode(String.Format("Game session id: {0}", Model.GameSessionId)) %>
    </div>
    <div style="margin: 40px 0 10px 0;">
      Team docts</div>
    <table class="docts">
      <thead>
        <tr>
          <th width="50">
            <%= Html.LabelFor(m => m.TeamAdorni.FirstOrDefault().SNid) %>
          </th>
          <th width="100">
            <%= Html.LabelFor(m => m.TeamAdorni.FirstOrDefault().SNUid) %>
          </th>
          <th width="50">
            <%= Html.LabelFor(m => m.TeamAdorni.FirstOrDefault().Login) %>
          </th>
          <th width="100">
            <%= Html.LabelFor(m => m.TeamAdorni.FirstOrDefault().NickName) %>
          </th>
          <th width="100">
            <%= Html.LabelFor(m => m.TeamAdorni.FirstOrDefault().Email) %>
          </th>
        </tr>
      </thead>
      <tbody>
        <% foreach ( AccountShortInfoModel account in Model.TeamDocts )
           { %>
        <tr>
          <td>
            <%= Html.Encode(account.SNid) %>
          </td>
          <td>
            <%= Html.Encode(account.SNUid) %>
          </td>
          <td>
            <%= Html.Encode(account.Login) %>
          </td>
          <td>
            <%= Html.Encode(account.NickName) %>
          </td>
          <td>
            <%= Html.Encode(account.Email) %>
          </td>
          <td>
            <%= Html.ActionLink("View", "Details", "Account", new { snid = account.SNid, snuid = account.SNUid}, null) %>
          </td>
        </tr>
        <% } %>
      </tbody>
    </table>
    <div style="margin: 40px 0 10px 0;">
      Team Adorni</div>
    <table class="adorni">
      <thead>
        <tr>
          <th width="50">
            <%= Html.LabelFor(m => m.TeamAdorni.FirstOrDefault().SNid) %>
          </th>
          <th width="100">
            <%= Html.LabelFor(m => m.TeamAdorni.FirstOrDefault().SNUid) %>
          </th>
          <th width="50">
            <%= Html.LabelFor(m => m.TeamAdorni.FirstOrDefault().Login) %>
          </th>
          <th width="100">
            <%= Html.LabelFor(m => m.TeamAdorni.FirstOrDefault().NickName) %>
          </th>
          <th width="100">
            <%= Html.LabelFor(m => m.TeamAdorni.FirstOrDefault().Email) %>
          </th>
        </tr>
      </thead>
      <tbody>
        <% foreach ( AccountShortInfoModel account in Model.TeamAdorni )
           { %>
        <tr>
          <td>
            <%= Html.Encode(account.SNid) %>
          </td>
          <td>
            <%= Html.Encode(account.SNUid) %>
          </td>
          <td>
            <%= Html.Encode(account.Login) %>
          </td>
          <td>
            <%= Html.Encode(account.NickName) %>
          </td>
          <td>
            <%= Html.Encode(account.Email) %>
          </td>
          <td>
            <%= Html.ActionLink("View", "Details", "Account", new { login = account.Login, snid = account.SNid, snuid = account.SNUid}, null) %>
          </td>
        </tr>
        <% } %>
      </tbody>
    </table>
  </div>
</asp:Content>
