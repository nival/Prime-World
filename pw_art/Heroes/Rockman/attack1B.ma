//Maya ASCII 2008 scene
//Name: attackF.ma
//Last modified: Fri, Oct 09, 2009 12:08:11 PM
//Codeset: 1251
requires maya "2008";
requires "Mayatomr" "9.0.1.2m - 3.6.1.6 ";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Unlimited 2008";
fileInfo "version" "2008";
fileInfo "cutIdentifier" "200708022245-704165";
fileInfo "osv" "Microsoft Windows XP Service Pack 3 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 178 ".cel[0].cev";
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
createNode animClip -n "attackFSource";
	setAttr ".ihi" 0;
	setAttr -s 178 ".ac[0:177]" no no yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes no no no no no no no no no no no no yes yes yes no no no no no no no no no 
		no no no yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes no no no no no no yes yes yes no no no;
	setAttr ".ss" 1;
	setAttr ".se" 45;
	setAttr ".ci" no;
createNode animCurveTU -n "animCurveTU335";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[0:4]"  9 10 3 3 9;
	setAttr -s 5 ".kot[0:4]"  9 10 3 3 9;
createNode animCurveTU -n "animCurveTU336";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[0:4]"  9 10 3 10 9;
	setAttr -s 5 ".kot[0:4]"  9 10 3 10 9;
createNode animCurveTA -n "animCurveTA791";
	setAttr ".tan" 9;
	setAttr -s 9 ".ktv[0:8]"  1 39.53428110495291 3 14.253255253492046 
		5 -14.857333603406389 6 -47.688885593065514 10 -45.941042822828464 14 -18.912723886936963 
		25 -6.8798372401008594 30 9.4839473274278436 45 39.53428110495291;
	setAttr -s 9 ".kit[1:8]"  10 10 3 9 10 9 9 9;
	setAttr -s 9 ".kot[1:8]"  10 10 3 9 10 9 9 9;
createNode animCurveTA -n "animCurveTA792";
	setAttr ".tan" 9;
	setAttr -s 9 ".ktv[0:8]"  1 32.600909957006799 3 -51.434218768614805 
		5 -51.965826792693477 6 67.829383859780563 10 65.754395399676611 14 56.272308042692814 
		25 17.727279232674242 30 1.7389440585096581 45 32.600909957006799;
	setAttr -s 9 ".kit[1:8]"  10 10 3 9 10 9 9 9;
	setAttr -s 9 ".kot[1:8]"  10 10 3 9 10 9 9 9;
createNode animCurveTA -n "animCurveTA793";
	setAttr ".tan" 9;
	setAttr -s 9 ".ktv[0:8]"  1 16.651520328974982 3 -141.32100967722297 
		5 -114.03055686596041 6 -39.792021059728782 10 -39.897311303253559 14 -16.932052096539518 
		25 -6.9139909232069474 30 11.887967258871058 45 16.651520328974982;
	setAttr -s 9 ".kit[1:8]"  10 10 3 9 10 9 9 9;
	setAttr -s 9 ".kot[1:8]"  10 10 3 9 10 9 9 9;
createNode animCurveTA -n "animCurveTA794";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  1 -87.582586884797436 3 -73.847322376631709 
		6 -71.453024517060754 7 -75.927140731816749 8 -76.71690180387877 10 -73.425105069386248 
		25 -23.046606952801909 45 -87.582586884797436;
	setAttr -s 8 ".kit[0:7]"  9 9 1 10 10 3 10 1;
	setAttr -s 8 ".kot[0:7]"  9 9 1 10 10 3 10 1;
	setAttr -s 8 ".kix[2:7]"  0.098550915718078613 0.033333331346511841 
		0.033333346247673035 0.066666662693023682 0.49999997019767761 0.066666662693023682;
	setAttr -s 8 ".kiy[2:7]"  -0.077555358409881592 0 0 0 -0.10589771717786789 
		0.23972558975219727;
	setAttr -s 8 ".kox[2:7]"  0.13188411295413971 0.033333346247673035 
		0.066666662693023682 0.49999997019767761 0.66666668653488159 0.066666662693023682;
	setAttr -s 8 ".koy[2:7]"  -0.10378718376159668 0 0 0 -0.14119696617126465 
		0.23972558975219727;
createNode animCurveTA -n "animCurveTA795";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA796";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA797";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA798";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  1 -0.90666238496249552 3 10.373642232624931 
		5 4.4477697773412821 6 -45.579084677400594 10 -45.579084677400594 25 -26.262851105308993 
		45 -0.90666238496249552;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 1;
	setAttr -s 7 ".kix[6]"  0.066666662693023682;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  0.066666662693023682;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "animCurveTA799";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  1 -0.14300750254877909 3 -23.567975544192787 
		5 -18.562769745045223 6 -1.2672131411434817 10 -1.2672131411434817 20 19.385258287338569 
		25 0.6861821367731975 30 -1.8134037082102368 45 -0.14300750254877909;
	setAttr -s 9 ".kit[0:8]"  9 10 10 10 10 10 10 10 
		1;
	setAttr -s 9 ".kot[0:8]"  9 10 10 10 10 10 10 10 
		1;
	setAttr -s 9 ".kix[8]"  0.066666662693023682;
	setAttr -s 9 ".kiy[8]"  -0.40884283185005188;
	setAttr -s 9 ".kox[8]"  0.066666662693023682;
	setAttr -s 9 ".koy[8]"  -0.40884283185005188;
createNode animCurveTA -n "animCurveTA800";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  1 -0.69869282260852494 3 19.71407615735033 
		5 7.3171855017678391 6 -23.79076007547895 10 -23.79076007547895 23 -6.1521852678264839 
		30 21.766859147511344 45 -0.69869282260852494;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 1;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 1;
	setAttr -s 8 ".kix[7]"  0.066666662693023682;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  0.066666662693023682;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTA -n "animCurveTA801";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  1 13.566397626420638 3 -23.62150596422223 
		5 -21.082281122329267 6 -6.4138273930642136 10 -6.4138273930642136 23 8.0997712233231347 
		26 -11.611635758086571 30 -10.463474087923126 45 13.566397626420638;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		1;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		1;
	setAttr -s 9 ".kix[8]"  0.066666662693023682;
	setAttr -s 9 ".kiy[8]"  0;
	setAttr -s 9 ".kox[8]"  0.066666662693023682;
	setAttr -s 9 ".koy[8]"  0;
