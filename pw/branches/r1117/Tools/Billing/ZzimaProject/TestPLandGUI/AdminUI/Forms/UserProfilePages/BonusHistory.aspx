<%@ Page Language="C#" AutoEventWireup="true" MasterPageFile="~/AdminUI/Templates/ZzimaUserProfile.Master"
    CodeBehind="BonusHistory.aspx.cs" Inherits="ZzimaBilling.AdminUI.Forms.UserProfilePages.BonusHistory"
    Title="<%$ Resources: AdminUI, UserProfile.Menu.BonusHistory %>"
    Culture="en-GB" %>

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
                            <td class="underLabel" valign="middle">
                                <asp:Label ID="lblGames" runat="server" Text="<%$ Resources: AdminUI, BonusHistory.Title %>"></asp:Label>
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
                                <asp:Label ID="Label1" runat="server" Text="<%$ Resources: AdminUI, BonusHistory.Period %>" />
                            </td>
                            <td>
                                <table>
                                    <tr>
                                        <td>
                                            <asp:CustomValidator ID="cvDate" runat="server" ErrorMessage="*" OnServerValidate="cvDate_ServerValidate" Display="Dynamic"
                                                ToolTip="<%$ resources:AdminUI, Reports.Validation.Dates %>"></asp:CustomValidator>
                                        </td>
                                        <td>
                                            <asp:Label ID="lblFrom" runat="server" Text="<%$ Resources: AdminUI, BonusHistory.From %>"
                                                Width="15px">
                                            </asp:Label>
                                        </td>
                                        <td>
                                            <uc1:DateTimeParameter ID="dtFrom" runat="server" />
                                        </td>
                                        <td>
                                            <asp:Label ID="lblTo" runat="server" Text="<%$ Resources: AdminUI, BonusHistory.To %>"
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
                                <asp:Label ID="lblSum" runat="server" Text="<%$ Resources: AdminUI, BonusHistory.Sum %>"></asp:Label>
                            </td>
                            <td>
                                <uc2:NumericalControl ID="bhSum" runat="server" />
                            </td>
                        </tr>
                        <!--Comment-->
                        <tr class="titleRowHeight">
                            <td style="width: 189px">
                                <asp:Label ID="Label2" runat="server" Text="<%$ Resources: AdminUI, BonusHistory.Comment %>"></asp:Label>
                            </td>
                            <td>
                                <asp:TextBox ID="bhComment" runat="server" CssClass="editBox"></asp:TextBox>
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
                        <asp:GridView ID="gvBonusHistory" runat="server" GridLines="Vertical" BorderWidth="1px"
                            CellPadding="3" AutoGenerateColumns="False" AllowPaging="True" AllowSorting="True"
                            PageSize="20" Width="100%" DataSourceID="odsBonusHistory" OnRowCreated="gvBonusHistory_RowCreated"
                            OnSorting="gvBonusHistory_Sorting" OnSorted="gvBonusHistory_Sorted">
                            <Columns>
                                <asp:BoundField DataField="Date" HeaderText="<%$ Resources: AdminUI, BonusHistory.GridView.Headers.DateAndTime %>"
                                    ReadOnly="true" SortExpression="Date">
                                    <ItemStyle Width="60%" />
                                </asp:BoundField>
                                <asp:BoundField DataField="Amount" HeaderText="<%$ Resources: AdminUI, BonusHistory.GridView.Headers.Amount %>"
                                    ReadOnly="True" SortExpression="Amount" />
                                <asp:BoundField DataField="Reason" HeaderText="<%$ Resources: AdminUI, BonusHistory.GridView.Headers.Comment %>"
                                    ReadOnly="True" SortExpression="Reason" />
                            </Columns>
                            <PagerStyle HorizontalAlign="Right" />
                            <HeaderStyle CssClass="headerRow" VerticalAlign="Middle" />
                            <PagerSettings Position="Top" />
                            <RowStyle CssClass="normalRow" />
                            <AlternatingRowStyle CssClass="alternativeRow" />
                            <PagerSettings Position="Top" Visible="False" />
                        </asp:GridView>
                        <asp:ObjectDataSource ID="odsBonusHistory" runat="server" SelectMethod="getUserBonusesHistoryTable"
                            TypeName="ZzimaBilling.AdminUI.DAL.EmployeeDAL">
                            <SelectParameters>
                                <asp:SessionParameter DefaultValue="-1" Name="userid" SessionField="UserID" Type="Int32" />
                                <asp:SessionParameter DefaultValue="null" Name="filter" SessionField="bonusFilterKey"
                                    Type="Object" />
                            </SelectParameters>
                        </asp:ObjectDataSource>
                    </div>
                </td>
            </tr>
        </table>
    </asp:Panel>
</asp:Content>
