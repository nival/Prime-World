//Maya ASCII 2008 scene
//Name: maugli_attack2.ma
//Last modified: Thu, Feb 05, 2009 02:18:36 PM
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
createNode animClip -n "maugli_attack2Source";
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
	setAttr ".se" 53;
	setAttr ".ci" no;
createNode animCurveTU -n "char_AimCurveEye_Right1_M_follow";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 10 5 10 9 10 22 10 27 10 30 10 34 10 
		38 10 47 10 53 10;
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
	setAttr -s 10 ".ktv[0:9]"  0 1 5 1 9 1 22 1 27 1 30 1 34 1 38 1 47 
		1 53 1;
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
		9 0 22 0 25 -0.0051972550483573802 27 0 30 -0.050695399327225429 34 0 38 0 42 -0.037596559596919064 
		47 0.0051546649538099891 53 0;
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
		9 0 22 0 25 -0.35751856195622522 27 0 30 -0.15160454777933444 34 0 38 0 42 -0.17036749883266628 
		47 -0.042853001544772097 53 0;
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
		9 0 22 0 25 0.071490222949566029 27 0 30 -0.0058619912590536314 34 0 38 0 42 -0.0079582595575412238 
		47 -1.0735424795098479e-005 53 0;
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 10 9 10 22 10 27 10 30 10 34 10 38 10 
		47 10 53 10;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveArm_R_IKVis";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 10 9 10 22 10 27 10 30 10 34 10 38 10 
		47 10 53 10;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKPoleVectorCurveArm_L_follow";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKPoleVectorCurveLeg_L_follow";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 12 10 20 10 27 10 38 10 41 10 47 10 
		53 10;
	setAttr -s 8 ".kit[0:7]"  3 1 1 1 10 1 3 1;
	setAttr -s 8 ".kot[0:7]"  3 1 1 1 10 1 3 1;
	setAttr -s 8 ".kix[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".kiy[1:7]"  0 0 0 0 0 0 0;
	setAttr -s 8 ".kox[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".koy[1:7]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_L_translateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 12 0 20 -0.30257399871140994 27 -0.30257399871140994 
		30 -0.30940632499877635 34 -0.31111331152215643 38 -0.30257399871140994 41 -0.30755319681230647 
		43 -0.098608906351549161 47 0 53 0;
	setAttr -s 11 ".kit[0:10]"  3 1 1 1 10 10 10 1 
		10 3 1;
	setAttr -s 11 ".kot[0:10]"  3 1 1 1 10 10 10 1 
		10 3 1;
	setAttr -s 11 ".kix[1:10]"  1 1 1 1 1 1 1 0.54516172409057617 1 1;
	setAttr -s 11 ".kiy[1:10]"  0 0 0 0 0 0 0 0.83833092451095581 0 0;
	setAttr -s 11 ".kox[1:10]"  1 1 1 1 1 1 1 0.54516172409057617 1 1;
	setAttr -s 11 ".koy[1:10]"  0 0 0 0 0 0 0 0.83833092451095581 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_L_translateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 12 0 20 0.10804131197287239 27 0.10804131197287239 
		30 0.12448419135912484 34 0.11449741038215089 38 0.10804131197287239 41 0.1196262536470504 
		43 0.23052011802632466 47 0 53 0;
	setAttr -s 11 ".kit[0:10]"  3 1 1 1 10 10 10 1 
		10 3 1;
	setAttr -s 11 ".kot[0:10]"  3 1 1 1 10 10 10 1 
		10 3 1;
	setAttr -s 11 ".kix[1:10]"  1 1 1 1 1 1 1 0.85819971561431885 1 1;
	setAttr -s 11 ".kiy[1:10]"  0 0 0 0 0 0 0 -0.51331597566604614 0 0;
	setAttr -s 11 ".kox[1:10]"  1 1 1 1 1 1 1 0.85819971561431885 1 1;
	setAttr -s 11 ".koy[1:10]"  0 0 0 0 0 0 0 -0.51331597566604614 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_L_translateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 12 0 20 -0.14265582873120647 27 -0.14265582873120647 
		30 -0.19044092783022135 34 -0.16977299844690832 38 -0.14265582873120647 41 -0.18425166995690584 
		43 0.021346135399742609 47 0 53 0;
	setAttr -s 11 ".kit[0:10]"  3 1 1 1 10 10 10 1 
		10 3 1;
	setAttr -s 11 ".kot[0:10]"  3 1 1 1 10 10 10 1 
		10 3 1;
	setAttr -s 11 ".kix[1:10]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[1:10]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[1:10]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[1:10]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraLeg_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveLeg_L_antiPop";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 12 0 20 0 27 0 38 0 47 0 53 0;
	setAttr -s 7 ".kit[0:6]"  3 1 1 1 1 3 1;
	setAttr -s 7 ".kot[0:6]"  3 1 1 1 1 3 1;
	setAttr -s 7 ".kix[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".kiy[1:6]"  0 0 0 0 0 0;
	setAttr -s 7 ".kox[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".koy[1:6]"  0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveLeg_L_stretchy";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 12 0 20 0 27 0 38 0 47 0 53 0;
	setAttr -s 7 ".kit[0:6]"  3 1 1 1 1 3 1;
	setAttr -s 7 ".kot[0:6]"  3 1 1 1 1 3 1;
	setAttr -s 7 ".kix[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".kiy[1:6]"  0 0 0 0 0 0;
	setAttr -s 7 ".kox[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".koy[1:6]"  0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveLeg_L_swivel";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 12 0 20 0 27 0 38 0 47 0 53 0;
	setAttr -s 7 ".kit[0:6]"  3 1 1 1 1 3 1;
	setAttr -s 7 ".kot[0:6]"  3 1 1 1 1 3 1;
	setAttr -s 7 ".kix[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".kiy[1:6]"  0 0 0 0 0 0;
	setAttr -s 7 ".kox[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".koy[1:6]"  0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveLeg_L_rotateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 12 0 16 -82.831962091028515 20 -170.2564772688267 
		27 -164.36509358760048 38 -164.36509358760048 43 -35.380593252613032 47 0 53 0;
	setAttr -s 9 ".kit[0:8]"  3 1 10 1 1 1 10 3 
		1;
	setAttr -s 9 ".kot[0:8]"  3 1 10 1 1 1 10 3 
		1;
	setAttr -s 9 ".kix[1:8]"  1 0.08938116580247879 1 1 1 0.10400938242673874 
		1 1;
	setAttr -s 9 ".kiy[1:8]"  0 -0.99599754810333252 0 0 0 0.99457633495330811 
		0 0;
	setAttr -s 9 ".kox[1:8]"  1 0.08938116580247879 1 1 1 0.10400938242673874 
		1 1;
	setAttr -s 9 ".koy[1:8]"  0 -0.99599754810333252 0 0 0 0.99457633495330811 
		0 0;
createNode animCurveTA -n "char_IKCurveLeg_L_rotateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 43.567069197048298 12 43.567069197048298 
		16 98.658324993000818 20 175.26744815515102 27 169.61302683800801 38 169.61302683800801 
		43 38.26647514019308 47 43.567069197048298 53 43.567069197048298;
	setAttr -s 9 ".kit[0:8]"  3 1 10 1 1 1 10 3 
		1;
	setAttr -s 9 ".kot[0:8]"  3 1 10 1 1 1 10 3 
		1;
	setAttr -s 9 ".kix[1:8]"  1 0.11523947864770889 1 1 1 0.13511823117733002 
		1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0.99333769083023071 0 0 0 -0.9908294677734375 
		0 0;
	setAttr -s 9 ".kox[1:8]"  1 0.11523947864770889 1 1 1 0.13511823117733002 
		1 1;
	setAttr -s 9 ".koy[1:8]"  0 0.99333769083023071 0 0 0 -0.9908294677734375 
		0 0;
createNode animCurveTA -n "char_IKCurveLeg_L_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 12 0 16 62.167434017136401 20 65.637802667385188 
		27 79.119279331691828 38 79.119279331691828 43 70.27059490471315 47 0 53 0;
	setAttr -s 9 ".kit[0:8]"  3 1 1 1 1 1 10 3 
		1;
	setAttr -s 9 ".kot[0:8]"  3 1 1 1 1 1 10 3 
		1;
	setAttr -s 9 ".kix[1:8]"  1 0.72658318281173706 0.865348219871521 
		1 1 0.21229866147041321 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0.68707853555679321 0.50117111206054688 
		0 0 -0.97720479965209961 0 0;
	setAttr -s 9 ".kox[1:8]"  1 0.72658306360244751 0.865348219871521 
		1 1 0.21229866147041321 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0.68707865476608276 0.50117111206054688 
		0 0 -0.97720479965209961 0 0;
