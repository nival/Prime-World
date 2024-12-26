//Maya ASCII 2008 scene
//Name: atackMoveB.ma
//Last modified: Tue, Nov 03, 2009 03:58:12 PM
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
createNode animClip -n "attackMoveSource2";
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
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU427";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[2:7]"  3 3 9 10 3 10;
	setAttr -s 8 ".kot[2:7]"  3 3 9 10 3 10;
createNode animCurveTA -n "animCurveTA1109";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -5.9044848404027581 4 -67.345073217495383 
		6 39.438750358026958 14 34.487530638080187 18 39.045042085615165 23 39.767023671090612 
		32 45.44159596142385 44 39.53428110495291;
	setAttr -s 8 ".kit[0:7]"  1 10 10 10 9 10 3 10;
	setAttr -s 8 ".kot[0:7]"  1 10 10 10 9 10 3 10;
	setAttr -s 8 ".kix[0:7]"  0.099872969090938568 0.13333334028720856 
		0.066666662693023682 0.26666665077209473 0.13333335518836975 0.16666662693023682 
		0.30000007152557373 0.39999997615814209;
	setAttr -s 8 ".kiy[0:7]"  -0.0202031210064888 0.52759253978729248 
		0.35546284914016724 -0.0045810029841959476 0.0409531369805336 0 0 -0.10310209542512894;
	setAttr -s 8 ".kox[0:7]"  0.09987301379442215 0.066666662693023682 
		0.26666665077209473 0.13333335518836975 0.16666662693023682 0.30000007152557373 0.39999997615814209 
		0.39999997615814209;
	setAttr -s 8 ".koy[0:7]"  -0.020203126594424248 0.26379624009132385 
		1.4218513965606689 -0.0022905019577592611 0.051191400736570358 0 0 -0.10310209542512894;
createNode animCurveTA -n "animCurveTA1110";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 58.807719017332971 4 37.65091915175492 
		6 -13.463328626407701 14 2.5184500334393332 18 26.472435454068016 23 31.712505502351856 
		32 31.937860051021964 44 32.600909957006799;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 9 10 3 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 9 10 3 10;
createNode animCurveTA -n "animCurveTA1111";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 36.369502687708085 4 29.726589093772084 
		6 33.36653343297364 14 33.733108261100796 18 43.450692876967182 23 33.676630345052367 
		32 18.724659360824806 44 16.651520328974982;
	setAttr -s 8 ".kit[0:7]"  1 10 10 10 9 10 3 10;
	setAttr -s 8 ".kot[0:7]"  1 10 10 10 9 10 3 10;
	setAttr -s 8 ".kix[0:7]"  0.033172678202390671 0.13333334028720856 
		0.066666662693023682 0.26666665077209473 0.13333335518836975 0.16666662693023682 
		0.30000007152557373 0.39999997615814209;
	setAttr -s 8 ".kiy[0:7]"  0.0127108134329319 -0.034941136837005615 
		0 0 -0.00043810036731883883 -0.15412519872188568 0 0;
	setAttr -s 8 ".kox[0:7]"  0.099839314818382263 0.066666662693023682 
		0.26666665077209473 0.13333335518836975 0.16666662693023682 0.30000007152557373 0.39999997615814209 
		0.39999997615814209;
	setAttr -s 8 ".koy[0:7]"  0.038255542516708374 -0.017470566555857658 
		0 0 -0.00054762524086982012 -0.27742549777030945 0 0;
createNode animCurveTA -n "animCurveTA1112";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -45.122442211365566 4 -96.935477567170466 
		6 -72.482795588127701 14 -72.482795588127701 18 -79.711276513490304 23 -83.739512497966473 
		32 -87.582586884797436 44 -87.582586884797436;
	setAttr -s 8 ".kit[0:7]"  1 10 10 10 9 10 3 10;
	setAttr -s 8 ".kot[0:7]"  1 10 10 10 9 10 3 10;
	setAttr -s 8 ".kix[0:7]"  0.12522487342357635 0.13333334028720856 
		0.066666662693023682 0.26666665077209473 0.13333335518836975 0.16666662693023682 
		0.30000007152557373 0.39999997615814209;
	setAttr -s 8 ".kiy[0:7]"  -0.16572846472263336 -0.31835219264030457 
		0 0 -0.087318584322929382 -0.049064371734857559 0 0;
	setAttr -s 8 ".kox[0:7]"  0.091892562806606293 0.066666662693023682 
		0.26666665077209473 0.13333335518836975 0.16666662693023682 0.30000007152557373 0.39999997615814209 
		0.39999997615814209;
	setAttr -s 8 ".koy[0:7]"  -0.12161493301391602 -0.1591760665178299 
		0 0 -0.10914818942546844 -0.088315911591053009 0 0;
