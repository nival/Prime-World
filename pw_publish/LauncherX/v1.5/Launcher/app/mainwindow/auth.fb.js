
deriveClass(FbAuth,SocialNetAuth,"FbAuth");function FbAuth(parent)
{FbAuth.__base.constructor.apply(this,arguments);this.name=AuthNetworks.FACEBOOK;this.windowDescription="fbWindowDescription";this.textId="fbAuthPanelText";this.markImage="images/fbInfo.png";this.mainAuthPanelImage="images/fb.png";this.connectNewImage="images/main-button-selectNetwork-fb.png";this.checkConnectionErrId="cantCheckSocNetFb";this.checkPermissionsUrl="https://graph.facebook.com/v2.8/me/permissions";this.uniTitleId="SN_FB_UniTitleSimple";this.refreshTokenUrl="https://graph.facebook.com/v2.8/oauth/access_token";this.loginURL=expandURI(app.getConfig("Authorization.FbLoginAddr",""));this.getDataUrl="https://graph.facebook.com/v2.8/me/?fields=id,name,email,gender";this.authRedirUrl=app.getConfig("Authorization.FbAuthRedirURI").toLowerCase();this.socialNetLocName=getLocalizedString("fbAuthName","innerHTML");}
FbAuth.prototype.__new=function(parent)
{return new FbAuth(parent);}
FbAuth.prototype.applyCachedValues=function(cachedValues)
{if(FbAuth.__base.applyCachedValues.apply(this,arguments))
{this.email=cachedValues.email;return true;}
return false;}
FbAuth.prototype.prepareCachedData=function()
{var cache=FbAuth.__base.prepareCachedData.apply(this,arguments);cache.email=this.email;return cache;}
FbAuth.prototype.storeCookies=function()
{var list=this.browserWindow.getCookies("https://www.facebook.com");var cookies="";for(var i=0;i<list.length;i++)
{var cookie=list[i];var name=cookie.name;if(name=="c_user"||name=="locale"||name=="lu"||name=="sct")
{cookies+=cookie.toRawForm()+"\r\n";}}
authMain.saveCookies("fb",cookies);}
FbAuth.prototype.applyCookies=function()
{var cookies=authMain.getCookies("fb");if(cookies)
this.browserWindow.setCookies(cookies);}
FbAuth.prototype.onBeforeCreateWindow=function(baseUrl,info)
{info.setAction(CreateNewWindowActions.ACTION_IGNORE);this.browserWindow.gotoUrl(baseUrl);}
FbAuth.prototype.onAuthFrameLoaded=function(isOk)
{if(this.browserWindow)
{this.browserWindow.addApplicationScriptObject("_app","");this.browserWindow.executeScript("_app.transferWebElement('fb', document);","");}}
FbAuth.prototype.processAuthToken=function(params)
{delete this.loggedIn;if(params.error)
{this.makeAuthError(getAuthErrorText("SN_FB_",params.error,params.error_description));this.parent.onSNAuthError(this);}
else
{this.authToken=params['access_token'];if(this.getUserData())
{this.parent.onSNAuthSuccess(this);}
else
{this.parent.onSNAuthError(this);}}}
FbAuth.prototype.getUserData=function()
{if(this.loggedIn)
return true;delete this.loggedIn;var url=this.checkPermissionsUrl+"?access_token="+this.authToken;var data=httpRequest(url,{"receiveBodyOnError":true,"useTLS":true});if(data.valid)
{try
{eval("data="+data.data);if(data&&data.data&&data.data.length>0)
{for(var index in data.data)
{if(data.data[index].permission!="email")
{continue;}
if(data.data[index].status=="granted")
{break;}
else
{return this.makeAuthError(getLocalizedString("SN_FB_access_denied"));}}}
else
{return this.makeAuthError(getLocalizedString("SN_FB_access_denied"));}}
catch(e)
{return this.makeAuthError(""+e);}}
else
{delete this.authToken;this.lastError=data;this.lastError.errorTitle=getLocalizedString(this.windowDescription);return false;}
var url=this.getDataUrl+"&access_token="+this.authToken;url=expandURI(url,this);var result=httpRequest(url,{receiveBodyOnError:true,useTLS:true});if(result.valid)
{try
{eval("result="+result.data);this.userId=result.id;this.email=result.email;this.loggedIn=true;return true;}
catch(e)
{this.makeAuthError(""+e);}}
else
{delete this.authToken;this.lastError=result;this.lastError.errorTitle=getLocalizedString(this.windowDescription);}
return false;}
FbAuth.prototype.refreshToken=function()
{this.log("Trying to refresh access_token");delete this.loggedIn;var prms={"client_id":app.getConfig("Authorization.FbAppId",""),"client_secret":app.getConfig("Authorization.FbAppSecret",""),"grant_type":"fb_exchange_token","fb_exchange_token":this.authToken};var reqData=joinRequestParameters(prms);var refreshUrl=this.refreshTokenUrl+"?"+reqData;var refreshData=httpRequest(refreshUrl,{receiveBodyOnError:true,useTLS:true});if(refreshData.valid)
{eval("refreshData="+refreshData.data);if(refreshData.access_token&&refreshData.access_token!="")
{this.authToken=refreshData.access_token;this.log("access_token updated successfully");return true;}
else
{this.logWarning("Can't refresh access_token, wrong answer:\r\n"+refreshData.data);}}
else
{this.logWarning("Can't refresh access_token:\r\n"+refreshData.errorMessage);}
return false;}