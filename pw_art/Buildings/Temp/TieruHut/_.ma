//Maya ASCII 2008 scene
//Name: _.ma
//Last modified: Tue, Oct 28, 2008 03:19:41 PM
//Codeset: 1251
requires maya "2008";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Complete 2008";
fileInfo "version" "2008";
fileInfo "cutIdentifier" "200708022245-704165";
fileInfo "osv" "Microsoft Windows XP Service Pack 2 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 6 ".cel[0].cev";
	setAttr ".cd[0].cm" -type "characterMapping" 36 "L3.scaleZ" 0 1 "L3.scaleY" 
		0 2 "L3.scaleX" 0 3 "L3.rotateZ" 2 1 "L3.rotateY" 2 
		2 "L3.rotateX" 2 3 "L3.translateZ" 1 1 "L3.translateY" 1 
		2 "L3.translateX" 1 3 "L2.scaleZ" 0 4 "L2.scaleY" 0 
		5 "L2.scaleX" 0 6 "L2.rotateZ" 2 4 "L2.rotateY" 2 5 "L2.rotateX" 
		2 6 "L2.translateZ" 1 4 "L2.translateY" 1 5 "L2.translateX" 
		1 6 "L1.scaleZ" 0 7 "L1.scaleY" 0 8 "L1.scaleX" 0 
		9 "L1.rotateZ" 2 7 "L1.rotateY" 2 8 "L1.rotateX" 2 
		9 "L1.translateZ" 1 7 "L1.translateY" 1 8 "L1.translateX" 
		1 9 "root.scaleZ" 0 10 "root.scaleY" 0 11 "root.scaleX" 
		0 12 "root.rotateZ" 2 10 "root.rotateY" 2 11 "root.rotateX" 
		2 12 "root.translateZ" 1 10 "root.translateY" 1 11 "root.translateX" 
		1 12  ;
	setAttr ".cd[0].cim" -type "Int32Array" 36 0 1 2 3 4
		 5 6 7 8 9 10 11 12 13 14 15 16
		 17 18 19 20 21 22 23 24 25 26 27 28
		 29 30 31 32 33 34 35 ;
createNode animClip -n "clip00Source";
	setAttr ".ihi" 0;
	setAttr -s 6 ".ac";
	setAttr ".ac[7:8]" yes yes;
	setAttr ".ac[16:17]" yes yes;
	setAttr ".ac[25:26]" yes yes;
	setAttr ".se" 60;
	setAttr ".ci" no;
createNode animCurveTL -n "L3_translateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -0.77339791486074705 18 -0.66343856094359988 
		40 -0.88367008005194048 60 -0.77339791486074705;
	setAttr -s 4 ".kit[1:3]"  3 10 3;
	setAttr -s 4 ".kot[1:3]"  3 10 3;
createNode animCurveTL -n "L3_translateX1";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -7.376527076583641 18 -7.6 40 -7.6 60 
		-7.376527076583641;
	setAttr -s 4 ".kit[0:3]"  10 3 3 10;
	setAttr -s 4 ".kot[0:3]"  10 3 3 10;
createNode animCurveTL -n "L2_translateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -5.5041621877373483 30 -5.4495978568601409 
		60 -5.5041621877373483;
createNode animCurveTL -n "L2_translateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -1.818481255311478 30 -1.2784741355539981 
		60 -1.818481255311478;
createNode animCurveTL -n "L1_translateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.19806835146556218 18 0.38202648154014524 
		40 -0.097777740240352462 60 0.19806835146556218;
createNode animCurveTL -n "L1_translateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 2.2501904315501724 18 2.2153463648096805 
		40 2.4654699163681695 60 2.2501904315501724;
createNode lightLinker -n "lightLinker1";
	setAttr -s 8 ".lnk";
	setAttr -s 8 ".slnk";
select -ne :time1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -l on ".o" 0;
select -ne :renderPartition;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -s 8 ".st";
select -ne :renderGlobalsList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
select -ne :defaultShaderList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -s 8 ".s";
select -ne :postProcessList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
	setAttr -s 4 ".u";
select -ne :lightList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
select -ne :defaultTextureList1;
	setAttr -s 4 ".tx";
select -ne :lambert1;
	setAttr ".miic" -type "float3" 3.1415927 3.1415927 3.1415927 ;
select -ne :initialShadingGroup;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -k on ".mwc";
	setAttr ".ro" yes;
select -ne :initialParticleSE;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -k on ".mwc";
	setAttr ".ro" yes;
select -ne :defaultRenderGlobals;
	setAttr -k on ".esr";
	setAttr ".fs" 1;
	setAttr ".ef" 10;
	setAttr -l on ".bfs";
	setAttr -l on ".mb";
	setAttr -k on ".mbf";
	setAttr -l on ".afp";
	setAttr -k on ".frts";
select -ne :defaultLightSet;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -k on ".mwc";
	setAttr ".ro" yes;
select -ne :hardwareRenderGlobals;
	addAttr -ci true -sn "ani" -ln "animation" -bt "ANIM" -min 0 -max 1 -at "bool";
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr ".ctrs" 256;
	setAttr ".btrs" 512;
	setAttr ".enpt" no;
	setAttr ".hgcd" no;
	setAttr ".hgci" no;
	setAttr -k on ".ani";
select -ne :characterPartition;
select -ne :defaultHardwareRenderGlobals;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr ".fn" -type "string" "im";
	setAttr ".res" -type "string" "ntsc_4d 646 485 1.333";
select -ne :ikSystem;
	setAttr -s 4 ".sol";
connectAttr "clip00Source.cl" "clipLibrary1.sc[0]";
connectAttr "L3_translateY1.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "L3_translateX1.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "L2_translateY1.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "L2_translateX1.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "L1_translateY1.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "L1_translateX1.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[7].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[7].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[7].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[7].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[8].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[8].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of _.ma
