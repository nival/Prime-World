//Maya ASCII 2008 scene
//Name: ability4_3.ma
//Last modified: Mon, Jul 27, 2009 01:38:24 PM
//Codeset: 1251
requires maya "2008";
requires "Mayatomr" "9.0.1.4m - 3.6.51.0 ";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Unlimited 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200802250025-718075";
fileInfo "osv" "Microsoft Windows XP Service Pack 3 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 130 ".cel[0].cev";
	setAttr ".cd[0].cm" -type "characterMapping" 130 "R_arm_ctrl.fkIk" 0 1 "L_arm_ctrl.fkIk" 
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
		2 53 "hips_ctrl.rotateY" 2 54 "hips_ctrl.rotateX" 2 55 "R_arm_elbowIk_ctrl.translateZ" 
		1 22 "R_arm_elbowIk_ctrl.translateY" 1 23 "R_arm_elbowIk_ctrl.translateX" 
		1 24 "L_arm_elbowIk_ctrl.translateZ" 1 25 "L_arm_elbowIk_ctrl.translateY" 
		1 26 "L_arm_elbowIk_ctrl.translateX" 1 27 "L_wrist_ik_ctrl.rotateZ" 
		2 56 "L_wrist_ik_ctrl.rotateY" 2 57 "L_wrist_ik_ctrl.rotateX" 2 
		58 "L_wrist_ik_ctrl.translateZ" 1 28 "L_wrist_ik_ctrl.translateY" 1 
		29 "L_wrist_ik_ctrl.translateX" 1 30 "R_wrist_ik_ctrl.rotateZ" 2 
		59 "R_wrist_ik_ctrl.rotateY" 2 60 "R_wrist_ik_ctrl.rotateX" 2 61 "R_wrist_ik_ctrl.translateZ" 
		1 31 "R_wrist_ik_ctrl.translateY" 1 32 "R_wrist_ik_ctrl.translateX" 
		1 33  ;
	setAttr ".cd[0].cim" -type "Int32Array" 130 0 1 2 3 4
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
		 125 126 127 128 129 ;
createNode animClip -n "ability4_3Source";
	setAttr ".ihi" 0;
	setAttr -s 130 ".ac[0:129]" yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".se" 29;
	setAttr ".ci" no;
createNode animCurveTU -n "tank_R_arm_ctrl_fkIk";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 2 1 5 1 6 1 7 1 11 1 17 1 20 1 25 1 
		29 1;
	setAttr -s 10 ".kit[0:9]"  10 3 3 3 3 3 10 10 
		10 3;
	setAttr -s 10 ".kot[0:9]"  10 3 3 3 3 3 10 10 
		10 3;
createNode animCurveTU -n "tank_L_arm_ctrl_fkIk";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 2 1 5 1 6 1 7 1 11 1 17 1 20 1 25 1 
		29 1;
	setAttr -s 10 ".kit[0:9]"  10 3 3 3 3 3 10 10 
		10 3;
	setAttr -s 10 ".kot[0:9]"  10 3 3 3 3 3 10 10 
		10 3;
createNode animCurveTA -n "tank_R_upArm_fk_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -89.455040683431079 2 -31.195806820730525 
		5 -31.195806820730525 6 -31.195806820730525 7 -31.195806820730525 11 -31.195806820730525 
		17 -30.947184887972561 20 -28.679344751197615 25 -21.539852830492425 29 -16.433008012612902;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 0.81443500518798828 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0.58025485277175903 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 0.81443500518798828 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0.58025485277175903 0;
createNode animCurveTA -n "tank_R_upArm_fk_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -1.3764914370199928 2 39.448537418915414 
		5 39.448537418915414 6 39.448537418915414 7 39.448537418915414 11 39.448537418915414 
		17 39.567025013250301 20 40.64782636959788 25 44.050346867583244 29 46.484153693874759;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  0.081307761371135712 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  -0.9966890811920166 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  0.081307761371135712 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  -0.9966890811920166 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "tank_R_upArm_fk_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -5.6400210530936121 2 33.488757645726594 
		5 33.488757645726594 6 33.488757645726594 7 33.488757645726594 11 33.488757645726594 
		17 32.672789487379617 20 25.229820480976382 25 -2.1223117926814647 29 -14.962212153601083;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  0.082513846457004547 1 1 1 1 1 0.40205568075180054 
		0.39321520924568176 1;
	setAttr -s 10 ".kiy[1:9]"  0.99658989906311035 0 0 0 0 0 -0.91561514139175415 
		-0.91944652795791626 0;
	setAttr -s 10 ".kox[1:9]"  0.082513846457004547 1 1 1 1 1 0.40205568075180054 
		0.39321520924568176 1;
	setAttr -s 10 ".koy[1:9]"  0.99658989906311035 0 0 0 0 0 -0.91561514139175415 
		-0.91944652795791626 0;
createNode animCurveTA -n "tank_R_elbow_fk_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 -33.783654902297663 5 -33.783654902297663 
		6 -33.783654902297663 7 -33.783654902297663 11 -33.783654902297663 17 -33.58750836504273 
		20 -31.798329973009171 25 -26.16573512318465 29 -22.136766656027952;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  0.10808606445789337 1 1 1 1 1 1 0.87172937393188477 
		1;
	setAttr -s 10 ".kiy[1:9]"  -0.99414151906967163 0 0 0 0 0 0 0.48998779058456421 
		0;
	setAttr -s 10 ".kox[1:9]"  0.10808606445789337 1 1 1 1 1 1 0.87172937393188477 
		1;
	setAttr -s 10 ".koy[1:9]"  -0.99414151906967163 0 0 0 0 0 0 0.48998779058456421 
		0;
createNode animCurveTA -n "tank_R_wrist_fk_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 5 0 6 0 7 0 11 0 17 0 20 0 25 0 
		29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "tank_R_wrist_fk_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 5 0 6 0 7 0 11 0 17 0 20 0 25 0 
		29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "tank_R_wrist_fk_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 5 0 6 0 7 0 11 0 17 0 20 0 25 0 
		29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "tank_R_shoulder_fk_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 2.0723375349424296 2 -34.242845369791141 
		4 -31.890647529774107 5 -6.8910974362290398 7 -6.8910974362290398 11 -6.8910974362290398 
		17 -13.390009346690171 20 -32.99280450738253 25 -40.691514243107463 29 -9.982335324211336;
	setAttr -s 10 ".kit[0:9]"  10 1 3 3 3 3 3 10 
		3 3;
	setAttr -s 10 ".kot[0:9]"  10 1 3 3 3 3 3 10 
		3 3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 0.48836076259613037 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 -0.87264180183410645 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 0.48836076259613037 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 -0.87264180183410645 0 0;
createNode animCurveTA -n "tank_R_shoulder_fk_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.43937305726377879 2 3.3502308408519244 
		4 -6.3491462378650008 5 6.650268435441542 7 6.650268435441542 11 6.650268435441542 
		17 5.8278136950510984 20 1.6452844170198895 25 13.265221047068005 29 15.766648207086439;
	setAttr -s 10 ".kit[0:9]"  10 1 3 3 3 3 3 10 
		3 3;
	setAttr -s 10 ".kot[0:9]"  10 1 3 3 3 3 3 10 
		3 3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 0.89913225173950195 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0.43767708539962769 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 0.89913225173950195 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0.43767708539962769 0 0;
createNode animCurveTA -n "animCurveTA98";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 -53.200740175628781 4 -57.388932727302155 
		5 -15.677062953203269 6 -15.677062953203269 7 -15.677062953203269 11 -15.677062953203269 
		17 -19.181510730742371 20 -38.309344892304225 25 -22.07655431574522 29 -11.890430275710493;
	setAttr -s 11 ".kit[0:10]"  10 1 10 3 3 3 1 3 
		10 10 3;
	setAttr -s 11 ".kot[0:10]"  10 1 10 3 3 3 1 3 
		10 10 3;
	setAttr -s 11 ".kix[1:10]"  1 0.15094286203384399 1 1 1 1 1 0.98251801729202271 
		0.54535490274429321 1;
	setAttr -s 11 ".kiy[1:10]"  0 0.98854249715805054 0 0 0 0 0 -0.18616767227649689 
		0.83820521831512451 0;
	setAttr -s 11 ".kox[1:10]"  1 0.15094286203384399 1 1 1 1 1 0.98251801729202271 
		0.54535490274429321 1;
	setAttr -s 11 ".koy[1:10]"  0 0.98854249715805054 0 0 0 0 0 -0.18616767227649689 
		0.83820521831512451 0;
createNode animCurveTA -n "animCurveTA99";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 -38.28377467823082 4 -37.438240382712003 
		5 -25.47238250173945 6 -25.47238250173945 7 -25.47238250173945 11 -25.47238250173945 
		17 -19.279375772470054 20 7.350495671366069 25 17.731622922762124 29 13.154882915602682;
	setAttr -s 11 ".kit[0:10]"  10 1 3 3 3 3 1 3 
		10 10 3;
	setAttr -s 11 ".kot[0:10]"  10 1 3 3 3 3 1 3 
		10 10 3;
	setAttr -s 11 ".kix[1:10]"  1 1 1 1 1 1 1 0.381583571434021 0.94743901491165161 
		1;
	setAttr -s 11 ".kiy[1:10]"  0 0 0 0 0 0 0 0.92433440685272217 0.31993651390075684 
		0;
	setAttr -s 11 ".kox[1:10]"  1 1 1 1 1 1 1 0.381583571434021 0.94743901491165161 
		1;
	setAttr -s 11 ".koy[1:10]"  0 0 0 0 0 0 0 0.92433440685272217 0.31993651390075684 
		0;
