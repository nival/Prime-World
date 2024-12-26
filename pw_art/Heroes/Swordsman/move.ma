//Maya ASCII 2008 scene
//Name: move.ma
//Last modified: Tue, Oct 28, 2008 05:15:10 PM
//Codeset: 1251
requires maya "2008";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Complete 2008";
fileInfo "version" "2008";
fileInfo "cutIdentifier" "200708022245-704165";
fileInfo "osv" "Microsoft Windows XP Service Pack 2 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 113 ".cel[0].cev";
	setAttr ".cd[0].cm" -type "characterMapping" 116 "Chest_locator.rotateZ" 2 
		1 "Chest_locator.rotateY" 2 2 "Chest_locator.rotateX" 2 3 "Shield_locator_World.rotateZ" 
		2 4 "Shield_locator_World.rotateY" 2 5 "Shield_locator_World.rotateX" 
		2 6 "Shield_locator_World.translateZ" 1 1 "Shield_locator_World.translateY" 
		1 2 "Shield_locator_World.translateX" 1 3 "Sword_locator_World.rotateZ" 
		2 7 "Sword_locator_World.rotateY" 2 8 "Sword_locator_World.rotateX" 
		2 9 "Sword_locator_World.translateZ" 1 4 "Sword_locator_World.translateY" 
		1 5 "Sword_locator_World.translateX" 1 6 "L_Locot_locator.translateZ" 
		1 7 "L_Locot_locator.translateY" 1 8 "L_Locot_locator.translateX" 
		1 9 "R_Locot_locator.translateZ" 1 10 "R_Locot_locator.translateY" 
		1 11 "R_Locot_locator.translateX" 1 12 "HeadTop_locator.translateZ" 
		1 13 "HeadTop_locator.translateY" 1 14 "HeadTop_locator.translateX" 
		1 15 "Head_locator.translateZ" 1 16 "Head_locator.translateY" 1 
		17 "Head_locator.translateX" 1 18 "Clothe_locator.rotateZ" 2 10 "Clothe_locator.rotateY" 
		2 11 "Clothe_locator.rotateX" 2 12 "Clothe_locator.translateZ" 
		1 19 "Clothe_locator.translateY" 1 20 "Clothe_locator.translateX" 
		1 21 "L_Hand_locator.Shield" 0 1 "L_Hand_locator.rotateZ" 2 
		13 "L_Hand_locator.rotateY" 2 14 "L_Hand_locator.rotateX" 2 15 "L_Hand_locator.translateZ" 
		1 22 "L_Hand_locator.translateY" 1 23 "L_Hand_locator.translateX" 
		1 24 "R_Hand_locator.Sword" 0 2 "R_Hand_locator.rotateZ" 2 
		16 "R_Hand_locator.rotateY" 2 17 "R_Hand_locator.rotateX" 2 18 "R_Hand_locator.translateZ" 
		1 25 "R_Hand_locator.translateY" 1 26 "R_Hand_locator.translateX" 
		1 27 "R_Knee_locator.translateZ" 1 28 "R_Knee_locator.translateY" 
		1 29 "R_Knee_locator.translateX" 1 30 "L_Knee_locator.translateZ" 
		1 31 "L_Knee_locator.translateY" 1 32 "L_Knee_locator.translateX" 
		1 33 "R_Leg_locator.Toe" 0 3 "R_Leg_locator.rotateZ" 2 19 "R_Leg_locator.rotateY" 
		2 20 "R_Leg_locator.rotateX" 2 21 "R_Leg_locator.translateZ" 1 
		34 "R_Leg_locator.translateY" 1 35 "R_Leg_locator.translateX" 1 
		36 "L_Leg_locator.Toe" 0 4 "L_Leg_locator.rotateZ" 2 22 "L_Leg_locator.rotateY" 
		2 23 "L_Leg_locator.rotateX" 2 24 "L_Leg_locator.translateZ" 1 
		37 "L_Leg_locator.translateY" 1 38 "L_Leg_locator.translateX" 1 
		39 "Hip_locator.rotateZ" 2 25 "Hip_locator.rotateY" 2 26 "Hip_locator.rotateX" 
		2 27 "Hip_locator.translateZ" 1 40 "Hip_locator.translateY" 1 
		41 "Hip_locator.translateX" 1 42 "Bag_locator.rotateZ" 2 28 "Bag_locator.rotateY" 
		2 29 "Bag_locator.rotateX" 2 30 "SmallSword_locator.rotateZ" 2 
		31 "SmallSword_locator.rotateY" 2 32 "SmallSword_locator.rotateX" 2 
		33 "SmallSword_locator.translateZ" 1 43 "SmallSword_locator.translateY" 
		1 44 "SmallSword_locator.translateX" 1 45 "L_Clavice_locator.rotateZ" 
		2 34 "L_Clavice_locator.rotateY" 2 35 "L_Clavice_locator.rotateX" 
		2 36 "R_Clavice_locator.rotateZ" 2 37 "R_Clavice_locator.rotateY" 
		2 38 "R_Clavice_locator.rotateX" 2 39 "Shield_locator_Hand.rotateZ" 
		2 40 "Shield_locator_Hand.rotateY" 2 41 "Shield_locator_Hand.rotateX" 
		2 42 "Shield_locator_Hand.translateZ" 1 46 "Shield_locator_Hand.translateY" 
		1 47 "Shield_locator_Hand.translateX" 1 48 "L_Thumb_locator.Thumb02" 
		0 5 "L_Thumb_locator.rotateZ" 2 43 "L_Thumb_locator.rotateY" 2 
		44 "L_Thumb_locator.rotateX" 2 45 "L_Fingers_locator.Fingers02" 0 
		6 "L_Fingers_locator.rotateZ" 2 46 "Sword_locator_Hand.rotateZ" 2 
		47 "Sword_locator_Hand.rotateY" 2 48 "Sword_locator_Hand.rotateX" 2 
		49 "Sword_locator_Hand.translateZ" 1 49 "Sword_locator_Hand.translateY" 
		1 50 "Sword_locator_Hand.translateX" 1 51 "R_Thumb_locator.Thumb02" 
		0 7 "R_Thumb_locator.rotateZ" 2 50 "R_Thumb_locator.rotateY" 2 
		51 "R_Thumb_locator.rotateX" 2 52 "R_Fingers_locator.Fingers02" 0 
		8 "R_Fingers_locator.rotateZ" 2 53 "Global.Mark" 0 9 "Weapon.Transparency" 
		0 10 "_.Transparency" 0 11 "Global.translateY" 1 52  ;
	setAttr ".cd[0].cim" -type "Int32Array" 116 0 1 2 3 4
		 5 6 7 8 9 10 11 12 13 14 15 16
		 17 18 19 20 21 22 23 24 25 26 27 28
		 29 30 31 32 33 34 35 36 37 38 39 40
		 41 42 43 44 45 46 47 48 49 50 51 52
		 53 54 55 56 57 58 59 60 61 62 63 64
		 65 66 67 68 69 70 71 72 73 74 75 76
		 77 78 79 80 81 82 83 84 85 86 87 88
		 89 90 91 92 93 94 95 96 97 98 99 100
		 101 102 103 104 105 106 107 108 109 110 111 112
		 113 114 115 ;
