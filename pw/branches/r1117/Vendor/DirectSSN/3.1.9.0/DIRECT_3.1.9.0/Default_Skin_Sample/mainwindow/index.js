var downloadManager = null;
var patchManager = null;
var bundlesLoaded = false;
var rootManifestUrl = "";
var failureString = "";
var verifying = false;
var settings = {
    "httpEnabled": true,
    "p2pEnabled": true,
    "downloadRate": 0,
    "uploadRate": 0,
    "upcomingPatchDownload": "stop"
};
var retryInterval = 0;
var IndefiniteProgressAnim = createPngAnim();
var tabHeader = null;
var tabContent = null;
var selectedTab = null;
var numGraphPoints = 40;
var incomingGraph;
var outgoingGraph;
var maxIncomingGraph = 0;
var maxOutgoingGraph = 0;
var incomingGraphData = [];
var outgoingGraphData = [];
var graphOptions = {
    grid: { borderWidth: 0 },
    series: { shadowSize: 0 }, 
    yaxis: { min: 0, max: 1 },
    xaxis: { show: false, min: 0, max: numGraphPoints, alignTicksWithAxis: 1 }
};

function getGraphData(list, max) {
    var res = [];
    var i = 0;
    var x = 0;

    max = Math.max(max, 1);

    for (i = 0; i < numGraphPoints - list.length; ++i) {
        res.push([i, 0]);
    }

    for (x = 0; x < list.length; ++x) {
        res.push([i, list[x] / max]);
        ++i;
    }

    return res;
}


function getTimeEstimateMessage(estimatedSeconds) {
    var oneSecond = 1;
    var oneMinute = oneSecond * 60;
    var oneHour = oneMinute * 60;
    var oneDay = oneHour * 24;

    if (estimatedSeconds < 0) {
        return Language.EstimatingTime;
    }

    if (estimatedSeconds < oneMinute) {
        return Language.ShortTimeLeft;
    }

    if (estimatedSeconds > 7 * oneDay) {
        return Language.LongTimeLeft;
    }

    var timeEstimateString = "";

    var days = (estimatedSeconds / oneDay).toString().split(".")[0];
    estimatedSeconds -= days * oneDay;
    if (days > 0) {
        timeEstimateString += " " + days + Language.DayAbbreviation;
    }

    var hours = (estimatedSeconds / oneHour).toString().split(".")[0];
    estimatedSeconds -= hours * oneHour;
    if (hours > 0) {
        timeEstimateString += " " + hours + Language.HourAbbreviation;
    }

    var minutes = (estimatedSeconds / oneMinute).toString().split(".")[0];
    estimatedSeconds -= minutes * oneMinute;
    if (minutes > 0) {
        timeEstimateString += " " + minutes + Language.MinuteAbbreviation;
    }

    if (timeEstimateString.length > 0)
        return timeEstimateString + " " + Language.Left;

    return Language.EstimatingTime;
}

function getTransferSpeedMessage(speed) {
    var speedKBps = speed / 1024;
    if (speedKBps <= 0.1) {
        return "0.0 " + Language.SpeedKB;
    }

    var speedMBps = speedKBps / 1024;
    if (speedMBps > 1.0) {
        return speedMBps.toFixed(2) + " " + Language.SpeedMB;
    }

    return speedKBps.toFixed(2) + " " + Language.SpeedKB;
}

function getBytesLeftMessage(bytesLeft) {
    downloadBytesLeft = Number(bytesLeft);
    var mbLeft = (downloadBytesLeft / (1024 * 1024));
    return mbLeft.toFixed(2) + " " + Language.BytesLeft;
}

function getLanguageString(str) {
    if (Language.hasOwnProperty(str) == false) {
        return str;
    }

    return Language[str];
}

function onConstructWebGetTarget(info) {
    return info.url;
}
/* QA CDN authentication code (replace function above with this one)

function onConstructWebGetTarget(info) {
	if (info.url.match("http://hwcdn.net/*")) {
	info.url += "?e={Add:{Time60},600}{Copy:&t={MD5:{ThisUrlPath}&s=s0e0}}";
	}
	if (info.url.match("http://llnwpp.vo.llnwd.net/*")) {
	info.url += "?e={Add:60,{Time}}{Copy:&h={MD5:llnw2010{This}}}";
	}
	if (info.url.match("http://vhost1.solidstatenetworks.net/*")) {
	info.url += "?nva={TimeStamp:{Add:{Time},600}}{Copy:&hash=0{Limit:20,{HMACSHA1:H#ahfsl1D!eI*fhZPa,{This}}}}";
	}
	return info.url;
}
*/

