
var requestId=0;function sslRequest(url,prms,onFinished){if(!prms||typeof(prms)!="object")
prms={};prms.useSsl=true;if(prms.getParams)
url+="?"+prms.getParams;return httpRequest(url,prms,onFinished);}
function tlsRequest(url,prms,onFinished){if(!prms||typeof(prms)!="object")
prms={};prms.useSsl=true;prms.useTLS=true;if(prms.getParams)
url+="?"+prms.getParams;return httpRequest(url,prms,onFinished);}
var HttpHeaders={ContentTypeHeader:0,ContentLengthHeader:1,LocationHeader:2,LastModifiedHeader:3,CookieHeader:4,SetCookieHeader:5,Authorization:-96};var ResultPresentation={String:0,Base64:1};function httpRequest(url,prms,onFinished){if(!prms||typeof(prms)!="object")
prms={};prms.reqId=requestId++;if(inClosingState){var data={error:true};if(prms.asyncRequest&&onFinished)
onFinished(data);return data;}
var method=prms.method;if(!method||method=="")
method="GET";app.logDebug("httpRequest url: "+url);app.logDebug("httpRequest prms: "+JSON.stringify(prms));var request=app.createNetworkRequest(url,method);if(prms.headers){app.logDebug("Headers: "+JSON.stringify(prms.headers));for(var h in prms.headers){request.setHeader(HttpHeaders[h],prms.headers[h]);}}
if(prms.returnAs)
request.setResultPresentation(prms.returnAs);if(prms.useSsl)
request.setUseSsl(true);if(prms.useTLS)
request.setUseTLS(true);request.receiveBodyOnError();if(prms.asyncRequest){request.setAsync(true);request.finished.connect(function(data){if(onFinished)
onFinished(data);request.deleteLater();});request.send(prms.data);}
else{request.setAsync(false);var text=prms.waitText;if(!text)
text=getLocalizedString("httpWaitText","innerHTML");showWaiter(text);var result=request.send(prms.data);app.logDebug("request result: "+JSON.stringify(result));request.deleteLater();hideWaiter();return result;}}
function loadFileContent(fileName,prms){if(!prms||typeof(prms)!="object")
prms={};var data=app.loadFileContent(fileName,prms);if(data.valid&&prms&&prms.isObject){try{eval("data.data = "+data.data);}
catch(e){app.logWarning("Can't parse as object: "+data.data);}}
return data;}
function saveFileContent(fileName,data,prms){if(!prms||typeof(prms)!="object")
prms={};if(typeof(data)=="object")
data=JSON.stringify(data);return app.saveFileContent(fileName,data,prms);}
function mergeObjectProperties(object,newProps){for(var name in newProps)
object[name]=newProps[name];return object;}
function openExternalBrowser(url){app.openExternalBrowser(url);}
function sleep(msec){var now=new Date();var exitTime=now.valueOf()+msec;while(true){now=new Date();if(now.valueOf()>exitTime)
return;}}
function getTime(){return(new Date()).valueOf();}
function objectToString(obj){return JSON.stringify(obj);}
function deriveClass(child,parent,className){var F=function(){};F.prototype=parent.prototype;child.prototype=new F();child.prototype.constructor=child;child.prototype.__className=className;child.__base=parent.prototype;}
function expandURI(uri,values){var regexp=/\&amp;/g;uri=uri.replace(regexp,"&");var valuesObj=values;if(!valuesObj)
valuesObj={};var searchExp=/{[^}]*/;while(true){var part=searchExp.exec(uri);if(part==null||part=="")
break;part=part[0];regexp=new RegExp("\\"+part+"\\}");part=part.substring(1);var value="";if(valuesObj[part])
value=valuesObj[part];else
value=app.getConfig(part,"")
uri=uri.replace(regexp,value);}
return uri;}
function joinRequestParameters(prms){var result="";for(var name in prms)
result+="&"+name+"="+prms[name];return result.substring(1);}
function text2xml(strXML){var xmlDoc=null;try{xmlDoc=(document.all)?new ActiveXObject("Microsoft.XMLDOM"):new DOMParser();xmlDoc.async=false;}catch(e){throw new Error("XML Parser could not be instantiated");}
var out;try{if(document.all){out=(xmlDoc.loadXML(strXML))?xmlDoc:false;}else{out=xmlDoc.parseFromString(strXML,"text/xml");}}catch(e){throw new Error("Error parsing XML string");}
return out;}
xml2json=function(xml){var obj={};if(xml.nodeType==1){if(xml.attributes.length>0){obj['@attributes']={};for(var j=0;j<xml.attributes.length;j++){obj['@attributes'][xml.attributes[j].nodeName]=xml.attributes[j].nodeValue;}}}else if(xml.nodeType==3){obj=xml.nodeValue;}
if(xml.hasChildNodes()){for(var i=0;i<xml.childNodes.length;i++){if(typeof(obj[xml.childNodes[i].nodeName])=='undefined'){obj[xml.childNodes[i].nodeName]=xml2json(xml.childNodes[i]);}else{if(typeof(obj[xml.childNodes[i].nodeName].length)=='undefined'){var old=obj[xml.childNodes[i].nodeName];obj[xml.childNodes[i].nodeName]=[];obj[xml.childNodes[i].nodeName].push(old);}
obj[xml.childNodes[i].nodeName].push(xml2json(xml.childNodes[i]));}}}
return obj;}
function xml_str2json(xml_str)
{return xml2json(text2xml(xml_str));}
var parseXml;if(typeof window.DOMParser!="undefined"){parseXml=function(xmlStr){return(new window.DOMParser()).parseFromString(xmlStr,"text/xml");};}else if(typeof window.ActiveXObject!="undefined"&&new window.ActiveXObject("Microsoft.XMLDOM")){parseXml=function(xmlStr){var xmlDoc=new window.ActiveXObject("Microsoft.XMLDOM");xmlDoc.async="false";xmlDoc.loadXML(xmlStr);return xmlDoc;};}else{throw new Error("No XML parser found");}
Array.prototype.union=function(other,comparator){if('function'!=typeof comparator){comparator=function(value1,value2)
{return value1!=value2;}}
var result=this.concat();var currentLength=result.length;var j;for(var i=0;i<other.length;i++){j=0;result[currentLength]=other[i];while(comparator(result[j],other[i])){j++;}
if(j==currentLength){currentLength++;}}
if(result.length!=currentLength){result.length--;}
return result;}