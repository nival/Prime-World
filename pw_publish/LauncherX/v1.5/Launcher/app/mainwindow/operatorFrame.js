
var operatorFrame=null;function OperatorFrame(){this.isInitialized=Boolean(false);}
OperatorFrame.prototype.initialize=function(){var _this=this;launcherPage.pageRequestFailed.connect(function(url,errCode,errText){_this.onMainPageRequestFailed(url,errCode,errText);});this.newsRefreshPeriod=parseInt(app.getConfig("OperatorContentRefresh","120"));this.checkMaintenanceInterval=parseInt(app.getConfig("OperatorCheckMaintenanceInterval","120"))*1000;var frame=launcherWindow.getFrameById("operatorFrame");frame.loadFinished.connect(function(isOk){return _this.onOperatorFrameLoaded(isOk);});this.lastUpdateTime=0;var updateInterval=parseInt(app.getConfig("OperatorContentUpdateMinutes","30"));if(isNaN(updateInterval)||updateInterval<0)
updateInterval=30;updateInterval*=60000;if(!inClosingState)
this.updateTimer=setInterval(function(){_this.onUpdateFrameTimer();},updateInterval);this.isInitialized=Boolean(true);}
OperatorFrame.prototype.getFrameUrl=function(frameName){var hostUrl=app.expandString("{OperatorContentUrl}");if(hostUrl.length!=0){var lastChar=hostUrl.charAt(hostUrl.length-1);if(lastChar!="/"&&lastChar!="\"")
hostUrl+="/";}
var stateUrl=app.getConfig("OperatorContent."+frameName,"");return hostUrl+stateUrl;}
OperatorFrame.prototype.hideFrame=function(){setDivDisplay("operatorFrameFake","block");setDivDisplay("operatorFrame","none");}
OperatorFrame.prototype.showFrame=function(){if(!this.isInitialized)
return;app.logMessage("showFrame: "+" updateManager.launcherUpdate="+updateManager.launcherUpdate+", updateManager.inUpdateProcess="+updateManager.inUpdateProcess+", updateManager.inLauncherUpdateRepair="+updateManager.inLauncherUpdateRepair);if(updateManager.launcherUpdate&&updateManager.inUpdateProcess&&!updateManager.inLauncherUpdateRepair){app.logMessage("showFrame: new state - hideFrame");this.hideFrame();}
else{app.logMessage("showFrame: check authMain.isLoggedIn = "+authMain.isLoggedIn());app.logMessage("showFrame: check lastPingState = "+this.lastPingState);if(authMain.isLoggedIn()||!this.lastPingState){setDivDisplay("operatorFrame","block");setDivDisplay("operatorFrameFake","none");}}}
OperatorFrame.prototype.showNews=function(){if(!this.isInitialized)
return;var curStatus=globalServerStatusChecker.GetStatus();if(curStatus==GlobalServerStatuses.MAINTENANCE){this.showServerError(true);return;}else if(curStatus==GlobalServerStatuses.CHECKING){return;}
app.logMessage("OperatorFrame: showNews");delete this.inServerError;delete this.inNewsError;if((this.lastFrameName=="loggedin"&&this.frameLoaded))
this.showFrame();if(this.setFrame("LoggedIn")){setDivDisplay("errorsOnOperFrame","none");setDivDisplay("newsOnOperFrame","block");}}
OperatorFrame.prototype.checkMaintenance=function(){app.logDebug("OperatorFrame: start checking maintenance");if(this.lastFrameName&&this.lastFrameName=="maintenance")
this.setFrame("LoggedIn");var _this=this;this.checkMaintenanceTimer=setInterval(function(){_this.onCheckMaintenance();},_this.checkMaintenanceInterval);}
OperatorFrame.prototype.onCheckMaintenance=function(){clearInterval(this.checkMaintenanceTimer);delete this.checkMaintenanceTimer;this.refreshFrame();}
OperatorFrame.prototype.showNewsError=function(){this.inNewsError=true;app.logMessage("OperatorFrame: showNewsError");this.hideFrame();setDivDisplay("errorOperFrameNoServer",this.inServerError?"block":"none");setDivDisplay("errorOperFrameCheckInet",this.inServerError?"block":"none");setDivDisplay("errorOperFrameNoNews",this.inServerError?"none":"block");setDivDisplay("errorsOnOperFrame","block");this.killRefreshTimer();this.refreshWaitStart=(new Date()).valueOf();var _this=this;if(!inClosingState)
this.refreshTimer=setInterval(function(){_this.frameRefreshWaiter();},1000);this.frameRefreshWaiter();}
OperatorFrame.prototype.killRefreshTimer=function(){if(this.refreshTimer){clearInterval(this.refreshTimer);delete this.refreshTimer;}}
OperatorFrame.prototype.frameRefreshWaiter=function(){var curTime=(new Date()).valueOf();var period=(curTime-this.refreshWaitStart)/1000;if(period>this.newsRefreshPeriod){this.killRefreshTimer();setDivDisplay("errorsOnOperFrame","none");setDivDisplay("newsOnOperFrame","block");this.refreshFrame();}
else{var timeStr=getTimeEstimateMessage(this.newsRefreshPeriod-period);var element=document.getElementById("errorOperFrameUpdateTime");element.innerHTML=getLocalizedString("errorOperFrameUpdateTime","innerHTML")+" "+timeStr;}}
OperatorFrame.prototype.showServerError=function(maintenance){app.logMessage("OperatorFrame: showServerError");if(!maintenance)
this.inServerError=true;if(!this.lastFrameName||this.lastFrameName==""){setDivDisplay("errorsOnOperFrame","none");setDivDisplay("newsOnOperFrame","block");}
if(maintenance)
this.setFrame("Maintenance");else
this.setFrame("NoConnection");}
OperatorFrame.prototype.setFrame=function(frameName){app.logDebug("OperatorFrame: setFrame "+frameName);this.lastFrameName=frameName.toLowerCase();var url=this.getFrameUrl(frameName);return this.setFrameUrl(url);}
OperatorFrame.prototype.setFrameUrl=function(url){var loCase=url.toLowerCase();if(this.lastFrameUrl==loCase)
return false;app.logDebug("OperatorFrame: setFrameUrl "+url);this.lastFrameUrl=loCase;this.hideFrameOnLoad();this.refreshFrame();return true;}
OperatorFrame.prototype.refreshFrame=function(){if(globalServerStatusChecker.GetStatus()==GlobalServerStatuses.CHECKING)
return;app.logDebug("OperatorFrame: refreshFrame "+this.lastFrameUrl);if(this.lastFrameUrl&&this.lastFrameUrl!=""){this.killRefreshTimer();delete this.frameFinished;delete this.hasErrors;delete this.inNewsError;delete this.frameLoaded;var el=document.getElementById("operatorFrame");el.src=this.lastFrameUrl;}}
OperatorFrame.prototype.onMainPageRequestFailed=function(url,errCode,errText){if(url.toLowerCase()==this.lastFrameUrl){this.frameLoaded=false;this.hasErrors=true;}}
OperatorFrame.prototype.onOperatorFrameLoaded=function(isOk){setDivDisplay("newsOnOperFrame","none");app.logMessage("onOperatorFrameLoaded isOk = "+isOk+", url="+this.lastFrameUrl);this.hasErrors=!isOk;if(this.hasErrors){this.frameLoaded=false;this.showNewsError();return;}
app.logMessage("Setting _app object to operatorFrame");launcherWindow.addApplicationScriptObject("_app","operatorFrame");launcherWindow.executeScript("function openExternalBrowser(url) { _app.openExternalBrowser(url); }","operatorFrame");launcherWindow.executeScript("function executeAddon(name) { _app.executeAddon(name); }","operatorFrame");launcherWindow.executeScript("document.onselectstart = document.ondragstart = document.onscroll = document.oncontextmenu = function() { return false; };","operatorFrame");launcherWindow.executeScript("document.onmousedown = function(event) { return (event.button != 1); }","operatorFrame");launcherWindow.executeScript("document.onkeypress = function(event) { if(event.keyCode == 13) { _app.processScriptEnterKeyEvent(); return false; } return true; };","operatorFrame");this.lastUpdateTime=(new Date()).valueOf();this.showFrame();this.frameLoaded=true;app.logMessage("OperatorFrameLoaded.");isMaintenance=globalServerStatusChecker.GetStatus()==GlobalServerStatuses.MAINTENANCE;if(isMaintenance&&usingMailRuGC){showErrorMessage(getLocalizedString("srvOfflineText","innerHTML","Технические работы на сервере"));return;}
if(isMaintenance)
this.showServerError(true);updateManager.checkAndShowDefendersResult();updateMainButton();}
OperatorFrame.prototype.onServerPing=function(pingValid){this.lastPingState=pingValid;if(pingValid){this.updateTechWorksMessage(false);delete this.inServerError;setDivDisplay("MainInfoPanel","block");if(this.launcherUpdate)
return;if(authMain.isAuthProcessed()&&authMain.isLoggedIn())
{this.showNews();}
else{app.logMessage("onServerPing: pingValid, start processAuth()");authMain.processAuth();}}
else{if(authMain.isLoggedIn())
authMain.setNeedRelogin();this.showServerOffline();setDivDisplay("MainInfoPanel","none");}}
OperatorFrame.prototype.showServerOffline=function(){var authVisible=(document.getElementById("authFrame").style.display=="block");if(authVisible&&!authMain.isLoggedIn())
this.updateTechWorksMessage(true);else{this.updateTechWorksMessage(false);this.showServerError();}}
OperatorFrame.prototype.updateTechWorksMessage=function(visible){if(visible)
setDivDisplay("srvOfflineMessage","block");else
setDivDisplay("srvOfflineMessage","none");}
OperatorFrame.prototype.onUpdateFrameTimer=function(){if(authMain&&authMain.isLoggedIn()){app.logMessage("Updating operator frame");this.refreshFrame();}}
OperatorFrame.prototype.hideFrameOnLoad=function(){this.hideFrame();}
OperatorFrame.prototype.onLauncherClosing=function(){if(this.updateTimer){clearInterval(this.updateTimer);delete this.updateTimer;}
this.killRefreshTimer();}