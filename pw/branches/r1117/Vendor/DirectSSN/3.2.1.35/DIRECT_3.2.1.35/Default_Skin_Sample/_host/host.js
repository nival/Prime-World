/*!
* \file host.js
* \brief File containing Host class
*/

/*!
* \class Host
* \brief Host Top level container for the host
*/

function Host() {
   /*!
   * Window attached to host
   * \type SkinWindow
   */
    this.skinWindow = null;
   /*!
   * App attached to host
   * \type app
   */
    this.app = null;
   /*!
   * Hex table for encoding/decoding hex
   * \type array
   */    
    this.hexTable = {
        "00": 0, "01": 1, "02": 2, "03": 3, "04": 4, "05": 5, "06": 6, "07": 7, "08": 8, "09": 9, "0A": 10, "0B": 11, "0C": 12, "0D": 13, "0E": 14, "0F": 15,
        "10": 16, "11": 17, "12": 18, "13": 19, "14": 20, "15": 21, "16": 22, "17": 23, "18": 24, "19": 25, "1A": 26, "1B": 27, "1C": 28, "1D": 29, "1E": 30, "1F": 31,
        "20": 32, "21": 33, "22": 34, "23": 35, "24": 36, "25": 37, "26": 38, "27": 39, "28": 40, "29": 41, "2A": 42, "2B": 43, "2C": 44, "2D": 45, "2E": 46, "2F": 47,
        "30": 48, "31": 49, "32": 50, "33": 51, "34": 52, "35": 53, "36": 54, "37": 55, "38": 56, "39": 57, "3A": 58, "3B": 59, "3C": 60, "3D": 61, "3E": 62, "3F": 63,
        "40": 64, "41": 65, "42": 66, "43": 67, "44": 68, "45": 69, "46": 70, "47": 71, "48": 72, "49": 73, "4A": 74, "4B": 75, "4C": 76, "4D": 77, "4E": 78, "4F": 79,
        "50": 80, "51": 81, "52": 82, "53": 83, "54": 84, "55": 85, "56": 86, "57": 87, "58": 88, "59": 89, "5A": 90, "5B": 91, "5C": 92, "5D": 93, "5E": 94, "5F": 95,
        "60": 96, "61": 97, "62": 98, "63": 99, "64": 100, "65": 101, "66": 102, "67": 103, "68": 104, "69": 105, "6A": 106, "6B": 107, "6C": 108, "6D": 109, "6E": 110, "6F": 111,
        "70": 112, "71": 113, "72": 114, "73": 115, "74": 116, "75": 117, "76": 118, "77": 119, "78": 120, "79": 121, "7A": 122, "7B": 123, "7C": 124, "7D": 125, "7E": 126, "7F": 127,
        "80": 128, "81": 129, "82": 130, "83": 131, "84": 132, "85": 133, "86": 134, "87": 135, "88": 136, "89": 137, "8A": 138, "8B": 139, "8C": 140, "8D": 141, "8E": 142, "8F": 143,
        "90": 144, "91": 145, "92": 146, "93": 147, "94": 148, "95": 149, "96": 150, "97": 151, "98": 152, "99": 153, "9A": 154, "9B": 155, "9C": 156, "9D": 157, "9E": 158, "9F": 159,
        "A0": 160, "A1": 161, "A2": 162, "A3": 163, "A4": 164, "A5": 165, "A6": 166, "A7": 167, "A8": 168, "A9": 169, "AA": 170, "AB": 171, "AC": 172, "AD": 173, "AE": 174, "AF": 175,
        "B0": 176, "B1": 177, "B2": 178, "B3": 179, "B4": 180, "B5": 181, "B6": 182, "B7": 183, "B8": 184, "B9": 185, "BA": 186, "BB": 187, "BC": 188, "BD": 189, "BE": 190, "BF": 191,
        "C0": 192, "C1": 193, "C2": 194, "C3": 195, "C4": 196, "C5": 197, "C6": 198, "C7": 199, "C8": 200, "C9": 201, "CA": 202, "CB": 203, "CC": 204, "CD": 205, "CE": 206, "CF": 207,
        "D0": 208, "D1": 209, "D2": 210, "D3": 211, "D4": 212, "D5": 213, "D6": 214, "D7": 215, "D8": 216, "D9": 217, "DA": 218, "DB": 219, "DC": 220, "DD": 221, "DE": 222, "DF": 223,
        "E0": 224, "E1": 225, "E2": 226, "E3": 227, "E4": 228, "E5": 229, "E6": 230, "E7": 231, "E8": 232, "E9": 233, "EA": 234, "EB": 235, "EC": 236, "ED": 237, "EE": 238, "EF": 239,
        "F0": 240, "F1": 241, "F2": 242, "F3": 243, "F4": 244, "F5": 245, "F6": 246, "F7": 247, "F8": 248, "F9": 249, "FA": 250, "FB": 251, "FC": 252, "FD": 253, "FE": 254, "FF": 255 };
        
    this.onBundleAttached = [];
    this.onInteropLoaded = [];
};

