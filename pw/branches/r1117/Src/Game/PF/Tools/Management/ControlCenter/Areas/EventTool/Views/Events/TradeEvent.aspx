﻿<%@ Page Title="Trade Event" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<TradeEventModel>" %>
<%@ Import namespace="ControlCenter.Areas.EventTool.Models" %>

<asp:Content ID="cTitle" ContentPlaceHolderID="TitleContent" runat="server">
Trade Events
</asp:Content>

<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">
    <link rel="stylesheet" href="/Content/pager.css" />
    <link href="../../../../Content/jquery-ui-1.8.17.custom.css" rel="stylesheet" type="text/css" />
    <style type="text/css">
    /* css for timepicker */
        .ui-timepicker-div .ui-widget-header { margin-bottom: 8px; }
        .ui-timepicker-div dl { text-align: left; }
        .ui-timepicker-div dl dt { height: 25px; margin-bottom: -25px; }
        .ui-timepicker-div dl dd { margin: 0 10px 10px 65px; }
        .ui-timepicker-div td { font-size: 90%; }
        .ui-tpicker-grid-label { background: none; border: none; margin: 0; padding: 0; }
    </style>
  
    <style type="text/css">
        .filter { border: 0; }
        .filter td { border: 0; }
        .saveButton { font-size: 150%; font-weight: bold; }
    </style>
  
    <script type="text/javascript" src="../../../../Scripts/jquery-ui-1.8.16.custom.min.js"></script>
    <script type="text/javascript" src="../../../../Scripts/jquery-ui-timepicker-addon.js"></script>
    <script type="text/javascript" src="../../../../Scripts/jquery-ui-sliderAccess.js"></script>

    <script type="text/javascript">
        $(document).ready(function () {
            $('#StartTime').datetimepicker({ dateFormat: 'dd.mm.yy', timeFormat: 'hh:mm:ss', showSecond: true });
            $('#EndTime').datetimepicker({ dateFormat: 'dd.mm.yy', timeFormat: 'hh:mm:ss', showSecond: true });
        });
    </script>
</asp:Content>

<asp:Content ID="cMain" ContentPlaceHolderID="MainContent" runat="server">

<div id="pagemenu" style="width: 30%; float: right; margin-left: 15px">
  <div class = "menublock">
    <% if (!Model.New) { %>
      <p><%= Html.ActionLink("Delete", "Delete", new { id = Model.EventId }, new { @class = "link-delete" }) %></p>
    <% } %>
    <p><%= Html.ActionLink("Back to list", "Index") %></p>
  </div>
</div> 

