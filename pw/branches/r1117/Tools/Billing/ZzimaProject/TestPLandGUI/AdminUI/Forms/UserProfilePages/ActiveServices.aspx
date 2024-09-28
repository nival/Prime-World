<%@ Page Title="" Language="C#" MasterPageFile="~/AdminUI/Templates/ZzimaUserProfile.Master"
    AutoEventWireup="true" CodeBehind="ActiveServices.aspx.cs" Inherits="ZzimaBilling.AdminUI.Forms.UserProfilePages.ActiveServices" %>

<asp:Content ID="Content1" ContentPlaceHolderID="UserPageHolder" runat="server">
    <link href="../../css/Grid.css" rel="stylesheet" type="text/css" />
    <div>
        <br />
        <asp:Label ID="Label1" runat="server" Font-Bold="true" Text="Бан на Zzima.com (сервис sn) :"></asp:Label>
        <br />
        <br />
        <asp:Label ID="lblBefore" runat="server" Text=""></asp:Label>
        <asp:TextBox ID="txtHoursTemp" runat="server"></asp:TextBox>
        <asp:Label ID="lblAfter" runat="server" Text=""></asp:Label>
        <asp:Button ID="btnTempBan" runat="server" Text="" onclick="btnTempBan_Click" />
        <asp:RegularExpressionValidator ID="RegularExpressionValidator1" runat="server" ErrorMessage="not valid"
                ValidationExpression="[0-9]{1,4}" ControlToValidate="txtHoursTemp"></asp:RegularExpressionValidator>
        <br />
        <br />
        <asp:Label ID="label2" runat="server" Text=" Полный бан "></asp:Label>
        <asp:CheckBox ID="chkTotalBan" runat="server" AutoPostBack="True" 
            oncheckedchanged="chkTotalBan_CheckedChanged" />
        <hr/>
        <table id="TABLE1">
            <tr>
                <td style="width: 220px; vertical-align: top">
                    <br />
                    <asp:Button ID="btnSubscribe" runat="server" Height="28px" Text="Применить" Width="190px"
                        OnClick="btnSubscribe_Click" Style="margin-left: 10px" />
                    <br />
                    <br />
                    <asp:Button ID="btnBanAllSvcs" runat="server" Text="Отписать со всех сервисов" Height="28px"
                        Width="190px" OnClick="btnBanAllSvcs_Click" Style="margin-left: 10px" />
                </td>
                <td style="width: 220px; vertical-align: top">
                    <label id="lblCurrentSvcs" text="Aктивные сервисы">
                        Aктивные сервисы</label>
                    <br />
                    <asp:CheckBoxList ID="chkBoxList" RepeatLayout="Table" runat="server" />
                    <br />
                    <asp:Button ID="btnSelectExisting" runat="server" Text="Выбрать подписанные" Height="25px"
                        Width="170px" OnClick="btnSelectExisting_Click" />
                </td>
                <td style="width: 300px; vertical-align: top">
                    <label id="lblOldSvcs" text="">
                        Пользователь подписан
                    </label>
                    <br />
                    <asp:GridView ID="gvSvcsExists" runat="server" ShowHeader="false" AutoGenerateColumns="True">
                        <RowStyle CssClass="normalRow" />
                        <AlternatingRowStyle CssClass="alternativeRow" />
                    </asp:GridView>
                </td>
            </tr>
        </table>
    </div>
</asp:Content>