/*!
* releases the host
*/
Host.prototype.release = function() {
    if (this.skinWindow !== null) {
        this.skinWindow.release();
        this.skinWindow = null;
    }

    if (this.app !== null) {
        this.app.release();
        this.app = null;
    }
};

/*!
* initializes the host
*/
Host.prototype.init = function(skinWindow) {
    var self;

    if (this.skinWindow !== null || this.app !== null) {
        throw "Host already initialized";
    }

    self = this;

    this.app = createApp();
    this.app.onBundleAttached = function(info) {
        self.internalRaiseBundleAttached(info);
    };
    this.app.onInteropLoaded = function(info) {
        self.internalRaiseInteropLoaded(info);
    };
    
    this.skinWindow = createSkinWindow();
    
};

Host.prototype.internalRaiseEvent = function(event, info) {
    event.forEachReverse(function(handler) {
        if (handler !== null) {
            handler(info);
        }
    });
};

Host.prototype.internalRaiseBundleAttached = function(info) {
    this.internalRaiseEvent(this.onBundleAttached, info);
};

Host.prototype.internalRaiseInteropLoaded = function(info) {
    this.internalRaiseEvent(this.onInteropLoaded, info);
};

/*!
* subscribe to the BundleAttached event
* \tparam event handler callback function for BundleAttached event
*/
Host.prototype.addBundleAttachedEventHandler = function(handler) {
    this.onBundleAttached.push(handler);
};

/*!
* unsubscribe from the BundleAttached event
* \tparam event handler callback function for BundleAttached event
*/
Host.prototype.removeBundleAttachedEventHandler = function(handler) {
    this.onBundleAttached.removeElement(handler);
};

/*!
* subscribe to the InteropLoaded event
* \tparam event handler callback function for InteropLoaded event
*/
Host.prototype.addInteropLoadedEventHandler = function(handler) {
    this.onInteropLoaded.push(handler);
};

/*!
* unsubscribe from the InteropLoaded event
* \tparam event handler callback function for InteropLoaded event
*/
Host.prototype.removeInteropLoadedEventHandler = function(handler) {
    this.onInteropLoaded.removeElement(handler);
};

/*!
* elevates the host
*/
Host.prototype.elevate = function() {
    if (this.app.getElevated() === false) {
        this.app.setRestartElevated(true);
        this.app.setRestart(true);
        return true;
    }

    return false;
};

/*!
* creates an id from a string
* \tparam string str string to create id from
* \treturn string id created from string
*/
Host.prototype.idFromString = function(str) {
    return host.app.expandString("{SHA1:" + str + "}");
};

/*!
* converts a url to a filename in the specified directory
* \tparam string url url to convert
* \tparam string directory output directory
* \tparam string extension extension of filename
* \treturn string path to file
*/
Host.prototype.urlToFileName = function(url, directory, extension) {
    var fileName;
    fileName = url.replace(
        host.app.expandString("{ContentUrl}"),
        host.app.expandString("{ModuleFileName}\\")
        );
    fileName = host.app.expandString(directory + "{SHA1:" + fileName.toLowerCase() + "}" + extension);
    return fileName;
};

/*!
* decode a hex string
* \tparam string str string to decode
*/
Host.prototype.decodeHex = function(str) {
    var i, n, result = "", nextchar = "";
    str = str.toUpperCase().replace(new RegExp("s/[^0-9A-Z]//g"));
    for (i=0; i<str.length; i++){
        nextchar += str.charAt(i);
        if (nextchar.length == 2){
            n = (this.hexTable[nextchar]).toString(16);
            if (n.length == 1) {
                n = "0" + n;
            }
            result += unescape("%" + n);
            nextchar = "";
        }
    }
    return result;
};

