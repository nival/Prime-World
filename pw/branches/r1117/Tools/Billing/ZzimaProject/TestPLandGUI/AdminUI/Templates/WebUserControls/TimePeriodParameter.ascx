<%@ Register Src="DateTimeParameter.ascx" TagName="DateTimeParameter" TagPrefix="uc1" %>
<%@ Control Language="C#" AutoEventWireup="true" CodeBehind="TimePeriodParameter.ascx.cs"
    Inherits="ZzimaBilling.AdminUI.Templates.WebUserControls.TimePeriodParameter" %>

<style type="text/css">
   
    .jsTimePeriod
    {
	    border:1px solid #373c3f;
	    background-color:#faf9f8;
	    color:#046294;
	    font-family:Verdana;
	    font-size:10pt;
	    vertical-align:middle;	
	    text-align:left;	
	    height:20px;
    }
    
</style>

<div>
    <table>
        <tr>
            <td colspan="4">
                <asp:DropDownList ID="ddlPeriodValues" runat="server" Width="100%" 
                    CssClass="jsTimePeriod" 
                    AutoPostBack="true">
                </asp:DropDownList>
            </td>
        </tr>
        <tr id="idDateTimeTR" runat="server">
            <td>
                <asp:CustomValidator ID="cvDate" runat="server" Display="Dynamic" 
                    ErrorMessage="*" onservervalidate="cvDate_ServerValidate"
                     ToolTip="<%$ resources:AdminUI, Reports.Validation.Dates %>"></asp:CustomValidator>
            </td>
            <td>
                <asp:Label ID="Label2" runat="server" Text="<%$ Resources: AdminUI, TimePeriodParameter.From %>"
                    Width="15px">
                </asp:Label>
            </td>
            <td>
                <uc1:DateTimeParameter ID="dtFrom" runat="server" timeSign="false" />
            </td>
            <td>
                <asp:Label ID="Label3" runat="server" Text="<%$ Resources: AdminUI, TimePeriodParameter.To %>"
                    Width="15px">
                </asp:Label>
            </td>
            <td>
                <uc1:DateTimeParameter ID="dtTo" runat="server" timeSign="false" />
            </td>
        </tr>
    </table>
</div>
