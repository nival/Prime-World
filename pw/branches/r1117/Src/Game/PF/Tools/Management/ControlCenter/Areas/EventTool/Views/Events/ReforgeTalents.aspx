<%@ Page Title="Title" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<ControlCenter.Areas.EventTool.Models.ReforgeTalentsEventModel>" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
Reforge Talents Event 
</asp:Content>

<asp:Content ID="Content1" ContentPlaceHolderID="Links" runat="server">

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


      });



  </script>

</asp:Content>


<asp:Content ID="cLinks" ContentPlaceHolderID="MainContent" runat="server">
 <div id="pagemenu" style="width: 30%; float: right; margin-left: 15px">
    
  <div class = "menublock">
      
    <% if (Model.Id != 0) { %>
      <p><%= Html.ActionLink("Delete", "Delete", new { id = Model.Id }, new { @class = "link-delete" }) %></p>
    <% } %>
    <p><%= Html.ActionLink("Back to list", "Index") %></p>

  </div>

</div>


<div id="pagecontent" style="width: 70%">
  
  <h1>Reforge Talents Event </h1>

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
    
    <h4>Prices</h4>
    <table>
      <%
          var i = 0;
          var j = 0;
          for(int k=0; k< Model.ListReforgeTalentPrices.Count; k++)
          {
              if (i == 0)
              
      %>
                  <tr>
         <%
             
              if (i < 3)
              {
         %>
            
          
        <td>
        
        
        <h3>
            <u><%= Html.LabelFor(m => m.ListReforgeTalentPrices[k].Rarity)%></u>: <%= Model.ListReforgeTalentPrices[k].Rarity%>
        </h3>
        
        <div class="editor-label"><%= Html.LabelFor(m => m.ListReforgeTalentPrices[k].RerollPrice) %></div>
        
        <div class="editor-field">
            <%= Html.TextBoxFor(m =>m.ListReforgeTalentPrices[k].RerollPrice)%>
        </div>        
        <div class="editor-label">
            <%= Model.DefaultListReforgeTalentPrices[k].RerollPrice %> (default)
        </div>
         
         <div class="editor-label"><%= Html.LabelFor(m => m.ListReforgeTalentPrices[k].UpgradePrice) %></div>
        <div class="editor-field">
            <%= Html.TextBoxFor( m=>m.ListReforgeTalentPrices[k].UpgradePrice)%>
        </div>
        <div class="editor-label">
            <%= Model.DefaultListReforgeTalentPrices[k].UpgradePrice%> (default)
        </div>
        
                
        <div class="editor-label"><%= Html.LabelFor(m=>m.ListReforgeTalentPrices[k].TalentsToUpgrade) %></div>
        <div class="editor-field">
                <%= Html.TextBoxFor(m=>m.ListReforgeTalentPrices[k].TalentsToUpgrade)%>
        </div>
        <div class="editor-label">
            <%= Model.DefaultListReforgeTalentPrices[k].TalentsToUpgrade%> (default)
        </div>               

        </td>
      
      
      <% i++;
              }
              if (i>=3)
              {
                  i = 0;
      %>
               </tr>
            <% } 

          }
     %>
    </table>
    
    <br/><br/>
    <input type="submit" value="Save"/>

  <% } %>


</div>
    

</asp:Content>