createNode animCurveTA -n "animCurveTA1113";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1114";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1115";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1116";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -1.2317224292933964 4 -1.1926536499213169 
		6 -1.1926536499213169 14 -1.1926536499213169 18 -1.0825755607147456 23 -0.99845831414959596 
		32 -0.90666238496249552 44 -0.90666238496249552;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1117";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -2.3167854357758224 4 -1.1961381530463304 
		6 -1.1961381530463304 14 -1.1961381530463304 18 1.6251155413354244 23 1.2305231465523319 
		32 -0.14300750254877909 44 -0.14300750254877909;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1118";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 6.1206310772034049 4 10.371046052828191 
		6 -4.791960185015478 14 -4.791960185015478 18 -3.2164608426483019 23 -2.0125276415102409 
		32 -0.69869282260852494 44 -0.69869282260852494;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1119";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -1.5837738651021782 4 -20.604608392586229 
		6 -19.124861671249963 14 -19.124861671249963 18 -6.5419901008113097 23 3.0733338660512661 
		32 13.566397626420638 44 13.566397626420638;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1120";
	setAttr ".tan" 3;
	setAttr -s 8 ".ktv[0:7]"  0 29.390444190844978 4 84.409400100336697 
		6 9.2310662164528452 14 2.3924934646512446 18 -34.925913600349517 23 -30.899652556055152 
		32 -10.511380425278997 44 -14.474463091487671;
	setAttr -s 8 ".kit[0:7]"  1 10 3 3 9 10 3 10;
	setAttr -s 8 ".kot[0:7]"  1 10 3 3 9 10 3 10;
	setAttr -s 8 ".kix[0:7]"  0.098998740315437317 0.13333334028720856 
		0.066666662693023682 0.26666665077209473 0.13333335518836975 0.16666662693023682 
		0.30000007152557373 0.39999997615814209;
	setAttr -s 8 ".kiy[0:7]"  0.065068379044532776 -0.23456501960754395 
		0 0 -0.25824785232543945 0.15218351781368256 0 -0.069168843328952789;
	setAttr -s 8 ".kox[0:7]"  0.098998785018920898 0.066666662693023682 
		0.26666665077209473 0.13333335518836975 0.16666662693023682 0.30000007152557373 0.39999997615814209 
		0.39999997615814209;
	setAttr -s 8 ".koy[0:7]"  0.065068401396274567 -0.11728249490261078 
		0 0 -0.32280969619750977 0.27393046021461487 0 -0.069168843328952789;
createNode animCurveTA -n "animCurveTA1121";
	setAttr ".tan" 3;
	setAttr -s 8 ".ktv[0:7]"  0 39.175573872606115 4 -17.838162850745562 
		6 52.618406143147403 14 55.260152558428558 18 31.251110059817172 23 27.509707943207587 
		32 29.033342295222326 44 28.826393195295356;
	setAttr -s 8 ".kit[1:7]"  10 3 3 9 10 3 10;
	setAttr -s 8 ".kot[1:7]"  10 3 3 9 10 3 10;
createNode animCurveTA -n "animCurveTA1122";
	setAttr ".tan" 3;
	setAttr -s 8 ".ktv[0:7]"  0 44.934254123355444 4 56.605419878403126 
		6 39.17546312519454 14 32.5382972410127 18 -2.8326920224004741 23 -3.974422069812904 
		32 6.5847131855268461 44 4.3502300737951041;
	setAttr -s 8 ".kit[1:7]"  10 3 3 9 10 3 10;
	setAttr -s 8 ".kot[1:7]"  10 3 3 9 10 3 10;
createNode animCurveTA -n "animCurveTA1123";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -44.719915167449514 4 -48.674541848530694 
		6 -94.697914078394874 14 -94.697914078394874 18 -53.38374460834072 23 -51.201373137683468 
		32 -59.684677024606373 44 -59.684677024606373;
	setAttr -s 8 ".kit[0:7]"  9 10 10 10 9 10 3 10;
	setAttr -s 8 ".kot[0:7]"  9 10 10 10 9 10 3 10;
