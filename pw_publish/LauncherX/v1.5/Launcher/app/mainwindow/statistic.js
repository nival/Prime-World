
var EventTypes={START:1,SHOW_AUTH:2,AUTH_SUCCESS:4,DOWNLOADING:8,PAUSED:16,RESUMED:32,READY_PLAY:64,START_PLAY:128,RETURN_FROM_GAME:256,FINALIZER:0};var statistic=null;function Statistic()
{this.reset();}
Statistic.prototype.reset=function()
{this.allEvents={statEvents:[],advEvents:[]};this.statEvents=this.allEvents.statEvents;this.advEvents=this.allEvents.advEvents;}
Statistic.prototype.load=function()
{var statFileName=app.expandString("{UserDataStorage}/{ApplicationName}.stat");var statData=loadFileContent(statFileName,{isObject:true});if(statData.valid)
{if(statData.data instanceof Array)
{this.allEvents.statEvents=statData.data;this.allEvents.advEvents=[];}
else if(statData.data instanceof Object)
{this.allEvents=statData.data;if(!(this.allEvents.advEvents instanceof Array))
this.allEvents.advEvents=[];if(!(this.allEvents.statEvents instanceof Array))
this.allEvents.statEvents=[];}
this.statEvents=this.allEvents.statEvents;this.advEvents=this.allEvents.advEvents;}
for(var i=0;i<this.advEvents.length;i++)
{var evn=this.advEvents[i];delete evn.inWait;}}
Statistic.prototype.save=function()
{var statFileName=app.expandString("{UserDataStorage}/{ApplicationName}.stat");saveFileContent(statFileName,this.allEvents);}
Statistic.prototype.sendEvents=function()
{if(!authServer)
return;while(this.statEvents.length>0)
{var statEvent=this.statEvents[0];var req="?action=l_events&locale="+langInfo.langCode;for(var name in statEvent)
req+="&"+name+"="+statEvent[name];req+="&hostid="+hostId+"&ver="+protocolVersion;var data=authServer.request(req);if(!data.valid)
break;this.statEvents.splice(0,1);this.save();}
this.sendAdvancedEvents();}
Statistic.prototype.checkEvent=function(eventMask)
{if(this.statEvents.length==0)
return 0;var curEvent=this.statEvents[this.statEvents.length-1];return curEvent.bitmask&eventMask;}
Statistic.prototype.pushEvent=function(eventType)
{if(!authMain)
return;if(this.statEvents.length==0)
this.statEvents[0]={bitmask:0};var curEvent=this.statEvents[this.statEvents.length-1];curEvent.bitmask|=eventType;var dt=new Date();curEvent.timestamp=parseInt(dt.valueOf()/1000);var auid=authMain.getAUID();if(auid)
curEvent.auid=auid;if(muid&&muid!="")
curEvent.muid=muid;this.save();}
Statistic.prototype.sendAdvanced=function(prms)
{if(!authMain)
return;prms.time=parseInt((new Date()).valueOf()/1000);prms.muid=muid;prms.auid=authMain.getAUID();prms.ver=protocolVersion;prms.version=skinVersion;prms.hostid=hostId;this.advEvents[this.advEvents.length]=prms;this.save();app.logMessage("STAT: sendAdvanced: "+prms.cmd);this.sendAdvancedEvents();}
Statistic.prototype.sendAdvancedEvents=function()
{if(this.advEvents.length>0)
{var evn=this.advEvents[0];if(evn.inWait)
return;var req="?action=l_stat&locale="+langInfo.langCode;for(var name in evn)
{var value=evn[name];if(value&&value!="")
req+="&"+name+"="+value;}
var _this=this;evn.inWait=true;app.logMessage("STAT: authServer.request: "+evn.cmd);authServer.request(req,{asyncRequest:true,force:true},function(data){_this.onAdvRequestFinished(evn,data);});}}
Statistic.prototype.onAdvRequestFinished=function(prms,data)
{delete prms.inWait;app.logMessage("STAT: onAdvRequestFinished: "+prms.cmd+", "+objectToString(data));if(data.valid)
{var response;try
{eval("response = "+data.data);}
catch(e)
{app.logWarning("Statistic can't parse server answer: "+data.data);}
if(response&&response.response)
{response=response.response;if(response.ok==1)
{for(var i=0;i<this.advEvents.length;i++)
{if(this.advEvents[i]==prms)
{this.advEvents.splice(i,1);this.save();break;}}}
else
{app.logWarning("Statistic got error from server (ec="+response.ec+"): "+response.error);}}
else
{app.logWarning("Statistic got wrong answer from server "+data.data);}
this.sendAdvancedEvents();}
else if(data.errorType=="NET_USER_ABORT")
{this.sendAdvancedEvents();}}