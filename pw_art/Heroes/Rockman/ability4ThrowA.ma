//Maya ASCII 2008 scene
//Name: ability4ThrowA.ma
//Last modified: Tue, Sep 22, 2009 11:14:17 AM
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
	setAttr -s 130 ".cel[0].cev";
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
createNode animClip -n "ability4_1StartSource2";
	setAttr ".ihi" 0;
	setAttr -s 130 ".ac";
	setAttr ".ac[0:111]" no no yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes no no no no no no yes yes yes no 
		no no yes yes yes no no no yes yes yes no no no no yes yes yes no no no no yes yes 
		yes no no no no no no no yes yes no no no no yes yes no no no no no no no no no no 
		no no yes yes yes no no no no no no no no no no no no yes yes yes yes yes yes yes 
		yes yes;
	setAttr ".ac[148:165]" no no no no no no yes yes yes no no no yes yes yes 
		no no no;
	setAttr ".se" 19;
	setAttr ".ci" no;
createNode animCurveTU -n "animCurveTU390";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 1 1 2 1 19 1;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[0:3]"  1 10 10 3;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[0:3]"  1 1 1 1;
	setAttr -s 4 ".koy[0:3]"  0 0 0 0;
createNode animCurveTU -n "animCurveTU391";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 1 1 2 1 19 1;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[0:3]"  1 10 10 3;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[0:3]"  1 1 1 1;
	setAttr -s 4 ".koy[0:3]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1012";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -16.433008012612902 2 -31.195806820730525 
		4 -32.713044948771866 9 41.157126521024942 13 -19.911393005424234 14 -45.900073446502894 
		15 -68.940593880275813 16 -82.82739352908122 17 -89.455040683431079 19 -89.455040683431079;
	setAttr -s 10 ".kit[3:9]"  1 10 10 10 10 10 1;
	setAttr -s 10 ".kot[0:9]"  1 10 10 1 10 10 10 10 
		10 3;
	setAttr -s 10 ".kix[3:9]"  1 0.1090359091758728 0.077671654522418976 
		0.10288989543914795 0.18305043876171112 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 -0.99403780698776245 -0.9969789981842041 
		-0.99469280242919922 -0.98310351371765137 0 0;
	setAttr -s 10 ".kox[0:9]"  0.25049063563346863 1 1 1 0.1090359091758728 
		0.077671654522418976 0.10288989543914795 0.18305043876171112 1 1;
	setAttr -s 10 ".koy[0:9]"  -0.96811908483505249 0 0 0 -0.99403780698776245 
		-0.9969789981842041 -0.99469280242919922 -0.98310351371765137 0 0;
createNode animCurveTA -n "animCurveTA1013";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 46.484153693874759 2 39.448537418915414 
		4 1.7162337615894914 9 -8.4586571110921067 13 -6.8729110237901097 14 -6.5792543409564059 
		15 -32.872775788344619 16 -16.691080358455281 17 -1.3764914370199928 19 -1.3764914370199928;
	setAttr -s 10 ".kit[3:9]"  1 10 10 10 10 10 1;
	setAttr -s 10 ".kot[0:9]"  1 10 10 1 10 10 10 10 
		10 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 0.35337603092193604 0.12039308995008469 
		1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 -0.93548136949539185 0.99272632598876953 
		0 0;
	setAttr -s 10 ".kox[0:9]"  0.47712895274162292 0.16821373999118805 
		0.26879087090492249 1 1 1 0.35337603092193604 0.12039308995008469 1 1;
	setAttr -s 10 ".koy[0:9]"  -0.87883329391479492 -0.98575049638748169 
		-0.96319854259490967 0 0 0 -0.93548136949539185 0.99272632598876953 0 0;
createNode animCurveTA -n "animCurveTA1014";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -14.962212153601083 2 33.488757645726594 
		4 29.146950919551628 9 -97.2644864206178 13 -101.40521102843206 14 -101.54698584600887 
		15 -92.576790913832369 16 -41.116183601644231 17 -5.6400210530936121 19 -5.6400210530936121;
	setAttr -s 10 ".kit[3:9]"  1 10 10 10 10 10 1;
	setAttr -s 10 ".kot[0:9]"  1 10 10 1 10 10 10 10 
		10 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 0.063082277774810791 0.043894395232200623 
		1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0.9980083703994751 0.99903619289398193 
		0 0;
	setAttr -s 10 ".kox[0:9]"  0.078592926263809204 0.1706533282995224 
		0.10171585530042648 1 1 1 0.063082277774810791 0.043894395232200623 1 1;
	setAttr -s 10 ".koy[0:9]"  0.9969068169593811 0.98533111810684204 
		-0.99481350183486938 0 0 0 0.9980083703994751 0.99903619289398193 0 0;
createNode animCurveTA -n "animCurveTA1015";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -22.136766656027952 2 -33.783654902297663 
		4 -55.727362652924363 9 -88.838184689260174 13 -99.93456229380682 14 -102.64644562007194 
		15 -93.765673893427547 16 -38.328992405940923 17 0 19 0;
	setAttr -s 10 ".kit[3:9]"  1 10 10 10 10 10 1;
	setAttr -s 10 ".kot[0:9]"  1 10 10 1 10 10 10 10 
		10 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 0.059284090995788574 0.040703091770410538 
		1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0.998241126537323 0.99917125701904297 
		0 0;
	setAttr -s 10 ".kox[0:9]"  0.31162926554679871 0.2217649519443512 
		0.23597452044487 1 1 1 0.059284090995788574 0.040703091770410538 1 1;
	setAttr -s 10 ".koy[0:9]"  -0.95020371675491333 -0.97510015964508057 
		-0.97175925970077515 0 0 0 0.998241126537323 0.99917125701904297 0 0;
createNode animCurveTA -n "animCurveTA1016";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 16 0 17 
		0 19 0;
	setAttr -s 10 ".kit[3:9]"  1 10 10 10 10 10 1;
	setAttr -s 10 ".kot[0:9]"  1 10 10 1 10 10 10 10 
		10 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[0:9]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[0:9]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1017";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 16 0 17 
		0 19 0;
	setAttr -s 10 ".kit[3:9]"  1 10 10 10 10 10 1;
	setAttr -s 10 ".kot[0:9]"  1 10 10 1 10 10 10 10 
		10 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[0:9]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[0:9]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1018";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 16 0 17 
		0 19 0;
	setAttr -s 10 ".kit[3:9]"  1 10 10 10 10 10 1;
	setAttr -s 10 ".kot[0:9]"  1 10 10 1 10 10 10 10 
		10 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[0:9]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[0:9]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1019";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -9.982335324211336 2 -9.982335324211336 
		4 -21.165552105865974 9 -21.165552105865974 13 -22.627829899567441 14 -19.181261642216157 
		15 -21.769820234659747 16 -30.247225237797721 17 -38.724641610024975 19 -24.508933374278005;
	setAttr -s 10 ".kit[3:9]"  1 10 1 10 10 1 1;
	setAttr -s 10 ".kot[0:9]"  1 10 10 1 10 1 10 10 
		1 1;
	setAttr -s 10 ".kix[3:9]"  1 1 0.35271993279457092 1 0.21977964043617249 
		0.49800083041191101 0.066666662693023682;
	setAttr -s 10 ".kiy[3:9]"  0 0 0.93572896718978882 0 -0.97554951906204224 
		0.86717653274536133 0.29961159825325012;
	setAttr -s 10 ".kox[0:9]"  1 1 1 1 1 0.35271993279457092 1 0.21977964043617249 
		0.49800056219100952 0.066666662693023682;
	setAttr -s 10 ".koy[0:9]"  0 0 0 0 0 0.93572896718978882 0 -0.97554951906204224 
		0.86717671155929565 0.29961159825325012;
createNode animCurveTA -n "animCurveTA1020";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 15.766648207086439 2 15.766648207086439 
		4 -31.722998759272084 9 -31.722998759272084 13 -8.7432378138669637 14 -4.4877265276808327 
		15 -7.640499509968218 16 -13.157853507915119 17 -16.648428529367283 19 -35.661094456179271;
	setAttr -s 10 ".kit[3:9]"  1 10 1 10 10 1 1;
	setAttr -s 10 ".kot[0:9]"  1 10 10 1 10 1 10 10 
		1 1;
	setAttr -s 10 ".kix[3:9]"  1 0.33087360858917236 1 0.40316870808601379 
		0.39039158821105957 0.26606902480125427 0.066666662693023682;
	setAttr -s 10 ".kiy[3:9]"  0 0.94367510080337524 0 -0.91512566804885864 
		-0.92064893245697021 -0.96395403146743774 -0.34679427742958069;
	setAttr -s 10 ".kox[0:9]"  1 1 1 1 0.33087360858917236 1 0.40316870808601379 
		0.39039158821105957 0.26606899499893188 0.066666662693023682;
	setAttr -s 10 ".koy[0:9]"  0 0 0 0 0.94367510080337524 0 -0.91512566804885864 
		-0.92064893245697021 -0.96395397186279297 -0.34679439663887024;
