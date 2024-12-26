//Maya ASCII 2008 scene
//Name: idle.ma
//Last modified: Mon, Jun 01, 2009 11:56:22 AM
//Codeset: 1251
requires maya "2008";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Complete 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200802250025-718075";
fileInfo "osv" "Microsoft Windows XP Service Pack 3 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 139 ".cel[0].cev";
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
createNode animClip -n "idleSource";
	setAttr ".ihi" 0;
	setAttr -s 139 ".ac";
	setAttr ".ac[0:20]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes;
	setAttr ".ac[36:44]" yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[57:96]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes;
	setAttr ".ac[123:152]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[205:207]" yes yes yes;
	setAttr ".ac[214:219]" yes yes yes yes yes yes;
	setAttr ".ac[229:231]" yes yes yes;
	setAttr ".ac[235:261]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".se" 70;
	setAttr ".ci" no;
createNode animCurveTA -n "tail2_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 70 0;
createNode animCurveTA -n "tail2_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 70 0;
createNode animCurveTA -n "tail2_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -20.730087684015032 25 -8.1157716546962657 
		40 -17.579746434357872 70 -20.730087684015032;
	setAttr -s 4 ".kit[0:3]"  3 1 1 3;
	setAttr -s 4 ".kot[0:3]"  3 1 1 3;
	setAttr -s 4 ".kix[1:3]"  0.99835515022277832 0.98320436477661133 
		1;
	setAttr -s 4 ".kiy[1:3]"  0.057332836091518402 -0.182508185505867 
		0;
	setAttr -s 4 ".kox[1:3]"  0.99835515022277832 0.98320436477661133 
		1;
	setAttr -s 4 ".koy[1:3]"  0.057332839816808701 -0.18250821530818939 
		0;
createNode animCurveTA -n "tail_rotateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1.6435770815818485 20 6.1815629643834837 
		40 3.9681320042669839 70 1.6435770815818485;
	setAttr -s 4 ".kit[3]"  10;
	setAttr -s 4 ".kot[3]"  10;
	setAttr -s 4 ".kix[0:3]"  1 0.99900507926940918 0.99544548988342285 
		1;
	setAttr -s 4 ".kiy[0:3]"  0 0.044597174972295761 -0.095332689583301544 
		0;
	setAttr -s 4 ".kox[0:3]"  1 0.99900507926940918 0.99544554948806763 
		1;
	setAttr -s 4 ".koy[0:3]"  0 0.044597174972295761 -0.095332704484462738 
		0;
createNode animCurveTA -n "tail_rotateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -8.4321922555201976 20 -11.665005152379411 
		40 -9.7551471565652683 70 -8.4321922555201976;
	setAttr -s 4 ".kit[3]"  10;
	setAttr -s 4 ".kot[3]"  10;
	setAttr -s 4 ".kix[0:3]"  1 0.99985778331756592 0.99703782796859741 
		1;
	setAttr -s 4 ".kiy[0:3]"  0 -0.016864674165844917 0.076912984251976013 
		0;
	setAttr -s 4 ".kox[0:3]"  1 0.99985778331756592 0.99703782796859741 
		1;
	setAttr -s 4 ".koy[0:3]"  0 -0.016864676028490067 0.076913006603717804 
		0;
createNode animCurveTA -n "tail_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -81.213167891630462 20 -78.041703045101528 
		40 -79.335246348865425 50 -79.23144167734479 70 -81.213167891630462;
	setAttr -s 5 ".kit[2:4]"  10 10 3;
	setAttr -s 5 ".kot[2:4]"  10 10 3;
	setAttr -s 5 ".kix[0:4]"  1 0.9998927116394043 1 1 1;
	setAttr -s 5 ".kiy[0:4]"  0 0.0146504957228899 0 0 0;
	setAttr -s 5 ".kox[0:4]"  1 0.9998927116394043 1 1 1;
	setAttr -s 5 ".koy[0:4]"  0 0.0146504957228899 0 0 0;
createNode animCurveTA -n "tail3_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 70 0;
createNode animCurveTA -n "tail3_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 70 0;
createNode animCurveTA -n "tail3_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -17.929079477298764 25 6.56902074503172 
		45 -23.976396089443181 60 -4.8936928347550745 70 -17.929079477298764;
