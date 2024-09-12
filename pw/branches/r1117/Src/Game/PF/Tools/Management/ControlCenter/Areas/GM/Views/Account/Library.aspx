<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<IEnumerable<TalentInfoModel>>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
  Library
</asp:Content>


<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">
  <script type="text/javascript">
    $(document).ready(
      function() {

        $('.rarityfilter').each(function() {
          $("input.rarityfilter[name='" + this.name + "']").attr("checked", this.checked);
          if (this.checked) {
            $('#chkall').attr('checked', false);
            var select = '#talents tr.rar' + this.name;
            $('.tourfilter:checked').each(function() {
              $(select + '.tour' + this.name).show();
            });
            if ($('.rarityfilter:not(:checked)').length == 0) {
              $('#raritychkall').attr('checked', true);
            }
          } else {
            $('#talents tr.rar' + this.name + ':visible').hide();
            $('#raritychkall').attr('checked', false);
          }
        });
        $('.tourfilter').each(function() {
          $("input.tourfilter[name='" + this.name + "']").attr("checked", this.checked);
          if (this.checked) {
            $('#chkall').attr('checked', false);
            var select = '#talents tr.tour' + this.name;
            $('.rarityfilter:checked').each(function() {
              $(select + '.rar' + this.name).show();
            });
            if ($('.tourfilter:not(:checked)').length == 0) {
              $('#tourchkall').attr('checked', true);
            }
          } else {
            $('#talents tr.tour' + this.name + ':visible').hide();
            $('#tourchkall').attr('checked', false);
          }
        });

        $('#chkall').change(
          function() {
            $('#talents td :checkbox:visible').attr('checked', this.checked);
          });

        $('#raritychkall').change(
          function() {
            $('.rarityfilter').attr('checked', this.checked);
            if (!this.checked) {
              $('#talents tbody tr').hide();
            } else {
              $('.tourfilter:checked').each(function() {
                $('#talents tr.tour' + this.name).show();
              });
            }
          });

        $('#tourchkall').change(
          function() {
            $('.tourfilter').attr('checked', this.checked);
            if (!this.checked) {
              $('#talents tbody tr').hide();
            } else {
              $('.rarityfilter:checked').each(function() {
                $('#talents tr.rar' + this.name).show();
              });
            }
          });

        $('.rarityfilter').change(
          function() {
            $("input.rarityfilter[name='" + this.name + "']").attr("checked", this.checked);
            if (this.checked) {
              $('#chkall').attr('checked', false);
              var select = '#talents tr.rar' + this.name;
              $('.tourfilter:checked').each(function() {
                $(select + '.tour' + this.name).show();
              });
              if ($('.rarityfilter:not(:checked)').length == 0) {
                $('#raritychkall').attr('checked', true);
              }
            } else {
              $('#talents tr.rar' + this.name + ':visible').hide();
              $('#raritychkall').attr('checked', false);
            }
          });

        $('.tourfilter').change(
          function() {
            $("input.tourfilter[name='" + this.name + "']").attr("checked", this.checked);
            if (this.checked) {
              $('#chkall').attr('checked', false);
              var select = '#talents tr.tour' + this.name;
              $('.rarityfilter:checked').each(function() {
                $(select + '.rar' + this.name).show();
              });
              if ($('.tourfilter:not(:checked)').length == 0) {
                $('#tourchkall').attr('checked', true);
              }
            } else {
              $('#talents tr.tour' + this.name + ':visible').hide();
              $('#tourchkall').attr('checked', false);
            }
          });

      });
  </script>
</asp:Content>


<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">

  <div id="pagemenu" style="width: 30%; float: right; margin-right: 0px">
    <p><%= Html.ActionLink("Add talents", "AddTalents", new { login = ViewData["login"] })%></p>
    <p><%= Html.ActionLink("Back to account details", "Details", new { login = ViewData["login"] })%></p>
  </div>
  
  <div id="pagecontent" style="width: 70%">
    <h2>Library</h2>

    <% using ( Html.BeginForm( "Library", "Account", new { login = ViewData["login"] }, FormMethod.Post, new { id = "theform" } ) ) { %>
    <div style="font-size: 1.2em; color: #000000; margin-bottom: 15px;">
      <%= Html.Encode( String.Format( "Account: {0}", ViewData["login"] ) )%>
    </div>
    
    <fieldset>
      <legend>Talents filter</legend>
      <div style="float: left; width: 200px">
        <p><strong>Rarity</strong></p>
        <p><input type="checkbox" id="raritychkall" checked="checked"/>All</p>
        <% foreach (DAL.Entities.TalentRarity e in Enum.GetValues(typeof(DAL.Entities.TalentRarity))) { %>
          <p>
            <%= Html.CheckBox(e.ToString(), true, new { @class = "rarityfilter" })%>
            <%= Html.Encode(e) %>
          </p>
        <% } %>
      </div>
      <div>
        <p><strong>Tour</strong></p>
        <p><input type="checkbox" id="tourchkall" checked="checked"/>All</p>
        <% for (int i = 1; i <= 6; i++ ) { %>
          <p>
            <%= Html.CheckBox(i.ToString(), true, new { @class = "tourfilter" })%>
            <%= Html.Encode(i)%>
          </p>
        <% } %>
      </div>
    </fieldset>
    
    <input type="hidden" name="login" value="<%= ViewData["login"] %>"/>
    <table id="talents">
      <thead>
        <tr>
          <% if (((GMToolsPrincipal) User).HasPermission("GM_AccountEdit")) { %>
            <th><input type="checkbox" id="chkall"/></th>
          <% } %>
          <th><%= Html.LabelFor( m => m.FirstOrDefault().TalentClassId )%></th>
          <th><%= Html.LabelFor( m => m.FirstOrDefault().TalentName )%></th>
          <th><%= Html.LabelFor( m => m.FirstOrDefault().Rarity )%></th>
          <th><%= Html.LabelFor( m => m.FirstOrDefault().Tour )%></th>
          <th><%= Html.LabelFor( m => m.FirstOrDefault().RefineRate )%></th>
          <th><%= Html.LabelFor( m => m.FirstOrDefault().BoundHeroClassName )%></th>
        </tr>
      </thead>
      <tbody>
        <% foreach (var item in Model) { %>
        <tr class="<%= String.Format("rar{0} tour{1}", item.Rarity, item.Tour) %>">
          <% if (((GMToolsPrincipal) User).HasPermission("GM_AccountEdit")) { %>
            <td><input type="checkbox" class="chktalent" name="selected" value="<%= item.TalentInstanceId %>" /></td>
          <% } %>
          <td><%= Html.Encode( item.TalentClassId )%></td>
          <td><%= Html.Encode( item.TalentName )%></td>
          <td><%= Html.Encode( item.Rarity )%></td>
          <td><%= Html.Encode( item.Tour )%></td>
          <td><%= Html.Encode( item.RefineRate )%></td>
          <td><%= Html.Encode( item.BoundHeroClassName )%></td>
          <% if (((GMToolsPrincipal) User).HasPermission("GM_AccountEdit")) { %>
            <td><%= Html.ActionLink("edit", "EditTalent", new { login = ViewData["login"], item.TalentInstanceId }) %></td>
          <% } %>
        </tr>
        <% } %>
      </tbody>
    </table>
    
    <p><input type="submit" value="Delete selected"/></p>
  </div>
  <% } %>
     
</asp:Content>
