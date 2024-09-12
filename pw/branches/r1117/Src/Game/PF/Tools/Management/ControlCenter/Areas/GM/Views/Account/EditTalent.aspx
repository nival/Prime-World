<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.GM.Models.TalentInfoModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	EditTalent
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

    <% if ( (string)ViewData["cameFrom"] == "TalentSet" ){ %>
      <div style="font-size: 1.2em; color: #000000; margin-bottom: 15px;">
        <%= Html.Encode( String.Format( "Edit Talent of Login: {0}, HeroName: {1}, HeroInstanceId: {2}", ViewData["login"], ViewData["heroName"], ViewData["heroInstanceId"] ) )%>
      </div>
    <% } else { %>
      <div style="font-size: 1.2em; color: #000000; margin-bottom: 15px;">
        <%= Html.Encode( String.Format( "Edit Talent of Login: {0}", ViewData["login"] )) %>
      </div>
    <% } %>

    <% using (Html.BeginForm()) { %>
        <%= Html.ValidationSummary() %>
        
        <fieldset>
            <legend>Fields</legend>
            
            <div class="editor-label">
                <%= Html.LabelFor(model => model.TalentName) %>: <%= Html.Encode(Model.TalentName) %>
            </div>
            <br />
            
            <div class="editor-label">
                <%= Html.LabelFor(model => model.RefineRate) %>
            </div>
            <div class="editor-field">
                <%= Html.TextBoxFor(model => model.RefineRate) %>
                <%= Html.ValidationMessageFor(model => model.RefineRate) %>
            </div>

            <div class="editor-label">
                <%= Html.LabelFor(model => model.BoundHeroClassName) %>
            </div>
            <div class="editor-field">
                <%= Html.DropDownListFor(m => m.BoundHeroInstanceId,
                                         new SelectList((List<HeroInfoModel>)ViewData["allheroes"], "HeroInstanceId", "HeroName"),
                                         new { style = "width:200px;" })%>
            </div>

            <p style="margin-top: 30px">
                <input type="submit" value="Save" />
            </p>
        </fieldset>

    <% } %>

    <div>
    <% if ( (string)ViewData["cameFrom"] == "TalentSet" ){ %>
        <%= Html.ActionLink( "Back to talent set", "TalentSet", new { login = ViewData["login"], heroInstanceId = ViewData["heroInstanceId"], heroName = ViewData["heroName"] } )%>
    <% } else { %>
        <%= Html.ActionLink( "Back to library", "Library", new { login = ViewData["login"] } )%>
    <% } %>
    </div>

</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>

