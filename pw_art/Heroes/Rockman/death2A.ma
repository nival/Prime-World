//Maya ASCII 2008 scene
//Name: death2B.ma
//Last modified: Mon, Oct 26, 2009 11:09:13 AM
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
	setAttr -s 136 ".cel[0].cev";
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
createNode animClip -n "deathSource";
	setAttr ".ihi" 0;
	setAttr -s 136 ".ac";
	setAttr ".ac[0:114]" no no yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes no no no no no no yes yes yes no 
		no no yes yes yes no no no yes yes yes no no no no yes yes yes no no no no yes yes 
		yes no no no no no no no yes yes no no no no yes yes no no no no no no no no no no 
		no no yes yes yes no no no no no no no no no no no no yes yes yes yes yes yes yes 
		yes yes yes yes yes;
	setAttr ".ac[124:141]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes;
	setAttr ".ac[145:147]" yes yes yes;
	setAttr ".se" 44;
	setAttr ".ci" no;
createNode animCurveTU -n "animCurveTU390";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 4 0 10 0;
	setAttr -s 3 ".kit[1:2]"  10 9;
	setAttr -s 3 ".kot[1:2]"  10 9;
createNode animCurveTU -n "animCurveTU391";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 4 0 10 0;
	setAttr -s 3 ".kit[1:2]"  10 9;
	setAttr -s 3 ".kot[1:2]"  10 9;
createNode animCurveTA -n "animCurveTA1012";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -16.433008012612902 10 26.877762858978073 
		27 59.875884532543225 31 49.500516694104569 41 46.80692268125329;
	setAttr -s 5 ".kit[0:4]"  3 9 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 9 10 10 10;
createNode animCurveTA -n "animCurveTA1013";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 46.484153693874759 10 66.451219992282773 
		27 47.23547304465658 31 -9.6046748650442915 41 4.6236000598629898;
	setAttr -s 5 ".kit[0:4]"  3 9 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 9 10 10 10;
createNode animCurveTA -n "animCurveTA1014";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -14.962212153601083 10 25.227284453484604 
		27 48.109471004499142 31 67.445710959915615 41 -0.77274873087511775;
	setAttr -s 5 ".kit[0:4]"  3 9 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 9 10 10 10;
createNode animCurveTA -n "animCurveTA1015";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -22.136766656027952 10 -27.420760629284384 
		18 -48.407374929930974 20 -37.548877099480272 27 -10.930063521313741 31 -20.899874017556648 
		41 -26.607850147772652;
	setAttr -s 7 ".kit[0:6]"  3 9 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 9 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA1016";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.68849474610917216 4 -10.838249119821787 
		10 -0.15941710440026655 15 10.180323073615117 18 14.295016362005523 27 -24.170697816827925 
		31 7.5358327017817679 41 31.376979699052953;
	setAttr -s 8 ".kit[0:7]"  3 10 9 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 9 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA1017";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.42006444830693845 4 0.14900831963452393 
		10 -24.031764915528925 15 -2.1747616853241847 18 5.2534632648880359 27 -30.836825994957547 
		31 -9.4523380357319766 41 -9.270447388697189;
	setAttr -s 8 ".kit[0:7]"  3 10 9 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 9 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA1018";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.63229744012554356 4 -3.043109510157433 
		10 -3.0715066460130771 15 4.3620174722805416 18 23.083745312426011 27 36.03378989967031 
		31 -59.487253908234024 41 5.8153844972599718;
	setAttr -s 8 ".kit[0:7]"  3 10 9 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 9 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA1019";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -10.263293154844943 4 -1.7561932647960961 
		10 -27.420760629284384 13 -30.19803661864001 18 -11.745169810984768 27 -16.663075567008701 
		31 -5.6122468306197835 35 3.2155098724905264 37 3.2155098724905264 41 3.2155098724905264;
	setAttr -s 10 ".kit[0:9]"  3 10 9 10 10 10 10 3 
		1 10;
	setAttr -s 10 ".kot[0:9]"  3 10 9 10 10 10 10 3 
		1 10;
	setAttr -s 10 ".kix[8:9]"  1 1;
	setAttr -s 10 ".kiy[8:9]"  0 0;
	setAttr -s 10 ".kox[8:9]"  1 1;
	setAttr -s 10 ".koy[8:9]"  0 0;
createNode animCurveTA -n "animCurveTA1020";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 15.824321534293112 4 13.538309825139127 
		10 3.733621579953553 13 13.127692586578814 18 16.590163062090102 41 3.733621579953553;
	setAttr -s 6 ".kit[0:5]"  3 10 9 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 9 10 10 10;
createNode animCurveTA -n "animCurveTA1021";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -10.818908651033057 4 0.16548582532002901 
		10 0.63830243648086316 27 -3.0809043401251426 31 16.285168409491373 40 -6.0646249705725834 
		44 -20.477026924279105;
	setAttr -s 7 ".kit[0:6]"  3 10 9 10 10 3 10;
	setAttr -s 7 ".kot[0:6]"  3 10 9 10 10 3 10;
createNode animCurveTA -n "animCurveTA1022";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 12.875158369523408 4 -0.065103823331685046 
		10 -0.25111473430712411 13 8.3045477633766041 18 -10.903625031712124 27 0.81000292772268245 
		31 3.9801459427458106 40 -2.0454884020443171 44 -1.6753730983654114;
	setAttr -s 9 ".kit[0:8]"  3 10 9 10 10 10 10 3 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 9 10 10 10 10 3 
		10;
createNode animCurveTA -n "animCurveTA1023";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -25.378456988571386 4 -18.829706455736034 
		10 9.9847949660988888 27 58.073481759461075 31 40.501287494657817 35 37.334966171494322 
		39 35.972080349481729 44 29.224448279231328;
	setAttr -s 8 ".kit[0:7]"  3 10 9 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 9 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA1024";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 49.284082676870852 4 45.395329682695632 
		10 28.284817965330859 27 -10.728496524398391 31 -19.659690981010154 35 16.412259392939372 
		39 4.043061180886661 44 5.7990765477943045;
	setAttr -s 8 ".kit[0:7]"  3 10 9 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 9 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA1025";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 34.969087097535308 4 28.957267678687966 
		10 2.5052638510759753 27 57.582827455147793 31 52.561146728017064 35 15.654080871680927 
		39 36.322069286895818 44 49.381405720672873;
	setAttr -s 8 ".kit[0:7]"  3 10 9 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 9 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA1026";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -4.2353230899544307 4 -10.276256529990123 
		10 -36.856363223777407 27 -19.572941543596233 31 -13.580250806226976 35 -11.101720189769996 
		39 -29.172644881200416 44 -21.994048072990587;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA1027";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 10 0 27 0 31 0 35 0 38 11.440555204209817 
		44 28.243351935108063;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTA -n "animCurveTA1028";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 10 0 27 0 31 0 35 -16.331724173966546 
		38 -8.743435990625235 44 -19.2226993400281;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTA -n "animCurveTA1029";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 10 0 27 0 31 0 35 0 38 -10.702964795011495 
		44 -53.056667934358181;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTA -n "animCurveTA1030";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 4 -0.18498681394440383 10 -0.71352053161772477 
		14 13.365911447574344 18 0.082824973896139062 27 21.352495385084293 31 -13.319772500599857 
		35 -22.073496718183108 37 -22.073496718183108 41 -13.319772500599857;
	setAttr -s 10 ".kit[0:9]"  3 10 9 10 10 10 10 3 
		1 3;
	setAttr -s 10 ".kot[0:9]"  3 10 9 10 10 10 10 3 
		1 3;
	setAttr -s 10 ".kix[8:9]"  1 1;
	setAttr -s 10 ".kiy[8:9]"  0 0;
	setAttr -s 10 ".kox[8:9]"  1 1;
	setAttr -s 10 ".koy[8:9]"  0 0;
