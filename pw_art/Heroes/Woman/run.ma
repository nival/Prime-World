//Maya ASCII 2008 scene
//Name: run.ma
//Last modified: Tue, May 26, 2009 01:06:44 PM
//Codeset: 1251
requires maya "2008";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Complete 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200802250025-718075";
fileInfo "osv" "Microsoft Windows XP Service Pack 3 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 113 ".cel[0].cev";
	setAttr ".cd[0].cm" -type "characterMapping" 218 "FKIKControlCurveLeg_L.IKVis" 
		0 1 "FKIKControlCurveLeg_L.FKVis" 0 2 "FKIKControlCurveLeg_L.FKIKBlend" 
		0 3 "FKIKControlCurveArm_L.IKVis" 0 4 "FKIKControlCurveArm_L.FKVis" 
		0 5 "FKIKControlCurveArm_L.FKIKBlend" 0 6 "FKIKControlCurveSpine_M.IKVis" 
		0 7 "FKIKControlCurveSpine_M.FKVis" 0 8 "FKIKControlCurveSpine_M.FKIKBlend" 
		0 9 "FKIKControlCurveLeg_R.IKVis" 0 10 "FKIKControlCurveLeg_R.FKVis" 
		0 11 "FKIKControlCurveLeg_R.FKIKBlend" 0 12 "FKIKControlCurveArm_R.IKVis" 
		0 13 "FKIKControlCurveArm_R.FKVis" 0 14 "FKIKControlCurveArm_R.FKIKBlend" 
		0 15 "IKPoleVectorCurveLeg_L.follow" 0 16 "IKPoleVectorCurveLeg_L.translateZ" 
		1 1 "IKPoleVectorCurveLeg_L.translateY" 1 2 "IKPoleVectorCurveLeg_L.translateX" 
		1 3 "IKCurveLegBall_L.rotateX" 2 1 "IKCurveLegToe_L.rotateZ" 
		2 2 "IKCurveLegToe_L.rotateY" 2 3 "IKCurveLegToe_L.rotateX" 2 
		4 "IKCurveLeg_L.rollAngle" 0 17 "IKCurveLeg_L.roll" 0 18 "IKCurveLeg_L.swivel" 
		0 19 "IKCurveLeg_L.rotateZ" 2 5 "IKCurveLeg_L.rotateY" 2 
		6 "IKCurveLeg_L.rotateX" 2 7 "IKCurveLeg_L.translateZ" 1 4 "IKCurveLeg_L.translateY" 
		1 5 "IKCurveLeg_L.translateX" 1 6 "IKPoleVectorCurveLeg_R.follow" 
		0 20 "IKPoleVectorCurveLeg_R.translateZ" 1 7 "IKPoleVectorCurveLeg_R.translateY" 
		1 8 "IKPoleVectorCurveLeg_R.translateX" 1 9 "IKCurveLegBall_R.rotateX" 
		2 8 "IKCurveLegToe_R.rotateZ" 2 9 "IKCurveLegToe_R.rotateY" 2 
		10 "IKCurveLegToe_R.rotateX" 2 11 "IKCurveLeg_R.rollAngle" 0 21 "IKCurveLeg_R.roll" 
		0 22 "IKCurveLeg_R.swivel" 0 23 "IKCurveLeg_R.rotateZ" 2 12 "IKCurveLeg_R.rotateY" 
		2 13 "IKCurveLeg_R.rotateX" 2 14 "IKCurveLeg_R.translateZ" 1 
		10 "IKCurveLeg_R.translateY" 1 11 "IKCurveLeg_R.translateX" 1 12 "HipSwingerRoot_M.rotateZ" 
		2 15 "HipSwingerRoot_M.rotateY" 2 16 "HipSwingerRoot_M.rotateX" 
		2 17 "RootCurveRoot_M.CenterBtwFeet" 0 24 "RootCurveRoot_M.rotateZ" 
		2 18 "RootCurveRoot_M.rotateY" 2 19 "RootCurveRoot_M.rotateX" 2 
		20 "RootCurveRoot_M.translateZ" 1 13 "RootCurveRoot_M.translateY" 1 
		14 "RootCurveRoot_M.translateX" 1 15 "FKCurveShirt_07_L.rotateZ" 2 
		21 "FKCurveShirt_07_L.rotateY" 2 22 "FKCurveShirt_07_L.rotateX" 2 
		23 "FKCurveAnkle_L.rotateZ" 2 24 "FKCurveAnkle_L.rotateY" 2 25 "FKCurveAnkle_L.rotateX" 
		2 26 "FKCurveMiddleToe1_L.rotateZ" 2 27 "FKCurveShoulder_L.Global" 
		0 25 "FKCurveShoulder_L.rotateZ" 2 28 "FKCurveShoulder_L.rotateY" 
		2 29 "FKCurveShoulder_L.rotateX" 2 30 "FKCurveElbow_L.rotateY" 
		2 31 "FKCurveIndexFinger3_L.rotateZ" 2 32 "FKCurveIndexFinger3_L.rotateY" 
		2 33 "FKCurveIndexFinger3_L.rotateX" 2 34 "FKCurveIndexFinger2_L.rotateZ" 
		2 35 "FKCurveIndexFinger2_L.rotateY" 2 36 "FKCurveIndexFinger2_L.rotateX" 
		2 37 "FKCurveIndexFinger1_L.rotateZ" 2 38 "FKCurveIndexFinger1_L.rotateY" 
		2 39 "FKCurveIndexFinger1_L.rotateX" 2 40 "FKCurveThumbFinger3_L.rotateZ" 
		2 41 "FKCurveThumbFinger3_L.rotateY" 2 42 "FKCurveThumbFinger3_L.rotateX" 
		2 43 "FKCurveThumbFinger2_L.rotateZ" 2 44 "FKCurveThumbFinger2_L.rotateY" 
		2 45 "FKCurveThumbFinger2_L.rotateX" 2 46 "FKCurveThumbFinger1_L.rotateZ" 
		2 47 "FKCurveThumbFinger1_L.rotateY" 2 48 "FKCurveThumbFinger1_L.rotateX" 
		2 49 "FKCurveWrist_L.Spread" 0 26 "FKCurveWrist_L.ThumbFingerCurl" 
		0 27 "FKCurveWrist_L.IndexFingerCurl" 0 28 "FKCurveWrist_L.Global" 
		0 29 "FKCurveWrist_L.rotateZ" 2 50 "FKCurveWrist_L.rotateY" 2 
		51 "FKCurveWrist_L.rotateX" 2 52 "FKCurveShirt_04_L.rotateZ" 2 
		53 "FKCurveShirt_04_L.rotateY" 2 54 "FKCurveShirt_04_L.rotateX" 2 
		55 "FKCurveShirt_02_L.rotateZ" 2 56 "FKCurveShirt_02_L.rotateY" 2 
		57 "FKCurveShirt_02_L.rotateX" 2 58 "FKCurveShirt_01_L.rotateZ" 2 
		59 "FKCurveShirt_01_L.rotateY" 2 60 "FKCurveShirt_01_L.rotateX" 2 
		61 "FKCurveShirt_07_R.rotateZ" 2 62 "FKCurveShirt_07_R.rotateY" 2 
		63 "FKCurveShirt_07_R.rotateX" 2 64 "FKCurveAnkle_R.rotateZ" 2 
		65 "FKCurveAnkle_R.rotateY" 2 66 "FKCurveAnkle_R.rotateX" 2 67 "FKCurveMiddleToe1_R.rotateZ" 
		2 68 "FKCurveBackA_M.rotateZ" 2 69 "FKCurveBackA_M.rotateY" 2 
		70 "FKCurveBackA_M.rotateX" 2 71 "FKCurveBackB1_M.rotateZ" 2 72 "FKCurveBackB1_M.rotateY" 
		2 73 "FKCurveBackB1_M.rotateX" 2 74 "FKCurveBackB_M.rotateZ" 2 
		75 "FKCurveBackB_M.rotateY" 2 76 "FKCurveBackB_M.rotateX" 2 77 "FKCurveCap_03_L.rotateZ" 
		2 78 "FKCurveCap_03_L.rotateY" 2 79 "FKCurveCap_03_L.rotateX" 2 
		80 "FKCurveCap_02_L.rotateZ" 2 81 "FKCurveCap_02_L.rotateY" 2 82 "FKCurveCap_02_L.rotateX" 
		2 83 "FKCurveCap_01_L.rotateZ" 2 84 "FKCurveCap_01_L.rotateY" 2 
		85 "FKCurveCap_01_L.rotateX" 2 86 "FKCurveScapula_L.rotateZ" 2 
		87 "FKCurveScapula_L.rotateY" 2 88 "FKCurveScapula_L.rotateX" 2 
		89 "FKCurveCap_03_R.rotateZ" 2 90 "FKCurveCap_03_R.rotateY" 2 91 "FKCurveCap_03_R.rotateX" 
		2 92 "FKCurveCap_02_R.rotateZ" 2 93 "FKCurveCap_02_R.rotateY" 2 
		94 "FKCurveCap_02_R.rotateX" 2 95 "FKCurveCap_01_R.rotateZ" 2 96 "FKCurveCap_01_R.rotateY" 
		2 97 "FKCurveCap_01_R.rotateX" 2 98 "FKCurveCap_07_L.rotateZ" 2 
		99 "FKCurveCap_07_L.rotateY" 2 100 "FKCurveCap_07_L.rotateX" 2 101 "FKCurveCap_06_L.rotateZ" 
		2 102 "FKCurveCap_06_L.rotateY" 2 103 "FKCurveCap_06_L.rotateX" 2 
		104 "FKCurveCap_05_L.rotateZ" 2 105 "FKCurveCap_05_L.rotateY" 2 106 "FKCurveCap_05_L.rotateX" 
		2 107 "FKCurveTail_02_L.rotateZ" 2 108 "FKCurveTail_02_L.rotateY" 
		2 109 "FKCurveTail_02_L.rotateX" 2 110 "FKCurveTail_01_L.rotateZ" 
		2 111 "FKCurveTail_01_L.rotateY" 2 112 "FKCurveTail_01_L.rotateX" 
		2 113 "FKCurveHair_02_L.rotateZ" 2 114 "FKCurveHair_02_L.rotateY" 
		2 115 "FKCurveHair_02_L.rotateX" 2 116 "FKCurveHair_01_L.rotateZ" 
		2 117 "FKCurveHair_01_L.rotateY" 2 118 "FKCurveHair_01_L.rotateX" 
		2 119 "FKCurveTail_02_R.rotateZ" 2 120 "FKCurveTail_02_R.rotateY" 
		2 121 "FKCurveTail_02_R.rotateX" 2 122 "FKCurveTail_01_R.rotateZ" 
		2 123 "FKCurveTail_01_R.rotateY" 2 124 "FKCurveTail_01_R.rotateX" 
		2 125 "FKCurveHead_M.Global" 0 30 "FKCurveHead_M.rotateZ" 2 
		126 "FKCurveHead_M.rotateY" 2 127 "FKCurveHead_M.rotateX" 2 128 "FKCurveNeck_M.rotateZ" 
		2 129 "FKCurveNeck_M.rotateY" 2 130 "FKCurveNeck_M.rotateX" 2 
		131 "FKCurveScapula_R.rotateZ" 2 132 "FKCurveScapula_R.rotateY" 2 
		133 "FKCurveScapula_R.rotateX" 2 134 "FKCurveChest_M.rotateZ" 2 135 "FKCurveChest_M.rotateY" 
		2 136 "FKCurveChest_M.rotateX" 2 137 "FKCurveShoulder_R.Global" 0 
		31 "FKCurveShoulder_R.rotateZ" 2 138 "FKCurveShoulder_R.rotateY" 2 
		139 "FKCurveShoulder_R.rotateX" 2 140 "FKCurveElbow_R.rotateY" 2 
		141 "FKCurveIndexFinger3_R.rotateZ" 2 142 "FKCurveIndexFinger3_R.rotateY" 
		2 143 "FKCurveIndexFinger3_R.rotateX" 2 144 "FKCurveIndexFinger2_R.rotateZ" 
		2 145 "FKCurveIndexFinger2_R.rotateY" 2 146 "FKCurveIndexFinger2_R.rotateX" 
		2 147 "FKCurveIndexFinger1_R.rotateZ" 2 148 "FKCurveIndexFinger1_R.rotateY" 
		2 149 "FKCurveIndexFinger1_R.rotateX" 2 150 "FKCurveThumbFinger3_R.rotateZ" 
		2 151 "FKCurveThumbFinger3_R.rotateY" 2 152 "FKCurveThumbFinger3_R.rotateX" 
		2 153 "FKCurveThumbFinger2_R.rotateZ" 2 154 "FKCurveThumbFinger2_R.rotateY" 
		2 155 "FKCurveThumbFinger2_R.rotateX" 2 156 "FKCurveThumbFinger1_R.rotateZ" 
		2 157 "FKCurveThumbFinger1_R.rotateY" 2 158 "FKCurveThumbFinger1_R.rotateX" 
		2 159 "FKCurveWrist_R.Spread" 0 32 "FKCurveWrist_R.ThumbFingerCurl" 
		0 33 "FKCurveWrist_R.IndexFingerCurl" 0 34 "FKCurveWrist_R.Global" 
		0 35 "FKCurveWrist_R.rotateZ" 2 160 "FKCurveWrist_R.rotateY" 2 
		161 "FKCurveWrist_R.rotateX" 2 162 "All.rotateZ" 2 163 "All.rotateY" 
		2 164 "All.rotateX" 2 165 "All.translateZ" 1 16 "All.translateY" 
		1 17 "All.translateX" 1 18  ;
	setAttr ".cd[0].cim" -type "Int32Array" 218 0 1 2 3 4
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
		 173 174 175 176 177 178 179 180 181 182 183 184
		 185 186 187 188 189 190 191 192 193 194 195 196
		 197 198 199 200 201 202 203 204 205 206 207 208
		 209 210 211 212 213 214 215 216 217 ;
