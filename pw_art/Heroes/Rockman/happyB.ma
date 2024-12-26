//Maya ASCII 2008 scene
//Name: happyB.ma
//Last modified: Thu, Dec 24, 2009 02:43:49 PM
//Codeset: 1251
requires maya "2008";
requires "Mayatomr" "9.0.1.4m - 3.6.51.0 ";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Complete 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200802250025-718075";
fileInfo "osv" "Microsoft Windows XP Service Pack 3 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary2";
	setAttr -s 148 ".cel[0].cev";
	setAttr ".cd[0].cm" -type "characterMapping" 166 "R_arm_ctrl.fkIk" 0 1 "L_arm_ctrl.fkIk" 
		0 2 "R_upArm_fk_ctrl.rotateZ" 2 1 "R_upArm_fk_ctrl.rotateY" 2 
		2 "R_upArm_fk_ctrl.rotateX" 2 3 "R_elbow_fk_ctrl.rotateZ" 2 4 "R_wrist_fk_ctrl.rotateZ" 
		2 5 "R_wrist_fk_ctrl.rotateY" 2 6 "R_wrist_fk_ctrl.rotateX" 2 
		7 "R_shoulder_fk_ctrl.rotateZ" 2 8 "R_shoulder_fk_ctrl.rotateY" 2 
		9 "L_shoulder_fk_ctrl.rotateZ" 2 10 "L_shoulder_fk_ctrl.rotateY" 2 
		11 "L_upArm_fk_ctrl.rotateZ" 2 12 "L_upArm_fk_ctrl.rotateY" 2 13 "L_upArm_fk_ctrl.rotateX" 
		2 14 "L_elbow_fk_ctrl.rotateZ" 2 15 "L_wrist_fk_ctrl.rotateZ" 2 
		16 "L_wrist_fk_ctrl.rotateY" 2 17 "L_wrist_fk_ctrl.rotateX" 2 18 "M_neck_fk_ctrl.rotateZ" 
		2 19 "M_neck_fk_ctrl.rotateY" 2 20 "M_neck_fk_ctrl.rotateX" 2 
		21 "M_head_fk_ctrl.rotateZ" 2 22 "M_head_fk_ctrl.rotateY" 2 23 "M_head_fk_ctrl.rotateX" 
		2 24 "R_leg_kneeIk_ctrl.translateZ" 1 1 "R_leg_kneeIk_ctrl.translateY" 
		1 2 "R_leg_kneeIk_ctrl.translateX" 1 3 "L_leg_kneeIk_ctrl.translateZ" 
		1 4 "L_leg_kneeIk_ctrl.translateY" 1 5 "L_leg_kneeIk_ctrl.translateX" 
		1 6 "com_ctrl.rotateZ" 2 25 "com_ctrl.rotateY" 2 26 "com_ctrl.rotateX" 
		2 27 "com_ctrl.translateZ" 1 7 "com_ctrl.translateY" 1 8 "com_ctrl.translateX" 
		1 9 "R_foot_ctrl.rotateZ" 2 28 "R_foot_ctrl.rotateY" 2 29 "R_foot_ctrl.rotateX" 
		2 30 "R_foot_ctrl.translateZ" 1 10 "R_foot_ctrl.translateY" 1 
		11 "R_foot_ctrl.translateX" 1 12 "L_foot_ctrl.rotateZ" 2 31 "L_foot_ctrl.rotateY" 
		2 32 "L_foot_ctrl.rotateX" 2 33 "L_foot_ctrl.translateZ" 1 
		13 "L_foot_ctrl.translateY" 1 14 "L_foot_ctrl.translateX" 1 15 "R_mace_ctrl.parent" 
		0 3 "R_mace_ctrl.rotateZ" 2 34 "R_mace_ctrl.rotateY" 2 35 "R_mace_ctrl.rotateX" 
		2 36 "R_mace_ctrl.translateZ" 1 16 "R_mace_ctrl.translateY" 1 
		17 "R_mace_ctrl.translateX" 1 18 "L_mace_ctrl.parent" 0 4 "L_mace_ctrl.rotateZ" 
		2 37 "L_mace_ctrl.rotateY" 2 38 "L_mace_ctrl.rotateX" 2 39 "L_mace_ctrl.translateZ" 
		1 19 "L_mace_ctrl.translateY" 1 20 "L_mace_ctrl.translateX" 1 
		21 "R_footRoll_ctrl.slide" 0 5 "R_footRoll_ctrl.clampHeel" 0 6 "R_footRoll_ctrl.clampToe" 
		0 7 "R_footRoll_ctrl.clampSideToSide" 0 8 "R_footRoll_ctrl.rotateY" 
		2 40 "R_footRoll_ctrl.rotateX" 2 41 "L_footRoll_ctrl.slide" 0 
		9 "L_footRoll_ctrl.clampHeel" 0 10 "L_footRoll_ctrl.clampToe" 0 
		11 "L_footRoll_ctrl.clampSideToSide" 0 12 "L_footRoll_ctrl.rotateY" 
		2 42 "L_footRoll_ctrl.rotateX" 2 43 "R_fingers_ctrl.mittenRoll" 
		0 13 "R_fingers_ctrl.indexRoll" 0 14 "R_fingers_ctrl.mittenC" 0 
		15 "R_fingers_ctrl.mittenB" 0 16 "R_fingers_ctrl.mittenA" 0 17 "R_fingers_ctrl.mittenSpread" 
		0 18 "R_fingers_ctrl.indexC" 0 19 "R_fingers_ctrl.indexB" 0 
		20 "R_fingers_ctrl.indexA" 0 21 "R_fingers_ctrl.indexSpread" 0 
		22 "R_fingers_ctrl.thumbB" 0 23 "R_fingers_ctrl.thumbA" 0 24 "R_fingers_ctrl.rotateZ" 
		2 44 "R_fingers_ctrl.rotateY" 2 45 "R_fingers_ctrl.rotateX" 2 
		46 "L_fingers_ctrl.mittenRoll" 0 25 "L_fingers_ctrl.indexRoll" 0 
		26 "L_fingers_ctrl.mittenC" 0 27 "L_fingers_ctrl.mittenB" 0 28 "L_fingers_ctrl.mittenA" 
		0 29 "L_fingers_ctrl.mittenSpread" 0 30 "L_fingers_ctrl.indexC" 
		0 31 "L_fingers_ctrl.indexB" 0 32 "L_fingers_ctrl.indexA" 0 
		33 "L_fingers_ctrl.indexSpread" 0 34 "L_fingers_ctrl.thumbB" 0 
		35 "L_fingers_ctrl.thumbA" 0 36 "L_fingers_ctrl.rotateZ" 2 47 "L_fingers_ctrl.rotateY" 
		2 48 "L_fingers_ctrl.rotateX" 2 49 "chest_ctrl.rotateZ" 2 
		50 "chest_ctrl.rotateY" 2 51 "chest_ctrl.rotateX" 2 52 "hips_ctrl.rotateZ" 
		2 53 "hips_ctrl.rotateY" 2 54 "hips_ctrl.rotateX" 2 55 "M_backCloth_ctrl.rotateZ" 
		2 56 "M_backCloth_ctrl.rotateY" 2 57 "M_backCloth_ctrl.rotateX" 
		2 58 "M_hang_ctrl.rotateZ" 2 59 "M_hang_ctrl.rotateY" 2 60 "M_hang_ctrl.rotateX" 
		2 61 "R_hang_ctrl.rotateZ" 2 62 "R_hang_ctrl.rotateY" 2 63 "R_hang_ctrl.rotateX" 
		2 64 "L_hang_ctrl.rotateZ" 2 65 "L_hang_ctrl.rotateY" 2 66 "L_hang_ctrl.rotateX" 
		2 67 "R_flag_3_ctrl.rotateZ" 2 68 "R_flag_3_ctrl.rotateY" 2 
		69 "R_flag_3_ctrl.rotateX" 2 70 "R_flag_2_ctrl.rotateZ" 2 71 "R_flag_2_ctrl.rotateY" 
		2 72 "R_flag_2_ctrl.rotateX" 2 73 "R_flag_1_ctrl.rotateZ" 2 
		74 "R_flag_1_ctrl.rotateY" 2 75 "R_flag_1_ctrl.rotateX" 2 76 "L_flag_1_ctrl.rotateZ" 
		2 77 "L_flag_1_ctrl.rotateY" 2 78 "L_flag_1_ctrl.rotateX" 2 
		79 "L_flag_2_ctrl.rotateZ" 2 80 "L_flag_2_ctrl.rotateY" 2 81 "L_flag_2_ctrl.rotateX" 
		2 82 "L_flag_3_ctrl.rotateZ" 2 83 "L_flag_3_ctrl.rotateY" 2 
		84 "L_flag_3_ctrl.rotateX" 2 85 "M_backFeature_ctrl.rotateZ" 2 
		86 "M_backFeature_ctrl.rotateY" 2 87 "M_backFeature_ctrl.rotateX" 2 
		88 "M_frontCloth_ctrl.rotateZ" 2 89 "M_frontCloth_ctrl.rotateY" 2 
		90 "M_frontCloth_ctrl.rotateX" 2 91 "R_arm_elbowIk_ctrl.translateZ" 
		1 22 "R_arm_elbowIk_ctrl.translateY" 1 23 "R_arm_elbowIk_ctrl.translateX" 
		1 24 "L_arm_elbowIk_ctrl.translateZ" 1 25 "L_arm_elbowIk_ctrl.translateY" 
		1 26 "L_arm_elbowIk_ctrl.translateX" 1 27 "L_wrist_ik_ctrl.rotateZ" 
		2 92 "L_wrist_ik_ctrl.rotateY" 2 93 "L_wrist_ik_ctrl.rotateX" 2 
		94 "L_wrist_ik_ctrl.translateZ" 1 28 "L_wrist_ik_ctrl.translateY" 1 
		29 "L_wrist_ik_ctrl.translateX" 1 30 "R_wrist_ik_ctrl.rotateZ" 2 
		95 "R_wrist_ik_ctrl.rotateY" 2 96 "R_wrist_ik_ctrl.rotateX" 2 97 "R_wrist_ik_ctrl.translateZ" 
		1 31 "R_wrist_ik_ctrl.translateY" 1 32 "R_wrist_ik_ctrl.translateX" 
		1 33  ;
	setAttr ".cd[0].cim" -type "Int32Array" 166 0 1 2 3 4
		 5 6 7 8 9 10 11 12 13 14 15 16
		 17 18 19 20 21 22 23 24 25 26 27 28
		 29 30 31 32 33 34 35 36 37 38 39 40
		 41 42 43 44 45 46 47 48 49 50 51 52
		 53 54 55 56 57 58 59 60 61 62 63 64
		 65 66 67 68 69 70 71 72 73 74 75 76
		 77 78 79 80 81 82 83 84 85 86 87 88
		 89 90 91 92 93 94 95 96 97 98 99 100
		 101 102 103 104 105 106 107 108 109 110 111 112
		 113 114 115 116 117 118 119 120 121 122 123 124
		 125 126 127 128 129 130 131 132 133 134 135 136
		 137 138 139 140 141 142 143 144 145 146 147 148
		 149 150 151 152 153 154 155 156 157 158 159 160
		 161 162 163 164 165 ;