createNode animClip -n "clip00Source";
	setAttr ".ihi" 0;
	setAttr -s 113 ".ac";
	setAttr ".ac[0:111]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[115]" no;
	setAttr ".ss" 5;
	setAttr ".se" 28;
	setAttr ".ci" no;
createNode animCurveTA -n "animCurveTA393";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 -179.31597800000003 5 -177.68614890000001 
		11 -183.27882495046578 17 -177.68614890000001 23 -179.62102174644383 29 -177.68614890000001;
	setAttr -s 7 ".kit[2:6]"  9 10 1 10 10;
	setAttr -s 7 ".kot[2:6]"  9 10 1 10 10;
	setAttr -s 7 ".kix[4:6]"  0.33933407068252563 0.20000000298023224 
		0.20000000298023224;
	setAttr -s 7 ".kiy[4:6]"  -0.027138842269778252 0 0;
	setAttr -s 7 ".kox[4:6]"  0.1726694256067276 0.20000000298023224 
		0.20000000298023224;
	setAttr -s 7 ".koy[4:6]"  -0.013809571042656898 0 0;
createNode animCurveTA -n "animCurveTA394";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 -135.25815739999999 5 -182.0991597 
		11 -171.65062681551237 17 -182.0991597 23 -192.18052813130657 29 -182.0991597;
	setAttr -s 7 ".kit[2:6]"  1 10 1 10 10;
	setAttr -s 7 ".kot[2:6]"  1 10 1 10 10;
	setAttr -s 7 ".kix[2:6]"  0.066674999892711639 0.20000000298023224 
		0.384102463722229 0.19999998807907104 0.19999997317790985;
	setAttr -s 7 ".kiy[2:6]"  0.12634657323360443 0 -0.734610915184021 
		0 0.17595307528972626;
	setAttr -s 7 ".kox[2:6]"  0.2000083327293396 0.19999998807907104 
		0.21742744743824005 0.20000000298023224 0.19999997317790985;
	setAttr -s 7 ".koy[2:6]"  0.37900805473327637 0 -0.41583839058876038 
		0 0.17595307528972626;
createNode animCurveTA -n "animCurveTA395";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 182.4295722 5 209.58565918794912 
		11 203.85096493116615 17 209.58565918794912 23 204.00658727550805 29 209.58565918794912;
	setAttr -s 7 ".kit[2:6]"  3 10 3 10 3;
	setAttr -s 7 ".kot[2:6]"  3 10 3 10 3;
createNode animCurveTA -n "animCurveTA396";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  5 0 29 0;
createNode animCurveTA -n "animCurveTA397";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  5 0 29 0;
createNode animCurveTA -n "animCurveTA398";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  5 0 29 0;
createNode animCurveTL -n "animCurveTL319";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  5 0 29 4.5600408628065141;
createNode animCurveTL -n "animCurveTL320";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  5 0 29 0;
createNode animCurveTL -n "animCurveTL321";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  5 0 29 0;
createNode animCurveTA -n "animCurveTA399";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  5 0 29 0;
createNode animCurveTA -n "animCurveTA400";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  5 0 29 0;
createNode animCurveTA -n "animCurveTA401";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  5 0 29 0;
createNode animCurveTL -n "animCurveTL322";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  5 0 29 4.5600408628065141;
createNode animCurveTL -n "animCurveTL323";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  5 0 29 0;
createNode animCurveTL -n "animCurveTL324";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  5 0 29 0;
createNode animCurveTL -n "animCurveTL325";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 0.23121685316153834 9 0.99442627184707222 
		17 2.5208451269357361 21 3.2840545345800454 29 4.7912577159680518;
createNode animCurveTL -n "animCurveTL326";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -0.22393532930211713 9 0.015269793485636451 
		17 -0.28417384571043358 21 0.045787731600359982 29 -0.22393532930211713;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL327";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  5 0.24318228952717219 9 0.243 17 0.24295 
		21 0.243 29 0.24318228952717219;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 10;
	setAttr -s 5 ".kot[0:4]"  3 9 9 9 10;
createNode animCurveTL -n "animCurveTL328";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  5 -0.2613544330215532 29 4.2986864297849605;
createNode animCurveTL -n "animCurveTL329";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  5 -0.24709570664594427 29 -0.24709570664594427;
createNode animCurveTL -n "animCurveTL330";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  5 -0.12301670324413685 29 -0.12301670324413685;
createNode animCurveTL -n "animCurveTL331";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -0.0070963888536680897 11 1.1329138350950196 
		17 2.2729240447153503 23 3.4129342593340981 29 4.552944473952846;
createNode animCurveTL -n "animCurveTL332";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -0.0034360675845639399 11 -0.0034360675845639399 
		17 -0.0034360675845639399 23 -0.0034360675845639399 29 -0.0034360675845639399;
createNode animCurveTL -n "animCurveTL333";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 0.028873232947846241 11 0.013470496449457605 
		17 0.028873232947846241 23 0.044275969446234881 29 0.028873232947846241;
	setAttr -s 5 ".kit[0:4]"  1 10 9 10 1;
	setAttr -s 5 ".kot[0:4]"  1 10 9 10 1;
	setAttr -s 5 ".kix[0:4]"  0.1606593132019043 0.20000000298023224 
		0.20000000298023224 0.20000000298023224 0.17359758913516998;
	setAttr -s 5 ".kiy[0:4]"  -0.019565446302294731 0 0.015402737073600292 
		0 -0.016313398256897926;
	setAttr -s 5 ".kox[0:4]"  0.16474619507789612 0.20000000298023224 
		0.20000000298023224 0.20000000298023224 0.17359763383865356;
	setAttr -s 5 ".koy[0:4]"  -0.018625961616635323 0 0.015402737073600292 
		0 -0.016313400119543076;
createNode animCurveTL -n "animCurveTL334";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0.08164236305 5 0.68687341290000004 
		11 1.8292853355384517 17 2.9535618523484191 23 4.1041887426760333 29 5.2469142757065148;
createNode animCurveTL -n "animCurveTL335";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0.0069138432029999999 5 -0.099744420740000006 
		11 0.088647660640986725 17 -0.096503280882800579 23 0.088710639021796434 29 -0.099744420740000006;
createNode animCurveTL -n "animCurveTL336";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0.0015309008900000001 5 -0.01327848033 
		11 -0.036125925132362451 17 0.0053779874025126143 23 0.031147180068443532 29 -0.01327848033;
	setAttr -s 7 ".kit[2:6]"  1 10 9 10 1;
	setAttr -s 7 ".kot[2:6]"  1 10 9 10 1;
	setAttr -s 7 ".kix[2:6]"  0.057070519775152206 0.20000000298023224 
		0.20000000298023224 0.20000000298023224 0.15226954221725464;
	setAttr -s 7 ".kiy[2:6]"  -0.010229310020804405 0 0.033636555075645447 
		0 -0.038493093103170395;
	setAttr -s 7 ".kox[2:6]"  0.17121152579784393 0.20000000298023224 
		0.20000000298023224 0.20000000298023224 0.14662754535675049;
	setAttr -s 7 ".koy[2:6]"  -0.030687924474477768 0 0.033636551350355148 
		0 -0.040377356112003326;
