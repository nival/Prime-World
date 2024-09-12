
deriveClass(MassiveAuth,SocialNetAuth,"MassiveAuth");function MassiveAuth(parent)
{MassiveAuth.__base.constructor.apply(this,arguments);this.name=AuthNetworks.MASSIVE;this.textId="msvAuthPanelText";this.markImage="images/msvInfo.png";this.mainAuthPanelImage="images/msv.png";this.connectNewImage="images/main-button-selectNetwork-msv.png";this.uniTitleId="SN_MSV_UniTitleSimple";this.activationCriticalTime=86400;this.socialNetLocName=getLocalizedString("msvAuthName","innerHTML");}
MassiveAuth.prototype.__new=function(parent)
{return new MassiveAuth(parent);}
MassiveAuth.prototype.applyCachedValues=function(cachedValues)
{if(MassiveAuth.__base.applyCachedValues.apply(this,arguments))
{this.email=cachedValues.email;return true;}
return false;}
MassiveAuth.prototype.prepareCachedData=function()
{var cache=MassiveAuth.__base.prepareCachedData.apply(this,arguments);cache.email=this.email;return cache;}
MassiveAuth.prototype.refreshToken=function()
{return this.getUserData();}
MassiveAuth.prototype.getUserData=function()
{var auidResult=this.getAUID();if(!auidResult._authError)
this.loggedIn=true;return this.loggedIn;}
MassiveAuth.prototype.showAuthWindow=function()
{this.attachToDialogs();var remember=document.getElementById("remember").checked;this.rememberPass=(remember&&this.authToken&&this.authToken!="");if(remember&&this.email)
document.getElementById("msvLoginWndEmailEdit").value=this.email;document.getElementById("msvRemember").checked=remember;document.getElementById("msvLoginWndPasswordEdit").value="";document.getElementById("msvLoginWndPasswordEdit").placeholder="";if(this.rememberPass)
document.getElementById("msvLoginWndPasswordEdit").placeholder=getLocalizedString("msvLoginWndRememberPlaceholder");else
document.getElementById("msvLoginWndPasswordEdit").placeholder="";dlgMan.ShowDialog("msvLoginWnd");}
MassiveAuth.prototype.attachToDialogs=function()
{authMain.activeMsv=this;var _this=this;dlg=document.getElementById("msvLoginWnd");dlg.onCommandButton=function(keyCode){_this.msvLoginWndCmdButton(keyCode)};}
MassiveAuth.prototype.msvLoginWndCmdButton=function(keyCode)
{if(keyCode==13)
this.onMsvLoginWndEnter();else if(keyCode==27)
dlgMan.CloseDialog('msvLoginWnd');}
MassiveAuth.prototype.onUserDataChanged=function(element)
{document.getElementById("msvLoginWndPasswordEdit").placeholder="";delete this.rememberPass;hideErrorTip(element);}
MassiveAuth.onMsvRememberClick=function()
{var remember=document.getElementById("msvRemember").checked;document.getElementById("remember").checked=remember;authMain.onRememberCheck();}
MassiveAuth.prototype.showMsvErrorMessage=function()
{if(this.msvError)
{if(this.msvError.ec==SSErrors.NOT_A_REGISTERED_AP_USER)
{var errText=authMain.getNotRegisteredApUserError();showErrorMessage(errText);return;}
else
if(this.msvError.ec==SSErrors.NOT_A_ALLOWED_AP_USER)
{var errText=authMain.getNotAllowedApUserError();showErrorMessage(errText);return;}
else if(this.msvError.ec==SSErrors.PWC_RESEND_TOO_OFTEN)
{var str=this.msvError.text;var regExp=/[0-9]+/;var number=regExp.exec(str);var timeStr="";if(number&&number!="")
{var intV=parseInt(number);var sec=intV%60;intV=(intV-sec)/60;var min=intV%60;intV=(intV-min)/60;var hh=intV%60;intV=(intV-hh)/24;if(intV>0)
timeStr+=" "+intV+" "+getLocalizedString("DayAbbreviation");if(intV>0||hh>0)
timeStr+=" "+hh+" "+getLocalizedString("HourAbbreviation");if(intV>0||hh>0||min>0)
timeStr+=" "+min+" "+getLocalizedString("MinuteAbbreviation");if(intV>0||hh>0||min>0||sec>0)
timeStr+=" "+sec+" "+getLocalizedString("SecondAbbreviation");}
var errStr="";if(timeStr!="")
{errStr=getLocalizedString("AGG_EC_82");if(errStr=="AGG_EC_82")
errStr="";if(errStr&&errStr!="")
errStr+=timeStr;}
else
{errStr=getLocalizedString("AGG_EC_82_0");if(errStr=="AGG_EC_82_0")
errStr="";}
if(errStr!="")
{showErrorMessage(errStr);return;}}}
showErrorMessage(this.lastError);this.logWarning(" error - "+JSON.stringify(this.lastError));}
MassiveAuth.prototype.checkUsername=function(email)
{if(!email||email=="")
return false;return true;}
MassiveAuth.prototype.checkPassword=function(pass,email)
{if(!pass||pass=="")
return getLocalizedString("ERR_EMPTY_PASSWORD");if(pass.length<4)
return getLocalizedString("ERR_PASSWORD_TO_SHORT");if(pass.length>32)
return getLocalizedString("ERR_PASSWORD_TO_LONG");var regExp=/[^A-Za-z0-9-_!@#?]/g;if(regExp.test(pass))
return getLocalizedString("MSV_ERR_PASSWORD_WRONG");return"";}
MassiveAuth.prototype.onMsvLoginWndEnter=function()
{var email=document.getElementById("msvLoginWndEmailEdit").value.trim();var pass=document.getElementById("msvLoginWndPasswordEdit").value;if(!this.checkUsername(email))
{var text=getLocalizedString((email=="")?"ERR_EMPTY_USERNAME":"ERR_WRONG_USERNAME");showErrorTip("msvLoginWndEmailEdit",text);return;}
if(!this.rememberPass)
{var passErr=this.checkPassword(pass,email);if(passErr&&passErr!="")
{showErrorTip("msvLoginWndPasswordEdit",passErr);return;}
this.authToken=app.getSHA1Hash(email.toUpperCase()+pass);}
this.email=email;this.processLogin();}
MassiveAuth.prototype.processLogin=function()
{var auidResult=this.getAUID();if(!auidResult._authError)
{dlgMan.CloseDialog("msvLoginWnd");this.loggedIn=true;this.parent.onSNAuthSuccess(this);return true;}
else if(this.msvError&&this.msvError.ec==SSErrors.PWC_BAD_SIGNATURE)
{delete this.authToken;}
this.showMsvErrorMessage();this.parent.onSNAuthError(this,true);return false;}
MassiveAuth.prototype.getAUID=function(force)
{if(force)
{this.log("Force request user info");}
else if(this.getAUIDResult)
{return this.getAUIDResult;}
this.attachToDialogs();var prms={"action":"l_who","hostid":hostId,"ver":protocolVersion,"locale":langInfo.langCode,"primary":authMain.isLoggedIn()?0:1};this.fillRequestParams(prms);if(this.email)
prms.snuid=app.getCipheredBase64(this.email.toLowerCase(),this.authToken);if(muid&&muid!="")
prms.muid=muid;prms=app.prepareSignedRequest(this.authToken,prms);var data=authServer.request("?"+prms);if(data.valid)
{var respData=undefined;if(!checkJsonResponse(data.data))
{data._authError=true;data.errorMessage=getAuthErrorText("REQ_ERR_","WRONG_ANSWER","");}
else
{try{eval("respData = "+data.data);}
catch(e)
{data._authError=true;data.errorMessage=""+e;}}
if(respData&&respData.response&&respData.response.ok==1)
{var result=respData.response;app.logPrivate("msv: for 'secret' use "+this.authToken);result.pwSign=this.authToken;this.userId=result.uid;if(result.activation_term_left&&result.activation_term_left!="")
this.activation_term_left=parseInt(result.activation_term_left);else
delete this.activation_term_left;this.getAUIDResult=result;this.parent.updateUserInfo(this,result);return result;}
else
{this.msvError={ec:respData.response.ec};if(!data.errorMessage||data.errorMessage=="")
{errorMessage=getAuthErrorText("AGG_EC_",respData.response.ec,respData.response.error);if(!respData.response||errorMessage==respData.response.error){data.errorTitle=getLocalizedString("SN_MSV_UniTitle");}
else
data.noDetails=true;data.errorMessage=errorMessage;}
else
{this.msvError.text=(!respData.response.error||respData.response.error=="")?data.errorMessage:respData.response.error;}
data._authError=true;}}
else
{data._authError=true;}
this.lastError=data;return data;}
MassiveAuth.openRegisterWindow=function()
{var url=app.getConfig("MsvRegisterUrl","http://my.massive.ph/?/user/register");openExternalBrowser(url);}
MassiveAuth.openResetPasswordWindow=function()
{var url=app.getConfig("MsvResetPasswordUrl","http://my.massive.ph/?/user/password/reset");openExternalBrowser(url);}
MassiveAuth.prototype.giveRewardOnConnect=function()
{return false;}