<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Main.aspx.cs" Inherits="ZzimaBilling.AdminUI.Forms.Main" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head>

<script>

function OnUsers()
{
    window.Body.location = "Users.aspx";
}

function OnPromocodes()
{
    window.Body.location = "AdministratorToolsPages/PromoCodes.aspx";
}

function OnReports()
{
    window.Body.location = "ReportsPages/Reports.aspx";
}

function OnTemplates()
{
    window.Body.location = "AdministratorToolsPages/Templates.aspx";
}

function OnProtocol()
{
    window.Body.location = "AdministratorToolsPages/Protocol.aspx";
}

</script>
</head>

<frameset rows="160,*" framespacing="0" frameborder="0" >
	<frame frameborder="0" name="Top" scrolling="no" src="Top.aspx" noresize/>
	<frame frameborder="0" noresize name="Body" scrolling="auto" src="Users.aspx"/>	
</frameset>

</html>
