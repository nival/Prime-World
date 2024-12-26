//Maya ASCII 2008 scene
//Name: run.ma
//Last modified: Mon, Jun 01, 2009 11:56:57 AM
//Codeset: 1251
requires maya "2008";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Complete 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200802250025-718075";
fileInfo "osv" "Microsoft Windows XP Service Pack 3 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 149 ".cel[0].cev";
	setAttr ".cd[0].cm" -type "characterMapping" 172 "Chest_locator.rotateZ" 2 
		16 "Chest_locator.rotateY" 2 17 "Chest_locator.rotateX" 2 18 "L_Locot_locator.translateZ" 
		1 22 "L_Locot_locator.translateY" 1 23 "L_Locot_locator.translateX" 
		1 24 "R_Locot_locator.translateZ" 1 25 "R_Locot_locator.translateY" 
		1 26 "R_Locot_locator.translateX" 1 27 "L_Hand_locator.Shield" 
		0 1 "L_Hand_locator.rotateZ" 2 22 "L_Hand_locator.rotateY" 2 
		23 "L_Hand_locator.rotateX" 2 24 "L_Hand_locator.translateZ" 1 
		37 "L_Hand_locator.translateY" 1 38 "L_Hand_locator.translateX" 1 
		39 "R_Hand_locator.Sword" 0 2 "R_Hand_locator.rotateZ" 2 25 "R_Hand_locator.rotateY" 
		2 26 "R_Hand_locator.rotateX" 2 27 "R_Hand_locator.translateZ" 
		1 40 "R_Hand_locator.translateY" 1 41 "R_Hand_locator.translateX" 
		1 42 "R_Knee_locator.translateZ" 1 43 "R_Knee_locator.translateY" 
		1 44 "R_Knee_locator.translateX" 1 45 "L_Knee_locator.translateZ" 
		1 46 "L_Knee_locator.translateY" 1 47 "L_Knee_locator.translateX" 
		1 48 "R_Leg_locator.Toe" 0 3 "R_Leg_locator.rotateZ" 2 28 "R_Leg_locator.rotateY" 
		2 29 "R_Leg_locator.rotateX" 2 30 "R_Leg_locator.translateZ" 1 
		49 "R_Leg_locator.translateY" 1 50 "R_Leg_locator.translateX" 1 
		51 "L_Leg_locator.Toe" 0 4 "L_Leg_locator.rotateZ" 2 31 "L_Leg_locator.rotateY" 
		2 32 "L_Leg_locator.rotateX" 2 33 "L_Leg_locator.translateZ" 1 
		52 "L_Leg_locator.translateY" 1 53 "L_Leg_locator.translateX" 1 
		54 "Hip_locator.rotateZ" 2 34 "Hip_locator.rotateY" 2 35 "Hip_locator.rotateX" 
		2 36 "Hip_locator.translateZ" 1 55 "Hip_locator.translateY" 1 
		56 "Hip_locator.translateX" 1 57 "L_Clavice_locator.rotateZ" 2 
		37 "L_Clavice_locator.rotateY" 2 38 "L_Clavice_locator.rotateX" 2 
		39 "R_Clavice_locator.rotateZ" 2 40 "R_Clavice_locator.rotateY" 2 
		41 "R_Clavice_locator.rotateX" 2 42 "shield_hand_locator.rotateZ" 2 
		43 "shield_hand_locator.rotateY" 2 44 "shield_hand_locator.rotateX" 
		2 45 "shield_hand_locator.translateZ" 1 82 "shield_hand_locator.translateY" 
		1 83 "shield_hand_locator.translateX" 1 84 "L_Thumb_locator.Thumb02" 
		0 7 "L_Thumb_locator.rotateZ" 2 46 "L_Thumb_locator.rotateY" 2 
		47 "L_Thumb_locator.rotateX" 2 48 "L_Fingers_locator.Fingers02" 0 
		8 "L_Fingers_locator.rotateZ" 2 49 "Weap_hand_locator.rotateZ" 2 
		50 "Weap_hand_locator.rotateY" 2 51 "Weap_hand_locator.rotateX" 2 
		52 "Weap_hand_locator.translateZ" 1 85 "Weap_hand_locator.translateY" 
		1 86 "Weap_hand_locator.translateX" 1 87 "R_Thumb_locator.Thumb02" 
		0 9 "R_Thumb_locator.rotateZ" 2 53 "R_Thumb_locator.rotateY" 2 
		54 "R_Thumb_locator.rotateX" 2 55 "R_Fingers_locator.Fingers02" 0 
		10 "R_Fingers_locator.rotateZ" 2 56 "Spine_locator.rotateZ" 2 63 "Spine_locator.rotateY" 
		2 64 "Spine_locator.rotateX" 2 65 "Horse_R_Thig_locator.rotateZ" 
		2 72 "Horse_R_Thig_locator.rotateY" 2 73 "Horse_R_Thig_locator.rotateX" 
		2 74 "Horse_L_Thig_locator1.rotateZ" 2 75 "Horse_L_Thig_locator1.rotateY" 
		2 76 "Horse_L_Thig_locator1.rotateX" 2 77 "Horse_Neck_locator.rotateZ" 
		2 81 "Horse_Neck_locator.rotateY" 2 82 "Horse_Neck_locator.rotateX" 
		2 83 "R_Ear_locator.rotateZ" 2 84 "R_Ear_locator.rotateY" 2 
		85 "R_Ear_locator.rotateX" 2 86 "L_Ear_locator.rotateZ" 2 87 "L_Ear_locator.rotateY" 
		2 88 "L_Ear_locator.rotateX" 2 89 "Horse_Hip_locator.rotateZ" 2 
		90 "Horse_Hip_locator.rotateY" 2 91 "Horse_Hip_locator.rotateX" 2 
		92 "Horse_Hip_locator.translateZ" 1 115 "Horse_Hip_locator.translateY" 
		1 116 "Horse_Hip_locator.translateX" 1 117 "Horse_L_B_Elbow_locator.translateZ" 
		1 121 "Horse_L_B_Elbow_locator.translateY" 1 122 "Horse_L_B_Elbow_locator.translateX" 
		1 123 "Horse_R_B_Elbow_locator1.translateZ" 1 124 "Horse_R_B_Elbow_locator1.translateY" 
		1 125 "Horse_R_B_Elbow_locator1.translateX" 1 126 "Horse_L_F_Elbow_locator.translateZ" 
		1 127 "Horse_L_F_Elbow_locator.translateY" 1 128 "Horse_L_F_Elbow_locator.translateX" 
		1 129 "Horse_R_F_Elbow_locator1.translateZ" 1 130 "Horse_R_F_Elbow_locator1.translateY" 
		1 131 "Horse_R_F_Elbow_locator1.translateX" 1 132 "Horse_L_F_Leg_locator.rotateZ" 
		2 93 "Horse_L_F_Leg_locator.rotateY" 2 94 "Horse_L_F_Leg_locator.rotateX" 
		2 95 "Horse_L_F_Leg_locator.translateZ" 1 133 "Horse_L_F_Leg_locator.translateY" 
		1 134 "Horse_L_F_Leg_locator.translateX" 1 135 "Horse_R_F_Leg_locator1.rotateZ" 
		2 96 "Horse_R_F_Leg_locator1.rotateY" 2 97 "Horse_R_F_Leg_locator1.rotateX" 
		2 98 "Horse_R_F_Leg_locator1.translateZ" 1 136 "Horse_R_F_Leg_locator1.translateY" 
		1 137 "Horse_R_F_Leg_locator1.translateX" 1 138 "Horse_L_B_Leg_locator1.rotateZ" 
		2 99 "Horse_L_B_Leg_locator1.rotateY" 2 100 "Horse_L_B_Leg_locator1.rotateX" 
		2 101 "Horse_L_B_Leg_locator1.translateZ" 1 139 "Horse_L_B_Leg_locator1.translateY" 
		1 140 "Horse_L_B_Leg_locator1.translateX" 1 141 "Horse_R_B_Leg_locator2.rotateZ" 
		2 102 "Horse_R_B_Leg_locator2.rotateY" 2 103 "Horse_R_B_Leg_locator2.rotateX" 
		2 104 "Horse_R_B_Leg_locator2.translateZ" 1 142 "Horse_R_B_Leg_locator2.translateY" 
		1 143 "Horse_R_B_Leg_locator2.translateX" 1 144 "Horse_Head_Top_locator1.translateZ" 
		1 145 "Horse_Head_Top_locator1.translateY" 1 146 "Horse_Head_Top_locator1.translateX" 
		1 147 "Global.Mark" 0 12 "Horse_mesh.Transparency" 0 13 "Shield_mesh.Transparency" 
		0 15 "Hip|Chest|Head|tail|tail2.rotateZ" 2 105 "Hip|Chest|Head|tail|tail2.rotateY" 
		2 106 "Hip|Chest|Head|tail|tail2.rotateX" 2 107 "Hip|Chest|Head|tail.rotateZ" 
		2 108 "Hip|Chest|Head|tail.rotateY" 2 109 "Hip|Chest|Head|tail.rotateX" 
		2 110 "tail3.rotateZ" 2 111 "tail3.rotateY" 2 112 "tail3.rotateX" 
		2 113 "Hip|Chest|Head.rotateZ" 2 114 "Hip|Chest|Head.rotateY" 2 
		115 "Hip|Chest|Head.rotateX" 2 116 "tail1.rotateZ" 2 117 "tail1.rotateY" 
		2 118 "tail1.rotateX" 2 119 "HorseHip|tail.rotateZ" 2 120 "HorseHip|tail.rotateY" 
		2 121 "HorseHip|tail.rotateX" 2 122 "tail1|tail2.rotateZ" 2 
		123 "tail1|tail2.rotateY" 2 124 "tail1|tail2.rotateX" 2 125 "HorseHip.rotateZ" 
		2 126 "HorseHip.rotateY" 2 127 "HorseHip.rotateX" 2 128 "HorseHip.translateZ" 
		1 148 "HorseHip.translateY" 1 149 "HorseHip.translateX" 1 150  ;
	setAttr ".cd[0].cim" -type "Int32Array" 172 36 37 38 39 40
		 41 42 43 44 57 58 59 60 61 62 63 64
		 65 66 67 68 69 70 71 72 73 74 75 76
		 77 78 79 80 81 82 83 84 85 86 87 88
		 89 90 91 92 93 94 95 96 123 124 125 126
		 127 128 129 130 131 132 133 134 135 136 137 138
		 139 140 141 142 143 144 145 146 147 148 149 150
		 151 152 159 160 161 174 175 176 177 178 179 205
		 206 207 208 209 210 211 212 213 214 215 216 217
		 218 219 223 224 225 226 227 228 229 230 231 232
		 233 234 235 236 237 238 239 240 241 242 243 244
		 245 246 247 248 249 250 251 252 253 254 255 256
		 257 258 259 260 261 325 326 328 0 1 2 3
		 4 5 6 7 8 9 10 11 12 13 14 15
		 16 17 18 19 20 21 22 23 24 25 26 ;
createNode animClip -n "runSource";
	setAttr ".ihi" 0;
	setAttr -s 149 ".ac";
	setAttr ".ac[0:20]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes;
	setAttr ".ac[36:44]" yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[58:63]" yes yes yes yes yes yes;
	setAttr ".ac[65:76]" yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[78:83]" yes yes yes yes yes yes;
	setAttr ".ac[85:96]" yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[123:134]" yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[136:138]" yes yes yes;
	setAttr ".ac[140:146]" yes yes yes yes yes yes yes;
	setAttr ".ac[148:150]" yes yes yes;
	setAttr ".ac[152]" yes;
	setAttr ".ac[159:161]" yes yes yes;
	setAttr ".ac[174:179]" yes yes yes yes yes yes;
	setAttr ".ac[205:207]" yes yes yes;
	setAttr ".ac[214:219]" yes yes yes yes yes yes;
	setAttr ".ac[223:261]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes;
	setAttr ".se" 20;
	setAttr ".ci" no;
createNode animCurveTA -n "tail2_rotateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 20 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
	setAttr -s 2 ".kix[0:1]"  1 1;
	setAttr -s 2 ".kiy[0:1]"  0 0;
	setAttr -s 2 ".kox[0:1]"  1 1;
	setAttr -s 2 ".koy[0:1]"  0 0;
