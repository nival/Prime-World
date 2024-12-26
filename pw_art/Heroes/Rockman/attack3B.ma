//Maya ASCII 2008 scene
//Name: attack3B.ma
//Last modified: Mon, Nov 02, 2009 01:09:43 PM
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
createNode animClip -n "attack3Source2";
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
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
	setAttr -s 8 ".kit[4:7]"  9 10 10 10;
	setAttr -s 8 ".kot[4:7]"  9 10 10 10;
createNode animCurveTU -n "animCurveTU427";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTA -n "animCurveTA1109";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 39.53428110495291 2 46.584221033715281 
		4 49.332450213946963 6 -64.666317826069744 18 -55.383321508029454 24 28.159947700401247 
		30 43.280704670853325 44 39.53428110495291;
	setAttr -s 8 ".kit[3:7]"  3 1 10 10 10;
	setAttr -s 8 ".kot[3:7]"  3 1 10 10 10;
	setAttr -s 8 ".kix[4:7]"  0.4311957061290741 0.19999998807907104 
		0.19999998807907104 0.46666669845581055;
	setAttr -s 8 ".kiy[4:7]"  0.46209517121315002 0.86100608110427856 
		0.059555865824222565 -0.065387427806854248;
	setAttr -s 8 ".kox[4:7]"  0.23119056224822998 0.19999998807907104 
		0.46666669845581055 0.46666669845581055;
	setAttr -s 8 ".koy[4:7]"  0.24775779247283936 0.86100608110427856 
		0.13896369934082031 -0.065387427806854248;
createNode animCurveTA -n "animCurveTA1110";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 32.600909957006799 2 19.562234583921725 
		4 -1.6565743853512693 6 51.00620005305214 18 49.762613479678862 24 37.729923943406355 
		30 32.601734627959743 44 32.600909957006799;
	setAttr -s 8 ".kit[3:7]"  3 9 10 10 10;
	setAttr -s 8 ".kot[3:7]"  3 9 10 10 10;
createNode animCurveTA -n "animCurveTA1111";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 16.651520328974982 2 7.3871307150625576 
		4 -57.842122593933709 6 -23.967681767226196 18 -8.1786051842557708 24 15.632121106030304 
		30 19.139655626023359 44 16.651520328974982;
	setAttr -s 8 ".kit[4:7]"  1 10 10 10;
	setAttr -s 8 ".kot[4:7]"  1 10 10 10;
	setAttr -s 8 ".kix[4:7]"  0.41252657771110535 0.19999998807907104 
		0.19999998807907104 0.46666669845581055;
	setAttr -s 8 ".kiy[4:7]"  0.21741171181201935 0.23839679360389709 
		0 0;
	setAttr -s 8 ".kox[4:7]"  0.21252459287643433 0.19999998807907104 
		0.46666669845581055 0.46666669845581055;
	setAttr -s 8 ".koy[4:7]"  0.11200569570064545 0.23839679360389709 
		0 0;
createNode animCurveTA -n "animCurveTA1112";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -87.582586884797436 2 -43.332992241027348 
		4 -43.332992241027348 6 -43.332992241027348 18 -50.764911654616576 24 -71.939348786818996 
		30 -82.041796743659674 44 -87.582586884797436;
createNode animCurveTA -n "animCurveTA1113";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTA -n "animCurveTA1114";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTA -n "animCurveTA1115";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTA -n "animCurveTA1116";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -0.90666238496249552 2 -0.90666238496249552 
		4 12.252729439223172 6 -33.459849845903626 18 -29.84054198268597 24 -13.339028208625185 
		30 -0.90666238496249552 44 -0.90666238496249552;
createNode animCurveTA -n "animCurveTA1117";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -0.14300750254877909 2 -0.14300750254877909 
		4 -14.018089027829115 6 -26.709416640231694 18 -20.298807117813478 24 -8.5605068925278349 
		30 -0.14300750254877909 44 -0.14300750254877909;
