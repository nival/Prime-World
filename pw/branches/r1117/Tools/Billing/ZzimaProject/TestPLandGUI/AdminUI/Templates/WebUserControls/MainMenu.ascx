<%@ Control Language="C#" AutoEventWireup="true" CodeBehind="MainMenu.ascx.cs" Inherits="ZzimaBilling.AdminUI.Templates.WebUserControls.MainMenu" %>

<table cellspacing="0" cellpadding="0" >
    <tr>
        <td>
            <asp:LinkButton ID="Users" PostBackUrl="javascript:window.location='~/AdminUI/Forms/Users.aspx'" runat="server" Text="<%$ resources:AdminUI, Menu.Users %>" CssClass="menuBtn" />
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