createNode animCurveTA -n "animCurveTA402";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  5 0 9 -5.1791040330361513 15 0.33528680556538576 
		19 -0.96617343673067591 23 0.72025626372224949 29 0;
createNode animCurveTA -n "animCurveTA403";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  5 0 9 -11.18181240440166 15 1.2323990568068899 
		19 -6.4954250205661115 23 3.3657870972447355 29 0;
createNode animCurveTA -n "animCurveTA404";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  5 13.657893158781347 9 53.685647903961708 
		15 56.969229176210561 19 31.795798041389883 23 65.799917200303753 29 13.657893158781347;
createNode animCurveTL -n "animCurveTL337";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  5 -0.0070963888536680897 9 0.75328324515760259 
		15 1.8938527048868978 19 2.6542323461259212 23 3.4146119807106161 29 4.552944473952846;
createNode animCurveTL -n "animCurveTL338";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  5 -0.0034360675845639399 9 -0.0034360675845639399 
		15 -0.0034360675845639399 19 -0.0034360675845639399 23 -0.0034360675845639399 29 
		-0.0034360675845639399;
createNode animCurveTL -n "animCurveTL339";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  5 0.049818208219252202 9 0.049818208219252202 
		15 0.049818208219252202 19 0.049818208219252202 23 0.049818208219252202 29 0.049818208219252202;
createNode animCurveTU -n "animCurveTU57";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  5 1 9 1 17 1 21 1 29 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTA -n "animCurveTA405";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 -97.317776110000011 5 -168.4988682818138 
		9 -168.61967872282904 17 -169.34454136892043 21 -169.59824329505244 29 -168.4988682818138;
createNode animCurveTA -n "animCurveTA406";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 -22.510433710000001 5 -48.238105777486275 
		9 -48.143821170269035 17 -47.578113526965623 21 -47.380115851809435 29 -48.238105777486275;
createNode animCurveTA -n "animCurveTA407";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 33.744205129999997 5 73.219090016899841 
		9 73.384302378100287 17 73.630159022882225 21 73.716208848555908 29 73.219090016899841;
	setAttr -s 7 ".kit[2:6]"  3 3 10 10 10;
	setAttr -s 7 ".kot[2:6]"  3 3 10 10 10;
createNode animCurveTL -n "animCurveTL340";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0.19256966180000001 5 0.52860064094033299 
		9 1.2130289717742164 17 2.8038576806392199 21 3.4348295149527961 29 5.0886415037468469;
createNode animCurveTL -n "animCurveTL341";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 -0.47591661800000001 5 -0.32282175818927028 
		9 -0.23433969441863781 17 -0.28570951117028665 21 -0.16242682339457701 29 -0.32282175818927028;
	setAttr -s 7 ".kit[2:6]"  3 10 10 10 3;
	setAttr -s 7 ".kot[2:6]"  3 10 10 10 3;
createNode animCurveTL -n "animCurveTL342";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 -0.35103494870000002 5 -0.4056890735357418 
		9 -0.3843075475089347 17 -0.30492104774808637 21 -0.31810330175457752 29 -0.4056890735357418;
	setAttr -s 7 ".kit[3:6]"  9 9 9 3;
	setAttr -s 7 ".kot[3:6]"  9 9 9 3;
createNode animCurveTU -n "animCurveTU58";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  5 1 9 1 13 1 17 1 29 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTA -n "animCurveTA408";
	setAttr ".tan" 9;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 118.28613840000001 5 59.074871366107097 
		9 59.465643243918151 13 58.025598968102742 17 57.416495903208038 21 57.228461481236842 
		25 57.541390121232865 29 59.074871366107097;
	setAttr -s 9 ".kit[0:8]"  10 10 10 9 9 9 9 9 
		10;
	setAttr -s 9 ".kot[0:8]"  10 10 10 9 9 9 9 9 
		10;
createNode animCurveTA -n "animCurveTA409";
	setAttr ".tan" 9;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 -52.494683350000003 5 16.861928234010957 
		9 17.345017229976314 13 18.930829691917804 17 21.377223656766247 21 20.555934336011912 
		25 18.475087066470419 29 16.861928234010957;
	setAttr -s 9 ".kit[0:8]"  10 10 10 9 9 1 9 9 
		10;
	setAttr -s 9 ".kot[0:8]"  10 10 10 9 9 1 9 9 
		10;
	setAttr -s 9 ".kix[5:8]"  0.13043402135372162 0.13333332538604736 
		0.13333332538604736 0.13333332538604736;
	setAttr -s 9 ".kiy[5:8]"  0.015809608623385429 -0.025325918570160866 
		-0.032236285507678986 0;
	setAttr -s 9 ".kox[5:8]"  0.13043402135372162 0.13333334028720856 
		0.13333334028720856 0.13333332538604736;
	setAttr -s 9 ".koy[5:8]"  0.015809608623385429 -0.025325920432806015 
		-0.032236289232969284 0;
createNode animCurveTA -n "animCurveTA410";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 -49.070871500000003 5 3.6903478830941272 
		9 1.4651686493555511 13 -3.5208134737810814 17 -6.2737962068061748 21 -4.4313373188877732 
		25 0.51634001602135815 29 3.6903478830941272;
	setAttr -s 9 ".kit[3:8]"  9 9 10 9 9 3;
	setAttr -s 9 ".kot[3:8]"  9 9 10 9 9 3;
createNode animCurveTL -n "animCurveTL343";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 -0.42755899860000002 5 0.043272641257086408 
		9 0.71608787512421246 13 1.4393984928263257 17 2.3533503992162759 21 3.3175291560963456 
		25 4.1425136550470203 29 4.6033135040636006;
createNode animCurveTL -n "animCurveTL344";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 -0.43178570799999999 5 -0.35995647453601715 
		9 -0.15975256603032439 13 -0.29901692819285453 17 -0.39007266127806389 21 -0.20646708674335792 
		25 -0.30852504394337038 29 -0.35995647453601715;
	setAttr -s 9 ".kit[2:8]"  3 10 10 10 10 10 10;
	setAttr -s 9 ".kot[2:8]"  3 10 10 10 10 10 10;
createNode animCurveTL -n "animCurveTL345";
	setAttr ".tan" 9;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0.43691536339999998 5 0.20140931592105607 
		9 0.2308930341211389 13 0.25947127977282353 17 0.27685557487354279 21 0.27263606332636753 
		25 0.23983581141953614 29 0.20140931592105607;
	setAttr -s 9 ".kit[0:8]"  10 10 3 9 9 10 9 9 
		3;
	setAttr -s 9 ".kot[0:8]"  10 10 3 9 9 10 9 9 
		3;