createNode animCurveTA -n "tail2_rotateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 20 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
	setAttr -s 2 ".kix[0:1]"  1 1;
	setAttr -s 2 ".kiy[0:1]"  0 0;
	setAttr -s 2 ".kox[0:1]"  1 1;
	setAttr -s 2 ".koy[0:1]"  0 0;
createNode animCurveTA -n "tail2_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -20.730087684015032 3 -25.905184615573116 
		6 -18.748317106568582 8 1.0155819016184295 11 8.5279600043147568 20 -20.730087684015032;
	setAttr -s 6 ".kit[1:5]"  3 10 1 1 1;
	setAttr -s 6 ".kot[1:5]"  3 10 1 1 1;
	setAttr -s 6 ".kix[0:5]"  0.5068773627281189 1 0.33430936932563782 
		0.21126006543636322 0.84640485048294067 0.50434297323226929;
	setAttr -s 6 ".kiy[0:5]"  -0.86201822757720947 0 0.94246339797973633 
		0.97742992639541626 -0.532539963722229 -0.86350345611572266;
	setAttr -s 6 ".kox[0:5]"  0.50687748193740845 1 0.33430936932563782 
		0.21126009523868561 0.84640485048294067 0.50434309244155884;
	setAttr -s 6 ".koy[0:5]"  -0.8620181679725647 0 0.94246339797973633 
		0.97742986679077148 -0.532539963722229 -0.86350345611572266;
createNode animCurveTA -n "tail_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.6435770815818531 20 1.6435770815818531;
createNode animCurveTA -n "tail_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -8.4321922555201851 20 -8.4321922555201851;
createNode animCurveTA -n "tail_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -25.342192845941312 3 -8.9797090864088478 
		8 -7.353764588855876 11 -11.957612627556715 20 -25.342192845941312;
	setAttr -s 5 ".kit[0:4]"  3 1 1 1 3;
	setAttr -s 5 ".kot[0:4]"  3 1 1 1 3;
	setAttr -s 5 ".kix[1:4]"  0.5823366641998291 0.85511481761932373 
		0.68467932939529419 1;
	setAttr -s 5 ".kiy[1:4]"  0.81294775009155273 -0.51843869686126709 
		-0.72884446382522583 0;
	setAttr -s 5 ".kox[1:4]"  0.58233660459518433 0.85511475801467896 
		0.68467926979064941 1;
	setAttr -s 5 ".koy[1:4]"  0.81294780969619751 -0.51843869686126709 
		-0.72884446382522583 0;
createNode animCurveTA -n "tail3_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 3 0 20 0;
	setAttr -s 3 ".kit[0:2]"  1 10 10;
	setAttr -s 3 ".kot[0:2]"  1 10 10;
	setAttr -s 3 ".kix[0:2]"  1 1 1;
	setAttr -s 3 ".kiy[0:2]"  0 0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode animCurveTA -n "tail3_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 3 0 20 0;
	setAttr -s 3 ".kit[0:2]"  1 10 10;
	setAttr -s 3 ".kot[0:2]"  1 10 10;
	setAttr -s 3 ".kix[0:2]"  1 1 1;
	setAttr -s 3 ".kiy[0:2]"  0 0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode animCurveTA -n "tail3_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -17.929079477298764 3 -23.72813658086698 
		8 -2.2558059131460073 11 6.7995556019286481 20 -17.929079477298764;
	setAttr -s 5 ".kit[1:4]"  3 1 3 1;
	setAttr -s 5 ".kot[1:4]"  3 1 3 1;
	setAttr -s 5 ".kix[0:4]"  0.43475267291069031 1 0.32701995968818665 
		1 0.44011223316192627;
	setAttr -s 5 ".kiy[0:4]"  -0.90054994821548462 0 0.94501739740371704 
		0 -0.89794278144836426;
	setAttr -s 5 ".kox[0:4]"  0.43475249409675598 1 0.32701990008354187 
		1 0.44011232256889343;
	setAttr -s 5 ".koy[0:4]"  -0.90055006742477417 0 0.94501745700836182 
		0 -0.89794278144836426;
createNode animCurveTA -n "Head_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 11 0 13 0 20 0;
createNode animCurveTA -n "Head_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 11 0 13 0 20 0;
createNode animCurveTA -n "Head_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -17.10181990704158 2 -19.642748895081979 
		5 -16.29156512653902 8 -19.101851452935843 11 -13.044874625408699 13 -17.041752261280415 
		20 -17.10181990704158;
createNode animCurveTA -n "tail1_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -21.307035143729429 13 -21.307035143729451 
		20 -21.307035143729429;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "tail1_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.81931241346511319 13 -0.81931241346510997 
		20 -0.81931241346511319;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "tail1_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -32.357651034590006 2 -23.162508340687193 
		4 -14.362858388063991 9 2.6236853835069662 13 -20.960435651347989 17 -40.18208125320897 
		20 -32.357651034590006;
	setAttr -s 7 ".kit[1:6]"  10 1 1 1 3 1;
	setAttr -s 7 ".kot[1:6]"  10 1 1 1 3 1;
	setAttr -s 7 ".kix[0:6]"  0.40337562561035156 0.39077886939048767 
		0.42785796523094177 0.96728283166885376 0.24824997782707214 1 0.40828853845596313;
	setAttr -s 7 ".kiy[0:6]"  0.91503447294235229 0.92048460245132446 
		0.90384602546691895 -0.25370058417320251 -0.96869605779647827 0 0.912852942943573;
	setAttr -s 7 ".kox[0:6]"  0.40337583422660828 0.39077886939048767 
		0.42785793542861938 0.96728289127349854 0.24824997782707214 1 0.40828877687454224;
	setAttr -s 7 ".koy[0:6]"  0.91503447294235229 0.92048460245132446 
		0.90384608507156372 -0.25370058417320251 -0.96869605779647827 0 0.91285288333892822;
createNode animCurveTA -n "tail_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -1.7207319971292734 2 -1.7207319971292798 
		6 -1.7207319971292796 9 -1.7207319971292796 13 -1.7207319971292765 17 -1.7207319971292754 
		20 -1.7207319971292734;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "tail_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -3.6860332002236964 2 -3.6860332002237062 
		6 -3.6860332002236964 9 -3.6860332002237026 13 -3.6860332002237093 17 -3.6860332002237044 
		20 -3.6860332002236964;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "tail_rotateX1";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 27.789466082370918 2 35.459226972056889 
		6 40.907120104549847 9 27.008855541741426 13 13.061714253239769 20 27.789466082370918;
	setAttr -s 6 ".kix[0:5]"  0.45045819878578186 0.5009075403213501 
		0.89840120077133179 0.40240553021430969 0.71985125541687012 0.45535621047019958;
	setAttr -s 6 ".kiy[0:5]"  0.89279752969741821 0.865500807762146 -0.43917575478553772 
		-0.91546154022216797 -0.69412839412689209 0.89030939340591431;
	setAttr -s 6 ".kox[0:5]"  0.45045799016952515 0.5009077787399292 
		0.89840120077133179 0.40240558981895447 0.71985131502151489 0.4553561806678772;
	setAttr -s 6 ".koy[0:5]"  0.89279764890670776 0.86550074815750122 
		-0.43917578458786011 -0.91546154022216797 -0.69412833452224731 0.89030939340591431;
createNode animCurveTA -n "tail2_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.69541506121312102 4 -1.5856249966598797 
		9 6.3097789938151569 13 -0.69541506121312469 17 -0.69541506121312613 20 -0.69541506121312102;
	setAttr -s 6 ".kit[5]"  1;
	setAttr -s 6 ".kot[5]"  1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTA -n "tail2_rotateY1";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.53675210472901158 4 -10.581051170628232 
		9 -3.2945547230399188 13 -0.53675210472900825 17 -0.5367521047290077 20 -0.53675210472901158;
	setAttr -s 6 ".kit[2:5]"  1 10 10 3;
	setAttr -s 6 ".kot[2:5]"  1 10 10 3;
	setAttr -s 6 ".kix[2:5]"  0.79832881689071655 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0.60222190618515015 0 0 0;
	setAttr -s 6 ".kox[2:5]"  0.79832857847213745 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0.60222214460372925 0 0 0;
createNode animCurveTA -n "tail2_rotateX1";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -24.737077588176479 4 -34.34835809483458 
		8 -31.523506873197071 9 1.7678160274446968 13 4.0362457040791044 17 -45.254951150066482 
		20 -24.737077588176479;
	setAttr -s 7 ".kit[0:6]"  3 1 1 1 1 3 3;
	setAttr -s 7 ".kot[0:6]"  3 1 1 1 1 3 3;
	setAttr -s 7 ".kix[1:6]"  0.85960954427719116 0.43046608567237854 
		0.44371992349624634 0.67642307281494141 1 1;
	setAttr -s 7 ".kiy[1:6]"  -0.51095157861709595 0.9026067852973938 
		0.89616554975509644 -0.73651337623596191 0 0;
	setAttr -s 7 ".kox[1:6]"  0.85960954427719116 0.43046602606773376 
		0.44371989369392395 0.67642313241958618 1 1;
	setAttr -s 7 ".koy[1:6]"  -0.51095157861709595 0.9026067852973938 
		0.89616554975509644 -0.73651331663131714 0 0;
createNode animCurveTA -n "animCurveTA72";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 8 0 16 0 20 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  0.1666666716337204;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.1666666716337204;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA73";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 8 0 16 0 20 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  0.1666666716337204;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  0.1666666716337204;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA74";
	setAttr ".tan" 1;
	setAttr -s 8 ".ktv[0:7]"  0 26.968901749837439 2 28.09367684926027 
		5 22.752452033847721 8 22.627472691104355 11 15.223924154039652 13 10.379993040551501 
		16 13.694040111574479 20 26.968901749837439;
	setAttr -s 8 ".kit[2:7]"  10 10 1 3 1 1;
	setAttr -s 8 ".kot[2:7]"  10 10 1 3 1 1;
	setAttr -s 8 ".kix[0:7]"  0.037373077124357224 0.058242976665496826 
		0.10000000149011612 0.10000000894069672 0.081044740974903107 0.066666662693023682 
		0.092981241643428802 0.037373077124357224;
	setAttr -s 8 ".kiy[0:7]"  0.055406510829925537 -0.025644019246101379 
		0 0 -0.14108921587467194 0 0.12946578860282898 0.055406510829925537;
	setAttr -s 8 ".kox[0:7]"  0.037373054772615433 0.09157533198595047 
		0.10000000894069672 0.099999994039535522 0.047718401998281479 0.10000002384185791 
		0.1263125091791153 0.037373054772615433;
	setAttr -s 8 ".koy[0:7]"  0.055406484752893448 -0.040320046246051788 
		0 0 -0.083072029054164886 0 0.17587576806545258 0.055406484752893448;