function repairManifestByIndex(manifestUrl, corruptFiles, x) {
    var patchManifestItem, manifestComplete;

    patchManifestItem = patchManager.repairPatchManifest(manifestUrl, corruptFiles);

    manifestComplete = function(info) {
        if (patchManifestItem.id !== info.patchManifestId) {
            return;
        }

        onProgress({ "percent": -1.0 });

        if (info.successful == true) {
            verifyManifestByIndex(false, x + 1);
        } else {
            verifyManifestComplete(info.successful, patchManifestItem.patchManifest.getLastError());
        }

        patchManager.removeManifestCompleteEventHandler(manifestComplete);
    };

    patchManager.addManifestCompleteEventHandler(manifestComplete);
    patchManifestItem.patchManifest.start();
}

function verifyManifestComplete(successful, lastError) {
    updateCompleteStatus(successful, lastError);
    verifying = false;

    if (successful == true) {
        // check for latest updates
        addPatchManifest(rootManifestUrl);
    }
}

function verifyManifestByIndex(quickScan, x) {
    var props, len, verifyComplete, patchManifestId;

    props = getObjectProperties(patchManager.patchManifests);
    len = props.length;

    if (x < len) {
        patchManifestId = props[x];
        verifyComplete = function(info) {
            if (patchManifestId !== info.patchManifestId) {
                return;
            }

            if (info.successful == true && info.corruptFiles.length > 0) {
                repairManifestByIndex(info.patchManifest.getUrl(), info.corruptFiles);
            } else if (info.successful == true) {
                verifyManifestByIndex(quickScan, x + 1);
            } else {
                verifyManifestComplete(false, patchManifestError.NONE);
            }

            patchManager.removeManifestVerifyCompleteEventHandler(verifyComplete);
        };
        patchManager.addManifestVerifyCompleteEventHandler(verifyComplete);
        
        patchManager.verifyManifestById(patchManifestId, quickScan);
    } else {
        verifyManifestComplete(true, patchManifestError.NONE);
    }
};

function verifyManifests(quickScan) {
    verifying = true;
    
    setLaunchVisible(false);
    setVerifyVisible(false);

    failureString = "";

    verifyManifestByIndex(quickScan, 0);
};

function addPatchManifest(manifestUrl) {
    var manifestComplete;

    failureString = "";

    setLaunchVisible(false);
    setVerifyVisible(false);

    patchManifestItem = patchManager.addPatchManifest(manifestUrl);

    manifestComplete = function(info) {
        var lastError;

        lastError = info.patchManifest.getLastError();

        if (patchManifestItem.id !== info.patchManifestId) {
            if (info.successful === false) {
                if (lastError !== patchManifestError.NONE && lastError !== patchManifestError.USERFAIL) {
                    updateStatusText(getLanguageString("PatchManifestError_" + patchManifestError.nameFromId(lastError)));
                }
            }
            return;
        }

        if (verifying == true) {
            return;
        }

        onProgress({ "percent": -1.0 });

        updateCompleteStatus(info.successful, lastError);
    };

    patchManager.addManifestCompleteEventHandler(manifestComplete);

    patchManifestItem.patchManifest.setRetryInterval(retryInterval);
    patchManifestItem.patchManifest.start();
}

