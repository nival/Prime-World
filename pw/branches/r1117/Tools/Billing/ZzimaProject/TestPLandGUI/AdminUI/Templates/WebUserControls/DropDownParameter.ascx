<%@ Control Language="C#" AutoEventWireup="true" CodeBehind="DropDownParameter.ascx.cs" Inherits="ZzimaBilling.UI.DropDownParameter" %>
<div>
    <asp:Label ID="lblParameterName" runat="server" Text="Parameter Name" 
        Width="200px"></asp:Label>
    <asp:DropDownList ID="ddlValues" runat="server" Width="200px">
    </asp:DropDownList>
</div>