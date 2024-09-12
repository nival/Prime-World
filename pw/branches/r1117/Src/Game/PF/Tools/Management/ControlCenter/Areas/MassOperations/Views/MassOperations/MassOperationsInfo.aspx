<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<IEnumerable<ControlCenter.Areas.MassOperations.Models.MassOperationInfoModel>>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	Mass operations info
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    
  <div id="pagemenu" style="width: 30%; float: right; margin-right: 0px">
    <p><%= Html.ActionLink( "Add new mass operation", "Index" )%></p>
  </div>
  
  <div id="pagecontent" style="width: 70%">
    <h2>Mass operations info</h2>
    <table id="friends">
      <thead>
        <tr>
          <th><%= Html.LabelFor( m => m.FirstOrDefault().StartTime )%></th>
          <th><%= Html.LabelFor( m => m.FirstOrDefault().EndTime )%></th>
          <th><%= Html.LabelFor( m => m.FirstOrDefault().OperationType )%></th>
          <th><%= Html.LabelFor( m => m.FirstOrDefault().Finished )%></th>
        </tr>
      </thead>
      <tbody>
        <% foreach (var item in Model) { %>
        <tr>
          <td><%= Html.Encode( item.StartTime )%></td>
          <td><%= Html.Encode( item.EndTime )%></td>
          <td><%= Html.Encode( item.OperationType )%></td>
          <% if (item.Finished) {%>
            <td><%= Html.Encode( "Finished" )%></td>
            <% if (item.FailedAuids != "") {%>
              <td><%= Html.ActionLink("download failed users", "GetFailedUsers", new { auids = item.FailedAuids, operationType = item.OperationType, date = item.StartTime.ToShortDateString() }) %></td>
            <% } else { %>
                <td><%= Html.Encode( "Success")%></td>
            <% } %>
            <td><%= Html.ActionLink("remove", "DeleteMassOperationInfo", new { operationId = item.OperationId }) %></td>
          <% } %>
          <% else { %>
            <td><%= Html.Encode( "In progress" )%></td>
          <% } %>
                      
        </tr>
        <% } %>
      </tbody>
    </table>
  </div>

</asp:Content>
