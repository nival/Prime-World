//Maya ASCII 2008 scene
//Name: death1B.ma
//Last modified: Mon, Oct 19, 2009 12:48:38 PM
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
createNode animClip -n "deathSource";
	setAttr ".ihi" 0;
	setAttr -s 148 ".ac[0:147]" no no yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes no no no no no no yes 
		yes yes no no no yes yes yes no no no yes yes yes no no no no yes yes yes no no no 
		no yes yes yes no no no no no no no yes yes no no no no yes yes no no no no no no 
		no no no no no no yes yes yes no no no no no no no no no no no no yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".se" 44;
	setAttr ".ci" no;
createNode animCurveTU -n "animCurveTU390";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU391";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1012";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -16.433008012612902 2 -16.433008012612902 
		4 -38.909404384040478 9 -52.982630412197246 12 -10.715284215376348 15 19.919776670238068 
		18 27.200330962087019 21 34.703645330400164 23 42.580909015807045 24 42.580909015807045;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1013";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 46.484153693874759 2 46.484153693874759 
		4 37.620407363861027 9 18.969271152563906 12 -13.580387449477687 15 -9.2440690766345242 
		18 -2.4234483344895157 21 -7.4936459423932611 23 -4.8608581933178909 24 -4.8608581933178909;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1014";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -14.962212153601083 2 -14.962212153601083 
		4 -25.237040262795077 9 -40.051154191297094 12 -69.800695275318816 15 -112.83750880854319 
		18 -141.83482224691099 21 -141.55190415200073 23 -141.25139094410608 24 -141.25139094410608;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1015";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -22.136766656027952 2 -35.152470004478879 
		4 -52.394093049430531 9 -39.502523991204846 12 -67.572534351851147 15 -38.535406781556134 
		18 -3.8593189014467217 21 -3.8593189014467217 23 -3.8593189014467217 24 -3.8593189014467217;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1016";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.68849474610917216 2 0.68849474610917216 
		4 0.68849474610917216 9 0.68849474610917216 12 0.68849474610917216 15 0.68849474610917216 
		18 0.68849474610917216 20 0.68849474610917216 22 0.68849474610917216 24 0.68849474610917216;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1017";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.42006444830693845 2 -0.42006444830693845 
		4 -0.42006444830693845 9 -0.42006444830693845 12 -0.42006444830693845 15 -0.42006444830693845 
		18 -0.42006444830693845 20 -0.42006444830693845 22 -0.42006444830693845 24 -0.42006444830693845;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1018";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.63229744012554356 2 -0.63229744012554356 
		4 -0.63229744012554356 9 -0.63229744012554356 12 -0.63229744012554356 15 -0.63229744012554356 
		18 -0.63229744012554356 20 -0.63229744012554356 22 -0.63229744012554356 24 -0.63229744012554356;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1019";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -10.263293154844943 2 -26.282629465243641 
		4 -57.302983027915985 9 -50.223184945021487 12 -29.983194981488637 15 -15.633744961368395 
		18 29.937036658357904 20 29.937036658357904 22 29.937036658357904 24 29.937036658357904;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1020";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 15.824321534293112 2 10.060833090320127 
		4 -13.471916922979908 9 10.627663832851526 12 10.093403448713477 15 -17.47752457427142 
		18 -25.295420090796913 20 -25.295420090796913 22 -25.295420090796913 24 -25.295420090796913;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1021";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -10.818908651033057 2 -24.896880515274741 
		4 -23.578496398856739 9 -31.225089526048286 12 -39.244921555607107 15 4.3324307596524543 
		18 0.87733300005747072 20 -3.2408600180347444 22 -7.6471628925837329 24 -7.6471628925837329;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1022";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 12.875158369523408 2 -13.053714770350085 
		4 -11.962559495145758 9 0.36708846428507347 12 -4.3566147541584836 15 0.49262108698303997 
		18 -14.069427783279867 20 -15.426924956173774 22 -16.784422129067682 24 -16.784422129067682;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1023";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -25.378456988571386 2 -25.378456988571386 
		4 -46.366193912968562 9 -53.480916658451484 12 -26.419313855217531 14 -10.586889306895143 
		17 2.5223253636496978 19 3.6760024057808587 22 6.7780344314902283 24 6.7780344314902283;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1024";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 49.284082676870852 2 49.284082676870852 
		4 40.39258054869007 9 8.8855794161686195 12 -16.816183674413232 14 17.696399484611479 
		17 -2.942794150004111 19 -8.1679422941825148 22 0.48660778962134293 24 0.48660778962134293;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1025";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 34.969087097535308 2 4.2255080418844848 
		4 -5.1131235270670006 9 -18.773908244461172 12 -50.756847780717422 14 -94.254951086181549 
		17 -53.907052294812196 19 -52.253445051424386 22 -51.965455068748277 24 -51.965455068748277;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1026";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -4.2353230899544307 2 -20.315490212658815 
		4 -43.461031360065576 9 -36.632082705253239 12 -50.918953003487303 14 -31.9311751397927 
		17 8.5128347709034617 19 7.2929780400863269 22 6.0731213092691902 24 6.0731213092691902;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1027";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1028";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1029";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1030";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 10.953960758885851 12 40.512206259600035 
		15 142.05055474326264 18 142.05055474326264 20 143.68120036817132 22 146.39894313186329 
		24 146.39894313186329;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1031";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1032";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1033";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -14.515820710620677 2 13.84550679523592 
		4 -22.726840219776836 9 -5.1757049697923501 12 11.750376693429939 15 -39.636423009676371 
		18 20.874689404187176 20 2.3090824120453899 23 20.874689404187176 24 20.874689404187176;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1034";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -17.383598210882599 2 -8.9150174919363447 
		4 0.17580192763602503 9 1.2134227889521036 12 2.1364458394876333 15 -28.335949953908379 
		18 -36.299341823325832 20 -36.540742153933529 23 -36.299341823325832 24 -36.299341823325832;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1035";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1.5268462968664711 2 6.5466553608716893 
		4 -7.1489550794680081 9 -7.7630151049118838 12 -18.737621142042133 15 13.223198170402709 
		18 -4.2777605182133973 20 -0.80600330527560526 23 -4.2777605182133973 24 -4.2777605182133973;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL382";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.00025694328101411035 2 0.00025694328101411035 
		4 0.00025694328101411035 9 0.00025694328101411035 12 0.15906405776318625 15 0.15906405776318625 
		18 -0.23441223597431587 20 -0.22117785024791448 22 -0.20794346452151305 24 -0.20794346452151305;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL383";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 1.0378306815217244 15 
		1.0378306815217244 18 1.0651142056274843 20 1.0935864708558749 22 1.1410402462160985 
		24 1.1410402462160985;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL384";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.12527739251666781 2 -0.12527739251666781 
		4 -0.12527739251666781 9 -0.12527739251666781 12 -0.047845633745343168 15 -0.047845633745343168 
		18 -0.070000147946570737 20 -0.098105304596141779 22 -0.14494723349443941 24 -0.14494723349443941;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL385";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.032833691772160223 2 0.032833691772160223 
		4 0.032833691772160223 9 0.032833691772160223 12 0.23630588557088289 15 0.23630588557088289 
		18 -0.24128009386558696 20 -0.23774760312603296 22 -0.23421511238647894 24 -0.23421511238647894;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL386";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.016062985925156426 2 -0.016062985925156426 
		4 -0.016062985925156426 9 -0.016062985925156426 12 0.89931713335141727 15 0.89931713335141727 
		18 1.1670674402944794 20 1.172447933578026 22 1.1778284268615726 24 1.1778284268615726;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL387";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.11728380015772394 2 0.11728380015772394 
		4 0.11728380015772394 9 0.11728380015772394 12 0.068463700591699456 15 0.068463700591699456 
		18 0.10690431487577162 20 0.12624482263962725 22 0.14558533040348287 24 0.14558533040348287;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1036";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 -7.3112260836245069 9 -7.3112260836245451 
		12 -2.0014643377819148 15 -2.0014643377819206 18 -2.0014643377819277 20 -2.0014643377819277 
		22 -2.0014643377819277 24 -2.0014643377819277;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1037";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 -4.7408186553868044 9 -4.7408186553868328 
		12 0.3419074520292818 15 0.34190745202928335 18 0.34190745202928485 20 0.34190745202928485 
		22 0.34190745202928485 24 0.34190745202928485;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1038";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 3.6719125695963681 2 6.6644929887218822 
		4 -20.937461783784762 9 -61.890305711969546 12 -95.540785949650456 15 -109.35583113935058 
		18 -98.058674033110549 20 -98.058674033110549 22 -98.058674033110549 24 -98.058674033110549;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL388";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.0319338039184065 2 -0.059193150606946944 
		4 -0.035000097775871403 9 -0.14956061062412895 12 -0.6958020618635572 15 -0.63105080937310731 
		18 -0.72392304171759425 20 -0.72392304171759425 22 -0.72392304171759425 24 -0.72392304171759425;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL389";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.00078859512199502824 2 0.043623611283471281 
		4 0.11106894010608603 9 0.46989110004708412 12 0.77496832166552576 15 0.91151861595844175 
		18 1.0251250573290602 20 1.0348386665181186 22 1.0445522757071768 24 1.0445522757071768;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL390";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0.0021500925296142307 4 0.014323414474088482 
		9 -0.0025501783627939717 12 0.023144424663996129 15 0.018568242507129889 18 0.034883052569511366 
		20 0.034883052569511366 22 0.034883052569511366 24 0.034883052569511366;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1039";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -16.236770139599834 2 -16.236770139599834 
		4 -16.236770139599834 9 -16.236770139599834 12 -6.8787089853461474 15 -9.1736577546004714 
		18 -6.8858939453846588 20 -14.407073525989111 22 -21.811589066867327 24 -21.811589066867327;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1040";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 10.673212493936877 15 
		17.2188514304028 18 -4.0229359625376206 20 -39.834323828116233 22 -35.605063887898091 
		24 -35.605063887898091;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1041";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 -18.913635806552819 12 -92.218569318875737 
		15 -112.13278955087033 18 -85.920368687249521 20 -83.726685389669697 22 -83.059090729522836 
		24 -83.059090729522836;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL391";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -6.0000000000892673e-006 2 -6.0000000000892673e-006 
		4 -6.0000000000892673e-006 9 -6.0000000000892673e-006 12 0.25655741068591409 15 0.47706390432155216 
		18 -0.074910529840273285 20 -0.046906762801196267 22 -0.077815408343464496 24 -0.077815408343464496;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL392";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 2.1809999999936394e-005 2 2.1809999999936394e-005 
		4 2.1809999999936394e-005 9 0.019706890549660697 12 0.085697307019844765 15 0.36209032602569269 
		18 0.27669276975156987 20 0.29144578279606909 22 0.31798225157410015 24 0.31798225157410015;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL393";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.040093865534497591 2 -0.040093865534497591 
		4 -0.040093865534497591 9 -0.039268816211945563 12 -0.039220929121699992 15 -0.083825816763793901 
		18 -0.11885220006327954 20 -0.16210847442330539 22 -0.21340438846390108 24 -0.21340438846390108;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1042";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 25.000774638404387 2 25.000774638404387 
		4 25.000774638404387 9 27.894067611017679 12 8.8946364782403773 16 -5.8396815820448911 
		18 18.047288757699086 21 18.864311677507153 23 20.25322014303368 24 19.681334597315228;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1043";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 2.5762851795466757 12 -18.069848426744567 
		16 -3.7527584368566083 18 21.752430336789303 21 21.841310673237402 23 24.469650069164722 
		24 17.607793998180966;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1044";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 -13.034539363478753 12 -68.868308382820388 
		16 -100.3217708301196 18 -85.540218295268772 21 -85.596233308417069 23 -85.446571969091551 
		24 -85.652248321565366;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL394";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0.064851208642175653 
		16 0.35533137668590992 18 -0.10520995309308892 21 -0.046940957873963608 23 -0.09488195511772618 
		24 -0.09488195511772618;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL395";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0.032392623161371641 12 0.067499854430481371 
		16 0.29034178827600293 18 0.3050819504525778 21 0.30729057174052488 23 0.32652118032095068 
		24 0.32652118032095068;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL396";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.038258090963777358 2 0.038258090963777358 
		4 0.038258090963777358 9 0.045617514378419988 12 0.040072057414330897 16 0.084302821784865853 
		18 0.22251423761788197 21 0.2547000309887188 23 0.2811432867976722 24 0.2811432867976722;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU392";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 4 1 9 1 12 1 15 1 18 1 20 1 22 1 24 
		1;
	setAttr -s 9 ".kit[0:8]"  10 9 9 9 9 9 9 9 
		9;
	setAttr -s 9 ".kot[0:8]"  10 5 5 5 5 5 5 5 
		5;