createNode animCurveTL -n "animCurveTL346";
	setAttr ".tan" 10;
	setAttr -s 15 ".ktv[0:14]"  0 0 3 -0.27992041070000001 5 0.26061860679999999 
		7 0.74500466914151142 9 1.2086192429356977 11 1.6245296859174381 13 1.9048452171010368 
		15 2.2696394015180474 17 2.4771364425358433 19 2.5801309126428627 21 2.767915204750516 
		23 3.1830753060039405 25 3.7923261292456205 27 4.4971729601475765 29 4.8206594696065137;
createNode animCurveTL -n "animCurveTL347";
	setAttr ".tan" 10;
	setAttr -s 15 ".ktv[0:14]"  0 0 3 -0.011100986429999999 5 -0.011082844749999999 
		7 0.16671739702012953 9 0.34451763879025898 11 0.35288954917220272 13 0.091773711905289934 
		15 0.034174630155235253 17 0.027327942609520317 19 0.032390853877312248 21 0.020232920043042196 
		23 0.00052533272388519126 25 -0.055388174454169936 27 -0.098486405469866145 29 -0.011082844749999999;
	setAttr -s 15 ".kit[7:14]"  9 9 9 9 9 9 10 3;
	setAttr -s 15 ".kot[7:14]"  9 9 9 9 9 9 10 3;
createNode animCurveTL -n "animCurveTL348";
	setAttr ".tan" 9;
	setAttr -s 15 ".ktv[0:14]"  0 0 3 -0.25099270909999999 5 -0.0851 7 
		-0.12066103361413706 9 -0.14258963172586336 11 -0.1297993820066442 13 -0.10710468877480202 
		15 -0.083477799563388494 17 -0.065839102474339078 19 -0.056183208075469324 21 -0.044411366718590112 
		23 -0.042175150262845629 25 -0.05023933184679133 27 -0.06720875803587982 29 -0.0851;
	setAttr -s 15 ".kit[0:14]"  10 10 3 9 9 9 9 9 
		9 9 9 9 9 9 10;
	setAttr -s 15 ".kot[0:14]"  10 10 3 9 9 9 9 9 
		9 9 9 9 9 9 10;
createNode animCurveTL -n "animCurveTL349";
	setAttr ".tan" 10;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0.2085622741 5 0.38005455189999998 
		9 1.1077530859380598 13 1.757951428923767 17 2.523864950281637 19 3.0885262082335996 
		21 3.4992015653836823 23 3.9154268273570083 25 4.2993146617476006 27 4.6567220122157194 
		29 4.9400954147065148;
createNode animCurveTL -n "animCurveTL350";
	setAttr ".tan" 10;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0.046188826689999997 5 -0.011877587009999999 
		9 0.17651449437098674 13 -0.18059981247935022 17 -0.012914933124487049 19 0.096763435856066005 
		21 0.30629328484158197 23 0.30382369380590174 25 0.18822279624273466 27 0.057715588584964422 
		29 -0.011877587009999999;
	setAttr -s 12 ".kit[2:11]"  3 10 3 10 10 10 10 10 
		10 3;
	setAttr -s 12 ".kot[2:11]"  3 10 3 10 10 10 10 10 
		10 3;
createNode animCurveTL -n "animCurveTL351";
	setAttr ".tan" 9;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0.024062140980000001 5 0.038694681139999999 
		9 0.05451185886397595 13 0.063029728889586606 17 0.071060292197687266 19 0.074068640458598345 
		21 0.077176380676989537 23 0.082193240670424356 25 0.082193240670424356 27 0.074232185469931572 
		29 0.038694681139999999;
	setAttr -s 12 ".kit[0:11]"  10 3 3 9 9 9 9 9 
		9 9 9 10;
	setAttr -s 12 ".kot[0:11]"  10 3 3 9 9 9 9 9 
		9 9 9 10;
createNode animCurveTU -n "animCurveTU59";
	setAttr ".tan" 2;
	setAttr -s 15 ".ktv[0:14]"  0 0 3 0 5 0 7 0 9 0 11 0 13 0 15 0 17 0 
		19 0 21 0 23 0 25 0 27 0 29 0;
	setAttr -s 15 ".kit[0:14]"  10 2 2 2 2 2 2 2 
		2 2 2 2 2 2 2;
	setAttr -s 15 ".kot[0:14]"  10 2 2 2 2 2 2 2 
		2 2 2 2 2 2 2;
createNode animCurveTA -n "animCurveTA411";
	setAttr ".tan" 2;
	setAttr -s 15 ".ktv[0:14]"  0 0 3 0 5 3.5175762189999893 7 1.4547982280315015 
		9 -0.54718178786539695 11 -0.54718178786539884 13 -0.54718178786539751 15 -0.54718178786539651 
		17 -0.54718178786539651 19 -0.54718178786539906 21 -0.5471817878654035 23 -0.79658091670768449 
		25 -0.79658091670768449 27 -0.79658091670768905 29 3.5175762189999893;
	setAttr -s 15 ".kit[0:14]"  10 2 2 2 2 2 2 2 
		2 2 2 2 2 2 2;
	setAttr -s 15 ".kot[0:14]"  10 2 2 2 2 2 2 2 
		2 2 2 2 2 2 2;
createNode animCurveTA -n "animCurveTA412";
	setAttr ".tan" 2;
	setAttr -s 15 ".ktv[0:14]"  0 0 3 -54.58951991 5 -14.219141980000018 
		7 -11.053085624536543 9 -7.098326354796459 11 -7.0983263547964546 13 -7.0983263547964732 
		15 -7.098326354796459 17 -7.098326354796459 19 -7.0983263547964572 21 -7.0983263547964564 
		23 -7.5387112001132488 25 -7.5387112001132488 27 -7.5387112001131857 29 -14.219141980000018;
	setAttr -s 15 ".kit[0:14]"  10 2 2 2 2 2 2 2 
		2 2 2 2 2 2 2;
	setAttr -s 15 ".kot[0:14]"  10 2 2 2 2 2 2 2 
		2 2 2 2 2 2 2;
createNode animCurveTA -n "animCurveTA413";
	setAttr ".tan" 2;
	setAttr -s 15 ".ktv[0:14]"  0 0 3 0 5 83.127441637463875 7 54.859724153162702 
		9 13.797624247056049 11 -42.201650949421619 13 -33.912530782017825 15 -1.2271330787571406 
		17 -1.2271330787571406 19 47.970048318776726 21 89.668068893106792 23 120.10257702716652 
		25 120.10257702716652 27 87.593307522536676 29 83.127441637463875;
	setAttr -s 15 ".kit[0:14]"  10 2 2 2 2 2 2 2 
		2 2 2 2 2 2 2;
	setAttr -s 15 ".kot[0:14]"  10 2 2 2 2 2 2 2 
		2 2 2 2 2 2 2;
