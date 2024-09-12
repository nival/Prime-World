<%@ Page Title="Title" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<NewsBannerModel>" %>
<%@ Import Namespace="ControlCenter.Areas.EventTool.Models" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
News banner
</asp:Content>


<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">

  <link href="/Content/jquery-ui-1.8.17.custom.css" rel="stylesheet" type="text/css" />

  <script type="text/javascript" src="/Scripts/jquery-ui-1.8.16.custom.min.js"></script>
  <script type="text/javascript" src="/Scripts/jquery.localizeDate.js"></script>
  <script type="text/javascript" src="/Scripts/jquery-ui-timepicker-addon.js"></script>
  <script type="text/javascript" src="/Scripts/jquery-ui-sliderAccess.js"></script>

  <script type="text/javascript">


      var InteractionWindowType;
      
        $(document).ready(function () {
            onReady();
        });

        function onReady() {
            localizeDate();
            $('#StartTime').datetimepicker({ dateFormat: 'dd.mm.yy', timeFormat: 'hh:mm:ss', showSecond: true });
            $('#EndTime').datetimepicker({ dateFormat: 'dd.mm.yy', timeFormat: 'hh:mm:ss', showSecond: true });

            InteractionWindowType = eval([<% ="\"" + DynamicQuestInfoModel.GetAllTexts(Model.DataExtensionsList) + "\"" %>]);

        }


        function onSelectType(list) {
            //warn: hardcode!
            switch (list.value.toString()) {
                case 'None':
                    document.getElementById("extensionJsonContainter").innerHTML = '';
                    break;
                case 'Interface':
                    var pattern = "";

                    pattern += "<label class=\"editor-label\">ButtonText</label><br/>";
                    pattern += "<input class=\"editor-field\" id=\"InteractionButtonText\" name=\"InteractionButtonText\" type=\"text\" value=\"\"><br/>";

                    pattern += "<label class=\"editor-label\">Go to Interface</label><br/>";
                    pattern += "<select class=\"editor-field\" id=\"Screen\" name=\"Screen\">";
                    InteractionWindowType.forEach(function (foreachValue) {
                        pattern += "<option>" + foreachValue + "</option>";
                    });
                    pattern += "</select><br/>";

                    pattern += "<label class=\"editor-label\">Parameter</label><br/>";
                    pattern += "<input class=\"editor-field\" id=\"InterfaceArgs\" name=\"InterfaceArgs\" type=\"text\" value=\"\">";

                    document.getElementById("extensionJsonContainter").innerHTML = pattern;
                    break;
                case 'Url':
                    var pattern = "";

                    pattern += "<label class=\"editor-label\">ButtonText</label><br/>";
                    pattern += "<input class=\"editor-field\" id=\"InteractionButtonText\" name=\"InteractionButtonText\" type=\"text\" value=\"\"><br/>";

                    pattern += "<label class=\"editor-label\">Url</label><br/>";
                    pattern += "<input class=\"editor-field\" id=\"InterfaceArgs\" name=\"InterfaceArgs\" type=\"text\" value=\"\">";

                    document.getElementById("extensionJsonContainter").innerHTML = pattern;
                    break;
                case 'Json':
                    var pattern = "";

                    pattern += "<label class=\"editor-label\">ButtonText </label><br/>";
                    pattern += "<input class=\"editor-field\" id=\"InteractionButtonText\" name=\"InteractionButtonText\" type=\"text\" value=\"\"><br/>";

                    pattern += "<label class=\"editor-label\">Raw Json</label><br/>";
                    pattern += "<textarea class=\"editor-field\" id=\"InterfaceArgs\" name=\"InterfaceArgs\" type=\"text\" value=\"\">";

                    document.getElementById("extensionJsonContainter").innerHTML = pattern;
                    break;

            }
        }   


  </script>

</asp:Content>


<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">
  
<div id="pagemenu" style="width: 30%; float: right; margin-left: 15px">
    
  <div class = "menublock">
      
    <% if (Model.Id != 0) { %>
      <p><%= Html.ActionLink("Delete", "Delete", new { id = Model.Id }, new { @class = "link-delete" }) %></p>
    <% } %>
    <p><%= Html.ActionLink("Back to list", "Index") %></p>

  </div>

</div>