createNode animCurveTL -n "animCurveTL64";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 0.14270078018222057;
createNode animCurveTL -n "animCurveTL65";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 -1.1683380213237218;
createNode animCurveTL -n "animCurveTL66";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 -0.13199843516776633;
createNode animCurveTL -n "animCurveTL67";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 0.22286510145816385;
createNode animCurveTL -n "animCurveTL68";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 -1.2247604743509974;
createNode animCurveTL -n "animCurveTL69";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 0.037767030045364025;
createNode animCurveTA -n "animCurveTA75";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 -73.602423831773578;
createNode animCurveTA -n "animCurveTA76";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 9.0217836106106422;
createNode animCurveTA -n "animCurveTA77";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 -89.440220508879349;
createNode animCurveTL -n "animCurveTL70";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 0.24505854477883987;
createNode animCurveTL -n "animCurveTL71";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 -1.2139723024096749;
createNode animCurveTL -n "animCurveTL72";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 -0.26960515313545896;
createNode animCurveTA -n "Champion_R_Hand_locator_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 79.173060709277962 2 79.173060709278005 
		5 79.173060709277948 7 79.173060709277962 11 79.173060709277976 20 79.173060709277962;
	setAttr -s 6 ".kit[5]"  1;
	setAttr -s 6 ".kot[5]"  1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTA -n "Champion_R_Hand_locator_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 15.10319526336513 2 17.640974701438534 
		5 21.335987084297372 7 24.334912369411672 11 27.818379783386959 14 29.615792461225151 
		20 15.10319526336513;
	setAttr -s 7 ".kit[6]"  1;
	setAttr -s 7 ".kot[6]"  1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "Champion_R_Hand_locator_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -54.324242615618004 2 -54.324242615618097 
		5 -54.324242615618111 7 -54.324242615618239 11 -54.324242615618211 20 -54.324242615618004;
	setAttr -s 6 ".kit[5]"  1;
	setAttr -s 6 ".kot[5]"  1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTL -n "Champion_R_Hand_locator_translateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.36690323259792557 2 0.38517723635075046 
		5 0.389953570200684 7 0.38968310871763412 11 0.36623160244084318 14 0.36332110141524043 
		20 0.36690323259792557;
	setAttr -s 7 ".kix[0:6]"  0.99875336885452271 0.99681270122528076 
		0.9998815655708313 0.99979662895202637 0.99824029207229614 0.99996328353881836 0.99875336885452271;
	setAttr -s 7 ".kiy[0:6]"  0.049916937947273254 0.079777754843235016 
		0.015392289496958256 -0.020167360082268715 -0.059299040585756302 -0.0085731949657201767 
		0.049916937947273254;
	setAttr -s 7 ".kox[0:6]"  0.99875336885452271 0.99681270122528076 
		0.9998815655708313 0.99979662895202637 0.99824035167694092 0.99996328353881836 0.99875336885452271;
	setAttr -s 7 ".koy[0:6]"  0.049916923046112061 0.079777725040912628 
		0.01539229042828083 -0.020167356356978416 -0.059299062937498093 -0.0085731940343976021 
		0.049916923046112061;
createNode animCurveTL -n "Champion_R_Hand_locator_translateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -1.122198288967909 2 -1.1156437115139732 
		5 -1.0888733259221179 7 -1.069027935132745 11 -1.0398813284991 14 -1.0410705592112173 
		20 -1.122198288967909;
	setAttr -s 7 ".kit[0:6]"  3 1 1 1 1 1 1;
	setAttr -s 7 ".kot[0:6]"  3 1 1 1 1 1 1;
	setAttr -s 7 ".kix[1:6]"  0.97994863986968994 0.95805156230926514 
		0.96925067901611328 0.99474763870239258 0.99609428644180298 1;
	setAttr -s 7 ".kiy[1:6]"  0.19925028085708618 0.28659600019454956 
		0.24607560038566589 0.10235777497291565 -0.088296078145503998 0;
	setAttr -s 7 ".kox[1:6]"  0.97994863986968994 0.95805156230926514 
		0.96925067901611328 0.99474763870239258 0.99609428644180298 1;
	setAttr -s 7 ".koy[1:6]"  0.19925041496753693 0.28659579157829285 
		0.24607579410076141 0.10235780477523804 -0.088296100497245789 0;
createNode animCurveTL -n "Champion_R_Hand_locator_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.13396473534770226 2 0.13396473534770226 
		5 0.13396473534770226 11 0.13396473534770226 20 0.13396473534770226;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL76";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 -0.085735089861745051;
createNode animCurveTL -n "animCurveTL77";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 -0.77678862872328902;
createNode animCurveTL -n "animCurveTL78";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 -0.32758782380619483;
createNode animCurveTL -n "animCurveTL79";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 -0.022529174976866462;
createNode animCurveTL -n "animCurveTL80";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 -0.73857428521639856;
createNode animCurveTL -n "animCurveTL81";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 0.33779863130171084;
createNode animCurveTA -n "Champion_R_Leg_locator_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -13.572416046402303 7 -13.572416046402303 
		11 -14.945412754201984 15 -14.945412754201969 20 -13.572416046402303;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "Champion_R_Leg_locator_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -14.142482270778586 7 -14.142482270778586 
		11 -13.387386238799605 15 -13.387386238799603 20 -14.142482270778586;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "Champion_R_Leg_locator_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 10.977096423896258 3 14.380469847146784 
		7 7.546442667033423 11 0.88981141468525804 15 -2.6658852982116819 20 10.977096423896258;
	setAttr -s 6 ".kit[1:5]"  3 1 1 3 1;
	setAttr -s 6 ".kot[1:5]"  3 1 1 3 1;
	setAttr -s 6 ".kix[0:5]"  0.62143397331237793 1 0.69687169790267944 
		0.79353451728820801 1 0.61836814880371094;
	setAttr -s 6 ".kiy[0:5]"  0.78346657752990723 0 -0.71719586849212646 
		-0.60852533578872681 0 0.78588855266571045;
	setAttr -s 6 ".kox[0:5]"  0.62143391370773315 1 0.69687169790267944 
		0.79353445768356323 1 0.61836832761764526;
	setAttr -s 6 ".koy[0:5]"  0.783466637134552 0 -0.71719586849212646 
		-0.60852527618408203 0 0.7858884334564209;
createNode animCurveTL -n "Champion_R_Leg_locator_translateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.12828411471898454 3 0.14740989247466851 
		7 0.16783448205179408 11 0.14679416837031437 15 0.13434881164901141 20 0.12828411471898454;
	setAttr -s 6 ".kit[0:5]"  10 1 10 1 1 1;
	setAttr -s 6 ".kot[0:5]"  10 1 10 1 1 1;
	setAttr -s 6 ".kix[1:5]"  0.97310429811477661 1 0.99329072237014771 
		0.99800759553909302 1;
	setAttr -s 6 ".kiy[1:5]"  0.23036520183086395 0 -0.11564411222934723 
		-0.063094235956668854 0;
	setAttr -s 6 ".kox[1:5]"  0.97310423851013184 1 0.99329078197479248 
		0.99800759553909302 1;
	setAttr -s 6 ".koy[1:5]"  0.23036536574363708 0 -0.11564412713050842 
		-0.06309422105550766 0;
createNode animCurveTL -n "Champion_R_Leg_locator_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.78981072570246968 3 -0.78556566352358492 
		7 -0.77278541513631149 11 -0.76412617104972569 15 -0.79092656092174396 20 -0.78981072570246968;
	setAttr -s 6 ".kit[1:5]"  1 1 10 3 3;
	setAttr -s 6 ".kot[1:5]"  1 1 10 3 3;
	setAttr -s 6 ".kix[1:5]"  0.99768418073654175 0.99539518356323242 
		1 1 1;
	setAttr -s 6 ".kiy[1:5]"  0.068017140030860901 0.095856659114360809 
		0 0 0;
	setAttr -s 6 ".kox[1:5]"  0.99768418073654175 0.99539518356323242 
		1 1 1;
	setAttr -s 6 ".koy[1:5]"  0.068017162382602692 0.095856659114360809 
		0 0 0;
createNode animCurveTL -n "Champion_R_Leg_locator_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.36143794093182707 20 -0.36143794093182707;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr -s 2 ".kox[1]"  1;
	setAttr -s 2 ".koy[1]"  0;
createNode animCurveTA -n "Champion_L_Leg_locator_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 16.92811612017594 7 16.928116120175936 
		11 15.4927979632808 15 15.4927979632808 20 16.92811612017594;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "Champion_L_Leg_locator_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 13.158990081775368 7 13.158990081775366 
		11 13.791673034224255 15 13.791673034224248 20 13.158990081775368;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "Champion_L_Leg_locator_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 6.1718269023380978 3 9.5752003255886287 
		7 2.741173145475261 11 -4.5766585873914991 15 -8.1323553002884363 20 6.1718269023380978;
	setAttr -s 6 ".kit[1:5]"  3 1 1 3 1;
	setAttr -s 6 ".kot[1:5]"  3 1 1 3 1;
	setAttr -s 6 ".kix[0:5]"  0.61167418956756592 1 0.64235854148864746 
		0.77419793605804443 1 0.60859775543212891;
	setAttr -s 6 ".kiy[0:5]"  0.79110985994338989 0 -0.76640433073043823 
		-0.63294357061386108 0 0.79347890615463257;
	setAttr -s 6 ".kox[0:5]"  0.61167418956756592 1 0.64235848188400269 
		0.77419787645339966 1 0.60859745740890503;
	setAttr -s 6 ".koy[0:5]"  0.79110985994338989 0 -0.76640433073043823 
		-0.63294368982315063 0 0.79347920417785645;
createNode animCurveTL -n "Champion_L_Leg_locator_translateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.14808794515731319 3 0.16605047681497334 
		7 0.18763831249012272 11 0.17008773710271444 15 0.15461794052654959 20 0.14808794515731319;
	setAttr -s 6 ".kit[0:5]"  10 1 10 1 1 1;
	setAttr -s 6 ".kot[0:5]"  10 1 10 1 1 1;
	setAttr -s 6 ".kix[1:5]"  0.96828716993331909 1 0.9905356764793396 
		0.99678468704223633 1;
	setAttr -s 6 ".kiy[1:5]"  0.24984002113342285 0 -0.13725565373897552 
		-0.08012671023607254 0;
	setAttr -s 6 ".kox[1:5]"  0.96828711032867432 1 0.9905356764793396 
		0.99678468704223633 1;
	setAttr -s 6 ".koy[1:5]"  0.2498401552438736 0 -0.1372557133436203 
		-0.080126725137233734 0;
createNode animCurveTL -n "Champion_L_Leg_locator_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.79503643999100104 3 -0.79079137781211628 
		7 -0.77801112942484285 11 -0.76935188533825705 15 -0.79615227521027532 20 -0.79503643999100104;
	setAttr -s 6 ".kit[1:5]"  1 1 10 10 1;
	setAttr -s 6 ".kot[1:5]"  1 1 10 10 1;
	setAttr -s 6 ".kix[1:5]"  0.99639099836349487 0.99476343393325806 
		1 1 1;
	setAttr -s 6 ".kiy[1:5]"  0.084882393479347229 0.1022043377161026 
		0 0 0;
	setAttr -s 6 ".kox[1:5]"  0.99639099836349487 0.99476343393325806 
		1 1 1;
	setAttr -s 6 ".koy[1:5]"  0.084882430732250214 0.10220435261726379 
		0 0 0;
createNode animCurveTL -n "Champion_L_Leg_locator_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.33351765877991613 20 0.33351765877991613;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr -s 2 ".kox[1]"  1;
	setAttr -s 2 ".koy[1]"  0;
createNode animCurveTA -n "Champion_Hip_locator_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 16 0 20 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "Champion_Hip_locator_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 2 0 16 0 20 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "Champion_Hip_locator_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -3.3984371450761697 2 3.0756395864457855 
		16 -5.3693296873797394 20 -3.3984371450761697;
	setAttr -s 4 ".kix[0:3]"  0.6643521785736084 0.97821295261383057 
		0.98347336053848267 0.67315375804901123;
	setAttr -s 4 ".kiy[0:3]"  0.74741971492767334 0.2076040655374527 
		-0.18105287849903107 0.73950254917144775;
	setAttr -s 4 ".kox[0:3]"  0.66435205936431885 0.97821295261383057 
		0.98347336053848267 0.67315363883972168;
	setAttr -s 4 ".koy[0:3]"  0.74741983413696289 0.20760408043861389 
		-0.18105290830135345 0.7395026683807373;
createNode animCurveTL -n "Champion_Hip_locator_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.0012780248100237876 2 -0.0012780248100237876 
		6 -0.00013254943309620303 8 -0.00082874799794293002 11 -0.0051577032934784989 13 
		-0.0056818890466725164 16 -0.005977387885773692 20 -0.0012780248100237876;
	setAttr -s 8 ".kit[3:7]"  1 1 1 10 1;
	setAttr -s 8 ".kot[3:7]"  1 1 1 10 1;
	setAttr -s 8 ".kix[3:7]"  0.99974042177200317 0.9999614953994751 
		0.99997222423553467 1 1;
	setAttr -s 8 ".kiy[3:7]"  -0.022783169522881508 -0.0087756365537643433 
		-0.0074573047459125519 0 0;
	setAttr -s 8 ".kox[3:7]"  0.99974042177200317 0.9999614953994751 
		0.99997222423553467 1 1;
	setAttr -s 8 ".koy[3:7]"  -0.022783165797591209 -0.008775634691119194 
		-0.0074573038145899773 0 0;
