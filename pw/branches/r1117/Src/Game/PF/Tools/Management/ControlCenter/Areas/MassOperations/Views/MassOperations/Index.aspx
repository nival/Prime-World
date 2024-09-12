<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.MassOperations.Models.MassOperationsModel>" %>
<%@ Import Namespace="ControlCenter.Areas.MassOperations.Models"%>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
	Index
</asp:Content>

<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">
    <script type="text/javascript" src="/Scripts/jquery-ui-1.8.16.custom.min.js"></script>
    <script type="text/javascript" src="/Scripts/jquery.localizeDate.js"></script>
    <script type="text/javascript" src="/Scripts/jquery-ui-timepicker-addon.js"></script>
    <script type="text/javascript" src="/Scripts/jquery-ui-sliderAccess.js"></script>
    <script type="text/javascript" src="/Scripts/PageSpecific/DynamicQuestInfo.js"></script>
    <script type="text/javascript" src="/Scripts/CommonScripts.js"></script>
   
    <script type="text/javascript">
        var MassOperationTypeEnum = "";
        var Heroes = "";
        var HeroesValues = "";
        var Constructions = "";
        var ConstructionsValues = "";
        var Factions = "";
        
        function OnDocumentReady() {
            MassOperationTypeEnum = eval([<% ="\"" + MassOperationsModel.GetAllTexts(Model.MassOperationTypes) + "\"" %>]);
            Heroes = eval([<% ="\"" + MassOperationsModel.GetAllTexts(Model.HeroList) + "\"" %>]);
            HeroesValues = eval([<% ="\"" + MassOperationsModel.GetAllValues(Model.HeroList) + "\"" %>]);
            Constructions = eval([<% ="\"" + MassOperationsModel.GetAllTexts(Model.ConstructionList) + "\"" %>]);
            ConstructionsValues = eval([<% ="\"" + MassOperationsModel.GetAllValues(Model.ConstructionList) + "\"" %>]);
            Factions = eval([<% ="\"" + MassOperationsModel.GetAllTexts(Model.FactionList) + "\"" %>]);

            $("#MassOperationType").change(function () {
                ChangeInputs(this, "MassOperationsFields");
            });
            ChangeInputs($("#MassOperationType"), "MassOperationsFields");
        };
        
        function ChangeInputs(select, awardsType) {
            select = $(select);

            $('.MassOperationsFields').each(function() {
                $(this).remove();
            });
            var val = select.val();
            var tr = Pattern(val, awardsType);
            var awardContainer = select.parents("div:first");
            awardContainer
                .after(tr);

        }

        function Pattern(value, operationType) {
            var html = "<div class=\"" + operationType + "\">{pattern}</div>";
            var pattern = "";

            switch (value) {
            case "UnlockFlag":
            case "LockFlag":
                {
                    pattern += "<br>FlagId<br>";
                    pattern += "<input name=\"FlagId\" id=\"FlagId\" type=\"text\" value=\"\">";
                    break;
                }
            case "AddTalent":
                {
                    pattern += "<br>Talent (long id)<br>";
                    pattern += "<input name=\"Talent\" id=\"Talent\" type=\"text\" value=\"\">";
                    break;
                }
            case "AddTalents":
                {
                    pattern += "<br>Talents (long id, comma separated)<br>";
                    pattern += "<input name=\"Talents\" id=\"Talents\" type=\"text\" value=\"\">";
                    break;
                }
            case "PremiumAccount":
                {
                    pattern += "<br>Days of permium account<br>";
                    pattern += "<input name=\"PremiumDays\" id=\"PremiumDays\" type=\"text\" value=\"\">";
                    break;
                }
            case "SendMessageToUser":
                {
                    pattern += "<br>Message<br>";
                    pattern += "<textarea name=\"UserMessage\" id=\"UserMessage\" type=\"text\" value=\"\"></textarea>";
                    break;
                }
            case "GiveLamp":
                {
                    pattern += "<p>Bonus</p>";
                    pattern += "<input name=\"LampSettings.Bonus\" id=\"LampSettings.Bonus\" type=\"text\" value=\"100\">";
                    pattern += "<p>Gold</p>";
                    pattern += "<input name=\"LampSettings.Gold\" id=\"LampSettings.Gold\" type=\"text\" value=\"2000\">";
                    pattern += "<p>Transaction</p>";
                    pattern += "<input name=\"LampSettings.Transaction\" id=\"LampSettings.Transaction\" type=\"text\" value=\"1\">";
                    pattern += "<p>Duration</p>";
                    pattern += "<input name=\"LampSettings.Duration\" id=\"LampSettings.Duration\" type=\"text\" value=\"172800\">";
                    break;
                }
            case "AddSkin":
            case "DeleteSkin":
                {
                    pattern += "<p>PersistentId</p>";
                    pattern += "<input name=\"HeroSkinId\" id=\"HeroSkinId\" type=\"text\" value=\"\">";
                    break;
                }
            case "UnlockHero":
            case "LockHero":
                {
                    pattern += "<select name=\"HeroClassId\" id=\"HeroClassId\">";
                    Heroes.forEach(function(foreachValue) {
                        pattern += "<option>" + foreachValue + "</option>";
                    });
                    pattern += "</select>";
                    break;
                }
            case "AddBuilding":
                {
                    pattern += "<select name=\"BuildingPersistentId\" id=\"BuildingPersistentId\">";
                    Constructions.forEach(function(foreachValue) {
                        pattern += "<option>" + foreachValue + "</option>";
                    });
                    pattern += "</select>";
                    break;
                }
            case "EditAccount":
                {
                    pattern += "Silver<br>";
                    pattern += "<input name=\"AccountSettings.Silver\" id=\"AccountSettings.Silver\" type=\"text\" value=\"0\">";
                    pattern += "<br>Wood/Silk<br>";
                    pattern += "<input name=\"AccountSettings.Resource1\" id=\"AccountSettings.Resource1\" type=\"text\" value=\"0\">";
                    pattern += "<br>Ore/Sap<br>";
                    pattern += "<input name=\"AccountSettings.Resource2\" id=\"AccountSettings.Resource2\" type=\"text\" value=\"0\">";
                    pattern += "<br>Food<br>";
                    pattern += "<input name=\"AccountSettings.Resource3\" id=\"AccountSettings.Resource3\" type=\"text\" value=\"0\">";
                    pattern += "<br>Perl<br>";
                    pattern += "<input name=\"AccountSettings.Perl\" id=\"AccountSettings.Perl\" type=\"text\" value=\"0\">";
                    pattern += "<br>RedPerl<br>";
                    pattern += "<input name=\"AccountSettings.RedPerl\" id=\"AccountSettings.RedPerl\" type=\"text\" value=\"0\">";
                    pattern += "<br>CWPoints<br>";
                    pattern += "<input name=\"AccountSettings.CWPoints\" id=\"AccountSettings.CWPoints\" type=\"text\" value=\"0\">";
                    pattern += "<br>Currencies<br>";
                    pattern += "<input name=\"AccountSettings.Currencies\" id=\"AccountSettings.Currencies\" type=\"text\" value=\"\" placeholder=\"Ex: &quot;CC_Oscar:20,CC_Other:30&quot;\">";
                    pattern += "<br>Faction<br>";
                    pattern += "<select name=\"AccountSettings.Fraction\" id=\"AccountSettings.Fraction\">";
                    Factions.forEach(function(foreachValue) {
                        pattern += "<option>" + foreachValue + "</option>";
                    });
                    pattern += "</select>";
                }
            }

            if (pattern.localeCompare("") === 0) return "";


            return html.replace("{pattern}", pattern);
        }

        $(document).ready(OnDocumentReady);
    </script>
