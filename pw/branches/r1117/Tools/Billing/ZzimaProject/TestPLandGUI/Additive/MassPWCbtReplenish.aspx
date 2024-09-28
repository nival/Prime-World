<%@ Page Title="" Language="C#" MasterPageFile="~/AdminUI/Templates/ZzimaMaster.Master" AutoEventWireup="true" CodeBehind="MassPWCbtReplenish.aspx.cs" Inherits="ZzimaBilling.Additive.MassPWCbtReplenish" %>
<asp:Content ID="Content1" ContentPlaceHolderID="BodyPlaceHolder" runat="server">
<div>
    <table>
        <tr>
            <td style="width: 300px; vertical-align: top">
                <asp:Label ID="Label4" runat="server" Text="список юзеров, каждый с новой строки"></asp:Label>
                <br />
                <asp:TextBox ID="txtUserList" Width="280px" runat="server" Rows="35" TextMode="MultiLine" />
            </td>
            <td style="width: 320px; vertical-align: top; margin-left: 30px">
                <asp:Label ID="Label5" runat="server" Text="Выбрать режим начисления : "></asp:Label>
                <br />
                <asp:DropDownList ID="ddlReplenishRegime" runat="server">
                    <asp:ListItem Selected="True" Value="align" Text="привести баланс к значению" />
                    <asp:ListItem Value="simple" Text="увеличить на значение" />
                </asp:DropDownList>
                <br />
                <br />
                <br />
                <asp:Label ID="Label1" runat="server" Text="От сервиса: "></asp:Label>
                <asp:DropDownList ID="ddlFromServiceName" runat="server" />
                <br />
                <br />
                <asp:Label ID="lblAmount" runat="server" Text="Значение: "></asp:Label>
                <asp:TextBox ID="txtAmount" runat="server"></asp:TextBox>
                <asp:RangeValidator ID="RangeValidator1" runat="server" Display="dynamic" ControlToValidate="txtAmount"
                    Type="Integer" ErrorMessage="not valid" MinimumValue="1" MaximumValue="2147483647"
                    EnableClientScript="True">
                </asp:RangeValidator>
                <asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" ControlToValidate="txtAmount"
                    EnableClientScript="True" ErrorMessage="not valid" Display="dynamic">
                </asp:RequiredFieldValidator>
                <br />
                <br />
                <asp:Label ID="Label2" runat="server" Text="Платежная система: "></asp:Label>
                <asp:DropDownList ID="ddlPaymentSystem" runat="server">
                    <asp:ListItem Selected="True" Value="CBT" />
                </asp:DropDownList>
                <br />
                <br />
                <asp:Label ID="Label3" runat="server" Text="поле Reason: "></asp:Label>
                <asp:TextBox ID="txtReason" runat="server"></asp:TextBox>
                <asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" ControlToValidate="txtReason"
                    ErrorMessage="not valid" EnableClientScript="True" Display="dynamic">
                </asp:RequiredFieldValidator>
                <br />
                <br />
                <asp:Button ID="btnReplenish" runat="server" Text="Пополнить" OnClick="btnReplenish_Click"
                    OnClientClick="if (!confirm('Данные корректны ?')) return false;" />
            </td>
            <td style="vertical-align: top">
                <asp:Label ID="lblWarn" runat="server" Text=""></asp:Label>
                <asp:GridView ID="gvResult" runat="server">
                </asp:GridView>
            </td>
        </tr>
    </table>
    </div>
</asp:Content>