createNode animCurveTL -n "char_IKCurveLeg_L_translateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.28844199405395621 12 -0.28844199405395621 
		20 -0.28844199405395615 27 -0.33025014677226644 38 -0.33025014677226644 47 -0.28844199405395621 
		53 -0.28844199405395621;
	setAttr -s 7 ".kit[0:6]"  3 1 1 1 1 3 1;
	setAttr -s 7 ".kot[0:6]"  3 1 1 1 1 3 1;
	setAttr -s 7 ".kix[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".kiy[1:6]"  0 0 0 0 0 0;
	setAttr -s 7 ".kox[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".koy[1:6]"  0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveLeg_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 14 0.17456610198272621 16 0.16516007124955812 
		20 0.048957904239827599 27 0.10643381712593453 38 0.10643381712593453 43 0.22471130667534217 
		47 0 53 0;
	setAttr -s 10 ".kit[1:9]"  1 3 1 1 3 1 3 3 
		1;
	setAttr -s 10 ".kot[1:9]"  1 3 1 1 3 1 3 3 
		1;
	setAttr -s 10 ".kix[1:9]"  1 1 0.95671379566192627 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 -0.29103046655654907 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 0.95671385526657104 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 -0.29103046655654907 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveLeg_L_translateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.087756482507145378 12 0.087756482507145378 
		20 0.087756482507145378 27 0.087756482507145378 38 0.087756482507145378 47 0.087756482507145378 
		53 0.087756482507145378;
	setAttr -s 7 ".kit[0:6]"  3 1 1 1 1 3 1;
	setAttr -s 7 ".kot[0:6]"  3 1 1 1 1 3 1;
	setAttr -s 7 ".kix[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".kiy[1:6]"  0 0 0 0 0 0;
	setAttr -s 7 ".kox[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".koy[1:6]"  0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraLeg_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 -0.80651909766667318 22 -0.80651909766667318 
		27 -0.80651909766667318 30 -0.80651909766667318 34 -0.80651909766667318 38 -0.80651909766667318 
		47 -0.80651909766667318 53 0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveArm_R_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 -1.0333372441880238 22 -1.0333372441880238 
		27 -1.0333372441880238 30 -1.0333372441880238 34 -1.0333372441880238 38 -1.0333372441880238 
		47 -1.0333372441880238 53 0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveArm_R_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 10 9 10 22 10 27 10 30 10 34 10 38 10 
		47 10 53 10;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_R_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
		22 0.33022172654533777 27 0.33022172654533777 30 0.33022172654533777 34 0.33022172654533777 
		38 0.33022172654533777 47 0.33022172654533777 53 0.33022172654533777;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveLeg_R_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
		22 -0.13911956167322667 27 -0.13911956167322667 30 -0.13911956167322667 34 -0.13911956167322667 
		38 -0.13911956167322667 47 -0.13911956167322667 53 -0.13911956167322667;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraLeg_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 22 1 24 1 27 1 30 1 34 1 38 1 47 1 
		53 1;
	setAttr -s 9 ".kit[2:8]"  1 10 3 3 3 3 1;
	setAttr -s 9 ".kot[2:8]"  1 10 3 3 3 3 1;
	setAttr -s 9 ".kix[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[2:8]"  0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[2:8]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveTooth1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 22 1 24 1 27 1 30 1 34 1 38 1 47 1 
		53 1;
	setAttr -s 9 ".kit[2:8]"  1 10 3 3 3 3 1;
	setAttr -s 9 ".kot[2:8]"  1 10 3 3 3 3 1;
	setAttr -s 9 ".kix[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[2:8]"  0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[2:8]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveTooth1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 22 1 24 1 27 1 30 1 34 1 38 1 47 1 
		53 1;
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
		22 -69.10088669565576 24 8.0259526563423993 27 -11.433423741937943 30 -23.867070987228868 
		34 -69.362464001678944 38 -28.797340134102253 41 -38.796210369001784 44 -15.138671077050615 
		47 -32.511845976965219 50 -34.369001036401016 53 -27.541549434058677;
	setAttr -s 13 ".kit[1:12]"  10 3 1 10 3 3 3 10 
		10 3 10 1;
	setAttr -s 13 ".kot[1:12]"  10 3 1 10 3 3 3 10 
		10 3 10 1;
	setAttr -s 13 ".kix[3:12]"  1 0.33813601732254028 1 1 1 0.6427275538444519 
		0.87680238485336304 1 1 1;
	setAttr -s 13 ".kiy[3:12]"  0 -0.94109725952148438 0 0 0 0.7660948634147644 
		0.48085081577301025 0 0 0;
	setAttr -s 13 ".kox[3:12]"  1 0.33813601732254028 1 1 1 0.6427275538444519 
		0.87680238485336304 1 1 1;
	setAttr -s 13 ".koy[3:12]"  0 -0.94109725952148438 0 0 0 0.7660948634147644 
		0.48085081577301025 0 0 0;
createNode animCurveTA -n "char_FKCurveTooth1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 8.4599709196312922 6 11.048078024375929 
		22 4.9239946860727963 24 1.3790349658998506 27 -19.000189528533628 30 36.124214586630572 
		34 -17.164022145063171 38 24.077612137520855 41 -0.12364666191881581 44 4.8530503846892978 
		47 -5.5991780055355518 50 13.121015710141641 53 8.4599709196312922;
	setAttr -s 13 ".kit[1:12]"  10 3 1 10 3 3 3 10 
		10 3 10 1;
	setAttr -s 13 ".kot[1:12]"  10 3 1 10 3 3 3 10 
		10 3 10 1;
	setAttr -s 13 ".kix[3:12]"  1 0.31321096420288086 1 1 1 0.51201051473617554 
		0.90228539705276489 1 0.63179057836532593 1;
	setAttr -s 13 ".kiy[3:12]"  0 0.9496835470199585 0 0 0 -0.85897916555404663 
		-0.43113917112350464 0 0.77513915300369263 0;
	setAttr -s 13 ".kox[3:12]"  1 0.31321096420288086 1 1 1 0.51201051473617554 
		0.90228539705276489 1 0.63179057836532593 1;
	setAttr -s 13 ".koy[3:12]"  0 0.9496835470199585 0 0 0 -0.85897916555404663 
		-0.43113917112350464 0 0.77513915300369263 0;
createNode animCurveTA -n "char_FKCurveTooth1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 6.8137435045968227 6 2.5291732906843438 
		22 -5.8830798092889944 24 4.0997967922338443 27 -7.990926157558591 30 13.666955388705983 
		34 12.949789200140968 38 0.41492619154254412 41 5.4352804950187661 44 7.8473983067194695 
		47 -0.93998777022731683 50 8.5890948267223592 53 6.8137435045968227;
	setAttr -s 13 ".kit[1:12]"  10 3 1 10 3 3 3 10 
		10 3 10 1;
	setAttr -s 13 ".kot[1:12]"  10 3 1 10 3 3 3 10 
		10 3 10 1;
	setAttr -s 13 ".kix[3:12]"  1 0.76763248443603516 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[3:12]"  0 0.64089035987854004 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[3:12]"  1 0.76763248443603516 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[3:12]"  0 0.64089035987854004 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKCurveTooth1_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -0.028863465787140358 6 -0.091073054744884641 
		22 -0.04653174737723198 24 -0.028863465787140358 27 -0.028029580965363111 30 -0.028863465787140358 
		34 -0.043433965367030362 38 -0.028863465787140358 41 -0.031620284950151969 47 -0.039250141713495348 
		50 -0.060211257896800097 53 -0.028863465787140358;
	setAttr -s 12 ".kit[1:11]"  10 3 1 10 3 3 3 10 
		3 10 1;
	setAttr -s 12 ".kot[1:11]"  10 3 1 10 3 3 3 10 
		3 10 1;
	setAttr -s 12 ".kix[3:11]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[3:11]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[3:11]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[3:11]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKCurveTooth1_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -0.023775464972591611 6 -0.0097006006052766137 
		22 -0.050572926271469955 24 -0.023775464972591611 27 -0.012603345928248607 30 -0.023775464972591611 
		34 -0.017889043022686086 38 -0.023775464972591611 41 -0.047733729481177156 47 -0.039698589716682206 
		50 -0.034143234276617175 53 -0.023775464972591611;
	setAttr -s 12 ".kit[1:11]"  10 3 1 10 3 3 3 10 
		3 10 1;
	setAttr -s 12 ".kot[1:11]"  10 3 1 10 3 3 3 10 
		3 10 1;
	setAttr -s 12 ".kix[3:11]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[3:11]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[3:11]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[3:11]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKCurveTooth1_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -0.052162964274260919 6 0.0068343795400855594 
		22 -0.12533239361746645 24 -0.052162964274260919 27 -0.09242030418061481 30 -0.052162964274260919 
		34 -0.13741359615144641 38 -0.052162964274260919 41 -0.070814674602396141 47 -0.069482764048043225 
		50 -0.074711271367427307 53 -0.052162964274260919;
	setAttr -s 12 ".kit[1:11]"  10 3 1 10 3 3 3 10 
		3 10 1;
	setAttr -s 12 ".kot[1:11]"  10 3 1 10 3 3 3 10 
		3 10 1;
	setAttr -s 12 ".kix[3:11]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[3:11]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[3:11]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[3:11]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKExtraTooth1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 12 ".ktv[0:11]"  0 -60.970082317325229 3 -50.524167673354441 
		7 -38.575624022912514 12 -22.805567804451098 18 0.20901362320271161 27 18.786516817601328 
		30 25.136549957559932 34 23.061105946040495 38 23.061105946040495 42 -17.764172655247396 
		45 -27.754960061603732 53 -60.970082317325229;
	setAttr -s 12 ".kit[1:11]"  9 10 10 3 10 3 3 3 
		10 10 1;
	setAttr -s 12 ".kot[1:11]"  9 10 10 3 10 3 3 3 
		10 10 1;
	setAttr -s 12 ".kix[11]"  1;
	setAttr -s 12 ".kiy[11]"  0;
	setAttr -s 12 ".kox[11]"  1;
	setAttr -s 12 ".koy[11]"  0;
createNode animCurveTA -n "FKCurveR_Shoulder1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -5.1174438057844904 3 -18.63211667274814 
		7 32.193767378721546 12 11.303660652912093 18 0.66074502663138623 27 23.817903109433793 
		30 32.972944284836721 34 31.765246771002637 38 31.765246771002637 42 12.853678218820804 
		45 12.921837881605878 53 -5.1174438057844904;
	setAttr -s 12 ".kit[3:11]"  10 3 10 3 3 3 10 10 
		1;
	setAttr -s 12 ".kot[3:11]"  10 3 10 3 3 3 10 10 
		1;
	setAttr -s 12 ".kix[11]"  1;
	setAttr -s 12 ".kiy[11]"  0;
	setAttr -s 12 ".kox[11]"  1;
	setAttr -s 12 ".koy[11]"  0;
createNode animCurveTA -n "FKCurveR_Shoulder1_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 -36.986337964869008 9 -57.193375446487082 
		18 -37.135759869419324 22 -54.945282924660333 24 -46.724827317299486 26 -8.4912515929493555 
		27 4.8482988835022391 30 5.5736428565451055 34 1.8800141319440642 38 1.8800141319440642 
		41 2.8695882594134083 44 -33.013348081559705 49 -48.099749718524677 53 -36.986337964869008;
	setAttr -s 14 ".kit[0:13]"  3 10 10 3 10 10 10 3 
		3 3 10 10 10 1;
	setAttr -s 14 ".kot[0:13]"  3 10 10 3 10 10 10 3 
		3 3 10 10 10 1;
	setAttr -s 14 ".kix[13]"  1;
	setAttr -s 14 ".kiy[13]"  0;
	setAttr -s 14 ".kox[13]"  1;
	setAttr -s 14 ".koy[13]"  0;