function onPatcherStart() {
    var fileName, updateConnectionSettings, fileAttempt;

    rootManifestUrl = host.app.getConfig("TargetUrl", "");
    if (rootManifestUrl.length == 0) {
        updateStatusText("Target URL not found");
        return;
    }

    retryInterval = parseInt(host.app.getConfig("RetryInterval", "3600"), 10); // 1 hour default

    updateConnectionSettings = function(info, force) {
        if (info.hasOwnProperty("download") === true) {
            if (info.download.getActive() === true || force === true) {
                if (info.download.getWebActive() != settings.httpEnabled) {
                    info.download.setWebActive(settings.httpEnabled);
                }

                if (info.download.getBitActive() != settings.p2pEnabled) {
                    info.download.setBitActive(settings.p2pEnabled);
                }
            }
        }
    }

    downloadManager.addDownloadConfigCompleteEventHandler(function(info) {
        updateConnectionSettings(info, true);
    });

    downloadManager.addDownloadProgressEventHandler(function(info) {
        updateConnectionSettings(info, false);

        switch (info.download.getState()) {
            case downloadState.UNKNOWN:
            case downloadState.COMPLETE:
            case downloadState.SEED:
            case downloadState.FAILURE:
            case downloadState.IDLE:
            case downloadState.PAUSE:
            case downloadState.STOP:
            case downloadState.DOWNLOADSTALLED:
                return;
        }

        onProgress(info);

        updateTimeEstimate(getTimeEstimateMessage(info.download.getRemainingTime()));
        updateDeliveryMethod(info.download.getConnectivity());
        updateBytesLeft(getBytesLeftMessage(info.download.getBytesLeft()));

        var rates = JSON.parse(info.download.getTransferRates());
        updateAverageIncomingSpeed(rates.incoming.average);
        updateTransferSpeed(rates.incoming.average);
        updateCurrentIncomingSpeed(rates.incoming.current);
        updateMaxIncomingSpeed(rates.incoming.max);
        updateAverageOutgoingSpeed(rates.outgoing.average);
        updateCurrentOutgoingSpeed(rates.outgoing.current);
        updateMaxOutgoingSpeed(rates.outgoing.max);
        updateGraphs(rates.incoming.current, rates.outgoing.current);
    });

    downloadManager.addDownloadStateChangeEventHandler(function(info) {
        var failureReason;

        switch (info.state) {
            case downloadState.SEED:
                // Do nothing
                break;

            case downloadState.DOWNLOADSTALLED:
                failureReason = info.download.getLastFailure();
                if (failureReason > downloadFailure.NONE) {
                    updateStatusText(getLanguageString("DownloadFailure_" + downloadFailure.nameFromId(failureReason)));
                } else {
                    updateStatusText(getLanguageString("DownloadState_" + downloadState.nameFromId(info.state)));
                }
                break;

            default:
                updateStatusText(getLanguageString("DownloadState_" + downloadState.nameFromId(info.state)));
                break;
        }

        switch (info.state) {
            case downloadState.UNKNOWN:
            case downloadState.COMPLETE:
            case downloadState.SEED:
            case downloadState.FAILURE:
            case downloadState.IDLE:
            case downloadState.START:
                setPauseResumeVisible(false);
                setDownloadVisible(false);
                break;

            case downloadState.PAUSE:
            case downloadState.STOP:
            case downloadState.DOWNLOADSTALLED:
                setPauseResumeVisible(true);
                setDownloadVisible(false);
                break;

            case downloadState.RESUME:
            case downloadState.CREATE:
            case downloadState.CHECK:
            case downloadState.DOWNLOADWITHCHECK:
            case downloadState.DOWNLOAD:
                setPauseResumeVisible(true);
                setDownloadVisible(true);
                break;
        }
    });

    patchManager.addManifestVerifyStartEventHandler(function(info) {
        updateStatusText(getLanguageString("PatchManifestState_Verify"));
        onProgress({ "percent": -1.0 });
    });

    patchManager.addManifestVerifyProgressEventHandler(function(info) {
        onProgress({ "percent": info.percent });
    });

    patchManager.addManifestRequiredCompleteEventHandler(function(info) {
        var rootManifest;

        rootManifest = patchManager.manifestById(host.idFromString(rootManifestUrl.toLowerCase()));
        
        setVerifyVisible(rootManifest !== null && rootManifest.getCurrentReleaseId() >= 0);
        setLaunchVisible(rootManifest !== null && rootManifest.getCurrentReleaseId() >= rootManifest.getRequiredReleaseId());
    });
    
    patchManager.addManifestStateChangeEventHandler(function(info) {
        if (info.state == patchManifestState.COMPLETE) {
            // Don"t show the complete message
            return;
        }

        updateStatusText(getLanguageString("PatchManifestState_" + patchManifestState.nameFromId(info.state)));
        onProgress({ "percent": -1.0 });
    });

    patchManager.addPatchDownloadErrorEventHandler(function(info) {
        updateStatusText(getLanguageString("DownloadError_" + downloadError.nameFromId(info.download.getLastError())));
    });

    patchManager.addPatchFileErrorEventHandler(function(info) {
        updateStatusText(getLanguageString("FileError_" + fileError.nameFromId(info.error)));
        if (info.error <= fileError.UNKNOWN) {
            // unknown failure, the repair will have to fix this
            info.patch.fail();
        } else {
            // retry in ten seconds
            setTimeout(function() { info.patch.resume(); }, 1000 * 10);
        }
    });

    patchManager.addPatchCorruptSourceFileEventHandler(function(info) {
        failureString = "FileError_CorruptSource";
        
        // No good fix for this one, the repair will have to pick it up
        info.patch.fail();
    });

    patchManager.addPatchCorruptDestFileEventHandler(function(info) {
        ++fileAttempt;
        if (fileAttempt <= 3) {
            info.patch.resume();
        } else {
            failureString = "FileError_CorruptDest";
            
            // i tried a couple times, now I'll fail
            info.patch.fail();
        }
    });

    patchManager.addPatchDidPatchFileEventHandler(function(info) {
        fileAttempt = 0;
    });

    patchManager.addPatchCompleteEventHandler(function(info) {
        info.download.eraseContent();
        downloadManager.removeDownload(info.downloadId);
    });

    patchManager.addPatchProgressEventHandler(function(info) {
        onProgress({ "percent": info.percent });

        if (info.percent >= 0) {
            setPerformanceVisible(true);

            updateTimeEstimate(getTimeEstimateMessage(info.patch.getRemainingTime()));
            updateBytesLeft(getBytesLeftMessage(info.patch.getBytesLeft()));

            var writeRates = JSON.parse(info.patch.getWriteRates());
            updateTransferSpeed(writeRates.average);
            updateAverageOutgoingSpeed(writeRates.average);
            updateCurrentOutgoingSpeed(writeRates.current);
            updateMaxOutgoingSpeed(writeRates.max);
            updateGraphs(0, writeRates.current);
        } else {
            setPerformanceVisible(false);
        }
    });

    addPatchManifest(rootManifestUrl);
}

