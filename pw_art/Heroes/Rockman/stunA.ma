//Maya ASCII 2008 scene
//Name: stun.ma
//Last modified: Wed, Oct 28, 2009 02:28:11 PM
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
createNode animClip -n "stunSource2";
	setAttr ".ihi" 0;
	setAttr -s 148 ".ac[0:147]" no no yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes no no no no no no yes 
		yes yes no no no yes yes yes no no no yes yes yes no no no no yes yes yes no no no 
		no yes yes yes no no no no no no no yes yes no no no no yes yes no no no no no no 
		no no no no no no yes yes yes no no no no no no no no no no no no yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".se" 60;
	setAttr ".ci" no;
createNode animCurveTU -n "animCurveTU390";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU391";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1012";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 32.156474974395337 15 31.56415190532698 
		30 15.285591806528338 45 8.5483937984735192 60 32.156474974395337;
	setAttr -s 5 ".kit[0:4]"  1 9 9 9 1;
	setAttr -s 5 ".kot[0:4]"  1 9 9 9 1;
	setAttr -s 5 ".kix[0:4]"  0.99418801069259644 0.95927858352661133 
		0.92793142795562744 0.95927858352661133 0.99259054660797119;
	setAttr -s 5 ".kiy[0:4]"  0.10765807330608368 -0.28246194124221802 
		-0.37275078892707825 0.28246194124221802 0.12150727957487106;
	setAttr -s 5 ".kox[0:4]"  0.99418801069259644 0.95927858352661133 
		0.92793142795562744 0.95927858352661133 0.99259054660797119;
	setAttr -s 5 ".koy[0:4]"  0.10765807330608368 -0.28246194124221802 
		-0.37275078892707825 0.28246194124221802 0.12150729447603226;
createNode animCurveTA -n "animCurveTA1013";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 58.825736513632691 15 60.056029982130021 
		30 62.176390056705884 45 56.284114776208824 60 58.825736513632691;
	setAttr -s 5 ".kit[0:4]"  1 9 9 9 1;
	setAttr -s 5 ".kot[0:4]"  1 9 9 9 1;
	setAttr -s 5 ".kix[0:4]"  0.99919819831848145 0.9982944130897522 
		0.99784004688262939 0.9982944130897522 0.99787390232086182;
	setAttr -s 5 ".kiy[0:4]"  0.040038846433162689 0.058380190283060074 
		-0.065690144896507263 -0.058380190283060074 0.065174154937267303;
	setAttr -s 5 ".kox[0:4]"  0.99919813871383667 0.9982944130897522 
		0.99784004688262939 0.9982944130897522 0.99787390232086182;
	setAttr -s 5 ".koy[0:4]"  0.040038850158452988 0.058380190283060074 
		-0.065690144896507263 -0.058380190283060074 0.065174207091331482;
createNode animCurveTA -n "animCurveTA1014";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 61.701954060021336 15 44.098964136272564 
		30 42.370822108596819 45 49.411985521995348 60 61.701954060021336;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 9 9 3;
createNode animCurveTA -n "animCurveTA1015";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -27.072851671765999 15 -19.555970510061776 
		30 -27.072851671765999 45 -38.377002016124862 60 -27.072851671765999;
	setAttr -s 5 ".kit[0:4]"  3 10 9 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 9 10 3;
createNode animCurveTA -n "animCurveTA1016";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.68849474610917216 15 0.68849474610917216 
		30 0.68849474610917216 45 0.68849474610917216 60 0.68849474610917216;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1017";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.42006444830693845 15 -0.42006444830693845 
		30 -0.42006444830693845 45 -0.42006444830693845 60 -0.42006444830693845;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1018";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.63229744012554356 15 -0.63229744012554356 
		30 -0.63229744012554356 45 -0.63229744012554356 60 -0.63229744012554356;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1019";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -6.7713643828181516 15 14.296486022022894 
		30 -6.7713643828181516 45 -17.730015947670374 60 -6.7713643828181516;
	setAttr -s 5 ".kit[0:4]"  2 10 9 10 2;
	setAttr -s 5 ".kot[0:4]"  2 10 9 10 2;
