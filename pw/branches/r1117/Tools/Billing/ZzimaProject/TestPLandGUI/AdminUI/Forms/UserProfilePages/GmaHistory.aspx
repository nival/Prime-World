<%@ Page Language="C#" AutoEventWireup="true" MasterPageFile="~/AdminUI/Templates/ZzimaUserProfile.Master"
    CodeBehind="GmaHistory.aspx.cs" Inherits="ZzimaBilling.AdminUI.Forms.UserProfilePages.GmaHistory"
    Title="<%$ Resources: AdminUI, UserProfile.Menu.GmaHistory %>" 
    Culture="en-GB"%>

<%@ Register Assembly="System.Web.DataVisualization, Version=3.5.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35"
    Namespace="System.Web.UI.DataVisualization.Charting" TagPrefix="asp" %>
<%@ Register Src="../../Templates/WebUserControls/NumericalControl.ascx" TagName="NumericalControl"
    TagPrefix="uc2" %>
<%@ Register Src="../../Templates/WebUserControls/DateTimeParameter.ascx" TagName="DateTimeParameter"
    TagPrefix="uc1" %>
<asp:Content ID="Content" ContentPlaceHolderID="UserPageHolder" runat="server">
    <link href="../../css/Grid.css" rel="stylesheet" type="text/css" />
    <link href="../../css/Zzima.css" rel="stylesheet" type="text/css" />
    <asp:Panel ID="Panel1" DefaultButton="lbnApply" runat="server">
        <table class="tableInfo">
            <tr class="titleRowHeight">
                <td colspan="2">
                    <table>
                        <tr>
                            <td class="underLabel" valign="middle" colspan="2">
                                <asp:Label ID="lblActualBalance" runat="server" Text="<%$ Resources: AdminUI, GmaHistory.Title %>"></asp:Label>
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
                                <asp:Label ID="Label1" runat="server" Text="<%$ Resources: AdminUI, GmaHistory.Period %>">
                                </asp:Label>
                            </td>
                            <td>
                                <table>
                                    <tr>
                                        <td>
                                            <asp:CustomValidator ID="cvDate" runat="server" ErrorMessage="*" OnServerValidate="cvDate_ServerValidate"
                                                Display="Dynamic" ToolTip="<%$ resources:AdminUI, Reports.Validation.Dates %>"></asp:CustomValidator>
                                        </td>
                                        <td>
                                            <asp:Label ID="Label2" runat="server" Text="<%$ Resources: AdminUI, GmaHistory.From %>"
                                                Width="15px">
                                            </asp:Label>
                                        </td>
                                        <td>
                                            <uc1:DateTimeParameter ID="dtFrom" runat="server" />
                                        </td>
                                        <td>
                                            <asp:Label ID="Label3" runat="server" Text="<%$ Resources: AdminUI, GmaHistory.To %>"
                                                Width="15px">
                                            </asp:Label>
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
                                <asp:Label ID="Label4" runat="server" Text="<%$ Resources: AdminUI, GmaHistory.Sum %>"></asp:Label>
                            </td>
                            <td>
                                <uc2:NumericalControl ID="ncAmount" runat="server" />
                            </td>
                        </tr>
                        <!--Admin name-->
                        <tr class="titleRowHeight">
                            <td style="width: 189px">
                                <asp:Label ID="lblPaymentSystem" runat="server" Text="<%$ Resources: AdminUI, GmaHistory.GmaLogin %>"></asp:Label>
                            </td>
                            <td>
                                <asp:TextBox ID="tbGmaLogin" CssClass="editBox" runat="server"></asp:TextBox>
                            </td>
                        </tr>
                        <!--Comment-->
                        <tr class="titleRowHeight">
                            <td style="width: 189px">
                                <asp:Label ID="Label5" runat="server" Text="<%$ Resources: AdminUI, GmaHistory.Comment %>"></asp:Label>
                            </td>
                            <td>
                                <asp:TextBox ID="tbComment" Rows="2" CssClass="editBox" runat="server"></asp:TextBox>
                            </td>
                        </tr>
                        <tr class="titleRowHeight">
                            <td align="right" colspan="2">
                                <div class="applyImg">
                                    <asp:LinkButton ID="lbnApply" CssClass="buttonMid" Text="<%$ resources:AdminUI, Button.Apply %>"
                                        runat="server" OnClick="lbnApply_Click"></asp:LinkButton>
                                </div>
                            </td>
                        </tr>
                    </table>
                </td>
            </tr>
            <tr height="4">
                <td colspan="2" class="hSeparator" />
            </tr>
            <tr>
                <td colspan="2">
                    <div>
                        <!--Pager-->
                        <asp:Panel ID="gvPagerRow" runat="server">
                            <table cellpadding="0" cellspacing="0" width="100%">
                                <tr>
                                    <td align="left">
                                        <div>
                                            <table>
                                                <tr class="titleRowHeight">
                                                    <td>
                                                        <table>
                                                            <tr>
                                                                <td align="left" valign="middle" class="underLabel">
                                                                    <asp:Literal ID="Literal5" runat="server" Text="<%$ resources:AdminUI, BonusHistory.Result %>"></asp:Literal>
                                                                    <img alt="" src="../../Images/arrow.gif" class="arrowIcon" />
                                                                </td>
                                                            </tr>
                                                        </table>
                                                    </td>
                                                    <td>
                                                        <asp:Label ID="lblTotalCount" runat="server" Text="<%$ resources:AdminUI, Users.TotalCount %>"></asp:Label>
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
                        <asp:GridView ID="gvGmaHistory" runat="server" GridLines="Vertical" BorderWidth="1px"
                            CellPadding="3" AutoGenerateColumns="False" AllowPaging="True" AllowSorting="True"
                            PageSize="20" DataSourceID="odsGmaHistory" OnRowCreated="gvGmaHistory_RowCreated"
                            OnSorting="gvGmaHistory_Sorting" Width="100%" OnSorted="gvGmaHistory_Sorted">
                            <PagerStyle HorizontalAlign="Right" />
                            <Columns>
                                <asp:BoundField DataField="Date" HeaderText="<%$ Resources: AdminUI, GmaHistory.GridView.Headers.Date %>"
                                    ReadOnly="true" SortExpression="Date">
                                    <ItemStyle Width="60%" />
                                </asp:BoundField>
                                <asp:BoundField DataField="Sum" HeaderText="<%$ Resources: AdminUI, GmaHistory.GridView.Headers.Sum %>"
                                    ReadOnly="True" SortExpression="Sum" />
                                <asp:BoundField DataField="Login" HeaderText="<%$ Resources: AdminUI, GmaHistory.GridView.Headers.Login %>"
                                    ReadOnly="True" SortExpression="Login" />
                                <asp:BoundField DataField="Comment" HeaderText="<%$ Resources: AdminUI, GmaHistory.GridView.Headers.Comment %>"
                                    ReadOnly="True" SortExpression="Comment" />
                            </Columns>
                            <HeaderStyle CssClass="headerRow" VerticalAlign="Middle" />
                            <PagerSettings Position="Top" />
                            <RowStyle CssClass="normalRow" />
                            <AlternatingRowStyle CssClass="alternativeRow" />
                            <PagerSettings Position="Top" Visible="False" />
                        </asp:GridView>
                        <asp:ObjectDataSource ID="odsGmaHistory" runat="server" SelectMethod="GetGmaHistoryTable"
                            TypeName="ZzimaBilling.AdminUI.DAL.UserDAL">
                            <SelectParameters>
                                <asp:SessionParameter DefaultValue="-1" Name="userID" SessionField="UserID" Type="Int32" />
                                <asp:SessionParameter DefaultValue="null" Name="filter" SessionField="gmaHistoryFilter"
                                    Type="Object" />
                            </SelectParameters>
                        </asp:ObjectDataSource>
                    </div>
                </td>
            </tr>
        </table>
    </asp:Panel>
</asp:Content>
