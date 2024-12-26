//Maya ASCII 2008 scene
//Name: maugli_attack.ma
//Last modified: Wed, Feb 04, 2009 01:04:44 PM
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
		1 73 "FKCurveR_Shoulder1_L.rotateZ" 2 226 "FKCurveR_Shoulder1_L.rotateX" 
		2 227 "FKCurveR_Shoulder1_R.rotateZ" 2 228 "FKCurveR_Shoulder1_R.rotateX" 
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
createNode animClip -n "maugli_attackSource";
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
	setAttr ".se" 42;
	setAttr ".ci" no;
createNode animCurveTU -n "char_AimCurveEye_Right1_M_follow";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 10 5 10 9 10 12 10 17 10 20 10 23 10 
		27 10 36 10 42 10;
	setAttr -s 10 ".kit[1:9]"  10 1 3 10 3 3 3 3 
		1;
	setAttr -s 10 ".kot[1:9]"  10 1 3 10 3 3 3 3 
		1;
	setAttr -s 10 ".kix[2:9]"  1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[2:9]"  0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[2:9]"  1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[2:9]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_AimCurveEye_Right1_M_cross";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 5 1 9 1 12 1 17 1 20 1 23 1 27 1 36 
		1 42 1;
	setAttr -s 10 ".kit[1:9]"  10 1 3 10 3 3 3 3 
		1;
	setAttr -s 10 ".kot[1:9]"  10 1 3 10 3 3 3 3 
		1;
	setAttr -s 10 ".kix[2:9]"  1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[2:9]"  0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[2:9]"  1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[2:9]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_AimCurveEye_Right1_M_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 3 -0.098330130205981886 5 -0.0044844386818756604 
		9 0 12 0 15 -0.0051972550483573802 17 0 20 -0.050695399327225429 23 0 27 0 31 -0.037596559596919064 
		36 0.0051546649538099891 42 0;
	setAttr -s 13 ".kit[1:12]"  10 10 1 3 10 10 3 3 
		3 10 3 1;
	setAttr -s 13 ".kot[1:12]"  10 10 1 3 10 10 3 3 
		3 10 3 1;
	setAttr -s 13 ".kix[3:12]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[3:12]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[3:12]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[3:12]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_AimCurveEye_Right1_M_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 3 0.099932738046869779 5 -0.13660715730243475 
		9 0 12 0 15 -0.35751856195622522 17 0 20 -0.15160454777933444 23 0 27 0 31 -0.17036749883266628 
		36 -0.042853001544772097 42 0;
	setAttr -s 13 ".kit[1:12]"  10 10 1 3 10 10 3 3 
		3 10 3 1;
	setAttr -s 13 ".kot[1:12]"  10 10 1 3 10 10 3 3 
		3 10 3 1;
	setAttr -s 13 ".kix[3:12]"  1 1 1 0.62913984060287476 1 1 1 0.98995143175125122 
		1 1;
	setAttr -s 13 ".kiy[3:12]"  0 0 0 0.77729213237762451 0 0 0 -0.14140793681144714 
		0 0;
	setAttr -s 13 ".kox[3:12]"  1 1 1 0.62913984060287476 1 1 1 0.98995143175125122 
		1 1;
	setAttr -s 13 ".koy[3:12]"  0 0 0 0.77729213237762451 0 0 0 -0.14140793681144714 
		0 0;
createNode animCurveTL -n "char_AimCurveEye_Right1_M_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 3 0.00064102816145426421 5 0.0018657295618841594 
		9 0 12 0 15 0.071490222949566029 17 0 20 -0.0058619912590536314 23 0 27 0 31 -0.0079582595575412238 
		36 -1.0735424795098479e-005 42 0;
	setAttr -s 13 ".kit[1:12]"  10 10 1 3 10 10 3 3 
		3 10 3 1;
	setAttr -s 13 ".kot[1:12]"  10 10 1 3 10 10 3 3 
		3 10 3 1;
	setAttr -s 13 ".kix[3:12]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[3:12]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[3:12]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[3:12]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveArm_L_IKVis";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 9 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 5 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 0 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveArm_L_FKVis";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 9 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 5 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 0 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveArm_L_FKIKBlend";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveLeg_L_IKVis";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 9 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 5 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 0 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveLeg_L_FKVis";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 9 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 5 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 0 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveLeg_L_FKIKBlend";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 10 9 10 12 10 17 10 20 10 23 10 27 10 
		36 10 42 10;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveArm_R_IKVis";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 9 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 5 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 0 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveArm_R_FKVis";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 9 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 5 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 0 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveArm_R_FKIKBlend";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveLeg_R_IKVis";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 9 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 5 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 0 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveLeg_R_FKVis";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 9 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 5 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 0 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveLeg_R_FKIKBlend";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 10 9 10 12 10 17 10 20 10 23 10 27 10 
		36 10 42 10;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKPoleVectorCurveArm_L_follow";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveArm_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveArm_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveArm_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraArm_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraArm_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraArm_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveArm_L_antiPop";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveArm_L_stretchy";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveArm_L_follow";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveArm_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveArm_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveArm_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveArm_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveArm_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveArm_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraArm_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraArm_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraArm_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraArm_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraArm_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraArm_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKPoleVectorCurveLeg_L_follow";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 10 9 10 12 10 17 10 20 10 23 10 27 10 
		36 10 42 10;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraLeg_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraLeg_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraLeg_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveLeg_L_antiPop";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveLeg_L_stretchy";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveLeg_L_swivel";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveLeg_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveLeg_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 43.567069197048298 9 43.567069197048298 
		12 43.567069197048298 17 43.567069197048298 20 43.567069197048298 23 43.567069197048298 
		27 43.567069197048298 36 43.567069197048298 42 43.567069197048298;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveLeg_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveLeg_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.28844199405395621 9 -0.28844199405395621 
		12 -0.28844199405395621 17 -0.28844199405395621 20 -0.28844199405395621 23 -0.28844199405395621 
		27 -0.28844199405395621 36 -0.28844199405395621 42 -0.28844199405395621;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveLeg_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveLeg_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.087756482507145378 9 0.087756482507145378 
		12 0.087756482507145378 17 0.087756482507145378 20 0.087756482507145378 23 0.087756482507145378 
		27 0.087756482507145378 36 0.087756482507145378 42 0.087756482507145378;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraLeg_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraLeg_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraLeg_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraLeg_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraLeg_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraLeg_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKPoleVectorCurveArm_R_follow";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveArm_R_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 -0.80651909766667318 12 -0.80651909766667318 
		17 -0.80651909766667318 20 -0.80651909766667318 23 -0.80651909766667318 27 -0.80651909766667318 
		36 -0.80651909766667318 42 0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveArm_R_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 -1.0333372441880238 12 -1.0333372441880238 
		17 -1.0333372441880238 20 -1.0333372441880238 23 -1.0333372441880238 27 -1.0333372441880238 
		36 -1.0333372441880238 42 0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveArm_R_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraArm_R_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraArm_R_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraArm_R_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveArm_R_antiPop";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveArm_R_stretchy";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveArm_R_follow";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveArm_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveArm_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveArm_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveArm_R_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveArm_R_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveArm_R_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraArm_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraArm_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraArm_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraArm_R_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraArm_R_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraArm_R_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKPoleVectorCurveLeg_R_follow";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 10 9 10 12 10 17 10 20 10 23 10 27 10 
		36 10 42 10;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_R_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_R_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_R_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraLeg_R_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraLeg_R_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraLeg_R_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveLeg_R_antiPop";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveLeg_R_stretchy";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveLeg_R_swivel";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveLeg_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveLeg_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveLeg_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveLeg_R_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.33022172654533777 9 0.33022172654533777 
		12 0.33022172654533777 17 0.33022172654533777 20 0.33022172654533777 23 0.33022172654533777 
		27 0.33022172654533777 36 0.33022172654533777 42 0.33022172654533777;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveLeg_R_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveLeg_R_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.13911956167322667 9 -0.13911956167322667 
		12 -0.13911956167322667 17 -0.13911956167322667 20 -0.13911956167322667 23 -0.13911956167322667 
		27 -0.13911956167322667 36 -0.13911956167322667 42 -0.13911956167322667;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraLeg_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraLeg_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraLeg_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraLeg_R_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraLeg_R_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraLeg_R_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveTooth1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 12 1 14 1 17 1 20 1 23 1 27 1 36 1 
		42 1;
	setAttr -s 9 ".kit[2:8]"  1 10 3 3 3 3 1;
	setAttr -s 9 ".kot[2:8]"  1 10 3 3 3 3 1;
	setAttr -s 9 ".kix[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[2:8]"  0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[2:8]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveTooth1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 12 1 14 1 17 1 20 1 23 1 27 1 36 1 
		42 1;
	setAttr -s 9 ".kit[2:8]"  1 10 3 3 3 3 1;
	setAttr -s 9 ".kot[2:8]"  1 10 3 3 3 3 1;
	setAttr -s 9 ".kix[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[2:8]"  0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[2:8]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveTooth1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 12 1 14 1 17 1 20 1 23 1 27 1 36 1 
		42 1;
	setAttr -s 9 ".kit[2:8]"  1 10 3 3 3 3 1;
	setAttr -s 9 ".kot[2:8]"  1 10 3 3 3 3 1;
	setAttr -s 9 ".kix[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[2:8]"  0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[2:8]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveTooth1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -27.541549434058677 6 8.5802902605943689 
		12 -69.10088669565576 14 8.0259526563423993 17 -11.433423741937943 20 -23.867070987228868 
		23 -69.362464001678944 27 -28.797340134102253 30 -38.796210369001784 33 -15.138671077050615 
		36 -25.538889936742681 39 -39.725039904647929 42 -27.541549434058677;
	setAttr -s 13 ".kit[1:12]"  10 3 1 10 3 3 3 10 
		10 3 10 1;
	setAttr -s 13 ".kot[1:12]"  10 3 1 10 3 3 3 10 
		10 3 10 1;
	setAttr -s 13 ".kix[3:12]"  1 0.33813604712486267 1 1 1 0.6427275538444519 
		0.65393537282943726 1 0.98506981134414673 1;
	setAttr -s 13 ".kiy[3:12]"  0 -0.94109725952148438 0 0 0 0.7660948634147644 
		0.75655043125152588 0 -0.17215578258037567 0;
	setAttr -s 13 ".kox[3:12]"  1 0.33813604712486267 1 1 1 0.6427275538444519 
		0.65393537282943726 1 0.98506981134414673 1;
	setAttr -s 13 ".koy[3:12]"  0 -0.94109725952148438 0 0 0 0.7660948634147644 
		0.75655043125152588 0 -0.17215578258037567 0;