createNode animCurveTA -n "animCurveTA1045";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 3.1010408144269363e-014 4 0 9 0 12 0 
		15 0 18 0 20 0 22 0 24 0;
createNode animCurveTA -n "animCurveTA1046";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 2.1071174764695681e-014 4 0 9 0 12 0 
		15 0 18 0 20 0 22 0 24 0;
createNode animCurveTA -n "animCurveTA1047";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 4.3096515933830644e-013 4 0 9 0 12 0 
		15 0 18 0 20 0 22 0 24 0;
createNode animCurveTL -n "animCurveTL397";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.80799999999999983 4 -0.80799999999999983 
		9 -0.80799999999999983 12 -0.80799999999999983 15 -0.80799999999999983 18 -0.80799999999999983 
		20 -0.80799999999999983 22 -0.80799999999999983 24 -0.80799999999999983;
createNode animCurveTL -n "animCurveTL398";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -8.785595135511054e-016 4 0 9 0 12 0 
		15 0 18 0 20 0 22 0 24 0;
createNode animCurveTL -n "animCurveTL399";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 3.8857805861880479e-016 4 0 9 0 12 0 
		15 0 18 0 20 0 22 0 24 0;
createNode animCurveTU -n "animCurveTU393";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 4 1 9 1 12 1 15 1 18 1 20 1 22 1 24 
		1;
	setAttr -s 9 ".kit[0:8]"  10 9 9 9 9 9 9 9 
		9;
	setAttr -s 9 ".kot[0:8]"  10 5 5 5 5 5 5 5 
		5;