createNode animClip -n "happyBSource2";
	setAttr ".ihi" 0;
	setAttr -s 148 ".ac[0:147]" no no yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes no no no no no no yes 
		yes yes no no no yes yes yes no no no yes yes yes no no no no yes yes yes no no no 
		no yes yes yes no no no no no no no yes yes no no no no yes yes no no no no no no 
		no no no no no no yes yes yes no no no no no no no no no no no no yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".se" 70;
	setAttr ".ci" no;
createNode animCurveTU -n "animCurveTU498";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "animCurveTU499";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTA -n "animCurveTA1255";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -16.433008012612902 5 -20.931085008783658 
		8 -45.666664653765444 12 -11.675113442933807 24 1.7025651857481585 30 -5.8785005780448474 
		35 1.7025651857481585 40 -11.791215034168086 54 -23.46216587113593 70 -16.433008012612902;
	setAttr -s 10 ".kit[9]"  3;
	setAttr -s 10 ".kot[9]"  3;
createNode animCurveTA -n "animCurveTA1256";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 46.484153693874759 5 45.718577105720065 
		8 -7.2591978264589159 12 -36.580927859990474 24 -25.122054040618497 30 -50.63639224857355 
		35 -25.122054040618497 40 -32.460200861731508 54 49.938166588409139 70 46.484153693874759;
createNode animCurveTA -n "animCurveTA1257";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -14.962212153601083 5 25.399592325307911 
		8 25.273996362228399 12 -59.765002859466804 24 -74.615512849276541 30 -72.652658120287953 
		35 -74.615512849276541 40 -68.016226920049675 54 -7.9926221456671396 70 -14.962212153601083;
	setAttr -s 10 ".kit[9]"  3;
	setAttr -s 10 ".kot[9]"  3;
createNode animCurveTA -n "animCurveTA1258";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -22.136766656027952 5 -63.537804605254834 
		8 -64.826936797881203 12 -30.989042214626689 24 -55.355493245142448 30 -22.665487273640398 
		35 -55.355493245142448 40 -30.989042214626689 54 -29.169698473390145 70 -22.136766656027952;
	setAttr -s 10 ".kit[1:9]"  9 9 10 10 10 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  9 9 10 10 10 10 10 10 
		3;
createNode animCurveTA -n "tank_R_wrist_fk_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTA -n "tank_R_wrist_fk_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTA -n "tank_R_wrist_fk_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTA -n "animCurveTA1259";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -9.982335324211336 5 -31.908217326871881 
		8 -25.732818489103384 12 -10.395727317297833 40 -10.395727317297833 54 -9.982335324211336 
		70 -9.982335324211336;
createNode animCurveTA -n "animCurveTA1260";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 15.766648207086439 5 -3.6911177551532353 
		8 -22.844445698547375 12 -51.130278468654915 40 -51.130278468654915 54 15.766648207086439 
		70 15.766648207086439;
