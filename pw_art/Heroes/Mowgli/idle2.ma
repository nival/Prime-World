//Maya ASCII 2008 scene
//Name: maugli_idle2.ma
//Last modified: Thu, Feb 05, 2009 04:52:12 PM
//Codeset: 1251
requires maya "2008";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Unlimited 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200802250025-718075";
fileInfo "osv" "Microsoft Windows XP Service Pack 3 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 432 ".cel[0].cev";
	setAttr ".cd[0].cm" -type "characterMapping" 432 "AimCurveEye_Right1_M.follow" 
		0 1 "AimCurveEye_Right1_M.cross" 0 2 "AimCurveEye_Right1_M.translateY" 
		1 2 "AimCurveEye_Right1_M.translateX" 1 3 "FKIKControlCurveArm_L.IKVis" 
		0 3 "FKIKControlCurveArm_L.FKVis" 0 4 "FKIKControlCurveArm_L.FKIKBlend" 
		0 5 "FKIKControlCurveLeg_L.IKVis" 0 6 "FKIKControlCurveLeg_L.FKVis" 
		0 7 "FKIKControlCurveLeg_L.FKIKBlend" 0 8 "FKIKControlCurveArm_R.IKVis" 
		0 9 "FKIKControlCurveArm_R.FKVis" 0 10 "FKIKControlCurveArm_R.FKIKBlend" 
		0 11 "FKIKControlCurveLeg_R.IKVis" 0 12 "FKIKControlCurveLeg_R.FKVis" 
		0 13 "FKIKControlCurveLeg_R.FKIKBlend" 0 14 "IKPoleVectorCurveArm_L.follow" 
		0 15 "IKPoleVectorCurveArm_L.translateZ" 1 4 "IKPoleVectorCurveArm_L.translateY" 
		1 5 "IKPoleVectorCurveArm_L.translateX" 1 6 "IKPoleVectorExtraArm_L.translateZ" 
		1 7 "IKPoleVectorExtraArm_L.translateY" 1 8 "IKPoleVectorExtraArm_L.translateX" 
		1 9 "IKCurveArm_L.antiPop" 0 16 "IKCurveArm_L.stretchy" 0 
		17 "IKCurveArm_L.follow" 0 18 "IKCurveArm_L.rotateZ" 2 1 "IKCurveArm_L.rotateY" 
		2 2 "IKCurveArm_L.rotateX" 2 3 "IKCurveArm_L.translateZ" 1 
		10 "IKCurveArm_L.translateY" 1 11 "IKCurveArm_L.translateX" 1 12 "IKExtraArm_L.rotateZ" 
		2 4 "IKExtraArm_L.rotateY" 2 5 "IKExtraArm_L.rotateX" 2 
		6 "IKExtraArm_L.translateZ" 1 13 "IKExtraArm_L.translateY" 1 14 "IKExtraArm_L.translateX" 
		1 15 "IKPoleVectorCurveLeg_L.follow" 0 19 "IKPoleVectorCurveLeg_L.translateZ" 
		1 16 "IKPoleVectorCurveLeg_L.translateY" 1 17 "IKPoleVectorCurveLeg_L.translateX" 
		1 18 "IKPoleVectorExtraLeg_L.translateZ" 1 19 "IKPoleVectorExtraLeg_L.translateY" 
		1 20 "IKPoleVectorExtraLeg_L.translateX" 1 21 "IKCurveLeg_L.antiPop" 
		0 20 "IKCurveLeg_L.stretchy" 0 21 "IKCurveLeg_L.swivel" 0 
		22 "IKCurveLeg_L.rotateZ" 2 7 "IKCurveLeg_L.rotateY" 2 8 "IKCurveLeg_L.rotateX" 
		2 9 "IKCurveLeg_L.translateZ" 1 22 "IKCurveLeg_L.translateY" 1 
		23 "IKCurveLeg_L.translateX" 1 24 "IKExtraLeg_L.rotateZ" 2 10 "IKExtraLeg_L.rotateY" 
		2 11 "IKExtraLeg_L.rotateX" 2 12 "IKExtraLeg_L.translateZ" 1 
		25 "IKExtraLeg_L.translateY" 1 26 "IKExtraLeg_L.translateX" 1 27 "IKPoleVectorCurveArm_R.follow" 
		0 23 "IKPoleVectorCurveArm_R.translateZ" 1 28 "IKPoleVectorCurveArm_R.translateY" 
		1 29 "IKPoleVectorCurveArm_R.translateX" 1 30 "IKPoleVectorExtraArm_R.translateZ" 
		1 31 "IKPoleVectorExtraArm_R.translateY" 1 32 "IKPoleVectorExtraArm_R.translateX" 
		1 33 "IKCurveArm_R.antiPop" 0 24 "IKCurveArm_R.stretchy" 0 
		25 "IKCurveArm_R.follow" 0 26 "IKCurveArm_R.rotateZ" 2 13 "IKCurveArm_R.rotateY" 
		2 14 "IKCurveArm_R.rotateX" 2 15 "IKCurveArm_R.translateZ" 1 
		34 "IKCurveArm_R.translateY" 1 35 "IKCurveArm_R.translateX" 1 36 "IKExtraArm_R.rotateZ" 
		2 16 "IKExtraArm_R.rotateY" 2 17 "IKExtraArm_R.rotateX" 2 
		18 "IKExtraArm_R.translateZ" 1 37 "IKExtraArm_R.translateY" 1 38 "IKExtraArm_R.translateX" 
		1 39 "IKPoleVectorCurveLeg_R.follow" 0 27 "IKPoleVectorCurveLeg_R.translateZ" 
		1 40 "IKPoleVectorCurveLeg_R.translateY" 1 41 "IKPoleVectorCurveLeg_R.translateX" 
		1 42 "IKPoleVectorExtraLeg_R.translateZ" 1 43 "IKPoleVectorExtraLeg_R.translateY" 
		1 44 "IKPoleVectorExtraLeg_R.translateX" 1 45 "IKCurveLeg_R.antiPop" 
		0 28 "IKCurveLeg_R.stretchy" 0 29 "IKCurveLeg_R.swivel" 0 
		30 "IKCurveLeg_R.rotateZ" 2 19 "IKCurveLeg_R.rotateY" 2 20 "IKCurveLeg_R.rotateX" 
		2 21 "IKCurveLeg_R.translateZ" 1 46 "IKCurveLeg_R.translateY" 1 
		47 "IKCurveLeg_R.translateX" 1 48 "IKExtraLeg_R.rotateZ" 2 22 "IKExtraLeg_R.rotateY" 
		2 23 "IKExtraLeg_R.rotateX" 2 24 "IKExtraLeg_R.translateZ" 1 
		49 "IKExtraLeg_R.translateY" 1 50 "IKExtraLeg_R.translateX" 1 51 "FKCurveTooth1_L.scaleZ" 
		0 31 "FKCurveTooth1_L.scaleY" 0 32 "FKCurveTooth1_L.scaleX" 0 
		33 "FKCurveTooth1_L.rotateZ" 2 25 "FKCurveTooth1_L.rotateY" 2 26 "FKCurveTooth1_L.rotateX" 
		2 27 "FKCurveTooth1_L.translateZ" 1 52 "FKCurveTooth1_L.translateY" 
		1 53 "FKCurveTooth1_L.translateX" 1 54 "FKExtraTooth1_L.scaleZ" 
		0 34 "FKExtraTooth1_L.scaleY" 0 35 "FKExtraTooth1_L.scaleX" 0 
		36 "FKExtraTooth1_L.rotateZ" 2 28 "FKExtraTooth1_L.rotateY" 2 29 "FKExtraTooth1_L.rotateX" 
		2 30 "FKExtraTooth1_L.translateZ" 1 55 "FKExtraTooth1_L.translateY" 
		1 56 "FKExtraTooth1_L.translateX" 1 57 "FKExtraPen1_L.rotateZ" 
		2 34 "FKExtraPen1_L.rotateY" 2 35 "FKExtraPen1_L.rotateX" 2 
		36 "FKExtraPen1_R.rotateZ" 2 40 "FKExtraPen1_R.rotateY" 2 41 "FKExtraPen1_R.rotateX" 
		2 42 "FKCurveHair1_L.scaleZ" 0 43 "FKCurveHair1_L.scaleY" 0 
		44 "FKCurveHair1_L.scaleX" 0 45 "FKCurveHair1_L.rotateZ" 2 43 "FKCurveHair1_L.rotateY" 
		2 44 "FKCurveHair1_L.rotateX" 2 45 "FKExtraHair1_L.rotateZ" 2 
		46 "FKExtraHair1_L.rotateY" 2 47 "FKExtraHair1_L.rotateX" 2 48 "FKCurveHead1_M.scaleZ" 
		0 46 "FKCurveHead1_M.scaleY" 0 47 "FKCurveHead1_M.scaleX" 0 
		48 "FKCurveHead1_M.rotateZ" 2 49 "FKCurveHead1_M.rotateY" 2 50 "FKCurveHead1_M.rotateX" 
		2 51 "FKExtraHead1_M.rotateZ" 2 52 "FKExtraHead1_M.rotateY" 2 
		53 "FKExtraHead1_M.rotateX" 2 54 "FKCurveNeck1_M.scaleZ" 0 49 "FKCurveNeck1_M.scaleY" 
		0 50 "FKCurveNeck1_M.scaleX" 0 51 "FKCurveNeck1_M.rotateZ" 2 
		55 "FKCurveNeck1_M.rotateY" 2 56 "FKCurveNeck1_M.rotateX" 2 57 "FKExtraNeck1_M.rotateZ" 
		2 58 "FKExtraNeck1_M.rotateY" 2 59 "FKExtraNeck1_M.rotateX" 2 
		60 "FKCurveSpine3_M.scaleZ" 0 52 "FKCurveSpine3_M.scaleY" 0 53 "FKCurveSpine3_M.scaleX" 
		0 54 "FKCurveSpine3_M.rotateZ" 2 61 "FKCurveSpine3_M.rotateY" 2 
		62 "FKCurveSpine3_M.rotateX" 2 63 "FKExtraSpine3_M.rotateZ" 2 64 "FKExtraSpine3_M.rotateY" 
		2 65 "FKExtraSpine3_M.rotateX" 2 66 "FKCurveSpine4_L.scaleZ" 0 
		55 "FKCurveSpine4_L.scaleY" 0 56 "FKCurveSpine4_L.scaleX" 0 57 "FKCurveSpine4_L.rotateZ" 
		2 67 "FKCurveSpine4_L.rotateY" 2 68 "FKCurveSpine4_L.rotateX" 2 
		69 "FKExtraSpine4_L.rotateZ" 2 70 "FKExtraSpine4_L.rotateY" 2 71 "FKExtraSpine4_L.rotateX" 
		2 72 "FKCurvePelvis1_M.scaleZ" 0 58 "FKCurvePelvis1_M.scaleY" 0 
		59 "FKCurvePelvis1_M.scaleX" 0 60 "FKCurvePelvis1_M.rotateZ" 2 
		73 "FKCurvePelvis1_M.rotateY" 2 74 "FKCurvePelvis1_M.rotateX" 2 
		75 "FKExtraPelvis1_M.rotateZ" 2 76 "FKExtraPelvis1_M.rotateY" 2 
		77 "FKExtraPelvis1_M.rotateX" 2 78 "RootCurveRoot1_M.CenterBtwFeet" 
		0 61 "RootCurveRoot1_M.rotateZ" 2 79 "RootCurveRoot1_M.rotateY" 
		2 80 "RootCurveRoot1_M.rotateX" 2 81 "RootCurveRoot1_M.translateZ" 
		1 58 "RootCurveRoot1_M.translateY" 1 59 "RootCurveRoot1_M.translateX" 
		1 60 "RootExtraRoot1_M.rotateZ" 2 82 "RootExtraRoot1_M.rotateY" 
		2 83 "RootExtraRoot1_M.rotateX" 2 84 "RootExtraRoot1_M.translateZ" 
		1 61 "RootExtraRoot1_M.translateY" 1 62 "RootExtraRoot1_M.translateX" 
		1 63 "FKCurveR_Clavicle1_L.scaleZ" 0 62 "FKCurveR_Clavicle1_L.scaleY" 
		0 63 "FKCurveR_Clavicle1_L.scaleX" 0 64 "FKCurveR_Clavicle1_L.rotateZ" 
		2 85 "FKCurveR_Clavicle1_L.rotateY" 2 86 "FKCurveR_Clavicle1_L.rotateX" 
		2 87 "FKExtraR_Clavicle1_L.rotateZ" 2 88 "FKExtraR_Clavicle1_L.rotateY" 
		2 89 "FKExtraR_Clavicle1_L.rotateX" 2 90 "FKCurveR_Shoulder1_L.scaleZ" 
		0 65 "FKCurveR_Shoulder1_L.scaleY" 0 66 "FKCurveR_Shoulder1_L.scaleX" 
		0 67 "FKCurveR_Shoulder1_L.rotateY" 2 91 "FKExtraR_Shoulder1_L.rotateZ" 
		2 92 "FKExtraR_Shoulder1_L.rotateY" 2 93 "FKExtraR_Shoulder1_L.rotateX" 
		2 94 "FKCurveR_Elbow1_L.scaleZ" 0 68 "FKCurveR_Elbow1_L.scaleY" 
		0 69 "FKCurveR_Elbow1_L.scaleX" 0 70 "FKCurveR_Elbow1_L.rotateY" 
		2 95 "FKExtraR_Elbow1_L.rotateZ" 2 96 "FKExtraR_Elbow1_L.rotateY" 
		2 97 "FKExtraR_Elbow1_L.rotateX" 2 98 "FKCurveDevice3_L.scaleZ" 
		0 71 "FKCurveDevice3_L.scaleY" 0 72 "FKCurveDevice3_L.scaleX" 0 
		73 "FKCurveDevice3_L.rotateZ" 2 99 "FKCurveDevice3_L.rotateY" 2 
		100 "FKCurveDevice3_L.rotateX" 2 101 "FKCurveDevice3_L.translateZ" 1 
		64 "FKCurveDevice3_L.translateY" 1 65 "FKCurveDevice3_L.translateX" 
		1 66 "FKExtraDevice3_L.scaleZ" 0 74 "FKExtraDevice3_L.scaleY" 0 
		75 "FKExtraDevice3_L.scaleX" 0 76 "FKExtraDevice3_L.rotateZ" 2 
		102 "FKExtraDevice3_L.rotateY" 2 103 "FKExtraDevice3_L.rotateX" 2 
		104 "FKExtraDevice3_L.translateZ" 1 67 "FKExtraDevice3_L.translateY" 
		1 68 "FKExtraDevice3_L.translateX" 1 69 "FKCurveR_Thumb5_L.scaleZ" 
		0 77 "FKCurveR_Thumb5_L.scaleY" 0 78 "FKCurveR_Thumb5_L.scaleX" 
		0 79 "FKCurveR_Thumb5_L.rotateZ" 2 105 "FKCurveR_Thumb5_L.rotateY" 
		2 106 "FKCurveR_Thumb5_L.rotateX" 2 107 "FKExtraR_Thumb5_L.rotateZ" 
		2 108 "FKExtraR_Thumb5_L.rotateY" 2 109 "FKExtraR_Thumb5_L.rotateX" 
		2 110 "FKCurveR_Thumb6_L.scaleZ" 0 80 "FKCurveR_Thumb6_L.scaleY" 
		0 81 "FKCurveR_Thumb6_L.scaleX" 0 82 "FKCurveR_Thumb6_L.rotateZ" 
		2 111 "FKCurveR_Thumb6_L.rotateY" 2 112 "FKCurveR_Thumb6_L.rotateX" 
		2 113 "FKExtraR_Thumb6_L.rotateZ" 2 114 "FKExtraR_Thumb6_L.rotateY" 
		2 115 "FKExtraR_Thumb6_L.rotateX" 2 116 "FKCurveR_Middle5_L.scaleZ" 
		0 83 "FKCurveR_Middle5_L.scaleY" 0 84 "FKCurveR_Middle5_L.scaleX" 
		0 85 "FKCurveR_Middle5_L.rotateZ" 2 117 "FKCurveR_Middle5_L.rotateY" 
		2 118 "FKCurveR_Middle5_L.rotateX" 2 119 "FKExtraR_Middle5_L.rotateZ" 
		2 120 "FKExtraR_Middle5_L.rotateY" 2 121 "FKExtraR_Middle5_L.rotateX" 
		2 122 "FKCurveR_Middle6_L.scaleZ" 0 86 "FKCurveR_Middle6_L.scaleY" 
		0 87 "FKCurveR_Middle6_L.scaleX" 0 88 "FKCurveR_Middle6_L.rotateZ" 
		2 123 "FKCurveR_Middle6_L.rotateY" 2 124 "FKCurveR_Middle6_L.rotateX" 
		2 125 "FKExtraR_Middle6_L.rotateZ" 2 126 "FKExtraR_Middle6_L.rotateY" 
		2 127 "FKExtraR_Middle6_L.rotateX" 2 128 "FKCurveR_Wrist1_L.scaleZ" 
		0 89 "FKCurveR_Wrist1_L.scaleY" 0 90 "FKCurveR_Wrist1_L.scaleX" 
		0 91 "FKCurveR_Wrist1_L.rotateZ" 2 129 "FKCurveR_Wrist1_L.rotateY" 
		2 130 "FKCurveR_Wrist1_L.rotateX" 2 131 "FKExtraR_Wrist1_L.rotateZ" 
		2 132 "FKExtraR_Wrist1_L.rotateY" 2 133 "FKExtraR_Wrist1_L.rotateX" 
		2 134 "FKCurveR_Hip1_L.scaleZ" 0 92 "FKCurveR_Hip1_L.scaleY" 0 
		93 "FKCurveR_Hip1_L.scaleX" 0 94 "FKCurveR_Hip1_L.rotateZ" 2 135 "FKCurveR_Hip1_L.rotateY" 
		2 136 "FKCurveR_Hip1_L.rotateX" 2 137 "FKExtraR_Hip1_L.rotateZ" 2 
		138 "FKExtraR_Hip1_L.rotateY" 2 139 "FKExtraR_Hip1_L.rotateX" 2 140 "FKCurveR_Knee1_L.scaleZ" 
		0 95 "FKCurveR_Knee1_L.scaleY" 0 96 "FKCurveR_Knee1_L.scaleX" 0 
		97 "FKCurveR_Knee1_L.rotateZ" 2 141 "FKExtraR_Knee1_L.rotateZ" 2 
		142 "FKExtraR_Knee1_L.rotateY" 2 143 "FKExtraR_Knee1_L.rotateX" 2 
		144 "FKCurveR_Ankle1_L.scaleZ" 0 98 "FKCurveR_Ankle1_L.scaleY" 0 
		99 "FKCurveR_Ankle1_L.scaleX" 0 100 "FKCurveR_Ankle1_L.rotateZ" 2 
		145 "FKCurveR_Ankle1_L.rotateY" 2 146 "FKCurveR_Ankle1_L.rotateX" 2 
		147 "FKExtraR_Ankle1_L.rotateZ" 2 148 "FKExtraR_Ankle1_L.rotateY" 2 
		149 "FKExtraR_Ankle1_L.rotateX" 2 150 "FKCurveR_Ball1_L.scaleZ" 0 
		101 "FKCurveR_Ball1_L.scaleY" 0 102 "FKCurveR_Ball1_L.scaleX" 0 103 "FKCurveR_Ball1_L.rotateZ" 
		2 151 "FKCurveR_Ball1_L.rotateY" 2 152 "FKCurveR_Ball1_L.rotateX" 
		2 153 "FKExtraR_Ball1_L.rotateZ" 2 154 "FKExtraR_Ball1_L.rotateY" 
		2 155 "FKExtraR_Ball1_L.rotateX" 2 156 "FKCurveR_Clavicle1_R.scaleZ" 
		0 104 "FKCurveR_Clavicle1_R.scaleY" 0 105 "FKCurveR_Clavicle1_R.scaleX" 
		0 106 "FKCurveR_Clavicle1_R.rotateZ" 2 157 "FKCurveR_Clavicle1_R.rotateY" 
		2 158 "FKCurveR_Clavicle1_R.rotateX" 2 159 "FKExtraR_Clavicle1_R.rotateZ" 
		2 160 "FKExtraR_Clavicle1_R.rotateY" 2 161 "FKExtraR_Clavicle1_R.rotateX" 
		2 162 "FKCurveR_Shoulder1_R.scaleZ" 0 107 "FKCurveR_Shoulder1_R.scaleY" 
		0 108 "FKCurveR_Shoulder1_R.scaleX" 0 109 "FKCurveR_Shoulder1_R.rotateY" 
		2 163 "FKExtraR_Shoulder1_R.rotateZ" 2 164 "FKExtraR_Shoulder1_R.rotateY" 
		2 165 "FKExtraR_Shoulder1_R.rotateX" 2 166 "FKCurveR_Elbow1_R.scaleZ" 
		0 110 "FKCurveR_Elbow1_R.scaleY" 0 111 "FKCurveR_Elbow1_R.scaleX" 
		0 112 "FKCurveR_Elbow1_R.rotateY" 2 167 "FKExtraR_Elbow1_R.rotateZ" 
		2 168 "FKExtraR_Elbow1_R.rotateY" 2 169 "FKExtraR_Elbow1_R.rotateX" 
		2 170 "FKCurveR_Thumb5_R.scaleZ" 0 113 "FKCurveR_Thumb5_R.scaleY" 
		0 114 "FKCurveR_Thumb5_R.scaleX" 0 115 "FKCurveR_Thumb5_R.rotateZ" 
		2 171 "FKCurveR_Thumb5_R.rotateY" 2 172 "FKCurveR_Thumb5_R.rotateX" 
		2 173 "FKExtraR_Thumb5_R.rotateZ" 2 174 "FKExtraR_Thumb5_R.rotateY" 
		2 175 "FKExtraR_Thumb5_R.rotateX" 2 176 "FKCurveR_Thumb6_R.scaleZ" 
		0 116 "FKCurveR_Thumb6_R.scaleY" 0 117 "FKCurveR_Thumb6_R.scaleX" 
		0 118 "FKCurveR_Thumb6_R.rotateZ" 2 177 "FKCurveR_Thumb6_R.rotateY" 
		2 178 "FKCurveR_Thumb6_R.rotateX" 2 179 "FKExtraR_Thumb6_R.rotateZ" 
		2 180 "FKExtraR_Thumb6_R.rotateY" 2 181 "FKExtraR_Thumb6_R.rotateX" 
		2 182 "FKCurveR_Middle5_R.scaleZ" 0 119 "FKCurveR_Middle5_R.scaleY" 
		0 120 "FKCurveR_Middle5_R.scaleX" 0 121 "FKCurveR_Middle5_R.rotateZ" 
		2 183 "FKCurveR_Middle5_R.rotateY" 2 184 "FKCurveR_Middle5_R.rotateX" 
		2 185 "FKExtraR_Middle5_R.rotateZ" 2 186 "FKExtraR_Middle5_R.rotateY" 
		2 187 "FKExtraR_Middle5_R.rotateX" 2 188 "FKCurveR_Middle6_R.scaleZ" 
		0 122 "FKCurveR_Middle6_R.scaleY" 0 123 "FKCurveR_Middle6_R.scaleX" 
		0 124 "FKCurveR_Middle6_R.rotateZ" 2 189 "FKCurveR_Middle6_R.rotateY" 
		2 190 "FKCurveR_Middle6_R.rotateX" 2 191 "FKExtraR_Middle6_R.rotateZ" 
		2 192 "FKExtraR_Middle6_R.rotateY" 2 193 "FKExtraR_Middle6_R.rotateX" 
		2 194 "FKCurveR_Wrist1_R.scaleZ" 0 125 "FKCurveR_Wrist1_R.scaleY" 
		0 126 "FKCurveR_Wrist1_R.scaleX" 0 127 "FKCurveR_Wrist1_R.rotateZ" 
		2 195 "FKCurveR_Wrist1_R.rotateY" 2 196 "FKCurveR_Wrist1_R.rotateX" 
		2 197 "FKExtraR_Wrist1_R.rotateZ" 2 198 "FKExtraR_Wrist1_R.rotateY" 
		2 199 "FKExtraR_Wrist1_R.rotateX" 2 200 "FKCurveR_Hip1_R.scaleZ" 
		0 128 "FKCurveR_Hip1_R.scaleY" 0 129 "FKCurveR_Hip1_R.scaleX" 0 
		130 "FKCurveR_Hip1_R.rotateZ" 2 201 "FKCurveR_Hip1_R.rotateY" 2 202 "FKCurveR_Hip1_R.rotateX" 
		2 203 "FKExtraR_Hip1_R.rotateZ" 2 204 "FKExtraR_Hip1_R.rotateY" 2 
		205 "FKExtraR_Hip1_R.rotateX" 2 206 "FKCurveR_Knee1_R.scaleZ" 0 131 "FKCurveR_Knee1_R.scaleY" 
		0 132 "FKCurveR_Knee1_R.scaleX" 0 133 "FKCurveR_Knee1_R.rotateZ" 
		2 207 "FKExtraR_Knee1_R.rotateZ" 2 208 "FKExtraR_Knee1_R.rotateY" 
		2 209 "FKExtraR_Knee1_R.rotateX" 2 210 "FKCurveR_Ankle1_R.scaleZ" 
		0 134 "FKCurveR_Ankle1_R.scaleY" 0 135 "FKCurveR_Ankle1_R.scaleX" 
		0 136 "FKCurveR_Ankle1_R.rotateZ" 2 211 "FKCurveR_Ankle1_R.rotateY" 
		2 212 "FKCurveR_Ankle1_R.rotateX" 2 213 "FKExtraR_Ankle1_R.rotateZ" 
		2 214 "FKExtraR_Ankle1_R.rotateY" 2 215 "FKExtraR_Ankle1_R.rotateX" 
		2 216 "FKCurveR_Ball1_R.scaleZ" 0 137 "FKCurveR_Ball1_R.scaleY" 0 
		138 "FKCurveR_Ball1_R.scaleX" 0 139 "FKCurveR_Ball1_R.rotateZ" 2 
		217 "FKCurveR_Ball1_R.rotateY" 2 218 "FKCurveR_Ball1_R.rotateX" 2 
		219 "FKExtraR_Ball1_R.rotateZ" 2 220 "FKExtraR_Ball1_R.rotateY" 2 
		221 "FKExtraR_Ball1_R.rotateX" 2 222 "All.scaleZ" 0 140 "All.scaleY" 
		0 141 "All.scaleX" 0 142 "All.rotateZ" 2 223 "All.rotateY" 
		2 224 "All.rotateX" 2 225 "All.translateZ" 1 70 "All.translateY" 
		1 71 "All.translateX" 1 72 "All.visibility" 0 143 "AimCurveEye_Right1_M.translateZ" 
		1 73 "FKCurveR_Shoulder1_R.rotateZ" 2 226 "FKCurveR_Shoulder1_R.rotateX" 
		2 227 "FKCurveR_Shoulder1_L.rotateZ" 2 228 "FKCurveR_Shoulder1_L.rotateX" 
		2 229  ;
	setAttr ".cd[0].cim" -type "Int32Array" 432 0 1 3 4 5
		 6 7 8 9 10 11 12 13 14 15 16 17
		 18 19 20 21 22 23 24 25 26 27 28 29
		 30 31 32 33 34 35 36 37 38 39 40 41
		 42 43 44 45 46 47 48 49 50 51 52 53
		 54 55 56 57 58 59 60 61 62 63 64 65
		 66 67 68 69 70 71 72 73 74 75 76 77
		 78 79 80 81 82 83 84 85 86 87 88 89
		 90 91 92 93 94 95 96 97 98 99 100 101
		 102 103 104 105 106 107 108 109 110 111 112 113
		 114 115 116 117 118 119 120 121 122 129 130 131
		 138 139 140 141 142 143 144 145 146 147 148 149
		 150 151 152 153 154 155 156 157 158 159 160 161
		 162 163 164 165 166 167 168 169 170 171 172 173
		 174 175 176 177 178 179 180 181 182 183 184 185
		 186 187 188 189 190 191 192 193 194 195 196 197
		 198 199 200 201 202 203 204 205 206 207 208 209
		 210 211 212 213 214 215 216 217 218 219 220 221
		 222 223 224 225 226 227 228 229 230 231 232 233
		 234 235 236 237 238 239 240 241 242 243 244 245
		 246 247 248 249 250 251 252 253 254 255 256 257
		 258 259 260 261 262 263 264 265 266 267 268 269
		 270 271 272 273 274 275 276 277 278 279 280 281
		 282 283 284 285 286 287 288 289 290 291 292 293
		 294 295 296 297 298 299 300 301 302 303 304 305
		 306 307 308 309 310 311 312 313 314 315 316 317
		 318 319 320 321 322 323 324 325 326 327 328 329
		 330 331 332 333 334 335 336 337 338 339 340 341
		 342 343 344 345 346 347 348 349 350 351 352 353
		 354 355 356 357 358 359 360 361 362 363 364 365
		 366 367 368 369 370 371 372 373 374 375 376 377
		 378 379 380 381 382 383 384 385 386 387 388 389
		 390 391 392 393 394 395 396 397 398 399 400 401
		 402 403 404 405 406 407 408 409 410 411 412 413
		 414 415 416 417 418 419 420 421 422 423 424 425
		 426 427 428 429 430 431 432 433 434 435 436 437
		 438 439 2 123 124 125 126 ;