</asp:Content>
<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">
    <h2>Mass Operations</h2> 
    
    <div id="pagemenu" style="width: 30%; float: right; margin-right: 0px">
      <p><%= Html.ActionLink( "View history", "MassOperationsInfo" )%></p>
    </div>
    
    <%using (Html.BeginForm("Index", "MassOperations", FormMethod.Post, new { enctype = "multipart/form-data" }))
        { %>        
        <div class="editor-label">
            <%= Html.LabelFor(model => model.Auids) %>:
        </div>
        <div class="editor-field">
            <%= Html.TextAreaFor(model => model.Auids) %>
            <%= Html.ValidationMessageFor( model => model.Auids )%>
        </div>
        <br/>or<br/>
        <input type="file" name="file" />
        <br/>
        <div class="editor-label">
            <%= Html.LabelFor( model => model.MassOperationType )%>:
        </div>
        <div class="editor-field">
            <%= Html.DropDownListFor( model => model.MassOperationType, new SelectList( ( Enum.GetValues( typeof( MassOperationType ) ) ).Cast<MassOperationType>() ), new { id = "MassOperationType" } )%>
            <%= Html.ValidationMessageFor( model => model.MassOperationType )%>
        </div>
        
           <input type="submit" value="Send"/>
        <% } %>

</asp:Content>

