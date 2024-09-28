<%@ Page Title="" Language="C#" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.GM.Models.TournamentInfoModel>" MasterPageFile="~/Views/Shared/Site.Master" %>

<%@ Import Namespace="ControlCenter.Areas.GM.Models" %>
<asp:Content runat="server" ID="cTitle" ContentPlaceHolderID="TitleContent">
Edit Tournament Info
</asp:Content>

<asp:Content runat="server" ID="cMain" ContentPlaceHolderID="MainContent">
  <h2>Tournament Info</h2>
  <% using (Html.BeginForm()) {%>
  <div style="font-size: 1.2em; color: #000000; margin-bottom: 15px;">
    Account: <%= ViewData["login"] %>
  </div>
  <%= Html.ValidationSummary(true) %>
  <fieldset>
    <legend>Fields</legend>
    <%= Html.HiddenFor( model => model.Login ) %>
    
    <div class="editor-label">
      <%= Html.LabelFor( model => model.Wins ) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor( model => model.Wins )%>
      <%= Html.ValidationMessageFor( model => model.Wins )%>
    </div>

    <div class="editor-label">
      <%= Html.LabelFor( model => model.Losses ) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor( model => model.Losses )%>
      <%= Html.ValidationMessageFor( model => model.Losses )%>
    </div>

    <div class="editor-label">
      <%= Html.LabelFor( model => model.LastGameTime ) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => Model.LastGameTime)%>
      <%= Html.ValidationMessageFor( model => model.LastGameTime )%>
    </div>

    <div class="editor-label">
      <%= Html.LabelFor( model => model.TicketPriseState )%>
    </div>
    <div class="editor-field">
      <%= Html.DropDownListFor(model => model.TicketPriseState, new SelectList((Enum.GetValues(typeof(TicketPriseStateEnum))).Cast<TicketPriseStateEnum>().Take(3)))%>
      <%= Html.ValidationMessageFor( model => model.TicketPriseState )%>
    </div>
    
    <div class="editor-label">
      <%= Html.LabelFor( model => model.TicketBoughtType )%>
    </div>
    <div class="editor-field">
      <%= Html.DropDownListFor( model => model.TicketBoughtType, new SelectList( ( Enum.GetValues( typeof( TicketBoughtTypeEnum ) ) ).Cast<TicketBoughtTypeEnum>().Take( 4 ) ) )%>
      <%= Html.ValidationMessageFor( model => model.TicketBoughtType )%>
    </div>
    
    <div class="editor-label">
      <%= Html.LabelFor( model => model.State )%>
    </div>
    <div class="editor-field">
      <%= Html.DropDownListFor(model => model.State, new SelectList((Enum.GetValues(typeof(TicketStateEnum))).Cast<TicketStateEnum>().Take(3)))%>
      <%= Html.ValidationMessageFor( model => model.State )%>
    </div>
    
    <div class="editor-label">
      <%= Html.LabelFor(model => model.MissedGames)%>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.MissedGames)%>
      <%= Html.ValidationMessageFor(model => model.MissedGames)%>
    </div>
    
    <div class="editor-label">
      <%= Html.LabelFor(model => model.IsSynchronized)%>
    </div>
    <div class="editor-field">
      <%= Html.CheckBoxFor(model => model.IsSynchronized, new { @disabled = "disabled" })%>
      <%= Html.ValidationMessageFor( model => model.IsSynchronized)%>
    </div>

    <input type="submit" value="Save" style="margin:15px 0 0 0"/><input type="submit" value="Synchronize" style="margin:15px 0 0 0"/>
  </fieldset>
  <% } %>
  
  <div>
    <p><%= Html.ActionLink("Back to account details", "Details", new { login = ViewData["login"] })%></p>
    <p><%= Html.ActionLink("View tournament games", "TournamentGames", new { login = ViewData["login"] })%></p>
    <p><%= Html.ActionLink("Give tournament ticket", "TournamentTicketGiven", new { login = ViewData["login"] })%></p>
  </div>

</asp:Content>