createNode animCurveTA -n "animCurveTA802";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  1 -14.474463091487671 3 -16.569958520050811 
		5 -45.781194574109293 6 -78.851937052803748 10 -79.773474036654093 14 -53.510588624955858 
		25 -46.005340004729987 30 -38.91722069935755 45 -14.474463091487671;
	setAttr -s 9 ".kit[0:8]"  9 10 10 3 10 10 10 10 
		9;
	setAttr -s 9 ".kot[0:8]"  9 10 10 3 10 10 10 10 
		9;
createNode animCurveTA -n "animCurveTA803";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  1 28.826393195295356 3 -51.368390574046437 
		5 -51.175174576169454 6 69.523936536853242 10 67.767586019641328 14 60.772107791170342 
		25 28.028596249216555 30 11.609482341917293 45 28.826393195295356;
	setAttr -s 9 ".kit[0:8]"  9 10 10 3 10 10 10 10 
		9;
	setAttr -s 9 ".kot[0:8]"  9 10 10 3 10 10 10 10 
		9;
createNode animCurveTA -n "animCurveTA804";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  1 4.3502300737951041 3 -143.17012152456331 
		5 -103.63264322314951 6 -65.423415607045754 10 -65.85824467950178 14 -42.890540492939785 
		25 -7.7370129760240367 30 2.6158619508619045 45 4.3502300737951041;
	setAttr -s 9 ".kit[0:8]"  9 10 10 3 10 10 10 10 
		9;
	setAttr -s 9 ".kot[0:8]"  9 10 10 3 10 10 10 10 
		9;
createNode animCurveTA -n "animCurveTA805";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  1 -59.684677024606373 3 -55.113913014724361 
		6 -52.719615155153477 7 -57.750488985842445 8 -58.449456555083493 10 -54.681943672150297 
		25 -10.034283160962904 45 -59.684677024606373;
	setAttr -s 8 ".kit[0:7]"  9 9 1 10 10 10 10 1;
	setAttr -s 8 ".kot[0:7]"  9 9 1 10 10 10 10 1;
	setAttr -s 8 ".kix[2:7]"  0.098550915718078613 0.033333331346511841 
		0.033333346247673035 0.066666662693023682 0.49999997019767761 0.066666662693023682;
	setAttr -s 8 ".kiy[2:7]"  -0.077555358409881592 0 0 0.099412262439727783 
		-0.037420358508825302 0.079774878919124603;
	setAttr -s 8 ".kox[2:7]"  0.13188411295413971 0.033333346247673035 
		0.066666662693023682 0.49999997019767761 0.66666668653488159 0.066666662693023682;
	setAttr -s 8 ".koy[2:7]"  -0.10378718376159668 0 0 0.74559193849563599 
		-0.049893815070390701 0.079774878919124603;
createNode animCurveTA -n "animCurveTA806";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA807";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA808";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA809";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  1 -0.19158875421948376 3 -10.171852417236783 
		6 -17.197835894690886 10 -17.197835894690886 25 11.691716253129091 45 -0.19158875421948376;
	setAttr -s 6 ".kit[0:5]"  2 10 10 10 10 1;
	setAttr -s 6 ".kot[0:5]"  2 10 10 10 10 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  0.066666662693023682;
	setAttr -s 6 ".koy[5]"  -0.17418846487998962;
createNode animCurveTA -n "animCurveTA810";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  1 -7.898767459478834 3 -7.3771303871977079 
		6 -6.8752559585519268 10 -6.8752559585519268 25 -7.2780296672217029 45 -7.898767459478834;
	setAttr -s 6 ".kit[0:5]"  2 10 10 10 10 1;
	setAttr -s 6 ".kot[0:5]"  2 10 10 10 10 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  0.066666662693023682;
	setAttr -s 6 ".koy[5]"  0.0091042844578623772;
createNode animCurveTA -n "animCurveTA811";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  1 2.3461370896484395 3 3.6759609559965707 
		6 4.5486555084145017 10 4.5486555084145017 25 -0.74428388185083161 45 2.3461370896484395;
	setAttr -s 6 ".kit[0:5]"  2 10 10 10 10 1;
	setAttr -s 6 ".kot[0:5]"  2 10 10 10 10 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  0.066666662693023682;
	setAttr -s 6 ".koy[5]"  0.02320980466902256;
createNode animCurveTA -n "animCurveTA812";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 1.4245112294344 3 -1.6963346743692815 
		6 -15.908955296363992 10 -15.908955296363992 45 1.4245112294344;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.066666662693023682;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA813";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 1.8864606807611757 3 1.5563657748243374 
		6 0.008688607023490065 10 0.008688607023490065 45 1.8864606807611757;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.066666662693023682;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA814";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 -5.9921097590926697 3 -6.0858829270924888 
		6 -6.2810073422102235 10 -6.2810073422102235 45 -5.9921097590926697;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.066666662693023682;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL295";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL296";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 -0.32745760633437881 6 -0.74491232895853632 
		10 -0.74491232895853632 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.066666662693023682;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL297";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 -0.12272155611893799 3 -0.12272155611893799 
		6 -0.12272155611893799 10 -0.12272155611893799 45 -0.12272155611893799;
	setAttr -s 5 ".kit[0:4]"  9 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  9 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.066666662693023682;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL298";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 0.033 3 0.033 6 0.033 10 -0.28796836093681916 
		45 0.033;
	setAttr -s 5 ".kit[0:4]"  9 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  9 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.066666662693023682;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL299";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 -0.016 3 -0.25181469564796788 6 -0.25181469564796788 
		10 -0.30669779027736271 45 -0.016;
	setAttr -s 5 ".kit[0:4]"  9 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  9 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.066666662693023682;
	setAttr -s 5 ".kiy[4]"  -0.23581469058990479;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  -0.23581469058990479;
createNode animCurveTL -n "animCurveTL300";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 0.10379921435641129 3 0.10379921435641129 
		6 0.063132593101062076 10 0.10379921435641129 45 0.10379921435641129;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.066666662693023682;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA815";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  1 -18.178217858042064 3 -7.7441784385395858 
		6 2.3784481273371862 10 2.9128776996530164 22 -4.8663559898223667 30 -13.851018358337965 
		45 -18.178217858042064;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 9 9;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 9 9;
	setAttr -s 7 ".kix[0:6]"  0.066523261368274689 0.066666662693023682 
		0.10000000149011612 0.13333334028720856 0.40000000596046448 0.26666665077209473 0.5;
	setAttr -s 7 ".kiy[0:6]"  0.0579969622194767 0.14351259171962738 
		0 0 -0.17555111646652222 -0.080812454223632813 -0.075523875653743744;
	setAttr -s 7 ".kox[0:6]"  0.066523268818855286 0.10000000149011612 
		0.13333334028720856 0.40000000596046448 0.26666665077209473 0.5 0.5;
	setAttr -s 7 ".koy[0:6]"  0.057996965944766998 0.21526889503002167 
		0 0 -0.11703407019376755 -0.15152336657047272 -0.075523875653743744;
