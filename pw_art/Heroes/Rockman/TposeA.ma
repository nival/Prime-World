//Maya ASCII 2008 scene
//Name: TposeA.ma
//Last modified: Thu, Aug 13, 2009 06:22:50 PM
//Codeset: 1251
requires maya "2008";
requires "Mayatomr" "9.0.1.4m - 3.6.51.0 ";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Complete 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200802250025-718075";
fileInfo "osv" "Microsoft Windows XP Service Pack 3 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 124 ".cel[0].cev";
	setAttr ".cd[0].cm" -type "characterMapping" 178 "R_arm_ctrl.fkIk" 0 1 "L_arm_ctrl.fkIk" 
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
		1 33 "L_leg_sknHelp_ctrl.translateZ" 1 34 "L_leg_sknHelp_ctrl.translateY" 
		1 35 "L_leg_sknHelp_ctrl.translateX" 1 36 "R_leg_sknHelp_ctrl.translateZ" 
		1 37 "R_leg_sknHelp_ctrl.translateY" 1 38 "R_leg_sknHelp_ctrl.translateX" 
		1 39 "transform.rotateZ" 2 98 "transform.rotateY" 2 99 "transform.rotateX" 
		2 100 "transform.translateZ" 1 40 "transform.translateY" 1 
		41 "transform.translateX" 1 42  ;
	setAttr ".cd[0].cim" -type "Int32Array" 178 0 1 2 3 4
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
		 161 162 163 164 165 166 167 168 169 170 171 172
		 173 174 175 176 177 ;
createNode animClip -n "skinPoseSource";
	setAttr ".ihi" 0;
	setAttr -s 124 ".ac";
	setAttr ".ac[0:111]" no no yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes no no no no no no yes yes yes no 
		no no yes yes yes no no no yes yes yes no no no no yes yes yes no no no no yes yes 
		yes no no no no no no no yes yes no no no no yes yes no no no no no no no no no no 
		no no yes yes yes no no no no no no no no no no no no yes yes yes yes yes yes yes 
		yes yes;
	setAttr ".ac[115:123]" no no no no no no no no no;
	setAttr ".ac[142:144]" no no no;
	setAttr ".se" 1;
	setAttr ".ci" no;