createNode animCurveTL -n "Champion_Hip_locator_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.94610970165484987 2 -0.94610970165484987 
		6 -0.93267673283991315 8 -0.93624944312146852 11 -0.95494592755421415 13 -0.94569702901271213 
		16 -0.93180735606978504 20 -0.94610970165484987;
	setAttr -s 8 ".kit[3:7]"  1 10 1 10 1;
	setAttr -s 8 ".kot[3:7]"  1 10 1 10 1;
	setAttr -s 8 ".kix[3:7]"  0.99488168954849243 1 0.98450690507888794 
		1 1;
	setAttr -s 8 ".kiy[3:7]"  -0.10104658454656601 0 0.17534589767456055 
		0 0;
	setAttr -s 8 ".kox[3:7]"  0.99488168954849243 1 0.98450690507888794 
		1 1;
	setAttr -s 8 ".koy[3:7]"  -0.10104656219482422 0 0.1753460168838501 
		0 0;
createNode animCurveTL -n "Champion_Hip_locator_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 6 0 11 0 20 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "animCurveTA90";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 9.8356685883660511;
createNode animCurveTA -n "animCurveTA91";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 -9.3261534711754361;
createNode animCurveTA -n "animCurveTA92";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 2.3853567319547375;
createNode animCurveTA -n "animCurveTA93";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 30.354203916720014;
createNode animCurveTA -n "animCurveTA94";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 17.177439676111732;
createNode animCurveTA -n "animCurveTA95";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 16.28504424923808;
createNode animCurveTA -n "animCurveTA96";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 -0.014935073133263735;
createNode animCurveTA -n "animCurveTA97";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 187.5796802179496;
createNode animCurveTA -n "animCurveTA98";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 -92.34331294293078;
createNode animCurveTL -n "animCurveTL91";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 -0.019566644519235961;
createNode animCurveTL -n "animCurveTL92";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 0.085900421379315375;
createNode animCurveTL -n "animCurveTL93";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 -0.0032546051995154474;
createNode animCurveTA -n "animCurveTA99";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 -31.020612655123333;
createNode animCurveTA -n "animCurveTA100";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 11.198285947268632;
createNode animCurveTA -n "animCurveTA101";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 4.823799912124791;
createNode animCurveTA -n "animCurveTA102";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 -33.118292212018972;
createNode animCurveTA -n "animCurveTA103";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 -1.2808772232691179;
createNode animCurveTA -n "animCurveTA104";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 -2.8759112065701404;
createNode animCurveTA -n "animCurveTA105";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 90.653592159103439;
createNode animCurveTL -n "animCurveTL94";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 0.002388170883337609;
createNode animCurveTL -n "animCurveTL95";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 0.084972716487962008;
createNode animCurveTL -n "animCurveTL96";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 0.035778931447803565;
createNode animCurveTA -n "animCurveTA106";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 27.45475670134093;
createNode animCurveTA -n "animCurveTA107";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 0;
createNode animCurveTA -n "animCurveTA108";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 16.11950950967347;
createNode animCurveTA -n "animCurveTA109";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 5.617037998813025;
createNode animCurveTA -n "animCurveTA110";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0 8 0 20 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  0.26666668057441711;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  0.26666668057441711;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "animCurveTA111";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0 8 0 20 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  0.26666668057441711;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  0.26666668057441711;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "animCurveTA112";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 7.3802851200190229 2 5.1465678304472302 
		4 5.1525713381728124 8 1.2602009783444215 11 -2.6270084529552307 13 -1.5844912026092595 
		15 -2.167250651781957 20 7.3802851200190229;
	setAttr -s 8 ".kit[0:7]"  3 10 10 1 3 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 1 3 10 10 3;
	setAttr -s 8 ".kix[3:7]"  0.21318235993385315 0.099999994039535522 
		0.066666662693023682 0.066666662693023682 0.16666668653488159;
	setAttr -s 8 ".kiy[3:7]"  -0.15315678715705872 0 0 0 0;
	setAttr -s 8 ".kox[3:7]"  0.079865574836730957 0.066666662693023682 
		0.066666662693023682 0.16666668653488159 0.16666668653488159;
	setAttr -s 8 ".koy[3:7]"  -0.057377923280000687 0 0 0 0;
createNode animCurveTA -n "animCurveTA113";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 0;
createNode animCurveTA -n "animCurveTA114";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 0;
createNode animCurveTA -n "animCurveTA115";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 -11.50204371272193;
createNode animCurveTA -n "animCurveTA116";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 -4.4907264049357849;
createNode animCurveTA -n "animCurveTA117";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 1.15889491647135;
createNode animCurveTA -n "animCurveTA118";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  5 -1.6969080274805199;
createNode animCurveTA -n "animCurveTA119";
	setAttr ".tan" 1;
	setAttr -s 2 ".ktv[0:1]"  0 0 20 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
	setAttr -s 2 ".kix[0:1]"  0.73333334922790527 0.66666668653488159;
	setAttr -s 2 ".kiy[0:1]"  0 0;
	setAttr -s 2 ".kox[0:1]"  0.73333334922790527 0.66666668653488159;
	setAttr -s 2 ".koy[0:1]"  0 0;
createNode animCurveTA -n "animCurveTA120";
	setAttr ".tan" 1;
	setAttr -s 2 ".ktv[0:1]"  0 0 20 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
	setAttr -s 2 ".kix[0:1]"  0.73333334922790527 0.66666668653488159;
	setAttr -s 2 ".kiy[0:1]"  0 0;
	setAttr -s 2 ".kox[0:1]"  0.73333334922790527 0.66666668653488159;
	setAttr -s 2 ".koy[0:1]"  0 0;
createNode animCurveTA -n "animCurveTA121";
	setAttr ".tan" 1;
	setAttr -s 7 ".ktv[0:6]"  0 -19.628090654943239 4 -29.597932454430556 
		6 -29.778869814791584 11 -6.1361745741796812 13 1.2640259573086547 17 -1.6124900058133098 
		20 -19.628090654943239;
	setAttr -s 7 ".kit[2:6]"  3 1 1 1 1;
	setAttr -s 7 ".kot[2:6]"  3 1 1 1 1;
	setAttr -s 7 ".kix[0:6]"  0.078204825520515442 0.13302195072174072 
		0.066666662693023682 0.16516293585300446 0.062958911061286926 0.12011982500553131 
		0.078204825520515442;
	setAttr -s 7 ".kiy[0:6]"  -0.15488974750041962 -0.013062277808785439 
		0 0.39513629674911499 0.034693032503128052 -0.17410467565059662 -0.15488974750041962;
	setAttr -s 7 ".kox[0:6]"  0.078204885125160217 0.066355317831039429 
		0.1666666716337204 0.031852953135967255 0.1296243816614151 0.12011978775262833 0.078204885125160217;
	setAttr -s 7 ".koy[0:6]"  -0.1548897922039032 -0.0065158545039594173 
		0 0.076205112040042877 0.071428552269935608 -0.17410463094711304 -0.1548897922039032;
createNode animCurveTA -n "Champion_Horse_Hip_locator_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 0 6 0 8 0 13 0 17 0 20 0;
	setAttr -s 7 ".kit[6]"  1;
	setAttr -s 7 ".kot[6]"  1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "Champion_Horse_Hip_locator_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 0 6 0 8 0 13 0 17 0 20 0;
	setAttr -s 7 ".kit[6]"  1;
	setAttr -s 7 ".kot[6]"  1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "Champion_Horse_Hip_locator_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -8.8958728371208444 4 -10.615871711392376 
		6 -7.2589672650597201 8 -7.4879851713604113 11 -1.5249169106519582 13 3.2437955643672818 
		15 2.2526171000398896 17 -0.12764470360289176 20 -8.8958728371208444;
	setAttr -s 9 ".kit[2:8]"  10 10 1 10 1 1 1;
	setAttr -s 9 ".kot[2:8]"  10 10 1 10 1 1 1;
	setAttr -s 9 ".kix[0:8]"  0.80951994657516479 0.98811399936676025 
		1 1 0.56853377819061279 1 0.88864874839782715 0.76443517208099365 0.8074684739112854;
	setAttr -s 9 ".kiy[0:8]"  -0.58709245920181274 0.15372321009635925 
		0 0 0.82265996932983398 0 -0.45858848094940186 -0.64470064640045166 -0.58991074562072754;
	setAttr -s 9 ".kox[0:8]"  0.80951970815658569 0.98811393976211548 
		1 1 0.56853377819061279 1 0.88864874839782715 0.76443517208099365 0.8074682354927063;
	setAttr -s 9 ".koy[0:8]"  -0.58709263801574707 0.15372322499752045 
		0 0 0.82265996932983398 0 -0.45858860015869141 -0.64470070600509644 -0.58991104364395142;
createNode animCurveTL -n "Champion_Horse_Hip_locator_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.022398622623901798 4 0.022398622623901798 
		6 0.022398622623901798 8 0.022398622623901798 9 0.022398622623901798 11 0.022398622623901798 
		17 0.022398622623901798 20 0.022398622623901798;
	setAttr -s 8 ".kit[7]"  1;
	setAttr -s 8 ".kot[7]"  1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTL -n "animCurveTL98";
	setAttr ".tan" 1;
	setAttr -s 10 ".ktv[0:9]"  0 -0.0089607622016299598 4 -0.069559786865130049 
		6 -0.14355550662808542 8 -0.1732221822938502 9 -0.16066762285920361 11 -0.1019991055454476 
		13 -0.058663802985431057 15 -0.027885386214449713 17 -0.012192160452041322 20 -0.0089607622016299598;
	setAttr -s 10 ".kit[0:9]"  3 1 1 10 1 1 1 1 
		1 3;
	setAttr -s 10 ".kot[0:9]"  3 1 1 10 1 1 1 1 
		1 3;
	setAttr -s 10 ".kix[1:9]"  0.07723052054643631 0.027593962848186493 
		0.066666677594184875 0.036650687456130981 0.045235581696033478 0.04232209175825119 
		0.057655565440654755 0.065497227013111115 0.10000002384185791;
	setAttr -s 10 ".kiy[1:9]"  -0.056134026497602463 -0.03075362928211689 
		0 0.027936451137065887 0.024357536807656288 0.026136986911296844 0.016704907640814781 
		0.0064208111725747585 0;
	setAttr -s 10 ".kox[1:9]"  0.038615245372056961 0.027593974024057388 
		0.033333331346511841 0.036650687456130981 0.045235585421323776 0.042322088032960892 
		0.057655535638332367 0.13099440932273865 0.10000002384185791;
	setAttr -s 10 ".koy[1:9]"  -0.028067013248801231 -0.030753623694181442 
		0 0.027936452999711037 0.02435753308236599 0.026136994361877441 0.016704894602298737 
		0.012841618619859219 0;
createNode animCurveTL -n "animCurveTL99";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 8 0 9 0 11 0 17 0 20 0;
	setAttr -s 8 ".kit[7]"  1;
	setAttr -s 8 ".kot[7]"  1;
	setAttr -s 8 ".kix[7]"  0.13333334028720856;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  0.13333334028720856;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTL -n "Champion_Horse_L_B_Elbow_locator_translateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.092482322949311913 4 0.14202165722963866 
		8 -0.2125941176751156 9 -0.2125941176751156 13 -0.29266864749231791 20 -0.092482322949311913;
	setAttr -s 6 ".kit[1:5]"  3 10 10 1 1;
	setAttr -s 6 ".kot[1:5]"  3 10 10 1 1;
	setAttr -s 6 ".kix[0:5]"  0.35852333903312683 1 1 1 0.99697631597518921 
		0.35500508546829224;
	setAttr -s 6 ".kiy[0:5]"  0.93352079391479492 0 0 0 -0.077706120908260345 
		0.93486440181732178;
	setAttr -s 6 ".kox[0:5]"  0.35852333903312683 1 1 1 0.99697631597518921 
		0.35500508546829224;
	setAttr -s 6 ".koy[0:5]"  0.93352073431015015 0 0 0 -0.077706143260002136 
		0.93486440181732178;
