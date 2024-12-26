//Maya ASCII 2008 scene
//Name: birthA.ma
//Last modified: Wed, Dec 23, 2009 06:53:05 PM
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
	setAttr -s 145 ".cel[0].cev";
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
createNode animClip -n "birthASource";
	setAttr ".ihi" 0;
	setAttr -s 145 ".ac";
	setAttr ".ac[0:141]" no no yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes no 
		no no no no no no no no no no no yes yes yes no no no no no no no no no no no no 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[145:147]" yes yes yes;
	setAttr ".se" 90;
	setAttr ".ci" no;
createNode animCurveTU -n "animCurveTU217";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU218";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA415";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -58.210811087465537 6 -80.036797706722751 
		16 17.221347278115161 26 24.342816389675075 38 12.518169506488068 50 52.707707451938056 
		62 -61.700207764644745 74 2.4227458172133196 90 -16.433008012612902;
	setAttr -s 9 ".kit[0:8]"  3 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 1 10 10 10 10 
		3;
	setAttr -s 9 ".kix[3:8]"  0.89985287189483643 0.8503495454788208 
		0.52545851469039917 0.67366212606430054 0.76325803995132446 1;
	setAttr -s 9 ".kiy[3:8]"  -0.43619361519813538 0.52621835470199585 
		-0.85081923007965088 -0.73903942108154297 0.64609378576278687 0;
	setAttr -s 9 ".kox[3:8]"  0.89985287189483643 0.8503495454788208 
		0.52545851469039917 0.67366212606430054 0.76325803995132446 1;
	setAttr -s 9 ".koy[3:8]"  -0.43619361519813538 0.52621835470199585 
		-0.85081923007965088 -0.73903942108154297 0.64609378576278687 0;
createNode animCurveTA -n "animCurveTA416";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 70.974480387286377 6 70.223115045743199 
		16 37.311293852009065 26 41.86923477896844 38 43.888656962534562 50 37.117043128338949 
		62 41.469505605763686 74 51.737418834064009 90 46.484153693874759;
	setAttr -s 9 ".kit[0:8]"  3 10 10 9 9 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 9 9 10 10 10 
		3;
createNode animCurveTA -n "animCurveTA417";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 19.582662834075155 6 -1.3095556391415715 
		16 36.14768339221061 26 -28.774293286344747 38 -32.706646488685465 50 44.068687062248152 
		62 10.743956294161357 74 -4.0082359508937184 90 -14.962212153601083;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTA -n "animCurveTA418";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -48.494107129364522 6 -65.799766742248309 
		16 -65.799766742248309 26 -17.747435320524499 38 -13.015765738805506 50 -35.774292319817121 
		62 -35.774292319817121 74 -22.136766656027952 90 -22.136766656027952;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA419";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTA -n "animCurveTA420";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTA -n "animCurveTA421";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTA -n "animCurveTA422";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -15.031270985849668 6 -15.031270985849668 
		16 0 26 15.505325999828518 38 9.5177910794899034 50 9.5177910794899034 62 1.8614700548132253 
		74 -9.982335324211336 90 -9.982335324211336;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 9 9 10 9 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 9 9 10 9 
		10;
createNode animCurveTA -n "animCurveTA423";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -26.23641467530431 6 -26.23641467530431 
		16 0 26 3.9369150859396673 38 8.1297202680918996 50 8.1297202680918996 62 3.2177042159257172 
		74 15.766648207086439 90 15.766648207086439;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 9 9 10 9 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 9 9 10 9 
		10;
