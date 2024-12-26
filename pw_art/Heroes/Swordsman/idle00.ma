//Maya ASCII 5.0 scene
//Name: Footman.idle00.ma
//Last modified: Fri, Apr 09, 2004 06:37:20 PM
requires maya "5.0";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Unlimited 5.0";
fileInfo "version" "5.0";
fileInfo "cutIdentifier" "200304010010";
fileInfo "osv" "Microsoft Windows 2000 Professional Service Pack 4 (Build 2195)\n";
createNode animClip -n "idle00Source";
	setAttr ".ihi" 0;
	setAttr ".st" 5;
	setAttr ".du" 74;
	setAttr ".ci" no;
createNode animCurveTA -n "Char_Chest_locator_rotateZ";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 5.0767330165697206 5 1.3279995858904801 
		40 1.3279995858904778 80 1.3279995858904801;
createNode animCurveTA -n "Char_Chest_locator_rotateY";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 -9.9615580980903751 5 -18.025691155969195 
		40 -20.145954973733389 80 -18.025691155969195;
createNode animCurveTA -n "Char_Chest_locator_rotateX";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 -0.88044701579796236 5 9.0484514413106716 
		40 15.855571892737114 80 9.0484514413106716;
	setAttr -s 5 ".kit[2:4]"  1 10 10;
	setAttr -s 5 ".kot[2:4]"  1 10 10;
	setAttr -s 5 ".kix[2:4]"  0.064797878265380859 1.1666667461395264 
		1.3333333730697632;
	setAttr -s 5 ".kiy[2:4]"  -0.0032695140689611435 0 -0.11880666762590408;
	setAttr -s 5 ".kox[2:4]"  1.1314543485641479 1.3333332538604736 
		1.3333333730697632;
	setAttr -s 5 ".koy[2:4]"  -0.057089917361736298 0 -0.11880666762590408;
createNode animCurveTA -n "Char_Shield_locator_World_rotateZ";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 0 80 0;
createNode animCurveTA -n "Char_Shield_locator_World_rotateY";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 0 80 0;
createNode animCurveTA -n "Char_Shield_locator_World_rotateX";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 0 80 0;
createNode animCurveTL -n "Char_Shield_locator_World_translateZ";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 0 80 0;
createNode animCurveTL -n "Char_Shield_locator_World_translateY";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 0 80 0;
createNode animCurveTL -n "Char_Shield_locator_World_translateX";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 0 80 0;
createNode animCurveTA -n "Char_Sword_locator_World_rotateZ";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 0 80 0;
createNode animCurveTA -n "Char_Sword_locator_World_rotateY";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 0 80 0;
createNode animCurveTA -n "Char_Sword_locator_World_rotateX";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 0 80 0;
createNode animCurveTL -n "Char_Sword_locator_World_translateZ";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 0 80 0;
createNode animCurveTL -n "Char_Sword_locator_World_translateY";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 0 80 0;
createNode animCurveTL -n "Char_Sword_locator_World_translateX";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 0 80 0;
createNode animCurveTL -n "Char_L_Locot_locator_translateZ";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 0 5 0.24819552039891896 40 
		0.20613901760230141 80 0.24819552039891896;
	setAttr -s 5 ".kit[3:4]"  9 10;
	setAttr -s 5 ".kot[3:4]"  9 10;
createNode animCurveTL -n "Char_L_Locot_locator_translateY";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 0 5 -0.27469944966509141 
		40 -0.27777862849816959 80 -0.27469944966509141;
	setAttr -s 5 ".kit[3:4]"  9 10;
	setAttr -s 5 ".kot[3:4]"  9 10;
createNode animCurveTL -n "Char_L_Locot_locator_translateX";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 0 5 0.26769795222050691 40 
		0.23072032604471765 80 0.26769795222050691;
	setAttr -s 5 ".kit[3:4]"  9 10;
	setAttr -s 5 ".kot[3:4]"  9 10;
createNode animCurveTL -n "Char_R_Locot_locator_translateZ";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 0 5 -0.2613544330215532 40 
		-0.30341093581817075 80 -0.2613544330215532;
createNode animCurveTL -n "Char_R_Locot_locator_translateY";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 -0.19226194684043407 5 -0.24709570664594427 
		40 -0.25017488547902245 80 -0.24709570664594427;
createNode animCurveTL -n "Char_R_Locot_locator_translateX";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 -0.035915365782317243 5 0.23566418246003235 
		40 0.19868655628424309 80 0.23566418246003235;
createNode animCurveTL -n "Char_HeadTop_locator_translateZ";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 5 -0.0070963888536680897 
		20 -0.028082490497991552 40 -0.049152891650285635 60 -0.028082490497991552 
		80 -0.0070963888536680897;
	setAttr -s 7 ".kit[3:6]"  9 9 9 10;
	setAttr -s 7 ".kot[3:6]"  9 9 9 10;
createNode animCurveTL -n "Char_HeadTop_locator_translateY";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 5 -0.0034360675845639399 
		20 0.0098786113595392688 40 -0.0065152464176421176 60 0.0098786113595392688 
		80 -0.0034360675845639399;
	setAttr -s 7 ".kit[3:6]"  9 9 9 10;
	setAttr -s 7 ".kot[3:6]"  9 9 9 10;
createNode animCurveTL -n "Char_HeadTop_locator_translateX";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 -0.04906451228834087 5 0.028873232947846241 
		20 0.015875690471994188 40 -0.0081043932279430166 60 0.0054146326526420506 
		80 0.028873232947846241;
	setAttr -s 7 ".kit[3:6]"  9 9 9 10;
	setAttr -s 7 ".kot[3:6]"  9 9 9 10;
createNode animCurveTL -n "Char_Head_locator_translateZ";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 5 -0.0070963888536680897 
		20 -0.028082490497991552 40 -0.049152891650285635 60 -0.028082490497991552 
		80 -0.0070963888536680897;
	setAttr -s 7 ".kit[3:6]"  9 9 9 10;
	setAttr -s 7 ".kot[3:6]"  9 9 9 10;
createNode animCurveTL -n "Char_Head_locator_translateY";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0.031805653569169534 5 -0.045463711799524242 
		20 -0.032149032855421034 40 -0.04854289063260242 60 -0.032149032855421034 
		80 -0.045463711799524242;
createNode animCurveTL -n "Char_Head_locator_translateX";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 -0.030485593883446821 5 0.027087692813105652 
		20 0.014090150337253603 40 -0.0098899333626836124 60 0.0036290925179014652 
		80 0.027087692813105652;
	setAttr -s 7 ".kit[3:6]"  9 9 9 10;
	setAttr -s 7 ".kot[3:6]"  9 9 9 10;
createNode animCurveTA -n "Char_Clothe_locator_rotateZ";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 5 0 20 0 40 0 60 0 80 0;
createNode animCurveTA -n "Char_Clothe_locator_rotateY";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 5 0 20 0 40 0 60 0 80 0;
createNode animCurveTA -n "Char_Clothe_locator_rotateX";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 5 13.657893158781347 20 
		13.657893158781347 40 13.657893158781347 60 13.657893158781347 80 13.657893158781347;