createNode animCurveTA -n "char_FKCurveTooth1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 8.4599709196312922 6 11.048078024375929 
		12 4.9239946860727963 14 1.3790349658998506 17 -19.000189528533628 20 36.124214586630572 
		23 -17.164022145063171 27 24.077612137520855 30 -0.12364666191881581 33 4.8530503846892978 
		36 13.084807433598165 39 9.4031949215802602 42 8.4599709196312922;
	setAttr -s 13 ".kit[1:12]"  10 3 1 10 3 3 3 10 
		10 3 10 1;
	setAttr -s 13 ".kot[1:12]"  10 3 1 10 3 3 3 10 
		10 3 10 1;
	setAttr -s 13 ".kix[3:12]"  1 0.31321099400520325 1 1 1 0.51201051473617554 
		0.65531682968139648 1 1 1;
	setAttr -s 13 ".kiy[3:12]"  0 0.9496835470199585 0 0 0 -0.85897916555404663 
		0.75535410642623901 0 0 0;
	setAttr -s 13 ".kox[3:12]"  1 0.31321099400520325 1 1 1 0.51201051473617554 
		0.65531682968139648 1 1 1;
	setAttr -s 13 ".koy[3:12]"  0 0.9496835470199585 0 0 0 -0.85897916555404663 
		0.75535410642623901 0 0 0;
createNode animCurveTA -n "char_FKCurveTooth1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 6.8137435045968227 6 2.5291732906843438 
		12 -5.8830798092889944 14 4.0997967922338443 17 -7.990926157558591 20 13.666955388705983 
		23 12.949789200140968 27 0.41492619154254412 30 5.4352804950187661 33 7.8473983067194695 
		36 9.0999193016547455 39 -8.426659547906544 42 6.8137435045968227;
	setAttr -s 13 ".kit[1:12]"  10 3 1 10 3 3 3 10 
		10 3 10 1;
	setAttr -s 13 ".kot[1:12]"  10 3 1 10 3 3 3 10 
		10 3 10 1;
	setAttr -s 13 ".kix[3:12]"  1 0.76763248443603516 1 1 1 1 1 1 0.98067355155944824 
		1;
	setAttr -s 13 ".kiy[3:12]"  0 0.64089024066925049 0 0 0 0 0 0 -0.19565080106258392 
		0;
	setAttr -s 13 ".kox[3:12]"  1 0.76763248443603516 1 1 1 1 1 1 0.98067355155944824 
		1;
	setAttr -s 13 ".koy[3:12]"  0 0.64089024066925049 0 0 0 0 0 0 -0.19565080106258392 
		0;
createNode animCurveTL -n "char_FKCurveTooth1_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -0.028863465787140358 6 -0.091073054744884641 
		12 -0.04653174737723198 14 -0.028863465787140358 17 -0.028029580965363111 20 -0.028863465787140358 
		23 -0.043433965367030362 27 -0.028863465787140358 30 -0.031620284950151969 36 -0.039250141713495348 
		42 -0.028863465787140358;
	setAttr -s 11 ".kit[1:10]"  10 3 1 10 3 3 3 10 
		3 1;
	setAttr -s 11 ".kot[1:10]"  10 3 1 10 3 3 3 10 
		3 1;
	setAttr -s 11 ".kix[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[3:10]"  0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[3:10]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKCurveTooth1_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -0.023775464972591611 6 -0.0097006006052766137 
		12 -0.050572926271469955 14 -0.023775464972591611 17 -0.012603345928248607 20 -0.023775464972591611 
		23 -0.017889043022686086 27 -0.023775464972591611 30 -0.047733729481177156 36 -0.039698589716682206 
		42 -0.023775464972591611;
	setAttr -s 11 ".kit[1:10]"  10 3 1 10 3 3 3 10 
		3 1;
	setAttr -s 11 ".kot[1:10]"  10 3 1 10 3 3 3 10 
		3 1;
	setAttr -s 11 ".kix[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[3:10]"  0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[3:10]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKCurveTooth1_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -0.052162964274260919 6 0.0068343795400855594 
		12 -0.12533239361746645 14 -0.052162964274260919 17 -0.09242030418061481 20 -0.052162964274260919 
		23 -0.13741359615144641 27 -0.052162964274260919 30 -0.070814674602396141 36 -0.069482764048043225 
		42 -0.052162964274260919;
	setAttr -s 11 ".kit[1:10]"  10 3 1 10 3 3 3 10 
		3 1;
	setAttr -s 11 ".kot[1:10]"  10 3 1 10 3 3 3 10 
		3 1;
	setAttr -s 11 ".kix[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[3:10]"  0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[3:10]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKExtraTooth1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKExtraTooth1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKExtraTooth1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraTooth1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraTooth1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraTooth1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKExtraTooth1_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKExtraTooth1_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKExtraTooth1_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "FKCurveR_Shoulder1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -60.970082317325229 3 -39.157392531169037 
		8 -14.571774992818323 12 -15.147443948609196 17 18.786516817601328 20 25.136549957559932 
		23 23.061105946040495 27 23.061105946040495 31 0.30770430785842584 34 -25.530615019049694 
		42 -60.970082317325229;
	setAttr -s 11 ".kit[2:10]"  10 3 10 3 3 3 10 10 
		1;
	setAttr -s 11 ".kot[2:10]"  10 3 10 3 3 3 10 10 
		1;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[10]"  1;
	setAttr -s 11 ".koy[10]"  0;
createNode animCurveTA -n "FKCurveR_Shoulder1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -5.1174438057844904 3 2.1997779774519839 
		8 57.112493850510418 12 -11.947281338413678 17 23.817903109433793 20 32.972944284836721 
		23 31.765246771002637 27 31.765246771002637 31 21.536281652691454 34 44.819116476904583 
		42 -5.1174438057844904;
	setAttr -s 11 ".kit[2:10]"  10 3 10 3 3 3 10 10 
		1;
	setAttr -s 11 ".kot[2:10]"  10 3 10 3 3 3 10 10 
		1;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[10]"  1;
	setAttr -s 11 ".koy[10]"  0;
createNode animCurveTA -n "FKCurveR_Shoulder1_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 -36.986337964869008 3 -31.614264523768551 
		8 -62.969410937841388 12 -59.522184518546084 14 -55.037925415981107 16 -7.3012596305980297 
		17 4.8482988835022391 20 5.5736428565451055 23 1.8800141319440642 27 1.8800141319440642 
		30 2.8695882594134083 33 -10.774622599650353 38 -50.31077401886732 42 -36.986337964869008;
	setAttr -s 14 ".kit[0:13]"  3 3 10 3 10 10 10 3 
		3 3 10 10 10 1;
	setAttr -s 14 ".kot[0:13]"  3 3 10 3 10 10 10 3 
		3 3 10 10 10 1;
	setAttr -s 14 ".kix[13]"  1;
	setAttr -s 14 ".kiy[13]"  0;
	setAttr -s 14 ".kox[13]"  1;
	setAttr -s 14 ".koy[13]"  0;
createNode animCurveTA -n "FKCurveR_Shoulder1_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 10.660406869524985 3 -24.642255266631452 
		8 45.438841565665847 12 -33.403655711806735 14 -18.834742025703406 16 32.979396125127124 
		17 53.920291883939228 20 62.387048132527489 23 60.412055041306466 27 60.412055041306466 
		30 58.682047046153201 33 71.347882105520711 38 32.442840882299457 42 10.660406869524985;
	setAttr -s 14 ".kit[0:13]"  3 3 10 3 10 10 10 3 
		3 3 10 10 10 1;
	setAttr -s 14 ".kot[0:13]"  3 3 10 3 10 10 10 3 
		3 3 10 10 10 1;
	setAttr -s 14 ".kix[13]"  1;
	setAttr -s 14 ".kiy[13]"  0;
	setAttr -s 14 ".kox[13]"  1;
	setAttr -s 14 ".koy[13]"  0;