createNode animCurveTA -n "animCurveTA424";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -34.809691195952624 6 -34.809691195952624 
		16 0 26 16.348493579425142 38 11.903261147371476 50 -2.0348780910086459 62 11.903261147371476 
		74 -4.5415548635099237 90 -4.5415548635099237;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA425";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -12.053775450155658 6 -12.053775450155658 
		16 0 26 2.2938636103234344 38 2.1540337978715658 50 -9.7350056949183852 62 2.1540337978715658 
		74 1.754519992899283 90 1.754519992899283;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA426";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -81.851776506534023 6 -80.657264600619087 
		16 9.1262865821130514 26 21.220471518806367 38 8.2094863459737049 50 -66.489692115963962 
		62 54.462647296856666 74 -10.112783257940624 90 -25.378456988571386;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTA -n "animCurveTA427";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 39.240605629277823 6 43.617173977187228 
		16 18.093008185416281 26 46.69801834159766 38 47.368479397050073 50 36.361516049718617 
		62 24.658147536147769 74 54.084827184426878 90 49.284082676870852;
	setAttr -s 9 ".kit[0:8]"  3 10 10 9 9 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 9 9 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA428";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -1.4900127609190585 6 0.45369855004304865 
		16 43.150883571242645 26 -1.5539010855031863 38 4.1706561245017379 50 21.96684868763208 
		62 49.94050141519044 74 42.266743911250082 90 34.969087097535308;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA429";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -54.053523507707013 6 -61.975696206520887 
		16 -61.975696206520887 26 -16.507387922527336 38 -6.9026724994066422 50 -26.365448953936475 
		62 -26.365448953936475 74 -4.2353230899544307 90 -4.2353230899544307;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA430";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTA -n "animCurveTA431";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTA -n "animCurveTA432";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTA -n "animCurveTA433";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -42.894982284341559 6 -42.894982284341559 
		16 -42.894982284341559 26 54.788077508122967 38 50.08912095285671 50 50.08912095285671 
		62 50.08912095285671 74 0 90 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA434";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 3.273916426956045 6 3.273916426956045 
		16 3.273916426956045 26 10.73512971479474 38 8.3314075276024067 50 8.3314075276024067 
		62 8.3314075276024067 74 0 90 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA435";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.74142827142552248 6 -0.74142827142552248 
		16 -0.74142827142552248 26 -3.8072599702537722 38 -3.0080622816720197 50 -3.0080622816720197 
		62 -3.0080622816720197 74 0 90 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA436";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -37.264010934530496 6 -37.264010934530496 
		16 -37.264010934530496 26 -36.401834764431776 38 -32.348869740938646 50 -32.348869740938646 
		62 -32.348869740938646 74 -14.515820710620677 90 -14.515820710620677;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA437";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.93159408243017094 6 0.93159408243017094 
		16 0.93159408243017094 26 0.23743235271155472 38 -3.0257210379024335 50 -3.0257210379024335 
		62 -3.0257210379024335 74 -17.383598210882599 90 -17.383598210882599;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA438";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 10.03599816740434 6 10.03599816740434 
		16 10.03599816740434 26 9.7134939094581014 38 8.1974481947366034 50 8.1974481947366034 
		62 8.1974481947366034 74 1.5268462968664711 90 1.5268462968664711;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL127";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.00025694328101411035 6 0.00025694328101411035 
		16 0.00025694328101411035 26 0.00025694328101411035 38 0.00025694328101411035 50 
		0.00025694328101411035 62 0.00025694328101411035 74 0.00025694328101411035 90 0.00025694328101411035;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL128";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL129";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.12527739251666781 6 -0.12527739251666781 
		16 -0.12527739251666781 26 -0.12527739251666781 38 -0.12527739251666781 50 -0.12527739251666781 
		62 -0.12527739251666781 74 -0.12527739251666781 90 -0.12527739251666781;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL130";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.032833691772160223 6 0.032833691772160223 
		16 0.032833691772160223 26 0.032833691772160223 38 0.032833691772160223 50 0.032833691772160223 
		62 0.032833691772160223 74 0.032833691772160223 90 0.032833691772160223;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL131";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.016062985925156426 6 -0.016062985925156426 
		16 -0.016062985925156426 26 -0.016062985925156426 38 -0.016062985925156426 50 -0.016062985925156426 
		62 -0.016062985925156426 74 -0.016062985925156426 90 -0.016062985925156426;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL132";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.11728380015772394 6 0.11728380015772394 
		16 0.11728380015772394 26 0.11728380015772394 38 0.11728380015772394 50 0.11728380015772394 
		62 0.11728380015772394 74 0.11728380015772394 90 0.11728380015772394;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA439";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99309123264824872 6 0.99309123264824861 
		16 0.37091086482630625 26 0.35036478392394532 38 0.25952947885478977 50 2.3998492605534905 
		62 1.8492061436658422 74 0 90 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 9 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 9 10 
		10;
createNode animCurveTA -n "animCurveTA440";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.66298730264573569 6 0.66298730264573491 
		16 1.1349808223766049 26 1.0721101706632934 38 0.79415571037402999 50 1.7560329303968971 
		62 1.2681563949332337 74 0 90 0;
	setAttr -s 9 ".kit[0:8]"  3 10 9 9 10 10 9 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 9 9 10 10 9 10 
		10;
createNode animCurveTA -n "animCurveTA441";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 21.390714801681071 6 34.348190830316646 
		16 -3.8292968282385891 26 -6.3622034571881665 38 -4.5040339899326964 50 1.3669164336455257 
		62 -2.6154222218279903 74 3.6719125695963681 90 3.6719125695963681;
	setAttr -s 9 ".kit[0:8]"  3 10 1 1 1 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 1 1 1 10 10 10 
		10;
	setAttr -s 9 ".kix[2:8]"  0.88052326440811157 0.99330753087997437 
		0.99445569515228271 0.99915230274200439 0.99873799085617065 1 1;
	setAttr -s 9 ".kiy[2:8]"  -0.47400298714637756 0.11549978703260422 
		0.10515629500150681 0.041168190538883209 0.050223745405673981 0 0;
	setAttr -s 9 ".kox[2:8]"  0.88052326440811157 0.99330753087997437 
		0.99445575475692749 0.99915230274200439 0.99873799085617065 1 1;
	setAttr -s 9 ".koy[2:8]"  -0.47400298714637756 0.11549978703260422 
		0.10515628010034561 0.041168190538883209 0.050223745405673981 0 0;
