
deriveClass(VkAuth,SocialNetAuth,"VkAuth");function VkAuth(parent)
{VkAuth.__base.constructor.apply(this,arguments);this.name=AuthNetworks.VKONTAKTE;this.windowDescription="vkWindowDescription";this.textId="vkAuthPanelText";this.markImage="images/vkInfo.png";this.mainAuthPanelImage="images/vk.png";this.connectNewImage="images/main-button-selectNetwork-vk.png";this.checkConnectionErrId="cantCheckSocNetVk";this.uniTitleId="SN_VK_UniTitleSimple";this.checkPermissionsUrl="https://api.vk.com/method/account.getAppPermissions?v=5.71";this.loginURL=expandURI(app.getConfig("Authorization.VkLoginAddr",""));this.checkPermissionsValues={friends:2,offline:65536};this.authRedirUrl=app.getConfig("Authorization.VkAuthRedirURI").toLowerCase();;this.socialNetLocName=getLocalizedString("vkAuthName","innerHTML");}
VkAuth.prototype.__new=function(parent)
{return new VkAuth(parent);}
VkAuth.prototype.storeCookies=function()
{}
VkAuth.prototype.applyCookies=function()
{}
VkAuth.prototype.processAuthToken=function(params)
{delete this.loggedIn;if(params.access_token)
{this.authToken=params.access_token;this.userId=params.user_id;if(this.getUserData())
{this.parent.onSNAuthSuccess(this);}
else
{this.parent.onSNAuthError(this);}}
else
{this.makeAuthError(getAuthErrorText("SN_VK_",params.error,params.error_description));this.parent.onSNAuthError(this);}}
VkAuth.prototype.getUserData=function()
{if(this.loggedIn)
return true;delete this.loggedIn;var url=this.checkPermissionsUrl+"&uid="+this.userId+"&access_token="+this.authToken;var data=httpRequest(url,{"receiveBodyOnError":true,"useTLS":true});if(data.valid)
{try
{eval("data="+data.data);var response=data.response;for(var permName in this.checkPermissionsValues)
{var perm=this.checkPermissionsValues[permName];if((response&perm)!=perm)
return this.makeAuthError(getLocalizedString("SN_VK_access_denied"));}
this.loggedIn=true;return true;}
catch(e)
{return this.makeAuthError(""+e);}}
delete this.authToken;this.lastError=data;this.lastError.errorTitle=getLocalizedString(this.windowDescription);return false;}
VkAuth.prototype.refreshToken=function()
{this.log("Trying to refresh access_token");if(this.authToken)
return true;delete this.loggedIn;return false;}
VkAuth.prototype.onBeforeNavigate=function(request)
{var frame=request.getFrame();if(!frame)
{var url=request.getNewUrl();app.logMessage("Got request to new window. Open external browser on: "+url);openExternalBrowser(url);request.accept(false);}}