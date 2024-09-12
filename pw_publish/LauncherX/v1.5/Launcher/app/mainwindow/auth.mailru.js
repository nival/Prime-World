
var MAILRU_GC_STATES={MGC_READY:0,MGC_GAME_STARTED:0,MGC_DOWNLOADING:1,MGC_PATCHING:3,MGC_NO_ENOUGH_DISK_SPACE:4,MGC_ERROR:5,MGC_NEED_REPAIR:6,MGC_REPAIR:7,MGC_INITIALIZING:8,MGC_DISABLE_WRITE_STATE:100,MGC_CLOSING:101};deriveClass(MailRuAuth,SocialNetAuth,"MailRuAuth");function MailRuAuth(parent)
{MailRuAuth.__base.constructor.apply(this,arguments);this.name=AuthNetworks.MAILRU;this.windowDescription="mruWindowDescription";this.textId="mruAuthPanelText";this.markImage="images/mmInfo.png";this.mainAuthPanelImage="images/mm.png";this.connectNewImage="images/main-button-selectNetwork-mm.png";this.checkConnectionErrId="cantCheckSocNetMru";this.uniTitleId="SN_MRU_UniTitleSimple";this.loginURL=expandURI(app.getConfig("Authorization.MailRuLoginAddr",""));this.authRedirUrl=app.getConfig("Authorization.MailRuAuthRedirAddr").toLowerCase();;this.socialNetLocName=getLocalizedString("mruAuthName","innerHTML");if(usingMailRuGC){this.stopOnServerAuthFailed=true;this.userConfirmRequired=false;var params={access_token:app.getCommandLineOption("--mm_session_key"),x_mailru_vid:app.getCommandLineOption("--mm_uid")};this.processAuthToken(params);}}
MailRuAuth.prototype.__new=function(parent)
{return new MailRuAuth(parent);}
MailRuAuth.prototype.applyCachedValues=function(cachedValues)
{if(MailRuAuth.__base.applyCachedValues.apply(this,arguments))
{this.snRefreshToken=cachedValues.snRefreshToken;return true;}
return false;}
MailRuAuth.prototype.prepareCachedData=function()
{var cache=MailRuAuth.__base.prepareCachedData.apply(this,arguments);if(this.snRefreshToken=="")
delete this.snRefreshToken;cache.snRefreshToken=this.snRefreshToken;return cache;}
MailRuAuth.prototype.processAuthToken=function(params)
{delete this.loggedIn;if(params.error)
{this.makeAuthError(getAuthErrorText("SN_MRU_",params.error,params.error_description));this.parent.onSNAuthError(this);}
else
{this.authToken=params['access_token'];this.snRefreshToken=params['refresh_token'];this.userId=params['x_mailru_vid'];if(this.getUserData())
{if(onlyUpdateMode)
this.parent.onAuthComplete();else
this.parent.onSNAuthSuccess(this);}
else
{this.parent.onSNAuthError(this);}}}
MailRuAuth.prototype.getUserData=function()
{if(usingMailRuGC){this.loggedIn=true;return true;}
if(this.loggedIn)
return true;delete this.loggedIn;var url=app.getConfig("Authorization.MailRuGetData","");url=expandURI(url,this);var prms=[];prms[prms.length]="method=users.getInfo";prms[prms.length]="app_id="+app.getConfig("Authorization.MailRuAppId");prms[prms.length]="session_key="+this.authToken;prms[prms.length]="secure=0";prms.sort();var appKey=app.getConfig("Authorization.MailRuSecret","");var prmsStr=prms.join("");this.logPrivate("prms= "+prmsStr);this.logPrivate("private_key= "+appKey);this.logPrivate("uid= "+this.userId);var sig=app.getHash([this.userId,prmsStr,appKey]);prms[prms.length]="sig="+sig;url+=prms.join("&");var data=httpRequest(url);if(data.valid)
{try
{eval("data = "+data.data);this.loggedIn=true;return true;}
catch(e)
{var err=""+e;this.makeAuthError(getAuthErrorText("SN_MRU_",err,err));}}
else
{this.lastError=data;delete this.authToken;this.lastError.errorTitle=getLocalizedString(this.windowDescription);}
return false;}
MailRuAuth.prototype.refreshToken=function()
{delete this.loggedIn;if(!this.snRefreshToken)
return false;var prms={refresh_token:this.snRefreshToken,grant_type:"refresh_token",client_id:app.getConfig("Authorization.MailRuAppId",""),client_secret:app.getConfig("Authorization.MailRuSecret","")};var url=app.getConfig("Authorization.MailRuGetToken","");var reqData=joinRequestParameters(prms);var data=httpRequest(url,{method:"POST",headers:{"ContentTypeHeader":"application/x-www-form-urlencoded"},"data":reqData});if(data.valid)
{try
{eval("data = "+data.data);if(data.access_token&&data.access_token!="")
{this.authToken=data.access_token;return true;}}
catch(e)
{this.logWarning("refreshToken error: "+e);}}
else
{this.logWarning("refreshToken error: errorType = "+data.errorType+", desc = "+data.errorMessage);this.lastError=data;this.lastError.errorTitle=getLocalizedString(this.windowDescription);}
delete this.authToken;return false;}
MailRuAuth.prototype.fillRequestParams=function(prms,prefix)
{MailRuAuth.__base.fillRequestParams.apply(this,arguments);if(!prefix)
prefix="";prms["snrefresh_token"+prefix]=this.snRefreshToken;}
MailRuAuth.updateContentProgress=function(curDownloaded,totalForDownload,curApplied,totalForApply,isRepair){if(totalForDownload!=curDownloaded){app.writeMailRuState(MAILRU_GC_STATES.MGC_DOWNLOADING,isRepair?getLocalizedString("repairFilesText","innerHTML"):getLocalizedString("launcherUpdatePercent","innerHTML"),curDownloaded,totalForDownload);}else{var state=MAILRU_GC_STATES.MGC_PATCHING;if(isRepair)
state=MAILRU_GC_STATES.MGC_REPAIR;app.writeMailRuState(state,getLocalizedString("PatchManifestState_Patching"),curApplied,totalForApply);}}
MailRuAuth.onCheckFilesProgress=function(result){if(result.patchesTotalForApply>0){app.writeMailRuState(MAILRU_GC_STATES.MGC_REPAIR,getLocalizedString("repairFilesText","innerHTML"),result.patchesCurApplied*100.0,result.patchesTotalForApply*100.0);}}