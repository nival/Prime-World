<%@ Page Title="Title" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<RerollShopGroupProbabilityModel>" %>
<%@ Import Namespace="ControlCenter.Areas.EventTool.Models" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
Reroll shop probability event
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
        var rerollTime = $("#allgroupsrerolls #R" + $(event.target).val()).val();
        $("#dynamicblock_" + event.data.id + " #RerollTime").val(rerollTime);
        $("#dynamicblock_" + event.data.id + " #RerollTimeOld").text(rerollTime);
        var probability = $("#allgroupsprobs #P" + $(event.target).val()).val();
        $("#dynamicblock_" + event.data.id + " #Probability").val(probability);
        $("#dynamicblock_" + event.data.id + " #ProbabilityOld").text(probability);
        var minlvl = $("#allgroupsminlvl #MIL" + $(event.target).val()).val();
        if (minlvl < 0) minlvl = 0;
        if (minlvl > 10) minlvl = 10;
        $("#dynamicblock_" + event.data.id + " #MinUpgradeLevel").val(minlvl);
        $("#dynamicblock_" + event.data.id + " #MinUpgradeLevelOld").text(minlvl);
        var maxlvl = $("#allgroupsmaxlvl #MAL" + $(event.target).val()).val();
        if (maxlvl < minlvl) maxlvl = minlvl;
        if (maxlvl > 10) maxlvl = 10;
        $("#dynamicblock_" + event.data.id + " #MaxUpgradeLevel").val(maxlvl);
        $("#dynamicblock_" + event.data.id + " #MaxUpgradeLevelOld").text(maxlvl);
      }).change();

      blockid++;
    }


    // Ломать - не строить
    function remove_dynamicblock(id) {
      $("#dynamicblock_" + id).remove();
    }


    function fill_dynamicblock(group, reroll, probability, minlvl, maxlvl) {
      var id = blockid;
      add_dynamicblock();
      $("#dynamicblock_" + id + " #Group [value='" + group + "']").attr("selected", "selected").change();
      $("#dynamicblock_" + id + " #RerollTime").val(reroll);
      $("#dynamicblock_" + id + " #Probability").val(probability);
      $("#dynamicblock_" + id + " #MinUpgradeLevel").val(minlvl);
      $("#dynamicblock_" + id + " #MaxUpgradeLevel").val(maxlvl);
    }

    $(document).ready(function() {
      
      // Заполнение данными из модели (при редактировании ивента)
      <% foreach (var p in Model.NewPrices) { %>
      fill_dynamicblock('<%= p.Group %>', <%= p.RerollTime %>, <%= p.Probability %>, <%= p.MinUpgradeLevel%>, <%= p.MaxUpgradeLevel%> );
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
  
  <h1>Reroll group probability event</h1>

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

    <a href="javascript:add_dynamicblock()">Add new group probability</a>
  
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
        <td>Reroll time</td>
        <td><input type="text" id="RerollTime" name="RerollTime" /></td>
      </tr>
      <tr>
        <td></td>
        <td><span id="RerollTimeOld"></span> (old reroll time)</td>
      </tr>
      <tr>
        <td>Probability</td>
        <td><input type="text" id="Probability" name="Probability" /></td>
      </tr>
      <tr>
        <td></td>
        <td><span id="ProbabilityOld"></span> (old probability)</td>
      </tr>
      <tr>
        <td>MinUpgradeLevel</td>
        <td><input type="text" id="MinUpgradeLevel" name="MinUpgradeLevel" /></td>
      </tr>
      <tr>
        <td></td>
        <td><span id="MinUpgradeLevelOld"></span> (old MinUpgradeLevel)</td>
      </tr>
      <tr>
        <td>MaxUpgradeLevel</td>
        <td><input type="text" id="MaxUpgradeLevel" name="MaxUpgradeLevel" /></td>
      </tr>
      <tr>
        <td></td>
        <td><span id="MaxUpgradeLevelOld"></span> (old MaxUpgradeLevel)</td>
      </tr>
    </table>
    
    <%-- хидден из которого мы соберем все идшники блоков при разборе поста в SkinPriceModelBinder --%>
    <input type="hidden" name="index" value="-1"/> 

  </div>


  <%-- Справочники по ценам, чтобы не делать ненужные ajax запросы --%>
  <div id="allgroupsrerolls">
    <% foreach (var p in Model.DefaultPrices) { %>
      <input type="hidden" id="R<%= p.Group %>" value="<%= p.RerollTime %>"/>
    <% } %>
  </div>
  <div id="allgroupsprobs">
    <% foreach (var p in Model.DefaultPrices) { %>
      <input type="hidden" id="P<%= p.Group %>" value="<%= p.Probability %>"/>
    <% } %>
  </div>
  <div id="allgroupsminlvl">
    <% foreach (var p in Model.DefaultPrices) { %>
      <input type="hidden" id="MIL<%= p.Group %>" value="<%= p.MinUpgradeLevel %>"/>
    <% } %>
  </div>
  <div id="allgroupsmaxlvl">
    <% foreach (var p in Model.DefaultPrices) { %>
      <input type="hidden" id="MAL<%= p.Group %>" value="<%= p.MaxUpgradeLevel %>"/>
    <% } %>
  </div>
</div>

</asp:Content>