createNode animCurveTA -n "animCurveTA1048";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 4 0 9 0 12 0 15 0 18 0 20 0 22 0 24 
		0;
createNode animCurveTA -n "animCurveTA1049";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 4 0 9 0 12 0 15 0 18 0 20 0 22 0 24 
		0;
createNode animCurveTA -n "animCurveTA1050";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 4 0 9 0 12 0 15 0 18 0 20 0 22 0 24 
		0;
createNode animCurveTL -n "animCurveTL400";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.80789537837891157 4 -0.80789537837891157 
		9 -0.80789537837891157 12 -0.80789537837891157 15 -0.80789537837891157 18 -0.80789537837891157 
		20 -0.80789537837891157 22 -0.80789537837891157 24 -0.80789537837891157;
createNode animCurveTL -n "animCurveTL401";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 2.2649661009579991e-017 4 0 9 0 12 0 
		15 0 18 0 20 0 22 0 24 0;
createNode animCurveTL -n "animCurveTL402";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.5099033134902129e-013 4 0 9 0 12 0 
		15 0 18 0 20 0 22 0 24 0;
createNode animCurveTU -n "animCurveTU394";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU395";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 45 2 45 4 45 9 45 12 45 15 45 18 45 20 
		45 22 45 24 45;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU396";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 45 2 45 4 45 9 45 12 45 15 45 18 45 20 
		45 22 45 24 45;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU397";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 45 2 45 4 45 9 45 12 45 15 45 18 45 20 
		45 22 45 24 45;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1051";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1052";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU398";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU399";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 45 2 45 4 45 9 45 12 45 15 45 18 45 20 
		45 22 45 24 45;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU400";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 45 2 45 4 45 9 45 12 45 15 45 18 45 20 
		45 22 45 24 45;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU401";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 45 2 45 4 45 9 45 12 45 15 45 18 45 20 
		45 22 45 24 45;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1053";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1054";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU402";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU403";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU404";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU405";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU406";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU407";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU408";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU409";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU410";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU411";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU412";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU413";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1055";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1056";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1057";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -2.5999764661798822e-011 2 0 4 0 9 0 
		12 0 15 0 18 0 20 0 22 0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU414";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU415";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU416";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU417";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU418";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU419";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU420";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU421";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU422";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU423";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU424";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU425";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1058";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1059";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 20 0 22 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1060";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -2.5997909391022333e-011 2 0 4 0 9 0 
		12 0 15 0 18 0 20 0 22 0 24 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1061";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -6.7832614176793165 2 -43.087995179172253 
		4 -67.882764069841713 9 -53.288556957455135 12 -48.799848374301135 15 -15.520146425914747 
		18 -23.352465622587932 20 -15.950919214040956 22 -15.950919214040956 24 -15.950919214040956;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1062";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 4.5077237393828433 4 -1.2543185043016476 
		9 0.16179328943496712 12 0.88749995669721771 15 1.4024737406310153 18 4.7734017506785449 
		20 4.5441652839660938 22 4.5441652839660938 24 4.5441652839660938;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1063";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 -2.5782149099142289 4 -14.667191736937637 
		9 -9.2000235350589161 12 -9.1588999954944441 15 -19.667905953945723 18 1.4763673128823509 
		20 2.8867257728965066 22 2.8867257728965066 24 2.8867257728965066;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1064";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -17.428736070727251 2 -17.428736070727251 
		4 -17.428736070727251 9 -17.428736070727251 12 -17.428736070727251 15 -17.428736070727251 
		18 -17.428736070727251 21 -17.428736070727251 24 -17.428736070727251;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1065";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 12 0 15 0 18 0 21 0 24 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1066";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 12 0 15 11.420681562379674 
		18 -8.1358075114085011 21 10.2213763866076 24 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "tank_M_backCloth_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 -17.629285199370276 4 29.847864019391412 
		8 -40.119810110574171 12 -102.61337317454995 14 -119.28558333536756 17 -74.959397221786631 
		20 -100.84697356652725 22 -91.653952305622127;