createNode animCurveTL -n "Char_Clothe_locator_translateZ";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 5 -0.0070963888536680897 
		20 -0.028082490497991552 40 -0.049152891650285635 60 -0.028082490497991552 
		80 -0.0070963888536680897;
createNode animCurveTL -n "Char_Clothe_locator_translateY";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 5 -0.0034360675845639399 
		20 0.0098786113595392688 40 -0.0065152464176421176 60 0.0098786113595392688 
		80 -0.0034360675845639399;
createNode animCurveTL -n "Char_Clothe_locator_translateX";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 5 0.049818208219252202 
		20 0.036820665743400149 40 0.012840582043462945 60 0.026359607924048012 80 
		0.049818208219252202;
createNode animCurveTU -n "Char_L_Hand_locator_Shield";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 1 2 1 5 1 40 1 80 1;
	setAttr -s 5 ".kit[4]"  10;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 10;
createNode animCurveTA -n "Char_L_Hand_locator_rotateZ";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 -76.771215661777489 5 -140.09137328137615 
		40 -138.30378020034746 80 -140.09137328137615;
createNode animCurveTA -n "Char_L_Hand_locator_rotateY";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 -34.936684051068497 5 -41.32214986621824 
		40 -42.77778893149415 80 -41.32214986621824;
createNode animCurveTA -n "Char_L_Hand_locator_rotateX";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 -5.7225404439904688 5 48.2339608204746 
		40 47.036519303467784 80 48.2339608204746;
createNode animCurveTL -n "Char_L_Hand_locator_translateZ";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 0.10921817915811 5 0.22829510939120629 
		40 0.22829510939120629 80 0.22829510939120629;
	setAttr -s 5 ".kit[2:4]"  3 10 10;
	setAttr -s 5 ".kot[2:4]"  3 10 10;
createNode animCurveTL -n "Char_L_Hand_locator_translateY";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 -0.44494523011614384 5 -0.3818372728130861 
		40 -0.35272939787498453 80 -0.38183183600645232;
	setAttr -s 5 ".kit[2:4]"  3 10 3;
	setAttr -s 5 ".kot[2:4]"  3 10 3;
createNode animCurveTL -n "Char_L_Hand_locator_translateX";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 -0.34355628339150263 5 -0.26678912622464734 
		40 -0.29974750397367012 80 -0.26678912622464734;
	setAttr -s 5 ".kit[2:4]"  3 10 10;
	setAttr -s 5 ".kot[2:4]"  3 10 10;
createNode animCurveTU -n "Char_R_Hand_locator_Sword";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 1 2 1 5 1 40 1 80 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTA -n "Char_R_Hand_locator_rotateZ";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 59.2986616091207 5 20.310788668107964 
		40 23.530357151659729 80 20.310788668107964;
	setAttr -s 5 ".kit[2:4]"  3 1 3;
	setAttr -s 5 ".kot[2:4]"  3 1 3;
	setAttr -s 5 ".kix[3:4]"  1.0852841138839722 1.3333333730697632;
	setAttr -s 5 ".kiy[3:4]"  0.03602319210767746 0;
	setAttr -s 5 ".kox[3:4]"  1.2519470453262329 1.3333333730697632;
	setAttr -s 5 ".koy[3:4]"  0.041555136442184448 0;
createNode animCurveTA -n "Char_R_Hand_locator_rotateY";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 -22.276923710305624 5 66.512956204860245 
		40 57.263941260645232 80 66.512956204860245;
	setAttr -s 5 ".kit[2:4]"  3 1 3;
	setAttr -s 5 ".kot[2:4]"  3 1 3;
	setAttr -s 5 ".kix[3:4]"  1.1136965751647949 1.3333333730697632;
	setAttr -s 5 ".kiy[3:4]"  -0.084232360124588013 0;
	setAttr -s 5 ".kox[3:4]"  1.2803608179092407 1.3333333730697632;
	setAttr -s 5 ".koy[3:4]"  -0.096837744116783142 0;
createNode animCurveTA -n "Char_R_Hand_locator_rotateX";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 39.667190379474654 5 -75.483590873900127 
		40 -72.336076345774558 80 -75.483590873900127;
	setAttr -s 5 ".kit[2:4]"  3 1 3;
	setAttr -s 5 ".kot[2:4]"  3 1 3;
	setAttr -s 5 ".kix[3:4]"  1.062914252281189 1.3333333730697632;
	setAttr -s 5 ".kiy[3:4]"  0.039480526000261307 0;
	setAttr -s 5 ".kox[3:4]"  1.2295764684677124 1.3333333730697632;
	setAttr -s 5 ".koy[3:4]"  0.04567096009850502 0;
createNode animCurveTL -n "Char_R_Hand_locator_translateZ";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 0.091237381762139774 5 -0.23002750690950557 
		40 -0.20113216339509593 80 -0.23002750690950557;
	setAttr -s 5 ".kit[3:4]"  1 10;
	setAttr -s 5 ".kot[3:4]"  1 10;
	setAttr -s 5 ".kix[3:4]"  1.1233570575714111 1.3333333730697632;
	setAttr -s 5 ".kiy[3:4]"  0.014671096578240395 0;
	setAttr -s 5 ".kox[3:4]"  1.2838362455368042 1.3333333730697632;
	setAttr -s 5 ".koy[3:4]"  0.016766967251896858 0;
createNode animCurveTL -n "Char_R_Hand_locator_translateY";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 -0.47474391147545703 5 -0.10618930795413672 
		40 -0.16795034629564731 80 -0.10618930795413672;
	setAttr -s 5 ".kit[2:4]"  3 1 3;
	setAttr -s 5 ".kot[2:4]"  3 1 3;
	setAttr -s 5 ".kix[3:4]"  1.1025160551071167 1.3333333730697632;
	setAttr -s 5 ".kiy[3:4]"  -0.037990327924489975 0;
	setAttr -s 5 ".kox[3:4]"  1.2600173950195313 1.3333333730697632;
	setAttr -s 5 ".koy[3:4]"  -0.04341747984290123 0;
createNode animCurveTL -n "Char_R_Hand_locator_translateX";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 0.23715921315747951 5 0.16650073509114327 
		40 0.12851966928417263 80 0.16650073509114327;
	setAttr -s 5 ".kit[3:4]"  1 10;
	setAttr -s 5 ".kot[3:4]"  1 10;
	setAttr -s 5 ".kix[3:4]"  1.1097731590270996 1.3333333730697632;
	setAttr -s 5 ".kiy[3:4]"  -0.022036723792552948 0;
	setAttr -s 5 ".kox[3:4]"  1.2683122158050537 1.3333333730697632;
	setAttr -s 5 ".koy[3:4]"  -0.025184821337461472 0;
createNode animCurveTL -n "Char_R_Knee_locator_translateZ";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 0 5 -0.15728441520586695 
		40 -0.19934091800248449 80 -0.15728441520586695;
	setAttr -s 5 ".kit[3:4]"  9 10;
	setAttr -s 5 ".kot[3:4]"  9 10;