<div id="pagecontent" style="width: 70%">
  <h1><% if (Model.EventId == 0) { %>Create new trade event<% } else { %>Edit trade event<% } %></h1>
  <fieldset>
    <legend><%= Html.LabelFor(m => m.EventId) %>: <%= Model.New ? "New" : Model.EventId.ToString() %></legend>
    <%= Html.ValidationSummary(true) %>
    <% using (Html.BeginForm()) { %>

      <%= Html.HiddenFor(m => m.EventId) %>
      <%--<button name="command" type="submit" value="pass">Reload model (debug)</button>--%>

      <%--Description--%>
      <div class="editor-label"><strong><%= Html.LabelFor(m => m.Description) %>*:</strong></div>
      <div class="editor-field">
        <%= Html.EditorFor(m => m.Description) %>
        <%= Html.ValidationMessageFor(m => m.Description) %>
      </div>

      <%--Enabled--%>
      <div class="editor-label"><strong><%= Html.LabelFor(model => model.Enabled) %>*:</strong></div>
      <div class="editor-field">
        <%= Html.CheckBoxFor(model => model.Enabled) %>
      </div>
      
      <%--TradeEventGUID--%>
      <div class="editor-label"><strong><%= Html.LabelFor(model => model.TradeEventGUID) %>*:</strong></div>
      <div class="editor-field">
          <%= Html.EditorFor(model => model.TradeEventGUID)%>
          <%= Html.ValidationMessageFor(m => m.TradeEventGUID)%>
      </div>

      <%-- Locale --%>
      <div class="editor-label"><strong><%= Html.LabelFor(model => model.Locale) %>*:</strong></div>
      <div class="editor-field">
        <%= Html.DropDownListFor(model => model.Locale, Model.AvailableLocales) %>
      </div>

      <%--StartTime--%>
      <div class="editor-label"><strong><%= Html.LabelFor(m => m.StartTime) %> UTC*:</strong></div>
      <div class="editor-field">
        <%= Html.EditorFor(m => m.StartTime) %>
        <%= Html.ValidationMessageFor(m => m.StartTime) %>
      </div>

      <%--EndTime--%>
      <div class="editor-label"><strong><%= Html.LabelFor(m => m.EndTime) %> UTC*:</strong></div>
      <div class="editor-field">
        <%= Html.EditorFor(m => m.EndTime) %>
        <%= Html.ValidationMessageFor(m => m.EndTime) %>
      </div>
          
          
          <%--CompletionTalentId--%>
          <div class="editor-label"><strong><%= Html.LabelFor(model => model.CompletionTalentId)%>:</strong></div>
          <div class="editor-field">
              <%= Html.TextBoxFor(model => model.CompletionTalentId)%>
              <%= Html.ValidationMessageFor(model => model.CompletionTalentId)%>
          </div>
          
          <%--CompletionTalentRatio--%>
          <div class="editor-label"><strong><%= Html.LabelFor(model => model.CompletionTalentRatio)%>:</strong></div>
          <div class="editor-field">
              <%= Html.TextBoxFor(model => model.CompletionTalentRatio)%>
              <%= Html.ValidationMessageFor(model => model.CompletionTalentRatio)%>
          </div>
          
          
      <%--ExperienceCurrnecyId--%>
      <div class="editor-label"><strong><%= Html.LabelFor(model => model.ExperienceCurrencyName)%>:</strong></div>
      <div class="editor-field">
          <%= Html.TextBoxFor(model => model.ExperienceCurrencyName)%>
          <%= Html.ValidationMessageFor(model => model.ExperienceCurrencyName)%>
      </div>
      
      <%--Title--%>
      <div class="editor-label"><strong><%= Html.LabelFor(model => model.Title)%>:</strong></div>
      <div class="editor-field">
          <%= Html.TextBoxFor(model => model.Title)%>
          <%= Html.ValidationMessageFor(model => model.Title)%>
      </div>
      
         
      <%--Text--%>
      <div class="editor-label"><strong><%= Html.LabelFor(model => model.Text)%>:</strong></div>
      <div class="editor-field">
          <%= Html.TextBoxFor(model => model.Text)%>
          <%= Html.ValidationMessageFor(model => model.Text)%>
      </div>
      
      <%--RewardsBlockTitle--%>
      <div class="editor-label"><strong><%= Html.LabelFor(model => model.RewardsBlockTitle)%>:</strong></div>
      <div class="editor-field">
          <%= Html.TextBoxFor(model => model.RewardsBlockTitle)%>
          <%= Html.ValidationMessageFor(model => model.RewardsBlockTitle)%>
      </div>

      <%--BannerUrl--%>
      <div class="editor-label"><strong><%= Html.LabelFor(model => model.BannerUrl)%>:</strong></div>
      <div class="editor-field">
          <%= Html.TextBoxFor(model => model.BannerUrl)%>
          <%= Html.ValidationMessageFor(model => model.BannerUrl)%>
      </div>


          <%--Groups--%>
          <div class="editor-label">
              <strong><%= Html.LabelFor(m => m.TradeEventGroups)%>*:</strong>
              <button name="command" type="submit" value="<%= TradeEventModel.GroupNameCommand %>_add:0" style="color: darkgreen">ADD</button>
          </div>
          
          <div style="margin-left: 20px">
          <% if (Model.TradeEventGroups.Count != 0)
             { %>
              
              <% for (int i = 0; i < Model.TradeEventGroups.Count; i++)
                 { %> 
                  <fieldset style="border: solid darkred 2px;">
                      <legend>
                          <span>Group #<%=i+1 %></span>
                          <button name="command" type="submit" value="<%= TradeEventModel.GroupNameCommand %>_up:<%=i %>"<%= (i == 0) ? " disabled=\"disabled\"" : "" %>>&uarr;</button>
                          <button name="command" type="submit" value="<%= TradeEventModel.GroupNameCommand %>_down:<%=i %>"<%= (i == Model.TradeEventGroups.Count - 1) ? " disabled=\"disabled\"" : "" %>>&darr;</button>
                          <button name="command" type="submit" value="<%= TradeEventModel.GroupNameCommand %>_clone:<%=i %>" style="color: darkgreen">COPY</button>
                          <button name="command" type="submit" value="<%= TradeEventModel.GroupNameCommand %>_remove:<%=i %>" style="color: darkred">DEL</button>
                      </legend>
                      <details open="open">
                          <summary>Expand</summary>
                          <%= Html.EditorFor(model => model.TradeEventGroups[i]) %>
                      </details>
                  </fieldset>
                  
                  
              <% } %>
          <% } %>
          </div>
          

          <%--ExperienceRewardRelations--%>
          <div class="editor-label">
              <strong><%= Html.LabelFor(m => m.ExperienceRewardRelations)%>*:</strong>
              <button name="command" type="submit" value="experience_reward_add:0" style="color: darkgreen">ADD</button>
          </div>
          
          <div style="margin-left: 20px">
          <% if (Model.ExperienceRewardRelations.Count != 0)
             { %>
              <% for (int i = 0; i < Model.ExperienceRewardRelations.Count; i++)
                 { %> 
                  
                  
                  <fieldset style="border: solid greenyellow 2px;">
                      <legend>
                          <span>ExperienceRewardRelation #<%=i+1 %></span>
                          <button name="command" type="submit" value="<%= TradeEventModel.ExperienceNameCommand %>_up:<%=i %>"<%= (i == 0) ? " disabled=\"disabled\"" : "" %>>&uarr;</button>
                          <button name="command" type="submit" value="<%= TradeEventModel.ExperienceNameCommand %>_down:<%=i %>"<%= (i == Model.ExperienceRewardRelations.Count - 1) ? " disabled=\"disabled\"" : "" %>>&darr;</button>
                          <button name="command" type="submit" value="<%= TradeEventModel.ExperienceNameCommand %>_clone:<%=i %>" style="color: darkgreen">COPY</button>
                          <button name="command" type="submit" value="<%= TradeEventModel.ExperienceNameCommand %>_remove:<%=i %>" style="color: darkred">DEL</button>
                      </legend>
                      <details open="open">
                          <summary>Expand</summary>
                          
                          <%-- Reward --%>
                          <fieldset style="border: solid blue 2px;">

                          <legend>
                          <div class="editor-label"><strong><%= Html.LabelFor(m => m.ExperienceRewardRelations[i].Reward)%>*:</strong></div>
                          </legend>

                              <%= Html.EditorFor(m => m.ExperienceRewardRelations[i].Reward)%>

                              <%--RewardCount--%>
                              <div class="editor-label"><strong><%= Html.LabelFor(m => m.ExperienceRewardRelations[i].RewardCount)%>*:</strong></div>
                              <div class="editor-field">
                                  <%= Html.EditorFor(m => m.ExperienceRewardRelations[i].RewardCount)%>
                                  <%= Html.ValidationMessageFor(m => m.ExperienceRewardRelations[i].RewardCount)%>
                              </div>
                              
                              <%--IsMinor--%>
                              <div class="editor-label"><strong><%= Html.LabelFor(m => m.ExperienceRewardRelations[i].IsMinor)%>*:</strong></div>
                              <div class="editor-field">
                                  <%= Html.EditorFor(m => m.ExperienceRewardRelations[i].IsMinor)%>
                                  <%= Html.ValidationMessageFor(m => m.ExperienceRewardRelations[i].IsMinor)%>
                              </div>
                          
                          </fieldset>
                          


                          <%--Experience--%>
                          <div class="editor-label"><strong><%= Html.LabelFor(m => m.ExperienceRewardRelations[i].Experience)%>*:</strong></div>
                          <div class="editor-field">
                              <%= Html.EditorFor(m => m.ExperienceRewardRelations[i].Experience)%>
                              <%= Html.ValidationMessageFor(m => m.ExperienceRewardRelations[i].Experience)%>
                          </div>

                      </details>
                  </fieldset>

              <% } %>
          <% } %>
          </div>
          
          
          
           <%--WorldRatingRewardRelations--%>
          <div class="editor-label">
              <strong><%= Html.LabelFor(m => m.WorldRatingRewardRelations)%>*:</strong>
              <button name="command" type="submit" value="worldrating_reward_add:0" style="color: darkgreen">ADD</button>
          </div>
          <div style="margin-left: 20px">
          <% if (Model.WorldRatingRewardRelations.Count != 0)
             { %>
              <% for (int i = 0; i < Model.WorldRatingRewardRelations.Count; i++)
                 { %> 
                  
                  
                  <fieldset style="border: solid paleturquoise 2px;">
                      <legend>
                          <span>WorldRatingRewardRelation #<%=i+1 %></span>
                          <button name="command" type="submit" value="<%= TradeEventModel.WorldRatingNameCommand %>_reward_up:<%=i %>"<%= (i == 0) ? " disabled=\"disabled\"" : "" %>>&uarr;</button>
                          <button name="command" type="submit" value="<%= TradeEventModel.WorldRatingNameCommand %>_down:<%=i %>"<%= (i == Model.WorldRatingRewardRelations.Count - 1) ? " disabled=\"disabled\"" : "" %>>&darr;</button>
                          <button name="command" type="submit" value="<%= TradeEventModel.WorldRatingNameCommand %>_clone:<%=i %>" style="color: darkgreen">COPY</button>
                          <button name="command" type="submit" value="<%= TradeEventModel.WorldRatingNameCommand %>_remove:<%=i %>" style="color: darkred">DEL</button>
                      </legend>
                      <details open="open">
                          <summary>Expand</summary>
                          
                          <%-- Reward --%>
                          <fieldset style="border: solid blue 2px;">

                          <legend>
                          <div class="editor-label"><strong><%= Html.LabelFor(m => m.WorldRatingRewardRelations[i].Reward)%>*:</strong></div>
                          </legend>

                              <%= Html.EditorFor(m => m.WorldRatingRewardRelations[i].Reward)%>
                              
                              <%--RewardCount--%>
                              <div class="editor-label"><strong><%= Html.LabelFor(m => m.WorldRatingRewardRelations[i].RewardCount)%>*:</strong></div>
                              <div class="editor-field">
                                  <%= Html.EditorFor(m => m.WorldRatingRewardRelations[i].RewardCount)%>
                                  <%= Html.ValidationMessageFor(m => m.WorldRatingRewardRelations[i].RewardCount)%>
                              </div>
                          
                          </fieldset>

                          <%--Experience--%>
                          <div class="editor-label"><strong><%= Html.LabelFor(m => m.WorldRatingRewardRelations[i].WorldPosition)%>*:</strong></div>
                          <div class="editor-field">
                              <%= Html.EditorFor(m => m.WorldRatingRewardRelations[i].WorldPosition)%>
                              <%= Html.ValidationMessageFor(m => m.WorldRatingRewardRelations[i].WorldPosition)%>
                          </div>

                      </details>
                  </fieldset>

              <% } %>
          <% } %>
          </div>
          

          
          
          

    <button class="saveButton" type="submit" name="command" value=""><%= Model.New ? "Save new Trade Event" : "Save Trade Event #" + Model.EventId %></button>
    <% if (!Model.New) { %>
        <button type="submit" name="command" value="clone">Clone event</button>
    <% } %>

    <hr/>
    <% } %>
  </fieldset>
</div>

</asp:Content>

