<%@ Page Language="C#" AutoEventWireup="true" MasterPageFile="~/AdminUI/Templates/ZzimaUserProfile.Master" 
    CodeBehind="GmaTool.aspx.cs" Inherits="ZzimaBilling.AdminUI.Forms.UserProfilePages.GmaTool"
    Title="<%$ Resources: AdminUI, UserProfile.Menu.GmaTool %>"
    Culture="en-GB" %>

<asp:Content ID="Content" ContentPlaceHolderID="UserPageHolder" runat="server">
    <link href="../../css/Zzima.css" rel="stylesheet" type="text/css" />
    <link href="../../css/Grid.css" rel="stylesheet" type="text/css" />
    <link href="../../css/GmaTool.css" rel="stylesheet" type="text/css" />
    <asp:Panel ID="Panel1" DefaultButton="btnAccept" runat="server">
    <table class="tableInfo">
    <tr class="titleRowHeight">
        <td colspan="2">
            <div>
                <table>
                    <tr>
                        <td class="underLabel" valign="middle">
                            <asp:Literal ID="Literal1" runat="server" Text="<%$ resources: AdminUI, GmaTool.Title %>"></asp:Literal>
                            <img alt="" src="../../Images/arrow.gif"  class="arrowIcon"/>
                        </td>
                    </tr>
                </table>
            </div>
        </td>
    </tr>

    <tr>
        <td class="dummySpace">&nbsp;</td>
        <td valign="top">
            <table width="100%">
            <tr class="titleRowHeight" >
                <td class="fieldLabel">
                    <asp:Label ID="Label1" runat="server" Width="200px" Text="<%$ resources: AdminUI, GmaTool.WriteOff %>"> </asp:Label>
                </td>
                <td width="1px">&nbsp;</td>
                <td class="radioList">
                    <asp:RadioButtonList ID="rblWriteOff" runat="server"  >
                        <asp:ListItem Selected="True" Text="<%$ resources:AdminUI, GmaTool.WriteOff.Real %> " />
                        <asp:ListItem Text="<%$ resources:AdminUI, GmaTool.WriteOff.Bonus %>" />
                        <asp:ListItem Text="<%$ resources:AdminUI, GmaTool.WriteOff.CBT %>" />
                    </asp:RadioButtonList>
                </td>
                <td valign="top" >
                    <asp:DropDownList ID="ddlPaymentSystem" runat="server" CssClass="editBox" Width="200px">
                        <asp:ListItem Selected="True" ></asp:ListItem>
                    </asp:DropDownList>
                </td>
            </tr>
            
            <tr class="titleRowHeight" >
                <td class="fieldLabel">
                    <asp:Label ID="Label2" runat="server" Text="<%$ resources: AdminUI, GmaTool.Sum %>"> </asp:Label>
                </td>
                <td valign="top">
                    <asp:RequiredFieldValidator ID="rfvPromoCodesAmount" runat="server" 
                        ErrorMessage="*"
                        ToolTip="<%$ resources:AdminUI, GmaTool.Validation.Sum %>"
                        ControlToValidate="tpSum" Display="Dynamic"> </asp:RequiredFieldValidator>                
                    <asp:RegularExpressionValidator ID="revPromoCodesAmount" runat="server" 
                        ErrorMessage="*"
                        ToolTip="<%$ resources:AdminUI, GmaTool.Validation %>"
                        ControlToValidate="tpSum"
                        ValidationExpression="^([1-9]\d*([\.,]\d{1,2})?)|(0[\.,][1-9]\d?)|(0[\.,]0[1-9])$" 
                        Display="Dynamic"></asp:RegularExpressionValidator>                    
                </td>
                <td width="200px">
                    <asp:TextBox runat="server" CssClass="editBox" Width="200px" ID="tpSum" ></asp:TextBox>
                </td>
            </tr>
            <tr class="titleRowHeight" >
                <td class="fieldLabel">
                    <asp:Label ID="Label3" runat="server" Text="<%$ resources: AdminUI, GmaTool.Comment %>"> </asp:Label>
                </td>
                <td valign="top">
                    <asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" 
                        ErrorMessage="*"
                        ToolTip="<%$ resources:AdminUI, GmaTool.Validation.Sum %>"
                        ControlToValidate="tpComment"> </asp:RequiredFieldValidator>                 
                </td>
                <td colspan="2">
                    <asp:TextBox ID="tpComment" TextMode="MultiLine" runat="server" CssClass="smallTextArea"></asp:TextBox>
                </td>
            </tr>
            <tr class="titleRowHeight">
                <td>
                    <asp:Label ID="Label4" runat="server" Text="<%$ resources: AdminUI, GmaTool.Password %>"> </asp:Label>
                </td>
                <td valign="top">
                    <asp:RequiredFieldValidator ID="tpPasswordValidator" runat="server" 
                        ErrorMessage="*"
                        ToolTip="<%$ resources:AdminUI, GmaTool.Validation.Sum %>"
                        ControlToValidate="tpPassword"> </asp:RequiredFieldValidator>                 
                </td>                
                <td >
                    <asp:TextBox runat="server" Width="200px" TextMode="Password" CssClass="editBox" ID="tpPassword" ></asp:TextBox>
                </td>
            </tr>
            </table>

        </td>
    </tr> 
    <tr class="titleRowHeight">
        <td colspan="2" align="right">
            <div class="writeoffImg">
                <asp:LinkButton ID="btnAccept" CssClass="button" runat="server" 
                    Text="<%$ resources:AdminUI, Button.WriteOff %>" onclick="onclick_writeoff"> </asp:LinkButton>
            </div>
        </td>
    </tr>
</table>
</asp:Panel>
</asp:Content>