createNode animCurveTA -n "animCurveTA1021";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -11.890430275710493 2 -11.890430275710493 
		4 -15.172291250691057 9 -29.591812187340803 13 -45.451199064333203 14 -40.37116680621164 
		15 -40.37116680621164 16 -40.37116680621164 17 -40.37116680621164 19 -37.494194471482238;
	setAttr -s 10 ".kit[3:9]"  1 10 10 10 10 1 1;
	setAttr -s 10 ".kot[0:9]"  1 10 10 1 10 10 10 10 
		1 1;
	setAttr -s 10 ".kix[3:9]"  1 0.66310787200927734 1 1 1 1 0.066666662693023682;
	setAttr -s 10 ".kiy[3:9]"  0 -0.74852383136749268 0 0 0 0 0.075318887829780579;
	setAttr -s 10 ".kox[0:9]"  1 1 0.60267919301986694 1 0.66310787200927734 
		1 1 1 1 0.066666662693023682;
	setAttr -s 10 ".koy[0:9]"  0 0 -0.79798352718353271 0 -0.74852383136749268 
		0 0 0 0 0.075318977236747742;
createNode animCurveTA -n "animCurveTA1022";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 13.154882915602682 2 13.154882915602682 
		4 -19.735642011556845 9 -50.290832764122605 13 -35.642699328874905 14 -32.208612983935218 
		15 -32.208612983935218 16 -32.208612983935218 17 -32.208612983935218 19 -36.412759215246886;
	setAttr -s 10 ".kit[3:9]"  1 10 10 10 10 1 1;
	setAttr -s 10 ".kot[0:9]"  1 10 10 1 10 10 10 10 
		1 1;
	setAttr -s 10 ".kix[3:9]"  1 0.46698436141014099 1 1 1 1 0.066666662693023682;
	setAttr -s 10 ".kiy[3:9]"  0 0.88426560163497925 0 0 0 0 -0.11006424576044083;
	setAttr -s 10 ".kox[0:9]"  1 1 0.20618803799152374 1 0.46698436141014099 
		1 1 1 1 0.066666662693023682;
	setAttr -s 10 ".koy[0:9]"  0 0 -0.97851240634918213 0 0.88426560163497925 
		0 0 0 0 -0.11006429046392441;
createNode animCurveTA -n "animCurveTA1023";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -25.378456988571386 2 -54.157692469207241 
		4 -29.42465996773581 9 33.708224287962295 13 -19.915783998753671 14 -43.133493505799684 
		15 -65.946803295731357 16 -79.872309792175145 17 -86.560064018088582 19 -86.560064018088582;
	setAttr -s 10 ".kit[3:9]"  1 10 10 10 10 10 1;
	setAttr -s 10 ".kot[0:9]"  1 10 10 1 10 10 10 10 
		10 3;
	setAttr -s 10 ".kix[3:9]"  1 0.12332364916801453 0.082697160542011261 
		0.10341218858957291 0.18220216035842896 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 -0.9923664927482605 -0.99657469987869263 
		-0.99463862180709839 -0.9832611083984375 0 0;
	setAttr -s 10 ".kox[0:9]"  0.13157100975513458 0.88370203971862793 
		0.15042127668857574 1 0.12332364916801453 0.082697160542011261 0.10341218858957291 
		0.18220216035842896 1 1;
	setAttr -s 10 ".koy[0:9]"  -0.99130678176879883 -0.46804988384246826 
		0.98862200975418091 0 -0.9923664927482605 -0.99657469987869263 -0.99463862180709839 
		-0.9832611083984375 0 0;
createNode animCurveTA -n "animCurveTA1024";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 49.284082676870852 2 15.078622424421384 
		4 13.791694948490491 9 -1.2803820229134193 13 3.1429578497004313 14 2.5192751597744074 
		15 -12.101529984536269 16 -4.2994001870349132 17 3.362244931545689 19 3.362244931545689;
	setAttr -s 10 ".kit[3:9]"  1 10 10 10 10 10 1;
	setAttr -s 10 ".kot[0:9]"  1 10 10 1 10 10 10 10 
		10 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 0.48872625827789307 0.23980332911014557 
		1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 -0.87243711948394775 0.97082144021987915 
		0 0;
	setAttr -s 10 ".kox[0:9]"  0.11098002642393112 1 1 1 1 1 0.48872625827789307 
		0.23980332911014557 1 1;
	setAttr -s 10 ".koy[0:9]"  -0.99382263422012329 0 0 0 0 0 -0.87243711948394775 
		0.97082144021987915 0 0;
createNode animCurveTA -n "animCurveTA1025";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 34.969087097535308 2 46.655633975872433 
		4 9.6207715842079207 9 -93.169034248282415 13 -108.43112079066671 14 -112.09256537644562 
		15 -99.432526289321743 16 -53.721544473653864 17 -22.879383758771784 19 -22.879383758771784;
	setAttr -s 10 ".kit[3:9]"  1 10 10 10 10 10 1;
	setAttr -s 10 ".kot[0:9]"  1 10 10 1 10 10 10 10 
		10 3;
	setAttr -s 10 ".kix[3:9]"  1 0.45051410794258118 0.39073476195335388 
		0.065298974514007568 0.049834299832582474 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 -0.8927692174911499 0.92050337791442871 
		0.99786573648452759 0.99875748157501221 0 0;
	setAttr -s 10 ".kox[0:9]"  0.31067398190498352 0.28855854272842407 
		0.095178648829460144 1 0.45051410794258118 0.39073476195335388 0.065298974514007568 
		0.049834299832582474 1 1;
	setAttr -s 10 ".koy[0:9]"  0.95051652193069458 -0.95746225118637085 
		-0.9954601526260376 0 -0.8927692174911499 0.92050337791442871 0.99786573648452759 
		0.99875748157501221 0 0;
createNode animCurveTA -n "animCurveTA1026";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -4.2353230899544307 2 -29.363922948428606 
		4 -52.837528016549726 9 -88.491362247401582 13 -96.210822707372728 14 -100.1477600169877 
		15 -107.29691857235443 16 -45.302843219292122 17 0 19 0;
	setAttr -s 10 ".kit[3:9]"  1 10 10 10 10 10 1;
	setAttr -s 10 ".kot[0:9]"  1 10 10 1 10 10 10 10 
		10 3;
	setAttr -s 10 ".kix[3:9]"  1 0.63372433185577393 0.32575643062591553 
		0.069477535784244537 0.03557698056101799 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 -0.77355891466140747 -0.9454537034034729 
		0.99758350849151611 0.99936693906784058 0 0;
	setAttr -s 10 ".kox[0:9]"  0.15028055012226105 0.15527649223804474 
		0.22053803503513336 1 0.63372433185577393 0.32575643062591553 0.069477535784244537 
		0.03557698056101799 1 1;
	setAttr -s 10 ".koy[0:9]"  -0.98864340782165527 -0.98787111043930054 
		-0.97537839412689209 0 -0.77355891466140747 -0.9454537034034729 0.99758350849151611 
		0.99936693906784058 0 0;