createNode animCurveTA -n "tank_L_upArm_fk_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -86.560064018088582 2 -54.157692469207241 
		5 -54.157692469207241 6 -54.157692469207241 7 -54.157692469207241 11 -54.157692469207241 
		17 -53.673018171230765 20 -49.251992986440236 25 -33.005188076295767 29 -25.378456988571386;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  0.67002719640731812 1 1 1 1 1 0.59445774555206299 
		0.58429992198944092 1;
	setAttr -s 10 ".kiy[1:9]"  -0.74233657121658325 0 0 0 0 0 0.80412685871124268 
		0.81153780221939087 0;
	setAttr -s 10 ".kox[1:9]"  0.67002719640731812 1 1 1 1 1 0.59445774555206299 
		0.58429992198944092 1;
	setAttr -s 10 ".koy[1:9]"  -0.74233657121658325 0 0 0 0 0 0.80412685871124268 
		0.81153780221939087 0;
createNode animCurveTA -n "tank_L_upArm_fk_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 3.362244931545689 2 15.078622424421384 
		5 15.078622424421384 6 15.078622424421384 7 15.078622424421384 11 15.078622424421384 
		17 15.654680375855602 20 20.909274485389236 25 40.219358217899497 29 49.284082676870852;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 0.52815699577331543 0.51812261343002319 
		1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0.84914672374725342 0.85530632734298706 
		0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 0.52815699577331543 0.51812261343002319 
		1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0.84914672374725342 0.85530632734298706 
		0;
createNode animCurveTA -n "tank_L_upArm_fk_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -22.879383758771784 2 46.655633975872433 
		5 46.655633975872433 6 46.655633975872433 7 46.655633975872433 11 46.655633975872433 
		17 46.458819543194458 20 44.663548848560211 25 39.011774540496667 29 34.969087097535308;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  0.1426030695438385 1 1 1 1 1 1 0.87101626396179199 
		1;
	setAttr -s 10 ".kiy[1:9]"  -0.98977994918823242 0 0 0 0 0 0 -0.491254061460495 
		0;
	setAttr -s 10 ".kox[1:9]"  0.1426030695438385 1 1 1 1 1 1 0.87101626396179199 
		1;
	setAttr -s 10 ".koy[1:9]"  -0.98977994918823242 0 0 0 0 0 0 -0.491254061460495 
		0;
createNode animCurveTA -n "tank_L_elbow_fk_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 -29.363922948428606 5 -29.363922948428606 
		6 -29.363922948428606 7 -29.363922948428606 11 -29.363922948428606 17 -28.940729410027199 
		20 -25.080509672515831 25 -10.894605930810444 29 -4.2353230899544307;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  0.074930846691131592 1 1 1 1 1 0.64616590738296509 
		0.63619470596313477 1;
	setAttr -s 10 ".kiy[1:9]"  -0.9971887469291687 0 0 0 0 0 0.76319694519042969 
		0.77152860164642334 0;
	setAttr -s 10 ".kox[1:9]"  0.074930846691131592 1 1 1 1 1 0.64616590738296509 
		0.63619470596313477 1;
	setAttr -s 10 ".koy[1:9]"  -0.9971887469291687 0 0 0 0 0 0.76319694519042969 
		0.77152860164642334 0;
createNode animCurveTA -n "tank_L_wrist_fk_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 5 0 6 0 7 0 11 0 17 0 20 0 25 0 
		29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "tank_L_wrist_fk_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 5 0 6 0 7 0 11 0 17 0 20 0 25 0 
		29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "tank_L_wrist_fk_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 5 0 6 0 7 0 11 0 17 0 20 0 25 0 
		29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "tank_M_neck_fk_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 24.189035444866914 2 0 5 0 6 0 7 0 12 
		-43.373571151653614 17 -41.629965395425188 20 -19.059686480129884 25 0 29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 10 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 10 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 0.34454390406608582 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0.93877017498016357 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 0.34454390406608582 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0.93877017498016357 0 0;
createNode animCurveTA -n "tank_M_neck_fk_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 5 0 6 0 7 0 17 0 20 0 25 0 29 0;
	setAttr -s 9 ".kit[1:8]"  1 10 1 3 10 10 10 3;
	setAttr -s 9 ".kot[1:8]"  1 10 1 3 10 10 10 3;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "tank_M_neck_fk_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 5 0 6 0 7 0 17 0 20 0 25 0 29 0;
	setAttr -s 9 ".kit[1:8]"  1 10 1 3 10 10 10 3;
	setAttr -s 9 ".kot[1:8]"  1 10 1 3 10 10 10 3;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "tank_M_head_fk_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -40.897138223406102 2 -23.162235351402309 
		7 -66.525159316500904 16 -70.328280201043242 20 -40.748056694995967 25 -17.506845541036522 
		29 -14.515820710620677;
	setAttr -s 7 ".kit[1:6]"  1 10 10 10 10 3;
	setAttr -s 7 ".kot[1:6]"  1 10 10 10 10 3;
	setAttr -s 7 ".kix[1:6]"  0.32949343323707581 0.49316069483757019 
		0.69372540712356567 0.30944046378135681 0.5480729341506958 1;
	setAttr -s 7 ".kiy[1:6]"  -0.94415783882141113 -0.86993831396102905 
		0.72023952007293701 0.95091885328292847 0.83643049001693726 0;
	setAttr -s 7 ".kox[1:6]"  0.32949343323707581 0.49316069483757019 
		0.69372540712356567 0.30944046378135681 0.5480729341506958 1;
	setAttr -s 7 ".koy[1:6]"  -0.94415783882141113 -0.86993831396102905 
		0.72023952007293701 0.95091885328292847 0.83643049001693726 0;
createNode animCurveTA -n "tank_M_head_fk_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1.6788139529320265 2 1.6788139529320265 
		16 0.25043335881874357 20 -1.5705588650234097 25 -12.331904168870317 29 -17.383598210882599;
	setAttr -s 6 ".kit[1:5]"  1 10 10 10 3;
	setAttr -s 6 ".kot[1:5]"  1 10 10 10 3;
	setAttr -s 6 ".kix[1:5]"  1 1 1 0.73594361543655396 1;
	setAttr -s 6 ".kiy[1:5]"  0 0 0 -0.67704278230667114 0;
	setAttr -s 6 ".kox[1:5]"  1 1 1 0.73594361543655396 1;
	setAttr -s 6 ".koy[1:5]"  0 0 0 -0.67704278230667114 0;
createNode animCurveTA -n "tank_M_head_fk_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -1.2527070794692798 2 -1.2527070794692798 
		16 -0.84295587523731608 20 -0.77890527991180647 25 0.56532484416236162 29 1.5268462968664711;
	setAttr -s 6 ".kit[1:5]"  1 10 10 10 3;
	setAttr -s 6 ".kot[1:5]"  1 10 10 10 3;
	setAttr -s 6 ".kix[1:5]"  1 1 1 1 1;
	setAttr -s 6 ".kiy[1:5]"  0 0 0 0 0;
	setAttr -s 6 ".kox[1:5]"  1 1 1 1 1;
	setAttr -s 6 ".koy[1:5]"  0 0 0 0 0;
createNode animCurveTL -n "tank_R_leg_kneeIk_ctrl_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.068559431513433244 2 0.00025694328101411035 
		5 -0.48104483033160161 6 -0.48104483033160161 7 -0.48104483033160161 11 -0.48104483033160161 
		17 -0.47293917375856709 20 -0.39900228047113251 25 -0.12729193590242055 29 0.00025694328101411035;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 0.61083865165710449 0.60071170330047607 
		1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0.79175513982772827 0.79946577548980713 
		0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 0.61083865165710449 0.60071170330047607 
		1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0.79175513982772827 0.79946577548980713 
		0;
createNode animCurveTL -n "tank_R_leg_kneeIk_ctrl_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.19392631490774814 2 0.092152062091758691 
		5 0.050866559595499405 6 0.050866559595499405 7 0.050866559595499405 11 0.050866559595499405 
		17 0.052212246502857662 20 0.06448712002743312 25 0.10313021436873454 29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "tank_R_leg_kneeIk_ctrl_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.41621523852525538 2 -0.12527739251666781 
		5 -0.1637564024290098 6 -0.1637564024290098 7 -0.1637564024290098 11 -0.1637564024290098 
		17 -0.16310837315357465 20 -0.15719728242905795 25 -0.13858830563836702 29 -0.12527739251666781;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "tank_L_leg_kneeIk_ctrl_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.12430866650918489 2 0.37212154043042989 
		5 0.032833691772160403 6 0.032833691772160403 7 0.032833691772160403 11 0.032833691772160403 
		17 0.032833691772160403 20 0.032833691772160375 25 0.032833691772160285 29 0.032833691772160223;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "tank_L_leg_kneeIk_ctrl_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.21267695235768835 2 -0.2571328939085919 
		5 -0.24620022940417824 6 -0.24620022940417824 7 -0.24620022940417824 11 -0.24620022940417824 
		17 -0.24012212627000612 20 -0.18467984855047653 25 0.019064722867369321 29 -0.016062985925156426;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 0.71709215641021729 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0.69697827100753784 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 0.71709215641021729 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0.69697827100753784 0 0;
createNode animCurveTL -n "tank_L_leg_kneeIk_ctrl_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.20930625035219369 2 0.33224650602138706 
		5 0.1172838001577239 6 0.1172838001577239 7 0.1172838001577239 11 0.1172838001577239 
		17 0.1172838001577239 20 0.1172838001577239 25 0.11728380015772392 29 0.11728380015772394;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "tank_com_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 4.0303467086837745 3 3.6977897268488915 
		5 3.2472207612871475 11 3.2472207612871475 17 3.2726820774659768 25 1.1769845103697112 
		29 0;
	setAttr -s 7 ".kit[2:6]"  3 3 10 10 3;
	setAttr -s 7 ".kot[2:6]"  3 3 10 10 3;
