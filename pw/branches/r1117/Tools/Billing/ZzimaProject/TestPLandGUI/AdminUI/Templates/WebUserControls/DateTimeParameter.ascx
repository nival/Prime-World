<%@ Control Language="C#" AutoEventWireup="true" CodeBehind="DateTimeParameter.ascx.cs"
    Inherits="ZzimaBilling.AdminUI.Templates.WebUserControls.DateTimeParameter" %>
<%@ Register Assembly="eWorld.UI" Namespace="eWorld.UI" TagPrefix="ew" %>
<link href="../../css/Templates.css" rel="stylesheet" type="text/css" />
<link href="../../css/calendar/calendar.css" rel="stylesheet" type="text/css" />

<script language="JavaScript" src="../../js/calendar/calendar_eu.js"></script>

<style type="text/css">
    .jsDateTime
    {
        border: 1px solid #373c3f;
        background-color: #faf9f8;
        color: #046294;
        font-family: Verdana;
        font-size: 10pt;
        vertical-align: middle;
        text-align: left;
        height: 20px;
        width: 90px;
    }
</style>
<div>
    <table style="table-layout: fixed;">
        <tr>
            <td style="width: 130px; min-width: 130px">
                <asp:RequiredFieldValidator ID="rfvDatePicker" runat="server" ErrorMessage="*" ToolTip="<%$ resources:AdminUI, Calendar.Validation.Required %>"
                    ControlToValidate="datePicker" Display="Dynamic" Width="1px"></asp:RequiredFieldValidator>
                <asp:CompareValidator ID="cmpvDatePicker" runat="server" ErrorMessage="*" ToolTip="<%$ resources:AdminUI, Calendar.Validation.Compare %>"
                    ControlToValidate="datePicker" Display="Dynamic" Operator="DataTypeCheck" Type="Date"
                    Width="1px">
                </asp:CompareValidator>
                <%--<asp:CustomValidator ID="cstvDatePicker" runat="server" ErrorMessage="*" 
                    ToolTip="<%$ resources:AdminUI, Calendar.Validation.Compare %>" 
                    Display="Dynamic" onservervalidate="cstvDatePicker_ServerValidate">
                </asp:CustomValidator>--%>
                <asp:TextBox ID="datePicker" MaxLength="20" runat="server" CssClass="jsDateTime"></asp:TextBox>

                <script language="javascript" type="text/javascript">
                    var ddlID = '<%=ClientID%>_datePicker';
                    var ddl = document.getElementById(ddlID);
                    if (ddl && ddl.disabled != true) {
                        //ddl.readOnly = true;
                        var A_CALTPL = {
                            'months':
                [
                     '<asp:Literal runat="server" Text="<%$ resources:AdminUI, Calendar.M1 %>"/>',
                     '<asp:Literal runat="server" Text="<%$ resources:AdminUI, Calendar.M2 %>"/>',
                     '<asp:Literal runat="server" Text="<%$ resources:AdminUI, Calendar.M3 %>"/>',
                     '<asp:Literal runat="server" Text="<%$ resources:AdminUI, Calendar.M4 %>"/>',
                     '<asp:Literal runat="server" Text="<%$ resources:AdminUI, Calendar.M5 %>"/>',
                     '<asp:Literal runat="server" Text="<%$ resources:AdminUI, Calendar.M6 %>"/>',
                     '<asp:Literal runat="server" Text="<%$ resources:AdminUI, Calendar.M7 %>"/>',
                     '<asp:Literal runat="server" Text="<%$ resources:AdminUI, Calendar.M8 %>"/>',
                     '<asp:Literal runat="server" Text="<%$ resources:AdminUI, Calendar.M9 %>"/>',
                     '<asp:Literal runat="server" Text="<%$ resources:AdminUI, Calendar.M10 %>"/>',
                     '<asp:Literal runat="server" Text="<%$ resources:AdminUI, Calendar.M11 %>"/>',
                     '<asp:Literal runat="server" Text="<%$ resources:AdminUI, Calendar.M12 %>"/>'
                ],
                            'weekdays':
                [
                     '<asp:Literal runat="server" Text="<%$ resources:AdminUI, Calendar.D1 %>"/>',
                    '<asp:Literal runat="server" Text="<%$ resources:AdminUI, Calendar.D2 %>"/>',
                    '<asp:Literal runat="server" Text="<%$ resources:AdminUI, Calendar.D3 %>"/>',
                    '<asp:Literal runat="server" Text="<%$ resources:AdminUI, Calendar.D4 %>"/>',
                    '<asp:Literal runat="server" Text="<%$ resources:AdminUI, Calendar.D5 %>"/>',
                    '<asp:Literal runat="server" Text="<%$ resources:AdminUI, Calendar.D6 %>"/>',
                    '<asp:Literal runat="server" Text="<%$ resources:AdminUI, Calendar.D7 %>"/>'
                ],
                            'yearscroll': true,
                            'weekstart': 1,
                            'centyear': 70,
                            'imgpath': '../../Images/calendar/'
                        }

                        new tcal({
                            // if referenced by ID then form name is not required
                            'controlname': '<%=ClientID%>_datePicker'
                        }, A_CALTPL);
                    }
                </script>

            </td>
            <td id="idTdTime" runat="server" style="width: 60px">
                <asp:DropDownList ID="ddlTime" runat="server" CssClass="editBoxHours">
                </asp:DropDownList>
            </td>
        </tr>
    </table>
</div>