createNode animClip -n "runSource";
	setAttr ".ihi" 0;
	setAttr -s 113 ".ac";
	setAttr ".ac[16:18]" yes yes yes;
	setAttr ".ac[26:31]" yes yes yes yes yes yes;
	setAttr ".ac[33:35]" yes yes yes;
	setAttr ".ac[43:48]" yes yes yes yes yes yes;
	setAttr ".ac[53:61]" yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[67:70]" yes yes yes yes;
	setAttr ".ac[93:107]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes;
	setAttr ".ac[112:129]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes;
	setAttr ".ac[133:150]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes;
	setAttr ".ac[157:162]" yes yes yes yes yes yes;
	setAttr ".ac[170:175]" yes yes yes yes yes yes;
	setAttr ".ac[179:181]" yes yes yes;
	setAttr ".ac[183:186]" yes yes yes yes;
	setAttr ".ac[193:198]" yes yes yes yes yes yes;
	setAttr ".ac[202:204]" yes yes yes;
	setAttr ".ac[209:211]" yes yes yes;
	setAttr ".se" 18;
	setAttr ".ci" no;
createNode animCurveTL -n "IKPoleVectorCurveLeg_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.00026144446081529586 2 -0.015286025679820825 
		5 -0.0052722030881556647 9 -0.0065357103853514696 11 -0.0060735102550556353 18 -0.00026144446081529586;
	setAttr -s 6 ".kit[4:5]"  1 1;
	setAttr -s 6 ".kot[4:5]"  1 1;
	setAttr -s 6 ".kix[4:5]"  0.99993383884429932 1;
	setAttr -s 6 ".kiy[4:5]"  0.011503425426781178 0;
	setAttr -s 6 ".kox[4:5]"  0.99993383884429932 1;
	setAttr -s 6 ".koy[4:5]"  0.011503427289426327 0;
createNode animCurveTL -n "IKPoleVectorCurveLeg_L_translateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.00024847948345783905 2 -0.0043837800964058073 
		5 0.0073131564245535012 9 0.012094061047812427 11 0.0071195688365217865 18 -0.00024847948345783905;
	setAttr -s 6 ".kit[1:5]"  10 1 10 1 1;
	setAttr -s 6 ".kot[1:5]"  10 1 10 1 1;
	setAttr -s 6 ".kix[0:5]"  0.99991083145141602 1 0.99580323696136475 
		1 0.99852293729782104 0.99991273880004883;
	setAttr -s 6 ".kiy[0:5]"  -0.013356230221688747 0 0.091520428657531738 
		0 -0.054332051426172256 -0.013215662911534309;
	setAttr -s 6 ".kox[0:5]"  0.99991083145141602 1 0.99580323696136475 
		1 0.99852299690246582 0.99991273880004883;
	setAttr -s 6 ".koy[0:5]"  -0.013356231153011322 0 0.091520451009273529 
		0 -0.054332040250301361 -0.013215664774179459;
createNode animCurveTL -n "IKPoleVectorCurveLeg_L_translateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.0036781614106423232 2 -0.10043937963923898 
		5 0.10276961743299078 9 0.13518860614944403 11 0.083583132391709294 18 -0.0036781614106423232;
	setAttr -s 6 ".kit[1:5]"  10 1 1 10 1;
	setAttr -s 6 ".kot[1:5]"  10 1 1 10 1;
	setAttr -s 6 ".kix[0:5]"  0.99404054880142212 0.84277361631393433 
		0.78083300590515137 0.93814098834991455 0.90749245882034302 0.99397921562194824;
	setAttr -s 6 ".kiy[0:5]"  -0.10901109874248505 0.53826826810836792 
		0.62473982572555542 -0.34625351428985596 -0.42006844282150269 -0.10956916213035583;
	setAttr -s 6 ".kox[0:5]"  0.99404060840606689 0.84277361631393433 
		0.78083282709121704 0.93814104795455933 0.90749245882034302 0.99397921562194824;
	setAttr -s 6 ".koy[0:5]"  -0.10901109874248505 0.53826826810836792 
		0.62474006414413452 -0.34625348448753357 -0.42006844282150269 -0.10956916958093643;
createNode animCurveTA -n "IKCurveLeg_L_rotateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 9 -7.8961052418785673 11 -4.739422734917186 
		14 -4.2379330668715305 18 0;
	setAttr -s 5 ".kit[0:4]"  3 3 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 3 1 1 1;
	setAttr -s 5 ".kix[2:4]"  0.99315321445465088 0.99682009220123291 
		1;
	setAttr -s 5 ".kiy[2:4]"  0.11681924760341644 0.079685278236865997 
		0;
	setAttr -s 5 ".kox[2:4]"  0.99315321445465088 0.99682009220123291 
		1;
	setAttr -s 5 ".koy[2:4]"  0.11681922525167465 0.079685278236865997 
		0;
createNode animCurveTA -n "IKCurveLeg_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.39914628686590758 2 2.7571472870547966 
		5 0.86216693892950891 9 1.4448489821671229 11 0.86216693892951468 14 -3.5229012702802516 
		18 0.39914628686590758;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 1 10 1;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 1 10 1;
	setAttr -s 7 ".kix[0:6]"  0.85268831253051758 1 1 1 0.97246617078781128 
		0.99940085411071777 0.85042697191238403;
	setAttr -s 7 ".kiy[0:6]"  0.52242004871368408 0 0 0 -0.23304443061351776 
		-0.03461311012506485 0.52609318494796753;
	setAttr -s 7 ".kox[0:6]"  0.85268831253051758 1 1 1 0.9724661111831665 
		0.99940085411071777 0.85042703151702881;
	setAttr -s 7 ".koy[0:6]"  0.52242004871368408 0 0 0 -0.23304450511932373 
		-0.03461311012506485 0.52609306573867798;
createNode animCurveTA -n "IKCurveLeg_L_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 1.6107867357656509 5 56.263954905876005 
		9 100.42964808191302 11 68.140907287207327 14 27.787583429941506 16 4.4735510731723034 
		18 0;
	setAttr -s 8 ".kit[0:7]"  10 1 1 3 1 1 10 1;
	setAttr -s 8 ".kot[0:7]"  10 1 1 3 1 1 10 1;
	setAttr -s 8 ".kix[1:7]"  0.57991683483123779 0.069299869239330292 
		1 0.11214616894721985 0.14960598945617676 0.26508721709251404 1;
	setAttr -s 8 ".kiy[1:7]"  0.81467568874359131 0.99759590625762939 
		0 -0.99369174242019653 -0.98874568939208984 -0.96422445774078369 0;
	setAttr -s 8 ".kox[1:7]"  0.57991695404052734 0.069299861788749695 
		1 0.11214616894721985 0.14960598945617676 0.26508721709251404 1;
	setAttr -s 8 ".koy[1:7]"  0.81467568874359131 0.99759584665298462 
		0 -0.99369174242019653 -0.98874568939208984 -0.96422445774078369 0;
