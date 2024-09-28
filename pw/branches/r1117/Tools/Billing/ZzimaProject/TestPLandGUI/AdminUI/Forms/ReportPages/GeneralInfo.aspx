<%@ Page Language="C#" MasterPageFile="~/AdminUI/Templates/ZzimaMasterReports.Master"
    AutoEventWireup="true" CodeBehind="GeneralInfo.aspx.cs" Inherits="ZzimaBilling.Admin.ReportsPages.GeneralInfo"
    Title="<%$ resources: AdminUI, Reports.Menu.GeneralInfo %>" 
    Culture="en-us"%>

<%@ Register Assembly="System.Web.DataVisualization, Version=3.5.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35"
    Namespace="System.Web.UI.DataVisualization.Charting" TagPrefix="asp" %>
<%@ Register Src="../../Templates/WebUserControls/NumericalControl.ascx" TagName="NumericalControl"
    TagPrefix="uc2" %>
<%@ Register Src="../../Templates/WebUserControls/DateTimeParameter.ascx" TagName="DateTimeParameter"
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
        <tr class="titleRowHeight">
            <td class="dummySpace">
                &nbsp;
            </td>
            <td valign="top">
                <table>
                    <tr class="titleRowHeight">
                        <td style="width: 200px">
                            <asp:Label ID="Label1" runat="server" Text="<%$ Resources: AdminUI, Reports.Period %>">
                            </asp:Label>
                        </td>
                        <td>
                            <table>
                                <tr>
                                    <td>
                                        <asp:Label ID="Label2" runat="server" Text="<%$ Resources: AdminUI, Reports.Period.From %>"
                                            Width="15px">
                                        </asp:Label>
                                    </td>
                                    <td>
                                        <uc1:DateTimeParameter ID="dtFrom" runat="server" timeSign="false" />
                                    </td>
                                    <td>
                                        <asp:Label ID="Label3" runat="server" Text="<%$ Resources: AdminUI, Reports.Period.To %>"
                                            Width="15px">
                                        </asp:Label>
                                    </td>
                                    <td>
                                        <uc1:DateTimeParameter ID="dtTo" runat="server" timeSign="false" />
                                    </td>
                                    <td>
                                        <asp:CustomValidator ID="cvDate" runat="server" ErrorMessage="*" ToolTip="<%$ resources:AdminUI, Reports.Validation.Dates %>"
                                            onservervalidate="cvDate_ServerValidate"></asp:CustomValidator>
                                    </td>
                                </tr>
                            </table>
                        </td>
                    </tr>
                </table>
            </td>
        </tr>
        <tr class="titleRowHeight">
            <td align="right" colspan="2">
                <div class="reportImg">
                    <asp:LinkButton ID="lbtnReport" CssClass="buttonMid" Text="<%$ resources:AdminUI, Button.Report %>"
                        runat="server" onclick="lbtnReport_Click"></asp:LinkButton>
                </div>
            </td>
        </tr>
    </table>
    </asp:Panel>
</asp:Content>