createNode animCurveTU -n "character1_R_arm_ctrl_fkIk";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_L_arm_ctrl_fkIk";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_R_upArm_fk_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_R_upArm_fk_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_R_upArm_fk_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_R_elbow_fk_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_R_wrist_fk_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_R_wrist_fk_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_R_wrist_fk_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_R_shoulder_fk_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_R_shoulder_fk_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_L_shoulder_fk_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_L_shoulder_fk_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_L_upArm_fk_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_L_upArm_fk_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_L_upArm_fk_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_L_elbow_fk_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_L_wrist_fk_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_L_wrist_fk_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_L_wrist_fk_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_M_neck_fk_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_M_neck_fk_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_M_neck_fk_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_M_head_fk_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_M_head_fk_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_M_head_fk_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "character1_R_leg_kneeIk_ctrl_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "character1_R_leg_kneeIk_ctrl_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "character1_R_leg_kneeIk_ctrl_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "character1_L_leg_kneeIk_ctrl_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "character1_L_leg_kneeIk_ctrl_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "character1_L_leg_kneeIk_ctrl_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_com_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_com_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_com_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "character1_com_ctrl_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "character1_com_ctrl_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "character1_com_ctrl_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_R_foot_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_R_foot_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_R_foot_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "character1_R_foot_ctrl_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "character1_R_foot_ctrl_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "character1_R_foot_ctrl_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_L_foot_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_L_foot_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_L_foot_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "character1_L_foot_ctrl_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "character1_L_foot_ctrl_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "character1_L_foot_ctrl_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_R_mace_ctrl_parent";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_R_mace_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_R_mace_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_R_mace_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "character1_R_mace_ctrl_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -0.81944359671150613;
createNode animCurveTL -n "character1_R_mace_ctrl_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -7.9552118737661725e-011;
createNode animCurveTL -n "character1_R_mace_ctrl_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0.0087141990168126959;
createNode animCurveTU -n "character1_L_mace_ctrl_parent";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_L_mace_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_L_mace_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_L_mace_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "character1_L_mace_ctrl_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -0.80451419482641451;
createNode animCurveTL -n "character1_L_mace_ctrl_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -2.4945889741368431e-013;
createNode animCurveTL -n "character1_L_mace_ctrl_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -0.0085562672260772743;
createNode animCurveTU -n "character1_R_footRoll_ctrl_slide";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_R_footRoll_ctrl_clampHeel";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 45;
createNode animCurveTU -n "character1_R_footRoll_ctrl_clampToe";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 45;
createNode animCurveTU -n "character1_R_footRoll_ctrl_clampSideToSide";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 45;
createNode animCurveTA -n "character1_R_footRoll_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_R_footRoll_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_L_footRoll_ctrl_slide";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_L_footRoll_ctrl_clampHeel";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 45;
createNode animCurveTU -n "character1_L_footRoll_ctrl_clampToe";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 45;
createNode animCurveTU -n "character1_L_footRoll_ctrl_clampSideToSide";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 45;
createNode animCurveTA -n "character1_L_footRoll_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_L_footRoll_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_R_fingers_ctrl_mittenRoll";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_R_fingers_ctrl_indexRoll";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_R_fingers_ctrl_mittenC";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_R_fingers_ctrl_mittenB";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_R_fingers_ctrl_mittenA";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_R_fingers_ctrl_mittenSpread";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_R_fingers_ctrl_indexC";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_R_fingers_ctrl_indexB";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_R_fingers_ctrl_indexA";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_R_fingers_ctrl_indexSpread";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_R_fingers_ctrl_thumbB";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_R_fingers_ctrl_thumbA";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_R_fingers_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_R_fingers_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_R_fingers_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -2.5999764661798822e-011;
createNode animCurveTU -n "character1_L_fingers_ctrl_mittenRoll";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_L_fingers_ctrl_indexRoll";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_L_fingers_ctrl_mittenC";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_L_fingers_ctrl_mittenB";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_L_fingers_ctrl_mittenA";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_L_fingers_ctrl_mittenSpread";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_L_fingers_ctrl_indexC";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_L_fingers_ctrl_indexB";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_L_fingers_ctrl_indexA";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_L_fingers_ctrl_indexSpread";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_L_fingers_ctrl_thumbB";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character1_L_fingers_ctrl_thumbA";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_L_fingers_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_L_fingers_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_L_fingers_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -2.5997909391022333e-011;
createNode animCurveTA -n "character1_chest_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_chest_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_chest_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_hips_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_hips_ctrl_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "character1_hips_ctrl_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "tank_M_hang_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "tank_M_hang_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "tank_M_hang_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "tank_R_hang_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "tank_R_hang_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "tank_R_hang_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "tank_L_hang_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "tank_L_hang_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "tank_L_hang_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "tank_M_backFeature_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "tank_M_backFeature_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "tank_M_backFeature_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode lightLinker -n "lightLinker1";
	setAttr -s 4 ".lnk";
	setAttr -s 4 ".slnk";
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
connectAttr "skinPoseSource.cl" "clipLibrary1.sc[0]";
connectAttr "character1_R_arm_ctrl_fkIk.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "character1_L_arm_ctrl_fkIk.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "character1_R_upArm_fk_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[2].cevr"
		;
connectAttr "character1_R_upArm_fk_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[3].cevr"
		;
connectAttr "character1_R_upArm_fk_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[4].cevr"
		;
connectAttr "character1_R_elbow_fk_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[5].cevr"
		;
connectAttr "character1_R_wrist_fk_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[6].cevr"
		;