function onBundlesLoaded() {
    var mode;

    downloadManager.init();

    bundlesLoaded = true;
    onPatcherStart();

    loadObjectFromFile(host.app.expandString("{SHA1:{ModuleFileName}}") + ".settings", function(info) {
        if (info.loadedObject != null) {
            mergeObjectProperties(settings, info.loadedObject);
            populateSettings();
            applySettings();
        }
    });
}

function onSkinLoaded() {
    // Disable selection on whole window
    document.onselectstart = function() { return false; };

    // Disable dragging on the whole window
    document.ondragstart = function() { return false; };

    host.init();

    host.app.onWillConstructWebGetTarget = onConstructWebGetTarget;

    host.skinWindow.onWillClose = function() {
        return true;
    }

    host.skinWindow.onDidClose = function() {
        if (downloadManager !== null) {
            downloadManager.release();
            downloadManager = null;
        }

        if (patchManager !== null) {
            patchManager.release();
            patchManager = null;
        }

        host.release();
        host = null;
    }

    host.app.info("Skin version: " + host.app.expandString("{SkinVersion}"));
	/* This tests passing command args through JS (use the alert only to display cmd args)
	alert(host.app.getCommandLine());
	if (host.app.getCommandLine().indexOf("/UserName") == -1)
	{
		host.app.setCommandLine(host.app.getCommandLine() + " /UserName");
		host.app.setRestart(true);
		return;
	}
	*/
    // Spool up the progress bar so the PNGs get loaded before the window is shown.
    onProgress({ "percent": -1.0 });

    initializeTabs();
    populateSettingsDefaults();
    populateDownloadOptions();
    populateUpcomingPatchSettings();
    populateSettings();
    setDownloadVisible(false);
    setPauseResumeVisible(false);
    setLaunchVisible(false);
    setVerifyVisible(false);

    incomingGraph = $.plot($("#incomingGraph"), [getGraphData(incomingGraphData, maxIncomingGraph)], graphOptions);
    outgoingGraph = $.plot($("#outgoingGraph"), [getGraphData(outgoingGraphData, maxOutgoingGraph)], graphOptions);

    host.skinWindow.show();
			// This tests using Gammy non-SSN certificate
            //host.app.loadInterop("c:\\temp\\downloader.dll");

            // This tests the canvas element (HTML5) make sure and uncomment the canvas test tag in the html
            //doCanvasTest(document.getElementById("canvasTest"));

    var bundleStatus = function(info) {
        updateStatusText(getLanguageString("PatchBundleState_" + info.state) + " " + getLanguageString("PatchBundleName_" + info.name));
    };

    var bundleProgress = function(info) {
        var completePercent = (((1 / info.numberOfBundles) * info.numberOfBundlesLoaded) + ((1 / info.numberOfBundles) * info.percent));
        onProgress({ "percent": completePercent });
    };

    var bundleComplete = function(info) {
        if (info.successful == true) {
            onBundlesLoaded();
        }
    };

    var bundleUrl = host.app.expandString("{AppContentUrl}bundles.json");
    host.loadBundles(bundleUrl, bundleStatus, bundleProgress, bundleComplete);
}

function populateDownloadOptions() {
    var optionalWebAllowed = host.app.getConfig("AllowWeb", "true").toLowerCase() === "true";
    var optionalP2PAllowed = host.app.getConfig("AllowP2P", "true").toLowerCase() === "true";

    var selbox = document.getElementById("downloadProtocols");

    if (optionalWebAllowed == true && optionalP2PAllowed == true) {
        selbox.options[selbox.options.length] = new Option("HTTP + P2P", "wp");
    }

    if (optionalWebAllowed == true) {
        selbox.options[selbox.options.length] = new Option("HTTP", "w");
    }

    if (optionalP2PAllowed == true) {
        selbox.options[selbox.options.length] = new Option("P2P", "p");
    }
}