createNode animCurveTA -n "animCurveTA1031";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 4 -1.8427593807254294 10 -9.9508999060800321 
		14 -16.233018286723567 18 15.364347617175746 27 -17.404665651791248 31 -14.95830335474294 
		35 -25.314506644060348 37 -25.314506644060348 41 -14.95830335474294;
	setAttr -s 10 ".kit[0:9]"  3 10 9 10 10 10 10 3 
		1 3;
	setAttr -s 10 ".kot[0:9]"  3 10 9 10 10 10 10 3 
		1 3;
	setAttr -s 10 ".kix[8:9]"  1 1;
	setAttr -s 10 ".kiy[8:9]"  0 0;
	setAttr -s 10 ".kox[8:9]"  1 1;
	setAttr -s 10 ".koy[8:9]"  0 0;
createNode animCurveTA -n "animCurveTA1032";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 4 0.79870374595660842 10 4.3130000224468699 
		14 -4.9967536663052048 18 31.49365831298979 27 -8.6674751188087455 31 9.3027106692023143 
		35 30.44254941195214 37 30.44254941195214 41 9.3027106692023143;
	setAttr -s 10 ".kit[0:9]"  3 10 9 10 10 10 10 3 
		1 3;
	setAttr -s 10 ".kot[0:9]"  3 10 9 10 10 10 10 3 
		1 3;
	setAttr -s 10 ".kix[8:9]"  1 1;
	setAttr -s 10 ".kiy[8:9]"  0 0;
	setAttr -s 10 ".kox[8:9]"  1 1;
	setAttr -s 10 ".koy[8:9]"  0 0;
createNode animCurveTA -n "animCurveTA1033";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -14.515820710620677 4 13.970600742149029 
		10 34.023653239880659 14 14.087927426548092 18 9.9480278721463744 27 -29.112106199592265 
		31 -85.823301400330095 35 -77.500230161865616 37 -77.500230161865616 41 -87.728819744886735;
	setAttr -s 10 ".kit[0:9]"  3 10 9 10 9 10 10 3 
		1 3;
	setAttr -s 10 ".kot[0:9]"  3 10 9 10 9 10 10 3 
		1 3;
	setAttr -s 10 ".kix[8:9]"  1 1;
	setAttr -s 10 ".kiy[8:9]"  0 0;
	setAttr -s 10 ".kox[8:9]"  1 1;
	setAttr -s 10 ".koy[8:9]"  0 0;
createNode animCurveTA -n "animCurveTA1034";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -17.383598210882599 4 -0.71023370371231431 
		10 16.938614906988605 14 12.744656841685227 18 21.505379377340383 27 24.042370057283438 
		31 8.4477279901421944 35 10.516188882091457 37 10.516188882091457 41 9.8761863712414826;
	setAttr -s 10 ".kit[0:9]"  3 10 9 10 9 10 10 3 
		1 3;
	setAttr -s 10 ".kot[0:9]"  3 10 9 10 9 10 10 3 
		1 3;
	setAttr -s 10 ".kix[8:9]"  1 1;
	setAttr -s 10 ".kiy[8:9]"  0 0;
	setAttr -s 10 ".kox[8:9]"  1 1;
	setAttr -s 10 ".koy[8:9]"  0 0;
createNode animCurveTA -n "animCurveTA1035";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1.5268462968664711 4 13.739009266861958 
		10 19.259659175702414 14 24.858214327103131 18 -14.004785748256706 27 19.675000726419569 
		31 37.358975517492169 35 35.296585907845085 37 35.296585907845085 41 37.055517148030219;
	setAttr -s 10 ".kit[0:9]"  3 10 9 10 9 10 10 3 
		1 3;
	setAttr -s 10 ".kot[0:9]"  3 10 9 10 9 10 10 3 
		1 3;
	setAttr -s 10 ".kix[8:9]"  1 1;
	setAttr -s 10 ".kiy[8:9]"  0 0;
	setAttr -s 10 ".kox[8:9]"  1 1;
	setAttr -s 10 ".koy[8:9]"  0 0;
createNode animCurveTL -n "animCurveTL382";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.00025694328101411035 4 -0.080556733298582789 
		10 -0.43613688347587848 27 -0.62102397214212635 31 -0.62723090054582098 35 -0.61873783667577154 
		37 -0.61873783667577154 41 -0.62723090054582098;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTL -n "animCurveTL383";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 -0.062188393764959056 10 -0.33581731194983655 
		27 -0.33581731194983655 31 -0.33581731194983655 35 -0.33581731194983655 37 -0.33581731194983655 
		41 -0.33581731194983655;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTL -n "animCurveTL384";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.12527739251666781 4 -0.10609305356411418 
		10 -0.021681968586025221 27 -0.0028584593084052985 31 -0.00067358576386280936 35 
		-0.061444121041799991 37 -0.061444121041799991 41 -0.23507431763959671;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTL -n "animCurveTL385";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.032833691772160223 4 -0.030023507428048629 
		7 -0.055834939752131219 10 -0.22528268058090695 27 -0.52680896441790392 35 -0.52789759977251072 
		37 -0.64685890608137164 41 -0.63020285146683774;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTL -n "animCurveTL386";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.016062985925156426 4 -0.10612808591913767 
		7 -0.41064199655179012 10 -0.50241450276937871 27 -0.11797972930060457 35 -0.09327697128544607 
		37 -0.09327697128544607 41 -0.07424732735160057;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 9 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 9 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTL -n "animCurveTL387";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.11728380015772394 4 0.10673297058395825 
		7 0.26458844134304754 10 0.060309322879244412 27 0.24482830160114727 31 0.20884795129205103 
		35 0.38278436754378165 37 0.28945416739982827 41 0.41150428401886252;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 3 1 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 3 1 
		3;
	setAttr -s 9 ".kix[7:8]"  1 1;
	setAttr -s 9 ".kiy[7:8]"  0 0;
	setAttr -s 9 ".kox[7:8]"  1 1;
	setAttr -s 9 ".koy[7:8]"  0 0;
createNode animCurveTA -n "animCurveTA1036";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 4 1.9534667336866405 10 10.54871983138832 
		15 13.023092207343312 18 17.332709256760168 27 -1.920062252777422 31 -22.264475321919697 
		35 -22.407840496982239 37 -17.943713433463671 41 -17.1119300799478;
	setAttr -s 10 ".kit[0:9]"  3 10 9 9 9 10 10 10 
		1 3;
	setAttr -s 10 ".kot[0:9]"  3 10 9 9 9 10 10 10 
		1 3;
	setAttr -s 10 ".kix[8:9]"  1 1;
	setAttr -s 10 ".kiy[8:9]"  0 0;
	setAttr -s 10 ".kox[8:9]"  1 1;
	setAttr -s 10 ".koy[8:9]"  0 0;
createNode animCurveTA -n "animCurveTA1037";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 4 -2.6711899765475429 10 -14.424424599830438 
		15 -11.858062857858187 18 -18.04739957228233 27 -11.878031608564116 31 -8.7560181464607219 
		35 -7.8846929990068784 37 -9.4497982237421496 41 -9.7695425354523859;
	setAttr -s 10 ".kit[0:9]"  3 10 9 9 9 10 10 10 
		1 3;
	setAttr -s 10 ".kot[0:9]"  3 10 9 9 9 10 10 10 
		1 3;
	setAttr -s 10 ".kix[8:9]"  1 1;
	setAttr -s 10 ".kiy[8:9]"  0 0;
	setAttr -s 10 ".kox[8:9]"  1 1;
	setAttr -s 10 ".koy[8:9]"  0 0;
createNode animCurveTA -n "animCurveTA1038";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 3.6719125695963681 4 -0.8987435326888229 
		10 -21.00962928054474 15 -18.832065053797756 18 -14.937029280433533 27 58.216939320920169 
		31 106.79979874311114 35 118.76070116267348 37 116.86231576167786 41 108.14961902619312;
	setAttr -s 10 ".kit[0:9]"  3 10 9 9 9 10 1 10 
		1 3;
	setAttr -s 10 ".kot[0:9]"  3 10 9 9 9 10 1 10 
		1 3;
	setAttr -s 10 ".kix[6:9]"  0.55113601684570313 1 1 1;
	setAttr -s 10 ".kiy[6:9]"  0.83441537618637085 0 0 0;
	setAttr -s 10 ".kox[6:9]"  0.55113637447357178 1 1 1;
	setAttr -s 10 ".koy[6:9]"  0.83441513776779175 0 0 0;