createNode animCurveTL -n "animCurveTL133";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.37908964937174494 6 -0.37908964937174494 
		16 -0.088099267034537659 26 -0.024419595343039814 38 -0.077486068990600426 50 -0.03113629966431853 
		62 -0.020558952999138371 74 -0.05103778814389151 90 -0.0319338039184065;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL134";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.05420676385985617 6 0.05420676385985617 
		16 0.14062593528151973 26 0.022731636821944977 38 0.017042700666212999 50 0.084046692909451562 
		62 0.038142906826435778 74 -0.046771839175953275 90 0.00078859512199502824;
	setAttr -s 9 ".kit[0:8]"  3 10 10 9 9 10 9 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 9 9 10 9 10 
		10;
createNode animCurveTL -n "animCurveTL135";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -0.0036422174640321791 6 -0.0036422174640321791 
		16 -0.020198330927843039 20 -0.077244401471015509 26 -0.012107286661700623 38 -0.0089683608108821703 
		50 -0.017955323905087067 62 0.023728853857431113 68 0.077933827128860253 74 -0.0048648718760103448 
		90 0;
	setAttr -s 11 ".kit[0:10]"  3 10 1 10 9 1 10 9 
		10 9 10;
	setAttr -s 11 ".kot[0:10]"  3 10 1 10 9 1 10 9 
		10 9 10;
	setAttr -s 11 ".kix[2:10]"  0.99637424945831299 0.99970549345016479 
		0.99358773231506348 0.99841654300689697 1 0.98746907711029053 0.99745470285415649 
		0.99440044164657593 1;
	setAttr -s 11 ".kiy[2:10]"  -0.085079006850719452 0.024265985935926437 
		0.11306373775005341 -0.056253515183925629 0 0.15781262516975403 -0.071302346885204315 
		-0.10567831248044968 0;
	setAttr -s 11 ".kox[2:10]"  0.99637424945831299 0.99970549345016479 
		0.99358773231506348 0.99841654300689697 1 0.98746907711029053 0.99745470285415649 
		0.99440044164657593 1;
	setAttr -s 11 ".koy[2:10]"  -0.085079006850719452 0.024265985935926437 
		0.11306373775005341 -0.056253500282764435 0 0.15781262516975403 -0.071302346885204315 
		-0.10567831248044968 0;
createNode animCurveTA -n "animCurveTA442";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -16.236770139599834 6 -16.236770139599834 
		16 -16.236770139599834 26 -16.236770139599834 38 -16.236770139599834 50 -16.236770139599834 
		62 -16.236770139599834 64 -16.236770139599834 68 -15.403232266877325 71 -16.236770139599834 
		74 -16.236770139599834 90 -16.236770139599834;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 10;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 10;
createNode animCurveTA -n "animCurveTA443";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 64 0 68 
		5.1792040182674004 71 0 74 0 90 0;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 10;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 10;
createNode animCurveTA -n "animCurveTA444";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 64 0 68 
		12.982967096519799 71 0 74 0 90 0;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 10;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 10;
createNode animCurveTL -n "animCurveTL136";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -6.0000000000892673e-006 6 -6.0000000000892673e-006 
		16 -6.0000000000892673e-006 26 -6.0000000000892673e-006 38 -6.0000000000892673e-006 
		50 -6.0000000000892673e-006 62 -6.0000000000892673e-006 64 -6.0000000000892673e-006 
		68 0.039674584654585031 71 -6.0000000000892673e-006 74 -6.0000000000892673e-006 90 
		-6.0000000000892673e-006;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 10;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 10;
createNode animCurveTL -n "animCurveTL137";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0.12043983876385822 6 0.12043983876385822 
		16 0.12043983876385822 26 0.12043983876385822 38 0.12043983876385822 50 0.12043983876385822 
		62 0.12043983876385822 64 0.12043983876385822 68 0.060230824381929067 71 2.1809999999936394e-005 
		74 2.1809999999936394e-005 90 2.1809999999936394e-005;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 10;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 10;
createNode animCurveTL -n "animCurveTL138";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -0.040093865534497591 6 -0.040093865534497591 
		16 -0.040093865534497591 26 -0.040093865534497591 38 -0.040093865534497591 50 -0.040093865534497591 
		62 -0.040093865534497591 64 -0.040093865534497591 68 -0.040093865534497591 71 -0.040093865534497591 
		74 -0.040093865534497591 90 -0.040093865534497591;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 10;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 10;