createNode animCurveTA -n "tank_M_backCloth_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "tank_M_backCloth_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "tank_M_hang_ctrl_rotateZ2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 9.1478457292549002 2 16.559456764651966 
		4 75.957577065764823 7 -17.723430697424885 11 -41.440749591184975 14 -103.92380594869391 
		18 -90.274614816814662 21 -99.232534295598569;
createNode animCurveTA -n "tank_M_hang_ctrl_rotateY2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 -12.298738362651717 7 -4.1129474714386882 
		11 11.941047354958485 14 2.5888724446004079 18 0.98183808994088595 21 2.048883248358722;
createNode animCurveTA -n "tank_M_hang_ctrl_rotateX2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 1.5882811367797507 7 22.635446700715175 
		11 17.161697105587489 14 6.472848098241653 18 6.9001551250232724 21 6.6627697152586585;
createNode animCurveTA -n "tank_R_hang_ctrl_rotateZ2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 9.1478457292549002 2 16.559456764651966 
		4 75.957577065764823 7 -17.723430697424885 11 -41.440749591184975 14 -103.92380594869391 
		18 -90.274614816814662 21 -99.232534295598569;
createNode animCurveTA -n "tank_R_hang_ctrl_rotateY2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 -12.298738362651717 7 -4.1129474714386882 
		11 11.941047354958485 14 2.5888724446004079 18 0.98183808994088595 21 2.048883248358722;
