//Maya ASCII 2008 scene
//Name: attack4B.ma
//Last modified: Mon, Nov 02, 2009 12:58:10 PM
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
createNode animClip -n "attackSource2";
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
createNode animCurveTU -n "animCurveTU426";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTU -n "animCurveTU427";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTA -n "animCurveTA1109";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 39.53428110495291 2 80.774804853371606 
		4 34.123560075754995 6 34.123560075754995 18 34.123560075754995 23 11.294121682984013 
		28 38.049776645939609 36 38.792028999875981 44 39.53428110495291;
createNode animCurveTA -n "animCurveTA1110";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 32.600909957006799 2 -4.2981852407069994 
		4 32.249867368590103 6 32.249867368590103 18 32.249867368590103 23 42.673640276226379 
		28 39.189230557356908 36 35.759302338729377 44 32.600909957006799;
createNode animCurveTA -n "animCurveTA1111";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 16.651520328974982 2 34.388706509302004 
		4 34.67147396140102 6 34.67147396140102 18 34.67147396140102 23 17.038599595304429 
		28 26.370048176718804 36 22.68873483774502 44 16.651520328974982;
createNode animCurveTA -n "animCurveTA1112";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -87.582586884797436 2 -73.574751845939389 
		4 -54.757221260416735 6 -54.757221260416735 18 -54.757221260416735 23 -68.353395334932884 
		28 -87.582586884797436 36 -82.575024819405428 44 -87.582586884797436;
createNode animCurveTA -n "animCurveTA1113";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTA -n "animCurveTA1114";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTA -n "animCurveTA1115";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTA -n "animCurveTA1116";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -0.90666238496249552 2 18.910003750547556 
		4 18.314607953690501 6 24.589240674870478 18 24.589240674870478 23 10.003323975188403 
		28 -0.90666238496249552 36 -0.90666238496249552 44 -0.90666238496249552;
createNode animCurveTA -n "animCurveTA1117";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -0.14300750254877909 2 -0.10714165082092433 
		4 -0.2590250398983317 6 -0.2587293542900625 18 -0.2587293542900625 23 -2.4668241939992788 
		28 -0.14300750254877909 36 -0.14300750254877909 44 -0.14300750254877909;
createNode animCurveTA -n "animCurveTA1118";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -0.69869282260852494 2 -7.5169108985234141 
		4 4.8484545758535109 6 9.7220317875425852 18 -1.0208126725292799 23 -0.85975279076854327 
		28 -0.69869282260852494 36 -0.69869282260852494 44 -0.69869282260852494;
createNode animCurveTA -n "animCurveTA1119";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 13.566397626420638 2 -17.954589818302384 
		4 -24.761367263233929 6 -26.306252210390419 18 -22.549417251594907 23 -2.2260228924578933 
		28 13.566397626420638 36 13.566397626420638 44 13.566397626420638;
createNode animCurveTA -n "animCurveTA1120";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -14.474463091487671 2 -59.408956337569137 
		4 7.7879447898077032 6 34.526614320908692 18 29.141363953952883 23 -4.9481428299670593 
		28 -5.1508931667839279 36 -8.647232503242936 44 -14.474463091487671;
createNode animCurveTA -n "animCurveTA1121";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 28.826393195295356 2 40.569317171229883 
		4 4.2331119929249326 6 -9.8206149555571169 18 3.6180678266567767 23 50.439705948668482 
		28 37.907216931562211 36 32.443496912419256 44 28.826393195295356;
createNode animCurveTA -n "animCurveTA1122";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 4.3502300737951041 2 15.217341022544133 
		4 19.952541791281192 6 21.384055197363644 18 31.145561069511871 23 15.057729053572634 
		28 28.501604163516678 36 18.425075630351987 44 4.3502300737951041;
createNode animCurveTA -n "animCurveTA1123";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -59.684677024606373 2 -74.180897563233813 
		4 -45.287024722774326 6 -64.538331698130932 18 -64.538331698130932 23 -52.057387760510188 
		28 -59.684677024606373 36 -53.666282418254617 44 -59.684677024606373;
createNode animCurveTA -n "animCurveTA1124";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTA -n "animCurveTA1125";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTA -n "animCurveTA1126";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTA -n "animCurveTA1127";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -0.19158875421948376 2 -22.95212206148997 
		4 -20.4807877984619 6 -18.816504048570042 18 -18.816504048570042 23 -9.5040488991906962 
		28 -0.19158875421948376 36 -0.19158875421948376 44 -0.19158875421948376;
createNode animCurveTA -n "animCurveTA1128";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -7.898767459478834 2 -17.731120032884093 
		4 -12.946849417198626 6 -10.829143728212973 18 -10.829143728212973 23 -9.3639559868400095 
		28 -7.898767459478834 36 -7.898767459478834 44 -7.898767459478834;
