var CommonScripts = CommonScripts || {};

CommonScripts.FillSelectFromString = function (select, string) {
    var vals = select.val();
    if (vals === null || vals === undefined) {
        vals = [];
    }
    var values = string.split(",");
    var options = select.find("option");
    for (var i = 0; i < options.length; i++) {
        if (values.indexOf(options[i].value) !== -1) {
            vals.push(options[i].value);
        }
    }
    select.val(vals);
};

CommonScripts.AddListBox = function (div, listValues, listTexts, multiple) {
    var input = div.find("input");
    input.addClass("hidden");
    var listBox = div.find("select");
    for (var i = 0; i < listBox.length; i++) {
        listBox[i].remove();
    }
    div.append(function () {
        var listBoxCreator;
        if (multiple) {
            listBoxCreator = $("<select multiple>");
        } else {
            listBoxCreator = $("<select>");
        }

        var minLength = listValues.length;
        if (minLength > listTexts.length) {
            minLength = listTexts.length;
        }
        for (var j = 0; j < minLength; j++) {
            listBoxCreator.append("<option value='" + listValues[j] + "'>" + listTexts[j] + "</option>");
        }
        return listBoxCreator;
    });
    listBox = div.find("select");
    listBox.change(function () {
        if (listBox.val() == undefined) {
            CommonScripts.FillSelectFromString(listBox, input.val());
        } else if (listBox.val().length > 0) {
            var allValues = listBox.val();
            if (allValues.constructor === Array) {
                allValues = allValues.join(",");
            }
            input.val(allValues);
        }
    });
    CommonScripts.FillSelectFromString(listBox, input.val());
};

