<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<IEnumerable<ControlCenter.Areas.GM.Models.BroadcastModel>>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
  Get broadcasts list
</asp:Content>

<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">
  <link rel="stylesheet" href="/Content/pager.css" />
  <script type="text/javascript" src="../../Scripts/jquery.localizeDate.js"></script>
  <script type="text/javascript">
    $(document).ready(function() {
      localizeDate();
    });
  </script>
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <h2>Broadcasts list</h2>
  
  <table>
    <tr>
      <th><%= Html.LabelFor(m => m.FirstOrDefault().Id) %></th>
      <th><%= Html.LabelFor(m => m.FirstOrDefault().Title) %></th>
      <th>Locales</th>
      <th><label class="timeZoneLabel">TimeStart, utc+0</label></th>
      <th><label class="timeZoneLabel">TimeFinish, utc+0</label></th>
      <th><%= Html.LabelFor(m => m.FirstOrDefault().Interval)%></th>
      <th><%= Html.LabelFor(m => m.FirstOrDefault().EnabledNow)%></th>
    </tr>
    <% foreach ( var item in Model ) { %>
    <tr>
      <td><%= Html.Encode(item.Id) %></td>
      <td><%= Html.Encode(item.Title) %></td>
      <td><%= Html.Encode(String.Join(", ", item.Messages.Where(m => !String.IsNullOrEmpty(m.Text)).Select(m => m.Locale).ToArray())) %></td>
      <td class="utcdateText"><%= Html.Encode(item.TimeStart.ToString( "dd'.'MM'.'yyyy HH:mm:ss" ) ) %></td>
      <td class="utcdateText"><%= Html.Encode( item.TimeFinish.ToString( "dd'.'MM'.'yyyy HH:mm:ss" ) )%></td>
      <td><%= Html.Encode(item.Interval) %></td>
      <td><%= Html.Encode(item.EnabledNow) %></td>
      
      <td><%= Html.ActionLink( "start rotation", "StartRotation", new { item.Id } )%></td>
      <td><%= Html.ActionLink("stop rotation", "StopRotation", new { item.Id })%></td>
      <td><%= Html.ActionLink("edit", "EditMessage", new { item.Id })%></td>
      <td><%= Html.ActionLink("delete", "DeleteMessage", new { item.Id }, new { @class = "link-delete" })%>      </td>
    </tr>
    <% } %>
  </table>
  
  <div class="pager">
    <% for (int i = 1; i <= (int)ViewData["totalpages"]; i++) { %>
      <%= Html.ActionLink(i.ToString(), "GetBroadcastList", new { page = i },
                                  i == (int)ViewData["page"] ? new { @class = "selected" } : null)%>
    <% } %>
  </div>
  
  <p>
    <%= Html.ActionLink( "add new", "CreateNew")%>
  </p>
</asp:Content>
