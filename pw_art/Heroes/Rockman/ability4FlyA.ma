//Maya ASCII 2008 scene
//Name: ability4_2.ma
//Last modified: Mon, Jul 27, 2009 01:24:28 PM
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
createNode animClip -n "ability4_2Source";
	setAttr ".ihi" 0;
	setAttr -s 130 ".ac[0:129]" yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".se" 10;
	setAttr ".ci" no;
createNode animCurveTU -n "tank_R_arm_ctrl_fkIk";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 5 1 10 1;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_L_arm_ctrl_fkIk";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 5 1 10 1;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_R_upArm_fk_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -89.455040683431079 5 -89.455040683431079 
		10 -89.455040683431079;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_R_upArm_fk_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -1.3764914370199928 5 -1.3764914370199928 
		10 -1.3764914370199928;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_R_upArm_fk_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -5.6400210530936121 5 -5.6400210530936121 
		10 -5.6400210530936121;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_R_elbow_fk_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 10 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_R_wrist_fk_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 10 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_R_wrist_fk_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 10 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_R_wrist_fk_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 10 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_R_shoulder_fk_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 2.0723375349424296 6 20.085085597832201 
		10 2.0723375349424296;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "tank_R_shoulder_fk_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.43937305726377879 6 -4.0370892739635824 
		10 -0.43937305726377879;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "animCurveTA98";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 6 10.339247172359283 10 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "animCurveTA99";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 6 -1.8161412054623887 10 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_L_upArm_fk_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -86.560064018088582 5 -86.560064018088582 
		10 -86.560064018088582;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_L_upArm_fk_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 3.3622449315456886 5 3.3622449315456886 
		10 3.3622449315456886;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_L_upArm_fk_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -22.879383758771784 5 -22.879383758771784 
		10 -22.879383758771784;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_L_elbow_fk_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 10 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_L_wrist_fk_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 10 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_L_wrist_fk_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 10 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_L_wrist_fk_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 10 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_M_neck_fk_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 24.189035444866914 3 24.194840721822771 
		7 15.675790997234765 10 24.189035444866914;
	setAttr -s 4 ".kit[0:3]"  3 10 10 3;
	setAttr -s 4 ".kot[0:3]"  3 10 10 3;
createNode animCurveTA -n "tank_M_neck_fk_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 3 1.8883153869021632 7 1.7021401132681495 
		10 0;
	setAttr -s 4 ".kit[0:3]"  3 10 10 3;
	setAttr -s 4 ".kot[0:3]"  3 10 10 3;
createNode animCurveTA -n "tank_M_neck_fk_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 3 -3.8931960299043387 7 -8.5315186865434818 
		10 0;
	setAttr -s 4 ".kit[0:3]"  3 10 10 3;
	setAttr -s 4 ".kot[0:3]"  3 10 10 3;
createNode animCurveTA -n "tank_M_head_fk_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -40.897138223406102 3 -41.745253124662703 
		7 -34.330874081207028 10 -40.897138223406102;
	setAttr -s 4 ".kit[0:3]"  3 10 10 3;
	setAttr -s 4 ".kot[0:3]"  3 10 10 3;
createNode animCurveTA -n "tank_M_head_fk_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1.6788139529320265 3 2.7457274299068164 
		7 7.751436081653277 10 1.6788139529320265;
	setAttr -s 4 ".kit[0:3]"  3 10 10 3;
	setAttr -s 4 ".kot[0:3]"  3 10 10 3;
createNode animCurveTA -n "tank_M_head_fk_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -1.2527070794692798 3 3.2128174785967638 
		7 1.8478343020731967 10 -1.2527070794692798;
	setAttr -s 4 ".kit[0:3]"  3 10 10 3;
	setAttr -s 4 ".kot[0:3]"  3 10 10 3;
createNode animCurveTL -n "tank_R_leg_kneeIk_ctrl_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -0.068559431513433244 5 -0.068559431513433244 
		7 -0.068559431513433244 10 -0.068559431513433244;
	setAttr -s 4 ".kit[0:3]"  3 10 10 3;
	setAttr -s 4 ".kot[0:3]"  3 10 10 3;
