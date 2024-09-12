<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="ReportPage.aspx.cs" Inherits="ZzimaBilling.AdminUI.Forms.ReportPages.ReportPage"
    Culture="en-GB" %>

<%@ Register Assembly="Microsoft.ReportViewer.WebForms, Version=9.0.0.0, Culture=neutral, PublicKeyToken=b03f5f7f11d50a3a"
    Namespace="Microsoft.Reporting.WebForms" TagPrefix="rsweb" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>
        <asp:Literal ID="titleId" runat="server" />
    </title>
    <link href="~/AdminUI/css/Zzima.css" rel="stylesheet" type="text/css" />
</head>
<body>
    <form id="form1" runat="server">
    <rsweb:ReportViewer ID="ZzimaReportViewer" runat="server" ProcessingMode="Remote"
        ShowCredentialPrompts="False" ShowDocumentMapButton="False" ShowFindControls="False"
        ShowParameterPrompts="False" ShowPromptAreaButton="False" ShowZoomControl="False"
        Style="height: 93%;" BackColor="White" Width="1000px">
    </rsweb:ReportViewer>
    </form>
</body>
</html>