createNode animCurveTL -n "animCurveTL352";
	setAttr ".tan" 2;
	setAttr -s 15 ".ktv[0:14]"  0 0 3 -0.24521214450000001 5 0.058774832812705541 
		7 0.3861196457080327 9 1.0924044398940915 11 1.739238052233228 13 2.0925349258201633 
		15 2.3229615309506375 17 2.3229615309506375 19 2.4741645490613031 21 2.687945093563846 
		23 3.0906526496845106 25 3.5962240852318867 27 4.0704085608811127 29 4.6188156956192197;
	setAttr -s 15 ".kit[0:14]"  10 2 2 2 2 2 2 2 
		2 2 2 2 2 2 2;
	setAttr -s 15 ".kot[0:14]"  10 2 2 2 2 2 2 2 
		2 2 2 2 2 2 2;
createNode animCurveTL -n "animCurveTL353";
	setAttr ".tan" 2;
	setAttr -s 14 ".ktv[0:13]"  0 0 3 0 5 0.20473124024750611 9 0.34948439161748956 
		11 0.30594242049696657 13 0.1298815386012333 15 -0.0019513352157739527 17 -0.0019513352157739527 
		19 0.10324426905627659 21 0.28638173206629502 23 0.47028975749399576 25 0.46026687729943322 
		27 0.20619967356616431 29 0.20473124024750611;
	setAttr -s 14 ".kit[0:13]"  10 2 2 2 2 2 2 2 
		2 2 2 2 2 2;
	setAttr -s 14 ".kot[0:13]"  10 2 2 2 2 2 2 2 
		2 2 2 2 2 2;
createNode animCurveTL -n "animCurveTL354";
	setAttr ".tan" 2;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 -0.036492834949999997 5 -0.065952047289999996 
		11 -0.0082322708610689799 13 0.0074447054529616641 15 0.023121681766992308 17 0.023121681766992308 
		27 -0.051106425780501286 29 -0.065952047289999996;
	setAttr -s 9 ".kit[0:8]"  10 2 2 2 2 2 2 2 
		2;
	setAttr -s 9 ".kot[0:8]"  10 2 2 2 2 2 2 2 
		2;
createNode animCurveTU -n "animCurveTU60";
	setAttr ".tan" 2;
	setAttr -s 15 ".ktv[0:14]"  0 0 3 0 5 0 7 0 9 0 11 0 13 0 15 0 17 0 
		19 0 21 0 23 0 25 0 27 0 29 0;
	setAttr -s 15 ".kit[0:14]"  10 2 2 2 2 2 2 2 
		2 2 2 2 2 2 2;
	setAttr -s 15 ".kot[0:14]"  10 2 2 2 2 2 2 2 
		2 2 2 2 2 2 2;
createNode animCurveTA -n "animCurveTA414";
	setAttr ".tan" 2;
	setAttr -s 15 ".ktv[0:14]"  0 0 3 0 5 0 7 2.0519261047902111 9 2.0519261047902093 
		11 2.051926104790208 13 2.0519261047902186 15 2.0519261047902284 17 2.0519261047902546 
		19 2.0519261047902528 21 0.1221869962347097 23 2.3132150721657849 25 2.3132150721657849 
		27 0 29 0;
	setAttr -s 15 ".kit[0:14]"  10 2 2 2 2 2 2 2 
		2 2 2 2 2 2 2;
	setAttr -s 15 ".kot[0:14]"  10 2 2 2 2 2 2 2 
		2 2 2 2 2 2 2;
createNode animCurveTA -n "animCurveTA415";
	setAttr ".tan" 2;
	setAttr -s 15 ".ktv[0:14]"  0 0 3 -11.15749273 5 4.978760523 7 6.972484576966635 
		9 6.9724845769666359 11 6.9724845769666404 13 6.9724845769666812 15 6.9724845769666848 
		17 6.9724845769667034 19 6.9724845769667034 21 6.1514980372543668 23 6.4537397086063217 
		25 6.4537397086063235 27 4.978760523 29 4.978760523;
	setAttr -s 15 ".kit[0:14]"  10 2 2 2 2 2 2 2 
		2 2 2 2 2 2 2;
	setAttr -s 15 ".kot[0:14]"  10 2 2 2 2 2 2 2 
		2 2 2 2 2 2 2;
createNode animCurveTA -n "animCurveTA416";
	setAttr ".tan" 2;
	setAttr -s 15 ".ktv[0:14]"  0 0 3 0 5 0 7 52.749328211865681 9 92.599629883063145 
		11 120.07406274327977 13 123.05346956470243 15 90.084275193715172 17 88.639195451149391 
		19 51.414198207867742 21 15.364124914679229 23 -40.031785418278943 25 -34.596666560105866 
		27 0 29 0;
	setAttr -s 15 ".kit[0:14]"  10 2 2 2 2 2 2 2 
		2 2 2 2 2 2 2;
	setAttr -s 15 ".kot[0:14]"  10 2 2 2 2 2 2 2 
		2 2 2 2 2 2 2;
createNode animCurveTL -n "animCurveTL355";
	setAttr ".tan" 2;
	setAttr -s 15 ".ktv[0:14]"  0 0 3 0.27390489299999998 5 0.041069818680000002 
		7 0.19129377059366814 9 0.41145185135993589 11 0.83166744062748954 13 1.3253572817941328 
		15 1.9627871198280684 17 2.4045241699764697 19 2.7927219296572789 21 3.3709323004029232 
		23 4.0202316653532257 25 4.3531059638301297 27 4.6019165503560435 29 4.6011106814865146;
	setAttr -s 15 ".kit[0:14]"  10 2 2 2 2 2 2 2 
		2 2 2 2 2 2 2;
	setAttr -s 15 ".kot[0:14]"  10 2 2 2 2 2 2 2 
		2 2 2 2 2 2 2;
createNode animCurveTL -n "animCurveTL356";
	setAttr ".tan" 2;
	setAttr -s 14 ".ktv[0:13]"  0 0 3 0 5 -1.2463030880000001e-017 7 0.097797774118697722 
		9 0.28211483571887191 11 0.46023653267459541 13 0.45158538505776685 15 0.2063821985764237 
		17 0.18209136175919272 21 0.35021648189067378 23 0.33209598883348646 25 0.1236671330997588 
		27 -1.2463030880000001e-017 29 -1.2463030880000001e-017;
	setAttr -s 14 ".kit[0:13]"  10 2 2 2 2 2 2 2 
		2 2 2 2 2 2;
	setAttr -s 14 ".kot[0:13]"  10 2 2 2 2 2 2 2 
		2 2 2 2 2 2;
createNode animCurveTL -n "animCurveTL357";
	setAttr ".tan" 2;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0.090348287870000002 5 -0.015449325430000001 
		7 -0.012661299264365669 17 0.061211504800495975 23 0.011401461557439332 25 -0.0020239319362803324 
		27 -0.015449325430000001 29 -0.015449325430000001;
	setAttr -s 9 ".kit[0:8]"  10 2 2 2 2 2 2 2 
		2;
	setAttr -s 9 ".kot[0:8]"  10 2 2 2 2 2 2 2 
		2;
