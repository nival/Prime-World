//Maya ASCII 2008 scene
//Name: attackE.ma
//Last modified: Fri, Oct 09, 2009 11:28:24 AM
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
createNode animClip -n "attackESource";
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
createNode animCurveTU -n "animCurveTU109";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[1:3]"  10 3 9;
	setAttr -s 4 ".kot[1:3]"  10 3 9;
createNode animCurveTU -n "animCurveTU110";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[0:3]"  9 10 10 9;
	setAttr -s 4 ".kot[0:3]"  9 10 10 9;
createNode animCurveTA -n "animCurveTA166";
	setAttr ".tan" 10;
	setAttr -s 13 ".ktv[0:12]"  1 39.53428110495291 2 58.728131262473468 
		3 52.825773890752984 4 38.483218487789543 5 -22.055828083069059 6 -77.345348193139969 
		7 -71.661726084942671 10 -55.693203822255541 14 -60.911818981493646 17 -66.485107482857941 
		25 -59.381520922853987 36 26.310881873129244 45 39.53428110495291;
	setAttr -s 13 ".kit[0:12]"  9 10 10 10 10 3 10 3 
		10 10 10 10 9;
	setAttr -s 13 ".kot[0:12]"  9 10 10 10 10 3 10 3 
		10 10 10 10 9;
createNode animCurveTA -n "animCurveTA167";
	setAttr ".tan" 10;
	setAttr -s 13 ".ktv[0:12]"  1 32.600909957006799 2 9.6717374121956308 
		3 -21.221187555177462 4 -42.200409090848382 5 -41.889074438889843 6 27.514152951249585 
		7 8.9885347883586917 10 -22.8995887912386 14 -10.240854784654587 17 7.8625863346635283 
		25 32.311652404299004 36 2.7646903713291433 45 32.600909957006799;
	setAttr -s 13 ".kit[0:12]"  9 10 10 10 10 9 10 3 
		10 10 10 10 9;
	setAttr -s 13 ".kot[0:12]"  9 10 10 10 10 9 10 3 
		10 10 10 10 9;
createNode animCurveTA -n "animCurveTA168";
	setAttr ".tan" 10;
	setAttr -s 13 ".ktv[0:12]"  1 16.651520328974982 2 -16.842870042265265 
		3 -53.706729338278869 4 -39.685217363498751 5 28.028200264659095 6 48.798137773550145 
		7 65.762242373468098 10 71.111417071529189 14 65.769080871055991 17 57.841252165991065 
		25 27.080525362682089 36 11.078046812533323 45 16.651520328974982;
	setAttr -s 13 ".kit[0:12]"  9 10 10 10 10 9 10 3 
		10 10 10 10 9;
	setAttr -s 13 ".kot[0:12]"  9 10 10 10 10 9 10 3 
		10 10 10 10 9;
createNode animCurveTA -n "animCurveTA169";
	setAttr ".tan" 10;
	setAttr -s 14 ".ktv[0:13]"  1 -87.582586884797436 2 -45.221091940950046 
		3 -43.968415300591516 6 -37.490648278754307 7 -62.388353709634586 8 -81.514109313674126 
		9 -95.928698368378036 10 -102.00507240345416 14 -89.26195101134509 17 -68.541473252793949 
		25 -38.50417639045066 30 -26.641610385494335 36 -51.858605364168227 45 -87.582586884797436;
	setAttr -s 14 ".kit[0:13]"  9 10 10 10 10 10 10 3 
		10 10 10 9 10 9;
	setAttr -s 14 ".kot[0:13]"  9 10 10 10 10 10 10 3 
		10 10 10 9 10 9;
createNode animCurveTA -n "animCurveTA170";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "animCurveTA171";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "animCurveTA172";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "animCurveTA173";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  1 -0.90666238496249552 3 12.783374807276051 
		5 2.3487574806392608 6 2.1131738394730939 10 -17.583488169348524 25 -25.473693206032546 
		45 -0.90666238496249552;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 3 10 9;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 3 10 9;
createNode animCurveTA -n "animCurveTA174";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  1 -0.14300750254877909 3 -24.499570975942426 
		5 -27.376358583806262 6 -0.21157390776037555 10 -22.050362135035503 25 -0.70778091995040393 
		31 12.555158987468511 36 -0.76649469222012556 45 -0.14300750254877909;
	setAttr -s 9 ".kit[0:8]"  9 10 10 10 3 10 10 10 
		9;
	setAttr -s 9 ".kot[0:8]"  9 10 10 10 3 10 10 10 
		9;
createNode animCurveTA -n "animCurveTA175";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  1 -0.69869282260852494 3 -0.69869282260852494 
		6 -0.69869282260852494 10 -20.854848717979166 20 5.0021747134189285 27 -18.700229073937479 
		33 -11.813415544505094 38 -6.942453126636166 45 -0.69869282260852494;
	setAttr -s 9 ".kit[0:8]"  3 10 10 1 10 10 10 9 
		9;
	setAttr -s 9 ".kot[0:8]"  3 10 10 1 10 10 10 9 
		9;
	setAttr -s 9 ".kix[3:8]"  0.1376674622297287 0.3333333432674408 0.2333332896232605 
		0.20000004768371582 0.16666662693023682 0.23333334922790527;
	setAttr -s 9 ".kiy[3:8]"  -0.0040065390057861805 0.022120712324976921 
		-0.1580316573381424 0.11193379014730453 0.080828532576560974 0.10897417366504669;
	setAttr -s 9 ".kox[3:8]"  0.33766824007034302 0.2333332896232605 
		0.20000004768371582 0.16666662693023682 0.23333334922790527 0.23333334922790527;
	setAttr -s 9 ".koy[3:8]"  -0.0098271556198596954 0.015484496019780636 
		-0.13545575737953186 0.093278110027313232 0.11315997689962387 0.10897417366504669;
createNode animCurveTA -n "animCurveTA176";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  1 13.566397626420638 3 13.566397626420638 
		6 13.566397626420638 10 -6.6795020076653921 20 -8.8108735967505929 27 14.872417183762135 
		33 20.25981402063195 38 8.4128033231446917 45 13.566397626420638;
	setAttr -s 9 ".kit[0:8]"  3 10 10 1 10 10 10 9 
		9;
	setAttr -s 9 ".kot[0:8]"  3 10 10 1 10 10 10 9 
		9;
	setAttr -s 9 ".kix[3:8]"  0.17966414988040924 0.3333333432674408 
		0.2333332896232605 0.20000004768371582 0.16666662693023682 0.23333334922790527;
	setAttr -s 9 ".kiy[3:8]"  -0.069459177553653717 0 0.27320414781570435 
		-0.061495393514633179 -0.048675887286663055 0.089947186410427094;
	setAttr -s 9 ".kox[3:8]"  0.37967404723167419 0.2333332896232605 
		0.20000004768371582 0.16666662693023682 0.23333334922790527 0.23333334922790527;
	setAttr -s 9 ".koy[3:8]"  -0.14678399264812469 0 0.23417507112026215 
		-0.051246136426925659 -0.068146266043186188 0.089947186410427094;
createNode animCurveTA -n "animCurveTA177";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  1 -14.474463091487671 3 -41.683457287081623 
		6 37.651406296786078 10 46.17263477124142 20 49.569436869949328 27 5.0550716428992724 
		31 -28.658456540272471 38 -21.029357508005212 45 -14.474463091487671;
	setAttr -s 9 ".kit[0:8]"  9 10 10 10 10 10 10 9 
		9;
	setAttr -s 9 ".kot[0:8]"  9 10 10 10 10 10 10 9 
		9;