createNode animCurveTA -n "tank_com_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 -0.99374261800199859 5 -2.3158173002997038 
		11 -2.3158173002997038 17 -2.0042792328266676 25 -0.63120994418144027 29 0;
	setAttr -s 7 ".kit[2:6]"  3 3 10 10 3;
	setAttr -s 7 ".kot[2:6]"  3 3 10 10 3;
createNode animCurveTA -n "tank_com_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -3.1995227445375076 3 15.142449668642477 
		5 32.236829665660231 11 17.092836518126528 17 27.662090843837269 25 11.098720885777338 
		29 3.6719125695963681;
	setAttr -s 7 ".kit[2:6]"  3 3 10 10 3;
	setAttr -s 7 ".kot[2:6]"  3 3 10 10 3;
createNode animCurveTL -n "tank_com_ctrl_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.083905346187052851 3 -0.32675039396877137 
		5 -0.41030998602145652 11 -0.46854106278025964 17 -0.3387655470596978 25 -0.091049287681205668 
		29 -0.0319338039184065;
	setAttr -s 7 ".kit[0:6]"  10 10 3 3 10 3 3;
	setAttr -s 7 ".kot[0:6]"  10 10 3 3 10 3 3;
createNode animCurveTL -n "tank_com_ctrl_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.18190998978057271 3 -0.35527958851523278 
		5 -0.41493364894366164 11 -0.53714025790713249 17 -0.25246590570105026 25 0.22580428204950248 
		29 0.00078859512199502824;
	setAttr -s 7 ".kit[0:6]"  10 10 3 3 10 3 3;
	setAttr -s 7 ".kot[0:6]"  10 10 3 3 10 3 3;
createNode animCurveTL -n "tank_com_ctrl_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.027094269865637972 3 -0.027094269865637944 
		5 -0.027094269865637927 11 -0.031522857825758373 17 -0.026637972260541747 25 -0.0093726286902642651 
		29 0;
	setAttr -s 7 ".kit[2:6]"  3 3 10 10 3;
	setAttr -s 7 ".kot[2:6]"  3 3 10 10 3;
createNode animCurveTA -n "tank_R_foot_ctrl_rotateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -16.236770139599834 3 -16.236770139599834 
		5 -16.236770139599834 7 -16.236770139599834 11 -16.236770139599834 17 -16.236770139599834 
		20 -16.236770139599834 25 -16.236770139599834 29 -16.236770139599834;
	setAttr -s 9 ".kit[0:8]"  10 1 1 3 3 10 1 1 
		3;
	setAttr -s 9 ".kot[0:8]"  10 1 1 3 3 10 1 1 
		3;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "tank_R_foot_ctrl_rotateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 5 0 7 0 11 0 17 0 20 0 25 0 29 
		0;
	setAttr -s 9 ".kit[0:8]"  10 1 1 3 3 10 1 1 
		3;
	setAttr -s 9 ".kot[0:8]"  10 1 1 3 3 10 1 1 
		3;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "tank_R_foot_ctrl_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 29.469230096288687 3 0 5 0 7 0 11 0 17 
		0 20 0 25 0 29 0;
	setAttr -s 9 ".kit[0:8]"  10 1 1 3 3 10 1 1 
		3;
	setAttr -s 9 ".kot[0:8]"  10 1 1 3 3 10 1 1 
		3;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "tank_R_foot_ctrl_translateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.13237335523236018 3 -6.0000000000892673e-006 
		5 -6.0000000000892673e-006 7 -6.0000000000892673e-006 11 -6.0000000000892673e-006 
		17 -6.0000000000892673e-006 20 -6.0000000000892673e-006 25 -6.0000000000892673e-006 
		29 -6.0000000000892673e-006;
	setAttr -s 9 ".kit[0:8]"  10 1 1 3 3 10 1 1 
		3;
	setAttr -s 9 ".kot[0:8]"  10 1 1 3 3 10 1 1 
		3;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "tank_R_foot_ctrl_translateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.42950114909550519 3 0.13079324706014056 
		5 0.13079324706014056 7 0.13079324706014056 11 0.13079324706014056 17 0.13079324706014056 
		20 2.1809999999936394e-005 25 2.1809999999936394e-005 29 2.1809999999936394e-005;
	setAttr -s 9 ".kit[0:8]"  10 1 1 3 3 10 1 1 
		3;
	setAttr -s 9 ".kot[0:8]"  10 1 1 3 3 10 1 1 
		3;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "tank_R_foot_ctrl_translateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.040093865534497591 3 -0.040093865534497591 
		5 -0.040093865534497591 7 -0.040093865534497591 11 -0.040093865534497591 17 -0.040093865534497591 
		20 -0.040093865534497591 25 -0.040093865534497591 29 -0.040093865534497591;
	setAttr -s 9 ".kit[0:8]"  10 1 1 3 3 10 1 1 
		3;
	setAttr -s 9 ".kot[0:8]"  10 1 1 3 3 10 1 1 
		3;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "tank_L_foot_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1.2955202959470657 2 14.78467884282118 
		4 25.000774638404387 5 25.000774638404387 6 25.000774638404387 7 25.000774638404387 
		11 25.000774638404387 18 25.000774638404387 21 21.365082801812449 25 25.000774638404387 
		29 25.000774638404387;
	setAttr -s 11 ".kit[0:10]"  10 10 3 3 1 3 3 3 
		10 1 3;
	setAttr -s 11 ".kot[0:10]"  10 10 3 3 1 3 3 3 
		10 1 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "tank_L_foot_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -9.3172514171137504 2 8.4194426745928279 
		4 0 5 0 6 0 7 0 11 0 18 0 21 -13.299467027382612 25 0 29 0;
	setAttr -s 11 ".kit[0:10]"  10 10 3 3 1 3 3 3 
		10 1 3;
	setAttr -s 11 ".kot[0:10]"  10 10 3 3 1 3 3 3 
		10 1 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "tank_L_foot_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 49.719259945663509 2 -22.344429705194017 
		4 0 5 0 6 0 7 0 11 0 18 0 21 30.457626383946057 25 0 29 0;
	setAttr -s 11 ".kit[0:10]"  10 10 3 3 1 3 3 3 
		10 1 3;
	setAttr -s 11 ".kot[0:10]"  10 10 3 3 1 3 3 3 
		10 1 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "tank_L_foot_ctrl_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0.2400357145301461 2 0.29738754806939371 
		4 0 5 0 6 0 7 0 11 0 18 0 21 0.1994871675198247 25 0 29 0;
	setAttr -s 11 ".kit[0:10]"  10 10 3 3 1 3 3 3 
		10 1 3;
	setAttr -s 11 ".kot[0:10]"  10 10 3 3 1 3 3 3 
		10 1 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "tank_L_foot_ctrl_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -0.090333936745635501 2 -0.44368010792909457 
		4 -0.65748466020978213 5 -0.65748466020978213 6 -0.65748466020978213 7 -0.65748466020978213 
		11 -0.65748466020978213 18 -0.65748466020978213 21 -0.03552871455024692 25 0 29 0;
	setAttr -s 11 ".kit[0:10]"  10 10 3 3 1 3 3 3 
		10 1 3;
	setAttr -s 11 ".kot[0:10]"  10 10 3 3 1 3 3 3 
		10 1 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "tank_L_foot_ctrl_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0.04101937684988706 2 0.06447781764902559 
		4 0.038258090963777407 5 0.038258090963777407 6 0.038258090963777407 7 0.038258090963777407 
		11 0.038258090963777407 18 0.038258090963777407 21 0.049891121784473746 25 0.038258090963777358 
		29 0.038258090963777358;
	setAttr -s 11 ".kit[0:10]"  10 10 3 3 1 3 3 3 
		10 1 3;
	setAttr -s 11 ".kot[0:10]"  10 10 3 3 1 3 3 3 
		10 1 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_R_mace_ctrl_parent";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 25 ".ktv[0:24]"  0 1 1 1 2 1 3 1 4 1 5 1 7 1 8 1 9 1 10 
		1 11 1 12 1 13 1 14 1 15 1 16 1 17 1 18 1 19 1 20 1 21 1 22 1 23 1 24 1 29 1;
	setAttr -s 25 ".kit[24]"  1;
	setAttr -s 25 ".kot[24]"  5;
	setAttr -s 25 ".kix[24]"  1;
	setAttr -s 25 ".kiy[24]"  0;
createNode animCurveTA -n "tank_R_mace_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 25 ".ktv[0:24]"  0 0 1 13.895653103771515 2 24.471969446342371 
		3 21.210419820962638 4 -7.4961960462510406 5 -7.5383212580296908 7 -8.9507175201173297 
		8 -9.7866952556879081 9 -10.630980198725606 10 -11.202610920856158 11 -11.174267316448065 
		12 -11.345641685307454 13 -12.184524327797279 14 -12.848814353920696 15 -12.783650399980576 
		16 -11.774472994922411 17 -9.6534067722933976 18 -7.019223352544806 19 -5.1268851811091727 
		20 -4.6394016848909354 21 -5.9879478343003187 22 -8.8928078754057385 23 -12.872364109477166 
		24 -17.658379797672083 29 0;
	setAttr -s 25 ".kit[24]"  1;
	setAttr -s 25 ".kot[24]"  1;
	setAttr -s 25 ".kix[24]"  1;
	setAttr -s 25 ".kiy[24]"  0;
	setAttr -s 25 ".kox[24]"  1;
	setAttr -s 25 ".koy[24]"  0;