createNode animCurveTA -n "animCurveTA1129";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 2.3461370896484395 2 11.643845010814465 
		4 6.6911463829628239 6 4.5273004023666337 18 4.5273004023666337 23 3.4367190385243487 
		28 2.3461370896484395 36 2.3461370896484395 44 2.3461370896484395;
createNode animCurveTA -n "animCurveTA1130";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 1.4245112294344 2 1.4245112294344 4 1.4245112294344 
		6 1.4245112294344 18 1.4245112294344 23 1.4245112294344 28 1.4245112294344 36 1.4245112294344 
		44 1.4245112294344;
createNode animCurveTA -n "animCurveTA1131";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 1.8864606807611757 2 1.8864606807611757 
		4 1.8864606807611757 6 1.8864606807611757 18 1.8864606807611757 23 1.8864606807611757 
		28 1.8864606807611757 36 1.8864606807611757 44 1.8864606807611757;
createNode animCurveTA -n "animCurveTA1132";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -5.9921097590926697 2 -5.9921097590926697 
		4 -5.9921097590926697 6 -5.9921097590926697 18 -5.9921097590926697 23 -5.9921097590926697 
		28 -5.9921097590926697 36 -5.9921097590926697 44 -5.9921097590926697;
createNode animCurveTL -n "animCurveTL415";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 -0.0029616969366186752 4 0.54887067931658839 
		6 0.36927962094784095 18 0.36927962094784095 23 0.18463985999817983 28 0 36 0 44 
		0;
createNode animCurveTL -n "animCurveTL416";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 -0.25305456122736808 4 -0.18849312561455853 
		6 -0.48809657419268926 18 -0.48809657419268926 23 -0.2440483525552001 28 0 36 0 44 
		0;
createNode animCurveTL -n "animCurveTL417";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -0.12272155611893799 2 -0.056539668510212984 
		4 0.096625222905038402 6 0.16264559139920792 18 0.16264559139920792 23 0.01996205591085401 
		28 -0.12272155611893799 36 -0.12272155611893799 44 -0.12272155611893799;
createNode animCurveTL -n "animCurveTL418";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0.033 2 -0.087531905649224487 4 -0.087531905649224487 
		6 -0.087531905649224487 18 -0.087531905649224487 23 -0.10665005922488149 28 0.033 
		36 0.033 44 0.033;
createNode animCurveTL -n "animCurveTL419";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -0.016 2 -0.0148742933272005 4 -0.0148742933272005 
		6 -0.0148742933272005 18 -0.0148742933272005 23 -0.020778951295263241 28 -0.016 36 
		-0.016 44 -0.016;
createNode animCurveTL -n "animCurveTL420";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0.10379921435641129 2 0.20435711803041706 
		4 0.20435711803041706 6 0.20435711803041706 18 0.20435711803041706 23 0.21171143269531423 
		28 0.10379921435641129 36 0.10379921435641129 44 0.10379921435641129;
createNode animCurveTA -n "animCurveTA1133";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -18.178217858042064 2 -5.297829953324106 
		4 22.352195054076365 6 32.342626648964227 18 32.045795941101375 23 6.536773092576774 
		28 0.85454836923998712 36 -16.972740355907952 44 -18.178217858042064;
createNode animCurveTA -n "animCurveTA1134";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -4.6186256351197352 2 9.1264443785689071 
		4 4.7906909477069091 6 2.7155653208848127 18 1.7145981984530374 23 6.7223069942531604 
		28 3.5715143237584974 36 -4.4581503019842836 44 -4.6186256351197352;
createNode animCurveTA -n "animCurveTA1135";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -7.7006231053605507 2 25.650980865777075 
		4 -5.907320826708407 6 -18.859965675814795 18 -15.815944902846887 23 7.3835825425924773 
		28 15.966075788735465 36 2.0642508466212042 44 -7.7006231053605507;
createNode animCurveTL -n "animCurveTL421";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -0.062545592999319929 2 -0.077511269265836485 
		4 -0.069565584553682655 6 -0.068094160406395363 18 -0.052801403469827347 23 -0.091252471907466007 
		28 -0.12079852879137599 36 -0.062545592999304844 44 -0.062545592999319929;
createNode animCurveTL -n "animCurveTL422";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -0.032867286470989195 2 -0.058238840965088273 
		4 -0.23260942711784935 6 -0.30623260328368734 18 -0.19530053679663847 23 -0.10202751115400965 
		28 -0.030862161859033139 36 -0.0055468367299970501 44 -0.032867286470989195;
createNode animCurveTL -n "animCurveTL423";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -0.0098384205421270955 2 0.23421860181620441 
		4 0.20576919793374182 6 0.20050078603910007 18 0.19753599347028036 23 0.22446105712166112 
		28 0.040214159527575566 36 -0.022546095554744953 44 -0.0098384205421270955;
