<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<AuidListMemberModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
  Index
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <link href="/Content/jquery-ui-1.8.17.custom.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Scripts/jquery-ui-1.8.16.custom.min.js"></script>
    <script type="text/javascript" src="/Scripts/jquery.localizeDate.js"></script>
    <script type="text/javascript" src="/Scripts/jquery-ui-timepicker-addon.js"></script>
    <script type="text/javascript" src="/Scripts/jquery-ui-sliderAccess.js"></script>
    <script type="text/javascript" src="/Scripts/CommonScripts.js"></script>
    
    <% if (!String.IsNullOrEmpty(ViewData["Warning"] as String))
       { %>
    <p style="background-color:yellow;color:red">
        <b>
            <%=((String) ViewData["Warning"]) %>
        </b>
    </p>
    <% } %>
    <h2>AuidList #<%=Model.Index %></h2>

    <div class="pagemenu">
        <p><%= Html.ActionLink("Back to list", "Index")%></p>
        <br/>
        <p><%= Html.ActionLink("Remove", "RemoveAuidListMember", new {id = Model.Index})%></p>
    </div>

    <%using (Html.BeginForm("AuidListMember", "AuidList", FormMethod.Post, new { enctype = "multipart/form-data" }))
        { %>
    <div class="editor-field">
        <%= Html.HiddenFor(model => model.Index) %>
    </div>
    <div class="editor-label">
        <%= Html.LabelFor(model => model.Description) %>:
    </div>
    <div class="editor-field">
        <%= Html.TextBox("Description", Model.Description, new {id="Description", name="Description"}) %>
        <%= Html.ValidationMessageFor( model => model.Description )%>
    </div>
    <br/>
    <div class="editor-label">
        <%= Html.LabelFor(model => model.Auids) %>:
    </div>
    <div class="editor-field">
        <%= Html.TextAreaFor(model => model.Auids) %>
        <%= Html.ValidationMessageFor( model => model.Auids )%>
    </div>
    <div class="editor-field">
        <%= Html.HiddenFor(model => model.Links) %>
    </div>
    <input type="file" name="file" />
    <br/>
    <input type="submit" value="Edit"/>

    <% } %>
</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>
