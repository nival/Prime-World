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
    if (this.skinWindow !== null || this.app !== null) {
        throw "Host already initialized";        
    }

    this.skinWindow = createSkinWindow();
    this.app = createApp();
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
    fileName = host.app.expandString(directory + "{SHA1:" + fileName + "}" + extension);
    return fileName;
};

/*!
* gets a JSON object from a url
* \tparam string url url of json object
* \tparam event completeCallback called when function is complete with json object as parameter
*/
Host.prototype.getJSON = function(url, completeCallback) {
    var httpRequest;
    httpRequest = new XMLHttpRequest();
    httpRequest.open("GET", url, true);
    httpRequest.onreadystatechange = function() {
        if (httpRequest.readyState === 4) {
            if (httpRequest.status === 200) {
                completeCallback(JSON.parse(httpRequest.responseText));
            } else {
                completeCallback(null);
            }
        }
    };

    httpRequest.send(null);
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

    Array.forEach(urls, function(url) {
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

        Array.forEach(bundleKeys, function(bundleName) {
            bundle = bundleList[bundleName];
            nameList[numberOfBundles] = bundleName;
            urlList[numberOfBundles] = bundle.url;
            ++numberOfBundles;
        });

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
                    completeCallback({ "successful": false });
                    return;
                }

                ++numberOfBundlesLoaded;
                if (numberOfBundlesLoaded === numberOfBundles) {
                    if (completeCallback !== null) {
                        completeCallback({ "successful": true });
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
* precreated global instance of the host
* \type Host
*/
var host = new Host();
