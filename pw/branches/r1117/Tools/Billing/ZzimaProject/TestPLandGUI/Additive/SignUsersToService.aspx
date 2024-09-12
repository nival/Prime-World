<%@ Page Language="C#" AutoEventWireup="true" MasterPageFile="~/AdminUI/Templates/ZzimaMaster.Master" Inherits="Additive_SignUsersToService" Codebehind="SignUsersToService.aspx.cs" %>

<asp:Content ID="Content" ContentPlaceHolderID="BodyPlaceHolder" runat="server">
    <div>
        <table id="table" style="width: 1000px">
            <tr>
                <td style="width: 200px; vertical-align: top">
                    <asp:GridView ID="gvCBTSvcs" Width="170px" runat="server" OnSelectedIndexChanged="gvCBTSvcs_SelectedIndexChanged"
                        DataKeyNames="name" AutoGenerateColumns="False">
                        <SelectedRowStyle BackColor="Silver" />
                        <Columns>
                            <asp:ButtonField ButtonType="Link" DataTextField="name" HeaderText="<%$ Resources: AdminUI, Additive.ColumnName %>" CommandName="Select" />
                            <asp:BoundField HeaderText="<%$ Resources: AdminUI, Additive.ColumnDescription %>" DataField="description" />
                            <asp:BoundField HeaderText="<%$ Resources: AdminUI, Additive.ColumnSvcId %>" DataField="id" />
                        </Columns>
                    </asp:GridView>
                    <br />
                </td>
                <td style="width: 250px; vertical-align: top; margin-left: 20px">
                    <asp:TextBox ID="txtSubscribe" Width="220px" runat="server" Rows="20" TextMode="MultiLine"></asp:TextBox>
                    <br />
                    <asp:Button ID="btnSubcribe" Width="220px" Height="28px" runat="server" Text="<%$ Resources: AdminUI, Additive.SignUsers %>" OnClick="btnSubcribe_Click" />
                    <br />
                    <br />
                    <asp:Button ID="btnDeSubscribeFromTextbox" runat="server" Width="220px" Height="28px" 
                        Text="<%$ Resources: AdminUI, Additive.DeSubscribe %>" 
                        onclick="btnDeSubscribeFromTextbox_Click" />
                    <br />
                    <br />
                    <asp:Button ID="btnDeSubcribe" runat="server" Width="220px" Height="28px"
                        Text="<%$ Resources: AdminUI, Additive.DeSubscribeAll %>" OnClick="btnDeSubcribe_Click" />
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