connectAttr "character1_R_wrist_fk_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[7].cevr"
		;
connectAttr "character1_R_wrist_fk_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[8].cevr"
		;
connectAttr "character1_R_shoulder_fk_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[9].cevr"
		;
connectAttr "character1_R_shoulder_fk_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[10].cevr"
		;
connectAttr "character1_L_shoulder_fk_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[11].cevr"
		;
connectAttr "character1_L_shoulder_fk_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[12].cevr"
		;
connectAttr "character1_L_upArm_fk_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[13].cevr"
		;
connectAttr "character1_L_upArm_fk_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[14].cevr"
		;
connectAttr "character1_L_upArm_fk_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[15].cevr"
		;
connectAttr "character1_L_elbow_fk_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[16].cevr"
		;
connectAttr "character1_L_wrist_fk_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[17].cevr"
		;
connectAttr "character1_L_wrist_fk_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[18].cevr"
		;
connectAttr "character1_L_wrist_fk_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[19].cevr"
		;
connectAttr "character1_M_neck_fk_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[20].cevr"
		;
connectAttr "character1_M_neck_fk_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[21].cevr"
		;
connectAttr "character1_M_neck_fk_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[22].cevr"
		;
connectAttr "character1_M_head_fk_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[23].cevr"
		;
connectAttr "character1_M_head_fk_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[24].cevr"
		;
connectAttr "character1_M_head_fk_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[25].cevr"
		;
connectAttr "character1_R_leg_kneeIk_ctrl_translateZ.a" "clipLibrary1.cel[0].cev[26].cevr"
		;
connectAttr "character1_R_leg_kneeIk_ctrl_translateY.a" "clipLibrary1.cel[0].cev[27].cevr"
		;
connectAttr "character1_R_leg_kneeIk_ctrl_translateX.a" "clipLibrary1.cel[0].cev[28].cevr"
		;
connectAttr "character1_L_leg_kneeIk_ctrl_translateZ.a" "clipLibrary1.cel[0].cev[29].cevr"
		;
connectAttr "character1_L_leg_kneeIk_ctrl_translateY.a" "clipLibrary1.cel[0].cev[30].cevr"
		;
connectAttr "character1_L_leg_kneeIk_ctrl_translateX.a" "clipLibrary1.cel[0].cev[31].cevr"
		;
connectAttr "character1_com_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "character1_com_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "character1_com_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "character1_com_ctrl_translateZ.a" "clipLibrary1.cel[0].cev[35].cevr"
		;
connectAttr "character1_com_ctrl_translateY.a" "clipLibrary1.cel[0].cev[36].cevr"
		;
connectAttr "character1_com_ctrl_translateX.a" "clipLibrary1.cel[0].cev[37].cevr"
		;
connectAttr "character1_R_foot_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[38].cevr"
		;
connectAttr "character1_R_foot_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[39].cevr"
		;
connectAttr "character1_R_foot_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[40].cevr"
		;
connectAttr "character1_R_foot_ctrl_translateZ.a" "clipLibrary1.cel[0].cev[41].cevr"
		;
connectAttr "character1_R_foot_ctrl_translateY.a" "clipLibrary1.cel[0].cev[42].cevr"
		;
connectAttr "character1_R_foot_ctrl_translateX.a" "clipLibrary1.cel[0].cev[43].cevr"
		;
connectAttr "character1_L_foot_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[44].cevr"
		;
connectAttr "character1_L_foot_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[45].cevr"
		;
connectAttr "character1_L_foot_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[46].cevr"
		;
connectAttr "character1_L_foot_ctrl_translateZ.a" "clipLibrary1.cel[0].cev[47].cevr"
		;
connectAttr "character1_L_foot_ctrl_translateY.a" "clipLibrary1.cel[0].cev[48].cevr"
		;
connectAttr "character1_L_foot_ctrl_translateX.a" "clipLibrary1.cel[0].cev[49].cevr"
		;
