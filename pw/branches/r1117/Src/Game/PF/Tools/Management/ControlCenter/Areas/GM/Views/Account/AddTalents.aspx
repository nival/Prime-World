<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<IList<TalentAddModel>>" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
Add talents
</asp:Content>

<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">
  
  <style type="text/css">
    
    td input[type='text'] {
      width: 40px;
    }
    
    td input[type='text']:read-only {
      background-color: #eee;
      color: #ccc;
    }
    
  </style>
  
  <script type="text/javascript">
    $(document).ready(
    function() {

      $('#chkall').click(
        function() {
          $('#talents td :checkbox:visible').attr('checked', this.checked);
          if (this.checked) {
            $('#talents td :text:visible[readonly="readonly"]').val(1);
            $('#talents td :text:visible[readonly="readonly"]').attr('readonly', false);
          } else {
            $('#talents td input:text::visible').val(0);
            $('#talents td input:text::visible').attr('readonly', true);
          }
        });

      $('.chktalent').change(
        function() {
          var txt = $(this).parent().parent().find('input:text');
          txt.attr('readonly', !this.checked);
          txt.val(this.checked ? 1 : 0);
          if (!this.checked)
            $('#chkall').attr('checked', false);
        });

      $('.chkfilter').change(
        function() {
          $('#talents tr.' + this.name + ' input:text').attr('readonly', true);
          $('#talents tr.' + this.name + ' input:text').val(0);
          $('#talents tr.' + this.name + ' input:checkbox').attr('checked', false);
          $('#talents tr.' + this.name).css('display', this.checked ? '' : 'none');
          if (this.checked)
            $('#chkall').attr('checked', false);
        });

      $('#talents tr.Class').css('display', 'none');

    }); 

  </script>
</asp:Content>


<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">

<div id="pagemenu" style="width: 30%; float: right; margin-right: 0px">
  <p><%= Html.ActionLink("Back to library", "Library", new { login = ViewData["login"] })%></p>
</div>
  
<div id="pagecontent" style="width: 70%">
  
  <h2>Add talents to library</h2>
  
  <div style="font-size: 1.2em; color: #000000; margin-bottom: 15px;">
    <%= Html.Encode( String.Format( "Account: {0}", ViewData["login"] ) )%>
  </div>
  
  <% using (Html.BeginForm()) { %>

    <fieldset>
      <legend>Talents filter</legend>
      <p><strong>Rarity</strong></p>
      <% foreach (DAL.Entities.TalentRarity e in Enum.GetValues(typeof(DAL.Entities.TalentRarity))) { %>
        <p>
          <%= Html.CheckBox(e.ToString(), e != DAL.Entities.TalentRarity.Class, new { @class = "chkfilter" })%>
          <%= Html.Encode(e) %>
        </p>
      <% } %>
    </fieldset>

    <table id="talents">
    <tr>
      <th><input type="checkbox" id="chkall"/></th>
      <th><%= Html.LabelFor(m => m.FirstOrDefault().Count) %></th>
      <th><%= Html.LabelFor(m => m.FirstOrDefault().TalentClassId) %></th>
      <th><%= Html.LabelFor(m => m.FirstOrDefault().TalentName) %></th>
      <th><%= Html.LabelFor(m => m.FirstOrDefault().Rarity) %></th>
    </tr>
    <% for (int i = 0; i < Model.Count; i++) { %>
      <tr class="<%= Model[i].Rarity.ToString() %>">
        <td><input type="checkbox" class="chktalent"/></td>
        <td>
          <%= Html.TextBoxFor(m => m[i].Count, new { @readonly = "readonly" })%>
          <%= Html.HiddenFor(m => m[i].TalentClassId)%>
        </td>
        <td><%= Html.DisplayFor(m => m[i].TalentClassId)%></td>
        <td><%= Html.DisplayFor(m => m[i].TalentName)%></td>
        <td><%= Html.DisplayFor(m => m[i].Rarity)%></td>
      </tr>
    <% } %>
  </table>
  
  <p><input type="submit" value="Add selected"/></p>
  <% } %>

</div>

</asp:Content>