function populateUpcomingPatchSettings() {
    var upcomingPatchesAllowed = host.app.getConfig("AllowUpcomingPatchDownloadConfiguration", "true").toLowerCase() === "true";
    var optionResume = host.app.getConfig("AllowUpcomingPatchDownloadResume", "true").toLowerCase() === "true";
    var optionContinue = host.app.getConfig("AllowUpcomingPatchDownloadContinue", "true").toLowerCase() === "true";
    var optionStop = host.app.getConfig("AllowUpcomingPatchDownloadStop", "true").toLowerCase() === "true";

    var selbox = document.getElementById("upcomingPatchDownload");

    if (upcomingPatchesAllowed == true) {
        selbox.options.length = 0;
    } else {
        document.getElementById("upcomingPatchDownload").disabled = true;
    }

    if (optionStop == true) {
        selbox.options[selbox.options.length] = new Option("Stop Download While Playing", "stop");
    }
    if (optionContinue == true) {
        selbox.options[selbox.options.length] = new Option("Continue Download While Playing", "continue");
    }
    if (optionResume == true) {
        selbox.options[selbox.options.length] = new Option("Resume Download After Playing", "resume");
    }
}

function applySettings() {
    var optionalWebAllowed = host.app.getConfig("AllowWeb", "true").toLowerCase() === "true";
    var optionalP2PAllowed = host.app.getConfig("AllowP2P", "true").toLowerCase() === "true";

    settings.httpEnabled = (optionalWebAllowed == true) && (document.getElementById("downloadProtocols").value.indexOf("w") != -1);
    settings.p2pEnabled = (optionalP2PAllowed == true) && (document.getElementById("downloadProtocols").value.indexOf("p") != -1);
    settings.uploadRate = parseInt(document.getElementById("maxUploadRate").value);
    settings.downloadRate = parseInt(document.getElementById("maxDownloadRate").value);
    settings.upcomingPatchDownload = document.getElementById("upcomingPatchDownload").value;

    if (downloadManager !== null) {
        downloadManager.downloader.setDownloadLimit(settings.downloadRate);
        downloadManager.downloader.setUploadLimit(settings.uploadRate);
    }
}

function populateSettingsDefaults() {
    settings.uploadRate = parseInt(host.app.getConfig("DefaultUploadRate", "0"), 10);
    settings.downloadRate = parseInt(host.app.getConfig("DefaultDownloadRate", "0"), 10);
    settings.httpEnabled = host.app.getConfig("DefaultWeb", "true").toLowerCase() === "true";
    settings.p2pEnabled = host.app.getConfig("DefaultP2P", "true").toLowerCase() === "true";
    settings.upcomingPatchDownload = host.app.getConfig("DefaultUpcomingPatchDownload", "stop").toLowerCase();
}

function populateSettings() {
    var optionalWebAllowed = host.app.getConfig("AllowWeb", "true").toLowerCase() === "true";
    var optionalP2PAllowed = host.app.getConfig("AllowP2P", "true").toLowerCase() === "true";

    var downloadSettings = "";

    if (settings.httpEnabled === true && optionalWebAllowed == true) {
        downloadSettings += "w";
    }
    if (settings.p2pEnabled === true && optionalP2PAllowed == true) {
        downloadSettings += "p";
    }

    document.getElementById("downloadProtocols").value = downloadSettings;
    document.getElementById("maxUploadRate").value = settings.uploadRate;
    document.getElementById("maxDownloadRate").value = settings.downloadRate;
    document.getElementById("upcomingPatchDownload").value = settings.upcomingPatchDownload;
}

function launch() {

    var process = createProcess();
    if (settings.upcomingPatchDownload != "stop") {
        process.onExit = function(info) {
            if (settings.upcomingPatchDownload == "resume") {
                downloadManager.setAllDownloadsActive(true);
            }

            host.skinWindow.restore();

            this.release();
        };
    }

    var applicationName = host.app.expandString(host.app.getConfig("Launch.Application", ""));
    var arguments = host.app.expandString(host.app.getConfig("Launch.Arguments", ""));
    var workingDirectory = host.app.expandString(host.app.getConfig("Launch.WorkingDirectory", ""));
    var showWindow = host.app.getConfig("Launch.ShowWindow", "true").toLowerCase() === "true";
    var elevate = host.app.getConfig("Launch.Elevate", "false").toLowerCase() === "true";

    process.setApplicationName(applicationName);
    process.setArguments(arguments);
    process.setWorkingDirectory(workingDirectory);
    process.setShowWindow(showWindow);
    process.setElevate(elevate);

    if (process.launch() == false) {
        process.release();
    }

    if (settings.upcomingPatchDownload === "resume") {
        downloadManager.setAllDownloadsActive(false);
        host.skinWindow.minimize();
    } else if (settings.upcomingPatchDownload === "continue") {
        host.skinWindow.minimize();
    } else {
        process.release();
        host.skinWindow.close();
    }
}

