<%@ Page Title="Title" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<HeroPriceModel>" %>
<%@ Import Namespace="ControlCenter.Areas.EventTool.Models" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
Hero price event
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

      // Заполнение дефолтных цен при выборе героя в выпадающем списке
      block.find("#Hero").change({ id: blockid }, function(event) {
        var silverPriceOfSelectedHero = $("#allheroessilver #S" + $(event.target).val()).val();
        $("#dynamicblock_" + event.data.id + " #Silver").val(silverPriceOfSelectedHero);
        $("#dynamicblock_" + event.data.id + " #SilverOld").text(silverPriceOfSelectedHero);
        var goldPriceOfSelectedHero = $("#allheroesgold #G" + $(event.target).val()).val();
        $("#dynamicblock_" + event.data.id + " #Gold").val(goldPriceOfSelectedHero);
        $("#dynamicblock_" + event.data.id + " #GoldOld").text(goldPriceOfSelectedHero);
      }).change();

      blockid++;
    }


    // Ломать - не строить
    function remove_dynamicblock(id) {
      $("#dynamicblock_" + id).remove();
    }


    function fill_dynamicblock(hero, silver, gold) {
      var id = blockid;
      add_dynamicblock();
      $("#dynamicblock_" + id + " #Hero [value='" + hero + "']").attr("selected", "selected").change();
      $("#dynamicblock_" + id + " #Silver").val(silver);
      $("#dynamicblock_" + id + " #Gold").val(gold);
    }

    $(document).ready(function() {
      
      // Заполнение данными из модели (при редактировании ивента)
      <% foreach (var p in Model.NewPrices) { %>
      fill_dynamicblock('<%= p.Hero %>', <%= p.SilverPrice %>, <%= p.GoldPrice %>);
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
  
  <h1>Hero price event</h1>

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

    <a href="javascript:add_dynamicblock()">Add new hero price</a>
  
    <br/><br/>
    <input type="submit" value="Save"/>

  <% } %>


  <%-- Образец блока, который копируется при нажатии на ссылку добавления --%>
  <div id="dynamicblock_prototype" style="margin-top: 10px; margin-bottom: 15px; display: none">
    
    <a href="javascript:void(0)">remove</a>
    <table>
      <tr>
        <td>Hero</td>
        <td><%= Html.DropDownList("Hero", new SelectList((IEnumerable)ViewData["Heroes"], "Id", "Name")) %></td>
      </tr>
      <tr>
        <td>Silver price</td>
        <td><input type="text" id="Silver" name="SilverPrice" /></td>
      </tr>
      <tr>
        <td></td>
        <td><span id="SilverOld"></span> (old price)</td>
      </tr>
      <tr>
        <td>Gold price</td>
        <td><input type="text" id="Gold" name="GoldPrice" /></td>
      </tr>
      <tr>
        <td></td>
        <td><span id="GoldOld"></span> (old price)</td>
      </tr>
    </table>
    
    <%-- хидден из которого мы соберем все идшники блоков при разборе поста в SkinPriceModelBinder --%>
    <input type="hidden" name="index" value="-1"/> 

  </div>


  <%-- Справочники по ценам, чтобы не делать ненужные ajax запросы --%>
  <div id="allheroessilver">
    <% foreach (var p in Model.DefaultPrices) { %>
      <input type="hidden" id="S<%= p.Hero %>" value="<%= p.SilverPrice %>"/>
    <% } %>
  </div>
  <div id="allheroesgold">
    <% foreach (var p in Model.DefaultPrices) { %>
      <input type="hidden" id="G<%= p.Hero %>" value="<%= p.GoldPrice %>"/>
    <% } %>
  </div>

</div>

</asp:Content>