createNode animCurveTA -n "animCurveTA1261";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -4.5415548635099237 5 -37.967715495250388 
		8 -38.250592147433579 12 -31.362158481682041 40 -31.362158481682041 54 -4.5415548635099237 
		70 -4.5415548635099237;
createNode animCurveTA -n "animCurveTA1262";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.754519992899283 5 -3.3511867268748441 
		8 -13.023166362735161 12 -28.34747684907569 40 -28.34747684907569 54 1.754519992899283 
		70 1.754519992899283;
createNode animCurveTA -n "animCurveTA1263";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -25.378456988571386 5 -16.258751314626476 
		8 -42.522001806450476 12 -11.124395856637998 24 -2.2611600636525728 30 -5.8964797793793657 
		35 -2.2611600636525728 40 -12.636185066361799 54 -29.368927749225691 70 -25.378456988571386;
	setAttr -s 10 ".kit[4:9]"  9 10 10 10 10 3;
	setAttr -s 10 ".kot[4:9]"  9 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA1264";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 49.284082676870852 5 17.571869731331336 
		8 -15.044899188543454 12 -39.768045297738247 24 -22.491495227875944 30 -42.334411988074038 
		35 -22.491495227875944 40 -36.462354932924967 54 53.050330052915875 70 49.284082676870852;
createNode animCurveTA -n "animCurveTA1265";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 34.969087097535308 5 40.562466833095868 
		8 27.37231256193504 12 -59.366753548065745 24 -68.262720439615862 30 -69.001604050363127 
		35 -68.262720439615862 40 -56.947189922534236 54 33.828027019808161 70 34.969087097535308;
createNode animCurveTA -n "animCurveTA1266";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -4.2353230899544307 5 -75.76252537050577 
		8 -85.098973100090703 12 -15.96019624418668 24 -48.632690590121712 30 -18.232982568681376 
		35 -48.632690590121712 40 -15.96019624418668 54 -12.407413541234289 70 -4.2353230899544307;
	setAttr -s 10 ".kit[9]"  3;
	setAttr -s 10 ".kot[9]"  3;
createNode animCurveTA -n "tank_L_wrist_fk_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTA -n "tank_L_wrist_fk_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTA -n "tank_L_wrist_fk_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTA -n "animCurveTA1267";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 -7.8267770401379497 8 8.2254171082446952 
		12 37.252369900656717 40 37.252369900656717 54 12.921887482088605 70 0;
	setAttr -s 7 ".kit[6]"  3;
	setAttr -s 7 ".kot[6]"  3;
createNode animCurveTA -n "animCurveTA1268";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 3.6184647152117773 8 5.8891141873419794 
		12 8.9532339523918019 40 8.9532339523918019 54 7.5859922418110077 70 0;
	setAttr -s 7 ".kit[1:6]"  9 9 10 10 9 3;
	setAttr -s 7 ".kot[1:6]"  9 9 10 10 9 3;
createNode animCurveTA -n "animCurveTA1269";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 15.192507722648415 8 16.276275166380771 
		12 17.946079445283281 40 17.946079445283281 54 10.017778940039754 70 0;
	setAttr -s 7 ".kit[2:6]"  9 10 10 10 3;
	setAttr -s 7 ".kot[2:6]"  9 10 10 10 3;
createNode animCurveTA -n "animCurveTA1270";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -14.515820710620677 5 -14.515820710620677 
		8 -13.595835272687118 12 -11.328396849449989 40 -11.328396849449989 54 -14.515820710620677 
		70 -14.515820710620677;
createNode animCurveTA -n "animCurveTA1271";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -17.383598210882599 5 -17.383598210882599 
		8 -17.835592254425507 12 -18.531997735427183 40 -18.531997735427183 54 -17.383598210882599 
		70 -17.383598210882599;
createNode animCurveTA -n "animCurveTA1272";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.5268462968664711 5 1.5268462968664711 
		8 -0.86146472828055509 12 -6.7478057740091995 40 -6.7478057740091995 54 1.5268462968664711 
		70 1.5268462968664711;
createNode animCurveTL -n "animCurveTL457";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.00025694328101411035 5 0.00025694328101411035 
		8 0.00025694328101411035 12 0.00025694328101411035 40 0.00025694328101411035 54 0.00025694328101411035 
		70 0.00025694328101411035;
createNode animCurveTL -n "animCurveTL458";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTL -n "animCurveTL459";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.12527739251666781 5 -0.12527739251666781 
		8 -0.12527739251666781 12 -0.12527739251666781 40 -0.12527739251666781 54 -0.12527739251666781 
		70 -0.12527739251666781;
createNode animCurveTL -n "animCurveTL460";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.032833691772160223 5 0.032833691772160223 
		8 0.032833691772160223 12 0.032833691772160223 40 0.032833691772160223 54 0.032833691772160223 
		70 0.032833691772160223;
createNode animCurveTL -n "animCurveTL461";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.016062985925156426 5 -0.016062985925156426 
		8 -0.016062985925156426 12 -0.016062985925156426 40 -0.016062985925156426 54 -0.016062985925156426 
		70 -0.016062985925156426;
createNode animCurveTL -n "animCurveTL462";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.11728380015772394 5 0.11728380015772394 
		8 0.11728380015772394 12 0.11728380015772394 40 0.11728380015772394 54 0.11728380015772394 
		70 0.11728380015772394;
createNode animCurveTA -n "animCurveTA1273";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 3.7554037953221941 5 -1.5892797442962037 
		8 0.10735546802764266 12 4.2889605722040667 40 4.2842591079853811 44 3.4349014257478627 
		54 0 70 0;
	setAttr -s 9 ".kit[0:8]"  10 10 10 9 9 9 9 9 
		10;
	setAttr -s 9 ".kot[0:8]"  10 10 10 9 9 9 9 9 
		10;
createNode animCurveTA -n "animCurveTA1274";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 -2.7924230090955238 5 -1.3434367869480965 
		8 -2.0606568107714471 12 -3.1657066732865569 40 -1.6848755242522306 44 -1.3508476482373886 
		54 0 70 0;
	setAttr -s 9 ".kit[3:8]"  9 10 9 9 9 10;
	setAttr -s 9 ".kot[3:8]"  9 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1275";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 3.6719125695963681 2 -1.1475031874459765 
		5 -6.8843171684347411 8 -9.0387824355018047 12 -10.37571181182933 40 -10.26461919530235 
		44 -7.5016909923370116 54 3.6719125695963681 70 3.6719125695963681;
	setAttr -s 9 ".kit[0:8]"  10 10 9 9 9 9 9 10 
		10;
	setAttr -s 9 ".kot[0:8]"  10 10 9 9 9 9 9 10 
		10;
createNode animCurveTL -n "animCurveTL463";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.0319338039184065 2 -0.066781793561608127 
		5 -0.10219184432316104 8 -0.070285905080250649 12 -0.00053073584926333084 40 -0.014765641290912821 
		44 -0.020518550273000386 54 -0.043783984468856819 70 -0.0319338039184065;
	setAttr -s 9 ".kit[1:8]"  9 10 9 10 9 9 10 10;
	setAttr -s 9 ".kot[1:8]"  9 10 9 10 9 9 10 10;