createNode animCurveTA -n "char_FKExtraPen1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraPen1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraPen1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraPen1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraPen1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraPen1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveHair1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 12 1 17 1 23 1 27 1 36 1 42 1;
	setAttr -s 7 ".kit[2:6]"  10 3 3 3 1;
	setAttr -s 7 ".kot[2:6]"  10 3 3 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTU -n "char_FKCurveHair1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 12 1 17 1 23 1 27 1 36 1 42 1;
	setAttr -s 7 ".kit[2:6]"  10 3 3 3 1;
	setAttr -s 7 ".kot[2:6]"  10 3 3 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTU -n "char_FKCurveHair1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 12 1 17 1 23 1 27 1 36 1 42 1;
	setAttr -s 7 ".kit[2:6]"  10 3 3 3 1;
	setAttr -s 7 ".kot[2:6]"  10 3 3 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "char_FKCurveHair1_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 30.524599611915377 3 5.5429894013368441 
		7 18.498408662436493 10 49.375458984436662 12 90.432028644184911 17 97.445491285110975 
		23 21.087533400117518 27 24.742540742129744 32 24.670898793004955 36 19.266736482624157 
		39 21.677083202318556 42 30.524599611915377;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 3 10 3 3 
		10 3 10 1;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 3 10 3 3 
		10 3 10 1;
	setAttr -s 12 ".kix[11]"  1;
	setAttr -s 12 ".kiy[11]"  0;
	setAttr -s 12 ".kox[11]"  1;
	setAttr -s 12 ".koy[11]"  0;
createNode animCurveTA -n "char_FKCurveHair1_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -20.226445302148342 3 -10.212490691375768 
		7 3.9490296677899912 10 -13.264900933474937 12 -26.315887475171731 17 -5.952444586615746 
		23 20.359631518282274 27 -3.1815135075346861 32 -4.0431248720744879 36 -16.155450097095493 
		39 -17.135645418096232 42 -20.226445302148342;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 3 10 3 3 
		10 3 10 1;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 3 10 3 3 
		10 3 10 1;
	setAttr -s 12 ".kix[11]"  1;
	setAttr -s 12 ".kiy[11]"  0;
	setAttr -s 12 ".kox[11]"  1;
	setAttr -s 12 ".koy[11]"  0;
createNode animCurveTA -n "char_FKCurveHair1_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 17.701770262088139 3 18.43272515574445 
		7 18.683992736659185 10 0.41580381820428647 12 -8.115178764866851 17 0.53617946710293307 
		23 -25.637026091564636 27 8.1814655157432359 32 3.772585684982642 36 22.958394015791377 
		39 11.022316512300151 42 17.701770262088139;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 3 10 3 3 
		10 3 10 1;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 3 10 3 3 
		10 3 10 1;
	setAttr -s 12 ".kix[11]"  1;
	setAttr -s 12 ".kiy[11]"  0;
	setAttr -s 12 ".kox[11]"  1;
	setAttr -s 12 ".koy[11]"  0;
createNode animCurveTA -n "char_FKExtraHair1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraHair1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraHair1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveHead1_M_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 42 1;
	setAttr -s 8 ".kit[1:7]"  1 3 10 3 3 3 1;
	setAttr -s 8 ".kot[1:7]"  1 3 10 3 3 3 1;
	setAttr -s 8 ".kix[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".kiy[1:7]"  0 0 0 0 0 0 0;
	setAttr -s 8 ".kox[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".koy[1:7]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveHead1_M_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 42 1;
	setAttr -s 8 ".kit[1:7]"  1 3 10 3 3 3 1;
	setAttr -s 8 ".kot[1:7]"  1 3 10 3 3 3 1;
	setAttr -s 8 ".kix[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".kiy[1:7]"  0 0 0 0 0 0 0;
	setAttr -s 8 ".kox[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".koy[1:7]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveHead1_M_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 42 1;
	setAttr -s 8 ".kit[1:7]"  1 3 10 3 3 3 1;
	setAttr -s 8 ".kot[1:7]"  1 3 10 3 3 3 1;
	setAttr -s 8 ".kix[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".kiy[1:7]"  0 0 0 0 0 0 0;
	setAttr -s 8 ".kox[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".koy[1:7]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveHead1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 19.649599090973453 3 2.8897612095118701 
		9 -12.711148402593016 12 -12.711148402593016 17 -9.3505609836591539 20 -10.489027536102594 
		23 -10.762570033299438 27 -10.762570033299438 36 3.3741991673347469 42 19.649599090973453;
	setAttr -s 10 ".kit[1:9]"  10 1 3 10 3 3 3 10 
		1;
	setAttr -s 10 ".kot[1:9]"  10 1 3 10 3 3 3 10 
		1;
	setAttr -s 10 ".kix[2:9]"  1 1 1 1 1 1 0.68567776679992676 1;
	setAttr -s 10 ".kiy[2:9]"  0 0 0 0 0 0 0.72790521383285522 0;
	setAttr -s 10 ".kox[2:9]"  1 1 1 1 1 1 0.68567776679992676 1;
	setAttr -s 10 ".koy[2:9]"  0 0 0 0 0 0 0.72790521383285522 0;
createNode animCurveTA -n "char_FKCurveHead1_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -30.214171376615486 3 -21.967249549556939 
		9 -13.753503568705142 12 -13.753503568705142 17 -4.184005126421253 20 -7.3891637036425433 
		23 -7.1933132812450209 27 -7.1933132812450209 36 -22.271317716063333 42 -30.214171376615486;
	setAttr -s 10 ".kit[1:9]"  10 1 3 10 3 3 3 10 
		1;
	setAttr -s 10 ".kot[1:9]"  10 1 3 10 3 3 3 10 
		1;
	setAttr -s 10 ".kix[2:9]"  1 1 0.92311668395996094 1 1 1 0.77950578927993774 
		1;
	setAttr -s 10 ".kiy[2:9]"  0 0 0.38451969623565674 0 0 0 -0.62639492750167847 
		0;
	setAttr -s 10 ".kox[2:9]"  1 1 0.92311668395996094 1 1 1 0.77950578927993774 
		1;
	setAttr -s 10 ".koy[2:9]"  0 0 0.38451969623565674 0 0 0 -0.62639492750167847 
		0;
createNode animCurveTA -n "char_FKCurveHead1_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -39.886477028299176 3 -2.6323891530111339 
		9 12.446794108168179 12 12.446794108168179 17 52.364525266864028 20 11.167429984683087 
		23 13.834248631199793 27 13.834248631199793 36 -7.1777112803729528 42 -39.886477028299176;
	setAttr -s 10 ".kit[1:9]"  10 1 3 10 3 3 3 10 
		1;
	setAttr -s 10 ".kot[1:9]"  10 1 3 10 3 3 3 10 
		1;
	setAttr -s 10 ".kix[2:9]"  1 1 0.99651259183883667 1 1 1 0.47054773569107056 
		1;
	setAttr -s 10 ".kiy[2:9]"  0 0 -0.083442166447639465 0 0 0 -0.88237446546554565 
		0;
	setAttr -s 10 ".kox[2:9]"  1 1 0.99651259183883667 1 1 1 0.47054773569107056 
		1;
	setAttr -s 10 ".koy[2:9]"  0 0 -0.083442166447639465 0 0 0 -0.88237446546554565 
		0;
createNode animCurveTA -n "char_FKExtraHead1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraHead1_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraHead1_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveNeck1_M_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 42 1;
	setAttr -s 8 ".kit[1:7]"  1 3 10 3 3 3 1;
	setAttr -s 8 ".kot[1:7]"  1 3 10 3 3 3 1;
	setAttr -s 8 ".kix[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".kiy[1:7]"  0 0 0 0 0 0 0;
	setAttr -s 8 ".kox[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".koy[1:7]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveNeck1_M_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 42 1;
	setAttr -s 8 ".kit[1:7]"  1 3 10 3 3 3 1;
	setAttr -s 8 ".kot[1:7]"  1 3 10 3 3 3 1;
	setAttr -s 8 ".kix[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".kiy[1:7]"  0 0 0 0 0 0 0;
	setAttr -s 8 ".kox[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".koy[1:7]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveNeck1_M_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 42 1;
	setAttr -s 8 ".kit[1:7]"  1 3 10 3 3 3 1;
	setAttr -s 8 ".kot[1:7]"  1 3 10 3 3 3 1;
	setAttr -s 8 ".kix[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".kiy[1:7]"  0 0 0 0 0 0 0;
	setAttr -s 8 ".kox[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".koy[1:7]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveNeck1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 16.978679829010165 3 7.6722037796158737 
		9 37.472065634496538 12 67.83249218764243 17 115.44942676244368 20 63.187759853731862 
		23 64.769761465338291 27 64.769761465338291 42 16.978679829010165;
	setAttr -s 9 ".kit[1:8]"  10 1 3 10 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  10 1 3 10 3 3 3 1;
	setAttr -s 9 ".kix[2:8]"  1 1 0.95676738023757935 1 1 1 1;
	setAttr -s 9 ".kiy[2:8]"  0 0 -0.29085442423820496 0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  1 1 0.95676738023757935 1 1 1 1;
	setAttr -s 9 ".koy[2:8]"  0 0 -0.29085442423820496 0 0 0 0;