createNode animCurveTL -n "animCurveTL101";
	setAttr ".tan" 1;
	setAttr -s 6 ".ktv[0:5]"  0 -0.10932261951568766 4 -0.10932261951568766 
		8 0.090863705027318678 9 0.29105002957032489 13 0.43404026138675822 20 -0.10932261951568766;
	setAttr -s 6 ".kit[0:5]"  10 10 1 1 1 1;
	setAttr -s 6 ".kot[0:5]"  10 10 1 1 1 1;
	setAttr -s 6 ".kix[2:5]"  0.12208937853574753 0.050562713295221329 
		0.12978482246398926 0.13333334028720856;
	setAttr -s 6 ".kiy[2:5]"  0.28212824463844299 0.13629426062107086 
		-0.14327020943164825 0;
	setAttr -s 6 ".kox[2:5]"  0.061044685542583466 0.10112541168928146 
		0.25956970453262329 0.13333334028720856;
	setAttr -s 6 ".koy[2:5]"  0.1410641223192215 0.27258852124214172 
		-0.28654047846794128 0;
createNode animCurveTL -n "animCurveTL102";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 0 9 0 13 0 20 0;
	setAttr -s 6 ".kit[5]"  1;
	setAttr -s 6 ".kot[5]"  1;
	setAttr -s 6 ".kix[5]"  0.13333334028720856;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  0.13333334028720856;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTL -n "Champion_Horse_R_B_Elbow_locator1_translateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.091513748362517244 4 0.13107012162660459 
		9 -0.20598545292835158 15 -0.42220978377492724 20 -0.091513748362517244;
	setAttr -s 5 ".kit[1:4]"  3 1 3 1;
	setAttr -s 5 ".kot[1:4]"  3 1 3 1;
	setAttr -s 5 ".kix[0:4]"  0.36350727081298828 1 0.47145676612854004 
		1 0.36055341362953186;
	setAttr -s 5 ".kiy[0:4]"  0.93159139156341553 0 -0.88188916444778442 
		0 0.93273860216140747;
	setAttr -s 5 ".kox[0:4]"  0.36350727081298828 1 0.47145697474479675 
		1 0.36055329442024231;
	setAttr -s 5 ".koy[0:4]"  0.93159133195877075 0 -0.88188916444778442 
		0 0.93273860216140747;
createNode animCurveTL -n "Champion_Horse_R_B_Elbow_locator1_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -0.10356494090188484 9 0.074502155089412714 
		15 0.344782561709297 20 -0.10356494090188484;
	setAttr -s 4 ".kit[1:3]"  1 3 3;
	setAttr -s 4 ".kot[1:3]"  1 3 3;
	setAttr -s 4 ".kix[1:3]"  0.66541963815689087 1 1;
	setAttr -s 4 ".kiy[1:3]"  0.74646955728530884 0 0;
	setAttr -s 4 ".kox[1:3]"  0.66541963815689087 1 1;
	setAttr -s 4 ".koy[1:3]"  0.74646949768066406 0 0;
createNode animCurveTL -n "Champion_Horse_R_B_Elbow_locator1_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 9 0 15 0 20 0;
createNode animCurveTL -n "Champion_Horse_L_F_Elbow_locator_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.1747810957208229 4 0.72411879829055303 
		11 0.48317132462301704 20 0.1747810957208229;
	setAttr -s 4 ".kit[1:3]"  10 1 3;
	setAttr -s 4 ".kot[1:3]"  10 1 3;
	setAttr -s 4 ".kix[2:3]"  0.50630474090576172 1;
	setAttr -s 4 ".kiy[2:3]"  -0.86235463619232178 0;
	setAttr -s 4 ".kox[2:3]"  0.50630480051040649 1;
	setAttr -s 4 ".koy[2:3]"  -0.86235463619232178 0;
createNode animCurveTL -n "animCurveTL107";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  0 0.021677066875706585 4 0.21496255481690818 
		11 0.21282484171999738 20 0.021677066875706585;
	setAttr -s 4 ".kit[0:3]"  3 10 10 3;
	setAttr -s 4 ".kot[0:3]"  3 10 10 3;
createNode animCurveTL -n "animCurveTL108";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0 11 0 20 0;
createNode animCurveTL -n "Champion_Horse_R_F_Elbow_locator1_translateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.53153498364269192 4 0.72312967187181876 
		9 0.75564987854541721 15 0.37477078275576481 20 0.53153498364269192;
	setAttr -s 5 ".kit[3:4]"  10 1;
	setAttr -s 5 ".kot[3:4]"  10 1;
	setAttr -s 5 ".kix[0:4]"  0.58943665027618408 0.79171675443649292 
		0.97886276245117188 0.85323959589004517 0.59539788961410522;
	setAttr -s 5 ".kiy[0:4]"  0.80781465768814087 0.61088836193084717 
		-0.20451842248439789 -0.52151918411254883 0.80343103408813477;
	setAttr -s 5 ".kox[0:4]"  0.58943676948547363 0.7917168140411377 
		0.97886276245117188 0.85323959589004517 0.59539800882339478;
	setAttr -s 5 ".koy[0:4]"  0.80781459808349609 0.61088830232620239 
		-0.20451845228672028 -0.52151918411254883 0.80343085527420044;
createNode animCurveTL -n "animCurveTL110";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.086763698872975192 4 0.086763698872975192 
		20 0.086763698872975192;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  0.13333334028720856;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  0.13333334028720856;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "animCurveTL111";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0 4 0 20 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  0.13333334028720856;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  0.13333334028720856;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "Champion_Horse_L_F_Leg_locator_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 4 0 6 0 9 0 11 0 13 0 15 0 19 0 20 
		0;
	setAttr -s 9 ".kit[0:8]"  1 10 10 10 10 10 10 10 
		1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 10 10 10 10 10 
		1;
	setAttr -s 9 ".kix[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[0:8]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "Champion_Horse_L_F_Leg_locator_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 4 0 6 0 9 0 11 0 13 0 15 0 19 0 20 
		0;
	setAttr -s 9 ".kit[0:8]"  1 10 10 10 10 10 10 10 
		1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 10 10 10 10 10 
		1;
	setAttr -s 9 ".kix[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[0:8]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "Champion_Horse_L_F_Leg_locator_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 23.595452449290423 2 18.433469527677214 
		4 -12.613596756142163 6 -16.378432600680384 8 -8.1612491517733474 9 0 11 23.756981536437483 
		13 55.494997012766788 15 93.847978709093255 17 97.382067120301102 19 72.316042850441306 
		20 23.595452449290423;
	setAttr -s 12 ".kit[1:11]"  10 1 10 1 1 1 1 1 
		10 10 3;
	setAttr -s 12 ".kot[1:11]"  10 1 10 1 1 1 1 1 
		10 10 3;
	setAttr -s 12 ".kix[0:11]"  1 0.2064368724822998 0.51112210750579834 
		0.86397528648376465 0.39935487508773804 0.35733360052108765 0.11472843587398529 0.12036237865686417 
		0.17612972855567932 0.33437380194664001 0.077417612075805664 1;
	setAttr -s 12 ".kiy[0:11]"  0 -0.97845989465713501 -0.85950809717178345 
		0.50353419780731201 0.91679644584655762 0.93397682905197144 0.99339687824249268 0.99273008108139038 
		0.98436695337295532 -0.94244050979614258 -0.99699878692626953 0;
	setAttr -s 12 ".kox[0:11]"  1 0.2064368724822998 0.51112204790115356 
		0.86397528648376465 0.39935481548309326 0.35733360052108765 0.11472842842340469 0.12036236375570297 
		0.17612968385219574 0.33437380194664001 0.077417612075805664 1;
	setAttr -s 12 ".koy[0:11]"  0 -0.97845989465713501 -0.859508216381073 
		0.50353419780731201 0.91679650545120239 0.93397682905197144 0.99339693784713745 0.99273008108139038 
		0.9843670129776001 -0.94244050979614258 -0.99699878692626953 0;
createNode animCurveTL -n "animCurveTL112";
	setAttr ".tan" 1;
	setAttr -s 12 ".ktv[0:11]"  0 0.4735845525237779 2 0.70440067295442499 
		4 0.84008947911748177 6 0.81113713640547314 8 0.64844961065565521 9 0.32639439845331619 
		11 -0.23150800549771011 13 -0.53105475126489943 15 -0.41927100251403077 17 -0.09456949924447855 
		19 0.29495279077209813 20 0.4735845525237779;
	setAttr -s 12 ".kit[2:11]"  10 1 10 1 1 3 1 1 
		1 1;
	setAttr -s 12 ".kot[2:11]"  10 1 10 1 1 3 1 1 
		1 1;
	setAttr -s 12 ".kix[0:11]"  0.019075110554695129 0.059638123959302902 
		0.066666670143604279 0.062650874257087708 0.066666677594184875 0.031061865389347076 
		0.062165115028619766 0.066666662693023682 0.071039088070392609 0.075573951005935669 
		0.05952681228518486 0.019075110554695129;
	setAttr -s 12 ".kiy[0:11]"  0.1196100264787674 0.19609655439853668 
		0 -0.085303887724876404 -0.32316184043884277 -0.29805469512939453 -0.43963509798049927 
		0 0.20867292582988739 0.39366081357002258 0.38063865900039673 0.1196100264787674;
	setAttr -s 12 ".kox[0:11]"  0.019075110554695129 0.059638116508722305 
		0.066666662693023682 0.062650874257087708 0.033333331346511841 0.062123734503984451 
		0.062165115028619766 0.066666662693023682 0.071039058268070221 0.075573943555355072 
		0.029763432219624519 0.019075110554695129;
	setAttr -s 12 ".koy[0:11]"  0.11960998922586441 0.1960965096950531 
		0 -0.085303887724876404 -0.161580890417099 -0.59610939025878906 -0.43963509798049927 
		0 0.208672896027565 0.3936607837677002 0.19031952321529388 0.11960998922586441;
createNode animCurveTL -n "animCurveTL113";
	setAttr ".tan" 1;
	setAttr -s 11 ".ktv[0:10]"  0 0.20453647410167508 4 0.26219299658816042 
		6 0.17687510667108042 8 0.020855419849192591 9 0 11 0.070065185106559735 13 0.13799539388834775 
		15 0.25352413745676211 17 0.33169797932614958 19 0.33169797932614958 20 0.20453647410167508;
	setAttr -s 11 ".kit[1:10]"  3 1 1 10 1 10 1 10 
		10 3;
	setAttr -s 11 ".kot[1:10]"  3 1 1 10 1 10 1 10 
		10 3;
	setAttr -s 11 ".kix[0:10]"  0.033333361148834229 0.13333334028720856 
		0.040547549724578857 0.056566640734672546 0.033333331346511841 0.04243265837430954 
		0.066666662693023682 0.057682543992996216 0.066666662693023682 0.066666662693023682 
		0.033333361148834229;
	setAttr -s 11 ".kiy[0:10]"  0 0 -0.12769770622253418 -0.032797444611787796 
		0 0.049479424953460693 0.091729477047920227 0.10205221921205521 0 0 0;
	setAttr -s 11 ".kox[0:10]"  0.033333361148834229 0.066666662693023682 
		0.040547549724578857 0.056566622108221054 0.066666662693023682 0.04243265837430954 
		0.066666662693023682 0.057682525366544724 0.066666662693023682 0.033333361148834229 
		0.033333361148834229;
	setAttr -s 11 ".koy[0:10]"  0 0 -0.12769772112369537 -0.032797425985336304 
		0 0.049479436129331589 0.091729477047920227 0.10205218195915222 0 0 0;