createNode animCurveTL -n "Char_R_Knee_locator_translateY";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 0 5 0.063144408114785111 
		40 0.060065229281706933 80 0.063144408114785111;
createNode animCurveTL -n "Char_R_Knee_locator_translateX";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 -0.055558024602225475 5 -0.50898231702401886 
		40 -0.54595994319980812 80 -0.50898231702401886;
	setAttr -s 5 ".kit[3:4]"  9 10;
	setAttr -s 5 ".kot[3:4]"  9 10;
createNode animCurveTL -n "Char_L_Knee_locator_translateZ";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 0 5 0.00069708472453872128 
		40 -0.041359418072078824 80 0.00069708472453872128;
	setAttr -s 5 ".kit[2:4]"  3 10 10;
	setAttr -s 5 ".kot[2:4]"  3 10 10;
createNode animCurveTL -n "Char_L_Knee_locator_translateY";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 0 5 0.027296557722927772 
		40 0.024217378889849595 80 0.027296557722927772;
createNode animCurveTL -n "Char_L_Knee_locator_translateX";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 0.091522324308572212 5 0.30320886908454558 
		40 0.26623124290875633 80 0.30320886908454558;
createNode animCurveTU -n "Char_R_Leg_locator_Toe";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 0 80 0;
createNode animCurveTA -n "Char_R_Leg_locator_rotateZ";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 2.4545668869252451 80 
		2.4545668869252451;
createNode animCurveTA -n "Char_R_Leg_locator_rotateY";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 -10.000000000000002 5 -59.222044573256952 
		80 -59.222044573256952;
createNode animCurveTA -n "Char_R_Leg_locator_rotateX";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 -2.434202033955327 80 
		-2.434202033955327;
createNode animCurveTL -n "Char_R_Leg_locator_translateZ";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 -0.3296746241193716 80 
		-0.3296746241193716;
createNode animCurveTL -n "Char_R_Leg_locator_translateY";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 0 80 0;
createNode animCurveTL -n "Char_R_Leg_locator_translateX";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 -0.045436156506848263 
		80 -0.045436156506848263;
createNode animCurveTU -n "Char_L_Leg_locator_Toe";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 0 80 0;
createNode animCurveTA -n "Char_L_Leg_locator_rotateZ";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 0 80 0;
createNode animCurveTA -n "Char_L_Leg_locator_rotateY";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 10.000000000000004 5 15.642077920431827 
		80 15.642077920431827;
createNode animCurveTA -n "Char_L_Leg_locator_rotateX";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 0 80 0;
createNode animCurveTL -n "Char_L_Leg_locator_translateZ";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0.093590416298333118 5 0.093590416298333118 
		80 0.093590416298333118;
createNode animCurveTL -n "Char_L_Leg_locator_translateY";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 0 80 0;
createNode animCurveTL -n "Char_L_Leg_locator_translateX";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0.11655511999435637 5 0.22004454697835768 
		80 0.22004454697835768;
createNode animCurveTA -n "Char_Hip_locator_rotateZ";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 -5 5 0.91153173449061375 
		20 0.91153173449060998 40 0.91153173449060998 60 0.91153173449060998 80 0.91153173449061375;
createNode animCurveTA -n "Char_Hip_locator_rotateY";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 5 -15.302297995125491 20 
		-15.302297995125516 40 -15.302297995125516 60 -15.302297995125516 80 -15.302297995125491;
createNode animCurveTA -n "Char_Hip_locator_rotateX";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 5 0.10953910533628933 20 
		0.051103812633386064 40 0.030389132625500238 60 0.051103812633386064 80 0.10953910533628933;
	setAttr -s 7 ".kit[3:6]"  9 10 1 10;
	setAttr -s 7 ".kot[3:6]"  9 10 1 10;
	setAttr -s 7 ".kix[5:6]"  0.63707560300827026 0.66666668653488159;
	setAttr -s 7 ".kiy[5:6]"  0.00089398719137534499 0;
	setAttr -s 7 ".kox[5:6]"  0.63707560300827026 0.66666668653488159;
	setAttr -s 7 ".koy[5:6]"  0.00089398707496002316 0;
createNode animCurveTL -n "Char_Hip_locator_translateZ";
	setAttr ".tan" 3;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0.037414363530582494 5 -0.15726637602639884 
		20 -0.1614430168543026 40 -0.16398438044662969 60 -0.15964445882280967 80 
		-0.15726637602639884;
	setAttr -s 7 ".kit[0:6]"  10 10 3 1 3 1 3;
	setAttr -s 7 ".kot[0:6]"  10 10 3 1 3 1 3;
	setAttr -s 7 ".kix[3:6]"  0.44905674457550049 0.66666668653488159 
		0.45922741293907166 0.66666668653488159;
	setAttr -s 7 ".kiy[3:6]"  -0.0044492022134363651 0 0.0027106788475066423 
		0;
	setAttr -s 7 ".kox[3:6]"  0.59874230623245239 0.66666668653488159 
		0.91845369338989258 0.66666668653488159;
	setAttr -s 7 ".koy[3:6]"  -0.0059322686865925789 0 0.0054213455878198147 
		0;
createNode animCurveTL -n "Char_Hip_locator_translateY";
	setAttr ".tan" 1;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 -0.020433619022911964 5 -0.051637082257696622 
		20 -0.05802423962250032 40 -0.057193333522879364 60 -0.05954251358478202 
		80 -0.051637082257696622;
	setAttr -s 7 ".kit[0:6]"  10 10 1 1 1 1 1;
	setAttr -s 7 ".kot[0:6]"  10 10 1 1 1 1 1;
	setAttr -s 7 ".kix[2:6]"  0.1468593031167984 0.48721268773078918 
		0.7035897970199585 0.60976290702819824 1.0024493932723999;
	setAttr -s 7 ".kiy[2:6]"  -0.00057487166486680508 -0.0097969751805067062 
		-0.0064097251743078232 0.0036544795148074627 -0.002341125626116991;
	setAttr -s 7 ".kox[2:6]"  0.73429751396179199 0.64961689710617065 
		0.3517947793006897 0.60976302623748779 1.0024497509002686;
	setAttr -s 7 ".koy[2:6]"  -0.0028743634466081858 -0.013062631711363792 
		-0.0032048642169684172 0.0036544797476381063 -0.0023411272559314966;
createNode animCurveTL -n "Char_Hip_locator_translateX";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 -0.049762091519964219 5 0.066874042172448467 
		20 0.058108132905130006 40 0.049901935270701386 60 0.055934225474650087 80 
		0.066874042172448467;
	setAttr -s 7 ".kit[3:6]"  1 1 1 10;
	setAttr -s 7 ".kot[3:6]"  1 1 1 10;
	setAttr -s 7 ".kix[3:6]"  0.35217803716659546 0.66962820291519165 
		0.36188429594039917 0.66666668653488159;
	setAttr -s 7 ".kiy[3:6]"  -0.0093158306553959846 -0.00089011213276535273 
		0.0072302063927054405 0;
	setAttr -s 7 ".kox[3:6]"  0.70435595512390137 0.3348143994808197 
		0.72376817464828491 0.66666668653488159;
	setAttr -s 7 ".koy[3:6]"  -0.018631676211953163 -0.00044505769619718194 
		0.014460415579378605 0;
