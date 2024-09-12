
deriveClass(OkAuth,SocialNetAuth,"OkAuth");function OkAuth(parent)
{OkAuth.__base.constructor.apply(this,arguments);this.name=AuthNetworks.ODNOKLASSNIKI;this.windowDescription="okWindowDescription";this.textId="okAuthPanelText";this.markImage="images/okInfo.png";this.mainAuthPanelImage="images/ok.png";this.connectNewImage="images/main-button-selectNetwork-ok.png";this.checkConnectionErrId="cantCheckSocNetOk";this.uniTitleId="SN_OK_UniTitleSimple";this.loginURL=expandURI(app.getConfig("Authorization.OkLoginAddr",""));this.authRedirUrl=app.getConfig("Authorization.OkAuthRedirURI").toLowerCase();this.socialNetLocName=getLocalizedString("okAuthName","innerHTML");}
OkAuth.prototype.__new=function(parent)
{return new OkAuth(parent);}
OkAuth.prototype.applyCachedValues=function(cachedValues)
{if(OkAuth.__base.applyCachedValues.apply(this,arguments))
{this.snRefreshToken=cachedValues.snRefreshToken;return true;}
return false;}
OkAuth.prototype.prepareCachedData=function()
{var cache=OkAuth.__base.prepareCachedData.apply(this,arguments);if(this.snRefreshToken=="")
delete this.snRefreshToken;cache.snRefreshToken=this.snRefreshToken;return cache;}
OkAuth.prototype.processAuthToken=function(params)
{if(!params.error)
{var authCode=params['code'];var url=app.getConfig("Authorization.OkGetToken","");var reqData="code="+authCode+"&grant_type=authorization_code"+"&client_id="+app.getConfig("Authorization.OkAppId","")+"&client_secret="+app.getConfig("Authorization.OkAuthSecret","")+"&redirect_uri="+this.authRedirUrl;var data=httpRequest(url,{method:"POST",headers:{"ContentTypeHeader":"application/x-www-form-urlencoded"},"data":reqData});if(data.valid)
{try{eval("data = "+data.data);}
catch(e)
{params.error=""+e;}
if(!params.error)
{if(data.access_token)
{this.authToken=data.access_token;this.snRefreshToken=data.refresh_token;if(this.getUserData())
this.parent.onSNAuthSuccess(this);else
this.parent.onSNAuthError(this);return;}
else
{params.error=data.errorMessage;}}}
else
{this.lastError=data;this.lastError.errorTitle=getLocalizedString(this.windowDescription);this.parent.onSNAuthError(this);return;}}
if(params.error)
{this.makeAuthError(getAuthErrorText("SN_OK_",params.error,params.error));this.parent.onSNAuthError(this);}}
OkAuth.prototype.getUserData=function()
{if(this.loggedIn)
return true;delete this.loggedIn;var url=app.getConfig("Authorization.OkGetData","");url=expandURI(url,this);var prms=new Array();prms[prms.length]="method=users.getCurrentUser";prms[prms.length]="format=JSON";prms[prms.length]="application_key="+app.getConfig("Authorization.OkAuthPublic","");prms.sort();var sig=this.authToken+app.getConfig("Authorization.OkAuthSecret","");sig=app.getHash([sig]);var prmsStr=prms.join("");sig=app.getHash([prmsStr,sig]);prms[prms.length]="access_token="+this.authToken;prms[prms.length]="sig="+sig;url+=prms.join("&");var data=httpRequest(url);if(data.valid)
{try
{eval("data = "+data.data);this.userId=data.uid;this.loggedIn=true;return true;}
catch(e)
{var err=""+e;this.makeAuthError(getAuthErrorText("SN_OK_",err,err));}}
else
{this.lastError=data;delete this.authToken;this.lastError.errorTitle=getLocalizedString(this.windowDescription);}
return false;}
OkAuth.prototype.refreshToken=function()
{delete this.loggedIn;if(!this.snRefreshToken)
return false;var prms={refresh_token:this.snRefreshToken,grant_type:"refresh_token",client_id:app.getConfig("Authorization.OkAppId",""),client_secret:app.getConfig("Authorization.OkAuthSecret","")};var url=app.getConfig("Authorization.OkGetToken","");var reqData=joinRequestParameters(prms);var data=httpRequest(url,{method:"POST",headers:{"ContentTypeHeader":"application/x-www-form-urlencoded"},"data":reqData});if(data.valid)
{try
{eval("data = "+data.data);if(data.access_token&&data.access_token!="")
{this.authToken=data.access_token;return true;}}
catch(e)
{this.logWarning("refreshToken error: "+e);}}
else
{this.logWarning("refreshToken error: errorType = "+data.errorType+", desc = "+data.errorMessage);this.lastError=data;this.lastError.errorTitle=getLocalizedString(this.windowDescription);}
delete this.authToken;return false;}
OkAuth.prototype.fillRequestParams=function(prms,prefix)
{OkAuth.__base.fillRequestParams.apply(this,arguments);if(!prefix)
prefix="";prms["snrefresh_token"+prefix]=this.snRefreshToken;}