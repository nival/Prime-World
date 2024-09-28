<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.GM.Models.GiveTournamentTicketModel>" %>

<asp:Content runat="server" ID="cTitle" ContentPlaceHolderID="TitleContent">
Give Tournament Ticket
</asp:Content>

<asp:Content runat="server" ID="cMain" ContentPlaceHolderID="MainContent">
  <h2>User <%= ViewData["login"] %> now has a tournament ticket</h2>
  <p><%= Html.ActionLink("Back to account details", "Details", new { login = ViewData["login"] })%></p>
</asp:Content>

