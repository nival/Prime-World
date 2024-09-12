<%@ Page Title="PlayerWipe" Language="C#" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.GM.Models.PlayerWipeModel>" MasterPageFile="~/Views/Shared/Site.Master" %>

<asp:Content runat="server" ID="Title" ContentPlaceHolderID="TitleContent">
    PlayerWipe
</asp:Content>

<asp:Content runat="server" ID="Main" ContentPlaceHolderID="MainContent">
    <% using (Html.BeginForm())
       { %>

        <fieldset>
        <legend>Find Account By NickName</legend>
            <%--FoundAccountByNick.NickName--%>
            <div class="editor-label"><strong><%= Html.LabelFor(m => m.NickName) %></strong></div>
            <div class="editor-field"><%= Html.EditorFor(m => m.NickName)%></div>
            
            <% if (Model.FoundAccountByNick != null) %>
            <% { %>

            <fieldset>
                <legend>Response</legend>
                <%= Html.EditorFor(m => m.FoundAccountByNick) %>
            </fieldset>

            <% } %>
            
            <button name="command" type="submit" value="<%= PlayerWipeModel.CommandFindAccountByNick %>" style="color: darkgreen">Search !</button>
        </fieldset>
        <% } %>    
        <% using (Html.BeginForm())
           { %>
        <fieldset>
            <legend>Find Account By Email</legend>
            <%--FoundAccountByNick.Email--%>
            <div class="editor-label"><strong><%= Html.LabelFor(m => m.Email) %></strong></div>
            <div class="editor-field"><%= Html.EditorFor(m => m.Email)%></div>
            
            <% if (Model.FoundAccountByEmail != null) %>
            <% { %>

            <fieldset>
                <legend>Response</legend>
                <%= Html.EditorFor(m => m.FoundAccountByEmail) %>
            </fieldset>

            <% } %>
        
            <button name="command" type="submit" value="<%= PlayerWipeModel.CommandFindAccountByEmail %>" style="color: darkgreen">Search !</button>
        </fieldset>
        <% } %>    
        <% using (Html.BeginForm())
            { %>
        <fieldset>
            <legend>Account Change Email</legend>
            <%--Email--%>
            <div class="editor-label"><strong><%= Html.LabelFor(m => m.Email) %></strong></div>
            <div class="editor-field"><%= Html.EditorFor(m => m.Email)%></div>
            
            <%--NewEmail--%>
            <div class="editor-label"><strong><%= Html.LabelFor(m => m.NewEmail) %></strong></div>
            <div class="editor-field"><%= Html.EditorFor(m => m.NewEmail)%></div>
            
            <%--NewPassword--%>
            <div class="editor-label"><strong><%= Html.LabelFor(m => m.NewPassword) %></strong></div>
            <div class="editor-field"><%= Html.EditorFor(m => m.NewPassword)%></div>
            
            <% if (Model.EditedAccountAfterChangeEmail != null) %>
            <% { %>

            <fieldset>
                <legend>AccountAfterChange</legend>
                <%= Html.EditorFor(m => m.EditedAccountAfterChangeEmail) %>
            </fieldset>

            <% } %>
        
            <button name="command" type="submit" value="<%= PlayerWipeModel.CommandChangeAccountEmail %>" style="color: darkgreen">Change!</button>
        </fieldset>
        <% } %>    
            <% using (Html.BeginForm())
             { %>
        <fieldset>
            <legend>Account Wipe</legend>
            <%--FoundAccountByNick.Email--%>
            <div class="editor-label"><strong><%= Html.LabelFor(m => m.Email)%></strong></div>
            <div class="editor-field"><%= Html.EditorFor(m => m.Email)%></div>
            
            <div class="editor-label"><strong><%= Html.LabelFor(m => m.NickName)%></strong></div>
            <div class="editor-field"><%= Html.EditorFor(m => m.NickName)%></div>
                        
            <% if (Model.EditedAccountAfterWipe != null) %>
               <% { %>

                <fieldset>
                    <legend>Wiped Account:</legend>
                    <%= Html.EditorFor(m => m.EditedAccountAfterWipe) %>
                </fieldset>

              <% } %>
            
        
            <button name="command" type="submit" value="<%= PlayerWipeModel.CommandWipeAccount %>" style="color: darkgreen">Wipe!</button>
        </fieldset>
    <% } %>    

</asp:Content>

