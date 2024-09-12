
deriveClass(DltAuth,SocialNetAuth,"DltAuth");function DltAuth(parent)
{DltAuth.__base.constructor.apply(this,arguments);this.name=AuthNetworks.DRAUGAS;this.windowDescription="dltWindowDescription";this.textId="dltAuthPanelText";this.markImage="images/dltInfo.png";this.mainAuthPanelImage="images/dlt.png";this.connectNewImage="images/main-button-selectNetwork-dlt.png";this.checkConnectionErrId="cantCheckSocNetDlt";this.uniTitleId="SN_DLT_UniTitleSimple";this.getTokenUrl=app.getConfig("Authorization.DltGetToken").toLowerCase();this.refreshTokenUrl=app.getConfig("Authorization.DltRefreshToken").toLowerCase();this.loginURL=expandURI(app.getConfig("Authorization.DltLoginAddr"));this.getDataUrl=app.getConfig("Authorization.DltGetData").toLowerCase();this.authRedirUrl=app.getConfig("Authorization.DltAuthRedirUrl").toLowerCase();this.socialNetLocName=getLocalizedString("dltAuthName","innerHTML");if(document.getElementsByClassName("ap_content-action reverse").length){document.getElementsByClassName("ap_content-action reverse")[0].className="ap_content-action";}}
DltAuth.prototype.__new=function(parent)
{return new DltAuth(parent);}
DltAuth.prototype.applyCachedValues=function(cachedValues)
{if(DltAuth.__base.applyCachedValues.apply(this,arguments))
{this.email=cachedValues.email;this.snRefreshToken=cachedValues.snRefreshToken;return true;}
return false;}
DltAuth.prototype.prepareCachedData=function()
{var cache=DltAuth.__base.prepareCachedData.apply(this,arguments);cache.email=this.email;cache.snRefreshToken=this.snRefreshToken;return cache;}
DltAuth.prototype.storeCookies=function()
{var list=this.browserWindow.getCookies("http://www.draugas.lt");var cookies="";for(var i=0;i<list.length;i++)
{var cookie=list[i];var name=cookie.name;if(name=="CI"||name=="IDENT"||name=="CV")
{cookies+=cookie.toRawForm()+"\r\n";}}
authMain.saveCookies("dlt",cookies);}
DltAuth.prototype.applyCookies=function()
{var cookies=authMain.getCookies("dlt");if(cookies)
this.browserWindow.setCookies(cookies);}
DltAuth.prototype.onBeforeCreateWindow=function(baseUrl,info)
{info.setAction(CreateNewWindowActions.ACTION_IGNORE);this.browserWindow.gotoUrl(baseUrl);}
DltAuth.prototype.onAuthFrameLoaded=function(isOk)
{if(this.browserWindow)
{this.browserWindow.addApplicationScriptObject("_app","");this.browserWindow.executeScript("_app.transferWebElement('dlt', document);","");}}
DltAuth.prototype.onAuthUrlChanged=function(url)
{app.logDebug("DltAuth [onAuthUrlChanged] url changed to "+url);app.logDebug("DltAuth [onAuthUrlChanged] authRedirUrl="+this.authRedirUrl);var redirUrl=this.authRedirUrl;if(url.substring(0,redirUrl.length).toLowerCase()==redirUrl)
{app.logDebug("DltAuth [onAuthUrlChanged] destroy browser window");var prms=urldecode(url.substring(redirUrl.length));if(document.getElementById("multiRemember").checked)
this.storeCookies();else
authMain.saveCookies(this.name,{});this.destroyBrowserWindow();this.processAuthToken(prms);}}
DltAuth.prototype.processAuthToken=function(params)
{if(!params.error)
{var authCode=params['code'];app.logDebug("Got code : "+authCode);var reqData=joinRequestParameters({"code":authCode,"client_id":app.getConfig("Authorization.DltAppId"),"client_secret":app.getConfig("Authorization.DltAuthSecret"),"redirect_uri":app.getConfig("Authorization.DltAuthRedirUrl")});this.logPrivate("request draugas token: "+reqData);var data=httpRequest(this.getTokenUrl,{method:"POST",headers:{"ContentTypeHeader":"application/x-www-form-urlencoded"},"data":reqData});if(data.valid)
{try
{eval("data="+JSON.stringify(data.data));data=data.split("&");var dict={};for(var i=0;i<data.length;i++)
{dict[data[i].split("=")[0]]=data[i].split("=")[1];}
app.logDebug("Resulting dict = "+JSON.stringify(dict));data=dict;}
catch(e)
{app.logDebug("Failed to eval data:"+data.data);params.error=""+e;}
if(!params.error)
{if(data.access_token)
{this.authToken=data.access_token;this.snRefreshToken=data.access_token;if(this.getUserData())
this.parent.onSNAuthSuccess(this);else
this.parent.onSNAuthError(this);return;}
else
{params.error=data.errorMessage;}}}
else
{this.lastError=data;this.lastError.errorTitle=getLocalizedString(this.windowDescription);this.parent.onSNAuthError(this);return;}}
if(params.error)
{this.makeAuthError(getAuthErrorText("SN_DLT_",params.error,params.error));this.parent.onSNAuthError(this);}}
DltAuth.prototype.getUserData=function()
{if(this.loggedIn)
return true;delete this.loggedIn;var url=expandURI(this.getDataUrl,this);var data=httpRequest(url,{headers:{"ContentTypeHeader":"application/x-www-form-urlencoded","Authorization":"Bearer "+this.authToken}});if(data.valid)
{try
{eval("data = "+data.data);this.userId=data.Id;this.email=data.Email;this.nickname=data.Name;this.loggedIn=true;return true;}
catch(e)
{this.makeAuthError(""+e);}}
else
{delete this.authToken;this.lastError=data;this.lastError.errorTitle=getLocalizedString(this.windowDescription);}
return false;}
DltAuth.prototype.logout=function()
{this.log("logout");DltAuth.__base.logout();document.getElementById("multiRemember").checked=false;this.loggedIn=false;authMain.saveCookies(this.name,{});}
DltAuth.prototype.refreshToken=function()
{app.logDebug("Refresh token - not implemented");return true;}