createNode animCurveTA -n "animCurveTA178";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  1 28.826393195295356 3 16.584331763190285 
		6 14.438552663509697 10 -5.0527712439631873 20 -13.149898859596918 27 39.900500190444731 
		31 37.615786236744555 38 13.665454061343398 45 28.826393195295356;
	setAttr -s 9 ".kit[0:8]"  9 10 10 10 10 10 10 9 
		9;
	setAttr -s 9 ".kot[0:8]"  9 10 10 10 10 10 10 9 
		9;
createNode animCurveTA -n "animCurveTA179";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  1 4.3502300737951041 3 -11.396937926071015 
		6 52.293346628048141 10 62.062091446064159 20 63.002856360121896 27 24.245331272394406 
		31 -7.7802452372915853 38 -2.8951165210140659 45 4.3502300737951041;
	setAttr -s 9 ".kit[0:8]"  9 10 10 10 10 10 10 9 
		9;
	setAttr -s 9 ".kot[0:8]"  9 10 10 10 10 10 10 9 
		9;
createNode animCurveTA -n "animCurveTA180";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  1 -59.684677024606373 3 -59.684677024606373 
		6 -48.412559564556943 10 -8.1275878781935553 20 -8.1275878781935553 45 -59.684677024606373;
	setAttr -s 6 ".kit[0:5]"  9 10 10 10 10 1;
	setAttr -s 6 ".kot[0:5]"  9 10 10 10 10 1;
	setAttr -s 6 ".kix[5]"  0.066666662693023682;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  0.066666662693023682;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTA -n "animCurveTA181";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "animCurveTA182";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "animCurveTA183";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "animCurveTA184";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  1 -0.19158875421948376 3 11.066520076989239 
		6 -16.601583354969737 10 -9.7438904724175295 25 -11.729901189816623 45 -0.19158875421948376;
	setAttr -s 6 ".kit[0:5]"  2 10 10 3 9 1;
	setAttr -s 6 ".kot[0:5]"  2 10 10 3 9 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  0.066666662693023682;
	setAttr -s 6 ".koy[5]"  0.1964910626411438;
createNode animCurveTA -n "animCurveTA185";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  1 -7.898767459478834 3 -12.04484172400084 
		6 27.091621037126924 10 52.095917628718482 25 20.457903963919261 45 -7.898767459478834;
	setAttr -s 6 ".kit[0:5]"  2 10 10 3 9 1;
	setAttr -s 6 ".kot[0:5]"  2 10 10 3 9 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  0.066666662693023682;
	setAttr -s 6 ".koy[5]"  -0.072362646460533142;
createNode animCurveTA -n "animCurveTA186";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  1 2.3461370896484395 3 -3.1108642900164498 
		6 1.9294237117746578 10 16.293621152611458 25 3.5300400572293582 45 2.3461370896484395;
	setAttr -s 6 ".kit[0:5]"  2 10 10 3 9 1;
	setAttr -s 6 ".kot[0:5]"  2 10 10 3 9 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  0.066666662693023682;
	setAttr -s 6 ".koy[5]"  -0.095242641866207123;
createNode animCurveTA -n "animCurveTA187";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 1.4245112294344 3 5.5153155732439894 
		6 1.5632905783433915 10 -9.3555952827914926 45 1.4245112294344;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.066666662693023682;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA188";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 1.8864606807611757 3 0.6061593701259903 
		6 -3.3104148757632887 10 -3.7673688541568664 45 1.8864606807611757;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.066666662693023682;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA189";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 -5.9921097590926697 3 -6.6764360772011022 
		6 1.936824070515778 10 8.7377969110256792 45 -5.9921097590926697;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.066666662693023682;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL64";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 -0.26127236006231064 45 0;
	setAttr -s 4 ".kit[0:3]"  2 10 10 1;
	setAttr -s 4 ".kot[0:3]"  2 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  0.066666662693023682;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTL -n "animCurveTL65";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[0:3]"  3 10 10 1;
	setAttr -s 4 ".kot[0:3]"  3 10 10 1;
	setAttr -s 4 ".kix[3]"  0.066666662693023682;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  0.066666662693023682;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTL -n "animCurveTL66";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  1 -0.12272155611893799 3 -0.20071035765146222 
		10 -0.12272155611893799 45 -0.12272155611893799;
	setAttr -s 4 ".kit[0:3]"  9 10 10 1;
	setAttr -s 4 ".kot[0:3]"  9 10 10 1;
	setAttr -s 4 ".kix[3]"  0.066666662693023682;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  0.066666662693023682;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTL -n "animCurveTL67";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  1 0.033 3 0.033 10 0.033 45 0.033;
	setAttr -s 4 ".kit[0:3]"  9 10 10 1;
	setAttr -s 4 ".kot[0:3]"  9 10 10 1;
	setAttr -s 4 ".kix[3]"  0.066666662693023682;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  0.066666662693023682;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTL -n "animCurveTL68";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  1 -0.016 3 -0.20257666148407488 10 -0.20257666148407488 
		45 -0.016;
	setAttr -s 4 ".kit[0:3]"  9 10 10 1;
	setAttr -s 4 ".kot[0:3]"  9 10 10 1;
	setAttr -s 4 ".kix[3]"  0.066666662693023682;
	setAttr -s 4 ".kiy[3]"  -0.18657666444778442;
	setAttr -s 4 ".kox[3]"  0.066666662693023682;
	setAttr -s 4 ".koy[3]"  -0.18657666444778442;
createNode animCurveTL -n "animCurveTL69";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 0.10379921435641129 3 -0.072836215140426777 
		10 -0.072836215140426777 36 -0.015107708971127518 45 0.10379921435641129;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.066666662693023682;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA190";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  1 -18.178217858042064 3 -34.660116069009554 
		6 33.98166221728264 10 27.833844971659964 25 -4.7797710217196236 36 -22.56395424126854 
		45 -18.178217858042064;
	setAttr -s 7 ".kit[0:6]"  1 10 3 3 10 10 1;
	setAttr -s 7 ".kot[0:6]"  1 10 3 3 10 10 1;
	setAttr -s 7 ".kix[0:6]"  0.066523261368274689 0.066666662693023682 
		0.10000000149011612 0.13333334028720856 0.49999997019767761 0.36666673421859741 0.066523261368274689;
	setAttr -s 7 ".kiy[0:6]"  0.0579969622194767 0.36414462327957153 
		0 0 -0.50746583938598633 -0.12861587107181549 0.0579969622194767;
	setAttr -s 7 ".kox[0:6]"  0.066523268818855286 0.10000000149011612 
		0.13333334028720856 0.49999997019767761 0.36666673421859741 0.29999995231628418 0.066523268818855286;
	setAttr -s 7 ".koy[0:6]"  0.057996965944766998 0.54621696472167969 
		0 0 -0.37214171886444092 -0.10523113608360291 0.057996965944766998;
createNode animCurveTA -n "animCurveTA191";
	setAttr ".tan" 3;
	setAttr -s 7 ".ktv[0:6]"  1 -4.6186256351197352 3 -10.039413731040542 
		6 -14.666019726273879 10 -9.771744428911493 25 0.99907436710188668 36 -14.64269146433756 
		45 -4.6186256351197352;
	setAttr -s 7 ".kit[1:6]"  10 3 3 10 10 1;
	setAttr -s 7 ".kot[1:6]"  10 3 3 10 10 1;
	setAttr -s 7 ".kix[6]"  0.066666662693023682;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  0.066666662693023682;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "animCurveTA192";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  1 -7.7006231053605507 3 -3.0742777908563528 
		6 19.659692365727857 10 28.288459548030382 25 0.74689830029215076 36 -7.7959159059989718 
		45 -7.7006231053605507;
	setAttr -s 7 ".kit[0:6]"  3 10 9 3 10 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 9 3 10 10 1;
	setAttr -s 7 ".kix[6]"  0.066666662693023682;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  0.066666662693023682;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTL -n "animCurveTL70";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  1 -0.062545592999319929 3 -0.097157704334261547 
		6 -0.18210900190778237 10 -0.20424325759375384 45 -0.062545592999319929;
	setAttr -s 5 ".kit[1:4]"  10 9 3 1;
	setAttr -s 5 ".kot[1:4]"  10 9 3 1;
	setAttr -s 5 ".kix[4]"  0.066666662693023682;
	setAttr -s 5 ".kiy[4]"  -0.034612111747264862;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  -0.034612111747264862;