createNode animCurveTL -n "animCurveTL388";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.0319338039184065 4 -0.12914745720997398 
		10 -0.55688750397938447 15 -0.56736578272486748 18 -0.55576767874256561 27 -0.54970633459507678 
		31 -0.56957631088493932 35 -0.54700258421930636 37 -0.56553417237281822 41 -0.5965441272738361;
	setAttr -s 10 ".kit[0:9]"  3 10 9 10 10 10 10 10 
		1 3;
	setAttr -s 10 ".kot[0:9]"  3 10 9 10 10 10 10 10 
		1 3;
	setAttr -s 10 ".kix[8:9]"  1 1;
	setAttr -s 10 ".kiy[8:9]"  0 0;
	setAttr -s 10 ".kox[8:9]"  1 1;
	setAttr -s 10 ".koy[8:9]"  0 0;
createNode animCurveTL -n "animCurveTL389";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.00078859512199502824 4 -0.090715147701134063 
		10 -0.49333158369170438 27 -0.66988365430423447 31 -0.8689368478504953 35 -0.93307611775385657 
		37 -0.95225908131754311 41 -0.92402464625802139;
	setAttr -s 8 ".kit[0:7]"  3 10 9 10 10 10 10 9;
	setAttr -s 8 ".kot[0:7]"  3 10 9 10 10 10 10 9;
createNode animCurveTL -n "animCurveTL390";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 4 -0.011327139533134821 7 -0.056603957227832485 
		10 -0.061166550739267744 27 -0.061166550739267744 31 -0.061166550739267744 35 -0.061166550739267744 
		37 -0.061166550739267744 41 -0.061166550739267744;
	setAttr -s 9 ".kit[0:8]"  3 10 10 9 10 10 10 1 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 9 10 10 10 1 
		3;
	setAttr -s 9 ".kix[7:8]"  1 1;
	setAttr -s 9 ".kiy[7:8]"  0 0;
	setAttr -s 9 ".kox[7:8]"  1 1;
	setAttr -s 9 ".koy[7:8]"  0 0;
createNode animCurveTA -n "animCurveTA1039";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -16.236770139599834 4 -16.236770139599834 
		10 -16.236770139599944 27 -9.8234954985988576 35 -3.091963641844091 41 9.3934880846013993;
	setAttr -s 6 ".kit[0:5]"  3 1 10 10 10 9;
	setAttr -s 6 ".kot[0:5]"  3 1 10 10 10 9;
	setAttr -s 6 ".kix[1:5]"  1 1 0.96413034200668335 0.81202948093414307 
		0.67617851495742798;
	setAttr -s 6 ".kiy[1:5]"  0 0 0.26542913913726807 0.58361649513244629 
		0.73673772811889648;
	setAttr -s 6 ".kox[1:5]"  1 1 0.96413034200668335 0.81202948093414307 
		0.67617851495742798;
	setAttr -s 6 ".koy[1:5]"  0 0 0.26542913913726807 0.58361649513244629 
		0.73673772811889648;
createNode animCurveTA -n "animCurveTA1040";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 10 0 27 -20.63609868451919 35 12.68657947951151 
		41 54.209783226963459;
	setAttr -s 6 ".kit[0:5]"  3 1 10 10 10 9;
	setAttr -s 6 ".kot[0:5]"  3 1 10 10 10 9;
	setAttr -s 6 ".kix[1:5]"  1 1 0.96646547317504883 0.3364185094833374 
		0.26602569222450256;
	setAttr -s 6 ".kiy[1:5]"  0 0 0.25679677724838257 0.94171255826950073 
		0.96396595239639282;
	setAttr -s 6 ".kox[1:5]"  1 1 0.96646547317504883 0.3364185094833374 
		0.26602569222450256;
	setAttr -s 6 ".koy[1:5]"  0 0 0.25679677724838257 0.94171255826950073 
		0.96396595239639282;
createNode animCurveTA -n "animCurveTA1041";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 0 10 61.42870430100416 27 80.381024716309511 
		31 87.495573143160826 35 86.417081236472782 41 76.641467858878599;
	setAttr -s 7 ".kit[0:6]"  3 1 10 10 10 10 9;
	setAttr -s 7 ".kot[0:6]"  3 1 10 10 10 10 9;
	setAttr -s 7 ".kix[1:6]"  1 0.47954672574996948 0.83846950531005859 
		1 1 0.76078063249588013;
	setAttr -s 7 ".kiy[1:6]"  0 0.87751644849777222 0.54494857788085938 
		0 0 -0.64900904893875122;
	setAttr -s 7 ".kox[1:6]"  1 0.47954672574996948 0.83846950531005859 
		1 1 0.76078063249588013;
	setAttr -s 7 ".koy[1:6]"  0 0.87751644849777222 0.54494857788085938 
		0 0 -0.64900904893875122;
createNode animCurveTL -n "animCurveTL391";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -6.0000000000892673e-006 4 -6.0000000000892673e-006 
		10 0.16661782245618859 27 0.15824484167503955 31 0.21248136794097031 35 0.3883169071451304 
		37 0.27887486732610917 41 0.085930559317498476;
	setAttr -s 8 ".kit[0:7]"  3 1 10 10 10 10 10 9;
	setAttr -s 8 ".kot[0:7]"  3 1 10 10 10 10 10 9;
	setAttr -s 8 ".kix[1:7]"  1 1 1 0.75714725255966187 0.94907152652740479 
		0.55165863037109375 0.56850790977478027;
	setAttr -s 8 ".kiy[1:7]"  0 0 0 0.65324419736862183 0.3150608241558075 
		-0.83406996726989746 -0.82267779111862183;
	setAttr -s 8 ".kox[1:7]"  1 1 1 0.75714725255966187 0.94907152652740479 
		0.55165863037109375 0.56850790977478027;
	setAttr -s 8 ".koy[1:7]"  0 0 0 0.65324419736862183 0.3150608241558075 
		-0.83406996726989746 -0.82267779111862183;
createNode animCurveTL -n "animCurveTL392";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 2.1809999999936394e-005 4 2.1809999999936394e-005 
		10 2.1809999999936394e-005 27 0.043458005638355168 31 -0.079789273735751357 35 -0.19251410122951843 
		37 -0.13590148705991881 41 -0.054876689748355405;
	setAttr -s 8 ".kit[0:7]"  3 1 10 10 10 10 10 9;
	setAttr -s 8 ".kot[0:7]"  3 1 10 10 10 10 10 9;
	setAttr -s 8 ".kix[1:7]"  1 1 1 0.74889242649078369 0.96282368898391724 
		0.82377767562866211 0.85458153486251831;
	setAttr -s 8 ".kiy[1:7]"  0 0 0 -0.66269153356552124 -0.27013078331947327 
		0.56691300868988037 0.51931720972061157;
	setAttr -s 8 ".kox[1:7]"  1 1 1 0.74889242649078369 0.96282368898391724 
		0.82377767562866211 0.85458153486251831;
	setAttr -s 8 ".koy[1:7]"  0 0 0 -0.66269153356552124 -0.27013078331947327 
		0.56691300868988037 0.51931720972061157;
createNode animCurveTL -n "animCurveTL393";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.040093865534497591 4 -0.040093865534497591 
		10 -0.040093865534497591 27 -0.040093865534497591 35 -0.040093865534497591 41 -0.040093865534497591;
	setAttr -s 6 ".kit[0:5]"  3 1 10 10 10 9;
	setAttr -s 6 ".kot[0:5]"  3 1 10 10 10 9;
	setAttr -s 6 ".kix[1:5]"  1 1 1 1 1;
	setAttr -s 6 ".kiy[1:5]"  0 0 0 0 0;
	setAttr -s 6 ".kox[1:5]"  1 1 1 1 1;
	setAttr -s 6 ".koy[1:5]"  0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1042";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 25.000774638404387 4 24.115171736034188 
		10 20.218519195338896 27 -18.444649864957963 35 -25.944441401484013 39 -21.655265066470321;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 9;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 9;