createNode animCurveTA -n "Char_Bag_locator_rotateZ";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 0 5 -6.7097270679247689 40 
		-10.385882924913318 80 -6.7097270679247689;
	setAttr -s 5 ".kit[2:4]"  3 10 3;
	setAttr -s 5 ".kot[2:4]"  3 10 3;
createNode animCurveTA -n "Char_Bag_locator_rotateY";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 0 5 -24.005486609752403 40 
		-19.816277318619484 80 -24.005486609752403;
	setAttr -s 5 ".kit[2:4]"  3 10 3;
	setAttr -s 5 ".kot[2:4]"  3 10 3;
createNode animCurveTA -n "Char_Bag_locator_rotateX";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 0 5 0 40 1.2477515994946329 
		80 0;
createNode animCurveTA -n "Char_SmallSword_locator_rotateZ";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 15.000000000000002 5 9.6921754187547098 
		40 13.14373187969033 80 9.6921754187547098;
createNode animCurveTA -n "Char_SmallSword_locator_rotateY";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 0 5 8.810063617344392 40 
		7.7438573530905837 80 8.810063617344392;
createNode animCurveTA -n "Char_SmallSword_locator_rotateX";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 0 5 23.265079145375779 40 
		17.579502194203698 80 23.265079145375779;
createNode animCurveTL -n "Char_SmallSword_locator_translateZ";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 -0.040210713659284476 2 -0.040210713659284476 
		5 -0.040210713659284476 40 -0.040210713659284476 80 -0.040210713659284476;
createNode animCurveTL -n "Char_SmallSword_locator_translateY";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 -0.92352553218673483 2 -0.92172394262998947 
		5 -0.92172394262998947 40 -0.92172394262998947 80 -0.92172394262998947;
createNode animCurveTL -n "Char_SmallSword_locator_translateX";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 0.020592262861709541 5 0.020592262861709541 
		40 0.020592262861709541 80 0.020592262861709541;
createNode animCurveTA -n "Char_L_Clavice_locator_rotateZ";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 0 5 -10.814320486728878 40 
		-13.252130839073335 80 -10.814320486728878;
createNode animCurveTA -n "Char_L_Clavice_locator_rotateY";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 0 5 -3.7464163230089 40 0.62273784498000273 
		80 -3.7464163230089;
createNode animCurveTA -n "Char_L_Clavice_locator_rotateX";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 0 5 -10.897220128485484 40 
		-16.413212079771736 80 -10.897220128485484;
createNode animCurveTA -n "Char_R_Clavice_locator_rotateZ";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 0 5 0.72504957116732272 40 
		9.0052724458255753 80 0.72504957116732272;
	setAttr -s 5 ".kit[2:4]"  1 10 1;
	setAttr -s 5 ".kot[2:4]"  1 10 1;
	setAttr -s 5 ".kix[2:4]"  0.026390543207526207 1.1666667461395264 
		1.2691526412963867;
	setAttr -s 5 ".kiy[2:4]"  -0.0051881764084100723 0 -0.21529695391654968;
	setAttr -s 5 ".kox[2:4]"  1.0930348634719849 1.3333332538604736 
		1.2691529989242554;
	setAttr -s 5 ".koy[2:4]"  -0.21488223969936371 0 -0.21529701352119446;
createNode animCurveTA -n "Char_R_Clavice_locator_rotateY";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 0 5 -16.065060266995822 40 
		-12.07642108610667 80 -16.065060266995822;
	setAttr -s 5 ".kit[2:4]"  1 10 1;
	setAttr -s 5 ".kot[2:4]"  1 10 1;
	setAttr -s 5 ".kix[2:4]"  0.0049999016337096691 1.1666667461395264 
		1.2074915170669556;
	setAttr -s 5 ".kiy[2:4]"  -0.00093731930246576667 0 -0.23963500559329987;
	setAttr -s 5 ".kox[2:4]"  1.0716347694396973 1.3333332538604736 
		1.2074918746948242;
	setAttr -s 5 ".koy[2:4]"  -0.2008967399597168 0 -0.23963506519794464;
createNode animCurveTA -n "Char_R_Clavice_locator_rotateX";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 0 5 -1.8244965449281254 40 
		-1.7786265010053246 80 -1.8244965449281254;
	setAttr -s 5 ".kit[2:4]"  1 10 1;
	setAttr -s 5 ".kot[2:4]"  1 10 1;
	setAttr -s 5 ".kix[2:4]"  0.0064845560118556023 1.1666666269302368 
		1.2293301820755005;
	setAttr -s 5 ".kiy[2:4]"  0.00034248217707499862 0 0.063923828303813934;
	setAttr -s 5 ".kox[2:4]"  1.0731217861175537 1.3333333730697632 
		1.2293300628662109;
	setAttr -s 5 ".koy[2:4]"  0.056676976382732391 0 0.063923820853233337;
createNode animCurveTA -n "Char_Shield_locator_Hand_rotateZ";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 -2.97800001338583 5 -5.0566276381482984 
		40 -8.6135945883730383 80 -5.0566276381482984;
	setAttr -s 5 ".kit[2:4]"  1 10 10;
	setAttr -s 5 ".kot[2:4]"  1 10 10;
	setAttr -s 5 ".kix[2:4]"  0.083575360476970673 1.1666667461395264 
		1.3333333730697632;
	setAttr -s 5 ".kiy[2:4]"  -0.0076465494930744171 0 0.062080785632133484;
	setAttr -s 5 ".kox[2:4]"  1.1502373218536377 1.3333332538604736 
		1.3333333730697632;
	setAttr -s 5 ".koy[2:4]"  -0.10523851960897446 0 0.062080785632133484;
createNode animCurveTA -n "Char_Shield_locator_Hand_rotateY";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 -9.7822412312834413 5 -17.107761286541351 
		40 -14.672851124216253 80 -17.107761286541351;
	setAttr -s 5 ".kit[2:4]"  1 10 10;
	setAttr -s 5 ".kot[2:4]"  1 10 10;
	setAttr -s 5 ".kix[2:4]"  0.096254788339138031 1.1666666269302368 
		1.3333333730697632;
	setAttr -s 5 ".kiy[2:4]"  0.0064466414041817188 0 0;
	setAttr -s 5 ".kox[2:4]"  1.1629205942153931 1.3333333730697632 
		1.3333333730697632;
	setAttr -s 5 ".koy[2:4]"  0.077886335551738739 0 0;
createNode animCurveTA -n "Char_Shield_locator_Hand_rotateX";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 -1.2339729835558362 2 -50.078804475066228 
		5 -55.761927886665404 40 -55.390123601664214 80 -55.761927886665404;
	setAttr -s 5 ".kit[2:4]"  1 10 10;
	setAttr -s 5 ".kot[2:4]"  1 10 10;
	setAttr -s 5 ".kix[2:4]"  0.086931005120277405 1.1666666269302368 
		1.3333333730697632;
	setAttr -s 5 ".kiy[2:4]"  0.0011406884295865893 0 0;
	setAttr -s 5 ".kox[2:4]"  1.1535937786102295 1.3333333730697632 
		1.3333333730697632;
	setAttr -s 5 ".koy[2:4]"  0.015137187205255032 0 0;