function saveSettings() {
    document.getElementById("saveButton").className = "hiddenItem";

    applySettings();

    if (bundlesLoaded == true) {
        saveObjectToFile(settings, host.app.expandString("{SHA1:{ModuleFileName}}") + ".settings");
    }
}

function settingsChanged() {
    document.getElementById("saveButton").className = "saveButtonNormal";
}

function updateDeliveryMethod(text) {
    document.getElementById("deliveryMethod").innerHTML = text;
}

function updateGraphs(incomingSpeed, outgoingSpeed) {
    while (incomingGraphData.length > numGraphPoints) incomingGraphData.removeIndex(0);
    incomingGraphData.push(incomingSpeed);

    while (outgoingGraphData.length > numGraphPoints) outgoingGraphData.removeIndex(0);
    outgoingGraphData.push(outgoingSpeed);

    incomingGraph.setData([getGraphData(incomingGraphData, maxIncomingGraph)]);
    incomingGraph.draw();

    outgoingGraph.setData([getGraphData(outgoingGraphData, maxOutgoingGraph)]);
    outgoingGraph.draw();
}

function setLaunchVisible(visible) {
    var launchButton = document.getElementById("launchButton");
    if (visible) {
        launchButton.className = "launchButtonNormal";
    } else {
        launchButton.className = "hiddenItem";
    }
}

function setVerifyVisible(visible) {
    var verifyButton = document.getElementById("verifyButton");
    if (visible) {
        verifyButton.className = "verifyButtonNormal";
    } else {
        verifyButton.className = "hiddenItem";
    }
}

function setProgressBarVisible(visible) {
    var progressBarValue = document.getElementById("progressBar-value");
    var progressBarWrap = document.getElementById("progressBar-wrap");

    if (visible) {
        progressBarValue.style.visibility = "visible";
        progressBarWrap.style.visibility = "visible";
    } else {
        progressBarValue.style.visibility = "hidden";
        progressBarWrap.style.visibility = "hidden";
    }
}

function updatePauseResumeButtons() {
    var pauseButton = document.getElementById("pauseButton");
    var resumeButton = document.getElementById("resumeButton");

    if (downloadManager === null) {
        resumeButton.src = "images/main-button-resume-disabled.png"
        pauseButton.src = "images/main-button-pause-disabled.png"
        return;
    }

    if (downloadManager.hasActiveDownload() == true) {
        if (pauseButton.src.indexOf("images/main-button-pause-hover.png") == -1) {
            pauseButton.src = "images/main-button-pause-normal.png"
        }

        resumeButton.src = "images/main-button-resume-disabled.png"
    } else {
        pauseButton.src = "images/main-button-pause-disabled.png"

        if (resumeButton.src.indexOf("images/main-button-resume-hover.png") == -1) {
            resumeButton.src = "images/main-button-resume-normal.png"
        }
    }
}

function setPauseResumeVisible(visible) {
    var pauseButton = document.getElementById("pauseButton");
    var resumeButton = document.getElementById("resumeButton");

    if (visible) {
        pauseButton.style.visibility = "visible";
        resumeButton.style.visibility = "visible";

        updatePauseResumeButtons();
    } else {
        pauseButton.style.visibility = "hidden"
        resumeButton.style.visibility = "hidden";
    }
}

function setPerformanceVisible(visible) {
    var statusEstimateKey = document.getElementById("statusTimeEstimateKey");
    var statusEstimate = document.getElementById("statusTimeEstimate");
    var statusBytesLeftKey = document.getElementById("statusBytesLeftKey");
    var statusBytesLeft = document.getElementById("statusBytesLeft");
    var statusTransferSpeedKey = document.getElementById("statusTransferSpeedKey");
    var statusTransferSpeed = document.getElementById("statusTransferSpeed");

    if (visible) {
        statusEstimateKey.innerHTML = "<b>Time</b>";
        statusBytesLeftKey.innerHTML = "<b>Bytes</b>";
        statusTransferSpeedKey.innerHTML = "<b>Speed</b>";
    } else {
        statusEstimateKey.innerHTML = "";
        statusBytesLeftKey.innerHTML = "";
        statusTransferSpeedKey.innerHTML = "";
        statusEstimate.innerHTML = "";
        statusBytesLeft.innerHTML = "";
        statusTransferSpeed.innerHTML = "";
    }
}

function setDeliveryMethodVisible(visible) {
    var deliveryMethod = document.getElementById("deliveryMethod");

    if (visible) {
        deliveryMethod.style.visibility = "visible";
    } else {
        deliveryMethod.style.visibility = "hidden";
    }
}

function setDownloadVisible(visible) {
    setDeliveryMethodVisible(visible);
    setPerformanceVisible(visible);
}