createNode animCurveTA -n "animCurveTA1136";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -25.590668618635455 2 -20.319346347536609 
		4 -8.0074566274163725 6 -2.9426289173755391 18 -2.9426289173755391 23 -18.966019570177181 
		28 -25.590668618635455 36 -25.590668618635455 44 -25.590668618635455;
createNode animCurveTA -n "animCurveTA1137";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 11.171496892680478 4 -4.2212744942761713 
		6 -7.8032359932179363 18 -7.8032359932179363 23 0.16222531353217221 28 0 36 0 44 
		0;
createNode animCurveTA -n "animCurveTA1138";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 30.360922127485495 4 -53.865163434708514 
		6 -62.019041182167896 18 -62.019041182167896 23 16.774967070923861 28 0 36 0 44 0;
	setAttr -s 9 ".kit[2:8]"  1 10 10 10 10 10 10;
	setAttr -s 9 ".kot[2:8]"  1 10 10 10 10 10 10;
	setAttr -s 9 ".kix[2:8]"  0.090939871966838837 0.066666662693023682 
		0.40000003576278687 0.16666662693023682 0.16666668653488159 0.2666667103767395 0.26666665077209473;
	setAttr -s 9 ".kiy[2:8]"  -0.47716978192329407 0 0 0.54121816158294678 
		0 0 0;
	setAttr -s 9 ".kox[2:8]"  0.09093986451625824 0.40000003576278687 
		0.16666662693023682 0.16666668653488159 0.2666667103767395 0.26666665077209473 0.26666665077209473;
	setAttr -s 9 ".koy[2:8]"  -0.47716978192329407 0 0 0.5412183403968811 
		0 0 0;
createNode animCurveTL -n "animCurveTL424";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0.21024126291697104 4 0.47769691674981096 
		6 0.25893633172253294 18 0.3126296259909852 23 0.1460384093852897 28 0 36 0 44 0;
	setAttr -s 9 ".kit[3:8]"  3 3 10 10 10 10;
	setAttr -s 9 ".kot[3:8]"  3 3 10 10 10 10;
createNode animCurveTL -n "animCurveTL425";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0.15953969092363035 2 -0.10864235631358879 
		4 -0.73529447235628342 6 -0.9924160706130758 18 -0.86355140216627302 23 -0.13594064821383842 
		28 0.15953969092363035 36 0.15953969092363035 44 0.15953969092363035;
	setAttr -s 9 ".kit[3:8]"  3 1 10 10 10 10;
	setAttr -s 9 ".kot[3:8]"  3 1 10 10 10 10;
	setAttr -s 9 ".kix[4:8]"  0.39753603935241699 0.16666662693023682 
		0.16666668653488159 0.2666667103767395 0.26666665077209473;
	setAttr -s 9 ".kiy[4:8]"  0.28303351998329163 0.51154547929763794 
		0 0 0;
	setAttr -s 9 ".kox[4:8]"  0.13251197338104248 0.16666668653488159 
		0.2666667103767395 0.26666665077209473 0.26666665077209473;
	setAttr -s 9 ".koy[4:8]"  0.094344466924667358 0.51154565811157227 
		0 0 0;
createNode animCurveTL -n "animCurveTL426";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -0.04 2 0.066793492496307227 4 0.21233058179560527 
		6 0.27567857257418416 18 0.2595320866407434 23 0.17503218002468485 28 -0.04 36 -0.04 
		44 -0.04;
createNode animCurveTA -n "animCurveTA1139";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 11.880229891661756 2 11.880229891661756 
		4 11.880229891661756 6 11.880229891661756 18 11.880229891661756 23 11.880229891661756 
		28 11.880229891661756 36 11.880229891661756 44 11.880229891661756;
createNode animCurveTA -n "animCurveTA1140";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTA -n "animCurveTA1141";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTL -n "animCurveTL427";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTL -n "animCurveTL428";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -0.20007920657257083 2 -0.20007920657257083 
		4 -0.20007920657257083 6 -0.20007920657257083 18 -0.20007920657257083 23 -0.20007920657257083 
		28 -0.20007920657257083 36 -0.20007920657257083 44 -0.20007920657257083;
createNode animCurveTL -n "animCurveTL429";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0.098575236578624326 2 0.098575236578624326 
		4 0.098575236578624326 6 0.098575236578624326 18 0.098575236578624326 23 0.098575236578624326 
		28 0.098575236578624326 36 0.098575236578624326 44 0.098575236578624326;
createNode animCurveTU -n "animCurveTU428";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 4 1 6 1 18 1 23 1 28 1 36 1 44 
		1;
	setAttr -s 9 ".kot[0:8]"  5 5 5 5 5 5 5 5 
		5;
