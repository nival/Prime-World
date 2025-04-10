// Скрипт позволяет преобразовывать xml файлы при помощи XSLT
// Используя при этом MSXML
// Основная часть была взята из примера msdn. Немного модифицирована мной
var oArgs = WScript.Arguments;

if (oArgs.length != 3)
{
   WScript.Echo ("Usage : cscript xslt.js xml xsl output");
   WScript.Quit();
}
xmlFile = oArgs(0);
xslFile = oArgs(1);
outFile = oArgs(2);

var xsl = new ActiveXObject("MSXML2.DOMDocument");
var xml = new ActiveXObject("MSXML2.DOMDocument");
xml.validateOnParse = false;
xml.async = false;
xml.load(xmlFile);

if (xml.parseError.errorCode != 0)
   WScript.Echo ("XML Parse Error : " + xml.parseError.reason);

xsl.async = false;
xsl.load(xslFile);

if (xsl.parseError.errorCode != 0)
   WScript.Echo ("XSL Parse Error : " + xsl.parseError.reason);

//WScript.Echo (xml.transformNode(xsl.documentElement));

try
{
	var fso, tf;
	fso = new ActiveXObject("Scripting.FileSystemObject");
	tf = fso.CreateTextFile(outFile, true);
	tf.Write (xml.transformNode(xsl.documentElement));
	tf.Close();
}
catch(err)
{
   WScript.Echo ("Transformation Error : " + err.number + "*" + err.description);
}