createNode animCurveTL -n "tank_R_leg_kneeIk_ctrl_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -0.19392631490774814 5 -0.19392631490774814 
		7 -0.19392631490774814 10 -0.19392631490774814;
	setAttr -s 4 ".kit[0:3]"  3 10 10 3;
	setAttr -s 4 ".kot[0:3]"  3 10 10 3;
createNode animCurveTL -n "tank_R_leg_kneeIk_ctrl_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -0.41621523852525538 5 -0.57820668067311976 
		7 -0.64581989230266867 10 -0.41621523852525538;
	setAttr -s 4 ".kit[0:3]"  3 10 10 3;
	setAttr -s 4 ".kot[0:3]"  3 10 10 3;
createNode animCurveTL -n "tank_L_leg_kneeIk_ctrl_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.12430866650918489 5 -0.13398614220816762 
		10 0.12430866650918489;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "tank_L_leg_kneeIk_ctrl_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.21267695235768835 5 -0.17040048971538546 
		10 -0.21267695235768835;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "tank_L_leg_kneeIk_ctrl_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.20930625035219369 5 0.18619079920945292 
		10 0.20930625035219369;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_com_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 4.0303467086837745 5 6.424846032563722 
		10 4.0303467086837745;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_com_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 -0.44592461638157532 10 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_com_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -3.1995227445375076 5 0.75415460028643233 
		10 -3.1995227445375076;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "tank_com_ctrl_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.083905346187052851 5 -0.083905346187052851 
		10 -0.083905346187052851;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "tank_com_ctrl_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.18190998978057271 5 -0.20162430876385029 
		10 -0.18190998978057271;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "tank_com_ctrl_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.027094269865637972 5 -0.027094269865637972 
		10 -0.027094269865637972;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_R_foot_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -16.236770139599834 5 -20.440602486013244 
		10 -16.236770139599834;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "tank_R_foot_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 9.0929559364600507 10 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "tank_R_foot_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 29.469230096288687 5 26.098355933215647 
		10 29.469230096288687;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "tank_R_foot_ctrl_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.13237335523236018 5 0.12619266881229554 
		10 0.13237335523236018;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "tank_R_foot_ctrl_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.42950114909550519 5 0.48260195375449633 
		7 0.471730444323051 10 0.42950114909550519;
	setAttr -s 4 ".kit[0:3]"  3 10 10 1;
	setAttr -s 4 ".kot[0:3]"  3 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTL -n "tank_R_foot_ctrl_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.040093865534497591 5 0.034746899368593404 
		10 -0.040093865534497591;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "tank_L_foot_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.2955202959470657 5 2.3727491486068315 
		10 1.2955202959470657;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_L_foot_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -9.3172514171137504 5 4.8508182812115628 
		10 -9.3172514171137504;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_L_foot_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 49.719259945663509 5 66.269674503199596 
		10 49.719259945663509;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "tank_L_foot_ctrl_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.2400357145301461 5 0.25617221084762409 
		10 0.2400357145301461;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "tank_L_foot_ctrl_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.090333936745635501 5 -0.10460376710820096 
		10 -0.090333936745635501;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "tank_L_foot_ctrl_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.04101937684988706 5 0.01688244480624701 
		10 0.04101937684988706;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_R_mace_ctrl_parent";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 5 1 10 1;
	setAttr -s 3 ".kit[1:2]"  9 10;
	setAttr -s 3 ".kot[1:2]"  5 10;
createNode animCurveTA -n "tank_R_mace_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  10 0;
createNode animCurveTA -n "tank_R_mace_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  10 0;
createNode animCurveTA -n "tank_R_mace_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  10 0;
createNode animCurveTL -n "tank_R_mace_ctrl_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  10 -0.808;
createNode animCurveTL -n "tank_R_mace_ctrl_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  10 0;
createNode animCurveTL -n "tank_R_mace_ctrl_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  10 0;
createNode animCurveTU -n "tank_L_mace_ctrl_parent";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 5 1 10 1;
	setAttr -s 3 ".kit[1:2]"  9 10;
	setAttr -s 3 ".kot[1:2]"  5 10;