createNode animCurveTA -n "char_FKCurveNeck1_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -13.679820867901928 3 -10.521801524889396 
		9 -39.692343364842266 12 -45.881109512135623 17 -42.215625654554685 20 -52.471627939590036 
		23 -52.707683412697989 27 -52.707683412697989 42 -13.679820867901928;
	setAttr -s 9 ".kit[1:8]"  10 1 3 10 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  10 1 3 10 3 3 3 1;
	setAttr -s 9 ".kix[2:8]"  1 1 0.91821926832199097 1 1 1 1;
	setAttr -s 9 ".kiy[2:8]"  0 0 -0.39607241749763489 0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  1 1 0.91821926832199097 1 1 1 1;
	setAttr -s 9 ".koy[2:8]"  0 0 -0.39607241749763489 0 0 0 0;
createNode animCurveTA -n "char_FKCurveNeck1_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -6.4072944111053358 3 -0.29107239215523245 
		9 -13.232297953099101 12 -35.046185705272578 17 -72.268265577018113 20 -29.770981049351267 
		23 -30.937623276318053 27 -30.937623276318053 42 -6.4072944111053358;
	setAttr -s 9 ".kit[1:8]"  10 1 3 10 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  10 1 3 10 3 3 3 1;
	setAttr -s 9 ".kix[2:8]"  1 1 0.94524657726287842 1 1 1 1;
	setAttr -s 9 ".kiy[2:8]"  0 0 0.32635706663131714 0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  1 1 0.94524657726287842 1 1 1 1;
	setAttr -s 9 ".koy[2:8]"  0 0 0.32635706663131714 0 0 0 0;
createNode animCurveTA -n "char_FKExtraNeck1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraNeck1_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraNeck1_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveSpine3_M_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 12 1 17 1 20 1 23 1 27 1 42 1;
	setAttr -s 7 ".kit[2:6]"  10 3 9 3 1;
	setAttr -s 7 ".kot[2:6]"  10 3 9 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTU -n "char_FKCurveSpine3_M_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 12 1 17 1 20 1 23 1 27 1 42 1;
	setAttr -s 7 ".kit[2:6]"  10 3 9 3 1;
	setAttr -s 7 ".kot[2:6]"  10 3 9 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTU -n "char_FKCurveSpine3_M_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 12 1 17 1 20 1 23 1 27 1 42 1;
	setAttr -s 7 ".kit[2:6]"  10 3 9 3 1;
	setAttr -s 7 ".kot[2:6]"  10 3 9 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "char_FKCurveSpine3_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -4.1759924717065973 12 6.0046405526338207 
		17 -9.4581257762622588 20 0.27940843982239216 23 -0.86559519377573313 27 -2.2785015060164993 
		42 -4.1759924717065973;
	setAttr -s 7 ".kit[2:6]"  10 3 9 3 1;
	setAttr -s 7 ".kot[2:6]"  10 3 9 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "char_FKCurveSpine3_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -1.201 12 -6.1932906666550434 17 -5.1964791993011028 
		20 -1.7662304730518328 23 -2.7341120111416477 27 -4.6017051289856976 42 -1.201;
	setAttr -s 7 ".kit[2:6]"  10 3 9 3 1;
	setAttr -s 7 ".kot[2:6]"  10 3 9 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "char_FKCurveSpine3_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -38.617693158088045 12 22.183804309029739 
		17 -57.842154552092786 20 3.8501089147386836 23 -6.2665387077850667 27 -22.374678605655813 
		42 -38.617693158088045;
	setAttr -s 7 ".kit[2:6]"  10 3 9 3 1;
	setAttr -s 7 ".kot[2:6]"  10 3 9 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "char_FKExtraSpine3_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraSpine3_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraSpine3_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveSpine4_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 12 1 17 1 20 1 23 1 27 1 42 1;
	setAttr -s 7 ".kit[2:6]"  10 3 9 3 1;
	setAttr -s 7 ".kot[2:6]"  10 3 9 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTU -n "char_FKCurveSpine4_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 12 1 17 1 20 1 23 1 27 1 42 1;
	setAttr -s 7 ".kit[2:6]"  10 3 9 3 1;
	setAttr -s 7 ".kot[2:6]"  10 3 9 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTU -n "char_FKCurveSpine4_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 12 1 17 1 20 1 23 1 27 1 42 1;
	setAttr -s 7 ".kit[2:6]"  10 3 9 3 1;
	setAttr -s 7 ".kot[2:6]"  10 3 9 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "char_FKCurveSpine4_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 19.548247782583122 12 -9.5911657361255731 
		17 7.35478142923668 20 -29.737515190132321 23 -28.169608817358842 27 -31.643302542984962 
		42 19.548247782583122;
	setAttr -s 7 ".kit[2:6]"  10 3 3 3 1;
	setAttr -s 7 ".kot[2:6]"  10 3 3 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "char_FKCurveSpine4_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 4.2832309672587163 12 3.2417694084653226 
		17 9.0221122426315254 20 8.5320284528613328 23 8.5213607743149176 27 8.4812891729769735 
		42 4.2832309672587163;
	setAttr -s 7 ".kit[2:6]"  10 3 9 3 1;
	setAttr -s 7 ".kot[2:6]"  10 3 9 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "char_FKCurveSpine4_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 5.393 12 -0.14935477519640319 17 9.7143510542010389 
		20 10.762186281775548 23 10.722461141284734 27 10.509934617204308 42 5.393;
	setAttr -s 7 ".kit[2:6]"  10 3 9 3 1;
	setAttr -s 7 ".kot[2:6]"  10 3 9 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "char_FKExtraSpine4_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraSpine4_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraSpine4_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurvePelvis1_M_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 9 1 12 1 17 1 23 1 27 1 36 1 42 1;
	setAttr -s 8 ".kit[1:7]"  1 3 10 3 3 3 1;
	setAttr -s 8 ".kot[1:7]"  1 3 10 3 3 3 1;
	setAttr -s 8 ".kix[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".kiy[1:7]"  0 0 0 0 0 0 0;
	setAttr -s 8 ".kox[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".koy[1:7]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurvePelvis1_M_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 9 1 12 1 17 1 23 1 27 1 36 1 42 1;
	setAttr -s 8 ".kit[1:7]"  1 3 10 3 3 3 1;
	setAttr -s 8 ".kot[1:7]"  1 3 10 3 3 3 1;
	setAttr -s 8 ".kix[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".kiy[1:7]"  0 0 0 0 0 0 0;
	setAttr -s 8 ".kox[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".koy[1:7]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurvePelvis1_M_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 9 1 12 1 17 1 23 1 27 1 36 1 42 1;
	setAttr -s 8 ".kit[1:7]"  1 3 10 3 3 3 1;
	setAttr -s 8 ".kot[1:7]"  1 3 10 3 3 3 1;
	setAttr -s 8 ".kix[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".kiy[1:7]"  0 0 0 0 0 0 0;
	setAttr -s 8 ".kox[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".koy[1:7]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurvePelvis1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 22.842862988065157 12 22.842862988065157 
		17 11.755078576380047 20 0.4163007934468359 23 6.623016032345487 27 0.58437725410949704 
		36 1.5131268240297662 42 0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 10 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 10 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 0.56303584575653076 0.91265201568603516 
		1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 -0.82643246650695801 -0.40873754024505615 
		0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 0.56303584575653076 0.91265201568603516 
		1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 -0.82643246650695801 -0.40873754024505615 
		0 0 0 0;
createNode animCurveTA -n "char_FKCurvePelvis1_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 -1.4581216654551474 12 -1.4581216654551474 
		17 5.4917673872291326 20 8.3135302672326397 23 8.7085746381789324 27 -0.30623066173798003 
		36 -0.75594070878494846 42 0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 10 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 10 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurvePelvis1_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.83191351642244571 9 -4.76808390348695 
		12 -4.76808390348695 17 -2.079989229254299 20 -39.721297326483196 23 -0.8357848435783376 
		27 -1.1579398580721627 36 -21.335077861456867 42 -0.83191351642244571;
	setAttr -s 9 ".kit[1:8]"  1 3 10 10 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 10 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 0.99415707588195801 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0.10794290900230408 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 0.99415707588195801 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0.10794290900230408 0 0 0 0;
createNode animCurveTA -n "char_FKExtraPelvis1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraPelvis1_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraPelvis1_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_RootCurveRoot1_M_CenterBtwFeet";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 9 0 12 0 17 0 20 0 27 0 42 0;
	setAttr -s 8 ".kit[1:7]"  10 1 3 10 3 3 1;
	setAttr -s 8 ".kot[1:7]"  10 1 3 10 3 3 1;
	setAttr -s 8 ".kix[2:7]"  1 1 1 1 1 1;
	setAttr -s 8 ".kiy[2:7]"  0 0 0 0 0 0;
	setAttr -s 8 ".kox[2:7]"  1 1 1 1 1 1;
	setAttr -s 8 ".koy[2:7]"  0 0 0 0 0 0;