<div id="pagecontent" style="width: 70%">
  
  <h1>News banner</h1>

  <% if (Model.Id == 0) { %>
    <h4>New</h4>
  <% } else { %>
    <h4>ID = <%= Model.Id %></h4>
    <h4><%= Model.Enabled ? "ENABLED" : "DISABLED" %></h4>
  <% } %>

  <% using (Html.BeginForm()) { %>

    <%= Html.ValidationSummary(true) %>

    <%= Html.HiddenFor(m => m.Id) %>
    <%= Html.HiddenFor(m => m.Enabled) %>
    <%= Html.HiddenFor(m => m.TimeZone) %>

    <div class="editor-label">
      <%= Html.LabelFor(m => m.Description) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(m => m.Description) %>
      <%= Html.ValidationMessageFor(m => m.Description) %>
    </div>

    <div style="margin-top: 10px">
      <div class="timeZoneLabel">Start time, utc+0</div>
      <div class="editor-field"><%= Html.TextBoxFor(m => m.StartTime, new Dictionary<string, object> { { "class", "utcdateVal" }, { "Value", Model.StartTime.ToString("dd'.'MM'.'yyyy HH:mm:ss")} }) %></div>
    </div>
  
    <div style="margin-top: 10px">
      <div class="timeZoneLabel">End time, utc+0</div>
      <div class="editor-field"><%= Html.TextBoxFor(m => m.EndTime, new Dictionary<string, object> { { "class", "utcdateVal" }, { "Value", Model.EndTime.ToString("dd'.'MM'.'yyyy HH:mm:ss") } }) %></div>
    </div>

    <div class="editor-label">
      <%= Html.LabelFor(m => m.ButtonText) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(m => m.ButtonText) %>
      <%= Html.ValidationMessageFor(m => m.ButtonText) %>
    </div>

    <div class="editor-label">
      <%= Html.LabelFor(m => m.WindowCaption) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(m => m.WindowCaption) %>
      <%= Html.ValidationMessageFor(m => m.WindowCaption) %>
    </div>

    <div class="editor-label">
      <%= Html.LabelFor(m => m.ButtonUrl) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(m => m.ButtonUrl) %>
      <%= Html.ValidationMessageFor(m => m.ButtonUrl) %>
    </div>

    <div class="editor-label">
      <%= Html.LabelFor(m => m.MainUrl) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(m => m.MainUrl) %>
      <%= Html.ValidationMessageFor(m => m.MainUrl) %>
    </div>

    <div class="editor-label">
      <%= Html.LabelFor(m => m.MainUrlB) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(m => m.MainUrlB) %>
      <%= Html.ValidationMessageFor(m => m.MainUrlB) %>
    </div>

    <div class="editor-label">
      <%= Html.LabelFor(m => m.Tooltip) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(m => m.Tooltip) %>
      <%= Html.ValidationMessageFor(m => m.Tooltip) %>
    </div>

    <div class="editor-label">
      <%= Html.LabelFor(m => m.LoginNetworks) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(m => m.LoginNetworks) %>
      <%= Html.ValidationMessageFor(m => m.LoginNetworks) %>
    </div>

    <div class="editor-label">
      <%= Html.LabelFor(m => m.MinLordLevel) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(m => m.MinLordLevel) %>
      <%= Html.ValidationMessageFor(m => m.MinLordLevel) %>
    </div>

    <div class="editor-label">
      <%= Html.LabelFor(m => m.HideIfViewed) %>
    </div>
    <div class="editor-field">
      <%= Html.EditorFor(m => m.HideIfViewed) %>
      <%= Html.ValidationMessageFor(m => m.HideIfViewed) %>
    </div>

    <div class="editor-label">
      <%= Html.LabelFor(m => m.Locale) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(m => m.Locale) %>
      <%= Html.ValidationMessageFor(m => m.Locale) %>
    </div>
        <div style="padding: 10px">
            <div class="editor-label">
                Type Banner
            </div>
            <div class="editor-field">
                <%= Html.DropDownListFor(model => model.Type, Model.Type.ToSelectList(), new Dictionary<string, object> { { "onchange", "onSelectType(this);" } })%>
            </div>
            <div style="padding: 10px" id="extensionJsonContainter">
                <%
                    var type = Model.Type;
                    switch (type)
                    {
                        case NewsBannerModel.ENewsType.Interface:
                            %>
                            
                                <label class="editor-label">ButtonText </label><br/>
                                <%= Html.TextBoxFor(m => m.InteractionButtonText, new Dictionary<string, object> { { "class", "editor-field" } })%><br/>

                                <label class="editor-label">Go to Interface</label><br/>
                                <%= Html.DropDownListFor(model => model.Screen, 
                                        Model.Screen.ToSelectList()
                                            .Select(q => new SelectListItem() { Text = q.Text, Value = q.Value, Selected = q.Value.Equals(Model.Screen.ToString()) }))%><br/>

                                <label class="editor-label">Parameter</label><br/>
                                <%= Html.TextBoxFor(m => m.InterfaceArgs, new Dictionary<string, object> { { "class", "editor-field" } })%>
                            
                            <%
                            break;
                        case NewsBannerModel.ENewsType.Url:
                            %>
                            
                <label class="editor-label">ButtonText </label><br/>
                <%= Html.TextBoxFor(m => m.InteractionButtonText, new Dictionary<string, object> { { "class", "editor-field" } })%><br/>

                
                <label class="editor-label">Url</label><br/>
                <%= Html.TextBoxFor(m => m.InterfaceArgs, new Dictionary<string, object> { { "class", "editor-field" } })%>
                            
                            <%
                            break;
                    }

                %>
                <%--<%= Html.DropDownListFor(model => model.data, (Model.DataExtensionsList).Items.OfType<SelectListItem>(), new Dictionary<string, object> { { "onchange", "onSelectType(this);" } })%>
            <%= Html.TextBoxFor(m => m.type)%>--%>
            </div>
        </div>
        

    <br/><br/>
    <input type="submit" value="Save"/>

  <% } %>

</div>

</asp:Content>