connectAttr "character1_R_mace_ctrl_parent.a" "clipLibrary1.cel[0].cev[50].cevr"
		;
connectAttr "character1_R_mace_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[51].cevr"
		;
connectAttr "character1_R_mace_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[52].cevr"
		;
connectAttr "character1_R_mace_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[53].cevr"
		;
connectAttr "character1_R_mace_ctrl_translateZ.a" "clipLibrary1.cel[0].cev[54].cevr"
		;
connectAttr "character1_R_mace_ctrl_translateY.a" "clipLibrary1.cel[0].cev[55].cevr"
		;
connectAttr "character1_R_mace_ctrl_translateX.a" "clipLibrary1.cel[0].cev[56].cevr"
		;
connectAttr "character1_L_mace_ctrl_parent.a" "clipLibrary1.cel[0].cev[57].cevr"
		;
connectAttr "character1_L_mace_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[58].cevr"
		;
connectAttr "character1_L_mace_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[59].cevr"
		;
connectAttr "character1_L_mace_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[60].cevr"
		;
connectAttr "character1_L_mace_ctrl_translateZ.a" "clipLibrary1.cel[0].cev[61].cevr"
		;
connectAttr "character1_L_mace_ctrl_translateY.a" "clipLibrary1.cel[0].cev[62].cevr"
		;
connectAttr "character1_L_mace_ctrl_translateX.a" "clipLibrary1.cel[0].cev[63].cevr"
		;
connectAttr "character1_R_footRoll_ctrl_slide.a" "clipLibrary1.cel[0].cev[64].cevr"
		;
connectAttr "character1_R_footRoll_ctrl_clampHeel.a" "clipLibrary1.cel[0].cev[65].cevr"
		;
connectAttr "character1_R_footRoll_ctrl_clampToe.a" "clipLibrary1.cel[0].cev[66].cevr"
		;
connectAttr "character1_R_footRoll_ctrl_clampSideToSide.a" "clipLibrary1.cel[0].cev[67].cevr"
		;
connectAttr "character1_R_footRoll_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[68].cevr"
		;
connectAttr "character1_R_footRoll_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[69].cevr"
		;
connectAttr "character1_L_footRoll_ctrl_slide.a" "clipLibrary1.cel[0].cev[70].cevr"
		;
connectAttr "character1_L_footRoll_ctrl_clampHeel.a" "clipLibrary1.cel[0].cev[71].cevr"
		;
connectAttr "character1_L_footRoll_ctrl_clampToe.a" "clipLibrary1.cel[0].cev[72].cevr"
		;
connectAttr "character1_L_footRoll_ctrl_clampSideToSide.a" "clipLibrary1.cel[0].cev[73].cevr"
		;
connectAttr "character1_L_footRoll_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[74].cevr"
		;
connectAttr "character1_L_footRoll_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[75].cevr"
		;
connectAttr "character1_R_fingers_ctrl_mittenRoll.a" "clipLibrary1.cel[0].cev[76].cevr"
		;
connectAttr "character1_R_fingers_ctrl_indexRoll.a" "clipLibrary1.cel[0].cev[77].cevr"
		;
connectAttr "character1_R_fingers_ctrl_mittenC.a" "clipLibrary1.cel[0].cev[78].cevr"
		;
connectAttr "character1_R_fingers_ctrl_mittenB.a" "clipLibrary1.cel[0].cev[79].cevr"
		;
connectAttr "character1_R_fingers_ctrl_mittenA.a" "clipLibrary1.cel[0].cev[80].cevr"
		;
connectAttr "character1_R_fingers_ctrl_mittenSpread.a" "clipLibrary1.cel[0].cev[81].cevr"
		;
connectAttr "character1_R_fingers_ctrl_indexC.a" "clipLibrary1.cel[0].cev[82].cevr"
		;
