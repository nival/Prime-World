
deriveClass(ZzimaAuth,SocialNetAuth,"ZzimaAuth");function ZzimaAuth(parent)
{ZzimaAuth.__base.constructor.apply(this,arguments);this.name=AuthNetworks.ZZIMA;this.windowDescription=this.name+"WindowDescription";this.textId=this.name+"AuthPanelText";this.markImage="images/zzimaInfo.png";this.mainAuthPanelImage="images/zzima.png";this.connectNewImage="images/main-button-selectNetwork-zzima.png";this.checkConnectionErrId="cantCheckSocNetZzima";this.uniTitleId="SN_ZZIMA_UniTitleSimple";this.loginURL=expandURI(app.getConfig("Authorization.ZzimaLoginAddr",""));this.authRedirUrl=app.getConfig("Authorization.ZzimaAuthRedirAddr").toLowerCase();;this.socialNetLocName=getLocalizedString(this.name+"AuthName","innerHTML");}
ZzimaAuth.prototype.__new=function(parent)
{return new ZzimaAuth(parent);}
ZzimaAuth.prototype.applyCachedValues=function(cachedValues)
{if(ZzimaAuth.__base.applyCachedValues.apply(this,arguments))
{this.authCode=cachedValues.authCode;return true;}
return false;}
ZzimaAuth.prototype.prepareCachedData=function()
{var cache=ZzimaAuth.__base.prepareCachedData.apply(this,arguments);if(this.authCode=="")
delete this.authCode;cache.authCode=this.authCode;return cache;}
ZzimaAuth.prototype.processAuthToken=function(params)
{delete this.loggedIn;if(params.error)
{this.makeAuthError(getAuthErrorText("SN_ZZIMA_",params.error,params.error_description));this.parent.onSNAuthError(this);}
else
{this.authCode=params['code'];if(this.getToken())
{this.processAuthTokenComplete();}
else
{this.parent.onSNAuthError(this);}}}
ZzimaAuth.prototype.getToken=function()
{if(this.loggedIn)
return true;delete this.loggedIn;var url=app.getConfig("Authorization.ZzimaGetToken","");url=expandURI(url,this);var prms=[];prms[prms.length]="client_secret="+app.getConfig("Authorization.ZzimaSecret");prms[prms.length]="client_id="+app.getConfig("Authorization.ZzimaAppId");prms[prms.length]="code="+this.authCode;prms[prms.length]="redirect_uri="+app.getConfig("Authorization.ZzimaAuthRedirAddr");var reqData=prms.join("&");var data=httpRequest(url,{method:"POST",headers:{"ContentTypeHeader":"application/x-www-form-urlencoded"},"data":reqData});if(data.valid){try{eval("data = "+data.data);if(data.error){this.makeAuthError(getAuthErrorText("SN_ZZIMA_",data.error,data.error_description));}else{this.userId=data.user_id;this.authToken=data.access_token;return true;}}
catch(e){var err=""+e;this.makeAuthError(getAuthErrorText("SN_ZZIMA_",err,err));}}
else{this.lastError=data;delete this.authToken;this.lastError.errorTitle=getLocalizedString(this.windowDescription);}
return false;}
ZzimaAuth.prototype.processAuthTokenComplete=function()
{if(this.getUserData())
{if(onlyUpdateMode)
this.parent.onAuthComplete();else
this.parent.onSNAuthSuccess(this);return true;}
else
{this.parent.onSNAuthError(this);return false;}}
ZzimaAuth.prototype.getUserData=function()
{if(this.loggedIn)
return true;delete this.loggedIn;var url=app.getConfig("Authorization.ZzimaGetData","");url=expandURI(url,this);var prms=[];prms[prms.length]="userhash="+this.authToken;var reqData=prms.join("&");var data=httpRequest(url,{method:"POST",headers:{"ContentTypeHeader":"application/x-www-form-urlencoded"},"data":reqData});if(data.valid)
{try
{eval("data = "+data.data);this.loggedIn=true;return true;}
catch(e)
{var err=""+e;this.makeAuthError(getAuthErrorText("SN_ZZIMA_",err,err));}}
else
{this.lastError=data;delete this.authToken;this.lastError.errorTitle=getLocalizedString(this.windowDescription);}
return false;}
ZzimaAuth.prototype.refreshToken=function()
{delete this.loggedIn;if(!this.authCode)
return false;if(this.getUserData())
return true;else if(this.getToken()){this.processAuthTokenComplete();return true;}else{this.logWarning("refreshToken error");delete this.authToken;return false;}}