createNode animCurveTL -n "IKCurveLeg_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.1992748724595016 2 -0.42910761118426521 
		5 -0.84325487864088922 9 -0.86495135600599948 11 -0.40622583457224359 14 0.44175003674307467 
		16 0.55151866625904411 18 0.1992748724595016;
	setAttr -s 8 ".kit[7]"  1;
	setAttr -s 8 ".kot[7]"  1;
	setAttr -s 8 ".kix[7]"  0.10550042986869812;
	setAttr -s 8 ".kiy[7]"  -0.99441927671432495;
	setAttr -s 8 ".kox[7]"  0.10550042986869812;
	setAttr -s 8 ".koy[7]"  -0.99441927671432495;
createNode animCurveTL -n "IKCurveLeg_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -4.4247910326756021e-017 2 -0.001877127572350157 
		5 0.36676622377792462 9 0.59302948772835873 11 0.53413904916591715 14 0.47994861004034173 
		16 0.22418937252148685 18 -4.4247910326756021e-017;
	setAttr -s 8 ".kit[7]"  1;
	setAttr -s 8 ".kot[7]"  1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTL -n "IKCurveLeg_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.099872282570830362 2 -0.11020767255795175 
		5 -0.1292341848694058 9 -0.1292341848694058 11 -0.082100787719999013 14 -0.1292341848694058 
		18 -0.099872282570830362;
	setAttr -s 7 ".kit[6]"  1;
	setAttr -s 7 ".kot[6]"  1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTL -n "IKPoleVectorCurveLeg_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.0017341302558844186 2 -0.0022658491436672347 
		9 -0.0003393533274724357 14 -0.0018320706968544111 18 -0.0017341302558844186;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "IKPoleVectorCurveLeg_R_translateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.013721572558675852 2 0.012577835190673615 
		9 0.0088843142908362326 14 0.01114264838078614 18 0.013721572558675852;
	setAttr -s 5 ".kit[0:4]"  10 1 10 1 1;
	setAttr -s 5 ".kot[0:4]"  10 1 10 1 1;
	setAttr -s 5 ".kix[1:4]"  0.99972254037857056 1 0.99951809644699097 
		1;
	setAttr -s 5 ".kiy[1:4]"  -0.023555522784590721 0 0.031042134389281273 
		0;
	setAttr -s 5 ".kox[1:4]"  0.99972254037857056 1 0.99951815605163574 
		1;
	setAttr -s 5 ".koy[1:4]"  -0.023555537685751915 0 0.031042147427797318 
		0;
createNode animCurveTL -n "IKPoleVectorCurveLeg_R_translateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.10052733366696029 2 -0.035496073305771009 
		9 -0.051014568563651871 14 -0.077799846674378406 18 -0.10052733366696029;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 3;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 3;
	setAttr -s 5 ".kix[2:4]"  0.98667174577713013 0.98568224906921387 
		1;
	setAttr -s 5 ".kiy[2:4]"  -0.16272343695163727 -0.16861379146575928 
		0;
	setAttr -s 5 ".kox[2:4]"  0.98667174577713013 0.98568218946456909 
		1;
	setAttr -s 5 ".koy[2:4]"  -0.16272352635860443 -0.1686137467622757 
		0;
createNode animCurveTA -n "IKCurveLeg_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 8.0443647974346337 5 -3.1280055948985583 
		7 -3.1280055948985677 9 -2.9643419978993886 14 -3.1280055948985797 18 8.0443647974346337;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 3;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 3;
createNode animCurveTA -n "IKCurveLeg_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -2.5875736830798322 5 1.6562996501889693 
		7 1.6562996501889742 9 5.7295594295618368 14 1.6562996501889797 18 -2.5875736830798322;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 1 3;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 1 3;
	setAttr -s 6 ".kix[4:5]"  0.78673529624938965 1;
	setAttr -s 6 ".kiy[4:5]"  -0.61729061603546143 0;
	setAttr -s 6 ".kox[4:5]"  0.78673529624938965 1;
	setAttr -s 6 ".koy[4:5]"  -0.61729061603546143 0;
createNode animCurveTA -n "IKCurveLeg_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 75.89008753502894 5 25.641740874886228 
		7 -5.5796313522810026 9 2.4114625021092575 11 2.703308301322084 14 62.249013435438684 
		18 75.89008753502894;
	setAttr -s 7 ".kit[0:6]"  3 1 3 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 1 3 10 10 10 3;
	setAttr -s 7 ".kix[1:6]"  0.10605805367231369 1 1 1 0.17969635128974915 
		1;
	setAttr -s 7 ".kiy[1:6]"  -0.99435997009277344 0 0 0 0.98372215032577515 
		0;
	setAttr -s 7 ".kox[1:6]"  0.10605805367231369 1 1 1 0.17969635128974915 
		1;
	setAttr -s 7 ".koy[1:6]"  -0.99435991048812866 0 0 0 0.98372215032577515 
		0;
createNode animCurveTL -n "IKCurveLeg_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.80552351496030128 2 -0.34692142202126669 
		5 0.41531398803616482 7 0.55588536444871317 9 0.22630030669866463 11 -0.39359904659019451 
		14 -0.77173765209639877 18 -0.80552351496030128;
	setAttr -s 8 ".kit[7]"  1;
	setAttr -s 8 ".kot[7]"  1;
	setAttr -s 8 ".kix[7]"  0.14385724067687988;
	setAttr -s 8 ".kiy[7]"  0.98959845304489136;
	setAttr -s 8 ".kox[7]"  0.14385724067687988;
	setAttr -s 8 ".koy[7]"  0.98959845304489136;
createNode animCurveTL -n "IKCurveLeg_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.55908534597197379 2 0.48428659526758111 
		5 0.537906685632078 9 0.0075039957473881473 11 0.0075039957473883112 14 0.38564260125359245 
		18 0.55908534597197379;
	setAttr -s 7 ".kit[0:6]"  3 10 3 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 3 10 10 10 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTL -n "IKCurveLeg_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.1363272205506369 2 0.066599279295640787 
		5 0.085948248055977783 9 0.1140573633789454 11 0.114 14 0.10000280571746134 18 0.1363272205506369;
	setAttr -s 7 ".kit[0:6]"  3 10 1 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 1 10 10 10 1;
	setAttr -s 7 ".kix[2:6]"  0.9626043438911438 1 1 1 1;
	setAttr -s 7 ".kiy[2:6]"  0.27091115713119507 0 0 0 0;
	setAttr -s 7 ".kox[2:6]"  0.9626043438911438 1 1 1 1;
	setAttr -s 7 ".koy[2:6]"  0.27091124653816223 0 0 0 0;
createNode animCurveTA -n "RootCurveRoot_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 3.7089771174126573 9 -3.709 18 3.7089771174126573;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "RootCurveRoot_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 9 0 18 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "RootCurveRoot_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 9.2395046138051953 9 7.3659458020559274 
		18 9.2395046138051953;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "RootCurveRoot_M_translateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.16409014520775284 2 -0.16409014520775286 
		5 -0.16409014520775284 9 -0.16409014520775284 11 -0.16409014520775286 14 -0.16409014520775284 
		18 -0.16409014520775284;
	setAttr -s 7 ".kit[0:6]"  10 10 10 1 1 1 1;
	setAttr -s 7 ".kot[0:6]"  10 10 10 1 1 1 1;
	setAttr -s 7 ".kix[3:6]"  1 1 1 1;
	setAttr -s 7 ".kiy[3:6]"  0 0 0 0;
	setAttr -s 7 ".kox[3:6]"  1 1 1 1;
	setAttr -s 7 ".koy[3:6]"  0 0 0 0;
createNode animCurveTL -n "RootCurveRoot_M_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.086913493007000131 2 -0.12299865938916096 
		5 -0.0091916278111308092 9 -0.086913493007000131 11 -0.12299865938916096 14 -0.0091916278111308092 
		18 -0.086913493007000131;
	setAttr -s 7 ".kit[0:6]"  1 3 3 1 3 3 1;
	setAttr -s 7 ".kot[0:6]"  1 3 3 1 3 3 1;
	setAttr -s 7 ".kix[0:6]"  0.7633826732635498 1 1 0.75608229637145996 
		1 1 0.7633826732635498;
	setAttr -s 7 ".kiy[0:6]"  -0.64594656229019165 0 0 -0.65447664260864258 
		0 0 -0.64594656229019165;
	setAttr -s 7 ".kox[0:6]"  0.76338255405426025 1 1 0.75608205795288086 
		1 1 0.76338255405426025;
	setAttr -s 7 ".koy[0:6]"  -0.6459466814994812 0 0 -0.65447688102722168 
		0 0 -0.6459466814994812;
createNode animCurveTL -n "RootCurveRoot_M_translateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.033658181048765543 2 0.045371302050160489 
		9 0.01491877083345515 11 0.0032076290657088724 14 0.016159325731467555 18 0.033658181048765543;
	setAttr -s 6 ".kit[1:5]"  10 1 1 1 1;
	setAttr -s 6 ".kot[1:5]"  10 1 1 1 1;
	setAttr -s 6 ".kix[0:5]"  0.99215608835220337 1 0.97299200296401978 
		1 0.98760116100311279 0.99215608835220337;
	setAttr -s 6 ".kiy[0:5]"  0.12500555813312531 0 -0.2308388352394104 
		0 0.15698392689228058 0.12500555813312531;
	setAttr -s 6 ".kox[0:5]"  0.99215608835220337 1 0.97299200296401978 
		1 0.98760116100311279 0.99215608835220337;
	setAttr -s 6 ".koy[0:5]"  0.12500554323196411 0 -0.23083898425102234 
		0 0.15698401629924774 0.12500554323196411;
createNode animCurveTA -n "FKCurveShirt_07_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 9.0955859099422653 5 -5.9793973376520047 
		9 7.0323984990325235 14 17.892354036004921 18 9.0955859099422653;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  0.53512436151504517;
	setAttr -s 5 ".kiy[4]"  -0.84477335214614868;
	setAttr -s 5 ".kox[4]"  0.53512436151504517;
	setAttr -s 5 ".koy[4]"  -0.84477335214614868;