createNode animCurveTA -n "animCurveTA1027";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 16 0 17 
		0 19 0;
	setAttr -s 10 ".kit[3:9]"  1 10 10 10 10 10 1;
	setAttr -s 10 ".kot[0:9]"  1 10 10 1 10 10 10 10 
		10 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[0:9]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[0:9]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1028";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 16 0 17 
		0 19 0;
	setAttr -s 10 ".kit[3:9]"  1 10 10 10 10 10 1;
	setAttr -s 10 ".kot[0:9]"  1 10 10 1 10 10 10 10 
		10 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[0:9]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[0:9]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1029";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 16 0 17 
		0 19 0;
	setAttr -s 10 ".kit[3:9]"  1 10 10 10 10 10 1;
	setAttr -s 10 ".kot[0:9]"  1 10 10 1 10 10 10 10 
		10 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[0:9]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[0:9]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1030";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 9 7.6768890631514601 13 30.370852836869346 
		14 34.573438720891176 15 19.23400032990557 17 7.6768890631514601 19 7.6768890631514601;
	setAttr -s 8 ".kit[2:7]"  1 10 10 10 10 1;
	setAttr -s 8 ".kot[0:7]"  1 10 1 10 10 10 10 3;
	setAttr -s 8 ".kix[2:7]"  1 0.33457660675048828 0.32442837953567505 
		0.20834793150424957 1 1;
	setAttr -s 8 ".kiy[2:7]"  0 0.94236862659454346 -0.94591027498245239 
		-0.9780547022819519 0 0;
	setAttr -s 8 ".kox[0:7]"  1 1 1 0.33457660675048828 0.32442837953567505 
		0.20834793150424957 1 1;
	setAttr -s 8 ".koy[0:7]"  0 0 0 0.94236862659454346 -0.94591027498245239 
		-0.9780547022819519 0 0;
createNode animCurveTA -n "animCurveTA1031";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 9 0 13 -5.2107554065146173 14 -6.1757101114247321 
		15 -3.0878550557123661 17 0 19 0;
	setAttr -s 8 ".kit[2:7]"  1 10 10 10 10 1;
	setAttr -s 8 ".kot[0:7]"  1 10 1 10 10 10 10 3;
	setAttr -s 8 ".kix[2:7]"  1 1 1 0.68013167381286621 1 1;
	setAttr -s 8 ".kiy[2:7]"  0 0 0 0.73308998346328735 0 0;
	setAttr -s 8 ".kox[0:7]"  1 1 1 1 1 0.68013167381286621 1 1;
	setAttr -s 8 ".koy[0:7]"  0 0 0 0 0 0.73308998346328735 0 0;
createNode animCurveTA -n "animCurveTA1032";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 9 0 13 -7.1372737765107699 14 -8.4589911425312856 
		15 -4.2294955712656437 17 0 19 0;
	setAttr -s 8 ".kit[2:7]"  1 10 10 10 10 1;
	setAttr -s 8 ".kot[0:7]"  1 10 1 10 10 10 10 3;
	setAttr -s 8 ".kix[2:7]"  1 1 1 0.56080073118209839 1 1;
	setAttr -s 8 ".kiy[2:7]"  0 0 0 0.82795083522796631 0 0;
	setAttr -s 8 ".kox[0:7]"  1 1 1 1 1 0.56080073118209839 1 1;
	setAttr -s 8 ".koy[0:7]"  0 0 0 0 0 0.82795083522796631 0 0;
createNode animCurveTA -n "animCurveTA1033";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -14.515820710620677 2 -23.162235351402309 
		9 -38.061951401938721 13 -38.061951401938721 14 -38.061951401938721 15 -38.061951401938721 
		17 -38.061951401938721 19 -38.061951401938721;
	setAttr -s 8 ".kit[2:7]"  1 10 1 10 10 1;
	setAttr -s 8 ".kot[0:7]"  1 10 1 10 1 10 10 3;
	setAttr -s 8 ".kix[2:7]"  1 1 1 1 1 1;
	setAttr -s 8 ".kiy[2:7]"  0 0 0 0 0 0;
	setAttr -s 8 ".kox[0:7]"  0.40409392118453979 0.58961284160614014 
		1 1 1 1 1 1;
	setAttr -s 8 ".koy[0:7]"  -0.91471749544143677 -0.80768603086471558 
		0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1034";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -17.383598210882599 2 1.6788139529320265 
		9 1.6788139529320265 13 1.6788139529320265 14 1.6788139529320265 15 1.6788139529320265 
		17 1.6788139529320265 19 1.6788139529320265;
	setAttr -s 8 ".kit[2:7]"  1 10 1 10 10 1;
	setAttr -s 8 ".kot[0:7]"  1 10 1 10 1 10 10 3;
	setAttr -s 8 ".kix[2:7]"  1 1 1 1 1 1;
	setAttr -s 8 ".kiy[2:7]"  0 0 0 0 0 0;
	setAttr -s 8 ".kox[0:7]"  0.19647401571273804 1 1 1 1 1 1 1;
	setAttr -s 8 ".koy[0:7]"  0.98050904273986816 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1035";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1.5268462968664711 2 -1.2527070794692798 
		9 -1.2527070794692798 13 -1.2527070794692798 14 -1.2527070794692798 15 -1.2527070794692798 
		17 -1.2527070794692798 19 -1.2527070794692798;
	setAttr -s 8 ".kit[2:7]"  1 10 1 10 10 1;
	setAttr -s 8 ".kot[0:7]"  1 10 1 10 1 10 10 3;
	setAttr -s 8 ".kix[2:7]"  1 1 1 1 1 1;
	setAttr -s 8 ".kiy[2:7]"  0 0 0 0 0 0;
	setAttr -s 8 ".kox[0:7]"  1 1 1 1 1 1 1 1;
	setAttr -s 8 ".koy[0:7]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL382";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.00025694328101411035 2 0.00025694328101411035 
		4 0.00025694328101411035 9 0.55821544801624279 13 0.55821544801624279 14 0.55821544801624279 
		19 0.12696153992311984;
	setAttr -s 7 ".kit[3:6]"  1 10 10 1;
	setAttr -s 7 ".kot[0:6]"  1 10 10 1 10 10 3;
	setAttr -s 7 ".kix[3:6]"  1 1 1 1;
	setAttr -s 7 ".kiy[3:6]"  0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL383";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 4 0 9 -0.42448134563417961 13 -0.42448134563417961 
		14 -0.42448134563417961 19 -1.3488613289098041;
	setAttr -s 7 ".kit[3:6]"  1 10 10 1;
	setAttr -s 7 ".kot[0:6]"  1 10 10 1 10 10 3;
	setAttr -s 7 ".kix[3:6]"  1 1 1 1;
	setAttr -s 7 ".kiy[3:6]"  0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL384";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.12527739251666781 2 -0.12527739251666781 
		4 -0.12527739251666781 9 -0.16133533806949696 13 -0.16133533806949696 14 -0.16133533806949696 
		19 -0.16133533806949671;
	setAttr -s 7 ".kit[3:6]"  1 10 10 1;
	setAttr -s 7 ".kot[0:6]"  1 10 10 1 10 10 3;
	setAttr -s 7 ".kix[3:6]"  1 1 1 1;
	setAttr -s 7 ".kiy[3:6]"  0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL385";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.032833691772160223 2 0.032833691772160223 
		4 0.032833691772160223 9 0.032833691772160223 13 0.032833691772160223 14 0.032833691772160223 
		19 -0.39842021632096242;
	setAttr -s 7 ".kit[3:6]"  1 10 10 1;
	setAttr -s 7 ".kot[0:6]"  1 10 10 1 10 10 3;
	setAttr -s 7 ".kix[3:6]"  1 1 1 1;
	setAttr -s 7 ".kiy[3:6]"  0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL386";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.016062985925156426 2 -0.016062985925156426 
		4 -0.016062985925156426 9 -0.016062985925156426 13 -0.016062985925156426 14 -0.016062985925156426 
		19 -0.45525776327682804;
	setAttr -s 7 ".kit[3:6]"  1 10 10 1;
	setAttr -s 7 ".kot[0:6]"  1 10 10 1 10 10 3;
	setAttr -s 7 ".kix[3:6]"  1 1 1 1;
	setAttr -s 7 ".kiy[3:6]"  0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL387";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.11728380015772394 2 0.11728380015772394 
		4 0.11728380015772394 9 0.11728380015772394 13 0.11728380015772394 14 0.11728380015772394 
		19 0.49581852324870124;
	setAttr -s 7 ".kit[3:6]"  1 10 10 1;
	setAttr -s 7 ".kot[0:6]"  1 10 10 1 10 10 3;
	setAttr -s 7 ".kix[3:6]"  1 1 1 1;
	setAttr -s 7 ".kiy[3:6]"  0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1036";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 -0.80960559765347717 9 -2.7309712595805546 
		13 -0.52291559238278951 15 5.3169573556129617 19 8.674464028537864;
	setAttr -s 6 ".kit[0:5]"  10 9 1 1 10 1;
	setAttr -s 6 ".kot[1:5]"  9 1 1 10 9;
	setAttr -s 6 ".kix[2:5]"  1 0.92256730794906616 0.77987003326416016 
		0.97115558385848999;
	setAttr -s 6 ".kiy[2:5]"  0 0.38583636283874512 0.62594151496887207 
		0.2384466826915741;
	setAttr -s 6 ".kox[0:5]"  1 0.98761242628097534 1 0.92256730794906616 
		0.77987003326416016 0.91548484563827515;
	setAttr -s 6 ".koy[0:5]"  0 -0.15691329538822174 0 0.38583630323410034 
		0.62594151496887207 0.40235248208045959;