createNode animCurveTA -n "animCurveTA1124";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1125";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1126";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1127";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 -7.8079750080638295 6 -13.058569190429449 
		14 -13.058569190429449 18 -1.2222106508895205 23 0.55533902921614597 32 -0.19158875421948376 
		44 -0.19158875421948376;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1128";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 12.057717375248709 6 -10.606555938113802 
		14 -10.606555938113802 18 -8.1156564266663871 23 -7.7415804541735627 32 -7.898767459478834 
		44 -7.898767459478834;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1129";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 -10.976680194724748 6 15.108626529658169 
		14 15.108626529658169 18 3.3683894462214257 23 1.6052749952180825 32 2.3461370896484395 
		44 2.3461370896484395;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1130";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 2.094427936025169 4 -14.824185954254862 
		6 -18.904346947311801 14 -19.879826341049746 18 -11.679782986899292 23 -5.4136398981592961 
		32 1.4245112294344 44 1.4245112294344;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 9 10 3 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 9 10 3 10;
createNode animCurveTA -n "animCurveTA1131";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 2.2351294143535361 4 1.7591293557368488 
		6 1.6294964908372624 14 -0.45230705997532605 18 0.4478850631488287 23 1.1357756495238669 
		32 1.8864606807611757 44 1.8864606807611757;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1132";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0.45754839295120231 4 -1.7594426093214925 
		6 -1.8801318894369652 14 -6.9752651321989472 18 -6.5968484526535232 23 -6.3076776528575422 
		32 -5.9921097590926697 44 -5.9921097590926697;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTL -n "animCurveTL415";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0.00025694328101411035 4 -0.022253170030878934 
		6 -0.022253170030878934 14 -0.022253170030878934 18 -0.0017824387328361189 23 0.0012917955885654447 
		32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTL -n "animCurveTL416";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 -1.1704348347801004 6 -1.1704348347801004 
		14 -1.1704348347801004 18 -0.71993425682729617 23 -0.3756798470610947 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTL -n "animCurveTL417";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -0.12122743177477754 4 -0.22435647486370341 
		6 -0.22435647486370341 14 -0.22435647486370341 18 -0.18523717639946605 23 -0.15534378251889835 
		32 -0.12272155611893799 44 -0.12272155611893799;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTL -n "animCurveTL418";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 -0.12960819856623565 6 -0.12960819856623565 
		14 -0.12960819856623565 18 -0.067020273756464799 23 -0.019193099432083097 32 0.033 
		44 0.033;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTL -n "animCurveTL419";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 -0.71549804805118578 6 -0.71549804805118578 
		14 -0.71549804805118578 18 -0.42194068409654256 23 -0.22329116897310891 32 -0.016 
		44 -0.016;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTL -n "animCurveTL420";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0.14866791985076391 4 0.38285174708587016 
		6 0.38285174708587016 14 0.38285174708587016 18 0.27544437715960352 23 0.19336798751544715 
		32 0.10379921435641129 44 0.10379921435641129;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1133";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -7.6108200257106455 4 22.304367496154381 
		6 -5.0100106401867697 14 -4.8905797988826221 18 -7.8088652573692849 23 -12.357365301469688 
		32 -18.178217858042064 44 -18.178217858042064;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1134";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -1.2143438271734348 4 10.269726703901854 
		6 -3.5721560165804851 14 -2.6197995524357558 18 9.4296247598990099 23 5.1044699702711913 
		32 -4.6186256351197352 44 -4.6186256351197352;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1135";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 11.936000000000002 4 1.7732350554772667 
		6 20.480380476199795 14 22.931111840696705 18 11.275534158130897 23 2.2267312964843322 
		32 -7.7006231053605507 44 -7.7006231053605507;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTL -n "animCurveTL421";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -0.12426724926881808 4 -0.11344193402412064 
		6 -0.24130478537525993 14 -0.26173672438721696 18 -0.18803865626492802 23 -0.11935397535864806 
		32 -0.071558932843931666 44 -0.062545592999319929;
	setAttr -s 8 ".kit[0:7]"  9 10 10 10 9 10 3 10;
	setAttr -s 8 ".kot[0:7]"  9 10 10 10 9 10 3 10;