createNode animCurveTA -n "Head_rotateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 70 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
	setAttr -s 2 ".kix[0:1]"  1 1;
	setAttr -s 2 ".kiy[0:1]"  0 0;
	setAttr -s 2 ".kox[0:1]"  1 1;
	setAttr -s 2 ".koy[0:1]"  0 0;
createNode animCurveTA -n "Head_rotateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 70 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
	setAttr -s 2 ".kix[0:1]"  1 1;
	setAttr -s 2 ".kiy[0:1]"  0 0;
	setAttr -s 2 ".kox[0:1]"  1 1;
	setAttr -s 2 ".koy[0:1]"  0 0;
createNode animCurveTA -n "Head_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -5.3421498242058192 10 -6.7758992511069343 
		30 -14.360175957275876 50 -12.84439477571083 70 -5.3421498242058192;
	setAttr -s 5 ".kit[0:4]"  3 1 1 1 3;
	setAttr -s 5 ".kot[0:4]"  3 1 1 1 3;
	setAttr -s 5 ".kix[1:4]"  0.98592036962509155 0.9982878565788269 
		0.9829297661781311 1;
	setAttr -s 5 ".kiy[1:4]"  -0.16721558570861816 -0.058492559939622879 
		0.18398141860961914 0;
	setAttr -s 5 ".kox[1:4]"  0.98592036962509155 0.9982878565788269 
		0.9829297661781311 1;
	setAttr -s 5 ".koy[1:4]"  -0.16721564531326294 -0.058492567390203476 
		0.18398143351078033 0;
createNode animCurveTA -n "tail1_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -15.964090848082433 15 -15.964090848082446 
		70 -15.964090848082433;
createNode animCurveTA -n "tail1_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -9.1585474876913739 15 -9.1585474876913953 
		70 -9.1585474876913739;
createNode animCurveTA -n "tail1_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -37.94198216029416 15 -27.868138415107641 
		30 -16.070083012135807 45 -26.499492263273634 70 -37.94198216029416;
	setAttr -s 5 ".kit[1:4]"  1 3 1 3;
	setAttr -s 5 ".kot[1:4]"  1 3 1 3;
	setAttr -s 5 ".kix[1:4]"  0.78913861513137817 1 0.90801745653152466 
		1;
	setAttr -s 5 ".kiy[1:4]"  0.61421525478363037 0 -0.41893231868743896 
		0;
	setAttr -s 5 ".kox[1:4]"  0.78913861513137817 1 0.90801757574081421 
		1;
	setAttr -s 5 ".koy[1:4]"  0.61421513557434082 0 -0.41893219947814941 
		0;
createNode animCurveTA -n "tail_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -1.7207319971292734 70 -1.7207319971292734;
createNode animCurveTA -n "tail_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -3.6860332002236964 70 -3.6860332002236964;
createNode animCurveTA -n "tail_rotateX1";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -48.059902027520991 15 -48.473469906142945 
		30 -51.659801266357121 50 -53.963250822765723 70 -48.059902027520991;
	setAttr -s 5 ".kit[1:4]"  1 1 3 3;
	setAttr -s 5 ".kot[1:4]"  1 1 3 3;
	setAttr -s 5 ".kix[1:4]"  0.99879354238510132 0.99191319942474365 
		1 1;
	setAttr -s 5 ".kiy[1:4]"  -0.049106739461421967 -0.12691843509674072 
		0 0;
	setAttr -s 5 ".kox[1:4]"  0.99879354238510132 0.99191319942474365 
		1 1;
	setAttr -s 5 ".koy[1:4]"  -0.049106758087873459 -0.12691843509674072 
		0 0;