createNode animCurveTA -n "animCurveTA417";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 -3.5135950739999999 5 0.16417887580000001 
		9 -4.1390783469424388 17 -0.64549732328461673 21 1.089061586547023 29 0.16417887580000001;
	setAttr -s 7 ".kit[4:6]"  9 10 10;
	setAttr -s 7 ".kot[4:6]"  9 10 10;
createNode animCurveTA -n "animCurveTA418";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 -41.506005369999997 5 -0.89806840369999985 
		9 7.4650678160608708 17 1.2577262725683649 21 -7.5578028954404317 29 -0.89806840369999985;
	setAttr -s 7 ".kit[2:6]"  1 9 1 9 10;
	setAttr -s 7 ".kot[2:6]"  1 9 1 9 10;
	setAttr -s 7 ".kix[2:6]"  0.10525605082511902 0.13333331048488617 
		0.26017928123474121 0.13333332538604736 0.26666665077209473;
	setAttr -s 7 ".kiy[2:6]"  0.13725113868713379 0.012541903182864189 
		-0.33190268278121948 -0.012541905045509338 0.11623429507017136;
	setAttr -s 7 ".kox[2:6]"  0.17192995548248291 0.26666668057441711 
		0.12684698402881622 0.26666668057441711 0.26666665077209473;
	setAttr -s 7 ".koy[2:6]"  0.22419224679470062 0.025083811953663826 
		-0.16181482374668121 -0.025083811953663826 0.11623429507017136;
createNode animCurveTA -n "animCurveTA419";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 6.8742004950000011 5 9.2245249210000004 
		9 12.052048331041901 17 10.075689281073467 21 11.844039130518112 29 9.2245249210000004;
	setAttr -s 7 ".kit[2:6]"  9 10 10 10 10;
	setAttr -s 7 ".kot[2:6]"  9 10 10 10 10;
createNode animCurveTL -n "animCurveTL358";
	setAttr ".tan" 10;
	setAttr -s 15 ".ktv[0:14]"  0 0 3 -0.069817337130000004 5 0.092974324309999995 
		7 0.4328390412310269 9 0.8206728583480597 11 1.2353862469484513 13 1.615540186498811 
		15 1.9803343709158221 17 2.3596627637584193 19 2.7108261912055278 21 3.0940643921127076 
		23 3.5102896540860336 25 3.8941774884766254 27 4.2515848389447441 29 4.6530151871165133;
createNode animCurveTL -n "animCurveTL359";
	setAttr ".tan" 10;
	setAttr -s 15 ".ktv[0:14]"  0 0 3 -0.027984753590000001 5 -0.050866970318222668 
		7 0.029914525027562783 9 0.12591299461098673 11 0.12591299461098673 13 -0.016164740372480474 
		15 -0.079569880348423799 17 -0.047625830461023241 19 0.03298679160866172 21 0.12844556402747667 
		23 0.12597597299179644 25 -0.015548157914521771 27 -0.080572532104515066 29 -0.050866970318222668;
	setAttr -s 15 ".kit[4:14]"  9 9 10 10 9 10 9 9 
		10 10 10;
	setAttr -s 15 ".kot[4:14]"  9 9 10 10 9 10 9 9 
		10 10 10;
createNode animCurveTL -n "animCurveTL360";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 -0.0066899853300000003 5 -0.00080738288230000003 
		9 -0.0077045252266192601 17 0.0011175544427630395 21 0.00858276333886758 29 -0.00080738288230000003;
	setAttr -s 7 ".kit[2:6]"  1 10 1 10 10;
	setAttr -s 7 ".kot[2:6]"  1 10 1 10 10;
	setAttr -s 7 ".kix[2:6]"  0.050817970186471939 0.13333332538604736 
		0.25524431467056274 0.13333332538604736 0.26666665077209473;
	setAttr -s 7 ".kiy[2:6]"  -0.0039785387925803661 0 0.022466277703642845 
		0 0;
	setAttr -s 7 ".kox[2:6]"  0.10163587331771851 0.26666665077209473 
		0.12762212753295898 0.26666665077209473 0.26666665077209473;
	setAttr -s 7 ".koy[2:6]"  -0.0079570738598704338 0 0.011233142577111721 
		0 0;
createNode animCurveTA -n "animCurveTA420";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 -17.82399672 5 -9.8206484540000005 
		11 -33.84885438002793 17 -14.867158121458241 23 -9.820648454000013 29 -9.8206484540000005;
createNode animCurveTA -n "animCurveTA421";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 -10.43459315 5 -10.12469553 11 -16.765081275265835 
		17 -12.678162540620892 23 -10.124695530000006 29 -10.12469553;
	setAttr -s 7 ".kit[4:6]"  9 10 10;
	setAttr -s 7 ".kot[4:6]"  9 10 10;
createNode animCurveTA -n "animCurveTA422";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 2.4451474769999999 5 -0.1383780527 
		11 30.033475473477601 17 0.74816180885504202 23 -20.395418327583233 29 -0.1383780527;
	setAttr -s 7 ".kit[2:6]"  1 10 10 10 10;
	setAttr -s 7 ".kot[2:6]"  1 10 10 10 10;
	setAttr -s 7 ".kix[2:6]"  0.040924295783042908 0.20000000298023224 
		0.20000000298023224 0.19999998807907104 0.19999997317790985;
	setAttr -s 7 ".kiy[2:6]"  0.090067051351070404 0.0077365199103951454 
		-0.44007512927055359 -0.0077365199103951454 0.35355204343795776;
	setAttr -s 7 ".kox[2:6]"  0.17425119876861572 0.19999998807907104 
		0.20000000298023224 0.20000000298023224 0.19999997317790985;
	setAttr -s 7 ".koy[2:6]"  0.38349571824073792 0.0077365194447338581 
		-0.44007512927055359 -0.0077365203760564327 0.35355204343795776;
createNode animCurveTA -n "animCurveTA423";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 9.6921754187547098 11 1.2005820575340533 
		17 9.6921754187547098 23 0.58929061196348864 29 9.6921754187547098;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTA -n "animCurveTA424";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 8.810063617344392 11 -6.4315866638983303 
		17 3.6133029711653628 23 13.365596750117005 29 8.810063617344392;
createNode animCurveTA -n "animCurveTA425";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 23.265079145375779 11 -27.065717620153116 
		17 23.265079145375779 23 59.660084837642323 29 23.265079145375779;
createNode animCurveTL -n "animCurveTL361";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -0.040210713659284476 11 -0.040210713659284476 
		17 -0.040210713659284476 23 -0.040210713659284476 29 -0.040210713659284476;
createNode animCurveTL -n "animCurveTL362";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -0.92172394262998947 11 -0.92172394262998947 
		17 -0.92172394262998947 23 -0.92172394262998947 29 -0.92172394262998947;
