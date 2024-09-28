<%@ Page Title="" Language="C#" MasterPageFile="~/AdminUI/Templates/ZzimaMaster.Master" AutoEventWireup="true" CodeBehind="SignUsersPW.aspx.cs" Inherits="ZzimaBilling.Additive.SignUsersPW" %>


<asp:Content ID="Content1" ContentPlaceHolderID="BodyPlaceHolder" runat="server">
<div>
        <table id="table" style="width: 1000px">
            <tr>
                <td style="width: 200px; vertical-align: top; margin-left: 20px">
                    <asp:Label ID="lblServiceName" runat="server" Text=""></asp:Label>
                    <br />
                    <asp:TextBox ID="txtSubscribe" Width="220px" runat="server" Rows="30" TextMode="MultiLine"></asp:TextBox>
                    <br />
                    <asp:Button ID="btnSubcribe" Width="220px" Height="28px" runat="server" Text="Подписать юзеров" OnClick="btnSubcribe_Click" />
                    <br />
                    <br />
                    <asp:Button ID="btnDeSubscribeFromTextbox" runat="server" Width="220px" Height="28px" 
                        Text="Отписать юзеров" 
                        onclick="btnDeSubscribeFromTextbox_Click" />
                    <br />
                    <br />
                    <asp:Button ID="btnDeSubcribe" runat="server" Width="220px" Height="28px"
                        Text="Отписать всех" OnClick="btnDeSubcribe_Click"
                        OnClientClick="if (!confirm('Все юзеры будут отписаны, продолжить ?')) return false;" />
                </td>
                <td style="width: 250px; vertical-align: top">
                    <asp:Label ID="lblWarn" runat="server"></asp:Label>
                    <asp:GridView ID="gvSubcribed" runat="server" Width="220px" AllowPaging="True" PageSize="3000"
                        OnPageIndexChanging="gvSubcribed_PageIndexChanging">
                    </asp:GridView>
                </td>
            </tr>
        </table>
    </div>
</asp:Content>