createNode animCurveTA -n "FKCurveR_Shoulder1_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 10.660406869524985 9 -8.0104831267137762 
		18 -6.7140581358769849 22 -25.645489412199673 24 -8.6723355410242817 26 39.96317346336258 
		27 53.920291883939228 30 62.387048132527489 34 60.412055041306466 38 60.412055041306466 
		41 58.682047046153201 44 18.822528603719718 49 8.1428486653223846 53 10.660406869524985;
	setAttr -s 14 ".kit[0:13]"  3 10 10 3 10 10 10 3 
		3 3 10 10 10 1;
	setAttr -s 14 ".kot[0:13]"  3 10 10 3 10 10 10 3 
		3 3 10 10 10 1;
	setAttr -s 14 ".kix[13]"  1;
	setAttr -s 14 ".kiy[13]"  0;
	setAttr -s 14 ".kox[13]"  1;
	setAttr -s 14 ".koy[13]"  0;
createNode animCurveTA -n "char_FKExtraPen1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 7 1 33 1 38 1 47 1 53 1;
	setAttr -s 7 ".kit[1:6]"  10 10 3 3 3 1;
	setAttr -s 7 ".kot[1:6]"  10 10 3 3 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTU -n "char_FKCurveHair1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 7 1 33 1 38 1 47 1 53 1;
	setAttr -s 7 ".kit[1:6]"  10 10 3 3 3 1;
	setAttr -s 7 ".kot[1:6]"  10 10 3 3 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTU -n "char_FKCurveHair1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 7 1 33 1 38 1 47 1 53 1;
	setAttr -s 7 ".kit[1:6]"  10 10 3 3 3 1;
	setAttr -s 7 ".kot[1:6]"  10 10 3 3 3 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "char_FKCurveHair1_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 17 ".ktv[0:16]"  0 30.524599611915377 3 28.229079733444738 
		7 28.45323585017416 11 27.046710641712846 14 18.074403099747592 20 73.621729151468131 
		24 36.197673605284024 27 40.135396341313708 28 74.072469551477852 30 100.89271082539042 
		33 59.537341217440904 36 25.721997820811211 38 26.07763285389197 43 23.092362948075252 
		47 23.745243154591343 50 21.763073581474373 53 30.524599611915377;
	setAttr -s 17 ".kit[0:16]"  3 10 10 10 10 10 10 10 
		10 10 9 10 1 10 9 9 1;
	setAttr -s 17 ".kot[0:16]"  3 10 10 10 10 10 10 10 
		10 10 9 10 1 10 9 9 1;
	setAttr -s 17 ".kix[12:16]"  0.94980788230895996 1 0.99509310722351074 
		0.86066198348999023 1;
	setAttr -s 17 ".kiy[12:16]"  -0.31283378601074219 0 -0.09894271194934845 
		0.50917679071426392 0;
	setAttr -s 17 ".kox[12:16]"  0.94980788230895996 1 0.99509310722351074 
		0.86066198348999023 1;
	setAttr -s 17 ".koy[12:16]"  -0.31283384561538696 0 -0.09894271194934845 
		0.50917679071426392 0;
createNode animCurveTA -n "char_FKCurveHair1_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 17 ".ktv[0:16]"  0 -20.226445302148342 3 -7.7720559360319239 
		7 9.9810276309880965 11 19.882481930920758 14 15.195892975388862 20 -12.653525957761044 
		24 -3.5821666369009693 27 7.5053679564402147 28 0.51997916638743391 30 -1.0726696219118144 
		33 -22.378594420586662 36 -11.505148906633023 38 -2.5969192301462698 43 15.143236813168569 
		47 -8.7513939016726816 50 -16.131717190760664 53 -20.226445302148342;
	setAttr -s 17 ".kit[0:16]"  3 10 10 10 10 10 3 10 
		10 10 3 10 9 10 3 10 1;
	setAttr -s 17 ".kot[0:16]"  3 10 10 10 10 10 3 10 
		10 10 3 10 9 10 3 10 1;
	setAttr -s 17 ".kix[16]"  1;
	setAttr -s 17 ".kiy[16]"  0;
	setAttr -s 17 ".kox[16]"  1;
	setAttr -s 17 ".koy[16]"  0;
createNode animCurveTA -n "char_FKCurveHair1_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 17 ".ktv[0:16]"  0 17.701770262088139 3 12.088109584296729 
		7 -1.7780742321615404 11 -7.860089019882512 14 5.4076613461644421 20 -5.9163370108069833 
		24 1.1394693763295527 27 32.827652847322625 28 27.69958141419697 30 -26.748009989736858 
		33 -28.969106528341079 36 14.493246885272852 38 -1.7549706063755581 43 -1.6836440544021614 
		47 -3.0008845103027828 50 20.21737559444707 53 17.701770262088139;
	setAttr -s 17 ".kit[0:16]"  3 10 10 10 10 10 10 10 
		10 1 3 10 3 10 9 9 1;
	setAttr -s 17 ".kot[0:16]"  3 10 10 10 10 10 10 10 
		10 1 3 10 3 10 9 9 1;
	setAttr -s 17 ".kix[9:16]"  0.90233951807022095 1 0.33110237121582031 
		1 1 0.52102601528167725 0.48427557945251465 1;
	setAttr -s 17 ".kiy[9:16]"  -0.43102598190307617 0 0.94359481334686279 
		0 0 0.85354083776473999 0.87491554021835327 0;
	setAttr -s 17 ".kox[9:16]"  0.90233957767486572 1 0.33110237121582031 
		1 1 0.52102601528167725 0.48427557945251465 1;
	setAttr -s 17 ".koy[9:16]"  -0.43102598190307617 0 0.94359481334686279 
		0 0 0.85354083776473999 0.87491554021835327 0;
createNode animCurveTA -n "char_FKExtraHair1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 7 ".ktv[0:6]"  0 1 9 1 27 1 30 1 34 1 38 1 53 1;
	setAttr -s 7 ".kit[1:6]"  1 10 3 3 3 1;
	setAttr -s 7 ".kot[1:6]"  1 10 3 3 3 1;
	setAttr -s 7 ".kix[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".kiy[1:6]"  0 0 0 0 0 0;
	setAttr -s 7 ".kox[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".koy[1:6]"  0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveHead1_M_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 9 1 27 1 30 1 34 1 38 1 53 1;
	setAttr -s 7 ".kit[1:6]"  1 10 3 3 3 1;
	setAttr -s 7 ".kot[1:6]"  1 10 3 3 3 1;
	setAttr -s 7 ".kix[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".kiy[1:6]"  0 0 0 0 0 0;
	setAttr -s 7 ".kox[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".koy[1:6]"  0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveHead1_M_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 9 1 27 1 30 1 34 1 38 1 53 1;
	setAttr -s 7 ".kit[1:6]"  1 10 3 3 3 1;
	setAttr -s 7 ".kot[1:6]"  1 10 3 3 3 1;
	setAttr -s 7 ".kix[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".kiy[1:6]"  0 0 0 0 0 0;
	setAttr -s 7 ".kox[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".koy[1:6]"  0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveHead1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 19.649599090973453 9 -11.644285720053272 
		19 -1.137976532986517 23 0.82835443029539024 27 -9.3505609836591539 30 -10.489027536102594 
		34 -10.762570033299438 38 -10.762570033299438 47 3.3741991673347469 53 19.649599090973453;
	setAttr -s 10 ".kit[1:9]"  1 1 10 1 3 3 3 10 
		1;
	setAttr -s 10 ".kot[1:9]"  1 1 10 1 3 3 3 10 
		1;
	setAttr -s 10 ".kix[1:9]"  1 0.88146167993545532 1 0.9167475700378418 
		1 1 1 0.68567776679992676 1;
	setAttr -s 10 ".kiy[1:9]"  0 0.47225546836853027 0 -0.39946705102920532 
		0 0 0 0.72790521383285522 0;
	setAttr -s 10 ".kox[1:9]"  1 0.8814617395401001 1 0.9167475700378418 
		1 1 1 0.68567776679992676 1;
	setAttr -s 10 ".koy[1:9]"  0 0.47225549817085266 0 -0.39946705102920532 
		0 0 0 0.72790521383285522 0;
createNode animCurveTA -n "char_FKCurveHead1_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -30.214171376615486 9 11.628174086821353 
		19 -9.5886924194151426 23 -24.903660086800205 27 -4.184005126421253 30 -7.3891637036425433 
		34 -7.1933132812450209 38 -7.1933132812450209 47 -22.271317716063333 53 -30.214171376615486;
	setAttr -s 10 ".kit[1:9]"  1 10 3 3 3 3 3 10 
		1;
	setAttr -s 10 ".kot[1:9]"  1 10 3 3 3 3 3 10 
		1;
	setAttr -s 10 ".kix[1:9]"  1 0.59061670303344727 1 1 1 1 1 0.77950578927993774 
		1;
	setAttr -s 10 ".kiy[1:9]"  0 -0.80695223808288574 0 0 0 0 0 -0.62639492750167847 
		0;
	setAttr -s 10 ".kox[1:9]"  1 0.59061670303344727 1 1 1 1 1 0.77950578927993774 
		1;
	setAttr -s 10 ".koy[1:9]"  0 -0.80695223808288574 0 0 0 0 0 -0.62639492750167847 
		0;
createNode animCurveTA -n "char_FKCurveHead1_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -39.886477028299176 9 -38.624922923040245 
		19 27.209913495311607 23 46.674173477893483 27 52.364525266864028 30 11.167429984683087 
		34 13.834248631199793 38 13.834248631199793 47 -7.1777112803729528 53 -39.886477028299176;
	setAttr -s 10 ".kit[1:9]"  1 10 10 3 3 3 3 10 
		1;
	setAttr -s 10 ".kot[1:9]"  1 10 10 3 3 3 3 10 
		1;
	setAttr -s 10 ".kix[1:9]"  0.98878294229507446 0.29911121726036072 
		0.51913774013519287 1 1 1 1 0.47054773569107056 1;
	setAttr -s 10 ".kiy[1:9]"  0.1493595689535141 0.95421826839447021 
		0.8546905517578125 0 0 0 0 -0.88237446546554565 0;
	setAttr -s 10 ".kox[1:9]"  0.98878294229507446 0.29911121726036072 
		0.51913774013519287 1 1 1 1 0.47054773569107056 1;
	setAttr -s 10 ".koy[1:9]"  0.14935958385467529 0.95421826839447021 
		0.8546905517578125 0 0 0 0 -0.88237446546554565 0;