createNode animCurveTL -n "Char_Shield_locator_Hand_translateZ";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 -0.011301811406185556 5 -0.011301811406185556 
		40 -0.0082271993039075425 80 -0.011301811406185556;
	setAttr -s 5 ".kit[2:4]"  1 10 10;
	setAttr -s 5 ".kot[2:4]"  1 10 10;
	setAttr -s 5 ".kix[2:4]"  0.099607102572917938 1.1666666269302368 
		1.3333333730697632;
	setAttr -s 5 ".kiy[2:4]"  0.00024327551363967359 0 0;
	setAttr -s 5 ".kox[2:4]"  1.1620807647705078 1.3333333730697632 
		1.3333333730697632;
	setAttr -s 5 ".koy[2:4]"  0.0028382090386003256 0 0;
createNode animCurveTL -n "Char_Shield_locator_Hand_translateY";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 -0.0098431871193776898 5 
		-0.0098431871193776898 40 -0.0034403696451043618 80 -0.0098431871193776898;
	setAttr -s 5 ".kit[2:4]"  1 10 10;
	setAttr -s 5 ".kot[2:4]"  1 10 10;
	setAttr -s 5 ".kix[2:4]"  0.099533453583717346 1.1666666269302368 
		1.3333333730697632;
	setAttr -s 5 ".kiy[2:4]"  0.00026071607135236263 0 0;
	setAttr -s 5 ".kox[2:4]"  1.1612265110015869 1.3333333730697632 
		1.3333333730697632;
	setAttr -s 5 ".koy[2:4]"  0.0030416955705732107 0 0;
createNode animCurveTL -n "Char_Shield_locator_Hand_translateX";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 -0.0040455390558233545 5 
		-0.0040455390558233545 40 -0.0087199311052271865 80 -0.0040455390558233545;
	setAttr -s 5 ".kit[2:4]"  1 10 10;
	setAttr -s 5 ".kot[2:4]"  1 10 10;
	setAttr -s 5 ".kix[2:4]"  0.099021270871162415 1.1666666269302368 
		1.3333333730697632;
	setAttr -s 5 ".kiy[2:4]"  -0.0004143499827478081 0 0;
	setAttr -s 5 ".kox[2:4]"  1.1552462577819824 1.3333333730697632 
		1.3333333730697632;
	setAttr -s 5 ".koy[2:4]"  -0.004834076389670372 0 0;
createNode animCurveTU -n "Char_L_Thumb_locator_Thumb02";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 0 80 0;
createNode animCurveTA -n "Char_L_Thumb_locator_rotateZ";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 6.2120208622334312e-018 2 -45.000000000000007 
		5 -45.000000000000007 80 -45.000000000000007;
createNode animCurveTA -n "Char_L_Thumb_locator_rotateY";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 6.7943978180678144e-019 2 0 5 
		0 80 0;
createNode animCurveTA -n "Char_L_Thumb_locator_rotateX";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 3.975693351829396e-016 2 0 5 
		0 80 0;
createNode animCurveTU -n "Char_L_Fingers_locator_Fingers02";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 4.6000000000000005 5 4.6000000000000005 
		80 4.6000000000000005;
createNode animCurveTA -n "Char_L_Fingers_locator_rotateZ";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 -35.00000000000005 5 -35.00000000000005 
		80 -35.00000000000005;
createNode animCurveTA -n "Char_Sword_locator_Hand_rotateZ";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 0 80 0;
createNode animCurveTA -n "Char_Sword_locator_Hand_rotateY";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 0 80 0;
createNode animCurveTA -n "Char_Sword_locator_Hand_rotateX";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 0 80 0;
createNode animCurveTL -n "Char_Sword_locator_Hand_translateZ";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 0 80 0;
createNode animCurveTL -n "Char_Sword_locator_Hand_translateY";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 0 80 0;
createNode animCurveTL -n "Char_Sword_locator_Hand_translateX";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 5 0 80 0;
createNode animCurveTU -n "Char_R_Thumb_locator_Thumb02";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 2.9000000000000004 5 2.9000000000000004 
		80 2.9000000000000004;
createNode animCurveTA -n "Char_R_Thumb_locator_rotateZ";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 3.1060104311167156e-018 2 8.3135312287614322 
		5 8.3135312287614322 80 8.3135312287614322;
createNode animCurveTA -n "Char_R_Thumb_locator_rotateY";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 2.9118847791719218e-019 2 -19.995134732632 
		5 -19.995134732632 80 -19.995134732632;
createNode animCurveTA -n "Char_R_Thumb_locator_rotateX";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 3.975693351829396e-016 2 1.5108588730100463 
		5 1.5108588730100463 80 1.5108588730100463;
createNode animCurveTU -n "Char_R_Fingers_locator_Fingers02";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 7.6000000000000005 5 7.6000000000000005 
		80 7.6000000000000005;
