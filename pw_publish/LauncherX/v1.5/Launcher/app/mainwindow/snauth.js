
var AuthNetworks={FACEBOOK:"fb",ODNOKLASSNIKI:"ok",VKONTAKTE:"vk",STEAM:"st",PW_CONNECT:"pwc",AERIA:"ae",MAILRU:"mru",MASSIVE:"msv",ARC:"arc",ZZIMA:"zzma",GAMIGO:"gmg",DRAUGAS:"dlt"};function SocialNetAuth(parent)
{this.userConfirmRequired=true;this.stopOnServerAuthFailed=false;this.allowedToLogin=true;this.allowedToMerge=true;this.logoutAllowed=true;this.webBillingSupported=true;this.parent=parent;}
SocialNetAuth.prototype.createNew=function(parent,cachedValues)
{var result=this.__new(parent);result.applyCachedValues(cachedValues);result.SetAllowedToLogin(this.allowedToLogin);return result;}
SocialNetAuth.prototype.applyCachedValues=function(cachedValues)
{if(cachedValues)
{this.userId=cachedValues.userId;this.authToken=cachedValues.authToken;return true;}
return false;}
SocialNetAuth.prototype.getUserId=function()
{return this.userId;}
SocialNetAuth.prototype.getAuthToken=function()
{return this.authToken;}
SocialNetAuth.prototype.getLoginURL=function()
{return this.loginURL;}
SocialNetAuth.prototype.applyCookies=function()
{}
SocialNetAuth.prototype.storeCookies=function()
{}
SocialNetAuth.prototype.showJoinWnd=function(joinNextSN)
{app.logDebug("[SocialNetAuth] showJoinWnd");var newSocialNew=this.createNew(this.parent);newSocialNew.forMerge=false;newSocialNew.IsJoinWnd=true;newSocialNew.JoinNextSN=joinNextSN;newSocialNew.showAuthWindow();return 1;}
SocialNetAuth.prototype.onJoinSNAuthSuccess=function()
{app.logDebug("[SocialNetAuth] onJoinSNAuthSuccess this.IsJoinWnd = "+this.IsJoinWnd);if(this.IsJoinWnd)
{dlgMan.CloseDialog('joinPWCWnd');this.JoinNextSN.authorize(true);}}
SocialNetAuth.prototype.showAuthWindow=function()
{this.browserWindow=app.createBrowserWindow();this.applyCookies();this.browserWindow.setAppModal(true);var _this=this;this.browserWindow.requestFailed.connect(function(url,errorCode,errorMessage){_this.onPageLoadError(url,errorCode,errorMessage);});this.browserWindow.windowClosed.connect(function(){_this.onCloseAuthWindow();});this.browserWindow.urlChanged.connect(function(url){_this.onAuthUrlChanged(url);});var mainPage=this.browserWindow.getMainPage();mainPage.beforeNavigate.connect(function(request){_this.onBeforeNavigate(request);});this.browserWindow.setWindowTitle(getLocalizedString(this.windowDescription));var url=this.getLoginURL();this.browserWindow.gotoUrl(url);this.browserWindow.show();this.browserWindow.raise();}
SocialNetAuth.prototype.onCloseAuthWindow=function()
{this.destroyBrowserWindow();}
SocialNetAuth.prototype.destroyBrowserWindow=function()
{if(this.browserWindow)
{var wnd=this.browserWindow;delete this.browserWindow;wnd.close();wnd.deleteLater();}}
SocialNetAuth.prototype.onPageLoadError=function(url,errorCode,errorMessage){this.destroyBrowserWindow();var errData={"error":true,"errorCode":errorCode,"errorType":"HTTP"};errData.errorTitle=getLocalizedString(this.checkConnectionErrId);var txt="HTTP_ERR_CODE_"+errorCode;var locText=getLocalizedString(txt);if(txt==locText)
locText=errorMessage;errData.errorMessage=getLocalizedString(this.uniTitleId)+"\r\n("+errorCode+") "+locText;showErrorMessage(errData);};SocialNetAuth.prototype.onBeforeNavigate=function(request)
{}
SocialNetAuth.prototype.onAuthUrlChanged=function(url)
{app.logDebug("[onAuthUrlChanged] url changed to "+url);app.logDebug("[onAuthUrlChanged] authRedirUrl="+this.authRedirUrl);var redirUrl=this.authRedirUrl;if(url.substring(0,redirUrl.length).toLowerCase()==redirUrl)
{app.logDebug("[onAuthUrlChanged] destroy browser window");var prms=urldecode(url.substring(redirUrl.length));this.storeCookies();this.destroyBrowserWindow();this.processAuthToken(prms);}}
SocialNetAuth.prototype.onAuthFrameLoaded=function(isOk)
{}
SocialNetAuth.prototype.makeAuthError=function(text)
{if(inClosingState)
return;delete this.authToken;this.lastError={error:true,_authError:true,errorMessage:text};this.lastError.errorTitle=getLocalizedString(this.windowDescription);if(this.lastError.errorTitle==this.windowDescription)
delete this.lastError.errorTitle;}
SocialNetAuth.prototype.processAuthToken=function(params)
{this.makeAuthError("processAuthToken is not implemented");this.parent.onSNAuthError(this);}
SocialNetAuth.prototype.scaleAuthImage=function(mouseOver)
{var element=document.getElementById(this.name+"AuthPanelImage");if(mouseOver)
element.className="socialNetsToLoginImageHover";else
element.className="socialNetsToLoginImage";element=document.getElementById(this.name+"AuthPanelText");if(mouseOver)
element.className="socialNetsToLoginTextHover";else
element.className="socialNetsToLoginText";}
SocialNetAuth.prototype.authorize=function(forMerge)
{var newSocialNew=this.createNew(this.parent);newSocialNew.forMerge=forMerge;newSocialNew.showAuthWindow();}
SocialNetAuth.prototype.isLoggedIn=function()
{return this.loggedIn;}
SocialNetAuth.prototype.fillRequestParams=function(prms,prefix)
{if(!prefix)
prefix="";prms["snid"+prefix]=this.name;prms["snuid"+prefix]=this.userId;prms["sntoken"+prefix]=this.authToken;}
SocialNetAuth.prototype.getAUID=function()
{var prms={"hostid":hostId,"ver":protocolVersion,"locale":langInfo.langCode,"primary":authMain.isLoggedIn()?0:1};if(muid&&muid!="")
prms.muid=muid;this.fillRequestParams(prms);var url="?action=l_who&"+joinRequestParameters(prms);var data=authServer.request(url);if(data.valid)
{var respData=null;if(!checkJsonResponse(data.data))
{data._authError=true;data.errorMessage=getAuthErrorText("REQ_ERR_","WRONG_ANSWER","");}
else
{try{eval("respData = "+data.data);}
catch(e)
{data._authError=true;data.errorMessage=""+e;}}
if(respData&&respData.response&&respData.response.ok==1)
{var result=respData.response;if(result.registered&&parseInt(result.registered)==1)
{var info=result.info;var nickname=info.nick;if(!nickname||nickname=="")
nickname=this.userId;sendRefInfo("pw_register",{"hostid":hostId,"auid":info.auid,"snid":this.name,"snuid":this.userId,"nickname":nickname});}
statistic.pushEvent(EventTypes.AUTH_SUCCESS);result.pwSign=app.getHash([this.authToken]);app.logPrivate(this.name+": for 'secret' use "+result.pwSign+" , token "+this.authToken);return result;}
else
{if(respData&&respData.response&&respData.response.ec==SSErrors.NOT_A_REGISTERED_AP_USER)
{data._authError=true;data.errorMessage=authMain.getNotRegisteredApUserError();showErrorMessage(data.errorMessage);}
else
if(respData&&respData.response&&respData.response.ec==SSErrors.NOT_A_ALLOWED_AP_USER)
{data._authError=true;data.errorMessage=authMain.getNotAllowedApUserError();showErrorMessage(data.errorMessage);}
else
if(!data.errorMessage||data.errorMessage=="")
{data._authError=true;data.errorMessage=(respData&&respData.response)?getAuthErrorText("AGG_EC_",respData.response.ec,respData.response.error):getLocalizedString("AGG_EC_Unknown");}}}
else
{data._authError=true;}
return data;}
SocialNetAuth.prototype.isInfoMarkVisible=function()
{return this.isAllowedToMerge()||(this.isAllowedToLogin()&&this.isLoggedIn());}
SocialNetAuth.prototype.SetAllowedToLogin=function(allowed)
{this.allowedToLogin=allowed;}
SocialNetAuth.prototype.SetAllowedToMerge=function(allowed)
{this.allowedToMerge=allowed;}
SocialNetAuth.prototype.isAllowedToLogin=function()
{return this.allowedToLogin;}
SocialNetAuth.prototype.isAllowedToMerge=function()
{return this.allowedToMerge;}
SocialNetAuth.prototype.isUserConfirmRequired=function()
{return this.userConfirmRequired;}
SocialNetAuth.prototype.isBlocksAuthProcess=function()
{return this.stopOnServerAuthFailed;}
SocialNetAuth.prototype.prepareCachedData=function()
{var cache={};cache.userId=this.userId;cache.authToken=this.authToken;return cache;}
SocialNetAuth.prototype.giveRewardOnConnect=function()
{return true;}
SocialNetAuth.prototype.showInfoImage=function(panel,left,inSNS)
{var imgElement=document.createElement("img");imgElement.className="socialNetMark";imgElement.style.left=left+"px";imgElement.id=this.name+"AuthPanelImage";imgElement.src=this.markImage;panel.appendChild(imgElement);this.markPosition=left;this.markElement=imgElement;var _this=this;var _inSNS=inSNS;imgElement.onmouseover=function(){authMain.onMarkMouseOver(_this,_inSNS);};imgElement.onmouseout=function(){authMain.onMarkMouseOut(_this);};imgElement.onclick=function(){authMain.onMarkClick(_this);};if(!this.isLoggedIn())
{imgElement.style.cursor="pointer";var sign=document.createElement("img");sign.className="socialNetMarkSign";sign.style.left=(left+25)+"px";if(inSNS)
sign.src="images/socNetReload.png";else
sign.src="images/socNetAdd.png";sign.style.cursor="pointer";sign.onmouseover=function(){authMain.onMarkMouseOver(_this,_inSNS);};sign.onmouseout=function(){authMain.onMarkMouseOut(_this);};sign.onclick=function(){authMain.onMarkClick(_this);};panel.appendChild(sign);this.markSignElement=sign;}
else
{imgElement.style.cursor="default";delete this.markSignElement;}}
SocialNetAuth.prototype.logout=function()
{this.log("logout");document.getElementById("multiRemember").checked=false;delete this.loggedIn;}
SocialNetAuth.prototype.refreshToken=function()
{this.logWarning("Executing base refreshToken");return true;}
SocialNetAuth.prototype.getUserData=function()
{this.logWarning("Executing base getUserData");return true;}
SocialNetAuth.prototype.tryToLoginWithoutConfirm=function(callback)
{this.logWarning("Executing base tryToLoginWithoutConfirm");if(callback)
callback(this,false);}
SocialNetAuth.prototype.log=function(text)
{text="Auth "+this.name+": "+text;app.logMessage(text);}
SocialNetAuth.prototype.logWarning=function(text)
{text="Auth "+this.name+": "+text;app.logWarning(text);}
SocialNetAuth.prototype.logPrivate=function(text)
{text="Auth "+this.name+": "+text;app.logPrivate(text);}