createNode animCurveTA -n "tank_R_hang_ctrl_rotateX2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 1.5882811367797507 7 22.635446700715175 
		11 17.161697105587489 14 6.472848098241653 18 6.9001551250232724 21 6.6627697152586585;
createNode animCurveTA -n "tank_L_hang_ctrl_rotateZ2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 9.1478457292549002 2 16.559456764651966 
		4 75.957577065764823 7 -17.723430697424885 11 -41.440749591184975 14 -103.92380594869391 
		18 -90.274614816814662 21 -99.232534295598569;
createNode animCurveTA -n "tank_L_hang_ctrl_rotateY2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 -12.298738362651717 7 -4.1129474714386882 
		11 11.941047354958485 14 2.5888724446004079 18 0.98183808994088595 21 2.048883248358722;
createNode animCurveTA -n "tank_L_hang_ctrl_rotateX2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 1.5882811367797507 7 22.635446700715175 
		11 17.161697105587489 14 6.472848098241653 18 6.9001551250232724 21 6.6627697152586585;
createNode animCurveTA -n "tank_R_flag_3_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 44.229880222083935 5 -11.981701625663545 
		11 -39.767247242214609 14 -40.283463842025405 17 -22.365524053457886 21 -2.5678226659597989;
createNode animCurveTA -n "tank_R_flag_3_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 21.013421249704315 5 1.9418286290220022 
		11 19.577694706617109 14 23.437914825753374 17 21.87956873490187 21 25.569141257110907;