createNode animCurveTA -n "tail2_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.69541506121312102 70 -0.69541506121312102;
createNode animCurveTA -n "tail2_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.53675210472901158 70 -0.53675210472901158;
createNode animCurveTA -n "tail2_rotateX1";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -24.737077588176479 15 -41.777625374821255 
		30 -12.403700447795998 45 -7.0947247535288991 55 -32.095714049572585 70 -24.737077588176479;
	setAttr -s 6 ".kit[0:5]"  3 3 1 1 1 3;
	setAttr -s 6 ".kot[0:5]"  3 3 1 1 1 3;
	setAttr -s 6 ".kix[2:5]"  0.72831833362579346 0.95520329475402832 
		0.98995482921600342 1;
	setAttr -s 6 ".kiy[2:5]"  0.68523901700973511 -0.29595041275024414 
		-0.14138403534889221 0;
	setAttr -s 6 ".kox[2:5]"  0.72831827402114868 0.95520329475402832 
		0.98995482921600342 1;
	setAttr -s 6 ".koy[2:5]"  0.68523907661437988 -0.29595041275024414 
		-0.14138405025005341 0;
createNode animCurveTA -n "animCurveTA193";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0 35 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1.3333333730697632;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "animCurveTA194";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0 35 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1.3333333730697632;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "animCurveTA195";
	setAttr ".tan" 1;
	setAttr -s 5 ".ktv[0:4]"  0 5.4108354304721047 15 6.375240933095939 
		35 9.9340634981481521 50 10.074067407298825 70 5.4108354304721047;
	setAttr -s 5 ".kit[0:4]"  3 1 1 1 3;
	setAttr -s 5 ".kot[0:4]"  3 1 1 1 3;
	setAttr -s 5 ".kix[1:4]"  0.31331488490104675 0.50863140821456909 
		0.46542537212371826 0.66666662693023682;
	setAttr -s 5 ".kiy[1:4]"  0.028915524482727051 0.032585296779870987 
		-0.013813557103276253 0;
	setAttr -s 5 ".kox[1:4]"  0.47994250059127808 0.34198272228240967 
		0.63208794593811035 0.66666662693023682;
	setAttr -s 5 ".koy[1:4]"  0.044293414801359177 0.021909011527895927 
		-0.018760001286864281 0;
createNode animCurveTL -n "animCurveTL190";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0.14270078018222057;
createNode animCurveTL -n "animCurveTL191";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 -1.1683380213237218;
createNode animCurveTL -n "animCurveTL192";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 -0.13199843516776633;
createNode animCurveTL -n "animCurveTL193";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0.22286510145816385;
createNode animCurveTL -n "animCurveTL194";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 -1.2247604743509974;
createNode animCurveTL -n "animCurveTL195";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0.037767030045364025;
createNode animCurveTU -n "animCurveTU17";
	setAttr ".tan" 5;
	setAttr -s 3 ".ktv[0:2]"  0 1 35 1 70 1;
	setAttr -s 3 ".kit[0:2]"  9 9 1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
createNode animCurveTA -n "animCurveTA196";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  0 -74.079249014308573 35 -64.398736965714733 
		70 -74.079249014308573;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "animCurveTA197";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 10.253140597234749 35 5.1380461952872176 
		70 10.253140597234749;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1.1666666269302368;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "animCurveTA198";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  0 -89.692972554796782 35 -85.881792424918729 
		70 -89.692972554796782;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "animCurveTL196";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.24591456611576609 35 0.24245346384728494 
		70 0.24591456611576609;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1.1666666269302368;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "animCurveTL197";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  0 -1.2272958631338584 35 -1.14626295844182 
		70 -1.2272958631338584;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1.1666666269302368;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "animCurveTL198";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 -0.26960515313545896 35 -0.24852091093101081 
		70 -0.26960515313545896;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1.1666666269302368;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "animCurveTU18";
	setAttr ".tan" 5;
	setAttr -s 3 ".ktv[0:2]"  0 1 35 1 70 1;
	setAttr -s 3 ".kit[0:2]"  9 9 1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0.1111111119389534;
createNode animCurveTA -n "animCurveTA199";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  0 79.500707521698359 35 79.500707521698374 
		70 79.500707521698359;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "animCurveTA200";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  0 -7.1073160051615583 35 -6.2207150372372215 
		70 -7.1073160051615583;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "animCurveTA201";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  0 -97.709239998422049 35 -97.709239998421992 
		70 -97.709239998422049;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "animCurveTL199";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  0 0.29262167183134014 35 0.27375304545907941 
		70 0.29262167183134014;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "animCurveTL200";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 -0.90649243360090281 35 -0.90701380132282994 
		70 -0.90649243360090281;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1.3333333730697632;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "animCurveTL201";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  0 0.13396473534770226 35 0.13396473534770226 
		70 0.13396473534770226;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "animCurveTL202";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 -0.085735089861745051;