createNode animCurveTA -n "char_FKExtraHead1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 7 ".ktv[0:6]"  0 1 9 1 27 1 30 1 34 1 38 1 53 1;
	setAttr -s 7 ".kit[1:6]"  1 10 3 3 3 1;
	setAttr -s 7 ".kot[1:6]"  1 10 3 3 3 1;
	setAttr -s 7 ".kix[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".kiy[1:6]"  0 0 0 0 0 0;
	setAttr -s 7 ".kox[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".koy[1:6]"  0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveNeck1_M_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 9 1 27 1 30 1 34 1 38 1 53 1;
	setAttr -s 7 ".kit[1:6]"  1 10 3 3 3 1;
	setAttr -s 7 ".kot[1:6]"  1 10 3 3 3 1;
	setAttr -s 7 ".kix[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".kiy[1:6]"  0 0 0 0 0 0;
	setAttr -s 7 ".kox[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".koy[1:6]"  0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveNeck1_M_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 9 1 27 1 30 1 34 1 38 1 53 1;
	setAttr -s 7 ".kit[1:6]"  1 10 3 3 3 1;
	setAttr -s 7 ".kot[1:6]"  1 10 3 3 3 1;
	setAttr -s 7 ".kix[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".kiy[1:6]"  0 0 0 0 0 0;
	setAttr -s 7 ".kox[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".koy[1:6]"  0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveNeck1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 16.978679829010165 3 7.6722037796158737 
		9 3.2686348558304195 19 18.542041362374558 27 115.44942676244368 30 63.187759853731862 
		34 64.769761465338291 38 64.769761465338291 53 16.978679829010165;
	setAttr -s 9 ".kit[1:8]"  10 1 10 10 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  10 1 10 10 3 3 3 1;
	setAttr -s 9 ".kix[2:8]"  1 0.29299795627593994 0.42577552795410156 
		1 1 1 1;
	setAttr -s 9 ".kiy[2:8]"  0 0.95611310005187988 0.90482878684997559 
		0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  1 0.29299795627593994 0.42577552795410156 
		1 1 1 1;
	setAttr -s 9 ".koy[2:8]"  0 0.95611310005187988 0.90482878684997559 
		0 0 0 0;
createNode animCurveTA -n "char_FKCurveNeck1_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -13.679820867901928 3 -10.521801524889396 
		9 -8.9632702549799035 19 -27.127076082238037 27 -42.215625654554685 30 -52.471627939590036 
		34 -52.707683412697989 38 -52.707683412697989 53 -13.679820867901928;
	setAttr -s 9 ".kit[1:8]"  10 1 10 10 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  10 1 10 10 3 3 3 1;
	setAttr -s 9 ".kix[2:8]"  1 0.71877098083496094 0.63817423582077026 
		1 1 1 1;
	setAttr -s 9 ".kiy[2:8]"  0 -0.69524693489074707 -0.76989197731018066 
		0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  1 0.71877098083496094 0.63817423582077026 
		1 1 1 1;
	setAttr -s 9 ".koy[2:8]"  0 -0.69524693489074707 -0.76989197731018066 
		0 0 0 0;
createNode animCurveTA -n "char_FKCurveNeck1_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -6.4072944111053358 3 -0.29107239215523245 
		9 7.6012918895798389 19 7.4788437311948295 27 -72.268265577018113 30 -29.770981049351267 
		34 -30.937623276318053 38 -30.937623276318053 53 -6.4072944111053358;
	setAttr -s 9 ".kit[1:8]"  10 1 10 10 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  10 1 10 10 3 3 3 1;
	setAttr -s 9 ".kix[2:8]"  1 1 0.49124547839164734 1 1 1 1;
	setAttr -s 9 ".kiy[2:8]"  0 0 -0.87102121114730835 0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  1 1 0.49124547839164734 1 1 1 1;
	setAttr -s 9 ".koy[2:8]"  0 0 -0.87102121114730835 0 0 0 0;
createNode animCurveTA -n "char_FKExtraNeck1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 15 1 22 1 27 1 30 1 34 1 38 1 53 
		1;
	setAttr -s 9 ".kit[1:8]"  10 3 9 10 3 9 3 1;
	setAttr -s 9 ".kot[1:8]"  10 3 9 10 3 9 3 1;
	setAttr -s 9 ".kix[8]"  1;
	setAttr -s 9 ".kiy[8]"  0;
	setAttr -s 9 ".kox[8]"  1;
	setAttr -s 9 ".koy[8]"  0;
createNode animCurveTU -n "char_FKCurveSpine3_M_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 15 1 22 1 27 1 30 1 34 1 38 1 53 
		1;
	setAttr -s 9 ".kit[1:8]"  10 3 9 10 3 9 3 1;
	setAttr -s 9 ".kot[1:8]"  10 3 9 10 3 9 3 1;
	setAttr -s 9 ".kix[8]"  1;
	setAttr -s 9 ".kiy[8]"  0;
	setAttr -s 9 ".kox[8]"  1;
	setAttr -s 9 ".koy[8]"  0;
createNode animCurveTU -n "char_FKCurveSpine3_M_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 15 1 22 1 27 1 30 1 34 1 38 1 53 
		1;
	setAttr -s 9 ".kit[1:8]"  10 3 9 10 3 9 3 1;
	setAttr -s 9 ".kot[1:8]"  10 3 9 10 3 9 3 1;
	setAttr -s 9 ".kix[8]"  1;
	setAttr -s 9 ".kiy[8]"  0;
	setAttr -s 9 ".kox[8]"  1;
	setAttr -s 9 ".koy[8]"  0;
createNode animCurveTA -n "char_FKCurveSpine3_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -4.1759924717065973 9 2.1552350212488749 
		15 5.5944198084091301 22 2.6768558870410928 27 -9.4581257762622588 30 0.27940843982239216 
		34 -2.1084913893326003 38 -2.8754938162980013 53 -4.1759924717065973;
	setAttr -s 9 ".kit[1:8]"  10 3 9 10 3 9 3 1;
	setAttr -s 9 ".kot[1:8]"  10 3 9 10 3 9 3 1;
	setAttr -s 9 ".kix[8]"  1;
	setAttr -s 9 ".kiy[8]"  0;
	setAttr -s 9 ".kox[8]"  1;
	setAttr -s 9 ".koy[8]"  0;
createNode animCurveTA -n "char_FKCurveSpine3_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -1.201 9 -15.837321805785114 15 -24.544322779598577 
		22 -2.9206737826924951 27 -5.1964791993011028 30 -1.7662304730518328 34 -4.4716034930068673 
		38 -5.9611492812069811 53 -1.201;
	setAttr -s 9 ".kit[1:8]"  10 3 9 10 3 9 3 1;
	setAttr -s 9 ".kot[1:8]"  10 3 9 10 3 9 3 1;
	setAttr -s 9 ".kix[8]"  1;
	setAttr -s 9 ".kiy[8]"  0;
	setAttr -s 9 ".kox[8]"  1;
	setAttr -s 9 ".koy[8]"  0;
createNode animCurveTA -n "char_FKCurveSpine3_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -38.617693158088045 9 -21.006997238691973 
		15 8.9206161704577767 22 -7.3197561523601387 27 -57.842154552092786 30 3.8501089147386836 
		34 -21.221190276002606 38 -32.576640694635813 53 -38.617693158088045;
	setAttr -s 9 ".kit[1:8]"  10 3 9 10 3 9 1 1;
	setAttr -s 9 ".kot[1:8]"  10 3 9 10 3 9 1 1;
	setAttr -s 9 ".kix[7:8]"  0.62765425443649292 1;
	setAttr -s 9 ".kiy[7:8]"  -0.778492271900177 0;
	setAttr -s 9 ".kox[7:8]"  0.62765425443649292 1;
	setAttr -s 9 ".koy[7:8]"  -0.778492271900177 0;
createNode animCurveTA -n "char_FKExtraSpine3_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 15 1 22 1 27 1 30 1 34 1 38 1 53 
		1;
	setAttr -s 9 ".kit[1:8]"  10 10 3 10 3 9 3 1;
	setAttr -s 9 ".kot[1:8]"  10 10 3 10 3 9 3 1;
	setAttr -s 9 ".kix[8]"  1;
	setAttr -s 9 ".kiy[8]"  0;
	setAttr -s 9 ".kox[8]"  1;
	setAttr -s 9 ".koy[8]"  0;
createNode animCurveTU -n "char_FKCurveSpine4_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 15 1 22 1 27 1 30 1 34 1 38 1 53 
		1;
	setAttr -s 9 ".kit[1:8]"  10 10 3 10 3 9 3 1;
	setAttr -s 9 ".kot[1:8]"  10 10 3 10 3 9 3 1;
	setAttr -s 9 ".kix[8]"  1;
	setAttr -s 9 ".kiy[8]"  0;
	setAttr -s 9 ".kox[8]"  1;
	setAttr -s 9 ".koy[8]"  0;
createNode animCurveTU -n "char_FKCurveSpine4_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 15 1 22 1 27 1 30 1 34 1 38 1 53 
		1;
	setAttr -s 9 ".kit[1:8]"  10 10 3 10 3 9 3 1;
	setAttr -s 9 ".kot[1:8]"  10 10 3 10 3 9 3 1;
	setAttr -s 9 ".kix[8]"  1;
	setAttr -s 9 ".kiy[8]"  0;
	setAttr -s 9 ".kox[8]"  1;
	setAttr -s 9 ".koy[8]"  0;