createNode animCurveTA -n "Char_R_Fingers_locator_rotateZ";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 24.999999999999996 5 24.999999999999996 
		80 24.999999999999996;
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 112 ".cel[1].cev";
	setAttr ".cd[0].cm" -type "characterMapping" 112 "Chest_locator.rotateZ" 
		2 1 "Chest_locator.rotateY" 2 2 "Chest_locator.rotateX" 
		2 3 "Shield_locator_World.rotateZ" 2 4 "Shield_locator_World.rotateY" 
		2 5 "Shield_locator_World.rotateX" 2 6 "Shield_locator_World.translateZ" 
		1 1 "Shield_locator_World.translateY" 1 2 "Shield_locator_World.translateX" 
		1 3 "Sword_locator_World.rotateZ" 2 7 "Sword_locator_World.rotateY" 
		2 8 "Sword_locator_World.rotateX" 2 9 "Sword_locator_World.translateZ" 
		1 4 "Sword_locator_World.translateY" 1 5 "Sword_locator_World.translateX" 
		1 6 "L_Locot_locator.translateZ" 1 7 "L_Locot_locator.translateY" 
		1 8 "L_Locot_locator.translateX" 1 9 "R_Locot_locator.translateZ" 
		1 10 "R_Locot_locator.translateY" 1 11 "R_Locot_locator.translateX" 
		1 12 "HeadTop_locator.translateZ" 1 13 "HeadTop_locator.translateY" 
		1 14 "HeadTop_locator.translateX" 1 15 "Head_locator.translateZ" 
		1 16 "Head_locator.translateY" 1 17 "Head_locator.translateX" 
		1 18 "Clothe_locator.rotateZ" 2 10 "Clothe_locator.rotateY" 
		2 11 "Clothe_locator.rotateX" 2 12 "Clothe_locator.translateZ" 
		1 19 "Clothe_locator.translateY" 1 20 "Clothe_locator.translateX" 
		1 21 "L_Hand_locator.Shield" 0 1 "L_Hand_locator.rotateZ" 
		2 13 "L_Hand_locator.rotateY" 2 14 "L_Hand_locator.rotateX" 
		2 15 "L_Hand_locator.translateZ" 1 22 "L_Hand_locator.translateY" 
		1 23 "L_Hand_locator.translateX" 1 24 "R_Hand_locator.Sword" 
		0 2 "R_Hand_locator.rotateZ" 2 16 "R_Hand_locator.rotateY" 
		2 17 "R_Hand_locator.rotateX" 2 18 "R_Hand_locator.translateZ" 
		1 25 "R_Hand_locator.translateY" 1 26 "R_Hand_locator.translateX" 
		1 27 "R_Knee_locator.translateZ" 1 28 "R_Knee_locator.translateY" 
		1 29 "R_Knee_locator.translateX" 1 30 "L_Knee_locator.translateZ" 
		1 31 "L_Knee_locator.translateY" 1 32 "L_Knee_locator.translateX" 
		1 33 "R_Leg_locator.Toe" 0 3 "R_Leg_locator.rotateZ" 2 
		19 "R_Leg_locator.rotateY" 2 20 "R_Leg_locator.rotateX" 2 
		21 "R_Leg_locator.translateZ" 1 34 "R_Leg_locator.translateY" 
		1 35 "R_Leg_locator.translateX" 1 36 "L_Leg_locator.Toe" 
		0 4 "L_Leg_locator.rotateZ" 2 22 "L_Leg_locator.rotateY" 
		2 23 "L_Leg_locator.rotateX" 2 24 "L_Leg_locator.translateZ" 
		1 37 "L_Leg_locator.translateY" 1 38 "L_Leg_locator.translateX" 
		1 39 "Hip_locator.rotateZ" 2 25 "Hip_locator.rotateY" 2 
		26 "Hip_locator.rotateX" 2 27 "Hip_locator.translateZ" 1 
		40 "Hip_locator.translateY" 1 41 "Hip_locator.translateX" 1 
		42 "Bag_locator.rotateZ" 2 28 "Bag_locator.rotateY" 2 29 "Bag_locator.rotateX" 
		2 30 "SmallSword_locator.rotateZ" 2 31 "SmallSword_locator.rotateY" 
		2 32 "SmallSword_locator.rotateX" 2 33 "SmallSword_locator.translateZ" 
		1 43 "SmallSword_locator.translateY" 1 44 "SmallSword_locator.translateX" 
		1 45 "L_Clavice_locator.rotateZ" 2 34 "L_Clavice_locator.rotateY" 
		2 35 "L_Clavice_locator.rotateX" 2 36 "R_Clavice_locator.rotateZ" 
		2 37 "R_Clavice_locator.rotateY" 2 38 "R_Clavice_locator.rotateX" 
		2 39 "Shield_locator_Hand.rotateZ" 2 40 "Shield_locator_Hand.rotateY" 
		2 41 "Shield_locator_Hand.rotateX" 2 42 "Shield_locator_Hand.translateZ" 
		1 46 "Shield_locator_Hand.translateY" 1 47 "Shield_locator_Hand.translateX" 
		1 48 "L_Thumb_locator.Thumb02" 0 5 "L_Thumb_locator.rotateZ" 
		2 43 "L_Thumb_locator.rotateY" 2 44 "L_Thumb_locator.rotateX" 
		2 45 "L_Fingers_locator.Fingers02" 0 6 "L_Fingers_locator.rotateZ" 
		2 46 "Sword_locator_Hand.rotateZ" 2 47 "Sword_locator_Hand.rotateY" 
		2 48 "Sword_locator_Hand.rotateX" 2 49 "Sword_locator_Hand.translateZ" 
		1 49 "Sword_locator_Hand.translateY" 1 50 "Sword_locator_Hand.translateX" 
		1 51 "R_Thumb_locator.Thumb02" 0 7 "R_Thumb_locator.rotateZ" 
		2 50 "R_Thumb_locator.rotateY" 2 51 "R_Thumb_locator.rotateX" 
		2 52 "R_Fingers_locator.Fingers02" 0 8 "R_Fingers_locator.rotateZ" 
		2 53  ;
	setAttr ".cd[0].cim" -type "Int32Array" 112 0 1 2 3
		 4 5 6 7 8 9 10 11 12 13 14
		 15 16 17 18 19 20 21 22 23 24 25
		 26 27 28 29 30 31 32 33 34 35 36
		 37 38 39 40 41 42 43 44 45 46 47
		 48 49 50 51 52 53 54 55 56 57 58
		 59 60 61 62 63 64 65 66 67 68 69
		 70 71 72 73 74 75 76 77 78 79 80
		 81 82 83 84 85 86 87 88 89 90 91
		 92 93 94 95 96 97 98 99 100 101 102
		 103 104 105 106 107 108 109 110 111 ;
createNode animClip -n "idle00";
	setAttr ".o" 1;
	setAttr ".sf" 5;
createNode lightLinker -n "lightLinker1";
	setAttr ".ihi" 0;
	setAttr -s 4 ".lnk";
select -ne :time1;
	setAttr ".o" 5;
select -ne :renderPartition;
	setAttr -s 4 ".st";
select -ne :renderGlobalsList1;
select -ne :defaultShaderList1;
	setAttr -s 4 ".s";
select -ne :postProcessList1;
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
select -ne :lightList1;
select -ne :defaultTextureList1;
	setAttr -s 2 ".tx";
select -ne :initialShadingGroup;
	addAttr -ci true -sn "materialIndex" -ln "materialIndex" -at "long";
	setAttr -k on ".nds";
	setAttr -k on ".mwc";
	setAttr ".ro" yes;
select -ne :initialParticleSE;
	addAttr -ci true -sn "materialIndex" -ln "materialIndex" -at "long";
	setAttr ".ro" yes;
select -ne :defaultRenderGlobals;
	addAttr -ci true -sn "currentRenderer" -ln "currentRenderer" -dt "string";
	setAttr ".mcfr" 30;
	setAttr -k on ".mbf";
	setAttr ".currentRenderer" -type "string" "mayaSoftware";
select -ne :hardwareRenderGlobals;
	setAttr ".fn" -type "string" "default-%4n";
	setAttr ".hwfr" 30;
select -ne :characterPartition;
select -ne :defaultHardwareRenderGlobals;
	setAttr ".fn" -type "string" "im";
	setAttr ".res" -type "string" "ntsc_4d 646 485 1.333";
select -ne :ikSystem;
connectAttr "idle00Source.st" "clipLibrary1.st[1]";
connectAttr "idle00Source.du" "clipLibrary1.du[1]";
connectAttr "Char_Chest_locator_rotateZ.a" "clipLibrary1.cel[1].cev[0].cevr"
		;
connectAttr "Char_Chest_locator_rotateY.a" "clipLibrary1.cel[1].cev[1].cevr"
		;
connectAttr "Char_Chest_locator_rotateX.a" "clipLibrary1.cel[1].cev[2].cevr"
		;
connectAttr "Char_Shield_locator_World_rotateZ.a" "clipLibrary1.cel[1].cev[3].cevr"
		;