createNode animCurveTA -n "animCurveTA1043";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 -6.0471706032786701 10 -32.654719088687131 
		27 -32.612634323475795 35 -6.4348070389828509 39 -32.607749480337233;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 9;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 9;
createNode animCurveTA -n "animCurveTA1044";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 7.7089854624141738 10 41.628518939238496 
		27 113.72779638869548 31 111.32479708148858 35 102.94378986965064 39 127.9472233775312;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 9;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 9;
createNode animCurveTL -n "animCurveTL394";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0.020204573929147856 10 0.10910469253953618 
		27 0.038367218014023055 31 0.026278624227878602 35 0.12298226117627216 39 0.00089870997643699097 
		41 0.00089870997643699097;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 1 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 1 10;
	setAttr -s 8 ".kix[6:7]"  0.4121738076210022 1;
	setAttr -s 8 ".kiy[6:7]"  -0.91110527515411377 0;
	setAttr -s 8 ".kox[6:7]"  0.4121738076210022 1;
	setAttr -s 8 ".koy[6:7]"  -0.91110527515411377 0;
createNode animCurveTL -n "animCurveTL395";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 10 0 27 -0.097393402103703577 31 
		-0.20670947887984836 35 -0.29630272890213566 39 -0.26165985725128632 41 -0.25414027204803485;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 3 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 3 3;
createNode animCurveTL -n "animCurveTL396";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.038258090963777358 4 0.038258090963777358 
		10 0.038258090963777358 27 0.20844464856242736 35 0.21943993567819031 39 0.22819846289375073;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 9;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 9;
createNode animCurveTU -n "animCurveTU392";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 1 0 4 0 8 0 11 0 30 0;
	setAttr -s 6 ".kot[0:5]"  5 5 5 5 5 5;
createNode animCurveTA -n "animCurveTA1045";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 1 46.81195095119908 4 48.8883650457689 
		8 91.958137523846034 11 105.16031979261393 15 85.92117356307827 20 54.489808002324089 
		30 61.038060573568735 40 57.09058797079571;
	setAttr -s 9 ".kit[1:8]"  9 3 10 10 10 10 10 10;
	setAttr -s 9 ".kot[1:8]"  9 3 10 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA1046";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 1 -45.275409438700336 4 -82.575368060640855 
		8 -39.825389126841614 11 -1.2215879365995428 15 10.081037523017232 20 -0.66103826305641333 
		30 -0.86503741666759648 40 -0.7412185264229979;
	setAttr -s 9 ".kit[1:8]"  9 3 10 10 10 10 10 10;
	setAttr -s 9 ".kot[1:8]"  9 3 10 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA1047";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 1 -28.442275445762885 4 -33.373446295937399 
		8 -87.187426891745744 11 -125.9260478166664 15 -168.63333112153899 20 -210.66265210085592 
		30 -178.26106303077708 40 -192.43211847653308;
	setAttr -s 9 ".kit[1:8]"  9 2 10 10 10 10 10 10;
	setAttr -s 9 ".kot[1:8]"  9 2 10 10 10 10 10 10;
createNode animCurveTL -n "animCurveTL397";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.80799999999999983 1 -1.1350522067035707 
		4 -1.5514289985808474 8 -1.6396810397072941 11 -2.1459565703235421 15 -2.0582226906994623 
		20 -2.0836566594472479 30 -2.0831455642879599 40 -2.0878502490268529;
	setAttr -s 9 ".kit[2:8]"  9 9 10 10 10 10 10;
	setAttr -s 9 ".kot[2:8]"  9 9 10 10 10 10 10;
createNode animCurveTL -n "animCurveTL398";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -8.785595135511054e-016 1 -0.15329745091571509 
		4 -0.32677122247571883 8 0.14808714674505641 11 0.44816628516045715 20 0.6303900725710283 
		30 0.57823517034503169 40 0.61911099734932262;
	setAttr -s 8 ".kit[2:7]"  9 9 10 10 10 10;
	setAttr -s 8 ".kot[2:7]"  9 9 10 10 10 10;
createNode animCurveTL -n "animCurveTL399";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 3.8857805861880479e-016 1 0.05801803551419079 
		4 -0.15339837903787379 5 -0.12275372011897392 6 -0.15133925265440412 8 -0.2947002944876434 
		11 -0.44776377062740963 20 -0.65014378942501594 30 -0.56156204308068203 40 -0.61916514383826748;
	setAttr -s 10 ".kit[2:9]"  9 10 10 9 10 10 10 10;
	setAttr -s 10 ".kot[2:9]"  9 10 10 9 10 10 10 10;
createNode animCurveTU -n "animCurveTU393";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 11 1 12 0 25 0;
	setAttr -s 4 ".kit[0:3]"  10 9 9 9;
	setAttr -s 4 ".kot[0:3]"  10 5 5 5;
createNode animCurveTA -n "animCurveTA1048";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 11 0 12 -28.194708635120637 16 -39.668735731260924 
		20 -25.986376683826975 25 -40.333815845211014 31 -67.234921194878012 38 -55.632468476574303;
createNode animCurveTA -n "animCurveTA1049";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 11 0 12 22.605915994596209 16 61.136198805305078 
		20 124.23957011869373 25 185.25385004067056 31 184.99528731290067 38 184.61270034260269;
createNode animCurveTA -n "animCurveTA1050";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 11 0 12 -8.9372680976516445 16 -23.90536623563295 
		20 16.205225667113847 25 51.26325992845053 31 127.30382936385425 38 111.62118363262944;
createNode animCurveTL -n "animCurveTL400";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.80789537837891157 11 -0.80789537837891157 
		12 -1.5182779290559163 16 -1.5669530088021031 20 -1.5894517319724955 25 -2.1123490207465303 
		28 -2.0151444296067655 31 -2.1121461719607839;
createNode animCurveTL -n "animCurveTL401";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 2.2649661009579991e-017 11 2.2649661009579991e-017 
		12 -0.4094037363646239 16 -0.50217349980764292 20 -0.91930772872469058 25 -1.2630180605310621 
		31 -1.4703382733049812;
createNode animCurveTL -n "animCurveTL402";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.5099033134902129e-013 11 1.5099033134902129e-013 
		12 -0.21324049882065649 16 0.14171025811638774 20 0.8064140804004809 25 1.1920213996276405 
		31 1.4920490975662972;