createNode animCurveTA -n "animCurveTA1020";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 22.4516205763505 15 22.403559277476603 
		30 22.4516205763505 45 18.463709645455637 60 22.4516205763505;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1021";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.5658328944520283 15 -8.8176940793701331 
		30 10.774494736112509 45 -8.8176940793701331 60 -1.5658328944520283;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1022";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 17.379897919727409 15 17.468733538032492 
		30 10.056765519025946 45 17.468733538032492 60 17.379897919727409;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1023";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -12.992806719848367 15 7.8171261860747805 
		30 39.613625678416135 45 33.190336437597999 60 -12.992806719848339;
	setAttr -s 5 ".kit[0:4]"  3 10 9 9 3;
	setAttr -s 5 ".kot[0:4]"  3 10 9 9 3;
createNode animCurveTA -n "animCurveTA1024";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 71.202853533331663 15 59.310525069485557 
		30 45.714578342695198 45 60.936014114116652 60 71.202853533331606;
	setAttr -s 5 ".kit[1:4]"  1 3 1 3;
	setAttr -s 5 ".kot[1:4]"  1 3 1 3;
	setAttr -s 5 ".kix[1:4]"  0.8313634991645813 1 0.81338822841644287 
		1;
	setAttr -s 5 ".kiy[1:4]"  -0.55572909116744995 0 0.58172130584716797 
		0;
	setAttr -s 5 ".kox[1:4]"  0.83136343955993652 1 0.81338810920715332 
		1;
	setAttr -s 5 ".koy[1:4]"  -0.5557292103767395 0 0.58172148466110229 
		0;
createNode animCurveTA -n "animCurveTA1025";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 38.33556469294949 15 46.926268331201143 
		30 51.565317018985098 45 61.353426994345369 60 38.33556469294949;
	setAttr -s 5 ".kit[1:4]"  9 1 10 3;
	setAttr -s 5 ".kot[1:4]"  9 1 10 3;
	setAttr -s 5 ".kix[2:4]"  0.90379154682159424 0.97436267137527466 
		1;
	setAttr -s 5 ".kiy[2:4]"  0.42797303199768066 -0.22498300671577454 
		0;
	setAttr -s 5 ".kox[2:4]"  0.90379154682159424 0.97436267137527466 
		1;
	setAttr -s 5 ".koy[2:4]"  0.42797306180000305 -0.22498300671577454 
		0;
createNode animCurveTA -n "animCurveTA1026";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -12.356113894474943 15 -27.51761771031585 
		30 -21.70295201468031 45 -5.3850572315304817 60 -12.356113894474943;
	setAttr -s 5 ".kit[0:4]"  2 9 9 10 2;
	setAttr -s 5 ".kot[0:4]"  2 9 9 10 2;
createNode animCurveTA -n "animCurveTA1027";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1028";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1029";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1030";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -6.2709233671517923 15 -5.9898863844538148 
		30 -10.583039209322235 45 -10.583039209322235 60 -6.2709233671517923;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1031";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 2.1916571121607373 15 2.1710377505709229 
		30 2.5010617691156898 45 2.5010617691156898 60 2.1916571121607373;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1032";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 4.1938822831475493 15 4.2045792744067327 
		30 4.0172592923953516 45 4.0172592923953516 60 4.1938822831475493;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1033";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -26.15777779314551 30 -26.496933820741674 
		60 -26.15777779314551;
createNode animCurveTA -n "animCurveTA1034";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -7.7309160774392849 30 -7.5076916713876516 
		60 -7.7309160774392849;
createNode animCurveTA -n "animCurveTA1035";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -5.4580677241186253 30 5.7126774255951407 
		60 -5.4580677241186253;
