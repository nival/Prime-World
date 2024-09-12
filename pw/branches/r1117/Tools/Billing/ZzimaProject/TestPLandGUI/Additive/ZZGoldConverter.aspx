<%@ Page Title="" Language="C#" MasterPageFile="~/AdminUI/Templates/ZzimaMaster.Master"
    AutoEventWireup="true" CodeBehind="ZZGoldConverter.aspx.cs" Inherits="ZzimaBilling.Additive.ZZGoldConverter" %>

<asp:Content ID="Content1" ContentPlaceHolderID="BodyPlaceHolder" runat="server">
    <table>
        <tr>
            <td style="width: 160px; height: 40px">
                <asp:Label ID="Label3" runat="server" Text="fromServiceName: "></asp:Label>
            </td>
            <td>
                <asp:DropDownList ID="ddlFromServiceName" runat="server">
                </asp:DropDownList>
            </td>
        </tr>
        <tr>
            <td style="width: 160px; height: 40px">
                <asp:Label ID="Label1" runat="server" Text="юзер-источник: "></asp:Label>
            </td>
            <td>
                <asp:TextBox ID="txtSrcUsername" runat="server"></asp:TextBox>
                <asp:RequiredFieldValidator ID="RequiredFieldValidator3" runat="server" ErrorMessage="not valid" ControlToValidate="txtSrcUsername"></asp:RequiredFieldValidator>
            </td>
        </tr>
        <tr>
            <td style="width: 160px; height: 40px">
                <asp:Label ID="Label2" runat="server" Text="счет-источник: "></asp:Label>
            </td>
            <td>
                <asp:DropDownList ID="ddlSrcServiceName" runat="server">
                </asp:DropDownList>
            </td>
        </tr>
        <tr>
            <td style="width: 160px; height: 40px">
                <asp:Label ID="Label4" runat="server" Text="юзер-получатель: "></asp:Label>
            </td>
            <td>
                <asp:TextBox ID="txtDestUserName" runat="server"></asp:TextBox>
                <asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" ErrorMessage="not valid" ControlToValidate="txtDestUserName"></asp:RequiredFieldValidator>
            </td>
        </tr>
        <tr>
            <td style="width: 160px; height: 40px">
                <asp:Label ID="Label5" runat="server" Text="счет-получатель: "></asp:Label>
            </td>
            <td>
                <asp:DropDownList ID="ddlDestServiceName" runat="server">
                </asp:DropDownList>
            </td>
        </tr>
        <tr>
            <td style="width: 160px; height: 40px">
                <asp:Label ID="Label6" runat="server" Text="сумма: "></asp:Label>
            </td>
            <td>
                <asp:TextBox ID="txtAmount" runat="server"></asp:TextBox>
                <asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" ErrorMessage="not valid" ControlToValidate="txtAmount"></asp:RequiredFieldValidator>
                <asp:RegularExpressionValidator ID="RegularExpressionValidator1" runat="server" ErrorMessage="not valid"
                ValidationExpression="[0-9]{1,9}" ControlToValidate="txtAmount"></asp:RegularExpressionValidator>
            </td>
        </tr>
        <tr>
            <td style="width: 160px; height: 40px">
                <asp:Label ID="Label7" runat="server" Text="reason: "></asp:Label>
            </td>
            <td>
                <asp:TextBox ID="txtReason" runat="server"></asp:TextBox>
            </td>
        </tr>
    </table>
    <asp:Button ID="btnTransfer" runat="server" Text="Применить" 
        onclick="btnTransfer_Click" />
</asp:Content>