createNode animCurveTL -n "animCurveTL422";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 -0.41045340443691747 6 -0.56463661380597685 
		14 -0.46000418629555911 18 -0.25852169327737151 23 0.062599984447280141 32 0.011835954993039591 
		44 -0.032867286470989195;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTL -n "animCurveTL423";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0.047886994693685757 4 0.031339974139486915 
		6 0.035969524118697901 14 0.045706675818127894 18 0.14111333941812751 23 0.11639947339476608 
		32 -0.0038103144541476973 44 -0.0098384205421270955;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1136";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -10.91672111902791 2 -1.0502232201839465 
		4 -1.0502232201839465 6 -1.0502232201839465 14 -1.0502232201839465 18 -23.625023259410092 
		23 -25.590668618635455 32 -25.590668618635455 44 -25.590668618635455;
	setAttr -s 9 ".kit[5:8]"  9 10 3 10;
	setAttr -s 9 ".kot[5:8]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1137";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 6 0 14 0 18 0 23 0 32 0 44 
		0;
	setAttr -s 9 ".kit[5:8]"  9 10 3 10;
	setAttr -s 9 ".kot[5:8]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1138";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 54.531249688760838 2 0 4 0 6 0 14 0 18 
		16.8739452277681 23 0 32 0 44 0;
	setAttr -s 9 ".kit[5:8]"  9 10 3 10;
	setAttr -s 9 ".kot[5:8]"  9 10 3 10;
createNode animCurveTL -n "animCurveTL424";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0.14433764449692274 2 0 4 0 6 0 14 0 
		18 0.10799102515747247 23 0 32 0 44 0;
	setAttr -s 9 ".kit[5:8]"  9 10 3 10;
	setAttr -s 9 ".kot[5:8]"  9 10 3 10;
createNode animCurveTL -n "animCurveTL425";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0.375 2 -0.62964667162485854 4 -0.62964667162485854 
		6 -0.62964667162485854 14 -0.62964667162485854 18 -0.29984979411135237 23 0.15953969092363035 
		32 0.15953969092363035 44 0.15953969092363035;
	setAttr -s 9 ".kit[0:8]"  2 10 10 10 10 9 10 3 
		10;
	setAttr -s 9 ".kot[0:8]"  2 10 10 10 10 9 10 3 
		10;
createNode animCurveTL -n "animCurveTL426";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 -0.049724280172069299 2 -0.04 4 -0.04 
		6 -0.04 14 -0.04 18 -0.04 23 -0.04 32 -0.04 44 -0.04;
	setAttr -s 9 ".kit[5:8]"  9 10 3 10;
	setAttr -s 9 ".kot[5:8]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1139";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 13.771049833755342 4 13.448095463381762 
		6 11.880229891661756 14 11.880229891661756 18 11.880229891661756 23 11.880229891661756 
		32 11.880229891661756 44 11.880229891661756;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1140";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1141";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -0.036768619302931224 4 -0.030488493928678986 
		6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTL -n "animCurveTL427";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTL -n "animCurveTL428";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -0.191 4 -0.1938473426631496 6 -0.20007920657257083 
		14 -0.20007920657257083 18 -0.20007920657257083 23 -0.20007920657257083 32 -0.20007920657257083 
		44 -0.20007920657257083;
	setAttr -s 8 ".kit[0:7]"  2 10 10 10 9 10 3 10;
	setAttr -s 8 ".kot[0:7]"  2 10 10 10 9 10 3 10;
createNode animCurveTL -n "animCurveTL429";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0.050237714532295197 4 0.05849382271603186 
		6 0.098575236578624326 14 0.098575236578624326 18 0.098575236578624326 23 0.098575236578624326 
		32 0.098575236578624326 44 0.098575236578624326;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU428";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 4 1 6 1 14 1 18 1 23 1 32 1 44 1;
	setAttr -s 8 ".kit[6:7]"  3 9;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 9 5 3 5;