createNode animClip -n "maugli_idle2Source";
	setAttr ".ihi" 0;
	setAttr -s 432 ".ac";
	setAttr ".ac[0:126]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[129:131]" yes yes yes;
	setAttr ".ac[138:439]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes no no no yes yes yes no no no no;
	setAttr ".se" 70;
	setAttr ".ci" no;
createNode animCurveTU -n "char_AimCurveEye_Right1_M_follow";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 70 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTU -n "char_AimCurveEye_Right1_M_cross";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 70 1;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTL -n "char_AimCurveEye_Right1_M_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 3.4299179804087934 70 3.4299179804087934;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTL -n "char_AimCurveEye_Right1_M_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.81831860840024984 70 -0.81831860840024984;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTL -n "char_AimCurveEye_Right1_M_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.059018783840309119 70 0.059018783840309119;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTU -n "char_FKIKControlCurveArm_L_IKVis";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKIKControlCurveArm_L_FKVis";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKIKControlCurveArm_L_FKIKBlend";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKIKControlCurveLeg_L_IKVis";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKIKControlCurveLeg_L_FKVis";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKIKControlCurveLeg_L_FKIKBlend";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 10 32 10 70 10;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKIKControlCurveArm_R_IKVis";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKIKControlCurveArm_R_FKVis";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKIKControlCurveArm_R_FKIKBlend";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKIKControlCurveLeg_R_IKVis";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKIKControlCurveLeg_R_FKVis";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKIKControlCurveLeg_R_FKIKBlend";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 10 32 10 70 10;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_IKPoleVectorCurveArm_L_follow";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKPoleVectorCurveArm_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKPoleVectorCurveArm_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKPoleVectorCurveArm_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKPoleVectorExtraArm_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKPoleVectorExtraArm_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKPoleVectorExtraArm_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_IKCurveArm_L_antiPop";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_IKCurveArm_L_stretchy";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_IKCurveArm_L_follow";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_IKCurveArm_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_IKCurveArm_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_IKCurveArm_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKCurveArm_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKCurveArm_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKCurveArm_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_IKExtraArm_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_IKExtraArm_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_IKExtraArm_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKExtraArm_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKExtraArm_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKExtraArm_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_IKPoleVectorCurveLeg_L_follow";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 10 32 10 70 10;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKPoleVectorExtraLeg_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKPoleVectorExtraLeg_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKPoleVectorExtraLeg_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_IKCurveLeg_L_antiPop";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_IKCurveLeg_L_stretchy";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_IKCurveLeg_L_swivel";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_IKCurveLeg_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_IKCurveLeg_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 43.567069197048298 32 43.567069197048298 
		70 43.567069197048298;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_IKCurveLeg_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKCurveLeg_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.28844199405395621 32 -0.28844199405395621 
		70 -0.28844199405395621;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKCurveLeg_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKCurveLeg_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.087756482507145378 32 0.087756482507145378 
		70 0.087756482507145378;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_IKExtraLeg_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_IKExtraLeg_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_IKExtraLeg_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKExtraLeg_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKExtraLeg_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKExtraLeg_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_IKPoleVectorCurveArm_R_follow";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKPoleVectorCurveArm_R_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKPoleVectorCurveArm_R_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKPoleVectorCurveArm_R_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKPoleVectorExtraArm_R_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKPoleVectorExtraArm_R_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKPoleVectorExtraArm_R_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_IKCurveArm_R_antiPop";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_IKCurveArm_R_stretchy";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_IKCurveArm_R_follow";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_IKCurveArm_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_IKCurveArm_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_IKCurveArm_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKCurveArm_R_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKCurveArm_R_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKCurveArm_R_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_IKExtraArm_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_IKExtraArm_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_IKExtraArm_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKExtraArm_R_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKExtraArm_R_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKExtraArm_R_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_IKPoleVectorCurveLeg_R_follow";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 10 32 10 70 10;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_R_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_R_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_R_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKPoleVectorExtraLeg_R_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKPoleVectorExtraLeg_R_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKPoleVectorExtraLeg_R_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_IKCurveLeg_R_antiPop";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_IKCurveLeg_R_stretchy";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_IKCurveLeg_R_swivel";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_IKCurveLeg_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_IKCurveLeg_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_IKCurveLeg_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKCurveLeg_R_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.33022172654533777 32 0.33022172654533777 
		70 0.33022172654533777;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKCurveLeg_R_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKCurveLeg_R_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.13911956167322667 32 -0.13911956167322667 
		70 -0.13911956167322667;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_IKExtraLeg_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_IKExtraLeg_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_IKExtraLeg_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKExtraLeg_R_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKExtraLeg_R_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_IKExtraLeg_R_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveTooth1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveTooth1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveTooth1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveTooth1_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -27.541549434058677 10 -23.340501257315196 
		19 -33.376110699140135 32 -16.27656000291276 47 -25.824057909880402 57 -40.504650297541509 
		64 -37.092514766348437 70 -27.541549434058677;
	setAttr -s 8 ".kit[0:7]"  3 10 10 3 1 10 10 1;
	setAttr -s 8 ".kot[0:7]"  3 10 10 3 1 10 10 1;
	setAttr -s 8 ".kix[4:7]"  1 0.94471889734268188 0.88644903898239136 
		1;
	setAttr -s 8 ".kiy[4:7]"  0 -0.3278813362121582 0.46282625198364258 
		0;
	setAttr -s 8 ".kox[4:7]"  1 0.94471889734268188 0.88644903898239136 
		1;
	setAttr -s 8 ".koy[4:7]"  0 -0.3278813362121582 0.46282625198364258 
		0;