createNode animCurveTA -n "tank_R_mace_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 25 ".ktv[0:24]"  0 0 1 -2.5760225029945061 2 -7.6883821692634164 
		3 -8.4934490945384447 4 -9.901381718861991 5 -11.055321718590577 7 -9.552387089894621 
		8 -10.845598185912261 9 -12.140365596871927 10 -12.904491557006271 11 -12.461260761930056 
		12 -10.538213484725755 13 -7.3026054955708215 14 -2.7216314857425647 15 3.2652215073397532 
		16 10.71540191033295 17 17.849597316808197 18 21.534373146409905 19 20.924473690330387 
		20 16.73587380848285 21 10.546081403378702 22 4.0907488176269267 23 -0.0433259849114732 
		24 -3.1946243566483608 29 0;
	setAttr -s 25 ".kit[24]"  1;
	setAttr -s 25 ".kot[24]"  1;
	setAttr -s 25 ".kix[24]"  1;
	setAttr -s 25 ".kiy[24]"  0;
	setAttr -s 25 ".kox[24]"  1;
	setAttr -s 25 ".koy[24]"  0;
createNode animCurveTA -n "tank_R_mace_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 25 ".ktv[0:24]"  0 0 1 -18.642267664609772 2 -55.886992507052142 
		3 -59.38589732780278 4 -65.710294247261189 5 -68.684801117469561 7 -72.322707231742513 
		8 -71.254672211634016 9 -70.099534403868702 10 -69.585186524620539 11 -70.365724866263065 
		12 -70.384366678737081 13 -68.049900748186317 14 -64.62074406118559 15 -61.052401178437869 
		16 -57.811526945212208 17 -53.008201712900018 18 -46.017187617597529 19 -39.782691310161198 
		20 -34.167825880687559 21 -27.966206612069247 22 -21.603161859732378 23 -16.077924530323237 
		24 -11.643866690391881 29 0;
	setAttr -s 25 ".kit[24]"  1;
	setAttr -s 25 ".kot[24]"  1;
	setAttr -s 25 ".kix[24]"  1;
	setAttr -s 25 ".kiy[24]"  0;
	setAttr -s 25 ".kox[24]"  1;
	setAttr -s 25 ".koy[24]"  0;
createNode animCurveTL -n "tank_R_mace_ctrl_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 25 ".ktv[0:24]"  0 -0.808 1 -0.80098701259879834 2 -0.7880913099502167 
		3 -0.78570078791639908 4 -0.78157084965870949 5 -0.77767940411020708 7 -0.78446079876776897 
		8 -0.77908994395224251 9 -0.77371496222460179 10 -0.77059187154081066 11 -0.77251063864596192 
		12 -0.78011129069032759 13 -0.79245393718987911 14 -0.81001874315663391 15 -0.83324641930904209 
		16 -0.86220230644194329 17 -0.88891474770524748 18 -0.90137852906412497 19 -0.89776121582284407 
		20 -0.88054442166194002 21 -0.85495272547332202 22 -0.82787681279627567 23 -0.81024170997880152 
		24 -0.79684553653157986 29 -0.808;
	setAttr -s 25 ".kit[24]"  1;
	setAttr -s 25 ".kot[24]"  1;
	setAttr -s 25 ".kix[24]"  1;
	setAttr -s 25 ".kiy[24]"  0;
	setAttr -s 25 ".kox[24]"  1;
	setAttr -s 25 ".koy[24]"  0;
createNode animCurveTL -n "tank_R_mace_ctrl_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 25 ".ktv[0:24]"  0 0 1 0.055061876800416784 2 0.094122304251159819 
		3 0.087907104861891974 4 -0.023516329156720351 5 -0.023703443163278538 7 -0.029638649676963325 
		8 -0.032738144131049633 9 -0.03581527460948724 10 -0.037900935774614113 11 -0.037906704460776534 
		12 -0.038862051615404618 13 -0.042430388228816555 14 -0.04525028205741826 15 -0.044875145005699939 
		16 -0.040117584650986804 17 -0.030717349290643198 18 -0.020352656831723926 19 -0.013740285714665724 
		20 -0.012813616273307727 21 -0.019285072578362473 22 -0.032029981074063789 23 -0.048686526660761391 
		24 -0.067888817829249756 29 0;
	setAttr -s 25 ".kit[24]"  1;
	setAttr -s 25 ".kot[24]"  1;
	setAttr -s 25 ".kix[24]"  1;
	setAttr -s 25 ".kiy[24]"  0;
	setAttr -s 25 ".kox[24]"  1;
	setAttr -s 25 ".koy[24]"  0;
createNode animCurveTL -n "tank_R_mace_ctrl_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 25 ".ktv[0:24]"  0 0 1 -0.028485780645648422 2 -0.21583963407490581 
		3 -0.022796974573946915 4 -0.0033266791166806087 5 -0.0040237571332140121 7 -0.0033880120711776707 
		8 -0.0046113232559105155 9 -0.00601058221234263 10 -0.006947282622614237 11 -0.0065371939327556472 
		12 -0.0052101043858319152 13 -0.003927589370086304 14 -0.0029747580640427929 15 -0.0031356740671247829 
		16 -0.0060162710532596364 17 -0.011579542335381166 18 -0.015046089425819087 19 -0.013401272404306219 
		20 -0.0079136013744507405 21 -0.0026790171857180578 22 -0.0011104650781381675 23 
		-0.0035686849038698565 24 -0.0089031979915459303 29 0;
	setAttr -s 25 ".kit[24]"  1;
	setAttr -s 25 ".kot[24]"  1;
	setAttr -s 25 ".kix[24]"  1;
	setAttr -s 25 ".kiy[24]"  0;
	setAttr -s 25 ".kox[24]"  1;
	setAttr -s 25 ".koy[24]"  0;
createNode animCurveTU -n "tank_L_mace_ctrl_parent";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 24 ".ktv[0:23]"  0 1 1 1 2 1 3 1 4 1 5 1 6 1 7 1 8 1 9 1 
		10 1 11 1 12 1 13 1 14 1 15 1 16 1 17 1 18 1 19 1 20 1 21 1 22 1 29 1;
	setAttr -s 24 ".kit[23]"  1;
	setAttr -s 24 ".kot[23]"  5;
	setAttr -s 24 ".kix[23]"  1;
	setAttr -s 24 ".kiy[23]"  0;
createNode animCurveTA -n "tank_L_mace_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 24 ".ktv[0:23]"  0 0 1 -4.0663452172717358 2 -22.728261419495936 
		3 -18.857352068255064 4 5.872395144476787 5 13.33448423322824 6 13.205321672135089 
		7 12.397670742164909 8 11.137951829115023 9 9.8253562771419585 10 8.8014303964601481 
		11 8.4237031424116733 12 9.2770664110783176 13 11.245655305594868 14 13.64032476399473 
		15 15.827270523128918 16 17.221630830723971 17 18.496080491254531 18 21.349828635651427 
		19 20.219877014523252 20 16.443149986378312 21 14.984440174253617 22 12.559933439460144 
		29 0;
	setAttr -s 24 ".kit[23]"  1;
	setAttr -s 24 ".kot[23]"  1;
	setAttr -s 24 ".kix[23]"  1;
	setAttr -s 24 ".kiy[23]"  0;
	setAttr -s 24 ".kox[23]"  1;
	setAttr -s 24 ".koy[23]"  0;
createNode animCurveTA -n "tank_L_mace_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 24 ".ktv[0:23]"  0 0 1 11.290117687014479 2 -3.6648950210387055 
		3 -0.9090989504814968 4 3.5709736433814978 5 7.2527753459092379 6 7.7892141515892774 
		7 7.5750104260411257 8 8.5686618004629853 9 9.4372776262230911 10 10.123525059509586 
		11 10.395699597588086 12 9.5818113472250452 13 7.3364567608225615 14 3.9825706109528487 
		15 -0.18385809098480393 16 -4.9919716764884159 17 -10.285167176802707 18 -13.018182426402568 
		19 -11.171460108454225 20 -9.345688377824052 21 -8.1469393832353916 22 -6.4297013683034132 
		29 0;
	setAttr -s 24 ".kit[23]"  1;
	setAttr -s 24 ".kot[23]"  1;
	setAttr -s 24 ".kix[23]"  1;
	setAttr -s 24 ".kiy[23]"  0;
	setAttr -s 24 ".kox[23]"  1;
	setAttr -s 24 ".koy[23]"  0;
createNode animCurveTA -n "tank_L_mace_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 24 ".ktv[0:23]"  0 0 1 -14.354621316353931 2 -80.799068895474861 
		3 -73.593363890714301 4 -72.575492769962224 5 -71.998561598725914 6 -73.092810561426106 
		7 -73.312295841245657 8 -71.944857638580501 9 -70.818649389907549 10 -70.110790629375558 
		11 -69.859660021069871 12 -69.78510926413442 13 -69.723099724056539 14 -69.845231565618349 
		15 -70.171182361646004 16 -70.579107430577793 17 -71.242798425055668 18 -75.220655611639472 
		19 -80.795074670882244 20 -80.997736421606092 21 -73.419138872467855 22 -60.025192922540469 
		29 0;
	setAttr -s 24 ".kit[23]"  1;
	setAttr -s 24 ".kot[23]"  1;
	setAttr -s 24 ".kix[23]"  1;
	setAttr -s 24 ".kiy[23]"  0;
	setAttr -s 24 ".kox[23]"  1;
	setAttr -s 24 ".koy[23]"  0;