createNode animCurveTL -n "animCurveTL71";
	setAttr ".tan" 3;
	setAttr -s 5 ".ktv[0:4]"  1 -0.032867286470989195 3 -0.17306616688009402 
		6 -0.29068217283210629 10 -0.29068217283210629 45 -0.032867286470989195;
	setAttr -s 5 ".kit[0:4]"  9 10 3 3 1;
	setAttr -s 5 ".kot[0:4]"  9 10 3 3 1;
	setAttr -s 5 ".kix[4]"  0.066666662693023682;
	setAttr -s 5 ".kiy[4]"  -0.14019888639450073;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  -0.14019888639450073;
createNode animCurveTL -n "animCurveTL72";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  1 -0.0098384205421270955 3 -0.045513647780376337 
		10 -0.010934714093214195 36 -0.13273729618618149 45 -0.0098384205421270955;
	setAttr -s 5 ".kit[0:4]"  9 10 3 10 1;
	setAttr -s 5 ".kot[0:4]"  9 10 3 10 1;
	setAttr -s 5 ".kix[4]"  0.066666662693023682;
	setAttr -s 5 ".kiy[4]"  -0.035675227642059326;
	setAttr -s 5 ".kox[4]"  0.066666662693023682;
	setAttr -s 5 ".koy[4]"  -0.035675227642059326;
createNode animCurveTA -n "animCurveTA193";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  1 -25.590668618635455 3 -25.590668618635455 
		6 -44.715432122753263 10 -44.715432122753263 25 -44.715432122753263 33 -25.590668618635455 
		45 -25.590668618635455;
	setAttr -s 7 ".kit[0:6]"  2 1 10 10 10 3 3;
	setAttr -s 7 ".kot[0:6]"  2 1 10 10 10 3 3;
	setAttr -s 7 ".kix[1:6]"  1 0.10000000149011612 0.13333334028720856 
		0.49999997019767761 0.2666667103767395 0.39999997615814209;
	setAttr -s 7 ".kiy[1:6]"  0 0 0 0 0 0;
	setAttr -s 7 ".kox[1:6]"  0.066666662693023682 0.13333334028720856 
		0.49999997019767761 0.2666667103767395 0.39999997615814209 0.39999997615814209;
	setAttr -s 7 ".koy[1:6]"  -0.14069449901580811 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA194";
	setAttr ".tan" 3;
	setAttr -s 6 ".ktv[0:5]"  1 0 3 0 10 0 25 0 33 0 45 0;
	setAttr -s 6 ".kit[1:5]"  1 10 10 3 3;
	setAttr -s 6 ".kot[1:5]"  1 10 10 3 3;
	setAttr -s 6 ".kix[1:5]"  0.066666662693023682 0.23333334922790527 
		0.49999997019767761 0.2666667103767395 0.39999997615814209;
	setAttr -s 6 ".kiy[1:5]"  0 0 0 0 0;
	setAttr -s 6 ".kox[1:5]"  0.066666662693023682 0.49999997019767761 
		0.2666667103767395 0.39999997615814209 0.39999997615814209;
	setAttr -s 6 ".koy[1:5]"  0 0 0 0 0;
createNode animCurveTA -n "animCurveTA195";
	setAttr ".tan" 3;
	setAttr -s 6 ".ktv[0:5]"  1 0 3 0 10 0 25 0 33 0 45 0;
	setAttr -s 6 ".kit[1:5]"  1 10 10 3 3;
	setAttr -s 6 ".kot[1:5]"  1 10 10 3 3;
	setAttr -s 6 ".kix[1:5]"  0.066666662693023682 0.23333334922790527 
		0.49999997019767761 0.2666667103767395 0.39999997615814209;
	setAttr -s 6 ".kiy[1:5]"  0 0 0 0 0;
	setAttr -s 6 ".kox[1:5]"  0.066666662693023682 0.49999997019767761 
		0.2666667103767395 0.39999997615814209 0.39999997615814209;
	setAttr -s 6 ".koy[1:5]"  0 0 0 0 0;
createNode animCurveTL -n "animCurveTL73";
	setAttr ".tan" 3;
	setAttr -s 6 ".ktv[0:5]"  1 0 3 0 10 0 25 0 33 0 45 0;
	setAttr -s 6 ".kit[1:5]"  1 10 10 3 3;
	setAttr -s 6 ".kot[1:5]"  1 10 10 3 3;
	setAttr -s 6 ".kix[1:5]"  0.066666662693023682 0.23333334922790527 
		0.49999997019767761 0.2666667103767395 0.39999997615814209;
	setAttr -s 6 ".kiy[1:5]"  0 0 0 0 0;
	setAttr -s 6 ".kox[1:5]"  0.066666662693023682 0.49999997019767761 
		0.2666667103767395 0.39999997615814209 0.39999997615814209;
	setAttr -s 6 ".koy[1:5]"  0 0 0 0 0;
createNode animCurveTL -n "animCurveTL74";
	setAttr ".tan" 3;
	setAttr -s 6 ".ktv[0:5]"  1 0.15953969092363035 3 0.15953969092363035 
		10 0.15953969092363035 25 0.15953969092363035 33 0.15953969092363035 45 0.15953969092363035;
	setAttr -s 6 ".kit[1:5]"  1 10 10 3 3;
	setAttr -s 6 ".kot[1:5]"  1 10 10 3 3;
	setAttr -s 6 ".kix[1:5]"  0.066666662693023682 0.23333334922790527 
		0.49999997019767761 0.2666667103767395 0.39999997615814209;
	setAttr -s 6 ".kiy[1:5]"  0 0 0 0 0;
	setAttr -s 6 ".kox[1:5]"  0.066666662693023682 0.49999997019767761 
		0.2666667103767395 0.39999997615814209 0.39999997615814209;
	setAttr -s 6 ".koy[1:5]"  0 0 0 0 0;
createNode animCurveTL -n "animCurveTL75";
	setAttr ".tan" 3;
	setAttr -s 6 ".ktv[0:5]"  1 -0.04 3 -0.04 10 -0.04 25 -0.04 33 -0.04 
		45 -0.04;
	setAttr -s 6 ".kit[1:5]"  1 10 10 3 3;
	setAttr -s 6 ".kot[1:5]"  1 10 10 3 3;
	setAttr -s 6 ".kix[1:5]"  0.066666662693023682 0.23333334922790527 
		0.49999997019767761 0.2666667103767395 0.39999997615814209;
	setAttr -s 6 ".kiy[1:5]"  0 0 0 0 0;
	setAttr -s 6 ".kox[1:5]"  0.066666662693023682 0.49999997019767761 
		0.2666667103767395 0.39999997615814209 0.39999997615814209;
	setAttr -s 6 ".koy[1:5]"  0 0 0 0 0;
