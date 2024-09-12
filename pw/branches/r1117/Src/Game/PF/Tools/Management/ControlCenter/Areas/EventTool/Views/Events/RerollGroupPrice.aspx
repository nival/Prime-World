<%@ Page Title="Title" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<RerollShopGroupPriceModel>" %>
<%@ Import Namespace="ControlCenter.Areas.EventTool.Models" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
Reroll shop price event
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

    // Нумерация добавленных блоков
    var blockid = 0;

    // Добавление контролов и обработчиков для них
    function add_dynamicblock() {

      // Копирование эталонного блока и проставление имен в формате "fieldname_blockid"
      var block = $("#dynamicblock_prototype").clone();

      block.attr("id", "dynamicblock_" + blockid);
      block.show();
      block.find("input:not([type='hidden']),select").each(function () {
        var n = $(this).attr('name');
        $(this).attr('name', n + '_' + blockid);
      });
      $("#dynamic-content").append(block);

      block.find("a").attr("href", "javascript:remove_dynamicblock(" + blockid + ")");
      block.find("[name='index']").val(blockid);

      // Заполнение дефолтных цен при выборе группы в выпадающем списке
      block.find("#Group").change({ id: blockid }, function(event) {
        var minPrice = $("#allgroupsmin #Min" + $(event.target).val()).val();
        $("#dynamicblock_" + event.data.id + " #MinPrice").val(minPrice);
        $("#dynamicblock_" + event.data.id + " #MinPriceOld").text(minPrice);
        var maxPrice = $("#allgroupsmax #Max" + $(event.target).val()).val();
        $("#dynamicblock_" + event.data.id + " #MaxPrice").val(maxPrice);
        $("#dynamicblock_" + event.data.id + " #MaxPriceOld").text(maxPrice);
      }).change();

      blockid++;
    }


    // Ломать - не строить
    function remove_dynamicblock(id) {
      $("#dynamicblock_" + id).remove();
    }


    function fill_dynamicblock(group, minPrice, maxPrice) {
      var id = blockid;
      add_dynamicblock();
      $("#dynamicblock_" + id + " #Group [value='" + group + "']").attr("selected", "selected").change();
      $("#dynamicblock_" + id + " #MinPrice").val(minPrice);
      $("#dynamicblock_" + id + " #MaxPrice").val(maxPrice);
    }

    $(document).ready(function() {
      
      // Заполнение данными из модели (при редактировании ивента)
      <% foreach (var p in Model.NewPrices) { %>
      fill_dynamicblock('<%= p.Group %>', <%= p.MinPrice %>, <%= p.MaxPrice %>);
      <% } %>

      localizeDate();
      $('#StartTime').datetimepicker({ dateFormat: 'dd.mm.yy', timeFormat: 'hh:mm:ss', showSecond: true });
      $('#EndTime').datetimepicker({ dateFormat: 'dd.mm.yy', timeFormat: 'hh:mm:ss', showSecond: true });

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
  
  <h1>Reroll group price event</h1>

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

    <div id="dynamic-content" style="margin: 20px 0px">
    </div>

    <a href="javascript:add_dynamicblock()">Add new group price</a>
  
    <br/><br/>
    <input type="submit" value="Save"/>

  <% } %>


  <%-- Образец блока, который копируется при нажатии на ссылку добавления --%>
  <div id="dynamicblock_prototype" style="margin-top: 10px; margin-bottom: 15px; display: none">
    
    <a href="javascript:void(0)">remove</a>
    <table>
      <tr>
        <td>Group</td>
        <td><%= Html.DropDownList( "Group", new SelectList( (IEnumerable)ViewData["Groups"], "Id", "Name" ) )%></td>
      </tr>
      <tr>
        <td>Min price</td>
        <td><input type="text" id="MinPrice" name="MinPrice" /></td>
      </tr>
      <tr>
        <td></td>
        <td><span id="MinPriceOld"></span> (old min price)</td>
      </tr>
      <tr>
        <td>Max price</td>
        <td><input type="text" id="MaxPrice" name="MaxPrice" /></td>
      </tr>
      <tr>
        <td></td>
        <td><span id="MaxPriceOld"></span> (old max price)</td>
      </tr>
    </table>
    
    <%-- хидден из которого мы соберем все идшники блоков при разборе поста в SkinPriceModelBinder --%>
    <input type="hidden" name="index" value="-1"/> 

  </div>


  <%-- Справочники по ценам, чтобы не делать ненужные ajax запросы --%>
  <div id="allgroupsmin">
    <% foreach (var p in Model.DefaultPrices) { %>
      <input type="hidden" id="Min<%= p.Group %>" value="<%= p.MinPrice %>"/>
    <% } %>
  </div>
  <div id="allgroupsmax">
    <% foreach (var p in Model.DefaultPrices) { %>
      <input type="hidden" id="Max<%= p.Group %>" value="<%= p.MaxPrice %>"/>
    <% } %>
  </div>

</div>

</asp:Content>
