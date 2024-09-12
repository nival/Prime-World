<%@ Page Language="C#" MasterPageFile="~/AdminUI/Templates/ZzimaUserProfile.Master" 
 AutoEventWireup="true" CodeBehind="ActualBalance.aspx.cs" Inherits="ZzimaBilling.Admin.UserProfilePages.ActualBalance" 
 Title="<%$ Resources: AdminUI, UserProfile.Menu.ActualBalance %>"
 Culture="en-GB" %>

<asp:Content ID="Content" ContentPlaceHolderID="UserPageHolder" runat="server">
    <link href="../../css/Grid.css" rel="stylesheet" type="text/css" />
    <link href="../../css/Zzima.css" rel="stylesheet" type="text/css" />
    
<table   class="tableInfo">
    <tr  class="titleRowHeight">
        <td colspan="2">
            <table>
                <tr>
                    <td class="underLabel" valign="middle">
                        <asp:Label ID="lblActualBalance" runat="server" 
                            Text="<%$ Resources: AdminUI, ActualBalance.ActualBalanceTitle %>"></asp:Label>
                        <img alt="" src="../../Images/arrow.gif" class="arrowIcon"/>
                    </td>
                    <td>
                        <asp:DropDownList ID="ddlServices" runat="server" CssClass="editBox" 
                            AutoPostBack="True">
                        </asp:DropDownList>
                    </td>
                </tr>
            </table>
        </td>
    </tr>
    <tr  class="titleRowHeight">
        <td class="dummySpace">
                <table class="dummySpace" style="table-layout:fixed;">
                </table>            
        </td>
        <td style="width:100%;">
            <asp:Label ID="lblTotalBalanceTitle" runat="server"
                Text="<%$ Resources: AdminUI, ActualBalance.TotalTitle %>"></asp:Label>
            <asp:Label ID="lblTotalBalanceValue" runat="server" Text="0"  CssClass="labelCount"></asp:Label>
        </td>
    </tr>
    <!--<tr  class="titleRowHeight">
        <td >&nbsp;</td>
        <td>
            <asp:Label ID="lblMoney" runat="server" CssClass="underlineLabel"
                Text="<%$ Resources: AdminUI, ActualBalance.MoneyTitle %>"></asp:Label>
        </td>
    </tr>-->
    <tr  class="titleRowHeight">
        <td colspan="2">
            <div>
            <!--Pager-->
            <!--<asp:Panel ID="gvPagerRow" runat="server" >
                    <table cellpadding="0" cellspacing="0"  width="100%">
                            <tr>
                                <td align="left">
                                    <div>
                                        <table>
                                        <tr class="filterRowHeight">
                                                <td> <asp:Label ID="lblTotalCount" runat="server" 
                                                        Text="<%$ resources:AdminUI, Users.TotalCount %>"></asp:Label> 
                                                </td>
                                                <td>&nbsp;</td>
                                                <td> <asp:Label ID="lblCount" class="labelCount" runat="server"
                                                        Text="0"></asp:Label>
                                                </td>
                                           </tr>
                                       </table>  
                                    </div>
                                </td>
          
                                <td align="right">
                                <div>
                                    <table> <tr>  
                                        <td align="right" >                
                                            <asp:Literal ID="Literal9" runat="server" Text="<%$ resources: AdminUI, Pager.Page%>" />
                                            <asp:label id="PageNumberLabel" CssClass="labelCount" runat="server"/> 
                                            <asp:Literal ID="Literal10" runat="server" Text="<%$ resources: AdminUI, Pager.Of%>" />
                                            <asp:label id="TotalPagesLabel" CssClass="labelCount" runat="server"/>                
                                        </td>                                    
                                        <td width="20px">&nbsp;</td>
                                        <td> <asp:LinkButton ID="lnkFirstPage" CommandName="Page" 
                                                CommandArgument="First" runat="server"
                                                CssClass="labelCount"
                                                Text="<%$ resources: AdminUI, Pager.First %>"
                                                ToolTip="<%$ resources: AdminUI, Pager.Tip.First %>"></asp:LinkButton>
                                        </td>
                                        <td> <asp:LinkButton ID="lnkPrevPage" CommandName="Page" 
                                            CommandArgument="Prev" runat="server" 
                                            Text="<%$ resources: AdminUI, Pager.Prev %>"
                                            CssClass="labelCount"
                                            ToolTip="<%$ resources: AdminUI, Pager.Tip.Prev %>"></asp:LinkButton>
                                        </td>
                                        <td> <asp:LinkButton ID="lnkNextPage" CommandName="Page" 
                                            CommandArgument="Next" runat="server" 
                                            Text="<%$ resources: AdminUI, Pager.Next %>"
                                            CssClass="labelCount"
                                            ToolTip="<%$ resources: AdminUI, Pager.Tip.Next %>"></asp:LinkButton>
                                        </td>
                                        <td> <asp:LinkButton ID="lnkLastPage" CommandName="Page" 
                                                CommandArgument="Last" runat="server" 
                                                Text="<%$ resources: AdminUI, Pager.Last %>"
                                                CssClass="labelCount"
                                                ToolTip="<%$ resources: AdminUI, Pager.Tip.Last %>"></asp:LinkButton>
                                        </td>
                                    </tr> </table>
                                    </div>
                                    </td>
                            </tr>  
        
                        </table>
                </asp:Panel>-->
            <!--GridView-->
            <asp:GridView ID="gvPaymentSystems" runat="server" 
                    GridLines="Vertical"
                    BorderWidth="1px"
                    CellPadding="3" Width="100%" 
                    AutoGenerateColumns="False" 
                    AllowPaging="False" 
                    DataSourceID="odsPSAccounts"
                    PageSize="6" 
                    AllowSorting="True" 
                    onrowcreated="gvPaymentSystems_RowCreated" 
                    onsorting="gvPaymentSystems_Sorting" 
                    ondatabound="gvPaymentSystems_DataBound">
                <Columns>
                    <asp:BoundField DataField="PaymentSystemName" 
                        HeaderText="<%$ Resources: AdminUI, ActualBalance.GridView.PSTitle %>"
                        DataFormatString="<%$ Resources: AdminUI, ActualBalance.GridView.PSFormatString %>"
                        SortExpression="PaymentSystemName" />
                        
                    <asp:BoundField DataField="Amount" 
                        HeaderText="<%$ Resources: AdminUI, ActualBalance.GridView.AmountTitle %>" 
                        SortExpression="Amount" />
                        
                </Columns>
                <PagerStyle HorizontalAlign="Right" />
                <HeaderStyle CssClass="headerRow" VerticalAlign="Middle" />
                <PagerSettings Position="Top" Visible="False" />
                <RowStyle CssClass="normalRow" />
                <AlternatingRowStyle CssClass="alternativeRow" />
            </asp:GridView>
            </div>
        </td>
    </tr>
    <tr   class="titleRowHeight">
        <td >&nbsp;</td>
        <td >
            <asp:Label ID="lblBonusBalanceTitle" runat="server" CssClass="underlineLabel"
                Text="<%$ Resources: AdminUI, ActualBalance.BonusBalanceTitle %>"></asp:Label>
            <asp:Label ID="lblBonusBalanceValue" runat="server"  CssClass="underlineLabelCount"
                Text="0"></asp:Label>
        </td>
    </tr>
    <tr  class="titleRowHeight">
        <td colspan="2">                
            <asp:ObjectDataSource ID="odsPSAccounts" runat="server" 
                SelectMethod="GetPaymentSystemsTableFiltered"
                TypeName="ZzimaBilling.AdminUI.DAL.UserDAL"
                OldValuesParameterFormatString="original_{0}">
                <SelectParameters>
                    <asp:SessionParameter DefaultValue="-1" Name="userID" SessionField="UserID" 
                        Type="Int32" />
                    <asp:ControlParameter Name="serviceID" controlid="ddlServices" propertyname="SelectedValue" />
                </SelectParameters>
            </asp:ObjectDataSource>
        </td>
    </tr>
</table>
</asp:Content>