createNode animCurveTL -n "animCurveTL464";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.00078859512199502824 2 0.047431628957756169 
		5 0.087607703303493017 8 0.060560119256262958 12 -0.0045832822108121483 40 -0.021080104135420673 
		44 -0.030386224856038521 54 -0.078191810178541779 70 0.00078859512199502824;
	setAttr -s 9 ".kit[0:8]"  10 9 10 9 9 9 9 10 
		3;
	setAttr -s 9 ".kot[0:8]"  10 9 10 9 9 9 9 10 
		3;
createNode animCurveTL -n "animCurveTL465";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 -0.031531823728716199 5 0.014169169386698528 
		8 0.022291591768731082 12 0.034806136034669498 40 -0.0026632417516791536 44 -0.049598124044160224 
		54 -0.0038073655253956073 70 0;
	setAttr -s 9 ".kit[2:8]"  9 9 10 9 10 9 10;
	setAttr -s 9 ".kot[2:8]"  9 9 10 9 10 9 10;
createNode animCurveTA -n "animCurveTA1276";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -16.236770139599834 5 -16.236770139599834 
		8 -16.236770139599834 12 -16.236770139599834 40 -16.236770139599834 54 -16.236770139599834 
		70 -16.236770139599834;
createNode animCurveTA -n "animCurveTA1277";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTA -n "animCurveTA1278";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTL -n "animCurveTL466";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -6.0000000000892673e-006 5 -6.0000000000892673e-006 
		8 -6.0000000000892673e-006 12 -6.0000000000892673e-006 40 -6.0000000000892673e-006 
		54 -6.0000000000892673e-006 70 -6.0000000000892673e-006;
createNode animCurveTL -n "animCurveTL467";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 2.1809999999936394e-005 5 2.1809999999936394e-005 
		8 2.1809999999936394e-005 12 2.1809999999936394e-005 40 2.1809999999936394e-005 54 
		2.1809999999936394e-005 70 2.1809999999936394e-005;
createNode animCurveTL -n "animCurveTL468";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.040093865534497591 5 -0.040093865534497591 
		8 -0.040093865534497591 12 -0.040093865534497591 40 -0.040093865534497591 54 -0.040093865534497591 
		70 -0.040093865534497591;
createNode animCurveTA -n "animCurveTA1279";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 25.000774638404387 2 26.522184281744554 
		5 25.000774638404387 8 25.000774638404387 12 25.000774638404387 40 25.000774638404387 
		44 27.011901369614197 48 25.000774638404387 54 25.000774638404387 70 25.000774638404387;
createNode animCurveTA -n "animCurveTA1280";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 -3.1159853875724122 5 0 8 0 12 0 
		40 0 44 -2.1840033542249468 48 0 54 0 70 0;
createNode animCurveTA -n "animCurveTA1281";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 9.7460813528318475 5 0 8 0 12 0 40 
		0 44 9.3345962759524088 48 0 54 0 70 0;
createNode animCurveTL -n "animCurveTL469";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0.057567548540586773 5 0 8 0 12 0 
		40 0 44 0.037620680685435101 48 0 54 0 70 0;
createNode animCurveTL -n "animCurveTL470";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0.068881450067331415 5 0.13887388839144554 
		8 0.13887388839144554 12 0.13887388839144554 40 0.13887388839144554 44 0.069436944195722772 
		48 0 54 0 70 0;
createNode animCurveTL -n "animCurveTL471";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.038258090963777358 2 0.038258090963777372 
		5 0.038258090963777393 8 0.038258090963777393 12 0.038258090963777393 40 0.038258090963777393 
		44 0.038258090963777372 48 0.038258090963777358 54 0.038258090963777358 70 0.038258090963777358;
createNode animCurveTU -n "animCurveTU500";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 5 1 8 1 12 1 40 1 54 1 70 1;
	setAttr -s 7 ".kot[0:6]"  5 5 5 5 5 5 5;
createNode animCurveTA -n "animCurveTA1282";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTA -n "animCurveTA1283";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTA -n "animCurveTA1284";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTL -n "animCurveTL472";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.808 5 -0.808 8 -0.808 12 -0.808 40 
		-0.808 54 -0.808 70 -0.808;
createNode animCurveTL -n "animCurveTL473";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTL -n "animCurveTL474";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "animCurveTU501";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 5 1 8 1 12 1 40 1 54 1 70 1;
	setAttr -s 7 ".kot[0:6]"  5 5 5 5 5 5 5;
createNode animCurveTA -n "animCurveTA1285";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTA -n "animCurveTA1286";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTA -n "animCurveTA1287";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTL -n "animCurveTL475";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.80789537837891157 5 -0.80789537837891157 
		8 -0.80789537837891157 12 -0.80789537837891157 40 -0.80789537837891157 54 -0.80789537837891157 
		70 -0.80789537837891157;
createNode animCurveTL -n "animCurveTL476";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTL -n "animCurveTL477";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_R_footRoll_ctrl_slide";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_R_footRoll_ctrl_clampHeel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 45 5 45 8 45 12 45 40 45 54 45 70 45;
createNode animCurveTU -n "tank_R_footRoll_ctrl_clampToe";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 45 5 45 8 45 12 45 40 45 54 45 70 45;
createNode animCurveTU -n "tank_R_footRoll_ctrl_clampSideToSide";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 45 5 45 8 45 12 45 40 45 54 45 70 45;
createNode animCurveTA -n "tank_R_footRoll_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTA -n "tank_R_footRoll_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_L_footRoll_ctrl_slide";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_L_footRoll_ctrl_clampHeel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 45 5 45 8 45 12 45 40 45 54 45 70 45;
createNode animCurveTU -n "tank_L_footRoll_ctrl_clampToe";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 45 5 45 8 45 12 45 40 45 54 45 70 45;
createNode animCurveTU -n "tank_L_footRoll_ctrl_clampSideToSide";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 45 5 45 8 45 12 45 40 45 54 45 70 45;
createNode animCurveTA -n "tank_L_footRoll_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTA -n "tank_L_footRoll_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_R_fingers_ctrl_mittenRoll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_R_fingers_ctrl_indexRoll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_R_fingers_ctrl_mittenC";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_R_fingers_ctrl_mittenB";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_R_fingers_ctrl_mittenA";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_R_fingers_ctrl_mittenSpread";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_R_fingers_ctrl_indexC";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_R_fingers_ctrl_indexB";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_R_fingers_ctrl_indexA";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_R_fingers_ctrl_indexSpread";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_R_fingers_ctrl_thumbB";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_R_fingers_ctrl_thumbA";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTA -n "tank_R_fingers_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTA -n "tank_R_fingers_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTA -n "tank_R_fingers_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_L_fingers_ctrl_mittenRoll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_L_fingers_ctrl_indexRoll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_L_fingers_ctrl_mittenC";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_L_fingers_ctrl_mittenB";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_L_fingers_ctrl_mittenA";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_L_fingers_ctrl_mittenSpread";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_L_fingers_ctrl_indexC";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_L_fingers_ctrl_indexB";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_L_fingers_ctrl_indexA";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_L_fingers_ctrl_indexSpread";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_L_fingers_ctrl_thumbB";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTU -n "tank_L_fingers_ctrl_thumbA";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTA -n "tank_L_fingers_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTA -n "tank_L_fingers_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTA -n "tank_L_fingers_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTA -n "animCurveTA1288";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -6.7832614176793165 5 -70.830566806931373 
		8 -24.240492861068102 12 8.6131161053332477 40 1.8746877263820785 54 4.6310180746467946 
		70 -6.7832614176793165;