createNode animCurveTA -n "char_FKCurveSpine4_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 19.548247782583122 3 26.782990971087862 
		9 8.0452943233609435 15 -2.6182852314206024 22 -22.480820747593238 27 7.35478142923668 
		30 -29.737515190132321 34 -12.879000917478663 38 -14.897289177447087 53 19.548247782583122;
	setAttr -s 10 ".kit[1:9]"  10 10 10 3 10 3 3 3 
		1;
	setAttr -s 10 ".kot[1:9]"  10 10 10 3 10 3 3 3 
		1;
	setAttr -s 10 ".kix[9]"  1;
	setAttr -s 10 ".kiy[9]"  0;
	setAttr -s 10 ".kox[9]"  1;
	setAttr -s 10 ".koy[9]"  0;
createNode animCurveTA -n "char_FKCurveSpine4_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 4.2832309672587163 3 3.3445319968126874 
		9 3.7698553491907387 15 3.4909846850544555 22 5.5304990160832688 27 9.0221122426315254 
		30 8.5320284528613328 34 8.478601644799749 38 8.5558128724041911 53 4.2832309672587163;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 3 10 3 9 
		3 1;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 3 10 3 9 
		3 1;
	setAttr -s 10 ".kix[9]"  1;
	setAttr -s 10 ".kiy[9]"  0;
	setAttr -s 10 ".kox[9]"  1;
	setAttr -s 10 ".koy[9]"  0;
createNode animCurveTA -n "char_FKCurveSpine4_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 5.393 3 5.289373128607421 9 2.6609646365777002 
		15 1.1768962674786003 22 3.5381690422678895 27 9.7143510542010389 30 10.762186281775548 
		34 11.632112687131713 38 11.546605813784138 53 5.393;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 3 10 3 9 
		3 1;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 3 10 3 9 
		3 1;
	setAttr -s 10 ".kix[9]"  1;
	setAttr -s 10 ".kiy[9]"  0;
	setAttr -s 10 ".kox[9]"  1;
	setAttr -s 10 ".koy[9]"  0;
createNode animCurveTA -n "char_FKExtraSpine4_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 8 ".ktv[0:7]"  0 1 9 1 22 1 27 1 34 1 38 1 47 1 53 1;
	setAttr -s 8 ".kit[1:7]"  1 3 10 3 3 3 1;
	setAttr -s 8 ".kot[1:7]"  1 3 10 3 3 3 1;
	setAttr -s 8 ".kix[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".kiy[1:7]"  0 0 0 0 0 0 0;
	setAttr -s 8 ".kox[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".koy[1:7]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurvePelvis1_M_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 9 1 22 1 27 1 34 1 38 1 47 1 53 1;
	setAttr -s 8 ".kit[1:7]"  1 3 10 3 3 3 1;
	setAttr -s 8 ".kot[1:7]"  1 3 10 3 3 3 1;
	setAttr -s 8 ".kix[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".kiy[1:7]"  0 0 0 0 0 0 0;
	setAttr -s 8 ".kox[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".koy[1:7]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurvePelvis1_M_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 9 1 22 1 27 1 34 1 38 1 47 1 53 1;
	setAttr -s 8 ".kit[1:7]"  1 3 10 3 3 3 1;
	setAttr -s 8 ".kot[1:7]"  1 3 10 3 3 3 1;
	setAttr -s 8 ".kix[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".kiy[1:7]"  0 0 0 0 0 0 0;
	setAttr -s 8 ".kox[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".koy[1:7]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurvePelvis1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 22.842862988065157 22 22.842862988065157 
		27 11.755078576380047 30 0.4163007934468359 34 6.623016032345487 38 0.58437725410949704 
		47 1.5131268240297662 53 0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 10 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 10 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 0.56303578615188599 0.93357622623443604 
		1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 -0.82643246650695801 -0.35837876796722412 
		0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 0.56303578615188599 0.93357622623443604 
		1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 -0.82643246650695801 -0.35837876796722412 
		0 0 0 0;
createNode animCurveTA -n "char_FKCurvePelvis1_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 -1.4581216654551474 22 -1.4581216654551474 
		27 5.4917673872291326 30 8.3135302672326397 34 8.7085746381789324 38 -0.30623066173798003 
		47 -0.75594070878494846 53 0;
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
		22 -4.76808390348695 27 -2.079989229254299 30 -39.721297326483196 34 -0.8357848435783376 
		38 -1.1579398580721627 47 -21.335077861456867 53 -0.83191351642244571;
	setAttr -s 9 ".kit[1:8]"  1 3 10 10 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 10 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 0.9956972599029541 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0.092665828764438629 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 0.9956972599029541 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0.092665828764438629 0 0 0 0;
createNode animCurveTA -n "char_FKExtraPelvis1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 9 0 22 0 27 0 30 0 38 0 53 0;
	setAttr -s 8 ".kit[1:7]"  10 1 3 10 3 3 1;
	setAttr -s 8 ".kot[1:7]"  10 1 3 10 3 3 1;
	setAttr -s 8 ".kix[2:7]"  1 1 1 1 1 1;
	setAttr -s 8 ".kiy[2:7]"  0 0 0 0 0 0;
	setAttr -s 8 ".kox[2:7]"  1 1 1 1 1 1;
	setAttr -s 8 ".koy[2:7]"  0 0 0 0 0 0;
createNode animCurveTA -n "char_RootCurveRoot1_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 3.0405827598215973 3 1.1862675627745136 
		9 -5.7342276833307935 15 6.1891767831681772 22 -6.7670474788783732 27 -10.884252715826294 
		30 -4.4747150497444279 34 -5.3203006506799575 38 -5.2253523696138329 53 3.0405827598215973;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 3 10 3 10 
		3 1;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 3 10 3 10 
		3 1;
	setAttr -s 10 ".kix[9]"  1;
	setAttr -s 10 ".kiy[9]"  0;
	setAttr -s 10 ".kox[9]"  1;
	setAttr -s 10 ".koy[9]"  0;
createNode animCurveTA -n "char_RootCurveRoot1_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 23.714440424736864 3 17.558097593986059 
		9 -8.86950929521403 15 10.539749727123892 22 10.574335621353628 27 -3.2358871566527179 
		30 3.2327000092307454 34 -0.69375216559502584 38 -1.4113064676692411 53 23.714440424736864;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 3 10 3 10 
		3 1;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 3 10 3 10 
		3 1;
	setAttr -s 10 ".kix[9]"  1;
	setAttr -s 10 ".kiy[9]"  0;
	setAttr -s 10 ".kox[9]"  1;
	setAttr -s 10 ".koy[9]"  0;
createNode animCurveTA -n "char_RootCurveRoot1_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 8.6470827930312559 3 -3.2108037797679256 
		9 22.021998868284449 15 7.8432759614855527 22 8.5315890036059088 27 -31.777351022542401 
		30 78.532366732074294 34 38.158910763546992 38 27.438165946026135 53 8.6470827930312577;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 3 10 3 10 
		9 1;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 3 10 3 10 
		9 1;
	setAttr -s 10 ".kix[9]"  1;
	setAttr -s 10 ".kiy[9]"  0;
	setAttr -s 10 ".kox[9]"  1;
	setAttr -s 10 ".koy[9]"  0;
createNode animCurveTL -n "char_RootCurveRoot1_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.11500744677504726 3 -0.10308673019935877 
		9 -0.043859246129274693 15 -0.060300904953272172 22 0.14863634019373445 27 -0.045272253618358099 
		30 0.028281927910081328 38 -0.032382146104468899 44 0.1014164606967938 53 -0.11500744677504726;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 3 10 3 3 
		10 1;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 3 10 3 3 
		10 1;
	setAttr -s 10 ".kix[9]"  1;
	setAttr -s 10 ".kiy[9]"  0;
	setAttr -s 10 ".kox[9]"  1;
	setAttr -s 10 ".koy[9]"  0;
createNode animCurveTL -n "char_RootCurveRoot1_M_translateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.26403992941414445 3 -0.26437829849217831 
		9 -0.35742997693530748 15 -0.16810886129215055 22 -0.72729432788976478 27 -0.75439797420732335 
		30 -0.75439797420732335 38 -0.75439797420732335 44 -0.14424564493373657 53 -0.26403992941414445;
	setAttr -s 10 ".kit[0:9]"  3 10 10 3 1 10 1 1 
		3 1;
	setAttr -s 10 ".kot[0:9]"  3 10 10 3 1 10 1 1 
		3 1;
	setAttr -s 10 ".kix[4:9]"  0.96337312459945679 1 1 1 1 1;
	setAttr -s 10 ".kiy[4:9]"  -0.26816478371620178 0 0 0 0 0;
	setAttr -s 10 ".kox[4:9]"  0.96337306499481201 1 1 1 1 1;
	setAttr -s 10 ".koy[4:9]"  -0.26816475391387939 0 0 0 0 0;
createNode animCurveTL -n "char_RootCurveRoot1_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.0438000161016944 3 0.04951188598577394 
		9 -0.07160810243879398 15 -0.20045551183038718 22 -0.07289493616749454 27 -0.035570591122703013 
		30 -0.028592909366213753 38 -0.025846313891582692 44 -0.029423814153845484 53 -0.0438000161016944;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 1 1 3 3 
		10 1;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 1 1 3 3 
		10 1;
	setAttr -s 10 ".kix[4:9]"  0.96082890033721924 0.99249833822250366 
		1 1 1 1;
	setAttr -s 10 ".kiy[4:9]"  0.27714231610298157 0.12225836515426636 
		0 0 0 0;
	setAttr -s 10 ".kox[4:9]"  0.96082890033721924 0.99249833822250366 
		1 1 1 1;
	setAttr -s 10 ".koy[4:9]"  0.27714231610298157 0.12225840985774994 
		0 0 0 0;
