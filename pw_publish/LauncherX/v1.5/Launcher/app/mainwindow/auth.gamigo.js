
deriveClass(GamigoAuth,SocialNetAuth,"GamigoAuth");function GamigoAuth(parent)
{GamigoAuth.__base.constructor.apply(this,arguments);this.name=AuthNetworks.GAMIGO;this.textId="gmgAuthPanelText";this.markImage="images/gmgInfo.png";this.mainAuthPanelImage="images/gmg.png";this.connectNewImage="images/main-button-selectNetwork-gmg.png";this.uniTitleId="SN_GMG_UniTitleSimple";this.socialNetLocName=getLocalizedString("gmgAuthName","innerHTML");this.gmgKey=app.getConfig("Authorization.GmgPassKey","");}
GamigoAuth.prototype.__new=function(parent)
{return new GamigoAuth(parent);}
GamigoAuth.prototype.applyCachedValues=function(cachedValues)
{if(GamigoAuth.__base.applyCachedValues.apply(this,arguments))
{this.username=cachedValues.username;return true;}
return false;}
GamigoAuth.prototype.prepareCachedData=function()
{var cache=GamigoAuth.__base.prepareCachedData.apply(this,arguments);cache.username=this.username;return cache;}
GamigoAuth.prototype.logout=function()
{PwcAuth.__base.logout();this.loggedIn=false;document.getElementById("gmgLoginWndPasswordEdit").value="";}
GamigoAuth.prototype.refreshToken=function()
{this.showAuthWindow();return this.getUserData();}
GamigoAuth.prototype.getUserData=function()
{var auidResult=this.getAUID();if(!auidResult._authError)
this.loggedIn=true;return this.loggedIn;}
GamigoAuth.prototype.showAuthWindow=function()
{this.attachToDialogs();var remember=document.getElementById("multiRemember").checked;this.rememberPass=(remember&&this.authToken&&this.authToken!="");if(remember&&this.username)
document.getElementById("gmgLoginWndUsernameEdit").value=this.username;document.getElementById("gmgLoginWndPasswordEdit").value="";document.getElementById("gmgLoginWndPasswordEdit").placeholder="";if(this.rememberPass)
document.getElementById("gmgLoginWndPasswordEdit").placeholder=getLocalizedString("gmgLoginWndRememberPlaceholder");else
document.getElementById("gmgLoginWndPasswordEdit").placeholder="";}
GamigoAuth.prototype.attachToDialogs=function()
{authMain.activeGmg=this;var _this=this;dlg=document.getElementById("authGMG");if(!dlg)
return;dlg.onCommandButton=function(keyCode){_this.gmgLoginWndCmdButton(keyCode)};}
GamigoAuth.prototype.gmgLoginWndCmdButton=function(keyCode)
{if(keyCode==13)
this.onGmgLoginWndEnter();}
GamigoAuth.prototype.onUserDataChanged=function(element)
{document.getElementById("gmgLoginWndPasswordEdit").placeholder="";delete this.rememberPass;hideErrorTip(element);markInput(element,InputMarks.NoMark);}
GamigoAuth.prototype.onGmgRememberCheck=function()
{authMain.onRememberCheck();}
GamigoAuth.prototype.showGmgErrorMessage=function()
{if(this.gmgError)
{if(this.gmgError.ec==SSErrors.NOT_A_REGISTERED_AP_USER)
{var errText=authMain.getNotRegisteredApUserError();showErrorMessage(errText);return;}
else
if(this.gmgError.ec==SSErrors.NOT_A_ALLOWED_AP_USER)
{var errText=authMain.getNotAllowedApUserError();showErrorMessage(errText);return;}
else
if(this.gmgError.ec==SSErrors.AGGREGATOR_LOGIN_FAIL)
{var errText=getLocalizedString("SN_GMG_AuthFailed");showErrorMessage(errText);return;}}
showErrorMessage(this.lastError);this.logWarning(" error - "+JSON.stringify(this.lastError));}
GamigoAuth.prototype.checkUsername=function(username)
{if(!username||username=="")
return false;var regExp=/[^A-Za-z0-9]/g;if(regExp.test(username))
return false;return true;}
GamigoAuth.prototype.checkPassword=function(pass)
{if(!pass||pass=="")
return getLocalizedString("ERR_EMPTY_PASSWORD");if(pass.length<4)
return getLocalizedString("ERR_PASSWORD_TO_SHORT");if(pass.length>32)
return getLocalizedString("ERR_PASSWORD_TO_LONG");var regExp=/[^A-Za-z0-9]/g;if(regExp.test(pass))
return getLocalizedString("ERR_PASSWORD_WRONG");return"";}
GamigoAuth.prototype.onGmgLoginWndEnter=function()
{var username=document.getElementById("gmgLoginWndUsernameEdit").value.trim();var pass=document.getElementById("gmgLoginWndPasswordEdit").value;if(!this.checkUsername(username))
{var text=getLocalizedString((username=="")?"ERR_EMPTY_USERNAME":"ERR_WRONG_USERNAME");showErrorTip("gmgLoginWndUsernameEdit",text);return;}
if(!this.rememberPass)
{var passErr=this.checkPassword(pass,username);if(passErr&&passErr!="")
{showErrorTip("gmgLoginWndPasswordEdit",passErr);return;}
this.authToken=app.getCipheredBlowfishBase64(pass,this.gmgKey);}
this.username=username;this.processLogin();}
GamigoAuth.prototype.processLogin=function()
{var auidResult=this.getAUID('force');if(!auidResult._authError)
{this.loggedIn=true;authMain.onSNAuthSuccess(this);this.parent.onSNAuthSuccess(this,true);return true;}
else if(this.gmgError&&this.gmgError.ec==SSErrors.PWC_BAD_SIGNATURE)
{delete this.authToken;}
this.showGmgErrorMessage();this.parent.onSNAuthError(this,true);document.getElementById("pwcLoginWndPasswordEdit").value="";return false;}
GamigoAuth.prototype.getAUID=function(force)
{if(force)
{this.log("Force request user info");}
else if(this.getAUIDResult)
{return this.getAUIDResult;}
this.attachToDialogs();var prms={"action":"l_who","hostid":hostId,"ver":protocolVersion,"locale":langInfo.langCode,"primary":authMain.isLoggedIn()?0:1};this.fillRequestParams(prms);if(this.username)
prms.snuid=this.username;if(muid&&muid!="")
prms.muid=muid;prms=app.prepareSignedRequest(this.authToken,prms);var data=authServer.request("?"+prms);if(data.valid)
{var respData=undefined;if(!checkJsonResponse(data.data))
{data._authError=true;data.errorMessage=getAuthErrorText("REQ_ERR_","WRONG_ANSWER","");}
else
{try{eval("respData = "+data.data);}
catch(e)
{data._authError=true;data.errorMessage=""+e;}}
if(respData&&respData.response&&respData.response.ok==1)
{var result=respData.response;app.logPrivate("gmg: for 'secret' use "+this.authToken);result.pwSign=this.authToken;this.userId=result.uid;if(result.activation_term_left&&result.activation_term_left!="")
this.activation_term_left=parseInt(result.activation_term_left);else
delete this.activation_term_left;this.getAUIDResult=result;this.parent.updateUserInfo(this,result);return result;}
else
{this.gmgError={ec:respData.response.ec};if(!data.errorMessage||data.errorMessage=="")
{errorMessage=getAuthErrorText("AGG_EC_",respData.response.ec,respData.response.error);if(!respData.response||errorMessage==respData.response.error){data.errorTitle=getLocalizedString("SN_GMG_UniTitle");}
else
data.noDetails=true;data.errorMessage=errorMessage;}
else
{this.gmgError.text=(!respData.response.error||respData.response.error=="")?data.errorMessage:respData.response.error;}
data._authError=true;}}
else
{data._authError=true;}
this.lastError=data;return data;}
GamigoAuth.openRegisterWindow=function()
{var url=app.getConfig("Authorization.GmgRegisterUrl","https://de.gamigo.com/game/prime-world/");openExternalBrowser(url);}
GamigoAuth.openResetPasswordWindow=function()
{var url=app.getConfig("Authorization.GmgResetPasswordUrl","https://de.gamigo.com/auth/password/landing/gsvk/PW.de.de.gamigo.v1");openExternalBrowser(url);}
GamigoAuth.prototype.giveRewardOnConnect=function()
{return false;}
GamigoAuth.prototype.showAuthForm=function()
{setDivDisplay("authGMG","block");setDivDisplay("regGMG","block");window.location='#authGMG';}