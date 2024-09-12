<%@ Page Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
Prime World
</asp:Content>

<asp:Content ID="styles" ContentPlaceHolderID="Links" runat="server">
  <style type="text/css">
    .montable, .montable * { border: 0px; }
    td.inf { font-weight: bold }
  </style>
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <h2><%= Html.Encode(ViewData["Message"]) %></h2>

  <p style="font-weight: bold; font-size: 1.12em; margin-top: 50px;">Version info</p>
  <table class="montable">
    <tr>
      <td>Social server : </td>
      <td class="inf"><%= Html.Encode(ViewData["SocVersion"])%></td>
    </tr>
    <tr>
      <td>PvX server : </td>
      <td class="inf"><%= Html.Encode(ViewData["PvXVersion"])%></td>
    </tr>
    <tr>
      <td>Game tools : </td>
      <td class="inf"><%= Html.Encode(ViewData["GameToolsVersion"])%></td>
    </tr>
  </table>
</asp:Content>


