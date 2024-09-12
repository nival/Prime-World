<%@ Page Language="C#" MasterPageFile="~/AdminUI/Templates/ZzimaUserProfile.Master"
    AutoEventWireup="true" CodeBehind="PaymentsHistory.aspx.cs" Inherits="ZzimaBilling.Admin.UserProfilePages.PaymentsHistory"
    Title="<%$ Resources: AdminUI, UserProfile.Menu.PaymentsHistory %>" 
    Culture="en-GB"%>

<%@ Register Assembly="System.Web.DataVisualization, Version=3.5.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35"
    Namespace="System.Web.UI.DataVisualization.Charting" TagPrefix="asp" %>
<%@ Register Src="../../Templates/WebUserControls/NumericalControl.ascx" TagName="NumericalControl"
    TagPrefix="uc2" %>
<%@ Register Src="../../Templates/WebUserControls/DateTimeParameter.ascx" TagName="DateTimeParameter"
    TagPrefix="uc1" %>
<asp:Content ID="Content" ContentPlaceHolderID="UserPageHolder" runat="server">
    <link href="../../css/Grid.css" rel="stylesheet" type="text/css" />
    <link href="../../css/Templates.css" rel="stylesheet" type="text/css" />
    <link href="../../css/Zzima.css" rel="stylesheet" type="text/css" />
    <asp:Panel ID="Panel1" DefaultButton="lbnApply" runat="server">
        <table class="tableInfo">
            <tr class="titleRowHeight">
                <td colspan="3">
                    <table>
                        <tr>
                            <td class="underLabel" valign="middle">
                                <asp:Label ID="lblActualBalance" runat="server" Text="<%$ Resources: AdminUI, PaymentsHistory.Title %>"></asp:Label>
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
                                <asp:Label ID="lblCBTAmountTitle" runat="server" Text="<%$ Resources: AdminUI, PaymentsHistory.Period %>"> </asp:Label>
                            </td>
                            <td>
                                <table>
                                    <tr>
                                        <td>
                                            <asp:CustomValidator ID="cvDate" runat="server" ErrorMessage="*" OnServerValidate="cvDate_ServerValidate"
                                                Display="Dynamic" ToolTip="<%$ resources:AdminUI, Reports.Validation.Dates %>"></asp:CustomValidator>
                                        </td>
                                        <td>
                                            <asp:Label ID="lblFrom" runat="server" Text="<%$ Resources: AdminUI, PaymentsHistory.From %>"
                                                Width="15px"> </asp:Label>
                                        </td>
                                        <td>
                                            <uc1:DateTimeParameter ID="dtFrom" runat="server" />
                                        </td>
                                        <td>
                                            <asp:Label ID="lblTo" runat="server" Text="<%$ Resources: AdminUI, PaymentsHistory.To %>"
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
                        <!--PaymentSystem-->
                        <tr class="titleRowHeight">
                            <td style="width: 189px">
                                <asp:Label ID="lblPaymentSystem" runat="server" Text="<%$ Resources: AdminUI, PaymentsHistory.PaymentSystem %>"></asp:Label>
                            </td>
                            <td>
                                <asp:DropDownList ID="ddlPaymentSystem" runat="server" CssClass="editBox" EnableViewState="true">
                                </asp:DropDownList>
                            </td>
                        </tr>
                        <tr class="titleRowHeight">
                            <td align="right" colspan="3">
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
                <td colspan="3" class="hSeparator" />
            </tr>
        </table>
        <table cellpadding="0" cellspacing="0" class="tableDetails">
            <tr>
                <td colspan="3">
                    <div id="tabStripDiv" class="tabStrip" runat="server">
                        <asp:Menu ID="tabControl" runat="server" Orientation="Horizontal" StaticEnableDefaultPopOutImage="False"
                            StaticMenuItemStyle-CssClass="tabStripNormalStyle" StaticSelectedStyle-CssClass="tabStripSelectedStyle"
                            OnMenuItemClick="OnTab_ItemClick">
                            <Items>
                                <asp:MenuItem Text="<%$ resources:AdminUI, PaymentsHistory.Tabs.pvDetails.Title %>"
                                    Value="pwDetails" Selected="true" />
                                <asp:MenuItem Text="<%$ resources:AdminUI, PaymentsHistory.Tabs.pvTransactions.Title %>"
                                    Value="pwTransactions" />
                                <asp:MenuItem Text="<%$ resources:AdminUI, PaymentsHistory.Tabs.pvMoneyAmount.Title %>"
                                    Value="pwMoneyAmount" />
                            </Items>
                        </asp:Menu>
                    </div>
                </td>
            </tr>
            <tr>
                <td colspan="3">
                    <div id="TabStripFrameDiv" class="tabStripFrame" runat="server">
                        <!--Pager-->
                        <asp:Panel ID="pgrDetails" runat="server">
                            <table cellpadding="0" cellspacing="0" width="100%">
                                <tr>
                                    <td align="left">
                                        <div>
                                            <table>
                                                <tr class="titleRowHeight">
                                                    <td>
                                                        <table>
                                                            <tr>
                                                                <td class="underLabel" valign="middle">
                                                                    <asp:Literal ID="Literal8" runat="server" Text="<%$ resources:AdminUI, Users.Result %>"></asp:Literal>
                                                                    <img alt="" src="../../Images/arrow.gif" class="arrowIcon" />
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
                                                        <asp:Label ID="PageNumberLabel" CssClass="labelCount" runat="server" Text="0" />
                                                        <asp:Literal ID="Literal10" runat="server" Text="<%$ resources: AdminUI, Pager.Of%>" />
                                                        <asp:Label ID="TotalPagesLabel" CssClass="labelCount" runat="server" Text="0" />
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
                        <!--MultiView-->
                        <asp:MultiView ID="MultiPageDetails" runat="server">
                            <asp:View ID="pwDetails" runat="server">
                                <table width="100%">
                                    <tr>
                                        <td>
                                            <!--GridView-->
                                            <asp:GridView ID="gvDetails" runat="server" AllowPaging="True" PageSize="20" Width="100%"
                                                AutoGenerateColumns="False" DataSourceID="odsDetails" OnSorted="gvDetails_Sorted">
                                                <HeaderStyle CssClass="headerRow" VerticalAlign="Middle" />
                                                <PagerSettings Visible="False" />
                                                <RowStyle CssClass="normalRow" />
                                                <AlternatingRowStyle CssClass="alternativeRow" />
                                                <Columns>
                                                    <asp:BoundField DataField="Date" HeaderText="<%$ Resources: AdminUI, PaymentsHistory.Details.GridView.DateAndTime %>"
                                                        SortExpression="Date" />
                                                    <asp:BoundField DataField="PaymentSystem" HeaderText="<%$ Resources: AdminUI, PaymentsHistory.Details.GridView.PaymentSystem %>"
                                                        SortExpression="PaymentSystem" />
                                                    <asp:BoundField DataField="Amount" HeaderText="<%$ Resources: AdminUI, PaymentsHistory.Details.GridView.Sum %>"
                                                        SortExpression="Amount" />
                                                </Columns>
                                            </asp:GridView>
                                        </td>
                                    </tr>
                                    <tr>
                                        <td>
                                            <table class="tableInfo" width="100%">
                                                <tr class="titleRowHeight">
                                                    <td>
                                                        <asp:Label ID="lblTotalCountTitle" runat="server" Text="<%$ resources:AdminUI, PaymentsHistory.Details.TotalCount %>"></asp:Label>
                                                    </td>
                                                    <td>
                                                        <asp:Label ID="lblTotalCountValue" runat="server" Text="0" CssClass="labelCount"></asp:Label>
                                                    </td>
                                                </tr>
                                                <tr class="titleRowHeight">
                                                    <td>
                                                        <asp:Label ID="lblTotalAmountTitle" runat="server" Text="<%$ resources:AdminUI, PaymentsHistory.Details.TotalMoney %>"></asp:Label>
                                                    </td>
                                                    <td>
                                                        <asp:Label ID="lblTotalAmountValue" runat="server" Text="0" CssClass="labelCount"></asp:Label>
                                                    </td>
                                                </tr>
                                                <tr class="titleRowHeight">
                                                    <td>
                                                        <asp:Label ID="lblDiffPSTitle" runat="server" Text="<%$ resources:AdminUI, PaymentsHistory.Details.DiffPS %>"></asp:Label>
                                                    </td>
                                                    <td>
                                                        <asp:Label ID="lblDiffPSValue" runat="server" CssClass="labelCount" Text="0"></asp:Label>
                                                    </td>
                                                </tr>
                                            </table>
                                            <asp:ObjectDataSource ID="odsDetails" runat="server" OldValuesParameterFormatString="original_{0}"
                                                SelectMethod="getUserPaymentsHistoryTable" TypeName="ZzimaBilling.AdminUI.DAL.EmployeeDAL">
                                                <SelectParameters>
                                                    <asp:SessionParameter Name="userid" SessionField="UserID" Type="Int32" />
                                                    <asp:SessionParameter Name="filter" SessionField="Filter" Type="Object" />
                                                </SelectParameters>
                                            </asp:ObjectDataSource>
                                        </td>
                                    </tr>
                                </table>
                            </asp:View>
                            <asp:View ID="pwTransactions" runat="server">
                                <table width="100%">
                                    <tr>
                                        <td style="width: 100%">
                                            <!--GridView-->
                                            <asp:GridView ID="gvTransactions" runat="server" AllowPaging="True" PageSize="3"
                                                Width="100%" AutoGenerateColumns="False" AllowSorting="True" DataSourceID="odsTransactions"
                                                OnSorted="gvTransactions_Sorted">
                                                <Columns>
                                                    <asp:BoundField DataField="Place" HeaderText="<%$ Resources: AdminUI, PaymentsHistory.Transactions.GridView.Place %>"
                                                        SortExpression="Place" />
                                                    <asp:BoundField DataField="PaymentSystem" HeaderText="<%$ Resources: AdminUI, PaymentsHistory.Transactions.GridView.PaymentSystem %>"
                                                        SortExpression="PaymentSystem" />
                                                    <asp:BoundField DataField="Count" HeaderText="<%$ Resources: AdminUI, PaymentsHistory.Transactions.GridView.Count %>"
                                                        SortExpression="Count" />
                                                    <asp:BoundField DataField="Percent" HeaderText="<%$ Resources: AdminUI, PaymentsHistory.Transactions.GridView.Percent %>"
                                                        SortExpression="Percent" DataFormatString="<%$ resources: AdminUI, PaymentsHistory.PercentFormat %>" />
                                                </Columns>
                                                <HeaderStyle CssClass="headerRow" VerticalAlign="Middle" />
                                                <PagerSettings Visible="False" />
                                                <RowStyle CssClass="normalRow" />
                                                <AlternatingRowStyle CssClass="alternativeRow" />
                                            </asp:GridView>
                                        </td>
                                    </tr>
                                    <tr>
                                        <td align="center">
                                            <asp:Chart ID="chrtTransactions" runat="server" BackColor="236, 233, 228" Width="1000px"
                                                ImageStorageMode="UseHttpHandler" ImageType="Jpeg" Height="500px">
                                                <Series>
                                                    <asp:Series Name="Series1" ChartType="Pie">
                                                    </asp:Series>
                                                </Series>
                                                <ChartAreas>
                                                    <asp:ChartArea Name="ChartArea1" BackColor="236, 233, 228">
                                                        <Area3DStyle Enable3D="true" />
                                                    </asp:ChartArea>
                                                </ChartAreas>
                                            </asp:Chart>
                                        </td>
                                    </tr>
                                </table>
                                <asp:ObjectDataSource ID="odsTransactions" runat="server" SelectMethod="getUserPaymentsHistoryCTTable"
                                    TypeName="ZzimaBilling.AdminUI.DAL.EmployeeDAL">
                                    <SelectParameters>
                                        <asp:SessionParameter Name="userid" SessionField="UserID" Type="Int32" />
                                        <asp:SessionParameter Name="filter" SessionField="Filter" Type="Object" />
                                    </SelectParameters>
                                </asp:ObjectDataSource>
                            </asp:View>
                            <asp:View ID="pwMoneyAmount" runat="server">
                                <table width="100%">
                                    <tr>
                                        <td>
                                            <!--GridView-->
                                            <asp:GridView ID="gvMoney" runat="server" AllowPaging="True" AutoGenerateColumns="False"
                                                PageSize="3" Width="100%" AllowSorting="True" DataSourceID="odsMoney" OnSorted="gvMoney_Sorted">
                                                <Columns>
                                                    <asp:BoundField DataField="Place" HeaderText="<%$ Resources: AdminUI, PaymentsHistory.Money.GridView.Place %>"
                                                        SortExpression="Place" />
                                                    <asp:BoundField DataField="PaymentSystem" HeaderText="<%$ Resources: AdminUI, PaymentsHistory.Money.GridView.PS %>"
                                                        SortExpression="PaymentSystem" />
                                                    <asp:BoundField DataField="Amount" HeaderText="<%$ Resources: AdminUI, PaymentsHistory.Money.GridView.Bought %>"
                                                        SortExpression="Amount" />
                                                    <asp:BoundField DataField="Percent" HeaderText="<%$ Resources: AdminUI, PaymentsHistory.Money.GridView.Percent %>"
                                                        SortExpression="Percent" DataFormatString="<%$ resources: AdminUI, PaymentsHistory.PercentFormat %>" />
                                                </Columns>
                                                <HeaderStyle CssClass="headerRow" VerticalAlign="Middle" />
                                                <PagerSettings Visible="False" />
                                                <RowStyle CssClass="normalRow" />
                                                <AlternatingRowStyle CssClass="alternativeRow" />
                                            </asp:GridView>
                                        </td>
                                    </tr>
                                    <tr>
                                        <td align="center">
                                            <asp:Chart ID="chrtMoneyAmount" runat="server" Width="1000px" BackColor="236, 233, 228"
                                                ImageStorageMode="UseHttpHandler" ImageType="Jpeg" Height="500px">
                                                <Series>
                                                    <asp:Series Name="Series1" ChartType="Pie">
                                                    </asp:Series>
                                                </Series>
                                                <ChartAreas>
                                                    <asp:ChartArea Name="ChartArea1" BackColor="236, 233, 228">
                                                        <Area3DStyle Enable3D="true" />
                                                    </asp:ChartArea>
                                                </ChartAreas>
                                            </asp:Chart>
                                        </td>
                                    </tr>
                                </table>
                                <asp:ObjectDataSource ID="odsMoney" runat="server" SelectMethod="getUserPaymentsHistoryCMTable"
                                    SelectCountMethod="getUserPaymentsHistoryCMCount" TypeName="ZzimaBilling.AdminUI.DAL.EmployeeDAL">
                                    <SelectParameters>
                                        <asp:SessionParameter Name="userid" SessionField="UserID" Type="Int32" />
                                        <asp:SessionParameter Name="filter" SessionField="Filter" Type="Object" />
                                    </SelectParameters>
                                </asp:ObjectDataSource>
                            </asp:View>
                        </asp:MultiView>
                    </div>
                </td>
            </tr>
            <tr>
                <td colspan="3">
                </td>
            </tr>
        </table>
    </asp:Panel>
</asp:Content>