createNode animCurveTA -n "animCurveTA1142";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTA -n "animCurveTA1143";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTA -n "animCurveTA1144";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTL -n "animCurveTL430";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -0.81944359671150613 2 -0.81944359671150613 
		4 -0.81944359671150613 6 -0.81944359671150613 18 -0.81944359671150613 23 -0.81944359671150613 
		28 -0.81944359671150613 36 -0.81944359671150613 44 -0.81944359671150613;
createNode animCurveTL -n "animCurveTL431";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0.029470472912715796 2 0.029470472912715796 
		4 0.029470472912715796 6 0.029470472912715796 18 0.029470472912715796 23 0.029470472912715796 
		28 0.029470472912715796 36 0.029470472912715796 44 0.029470472912715796;
createNode animCurveTL -n "animCurveTL432";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -0.070295643204272437 2 -0.070295643204272437 
		4 -0.070295643204272437 6 -0.070295643204272437 18 -0.070295643204272437 23 -0.070295643204272437 
		28 -0.070295643204272437 36 -0.070295643204272437 44 -0.070295643204272437;
createNode animCurveTU -n "animCurveTU429";
	setAttr ".tan" 9;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 4 1 6 1 18 1 23 1 28 1 36 1 44 
		1;
	setAttr -s 9 ".kot[0:8]"  5 5 5 5 5 5 5 5 
		5;
createNode animCurveTA -n "animCurveTA1145";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -4.8160457500419067 2 -4.8160457500419067 
		4 -4.8160457500419067 6 -4.8160457500419067 18 -4.8160457500419067 23 -4.8160457500419067 
		28 -4.8160457500419067 36 -4.8160457500419067 44 -4.8160457500419067;
createNode animCurveTA -n "animCurveTA1146";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTA -n "animCurveTA1147";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTL -n "animCurveTL433";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -0.80451419482641451 2 -0.80451419482641451 
		4 -0.80451419482641451 6 -0.80451419482641451 18 -0.80451419482641451 23 -0.80451419482641451 
		28 -0.80451419482641451 36 -0.80451419482641451 44 -0.80451419482641451;
createNode animCurveTL -n "animCurveTL434";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -2.4945889741368431e-013 2 0 4 0 6 0 
		18 0 23 0 28 0 36 0 44 0;
createNode animCurveTL -n "animCurveTL435";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -0.0085562672260772743 2 -0.0085562672260772743 
		4 -0.0085562672260772743 6 -0.0085562672260772743 18 -0.0085562672260772743 23 -0.0085562672260772743 
		28 -0.0085562672260772743 36 -0.0085562672260772743 44 -0.0085562672260772743;
createNode animCurveTU -n "animCurveTU430";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTU -n "animCurveTU431";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 45 2 45 4 45 6 45 18 45 23 45 28 45 36 
		45 44 45;
createNode animCurveTU -n "animCurveTU432";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 45 2 45 4 45 6 45 18 45 23 45 28 45 36 
		45 44 45;
createNode animCurveTU -n "animCurveTU433";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 45 2 45 4 45 6 45 18 45 23 45 28 45 36 
		45 44 45;
createNode animCurveTA -n "animCurveTA1148";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTA -n "animCurveTA1149";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTU -n "animCurveTU434";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTU -n "animCurveTU435";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 45 2 45 4 45 6 45 18 45 23 45 28 45 36 
		45 44 45;
createNode animCurveTU -n "animCurveTU436";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 45 2 45 4 45 6 45 18 45 23 45 28 45 36 
		45 44 45;
createNode animCurveTU -n "animCurveTU437";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 45 2 45 4 45 6 45 18 45 23 45 28 45 36 
		45 44 45;
createNode animCurveTA -n "animCurveTA1150";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTA -n "animCurveTA1151";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTU -n "animCurveTU438";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTU -n "animCurveTU439";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTU -n "animCurveTU440";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTU -n "animCurveTU441";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTU -n "animCurveTU442";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTU -n "animCurveTU443";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTU -n "animCurveTU444";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTU -n "animCurveTU445";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTU -n "animCurveTU446";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTU -n "animCurveTU447";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTU -n "animCurveTU448";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTU -n "animCurveTU449";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTA -n "animCurveTA1152";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTA -n "animCurveTA1153";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTA -n "animCurveTA1154";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -2.5999764661798822e-011 2 0 4 0 6 0 
		18 0 23 0 28 0 36 0 44 0;
createNode animCurveTU -n "animCurveTU450";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTU -n "animCurveTU451";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTU -n "animCurveTU452";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTU -n "animCurveTU453";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTU -n "animCurveTU454";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTU -n "animCurveTU455";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTU -n "animCurveTU456";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTU -n "animCurveTU457";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTU -n "animCurveTU458";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTU -n "animCurveTU459";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTU -n "animCurveTU460";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTU -n "animCurveTU461";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTA -n "animCurveTA1155";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTA -n "animCurveTA1156";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTA -n "animCurveTA1157";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -2.5997909391022333e-011 2 0 4 0 6 0 
		18 0 23 0 28 0 36 0 44 0;
