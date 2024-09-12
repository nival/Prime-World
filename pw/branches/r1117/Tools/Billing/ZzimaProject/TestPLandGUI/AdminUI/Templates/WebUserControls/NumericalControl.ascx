<%@ Control Language="C#" AutoEventWireup="true" CodeBehind="NumericalControl.ascx.cs" Inherits="ZzimaBilling.AdminUI.Templates.WebUserControls.NumericalControl" %>
<link href="../../css/Templates.css" rel="stylesheet" type="text/css" />
<link href="../../css/Zzima.css" rel="stylesheet" type="text/css" />

<script type="text/javascript" language="javascript">
    //Gets the prefix of controlID
    function GetPrefix(controlID) {
        if (controlID.toString().length > 0) {
            var index = controlID.toString().lastIndexOf('_');
            var prefix = controlID.toString().substring(0, index);
            return prefix;
        }
        return null;
    }

    //Set some text for lblOne
    function SetTextForLabelOne(prefix, text) {
        var lblOneId = prefix + '_lblFirst';
        document.getElementById(lblOneId).innerHTML = text;  
    }

    //Set some text for lblTwo
    function SetTextForLabelTwo(prefix, text) {
        var lblTwoId = prefix + '_lblSecond';
        document.getElementById(lblTwoId).innerHTML = text;
    }
    
    
    function ShowSection(sectionID) {
        var section = document.getElementById(sectionID);
        if (section != null)
            section.style.visibility = 'visible';
    }

    function HideSection(sectionID) {
        var section = document.getElementById(sectionID);
        if (section != null)
            section.style.visibility = 'hidden';
    }

    //Configure options
    function Configure(ddl) {
        var optionName = ddl[ddl.selectedIndex].value;
        var prefix = GetPrefix(ddl.id);
        var sectionOneID = prefix + '_sectionOne';
        var sectionTwoID = prefix + '_sectionTwo';
        //Clear text boxes
        //ClearTextBoxes(prefix);
        //Configure chosen option
        if (optionName == 'any') {
            HideSection(sectionOneID);
            HideSection(sectionTwoID);
        };
        if (optionName == 'lessthan') {
            ShowSection(sectionOneID);
            HideSection(sectionTwoID);
            SetTextForLabelOne(prefix, '<%=(String)GetGlobalResourceObject("AdminUI", "NumericalControl.To") %> ');
        };
        if (optionName == 'greatthan') {
            ShowSection(sectionOneID);
            HideSection(sectionTwoID);
            SetTextForLabelOne(prefix, '<%=(String)GetGlobalResourceObject("AdminUI", "NumericalControl.From") %>  ');
        };
        if (optionName == 'equal') {
            ShowSection(sectionOneID);
            HideSection(sectionTwoID);
            SetTextForLabelOne(prefix, '<%=(String)GetGlobalResourceObject("AdminUI", "NumericalControl.Equal") %>   '); 
        };
        if (optionName == 'range') {
            ShowSection(sectionOneID);
            ShowSection(sectionTwoID);
            SetTextForLabelOne(prefix, '<%=(String)GetGlobalResourceObject("AdminUI", "NumericalControl.From") %> ');
            SetTextForLabelTwo(prefix, '<%=(String)GetGlobalResourceObject("AdminUI", "NumericalControl.To") %> '); 
        };
    }

    function GetIndex(text) {
        if(text=="any")
            return 0;
        if (text == "lessthan")
            return 1;
        if (text == "greatthan")
            return 2;
        if (text == "range")
            return 3;
        if (text == "equal")
            return 4;
    }
    
    function Configure2(ddl, selectedValue) {
    
        ddl.selectedIndex = GetIndex(selectedValue);
            
        var optionName = selectedValue;
        var prefix = GetPrefix(ddl.id);
        var sectionOneID = prefix + '_sectionOne';
        var sectionTwoID = prefix + '_sectionTwo';
        //Clear text boxes
        //ClearTextBoxes(prefix);
        //Configure chosen option
        if (optionName == 'any') {
            HideSection(sectionOneID);
            HideSection(sectionTwoID);
        };
        if (optionName == 'lessthan') {
            ShowSection(sectionOneID);
            HideSection(sectionTwoID);
            SetTextForLabelOne(prefix, 
            '<asp:Literal ID="Literal6" runat="server" Text="<%$ resources:AdminUI, NumericalControl.To %>"/>');
        };
        if (optionName == 'greatthan') {
            ShowSection(sectionOneID);
            HideSection(sectionTwoID);
            SetTextForLabelOne(prefix, 
            '<asp:Literal ID="Literal7" runat="server" Text="<%$ resources:AdminUI, NumericalControl.From %>"/> ');
        };
        if (optionName == 'equal') {
            ShowSection(sectionOneID);
            HideSection(sectionTwoID);
            SetTextForLabelOne(prefix, 
            '<asp:Literal ID="Literal8" runat="server" Text="<%$ resources:AdminUI, NumericalControl.Equal %>"/> ');
        };
        if (optionName == 'range') {
            ShowSection(sectionOneID);
            ShowSection(sectionTwoID);
            SetTextForLabelOne(prefix, 
            '<asp:Literal ID="Literal9" runat="server" Text="<%$ resources:AdminUI, NumericalControl.From %>"/>  ');
            SetTextForLabelTwo(prefix, 
            '<asp:Literal ID="Literal10" runat="server" Text="<%$ resources:AdminUI, NumericalControl.To %>"/>  ');
        };
    }

    function IsNumeric(sText) {

        alert(/^\d+([\.,]\d{1,2})?$/.test(sText));
        return /^\d+([\.,]\d{1,2})?$/.test(sText);
        /*var ValidChars = "0123456789.";
        var IsNumber = true;
        var Char;


        for (i = 0; i < sText.length && IsNumber == true; i++) {
            Char = sText.charAt(i);
            if (ValidChars.indexOf(Char) == -1) {
                IsNumber = false;
            }
        }
        return IsNumber;*/

    }

    