function updateCompleteStatus(successful, lastError) {
    var rootManifest;

    if (successful == true) {
        updateStatusText(getLanguageString("PatchManifestState_Complete"));
    } else if (lastError == patchManifestError.USERFAIL) {
        if (failureString.length > 0) {
            updateStatusText(getLanguageString(failureString));
        } 
    } else if (lastError != patchManifestError.NONE) {
        updateStatusText(getLanguageString("PatchManifestError_" + patchManifestError.nameFromId(lastError)));
    }

    setProgressBarVisible(false);
    setDownloadVisible(false);
    setPauseResumeVisible(false);

    rootManifest = patchManager.manifestById(host.idFromString(rootManifestUrl.toLowerCase()));
    setVerifyVisible(rootManifest !== null && rootManifest.getCurrentReleaseId() >= 0);
    setLaunchVisible(rootManifest !== null && rootManifest.getCurrentReleaseId() >= rootManifest.getRequiredReleaseId());
}

function onProgress(info) {
    setProgressBarVisible(true);
    
    var x = parseInt(info.percent * 100, 10);
    if (x < 0) {
        if (IndefiniteProgressAnim.isRunning() === false) {
            var progressBarValue = document.getElementById("progressBar-value");
            progressBarValue.style.width = "100%";

            progressBarValue.style.backgroundImage = "url(images/main-progressbar-indefinite.png)";
            IndefiniteProgressAnim.start("progressBar-value", 11, 19, 20, false);
        }
    } else {
        if (IndefiniteProgressAnim.isRunning() === true) {
            IndefiniteProgressAnim.stop();
            var progressBarValue = document.getElementById("progressBar-value");
            progressBarValue.style.backgroundPosition = "";
            progressBarValue.style.backgroundImage = "url(images/main-progressbar.png)";
        }
        document.getElementById("progressBar-value").style.width = x + "%";
    }
}

function updateStatusText(Text) {
    document.getElementById("statusText").innerHTML = Text;
}

function updateBytesLeft(Text) {
    document.getElementById("statusBytesLeft").innerHTML = Text;
}

function updateTimeEstimate(Text) {
    document.getElementById("statusTimeEstimate").innerHTML = Text;
}

function updateTransferSpeed(speed) {
    var Text = getTransferSpeedMessage(speed);
    document.getElementById("statusTransferSpeed").innerHTML = Text;
}

function updateMaxIncomingSpeed(maxIncomingSpeed) {
    maxIncomingGraph = maxIncomingSpeed;
    var Text = getTransferSpeedMessage(maxIncomingSpeed);
    document.getElementById("incomingMaxSpeed").innerHTML = "Max " + Text;
}

function updateAverageIncomingSpeed(averageIncomingSpeed) {
    var Text = getTransferSpeedMessage(averageIncomingSpeed);
    document.getElementById("incomingAvgSpeed").innerHTML = "Avg " + Text;
}

function updateCurrentIncomingSpeed(currentIncomingSpeed) {
    var Text = getTransferSpeedMessage(currentIncomingSpeed);
    document.getElementById("incomingCurSpeed").innerHTML = "Cur " + Text;
}

function updateMaxOutgoingSpeed(maxOutgoingSpeed) {
    maxOutgoingGraph = maxOutgoingSpeed;
    var Text = getTransferSpeedMessage(maxOutgoingSpeed);
    document.getElementById("outgoingMaxSpeed").innerHTML = "Max " + Text;
}

function updateAverageOutgoingSpeed(averageOutgoingSpeed) {
    var Text = getTransferSpeedMessage(averageOutgoingSpeed);
    document.getElementById("outgoingAvgSpeed").innerHTML = "Avg " + Text;
}

function updateCurrentOutgoingSpeed(currentOutgoingSpeed) {
    var Text = getTransferSpeedMessage(currentOutgoingSpeed);
    document.getElementById("outgoingCurSpeed").innerHTML = "Cur " + Text;
}

function initializeTabs() {
    tabHeader = [
                document.getElementById("mainTabHeader"),
                document.getElementById("performanceTabHeader"),
                document.getElementById("optionsTabHeader")
                ];

    tabContent = [
                document.getElementById("mainTabContent"),
                document.getElementById("performanceTabContent"),
                document.getElementById("optionsTabContent")
                ];

    resetTabs();

    tabSelect(document.getElementById("mainTabHeader"));
}

function resetTabs() {
    for (var i = 0; i < tabHeader.length; ++i) {
        tabHeader[i].className = "tabHeaderNormal";
        tabContent[i].style.display = "none";
        tabContent[i].style.visibility = "hidden";
    }
}

