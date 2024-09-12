<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<QuestForTalentModel>" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
	EditQuestForTalent
</asp:Content>

<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">

    <script type="text/javascript">
        function copyToClipBoard() {
            /* Get the text field */
            var copyText = document.getElementById("myInput");

            /* Select the text field */
            copyText.select();

            /* Copy the text inside the text field */
            document.execCommand("Copy");

            /* Alert the copied text */
            alert("Copied the text: " + copyText.value);
        }
    </script>

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
    </script>

</asp:Content>

<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">

    <div id="pagemenu" style="width: 30%; float: right; margin-left: 15px">
        <div class = "menublock">
            <p><%= Html.ActionLink("Back to quests list", "QuestsForTalents", new { auid = ViewData["Auid"], login = ViewData["Login"] })%></p>
        </div>
    </div> 
    
    <h2>View selected QuestForTalent</h2>
    
    <table>
        <tr>
            <td><b>StartTime</b></td>
            <td><b>EndTime</b></td>
            <td><b>Current Quest Progress</b></td>
            <td><b>Total Quest Progress</b></td>
            <td><b>Talent in Award</b></td>
            <td><b>Shards Spent</b></td>
            <td><b>More info (<a target="_blank" href="https://codebeautify.org/python-formatter-beautifier" >Formatting Helper</a>)</b></td>
        </tr>
        
        
            <tr>
                <td>
                    <%= Model.StartTime%>
                </td>
                <td>
                    <%= Model.EndTime%>
                </td>
                <td>
                    <%= Model.CurrentObjectiveValue%>
                </td>
                <td>
                    <%= Model.TotalObjectiveData %>
                </td>
                <td style="background-color: gold; color: black">
                    <%= Model.TalentAwardName %>
                </td>
                <td>
                    <%= Model.ShardsSpent %>
                </td>
                <td>
                    <button style="color: white; background-color: blueviolet" onclick="copyToClipBoard()">Copy to clipboard</button><textarea  type="text" id="myInput"><%= Model.FullDynamicQuestDump%></textarea>
                </td>
            </tr>
    
        
    </table>

    <h2>Edit QuestForTalent</h2>

    <% using (Html.BeginForm()) { %>
        
        <%= Html.HiddenFor(model => model.AwardId) %>
        <%= Html.HiddenFor(model => model.ObjectiveId) %>
        <%= Html.HiddenFor(model => model.Auid) %>
        <%= Html.HiddenFor(model => model.QuestId) %>
        
        <div><%= Html.LabelFor(m => m.StartTime) %>:<br/></div>
        <div style="margin-bottom: 10px"><%= Html.EditorFor(m => m.StartTime) %><br/></div>
        
        <div><%= Html.LabelFor(m => m.EndTime) %>:<br/></div>
        <div style="margin-bottom: 10px"><%= Html.EditorFor(m => m.EndTime) %><br/></div>
        
        <div><%= Html.LabelFor(m => m.CurrentObjectiveValue) %>:<br/></div>
        <div style="margin-bottom: 10px"><%= Html.EditorFor(m => m.CurrentObjectiveValue) %><br/></div>
        
        <div><%= Html.LabelFor(m => m.TalentAwardName) %>:<br/></div>
        <div style="margin-bottom: 10px"><%= Html.EditorFor(m => m.TalentAwardName)%><br/></div>

        <input type="submit" value="Edit"/>

    <% } %>
</asp:Content>