createNode animCurveTA -n "animCurveTA816";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  1 -4.6186256351197352 3 -1.2625335176246559 
		6 -0.44323756620960147 10 -1.1054922491185493 22 8.5830970634722696 30 5.2728822218796134 
		45 -4.6186256351197352;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 1 9;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 1 9;
	setAttr -s 7 ".kix[5:6]"  0.66508835554122925 0.5;
	setAttr -s 7 ".kiy[5:6]"  -0.15475893020629883 -0.1726393848657608;
	setAttr -s 7 ".kox[5:6]"  0.16508971154689789 0.5;
	setAttr -s 7 ".koy[5:6]"  -0.038414604961872101 -0.1726393848657608;
createNode animCurveTA -n "animCurveTA817";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  1 -7.7006231053605507 3 12.310952105733843 
		6 28.274144278740859 10 34.051720552779749 22 -3.1318442595502272 30 -3.5749738306036281 
		45 -7.7006231053605507;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 9 9;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 9 9;
createNode animCurveTL -n "animCurveTL301";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  1 -0.062545592999319929 3 0.0681232830739541 
		6 -0.18719424764380296 10 -0.2395016946258508 22 -0.064025840504967582 45 -0.062545592999319929;
	setAttr -s 6 ".kit[0:5]"  9 10 10 9 10 9;
	setAttr -s 6 ".kot[0:5]"  9 10 10 9 10 9;
createNode animCurveTL -n "animCurveTL302";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  1 -0.032867286470989195 3 -0.11 6 -0.18918299557585996 
		10 -0.189 14 -0.25150442997668487 45 -0.032867286470989195;
	setAttr -s 6 ".kit[0:5]"  9 10 10 10 10 9;
	setAttr -s 6 ".kot[0:5]"  9 10 10 10 10 9;
createNode animCurveTL -n "animCurveTL303";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  1 -0.0098384205421270955 3 0.043019803315718613 
		6 0.028915899509083253 10 0.028915899509083253 22 0.11915576043442085 30 0.15568503575478546 
		45 -0.0098384205421270955;
	setAttr -s 7 ".kit[0:6]"  9 10 10 10 10 10 9;
	setAttr -s 7 ".kot[0:6]"  9 10 10 10 10 10 9;
