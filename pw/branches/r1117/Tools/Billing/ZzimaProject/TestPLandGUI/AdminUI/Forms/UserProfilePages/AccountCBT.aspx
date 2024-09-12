<%@ Page Language="C#" AutoEventWireup="true" MasterPageFile="~/AdminUI/Templates/ZzimaUserProfile.Master" 
    CodeBehind="AccountCBT.aspx.cs" Inherits="ZzimaBilling.AdminUI.Forms.UserProfilePages.AccountCBT" 
    Title="<%$ Resources: AdminUI, UserProfile.Menu.AccountCBT %>"
    Culture="en-GB" %>

<asp:Content ID="Content" ContentPlaceHolderID="UserPageHolder" runat="server">
    <link href="../../css/Grid.css" rel="stylesheet" type="text/css" />
    <link href="../../css/Zzima.css" rel="stylesheet" type="text/css" />
    
    <table   class="tableInfo">
        <tr  class="titleRowHeight">
            <td ColSpan="2">
                <table>
                    <tr>
                        <td class="underLabel" valign="middle"> 
                            <asp:Label ID="lblActualBalance" runat="server" 
                                Text="<%$ Resources: AdminUI, AccountCBT.Title %>"></asp:Label>
                            <img alt="" src="../../Images/arrow.gif" class="arrowIcon"/>
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
                <asp:Label ID="lblCBTAmountTitle" runat="server"
                    Text="<%$ Resources: AdminUI, AccountCBT.Total %>"></asp:Label>
                <asp:Label ID="lblCBTAmountValue" runat="server" Text="123"  CssClass="labelCount"></asp:Label>
            </td>
        </tr>
        <tr  class="titleRowHeight">
            <td >&nbsp;</td>
            <td>
                <asp:Label ID="lblTotal" runat="server" CssClass="underlineLabel"
                    Text="<%$ Resources: AdminUI, AccountCBT.Details %>"></asp:Label>
            </td>
        </tr>
        <tr>
            <td colspan="2">
                <!--Pager-->
                 <asp:Panel ID="gvPagerRow" runat="server" >
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
                </asp:Panel>
                <!--GridView-->
                <asp:GridView ID="gvAccountCBTDetails" runat="server" 
                        GridLines="Horizontal"
                        BorderWidth="1px"
                        CellPadding="3" 
                        Width="100%" 
                        AutoGenerateColumns="False" 
                        AllowPaging="True"
                        AllowSorting="true" 
                        DataSourceID="odsAccountCBT" 
                        PageSize="5" 
                        onrowcreated="gvAccountCBTDetails_RowCreated" 
                        onsorting="gvAccountCBTDetails_Sorting">
                    <Columns>
                        <asp:BoundField DataField="ServiceName" 
                            HeaderText="<%$ Resources: AdminUI, ActualCBT.GridView.Headers.Game %>" 
                            SortExpression="ServiceName" >
                        <ItemStyle Width="70%" />
                        </asp:BoundField>
                        <asp:BoundField DataField="Amount" 
                            HeaderText="<%$ Resources: AdminUI, ActualCBT.GridView.Headers.Money %>" 
                            SortExpression="Amount" />
                    </Columns>
                    <PagerStyle HorizontalAlign="Right" />
                    <HeaderStyle CssClass="headerRow" VerticalAlign="Middle" />
                    <PagerSettings Position="Top" />
                    <RowStyle CssClass="normalRow" />
                    <AlternatingRowStyle CssClass="alternativeRow" />
                    <PagerSettings Position="Top" Visible="False" />
                </asp:GridView>
                <asp:ObjectDataSource ID="odsAccountCBT" runat="server" 
                    SelectMethod="GetAccountDetailsTable" TypeName="ZzimaBilling.AdminUI.DAL.UserDAL">
                    <SelectParameters>
                        <asp:SessionParameter DefaultValue="-1" Name="userID" SessionField="UserID" 
                            Type="Int32" />
                    </SelectParameters>
                </asp:ObjectDataSource>
            </td>
        </tr>
    </table>
</asp:Content>
