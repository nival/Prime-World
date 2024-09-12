$.getScript("/Scripts/CommonScripts.js", function () {
});

var DynamicQuestEnum = DynamicQuestEnum || {};
DynamicQuestEnum.QuestTypeEnum = "";
DynamicQuestEnum.SessionCheckTypeEnum = "";
DynamicQuestEnum.CollectingTypeEnum = "";
DynamicQuestEnum.ResourcesEnum = "";
DynamicQuestEnum.DynamicQuestAwardType = "";
DynamicQuestEnum.DynamicQuestAwardConditionType = "";
DynamicQuestEnum.DynamicQuestMaps = "";
DynamicQuestEnum.DynamicQuestMapsValues = "";
DynamicQuestEnum.DynamicQuestHeroes = "";
DynamicQuestEnum.DynamicQuestHeroesValues = "";
DynamicQuestEnum.DynamicQuestConstructions = "";
DynamicQuestEnum.ModelDataConditionEnum = "";
DynamicQuestEnum.DynamicQuestPreConditionType = "";
DynamicQuestEnum.DynamicQuestTournamentMaps = "";
DynamicQuestEnum.DynamicQuestTournamentMapsValues = "";

function AddObjective(questData) {
    var objectivesCount = $("." + questData + "-container select").length;
    //добавляем поля
    if (objectivesCount >= 5) return;
    var objectiveContainer = $("<tr/>").attr("class", questData + "-container").attr("id", questData + "Container" + objectivesCount).appendTo("#" + questData);
    objectiveContainer.wrap("<tr><td><table>");
    objectiveContainer.before("<tr><th>Objective type</th><th>Description</th><th>ButtonDescription</th></tr>");
    var tdType = $("<td/>").appendTo(objectiveContainer);
    $("<input/>").attr("type", "text").attr("name", "Data." + questData + "[" + objectivesCount + "].EditId").attr("id", "Data_" + questData + "[" + objectivesCount + "]_EditId").attr("hidden", true).attr("value", objectivesCount).appendTo(tdType);
    var typePicker = $("<select/>").attr("name", "Data." + questData + "[" + objectivesCount + "].QuestCheckType").attr("id", "Data_" + questData + "[" + objectivesCount + "]_QuestCheckType").appendTo(tdType);
    DynamicQuestEnum.QuestTypeEnum.forEach(function (value) {
        $("<option>" + value + "</option>").appendTo(typePicker);
    });
    var tdDescr = $("<td/>").appendTo(objectiveContainer);
    $("<input/>").attr("type", "text").attr("name", "Data." + questData + "[" + objectivesCount + "].Description").attr("id", "Data_" + questData + "[" + objectivesCount + "]_Description").appendTo(tdDescr);
    var tdButtDescr = $("<td/>").appendTo(objectiveContainer);
    $("<input/>").attr("type", "text").attr("name", "Data." + questData + "[" + objectivesCount + "].ButtonDescription").attr("id", "Data_" + questData + "[" + objectivesCount + "]_ButtonDescription").appendTo(tdButtDescr);
    var removeButtonDiv = $("<td/>").attr("class", "remove-" + questData).appendTo(objectiveContainer);
    $("<a/>").attr("href", "javascript: void(0)").text("Remove").appendTo(removeButtonDiv);
    //на нажатие этого элемента добавляем обработчик - функцию удаления
    removeButtonDiv.click(function () {
        RemoveObjective(this, questData);
    });
    objectivesCount++;
}

function RemoveObjective(target, questData) {
    var objectivesCount = $("." + questData + "-container select").length;
    var containerName = questData + "Container";
    var id = $(target).parent().attr("id");
    var recalculateStartNum = parseInt(id.substring(containerName.length));
    //удаляем tr
    $(target)
    .parents("tr:last")
    .remove();

    AppendObjectiveConditions(questData);

    for (var i = recalculateStartNum + 1; i < objectivesCount; i++) {
        //функция пересчета аттрибутов name и id
        RecalculateObjectiveNamesAndIds(i, questData);
    }
}