createNode animCurveTL -n "animCurveTL203";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 -0.77678862872328902;
createNode animCurveTL -n "animCurveTL204";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 -0.32758782380619483;
createNode animCurveTL -n "animCurveTL205";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 -0.022529174976866462;
createNode animCurveTL -n "animCurveTL206";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 -0.73857428521639856;
createNode animCurveTL -n "animCurveTL207";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0.33779863130171084;
createNode animCurveTU -n "animCurveTU19";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA202";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 -13.572416046402321;
createNode animCurveTA -n "animCurveTA203";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 -14.142482270778613;
createNode animCurveTA -n "animCurveTA204";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 -15.434928480805077;
createNode animCurveTL -n "animCurveTL208";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0.18689813571882119;
createNode animCurveTL -n "animCurveTL209";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 -0.83654195934921649;
createNode animCurveTL -n "animCurveTL210";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 -0.36143794093182707;
createNode animCurveTU -n "animCurveTU20";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA205";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 16.928116120175844;
createNode animCurveTA -n "animCurveTA206";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 13.158990081775318;
createNode animCurveTA -n "animCurveTA207";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 -20.514940347492182;
createNode animCurveTL -n "animCurveTL211";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0.20664360032799686;
createNode animCurveTL -n "animCurveTL212";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 -0.84161235104344834;
createNode animCurveTL -n "animCurveTL213";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0.33351765877991613;
createNode animCurveTA -n "animCurveTA208";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA209";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA210";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 -6.4873880266507813;
createNode animCurveTL -n "animCurveTL214";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL215";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 -0.97082920327636302;
createNode animCurveTL -n "animCurveTL216";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA211";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 9.8356685883660511;
createNode animCurveTA -n "animCurveTA212";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 -9.3261534711754361;
createNode animCurveTA -n "animCurveTA213";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 2.3853567319547375;
createNode animCurveTA -n "animCurveTA214";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0.3914595141136728;
createNode animCurveTA -n "animCurveTA215";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 13.854835905531724;
createNode animCurveTA -n "animCurveTA216";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 10.557756442282532;
createNode animCurveTA -n "animCurveTA217";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 -0.014935073133263735 40 -0.13041896243835641 
		70 -0.014935073133263735;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1.3333333730697632;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "animCurveTA218";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 187.5796802179496 40 184.76620078794869 
		70 187.5796802179496;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1.3333333730697632;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "animCurveTA219";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 -92.34331294293078 40 -92.33089123214431 
		70 -92.34331294293078;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1.3333333730697632;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "animCurveTL217";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 -0.019566644519235961 40 -0.019566644519235961 
		70 -0.019566644519235961;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1.3333333730697632;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "animCurveTL218";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.085900421379315375 40 0.085900421379315375 
		70 0.085900421379315375;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1.3333333730697632;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "animCurveTL219";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 -0.0032546051995154474 40 -0.0032546051995154474 
		70 -0.0032546051995154474;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1.3333333730697632;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "animCurveTU21";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 5;
createNode animCurveTA -n "animCurveTA220";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 -31.020612655123333;
createNode animCurveTA -n "animCurveTA221";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 11.198285947268632;
createNode animCurveTA -n "animCurveTA222";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 4.823799912124791;
createNode animCurveTU -n "animCurveTU22";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 5.8000000000000007;
createNode animCurveTA -n "animCurveTA223";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 -33.118292212018972;
createNode animCurveTA -n "animCurveTA224";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 -1.2808772232691179;
createNode animCurveTA -n "animCurveTA225";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 -2.8759112065701404;
createNode animCurveTA -n "animCurveTA226";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 90.653592159103439;
createNode animCurveTL -n "animCurveTL220";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0.002388170883337609;
createNode animCurveTL -n "animCurveTL221";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0.084972716487962008;
createNode animCurveTL -n "animCurveTL222";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0.035778931447803565;
createNode animCurveTU -n "animCurveTU23";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 3.1;
createNode animCurveTA -n "animCurveTA227";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 27.45475670134093;
createNode animCurveTA -n "animCurveTA228";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA229";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 16.11950950967347;
createNode animCurveTU -n "animCurveTU24";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 3.7;
createNode animCurveTA -n "animCurveTA230";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 5.617037998813025;
createNode animCurveTA -n "animCurveTA240";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0 40 0 70 0;
	setAttr -s 3 ".kit[2]"  3;
	setAttr -s 3 ".kot[2]"  3;
