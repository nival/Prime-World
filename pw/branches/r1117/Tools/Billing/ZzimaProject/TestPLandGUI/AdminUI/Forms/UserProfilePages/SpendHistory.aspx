<%@ Page Language="C#" AutoEventWireup="true" MasterPageFile="~/AdminUI/Templates/ZzimaUserProfile.Master"
    CodeBehind="SpendHistory.aspx.cs" Inherits="ZzimaBilling.AdminUI.Forms.UserProfilePages.SpendHistory"
    Title="<%$ Resources: AdminUI, UserProfile.Menu.SpendHistory %>"
    Culture="en-GB" %>

<%@ Register Src="../../Templates/WebUserControls/DateTimeParameter.ascx" TagName="DateTimeParameter"
    TagPrefix="uc1" %>
<%@ Register Src="../../Templates/WebUserControls/NumericalControl.ascx" TagName="NumericalControl"
    TagPrefix="uc2" %>
<asp:Content ID="Content" ContentPlaceHolderID="UserPageHolder" runat="server">
    <link href="../../css/Grid.css" rel="stylesheet" type="text/css" />
    <link href="../../css/Templates.css" rel="stylesheet" type="text/css" />
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

    <asp:Panel ID="Panel1" DefaultButton="lbnApply" runat="server">
        <table class="tableInfo">
            <tr class="titleRowHeight">
                <td colspan="3">
                    <table>
                        <tr>
                            <td class="underLabel" valign="middle">
                                <asp:Label ID="lblSpendHistoryTitle" runat="server" Text="<%$ Resources:AdminUI, SpendHistory.Title %>"></asp:Label>
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
                <td style="width: 200px">
                    <asp:Label ID="Label1" runat="server" Text="<%$ Resources: AdminUI, PaymentsHistory.Period %>" />
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
                                    Width="15px">
                                </asp:Label>
                            </td>
                            <td>
                                <uc1:DateTimeParameter ID="dtFrom" runat="server" />
                            </td>
                            <td>
                                <asp:Label ID="lblTo" runat="server" Text="<%$ Resources: AdminUI, PaymentsHistory.To %>"
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
            <!--Game-->
            <tr height="85px">
                <td>
                    &nbsp;
                </td>
                <td style="width: 189px" valign="top">
                    <asp:Label ID="lblGame" runat="server" Text="<%$ Resources: AdminUI, SpendHistory.Game %>"></asp:Label>
                </td>
                <td>
                    <table>
                        <tr>
                            <td>
                                <input id="chkGamesId" type="checkbox" enableviewstate="true" onclick="checkedAll(document.forms[0].chkGamesId.checked, '<%=chlGames.ClientID %>');" />
                                <asp:Literal ID="Literal1" runat="server" Text="<%$ Resources: AdminUI, SpendHistory.CheckAll %>"></asp:Literal>
                            </td>
                        </tr>
                        <tr>
                            <td colspan="2">
                                <div class="smallCheckBoxList">
                                    <asp:CheckBoxList ID="chlGames" runat="server" CssClass="controls">
                                    </asp:CheckBoxList>
                                </div>
                            </td>
                        </tr>
                    </table>
                </td>
            </tr>
            <!--Subject-->
            <tr height="85px">
                <td>
                    &nbsp;
                </td>
                <td style="width: 189px" valign="top">
                    <asp:Label ID="lblSubject" runat="server" Text="<%$ Resources:AdminUI, SpendHistory.Subject %>"></asp:Label>
                </td>
                <td>
                    <table>
                        <tr>
                            <td>
                                <input id="chkSubjectsId" type="checkbox" enableviewstate="true" onclick="checkedAll(document.forms[0].chkSubjectsId.checked, '<%=chlSubjects.ClientID %>');" />
                                <asp:Literal ID="Literal2" runat="server" Text="<%$ Resources: AdminUI, SpendHistory.CheckAll %>"></asp:Literal>
                            </td>
                        </tr>
                        <tr>
                            <td colspan="2">
                                <div class="smallCheckBoxList">
                                    <asp:CheckBoxList ID="chlSubjects" runat="server" CssClass="controls">
                                    </asp:CheckBoxList>
                                </div>
                            </td>
                        </tr>
                    </table>
                </td>
                <!--Amount-->
                <tr class="titleRowHeight">
                    <td>
                        &nbsp;
                    </td>
                    <td style="width: 189px">
                        <asp:Label ID="lblAmount" runat="server" Text="<%$ Resources:AdminUI, SpendHistory.Sum %>"></asp:Label>
                    </td>
                    <td>
                        <uc2:NumericalControl ID="ncAmount" runat="server" />
                    </td>
                </tr>
                <!--Button Apply-->
                <tr class="titleRowHeight">
                    <td align="right" colspan="3">
                        <div class="applyImg">
                            <asp:LinkButton ID="lbnApply" CssClass="buttonMid" Text="<%$ resources:AdminUI, Button.Apply %>"
                                runat="server" OnClick="lbnApply_Click"></asp:LinkButton>
                        </div>
                    </td>
                </tr>
                <tr height="4">
                    <td colspan="3" class="hSeparator" />
                </tr>
        </table>
        <table cellpadding="0" cellspacing="0" class="tableDetails">
            <tr>
                <td colspan="3">
                </td>
            </tr>
            <tr>
                <td colspan="3">
                    <div id="tabStripDiv" runat="server" class="tabStrip">
                        <asp:Menu ID="tabControl" runat="server" Orientation="Horizontal" StaticEnableDefaultPopOutImage="False"
                            StaticMenuItemStyle-CssClass="tabStripNormalStyle" StaticSelectedStyle-CssClass="tabStripSelectedStyle"
                            OnMenuItemClick="OnTab_ItemClick">
                            <Items>
                                <asp:MenuItem Text="<%$ resources:AdminUI, SpendHistory.Tabs.pvDetails.Title %>"
                                    Value="pvDetails" Selected="true" />
                                <asp:MenuItem Text="<%$ resources:AdminUI, SpendHistory.Tabs.pvSCT.Title %>" Value="pvSCT">
                                </asp:MenuItem>
                                <asp:MenuItem Text="<%$ resources:AdminUI, SpendHistory.Tabs.pvSCM.Title %>" Value="pvSCM">
                                </asp:MenuItem>
                                <asp:MenuItem Text="<%$ resources:AdminUI, SpendHistory.Tabs.pvRCT.Title %>" Value="pvRCT">
                                </asp:MenuItem>
                                <asp:MenuItem Text="<%$ resources:AdminUI, SpendHistory.Tabs.pvRCM.Title %>" Value="pvRCM">
                                </asp:MenuItem>
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
                                                            CssClass="labelCount" Text="<%$ resources: AdminUI, Pager.First %>" ToolTip="<%$ resources: AdminUI, Pager.Tip.First %>"
                                                            Enabled="false"></asp:LinkButton>
                                                    </td>
                                                    <td>
                                                        <asp:LinkButton ID="lnkPrevPage" CommandName="Page" CommandArgument="Prev" runat="server"
                                                            Text="<%$ resources: AdminUI, Pager.Prev %>" CssClass="labelCount" ToolTip="<%$ resources: AdminUI, Pager.Tip.Prev %>"
                                                            Enabled="false"></asp:LinkButton>
                                                    </td>
                                                    <td>
                                                        <asp:LinkButton ID="lnkNextPage" CommandName="Page" CommandArgument="Next" runat="server"
                                                            Text="<%$ resources: AdminUI, Pager.Next %>" CssClass="labelCount" ToolTip="<%$ resources: AdminUI, Pager.Tip.Next %>"
                                                            Enabled="false"></asp:LinkButton>
                                                    </td>
                                                    <td>
                                                        <asp:LinkButton ID="lnkLastPage" CommandName="Page" CommandArgument="Last" runat="server"
                                                            Text="<%$ resources: AdminUI, Pager.Last %>" CssClass="labelCount" ToolTip="<%$ resources: AdminUI, Pager.Tip.Last %>"
                                                            Enabled="false"></asp:LinkButton>
                                                    </td>
                                                </tr>
                                            </table>
                                        </div>
                                    </td>
                                </tr>
                            </table>
                        </asp:Panel>
                        <!--Multi View-->
                        <asp:MultiView ID="MultiPageDetails" runat="server">
                            <asp:View ID="pvDetails" runat="server">
                                <table width="100%">
                                    <tr>
                                        <td colspan="2">
                                            <asp:GridView ID="gvDetails" runat="server" AllowPaging="True" AllowSorting="True"
                                                AutoGenerateColumns="False" PageSize="20" Width="100%" OnSorted="gvDetails_Sorted">
                                                <Columns>
                                                    <asp:BoundField DataField="DateTime" HeaderText="<%$ resources: AdminUI, SpendHistory.gvDetails.DateTime %>"
                                                        SortExpression="DateTime" />
                                                    <asp:BoundField DataField="Amount" HeaderText="<%$ resources: AdminUI, SpendHistory.gvDetails.Amount %>"
                                                        SortExpression="Amount" />
                                                    <asp:BoundField DataField="ServiceName" HeaderText="<%$ resources: AdminUI, SpendHistory.gvDetails.Game %>"
                                                        SortExpression="ServiceName" />
                                                    <asp:BoundField DataField="Reason" HeaderText="<%$ resources: AdminUI, SpendHistory.gvDetails.Subject %>"
                                                        SortExpression="Reason" />
                                                </Columns>
                                                <HeaderStyle CssClass="headerRow" VerticalAlign="Middle" />
                                                <PagerSettings Visible="False" />
                                                <RowStyle CssClass="normalRow" />
                                                <AlternatingRowStyle CssClass="alternativeRow" />
                                            </asp:GridView>
                                        </td>
                                    </tr>
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
                                </table>
                            </asp:View>
                            <asp:View ID="pvSCT" runat="server">
                                <table width="100%">
                                    <tr>
                                        <td>
                                            <asp:GridView ID="gvSCT" runat="server" AllowPaging="True" AllowSorting="True" AutoGenerateColumns="False"
                                                PageSize="20" Width="100%" OnSorted="gvSCT_Sorted">
                                                <Columns>
                                                    <asp:BoundField DataField="Place" HeaderText="<%$ resources: AdminUI, SpendHistory.gvSCT.Place %>"
                                                        SortExpression="Place" />
                                                    <asp:BoundField DataField="ServiceName" HeaderText="<%$ resources: AdminUI, SpendHistory.gvSCT.Game %>"
                                                        SortExpression="ServiceName" />
                                                    <asp:BoundField DataField="Count" HeaderText="<%$ resources: AdminUI, SpendHistory.gvSCT.TransactionsAmount %>"
                                                        SortExpression="Count" />
                                                    <asp:BoundField DataField="Percent" HeaderText="<%$ resources: AdminUI, SpendHistory.gvSCT.Percent %>"
                                                        SortExpression="Percent" DataFormatString="<%$ resources: AdminUI, SpendHistory.PercentFormat %>" />
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
                                            <asp:Chart ID="chrtSCT" runat="server" BackColor="236, 233, 228" Width="1000px" ImageStorageMode="UseHttpHandler"
                                                ImageType="Jpeg" Height="500px">
                                                <Series>
                                                    <asp:Series Name="Series1" ChartType="Pie">
                                                        <SmartLabelStyle IsOverlappedHidden="false" />
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
                            </asp:View>
                            <asp:View ID="pvSCM" runat="server">
                                <table width="100%">
                                    <tr>
                                        <td>
                                            <asp:GridView ID="gvSCM" runat="server" AllowPaging="True" AllowSorting="True" AutoGenerateColumns="False"
                                                PageSize="20" Width="100%" OnSorted="gvSCM_Sorted">
                                                <Columns>
                                                    <asp:BoundField DataField="Place" HeaderText="<%$ resources: AdminUI, SpendHistory.gvSCM.Place %>"
                                                        SortExpression="Place" />
                                                    <asp:BoundField DataField="ServiceName" HeaderText="<%$ resources: AdminUI, SpendHistory.gvSCM.Game %>"
                                                        SortExpression="ServiceName" />
                                                    <asp:BoundField DataField="Amount" HeaderText="<%$ resources: AdminUI, SpendHistory.gvSCM.Amount %>"
                                                        SortExpression="Amount" />
                                                    <asp:BoundField DataField="Percent" HeaderText="<%$ resources: AdminUI, SpendHistory.gvSCM.Percent %>"
                                                        SortExpression="Percent" DataFormatString="<%$ resources: AdminUI, SpendHistory.PercentFormat %>" />
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
                                            <asp:Chart ID="chrtSCM" runat="server" BackColor="236, 233, 228" Width="1000px" ImageStorageMode="UseHttpHandler"
                                                ImageType="Jpeg" Height="500px">
                                                <Series>
                                                    <asp:Series Name="Series1" ChartType="Pie">
                                                        <SmartLabelStyle IsOverlappedHidden="false" />
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
                            </asp:View>
                            <asp:View ID="pvRCT" runat="server">
                                <table width="100%">
                                    <tr>
                                        <td>
                                            <asp:GridView ID="gvRCT" runat="server" AllowPaging="True" AllowSorting="True" AutoGenerateColumns="False"
                                                PageSize="20" Width="100%" OnSorted="gvRCT_Sorted">
                                                <Columns>
                                                    <asp:BoundField DataField="Place" HeaderText="<%$ resources: AdminUI, SpendHistory.gvRCT.Place %>"
                                                        SortExpression="Place" />
                                                    <asp:BoundField DataField="Reason" HeaderText="<%$ resources: AdminUI, SpendHistory.gvRCT.Reason %>"
                                                        SortExpression="Reason" />
                                                    <asp:BoundField DataField="Count" HeaderText="<%$ resources: AdminUI, SpendHistory.gvRCT.TransactionsAmount %>"
                                                        SortExpression="Count" />
                                                    <asp:BoundField DataField="Percent" HeaderText="<%$ resources: AdminUI, SpendHistory.gvRCT.Percent %>"
                                                        SortExpression="Percent" DataFormatString="<%$ resources: AdminUI, SpendHistory.PercentFormat %>" />
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
                                            <asp:Chart ID="chrtRCT" runat="server" BackColor="236, 233, 228" Width="1000px" ImageStorageMode="UseHttpHandler"
                                                ImageType="Jpeg" Height="500px">
                                                <Series>
                                                    <asp:Series Name="Series1" ChartType="Pie">
                                                        <SmartLabelStyle IsOverlappedHidden="false" />
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
                            </asp:View>
                            <asp:View ID="pvRCM" runat="server">
                                <table width="100%">
                                    <tr>
                                        <td>
                                            <asp:GridView ID="gvRCM" runat="server" AllowPaging="True" AllowSorting="True" AutoGenerateColumns="False"
                                                PageSize="20" Width="100%" OnSorted="gvRCM_Sorted">
                                                <Columns>
                                                    <asp:BoundField DataField="Place" HeaderText="<%$ resources: AdminUI, SpendHistory.gvRCM.Place %>"
                                                        SortExpression="Place" />
                                                    <asp:BoundField DataField="Reason" HeaderText="<%$ resources: AdminUI, SpendHistory.gvRCM.Reason %>"
                                                        SortExpression="Reason" />
                                                    <asp:BoundField DataField="Amount" HeaderText="<%$ resources: AdminUI, SpendHistory.gvRCM.Amount %>"
                                                        SortExpression="Amount" />
                                                    <asp:BoundField DataField="Percent" HeaderText="<%$ resources: AdminUI, SpendHistory.gvRCM.Percent %>"
                                                        SortExpression="Percent" DataFormatString="<%$ resources: AdminUI, SpendHistory.PercentFormat %>" />
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
                                            <asp:Chart ID="chrtRCM" runat="server" BackColor="236, 233, 228" Width="1000px" ImageStorageMode="UseHttpHandler"
                                                ImageType="Jpeg" Height="500px">
                                                <Series>
                                                    <asp:Series Name="Series1" ChartType="Pie">
                                                        <SmartLabelStyle IsOverlappedHidden="false" />
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
                            </asp:View>
                        </asp:MultiView>
                    </div>
                </td>
            </tr>
        </table>
    </asp:Panel>
</asp:Content>
