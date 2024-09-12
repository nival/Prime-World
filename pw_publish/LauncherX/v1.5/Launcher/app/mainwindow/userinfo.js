
var Sex={UNKNOWN:0,MALE:1,FEMALE:2}
function UserInfo()
{this.sns={};this.__className="UserInfo";}
UserInfo.prototype.fillRequestParams=function(prms,prefix)
{if(!prefix)
prefix="";prms["auid"+prefix]=this.auid;prms["token"+prefix]=this.pwToken;}
UserInfo.prototype.logout=function()
{delete this.loggedIn;delete this.allLoggedIn;for(var sn in this.sns)
{var socialNet=this.sns[sn];if(socialNet.isLoggedIn())
socialNet.logout();socialNet.parent=authMain;}}
UserInfo.prototype.isLoggedIn=function()
{return this.loggedIn;}
UserInfo.prototype.getAUID=function()
{return this.auid;}
UserInfo.prototype.getFraction=function()
{return this.fraction;}
UserInfo.prototype.getToken=function()
{return this.pwToken;}
UserInfo.prototype.getSecret=function()
{return this.pwSign;}
UserInfo.prototype.getServer=function()
{return this.server;}
UserInfo.prototype.deleteServer=function()
{delete this.server;app.logMessage("'server' variable successfully deleted");}
UserInfo.prototype.onSNAuthSuccess=function(socialNet)
{app.logDebug("[userInfo] onAuthSuccess: "+socialNet.name);var curSocialNet=this.sns[socialNet.name];if(socialNet.IsJoinWnd==true&&socialNet.forMerge==false)
{socialNet.onJoinSNAuthSuccess();}
if(curSocialNet&&curSocialNet.getUserId()==socialNet.getUserId())
{this.sns[socialNet.name]=socialNet;authMain.displayUserData();authMain.saveAuthData();return true;}
showErrorMessage(getLocalizedString("wrongUserAccount"));return false;}
UserInfo.prototype.onSNAuthError=function(socialNet,notShowError)
{authMain.displayUserData();if(!notShowError)
{if(socialNet.stopOnServerAuthFailed)
showErrorMessage(socialNet.lastError,closeClick);else
showErrorMessage(socialNet.lastError);}}
UserInfo.prototype.updateUserInfo=function(socialNet,result)
{app.logMessage("update user info ["+socialNet.name+"]");var info=result.info;this.nickname=info.nick;if(!this.nickname||this.nickname=="")
this.nickname=socialNet.userId;this.avatarURL=prepareAvatarUrl(info.photo);this.fraction=info.fraction;this.sex=info.sex;if(this.sex==Sex.UNKNOWN)
this.sex=Sex.MALE;if(this.fraction)
{var fracName="fraction_"+parseInt(this.fraction);this.fractionName=getLocalizedString(fracName);if(fracName==this.fractionName)
{this.fraction=-1;this.fractionName="";}}
if(!this.fractionName||this.fractionName=="")
{this.fractionName=getLocalizedString("fraction_none");this.fraction=-1;}
this.fame=info.fame;if(this.fame)
{while(this.fame.length>1&&this.fame.substring(0,1)=="0")
this.fame=this.fame.substring(1);}
if(!this.fame||this.fame=="")
this.fame="0";this.pwToken=result.token;this.server=result.server;if(this.server=="")
{app.logWarning("received empty string as 'server'. Removing server.");this.deleteServer();}
app.logMessage("UserInfo.updateUserInfo: server="+this.server+" fraction="+this.fraction+" sex="+this.sex+" fame="+this.fame+" avatar="+this.avatarURL);this.auid=info.auid;this.pwSign=result.pwSign;}
UserInfo.prototype.authOnServer=function(socialNet)
{delete this.auid;var result=socialNet.getAUID();if(result._authError)
{this.lastError=result;app.logWarning("authOnServer error "+JSON.stringify(result));return false;}
else
app.logMessage("authOnServer success sn_id="+socialNet.name);this.updateUserInfo(socialNet,result);var fsn=result.fsn;this.sns={};for(var sn in result.sns){if(sn==socialNet.name){socialNet.parent=this;this.sns[socialNet.name]=socialNet;}
else{var newSocialNet=authMain.getSocialNetwork(sn);if(newSocialNet){var cachedValues=authMain.getCachedSocialNet(sn,result.sns[sn]);this.sns[sn]=newSocialNet.createNew(this,cachedValues);}}}
this.fsn=socialNet;return true;}
UserInfo.prototype.getFSN=function()
{return this.fsn;}
UserInfo.prototype.getSNS=function()
{return this.sns;}
UserInfo.prototype.processSNSQueue=function()
{app.logMessage("Process authorization for SNS queue");delete this.loggedIn;this.allLoggedIn=true;var snName;var socialNet;for(snName in this.sns)
{socialNet=this.sns[snName];if(socialNet.isLoggedIn())
{this.loggedIn=true;break;}}
for(snName in this.sns)
{socialNet=this.sns[snName];if(!socialNet.isLoggedIn())
{if(socialNet.refreshToken())
socialNet.getUserData();}
if(socialNet.isLoggedIn())
{app.logMessage("Social network '"+snName+"' authorized");this.loggedIn=true;}
else
{app.logMessage("Social network '"+snName+"' not authorized");delete this.allLoggedIn;}}
app.logMessage("Authorization for SNS finished. loggedIn="+this.loggedIn+", allLoggedIn="+this.allLoggedIn);}