createNode animCurveTA -n "char_RootCurveRoot1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 3.0405827598215973 3 1.1862675627745136 
		12 -17.058974866308979 17 -10.884252715826294 20 -4.4747150497444279 27 -5.2542678171142061 
		42 3.0405827598215973;
	setAttr -s 7 ".kit[1:6]"  10 3 10 3 3 1;
	setAttr -s 7 ".kot[1:6]"  10 3 10 3 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "char_RootCurveRoot1_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 23.714440424736864 3 17.558097593986059 
		12 11.911509763239359 17 -3.2358871566527179 20 3.2327000092307454 27 1.2992198406353519 
		42 23.714440424736864;
	setAttr -s 7 ".kit[1:6]"  10 3 10 3 3 1;
	setAttr -s 7 ".kot[1:6]"  10 3 10 3 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "char_RootCurveRoot1_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 8.6470827930312559 3 -3.2108037797679256 
		12 -8.9231888340447298 17 -31.777351022542401 20 78.532366732074294 27 56.361292021523504 
		42 8.6470827930312577;
	setAttr -s 7 ".kit[1:6]"  10 3 10 3 9 1;
	setAttr -s 7 ".kot[1:6]"  10 3 10 3 9 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTL -n "char_RootCurveRoot1_M_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.11500744677504726 3 -0.10308673019935877 
		12 -0.2041855366049958 17 -0.045272253618358099 20 0.028281927910081328 27 -0.032382146104468899 
		33 -0.093238631738542244 42 -0.11500744677504726;
	setAttr -s 8 ".kit[1:7]"  10 3 10 3 3 10 1;
	setAttr -s 8 ".kot[1:7]"  10 3 10 3 3 10 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTL -n "char_RootCurveRoot1_M_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.26403992941414445 3 -0.12560405365075475 
		12 -0.096810467978504899 17 -0.4001297562269216 20 -0.34320432877407248 27 -0.34592299292624434 
		33 -0.14424564493373657 42 -0.26403992941414445;
	setAttr -s 8 ".kit[1:7]"  10 1 10 3 3 10 1;
	setAttr -s 8 ".kot[1:7]"  10 1 10 3 3 10 1;
	setAttr -s 8 ".kix[2:7]"  0.96337312459945679 0.73447394371032715 
		1 1 0.9868541955947876 1;
	setAttr -s 8 ".kiy[2:7]"  -0.26816478371620178 -0.67863696813583374 
		0 0 0.16161328554153442 0;
	setAttr -s 8 ".kox[2:7]"  0.96337306499481201 0.73447394371032715 
		1 1 0.9868541955947876 1;
	setAttr -s 8 ".koy[2:7]"  -0.26816475391387939 -0.67863696813583374 
		0 0 0.16161328554153442 0;
createNode animCurveTL -n "char_RootCurveRoot1_M_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.0438000161016944 3 0.04951188598577394 
		12 -0.050645822639363236 17 -0.035570591122703013 20 -0.028592909366213753 27 -0.025846313891582692 
		33 -0.029423814153845484 42 -0.0438000161016944;
	setAttr -s 8 ".kit[1:7]"  10 3 10 3 3 10 1;
	setAttr -s 8 ".kot[1:7]"  10 3 10 3 3 10 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTA -n "char_RootExtraRoot1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_RootExtraRoot1_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_RootExtraRoot1_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_RootExtraRoot1_M_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_RootExtraRoot1_M_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_RootExtraRoot1_M_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Clavicle1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Clavicle1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Clavicle1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 66.461163309425402 12 66.461163309425402 
		17 60.627655188061588 20 57.927573059983601 23 57.927573059983601 27 57.927573059983601 
		36 26.900860541006267 42 0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 8.8562192445419878 12 8.8562192445419878 
		17 -6.6006199541288275 20 -13.754931632218884 23 -13.754931632218884 27 -13.754931632218884 
		36 5.1811201591342284 42 0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 0.55988436937332153 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 -0.82857078313827515 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 0.55988436937332153 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 -0.82857078313827515 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 3.4986940569081706 12 3.4986940569081706 
		17 14.490749023129666 20 19.578502489427535 23 19.578502489427535 27 19.578502489427535 
		36 -1.9762778550407079 42 0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 0.68882191181182861 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0.72493058443069458 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 0.68882191181182861 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0.72493058443069458 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 2.1942103669999999e-008 9 2.1942103669999999e-008 
		12 2.1942103669999999e-008 17 2.1942103669999999e-008 20 2.1942103669999999e-008 
		23 2.1942103669999999e-008 27 2.1942103669999999e-008 36 2.1942103669999999e-008 
		42 2.1942103669999999e-008;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 12 1 17 1 20 1 23 1 27 1 42 1;
	setAttr -s 8 ".kit[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kot[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 12 1 17 1 20 1 23 1 27 1 42 1;
	setAttr -s 8 ".kit[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kot[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 12 1 17 1 20 1 23 1 27 1 42 1;
	setAttr -s 8 ".kit[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kot[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTA -n "char_FKCurveR_Shoulder1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -0.68127875452050601 3 -9.9652486240204361 
		8 -25.735904623138968 12 6.0482352161106601 17 32.700758655165423 20 43.350195658196846 
		23 42.350577201947608 27 42.350577201947608 31 16.089793629335631 34 9.4096837338432575 
		42 -0.68127875452050601;
	setAttr -s 11 ".kit[2:10]"  10 3 10 3 3 3 10 10 
		1;
	setAttr -s 11 ".kot[2:10]"  10 3 10 3 3 3 10 10 
		1;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[10]"  1;
	setAttr -s 11 ".koy[10]"  0;
createNode animCurveTA -n "char_FKExtraR_Shoulder1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Shoulder1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Shoulder1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 3 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  10 3 10 3 3 3 9 1;
	setAttr -s 9 ".kot[1:8]"  10 3 10 3 3 3 9 1;
	setAttr -s 9 ".kix[8]"  1;
	setAttr -s 9 ".kiy[8]"  0;
	setAttr -s 9 ".kox[8]"  1;
	setAttr -s 9 ".koy[8]"  0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 3 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  10 3 10 3 3 3 9 1;
	setAttr -s 9 ".kot[1:8]"  10 3 10 3 3 3 9 1;
	setAttr -s 9 ".kix[8]"  1;
	setAttr -s 9 ".kiy[8]"  0;
	setAttr -s 9 ".kox[8]"  1;
	setAttr -s 9 ".koy[8]"  0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 3 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  10 3 10 3 3 3 9 1;
	setAttr -s 9 ".kot[1:8]"  10 3 10 3 3 3 9 1;
	setAttr -s 9 ".kix[8]"  1;
	setAttr -s 9 ".kiy[8]"  0;
	setAttr -s 9 ".kox[8]"  1;
	setAttr -s 9 ".koy[8]"  0;
createNode animCurveTA -n "char_FKCurveR_Elbow1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 48.213367515818511 3 5.5380787612603557 
		12 56.960230547241977 17 41.335327791157709 20 4.3908859224067625 23 6.5585667762089361 
		27 6.5585667762089361 31 48.080438767926907 36 53.692516726423101 39 41.309583190089498 
		42 48.213367515818511;
	setAttr -s 11 ".kit[1:10]"  10 3 10 3 3 3 1 9 
		10 1;
	setAttr -s 11 ".kot[1:10]"  10 3 10 3 3 3 1 9 
		10 1;
	setAttr -s 11 ".kix[7:10]"  0.55368977785110474 0.9142497181892395 
		0.90217453241348267 1;
	setAttr -s 11 ".kiy[7:10]"  0.83272308111190796 -0.4051511287689209 
		-0.43137124180793762 0;
	setAttr -s 11 ".kox[7:10]"  0.55368947982788086 0.9142497181892395 
		0.90217453241348267 1;
	setAttr -s 11 ".koy[7:10]"  0.83272325992584229 -0.4051511287689209 
		-0.43137124180793762 0;