function RecalculateObjectiveNamesAndIds(number, questData) {
    var prevNumber = number - 1;
    $("#" + questData + "Container" + number).attr("id", questData + "Container" + prevNumber);
    //скобки "[" и "]" которые присутствуют в id DOM-объекта в jquery селекторе
    // необходим экранировать двойным обратным слэшем \\
    $("#" + questData + "\\[" + number + "\\]_EditId")
    .attr("id", "" + questData + "[" + prevNumber + "]_EditId")
    .attr("name", "" + questData + "[" + prevNumber + "].EditId")
    .attr("value", prevNumber);
    $("#" + questData + "\\[" + number + "\\]_QuestCheckType")
    .attr("id", "" + questData + "[" + prevNumber + "]_QuestCheckType")
    .attr("name", "" + questData + "[" + prevNumber + "].QuestCheckType");
    $("#" + questData + "\\[" + number + "\\]_Description")
    .attr("id", "" + questData + "[" + prevNumber + "]_Description")
    .attr("name", "" + questData + "[" + prevNumber + "].Description");
    $("#" + questData + "\\[" + number + "\\]_ButtonDescription")
    .attr("id", "" + questData + "[" + prevNumber + "]_ButtonDescription")
    .attr("name", "" + questData + "[" + prevNumber + "].ButtonDescription");
}

function AppendObjectiveConditions(questData) {
    var objective = $("." + questData + "-container select");
    var objectiveLen = objective.length;
    var conditionLen = RecalculateObjectiveConditionsName(questData);

    for (var i = conditionLen; i < objectiveLen; i++) {
        ChangeObjectiveConditions(objective[i], questData);
    }
}

function ChangeObjectiveConditions(select, questData) {
    select = $(select);

    var val = select.val();
    var id = select.attr("name").replace(/\D/g, "");
    var tr = ObjectiveConditionsPattern(val, id, questData);
    var objectiveContainer = select.parents("tr:first");

    if (objectiveContainer.next().is("." + questData + "-condition")) {
        objectiveContainer
      .next()
      .remove()
      .end()
      .after(tr);
    }
    else {
        objectiveContainer
      .after(tr);
    }

    AddListBoxes();
}