createNode animCurveTA -n "animCurveTA818";
	setAttr ".tan" 1;
	setAttr -s 9 ".ktv[0:8]"  1 -25.590668618635455 3 -20.876807546545354 
		5 -16.503807886767909 6 -16.503807886767909 10 -16.503807886767909 26 -16.503807886767909 
		35 -25.590668618635455 37 -25.590668618635455 45 -25.590668618635455;
	setAttr -s 9 ".kit[0:8]"  2 10 1 10 1 1 3 3 
		3;
	setAttr -s 9 ".kot[0:8]"  2 10 1 10 1 1 3 3 
		3;
	setAttr -s 9 ".kix[2:8]"  0.10000000149011612 0.033333331346511841 
		0.033333331346511841 0.033333331346511841 0.29999995231628418 0.066666722297668457 
		0.26666665077209473;
	setAttr -s 9 ".kiy[2:8]"  0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  0.13333334028720856 0.13333334028720856 
		0.13333334028720856 0.13333334028720856 0.066666722297668457 0.26666665077209473 
		0.26666665077209473;
	setAttr -s 9 ".koy[2:8]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA819";
	setAttr ".tan" 3;
	setAttr -s 9 ".ktv[0:8]"  1 0 3 0.98358283632806076 5 1.330383296706239 
		6 1.330383296706239 10 1.330383296706239 26 1.330383296706239 35 0 37 0 45 0;
	setAttr -s 9 ".kit[1:8]"  10 1 10 1 1 3 3 3;
	setAttr -s 9 ".kot[1:8]"  10 1 10 1 1 3 3 3;
	setAttr -s 9 ".kix[2:8]"  0.10000000149011612 0.033333331346511841 
		0.033333331346511841 0.033333331346511841 0.29999995231628418 0.066666722297668457 
		0.26666665077209473;
	setAttr -s 9 ".kiy[2:8]"  0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  0.13333334028720856 0.13333334028720856 
		0.13333334028720856 0.13333334028720856 0.066666722297668457 0.26666665077209473 
		0.26666665077209473;
	setAttr -s 9 ".koy[2:8]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA820";
	setAttr ".tan" 3;
	setAttr -s 9 ".ktv[0:8]"  1 0 3 13.21918502606515 5 1.2880821276638139 
		6 1.2880821276638139 10 1.2880821276638139 26 1.2880821276638139 35 0 37 0 45 0;
	setAttr -s 9 ".kit[1:8]"  10 1 10 1 1 3 3 3;
	setAttr -s 9 ".kot[1:8]"  10 1 10 1 1 3 3 3;
	setAttr -s 9 ".kix[2:8]"  0.10000000149011612 0.033333331346511841 
		0.033333331346511841 0.033333331346511841 0.29999995231628418 0.066666722297668457 
		0.26666665077209473;
	setAttr -s 9 ".kiy[2:8]"  0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  0.13333334028720856 0.13333334028720856 
		0.13333334028720856 0.13333334028720856 0.066666722297668457 0.26666665077209473 
		0.26666665077209473;
	setAttr -s 9 ".koy[2:8]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL304";
	setAttr ".tan" 3;
	setAttr -s 10 ".ktv[0:9]"  1 0 3 0.071276082456270637 5 0 6 0 10 0 
		26 0 30 0.02605299764478777 35 0 37 0 45 0;
	setAttr -s 10 ".kit[1:9]"  10 1 10 1 1 10 3 3 
		3;
	setAttr -s 10 ".kot[1:9]"  10 1 10 1 1 10 3 3 
		3;
	setAttr -s 10 ".kix[2:9]"  0.10000000149011612 0.033333331346511841 
		0.033333331346511841 0.033333331346511841 0.13333332538604736 0.16666662693023682 
		0.066666722297668457 0.26666665077209473;
	setAttr -s 10 ".kiy[2:9]"  0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[2:9]"  0.13333334028720856 0.13333334028720856 
		0.13333334028720856 0.13333334028720856 0.16666662693023682 0.066666722297668457 
		0.26666665077209473 0.26666665077209473;
	setAttr -s 10 ".koy[2:9]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL305";
	setAttr ".tan" 3;
	setAttr -s 8 ".ktv[0:7]"  1 0.15953969092363035 5 -0.46515705183908213 
		6 -0.46515705183908213 10 -0.46515705183908213 26 -0.46515705183908213 35 0.15953969092363035 
		37 0.15953969092363035 45 0.15953969092363035;
	setAttr -s 8 ".kit[1:7]"  1 10 1 1 3 3 3;
	setAttr -s 8 ".kot[1:7]"  1 10 1 1 3 3 3;
	setAttr -s 8 ".kix[1:7]"  0.1666666716337204 0.033333331346511841 
		0.033333331346511841 0.033333331346511841 0.29999995231628418 0.066666722297668457 
		0.26666665077209473;
	setAttr -s 8 ".kiy[1:7]"  -0.46244534850120544 0 0 0 0 0 0;
	setAttr -s 8 ".kox[1:7]"  0.13333334028720856 0.13333334028720856 
		0.13333334028720856 0.13333334028720856 0.066666722297668457 0.26666665077209473 
		0.26666665077209473;
	setAttr -s 8 ".koy[1:7]"  -0.36995628476142883 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL306";
	setAttr ".tan" 3;
	setAttr -s 8 ".ktv[0:7]"  1 -0.04 5 -0.04 6 -0.04 10 -0.04 26 -0.04 
		35 -0.04 37 -0.04 45 -0.04;
	setAttr -s 8 ".kit[1:7]"  1 10 1 1 3 3 3;
	setAttr -s 8 ".kot[1:7]"  1 10 1 1 3 3 3;
	setAttr -s 8 ".kix[1:7]"  0.1666666716337204 0.033333331346511841 
		0.033333331346511841 0.033333331346511841 0.29999995231628418 0.066666722297668457 
		0.26666665077209473;
	setAttr -s 8 ".kiy[1:7]"  0 0 0 0 0 0 0;
	setAttr -s 8 ".kox[1:7]"  0.13333334028720856 0.13333334028720856 
		0.13333334028720856 0.13333334028720856 0.066666722297668457 0.26666665077209473 
		0.26666665077209473;
	setAttr -s 8 ".koy[1:7]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA821";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 11.880229891661756 3 11.880229891661756 
		6 11.880229891661756 10 11.880229891661756 45 11.880229891661756;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA822";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA823";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL307";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL308";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 -0.20007920657257083 3 -0.20007920657257083 
		6 -0.20007920657257083 10 -0.20007920657257083 45 -0.20007920657257083;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL309";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 0.098575236578624326 3 0.098575236578624326 
		6 0.098575236578624326 10 0.098575236578624326 45 0.098575236578624326;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU337";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  1 1 3 1 6 1 10 1 45 1;
	setAttr -s 5 ".kit[0:4]"  2 9 9 9 1;
	setAttr -s 5 ".kot[0:4]"  2 5 5 5 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA824";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA825";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA826";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL310";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 -0.81944359671150613 3 -0.81944359671150613 
		6 -0.81944359671150613 10 -0.81944359671150613 45 -0.81944359671150613;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL311";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 0.029470472912715796 3 0.029470472912715796 
		6 0.029470472912715796 10 0.029470472912715796 45 0.029470472912715796;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL312";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 -0.070295643204272437 3 -0.070295643204272437 
		6 -0.070295643204272437 10 -0.070295643204272437 45 -0.070295643204272437;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.066666662693023682;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU338";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  1 1 3 1 6 1 10 1 45 1;
	setAttr -s 5 ".kit[0:4]"  2 9 9 9 1;
	setAttr -s 5 ".kot[0:4]"  2 5 5 5 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA827";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 -4.8160457500419067 3 -4.8160457500419067 
		6 -4.8160457500419067 10 -4.8160457500419067 45 -4.8160457500419067;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA828";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA829";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL313";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 -0.80451419482641451 3 -0.80451419482641451 
		6 -0.80451419482641451 10 -0.80451419482641451 45 -0.80451419482641451;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL314";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 -2.4945889741368431e-013 3 0 6 0 10 0 
		45 -2.4945889741368431e-013;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL315";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 -0.0085562672260772743 3 -0.0085562672260772743 
		6 -0.0085562672260772743 10 -0.0085562672260772743 45 -0.0085562672260772743;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU339";
	setAttr ".tan" 10;
	setAttr -s 10 ".ktv[0:9]"  1 0 3 0 6 0 10 0 24 0 26 0 35 0 37 0 38 
		0 45 0;
	setAttr -s 10 ".kit[0:9]"  2 10 10 10 10 10 10 3 
		1 9;
	setAttr -s 10 ".kot[0:9]"  2 10 10 10 10 10 10 3 
		1 9;
	setAttr -s 10 ".kix[8:9]"  0.066666722297668457 0.23333334922790527;
	setAttr -s 10 ".kiy[8:9]"  0 0;
	setAttr -s 10 ".kox[8:9]"  0.26666665077209473 0.23333334922790527;
	setAttr -s 10 ".koy[8:9]"  0 0;
createNode animCurveTU -n "animCurveTU340";
	setAttr ".tan" 10;
	setAttr -s 10 ".ktv[0:9]"  1 45 3 45 6 45 10 45 24 45 26 45 35 45 
		37 45 38 45 45 45;
	setAttr -s 10 ".kit[0:9]"  2 10 10 10 10 10 10 1 
		1 1;
	setAttr -s 10 ".kot[0:9]"  2 10 10 10 10 10 10 1 
		1 1;
	setAttr -s 10 ".kix[7:9]"  1 1 1;
	setAttr -s 10 ".kiy[7:9]"  0 0 0;
	setAttr -s 10 ".kox[7:9]"  0.066666662693023682 0.066666662693023682 
		0.066666662693023682;
	setAttr -s 10 ".koy[7:9]"  0 0 0;