createNode animCurveTA -n "animCurveTA196";
	setAttr ".tan" 1;
	setAttr -s 8 ".ktv[0:7]"  1 11.880229891661756 2 11.880229891661756 
		5 5.9568497368918365 10 5.9568497368918365 31 5.9568497368918365 35 5.9568497368918365 
		38 11.880229891661756 45 11.880229891661756;
	setAttr -s 8 ".kit[0:7]"  2 1 1 10 3 1 1 9;
	setAttr -s 8 ".kot[0:7]"  2 1 1 10 3 1 1 9;
	setAttr -s 8 ".kix[1:7]"  1 0.066666662693023682 0.1666666716337204 
		0.69999992847442627 0.49999994039535522 0.16666662693023682 0.23333334922790527;
	setAttr -s 8 ".kiy[1:7]"  0 0 0 0 0 0.10338248312473297 0;
	setAttr -s 8 ".kox[1:7]"  0.066666662693023682 0.23333334922790527 
		0.69999992847442627 0.13333332538604736 0.23333334922790527 0.16666662693023682 0.23333334922790527;
	setAttr -s 8 ".koy[1:7]"  -0.10338248312473297 0 0 0 0 0.10338248312473297 
		0;
createNode animCurveTA -n "animCurveTA197";
	setAttr ".tan" 1;
	setAttr -s 8 ".ktv[0:7]"  1 0 2 0 5 0 10 0 31 0 35 0 38 0 45 0;
	setAttr -s 8 ".kit[0:7]"  2 1 1 10 3 1 1 3;
	setAttr -s 8 ".kot[0:7]"  2 1 1 10 3 1 1 3;
	setAttr -s 8 ".kix[1:7]"  1 0.066666662693023682 0.1666666716337204 
		0.69999992847442627 0.49999994039535522 0.16666662693023682 0.23333334922790527;
	setAttr -s 8 ".kiy[1:7]"  0 0 0 0 0 0 0;
	setAttr -s 8 ".kox[1:7]"  0.066666662693023682 0.23333334922790527 
		0.69999992847442627 0.13333332538604736 0.23333334922790527 0.16666662693023682 0.23333334922790527;
	setAttr -s 8 ".koy[1:7]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA198";
	setAttr ".tan" 1;
	setAttr -s 8 ".ktv[0:7]"  1 0 2 7.4545959177912744 5 0 10 0 31 0 
		35 0 38 0 45 0;
	setAttr -s 8 ".kit[0:7]"  2 1 1 10 3 1 1 3;
	setAttr -s 8 ".kot[0:7]"  2 1 1 10 3 1 1 3;
	setAttr -s 8 ".kix[1:7]"  1 0.066666662693023682 0.1666666716337204 
		0.69999992847442627 0.49999994039535522 0.16666662693023682 0.23333334922790527;
	setAttr -s 8 ".kiy[1:7]"  0 0 0 0 0 0 0;
	setAttr -s 8 ".kox[1:7]"  0.066666662693023682 0.23333334922790527 
		0.69999992847442627 0.13333332538604736 0.23333334922790527 0.16666662693023682 0.23333334922790527;
	setAttr -s 8 ".koy[1:7]"  0.13508149981498718 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL76";
	setAttr ".tan" 1;
	setAttr -s 8 ".ktv[0:7]"  1 0 2 0.041677345969035259 5 0 10 0 31 
		0 35 0 38 0 45 0;
	setAttr -s 8 ".kit[0:7]"  2 1 1 10 3 1 1 3;
	setAttr -s 8 ".kot[0:7]"  2 1 1 10 3 1 1 3;
	setAttr -s 8 ".kix[1:7]"  1 0.066666662693023682 0.1666666716337204 
		0.69999992847442627 0.49999994039535522 0.16666662693023682 0.23333334922790527;
	setAttr -s 8 ".kiy[1:7]"  0 0 0 0 0 0 0;
	setAttr -s 8 ".kox[1:7]"  0.066666662693023682 0.23333334922790527 
		0.69999992847442627 0.13333332538604736 0.23333334922790527 0.16666662693023682 0.23333334922790527;
	setAttr -s 8 ".koy[1:7]"  0.042099390178918839 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL77";
	setAttr ".tan" 1;
	setAttr -s 8 ".ktv[0:7]"  1 -0.20007920657257083 2 -0.20007920657257083 
		5 -0.46654864940744167 10 -0.46654864940744167 31 -0.46654864940744167 35 -0.46654864940744167 
		38 -0.20007920657257083 45 -0.20007920657257083;
	setAttr -s 8 ".kit[0:7]"  2 1 1 10 3 1 1 3;
	setAttr -s 8 ".kot[0:7]"  2 1 1 10 3 1 1 3;
	setAttr -s 8 ".kix[1:7]"  1 0.066666662693023682 0.1666666716337204 
		0.69999992847442627 0.49999994039535522 0.16666662693023682 0.23333334922790527;
	setAttr -s 8 ".kiy[1:7]"  0 0 0 0 0 0 0;
	setAttr -s 8 ".kox[1:7]"  0.066666662693023682 0.23333334922790527 
		0.69999992847442627 0.13333332538604736 0.23333334922790527 0.16666662693023682 0.23333334922790527;
	setAttr -s 8 ".koy[1:7]"  -0.26646944880485535 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL78";
	setAttr ".tan" 1;
	setAttr -s 8 ".ktv[0:7]"  1 0.098575236578624326 2 0.098575236578624326 
		5 0.08748812254799819 10 0.08748812254799819 31 0.08748812254799819 35 0.08748812254799819 
		38 0.098575236578624326 45 0.098575236578624326;
	setAttr -s 8 ".kit[0:7]"  2 1 1 10 3 1 1 3;
	setAttr -s 8 ".kot[0:7]"  2 1 1 10 3 1 1 3;
	setAttr -s 8 ".kix[1:7]"  1 0.066666662693023682 0.1666666716337204 
		0.69999992847442627 0.49999994039535522 0.16666662693023682 0.23333334922790527;
	setAttr -s 8 ".kiy[1:7]"  0 0 0 0 0 0 0;
	setAttr -s 8 ".kox[1:7]"  0.066666662693023682 0.23333334922790527 
		0.69999992847442627 0.13333332538604736 0.23333334922790527 0.16666662693023682 0.23333334922790527;
	setAttr -s 8 ".koy[1:7]"  -0.011087113991379738 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU111";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  1 1 3 1 10 1 45 1;
	setAttr -s 4 ".kit[1:3]"  9 9 1;
	setAttr -s 4 ".kot[1:3]"  5 5 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  0.066666662693023682;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "animCurveTA199";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[0:3]"  2 10 10 1;
	setAttr -s 4 ".kot[0:3]"  2 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  0.066666662693023682;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "animCurveTA200";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[0:3]"  2 10 10 1;
	setAttr -s 4 ".kot[0:3]"  2 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  0.066666662693023682;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "animCurveTA201";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[0:3]"  2 10 10 1;
	setAttr -s 4 ".kot[0:3]"  2 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  0.066666662693023682;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTL -n "animCurveTL79";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  1 -0.81944359671150613 3 -0.81944359671150613 
		10 -0.81944359671150613 45 -0.81944359671150613;
	setAttr -s 4 ".kit[0:3]"  2 10 10 1;
	setAttr -s 4 ".kot[0:3]"  2 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  0.066666662693023682;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTL -n "animCurveTL80";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  1 0.029470472912715796 3 0.029470472912715796 
		10 0.029470472912715796 45 0.029470472912715796;
	setAttr -s 4 ".kit[0:3]"  2 10 10 1;
	setAttr -s 4 ".kot[0:3]"  2 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  0.066666662693023682;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTL -n "animCurveTL81";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  1 -0.070295643204272437 3 -0.070295643204272437 
		10 -0.070295643204272437 45 -0.070295643204272437;
	setAttr -s 4 ".kit[0:3]"  3 10 10 1;
	setAttr -s 4 ".kot[0:3]"  3 10 10 1;
	setAttr -s 4 ".kix[3]"  0.066666662693023682;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  0.066666662693023682;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU112";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  1 1 3 1 10 1 45 1;
	setAttr -s 4 ".kit[1:3]"  9 9 1;
	setAttr -s 4 ".kot[1:3]"  5 5 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  0.066666662693023682;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "animCurveTA202";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  1 -4.8160457500419067 3 -4.8160457500419067 
		10 -4.8160457500419067 45 -4.8160457500419067;
	setAttr -s 4 ".kit[0:3]"  2 10 10 1;
	setAttr -s 4 ".kot[0:3]"  2 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  0.066666662693023682;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "animCurveTA203";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[0:3]"  2 10 10 1;
	setAttr -s 4 ".kot[0:3]"  2 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  0.066666662693023682;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "animCurveTA204";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[0:3]"  2 10 10 1;
	setAttr -s 4 ".kot[0:3]"  2 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  0.066666662693023682;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTL -n "animCurveTL82";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  1 -0.80451419482641451 3 -0.80451419482641451 
		10 -0.80451419482641451 45 -0.80451419482641451;
	setAttr -s 4 ".kit[0:3]"  2 10 10 1;
	setAttr -s 4 ".kot[0:3]"  2 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  0.066666662693023682;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTL -n "animCurveTL83";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  1 -2.4945889741368431e-013 3 -2.4945889741368431e-013 
		10 -2.4945889741368431e-013 45 -2.4945889741368431e-013;
	setAttr -s 4 ".kit[0:3]"  2 10 10 1;
	setAttr -s 4 ".kot[0:3]"  2 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  0.066666662693023682;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTL -n "animCurveTL84";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  1 -0.0085562672260772743 3 -0.0085562672260772743 
		10 -0.0085562672260772743 45 -0.0085562672260772743;
	setAttr -s 4 ".kit[0:3]"  2 10 10 1;
	setAttr -s 4 ".kot[0:3]"  2 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  0.066666662693023682;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU113";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  1 0 3 0 6 0 10 0 25 0 45 0;
	setAttr -s 6 ".kit[0:5]"  2 10 10 10 1 1;
	setAttr -s 6 ".kot[0:5]"  2 10 10 10 1 1;
	setAttr -s 6 ".kix[4:5]"  1 1;
	setAttr -s 6 ".kiy[4:5]"  0 0;
	setAttr -s 6 ".kox[4:5]"  0.066666662693023682 0.066666662693023682;
	setAttr -s 6 ".koy[4:5]"  0 0;