createNode animCurveTA -n "char_FKCurveTooth1_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 8.4599709196312922 10 -1.3721555117885309 
		19 -3.2060004325575941 32 3.9281847813405282 47 -6.3882740562099976 57 8.5500369254014057 
		64 1.3881780211525614 70 8.4599709196312922;
	setAttr -s 8 ".kit[0:7]"  3 10 10 3 1 10 10 1;
	setAttr -s 8 ".kot[0:7]"  3 10 10 3 1 10 10 1;
	setAttr -s 8 ".kix[4:7]"  1 0.97249448299407959 0.99999344348907471 
		1;
	setAttr -s 8 ".kiy[4:7]"  0 0.23292617499828339 -0.0036275498569011688 
		0;
	setAttr -s 8 ".kox[4:7]"  1 0.97249448299407959 0.99999344348907471 
		1;
	setAttr -s 8 ".koy[4:7]"  0 0.23292617499828339 -0.0036275498569011688 
		0;
createNode animCurveTA -n "char_FKCurveTooth1_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 6.8137435045968227 10 2.9295498524351387 
		19 0.46711481072848948 32 5.9878059673093897 47 0.24393444827094243 57 4.0840145667914616 
		64 2.3421255595334247 70 6.8137435045968227;
	setAttr -s 8 ".kit[0:7]"  3 10 10 3 1 10 10 1;
	setAttr -s 8 ".kot[0:7]"  3 10 10 3 1 10 10 1;
	setAttr -s 8 ".kix[4:7]"  1 1 1 1;
	setAttr -s 8 ".kiy[4:7]"  0 0 0 0;
	setAttr -s 8 ".kox[4:7]"  1 1 1 1;
	setAttr -s 8 ".koy[4:7]"  0 0 0 0;
createNode animCurveTL -n "char_FKCurveTooth1_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.028863465787140358 19 -0.018990020173155462 
		32 -0.028863465787140358 47 -0.0061489346798207804 57 -0.025866201416544783 70 -0.028863465787140358;
	setAttr -s 6 ".kit[1:5]"  10 3 1 10 1;
	setAttr -s 6 ".kot[1:5]"  10 3 1 10 1;
	setAttr -s 6 ".kix[3:5]"  1 1 1;
	setAttr -s 6 ".kiy[3:5]"  0 0 0;
	setAttr -s 6 ".kox[3:5]"  1 1 1;
	setAttr -s 6 ".koy[3:5]"  0 0 0;
createNode animCurveTL -n "char_FKCurveTooth1_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.023775464972591611 19 -0.027635716517206296 
		32 -0.023775464972591611 47 -0.032656235396650128 57 -0.027906052317775133 70 -0.023775464972591611;
	setAttr -s 6 ".kit[1:5]"  10 3 1 10 1;
	setAttr -s 6 ".kot[1:5]"  10 3 1 10 1;
	setAttr -s 6 ".kix[3:5]"  1 1 1;
	setAttr -s 6 ".kiy[3:5]"  0 0 0;
	setAttr -s 6 ".kox[3:5]"  1 1 1;
	setAttr -s 6 ".koy[3:5]"  0 0 0;
createNode animCurveTL -n "char_FKCurveTooth1_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.052162964274260919 19 -0.054631752490862079 
		32 -0.052162964274260919 47 -0.057842578963578729 57 -0.084112223049794127 70 -0.052162964274260919;
	setAttr -s 6 ".kit[1:5]"  10 3 1 10 1;
	setAttr -s 6 ".kot[1:5]"  10 3 1 10 1;
	setAttr -s 6 ".kix[3:5]"  1 1 1;
	setAttr -s 6 ".kiy[3:5]"  0 0 0;
	setAttr -s 6 ".kox[3:5]"  1 1 1;
	setAttr -s 6 ".koy[3:5]"  0 0 0;
createNode animCurveTU -n "char_FKExtraTooth1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKExtraTooth1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKExtraTooth1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraTooth1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraTooth1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraTooth1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_FKExtraTooth1_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_FKExtraTooth1_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_FKExtraTooth1_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "FKCurveR_Shoulder1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -36.986337964869008 13 -55.167073092905717 
		32 -65.680240759346887 47 -51.843015010899158 70 -36.986337964869008;
	setAttr -s 5 ".kit[1:4]"  10 3 10 1;
	setAttr -s 5 ".kot[1:4]"  10 3 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "FKCurveR_Shoulder1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 15.957960813366103 13 8.0567311063309592 
		32 -39.443734122415378 47 -27.206961721579827 70 15.957960813366103;
	setAttr -s 5 ".kit[1:4]"  10 3 1 1;
	setAttr -s 5 ".kot[1:4]"  10 3 1 1;
	setAttr -s 5 ".kix[3:4]"  0.97567659616470337 1;
	setAttr -s 5 ".kiy[3:4]"  0.21921516954898834 0;
	setAttr -s 5 ".kox[3:4]"  0.97567659616470337 1;
	setAttr -s 5 ".koy[3:4]"  0.21921513974666595 0;
createNode animCurveTA -n "FKCurveR_Shoulder1_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -60.970082317325229 13 -64.335535839286493 
		32 -47.487400713297731 47 -53.009961978089919 70 -60.970082317325229;
	setAttr -s 5 ".kit[0:4]"  1 10 3 10 1;
	setAttr -s 5 ".kot[0:4]"  1 10 3 10 1;
	setAttr -s 5 ".kix[0:4]"  0.98322552442550659 0.97651934623718262 
		1 0.98317772150039673 0.99594390392303467;
	setAttr -s 5 ".kiy[0:4]"  -0.18239429593086243 0.21542978286743164 
		0 -0.18265154957771301 -0.089976757764816284;
	setAttr -s 5 ".kox[0:4]"  0.98322546482086182 0.97651934623718262 
		1 0.98317772150039673 0.99594384431838989;
	setAttr -s 5 ".koy[0:4]"  -0.1823943555355072 0.21542978286743164 
		0 -0.18265154957771301 -0.089976765215396881;
createNode animCurveTA -n "FKCurveR_Shoulder1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -5.1174438057844904 13 -16.590039179734546 
		32 -52.45650681093764 47 -31.498182368708569 70 -5.1174438057844904;
	setAttr -s 5 ".kit[1:4]"  10 3 1 1;
	setAttr -s 5 ".kot[1:4]"  10 3 1 1;
	setAttr -s 5 ".kix[3:4]"  0.78622525930404663 1;
	setAttr -s 5 ".kiy[3:4]"  0.61794006824493408 0;
	setAttr -s 5 ".kox[3:4]"  0.78622519969940186 1;
	setAttr -s 5 ".koy[3:4]"  0.61794018745422363 0;