createNode animCurveTA -n "animCurveTA1037";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 -0.15931450759907628 9 7.1672997541590613 
		13 7.5054595224179295 15 3.1933605983513274 19 -4.5229059631810511;
	setAttr -s 6 ".kit[2:5]"  1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  1 10 1 10 10 9;
	setAttr -s 6 ".kix[2:5]"  0.9968300461769104 1 0.68976783752441406 
		0.79854905605316162;
	setAttr -s 6 ".kiy[2:5]"  0.079560928046703339 0 -0.72403061389923096 
		-0.60192978382110596;
	setAttr -s 6 ".kox[0:5]"  1 1 0.9968300461769104 1 0.68976783752441406 
		0.70356011390686035;
	setAttr -s 6 ".koy[0:5]"  0 0 0.079560913145542145 0 -0.72403061389923096 
		-0.71063578128814697;
createNode animCurveTA -n "animCurveTA1038";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 3.6719125695963681 4 -1.4655618953789071 
		9 -20.576776382717902 13 -10.37567729304981 15 21.467167632801793 19 43.676635254144976;
	setAttr -s 6 ".kit[2:5]"  1 10 9 1;
	setAttr -s 6 ".kot[0:5]"  1 10 1 10 9 9;
	setAttr -s 6 ".kix[2:5]"  1 0.26295986771583557 0.20739187300205231 
		0.37344798445701599;
	setAttr -s 6 ".kiy[2:5]"  0 0.96480673551559448 0.97825795412063599 
		0.92765110731124878;
	setAttr -s 6 ".kox[0:5]"  0.82981187105178833 0.57829916477203369 
		1 0.26295986771583557 0.20739187300205231 0.32526758313179016;
	setAttr -s 6 ".koy[0:5]"  -0.55804336071014404 -0.81582480669021606 
		0 0.96480673551559448 0.97825795412063599 0.9456220269203186;
createNode animCurveTL -n "animCurveTL388";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.0319338039184065 4 -0.0319338039184065 
		9 -0.0319338039184065 13 -0.04081722801093636 15 -0.1018699228873113 17 -0.18893539499689627 
		19 -0.16266857123533301;
	setAttr -s 7 ".kit[2:6]"  1 1 10 10 1;
	setAttr -s 7 ".kot[0:6]"  1 10 1 1 10 10 9;
	setAttr -s 7 ".kix[2:6]"  1 0.99262607097625732 0.66903948783874512 
		1 0.73129141330718994;
	setAttr -s 7 ".kiy[2:6]"  0 -0.12121700495481491 -0.74322682619094849 
		0 0.68206512928009033;
	setAttr -s 7 ".kox[0:6]"  1 1 1 0.99262607097625732 0.66903948783874512 
		1 0.93038833141326904;
	setAttr -s 7 ".koy[0:6]"  0 0 0 -0.12121699750423431 -0.74322682619094849 
		0 0.36657524108886719;
createNode animCurveTL -n "animCurveTL389";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.00078859512199502824 4 0.013021313688540839 
		9 -0.22587442085917966 13 -0.36226094808441084 15 -0.43710457326725904 17 -0.55569705736504305 
		19 -0.65534203362241317;
	setAttr -s 7 ".kit[0:6]"  10 3 9 10 9 9 1;
	setAttr -s 7 ".kot[0:6]"  1 3 9 10 9 9 9;
	setAttr -s 7 ".kix[6]"  0.80102264881134033;
	setAttr -s 7 ".kiy[6]"  -0.59863412380218506;
	setAttr -s 7 ".kox[0:6]"  1 1 0.62440842390060425 0.68754035234451294 
		0.56752842664718628 0.52135318517684937 0.55606615543365479;
	setAttr -s 7 ".koy[0:6]"  0 0 -0.78109794855117798 -0.72614628076553345 
		-0.82335376739501953 -0.85334104299545288 -0.831138014793396;
createNode animCurveTL -n "animCurveTL390";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 0.087638333384540634 9 0.087638333384540634 
		13 0.092665486093646568 15 0.071177565597237077 17 0.048758690895437606 19 0.0056179696155251721;
	setAttr -s 7 ".kit[2:6]"  1 10 9 9 1;
	setAttr -s 7 ".kot[0:6]"  1 10 1 10 9 9 3;
	setAttr -s 7 ".kix[2:6]"  1 1 0.94982600212097168 0.89738768339157104 
		1;
	setAttr -s 7 ".kiy[2:6]"  0 0 -0.31277862191200256 -0.44124284386634827 
		0;
	setAttr -s 7 ".kox[0:6]"  0.83565002679824829 1 1 1 0.94982600212097168 
		0.89738768339157104 1;
	setAttr -s 7 ".koy[0:6]"  0.54926228523254395 0 0 0 -0.31277862191200256 
		-0.44124284386634827 0;
createNode animCurveTA -n "animCurveTA1039";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -16.236770139599834 2 -16.236770139599834 
		4 -22.353791593707186 9 -13.984038542487326 13 -11.247452254811609 15 -16.236770139599834 
		17 -16.236770139599834 19 -16.236770139599834;
	setAttr -s 8 ".kit[3:7]"  9 10 1 1 1;
	setAttr -s 8 ".kot[0:7]"  1 10 10 9 10 1 1 3;
	setAttr -s 8 ".kix[5:7]"  1 1 1;
	setAttr -s 8 ".kiy[5:7]"  0 0 0;
	setAttr -s 8 ".kox[0:7]"  1 1 0.9860985279083252 0.83992171287536621 
		1 1 1 1;
	setAttr -s 8 ".koy[0:7]"  0 0 0.16616147756576538 0.54270756244659424 
		0 0 0 0;
createNode animCurveTA -n "animCurveTA1040";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 3.6982171842001859 9 8.3346354876652864 
		13 -9.7769596257992681 15 0 17 0 19 0;
	setAttr -s 8 ".kit[0:7]"  10 10 10 1 10 1 1 1;
	setAttr -s 8 ".kot[1:7]"  10 10 1 10 1 1 3;
	setAttr -s 8 ".kix[3:7]"  1 0.8087124228477478 1 1 1;
	setAttr -s 8 ".kiy[3:7]"  0 -0.58820420503616333 0 0 0;
	setAttr -s 8 ".kox[0:7]"  1 1 0.84859681129455566 1 0.8087124228477478 
		1 1 1;
	setAttr -s 8 ".koy[0:7]"  0 0 0.52904009819030762 0 -0.58820420503616333 
		0 0 0;
createNode animCurveTA -n "animCurveTA1041";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 58.70026520403372 9 30.20243826253872 
		13 -40.056905319923331 15 0 17 0 19 0;
	setAttr -s 8 ".kit[0:7]"  10 10 3 9 10 1 1 1;
	setAttr -s 8 ".kot[1:7]"  10 3 9 10 1 1 3;
	setAttr -s 8 ".kix[5:7]"  1 1 1;
	setAttr -s 8 ".kiy[5:7]"  0 0 0;
	setAttr -s 8 ".kox[0:7]"  1 1 1 0.17147262394428253 0.35473698377609253 
		1 1 1;
	setAttr -s 8 ".koy[0:7]"  0 0 0 -0.98518890142440796 -0.93496614694595337 
		0 0 0;
createNode animCurveTL -n "animCurveTL391";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -6.0000000000892673e-006 2 -6.0000000000892673e-006 
		4 0.21324977853321433 9 0.34008262052993876 13 0.24814286669627339 15 -6.0000000000892673e-006 
		17 -6.0000000000892673e-006 19 -6.0000000000892673e-006;
	setAttr -s 8 ".kit[0:7]"  10 10 10 1 10 1 1 1;
	setAttr -s 8 ".kot[1:7]"  10 10 1 10 1 1 3;
	setAttr -s 8 ".kix[3:7]"  1 0.50692194700241089 1 1 1;
	setAttr -s 8 ".kiy[3:7]"  0 -0.8619920015335083 0 0 0;
	setAttr -s 8 ".kox[0:7]"  1 1 0.56574231386184692 1 0.50692194700241089 
		1 1 1;
	setAttr -s 8 ".koy[0:7]"  0 0 0.82458215951919556 0 -0.8619920015335083 
		0 0 0;
