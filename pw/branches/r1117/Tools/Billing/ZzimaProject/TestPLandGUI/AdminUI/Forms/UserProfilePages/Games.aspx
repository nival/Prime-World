<%@ Page Language="C#" AutoEventWireup="true" MasterPageFile="~/AdminUI/Templates/ZzimaUserProfile.Master"
    CodeBehind="Games.aspx.cs" Inherits="ZzimaBilling.AdminUI.Forms.UserProfilePages.Games"
    Title="<%$ Resources: AdminUI, UserProfile.Menu.Games %>"
    Culture="en-GB" %>

<asp:Content ID="Content" ContentPlaceHolderID="UserPageHolder" runat="server">
    <link href="../../css/Grid.css" rel="stylesheet" type="text/css" />
    <link href="../../css/Zzima.css" rel="stylesheet" type="text/css" />
    <table  class="tableInfo">
        <tr class="titleRowHeight">
            <td colspan="2">
                <div>
                    <table>
                        <tr>
                            <td class="underLabel" valign="middle">
                                <asp:Label ID="lblGames" runat="server" Text="<%$ Resources: AdminUI, Games.Title %>"></asp:Label>
                                <img alt="" src="../../Images/arrow.gif" class="arrowIcon" />
                            </td>
                        </tr>
                    </table>
                </div>
            </td>
        </tr>
        <tr class="titleRowHeight">
            <td class="dummySpace">
                <table class="dummySpace" style="table-layout:fixed;">
                </table>            
            </td>
            <td style="width:100%;">
                <asp:Label ID="lblDetails" runat="server" CssClass="underlineLabel" Text="<%$ Resources: AdminUI, Games.Details %>"></asp:Label>
            </td>
        </tr>
        <tr>
            <td colspan="2">
                <!--Pager-->
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
                <asp:GridView ID="gvLastSessions" runat="server" GridLines="Vertical" BorderWidth="1px"
                    CellPadding="3" AutoGenerateColumns="False" AllowPaging="True" AllowSorting="True"
                    PageSize="20" DataSourceID="odsGames" OnRowCreated="gvLastSessions_RowCreated"
                    OnSorting="gvLastSessions_Sorting" Width="100%">
                    <PagerStyle HorizontalAlign="Right" />
                    <Columns>
                        <asp:BoundField DataField="Name" HeaderText="<%$ Resources: AdminUI, Games.GridView.Headers.Game %>"
                            ReadOnly="true" SortExpression="Name">
                        </asp:BoundField>
                        <asp:BoundField DataField="LastSessionDate" DataFormatString="{0:d}" htmlencode="false" HeaderText="<%$ Resources: AdminUI, Games.GridView.Headers.LastSessionDate %>"
                            ReadOnly="True" SortExpression="LastSessionDate" >
                        <HeaderStyle Width="40%" />
                        </asp:BoundField>
                        <asp:BoundField DataField="LastSessionTime" HeaderText="<%$ Resources: AdminUI, Games.GridView.Headers.LastSessionTime %>"
                            ReadOnly="True" SortExpression="LastSessionTime" >
                        <HeaderStyle Width="35%" />
                        </asp:BoundField>
                    </Columns>
                    <HeaderStyle CssClass="headerRow" VerticalAlign="Middle" />
                    <PagerSettings Position="Top" />
                    <RowStyle CssClass="normalRow" />
                    <AlternatingRowStyle CssClass="alternativeRow" />
                    <PagerSettings Position="Top" Visible="False" />
                </asp:GridView>
                <asp:ObjectDataSource ID="odsGames" runat="server" SelectMethod="GetLastSessionsTable"
                    TypeName="ZzimaBilling.AdminUI.DAL.UserDAL">
                    <SelectParameters>
                        <asp:SessionParameter DefaultValue="-1" Name="userID" SessionField="UserID" Type="Int32" />
                    </SelectParameters>
                </asp:ObjectDataSource>
            </td>
        </tr>
    </table>
</asp:Content>