createNode animCurveTU -n "animCurveTU341";
	setAttr ".tan" 10;
	setAttr -s 10 ".ktv[0:9]"  1 45 3 45 6 45 10 45 24 45 26 45 35 45 
		37 45 38 45 45 45;
	setAttr -s 10 ".kit[0:9]"  2 10 10 10 10 10 10 1 
		1 1;
	setAttr -s 10 ".kot[0:9]"  2 10 10 10 10 10 10 1 
		1 1;
	setAttr -s 10 ".kix[7:9]"  1 1 1;
	setAttr -s 10 ".kiy[7:9]"  0 0 0;
	setAttr -s 10 ".kox[7:9]"  0.066666662693023682 0.066666662693023682 
		0.066666662693023682;
	setAttr -s 10 ".koy[7:9]"  0 0 0;
createNode animCurveTU -n "animCurveTU342";
	setAttr ".tan" 10;
	setAttr -s 10 ".ktv[0:9]"  1 45 3 45 6 45 10 45 24 45 26 45 35 45 
		37 45 38 45 45 45;
	setAttr -s 10 ".kit[0:9]"  2 10 10 10 10 10 10 1 
		1 1;
	setAttr -s 10 ".kot[0:9]"  2 10 10 10 10 10 10 1 
		1 1;
	setAttr -s 10 ".kix[7:9]"  1 1 1;
	setAttr -s 10 ".kiy[7:9]"  0 0 0;
	setAttr -s 10 ".kox[7:9]"  0.066666662693023682 0.066666662693023682 
		0.066666662693023682;
	setAttr -s 10 ".koy[7:9]"  0 0 0;
createNode animCurveTA -n "animCurveTA830";
	setAttr ".tan" 10;
	setAttr -s 10 ".ktv[0:9]"  1 0 3 0 6 0 10 0 24 0 26 0 35 0 37 0 38 
		0 45 0;
	setAttr -s 10 ".kit[0:9]"  2 10 10 10 10 10 10 3 
		1 9;
	setAttr -s 10 ".kot[0:9]"  2 10 10 10 10 10 10 3 
		1 9;
	setAttr -s 10 ".kix[8:9]"  0.066666722297668457 0.23333334922790527;
	setAttr -s 10 ".kiy[8:9]"  0 0;
	setAttr -s 10 ".kox[8:9]"  0.26666665077209473 0.23333334922790527;
	setAttr -s 10 ".koy[8:9]"  0 0;
createNode animCurveTA -n "animCurveTA831";
	setAttr ".tan" 10;
	setAttr -s 11 ".ktv[0:10]"  1 0 3 0 5 6.7036155847945817 6 0.53604794732939887 
		10 -0.30307694958640796 24 -0.10419847015882577 26 5.393117023074395 35 13.311941745515345 
		37 3.4355825110878264 38 0 45 0;
	setAttr -s 11 ".kit[0:10]"  2 10 3 9 10 10 10 3 
		3 1 9;
	setAttr -s 11 ".kot[0:10]"  2 10 3 9 10 10 10 3 
		3 1 9;
	setAttr -s 11 ".kix[9:10]"  0.066666722297668457 0.23333334922790527;
	setAttr -s 11 ".kiy[9:10]"  0 0;
	setAttr -s 11 ".kox[9:10]"  0.26666665077209473 0.23333334922790527;
	setAttr -s 11 ".koy[9:10]"  0 0;
createNode animCurveTU -n "animCurveTU343";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 6 0 45 0;
	setAttr -s 4 ".kit[0:3]"  2 10 10 1;
	setAttr -s 4 ".kot[0:3]"  2 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  0.066666662693023682;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU344";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  1 45 3 45 6 45 45 45;
	setAttr -s 4 ".kit[0:3]"  2 10 10 1;
	setAttr -s 4 ".kot[0:3]"  2 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  0.066666662693023682;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU345";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  1 45 3 45 6 45 45 45;
	setAttr -s 4 ".kit[0:3]"  2 10 10 1;
	setAttr -s 4 ".kot[0:3]"  2 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  0.066666662693023682;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU346";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  1 45 3 45 6 45 45 45;
	setAttr -s 4 ".kit[0:3]"  2 10 10 1;
	setAttr -s 4 ".kot[0:3]"  2 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  0.066666662693023682;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "animCurveTA832";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 6 0 45 0;
	setAttr -s 4 ".kit[0:3]"  2 10 10 1;
	setAttr -s 4 ".kot[0:3]"  2 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  0.066666662693023682;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "animCurveTA833";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 7.3780659221452769 6 0.61062508896188783 
		45 0;
	setAttr -s 4 ".kit[1:3]"  10 3 1;
	setAttr -s 4 ".kot[1:3]"  10 3 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  0.066666662693023682;
	setAttr -s 4 ".koy[3]"  0.12877154350280762;
createNode animCurveTU -n "animCurveTU347";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU348";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU349";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU350";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU351";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU352";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU353";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU354";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU355";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU356";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU357";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU358";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA834";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA835";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA836";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 -2.5999764661798822e-011 3 0 6 0 10 0 
		45 -2.5999764661798822e-011;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU359";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU360";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU361";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU362";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU363";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU364";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU365";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU366";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU367";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU368";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU369";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU370";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA837";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA838";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA839";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 -2.5997909391022333e-011 3 0 6 0 10 0 
		45 -2.5997909391022333e-011;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA840";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  1 -5.8382275551355809 3 17.732018121725257 
		5 17.132936162497632 6 -28.256620204744884 10 -13.843694123357738 21 -20.11046895356127 
		27 0.44590213474813412 35 -7.003172063074298 45 -5.8382275551355809;
	setAttr -s 9 ".kit[0:8]"  1 10 10 3 9 10 10 10 
		1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 3 9 10 10 10 
		1;
	setAttr -s 9 ".kix[0:8]"  0.06666005402803421 0.066666662693023682 
		0.066666670143604279 0.033333331346511841 0.13333334028720856 0.36666664481163025 
		0.19999998807907104 0.26666665077209473 0.06666005402803421;
	setAttr -s 9 ".kiy[0:8]"  -0.015686014667153358 0 0 0 0.037913911044597626 
		0.16137680411338806 0.098042353987693787 0 -0.015686014667153358;
	setAttr -s 9 ".kox[0:8]"  0.066660061478614807 0.066666670143604279 
		0.033333331346511841 0.13333334028720856 0.36666664481163025 0.19999998807907104 
		0.26666665077209473 0.33333337306976318 0.066660061478614807;
	setAttr -s 9 ".koy[0:8]"  -0.015686014667153358 0 0 0 0.10426324605941772 
		0.08802371472120285 0.13072313368320465 0 -0.015686014667153358;