createNode animCurveTA -n "FKCurveShirt_07_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.4249165592135355 5 5.4755507945221833 
		9 -0.817924333230863 14 3.9909601539409607 18 1.4249165592135355;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  0.92060202360153198;
	setAttr -s 5 ".kiy[4]"  0.39050227403640747;
	setAttr -s 5 ".kox[4]"  0.92060202360153198;
	setAttr -s 5 ".koy[4]"  0.39050227403640747;
createNode animCurveTA -n "FKCurveShirt_07_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -12.936871404160097 5 -16.705231538488125 
		9 -7.7045699465293476 14 -6.3882986911017907 18 -12.936871404160097;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  0.93019181489944458;
	setAttr -s 5 ".kiy[4]"  -0.36707392334938049;
	setAttr -s 5 ".kox[4]"  0.9301917552947998;
	setAttr -s 5 ".koy[4]"  -0.36707389354705811;
createNode animCurveTA -n "FKCurveShoulder_L_rotateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -74.933116724836481 5 -73.72920122611734 
		9 -69.519248017626623 14 -71.759778294121631 18 -74.933116724836481;
	setAttr -s 5 ".kit[0:4]"  3 1 10 1 3;
	setAttr -s 5 ".kot[0:4]"  3 1 10 1 3;
	setAttr -s 5 ".kix[1:4]"  0.94892477989196777 1 0.9124796986579895 
		1;
	setAttr -s 5 ".kiy[1:4]"  0.31550252437591553 0 -0.40912207961082458 
		0;
	setAttr -s 5 ".kox[1:4]"  0.948924720287323 1 0.9124796986579895 
		1;
	setAttr -s 5 ".koy[1:4]"  0.31550267338752747 0 -0.40912196040153503 
		0;
createNode animCurveTA -n "FKCurveShoulder_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 10.614791538430152 5 19.062989987589308 
		9 4.5030788434188365 14 -8.9238088500410431 16 -2.8491699408910796 18 10.614791538430152;
	setAttr -s 6 ".kit[5]"  1;
	setAttr -s 6 ".kot[5]"  1;
	setAttr -s 6 ".kix[5]"  0.74896764755249023;
	setAttr -s 6 ".kiy[5]"  0.66260665655136108;
	setAttr -s 6 ".kox[5]"  0.74896758794784546;
	setAttr -s 6 ".koy[5]"  0.66260659694671631;
createNode animCurveTA -n "FKCurveShoulder_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.53631086340241096 5 40.006108484391447 
		9 -6.405589524992263 14 -45.980976772111738 16 -39.099739228412439 18 0.53631086340241096;
	setAttr -s 6 ".kit[5]"  1;
	setAttr -s 6 ".kot[5]"  1;
	setAttr -s 6 ".kix[5]"  0.23515486717224121;
	setAttr -s 6 ".kiy[5]"  0.97195792198181152;
	setAttr -s 6 ".kox[5]"  0.23515485227108002;
	setAttr -s 6 ".koy[5]"  0.97195786237716675;
createNode animCurveTA -n "FKCurveElbow_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 43.24476258542817 5 56.223480946168664 
		9 64.217448748576189 14 37.987811676311182 16 43.330546576072557 18 43.24476258542817;
	setAttr -s 6 ".kit[0:5]"  1 1 10 10 10 1;
	setAttr -s 6 ".kot[0:5]"  1 1 10 10 10 1;
	setAttr -s 6 ".kix[0:5]"  1 0.47232910990715027 0.6859094500541687 
		0.5390937328338623 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0.88142228126525879 -0.72768694162368774 
		-0.84224581718444824 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.47232916951179504 0.6859094500541687 
		0.5390937328338623 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0.88142228126525879 -0.72768694162368774 
		-0.84224581718444824 0 0;
createNode animCurveTA -n "FKCurveWrist_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 3.3233168528430785 18 3.3233168528430785;
createNode animCurveTA -n "FKCurveWrist_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -5.8515861299017047 18 -5.8515861299017047;
createNode animCurveTA -n "FKCurveWrist_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 18 0;
createNode animCurveTA -n "FKCurveShirt_04_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -18.165439809773762 5 -13.310978670995782 
		9 -16.591116163089271 14 -30.640215195961002 18 -18.165439809773762;
createNode animCurveTA -n "FKCurveShirt_04_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 3.6764714105499601 5 15.958912840890269 
		9 -4.0495965054494905 14 -5.3189627770146224 18 3.6764714105499601;
createNode animCurveTA -n "FKCurveShirt_04_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 30.917170601365797 5 -33.311831797182194 
		9 -1.8142895132957144 14 39.656977780404901 18 30.917170601365797;
createNode animCurveTA -n "FKCurveShirt_02_L_rotateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -7.6130324620984355 5 -0.34582152424970602 
		9 -9.2508161062434464 14 -13.141574061977529 18 -7.6130324620984355;
	setAttr -s 5 ".kit[1:4]"  10 10 1 1;
	setAttr -s 5 ".kot[1:4]"  10 10 1 1;
	setAttr -s 5 ".kix[0:4]"  0.60961520671844482 0.99549132585525513 
		0.80214077234268188 0.94032883644104004 0.60961520671844482;
	setAttr -s 5 ".kiy[0:4]"  0.79269754886627197 -0.094852782785892487 
		-0.59713500738143921 0.34026703238487244 0.79269754886627197;
	setAttr -s 5 ".kox[0:4]"  0.60961538553237915 0.99549132585525513 
		0.80214077234268188 0.94032889604568481 0.60961538553237915;
	setAttr -s 5 ".koy[0:4]"  0.79269742965698242 -0.094852782785892487 
		-0.59713500738143921 0.34026700258255005 0.79269742965698242;
createNode animCurveTA -n "FKCurveShirt_02_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -2.978348003092488 5 6.0226482942832495 
		9 -13.854503234075906 14 -3.6052700488903429 18 -2.978348003092488;
	setAttr -s 5 ".kit[1:4]"  3 10 3 1;
	setAttr -s 5 ".kot[1:4]"  3 10 3 1;
	setAttr -s 5 ".kix[4]"  0.89359313249588013;
	setAttr -s 5 ".kiy[4]"  0.44887790083885193;
	setAttr -s 5 ".kox[4]"  0.89359313249588013;
	setAttr -s 5 ".koy[4]"  0.44887790083885193;
createNode animCurveTA -n "FKCurveShirt_02_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 32.273462654811432 5 -16.209614298000524 
		9 -28.87163145615466 14 9.6801586225126037 18 32.273462654811432;
	setAttr -s 5 ".kit[2:4]"  1 3 1;
	setAttr -s 5 ".kot[2:4]"  1 3 1;
	setAttr -s 5 ".kix[2:4]"  0.14953857660293579 1 1;
	setAttr -s 5 ".kiy[2:4]"  0.98875594139099121 0 0;
	setAttr -s 5 ".kox[2:4]"  0.14953859150409698 1 1;
	setAttr -s 5 ".koy[2:4]"  0.98875594139099121 0 0;
createNode animCurveTA -n "FKCurveShirt_01_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -19.353710123788716 5 -71.54660822399272 
		9 -21.476367436625214 14 -64.331732661867179 18 -19.353710123788716;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "FKCurveShirt_01_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 4.2189893072323166 5 -7.5343386958074321 
		9 0 14 -4.8243608667725564 18 4.2189893072323166;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  0.97117316722869873;
	setAttr -s 5 ".kiy[4]"  -0.23837527632713318;
	setAttr -s 5 ".kox[4]"  0.97117316722869873;
	setAttr -s 5 ".koy[4]"  -0.23837527632713318;
createNode animCurveTA -n "FKCurveShirt_01_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -8.4328147173867247 5 -23.082682437696874 
		9 0 14 29.529484441410244 18 -8.4328147173867247;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  0.89777690172195435;
	setAttr -s 5 ".kiy[4]"  0.44045045971870422;
	setAttr -s 5 ".kox[4]"  0.89777690172195435;
	setAttr -s 5 ".koy[4]"  0.44045045971870422;
createNode animCurveTA -n "FKCurveShirt_07_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 41.281228824251627 5 31.717493190946488 
		9 2.8928266319236964 14 11.384200867225292 18 41.281228824251627;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  0.70657241344451904;
	setAttr -s 5 ".kiy[4]"  -0.70764076709747314;
	setAttr -s 5 ".kox[4]"  0.70657241344451904;
	setAttr -s 5 ".koy[4]"  -0.70764076709747314;
createNode animCurveTA -n "FKCurveShirt_07_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 25.395879473281262 5 9.4033831796268466 
		9 16.935051297630697 14 7.83463702153285 18 25.395879473281262;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  0.51267075538635254;
	setAttr -s 5 ".kiy[4]"  -0.85858529806137085;
	setAttr -s 5 ".kox[4]"  0.51267075538635254;
	setAttr -s 5 ".koy[4]"  -0.85858529806137085;
createNode animCurveTA -n "FKCurveShirt_07_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.412060511524269 5 -5.5084585841514793 
		9 0.40688891459661564 14 1.5721857694377861 18 1.412060511524269;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  0.80972009897232056;
	setAttr -s 5 ".kiy[4]"  -0.58681637048721313;
	setAttr -s 5 ".kox[4]"  0.80972009897232056;
	setAttr -s 5 ".koy[4]"  -0.58681637048721313;
createNode animCurveTA -n "FKCurveBackA_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.30296546961098586 9 -0.13954805603039269 
		18 -0.30296546961098586;
createNode animCurveTA -n "FKCurveBackA_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -6.0075410145026638 9 6.0000000000000009 
		18 -6.0075410145026638;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "FKCurveBackA_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 4.3544237315987795 9 4.3403584633280996 
		18 4.3544237315987795;