createNode animCurveTU -n "animCurveTU114";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  1 45 3 45 6 45 10 45 25 45 45 45;
	setAttr -s 6 ".kit[0:5]"  2 10 10 10 1 1;
	setAttr -s 6 ".kot[0:5]"  2 10 10 10 1 1;
	setAttr -s 6 ".kix[4:5]"  1 1;
	setAttr -s 6 ".kiy[4:5]"  0 0;
	setAttr -s 6 ".kox[4:5]"  0.066666662693023682 0.066666662693023682;
	setAttr -s 6 ".koy[4:5]"  0 0;
createNode animCurveTU -n "animCurveTU115";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  1 45 3 45 6 45 10 45 25 45 45 45;
	setAttr -s 6 ".kit[0:5]"  2 10 10 10 1 1;
	setAttr -s 6 ".kot[0:5]"  2 10 10 10 1 1;
	setAttr -s 6 ".kix[4:5]"  1 1;
	setAttr -s 6 ".kiy[4:5]"  0 0;
	setAttr -s 6 ".kox[4:5]"  0.066666662693023682 0.066666662693023682;
	setAttr -s 6 ".koy[4:5]"  0 0;
createNode animCurveTU -n "animCurveTU116";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  1 45 3 45 6 45 10 45 25 45 45 45;
	setAttr -s 6 ".kit[0:5]"  2 10 10 10 1 1;
	setAttr -s 6 ".kot[0:5]"  2 10 10 10 1 1;
	setAttr -s 6 ".kix[4:5]"  1 1;
	setAttr -s 6 ".kiy[4:5]"  0 0;
	setAttr -s 6 ".kox[4:5]"  0.066666662693023682 0.066666662693023682;
	setAttr -s 6 ".koy[4:5]"  0 0;
createNode animCurveTA -n "animCurveTA205";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  1 0 3 0 6 0 10 0 25 0 45 0;
	setAttr -s 6 ".kit[0:5]"  2 10 10 10 1 1;
	setAttr -s 6 ".kot[0:5]"  2 10 10 10 1 1;
	setAttr -s 6 ".kix[4:5]"  1 1;
	setAttr -s 6 ".kiy[4:5]"  0 0;
	setAttr -s 6 ".kox[4:5]"  0.066666662693023682 0.066666662693023682;
	setAttr -s 6 ".koy[4:5]"  0 0;
createNode animCurveTA -n "animCurveTA206";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  1 0 3 0 6 0 10 15.164323852297839 14 23.236154630612504 
		25 0 45 0;
	setAttr -s 7 ".kit[0:6]"  2 10 10 10 10 3 1;
	setAttr -s 7 ".kot[0:6]"  2 10 10 10 10 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  0.066666662693023682;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTU -n "animCurveTU117";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  1 0 3 0 10 0 31 0 35 0 43 0 45 0;
	setAttr -s 7 ".kit[0:6]"  2 10 10 10 10 1 1;
	setAttr -s 7 ".kot[0:6]"  2 10 10 10 10 1 1;
	setAttr -s 7 ".kix[5:6]"  1 1;
	setAttr -s 7 ".kiy[5:6]"  0 0;
	setAttr -s 7 ".kox[5:6]"  0.066666662693023682 0.066666662693023682;
	setAttr -s 7 ".koy[5:6]"  0 0;
createNode animCurveTU -n "animCurveTU118";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  1 45 3 45 10 45 31 45 35 45 43 45 45 45;
	setAttr -s 7 ".kit[0:6]"  2 10 10 10 10 1 1;
	setAttr -s 7 ".kot[0:6]"  2 10 10 10 10 1 1;
	setAttr -s 7 ".kix[5:6]"  1 1;
	setAttr -s 7 ".kiy[5:6]"  0 0;
	setAttr -s 7 ".kox[5:6]"  0.066666662693023682 0.066666662693023682;
	setAttr -s 7 ".koy[5:6]"  0 0;
createNode animCurveTU -n "animCurveTU119";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  1 45 3 45 10 45 31 45 35 45 43 45 45 45;
	setAttr -s 7 ".kit[0:6]"  2 10 10 10 10 1 1;
	setAttr -s 7 ".kot[0:6]"  2 10 10 10 10 1 1;
	setAttr -s 7 ".kix[5:6]"  1 1;
	setAttr -s 7 ".kiy[5:6]"  0 0;
	setAttr -s 7 ".kox[5:6]"  0.066666662693023682 0.066666662693023682;
	setAttr -s 7 ".koy[5:6]"  0 0;
createNode animCurveTU -n "animCurveTU120";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  1 45 3 45 10 45 31 45 35 45 43 45 45 45;
	setAttr -s 7 ".kit[0:6]"  2 10 10 10 10 1 1;
	setAttr -s 7 ".kot[0:6]"  2 10 10 10 10 1 1;
	setAttr -s 7 ".kix[5:6]"  1 1;
	setAttr -s 7 ".kiy[5:6]"  0 0;
	setAttr -s 7 ".kox[5:6]"  0.066666662693023682 0.066666662693023682;
	setAttr -s 7 ".koy[5:6]"  0 0;