createNode animCurveTL -n "animCurveTL392";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 2.1809999999936394e-005 2 2.1809999999936394e-005 
		4 -0.024225359171323919 9 -0.33038694917839573 13 -0.69252485408602693 15 -0.75958742906892185 
		17 -0.75958742906892185 19 -0.75958742906892185;
	setAttr -s 8 ".kit[0:7]"  10 10 10 9 9 1 1 1;
	setAttr -s 8 ".kot[1:7]"  10 10 9 9 1 1 3;
	setAttr -s 8 ".kix[5:7]"  1 1 1;
	setAttr -s 8 ".kiy[5:7]"  0 0 0;
	setAttr -s 8 ".kox[0:7]"  1 1 1 0.40953037142753601 0.42237630486488342 
		1 1 1;
	setAttr -s 8 ".koy[0:7]"  0 0 0 -0.91229647397994995 -0.90642064809799194 
		0 0 0;
createNode animCurveTL -n "animCurveTL393";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.040093865534497591 2 -0.040093865534497591 
		4 0.020022972709482965 9 -0.0072711597625078244 13 -0.034965317757624195 15 -0.040093865534497591 
		17 -0.040093865534497591 19 -0.040093865534497591;
	setAttr -s 8 ".kit[0:7]"  10 10 10 9 9 1 1 1;
	setAttr -s 8 ".kot[1:7]"  10 10 9 9 1 1 3;
	setAttr -s 8 ".kix[5:7]"  1 1 1;
	setAttr -s 8 ".kiy[5:7]"  0 0 0;
	setAttr -s 8 ".kox[0:7]"  1 1 1 0.98361337184906006 0.98679941892623901 
		1 1 1;
	setAttr -s 8 ".koy[0:7]"  0 0 0 -0.18029072880744934 -0.16194714605808258 
		0 0 0;
createNode animCurveTA -n "animCurveTA1042";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 25.000774638404387 2 25.000774638404387 
		4 25.000774638404387 9 25.000774638404387 13 25.000774638404387 14 25.000774638404387 
		15 25.000774638404387 17 25.000774638404387 19 25.000774638404387;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1043";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1044";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL394";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL395";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL396";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.038258090963777358 2 0.038258090963777358 
		4 0.038258090963777358 9 0.038258090963777358 13 0.038258090963777358 14 0.038258090963777358 
		15 0.038258090963777358 17 0.038258090963777358 19 0.038258090963777358;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU392";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 4 1 9 1 13 1 14 1 15 1 17 1 19 
		1;
	setAttr -s 9 ".kit[0:8]"  10 9 9 1 9 9 9 9 
		1;
	setAttr -s 9 ".kot[0:8]"  1 5 5 5 5 5 5 5 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 0 0 0 0 0 0 0 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1045";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 19 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1046";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 19 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1047";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 19 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTL -n "animCurveTL397";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.808 19 -0.808;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTL -n "animCurveTL398";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 19 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTL -n "animCurveTL399";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 19 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTU -n "animCurveTU393";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 4 1 9 1 13 1 14 1 15 1 17 1 19 
		1;
	setAttr -s 9 ".kit[0:8]"  10 9 9 1 9 9 9 9 
		1;
	setAttr -s 9 ".kot[0:8]"  1 5 5 5 5 5 5 5 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 0 0 0 0 0 0 0 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1048";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 19 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1049";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 19 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1050";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 19 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTL -n "animCurveTL400";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.80789537837891157 19 -0.80789537837891157;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTL -n "animCurveTL401";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 19 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTL -n "animCurveTL402";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 19 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTU -n "animCurveTU394";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 9 0 13 0 15 0 17 0 19 0;
	setAttr -s 8 ".kit[3:7]"  1 10 1 10 1;
	setAttr -s 8 ".kot[0:7]"  1 10 10 1 10 1 10 3;
	setAttr -s 8 ".kix[3:7]"  1 1 1 1 1;
	setAttr -s 8 ".kiy[3:7]"  0 0 0 0 0;
	setAttr -s 8 ".kox[0:7]"  1 1 1 1 1 1 1 1;
	setAttr -s 8 ".koy[0:7]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU395";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 45 2 45 4 45 9 45 13 45 15 45 17 45 19 
		45;
	setAttr -s 8 ".kit[3:7]"  1 10 1 10 1;
	setAttr -s 8 ".kot[0:7]"  1 10 10 1 10 1 10 3;
	setAttr -s 8 ".kix[3:7]"  1 1 1 1 1;
	setAttr -s 8 ".kiy[3:7]"  0 0 0 0 0;
	setAttr -s 8 ".kox[0:7]"  1 1 1 1 1 1 1 1;
	setAttr -s 8 ".koy[0:7]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU396";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 45 2 45 4 45 9 45 13 45 15 45 17 45 19 
		45;
	setAttr -s 8 ".kit[3:7]"  1 10 1 10 1;
	setAttr -s 8 ".kot[0:7]"  1 10 10 1 10 1 10 3;
	setAttr -s 8 ".kix[3:7]"  1 1 1 1 1;
	setAttr -s 8 ".kiy[3:7]"  0 0 0 0 0;
	setAttr -s 8 ".kox[0:7]"  1 1 1 1 1 1 1 1;
	setAttr -s 8 ".koy[0:7]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU397";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 45 2 45 4 45 9 45 13 45 15 45 17 45 19 
		45;
	setAttr -s 8 ".kit[3:7]"  1 10 1 10 1;
	setAttr -s 8 ".kot[0:7]"  1 10 10 1 10 1 10 3;
	setAttr -s 8 ".kix[3:7]"  1 1 1 1 1;
	setAttr -s 8 ".kiy[3:7]"  0 0 0 0 0;
	setAttr -s 8 ".kox[0:7]"  1 1 1 1 1 1 1 1;
	setAttr -s 8 ".koy[0:7]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1051";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 9 0 13 0 15 0 17 0 19 0;
	setAttr -s 8 ".kit[3:7]"  1 10 1 10 1;
	setAttr -s 8 ".kot[0:7]"  1 10 10 1 10 1 10 3;
	setAttr -s 8 ".kix[3:7]"  1 1 1 1 1;
	setAttr -s 8 ".kiy[3:7]"  0 0 0 0 0;
	setAttr -s 8 ".kox[0:7]"  1 1 1 1 1 1 1 1;
	setAttr -s 8 ".koy[0:7]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1052";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 9 0 13 0 15 0 17 0 19 0;
	setAttr -s 8 ".kit[3:7]"  1 10 1 10 1;
	setAttr -s 8 ".kot[0:7]"  1 10 10 1 10 1 10 3;
	setAttr -s 8 ".kix[3:7]"  1 1 1 1 1;
	setAttr -s 8 ".kiy[3:7]"  0 0 0 0 0;
	setAttr -s 8 ".kox[0:7]"  1 1 1 1 1 1 1 1;
	setAttr -s 8 ".koy[0:7]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU398";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU399";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 45 2 45 4 45 9 45 13 45 14 45 15 72.5 
		17 100 19 100;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 0.0018181785708293319 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0.99999833106994629 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 0.0018181785708293319 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0.99999833106994629 0 0;
createNode animCurveTU -n "animCurveTU400";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 45 2 45 4 45 9 45 13 45 14 45 15 72.5 
		17 100 19 100;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 0.0018181785708293319 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0.99999833106994629 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 0.0018181785708293319 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0.99999833106994629 0 0;
createNode animCurveTU -n "animCurveTU401";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 45 2 45 4 45 9 45 13 45 14 45 15 72.5 
		17 100 19 100;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 0.0018181785708293319 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0.99999833106994629 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 0.0018181785708293319 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0.99999833106994629 0 0;
createNode animCurveTA -n "animCurveTA1053";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1054";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 7.123599037164368 14 
		12.902572357967518 15 26.402239436656117 17 40.138092101233198 19 58.811380424361545;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 0.59489905834197998 0.19435404241085052 
		0.20586542785167694 0.22943080961704254 1;
	setAttr -s 9 ".kiy[3:8]"  0 0.80380046367645264 0.98093140125274658 
		0.97858035564422607 0.97332507371902466 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 0.59489905834197998 0.19435404241085052 
		0.20586542785167694 0.22943080961704254 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0.80380046367645264 0.98093140125274658 
		0.97858035564422607 0.97332507371902466 0;