createNode animCurveTA -n "char_FKExtraPen1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraPen1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraPen1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraPen1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraPen1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraPen1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveHair1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveHair1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveHair1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveHair1_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 30.524599611915377 7 36.310982403441642 
		11 38.58487321850955 22 34.381205104264332 32 28.276990886028251 46 22.44952932367255 
		56 43.086100856052816 70 30.524599611915377;
	setAttr -s 8 ".kit[0:7]"  3 9 10 10 3 10 10 1;
	setAttr -s 8 ".kot[0:7]"  3 9 10 10 3 10 10 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTA -n "char_FKCurveHair1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -20.226445302148342 7 -20.263860108477445 
		11 -15.836173988415752 22 -18.972038183463532 32 -19.84881396769876 46 -19.559186522181836 
		56 -19.816992333565416 70 -20.226445302148342;
	setAttr -s 8 ".kit[1:7]"  10 3 9 3 10 9 1;
	setAttr -s 8 ".kot[1:7]"  10 3 9 3 10 9 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTA -n "char_FKCurveHair1_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 17.701770262088139 7 8.4582733723251806 
		11 0.79579383683909288 22 23.728066887956331 32 4.2575314391085932 46 25.778098635714063 
		56 2.9117632583197675 70 17.701770262088139;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 3 10 10 1;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 3 10 10 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTA -n "char_FKExtraHair1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraHair1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraHair1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveHead1_M_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 9 1 31 1 70 1;
	setAttr -s 4 ".kit[1:3]"  10 3 1;
	setAttr -s 4 ".kot[1:3]"  10 3 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTU -n "char_FKCurveHead1_M_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 9 1 31 1 70 1;
	setAttr -s 4 ".kit[1:3]"  10 3 1;
	setAttr -s 4 ".kot[1:3]"  10 3 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTU -n "char_FKCurveHead1_M_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 9 1 31 1 70 1;
	setAttr -s 4 ".kit[1:3]"  10 3 1;
	setAttr -s 4 ".kot[1:3]"  10 3 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTA -n "char_FKCurveHead1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 19.649599090973453 9 18.77448405815608 
		31 15.619810250443541 49 14.759616308268679 59 17.60273880375409 70 19.649599090973453;
	setAttr -s 6 ".kit[0:5]"  1 3 9 3 9 1;
	setAttr -s 6 ".kot[0:5]"  1 3 9 3 9 1;
	setAttr -s 6 ".kix[0:5]"  0.99307829141616821 1 0.99862182140350342 
		1 0.99264925718307495 0.99469786882400513;
	setAttr -s 6 ".kiy[0:5]"  0.11745449900627136 0 -0.052482068538665771 
		0 0.12102707475423813 0.10284031182527542;
	setAttr -s 6 ".kox[0:5]"  0.99307829141616821 1 0.99862182140350342 
		1 0.99264925718307495 0.99469786882400513;
	setAttr -s 6 ".koy[0:5]"  0.11745445430278778 0 -0.052482068538665771 
		0 0.12102707475423813 0.10284031182527542;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTA -n "char_FKCurveHead1_M_rotateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -30.214171376615486 9 -28.743128586266131 
		31 -25.614734943492159 49 -25.1039933910074 59 -28.610291128865811 70 -30.214171376615486;
	setAttr -s 6 ".kit[0:5]"  3 1 1 10 9 1;
	setAttr -s 6 ".kot[0:5]"  3 1 1 10 9 1;
	setAttr -s 6 ".kix[1:5]"  0.99161803722381592 0.99995291233062744 
		1 0.99198043346405029 1;
	setAttr -s 6 ".kiy[1:5]"  0.12920424342155457 0.0097074862569570541 
		0 -0.12639167904853821 0;
	setAttr -s 6 ".kox[1:5]"  0.99161803722381592 0.99995291233062744 
		1 0.99198043346405029 1;
	setAttr -s 6 ".koy[1:5]"  0.12920422852039337 0.0097074871882796288 
		0 -0.12639167904853821 0;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTA -n "char_FKCurveHead1_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -39.886477028299176 9 -39.488362850065933 
		31 -30.42166906269339 49 -18.451889866436996 59 -29.6148114643984 70 -39.886477028299176;
	setAttr -s 6 ".kit[0:5]"  1 10 9 3 10 1;
	setAttr -s 6 ".kot[0:5]"  1 10 9 3 10 1;
	setAttr -s 6 ".kix[0:5]"  0.92745733261108398 1 0.9641149640083313 
		1 0.88194942474365234 0.86362272500991821;
	setAttr -s 6 ".kiy[0:5]"  -0.37392899394035339 0 0.2654852569103241 
		0 -0.47134420275688171 -0.5041387677192688;
	setAttr -s 6 ".kox[0:5]"  0.92745733261108398 1 0.9641149640083313 
		1 0.88194942474365234 0.86362266540527344;
	setAttr -s 6 ".koy[0:5]"  -0.37392899394035339 0 0.2654852569103241 
		0 -0.47134420275688171 -0.5041387677192688;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTA -n "char_FKExtraHead1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraHead1_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraHead1_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveNeck1_M_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 9 1 31 1 70 1;
	setAttr -s 4 ".kit[1:3]"  10 3 1;
	setAttr -s 4 ".kot[1:3]"  10 3 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTU -n "char_FKCurveNeck1_M_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 9 1 31 1 70 1;
	setAttr -s 4 ".kit[1:3]"  10 3 1;
	setAttr -s 4 ".kot[1:3]"  10 3 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTU -n "char_FKCurveNeck1_M_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 9 1 31 1 70 1;
	setAttr -s 4 ".kit[1:3]"  10 3 1;
	setAttr -s 4 ".kot[1:3]"  10 3 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTA -n "char_FKCurveNeck1_M_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 16.978679829010165 9 13.952003425871615 
		31 0.23930250883218021 49 15.222416664659047 59 19.320874933567779 70 16.978679829010165;
	setAttr -s 6 ".kit[1:5]"  1 3 9 10 1;
	setAttr -s 6 ".kot[1:5]"  1 3 9 10 1;
	setAttr -s 6 ".kix[1:5]"  0.98729723691940308 1 0.94183683395385742 
		1 0.94007635116577148;
	setAttr -s 6 ".kiy[1:5]"  -0.15888442099094391 0 0.33607050776481628 
		0 -0.34096404910087585;
	setAttr -s 6 ".kox[1:5]"  0.98729723691940308 1 0.94183683395385742 
		1 0.94007635116577148;
	setAttr -s 6 ".koy[1:5]"  -0.15888439118862152 0 0.33607050776481628 
		0 -0.34096401929855347;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTA -n "char_FKCurveNeck1_M_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -13.679820867901928 9 -13.696093316564793 
		31 0.088617888208387882 49 -13.449747721477399 59 -15.304824596454559 70 -13.679820867901928;
	setAttr -s 6 ".kit[1:5]"  1 3 9 10 1;
	setAttr -s 6 ".kot[1:5]"  1 3 9 10 1;
	setAttr -s 6 ".kix[1:5]"  0.97081607580184937 1 0.96097826957702637 
		1 0.97106254100799561;
	setAttr -s 6 ".kiy[1:5]"  0.23982524871826172 0 -0.27662399411201477 
		0 0.23882564902305603;
	setAttr -s 6 ".kox[1:5]"  0.97081607580184937 1 0.96097826957702637 
		1 0.97106248140335083;
	setAttr -s 6 ".koy[1:5]"  0.23982523381710052 0 -0.27662399411201477 
		0 0.23882564902305603;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTA -n "char_FKCurveNeck1_M_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -6.4072944111053358 9 -4.02548198270103 
		31 6.5900556567536954 49 -2.8163302190369874 59 -7.7485334237039787 70 -6.4072944111053358;
	setAttr -s 6 ".kit[2:5]"  3 9 10 1;
	setAttr -s 6 ".kot[2:5]"  3 9 10 1;
	setAttr -s 6 ".kix[0:5]"  0.95438891649246216 0.9667009711265564 
		1 0.96588188409805298 1 0.96592515707015991;
	setAttr -s 6 ".kiy[0:5]"  0.29856649041175842 0.25590872764587402 
		0 -0.25898283720016479 0 0.25882157683372498;
	setAttr -s 6 ".kox[0:5]"  0.95438891649246216 0.96670103073120117 
		1 0.96588188409805298 1 0.96592515707015991;
	setAttr -s 6 ".koy[0:5]"  0.29856640100479126 0.25590860843658447 
		0 -0.25898283720016479 0 0.25882163643836975;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTA -n "char_FKExtraNeck1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraNeck1_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraNeck1_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveSpine3_M_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 70 1;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr -s 2 ".kox[1]"  1;
	setAttr -s 2 ".koy[1]"  0;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTU -n "char_FKCurveSpine3_M_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 70 1;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr -s 2 ".kox[1]"  1;
	setAttr -s 2 ".koy[1]"  0;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTU -n "char_FKCurveSpine3_M_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 70 1;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr -s 2 ".kox[1]"  1;
	setAttr -s 2 ".koy[1]"  0;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTA -n "char_FKCurveSpine3_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -4.1759924717065973 12 -7.1556594086889529 
		32 4.2103709211070095 47 3.5487471408851179 70 -4.1759924717065973;
	setAttr -s 5 ".kit[0:4]"  1 3 10 3 9;
	setAttr -s 5 ".kot[0:4]"  1 3 10 3 9;
	setAttr -s 5 ".kix[0:4]"  0.96234452724456787 1 1 1 0.98488712310791016;
	setAttr -s 5 ".kiy[0:4]"  -0.27183276414871216 0 0 0 -0.17319732904434204;
	setAttr -s 5 ".kox[0:4]"  0.96234452724456787 1 1 1 0.98488712310791016;
	setAttr -s 5 ".koy[0:4]"  -0.27183279395103455 0 0 0 -0.17319732904434204;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTA -n "char_FKCurveSpine3_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.201 12 -5.7064919135893177 32 -1.035929450379605 
		47 3.3089341967920896 70 -1.201;
	setAttr -s 5 ".kit[0:4]"  1 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  1 10 10 10 1;
	setAttr -s 5 ".kix[0:4]"  0.98182344436645508 0.99999642372131348 
		0.99102717638015747 0.99999749660491943 0.98354965448379517;
	setAttr -s 5 ".kiy[0:4]"  -0.18979661166667938 0.00270095095038414 
		0.13366028666496277 -0.002274487866088748 -0.18063817918300629;
	setAttr -s 5 ".kox[0:4]"  0.98182344436645508 0.99999642372131348 
		0.99102717638015747 0.99999749660491943 0.98354965448379517;
	setAttr -s 5 ".koy[0:4]"  -0.18979664146900177 0.00270095095038414 
		0.13366028666496277 -0.002274487866088748 -0.18063822388648987;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTA -n "char_FKCurveSpine3_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -38.617693158088045 12 -40.938982739361215 
		32 -19.930340841481332 47 -25.75307607357044 70 -38.617693158088045;
	setAttr -s 5 ".kit[0:4]"  1 3 10 10 1;
	setAttr -s 5 ".kot[0:4]"  1 3 10 10 1;
	setAttr -s 5 ".kix[0:4]"  0.97139179706573486 1 0.97515225410461426 
		0.96841150522232056 0.97671705484390259;
	setAttr -s 5 ".kiy[0:4]"  -0.23748266696929932 0 0.22153569757938385 
		-0.24935770034790039 -0.21453167498111725;
	setAttr -s 5 ".kox[0:4]"  0.97139179706573486 1 0.97515225410461426 
		0.96841150522232056 0.97671705484390259;
	setAttr -s 5 ".koy[0:4]"  -0.23748260736465454 0 0.22153569757938385 
		-0.24935770034790039 -0.21453158557415009;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTA -n "char_FKExtraSpine3_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraSpine3_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraSpine3_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveSpine4_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 70 1;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr -s 2 ".kox[1]"  1;
	setAttr -s 2 ".koy[1]"  0;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTU -n "char_FKCurveSpine4_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 70 1;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr -s 2 ".kox[1]"  1;
	setAttr -s 2 ".koy[1]"  0;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTU -n "char_FKCurveSpine4_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 70 1;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr -s 2 ".kox[1]"  1;
	setAttr -s 2 ".koy[1]"  0;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTA -n "char_FKCurveSpine4_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 19.548247782583122 12 17.01656508121722 
		32 17.864427882893185 47 17.411021455645038 70 19.548247782583122;
	setAttr -s 5 ".kit[0:4]"  9 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  9 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.99325072765350342;
	setAttr -s 5 ".kiy[4]"  -0.11598711460828781;
	setAttr -s 5 ".kox[4]"  0.99325072765350342;
	setAttr -s 5 ".koy[4]"  -0.1159871444106102;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTA -n "char_FKCurveSpine4_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 4.2832309672587163 12 3.094104958457724 
		32 3.774915702093891 47 4.1650935403218856 70 4.2832309672587163;
	setAttr -s 5 ".kit[0:4]"  1 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  1 10 10 10 1;
	setAttr -s 5 ".kix[0:4]"  0.99924582242965698 1 1 1 0.9983515739440918;
	setAttr -s 5 ".kiy[0:4]"  -0.038831252604722977 0 0 0 -0.057395860552787781;
	setAttr -s 5 ".kox[0:4]"  0.99924576282501221 1 1 1 0.99835151433944702;
	setAttr -s 5 ".koy[0:4]"  -0.038831252604722977 0 0 0 -0.057395860552787781;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTA -n "char_FKCurveSpine4_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 5.393 12 5.0506675901280564 32 5.2423561517390622 
		47 5.2818868257925979 70 5.393;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTA -n "char_FKExtraSpine4_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraSpine4_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraSpine4_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurvePelvis1_M_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurvePelvis1_M_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurvePelvis1_M_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurvePelvis1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurvePelvis1_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurvePelvis1_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.83191351642244571 32 -0.83191351642244571 
		70 -0.83191351642244571;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraPelvis1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraPelvis1_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraPelvis1_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_RootCurveRoot1_M_CenterBtwFeet";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 44 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTA -n "char_RootCurveRoot1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 3.0405827598215973 10 2.4030182720652569 
		44 -0.88284418120700281 70 3.0405827598215973;
	setAttr -s 4 ".kit[1:3]"  9 3 1;
	setAttr -s 4 ".kot[1:3]"  9 3 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTA -n "char_RootCurveRoot1_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 23.714440424736864 10 26.929125615312884 
		44 14.422473236103739 70 23.714440424736864;
	setAttr -s 4 ".kit[0:3]"  1 3 3 1;
	setAttr -s 4 ".kot[0:3]"  1 3 3 1;
	setAttr -s 4 ".kix[0:3]"  0.96292614936828613 1 1 0.95836281776428223;
	setAttr -s 4 ".kiy[0:3]"  0.26976528763771057 0 0 0.28555348515510559;
	setAttr -s 4 ".kox[0:3]"  0.96292614936828613 1 1 0.95836281776428223;
	setAttr -s 4 ".koy[0:3]"  0.26976519823074341 0 0 0.28555354475975037;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTA -n "char_RootCurveRoot1_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 8.6470827930312559 10 7.0616472578209342 
		44 -1.0565194972118839 70 8.6470827930312559;
	setAttr -s 4 ".kit[1:3]"  1 3 1;
	setAttr -s 4 ".kot[1:3]"  1 3 1;
	setAttr -s 4 ".kix[1:3]"  0.9896511435508728 1 1;
	setAttr -s 4 ".kiy[1:3]"  -0.14349405467510223 0 0;
	setAttr -s 4 ".kox[1:3]"  0.9896511435508728 1 1;
	setAttr -s 4 ".koy[1:3]"  -0.14349403977394104 0 0;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTL -n "char_RootCurveRoot1_M_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -0.11500744677504726 10 -0.081944897162661567 
		48 -0.19111587324388607 70 -0.11500744677504726;
	setAttr -s 4 ".kit[0:3]"  1 3 3 1;
	setAttr -s 4 ".kot[0:3]"  1 3 3 1;
	setAttr -s 4 ".kix[0:3]"  0.9826735258102417 1 1 0.98071485757827759;
	setAttr -s 4 ".kiy[0:3]"  0.18534499406814575 0 0 0.19544415175914764;
	setAttr -s 4 ".kox[0:3]"  0.9826735258102417 1 1 0.98071473836898804;
	setAttr -s 4 ".koy[0:3]"  0.18534500896930695 0 0 0.19544416666030884;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTL -n "char_RootCurveRoot1_M_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.26403992941414445 44 -0.21143663907543297 
		70 -0.26403992941414445;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTL -n "char_RootCurveRoot1_M_translateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -0.0438000161016944 10 -0.062678045121061232 
		44 0.016868006578670353 70 -0.0438000161016944;
	setAttr -s 4 ".kit[1:3]"  10 3 1;
	setAttr -s 4 ".kot[1:3]"  10 3 1;
	setAttr -s 4 ".kix[0:3]"  0.99563968181610107 1 1 0.99696612358093262;
	setAttr -s 4 ".kiy[0:3]"  -0.093283019959926605 0 0 -0.077836841344833374;
	setAttr -s 4 ".kox[0:3]"  0.99563968181610107 1 1 0.99696612358093262;
	setAttr -s 4 ".koy[0:3]"  -0.093282990157604218 0 0 -0.07783682644367218;
	setAttr ".pre" 3;
	setAttr ".pst" 3;
createNode animCurveTA -n "char_RootExtraRoot1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_RootExtraRoot1_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_RootExtraRoot1_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_RootExtraRoot1_M_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_RootExtraRoot1_M_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_RootExtraRoot1_M_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Clavicle1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Clavicle1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Clavicle1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 -12.310297351960626 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 -18.030407654922946 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 -0.80424806991032161 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 2.1942103669999999e-008 32 2.1942103669999999e-008 
		70 2.1942103669999999e-008;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Shoulder1_L_rotateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.68127875452050601 13 0.50946811229147926 
		32 0.86516854131991994 47 -1.3696538317779603 70 -0.68127875452050601;
	setAttr -s 5 ".kit[0:4]"  9 1 3 10 1;
	setAttr -s 5 ".kot[0:4]"  9 1 3 10 1;
	setAttr -s 5 ".kix[1:4]"  0.99988234043121338 1 1 0.99950236082077026;
	setAttr -s 5 ".kiy[1:4]"  0.015341590158641338 0 0 0.031545024365186691;
	setAttr -s 5 ".kox[1:4]"  0.99988234043121338 1 1 0.99950236082077026;
	setAttr -s 5 ".koy[1:4]"  0.015341594815254211 0 0 0.031545024365186691;
createNode animCurveTA -n "char_FKExtraR_Shoulder1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Shoulder1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Shoulder1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Elbow1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 48.213367515818511 32 48.213367515818511 
		70 48.213367515818511;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Elbow1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Elbow1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Elbow1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveDevice3_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveDevice3_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveDevice3_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveDevice3_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -83.798780827240449 32 -83.798780827240449 
		70 -83.798780827240449;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveDevice3_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.15209529104924274 32 -0.15209529104924274 
		70 -0.15209529104924274;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveDevice3_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -4.6558253190878789 32 -4.6558253190878789 
		70 -4.6558253190878789;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_FKCurveDevice3_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.070796223027113955 32 0.070796223027113955 
		70 0.070796223027113955;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_FKCurveDevice3_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.0024602716719113347 32 0.0024602716719113347 
		70 0.0024602716719113347;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_FKCurveDevice3_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.20119425626585011 32 0.20119425626585011 
		70 0.20119425626585011;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKExtraDevice3_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKExtraDevice3_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKExtraDevice3_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraDevice3_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraDevice3_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraDevice3_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_FKExtraDevice3_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_FKExtraDevice3_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_FKExtraDevice3_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Thumb5_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Thumb5_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Thumb5_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Thumb5_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 64.163191954635607 32 64.163191954635607 
		70 64.163191954635607;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Thumb5_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 2.4325234183121345 32 2.4325234183121345 
		70 2.4325234183121345;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Thumb5_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 8.5957802944005888 32 8.5957802944005888 
		70 8.5957802944005888;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Thumb5_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Thumb5_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Thumb5_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Thumb6_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Thumb6_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Thumb6_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Thumb6_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 30.907503992135247 32 30.907503992135247 
		70 30.907503992135247;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Thumb6_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -37.423813770375673 32 -37.423813770375673 
		70 -37.423813770375673;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Thumb6_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -55.763523784114774 32 -55.763523784114774 
		70 -55.763523784114774;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Thumb6_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Thumb6_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Thumb6_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Middle5_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Middle5_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Middle5_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Middle5_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 65.894016206888068 32 65.894016206888068 
		70 65.894016206888068;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Middle5_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 18.465908619718412 32 18.465908619718412 
		70 18.465908619718412;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Middle5_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -36.952741198413079 32 -36.952741198413079 
		70 -36.952741198413079;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Middle5_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Middle5_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Middle5_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Middle6_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Middle6_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Middle6_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Middle6_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 17.446522746060875 32 17.446522746060875 
		70 17.446522746060875;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Middle6_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Middle6_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Middle6_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Middle6_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Middle6_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 32 -2.2482649983687057 45 2.9738133580831878 
		70 0;
	setAttr -s 4 ".kit[2:3]"  10 1;
	setAttr -s 4 ".kot[2:3]"  10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 24.211026325508492 13 27.617622481588853 
		32 54.177895278315113 45 40.946726623649361 70 24.211026325508492;
	setAttr -s 5 ".kit[1:4]"  10 3 10 1;
	setAttr -s 5 ".kot[1:4]"  10 3 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 32 -8.7669545331120204 45 -11.807488533008792 
		70 0;
	setAttr -s 4 ".kit[2:3]"  10 1;
	setAttr -s 4 ".kot[2:3]"  10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "char_FKExtraR_Wrist1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Wrist1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Wrist1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Hip1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Hip1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Hip1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Hip1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Hip1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Hip1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Hip1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Hip1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Hip1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Knee1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Knee1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Knee1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Knee1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Knee1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Knee1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Knee1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Ankle1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Ankle1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Ankle1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Ankle1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Ankle1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Ankle1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Ankle1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Ankle1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Ankle1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Ball1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Ball1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Ball1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Ball1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Ball1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Ball1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Ball1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Ball1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Ball1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Clavicle1_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Clavicle1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Clavicle1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 -15.070563988318813 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 -8.6916345634859891 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 -8.3412926476998255 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -2.194210208e-008 32 -2.194210208e-008 
		70 -2.194210208e-008;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Shoulder1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 17.19229314797029 13 22.189965876663916 
		32 24.90532447877175 47 18.201056877013027 70 17.19229314797029;
	setAttr -s 5 ".kit[1:4]"  1 3 10 1;
	setAttr -s 5 ".kot[1:4]"  1 3 10 1;
	setAttr -s 5 ".kix[1:4]"  0.99963259696960449 1 1 1;
	setAttr -s 5 ".kiy[1:4]"  0.027105692774057388 0 0 0;
	setAttr -s 5 ".kox[1:4]"  0.99963259696960449 1 1 1;
	setAttr -s 5 ".koy[1:4]"  0.027105702087283134 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Shoulder1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Shoulder1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Shoulder1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Elbow1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 36.067317209388015 32 20.349176061094898 
		47 34.238389411206541 70 36.067317209388015;
	setAttr -s 4 ".kit[2:3]"  10 1;
	setAttr -s 4 ".kot[2:3]"  10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "char_FKExtraR_Elbow1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Elbow1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Elbow1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Thumb5_R_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 19 1 43 1 70 1;
	setAttr -s 4 ".kit[0:3]"  3 10 10 1;
	setAttr -s 4 ".kot[0:3]"  3 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "char_FKCurveR_Thumb5_R_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 19 1 43 1 70 1;
	setAttr -s 4 ".kit[0:3]"  3 10 10 1;
	setAttr -s 4 ".kot[0:3]"  3 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "char_FKCurveR_Thumb5_R_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 19 1 43 1 70 1;
	setAttr -s 4 ".kit[0:3]"  3 10 10 1;
	setAttr -s 4 ".kot[0:3]"  3 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "char_FKCurveR_Thumb5_R_rotateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 27.905251822156437 19 31.030075028554602 
		43 27.905251822156437 59 24.638677065058307 70 27.905251822156437;
	setAttr -s 5 ".kit[1:4]"  10 1 10 1;
	setAttr -s 5 ".kot[1:4]"  10 1 10 1;
	setAttr -s 5 ".kix[0:4]"  0.98926585912704468 1 0.99569958448410034 
		1 0.98453104496002197;
	setAttr -s 5 ".kiy[0:4]"  0.14612694084644318 0 -0.092640817165374756 
		0 0.17521025240421295;
	setAttr -s 5 ".kox[0:4]"  0.98926585912704468 1 0.99569964408874512 
		1 0.98453110456466675;
	setAttr -s 5 ".koy[0:4]"  0.14612694084644318 0 -0.092640846967697144 
		0 0.17521026730537415;