createNode animCurveTA -n "FKCurveBackB1_M_rotateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -2.556942269326465 9 -2.6974421100891233 
		18 -2.556942269326465;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[0:2]"  1 1 1;
	setAttr -s 3 ".kiy[0:2]"  0 0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode animCurveTA -n "FKCurveBackB1_M_rotateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.039274060735877712 9 -3.491767184944631 
		18 0.039274060735877712;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[0:2]"  1 1 1;
	setAttr -s 3 ".kiy[0:2]"  0 0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode animCurveTA -n "FKCurveBackB1_M_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.351 5 -5.957 9 -0.351 14 5.957036952812512 
		18 0.351;
	setAttr -s 5 ".kit[1:4]"  3 1 3 1;
	setAttr -s 5 ".kot[1:4]"  3 1 3 1;
	setAttr -s 5 ".kix[0:4]"  0.69738298654556274 1 0.69124317169189453 
		1 0.70318573713302612;
	setAttr -s 5 ".kiy[0:4]"  -0.71669864654541016 0 0.72262227535247803 
		0 -0.71100622415542603;
	setAttr -s 5 ".kox[0:4]"  0.69738340377807617 1 0.69124341011047363 
		1 0.70318609476089478;
	setAttr -s 5 ".koy[0:4]"  -0.71669834852218628 0 0.7226220965385437 
		0 -0.7110058069229126;
createNode animCurveTA -n "FKCurveBackB_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 9 0 14 0 18 0;
createNode animCurveTA -n "FKCurveBackB_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.079491639660714875 9 0.079491639660714875 
		14 0.079491639660714875 18 0.079491639660714875;
createNode animCurveTA -n "FKCurveBackB_M_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.74600000000000011 5 -4.495 9 -0.74600000000000011 
		14 4.495 18 0.74600000000000011;
	setAttr -s 5 ".kit[1:4]"  3 1 3 1;
	setAttr -s 5 ".kot[1:4]"  3 1 3 1;
	setAttr -s 5 ".kix[0:4]"  0.79951506853103638 1 0.84845513105392456 
		1 0.8346443772315979;
	setAttr -s 5 ".kiy[0:4]"  -0.60064613819122314 0 0.52926731109619141 
		0 -0.5507892370223999;
	setAttr -s 5 ".kox[0:4]"  0.79951506853103638 1 0.84845507144927979 
		1 0.82765889167785645;
	setAttr -s 5 ".koy[0:4]"  -0.60064613819122314 0 0.52926748991012573 
		0 -0.56123137474060059;
createNode animCurveTA -n "FKCurveCap_03_L_rotateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 15.902198973523115 5 -6.1767756271874346 
		9 17.633094599746727 12 45.145033168496838 14 13.821775382030808 18 15.902198973523115;
	setAttr -s 6 ".kit[1:5]"  10 1 10 1 1;
	setAttr -s 6 ".kot[1:5]"  10 1 10 1 1;
	setAttr -s 6 ".kix[0:5]"  0.53962016105651855 0.9949679970741272 
		0.14614582061767578 0.92875808477401733 0.32996264100074768 0.56112885475158691;
	setAttr -s 6 ".kiy[0:5]"  -0.84190863370895386 0.10019270330667496 
		0.98926311731338501 -0.37068635225296021 -0.94399404525756836 -0.8277285099029541;
	setAttr -s 6 ".kox[0:5]"  0.56335818767547607 0.9949679970741272 
		0.1461457759141922 0.92875808477401733 0.32996261119842529 0.56112921237945557;
	setAttr -s 6 ".koy[0:5]"  -0.82621276378631592 0.10019270330667496 
		0.98926305770874023 -0.37068635225296021 -0.94399404525756836 -0.82772821187973022;
createNode animCurveTA -n "FKCurveCap_03_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -6.2120208622334324e-017 5 7.6779236910778144 
		12 20.172945202157393 14 16.020166174459177 18 -6.2120208622334324e-017;
	setAttr -s 5 ".kit[1:4]"  1 3 1 3;
	setAttr -s 5 ".kot[1:4]"  1 3 1 3;
	setAttr -s 5 ".kix[1:4]"  0.62518632411956787 1 0.38405978679656982 
		1;
	setAttr -s 5 ".kiy[1:4]"  0.78047561645507813 0 -0.92330825328826904 
		0;
	setAttr -s 5 ".kox[1:4]"  0.6251862645149231 1 0.38405987620353699 
		1;
	setAttr -s 5 ".koy[1:4]"  0.78047561645507813 0 -0.92330819368362427 
		0;
createNode animCurveTA -n "FKCurveCap_03_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -1.987846675914698e-016 5 -16.57986007571489 
		9 -16.871249269547256 12 9.2216348856982524 14 -17.499130360263816 18 -1.987846675914698e-016;
	setAttr -s 6 ".kit[1:5]"  1 1 3 3 3;
	setAttr -s 6 ".kot[1:5]"  1 1 3 3 3;
	setAttr -s 6 ".kix[1:5]"  0.61082267761230469 0.58506965637207031 
		1 1 1;
	setAttr -s 6 ".kiy[1:5]"  -0.79176747798919678 0.81098312139511108 
		0 0 0;
	setAttr -s 6 ".kox[1:5]"  0.61082255840301514 0.58506959676742554 
		1 1 1;
	setAttr -s 6 ".koy[1:5]"  -0.79176753759384155 0.81098306179046631 
		0 0 0;
createNode animCurveTA -n "FKCurveCap_02_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.5902773407317584e-015 5 0.46293837215696615 
		9 29.70480551636458 14 -0.26362371311356253 18 1.5902773407317584e-015;
	setAttr -s 5 ".kit[1:4]"  10 10 3 3;
	setAttr -s 5 ".kot[1:4]"  10 10 3 3;
createNode animCurveTA -n "FKCurveCap_02_L_rotateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -7.9513867036587919e-016 5 0 9 6.399731950951554 
		14 6.7629830939914486 18 -7.9513867036587919e-016;
	setAttr -s 5 ".kit[0:4]"  10 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  10 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  0.95724338293075562 0.97098052501678467 
		1;
	setAttr -s 5 ".kiy[2:4]"  0.28928375244140625 -0.2391587495803833 
		0;
	setAttr -s 5 ".kox[2:4]"  0.95724344253540039 0.97098052501678467 
		1;
	setAttr -s 5 ".koy[2:4]"  0.28928381204605103 -0.2391587495803833 
		0;
createNode animCurveTA -n "FKCurveCap_02_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.590277340731758e-015 5 0 9 2.4401644098235304 
		14 -1.0740612614922238 18 -1.590277340731758e-015;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "FKCurveCap_01_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 2.1077348468211259 5 6.9293817304955887 
		9 -3.3573475025333361 18 2.1077348468211259;
	setAttr -s 4 ".kit[0:3]"  1 10 10 1;
	setAttr -s 4 ".kot[0:3]"  1 10 10 1;
	setAttr -s 4 ".kix[0:3]"  0.82315683364868164 0.95299077033996582 
		0.98166012763977051 0.82681649923324585;
	setAttr -s 4 ".kiy[0:3]"  0.56781411170959473 -0.30299922823905945 
		-0.19063903391361237 0.56247186660766602;
	setAttr -s 4 ".kox[0:3]"  0.82315677404403687 0.95299077033996582 
		0.98166012763977051 0.82681643962860107;
	setAttr -s 4 ".koy[0:3]"  0.5678141713142395 -0.30299922823905945 
		-0.19063903391361237 0.56247186660766602;
createNode animCurveTA -n "FKCurveCap_01_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 8.2449678627530059 5 7.9805493164678953 
		9 6.7616039187184995 18 8.2449678627530059;
	setAttr -s 4 ".kit[1:3]"  1 10 10;
	setAttr -s 4 ".kot[1:3]"  1 10 10;
	setAttr -s 4 ".kix[1:3]"  0.9975665807723999 1 1;
	setAttr -s 4 ".kiy[1:3]"  -0.069720610976219177 0 0;
	setAttr -s 4 ".kox[1:3]"  0.9975665807723999 1 1;
	setAttr -s 4 ".koy[1:3]"  -0.069720618426799774 0 0;
createNode animCurveTA -n "FKCurveCap_01_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -4.8296625743685233 5 -3.4420787778693205 
		9 -4.4264324639117749 18 -4.8296625743685233;
	setAttr -s 4 ".kit[2:3]"  1 10;
	setAttr -s 4 ".kot[2:3]"  1 10;
	setAttr -s 4 ".kix[2:3]"  0.99755364656448364 1;
	setAttr -s 4 ".kiy[2:3]"  -0.069905117154121399 0;
	setAttr -s 4 ".kox[2:3]"  0.99755364656448364 1;
	setAttr -s 4 ".koy[2:3]"  -0.06990513950586319 0;
createNode animCurveTA -n "FKCurveCap_03_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 22.895244523512627 5 9.0586184616541363 
		9 33.093442191782124 12 36.692439803960006 14 33.081821388738803 18 22.895244523512627;
createNode animCurveTA -n "FKCurveCap_03_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 11.00163001767992 5 -2.1876097520883815 
		9 20.69314247578831 12 13.831324198663907 14 5.9537582668148543 18 11.00163001767992;
createNode animCurveTA -n "FKCurveCap_03_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -11.018840458648437 5 -25.522879599764845 
		9 -11.800484438957369 12 -10.165808556892946 14 -10.498308007243502 18 -11.018840458648437;
createNode animCurveTA -n "FKCurveCap_02_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -3.827365692918947 5 -29.602326287129525 
		9 23.436560883946846 12 -3.8820973059884527 14 -12.745526938777395 18 -3.827365692918947;
	setAttr -s 6 ".kit[3:5]"  10 3 3;
	setAttr -s 6 ".kot[3:5]"  10 3 3;
createNode animCurveTA -n "FKCurveCap_02_R_rotateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 2.8109558668301426 9 9.6505683506406612 
		14 -1.7864607513022384 18 0;
	setAttr -s 5 ".kit[3:4]"  10 1;
	setAttr -s 5 ".kot[3:4]"  10 1;
	setAttr -s 5 ".kix[0:4]"  0.99110722541809082 0.88438689708709717 
		0.93224740028381348 1 0.99101459980010986;
	setAttr -s 5 ".kiy[0:4]"  0.13306587934494019 0.46675461530685425 
		-0.3618215024471283 0 0.13375371694564819;
	setAttr -s 5 ".kox[0:4]"  0.99110722541809082 0.88438695669174194 
		0.93224745988845825 1 0.99101459980010986;
	setAttr -s 5 ".koy[0:4]"  0.13306589424610138 0.46675458550453186 
		-0.36182141304016113 0 0.13375371694564819;