function ObjectiveConditionsPattern(objectiveConditionType, id, questDataType) {
    var html = "<tr class=\"" + questDataType + "-condition\"><td colspan=\"4\"><table><tr><th>Conditions</th></tr>{pattern}</table></td></tr>";
    var pattern = "";
    var index = 0;

    switch (objectiveConditionType) {
        case "SessionResult":
            {
                pattern += "<tr>";
                pattern += "<td class=\"AddListBoxMaps\"><p>Game type</p>";
                pattern += "<input name=\"Data." + questDataType + "[" + id + "].SessionCondition.GameType\" type=\"text\" value=\"" + DynamicQuestEnum.DynamicQuestMapsValues.join(",") + "\"></td>";
                pattern += "<td class=\"AddListBoxHeroes\"><p>Hero</p>";
                pattern += "<input name=\"Data." + questDataType + "[" + id + "].SessionCondition.PickedHero\" type=\"text\" value=\"" + DynamicQuestEnum.DynamicQuestHeroesValues.join(",") + "\"></td>";
                pattern += "<td><p>Total amount</p>";
                pattern += "<input name=\"Data." + questDataType + "[" + id + "].SessionCondition.TotalValue\" type=\"text\" value=\"0\"></td>";
                pattern += "</tr><tr>";
                pattern += "<td><p>Type to collect</p>";
                pattern += "<select name=\"Data." + questDataType + "[" + id + "].SessionCondition.CollectingType\">";
                DynamicQuestEnum.CollectingTypeEnum.forEach(function (foreachValue) {
                    pattern += "<option>" + foreachValue + "</option>";
                });
                pattern += "</select></td>";
                pattern += "<td><p>Increment per battle</p>";
                pattern += "<input name=\"Data." + questDataType + "[" + id + "].SessionCondition.IncrementPerBattle\" type=\"text\" value=\"0\"></td>";
                pattern += "<td><p>Session result influence</p>";
                pattern += "<select name=\"Data." + questDataType + "[" + id + "].SessionCondition.SessionCheckType\">";
                for (index = 0; index < DynamicQuestEnum.SessionCheckTypeEnum.length; index++) {
                    pattern += "<option value=\"" + index + "\">" + DynamicQuestEnum.SessionCheckTypeEnum[index] + "</option>";
                };
                pattern += "</select></td>";
                pattern += "</tr><tr>";
                pattern += "<td><p>Player party size</p>";
                pattern += "<input name=\"Data." + questDataType + "[" + id + "].SessionCondition.PlayerPartySize\" type=\"text\" value=\"1\"></td>";
                pattern += "<td><p>Enemy party size</p>";
                pattern += "<input name=\"Data." + questDataType + "[" + id + "].SessionCondition.EnemyPartySize\" type=\"text\" value=\"1\"></td>";
                pattern += "<td><p>Check only for guild games (0 - false, 1 - true)</p>";
                pattern += "<input name=\"Data." + questDataType + "[" + id + "].SessionCondition.IsGuildGame\" type=\"text\" value=\"0\"></td>";
                pattern += "</tr><tr>";
                // NUM_TASK - additions:
                pattern += "<td><p>Player party size strong condition</p>";
                pattern += "<input name=\"Data." + questDataType + "[" + id + "].SessionCondition.IsPlayerPartySizeStrongCond\" type=\"text\" value=\"0\"></td>";
                pattern += "<td><p>Enemy party size strong condition</p>";
                pattern += "<input name=\"Data." + questDataType + "[" + id + "].SessionCondition.IsEnemyPartySizeStrongCond\" type=\"text\" value=\"0\"></td>";
                pattern += "<td><p>Strong conditions: 0 - false, 1 - true</p></td>";
                // end of additions
                pattern += "</tr>";
                break;
            }
        case "SessionInfo":
            {
                pattern += "<tr>";
                pattern += "<td class=\"AddListBoxMaps\"><p>Game type</p>";
                pattern += "<input name=\"Data." + questDataType + "[" + id + "].SessionCondition.GameType\" type=\"text\" value=\"" + DynamicQuestEnum.DynamicQuestMapsValues.join(",") + "\"></td>";
                pattern += "<td class=\"AddListBoxHeroes\"><p>Hero</p>";
                pattern += "<input name=\"Data." + questDataType + "[" + id + "].SessionCondition.PickedHero\" type=\"text\" value=\"" + DynamicQuestEnum.DynamicQuestHeroesValues.join(",") + "\"></td>";
                pattern += "<td><p>Total amount</p>";
                pattern += "<input name=\"Data." + questDataType + "[" + id + "].SessionCondition.TotalValue\" type=\"text\" value=\"0\"></td>";
                pattern += "<td><p>Session result influence</p>";
                pattern += "<select name=\"Data." + questDataType + "[" + id + "].SessionCondition.SessionCheckType\">";
                for (index = 0; index < DynamicQuestEnum.SessionCheckTypeEnum.length; index++) {
                    pattern += "<option value=\"" + index + "\">" + DynamicQuestEnum.SessionCheckTypeEnum[index] + "</option>";
                };
                pattern += "</select>";
                pattern += "<input name=\"Data." + questDataType + "[" + id + "].SessionCondition.CollectingType\", value=\"\", class=\"hidden\"/>";
                pattern += "</select></td>";
                pattern += "</tr><tr>";
                pattern += "<td><p>Player party size</p>";
                pattern += "<input name=\"Data." + questDataType + "[" + id + "].SessionCondition.PlayerPartySize\" type=\"text\" value=\"1\"></td>";
                pattern += "<td><p>Enemy party size</p>";
                pattern += "<input name=\"Data." + questDataType + "[" + id + "].SessionCondition.EnemyPartySize\" type=\"text\" value=\"1\"></td>";
                pattern += "<td><p>Check only for guild games (0 - false, 1 - true)</p>";
                pattern += "<input name=\"Data." + questDataType + "[" + id + "].SessionCondition.IsGuildGame\" type=\"text\" value=\"0\"></td>";
                // NUM_TASK - additions:
                pattern += "<td><p>Player party size strong condition</p>";
                pattern += "<input name=\"Data." + questDataType + "[" + id + "].SessionCondition.IsPlayerPartySizeStrongCond\" type=\"text\" value=\"0\"></td>";
                pattern += "<td><p>Enemy party size strong condition</p>";
                pattern += "<input name=\"Data." + questDataType + "[" + id + "].SessionCondition.IsEnemyPartySizeStrongCond\" type=\"text\" value=\"0\"></td>";
                pattern += "<td><p>Strong conditions: 0 - false, 1 - true</p></td>";
                // end of additions
                pattern += "</tr>";
                break;
            }
        case "Instant":
            {
                pattern += "<tr>";
                pattern += "<td><p>Resource type</p>";
                pattern += "<select name=\"Data." + questDataType + "[" + id + "].InstantCondition.ResourceType\">";
                for (index = 0; index < DynamicQuestEnum.ResourcesEnum.length; index++) {
                    pattern += "<option value=\"" + index + "\">" + DynamicQuestEnum.ResourcesEnum[index] + "</option>";
                }
                pattern += "</select></td>";
                pattern += "<td><p>Total amount or String data if TalentsToPay/CustomCurrency</p>";
                pattern += "<input name=\"Data." + questDataType + "[" + id + "].InstantCondition.TotalValue\" type=\"text\" value=\"0\"></td>";
                pattern += "</tr>";
                break;
            }
        case "ModelData":
            {
                pattern += "<tr>";
                pattern += "<td><p>Condition type</p>";
                pattern += "<select name=\"Data." + questDataType + "[" + id + "].ModelDataCondition.TypeToCollect\">";
                for (index = 0; index < DynamicQuestEnum.ModelDataConditionEnum.length; index++) {
                    pattern += "<option value=\"" + index + "\">" + DynamicQuestEnum.ModelDataConditionEnum[index] + "</option>";
                }
                pattern += "</select></td>";
                pattern += "<td><p>Total amount</p>";
                pattern += "<input name=\"Data." + questDataType + "[" + id + "].ModelDataCondition.TotalValue\" type=\"text\" value=\"0\"></td>";
                pattern += "<td><p>PersistentId or string info</p>";
                pattern += "<input name=\"Data." + questDataType + "[" + id + "].ModelDataCondition.PersistentId\" type=\"text\" value=\"\"></td>";
                pattern += "</tr>";
                break;
            }
    }

    return html.replace("{pattern}", pattern);
}