createNode animCurveTA -n "tank_R_flag_3_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 40.13672852089023 5 0.81538714052962735 
		11 10.195204618287407 14 8.9594810114037848 17 -13.786832938153424 21 -16.230767702415342;
createNode animCurveTA -n "tank_R_flag_2_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.339 2 46.280917356892381 5 -10.609021811836765 
		11 -38.378946938131342 14 -38.889124551981297 17 -20.734657063116749 21 -0.61024703372999856;
createNode animCurveTA -n "tank_R_flag_2_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.339 2 21.027108120852457 5 3.5293000468988533 
		11 21.463276253582812 14 25.324974598773391 17 23.625439702788963 21 26.959885590022637;
createNode animCurveTA -n "tank_R_flag_2_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.339 2 42.165226771847379 5 1.8488044629841069 
		11 10.380457815253466 14 9.1314180316252536 17 -12.991813652535356 21 -14.797711835753825;
createNode animCurveTA -n "tank_R_flag_1_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 44.229880222083935 5 -11.981701625663545 
		11 -39.767247242214609 14 -40.283463842025405 17 -22.365524053457886 21 -2.5678226659597989;
createNode animCurveTA -n "tank_R_flag_1_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 21.013421249704315 5 1.9418286290220022 
		11 19.577694706617109 14 23.437914825753374 17 21.87956873490187 21 25.569141257110907;
createNode animCurveTA -n "tank_R_flag_1_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 40.13672852089023 5 0.81538714052962735 
		11 10.195204618287407 14 8.9594810114037848 17 -13.786832938153424 21 -16.230767702415342;
createNode animCurveTA -n "tank_L_flag_1_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 36.488239430618073 4 -5.1587456940838843 
		14 -20.045871230019344 17 -10.796396161506381 21 -4.9920069746662845 24 -7.7141990948254877;
createNode animCurveTA -n "tank_L_flag_1_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 5.3565600964659446 14 18.667536276531642 
		17 -0.32851948597621006 21 -1.4269056234842621 24 -2.468323155870678;
