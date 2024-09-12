<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Template.aspx.cs" Inherits="ZzimaBilling.AdminUI.Forms.Template" 
    MasterPageFile="~/AdminUI/Templates/ZzimaDetails.Master" 
    EnableEventValidation="false" ValidateRequest="false"%>
    
<asp:Content ID="Content" ContentPlaceHolderID="DetailsPlaceHolder" runat="server">
    
    <link href="../../css/Zzima.css" rel="stylesheet" type="text/css" />
    <link href="../../css/Template.css" rel="stylesheet" type="text/css" />
    
    <script language="javascript" type="text/javascript">
        function RefreshParent() {
            window.parent.location.href = window.parent.location.href;
        }

        function checkedDefault(checkedVal, textBoxId, validatorId) {
            var objTexBox = document.getElementById(textBoxId);
            objTexBox.Text = "";
            objTexBox.disabled = checkedVal;
            var objValidator = document.getElementById(validatorId);
            ValidatorEnable(objValidator, !checkedVal);
            return false;
        }
        
    </script>
       

    <form id="form1" runat="server" DefaultButton="btnSave" >
    <input id="servicesHidden" name="servicesHidden"  type="hidden" runat="server"/>
    <input id="checkedService" name="checkedService" type="hidden" runat="server" />
    <div >
    
        <asp:Label ID="lblError" runat="server" Text="Label" Visible="false"></asp:Label>
        <table>
                <tr>
                    <td style="width: 119px; height: 26px">
                        <asp:Label ID="lblDetailsTitle" runat="server" 
                            Text="<%$resources: AdminUI, Templates.DetailsTitle %>" 
                            CssClass="underlineLabel"></asp:Label>
                    </td>
                    <td style="width: 100px; height: 26px">
                        <asp:Label ID="lblNameTitle" runat="server" 
                            Text="<%$resources: AdminUI, Templates.NameTitle %>"></asp:Label>
                    </td>
                    <td width="1px">
                        <asp:RequiredFieldValidator ID="rfvName" runat="server" 
                            ErrorMessage="*" ToolTip="<%$resources: AdminUI,  Templates.Validation.Name%>" ControlToValidate="tbxName"
                            Display="Dynamic">
                        </asp:RequiredFieldValidator>
                    </td>
                    <td style="height: 26px">
                        <asp:TextBox ID="tbxName" CssClass="editBox" runat="server" Width="400px"></asp:TextBox>
                    </td>
                    <td>
                        <asp:CheckBox ID="chDefault" runat="server" AutoPostBack="true" oncheckedchanged="chDefault_CheckedChanged" Text="<%$ Resources: AdminUI, Templates.Default %>" />
                    </td>
                </tr>
                <tr>
                    <td></td>
                    <td style="width: 100px; height: 35px">
                        <asp:Label ID="lblMaskTitle" runat="server" 
                            Text="<%$resources: AdminUI, Templates.MaskTitle %>"></asp:Label>
                    </td>
                    <td>
                        <asp:RequiredFieldValidator ID="rfvMask" runat="server" 
                            ErrorMessage="*" ToolTip="<%$resources: AdminUI,  Templates.Validation.Mask%>" ControlToValidate="tbxMask"
                            Display="Dynamic">
                        </asp:RequiredFieldValidator>
                    </td>
                    <td style="height: 35px">
                        <asp:TextBox ID="tbxMask" CssClass="editBox" runat="server" Width="400px"></asp:TextBox>
                    </td>
                </tr
                </table>
                <table cellpadding="0" cellspacing="0">
                    <tr height="118px">
                        <td>
                            <asp:ListBox ID="lbxAllServices" runat="server" 
                            CssClass="listBox" AutoPostBack="false" SelectionMode="Multiple">
                            </asp:ListBox>
                        </td>
                        
                        <td valign="middle" width="20px">
                            <div>
                                <table cellpadding="0" cellspacing="0" class="bodyBackground" width="20px" height="118px">
                                    <tr height="38px" class="buttonsAreaBack"> <td></td></tr>
                                    <tr height="20px"> <td align="center" valign="center" > 
                                        
                                        <asp:ImageButton ID="btnRemove" runat="server" 
                                            ImageUrl="../../Images/icon-L-arrow.gif"
                                            onclick="btnRemove_Click"/>
                                     </td> </tr>
                                     <tr height="2px" class="buttonsSeparator"> <td> </td> </tr>
                                     <tr height="20px"> <td align="center" valign="center" >
                                        <asp:ImageButton ID="btnAdd"  runat="server"
                                            ImageUrl="../../Images/icon-R-arrow.gif" 
                                            onclick="btnAdd_Click"/>
                                     </td> </tr>
                                     <tr height="38px" class="buttonsAreaBack"> <td></td></tr>
                                </table>    

                            </div>
                        </td>
                        
                        <td>
                            <asp:ListBox ID="lbxActualServices" runat="server" 
                                CssClass="listBox"
                                AutoPostBack="true"
                                onselectedindexchanged="lbxActualServices_SelectedIndexChanged"> 
                            </asp:ListBox>
                        </td>
                        <td width="30px">
                            <asp:TextBox ID="tbxParameters" runat="server" TextMode="MultiLine" 
                                CssClass="editBox" Height="116px" Width="460px" ></asp:TextBox>
                        </td>
                    </tr>
                    <tr> <td colspan="5"> &nbsp;</td> </tr>
                    </table>
                    
                    <table width="100%">
                    <tr height="20px" >
                        <td colspan="5" align="right">
                            <div class="saveImg">
                                <asp:LinkButton ID="btnSave" runat="server" 
                                    Text="<%$resources: AdminUI, Templates.SaveButtonTitle %>" 
                                    CssClass="buttonMid" onclick="btnSave_Click" />
                             </div>
                       </td>
                    </tr>
                </table>
        </div>
    </form>
</asp:Content>    
