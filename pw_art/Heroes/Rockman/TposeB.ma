//Maya ASCII 2008 scene
//Name: TposeB.ma
//Last modified: Wed, Aug 12, 2009 02:39:53 PM
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
	setAttr -s 124 ".cel[0].cev";
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
createNode animClip -n "skinPoseBSource";
	setAttr ".ihi" 0;
	setAttr -s 124 ".ac";
	setAttr ".ac[0:111]" no no yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes no no no no no no yes yes yes no 
		no no yes yes yes no no no yes yes yes no no no no yes yes yes no no no no yes yes 
		yes no no no no no no no yes yes no no no no yes yes no no no no no no no no no no 
		no no yes yes yes no no no no no no no no no no no no yes yes yes yes yes yes yes 
		yes yes;
	setAttr ".ac[115:123]" yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[142:144]" yes yes yes;
	setAttr ".se" 2;
	setAttr ".ci" no;
createNode animCurveTU -n "animCurveTU354";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU355";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA957";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA958";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA959";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA960";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA961";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA962";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA963";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA964";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA965";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA966";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA967";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA968";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA969";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA970";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA971";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA972";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA973";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA974";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA975";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA976";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA977";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA978";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA979";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA980";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "animCurveTL361";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "animCurveTL362";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "animCurveTL363";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "animCurveTL364";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "animCurveTL365";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "animCurveTL366";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA981";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA982";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA983";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "animCurveTL367";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "animCurveTL368";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "animCurveTL369";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA984";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA985";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA986";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "animCurveTL370";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "animCurveTL371";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "animCurveTL372";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA987";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA988";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA989";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "animCurveTL373";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "animCurveTL374";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "animCurveTL375";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU356";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA990";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA991";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA992";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "animCurveTL376";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -0.81944359671150613;
createNode animCurveTL -n "animCurveTL377";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -7.9552118737661725e-011;
createNode animCurveTL -n "animCurveTL378";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0.0087141990168126959;
createNode animCurveTU -n "animCurveTU357";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA993";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA994";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA995";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "animCurveTL379";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -0.80451419482641451;
createNode animCurveTL -n "animCurveTL380";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -2.4945889741368431e-013;
createNode animCurveTL -n "animCurveTL381";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -0.0085562672260772743;
createNode animCurveTU -n "animCurveTU358";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU359";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 45;
createNode animCurveTU -n "animCurveTU360";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 45;
createNode animCurveTU -n "animCurveTU361";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 45;
createNode animCurveTA -n "animCurveTA996";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA997";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU362";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU363";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 45;
createNode animCurveTU -n "animCurveTU364";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 45;
createNode animCurveTU -n "animCurveTU365";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 45;
createNode animCurveTA -n "animCurveTA998";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA999";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU366";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU367";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU368";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU369";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU370";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU371";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU372";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU373";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU374";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU375";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU376";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU377";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA1000";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA1001";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA1002";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -2.5999764661798822e-011;
createNode animCurveTU -n "animCurveTU378";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU379";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU380";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU381";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU382";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU383";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU384";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU385";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU386";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU387";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU388";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "animCurveTU389";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA1003";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA1004";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA1005";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -2.5997909391022333e-011;
createNode animCurveTA -n "animCurveTA1006";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA1007";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA1008";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA1009";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA1010";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA1011";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "tank_M_hang_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "tank_M_hang_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "tank_M_hang_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "tank_R_hang_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "tank_R_hang_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "tank_R_hang_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "tank_L_hang_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "tank_L_hang_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "tank_L_hang_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "tank_M_backFeature_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "tank_M_backFeature_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "tank_M_backFeature_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode lightLinker -n "lightLinker1";
	setAttr -s 7 ".lnk";
	setAttr -s 7 ".slnk";
select -ne :time1;
	setAttr -av -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 1;
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
	setAttr -s 16 ".u";
select -ne :lightList1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
select -ne :defaultTextureList1;
	setAttr -s 6 ".tx";
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
	setAttr -k on ".bll";
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
	setAttr ".pa" 1;
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
	setAttr -s 2 ".st";
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
	setAttr -s 3 ".sol";