createNode animCurveTL -n "animCurveTL382";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.00025694328101411035 15 0.00025694328101411035 
		30 0.00025694328101411035 45 0.00025694328101411035 60 0.00025694328101411035;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL383";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL384";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.12527739251666781 15 -0.12527739251666781 
		30 -0.12527739251666781 45 -0.12527739251666781 60 -0.12527739251666781;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL385";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.032833691772160223 15 0.032833691772160223 
		30 0.032833691772160223 45 0.032833691772160223 60 0.032833691772160223;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL386";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.016062985925156426 15 -0.016062985925156426 
		30 -0.016062985925156426 45 -0.016062985925156426 60 -0.016062985925156426;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL387";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.11728380015772394 15 0.11728380015772394 
		30 0.11728380015772394 45 0.11728380015772394 60 0.11728380015772394;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1036";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -2.2720201456595888 15 -0.86262827860006497 
		30 0.74961563248753227 45 -0.86262827860006497 60 -2.2720201456595888;
	setAttr -s 5 ".kit[1:4]"  1 3 1 3;
	setAttr -s 5 ".kot[1:4]"  1 3 1 3;
	setAttr -s 5 ".kix[1:4]"  0.99653643369674683 1 0.99607926607131958 
		1;
	setAttr -s 5 ".kiy[1:4]"  0.083157815039157867 0 -0.08846554160118103 
		0;
	setAttr -s 5 ".kox[1:4]"  0.99653643369674683 1 0.99607926607131958 
		1;
	setAttr -s 5 ".koy[1:4]"  0.083157800137996674 0 -0.08846554160118103 
		0;
createNode animCurveTA -n "animCurveTA1037";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 6.310555954633986 15 0 30 -5.7281614243314989 
		45 0 60 6.310555954633986;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1038";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -19.847201316347629 15 -13.207859934748164 
		30 -7.4683573379097306 45 -13.944932300487299 60 -19.847201316347629;
	setAttr -s 5 ".kit[1:4]"  1 3 1 3;
	setAttr -s 5 ".kot[1:4]"  1 3 1 3;
	setAttr -s 5 ".kix[1:4]"  0.94719874858856201 1 0.9529234766960144 
		1;
	setAttr -s 5 ".kiy[1:4]"  0.32064709067344666 0 -0.30321094393730164 
		0;
	setAttr -s 5 ".kox[1:4]"  0.94719874858856201 1 0.9529234766960144 
		1;
	setAttr -s 5 ".koy[1:4]"  0.32064703106880188 0 -0.30321097373962402 
		0;
createNode animCurveTL -n "animCurveTL388";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.029083050929249406 15 -0.029083050929249406 
		30 -0.029083050929249406 45 -0.029083050929249406 60 -0.029083050929249406;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL389";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.0084783132527929302 15 -0.063440169961996071 
		30 -0.12722102809756705 45 -0.055302544882778054 60 0.0084783132527929302;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL390";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.0033047562864448685 15 -0.093518881802929971 
		30 -0.0033047562864448685 45 0.075501314074885056 60 -0.0033047562864448685;
	setAttr -s 5 ".kit[0:4]"  2 10 1 10 2;
	setAttr -s 5 ".kot[0:4]"  2 10 1 10 2;
	setAttr -s 5 ".kix[2:4]"  0.96311491727828979 1 0.98780590295791626;
	setAttr -s 5 ".kiy[2:4]"  0.26909038424491882 0 -0.15569020807743073;
	setAttr -s 5 ".kox[2:4]"  0.96311497688293457 1 1;
	setAttr -s 5 ".koy[2:4]"  0.26909032464027405 0 0;