createNode animCurveTA -n "animCurveTA241";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0 40 0 70 0;
	setAttr -s 3 ".kit[2]"  3;
	setAttr -s 3 ".kot[2]"  3;
createNode animCurveTA -n "animCurveTA242";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0 40 -4.8219457199987392 70 0;
	setAttr -s 3 ".kit[2]"  3;
	setAttr -s 3 ".kot[2]"  3;
createNode animCurveTA -n "animCurveTA249";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0 35 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1.1666666269302368;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "animCurveTA250";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0 35 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1.1666666269302368;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "animCurveTA251";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  0 0 35 0.63436504012088224 70 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "animCurveTL223";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  0 0.022398622623901798 35 0.016414570861972164 
		70 0.022398622623901798;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "animCurveTL224";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  0 0 35 -0.00041973616822177265 70 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "animCurveTL225";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0 35 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1.1666666269302368;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "animCurveTL232";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0 40 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1.3333333730697632;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "animCurveTL233";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0 40 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1.3333333730697632;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "animCurveTL234";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0 40 -0.063144084550375235 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1.3333333730697632;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "animCurveTA252";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA253";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA254";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL238";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0.13412027915836044;
createNode animCurveTL -n "animCurveTL239";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL240";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA255";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA256";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA257";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL241";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 -0.0097076682746837228;
createNode animCurveTL -n "animCurveTL242";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL243";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA258";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA259";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA260";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL244";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 -0.0088452850090936508;
createNode animCurveTL -n "animCurveTL245";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL246";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA261";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA262";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA263";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL247";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0.32999671331968833;
createNode animCurveTL -n "animCurveTL248";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL249";
	setAttr ".tan" 10;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL250";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 35 0 55 0 70 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  0.1666666716337204;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1.5;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL251";
	setAttr ".tan" 1;
	setAttr -s 5 ".ktv[0:4]"  0 -0.1069060174164429 20 -0.15540179365955337 
		35 -0.028550334719977588 55 0.071445716976025003 70 -0.1069060174164429;
	setAttr -s 5 ".kix[0:4]"  0.087348133325576782 0.63043063879013062 
		0.40422368049621582 0.65924841165542603 0.22261592745780945;
	setAttr -s 5 ".kiy[0:4]"  -0.036886114627122879 0.057238250970840454 
		0.12445241957902908 -0.05186893418431282 -0.1167309582233429;
	setAttr -s 5 ".kox[0:4]"  0.34939262270927429 0.47282299399375916 
		0.53896486759185791 0.494436115026474 0.22261589765548706;
	setAttr -s 5 ".koy[0:4]"  -0.14754457771778107 0.042928703129291534 
		0.16593654453754425 -0.038901694118976593 -0.1167309582233429;
createNode animCurveTL -n "animCurveTL252";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 35 0 55 0 70 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  0.1666666716337204;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1.5;
	setAttr -s 5 ".koy[4]"  0;