createNode animCurveTL -n "animCurveTL363";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 0.020592262861709541 11 0.020592262861709541 
		17 0.020592262861709541 23 0.020592262861709541 29 0.020592262861709541;
createNode animCurveTA -n "animCurveTA426";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -10.814320486728878 9 -15.34689834904758 
		17 0.41226215882945244 21 6.7101889336323923 29 -10.814320486728878;
createNode animCurveTA -n "animCurveTA427";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -3.7464163230089 9 -6.9271660479245405 
		17 -10.956886956011886 21 -11.991364640558491 29 -3.7464163230089;
	setAttr -s 5 ".kit[1:4]"  9 9 10 10;
	setAttr -s 5 ".kot[1:4]"  9 9 10 10;
createNode animCurveTA -n "animCurveTA428";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -10.897220128485484 9 -6.1638027297161591 
		17 -2.5610341209434981 21 -3.5950671111978365 29 -10.897220128485484;
	setAttr -s 5 ".kit[3:4]"  9 10;
	setAttr -s 5 ".kot[3:4]"  9 10;
createNode animCurveTA -n "animCurveTA429";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 0.72504957116732272;
createNode animCurveTA -n "animCurveTA430";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 -16.065060266995822;
createNode animCurveTA -n "animCurveTA431";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 -1.8244965449281254;
createNode animCurveTA -n "animCurveTA432";
	setAttr ".tan" 9;
	setAttr -s 13 ".ktv[0:12]"  5 -5.0566276381482984 7 -3.484518970038049 
		9 -1.7937325371110211 11 -3.2452544650281228 13 -6.8537504772041897 15 -10.930910870569081 
		17 -12.001901607532574 19 -5.0566276381483037 21 0.97005571510351507 23 2.5768587555432578 
		25 -0.0096185152862375157 27 -3.0353450648636926 29 -5.0566276381482984;
	setAttr -s 13 ".kit[0:12]"  10 9 10 9 9 9 3 10 
		9 9 9 9 3;
	setAttr -s 13 ".kot[0:12]"  10 9 10 9 9 9 3 10 
		9 9 9 9 3;
createNode animCurveTA -n "animCurveTA433";
	setAttr ".tan" 10;
	setAttr -s 13 ".ktv[0:12]"  5 -17.107761286541351 7 -17.107761286541365 
		9 -18.008212833582718 11 -20.951715970465013 13 -16.431472878018401 15 -17.715810976305594 
		17 -18.418704892376471 19 -17.107761286541358 21 -19.640593605298388 23 -20.261397495760701 
		25 -13.705448160094347 27 -15.493612018158517 29 -17.107761286541351;
	setAttr -s 13 ".kit[2:12]"  9 10 9 9 10 10 9 9 
		10 9 10;
	setAttr -s 13 ".kot[2:12]"  9 10 9 9 10 10 9 9 
		10 9 10;
createNode animCurveTA -n "animCurveTA434";
	setAttr ".tan" 10;
	setAttr -s 13 ".ktv[0:12]"  5 -61.30467647456598 7 -63.917456850707573 
		9 -60.04450513170525 11 -52.755696860375139 13 -65.063047385231329 15 -66.428465192291029 
		17 -57.789475160489786 19 -63.354756609118873 21 -67.086176868146254 23 -63.338210125286402 
		25 -73.761610551488431 27 -75.573784783404221 29 -61.30467647456598;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 9 10 10 10 
		10 10 9 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 9 10 10 10 
		10 10 9 10 3;
createNode animCurveTL -n "animCurveTL364";
	setAttr ".tan" 10;
	setAttr -s 13 ".ktv[0:12]"  5 -0.011301811406185556 7 -0.011301811406185556 
		9 -0.011301811406185556 11 -0.011301811406185556 13 -0.011301811406185556 15 -0.011301811406185556 
		17 -0.011301811406185556 19 -0.011301811406185556 21 -0.011301811406185556 23 -0.011301811406185556 
		25 -0.011301811406185556 27 -0.011301811406185556 29 -0.011301811406185556;
createNode animCurveTL -n "animCurveTL365";
	setAttr ".tan" 10;
	setAttr -s 13 ".ktv[0:12]"  5 -0.0098431871193776898 7 -0.0098431871193776898 
		9 -0.0098431871193776898 11 -0.0098431871193776898 13 -0.0098431871193776898 15 -0.0098431871193776898 
		17 -0.0098431871193776898 19 -0.0098431871193776898 21 -0.0098431871193776898 23 
		-0.0098431871193776898 25 -0.0098431871193776898 27 -0.0098431871193776898 29 -0.0098431871193776898;
createNode animCurveTL -n "animCurveTL366";
	setAttr ".tan" 10;
	setAttr -s 13 ".ktv[0:12]"  5 -0.0040455390558233545 7 -0.0040455390558233545 
		9 -0.0040455390558233545 11 -0.0040455390558233545 13 -0.0040455390558233545 15 -0.0040455390558233545 
		17 -0.0040455390558233545 19 -0.0040455390558233545 21 -0.0040455390558233545 23 
		-0.0040455390558233545 25 -0.0040455390558233545 27 -0.0040455390558233545 29 -0.0040455390558233545;
createNode animCurveTU -n "animCurveTU61";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  5 3.7 29 3.7;
createNode animCurveTA -n "animCurveTA435";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 3 -9.124356938 5 -34.501494399870047 
		29 -34.501494399870047;
createNode animCurveTA -n "animCurveTA436";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 3 32.538509300000001 5 -5.0574945625248704 
		29 -5.0574945625248704;
createNode animCurveTA -n "animCurveTA437";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 3 66.319220920000006 5 44.186709870194484 
		29 44.186709870194484;
createNode animCurveTU -n "animCurveTU62";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  5 4.6000000000000005 29 4.6000000000000005;
createNode animCurveTA -n "animCurveTA438";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  5 -20.650249620961816 29 -20.650249620961816;
createNode animCurveTA -n "animCurveTA439";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 0;
createNode animCurveTA -n "animCurveTA440";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 0;
createNode animCurveTA -n "animCurveTA441";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 0;
createNode animCurveTL -n "animCurveTL367";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 0;
createNode animCurveTL -n "animCurveTL368";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 0;
createNode animCurveTL -n "animCurveTL369";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 0;
createNode animCurveTU -n "animCurveTU63";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 2.9000000000000004;
createNode animCurveTA -n "animCurveTA442";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 3 18.414671080000002 5 -12.69003685 
		29 -12.69003685;
createNode animCurveTA -n "animCurveTA443";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 3 31.007973249999999 5 -0.597753847 
		29 -0.597753847;
createNode animCurveTA -n "animCurveTA444";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0 3 76.036423780000007 5 16.792335510000001 
		29 16.792335510000001;
createNode animCurveTU -n "animCurveTU64";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 7.6000000000000005;
createNode animCurveTA -n "animCurveTA445";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 24.999999999999996;
createNode animCurveTL -n "Global_translateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  5 0 29 4.788;
createNode lightLinker -n "lightLinker1";
	setAttr -s 5 ".lnk";
	setAttr -s 5 ".slnk";
