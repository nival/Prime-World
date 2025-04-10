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
    * \tparam object elt object to get the array index of
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
    * \tparam object element object to remove
    */
    Array.prototype.removeElement = function(element) {
        var idx;
        
        idx = this.indexOf(element);
        if (idx >= 0) {
            this.splice(idx, 1);
        }
    };
}

if (!Array.prototype.forEach) {
    /*!
    * array enumerator
    * \tparam function block function to call during each object
    * \tparam object context block context
    */
    Array.prototype.forEach = function(block, context) {
        var i, len;
        
        i = 0;
        len = this.length;

        while (i < len) {
            block.call(context, this[i], i, this);
            ++i;
        }
    };
    // Backwards compatibility
    Array.forEach = function(o,b,c) { o.forEach(b, c); };
}

if (!Array.prototype.forEachReverse) {
    /*!
    * array enumerator
    * \tparam function block function to call during each object
    * \tparam object context block context
    */
    Array.prototype.forEachReverse = function(block, context) {
        var i;

        i = this.length - 1;

        while (i >= 0) {
            block.call(context, this[i], i, this);
            --i;
        }
    };
    // Backwards compatibility
    Array.forEachReverse = function(o,b,c) { o.forEachReverse(b, c); };
}

/*!
* \class String
* \brief String extension
* \docgen function String() {}
*/
if (!String.prototype.replaceAll) {
    /*!
    * replaces all instances of one string with another
    * \tparam string oldString string to find
    * \tparam string newString string to replace
    */
    String.prototype.replaceAll = function(oldString, newString) {
        return this.split(oldString).join(newString);
    };
}

if (!String.prototype.trimChars) {
    /*!
    * trims specified chars off the ends
    * \tparam string chars string of characters to trim
    */
    String.prototype.trimChars = function(chars) {
        var i = 0, j = 0;
        for (i = 0; i < this.length; i++) {
            if (chars.indexOf(this.charAt(i)) === -1) {
                break;
            }
        }
        for (j = this.length - 1; j > i; j--) {
            if (chars.indexOf(this.charAt(j)) === -1) {
                j++;
                break;
            }
        }
        return this.substring(i, j);
    };
}

/* NOTE: We do not extend Object.prototype because it breaks the object-as-hashtables feature of Javascript */

/*!
* merges the properties of two javascript objects
* \tparam object target object to merge the properties to
* \tparam object src object to merge the properties from
*/
function mergeObjectProperties(target, src) {
    var key;

    for (key in src) {
        if (src.hasOwnProperty(key)) {
            if (src[key] instanceof Array) {
                target[key] = {};
                mergeObjectProperties(target[key], src[key]);
            } else {
                target[key] = src[key];
            }
        }
    }
    return target;
};

/*!
* build an array of property keys from an object
* \tparam object obj object to get the properties from
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

/*!
* save an object to a file
* \tparam object obj object to save
* \tparam string fileName location for save
* @treturn bool true if the object is saved or false otherwise
*/
function saveObjectToFile(obj, fileName) {
    var isOk, fileLocation, jsonString, textFileWriter, current, maxChunk, len, writeString, bytesWritten;

    fileLocation = host.app.expandString("{LocalStorage}") + fileName;
    jsonString = JSON.stringify(obj);

    maxChunk = 2048;
    len = jsonString.length;
    current = 0;

    textFileWriter = createTextFileWriter();

    isOk = false;

    if (textFileWriter.open(fileLocation) === true) {
        isOk = true;
        while (isOk === true && current < len) {
            writeString = jsonString.substr(current, maxChunk);
            bytesWritten = textFileWriter.write(writeString);
            if (bytesWritten <= 0) {
                isOk = false;
                break;
            }
            current += bytesWritten;
        }
        textFileWriter.close();
    }

    textFileWriter.release();
    return isOk;
}

/*!
* load object from a file
* \tparam string fileName location for load
* \tparam event onLoadComplete function called when load completed
*/
function loadObjectFromFile(fileName, onLoadComplete) {
    var fileLocation, jsonString, textFileReader, obj;

    fileLocation = host.app.expandString("{LocalStorage}") + fileName;

    textFileReader = createTextFileReader();
    textFileReader.setFileName(fileLocation);

    jsonString = "";
    textFileReader.onRead = function(info) {
        jsonString += info.text;
    };

    textFileReader.onComplete = function(info) {
        obj = null;

        if (info.successful === true) {
            try {
                obj = JSON.parse(jsonString);
            } catch (err) {
                obj = null;
            }
        }

        if (onLoadComplete !== null) {
            onLoadComplete({ "loadedObject": obj });
        }

        this.release();
    };

    textFileReader.start();
}
