<%@ Page Language="C#" MasterPageFile="~/AdminUI/Templates/ZzimaMaster.Master" Title="<%$ resources:AdminUI, Title.Users %>"
    AutoEventWireup="true" CodeBehind="Users.aspx.cs" Inherits="ZzimaBilling.Admin.Users" %>

<%@ Register Assembly="ZzimaBilling" Namespace="ZzimaBilling.Controls" TagPrefix="cc1" %>
<%@ Register Src="../Templates/WebUserControls/NumericalControl.ascx" TagName="NumericalControl"
    TagPrefix="uc1" %>
<%@ Register Src="../Templates/WebUserControls/TextParameter.ascx" TagName="TextParameter"
    TagPrefix="uc2" %>
<asp:Content ID="Content1" ContentPlaceHolderID="BodyPlaceHolder" runat="server">
    <link href="../css/Grid.css" rel="stylesheet" type="text/css" />
    <link href="../css/Templates.css" rel="stylesheet" type="text/css" />
    <link href="../css/Zzima.css" rel="stylesheet" type="text/css" />
    <link href="../css/Users.css" rel="stylesheet" type="text/css" />
    <asp:Panel DefaultButton="btnSearch" runat="server">
        <div>
            <!--Search table-->
            <table style="padding-top: 10px; width: 100%;">
                <tr class="filterRowHeight">
                    <td valign="middle" width="150px">
                        <table>
                            <tr>
                                <td class="underLabel" valign="middle">
                                    <asp:Literal ID="Literal1" runat="server" Text="<%$ resources:AdminUI, Users.Filter %>"></asp:Literal>
                                    <img alt="" src="../Images/arrow.gif" class="arrowIcon" />
                                </td>
                            </tr>
                        </table>
                    </td>
                    <td class="fieldsLabel">
                        <asp:Literal ID="Literal2" runat="server" Text="<%$ resources:AdminUI, Users.UsernameTitle %>"></asp:Literal>
                    </td>
                    <td width="300px">
                        <asp:TextBox runat="server" CssClass="editBox" ID="tpUsername"></asp:TextBox>
                    </td>
                    <td>
                        &nbsp;
                    </td>
                </tr>
                <!--добавляем поиск по userID-->
                <tr class="filterRowHeight">
                    <td>
                        &nbsp
                    </td>
                    <td class="fieldsLabel">
                        <asp:Literal ID="Literal11" runat="server" Text="userID"></asp:Literal>
                    </td>
                    <td>
                        <asp:TextBox ID="txtUserId" CssClass="editBox" runat="server"></asp:TextBox>
                    </td>
                    <td>
                        &nbsp;
                    </td>
                </tr>
                <asp:RegularExpressionValidator ID="RegularExpressionValidator1" ASPClass="RegularExpressionValidator"
                    ControlToValidate="txtUserId" ValidationExpression="\d{1,10}"
                    runat="server" ErrorMessage="not valid userID"></asp:RegularExpressionValidator>
                <tr class="filterRowHeight">
                    <td>
                        &nbsp
                    </td>
                    <td class="fieldsLabel">
                        <asp:Literal ID="Literal3" runat="server" Text="<%$ resources:AdminUI, Users.EmailTitle %>"></asp:Literal>
                    </td>
                    <td>
                        <asp:TextBox ID="tpEmail" CssClass="editBox" runat="server"></asp:TextBox>
                    </td>
                    <td>
                        &nbsp;
                    </td>
                </tr>
                <tr class="filterRowHeight">
                    <td>
                        &nbsp
                    </td>
                    <td class="fieldsLabel">
                        <asp:Literal ID="Literal4" runat="server" Text="<%$ resources:AdminUI, Users.TotalBalanceTitle %>"></asp:Literal>
                    </td>
                    <td colspan="2">
                        <uc1:NumericalControl ID="ncTotal" runat="server" />
                    </td>
                </tr>
                <tr class="filterRowHeight">
                    <td>
                        &nbsp
                    </td>
                    <td class="fieldsLabel">
                        <asp:Literal ID="Literal5" runat="server" Text="<%$ resources:AdminUI, Users.RealBalanceTitle %>"></asp:Literal>
                    </td>
                    <td colspan="2">
                        <uc1:NumericalControl ID="ncReal" runat="server" />
                    </td>
                </tr>
                <tr class="filterRowHeight">
                    <td>
                        &nbsp
                    </td>
                    <td class="fieldsLabel">
                        <asp:Literal ID="Literal6" runat="server" Text="<%$ resources:AdminUI, Users.BonusBalanceTitle %>"></asp:Literal>
                    </td>
                    <td colspan="2">
                        <uc1:NumericalControl ID="ncBonus" runat="server" />
                    </td>
                </tr>
                <tr class="filterRowHeight">
                    <td>
                        &nbsp
                    </td>
                    <td class="fieldsLabel">
                        <asp:Literal ID="Literal7" runat="server" Text="<%$ resources:AdminUI, Users.PartnerProgramTitle %>"></asp:Literal>
                    </td>
                    <td>
                        <asp:DropDownList ID="ddlPartnerProgram" runat="server" CssClass="editBox">
                            <asp:ListItem Selected="True" Text="<%$ resources:AdminUI, Users.ChoosePartnerProgram %>"
                                Value=""></asp:ListItem>
                        </asp:DropDownList>
                    </td>
                    <td>
                        &nbsp;
                    </td>
                </tr>
                <tr class="filterRowHeight">
                    <td colspan="3">
                        &nbsp;
                    </td>
                    <td align="right" valign="bottom">
                        <div class="searchImg">
                            <asp:LinkButton ID="btnSearch" CssClass="button" runat="server" Text="<%$ resources:AdminUI, Button.Search %>"
                                OnClick="btnSearch_Click">
                            </asp:LinkButton>
                        </div>
                    </td>
                </tr>
                <tr height="4">
                    <td colspan="4" class="hSeparator">
                    </td>
                </tr>
            </table>
        </div>
        <div id="GridViewDiv" width="100%">
            <table width="100%" cellpadding="0" cellspacing="0">
                <tr>
                    <td>
                        <div style="height: 292px;" id="PagerAndGridView" runat="server">
                            <!--Pager-->
                            <asp:Panel ID="gvPagerRow" runat="server">
                                <table cellpadding="0" cellspacing="0" width="100%">
                                    <tr>
                                        <td align="left">
                                            <div>
                                                <table>
                                                    <tr class="filterRowHeight">
                                                        <td>
                                                            <table>
                                                                <tr>
                                                                    <td class="underLabel" valign="middle">
                                                                        <asp:Literal ID="Literal8" runat="server" Text="<%$ resources:AdminUI, Users.Result %>"></asp:Literal>
                                                                        <img alt="" src="../Images/arrow.gif" class="arrowIcon" />
                                                                    </td>
                                                                </tr>
                                                            </table>
                                                        </td>
                                                        <td>
                                                            &nbsp;
                                                        </td>
                                                        <td>
                                                            <asp:Label ID="lblTotalCount" runat="server" Text="<%$ resources:AdminUI, Users.TotalCount %>"></asp:Label>
                                                        </td>
                                                        <td>
                                                            &nbsp;
                                                        </td>
                                                        <td>
                                                            <asp:Label ID="lblCount" class="labelCount" runat="server" Text=""></asp:Label>
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
                                        <td align="right" width="1px" style="padding-left: 10px">
                                            <asp:ImageButton ID="btnExport" runat="server" ImageUrl="~/AdminUI/Images/icon-xlsx.gif"
                                                OnClick="btnExport_Click" ToolTip="<%$ resources:AdminUI, Tooltip.Export2Xls %>" />
                                        </td>
                                    </tr>
                                </table>
                            </asp:Panel>
                            <!--GridView-->
                            <asp:GridView ID="gvUsers" runat="server" OnRowCreated="gvUsers_RowCreated" PageSize="6"
                                GridLines="Vertical" BorderWidth="1px" CellPadding="3" Width="100%" OnRowDataBound="gvUsers_RowDataBound"
                                AllowSorting="True" AutoGenerateColumns="False" OnSorting="gvUsers_Sorting">
                                <PagerSettings Position="Top" Mode="NumericFirstLast"></PagerSettings>
                                <PagerStyle HorizontalAlign="Right" />
                                <Columns>
                                    <asp:BoundField HeaderText="id" Visible="False" />
                                    <asp:BoundField DataField="Username" HeaderText="<%$ resources: AdminUI, Users.GridView.Headers.Username %>"
                                        SortExpression="Username">
                                        <HeaderStyle Font-Underline="False" />
                                    </asp:BoundField>
                                    <asp:BoundField DataField="id" HeaderText="userID" SortExpression="id" />
                                    <asp:BoundField DataField="email" HeaderText="<%$ resources: AdminUI, Users.GridView.Headers.Email%>"
                                        SortExpression="email" />
                                    <asp:BoundField DataField="Total" HeaderText="<%$ resources: AdminUI, Users.GridView.Headers.Total%>"
                                        SortExpression="Total" />
                                    <asp:BoundField DataField="RealBalance" HeaderText="<%$ resources: AdminUI, Users.GridView.Headers.Real%>"
                                        SortExpression="RealBalance" />
                                    <asp:BoundField DataField="BonusMoney" HeaderText="<%$ resources: AdminUI, Users.GridView.Headers.Bonus%>"
                                        SortExpression="BonusMoney" />
                                    <asp:BoundField DataField="PartnerProgram" HeaderText="<%$ resources: AdminUI, Users.GridView.Headers.PartnerProgram%>"
                                        SortExpression="PartnerProgram" />
                                </Columns>
                                <FooterStyle BorderWidth="1px" />
                                <SelectedRowStyle Font-Bold="True" ForeColor="White" />
                                <HeaderStyle CssClass="headerRow" VerticalAlign="Middle" />
                                <RowStyle CssClass="normalRow" />
                                <AlternatingRowStyle CssClass="alternativeRow" />
                            </asp:GridView>
                        </div>
                    </td>
                </tr>
            </table>
        </div>
    </asp:Panel>
    <%--    </div>--%>
</asp:Content>