createNode animCurveTA -n "tank_L_mace_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  10 0;
createNode animCurveTA -n "tank_L_mace_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  10 0;
createNode animCurveTA -n "tank_L_mace_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  10 0;
createNode animCurveTL -n "tank_L_mace_ctrl_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  10 -0.80789537837891157;
createNode animCurveTL -n "tank_L_mace_ctrl_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  10 0;
createNode animCurveTL -n "tank_L_mace_ctrl_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  10 0;
createNode animCurveTU -n "tank_R_footRoll_ctrl_slide";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 10 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_R_footRoll_ctrl_clampHeel";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 45 5 45 10 45;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_R_footRoll_ctrl_clampToe";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 45 5 45 10 45;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_R_footRoll_ctrl_clampSideToSide";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 45 5 45 10 45;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_R_footRoll_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 10 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_R_footRoll_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 24.001932629614718 5 35.516752748825972 
		10 24.001932629614718;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_L_footRoll_ctrl_slide";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 10 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_L_footRoll_ctrl_clampHeel";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 100 5 100 10 100;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_L_footRoll_ctrl_clampToe";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 100 5 100 10 100;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_L_footRoll_ctrl_clampSideToSide";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 100 5 100 10 100;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_L_footRoll_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 10 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_L_footRoll_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 10 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_R_fingers_ctrl_mittenRoll";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 10 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_R_fingers_ctrl_indexRoll";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 10 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_R_fingers_ctrl_mittenC";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 63.300000000000004 5 63.300000000000004 
		10 63.300000000000004;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_R_fingers_ctrl_mittenB";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 63.300000000000004 5 63.300000000000004 
		10 63.300000000000004;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_R_fingers_ctrl_mittenA";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 41.2 5 41.2 10 41.2;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_R_fingers_ctrl_mittenSpread";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 10 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_R_fingers_ctrl_indexC";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 63.300000000000004 5 63.300000000000004 
		10 63.300000000000004;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_R_fingers_ctrl_indexB";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 63.300000000000004 5 63.300000000000004 
		10 63.300000000000004;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_R_fingers_ctrl_indexA";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 41.2 5 41.2 10 41.2;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_R_fingers_ctrl_indexSpread";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 10 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_R_fingers_ctrl_thumbB";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 63.300000000000004 5 63.300000000000004 
		10 63.300000000000004;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_R_fingers_ctrl_thumbA";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 26.800000000000004 5 26.800000000000004 
		10 26.800000000000004;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_R_fingers_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -31.011121823005837 5 -31.011121823005837 
		10 -31.011121823005837;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_R_fingers_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -18.132561944637335 5 -18.132561944637335 
		10 -18.132561944637335;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_R_fingers_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 45.106937981007185 5 45.106937981007185 
		10 45.106937981007185;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_L_fingers_ctrl_mittenRoll";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 10 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_L_fingers_ctrl_indexRoll";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 10 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_L_fingers_ctrl_mittenC";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 63.300000000000004 5 63.300000000000004 
		10 63.300000000000004;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_L_fingers_ctrl_mittenB";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 63.300000000000004 5 63.300000000000004 
		10 63.300000000000004;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_L_fingers_ctrl_mittenA";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 41.2 5 41.2 10 41.2;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_L_fingers_ctrl_mittenSpread";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 10 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_L_fingers_ctrl_indexC";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 63.300000000000004 5 63.300000000000004 
		10 63.300000000000004;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_L_fingers_ctrl_indexB";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 63.300000000000004 5 63.300000000000004 
		10 63.300000000000004;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_L_fingers_ctrl_indexA";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 41.2 5 41.2 10 41.2;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_L_fingers_ctrl_indexSpread";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 10 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_L_fingers_ctrl_thumbB";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 63.300000000000004 5 63.300000000000004 
		10 63.300000000000004;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "tank_L_fingers_ctrl_thumbA";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 26.800000000000004 5 26.800000000000004 
		10 26.800000000000004;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_L_fingers_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 10 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_L_fingers_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 10 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_L_fingers_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 10 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_chest_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 14 3 20.403542687830953 7 16.705259247196445 
		10 14;
	setAttr -s 4 ".kit[0:3]"  3 10 10 3;
	setAttr -s 4 ".kot[0:3]"  3 10 10 3;
