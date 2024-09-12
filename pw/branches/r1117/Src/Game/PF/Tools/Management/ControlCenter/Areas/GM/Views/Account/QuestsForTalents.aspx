<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<QuestsForTalentsModel>" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
    Current QuestsForTalents
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

</asp:Content>


<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">

    <div id="pagemenu" style="width: 30%; float: right; margin-right: 0px">
        <p><%= Html.ActionLink("Back to account details", "Details", new { auid = Model.Auid })%></p>
    </div>

    <h2>Current DynamicQuests</h2>
    
    <table style="margin-bottom: 10px">
        <tr>
            <td style="background-color: gold; padding: 10px"></td>
            <td>Quests For Talents</td>
        </tr>
        <tr>
            <td style="background-color: green; padding: 10px"></td>
            <td>DynamicQuests</td>
        </tr>
    </table>
    
    <table>
        <tr>
            <td></td>
            <td><b>StartTime</b></td>
            <td><b>EndTime</b></td>
            <td><b>Current Quest Progress</b></td>
            <td><b>Total Quest Progress</b></td>
            <td><b>Talent in Award</b></td>
            <td><b>Shards Spent</b></td>
            <td><b>More info (<a target="_blank" href="https://codebeautify.org/python-formatter-beautifier" >Formatting Helper</a>, <a target="_blank" href="https://r12a.github.io/apps/conversion/" >UnicodeToText Helper</a>)</b></td>
            <td><b>Edit</b></td>
        </tr>
    <% for (int i = 0; i < Model.items.Count; i++){ %>
        
        
            <% if (Model.items[i].Reason == 1) {%>
                <tr>
                    <td style="background-color: gold; color: black">
                        <%= i + 1 %>
                    </td>
                    <td>
                        <%= Model.items[i].StartTime %>
                    </td>
                    <td>
                        <%= Model.items[i].EndTime %>
                    </td>
                    <td>
                        <%= Model.items[i].CurrentObjectiveValue %>
                    </td>
                    <td>
                        <%= Model.items[i].TotalObjectiveData %>
                    </td>
                    <td>
                        <%= Model.items[i].TalentAwardName %>
                    </td>
                    <td>
                        <%= Model.items[i].ShardsSpent %>
                    </td>
                    <td>
                        <button style="color: white; background-color: blueviolet" onclick="copyToClipBoard()">Copy to clipboard</button><textarea  type="text" id="myInput"><%= Model.items[i].FullDynamicQuestDump %></textarea>
                    </td>
                    <td>
                        <%= Html.ActionLink("Edit", "EditQuestForTalent", new { auid = Model.Auid, login = Model.Login, questNumber = i })%>
                    </td>
                </tr>
            <% } else if (Model.items[i].Reason == 0) { %>
                <tr>
                    <td style="background-color: green; color: black">
                        <%= i + 1 %>
                    </td>
                    <td>
                        <%= Model.items[i].StartTime %>
                    </td>
                    <td>
                        <%= Model.items[i].EndTime %>
                    </td>
                    <td>
                        
                    </td>
                    <td>
                        
                    </td>
                    <td>
                        
                    </td>
                    <td>

                    </td>
                    <td>
                        <button style="color: white; background-color: blueviolet" onclick="copyToClipBoard()">Copy to clipboard</button><textarea  type="text" id="Textarea1"><%= Model.items[i].FullDynamicQuestDump %></textarea>
                    </td>
                    <td>
                        
                    </td>
                </tr>
            <% } %>
        
    
    <% } %>
    </table>

</asp:Content>
