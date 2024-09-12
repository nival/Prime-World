
var CheckUpdateResults={Error:-1,NoUpdates:0,HasLauncherUpdates:1,HasContentUpdates:2};var UpdateItems={Launcher:0,PWClient:1,Defenders:2};var UpdateStatus={US_ERROR:-1,US_NO_NEW_UPDATES:0,US_FINISHED:1};var updateManager=null;function UpdateManager(){this.resetSpeedValues();this.UpdateDefinitions=[];this.downloaded=false;this.barFullWidth=430;this.inUpdateProcess=false;this.lastUpdateTime=0;this.checkUpdatesResult=CheckUpdateResults.NoUpdates;this.waitForRetryInterval=parseInt(app.getConfig("UpdateRetryInterval","120"));if(isNaN(this.waitForRetryInterval)||this.waitForRetryInterval<0)
this.waitForRetryInterval=120;for(var defName in UpdateItems)
this.UpdateDefinitions[UpdateItems[defName]]={id:UpdateItems[defName]};this.UpdateDefinitions[UpdateItems.Launcher].Url=app.getConfig("TargetUrlLauncher","");this.UpdateDefinitions[UpdateItems.Launcher].repairTitle=getLocalizedString("checkCorruptedFilesTextLauncher");this.UpdateDefinitions[UpdateItems.Launcher].bCanUseSubFolders=Boolean(false);this.checkUpdateInterval=parseInt(app.getConfig("CheckUpdateIntervalMinutes","60"));if(isNaN(this.checkUpdateInterval)||this.checkUpdateInterval<0)
this.checkUpdateInterval=60;this.checkUpdateInterval*=60000;this.speedUpdatePeriod=parseInt(app.getConfig("SpeedUpdateInterval","2"));if(isNaN(this.speedUpdatePeriod)||this.speedUpdatePeriod<0)
this.speedUpdatePeriod=2;this.speedUpdatePeriod*=1000;var _this=this;app.updateContentProgress.connect(function(curDownloaded,totalForDownload,curApplied,totalForApply,isRepair){if(usingMailRuGC){MailRuAuth.updateContentProgress(curDownloaded,totalForDownload,curApplied,totalForApply,isRepair);}
else
_this.updateContentProgress(curDownloaded,totalForDownload,curApplied,totalForApply,isRepair);});app.updateContentFinished.connect(function(result){_this.updateContentFinished(result);});app.checkForUpdatesFinished.connect(function(result){_this.onCheckForUpdatesFinished(result);});app.checkFilesFinished.connect(function(result){_this.onCheckFilesFinished(result);});app.checkFilesProgress.connect(function(result){if(usingMailRuGC)
MailRuAuth.onCheckFilesProgress(result);else
_this.onCheckFilesProgress(result);});app.repairFinished.connect(function(result){_this.onRepairFinished(result);});app.repairProgress.connect(function(result){if(usingMailRuGC){MailRuAuth.updateContentProgress(result.bytesCurDownloaded,result.bytesTotalForDownload,result.patchesCurApplied*100.0,result.patchesTotalForApply*100.0,true);}
else
_this.onRepairProgress(result);});app.repairAborted.connect(function(){_this.onRepairAborted();});app.updateAddonProgress.connect(function(result){_this.onUpdateAddonProgress(result);});app.updateAddonFinished.connect(function(result){_this.onUpdateAddonFinished(result);});}
UpdateManager.prototype.initContentDefinitions=function(){this.UpdateDefinitions[UpdateItems.PWClient].Url=app.getConfig("TargetUrl","");this.UpdateDefinitions[UpdateItems.PWClient].repairTitle=getLocalizedString("checkCorruptedFilesText");this.UpdateDefinitions[UpdateItems.PWClient].bCanUseSubFolders=Boolean(true);this.UpdateDefinitions[UpdateItems.PWClient].onFinishRepair=function(){var forceRepairFile=app.getConfig("ForceRepairFile",".force_repair");if(forceRepairFile&&forceRepairFile!=""){if(app.checkFile(forceRepairFile))
app.removeFile(forceRepairFile);}}
this.UpdateDefinitions[UpdateItems.Defenders].Url=app.getConfig("Defenders.TargetUrl","");this.UpdateDefinitions[UpdateItems.Defenders].repairTitle=getLocalizedString("checkCorruptedFilesTextDefenders");this.UpdateDefinitions.forEach(function(def){if(def.Url=="")
delete def.Url;});}
UpdateManager.prototype.resetSpeedValues=function(notClear){this.speed=0;this.setupAvgSpeedValues();this.minSpeed=-1;this.lastSpeedUpdateTime=0;this.lastSpeedUpdateSize=0;this.totalBytes=0;this.downloadedBytes=0;this.totalPatches=0;this.appliedPatches=0;this.firstUpdate=true;if(!notClear){delete this.dstartSent;delete this.drepairSent;}}
UpdateManager.prototype.setupAvgSpeedValues=function(){this.avgSpeedValues={calculateStartTime:getTime(),calculatedSpeed:0,fullDownload:0,lastDownload:-1};}
UpdateManager.prototype.startUpdateContent=function(){if(inClosingState)
return;app.logMessage("startUpdateContent");this.resetSpeedValues();document.getElementById("mainInfoTbl").style.visibility="hidden";if(this.UpdateDefinitions[UpdateItems.PWClient].Url){if(this.UpdateDefinitions[UpdateItems.PWClient].Url=="none"){this.updateContentFinished({valid:true});}
else{setDivDisplay("MainInfoPanel","block");if(!authMain.isLoggedIn()){setDivDisplay("UserInfoPanel","none");}
this.downloaded=false;setDownloadWaitVisible(true);setDownloadVisible(false);this.inUpdateProcess=true;delete this.launcherUpdate;app.startUpdateContents(this.UpdateDefinitions[UpdateItems.PWClient].Url,this.UpdateDefinitions[UpdateItems.PWClient].bCanUseSubFolders);}}
else{var error={error:true,errorType:"EMPTY_TARGET_URL",solutionID:"SOL_TECH_SUPPORT"};showErrorMessage(error);}}
UpdateManager.prototype.startUpdateLauncher=function(){if(inClosingState){app.logWarning("startUpdateLauncher failed - is in closing state");return;}
app.logMessage("startUpdateLauncher");delete this.inLauncherUpdateRepair;setDivDisplay("launcherUpdatePanel","block");setDivDisplay("newsMainDiv","none");document.getElementById("launcherUpdateCaption").innerHTML=getLocalizedString("launcherUpdateCaption","innerHTML");setDivDisplay("launcherUpdateLabel","none");this.resetSpeedValues();document.getElementById("mainInfoTbl").style.visibility="hidden";app.logMessage("    url="+this.UpdateDefinitions[UpdateItems.Launcher].Url);if(this.UpdateDefinitions[UpdateItems.Launcher].Url){this.launcherUpdate=true;var sUrl=this.UpdateDefinitions[UpdateItems.Launcher].Url;var bFlag=this.UpdateDefinitions[UpdateItems.Launcher].bCanUseSubFolders;app.logMessage("    url="+sUrl+" flag="+bFlag.toString());app.startUpdateContents(sUrl,bFlag);this.inUpdateProcess=true;}
else{delete this.launcherUpdate;onLauncherUpdated();}}
UpdateManager.prototype.setRepairState=function(isRepair){if(this.isRepair!=isRepair){this.isRepair=isRepair;updateMainButton();this.firstUpdate=true;var element=document.getElementById("downloadBar");if(this.isRepair){element.className="progressBarClass progress red";element.style.width="0px";setDivDisplay("patchBarBorder","none");setDivDisplay("repairFilesText","block");document.getElementById("repairFilesText").innerHTML=getLocalizedString("repairFilesText","innerHTML");}
else{element.className="progressBarClass progress green";setDivDisplay("patchBarBorder","block");setDivDisplay("repairFilesText","none");}}}
UpdateManager.prototype.updateContentProgress=function(curDownloaded,totalForDownload,curApplied,totalForApply,isRepair){this.setRepairState(isRepair);if(this.launcherUpdate)
return this.updateLauncherProgress(curDownloaded,totalForDownload,curApplied,totalForApply,isRepair);this.totalBytes=totalForDownload;this.downloadedBytes=curDownloaded;this.totalPatches=totalForApply;this.appliedPatches=curApplied;if(this.firstUpdate){var statPrms={"total_download":this.totalBytes};if(this.isRepair){statPrms.cmd="drepair";this.drepairSent=true;}
else{statPrms.total_patches=this.totalPatches;if(this.totalBytes>0){if(!this.dstartSent){statPrms.cmd="dstart";this.dstartSent=true;}}}
if(statPrms.cmd&&statPrms.cmd!=""){statPrms.muid=muid;statistic.sendAdvanced(statPrms);}
delete this.firstUpdate;}
if(currentState==States.PausingBeforeDownload||currentState==States.Hide){dlgMan.CloseDialog("httpWaitDiv");updateMainButton(States.Download);}
setDownloadWaitVisible(false);setDownloadVisible(true);this.showDownloadInfo(curDownloaded,totalForDownload);if(!this.isRepair){var mainButtonWrap=document.getElementById("mainButtonWrap");mainButtonWrap.style.display=(totalForDownload<=curDownloaded)?"none":"block";}
var curTime=getTime();if(this.lastSpeedUpdateTime==0||curTime<this.lastSpeedUpdateTime||curDownloaded<this.lastSpeedUpdateSize){this.lastSpeedUpdateTime=curTime;this.lastSpeedUpdateSize=curDownloaded;}
var timeSpent=curTime-this.lastSpeedUpdateTime;if(totalForDownload<=curDownloaded||timeSpent<this.speedUpdatePeriod){if(totalForDownload<=curDownloaded)
document.getElementById("mainInfoTbl").style.visibility="hidden";}
else{document.getElementById("mainInfoTbl").style.visibility="visible";var downloaded=curDownloaded-this.lastSpeedUpdateSize;this.speed=downloaded/timeSpent;document.getElementById("speedText").innerHTML=getTransferSpeedMessage(this.speed*1000);var timeRemain=(totalForDownload-curDownloaded)/this.speed;document.getElementById("timeRemainText").innerHTML=getTimeEstimateMessage(timeRemain/1000);if(this.minSpeed<0||this.speed<this.minSpeed)
this.minSpeed=this.speed;this.lastSpeedUpdateTime=curTime;this.lastSpeedUpdateSize=curDownloaded;}
if(curDownloaded<totalForDownload&&this.avgSpeedValues.lastDownload<curDownloaded&&this.avgSpeedValues.calculateStartTime<curTime){var sizeDiff=curDownloaded-this.avgSpeedValues.lastDownload;if(this.avgSpeedValues.lastDownload<0){this.avgSpeedValues.calculatedSpeed=this.speed;this.avgSpeedValues.calculateStartTime=getTime();}
else{this.avgSpeedValues.fullDownload+=sizeDiff;var timeDiff=curTime-this.avgSpeedValues.calculateStartTime;if(timeDiff>0)
this.avgSpeedValues.calculatedSpeed=this.avgSpeedValues.fullDownload/timeDiff;else
this.avgSpeedValues.calculatedSpeed=this.speed;}
this.avgSpeedValues.lastDownload=curDownloaded;}
var patchCaption=getLocalizedString("patchBarText","innerHTML");patchCaption+=" "+parseInt(curApplied)+"/"+parseInt(totalForApply);document.getElementById("patchBarText").innerHTML=patchCaption;var k=curApplied/totalForApply;var width=this.barFullWidth*k;document.getElementById("patchBar").style.width=parseInt(width)+"px";}
UpdateManager.prototype.showDownloadInfo=function(curDownloaded,totalForDownload){var downloadCaption=getLocalizedString("downloadBarText","innerHTML");downloadCaption+=" "+mBytesMessage(curDownloaded)+"/"+mBytesMessage(totalForDownload);document.getElementById("downloadBarText").innerHTML=downloadCaption;var k=curDownloaded/totalForDownload;var width=this.barFullWidth*k;document.getElementById("downloadBar").style.width=parseInt(width)+"px";}
UpdateManager.prototype.updateLauncherProgress=function(curDownloaded,totalForDownload,curApplied,totalForApply,isRepair){if(totalForDownload>0){if(isRepair){if(!this.inLauncherUpdateRepair){app.logMessage("Turn to repair from launcher self update");this.inLauncherUpdateRepair=true;this.showRepairOnLauncherUpdate();}
this.showDownloadInfo(curDownloaded,totalForDownload);}
else{operatorFrame.hideFrame();if(this.inLauncherUpdateRepair){app.logMessage("Turn to repair from ");delete this.inLauncherUpdateRepair;this.hideRepairOnLauncherUpdate();}
var element=document.getElementById("launcherUpdateCaption");var percent=curDownloaded*100/totalForDownload;var percentStr=getLocalizedString("launcherUpdatePercent","innerHTML")+" "+percent.toFixed(0)+"%";element.innerHTML=percentStr;element=document.getElementById("launcherUpdateLabel");element.style.display="block";}}}
UpdateManager.prototype.showRepairOnLauncherUpdate=function(){setDivDisplay("launcherUpdatePanel","none");setDivDisplay("MainInfoPanel","block");setDivDisplay("InfoWindow","none");setDivDisplay("mainTabContent","block");document.getElementById("mainTabContent").style.left="168px";document.getElementById("downloadWaitPanel").style.left="168px";operatorFrame.showNews();}
UpdateManager.prototype.hideRepairOnLauncherUpdate=function(){operatorFrame.hideFrame();setDivDisplay("launcherUpdatePanel","block");setDivDisplay("MainInfoPanel","none");this.restoreDownloadIndicators();}
UpdateManager.prototype.restoreDownloadIndicators=function(){setDivDisplay("mainTabContent","none");setDivDisplay("InfoWindow","block");document.getElementById("mainTabContent").style.left="216px";document.getElementById("downloadWaitPanel").style.left="216px";}
UpdateManager.prototype.updateContentFinished=function(result){this.inUpdateProcess=false;this.lastUpdateTime=getTime();this.onCheckUpdatesTimeout();this.setRepairState(false);if(this.launcherUpdate)
return this.updateLauncherFinished(result);delete this.launcherUpdate;setDownloadWaitVisible(false);setDownloadVisible(false);app.logMessage("updateContentFinished");if(result.error){var statPrms=this.makeStatParameters("derror");statPrms.error=this.makeStatErrorString(result);if(result.errorType=="HTTP"||result.errorType=="PATCH_MANIFEST_VERSION")
statPrms.need_close=0;else
statPrms.need_close=1;statistic.sendAdvanced(statPrms);if(result.errorType=="HTTP"||result.errorType=="PATCH_MANIFEST_VERSION"){this.onUpdateContentFailed(result);}
else{var _this=this;this.disableCheckForUpdates();showErrorMessage(result,function(){_this.onUpdateContentFailed(result);});}
updateMainButton(States.Hide);}
else{delete this.updateHttpFailed;this.downloaded=true;checkDownloadState();app.showAlertBlink();if(result.status==UpdateStatus.US_FINISHED&&launcherSettings.playSound){app.playSound(app.getConfig("OnUpdateContentFinishedSound","update_finished.wav"));}
this.sendDend();if(!this.dontUpdateDefenders){if(!this.checkForForcedRepair()){if(this.checkDefendersRemoveState()){this.removeDefenders();app.logMessage("[UpdateManager] checkDefendersRemoveState");this.onFullUpdateFinished();}else if(this.isDefendersAllowed()){if(this.checkDefendersInstalled())
this.startDownloadAddon();else
this.showDefendersInstallButton();}else{app.logMessage("[UpdateManager] updateContentFinished - update ui");this.onFullUpdateFinished();}}}
else{app.logMessage("[UpdateManager] updateContentFinished - update ui");this.onFullUpdateFinished();}}}
UpdateManager.prototype.isDefendersAllowed=function(){var noDefendersInstall;noDefendersInstall=app.getConfig("NoDefendersInstall","0");return"0"==noDefendersInstall;}
UpdateManager.prototype.sendDend=function(){if(this.dstartSent||this.drepairSent){statistic.sendAdvanced(this.makeStatParameters("dend"));delete this.dstartSent;delete this.drepairSent;}}
UpdateManager.prototype.makeStatParameters=function(command){var prms={"cmd":command,"speed":this.speed,"avg_speed":this.avgSpeedValues.calculatedSpeed,"min_speed":this.minSpeed,"total_patches":this.totalPatches.toFixed(),"applied_patches":this.appliedPatches.toFixed(),"downloaded":this.downloadedBytes,"total_download":this.totalBytes,"muid":muid};if(prms.min_speed<0)
prms.min_speed=0;return prms;}
UpdateManager.prototype.makeStatErrorString=function(error){var result="ERR_"+error.errorType;if(error.errorType=="HTTP")
result+="_"+error.errorCode+"_"+error.statusCode;if(error.nested)
result+=" "+this.makeStatErrorString(error.nested);return result;}
UpdateManager.prototype.updateLauncherFinished=function(result){app.logMessage("updateLauncherFinished");this.inUpdateProcess=false;this.lastUpdateTime=getTime();setDivDisplay("launcherUpdatePanel","none");setDivDisplay("newsMainDiv","block");if(result.error){app.logWarning("update launcher failed - "+JSON.stringify(result));result.errorTitle=getLocalizedString("launcherUpdateFailed");if(result.errorType=="HTTP"||result.errorType=="PATCH_MANIFEST_VERSION"){this.onUpdateLauncherFailed(result);}
else{var _this=this;this.disableCheckForUpdates();showErrorMessage(result,function(){_this.onUpdateLauncherFailed(result);});}
delete this.inLauncherUpdateRepair;return;}
delete this.inLauncherUpdateRepair;delete this.launcherUpdate;delete this.updateHttpFailed;onLauncherUpdated();}
UpdateManager.prototype.onUpdateLauncherFailed=function(result){if(!this.inLauncherUpdateRepair)
operatorFrame.showServerError();this.onUpdateFailed(result);}
UpdateManager.prototype.onUpdateContentFailed=function(result){var element=document.getElementById("mainTabContent");element.style.display="none";updateMainButton(States.Hide);this.onUpdateFailed(result);}
UpdateManager.prototype.retryUpdate=function(){this.waitForRetryStarts=getTime();this.killWaitForRetryTimer();var _this=this;app.logMessage("[retryUpdate] inClosingState = "+inClosingState?"true":"false");if(!inClosingState)
this.waitForRetryTimer=setInterval(function(){_this.waitForRetryUpdate();},1000);element=document.getElementById("waitForRetryPanelValue");element.innerHTML=getTimeEstimateMessage(this.waitForRetryInterval);}
UpdateManager.prototype.onUpdateFailed=function(result){app.logWarning("Update failed - "+JSON.stringify(result));if(result.errorType=="HTTP"||result.errorType=="PATCH_MANIFEST_VERSION"){this.updateHttpFailed=true;this.lastError=result;setDivDisplay("waitForRetryPanel","block");setDivDisplay("mainTabContent","none");app.queryRetryPatching();}
else{closeClick();}}
UpdateManager.prototype.waitForRetryUpdate=function(){var curTime=getTime();var interval=(curTime-this.waitForRetryStarts)/1000;var remain=this.waitForRetryInterval-interval;if(remain<0){app.logMessage("Time to repeat checking for updates");this.cancelWaitRetry();if(this.launcherUpdate){operatorFrame.hideFrame();updateLauncher();}
else{statistic.sendAdvanced({"cmd":"drepeat","muid":muid});updateGameData();}
return;}
var element=document.getElementById("waitForRetryPanelValue");element.innerHTML=getTimeEstimateMessage(remain);}
UpdateManager.prototype.cancelWaitRetry=function(){setDivDisplay("waitForRetryPanel","none");this.killWaitForRetryTimer();}
UpdateManager.prototype.killWaitForRetryTimer=function(){if(this.waitForRetryTimer){clearInterval(this.waitForRetryTimer);delete this.waitForRetryTimer;}}
UpdateManager.prototype.addDefinitionToCheckForUpdates=function(def){if(this.UpdateDefinitions[def].Url){this.checkFor[this.checkFor.length]={url:this.UpdateDefinitions[def].Url.toLowerCase(),value:CheckUpdateResults.HasContentUpdates};app.checkForUpdates(this.UpdateDefinitions[def].Url,this.UpdateDefinitions[def].bCanUseSubFolders);}}
UpdateManager.prototype.checkForUpdates=function(onFinishCallback){if(!this.isCheckForUpdatesFinised()||this.hasActiveDownloads())
return false;this.checkUpdatesResult=CheckUpdateResults.NoUpdates;this.checkFor=[];this.onCheckFinishCallback=onFinishCallback;delete this.checkUpdatesError;if(authMain.isLoggedIn()){this.addDefinitionToCheckForUpdates(UpdateItems.PWClient);}
this.addDefinitionToCheckForUpdates(UpdateItems.Launcher);return true;}
UpdateManager.prototype.hasActiveDownloads=function(){app.logMessage("hasActiveDownloads: "+this.inUpdateProcess);return this.inUpdateProcess;}
UpdateManager.prototype.isCheckForUpdatesFinised=function(){if(this.checkFor){if(this.checkFor.length==0){delete this.checkFor;return true;}
return false;}
return true;}
UpdateManager.prototype.onCheckForUpdatesFinished=function(result){if(result.error){this.checkUpdatesResult=CheckUpdateResults.Error;this.checkUpdatesError=result;delete this.checkFor;}
else{if(this.checkFor){var url=result.url.toLowerCase();app.logDebug("check finished for :"+url+" checkFor length = "+this.checkFor.length);for(var i=0;i<this.checkFor.length;i++){var checkInfo=this.checkFor[i];app.logDebug("    checkFor info slot: "+checkInfo.url);if(checkInfo.url==url){this.checkFor.splice(i,1);if(result.hasUpdates)
this.checkUpdatesResult|=checkInfo.value;if(this.checkFor.length==0)
delete this.checkFor;break;}}}}
if(!this.checkFor){this.lastUpdateTime=getTime();this.onCheckUpdatesTimeout();if(this.onCheckFinishCallback)
this.onCheckFinishCallback(this.checkUpdatesResult);}}
UpdateManager.prototype.autoCheckFinished=function(result){var needUpdate=(result!=CheckUpdateResults.Error&&result!=CheckUpdateResults.NoUpdates);var curTime=getTime();app.logMessage("Autocheck for updates finished at "+curTime+": "+result);if(needUpdate)
processNewUpdates(result);}
UpdateManager.prototype.onCheckUpdatesTimeout=function(){this.disableCheckForUpdates();var curTime=getTime();var interval=curTime-this.lastUpdateTime;var _this=this;var newInterval=this.checkUpdateInterval;if(interval>=this.checkUpdateInterval){if(this.lastUpdateTime!=0&&!gameStarted){if(!this.inUpdateDefenders){app.logMessage("Start autocheck for updates at "+curTime);this.checkForUpdates(function(result){_this.autoCheckFinished(result);});}}}
else{newInterval=this.checkUpdateInterval-interval+1000;}
app.logMessage("Set check for updates timer to: "+newInterval+" ("+(curTime+newInterval)+")");if(!inClosingState)
this.checkTimeout=setTimeout(function(){_this.onCheckUpdatesTimeout();},newInterval);}
UpdateManager.prototype.disableCheckForUpdates=function(){if(this.checkTimeout){clearTimeout(this.checkTimeout);delete this.checkTimeout;}}
UpdateManager.prototype.enableCheckForUpdates=function(){if(!inClosingState)
this.onCheckUpdatesTimeout();}
UpdateManager.prototype.onAdvancedErrorClick=function(){if(this.lastError){showErrorMessage(this.lastError);}}
UpdateManager.prototype.onCloseClick=function(){if(this.inUpdateProcess||this.inRepair){var statPrms=this.makeStatParameters("dcancel");statistic.sendAdvanced(statPrms);}}
UpdateManager.prototype.onMainButtonClick=function(btnState){if(btnState==States.Download){var statPrms=this.makeStatParameters("dpause");statistic.sendAdvanced(statPrms);}
else if(btnState==States.Paused){statistic.sendAdvanced({"cmd":"dresume","muid":muid});}}
function getTransferSpeedMessage(speed){var speedKBps=speed/1024;if(speedKBps<=0.01)
return"0.0 "+getLocalizedString("SpeedKB");var speedMBps=speedKBps/1024;if(speedMBps>1.0)
return speedMBps.toFixed(2)+" "+getLocalizedString("SpeedMB");return speedKBps.toFixed(2)+" "+getLocalizedString("SpeedKB");}
function getTimeEstimateMessage(estimatedSeconds){var oneMinute=60;var oneHour=oneMinute*60;var oneDay=oneHour*24;if(estimatedSeconds<0)
return getLocalizedString("EstimatingTime");if(estimatedSeconds>7*oneDay)
return getLocalizedString("LongTimeLeft");var timeEstimateString="";var days=parseInt((estimatedSeconds/oneDay));estimatedSeconds-=days*oneDay;if(days>0)
timeEstimateString+=" "+days+" "+getLocalizedString("DayAbbreviation");var hours=parseInt((estimatedSeconds/oneHour));estimatedSeconds-=hours*oneHour;if(hours>0)
timeEstimateString+=" "+hours+" "+getLocalizedString("HourAbbreviation");if(days<=0){var minutes=parseInt((estimatedSeconds/oneMinute));estimatedSeconds-=minutes*oneMinute;if(minutes>0)
timeEstimateString+=" "+minutes+" "+getLocalizedString("MinuteAbbreviation");if(hours<=0){var seconds=parseInt(estimatedSeconds);timeEstimateString+=" "+seconds+" "+getLocalizedString("SecondAbbreviation");}}
if(timeEstimateString.length>0)
return timeEstimateString;return getLocalizedString("EstimatingTime");}
function mBytesMessage(bytes){bytes=Number(bytes);var mbRemain=(bytes/(1024*1024));return mbRemain.toFixed(2)+" "+getLocalizedString("MbRemain");}
UpdateManager.prototype.startRepair=function(){var i;var def;if(inClosingState)
return;this.repairItems=[];if(arguments.length>0){for(i=0;i<arguments.length;i++){def=this.UpdateDefinitions[arguments[i]];if(def)
this.repairItems[this.repairItems.length]=def;}}
else{for(i=UpdateItems.Launcher;i<=UpdateItems.Defenders;i++){def=this.UpdateDefinitions[i];if(def)
this.repairItems[this.repairItems.length]=def;}}
delete this.repairNeedRestart;if(this.repairItems.length>0)
this.processRepairItem();}
UpdateManager.prototype.processRepairItem=function(){if(inClosingState)
return;this.disableCheckForUpdates();this.hideDefendersInfo();delete this.dstartSent;delete this.drepairSent;enableRepairButton(false);this.inRepair=true;setDownloadVisible(true);this.setRepairState(true);var el=document.getElementById("downloadBar");el.className="progressBarClass progress yellow";el.style.width="0px";el=document.getElementById("downloadBarText");el.innerHTML="";var repairItem=this.repairItems[0];document.getElementById("repairFilesText").innerHTML=repairItem.repairTitle;app.logMessage("Start repair from "+repairItem.Url);if(repairItem.Url)
app.startRepair(repairItem.Url,repairItem.bCanUseSubFolders);else
this.onRepairFinished({valid:true});}
UpdateManager.prototype.onCheckFilesFinished=function(result){var state=result.valid?"successfully":("with error: "+result.errorMessage);app.logMessage("Check files finished "+state);app.logMessage("Checked project "+this.repairURL);app.logMessage("CheckFilesFinished: result.valid="+result.valid+", result.error="+result.error);if(!result.valid){app.logWarning("CheckFilesFinished: failed - show error message and finalizeRepair.")
result.errorTitle=getLocalizedString("checkFilesError");showErrorMessage(result);this.finalizeRepair(result);}
this.hasFilesToRepair|=result.needRepair;delete this.isRepair;if(result.valid&&!result.needRepair)
this.onRepairFinished(result);if(result.needRepair)
this.resetSpeedValues();if(!inClosingState)
app.repairCurruptedFiles();}
UpdateManager.prototype.onCheckFilesProgress=function(result){var k=1;if(result.patchesTotalForApply>0)
k=result.patchesCurApplied/result.patchesTotalForApply;var width=this.barFullWidth*k;document.getElementById("downloadBar").style.width=parseInt(width)+"px";}
UpdateManager.prototype.onRepairFinished=function(result){var state=result.valid?"successfully":("with error: "+result.errorMessage);app.logMessage("Repair files finished "+state);var repairItem=this.repairItems[0];app.logMessage("Repaired project "+repairItem.Url);if(result.valid){this.repairNeedRestart|=result.needRestart;this.sendDend();if(repairItem.onFinishRepair)
repairItem.onFinishRepair(this);this.repairItems.splice(0,1);if(this.repairItems.length==0){var text;if(this.repairNeedRestart){text=getLocalizedString("repairFilesSuccess");text+="<br/><span style='color:#ff0;'>";text+=getLocalizedString("repairFilesSuccessRestart");text+="</span>"}
else{if(this.hasFilesToRepair)
text=getLocalizedString("repairFilesSuccessfully");else
text=getLocalizedString("checkFilesNoRepair");}
delete this.hasFilesToRepair;setDownloadVisible(false);var continueDownload=!this.repairNeedRestart&&this.inForcedRepair;var _this=this;showMessageBox(getLocalizedString("repairFilesTitle"),text,function(){_this.onCloseRepairSuccessMsg(continueDownload);});this.checkAndShowDefendersResult();this.onFullUpdateFinished();}
else{this.processRepairItem();}}
else{delete this.hasFilesToRepair;app.logWarning("RepairFailed: "+JSON.stringify(result));result.errorTitle=getLocalizedString("repairFilesError");showErrorMessage(result,this.enableCheckForUpdates());this.finalizeRepair(result,true);}}
UpdateManager.prototype.onRepairProgress=function(result){this.updateContentProgress(result.bytesCurDownloaded,result.bytesTotalForDownload,result.patchesCurApplied,result.patchesTotalForApply,true);}
UpdateManager.prototype.onRepairAborted=function(){this.finalizeRepair();}
UpdateManager.prototype.finalizeRepair=function(result,dontStartCheckUpdates){if(result&&!result.valid&&this.drepairSent){var statPrms=this.makeStatParameters("derror");statPrms.error=this.makeStatErrorString(result);statPrms.need_close=0;statistic.sendAdvanced(statPrms);}
delete this.isRepair;delete this.inRepair;setDownloadVisible(false);enableRepairButton(true);updateMainButton();delete this.repairURL;if(!dontStartCheckUpdates)
this.enableCheckForUpdates();this.checkAndShowDefendersResult();delete this.inForcedRepair;}
UpdateManager.prototype.onCloseRepairSuccessMsg=function(continueDownload){this.finalizeRepair();if(this.repairNeedRestart)
updateMainButton(States.Hide);app.finishRepairProcess(this.repairNeedRestart);if(continueDownload){delete this.inForcedRepair;this.checkAndShowDefendersResult(true);}}
UpdateManager.prototype.hideDefendersInfo=function(){if(operatorFrame.frameLoaded)
launcherWindow.executeScript("hideDefendersInfo();","operatorFrame");}
UpdateManager.prototype.startDownloadAddon=function(){delete this.defendersUpdateResult;delete this.LastDefendersError;this.hideDefendersInfo();if(inClosingState)
return;if(this.checkDefendersRemoveState()){app.logMessage("startDownloadAddon: Defenders in removed state. No updates.");return;}
if(this.UpdateDefinitions[UpdateItems.Defenders].Url){this.resetSpeedValues();app.logMessage("Start download Defenders");this.inUpdateDefenders=true;enableRepairButton(false);if(operatorFrame.frameLoaded)
launcherWindow.executeScript("showDefendersProgress(0);","operatorFrame");app.startUpdateAddon(this.UpdateDefinitions[UpdateItems.Defenders].Url);}
else{this.onFullUpdateFinished();}}
UpdateManager.prototype.onUpdateAddonProgress=function(result){var k1=(result.TotalForDownload==0)?0:result.CurDownloaded/result.TotalForDownload;var k2=(result.TotalForApply==0)?0:result.CurApplied/result.TotalForApply;var k=(k1*3+k2)/4;if(operatorFrame.frameLoaded)
launcherWindow.executeScript("showDefendersProgress("+k+");","operatorFrame");}
UpdateManager.prototype.onUpdateAddonFinished=function(result){delete this.inUpdateDefenders;this.defendersUpdateResult=result;this.hideDefendersInfo();if(result.valid){app.logMessage("Defenders updated succesfully");if(operatorFrame.frameLoaded)
launcherWindow.executeScript("showDefendersButton();","operatorFrame");delete this.LastDefendersError;}
else{this.LastDefendersError=result;app.logWarning("Defenders update failed: "+JSON.stringify(result));if(operatorFrame.frameLoaded)
launcherWindow.executeScript("showDefendersErrorLink();","operatorFrame");}
app.logMessage("Defenders update finished. Enabling repair button");enableRepairButton(true);this.onFullUpdateFinished();}
UpdateManager.prototype.checkAndShowDefendersResult=function(startUpdate){app.logMessage("checkAndShowDefendersResult");if(this.checkDefendersInstalled()){app.logMessage("checkDefendersInstalled() returns true.");if(this.defendersUpdateResult){app.logMessage("Refresh addon update result display. defendersUpdateResult.valid="+this.defendersUpdateResult.valid);this.onUpdateAddonFinished(this.defendersUpdateResult);}
else{app.logMessage("defendersUpdateResult is not set");if(startUpdate){app.logMessage("Start update Defenders");this.startDownloadAddon();}}}
else{this.showDefendersInstallButton();}}
UpdateManager.prototype.checkDefendersInstalled=function(){if(this.checkDefendersRemoveState()){app.logMessage("Defenders in remove state. checkDefendersInstalled result is false");return false;}
var installed=launcherSettings.defendersInstalled;app.logMessage("launcherSettings.defendersInstalled is set to "+installed);if(!installed){var dirName=app.expandString("{Defenders.WorkingDirectory}");app.logMessage("Setting defendersInstalled is not set, checkDefendersInstalled() on directory "+dirName);if(dirName&&dirName!="")
installed=app.checkDirectory(dirName);}
app.logMessage("checkDefendersInstalled result is "+installed);return installed;}
UpdateManager.prototype.checkForForcedRepair=function(){if(this.inForcedRepair)
return true;var forceRepairFile=app.getConfig("ForceRepairFile",".force_repair");if(forceRepairFile&&forceRepairFile!=""){if(app.checkFile(forceRepairFile)){this.inForcedRepair=true;app.logMessage("Found file "+forceRepairFile+", starting forced repair");this.startRepair(UpdateItems.PWClient);return true;}}
return false;}
UpdateManager.prototype.onFullUpdateFinished=function(){if(usingMailRuGC){if(onlyUpdateMode){app.writeMailRuState(MAILRU_GC_STATES.MGC_READY,"",0,0,0);closeClick();return;}
app.logMessage("[UpdateManager] onFullUpdateFinished");mainButtonClick();}}
UpdateManager.prototype.showDefendersInstallButton=function(){if(this.checkDefendersRemoveState()){app.logMessage("showDefendersInstallButton: Defenders in removed state. No updates.");return;}
var noDefendersInstall=app.getConfig("NoDefendersInstall","0");app.logMessage("NoDefendersInstall is set to \""+noDefendersInstall+"\"");if(noDefendersInstall!="0"){app.logMessage("Install defenders button not shown");return;}
if(this.UpdateDefinitions[UpdateItems.Defenders].Url){app.logMessage("Before show Defenders Install Button. frameLoaded="+operatorFrame.frameLoaded+", downloaded="+this.downloaded);if(operatorFrame.frameLoaded&&this.downloaded){launcherWindow.executeScript("showDefendersInstall();","operatorFrame");app.logMessage("Defenders Install Button is shown");}}}
UpdateManager.prototype.onLauncherClosing=function(){this.killWaitForRetryTimer();this.disableCheckForUpdates();}
UpdateManager.prototype.checkDefendersRemoveState=function(){return this.removeDefendersFolders;}
UpdateManager.prototype.removeDefenders=function(){if(this.removeDefendersFolders&&this.removeDefendersFolders.length>0){app.logMessage("Removing Defenders folders");for(var i=0;i<this.removeDefendersFolders.length;){var folder=this.removeDefendersFolders[i];if(app.removeDirectory(folder))
this.removeDefendersFolders.splice(i,1);else
i++;}}}