createNode animCurveTA -n "animCurveTA1118";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -0.69869282260852494 2 -0.69869282260852494 
		4 14.730130785696719 6 -23.827717531254965 18 -22.109966658273741 24 -11.404329740441135 
		30 -0.69869282260852494 44 -0.69869282260852494;
createNode animCurveTA -n "animCurveTA1119";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 13.566397626420638 2 13.566397626420638 
		4 -18.7968147408044 6 -4.3452811876355089 18 3.2082597332769791 24 9.5068085309232409 
		30 13.566397626420638 44 13.566397626420638;
createNode animCurveTA -n "animCurveTA1120";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -14.474463091487671 2 28.864353809308511 
		4 30.199791382699878 6 -61.611517649242138 18 -50.297906148216832 24 8.9666302202364712 
		30 -8.3997080786007121 44 -14.474463091487671;
	setAttr -s 8 ".kit[3:7]"  1 1 10 10 10;
	setAttr -s 8 ".kot[3:7]"  1 1 10 10 10;
	setAttr -s 8 ".kix[3:7]"  0.06470528244972229 0.42987346649169922 
		0.19999998807907104 0.19999998807907104 0.46666669845581055;
	setAttr -s 8 ".kiy[3:7]"  0.029923615977168083 0.37130185961723328 
		0.36563074588775635 -0.12273726612329483 -0.10602447390556335;
	setAttr -s 8 ".kox[3:7]"  0.39803814888000488 0.22986854612827301 
		0.19999998807907104 0.46666669845581055 0.46666669845581055;
	setAttr -s 8 ".koy[3:7]"  0.18407678604125977 0.19854831695556641 
		0.36563074588775635 -0.28638699650764465 -0.10602447390556335;
createNode animCurveTA -n "animCurveTA1121";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 28.826393195295356 2 18.818811475665576 
		4 0.15042476214250214 6 52.080041215187173 18 52.201830889145526 24 31.299214263072663 
		30 30.550709957699315 44 28.826393195295356;
createNode animCurveTA -n "animCurveTA1122";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 4.3502300737951041 2 6.2888498862645683 
		4 -43.410502471381001 6 -17.347728035456011 18 -6.9957874472681505 24 15.432002509913467 
		30 7.7524444967789075 44 4.3502300737951041;
	setAttr -s 8 ".kit[3:7]"  1 1 10 10 10;
	setAttr -s 8 ".kot[3:7]"  1 1 10 10 10;
	setAttr -s 8 ".kix[3:7]"  0.093606621026992798 0.41313138604164124 
		0.19999998807907104 0.19999998807907104 0.46666669845581055;
	setAttr -s 8 ".kiy[3:7]"  0.059994842857122421 0.19787697494029999 
		0.12870259582996368 -0.058024019002914429 -0.059379842132329941;
	setAttr -s 8 ".kox[3:7]"  0.42694738507270813 0.21312923729419708 
		0.19999998807907104 0.46666669845581055 0.46666669845581055;
	setAttr -s 8 ".koy[3:7]"  0.27364113926887512 0.10208225250244141 
		0.12870259582996368 -0.13538940250873566 -0.059379842132329941;
createNode animCurveTA -n "animCurveTA1123";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -59.684677024606373 2 -30.548706441816798 
		4 -30.548706441816798 6 -30.548706441816798 18 -35.442224359392497 24 -49.384448707277002 
		30 -54.225002805764767 44 -59.684677024606373;
createNode animCurveTA -n "animCurveTA1124";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTA -n "animCurveTA1125";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTA -n "animCurveTA1126";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTA -n "animCurveTA1127";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -0.19158875421948376 2 -18.346770300215834 
		4 -28.495987734150606 6 -28.495987734150606 18 -23.742135992000236 24 -10.197837615104445 
		30 -0.19158875421948376 44 -0.19158875421948376;