createNode animCurveTA -n "animCurveTA1158";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -5.8382275551355809 2 -36.385220400629564 
		4 -25.42531411520531 6 -20.315228566867351 18 -26.966841179192865 23 -24.795013080501899 
		28 -41.057543823801254 36 -23.64530502465886 44 -5.8382275551355809;
createNode animCurveTA -n "animCurveTA1159";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -2.3136539176186792 2 -20.135555034284302 
		4 -9.7941604158483742 6 -5.3273354914337085 18 -9.1124637212373454 23 -6.245205261359736 
		28 -7.6150910725009275 36 -2.4694801400798925 44 -2.3136539176186792;
createNode animCurveTA -n "animCurveTA1160";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -13.887028133305018 2 -20.789612204052201 
		4 -17.00284510681341 6 -15.355052821141792 18 -15.10950997960903 23 -10.538944940073703 
		28 -13.27472044864899 36 -6.5529547941168778 44 -13.887028133305018;
createNode animCurveTA -n "animCurveTA1161";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 13.873263178484903 2 13.873263178484903 
		4 13.873263178484903 6 13.873263178484903 18 13.873263178484903 23 13.873263178484903 
		28 13.873263178484903 36 13.873263178484903 44 13.873263178484903;
createNode animCurveTA -n "animCurveTA1162";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTA -n "animCurveTA1163";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 18 0 23 0 28 0 36 0 44 
		0;
createNode animCurveTA -n "tank_M_backCloth_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 -12.86539240201413 6 43.31207420015938 
		11 -41.282648347432307 18 26.146485390261006 25 -16.127233868148295 35 12.047017705568189 
		44 0;
createNode animCurveTA -n "tank_M_backCloth_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 9.4741161346176082 6 6.2187670551751379 
		11 -2.1033270111937665 18 6.7854041571269894 25 11.558757024705145 35 1.7068393558705099 
		44 0;
createNode animCurveTA -n "tank_M_backCloth_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 4.6203825171879913 6 -0.846540284591345 
		11 -17.785766459045078 18 -8.5987462093319298 25 -0.86030163697492645 35 4.4642662907803015 
		44 0;
createNode animCurveTA -n "tank_M_hang_ctrl_rotateZ2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -7.6359447996384162 2 53.895136569311674 
		5 101.70829035534879 10 -14.838889822277089 14 -19.035238009193989 18 36.272528007442439 
		23 50.171079012682966 27 22.332459854990219 34 26.62744143868461 44 -7.6359447996384162;
createNode animCurveTA -n "tank_M_hang_ctrl_rotateY2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -35.260196151694586 2 -3.7058743380378827 
		5 3.7805246183719499 10 -2.6388625306785602 14 -1.5449666432788798 18 6.3342700777146588 
		23 -1.0806691232573216 27 1.715337400006302 34 -33.470442109730712 44 -35.260196151694586;
createNode animCurveTA -n "tank_M_hang_ctrl_rotateX2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 68.744635926587719 2 3.9205175767605307 
		5 10.365249968420185 10 -3.4378780364795958 14 -8.8224092666481653 18 -16.309903673925604 
		23 -8.1938350176952479 27 -3.2445869328796682 34 25.339098550049417 44 68.744635926587719;
createNode animCurveTA -n "tank_R_hang_ctrl_rotateZ2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -7.6359447996384162 2 53.895136569311674 
		5 101.70829035534879 10 -14.838889822277089 14 -19.035238009193989 18 36.272528007442439 
		23 50.171079012682966 27 22.332459854990219 34 26.62744143868461 44 -7.6359447996384162;
createNode animCurveTA -n "tank_R_hang_ctrl_rotateY2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -35.260196151694586 2 -3.7058743380378827 
		5 3.7805246183719499 10 -2.6388625306785602 14 -1.5449666432788798 18 6.3342700777146588 
		23 -1.0806691232573216 27 1.715337400006302 34 -33.470442109730712 44 -35.260196151694586;
createNode animCurveTA -n "tank_R_hang_ctrl_rotateX2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 68.744635926587719 2 3.9205175767605307 
		5 10.365249968420185 10 -3.4378780364795958 14 -8.8224092666481653 18 -16.309903673925604 
		23 -8.1938350176952479 27 -3.2445869328796682 34 25.339098550049417 44 68.744635926587719;
createNode animCurveTA -n "tank_L_hang_ctrl_rotateZ2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -7.6359447996384162 2 53.895136569311674 
		5 101.70829035534879 10 -14.838889822277089 14 -19.035238009193989 18 36.272528007442439 
		23 50.171079012682966 27 22.332459854990219 34 26.62744143868461 44 -7.6359447996384162;