connectAttr "Char_Shield_locator_World_rotateY.a" "clipLibrary1.cel[1].cev[4].cevr"
		;
connectAttr "Char_Shield_locator_World_rotateX.a" "clipLibrary1.cel[1].cev[5].cevr"
		;
connectAttr "Char_Shield_locator_World_translateZ.a" "clipLibrary1.cel[1].cev[6].cevr"
		;
connectAttr "Char_Shield_locator_World_translateY.a" "clipLibrary1.cel[1].cev[7].cevr"
		;
connectAttr "Char_Shield_locator_World_translateX.a" "clipLibrary1.cel[1].cev[8].cevr"
		;
connectAttr "Char_Sword_locator_World_rotateZ.a" "clipLibrary1.cel[1].cev[9].cevr"
		;
connectAttr "Char_Sword_locator_World_rotateY.a" "clipLibrary1.cel[1].cev[10].cevr"
		;
connectAttr "Char_Sword_locator_World_rotateX.a" "clipLibrary1.cel[1].cev[11].cevr"
		;
connectAttr "Char_Sword_locator_World_translateZ.a" "clipLibrary1.cel[1].cev[12].cevr"
		;
connectAttr "Char_Sword_locator_World_translateY.a" "clipLibrary1.cel[1].cev[13].cevr"
		;
connectAttr "Char_Sword_locator_World_translateX.a" "clipLibrary1.cel[1].cev[14].cevr"
		;
connectAttr "Char_L_Locot_locator_translateZ.a" "clipLibrary1.cel[1].cev[15].cevr"
		;
connectAttr "Char_L_Locot_locator_translateY.a" "clipLibrary1.cel[1].cev[16].cevr"
		;
connectAttr "Char_L_Locot_locator_translateX.a" "clipLibrary1.cel[1].cev[17].cevr"
		;
connectAttr "Char_R_Locot_locator_translateZ.a" "clipLibrary1.cel[1].cev[18].cevr"
		;
connectAttr "Char_R_Locot_locator_translateY.a" "clipLibrary1.cel[1].cev[19].cevr"
		;
connectAttr "Char_R_Locot_locator_translateX.a" "clipLibrary1.cel[1].cev[20].cevr"
		;
connectAttr "Char_HeadTop_locator_translateZ.a" "clipLibrary1.cel[1].cev[21].cevr"
		;
connectAttr "Char_HeadTop_locator_translateY.a" "clipLibrary1.cel[1].cev[22].cevr"
		;
connectAttr "Char_HeadTop_locator_translateX.a" "clipLibrary1.cel[1].cev[23].cevr"
		;
connectAttr "Char_Head_locator_translateZ.a" "clipLibrary1.cel[1].cev[24].cevr"
		;
connectAttr "Char_Head_locator_translateY.a" "clipLibrary1.cel[1].cev[25].cevr"
		;
connectAttr "Char_Head_locator_translateX.a" "clipLibrary1.cel[1].cev[26].cevr"
		;
connectAttr "Char_Clothe_locator_rotateZ.a" "clipLibrary1.cel[1].cev[27].cevr"
		;
connectAttr "Char_Clothe_locator_rotateY.a" "clipLibrary1.cel[1].cev[28].cevr"
		;
connectAttr "Char_Clothe_locator_rotateX.a" "clipLibrary1.cel[1].cev[29].cevr"
		;
connectAttr "Char_Clothe_locator_translateZ.a" "clipLibrary1.cel[1].cev[30].cevr"
		;
connectAttr "Char_Clothe_locator_translateY.a" "clipLibrary1.cel[1].cev[31].cevr"
		;
connectAttr "Char_Clothe_locator_translateX.a" "clipLibrary1.cel[1].cev[32].cevr"
		;
connectAttr "Char_L_Hand_locator_Shield.a" "clipLibrary1.cel[1].cev[33].cevr"
		;
connectAttr "Char_L_Hand_locator_rotateZ.a" "clipLibrary1.cel[1].cev[34].cevr"
		;
connectAttr "Char_L_Hand_locator_rotateY.a" "clipLibrary1.cel[1].cev[35].cevr"
		;
connectAttr "Char_L_Hand_locator_rotateX.a" "clipLibrary1.cel[1].cev[36].cevr"
		;
connectAttr "Char_L_Hand_locator_translateZ.a" "clipLibrary1.cel[1].cev[37].cevr"
		;
connectAttr "Char_L_Hand_locator_translateY.a" "clipLibrary1.cel[1].cev[38].cevr"
		;
connectAttr "Char_L_Hand_locator_translateX.a" "clipLibrary1.cel[1].cev[39].cevr"
		;
connectAttr "Char_R_Hand_locator_Sword.a" "clipLibrary1.cel[1].cev[40].cevr"
		;
connectAttr "Char_R_Hand_locator_rotateZ.a" "clipLibrary1.cel[1].cev[41].cevr"
		;
connectAttr "Char_R_Hand_locator_rotateY.a" "clipLibrary1.cel[1].cev[42].cevr"
		;
connectAttr "Char_R_Hand_locator_rotateX.a" "clipLibrary1.cel[1].cev[43].cevr"
		;
connectAttr "Char_R_Hand_locator_translateZ.a" "clipLibrary1.cel[1].cev[44].cevr"
		;
connectAttr "Char_R_Hand_locator_translateY.a" "clipLibrary1.cel[1].cev[45].cevr"
		;
connectAttr "Char_R_Hand_locator_translateX.a" "clipLibrary1.cel[1].cev[46].cevr"
		;
connectAttr "Char_R_Knee_locator_translateZ.a" "clipLibrary1.cel[1].cev[47].cevr"
		;
connectAttr "Char_R_Knee_locator_translateY.a" "clipLibrary1.cel[1].cev[48].cevr"
		;
connectAttr "Char_R_Knee_locator_translateX.a" "clipLibrary1.cel[1].cev[49].cevr"
		;
connectAttr "Char_L_Knee_locator_translateZ.a" "clipLibrary1.cel[1].cev[50].cevr"
		;
connectAttr "Char_L_Knee_locator_translateY.a" "clipLibrary1.cel[1].cev[51].cevr"
		;
connectAttr "Char_L_Knee_locator_translateX.a" "clipLibrary1.cel[1].cev[52].cevr"
		;
connectAttr "Char_R_Leg_locator_Toe.a" "clipLibrary1.cel[1].cev[53].cevr"
		;
connectAttr "Char_R_Leg_locator_rotateZ.a" "clipLibrary1.cel[1].cev[54].cevr"
		;
connectAttr "Char_R_Leg_locator_rotateY.a" "clipLibrary1.cel[1].cev[55].cevr"
		;
connectAttr "Char_R_Leg_locator_rotateX.a" "clipLibrary1.cel[1].cev[56].cevr"
		;
connectAttr "Char_R_Leg_locator_translateZ.a" "clipLibrary1.cel[1].cev[57].cevr"
		;
connectAttr "Char_R_Leg_locator_translateY.a" "clipLibrary1.cel[1].cev[58].cevr"
		;
