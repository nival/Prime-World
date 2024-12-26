//Maya ASCII 2008 scene
//Name: _anim.ma
//Last modified: Mon, Nov 02, 2009 12:59:28 PM
//Codeset: 1251
requires maya "2008";
requires "Mayatomr" "9.0.1.4m - 3.6.51.0 ";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Complete 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200708022245-718075";
fileInfo "osv" "Microsoft Windows XP Service Pack 3 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 10 ".cel[0].cev";
	setAttr ".cd[0].cm" -type "characterMapping" 31 "SmallLamp_Locator04.rotateZ" 
		2 1 "SmallLamp_Locator04.rotateY" 2 2 "SmallLamp_Locator04.rotateX" 
		2 3 "SmallLamp_Locator04.translateZ" 1 1 "SmallLamp_Locator04.translateY" 
		1 2 "SmallLamp_Locator04.translateX" 1 3 "SmallLamp_Locator03.rotateZ" 
		2 4 "SmallLamp_Locator03.rotateY" 2 5 "SmallLamp_Locator03.rotateX" 
		2 6 "SmallLamp_Locator03.translateZ" 1 4 "SmallLamp_Locator03.translateY" 
		1 5 "SmallLamp_Locator03.translateX" 1 6 "SmallLamp_Locator02.rotateZ" 
		2 7 "SmallLamp_Locator02.rotateY" 2 8 "SmallLamp_Locator02.rotateX" 
		2 9 "SmallLamp_Locator02.translateZ" 1 7 "SmallLamp_Locator02.translateY" 
		1 8 "SmallLamp_Locator02.translateX" 1 9 "SmallLamp_Locator01.rotateZ" 
		2 10 "SmallLamp_Locator01.rotateY" 2 11 "SmallLamp_Locator01.rotateX" 
		2 12 "SmallLamp_Locator01.translateZ" 1 10 "SmallLamp_Locator01.translateY" 
		1 11 "SmallLamp_Locator01.translateX" 1 12 "HouseTop_Locator.rotateZ" 
		2 13 "HouseTop_Locator.rotateY" 2 14 "HouseTop_Locator.rotateX" 
		2 15 "HouseTop_Locator.translateZ" 1 13 "HouseTop_Locator.translateY" 
		1 14 "HouseTop_Locator.translateX" 1 15 "Circle.rotateZ" 2 
		16  ;
	setAttr ".cd[0].cim" -type "Int32Array" 31 0 1 2 3 4
		 5 6 7 8 9 10 11 12 13 14 15 16
		 17 18 19 20 21 22 23 24 25 26 27 28
		 29 30 ;
createNode animClip -n "clip1223Source1";
	setAttr ".ihi" 0;
	setAttr -s 10 ".ac";
	setAttr ".ac[3]" yes;
	setAttr ".ac[9]" yes;
	setAttr ".ac[15]" yes;
	setAttr ".ac[21]" yes;
	setAttr ".ac[25:30]" yes yes no no no yes;
	setAttr ".se" 450;
	setAttr ".ci" no;
createNode animCurveTL -n "animCurveTL8";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -0.45599644537641815 11.525 -0.054832715104193075 
		24 -0.78113432940595662 30 -0.45599644537641815;
	setAttr ".pst" 3;
createNode animCurveTL -n "animCurveTL9";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 8.195 0.20991465094851605 24 -0.27006191861135459 
		30 0;
	setAttr -s 4 ".kit[0:3]"  2 10 10 2;
	setAttr -s 4 ".kot[0:3]"  2 10 10 2;
	setAttr ".pst" 3;
createNode animCurveTL -n "animCurveTL10";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.042213615594264627 10.155 -0.13518999885025007 
		23 0.18588149771392162 30 0.042213615594264627;
	setAttr -s 4 ".kit[0:3]"  3 10 10 3;
	setAttr -s 4 ".kot[0:3]"  3 10 10 3;
	setAttr ".pst" 3;
createNode animCurveTL -n "animCurveTL11";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -0.10125000000000006 8.195 0.099165203019921294 
		21.715 -0.31390797025770489 30 -0.10125000000000006;
	setAttr ".pst" 3;
createNode animCurveTA -n "animCurveTA4";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.30500000000000027 15.185 0.009197277534066798 
		29.95 0.30500000000000027;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
	setAttr ".pst" 3;
createNode animCurveTA -n "animCurveTA5";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 15.185 0.21258943629682633 29.95 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTL -n "animCurveTL12";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -0.62415024390492879 7.85 -0.73253143405464571 
		20.1 -0.48269640446541129 29.95 -0.62415024390492879;
	setAttr -s 4 ".kit[0:3]"  10 3 3 10;
	setAttr -s 4 ".kot[0:3]"  10 3 3 10;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTL -n "animCurveTL13";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.053645556615384525 13.965 0.00052055661538458675 
		29.95 0.053645556615384525;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTL -n "animCurveTL14";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 13.715 0.043750000000000018 29.95 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTA -n "animCurveTA6";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 450 -360;
