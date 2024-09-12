
var SSErrors={NOT_A_REGISTERED_AP_USER:8,AGGREGATOR_LOGIN_FAIL:9,AGGREGATOR_JOIN_USER_EXISTS:35,AGGREGATOR_MERGE_FAIL:36,PWC_BAD_SIGNATURE:71,PWC_ACTIVATION_EXPIRED:74,PWC_RESEND_TOO_OFTEN:82,NOT_A_ALLOWED_AP_USER:400,PWC_ACCOUNT_BAN:910,__Finalizer:-1};var CreateNewWindowActions={ACTION_IGNORE:0,ACTION_CREATE:1,ACTION_RETURN_THIS:2};var authInfoImagesWidth=40;var MAX_VISIBLE_ICONS_COUNT=3;function prepareAvatarUrl(url)
{if(!url||url=="")
url="images/main-login-avatar.png";if(url.toLowerCase().indexOf("odnoklassniki.ru")<0)
return url;var imgData=httpRequest(url,{"useCache":true,"returnAs":ResultPresentation.Base64});if(imgData.valid)
return"data:;base64,"+imgData.data;return"images/default-avatar.png";}
function getAuthErrorText(prefix,ec,defaultTxt)
{var ecTxt=prefix+ec;if(prefix=="AGG_EC_"&&(ec==SSErrors.AGGREGATOR_LOGIN_FAIL||ec==SSErrors.AGGREGATOR_MERGE_FAIL))
{var matches=defaultTxt.match(/code=[0-9]*/);if(matches&&matches.length>0)
{ecTxt=prefix+matches[0];}
else
{if(defaultTxt=="no aggregator properties")
ecTxt=prefix+"NO_AGG_PROPS";}}
var txt=getLocalizedString(ecTxt);if(!txt||txt==""||txt==ecTxt)
{ecTxt="ERR_EMPTY_"+defaultTxt;txt=getLocalizedString(ecTxt);if(!txt||txt==""||txt==ecTxt)
{var title=getLocalizedString(prefix+"UniTitle");if(!title||title==""||title==prefix+"UniTitle")
return defaultTxt;return title+defaultTxt;}}
return txt;}
function AuthMain()
{this.__className="AuthMain";app.logMessage("create AuthMain");this.socNetNoConfirm=[];this.socNetDefs={};this.socNetCookies={};this.isBlocked=false;}
AuthMain.prototype.initializeLoginServiceMode=function()
{var jsonString=app.getJSONNode("Authorization.Modes");var modes;try{modes=JSON.parse(jsonString);}catch(e){app.logWarning("can't parse '"+jsonString+"'");try{modes=app.getAuthorizationModes();}
catch(e){app.logWarning("can't get modes from app");}}
if(modes==undefined||modes==""){showErrorMessage(getLocalizedString("criticalErrorTitle"),closeBtnClick);return;}
else
app.logDebug("modes: \n"+JSON.stringify(modes));var currentMode;var idx;predefinedMode=app.getConfig("AuthMode","");if(refInfo&&predefinedMode==""&&refInfo["authMode"]!=undefined)
predefinedMode=refInfo["authMode"];if(predefinedMode==""&&refInfo&&refInfo["session"]=="gamigo"){predefinedMode="gamigo";}
if(predefinedMode!=""){predefinedMode=predefinedMode.toLowerCase();app.logDebug("[initializeLoginServiceMode] predefined mode = "+predefinedMode);}
var mode;for(mode in modes){if(mode.toLowerCase()==predefinedMode){currentMode=modes[mode];currentMode.name=mode;break;}}
if(!currentMode){for(mode in modes){var validMode=true;if(modes[mode].CmdArguments!="")
{var cmdArgs=modes[mode].CmdArguments.split(" ");for(idx=0;idx<cmdArgs.length;idx++)
{if(app.getCommandLineArgumentIndex(cmdArgs[idx])==-1)
{validMode=false;break;}}}
if(validMode)
{currentMode=modes[mode];currentMode.name=mode;break;}}}
this.currentLoginServiceMode=currentMode;app.logMessage("current mode:"+JSON.stringify(this.currentLoginServiceMode));}
AuthMain.prototype.initialize=function()
{this.initializeLoginServiceMode();var allowedToLogin=this.currentLoginServiceMode.ServicesToLogin.split(COMMA_SEPARATED_RE);var allowedToMerge=this.currentLoginServiceMode.ServicesForMerge.split(COMMA_SEPARATED_RE);var sns=allowedToLogin.union(allowedToMerge);if(sns.length>0)
{this.socNetDefs={};this.socNetNames=[];app.logMessage("Initialized login services: "+sns.toString());for(var i=0;i<sns.length;i++)
{var sn=sns[i];var def=null;switch(sn)
{case AuthNetworks.FACEBOOK:def=new FbAuth(this);break;case AuthNetworks.ODNOKLASSNIKI:def=new OkAuth(this);break;case AuthNetworks.VKONTAKTE:def=new VkAuth(this);break;case AuthNetworks.PW_CONNECT:def=new PwcAuth(this);break;case AuthNetworks.AERIA:def=new AeriaAuth(this);break;case AuthNetworks.STEAM:def=new SteamAuth(this);break;case AuthNetworks.MAILRU:def=new MailRuAuth(this);break;case AuthNetworks.MASSIVE:def=new MassiveAuth(this);break;case AuthNetworks.ARC:def=new ArcAuth(this);break;case AuthNetworks.ZZIMA:def=new ZzimaAuth(this);break;case AuthNetworks.GAMIGO:def=new GamigoAuth(this);break;case AuthNetworks.DRAUGAS:def=new DltAuth(this);break;}
if(def)
{this.socNetDefs[sn]=def;this.socNetNames[this.socNetNames.length]=sn;}}}
app.logMessage("Allowed to login services: "+allowedToLogin.toString());for(var snName in this.socNetDefs)
{var socialNet=this.socNetDefs[snName];if(allowedToLogin.indexOf(snName)==-1)
{socialNet.SetAllowedToLogin(false);}
if(allowedToMerge.indexOf(snName)==-1)
{socialNet.SetAllowedToMerge(false);}
if(!socialNet.isUserConfirmRequired()&&socialNet.isAllowedToLogin())
this.socNetNoConfirm.push(socialNet);}
this.loadCookies();this.populateSNButtons();}
AuthMain.prototype.populateSNButtons=function()
{var element=document.getElementsByClassName("ap_social-auth")[0];var totalButtons=0;if(!element.precached)
{while(element.firstChild)
element.removeChild(element.firstChild);var fragment=document.createDocumentFragment();for(var i=0;i<this.socNetNames.length;i++)
{var socNetName=this.socNetNames[i];var socialNet=this.socNetDefs[socNetName];if(socNetName=='pwc'||socNetName=="gmg")
{socialNet.authorize();continue;}
if(!socialNet.isUserConfirmRequired())
continue;if(!socialNet.isAllowedToLogin())
continue;var listItem=document.createElement("li");listItem.className="ap_social-block";var button=document.createElement("a");button.className="ap_social-link "+socNetName+" e_gold";var spanEl=document.createElement("span");spanEl.className="ap_social-icon";spanEl.id=socialNet.textId;spanEl.innerHTML=getLocalizedString(socialNet.textId,"innerHTML");this.setAuthButtonHandlers(listItem,socialNet);button.appendChild(spanEl);listItem.appendChild(button);fragment.appendChild(listItem);totalButtons++;}
element.appendChild(fragment);element.precached=true;}
if(totalButtons>0){document.getElementsByClassName("ap_action-social")[0].style.display="block";}}
AuthMain.prototype.getSocialNetwork=function(name)
{return this.socNetDefs[name];}
AuthMain.prototype.setAuthButtonHandlers=function(btn,socialNet)
{btn.onclick=function(){socialNet.authorize();};}
AuthMain.prototype.isAuthProcessed=function()
{return this.authProcessed;}
AuthMain.prototype.processAuth=function()
{if(this.isBlocked)
return;if(!this.isLoggedIn()&&!this.isAuthProcessed())
{this.authProcessed=true;if(this.cachedData.autoLogin)
{if(this.tryToLoginByAny())
return;}
this.firstAuth();}}
AuthMain.prototype.tryToLoginWithoutConfirm=function(callback)
{if(!this.socNetNoConfirm||this.socNetNoConfirm.length==0)
{if(callback)
callback(false);return;}
var isLoggedIn=false;var responses=0;var self=this;var firstLoggedSn;var error=false;var onSnLoginResponse=function(sn,criticalError)
{responses++;app.logMessage("tryToLoginWithoutConfirm: response for "+sn.name+", total responses "+responses);if(criticalError)
{app.logWarning("tryToLoginWithoutConfirm: critical error received");error=true;}
if(!isLoggedIn&&sn.isLoggedIn())
{firstLoggedSn=sn;isLoggedIn=true;}
if(responses==self.socNetNoConfirm.length)
{if(callback)
callback(isLoggedIn,error);}}
this.socNetNoConfirm.forEach(function(sn_def){app.logMessage("tryToLoginWithoutConfirm: request for "+sn_def.name);sn_def.tryToLoginWithoutConfirm(onSnLoginResponse);});}
AuthMain.prototype.tryToLoginByAny=function(doNotCallComplete)
{app.logMessage("tryToLoginByAny: starting...");var socialNet;for(var sn in this.cachedData.sns)
{var newSocialNet=authMain.getSocialNetwork(sn);if(newSocialNet)
{var cachedValues=this.cachedData.sns[sn];socialNet=newSocialNet.createNew(this,cachedValues);app.logMessage("tryToLoginByAny: checking "+socialNet.name);if(socialNet.isAllowedToLogin()&&socialNet.refreshToken()&&socialNet.getUserData())
break;}}
if(socialNet&&socialNet.isLoggedIn())
{app.logMessage("tryToLoginByAny: "+socialNet.name+" selected. isLoggedIn="+socialNet.isLoggedIn());this.onSNAuthSuccess(socialNet,doNotCallComplete);app.logMessage("tryToLoginByAny: successfully");return true;}
app.logWarning("tryToLoginByAny: failed");return false;}
AuthMain.prototype.blockAuthProcess=function(socialNet)
{this.isBlocked=true;showErrorMessage(getLocalizedString("authWasBlockedError"),closeBtnClick);app.logWarning("Auth process blocked by sn="+socialNet?socialNet.name:"undefined");}
AuthMain.prototype.setNeedRelogin=function()
{this.needRelogin=true;}
AuthMain.prototype.isNeedRelogin=function()
{return this.needRelogin;}
AuthMain.prototype.refreshUserData=function(clearServerInfo)
{if(this.getServer()&&clearServerInfo)
this.userInfo.deleteServer();this.tryToLoginByAny();}
AuthMain.prototype.firstAuth=function()
{delete this.needRelogin;operatorFrame.hideFrame();setDivDisplay("srvOfflineMessage","none");setDivDisplay("waitForRetryPanel","none");setDivDisplay("authFrame","block");app.logMessage("open authMain window");statistic.pushEvent(EventTypes.SHOW_AUTH);if(authMain.activePwc){authMain.activePwc.showAuthForm();}
if(authMain.activeGmg){authMain.activeGmg.showAuthForm();}
updateEULADiv(false);}
AuthMain.prototype.loadAuthData=function(cache)
{this.cachedData=cache;if(!this.cachedData||typeof(this.cachedData)!="object")
this.cachedData={"sns":{}};if(!this.cachedData.sns||typeof(this.cachedData.sns)!="object")
this.cachedData.sns={};document.getElementById("multiRemember").checked=this.cachedData.rememberMe;}
AuthMain.prototype.saveAuthData=function(sns)
{var cache={};cache.rememberMe=document.getElementById("multiRemember").checked;cache.autoLogin=cache.rememberMe&&this.isLoggedIn();cache.sns={};if(!sns&&this.userInfo)
sns=this.userInfo.getSNS();if(!sns)
sns={};for(var sn in sns)
{var socialNet=sns[sn];var cachedData=socialNet.prepareCachedData();if(cachedData)
cache.sns[sn]=cachedData;}
this.cachedData=cache;saveAuth(cache);}
AuthMain.prototype.loadCookies=function()
{var cookieFileName=app.expandString("{UserDataStorage}/{ApplicationName}.cookies");var cookieObj=loadFileContent(cookieFileName,{isObject:true});if(cookieObj.valid&&(cookieObj.data instanceof Object))
this.socNetCookies=cookieObj.data;else
this.socNetCookies={};}
AuthMain.prototype.saveCookies=function(name,cookies)
{this.socNetCookies[name]=cookies;this.saveCookiesArray();}
AuthMain.prototype.getCookies=function(name)
{if(this.socNetCookies[name]!="")
return this.socNetCookies[name];return null;}
AuthMain.prototype.saveCookiesArray=function()
{var cookieFileName=app.expandString("{UserDataStorage}/{ApplicationName}.cookies");saveFileContent(cookieFileName,this.socNetCookies);}
AuthMain.prototype.onSNAuthError=function(socialNet,notShowError)
{if(!notShowError)
{if(socialNet.isBlocksAuthProcess())
showErrorMessage(socialNet.lastError,closeClick);else
showErrorMessage(socialNet.lastError);}
if(!socialNet.isBlocksAuthProcess())
if(!socialNet.forMerge)
this.firstAuth();}
AuthMain.prototype.getServer=function()
{if(this.userInfo)
return this.userInfo.getServer();return undefined;}
AuthMain.prototype.getAUID=function()
{if(this.userInfo)
return this.userInfo.getAUID();return undefined;}
AuthMain.prototype.getFraction=function()
{if(this.userInfo)
return this.userInfo.getFraction();return undefined;}
AuthMain.prototype.setAUID=function(auid)
{var userInfo=new UserInfo();app.logMessage("userInfo update: setAUID");this.userInfo=userInfo;this.userInfo.auid=auid;this.userInfo.loggedIn=true;}
AuthMain.prototype.getToken=function()
{if(this.userInfo)
return this.userInfo.getToken();return undefined;}
AuthMain.prototype.getSecret=function()
{if(this.userInfo)
return this.userInfo.getSecret();return undefined;}
AuthMain.prototype.onSNAuthSuccess=function(socialNet,doNotCallComplete)
{app.logDebug("[AuthMain] onAuthSuccess: "+socialNet.name);var isOk=true;if(!socialNet.logoutAllowed)
disableLogoutElements();if(!socialNet.webBillingSupported)
disableWebBillingElements();if(socialNet.forMerge)
{this.mergeSocialNetwork(socialNet);return isOk;}
if(socialNet.isLoggedIn())
{var userInfo=new UserInfo();if(userInfo.authOnServer(socialNet))
{app.logMessage("userInfo update: authOnServer");this.userInfo=userInfo;this.userInfo.processSNSQueue();}
else
{app.logWarning("userInfo update: authOnServer failed");isOk=false;if(socialNet.isBlocksAuthProcess())
authMain.blockAuthProcess(socialNet);else
showErrorMessage(getLocalizedString("authWasBlockedError"));}}
this.finishAuth(doNotCallComplete);return isOk;}
AuthMain.prototype.isLoggedIn=function()
{return(this.userInfo&&this.userInfo.isLoggedIn());}
AuthMain.prototype.getCachedSocialNet=function(snid,snuid)
{var cachedValue=this.cachedData.sns[snid];if(cachedValue&&cachedValue.userId==snuid)
return cachedValue;return{"userId":snuid};}
AuthMain.prototype.finishAuth=function(doNotCallComplete)
{if(this.isBlocked)
return;delete this.needRelogin;if(this.isLoggedIn())
{app.logMessage("on success pw server login");if(!launcherMainInfo.notFirstLogin){launcherMainInfo.notFirstLogin=true;saveInfo();}
this.displayUserData();this.hideAuthWindow(true);this.checkPwcActivationOnLogin();this.checkPwcInvite();}
else
{this.firstAuth();}
this.saveAuthData();if(this.isLoggedIn()&&!doNotCallComplete){this.onAuthComplete();}}
function getDateDiff(dateTimeFrom,dateTimeTo,interval){var second=1000,minute=second*60,hour=minute*60,day=hour*24,week=day*7;var timediff=dateTimeTo-dateTimeFrom;if(isNaN(timediff))return NaN;switch(interval){case"years":return date2.getFullYear()-date1.getFullYear();case"months":return((date2.getFullYear()*12+date2.getMonth())-(date1.getFullYear()*12+date1.getMonth()));case"weeks":return Math.floor(timediff/week);case"days":return Math.floor(timediff/day);case"hours":return Math.floor(timediff/hour);case"minutes":return Math.floor(timediff/minute);case"seconds":return Math.floor(timediff/second);default:return undefined;}}
AuthMain.prototype.checkPwcInvite=function()
{var enableInviteDialog=parseInt(app.getConfig("AuthEnableInviteDialog","0"));if(!enableInviteDialog)
return;var checkSNS=app.getConfig("Services2ForceInvitePWC","").split(",");app.logDebug("sns to force invite with pwc:"+checkSNS);var pwcSocialNet=this.getFromSNS(AuthNetworks.PW_CONNECT);var snThatDontNeed2MergeCount=0;for(var sn in this.userInfo.sns){if(sn!=AuthNetworks.PW_CONNECT&&checkSNS.indexOf(sn)<0){snThatDontNeed2MergeCount++;app.logDebug(sn+" don't need to merge with pwc");}}
var auid=this.getAUID();if(auid==undefined)
return;var currentUserInviteData={};if(launcherMainInfo.inviteData==undefined){launcherMainInfo.inviteData={}}
if(launcherMainInfo.inviteData[auid]==undefined)
launcherMainInfo.inviteData[auid]=currentUserInviteData;else
currentUserInviteData=launcherMainInfo.inviteData[auid];if(!currentUserInviteData.invitePwcLoginCount)
currentUserInviteData.invitePwcLoginCount=0;var numberOfLoginsBeforeInvite=parseInt(app.getConfig("InvitePWC_SkipLoginsCount",2));if(currentUserInviteData.invitePwcLoginCount<numberOfLoginsBeforeInvite){currentUserInviteData.invitePwcLoginCount+=1;var loginsLeft=numberOfLoginsBeforeInvite-currentUserInviteData.invitePwcLoginCount;app.logDebug("Number of logins left to show invite to pwc: "+loginsLeft);launcherMainInfo.inviteData[auid]=currentUserInviteData;saveInfo();return;}
var curTime=(new Date()).getTime();if(currentUserInviteData.lastInvitePwcDate){var dateDiff=getDateDiff(currentUserInviteData.lastInvitePwcDate,curTime,"days");app.logDebug("last invite time: "+currentUserInviteData.lastInvitePwcDate);var retryPeriod=parseInt(app.getConfig("InvitePWC_RetryDelayInDays",7));if(dateDiff<retryPeriod){var daysLeft=retryPeriod-dateDiff;app.logDebug("Number of days left to show invite to pwc: "+daysLeft);return;}}
var noOtherSns=snThatDontNeed2MergeCount==0;if(noOtherSns&&!pwcSocialNet){currentUserInviteData.lastInvitePwcDate=curTime;launcherMainInfo.inviteData[auid]=currentUserInviteData;saveInfo();this.showPwcInviteDialog();}else{app.logDebug("no need to invite PWC");}}
AuthMain.prototype.showPwcInviteDialog=function()
{var socialNet=this.userInfo.getFSN();if(!socialNet||!socialNet.isLoggedIn())
return;var text=getLocalizedString("pwcRegisterInviteLabel","innerHTML");if(this.userInfo.sex==Sex.MALE)
text=getLocalizedString("pwcRegisterInviteLabelMale");else if(this.userInfo.sex==Sex.FEMALE)
text=getLocalizedString("pwcRegisterInviteLabelFemale");document.getElementById("pwcRegisterInviteLabel").innerHTML=text;text=getLocalizedString("pwcRegisterInviteLabel2","innerHTML");text=expandLocaleString(text,[/\{SocNetLocName\}/,socialNet.socialNetLocName]);var element=document.getElementById("pwcRegisterInviteLabel2");element.innerHTML=text;dlgMan.ShowDialog("pwcRegisterInviteWnd");}
AuthMain.prototype.showRegisterInvite=function()
{dlgMan.CloseDialog("pwcRegisterInviteWnd");var pwcSocialNet=new PwcAuth(this);pwcSocialNet.forMerge=true;var email="";var fbSocialNet=this.getFromSNS(AuthNetworks.FACEBOOK);if(fbSocialNet)
email=fbSocialNet.email;pwcSocialNet.showRegisterWindow(email,true,this.userInfo.sex);}
AuthMain.prototype.checkPwcActivationOnLogin=function()
{var pwcSocialNet=this.getFromSNS(AuthNetworks.PW_CONNECT);if(pwcSocialNet)
pwcSocialNet.checkActivation();}
AuthMain.prototype.onAuthComplete=function()
{}
AuthMain.prototype.hideAuthWindow=function(success)
{if(success)
setDivDisplay("srvOfflineMessage","none");setDivDisplay("authFrame","none");operatorFrame.showNews();updateEULADiv(true);}
AuthMain.prototype.displayUserData=function()
{var snName;var socialNet;var width=0;var visCount=0;var toReloginSNs=[];var loggedSNs=[];var toMergeSNs=[];var sns=this.userInfo.getSNS();for(snName in this.socNetDefs){socialNet=this.socNetDefs[snName];if(sns[snName]&&sns[snName].isInfoMarkVisible()){visCount++;if(sns[snName].isLoggedIn()){loggedSNs.push(sns[snName]);}
else{toReloginSNs.push(socialNet);}}
else if(socialNet.isAllowedToMerge()){visCount++;toMergeSNs.push(socialNet);}}
var realVisCount=visCount>MAX_VISIBLE_ICONS_COUNT?MAX_VISIBLE_ICONS_COUNT:visCount;var dist=Math.floor((140-realVisCount*authInfoImagesWidth)/(realVisCount+1));var left=50+dist;var panel=document.getElementById("SocNetsMarks");while(panel.firstChild)
panel.removeChild(panel.firstChild);var showedCount=0;var _this=this;var showSNS=function(socialNetName){var inSNS=true;socialNet=sns[socialNetName];if(!socialNet){socialNet=_this.socNetDefs[socialNetName];inSNS=false;}
if(!socialNet)
return Boolean(false);if(showedCount<realVisCount){app.logDebug("show icon for "+socialNet.name+"["+showedCount+"]");showedCount++;socialNet.showInfoImage(panel,left,inSNS);left+=authInfoImagesWidth+dist;return Boolean(true);}
return Boolean(false);}
for(var i=0;i<toMergeSNs.length;i++){showSNS(toMergeSNs[i].name);}
for(i=0;i<toReloginSNs.length;i++){showSNS(toReloginSNs[i].name);}
for(i=0;i<loggedSNs.length;i++){showSNS(loggedSNs[i].name);}
var avatar=document.getElementById("avatarImg");avatar.src=this.userInfo.avatarURL;setDivDisplay("MainInfoPanel","block");setDivDisplay("UserInfoPanel","block");var userNameDiv=document.getElementById("UserName");var maxWidth=140;var textString=this.userInfo.nickname;userNameDiv.title=userNameDiv.innerHTML=textString;userNameDiv.style.width="";while(userNameDiv.offsetWidth>maxWidth)
{textString=textString.substring(0,textString.length-1);userNameDiv.innerHTML=textString+"...";}
userNameDiv.style.width=maxWidth+"px";if(updateManager.downloaded&&!isMaintenance)
updateMainButton(States.Ready);else
updateMainButton();}
AuthMain.prototype.giveRewardOnConnectNew=function()
{var sns={};if(this.userInfo)
sns=this.userInfo.getSNS();var connectedCount=0;for(var sn in sns)
{var socialNet=sns[sn];if(socialNet.giveRewardOnConnect())
connectedCount++;}
return connectedCount<2;}
AuthMain.prototype.onMarkMouseOver=function(socialNet,inSNS)
{var tooltipElement=document.getElementById("authInfoTooltip");if(tooltipElement.style.display=="none")
{var text;if(socialNet.isLoggedIn())
{text=getLocalizedString("connectedTooltip","innerHTML");}
else
{if(inSNS)
{text=getLocalizedString("reconnetTooltip","innerHTML");}
else
{if(this.giveRewardOnConnectNew())
text=getLocalizedString("connectNewTooltip","innerHTML");else
text=getLocalizedString("connectNewTooltipNoReward","innerHTML");}}
text=expandLocaleString(text,[/\{socialNetLocName\}/,socialNet.socialNetLocName]);document.getElementById("authInfoTooltip").innerHTML=text;tooltipElement.style.left=(socialNet.markPosition+20)+"px";tooltipElement.style.opacity=0;tooltipElement.currentOpacity=0;tooltipElement.style.display="block";if(this.showInfoTooltipUpdater)
clearInterval(this.showInfoTooltipUpdater)
var _this=this;this.showInfoTooltipUpdater=setInterval(function(){_this.updateInfoTooltip();},20);var pwc=this.getFromSNS(AuthNetworks.PW_CONNECT);if(pwc)
pwc.hideActivationReminder();}}
AuthMain.prototype.onMarkMouseOut=function(socialNet)
{var e=window.event;var tooltipElement=document.getElementById("authInfoTooltip");var nextElement=document.elementFromPoint(e.pageX,e.pageY);if(nextElement)
{if(nextElement==socialNet.markElement||nextElement==socialNet.markSignElement||nextElement==tooltipElement)
return;}
this.hideInfoPanelTooltip(tooltipElement);}
AuthMain.prototype.updateTooltipElement=function(tooltipElement,increment)
{var opacity=tooltipElement.currentOpacity;if(!opacity)
opacity=0;opacity+=increment;var finished=false;if(increment>0&&opacity>1)
{finished=true;opacity=1;}
else if(increment<0&&opacity<0.01)
{finished=true;opacity=0;}
tooltipElement.style.opacity=opacity;tooltipElement.currentOpacity=opacity;return finished;}
AuthMain.prototype.updateInfoTooltip=function()
{var tooltipElement=document.getElementById("authInfoTooltip");if(this.updateTooltipElement(tooltipElement,0.1))
{clearInterval(this.showInfoTooltipUpdater);delete this.showInfoTooltipUpdater;}}
AuthMain.prototype.infoPanelTooltipOut=function(tooltipElement)
{var e=window.event;var nextElement=document.elementFromPoint(e.pageX,e.pageY);if(nextElement)
{if(nextElement==tooltipElement||nextElement.parentNode==tooltipElement)
return;}
this.hideInfoPanelTooltip(tooltipElement);}
AuthMain.prototype.hideInfoPanelTooltip=function(tooltipElement)
{tooltipElement.style.display="none";if(this.showInfoTooltipUpdater)
{clearInterval(this.showInfoTooltipUpdater);delete this.showInfoTooltipUpdater;}}
AuthMain.prototype.onMarkClick=function(socialNet)
{var fromSNS=this.getFromSNS(socialNet.name);if(fromSNS)
{if(fromSNS.isLoggedIn())
return;socialNet.authorize(false);}
else
{this.showJoinDialog(socialNet);}}
AuthMain.prototype.getFromSNS=function(name)
{if(this.userInfo)
return this.userInfo.sns[name];return undefined;}
AuthMain.prototype.logout=function()
{app.logMessage("Change server in logout from '"+this.getServer()+"' to empty");this.userInfo.logout();this.saveAuthData();app.logMessage("Removing userInfo in logout");delete this.userInfo;setDivDisplay("MainInfoPanel","block");setDivDisplay("authFrame","block");setDivDisplay("UserInfoPanel","none");setDivDisplay("waitForRetryPanel","none");updateMainButton();this.authProcessed=false;this.firstAuth();}
AuthMain.prototype.onRememberCheck=function()
{this.saveAuthData();}
AuthMain.prototype.onUserNameMouse=function(elem,mouseOver)
{var pwc=this.getFromSNS(AuthNetworks.PW_CONNECT);if(pwc)
pwc.onUserNameMouse(elem,mouseOver);}
AuthMain.prototype.showJoinDialog=function(socialNet)
{var pwcSocialNet=this.getFromSNS(AuthNetworks.PW_CONNECT);if(pwcSocialNet&&!pwcSocialNet.canJoin())
return;var text=getLocalizedString("connectInfoText","innerHTML");text=expandLocaleString(text,[/\{socialNetLocName\}/,socialNet.socialNetLocName]);var element=document.getElementById("connectInfoText");element.innerHTML=text;setDivDisplay("connectInfoText2",this.giveRewardOnConnectNew()?"block":"none");element=document.getElementById("connectNewSNButtonImg");element.src=socialNet.connectNewImage;element=document.getElementById("connectNewSNButton");var _this=this;element.onclick=function(){_this.tryJoinSocialNet(socialNet);};dlgMan.ShowDialog("connectNewInfoWnd");}
AuthMain.prototype.tryJoinSocialNet=function(socialNet)
{var fsn=this.userInfo.getFSN();result=fsn.showJoinWnd(socialNet);dlgMan.CloseDialog("connectNewInfoWnd");}
AuthMain.prototype.updateUserGender=function(gender)
{var fsn=this.userInfo.getFSN();if(fsn)
fsn=fsn.name;app.logMessage('updateUserGender: gender='+gender+' fsn='+fsn);var prms={'action':'l_set_gender','gender':gender,'auid':this.userInfo.getAUID(),'snid':fsn};var url='?'+app.prepareSignedRequest('',prms);var data=authServer.request(url);if(data.valid)
{try
{eval('data.data='+data.data);}
catch(e){}
var response=data.data.response;if(response.ok!=1)
app.logWarning('updateUserGender error, response was: '+JSON.stringify(data.data));else
app.logMessage('updateUserGender success');}}
AuthMain.prototype.mergeSocialNetwork=function(socialNet)
{if(socialNet!=null)
app.logMessage("mergeSocialNetwork sn.name="+socialNet.name);else
app.logMessage("mergeSocialNetwork null sn");delete socialNet.forMerge;var prms={"action":"l_join","hostid":hostId,"ver":protocolVersion,"locale":langInfo.langCode};socialNet.fillRequestParams(prms,"1");this.userInfo.fillRequestParams(prms,"0");var fsn=this.userInfo.getFSN();if(!fsn)
{app.logWarning("Trying to merge socialNetwork, but userInfo.fsn in null. Unable to process.");showErrorMessage(getLocalizedString("mergeAccountInternalError"));return;}
var first=fsn.getUserId();var second=socialNet.getUserId();app.logPrivate("Join social nets: "+fsn.name+":"+first+", "+socialNet.name+":"+second);var secret=app.getSecret([first,second]);var url="?"+app.prepareSignedRequest(secret,prms);var data=authServer.request(url);if(data.valid)
{try
{eval("data.data="+data.data);}
catch(e){}
var response=data.data.response;if(response.ok==1)
{dlgMan.CloseDialog("connectNewInfoWnd");var newSNS={};var sns=this.userInfo.getSNS();for(var sn in sns)
newSNS[sn]=sns[sn];newSNS[socialNet.name]=socialNet;this.saveAuthData(newSNS);this.refreshUserData();}
else
{if(response.ec==SSErrors.AGGREGATOR_JOIN_USER_EXISTS)
{dlgMan.CloseDialog("connectNewInfoWnd");showErrorMessage(getLocalizedString("userAlreadyMerged"));return;}
else
{var errTxt=getAuthErrorText("AGG_EC_",response.ec,response.error);app.logWarning("mergeSocialNetworks: failed - "+errTxt);showErrorMessage(errTxt);}}}
else
{showErrorMessage(data);app.logWarning("mergeSocialNetworks: failed - "+JSON.stringify(data));}}
AuthMain.prototype.showMergeDialog=function(socialNet)
{var mergeUserInfo=new UserInfo();if(mergeUserInfo.authOnServer(socialNet))
{mergeUserInfo.processSNSQueue();var hasIntersection=undefined;for(var sn in this.userInfo.sns)
{var curSN=this.userInfo.sns[sn];var merge=mergeUserInfo.sns[curSN.name];if(merge&&curSN&&merge.userId!=curSN.userId)
{hasIntersection=true;break;}}
if(hasIntersection)
{showErrorMessage(getLocalizedString("userAlreadyMerged"));return;}
var socialNets=[];socialNets[0]=this.userInfo;socialNets[1]=mergeUserInfo;var text=getLocalizedString("connectChooseText","innerHTML");text=expandLocaleString(text,[/\{socialNetLocName\}/,mergeUserInfo.getFSN().socialNetLocName]);var element=document.getElementById("connectChooseText");element.innerHTML=text;var tbl=document.getElementById("chooseSocNetTable");var html="";for(var n=0;n<4;n++)
{text=getLocalizedString("connectChooseTbl"+n,"innerHTML");html+="<tr class=\"connectInfoWndsText\">";for(var i=0;i<socialNets.length;i++)
{var curUserInfo=socialNets[i];var tdText=expandLocaleString(text,[/\{socialNetLocName\}/,curUserInfo.getFSN().socialNetLocName,/\{nickname\}/,curUserInfo.nickname,/\{fraction\}/,curUserInfo.fractionName,/\{fame\}/,curUserInfo.fame]);html+="<td  width=\"50%\">"+tdText+"</td>";}
html+="</tr>";}
element=document.getElementById("connectChooseTblBtn0");this.setMergeHandler(element,this.userInfo,mergeUserInfo);element=document.getElementById("connectChooseTblBtn1");this.setMergeHandler(element,mergeUserInfo,this.userInfo);tbl.innerHTML=html;dlgMan.CloseDialog("connectNewInfoWnd");dlgMan.ShowDialog("connectInfoChooseWnd");}
else
{var error=mergeUserInfo.lastError;if(error)
{app.logWarning("showMergeDialog: failed - "+JSON.stringify(error));if(error.errorType&&error.errorType!="")
showErrorMessage(error);else if(error.errorMessage&&error.errorMessage!="")
showErrorMessage(error.errorMessage);}}}
AuthMain.prototype.setMergeHandler=function(element,first,second)
{var _this=this;element.onclick=function(){_this.chooseForMerge(first,second);};}
AuthMain.prototype.chooseForMerge=function(first,second)
{var element=document.getElementById("confirmMergeText");var text=getLocalizedString("confirmMergeText","innerHTML");element.innerHTML=expandLocaleString(text,[/\{socialNetLocName\}/,first.getFSN().socialNetLocName]);this.mergeList=[first,second];dlgMan.ShowDialog("confirmMergeWnd");}
AuthMain.prototype.cancelMerge=function()
{dlgMan.CloseDialog("connectInfoChooseWnd");delete this.mergeList;}
AuthMain.prototype.mergePwcFromInvite=function(pwcSocialNet)
{var mergeUserInfo=new UserInfo();if(mergeUserInfo.authOnServer(pwcSocialNet))
{this.mergeList=[this.userInfo,mergeUserInfo];this.finalizeMerge(true);}}
AuthMain.prototype.finalizeMerge=function(result)
{dlgMan.CloseDialog("confirmMergeWnd");if(!result)
return;app.logMessage("userInfo update: finalizeMerge");var prms={"action":"l_merge","ver":protocolVersion};var n=0;var forSecret=[];app.logDebug("Merge info:");for(var i=0;i<this.mergeList.length;i++)
{var curUserInfo=this.mergeList[i];forSecret[i]=curUserInfo.getFSN().getUserId();app.logDebug("SNID="+curUserInfo.getFSN().name+", SNUID="+forSecret[i]);prms["auid"+i]=curUserInfo.getAUID();prms["token"+i]=curUserInfo.getToken();}
var secret=app.getSecret([forSecret]);prms=app.prepareSignedRequest(secret,prms);var data=authServer.request("?"+prms);if(data.valid)
{try
{eval("data="+data.data);}
catch(e){}
if(data.response.ok==1)
{dlgMan.CloseDialog("connectInfoChooseWnd");this.userInfo=this.mergeList[0];var newSNS={};for(var i=0;i<this.mergeList.length;i++)
{var sns=this.mergeList[i].getSNS();for(var sn in sns)
newSNS[sn]=sns[sn];}
this.saveAuthData(newSNS);delete this.mergeList;this.refreshUserData();this.displayUserData();}
else
{app.logWarning("finalizeMerge: failed - "+JSON.stringify(data.response.error));showErrorMessage(getAuthErrorText("AGG_EC_",data.response.ec,data.response.error));}}
else
{app.logWarning("finalizeMerge: failed - "+JSON.stringify(data));showErrorMessage(data);}}
AuthMain.prototype.updateUserInfo=function(socialNet,result)
{}
AuthMain.prototype.getNotRegisteredApUserError=function()
{var errStr=getLocalizedString("AGG_EC8_title");var mainPageSpan="<span class='linkMark' onclick=\"openExternalBrowser('"+getLocalizedString("ec8_mainPage_Link")+"');\">"+getLocalizedString("ec8_mainPage")+"</span>";var myAccountPageSpan="<span class='linkMark' onclick=\"openExternalBrowser('"+getLocalizedString("ec8_myAccountPage_Link")+"');\">"+getLocalizedString("ec8_myAccountPage")+"</span>";for(var i=1;i<3;i++)
{var line=getLocalizedString("AGG_EC8_line"+i);line=expandLocaleString(line,[/\{ec8_mainPage\}/,mainPageSpan,/\{ec8_myAccountPage\}/,myAccountPageSpan]);errStr+="<br/>"+line;}
return errStr;}
AuthMain.prototype.getNotAllowedApUserError=function()
{return getLocalizedString("AGG_EC400_title");}