/*!
* gets a JSON object from a url
* \tparam string url url of json object
* \tparam event completeCallback called when function is complete with json object as parameter
*/
Host.prototype.getJSON = function(url, completeCallback) {
    this.downloadContent(url, null, function(info) { 
        if (info.successful == false) {
            completeCallback(null);
            return;
        }
        
        completeCallback(JSON.parse(info.content));
    });
};

/*!
* dynamically load javascript files from url 
* \tparam string url url of javascript
* \tparam event completeCallback called when function is complete with successful parameter
*/
Host.prototype.loadJS = function(url, completeCallback) {
    var headID, newScript, done;

    headID = document.getElementsByTagName("head")[0];
    newScript = document.createElement("script");
    newScript.type = "text/javascript";
    newScript.src = encodeURI(url);

    done = false;
    newScript.onload = newScript.onreadystatechange = function() {
        if (!done && (!this.readyState
                || this.readyState === "loaded"
                || this.readyState === "complete")) {
            done = true;

            if (completeCallback !== null) {
                completeCallback({ "successful": true });
            }

            // Handle memory leak in IE
            newScript.onload = newScript.onreadystatechange = null;
            headID.removeChild(newScript);
        }
    };

    headID.appendChild(newScript);
};

/*!
* dynamically load CSS files from url 
* \tparam string url url of CSS
* \tparam event completeCallback called when function is complete with successful parameter
*/
Host.prototype.loadCSS = function(url, completeCallback) {
    var head, link, sheet, cssRules, intervalId, timeoutId;
    
    head = document.getElementsByTagName("head")[0];
    link = document.createElement("link");
    link.rel = "stylesheet";
    link.type = "text/css";
    link.href = encodeURI(url);
    
    if ("sheet" in link) {
        sheet = "sheet"; cssRules = "cssRules";
    } else {
        sheet = "styleSheet"; cssRules = "rules";
    }

    intervalId = setInterval(function() {
        try {
            if (link[sheet] && link[sheet][cssRules].length) {
                clearInterval(intervalId);
                clearTimeout(timeoutId);
                if (completeCallback !== null) {
                    completeCallback({ "successful": true });
                }
            }
        } catch(e) {} finally {}
    }, 10),
    timeoutId = setTimeout(function() {
        clearInterval(intervalId);
        clearTimeout(timeoutId);
        head.removeChild(link);
        if (completeCallback !== null) {
            completeCallback({ "successful": false });
        }
    }, 1500);

    head.appendChild(link);
};

/*!
* dynamically load javascript files from url 
* \tparam array urls array of urls for javascript files
* \tparam event completeCallback called when function is complete with successful parameter
*/
Host.prototype.loadJSArray = function(urls, completeCallback) {
    var itemsLoaded, itemsComplete;

    itemsLoaded = 0;

    itemsComplete = function(info) {
        ++itemsLoaded;
        if (itemsLoaded === urls.length) {
            if (completeCallback !== null) {
                completeCallback({ "successful": true });
            }
        }
    };

    urls.forEach(function(url) {
        host.loadJS(url, itemsComplete);
    });
};