createNode animCurveTA -n "animCurveTA207";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  1 0 3 0 10 0 31 0 35 -3.5750676827199666 
		43 0 45 0;
	setAttr -s 7 ".kit[0:6]"  2 10 10 10 10 1 1;
	setAttr -s 7 ".kot[0:6]"  2 10 10 10 10 1 1;
	setAttr -s 7 ".kix[5:6]"  1 1;
	setAttr -s 7 ".kiy[5:6]"  0 0;
	setAttr -s 7 ".kox[5:6]"  0.066666662693023682 0.066666662693023682;
	setAttr -s 7 ".koy[5:6]"  0 0;
createNode animCurveTA -n "animCurveTA208";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  1 0 3 0 10 0 31 0 35 7.1903166320408785 
		38 9.0443961239361403 43 0 45 0;
	setAttr -s 8 ".kit[0:7]"  2 10 10 10 10 10 1 1;
	setAttr -s 8 ".kot[0:7]"  2 10 10 10 10 10 1 1;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  0.066666662693023682 0.066666662693023682;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTU -n "animCurveTU121";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU122";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU123";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU124";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU125";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU126";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU127";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU128";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU129";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU130";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU131";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU132";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "animCurveTA209";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "animCurveTA210";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "animCurveTA211";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 -2.5999764661798822e-011 3 -2.5999764661798822e-011 
		10 -2.5999764661798822e-011 45 -2.5999764661798822e-011;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU133";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU134";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU135";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU136";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU137";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU138";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU139";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU140";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU141";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU142";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU143";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "animCurveTU144";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "animCurveTA212";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "animCurveTA213";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "animCurveTA214";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 -2.5997909391022333e-011 3 -2.5997909391022333e-011 
		10 -2.5997909391022333e-011 45 -2.5997909391022333e-011;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "animCurveTA215";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  1 -5.8382275551355809 3 0.55094126562236756 
		4 -16.788706703048955 6 3.2011968734023077 10 -13.178257016944228 25 -20.237575912505445 
		36 -13.580065429309439 45 -5.8382275551355809;
	setAttr -s 8 ".kit[0:7]"  1 10 10 10 3 9 10 1;
	setAttr -s 8 ".kot[0:7]"  1 10 10 10 3 9 10 1;
	setAttr -s 8 ".kix[0:7]"  0.06666005402803421 0.066666662693023682 
		0.033333338797092438 0.066666662693023682 0.13333334028720856 0.49999997019767761 
		0.36666673421859741 0.06666005402803421;
	setAttr -s 8 ".kiy[0:7]"  -0.015686014667153358 -0.12741458415985107 
		0.015418563969433308 0.021004743874073029 0 -0.0040458920411765575 0.13822384178638458 
		-0.015686014667153358;
	setAttr -s 8 ".kox[0:7]"  0.066660061478614807 0.033333338797092438 
		0.066666662693023682 0.13333334028720856 0.49999997019767761 0.36666673421859741 
		0.29999995231628418 0.066660061478614807;
	setAttr -s 8 ".koy[0:7]"  -0.015686014667153358 -0.063707306981086731 
		0.030837122350931168 0.042009491473436356 0 -0.0029669881332665682 0.11309219896793365 
		-0.015686014667153358;
createNode animCurveTA -n "animCurveTA216";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  1 -2.3136539176186792 3 -2.3972369079961999 
		4 29.886193234284359 6 29.630264204023025 10 19.537880515568371 25 17.975343854855289 
		36 -3.9261289150813212 45 -2.3136539176186792;
	setAttr -s 8 ".kit[0:7]"  1 10 10 10 3 9 10 1;
	setAttr -s 8 ".kot[0:7]"  1 10 10 10 3 9 10 1;
	setAttr -s 8 ".kix[0:7]"  0.066300936043262482 0.066666662693023682 
		0.033333338797092438 0.066666662693023682 0.13333334028720856 0.49999997019767761 
		0.36666673421859741 0.066300936043262482;
	setAttr -s 8 ".kiy[0:7]"  -0.034498795866966248 0 0 0 0 -0.23626396059989929 
		0 -0.034498795866966248;
	setAttr -s 8 ".kox[0:7]"  0.066300936043262482 0.033333338797092438 
		0.066666662693023682 0.13333334028720856 0.49999997019767761 0.36666673421859741 
		0.29999995231628418 0.066300936043262482;
	setAttr -s 8 ".koy[0:7]"  -0.034498799592256546 0 0 0 0 -0.17326027154922485 
		0 -0.034498799592256546;
createNode animCurveTA -n "animCurveTA217";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  1 -13.887028133305018 3 -22.384409411812765 
		4 -17.465645064866191 6 10.826651655737562 10 36.104547565803088 25 14.930146002499962 
		36 -0.7693042736941671 45 -13.887028133305018;
	setAttr -s 8 ".kit[0:7]"  1 10 10 10 3 9 10 1;
	setAttr -s 8 ".kot[0:7]"  1 10 10 10 3 9 10 1;
	setAttr -s 8 ".kix[0:7]"  0.066675402224063873 0.066666662693023682 
		0.033333338797092438 0.066666662693023682 0.13333334028720856 0.49999997019767761 
		0.36666673421859741 0.066675402224063873;
	setAttr -s 8 ".kiy[0:7]"  0.0037189542781561613 -0.041639093309640884 
		0.19321414828300476 0.31165871024131775 0 -0.3712904155254364 -0.27662506699562073 
		0.0037189542781561613;
	setAttr -s 8 ".kox[0:7]"  0.06667540967464447 0.033333338797092438 
		0.066666662693023682 0.13333334028720856 0.49999997019767761 0.36666673421859741 
		0.29999995231628418 0.06667540967464447;
	setAttr -s 8 ".koy[0:7]"  0.0037189535796642303 -0.020819550380110741 
		0.38642820715904236 0.62331753969192505 0 -0.27227970957756042 -0.22632952034473419 
		0.0037189535796642303;
createNode animCurveTA -n "animCurveTA218";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  1 13.873263178484903 3 25.789541315292396 
		6 30.449430566830305 10 30.449430566830305 25 26.083093790185256 35 21.533974071815638 
		45 13.873263178484903;
	setAttr -s 7 ".kit[0:6]"  2 10 10 3 10 10 1;
	setAttr -s 7 ".kot[0:6]"  2 10 10 3 10 10 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  0.066666662693023682;
	setAttr -s 7 ".koy[6]"  0.20797829329967499;
createNode animCurveTA -n "animCurveTA219";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  1 0 3 5.7477139006305489 6 0.89127678232234531 
		10 0.89127678232234531 25 -9.1731676183439408 35 0.1458792239666743 45 0;
	setAttr -s 7 ".kit[0:6]"  2 10 10 3 10 10 1;
	setAttr -s 7 ".kot[0:6]"  2 10 10 3 10 10 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  0.066666662693023682;
	setAttr -s 7 ".koy[6]"  0.10031653195619583;
createNode animCurveTA -n "animCurveTA220";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  1 0 3 -2.8191557937623566 6 3.4892902384080626 
		10 3.4892902384080626 25 1.7663044014974605 35 0.79555908135123576 45 0;
	setAttr -s 7 ".kit[0:6]"  2 10 10 3 10 10 1;
	setAttr -s 7 ".kot[0:6]"  2 10 10 3 10 10 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  0.066666662693023682;
	setAttr -s 7 ".koy[6]"  -0.049203552305698395;
createNode animCurveTA -n "animCurveTA221";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 0;
	setAttr ".kit[9]"  4;
	setAttr ".kot[9]"  4;
createNode animCurveTA -n "animCurveTA222";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 0;
	setAttr ".kit[9]"  4;
	setAttr ".kot[9]"  4;
createNode animCurveTA -n "animCurveTA223";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 0;
	setAttr ".kit[9]"  4;
	setAttr ".kot[9]"  4;
