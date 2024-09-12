<%@ Page Title="GWEvents" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<GWEventsModel>" %>
<%@ Import Namespace="ControlCenter.Areas.GWEvents.Models" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
GWEvents
</asp:Content>


<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">

    <link rel="stylesheet" href="/Content/pager.css" />
    <link href="../../../../Content/jquery-ui-1.8.17.custom.css" rel="stylesheet" type="text/css" />
    <style type="text/css">
    /* css for timepicker */
        .ui-timepicker-div .ui-widget-header { margin-bottom: 8px; }
        .ui-timepicker-div dl { text-align: left; }
        .ui-timepicker-div dl dt { height: 25px; margin-bottom: -25px; }
        .ui-timepicker-div dl dd { margin: 0 10px 10px 65px; }
        .ui-timepicker-div td { font-size: 90%; }
        .ui-tpicker-grid-label { background: none; border: none; margin: 0; padding: 0; }
    </style>
  
    <style type="text/css">
        .filter { border: 0; }
        .filter td { border: 0; }
        .saveButton { font-size: 150%; font-weight: bold; }
    </style>
  
    <script type="text/javascript" src="../../../../Scripts/jquery-ui-1.8.16.custom.min.js"></script>
    <script type="text/javascript" src="../../../../Scripts/jquery-ui-timepicker-addon.js"></script>
    <script type="text/javascript" src="../../../../Scripts/jquery-ui-sliderAccess.js"></script>

    <script type="text/javascript">
        $(document).ready(function () {
            $("input[name*='Time']").datetimepicker({ dateFormat: 'dd.mm.yy', timeFormat: 'hh:mm:ss', showSecond: true });
        });

        function confirmEventChange() {
            if (confirm("Перепроверьте и подтвердите изменения")) {
                document.getElementById("updateform").submit(); 
            }
                
        }
    </script>

</asp:Content>


<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">

<div id="pagecontent" style="width: 70%">
    <h2>GWEvents</h2>

    <% int lastEvent = Model.GwEvents.Count - 1; %>

    <fieldset>
    <legend>Last GuildWar Event Edit Form</legend>
    
        <% using (Html.BeginForm(null, null, FormMethod.Post, new { id = "updateform" })) { %>

        <%= Html.ValidationSummary(true) %>

        <div class="editor-field">
            <%= Html.LabelFor(m => m.GwEvents[lastEvent].Enabled)%>
            = "<%= Model.GwEvents[lastEvent].Enabled%>"
        </div>
        
        <div style="margin-top: 10px">
            <%= Html.LabelFor(m => m.GwEvents[lastEvent].Id)%>
             = "<%= Model.GwEvents[lastEvent].Id %>"
        </div>
        
        <div style="margin-top: 10px">
            <%= Html.LabelFor(m => m.GwEvents[lastEvent].EventIndex)%>
             = "<%= Model.GwEvents[lastEvent].EventIndex%>"
        </div>

        <div style="margin-top: 10px">
          <div class="timeZoneLabel">End time, utc+0</div>
          <%= Html.EditorFor(m => m.GwEvents[lastEvent].EndTime)%>
          <%= Html.ValidationMessageFor(m => m.GwEvents[lastEvent].EndTime)%>
        </div>
        
        <div class="editor-label">
            <%= Html.LabelFor(m => m.GwEvents[lastEvent].PointsToAdd) %> (Current points: <%= Model.GwEvents[lastEvent].CurrentPoints %>; Points to Add limit: <%= Model.GwEvents[lastEvent].PointsToAddLimit %>)
        </div>
        <div class="editor-field">
            <%= Html.TextBoxFor(m => m.GwEvents[lastEvent].PointsToAdd)%>
            <%= Html.ValidationMessage("PointsToAdd")%>
        </div>

        <div class="editor-label">
          <%= Html.LabelFor(m => m.GwEvents[lastEvent].Limit) %>
        </div>
        <div class="editor-field">
          <%= Html.TextBoxFor(m => m.GwEvents[lastEvent].Limit)%>
          <%= Html.ValidationMessageFor(m => m.GwEvents[lastEvent].Limit)%>
        </div>

        <br/><br/>
        <input id="updateBtn" type="button" value="Update" onclick="confirmEventChange();"/>
      
    </fieldset>
    <fieldset>
        <legend>All Guild War Events info</legend>
        <% if (Model.GwEvents.Count > 0) { %>
            <table>
            <tr>
                <td>
                    
                </td>
                <td>
                    <b><%= Html.LabelFor(m => m.GwEvents[0].Id)%></b>
                </td>
                <td>
                    <b><%= Html.LabelFor(m => m.GwEvents[0].EventIndex)%></b>
                    
                </td>
                <td>
                    <b><%= Html.LabelFor(m => m.GwEvents[0].Enabled)%></b>
                    
                </td>
                <td>
                    <b><%= Html.LabelFor(m => m.GwEvents[0].CurrentPoints)%></b>
                    
                </td>
                <td>
                    <b>PoolPointsLeft</b>
                </td>
                <td>
                    <b><%= Html.LabelFor(m => m.GwEvents[0].EndTime)%></b>
                </td>
                <td>
                    <b><%= Html.LabelFor(m => m.GwEvents[0].Limit)%></b>
                </td>
                <td>
                    
                </td>
            </tr>
        <% for (int i = 0; i < Model.GwEvents.Count; i++) { %>
            <tr>
                <td>
                    <%= i + 1 %><div style="display: none;"> <%= Html.EditorFor(m => m.GwEvents[i])%></div>
                </td>
                <td>
                    <%= Model.GwEvents[i].Id%>
                </td>
                <td>
                    <%= Model.GwEvents[i].EventIndex%>
                </td>
                <td>
                    <%= Model.GwEvents[i].Enabled%>
                </td>
                <td>
                    <%= Model.GwEvents[i].CurrentPoints%>
                </td>
                <td>
                    <%= Model.GwEvents[i].Limit - Model.GwEvents[i].CurrentPoints %>
                </td>
                <td>
                    <%= Model.GwEvents[i].EndTime %>
                </td>
                <td>
                    <%= Model.GwEvents[i].Limit%>
                </td>
                <td>
                    <%= Html.ActionLink("History", "GWEventHistory", new { eventIdx = Model.GwEvents[i].EventIndex })%>
                </td>
            </tr>
        <% } %>
        </table>
        <% } %>
    </fieldset>
    <% } %>
</div>

</asp:Content>