createNode animCurveTA -n "tank_chest_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 3 0.7125050854892685 7 0.4860233738406472 
		10 0;
	setAttr -s 4 ".kit[0:3]"  3 10 10 3;
	setAttr -s 4 ".kot[0:3]"  3 10 10 3;
createNode animCurveTA -n "tank_chest_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 3 0.36250898045161417 7 0.21854385858021363 
		10 0;
	setAttr -s 4 ".kit[0:3]"  3 10 10 3;
	setAttr -s 4 ".kot[0:3]"  3 10 10 3;
createNode animCurveTA -n "tank_hips_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -8.754350408666415 3 -3.3979260666701792 
		7 -2.8116225309699452 10 -8.754350408666415;
	setAttr -s 4 ".kit[0:3]"  3 10 10 3;
	setAttr -s 4 ".kot[0:3]"  3 10 10 3;
createNode animCurveTA -n "tank_hips_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 3 0.61476763672088397 7 -4.5410281495671834 
		10 0;
	setAttr -s 4 ".kit[0:3]"  1 10 10 1;
	setAttr -s 4 ".kot[0:3]"  1 10 10 1;
	setAttr -s 4 ".kix[0:3]"  0.98276704549789429 1 0.99894446134567261 
		0.99003911018371582;
	setAttr -s 4 ".kiy[0:3]"  0.18484844267368317 0 -0.045935969799757004 
		0.14079263806343079;
	setAttr -s 4 ".kox[0:3]"  0.98276704549789429 1 0.99894446134567261 
		0.99003911018371582;
	setAttr -s 4 ".koy[0:3]"  0.18484833836555481 0 -0.045935969799757004 
		0.14079263806343079;
createNode animCurveTA -n "tank_hips_ctrl_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 3.388960132427024 3 9.7724348462547717 
		7 -14.608169334134731 10 3.388960132427024;
	setAttr -s 4 ".kit[1:3]"  3 10 1;
	setAttr -s 4 ".kot[1:3]"  3 10 1;
	setAttr -s 4 ".kix[3]"  0.5713803768157959;
	setAttr -s 4 ".kiy[3]"  0.82068538665771484;
	setAttr -s 4 ".kox[3]"  0.57138031721115112;
	setAttr -s 4 ".koy[3]"  0.82068550586700439;
createNode animCurveTL -n "tank_R_arm_elbowIk_ctrl_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.64570446860013975 5 -0.64570446860013975 
		10 -0.64570446860013975;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "tank_R_arm_elbowIk_ctrl_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.61491768886155418 5 -0.61491768886155418 
		10 -0.61491768886155418;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "tank_R_arm_elbowIk_ctrl_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.17978866471134988 5 -0.17978866471134988 
		10 -0.17978866471134988;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "tank_L_arm_elbowIk_ctrl_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.56296936079974336 10 -0.56296936079974336;
createNode animCurveTL -n "tank_L_arm_elbowIk_ctrl_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.23624536192382939 10 -0.23624536192382939;
createNode animCurveTL -n "tank_L_arm_elbowIk_ctrl_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.1017281787361634 10 0.1017281787361634;
createNode animCurveTA -n "tank_L_wrist_ik_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 12.045025413209775 4 12.325294388642586 
		6 12.252632061678526 10 12.045025413209778;
	setAttr -s 4 ".kit[0:3]"  1 10 10 3;
	setAttr -s 4 ".kot[0:3]"  1 10 10 3;
	setAttr -s 4 ".kix[0:3]"  1 1 1 1;
	setAttr -s 4 ".kiy[0:3]"  0 0 0 0;
	setAttr -s 4 ".kox[0:3]"  1 1 1 1;
	setAttr -s 4 ".koy[0:3]"  0 0 0 0;
createNode animCurveTA -n "tank_L_wrist_ik_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -9.621221798521443 4 -15.452880729222576 
		6 -13.940969154596356 10 -9.621221798521443;
	setAttr -s 4 ".kit[0:3]"  1 10 10 3;
	setAttr -s 4 ".kot[0:3]"  1 10 10 3;
	setAttr -s 4 ".kix[0:3]"  1 1 1 1;
	setAttr -s 4 ".kiy[0:3]"  0 0 0 0;
	setAttr -s 4 ".kox[0:3]"  1 1 1 1;
	setAttr -s 4 ".koy[0:3]"  0 0 0 0;