createNode animCurveTA -n "char_RootExtraRoot1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 -1.2960781342528835 22 66.461163309425402 
		27 60.627655188061588 30 57.927573059983601 34 57.927573059983601 38 57.927573059983601 
		47 26.900860541006267 53 0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 11.097799452881013 22 8.8562192445419878 
		27 -6.6006199541288275 30 -13.754931632218884 34 -13.754931632218884 38 -13.754931632218884 
		47 5.1811201591342284 53 0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 0.55988430976867676 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 -0.82857078313827515 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 0.55988430976867676 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 -0.82857078313827515 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 -32.520863427474922 22 3.4986940569081706 
		27 14.490749023129666 30 19.578502489427535 34 19.578502489427535 38 19.578502489427535 
		47 -1.9762778550407079 53 0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 0.68882185220718384 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0.72493064403533936 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 0.68882185220718384 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0.72493064403533936 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 2.1942103669999999e-008 9 2.1942103669999999e-008 
		22 2.1942103669999999e-008 27 2.1942103669999999e-008 30 2.1942103669999999e-008 
		34 2.1942103669999999e-008 38 2.1942103669999999e-008 47 2.1942103669999999e-008 
		53 2.1942103669999999e-008;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 18 1 27 1 30 1 34 1 38 1 53 1;
	setAttr -s 8 ".kit[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kot[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 18 1 27 1 30 1 34 1 38 1 53 1;
	setAttr -s 8 ".kit[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kot[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 18 1 27 1 30 1 34 1 38 1 53 1;
	setAttr -s 8 ".kit[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kot[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTA -n "char_FKCurveR_Shoulder1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -0.68127875452050601 3 6.7015101581334182 
		7 14.728150622418728 12 49.275604344087988 18 10.643269053716526 27 32.700758655165423 
		30 43.350195658196846 34 42.350577201947608 38 42.350577201947608 42 44.123321077587299 
		45 16.319957728816011 53 -0.68127875452050601;
	setAttr -s 12 ".kit[1:11]"  1 1 10 3 10 3 3 3 
		10 10 1;
	setAttr -s 12 ".kot[1:11]"  1 1 10 3 10 3 3 3 
		10 10 1;
	setAttr -s 12 ".kix[1:11]"  0.74944698810577393 0.65065085887908936 
		0.98161625862121582 1 0.57385653257369995 1 1 1 1 0.42453819513320923 1;
	setAttr -s 12 ".kiy[1:11]"  0.66206437349319458 0.759377121925354 -0.19086536765098572 
		0 0.81895583868026733 0 0 0 0 -0.9054100513458252 0;
	setAttr -s 12 ".kox[1:11]"  0.74944698810577393 0.65065097808837891 
		0.98161625862121582 1 0.57385653257369995 1 1 1 1 0.42453819513320923 1;
	setAttr -s 12 ".koy[1:11]"  0.66206437349319458 0.75937700271606445 
		-0.19086536765098572 0 0.81895583868026733 0 0 0 0 -0.9054100513458252 0;
createNode animCurveTA -n "char_FKExtraR_Shoulder1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 8 ".ktv[0:7]"  0 1 22 1 27 1 30 1 34 1 38 1 47 1 53 1;
	setAttr -s 8 ".kit[2:7]"  10 3 3 3 9 1;
	setAttr -s 8 ".kot[2:7]"  10 3 3 3 9 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 22 1 27 1 30 1 34 1 38 1 47 1 53 1;
	setAttr -s 8 ".kit[2:7]"  10 3 3 3 9 1;
	setAttr -s 8 ".kot[2:7]"  10 3 3 3 9 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 22 1 27 1 30 1 34 1 38 1 47 1 53 1;
	setAttr -s 8 ".kit[2:7]"  10 3 3 3 9 1;
	setAttr -s 8 ".kot[2:7]"  10 3 3 3 9 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTA -n "char_FKCurveR_Elbow1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 48.213367515818511 10 10.37057372646967 
		22 56.960230547241977 27 41.335327791157709 30 4.3908859224067625 34 6.5585667762089361 
		38 6.5585667762089361 42 48.080438767926907 47 53.692516726423101 50 41.309583190089498 
		53 48.213367515818511;
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
		22 -83.798780827240449 27 -83.798780827240449 30 -83.798780827240449 34 -83.798780827240449 
		38 -83.798780827240449 47 -83.798780827240449 53 -83.798780827240449;
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
		22 -0.15209529104924274 27 -0.15209529104924274 30 -0.15209529104924274 34 -0.15209529104924274 
		38 -0.15209529104924274 47 -0.15209529104924274 53 -0.15209529104924274;
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
		22 -4.6558253190878789 27 -4.6558253190878789 30 -4.6558253190878789 34 -4.6558253190878789 
		38 -4.6558253190878789 47 -4.6558253190878789 53 -4.6558253190878789;
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
		22 0.038939746117583683 27 0.038939746117583683 30 0.038939746117583683 34 0.038939746117583683 
		38 0.038939746117583683 47 0.070796223027113955 53 0.070796223027113955;
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
		22 -0.055087414590916595 27 -0.055087414590916595 30 -0.055087414590916595 34 -0.055087414590916595 
		38 -0.055087414590916595 47 0.0024602716719113347 53 0.0024602716719113347;
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
		22 0.020010939989264866 27 0.020010939989264866 30 0.020010939989264866 34 0.020010939989264866 
		38 0.020010939989264866 47 0.20119425626585011 53 0.20119425626585011;
	setAttr -s 9 ".kit[1:8]"  1 1 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 1 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKExtraDevice3_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
		22 64.163191954635607 27 64.163191954635607 30 64.163191954635607 34 64.163191954635607 
		38 64.163191954635607 47 64.163191954635607 53 64.163191954635607;
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
		22 2.4325234183121345 27 2.4325234183121345 30 2.4325234183121345 34 2.4325234183121345 
		38 2.4325234183121345 47 2.4325234183121345 53 2.4325234183121345;
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
		22 8.5957802944005888 27 8.5957802944005888 30 8.5957802944005888 34 8.5957802944005888 
		38 8.5957802944005888 47 8.5957802944005888 53 8.5957802944005888;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb5_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
		22 30.907503992135247 27 30.907503992135247 30 30.907503992135247 34 30.907503992135247 
		38 30.907503992135247 47 30.907503992135247 53 30.907503992135247;
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
		22 -37.423813770375673 27 -37.423813770375673 30 -37.423813770375673 34 -37.423813770375673 
		38 -37.423813770375673 47 -37.423813770375673 53 -37.423813770375673;
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
		22 -55.763523784114774 27 -55.763523784114774 30 -55.763523784114774 34 -55.763523784114774 
		38 -55.763523784114774 47 -55.763523784114774 53 -55.763523784114774;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb6_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
		22 65.894016206888068 27 65.894016206888068 30 65.894016206888068 34 65.894016206888068 
		38 65.894016206888068 47 65.894016206888068 53 65.894016206888068;
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
		22 18.465908619718412 27 18.465908619718412 30 18.465908619718412 34 18.465908619718412 
		38 18.465908619718412 47 18.465908619718412 53 18.465908619718412;
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
		22 -36.952741198413079 27 -36.952741198413079 30 -36.952741198413079 34 -36.952741198413079 
		38 -36.952741198413079 47 -36.952741198413079 53 -36.952741198413079;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle5_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
		22 17.446522746060875 27 17.446522746060875 30 17.446522746060875 34 17.446522746060875 
		38 17.446522746060875 47 17.446522746060875 53 17.446522746060875;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle6_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 10 ".ktv[0:9]"  0 1 3 1 9 1 18 1 27 1 30 1 34 1 38 1 47 
		1 53 1;
	setAttr -s 10 ".kit[1:9]"  10 10 3 10 3 3 3 9 
		1;
	setAttr -s 10 ".kot[1:9]"  10 10 3 10 3 3 3 9 
		1;
	setAttr -s 10 ".kix[9]"  1;
	setAttr -s 10 ".kiy[9]"  0;
	setAttr -s 10 ".kox[9]"  1;
	setAttr -s 10 ".koy[9]"  0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 3 1 9 1 18 1 27 1 30 1 34 1 38 1 47 
		1 53 1;
	setAttr -s 10 ".kit[1:9]"  10 10 3 10 3 3 3 9 
		1;
	setAttr -s 10 ".kot[1:9]"  10 10 3 10 3 3 3 9 
		1;
	setAttr -s 10 ".kix[9]"  1;
	setAttr -s 10 ".kiy[9]"  0;
	setAttr -s 10 ".kox[9]"  1;
	setAttr -s 10 ".koy[9]"  0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 3 1 9 1 18 1 27 1 30 1 34 1 38 1 47 
		1 53 1;
	setAttr -s 10 ".kit[1:9]"  10 10 3 10 3 3 3 9 
		1;
	setAttr -s 10 ".kot[1:9]"  10 10 3 10 3 3 3 9 
		1;
	setAttr -s 10 ".kix[9]"  1;
	setAttr -s 10 ".kiy[9]"  0;
	setAttr -s 10 ".kox[9]"  1;
	setAttr -s 10 ".koy[9]"  0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 3 -9.7099612269341122 9 -10.162970020619548 
		14 -14.418787759539905 18 -46.876704027513874 27 -68.147061640003585 30 -78.669908868060404 
		34 -78.679439495546163 38 -78.679439495546163 42 -51.639930485438605 47 -6.7986370362520576 
		50 3.090079619538268 53 0;
	setAttr -s 13 ".kit[1:12]"  10 10 3 9 10 3 3 3 
		10 9 10 1;
	setAttr -s 13 ".kot[1:12]"  10 10 3 9 10 3 3 3 
		10 9 10 1;
	setAttr -s 13 ".kix[12]"  1;
	setAttr -s 13 ".kiy[12]"  0;
	setAttr -s 13 ".kox[12]"  1;
	setAttr -s 13 ".koy[12]"  0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 24.211026325508492 3 39.913297397905815 
		9 27.297679162445231 14 66.714774966943736 18 55.999392003811217 27 54.612821209480899 
		30 66.824586216346248 34 65.437021389761753 38 65.437021389761753 42 47.84783656598092 
		47 24.92756563076944 50 32.92423406983896 53 24.211026325508492;
	setAttr -s 13 ".kit[1:12]"  10 10 3 9 3 3 3 3 
		10 3 10 1;
	setAttr -s 13 ".kot[1:12]"  10 10 3 9 3 3 3 3 
		10 3 10 1;
	setAttr -s 13 ".kix[12]"  1;
	setAttr -s 13 ".kiy[12]"  0;
	setAttr -s 13 ".kox[12]"  1;
	setAttr -s 13 ".koy[12]"  0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 3 -1.0134453754851236 9 1.2947066242147538 
		14 -20.79874536292877 18 12.127517796976752 27 11.548032223814603 30 15.993359403077292 
		34 15.94184663579923 38 15.94184663579923 42 -1.951331011071421 47 5.0988398992036164 
		50 4.6082229836562796 53 0;
	setAttr -s 13 ".kit[1:12]"  10 10 10 1 1 3 3 3 
		3 3 1 1;
	setAttr -s 13 ".kot[1:12]"  10 10 10 1 1 3 3 3 
		3 3 1 1;
	setAttr -s 13 ".kix[4:12]"  0.98833376169204712 0.99926227331161499 
		1 1 1 1 1 0.99352824687957764 1;
	setAttr -s 13 ".kiy[4:12]"  0.15230390429496765 0.038404252380132675 
		0 0 0 0 0 -0.11358524113893509 0;
	setAttr -s 13 ".kox[4:12]"  0.98833370208740234 0.99926227331161499 
		1 1 1 1 1 0.99352824687957764 1;
	setAttr -s 13 ".koy[4:12]"  0.15230397880077362 0.038404226303100586 
		0 0 0 0 0 -0.1135852113366127 0;
