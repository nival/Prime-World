<%@ Page Language="C#" MasterPageFile="~/AdminUI/Templates/ZzimaMasterReports.Master"
    AutoEventWireup="true" CodeBehind="Expenses.aspx.cs" Inherits="ZzimaBilling.Admin.ReportsPages.Expenses"
    Title="<%$ resources: AdminUI, Reports.Menu.Expenses %>" 
    Culture="en-GB"%>

<%@ Register Src="../../Templates/WebUserControls/TimePeriodParameter.ascx" TagName="TimePeriodParameter"
    TagPrefix="uc1" %>
<%@ Register Src="../../Templates/WebUserControls/NumericalControl.ascx" TagName="NumericalControl"
    TagPrefix="uc2" %>
<%@ Register Src="../../Templates/WebUserControls/GroupsParamater.ascx" TagName="GroupsParamater"
    TagPrefix="uc3" %>
<asp:Content ID="Content" ContentPlaceHolderID="ReportPageHolder" runat="server">
    <link href="../../css/Grid.css" rel="stylesheet" type="text/css" />
    <link href="../../css/GeneralInfo.css" rel="stylesheet" type="text/css" />
    <link href="../../css/Zzima.css" rel="stylesheet" type="text/css" />

    <script language="javascript" type="text/javascript">
        function checkedAll(checkedVal, objCheckListId) {
            var objCheckListBox = document.getElementById(objCheckListId);
            if (objCheckListBox == null)
                return false;
                
            var chkBoxCount = objCheckListBox.getElementsByTagName("input");
            for (var i = 0; i < chkBoxCount.length; i++)
                chkBoxCount[i].checked = checkedVal;
            return false;
        }
    </script>

    <asp:Panel ID="Panel1" DefaultButton="lbtnReport" runat="server">
        <!--Search table-->
        <table class="tableInfo">
            <tr class="titleRowHeight">
                <td colspan="2">
                    <div>
                        <table>
                            <tr>
                                <td class="underLabel" valign="middle">
                                    <asp:Literal ID="Literal2" runat="server" Text="<%$ resources: AdminUI, Reports.InputData %>"></asp:Literal>
                                    <img alt="" src="../../Images/arrow.gif" class="arrowIcon" />
                                </td>
                            </tr>
                        </table>
                    </div>
                </td>
            </tr>
            <!--Period-->
            <tr>
                <td class="dummySpace">
                    &nbsp;
                </td>
                <td style="width: 200px" valign="top">
                    <asp:Literal ID="Literal3" runat="server" Text="<%$ resources:AdminUI, Reports.Period %>"></asp:Literal>
                </td>
                <td>
                    <uc1:TimePeriodParameter ID="dtTimePeriod" runat="server" />
                </td>
            </tr>
            <!--Payment System-->
            <tr class="filterRowHeight">
                <td>
                    &nbsp
                </td>
                <td>
                    <asp:Literal ID="Literal1" runat="server" Text="<%$ resources:AdminUI, Users.UsernameTitle %>"></asp:Literal>
                </td>
                <td>
                    <asp:TextBox runat="server" CssClass="editBox" ID="tbxUsernameMask"></asp:TextBox>
                </td>
            </tr>
            <!--Games-->
            <tr class="filterRowHeight">
                <td>
                    &nbsp
                </td>
                <td valign="top">
                    <asp:Literal ID="Literal4" runat="server" Text="<%$ resources:AdminUI, Reports.Expenses.Games %>"></asp:Literal>
                </td>
                <td>
                    <table width="100%">
                        <tr>
                            <td>
                                <input id="chkGamesId" type="checkbox" enableviewstate="true" onclick="checkedAll(document.forms[0].chkGamesId.checked, '<%=chbxGames.ClientID %>');" />
                                <asp:Literal ID="Literal5" runat="server" Text="<%$ Resources: AdminUI, SpendHistory.CheckAll %>"></asp:Literal>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <div class="checkBoxList">
                                    <asp:CheckBoxList ID="chbxGames" runat="server" CssClass="controls">
                                    </asp:CheckBoxList>
                                </div>
                            </td>
                        </tr>
                    </table>
                </td>
            </tr>
            <!--Subjects-->
            <tr class="filterRowHeight">
                <td>
                    &nbsp
                </td>
                <td valign="top">
                    <asp:Literal runat="server" Text="<%$ resources:AdminUI, Reports.Expenses.Subjects %>"></asp:Literal>
                </td>
                <td>
                    <table width="100%">
                        <tr>
                            <td>
                                <input id="chkSubjectsId" type="checkbox" enableviewstate="true" onclick="checkedAll(document.forms[0].chkSubjectsId.checked, '<%=chbxSubjects.ClientID %>');" />
                                <asp:Literal ID="Literal8" runat="server" Text="<%$ Resources: AdminUI, SpendHistory.CheckAll %>"></asp:Literal>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <div class="checkBoxList">
                                    <asp:CheckBoxList ID="chbxSubjects" runat="server" CssClass="controls">
                                    </asp:CheckBoxList>
                                </div>
                            </td>
                        </tr>
                    </table>
                </td>
            </tr>
            <tr class="filterRowHeight">
                <td>
                    &nbsp
                </td>
                <td>
                    <asp:Literal ID="Literal6" runat="server" Text="<%$ resources:AdminUI, Reports.Expenses.TotalAmount %>"></asp:Literal>
                </td>
                <td>
                    <uc2:NumericalControl ID="ncTotalCount" runat="server" />
                </td>
            </tr>
            <tr class="filterRowHeight">
                <td>
                    &nbsp
                </td>
                <td>
                    <asp:Literal ID="Literal7" runat="server" Text="<%$ resources:AdminUI, Reports.Expenses.TransactionsCount %>"></asp:Literal>
                </td>
                <td>
                    <uc2:NumericalControl ID="ncTransactionCount" runat="server" />
                </td>
            </tr>
            <tr class="filterRowHeight">
                <td>
                    &nbsp
                </td>
                <td valign="top">
                    <asp:Literal runat="server" Text="<%$ resources:AdminUI, Reports.Payments.DevideIntoGroups %>" />
                </td>
                <td>
                    <table cellpadding="0" cellspacing="0">
                        <tr>
                            <td valign="top">
                                <asp:CheckBox ID="chbxDevideIntoGroups" runat="server" AutoPostBack="true" OnCheckedChanged="chbxDevideIntoGroups_CheckedChanged" />
                            </td>
                            <td>
                                <uc3:GroupsParamater ID="gpGroups" runat="server" />
                            </td>
                        </tr>
                    </table>
                </td>
            </tr>
            <tr class="titleRowHeight">
                <td align="right" colspan="3">
                    <div class="reportImg">
                        <asp:LinkButton ID="lbtnReport" CssClass="buttonMid" Text="<%$ resources:AdminUI, Button.Report %>"
                            runat="server" OnClick="lbtnReport_Click"></asp:LinkButton>
                    </div>
                </td>
            </tr>
        </table>
    </asp:Panel>
</asp:Content>