createNode animCurveTA -n "char_FKCurveR_Thumb5_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 19 -27.463859904614345 43 0 70 0;
	setAttr -s 4 ".kit[0:3]"  3 10 10 1;
	setAttr -s 4 ".kot[0:3]"  3 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "char_FKCurveR_Thumb5_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 19 -4.2182425118128277 43 0 70 0;
	setAttr -s 4 ".kit[0:3]"  3 10 10 1;
	setAttr -s 4 ".kot[0:3]"  3 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "char_FKExtraR_Thumb5_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Thumb5_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Thumb5_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Thumb6_R_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 19 1 43 1 70 1;
	setAttr -s 4 ".kit[0:3]"  3 10 10 1;
	setAttr -s 4 ".kot[0:3]"  3 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "char_FKCurveR_Thumb6_R_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 19 1 43 1 70 1;
	setAttr -s 4 ".kit[0:3]"  3 10 10 1;
	setAttr -s 4 ".kot[0:3]"  3 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "char_FKCurveR_Thumb6_R_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 19 1 43 1 70 1;
	setAttr -s 4 ".kit[0:3]"  3 10 10 1;
	setAttr -s 4 ".kot[0:3]"  3 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "char_FKCurveR_Thumb6_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 28.959457180709169 19 24.183133757312639 
		43 28.959457180709169 70 28.959457180709169;
	setAttr -s 4 ".kit[0:3]"  3 10 10 1;
	setAttr -s 4 ".kot[0:3]"  3 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "char_FKCurveR_Thumb6_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -12.483272772594933 19 -24.310452477262693 
		43 -12.483272772594933 70 -12.483272772594933;
	setAttr -s 4 ".kit[0:3]"  3 10 10 1;
	setAttr -s 4 ".kot[0:3]"  3 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "char_FKCurveR_Thumb6_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 21.335853393578894 19 21.770283962500024 
		43 21.335853393578894 70 21.335853393578894;
	setAttr -s 4 ".kit[0:3]"  3 10 10 1;
	setAttr -s 4 ".kot[0:3]"  3 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "char_FKExtraR_Thumb6_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Thumb6_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Thumb6_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Middle5_R_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 19 1 43 1 70 1;
	setAttr -s 4 ".kit[0:3]"  3 10 10 1;
	setAttr -s 4 ".kot[0:3]"  3 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "char_FKCurveR_Middle5_R_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 19 1 43 1 70 1;
	setAttr -s 4 ".kit[0:3]"  3 10 10 1;
	setAttr -s 4 ".kot[0:3]"  3 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "char_FKCurveR_Middle5_R_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 19 1 43 1 70 1;
	setAttr -s 4 ".kit[0:3]"  3 10 10 1;
	setAttr -s 4 ".kot[0:3]"  3 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "char_FKCurveR_Middle5_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 31.36933547988048 19 23.804163271563212 
		43 42.320762123924595 60 24.423414146116343 70 31.36933547988048;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "char_FKCurveR_Middle5_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 19 0.11419902770464099 43 0.2768052554932996 
		60 0.41441892250875612 70 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "char_FKCurveR_Middle5_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 19 -0.13562619485012897 43 -0.32874223425238758 
		60 -0.49217635792068021 70 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "char_FKExtraR_Middle5_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Middle5_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Middle5_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Middle6_R_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 19 1 43 1 70 1;
	setAttr -s 4 ".kit[0:3]"  3 10 10 1;
	setAttr -s 4 ".kot[0:3]"  3 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "char_FKCurveR_Middle6_R_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 19 1 43 1 70 1;
	setAttr -s 4 ".kit[0:3]"  3 10 10 1;
	setAttr -s 4 ".kot[0:3]"  3 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTU -n "char_FKCurveR_Middle6_R_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 19 1 43 1 70 1;
	setAttr -s 4 ".kit[0:3]"  3 10 10 1;
	setAttr -s 4 ".kot[0:3]"  3 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "char_FKCurveR_Middle6_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 20.121507236316084 19 12.556335027998822 
		43 31.072933880360161 60 13.175585902551928 70 20.121507236316084;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "char_FKCurveR_Middle6_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 19 0.11419902770464109 43 0.27680525549329987 
		60 0.41441892250875656 70 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "char_FKCurveR_Middle6_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 19 -0.13562619485012917 43 -0.32874223425238797 
		60 -0.49217635792068093 70 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "char_FKExtraR_Middle6_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Middle6_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Middle6_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 5.3442930176413892 13 -3.8319039821847012 
		32 -13.867544922959635 50 -8.0260945776356767 60 -1.0747049291139579 70 5.3442930176413892;
	setAttr -s 6 ".kit[0:5]"  3 10 3 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 3 10 10 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 30.381278874765098 13 12.276105178343432 
		32 37.64568259291778 50 34.690782058899266 60 38.227167309042827 70 30.381278874765098;
	setAttr -s 6 ".kit[0:5]"  3 10 3 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 3 10 10 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 11.798366512855891 13 6.0941083553072071 
		32 5.8647075933550488 50 -5.6257498267362775 60 5.51767115270132 70 11.798366512855891;
	setAttr -s 6 ".kit[0:5]"  3 10 3 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 3 10 10 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTA -n "char_FKExtraR_Wrist1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Wrist1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Wrist1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Hip1_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Hip1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Hip1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Hip1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Hip1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Hip1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Hip1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Hip1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Hip1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Knee1_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Knee1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Knee1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Knee1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Knee1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Knee1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Knee1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Ankle1_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Ankle1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Ankle1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Ankle1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Ankle1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Ankle1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Ankle1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Ankle1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Ankle1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Ball1_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Ball1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_FKCurveR_Ball1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Ball1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Ball1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKCurveR_Ball1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Ball1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Ball1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_FKExtraR_Ball1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_All_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_All_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_All_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_All_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_All_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "char_All_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_All_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_All_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "char_All_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 32 0 70 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTU -n "char_All_visibility";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 32 1 70 1;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode lightLinker -n "lightLinker1";
	setAttr -s 3 ".lnk";
	setAttr -s 3 ".slnk";
select -ne :time1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 0;
select -ne :renderPartition;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 3 ".st";
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
	setAttr -s 3 ".s";
select -ne :postProcessList1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
	setAttr -s 3 ".u";
select -ne :lightList1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
select -ne :defaultTextureList1;
	setAttr -s 2 ".tx";
select -ne :lambert1;
	setAttr ".miic" -type "float3" 9.8696051 9.8696051 9.8696051 ;
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
select -ne :defaultRenderGlobals;
	setAttr ".mcfr" 30;
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
select -ne :hyperGraphLayout;
	setAttr -s 34 ".hyp";
	setAttr ".hyp[29].isc" yes;
	setAttr ".hyp[29].isf" no;
	setAttr ".hyp[33].isc" yes;
	setAttr ".hyp[33].isf" no;
	setAttr ".hyp[34].isc" yes;
	setAttr ".hyp[34].isf" no;
	setAttr ".hyp[36].isc" yes;
	setAttr ".hyp[36].isf" no;
	setAttr ".hyp[37].isc" yes;
	setAttr ".hyp[37].isf" no;
	setAttr ".hyp[38].isc" yes;
	setAttr ".hyp[38].isf" no;
	setAttr ".hyp[39].isc" yes;
	setAttr ".hyp[39].isf" no;
	setAttr ".hyp[40].isc" yes;
	setAttr ".hyp[40].isf" no;
	setAttr ".hyp[41].isc" yes;
	setAttr ".hyp[41].isf" no;
	setAttr ".hyp[42].isc" yes;
	setAttr ".hyp[42].isf" no;
	setAttr ".hyp[43].isc" yes;
	setAttr ".hyp[43].isf" no;
	setAttr ".hyp[44].isc" yes;
	setAttr ".hyp[44].isf" no;
	setAttr ".hyp[45].isc" yes;
	setAttr ".hyp[45].isf" no;
	setAttr ".hyp[46].isc" yes;
	setAttr ".hyp[46].isf" no;
	setAttr ".hyp[47].isc" yes;
	setAttr ".hyp[47].isf" no;
	setAttr ".hyp[48].isc" yes;
	setAttr ".hyp[48].isf" no;
	setAttr ".hyp[49].isc" yes;
	setAttr ".hyp[49].isf" no;
	setAttr ".hyp[50].isc" yes;
	setAttr ".hyp[50].isf" no;
	setAttr ".hyp[51].isc" yes;
	setAttr ".hyp[51].isf" no;
	setAttr ".hyp[52].isc" yes;
	setAttr ".hyp[52].isf" no;
	setAttr ".hyp[53].isc" yes;
	setAttr ".hyp[53].isf" no;
	setAttr ".hyp[54].isc" yes;
	setAttr ".hyp[54].isf" no;
	setAttr ".hyp[55].isc" yes;
	setAttr ".hyp[55].isf" no;
	setAttr ".hyp[56].isc" yes;
	setAttr ".hyp[56].isf" no;
	setAttr ".hyp[58].isc" yes;
	setAttr ".hyp[58].isf" no;
	setAttr ".hyp[59].isc" yes;
	setAttr ".hyp[59].isf" no;
	setAttr ".hyp[60].isc" yes;
	setAttr ".hyp[60].isf" no;
	setAttr ".hyp[61].isc" yes;
	setAttr ".hyp[61].isf" no;
	setAttr ".hyp[62].isc" yes;
	setAttr ".hyp[62].isf" no;
	setAttr ".hyp[63].isc" yes;
	setAttr ".hyp[63].isf" no;
	setAttr ".hyp[65].isc" yes;
	setAttr ".hyp[65].isf" no;
	setAttr ".hyp[68].isc" yes;
	setAttr ".hyp[68].isf" no;
	setAttr ".hyp[76].isc" yes;
	setAttr ".hyp[76].isf" no;
	setAttr ".hyp[77].isc" yes;
	setAttr ".hyp[77].isf" no;
connectAttr "maugli_idle2Source.cl" "clipLibrary1.sc[0]";
connectAttr "char_AimCurveEye_Right1_M_follow.a" "clipLibrary1.cel[0].cev[0].cevr"
		;
connectAttr "char_AimCurveEye_Right1_M_cross.a" "clipLibrary1.cel[0].cev[1].cevr"
		;
connectAttr "char_AimCurveEye_Right1_M_translateZ.a" "clipLibrary1.cel[0].cev[2].cevr"
		;
connectAttr "char_AimCurveEye_Right1_M_translateY.a" "clipLibrary1.cel[0].cev[3].cevr"
		;
connectAttr "char_AimCurveEye_Right1_M_translateX.a" "clipLibrary1.cel[0].cev[4].cevr"
		;
connectAttr "char_FKIKControlCurveArm_L_IKVis.a" "clipLibrary1.cel[0].cev[5].cevr"
		;
connectAttr "char_FKIKControlCurveArm_L_FKVis.a" "clipLibrary1.cel[0].cev[6].cevr"
		;
connectAttr "char_FKIKControlCurveArm_L_FKIKBlend.a" "clipLibrary1.cel[0].cev[7].cevr"
		;
connectAttr "char_FKIKControlCurveLeg_L_IKVis.a" "clipLibrary1.cel[0].cev[8].cevr"
		;
connectAttr "char_FKIKControlCurveLeg_L_FKVis.a" "clipLibrary1.cel[0].cev[9].cevr"
		;
connectAttr "char_FKIKControlCurveLeg_L_FKIKBlend.a" "clipLibrary1.cel[0].cev[10].cevr"
		;
connectAttr "char_FKIKControlCurveArm_R_IKVis.a" "clipLibrary1.cel[0].cev[11].cevr"
		;
connectAttr "char_FKIKControlCurveArm_R_FKVis.a" "clipLibrary1.cel[0].cev[12].cevr"
		;
connectAttr "char_FKIKControlCurveArm_R_FKIKBlend.a" "clipLibrary1.cel[0].cev[13].cevr"
		;
connectAttr "char_FKIKControlCurveLeg_R_IKVis.a" "clipLibrary1.cel[0].cev[14].cevr"
		;
connectAttr "char_FKIKControlCurveLeg_R_FKVis.a" "clipLibrary1.cel[0].cev[15].cevr"
		;
connectAttr "char_FKIKControlCurveLeg_R_FKIKBlend.a" "clipLibrary1.cel[0].cev[16].cevr"
		;
connectAttr "char_IKPoleVectorCurveArm_L_follow.a" "clipLibrary1.cel[0].cev[17].cevr"
		;
connectAttr "char_IKPoleVectorCurveArm_L_translateZ.a" "clipLibrary1.cel[0].cev[18].cevr"
		;
connectAttr "char_IKPoleVectorCurveArm_L_translateY.a" "clipLibrary1.cel[0].cev[19].cevr"
		;
connectAttr "char_IKPoleVectorCurveArm_L_translateX.a" "clipLibrary1.cel[0].cev[20].cevr"
		;
connectAttr "char_IKPoleVectorExtraArm_L_translateZ.a" "clipLibrary1.cel[0].cev[21].cevr"
		;
connectAttr "char_IKPoleVectorExtraArm_L_translateY.a" "clipLibrary1.cel[0].cev[22].cevr"
		;
connectAttr "char_IKPoleVectorExtraArm_L_translateX.a" "clipLibrary1.cel[0].cev[23].cevr"
		;
connectAttr "char_IKCurveArm_L_antiPop.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "char_IKCurveArm_L_stretchy.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "char_IKCurveArm_L_follow.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "char_IKCurveArm_L_rotateZ.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "char_IKCurveArm_L_rotateY.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "char_IKCurveArm_L_rotateX.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "char_IKCurveArm_L_translateZ.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "char_IKCurveArm_L_translateY.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "char_IKCurveArm_L_translateX.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "char_IKExtraArm_L_rotateZ.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "char_IKExtraArm_L_rotateY.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "char_IKExtraArm_L_rotateX.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "char_IKExtraArm_L_translateZ.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "char_IKExtraArm_L_translateY.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "char_IKExtraArm_L_translateX.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "char_IKPoleVectorCurveLeg_L_follow.a" "clipLibrary1.cel[0].cev[39].cevr"
		;
connectAttr "char_IKPoleVectorCurveLeg_L_translateZ.a" "clipLibrary1.cel[0].cev[40].cevr"
		;
connectAttr "char_IKPoleVectorCurveLeg_L_translateY.a" "clipLibrary1.cel[0].cev[41].cevr"
		;
connectAttr "char_IKPoleVectorCurveLeg_L_translateX.a" "clipLibrary1.cel[0].cev[42].cevr"
		;
connectAttr "char_IKPoleVectorExtraLeg_L_translateZ.a" "clipLibrary1.cel[0].cev[43].cevr"
		;
connectAttr "char_IKPoleVectorExtraLeg_L_translateY.a" "clipLibrary1.cel[0].cev[44].cevr"
		;
connectAttr "char_IKPoleVectorExtraLeg_L_translateX.a" "clipLibrary1.cel[0].cev[45].cevr"
		;