createNode animCurveTA -n "char_FKExtraR_Wrist1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
		0;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ball1_L_scaleZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 12 1 20 1 27 1 38 1 47 1 53 1;
	setAttr -s 7 ".kit[0:6]"  3 1 1 1 1 3 1;
	setAttr -s 7 ".kot[0:6]"  3 1 1 1 1 3 1;
	setAttr -s 7 ".kix[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".kiy[1:6]"  0 0 0 0 0 0;
	setAttr -s 7 ".kox[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".koy[1:6]"  0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ball1_L_scaleY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 12 1 20 1 27 1 38 1 47 1 53 1;
	setAttr -s 7 ".kit[0:6]"  3 1 1 1 1 3 1;
	setAttr -s 7 ".kot[0:6]"  3 1 1 1 1 3 1;
	setAttr -s 7 ".kix[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".kiy[1:6]"  0 0 0 0 0 0;
	setAttr -s 7 ".kox[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".koy[1:6]"  0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ball1_L_scaleX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 12 1 20 1 27 1 38 1 47 1 53 1;
	setAttr -s 7 ".kit[0:6]"  3 1 1 1 1 3 1;
	setAttr -s 7 ".kot[0:6]"  3 1 1 1 1 3 1;
	setAttr -s 7 ".kix[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".kiy[1:6]"  0 0 0 0 0 0;
	setAttr -s 7 ".kox[1:6]"  1 1 1 1 1 1;
	setAttr -s 7 ".koy[1:6]"  0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ball1_L_rotateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 12 0 20 0 27 0 38 0 43 28.338467806512103 
		47 0 53 0;
	setAttr -s 8 ".kit[0:7]"  3 1 1 1 1 10 3 1;
	setAttr -s 8 ".kot[0:7]"  3 1 1 1 1 10 3 1;
	setAttr -s 8 ".kix[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".kiy[1:7]"  0 0 0 0 0 0 0;
	setAttr -s 8 ".kox[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".koy[1:7]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ball1_L_rotateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 12 0 20 0 27 0 38 0 43 6.5717124887163134 
		47 0 53 0;
	setAttr -s 8 ".kit[0:7]"  3 1 1 1 1 10 3 1;
	setAttr -s 8 ".kot[0:7]"  3 1 1 1 1 10 3 1;
	setAttr -s 8 ".kix[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".kiy[1:7]"  0 0 0 0 0 0 0;
	setAttr -s 8 ".kox[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".koy[1:7]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ball1_L_rotateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 12 0 20 0 27 0 38 0 43 -2.5065209657332086 
		47 0 53 0;
	setAttr -s 8 ".kit[0:7]"  3 1 1 1 1 10 3 1;
	setAttr -s 8 ".kot[0:7]"  3 1 1 1 1 10 3 1;
	setAttr -s 8 ".kix[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".kiy[1:7]"  0 0 0 0 0 0 0;
	setAttr -s 8 ".kox[1:7]"  1 1 1 1 1 1 1;
	setAttr -s 8 ".koy[1:7]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ball1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 10 ".ktv[0:9]"  0 1 9 1 18 1 22 1 27 1 30 1 34 1 38 1 47 
		1 53 1;
	setAttr -s 10 ".kit[1:9]"  1 10 3 10 3 3 3 3 
		1;
	setAttr -s 10 ".kot[1:9]"  1 10 3 10 3 3 3 3 
		1;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Clavicle1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 9 1 18 1 22 1 27 1 30 1 34 1 38 1 47 
		1 53 1;
	setAttr -s 10 ".kit[1:9]"  1 10 3 10 3 3 3 3 
		1;
	setAttr -s 10 ".kot[1:9]"  1 10 3 10 3 3 3 3 
		1;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Clavicle1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 9 1 18 1 22 1 27 1 30 1 34 1 38 1 47 
		1 53 1;
	setAttr -s 10 ".kit[1:9]"  1 10 3 10 3 3 3 3 
		1;
	setAttr -s 10 ".kot[1:9]"  1 10 3 10 3 3 3 3 
		1;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 9 0 18 34.372143645106519 22 0 27 24.179521757431925 
		30 35.371191196207185 34 35.371191196207185 38 35.371191196207185 47 0 53 0;
	setAttr -s 10 ".kit[1:9]"  1 10 3 10 3 3 3 3 
		1;
	setAttr -s 10 ".kot[1:9]"  1 10 3 10 3 3 3 3 
		1;
	setAttr -s 10 ".kix[1:9]"  1 1 1 0.39654427766799927 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0.91801553964614868 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 0.39654427766799927 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0.91801553964614868 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 9 0 18 11.957237006386116 22 0 27 -16.307418007125815 
		30 -23.855426341061829 34 -23.855426341061829 38 -23.855426341061829 47 0 53 0;
	setAttr -s 10 ".kit[1:9]"  1 10 3 10 3 3 3 3 
		1;
	setAttr -s 10 ".kot[1:9]"  1 10 3 10 3 3 3 3 
		1;
	setAttr -s 10 ".kix[1:9]"  1 1 1 0.53933918476104736 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 -0.84208863973617554 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 0.53933918476104736 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 -0.84208863973617554 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 9 0 18 6.4877705917744013 22 0 27 -5.7073465023618448 
		30 -8.3490337974114723 34 -8.3490337974114723 38 -8.3490337974114723 47 0 53 0;
	setAttr -s 10 ".kit[1:9]"  1 10 3 10 3 3 3 3 
		1;
	setAttr -s 10 ".kot[1:9]"  1 10 3 10 3 3 3 3 
		1;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -2.194210208e-008 9 -2.194210208e-008 
		22 -2.194210208e-008 27 -2.194210208e-008 30 -2.194210208e-008 34 -2.194210208e-008 
		38 -2.194210208e-008 47 -2.194210208e-008 53 -2.194210208e-008;
	setAttr -s 9 ".kit[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kot[1:8]"  1 3 10 3 3 3 3 1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 8 ".ktv[0:7]"  0 1 18 1 22 1 27 1 30 1 34 1 38 1 53 1;
	setAttr -s 8 ".kit[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kot[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 18 1 22 1 27 1 30 1 34 1 38 1 53 1;
	setAttr -s 8 ".kit[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kot[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 18 1 22 1 27 1 30 1 34 1 38 1 53 1;
	setAttr -s 8 ".kit[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kot[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTA -n "char_FKCurveR_Shoulder1_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 17.19229314797029 9 -7.7945943832934912 
		18 17.552988648257653 22 42.013635280036965 24 49.718456358889341 26 39.01620287623291 
		27 18.263978310736075 30 9.6684676402462308 34 4.2817059612524782 38 4.2817059612524782 
		41 13.181910898957232 44 30.063103456447813 49 12.888573410984803 53 17.19229314797029;
	setAttr -s 14 ".kit[0:13]"  3 10 10 3 10 10 10 3 
		3 3 10 10 10 1;
	setAttr -s 14 ".kot[0:13]"  3 10 10 3 10 10 10 3 
		3 3 10 10 10 1;
	setAttr -s 14 ".kix[13]"  1;
	setAttr -s 14 ".kiy[13]"  0;
	setAttr -s 14 ".kox[13]"  1;
	setAttr -s 14 ".koy[13]"  0;
createNode animCurveTA -n "char_FKExtraR_Shoulder1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 8 ".ktv[0:7]"  0 1 18 1 22 1 27 1 30 1 34 1 38 1 53 1;
	setAttr -s 8 ".kit[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kot[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 18 1 22 1 27 1 30 1 34 1 38 1 53 1;
	setAttr -s 8 ".kit[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kot[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 18 1 22 1 27 1 30 1 34 1 38 1 53 1;
	setAttr -s 8 ".kit[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kot[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTA -n "char_FKCurveR_Elbow1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 36.067317209388015 18 98.673024871974718 
		22 95.153421120403863 27 117.11175485446147 30 102.99017033930852 34 103.83575275177071 
		38 103.83575275177071 49 52.688434290166128 53 36.067317209388015;
	setAttr -s 9 ".kit[1:8]"  10 3 10 3 3 3 10 1;
	setAttr -s 9 ".kot[1:8]"  10 3 10 3 3 3 10 1;
	setAttr -s 9 ".kix[8]"  1;
	setAttr -s 9 ".kiy[8]"  0;
	setAttr -s 9 ".kox[8]"  1;
	setAttr -s 9 ".koy[8]"  0;