createNode animCurveTU -n "animCurveTU394";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 10 0 27 0 31 0 35 0 37 0 41 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTU -n "animCurveTU395";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 45 4 45 10 45 27 45 31 45 35 45 37 45 
		41 45;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTU -n "animCurveTU396";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 45 4 45 10 45 27 45 31 45 35 45 37 45 
		41 45;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTU -n "animCurveTU397";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 45 4 45 10 45 27 45 31 45 35 45 37 45 
		41 45;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTA -n "animCurveTA1051";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 -0.26603189083992684 10 -1.0261229551011226 
		27 -1.0261229551011226 31 -1.0261229551011226 35 -1.0261229551011226 37 -1.0261229551011226 
		41 -1.0261229551011226;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTA -n "animCurveTA1052";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0.90071917679383984 10 72.609609895152332 
		27 72.609609895152332 31 72.609609895152332 35 72.609609895152332 37 72.609609895152332 
		41 72.609609895152332;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTU -n "animCurveTU398";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 10 0 27 0 31 0 35 0 37 0 41 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTU -n "animCurveTU399";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 45 4 45 10 45 27 45 31 45 35 45 37 45 
		41 45;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTU -n "animCurveTU400";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 45 4 45 10 45 27 45 31 45 35 45 37 45 
		41 45;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTU -n "animCurveTU401";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 45 4 45 10 45 27 45 31 45 35 45 37 45 
		41 45;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTA -n "animCurveTA1053";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 -0.32670195733908231 10 -17.360130515992612 
		27 -1.2601360567850637 31 -1.2601360567850637 35 -1.2601360567850637 37 -1.2601360567850637 
		41 -1.2601360567850637;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTA -n "animCurveTA1054";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0.92893831569742136 10 38.519892098503192 
		27 5.0162666862465679 31 5.0162666862465679 35 5.0162666862465679 37 5.0162666862465679 
		41 5.0162666862465679;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTU -n "animCurveTU402";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 10 0 27 0 31 0 35 0 37 0 41 0;
	setAttr -s 8 ".kit[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTU -n "animCurveTU403";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 10 0 27 0 31 0 35 0 37 0 41 0;
	setAttr -s 8 ".kit[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTU -n "animCurveTU404";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 5.7407410315871159 10 31 27 31 31 
		31 35 31 37 31 41 31;
	setAttr -s 8 ".kit[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTU -n "animCurveTU405";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 3.5370371308207678 10 19.1 27 19.1 
		31 19.1 35 19.1 37 19.1 41 19.1;
	setAttr -s 8 ".kit[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTU -n "animCurveTU406";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 1.9074075228185021 10 10.3 27 10.3 
		31 10.3 35 10.3 37 10.3 41 10.3;
	setAttr -s 8 ".kit[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTU -n "animCurveTU407";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 10 0 27 0 31 0 35 0 37 0 41 0;
	setAttr -s 8 ".kit[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTU -n "animCurveTU408";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 3.5000002310576552 10 18.900000000000002 
		27 18.900000000000002 31 18.900000000000002 35 18.900000000000002 37 18.900000000000002 
		41 18.900000000000002;
	setAttr -s 8 ".kit[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTU -n "animCurveTU409";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 4.277777988765612 10 23.099999999999998 
		27 23.099999999999998 31 23.099999999999998 35 23.099999999999998 37 23.099999999999998 
		41 23.099999999999998;
	setAttr -s 8 ".kit[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTU -n "animCurveTU410";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 -0.018518519061669545 10 -0.099999999999999645 
		27 -0.099999999999999645 31 -0.099999999999999645 35 -0.099999999999999645 37 -0.099999999999999645 
		41 -0.099999999999999645;
	setAttr -s 8 ".kit[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTU -n "animCurveTU411";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 10 0 27 0 31 0 35 0 37 0 41 0;
	setAttr -s 8 ".kit[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTU -n "animCurveTU412";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 8.7407412825731807 10 47.2 27 47.2 
		31 47.2 35 47.2 37 47.2 41 47.2;
	setAttr -s 8 ".kit[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTU -n "animCurveTU413";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 10 0 27 0 31 0 35 0 37 0 41 0;
	setAttr -s 8 ".kit[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTA -n "animCurveTA1055";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 4.4889778968817069 10 24.240479662773378 
		27 24.240479662773378 31 -10.623109808853648 35 24.240479662773378 37 24.240479662773378 
		41 24.240479662773378;
	setAttr -s 8 ".kit[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTA -n "animCurveTA1056";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 -5.4776969861539913 10 -29.579562147788948 
		27 -29.579562147788948 31 -3.8032961122957598 35 -29.579562147788948 37 -29.579562147788948 
		41 -29.579562147788948;
	setAttr -s 8 ".kit[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTA -n "animCurveTA1057";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -2.5999764661798822e-011 4 -0.66975292718089363 
		10 -3.6166656418517951 27 -3.6166656418517951 31 16.600484989037145 35 -3.6166656418517951 
		37 -3.6166656418517951 41 -3.6166656418517951;
	setAttr -s 8 ".kit[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kot[0:7]"  3 10 9 10 10 3 1 3;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTU -n "animCurveTU414";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 27 -14.8 44 -14.8;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.029433349147439003;
	setAttr -s 5 ".kiy[4]"  -0.99956679344177246;
	setAttr -s 5 ".kox[4]"  0.029433349147439003;
	setAttr -s 5 ".koy[4]"  -0.99956679344177246;
createNode animCurveTU -n "animCurveTU415";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 27 0 44 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU416";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 27 32.7 44 32.7;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.013326109386980534;
	setAttr -s 5 ".kiy[4]"  0.99991118907928467;
	setAttr -s 5 ".kox[4]"  0.013326109386980534;
	setAttr -s 5 ".koy[4]"  0.99991118907928467;
createNode animCurveTU -n "animCurveTU417";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 27 14.700000000000001 44 14.700000000000001;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.029633402824401855;
	setAttr -s 5 ".kiy[4]"  0.99956083297729492;
	setAttr -s 5 ".kox[4]"  0.029633402824401855;
	setAttr -s 5 ".koy[4]"  0.99956083297729492;
createNode animCurveTU -n "animCurveTU418";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 27 10.3 44 10.3;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.042273085564374924;
	setAttr -s 5 ".kiy[4]"  0.99910610914230347;
	setAttr -s 5 ".kox[4]"  0.042273085564374924;
	setAttr -s 5 ".koy[4]"  0.99910610914230347;
createNode animCurveTU -n "animCurveTU419";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 27 0 44 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU420";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 27 16.4 44 16.4;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.026563933119177818;
	setAttr -s 5 ".kiy[4]"  0.99964714050292969;
	setAttr -s 5 ".kox[4]"  0.026563933119177818;
	setAttr -s 5 ".koy[4]"  0.99964714050292969;
createNode animCurveTU -n "animCurveTU421";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 27 15.5 44 15.5;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.028105186298489571;
	setAttr -s 5 ".kiy[4]"  0.99960500001907349;
	setAttr -s 5 ".kox[4]"  0.028105186298489571;
	setAttr -s 5 ".koy[4]"  0.99960500001907349;
createNode animCurveTU -n "animCurveTU422";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 27 14.700000000000001 44 14.700000000000001;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.029633402824401855;
	setAttr -s 5 ".kiy[4]"  0.99956083297729492;
	setAttr -s 5 ".kox[4]"  0.029633402824401855;
	setAttr -s 5 ".koy[4]"  0.99956083297729492;
createNode animCurveTU -n "animCurveTU423";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 27 0 44 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU424";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 27 30.1 44 30.1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.014476972632110119;
	setAttr -s 5 ".kiy[4]"  0.99989521503448486;
	setAttr -s 5 ".kox[4]"  0.014476972632110119;
	setAttr -s 5 ".koy[4]"  0.99989521503448486;
createNode animCurveTU -n "animCurveTU425";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 27 9.3 44 9.3;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.046809125691652298;
	setAttr -s 5 ".kiy[4]"  0.99890387058258057;
	setAttr -s 5 ".kox[4]"  0.046809125691652298;
	setAttr -s 5 ".koy[4]"  0.99890387058258057;
createNode animCurveTA -n "animCurveTA1058";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 27 24.080359636206918 44 24.080359636206918;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.71980845928192139;
	setAttr -s 5 ".kiy[4]"  0.69417273998260498;
	setAttr -s 5 ".kox[4]"  0.71980845928192139;
	setAttr -s 5 ".koy[4]"  0.69417273998260498;
createNode animCurveTA -n "animCurveTA1059";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 27 6.4984720192370302 44 6.4984720192370302;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.96776241064071655;
	setAttr -s 5 ".kiy[4]"  0.25186493992805481;
	setAttr -s 5 ".kox[4]"  0.96776241064071655;
	setAttr -s 5 ".koy[4]"  0.25186493992805481;
createNode animCurveTA -n "animCurveTA1060";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -2.5997909391022333e-011 4 0 10 0 27 
		13.430725208127319 44 13.430725208127319;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.8806840181350708;
	setAttr -s 5 ".kiy[4]"  0.47370421886444092;
	setAttr -s 5 ".kox[4]"  0.8806840181350708;
	setAttr -s 5 ".koy[4]"  0.47370421886444092;
createNode animCurveTA -n "animCurveTA1061";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -6.7832614176793165 4 -7.4048622158363004 
		7 -4.305289781676354 10 -10.139905536638178 13 -21.112648899032472 15 -22.522385200927697 
		20 -16.280684176709581 27 30.403197618365656 31 -3.7044033445255322 35 11.633615780611329 
		37 7.6878128473836638 41 -2.7130827950898371;
	setAttr -s 12 ".kit[0:11]"  3 10 10 9 9 9 9 10 
		10 3 1 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 9 9 9 9 10 
		10 3 1 3;
	setAttr -s 12 ".kix[10:11]"  1 1;
	setAttr -s 12 ".kiy[10:11]"  0 0;
	setAttr -s 12 ".kox[10:11]"  1 1;
	setAttr -s 12 ".koy[10:11]"  0 0;