connectAttr "character1_R_fingers_ctrl_indexB.a" "clipLibrary1.cel[0].cev[83].cevr"
		;
connectAttr "character1_R_fingers_ctrl_indexA.a" "clipLibrary1.cel[0].cev[84].cevr"
		;
connectAttr "character1_R_fingers_ctrl_indexSpread.a" "clipLibrary1.cel[0].cev[85].cevr"
		;
connectAttr "character1_R_fingers_ctrl_thumbB.a" "clipLibrary1.cel[0].cev[86].cevr"
		;
connectAttr "character1_R_fingers_ctrl_thumbA.a" "clipLibrary1.cel[0].cev[87].cevr"
		;
connectAttr "character1_R_fingers_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[88].cevr"
		;
connectAttr "character1_R_fingers_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[89].cevr"
		;
connectAttr "character1_R_fingers_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[90].cevr"
		;
connectAttr "character1_L_fingers_ctrl_mittenRoll.a" "clipLibrary1.cel[0].cev[91].cevr"
		;
connectAttr "character1_L_fingers_ctrl_indexRoll.a" "clipLibrary1.cel[0].cev[92].cevr"
		;
connectAttr "character1_L_fingers_ctrl_mittenC.a" "clipLibrary1.cel[0].cev[93].cevr"
		;
connectAttr "character1_L_fingers_ctrl_mittenB.a" "clipLibrary1.cel[0].cev[94].cevr"
		;
connectAttr "character1_L_fingers_ctrl_mittenA.a" "clipLibrary1.cel[0].cev[95].cevr"
		;
connectAttr "character1_L_fingers_ctrl_mittenSpread.a" "clipLibrary1.cel[0].cev[96].cevr"
		;
connectAttr "character1_L_fingers_ctrl_indexC.a" "clipLibrary1.cel[0].cev[97].cevr"
		;
connectAttr "character1_L_fingers_ctrl_indexB.a" "clipLibrary1.cel[0].cev[98].cevr"
		;
connectAttr "character1_L_fingers_ctrl_indexA.a" "clipLibrary1.cel[0].cev[99].cevr"
		;
connectAttr "character1_L_fingers_ctrl_indexSpread.a" "clipLibrary1.cel[0].cev[100].cevr"
		;
connectAttr "character1_L_fingers_ctrl_thumbB.a" "clipLibrary1.cel[0].cev[101].cevr"
		;
connectAttr "character1_L_fingers_ctrl_thumbA.a" "clipLibrary1.cel[0].cev[102].cevr"
		;
connectAttr "character1_L_fingers_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[103].cevr"
		;
connectAttr "character1_L_fingers_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[104].cevr"
		;
connectAttr "character1_L_fingers_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[105].cevr"
		;
connectAttr "character1_chest_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[106].cevr"
		;
connectAttr "character1_chest_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[107].cevr"
		;
connectAttr "character1_chest_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[108].cevr"
		;
connectAttr "character1_hips_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[109].cevr"
		;
connectAttr "character1_hips_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[110].cevr"
		;
connectAttr "character1_hips_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[111].cevr"
		;
connectAttr "tank_M_hang_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[115].cevr";
connectAttr "tank_M_hang_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[116].cevr";
connectAttr "tank_M_hang_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[117].cevr";
connectAttr "tank_R_hang_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[118].cevr";
connectAttr "tank_R_hang_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[119].cevr";
connectAttr "tank_R_hang_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[120].cevr";
connectAttr "tank_L_hang_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[121].cevr";
connectAttr "tank_L_hang_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[122].cevr";
connectAttr "tank_L_hang_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[123].cevr";
connectAttr "tank_M_backFeature_ctrl_rotateZ.a" "clipLibrary1.cel[0].cev[142].cevr"
		;
connectAttr "tank_M_backFeature_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[143].cevr"
		;
connectAttr "tank_M_backFeature_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[144].cevr"
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
// End of TposeA.ma
