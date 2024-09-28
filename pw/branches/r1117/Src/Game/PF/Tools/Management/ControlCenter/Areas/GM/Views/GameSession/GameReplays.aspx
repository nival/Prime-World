<%@ Page Title="" Language="C#" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.GM.Models.GameReplayModel>" MasterPageFile="~/Views/Shared/Site.Master" %>

<asp:Content runat="server" ID="Title" ContentPlaceHolderID="TitleContent">
Game replays
</asp:Content>

<asp:Content runat="server" ID="Main" ContentPlaceHolderID="MainContent">
  <h2 style="color:Red">Search replays</h2>

  <% using (Html.BeginForm()) {%>
  <%= Html.ValidationSummary(true) %>
  <fieldset>
    <legend>Fields</legend>
    
    <div class="editor-label">
      <%= Html.LabelFor(model => model.Hostname) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor( model => model.Hostname )%>
      <%= Html.ValidationMessageFor( model => model.Hostname )%>
    </div>

    <div class="editor-label">
      <%= Html.LabelFor(model => model.Date) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor( model => model.Date )%>
      <%= Html.ValidationMessageFor( model => model.Date )%>
    </div>

    <div class="editor-label">
      <%= Html.LabelFor(model => model.GameSessionId) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor( model => model.GameSessionId )%>
      <%= Html.ValidationMessageFor( model => model.GameSessionId )%>
    </div>
    <% if (Model.Replays.Count > 0) { %>
          <table>
       <%   foreach ( var replay in Model.Replays )
         { %> 
         <tr>
            <td><%= Html.Encode(replay.Name) %> </td>
            <td><%= Html.ActionLink( "Download", "DownloadReplay", new { replayLink = replay.Link } )%></td>
        </tr>        
         <% }%>
         </table>
     <% }%>
     <% if (Model.ErrorIfExistToShow != "") { %>
        <div><%= Html.Encode( Model.ErrorIfExistToShow )%></div>
     <% }%>
    <input type="submit" value="Search" style="margin:15px 0 0 0"/>
  </fieldset>
  <% } %>


</asp:Content>