createNode animCurveTL -n "animCurveTL114";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 8 0 9 0 11 0 13 0 15 0 19 0 20 
		0;
	setAttr -s 9 ".kit[0:8]"  1 10 10 10 10 10 10 10 
		1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 10 10 10 10 10 
		1;
	setAttr -s 9 ".kix[0:8]"  0.20000000298023224 0.20000000298023224 
		0.066666677594184875 0.033333331346511841 0.066666662693023682 0.066666662693023682 
		0.066666662693023682 0.13333332538604736 0.20000000298023224;
	setAttr -s 9 ".kiy[0:8]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  0.20000000298023224 0.066666677594184875 
		0.033333331346511841 0.066666662693023682 0.066666662693023682 0.066666662693023682 
		0.13333332538604736 0.033333361148834229 0.20000000298023224;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "Champion_Horse_R_F_Leg_locator1_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 4 0 6 0 8 0 11 0 13 0 15 0 17 0 19 
		0 20 0;
	setAttr -s 10 ".kit[0:9]"  1 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  1 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kix[0:9]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[0:9]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[0:9]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[0:9]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "Champion_Horse_R_F_Leg_locator1_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 4 0 6 0 8 0 11 0 13 0 15 0 17 0 19 
		0 20 0;
	setAttr -s 10 ".kit[0:9]"  1 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  1 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kix[0:9]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[0:9]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[0:9]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[0:9]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "Champion_Horse_R_F_Leg_locator1_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 116.85486634994713 2 110.72786935601792 
		4 94.599442084172239 6 42.976018521401691 8 -6.5867687165949143 9 -30.257246303068701 
		11 -18.321451025748082 13 -0.050854434929023445 15 -0.050854434929023445 17 58.269684964198291 
		19 100.79641172567375 20 116.85486634994713;
	setAttr -s 12 ".kit[0:11]"  3 1 10 1 10 10 1 10 
		10 10 10 3;
	setAttr -s 12 ".kot[0:11]"  3 1 10 1 10 10 1 10 
		10 10 10 3;
	setAttr -s 12 ".kix[1:11]"  0.34629756212234497 0.11204610764980316 
		0.060046199709177017 0.077999018132686615 0.43875405192375183 0.18286964297294617 
		1 1 0.075536124408245087 0.097334742546081543 1;
	setAttr -s 12 ".kiy[1:11]"  -0.93812471628189087 -0.99370300769805908 
		-0.99819564819335938 -0.99695348739624023 -0.89860713481903076 0.98313719034194946 
		0 0 0.99714308977127075 0.99525171518325806 0;
	setAttr -s 12 ".kox[1:11]"  0.34629756212234497 0.11204610764980316 
		0.060046199709177017 0.077999018132686615 0.43875405192375183 0.18286968767642975 
		1 1 0.075536124408245087 0.097334742546081543 1;
	setAttr -s 12 ".koy[1:11]"  -0.93812471628189087 -0.99370300769805908 
		-0.9981955885887146 -0.99695348739624023 -0.89860713481903076 0.98313713073730469 
		0 0 0.99714308977127075 0.99525171518325806 0;
createNode animCurveTL -n "animCurveTL115";
	setAttr ".tan" 10;
	setAttr -s 12 ".ktv[0:11]"  0 -0.071297986074489228 2 0.094281253904861612 
		4 0.310186529598934 6 0.58994184109277781 8 1.0375503394829291 9 0.96651941868224656 
		11 0.72284805431798227 13 0.45164996411689107 15 0.20277245812696593 17 -0.44769604153893527 
		19 -0.26966993422467034 20 -0.071297986074489228;
	setAttr -s 12 ".kit[0:11]"  1 10 10 10 3 10 10 10 
		10 3 1 1;
	setAttr -s 12 ".kot[0:11]"  1 10 10 10 3 10 10 10 
		10 3 1 1;
	setAttr -s 12 ".kix[0:11]"  0.14711007475852966 0.066666670143604279 
		0.066666670143604279 0.066666662693023682 0.066666677594184875 0.033333331346511841 
		0.066666662693023682 0.066666662693023682 0.066666662693023682 0.066666662693023682 
		0.050889600068330765 0.14711007475852966;
	setAttr -s 12 ".kiy[0:11]"  0.36373189091682434 0.19074225425720215 
		0.24783031642436981 0.3636818528175354 0 -0.10490076243877411 -0.25743472576141357 
		-0.26003780961036682 -0.44967299699783325 0 0.27460163831710815 0.36373189091682434;
	setAttr -s 12 ".kox[0:11]"  0.14711008965969086 0.066666670143604279 
		0.066666662693023682 0.066666677594184875 0.033333331346511841 0.066666662693023682 
		0.066666662693023682 0.066666662693023682 0.066666662693023682 0.066666662693023682 
		0.050889600068330765 0.14711008965969086;
	setAttr -s 12 ".koy[0:11]"  0.36373192071914673 0.19074225425720215 
		0.24783028662204742 0.36368194222450256 0 -0.20980152487754822 -0.25743472576141357 
		-0.26003780961036682 -0.44967299699783325 0 0.27460163831710815 0.36373192071914673;
createNode animCurveTL -n "animCurveTL116";
	setAttr ".tan" 1;
	setAttr -s 11 ".ktv[0:10]"  0 0.26214989116700238 4 0.26214989116700238 
		6 0.26214989116700238 8 0.35370617492862422 9 0.27515028511296247 11 0.10043785694577925 
		13 6.2548810817103506e-005 15 0.00091527890467538175 17 0.1604206869874224 19 0.29266865242087614 
		20 0.26214989116700238;
	setAttr -s 11 ".kit[0:10]"  3 10 10 3 1 1 10 1 
		1 10 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 3 1 1 10 1 
		1 10 3;
	setAttr -s 11 ".kix[4:10]"  0.061283629387617111 0.04178396612405777 
		0.066666662693023682 0.067072227597236633 0.054320059716701508 0.066666662693023682 
		0.033333361148834229;
	setAttr -s 11 ".kiy[4:10]"  -0.12206214666366577 -0.12608431279659271 
		0 0.012253031134605408 0.14946386218070984 0 0;
	setAttr -s 11 ".kox[4:10]"  0.061283621937036514 0.041783977299928665 
		0.066666662693023682 0.067072227597236633 0.054320059716701508 0.033333361148834229 
		0.033333361148834229;
	setAttr -s 11 ".koy[4:10]"  -0.12206218391656876 -0.12608428299427032 
		0 0.01225303765386343 0.14946387708187103 0 0;
createNode animCurveTL -n "animCurveTL117";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 4 0 6 0 8 0 9 0 15 0 17 0 19 0 20 0;
	setAttr -s 9 ".kit[0:8]"  1 10 10 10 10 10 10 10 
		1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 10 10 10 10 10 
		1;
	setAttr -s 9 ".kix[0:8]"  0.13333334028720856 0.13333334028720856 
		0.066666662693023682 0.066666677594184875 0.033333331346511841 0.19999998807907104 
		0.066666662693023682 0.066666662693023682 0.13333334028720856;
	setAttr -s 9 ".kiy[0:8]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  0.13333334028720856 0.066666662693023682 
		0.066666677594184875 0.033333331346511841 0.19999998807907104 0.066666662693023682 
		0.066666662693023682 0.033333361148834229 0.13333334028720856;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "Champion_Horse_L_B_Leg_locator1_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 4 0 6 0 8 0 9 0 11 0 13 0 17 0 19 0 
		20 0;
	setAttr -s 10 ".kit[9]"  1;
	setAttr -s 10 ".kot[9]"  1;
	setAttr -s 10 ".kix[9]"  1;
	setAttr -s 10 ".kiy[9]"  0;
	setAttr -s 10 ".kox[9]"  1;
	setAttr -s 10 ".koy[9]"  0;
createNode animCurveTA -n "Champion_Horse_L_B_Leg_locator1_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 4 0 6 0 8 0 9 0 11 0 13 0 17 0 19 0 
		20 0;
	setAttr -s 10 ".kit[9]"  1;
	setAttr -s 10 ".kot[9]"  1;
	setAttr -s 10 ".kix[9]"  1;
	setAttr -s 10 ".kiy[9]"  0;
	setAttr -s 10 ".kox[9]"  1;
	setAttr -s 10 ".koy[9]"  0;
createNode animCurveTA -n "Champion_Horse_L_B_Leg_locator1_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 12.329166871354929 4 0 6 0 8 41.012883700969972 
		9 85.93240436245793 11 97.510530024988867 13 88.269486696937363 17 46.199246527021785 
		19 24.190613692567577 20 12.329166871354929;
	setAttr -s 10 ".kit[1:9]"  10 10 1 1 1 10 1 1 
		1;
	setAttr -s 10 ".kot[1:9]"  10 10 1 1 1 10 1 1 
		1;
	setAttr -s 10 ".kix[0:9]"  0.47660627961158752 1 1 0.073441855609416962 
		0.14066711068153381 0.66423070430755615 0.21795709431171417 0.14548507332801819 0.23367142677307129 
		0.47457855939865112;
	setAttr -s 10 ".kiy[0:9]"  -0.87911689281463623 0 0 0.99729955196380615 
		0.99005699157714844 -0.74752771854400635 -0.97595840692520142 -0.98936045169830322 
		-0.97231566905975342 -0.88021314144134521;
	setAttr -s 10 ".kox[0:9]"  0.47660636901855469 1 1 0.073441870510578156 
		0.14066717028617859 0.66423076391220093 0.21795709431171417 0.14548508822917938 0.23367142677307129 
		0.47457864880561829;
	setAttr -s 10 ".koy[0:9]"  -0.87911689281463623 0 0 0.99729949235916138 
		0.99005699157714844 -0.7475275993347168 -0.97595840692520142 -0.98936045169830322 
		-0.97231566905975342 -0.88021314144134521;
createNode animCurveTL -n "animCurveTL118";
	setAttr ".tan" 1;
	setAttr -s 12 ".ktv[0:11]"  0 0.5850999501689107 2 0.85111184565214393 
		4 0.64235254789104346 6 0.061194548644075031 8 -0.31013934020868983 9 -0.45562101962440871 
		11 -0.54206854957975237 13 -0.48710802700602074 15 -0.22864450887853183 17 0.14102830730026464 
		19 0.42297294437652105 20 0.5850999501689107;
	setAttr -s 12 ".kit[1:11]"  3 1 1 1 1 1 1 10 
		10 1 1;
	setAttr -s 12 ".kot[1:11]"  3 1 1 1 1 1 1 10 
		10 1 1;
	setAttr -s 12 ".kix[0:11]"  0.05617905780673027 0.066666670143604279 
		0.055330261588096619 0.061965014785528183 0.074345797300338745 0.064502105116844177 
		0.066597111523151398 0.062507905066013336 0.066666662693023682 0.066666662693023682 
		0.068958118557929993 0.05617905780673027;
	setAttr -s 12 ".kiy[0:11]"  0.1375495046377182 0 -0.42138791084289551 
		-0.47642174363136292 -0.20524789392948151 -0.13078032433986664 -0.012233593501150608 
		0.093130119144916534 0.31406816840171814 0.32580873370170593 0.21022246778011322 
		0.1375495046377182;
	setAttr -s 12 ".kox[0:11]"  0.056179046630859375 0.066666670143604279 
		0.055330250412225723 0.061965025961399078 0.074345782399177551 0.064502105116844177 
		0.066597111523151398 0.062507927417755127 0.066666662693023682 0.066666662693023682 
		0.068958118557929993 0.056179046630859375;
	setAttr -s 12 ".koy[0:11]"  0.13754956424236298 0 -0.42138785123825073 
		-0.47642186284065247 -0.20524786412715912 -0.13078030943870544 -0.012233593501150608 
		0.093130141496658325 0.31406816840171814 0.32580873370170593 0.21022246778011322 
		0.13754956424236298;
createNode animCurveTL -n "animCurveTL119";
	setAttr ".tan" 10;
	setAttr -s 12 ".ktv[0:11]"  0 0.17437678173497589 2 0.11333925922722804 
		4 0 6 0 8 0.1118933225538155 9 0.24465750934778766 11 0.35748934925821901 13 0.40835395134800884 
		15 0.33205704821332388 17 0.19472262257089129 19 0.17409298920268024 20 0.17437678173497589;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 1 1 10 10 
		1 1 10 1;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 1 1 10 10 
		1 1 10 1;
	setAttr -s 12 ".kix[4:11]"  0.063531503081321716 0.059947174042463303 
		0.066666662693023682 0.066666662693023682 0.049938030540943146 0.057455152273178101 
		0.066666662693023682 0.066666670143604279;
	setAttr -s 12 ".kiy[4:11]"  0.11518780887126923 0.127664715051651 0.081848219037055969 
		-0.012716150842607021 -0.11918175965547562 -0.040473375469446182 0 0;
	setAttr -s 12 ".kox[4:11]"  0.063531495630741119 0.059947170317173004 
		0.066666662693023682 0.066666662693023682 0.049938004463911057 0.057455155998468399 
		0.033333361148834229 0.066666670143604279;
	setAttr -s 12 ".koy[4:11]"  0.11518781632184982 0.12766470015048981 
		0.081848219037055969 -0.012716150842607021 -0.11918170750141144 -0.040473379194736481 
		0 0;