createNode animCurveTA -n "char_FKExtraR_Elbow1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 10 ".ktv[0:9]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 41 1 47 
		1 53 1;
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
	setAttr -s 10 ".ktv[0:9]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 41 1 47 
		1 53 1;
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
	setAttr -s 10 ".ktv[0:9]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 41 1 47 
		1 53 1;
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
		22 27.905251822156437 27 27.905251822156437 30 27.905251822156437 34 27.905251822156437 
		38 27.905251822156437 41 19.261980434307446 47 27.905251822156437 51 40.069677096503952 
		53 27.905251822156437;
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
	setAttr -s 11 ".ktv[0:10]"  0 0 9 -9.9430254580064652 22 0 27 0 30 
		0 34 0 38 0 41 2.3869127895860891 47 0 51 7.4387832149840536 53 0;
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
	setAttr -s 11 ".ktv[0:10]"  0 0 9 14.326287802596285 22 0 27 0 30 0 
		34 0 38 0 41 -11.819045108965327 47 0 51 3.3070573943716166 53 0;
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 10 ".ktv[0:9]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 41 1 47 
		1 53 1;
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
	setAttr -s 10 ".ktv[0:9]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 41 1 47 
		1 53 1;
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
	setAttr -s 10 ".ktv[0:9]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 41 1 47 
		1 53 1;
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
		14 38.295136570964978 22 21.821476003942252 27 21.821476003942252 30 21.821476003942252 
		34 21.821476003942252 38 21.821476003942252 41 19.391947340764041 47 28.959457180709169 
		51 43.148960212739993 53 28.959457180709169;
	setAttr -s 12 ".kit[0:11]"  3 1 10 3 1 1 1 1 
		10 3 10 1;
	setAttr -s 12 ".kot[0:11]"  3 1 10 3 1 1 1 1 
		10 3 10 1;
	setAttr -s 12 ".kix[1:11]"  1 0.99372053146362305 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[1:11]"  0 0.11189030855894089 0 0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[1:11]"  1 0.99372053146362305 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[1:11]"  0 0.11189030855894089 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb6_R_rotateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -12.483272772594933 9 -12.078447682014165 
		14 -7.7250360052022797 22 -7.7195164525836812 27 -7.7195164525836812 30 -7.7195164525836812 
		34 -7.7195164525836812 38 -7.7195164525836812 41 -18.694141118612428 47 -12.483272772594933 
		51 -9.5555687008010999 53 -12.483272772594933;
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
		14 40.213088386526422 22 5.6667086511936748 27 5.6667086511936748 30 5.6667086511936748 
		34 5.6667086511936748 38 5.6667086511936748 41 20.941917813515158 47 21.335853393578894 
		51 21.122638291690549 53 21.335853393578894;
	setAttr -s 12 ".kit[0:11]"  3 1 10 3 1 1 1 1 
		10 3 10 1;
	setAttr -s 12 ".kot[0:11]"  3 1 10 3 1 1 1 1 
		10 3 10 1;
	setAttr -s 12 ".kix[1:11]"  1 0.81701815128326416 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[1:11]"  0 -0.57661199569702148 0 0 0 0 0 0 0 0 
		0;
	setAttr -s 12 ".kox[1:11]"  1 0.81701815128326416 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[1:11]"  0 -0.57661199569702148 0 0 0 0 0 0 0 0 
		0;
createNode animCurveTA -n "char_FKExtraR_Thumb6_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 10 ".ktv[0:9]"  0 1 9 1 14 1 22 1 27 1 30 1 34 1 38 1 44 
		1 53 1;
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
	setAttr -s 10 ".ktv[0:9]"  0 1 9 1 14 1 22 1 27 1 30 1 34 1 38 1 44 
		1 53 1;
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
	setAttr -s 10 ".ktv[0:9]"  0 1 9 1 14 1 22 1 27 1 30 1 34 1 38 1 44 
		1 53 1;
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
		14 13.112658761378608 22 76.718153443502999 27 76.718153443502999 30 76.718153443502999 
		34 76.718153443502999 38 76.718153443502999 41 37.358107391796061 44 13.266100783563001 
		48 20.395798471309988 53 36.340151082658281;
	setAttr -s 12 ".kit[0:11]"  3 1 10 3 1 1 1 1 
		10 3 10 1;
	setAttr -s 12 ".kot[0:11]"  3 1 10 3 1 1 1 1 
		10 3 10 1;
	setAttr -s 12 ".kix[1:11]"  1 0.3290906548500061 1 1 1 1 1 0.17772065103054047 
		1 0.59739863872528076 1;
	setAttr -s 12 ".kiy[1:11]"  0 0.94429832696914673 0 0 0 0 0 -0.984080970287323 
		0 0.80194437503814697 0;
	setAttr -s 12 ".kox[1:11]"  1 0.3290906548500061 1 1 1 1 1 0.17772065103054047 
		1 0.59739863872528076 1;
	setAttr -s 12 ".koy[1:11]"  0 0.94429832696914673 0 0 0 0 0 -0.984080970287323 
		0 0.80194437503814697 0;
createNode animCurveTA -n "char_FKCurveR_Middle5_R_rotateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 9 1.3209593890539704 14 -1.2134996039568966 
		22 0 27 0 30 0 34 0 38 0 41 -12.710281456073488 44 0 53 0;
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
	setAttr -s 11 ".ktv[0:10]"  0 0 9 -7.9160682837850107 14 -1.6902884050238509 
		22 0 27 0 30 0 34 0 38 0 41 2.5030879603960932 44 0 53 0;
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 10 ".ktv[0:9]"  0 1 9 1 14 1 22 1 27 1 30 1 34 1 38 1 44 
		1 53 1;
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
	setAttr -s 10 ".ktv[0:9]"  0 1 9 1 14 1 22 1 27 1 30 1 34 1 38 1 44 
		1 53 1;
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
	setAttr -s 10 ".ktv[0:9]"  0 1 9 1 14 1 22 1 27 1 30 1 34 1 38 1 44 
		1 53 1;
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
		14 -28.044800860589348 22 25.092322839093878 27 25.092322839093878 30 25.092322839093878 
		34 25.092322839093878 38 25.092322839093878 41 -5.2291364146466472 44 2.0182725399985912 
		48 9.147970227745585 51 33.519001775952816 53 25.092322839093878;
	setAttr -s 13 ".kit[0:12]"  3 1 10 3 1 1 1 1 
		10 3 10 10 1;
	setAttr -s 13 ".kot[0:12]"  3 1 10 3 1 1 1 1 
		10 3 10 10 1;
	setAttr -s 13 ".kix[1:12]"  1 0.6267966628074646 1 1 1 1 1 0.44479402899742126 
		1 0.39067542552947998 0.51381045579910278 1;
	setAttr -s 13 ".kiy[1:12]"  0 0.77918285131454468 0 0 0 0 0 -0.89563292264938354 
		0 0.92052853107452393 0.85790371894836426 0;
	setAttr -s 13 ".kox[1:12]"  1 0.6267966628074646 1 1 1 1 1 0.44479402899742126 
		1 0.39067542552947998 0.51381045579910278 1;
	setAttr -s 13 ".koy[1:12]"  0 0.77918285131454468 0 0 0 0 0 -0.89563292264938354 
		0 0.92052853107452393 0.85790371894836426 0;
createNode animCurveTA -n "char_FKCurveR_Middle6_R_rotateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 9 1.3209593890539713 14 -1.2134996039568995 
		22 0 27 0 30 0 34 0 38 0 41 -2.5417326028243892 44 0 53 0;
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
	setAttr -s 11 ".ktv[0:10]"  0 0 9 -7.9160682837850196 14 -1.6902884050238522 
		22 0 27 0 30 0 34 0 38 0 41 -6.7814653375193545 44 0 53 0;
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 8 ".ktv[0:7]"  0 1 18 1 22 1 27 1 30 1 34 1 38 1 53 1;
	setAttr -s 8 ".kit[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kot[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 18 1 22 1 27 1 30 1 34 1 38 1 53 1;
	setAttr -s 8 ".kit[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kot[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 18 1 22 1 27 1 30 1 34 1 38 1 53 1;
	setAttr -s 8 ".kit[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kot[1:7]"  10 3 10 3 3 3 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 5.3442930176413892 9 1.1834294154979113 
		18 -23.990652364167644 22 -40.575596163297973 27 -29.96475973812646 30 -29.701436801912507 
		34 -29.337588908370989 38 -29.337588908370989 41 -26.923879644852587 44 -24.158318170345513 
		48 2.3824161550094165 53 5.3442930176413892;
	setAttr -s 12 ".kit[0:11]"  3 10 10 3 10 3 3 3 
		10 10 10 1;
	setAttr -s 12 ".kot[0:11]"  3 10 10 3 10 3 3 3 
		10 10 10 1;
	setAttr -s 12 ".kix[11]"  1;
	setAttr -s 12 ".kiy[11]"  0;
	setAttr -s 12 ".kox[11]"  1;
	setAttr -s 12 ".koy[11]"  0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 30.381278874765098 9 35.580391628559099 
		18 37.065137543984527 22 13.365829216009248 27 37.421139298934499 30 42.364576427924604 
		34 42.77983797373696 38 42.77983797373696 41 57.137905116097073 44 60.357111882398527 
		48 30.05363055852952 53 30.381278874765098;
	setAttr -s 12 ".kit[0:11]"  3 10 10 3 10 3 3 3 
		10 10 10 1;
	setAttr -s 12 ".kot[0:11]"  3 10 10 3 10 3 3 3 
		10 10 10 1;
	setAttr -s 12 ".kix[11]"  1;
	setAttr -s 12 ".kiy[11]"  0;
	setAttr -s 12 ".kox[11]"  1;
	setAttr -s 12 ".koy[11]"  0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 11.798366512855891 9 8.2443782739708418 
		18 -13.528635936987 22 11.665536170892903 27 1.7028036027972324 30 4.5477013810728453 
		34 4.2873898923470248 38 4.2873898923470248 41 -7.08566511429414 44 16.295256917318671 
		48 -9.6578299110799382 53 11.798366512855891;
	setAttr -s 12 ".kit[0:11]"  3 10 10 3 10 3 3 3 
		10 10 10 1;
	setAttr -s 12 ".kot[0:11]"  3 10 10 3 10 3 3 3 
		10 10 10 1;
	setAttr -s 12 ".kix[11]"  1;
	setAttr -s 12 ".kiy[11]"  0;
	setAttr -s 12 ".kox[11]"  1;
	setAttr -s 12 ".koy[11]"  0;
createNode animCurveTA -n "char_FKExtraR_Wrist1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 0 9 0 22 0 27 0 30 0 34 0 38 0 47 0 53 
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
	setAttr -s 9 ".ktv[0:8]"  0 1 9 1 22 1 27 1 30 1 34 1 38 1 47 1 53 
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
	setAttr ".o" 45;
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
connectAttr "maugli_attack2Source.cl" "clipLibrary1.sc[0]";
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
// End of maugli_attack2.ma