connectAttr "Char_R_Leg_locator_translateX.a" "clipLibrary1.cel[1].cev[59].cevr"
		;
connectAttr "Char_L_Leg_locator_Toe.a" "clipLibrary1.cel[1].cev[60].cevr"
		;
connectAttr "Char_L_Leg_locator_rotateZ.a" "clipLibrary1.cel[1].cev[61].cevr"
		;
connectAttr "Char_L_Leg_locator_rotateY.a" "clipLibrary1.cel[1].cev[62].cevr"
		;
connectAttr "Char_L_Leg_locator_rotateX.a" "clipLibrary1.cel[1].cev[63].cevr"
		;
connectAttr "Char_L_Leg_locator_translateZ.a" "clipLibrary1.cel[1].cev[64].cevr"
		;
connectAttr "Char_L_Leg_locator_translateY.a" "clipLibrary1.cel[1].cev[65].cevr"
		;
connectAttr "Char_L_Leg_locator_translateX.a" "clipLibrary1.cel[1].cev[66].cevr"
		;
connectAttr "Char_Hip_locator_rotateZ.a" "clipLibrary1.cel[1].cev[67].cevr"
		;
connectAttr "Char_Hip_locator_rotateY.a" "clipLibrary1.cel[1].cev[68].cevr"
		;
connectAttr "Char_Hip_locator_rotateX.a" "clipLibrary1.cel[1].cev[69].cevr"
		;
connectAttr "Char_Hip_locator_translateZ.a" "clipLibrary1.cel[1].cev[70].cevr"
		;
connectAttr "Char_Hip_locator_translateY.a" "clipLibrary1.cel[1].cev[71].cevr"
		;
connectAttr "Char_Hip_locator_translateX.a" "clipLibrary1.cel[1].cev[72].cevr"
		;
connectAttr "Char_Bag_locator_rotateZ.a" "clipLibrary1.cel[1].cev[73].cevr"
		;
connectAttr "Char_Bag_locator_rotateY.a" "clipLibrary1.cel[1].cev[74].cevr"
		;
connectAttr "Char_Bag_locator_rotateX.a" "clipLibrary1.cel[1].cev[75].cevr"
		;
connectAttr "Char_SmallSword_locator_rotateZ.a" "clipLibrary1.cel[1].cev[76].cevr"
		;
connectAttr "Char_SmallSword_locator_rotateY.a" "clipLibrary1.cel[1].cev[77].cevr"
		;
connectAttr "Char_SmallSword_locator_rotateX.a" "clipLibrary1.cel[1].cev[78].cevr"
		;
connectAttr "Char_SmallSword_locator_translateZ.a" "clipLibrary1.cel[1].cev[79].cevr"
		;
connectAttr "Char_SmallSword_locator_translateY.a" "clipLibrary1.cel[1].cev[80].cevr"
		;
connectAttr "Char_SmallSword_locator_translateX.a" "clipLibrary1.cel[1].cev[81].cevr"
		;
connectAttr "Char_L_Clavice_locator_rotateZ.a" "clipLibrary1.cel[1].cev[82].cevr"
		;
connectAttr "Char_L_Clavice_locator_rotateY.a" "clipLibrary1.cel[1].cev[83].cevr"
		;
connectAttr "Char_L_Clavice_locator_rotateX.a" "clipLibrary1.cel[1].cev[84].cevr"
		;
connectAttr "Char_R_Clavice_locator_rotateZ.a" "clipLibrary1.cel[1].cev[85].cevr"
		;
connectAttr "Char_R_Clavice_locator_rotateY.a" "clipLibrary1.cel[1].cev[86].cevr"
		;
connectAttr "Char_R_Clavice_locator_rotateX.a" "clipLibrary1.cel[1].cev[87].cevr"
		;
connectAttr "Char_Shield_locator_Hand_rotateZ.a" "clipLibrary1.cel[1].cev[88].cevr"
		;
connectAttr "Char_Shield_locator_Hand_rotateY.a" "clipLibrary1.cel[1].cev[89].cevr"
		;
connectAttr "Char_Shield_locator_Hand_rotateX.a" "clipLibrary1.cel[1].cev[90].cevr"
		;
connectAttr "Char_Shield_locator_Hand_translateZ.a" "clipLibrary1.cel[1].cev[91].cevr"
		;
connectAttr "Char_Shield_locator_Hand_translateY.a" "clipLibrary1.cel[1].cev[92].cevr"
		;
connectAttr "Char_Shield_locator_Hand_translateX.a" "clipLibrary1.cel[1].cev[93].cevr"
		;
connectAttr "Char_L_Thumb_locator_Thumb02.a" "clipLibrary1.cel[1].cev[94].cevr"
		;
connectAttr "Char_L_Thumb_locator_rotateZ.a" "clipLibrary1.cel[1].cev[95].cevr"
		;
connectAttr "Char_L_Thumb_locator_rotateY.a" "clipLibrary1.cel[1].cev[96].cevr"
		;
connectAttr "Char_L_Thumb_locator_rotateX.a" "clipLibrary1.cel[1].cev[97].cevr"
		;
connectAttr "Char_L_Fingers_locator_Fingers02.a" "clipLibrary1.cel[1].cev[98].cevr"
		;
connectAttr "Char_L_Fingers_locator_rotateZ.a" "clipLibrary1.cel[1].cev[99].cevr"
		;
connectAttr "Char_Sword_locator_Hand_rotateZ.a" "clipLibrary1.cel[1].cev[100].cevr"
		;
connectAttr "Char_Sword_locator_Hand_rotateY.a" "clipLibrary1.cel[1].cev[101].cevr"
		;
connectAttr "Char_Sword_locator_Hand_rotateX.a" "clipLibrary1.cel[1].cev[102].cevr"
		;
connectAttr "Char_Sword_locator_Hand_translateZ.a" "clipLibrary1.cel[1].cev[103].cevr"
		;
connectAttr "Char_Sword_locator_Hand_translateY.a" "clipLibrary1.cel[1].cev[104].cevr"
		;
connectAttr "Char_Sword_locator_Hand_translateX.a" "clipLibrary1.cel[1].cev[105].cevr"
		;
connectAttr "Char_R_Thumb_locator_Thumb02.a" "clipLibrary1.cel[1].cev[106].cevr"
		;
connectAttr "Char_R_Thumb_locator_rotateZ.a" "clipLibrary1.cel[1].cev[107].cevr"
		;
connectAttr "Char_R_Thumb_locator_rotateY.a" "clipLibrary1.cel[1].cev[108].cevr"
		;
connectAttr "Char_R_Thumb_locator_rotateX.a" "clipLibrary1.cel[1].cev[109].cevr"
		;
connectAttr "Char_R_Fingers_locator_Fingers02.a" "clipLibrary1.cel[1].cev[110].cevr"
		;
connectAttr "Char_R_Fingers_locator_rotateZ.a" "clipLibrary1.cel[1].cev[111].cevr"
		;
connectAttr "idle00Source.st" "idle00.st";
connectAttr "idle00Source.du" "idle00.du";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[2].llnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[4].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[4].olnk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of Footman.idle00.ma