createNode animCurveTU -n "animCurveTU402";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU403";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU404";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU405";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU406";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU407";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU408";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU409";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU410";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU411";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU412";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 58.052264096385542 2 58.052264096385542 
		4 58.052264096385542 9 58.052264096385542 13 58.052264096385542 14 58.052264096385542 
		15 58.052264096385542 17 58.052264096385542 19 58.052264096385542;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU413";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 39.778629397590358 2 39.778629397590358 
		4 39.778629397590358 9 39.778629397590358 13 39.778629397590358 14 39.778629397590358 
		15 39.778629397590358 17 39.778629397590358 19 39.778629397590358;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1055";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1056";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1057";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU414";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 18 
		0 19 0;
	setAttr -s 10 ".kit[3:9]"  1 10 10 10 10 10 1;
	setAttr -s 10 ".kot[0:9]"  1 10 10 1 10 10 10 10 
		10 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[0:9]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[0:9]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU415";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 18 
		0 19 0;
	setAttr -s 10 ".kit[3:9]"  1 10 10 10 10 10 1;
	setAttr -s 10 ".kot[0:9]"  1 10 10 1 10 10 10 10 
		10 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[0:9]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[0:9]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU416";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU417";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU418";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU419";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU420";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU421";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU422";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU423";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU424";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 58.052264096385542 2 58.052264096385542 
		4 58.052264096385542 9 58.052264096385542 13 58.052264096385542 14 58.052264096385542 
		15 58.052264096385542 17 58.052264096385542 19 58.052264096385542;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU425";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 39.778629397590358 2 39.778629397590358 
		4 39.778629397590358 9 39.778629397590358 13 39.778629397590358 14 39.778629397590358 
		15 39.778629397590358 17 39.778629397590358 18 39.778629397590358 19 39.778629397590358;
	setAttr -s 10 ".kit[3:9]"  1 10 10 10 10 10 1;
	setAttr -s 10 ".kot[0:9]"  1 10 10 1 10 10 10 10 
		10 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[0:9]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[0:9]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1058";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1059";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1060";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 13 0 14 0 15 0 17 0 19 
		0;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1061";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -6.7832614176793165 2 -6.7832614176793165 
		4 -16.999826481061717 9 -12.534324701465648 13 30.66776647297511 17 44.052628309068133 
		19 -27.111347419192967;
	setAttr -s 7 ".kit[3:6]"  1 10 3 1;
	setAttr -s 7 ".kot[0:6]"  1 10 10 1 10 3 9;
	setAttr -s 7 ".kix[3:6]"  0.83661937713623047 0.26067215204238892 
		1 0.066146314144134521;
	setAttr -s 7 ".kiy[3:6]"  0.54778474569320679 0.96542739868164063 
		0 -0.99780994653701782;
	setAttr -s 7 ".kox[0:6]"  1 1 0.918609619140625 0.83661925792694092 
		0.26067215204238892 1 0.053597737103700638;
	setAttr -s 7 ".koy[0:6]"  0 0 -0.39516609907150269 0.54778480529785156 
		0.96542739868164063 0 -0.99856257438659668;
createNode animCurveTA -n "animCurveTA1062";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 4 0.2257736998004273 9 0.1144651490823176 
		13 2.5032600711390147 17 4.1482288133133904 19 -7.2996596641069003;
	setAttr -s 7 ".kit[3:6]"  1 9 10 1;
	setAttr -s 7 ".kot[0:6]"  1 10 10 1 9 10 9;
	setAttr -s 7 ".kix[3:6]"  1 0.96687173843383789 1 0.39535170793533325;
	setAttr -s 7 ".kiy[3:6]"  0 0.2552630603313446 0 -0.91852980852127075;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 0.96687173843383789 1 0.31650781631469727;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0.2552630603313446 0 -0.94858986139297485;
createNode animCurveTA -n "animCurveTA1063";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 4 1.8778199224371714 9 1.4156365771080466 
		13 -3.7015263866841024 17 -2.0897395489686232 19 -1.9927742725502995;
	setAttr -s 7 ".kit[3:6]"  1 10 10 1;
	setAttr -s 7 ".kot[0:6]"  1 10 10 1 10 10 3;
	setAttr -s 7 ".kix[3:6]"  0.99758458137512207 1 1 1;
	setAttr -s 7 ".kiy[3:6]"  -0.069462187588214874 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 0.99758458137512207 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 -0.069462180137634277 0 0 0;
createNode animCurveTA -n "animCurveTA1064";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -17.428736070727251 2 0 4 24.909082766868579 
		9 0 13 -3.8261910537556094 14 -4.5347449525992412 15 -3.0918114428996777 17 0 19 
		8.374385843431325;
	setAttr -s 9 ".kit[3:8]"  1 9 10 9 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 9 10 9 10 
		3;
	setAttr -s 9 ".kix[3:8]"  0.8674238920211792 0.90332037210464478 
		1 0.78412377834320068 0.55446428060531616 1;
	setAttr -s 9 ".kiy[3:8]"  -0.4975699782371521 -0.4289664626121521 
		0 0.62060445547103882 0.83220756053924561 0;
	setAttr -s 9 ".kox[0:8]"  0.2140810489654541 0.17757242918014526 
		1 0.8674236536026001 0.90332037210464478 1 0.78412377834320068 0.55446428060531616 
		1;
	setAttr -s 9 ".koy[0:8]"  0.97681587934494019 0.98410767316818237 
		0 -0.49757030606269836 -0.4289664626121521 0 0.62060445547103882 0.83220756053924561 
		0;
createNode animCurveTA -n "animCurveTA1065";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 -0.70920766056170736 9 0 13 5.4526894680805258 
		14 6.4624467769843275 15 3.2312233884921637 17 0 19 7.6209805915673243;
	setAttr -s 9 ".kit[3:8]"  1 9 10 10 3 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 1 9 10 10 3 
		3;
	setAttr -s 9 ".kix[3:8]"  1 0.82817757129669189 1 0.66340476274490356 
		1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0.56046575307846069 0 -0.7482607364654541 
		0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 0.82817757129669189 1 0.66340476274490356 
		1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0.56046575307846069 0 -0.7482607364654541 
		0 0;
createNode animCurveTA -n "animCurveTA1066";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 -2.5313504883604443 9 0 13 8.3119293859629231 
		14 9.8511755685486477 15 4.9255877842743239 17 0 19 3.3046360458264146;
	setAttr -s 9 ".kit[3:8]"  9 9 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 9 9 10 10 10 
		3;
	setAttr -s 9 ".kix[8]"  1;
	setAttr -s 9 ".kiy[8]"  0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 0.84577226638793945 0.69601958990097046 
		1 0.50276142358779907 0.97822201251983643 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0.53354394435882568 0.71802270412445068 
		0 -0.86442524194717407 -0.20756120979785919 0;
createNode animCurveTL -n "animCurveTL403";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.30197856268412637 1 -0.22130595786678597 
		4 0.57335895591125252 13 0.04839292545355825 17 -0.44086953427281228 19 -0.65550278964705055;
	setAttr -s 6 ".kit[5]"  1;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 3;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[0:5]"  0.38187798857688904 0.15058527886867523 
		0.82913798093795776 0.39289566874504089 0.27331453561782837 1;
	setAttr -s 6 ".koy[0:5]"  0.9242127537727356 0.98859703540802002 
		0.5590440034866333 -0.91958308219909668 -0.96192473173141479 0;
createNode animCurveTL -n "animCurveTL404";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.68322198261048583 1 -0.35481439169594642 
		4 0.012348526903594205 13 -1.5314182984374769 17 -1.6693376161576161 19 -1.7965547040310004;
	setAttr -s 6 ".kit[5]"  1;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 3;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[0:5]"  0.10098106414079666 0.18826156854629517 
		0.32187005877494812 0.2495269775390625 0.60220938920974731 1;
	setAttr -s 6 ".koy[0:5]"  0.99488836526870728 0.98211896419525146 
		-0.94678384065628052 -0.9683678150177002 -0.79833823442459106 0;
createNode animCurveTL -n "animCurveTL405";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.0013196526438615797 1 -0.041294726046990554 
		4 -0.15482265241329513 13 -0.51316930157761109 17 -0.22319954535543235 19 -0.27735575849389105;
	setAttr -s 6 ".kit[5]"  1;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 3;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[0:5]"  1 1 0.6466217041015625 0.98777848482131958 
		0.64681905508041382 1;
	setAttr -s 6 ".koy[0:5]"  0 0 -0.76281088590621948 -0.15586435794830322 
		0.76264345645904541 0;