connectAttr "char_IKCurveLeg_L_antiPop.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "char_IKCurveLeg_L_stretchy.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "char_IKCurveLeg_L_swivel.a" "clipLibrary1.cel[0].cev[48].cevr";
connectAttr "char_IKCurveLeg_L_rotateZ.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "char_IKCurveLeg_L_rotateY.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "char_IKCurveLeg_L_rotateX.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "char_IKCurveLeg_L_translateZ.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "char_IKCurveLeg_L_translateY.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "char_IKCurveLeg_L_translateX.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "char_IKExtraLeg_L_rotateZ.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "char_IKExtraLeg_L_rotateY.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "char_IKExtraLeg_L_rotateX.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "char_IKExtraLeg_L_translateZ.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "char_IKExtraLeg_L_translateY.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "char_IKExtraLeg_L_translateX.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "char_IKPoleVectorCurveArm_R_follow.a" "clipLibrary1.cel[0].cev[61].cevr"
		;
connectAttr "char_IKPoleVectorCurveArm_R_translateZ.a" "clipLibrary1.cel[0].cev[62].cevr"
		;
connectAttr "char_IKPoleVectorCurveArm_R_translateY.a" "clipLibrary1.cel[0].cev[63].cevr"
		;
connectAttr "char_IKPoleVectorCurveArm_R_translateX.a" "clipLibrary1.cel[0].cev[64].cevr"
		;
connectAttr "char_IKPoleVectorExtraArm_R_translateZ.a" "clipLibrary1.cel[0].cev[65].cevr"
		;
connectAttr "char_IKPoleVectorExtraArm_R_translateY.a" "clipLibrary1.cel[0].cev[66].cevr"
		;
connectAttr "char_IKPoleVectorExtraArm_R_translateX.a" "clipLibrary1.cel[0].cev[67].cevr"
		;
connectAttr "char_IKCurveArm_R_antiPop.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "char_IKCurveArm_R_stretchy.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "char_IKCurveArm_R_follow.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "char_IKCurveArm_R_rotateZ.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "char_IKCurveArm_R_rotateY.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "char_IKCurveArm_R_rotateX.a" "clipLibrary1.cel[0].cev[73].cevr";
connectAttr "char_IKCurveArm_R_translateZ.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "char_IKCurveArm_R_translateY.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "char_IKCurveArm_R_translateX.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "char_IKExtraArm_R_rotateZ.a" "clipLibrary1.cel[0].cev[77].cevr";
connectAttr "char_IKExtraArm_R_rotateY.a" "clipLibrary1.cel[0].cev[78].cevr";
connectAttr "char_IKExtraArm_R_rotateX.a" "clipLibrary1.cel[0].cev[79].cevr";
connectAttr "char_IKExtraArm_R_translateZ.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "char_IKExtraArm_R_translateY.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "char_IKExtraArm_R_translateX.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "char_IKPoleVectorCurveLeg_R_follow.a" "clipLibrary1.cel[0].cev[83].cevr"
		;
connectAttr "char_IKPoleVectorCurveLeg_R_translateZ.a" "clipLibrary1.cel[0].cev[84].cevr"
		;
connectAttr "char_IKPoleVectorCurveLeg_R_translateY.a" "clipLibrary1.cel[0].cev[85].cevr"
		;
connectAttr "char_IKPoleVectorCurveLeg_R_translateX.a" "clipLibrary1.cel[0].cev[86].cevr"
		;
connectAttr "char_IKPoleVectorExtraLeg_R_translateZ.a" "clipLibrary1.cel[0].cev[87].cevr"
		;
connectAttr "char_IKPoleVectorExtraLeg_R_translateY.a" "clipLibrary1.cel[0].cev[88].cevr"
		;
connectAttr "char_IKPoleVectorExtraLeg_R_translateX.a" "clipLibrary1.cel[0].cev[89].cevr"
		;
connectAttr "char_IKCurveLeg_R_antiPop.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "char_IKCurveLeg_R_stretchy.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "char_IKCurveLeg_R_swivel.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "char_IKCurveLeg_R_rotateZ.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "char_IKCurveLeg_R_rotateY.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "char_IKCurveLeg_R_rotateX.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "char_IKCurveLeg_R_translateZ.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "char_IKCurveLeg_R_translateY.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "char_IKCurveLeg_R_translateX.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "char_IKExtraLeg_R_rotateZ.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "char_IKExtraLeg_R_rotateY.a" "clipLibrary1.cel[0].cev[100].cevr";
connectAttr "char_IKExtraLeg_R_rotateX.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "char_IKExtraLeg_R_translateZ.a" "clipLibrary1.cel[0].cev[102].cevr"
		;
connectAttr "char_IKExtraLeg_R_translateY.a" "clipLibrary1.cel[0].cev[103].cevr"
		;
connectAttr "char_IKExtraLeg_R_translateX.a" "clipLibrary1.cel[0].cev[104].cevr"
		;
connectAttr "char_FKCurveTooth1_L_scaleZ.a" "clipLibrary1.cel[0].cev[105].cevr";
connectAttr "char_FKCurveTooth1_L_scaleY.a" "clipLibrary1.cel[0].cev[106].cevr";
connectAttr "char_FKCurveTooth1_L_scaleX.a" "clipLibrary1.cel[0].cev[107].cevr";
connectAttr "char_FKCurveTooth1_L_rotateZ.a" "clipLibrary1.cel[0].cev[108].cevr"
		;
connectAttr "char_FKCurveTooth1_L_rotateY.a" "clipLibrary1.cel[0].cev[109].cevr"
		;
connectAttr "char_FKCurveTooth1_L_rotateX.a" "clipLibrary1.cel[0].cev[110].cevr"
		;
connectAttr "char_FKCurveTooth1_L_translateZ.a" "clipLibrary1.cel[0].cev[111].cevr"
		;
connectAttr "char_FKCurveTooth1_L_translateY.a" "clipLibrary1.cel[0].cev[112].cevr"
		;
connectAttr "char_FKCurveTooth1_L_translateX.a" "clipLibrary1.cel[0].cev[113].cevr"
		;
connectAttr "char_FKExtraTooth1_L_scaleZ.a" "clipLibrary1.cel[0].cev[114].cevr";
connectAttr "char_FKExtraTooth1_L_scaleY.a" "clipLibrary1.cel[0].cev[115].cevr";
connectAttr "char_FKExtraTooth1_L_scaleX.a" "clipLibrary1.cel[0].cev[116].cevr";
connectAttr "char_FKExtraTooth1_L_rotateZ.a" "clipLibrary1.cel[0].cev[117].cevr"
		;
connectAttr "char_FKExtraTooth1_L_rotateY.a" "clipLibrary1.cel[0].cev[118].cevr"
		;
connectAttr "char_FKExtraTooth1_L_rotateX.a" "clipLibrary1.cel[0].cev[119].cevr"
		;
connectAttr "char_FKExtraTooth1_L_translateZ.a" "clipLibrary1.cel[0].cev[120].cevr"
		;
connectAttr "char_FKExtraTooth1_L_translateY.a" "clipLibrary1.cel[0].cev[121].cevr"
		;
connectAttr "char_FKExtraTooth1_L_translateX.a" "clipLibrary1.cel[0].cev[122].cevr"
		;
connectAttr "FKCurveR_Shoulder1_R_rotateZ.a" "clipLibrary1.cel[0].cev[123].cevr"
		;
connectAttr "FKCurveR_Shoulder1_R_rotateX.a" "clipLibrary1.cel[0].cev[124].cevr"
		;
connectAttr "FKCurveR_Shoulder1_L_rotateZ.a" "clipLibrary1.cel[0].cev[125].cevr"
		;
connectAttr "FKCurveR_Shoulder1_L_rotateX.a" "clipLibrary1.cel[0].cev[126].cevr"
		;
connectAttr "char_FKExtraPen1_L_rotateZ.a" "clipLibrary1.cel[0].cev[129].cevr";
connectAttr "char_FKExtraPen1_L_rotateY.a" "clipLibrary1.cel[0].cev[130].cevr";
connectAttr "char_FKExtraPen1_L_rotateX.a" "clipLibrary1.cel[0].cev[131].cevr";
connectAttr "char_FKExtraPen1_R_rotateZ.a" "clipLibrary1.cel[0].cev[138].cevr";
connectAttr "char_FKExtraPen1_R_rotateY.a" "clipLibrary1.cel[0].cev[139].cevr";
connectAttr "char_FKExtraPen1_R_rotateX.a" "clipLibrary1.cel[0].cev[140].cevr";
connectAttr "char_FKCurveHair1_L_scaleZ.a" "clipLibrary1.cel[0].cev[141].cevr";
connectAttr "char_FKCurveHair1_L_scaleY.a" "clipLibrary1.cel[0].cev[142].cevr";
connectAttr "char_FKCurveHair1_L_scaleX.a" "clipLibrary1.cel[0].cev[143].cevr";
connectAttr "char_FKCurveHair1_L_rotateZ.a" "clipLibrary1.cel[0].cev[144].cevr";
connectAttr "char_FKCurveHair1_L_rotateY.a" "clipLibrary1.cel[0].cev[145].cevr";
connectAttr "char_FKCurveHair1_L_rotateX.a" "clipLibrary1.cel[0].cev[146].cevr";
connectAttr "char_FKExtraHair1_L_rotateZ.a" "clipLibrary1.cel[0].cev[147].cevr";
connectAttr "char_FKExtraHair1_L_rotateY.a" "clipLibrary1.cel[0].cev[148].cevr";
connectAttr "char_FKExtraHair1_L_rotateX.a" "clipLibrary1.cel[0].cev[149].cevr";
connectAttr "char_FKCurveHead1_M_scaleZ.a" "clipLibrary1.cel[0].cev[150].cevr";
connectAttr "char_FKCurveHead1_M_scaleY.a" "clipLibrary1.cel[0].cev[151].cevr";
connectAttr "char_FKCurveHead1_M_scaleX.a" "clipLibrary1.cel[0].cev[152].cevr";
connectAttr "char_FKCurveHead1_M_rotateZ.a" "clipLibrary1.cel[0].cev[153].cevr";
connectAttr "char_FKCurveHead1_M_rotateY.a" "clipLibrary1.cel[0].cev[154].cevr";
connectAttr "char_FKCurveHead1_M_rotateX.a" "clipLibrary1.cel[0].cev[155].cevr";
connectAttr "char_FKExtraHead1_M_rotateZ.a" "clipLibrary1.cel[0].cev[156].cevr";
connectAttr "char_FKExtraHead1_M_rotateY.a" "clipLibrary1.cel[0].cev[157].cevr";
connectAttr "char_FKExtraHead1_M_rotateX.a" "clipLibrary1.cel[0].cev[158].cevr";
connectAttr "char_FKCurveNeck1_M_scaleZ.a" "clipLibrary1.cel[0].cev[159].cevr";
connectAttr "char_FKCurveNeck1_M_scaleY.a" "clipLibrary1.cel[0].cev[160].cevr";
connectAttr "char_FKCurveNeck1_M_scaleX.a" "clipLibrary1.cel[0].cev[161].cevr";
connectAttr "char_FKCurveNeck1_M_rotateZ.a" "clipLibrary1.cel[0].cev[162].cevr";
connectAttr "char_FKCurveNeck1_M_rotateY.a" "clipLibrary1.cel[0].cev[163].cevr";
connectAttr "char_FKCurveNeck1_M_rotateX.a" "clipLibrary1.cel[0].cev[164].cevr";
connectAttr "char_FKExtraNeck1_M_rotateZ.a" "clipLibrary1.cel[0].cev[165].cevr";
connectAttr "char_FKExtraNeck1_M_rotateY.a" "clipLibrary1.cel[0].cev[166].cevr";
connectAttr "char_FKExtraNeck1_M_rotateX.a" "clipLibrary1.cel[0].cev[167].cevr";
connectAttr "char_FKCurveSpine3_M_scaleZ.a" "clipLibrary1.cel[0].cev[168].cevr";
connectAttr "char_FKCurveSpine3_M_scaleY.a" "clipLibrary1.cel[0].cev[169].cevr";
connectAttr "char_FKCurveSpine3_M_scaleX.a" "clipLibrary1.cel[0].cev[170].cevr";
connectAttr "char_FKCurveSpine3_M_rotateZ.a" "clipLibrary1.cel[0].cev[171].cevr"
		;
connectAttr "char_FKCurveSpine3_M_rotateY.a" "clipLibrary1.cel[0].cev[172].cevr"
		;
connectAttr "char_FKCurveSpine3_M_rotateX.a" "clipLibrary1.cel[0].cev[173].cevr"
		;
connectAttr "char_FKExtraSpine3_M_rotateZ.a" "clipLibrary1.cel[0].cev[174].cevr"
		;
connectAttr "char_FKExtraSpine3_M_rotateY.a" "clipLibrary1.cel[0].cev[175].cevr"
		;
connectAttr "char_FKExtraSpine3_M_rotateX.a" "clipLibrary1.cel[0].cev[176].cevr"
		;
connectAttr "char_FKCurveSpine4_L_scaleZ.a" "clipLibrary1.cel[0].cev[177].cevr";
connectAttr "char_FKCurveSpine4_L_scaleY.a" "clipLibrary1.cel[0].cev[178].cevr";
connectAttr "char_FKCurveSpine4_L_scaleX.a" "clipLibrary1.cel[0].cev[179].cevr";
connectAttr "char_FKCurveSpine4_L_rotateZ.a" "clipLibrary1.cel[0].cev[180].cevr"
		;
connectAttr "char_FKCurveSpine4_L_rotateY.a" "clipLibrary1.cel[0].cev[181].cevr"
		;
connectAttr "char_FKCurveSpine4_L_rotateX.a" "clipLibrary1.cel[0].cev[182].cevr"
		;
connectAttr "char_FKExtraSpine4_L_rotateZ.a" "clipLibrary1.cel[0].cev[183].cevr"
		;
connectAttr "char_FKExtraSpine4_L_rotateY.a" "clipLibrary1.cel[0].cev[184].cevr"
		;
connectAttr "char_FKExtraSpine4_L_rotateX.a" "clipLibrary1.cel[0].cev[185].cevr"
		;
connectAttr "char_FKCurvePelvis1_M_scaleZ.a" "clipLibrary1.cel[0].cev[186].cevr"
		;
connectAttr "char_FKCurvePelvis1_M_scaleY.a" "clipLibrary1.cel[0].cev[187].cevr"
		;
connectAttr "char_FKCurvePelvis1_M_scaleX.a" "clipLibrary1.cel[0].cev[188].cevr"
		;
connectAttr "char_FKCurvePelvis1_M_rotateZ.a" "clipLibrary1.cel[0].cev[189].cevr"
		;
connectAttr "char_FKCurvePelvis1_M_rotateY.a" "clipLibrary1.cel[0].cev[190].cevr"
		;
connectAttr "char_FKCurvePelvis1_M_rotateX.a" "clipLibrary1.cel[0].cev[191].cevr"
		;
connectAttr "char_FKExtraPelvis1_M_rotateZ.a" "clipLibrary1.cel[0].cev[192].cevr"
		;
connectAttr "char_FKExtraPelvis1_M_rotateY.a" "clipLibrary1.cel[0].cev[193].cevr"
		;
connectAttr "char_FKExtraPelvis1_M_rotateX.a" "clipLibrary1.cel[0].cev[194].cevr"
		;
connectAttr "char_RootCurveRoot1_M_CenterBtwFeet.a" "clipLibrary1.cel[0].cev[195].cevr"
		;
connectAttr "char_RootCurveRoot1_M_rotateZ.a" "clipLibrary1.cel[0].cev[196].cevr"
		;
connectAttr "char_RootCurveRoot1_M_rotateY.a" "clipLibrary1.cel[0].cev[197].cevr"
		;
connectAttr "char_RootCurveRoot1_M_rotateX.a" "clipLibrary1.cel[0].cev[198].cevr"
		;
connectAttr "char_RootCurveRoot1_M_translateZ.a" "clipLibrary1.cel[0].cev[199].cevr"
		;
connectAttr "char_RootCurveRoot1_M_translateY.a" "clipLibrary1.cel[0].cev[200].cevr"
		;
connectAttr "char_RootCurveRoot1_M_translateX.a" "clipLibrary1.cel[0].cev[201].cevr"
		;
