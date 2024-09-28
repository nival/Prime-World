function Repair() {
    this.onProgress = null;
    this.onComplete = null;
    this.verifying = false;
}

Repair.prototype.internalRaiseProgress = function(info) {
    if (this.onProgress !== null) {
        this.onProgress(info);
    }
};

Repair.prototype.internalRaiseComplete = function(info) {
    this.verifying = false;
    
    if (this.onComplete !== null) {
        this.onComplete(info);
    }
};

Repair.prototype.repairByIndex = function(manifestUrl, corruptFiles, x) {
    var patchManifestItem, manifestComplete, self;

    self = this;
    
    patchManifestItem = patchManager.repairPatchManifest(manifestUrl, corruptFiles);

    manifestComplete = function(info) {
        if (patchManifestItem.id !== info.patchManifestId) {
            return;
        }

        self.internalRaiseProgress({ "percent": -1.0 });

        if (info.successful === true) {
            self.verifyByIndex(true, x + 1);
        } else {
            info.lastError = patchManifestItem.patchManifest.getLastError();
            self.internalRaiseComplete(info);
        }

        patchManager.removeManifestCompleteEventHandler(manifestComplete);
    };

    patchManager.addManifestCompleteEventHandler(manifestComplete);
    patchManifestItem.patchManifest.start();
};

Repair.prototype.verifyByIndex = function(quickScan, x) {
    var props, len, verifyComplete, patchManifestId, self;

    self = this;
    props = getObjectProperties(patchManager.patchManifests);
    len = props.length;

    if (x < len) {
        patchManifestId = props[x];
        verifyComplete = function(info) {
            if (patchManifestId !== info.patchManifestId) {
                return;
            }

            if (info.successful === true && info.corruptFiles.length > 0) {
                self.repairByIndex(info.patchManifest.getUrl(), info.corruptFiles, x);
            } else if (info.successful === true) {
                self.verifyByIndex(quickScan, x + 1);
            } else {
                self.internalRaiseComplete({ "successful": false, "lastError": patchManifestError.NONE });
            }

            patchManager.removeManifestVerifyCompleteEventHandler(verifyComplete);
        };
        patchManager.addManifestVerifyCompleteEventHandler(verifyComplete);

        patchManager.verifyManifestById(patchManifestId, quickScan);
    } else {
        this.internalRaiseComplete({ "successful": true, "lastError": patchManifestError.NONE });
    }
};

Repair.prototype.startVerify = function(quickScan) {
    if (this.verifying === true) {
        return;
    }
    
    this.verifying = true;

    this.verifyByIndex(quickScan, 0);
};

var repair = new Repair();