connectAttr "skinPoseBSource.cl" "clipLibrary2.sc[0]";
connectAttr "animCurveTU354.a" "clipLibrary2.cel[0].cev[0].cevr";
connectAttr "animCurveTU355.a" "clipLibrary2.cel[0].cev[1].cevr";
connectAttr "animCurveTA957.a" "clipLibrary2.cel[0].cev[2].cevr";
connectAttr "animCurveTA958.a" "clipLibrary2.cel[0].cev[3].cevr";
connectAttr "animCurveTA959.a" "clipLibrary2.cel[0].cev[4].cevr";
connectAttr "animCurveTA960.a" "clipLibrary2.cel[0].cev[5].cevr";
connectAttr "animCurveTA961.a" "clipLibrary2.cel[0].cev[6].cevr";
connectAttr "animCurveTA962.a" "clipLibrary2.cel[0].cev[7].cevr";
connectAttr "animCurveTA963.a" "clipLibrary2.cel[0].cev[8].cevr";
connectAttr "animCurveTA964.a" "clipLibrary2.cel[0].cev[9].cevr";
connectAttr "animCurveTA965.a" "clipLibrary2.cel[0].cev[10].cevr";
connectAttr "animCurveTA966.a" "clipLibrary2.cel[0].cev[11].cevr";
connectAttr "animCurveTA967.a" "clipLibrary2.cel[0].cev[12].cevr";
connectAttr "animCurveTA968.a" "clipLibrary2.cel[0].cev[13].cevr";
connectAttr "animCurveTA969.a" "clipLibrary2.cel[0].cev[14].cevr";
connectAttr "animCurveTA970.a" "clipLibrary2.cel[0].cev[15].cevr";
connectAttr "animCurveTA971.a" "clipLibrary2.cel[0].cev[16].cevr";
connectAttr "animCurveTA972.a" "clipLibrary2.cel[0].cev[17].cevr";
connectAttr "animCurveTA973.a" "clipLibrary2.cel[0].cev[18].cevr";
connectAttr "animCurveTA974.a" "clipLibrary2.cel[0].cev[19].cevr";
connectAttr "animCurveTA975.a" "clipLibrary2.cel[0].cev[20].cevr";
connectAttr "animCurveTA976.a" "clipLibrary2.cel[0].cev[21].cevr";
connectAttr "animCurveTA977.a" "clipLibrary2.cel[0].cev[22].cevr";
connectAttr "animCurveTA978.a" "clipLibrary2.cel[0].cev[23].cevr";
connectAttr "animCurveTA979.a" "clipLibrary2.cel[0].cev[24].cevr";
connectAttr "animCurveTA980.a" "clipLibrary2.cel[0].cev[25].cevr";
connectAttr "animCurveTL361.a" "clipLibrary2.cel[0].cev[26].cevr";
connectAttr "animCurveTL362.a" "clipLibrary2.cel[0].cev[27].cevr";
connectAttr "animCurveTL363.a" "clipLibrary2.cel[0].cev[28].cevr";
connectAttr "animCurveTL364.a" "clipLibrary2.cel[0].cev[29].cevr";
connectAttr "animCurveTL365.a" "clipLibrary2.cel[0].cev[30].cevr";
connectAttr "animCurveTL366.a" "clipLibrary2.cel[0].cev[31].cevr";
connectAttr "animCurveTA981.a" "clipLibrary2.cel[0].cev[32].cevr";
connectAttr "animCurveTA982.a" "clipLibrary2.cel[0].cev[33].cevr";
connectAttr "animCurveTA983.a" "clipLibrary2.cel[0].cev[34].cevr";
connectAttr "animCurveTL367.a" "clipLibrary2.cel[0].cev[35].cevr";
connectAttr "animCurveTL368.a" "clipLibrary2.cel[0].cev[36].cevr";
connectAttr "animCurveTL369.a" "clipLibrary2.cel[0].cev[37].cevr";
connectAttr "animCurveTA984.a" "clipLibrary2.cel[0].cev[38].cevr";
connectAttr "animCurveTA985.a" "clipLibrary2.cel[0].cev[39].cevr";
connectAttr "animCurveTA986.a" "clipLibrary2.cel[0].cev[40].cevr";
connectAttr "animCurveTL370.a" "clipLibrary2.cel[0].cev[41].cevr";
connectAttr "animCurveTL371.a" "clipLibrary2.cel[0].cev[42].cevr";
connectAttr "animCurveTL372.a" "clipLibrary2.cel[0].cev[43].cevr";
connectAttr "animCurveTA987.a" "clipLibrary2.cel[0].cev[44].cevr";
connectAttr "animCurveTA988.a" "clipLibrary2.cel[0].cev[45].cevr";
connectAttr "animCurveTA989.a" "clipLibrary2.cel[0].cev[46].cevr";
connectAttr "animCurveTL373.a" "clipLibrary2.cel[0].cev[47].cevr";
connectAttr "animCurveTL374.a" "clipLibrary2.cel[0].cev[48].cevr";
connectAttr "animCurveTL375.a" "clipLibrary2.cel[0].cev[49].cevr";
connectAttr "animCurveTU356.a" "clipLibrary2.cel[0].cev[50].cevr";
connectAttr "animCurveTA990.a" "clipLibrary2.cel[0].cev[51].cevr";
connectAttr "animCurveTA991.a" "clipLibrary2.cel[0].cev[52].cevr";
connectAttr "animCurveTA992.a" "clipLibrary2.cel[0].cev[53].cevr";
connectAttr "animCurveTL376.a" "clipLibrary2.cel[0].cev[54].cevr";
connectAttr "animCurveTL377.a" "clipLibrary2.cel[0].cev[55].cevr";
connectAttr "animCurveTL378.a" "clipLibrary2.cel[0].cev[56].cevr";
connectAttr "animCurveTU357.a" "clipLibrary2.cel[0].cev[57].cevr";
connectAttr "animCurveTA993.a" "clipLibrary2.cel[0].cev[58].cevr";
connectAttr "animCurveTA994.a" "clipLibrary2.cel[0].cev[59].cevr";
connectAttr "animCurveTA995.a" "clipLibrary2.cel[0].cev[60].cevr";
connectAttr "animCurveTL379.a" "clipLibrary2.cel[0].cev[61].cevr";
connectAttr "animCurveTL380.a" "clipLibrary2.cel[0].cev[62].cevr";
connectAttr "animCurveTL381.a" "clipLibrary2.cel[0].cev[63].cevr";
connectAttr "animCurveTU358.a" "clipLibrary2.cel[0].cev[64].cevr";
connectAttr "animCurveTU359.a" "clipLibrary2.cel[0].cev[65].cevr";
connectAttr "animCurveTU360.a" "clipLibrary2.cel[0].cev[66].cevr";
connectAttr "animCurveTU361.a" "clipLibrary2.cel[0].cev[67].cevr";
connectAttr "animCurveTA996.a" "clipLibrary2.cel[0].cev[68].cevr";
connectAttr "animCurveTA997.a" "clipLibrary2.cel[0].cev[69].cevr";
connectAttr "animCurveTU362.a" "clipLibrary2.cel[0].cev[70].cevr";
connectAttr "animCurveTU363.a" "clipLibrary2.cel[0].cev[71].cevr";
connectAttr "animCurveTU364.a" "clipLibrary2.cel[0].cev[72].cevr";
connectAttr "animCurveTU365.a" "clipLibrary2.cel[0].cev[73].cevr";
connectAttr "animCurveTA998.a" "clipLibrary2.cel[0].cev[74].cevr";
connectAttr "animCurveTA999.a" "clipLibrary2.cel[0].cev[75].cevr";
connectAttr "animCurveTU366.a" "clipLibrary2.cel[0].cev[76].cevr";
connectAttr "animCurveTU367.a" "clipLibrary2.cel[0].cev[77].cevr";
connectAttr "animCurveTU368.a" "clipLibrary2.cel[0].cev[78].cevr";
connectAttr "animCurveTU369.a" "clipLibrary2.cel[0].cev[79].cevr";
connectAttr "animCurveTU370.a" "clipLibrary2.cel[0].cev[80].cevr";
connectAttr "animCurveTU371.a" "clipLibrary2.cel[0].cev[81].cevr";
connectAttr "animCurveTU372.a" "clipLibrary2.cel[0].cev[82].cevr";
connectAttr "animCurveTU373.a" "clipLibrary2.cel[0].cev[83].cevr";
connectAttr "animCurveTU374.a" "clipLibrary2.cel[0].cev[84].cevr";
connectAttr "animCurveTU375.a" "clipLibrary2.cel[0].cev[85].cevr";
connectAttr "animCurveTU376.a" "clipLibrary2.cel[0].cev[86].cevr";
connectAttr "animCurveTU377.a" "clipLibrary2.cel[0].cev[87].cevr";
connectAttr "animCurveTA1000.a" "clipLibrary2.cel[0].cev[88].cevr";
connectAttr "animCurveTA1001.a" "clipLibrary2.cel[0].cev[89].cevr";
connectAttr "animCurveTA1002.a" "clipLibrary2.cel[0].cev[90].cevr";
connectAttr "animCurveTU378.a" "clipLibrary2.cel[0].cev[91].cevr";
connectAttr "animCurveTU379.a" "clipLibrary2.cel[0].cev[92].cevr";
connectAttr "animCurveTU380.a" "clipLibrary2.cel[0].cev[93].cevr";
connectAttr "animCurveTU381.a" "clipLibrary2.cel[0].cev[94].cevr";
connectAttr "animCurveTU382.a" "clipLibrary2.cel[0].cev[95].cevr";
connectAttr "animCurveTU383.a" "clipLibrary2.cel[0].cev[96].cevr";
connectAttr "animCurveTU384.a" "clipLibrary2.cel[0].cev[97].cevr";
connectAttr "animCurveTU385.a" "clipLibrary2.cel[0].cev[98].cevr";
connectAttr "animCurveTU386.a" "clipLibrary2.cel[0].cev[99].cevr";
connectAttr "animCurveTU387.a" "clipLibrary2.cel[0].cev[100].cevr";
connectAttr "animCurveTU388.a" "clipLibrary2.cel[0].cev[101].cevr";
connectAttr "animCurveTU389.a" "clipLibrary2.cel[0].cev[102].cevr";
connectAttr "animCurveTA1003.a" "clipLibrary2.cel[0].cev[103].cevr";
connectAttr "animCurveTA1004.a" "clipLibrary2.cel[0].cev[104].cevr";
connectAttr "animCurveTA1005.a" "clipLibrary2.cel[0].cev[105].cevr";
connectAttr "animCurveTA1006.a" "clipLibrary2.cel[0].cev[106].cevr";
connectAttr "animCurveTA1007.a" "clipLibrary2.cel[0].cev[107].cevr";
connectAttr "animCurveTA1008.a" "clipLibrary2.cel[0].cev[108].cevr";
connectAttr "animCurveTA1009.a" "clipLibrary2.cel[0].cev[109].cevr";
connectAttr "animCurveTA1010.a" "clipLibrary2.cel[0].cev[110].cevr";
connectAttr "animCurveTA1011.a" "clipLibrary2.cel[0].cev[111].cevr";
connectAttr "tank_M_hang_ctrl_rotateZ1.a" "clipLibrary2.cel[0].cev[115].cevr";
connectAttr "tank_M_hang_ctrl_rotateY1.a" "clipLibrary2.cel[0].cev[116].cevr";
connectAttr "tank_M_hang_ctrl_rotateX1.a" "clipLibrary2.cel[0].cev[117].cevr";
connectAttr "tank_R_hang_ctrl_rotateZ1.a" "clipLibrary2.cel[0].cev[118].cevr";
connectAttr "tank_R_hang_ctrl_rotateY1.a" "clipLibrary2.cel[0].cev[119].cevr";
connectAttr "tank_R_hang_ctrl_rotateX1.a" "clipLibrary2.cel[0].cev[120].cevr";
connectAttr "tank_L_hang_ctrl_rotateZ1.a" "clipLibrary2.cel[0].cev[121].cevr";
connectAttr "tank_L_hang_ctrl_rotateY1.a" "clipLibrary2.cel[0].cev[122].cevr";
connectAttr "tank_L_hang_ctrl_rotateX1.a" "clipLibrary2.cel[0].cev[123].cevr";
connectAttr "tank_M_backFeature_ctrl_rotateZ1.a" "clipLibrary2.cel[0].cev[142].cevr"
		;
connectAttr "tank_M_backFeature_ctrl_rotateY1.a" "clipLibrary2.cel[0].cev[143].cevr"
		;
connectAttr "tank_M_backFeature_ctrl_rotateX1.a" "clipLibrary2.cel[0].cev[144].cevr"
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
// End of TposeB.ma