createNode animCurveTA -n "animCurveTA1142";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1143";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1144";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTL -n "animCurveTL430";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -0.808 4 -0.80995458038520662 6 -0.80995458038520662 
		14 -0.80995458038520662 18 -0.81868354363982954 23 -0.81999443376260794 32 -0.81944359671150613 
		44 -0.81944359671150613;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTL -n "animCurveTL431";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0.0050335929996589528 6 0.0050335929996589528 
		14 0.0050335929996589528 18 0.027513122961843321 23 0.030889032886697594 32 0.029470472912715796 
		44 0.029470472912715796;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTL -n "animCurveTL432";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 -0.017788820199852954 6 -0.017788820199852954 
		14 -0.017788820199852954 18 -0.037998705797115367 23 -0.053442286845925072 32 -0.070295643204272437 
		44 -0.070295643204272437;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU429";
	setAttr ".tan" 9;
	setAttr -s 8 ".ktv[0:7]"  0 1 4 1 6 1 14 1 18 1 23 1 32 1 44 1;
	setAttr -s 8 ".kit[6:7]"  3 9;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 9 5 3 5;
createNode animCurveTA -n "animCurveTA1145";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 -1.5103668316710797 6 -1.5103668316710797 
		14 -1.5103668316710797 18 -4.5512668383521167 23 -5.0079402801023347 32 -4.8160457500419067 
		44 -4.8160457500419067;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1146";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1147";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTL -n "animCurveTL433";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -0.808 4 -0.8074046201914743 6 -0.8074046201914743 
		14 -0.8074046201914743 18 -0.80474571267838368 23 -0.80434640575134042 32 -0.80451419482641451 
		44 -0.80451419482641451;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTL -n "animCurveTL434";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTL -n "animCurveTL435";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 -0.0014614209598859463 6 -0.0014614209598859463 
		14 -0.0014614209598859463 18 -0.0079879828526226541 23 -0.0089681227750922476 32 
		-0.0085562672260772743 44 -0.0085562672260772743;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU430";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU431";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 45 4 45 6 45 14 45 18 45 23 45 32 45 
		44 45;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU432";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 45 4 45 6 45 14 45 18 45 23 45 32 45 
		44 45;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU433";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 45 4 45 6 45 14 45 18 45 23 45 32 45 
		44 45;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1148";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1149";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 -12.178188092746277 4 0 6 0 14 0 
		18 0 23 0 32 0 44 0;
	setAttr -s 9 ".kit[5:8]"  9 10 3 10;
	setAttr -s 9 ".kot[5:8]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU434";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU435";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 45 4 45 6 45 14 45 18 45 23 45 32 45 
		44 45;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU436";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 45 4 45 6 45 14 45 18 45 23 45 32 45 
		44 45;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU437";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 45 4 45 6 45 14 45 18 45 23 45 32 45 
		44 45;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1150";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1151";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 16.540080570599645 14 10.09884814238748 
		18 0 23 -1.1593065602608812 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU438";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU439";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU440";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU441";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU442";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU443";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU444";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU445";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU446";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU447";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU448";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU449";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1152";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1153";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1154";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU450";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU451";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU452";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU453";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU454";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU455";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU456";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU457";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU458";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU459";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU460";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTU -n "animCurveTU461";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1155";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1156";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1157";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 14 0 18 0 23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1158";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -9.5230312705234752 4 -44.382477037836935 
		6 -61.410676068997681 14 -63.413662925281294 18 -43.292724248578097 23 -25.763626144927013 
		32 -2.1028115935850584 44 -5.8382275551355809;
	setAttr -s 8 ".kit[2:7]"  3 3 9 10 3 10;
	setAttr -s 8 ".kot[2:7]"  3 3 9 10 3 10;
createNode animCurveTA -n "animCurveTA1159";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 7.7034312702563614 4 24.383386201955549 
		6 -16.386484802704459 14 -20.175427271687944 18 1.4249143059860685 23 2.3854120312615583 
		32 -2.1808759502178647 44 -2.3136539176186792;
	setAttr -s 8 ".kit[2:7]"  3 3 9 10 3 10;
	setAttr -s 8 ".kot[2:7]"  3 3 9 10 3 10;
createNode animCurveTA -n "animCurveTA1160";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 26.100751043370952 4 41.275778843908384 
		6 -28.626381756466053 14 -34.208368562114714 18 -3.2705255475668547 23 -4.0329070346074127 
		32 -13.75599965677022 44 -13.887028133305018;
	setAttr -s 8 ".kit[2:7]"  3 3 9 10 3 10;
	setAttr -s 8 ".kot[2:7]"  3 3 9 10 3 10;