createNode animCurveTL -n "animCurveTL120";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 8 0 9 0 13 0 19 0 20 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kix[0:6]"  0.20000000298023224 0.20000000298023224 
		0.066666677594184875 0.033333331346511841 0.13333332538604736 0.19999998807907104 
		0.20000000298023224;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.20000000298023224 0.066666677594184875 
		0.033333331346511841 0.13333332538604736 0.19999998807907104 0.033333361148834229 
		0.20000000298023224;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "Champion_Horse_R_B_Leg_locator2_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 0 4 0 6 0 8 0 9 0 11 0 15 0 17 0 
		19 0 20 0;
	setAttr -s 11 ".kit[10]"  1;
	setAttr -s 11 ".kot[10]"  1;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[10]"  1;
	setAttr -s 11 ".koy[10]"  0;
createNode animCurveTA -n "Champion_Horse_R_B_Leg_locator2_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 0 4 0 6 0 8 0 9 0 11 0 15 0 17 0 
		19 0 20 0;
	setAttr -s 11 ".kit[10]"  1;
	setAttr -s 11 ".kot[10]"  1;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[10]"  1;
	setAttr -s 11 ".koy[10]"  0;
createNode animCurveTA -n "Champion_Horse_R_B_Leg_locator2_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 6.8896044000940391 2 2.7792573681219372 
		4 -15.07901351717037 6 -34.843869653327182 8 -27.962905068275102 9 0 11 0 13 52.462107410912168 
		15 82.346335676132256 17 78.802982083968899 19 41.359221606614646 20 6.8896044000940391;
	setAttr -s 12 ".kit[0:11]"  3 10 1 3 10 10 10 1 
		1 1 1 1;
	setAttr -s 12 ".kot[0:11]"  3 10 1 3 10 10 10 1 
		1 1 1 1;
	setAttr -s 12 ".kix[2:11]"  0.17761106789112091 1 0.16225676238536835 
		1 1 0.098390363156795502 0.35390719771385193 0.21786102652549744 0.091988883912563324 
		1;
	setAttr -s 12 ".kiy[2:11]"  -0.98410075902938843 0 0.98674857616424561 
		0 0 0.99514788389205933 0.93528056144714355 -0.97597980499267578 -0.99576002359390259 
		0;
	setAttr -s 12 ".kox[2:11]"  0.17761106789112091 1 0.16225676238536835 
		1 1 0.098390363156795502 0.35390704870223999 0.21786113083362579 0.091988891363143921 
		1;
	setAttr -s 12 ".koy[2:11]"  -0.98410075902938843 0 0.98674857616424561 
		0 0 0.99514788389205933 0.93528062105178833 -0.97597980499267578 -0.99576002359390259 
		0;
createNode animCurveTL -n "animCurveTL121";
	setAttr ".tan" 1;
	setAttr -s 11 ".ktv[0:10]"  0 0.31151410319138395 2 0.58618295447624924 
		4 0.94223516910477834 6 0.9880133109855892 8 0.84559242513417776 9 0.4335891482068796 
		11 0.012594804851357055 13 -0.27876960406062778 15 -0.43110908731954894 17 -0.22289334255928867 
		20 0.31151410319138395;
	setAttr -s 11 ".kit[0:10]"  3 1 1 10 10 1 1 1 
		3 1 1;
	setAttr -s 11 ".kot[0:10]"  3 1 1 10 10 1 1 1 
		3 1 1;
	setAttr -s 11 ".kix[1:10]"  0.04652884230017662 0.059635452926158905 
		0.066666662693023682 0.066666677594184875 0.058498218655586243 0.071763649582862854 
		0.057974081486463547 0.066666662693023682 0.053455978631973267 0.066666670143604279;
	setAttr -s 11 ".kiy[1:10]"  0.37253785133361816 0.12378644943237305 
		0 -0.36961615085601807 -0.47910338640213013 -0.37148615717887878 -0.23374183475971222 
		0 0.29431477189064026 0;
	setAttr -s 11 ".kox[1:10]"  0.046528831124305725 0.059635456651449203 
		0.066666677594184875 0.033333331346511841 0.05849822610616684 0.071763664484024048 
		0.057974096387624741 0.066666662693023682 0.05345597118139267 0.066666670143604279;
	setAttr -s 11 ".koy[1:10]"  0.37253785133361816 0.12378646433353424 
		0 -0.18480803072452545 -0.47910341620445251 -0.37148618698120117 -0.23374196887016296 
		0 0.29431474208831787 0;
createNode animCurveTL -n "animCurveTL122";
	setAttr ".tan" 1;
	setAttr -s 11 ".ktv[0:10]"  0 0.14758872833721948 2 0.23405855188986235 
		4 0.2137127110539464 6 0.13741580791926145 8 0.040773063948660704 9 0 11 0 13 0.19845333042700952 
		15 0.35613359690535829 17 0.26966377335271552 20 0.14758872833721948;
	setAttr -s 11 ".kit[0:10]"  3 1 1 1 1 10 10 1 
		3 1 1;
	setAttr -s 11 ".kot[0:10]"  3 1 1 1 1 10 10 1 
		3 1 1;
	setAttr -s 11 ".kix[1:10]"  0.064976982772350311 0.048318058252334595 
		0.062830381095409393 0.044912617653608322 0.033333331346511841 0.066666662693023682 
		0.038891628384590149 0.066666662693023682 0.060824509710073471 0.066666670143604279;
	setAttr -s 11 ".kiy[1:10]"  0.015698991715908051 -0.04834907129406929 
		-0.089596092700958252 -0.051859490573406219 0 0 0.18721497058868408 0 -0.075015850365161896 
		0;
	setAttr -s 11 ".kox[1:10]"  0.064976982772350311 0.048318061977624893 
		0.06283038854598999 0.044912587851285934 0.066666662693023682 0.066666662693023682 
		0.038891643285751343 0.066666662693023682 0.12164902687072754 0.066666670143604279;
	setAttr -s 11 ".koy[1:10]"  0.015698991715908051 -0.048349086195230484 
		-0.089596107602119446 -0.051859490573406219 0 0 0.18721505999565125 0 -0.15003170073032379 
		0;
createNode animCurveTL -n "animCurveTL123";
	setAttr ".tan" 10;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 4 0 9 0 11 0 13 0 15 0 19 0 20 
		0;
	setAttr -s 9 ".kit[8]"  1;
	setAttr -s 9 ".kot[8]"  1;
	setAttr -s 9 ".kix[8]"  0.066666670143604279;
	setAttr -s 9 ".kiy[8]"  0;
	setAttr -s 9 ".kox[8]"  0.066666670143604279;
	setAttr -s 9 ".koy[8]"  0;
createNode animCurveTL -n "Champion_Horse_Head_Top_locator1_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.20434956740712229 2 -0.20112001899007392 
		8 -0.27172462563613525 11 -0.19533249788675899 17 -0.10970923593245219 20 -0.20434956740712229;
	setAttr -s 6 ".kit[3:5]"  1 10 3;
	setAttr -s 6 ".kot[3:5]"  1 10 3;
	setAttr -s 6 ".kix[3:5]"  0.84488111734390259 0.99954861402511597 
		1;
	setAttr -s 6 ".kiy[3:5]"  0.53495413064956665 -0.030043331906199455 
		0;
	setAttr -s 6 ".kox[3:5]"  0.84488111734390259 0.99954861402511597 
		1;
	setAttr -s 6 ".koy[3:5]"  0.5349542498588562 -0.030043331906199455 
		0;
createNode animCurveTL -n "animCurveTL125";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0.50718440048055835 2 0.62417298528707543 
		8 0.50067298632518076 11 0.51238370242103826 20 0.50718440048055835;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTL -n "animCurveTL126";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0 11 0 20 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  0.73333334922790527;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  0.73333334922790527;
	setAttr -s 3 ".koy[2]"  0;
createNode lightLinker -n "lightLinker1";
	setAttr -s 6 ".lnk";
	setAttr -s 5 ".slnk";
select -ne :time1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -l on ".o" 0;
select -ne :renderPartition;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 6 ".st";
select -ne :renderGlobalsList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
select -ne :defaultShaderList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 6 ".s";
select -ne :postProcessList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
	setAttr -s 3 ".u";
select -ne :lightList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
select -ne :defaultTextureList1;
	setAttr -s 3 ".tx";
select -ne :lambert1;
	setAttr ".miic" -type "float3" 31.006279 31.006279 31.006279 ;
select -ne :initialShadingGroup;
	setAttr -k on ".cch";
	setAttr -av -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -k on ".mwc";
	setAttr ".ro" yes;
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
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -k on ".mwc";
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
	setAttr ".mcfr" 30;
	setAttr -k on ".clip";
	setAttr -k on ".edm";
	setAttr -k on ".edl";
	setAttr -av -k on ".esr";
	setAttr -k on ".ors";
	setAttr -k on ".outf";
	setAttr -k on ".gama";
	setAttr ".fs" 1;
	setAttr ".ef" 10;
	setAttr -l on ".bfs";
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
	setAttr -l on ".mb";
	setAttr -k on ".mbf";
	setAttr -l on ".afp";
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
select -ne :defaultResolution;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -av ".w" 320;
	setAttr -av ".h" 240;
	setAttr -k on ".al";
	setAttr -av ".dar";
	setAttr -k on ".ldar";
	setAttr -k on ".off";
	setAttr -k on ".fld";
	setAttr -k on ".zsl";
select -ne :defaultLightSet;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -k on ".mwc";
	setAttr ".ro" yes;
select -ne :hardwareRenderGlobals;
	addAttr -ci true -sn "ani" -ln "animation" -bt "ANIM" -min 0 -max 1 -at "bool";
	setAttr -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
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
	setAttr ".enpt" no;
	setAttr -k off ".clmt";
	setAttr -k off -cb on ".lith";
	setAttr -k off -cb on ".sobc";
	setAttr -k off -cb on ".cuth";
	setAttr ".hgcd" no;
	setAttr ".hgci" no;
	setAttr -k off -cb on ".mgcs";
	setAttr -k off ".twa";
	setAttr -k off ".twz";
	setAttr -k on ".hwcc";
	setAttr -k on ".hwdp";
	setAttr -k on ".hwql";
	setAttr ".hwfr" 30;
	setAttr -k on ".ani" yes;
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
	setAttr -av ".ef";
	setAttr -k on ".fii";
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
connectAttr "runSource.cl" "clipLibrary1.sc[0]";
connectAttr "tail2_rotateZ.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "tail2_rotateY.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "tail2_rotateX.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "tail_rotateZ.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "tail_rotateY.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "tail_rotateX.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "tail3_rotateZ.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "tail3_rotateY.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "tail3_rotateX.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "Head_rotateZ.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "Head_rotateY.a" "clipLibrary1.cel[0].cev[10].cevr";
connectAttr "Head_rotateX.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "tail1_rotateZ.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "tail1_rotateY.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "tail1_rotateX.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "tail_rotateZ1.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "tail_rotateY1.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "tail_rotateX1.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "tail2_rotateZ1.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "tail2_rotateY1.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "tail2_rotateX1.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "animCurveTA72.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "animCurveTA73.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "animCurveTA74.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "animCurveTL64.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "animCurveTL65.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "animCurveTL66.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "animCurveTL67.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "animCurveTL68.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "animCurveTL69.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "animCurveTA75.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "animCurveTA76.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "animCurveTA77.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "animCurveTL70.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "animCurveTL71.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "animCurveTL72.a" "clipLibrary1.cel[0].cev[63].cevr";
connectAttr "Champion_R_Hand_locator_rotateZ.a" "clipLibrary1.cel[0].cev[65].cevr"
		;