createNode animCurveTL -n "tank_L_mace_ctrl_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 24 ".ktv[0:23]"  0 -0.80789537837891157 1 -0.76490626622131375 
		2 -0.82688090979977291 3 -0.81603017522775501 4 -0.79801812175207365 5 -0.78323397581132292 
		6 -0.78106412775457335 7 -0.78191787145261848 8 -0.77796543756313064 9 -0.77451213658553719 
		10 -0.77178427090277335 11 -0.77070295019229684 12 -0.77394870182784414 13 -0.78293135730257557 
		14 -0.79640369252670506 15 -0.81317117890867197 16 -0.83245781813823916 17 -0.85345401288379641 
		18 -0.86406923040489936 19 -0.85668343863454366 20 -0.84949013301855358 21 -0.84496976046522532 
		22 -0.83820623464352462 29 -0.80789537837891157;
	setAttr -s 24 ".kit[23]"  1;
	setAttr -s 24 ".kot[23]"  1;
	setAttr -s 24 ".kix[23]"  1;
	setAttr -s 24 ".kiy[23]"  0;
	setAttr -s 24 ".kox[23]"  1;
	setAttr -s 24 ".koy[23]"  0;
createNode animCurveTL -n "tank_L_mace_ctrl_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 24 ".ktv[0:23]"  0 0 1 0.012315359491283689 2 0.073605033228823225 
		3 0.066127095461774449 4 -0.031854176411999002 5 -0.061138674530259673 6 -0.060733232318874009 
		7 -0.057630046770270393 8 -0.052427838969600737 9 -0.047042977207772396 10 -0.042859095930890045 
		11 -0.04131366074679782 12 -0.044734152635442115 13 -0.052651136542816029 14 -0.062239605026039896 
		15 -0.070780501711901145 16 -0.07575294108839295 17 -0.079555351837236277 18 -0.089667890664561933 
		19 -0.086910229280687923 20 -0.073362692259729356 21 -0.06706376973841266 22 -0.056173141639969115 
		29 0;
	setAttr -s 24 ".kit[23]"  1;
	setAttr -s 24 ".kot[23]"  1;
	setAttr -s 24 ".kix[23]"  1;
	setAttr -s 24 ".kiy[23]"  0;
	setAttr -s 24 ".kox[23]"  1;
	setAttr -s 24 ".koy[23]"  0;
createNode animCurveTL -n "tank_L_mace_ctrl_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 24 ".ktv[0:23]"  0 0 1 0.06358322117306138 2 0.2139923660653581 
		3 0.012129683043645367 4 0.0012756447991797426 5 0.0072691704507661381 6 0.0073889723684946729 
		7 0.0065794836583648042 8 0.0059031532352189497 9 0.0053203023706807073 10 0.004997763245180642 
		11 0.0049185436318606168 12 0.0049983725159081782 13 0.0054167662300469432 14 0.0066718783212158517 
		15 0.0089671061025113907 16 0.012063781436228993 17 0.017040704578841548 18 0.023502052911019811 
		19 0.020452090316225191 20 0.014179242576201734 21 0.011469358994268708 22 0.0076531041222525076 
		29 0;
	setAttr -s 24 ".kit[23]"  1;
	setAttr -s 24 ".kot[23]"  1;
	setAttr -s 24 ".kix[23]"  1;
	setAttr -s 24 ".kiy[23]"  0;
	setAttr -s 24 ".kox[23]"  1;
	setAttr -s 24 ".koy[23]"  0;
createNode animCurveTU -n "tank_R_footRoll_ctrl_slide";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 5 0 6 0 7 0 11 0 17 0 20 0 25 0 29 
		0;
	setAttr -s 9 ".kit[2:8]"  1 3 3 10 10 10 3;
	setAttr -s 9 ".kot[2:8]"  1 3 3 10 10 10 3;
	setAttr -s 9 ".kix[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[2:8]"  0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[2:8]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_R_footRoll_ctrl_clampHeel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 45 5 45 6 45 7 45 11 45 17 45 20 45 25 
		45 29 45;
	setAttr -s 9 ".kit[2:8]"  1 3 3 10 10 10 3;
	setAttr -s 9 ".kot[2:8]"  1 3 3 10 10 10 3;
	setAttr -s 9 ".kix[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[2:8]"  0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[2:8]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_R_footRoll_ctrl_clampToe";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 45 5 45 6 45 7 45 11 45 17 45 20 45 25 
		45 29 45;
	setAttr -s 9 ".kit[2:8]"  1 3 3 10 10 10 3;
	setAttr -s 9 ".kot[2:8]"  1 3 3 10 10 10 3;
	setAttr -s 9 ".kix[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[2:8]"  0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[2:8]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_R_footRoll_ctrl_clampSideToSide";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 45 5 45 6 45 7 45 11 45 17 45 20 45 25 
		45 29 45;
	setAttr -s 9 ".kit[2:8]"  1 3 3 10 10 10 3;
	setAttr -s 9 ".kot[2:8]"  1 3 3 10 10 10 3;
	setAttr -s 9 ".kix[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[2:8]"  0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[2:8]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "tank_R_footRoll_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 5 0 6 0 7 0 11 0 17 0 20 0 25 0 29 
		0;
	setAttr -s 9 ".kit[2:8]"  1 3 3 10 10 10 3;
	setAttr -s 9 ".kot[2:8]"  1 3 3 10 10 10 3;
	setAttr -s 9 ".kix[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[2:8]"  0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[2:8]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "tank_R_footRoll_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 24.001932629614718 2 0 5 69.325592515814634 
		6 69.325592515814634 7 69.325592515814634 11 69.325592515814634 17 34.662842744342385 
		20 0 25 0 29 0;
	setAttr -s 10 ".kit[3:9]"  1 3 3 10 10 10 3;
	setAttr -s 10 ".kot[3:9]"  1 3 3 10 10 10 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 0.24065525829792023 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 -0.97061061859130859 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 0.24065525829792023 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 -0.97061061859130859 0 0 0;
createNode animCurveTU -n "tank_L_footRoll_ctrl_slide";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 5 0 6 0 7 0 11 0 18 0 21 0 25 0 
		29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_L_footRoll_ctrl_clampHeel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 100 2 45 5 45 6 45 7 45 11 45 18 45 21 
		45 25 45 29 45;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_L_footRoll_ctrl_clampToe";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 100 2 45 5 45 6 45 7 45 11 45 18 45 21 
		45 25 45 29 45;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_L_footRoll_ctrl_clampSideToSide";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 100 2 45 5 45 6 45 7 45 11 45 18 45 21 
		45 25 45 29 45;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "tank_L_footRoll_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 5 0 6 0 7 0 11 0 18 0 21 0 25 0 
		29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "tank_L_footRoll_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 5 0 6 0 7 0 11 0 18 0 21 0 25 0 
		29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_R_fingers_ctrl_mittenRoll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 5 0 6 0 7 0 11 0 17 0 20 0 25 0 
		29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_R_fingers_ctrl_indexRoll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 5 0 6 0 7 0 11 0 17 0 20 0 25 0 
		29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_R_fingers_ctrl_mittenC";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 63.300000000000004 2 0 5 0 6 0 7 0 11 
		0 17 0 20 0 25 0 29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_R_fingers_ctrl_mittenB";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 63.300000000000004 2 0 5 0 6 0 7 0 11 
		0 17 0 20 0 25 0 29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_R_fingers_ctrl_mittenA";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 41.2 2 0 5 0 6 0 7 0 11 0 17 0 20 0 25 
		0 29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_R_fingers_ctrl_mittenSpread";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 5 0 6 0 7 0 11 0 17 0 20 0 25 0 
		29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_R_fingers_ctrl_indexC";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 63.300000000000004 2 0 5 0 6 0 7 0 11 
		0 17 0 20 0 25 0 29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_R_fingers_ctrl_indexB";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 63.300000000000004 2 0 5 0 6 0 7 0 11 
		0 17 0 20 0 25 0 29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_R_fingers_ctrl_indexA";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 41.2 2 0 5 0 6 0 7 0 11 0 17 0 20 0 25 
		0 29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_R_fingers_ctrl_indexSpread";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 5 0 6 0 7 0 11 0 17 0 20 0 25 0 
		29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_R_fingers_ctrl_thumbB";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 63.300000000000004 2 0 5 0 6 0 7 0 11 
		0 17 0 20 0 25 0 29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_R_fingers_ctrl_thumbA";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 26.800000000000004 2 0 5 0 6 0 7 0 11 
		0 17 0 20 0 25 0 29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "tank_R_fingers_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -31.011121823005837 2 0 5 0 6 0 7 0 11 
		0 17 0 20 0 25 0 29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "tank_R_fingers_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -18.132561944637335 2 0 5 0 6 0 7 0 11 
		0 17 0 20 0 25 0 29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "tank_R_fingers_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 45.106937981007185 2 0 5 0 6 0 7 0 11 
		0 17 0 20 0 25 0 29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_L_fingers_ctrl_mittenRoll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 5 0 6 0 7 0 11 0 17 0 20 0 25 0 
		29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_L_fingers_ctrl_indexRoll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 5 0 6 0 7 0 11 0 17 0 20 0 25 0 
		29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_L_fingers_ctrl_mittenC";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 63.300000000000004 2 0 5 0 6 0 7 0 11 
		0 17 0 20 0 25 0 29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_L_fingers_ctrl_mittenB";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 63.300000000000004 2 0 5 0 6 0 7 0 11 
		0 17 0 20 0 25 0 29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_L_fingers_ctrl_mittenA";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 41.2 2 0 5 0 6 0 7 0 11 0 17 0 20 0 25 
		0 29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_L_fingers_ctrl_mittenSpread";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 5 0 6 0 7 0 11 0 17 0 20 0 25 0 
		29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_L_fingers_ctrl_indexC";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 63.300000000000004 2 0 5 0 6 0 7 0 11 
		0 17 0 20 0 25 0 29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_L_fingers_ctrl_indexB";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 63.300000000000004 2 0 5 0 6 0 7 0 11 
		0 17 0 20 0 25 0 29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_L_fingers_ctrl_indexA";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 41.2 2 0 5 0 6 0 7 0 11 0 17 0 20 0 25 
		0 29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_L_fingers_ctrl_indexSpread";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 5 0 6 0 7 0 11 0 17 0 20 0 25 0 
		29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_L_fingers_ctrl_thumbB";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 63.300000000000004 2 0 5 0 6 0 7 0 11 
		0 17 0 20 0 25 0 29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "tank_L_fingers_ctrl_thumbA";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 26.800000000000004 2 0 5 0 6 0 7 0 11 
		0 17 0 20 0 25 0 29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "tank_L_fingers_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 5 0 6 0 7 0 11 0 17 0 20 0 25 0 
		29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "tank_L_fingers_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 5 0 6 0 7 0 11 0 17 0 20 0 25 0 
		29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "tank_L_fingers_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 5 0 6 0 7 0 11 0 17 0 20 0 25 0 
		29 0;
	setAttr -s 10 ".kit[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kot[1:9]"  1 10 1 3 3 10 10 10 
		3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "tank_chest_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 14 2 -53.929516523207248 5 -47.394409309584972 
		7 -52.055309565669837 11 -52.055309565669837 16 -61.266923721448528 20 -76.608442856164459 
		29 -6.7832614176793165;
	setAttr -s 8 ".kit[1:7]"  1 10 3 3 10 10 3;
	setAttr -s 8 ".kot[1:7]"  1 10 3 3 10 10 3;
	setAttr -s 8 ".kix[1:7]"  1 0.98127889633178711 1 1 0.57349687814712524 
		0.41467294096946716 1;
	setAttr -s 8 ".kiy[1:7]"  0 0.19259217381477356 0 0 -0.81920778751373291 
		0.90997046232223511 0;
	setAttr -s 8 ".kox[1:7]"  1 0.98127889633178711 1 1 0.57349687814712524 
		0.41467294096946716 1;
	setAttr -s 8 ".koy[1:7]"  0 0.19259217381477356 0 0 -0.81920778751373291 
		0.90997046232223511 0;
