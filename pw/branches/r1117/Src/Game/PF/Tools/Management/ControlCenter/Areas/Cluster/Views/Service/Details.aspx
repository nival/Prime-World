<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<ServiceInfoModel>" %>
<%@ Import Namespace="ControlCenter.Areas.Cluster.Models"%>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
	Details
</asp:Content>

<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">
  <link href="/Content/services-common.css" rel="stylesheet" type="text/css" />
  <link href="/Content/services-details.css" rel="stylesheet" type="text/css" />
</asp:Content>

<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">
  <h2>Service "<%= Html.Encode(Model.ServiceId) %>"</h2>

  <div class="status <%= Model.Status.ToString().ToLower() %>">
    <%= Model.Status %>
  </div>

  <table>
    <thead>
      <tr>
        <th><%= Html.LabelFor(m => m.ServiceType) %></th>
        <th><%= Html.LabelFor(m => m.Machine) %></th>
        <th><%= Html.LabelFor(m => m.PID) %></th>
        <th><%= Html.LabelFor(m => m.Uptime) %></th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td><%= Html.Encode(Model.ServiceType) %></td>
        <td><%= Html.Encode(Model.Machine) %></td>
        <td><%= Html.Encode(Model.PID) %></td>
        <td><%= Html.Encode(Model.Uptime) %></td>
      </tr>
    </tbody>
  </table>
  
  <div style="width: 200px; background-color: #ffff99; padding: 50px; margin: 20px 0px">
    <p>Information about parameters will be here</p>
  </div>

  <% bool user_can_run = ((GMToolsPrincipal) User).HasPermission("Cluster_RunCommand"); %>
  <% if (user_can_run) {%>
    <div id="servicecommands">
    <%
      foreach (object value in Enum.GetValues(typeof(ServiceCommand)))
      {
        var cmd = (ServiceCommand)value;
        if (Model.CanRunCommand(cmd)) { %>
          <%= Html.ActionLink(cmd.ToString(), "Command", new { cmd, serviceId = Model.ServiceId }, new { @class = "actionlink" })%>
        <% }
        else
        { %>
          <span class="actionlink"><%= cmd.ToString() %></span>
        <% }
      } %>
    </div>
  <%} %>
  
  <%= Html.ActionLink("Back to List", "Index") %>
  
</asp:Content>


