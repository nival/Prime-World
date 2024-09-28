<%@ Page Title="Title" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<RerollShopGroupCurrenciesModel>" %>
<%@ Import Namespace="ControlCenter.Areas.EventTool.Models" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
Reroll shop currencies event
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
  <script type="text/javascript" src="/Scripts/CommonScripts.js"></script>

  <script type="text/javascript">
    function GetAllValues(label) {
          var resultObject = {};
          resultObject.namesArray = ["All"];
          resultObject.valuesArray = ["All"];
          $("." + label).each(function () {
              var tempValue = $(this).text();
              tempValue.split(", ").forEach(function (element) {
                  if ($.inArray(element, resultObject.valuesArray) === -1 && element !== "") {
                      resultObject.namesArray.push(element);
                      resultObject.valuesArray.push(element);
                  }
              });
              
          });
          return resultObject;
      }
      
    var CurrenciesEnum = eval([<% ="\"" + RerollShopGroupCurrenciesModel.GetAllTexts(Model.CurrenciesEnum) + "\"" %>]);
    var CurrenciesEnumValues = eval([<% ="\"" + RerollShopGroupCurrenciesModel.GetAllValues(Model.CurrenciesEnum) + "\"" %>]);
    var CurrenciesString = CurrenciesEnumValues.join(",");
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
      $(".Currencies").each(function () {
        CommonScripts.AddListBox($(this), CurrenciesEnumValues, CurrenciesEnum, true);
      });

      block.find("#Group").change({ id: blockid }, function(event) {
        var currencies = $("#allgroupscurrencies #C" + $(event.target).val()).val();
        $("#dynamicblock_" + event.data.id + " .Currencies select").val(currencies.split(','));
        $("#dynamicblock_" + event.data.id + " #CurrenciesOld").text(currencies);
        $("#dynamicblock_" + event.data.id + " #Currencies").val(currencies);
      }).change();

      blockid++;
    }


    // Ломать - не строить
    function remove_dynamicblock(id) {
      $("#dynamicblock_" + id).remove();
    }


    function fill_dynamicblock(group, currencies) {
      var id = blockid;
      add_dynamicblock();
      $("#dynamicblock_" + id + " #Group [value='" + group + "']").attr("selected", "selected").change();
      $("#dynamicblock_" + id + " .Currencies select").val(currencies.split(','));
      $("#dynamicblock_" + id + " #CurrenciesOld").text(currencies);
      $("#dynamicblock_" + id + " #Currencies").val(currencies);
    }

    $(document).ready(function() {
      
      // Заполнение данными из модели (при редактировании ивента)
      <% foreach (var p in Model.NewPrices) { %>
      fill_dynamicblock('<%= p.Group %>', '<%= p.Currencies %>');
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
  
  <h1>Reroll shop currencies event</h1>

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

    <a href="javascript:add_dynamicblock()">Add new group currencies</a>
  
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
        <td>Currencies</td>
        <td class="Currencies"><input type="text" id="Currencies" name="Currencies"/></td>
      </tr>
      <tr>
        <td></td>
        <td><span id="CurrenciesOld"></span> (old currencies)</td>
      </tr>
    </table>
    
    <%-- хидден из которого мы соберем все идшники блоков при разборе поста в SkinPriceModelBinder --%>
    <input type="hidden" name="index" value="-1"/> 

  </div>


  <%-- Справочники по ценам, чтобы не делать ненужные ajax запросы --%>
  <div id="allgroupscurrencies">
    <% foreach (var p in Model.DefaultPrices) { %>
      <input type="hidden" id="C<%= p.Group %>" value="<%= p.Currencies %>"/>
    <% } %>
  </div>

</div>

</asp:Content>
