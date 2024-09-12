<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.GM.Models.GuildMemberModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	EditMember
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

    <h2>Edit Member </h2>
    <% using (Html.BeginForm()) { %>
        <%= Html.ValidationSummary(true) %>
        
        <fieldset>
            <legend>Fields</legend>
            
            <div class="editor-label">
                <%= Html.LabelFor(model => model.Auid) %>: <%= Html.Encode(Model.Auid)%>
            </div>
            
            <div class="editor-label">
                <%= Html.LabelFor(model => model.IsOfficer) %>
            </div>
            <div class="editor-field">
                <%= Html.CheckBoxFor( model => model.IsOfficer)%>
                <%= Html.ValidationMessageFor(model => model.IsOfficer)%>
            </div>

            <div class="editor-label">
                <%= Html.LabelFor(model => model.AddedTalentsDailyCount) %>
            </div>
            <div class="editor-field">
                <%= Html.TextBoxFor(model => model.AddedTalentsDailyCount)%>
                <%= Html.ValidationMessageFor(model => model.AddedTalentsDailyCount)%>
            </div>
            <div class="editor-label">
                <%= Html.LabelFor(model => model.TakenTalentsDailyCount) %>
            </div>
            <div class="editor-field">
                <%= Html.TextBoxFor(model => model.TakenTalentsDailyCount)%>
                <%= Html.ValidationMessageFor(model => model.TakenTalentsDailyCount)%>
            </div>
            
            <p style="margin-top: 30px">
                <input type="submit" value="Save" />
            </p>
        </fieldset>
        <p><%= Html.ActionLink("Cancel", "ViewMembers", new { id = Model.GuildId })%></p>

    <% } %>

</asp:Content>
