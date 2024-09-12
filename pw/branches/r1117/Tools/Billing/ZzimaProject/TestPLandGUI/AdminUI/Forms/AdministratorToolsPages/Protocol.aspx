<%@ Page Language="C#" MasterPageFile="~/AdminUI/Templates/ZzimaMaster.Master"  Title="<%$ resources:AdminUI, Title.Protocol %>" AutoEventWireup="true" CodeBehind="Protocol.aspx.cs" Inherits="ZzimaBilling.AdminUI.Forms.Protocol" %>
    
<asp:Content ID="Protocol" ContentPlaceHolderID="BodyPlaceHolder" runat="server">
<asp:Panel ID="Panel1" DefaultButton="btnApply" runat="server">
<table cellspacing="0" cellpadding="0" width="100%">
    <tr class="radioBlock">
        <td class="leftColumn">
            <table cellspacing="0" cellpadding="0" >
            <tr><td>
                <div class="settLabelback">
                    <asp:Label Text="<%$ resources:AdminUI, Protocol.Services.Label %>" runat="server"></asp:Label>
                </div>
                </td>
            <td></td></tr>
            </table>
        </td>
        
        <td class="leftColumn1">
            <asp:RadioButtonList runat="server" ID="ServicesSett" CssClass="radio">
                <asp:ListItem Text="<%$ resources:AdminUI, Protocol.Services.Radio1 %>" ></asp:ListItem>
                <asp:ListItem Text="<%$ resources:AdminUI, Protocol.Services.Radio2 %>" ></asp:ListItem>
            </asp:RadioButtonList>                    
         </td>    
    </tr>
                
    <tr class="listBlock">
        <td class="rightColumn">
            <asp:Label ID="ServiceLabel" Text="<%$ resources:AdminUI, Protocol.Service.Label %>" runat="server"></asp:Label>
        </td>
        
        <td class="leftColumn" style="padding:0;">
            <div class="checkBoxList" >
                <asp:CheckBoxList ID="ServicesList" runat="server" CssClass="controls">
                </asp:CheckBoxList>
            </div>
        </td>
    </tr>
                
    <tr class="settingAreaSep1" >
        <td class="rightColumn1">
            <asp:Label ID="PeriodLabel" Text="<%$ resources:AdminUI, Protocol.Period.Label %>" runat="server"></asp:Label>
        </td>
        <td>
            <div>
                <asp:TextBox ID="ServicesPeriod" Width="50px" MaxLength="4" CssClass="editBox" runat="server" ></asp:TextBox>
                <asp:Label ID="Label1" Text="<%$ resources:AdminUI, Protocol.Days.Label %>" runat="server"></asp:Label>
                <asp:RequiredFieldValidator ID="rfvServicesPeriod" runat="server" 
                    ErrorMessage="<%$ resources:AdminUI, Protocol.Validation.Period %>"
                    ControlToValidate="ServicesPeriod">
                </asp:RequiredFieldValidator>
                <asp:RegularExpressionValidator ID="revServicesPeriod" runat="server" 
                    ErrorMessage="<%$ resources:AdminUI, Protocol.Validation.PeriodFormat %>"
                    ControlToValidate="ServicesPeriod"
                    ValidationExpression="^[0-9]\d*$">
                </asp:RegularExpressionValidator>
            </div>
        </td>
    </tr>

    <tr class="radioBlock" >    
        <td class="leftColumn1">
            <table>
            <tr><td>
                <div class="settLabelback">
                    <asp:Label ID="PSystemsLabel" Text="<%$ resources:AdminUI, Protocol.PSystems.Label %>" runat="server"></asp:Label>
                </div>
                </td>
            <td></td></tr>
            </table>
        </td>
                    
        <td class="leftColumn1">
            <asp:RadioButtonList runat="server" ID="PSystemSett" CssClass="radio">
                <asp:ListItem Text="<%$ resources:AdminUI, Protocol.PSystems.Radio1 %>" ></asp:ListItem>
                <asp:ListItem Text="<%$ resources:AdminUI, Protocol.PSystems.Radio2 %>" ></asp:ListItem>
            </asp:RadioButtonList>
        </td>                    
    </tr>
                
    <tr class="listBlock" >
        <td class="rightColumn">
            <asp:Label ID="PSystemLabel" Text="<%$ resources:AdminUI, Protocol.PSystem.Label %>" runat="server"></asp:Label>
        </td>
        
        <td class="leftColumn" style="padding:0;">
            <div class="checkBoxList" >
                <asp:CheckBoxList ID="PSystemsList" runat="server" CssClass="controls">
                </asp:CheckBoxList>
            </div>
        </td>
    </tr>
                
    <tr class="settingAreaSep1" >
        <td class="rightColumn1">
            <asp:Label ID="PeriodLabel2" Text="<%$ resources:AdminUI, Protocol.Period.Label %>" runat="server"></asp:Label>
        </td>
        <td>
            <div>
                <asp:TextBox ID="PSystemsPeriod" Width="50px" MaxLength="4" CssClass="editBox" runat="server" ></asp:TextBox>
                <asp:Label ID="Days2" Text="<%$ resources:AdminUI, Protocol.Days.Label %>" runat="server"></asp:Label>
                <asp:RequiredFieldValidator ID="rfvPSystemsPeriod" runat="server" 
                    ErrorMessage="<%$ resources:AdminUI, Protocol.Validation.Period %>"
                    ControlToValidate="PSystemsPeriod">
                </asp:RequiredFieldValidator>
                <asp:RegularExpressionValidator ID="revPSystemsPeriod" runat="server" 
                    ErrorMessage="<%$ resources:AdminUI, Protocol.Validation.PeriodFormat %>"
                    ControlToValidate="PSystemsPeriod"
                    ValidationExpression="^[0-9]\d*$">
                </asp:RegularExpressionValidator>
            </div>
        </td>
    </tr>                

    <tr class="radioBlock">
        <td class="leftColumn1">
            <table>
            <tr><td>
                <div class="settLabelback">
                    <asp:Label ID="RequestsLabel" Text="<%$ resources:AdminUI, Protocol.Requests.Label %>" runat="server"></asp:Label>
                </div>
                </td>
            <td></td></tr>
            </table>
        </td>
                    
        <td class="leftColumn1">
            <asp:RadioButtonList runat="server" ID="RequestsSett" CssClass="radio">
                <asp:ListItem Text="<%$ resources:AdminUI, Protocol.Requests.Radio1 %>" ></asp:ListItem>
                <asp:ListItem Text="<%$ resources:AdminUI, Protocol.Requests.Radio2 %>" ></asp:ListItem>
            </asp:RadioButtonList>
        </td>                    
    </tr>
                
    <tr height="30px">
        <td class="rightColumn1">
            <asp:Label ID="Label2" Text="<%$ resources:AdminUI, Protocol.Period.Label %>" runat="server"></asp:Label>
        </td>
        <td>
            <div>
                <asp:TextBox ID="RequestsPeriod" Width="50px" MaxLength="4" CssClass="editBox" runat="server" ></asp:TextBox>
                <asp:Label ID="Label4" Text="<%$ resources:AdminUI, Protocol.Days.Label %>" runat="server"></asp:Label>
                <asp:RequiredFieldValidator ID="rfvRequestsPeriod" runat="server" 
                    ErrorMessage="<%$ resources:AdminUI, Protocol.Validation.Period %>"
                    ControlToValidate="RequestsPeriod">
                </asp:RequiredFieldValidator>
                <asp:RegularExpressionValidator ID="revRequestsPeriod" runat="server" 
                    ErrorMessage="<%$ resources:AdminUI, Protocol.Validation.PeriodFormat %>"
                    ControlToValidate="RequestsPeriod"
                    ValidationExpression="^[0-9]\d*$">
                </asp:RegularExpressionValidator>
            </div>
        </td>
    </tr>                
    
    <tr><td>&nbsp;</td></tr>
    
    <tr height="20px">
        <td >&nbsp;</td>
        <td align="right" valign="bottom">
        <div class="applyImg">
            <asp:LinkButton ID="btnApply" CssClass="buttonMid" Text="<%$ resources:AdminUI, Button.Apply %>" runat="server">
            </asp:LinkButton>
        </div>
        </td>
    </tr>
    
</table>


</asp:Panel>
</asp:Content>
