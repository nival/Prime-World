<%@ Control Language="C#" Inherits="System.Web.Mvc.ViewUserControl<DynamicQuestInfoModel>" %>
<h3>
    Preconditions
</h3>
<%
            
            List<PreCondition> preConditionList;
            string preConditionListString;
            preConditionList = Model.Data.PreConditions;
            preConditionListString = "PreConditions";                
    
            if (Model.Editable && !Model.ExistingQuest) 
            { 
%>
<div class="add-<%= preConditionListString %>" id="AddPreConditions">
    <a href="javascript: void(0)">Add new PreCondition</a>
</div>
<table id="<%= preConditionListString %>">
    <% }

            var conIndex = 0;
            if (preConditionList != null)
            {
                foreach (var cond in Model.Data.PreConditions)
                {

    %>
    <tr>
        <td>
            <table>
                <tr class="<%= preConditionListString %>-container" id="<%= preConditionListString %>Container<%= Html.Encode(conIndex) %>">
                      <td>
                         <table>
                            <tr><th>PreCondition type</th></tr>
                            <tr>
                        <%                        
                            if (Model.ExistingQuest || !Model.Editable)
                            { %>
                            <td>
                    
                        <%= Html.DropDownList("Data." + preConditionListString + "[" + conIndex + "].PreConditionType",
                            Model.SetSelected(Model.PreConditionTypeList, cond.PreConditionType.ToString()),
                            new {id = "Data_" + preConditionListString + "[" + conIndex + "]_PreConditionType", disabled = Model.ExistingQuest && Model.Editable}) %>
                        <%= Html.Hidden("Data." + preConditionListString + "[" + conIndex + "].PreConditionType", cond.PreConditionType.ToString(),
                            new {id = "Data_" + preConditionListString + "[" + conIndex + "]_PreConditionType"}) %>
                    </td>
                    <% }
                            else
                            { %>
                    <td>
                        <%= Html.DropDownList("Data." + preConditionListString + "[" + conIndex + "].PreConditionType",
                            Model.SetSelected(Model.PreConditionTypeList, cond.PreConditionType.ToString()),
                            new {id = "Data_" + preConditionListString + "[" + conIndex + "]_PreConditionType"}) %>
                    </td>
                    </tr>
                    <% 
                        }
                    switch (cond.PreConditionType)
                    {                       
                        case DynamicQuestPreConditionType.Tournament:
                        {
                            %>
                            <tr><td><p>Tournament Map</p> </td> </tr> <tr>
                    <% 
                        if (Model.ExistingQuest || !Model.Editable)
                            { 
                    %>
                    
                    <td>
                        <%= Html.DropDownList("Data." + preConditionListString + "[" + conIndex + "].TournamentMapType", Model.SetSelected(Model.TournamentMapList, cond.TournamentMapType.ToString()),
                            new {id = "Data_" + preConditionListString + "[" + conIndex + "]_TournamentMapType"}) %>
                        
                        <%= Html.Hidden("Data." + preConditionListString + "[" + conIndex + "].TournamentMapType", cond.TournamentMapType.ToString(), 
                        new {id = "Data_" + preConditionListString + "[" + conIndex + "]_TournamentMapType"}) %>
                    </td>
                    <%
                            } else{ %>
                    <td>
                        <%= Html.DropDownList("Data." + preConditionListString + "[" + conIndex + "].TournamentMapType", Model.SetSelected(Model.TournamentMapList, cond.TournamentMapType.ToString()),
                            new {id = "Data_" + preConditionListString + "[" + conIndex + "]_TournamentMapType"}) %>
                    </td>
                    </tr>
                    <% } 
                    break;
                        }
                        case DynamicQuestPreConditionType.Usual:
                        {
                    %>
                        <tr><td>
                            Nothing
                        </td></tr>
                    <%
                        }
                            break;
                    }
                     conIndex++;

                     if (Model.Editable && !Model.ExistingQuest)
                     { %>
                    <td class="remove-<%= preConditionListString %>">
                        <a href="javascript: void(0)">Remove</a>
                    </td>
                    <% }
                }
            } %>
                </table></td></tr>
            </table>
</table>