createNode animCurveTA -n "animCurveTA1128";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -7.898767459478834 2 -7.9495702044888352 
		4 -6.5124296342561498 6 -6.5124296342561498 18 -6.8398632822150063 24 -7.3693153708469197 
		30 -7.898767459478834 44 -7.898767459478834;
createNode animCurveTA -n "animCurveTA1129";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 2.3461370896484395 2 4.3457637498037993 
		4 2.0804643414171888 6 2.0804643414171888 18 2.1432125370834512 24 2.2446748133659451 
		30 2.3461370896484395 44 2.3461370896484395;
createNode animCurveTA -n "animCurveTA1130";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 1.4245112294344 2 1.4245112294344 4 1.4245112294344 
		6 1.4245112294344 18 1.4245112294344 24 1.4245112294344 30 1.4245112294344 44 1.4245112294344;
createNode animCurveTA -n "animCurveTA1131";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 1.8864606807611757 2 1.8864606807611757 
		4 1.8864606807611757 6 1.8864606807611757 18 1.8864606807611757 24 1.8864606807611757 
		30 1.8864606807611757 44 1.8864606807611757;
createNode animCurveTA -n "animCurveTA1132";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -5.9921097590926697 2 -5.9921097590926697 
		4 -5.9921097590926697 6 -5.9921097590926697 18 -5.9921097590926697 24 -5.9921097590926697 
		30 -5.9921097590926697 44 -5.9921097590926697;
createNode animCurveTL -n "animCurveTL415";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0.027438774305166239 4 -0.051638106537319352 
		6 -0.051638106537319352 18 -0.04296525315694999 24 -0.092152709115196657 30 0 44 
		0;
createNode animCurveTL -n "animCurveTL416";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0.012233066278822792 4 -0.0061005916892951919 
		6 -0.0061005916892951919 18 -0.0046597170661040162 24 0.023212632680748913 30 0 44 
		0;
createNode animCurveTL -n "animCurveTL417";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -0.12272155611893799 2 -0.20851318262019802 
		4 -0.19494406526845537 6 -0.19494406526845537 18 -0.18281396827415128 24 -0.27142112461401657 
		30 -0.12272155611893799 44 -0.12272155611893799;
createNode animCurveTL -n "animCurveTL418";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0.033 2 0.29867943238403283 4 -0.022966720303286364 
		6 -0.022966720303286364 18 -0.013566856565836201 24 0.00017169645198360835 30 0.033 
		44 0.033;
createNode animCurveTL -n "animCurveTL419";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -0.016 2 0.00058042647417124392 4 -0.48069759645327625 
		6 -0.48069759645327625 18 -0.40264953430626904 24 -0.18145109391677772 30 -0.016 
		44 -0.016;
createNode animCurveTL -n "animCurveTL420";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0.10379921435641129 2 -0.022114066379474707 
		4 0.10487291456552336 6 0.10487291456552336 18 0.10461932155962865 24 0.037221775883410496 
		30 0.10379921435641129 44 0.10379921435641129;
createNode animCurveTA -n "animCurveTA1133";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -18.178217858042064 2 -17.296881865476298 
		4 -3.6124270570236172 6 -3.612427057023631 18 -6.0588174213000814 24 -12.518484894351555 
		30 -18.868529413546081 44 -18.178217858042064;
createNode animCurveTA -n "animCurveTA1134";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -4.6186256351197352 2 -8.0278819001575883 
		4 -2.3516520624489168 6 -2.3516520624488986 18 -2.8870795846740123 24 -8.7279777076710303 
		30 -4.2964643529859288 44 -4.6186256351197352;
createNode animCurveTA -n "animCurveTA1135";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -7.7006231053605507 2 -17.615365750376625 
		4 5.7336545451977265 6 29.454764804171187 18 28.268371651800223 24 8.9513315376787581 
		30 -5.0426529659286983 44 -7.7006231053605507;
