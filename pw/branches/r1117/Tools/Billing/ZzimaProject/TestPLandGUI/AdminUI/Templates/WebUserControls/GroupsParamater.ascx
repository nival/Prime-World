<%@ Control Language="C#" AutoEventWireup="true" CodeBehind="GroupsParamater.ascx.cs"
    Inherits="ZzimaBilling.AdminUI.Templates.WebUserControls.GroupsParamater" %>
<link href="../../css/Templates.css" rel="stylesheet" type="text/css" />
<link href="../../css/Grid.css" rel="stylesheet" type="text/css" />
<link href="../../css/Zzima.css" rel="stylesheet" type="text/css" />
<div>
    <table>
        <tr>
            <td>
                <asp:RegularExpressionValidator ID="revSum" runat="server" ErrorMessage="*" ToolTip="<%$ resources:AdminUI, PromoCodes.Validation %>"
                    ControlToValidate="tbSumGroup" Display="Dynamic" ValidationExpression="^([0-9]\d*([\.,]\d{1,2})?)|(0[\.,][1-9]\d?)|(0[\.,]0[1-9])$">
                </asp:RegularExpressionValidator>
                <asp:RequiredFieldValidator ID="rfvSum" runat="server" ErrorMessage="*" ToolTip="<%$ resources:AdminUI, PromoCodes.Validation.Sum %>"
                    ControlToValidate="tbSumGroup" Display="Dynamic">
                </asp:RequiredFieldValidator>
                <asp:CustomValidator ID="cvGroups" runat="server" ErrorMessage="*" ToolTip="<%$ resources:AdminUI, Reports.Validation.GroupCount %>"
                    OnServerValidate="cvGroups_ServerValidate" Display="Dynamic"></asp:CustomValidator>
            </td>
            <td>
                <asp:TextBox ID="tbSumGroup" runat="server" Width="165px"></asp:TextBox>
            </td>
            <td class="buttonTempl">
                <asp:ImageButton ID="btnAdd" runat="server" ImageUrl="~/AdminUI/Images/icon-add.gif"
                    ToolTip="<%$resources: AdminUI, GroupsParamater.Add %>" OnClick="btnAdd_Click" />
            </td>
            <td class="buttonSep">
                &nbsp;
            </td>
            <td class="buttonTempl">
                <asp:ImageButton ID="btnSave" runat="server" ImageUrl="~/AdminUI/Images/icon-save.gif"
                    ToolTip="<%$resources: AdminUI, GroupsParamater.Save %>" OnClick="btnSave_Click" />
            </td>
            <td class="buttonSep">
                &nbsp;
            </td>
            <td class="buttonTempl">
                <asp:ImageButton ID="btnDelete" runat="server" ImageUrl="~/AdminUI/Images/icon-delete.gif"
                    ToolTip="<%$resources: AdminUI, GroupsParamater.Delete %>" OnClick="btnDelete_Click" />
            </td>
        </tr>
        <tr>
            <td colspan="7">
                <asp:ListBox ID="lbxGroups" runat="server" CssClass="listBox" AutoPostBack="true"
                    SelectionMode="Single" Width="100%"></asp:ListBox>
            </td>
        </tr>
    </table>
</div>