createNode animCurveTA -n "tank_L_wrist_ik_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -108.12047303225579 4 -109.40988980327363 
		6 -109.07559656634308 10 -108.12047303225579;
	setAttr -s 4 ".kit[0:3]"  1 10 10 3;
	setAttr -s 4 ".kot[0:3]"  1 10 10 3;
	setAttr -s 4 ".kix[0:3]"  1 1 1 1;
	setAttr -s 4 ".kiy[0:3]"  0 0 0 0;
	setAttr -s 4 ".kox[0:3]"  1 1 1 1;
	setAttr -s 4 ".koy[0:3]"  0 0 0 0;
createNode animCurveTL -n "tank_L_wrist_ik_ctrl_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -0.13652127140893242 4 -0.13675869153504031 
		6 -0.13660110539454168 10 -0.13652127140893242;
	setAttr -s 4 ".kit[0:3]"  1 10 10 3;
	setAttr -s 4 ".kot[0:3]"  1 10 10 3;
	setAttr -s 4 ".kix[0:3]"  1 1 1 1;
	setAttr -s 4 ".kiy[0:3]"  0 0 0 0;
	setAttr -s 4 ".kox[0:3]"  1 1 1 1;
	setAttr -s 4 ".koy[0:3]"  0 0 0 0;
createNode animCurveTL -n "tank_L_wrist_ik_ctrl_translateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.10993952279559771 6 0.1639771263120674 
		10 0.10993952279559771;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
	setAttr -s 3 ".kix[0:2]"  1 1 1;
	setAttr -s 3 ".kiy[0:2]"  0 0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode animCurveTL -n "tank_L_wrist_ik_ctrl_translateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.095072060771691697 6 -0.13933284874715829 
		10 -0.095072060771691697;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
	setAttr -s 3 ".kix[0:2]"  1 1 1;
	setAttr -s 3 ".kiy[0:2]"  0 0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode animCurveTA -n "tank_R_wrist_ik_ctrl_rotateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -9.4788313115599525 3 -10.320302007483241 
		10 -9.4788313115599472;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
	setAttr -s 3 ".kix[0:2]"  1 1 1;
	setAttr -s 3 ".kiy[0:2]"  0 0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode animCurveTA -n "tank_R_wrist_ik_ctrl_rotateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 10.636596698164576 3 15.868547869016764 
		10 10.636596698164576;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
	setAttr -s 3 ".kix[0:2]"  1 1 1;
	setAttr -s 3 ".kiy[0:2]"  0 0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode animCurveTA -n "tank_R_wrist_ik_ctrl_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -86.674774112131288 3 -89.101451588526061 
		10 -86.674774112131288;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
	setAttr -s 3 ".kix[0:2]"  1 1 1;
	setAttr -s 3 ".kiy[0:2]"  0 0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode animCurveTL -n "tank_R_wrist_ik_ctrl_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -0.15625416903744213 3 -0.13528214017471724 
		6 -0.14320691621205497 10 -0.15625416903744213;
	setAttr -s 4 ".kit[0:3]"  1 10 10 3;
	setAttr -s 4 ".kot[0:3]"  1 10 10 3;
	setAttr -s 4 ".kix[0:3]"  1 1 1 1;
	setAttr -s 4 ".kiy[0:3]"  0 0 0 0;
	setAttr -s 4 ".kox[0:3]"  1 1 1 1;
	setAttr -s 4 ".koy[0:3]"  0 0 0 0;
createNode animCurveTL -n "tank_R_wrist_ik_ctrl_translateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.070877447654346781 6 0.1351982316070689 
		10 0.070877447654346781;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
	setAttr -s 3 ".kix[0:2]"  1 1 1;
	setAttr -s 3 ".kiy[0:2]"  0 0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode animCurveTL -n "tank_R_wrist_ik_ctrl_translateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.03102517283121296 6 0.082060122547848363 
		10 0.03102517283121296;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
	setAttr -s 3 ".kix[0:2]"  1 1 1;
	setAttr -s 3 ".kiy[0:2]"  0 0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
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
connectAttr "ability4_2Source.cl" "clipLibrary1.sc[0]";
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
// End of ability4_2.ma