createNode lightLinker -n "lightLinker1";
	setAttr -s 4 ".lnk";
	setAttr -s 4 ".slnk";
select -ne :time1;
	setAttr -av -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 0;
select -ne :renderPartition;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 4 ".st";
	setAttr -k on ".an";
	setAttr -k on ".pt";
select -ne :renderGlobalsList1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
select -ne :defaultShaderList1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 4 ".s";
select -ne :postProcessList1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -s 2 ".u";
select -ne :lightList1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
select -ne :defaultTextureList1;
	setAttr -s 2 ".tx";
select -ne :initialShadingGroup;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -av -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -k on ".mwc";
	setAttr -k on ".an";
	setAttr -k on ".il";
	setAttr -k on ".vo";
	setAttr -k on ".eo";
	setAttr -k on ".fo";
	setAttr -k on ".epo";
	setAttr ".ro" yes;
	setAttr -cb on ".mimt";
	setAttr -cb on ".miop";
	setAttr -cb on ".mise";
	setAttr -cb on ".mism";
	setAttr -cb on ".mice";
	setAttr -av ".micc";
	setAttr -cb on ".mica";
	setAttr -cb on ".micw";
	setAttr -cb on ".mirw";
select -ne :initialParticleSE;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -k on ".mwc";
	setAttr -k on ".an";
	setAttr -k on ".il";
	setAttr -k on ".vo";
	setAttr -k on ".eo";
	setAttr -k on ".fo";
	setAttr -k on ".epo";
	setAttr ".ro" yes;
	setAttr -cb on ".mimt";
	setAttr -cb on ".miop";
	setAttr -cb on ".mise";
	setAttr -cb on ".mism";
	setAttr -cb on ".mice";
	setAttr -cb on ".micc";
	setAttr -cb on ".mica";
	setAttr -cb on ".micw";
	setAttr -cb on ".mirw";
select -ne :defaultRenderGlobals;
	setAttr ".mcfr" 30;
	setAttr ".ren" -type "string" "mentalRay";
select -ne :defaultLightSet;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -k on ".mwc";
	setAttr ".ro" yes;
select -ne :hardwareRenderGlobals;
	setAttr -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".ctrs" 256;
	setAttr ".btrs" 512;
	setAttr -k off -cb on ".ehql";
	setAttr -k off -cb on ".eams";
	setAttr -k off ".eeaa";
	setAttr -k off ".engm";
	setAttr -k off ".mes";
	setAttr -k off ".emb";
	setAttr -k off ".mbbf";
	setAttr -k off ".mbs";
	setAttr -k off ".trm";
	setAttr -k off -cb on ".tshc";
	setAttr -k off ".clmt";
	setAttr -k off -cb on ".tcov";
	setAttr -k off -cb on ".lith";
	setAttr -k off -cb on ".sobc";
	setAttr -k off -cb on ".cuth";
	setAttr -k off -cb on ".mgcs";
	setAttr -k off ".twa";
	setAttr -k off ".twz";
	setAttr -k on ".hwcc";
	setAttr -k on ".hwdp";
	setAttr -k on ".hwql";
	setAttr ".hwfr" 30;
select -ne :characterPartition;
select -ne :defaultHardwareRenderGlobals;
	setAttr -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -k on ".rp";
	setAttr -k on ".cai";
	setAttr -k on ".coi";
	setAttr -cb on ".bc";
	setAttr -av -k on ".bcb";
	setAttr -av -k on ".bcg";
	setAttr -av -k on ".bcr";
	setAttr -k on ".ei";
	setAttr -k on ".ex";
	setAttr -k on ".es";
	setAttr -av -k on ".ef";
	setAttr -k on ".bf";
	setAttr -k on ".fii";
	setAttr -k on ".sf";
	setAttr -k on ".gr";
	setAttr -k on ".li";
	setAttr -k on ".ls";
	setAttr -k on ".mb";
	setAttr -k on ".ti";
	setAttr -k on ".txt";
	setAttr -k on ".mpr";
	setAttr -k on ".wzd";
	setAttr ".fn" -type "string" "im";
	setAttr -k on ".if";
	setAttr ".res" -type "string" "ntsc_4d 646 485 1.333";
	setAttr -k on ".as";
	setAttr -k on ".ds";
	setAttr -k on ".lm";
	setAttr -k on ".fir";
	setAttr -k on ".aap";
	setAttr -k on ".gh";
	setAttr -cb on ".sd";
connectAttr "clip1223Source1.cl" "clipLibrary1.sc[0]";
connectAttr "animCurveTL8.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "animCurveTL9.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "animCurveTL10.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "animCurveTL11.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "animCurveTA4.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "animCurveTA5.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "animCurveTL12.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "animCurveTL13.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "animCurveTL14.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "animCurveTA6.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of _anim.ma