createNode animCurveTA -n "char_FKExtraR_Elbow1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Elbow1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Elbow1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveDevice3_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 1 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 1 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveDevice3_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 1 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 1 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveDevice3_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 1 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 1 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveDevice3_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -83.798780827240449 9 -83.798780827240449 
		12 -83.798780827240449 17 -83.798780827240449 20 -83.798780827240449 23 -83.798780827240449 
		27 -83.798780827240449 36 -83.798780827240449 42 -83.798780827240449;
	setAttr -s 9 ".kit[1:8]"  1 1 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 1 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveDevice3_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.15209529104924274 9 -0.15209529104924274 
		12 -0.15209529104924274 17 -0.15209529104924274 20 -0.15209529104924274 23 -0.15209529104924274 
		27 -0.15209529104924274 36 -0.15209529104924274 42 -0.15209529104924274;
	setAttr -s 9 ".kit[1:8]"  1 1 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 1 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveDevice3_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -4.6558253190878789 9 -4.6558253190878789 
		12 -4.6558253190878789 17 -4.6558253190878789 20 -4.6558253190878789 23 -4.6558253190878789 
		27 -4.6558253190878789 36 -4.6558253190878789 42 -4.6558253190878789;
	setAttr -s 9 ".kit[1:8]"  1 1 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 1 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKCurveDevice3_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.070796223027113955 9 0.038939746117583683 
		12 0.038939746117583683 17 0.038939746117583683 20 0.038939746117583683 23 0.038939746117583683 
		27 0.038939746117583683 36 0.070796223027113955 42 0.070796223027113955;
	setAttr -s 9 ".kit[1:8]"  1 1 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 1 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKCurveDevice3_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.0024602716719113347 9 -0.055087414590916595 
		12 -0.055087414590916595 17 -0.055087414590916595 20 -0.055087414590916595 23 -0.055087414590916595 
		27 -0.055087414590916595 36 0.0024602716719113347 42 0.0024602716719113347;
	setAttr -s 9 ".kit[1:8]"  1 1 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 1 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKCurveDevice3_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.20119425626585011 9 0.020010939989264866 
		12 0.020010939989264866 17 0.020010939989264866 20 0.020010939989264866 23 0.020010939989264866 
		27 0.020010939989264866 36 0.20119425626585011 42 0.20119425626585011;
	setAttr -s 9 ".kit[1:8]"  1 1 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 1 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKExtraDevice3_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKExtraDevice3_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKExtraDevice3_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraDevice3_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraDevice3_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraDevice3_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKExtraDevice3_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKExtraDevice3_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKExtraDevice3_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb5_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb5_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb5_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb5_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 64.163191954635607 9 64.163191954635607 
		12 64.163191954635607 17 64.163191954635607 20 64.163191954635607 23 64.163191954635607 
		27 64.163191954635607 36 64.163191954635607 42 64.163191954635607;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb5_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 2.4325234183121345 9 2.4325234183121345 
		12 2.4325234183121345 17 2.4325234183121345 20 2.4325234183121345 23 2.4325234183121345 
		27 2.4325234183121345 36 2.4325234183121345 42 2.4325234183121345;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb5_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 8.5957802944005888 9 8.5957802944005888 
		12 8.5957802944005888 17 8.5957802944005888 20 8.5957802944005888 23 8.5957802944005888 
		27 8.5957802944005888 36 8.5957802944005888 42 8.5957802944005888;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb5_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb5_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb5_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb6_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb6_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb6_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb6_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 30.907503992135247 9 30.907503992135247 
		12 30.907503992135247 17 30.907503992135247 20 30.907503992135247 23 30.907503992135247 
		27 30.907503992135247 36 30.907503992135247 42 30.907503992135247;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb6_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -37.423813770375673 9 -37.423813770375673 
		12 -37.423813770375673 17 -37.423813770375673 20 -37.423813770375673 23 -37.423813770375673 
		27 -37.423813770375673 36 -37.423813770375673 42 -37.423813770375673;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb6_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -55.763523784114774 9 -55.763523784114774 
		12 -55.763523784114774 17 -55.763523784114774 20 -55.763523784114774 23 -55.763523784114774 
		27 -55.763523784114774 36 -55.763523784114774 42 -55.763523784114774;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb6_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb6_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb6_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle5_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle5_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle5_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle5_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 65.894016206888068 9 65.894016206888068 
		12 65.894016206888068 17 65.894016206888068 20 65.894016206888068 23 65.894016206888068 
		27 65.894016206888068 36 65.894016206888068 42 65.894016206888068;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle5_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 18.465908619718412 9 18.465908619718412 
		12 18.465908619718412 17 18.465908619718412 20 18.465908619718412 23 18.465908619718412 
		27 18.465908619718412 36 18.465908619718412 42 18.465908619718412;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle5_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -36.952741198413079 9 -36.952741198413079 
		12 -36.952741198413079 17 -36.952741198413079 20 -36.952741198413079 23 -36.952741198413079 
		27 -36.952741198413079 36 -36.952741198413079 42 -36.952741198413079;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle5_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle5_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle5_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle6_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle6_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle6_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle6_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 17.446522746060875 9 17.446522746060875 
		12 17.446522746060875 17 17.446522746060875 20 17.446522746060875 23 17.446522746060875 
		27 17.446522746060875 36 17.446522746060875 42 17.446522746060875;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle6_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle6_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle6_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle6_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle6_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 3 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  10 3 10 3 3 3 9 1;
	setAttr -s 9 ".kot[1:8]"  10 3 10 3 3 3 9 1;
	setAttr -s 9 ".kix[8]"  1;
	setAttr -s 9 ".kiy[8]"  0;
	setAttr -s 9 ".kox[8]"  1;
	setAttr -s 9 ".koy[8]"  0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 3 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  10 3 10 3 3 3 9 1;
	setAttr -s 9 ".kot[1:8]"  10 3 10 3 3 3 9 1;
	setAttr -s 9 ".kix[8]"  1;
	setAttr -s 9 ".kiy[8]"  0;
	setAttr -s 9 ".kox[8]"  1;
	setAttr -s 9 ".koy[8]"  0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 3 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  10 3 10 3 3 3 9 1;
	setAttr -s 9 ".kot[1:8]"  10 3 10 3 3 3 9 1;
	setAttr -s 9 ".kix[8]"  1;
	setAttr -s 9 ".kiy[8]"  0;
	setAttr -s 9 ".kox[8]"  1;
	setAttr -s 9 ".koy[8]"  0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 -9.7099612269341122 12 -39.03137562522074 
		17 -68.147061640003585 20 -78.669908868060404 23 -78.679439495546163 27 -78.679439495546163 
		31 -51.639930485438605 36 -6.7986370362520576 39 3.090079619538268 42 0;
	setAttr -s 11 ".kit[1:10]"  10 3 10 3 3 3 10 9 
		10 1;
	setAttr -s 11 ".kot[1:10]"  10 3 10 3 3 3 10 9 
		10 1;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[10]"  1;
	setAttr -s 11 ".koy[10]"  0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 24.211026325508492 3 39.913297397905815 
		12 60.266225768101982 17 54.612821209480899 20 66.824586216346248 23 65.437021389761753 
		27 65.437021389761753 31 47.84783656598092 36 24.92756563076944 39 32.92423406983896 
		42 24.211026325508492;
	setAttr -s 11 ".kit[1:10]"  10 3 10 3 3 3 10 3 
		10 1;
	setAttr -s 11 ".kot[1:10]"  10 3 10 3 3 3 10 3 
		10 1;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[10]"  1;
	setAttr -s 11 ".koy[10]"  0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 -1.0134453754851236 12 10.598009606868484 
		17 11.548032223814603 20 15.993359403077292 23 15.94184663579923 27 15.94184663579923 
		31 -1.951331011071421 36 5.0988398992036164 39 4.6082229836562796 42 0;
	setAttr -s 11 ".kit[1:10]"  10 3 10 3 3 3 10 9 
		10 1;
	setAttr -s 11 ".kot[1:10]"  10 3 10 3 3 3 10 9 
		10 1;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[10]"  1;
	setAttr -s 11 ".koy[10]"  0;
createNode animCurveTA -n "char_FKExtraR_Wrist1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Wrist1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Wrist1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Hip1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Hip1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Hip1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Hip1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Hip1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Hip1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Hip1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Hip1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Hip1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Knee1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Knee1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Knee1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Knee1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Knee1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Knee1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Knee1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ankle1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ankle1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ankle1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ankle1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ankle1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ankle1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ankle1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ankle1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ankle1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ball1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ball1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ball1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ball1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ball1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ball1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ball1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ball1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ball1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Clavicle1_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Clavicle1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Clavicle1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 24.179521757431925 20 35.371191196207185 
		23 35.371191196207185 27 35.371191196207185 36 0 42 0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 0.39654436707496643 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0.91801559925079346 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 0.39654436707496643 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0.91801559925079346 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 -16.307418007125815 20 
		-23.855426341061829 23 -23.855426341061829 27 -23.855426341061829 36 0 42 0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 0.53933924436569214 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 -0.84208863973617554 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 0.53933924436569214 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 -0.84208863973617554 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 -5.7073465023618448 20 
		-8.3490337974114723 23 -8.3490337974114723 27 -8.3490337974114723 36 0 42 0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -2.194210208e-008 9 -2.194210208e-008 
		12 -2.194210208e-008 17 -2.194210208e-008 20 -2.194210208e-008 23 -2.194210208e-008 
		27 -2.194210208e-008 36 -2.194210208e-008 42 -2.194210208e-008;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 12 1 17 1 20 1 23 1 27 1 42 1;
	setAttr -s 7 ".kit[2:6]"  10 3 3 3 1;
	setAttr -s 7 ".kot[2:6]"  10 3 3 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 12 1 17 1 20 1 23 1 27 1 42 1;
	setAttr -s 7 ".kit[2:6]"  10 3 3 3 1;
	setAttr -s 7 ".kot[2:6]"  10 3 3 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 12 1 17 1 20 1 23 1 27 1 42 1;
	setAttr -s 7 ".kit[2:6]"  10 3 3 3 1;
	setAttr -s 7 ".kot[2:6]"  10 3 3 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "char_FKCurveR_Shoulder1_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 17.19229314797029 3 10.296833608644212 
		8 -22.594930429650951 12 32.162138400691887 14 41.068432676001571 16 36.130565298716313 
		17 18.263978310736075 20 9.6684676402462308 23 4.2817059612524782 27 4.2817059612524782 
		30 13.181910898957232 33 8.198051688454246 38 12.073692520333108 42 17.19229314797029;
	setAttr -s 14 ".kit[0:13]"  3 3 10 3 10 10 10 3 
		3 3 10 10 10 1;
	setAttr -s 14 ".kot[0:13]"  3 3 10 3 10 10 10 3 
		3 3 10 10 10 1;
	setAttr -s 14 ".kix[13]"  1;
	setAttr -s 14 ".kiy[13]"  0;
	setAttr -s 14 ".kox[13]"  1;
	setAttr -s 14 ".koy[13]"  0;