createNode animCurveTA -n "tank_chest_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 -3.308839592621569 5 -2.6848077388773079 
		7 -2.7821150996320121 11 -2.7821150996320121 16 -3.0852095132631372 20 -3.2920491192361152 
		29 0;
	setAttr -s 8 ".kit[1:7]"  9 10 3 3 10 10 3;
	setAttr -s 8 ".kot[1:7]"  9 10 3 3 10 10 3;
createNode animCurveTA -n "tank_chest_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0.065008666841117446 5 0.79554482516342184 
		7 0.98432879515830907 11 0.98432879515830907 16 1.4504174006891402 20 2.0935339805069186 
		29 0;
	setAttr -s 8 ".kit[1:7]"  1 1 3 3 10 10 3;
	setAttr -s 8 ".kot[1:7]"  1 1 3 3 10 10 3;
	setAttr -s 8 ".kix[1:7]"  1 0.99969881772994995 1 1 1 1 1;
	setAttr -s 8 ".kiy[1:7]"  0 -0.024541532620787621 0 0 0 0 0;
	setAttr -s 8 ".kox[1:7]"  1 0.99969881772994995 1 1 1 1 1;
	setAttr -s 8 ".koy[1:7]"  0 -0.024541532620787621 0 0 0 0 0;
createNode animCurveTA -n "tank_hips_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -8.754350408666415 5 -23.40802839708229 
		7 3.4930412180378121 18 5.4292121524765617 23 -18.097558865096808 25 -7.8771317177034463 
		29 -17.428736070727251;
	setAttr -s 7 ".kit[1:6]"  1 10 10 10 10 3;
	setAttr -s 7 ".kot[1:6]"  1 10 10 10 10 3;
	setAttr -s 7 ".kix[1:6]"  1 1 1 0.70876604318618774 0.99830108880996704 
		1;
	setAttr -s 7 ".kiy[1:6]"  0 0 0 -0.7054436206817627 0.058266643434762955 
		0;
	setAttr -s 7 ".kox[1:6]"  1 1 1 0.70876604318618774 0.99830108880996704 
		1;
	setAttr -s 7 ".koy[1:6]"  0 0 0 -0.7054436206817627 0.058266643434762955 
		0;
createNode animCurveTA -n "tank_hips_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 1.2484492492031887 7 1.313472391972119 
		18 6.7318990668693264 23 1.7279698694564014 25 1.1111855803323996 29 0;
	setAttr -s 7 ".kit[1:6]"  1 10 10 10 10 3;
	setAttr -s 7 ".kot[1:6]"  1 10 10 10 10 3;
	setAttr -s 7 ".kix[1:6]"  1 1 0.99990808963775635 1 1 1;
	setAttr -s 7 ".kiy[1:6]"  0 0 0.013563152402639389 0 0 0;
	setAttr -s 7 ".kox[1:6]"  1 1 0.99990808963775635 1 1 1;
	setAttr -s 7 ".koy[1:6]"  0 0 0.013563152402639389 0 0 0;
createNode animCurveTA -n "tank_hips_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 3.388960132427024 5 6.2030799896039071 
		7 -0.80621963835905397 18 5.9872291544501808 23 0.82613677851409173 25 -0.6701028257466255 
		29 0;
	setAttr -s 7 ".kit[1:6]"  1 10 10 10 10 3;
	setAttr -s 7 ".kot[1:6]"  1 10 10 10 10 3;
	setAttr -s 7 ".kix[1:6]"  1 0.9999622106552124 0.99857628345489502 
		1 1 1;
	setAttr -s 7 ".kiy[1:6]"  0 -0.0086934585124254227 0.053342688828706741 
		0 0 0;
	setAttr -s 7 ".kox[1:6]"  1 0.9999622106552124 0.99857628345489502 
		1 1 1;
	setAttr -s 7 ".koy[1:6]"  0 -0.0086934585124254227 0.053342688828706741 
		0 0 0;
createNode animCurveTL -n "tank_R_arm_elbowIk_ctrl_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -0.64570446860013975 1 -0.27573255241351785 
		2 -0.78447714226657761 5 -0.78447714226657761 6 -0.7104120775407885 7 -0.7104120775407885 
		11 -0.7104120775407885 16 -0.85280258056772862 20 -0.68347755020518375 25 -0.43691264761877391 
		29 -0.30197856268412637;
	setAttr -s 11 ".kit[2:10]"  3 3 3 3 1 10 10 10 
		3;
	setAttr -s 11 ".kot[2:10]"  3 3 3 3 1 10 10 10 
		3;
	setAttr -s 11 ".kix[6:10]"  0.71829676628112793 0.99599373340606689 
		0.5850226879119873 0.61814093589782715 1;
	setAttr -s 11 ".kiy[6:10]"  0.69573682546615601 0.089422069489955902 
		0.81101691722869873 0.78606730699539185 0;
	setAttr -s 11 ".kox[6:10]"  0.71829676628112793 0.99599373340606689 
		0.5850226879119873 0.61814093589782715 1;
	setAttr -s 11 ".koy[6:10]"  0.69573682546615601 0.089422069489955902 
		0.81101691722869873 0.78606730699539185 0;
createNode animCurveTL -n "tank_R_arm_elbowIk_ctrl_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -0.61491768886155418 1 -0.46171813344011942 
		2 -1.1539520904663298 5 -1.3875445439136005 6 -1.4248534096889012 7 -1.4248534096889012 
		11 -1.4248534096889012 16 -1.1685603248462648 20 -0.60243701848592823 25 -0.24196818962995542 
		29 -0.68322198261048583;
	setAttr -s 11 ".kit[2:10]"  3 3 3 3 1 10 10 10 
		3;
	setAttr -s 11 ".kot[2:10]"  3 3 3 3 1 10 10 10 
		3;
	setAttr -s 11 ".kix[6:10]"  1 0.34269076585769653 0.30802491307258606 
		0.9656030535697937 1;
	setAttr -s 11 ".kiy[6:10]"  0 0.93944829702377319 0.95137834548950195 
		-0.26002073287963867 0;
	setAttr -s 11 ".kox[6:10]"  1 0.34269076585769653 0.30802491307258606 
		0.9656030535697937 1;
	setAttr -s 11 ".koy[6:10]"  0 0.93944829702377319 0.95137834548950195 
		-0.26002073287963867 0;
createNode animCurveTL -n "tank_R_arm_elbowIk_ctrl_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -0.17978866471134988 1 -0.26011719066600369 
		2 -0.71944949423844518 5 -0.71944949423844518 6 -0.68140685216126207 7 -0.68140685216126207 
		11 -0.68140685216126207 16 -0.69410349039438612 20 -0.52732787512041379 25 -0.16687433936800367 
		29 -0.0013196526438615797;
	setAttr -s 11 ".kit[2:10]"  3 3 3 3 1 10 10 10 
		3;
	setAttr -s 11 ".kot[2:10]"  3 3 3 3 1 10 10 10 
		3;
	setAttr -s 11 ".kix[6:10]"  1 1 0.49455505609512329 0.49542152881622314 
		1;
	setAttr -s 11 ".kiy[6:10]"  0 0 0.86914628744125366 0.86865276098251343 
		0;
	setAttr -s 11 ".kox[6:10]"  1 1 0.49455505609512329 0.49542152881622314 
		1;
	setAttr -s 11 ".koy[6:10]"  0 0 0.86914628744125366 0.86865276098251343 
		0;