createNode animCurveTA -n "animCurveTA1289";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 -0.97065730053662747 8 0.74514377807963006 
		12 -4.0714758662941453 40 -0.94910657932931042 54 -0.93563572272342865 70 0;
createNode animCurveTA -n "animCurveTA1290";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 -2.7442204613932706 8 2.5147138509327163 
		12 14.128657960158138 40 4.6593119991369596 54 -2.4919980547047156 70 0;
createNode animCurveTA -n "animCurveTA1291";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -17.428736070727251 5 -17.428736070727251 
		8 0 12 -17.428736070727251 40 -17.428736070727251 54 -17.428736070727251 70 -17.428736070727251;
createNode animCurveTA -n "animCurveTA1292";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTA -n "animCurveTA1293";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0 12 0 40 0 54 0 70 0;
createNode animCurveTA -n "tank_M_backCloth_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 -14.15404466973474 16 7.3844276697488826 
		30 -8.8506632265776819 42 5.1305957145331416 56 -8.513069363675724 70 0;
	setAttr -s 7 ".kit[6]"  3;
	setAttr -s 7 ".kot[6]"  3;
createNode animCurveTA -n "tank_M_backCloth_ctrl_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 1.2729602429702929 16 1.2220378728275221 
		30 1.1076166073240397 42 0.99191642756774456 56 0.78842941743983064 70 0;
	setAttr -s 7 ".kit[0:6]"  10 10 9 9 9 9 3;
	setAttr -s 7 ".kot[0:6]"  10 10 9 9 9 9 3;
createNode animCurveTA -n "tank_M_backCloth_ctrl_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0.96657162105612815 16 0.91361377567029856 
		30 0.84030746201242013 42 0.74278604348112365 56 0.6000868622917862 70 0;
	setAttr -s 7 ".kit[0:6]"  10 10 9 9 9 9 3;
	setAttr -s 7 ".kot[0:6]"  10 10 9 9 9 9 3;
createNode animCurveTA -n "tank_M_hang_ctrl_rotateZ3";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 9.1478457292549002 3 4.3706325431337998 
		6 51.666862301405189 11 32.874985474435945 15 -1.7620903923913918 18 -13.167439230549643 
		24 36.273424235686299 33 -8.062281729411902 41 27.500308362887488 45 15.540944406703353 
		49 0.91396553409723691 58 15.734164358090496 70 9.1478457292549002;
	setAttr -s 13 ".kit[12]"  3;
	setAttr -s 13 ".kot[12]"  3;
createNode animCurveTA -n "tank_M_hang_ctrl_rotateY3";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 6 -2.9231312541562819 15 8.6437399245011388 
		24 -12.739010916306151 33 10.115640233924672 41 -5.2331067993211304 45 13.76640755719308 
		49 12.175315776670526 58 -0.48737409711187446 70 0;
	setAttr -s 10 ".kit[6:9]"  9 9 10 3;
	setAttr -s 10 ".kot[6:9]"  9 9 10 3;
createNode animCurveTA -n "tank_M_hang_ctrl_rotateX3";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 6 -3.7961290221816761 15 4.4634931558691475 
		24 -7.4015757605162378 33 7.8728988517675695 41 3.4432162240376911 45 14.392545710441004 
		49 23.285278756023146 58 20.450937941150283 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 9 
		9 3;
createNode animCurveTA -n "tank_R_hang_ctrl_rotateZ3";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 9.1478457292549002 3 4.3706325431338184 
		6 51.666862301405189 11 32.874985474435945 15 -1.7620903923913918 18 -13.167439230549643 
		24 36.273424235686299 33 -8.062281729411902 41 27.500308362887488 45 15.540944406703353 
		49 0.91396553409723691 58 15.734164358090496 70 9.1478457292549002;
	setAttr -s 13 ".kit[9:12]"  9 10 10 3;
	setAttr -s 13 ".kot[9:12]"  9 10 10 3;
createNode animCurveTA -n "tank_R_hang_ctrl_rotateY3";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 6 -2.9231312541562819 15 8.6437399245011388 
		24 -12.739010916306151 33 10.115640233924672 41 -5.2331067993211304 45 13.76640755719308 
		49 12.175315776670526 58 -0.48737409711187446 70 0;
	setAttr -s 10 ".kit[6:9]"  9 9 10 3;
	setAttr -s 10 ".kot[6:9]"  9 9 10 3;
createNode animCurveTA -n "tank_R_hang_ctrl_rotateX3";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 6 -3.7961290221816761 15 4.4634931558691475 
		24 -7.4015757605162378 33 7.8728988517675695 41 3.4432162240376911 45 14.392545710441004 
		49 23.285278756023146 58 20.450937941150283 70 0;
	setAttr -s 10 ".kit[7:9]"  9 9 3;
	setAttr -s 10 ".kot[7:9]"  9 9 3;
createNode animCurveTA -n "tank_L_hang_ctrl_rotateZ3";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 9.1478457292549002 3 1.1107633331029119 
		6 51.666862301405189 11 33.14328745276422 15 -1.7620903923913918 18 -13.194957348584071 
		24 36.273424235686299 33 -8.062281729411902 41 27.500308362887488 45 15.540944406703353 
		49 0.91396553409723691 58 15.734164358090496 70 9.1478457292549002;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 10 10 10 10 
		10 10 10 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 10 10 10 10 
		10 10 10 10 3;
createNode animCurveTA -n "tank_L_hang_ctrl_rotateY3";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 6 -2.9231312541562819 15 8.6437399245011388 
		24 -12.739010916306151 33 10.115640233924672 41 -5.2331067993211304 45 13.76640755719308 
		49 12.175315776670526 58 -0.48737409711187446 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 9 9 
		10 3;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 9 9 
		10 3;
createNode animCurveTA -n "tank_L_hang_ctrl_rotateX3";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 6 -3.7961290221816761 15 4.4634931558691475 
		24 -7.4015757605162378 33 7.8728988517675695 41 3.4432162240376911 45 14.392545710441004 
		49 23.285278756023146 58 20.450937941150283 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		9 3;
createNode animCurveTA -n "animCurveTA1294";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1295";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1296";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1297";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1298";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1299";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1300";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1301";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1302";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1303";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1304";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1305";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1306";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1307";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1308";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1309";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1310";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1311";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "tank_M_backFeature_ctrl_rotateZ3";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -5.5312497278658954 6 -5.5312497278658954 
		10 18.988517043536309 14 3.3072247212436436 20 23.943270533015525 26 5.6721551688501419 
		32 10.823751724608824 46 10.823751724608824 60 -5.5312497278658954;