createNode animCurveTL -n "animCurveTL406";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.26875866938298265 4 0.58764974161526384 
		13 0 17 -0.47688216952798673 19 -0.60037952008017448;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[0:4]"  1 10 10 10 3;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[0:4]"  0.1538357138633728 0.84982186555862427 
		0.37702462077140808 0.31604781746864319 1;
	setAttr -s 5 ".koy[0:4]"  0.98809647560119629 0.52706998586654663 
		-0.92620325088500977 -0.94874322414398193 0;
createNode animCurveTL -n "animCurveTL407";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.73360091157126917 4 0.04991981062998839 
		13 -1.5540321667292381 17 -1.6958552604709236 19 -1.719394618044551;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[0:4]"  1 10 10 10 3;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[0:4]"  0.16776035726070404 0.46703505516052246 
		0.24090777337551117 1 1;
	setAttr -s 5 ".koy[0:4]"  0.98582780361175537 -0.8842388391494751 
		-0.97054797410964966 0 0;
createNode animCurveTL -n "animCurveTL408";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.040161846088425823 4 0.38097989983734271 
		13 0.80736905595509734 17 0.541457846918449 19 0.34903396825791139;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[0:4]"  1 10 10 10 3;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[0:4]"  0.36432766914367676 0.49179446697235107 
		0.93775999546051025 0.39994317293167114 1;
	setAttr -s 5 ".koy[0:4]"  0.9312707781791687 0.87071132659912109 
		0.34728413820266724 -0.91653996706008911 0;
createNode animCurveTA -n "animCurveTA1067";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -35.593511076504186 2 -79.439921922319215 
		4 -86.558281355676812 7 -78.19593401555133 9 -32.280894985739643 12 -84.460783041698249 
		15 -92.867921066337232 16 -106.34271341727923 17 -64.26136775247933 18 -71.693805108965108 
		19 -75.884720883249514;
	setAttr -s 11 ".kit[4:10]"  3 10 10 10 10 10 1;
	setAttr -s 11 ".kot[0:10]"  1 10 10 10 3 10 10 10 
		10 10 3;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[0:10]"  0.25374695658683777 0.14824029803276062 
		0.99162137508392334 0.17327384650707245 1 0.18584069609642029 0.3296109139919281 
		0.132351353764534 0.10957682132720947 0.31219875812530518 1;
	setAttr -s 11 ".koy[0:10]"  -0.9672706127166748 -0.98895132541656494 
		0.12917864322662354 0.98487371206283569 0 -0.98257982730865479 -0.94411683082580566 
		0.99120289087295532 0.99397838115692139 -0.95001673698425293 0;
createNode animCurveTA -n "animCurveTA1068";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 50.202913109388724 2 26.166073363995501 
		4 -8.4490950972543111 7 -43.587449336832734 9 -95.708894485969225 12 -125.56893359151269 
		15 -139.9498229886197 16 -108.66205381527826 17 -59.500392933090431 18 -13.247027141487207 
		19 -0.85132876050393891;
	setAttr -s 11 ".kit[10]"  1;
	setAttr -s 11 ".kot[0:10]"  1 10 10 10 10 10 10 10 
		10 10 3;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[0:10]"  0.10607957094907761 0.12915924191474915 
		0.13563543558120728 0.10878575593233109 0.11569888889789581 0.25074246525764465 0.41176909208297729 
		0.047426313161849976 0.040000632405281067 0.064990684390068054 1;
	setAttr -s 11 ".koy[0:10]"  -0.9943576455116272 -0.99162387847900391 
		-0.99075883626937866 -0.99406522512435913 -0.99328434467315674 -0.96805381774902344 
		0.91128826141357422 0.9988747239112854 0.99919968843460083 0.99788588285446167 0;
createNode animCurveTA -n "animCurveTA1069";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 23.417793060771654 2 11.020706227623526 
		4 24.20412875245173 7 -12.175288886111817 9 -134.16676192466963 12 -93.744203875427445 
		15 -75.135098796385876 16 -60.286925230525171 17 -97.800076293608981 18 -87.657627225555089 
		19 -90.211546298012578;
	setAttr -s 11 ".kit[2:10]"  1 10 1 10 10 10 10 10 
		1;
	setAttr -s 11 ".kot[0:10]"  1 10 1 10 1 10 10 10 
		10 10 3;
	setAttr -s 11 ".kix[2:10]"  0.33374315500259399 0.060187734663486481 
		0.34559741616249084 0.19056160748004913 0.22260494530200958 0.16618603467941284 0.138215571641922 
		1 1;
	setAttr -s 11 ".kiy[2:10]"  -0.94266408681869507 -0.99818706512451172 
		-0.93838286399841309 0.98167526721954346 0.97490870952606201 -0.98609441518783569 
		-0.9904022216796875 0 0;
	setAttr -s 11 ".kox[0:10]"  0.74144381284713745 0.99474430084228516 
		0.33374303579330444 0.060187734663486481 0.34559741616249084 0.19056160748004913 
		0.22260494530200958 0.16618603467941284 0.138215571641922 1 1;
	setAttr -s 11 ".koy[0:10]"  -0.67101490497589111 0.1023901179432869 
		-0.94266414642333984 -0.99818706512451172 -0.93838286399841309 0.98167526721954346 
		0.97490870952606201 -0.98609441518783569 -0.9904022216796875 0 0;
createNode animCurveTL -n "animCurveTL409";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.48200086220201055 2 -0.26697644677050297 
		4 0.16425683545873523 9 0.42917936829307041 15 0.18246763093258717 17 -0.0072291511895273093 
		18 -0.19161331928804876 19 -0.37963001886474468;
	setAttr -s 8 ".kit[7]"  1;
	setAttr -s 8 ".kot[0:7]"  1 10 10 10 10 10 10 9;
	setAttr -s 8 ".kix[7]"  0.25413215160369873;
	setAttr -s 8 ".kiy[7]"  -0.96716952323913574;
	setAttr -s 8 ".kox[0:7]"  0.29613566398620605 0.20206038653850555 
		0.31779807806015015 0.99876886606216431 0.52141094207763672 0.25825357437133789 0.17621715366840363 
		0.1745668351650238;
	setAttr -s 8 ".koy[0:7]"  0.95514589548110962 0.97937303781509399 
		0.94815844297409058 0.049604661762714386 -0.85330569744110107 -0.96607720851898193 
		-0.98435133695602417 -0.9846453070640564;
createNode animCurveTL -n "animCurveTL410";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.25008211660802959 4 -0.38265638396305307 
		9 -0.14917501192357885 12 -0.12927183174833426 15 -0.42463100212004101 18 -1.4757368182421902 
		19 -1.75414863959071;
	setAttr -s 7 ".kit[6]"  1;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 3;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[0:6]"  0.70912247896194458 0.94782000780105591 
		1 1 0.14692513644695282 0.099786445498466492 1;
	setAttr -s 7 ".koy[0:6]"  -0.70508533716201782 0.31880590319633484 
		0 0 -0.9891476035118103 -0.99500882625579834 0;
createNode animCurveTL -n "animCurveTL411";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.23878132695572496 2 -0.17365974227320316 
		4 -0.14501136157667557 9 -0.19503314545761738 15 -0.20813714949803289 17 -0.23130589026584111 
		18 -0.34649528586823364 19 -0.40653640287433251;
	setAttr -s 8 ".kit[3:7]"  9 9 9 10 1;
	setAttr -s 8 ".kot[0:7]"  1 10 10 9 9 9 10 3;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[0:7]"  0.71534770727157593 1 1 0.98550176620483398 
		0.99087536334991455 0.58577811717987061 0.35558626055717468 1;
	setAttr -s 8 ".koy[0:7]"  0.69876861572265625 0 0 -0.16966520249843597 
		-0.13478164374828339 -0.81047147512435913 -0.93464350700378418 0;