connectAttr "char_RootExtraRoot1_M_rotateZ.a" "clipLibrary1.cel[0].cev[202].cevr"
		;
connectAttr "char_RootExtraRoot1_M_rotateY.a" "clipLibrary1.cel[0].cev[203].cevr"
		;
connectAttr "char_RootExtraRoot1_M_rotateX.a" "clipLibrary1.cel[0].cev[204].cevr"
		;
connectAttr "char_RootExtraRoot1_M_translateZ.a" "clipLibrary1.cel[0].cev[205].cevr"
		;
connectAttr "char_RootExtraRoot1_M_translateY.a" "clipLibrary1.cel[0].cev[206].cevr"
		;
connectAttr "char_RootExtraRoot1_M_translateX.a" "clipLibrary1.cel[0].cev[207].cevr"
		;
connectAttr "char_FKCurveR_Clavicle1_L_scaleZ.a" "clipLibrary1.cel[0].cev[208].cevr"
		;
connectAttr "char_FKCurveR_Clavicle1_L_scaleY.a" "clipLibrary1.cel[0].cev[209].cevr"
		;
connectAttr "char_FKCurveR_Clavicle1_L_scaleX.a" "clipLibrary1.cel[0].cev[210].cevr"
		;
connectAttr "char_FKCurveR_Clavicle1_L_rotateZ.a" "clipLibrary1.cel[0].cev[211].cevr"
		;
connectAttr "char_FKCurveR_Clavicle1_L_rotateY.a" "clipLibrary1.cel[0].cev[212].cevr"
		;
connectAttr "char_FKCurveR_Clavicle1_L_rotateX.a" "clipLibrary1.cel[0].cev[213].cevr"
		;
connectAttr "char_FKExtraR_Clavicle1_L_rotateZ.a" "clipLibrary1.cel[0].cev[214].cevr"
		;
connectAttr "char_FKExtraR_Clavicle1_L_rotateY.a" "clipLibrary1.cel[0].cev[215].cevr"
		;
connectAttr "char_FKExtraR_Clavicle1_L_rotateX.a" "clipLibrary1.cel[0].cev[216].cevr"
		;
connectAttr "char_FKCurveR_Shoulder1_L_scaleZ.a" "clipLibrary1.cel[0].cev[217].cevr"
		;
connectAttr "char_FKCurveR_Shoulder1_L_scaleY.a" "clipLibrary1.cel[0].cev[218].cevr"
		;
connectAttr "char_FKCurveR_Shoulder1_L_scaleX.a" "clipLibrary1.cel[0].cev[219].cevr"
		;
connectAttr "char_FKCurveR_Shoulder1_L_rotateY.a" "clipLibrary1.cel[0].cev[220].cevr"
		;
connectAttr "char_FKExtraR_Shoulder1_L_rotateZ.a" "clipLibrary1.cel[0].cev[221].cevr"
		;
connectAttr "char_FKExtraR_Shoulder1_L_rotateY.a" "clipLibrary1.cel[0].cev[222].cevr"
		;
connectAttr "char_FKExtraR_Shoulder1_L_rotateX.a" "clipLibrary1.cel[0].cev[223].cevr"
		;
connectAttr "char_FKCurveR_Elbow1_L_scaleZ.a" "clipLibrary1.cel[0].cev[224].cevr"
		;
connectAttr "char_FKCurveR_Elbow1_L_scaleY.a" "clipLibrary1.cel[0].cev[225].cevr"
		;
connectAttr "char_FKCurveR_Elbow1_L_scaleX.a" "clipLibrary1.cel[0].cev[226].cevr"
		;
connectAttr "char_FKCurveR_Elbow1_L_rotateY.a" "clipLibrary1.cel[0].cev[227].cevr"
		;
connectAttr "char_FKExtraR_Elbow1_L_rotateZ.a" "clipLibrary1.cel[0].cev[228].cevr"
		;
connectAttr "char_FKExtraR_Elbow1_L_rotateY.a" "clipLibrary1.cel[0].cev[229].cevr"
		;
connectAttr "char_FKExtraR_Elbow1_L_rotateX.a" "clipLibrary1.cel[0].cev[230].cevr"
		;
connectAttr "char_FKCurveDevice3_L_scaleZ.a" "clipLibrary1.cel[0].cev[231].cevr"
		;
connectAttr "char_FKCurveDevice3_L_scaleY.a" "clipLibrary1.cel[0].cev[232].cevr"
		;
connectAttr "char_FKCurveDevice3_L_scaleX.a" "clipLibrary1.cel[0].cev[233].cevr"
		;
connectAttr "char_FKCurveDevice3_L_rotateZ.a" "clipLibrary1.cel[0].cev[234].cevr"
		;
connectAttr "char_FKCurveDevice3_L_rotateY.a" "clipLibrary1.cel[0].cev[235].cevr"
		;
connectAttr "char_FKCurveDevice3_L_rotateX.a" "clipLibrary1.cel[0].cev[236].cevr"
		;
connectAttr "char_FKCurveDevice3_L_translateZ.a" "clipLibrary1.cel[0].cev[237].cevr"
		;
connectAttr "char_FKCurveDevice3_L_translateY.a" "clipLibrary1.cel[0].cev[238].cevr"
		;
connectAttr "char_FKCurveDevice3_L_translateX.a" "clipLibrary1.cel[0].cev[239].cevr"
		;
connectAttr "char_FKExtraDevice3_L_scaleZ.a" "clipLibrary1.cel[0].cev[240].cevr"
		;
connectAttr "char_FKExtraDevice3_L_scaleY.a" "clipLibrary1.cel[0].cev[241].cevr"
		;
connectAttr "char_FKExtraDevice3_L_scaleX.a" "clipLibrary1.cel[0].cev[242].cevr"
		;
connectAttr "char_FKExtraDevice3_L_rotateZ.a" "clipLibrary1.cel[0].cev[243].cevr"
		;
connectAttr "char_FKExtraDevice3_L_rotateY.a" "clipLibrary1.cel[0].cev[244].cevr"
		;
connectAttr "char_FKExtraDevice3_L_rotateX.a" "clipLibrary1.cel[0].cev[245].cevr"
		;
connectAttr "char_FKExtraDevice3_L_translateZ.a" "clipLibrary1.cel[0].cev[246].cevr"
		;
connectAttr "char_FKExtraDevice3_L_translateY.a" "clipLibrary1.cel[0].cev[247].cevr"
		;
connectAttr "char_FKExtraDevice3_L_translateX.a" "clipLibrary1.cel[0].cev[248].cevr"
		;
connectAttr "char_FKCurveR_Thumb5_L_scaleZ.a" "clipLibrary1.cel[0].cev[249].cevr"
		;
connectAttr "char_FKCurveR_Thumb5_L_scaleY.a" "clipLibrary1.cel[0].cev[250].cevr"
		;
connectAttr "char_FKCurveR_Thumb5_L_scaleX.a" "clipLibrary1.cel[0].cev[251].cevr"
		;
connectAttr "char_FKCurveR_Thumb5_L_rotateZ.a" "clipLibrary1.cel[0].cev[252].cevr"
		;
connectAttr "char_FKCurveR_Thumb5_L_rotateY.a" "clipLibrary1.cel[0].cev[253].cevr"
		;
connectAttr "char_FKCurveR_Thumb5_L_rotateX.a" "clipLibrary1.cel[0].cev[254].cevr"
		;
connectAttr "char_FKExtraR_Thumb5_L_rotateZ.a" "clipLibrary1.cel[0].cev[255].cevr"
		;
connectAttr "char_FKExtraR_Thumb5_L_rotateY.a" "clipLibrary1.cel[0].cev[256].cevr"
		;
connectAttr "char_FKExtraR_Thumb5_L_rotateX.a" "clipLibrary1.cel[0].cev[257].cevr"
		;
connectAttr "char_FKCurveR_Thumb6_L_scaleZ.a" "clipLibrary1.cel[0].cev[258].cevr"
		;
connectAttr "char_FKCurveR_Thumb6_L_scaleY.a" "clipLibrary1.cel[0].cev[259].cevr"
		;
connectAttr "char_FKCurveR_Thumb6_L_scaleX.a" "clipLibrary1.cel[0].cev[260].cevr"
		;
connectAttr "char_FKCurveR_Thumb6_L_rotateZ.a" "clipLibrary1.cel[0].cev[261].cevr"
		;
connectAttr "char_FKCurveR_Thumb6_L_rotateY.a" "clipLibrary1.cel[0].cev[262].cevr"
		;
connectAttr "char_FKCurveR_Thumb6_L_rotateX.a" "clipLibrary1.cel[0].cev[263].cevr"
		;
connectAttr "char_FKExtraR_Thumb6_L_rotateZ.a" "clipLibrary1.cel[0].cev[264].cevr"
		;
connectAttr "char_FKExtraR_Thumb6_L_rotateY.a" "clipLibrary1.cel[0].cev[265].cevr"
		;
connectAttr "char_FKExtraR_Thumb6_L_rotateX.a" "clipLibrary1.cel[0].cev[266].cevr"
		;
connectAttr "char_FKCurveR_Middle5_L_scaleZ.a" "clipLibrary1.cel[0].cev[267].cevr"
		;
connectAttr "char_FKCurveR_Middle5_L_scaleY.a" "clipLibrary1.cel[0].cev[268].cevr"
		;
connectAttr "char_FKCurveR_Middle5_L_scaleX.a" "clipLibrary1.cel[0].cev[269].cevr"
		;
connectAttr "char_FKCurveR_Middle5_L_rotateZ.a" "clipLibrary1.cel[0].cev[270].cevr"
		;
connectAttr "char_FKCurveR_Middle5_L_rotateY.a" "clipLibrary1.cel[0].cev[271].cevr"
		;
connectAttr "char_FKCurveR_Middle5_L_rotateX.a" "clipLibrary1.cel[0].cev[272].cevr"
		;
connectAttr "char_FKExtraR_Middle5_L_rotateZ.a" "clipLibrary1.cel[0].cev[273].cevr"
		;
connectAttr "char_FKExtraR_Middle5_L_rotateY.a" "clipLibrary1.cel[0].cev[274].cevr"
		;
connectAttr "char_FKExtraR_Middle5_L_rotateX.a" "clipLibrary1.cel[0].cev[275].cevr"
		;
connectAttr "char_FKCurveR_Middle6_L_scaleZ.a" "clipLibrary1.cel[0].cev[276].cevr"
		;
connectAttr "char_FKCurveR_Middle6_L_scaleY.a" "clipLibrary1.cel[0].cev[277].cevr"
		;
connectAttr "char_FKCurveR_Middle6_L_scaleX.a" "clipLibrary1.cel[0].cev[278].cevr"
		;
connectAttr "char_FKCurveR_Middle6_L_rotateZ.a" "clipLibrary1.cel[0].cev[279].cevr"
		;
connectAttr "char_FKCurveR_Middle6_L_rotateY.a" "clipLibrary1.cel[0].cev[280].cevr"
		;
connectAttr "char_FKCurveR_Middle6_L_rotateX.a" "clipLibrary1.cel[0].cev[281].cevr"
		;
connectAttr "char_FKExtraR_Middle6_L_rotateZ.a" "clipLibrary1.cel[0].cev[282].cevr"
		;
connectAttr "char_FKExtraR_Middle6_L_rotateY.a" "clipLibrary1.cel[0].cev[283].cevr"
		;
connectAttr "char_FKExtraR_Middle6_L_rotateX.a" "clipLibrary1.cel[0].cev[284].cevr"
		;
connectAttr "char_FKCurveR_Wrist1_L_scaleZ.a" "clipLibrary1.cel[0].cev[285].cevr"
		;
connectAttr "char_FKCurveR_Wrist1_L_scaleY.a" "clipLibrary1.cel[0].cev[286].cevr"
		;
connectAttr "char_FKCurveR_Wrist1_L_scaleX.a" "clipLibrary1.cel[0].cev[287].cevr"
		;
connectAttr "char_FKCurveR_Wrist1_L_rotateZ.a" "clipLibrary1.cel[0].cev[288].cevr"
		;
connectAttr "char_FKCurveR_Wrist1_L_rotateY.a" "clipLibrary1.cel[0].cev[289].cevr"
		;
connectAttr "char_FKCurveR_Wrist1_L_rotateX.a" "clipLibrary1.cel[0].cev[290].cevr"
		;
connectAttr "char_FKExtraR_Wrist1_L_rotateZ.a" "clipLibrary1.cel[0].cev[291].cevr"
		;
connectAttr "char_FKExtraR_Wrist1_L_rotateY.a" "clipLibrary1.cel[0].cev[292].cevr"
		;
connectAttr "char_FKExtraR_Wrist1_L_rotateX.a" "clipLibrary1.cel[0].cev[293].cevr"
		;
connectAttr "char_FKCurveR_Hip1_L_scaleZ.a" "clipLibrary1.cel[0].cev[294].cevr";
connectAttr "char_FKCurveR_Hip1_L_scaleY.a" "clipLibrary1.cel[0].cev[295].cevr";
connectAttr "char_FKCurveR_Hip1_L_scaleX.a" "clipLibrary1.cel[0].cev[296].cevr";
connectAttr "char_FKCurveR_Hip1_L_rotateZ.a" "clipLibrary1.cel[0].cev[297].cevr"
		;
connectAttr "char_FKCurveR_Hip1_L_rotateY.a" "clipLibrary1.cel[0].cev[298].cevr"
		;
connectAttr "char_FKCurveR_Hip1_L_rotateX.a" "clipLibrary1.cel[0].cev[299].cevr"
		;
connectAttr "char_FKExtraR_Hip1_L_rotateZ.a" "clipLibrary1.cel[0].cev[300].cevr"
		;
connectAttr "char_FKExtraR_Hip1_L_rotateY.a" "clipLibrary1.cel[0].cev[301].cevr"
		;
connectAttr "char_FKExtraR_Hip1_L_rotateX.a" "clipLibrary1.cel[0].cev[302].cevr"
		;
connectAttr "char_FKCurveR_Knee1_L_scaleZ.a" "clipLibrary1.cel[0].cev[303].cevr"
		;
connectAttr "char_FKCurveR_Knee1_L_scaleY.a" "clipLibrary1.cel[0].cev[304].cevr"
		;
connectAttr "char_FKCurveR_Knee1_L_scaleX.a" "clipLibrary1.cel[0].cev[305].cevr"
		;
connectAttr "char_FKCurveR_Knee1_L_rotateZ.a" "clipLibrary1.cel[0].cev[306].cevr"
		;
connectAttr "char_FKExtraR_Knee1_L_rotateZ.a" "clipLibrary1.cel[0].cev[307].cevr"
		;
connectAttr "char_FKExtraR_Knee1_L_rotateY.a" "clipLibrary1.cel[0].cev[308].cevr"
		;
connectAttr "char_FKExtraR_Knee1_L_rotateX.a" "clipLibrary1.cel[0].cev[309].cevr"
		;
connectAttr "char_FKCurveR_Ankle1_L_scaleZ.a" "clipLibrary1.cel[0].cev[310].cevr"
		;
connectAttr "char_FKCurveR_Ankle1_L_scaleY.a" "clipLibrary1.cel[0].cev[311].cevr"
		;
connectAttr "char_FKCurveR_Ankle1_L_scaleX.a" "clipLibrary1.cel[0].cev[312].cevr"
		;
connectAttr "char_FKCurveR_Ankle1_L_rotateZ.a" "clipLibrary1.cel[0].cev[313].cevr"
		;
connectAttr "char_FKCurveR_Ankle1_L_rotateY.a" "clipLibrary1.cel[0].cev[314].cevr"
		;
connectAttr "char_FKCurveR_Ankle1_L_rotateX.a" "clipLibrary1.cel[0].cev[315].cevr"
		;
connectAttr "char_FKExtraR_Ankle1_L_rotateZ.a" "clipLibrary1.cel[0].cev[316].cevr"
		;
connectAttr "char_FKExtraR_Ankle1_L_rotateY.a" "clipLibrary1.cel[0].cev[317].cevr"
		;
connectAttr "char_FKExtraR_Ankle1_L_rotateX.a" "clipLibrary1.cel[0].cev[318].cevr"
		;
connectAttr "char_FKCurveR_Ball1_L_scaleZ.a" "clipLibrary1.cel[0].cev[319].cevr"
		;
