<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<BrokenAccountsModel>" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
Broken accounts
</asp:Content>

<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">
  
</asp:Content>


<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">
  
<div id="pagemenu" style="width: 30%; float: right; margin-right: 0px">
  <p><%= Html.ActionLink("Back", "Index")%></p>
</div>
  
<div id="pagecontent" style="width: 70%">

  <h2>Get old dump for user</h2>
  
  <% using (Html.BeginForm()) { %>
    
    <div class="editor-label">
        <%= Html.LabelFor( m => m.Login )%>
    </div>
    <div class="editor-field">  
        <%= Html.TextBoxFor(m => m.Login)%>
        <%= Html.ValidationMessageFor(model => model.Login ) %>
    </div>
    <div class="editor-label">
        <%= Html.LabelFor( m => m.Nickname )%>
    </div>
    <div class="editor-field">  
        <%= Html.TextBoxFor( m => m.Nickname )%>
        <%= Html.ValidationMessageFor( model => model.Nickname )%>
    </div>
    <div class="editor-label">
        <td><%= Html.LabelFor(m => m.BackupDate) %></td>
    </div>
    <div class="editor-field">
        <td><%= Html.DropDownListFor( m => m.BackupDate, (SelectList)ViewData["BackupDates"] )%></td>
    </div>
    
    <p><input type="submit" value="Download"/></p>
    
  <% } %>
  
</div>

</asp:Content>

