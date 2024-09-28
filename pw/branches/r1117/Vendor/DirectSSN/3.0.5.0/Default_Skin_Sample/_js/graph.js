//
// Copyright (C) 2010 Solid State Networks, Inc.  All rights reserved.
//
// This usage of this software is restricted to entities which have signed a license agreement
// with Solid State Networks, Inc.
//
// Licenses are valid for only one PRODUCT usage.  Please see the license agreement for further details.
//

_Graph = function(numPoints) {
    this._values = [];
    this._graphBox = [];
    this._maxValue = 1;
    this._numPoints = numPoints;
    this._graphHeight = 0;
    
    for (var x = 0; x < numPoints; ++x) {
        this._values[x] = 0;
    }
}

_Graph.prototype = {
    create: function(graphContainer) {
        var rowElement = graphContainer.insertRow(rowElement, 0);

        for (var x = 0; x < this._numPoints; ++x) {
            var columnElement = rowElement.insertCell(0);
            columnElement.setAttribute('className', 'graphBoxContainer');

            var graphBoxElement = document.createElement('div');
            graphBoxElement.setAttribute('className', 'graphBox');
            this._graphBox[x] = graphBoxElement;

            columnElement.appendChild(graphBoxElement)
            rowElement.appendChild(columnElement);
        }

        this._graphHeight = graphContainer.offsetHeight;
        this.draw();
    },

    draw: function() {
        var maxValue = this._maxValue * 1.20;
        for (var x = 0; x < this._numPoints; ++x) {
            var perc = this._values[x] / maxValue;
            if (perc > 1) {
                alert(perc + ' ' + this._values[x] + ' ' + maxValue);
            }
            var value = this._graphHeight * (1 - perc);
            this._graphBox[x].style.height = Math.max(value, 1) + 'px';
        }
    },

    addValue: function(value) {
        value = parseInt(value);
        if (value > this._maxValue) {
            this._maxValue = value;
        }

        for (var x = 0; x < this._numPoints - 1; ++x) {
            this._values[x] = this._values[x + 1];
        }

        this._values[this._numPoints - 1] = value;
        this.draw();
    }
}

    
    