createNode animCurveTA -n "animCurveTA445";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -0.83898321824155031 6 -0.83898321824155031 
		16 -0.83898321824155031 18 -0.83898321824155031 21 12.615669893757902 24 25.000774638404387 
		26 25.000774638404387 38 25.000774638404387 50 25.000774638404387 62 25.000774638404387 
		74 25.000774638404387 90 25.000774638404387;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 10;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 10;
createNode animCurveTA -n "animCurveTA446";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 6 0 16 0 18 0 21 -1.7133849296930137 
		24 0 26 0 38 0 50 0 62 0 74 0 90 0;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 10;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 10;
createNode animCurveTA -n "animCurveTA447";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 6 0 16 0 18 0 21 18.014559932100834 
		24 0 26 0 38 0 50 0 62 0 74 0 90 0;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 10;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 10;
createNode animCurveTL -n "animCurveTL139";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 6 0 16 0 18 0 21 0.064081652070044792 
		24 0 26 0 38 0 50 0 62 0 74 0 90 0;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 10;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 10;
createNode animCurveTL -n "animCurveTL140";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -0.12076025550900268 6 -0.12076025550900268 
		16 -0.12076025550900268 18 -0.12076025550900268 24 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 10 10 10 10 
		10 10 10;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 10 10 10 10 
		10 10 10;
createNode animCurveTL -n "animCurveTL141";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0.038258090963777393 6 0.038258090963777393 
		16 0.038258090963777393 18 0.038258090963777393 24 0.038258090963777358 26 0.038258090963777358 
		38 0.038258090963777358 50 0.038258090963777358 62 0.038258090963777358 74 0.038258090963777358 
		90 0.038258090963777358;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 10 10 10 10 
		10 10 10;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 10 10 10 10 
		10 10 10;
createNode animCurveTU -n "animCurveTU219";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 6 1 16 1 26 1 38 1 50 1 62 1 74 1 90 
		1;
	setAttr -s 9 ".kit[0:8]"  3 9 9 9 9 9 9 9 
		9;
	setAttr -s 9 ".kot[0:8]"  3 5 5 5 5 5 5 5 
		5;
createNode animCurveTA -n "animCurveTA448";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA449";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA450";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL142";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.808 6 -0.808 16 -0.808 26 -0.808 38 
		-0.808 50 -0.808 62 -0.808 74 -0.808 90 -0.808;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL143";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL144";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU220";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 6 1 16 1 26 1 38 1 50 1 62 1 74 1 90 
		1;
	setAttr -s 9 ".kit[0:8]"  3 9 9 9 9 9 9 9 
		9;
	setAttr -s 9 ".kot[0:8]"  3 5 5 5 5 5 5 5 
		5;
createNode animCurveTA -n "animCurveTA451";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA452";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA453";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL145";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.80789537837891157 6 -0.80789537837891157 
		16 -0.80789537837891157 26 -0.80789537837891157 38 -0.80789537837891157 50 -0.80789537837891157 
		62 -0.80789537837891157 74 -0.80789537837891157 90 -0.80789537837891157;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL146";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL147";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU221";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTU -n "animCurveTU222";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 45 6 45 16 45 26 45 38 45 50 45 62 45 
		74 45 90 45;
createNode animCurveTU -n "animCurveTU223";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 45 6 45 16 45 26 45 38 45 50 45 62 45 
		74 45 90 45;
createNode animCurveTU -n "animCurveTU224";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 45 6 45 16 45 26 45 38 45 50 45 62 45 
		74 45 90 45;
createNode animCurveTA -n "animCurveTA454";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTA -n "animCurveTA455";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTU -n "animCurveTU225";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTU -n "animCurveTU226";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 45 6 45 16 45 26 45 38 45 50 45 62 45 
		74 45 90 45;
createNode animCurveTU -n "animCurveTU227";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 45 6 45 16 45 26 45 38 45 50 45 62 45 
		74 45 90 45;
createNode animCurveTU -n "animCurveTU228";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 45 6 45 16 45 26 45 38 45 50 45 62 45 
		74 45 90 45;
createNode animCurveTA -n "animCurveTA456";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTA -n "animCurveTA457";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTU -n "animCurveTU229";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTU -n "animCurveTU230";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTU -n "animCurveTU231";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTU -n "animCurveTU232";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTU -n "animCurveTU233";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTU -n "animCurveTU234";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTU -n "animCurveTU235";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTU -n "animCurveTU236";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTU -n "animCurveTU237";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTU -n "animCurveTU238";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTU -n "animCurveTU239";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTU -n "animCurveTU240";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTA -n "animCurveTA458";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTA -n "animCurveTA459";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTA -n "animCurveTA460";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTU -n "animCurveTU241";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTU -n "animCurveTU242";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTU -n "animCurveTU243";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTU -n "animCurveTU244";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTU -n "animCurveTU245";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTU -n "animCurveTU246";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTU -n "animCurveTU247";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTU -n "animCurveTU248";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTU -n "animCurveTU249";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTU -n "animCurveTU250";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTU -n "animCurveTU251";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTU -n "animCurveTU252";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTA -n "animCurveTA461";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTA -n "animCurveTA462";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTA -n "animCurveTA463";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0 26 0 38 0 50 0 62 0 74 0 90 
		0;
