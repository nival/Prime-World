<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<MonitoringInfoModel>" %>
<%@ Import Namespace="ControlCenter.Areas.Monitoring.Models" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	Index
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

  <h2>Monitoring info</h2>
  <div>
    <table>
      <tr>
        <td> <%= Html.LabelFor(m => m.GameCCU) %></td>
        <td> <%= Html.Encode(Model.GameCCU) %></td>
      </tr>
      <tr>
        <td> <%= Html.LabelFor(m => m.BldCCU) %></td>
        <td> <%= Html.Encode(Model.BldCCU) %></td>
      </tr>
      <tr>
        <td> <%= Html.LabelFor(m => m.DwdCCU) %></td>
        <td> <%= Html.Encode(Model.DwdCCU) %></td>
      </tr>
      <tr>
        <td> <%= Html.LabelFor(m => m.NerCCU) %></td>
        <td> <%= Html.Encode(Model.NerCCU) %></td>
      </tr>
      <tr>
        <td> <%= Html.LabelFor(m => m.OpsCCU) %></td>
        <td> <%= Html.Encode(Model.OpsCCU) %></td>
      </tr>
      <tr>
        <td> <%= Html.LabelFor(m => m.TrnCCU) %></td>
        <td> <%= Html.Encode(Model.TrnCCU) %></td>
      </tr>
      <tr>
        <td> <%= Html.LabelFor(m => m.TutCCU) %></td>
        <td> <%= Html.Encode(Model.TutCCU) %></td>
      </tr>
      <tr>
        <td> <%= Html.LabelFor(m => m.OthCCU) %></td>
        <td> <%= Html.Encode(Model.OthCCU) %></td>
      </tr>
      <tr>
        <td> <%= Html.LabelFor(m => m.MMakingUsers) %></td>
        <td> <%= Html.Encode(Model.MMakingUsers) %></td>
      </tr>
    </table>
  </div>

</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>
