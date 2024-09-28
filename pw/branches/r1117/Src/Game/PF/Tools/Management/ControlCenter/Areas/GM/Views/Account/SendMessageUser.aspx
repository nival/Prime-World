<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.GM.Models.SendMessageModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	SendMessageUser
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

    <div style="font-size: 1.2em; color: #000000; margin-bottom: 15px;">
      <%= Html.Encode( String.Format( "Send Message to user : {0}", ViewData["login"] )) %>
    </div>
    
    <div>
      <% if ( (int)ViewData["noNeedToShowResult"] == 0 ) { %>
        <b>Successfully Executed</b>
      <% } else if ( (int)ViewData["noNeedToShowResult"] == -1 ) { %>
        <b>Errors In Sending</b>
    <% } %>
  </div>
    
    <% using (Html.BeginForm()) {%>
        <%= Html.ValidationSummary(true) %>
        
        <fieldset>
            <legend>Fields</legend>
            
            <div class="editor-label">
                <%= Html.LabelFor(model => model.MessageTitle) %>
            </div>
            <div class="editor-field">
                <%= Html.TextBoxFor(model => model.MessageTitle) %>
                <%= Html.ValidationMessageFor(model => model.MessageTitle) %>
            </div>
            
            <div class="editor-label">
                <%= Html.LabelFor(model => model.MessageText) %>
            </div>
            <div class="editor-field">
                <%= Html.TextAreaFor( model => model.MessageText, new { cols = "50%", rows = "10" } )%>
                <%= Html.ValidationMessageFor(model => model.MessageText) %>
            </div>
            
            <p>
                <input type="submit" value="Send Message" />
            </p>
        </fieldset>

    <% } %>

    <div>
        <%= Html.ActionLink( "back to account", "Details", new { login = ViewData["login"] } )%>
    </div>

</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>

