<%@ Page Language="C#" AutoEventWireup="true" MasterPageFile="~/AdminUI/Templates/ZzimaMaster.Master" Inherits="Additive_UnbanUser" Codebehind="UnbanUser.aspx.cs" %>

<asp:Content ID="Content" ContentPlaceHolderID="BodyPlaceHolder" runat="server">
    <div>
        Имя "разбаниваемого" пользователя:
        <asp:TextBox ID="txtUserName" runat="server"></asp:TextBox>
        <br />
        Название "разбаниваемого" сервиса :
        <asp:TextBox ID="txtSvcName" runat="server"></asp:TextBox>
        <br />
        <br />
        <asp:Button ID="btnGetReason" runat="server" Text="Посмотреть причину" Height="27px"
            Width="180px" OnClick="btnGetReason_Click" />
        <br />
        <br />
        <asp:Button ID="btnUnban" runat="server" Text="Снять бан" Height="27px" Width="180px"
            OnClick="btnUnban_Click" />
        <br />
        <br />
        <asp:Label ID="lblResult" runat="server"></asp:Label>
    </div>
</asp:Content>