createNode animCurveTA -n "animCurveTA224";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 -7.6359447996384162;
createNode animCurveTA -n "animCurveTA225";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 -35.260196151694586;
createNode animCurveTA -n "animCurveTA226";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 68.744635926587719;
createNode animCurveTA -n "animCurveTA227";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 -7.6359447996384162;
createNode animCurveTA -n "animCurveTA228";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 -35.260196151694586;
createNode animCurveTA -n "animCurveTA229";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 68.744635926587719;
createNode animCurveTA -n "animCurveTA230";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 -7.6359447996384162;
createNode animCurveTA -n "animCurveTA231";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 -35.260196151694586;
createNode animCurveTA -n "animCurveTA232";
	setAttr ".tan" 1;
	setAttr ".ktv[0]"  1 68.744635926587719;
	setAttr ".kix[0]"  0.066353410482406616;
	setAttr ".kiy[0]"  -0.10914206504821777;
	setAttr ".kox[0]"  0.066353403031826019;
	setAttr ".koy[0]"  -0.10914205014705658;
createNode animCurveTA -n "animCurveTA233";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 18.08;
createNode animCurveTA -n "animCurveTA234";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1 -0.0336;
createNode animCurveTA -n "animCurveTA235";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA236";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 18.373158409800983;
createNode animCurveTA -n "animCurveTA237";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA238";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA239";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1 18.373158409800983;
createNode animCurveTA -n "animCurveTA240";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA241";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA242";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 18.373158409800983;
createNode animCurveTA -n "animCurveTA243";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA244";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA245";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 18.373158409800983;
createNode animCurveTA -n "animCurveTA246";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA247";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA248";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 18.373158409800983;
createNode animCurveTA -n "animCurveTA249";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA250";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA251";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 -5.4432506707315573;
createNode animCurveTA -n "animCurveTA252";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA253";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 1.4808130565433952;
createNode animCurveTA -n "animCurveTA254";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 -13.113682797820777;
	setAttr ".kit[8]"  4;
	setAttr ".kot[8]"  4;
createNode animCurveTA -n "animCurveTA255";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 -4.0919497789234391;
	setAttr ".kit[8]"  4;
	setAttr ".kot[8]"  4;
createNode animCurveTA -n "animCurveTA256";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  1 31.178362171912408;
	setAttr ".kit[8]"  4;
	setAttr ".kot[8]"  4;
createNode animCurveTL -n "animCurveTL85";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0.30350192845064827;
createNode animCurveTL -n "animCurveTL86";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -1.0240687361594651;
createNode animCurveTL -n "animCurveTL87";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -0.43946686130894153;
createNode animCurveTL -n "animCurveTL88";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0.27531887801250954;
createNode animCurveTL -n "animCurveTL89";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -1.0012123423352446;
createNode animCurveTL -n "animCurveTL90";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0.71970840690534188;
createNode animCurveTA -n "animCurveTA257";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -111.88689016967699;
createNode animCurveTA -n "animCurveTA258";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -132.63553015029723;
createNode animCurveTA -n "animCurveTA259";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -66.606237462352041;
createNode animCurveTL -n "animCurveTL91";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0.4196306328102265;
createNode animCurveTL -n "animCurveTL92";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -0.14401492817444136;
createNode animCurveTL -n "animCurveTL93";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -0.19935929083177334;
createNode animCurveTA -n "animCurveTA260";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 119.62711466156466;
createNode animCurveTA -n "animCurveTA261";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 131.41878674178685;
createNode animCurveTA -n "animCurveTA262";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 301.25683546959215;
createNode animCurveTL -n "animCurveTL94";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0.40867405508166788;
createNode animCurveTL -n "animCurveTL95";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -0.10123643033093419;
createNode animCurveTL -n "animCurveTL96";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0.51342548710889013;
createNode animCurveTL -n "animCurveTL97";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTL -n "animCurveTL98";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTL -n "animCurveTL99";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTL -n "animCurveTL100";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTL -n "animCurveTL101";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTL -n "animCurveTL102";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  1 0 3 0 10 0 45 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "animCurveTA263";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA264";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "animCurveTA265";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "animCurveTL103";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "animCurveTL104";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTL -n "animCurveTL105";
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
	setAttr -s 4 ".sol";
