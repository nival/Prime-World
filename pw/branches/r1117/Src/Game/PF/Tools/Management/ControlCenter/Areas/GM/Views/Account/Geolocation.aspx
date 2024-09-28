<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<GeolocationInfoModel>" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
  Geolocation
</asp:Content>

<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">
</asp:Content>


<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">
  
<div id="pagemenu" style="width: 30%; float: right; margin-right: 0px">
  
  <%if (((GMToolsPrincipal)User).HasPermission("GM_AccountEdit")) {%>
  <div class = "menublock">
    <h4>Edit operations</h4>
    <p><%= Html.ActionLink("Edit geolocation binding", "BindGeolocation", new { Model.Auid })%></p>
    <% if (!String.IsNullOrEmpty(Model.GMCountry)) { %>
      <p><%= Html.ActionLink("Reset geolocation binding", "ResetGeolocation", new { Model.Auid })%></p>
    <% } %>
  </div>
  <%}%>

  <div><%= Html.ActionLink("Back to account details", "Details", new { Model.Auid })%></div>
</div>
  
<div id="pagecontent" style="width: 70%">
  <h2>Geolocation info for player (auid=<%= Model.Auid %>)</h2>
  
  <div>
    <p><b>Geolocation by ip address</b></p>
    <table>
      <tr>
        <td>Country</td>
        <td><%= Model.CountryName %> (code = "<%= Model.Country %>")</td>
      </tr>
      <tr>
        <td>Region</td>
        <td><%= Model.RegionName %> (code = "<%= Model.Region %>")</td>
      </tr>
      <tr>
        <td>City</td>
        <td><%= Model.City %></td>
      </tr>
    </table>
  </div>

  <div style="margin-top: 30px">

  <% if (!String.IsNullOrEmpty(Model.GMCountry)) { %>
    <p><b>Geolocation binding by GM</b></p>
    <table>
      <tr>
        <td>Country</td>
        <td><%= Model.GMCountryName%> (code = "<%= Model.GMCountry%>")</td>
      </tr>
      <tr>
        <td>Region</td>
        <td><%= Model.GMRegionName%> (code = "<%= Model.GMRegion%>")</td>
      </tr>
      <tr>
        <td>City</td>
        <td><%= Model.GMCity%></td>
      </tr>
    </table>
  <% } else { %>
    <p><b>No geolocation binding</b></p>
  <% } %>
  </div>
  
</div>

</asp:Content>