createNode animCurveTA -n "tank_L_flag_1_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 10.864749486526847 14 7.2925469008272144 
		17 -3.884769261376122 21 -6.2568553738130248 24 -5.42261480084517;
createNode animCurveTA -n "tank_L_flag_2_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 36.488239430618073 4 -5.1587456940838843 
		14 -20.045871230019344 17 -10.796396161506381 21 -4.9920069746662845 24 -7.7141990948254877;
createNode animCurveTA -n "tank_L_flag_2_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 5.3565600964659446 14 18.667536276531642 
		17 -0.32851948597621006 21 -1.4269056234842621 24 -2.468323155870678;
createNode animCurveTA -n "tank_L_flag_2_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 10.864749486526847 14 7.2925469008272144 
		17 -3.884769261376122 21 -6.2568553738130248 24 -5.42261480084517;
createNode animCurveTA -n "tank_L_flag_3_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 36.488239430618073 4 -5.1587456940838843 
		14 -20.045871230019344 17 -10.796396161506381 21 -4.9920069746662845 24 -7.7141990948254877;
createNode animCurveTA -n "tank_L_flag_3_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 5.3565600964659446 14 18.667536276531642 
		17 -0.32851948597621006 21 -1.4269056234842621 24 -2.468323155870678;
createNode animCurveTA -n "tank_L_flag_3_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 10.864749486526847 14 7.2925469008272144 
		17 -3.884769261376122 21 -6.2568553738130248 24 -5.42261480084517;
createNode animCurveTA -n "tank_M_backFeature_ctrl_rotateZ2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -5.5312497278658954 2 -9.2263768521812999 
		6 1.3989953896782896 10 -17.65461968656734 22 -17.65461968656734;
createNode animCurveTA -n "tank_M_backFeature_ctrl_rotateY2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 2 0 22 0;
createNode animCurveTA -n "tank_M_backFeature_ctrl_rotateX2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 2 0 22 0;
createNode animCurveTA -n "tank_M_frontCloth_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 8.1066489615016604 2 -12.071620578984247 
		4 16.787376951783298 6 -30.649631356774911 9 -111.23196854014897 12 -134.43916688743934 
		15 -25.416801619169142 20 -56.635782201772528 23 -19.923266690392836;
createNode animCurveTA -n "tank_M_frontCloth_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 -1.9136727583583983 6 1.0100168992914484 
		9 -2.5390387472086395 12 -0.3949967455311576 15 7.0049756161771413 20 8.4117630024022301 
		23 -0.5934678668883695;
createNode animCurveTA -n "tank_M_frontCloth_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 -4.0454460772668241 6 4.5092456310421989 
		9 0.041303863225862832 12 -33.153137509595666 15 2.5863705740916454 20 38.23003677479101 
		23 1.1960711301561635;
createNode lightLinker -n "lightLinker1";
	setAttr -s 4 ".lnk";
	setAttr -s 4 ".slnk";
select -ne :time1;
	setAttr -av -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 19;
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
connectAttr "tank_M_backCloth_ctrl_rotateZ.a" "clipLibrary2.cel[0].cev[112].cevr"
		;
connectAttr "tank_M_backCloth_ctrl_rotateY.a" "clipLibrary2.cel[0].cev[113].cevr"
		;
connectAttr "tank_M_backCloth_ctrl_rotateX.a" "clipLibrary2.cel[0].cev[114].cevr"
		;