connectAttr "char_FKCurveR_Ball1_L_scaleY.a" "clipLibrary1.cel[0].cev[320].cevr"
		;
connectAttr "char_FKCurveR_Ball1_L_scaleX.a" "clipLibrary1.cel[0].cev[321].cevr"
		;
connectAttr "char_FKCurveR_Ball1_L_rotateZ.a" "clipLibrary1.cel[0].cev[322].cevr"
		;
connectAttr "char_FKCurveR_Ball1_L_rotateY.a" "clipLibrary1.cel[0].cev[323].cevr"
		;
connectAttr "char_FKCurveR_Ball1_L_rotateX.a" "clipLibrary1.cel[0].cev[324].cevr"
		;
connectAttr "char_FKExtraR_Ball1_L_rotateZ.a" "clipLibrary1.cel[0].cev[325].cevr"
		;
connectAttr "char_FKExtraR_Ball1_L_rotateY.a" "clipLibrary1.cel[0].cev[326].cevr"
		;
connectAttr "char_FKExtraR_Ball1_L_rotateX.a" "clipLibrary1.cel[0].cev[327].cevr"
		;
connectAttr "char_FKCurveR_Clavicle1_R_scaleZ.a" "clipLibrary1.cel[0].cev[328].cevr"
		;
connectAttr "char_FKCurveR_Clavicle1_R_scaleY.a" "clipLibrary1.cel[0].cev[329].cevr"
		;
connectAttr "char_FKCurveR_Clavicle1_R_scaleX.a" "clipLibrary1.cel[0].cev[330].cevr"
		;
connectAttr "char_FKCurveR_Clavicle1_R_rotateZ.a" "clipLibrary1.cel[0].cev[331].cevr"
		;
connectAttr "char_FKCurveR_Clavicle1_R_rotateY.a" "clipLibrary1.cel[0].cev[332].cevr"
		;
connectAttr "char_FKCurveR_Clavicle1_R_rotateX.a" "clipLibrary1.cel[0].cev[333].cevr"
		;
connectAttr "char_FKExtraR_Clavicle1_R_rotateZ.a" "clipLibrary1.cel[0].cev[334].cevr"
		;
connectAttr "char_FKExtraR_Clavicle1_R_rotateY.a" "clipLibrary1.cel[0].cev[335].cevr"
		;
connectAttr "char_FKExtraR_Clavicle1_R_rotateX.a" "clipLibrary1.cel[0].cev[336].cevr"
		;
connectAttr "char_FKCurveR_Shoulder1_R_scaleZ.a" "clipLibrary1.cel[0].cev[337].cevr"
		;
connectAttr "char_FKCurveR_Shoulder1_R_scaleY.a" "clipLibrary1.cel[0].cev[338].cevr"
		;
connectAttr "char_FKCurveR_Shoulder1_R_scaleX.a" "clipLibrary1.cel[0].cev[339].cevr"
		;
connectAttr "char_FKCurveR_Shoulder1_R_rotateY.a" "clipLibrary1.cel[0].cev[340].cevr"
		;
connectAttr "char_FKExtraR_Shoulder1_R_rotateZ.a" "clipLibrary1.cel[0].cev[341].cevr"
		;
connectAttr "char_FKExtraR_Shoulder1_R_rotateY.a" "clipLibrary1.cel[0].cev[342].cevr"
		;
connectAttr "char_FKExtraR_Shoulder1_R_rotateX.a" "clipLibrary1.cel[0].cev[343].cevr"
		;
connectAttr "char_FKCurveR_Elbow1_R_scaleZ.a" "clipLibrary1.cel[0].cev[344].cevr"
		;
connectAttr "char_FKCurveR_Elbow1_R_scaleY.a" "clipLibrary1.cel[0].cev[345].cevr"
		;
connectAttr "char_FKCurveR_Elbow1_R_scaleX.a" "clipLibrary1.cel[0].cev[346].cevr"
		;
connectAttr "char_FKCurveR_Elbow1_R_rotateY.a" "clipLibrary1.cel[0].cev[347].cevr"
		;
connectAttr "char_FKExtraR_Elbow1_R_rotateZ.a" "clipLibrary1.cel[0].cev[348].cevr"
		;
connectAttr "char_FKExtraR_Elbow1_R_rotateY.a" "clipLibrary1.cel[0].cev[349].cevr"
		;
connectAttr "char_FKExtraR_Elbow1_R_rotateX.a" "clipLibrary1.cel[0].cev[350].cevr"
		;
connectAttr "char_FKCurveR_Thumb5_R_scaleZ.a" "clipLibrary1.cel[0].cev[351].cevr"
		;
connectAttr "char_FKCurveR_Thumb5_R_scaleY.a" "clipLibrary1.cel[0].cev[352].cevr"
		;
connectAttr "char_FKCurveR_Thumb5_R_scaleX.a" "clipLibrary1.cel[0].cev[353].cevr"
		;
connectAttr "char_FKCurveR_Thumb5_R_rotateZ.a" "clipLibrary1.cel[0].cev[354].cevr"
		;
connectAttr "char_FKCurveR_Thumb5_R_rotateY.a" "clipLibrary1.cel[0].cev[355].cevr"
		;
connectAttr "char_FKCurveR_Thumb5_R_rotateX.a" "clipLibrary1.cel[0].cev[356].cevr"
		;
connectAttr "char_FKExtraR_Thumb5_R_rotateZ.a" "clipLibrary1.cel[0].cev[357].cevr"
		;
connectAttr "char_FKExtraR_Thumb5_R_rotateY.a" "clipLibrary1.cel[0].cev[358].cevr"
		;
connectAttr "char_FKExtraR_Thumb5_R_rotateX.a" "clipLibrary1.cel[0].cev[359].cevr"
		;
connectAttr "char_FKCurveR_Thumb6_R_scaleZ.a" "clipLibrary1.cel[0].cev[360].cevr"
		;
connectAttr "char_FKCurveR_Thumb6_R_scaleY.a" "clipLibrary1.cel[0].cev[361].cevr"
		;
connectAttr "char_FKCurveR_Thumb6_R_scaleX.a" "clipLibrary1.cel[0].cev[362].cevr"
		;
connectAttr "char_FKCurveR_Thumb6_R_rotateZ.a" "clipLibrary1.cel[0].cev[363].cevr"
		;
connectAttr "char_FKCurveR_Thumb6_R_rotateY.a" "clipLibrary1.cel[0].cev[364].cevr"
		;
connectAttr "char_FKCurveR_Thumb6_R_rotateX.a" "clipLibrary1.cel[0].cev[365].cevr"
		;
connectAttr "char_FKExtraR_Thumb6_R_rotateZ.a" "clipLibrary1.cel[0].cev[366].cevr"
		;
connectAttr "char_FKExtraR_Thumb6_R_rotateY.a" "clipLibrary1.cel[0].cev[367].cevr"
		;
connectAttr "char_FKExtraR_Thumb6_R_rotateX.a" "clipLibrary1.cel[0].cev[368].cevr"
		;
connectAttr "char_FKCurveR_Middle5_R_scaleZ.a" "clipLibrary1.cel[0].cev[369].cevr"
		;
connectAttr "char_FKCurveR_Middle5_R_scaleY.a" "clipLibrary1.cel[0].cev[370].cevr"
		;
connectAttr "char_FKCurveR_Middle5_R_scaleX.a" "clipLibrary1.cel[0].cev[371].cevr"
		;
connectAttr "char_FKCurveR_Middle5_R_rotateZ.a" "clipLibrary1.cel[0].cev[372].cevr"
		;
connectAttr "char_FKCurveR_Middle5_R_rotateY.a" "clipLibrary1.cel[0].cev[373].cevr"
		;
connectAttr "char_FKCurveR_Middle5_R_rotateX.a" "clipLibrary1.cel[0].cev[374].cevr"
		;
connectAttr "char_FKExtraR_Middle5_R_rotateZ.a" "clipLibrary1.cel[0].cev[375].cevr"
		;
connectAttr "char_FKExtraR_Middle5_R_rotateY.a" "clipLibrary1.cel[0].cev[376].cevr"
		;
connectAttr "char_FKExtraR_Middle5_R_rotateX.a" "clipLibrary1.cel[0].cev[377].cevr"
		;
connectAttr "char_FKCurveR_Middle6_R_scaleZ.a" "clipLibrary1.cel[0].cev[378].cevr"
		;
connectAttr "char_FKCurveR_Middle6_R_scaleY.a" "clipLibrary1.cel[0].cev[379].cevr"
		;
connectAttr "char_FKCurveR_Middle6_R_scaleX.a" "clipLibrary1.cel[0].cev[380].cevr"
		;
connectAttr "char_FKCurveR_Middle6_R_rotateZ.a" "clipLibrary1.cel[0].cev[381].cevr"
		;
connectAttr "char_FKCurveR_Middle6_R_rotateY.a" "clipLibrary1.cel[0].cev[382].cevr"
		;
connectAttr "char_FKCurveR_Middle6_R_rotateX.a" "clipLibrary1.cel[0].cev[383].cevr"
		;
connectAttr "char_FKExtraR_Middle6_R_rotateZ.a" "clipLibrary1.cel[0].cev[384].cevr"
		;
connectAttr "char_FKExtraR_Middle6_R_rotateY.a" "clipLibrary1.cel[0].cev[385].cevr"
		;
connectAttr "char_FKExtraR_Middle6_R_rotateX.a" "clipLibrary1.cel[0].cev[386].cevr"
		;
connectAttr "char_FKCurveR_Wrist1_R_scaleZ.a" "clipLibrary1.cel[0].cev[387].cevr"
		;
connectAttr "char_FKCurveR_Wrist1_R_scaleY.a" "clipLibrary1.cel[0].cev[388].cevr"
		;
connectAttr "char_FKCurveR_Wrist1_R_scaleX.a" "clipLibrary1.cel[0].cev[389].cevr"
		;
connectAttr "char_FKCurveR_Wrist1_R_rotateZ.a" "clipLibrary1.cel[0].cev[390].cevr"
		;
connectAttr "char_FKCurveR_Wrist1_R_rotateY.a" "clipLibrary1.cel[0].cev[391].cevr"
		;
connectAttr "char_FKCurveR_Wrist1_R_rotateX.a" "clipLibrary1.cel[0].cev[392].cevr"
		;
connectAttr "char_FKExtraR_Wrist1_R_rotateZ.a" "clipLibrary1.cel[0].cev[393].cevr"
		;
connectAttr "char_FKExtraR_Wrist1_R_rotateY.a" "clipLibrary1.cel[0].cev[394].cevr"
		;
connectAttr "char_FKExtraR_Wrist1_R_rotateX.a" "clipLibrary1.cel[0].cev[395].cevr"
		;
connectAttr "char_FKCurveR_Hip1_R_scaleZ.a" "clipLibrary1.cel[0].cev[396].cevr";
connectAttr "char_FKCurveR_Hip1_R_scaleY.a" "clipLibrary1.cel[0].cev[397].cevr";
connectAttr "char_FKCurveR_Hip1_R_scaleX.a" "clipLibrary1.cel[0].cev[398].cevr";
connectAttr "char_FKCurveR_Hip1_R_rotateZ.a" "clipLibrary1.cel[0].cev[399].cevr"
		;
connectAttr "char_FKCurveR_Hip1_R_rotateY.a" "clipLibrary1.cel[0].cev[400].cevr"
		;
connectAttr "char_FKCurveR_Hip1_R_rotateX.a" "clipLibrary1.cel[0].cev[401].cevr"
		;
connectAttr "char_FKExtraR_Hip1_R_rotateZ.a" "clipLibrary1.cel[0].cev[402].cevr"
		;
connectAttr "char_FKExtraR_Hip1_R_rotateY.a" "clipLibrary1.cel[0].cev[403].cevr"
		;
connectAttr "char_FKExtraR_Hip1_R_rotateX.a" "clipLibrary1.cel[0].cev[404].cevr"
		;
connectAttr "char_FKCurveR_Knee1_R_scaleZ.a" "clipLibrary1.cel[0].cev[405].cevr"
		;
connectAttr "char_FKCurveR_Knee1_R_scaleY.a" "clipLibrary1.cel[0].cev[406].cevr"
		;
connectAttr "char_FKCurveR_Knee1_R_scaleX.a" "clipLibrary1.cel[0].cev[407].cevr"
		;
connectAttr "char_FKCurveR_Knee1_R_rotateZ.a" "clipLibrary1.cel[0].cev[408].cevr"
		;
connectAttr "char_FKExtraR_Knee1_R_rotateZ.a" "clipLibrary1.cel[0].cev[409].cevr"
		;
connectAttr "char_FKExtraR_Knee1_R_rotateY.a" "clipLibrary1.cel[0].cev[410].cevr"
		;
connectAttr "char_FKExtraR_Knee1_R_rotateX.a" "clipLibrary1.cel[0].cev[411].cevr"
		;
connectAttr "char_FKCurveR_Ankle1_R_scaleZ.a" "clipLibrary1.cel[0].cev[412].cevr"
		;
connectAttr "char_FKCurveR_Ankle1_R_scaleY.a" "clipLibrary1.cel[0].cev[413].cevr"
		;
connectAttr "char_FKCurveR_Ankle1_R_scaleX.a" "clipLibrary1.cel[0].cev[414].cevr"
		;
connectAttr "char_FKCurveR_Ankle1_R_rotateZ.a" "clipLibrary1.cel[0].cev[415].cevr"
		;
connectAttr "char_FKCurveR_Ankle1_R_rotateY.a" "clipLibrary1.cel[0].cev[416].cevr"
		;
connectAttr "char_FKCurveR_Ankle1_R_rotateX.a" "clipLibrary1.cel[0].cev[417].cevr"
		;
connectAttr "char_FKExtraR_Ankle1_R_rotateZ.a" "clipLibrary1.cel[0].cev[418].cevr"
		;
connectAttr "char_FKExtraR_Ankle1_R_rotateY.a" "clipLibrary1.cel[0].cev[419].cevr"
		;
connectAttr "char_FKExtraR_Ankle1_R_rotateX.a" "clipLibrary1.cel[0].cev[420].cevr"
		;
connectAttr "char_FKCurveR_Ball1_R_scaleZ.a" "clipLibrary1.cel[0].cev[421].cevr"
		;
connectAttr "char_FKCurveR_Ball1_R_scaleY.a" "clipLibrary1.cel[0].cev[422].cevr"
		;
connectAttr "char_FKCurveR_Ball1_R_scaleX.a" "clipLibrary1.cel[0].cev[423].cevr"
		;
connectAttr "char_FKCurveR_Ball1_R_rotateZ.a" "clipLibrary1.cel[0].cev[424].cevr"
		;
connectAttr "char_FKCurveR_Ball1_R_rotateY.a" "clipLibrary1.cel[0].cev[425].cevr"
		;
connectAttr "char_FKCurveR_Ball1_R_rotateX.a" "clipLibrary1.cel[0].cev[426].cevr"
		;
connectAttr "char_FKExtraR_Ball1_R_rotateZ.a" "clipLibrary1.cel[0].cev[427].cevr"
		;
connectAttr "char_FKExtraR_Ball1_R_rotateY.a" "clipLibrary1.cel[0].cev[428].cevr"
		;
connectAttr "char_FKExtraR_Ball1_R_rotateX.a" "clipLibrary1.cel[0].cev[429].cevr"
		;
connectAttr "char_All_scaleZ.a" "clipLibrary1.cel[0].cev[430].cevr";
connectAttr "char_All_scaleY.a" "clipLibrary1.cel[0].cev[431].cevr";
connectAttr "char_All_scaleX.a" "clipLibrary1.cel[0].cev[432].cevr";
connectAttr "char_All_rotateZ.a" "clipLibrary1.cel[0].cev[433].cevr";
connectAttr "char_All_rotateY.a" "clipLibrary1.cel[0].cev[434].cevr";
connectAttr "char_All_rotateX.a" "clipLibrary1.cel[0].cev[435].cevr";
connectAttr "char_All_translateZ.a" "clipLibrary1.cel[0].cev[436].cevr";
connectAttr "char_All_translateY.a" "clipLibrary1.cel[0].cev[437].cevr";
connectAttr "char_All_translateX.a" "clipLibrary1.cel[0].cev[438].cevr";
connectAttr "char_All_visibility.a" "clipLibrary1.cel[0].cev[439].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of maugli_idle2.ma