createNode lightLinker -n "lightLinker1";
	setAttr -s 6 ".lnk";
	setAttr -s 4 ".slnk";
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
	setAttr ".miic" -type "float3" 97.409096 97.409096 97.409096 ;
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
connectAttr "idleSource.cl" "clipLibrary1.sc[0]";
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
connectAttr "animCurveTA193.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "animCurveTA194.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "animCurveTA195.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "animCurveTL190.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "animCurveTL191.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "animCurveTL192.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "animCurveTL193.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "animCurveTL194.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "animCurveTL195.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "animCurveTU17.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "animCurveTA196.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "animCurveTA197.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "animCurveTA198.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "animCurveTL196.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "animCurveTL197.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "animCurveTL198.a" "clipLibrary1.cel[0].cev[63].cevr";
connectAttr "animCurveTU18.a" "clipLibrary1.cel[0].cev[64].cevr";
connectAttr "animCurveTA199.a" "clipLibrary1.cel[0].cev[65].cevr";
connectAttr "animCurveTA200.a" "clipLibrary1.cel[0].cev[66].cevr";
connectAttr "animCurveTA201.a" "clipLibrary1.cel[0].cev[67].cevr";
connectAttr "animCurveTL199.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "animCurveTL200.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "animCurveTL201.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "animCurveTL202.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "animCurveTL203.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "animCurveTL204.a" "clipLibrary1.cel[0].cev[73].cevr";
connectAttr "animCurveTL205.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "animCurveTL206.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "animCurveTL207.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "animCurveTU19.a" "clipLibrary1.cel[0].cev[77].cevr";
connectAttr "animCurveTA202.a" "clipLibrary1.cel[0].cev[78].cevr";
connectAttr "animCurveTA203.a" "clipLibrary1.cel[0].cev[79].cevr";
connectAttr "animCurveTA204.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "animCurveTL208.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "animCurveTL209.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "animCurveTL210.a" "clipLibrary1.cel[0].cev[83].cevr";
connectAttr "animCurveTU20.a" "clipLibrary1.cel[0].cev[84].cevr";
connectAttr "animCurveTA205.a" "clipLibrary1.cel[0].cev[85].cevr";
connectAttr "animCurveTA206.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "animCurveTA207.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "animCurveTL211.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "animCurveTL212.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr "animCurveTL213.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "animCurveTA208.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "animCurveTA209.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "animCurveTA210.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "animCurveTL214.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "animCurveTL215.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "animCurveTL216.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "animCurveTA211.a" "clipLibrary1.cel[0].cev[123].cevr";
connectAttr "animCurveTA212.a" "clipLibrary1.cel[0].cev[124].cevr";
connectAttr "animCurveTA213.a" "clipLibrary1.cel[0].cev[125].cevr";
connectAttr "animCurveTA214.a" "clipLibrary1.cel[0].cev[126].cevr";
connectAttr "animCurveTA215.a" "clipLibrary1.cel[0].cev[127].cevr";
connectAttr "animCurveTA216.a" "clipLibrary1.cel[0].cev[128].cevr";
connectAttr "animCurveTA217.a" "clipLibrary1.cel[0].cev[129].cevr";
connectAttr "animCurveTA218.a" "clipLibrary1.cel[0].cev[130].cevr";
connectAttr "animCurveTA219.a" "clipLibrary1.cel[0].cev[131].cevr";
connectAttr "animCurveTL217.a" "clipLibrary1.cel[0].cev[132].cevr";
connectAttr "animCurveTL218.a" "clipLibrary1.cel[0].cev[133].cevr";
connectAttr "animCurveTL219.a" "clipLibrary1.cel[0].cev[134].cevr";
connectAttr "animCurveTU21.a" "clipLibrary1.cel[0].cev[135].cevr";
connectAttr "animCurveTA220.a" "clipLibrary1.cel[0].cev[136].cevr";
connectAttr "animCurveTA221.a" "clipLibrary1.cel[0].cev[137].cevr";
connectAttr "animCurveTA222.a" "clipLibrary1.cel[0].cev[138].cevr";
connectAttr "animCurveTU22.a" "clipLibrary1.cel[0].cev[139].cevr";
connectAttr "animCurveTA223.a" "clipLibrary1.cel[0].cev[140].cevr";
connectAttr "animCurveTA224.a" "clipLibrary1.cel[0].cev[141].cevr";
connectAttr "animCurveTA225.a" "clipLibrary1.cel[0].cev[142].cevr";
connectAttr "animCurveTA226.a" "clipLibrary1.cel[0].cev[143].cevr";
connectAttr "animCurveTL220.a" "clipLibrary1.cel[0].cev[144].cevr";
connectAttr "animCurveTL221.a" "clipLibrary1.cel[0].cev[145].cevr";
connectAttr "animCurveTL222.a" "clipLibrary1.cel[0].cev[146].cevr";
connectAttr "animCurveTU23.a" "clipLibrary1.cel[0].cev[147].cevr";
connectAttr "animCurveTA227.a" "clipLibrary1.cel[0].cev[148].cevr";
connectAttr "animCurveTA228.a" "clipLibrary1.cel[0].cev[149].cevr";
connectAttr "animCurveTA229.a" "clipLibrary1.cel[0].cev[150].cevr";
connectAttr "animCurveTU24.a" "clipLibrary1.cel[0].cev[151].cevr";
connectAttr "animCurveTA230.a" "clipLibrary1.cel[0].cev[152].cevr";
connectAttr "animCurveTA240.a" "clipLibrary1.cel[0].cev[205].cevr";
connectAttr "animCurveTA241.a" "clipLibrary1.cel[0].cev[206].cevr";
connectAttr "animCurveTA242.a" "clipLibrary1.cel[0].cev[207].cevr";
connectAttr "animCurveTA249.a" "clipLibrary1.cel[0].cev[214].cevr";
connectAttr "animCurveTA250.a" "clipLibrary1.cel[0].cev[215].cevr";
connectAttr "animCurveTA251.a" "clipLibrary1.cel[0].cev[216].cevr";
connectAttr "animCurveTL223.a" "clipLibrary1.cel[0].cev[217].cevr";
connectAttr "animCurveTL224.a" "clipLibrary1.cel[0].cev[218].cevr";
connectAttr "animCurveTL225.a" "clipLibrary1.cel[0].cev[219].cevr";
connectAttr "animCurveTL232.a" "clipLibrary1.cel[0].cev[229].cevr";
connectAttr "animCurveTL233.a" "clipLibrary1.cel[0].cev[230].cevr";
connectAttr "animCurveTL234.a" "clipLibrary1.cel[0].cev[231].cevr";
connectAttr "animCurveTA252.a" "clipLibrary1.cel[0].cev[235].cevr";
connectAttr "animCurveTA253.a" "clipLibrary1.cel[0].cev[236].cevr";
connectAttr "animCurveTA254.a" "clipLibrary1.cel[0].cev[237].cevr";
connectAttr "animCurveTL238.a" "clipLibrary1.cel[0].cev[238].cevr";
connectAttr "animCurveTL239.a" "clipLibrary1.cel[0].cev[239].cevr";
connectAttr "animCurveTL240.a" "clipLibrary1.cel[0].cev[240].cevr";
connectAttr "animCurveTA255.a" "clipLibrary1.cel[0].cev[241].cevr";
connectAttr "animCurveTA256.a" "clipLibrary1.cel[0].cev[242].cevr";
connectAttr "animCurveTA257.a" "clipLibrary1.cel[0].cev[243].cevr";
connectAttr "animCurveTL241.a" "clipLibrary1.cel[0].cev[244].cevr";
connectAttr "animCurveTL242.a" "clipLibrary1.cel[0].cev[245].cevr";
connectAttr "animCurveTL243.a" "clipLibrary1.cel[0].cev[246].cevr";
connectAttr "animCurveTA258.a" "clipLibrary1.cel[0].cev[247].cevr";
connectAttr "animCurveTA259.a" "clipLibrary1.cel[0].cev[248].cevr";
connectAttr "animCurveTA260.a" "clipLibrary1.cel[0].cev[249].cevr";
connectAttr "animCurveTL244.a" "clipLibrary1.cel[0].cev[250].cevr";
connectAttr "animCurveTL245.a" "clipLibrary1.cel[0].cev[251].cevr";
connectAttr "animCurveTL246.a" "clipLibrary1.cel[0].cev[252].cevr";
connectAttr "animCurveTA261.a" "clipLibrary1.cel[0].cev[253].cevr";
connectAttr "animCurveTA262.a" "clipLibrary1.cel[0].cev[254].cevr";
connectAttr "animCurveTA263.a" "clipLibrary1.cel[0].cev[255].cevr";
connectAttr "animCurveTL247.a" "clipLibrary1.cel[0].cev[256].cevr";
connectAttr "animCurveTL248.a" "clipLibrary1.cel[0].cev[257].cevr";
connectAttr "animCurveTL249.a" "clipLibrary1.cel[0].cev[258].cevr";
connectAttr "animCurveTL250.a" "clipLibrary1.cel[0].cev[259].cevr";
connectAttr "animCurveTL251.a" "clipLibrary1.cel[0].cev[260].cevr";
connectAttr "animCurveTL252.a" "clipLibrary1.cel[0].cev[261].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of idle.ma
