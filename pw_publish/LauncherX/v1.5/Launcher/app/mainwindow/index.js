
var protocolVersion="0.0.0";var hostId="0000";var changedVideoSetts=false;var videoSettings=null;var refInfo=null;var muid="";var skinVersion="";var usingMailRuGC=false;var onlyUpdateMode=false;var inClosingState=false;var gameStarted=false;var tryGameStart=false;var showEulaOnLaunch=0;var launchedModule="";var COMMA_SEPARATED_RE=/\s*,\s*/;var isMaintenance=false;var qaMode=false;var OSTypes={WIN:1,MAC:2};var States={Hide:1,Download:2,PausingBeforeStop:3,Paused:4,PausingBeforeDownload:5,Ready:6};var StatStatuses={COMPLETE:0,STOPPED:1,DOWNLOAD_FAILURE:2,NOT_APPLIED:3};var WaitThrobberStates={Normal:1,ToLeft:2,Hide:3};var InputMarks={Valid:1,Error:2,NoMark:3};var currentState=States.Hide;var launcherMainInfo={};var langInfo={};var launcherSettings={};var authMain;var authServer=null;function AuthServer(){this.updateInterval=120000;var val=parseInt(app.getConfig("AuthServerOffTimeout",""),10);if(!isNaN(val)&&val>0){this.updateInterval=val*1000;}
this.checkPingOnLaunchInterval=5000;val=parseInt(app.getConfig("CheckPingOnLaunchInterval",""),10);if(!isNaN(val)&&val>0){this.checkPingOnLaunchInterval=val*1000;}
this.lastValidTime=0;this.url=expandURI(app.getConfig("AuthServer",""));var cfgActions=app.getConfig("ServerInstanceSpecifiedActions","l_join, l_merge").toLowerCase();this.serverSpecifiedActions=cfgActions.split(COMMA_SEPARATED_RE);}
AuthServer.prototype.request=function(req,prms,onFinished){if(!prms)
prms={};if(this.offline&&!prms.force){var curTime=(new Date()).valueOf();if(curTime-this.lastValidTime<this.updateInterval){var data={error:true,errorType:"HTTP",errorCode:-1};return data;}}
var url=this.url;var server=authMain.getServer();var action=getUrlParam('action',req);if(isLoginQueueEnabled()){var isSpecifiedAction=this.serverSpecifiedActions.indexOf(action)>=0;if(isSpecifiedAction&&server)
url+=server;else{url+=app.getConfig("LoginQueueURLPosfix","login");if(isSpecifiedAction)
app.logWarning("trying to execute server specified action, but server instance is not received yet. Using default url. action="+action);}}
else
if(server)
url+=server;var self=this;if(prms&&prms.asyncRequest){httpRequest(url+req,prms,function(data){self.processResponse(data);if(onFinished)
onFinished(data);});}
else{var data=httpRequest(url+req,prms);this.processResponse(data);return data;}};AuthServer.prototype.processResponse=function(data){this.lastValidTime=(new Date()).valueOf();this.offline=!data.valid;if(this.offline)
app.logWarning("response was invalid "+JSON.stringify(data));};AuthServer.prototype.startPings=function(){if(onlyUpdateMode)
return;var pingInterval=parseInt(app.getConfig("AuthServerCheckInterval","120"))*1000;var _this=this;this.serverPingTimer=setInterval(function(){_this.sendPing();},pingInterval);};AuthServer.prototype.sendPing=function(synchronous,debugFakeUrl){var reqPrms="?action=l_ping&ver="+protocolVersion;if(authMain.isLoggedIn())
reqPrms+="&auid="+authMain.getAUID()+"&token="+authMain.getToken();else
reqPrms+="&auid=-1";reqPrms+="&tm_guid="+Date.now();var prms={force:true};if(synchronous){var data=authServer.request(reqPrms,prms);return this.checkPingAnswer(data);}
if(!this.waitAsync){prms.asyncRequest=true;this.waitAsync=true;var _this=this;authServer.request(reqPrms,prms,function(data){_this.checkPingAnswer(data);});}};AuthServer.prototype.checkPingAnswer=function(data){delete this.waitAsync;if(!data.valid){operatorFrame.onServerPing(false);return data;}
try{eval("data.data="+data.data);}
catch(e){operatorFrame.onServerPing(false);return{error:true,errorType:"HTTP",errorCode:201};}
operatorFrame.onServerPing(true);return data;}
var dlgFrameMinZOrder=10;function DialogFrame(idDiv){this.Element=document.getElementById(idDiv);this.OriginalZOrder=this.Element.style.zIndex;if(!this.OriginalZOrder||this.OriginalZOrder=="")
this.OriginalZOrder=dlgFrameMinZOrder;else
this.OriginalZOrder=parseInt(this.OriginalZOrder);}
function DialogManager(){this.blanket=document.getElementById("waiterBlanket");this.Frames=[];}
DialogManager.prototype.GetActiveDialog=function(){if(this.Frames.length==0)
return null;var dlgFrame=this.Frames[this.Frames.length-1];if(dlgFrame&&dlgFrame.Element.style.display!="none")
return dlgFrame.Element;return null;}
DialogManager.prototype.ShowDialog=function(idDiv,execOnClose){if(usingMailRuGC){return;}
var dlgFrame=null;for(var i=0;i<this.Frames.length;i++){if(this.Frames[i].Element.id==idDiv){dlgFrame=this.Frames[i];this.Frames.splice(i,1);break;}}
if(!dlgFrame){dlgFrame=new DialogFrame(idDiv);if(!dlgFrame.Element)
return;dlgFrame.zOrder=dlgFrame.OriginalZOrder;dlgFrame.execOnClose=execOnClose;}
var idx=this.Frames.length;if(idx>0){var prevFrame=this.Frames[idx-1];dlgFrame.zOrder=prevFrame.zOrder+2;}
dlgFrame.Element.style.zIndex=dlgFrame.zOrder;dlgFrame.Element.style.display="block";this.blanket.style.zIndex=dlgFrame.zOrder-1;this.blanket.style.display="block";this.Frames[idx]=dlgFrame;setZOrderForErrorTip(dlgFrame.zOrder+1);changeOptionsButtonState();var elements=dlgFrame.Element.getElementsByTagName('input');if(elements[0]!=undefined)
elements[0].focus();return dlgFrame.Element;}
DialogManager.prototype.CloseDialog=function(idDiv){var element;if(idDiv){element=document.getElementById(idDiv);}
else if(this.Frames.length>0){element=this.Frames[this.Frames.length-1].Element;}
var frame;if(element){var i=this.Frames.length-1;for(;i>=0;i--)
if(this.Frames[i].Element==element)
break;if(i<0){element.style.display="none";return element;}
if(i==this.Frames.length-1){if(i>0){this.blanket.style.zIndex=this.Frames[i-1].zOrder-1;this.Frames[i-1].Element.style.display="block";}}
frame=this.Frames[i];this.Frames.splice(i,1);frame.Element.style.zIndex=frame.OriginalZOrder;frame.Element.style.display="none";}
if(this.Frames.length==0)
this.blanket.style.display="none";else
setZOrderForErrorTip(this.Frames[this.Frames.length-1].zOrder+1);showErrorTip();changeOptionsButtonState();if(frame&&frame.execOnClose)
frame.execOnClose(frame.Element);}
var dlgMan=null;function checkPointInElement(elName,x,y){var el=document.getElementById(elName);var rect=el.getBoundingClientRect();return x>=rect.left&&x<rect.right&&y>=rect.top&&y<rect.bottom;}
function IsDragablePoint(x,y){if(checkPointInElement("moveWindowArea",x,y))
return true;return checkPointInElement("applicationName",x,y);}
function onGlobalServerStatusChange(prevStatus,newStatus){updateMainButton();if(operatorFrame&&authMain&&authMain.isLoggedIn()){operatorFrame.showNews();}}
function onSkinLoaded(){var dlg=document.getElementById("errorMessage");dlg.onCommandButton=errorMessageDialogCmdButton;dlg=document.getElementById("ignoreSSLQuestion");dlg.onCommandButton=ignoreSSLQuestionCmdButton;dlg=document.getElementById("messageBoxWnd");dlg.onCommandButton=messageBoxWndCmdButton;launcherWindow.addApplicationScriptObject();langInfo.langCode=app.expandString("{Macros.LangCode}");qaMode=app.getConfig("QAMode","False")=="True";if(qaMode)
alert("QAMode on");usingMailRuGC=app.getConfig("AuthMode","")=="MailRuGC";onlyUpdateMode=app.getVariable("OnlyUpdateMode")=="True";if(usingMailRuGC&&!onlyUpdateMode)
app.writeMailRuState(MAILRU_GC_STATES.MGC_INITIALIZING,getLocalizedString("launcherInitialization","innerHTML"),1,5);skinVersion=app.expandString("{Macros.SkinVersion}");app.logMessage(app.expandString("Skin version: "+skinVersion));setDivDisplay("minimizeToTrayOptionSection","none");localizeSkin();dlgMan=new DialogManager();globalServerStatusChecker=new ServerStatusChecker();if(usingMailRuGC){globalServerStatusChecker.UpdateServerStatus();if(globalServerStatusChecker.GetStatus()==GlobalServerStatuses.MAINTENANCE){showErrorMessage(getLocalizedString("srvOfflineText","innerHTML","Технические работы на сервере"));return;}}else globalServerStatusChecker.StartCheck();updateManager=new UpdateManager();operatorFrame=new OperatorFrame();statistic=new Statistic();statistic.load();app.launcherClosing.connect(onLauncherClosing);document.onselectstart=document.ondragstart=document.onscroll=document.oncontextmenu=function(){return false;};document.onmousedown=function(event){return(event.button!=1);}
app.onScriptEnterKey.connect(onDocumentEnterPressed);document.onkeyup=checkPressedKey;hideWaiter();app.patcherReadyToRetry.connect(function(){app.logMessage("[patcherReadyToRetry] call retryUpdate");updateManager.retryUpdate();});if(!usingMailRuGC){launcherWindow.show();}
checkRunningProcesses();}
function postLauncherUpdateInitialization()
{app.logMessage("Load deployment settings");showWaiter(getLocalizedString("waitLabel","innerHTML"));app.onDeploymentSettingsLoaded.connect(onDeploymentSettingsLoaded);app.loadDeploymentSettings();}
function onDeploymentSettingsLoaded(result){hideWaiter();if(result!=null&&result.error){showErrorMessage(getLocalizedString("ERR_HTTP"),closeClick);return;}
if(usingMailRuGC&&!onlyUpdateMode)
app.writeMailRuState(MAILRU_GC_STATES.MGC_INITIALIZING,getLocalizedString("launcherInitialization","innerHTML"),2,5);if(!usingMailRuGC)
{if(app.getConfig("ServerStatusUrl"))
globalServerStatusChecker.UpdateServerStatus("async");}
protocolVersion=app.expandString("{PWSocVersion}");preparseRefInfo();operatorFrame.initialize();launcherPage.beforeNavigate.connect(onFramesBeforeNavigate);launcherWindow.windowClosing.connect(onMainWindowClosing);app.needToIgnoreSSLQuestion.connect(onNeedToIgnoreSSLQuestion);document.getElementById("httpWaitDiv").intervalNum=0;authServer=new AuthServer();authMain=new AuthMain();updateManager.initContentDefinitions();statistic.sendEvents();showEulaOnLaunch=parseInt(app.getConfig("ShowEULAOnLaunch","0"));updateEULADiv(false);app.onExecuteAddon.connect(onExecuteAddon);app.processFinished.connect(onGameProcessExit);app.processStarted.connect(onGameProcessStart);app.patcherPaused.connect(function(){hideWaiter();if(!updateManager.downloaded)
updateMainButton(States.Paused);else
checkDownloadState();});app.patcherResumed.connect(function(){updateManager.resetSpeedValues(true);updateMainButton(States.PausingBeforeDownload);});authMain.initialize();setDownloadVisible(false);updateMainButton(States.Hide,false);var appTitle=app.getConfig("Name","Prime World Launcher");appTitle+=" "+skinVersion;document.getElementById("applicationName").innerHTML=appTitle;var machineId=app.getMachineId();if(machineId.valid)
hostId=machineId.id;else
app.logWarning("Can't get machine id: "+machineId.errorMessage);app.logMessage("Use "+hostId+" as host id");sendStatInfo("l_start",{"version":skinVersion});if(authServer.offline){app.logMessage("AuthServer is offline");operatorFrame.showServerError();return;}
app.createDirectory(app.expandString("{UserDataStorage}"));loadAuth();loadInfo();var settsFileName=app.expandString("{UserDataStorage}/{ApplicationName}.settings");var settsObject=loadFileContent(settsFileName,{isObject:true});if(settsObject.valid){mergeObjectProperties(launcherSettings,settsObject.data);}
if(launcherSettings.playSound==undefined)
launcherSettings.playSound=true;if(usingMailRuGC){launcherSettings.playSound=false;launcherSettings.updateWithoutPrompt=true;}
statistic.pushEvent(EventTypes.START);onInitializationComplete();}
function onInitializationComplete()
{changeOptionsButtonState();var eulaRes=0;if(showEulaOnLaunch==1)
eulaRes=1;else
eulaRes=showEULA();if(eulaRes==0)
closeClick();updateMainButton(States.Hide);setVerifyVisible(false);if(eulaRes==1){if(updateManager.downloaded)
{checkDownloadState();}
else
{app.logMessage("Start update before auth");updateGameData();}
authMain.tryToLoginWithoutConfirm(onForceLoginAttemptDone);}
else{showErrorMessage(getLocalizedString("cantGetEula"),function(){closeClick();});}
if(authMain.cachedData.rememberMe&&!authMain.isLoggedIn())
{authMain.tryToLoginByAny(false);}}
function checkRunningProcesses(){app.logMessage("CheckRunningProcesses");if(app.checkRunningProcesses()){checkRunningProcessesFinished();return;}
dlgMan.ShowDialog("gameLaunchedDiv");app.logMessage("Has running process. Wait for finish.");setTimeout(checkRunningProcesses,5000);}
function checkRunningProcessesFinished(){app.logMessage("No running processes. Start update cycle.");dlgMan.CloseDialog("gameLaunchedDiv");updateLauncher();}
function updateLauncher(){updateManager.startUpdateLauncher();}
function updateEULADiv(showFull){if(showEulaOnLaunch==1&&showFull){setDivDisplay("newSiteLink","block");setDivDisplay("oldSiteLink","none");}
else{setDivDisplay("oldSiteLink","block");setDivDisplay("newSiteLink","none");}}
function onForceLoginAttemptDone(isLoggedIn,criticalError){hideWaiter();app.logMessage('Trying to login without confirm...Ok, isLoggedIn='+isLoggedIn+' criticalErrorReceived='+criticalError);if(criticalError){return;}
var pingInfo=authServer.sendPing(true);if(pingInfo.valid){if(authMain.isLoggedIn()){app.logMessage("User already is logged in");}
else{app.logMessage("First run processAuth from onLauncherUpdated");authMain.processAuth();}}
else{operatorFrame.showServerError();}
authServer.startPings();}
function onLauncherUpdated(){app.logMessage("Launcher updated");setDivDisplay("launcherUpdatePanel","none");setDivDisplay("newsMainDiv","block");updateManager.restoreDownloadIndicators();postLauncherUpdateInitialization();}
function updateGameData(){app.logMessage("updateGameData");if(currentState==States.Hide||currentState==States.Ready)
{updateManager.startUpdateContent();}
else
updateMainButton();statistic.pushEvent(EventTypes.DOWNLOADING);}
function onMainWindowClosing(wnd){statistic.sendEvents();}
function onSaveOptionsClick(element){if(element.className!="roundBtn disabled"){var alwaysUpdateCheck=document.getElementById("alwaysUpdateCheckOption");launcherSettings.updateWithoutPrompt=alwaysUpdateCheck.checked;var minimizeToTrayCheck=document.getElementById("minimizeToTrayOption");launcherSettings.minimizeToTaskBar=!minimizeToTrayCheck.checked;var playSoundOption=document.getElementById("playSoundOption");launcherSettings.playSound=playSoundOption.checked;closeOptions(true,true);}}
function closeOptions(saveBeforeClose,dontHide){if(saveBeforeClose)
saveSettings();if(videoSettings){videoSettings.deleteLater();videoSettings=null;}
document.getElementById("saveButtonLabel").className="roundBtn disabled";if(!dontHide)
dlgMan.CloseDialog("optionsPopup");}
function saveSettings(){if(changedVideoSetts&&videoSettings){var selbox=document.getElementById("screenResolutionSelect");var curValues;eval("curValues="+selbox.value);curValues.fullScreen=!document.getElementById("fullScreenCheck").checked;curValues.quality=parseInt(document.getElementById("graphicsQualitySelect").value);videoSettings.saveValues(curValues);changedVideoSetts=false;}
var settsFileName=app.expandString("{UserDataStorage}/{ApplicationName}.settings");saveFileContent(settsFileName,launcherSettings);}
function settingsChanged(){document.getElementById("saveButtonLabel").className="roundBtn";}
function videoSettingsFSChange(element){processVideoSettingsFS(element.checked);videoSettingsChanged();}
function processVideoSettingsFS(fullScreen){var combo=document.getElementById("screenResolutionSelect");combo.disabled=fullScreen;}
function videoSettingsChanged(){changedVideoSetts=true;settingsChanged();}
function setVerifyVisible(visible){}
function loadInfo(){var infoFileName=app.expandString("{UserDataStorage}/{ApplicationName}.info");var infoObject=loadFileContent(infoFileName,{isObject:true});if(infoObject.valid){mergeObjectProperties(launcherMainInfo,infoObject.data);delete launcherMainInfo.langCode;}}
function saveInfo(){var infoFileName=app.expandString("{UserDataStorage}/{ApplicationName}.info");delete launcherMainInfo.langCode;return saveFileContent(infoFileName,launcherMainInfo);}
function loadAuth(){var authFileNameOld=app.expandString("{UserDataStorage}/{ApplicationName}");app.logDebug("ModulePath: "+app.expandString("{ModulePath}"));var ID=app.getHash([app.expandString("{ModulePath}")]);var authFileNameNew=authFileNameOld+"_"+ID;var authFileExt=".auth";var params={isObject:true,encoding:"cipheredBase64"};var authObject=loadFileContent(authFileNameNew+authFileExt,params);if(!authObject.valid)
authObject=loadFileContent(authFileNameOld+authFileExt,params);if(authObject.valid)
authMain.loadAuthData(authObject.data);else
authMain.loadAuthData();}
function saveAuth(cache){var ID=app.getHash([app.expandString("{ModulePath}")]);var authFileName=app.expandString("{UserDataStorage}/{ApplicationName}");return saveFileContent(authFileName+"_"+ID+".auth",cache,{encoding:"cipheredBase64"});}
function changeButtonState(element,state){var img=getLocalizedString(element.id,"src");var regexp=/\{state\}/;element.src=img.replace(regexp,state);}
function changeOptionsButtonState(){document.getElementById("optionsButton").className=dlgMan.Frames.length>0?"titlebarButton disabled":"titlebarButton";}
function showWaiter(text,throbberState,minWidth,prefix){if(inClosingState)
return;if(!prefix)
prefix="";dlgMan.ShowDialog(prefix+"httpWaitDiv");var width=245;if(!throbberState)
throbberState=WaitThrobberStates.Normal;var throbber=document.getElementById(prefix+"waitThrobber");switch(throbberState){case WaitThrobberStates.Normal:throbber.style.display="inline-block";break;case WaitThrobberStates.ToLeft:throbber.style.display="inline-block";break;case WaitThrobberStates.Hide:throbber.style.display="none";width=320;break;}
var waitText=document.getElementById(prefix+"httpWaitText");if(minWidth)
waitText.style.minWidth=minWidth+"px";else
waitText.style.minWidth="";fitTextToElement(waitText,text,width,160,20);}
function hideWaiter(){if(inClosingState)
return;dlgMan.CloseDialog("httpWaitDiv");}
function closeBtnClick(){if(gameStarted){minimizeClick();}
else{if(!inClosingState)
if(updateManager!=null)updateManager.onCloseClick();closeClick();}}
function closeClick(){if(inClosingState)
return;launcherWindow.close();}
function minimizeClick(element){app.minimizeToTray();}
var eulaData={_onAccept:null,_onDiscard:null,_checkAggrement:false,_checkAge:false,_checkPrivacy:false,setup:function(onAccept,onClose){this._onAccept=(typeof onAccept==='function')?onAccept:null;this._onDiscard=(typeof onClose==='function')?onClose:null;},reset:function(){this._onAccept=null;this._onDiscard=null;this._checkAggrement=false;this._checkAge=false;this._checkPrivacy=false;},invokeAccept:function(){if(this._onAccept!==null){this._onAccept();}},invokeDiscard:function(){if(this._onDiscard!==null){this._onDiscard();}},ready:function(){return(this._checkAge===true)&&(this._checkAggrement===true)&&(this._checkPrivacy===true);}};function _eulaPopupInit(){var eulaIFrame=document.getElementById("eulaPage");eulaIFrame.src="eula-"+langInfo.langCode+".html";var ageCb=document.getElementById("eulaAcceptAge");var agreeCb=document.getElementById("eulaAcceptAgreement");var privacyCb=document.getElementById("eulaAcceptPrivacy");ageCb.checked=eulaData._checkAge;agreeCb.checked=eulaData._checkAggrement;privacyCb.checked=eulaData._checkPrivacy;var acceptBtn=document.getElementById("eulaButtonAccept");acceptBtn.className="roundBtn disabled";}
function eulaPopupShow(reset,onAccept,onDiscard){if(reset===true){eulaData.reset();};eulaData.setup(onAccept,onDiscard);_eulaPopupInit();dlgMan.ShowDialog("eulaPopup");}
function eulaPopupAccept(){if(eulaData.ready()!==true)
return;dlgMan.CloseDialog("eulaPopup");eulaData.invokeAccept();}
function eulaPopupDiscard(){dlgMan.CloseDialog("eulaPopup");eulaData.invokeDiscard();}
function eulaPopupChanged(){var ageCb=document.getElementById("eulaAcceptAge");var agreeCb=document.getElementById("eulaAcceptAgreement");var privacyCb=document.getElementById("eulaAcceptPrivacy");eulaData._checkAge=ageCb.checked;eulaData._checkAggrement=agreeCb.checked;eulaData._checkPrivacy=privacyCb.checked;var acceptBtn=document.getElementById("eulaButtonAccept");var ready=eulaData.ready();if(ready===true){acceptBtn.className="roundBtn";}else{acceptBtn.className="roundBtn disabled";}}
function getHTMLErrorText(error,info){getErrorText(error,info);var errCode=error.errorCode;if(errCode<0){info.textID="REQ_ERR_SERVER_UNREACHABLE";info.solutionID="SOL_HTTP_CONNECTION";}
else if(errCode>0&&errCode<100){info.textID="ERR_HTTP_CONNECTION";info.solutionID="SOL_HTTP_CONNECTION";}
else if(errCode>100&&errCode<200){info.textID="ERR_HTTP_PROXY";info.solutionID="SOL_HTTP_PROXY";}
else if(errCode>200&&errCode<300){if(errCode==299&&error.statusCode==400){info.textID="ERR_HTTP_CANT_GET_USERDATA";info.solutionID="SOL_HTTP_TRY_AGAIN";}
else{info.textID="ERR_HTTP_CONTENT";info.solutionID="SOL_HTTP_CONTENT";}}
else if(errCode>300){info.textID="ERR_HTTP_PROTO";}}
function getSSLErrorText(error,info){getErrorText(error,info);}
function getErrorText(error,info){if(error.errorType&&error.errorType!="")
info.textID="ERR_"+error.errorType;else
info.text=error.errorMessage;if(error.errorType=="FILE_WAIT")
info.solutionID="SOL_FILE_WAIT";else if(error.errorType=="NO_DISK_SPACE")
info.solutionID="SOL_NO_DISK_SPACE";else if(error.errorType=="FILE_WRITE_ERROR")
info.solutionID="SOL_FILE_WRITE_ERROR";else if(error.errorType=="PATCH_ORDER_ERROR")
info.solutionID="SOL_PATCH_ORDER_ERROR";else if(error.solutionID&&error.solutionID!="")
info.solutionID=error.solutionID;}
function getErrorInfo(error,info){if(error.nested)
getErrorInfo(error.nested,info);var curInfo={text:"",textID:"",solutionID:""};if(error.errorType=="HTTP")
getHTMLErrorText(error,curInfo);else if(error.errorType=="SSL")
getSSLErrorText(error,curInfo);else
getErrorText(error,curInfo);if(curInfo.textID!=""&&info.textIDs.indexOf("|"+curInfo.textID+"|")<0){info.textIDs+="|"+curInfo.textID+"|";curInfo.text=getLocalizedString(curInfo.textID);}
if(curInfo.text!=""){if(info.text!="")
info.text=curInfo.text+"<br/>"+info.text;else
info.text=curInfo.text;}
if(curInfo.solutionID!=""&&info.solIDs.indexOf("|"+curInfo.solutionID+"|")<0){info.solIDs+="|"+curInfo.solutionID+"|";curInfo.solution=getLocalizedString(curInfo.solutionID);if(info.solution!="")
info.solution=curInfo.solution+"<br/>"+info.solution;else
info.solution=curInfo.solution;}}
function showErrorMessage(error,onClose){hideWaiter();var el=document.getElementById("errorMessageText");var details;var info={textIDs:"",solIDs:"",text:"",solution:""};if(typeof(error)=="object"){details=error.errorMessage;getErrorInfo(error,info);if(error.noDetails)
details="";if(error.errorTitle&&error.errorTitle!=""){var errText="<strong>"+error.errorTitle+"</strong>";if(error.noDetails)
info.text=errText+"<br/>"+info.text;else
info.text=errText;}
el.innerHTML=info.text;el=document.getElementById("errorSolution");if(info.solution&&info.solution!=""){el.style.display="table-row";el=document.getElementById("errorSolutionText");el.innerHTML=info.solution;}
else{el.style.display="none";}}
else{info.text=error;el.innerHTML=error;el=document.getElementById("errorSolution");el.style.display="none";}
if(usingMailRuGC){var errorType=MAILRU_GC_STATES.MGC_ERROR;var size=0;if(error.errorType=="NO_DISK_SPACE")
{if(error.errorDetail){size=error.errorDetail;app.logDebug("Needed Size: "+error.errorDetail+" "+typeof(error.errorDetail));}
errorType=MAILRU_GC_STATES.MGC_NO_ENOUGH_DISK_SPACE;}
var res_text="<html>"+info.text+"</html>";app.writeMailRuState(errorType,res_text,0,0,size);closeClick();return;}
var detailsEl=document.getElementById("errorMessageDetails");var detailsPanel=document.getElementById("errorMessageDetailsPanel");detailsPanel.style.display="none";if(details&&details!=""){detailsEl.innerHTML=details;el=document.getElementById("errorMessageSwitch");el.style.display="block";var imgEl=document.getElementById("errorMessageSwitchImage");imgEl.src="images/arrowRight.png";}
else{el=document.getElementById("errorMessageSwitch");el.style.display="none";}
dlgMan.CloseDialog("errorMessage");dlgMan.ShowDialog("errorMessage",onClose);centerElement("errorMessage");if(authServer&&authServer.offline)
operatorFrame.showServerOffline();}
function onErrorMessageSwitch(){var detailsEl=document.getElementById("errorMessageDetailsPanel");var imgEl=document.getElementById("errorMessageSwitchImage");if(detailsEl.style.display=="none"){detailsEl.style.display="block";imgEl.src="images/arrowDown.png";}
else{detailsEl.style.display="none";imgEl.src="images/arrowRight.png";}}
function showMessageBox(title,text,onClose){dlgMan.CloseDialog("messageBoxWnd");document.getElementById("messageBoxWndTitle").innerHTML=title;document.getElementById("messageBoxWndText").innerHTML=text;dlgMan.ShowDialog("messageBoxWnd",onClose);centerElement("messageBoxWnd");}
function getLocalizedString(id,optionalType,defaultValue){res=app.getLocalizedString(id,optionalType);if(res==id&&defaultValue!=undefined)
res=defaultValue;return res;}
function localizeSkin(){var regexp=/\{state\}/;var htmlValues=app.getLocalizedHtmlValues();for(var i=0;i<document.all.length;i++){var node=document.all[i];var id=node.id;if(id&&id!=""){for(var type in htmlValues){var ids=htmlValues[type];if(ids[id])
node[type]=ids[id].replace(regexp,"normal");}}}
updateMainButton();}
function setDownloadVisible(visible){document.getElementById("mainTabContent").style.display=visible?"block":"none";}
function setDownloadWaitVisible(visible){document.getElementById("downloadWaitPanel").style.display=visible?"block":"none";}
function fitTextToElement(elem,text,maxWidth,maxHeight,maxFont){elem.innerHTML=text;elem.style.fontSize=maxFont+'px';while(elem.offsetHeight>maxHeight||elem.offsetWidth>maxWidth){elem.style.fontSize=(--maxFont)+'px';if(maxFont<11)
break;}}
function setMainButtonText(elem,text){fitTextToElement(elem,text,110,83,20);}
function updateMainButton(processState,disable){enableRepairButton(false);if(processState)
currentState=processState;var hide=gameStarted;if(updateManager==null||updateManager.isRepair||inClosingState)
hide=true;var text="";switch(currentState){case States.Hide:hide=true;break;case States.PausingBeforeStop:disable=true;case States.Download:text=getLocalizedString("mainButtonPauseDownload");break;case States.PausingBeforeDownload:disable=true;case States.Paused:text=getLocalizedString("mainButtonResumeDownload");break;case States.Ready:text=getLocalizedString("mainButtonPlay");if((globalServerStatusChecker.GetStatus()==GlobalServerStatuses.CHECKING||globalServerStatusChecker.GetStatus()==GlobalServerStatuses.MAINTENANCE||isMaintenance)&&!qaMode){hide=true;break;}
dlComplete=(updateManager.downloaded);if(dlComplete){enableRepairButton(true);statistic.pushEvent(EventTypes.READY_PLAY);}
if(!authMain.isLoggedIn()){disable=true;}
break;}
app.logMessage("updateMainButton: state="+currentState+" hide="+hide);var mainButtonWrap=document.getElementById("mainButtonWrap");if(hide){enableRepairButton(false);mainButtonWrap.style.display="none";}
else{var mainButton=document.getElementById("mainButton");mainButtonWrap.style.display="block";setMainButtonText(mainButton,text);if(updateManager.downloaded){if(authMain.isLoggedIn())
mainButtonWrap.title="";else
mainButtonWrap.title=getLocalizedString("pleaseLoginMainTooltip");}
else{mainButtonWrap.title=getLocalizedString("pleaseWaitMainTooltip");}
mainButton.className=disable?"disabled":"";}}
function expandLocaleString(str,params){for(var i=0;i<params.length;i+=2){var regexp=params[i];str=str.replace(regexp,params[i+1]);}
return str;}
function sendStatInfo(cmd,prms){var req="?action="+cmd+"&hostid="+hostId;for(var name in prms)
req+="&"+name+"="+encodeURIComponent(prms[name]);authServer.request(req,{asyncRequest:false});}
function sendDownloadInfo(info,fromPatchComplete){var cmd=null;var status=null;if(fromPatchComplete){cmd="l_dend";status=StatStatuses.COMPLETE;}
else{switch(info.state){case downloadState.START:case downloadState.DOWNLOAD:if(lastSendStatFileName!=info.download.getMetafileUrl()){cmd="l_dstart";lastSendStatFileName=info.download.getMetafileUrl();}
break;case downloadState.FAILURE:cmd="l_dend";status=StatStatuses.DOWNLOAD_FAILURE;break;case downloadState.STOP:cmd="l_dend";status=StatStatuses.STOPPED;break;case downloadState.DOWNLOADSTALLED:cmd="l_dend";if(info.download.getLastFailure()>downloadFailure.NONE)
status=StatStatuses.DOWNLOAD_FAILURE;else
status=StatStatuses.STOPPED;break;}}
if(cmd){var pack=info.download.getMetafileUrl();var pos=pack.lastIndexOf("/");if(pos>=0)
pack=pack.substring(pos+1);var version="";for(pos=pack.lastIndexOf(".");pos>0;pos--){var curChar=pack.charAt(pos-1);if(isNaN(curChar))
break;version=curChar+version;}
if(version=="")
version="-1";var prms={"package":pack,"version":version};if(status!=null)
prms.status=status;sendStatInfo(cmd,prms);}}
function checkJsonResponse(data){if(!data)
return false;var pos1=data.indexOf("<");var pos2=data.indexOf("{");if(pos1<0)
return(pos2>=0);if(pos2<0)
return false;return pos2<pos1;}
function preparseRefInfo(){var fileName=expandURI(app.getConfig("RefInfoFile",""));if(fileName&&fileName!=""){var fileData=loadFileContent(fileName);if(fileData.valid&&fileData.data&&(""+fileData.data).length>0){var content=""+fileData.data;app.logDebug("ref info: "+content);var part=content.split(" ");muid=encodeURIComponent(part[0]);app.logPrivate("\t muid: "+muid);if(muid&&muid!=""){var rx=/\W/;if(muid.search(rx)>=0)
muid="invalid";app.logDebug("\t validate muid: "+(muid=="invalid"?muid:"ok"));refInfo={"session":muid};var n=1;for(var i=1;i<part.length;i++){if(part[i]!=""){var subParam=part[i].split(':');var key;var value;if(subParam.length==1){key="param"+(n++);value=part[i];}
else{key=subParam[0];value=subParam[1];}
refInfo[key]=encodeURIComponent(value);app.logDebug("\t "+key+": "+refInfo[key]);}}
return true;}}}
refInfo=null;muid="";return false;}
function sendRefInfo(eventName,addPrms){}
var g_lastErrorTipElement=null;function showErrorTip(elementId,text,offsetX,offsetY){if(!offsetX)
offsetX=-4;if(!offsetY)
offsetY=4;var tipElement=document.getElementById("errorTipWnd");var elem;if(elementId)
elem=document.getElementById(elementId);g_lastErrorTipElement=elem;if(elem)
{markInput(elem,InputMarks.Error);var toolTipSibling=elem.nextElementSibling;toolTipSibling.className="p_error p_error__red";toolTipSibling.style.display="block";toolTipSibling.firstElementChild.innerHTML=text;}
else{tipElement.style.display="none";}}
function hideErrorTip(element){if(!element||element==g_lastErrorTipElement)
showErrorTip();if(element.tagName=="INPUT")
{var toolTipSibling=element.nextElementSibling;if(toolTipSibling.className=="p_error p_error__red")
{toolTipSibling.style.display="none";}}}
function popupErrorTooltip(inputElementId){var element=document.getElementById(inputElementId);if(element.tagName=="INPUT"&&element.className!="ap_form-input valid")
{var toolTip=element.nextElementSibling;if(toolTip.firstElementChild.innerHTML!=""&&toolTip.style.display=="none"&&toolTip.className=="p_error p_error__red")
{toolTip.style.display="block";}}}
function showToolTip(element,text)
{if(element.tagName=="INPUT"&&element.className!="ap_form-input valid")
{var toolTipSibling=element.nextElementSibling;toolTipSibling.className="p_error p_error__green";toolTipSibling.style.display="block";toolTipSibling.firstElementChild.innerHTML=getLocalizedString(text);}}
function hideToolTip(element)
{if(element.tagName=="INPUT"){var toolTipSibling=element.nextElementSibling;toolTipSibling.style.display="none";}}
function markInput(element,state){var elem=undefined;if(element){if(typeof element=="string"){elem=document.getElementById(element);}
else if(element.tagName=="INPUT"){elem=element;}}
var subclass="";switch(state){case InputMarks.Valid:subclass=" valid";break;case InputMarks.Error:subclass=" error";break;case InputMarks.NoMark:subclass="";break;default:subclass="";break;}
elem.className="ap_form-input"+subclass;}
function setZOrderForErrorTip(newZ){showErrorTip();var tipElement=document.getElementById("errorTipWnd");tipElement.style.zIndex=newZ;}
function onFramesBeforeNavigate(data){var frame=data.getFrame();if(data.getFrameName()=="operatorFrame"){var s1=data.getNewUrl().toLowerCase();var s2=data.getBaseUrl().toLowerCase()+"#";if(s1==s2)
data.accept(false);}}
function urldecode(url){url=decodeURIComponent(url);url=url.replace(/\?/g,"&");url=url.replace(/#/g,"&");var hashParams={};var e,a=/\+/g,r=/([^&;=]+)=?([^&;]*)/g,d=function(s){return s.replace(a," ");},q=url;while(e=r.exec(q))
hashParams[d(e[1])]=d(e[2]);return hashParams;}
function checkDownloadState(){app.logMessage("Check download state");if(updateManager.downloaded){updateMainButton(States.Ready);}
else{updateMainButton(States.Download);}
return updateManager.downloaded;}
function expandString(str){var regexp=/\&amp;/g;str=str.replace(regexp,"&");var searchExp=/{[^}]*/;while(true){var part=searchExp.exec(str);if(part==null||part=="")
break;part=part[0];regexp=new RegExp("\\"+part+"\\}");part=part.substring(1);var value=window;var strParts=part.split(".");var i=0;while(value&&i<strParts.length){value=value[strParts[i]];i++;}
if(!value){value=app.getConfig(part,"")
if(!value||value===""){var expandVar="{"+part+"}";value=app.expandString(expandVar);if(value==expandVar)
value="["+part+"]";}}
else{value=value.toString();}
str=str.replace(regexp,value);}
return str;}
function showEULA(){var url=app.expandString("{AppContentUrl}")+"mainwindow/eula-"+langInfo.langCode+".html";var data=httpRequest(url);var eulaText=data.data;if(!data.valid||!eulaText||eulaText=="")
return null;var md5=app.getHash([eulaText]);if(showEulaOnLaunch!=1&&launcherMainInfo.md5==md5)
return 1;var prms={readonly:true,caption:getLocalizedString("EULA"),isRTF:true,text:eulaText,buttons:[{title:getLocalizedString("EULA_Accept"),code:1},{title:getLocalizedString("EULA_Reject"),code:0}],width:500,height:600};if(showEulaOnLaunch==1){prms.buttons=[{title:getLocalizedString("EULA_OK"),code:1}];}
var result=app.showDialog(prms);if(result==1){launcherMainInfo.md5=md5;saveInfo();}
return result;}
function onMergeInfoClick(){showMergeInfo();}
function showMergeInfo(){var url=app.expandString("{AppContentUrl}")+"mainwindow/mergeinfo-"+langInfo.langCode+".html";var data=httpRequest(url);var eulaText=data.data;if(!data.valid||!eulaText||eulaText=="")
return null;var prms={readonly:true,caption:getLocalizedString("MergeInfoTitle"),isRTF:true,text:eulaText,buttons:[{title:getLocalizedString("MergeInfoAccept"),code:1}],width:500,height:600};return app.showDialog(prms);}
function mainButtonClick(){if(inClosingState)
return;switch(currentState){case States.Download:updateMainButton(States.PausingBeforeStop,true);showWaiter(getLocalizedString("waitForPause"));app.pausePatching();statistic.pushEvent(EventTypes.PAUSED);updateManager.onMainButtonClick(States.Download);break;case States.Paused:updateMainButton(States.PausingBeforeDownload,true);showWaiter(getLocalizedString("waitForDownload"));app.resumePatching();statistic.pushEvent(EventTypes.RESUMED);updateManager.onMainButtonClick(States.Paused);break;case States.Ready:if(authMain.isLoggedIn()){launch();}
else
{showMessageBox(getLocalizedString("pleaseLoginMainTitle"),getLocalizedString("pleaseLoginMainTooltip"));}
break;}}
function onShowEULAClick(){showEULA();}
function showSettingsWindow(){if(dlgMan.Frames.length==0&&populateSettings())
dlgMan.ShowDialog("optionsPopup");}
function populateSettings(){if(!videoSettings)
videoSettings=app.getVideoSettings();if(videoSettings){var resolutions=videoSettings.getResolutions();var resString="Got resolutions list: \r\n";for(var i=0;i<resolutions.length;i++){resString+="w="+resolutions[i].x;resString+=", h="+resolutions[i].y+"\r\n";}
app.logMessage(resString);var curSetts=videoSettings.loadValues();var selbox=document.getElementById("screenResolutionSelect");var curOptJson="{'x':"+curSetts.x+",'y':"+curSetts.y+"};";for(var i=0;i<resolutions.length;i++){var opt=resolutions[i].x+" x "+resolutions[i].y;var jsonOpt="{'x':"+resolutions[i].x+",'y':"+resolutions[i].y+"};";selbox.options[i]=new Option(opt,jsonOpt);selbox.options[i].selected=(jsonOpt==curOptJson);}
document.getElementById("fullScreenCheck").checked=!curSetts.fullScreen;selbox=document.getElementById("graphicsQualitySelect");for(var i=1;i<4;i++){var optName=getLocalizedString("graphicsQuality"+i);selbox.options[i-1]=new Option(optName,i);selbox.options[i-1].selected=(i==curSetts.quality);}
processVideoSettingsFS(!curSetts.fullScreen);}
changedVideoSetts=false;var element=document.getElementById("alwaysUpdateCheckOption");element.checked=launcherSettings.updateWithoutPrompt;element=document.getElementById("minimizeToTrayOption");element.checked=!launcherSettings.minimizeToTaskBar;element=document.getElementById("playSoundOption");element.checked=launcherSettings.playSound;return(videoSettings!==null);}
var startingBlinkTimer=null;function finalizeStarting(hide){if(startingBlinkTimer){clearInterval(startingBlinkTimer);startingBlinkTimer=null;}
app.logDebug("Hide gameStarting waiter");dlgMan.CloseDialog("gameStart_httpWaitDiv");if(hide)
tryGameStart=false;else
minimizeClick();}
function onGameProcessExit(info){tryGameStart=false;gameStarted=false;setDivDisplay("authInfoBlanket","none");setDivDisplay("optionsGraphicsSection","block");updateMainButton();app.restoreMainWindow();operatorFrame.refreshFrame();if(!usingMailRuGC){launcherWindow.show();launcherWindow.bringToFront();}
statistic.pushEvent(EventTypes.RETURN_FROM_GAME);finalizeStarting(true);if(!info)
info={"error":true,"errorType":"EXECUTE","errorMessage":getLocalizedString("gameStartFailed")};if(info.error){if(launchedModule=="Defenders")
info.errorTitle=getLocalizedString("defendersExecErrorTitle");showErrorMessage(info);}}
function blinkOnStarting(){var txt=getLocalizedString("gameStarting");var waitEl=document.getElementById("httpWaitDiv");var intervalNum=waitEl.intervalNum+1;if(intervalNum>3)
intervalNum=0;var points="";for(var i=0;i<intervalNum;i++)
points+=".";showWaiter(txt+points,WaitThrobberStates.ToLeft,140,"gameStart_");waitEl.intervalNum=intervalNum;}
function checkPingOnLaunch(){var pingInfo=authServer.sendPing(true);if(pingInfo.valid){if(!pingInfo.data||!pingInfo.data.response){delete pingInfo.valid;pingInfo.error=true;pingInfo.errorType="HTTP";pingInfo.errorMessage=getLocalizedString("REQ_ERR_WRONG_ANSWER");authMain.refreshUserData();}}
else{pingInfo.errorTitle=getLocalizedString("REQ_ERR_SERVER_UNREACHABLE");}
return pingInfo;}
function launch(){if(!updateManager.downloaded||tryGameStart)
return;if(!authMain.isLoggedIn()){app.logMessage('Trying to login without confirm...');showWaiter(getLocalizedString("httpWaitText","innerHTML"));authMain.tryToLoginWithoutConfirm(onForceLoginAttemptDone);return;}
app.logMessage("Trying to launch game");if(usingMailRuGC&&!onlyUpdateMode)
app.writeMailRuState(MAILRU_GC_STATES.MGC_INITIALIZING,getLocalizedString("launcherInitialization","innerHTML"),3,5);tryGameStart=true;var stopExec=false;var pingNum=1;var firstPingTime=(new Date()).valueOf();app.logDebug("Show gameStarting waiter");var txt=getLocalizedString("gameStarting");showWaiter(txt,WaitThrobberStates.ToLeft,140,"gameStart_");startingBlinkTimer=setInterval(blinkOnStarting,500);if(authMain.isNeedRelogin()){app.logMessage("Relogin on launch game. Change server value to empty");authMain.refreshUserData(true);if(!authMain.isLoggedIn())
stopExec=true;}
while(!stopExec){app.logMessage("Ping in launch: "+pingNum);pingNum++;var pingInfo=checkPingOnLaunch();if(pingInfo.error){showErrorMessage(pingInfo);stopExec=true;}
else{if(pingInfo.data.response.ok==1)
break;if(pingInfo.data.response.ec==2){var curPingTime=(new Date()).valueOf();if(curPingTime-firstPingTime>authServer.checkPingOnLaunchInterval){var err=getLocalizedString("ERR_CHECK_PING_ON_LAUNCH");err+="<br/>";err+=getLocalizedString("SOL_CHECK_PING_ON_LAUNCH");showErrorMessage(err);stopExec=true;break;}
sleep(500);}
else{showErrorMessage(getLocalizedString("AGG_EC_"+pingInfo.data.response.ec));stopExec=true;}}}
if(stopExec){finalizeStarting(true);return;}
updateManager.dontUpdateDefenders=true;if(updateManager.inUpdateDefenders)
launchAfterCheckUpdates(CheckUpdateResults.NoUpdates);else
updateManager.checkForUpdates(launchAfterCheckUpdates);}
function launchAfterCheckUpdates(result){var resultStr="No new updates";if(result==CheckUpdateResults.Error)
resultStr="There were some errors till check for updates";else if(result==CheckUpdateResults.HasContentUpdates)
resultStr="There are new content updates!";else if(result==CheckUpdateResults.HasLauncherUpdates)
resultStr="There are new launcher updates!";app.logMessage("[launchAfterCheckUpdates] check updates result: "+resultStr);if(result==CheckUpdateResults.NoUpdates){if(app.getConfig("OverrideTutorialFallthrough","False")!="True"){launchedModule=(authMain.getFraction()==-1)?"PW_Game":"Castle";}
else
{launchedModule="Castle";}
var appExeInfo=app.getExecutableName(launchedModule);if(appExeInfo.Canceled){app.logMessage("Cancel launching: appExeInfo.Canceled");onGameProcessExit({"canceled":true});return;}
if(usingMailRuGC&&!onlyUpdateMode)
app.writeMailRuState(MAILRU_GC_STATES.MGC_INITIALIZING,getLocalizedString("launcherInitialization","innerHTML"),4,5);if(launcherMainInfo.LastExeName!=appExeInfo.Name){launcherMainInfo.LastExeName=appExeInfo.Name;saveInfo();}
var arguments=prepareExecutionArguments(appExeInfo.Arguments);if(!launcherMainInfo.notFirstLaunch){sendRefInfo("pw_exlogin",{"hostid":hostId,"auid":authMain.getAUID()});launcherMainInfo.notFirstLaunch=true;saveInfo();}
statistic.pushEvent(EventTypes.START_PLAY);statistic.sendEvents();gameStarted=true;setDivDisplay("authInfoBlanket","block");app.startProcess(appExeInfo.Application,appExeInfo.WorkingDirectory,arguments);updateMainButton();app.logMessage("Game started");setDivDisplay("optionsGraphicsSection","none");}
else{finalizeStarting(true);if(result==CheckUpdateResults.Error){var error=updateManager.checkUpdatesError;error.errorTitle=getLocalizedString("ERR_CHECK_UPDATE_TITLE");showErrorMessage(updateManager.checkUpdatesError);return;}
processNewUpdates(result);}}
function onGameProcessStart(){app.logMessage("Module "+launchedModule+" was started.");if(usingMailRuGC){app.writeMailRuState(MAILRU_GC_STATES.MGC_GAME_STARTED,"");app.writeMailRuState(MAILRU_GC_STATES.MGC_DISABLE_WRITE_STATE,"");}
else{app.logMessage("Closing launcher.");closeClick();}}
function processNewUpdates(result){if(launcherSettings.updateWithoutPrompt){startUpdate(result);}
else{var element=document.getElementById("alwaysUpdateCheck");element.checked=launcherSettings.updateWithoutPrompt;dlgMan.ShowDialog("needUpdate");}}
function onNeedUpdateButton(){dlgMan.CloseDialog("needUpdate");var element=document.getElementById("alwaysUpdateCheck");launcherSettings.updateWithoutPrompt=element.checked;saveSettings();startUpdate();}
function startUpdate(result){if(!result)
result=updateManager.checkUpdatesResult;if((result&CheckUpdateResults.HasLauncherUpdates)==CheckUpdateResults.HasLauncherUpdates){updateMainButton(States.Hide);setDivDisplay("MainInfoPanel","none");operatorFrame.hideFrame();updateLauncher();}
else if((result&CheckUpdateResults.HasContentUpdates)==CheckUpdateResults.HasContentUpdates){updateMainButton(States.Hide);app.logMessage("Start update content after check for updates");updateGameData();}}
function onDocumentEnterPressed(){if(isMaintenance&&!qaMode)
return;if(updateManager.downloaded&&currentState==States.Ready&&authMain.isLoggedIn())
launch();}
function checkPressedKey(event){if(event.keyCode==13||event.keyCode==27){var dlg=dlgMan.GetActiveDialog();if(dlg){if(dlg.onCommandButton)
dlg.onCommandButton(event.keyCode);else if(event.keyCode==27){dlgMan.CloseDialog(dlg.id);}
return;}
else if(authMain.activePwc&&!authMain.isLoggedIn()){authMain.activePwc.onCommandButton(event.keyCode);return;}
else if(authMain.activeGmg&&!authMain.isLoggedIn()){authMain.activeGmg.gmgLoginWndCmdButton(event.keyCode);return;}}
if(event.keyCode==13){app.processScriptEnterKeyEvent();return false;}
return true;}
function errorMessageDialogCmdButton(keyCode){if(keyCode==13||keyCode==27)
dlgMan.CloseDialog("errorMessage");}
function messageBoxWndCmdButton(keyCode){if(keyCode==13||keyCode==27)
dlgMan.CloseDialog("messageBoxWnd");}
function onNeedToIgnoreSSLQuestion(question){var text=getLocalizedString("ignoreSSLQuestionWarning");text+="<b>"+question.getHost()+"</b><br/>";text+=getLocalizedString("ignoreSSLQuestionText");var el=document.getElementById("ignoreSSLQuestionText");el.innerHTML=text;el=document.getElementById("ignoreSSLQuestionDetailsPanel");el.style.display="none";el=document.getElementById("ignoreSSLQuestionDetails");el.innerHTML=question.getErrorMessage();el=document.getElementById("ignoreSSLQuestionSwitchImage");el.src="images/arrowRight.png";el=document.getElementById("ignoreSSLQuestion");el.questionObject=question;if(usingMailRuGC||(app.getConfig("IgnoreSSLErrors","False")=="True"))
{onNeedToIgnoreSSLAnswered(true);return;}
dlgMan.ShowDialog("ignoreSSLQuestion");}
function onNeedToIgnoreSSLAnswered(state){var el=document.getElementById("ignoreSSLQuestion");el.questionObject.accept(state);dlgMan.CloseDialog("ignoreSSLQuestion");app.needToIgnoreSSLAnswered();}
function onIgnoreSSLQuestionSwitch(){var detailsEl=document.getElementById("ignoreSSLQuestionDetailsPanel");var imgEl=document.getElementById("ignoreSSLQuestionSwitchImage");if(detailsEl.style.display=="none"){detailsEl.style.display="block";imgEl.src="images/arrowDown.png";}
else{detailsEl.style.display="none";imgEl.src="images/arrowRight.png";}}
function ignoreSSLQuestionCmdButton(keyCode){if(keyCode==13)
onNeedToIgnoreSSLAnswered(true);else if(keyCode==27)
onNeedToIgnoreSSLAnswered(false);}
function setDivDisplay(name,state){var element=document.getElementById(name);if(element)
element.style.display=state;else
app.logWarning("setDivDisplay: Element '"+name+"' not found");}
function centerElement(name){var el=document.getElementById(name);if(el){el.style.top="50%";el.style.left="50%";var h=el.offsetHeight/2;var w=el.offsetWidth/2;el.style.marginTop="-"+h+"px";el.style.marginLeft="-"+w+"px";}}
function enableRepairButton(state){var el=document.getElementById("verifyButtonLabel");if(updateManager==null||updateManager.inRepair||this.inUpdateDefenders)
state=false;el.className=state?"roundBtn":"roundBtn disabled";}
function checkRepairButtonEnabled(){var el=document.getElementById("verifyButtonLabel");return el.className=="roundBtn";}
function startFullRepair(){if(checkRepairButtonEnabled()){dlgMan.CloseDialog("optionsPopup");updateManager.startRepair();}}
function supportLinkClick(){var url=app.getConfig("PwSupportUrl","http://support.playpw.com/");openExternalBrowser(url);}
function playPwLinkClick(){var url=app.getConfig("PwUrl","http://www.playpw.com");openExternalBrowser(url);}
function onExecuteAddon(name){app.logMessage("ExecuteAddon action '"+name+"'");switch(name){case"defenders":var defendersExe=app.expandString("{Defenders.Application}");var defendersWD=app.expandString("{Defenders.WorkingDirectory}");var defendersServer=app.expandString("{Defenders.PwdServer}");var arguments=prepareExecutionArguments();arguments+=" --pwdserver "+defendersServer;app.logMessage("Trying to start Defenders...");launchedModule="Defenders";app.startProcess(defendersExe,defendersWD,arguments);break;case"defenders-last-error":if(updateManager.LastDefendersError){var error=updateManager.LastDefendersError;error.errorTitle=getLocalizedString("defendersUpdateErrorTitle");showErrorMessage(error);}
break;case"defenders-install":updateManager.startDownloadAddon();launcherSettings.defendersInstalled=true;saveSettings();break;}}
function prepareExecutionArguments(additionalArguments,pwdServer){var arguments="--snid pw --snuid "+authMain.getAUID();app.logMessage("Prepare command line: server = '"+authMain.getServer()+"'");var server=authMain.getServer();if(server)
arguments+=" --server "+server;arguments+=" --sntoken "+'\"'+authMain.getToken()+'\" ';var secret=authMain.getSecret();if(secret)
arguments+=" --secret \""+secret+"\" ";if(isLoginQueueEnabled())
arguments+=" --needqueue ";arguments+=" ver "+protocolVersion;if(additionalArguments&&additionalArguments!="")
arguments+=" "+additionalArguments;app.logDebug("Game command line arguments: "+arguments);return arguments;}
function browseToAccountPage(){var url=app.getConfig("PwAccountURL","");if(url!="")
openExternalBrowser(url);}
function onLauncherClosing(){hideWaiter();showWaiter(getLocalizedString("waitForClosing"));inClosingState=true;updateMainButton();var closeBtn=document.getElementById("closeButton");closeBtn.className="titlebarButton disabled";closeBtn.style.cursor="default";if(operatorFrame!=null)operatorFrame.onLauncherClosing();if(updateManager!=null)updateManager.onLauncherClosing();}
function disableLogoutElements(){hideElementById('Logout');}
function disableWebBillingElements(){hideElementById('lkEnter');}
function hideElementById(id){var el=document.getElementById(id);if(el)
el.style.display='none';}
function isLoginQueueEnabled(){return app.getConfig("UseLoginQueue","")=="1";}
function getUrlParam(paramName,url){var result={};url.replace(/([^?=&]+)(?:[&#]|=([^&#]*))/g,function(match,key,value){if(key.indexOf("[]")!==-1){key=key.replace(/\[\]$/,"");if(!(result[key])){result[key]=new Array();}
result[key].push(value);}else{result[key]=value||1;}});if(result[paramName]){return result[paramName];}else{return'';}};