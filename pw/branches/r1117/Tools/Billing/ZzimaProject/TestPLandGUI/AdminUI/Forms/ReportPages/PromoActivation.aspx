<%@ Page Language="C#" MasterPageFile="~/AdminUI/Templates/ZzimaMasterReports.Master"
    AutoEventWireup="true" CodeBehind="PromoActivation.aspx.cs" Inherits="ZzimaBilling.Admin.ReportsPages.PromoActivation"
    Title="<%$ resources: AdminUI, Reports.Menu.PromoActivation %>"
    Culture="en-GB" %>

<%@ Register Src="../../Templates/WebUserControls/TimePeriodParameter.ascx" TagName="TimePeriodParameter"
    TagPrefix="uc1" %>
<%@ Register Src="../../Templates/WebUserControls/NumericalControl.ascx" TagName="NumericalControl"
    TagPrefix="uc2" %>
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
        <tr>
            <td class="dummySpace">
                &nbsp;
            </td>
            <td style="width: 200px" valign="top">
                <asp:Label ID="Label1" runat="server" Text="<%$ Resources: AdminUI, Reports.Period %>">
                </asp:Label>
            </td>
            <td>
                <uc1:TimePeriodParameter ID="dtTimePeriod" runat="server" />
            </td>
        </tr>
        <tr>
            <td>
                &nbsp;
            </td>
            <td>
                <asp:Literal ID="Literal2" runat="server" Text="<%$ resources:AdminUI, Reports.Username %>"></asp:Literal>
            </td>
            <td colspan="2">
                <asp:TextBox runat="server" CssClass="editBox" ID="tbxUserName"></asp:TextBox>
            </td>
        </tr>
        <tr>
            <td>
                &nbsp;
            </td>
            <td>
                <asp:Literal ID="Literal3" runat="server" Text="<%$ resources:AdminUI, Reports.Amount %>"></asp:Literal>
            </td>
            <td colspan="2">
                <uc2:NumericalControl ID="ncAmount" runat="server" />
            </td>
        </tr>
        <tr>
            <td>
                &nbsp;
            </td>
            <td>
                <asp:Literal ID="Literal4" runat="server" Text="<%$ resources:AdminUI, Reports.Comment %>"></asp:Literal>
            </td>
            <td colspan="2">
                <asp:TextBox runat="server" CssClass="editBox" ID="tbxComment"></asp:TextBox>
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