createNode animCurveTA -n "animCurveTA1070";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 43.148863408286189 4 72.487108173187949 
		6 85.212133752284231 9 119.84114231786459 15 92.124013418304784 16 303.34430882716231 
		17 30.894759262856624 18 89.012161913576534 19 77.660502903164783;
	setAttr -s 9 ".kit[3:8]"  3 10 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 3 10 10 10 10 
		3;
	setAttr -s 9 ".kix[8]"  1;
	setAttr -s 9 ".kiy[8]"  0;
	setAttr -s 9 ".kox[0:8]"  0.33300438523292542 0.2628474235534668 
		0.19767819344997406 1 0.072661839425563812 0.062262840569019318 0.017818661406636238 
		0.081406600773334503 1;
	setAttr -s 9 ".koy[0:8]"  0.94292533397674561 0.96483737230300903 
		0.9802669882774353 0 0.99735665321350098 -0.99805974960327148 -0.99984127283096313 
		0.99668091535568237 0;
createNode animCurveTA -n "animCurveTA1071";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -39.634719780710149 4 -16.630365965903028 
		6 3.250039089670107 9 108.27378279974404 14 141.86008030126524 15 136.9372778588336 
		16 60.000885436125564 17 43.31862136414307 18 23.543369256824533 19 -5.0031331528127048;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 1 10 1;
	setAttr -s 10 ".kot[0:9]"  1 10 10 1 1 10 10 1 
		10 1;
	setAttr -s 10 ".kix[3:9]"  0.11866876482963562 0.1666666567325592 
		0.046611357480287552 0.040766909718513489 0.15944664180278778 0.078801780939102173 
		0.10239445418119431;
	setAttr -s 10 ".kiy[3:9]"  0.99293392896652222 -1.1523473262786865 
		-0.99891304969787598 -0.99916869401931763 -0.98720651865005493 -0.99689030647277832 
		-0.99474388360977173;
	setAttr -s 10 ".kox[0:9]"  0.079235352575778961 0.25815099477767944 
		0.076230540871620178 0.11866877228021622 0.099999994039535522 0.046611357480287552 
		0.040766909718513489 0.15944646298885345 0.078801780939102173 0.10239505022764206;
	setAttr -s 10 ".koy[0:9]"  0.99685591459274292 0.96610456705093384 
		0.99709022045135498 0.99293392896652222 -0.69140833616256714 -0.99891304969787598 
		-0.99916869401931763 -0.98720657825469971 -0.99689030647277832 -0.99474382400512695;
createNode animCurveTA -n "animCurveTA1072";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 329.74227729815868 4 341.85055498442239 
		6 329.51743039333468 9 304.36371733449522 15 281.27402103733721 16 488.60760215721592 
		17 248.25545144899547 18 268.27063584644048 19 271.37856583619362;
	setAttr -s 9 ".kit[1:8]"  9 10 9 9 10 10 10 1;
	setAttr -s 9 ".kot[0:8]"  1 9 10 9 9 10 10 10 
		3;
	setAttr -s 9 ".kix[8]"  1;
	setAttr -s 9 ".kiy[8]"  0;
	setAttr -s 9 ".kox[0:8]"  0.51429581642150879 0.99980753660202026 
		0.24685390293598175 0.33562538027763367 0.072371244430541992 0.11491753906011581 
		0.017333200201392174 0.16298173367977142 1;
	setAttr -s 9 ".koy[0:8]"  0.85761290788650513 -0.019617816433310509 
		-0.96905273199081421 -0.94199556112289429 0.99737775325775146 -0.99337506294250488 
		-0.99984979629516602 0.98662906885147095 0;
createNode animCurveTL -n "animCurveTL412";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.42664090322610937 2 -0.26001994003651996 
		4 0.11967824807728916 9 0.43146423828501718 12 0.30798883544075528 15 0.18247134926693498 
		17 -0.045507264518843772 19 -0.41978686599871862;
	setAttr -s 8 ".kit[2:7]"  1 3 10 10 1 1;
	setAttr -s 8 ".kot[0:7]"  1 10 1 3 10 10 1 9;
	setAttr -s 8 ".kix[2:7]"  0.41477480530738831 1 0.6262320876121521 
		0.4264579713344574 0.30731511116027832 0.22817762196063995;
	setAttr -s 8 ".kiy[2:7]"  0.90992414951324463 0 -0.7796366810798645 
		-0.90450739860534668 -0.95160782337188721 -0.97361958026885986;
	setAttr -s 8 ".kox[0:7]"  0.37147846817970276 0.23709842562675476 
		0.41477474570274353 1 0.6262320876121521 0.4264579713344574 0.30731505155563354 0.17535987496376038;
	setAttr -s 8 ".koy[0:7]"  0.92844152450561523 0.97148555517196655 
		0.90992414951324463 0 -0.7796366810798645 -0.90450739860534668 -0.95160776376724243 
		-0.98450440168380737;
createNode animCurveTL -n "animCurveTL413";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.24895072040176086 4 -0.38470994386844171 
		9 -0.13508511135484103 12 -0.10504995795010565 15 -0.41926347303355471 17 -1.1419568550756349 
		18 -1.4712029366379178 19 -1.747587159617044;
	setAttr -s 8 ".kit[0:7]"  10 3 9 9 9 10 10 1;
	setAttr -s 8 ".kot[0:7]"  1 3 9 9 9 10 10 9;
	setAttr -s 8 ".kix[7]"  0.19460940361022949;
	setAttr -s 8 ".kiy[7]"  -0.98088085651397705;
	setAttr -s 8 ".kox[0:7]"  0.70070368051528931 1 0.6900944709777832 
		0.57553696632385254 0.15869750082492828 0.09463588148355484 0.10941722244024277 0.11973724514245987;
	setAttr -s 8 ".koy[0:7]"  -0.71345239877700806 0 0.72371929883956909 
		-0.81777578592300415 -0.98732727766036987 -0.99551194906234741 -0.99399590492248535 
		-0.9928056001663208;
createNode animCurveTL -n "animCurveTL414";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.20572056125233662 2 0.27490200155120731 
		4 0.3282062330126963 9 0.4994430462413057 12 0.50631541432884086 15 0.43718748082144088 
		17 0.27838241436578054 18 0.37345881676812764 19 0.45475842170572756;
	setAttr -s 9 ".kit[3:8]"  9 9 9 3 10 1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 9 9 9 3 10 
		3;
	setAttr -s 9 ".kix[8]"  0.84445041418075562;
	setAttr -s 9 ".kiy[8]"  0.53563386201858521;
	setAttr -s 9 ".kox[0:8]"  0.69389820098876953 0.73642891645431519 
		0.72055214643478394 0.83157306909561157 0.95481157302856445 0.5902479887008667 1 
		0.35356634855270386 1;
	setAttr -s 9 ".koy[0:8]"  0.72007310390472412 0.67651486396789551 
		0.6934008002281189 0.55541551113128662 -0.29721167683601379 -0.80722200870513916 
		0 0.93540942668914795 0;
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
connectAttr "ability4_1StartSource2.cl" "clipLibrary2.sc[0]";
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
connectAttr "animCurveTL403.a" "clipLibrary2.cel[0].cev[148].cevr";
connectAttr "animCurveTL404.a" "clipLibrary2.cel[0].cev[149].cevr";
connectAttr "animCurveTL405.a" "clipLibrary2.cel[0].cev[150].cevr";
connectAttr "animCurveTL406.a" "clipLibrary2.cel[0].cev[151].cevr";
connectAttr "animCurveTL407.a" "clipLibrary2.cel[0].cev[152].cevr";
connectAttr "animCurveTL408.a" "clipLibrary2.cel[0].cev[153].cevr";
connectAttr "animCurveTA1067.a" "clipLibrary2.cel[0].cev[154].cevr";
connectAttr "animCurveTA1068.a" "clipLibrary2.cel[0].cev[155].cevr";
connectAttr "animCurveTA1069.a" "clipLibrary2.cel[0].cev[156].cevr";
connectAttr "animCurveTL409.a" "clipLibrary2.cel[0].cev[157].cevr";
connectAttr "animCurveTL410.a" "clipLibrary2.cel[0].cev[158].cevr";
connectAttr "animCurveTL411.a" "clipLibrary2.cel[0].cev[159].cevr";
connectAttr "animCurveTA1070.a" "clipLibrary2.cel[0].cev[160].cevr";
connectAttr "animCurveTA1071.a" "clipLibrary2.cel[0].cev[161].cevr";
connectAttr "animCurveTA1072.a" "clipLibrary2.cel[0].cev[162].cevr";
connectAttr "animCurveTL412.a" "clipLibrary2.cel[0].cev[163].cevr";
connectAttr "animCurveTL413.a" "clipLibrary2.cel[0].cev[164].cevr";
connectAttr "animCurveTL414.a" "clipLibrary2.cel[0].cev[165].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of ability4ThrowA.ma
