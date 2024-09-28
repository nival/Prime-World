
function debugPrint(value)
{var str="";for(var i=0;i<arguments.length;i++)
{if(i>0)
str+="\r\n";str+=valueToString(arguments[i],0);}
app.logDebug("debug print: "+str);app.showDialog({resizable:true,text:str,readonly:true,"width":800,"height":600});}
function debugPrintProps(value)
{var lines=[];if(typeof(value)=="object")
{for(var name in value)
{lines[lines.length]=name+" = "+value[name]+"\r\n";}}
else
{lines[lines.length]=value;}
lines.sort();var str="";for(var i=0;i<lines.length;i++)
{if(i>0)
str+="\r\n";str+=lines[i];}
app.logDebug("debug print collapsed: "+str);app.showDialog({resizable:true,text:str,readonly:true,"width":800,"height":600});}
function showCallStack()
{var callstack=[];var currentFunction=arguments.callee.caller;try
{var i=null;i.dont.exist+=1;}
catch(e)
{var lines=e.stack.split('\n');for(var i=1,len=lines.length;i<len;i++)
{callstack.push(lines[i]);}}
callstack.shift();debugPrint(callstack.join("\r\n"));}
function getCallerInfo()
{try
{var i=null;i.dont.exist+=1;}
catch(e)
{var lines=e.stack.split('\n');if(lines.length>3)
return lines[3];return lines[2]}
return"";}
function valueToString(value,indent)
{var indentStr="";var resultStr="";for(var i=0;i<indent;i++)
indentStr+="\t";var typeVar=typeof(value);if(typeVar=="object")
{if(value)
{resultStr="\r\n"+indentStr+"{\r\n";for(var name in value)
{var propStr=indentStr+"\t"+name+" = "+valueToString(value[name],indent+1);var typeNameVal=typeof(value[name]);if(typeNameVal!="object"&&typeNameVal!="array")
propStr+=",\r\n";resultStr+=propStr;}
resultStr+=indentStr+"},\r\n";}
else
{resultStr="null";}}
else if(typeVar=="array")
{if(value.length()>0)
{resultStr=indentStr+"[\r\n";for(var i=0;i<value.length;i++)
{var propStr=indentStr+"\t"+name+" = "+valueToString(value[i],indent+1)+",\r\n";resultStr+=propStr;}
resultStr+=indentStr+"],\r\n";}
else
{resultStr="[]";}}
else if(typeVar=="string")
{resultStr="\""+value+"\"";}
else
{if(value==undefined)
resultStr="undefined";else
resultStr=value.toString();}
return resultStr;}