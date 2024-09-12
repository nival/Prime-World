<%@ Page Language="C#" MasterPageFile="~/AdminUI/Templates/ZzimaUserProfile.Master" 
    AutoEventWireup="true" CodeBehind="GeneralInfo.aspx.cs" Inherits="ZzimaBilling.Admin.UserProfilePages.GeneralInfo" 
    Title="<%$ Resources: AdminUI, UserProfile.Menu.GeneralInfo %>"
    Culture="en-GB" %>

<asp:Content ID="Content" ContentPlaceHolderID="UserPageHolder" runat="server">
    <link href="../../css/Grid.css" rel="stylesheet" type="text/css" />
    <link href="../../css/Zzima.css" rel="stylesheet" type="text/css" />
    <link href="../../css/GeneralInfo.css" rel="stylesheet" type="text/css" />

    <table class="tableInfo">
    <tr class="titleRowHeight">
        <td colspan="2">
            <div>
                <table>
                    <tr>
                        <td class="underLabel" valign="middle">
                            <asp:Literal ID="Literal1" runat="server" 
                                Text="<%$ resources: AdminUI, GeneralInfo.Title %>"></asp:Literal>
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
            <table>
             <tr  class="titleRowHeight" >
                <td  class="fieldsLabel">
                    <asp:Label runat="server" Text="<%$ resources: AdminUI, GeneralInfo.Username %>"> </asp:Label>
                </td>
                <td>
                    <asp:Label ID="lblUserName"  CssClass="labelCount" runat="server" Text=""> </asp:Label>
                </td>
            </tr>

            <tr  class="titleRowHeight" >
                <td  class="fieldsLabel">
                    <asp:Label ID="Label4" runat="server" Text="userID"> </asp:Label>
                </td>
                <td>
                    <asp:Label ID="lblUserId"  CssClass="labelCount" runat="server" Text=""> </asp:Label>
                </td>
            </tr>
            
            <tr  class="titleRowHeight" >
                <td class="fieldsLabel">
                    <asp:Label ID="Label1" runat="server" Text="<%$ resources: AdminUI, GeneralInfo.Email %>"> </asp:Label>
                </td>
                <td>
                    <asp:Label ID="lblEmail"  CssClass="labelUnderline" runat="server" Text=""> </asp:Label>
                </td>
            </tr>
            
            <tr  class="titleRowHeight" >
                <td class="fieldsLabel">
                    <asp:Label ID="Label2" runat="server" Text="<%$ resources: AdminUI, GeneralInfo.RefferalCode %>"> </asp:Label>
                </td>
                <td>
                    <asp:Label ID="lblReferalLink"   CssClass="labelUnderline" runat="server" Text=""> </asp:Label>
                </td>
            </tr>
            
            <tr  class="titleRowHeight" >
                <td class="fieldsLabel">
                    <asp:Label ID="Label3" runat="server" Text="<%$ resources: AdminUI, GeneralInfo.RegisteredDate %>"> </asp:Label>
                </td>
                <td>
                    <asp:Label ID="lblRegDate"   CssClass="labelCount" runat="server" Text=""> </asp:Label>
                </td>
            </tr>
            
        </table>
        </td>
    </tr>
</table>
</asp:Content>