createNode animCurveTA -n "char_FKExtraR_Shoulder1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Shoulder1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Shoulder1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 12 1 17 1 20 1 23 1 27 1 42 1;
	setAttr -s 7 ".kit[2:6]"  10 3 3 3 1;
	setAttr -s 7 ".kot[2:6]"  10 3 3 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 12 1 17 1 20 1 23 1 27 1 42 1;
	setAttr -s 7 ".kit[2:6]"  10 3 3 3 1;
	setAttr -s 7 ".kot[2:6]"  10 3 3 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 12 1 17 1 20 1 23 1 27 1 42 1;
	setAttr -s 7 ".kit[2:6]"  10 3 3 3 1;
	setAttr -s 7 ".kot[2:6]"  10 3 3 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "char_FKCurveR_Elbow1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 36.067317209388015 12 95.153421120403863 
		17 117.11175485446147 20 102.99017033930852 23 103.83575275177071 27 103.83575275177071 
		38 52.688434290166128 42 36.067317209388015;
	setAttr -s 8 ".kit[2:7]"  10 3 3 3 10 1;
	setAttr -s 8 ".kot[2:7]"  10 3 3 3 10 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTA -n "char_FKExtraR_Elbow1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Elbow1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Elbow1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb5_R_scaleZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 30 1 36 
		1 42 1;
	setAttr -s 10 ".kit[0:9]"  3 1 3 1 1 1 1 10 
		3 1;
	setAttr -s 10 ".kot[0:9]"  3 1 3 1 1 1 1 10 
		3 1;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb5_R_scaleY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 30 1 36 
		1 42 1;
	setAttr -s 10 ".kit[0:9]"  3 1 3 1 1 1 1 10 
		3 1;
	setAttr -s 10 ".kot[0:9]"  3 1 3 1 1 1 1 10 
		3 1;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb5_R_scaleX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 30 1 36 
		1 42 1;
	setAttr -s 10 ".kit[0:9]"  3 1 3 1 1 1 1 10 
		3 1;
	setAttr -s 10 ".kot[0:9]"  3 1 3 1 1 1 1 10 
		3 1;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb5_R_rotateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 27.905251822156437 9 -18.110570264457376 
		12 27.905251822156437 17 27.905251822156437 20 27.905251822156437 23 27.905251822156437 
		27 27.905251822156437 30 19.261980434307446 36 27.905251822156437 40 40.069677096503952 
		42 27.905251822156437;
	setAttr -s 11 ".kit[0:10]"  3 1 3 1 1 1 1 10 
		3 10 1;
	setAttr -s 11 ".kot[0:10]"  3 1 3 1 1 1 1 10 
		3 10 1;
	setAttr -s 11 ".kix[1:10]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[1:10]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[1:10]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[1:10]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb5_R_rotateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 9 -9.9430254580064652 12 0 17 0 20 
		0 23 0 27 0 30 2.3869127895860891 36 0 40 7.4387832149840536 42 0;
	setAttr -s 11 ".kit[0:10]"  3 1 3 1 1 1 1 10 
		3 10 1;
	setAttr -s 11 ".kot[0:10]"  3 1 3 1 1 1 1 10 
		3 10 1;
	setAttr -s 11 ".kix[1:10]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[1:10]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[1:10]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[1:10]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb5_R_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 9 14.326287802596285 12 0 17 0 20 0 
		23 0 27 0 30 -11.819045108965327 36 0 40 3.3070573943716166 42 0;
	setAttr -s 11 ".kit[0:10]"  3 1 3 1 1 1 1 10 
		3 10 1;
	setAttr -s 11 ".kot[0:10]"  3 1 3 1 1 1 1 10 
		3 10 1;
	setAttr -s 11 ".kix[1:10]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[1:10]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[1:10]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[1:10]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb5_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb5_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb5_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb6_R_scaleZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 30 1 36 
		1 42 1;
	setAttr -s 10 ".kit[0:9]"  3 1 3 1 1 1 1 10 
		3 1;
	setAttr -s 10 ".kot[0:9]"  3 1 3 1 1 1 1 10 
		3 1;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb6_R_scaleY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 30 1 36 
		1 42 1;
	setAttr -s 10 ".kit[0:9]"  3 1 3 1 1 1 1 10 
		3 1;
	setAttr -s 10 ".kot[0:9]"  3 1 3 1 1 1 1 10 
		3 1;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb6_R_scaleX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 30 1 36 
		1 42 1;
	setAttr -s 10 ".kit[0:9]"  3 1 3 1 1 1 1 10 
		3 1;
	setAttr -s 10 ".kot[0:9]"  3 1 3 1 1 1 1 10 
		3 1;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb6_R_rotateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 28.959457180709169 9 19.025889487686719 
		11 38.295136570964978 12 21.821476003942252 17 21.821476003942252 20 21.821476003942252 
		23 21.821476003942252 27 21.821476003942252 30 19.391947340764041 36 28.959457180709169 
		40 43.148960212739993 42 28.959457180709169;
	setAttr -s 12 ".kit[0:11]"  3 1 10 3 1 1 1 1 
		10 3 10 1;
	setAttr -s 12 ".kot[0:11]"  3 1 10 3 1 1 1 1 
		10 3 10 1;
	setAttr -s 12 ".kix[1:11]"  1 0.89872699975967407 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[1:11]"  0 0.43850859999656677 0 0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[1:11]"  1 0.89872699975967407 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[1:11]"  0 0.43850859999656677 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb6_R_rotateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -12.483272772594933 9 -12.078447682014165 
		11 -7.7250360052022797 12 -7.7195164525836812 17 -7.7195164525836812 20 -7.7195164525836812 
		23 -7.7195164525836812 27 -7.7195164525836812 30 -18.694141118612428 36 -12.483272772594933 
		40 -9.5555687008010999 42 -12.483272772594933;
	setAttr -s 12 ".kit[0:11]"  3 1 10 3 1 1 1 1 
		10 3 10 1;
	setAttr -s 12 ".kot[0:11]"  3 1 10 3 1 1 1 1 
		10 3 10 1;
	setAttr -s 12 ".kix[1:11]"  1 1 1 1 1 1 1 0.96367526054382324 1 1 1;
	setAttr -s 12 ".kiy[1:11]"  0 0 0 0 0 0 0 -0.26707684993743896 0 0 
		0;
	setAttr -s 12 ".kox[1:11]"  1 1 1 1 1 1 1 0.96367526054382324 1 1 1;
	setAttr -s 12 ".koy[1:11]"  0 0 0 0 0 0 0 -0.26707684993743896 0 0 
		0;
createNode animCurveTA -n "char_FKCurveR_Thumb6_R_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 21.335853393578894 9 23.189234463764098 
		11 40.213088386526422 12 5.6667086511936748 17 5.6667086511936748 20 5.6667086511936748 
		23 5.6667086511936748 27 5.6667086511936748 30 20.941917813515158 36 21.335853393578894 
		40 21.122638291690549 42 21.335853393578894;
	setAttr -s 12 ".kit[0:11]"  3 1 10 3 1 1 1 1 
		10 3 10 1;
	setAttr -s 12 ".kot[0:11]"  3 1 10 3 1 1 1 1 
		10 3 10 1;
	setAttr -s 12 ".kix[1:11]"  1 0.3107907772064209 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[1:11]"  0 -0.95047831535339355 0 0 0 0 0 0 0 0 
		0;
	setAttr -s 12 ".kox[1:11]"  1 0.3107907772064209 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[1:11]"  0 -0.95047831535339355 0 0 0 0 0 0 0 0 
		0;
createNode animCurveTA -n "char_FKExtraR_Thumb6_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb6_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb6_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle5_R_scaleZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 9 1 11 1 12 1 17 1 20 1 23 1 27 1 33 
		1 42 1;
	setAttr -s 10 ".kit[0:9]"  3 1 10 3 1 1 1 1 
		3 1;
	setAttr -s 10 ".kot[0:9]"  3 1 10 3 1 1 1 1 
		3 1;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle5_R_scaleY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 9 1 11 1 12 1 17 1 20 1 23 1 27 1 33 
		1 42 1;
	setAttr -s 10 ".kit[0:9]"  3 1 10 3 1 1 1 1 
		3 1;
	setAttr -s 10 ".kot[0:9]"  3 1 10 3 1 1 1 1 
		3 1;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle5_R_scaleX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 9 1 11 1 12 1 17 1 20 1 23 1 27 1 33 
		1 42 1;
	setAttr -s 10 ".kit[0:9]"  3 1 10 3 1 1 1 1 
		3 1;
	setAttr -s 10 ".kot[0:9]"  3 1 10 3 1 1 1 1 
		3 1;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle5_R_rotateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 36.340151082658281 9 5.4757800989043348 
		11 13.112658761378608 12 76.718153443502999 17 76.718153443502999 20 76.718153443502999 
		23 76.718153443502999 27 76.718153443502999 30 37.358107391796061 33 13.266100783563001 
		37 20.395798471309988 42 36.340151082658281;
	setAttr -s 12 ".kit[0:11]"  3 1 10 3 1 1 1 1 
		10 3 10 1;
	setAttr -s 12 ".kot[0:11]"  3 1 10 3 1 1 1 1 
		10 3 10 1;
	setAttr -s 12 ".kix[1:11]"  1 0.080164894461631775 1 1 1 1 1 0.17772065103054047 
		1 0.59739863872528076 1;
	setAttr -s 12 ".kiy[1:11]"  0 0.99678152799606323 0 0 0 0 0 -0.984080970287323 
		0 0.80194437503814697 0;
	setAttr -s 12 ".kox[1:11]"  1 0.080164894461631775 1 1 1 1 1 0.17772065103054047 
		1 0.59739863872528076 1;
	setAttr -s 12 ".koy[1:11]"  0 0.99678152799606323 0 0 0 0 0 -0.984080970287323 
		0 0.80194437503814697 0;