createNode animCurveTA -n "tank_M_backFeature_ctrl_rotateY3";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 10 -4.476400174749247 14 0.051416107673667187 
		20 -5.6866425839003032 26 -1.2213325766519743 32 -2.2495259253515361 46 -2.2495259253515361 
		60 0;
createNode animCurveTA -n "tank_M_backFeature_ctrl_rotateX3";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 10 0.49330949397369961 14 0.13716540142614203 
		20 0.31293111670053908 26 0.35838435778022809 32 0.44198421660487547 46 0.44198421660487547 
		60 0;
createNode animCurveTA -n "tank_M_frontCloth_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 -8.7602114092081749 14 10.142657246691165 
		26 -15.812196298299455 40 12.313856091376584 58 -2.721282019452627 70 0;
	setAttr -s 7 ".kit[6]"  3;
	setAttr -s 7 ".kot[6]"  3;
createNode animCurveTA -n "tank_M_frontCloth_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0.00010994219542429486 14 0.001126298225948105 
		26 0.00077988172346424864 40 0.0013239182701172696 58 -0.00051234271198760868 70 
		0;
	setAttr -s 7 ".kit[1:6]"  1 10 10 10 10 3;
	setAttr -s 7 ".kot[1:6]"  1 10 10 10 10 3;
	setAttr -s 7 ".kix[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".kiy[1:6]"  1.7806809410103597e-005 0 0 0 0 0;
	setAttr -s 7 ".kox[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".koy[1:6]"  1.780680577212479e-005 0 0 0 0 0;
createNode animCurveTA -n "tank_M_frontCloth_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0.0065464175822225563 14 -0.0075491048370122374 
		26 0.012513306924454808 40 -0.0096917685669503408 58 0.0036987997531891938 70 0;
	setAttr -s 7 ".kit[6]"  3;
	setAttr -s 7 ".kot[6]"  3;
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
	setAttr -s 4 ".u";
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
	setAttr -s 2 ".dsm";
	setAttr -k on ".mwc";
	setAttr -k on ".an";
	setAttr -k on ".il";
	setAttr -k on ".vo";
	setAttr -k on ".eo";
	setAttr -k on ".fo";
	setAttr -k on ".epo";
	setAttr ".ro" yes;
	setAttr -s 2 ".gn";
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
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -k on ".macc";
	setAttr -k on ".macd";
	setAttr -k on ".macq";
	setAttr ".mcfr" 30;
	setAttr -k on ".clip";
	setAttr -k on ".edm";
	setAttr -k on ".edl";
	setAttr -av -k on ".esr";
	setAttr -k on ".ors";
	setAttr -k on ".outf";
	setAttr -k on ".gama";
	setAttr -k on ".be";
	setAttr -k on ".fec";
	setAttr -k on ".ofc";
	setAttr -k on ".comp";
	setAttr -k on ".cth";
	setAttr -k on ".soll";
	setAttr -k on ".rd";
	setAttr -k on ".lp";
	setAttr -k on ".sp";
	setAttr -k on ".shs";
	setAttr -k on ".lpr";
	setAttr -k on ".mm";
	setAttr -k on ".npu";
	setAttr -k on ".itf";
	setAttr -k on ".shp";
	setAttr -k on ".uf";
	setAttr -k on ".oi";
	setAttr -k on ".rut";
	setAttr -av -k on ".mbf";
	setAttr -k on ".afp";
	setAttr -k on ".pfb";
	setAttr -av -k on ".bll";
	setAttr -k on ".bls";
	setAttr -k on ".smv";
	setAttr -k on ".ubc";
	setAttr -k on ".mbc";
	setAttr -k on ".udbx";
	setAttr -k on ".smc";
	setAttr -k on ".kmv";
	setAttr -k on ".rlen";
	setAttr -av -k on ".frts";
	setAttr -k on ".tlwd";
	setAttr -k on ".tlht";
	setAttr -k on ".jfc";
	setAttr -k on ".ope";
	setAttr -k on ".oppf";
select -ne :defaultResolution;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -av ".w";
	setAttr -av ".h";
	setAttr ".pa" 1;
	setAttr -k on ".al";
	setAttr -av ".dar";
	setAttr -k on ".off";
	setAttr -k on ".fld";
	setAttr -k on ".zsl";
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
select -ne :ikSystem;
	setAttr -s 2 ".sol";