function tabSelect(element) {
    for (var i = 0; i < tabHeader.length; ++i) {
        if (tabHeader[i] != element) {
            tabHeader[i].className = "tabHeaderNormal";
            tabContent[i].style.display = "none";
            tabContent[i].style.visibility = "hidden";
        }
    }

    for (var i = 0; i < tabHeader.length; ++i) {
        if (tabHeader[i] == element) {
            selectedTab = tabHeader[i];
            tabHeader[i].className = "tabHeaderSelect";
            tabContent[i].style.display = "block";
            tabContent[i].style.visibility = "visible";
        }
    }
}

function tabHoverEnter(element) {
    if (selectedTab != element) {
        element.className = "tabHeaderHover";
    }
}

function tabHoverExit(element) {
    if (selectedTab != element) {
        element.className = "tabHeaderNormal";
    }
}

function closeHoverEnter(element) {
    element.src = "images/main-button-close-hover.png"
}

function closeHoverExit(element) {
    element.src = "images/main-button-close-normal.png"
}

function closeClick(element) {
    host.skinWindow.close();
}

function minimizeHoverEnter(element) {
    element.src = "images/main-button-minimize-hover.png"
}

function minimizeHoverExit(element) {
    element.src = "images/main-button-minimize-normal.png"
}

function minimizeClick(element) {
    host.skinWindow.minimize();
}

function pauseHoverEnter(element) {
    if (downloadManager !== null && downloadManager.hasActiveDownload() == true) {
        element.src = "images/main-button-pause-hover.png"
    }
}

function pauseHoverExit(element) {
    if (downloadManager !== null && downloadManager.hasActiveDownload() == true) {
        element.src = "images/main-button-pause-normal.png"
    }
}

function pauseClick(element) {
    downloadManager.setAllDownloadsActive(false);
}

function resumeHoverEnter(element) {
    if (downloadManager !== null && downloadManager.hasActiveDownload() == false) {
        element.src = "images/main-button-resume-hover.png"
    }
}

function resumeHoverExit(element) {
    if (downloadManager !== null && downloadManager.hasActiveDownload() == false) {
        element.src = "images/main-button-resume-normal.png"
    }
}

function resumeClick(element) {
    downloadManager.setAllDownloadsActive(true);
}

function saveHoverEnter(element) {
    if (element.className != "hiddenItem") {
        element.className = "saveButtonHover";
    }
}

function saveHoverExit(element) {
    if (element.className != "hiddenItem") {
        element.className = "saveButtonNormal";
    }
}

function verifyClick() {
    verifyManifests(true);
}

function verifyHoverEnter(element) {
    if (element.className != "hiddenItem") {
        element.className = "verifyButtonHover";
    }
}

function verifyHoverExit(element) {
    if (element.className != "hiddenItem") {
        element.className = "verifyButtonNormal";
    }
}

function launchHoverEnter(element) {
    if (element.className != "hiddenItem") {
        element.className = "launchButtonHover";
    }
}

function launchHoverExit(element) {
    if (element.className != "hiddenItem") {
        element.className = "launchButtonNormal";
    }
}

function beginMoveWindow(element) {
    host.skinWindow.beginMove();
}

function beginSizeWindow(element) {
    host.skinWindow.beginSize();
}

function doCanvasTest(c) {
    with (Math) {
        var o = c.getContext('2d'); var w = 400; var h = 400; c.width = w; c.height = h; var low; var high; function rnd() { seed = (seed * 214013 + 2531011) & 0xffffffff; return Math.abs(seed >> 16) / 32768; }
        var step = 1 / 20; var t = 0; window.setInterval(function() {
            o.fillStyle = "#000000"; o.fillRect(0, 0, w, h); o.save(); seed = 4; for (var j = 0; j < 500; j++)
            { var x = 4 * rnd() - 2 - cos(1.31 * t); var y = 4 * rnd() - 2 - sin(t); if (x * x + y * y < 1) { var tt = pow(x * x + y * y, 2); var d = pow(x * x + y * y, 1 / 6); x /= d; y /= d; var s = (5 + sin(t * 10.2)) / 6; x *= s; y *= s; x = x * 100 + w / 2; y = y * 100 + h / 2; var r = floor(rnd() * 224) + 32; var b = floor(rnd() * 224) + 32; var g = (r + b) / 8; o.globalAlpha = 1 - tt; o.fillStyle = "rgb(" + r + "," + g + "," + b + ")"; o.fillRect(x - 2, y - 2, 5, 5); } }
            o.globalCompositeOperation = "lighter"; var count = 7; for (var i = 0; i < count; i++)
            { var val = count - 1 - i; o.globalAlpha = 0.6; feedback(o, c, w, h, Math.pow(2, 1 / 2 / Math.pow(2, val / 2))); }
            o.restore(); t += step;
        }, step * 1000);
    }
    function feedback(o, c, w, h, scale)
    { o.save(); o.translate(w / 2, h / 2); o.scale(scale, scale); o.translate(-w / 2, -h / 2); o.drawImage(c, 0, 0); o.restore(); }
}