createNode animCurveTA -n "tank_L_hang_ctrl_rotateY2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -35.260196151694586 2 -3.7058743380378827 
		5 3.7805246183719499 10 -2.6388625306785602 14 -1.5449666432788798 18 6.3342700777146588 
		23 -1.0806691232573216 27 1.715337400006302 34 -33.470442109730712 44 -35.260196151694586;
createNode animCurveTA -n "tank_L_hang_ctrl_rotateX2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 68.744635926587719 2 3.9205175767605307 
		5 10.365249968420185 10 -3.4378780364795958 14 -8.8224092666481653 18 -16.309903673925604 
		23 -8.1938350176952479 27 -3.2445869328796682 34 25.339098550049417 44 68.744635926587719;
createNode animCurveTA -n "tank_R_flag_3_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 18.08;
createNode animCurveTA -n "tank_R_flag_3_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.0336;
createNode animCurveTA -n "tank_R_flag_3_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "tank_R_flag_2_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 18.373158409800983;
createNode animCurveTA -n "tank_R_flag_2_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "tank_R_flag_2_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "tank_R_flag_1_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 18.373158409800983;
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
	setAttr ".ktv[0]"  0 18.373158409800983;
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
	setAttr ".ktv[0]"  0 18.373158409800983;
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
	setAttr ".ktv[0]"  0 18.373158409800983;
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
	setAttr -s 7 ".ktv[0:6]"  0 -5.4432506707315573 2 3.6897631308421475 
		5 44.598994937874878 10 -10.218869568661276 18 15.970714369170008 24 -8.9795917530475027 
		44 -5.4432506707315573;
createNode animCurveTA -n "tank_M_backFeature_ctrl_rotateY2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 1.5078315520922529 5 -1.4047188279186857 
		10 8.0486348559972694 18 7.8671680456113373 24 12.886938767377428 44 0;
createNode animCurveTA -n "tank_M_backFeature_ctrl_rotateX2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.4808130565433952 2 2.2698606990936825 
		5 -2.0288587720451345 10 13.585858520317505 18 8.4420100647578291 24 11.043165843961182 
		44 1.4808130565433952;
createNode animCurveTA -n "tank_M_frontCloth_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -13.113682797820777 2 23.86763945606101 
		7 -53.809153479815592 14 1.4365975131167956 23 -32.561185289607309 33 19.942926304642533 
		44 -13.113682797820777;
createNode animCurveTA -n "tank_M_frontCloth_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -4.0919497789234391 2 3.330884650656766 
		7 -22.791821436276003 14 15.530762459319975 23 6.4721145820893371 33 -14.432743060165814 
		44 -4.0919497789234391;
