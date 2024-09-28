<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<IEnumerable<ServiceInfoModel>>" %>
<%@ Import Namespace="ControlCenter.Areas.Cluster.Models"%>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
	View all services
</asp:Content>

<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">
  <link href="/Content/services-common.css" rel="stylesheet" type="text/css" />
  <link href="/Content/services-index.css" rel="stylesheet" type="text/css" />
  <script src="/Scripts/service-view.js" type="text/javascript" ></script>
</asp:Content>

<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">
  <% bool user_can_run = ((GMToolsPrincipal) User).HasPermission("Cluster_RunCommand"); %>
  <% var groupby = (GroupServicesBy) ViewData["groupby"]; %>

  <div id="group_block" style="width: 50%">
    Group services:

    <% if (groupby == GroupServicesBy.Machine) { %>
      <span class="switch enabled">by machine</span> 
    <% } else { %>
        <%= Html.ActionLink("by machine", "Index", new { groupby = "machine" }, new { @class = "switch" })%>
    <% } %>

    <% if (groupby == GroupServicesBy.Type) { %>
      <span class="switch enabled">by type</span> 
    <% } else { %>
        <%= Html.ActionLink("by type", "Index", new { groupby = "type" }, new { @class = "switch" })%>
    <% } %>
  </div>

  <%
  using (Html.BeginForm("GroupCommand", "Service", new { groupby }, FormMethod.Post, new { id = "mainForm" }))
  {
    IEnumerable<string> groupheaders = groupby == GroupServicesBy.Machine
                                         ? Model.Select(m => m.Machine).Distinct()
                                         : Model.Select(m => m.ServiceType).Distinct();

    foreach (string header in groupheaders)
    {
      %>
      <h2><%= Html.Encode(header) %></h2>
      <table>
        <thead>
          <tr>
            <th class="sid_col">Service ID</th>
            <% if (groupby != GroupServicesBy.Machine) { %> <th class="machine_col">Machine</th> <% } %>
            <% if (groupby != GroupServicesBy.Type) { %> <th class="type_col">Type</th> <% } %>
            <th class="pid_col">PID</th>
            <th class="uptime_col">Uptime</th>
            <th class="status_col">Status</th>
            <%if (user_can_run) { %> <th class="commands_col">Available commands</th> <%} %>
          </tr>
        </thead>
        <tbody>
        <%
          Func<ServiceInfoModel, bool> func;
    
          if (groupby == GroupServicesBy.Machine)
            func = m => m.Machine == header;
          else 
            func = m => m.ServiceType == header;

          foreach (var service in Model.Where(func)) { %>
          <tr>
            <td>
              <%if (user_can_run) { %> <input type="checkbox" name="chkService" value="<%= service.ServiceId.Replace('/', '+') %>" /> <%}%>
              <%= Html.ActionLink(service.ServiceId, "Details", new {id = service.ServiceId.Replace('/', '+')}) %>
            </td>
            <td>
              <% if (groupby != GroupServicesBy.Machine) { %> 
                <%= Html.Encode(service.Machine) %>
              <% } %>
              <% if (groupby != GroupServicesBy.Type) { %> 
                <%= Html.Encode(service.ServiceType) %>
              <% } %>
            </td> 
            <td><%= Html.Encode(service.PID) %></td>
            <td><%= Html.Encode(service.Uptime.ToString()) %></td>
            <td class="status <%=service.Status.ToString().ToLower() %>"><%= service.Status.ToString() %></td>
            
            <%if (user_can_run) { %>
            <td>
              <%
              foreach (object value in Enum.GetValues(typeof(ServiceCommand)))
              {
                var cmd = (ServiceCommand) value;
                if (service.CanRunCommand(cmd)) { %>
                  <%= Html.ActionLink(cmd.ToString(), "Command", new { cmd, serviceId = service.ServiceId, groupby }, new { @class = "actionlink" })%>
                <% } else {%>
                  <span class="actionlink"><%= Html.Encode(cmd.ToString()) %></span>
                <% }
              } %>
            </td>
            <%} %>
          
          </tr>
        <% } %>
        </tbody>
      </table>
      <br />
    <%} %>

    <% if (user_can_run) { %>
    <div>
      <p><strong>Group actions:</strong></p>
      <div>
      <%--<%foreach (object value in Enum.GetValues(typeof(ServiceCommand)))
        {
          var cmd = (ServiceCommand) value; %>
          <button type="submit" class="actionlink" name="cmd" value="<%= Html.Encode(cmd.ToString()) %>">
            <%= Html.Encode(cmd.ToString()) %>
          </button>
      <%}%>--%>
      <button type="submit" class="actionlink" name="cmd" value="Start">
        <%= Html.Encode("Start") %>
      </button>
      </div>
    </div>
    <%} %>
  <%} %>

</asp:Content>