createNode animCurveTL -n "animCurveTL421";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -0.062545592999319929 2 -0.035274052886683033 
		4 -0.15994930229338264 6 -0.12252923801035631 18 -0.11245471360265204 24 -0.10642792507852844 
		30 -0.081417573609611618 44 -0.062545592999319929;
createNode animCurveTL -n "animCurveTL422";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -0.032867286470989195 2 0.14574379815200619 
		4 -0.018390647399757272 6 -0.093057816496347714 18 -0.084981690431680051 24 0.019110314672564264 
		30 0.02365517812744455 44 -0.032867286470989195;
createNode animCurveTL -n "animCurveTL423";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -0.0098384205421270955 2 -0.11115541858191633 
		4 -0.033697640015701351 6 -0.025721734939381603 18 -0.021970317730567374 24 -0.097898927115703471 
		30 -0.013592518990227787 44 -0.0098384205421270955;
createNode animCurveTA -n "animCurveTA1136";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -25.590668618635455 2 -25.590668618635455 
		4 -25.590668618635455 6 -25.590668618635455 18 -25.590668618635455 24 -25.590668618635455 
		30 -25.590668618635455 44 -25.590668618635455;
createNode animCurveTA -n "animCurveTA1137";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTA -n "animCurveTA1138";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTL -n "animCurveTL424";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTL -n "animCurveTL425";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0.15953969092363035 2 0.15953969092363035 
		4 0.15953969092363035 6 0.15953969092363035 18 0.15953969092363035 24 0.15953969092363035 
		30 0.15953969092363035 44 0.15953969092363035;
createNode animCurveTL -n "animCurveTL426";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -0.04 2 -0.04 4 -0.04 6 -0.04 18 -0.04 
		24 -0.04 30 -0.04 44 -0.04;
createNode animCurveTA -n "animCurveTA1139";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 11.880229891661756 2 11.880229891661756 
		4 11.880229891661756 6 11.880229891661756 18 11.880229891661756 22 10.645888432653122 
		27 11.880229891661756 44 11.880229891661756;
createNode animCurveTA -n "animCurveTA1140";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 22 -3.4652239092225336 
		27 0 44 0;
createNode animCurveTA -n "animCurveTA1141";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 -20.39176893157234 4 0 6 0 18 0 22 
		7.4343367788017085 27 0 44 0;
createNode animCurveTL -n "animCurveTL427";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0.092174287923050061 4 0 6 0 18 0 
		22 0.062689627508500184 27 0 44 0;
createNode animCurveTL -n "animCurveTL428";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -0.20007920657257083 2 -0.22212497823845129 
		4 -0.38713297400059521 6 -0.38713297400059521 18 -0.38713297400059521 22 -0.29690092566887866 
		27 -0.20007920657257083 44 -0.20007920657257083;
createNode animCurveTL -n "animCurveTL429";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0.098575236578624326 2 0.098575236578624326 
		4 0.022735009032279766 6 0.022735009032279766 18 0.022735009032279766 22 0.052126930567730843 
		27 0.098575236578624326 44 0.098575236578624326;
createNode animCurveTU -n "animCurveTU428";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 2 1 4 1 6 1 18 1 24 1 30 1 44 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTA -n "animCurveTA1142";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTA -n "animCurveTA1143";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTA -n "animCurveTA1144";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTL -n "animCurveTL430";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -0.81944359671150613 2 -0.81944359671150613 
		4 -0.81944359671150613 6 -0.81944359671150613 18 -0.81944359671150613 24 -0.81944359671150613 
		30 -0.81944359671150613 44 -0.81944359671150613;
createNode animCurveTL -n "animCurveTL431";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0.029470472912715796 2 0.029470472912715796 
		4 0.029470472912715796 6 0.029470472912715796 18 0.029470472912715796 24 0.029470472912715796 
		30 0.029470472912715796 44 0.029470472912715796;
