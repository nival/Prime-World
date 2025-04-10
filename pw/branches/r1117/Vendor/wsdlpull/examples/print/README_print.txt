An example which illustrates the usage of WSDL API.  It just prints a few 'intersting' wsdl elements found. 
On Linux/Unix platforms print is found in the    $(prefi)/bin (installation directory)
To run type 'print <wsdl_file_name> ' .  

***************************
Win32 specific
On Win32 platforms select the 'print' project from the workspace and build. print.exe is generated in the wsdlpull root directory
To run type 'print.exe <wsdl_file_name> ' 
Again since the soap.xsd is required for parsing wsdl documents with soap binding elements (which means all wsdl documents!!) you need to adjust the relative path in wsdlparser/SoapExt.cpp .Search for soap.xsd and change the win32 specific code.
***************************
