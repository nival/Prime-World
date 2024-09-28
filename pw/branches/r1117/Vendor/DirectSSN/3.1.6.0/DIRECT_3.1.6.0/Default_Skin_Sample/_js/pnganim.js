//
// Copyright (C) 2010 Solid State Networks, Inc.  All rights reserved.
//
// This usage of this software is restricted to entities which have signed a license agreement
// with Solid State Networks, Inc.
//
// Licenses are valid for only one PRODUCT usage.  Please see the license agreement for further details.
//

var _PngAnim = function() {
    this.timerId = null;
};

_PngAnim.prototype = {
    start: function(elementId, frameHeight, frameCount, frameDuration, reverse) {
        var element = document.getElementById(elementId);
        var i = 0;

        if (reverse === true) {
            i = frameCount - 1;
        }

        this.timerId = setInterval(function() {
            element.style.backgroundPosition = "0px -" + i * frameHeight + "px";

            if (reverse === true) {
                if (--i < 0) {
                    i = frameCount - 1;
                }
            }
            else {
                if (++i >= frameCount) {
                    i = 0;
                }
            }
        }, frameDuration);
    },

    isRunning: function() {
        return this.timerId !== null;
    },

    stop: function() {
        if (this.timerId !== null) {
            clearInterval(this.timerId);
            this.timerId = null;
        }
    }
};

function createPngAnim() {
    return new _PngAnim();
}
