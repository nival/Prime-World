<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.GM.Models.HeroInfoModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	AddHero
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

    <h2>Add Hero</h2>
    
    <% if ( (int)ViewData["noNeedToShowEditResult"] == 0 ) { %>
    <b>Successfullу Added</b>
    <% } else if ( (int)ViewData["noNeedToShowEditResult"] == -1 ) { %>
    <b>Errors In Adding</b>
    <% } %>

    <% using (Html.BeginForm()) {%>
        <%= Html.ValidationSummary(true) %>

        <fieldset>
            <legend>Fields</legend>
            
            <div class="editor-label">
                <%= Html.LabelFor(model => model.HeroName) %>
            </div>
            <div class="editor-field">
                <%= Html.TextBoxFor(model => model.HeroName) %>
                <%= Html.ValidationMessageFor(model => model.HeroName) %>
            </div>
            
            <div class="editor-label">
                <%= Html.LabelFor(model => model.Experience) %>
            </div>
            <div class="editor-field">
                <%= Html.TextBoxFor(model => model.Experience) %>
                <%= Html.ValidationMessageFor(model => model.Experience) %>
            </div>            

            <div class="editor-label">
                <%= Html.LabelFor(model => model.EpicWins) %>
            </div>
            <div class="editor-field">
                <%= Html.TextBoxFor( model => model.EpicWins )%>
                <%= Html.ValidationMessageFor( model => model.EpicWins )%>
            </div>
            
            <p>
                <input type="submit" value="Create" />
            </p>
        </fieldset>

    <% } %>

    <div>
        <%= Html.ActionLink("Back to hero list", "Heroes", new { login = ViewData["login"] } ) %>
    </div>

</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>