function RecalculateObjectiveConditionsName(questData) {
    var condition = $("." + questData + "-condition");
    var conditionLen = condition.length;

    for (var i = 0; i < conditionLen; i++) {
        $("[name]", condition[i])
      .each(function () {
          $(this).attr("name", function (index, attr) {
              return attr.replace(/[\d]+/g, i);
          });
      });
    }
    return conditionLen;
}

function AddListBoxes() {
    $(".AddListBoxMaps").each(function () {
        CommonScripts.AddListBox($(this), DynamicQuestEnum.DynamicQuestMapsValues, DynamicQuestEnum.DynamicQuestMaps, true);
    });
    $(".AddListBoxHeroes").each(function () {
        CommonScripts.AddListBox($(this), DynamicQuestEnum.DynamicQuestHeroesValues, DynamicQuestEnum.DynamicQuestHeroes, true);
    });
    $(".AddListBoxTournamentMaps").each(function () {
        CommonScripts.AddListBox($(this), DynamicQuestEnum.DynamicQuestTournamentMapsValues, DynamicQuestEnum.DynamicQuestTournamentMaps, false);
    });

};

function AddCommonObjectives() {
    $("#AddObjective").click(function () {
        AddObjective("QuestData");
        setTimeout(function () { AppendObjectiveConditions("QuestData"); }, 20);
    });

    $(".remove-QuestData").click(function () {
        RemoveObjective(this, "QuestData");
    });

    $("#QuestData")
    .on("change", ".QuestData-container select", function () {
        ChangeObjectiveConditions(this, "QuestData");
    });
};

function AddAlternativeObjectives() {
    $("#AddAlternativeObjective").click(function () {
        AddObjective("AlternativeQuestData");
        setTimeout(function () { AppendObjectiveConditions("AlternativeQuestData"); }, 20);
    });

    $(".remove-AlternativeQuestData").click(function () {
        RemoveObjective(this, "AlternativeQuestData");
    });

    $("#AlternativeQuestData")
    .on("change", ".AlternativeQuestData-container select", function () {
        ChangeObjectiveConditions(this, "AlternativeQuestData");
    });
};

