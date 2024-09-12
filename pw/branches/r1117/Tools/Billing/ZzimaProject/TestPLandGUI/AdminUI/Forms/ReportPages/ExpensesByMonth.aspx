<%@ Page Language="C#" MasterPageFile="~/AdminUI/Templates/ZzimaMasterReports.Master"
    AutoEventWireup="true" CodeBehind="ExpensesByMonth.aspx.cs" Inherits="ZzimaBilling.Admin.ReportsPages.ExpensesByMonth"
    Title="<%$ resources: AdminUI, Reports.Menu.ExpensesByMonth %>" 
    Culture="en-GB" %>

<%@ Register Src="../../Templates/WebUserControls/TimePeriodParameter.ascx" TagName="TimePeriodParameter"
    TagPrefix="uc1" %>
<asp:Content ID="Content" ContentPlaceHolderID="ReportPageHolder" runat="server">
    <link href="../../css/Grid.css" rel="stylesheet" type="text/css" />
    <link href="../../css/Zzima.css" rel="stylesheet" type="text/css" />
    <asp:Panel ID="Panel1" DefaultButton="lbtnReport" runat="server">
    <table class="tableInfo">
        <tr class="titleRowHeight">
            <td colspan="2">
                <div>
                    <table>
        <tr>
                            <td class="underLabel" valign="middle">
                                <asp:Literal ID="Literal1" runat="server" Text="<%$ resources: AdminUI, Reports.InputData %>"></asp:Literal>
                                <img alt="" src="../../Images/arrow.gif" class="arrowIcon" />
                            </td>
                        </tr>
                    </table>
                </div>
            </td>
        </tr>
        <tr class="timePeriodRowHeight">
            <td class="dummySpace">
                &nbsp;
            </td>
            <td style="width: 200px" valign="top">
                <asp:Label runat="server" Text="<%$ Resources: AdminUI, Reports.Period %>">
                </asp:Label>
            </td>
            <td>
                <uc1:TimePeriodParameter ID="dtTimePeriod" runat="server" />
            </td>
        </tr>
        <tr class="titleRowHeight">
            <td align="right" colspan="3">
                <div class="reportImg">
                    <asp:LinkButton ID="lbtnReport" CssClass="buttonMid" Text="<%$ resources:AdminUI, Button.Report %>"
                        runat="server"></asp:LinkButton>
                </div>
            </td>
        </tr>
    </table>
    </asp:Panel>
</asp:Content>