connectAttr "attackESource.cl" "clipLibrary1.sc[0]";
connectAttr "animCurveTU109.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "animCurveTU110.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "animCurveTA166.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "animCurveTA167.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "animCurveTA168.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "animCurveTA169.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "animCurveTA170.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "animCurveTA171.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "animCurveTA172.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "animCurveTA173.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "animCurveTA174.a" "clipLibrary1.cel[0].cev[10].cevr";
connectAttr "animCurveTA175.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "animCurveTA176.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "animCurveTA177.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "animCurveTA178.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "animCurveTA179.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "animCurveTA180.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "animCurveTA181.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "animCurveTA182.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "animCurveTA183.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "animCurveTA184.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "animCurveTA185.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "animCurveTA186.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "animCurveTA187.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "animCurveTA188.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "animCurveTA189.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "animCurveTL64.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "animCurveTL65.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "animCurveTL66.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "animCurveTL67.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "animCurveTL68.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "animCurveTL69.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "animCurveTA190.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "animCurveTA191.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "animCurveTA192.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "animCurveTL70.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "animCurveTL71.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "animCurveTL72.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "animCurveTA193.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "animCurveTA194.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "animCurveTA195.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "animCurveTL73.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "animCurveTL74.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "animCurveTL75.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "animCurveTA196.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "animCurveTA197.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "animCurveTA198.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "animCurveTL76.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "animCurveTL77.a" "clipLibrary1.cel[0].cev[48].cevr";
connectAttr "animCurveTL78.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "animCurveTU111.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "animCurveTA199.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "animCurveTA200.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "animCurveTA201.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "animCurveTL79.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "animCurveTL80.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "animCurveTL81.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "animCurveTU112.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "animCurveTA202.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "animCurveTA203.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "animCurveTA204.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "animCurveTL82.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "animCurveTL83.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "animCurveTL84.a" "clipLibrary1.cel[0].cev[63].cevr";
connectAttr "animCurveTU113.a" "clipLibrary1.cel[0].cev[64].cevr";
connectAttr "animCurveTU114.a" "clipLibrary1.cel[0].cev[65].cevr";
connectAttr "animCurveTU115.a" "clipLibrary1.cel[0].cev[66].cevr";
connectAttr "animCurveTU116.a" "clipLibrary1.cel[0].cev[67].cevr";
connectAttr "animCurveTA205.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "animCurveTA206.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "animCurveTU117.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "animCurveTU118.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "animCurveTU119.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "animCurveTU120.a" "clipLibrary1.cel[0].cev[73].cevr";
connectAttr "animCurveTA207.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "animCurveTA208.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "animCurveTU121.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "animCurveTU122.a" "clipLibrary1.cel[0].cev[77].cevr";
connectAttr "animCurveTU123.a" "clipLibrary1.cel[0].cev[78].cevr";
connectAttr "animCurveTU124.a" "clipLibrary1.cel[0].cev[79].cevr";
connectAttr "animCurveTU125.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "animCurveTU126.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "animCurveTU127.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "animCurveTU128.a" "clipLibrary1.cel[0].cev[83].cevr";
connectAttr "animCurveTU129.a" "clipLibrary1.cel[0].cev[84].cevr";
connectAttr "animCurveTU130.a" "clipLibrary1.cel[0].cev[85].cevr";
connectAttr "animCurveTU131.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "animCurveTU132.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "animCurveTA209.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "animCurveTA210.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr "animCurveTA211.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "animCurveTU133.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "animCurveTU134.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "animCurveTU135.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "animCurveTU136.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "animCurveTU137.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "animCurveTU138.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "animCurveTU139.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "animCurveTU140.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "animCurveTU141.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "animCurveTU142.a" "clipLibrary1.cel[0].cev[100].cevr";
connectAttr "animCurveTU143.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "animCurveTU144.a" "clipLibrary1.cel[0].cev[102].cevr";
connectAttr "animCurveTA212.a" "clipLibrary1.cel[0].cev[103].cevr";
connectAttr "animCurveTA213.a" "clipLibrary1.cel[0].cev[104].cevr";
connectAttr "animCurveTA214.a" "clipLibrary1.cel[0].cev[105].cevr";
connectAttr "animCurveTA215.a" "clipLibrary1.cel[0].cev[106].cevr";
connectAttr "animCurveTA216.a" "clipLibrary1.cel[0].cev[107].cevr";
connectAttr "animCurveTA217.a" "clipLibrary1.cel[0].cev[108].cevr";
connectAttr "animCurveTA218.a" "clipLibrary1.cel[0].cev[109].cevr";
connectAttr "animCurveTA219.a" "clipLibrary1.cel[0].cev[110].cevr";
connectAttr "animCurveTA220.a" "clipLibrary1.cel[0].cev[111].cevr";
connectAttr "animCurveTA221.a" "clipLibrary1.cel[0].cev[112].cevr";
connectAttr "animCurveTA222.a" "clipLibrary1.cel[0].cev[113].cevr";
connectAttr "animCurveTA223.a" "clipLibrary1.cel[0].cev[114].cevr";
connectAttr "animCurveTA224.a" "clipLibrary1.cel[0].cev[115].cevr";
connectAttr "animCurveTA225.a" "clipLibrary1.cel[0].cev[116].cevr";
connectAttr "animCurveTA226.a" "clipLibrary1.cel[0].cev[117].cevr";
connectAttr "animCurveTA227.a" "clipLibrary1.cel[0].cev[118].cevr";
connectAttr "animCurveTA228.a" "clipLibrary1.cel[0].cev[119].cevr";
connectAttr "animCurveTA229.a" "clipLibrary1.cel[0].cev[120].cevr";
connectAttr "animCurveTA230.a" "clipLibrary1.cel[0].cev[121].cevr";
connectAttr "animCurveTA231.a" "clipLibrary1.cel[0].cev[122].cevr";
connectAttr "animCurveTA232.a" "clipLibrary1.cel[0].cev[123].cevr";
connectAttr "animCurveTA233.a" "clipLibrary1.cel[0].cev[124].cevr";
connectAttr "animCurveTA234.a" "clipLibrary1.cel[0].cev[125].cevr";
connectAttr "animCurveTA235.a" "clipLibrary1.cel[0].cev[126].cevr";
connectAttr "animCurveTA236.a" "clipLibrary1.cel[0].cev[127].cevr";
connectAttr "animCurveTA237.a" "clipLibrary1.cel[0].cev[128].cevr";
connectAttr "animCurveTA238.a" "clipLibrary1.cel[0].cev[129].cevr";
connectAttr "animCurveTA239.a" "clipLibrary1.cel[0].cev[130].cevr";
connectAttr "animCurveTA240.a" "clipLibrary1.cel[0].cev[131].cevr";
connectAttr "animCurveTA241.a" "clipLibrary1.cel[0].cev[132].cevr";
connectAttr "animCurveTA242.a" "clipLibrary1.cel[0].cev[133].cevr";
connectAttr "animCurveTA243.a" "clipLibrary1.cel[0].cev[134].cevr";
connectAttr "animCurveTA244.a" "clipLibrary1.cel[0].cev[135].cevr";
connectAttr "animCurveTA245.a" "clipLibrary1.cel[0].cev[136].cevr";
connectAttr "animCurveTA246.a" "clipLibrary1.cel[0].cev[137].cevr";
connectAttr "animCurveTA247.a" "clipLibrary1.cel[0].cev[138].cevr";
connectAttr "animCurveTA248.a" "clipLibrary1.cel[0].cev[139].cevr";
connectAttr "animCurveTA249.a" "clipLibrary1.cel[0].cev[140].cevr";
connectAttr "animCurveTA250.a" "clipLibrary1.cel[0].cev[141].cevr";
connectAttr "animCurveTA251.a" "clipLibrary1.cel[0].cev[142].cevr";
connectAttr "animCurveTA252.a" "clipLibrary1.cel[0].cev[143].cevr";
connectAttr "animCurveTA253.a" "clipLibrary1.cel[0].cev[144].cevr";
connectAttr "animCurveTA254.a" "clipLibrary1.cel[0].cev[145].cevr";
connectAttr "animCurveTA255.a" "clipLibrary1.cel[0].cev[146].cevr";
connectAttr "animCurveTA256.a" "clipLibrary1.cel[0].cev[147].cevr";
connectAttr "animCurveTL85.a" "clipLibrary1.cel[0].cev[148].cevr";
connectAttr "animCurveTL86.a" "clipLibrary1.cel[0].cev[149].cevr";
connectAttr "animCurveTL87.a" "clipLibrary1.cel[0].cev[150].cevr";
connectAttr "animCurveTL88.a" "clipLibrary1.cel[0].cev[151].cevr";
connectAttr "animCurveTL89.a" "clipLibrary1.cel[0].cev[152].cevr";
connectAttr "animCurveTL90.a" "clipLibrary1.cel[0].cev[153].cevr";
connectAttr "animCurveTA257.a" "clipLibrary1.cel[0].cev[154].cevr";
connectAttr "animCurveTA258.a" "clipLibrary1.cel[0].cev[155].cevr";
connectAttr "animCurveTA259.a" "clipLibrary1.cel[0].cev[156].cevr";
connectAttr "animCurveTL91.a" "clipLibrary1.cel[0].cev[157].cevr";
connectAttr "animCurveTL92.a" "clipLibrary1.cel[0].cev[158].cevr";
connectAttr "animCurveTL93.a" "clipLibrary1.cel[0].cev[159].cevr";
connectAttr "animCurveTA260.a" "clipLibrary1.cel[0].cev[160].cevr";
connectAttr "animCurveTA261.a" "clipLibrary1.cel[0].cev[161].cevr";
connectAttr "animCurveTA262.a" "clipLibrary1.cel[0].cev[162].cevr";
connectAttr "animCurveTL94.a" "clipLibrary1.cel[0].cev[163].cevr";
connectAttr "animCurveTL95.a" "clipLibrary1.cel[0].cev[164].cevr";
connectAttr "animCurveTL96.a" "clipLibrary1.cel[0].cev[165].cevr";
connectAttr "animCurveTL97.a" "clipLibrary1.cel[0].cev[166].cevr";
connectAttr "animCurveTL98.a" "clipLibrary1.cel[0].cev[167].cevr";
connectAttr "animCurveTL99.a" "clipLibrary1.cel[0].cev[168].cevr";
connectAttr "animCurveTL100.a" "clipLibrary1.cel[0].cev[169].cevr";
connectAttr "animCurveTL101.a" "clipLibrary1.cel[0].cev[170].cevr";
connectAttr "animCurveTL102.a" "clipLibrary1.cel[0].cev[171].cevr";
connectAttr "animCurveTA263.a" "clipLibrary1.cel[0].cev[172].cevr";
connectAttr "animCurveTA264.a" "clipLibrary1.cel[0].cev[173].cevr";
connectAttr "animCurveTA265.a" "clipLibrary1.cel[0].cev[174].cevr";
connectAttr "animCurveTL103.a" "clipLibrary1.cel[0].cev[175].cevr";
connectAttr "animCurveTL104.a" "clipLibrary1.cel[0].cev[176].cevr";
connectAttr "animCurveTL105.a" "clipLibrary1.cel[0].cev[177].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of attackE.ma
