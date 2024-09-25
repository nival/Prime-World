// Microsft condition code compilation (Should be visible to ie)
/*@cc_on @*/
/*@if (@_win32 && @_jscript_version >= 5) 
if (!window.XMLHttpRequest) {
    window.XMLHttpRequest = function() { return new ActiveXObject('Microsoft.XMLHTTP') }
}
@end @*/

/*!
* \file jshelper.js
* \brief File containing general javascript extensions
*/

/*!
* \class Array
* \brief Array extension
* \docgen function Array() {}
*/
if (!Array.prototype.indexOf) {
    /*!
    * gets the index of an object
    * \tparam object object object to get the array index of
    * \tparam object from optional starting point
    * @treturn int index of object in array
    */
    Array.prototype.indexOf = function(elt /*, from */) {
        var len, from;

        len = this.length;
        from = Number(arguments[1]) || 0;
        from = (from < 0)
             ? Math.ceil(from)
             : Math.floor(from);
        if (from < 0) {
            from += len;
        }

        while (from < len) {
            if (this.hasOwnProperty(from) && this[from] === elt) {
                return from;
            }
            
            ++from;
        }
        return -1;
    };
}

if (!Array.prototype.removeIndex) {
    /*!
    * removes an object at the given index
    * \tparam int index index of object
    */
    Array.prototype.removeIndex = function(index) {
        this.splice(index, 1);
    };
}

if (!Array.prototype.removeElement) {
    /*!
    * removes an object
    * \tparam int object object to remove
    */
    Array.prototype.removeElement = function(element) {
        var idx;
        
        idx = this.indexOf(element);
        if (idx >= 0) {
            this.splice(idx, 1);
        }
    };
}

if (!Array.forEach) {
    /*!
    * array enumerator
    * \tparam array array array to enumerate
    * \tparam function block function to call during each object
    * \tparam object context block context
    */
    Array.forEach = function(object, block, context) {
        var i, len;
        
        i = 0;
        len = object.length;

        while (i < len) {
            block.call(context, object[i], i, object);
            ++i;
        }
    };
}

if (!Array.forEachReverse) {
    /*!
    * array enumerator
    * \tparam array array array to enumerate in reverse
    * \tparam function block function to call during each object
    * \tparam object context block context
    */
    Array.forEachReverse = function(object, block, context) {
        var i;

        i = object.length - 1;

        while (i >= 0) {
            block.call(context, object[i], i, object);
            --i;
        }
    };
}

/*!
* merges the properties of two javascript objects
* \tparam object target object to merge the properties to
* \tparam object src object to merge the properties from
*/
function mergeObjectProperties(target, src) {
    var key;

    for (key in src) {
        if (src.hasOwnProperty(key)) {
            target[key] = src[key];
        }
    }
};

/*!
* build an array of property keys from an object
* \tparam object obj object to merge the properties from
* \treturn list array of property keys
*/
function getObjectProperties(obj) {
    var key, keys;

    keys = [];
    for (key in obj) {
        if (obj.hasOwnProperty(key)) {
            keys.push(key);
        }
    }
    return keys;
};