createNode animCurveTA -n "animCurveTA841";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  1 -2.3136539176186792 3 3.5427242056509987 
		5 3.0611352085544206 6 -7.5034339315458576 10 -4.2588971786244505 21 5.1488543713932122 
		27 10.729988546555346 35 8.5144895314009901 45 -2.3136539176186792;
	setAttr -s 9 ".kit[0:8]"  1 10 10 3 9 10 10 10 
		1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 3 9 10 10 10 
		1;
	setAttr -s 9 ".kix[0:8]"  0.066300936043262482 0.066666662693023682 
		0.066666670143604279 0.033333331346511841 0.13333334028720856 0.36666664481163025 
		0.19999998807907104 0.26666665077209473 0.066300936043262482;
	setAttr -s 9 ".kiy[0:8]"  -0.034498795866966248 0 0 0 0.05888642743229866 
		0.16927409172058105 0 0 -0.034498795866966248;
	setAttr -s 9 ".kox[0:8]"  0.066300936043262482 0.066666670143604279 
		0.033333331346511841 0.13333334028720856 0.36666664481163025 0.19999998807907104 
		0.26666665077209473 0.33333337306976318 0.066300936043262482;
	setAttr -s 9 ".koy[0:8]"  -0.034498799592256546 0 0 0 0.1619376540184021 
		0.092331327497959137 0 0 -0.034498799592256546;
createNode animCurveTA -n "animCurveTA842";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  1 -13.887028133305018 3 -13.630265119368902 
		5 -12.733445712978989 6 -11.942126056823811 10 -13.427303866226083 21 2.5410049602552385 
		27 -14.216356117463278 35 -37.807285866632675 45 -13.887028133305018;
	setAttr -s 9 ".kit[0:8]"  1 10 10 3 9 10 10 10 
		1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 3 9 10 10 10 
		1;
	setAttr -s 9 ".kix[0:8]"  0.066675402224063873 0.066666662693023682 
		0.066666670143604279 0.033333331346511841 0.13333334028720856 0.36666664481163025 
		0.19999998807907104 0.26666665077209473 0.066675402224063873;
	setAttr -s 9 ".kiy[0:8]"  0.0037189542781561613 0 0 0 0.067407555878162384 
		-0.0089110098779201508 -0.30180451273918152 0.0025546031538397074 0.0037189542781561613;
	setAttr -s 9 ".kox[0:8]"  0.06667540967464447 0.066666670143604279 
		0.033333331346511841 0.13333334028720856 0.36666664481163025 0.19999998807907104 
		0.26666665077209473 0.33333337306976318 0.06667540967464447;
	setAttr -s 9 ".koy[0:8]"  0.0037189535796642303 0 0 0 0.18537075817584991 
		-0.0048605506308376789 -0.4024060070514679 0.0031932545825839043 0.0037189535796642303;
createNode animCurveTA -n "animCurveTA843";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 13.873263178484903 3 30.693756033742044 
		6 48.040697098624321 10 59.791438749284673 45 13.873263178484903;
	setAttr -s 5 ".kit[0:4]"  2 10 10 9 1;
	setAttr -s 5 ".kot[0:4]"  2 10 10 9 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0.13230280578136444;
createNode animCurveTA -n "animCurveTA844";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  1 0 3 0 6 0 10 0 24 10.730327504388242 
		45 0;
	setAttr -s 6 ".kit[0:5]"  2 10 10 9 10 1;
	setAttr -s 6 ".kot[0:5]"  2 10 10 9 10 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  0.066666662693023682;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTA -n "animCurveTA845";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[0:4]"  2 10 10 9 1;
	setAttr -s 5 ".kot[0:4]"  2 10 10 9 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA846";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 0;
	setAttr ".kit[9]"  4;
	setAttr ".kot[9]"  4;
createNode animCurveTA -n "animCurveTA847";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 0;
	setAttr ".kit[9]"  4;
	setAttr ".kot[9]"  4;
createNode animCurveTA -n "animCurveTA848";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 0;
	setAttr ".kit[9]"  4;
	setAttr ".kot[9]"  4;
createNode animCurveTA -n "animCurveTA849";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 -7.6359447996384162;
createNode animCurveTA -n "animCurveTA850";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 -35.260196151694586;
createNode animCurveTA -n "animCurveTA851";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 68.744635926587719;
createNode animCurveTA -n "animCurveTA852";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 -7.6359447996384162;
createNode animCurveTA -n "animCurveTA853";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 -35.260196151694586;
createNode animCurveTA -n "animCurveTA854";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 68.744635926587719;
createNode animCurveTA -n "animCurveTA855";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 -7.6359447996384162;
createNode animCurveTA -n "animCurveTA856";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 -35.260196151694586;
createNode animCurveTA -n "animCurveTA857";
	setAttr ".tan" 1;
	setAttr ".ktv[0]"  1 68.744635926587719;
	setAttr ".kix[0]"  0.066353410482406616;
	setAttr ".kiy[0]"  -0.10914206504821777;
	setAttr ".kox[0]"  0.066353403031826019;
	setAttr ".koy[0]"  -0.10914205014705658;
createNode animCurveTA -n "animCurveTA858";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 18.08;
createNode animCurveTA -n "animCurveTA859";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1 -0.0336;
createNode animCurveTA -n "animCurveTA860";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA861";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 18.373158409800983;
createNode animCurveTA -n "animCurveTA862";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA863";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA864";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1 18.373158409800983;
createNode animCurveTA -n "animCurveTA865";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA866";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA867";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 18.373158409800983;
createNode animCurveTA -n "animCurveTA868";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA869";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA870";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 18.373158409800983;
createNode animCurveTA -n "animCurveTA871";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA872";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA873";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 18.373158409800983;
createNode animCurveTA -n "animCurveTA874";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA875";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA876";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 -5.4432506707315573;
createNode animCurveTA -n "animCurveTA877";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA878";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 1.4808130565433952;
createNode animCurveTA -n "animCurveTA879";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 -13.113682797820777;
	setAttr ".kit[8]"  4;
	setAttr ".kot[8]"  4;
createNode animCurveTA -n "animCurveTA880";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 -4.0919497789234391;
	setAttr ".kit[8]"  4;
	setAttr ".kot[8]"  4;
createNode animCurveTA -n "animCurveTA881";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 31.178362171912408;
	setAttr ".kit[8]"  4;
	setAttr ".kot[8]"  4;