createNode animCurveTA -n "animCurveTA464";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -55.674217108036778 6 -63.430677535680054 
		16 -55.684885372073317 26 0.62239566788503098 38 5.4607080282503748 50 -30.323062769463878 
		62 -13.238929124916163 74 -6.7832614176793165 90 -6.7832614176793165;
	setAttr -s 9 ".kit[0:8]"  3 1 1 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 1 1 10 10 10 10 10 
		10;
	setAttr -s 9 ".kix[1:8]"  0.99121379852294922 0.61258488893508911 
		0.56633943319320679 0.82880055904388428 0.92591261863708496 0.88955068588256836 1 
		1;
	setAttr -s 9 ".kiy[1:8]"  -0.13226938247680664 0.7904047966003418 
		0.82417213916778564 -0.55954420566558838 -0.37773793935775757 0.4568365216255188 
		0 0;
	setAttr -s 9 ".kox[1:8]"  0.99121379852294922 0.61258500814437866 
		0.56633943319320679 0.82880055904388428 0.92591261863708496 0.88955068588256836 1 
		1;
	setAttr -s 9 ".koy[1:8]"  -0.13226939737796783 0.7904047966003418 
		0.82417213916778564 -0.55954420566558838 -0.37773793935775757 0.4568365216255188 
		0 0;
createNode animCurveTA -n "animCurveTA465";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -6.2415831313725905 6 -7.3236803044255563 
		16 -2.565018311667373 26 1.853337050361856 38 1.3728423086239652 50 -15.514337379325099 
		62 12.527959794062156 74 0 90 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 9 9 10 10 9 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 9 9 10 10 9 
		10;
createNode animCurveTA -n "animCurveTA466";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 10.455435612667811 6 17.6932349294155 
		16 18.807781893866654 26 6.9041876997006408 38 3.2373449553886289 50 -36.738997014800816 
		62 33.951028855089341 74 0 90 0;
	setAttr -s 9 ".kit[0:8]"  3 9 9 10 10 10 10 9 
		10;
	setAttr -s 9 ".kot[0:8]"  3 9 9 10 10 10 10 9 
		10;
createNode animCurveTA -n "animCurveTA467";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 21.730163993982138 6 21.730163993982138 
		16 10.859593702517781 26 0 38 -6.8197123823258332 50 -6.8197123823258332 62 -6.8197123823258332 
		74 -17.428736070727251 90 -17.428736070727251;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA468";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 0.10908770444828371 26 0 38 
		0 50 0 62 0 74 0 90 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA469";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 16 -8.119802675608204 26 0 38 0 
		50 0 62 0 74 0 90 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA470";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 6 -14.15404466973474 16 7.3844276697488826 
		30 -8.8506632265776819 42 5.1305957145331416 56 -8.513069363675724 72 9.7891974073930665 
		90 0;
	setAttr -s 8 ".kit[7]"  3;
	setAttr -s 8 ".kot[7]"  3;
createNode animCurveTA -n "animCurveTA471";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 6 1.2729602429702929 16 1.2220378728275221 
		30 1.1076166073240399 42 0.99191642756774456 56 0.78842941743983064 72 0.42913605984574166 
		90 0;
	setAttr -s 8 ".kit[0:7]"  10 10 9 9 9 9 9 10;
	setAttr -s 8 ".kot[0:7]"  10 10 9 9 9 9 9 10;
createNode animCurveTA -n "animCurveTA472";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 6 0.96657162105612815 16 0.91361377567029856 
		30 0.84030746201242013 42 0.74278604348112376 56 0.6000868622917862 72 0.31507061803670605 
		90 0;
	setAttr -s 8 ".kit[0:7]"  10 10 9 9 9 9 9 10;
	setAttr -s 8 ".kot[0:7]"  10 10 9 9 9 9 9 10;
createNode animCurveTA -n "animCurveTA473";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 9.1478457292549002 6 35.226798692962859 
		15 -1.7620903923913918 24 36.273424235686299 33 -8.062281729411902 41 27.500308362887488 
		45 15.540944406703353 49 0.91396553409723691 54 9.732415669227878 58 16.463135720163223 
		64 10.050626329893193 70 4.2268497150416833 78 5.3145239665726569 90 9.1478457292549002;
	setAttr -s 14 ".kit[13]"  3;
	setAttr -s 14 ".kot[13]"  3;