createNode animCurveTL -n "tank_L_arm_elbowIk_ctrl_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.56296936079974336 1 -0.1529435123807818 
		5 -0.54373721028808653 7 -0.57930802707313089 11 -0.57930802707313089 17 -0.45575149437201118 
		20 -0.41996608380022082 25 0.069689358592306239 29 -0.26875866938298265;
	setAttr -s 9 ".kit[2:8]"  3 3 3 10 10 10 3;
	setAttr -s 9 ".kot[2:8]"  3 3 3 10 10 10 3;
createNode animCurveTL -n "tank_L_arm_elbowIk_ctrl_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.23624536192382939 1 -0.23117617512470584 
		2 -1.2884989815806778 5 -1.4134640029553189 7 -1.4880817345059194 11 -1.4880817345059194 
		17 -1.1766908805551761 20 -1.1857062763465538 25 -0.25651095277577246 29 -0.73360091157126917;
	setAttr -s 10 ".kit[2:9]"  3 3 3 3 10 10 10 3;
	setAttr -s 10 ".kot[2:9]"  3 3 3 3 10 10 10 3;
createNode animCurveTL -n "tank_L_arm_elbowIk_ctrl_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.1017281787361634 1 0.17716186322813793 
		5 0.36662208094318854 7 0.44270736509755543 11 0.44270736509755543 17 0.44570555911194526 
		20 0.47297796057907948 25 0.55645054103280334 29 0.040161846088425823;
	setAttr -s 9 ".kit[2:8]"  3 3 3 10 10 10 3;
	setAttr -s 9 ".kot[2:8]"  3 3 3 10 10 10 3;
createNode animCurveTA -n "tank_L_wrist_ik_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 12.045025413209775 1 -92.348395777247291 
		2 -92.348395777247291 11 -92.672694121628709 19 -84.434798163063434 23 -85.580567700698779 
		29 -33.014961581574795;
	setAttr -s 7 ".kit[0:6]"  10 3 3 3 10 10 3;
	setAttr -s 7 ".kot[0:6]"  10 3 3 3 10 10 3;
createNode animCurveTA -n "tank_L_wrist_ik_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -9.621221798521443 1 52.603230620787677 
		2 52.603230620787684 11 57.745355853906354 19 39.787064421353776 29 53.701959296875678;
	setAttr -s 6 ".kit[0:5]"  10 3 3 3 10 3;
	setAttr -s 6 ".kot[0:5]"  10 3 3 3 10 3;
createNode animCurveTA -n "tank_L_wrist_ik_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -108.12047303225579 1 -73.095430924432335 
		2 -73.095430924432335 11 -73.490088265255977 19 -63.980008863886852 29 25.449476291659074;
	setAttr -s 6 ".kit[0:5]"  10 3 3 3 10 3;
	setAttr -s 6 ".kot[0:5]"  10 3 3 3 10 3;
createNode animCurveTL -n "tank_L_wrist_ik_ctrl_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.13652127140893242 1 -0.46849889351786567 
		2 -0.821 11 -0.78169558565512265 19 -0.84801784815644421 29 -0.48200086220201055;
	setAttr -s 6 ".kit[0:5]"  10 9 3 3 10 3;
	setAttr -s 6 ".kot[0:5]"  10 9 3 3 10 3;
createNode animCurveTL -n "tank_L_wrist_ik_ctrl_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.10993952279559771 1 -0.8235964207963804 
		2 -1.1230132479182053 11 -1.1738373746787074 19 -0.89089884028664224 29 -0.25008211660802959;
	setAttr -s 6 ".kit[0:5]"  10 9 3 3 10 3;
	setAttr -s 6 ".kot[0:5]"  10 9 3 3 10 3;
createNode animCurveTL -n "tank_L_wrist_ik_ctrl_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.095072060771691697 1 -0.32978548889830855 
		2 -0.33409053577119768 11 -0.33215165713157235 19 -0.37313386891947709 23 -0.47131657135316113 
		29 -0.23878132695572496;
	setAttr -s 7 ".kit[1:6]"  1 3 3 10 10 3;
	setAttr -s 7 ".kot[1:6]"  1 3 3 10 10 3;
	setAttr -s 7 ".kix[1:6]"  0.97998625040054321 1 1 1 0.92749553918838501 
		1;
	setAttr -s 7 ".kiy[1:6]"  -0.19906513392925262 0 0 0 0.37383416295051575 
		0;
	setAttr -s 7 ".kox[1:6]"  0.97998625040054321 1 1 1 0.92749553918838501 
		1;
	setAttr -s 7 ".koy[1:6]"  -0.19906511902809143 0 0 0 0.37383416295051575 
		0;
createNode animCurveTA -n "tank_R_wrist_ik_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -9.4788313115599525 1 91.100836135252692 
		2 95.002282027408583 11 95.67070667578389 19 86.376301216285 23 74.104588971774746 
		29 43.148863408286189;
	setAttr -s 7 ".kit[1:6]"  3 3 1 10 10 3;
	setAttr -s 7 ".kot[1:6]"  3 3 1 10 10 3;
	setAttr -s 7 ".kix[3:6]"  1 0.72826433181762695 0.40413016080856323 
		1;
	setAttr -s 7 ".kiy[3:6]"  0 -0.68529629707336426 -0.91470146179199219 
		0;
	setAttr -s 7 ".kox[3:6]"  1 0.72826433181762695 0.40413016080856323 
		1;
	setAttr -s 7 ".koy[3:6]"  0 -0.68529629707336426 -0.91470146179199219 
		0;
createNode animCurveTA -n "tank_R_wrist_ik_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10.636596698164576 1 -38.923548898794344 
		2 -51.810436450192476 11 -56.935282594332193 19 -40.441647508358031 23 -56.136172406163439 
		29 -39.634719780710149;
	setAttr -s 7 ".kit[1:6]"  3 3 1 10 10 3;
	setAttr -s 7 ".kot[1:6]"  3 3 1 10 10 3;
	setAttr -s 7 ".kix[3:6]"  1 0.99939262866973877 0.99910861253738403 
		1;
	setAttr -s 7 ".kiy[3:6]"  0 0.034846585243940353 0.042212978005409241 
		0;
	setAttr -s 7 ".kox[3:6]"  1 0.99939262866973877 0.99910861253738403 
		1;
	setAttr -s 7 ".koy[3:6]"  0 0.034846585243940353 0.042212978005409241 
		0;
createNode animCurveTA -n "tank_R_wrist_ik_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -86.674774112131288 1 -100.63960142736713 
		2 -103.43412926708633 11 -104.25564987806398 19 -94.568907182644949 23 -68.731948595009428 
		29 329.74227729815868;
	setAttr -s 7 ".kit[1:6]"  3 3 1 10 10 3;
	setAttr -s 7 ".kot[1:6]"  3 3 1 10 10 3;
	setAttr -s 7 ".kix[3:6]"  1 0.54212337732315063 0.044965289533138275 
		1;
	setAttr -s 7 ".kiy[3:6]"  0 0.84029883146286011 0.9989885687828064 
		0;
	setAttr -s 7 ".kox[3:6]"  1 0.54212337732315063 0.044965289533138275 
		1;
	setAttr -s 7 ".koy[3:6]"  0 0.84029883146286011 0.9989885687828064 
		0;
createNode animCurveTL -n "tank_R_wrist_ik_ctrl_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.15625416903744213 1 -0.51993402559398583 
		2 -0.85044657662326228 11 -0.81114216227838498 19 -0.86188114398380855 29 -0.42664090322610937;
	setAttr -s 6 ".kit[0:5]"  10 3 3 1 10 3;
	setAttr -s 6 ".kot[0:5]"  10 3 3 1 10 3;
	setAttr -s 6 ".kix[3:5]"  1 0.84195184707641602 1;
	setAttr -s 6 ".kiy[3:5]"  0 0.53955262899398804 0;
	setAttr -s 6 ".kox[3:5]"  1 0.84195184707641602 1;
	setAttr -s 6 ".koy[3:5]"  0 0.53955262899398804 0;
createNode animCurveTL -n "tank_R_wrist_ik_ctrl_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.070877447654346781 1 -0.70856815375296511 
		2 -1.0745477779523425 11 -1.1253719047128437 29 -0.24895072040176086;
	setAttr -s 5 ".kit[0:4]"  10 3 3 1 3;
	setAttr -s 5 ".kot[0:4]"  10 3 3 1 3;
	setAttr -s 5 ".kix[3:4]"  1 1;
	setAttr -s 5 ".kiy[3:4]"  0 0;
	setAttr -s 5 ".kox[3:4]"  1 1;
	setAttr -s 5 ".koy[3:4]"  0 0;
createNode animCurveTL -n "tank_R_wrist_ik_ctrl_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.03102517283121296 1 0.30598187672819044 
		2 0.27347849728758794 11 0.27541737592721327 19 0.33002330587733381 23 0.33103016476327629 
		29 0.20572056125233662;
	setAttr -s 7 ".kit[1:6]"  3 3 1 10 10 3;
	setAttr -s 7 ".kot[1:6]"  3 3 1 10 10 3;
	setAttr -s 7 ".kix[3:6]"  1 1 1 1;
	setAttr -s 7 ".kiy[3:6]"  0 0 0 0;
	setAttr -s 7 ".kox[3:6]"  1 1 1 1;
	setAttr -s 7 ".koy[3:6]"  0 0 0 0;
createNode lightLinker -n "lightLinker1";
	setAttr -s 7 ".lnk";
	setAttr -s 7 ".slnk";
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
	setAttr -s 7 ".st";
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
	setAttr -s 7 ".s";