createNode animCurveTL -n "animCurveTL432";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -0.070295643204272437 2 -0.070295643204272437 
		4 -0.070295643204272437 6 -0.070295643204272437 18 -0.070295643204272437 24 -0.070295643204272437 
		30 -0.070295643204272437 44 -0.070295643204272437;
createNode animCurveTU -n "animCurveTU429";
	setAttr ".tan" 9;
	setAttr -s 8 ".ktv[0:7]"  0 1 2 1 4 1 6 1 18 1 24 1 30 1 44 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTA -n "animCurveTA1145";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -4.8160457500419067 2 -4.8160457500419067 
		4 -4.8160457500419067 6 -4.8160457500419067 18 -4.8160457500419067 24 -4.8160457500419067 
		30 -4.8160457500419067 44 -4.8160457500419067;
createNode animCurveTA -n "animCurveTA1146";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTA -n "animCurveTA1147";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTL -n "animCurveTL433";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -0.80451419482641451 2 -0.80451419482641451 
		4 -0.80451419482641451 6 -0.80451419482641451 18 -0.80451419482641451 24 -0.80451419482641451 
		30 -0.80451419482641451 44 -0.80451419482641451;
createNode animCurveTL -n "animCurveTL434";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -2.4945889741368431e-013 2 0 4 0 6 0 
		18 0 24 0 30 0 44 0;
createNode animCurveTL -n "animCurveTL435";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -0.0085562672260772743 2 -0.0085562672260772743 
		4 -0.0085562672260772743 6 -0.0085562672260772743 18 -0.0085562672260772743 24 -0.0085562672260772743 
		30 -0.0085562672260772743 44 -0.0085562672260772743;
createNode animCurveTU -n "animCurveTU430";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTU -n "animCurveTU431";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 45 2 45 4 45 6 45 18 45 24 45 30 45 44 
		45;
createNode animCurveTU -n "animCurveTU432";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 45 2 45 4 45 6 45 18 45 24 45 30 45 44 
		45;
createNode animCurveTU -n "animCurveTU433";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 45 2 45 4 45 6 45 18 45 24 45 30 45 44 
		45;
createNode animCurveTA -n "animCurveTA1148";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTA -n "animCurveTA1149";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTU -n "animCurveTU434";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTU -n "animCurveTU435";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 45 2 45 4 45 6 45 18 45 24 45 30 45 44 
		45;
createNode animCurveTU -n "animCurveTU436";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 45 2 45 4 45 6 45 18 45 24 45 30 45 44 
		45;
createNode animCurveTU -n "animCurveTU437";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 45 2 45 4 45 6 45 18 45 24 45 30 45 44 
		45;
createNode animCurveTA -n "animCurveTA1150";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTA -n "animCurveTA1151";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTU -n "animCurveTU438";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTU -n "animCurveTU439";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTU -n "animCurveTU440";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTU -n "animCurveTU441";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTU -n "animCurveTU442";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTU -n "animCurveTU443";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTU -n "animCurveTU444";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTU -n "animCurveTU445";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTU -n "animCurveTU446";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTU -n "animCurveTU447";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTU -n "animCurveTU448";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTU -n "animCurveTU449";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTA -n "animCurveTA1152";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTA -n "animCurveTA1153";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTA -n "animCurveTA1154";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -2.5999764661798822e-011 2 0 4 0 6 0 
		18 0 24 0 30 0 44 0;
createNode animCurveTU -n "animCurveTU450";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTU -n "animCurveTU451";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTU -n "animCurveTU452";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTU -n "animCurveTU453";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTU -n "animCurveTU454";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTU -n "animCurveTU455";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTU -n "animCurveTU456";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTU -n "animCurveTU457";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTU -n "animCurveTU458";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTU -n "animCurveTU459";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTU -n "animCurveTU460";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTU -n "animCurveTU461";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTA -n "animCurveTA1155";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTA -n "animCurveTA1156";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTA -n "animCurveTA1157";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -2.5997909391022333e-011 2 0 4 0 6 0 
		18 0 24 0 30 0 44 0;