function AddAward(awardsType) {
    var awardsCount = $("." + awardsType + "-container select[id$='_AwardType']").length;
    //добавляем поля
    var awardContainer = $("<tr/>").attr("class", awardsType + "-container").attr("id", awardsType + "Container" + awardsCount).appendTo("#" + awardsType);
    awardContainer.wrap("<tr><td><table>");
    awardContainer.before("<tr><th>Award type</th><th>Award condition</th></tr>");
    var tdType = $("<td/>").appendTo(awardContainer);
    var typePicker = $("<select/>").attr("name", "Data." + awardsType + "[" + awardsCount + "].AwardType").attr("id", "Data_" + awardsType + "[" + awardsCount + "]_AwardType").appendTo(tdType);
    DynamicQuestEnum.DynamicQuestAwardType.forEach(function (localValue) {
        $("<option>" + localValue + "</option>").appendTo(typePicker);
    });
    var tdCond = $("<td/>").appendTo(awardContainer);
    var condPicker = $("<select/>").attr("name", "Data." + awardsType + "[" + awardsCount + "].AwardConditionType").attr("id", "Data_" + awardsType + "[" + awardsCount + "]_AwardConditionType").appendTo(tdCond);
    DynamicQuestEnum.DynamicQuestAwardConditionType.forEach(function (localValue, index) {
        if (index == 0) {
            $("<option selected>" + localValue + "</option>").appendTo(condPicker);
        } else {
            $("<option>" + localValue + "</option>").appendTo(condPicker);
        }
    });

    var removeButtonDiv = $("<td/>").attr("class", "remove-" + awardsType).appendTo(awardContainer);
    $("<a/>").attr("href", "javascript: void(0)").text("Remove").appendTo(removeButtonDiv);
    //на нажатие этого элемента добавляем обработчик - функцию удаления
    removeButtonDiv.click(function () {
        RemoveAward(this, awardsType);
    });
    awardsCount++;
}

function RemoveAward(target, awardsType) {
    var awardsCount = $("." + awardsType + "-container select[id$='_AwardType']").length;
    var containerName = awardsType + "Container";
    var id = $(target).parent().attr("id");
    var recalculateStartNum = parseInt(id.substring(containerName.length));
    //удаляем этот div
    $(target).parents("tr:last").remove();

    AppendAwardInputs();

    for (var i = recalculateStartNum + 1; i < awardsCount; i++) {
        //функция пересчета аттрибутов name и id
        RecalculateAwardNamesAndIds(i, awardsType);
    }
}

function RecalculateAwardNamesAndIds(number, awardsType) {
    var prevNumber = number - 1;
    $("#" + awardsType + "Container" + number).attr("id", awardsType + "Container" + prevNumber);
    //скобки "[" и "]" которые присутствуют в id DOM-объекта в jquery селекторе 
    // необходим экранировать двойным обратным слэшем \\
    $("#Data_" + awardsType + "\\[" + number + "\\]_AwardType")
    .attr("id", "Data_" + awardsType + "[" + prevNumber + "]_AwardType")
    .attr("name", "Data." + awardsType + "[" + prevNumber + "].AwardType");
}

function AppendAwardInputs(awardsType) {
    var award = $("." + awardsType + "-container select[id$='_AwardType']");
    var awardLen = award.length;
    var conditionLen = RecalculateAwardsName(awardsType);

    for (var i = conditionLen; i < awardLen; i++) {
        ChangeAwards(award[i], awardsType);
    }
}

function ChangeAwards(select, awardsType) {
    select = $(select);

    var val = select.val();
    var id = select.attr("name").replace(/\D/g, "");
    var tr = AwardsPattern(val, id, awardsType);
    var awardContainer = select.parents("tr:first");

    if (awardContainer.next().is("." + awardsType + "-input")) {
        awardContainer
      .next()
      .remove()
      .end()
      .after(tr);
    }
    else {
        awardContainer
      .after(tr);
    }

    AddListBoxes();
}

