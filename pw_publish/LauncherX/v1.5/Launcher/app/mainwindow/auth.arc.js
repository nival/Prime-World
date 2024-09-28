
deriveClass(ArcAuth,SocialNetAuth,"ArcAuth");var ARC_AUTHORIZED=false;function ArcAuth(parent)
{ArcAuth.__base.constructor.apply(this,arguments);this.name=AuthNetworks.ARC;this.userConfirmRequired=false;this.stopOnServerAuthFailed=true;this.textId="arcAuthPanelText";this.socialNetLocName=getLocalizedString("arcAuthName","innerHTML");this.AC={Unavailable:503,NotFound:404,Unauthorized:401,Timeout:408,ClientNotStarted:418}
this.logoutAllowed=false;this.webBillingSupported=false;this.ignoredSC=[this.AC.Unavailable]}
ArcAuth.prototype.__new=function(parent)
{return new ArcAuth(parent);}
ArcAuth.prototype.logout=function(){this.logWarning('arc_mock::unable to logout from arc');}
ArcAuth.prototype.refreshToken=function(){if(ARC_AUTHORIZED&&this.authToken)
this.loggedIn=true;return true;}
ArcAuth.prototype.getUserData=function(){this.logWarning('arc_mock::user data mock');return true;}
ArcAuth.prototype.isInfoMarkVisible=function(){return false;}
ArcAuth.prototype.tryToLoginWithoutConfirm=function(callback){var self=this;var criticalError=false;this.log('sending auth request...');arcConnect.onAuthResponse.connect(function(result){self.log('sending auth request...Ok');if(result!=undefined&&result.valid!=undefined&&result.uid!=undefined&&result.token!=undefined){self.log('result valid: authorized with uid='+result.uid);self.userId=result.uid;self.authToken=result.token;self.loggedIn=true;ARC_AUTHORIZED=true;try{var isOk=self.parent.onSNAuthSuccess(self);if(!isOk&&self.isBlocksAuthProcess())
criticalError=true;}
catch(e){self.logWarning("exception catched on onSNAuthSuccess callback handling: "+JSON.stringify(e));}}else{var sc=result?result.statusCode:0;var err=result?result.error:'empty result';self.logWarning('result not valid: error='+err+' statusCode='+sc);if(self.ignoredSC.indexOf(sc)!=-1){self.logWarning('unhandled error, skipping');self.parent.onSNAuthError(self,true);}else{if(self.isBlocksAuthProcess())
criticalError=true;self.fillLastError(err,sc);self.parent.onSNAuthError(self);}}
if(callback)
callback(self,criticalError);});arcConnect.requestAuth();}
ArcAuth.prototype.fillLastError=function(error,code){switch(code){case this.AC.Timeout:this.lastError=getLocalizedString('arcTimeoutErrorMessage','innerHTML');break;case this.AC.ClientNotStarted:this.lastError=getLocalizedString('arcClientNotStartedErrorMessage','innerHTML');break;default:this.lastError=getLocalizedString('arcUnknownErrorMessage','innerHTML');}}