connectAttr "happyBSource2.cl" "clipLibrary2.sc[0]";
connectAttr "animCurveTU498.a" "clipLibrary2.cel[0].cev[0].cevr";
connectAttr "animCurveTU499.a" "clipLibrary2.cel[0].cev[1].cevr";
connectAttr "animCurveTA1255.a" "clipLibrary2.cel[0].cev[2].cevr";
connectAttr "animCurveTA1256.a" "clipLibrary2.cel[0].cev[3].cevr";
connectAttr "animCurveTA1257.a" "clipLibrary2.cel[0].cev[4].cevr";
connectAttr "animCurveTA1258.a" "clipLibrary2.cel[0].cev[5].cevr";
connectAttr "tank_R_wrist_fk_ctrl_rotateZ.a" "clipLibrary2.cel[0].cev[6].cevr";
connectAttr "tank_R_wrist_fk_ctrl_rotateY.a" "clipLibrary2.cel[0].cev[7].cevr";
connectAttr "tank_R_wrist_fk_ctrl_rotateX.a" "clipLibrary2.cel[0].cev[8].cevr";
connectAttr "animCurveTA1259.a" "clipLibrary2.cel[0].cev[9].cevr";
connectAttr "animCurveTA1260.a" "clipLibrary2.cel[0].cev[10].cevr";
connectAttr "animCurveTA1261.a" "clipLibrary2.cel[0].cev[11].cevr";
connectAttr "animCurveTA1262.a" "clipLibrary2.cel[0].cev[12].cevr";
connectAttr "animCurveTA1263.a" "clipLibrary2.cel[0].cev[13].cevr";
connectAttr "animCurveTA1264.a" "clipLibrary2.cel[0].cev[14].cevr";
connectAttr "animCurveTA1265.a" "clipLibrary2.cel[0].cev[15].cevr";
connectAttr "animCurveTA1266.a" "clipLibrary2.cel[0].cev[16].cevr";
connectAttr "tank_L_wrist_fk_ctrl_rotateZ.a" "clipLibrary2.cel[0].cev[17].cevr";
connectAttr "tank_L_wrist_fk_ctrl_rotateY.a" "clipLibrary2.cel[0].cev[18].cevr";
connectAttr "tank_L_wrist_fk_ctrl_rotateX.a" "clipLibrary2.cel[0].cev[19].cevr";
connectAttr "animCurveTA1267.a" "clipLibrary2.cel[0].cev[20].cevr";
connectAttr "animCurveTA1268.a" "clipLibrary2.cel[0].cev[21].cevr";
connectAttr "animCurveTA1269.a" "clipLibrary2.cel[0].cev[22].cevr";
connectAttr "animCurveTA1270.a" "clipLibrary2.cel[0].cev[23].cevr";
connectAttr "animCurveTA1271.a" "clipLibrary2.cel[0].cev[24].cevr";
connectAttr "animCurveTA1272.a" "clipLibrary2.cel[0].cev[25].cevr";
connectAttr "animCurveTL457.a" "clipLibrary2.cel[0].cev[26].cevr";
connectAttr "animCurveTL458.a" "clipLibrary2.cel[0].cev[27].cevr";
connectAttr "animCurveTL459.a" "clipLibrary2.cel[0].cev[28].cevr";
connectAttr "animCurveTL460.a" "clipLibrary2.cel[0].cev[29].cevr";
connectAttr "animCurveTL461.a" "clipLibrary2.cel[0].cev[30].cevr";
connectAttr "animCurveTL462.a" "clipLibrary2.cel[0].cev[31].cevr";
connectAttr "animCurveTA1273.a" "clipLibrary2.cel[0].cev[32].cevr";
connectAttr "animCurveTA1274.a" "clipLibrary2.cel[0].cev[33].cevr";
connectAttr "animCurveTA1275.a" "clipLibrary2.cel[0].cev[34].cevr";
connectAttr "animCurveTL463.a" "clipLibrary2.cel[0].cev[35].cevr";
connectAttr "animCurveTL464.a" "clipLibrary2.cel[0].cev[36].cevr";
connectAttr "animCurveTL465.a" "clipLibrary2.cel[0].cev[37].cevr";
connectAttr "animCurveTA1276.a" "clipLibrary2.cel[0].cev[38].cevr";
connectAttr "animCurveTA1277.a" "clipLibrary2.cel[0].cev[39].cevr";
connectAttr "animCurveTA1278.a" "clipLibrary2.cel[0].cev[40].cevr";
connectAttr "animCurveTL466.a" "clipLibrary2.cel[0].cev[41].cevr";
connectAttr "animCurveTL467.a" "clipLibrary2.cel[0].cev[42].cevr";
connectAttr "animCurveTL468.a" "clipLibrary2.cel[0].cev[43].cevr";
connectAttr "animCurveTA1279.a" "clipLibrary2.cel[0].cev[44].cevr";
connectAttr "animCurveTA1280.a" "clipLibrary2.cel[0].cev[45].cevr";
connectAttr "animCurveTA1281.a" "clipLibrary2.cel[0].cev[46].cevr";
connectAttr "animCurveTL469.a" "clipLibrary2.cel[0].cev[47].cevr";
connectAttr "animCurveTL470.a" "clipLibrary2.cel[0].cev[48].cevr";
connectAttr "animCurveTL471.a" "clipLibrary2.cel[0].cev[49].cevr";
connectAttr "animCurveTU500.a" "clipLibrary2.cel[0].cev[50].cevr";
connectAttr "animCurveTA1282.a" "clipLibrary2.cel[0].cev[51].cevr";
connectAttr "animCurveTA1283.a" "clipLibrary2.cel[0].cev[52].cevr";
connectAttr "animCurveTA1284.a" "clipLibrary2.cel[0].cev[53].cevr";
connectAttr "animCurveTL472.a" "clipLibrary2.cel[0].cev[54].cevr";
connectAttr "animCurveTL473.a" "clipLibrary2.cel[0].cev[55].cevr";
connectAttr "animCurveTL474.a" "clipLibrary2.cel[0].cev[56].cevr";
connectAttr "animCurveTU501.a" "clipLibrary2.cel[0].cev[57].cevr";
connectAttr "animCurveTA1285.a" "clipLibrary2.cel[0].cev[58].cevr";
connectAttr "animCurveTA1286.a" "clipLibrary2.cel[0].cev[59].cevr";
connectAttr "animCurveTA1287.a" "clipLibrary2.cel[0].cev[60].cevr";
connectAttr "animCurveTL475.a" "clipLibrary2.cel[0].cev[61].cevr";
connectAttr "animCurveTL476.a" "clipLibrary2.cel[0].cev[62].cevr";
connectAttr "animCurveTL477.a" "clipLibrary2.cel[0].cev[63].cevr";
connectAttr "tank_R_footRoll_ctrl_slide.a" "clipLibrary2.cel[0].cev[64].cevr";
connectAttr "tank_R_footRoll_ctrl_clampHeel.a" "clipLibrary2.cel[0].cev[65].cevr"
		;
connectAttr "tank_R_footRoll_ctrl_clampToe.a" "clipLibrary2.cel[0].cev[66].cevr"
		;
connectAttr "tank_R_footRoll_ctrl_clampSideToSide.a" "clipLibrary2.cel[0].cev[67].cevr"
		;
connectAttr "tank_R_footRoll_ctrl_rotateY.a" "clipLibrary2.cel[0].cev[68].cevr";
connectAttr "tank_R_footRoll_ctrl_rotateX.a" "clipLibrary2.cel[0].cev[69].cevr";
connectAttr "tank_L_footRoll_ctrl_slide.a" "clipLibrary2.cel[0].cev[70].cevr";
connectAttr "tank_L_footRoll_ctrl_clampHeel.a" "clipLibrary2.cel[0].cev[71].cevr"
		;
connectAttr "tank_L_footRoll_ctrl_clampToe.a" "clipLibrary2.cel[0].cev[72].cevr"
		;
connectAttr "tank_L_footRoll_ctrl_clampSideToSide.a" "clipLibrary2.cel[0].cev[73].cevr"
		;
connectAttr "tank_L_footRoll_ctrl_rotateY.a" "clipLibrary2.cel[0].cev[74].cevr";
connectAttr "tank_L_footRoll_ctrl_rotateX.a" "clipLibrary2.cel[0].cev[75].cevr";
connectAttr "tank_R_fingers_ctrl_mittenRoll.a" "clipLibrary2.cel[0].cev[76].cevr"
		;
connectAttr "tank_R_fingers_ctrl_indexRoll.a" "clipLibrary2.cel[0].cev[77].cevr"
		;
connectAttr "tank_R_fingers_ctrl_mittenC.a" "clipLibrary2.cel[0].cev[78].cevr";
connectAttr "tank_R_fingers_ctrl_mittenB.a" "clipLibrary2.cel[0].cev[79].cevr";
connectAttr "tank_R_fingers_ctrl_mittenA.a" "clipLibrary2.cel[0].cev[80].cevr";
connectAttr "tank_R_fingers_ctrl_mittenSpread.a" "clipLibrary2.cel[0].cev[81].cevr"
		;
connectAttr "tank_R_fingers_ctrl_indexC.a" "clipLibrary2.cel[0].cev[82].cevr";
connectAttr "tank_R_fingers_ctrl_indexB.a" "clipLibrary2.cel[0].cev[83].cevr";
connectAttr "tank_R_fingers_ctrl_indexA.a" "clipLibrary2.cel[0].cev[84].cevr";
connectAttr "tank_R_fingers_ctrl_indexSpread.a" "clipLibrary2.cel[0].cev[85].cevr"
		;
