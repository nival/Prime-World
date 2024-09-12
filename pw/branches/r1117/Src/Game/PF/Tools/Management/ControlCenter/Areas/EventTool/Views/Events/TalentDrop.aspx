<%@ Page Title="Title" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<TalentDropRarityModel>" %>
<%@ Import Namespace="ControlCenter.Areas.EventTool.Models" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
Talent drop event
</asp:Content>


<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">

  <link href="/Content/jquery-ui-1.8.17.custom.css" rel="stylesheet" type="text/css" />
  
  <style type="text/css">
    table, table td {
      border: none;
    }
  </style>

  <script type="text/javascript" src="/Scripts/jquery-ui-1.8.16.custom.min.js"></script>
  <script type="text/javascript" src="/Scripts/jquery.localizeDate.js"></script>
  <script type="text/javascript" src="/Scripts/jquery-ui-timepicker-addon.js"></script>
  <script type="text/javascript" src="/Scripts/jquery-ui-sliderAccess.js"></script>

  <script type="text/javascript">

    $(document).ready(function () {

      localizeDate();
      $('#StartTime').datetimepicker({ dateFormat: 'dd.mm.yy', timeFormat: 'hh:mm:ss', showSecond: true });
      $('#EndTime').datetimepicker({ dateFormat: 'dd.mm.yy', timeFormat: 'hh:mm:ss', showSecond: true });

      $('#Premium').change(function() {
        var dictName = $(this).is(" :checked") ? "premiumdefault" : "ordinarydefault";
        $("#GoodRarityDefault").text($("#" + dictName + " [name='Good']").val());
        $("#ExcellentRarityDefault").text($("#" + dictName + " [name='Excellent']").val());
        $("#MagnificentRarityDefault").text($("#" + dictName + " [name='Magnificent']").val());
        $("#ExclusiveRarityDefault").text($("#" + dictName + " [name='Exclusive']").val());
      });

    });

  </script>

</asp:Content>


<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">
  
<div id="pagemenu" style="width: 30%; float: right; margin-left: 15px">
    
  <div class = "menublock">
      
    <% if (Model.Id != 0) { %>
      <p><%= Html.ActionLink("Delete", "Delete", new { id = Model.Id }, new { @class = "link-delete" }) %></p>
    <% } %>
    <p><%= Html.ActionLink("Back to list", "Index") %></p>

  </div>

</div>

<div id="pagecontent" style="width: 70%">
  
  <h1>Talent drop event</h1>

  <% if (Model.Id == 0) { %>
    <h4>New</h4>
  <% } else { %>
    <h4>ID = <%= Model.Id %></h4>
    <h4><%= Model.Enabled ? "ENABLED" : "DISABLED" %></h4>
  <% } %>

  <% using (Html.BeginForm()) { %>

    <%= Html.ValidationSummary(true) %>

    <%= Html.HiddenFor(m => m.Id) %>
    <%= Html.HiddenFor(m => m.Enabled) %>
    <%= Html.HiddenFor(m => m.TimeZone) %>

    <div class="editor-label">
      <%= Html.LabelFor(m => m.Description) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(m => m.Description) %>
      <%= Html.ValidationMessageFor(m => m.Description) %>
    </div>

    <div style="margin-top: 10px">
      <div class="timeZoneLabel">Start time, utc+0</div>
      <div class="editor-field"><%= Html.TextBoxFor(m => m.StartTime, new Dictionary<string, object> { { "class", "utcdateVal" }, { "Value", Model.StartTime.ToString("dd'.'MM'.'yyyy HH:mm:ss")} }) %></div>
    </div>
  
    <div style="margin-top: 10px">
      <div class="timeZoneLabel">End time, utc+0</div>
      <div class="editor-field"><%= Html.TextBoxFor(m => m.EndTime, new Dictionary<string, object> { { "class", "utcdateVal" }, { "Value", Model.EndTime.ToString("dd'.'MM'.'yyyy HH:mm:ss") } }) %></div>
    </div>
  
    <br/>
    <h4>Rarities</h4>
    <table>
      <tr>
        <th><%= Html.LabelFor(m => m.Premium) %></th>
        <th><%= Html.EditorFor(m => m.Premium) %></th>
      </tr>
      <tr>
        <td><%= Html.LabelFor(m => m.GoodRarity) %></td>
        <td><%= Html.TextBoxFor(m => m.GoodRarity) %></td>
      </tr>
      <tr>
        <td></td>
        <td><span id="GoodRarityDefault"><%= Model.Premium ? Model.PremiumDefault.Good : Model.OrdinaryDefault.Good %></span> (default)</td>
      </tr>
      <tr>
        <td><%= Html.LabelFor(m => m.ExcellentRarity) %></td>
        <td><%= Html.TextBoxFor(m => m.ExcellentRarity) %></td>
      </tr>
      <tr>
        <td></td>
        <td><span id="ExcellentRarityDefault"><%= Model.Premium ? Model.PremiumDefault.Excellent : Model.OrdinaryDefault.Excellent %></span> (default)</td>
      </tr>
      <tr>
        <td><%= Html.LabelFor(m => m.MagnificentRarity) %></td>
        <td><%= Html.TextBoxFor(m => m.MagnificentRarity) %></td>
      </tr>
      <tr>
        <td></td>
        <td><span id="MagnificentRarityDefault"><%= Model.Premium ? Model.PremiumDefault.Magnificent : Model.OrdinaryDefault.Magnificent %></span> (default)</td>
      </tr>
      <tr>
        <td><%= Html.LabelFor(m => m.ExclusiveRarity) %></td>
        <td><%= Html.TextBoxFor(m => m.ExclusiveRarity) %></td>
      </tr>
      <tr>
        <td></td>
        <td><span id="ExclusiveRarityDefault"><%= Model.Premium ? Model.PremiumDefault.Exclusive : Model.OrdinaryDefault.Exclusive %></span> (default)</td>
      </tr>
    </table>
    
    <br/><br/>
    <input type="submit" value="Save"/>

  <% } %>
  
  <%-- Справочники по дефолтным вероятностям --%>
  <div id="ordinarydefault">
    <input type="hidden" name="Good" value="<%= Model.OrdinaryDefault.Good %>"/>
    <input type="hidden" name="Excellent" value="<%= Model.OrdinaryDefault.Excellent %>"/>
    <input type="hidden" name="Magnificent" value="<%= Model.OrdinaryDefault.Magnificent %>"/>
    <input type="hidden" name="Exclusive" value="<%= Model.OrdinaryDefault.Exclusive %>"/>
  </div>
  <div id="premiumdefault">
    <input type="hidden" name="Good" value="<%= Model.PremiumDefault.Good %>"/>
    <input type="hidden" name="Excellent" value="<%= Model.PremiumDefault.Excellent %>"/>
    <input type="hidden" name="Magnificent" value="<%= Model.PremiumDefault.Magnificent %>"/>
    <input type="hidden" name="Exclusive" value="<%= Model.PremiumDefault.Exclusive %>"/>
  </div>

</div>

</asp:Content>