createNode animCurveTA -n "char_FKCurveR_Middle5_R_rotateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 9 1.3209593890539704 11 -1.2134996039568966 
		12 0 17 0 20 0 23 0 27 0 30 -12.710281456073488 33 0 42 0;
	setAttr -s 11 ".kit[0:10]"  3 1 10 3 1 1 1 1 
		10 3 1;
	setAttr -s 11 ".kot[0:10]"  3 1 10 3 1 1 1 1 
		10 3 1;
	setAttr -s 11 ".kix[1:10]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[1:10]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[1:10]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[1:10]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle5_R_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 9 -7.9160682837850107 11 -1.6902884050238509 
		12 0 17 0 20 0 23 0 27 0 30 2.5030879603960932 33 0 42 0;
	setAttr -s 11 ".kit[0:10]"  3 1 10 3 1 1 1 1 
		10 3 1;
	setAttr -s 11 ".kot[0:10]"  3 1 10 3 1 1 1 1 
		10 3 1;
	setAttr -s 11 ".kix[1:10]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[1:10]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[1:10]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[1:10]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle5_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle5_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle5_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle6_R_scaleZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 9 1 11 1 12 1 17 1 20 1 23 1 27 1 33 
		1 42 1;
	setAttr -s 10 ".kit[0:9]"  3 1 10 3 1 1 1 1 
		3 1;
	setAttr -s 10 ".kot[0:9]"  3 1 10 3 1 1 1 1 
		3 1;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle6_R_scaleY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 9 1 11 1 12 1 17 1 20 1 23 1 27 1 33 
		1 42 1;
	setAttr -s 10 ".kit[0:9]"  3 1 10 3 1 1 1 1 
		3 1;
	setAttr -s 10 ".kot[0:9]"  3 1 10 3 1 1 1 1 
		3 1;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle6_R_scaleX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 9 1 11 1 12 1 17 1 20 1 23 1 27 1 33 
		1 42 1;
	setAttr -s 10 ".kit[0:9]"  3 1 10 3 1 1 1 1 
		3 1;
	setAttr -s 10 ".kot[0:9]"  3 1 10 3 1 1 1 1 
		3 1;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle6_R_rotateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 25.092322839093878 9 -5.7720481446601086 
		11 -28.044800860589348 12 25.092322839093878 17 25.092322839093878 20 25.092322839093878 
		23 25.092322839093878 27 25.092322839093878 30 -5.2291364146466472 33 2.0182725399985912 
		37 9.147970227745585 40 33.519001775952816 42 25.092322839093878;
	setAttr -s 13 ".kit[0:12]"  3 1 10 3 1 1 1 1 
		10 3 10 10 1;
	setAttr -s 13 ".kot[0:12]"  3 1 10 3 1 1 1 1 
		10 3 10 10 1;
	setAttr -s 13 ".kix[1:12]"  1 0.18251898884773254 1 1 1 1 1 0.44479402899742126 
		1 0.39067542552947998 0.51381045579910278 1;
	setAttr -s 13 ".kiy[1:12]"  0 0.98320233821868896 0 0 0 0 0 -0.89563292264938354 
		0 0.92052853107452393 0.85790371894836426 0;
	setAttr -s 13 ".kox[1:12]"  1 0.18251898884773254 1 1 1 1 1 0.44479402899742126 
		1 0.39067542552947998 0.51381045579910278 1;
	setAttr -s 13 ".koy[1:12]"  0 0.98320233821868896 0 0 0 0 0 -0.89563292264938354 
		0 0.92052853107452393 0.85790371894836426 0;
createNode animCurveTA -n "char_FKCurveR_Middle6_R_rotateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 9 1.3209593890539713 11 -1.2134996039568995 
		12 0 17 0 20 0 23 0 27 0 30 -2.5417326028243892 33 0 42 0;
	setAttr -s 11 ".kit[0:10]"  3 1 10 3 1 1 1 1 
		10 3 1;
	setAttr -s 11 ".kot[0:10]"  3 1 10 3 1 1 1 1 
		10 3 1;
	setAttr -s 11 ".kix[1:10]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[1:10]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[1:10]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[1:10]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle6_R_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 9 -7.9160682837850196 11 -1.6902884050238522 
		12 0 17 0 20 0 23 0 27 0 30 -6.7814653375193545 33 0 42 0;
	setAttr -s 11 ".kit[0:10]"  3 1 10 3 1 1 1 1 
		10 3 1;
	setAttr -s 11 ".kot[0:10]"  3 1 10 3 1 1 1 1 
		10 3 1;
	setAttr -s 11 ".kix[1:10]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[1:10]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[1:10]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[1:10]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle6_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle6_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle6_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 12 1 17 1 20 1 23 1 27 1 42 1;
	setAttr -s 7 ".kit[2:6]"  10 3 3 3 1;
	setAttr -s 7 ".kot[2:6]"  10 3 3 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 12 1 17 1 20 1 23 1 27 1 42 1;
	setAttr -s 7 ".kit[2:6]"  10 3 3 3 1;
	setAttr -s 7 ".kot[2:6]"  10 3 3 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 12 1 17 1 20 1 23 1 27 1 42 1;
	setAttr -s 7 ".kit[2:6]"  10 3 3 3 1;
	setAttr -s 7 ".kot[2:6]"  10 3 3 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 5.3442930176413892 8 -53.600236265342616 
		12 -29.583987966563488 17 -29.664275244816398 20 -29.701436801912507 23 -29.337588908370989 
		27 -29.337588908370989 30 -26.923879644852587 33 -24.158318170345513 37 -53.855424630363359 
		42 5.3442930176413892;
	setAttr -s 11 ".kit[1:10]"  10 3 10 3 3 3 10 10 
		10 1;
	setAttr -s 11 ".kot[1:10]"  10 3 10 3 3 3 10 10 
		10 1;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[10]"  1;
	setAttr -s 11 ".koy[10]"  0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 30.381278874765098 8 15.789077290460526 
		12 37.49807926068037 17 40.824785830587473 20 42.364576427924604 23 42.77983797373696 
		27 42.77983797373696 30 57.137905116097073 33 60.357111882398527 37 30.725385837955393 
		42 30.381278874765098;
	setAttr -s 11 ".kit[1:10]"  10 3 10 3 3 3 10 10 
		10 1;
	setAttr -s 11 ".kot[1:10]"  10 3 10 3 3 3 10 10 
		10 1;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[10]"  1;
	setAttr -s 11 ".koy[10]"  0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 11.798366512855891 8 -23.791787293489055 
		12 -18.36843224025813 17 -2.7031087734984052 20 4.5477013810728453 23 4.2873898923470248 
		27 4.2873898923470248 30 -7.08566511429414 33 16.295256917318671 37 -16.18513420913807 
		42 11.798366512855891;
	setAttr -s 11 ".kit[1:10]"  10 3 10 3 3 3 10 10 
		10 1;
	setAttr -s 11 ".kot[1:10]"  10 3 10 3 3 3 10 10 
		10 1;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[10]"  1;
	setAttr -s 11 ".koy[10]"  0;
createNode animCurveTA -n "char_FKExtraR_Wrist1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Wrist1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Wrist1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Hip1_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Hip1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Hip1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Hip1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Hip1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Hip1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Hip1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Hip1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Hip1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Knee1_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Knee1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Knee1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Knee1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Knee1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Knee1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Knee1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ankle1_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ankle1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ankle1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ankle1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ankle1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ankle1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ankle1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ankle1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ankle1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ball1_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ball1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ball1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ball1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ball1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ball1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ball1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ball1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ball1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_All_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_All_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_All_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_All_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_All_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_All_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_All_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_All_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_All_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 12 0 17 0 20 0 23 0 27 0 36 0 42 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_All_visibility";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 12 1 17 1 20 1 23 1 27 1 36 1 42 
		1;
	setAttr -s 9 ".kit[1:8]"  1 3 9 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 5 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 0 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode lightLinker -n "lightLinker1";
	setAttr -s 3 ".lnk";
	setAttr -s 3 ".slnk";
select -ne :time1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 42;
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
connectAttr "maugli_attackSource.cl" "clipLibrary1.sc[0]";
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
connectAttr "FKCurveR_Shoulder1_L_rotateZ.a" "clipLibrary1.cel[0].cev[123].cevr"
		;
connectAttr "FKCurveR_Shoulder1_L_rotateX.a" "clipLibrary1.cel[0].cev[124].cevr"
		;
connectAttr "FKCurveR_Shoulder1_R_rotateZ.a" "clipLibrary1.cel[0].cev[125].cevr"
		;
connectAttr "FKCurveR_Shoulder1_R_rotateX.a" "clipLibrary1.cel[0].cev[126].cevr"
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
// End of maugli_attack.ma