function AwardsPattern(value, id, awardsType) {
    var html = "<tr class=\"" + awardsType + "-input\">{pattern}</tr>";
    var pattern = "";

    switch (value) {
        case "PremiumAcc":
        case "Gold":
        case "Resource1":
        case "Resource2":
        case "Resource3":
        case "Silver":
        case "Perl":
        case "RedPerl":
        case "Experience":
            {
                pattern += "<td><input name=\"Data." + awardsType + "[" + id + "].Value\" type=\"text\" value=\"0\"></td>";
                break;
            }
        case "Talent":
            {
                pattern += "<td><p>Talent</p>";
                pattern += "<input name=\"Data." + awardsType + "[" + id + "].TextData\" type=\"text\" value=\"\"></td>";
                pattern += "<td><p>Count</p>";
                pattern += "<input name=\"Data." + awardsType + "[" + id + "].Value\" type=\"text\" value=\"0\"></td>";
                pattern += "<td><p>RefinePoints</p>";
                pattern += "<input name=\"Data." + awardsType + "[" + id + "].AdditionalData2\" type=\"text\" value=\"1\"></td>";
                break;
            }
        case "CustomFlag":
        case "Skin":
            {
                pattern += "<td><p>PersistentId</p>";
                pattern += "<input name=\"Data." + awardsType + "[" + id + "].Value\" type=\"text\" value=\"\"></td>";
                break;
            }
        case "Quest":
            {
                pattern += "<td><p>Dynamic quest id</p>";
                pattern += "<input name=\"Data." + awardsType + "[" + id + "].Value\" type=\"text\" value=\"\"></td>";
                break;
            }
        case "RandomTalent":
            {
                pattern += "<td><p>Quality</p>";
                pattern += "<input name=\"Data." + awardsType + "[" + id + "].TextData\" type=\"text\" value=\"excellent\"></td>";
                pattern += "<td><p>Count</p>";
                pattern += "<input name=\"Data." + awardsType + "[" + id + "].Value\" type=\"text\" value=\"0\"></td>";
                pattern += "<td><p>RefinePoints</p>";
                pattern += "<input name=\"Data." + awardsType + "[" + id + "].AdditionalData2\" type=\"text\" value=\"1\"></td>";
                break;
            }
        case "Construction":
            {
                pattern += "<td><select name=\"Data." + awardsType + "[" + id + "].Value\">";
                DynamicQuestEnum.DynamicQuestConstructions.forEach(function (foreachValue) {
                    pattern += "<option>" + foreachValue + "</option>";
                });
                pattern += "</select></td>";
                break;
            }
        case "Hero":
        case "HeroStatsReset":
            {
                pattern += "<td><select name=\"Data." + awardsType + "[" + id + "].Value\">";
                DynamicQuestEnum.DynamicQuestHeroes.forEach(function (foreachValue) {
                    pattern += "<option>" + foreachValue + "</option>";
                });
                pattern += "</select></td>";
                break;
            }
        case "HeroExperience":
            {
                pattern += "<td><p>Hero</p><select name=\"Data." + awardsType + "[" + id + "].TextData\">";
                DynamicQuestEnum.DynamicQuestHeroes.forEach(function (foreachValue) {
                    pattern += "<option>" + foreachValue + "</option>";
                });
                pattern += "</select></td>";
                pattern += "<td><input name=\"Data." + awardsType + "[" + id + "].Value\" type=\"text\" value=\"0\"></td>";
                break;
            }
        case "Lamp":
            {
                pattern += "<td><p>Lamp settings in format lampType:goldBonus:transactions:duration, ex: 20:1000:5:86400</p>";
                pattern += "<input name=\"Data." + awardsType + "[" + id + "].TextData\" type=\"text\" value=\"20:1000:5:86400\"></td>";
                break;
            }
        case "RandomHero":
            {
                pattern += "<td class=\"AddListBoxHeroes\"><p>Available heroes</p>";
                pattern += "<input name=\"Data." + awardsType + "[" + id + "].TextData\" type=\"text\" value=\"" + DynamicQuestEnum.DynamicQuestHeroesValues.join(",") + "\"></td>";
                break;
            }
        case "RandomSkin":
            {
                pattern += "<td><p>Available skins</p>";
                pattern += "<input name=\"Data." + awardsType + "[" + id + "].TextData\" type=\"text\" value=\"\"></td>";
                break;
            }
        case "RandomTalentFromPool":
            {
                pattern += "<td><p>Talents pool</p>";
                pattern += "<input name=\"Data." + awardsType + "[" + id + "].TextData\" type=\"text\" value=\"\"></td>";
                pattern += "<td><p>Count</p>";
                pattern += "<input name=\"Data." + awardsType + "[" + id + "].Value\" type=\"text\" value=\"0\"></td>";
                pattern += "<td><p>RefinePoints</p>";
                pattern += "<input name=\"Data." + awardsType + "[" + id + "].AdditionalData2\" type=\"text\" value=\"1\"></td>";
                break;
            }
        case "AlreadyCompletedQuest":
            {
                pattern += "<td><p>Quests to remove</p>";
                pattern += "<input name=\"Data." + awardsType + "[" + id + "].TextData\" type=\"text\" value=\"\"></td>";
                pattern += "<td><p>Dynamic quest id</p>";
                pattern += "<input name=\"Data." + awardsType + "[" + id + "].Value\" type=\"text\" value=\"0\"></td>";
                break;
            }
        case "UpgradeHeroTalentsEvent":
            {
                pattern += "<td><p>Какое количество героев нам проапать ?</p>";
                pattern += "<input name=\"Data." + awardsType + "[" + id + "].Value\" type=\"text\" value=\"\"></td>";
                break;
            }
        case "Shard": 
            {
                pattern += "<td><p>Enter shards count ?</p>";
                pattern += "<input name=\"Data." + awardsType + "[" + id + "].Value\" type=\"text\" value=\"\"></td>";
                break;
            }
        case "CustomCurrency":
        {
            pattern += "<td><p>CurrencyName</p>";
            pattern += "<input name=\"Data." + awardsType + "[" + id + "].TextData\" type=\"text\" value=\"\"></td>";
            pattern += "<td><p>Count</p>";
            pattern += "<input name=\"Data." + awardsType + "[" + id + "].Value\" type=\"text\" value=\"0\"></td>";
            break;
        }
        case "Lootbox":
        {
            pattern += "<td><p>Lootbox persistentId</p>";
            pattern += "<input name=\"Data." + awardsType + "[" + id + "].TextData\" type=\"text\" value=\"\"></td>";

            pattern += "<td><p>Lootboxes count</p>";
            pattern += "<input name=\"Data." + awardsType + "[" + id + "].Value\" type=\"text\" value=\"1\"></td>";
            break;
        }
    }

    if (pattern.localeCompare("") === 0) return "";
    
    return html.replace("{pattern}", pattern);
}