connectAttr "tank_M_hang_ctrl_rotateZ2.a" "clipLibrary2.cel[0].cev[115].cevr";
connectAttr "tank_M_hang_ctrl_rotateY2.a" "clipLibrary2.cel[0].cev[116].cevr";
connectAttr "tank_M_hang_ctrl_rotateX2.a" "clipLibrary2.cel[0].cev[117].cevr";
connectAttr "tank_R_hang_ctrl_rotateZ2.a" "clipLibrary2.cel[0].cev[118].cevr";
connectAttr "tank_R_hang_ctrl_rotateY2.a" "clipLibrary2.cel[0].cev[119].cevr";
connectAttr "tank_R_hang_ctrl_rotateX2.a" "clipLibrary2.cel[0].cev[120].cevr";
connectAttr "tank_L_hang_ctrl_rotateZ2.a" "clipLibrary2.cel[0].cev[121].cevr";
connectAttr "tank_L_hang_ctrl_rotateY2.a" "clipLibrary2.cel[0].cev[122].cevr";
connectAttr "tank_L_hang_ctrl_rotateX2.a" "clipLibrary2.cel[0].cev[123].cevr";
connectAttr "tank_R_flag_3_ctrl_rotateZ1.a" "clipLibrary2.cel[0].cev[124].cevr";
connectAttr "tank_R_flag_3_ctrl_rotateY1.a" "clipLibrary2.cel[0].cev[125].cevr";
connectAttr "tank_R_flag_3_ctrl_rotateX1.a" "clipLibrary2.cel[0].cev[126].cevr";
connectAttr "tank_R_flag_2_ctrl_rotateZ1.a" "clipLibrary2.cel[0].cev[127].cevr";
connectAttr "tank_R_flag_2_ctrl_rotateY1.a" "clipLibrary2.cel[0].cev[128].cevr";
connectAttr "tank_R_flag_2_ctrl_rotateX1.a" "clipLibrary2.cel[0].cev[129].cevr";
connectAttr "tank_R_flag_1_ctrl_rotateZ1.a" "clipLibrary2.cel[0].cev[130].cevr";
connectAttr "tank_R_flag_1_ctrl_rotateY1.a" "clipLibrary2.cel[0].cev[131].cevr";
connectAttr "tank_R_flag_1_ctrl_rotateX1.a" "clipLibrary2.cel[0].cev[132].cevr";
connectAttr "tank_L_flag_1_ctrl_rotateZ1.a" "clipLibrary2.cel[0].cev[133].cevr";
connectAttr "tank_L_flag_1_ctrl_rotateY1.a" "clipLibrary2.cel[0].cev[134].cevr";
connectAttr "tank_L_flag_1_ctrl_rotateX1.a" "clipLibrary2.cel[0].cev[135].cevr";
connectAttr "tank_L_flag_2_ctrl_rotateZ1.a" "clipLibrary2.cel[0].cev[136].cevr";
connectAttr "tank_L_flag_2_ctrl_rotateY1.a" "clipLibrary2.cel[0].cev[137].cevr";
connectAttr "tank_L_flag_2_ctrl_rotateX1.a" "clipLibrary2.cel[0].cev[138].cevr";
connectAttr "tank_L_flag_3_ctrl_rotateZ1.a" "clipLibrary2.cel[0].cev[139].cevr";
connectAttr "tank_L_flag_3_ctrl_rotateY1.a" "clipLibrary2.cel[0].cev[140].cevr";
connectAttr "tank_L_flag_3_ctrl_rotateX1.a" "clipLibrary2.cel[0].cev[141].cevr";
connectAttr "tank_M_backFeature_ctrl_rotateZ2.a" "clipLibrary2.cel[0].cev[142].cevr"
		;
connectAttr "tank_M_backFeature_ctrl_rotateY2.a" "clipLibrary2.cel[0].cev[143].cevr"
		;
connectAttr "tank_M_backFeature_ctrl_rotateX2.a" "clipLibrary2.cel[0].cev[144].cevr"
		;
connectAttr "tank_M_frontCloth_ctrl_rotateZ.a" "clipLibrary2.cel[0].cev[145].cevr"
		;
connectAttr "tank_M_frontCloth_ctrl_rotateY.a" "clipLibrary2.cel[0].cev[146].cevr"
		;
connectAttr "tank_M_frontCloth_ctrl_rotateX.a" "clipLibrary2.cel[0].cev[147].cevr"
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
// End of death1B.ma
