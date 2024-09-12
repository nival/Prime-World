<%@ Page Language="C#" MasterPageFile="~/AdminUI/Templates/ZzimaMasterLogin.Master" 
AutoEventWireup="true" CodeBehind="Login.aspx.cs" Inherits="ZzimaBilling.AdminUI.Forms.Login" 
Title="<%$ resources:AdminUI, Title.Login %>" %>

    
<asp:Content ID="LoginPanel" ContentPlaceHolderID="LoginPanelPlace" runat="server">
    <asp:Login ID="lgnPanel" runat="server"
        TitleText="<br/>"
        UserNameLabelText="<%$ resources:AdminUI, Login.User %>" 
        PasswordLabelText="<%$ resources:AdminUI, Login.Password %>"
        RememberMeText="<%$ resources:AdminUI, Login.Save %>"
        LoginButtonText="<%$ resources:AdminUI, Login.Button %>"
        FailureText="<%$ resources:AdminUI, Login.FailureText %>"
        
        Font-Size="10pt"
        Font-Names="Verdana"

        Width="420px"
        Height="150px"
        TitleTextStyle-Height="20px"
    
        LabelStyle-ForeColor="#3b3c37"
        LabelStyle-Height="30px"
        
        TextBoxStyle-BorderStyle="Solid"
        TextBoxStyle-BorderWidth="1px"
        TextBoxStyle-BorderColor="#3b3c37"
        TextBoxStyle-Height="16px"
        TextBoxStyle-Width="200px"
    
        CheckBoxStyle-BorderColor="#3b3c37"
        CheckBoxStyle-ForeColor="#3b3c37"      
        CheckBoxStyle-Height="30px"
        CheckBoxStyle-VerticalAlign="Middle"
        
        LoginButtonType ="Link"
        
        DestinationPageUrl="~/AdminUI/Forms/Users.aspx"
        OnLoggedIn="lgnPanel_LoggedIn"
        >
         
        <LoginButtonStyle CssClass="button">
        </LoginButtonStyle >

    </asp:Login>
</asp:Content>
