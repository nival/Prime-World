<%@ Page Language="C#" AutoEventWireup="true" MasterPageFile="~/AdminUI/Templates/ZzimaMaster.Master" Inherits="AdminUI_Forms_CreateCbtService" Codebehind="CreateCbtService.aspx.cs" %>

<asp:Content ID="Content" ContentPlaceHolderID="BodyPlaceHolder" runat="server">
    <div>
        <table id="TABLE1">
            <tr>
                <td style="width: 300px">
                    Название сервиса
                    <br />
                    <asp:TextBox ID="txtServName" runat="server"></asp:TextBox>
                    <br />
                    Описание сервиса
                    <br />
                    <asp:TextBox ID="txtServDescr" runat="server"></asp:TextBox>
                    <br />
                    В режиме cbt
                    <br />
                    <asp:CheckBox ID="chkIsCBT" runat="server" />
                    <br />
                    Пароль сервиса
                    <br />
                    <asp:TextBox ID="txtPassword" runat="server" TextMode="Password"></asp:TextBox>
                    <br />
                    Является независимым
                    <br />
                    <asp:CheckBox ID="chkIsIndependent" runat="server" />
                    <br />
                </td>
                <td>
                    <asp:Label ID="lblResult" runat="server"></asp:Label>
                </td>
            </tr>
            <tr>
                <td style="width: 300px">
                    <asp:Button ID="Button1" runat="server" Text="Создать сервис" OnClick="Button1_Click" />
                </td>
            </tr>
        </table>
    </div>
</asp:Content>