createNode animCurveTA -n "FKCurveCap_02_R_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 5 5.8541884081759354 9 3.6334984854411627 
		18 0;
	setAttr -s 4 ".kit[0:3]"  3 1 1 3;
	setAttr -s 4 ".kot[0:3]"  3 1 1 3;
	setAttr -s 4 ".kix[1:3]"  0.99794381856918335 0.93122214078903198 
		1;
	setAttr -s 4 ".kiy[1:3]"  0.064095117151737213 -0.36445209383964539 
		0;
	setAttr -s 4 ".kox[1:3]"  0.99794381856918335 0.93122220039367676 
		1;
	setAttr -s 4 ".koy[1:3]"  0.064095109701156616 -0.36445203423500061 
		0;
createNode animCurveTA -n "FKCurveCap_01_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 6.1327690888623545 5 15.383597202068319 
		9 4.2738615731496283 18 6.1327690888623545;
	setAttr -s 4 ".kit[0:3]"  1 10 10 1;
	setAttr -s 4 ".kot[0:3]"  1 10 10 1;
	setAttr -s 4 ".kix[0:3]"  0.97501665353775024 0.99420291185379028 
		1 0.97475457191467285;
	setAttr -s 4 ".kiy[0:3]"  0.2221318781375885 -0.10751991719007492 
		0 0.22327908873558044;
	setAttr -s 4 ".kox[0:3]"  0.97501671314239502 0.99420291185379028 
		1 0.9728054404258728;
	setAttr -s 4 ".koy[0:3]"  0.22213189303874969 -0.10751991719007492 
		0 0.23162387311458588;
createNode animCurveTA -n "FKCurveCap_01_R_rotateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -2.4848083448933719e-017 5 5.3701061773251526 
		9 2.8324943424914029 18 -2.4848083448933719e-017;
	setAttr -s 4 ".kit[1:3]"  10 1 10;
	setAttr -s 4 ".kot[1:3]"  10 1 10;
	setAttr -s 4 ".kix[0:3]"  1 1 0.93677157163619995 1;
	setAttr -s 4 ".kiy[0:3]"  0 0 -0.34994158148765564 0;
	setAttr -s 4 ".kox[0:3]"  1 1 0.93677157163619995 1;
	setAttr -s 4 ".koy[0:3]"  0 0 -0.3499416708946228 0;
createNode animCurveTA -n "FKCurveCap_01_R_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -3.623693501247049 5 -7.3838589520551583 
		9 -4.0330398697305778 18 -3.623693501247049;
	setAttr -s 4 ".kit[1:3]"  10 1 1;
	setAttr -s 4 ".kot[1:3]"  10 1 1;
	setAttr -s 4 ".kix[0:3]"  0.99251919984817505 0.99971646070480347 
		0.98221194744110107 0.99243295192718506;
	setAttr -s 4 ".kiy[0:3]"  -0.1220889613032341 -0.023808052763342857 
		0.18777590990066528 -0.12278810143470764;
	setAttr -s 4 ".kox[0:3]"  0.99251919984817505 0.99971646070480347 
		0.9822118878364563 0.99243295192718506;
	setAttr -s 4 ".koy[0:3]"  -0.12208894640207291 -0.023808052763342857 
		0.18777582049369812 -0.12278812378644943;
createNode animCurveTA -n "FKCurveCap_07_L_rotateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 11.136357932486359 5 -15.00085762550011 
		9 28.059779897411005 14 28.650094743230397 18 11.136357932486359;
	setAttr -s 5 ".kit[0:4]"  10 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  10 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  0.36588117480278015 0.48417213559150696 
		0.40306344628334045;
	setAttr -s 5 ".kiy[2:4]"  0.93066161870956421 -0.87497276067733765 
		-0.9151720404624939;
	setAttr -s 5 ".kox[2:4]"  0.36588114500045776 0.48417216539382935 
		0.40306344628334045;
	setAttr -s 5 ".koy[2:4]"  0.93066155910491943 -0.87497276067733765 
		-0.9151720404624939;
createNode animCurveTA -n "FKCurveCap_07_L_rotateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -2.8546647754637262 5 2.8612359255764108 
		9 -8.4556436786839839 14 -25.510945314203951 18 -2.8546647754637262;
	setAttr -s 5 ".kix[0:4]"  0.4300839900970459 0.85806548595428467 
		0.38404512405395508 0.80887520313262939 0.42713147401809692;
	setAttr -s 5 ".kiy[0:4]"  0.90278887748718262 -0.51354038715362549 
		-0.92331433296203613 0.58798038959503174 0.90418952703475952;
	setAttr -s 5 ".kox[0:4]"  0.43008396029472351 0.85806548595428467 
		0.38404515385627747 0.80887526273727417 0.42713141441345215;
	setAttr -s 5 ".koy[0:4]"  0.90278893709182739 -0.51354038715362549 
		-0.92331433296203613 0.58798038959503174 0.9041895866394043;
createNode animCurveTA -n "FKCurveCap_07_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -6.3611093629270351e-015 5 -6.3792258574639797 
		9 14.835333325576405 14 -19.254343202589283 18 -6.3611093629270351e-015;
createNode animCurveTA -n "FKCurveCap_06_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 8.8589756697240585 5 -6.6734159105730235 
		9 20.814366551049861 14 -9.1652912820156445 18 8.8589756697240585;
createNode animCurveTA -n "FKCurveCap_06_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 5 0 14 0 18 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "FKCurveCap_06_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 5 0 14 0 18 0;
	setAttr -s 4 ".kit[3]"  1;
	setAttr -s 4 ".kot[3]"  1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "FKCurveCap_05_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.796218521909413 5 14.29519428653569 
		9 7.2596634980767396 18 0.796218521909413;
	setAttr -s 4 ".kit[1:3]"  10 1 3;
	setAttr -s 4 ".kot[1:3]"  10 1 3;
	setAttr -s 4 ".kix[2:3]"  0.68440240621566772 1;
	setAttr -s 4 ".kiy[2:3]"  -0.72910451889038086 0;
	setAttr -s 4 ".kox[2:3]"  0.6844024658203125 1;
	setAttr -s 4 ".koy[2:3]"  -0.72910451889038086 0;
createNode animCurveTA -n "FKCurveCap_05_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.11526965878421418 5 2.047327497037152 
		9 0.94200302047331386 18 0.11526965878421418;
	setAttr -s 4 ".kit[2:3]"  1 10;
	setAttr -s 4 ".kot[2:3]"  1 10;
	setAttr -s 4 ".kix[2:3]"  0.99143129587173462 1;
	setAttr -s 4 ".kiy[2:3]"  -0.13062949478626251 0;
	setAttr -s 4 ".kox[2:3]"  0.99143129587173462 1;
	setAttr -s 4 ".koy[2:3]"  -0.13062950968742371 0;
createNode animCurveTA -n "FKCurveCap_05_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -8.237029429272793 5 -7.9810680262409255 
		9 -8.1571599156975481 18 -8.237029429272793;
	setAttr -s 4 ".kit[2:3]"  1 10;
	setAttr -s 4 ".kot[2:3]"  1 10;
	setAttr -s 4 ".kix[2:3]"  0.99988967180252075 1;
	setAttr -s 4 ".kiy[2:3]"  -0.01485875528305769 0;
	setAttr -s 4 ".kox[2:3]"  0.99988967180252075 1;
	setAttr -s 4 ".koy[2:3]"  -0.014858774840831757 0;
createNode animCurveTA -n "FKCurveHair_02_L_rotateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 6.3611093629270351e-015 5 -7.1417580121906221 
		9 8.5601631744626392 14 8.8876717995984187 18 6.3611093629270351e-015;
	setAttr -s 5 ".kit[1:4]"  10 1 1 1;
	setAttr -s 5 ".kot[1:4]"  10 1 1 1;
	setAttr -s 5 ".kix[0:4]"  0.57003313302993774 0.89513850212097168 
		0.82683283090591431 0.84911024570465088 0.56678617000579834;
	setAttr -s 5 ".kiy[0:4]"  -0.82162171602249146 0.44578802585601807 
		0.56244772672653198 -0.52821564674377441 -0.82386493682861328;
	setAttr -s 5 ".kox[0:4]"  0.57003301382064819 0.89513850212097168 
		0.82683271169662476 0.84911024570465088 0.56678622961044312;
	setAttr -s 5 ".koy[0:4]"  -0.82162177562713623 0.44578802585601807 
		0.56244796514511108 -0.52821576595306396 -0.82386493682861328;
createNode animCurveTA -n "FKCurveHair_02_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -1.2424041724466865e-017 18 -1.2424041724466865e-017;
createNode animCurveTA -n "FKCurveHair_02_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -2.4848083448933725e-017 18 -2.4848083448933725e-017;
createNode animCurveTA -n "FKCurveHair_01_L_rotateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 8.2545049416514384 9 14.290794580194262 
		14 -5.2098111509735388 18 0;
	setAttr -s 5 ".kit[2:4]"  10 10 1;
	setAttr -s 5 ".kot[2:4]"  10 10 1;
	setAttr -s 5 ".kix[0:4]"  0.76078486442565918 0.70176815986633301 
		0.78723227977752686 0.76895016431808472 0.75885599851608276;
	setAttr -s 5 ".kiy[0:4]"  0.64900416135787964 0.7124055027961731 
		-0.61665648221969604 -0.63930875062942505 0.65125846862792969;
	setAttr -s 5 ".kox[0:4]"  0.76078486442565918 0.70176810026168823 
		0.78723227977752686 0.76895016431808472 0.75885599851608276;
	setAttr -s 5 ".koy[0:4]"  0.64900416135787964 0.7124055027961731 
		-0.61665648221969604 -0.63930875062942505 0.65125858783721924;