createNode animCurveTA -n "animCurveTA1062";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 4 0.03907512133644743 7 -4.6955957030183404 
		10 0.15071831745471567 13 2.3641242150461061 15 9.7411183508484367 20 -6.8697789516971319 
		27 -10.226080347363066 31 -13.537510553638761 35 -16.07429140368934 37 -15.384788963492229 
		41 -13.73224713970454;
	setAttr -s 12 ".kit[0:11]"  3 10 10 9 9 9 9 10 
		10 3 1 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 9 9 9 9 10 
		10 3 1 3;
	setAttr -s 12 ".kix[10:11]"  1 1;
	setAttr -s 12 ".kiy[10:11]"  0 0;
	setAttr -s 12 ".kox[10:11]"  1 1;
	setAttr -s 12 ".koy[10:11]"  0 0;
createNode animCurveTA -n "animCurveTA1063";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 4 -1.7831323105116559 7 -6.3101627768081148 
		10 -9.6289140312173362 13 -6.1288137124067426 15 2.5728005710307844 20 9.1721555504607686 
		27 2.2303416578850284 31 11.544252172803194 35 9.7504123924195056 37 10.820517971750659 
		41 11.310558617565819;
	setAttr -s 12 ".kit[0:11]"  3 10 10 9 9 9 9 10 
		10 3 1 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 9 9 9 9 10 
		10 3 1 3;
	setAttr -s 12 ".kix[10:11]"  1 1;
	setAttr -s 12 ".kiy[10:11]"  0 0;
	setAttr -s 12 ".kox[10:11]"  1 1;
	setAttr -s 12 ".koy[10:11]"  0 0;
createNode animCurveTA -n "animCurveTA1064";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -17.428736070727251 4 -14.120522239169778 
		7 25.495402652392848 10 15.83358527511813 14 -14.766044428714249 20 -9.2306235593622326 
		27 22.85800573764395 31 26.799493262697695 35 28.696852204117533 37 42.471989342760139 
		41 41.12919577886165;
	setAttr -s 11 ".kit[0:10]"  3 10 9 9 10 10 10 10 
		3 1 3;
	setAttr -s 11 ".kot[0:10]"  3 10 9 9 10 10 10 10 
		3 1 3;
	setAttr -s 11 ".kix[9:10]"  1 1;
	setAttr -s 11 ".kiy[9:10]"  0 0;
	setAttr -s 11 ".kox[9:10]"  1 1;
	setAttr -s 11 ".koy[9:10]"  0 0;
createNode animCurveTA -n "animCurveTA1065";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 4 -1.223125283490029 7 0.80194173813007108 
		10 1.8834037497593674 14 4.7239151153708896 20 -13.270375409103773 27 4.1326692539472596 
		31 5.1997818623298748 35 4.790047371813527 37 1.6745112188374434 41 5.3951241578818774;
	setAttr -s 11 ".kit[0:10]"  3 10 9 9 10 10 10 10 
		3 1 3;
	setAttr -s 11 ".kot[0:10]"  3 10 9 9 10 10 10 10 
		3 1 3;
	setAttr -s 11 ".kix[9:10]"  1 1;
	setAttr -s 11 ".kiy[9:10]"  0 0;
	setAttr -s 11 ".kox[9:10]"  1 1;
	setAttr -s 11 ".koy[9:10]"  0 0;
createNode animCurveTA -n "animCurveTA1066";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 4 2.1294464199138945 7 3.0541269523344114 
		10 12.122887111033684 14 8.7288183382029416 20 1.004405597685643 27 12.079816883025227 
		31 12.147232011437689 35 12.312446015976821 37 13.093182787309955 41 2.7025387670759584;
	setAttr -s 11 ".kit[0:10]"  3 10 9 9 10 10 10 10 
		3 1 3;
	setAttr -s 11 ".kot[0:10]"  3 10 9 9 10 10 10 10 
		3 1 3;
	setAttr -s 11 ".kix[9:10]"  1 1;
	setAttr -s 11 ".kiy[9:10]"  0 0;
	setAttr -s 11 ".kox[9:10]"  1 1;
	setAttr -s 11 ".koy[9:10]"  0 0;
createNode animCurveTA -n "animCurveTA1067";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.4708878214939103 5 57.000190165003687 
		10 52.717870984519777 15 4.646924406096427 20 -3.9752804980488139 25 43.968434850556527 
		30 43.493687315419635 36 110.85592721869237 42 38.109177204215122;
createNode animCurveTA -n "animCurveTA1068";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.25443561721892211 5 -0.21942941147104242 
		10 -15.055761805983915 15 -11.862069073602369 20 -22.77694652072001 25 -24.010317215371941 
		30 -22.783724065247171 36 -19.912016490179838 42 -12.58103861026223;
createNode animCurveTA -n "animCurveTA1069";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.091485475083844844 5 -0.15798061857650234 
		10 9.2050211987631574 15 31.692021847255599 20 17.046653514540754 25 17.427445580605426 
		30 -2.4131963558362988 36 -17.906328509604855 42 0.13727731044092908;
createNode animCurveTA -n "animCurveTA1070";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 23.336665386532097 5 47.28535027136072 
		11 35.996134397281203 16 9.7030944005036464 25 36.158307754655901 32 23.336665386532097 
		40 23.783248734265726;
createNode animCurveTA -n "animCurveTA1071";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 8.1029981786794743 5 4.2218458743800875 
		11 4.3938042967857225 16 20.785672555506665 25 15.973859074899433 32 8.1029981786794743 
		40 12.823880594175916;
createNode animCurveTA -n "animCurveTA1072";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.50725407442172754 5 -9.9592769292570473 
		11 -8.1369961067301144 16 -6.7123712385685073 25 -8.9496313954748583 32 0.50725407442172754 
		40 -10.053288903287246;
createNode animCurveTA -n "animCurveTA1073";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 24.835011182779763 5 48.659982252463706 
		11 37.381020924901243 16 11.546510897958751 25 37.936449161116762 32 24.835011182779763 
		40 25.43367938957849;
createNode animCurveTA -n "animCurveTA1074";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 8.797338172790246 5 4.1417412395904964 
		11 4.6861681244346052 16 21.87194882426526 25 16.254480766132197 32 8.797338172790246 
		40 13.50208941715837;
createNode animCurveTA -n "animCurveTA1075";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 2.292138075156855 5 -8.0587848948953145 
		11 -6.2566332089699763 16 -5.042626762020392 25 -6.9966357501919969 32 2.292138075156855 
		40 -8.233712194199347;
createNode animCurveTA -n "animCurveTA1076";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 23.301068501753321 5 47.2477620401718 
		11 35.959164475772397 16 9.6734871900847814 25 36.12144199487313 32 23.301068501753321 
		40 23.748432680589055;
createNode animCurveTA -n "animCurveTA1077";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 8.0613848222424949 5 4.1797451934067267 
		11 4.3510053323242879 16 20.747593942685278 25 15.93105840508986 32 8.0613848222424949 
		40 12.782190290825273;
createNode animCurveTA -n "animCurveTA1078";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.51738059143418313 5 -9.9670258421564188 
		11 -8.1363312757405168 16 -6.6914626636622598 25 -8.9490679846208536 32 0.51738059143418313 
		40 -10.043340563823316;
createNode animCurveTA -n "animCurveTA1079";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 23.260291830862055 5 47.192706321002603 
		11 35.913907151446651 16 10.224156815004765 25 35.688227633148536 32 23.260291830862055 
		40 23.697425300869366;
createNode animCurveTA -n "animCurveTA1080";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.56549606964789179 5 -3.7060114227128773 
		11 -4.0662593686848139 16 12.351428967045276 25 7.5127017276402395 32 -0.56549606964789179 
		40 4.1555927444734433;