function RecalculateAwardsName(questData) {
    var award = $("." + questData + "-input");
    var awardLen = award.length;

    for (var i = 0; i < awardLen; i++) {
        $("[name]", award[i])
      .each(function () {
          $(this).attr("name", function (index, attr) {
              return attr.replace(/\[\d\]+/g, "["+i+"]");
          });
      });
    }
    return awardLen;
}

function AddCommonAwards() {
    $("#AddAwards").click(function () {
        AddAward("Awards");
        setTimeout(function () { AppendAwardInputs("Awards"); }, 20);
    });

    $(".remove-Awards").click(function () {
        RemoveAward(this, "Awards");
    });

    $("#Awards")
    .on("change", ".Awards-container select[id$='_AwardType']", function () {
        ChangeAwards(this, "Awards");
    });
};

function AddAlternativeAwards() {
    $("#AddAlternativeAwards").click(function () {
        AddAward("AlternativeAwards");
        setTimeout(function () { AppendAwardInputs("AlternativeAwards"); }, 20);
    });

    $(".remove-AlternativeAwards").click(function () {
        RemoveAward(this, "AlternativeAwards");
    });

    $("#AlternativeAwards")
        .on("change", ".AlternativeAwards-container select[id$='_AwardType']", function () {
            ChangeAwards(this, "AlternativeAwards");
        });
};

function AddPreCondition(preconditionType) {
    var preconditionCount = $("." + preconditionType + "-container select").length;
    //добавляем поля
    var preconditionContainer = $("<tr/>").attr("class", preconditionType + "-container").attr("id", preconditionType + "Container" + preconditionCount).appendTo("#" + preconditionType);
    preconditionContainer.wrap("<tr><td><table>");
    preconditionContainer.before("<tr><th>PreCondition type</th></tr>");
    var tdType = $("<td/>").appendTo(preconditionContainer);
    var typePicker = $("<select/>").attr("name", "Data." + preconditionType + "[" + preconditionCount + "].PreConditionType").attr("id", "Data_" + preconditionType + "[" + preconditionCount + "]_PreConditionType").appendTo(tdType);
    DynamicQuestEnum.DynamicQuestPreConditionType.forEach(function (localValue) {
        $("<option>" + localValue + "</option>").appendTo(typePicker);
    });

    var removeButtonDiv = $("<td/>").attr("class", "remove-" + preconditionType).appendTo(preconditionContainer);
    $("<a/>").attr("href", "javascript: void(0)").text("Remove").appendTo(removeButtonDiv);
    //на нажатие этого элемента добавляем обработчик - функцию удаления
    removeButtonDiv.click(function () {
        RemovePreCondition(this, preconditionType);
    });
    preconditionCount++;
}