createNode animCurveTA -n "animCurveTA474";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 6 -2.9231312541562819 15 8.6437399245011388 
		24 -12.739010916306151 33 10.115640233924672 41 -5.2331067993211313 45 13.766407557193082 
		49 12.175315776670526 54 -28.52472678703019 58 -16.896380813084878 64 25.786133627207608 
		70 -5.8506267249962605 78 11.7363952076747 90 0;
	setAttr -s 14 ".kit[6:13]"  9 9 10 10 10 10 10 3;
	setAttr -s 14 ".kot[6:13]"  9 9 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA475";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 6 -3.7961290221816761 15 4.4634931558691475 
		24 -7.4015757605162378 33 7.8728988517675695 41 3.4432162240376911 45 14.392545710441004 
		49 23.285278756023146 54 20.266686502663955 58 15.67923506337649 64 11.234473392268038 
		70 10.129904753432106 78 5.736241182963056 90 0;
	setAttr -s 14 ".kit[0:13]"  3 10 10 10 10 10 10 10 
		10 10 9 9 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 10 10 10 10 10 10 
		10 10 9 9 10 3;
createNode animCurveTA -n "animCurveTA476";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 9.1478457292549002 6 35.226798692962859 
		15 -1.7620903923913918 24 36.273424235686299 33 -8.062281729411902 41 27.500308362887488 
		45 15.540944406703353 49 0.91396553409723691 54 9.732415669227878 58 16.463135720163223 
		64 10.050626329893193 70 4.2268497150416833 78 5.3145239665726569 90 9.1478457292549002;
	setAttr -s 14 ".kit[6:13]"  9 10 10 10 10 9 9 3;
	setAttr -s 14 ".kot[6:13]"  9 10 10 10 10 9 9 3;
createNode animCurveTA -n "animCurveTA477";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 6 -2.9231312541562819 15 8.6437399245011388 
		24 -12.739010916306151 33 10.115640233924672 41 -5.2331067993211313 45 13.766407557193082 
		49 12.175315776670526 54 -28.52472678703019 58 -16.896380813084878 64 25.786133627207608 
		70 -5.8506267249962605 78 11.7363952076747 90 0;
	setAttr -s 14 ".kit[6:13]"  9 9 10 10 10 10 10 3;
	setAttr -s 14 ".kot[6:13]"  9 9 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA478";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 6 -3.7961290221816761 15 4.4634931558691475 
		24 -7.4015757605162378 33 7.8728988517675695 41 3.4432162240376911 45 14.392545710441004 
		49 23.285278756023146 54 20.266686502663955 58 15.67923506337649 64 11.234473392268038 
		70 10.129904753432106 78 5.736241182963056 90 0;
	setAttr -s 14 ".kit[10:13]"  9 9 10 3;
	setAttr -s 14 ".kot[10:13]"  9 9 10 3;
createNode animCurveTA -n "animCurveTA479";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 9.1478457292549002 6 35.226798692962859 
		15 -1.7620903923913918 24 36.273424235686299 33 -8.062281729411902 41 27.500308362887488 
		45 15.540944406703353 49 0.91396553409723691 54 9.732415669227878 58 16.463135720163223 
		64 10.050626329893193 70 4.2268497150416833 78 5.3145239665726569 90 9.1478457292549002;
	setAttr -s 14 ".kit[0:13]"  3 10 10 10 10 10 10 10 
		10 10 10 9 9 3;
	setAttr -s 14 ".kot[0:13]"  3 10 10 10 10 10 10 10 
		10 10 10 9 9 3;
createNode animCurveTA -n "animCurveTA480";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 6 -2.9231312541562819 15 8.6437399245011388 
		24 -12.739010916306151 33 10.115640233924672 41 -5.2331067993211313 45 13.766407557193082 
		49 12.175315776670526 54 -28.52472678703019 58 -16.896380813084878 64 25.786133627207608 
		70 -5.8506267249962605 78 11.7363952076747 90 0;
	setAttr -s 14 ".kit[0:13]"  3 10 10 10 10 10 9 9 
		10 10 10 10 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 10 10 10 10 9 9 
		10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA481";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 6 -3.7961290221816761 15 4.4634931558691475 
		24 -7.4015757605162378 33 7.8728988517675695 41 3.4432162240376911 45 14.392545710441004 
		49 23.285278756023146 54 20.266686502663955 58 15.67923506337649 64 11.234473392268038 
		70 10.129904753432106 78 5.736241182963056 90 0;
	setAttr -s 14 ".kit[0:13]"  3 10 10 10 10 10 10 10 
		9 9 9 9 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 10 10 10 10 10 10 
		9 9 9 9 10 3;
createNode animCurveTA -n "animCurveTA482";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA483";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA484";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA485";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA486";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA487";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA488";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA489";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA490";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA491";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA492";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA493";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA494";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA495";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA496";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA497";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA498";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA499";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA500";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 6 -8.7602114092081749 14 10.142657246691167 
		26 -15.812196298299455 40 12.313856091376584 58 -2.721282019452627 75 9.3822341125880264 
		90 0;
	setAttr -s 8 ".kit[7]"  3;
	setAttr -s 8 ".kot[7]"  3;