createNode animCurveTA -n "animCurveTA1161";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -0.46379212099681288 4 0 6 0 14 0 18 
		12.762039851388256 23 14.678605536398882 32 13.873263178484903 44 13.873263178484903;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1162";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -1.1953227076810968 4 0 6 0 14 0 18 0 
		23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "animCurveTA1163";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 1.9438407078130946 4 0 6 0 14 0 18 0 
		23 0 32 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 3 10;
	setAttr -s 8 ".kot[4:7]"  9 10 3 10;
createNode animCurveTA -n "tank_M_backCloth_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 48.119986885981547 12 -17.394536959307814 
		18 31.305566636231362 24 -22.875658510547836 34 14.669046141255823 44 0;
	setAttr -s 7 ".kit[4:6]"  3 10 10;
	setAttr -s 7 ".kot[4:6]"  3 10 10;
createNode animCurveTA -n "tank_M_backCloth_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 7.0553106977763225 12 -0.020349356448297971 
		18 1.8103187128017797 24 0 44 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
createNode animCurveTA -n "tank_M_backCloth_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 -1.2022279078700209 12 -4.9382113136201635 
		18 -1.6795635606371968 24 0 44 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
createNode animCurveTA -n "tank_M_hang_ctrl_rotateZ2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -7.6359447996384162 6 25.031834653642733 
		10 54.717168693502757 14 105.88395739951264 19 27.697119395571633 24 -4.2521769360203114 
		34 6.6061324326086899 44 -7.6359447996384162;
createNode animCurveTA -n "tank_M_hang_ctrl_rotateY2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -35.260196151694586 6 40.937559055737701 
		10 -22.027589723928639 14 -42.947415922337449 19 8.6519943689612582 24 3.1250789503327323 
		34 -23.61141056651811 44 -35.260196151694586;
createNode animCurveTA -n "tank_M_hang_ctrl_rotateX2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 68.744635926587719 6 -9.5174165648569833 
		10 5.5305186208823249 14 -3.9382296525682126 19 10.414919512840706 24 -28.749576608833376 
		34 23.794017541711959 44 68.744635926587719;
createNode animCurveTA -n "tank_R_hang_ctrl_rotateZ2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -7.6359447996384162 6 25.031834653642733 
		10 54.717168693502757 14 105.88395739951264 19 27.697119395571633 24 -4.2521769360203114 
		34 6.6061324326086899 44 -7.6359447996384162;
createNode animCurveTA -n "tank_R_hang_ctrl_rotateY2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -35.260196151694586 6 40.937559055737701 
		10 -22.027589723928639 14 -42.947415922337449 19 8.6519943689612582 24 3.1250789503327323 
		34 -23.61141056651811 44 -35.260196151694586;
createNode animCurveTA -n "tank_R_hang_ctrl_rotateX2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 68.744635926587719 6 -9.5174165648569833 
		10 5.5305186208823249 14 -3.9382296525682126 19 10.414919512840706 24 -28.749576608833376 
		34 23.794017541711959 44 68.744635926587719;
createNode animCurveTA -n "tank_L_hang_ctrl_rotateZ2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -7.6359447996384162 6 25.031834653642733 
		10 54.717168693502757 14 105.88395739951264 19 27.697119395571633 24 -4.2521769360203114 
		34 6.6061324326086899 44 -7.6359447996384162;
createNode animCurveTA -n "tank_L_hang_ctrl_rotateY2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -35.260196151694586 6 40.937559055737701 
		10 -22.027589723928639 14 -42.947415922337449 19 8.6519943689612582 24 3.1250789503327323 
		34 -23.61141056651811 44 -35.260196151694586;
createNode animCurveTA -n "tank_L_hang_ctrl_rotateX2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 68.744635926587719 6 -9.5174165648569833 
		10 5.5305186208823249 14 -3.9382296525682126 19 10.414919512840706 24 -28.749576608833376 
		34 23.794017541711959 44 68.744635926587719;
createNode animCurveTA -n "tank_R_flag_3_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 18.08 24 18.08 44 18.08;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTA -n "tank_R_flag_3_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.0336 24 -0.0336 44 -0.0336;
	setAttr -s 3 ".kit[1:2]"  2 10;
	setAttr -s 3 ".kot[1:2]"  2 10;
createNode animCurveTA -n "tank_R_flag_3_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 24 0 44 0;
	setAttr -s 3 ".kit[1:2]"  2 10;
	setAttr -s 3 ".kot[1:2]"  2 10;
