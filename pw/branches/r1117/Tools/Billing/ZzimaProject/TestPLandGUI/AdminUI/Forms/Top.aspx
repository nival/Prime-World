<%@ Page Language="C#" MasterPageFile="~/AdminUI/Templates/ZzimaMaster.Master" AutoEventWireup="true" CodeBehind="Top.aspx.cs" Inherits="ZzimaBilling.AdminUI.Forms.Top" %>

<asp:Content ID="MenuPanel" ContentPlaceHolderID="MenuPlaceHolder" runat="server">

<table cellspacing="0" cellpadding="0" >
    <tr>
        <td>
            <asp:LinkButton ID="Users" PostBackUrl="javascript:window.parent.OnUsers()" runat="server" Text="<%$ resources:AdminUI, Menu.Users %>" CssClass="menuBtn" />
        </td>
        <td class="menuSeparator"></td>
        <td>
            <asp:LinkButton ID="Promocodes" PostBackUrl="javascript:window.parent.OnPromocodes()" runat="server" Text="<%$ resources:AdminUI, Menu.Promocodes %>" CssClass="menuBtn"/>
        </td>
        <td class="menuSeparator"></td>
        <td>
            <asp:LinkButton ID="Reports" PostBackUrl="javascript:window.parent.OnReports()" runat="server" Text="<%$ resources:AdminUI, Menu.Reports %>" CssClass="menuBtn"/>
        </td>
        <td class="menuSeparator"></td>
        <td>
            <asp:LinkButton ID="Templates" PostBackUrl="javascript:window.parent.OnTemplates()"  runat="server" Text="<%$ resources:AdminUI, Menu.Templates %>" CssClass="menuBtn"/>
        </td>
        <td class="menuSeparator"></td>
        <td>
            <asp:LinkButton ID="Protocol" PostBackUrl="javascript:window.parent.OnProtocol()" runat="server" Text="<%$ resources:AdminUI, Menu.Protocol %>" CssClass="menuBtn"/>
        </td>                       
        <td class="menuSeparator"></td>            
    </tr>
</table>

</asp:Content>
