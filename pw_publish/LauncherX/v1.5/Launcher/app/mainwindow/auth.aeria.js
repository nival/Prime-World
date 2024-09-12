
deriveClass(AeriaAuth,SocialNetAuth,"AeriaAuth");function AeriaAuth(parent)
{AeriaAuth.__base.constructor.apply(this,arguments);this.webBillingSupported=false;this.name=AuthNetworks.AERIA;this.windowDescription="aeWindowDescription";this.textId="aeAuthPanelText";this.markImage="images/aeInfo.png";this.mainAuthPanelImage="images/ae.png";this.connectNewImage="images/main-button-selectNetwork-ae.png";this.loginURL=expandURI(app.getConfig("Authorization.AeriaLoginAddr",""));this.authRedirUrl=app.getConfig("Authorization.AeriaAuthRedirAddr").toLowerCase();this.socialNetLocName=getLocalizedString("aeAuthName","innerHTML");this.certDomain=app.getConfig("Authorization.AeriaCN","");if(document.getElementsByClassName("ap_content-action reverse").length){document.getElementsByClassName("ap_content-action reverse")[0].className="ap_content-action";}}
AeriaAuth.prototype.__new=function(parent)
{return new AeriaAuth(parent);}
AeriaAuth.prototype.applyCachedValues=function(cachedValues)
{if(AeriaAuth.__base.applyCachedValues.apply(this,arguments))
{this.snRefreshToken=cachedValues.snRefreshToken;return true;}
return false;}
AeriaAuth.prototype.prepareCachedData=function()
{var cache=AeriaAuth.__base.prepareCachedData.apply(this,arguments);if(!this.snRefreshToken||this.snRefreshToken=="")
delete this.snRefreshToken;cache.snRefreshToken=this.snRefreshToken;return cache;}
AeriaAuth.prototype.processAuthToken=function(params)
{this.log("process auth token");if(params.error)
{this.makeAuthError(getAuthErrorText("SN_AE_",params.error,params.error));this.parent.onSNAuthError(this);return;}
if(!params.code)
{this.makeAuthError(getLocalizedString("aeriaNoCodeReceivedError"));this.parent.onSNAuthError(this);return;}
this.authCode=params.code;var tokensReceived=this.getTokens(this.authCode);if(tokensReceived)
{var dataReceived=this.getUserData();if(dataReceived)
{this.parent.onSNAuthSuccess(this);return;}}
this.parent.onSNAuthError(this);}
AeriaAuth.prototype.getTokens=function(authCode)
{this.log("get tokens");var params=joinRequestParameters({"grant_type":"authorization_code","code":authCode,"client_id":app.getConfig("Authorization.AeriaAppId",""),"client_secret":app.getConfig("Authorization.AeriaSecret","")});this.logPrivate("request aeria token: "+params);var url=app.getConfig("Authorization.AeriaGetToken","");var response=sslRequest(url,{"CertDomain":this.certDomain,method:"POST",headers:{"ContentTypeHeader":"application/x-www-form-urlencoded"},"data":params});this.logPrivate("access token response: "+JSON.stringify(response));var data=this.parseResponseOrError(response);if(data&&data.access_token&&data.refresh_token)
{this.log("get tokens success");this.authToken=data.access_token;this.snRefreshToken=data.refresh_token;this.logPrivate("access_token="+this.authToken+" refresh_token="+this.snRefreshToken);return true;}
else
{delete this.authToken;delete this.snRefreshToken;this.logWarning("get tokens fail");this.fillLastError(response);}
return false;}
AeriaAuth.prototype.getUserData=function()
{if(this.loggedIn)
return true;delete this.loggedIn;this.log("get user data");var url=expandURI(app.getConfig("Authorization.AeriaGetData"),this);this.logPrivate("get user data: url="+url);var response=sslRequest(url,{"CertDomain":this.certDomain});this.logPrivate("get user data response: "+JSON.stringify(response));var responseData=this.parseResponseOrError(response);if(responseData)
responseData=responseData.data;if(responseData&&responseData.uid)
{this.userId=responseData.uid;this.log("get user data success. userId="+this.userId);this.loggedIn=true;return true;}
else
{this.logWarning("get user data fail"+JSON.stringify(response));delete this.authToken;this.fillLastError(response);}
return false;}
AeriaAuth.prototype.refreshToken=function()
{this.log("refresh token");var requestData=joinRequestParameters({"grant_type":"refresh_token","refresh_token":this.snRefreshToken,"client_id":app.getConfig("Authorization.AeriaAppId","")});var url=expandURI(app.getConfig("Authorization.AeriaRefreshToken"),this);url=url+"?"+requestData;var response=sslRequest(url,{"CertDomain":this.certDomain});this.logPrivate("refresh token response: "+JSON.stringify(response));var responseData=this.parseResponseOrError(response);if(responseData&&responseData.access_token&&responseData.refresh_token)
{this.log("refresh token success");this.authToken=responseData.access_token;this.snRefreshToken=responseData.refresh_token;return true;}
else
{this.logWarning("refresh token fail - "+JSON.stringify(response));delete this.authToken;this.fillLastError(response);}
return false;}
AeriaAuth.prototype.fillLastError=function(data)
{this.lastError=data;this.lastError.errorTitle=getLocalizedString(this.windowDescription);}
AeriaAuth.prototype.fillRequestParams=function(prms,prefix)
{AeriaAuth.__base.fillRequestParams.apply(this,arguments);if(!prefix)
prefix="";prms["snrefresh_token"+prefix]=this.snRefreshToken;}
AeriaAuth.prototype.parseResponseOrError=function(response)
{var result;if(response&&response.valid)
{try
{eval("result="+response.data);this.logPrivate(JSON.stringify(result));}
catch(e)
{this.makeAuthError(""+e);return false;}
return result;}
return false;}
AeriaAuth.prototype.isInfoMarkVisible=function()
{return false;}
AeriaAuth.prototype.onPageLoadError=function(url,errorCode,errorMessage){this.logWarning(" handled error ["+errorCode+"]:"+errorMessage);AeriaAuth.__base.onPageLoadError.apply(this,arguments);}