createNode animCurveTA -n "animCurveTA1081";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.51381757445804221 5 -13.468096509451811 
		11 -10.028209543421093 16 -4.6216700630335881 25 -10.876486559781778 32 0.51381757445804221 
		40 -10.114193184720863;
createNode animCurveTA -n "animCurveTA1082";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 22.496381038005367 5 46.428923820756658 
		11 35.150072433261322 16 9.4604865586333933 25 34.924178275498619 32 22.496381038005367 
		40 22.933511692456399;
createNode animCurveTA -n "animCurveTA1083";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.57037312135576823 5 -3.7104686067822743 
		11 -4.0710176650004719 16 12.346677293592412 25 7.5079392529021023 32 -0.57037312135576823 
		40 4.1507158452184569;
createNode animCurveTA -n "animCurveTA1084";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.51381619645346732 5 -13.47008034612162 
		11 -10.029281943004877 16 -4.620545296822347 25 -10.877546590934946 32 0.51381619645346732 
		40 -10.114231872798447;
createNode animCurveTA -n "animCurveTA1085";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 23.186653625699083 5 47.119204589809932 
		11 35.840355415504469 16 10.150716628263869 25 35.614426374502195 32 23.186653625699083 
		40 23.623769173390489;
createNode animCurveTA -n "animCurveTA1086";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.57034051494142646 5 -3.7103644549374111 
		11 -4.0709457020131961 16 12.346667719133432 25 7.5080105383983984 32 -0.57034051494142646 
		40 4.1507498489435264;
createNode animCurveTA -n "animCurveTA1087";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.51363290912884429 5 -13.470234963726123 
		11 -10.029454061356351 16 -4.6207356081114312 25 -10.877720044488559 32 0.51363290912884429 
		40 -10.114415378267674;
createNode animCurveTA -n "animCurveTA1088";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 4.0372687674684382 5 24.404395400641569 
		10 29.260204239762448 15 -52.45605154112264 21 39.637390772036234 30 67.799143858277674 
		40 81.390146062831263;
createNode animCurveTA -n "animCurveTA1089";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -1.1757553538397181 5 -1.2016837750301568 
		10 6.2250732391982053 15 -8.077975747707022 21 -4.2840527511107593 30 -5.2776860657962228 
		40 -10.538528906444268;