/*!
* load bundles from url containing json file
* \tparam string url url of json object containing bundle information
* \tparam event statusCallback called when function changes status with name and state parameters
* \tparam event progressCallback called when function changes progress with percent parameter
* \tparam event completeCallback called when function is complete with successful parameter
*/
Host.prototype.loadBundles = function(url, statusCallback, progressCallback, completeCallback) {
    var onBundleList, numberOfBundlesLoaded, numberOfBundles, urlList, nameList, bundle, bundleLoader, loadNextBundle, bundleKeys;

    onBundleList = function(bundleList) {
        if (bundleList === null) {
            if (completeCallback !== null) {
                completeCallback({ "successful": false });
            }
        }

        numberOfBundlesLoaded = 0;
        numberOfBundles = 0;
        urlList = [];
        nameList = [];
        
        bundleKeys = getObjectProperties(bundleList);
        bundleKeys.forEach(function(bundleName) {
            bundle = bundleList[bundleName];
            nameList[numberOfBundles] = bundleName;
            urlList[numberOfBundles] = bundle.url;
            ++numberOfBundles;
        });

        if (progressCallback !== null) {
            progressCallback({ "percent": 0.0, "numberOfBundlesLoaded": numberOfBundlesLoaded, "numberOfBundles": numberOfBundles });
        }
                
        loadNextBundle = function() {
            bundleLoader = createBundleLoader();
            bundleLoader.name = nameList[numberOfBundlesLoaded];
            bundleLoader.url = host.app.expandString(urlList[numberOfBundlesLoaded]);

            bundleLoader.onStateChange = function(info) {
                if (statusCallback !== null) {
                    statusCallback({ "name": nameList[numberOfBundlesLoaded], "state": info.state });
                }
            };

            bundleLoader.onProgress = function(info) {
                if (progressCallback !== null) {
                    progressCallback({ "percent": info.percent, "numberOfBundlesLoaded": numberOfBundlesLoaded, "numberOfBundles": numberOfBundles });
                }
            };

            bundleLoader.onComplete = function(info) {
                if (info.successful === false) {
                    completeCallback(info);
                    return;
                }
                if (progressCallback !== null) {
                    progressCallback({ "percent": 1.0, "numberOfBundlesLoaded": numberOfBundlesLoaded, "numberOfBundles": numberOfBundles });
                }            
                ++numberOfBundlesLoaded;
                if (numberOfBundlesLoaded === numberOfBundles) {
                    if (completeCallback !== null) {
                        completeCallback(info);
                    }
                } else {
                    loadNextBundle(numberOfBundlesLoaded);
                }
            };

            bundleLoader.start();
        };

        loadNextBundle();
    };

    host.getJSON(url, onBundleList);
};

/*!
* dynamically retrieve content using httpDownload
* \tparam string url url of the content to retrieve
* \tparam event progressCallback called while downloading with percent downloading
* \tparam event completeCallback called when function is complete with successful parameter
*/
Host.prototype.downloadContent = function(url, progressCallback, completeCallback) {
    var attempt = 0, tryDownload;

    tryDownload = function() {
        var hexString = "";
        var httpDownload = createHttpDownload();

        attempt += 1;
        
        httpDownload.setRetryCount(1);
        httpDownload.setUrl(url);
        httpDownload.setUseCache(false);
        httpDownload.setUseWriteCallback(true);
        httpDownload.onProgress = progressCallback;
        httpDownload.onWrite = function(info) {
            hexString += info.buffer;
            return true;
        };
        httpDownload.onComplete = function(info) {
            if (completeCallback != null) {
                completeCallback({"successful": info.successful, "download": httpDownload, "content": host.decodeHex(hexString), "retry": function() { tryDownload(); }, "attempt": attempt});
            }
            this.release();
        };
        httpDownload.start();
    };
    tryDownload();
};

/*!
* load language JS
* \tparam string url app content url to language files
* \tparam event completeCallback called when function is complete with successful parameter
*/
Host.prototype.loadLanguage = function(url, completeCallback) {
    var successful = false;
    var onLanguageLoaded = function(info) {
        var languageUrl, skip = false;
        if ((info.successful === true) && (typeof LocalLanguage != 'undefined') && (LocalLanguage != null)) {
            mergeObjectProperties(Language, LocalLanguage);
            successful = true;
        } else if ((info.hasOwnProperty("skip") === false) || (info.skip === false)) {
            languageUrl = host.app.expandString(url + "language-{UserISO639LangName}.js").toLowerCase();
            if (info.hasOwnProperty("url") === true) {
                if (info.url === languageUrl) {
                    languageUrl = host.app.expandString(url + "language-{UserISO3166CountryName}.js").toLowerCase();
                    skip = true;
                }
            }
            host.loadJS(languageUrl, function(info) {
                onLanguageLoaded({ "successful": info.successful, "skip": skip, "url": languageUrl });
            });
            return;
        }
        if (completeCallback != null) {
            completeCallback({ "successful": successful });
        }
    };
        
    host.loadJS(host.app.expandString(url + "language-{UserISO639LangName}-{UserISO3166CountryName}.js").toLowerCase(), onLanguageLoaded);
};

/*!
* precreated global instance of the host
* \type Host
*/
var host = new Host();
