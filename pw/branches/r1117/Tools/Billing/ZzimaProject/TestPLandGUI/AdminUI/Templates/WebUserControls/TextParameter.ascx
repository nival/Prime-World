<%@ Control Language="C#" AutoEventWireup="true" CodeBehind="TextParameter.ascx.cs" Inherits="ZzimaBilling.UI.TextParameter" %>
<link href="../../css/Templates.css" rel="stylesheet" type="text/css" />
<div>
    <asp:Label ID="lblParameterName" runat="server" Text="Parameter Name" 
        Width="220px" CssClass="titleParameterText"></asp:Label>
    <asp:TextBox ID="tbxParameterValue" runat="server" Width="300px" 
        Font-Names="Wingdings 3" ForeColor="#156E9A"></asp:TextBox> 
</div>