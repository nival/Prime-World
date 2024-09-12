<%@ Page Language="C#" AutoEventWireup="true" MasterPageFile="~/AdminUI/Templates/ZzimaMaster.Master" Inherits="Additive_BanAll" Codebehind="BanAll.aspx.cs" %>

<asp:Content ID="Content" ContentPlaceHolderID="BodyPlaceHolder" runat="server">
    <div>
        <table id="TABLE1">
            <tr>
                <td style="width: 300px; vertical-align: top">
                    Имя пользователя
                    <br />
                    <asp:TextBox ID="txtUserName" runat="server" Width="225px"></asp:TextBox>
                    <br />
                    <br />
                    <asp:Button ID="btnGetActiveList" runat="server" Text="Список активных сервисов"
                        OnClick="btnGetActiveList_Click" Height="28px" Width="225px" />
                    <br />
                    <br />
                    <asp:Button ID="btnSubscribe" runat="server" Height="28px" Text="Подписать"
                        Width="225px" OnClick="btnSubscribe_Click" />
                    <br />
                    <br />
                    <asp:Button ID="btnBanAllSvcs" runat="server" Text="Забанить на всех сервисах" Height="28px"
                        Width="225px" OnClick="btnBanAllSvcs_Click" />
                    <br />
                    <br />
                    <asp:Label ID="lblResult" runat="server" Text=""></asp:Label>
                </td>
                <td>
                    <asp:CheckBoxList ID="chkBoxList" RepeatLayout="Table" runat="server"/>
                </td>
            </tr>
        </table>
    </div>
</asp:Content>