createNode animCurveTL -n "animCurveTL316";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0.30350192845064827;
createNode animCurveTL -n "animCurveTL317";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -1.0240687361594651;
createNode animCurveTL -n "animCurveTL318";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -0.43946686130894153;
createNode animCurveTL -n "animCurveTL319";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0.27531887801250954;
createNode animCurveTL -n "animCurveTL320";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -1.0012123423352446;
createNode animCurveTL -n "animCurveTL321";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0.71970840690534188;
createNode animCurveTA -n "animCurveTA882";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -111.88689016967699;
createNode animCurveTA -n "animCurveTA883";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -132.63553015029723;
createNode animCurveTA -n "animCurveTA884";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -66.606237462352041;
createNode animCurveTL -n "animCurveTL322";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0.4196306328102265;
createNode animCurveTL -n "animCurveTL323";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -0.14401492817444136;
createNode animCurveTL -n "animCurveTL324";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -0.19935929083177334;
createNode animCurveTA -n "animCurveTA885";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 119.62711466156466;
createNode animCurveTA -n "animCurveTA886";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 131.41878674178685;
createNode animCurveTA -n "animCurveTA887";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 301.25683546959215;
createNode animCurveTL -n "animCurveTL325";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0.40867405508166788;
createNode animCurveTL -n "animCurveTL326";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -0.10123643033093419;
createNode animCurveTL -n "animCurveTL327";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0.51342548710889013;
createNode animCurveTL -n "animCurveTL328";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL329";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL330";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL331";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL332";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL333";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 3 0 6 0 10 0 45 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA888";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA889";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA890";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "animCurveTL334";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "animCurveTL335";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "animCurveTL336";
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
	setAttr ".o" 45;
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
	setAttr -s 4 ".sol";
