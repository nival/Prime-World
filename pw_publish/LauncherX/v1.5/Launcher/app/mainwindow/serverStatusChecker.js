
var GlobalServerStatuses={UNKNOWN:0,ONLINE:1,MAINTENANCE:2,CHECKING:100};GlobalServerStatuses.GetStatusDesc=function(status){switch(status){case GlobalServerStatuses.UNKNOWN:return"server status unknown";case GlobalServerStatuses.ONLINE:return"server online";case GlobalServerStatuses.MAINTENANCE:return"server offline";case GlobalServerStatuses.CHECKING:return"server status requested";}
return"wrong server status";}
var globalServerStatusChecker=null;function ServerStatusChecker()
{this.status=GlobalServerStatuses.CHECKING;this.prev_status=null;}
ServerStatusChecker.prototype.GetStatus=function(){if(this.prev_status&&this.status==GlobalServerStatuses.CHECKING)
return this.prev_status;else
return this.status;}
ServerStatusChecker.prototype.GetStatusDesc=function(){return GlobalServerStatuses.GetStatusDesc(this.status);}
ServerStatusChecker.prototype.StartCheck=function(interval){if(!interval)
interval=5*60*1000;var secInterval=interval/1000;app.logDebug("[ServerStatusChecker] start checking status every "+
secInterval.toString()+" seconds");var _this=this;_this.UpdateServerStatus(true);this.serverCheckTimer=setInterval(function(){_this.UpdateServerStatus(true);},interval);}
ServerStatusChecker.prototype.StopCheck=function(){app.logDebug("[ServerStatusChecker] stop checking status");clearInterval(this.serverCheckTimer);delete this.serverCheckTimer;}
ServerStatusChecker.prototype.OnCheckServerStatusResponse=function(result){this.status=GlobalServerStatuses.UNKNOWN;if(!this.prev_status)
this.prev_status=this.status;if(result.valid){try{var online=(result.data.search("srvOnline")>0)?1:0;if(online==1){this.status=GlobalServerStatuses.ONLINE;}
else{this.status=GlobalServerStatuses.MAINTENANCE;}}
catch(e){app.logWarning("[ServerStatusChecker] OnUpdateStatus Error: "+e.message);}}
app.logDebug("[ServerStatusChecker] OnUpdateStatus: "+
GlobalServerStatuses.GetStatusDesc(this.status));if(this.status==GlobalServerStatuses.MAINTENANCE)
isMaintenance=true;if(this.prev_status!=this.status){app.logDebug("[ServerStatusChecker] status changed from <"+
GlobalServerStatuses.GetStatusDesc(this.prev_status)+"> to <"+
this.GetStatusDesc()+">");onGlobalServerStatusChange(this.prev_status,this.status);}}
ServerStatusChecker.prototype.UpdateServerStatus=function(async){var url=app.getConfig("ServerStatusUrl","");if(url==""){app.logDebug("[ServerStatusChecker]:  no url for check");this.StopCheck();this.OnCheckServerStatusResponse({});return;}
if(this.prev_status&&this.status==GlobalServerStatuses.CHECKING){app.logDebug("[ServerStatusChecker] Still waiting for reply on previous check");return;}
if(this.status!=GlobalServerStatuses.CHECKING)
this.prev_status=this.status;if(async){this.status=GlobalServerStatuses.CHECKING;app.logDebug("[ServerStatusChecker] Request server status");var _this=this;httpRequest(url,{asyncRequest:true},function(res){_this.OnCheckServerStatusResponse(res);});}
else this.OnCheckServerStatusResponse(httpRequest(url));}