select -ne :postProcessList1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -s 8 ".u";
select -ne :lightList1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
select -ne :defaultTextureList1;
	setAttr -s 5 ".tx";
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
	setAttr -av -k on ".bfs";
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
connectAttr "ability4_3Source.cl" "clipLibrary1.sc[0]";
connectAttr "tank_R_arm_ctrl_fkIk.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "tank_L_arm_ctrl_fkIk.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "tank_R_upArm_fk_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "tank_R_upArm_fk_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "tank_R_upArm_fk_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "tank_R_elbow_fk_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "tank_R_wrist_fk_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "tank_R_wrist_fk_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "tank_R_wrist_fk_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "tank_R_shoulder_fk_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[9].cevr"
		;
connectAttr "tank_R_shoulder_fk_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[10].cevr"
		;
connectAttr "animCurveTA98.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "animCurveTA99.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "tank_L_upArm_fk_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "tank_L_upArm_fk_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "tank_L_upArm_fk_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "tank_L_elbow_fk_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "tank_L_wrist_fk_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "tank_L_wrist_fk_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "tank_L_wrist_fk_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "tank_M_neck_fk_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "tank_M_neck_fk_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "tank_M_neck_fk_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "tank_M_head_fk_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "tank_M_head_fk_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "tank_M_head_fk_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "tank_R_leg_kneeIk_ctrl_translateZ.a" "clipLibrary1.cel[0].cev[26].cevr"
		;
connectAttr "tank_R_leg_kneeIk_ctrl_translateY.a" "clipLibrary1.cel[0].cev[27].cevr"
		;
connectAttr "tank_R_leg_kneeIk_ctrl_translateX.a" "clipLibrary1.cel[0].cev[28].cevr"
		;
connectAttr "tank_L_leg_kneeIk_ctrl_translateZ.a" "clipLibrary1.cel[0].cev[29].cevr"
		;
connectAttr "tank_L_leg_kneeIk_ctrl_translateY.a" "clipLibrary1.cel[0].cev[30].cevr"
		;
connectAttr "tank_L_leg_kneeIk_ctrl_translateX.a" "clipLibrary1.cel[0].cev[31].cevr"
		;
connectAttr "tank_com_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "tank_com_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "tank_com_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "tank_com_ctrl_translateZ.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "tank_com_ctrl_translateY.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "tank_com_ctrl_translateX.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "tank_R_foot_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "tank_R_foot_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "tank_R_foot_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "tank_R_foot_ctrl_translateZ.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "tank_R_foot_ctrl_translateY.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "tank_R_foot_ctrl_translateX.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "tank_L_foot_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "tank_L_foot_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "tank_L_foot_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "tank_L_foot_ctrl_translateZ.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "tank_L_foot_ctrl_translateY.a" "clipLibrary1.cel[0].cev[48].cevr";
connectAttr "tank_L_foot_ctrl_translateX.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "tank_R_mace_ctrl_parent.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "tank_R_mace_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "tank_R_mace_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "tank_R_mace_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "tank_R_mace_ctrl_translateZ.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "tank_R_mace_ctrl_translateY.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "tank_R_mace_ctrl_translateX.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "tank_L_mace_ctrl_parent.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "tank_L_mace_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "tank_L_mace_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "tank_L_mace_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "tank_L_mace_ctrl_translateZ.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "tank_L_mace_ctrl_translateY.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "tank_L_mace_ctrl_translateX.a" "clipLibrary1.cel[0].cev[63].cevr";
connectAttr "tank_R_footRoll_ctrl_slide.a" "clipLibrary1.cel[0].cev[64].cevr";
connectAttr "tank_R_footRoll_ctrl_clampHeel.a" "clipLibrary1.cel[0].cev[65].cevr"
		;
connectAttr "tank_R_footRoll_ctrl_clampToe.a" "clipLibrary1.cel[0].cev[66].cevr"
		;
connectAttr "tank_R_footRoll_ctrl_clampSideToSide.a" "clipLibrary1.cel[0].cev[67].cevr"
		;
connectAttr "tank_R_footRoll_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "tank_R_footRoll_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "tank_L_footRoll_ctrl_slide.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "tank_L_footRoll_ctrl_clampHeel.a" "clipLibrary1.cel[0].cev[71].cevr"
		;
connectAttr "tank_L_footRoll_ctrl_clampToe.a" "clipLibrary1.cel[0].cev[72].cevr"
		;
connectAttr "tank_L_footRoll_ctrl_clampSideToSide.a" "clipLibrary1.cel[0].cev[73].cevr"
		;
connectAttr "tank_L_footRoll_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "tank_L_footRoll_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "tank_R_fingers_ctrl_mittenRoll.a" "clipLibrary1.cel[0].cev[76].cevr"
		;
connectAttr "tank_R_fingers_ctrl_indexRoll.a" "clipLibrary1.cel[0].cev[77].cevr"
		;
connectAttr "tank_R_fingers_ctrl_mittenC.a" "clipLibrary1.cel[0].cev[78].cevr";
connectAttr "tank_R_fingers_ctrl_mittenB.a" "clipLibrary1.cel[0].cev[79].cevr";
connectAttr "tank_R_fingers_ctrl_mittenA.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "tank_R_fingers_ctrl_mittenSpread.a" "clipLibrary1.cel[0].cev[81].cevr"
		;
connectAttr "tank_R_fingers_ctrl_indexC.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "tank_R_fingers_ctrl_indexB.a" "clipLibrary1.cel[0].cev[83].cevr";
connectAttr "tank_R_fingers_ctrl_indexA.a" "clipLibrary1.cel[0].cev[84].cevr";
connectAttr "tank_R_fingers_ctrl_indexSpread.a" "clipLibrary1.cel[0].cev[85].cevr"
		;
connectAttr "tank_R_fingers_ctrl_thumbB.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "tank_R_fingers_ctrl_thumbA.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "tank_R_fingers_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "tank_R_fingers_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr "tank_R_fingers_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "tank_L_fingers_ctrl_mittenRoll.a" "clipLibrary1.cel[0].cev[91].cevr"
		;
connectAttr "tank_L_fingers_ctrl_indexRoll.a" "clipLibrary1.cel[0].cev[92].cevr"
		;
connectAttr "tank_L_fingers_ctrl_mittenC.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "tank_L_fingers_ctrl_mittenB.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "tank_L_fingers_ctrl_mittenA.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "tank_L_fingers_ctrl_mittenSpread.a" "clipLibrary1.cel[0].cev[96].cevr"
		;
connectAttr "tank_L_fingers_ctrl_indexC.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "tank_L_fingers_ctrl_indexB.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "tank_L_fingers_ctrl_indexA.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "tank_L_fingers_ctrl_indexSpread.a" "clipLibrary1.cel[0].cev[100].cevr"
		;
connectAttr "tank_L_fingers_ctrl_thumbB.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "tank_L_fingers_ctrl_thumbA.a" "clipLibrary1.cel[0].cev[102].cevr";
connectAttr "tank_L_fingers_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[103].cevr";
connectAttr "tank_L_fingers_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[104].cevr";
connectAttr "tank_L_fingers_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[105].cevr";
connectAttr "tank_chest_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[106].cevr";
connectAttr "tank_chest_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[107].cevr";
connectAttr "tank_chest_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[108].cevr";
connectAttr "tank_hips_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[109].cevr";
connectAttr "tank_hips_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[110].cevr";
connectAttr "tank_hips_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[111].cevr";
connectAttr "tank_R_arm_elbowIk_ctrl_translateZ.a" "clipLibrary1.cel[0].cev[112].cevr"
		;
connectAttr "tank_R_arm_elbowIk_ctrl_translateY.a" "clipLibrary1.cel[0].cev[113].cevr"
		;
connectAttr "tank_R_arm_elbowIk_ctrl_translateX.a" "clipLibrary1.cel[0].cev[114].cevr"
		;
connectAttr "tank_L_arm_elbowIk_ctrl_translateZ.a" "clipLibrary1.cel[0].cev[115].cevr"
		;
connectAttr "tank_L_arm_elbowIk_ctrl_translateY.a" "clipLibrary1.cel[0].cev[116].cevr"
		;
connectAttr "tank_L_arm_elbowIk_ctrl_translateX.a" "clipLibrary1.cel[0].cev[117].cevr"
		;
connectAttr "tank_L_wrist_ik_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[118].cevr"
		;
connectAttr "tank_L_wrist_ik_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[119].cevr"
		;
connectAttr "tank_L_wrist_ik_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[120].cevr"
		;
connectAttr "tank_L_wrist_ik_ctrl_translateZ.a" "clipLibrary1.cel[0].cev[121].cevr"
		;
connectAttr "tank_L_wrist_ik_ctrl_translateY.a" "clipLibrary1.cel[0].cev[122].cevr"
		;
connectAttr "tank_L_wrist_ik_ctrl_translateX.a" "clipLibrary1.cel[0].cev[123].cevr"
		;
connectAttr "tank_R_wrist_ik_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[124].cevr"
		;
connectAttr "tank_R_wrist_ik_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[125].cevr"
		;
connectAttr "tank_R_wrist_ik_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[126].cevr"
		;
connectAttr "tank_R_wrist_ik_ctrl_translateZ.a" "clipLibrary1.cel[0].cev[127].cevr"
		;
connectAttr "tank_R_wrist_ik_ctrl_translateY.a" "clipLibrary1.cel[0].cev[128].cevr"
		;
connectAttr "tank_R_wrist_ik_ctrl_translateX.a" "clipLibrary1.cel[0].cev[129].cevr"
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
// End of ability4_3.ma