connectAttr "attackFSource.cl" "clipLibrary1.sc[0]";
connectAttr "animCurveTU335.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "animCurveTU336.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "animCurveTA791.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "animCurveTA792.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "animCurveTA793.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "animCurveTA794.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "animCurveTA795.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "animCurveTA796.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "animCurveTA797.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "animCurveTA798.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "animCurveTA799.a" "clipLibrary1.cel[0].cev[10].cevr";
connectAttr "animCurveTA800.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "animCurveTA801.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "animCurveTA802.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "animCurveTA803.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "animCurveTA804.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "animCurveTA805.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "animCurveTA806.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "animCurveTA807.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "animCurveTA808.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "animCurveTA809.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "animCurveTA810.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "animCurveTA811.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "animCurveTA812.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "animCurveTA813.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "animCurveTA814.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "animCurveTL295.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "animCurveTL296.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "animCurveTL297.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "animCurveTL298.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "animCurveTL299.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "animCurveTL300.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "animCurveTA815.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "animCurveTA816.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "animCurveTA817.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "animCurveTL301.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "animCurveTL302.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "animCurveTL303.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "animCurveTA818.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "animCurveTA819.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "animCurveTA820.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "animCurveTL304.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "animCurveTL305.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "animCurveTL306.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "animCurveTA821.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "animCurveTA822.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "animCurveTA823.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "animCurveTL307.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "animCurveTL308.a" "clipLibrary1.cel[0].cev[48].cevr";
connectAttr "animCurveTL309.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "animCurveTU337.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "animCurveTA824.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "animCurveTA825.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "animCurveTA826.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "animCurveTL310.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "animCurveTL311.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "animCurveTL312.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "animCurveTU338.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "animCurveTA827.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "animCurveTA828.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "animCurveTA829.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "animCurveTL313.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "animCurveTL314.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "animCurveTL315.a" "clipLibrary1.cel[0].cev[63].cevr";
connectAttr "animCurveTU339.a" "clipLibrary1.cel[0].cev[64].cevr";
connectAttr "animCurveTU340.a" "clipLibrary1.cel[0].cev[65].cevr";
connectAttr "animCurveTU341.a" "clipLibrary1.cel[0].cev[66].cevr";
connectAttr "animCurveTU342.a" "clipLibrary1.cel[0].cev[67].cevr";
connectAttr "animCurveTA830.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "animCurveTA831.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "animCurveTU343.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "animCurveTU344.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "animCurveTU345.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "animCurveTU346.a" "clipLibrary1.cel[0].cev[73].cevr";
connectAttr "animCurveTA832.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "animCurveTA833.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "animCurveTU347.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "animCurveTU348.a" "clipLibrary1.cel[0].cev[77].cevr";
connectAttr "animCurveTU349.a" "clipLibrary1.cel[0].cev[78].cevr";
connectAttr "animCurveTU350.a" "clipLibrary1.cel[0].cev[79].cevr";
connectAttr "animCurveTU351.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "animCurveTU352.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "animCurveTU353.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "animCurveTU354.a" "clipLibrary1.cel[0].cev[83].cevr";
connectAttr "animCurveTU355.a" "clipLibrary1.cel[0].cev[84].cevr";
connectAttr "animCurveTU356.a" "clipLibrary1.cel[0].cev[85].cevr";
connectAttr "animCurveTU357.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "animCurveTU358.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "animCurveTA834.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "animCurveTA835.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr "animCurveTA836.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "animCurveTU359.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "animCurveTU360.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "animCurveTU361.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "animCurveTU362.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "animCurveTU363.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "animCurveTU364.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "animCurveTU365.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "animCurveTU366.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "animCurveTU367.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "animCurveTU368.a" "clipLibrary1.cel[0].cev[100].cevr";
connectAttr "animCurveTU369.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "animCurveTU370.a" "clipLibrary1.cel[0].cev[102].cevr";
connectAttr "animCurveTA837.a" "clipLibrary1.cel[0].cev[103].cevr";
connectAttr "animCurveTA838.a" "clipLibrary1.cel[0].cev[104].cevr";
connectAttr "animCurveTA839.a" "clipLibrary1.cel[0].cev[105].cevr";
connectAttr "animCurveTA840.a" "clipLibrary1.cel[0].cev[106].cevr";
connectAttr "animCurveTA841.a" "clipLibrary1.cel[0].cev[107].cevr";
connectAttr "animCurveTA842.a" "clipLibrary1.cel[0].cev[108].cevr";
connectAttr "animCurveTA843.a" "clipLibrary1.cel[0].cev[109].cevr";
connectAttr "animCurveTA844.a" "clipLibrary1.cel[0].cev[110].cevr";
connectAttr "animCurveTA845.a" "clipLibrary1.cel[0].cev[111].cevr";
connectAttr "animCurveTA846.a" "clipLibrary1.cel[0].cev[112].cevr";
connectAttr "animCurveTA847.a" "clipLibrary1.cel[0].cev[113].cevr";
connectAttr "animCurveTA848.a" "clipLibrary1.cel[0].cev[114].cevr";
connectAttr "animCurveTA849.a" "clipLibrary1.cel[0].cev[115].cevr";
connectAttr "animCurveTA850.a" "clipLibrary1.cel[0].cev[116].cevr";
connectAttr "animCurveTA851.a" "clipLibrary1.cel[0].cev[117].cevr";
connectAttr "animCurveTA852.a" "clipLibrary1.cel[0].cev[118].cevr";
connectAttr "animCurveTA853.a" "clipLibrary1.cel[0].cev[119].cevr";
connectAttr "animCurveTA854.a" "clipLibrary1.cel[0].cev[120].cevr";
connectAttr "animCurveTA855.a" "clipLibrary1.cel[0].cev[121].cevr";
connectAttr "animCurveTA856.a" "clipLibrary1.cel[0].cev[122].cevr";
connectAttr "animCurveTA857.a" "clipLibrary1.cel[0].cev[123].cevr";
connectAttr "animCurveTA858.a" "clipLibrary1.cel[0].cev[124].cevr";
connectAttr "animCurveTA859.a" "clipLibrary1.cel[0].cev[125].cevr";
connectAttr "animCurveTA860.a" "clipLibrary1.cel[0].cev[126].cevr";
connectAttr "animCurveTA861.a" "clipLibrary1.cel[0].cev[127].cevr";
connectAttr "animCurveTA862.a" "clipLibrary1.cel[0].cev[128].cevr";
connectAttr "animCurveTA863.a" "clipLibrary1.cel[0].cev[129].cevr";
connectAttr "animCurveTA864.a" "clipLibrary1.cel[0].cev[130].cevr";
connectAttr "animCurveTA865.a" "clipLibrary1.cel[0].cev[131].cevr";
connectAttr "animCurveTA866.a" "clipLibrary1.cel[0].cev[132].cevr";
connectAttr "animCurveTA867.a" "clipLibrary1.cel[0].cev[133].cevr";
connectAttr "animCurveTA868.a" "clipLibrary1.cel[0].cev[134].cevr";
connectAttr "animCurveTA869.a" "clipLibrary1.cel[0].cev[135].cevr";
connectAttr "animCurveTA870.a" "clipLibrary1.cel[0].cev[136].cevr";
connectAttr "animCurveTA871.a" "clipLibrary1.cel[0].cev[137].cevr";
connectAttr "animCurveTA872.a" "clipLibrary1.cel[0].cev[138].cevr";
connectAttr "animCurveTA873.a" "clipLibrary1.cel[0].cev[139].cevr";
connectAttr "animCurveTA874.a" "clipLibrary1.cel[0].cev[140].cevr";
connectAttr "animCurveTA875.a" "clipLibrary1.cel[0].cev[141].cevr";
connectAttr "animCurveTA876.a" "clipLibrary1.cel[0].cev[142].cevr";
connectAttr "animCurveTA877.a" "clipLibrary1.cel[0].cev[143].cevr";
connectAttr "animCurveTA878.a" "clipLibrary1.cel[0].cev[144].cevr";
connectAttr "animCurveTA879.a" "clipLibrary1.cel[0].cev[145].cevr";
connectAttr "animCurveTA880.a" "clipLibrary1.cel[0].cev[146].cevr";
connectAttr "animCurveTA881.a" "clipLibrary1.cel[0].cev[147].cevr";
connectAttr "animCurveTL316.a" "clipLibrary1.cel[0].cev[148].cevr";
connectAttr "animCurveTL317.a" "clipLibrary1.cel[0].cev[149].cevr";
connectAttr "animCurveTL318.a" "clipLibrary1.cel[0].cev[150].cevr";
connectAttr "animCurveTL319.a" "clipLibrary1.cel[0].cev[151].cevr";
connectAttr "animCurveTL320.a" "clipLibrary1.cel[0].cev[152].cevr";
connectAttr "animCurveTL321.a" "clipLibrary1.cel[0].cev[153].cevr";
connectAttr "animCurveTA882.a" "clipLibrary1.cel[0].cev[154].cevr";
connectAttr "animCurveTA883.a" "clipLibrary1.cel[0].cev[155].cevr";
connectAttr "animCurveTA884.a" "clipLibrary1.cel[0].cev[156].cevr";
connectAttr "animCurveTL322.a" "clipLibrary1.cel[0].cev[157].cevr";
connectAttr "animCurveTL323.a" "clipLibrary1.cel[0].cev[158].cevr";
connectAttr "animCurveTL324.a" "clipLibrary1.cel[0].cev[159].cevr";
connectAttr "animCurveTA885.a" "clipLibrary1.cel[0].cev[160].cevr";
connectAttr "animCurveTA886.a" "clipLibrary1.cel[0].cev[161].cevr";
connectAttr "animCurveTA887.a" "clipLibrary1.cel[0].cev[162].cevr";
connectAttr "animCurveTL325.a" "clipLibrary1.cel[0].cev[163].cevr";
connectAttr "animCurveTL326.a" "clipLibrary1.cel[0].cev[164].cevr";
connectAttr "animCurveTL327.a" "clipLibrary1.cel[0].cev[165].cevr";
connectAttr "animCurveTL328.a" "clipLibrary1.cel[0].cev[166].cevr";
connectAttr "animCurveTL329.a" "clipLibrary1.cel[0].cev[167].cevr";
connectAttr "animCurveTL330.a" "clipLibrary1.cel[0].cev[168].cevr";
connectAttr "animCurveTL331.a" "clipLibrary1.cel[0].cev[169].cevr";
connectAttr "animCurveTL332.a" "clipLibrary1.cel[0].cev[170].cevr";
connectAttr "animCurveTL333.a" "clipLibrary1.cel[0].cev[171].cevr";
connectAttr "animCurveTA888.a" "clipLibrary1.cel[0].cev[172].cevr";
connectAttr "animCurveTA889.a" "clipLibrary1.cel[0].cev[173].cevr";
connectAttr "animCurveTA890.a" "clipLibrary1.cel[0].cev[174].cevr";
connectAttr "animCurveTL334.a" "clipLibrary1.cel[0].cev[175].cevr";
connectAttr "animCurveTL335.a" "clipLibrary1.cel[0].cev[176].cevr";
connectAttr "animCurveTL336.a" "clipLibrary1.cel[0].cev[177].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of attackF.ma