connectAttr "tank_R_fingers_ctrl_thumbB.a" "clipLibrary2.cel[0].cev[86].cevr";
connectAttr "tank_R_fingers_ctrl_thumbA.a" "clipLibrary2.cel[0].cev[87].cevr";
connectAttr "tank_R_fingers_ctrl_rotateZ.a" "clipLibrary2.cel[0].cev[88].cevr";
connectAttr "tank_R_fingers_ctrl_rotateY.a" "clipLibrary2.cel[0].cev[89].cevr";
connectAttr "tank_R_fingers_ctrl_rotateX.a" "clipLibrary2.cel[0].cev[90].cevr";
connectAttr "tank_L_fingers_ctrl_mittenRoll.a" "clipLibrary2.cel[0].cev[91].cevr"
		;
connectAttr "tank_L_fingers_ctrl_indexRoll.a" "clipLibrary2.cel[0].cev[92].cevr"
		;
connectAttr "tank_L_fingers_ctrl_mittenC.a" "clipLibrary2.cel[0].cev[93].cevr";
connectAttr "tank_L_fingers_ctrl_mittenB.a" "clipLibrary2.cel[0].cev[94].cevr";
connectAttr "tank_L_fingers_ctrl_mittenA.a" "clipLibrary2.cel[0].cev[95].cevr";
connectAttr "tank_L_fingers_ctrl_mittenSpread.a" "clipLibrary2.cel[0].cev[96].cevr"
		;
connectAttr "tank_L_fingers_ctrl_indexC.a" "clipLibrary2.cel[0].cev[97].cevr";
connectAttr "tank_L_fingers_ctrl_indexB.a" "clipLibrary2.cel[0].cev[98].cevr";
connectAttr "tank_L_fingers_ctrl_indexA.a" "clipLibrary2.cel[0].cev[99].cevr";
connectAttr "tank_L_fingers_ctrl_indexSpread.a" "clipLibrary2.cel[0].cev[100].cevr"
		;
connectAttr "tank_L_fingers_ctrl_thumbB.a" "clipLibrary2.cel[0].cev[101].cevr";
connectAttr "tank_L_fingers_ctrl_thumbA.a" "clipLibrary2.cel[0].cev[102].cevr";
connectAttr "tank_L_fingers_ctrl_rotateZ.a" "clipLibrary2.cel[0].cev[103].cevr";
connectAttr "tank_L_fingers_ctrl_rotateY.a" "clipLibrary2.cel[0].cev[104].cevr";
connectAttr "tank_L_fingers_ctrl_rotateX.a" "clipLibrary2.cel[0].cev[105].cevr";
connectAttr "animCurveTA1288.a" "clipLibrary2.cel[0].cev[106].cevr";
connectAttr "animCurveTA1289.a" "clipLibrary2.cel[0].cev[107].cevr";
connectAttr "animCurveTA1290.a" "clipLibrary2.cel[0].cev[108].cevr";
connectAttr "animCurveTA1291.a" "clipLibrary2.cel[0].cev[109].cevr";
connectAttr "animCurveTA1292.a" "clipLibrary2.cel[0].cev[110].cevr";
connectAttr "animCurveTA1293.a" "clipLibrary2.cel[0].cev[111].cevr";
connectAttr "tank_M_backCloth_ctrl_rotateZ1.a" "clipLibrary2.cel[0].cev[112].cevr"
		;
connectAttr "tank_M_backCloth_ctrl_rotateY1.a" "clipLibrary2.cel[0].cev[113].cevr"
		;
connectAttr "tank_M_backCloth_ctrl_rotateX1.a" "clipLibrary2.cel[0].cev[114].cevr"
		;
connectAttr "tank_M_hang_ctrl_rotateZ3.a" "clipLibrary2.cel[0].cev[115].cevr";
connectAttr "tank_M_hang_ctrl_rotateY3.a" "clipLibrary2.cel[0].cev[116].cevr";
connectAttr "tank_M_hang_ctrl_rotateX3.a" "clipLibrary2.cel[0].cev[117].cevr";
connectAttr "tank_R_hang_ctrl_rotateZ3.a" "clipLibrary2.cel[0].cev[118].cevr";
connectAttr "tank_R_hang_ctrl_rotateY3.a" "clipLibrary2.cel[0].cev[119].cevr";
connectAttr "tank_R_hang_ctrl_rotateX3.a" "clipLibrary2.cel[0].cev[120].cevr";
connectAttr "tank_L_hang_ctrl_rotateZ3.a" "clipLibrary2.cel[0].cev[121].cevr";
connectAttr "tank_L_hang_ctrl_rotateY3.a" "clipLibrary2.cel[0].cev[122].cevr";
connectAttr "tank_L_hang_ctrl_rotateX3.a" "clipLibrary2.cel[0].cev[123].cevr";
connectAttr "animCurveTA1294.a" "clipLibrary2.cel[0].cev[124].cevr";
connectAttr "animCurveTA1295.a" "clipLibrary2.cel[0].cev[125].cevr";
connectAttr "animCurveTA1296.a" "clipLibrary2.cel[0].cev[126].cevr";
connectAttr "animCurveTA1297.a" "clipLibrary2.cel[0].cev[127].cevr";
connectAttr "animCurveTA1298.a" "clipLibrary2.cel[0].cev[128].cevr";
connectAttr "animCurveTA1299.a" "clipLibrary2.cel[0].cev[129].cevr";
connectAttr "animCurveTA1300.a" "clipLibrary2.cel[0].cev[130].cevr";
connectAttr "animCurveTA1301.a" "clipLibrary2.cel[0].cev[131].cevr";
connectAttr "animCurveTA1302.a" "clipLibrary2.cel[0].cev[132].cevr";
connectAttr "animCurveTA1303.a" "clipLibrary2.cel[0].cev[133].cevr";
connectAttr "animCurveTA1304.a" "clipLibrary2.cel[0].cev[134].cevr";
connectAttr "animCurveTA1305.a" "clipLibrary2.cel[0].cev[135].cevr";
connectAttr "animCurveTA1306.a" "clipLibrary2.cel[0].cev[136].cevr";
connectAttr "animCurveTA1307.a" "clipLibrary2.cel[0].cev[137].cevr";
connectAttr "animCurveTA1308.a" "clipLibrary2.cel[0].cev[138].cevr";
connectAttr "animCurveTA1309.a" "clipLibrary2.cel[0].cev[139].cevr";
connectAttr "animCurveTA1310.a" "clipLibrary2.cel[0].cev[140].cevr";
connectAttr "animCurveTA1311.a" "clipLibrary2.cel[0].cev[141].cevr";
connectAttr "tank_M_backFeature_ctrl_rotateZ3.a" "clipLibrary2.cel[0].cev[142].cevr"
		;
connectAttr "tank_M_backFeature_ctrl_rotateY3.a" "clipLibrary2.cel[0].cev[143].cevr"
		;
connectAttr "tank_M_backFeature_ctrl_rotateX3.a" "clipLibrary2.cel[0].cev[144].cevr"
		;
connectAttr "tank_M_frontCloth_ctrl_rotateZ1.a" "clipLibrary2.cel[0].cev[145].cevr"
		;
connectAttr "tank_M_frontCloth_ctrl_rotateY1.a" "clipLibrary2.cel[0].cev[146].cevr"
		;
connectAttr "tank_M_frontCloth_ctrl_rotateX1.a" "clipLibrary2.cel[0].cev[147].cevr"
		;
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of happyB.ma