createNode animCurveTA -n "tank_R_flag_2_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 18.373158409800983 24 18.373158409800983 
		44 18.373158409800983;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTA -n "tank_R_flag_2_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 24 0 44 0;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTA -n "tank_R_flag_2_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 24 0 44 0;
	setAttr -s 3 ".kit[1:2]"  2 10;
	setAttr -s 3 ".kot[1:2]"  2 10;
createNode animCurveTA -n "tank_R_flag_1_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 18.373158409800983 24 18.373158409800983 
		44 18.373158409800983;
	setAttr -s 3 ".kit[1:2]"  2 10;
	setAttr -s 3 ".kot[1:2]"  2 10;
createNode animCurveTA -n "tank_R_flag_1_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 24 0 44 0;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTA -n "tank_R_flag_1_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 24 0 44 0;
	setAttr -s 3 ".kit[1:2]"  2 10;
	setAttr -s 3 ".kot[1:2]"  2 10;
createNode animCurveTA -n "tank_L_flag_1_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 18.373158409800983 24 18.373158409800983 
		44 18.373158409800983;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTA -n "tank_L_flag_1_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 24 0 44 0;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTA -n "tank_L_flag_1_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 24 0 44 0;
	setAttr -s 3 ".kit[1:2]"  2 10;
	setAttr -s 3 ".kot[1:2]"  2 10;
createNode animCurveTA -n "tank_L_flag_2_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 18.373158409800983 24 18.373158409800983 
		44 18.373158409800983;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTA -n "tank_L_flag_2_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 24 0 44 0;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTA -n "tank_L_flag_2_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 24 0 44 0;
	setAttr -s 3 ".kit[1:2]"  2 10;
	setAttr -s 3 ".kot[1:2]"  2 10;
createNode animCurveTA -n "tank_L_flag_3_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 18.373158409800983 24 18.373158409800983 
		44 18.373158409800983;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTA -n "tank_L_flag_3_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 24 0 44 0;
	setAttr -s 3 ".kit[1:2]"  2 10;
	setAttr -s 3 ".kot[1:2]"  2 10;
createNode animCurveTA -n "tank_L_flag_3_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 24 0 44 0;
	setAttr -s 3 ".kit[1:2]"  2 10;
	setAttr -s 3 ".kot[1:2]"  2 10;
createNode animCurveTA -n "tank_M_backFeature_ctrl_rotateZ2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -5.4432506707315573 6 -5.4432506707315573 
		10 23.229500928324303 14 -14.267779510826728 24 -5.4432506707315573 44 -5.4432506707315573;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
createNode animCurveTA -n "tank_M_backFeature_ctrl_rotateY2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 -2.0511358308540077 14 -1.7546768459025737 
		24 0 44 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
createNode animCurveTA -n "tank_M_backFeature_ctrl_rotateX2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1.4808130565433952 6 1.4808130565433952 
		10 -3.3461568053371931 14 -0.74830064241134586 24 1.4808130565433952 44 1.4808130565433952;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
createNode animCurveTA -n "tank_M_frontCloth_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -13.113682797820777 6 21.875953260759218 
		12 -35.579429492268375 18 13.503935416416111 24 -19.497076293860374 34 13.394386916125301 
		44 -13.113682797820777;
	setAttr -s 7 ".kit[4:6]"  3 10 10;
	setAttr -s 7 ".kot[4:6]"  3 10 10;
createNode animCurveTA -n "tank_M_frontCloth_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -4.0919497789234391 6 14.599094612560746 
		12 -6.7692107092805802 18 -2.4248292718611522 24 -0.20901571515995418 34 -11.045329220054834 
		44 -4.0919497789234391;
	setAttr -s 7 ".kit[4:6]"  3 10 10;
	setAttr -s 7 ".kot[4:6]"  3 10 10;
createNode animCurveTA -n "tank_M_frontCloth_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 31.178362171912408 6 13.363693772090372 
		12 11.808017400449735 18 -23.449389624933939 24 31.418279304805743 34 15.295106269582567 
		44 31.178362171912408;
	setAttr -s 7 ".kit[4:6]"  3 10 10;
	setAttr -s 7 ".kot[4:6]"  3 10 10;
createNode lightLinker -n "lightLinker1";
	setAttr -s 4 ".lnk";
	setAttr -s 4 ".slnk";
select -ne :time1;
	setAttr -av -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 44;
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
connectAttr "attackMoveSource2.cl" "clipLibrary2.sc[0]";
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
// End of atackMoveB.ma