connectAttr "Champion_R_Hand_locator_rotateY.a" "clipLibrary1.cel[0].cev[66].cevr"
		;
connectAttr "Champion_R_Hand_locator_rotateX.a" "clipLibrary1.cel[0].cev[67].cevr"
		;
connectAttr "Champion_R_Hand_locator_translateZ.a" "clipLibrary1.cel[0].cev[68].cevr"
		;
connectAttr "Champion_R_Hand_locator_translateY.a" "clipLibrary1.cel[0].cev[69].cevr"
		;
connectAttr "Champion_R_Hand_locator_translateX.a" "clipLibrary1.cel[0].cev[70].cevr"
		;
connectAttr "animCurveTL76.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "animCurveTL77.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "animCurveTL78.a" "clipLibrary1.cel[0].cev[73].cevr";
connectAttr "animCurveTL79.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "animCurveTL80.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "animCurveTL81.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "Champion_R_Leg_locator_rotateZ.a" "clipLibrary1.cel[0].cev[78].cevr"
		;
connectAttr "Champion_R_Leg_locator_rotateY.a" "clipLibrary1.cel[0].cev[79].cevr"
		;
connectAttr "Champion_R_Leg_locator_rotateX.a" "clipLibrary1.cel[0].cev[80].cevr"
		;
connectAttr "Champion_R_Leg_locator_translateZ.a" "clipLibrary1.cel[0].cev[81].cevr"
		;
connectAttr "Champion_R_Leg_locator_translateY.a" "clipLibrary1.cel[0].cev[82].cevr"
		;
connectAttr "Champion_R_Leg_locator_translateX.a" "clipLibrary1.cel[0].cev[83].cevr"
		;
connectAttr "Champion_L_Leg_locator_rotateZ.a" "clipLibrary1.cel[0].cev[85].cevr"
		;
connectAttr "Champion_L_Leg_locator_rotateY.a" "clipLibrary1.cel[0].cev[86].cevr"
		;
connectAttr "Champion_L_Leg_locator_rotateX.a" "clipLibrary1.cel[0].cev[87].cevr"
		;
connectAttr "Champion_L_Leg_locator_translateZ.a" "clipLibrary1.cel[0].cev[88].cevr"
		;
connectAttr "Champion_L_Leg_locator_translateY.a" "clipLibrary1.cel[0].cev[89].cevr"
		;
connectAttr "Champion_L_Leg_locator_translateX.a" "clipLibrary1.cel[0].cev[90].cevr"
		;
connectAttr "Champion_Hip_locator_rotateZ.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "Champion_Hip_locator_rotateY.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "Champion_Hip_locator_rotateX.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "Champion_Hip_locator_translateZ.a" "clipLibrary1.cel[0].cev[94].cevr"
		;
connectAttr "Champion_Hip_locator_translateY.a" "clipLibrary1.cel[0].cev[95].cevr"
		;
connectAttr "Champion_Hip_locator_translateX.a" "clipLibrary1.cel[0].cev[96].cevr"
		;
connectAttr "animCurveTA90.a" "clipLibrary1.cel[0].cev[123].cevr";
connectAttr "animCurveTA91.a" "clipLibrary1.cel[0].cev[124].cevr";
connectAttr "animCurveTA92.a" "clipLibrary1.cel[0].cev[125].cevr";
connectAttr "animCurveTA93.a" "clipLibrary1.cel[0].cev[126].cevr";
connectAttr "animCurveTA94.a" "clipLibrary1.cel[0].cev[127].cevr";
connectAttr "animCurveTA95.a" "clipLibrary1.cel[0].cev[128].cevr";
connectAttr "animCurveTA96.a" "clipLibrary1.cel[0].cev[129].cevr";
connectAttr "animCurveTA97.a" "clipLibrary1.cel[0].cev[130].cevr";
connectAttr "animCurveTA98.a" "clipLibrary1.cel[0].cev[131].cevr";
connectAttr "animCurveTL91.a" "clipLibrary1.cel[0].cev[132].cevr";
connectAttr "animCurveTL92.a" "clipLibrary1.cel[0].cev[133].cevr";
connectAttr "animCurveTL93.a" "clipLibrary1.cel[0].cev[134].cevr";
connectAttr "animCurveTA99.a" "clipLibrary1.cel[0].cev[136].cevr";
connectAttr "animCurveTA100.a" "clipLibrary1.cel[0].cev[137].cevr";
connectAttr "animCurveTA101.a" "clipLibrary1.cel[0].cev[138].cevr";
connectAttr "animCurveTA102.a" "clipLibrary1.cel[0].cev[140].cevr";
connectAttr "animCurveTA103.a" "clipLibrary1.cel[0].cev[141].cevr";
connectAttr "animCurveTA104.a" "clipLibrary1.cel[0].cev[142].cevr";
connectAttr "animCurveTA105.a" "clipLibrary1.cel[0].cev[143].cevr";
connectAttr "animCurveTL94.a" "clipLibrary1.cel[0].cev[144].cevr";
connectAttr "animCurveTL95.a" "clipLibrary1.cel[0].cev[145].cevr";
connectAttr "animCurveTL96.a" "clipLibrary1.cel[0].cev[146].cevr";
connectAttr "animCurveTA106.a" "clipLibrary1.cel[0].cev[148].cevr";
connectAttr "animCurveTA107.a" "clipLibrary1.cel[0].cev[149].cevr";
connectAttr "animCurveTA108.a" "clipLibrary1.cel[0].cev[150].cevr";
connectAttr "animCurveTA109.a" "clipLibrary1.cel[0].cev[152].cevr";
connectAttr "animCurveTA110.a" "clipLibrary1.cel[0].cev[159].cevr";
connectAttr "animCurveTA111.a" "clipLibrary1.cel[0].cev[160].cevr";
connectAttr "animCurveTA112.a" "clipLibrary1.cel[0].cev[161].cevr";
connectAttr "animCurveTA113.a" "clipLibrary1.cel[0].cev[174].cevr";
connectAttr "animCurveTA114.a" "clipLibrary1.cel[0].cev[175].cevr";
connectAttr "animCurveTA115.a" "clipLibrary1.cel[0].cev[176].cevr";
connectAttr "animCurveTA116.a" "clipLibrary1.cel[0].cev[177].cevr";
connectAttr "animCurveTA117.a" "clipLibrary1.cel[0].cev[178].cevr";
connectAttr "animCurveTA118.a" "clipLibrary1.cel[0].cev[179].cevr";
connectAttr "animCurveTA119.a" "clipLibrary1.cel[0].cev[205].cevr";
connectAttr "animCurveTA120.a" "clipLibrary1.cel[0].cev[206].cevr";
connectAttr "animCurveTA121.a" "clipLibrary1.cel[0].cev[207].cevr";
connectAttr "Champion_Horse_Hip_locator_rotateZ.a" "clipLibrary1.cel[0].cev[214].cevr"
		;
connectAttr "Champion_Horse_Hip_locator_rotateY.a" "clipLibrary1.cel[0].cev[215].cevr"
		;
connectAttr "Champion_Horse_Hip_locator_rotateX.a" "clipLibrary1.cel[0].cev[216].cevr"
		;
connectAttr "Champion_Horse_Hip_locator_translateZ.a" "clipLibrary1.cel[0].cev[217].cevr"
		;
connectAttr "animCurveTL98.a" "clipLibrary1.cel[0].cev[218].cevr";
connectAttr "animCurveTL99.a" "clipLibrary1.cel[0].cev[219].cevr";
connectAttr "Champion_Horse_L_B_Elbow_locator_translateZ.a" "clipLibrary1.cel[0].cev[223].cevr"
		;
connectAttr "animCurveTL101.a" "clipLibrary1.cel[0].cev[224].cevr";
connectAttr "animCurveTL102.a" "clipLibrary1.cel[0].cev[225].cevr";
connectAttr "Champion_Horse_R_B_Elbow_locator1_translateZ.a" "clipLibrary1.cel[0].cev[226].cevr"
		;
connectAttr "Champion_Horse_R_B_Elbow_locator1_translateY.a" "clipLibrary1.cel[0].cev[227].cevr"
		;
connectAttr "Champion_Horse_R_B_Elbow_locator1_translateX.a" "clipLibrary1.cel[0].cev[228].cevr"
		;
connectAttr "Champion_Horse_L_F_Elbow_locator_translateZ.a" "clipLibrary1.cel[0].cev[229].cevr"
		;
connectAttr "animCurveTL107.a" "clipLibrary1.cel[0].cev[230].cevr";
connectAttr "animCurveTL108.a" "clipLibrary1.cel[0].cev[231].cevr";
connectAttr "Champion_Horse_R_F_Elbow_locator1_translateZ.a" "clipLibrary1.cel[0].cev[232].cevr"
		;
connectAttr "animCurveTL110.a" "clipLibrary1.cel[0].cev[233].cevr";
connectAttr "animCurveTL111.a" "clipLibrary1.cel[0].cev[234].cevr";
connectAttr "Champion_Horse_L_F_Leg_locator_rotateZ.a" "clipLibrary1.cel[0].cev[235].cevr"
		;
connectAttr "Champion_Horse_L_F_Leg_locator_rotateY.a" "clipLibrary1.cel[0].cev[236].cevr"
		;
connectAttr "Champion_Horse_L_F_Leg_locator_rotateX.a" "clipLibrary1.cel[0].cev[237].cevr"
		;
connectAttr "animCurveTL112.a" "clipLibrary1.cel[0].cev[238].cevr";
connectAttr "animCurveTL113.a" "clipLibrary1.cel[0].cev[239].cevr";
connectAttr "animCurveTL114.a" "clipLibrary1.cel[0].cev[240].cevr";
connectAttr "Champion_Horse_R_F_Leg_locator1_rotateZ.a" "clipLibrary1.cel[0].cev[241].cevr"
		;
connectAttr "Champion_Horse_R_F_Leg_locator1_rotateY.a" "clipLibrary1.cel[0].cev[242].cevr"
		;
connectAttr "Champion_Horse_R_F_Leg_locator1_rotateX.a" "clipLibrary1.cel[0].cev[243].cevr"
		;
connectAttr "animCurveTL115.a" "clipLibrary1.cel[0].cev[244].cevr";
connectAttr "animCurveTL116.a" "clipLibrary1.cel[0].cev[245].cevr";
connectAttr "animCurveTL117.a" "clipLibrary1.cel[0].cev[246].cevr";
connectAttr "Champion_Horse_L_B_Leg_locator1_rotateZ.a" "clipLibrary1.cel[0].cev[247].cevr"
		;
connectAttr "Champion_Horse_L_B_Leg_locator1_rotateY.a" "clipLibrary1.cel[0].cev[248].cevr"
		;
connectAttr "Champion_Horse_L_B_Leg_locator1_rotateX.a" "clipLibrary1.cel[0].cev[249].cevr"
		;
connectAttr "animCurveTL118.a" "clipLibrary1.cel[0].cev[250].cevr";
connectAttr "animCurveTL119.a" "clipLibrary1.cel[0].cev[251].cevr";
connectAttr "animCurveTL120.a" "clipLibrary1.cel[0].cev[252].cevr";
connectAttr "Champion_Horse_R_B_Leg_locator2_rotateZ.a" "clipLibrary1.cel[0].cev[253].cevr"
		;
connectAttr "Champion_Horse_R_B_Leg_locator2_rotateY.a" "clipLibrary1.cel[0].cev[254].cevr"
		;
connectAttr "Champion_Horse_R_B_Leg_locator2_rotateX.a" "clipLibrary1.cel[0].cev[255].cevr"
		;
connectAttr "animCurveTL121.a" "clipLibrary1.cel[0].cev[256].cevr";
connectAttr "animCurveTL122.a" "clipLibrary1.cel[0].cev[257].cevr";
connectAttr "animCurveTL123.a" "clipLibrary1.cel[0].cev[258].cevr";
connectAttr "Champion_Horse_Head_Top_locator1_translateZ.a" "clipLibrary1.cel[0].cev[259].cevr"
		;
connectAttr "animCurveTL125.a" "clipLibrary1.cel[0].cev[260].cevr";
connectAttr "animCurveTL126.a" "clipLibrary1.cel[0].cev[261].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[6].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[6].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of run.ma