createNode animCurveTA -n "tank_M_frontCloth_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 31.178362171912408 2 27.676016809994167 
		7 -35.152078181749197 14 6.2632882152304532 23 -5.1804484933220172 33 15.931492334241799 
		44 31.178362171912408;
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
connectAttr "attackSource2.cl" "clipLibrary2.sc[0]";
connectAttr "animCurveTU426.a" "clipLibrary2.cel[0].cev[0].cevr";
connectAttr "animCurveTU427.a" "clipLibrary2.cel[0].cev[1].cevr";
connectAttr "animCurveTA1109.a" "clipLibrary2.cel[0].cev[2].cevr";
connectAttr "animCurveTA1110.a" "clipLibrary2.cel[0].cev[3].cevr";
connectAttr "animCurveTA1111.a" "clipLibrary2.cel[0].cev[4].cevr";
connectAttr "animCurveTA1112.a" "clipLibrary2.cel[0].cev[5].cevr";
connectAttr "animCurveTA1113.a" "clipLibrary2.cel[0].cev[6].cevr";
connectAttr "animCurveTA1114.a" "clipLibrary2.cel[0].cev[7].cevr";
connectAttr "animCurveTA1115.a" "clipLibrary2.cel[0].cev[8].cevr";
connectAttr "animCurveTA1116.a" "clipLibrary2.cel[0].cev[9].cevr";
connectAttr "animCurveTA1117.a" "clipLibrary2.cel[0].cev[10].cevr";
connectAttr "animCurveTA1118.a" "clipLibrary2.cel[0].cev[11].cevr";
connectAttr "animCurveTA1119.a" "clipLibrary2.cel[0].cev[12].cevr";
connectAttr "animCurveTA1120.a" "clipLibrary2.cel[0].cev[13].cevr";
connectAttr "animCurveTA1121.a" "clipLibrary2.cel[0].cev[14].cevr";
connectAttr "animCurveTA1122.a" "clipLibrary2.cel[0].cev[15].cevr";
connectAttr "animCurveTA1123.a" "clipLibrary2.cel[0].cev[16].cevr";
connectAttr "animCurveTA1124.a" "clipLibrary2.cel[0].cev[17].cevr";
connectAttr "animCurveTA1125.a" "clipLibrary2.cel[0].cev[18].cevr";
connectAttr "animCurveTA1126.a" "clipLibrary2.cel[0].cev[19].cevr";
connectAttr "animCurveTA1127.a" "clipLibrary2.cel[0].cev[20].cevr";
connectAttr "animCurveTA1128.a" "clipLibrary2.cel[0].cev[21].cevr";
connectAttr "animCurveTA1129.a" "clipLibrary2.cel[0].cev[22].cevr";
connectAttr "animCurveTA1130.a" "clipLibrary2.cel[0].cev[23].cevr";
connectAttr "animCurveTA1131.a" "clipLibrary2.cel[0].cev[24].cevr";
connectAttr "animCurveTA1132.a" "clipLibrary2.cel[0].cev[25].cevr";
connectAttr "animCurveTL415.a" "clipLibrary2.cel[0].cev[26].cevr";
connectAttr "animCurveTL416.a" "clipLibrary2.cel[0].cev[27].cevr";
connectAttr "animCurveTL417.a" "clipLibrary2.cel[0].cev[28].cevr";
connectAttr "animCurveTL418.a" "clipLibrary2.cel[0].cev[29].cevr";
connectAttr "animCurveTL419.a" "clipLibrary2.cel[0].cev[30].cevr";
connectAttr "animCurveTL420.a" "clipLibrary2.cel[0].cev[31].cevr";
connectAttr "animCurveTA1133.a" "clipLibrary2.cel[0].cev[32].cevr";
connectAttr "animCurveTA1134.a" "clipLibrary2.cel[0].cev[33].cevr";
connectAttr "animCurveTA1135.a" "clipLibrary2.cel[0].cev[34].cevr";
connectAttr "animCurveTL421.a" "clipLibrary2.cel[0].cev[35].cevr";
connectAttr "animCurveTL422.a" "clipLibrary2.cel[0].cev[36].cevr";
connectAttr "animCurveTL423.a" "clipLibrary2.cel[0].cev[37].cevr";
connectAttr "animCurveTA1136.a" "clipLibrary2.cel[0].cev[38].cevr";
connectAttr "animCurveTA1137.a" "clipLibrary2.cel[0].cev[39].cevr";
connectAttr "animCurveTA1138.a" "clipLibrary2.cel[0].cev[40].cevr";
connectAttr "animCurveTL424.a" "clipLibrary2.cel[0].cev[41].cevr";
connectAttr "animCurveTL425.a" "clipLibrary2.cel[0].cev[42].cevr";
connectAttr "animCurveTL426.a" "clipLibrary2.cel[0].cev[43].cevr";
connectAttr "animCurveTA1139.a" "clipLibrary2.cel[0].cev[44].cevr";
connectAttr "animCurveTA1140.a" "clipLibrary2.cel[0].cev[45].cevr";
connectAttr "animCurveTA1141.a" "clipLibrary2.cel[0].cev[46].cevr";
connectAttr "animCurveTL427.a" "clipLibrary2.cel[0].cev[47].cevr";
connectAttr "animCurveTL428.a" "clipLibrary2.cel[0].cev[48].cevr";
connectAttr "animCurveTL429.a" "clipLibrary2.cel[0].cev[49].cevr";
connectAttr "animCurveTU428.a" "clipLibrary2.cel[0].cev[50].cevr";
connectAttr "animCurveTA1142.a" "clipLibrary2.cel[0].cev[51].cevr";
connectAttr "animCurveTA1143.a" "clipLibrary2.cel[0].cev[52].cevr";
connectAttr "animCurveTA1144.a" "clipLibrary2.cel[0].cev[53].cevr";
connectAttr "animCurveTL430.a" "clipLibrary2.cel[0].cev[54].cevr";
connectAttr "animCurveTL431.a" "clipLibrary2.cel[0].cev[55].cevr";
connectAttr "animCurveTL432.a" "clipLibrary2.cel[0].cev[56].cevr";
connectAttr "animCurveTU429.a" "clipLibrary2.cel[0].cev[57].cevr";
connectAttr "animCurveTA1145.a" "clipLibrary2.cel[0].cev[58].cevr";
connectAttr "animCurveTA1146.a" "clipLibrary2.cel[0].cev[59].cevr";
connectAttr "animCurveTA1147.a" "clipLibrary2.cel[0].cev[60].cevr";
connectAttr "animCurveTL433.a" "clipLibrary2.cel[0].cev[61].cevr";
connectAttr "animCurveTL434.a" "clipLibrary2.cel[0].cev[62].cevr";
connectAttr "animCurveTL435.a" "clipLibrary2.cel[0].cev[63].cevr";
connectAttr "animCurveTU430.a" "clipLibrary2.cel[0].cev[64].cevr";
connectAttr "animCurveTU431.a" "clipLibrary2.cel[0].cev[65].cevr";
connectAttr "animCurveTU432.a" "clipLibrary2.cel[0].cev[66].cevr";
connectAttr "animCurveTU433.a" "clipLibrary2.cel[0].cev[67].cevr";
connectAttr "animCurveTA1148.a" "clipLibrary2.cel[0].cev[68].cevr";
connectAttr "animCurveTA1149.a" "clipLibrary2.cel[0].cev[69].cevr";
connectAttr "animCurveTU434.a" "clipLibrary2.cel[0].cev[70].cevr";
connectAttr "animCurveTU435.a" "clipLibrary2.cel[0].cev[71].cevr";
connectAttr "animCurveTU436.a" "clipLibrary2.cel[0].cev[72].cevr";
connectAttr "animCurveTU437.a" "clipLibrary2.cel[0].cev[73].cevr";
connectAttr "animCurveTA1150.a" "clipLibrary2.cel[0].cev[74].cevr";
connectAttr "animCurveTA1151.a" "clipLibrary2.cel[0].cev[75].cevr";
connectAttr "animCurveTU438.a" "clipLibrary2.cel[0].cev[76].cevr";
connectAttr "animCurveTU439.a" "clipLibrary2.cel[0].cev[77].cevr";
connectAttr "animCurveTU440.a" "clipLibrary2.cel[0].cev[78].cevr";
connectAttr "animCurveTU441.a" "clipLibrary2.cel[0].cev[79].cevr";
connectAttr "animCurveTU442.a" "clipLibrary2.cel[0].cev[80].cevr";
connectAttr "animCurveTU443.a" "clipLibrary2.cel[0].cev[81].cevr";
connectAttr "animCurveTU444.a" "clipLibrary2.cel[0].cev[82].cevr";
connectAttr "animCurveTU445.a" "clipLibrary2.cel[0].cev[83].cevr";
connectAttr "animCurveTU446.a" "clipLibrary2.cel[0].cev[84].cevr";
connectAttr "animCurveTU447.a" "clipLibrary2.cel[0].cev[85].cevr";
connectAttr "animCurveTU448.a" "clipLibrary2.cel[0].cev[86].cevr";
connectAttr "animCurveTU449.a" "clipLibrary2.cel[0].cev[87].cevr";
connectAttr "animCurveTA1152.a" "clipLibrary2.cel[0].cev[88].cevr";
connectAttr "animCurveTA1153.a" "clipLibrary2.cel[0].cev[89].cevr";
connectAttr "animCurveTA1154.a" "clipLibrary2.cel[0].cev[90].cevr";
connectAttr "animCurveTU450.a" "clipLibrary2.cel[0].cev[91].cevr";
connectAttr "animCurveTU451.a" "clipLibrary2.cel[0].cev[92].cevr";
connectAttr "animCurveTU452.a" "clipLibrary2.cel[0].cev[93].cevr";
connectAttr "animCurveTU453.a" "clipLibrary2.cel[0].cev[94].cevr";
connectAttr "animCurveTU454.a" "clipLibrary2.cel[0].cev[95].cevr";
connectAttr "animCurveTU455.a" "clipLibrary2.cel[0].cev[96].cevr";
connectAttr "animCurveTU456.a" "clipLibrary2.cel[0].cev[97].cevr";
connectAttr "animCurveTU457.a" "clipLibrary2.cel[0].cev[98].cevr";
connectAttr "animCurveTU458.a" "clipLibrary2.cel[0].cev[99].cevr";
connectAttr "animCurveTU459.a" "clipLibrary2.cel[0].cev[100].cevr";
connectAttr "animCurveTU460.a" "clipLibrary2.cel[0].cev[101].cevr";
connectAttr "animCurveTU461.a" "clipLibrary2.cel[0].cev[102].cevr";
connectAttr "animCurveTA1155.a" "clipLibrary2.cel[0].cev[103].cevr";
connectAttr "animCurveTA1156.a" "clipLibrary2.cel[0].cev[104].cevr";
connectAttr "animCurveTA1157.a" "clipLibrary2.cel[0].cev[105].cevr";
connectAttr "animCurveTA1158.a" "clipLibrary2.cel[0].cev[106].cevr";
connectAttr "animCurveTA1159.a" "clipLibrary2.cel[0].cev[107].cevr";
connectAttr "animCurveTA1160.a" "clipLibrary2.cel[0].cev[108].cevr";
connectAttr "animCurveTA1161.a" "clipLibrary2.cel[0].cev[109].cevr";
connectAttr "animCurveTA1162.a" "clipLibrary2.cel[0].cev[110].cevr";
connectAttr "animCurveTA1163.a" "clipLibrary2.cel[0].cev[111].cevr";
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
// End of attack4B.ma