createNode animCurveTA -n "animCurveTA1039";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -16.236770139599834 15 -16.236770139599834 
		30 -16.236770139599834 45 -16.236770139599834 60 -16.236770139599834;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1040";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1041";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL391";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -6.0000000000892673e-006 15 -6.0000000000892673e-006 
		30 -6.0000000000892673e-006 45 -6.0000000000892673e-006 60 -6.0000000000892673e-006;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL392";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 2.1809999999936394e-005 15 2.1809999999936394e-005 
		30 2.1809999999936394e-005 45 2.1809999999936394e-005 60 2.1809999999936394e-005;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL393";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.040093865534497591 15 -0.040093865534497591 
		30 -0.040093865534497591 45 -0.040093865534497591 60 -0.040093865534497591;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1042";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 25.000774638404387 15 25.000774638404387 
		30 25.000774638404387 45 25.000774638404387 60 25.000774638404387;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1043";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1044";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL394";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL395";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL396";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.038258090963777358 15 0.038258090963777358 
		30 0.038258090963777358 45 0.038258090963777358 60 0.038258090963777358;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU392";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 15 1 30 1 45 1 60 1;
	setAttr -s 5 ".kit[1:4]"  9 3 9 3;
	setAttr -s 5 ".kot[1:4]"  5 3 5 3;
createNode animCurveTA -n "animCurveTA1045";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1046";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1047";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL397";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.80799999999999983 15 -0.80799999999999983 
		30 -0.80799999999999983 45 -0.80799999999999983 60 -0.80799999999999983;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL398";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL399";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU393";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 15 1 30 1 45 1 60 1;
	setAttr -s 5 ".kit[1:4]"  9 3 9 3;
	setAttr -s 5 ".kot[1:4]"  5 3 5 3;
createNode animCurveTA -n "animCurveTA1048";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1049";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1050";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL400";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.80789537837891157 15 -0.80789537837891157 
		30 -0.80789537837891157 45 -0.80789537837891157 60 -0.80789537837891157;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL401";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL402";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU394";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU395";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 45 15 45 30 45 45 45 60 45;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU396";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 45 15 45 30 45 45 45 60 45;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU397";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 45 15 45 30 45 45 45 60 45;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1051";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1052";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU398";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU399";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 45 15 45 30 45 45 45 60 45;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU400";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 45 15 45 30 45 45 45 60 45;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU401";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 45 15 45 30 45 45 45 60 45;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1053";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1054";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU402";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU403";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU404";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU405";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU406";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU407";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU408";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU409";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU410";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU411";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU412";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU413";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1055";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1056";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1057";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU414";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU415";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU416";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU417";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU418";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU419";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU420";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU421";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU422";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU423";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU424";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU425";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1058";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1059";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1060";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1061";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -21.142899808146542 15 -7.8899718456666035 
		30 -22.164303623398109 45 -39.166106401742255 60 -21.142899808146527;
	setAttr -s 5 ".kit[0:4]"  2 3 1 3 2;
	setAttr -s 5 ".kot[0:4]"  2 3 1 3 2;
	setAttr -s 5 ".kix[2:4]"  0.72986865043640137 1 0.84642404317855835;
	setAttr -s 5 ".kiy[2:4]"  -0.68358743190765381 0 0.53250956535339355;
	setAttr -s 5 ".kox[2:4]"  0.72986871004104614 1 1;
	setAttr -s 5 ".koy[2:4]"  -0.68358743190765381 0 0;
createNode animCurveTA -n "animCurveTA1062";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 9.7411992512390277 15 0 30 -11.282942617496635 
		45 0 60 9.7411992512390242;
	setAttr -s 5 ".kit[1:4]"  1 3 1 3;
	setAttr -s 5 ".kot[1:4]"  1 3 1 3;
	setAttr -s 5 ".kix[1:4]"  0.78747653961181641 1 0.81533622741699219 
		1;
	setAttr -s 5 ".kiy[1:4]"  -0.6163446307182312 0 0.57898783683776855 
		0;
	setAttr -s 5 ".kox[1:4]"  0.78747659921646118 1 0.81533628702163696 
		1;
	setAttr -s 5 ".koy[1:4]"  -0.61634457111358643 0 0.578987717628479 
		0;