createNode animCurveTA -n "FKCurveHair_01_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.7655625192200634e-031 18 1.7655625192200634e-031;
createNode animCurveTA -n "FKCurveHair_01_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -1.4124500153760511e-030 18 -1.4124500153760511e-030;
createNode animCurveTA -n "FKCurveHead_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 18 0;
createNode animCurveTA -n "FKCurveHead_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -2.8357390842854793 9 2.836 18 -2.8357390842854793;
createNode animCurveTA -n "FKCurveHead_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 18 0;
createNode animCurveTA -n "FKCurveNeck_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 9 0 18 0;
createNode animCurveTA -n "FKCurveNeck_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.7760418856848397 9 -1.776 18 1.7760418856848397;
createNode animCurveTA -n "FKCurveNeck_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 9 0 18 0;
createNode animCurveTA -n "FKCurveChest_M_rotateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.0381 5 0.23061276341548317 9 0.038115789704317851 
		14 -0.23100000000000004 18 -0.0381;
	setAttr -s 5 ".kit[1:4]"  10 1 10 1;
	setAttr -s 5 ".kot[1:4]"  10 1 10 1;
	setAttr -s 5 ".kix[0:4]"  0.99915117025375366 1 0.99898600578308105 
		1 0.99913549423217773;
	setAttr -s 5 ".kiy[0:4]"  0.041194766759872437 0 -0.045022070407867432 
		0 0.041572045534849167;
	setAttr -s 5 ".kox[0:4]"  0.99915111064910889 1 0.99898600578308105 
		1 0.99909979104995728;
	setAttr -s 5 ".koy[0:4]"  0.041194755584001541 0 -0.045022066682577133 
		0 0.042422864586114883;
createNode animCurveTA -n "FKCurveChest_M_rotateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.302 5 -1.8154309890358231 9 -0.30150625808634912 
		14 1.815 18 0.302;
	setAttr -s 5 ".kit[1:4]"  3 1 3 1;
	setAttr -s 5 ".kot[1:4]"  3 1 3 1;
	setAttr -s 5 ".kix[0:4]"  0.94885343313217163 1 0.95550161600112915 
		1 0.94798296689987183;
	setAttr -s 5 ".kiy[0:4]"  -0.31571701169013977 0 0.29498589038848877 
		0 -0.31832119822502136;
	setAttr -s 5 ".kox[0:4]"  0.94885343313217163 1 0.95550161600112915 
		1 0.94667387008666992;
	setAttr -s 5 ".koy[0:4]"  -0.31571707129478455 0 0.29498600959777832 
		0 -0.32219350337982178;
createNode animCurveTA -n "FKCurveChest_M_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.202 5 -7.2410000000000005 9 -1.2018663489749795 
		14 7.2410000000000005 18 1.202;
	setAttr -s 5 ".kit[1:4]"  3 1 3 1;
	setAttr -s 5 ".kot[1:4]"  3 1 3 1;
	setAttr -s 5 ".kix[0:4]"  0.57373225688934326 1 0.42302709817886353 
		1 0.57001394033432007;
	setAttr -s 5 ".kiy[0:4]"  -0.81904292106628418 0 0.9061170220375061 
		0 -0.82163506746292114;
	setAttr -s 5 ".kox[0:4]"  0.57373231649398804 1 0.4230271577835083 
		1 0.57001405954360962;
	setAttr -s 5 ".koy[0:4]"  -0.81904292106628418 0 0.90611696243286133 
		0 -0.82163494825363159;
createNode animCurveTA -n "FKCurveShoulder_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -62.610009094684536 5 -71.357375351548399 
		9 -70.61773177096255 14 -70.523527690082872 18 -62.610009094684536;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "FKCurveShoulder_R_rotateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -3.2669833265029995 5 -6.3954891516828383 
		9 2.5576274034875195 14 14.702175018194565 18 -3.2669833265029995;
	setAttr -s 5 ".kit[1:4]"  3 1 3 1;
	setAttr -s 5 ".kot[1:4]"  3 1 3 1;
	setAttr -s 5 ".kix[0:4]"  0.82890427112579346 1 0.51691752672195435 
		1 0.82890427112579346;
	setAttr -s 5 ".kiy[0:4]"  -0.55939054489135742 0 0.85603523254394531 
		0 -0.55939054489135742;
	setAttr -s 5 ".kox[0:4]"  0.82890415191650391 1 0.5169176459312439 
		1 0.82890415191650391;
	setAttr -s 5 ".koy[0:4]"  -0.5593906044960022 0 0.85603517293930054 
		0 -0.5593906044960022;
createNode animCurveTA -n "FKCurveShoulder_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -18.329914167102327 5 -49.264455405416555 
		9 -18.443467791168789 14 26.135472237891435 18 -18.329914167102327;
	setAttr -s 5 ".kit[0:4]"  1 3 10 3 1;
	setAttr -s 5 ".kot[0:4]"  1 3 10 3 1;
	setAttr -s 5 ".kix[0:4]"  0.27644670009613037 1 0.22226518392562866 
		1 0.27644670009613037;
	setAttr -s 5 ".kiy[0:4]"  -0.9610292911529541 0 0.97498619556427002 
		0 -0.9610292911529541;
	setAttr -s 5 ".kox[0:4]"  0.27644667029380798 1 0.22226518392562866 
		1 0.27644667029380798;
	setAttr -s 5 ".koy[0:4]"  -0.96102935075759888 0 0.97498619556427002 
		0 -0.96102935075759888;
createNode animCurveTA -n "FKCurveElbow_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 44.335286850027742 5 39.220918594781025 
		9 20.115364898257674 14 44.889201090148326 18 44.335286850027742;
	setAttr -s 5 ".kit[1:4]"  1 3 3 1;
	setAttr -s 5 ".kot[1:4]"  1 3 3 1;
	setAttr -s 5 ".kix[1:4]"  0.6208343505859375 1 1 1;
	setAttr -s 5 ".kiy[1:4]"  -0.78394180536270142 0 0 0;
	setAttr -s 5 ".kox[1:4]"  0.62083441019058228 1 1 1;
	setAttr -s 5 ".koy[1:4]"  -0.78394174575805664 0 0 0;
createNode animCurveTA -n "FKCurveIndexFinger1_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  18 -25.171097216131383;
createNode animCurveTA -n "FKCurveIndexFinger1_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  18 0;
createNode animCurveTA -n "FKCurveIndexFinger1_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  18 0;
createNode animCurveTA -n "FKCurveThumbFinger3_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  18 -11.452300749195436;
createNode animCurveTA -n "FKCurveThumbFinger3_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  18 0;
createNode animCurveTA -n "FKCurveThumbFinger3_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  18 0;
createNode animCurveTA -n "FKCurveThumbFinger1_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  18 1.3685145537110779;
createNode animCurveTA -n "FKCurveThumbFinger1_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  18 0;
createNode animCurveTA -n "FKCurveThumbFinger1_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  18 0;
createNode animCurveTA -n "FKCurveWrist_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -2.5831525449186588 5 -1.6794652745414238 
		9 -2.6160442891637103 14 -2.3970870166341163 18 -2.5831525449186588;
	setAttr -s 5 ".kit[0:4]"  1 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  1 10 10 10 1;
	setAttr -s 5 ".kix[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".kiy[0:4]"  0 0 0 0 0;
	setAttr -s 5 ".kox[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".koy[0:4]"  0 0 0 0 0;
createNode animCurveTA -n "FKCurveWrist_R_rotateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -3.0269951705135409 5 3.7947552341798438 
		9 -2.4922942755574637 14 -11.341754746877758 18 -3.0269951705135409;
	setAttr -s 5 ".kit[1:4]"  10 1 10 1;
	setAttr -s 5 ".kot[1:4]"  10 1 10 1;
	setAttr -s 5 ".kix[0:4]"  0.6897730827331543 0.99951648712158203 
		0.56158709526062012 0.99951648712158203 0.6897730827331543;
	setAttr -s 5 ".kiy[0:4]"  0.72402554750442505 0.031092595309019089 
		-0.82741767168045044 -0.031092595309019089 0.72402554750442505;
	setAttr -s 5 ".kox[0:4]"  0.68977314233779907 0.99951648712158203 
		0.56158709526062012 0.99951648712158203 0.68977314233779907;
	setAttr -s 5 ".koy[0:4]"  0.72402560710906982 0.031092595309019089 
		-0.82741767168045044 -0.031092595309019089 0.72402560710906982;
createNode animCurveTA -n "FKCurveWrist_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -21.208576951746391 5 -19.416950767424904 
		9 -23.255082898507123 14 -14.368827686988011 18 -21.208576951746391;
	setAttr -s 5 ".kit[0:4]"  1 10 3 3 1;
	setAttr -s 5 ".kot[0:4]"  1 10 3 3 1;
	setAttr -s 5 ".kix[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".kiy[0:4]"  0 0 0 0 0;
	setAttr -s 5 ".kox[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".koy[0:4]"  0 0 0 0 0;
createNode lightLinker -n "lightLinker1";
	setAttr -s 11 ".lnk";
	setAttr -s 11 ".slnk";
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
	setAttr -s 11 ".st";
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
	setAttr -s 11 ".s";
select -ne :postProcessList1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -s 9 ".u";
select -ne :lightList1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
select -ne :defaultTextureList1;
	setAttr -s 9 ".tx";
select -ne :initialShadingGroup;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -av -k on ".nds";
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
connectAttr "runSource.cl" "clipLibrary1.sc[0]";
connectAttr "IKPoleVectorCurveLeg_L_translateZ.a" "clipLibrary1.cel[0].cev[16].cevr"
		;
connectAttr "IKPoleVectorCurveLeg_L_translateY.a" "clipLibrary1.cel[0].cev[17].cevr"
		;
connectAttr "IKPoleVectorCurveLeg_L_translateX.a" "clipLibrary1.cel[0].cev[18].cevr"
		;
connectAttr "IKCurveLeg_L_rotateZ.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "IKCurveLeg_L_rotateY.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "IKCurveLeg_L_rotateX.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "IKCurveLeg_L_translateZ.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "IKCurveLeg_L_translateY.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "IKCurveLeg_L_translateX.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "IKPoleVectorCurveLeg_R_translateZ.a" "clipLibrary1.cel[0].cev[33].cevr"
		;
connectAttr "IKPoleVectorCurveLeg_R_translateY.a" "clipLibrary1.cel[0].cev[34].cevr"
		;
connectAttr "IKPoleVectorCurveLeg_R_translateX.a" "clipLibrary1.cel[0].cev[35].cevr"
		;
