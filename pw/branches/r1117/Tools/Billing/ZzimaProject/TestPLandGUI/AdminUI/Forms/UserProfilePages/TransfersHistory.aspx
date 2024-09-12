<%@ Page Title="" Language="C#" MasterPageFile="~/AdminUI/Templates/ZzimaUserProfile.Master"
    AutoEventWireup="true" CodeBehind="TransfersHistory.aspx.cs" Inherits="ZzimaBilling.AdminUI.Forms.UserProfilePages.TransfersHistory" %>

<%@ Register Assembly="System.Web.DataVisualization, Version=3.5.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35"
    Namespace="System.Web.UI.DataVisualization.Charting" TagPrefix="asp" %>
<%@ Register Src="../../Templates/WebUserControls/NumericalControl.ascx" TagName="NumericalControl"
    TagPrefix="uc2" %>
<%@ Register Src="../../Templates/WebUserControls/DateTimeParameter.ascx" TagName="DateTimeParameter"
    TagPrefix="uc1" %>
<asp:Content ID="Content1" ContentPlaceHolderID="UserPageHolder" runat="server">
    <link href="../../css/Grid.css" rel="stylesheet" type="text/css" />
    <link href="../../css/Templates.css" rel="stylesheet" type="text/css" />
    <link href="../../css/Zzima.css" rel="stylesheet" type="text/css" />
    <table class="tableInfo">
        <tr class="titleRowHeight">
            <td colspan="3">
                <table>
                    <tr>
                        <td class="underLabel" valign="middle">
                            <asp:Label ID="lblTransferName" runat="server" Text="<%$ Resources: AdminUI, TransferHistory.Title %>"></asp:Label>
                            <img alt="" src="../../Images/arrow.gif" class="arrowIcon" />
                        </td>
                    </tr>
                </table>
            </td>
        </tr>
        <tr>
            <td class="dummySpace">
                &nbsp;
            </td>
            <td>
                <table width="100%">
                    <tr class="titleRowHeight">
                        <td style="width: 200px">
                            <asp:Label ID="lblPeriod" runat="server" Text="<%$ Resources: AdminUI, PaymentsHistory.Period %>"> </asp:Label>
                        </td>
                        <td>
                            <table>
                                <tr>
                                    <td>
                                        <asp:CustomValidator ID="cvDate" runat="server" ErrorMessage="*" OnServerValidate="cvDate_ServerValidate"
                                            Display="Dynamic" ToolTip="<%$ resources:AdminUI, Reports.Validation.Dates %>"></asp:CustomValidator>
                                    </td>
                                    <td>
                                        <asp:Label ID="Label1" runat="server" Text="<%$ Resources: AdminUI, PaymentsHistory.From %>"
                                            Width="15px"> </asp:Label>
                                    </td>
                                    <td>
                                        <uc1:DateTimeParameter ID="dtFrom" runat="server" />
                                    </td>
                                    <td>
                                        <asp:Label ID="Label2" runat="server" Text="<%$ Resources: AdminUI, PaymentsHistory.To %>"
                                            Width="15px"> </asp:Label>
                                    </td>
                                    <td>
                                        <uc1:DateTimeParameter ID="dtTo" runat="server" />
                                    </td>
                                </tr>
                            </table>
                        </td>
                    </tr>
                    <!--Sum-->
                    <tr class="titleRowHeight">
                        <td style="width: 189px">
                            <asp:Label ID="lblSum" runat="server" Text="<%$ Resources: AdminUI, PaymentsHistory.Sum %>"></asp:Label>
                        </td>
                        <td>
                            <uc2:NumericalControl ID="ncAmount" runat="server" />
                        </td>
                    </tr>
                    <tr class="titleRowHeight">
                        <td align="right" colspan="3">
                            <div class="applyImg">
                                <asp:LinkButton ID="LinkButton1" CssClass="buttonMid" Text="<%$ resources:AdminUI, Button.Apply %>"
                                    runat="server" OnClick="lbnApply_Click"></asp:LinkButton>
                            </div>
                        </td>
                    </tr>
                </table>
            </td>
        </tr>
        <tr height="4">
            <td colspan="3" class="hSeparator" />
        </tr>
    </table>
    <asp:Panel ID="gvPagerRow" runat="server">
        <table cellpadding="0" cellspacing="0" width="100%">
            <tr>
                <td align="left">
                    <div>
                        <table>
                            <tr class="filterRowHeight">
                                <td>
                                    <asp:Label ID="lblTotalCount" runat="server" Text="<%$ resources:AdminUI, Users.TotalCount %>"></asp:Label>
                                </td>
                                <td>
                                    &nbsp;
                                </td>
                                <td>
                                    <asp:Label ID="lblCount" class="labelCount" runat="server" Text="0"></asp:Label>
                                </td>
                            </tr>
                        </table>
                    </div>
                </td>
                <td align="right">
                    <div>
                        <table>
                            <tr>
                                <td align="right">
                                    <asp:Literal ID="Literal9" runat="server" Text="<%$ resources: AdminUI, Pager.Page%>" />
                                    <asp:Label ID="PageNumberLabel" CssClass="labelCount" runat="server" />
                                    <asp:Literal ID="Literal10" runat="server" Text="<%$ resources: AdminUI, Pager.Of%>" />
                                    <asp:Label ID="TotalPagesLabel" CssClass="labelCount" runat="server" />
                                </td>
                                <td width="20px">
                                    &nbsp;
                                </td>
                                <td>
                                    <asp:LinkButton ID="lnkFirstPage" CommandName="Page" CommandArgument="First" runat="server"
                                        CssClass="labelCount" Text="<%$ resources: AdminUI, Pager.First %>" ToolTip="<%$ resources: AdminUI, Pager.Tip.First %>"></asp:LinkButton>
                                </td>
                                <td>
                                    <asp:LinkButton ID="lnkPrevPage" CommandName="Page" CommandArgument="Prev" runat="server"
                                        Text="<%$ resources: AdminUI, Pager.Prev %>" CssClass="labelCount" ToolTip="<%$ resources: AdminUI, Pager.Tip.Prev %>"></asp:LinkButton>
                                </td>
                                <td>
                                    <asp:LinkButton ID="lnkNextPage" CommandName="Page" CommandArgument="Next" runat="server"
                                        Text="<%$ resources: AdminUI, Pager.Next %>" CssClass="labelCount" ToolTip="<%$ resources: AdminUI, Pager.Tip.Next %>"></asp:LinkButton>
                                </td>
                                <td>
                                    <asp:LinkButton ID="lnkLastPage" CommandName="Page" CommandArgument="Last" runat="server"
                                        Text="<%$ resources: AdminUI, Pager.Last %>" CssClass="labelCount" ToolTip="<%$ resources: AdminUI, Pager.Tip.Last %>"></asp:LinkButton>
                                </td>
                            </tr>
                        </table>
                    </div>
                </td>
            </tr>
        </table>
    </asp:Panel>
    <asp:GridView ID="gvTransferHistory" runat="server" DataSourceID="odsTransfers" AutoGenerateColumns="False"
        AllowSorting="True" Width="100%" AllowPaging="True" PageSize="20" OnSorting="gvTransfersHistory_Sorting"
            OnRowCreated="gvTransfersHistory_RowCreated" >
        <Columns>
            <asp:BoundField DataField="AMOUNT" HeaderText="<%$ Resources: AdminUI, TransfersHistory.gridView.Amount %>"
                SortExpression="AMOUNT" />
            <asp:BoundField DataField="EXECUTEDAT" HeaderText="<%$ Resources: AdminUI, TransfersHistory.gridView.Date %>"
                SortExpression="EXECUTEDAT" />
            <asp:BoundField DataField="REASON" HeaderText="<%$ Resources: AdminUI, TransfersHistory.gridView.Reason %>"
                SortExpression="REASON" />
            <asp:BoundField DataField="SRCACCID" HeaderText="<%$ Resources: AdminUI, TransfersHistory.gridView.srcAccid %>"
                SortExpression="SRCACCID" />
            <asp:BoundField DataField="DESTACCID" HeaderText="<%$ Resources: AdminUI, TransfersHistory.gridView.destAccid %>"
                SortExpression="DESTACCID" />
        </Columns>
        <HeaderStyle CssClass="headerRow" VerticalAlign="Middle" />
        <PagerSettings Visible="False" />
        <RowStyle CssClass="normalRow" />
        <AlternatingRowStyle CssClass="alternativeRow" />
    </asp:GridView>
    <br />
    <asp:ObjectDataSource ID="odsTransfers" runat="server" SelectMethod="getUserTransfersHistoryTable"
        TypeName="ZzimaBilling.AdminUI.DAL.EmployeeDAL">
        <SelectParameters>
            <asp:SessionParameter Name="userid" SessionField="UserID" Type="Int32" />
            <asp:SessionParameter Name="filter" SessionField="Filter" Type="Object" />
        </SelectParameters>
    </asp:ObjectDataSource>
</asp:Content>
