<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<BindGeolocationModel>" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
Bind geolocation
</asp:Content>

<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">
  
  <script type="text/javascript">
    var _data;

    function filldropdowns() {
      $.post("/GM/Account/BindGeolocationChangedCountry", { country: $("#selectCountry").val() }, function(data) {
        $("#selectRegion").empty();
        $("#selectCity").empty();
        _data = data;
        $.each(_data, function(i, option) {
          $('#selectRegion').append($('<option/>').val(option.Region_code).text(option.Region_name_en));
        });
        fillcities();
      });
    }

    function fillcities() {
      $("#selectCity").empty();
      $.each(_data, function(i, option) {
        if (option.Region_code == $("#selectRegion").val()) {
          $.each(option.Cities, function(i2, option2) {
            $('#selectCity').append($('<option/>').val(option2).text(option2));
          });
        }
      });
    }

    $(document).ready(function() {
      $("#selectCountry").change(filldropdowns);
      $("#selectRegion").change(fillcities);
      // pre-load data
      $.post("/GM/Account/BindGeolocationChangedCountry", { country: $("#selectCountry").val() }, function(data) {
        _data = data;
      });
    });

  </script>
  
</asp:Content>


<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">
  
<div id="pagemenu" style="width: 30%; float: right; margin-right: 0px">
  <p><%= Html.ActionLink("Back", "Geolocation", new { Model.Auid })%></p>
</div>
  
<div id="pagecontent" style="width: 70%">

  <h2>Bind geolocation for user (auid = <%= Model.Auid %>)</h2>
  
  <% using (Html.BeginForm()) { %>
    
    <table>
      <tr>
        <td><%= Html.LabelFor(m => m.Country) %></td>
        <td><%= Html.DropDownListFor(m => m.Country, (SelectList)ViewData["CountriesList"], new { id = "selectCountry" })%></td>
      </tr>
      <tr>
        <td><%= Html.LabelFor(m => m.Region) %></td>
        <td><%= Html.DropDownListFor(m => m.Region, (SelectList)(ViewData["RegionsList"] ?? new SelectList(new object[0])), new { id = "selectRegion" })%></td>
      </tr>
      <tr>
        <td><%= Html.LabelFor(m => m.City) %></td>
        <td><%= Html.DropDownListFor(m => m.City, (SelectList)(ViewData["CitiesList"] ?? new SelectList(new object[0])), new { id = "selectCity" })%></td>
      </tr>
    </table>
    
    <p><input type="submit" value="Save"/></p>
    
  <% } %>
  
</div>

</asp:Content>