createNode animCurveTA -n "animCurveTA1090";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.6041892955772511 5 9.7151324216818509 
		10 -5.113028626790868 15 -12.264994699556585 21 -0.40883163018782698 30 -7.5002279261729097 
		40 -9.8624652529549639;
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
connectAttr "deathSource.cl" "clipLibrary2.sc[0]";
connectAttr "animCurveTU390.a" "clipLibrary2.cel[0].cev[0].cevr";
connectAttr "animCurveTU391.a" "clipLibrary2.cel[0].cev[1].cevr";
connectAttr "animCurveTA1012.a" "clipLibrary2.cel[0].cev[2].cevr";
connectAttr "animCurveTA1013.a" "clipLibrary2.cel[0].cev[3].cevr";
connectAttr "animCurveTA1014.a" "clipLibrary2.cel[0].cev[4].cevr";
connectAttr "animCurveTA1015.a" "clipLibrary2.cel[0].cev[5].cevr";
connectAttr "animCurveTA1016.a" "clipLibrary2.cel[0].cev[6].cevr";
connectAttr "animCurveTA1017.a" "clipLibrary2.cel[0].cev[7].cevr";
connectAttr "animCurveTA1018.a" "clipLibrary2.cel[0].cev[8].cevr";
connectAttr "animCurveTA1019.a" "clipLibrary2.cel[0].cev[9].cevr";
connectAttr "animCurveTA1020.a" "clipLibrary2.cel[0].cev[10].cevr";
connectAttr "animCurveTA1021.a" "clipLibrary2.cel[0].cev[11].cevr";
connectAttr "animCurveTA1022.a" "clipLibrary2.cel[0].cev[12].cevr";
connectAttr "animCurveTA1023.a" "clipLibrary2.cel[0].cev[13].cevr";
connectAttr "animCurveTA1024.a" "clipLibrary2.cel[0].cev[14].cevr";
connectAttr "animCurveTA1025.a" "clipLibrary2.cel[0].cev[15].cevr";
connectAttr "animCurveTA1026.a" "clipLibrary2.cel[0].cev[16].cevr";
connectAttr "animCurveTA1027.a" "clipLibrary2.cel[0].cev[17].cevr";
connectAttr "animCurveTA1028.a" "clipLibrary2.cel[0].cev[18].cevr";
connectAttr "animCurveTA1029.a" "clipLibrary2.cel[0].cev[19].cevr";
connectAttr "animCurveTA1030.a" "clipLibrary2.cel[0].cev[20].cevr";
connectAttr "animCurveTA1031.a" "clipLibrary2.cel[0].cev[21].cevr";
connectAttr "animCurveTA1032.a" "clipLibrary2.cel[0].cev[22].cevr";
connectAttr "animCurveTA1033.a" "clipLibrary2.cel[0].cev[23].cevr";
connectAttr "animCurveTA1034.a" "clipLibrary2.cel[0].cev[24].cevr";
connectAttr "animCurveTA1035.a" "clipLibrary2.cel[0].cev[25].cevr";
connectAttr "animCurveTL382.a" "clipLibrary2.cel[0].cev[26].cevr";
connectAttr "animCurveTL383.a" "clipLibrary2.cel[0].cev[27].cevr";
connectAttr "animCurveTL384.a" "clipLibrary2.cel[0].cev[28].cevr";
connectAttr "animCurveTL385.a" "clipLibrary2.cel[0].cev[29].cevr";
connectAttr "animCurveTL386.a" "clipLibrary2.cel[0].cev[30].cevr";
connectAttr "animCurveTL387.a" "clipLibrary2.cel[0].cev[31].cevr";
connectAttr "animCurveTA1036.a" "clipLibrary2.cel[0].cev[32].cevr";
connectAttr "animCurveTA1037.a" "clipLibrary2.cel[0].cev[33].cevr";
connectAttr "animCurveTA1038.a" "clipLibrary2.cel[0].cev[34].cevr";
connectAttr "animCurveTL388.a" "clipLibrary2.cel[0].cev[35].cevr";
connectAttr "animCurveTL389.a" "clipLibrary2.cel[0].cev[36].cevr";
connectAttr "animCurveTL390.a" "clipLibrary2.cel[0].cev[37].cevr";
connectAttr "animCurveTA1039.a" "clipLibrary2.cel[0].cev[38].cevr";
connectAttr "animCurveTA1040.a" "clipLibrary2.cel[0].cev[39].cevr";
connectAttr "animCurveTA1041.a" "clipLibrary2.cel[0].cev[40].cevr";
connectAttr "animCurveTL391.a" "clipLibrary2.cel[0].cev[41].cevr";
connectAttr "animCurveTL392.a" "clipLibrary2.cel[0].cev[42].cevr";
connectAttr "animCurveTL393.a" "clipLibrary2.cel[0].cev[43].cevr";
connectAttr "animCurveTA1042.a" "clipLibrary2.cel[0].cev[44].cevr";
connectAttr "animCurveTA1043.a" "clipLibrary2.cel[0].cev[45].cevr";
connectAttr "animCurveTA1044.a" "clipLibrary2.cel[0].cev[46].cevr";
connectAttr "animCurveTL394.a" "clipLibrary2.cel[0].cev[47].cevr";
connectAttr "animCurveTL395.a" "clipLibrary2.cel[0].cev[48].cevr";
connectAttr "animCurveTL396.a" "clipLibrary2.cel[0].cev[49].cevr";
connectAttr "animCurveTU392.a" "clipLibrary2.cel[0].cev[50].cevr";
connectAttr "animCurveTA1045.a" "clipLibrary2.cel[0].cev[51].cevr";
connectAttr "animCurveTA1046.a" "clipLibrary2.cel[0].cev[52].cevr";
connectAttr "animCurveTA1047.a" "clipLibrary2.cel[0].cev[53].cevr";
connectAttr "animCurveTL397.a" "clipLibrary2.cel[0].cev[54].cevr";
connectAttr "animCurveTL398.a" "clipLibrary2.cel[0].cev[55].cevr";
connectAttr "animCurveTL399.a" "clipLibrary2.cel[0].cev[56].cevr";
connectAttr "animCurveTU393.a" "clipLibrary2.cel[0].cev[57].cevr";
connectAttr "animCurveTA1048.a" "clipLibrary2.cel[0].cev[58].cevr";
connectAttr "animCurveTA1049.a" "clipLibrary2.cel[0].cev[59].cevr";
connectAttr "animCurveTA1050.a" "clipLibrary2.cel[0].cev[60].cevr";
connectAttr "animCurveTL400.a" "clipLibrary2.cel[0].cev[61].cevr";
connectAttr "animCurveTL401.a" "clipLibrary2.cel[0].cev[62].cevr";
connectAttr "animCurveTL402.a" "clipLibrary2.cel[0].cev[63].cevr";
connectAttr "animCurveTU394.a" "clipLibrary2.cel[0].cev[64].cevr";
connectAttr "animCurveTU395.a" "clipLibrary2.cel[0].cev[65].cevr";
connectAttr "animCurveTU396.a" "clipLibrary2.cel[0].cev[66].cevr";
connectAttr "animCurveTU397.a" "clipLibrary2.cel[0].cev[67].cevr";
connectAttr "animCurveTA1051.a" "clipLibrary2.cel[0].cev[68].cevr";
connectAttr "animCurveTA1052.a" "clipLibrary2.cel[0].cev[69].cevr";
connectAttr "animCurveTU398.a" "clipLibrary2.cel[0].cev[70].cevr";
connectAttr "animCurveTU399.a" "clipLibrary2.cel[0].cev[71].cevr";
connectAttr "animCurveTU400.a" "clipLibrary2.cel[0].cev[72].cevr";
connectAttr "animCurveTU401.a" "clipLibrary2.cel[0].cev[73].cevr";
connectAttr "animCurveTA1053.a" "clipLibrary2.cel[0].cev[74].cevr";
connectAttr "animCurveTA1054.a" "clipLibrary2.cel[0].cev[75].cevr";
connectAttr "animCurveTU402.a" "clipLibrary2.cel[0].cev[76].cevr";
connectAttr "animCurveTU403.a" "clipLibrary2.cel[0].cev[77].cevr";
connectAttr "animCurveTU404.a" "clipLibrary2.cel[0].cev[78].cevr";
connectAttr "animCurveTU405.a" "clipLibrary2.cel[0].cev[79].cevr";
connectAttr "animCurveTU406.a" "clipLibrary2.cel[0].cev[80].cevr";
connectAttr "animCurveTU407.a" "clipLibrary2.cel[0].cev[81].cevr";
connectAttr "animCurveTU408.a" "clipLibrary2.cel[0].cev[82].cevr";
connectAttr "animCurveTU409.a" "clipLibrary2.cel[0].cev[83].cevr";
connectAttr "animCurveTU410.a" "clipLibrary2.cel[0].cev[84].cevr";
connectAttr "animCurveTU411.a" "clipLibrary2.cel[0].cev[85].cevr";
connectAttr "animCurveTU412.a" "clipLibrary2.cel[0].cev[86].cevr";
connectAttr "animCurveTU413.a" "clipLibrary2.cel[0].cev[87].cevr";
connectAttr "animCurveTA1055.a" "clipLibrary2.cel[0].cev[88].cevr";
connectAttr "animCurveTA1056.a" "clipLibrary2.cel[0].cev[89].cevr";
connectAttr "animCurveTA1057.a" "clipLibrary2.cel[0].cev[90].cevr";
connectAttr "animCurveTU414.a" "clipLibrary2.cel[0].cev[91].cevr";
connectAttr "animCurveTU415.a" "clipLibrary2.cel[0].cev[92].cevr";
connectAttr "animCurveTU416.a" "clipLibrary2.cel[0].cev[93].cevr";
connectAttr "animCurveTU417.a" "clipLibrary2.cel[0].cev[94].cevr";
connectAttr "animCurveTU418.a" "clipLibrary2.cel[0].cev[95].cevr";
connectAttr "animCurveTU419.a" "clipLibrary2.cel[0].cev[96].cevr";
connectAttr "animCurveTU420.a" "clipLibrary2.cel[0].cev[97].cevr";
connectAttr "animCurveTU421.a" "clipLibrary2.cel[0].cev[98].cevr";
connectAttr "animCurveTU422.a" "clipLibrary2.cel[0].cev[99].cevr";
connectAttr "animCurveTU423.a" "clipLibrary2.cel[0].cev[100].cevr";
connectAttr "animCurveTU424.a" "clipLibrary2.cel[0].cev[101].cevr";
connectAttr "animCurveTU425.a" "clipLibrary2.cel[0].cev[102].cevr";
connectAttr "animCurveTA1058.a" "clipLibrary2.cel[0].cev[103].cevr";
connectAttr "animCurveTA1059.a" "clipLibrary2.cel[0].cev[104].cevr";
connectAttr "animCurveTA1060.a" "clipLibrary2.cel[0].cev[105].cevr";
connectAttr "animCurveTA1061.a" "clipLibrary2.cel[0].cev[106].cevr";
connectAttr "animCurveTA1062.a" "clipLibrary2.cel[0].cev[107].cevr";
connectAttr "animCurveTA1063.a" "clipLibrary2.cel[0].cev[108].cevr";
connectAttr "animCurveTA1064.a" "clipLibrary2.cel[0].cev[109].cevr";
connectAttr "animCurveTA1065.a" "clipLibrary2.cel[0].cev[110].cevr";
connectAttr "animCurveTA1066.a" "clipLibrary2.cel[0].cev[111].cevr";
connectAttr "animCurveTA1067.a" "clipLibrary2.cel[0].cev[112].cevr";
connectAttr "animCurveTA1068.a" "clipLibrary2.cel[0].cev[113].cevr";
connectAttr "animCurveTA1069.a" "clipLibrary2.cel[0].cev[114].cevr";
connectAttr "animCurveTA1070.a" "clipLibrary2.cel[0].cev[124].cevr";
connectAttr "animCurveTA1071.a" "clipLibrary2.cel[0].cev[125].cevr";
connectAttr "animCurveTA1072.a" "clipLibrary2.cel[0].cev[126].cevr";
connectAttr "animCurveTA1073.a" "clipLibrary2.cel[0].cev[127].cevr";
connectAttr "animCurveTA1074.a" "clipLibrary2.cel[0].cev[128].cevr";
connectAttr "animCurveTA1075.a" "clipLibrary2.cel[0].cev[129].cevr";
connectAttr "animCurveTA1076.a" "clipLibrary2.cel[0].cev[130].cevr";
connectAttr "animCurveTA1077.a" "clipLibrary2.cel[0].cev[131].cevr";
connectAttr "animCurveTA1078.a" "clipLibrary2.cel[0].cev[132].cevr";
connectAttr "animCurveTA1079.a" "clipLibrary2.cel[0].cev[133].cevr";
connectAttr "animCurveTA1080.a" "clipLibrary2.cel[0].cev[134].cevr";
connectAttr "animCurveTA1081.a" "clipLibrary2.cel[0].cev[135].cevr";
connectAttr "animCurveTA1082.a" "clipLibrary2.cel[0].cev[136].cevr";
connectAttr "animCurveTA1083.a" "clipLibrary2.cel[0].cev[137].cevr";
connectAttr "animCurveTA1084.a" "clipLibrary2.cel[0].cev[138].cevr";
connectAttr "animCurveTA1085.a" "clipLibrary2.cel[0].cev[139].cevr";
connectAttr "animCurveTA1086.a" "clipLibrary2.cel[0].cev[140].cevr";
connectAttr "animCurveTA1087.a" "clipLibrary2.cel[0].cev[141].cevr";
connectAttr "animCurveTA1088.a" "clipLibrary2.cel[0].cev[145].cevr";
connectAttr "animCurveTA1089.a" "clipLibrary2.cel[0].cev[146].cevr";
connectAttr "animCurveTA1090.a" "clipLibrary2.cel[0].cev[147].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of death2B.ma
