/*!
* \file bundleloader.js
* \brief File containing BundleLoader class and creation function
*/

/*!
* \class BundleLoader
* \brief Helper class to load bundles from JSON file
*/

function BundleLoader() {
   /*!
   * Triggered when the bundle loader has made progress.
   * \type event
   * \tparam double percent (-1.0: Still calculating) (0.0 to 1.0: Percent completed)
   */
    this.onProgress = null;
   /*!
   * Triggered when the bundle loader is complete.
   * \type event
   * \tparam bool successful true if the download was successful, false otherwise.
   */
    this.onComplete = null;
   /*!
   * Name of the bundle in the {LocalStorage} directory
   * \type string
   */
    this.name = "";
   /*!
   * Url location of the bundle
   * \type string
   */
    this.url = "";
}

BundleLoader.prototype.internalRaiseStateChange = function(state) {
    if (this.onStateChange !== null) {
        this.onStateChange({ "state": state });
    }
};

BundleLoader.prototype.internalRaiseProgress = function(percent) {
    if (this.onProgress !== null) {
        this.onProgress({ "percent": percent });
    }
};

BundleLoader.prototype.internalRaiseComplete = function(successful, exitCode) {
    if (successful === true) {
        this.internalRaiseStateChange("Complete");
    } else {
        this.internalRaiseStateChange("Failed");
    }

    if (this.onComplete !== null) {
        this.onComplete({ "successful": successful, "exitCode": exitCode });
    }
};

BundleLoader.prototype.internalDownload = function() {
    var self, path, httpDownload;

    self = this;
    path = host.app.expandString("{LocalStorage}" + this.name + ".bundle");

    httpDownload = createHttpDownload();
    httpDownload.setFileName(path);
    httpDownload.setUrl(this.url);
    httpDownload.setUseCache(true);

    httpDownload.onDownloadRequired = function(info) {
        self.internalRaiseStateChange("Downloading");
    };

    httpDownload.onProgress = function(info) {
        self.internalRaiseProgress(info.percent);
    };

    httpDownload.onComplete = function(info) {
        var exitCode = httpDownload.getExitCode();
        self.internalRaiseProgress(1.0);
        httpDownload.release();

        if (info.successful === true) {
            self.url = path;
            self.internalAttach();
        } else {
            self.internalRaiseComplete(false, exitCode);
        }
    };

    httpDownload.start();
};

BundleLoader.prototype.internalLoadExtract = function(extractFiles, completeCallback) {
    var len, numFilesLoaded, loadCompleteCallback, fileName, url, httpDownload, loadNext, self;

    self = this;
    if (extractFiles !== null) {
        len = extractFiles.length;
        numFilesLoaded = 0;

        loadNext = function() {
            fileName = host.app.expandString("{LocalStorage}") + extractFiles[numFilesLoaded];
            url = host.app.expandString("{ContentUrl}") + self.name + "/" + extractFiles[numFilesLoaded];

            httpDownload = createHttpDownload();
            httpDownload.setFileName(fileName);
            httpDownload.setUrl(url);
            httpDownload.setUseCache(true);
            httpDownload.onComplete = loadCompleteCallback;
            httpDownload.start();
        };

        loadCompleteCallback = function(info) {
            if (info.successful === false) {
                completeCallback(info);
            } else {
                ++numFilesLoaded;
                if (numFilesLoaded === len) {
                    completeCallback(info);
                } else {
                    loadNext();
                }
            }

            this.release();
        };

        if (len === 0) {
            completeCallback({ "successful": true });
        } else {
            loadNext();
        }
    } else {
        completeCallback({ "successful": false });
    }
};

BundleLoader.prototype.internalLoadInterop = function(interopFiles, completeCallback) {
    var len, numFilesLoaded, fileName, loadCompleteCallback, loadNext;

    if (interopFiles !== null) {
        numFilesLoaded = 0;
        len = interopFiles.length;

        loadNext = function() {
            fileName = host.app.expandString("{LocalStorage}") + interopFiles[numFilesLoaded];

            host.addInteropLoadedEventHandler(loadCompleteCallback);
            host.app.loadInterop(fileName);
        };

        loadCompleteCallback = function(info) {
            if (info.successful === false) {
                completeCallback(info);
            } else {
                ++numFilesLoaded;
                if (numFilesLoaded === len) {
                    completeCallback(info);
                } else {
                    loadNext();
                }
            }

            host.removeInteropLoadedEventHandler(loadCompleteCallback);
        };

        if (len === 0) {
            completeCallback({ "successful": true });
        } else {
            loadNext();
        }
    } else {
        completeCallback({ "successful": false });
    }
};

BundleLoader.prototype.internalLoadManifest = function() {
    var self, manifestUrl, interopComplete, extractComplete, jsComplete, javascriptFiles;
    self = this;
    manifestUrl = "/" + this.name + "/manifest.json";

    self.internalRaiseStateChange("Loading");

    host.getJSON(manifestUrl,
        function(manifestData) {
            if (manifestData !== null) {
                interopComplete = function(info) {
                    self.internalRaiseComplete(info.successful, null);
                };

                extractComplete = function(info) {
                    if (info.successful === true) {
                        self.internalLoadInterop(manifestData.register, interopComplete);
                    } else {
                        self.internalRaiseComplete(false, null);
                    }
                };

                jsComplete = function(info) {
                    if (info.successful === true) {
                        self.internalLoadExtract(manifestData.extract, extractComplete);
                    } else {
                        self.internalRaiseComplete(false, null);
                    }
                };

                javascriptFiles = [];

                Array.forEach(manifestData.javascript, function(fileName) {
                    javascriptFiles.push("/" + self.name + "/" + fileName);
                });

                host.loadJSArray(javascriptFiles, jsComplete);
            } else {
                self.internalRaiseComplete(false, null);
            }
        }
    );
};

BundleLoader.prototype.internalAttach = function() {
    var path, self, attachedEventHandler;

    path = host.app.expandString("{LocalStorage}" + this.name + ".bundle");
    self = this;
    
    attachedEventHandler = function(info) {
        if (self.name === info.bundleName) {
            if (info.successful === true) {
                self.internalLoadManifest();
            } else {
                self.internalRaiseComplete(false, null);
            }

            host.removeBundleAttachedEventHandler(attachedEventHandler);
        }
    };

    host.addBundleAttachedEventHandler(attachedEventHandler);
    host.app.attachBundle(this.name, path);
};

/*!
* starts the bundle loader
*/
BundleLoader.prototype.start = function() {
    var self, hasBundle;

    self = this;
    hasBundle = host.app.hasBundle(this.name);

    if (hasBundle === true) {
        this.internalLoadManifest();
        return;
    }

    this.internalDownload();
};

/*!
* Create instance of bundle loader
*/
function createBundleLoader() {
   return new BundleLoader();
}