createNode animCurveTA -n "animCurveTA501";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 6 0.00010994219542429486 14 0.001126298225948105 
		26 0.00077988172346424864 40 0.0013239182701172696 58 -0.00051234271198760878 75 
		0.00080189441919761091 90 0;
	setAttr -s 8 ".kit[1:7]"  1 10 10 10 10 10 10;
	setAttr -s 8 ".kot[1:7]"  1 10 10 10 10 10 10;
	setAttr -s 8 ".kix[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".kiy[1:7]"  1.7806809410103597e-005 0 0 0 0 0 0;
	setAttr -s 8 ".kox[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".koy[1:7]"  1.780680577212479e-005 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA502";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 6 0.0065464175822225563 14 -0.0075491048370122374 
		26 0.01251330692445481 40 -0.0096917685669503408 58 0.0036987997531891938 75 -0.0061863865896861301 
		90 0;
createNode lightLinker -n "lightLinker1";
	setAttr -s 4 ".lnk";
	setAttr -s 4 ".slnk";
select -ne :time1;
	setAttr -av -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 317;
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
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -av ".w";
	setAttr -av ".h";
	setAttr ".pa" 1;
	setAttr -k on ".al";
	setAttr -av ".dar";
	setAttr -k on ".off";
	setAttr -k on ".fld";
	setAttr -k on ".zsl";
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
connectAttr "birthASource.cl" "clipLibrary1.sc[0]";
connectAttr "animCurveTU217.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "animCurveTU218.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "animCurveTA415.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "animCurveTA416.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "animCurveTA417.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "animCurveTA418.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "animCurveTA419.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "animCurveTA420.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "animCurveTA421.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "animCurveTA422.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "animCurveTA423.a" "clipLibrary1.cel[0].cev[10].cevr";
connectAttr "animCurveTA424.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "animCurveTA425.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "animCurveTA426.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "animCurveTA427.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "animCurveTA428.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "animCurveTA429.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "animCurveTA430.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "animCurveTA431.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "animCurveTA432.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "animCurveTA433.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "animCurveTA434.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "animCurveTA435.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "animCurveTA436.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "animCurveTA437.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "animCurveTA438.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "animCurveTL127.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "animCurveTL128.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "animCurveTL129.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "animCurveTL130.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "animCurveTL131.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "animCurveTL132.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "animCurveTA439.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "animCurveTA440.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "animCurveTA441.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "animCurveTL133.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "animCurveTL134.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "animCurveTL135.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "animCurveTA442.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "animCurveTA443.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "animCurveTA444.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "animCurveTL136.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "animCurveTL137.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "animCurveTL138.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "animCurveTA445.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "animCurveTA446.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "animCurveTA447.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "animCurveTL139.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "animCurveTL140.a" "clipLibrary1.cel[0].cev[48].cevr";
connectAttr "animCurveTL141.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "animCurveTU219.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "animCurveTA448.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "animCurveTA449.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "animCurveTA450.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "animCurveTL142.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "animCurveTL143.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "animCurveTL144.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "animCurveTU220.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "animCurveTA451.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "animCurveTA452.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "animCurveTA453.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "animCurveTL145.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "animCurveTL146.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "animCurveTL147.a" "clipLibrary1.cel[0].cev[63].cevr";
connectAttr "animCurveTU221.a" "clipLibrary1.cel[0].cev[64].cevr";
connectAttr "animCurveTU222.a" "clipLibrary1.cel[0].cev[65].cevr";
connectAttr "animCurveTU223.a" "clipLibrary1.cel[0].cev[66].cevr";
connectAttr "animCurveTU224.a" "clipLibrary1.cel[0].cev[67].cevr";
connectAttr "animCurveTA454.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "animCurveTA455.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "animCurveTU225.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "animCurveTU226.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "animCurveTU227.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "animCurveTU228.a" "clipLibrary1.cel[0].cev[73].cevr";
connectAttr "animCurveTA456.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "animCurveTA457.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "animCurveTU229.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "animCurveTU230.a" "clipLibrary1.cel[0].cev[77].cevr";
connectAttr "animCurveTU231.a" "clipLibrary1.cel[0].cev[78].cevr";
connectAttr "animCurveTU232.a" "clipLibrary1.cel[0].cev[79].cevr";
connectAttr "animCurveTU233.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "animCurveTU234.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "animCurveTU235.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "animCurveTU236.a" "clipLibrary1.cel[0].cev[83].cevr";
connectAttr "animCurveTU237.a" "clipLibrary1.cel[0].cev[84].cevr";
connectAttr "animCurveTU238.a" "clipLibrary1.cel[0].cev[85].cevr";
connectAttr "animCurveTU239.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "animCurveTU240.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "animCurveTA458.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "animCurveTA459.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr "animCurveTA460.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "animCurveTU241.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "animCurveTU242.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "animCurveTU243.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "animCurveTU244.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "animCurveTU245.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "animCurveTU246.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "animCurveTU247.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "animCurveTU248.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "animCurveTU249.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "animCurveTU250.a" "clipLibrary1.cel[0].cev[100].cevr";
connectAttr "animCurveTU251.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "animCurveTU252.a" "clipLibrary1.cel[0].cev[102].cevr";
connectAttr "animCurveTA461.a" "clipLibrary1.cel[0].cev[103].cevr";
connectAttr "animCurveTA462.a" "clipLibrary1.cel[0].cev[104].cevr";
connectAttr "animCurveTA463.a" "clipLibrary1.cel[0].cev[105].cevr";
connectAttr "animCurveTA464.a" "clipLibrary1.cel[0].cev[106].cevr";
connectAttr "animCurveTA465.a" "clipLibrary1.cel[0].cev[107].cevr";
connectAttr "animCurveTA466.a" "clipLibrary1.cel[0].cev[108].cevr";
connectAttr "animCurveTA467.a" "clipLibrary1.cel[0].cev[109].cevr";
connectAttr "animCurveTA468.a" "clipLibrary1.cel[0].cev[110].cevr";
connectAttr "animCurveTA469.a" "clipLibrary1.cel[0].cev[111].cevr";
connectAttr "animCurveTA470.a" "clipLibrary1.cel[0].cev[112].cevr";
connectAttr "animCurveTA471.a" "clipLibrary1.cel[0].cev[113].cevr";
connectAttr "animCurveTA472.a" "clipLibrary1.cel[0].cev[114].cevr";
connectAttr "animCurveTA473.a" "clipLibrary1.cel[0].cev[115].cevr";
connectAttr "animCurveTA474.a" "clipLibrary1.cel[0].cev[116].cevr";
connectAttr "animCurveTA475.a" "clipLibrary1.cel[0].cev[117].cevr";
connectAttr "animCurveTA476.a" "clipLibrary1.cel[0].cev[118].cevr";
connectAttr "animCurveTA477.a" "clipLibrary1.cel[0].cev[119].cevr";
connectAttr "animCurveTA478.a" "clipLibrary1.cel[0].cev[120].cevr";
connectAttr "animCurveTA479.a" "clipLibrary1.cel[0].cev[121].cevr";
connectAttr "animCurveTA480.a" "clipLibrary1.cel[0].cev[122].cevr";
connectAttr "animCurveTA481.a" "clipLibrary1.cel[0].cev[123].cevr";
connectAttr "animCurveTA482.a" "clipLibrary1.cel[0].cev[124].cevr";
connectAttr "animCurveTA483.a" "clipLibrary1.cel[0].cev[125].cevr";
connectAttr "animCurveTA484.a" "clipLibrary1.cel[0].cev[126].cevr";
connectAttr "animCurveTA485.a" "clipLibrary1.cel[0].cev[127].cevr";
connectAttr "animCurveTA486.a" "clipLibrary1.cel[0].cev[128].cevr";
connectAttr "animCurveTA487.a" "clipLibrary1.cel[0].cev[129].cevr";
connectAttr "animCurveTA488.a" "clipLibrary1.cel[0].cev[130].cevr";
connectAttr "animCurveTA489.a" "clipLibrary1.cel[0].cev[131].cevr";
connectAttr "animCurveTA490.a" "clipLibrary1.cel[0].cev[132].cevr";
connectAttr "animCurveTA491.a" "clipLibrary1.cel[0].cev[133].cevr";
connectAttr "animCurveTA492.a" "clipLibrary1.cel[0].cev[134].cevr";
connectAttr "animCurveTA493.a" "clipLibrary1.cel[0].cev[135].cevr";
connectAttr "animCurveTA494.a" "clipLibrary1.cel[0].cev[136].cevr";
connectAttr "animCurveTA495.a" "clipLibrary1.cel[0].cev[137].cevr";
connectAttr "animCurveTA496.a" "clipLibrary1.cel[0].cev[138].cevr";
connectAttr "animCurveTA497.a" "clipLibrary1.cel[0].cev[139].cevr";
connectAttr "animCurveTA498.a" "clipLibrary1.cel[0].cev[140].cevr";
connectAttr "animCurveTA499.a" "clipLibrary1.cel[0].cev[141].cevr";
connectAttr "animCurveTA500.a" "clipLibrary1.cel[0].cev[145].cevr";
connectAttr "animCurveTA501.a" "clipLibrary1.cel[0].cev[146].cevr";
connectAttr "animCurveTA502.a" "clipLibrary1.cel[0].cev[147].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of birthA.ma
