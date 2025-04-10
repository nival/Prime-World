#!/bin/bash
#script to invoke the following web services.The outputs must be 0 for all below commands
type wsdl
wsdl RandomBushism.wsdl getRandomBushism  >/dev/null; echo $?
wsdl CountCheatService.wsdl LetterSolutions hleol >/dev/null; echo $?
wsdl CountCheatService.wsdl LetterSolutionsMin hleol 5  >/dev/null; echo $?
wsdl DictService.wsdl DefineInDict wn epiphany >/dev/null; echo $?
wsdl DictService.wsdl Define  epiphany >/dev/null; echo $?
wsdl DictService.wsdl DictionaryList >/dev/null; echo $?
#wsdl  GoogleSearch.wsdl doGoogleSearch  "*****license-key****" wsdlpull 1 5 0 1 1 1 1 1 >/dev/null;echo $?