createNode animCurveTA -n "animCurveTA1158";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -5.8382275551355809 2 -48.316341530112567 
		4 10.926532507427019 6 -54.342468108542931 18 -48.550458150267026 24 -38.030748881727952 
		30 -13.989718112364669 44 -5.8382275551355809;
createNode animCurveTA -n "animCurveTA1159";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -2.3136539176186792 2 15.123116994774636 
		4 4.1319182217636437 6 2.5639713596869811 18 1.744752155776816 24 7.0745036123207559 
		30 -1.8218292815353876 44 -2.3136539176186792;
createNode animCurveTA -n "animCurveTA1160";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -13.887028133305018 2 15.671790957276491 
		4 8.4701616716872294 6 -7.455264777042184 18 -11.675423860743217 24 -7.1949762300931814 
		30 -8.7205588937615879 44 -13.887028133305018;
createNode animCurveTA -n "animCurveTA1161";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 13.873263178484903 2 13.873263178484903 
		4 13.873263178484903 6 13.873263178484903 18 13.873263178484903 24 13.873263178484903 
		30 13.873263178484903 44 13.873263178484903;
createNode animCurveTA -n "animCurveTA1162";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTA -n "animCurveTA1163";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 18 0 24 0 30 0 44 0;
createNode animCurveTA -n "tank_M_backCloth_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 -20.470568448410784 6 45.262003356102134 
		11 -2.9291531938780579 18 10.068308927053927 26 -21.49120657884448 36 9.5200603852218268 
		44 0;
createNode animCurveTA -n "tank_M_backCloth_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 6.7548809799781138 6 0.80608658672954481 
		11 4.215130764619694 18 -2.0647322211130152 26 5.7471859359048043 36 -6.2369382227441506 
		44 0;
createNode animCurveTA -n "tank_M_backCloth_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 14.540694155506266 6 -1.8681079689911497 
		11 11.430434947135669 18 13.2073978422672 26 17.719293006449149 36 17.21408848620305 
		44 0;
createNode animCurveTA -n "tank_M_hang_ctrl_rotateZ2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -7.6359447996384162 2 3.0690107189360538 
		6 116.70988271657725 9 94.904137126337062 12 49.046864734964892 44 -7.6359447996384162;
createNode animCurveTA -n "tank_M_hang_ctrl_rotateY2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -35.260196151694586 2 -1.4612545379585777 
		6 -15.614466754094519 9 -6.1213783484819384 12 -5.475145431149155 44 -35.260196151694586;
createNode animCurveTA -n "tank_M_hang_ctrl_rotateX2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 68.744635926587719 2 17.474423563678261 
		6 -23.849751402591831 9 -9.8172228074295926 12 17.096511356991474 44 68.744635926587719;
createNode animCurveTA -n "tank_R_hang_ctrl_rotateZ2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -7.6359447996384162 2 3.0690107189360538 
		6 116.70988271657725 9 94.904137126337062 12 49.046864734964892 44 -7.6359447996384162;
createNode animCurveTA -n "tank_R_hang_ctrl_rotateY2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -35.260196151694586 2 -1.4612545379585777 
		6 -15.614466754094519 9 -6.1213783484819384 12 -5.475145431149155 44 -35.260196151694586;
createNode animCurveTA -n "tank_R_hang_ctrl_rotateX2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 68.744635926587719 2 17.474423563678261 
		6 -23.849751402591831 9 -9.8172228074295926 12 17.096511356991474 44 68.744635926587719;
createNode animCurveTA -n "tank_L_hang_ctrl_rotateZ2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -7.6359447996384162 2 3.0690107189360538 
		6 116.70988271657725 9 94.904137126337062 12 49.046864734964892 44 -7.6359447996384162;
createNode animCurveTA -n "tank_L_hang_ctrl_rotateY2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -35.260196151694586 2 -1.4612545379585777 
		6 -15.614466754094519 9 -6.1213783484819384 12 -5.475145431149155 44 -35.260196151694586;