select -ne :time1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -l on ".o" 5;
select -ne :renderPartition;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -s 5 ".st";
select -ne :renderGlobalsList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
select -ne :defaultShaderList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -s 5 ".s";
select -ne :postProcessList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
select -ne :lightList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
select -ne :defaultTextureList1;
	setAttr -s 2 ".tx";
select -ne :lambert1;
	setAttr ".miic" -type "float3" 3.1415927 3.1415927 3.1415927 ;
select -ne :initialShadingGroup;
	addAttr -ci true -sn "materialIndex" -ln "materialIndex" -at "long";
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -k on ".mwc";
	setAttr ".ro" yes;
select -ne :initialParticleSE;
	addAttr -ci true -sn "materialIndex" -ln "materialIndex" -at "long";
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -k on ".mwc";
	setAttr ".ro" yes;
select -ne :defaultRenderGlobals;
	setAttr ".mcfr" 30;
	setAttr -k on ".esr";
	setAttr -l on ".bfs";
	setAttr -k on ".mbf";
	setAttr -k on ".frts";
select -ne :defaultResolution;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -av ".w" 320;
	setAttr -av ".h" 240;
	setAttr -k on ".off";
	setAttr -k on ".fld";
	setAttr -k on ".zsl";
select -ne :defaultLightSet;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -k on ".mwc";
	setAttr ".ro" yes;
select -ne :hardwareRenderGlobals;
	addAttr -ci true -sn "ani" -ln "animation" -bt "ANIM" -min 0 -max 1 -at "bool";
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr ".enpt" no;
	setAttr ".hgcd" no;
	setAttr ".hgci" no;
	setAttr ".hwfr" 30;
	setAttr -k on ".ani" yes;
select -ne :characterPartition;
select -ne :defaultHardwareRenderGlobals;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr ".fn" -type "string" "im";
	setAttr ".res" -type "string" "ntsc_4d 646 485 1.333";
select -ne :ikSystem;
	setAttr -s 4 ".sol";
connectAttr "clip00Source.cl" "clipLibrary1.sc[0]";
connectAttr "animCurveTA393.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "animCurveTA394.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "animCurveTA395.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "animCurveTA396.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "animCurveTA397.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "animCurveTA398.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "animCurveTL319.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "animCurveTL320.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "animCurveTL321.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "animCurveTA399.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "animCurveTA400.a" "clipLibrary1.cel[0].cev[10].cevr";
connectAttr "animCurveTA401.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "animCurveTL322.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "animCurveTL323.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "animCurveTL324.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "animCurveTL325.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "animCurveTL326.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "animCurveTL327.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "animCurveTL328.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "animCurveTL329.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "animCurveTL330.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "animCurveTL331.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "animCurveTL332.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "animCurveTL333.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "animCurveTL334.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "animCurveTL335.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "animCurveTL336.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "animCurveTA402.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "animCurveTA403.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "animCurveTA404.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "animCurveTL337.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "animCurveTL338.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "animCurveTL339.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "animCurveTU57.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "animCurveTA405.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "animCurveTA406.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "animCurveTA407.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "animCurveTL340.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "animCurveTL341.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "animCurveTL342.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "animCurveTU58.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "animCurveTA408.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "animCurveTA409.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "animCurveTA410.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "animCurveTL343.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "animCurveTL344.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "animCurveTL345.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "animCurveTL346.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "animCurveTL347.a" "clipLibrary1.cel[0].cev[48].cevr";
connectAttr "animCurveTL348.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "animCurveTL349.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "animCurveTL350.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "animCurveTL351.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "animCurveTU59.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "animCurveTA411.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "animCurveTA412.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "animCurveTA413.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "animCurveTL352.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "animCurveTL353.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "animCurveTL354.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "animCurveTU60.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "animCurveTA414.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "animCurveTA415.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "animCurveTA416.a" "clipLibrary1.cel[0].cev[63].cevr";
connectAttr "animCurveTL355.a" "clipLibrary1.cel[0].cev[64].cevr";
connectAttr "animCurveTL356.a" "clipLibrary1.cel[0].cev[65].cevr";
connectAttr "animCurveTL357.a" "clipLibrary1.cel[0].cev[66].cevr";
connectAttr "animCurveTA417.a" "clipLibrary1.cel[0].cev[67].cevr";
connectAttr "animCurveTA418.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "animCurveTA419.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "animCurveTL358.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "animCurveTL359.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "animCurveTL360.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "animCurveTA420.a" "clipLibrary1.cel[0].cev[73].cevr";
connectAttr "animCurveTA421.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "animCurveTA422.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "animCurveTA423.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "animCurveTA424.a" "clipLibrary1.cel[0].cev[77].cevr";
connectAttr "animCurveTA425.a" "clipLibrary1.cel[0].cev[78].cevr";
connectAttr "animCurveTL361.a" "clipLibrary1.cel[0].cev[79].cevr";
connectAttr "animCurveTL362.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "animCurveTL363.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "animCurveTA426.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "animCurveTA427.a" "clipLibrary1.cel[0].cev[83].cevr";
connectAttr "animCurveTA428.a" "clipLibrary1.cel[0].cev[84].cevr";
connectAttr "animCurveTA429.a" "clipLibrary1.cel[0].cev[85].cevr";
connectAttr "animCurveTA430.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "animCurveTA431.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "animCurveTA432.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "animCurveTA433.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr "animCurveTA434.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "animCurveTL364.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "animCurveTL365.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "animCurveTL366.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "animCurveTU61.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "animCurveTA435.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "animCurveTA436.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "animCurveTA437.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "animCurveTU62.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "animCurveTA438.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "animCurveTA439.a" "clipLibrary1.cel[0].cev[100].cevr";
connectAttr "animCurveTA440.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "animCurveTA441.a" "clipLibrary1.cel[0].cev[102].cevr";
connectAttr "animCurveTL367.a" "clipLibrary1.cel[0].cev[103].cevr";
connectAttr "animCurveTL368.a" "clipLibrary1.cel[0].cev[104].cevr";
connectAttr "animCurveTL369.a" "clipLibrary1.cel[0].cev[105].cevr";
connectAttr "animCurveTU63.a" "clipLibrary1.cel[0].cev[106].cevr";
connectAttr "animCurveTA442.a" "clipLibrary1.cel[0].cev[107].cevr";
connectAttr "animCurveTA443.a" "clipLibrary1.cel[0].cev[108].cevr";
connectAttr "animCurveTA444.a" "clipLibrary1.cel[0].cev[109].cevr";
connectAttr "animCurveTU64.a" "clipLibrary1.cel[0].cev[110].cevr";
connectAttr "animCurveTA445.a" "clipLibrary1.cel[0].cev[111].cevr";
connectAttr "Global_translateY1.a" "clipLibrary1.cel[0].cev[115].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[3].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[3].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[4].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[4].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[5].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[5].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of move.ma