function RemovePreCondition(target, preconditionType) {
    var preconditionCount = $("." + preconditionType + "-container select").length;
    var containerName = preconditionType + "Container";
    var id = $(target).parent().attr("id");
    var recalculateStartNum = parseInt(id.substring(containerName.length));
    //удаляем этот div
    $(target).parents("tr:last").remove();

    AppendPreConditionInputs();

    for (var i = recalculateStartNum + 1; i < preconditionCount; i++) {
        //функция пересчета аттрибутов name и id
        RecalculatePreConditionNamesAndIds(i, preconditionType);
    }
}

function RecalculatePreConditionNamesAndIds(number, preconditionType) {
    var prevNumber = number - 1;
    $("#" + preconditionType + "Container" + number).attr("id", preconditionType + "Container" + prevNumber);
    //скобки "[" и "]" которые присутствуют в id DOM-объекта в jquery селекторе 
    // необходим экранировать двойным обратным слэшем \\
    $("#Data_" + preconditionType + "\\[" + number + "\\]_PreConditionType")
    .attr("id", "Data_" + preconditionType + "[" + prevNumber + "]_PreConditionType")
    .attr("name", "Data." + preconditionType + "[" + prevNumber + "].PreConditionType");
}

function AppendPreConditionInputs(preconditionType) {
    var precondition = $("." + preconditionType + "-container select");
    var preconditionLen = precondition.length;
    var conditionLen = RecalculatePreConditionName(preconditionType);

    for (var i = conditionLen; i < preconditionLen; i++) {
        ChangePreConditions(precondition[i], preconditionType);
    }
}

function ChangePreConditions(select, preconditionType) {
    select = $(select);

    var val = select.val();
    var id = select.attr("name").replace(/\D/g, "");
    var tr = PreConditionsPattern(val, id, preconditionType);
    var preconditionContainer = select.parents("tr:first");

    if (preconditionContainer.next().is("." + preconditionType + "-input")) {
        preconditionContainer
      .next()
      .remove()
      .end()
      .after(tr);
    }
    else {
        preconditionContainer
      .after(tr);
    }

    AddListBoxes();
}

function PreConditionsPattern(value, id, preconditionType) {
    var html = "<tr class=\"" + preconditionType + "-input\">{pattern}</tr>";
    var pattern = "";

    switch (value) {
        case "Usual":
           pattern += "<td>Nothing</td>";
        break;
        case "Tournament":
            {
               
                pattern += "<td><select name=\"Data." + preconditionType + "[" + id + "].TournamentMapType\" id=\"Data_" + preconditionType + "[" + id + "]_TournamentMapType\">";
                DynamicQuestEnum.DynamicQuestTournamentMaps.forEach(function (foreachValue, index) {
                    if (DynamicQuestEnum.DynamicQuestTournamentMaps.length - 1 == index) {
                        pattern += "<option selected type=\"text\" value=\"" + DynamicQuestEnum.DynamicQuestTournamentMapsValues[index] + "\">" + foreachValue + "</option>";
                    } else {
                        pattern += "<option type=\"text\" value=\"" + DynamicQuestEnum.DynamicQuestTournamentMapsValues[index] + "\">" + foreachValue + "</option>";
                    }
                });

                pattern += "</select></td>";

                break;
            }
    }
    if (parent === "") return "";
    return html.replace("{pattern}", pattern);
}

function RecalculatePreConditionName(questData) {
    var precondition = $("." + questData + "-input");
    var preconditionLen = precondition.length;

    for (var i = 0; i < preconditionLen; i++) {
        $("[name]", precondition[i])
      .each(function () {
          $(this).attr("name", function (index, attr) {
              return attr.replace(/[\d]+/g, i);
          });
      });
    }
  return preconditionLen;
}


function AddPreConditions() {
    $(".add-PreConditions").click(function () {
        AddPreCondition("PreConditions");
        setTimeout(function () { AppendPreConditionInputs("PreConditions"); }, 20);
    });

    $(".remove-PreConditions").click(function () {
        RemovePreCondition(this, "PreConditions");
    });

    $("#PreConditions")
    .on("change", ".PreConditions-container select", function () {
        ChangePreConditions(this, "PreConditions");
    });
};