createNode animCurveTA -n "tank_L_hang_ctrl_rotateX2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 68.744635926587719 2 17.474423563678261 
		6 -23.849751402591831 9 -9.8172228074295926 12 17.096511356991474 44 68.744635926587719;
createNode animCurveTA -n "tank_R_flag_3_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 18.08 20 18.08;
createNode animCurveTA -n "tank_R_flag_3_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.0336 20 -0.0336;
createNode animCurveTA -n "tank_R_flag_3_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 20 0;
createNode animCurveTA -n "tank_R_flag_2_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 18.373158409800983 20 18.373158409800983;
createNode animCurveTA -n "tank_R_flag_2_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 20 0;
createNode animCurveTA -n "tank_R_flag_2_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 20 0;
createNode animCurveTA -n "tank_R_flag_1_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 18.373158409800983 20 18.373158409800983;
createNode animCurveTA -n "tank_R_flag_1_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 20 0;
createNode animCurveTA -n "tank_R_flag_1_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 20 0;
createNode animCurveTA -n "tank_L_flag_1_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 18.373158409800983 20 18.373158409800983;
createNode animCurveTA -n "tank_L_flag_1_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 20 0;
createNode animCurveTA -n "tank_L_flag_1_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 20 0;
createNode animCurveTA -n "tank_L_flag_2_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 18.373158409800983 20 18.373158409800983;
createNode animCurveTA -n "tank_L_flag_2_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 20 0;
createNode animCurveTA -n "tank_L_flag_2_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 20 0;
createNode animCurveTA -n "tank_L_flag_3_ctrl_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 18.373158409800983 20 18.373158409800983;
createNode animCurveTA -n "tank_L_flag_3_ctrl_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 20 0;
createNode animCurveTA -n "tank_L_flag_3_ctrl_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 20 0;
createNode animCurveTA -n "tank_M_backFeature_ctrl_rotateZ2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -5.4432506707315573 2 -5.4432506707315573 
		4 42.085819845369386 6 25.449563039687952 8 -22.243775836294851 20 -11.982155252861249 
		28 -5.4432506707315573 44 -5.4432506707315573;
createNode animCurveTA -n "tank_M_backFeature_ctrl_rotateY2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 -6.7972948084968676 6 -1.1300809852511051 
		8 2.660214563574733 20 0.1686688558569984 28 0 44 0;
createNode animCurveTA -n "tank_M_backFeature_ctrl_rotateX2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1.4808130565433952 2 1.4808130565433952 
		4 1.860819413536835 6 4.6173910244081773 8 3.9406901923024904 20 1.4711778879466457 
		28 1.4808130565433952 44 1.4808130565433952;
createNode animCurveTA -n "tank_M_frontCloth_ctrl_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -13.113682797820777 2 2.7152696246670311 
		4 21.208367326330848 8 -27.50995668664779 16 40.777671094478045 24 -11.853900788854499 
		35 5.9914566315218387 44 -13.113682797820777;
createNode animCurveTA -n "tank_M_frontCloth_ctrl_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -4.0919497789234391 2 -9.8844861288881027 
		4 -0.89415954729497704 8 0.34103085422819718 16 -10.218732050703117 24 0.58414007960560888 
		35 -3.2645355203373869 44 -4.0919497789234391;
createNode animCurveTA -n "tank_M_frontCloth_ctrl_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 31.178362171912408 2 24.428570766748102 
		4 7.5857287534796578 8 6.1965104063011696 16 7.8377370174231684 24 15.44134503244217 
		35 20.896758949886465 44 31.178362171912408;
createNode lightLinker -n "lightLinker1";
	setAttr -s 4 ".lnk";
	setAttr -s 4 ".slnk";
select -ne :time1;
	setAttr -av -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 28;
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
connectAttr "attack3Source2.cl" "clipLibrary2.sc[0]";
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
// End of attack3B.ma