connectAttr "IKCurveLeg_R_rotateZ.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "IKCurveLeg_R_rotateY.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "IKCurveLeg_R_rotateX.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "IKCurveLeg_R_translateZ.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "IKCurveLeg_R_translateY.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "IKCurveLeg_R_translateX.a" "clipLibrary1.cel[0].cev[48].cevr";
connectAttr "RootCurveRoot_M_rotateZ.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "RootCurveRoot_M_rotateY.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "RootCurveRoot_M_rotateX.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "RootCurveRoot_M_translateZ.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "RootCurveRoot_M_translateY.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "RootCurveRoot_M_translateX.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "FKCurveShirt_07_L_rotateZ.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "FKCurveShirt_07_L_rotateY.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "FKCurveShirt_07_L_rotateX.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "FKCurveShoulder_L_rotateZ.a" "clipLibrary1.cel[0].cev[67].cevr";
connectAttr "FKCurveShoulder_L_rotateY.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "FKCurveShoulder_L_rotateX.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "FKCurveElbow_L_rotateY.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "FKCurveWrist_L_rotateZ.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "FKCurveWrist_L_rotateY.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "FKCurveWrist_L_rotateX.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "FKCurveShirt_04_L_rotateZ.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "FKCurveShirt_04_L_rotateY.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "FKCurveShirt_04_L_rotateX.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "FKCurveShirt_02_L_rotateZ.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "FKCurveShirt_02_L_rotateY.a" "clipLibrary1.cel[0].cev[100].cevr";
connectAttr "FKCurveShirt_02_L_rotateX.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "FKCurveShirt_01_L_rotateZ.a" "clipLibrary1.cel[0].cev[102].cevr";
connectAttr "FKCurveShirt_01_L_rotateY.a" "clipLibrary1.cel[0].cev[103].cevr";
connectAttr "FKCurveShirt_01_L_rotateX.a" "clipLibrary1.cel[0].cev[104].cevr";
connectAttr "FKCurveShirt_07_R_rotateZ.a" "clipLibrary1.cel[0].cev[105].cevr";
connectAttr "FKCurveShirt_07_R_rotateY.a" "clipLibrary1.cel[0].cev[106].cevr";
connectAttr "FKCurveShirt_07_R_rotateX.a" "clipLibrary1.cel[0].cev[107].cevr";
connectAttr "FKCurveBackA_M_rotateZ.a" "clipLibrary1.cel[0].cev[112].cevr";
connectAttr "FKCurveBackA_M_rotateY.a" "clipLibrary1.cel[0].cev[113].cevr";
connectAttr "FKCurveBackA_M_rotateX.a" "clipLibrary1.cel[0].cev[114].cevr";
connectAttr "FKCurveBackB1_M_rotateZ.a" "clipLibrary1.cel[0].cev[115].cevr";
connectAttr "FKCurveBackB1_M_rotateY.a" "clipLibrary1.cel[0].cev[116].cevr";
connectAttr "FKCurveBackB1_M_rotateX.a" "clipLibrary1.cel[0].cev[117].cevr";
connectAttr "FKCurveBackB_M_rotateZ.a" "clipLibrary1.cel[0].cev[118].cevr";
connectAttr "FKCurveBackB_M_rotateY.a" "clipLibrary1.cel[0].cev[119].cevr";
connectAttr "FKCurveBackB_M_rotateX.a" "clipLibrary1.cel[0].cev[120].cevr";
connectAttr "FKCurveCap_03_L_rotateZ.a" "clipLibrary1.cel[0].cev[121].cevr";
connectAttr "FKCurveCap_03_L_rotateY.a" "clipLibrary1.cel[0].cev[122].cevr";
connectAttr "FKCurveCap_03_L_rotateX.a" "clipLibrary1.cel[0].cev[123].cevr";
connectAttr "FKCurveCap_02_L_rotateZ.a" "clipLibrary1.cel[0].cev[124].cevr";
connectAttr "FKCurveCap_02_L_rotateY.a" "clipLibrary1.cel[0].cev[125].cevr";
connectAttr "FKCurveCap_02_L_rotateX.a" "clipLibrary1.cel[0].cev[126].cevr";
connectAttr "FKCurveCap_01_L_rotateZ.a" "clipLibrary1.cel[0].cev[127].cevr";
connectAttr "FKCurveCap_01_L_rotateY.a" "clipLibrary1.cel[0].cev[128].cevr";
connectAttr "FKCurveCap_01_L_rotateX.a" "clipLibrary1.cel[0].cev[129].cevr";
connectAttr "FKCurveCap_03_R_rotateZ.a" "clipLibrary1.cel[0].cev[133].cevr";
connectAttr "FKCurveCap_03_R_rotateY.a" "clipLibrary1.cel[0].cev[134].cevr";
connectAttr "FKCurveCap_03_R_rotateX.a" "clipLibrary1.cel[0].cev[135].cevr";
connectAttr "FKCurveCap_02_R_rotateZ.a" "clipLibrary1.cel[0].cev[136].cevr";
connectAttr "FKCurveCap_02_R_rotateY.a" "clipLibrary1.cel[0].cev[137].cevr";
connectAttr "FKCurveCap_02_R_rotateX.a" "clipLibrary1.cel[0].cev[138].cevr";
connectAttr "FKCurveCap_01_R_rotateZ.a" "clipLibrary1.cel[0].cev[139].cevr";
connectAttr "FKCurveCap_01_R_rotateY.a" "clipLibrary1.cel[0].cev[140].cevr";
connectAttr "FKCurveCap_01_R_rotateX.a" "clipLibrary1.cel[0].cev[141].cevr";
connectAttr "FKCurveCap_07_L_rotateZ.a" "clipLibrary1.cel[0].cev[142].cevr";
connectAttr "FKCurveCap_07_L_rotateY.a" "clipLibrary1.cel[0].cev[143].cevr";
connectAttr "FKCurveCap_07_L_rotateX.a" "clipLibrary1.cel[0].cev[144].cevr";
connectAttr "FKCurveCap_06_L_rotateZ.a" "clipLibrary1.cel[0].cev[145].cevr";
connectAttr "FKCurveCap_06_L_rotateY.a" "clipLibrary1.cel[0].cev[146].cevr";
connectAttr "FKCurveCap_06_L_rotateX.a" "clipLibrary1.cel[0].cev[147].cevr";
connectAttr "FKCurveCap_05_L_rotateZ.a" "clipLibrary1.cel[0].cev[148].cevr";
connectAttr "FKCurveCap_05_L_rotateY.a" "clipLibrary1.cel[0].cev[149].cevr";
connectAttr "FKCurveCap_05_L_rotateX.a" "clipLibrary1.cel[0].cev[150].cevr";
connectAttr "FKCurveHair_02_L_rotateZ.a" "clipLibrary1.cel[0].cev[157].cevr";
connectAttr "FKCurveHair_02_L_rotateY.a" "clipLibrary1.cel[0].cev[158].cevr";
connectAttr "FKCurveHair_02_L_rotateX.a" "clipLibrary1.cel[0].cev[159].cevr";
connectAttr "FKCurveHair_01_L_rotateZ.a" "clipLibrary1.cel[0].cev[160].cevr";
connectAttr "FKCurveHair_01_L_rotateY.a" "clipLibrary1.cel[0].cev[161].cevr";
connectAttr "FKCurveHair_01_L_rotateX.a" "clipLibrary1.cel[0].cev[162].cevr";
connectAttr "FKCurveHead_M_rotateZ.a" "clipLibrary1.cel[0].cev[170].cevr";
connectAttr "FKCurveHead_M_rotateY.a" "clipLibrary1.cel[0].cev[171].cevr";
connectAttr "FKCurveHead_M_rotateX.a" "clipLibrary1.cel[0].cev[172].cevr";
connectAttr "FKCurveNeck_M_rotateZ.a" "clipLibrary1.cel[0].cev[173].cevr";
connectAttr "FKCurveNeck_M_rotateY.a" "clipLibrary1.cel[0].cev[174].cevr";
connectAttr "FKCurveNeck_M_rotateX.a" "clipLibrary1.cel[0].cev[175].cevr";
connectAttr "FKCurveChest_M_rotateZ.a" "clipLibrary1.cel[0].cev[179].cevr";
connectAttr "FKCurveChest_M_rotateY.a" "clipLibrary1.cel[0].cev[180].cevr";
connectAttr "FKCurveChest_M_rotateX.a" "clipLibrary1.cel[0].cev[181].cevr";
connectAttr "FKCurveShoulder_R_rotateZ.a" "clipLibrary1.cel[0].cev[183].cevr";
connectAttr "FKCurveShoulder_R_rotateY.a" "clipLibrary1.cel[0].cev[184].cevr";
connectAttr "FKCurveShoulder_R_rotateX.a" "clipLibrary1.cel[0].cev[185].cevr";
connectAttr "FKCurveElbow_R_rotateY.a" "clipLibrary1.cel[0].cev[186].cevr";
connectAttr "FKCurveIndexFinger1_R_rotateZ.a" "clipLibrary1.cel[0].cev[193].cevr"
		;
connectAttr "FKCurveIndexFinger1_R_rotateY.a" "clipLibrary1.cel[0].cev[194].cevr"
		;
connectAttr "FKCurveIndexFinger1_R_rotateX.a" "clipLibrary1.cel[0].cev[195].cevr"
		;
connectAttr "FKCurveThumbFinger3_R_rotateZ.a" "clipLibrary1.cel[0].cev[196].cevr"
		;
connectAttr "FKCurveThumbFinger3_R_rotateY.a" "clipLibrary1.cel[0].cev[197].cevr"
		;
connectAttr "FKCurveThumbFinger3_R_rotateX.a" "clipLibrary1.cel[0].cev[198].cevr"
		;
connectAttr "FKCurveThumbFinger1_R_rotateZ.a" "clipLibrary1.cel[0].cev[202].cevr"
		;
connectAttr "FKCurveThumbFinger1_R_rotateY.a" "clipLibrary1.cel[0].cev[203].cevr"
		;
connectAttr "FKCurveThumbFinger1_R_rotateX.a" "clipLibrary1.cel[0].cev[204].cevr"
		;
connectAttr "FKCurveWrist_R_rotateZ.a" "clipLibrary1.cel[0].cev[209].cevr";
connectAttr "FKCurveWrist_R_rotateY.a" "clipLibrary1.cel[0].cev[210].cevr";
connectAttr "FKCurveWrist_R_rotateX.a" "clipLibrary1.cel[0].cev[211].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of run.ma
