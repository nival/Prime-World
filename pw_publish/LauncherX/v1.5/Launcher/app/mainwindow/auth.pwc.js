
deriveClass(PwcAuth,SocialNetAuth,"PwcAuth");function PwcAuth(parent)
{PwcAuth.__base.constructor.apply(this,arguments);this.name=AuthNetworks.PW_CONNECT;this.textId="pwcAuthPanelText";this.markImage="images/pwcInfo.png";this.activationCriticalTime=86400;this.socialNetLocName=getLocalizedString("pwcAuthName","innerHTML");document.getElementById("bodyBackground").addEventListener("click",this.hideErrorToolTips,true);document.getElementById("regPWC").addEventListener("click",this.popupErrorToolTips,true);document.getElementById("authPWC").addEventListener("click",this.popupErrorToolTips,true);}
PwcAuth.prototype.__new=function(parent)
{return new PwcAuth(parent);}
PwcAuth.prototype.applyCachedValues=function(cachedValues)
{if(PwcAuth.__base.applyCachedValues.apply(this,arguments))
{this.email=cachedValues.email;return true;}
return false;}
PwcAuth.prototype.prepareCachedData=function()
{var cache=PwcAuth.__base.prepareCachedData.apply(this,arguments);cache.email=this.email;return cache;}
PwcAuth.prototype.logout=function()
{PwcAuth.__base.logout();this.loggedIn=false;document.getElementById("pwcLoginWndPasswordEdit").value="";document.getElementById("pwcLoginWndPasswordEdit").placeholder="";document.getElementById("pwcRegisterWndPasswordEdit").value="";document.getElementById("pwcRegisterWndPasswordEdit").placeholder="";}
PwcAuth.prototype.refreshToken=function()
{this.showAuthWindow();return this.getUserData();}
PwcAuth.prototype.getUserData=function()
{var auidResult=this.getAUID();if(!auidResult._authError)
this.loggedIn=true;return this.loggedIn;}
PwcAuth.prototype.showAuthWindow=function()
{this.attachToDialogs();var remember=document.getElementById("multiRemember").checked;this.rememberPass=(remember&&this.authToken&&this.authToken!="");if(remember&&this.email)
document.getElementById("pwcLoginWndEmailEdit").value=this.email;document.getElementById("pwcLoginWndPasswordEdit").value="";document.getElementById("pwcLoginWndPasswordEdit").placeholder="";if(this.rememberPass)
document.getElementById("pwcLoginWndPasswordEdit").placeholder=getLocalizedString("pwcLoginWndRememberPlaceholder");else
document.getElementById("pwcLoginWndPasswordEdit").placeholder="";}
PwcAuth.prototype.attachToDialogs=function()
{authMain.activePwc=this;var _this=this;dlg=document.getElementById("authPWc");if(!dlg)
return;dlg=document.getElementById("pwcRememberPassWnd");if(dlg.onCommandButton)
dlg.onCommandButton=function(keyCode){_this.pwcRememberPassWndCmdButton(keyCode)};dlg=document.getElementById("pwcActivationReq");if(dlg.onCommandButton)
dlg.onCommandButton=function(keyCode){_this.pwcActivationReqCmdButton(keyCode)};}
PwcAuth.prototype.showJoinWnd=function(joinNextSN)
{this.JoinNextSN=joinNextSN;this.IsJoinWnd=true;this.forMerge=false;var ret=this.fillJoinWnd("joinPWCWnd");if(ret==0)
return 0;return dlgMan.ShowDialog("joinPWCWnd");}
PwcAuth.prototype.fillJoinWnd=function(divName)
{authMain.activePwc=this;var _this=this;dlg=document.getElementById(divName);if(!dlg)
return 0;var remember=document.getElementById("multiRemember").checked;this.rememberPass=false;if(remember&&this.email)
document.getElementById("jpwcLoginWndEmailEdit").value=this.email;else
document.getElementById("jpwcLoginWndEmailEdit").value="";document.getElementById("jpwcLoginWndPasswordEdit").value="";document.getElementById("jpwcLoginWndPasswordEdit").placeholder="";return 1;}
PwcAuth.prototype.pwcActivationReqCmdButton=function(keyCode)
{if(keyCode==13)
this.pwcSendConfirmEmail();else if(keyCode==27)
dlgMan.CloseDialog('pwcActivationReq');}
PwcAuth.prototype.pwcLoginWndCmdButton=function(keyCode)
{if(keyCode==13)
this.onPwcLoginWndEnter();}
PwcAuth.prototype.pwcRegisterWndCmdButton=function(keyCode)
{if(keyCode==13)
this.onPwcRegWndRegister();else if(keyCode==27)
{hideToolTip(document.getElementById("pwcRegisterWndEmailEdit"));hideToolTip(document.getElementById("pwcRegisterWndPasswordEdit"));}}
PwcAuth.prototype.pwcRememberPassWndCmdButton=function(keyCode)
{if(keyCode==13)
this.onPwcChangePass();else if(keyCode==27)
dlgMan.CloseDialog('pwcRememberPassWnd');}
PwcAuth.prototype.onUserDataChanged=function(element)
{if(this.IsJoinWnd)
{document.getElementById("jpwcLoginWndPasswordEdit").placeholder="";}
else
document.getElementById("pwcLoginWndPasswordEdit").placeholder="";delete this.rememberPass;hideErrorTip(element);markInput(element,InputMarks.NoMark);}
PwcAuth.prototype.onPwcRememberCheck=function(elementId)
{if(elementId!="")
{var element=document.getElementById(elementId);document.getElementById("multiRemember").checked=element.checked;}
authMain.onRememberCheck();}
PwcAuth.prototype.onPwcLoginWndForgotPass=function()
{var email=undefined;if(this.IsJoinWnd)
{email=document.getElementById("jpwcLoginWndEmailEdit").value.trim();}
else
{email=document.getElementById("pwcLoginWndEmailEdit").value.trim();}
document.getElementById("pwcRememberPassEmailEdit").value=email;dlgMan.ShowDialog("pwcRememberPassWnd");}
PwcAuth.prototype.onPwcChangePass=function()
{this.log("Change pwc password");var email=document.getElementById("pwcRememberPassEmailEdit").value.trim();if(!this.checkEmail(email))
{var text=getLocalizedString((email=="")?"ERR_EMPTY_EMAIL":"ERR_WRONG_EMAIL");showErrorTip("pwcRememberPassEmailEdit",text);return;}
var md5Mail=app.getHash([email.toLowerCase()]);var req="action=pwc_reset_pwd_link&snuid="+md5Mail+"&locale="+langInfo.langCode;var pwcServer=app.getConfig("PwConnectServer","");var certDomain=app.getConfig("PwConnectCN","");var data=sslRequest(pwcServer,{"CertDomain":certDomain,"getParams":req});if(data.valid)
{if(checkJsonResponse(data.data))
{try
{eval("data="+data.data);}
catch(e)
{showErrorMessage(e);return false;}
if(data.response.ok==1)
{dlgMan.CloseDialog("pwcRememberPassWnd");var text=getLocalizedString("pwcRememberPassLabel","innerHTML")+"<br/><br/>"+email;showMessageBox(getLocalizedString("pwcPassChangedWndTitle","innerHTML"),text);return true;}
else
{this.lastError=getAuthErrorText("AGG_EC_",data.response.ec,data.response.error);this.pwcError={text:data.response.error,ec:data.response.ec};this.showPwcErrorMessage();}}
else
{showErrorMessage(getAuthErrorText("REQ_ERR_","WRONG_ANSWER",""));this.logWarning("change password failed - "+getAuthErrorText("REQ_ERR_","WRONG_ANSWER",""));}}
else
{showErrorMessage(data);this.logWarning("change password failed - "+JSON.stringify(data));}
return false;}
PwcAuth.prototype.showPwcErrorMessage=function()
{if(this.pwcError)
{if(this.pwcError.ec==SSErrors.NOT_A_REGISTERED_AP_USER)
{var errText=authMain.getNotRegisteredApUserError();showErrorMessage(errText);return;}
else
if(this.pwcError.ec==SSErrors.NOT_A_ALLOWED_AP_USER)
{var errText=authMain.getNotAllowedApUserError();showErrorMessage(errText);return;}
else if(this.pwcError.ec==SSErrors.PWC_ACTIVATION_EXPIRED)
{document.getElementById("pwcActivationReqLabel1").innerHTML=getLocalizedString("pwcActivationReqLabel1","innerHTML");document.getElementById("pwcActivationReqLabel2").innerHTML=getLocalizedString("pwcActivationReqLabel2","innerHTML");document.getElementById("pwcActivationReqCaption").innerHTML=getLocalizedString("errorMessageCaption","innerHTML");dlgMan.ShowDialog("pwcActivationReq");return;}
else if(this.pwcError.ec==SSErrors.PWC_RESEND_TOO_OFTEN)
{var str=this.pwcError.text;var regExp=/[0-9]+/;var number=regExp.exec(str);var timeStr="";if(number&&number!="")
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
PwcAuth.prototype.checkEmail=function(email)
{if(!email||email=="")
return false;if(email.length<5||email.length>64)
return false;var re=/^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w+)+$/;return re.test(email);}
PwcAuth.prototype.checkDate=function(d,m,y)
{if(d==0)
return 1;if(m==0)
return 2;if(y==0)
return 3;var date=new Date(y,m-1,d);if(date.getDate()==d&&date.getMonth()==m-1&&date.getFullYear()==y)
return 0;return 4;}
PwcAuth.prototype.checkPassword=function(pass,email)
{if(!pass||pass=="")
return getLocalizedString("ERR_EMPTY_PASSWORD");if(pass.length<4)
return getLocalizedString("ERR_PASSWORD_TO_SHORT");if(pass.length>32)
return getLocalizedString("ERR_PASSWORD_TO_LONG");var regExp=/[^A-Za-z0-9]/g;if(regExp.test(pass))
return getLocalizedString("ERR_PASSWORD_WRONG");var pos=email.indexOf("@");if(pos>=0)
email=email.substring(0,pos);if(pass==email)
return getLocalizedString("ERR_PASSWORD_EQ_EMAIL");return"";}
PwcAuth.prototype.onCommandButton=function(keyCode)
{if(window.location.href.indexOf("#authPWC")!=-1)
{this.pwcLoginWndCmdButton(keyCode);}
else
{this.pwcRegisterWndCmdButton(keyCode);}}
PwcAuth.prototype.onPwcLoginWndEnter=function()
{var email=undefined;var pass=undefined;if(this.IsJoinWnd)
{email=document.getElementById("jpwcLoginWndEmailEdit").value.trim();pass=document.getElementById("jpwcLoginWndPasswordEdit").value;}
else
{email=document.getElementById("pwcLoginWndEmailEdit").value.trim();pass=document.getElementById("pwcLoginWndPasswordEdit").value;}
var validationFailed=false;if(!this.checkEmail(email))
{var text=getLocalizedString((email=="")?"ERR_EMPTY_EMAIL":"ERR_WRONG_EMAIL");if(this.IsJoinWnd)
showErrorTip("jpwcLoginWndEmailEdit",text);else
showErrorTip("pwcLoginWndEmailEdit",text);validationFailed=true;}
if(!this.rememberPass)
{var passErr=this.checkPassword(pass,email);if(passErr&&passErr!="")
{if(this.IsJoinWnd)
showErrorTip("jpwcLoginWndPasswordEdit",passErr);else
showErrorTip("pwcLoginWndPasswordEdit",passErr);return;}
if(validationFailed)
{return;}
this.authToken=app.getHash([pass]);}
this.email=email;this.processPwcLogin();}
PwcAuth.prototype.processPwcLogin=function()
{var auidResult=this.getAUID('force');if(!auidResult._authError)
{this.loggedIn=true;this.parent.onSNAuthSuccess(this);return true;}
else if(this.pwcError&&(this.pwcError.ec==SSErrors.PWC_BAD_SIGNATURE||this.pwcError.ec==SSErrors.PWC_ACCOUNT_BAN))
{delete this.authToken;}
this.showPwcErrorMessage();this.parent.onSNAuthError(this,true);if(this.IsJoinWnd)
document.getElementById("jpwcLoginWndPasswordEdit").value="";else
document.getElementById("pwcLoginWndPasswordEdit").value="";return false;}
PwcAuth.prototype.getAUID=function(force)
{if(force)
{this.log("Force request user info");}
else if(this.getAUIDResult)
{return this.getAUIDResult;}
this.attachToDialogs();var prms={"action":"l_who","hostid":hostId,"ver":protocolVersion,"snid":"pwe","locale":langInfo.langCode,"primary":authMain.isLoggedIn()?0:1};if(this.email)
prms.snuid=app.getHash([this.email.toLowerCase()]);if(muid&&muid!="")
prms.muid=muid;prms=app.prepareSignedRequest(this.authToken,prms);var data=authServer.request("?"+prms);if(data.valid)
{var respData=undefined;if(!checkJsonResponse(data.data))
{data._authError=true;data.errorMessage=getAuthErrorText("REQ_ERR_","WRONG_ANSWER","");}
else
{try{eval("respData = "+data.data);}
catch(e)
{data._authError=true;data.errorMessage=""+e;}}
if(respData&&respData.response&&respData.response.ok==1)
{var result=respData.response;app.logPrivate("pwc: for 'secret' use "+this.authToken);result.pwSign=this.authToken;this.userId=result.pwc_snuid;if(result.activation_term_left&&result.activation_term_left!="")
this.activation_term_left=parseInt(result.activation_term_left);else
delete this.activation_term_left;this.getAUIDResult=result;this.parent.updateUserInfo(this,result);return result;}
else
{this.pwcError={ec:respData.response.ec};if(!data.errorMessage||data.errorMessage=="")
{data.errorMessage=this.pwcError.text=(respData.response)?getAuthErrorText("AGG_EC_",respData.response.ec,respData.response.error):getLocalizedString("AGG_EC_Unknown");}
else
{this.pwcError.text=(!respData.response.error||respData.response.error=="")?data.errorMessage:respData.response.error;}
data._authError=true;data.noDetails=true;}}
else
{data._authError=true;}
this.lastError=data;return data;}
PwcAuth.prototype.onPwcLoginWndRegister=function()
{document.getElementById("pwcRegisterWndEmailEdit").value=document.getElementById("pwcLoginWndEmailEdit").value.trim();}
PwcAuth.prototype.showRegisterWindow=function(email,inInvite,sex)
{this.attachToDialogs();document.getElementById("pwcRegisterWndEmailEdit").value=email;document.getElementById("pwcRegisterWndPasswordEdit").value="";if(inInvite)
{document.getElementById("pwcRegSexMale").checked=(sex==Sex.MALE);document.getElementById("pwcRegSexFemale").checked=(sex==Sex.FEMALE);}
setDivDisplay("pwcRegHasAccount",inInvite?"none":"inline-block");setDivDisplay("pwcRegisterInviteCancel",inInvite?"inline-block":"none");setDivDisplay("pwcRegGenderSection",inInvite?"none":"block");document.getElementById("pwcRegisterWnd").inInvite=inInvite;dlgMan.ShowDialog("pwcRegisterWnd");centerElement("pwcRegisterWnd");}
PwcAuth.prototype.onPwcRegWndRegister=function()
{this.log("register pwc account");var email=document.getElementById("pwcRegisterWndEmailEdit").value.trim();var pass=document.getElementById("pwcRegisterWndPasswordEdit").value;if(this.IsJoinWnd)
document.getElementById("jpwcLoginWndEmailEdit").value=email;else
document.getElementById("pwcLoginWndEmailEdit").value=email;var inInvite=false;if(document.getElementById("pwcRegisterWnd"))
{inInvite=document.getElementById("pwcRegisterWnd").inInvite;}
if(!this.checkEmail(email))
{var text=getLocalizedString((email==="")?"ERR_EMPTY_EMAIL":"ERR_WRONG_EMAIL");showErrorTip("pwcRegisterWndEmailEdit",text);this.logWarning("error register pwc account - "+text);return;}
var passErr=this.checkPassword(pass,email);if(passErr&&passErr!=="")
{showErrorTip("pwcRegisterWndPasswordEdit",passErr);this.logWarning("error register pwc account - "+passErr);return;}
this.regEmail=email;this.regPass=pass;this.inInvite=inInvite;var self=this;eulaPopupShow(true,function(){self.onPwcRegAccept();},function(){self.onPwcRegDiscard();});return false;};PwcAuth.prototype.onPwcRegAccept=function()
{var email=this.regEmail;var pass=this.regPass;var inInvite=this.inInvite;delete this.regEmail;delete this.regPass;var gender=Sex.MALE;var dtValue=1;var passHash=app.getHash([pass]);var req="action=pwc_register&email="+email.toLowerCase()+"&pwd="+passHash+"&gender="+gender+"&birthdate="+dtValue+"&locale="+langInfo.langCode+"&hostid="+hostId;if(muid&&muid!="")
req+="&muid="+muid;var pwcServer=app.getConfig("PwConnectServer","");var certDomain=app.getConfig("PwConnectCN","");var data=sslRequest(pwcServer,{"CertDomain":certDomain,"getParams":req});if(data.valid)
{if(checkJsonResponse(data.data))
{try
{eval("data="+data.data);}
catch(e)
{this.logWarning("error register pwc account - "+JSON.stringify(e));showErrorMessage(e);return;}
if(data.response.ok==1)
{dlgMan.CloseDialog("pwcRegisterWnd");dlgMan.CloseDialog("pwcLoginWnd");this.email=email;this.authToken=passHash;if(inInvite)
{this.inMerge=true;authMain.mergePwcFromInvite(this);return false;}
else
{return this.processPwcLogin();}}
else
{this.logWarning("error register pwc account - "+JSON.stringify(data));showErrorMessage(getAuthErrorText("AGG_EC_",data.response.ec,data.response.error));}}
else
{var errText=getAuthErrorText("REQ_ERR_","WRONG_ANSWER","");this.logWarning("error register pwc account - "+errText);showErrorMessage(errText);}}
else
{this.logWarning("error register pwc account - "+JSON.stringify(data));showErrorMessage(data);}
return false;}
PwcAuth.prototype.onPwcRegDiscard=function()
{return false;}
PwcAuth.prototype.checkActivation=function()
{if(this.activation_term_left)
{if(this.activation_term_left<this.activationCriticalTime)
{document.getElementById("pwcActivationReqLabel1").innerHTML=getLocalizedString("pwcActivationReqLabelDay1","innerHTML");document.getElementById("pwcActivationReqLabel2").innerHTML=getLocalizedString("pwcActivationReqLabelDay2","innerHTML");document.getElementById("pwcActivationReqCaption").innerHTML=getLocalizedString("reminderMessageCaption","innerHTML");dlgMan.ShowDialog("pwcActivationReq");}
else
{this.showActivationReminder();}}}
PwcAuth.prototype.showActivationReminder=function()
{if(this.activationReminderHideUpdater)
return;if(this.activationReminderShowUpdater&&this.activationReminderInShowState)
return;var tooltipElement=document.getElementById("activationReminder");if(tooltipElement.style.display=="block"&&this.activationReminderInShowState)
return;if(!this.activationReminderShowUpdater)
{var _this=this;this.activationReminderShowUpdater=setInterval(function(){_this.updateactivationReminder();},20);tooltipElement.style.opacity=0;tooltipElement.style.display="block";}
this.activationReminderInShowState=true;}
PwcAuth.prototype.hideActivationReminderPaused=function()
{if(this.activationReminderUpdaterPaused)
clearInterval(this.activationReminderUpdaterPaused);var _this=this;this.activationReminderUpdaterPaused=setInterval(function(){_this.activationReminderUpdaterPausedHandler();},120);}
PwcAuth.prototype.activationReminderUpdaterPausedHandler=function()
{clearInterval(this.activationReminderUpdaterPaused);delete this.activationReminderUpdaterPaused;var el1=document.getElementById("UserName");var el2=document.getElementById("activationReminder");if(el1.mouseIsOver||el2.mouseIsOver)
return;this.hideActivationReminder();}
PwcAuth.prototype.hideActivationReminder=function()
{var tooltipElement=document.getElementById("activationReminder");tooltipElement.style.display="none";if(this.activationReminderShowUpdater)
{clearInterval(this.activationReminderShowUpdater);delete this.activationReminderShowUpdater;}
if(this.activationReminderHideUpdater)
{clearInterval(this.activationReminderHideUpdater);delete this.activationReminderHideUpdater;}}
PwcAuth.prototype.updateactivationReminder=function()
{var tooltipElement=document.getElementById("activationReminder");if(authMain.updateTooltipElement(tooltipElement,this.activationReminderInShowState?0.1:-0.1))
{clearInterval(this.activationReminderShowUpdater);delete this.activationReminderShowUpdater;if(this.activationReminderInShowState)
{var el1=document.getElementById("UserName");var el2=document.getElementById("activationReminder");if(el1.mouseIsOver||el2.mouseIsOver)
return;if(!this.activationReminderHideUpdater)
{var _this=this;this.activationReminderHideUpdater=setInterval(function(){_this.updateactivationReminderToHide();},3000);}}
else
{this.hideActivationReminder();}}}
PwcAuth.prototype.updateactivationReminderToHide=function()
{clearInterval(this.activationReminderHideUpdater);delete this.activationReminderHideUpdater;var el1=document.getElementById("UserName");var el2=document.getElementById("activationReminder");if(el1.mouseIsOver||el2.mouseIsOver)
return;if(!this.activationReminderShowUpdater)
{var _this=this;this.activationReminderShowUpdater=setInterval(function(){_this.updateactivationReminder()},20);}
delete this.activationReminderInShowState;}
PwcAuth.prototype.onActivationReminderMouse=function(elem,mouseOver)
{elem.mouseIsOver=mouseOver;if(!mouseOver)
this.hideActivationReminderPaused();}
PwcAuth.prototype.onUserNameMouse=function(elem,mouseOver)
{elem.mouseIsOver=mouseOver;if(mouseOver)
{if(this.activation_term_left)
this.showActivationReminder();}
else
{this.hideActivationReminderPaused();}}
PwcAuth.prototype.canJoin=function()
{if(this.activation_term_left)
{this.getAUID(true);if(this.activation_term_left)
{document.getElementById("pwcActivationReqLabel1").innerHTML=getLocalizedString("pwcActivationReqLabelMerge1","innerHTML");document.getElementById("pwcActivationReqLabel2").innerHTML=getLocalizedString("pwcActivationReqLabelMerge2","innerHTML");document.getElementById("pwcActivationReqCaption").innerHTML=getLocalizedString("errorMessageCaption","innerHTML");dlgMan.ShowDialog("pwcActivationReq");return false;}}
return true;}
PwcAuth.prototype.giveRewardOnConnect=function()
{return false;}
PwcAuth.prototype.pwcSendConfirmEmail=function()
{var email=this.email;if(!email)
email="";var prms={"action":"pwc_resend_confirm","locale":langInfo.langCode,"snuid":app.getHash([email.toLowerCase()])};prms=app.prepareSignedRequest(this.authToken,prms);var pwcServer=app.getConfig("PwConnectServer","");var certDomain=app.getConfig("PwConnectCN","");var data=sslRequest(pwcServer,{"CertDomain":certDomain,"getParams":prms});var respData=this.pwcParseResponse(data);if(respData.valid)
{dlgMan.CloseDialog("pwcActivationReq");}
else
{this.lastError=respData.error;this.ec=respData.ec;this.error=respData.respError;this.pwcError={text:this.error,ec:this.ec};this.showPwcErrorMessage();}}
PwcAuth.prototype.pwcParseResponse=function(data)
{if(data.valid)
{var respData=null;if(!checkJsonResponse(data.data))
{data.error=getAuthErrorText("REQ_ERR_","WRONG_ANSWER","");}
else
{try{eval("respData = "+data.data);}
catch(e)
{data.error=e;}}
if(respData&&respData.response&&respData.response.ok==1)
{respData.valid=true;return respData;}
if(!data.error||data.error=="")
data.error=(respData.response)?getAuthErrorText("AGG_EC_",respData.response.ec,respData.response.error):getLocalizedString("AGG_EC_Unknown");data.ec=respData.response.ec;data.respError=respData.response.error;}
else
{data.error=data;}
delete data.valid;return data;}
PwcAuth.prototype.validateEmailInput=function(element,doMark)
{hideToolTip(element);var email=element.value.trim();if(!this.checkEmail(email))
{if(email=="")
{hideToolTip(element.id);markInput(element,InputMarks.NoMark);return;}
var text=getLocalizedString("ERR_WRONG_EMAIL");showErrorTip(element.id,text);return;}
if(doMark)
{markInput(element,InputMarks.Valid);}
else
{markInput(element,InputMarks.NoMark);}}
PwcAuth.prototype.validatePasswordInput=function(element,doMark)
{hideToolTip(element);if(element.value=="")
{markInput(element,InputMarks.NoMark);return;}
var email=element.parentNode.parentNode.children[1].firstElementChild.value;var passErr=this.checkPassword(element.value,email);if(passErr&&passErr!="")
{showErrorTip(element.id,passErr);return;}
if(doMark)
{markInput(element,InputMarks.Valid);}
else
{markInput(element,InputMarks.NoMark);}}
PwcAuth.prototype.onRegistrationTabClicked=function()
{if(window.location.href.indexOf("#regPWC")!=-1)
{return;}
window.location='#regPWC';var regEmailEdit=document.getElementById("pwcRegisterWndEmailEdit");var regPasswordEdit=document.getElementById("pwcRegisterWndPasswordEdit");hideToolTip(regEmailEdit);hideToolTip(regPasswordEdit);markInput(regEmailEdit,InputMarks.NoMark);markInput(regPasswordEdit,InputMarks.NoMark);if(this.IsJoinWnd)
{if(document.getElementById("jpwcLoginWndEmailEdit").value.trim()!="")
{regEmailEdit.value=document.getElementById("jpwcLoginWndEmailEdit").value;document.getElementById("jpwcLoginWndPasswordEdit").value="";document.getElementById("pwcRegisterWndPasswordEdit").value="";this.validateEmailInput(regEmailEdit,'yesmarktheinputpleasethankyou');}}
else
{if(document.getElementById("pwcLoginWndEmailEdit").value.trim()!="")
{regEmailEdit.value=document.getElementById("pwcLoginWndEmailEdit").value;document.getElementById("pwcLoginWndPasswordEdit").value="";document.getElementById("pwcRegisterWndPasswordEdit").value="";this.validateEmailInput(regEmailEdit,'yesmarktheinputpleasethankyou');}}}
PwcAuth.prototype.onAuthTabClicked=function()
{if(window.location.href.indexOf("#authPWC")!=-1)
{return;}
window.location='#authPWC';var authEmailEdit=undefined;var authPasswordEdit=undefined;if(this.IsJoinWnd)
{authEmailEdit=document.getElementById("jpwcLoginWndEmailEdit");authPasswordEdit=document.getElementById("jpwcLoginWndPasswordEdit");}
else
{authEmailEdit=document.getElementById("pwcLoginWndEmailEdit");authPasswordEdit=document.getElementById("pwcLoginWndPasswordEdit");}
hideToolTip(authEmailEdit);hideToolTip(authPasswordEdit);markInput(authEmailEdit,InputMarks.NoMark);markInput(authPasswordEdit,InputMarks.NoMark);if(this.IsJoinWnd)
{if(document.getElementById("jpwcRegisterWndEmailEdit").value.trim()!="")
{authEmailEdit.value=document.getElementById("jpwcRegisterWndEmailEdit").value;document.getElementById("jpwcLoginWndPasswordEdit").value="";document.getElementById("pwcRegisterWndPasswordEdit").value="";this.validateEmailInput(authEmailEdit);}}
else
{if(document.getElementById("pwcRegisterWndEmailEdit").value.trim()!="")
{authEmailEdit.value=document.getElementById("pwcRegisterWndEmailEdit").value;document.getElementById("pwcLoginWndPasswordEdit").value="";document.getElementById("pwcRegisterWndPasswordEdit").value="";this.validateEmailInput(authEmailEdit);}}}
PwcAuth.prototype.hideErrorToolTips=function()
{if(window.location.href.indexOf("#authPWC")!=-1)
{if(this.IsJoinWnd)
{hideErrorTip(document.getElementById("jpwcLoginWndEmailEdit"));hideErrorTip(document.getElementById("jpwcLoginWndPasswordEdit"));}
else
{hideErrorTip(document.getElementById("pwcLoginWndEmailEdit"));hideErrorTip(document.getElementById("pwcLoginWndPasswordEdit"));}}
else
{hideErrorTip(document.getElementById("pwcRegisterWndEmailEdit"));hideErrorTip(document.getElementById("pwcRegisterWndPasswordEdit"));}}
PwcAuth.prototype.popupErrorToolTips=function()
{if(window.location.href.indexOf("#authPWC")!=-1)
{if(this.IsJoinWnd)
{popupErrorTooltip("jpwcLoginWndEmailEdit");popupErrorTooltip("jpwcLoginWndPasswordEdit");}
else
{popupErrorTooltip("pwcLoginWndEmailEdit");popupErrorTooltip("pwcLoginWndPasswordEdit");}}
else
{popupErrorTooltip("pwcRegisterWndEmailEdit");popupErrorTooltip("pwcRegisterWndPasswordEdit");}}
PwcAuth.prototype.showAuthForm=function()
{setDivDisplay("authPWC","block");setDivDisplay("regPWC","block");var openRegTab=app.getConfig("OpenRegTab","True");if(openRegTab=="True")
{if(launcherMainInfo.notFirstLogin||launcherMainInfo.notFirstLaunch)
{window.location='#authPWC';}
else
{launcherMainInfo.notFirstLogin=true;window.location='#regPWC';document.getElementById("multiRemember").checked=true;}}
else
{window.location='#authPWC';}}