</script>
    <div>
        <!--UI Part-->
        <table cellpadding="0" cellspacing="0">
            <tr>
                <td width="1px">
                    <asp:Label ID="lblError" runat="server" Style="color:Red" Text="*" ToolTip="<%$ resources:AdminUI, NumericalControl.Error %>"></asp:Label>
                </td>
                <!--Dropdown list with options of filtering-->
                <td>
                    <select id="<%=ClientID%>_ddl" name="<%=ClientID%>_ddl"  
                        class="editBox" 
                        onchange="Configure(this)">
                        <option value="any">
                            <asp:Literal ID="Literal1" runat="server" Text="<%$ resources:AdminUI, NumericalControl.AnyTitle %>"></asp:Literal>
                        </option>
                        <option value="lessthan">
                            <asp:Literal ID="Literal2" runat="server" Text="<%$ resources:AdminUI, NumericalControl.LessThanTitle %>"></asp:Literal>
                        </option>
                        <option value="greatthan">
                            <asp:Literal ID="Literal3" runat="server" Text="<%$ resources:AdminUI, NumericalControl.GreatThanTitle %>"></asp:Literal>
                        </option>
                        <option value="range">
                            <asp:Literal ID="Literal4" runat="server" Text="<%$ resources:AdminUI, NumericalControl.RangeTitle %>"></asp:Literal>
                        </option>
                        <option value="equal">
                            <asp:Literal ID="Literal5" runat="server" Text="<%$ resources:AdminUI, NumericalControl.EqualTitle %>"></asp:Literal>
                        </option>
                    </select>    
                </td>
                <!--Dynamic control content-->
                <td>
                    <table cellpadding="0" cellspacing="0">
                            <tr>
                                <td width="10px">&nbsp;</td>
                                <td id="<%=ClientID%>_sectionOne">
                                    <label id="<%=ClientID%>_lblFirst" class="insideText" ></label>
                                    <asp:TextBox ID="tbxFirst" runat="server" Width="40px" Font-Size="10pt" 
                                        CssClass="editBox"></asp:TextBox>
                                    
                                </td>
                                <td width="10px">&nbsp;</td>
                                <td id="<%=ClientID%>_sectionTwo" >
                                    <label id="<%=ClientID%>_lblSecond" class="insideText" ></label>
                                    <asp:TextBox ID="tbxSecond" runat="server" Width="40px" Font-Size="10pt" 
                                        CssClass="editBox"></asp:TextBox>
                                </td>
                                <td>
                                     
                                </td>
                            </tr>
                    </table>
                    <script language="javascript" type="text/javascript">
                        var ddlID = '<%=ClientID %>_ddl';
                        var ddl = document.getElementById(ddlID);
                        Configure2(ddl, '<%=SelectedValue %>');
                    </script>
                </td>
            </tr>
        </table>
    </div>
