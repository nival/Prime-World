<%@ Page Language="C#" MasterPageFile="~/AdminUI/Templates/ZzimaMaster.Master" AutoEventWireup="true" CodeBehind="PromoCodes.aspx.cs" Inherits="ZzimaBilling.AdminUI.Forms.PromoCodes" Title="<%$ resources:AdminUI, Title.Promocodes %>" %>

<%@ Register assembly="ZzimaBilling" namespace="ZzimaBilling.Controls" tagprefix="cc1" %>
<%@ Register src="../../Templates/WebUserControls/NumericalControl.ascx" tagname="NumericalControl" tagprefix="uc1" %>
<%@ Register src="../../Templates/WebUserControls/TextParameter.ascx" tagname="TextParameter" tagprefix="uc2" %>

<asp:Content ID="PromoCodes" ContentPlaceHolderID="BodyPlaceHolder" runat="server">
    <link href="../../css/Grid.css" rel="stylesheet" type="text/css" />
    <link href="../../css/PromoCodes.css" rel="stylesheet" type="text/css" />
    <link href="../../css/Zzima.css" rel="stylesheet" type="text/css" />
    
    <asp:Panel ID="Panel1" DefaultButton="btnGenerate" runat="server">
    <div>
        <table style="padding-top:10px;width:100%;" >
            <tr class="titleRowHeight">
                <td valign="middle" width="220px">
                    <table> <tr>
                        <td class="underLabel" valign="middle">
                            <asp:Literal ID="Literal1" runat="server" Text="<%$ resources:AdminUI, Promocodes.InputData %>"></asp:Literal>
                            <img alt="" src="../../Images/arrow.gif" class="arrowIcon"/>
                        </td>
                     </tr></table>
                </td>
                
                <td class="fieldsLabel">
                    <asp:Literal ID="Literal2" runat="server" Text="<%$ resources:AdminUI, Promocodes.PromoCodesAmount %>"></asp:Literal>
                </td>
                <td width="1px">                   
                    <asp:RegularExpressionValidator ID="revPromoCodesAmount" runat="server" 
                        ErrorMessage="*" ToolTip="<%$ resources:AdminUI, PromoCodes.Validation %>"
                        ControlToValidate="tpPromoCodesAmount" Display="Dynamic"
                        ValidationExpression="^[1-9]\d*$">
                    </asp:RegularExpressionValidator>
                    <asp:RequiredFieldValidator ID="rfvPromoCodesAmount" runat="server" 
                        ErrorMessage="*" ToolTip="<%$ resources:AdminUI, PromoCodes.Validation.Amount %>"
                        ControlToValidate="tpPromoCodesAmount" Display="Dynamic" >
                    </asp:RequiredFieldValidator>
                </td>
                <td >
                    <asp:TextBox runat="server" Width="200px" MaxLength="100" CssClass="editBox" ID="tpPromoCodesAmount"></asp:TextBox>
                </td>
            </tr>
            
            <tr class="titleRowHeight" >
                <td>&nbsp </td>
                <td class="fieldsLabel" >
                    <asp:Literal ID="Literal3" runat="server" Text="<%$ resources:AdminUI, Promocodes.Sum %>"></asp:Literal>
                </td>
                <td width="1px">
                    <asp:RegularExpressionValidator ID="revSum" runat="server" 
                        ErrorMessage="*" ToolTip="<%$ resources:AdminUI, PromoCodes.Validation %>"
                        ControlToValidate="tpSum" Display="Dynamic"
                        ValidationExpression="^([1-9]\d*([\.,]\d{1,2})?)|(0[\.,][1-9]\d?)|(0[\.,]0[1-9])$">
                    </asp:RegularExpressionValidator>
                    <asp:RequiredFieldValidator ID="rfvSum" runat="server" 
                        ErrorMessage="*" ToolTip="<%$ resources:AdminUI, PromoCodes.Validation.Sum %>"
                        ControlToValidate="tpSum" Display="Dynamic">
                    </asp:RequiredFieldValidator>
                </td> 
                <td >
                    <asp:TextBox ID="tpSum" Width="200px" MaxLength="100" CssClass="editBox" runat="server" ></asp:TextBox>
                </td>
            </tr>
            
            <tr class="areaRowHeight" >
                <td>&nbsp </td>
                <td class="fieldsLabel" >
                    <asp:Literal ID="Literal4" runat="server" Text="<%$ resources:AdminUI, Promocodes.Comment %>"></asp:Literal>
                </td>
                <td width="1px">
                    <asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" 
                        ErrorMessage="*" ToolTip="<%$ resources:AdminUI, PromoCodes.Validation.Comment %>"
                        ControlToValidate="tpComment" Display="Dynamic"> 
                    </asp:RequiredFieldValidator>
                </td>
                <td >
                    <asp:TextBox ID="tpComment" CssClass="textArea" TextMode="MultiLine" runat="server" ></asp:TextBox>
                </td> 
            </tr>

            <tr class="titleRowHeight" >
                <td colspan="3" class="fieldsLabel" >&nbsp;</td>
                <td align="right" valign="bottom">
                    <div class="generateImg">
                    <asp:LinkButton ID="btnGenerate" CssClass="buttonBig" runat="server" Text="<%$ resources:AdminUI, Button.Generate %>" 
                        onclick="btnGenerate_Click" >
                    </asp:LinkButton>
                    </div>
                </td>
            </tr>
            
            <tr height="4">
                <td colspan="4" class="hSeparator"> </td>
            </tr>
        </table>
    </div>

    <div id="GridViewDiv" width="100%">
    <table width="100%" cellpadding="0" cellspacing="0">
        <tr>
            <td colspan="6">
            <div class="gridAreaPromocodes">
                <!--Pager-->
                <asp:Panel ID="gvPagerRow" runat="server" >
                    <table cellpadding="0" cellspacing="0"  width="100%">
                            <tr>
                                <td align="left">
                                    <div>
                                        <table>
                                            <tr class="titleRowHeight">
                                                <td>
                                                    <table> <tr>
                                                        <td align="left" valign="middle" class="underLabel">
                                                            <asp:Literal ID="Literal5" runat="server" Text="<%$ resources:AdminUI, Promocodes.Result %>"></asp:Literal>
                                                            <img alt="" src="../../Images/arrow.gif" class="arrowIcon"/>
                                                        </td>
                                                    </tr></table>
                                                </td>
                                                <td>&nbsp;</td>
                                                <td> <asp:Label ID="lblTotalCount" runat="server" 
                                                        Text="<%$ resources:AdminUI, PromoCodes.TotalCount %>"></asp:Label> 
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
                           <td align="right" style="padding-left:10px;width:1px">
                                <asp:ImageButton ID="btnExport" runat="server" Enabled="False"
                                    ImageUrl="~/AdminUI/Images/icon-xlsx.gif" 
                                    ToolTip="<%$ resources:AdminUI, Tooltip.Export2Xls %>" 
                                    onclick="btnExport_Click" />
                            </td>
                             </tr>  
                        </table>
                </asp:Panel>
                <!--GridView-->
                <asp:ObjectDataSource ID="prCodesDataSource1" runat="server" 
                    SelectMethod="GetPromoCodesDataTable" 
                    TypeName="ZzimaBilling.AdminUI.Forms.PromoCodes">
                </asp:ObjectDataSource>
                <asp:GridView ID="gvPromoCodes" runat="server" 
                    PageSize="6" 
                    GridLines="Vertical"
                    BorderWidth="1px"
                    CellPadding="3" Width="100%" 
                    AllowSorting="True" 
                    AutoGenerateColumns="False" DataSourceID="prCodesDataSource1" 
                    onrowcreated="gvPromoCodes_RowCreated" onsorting="gvPromoCodes_Sorting" 
                    AllowPaging="True" onsorted="gvPromoCodes_Sorted" 
                    >
                    <Columns>
                        <asp:BoundField DataField="Code" HeaderText="<%$ resources: AdminUI, PromoCodes.GridView.Headers.Code%>" SortExpression="Code" />
                        <asp:BoundField DataField="GeneratedAt" HeaderText="<%$ resources: AdminUI, PromoCodes.GridView.Headers.GeneratedAt%>" SortExpression="GeneratedAt" />
                        <asp:BoundField DataField="Amount" HeaderText="<%$ resources: AdminUI, PromoCodes.GridView.Headers.Amount%>" SortExpression="Amount"/>
                    </Columns>
                    <PagerStyle HorizontalAlign="Right" />  
                    <HeaderStyle CssClass="headerRow" VerticalAlign="Middle" />
                    <PagerSettings Position="Top" Visible="False"/>
                    <RowStyle CssClass="normalRow" />
                    <AlternatingRowStyle CssClass="alternativeRow" />
                </asp:GridView>
            </div>
            </td>
        </tr>
    </table>    
    </div>
    </asp:Panel>
</asp:Content>