createNode animCurveTA -n "animCurveTA1063";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -11.49841417301748 15 0 30 13.729677110885969 
		45 0 60 -11.49841417301748;
	setAttr -s 5 ".kit[1:4]"  1 3 1 3;
	setAttr -s 5 ".kot[1:4]"  1 3 1 3;
	setAttr -s 5 ".kix[1:4]"  0.76290851831436157 1 0.79852968454360962 
		1;
	setAttr -s 5 ".kiy[1:4]"  0.64650648832321167 0 -0.60195547342300415 
		0;
	setAttr -s 5 ".kox[1:4]"  0.7629084587097168 1 0.79852968454360962 
		1;
	setAttr -s 5 ".koy[1:4]"  0.64650660753250122 0 -0.60195553302764893 
		0;
createNode animCurveTA -n "animCurveTA1064";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -17.428736070727251 15 -17.428736070727251 
		30 -17.428736070727251 45 -17.428736070727251 60 -17.428736070727251;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA1065";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
	setAttr -s 3 ".kit[1:2]"  9 2;
	setAttr -s 3 ".kot[1:2]"  9 2;
createNode animCurveTA -n "animCurveTA1066";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 30 0 45 0 60 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "tank_M_backCloth_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 -7.2170192627883578 60 0;
createNode animCurveTA -n "tank_M_backCloth_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 60 0;
createNode animCurveTA -n "tank_M_backCloth_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 60 0;
createNode animCurveTA -n "tank_M_hang_ctrl_rotateZ2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 9.1478457292549002 60 9.1478457292549002;
createNode animCurveTA -n "tank_M_hang_ctrl_rotateY2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 60 0;
createNode animCurveTA -n "tank_M_hang_ctrl_rotateX2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 60 0;
createNode animCurveTA -n "tank_R_hang_ctrl_rotateZ2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 9.1478457292549002 60 9.1478457292549002;
createNode animCurveTA -n "tank_R_hang_ctrl_rotateY2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 60 0;
createNode animCurveTA -n "tank_R_hang_ctrl_rotateX2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 60 0;
createNode animCurveTA -n "tank_L_hang_ctrl_rotateZ2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 9.1478457292549002 60 9.1478457292549002;
createNode animCurveTA -n "tank_L_hang_ctrl_rotateY2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 60 0;
createNode animCurveTA -n "tank_L_hang_ctrl_rotateX2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 60 0;
createNode animCurveTA -n "tank_R_flag_3_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "tank_R_flag_3_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "tank_R_flag_3_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "tank_R_flag_2_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.339;
createNode animCurveTA -n "tank_R_flag_2_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.339;
createNode animCurveTA -n "tank_R_flag_2_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.339;
createNode animCurveTA -n "tank_R_flag_1_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "tank_R_flag_1_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "tank_R_flag_1_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "tank_L_flag_1_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "tank_L_flag_1_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "tank_L_flag_1_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "tank_L_flag_2_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "tank_L_flag_2_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "tank_L_flag_2_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "tank_L_flag_3_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "tank_L_flag_3_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "tank_L_flag_3_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "tank_M_backFeature_ctrl_rotateZ2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -5.5312497278658954;
createNode animCurveTA -n "tank_M_backFeature_ctrl_rotateY2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "tank_M_backFeature_ctrl_rotateX2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "tank_M_frontCloth_ctrl_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 8.1066489615016604 30 -7.8434679813289607 
		60 8.1066489615016604;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "tank_M_frontCloth_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 60 0;
createNode animCurveTA -n "tank_M_frontCloth_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 60 0;
createNode lightLinker -n "lightLinker1";
	setAttr -s 4 ".lnk";
	setAttr -s 4 ".slnk";
select -ne :time1;
	setAttr -av -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 49;
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
connectAttr "stunSource2.cl" "clipLibrary2.sc[0]";
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
// End of stun.ma
