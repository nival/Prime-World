//Maya ASCII 2008 scene
//Name: maugli_idle.ma
//Last modified: Wed, Feb 04, 2009 01:08:06 PM
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
createNode animClip -n "maugli_idleSource";
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
	setAttr ".se" 128;
	setAttr ".ci" no;
createNode animCurveTU -n "char_AimCurveEye_Right1_M_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 19 ".ktv[0:18]"  0 10 3 10 12 10 21 10 23 10 26 10 28 10 
		35 10 51 10 63 10 73 10 76 10 85 10 87 10 91 10 96 10 101 10 105 10 128 10;
	setAttr -s 19 ".kit[2:18]"  3 3 3 1 10 1 1 10 
		1 1 1 10 10 10 10 3 3;
	setAttr -s 19 ".kot[2:18]"  3 3 3 1 10 1 1 10 
		1 1 1 10 10 10 10 3 3;
	setAttr -s 19 ".kix[5:18]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 19 ".kiy[5:18]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 19 ".kox[5:18]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 19 ".koy[5:18]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_AimCurveEye_Right1_M_cross";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 19 ".ktv[0:18]"  0 1 3 1 12 1 21 1 23 1 26 1 28 1 35 1 51 
		1 63 1 73 1 76 1 85 1 87 1 91 1 96 1 101 1 105 1 128 1;
	setAttr -s 19 ".kit[2:18]"  3 3 3 1 10 1 1 10 
		1 1 1 10 10 10 10 3 3;
	setAttr -s 19 ".kot[2:18]"  3 3 3 1 10 1 1 10 
		1 1 1 10 10 10 10 3 3;
	setAttr -s 19 ".kix[5:18]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 19 ".kiy[5:18]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 19 ".kox[5:18]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 19 ".koy[5:18]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_AimCurveEye_Right1_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 19 ".ktv[0:18]"  0 0 3 2.2204460492503128e-016 12 2.2204460492503131e-016 
		21 0 23 0 26 0 28 0 35 0 51 0 63 0 73 0 76 0 85 0 87 0 91 0 96 0 101 2.4651903288156619e-032 
		105 0 128 0;
	setAttr -s 19 ".kit[2:18]"  3 3 3 1 10 1 1 10 
		1 1 1 10 10 10 10 3 3;
	setAttr -s 19 ".kot[2:18]"  3 3 3 1 10 1 1 10 
		1 1 1 10 10 10 10 3 3;
	setAttr -s 19 ".kix[5:18]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 19 ".kiy[5:18]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 19 ".kox[5:18]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 19 ".koy[5:18]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_AimCurveEye_Right1_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 20 ".ktv[0:19]"  0 0 3 0 12 -2.2204460492503131e-016 21 
		0 23 0 26 0 28 0 35 0 51 0 54 0.11391797024566487 63 0 73 0 76 0 85 0 87 0 91 0 96 
		0 101 -0.031046536242574155 105 0 128 0;
	setAttr -s 20 ".kit[2:19]"  3 3 3 1 10 1 1 10 
		10 1 1 1 10 10 10 10 3 3;
	setAttr -s 20 ".kot[2:19]"  3 3 3 1 10 1 1 10 
		10 1 1 1 10 10 10 10 3 3;
	setAttr -s 20 ".kix[5:19]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 20 ".kiy[5:19]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 20 ".kox[5:19]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 20 ".koy[5:19]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_AimCurveEye_Right1_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 0 3 -0.40196389765808171 12 -0.30218848699576373 
		21 -0.30218848699576373 23 0.3897701002937472 26 0.3897701002937472 28 -0.2063889396095315 
		35 0 51 0 54 0.48903335828222516 61 0.23871189925648853 63 0.2198394697605752 73 
		0.2198394697605752 76 -0.29672609930867999 85 -0.29672609930867999 87 0 91 0 96 -0.2286288456435154 
		101 -0.33065512893696691 105 0 128 0;
	setAttr -s 21 ".kit[2:20]"  3 3 3 1 10 1 1 10 
		10 10 1 1 1 10 10 10 10 3 3;
	setAttr -s 21 ".kot[2:20]"  3 3 3 1 10 1 1 10 
		10 10 1 1 1 10 10 10 10 3 3;
	setAttr -s 21 ".kix[5:20]"  1 0.60993653535842896 1 1 0.81302142143249512 
		1 1 1 1 1 1 1 0.70995306968688965 0.79535830020904541 1 1;
	setAttr -s 21 ".kiy[5:20]"  0 -0.79245024919509888 0 0 0.58223378658294678 
		0 0 0 0 0 0 0 -0.70424902439117432 0.60613960027694702 0 0;
	setAttr -s 21 ".kox[5:20]"  1 0.60993653535842896 1 1 0.81302142143249512 
		1 1 1 1 1 1 1 0.70995306968688965 0.79535830020904541 1 1;
	setAttr -s 21 ".koy[5:20]"  0 -0.79245024919509888 0 0 0.58223378658294678 
		0 0 0 0 0 0 0 -0.70424902439117432 0.60613960027694702 0 0;
createNode animCurveTU -n "char_FKIKControlCurveArm_L_IKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[0:9]"  9 9 9 1 1 9 9 9 
		3 3;
	setAttr -s 10 ".kot[8:9]"  3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveArm_L_FKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[0:9]"  9 9 9 1 1 9 9 9 
		3 3;
	setAttr -s 10 ".kot[8:9]"  3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveArm_L_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveLeg_L_IKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[0:9]"  9 9 9 1 1 9 9 9 
		3 3;
	setAttr -s 10 ".kot[8:9]"  3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveLeg_L_FKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[0:9]"  9 9 9 1 1 9 9 9 
		3 3;
	setAttr -s 10 ".kot[8:9]"  3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveLeg_L_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 10 12 10 25 10 35 10 51 10 63 10 67 10 
		87 10 105 10 128 10;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveArm_R_IKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[0:9]"  9 9 9 1 1 9 9 9 
		3 3;
	setAttr -s 10 ".kot[8:9]"  3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveArm_R_FKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[0:9]"  9 9 9 1 1 9 9 9 
		3 3;
	setAttr -s 10 ".kot[8:9]"  3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveArm_R_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveLeg_R_IKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[0:9]"  9 9 9 1 1 9 9 9 
		3 3;
	setAttr -s 10 ".kot[8:9]"  3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveLeg_R_FKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[0:9]"  9 9 9 1 1 9 9 9 
		3 3;
	setAttr -s 10 ".kot[8:9]"  3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveLeg_R_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 10 12 10 25 10 35 10 51 10 63 10 67 10 
		87 10 105 10 128 10;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKPoleVectorCurveArm_L_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveArm_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveArm_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveArm_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraArm_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraArm_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraArm_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveArm_L_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveArm_L_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveArm_L_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveArm_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveArm_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveArm_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveArm_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveArm_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveArm_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraArm_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraArm_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraArm_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraArm_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraArm_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraArm_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKPoleVectorCurveLeg_L_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 10 12 10 25 10 35 10 51 10 63 10 67 10 
		87 10 105 10 128 10;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 -0.22324901799022062 
		67 -0.22324901799022062 87 -0.22324901799022062 105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 -0.047273369387632692 
		67 -0.047273369387632692 87 -0.047273369387632692 105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0.19361852795627221 
		67 0.19361852795627221 87 0.19361852795627221 105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraLeg_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraLeg_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraLeg_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveLeg_L_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveLeg_L_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveLeg_L_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveLeg_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveLeg_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 43.567069197048298 12 43.567069197048298 
		25 43.567069197048298 35 43.567069197048298 51 43.567069197048298 63 43.567069197048298 
		67 43.567069197048298 87 43.567069197048298 105 43.567069197048298 128 43.567069197048298;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveLeg_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveLeg_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.28844199405395621 12 -0.28844199405395621 
		25 -0.28844199405395621 35 -0.28844199405395621 51 -0.28844199405395621 63 -0.28844199405395621 
		67 -0.28844199405395621 87 -0.28844199405395621 105 -0.28844199405395621 128 -0.28844199405395621;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveLeg_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveLeg_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.087756482507145378 12 0.087756482507145378 
		25 0.087756482507145378 35 0.087756482507145378 51 0.087756482507145378 63 0.087756482507145378 
		67 0.087756482507145378 87 0.087756482507145378 105 0.087756482507145378 128 0.087756482507145378;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraLeg_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraLeg_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraLeg_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraLeg_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraLeg_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraLeg_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKPoleVectorCurveArm_R_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveArm_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveArm_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveArm_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraArm_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraArm_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraArm_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveArm_R_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveArm_R_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveArm_R_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveArm_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveArm_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveArm_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveArm_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveArm_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveArm_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraArm_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraArm_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraArm_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraArm_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraArm_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraArm_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKPoleVectorCurveLeg_R_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 10 12 10 25 10 51 10 63 10 67 10 87 10 
		105 10 128 10;
	setAttr -s 9 ".kit[3:8]"  1 10 10 10 3 3;
	setAttr -s 9 ".kot[3:8]"  1 10 10 10 3 3;
	setAttr -s 9 ".kix[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  0 0 0 0 0 0;
	setAttr -s 9 ".kox[3:8]"  1 1 1 1 1 1;
	setAttr -s 9 ".koy[3:8]"  0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 -0.0067164203273751468 25 -0.0067164203273751468 
		37 -0.0075351902415852767 51 -0.0075351902415852767 63 0.0066512907076949372 67 0.0066512907076949372 
		87 0.0066512907076949372 105 0 128 0;
	setAttr -s 10 ".kit[4:9]"  1 10 10 10 3 3;
	setAttr -s 10 ".kot[4:9]"  1 10 10 10 3 3;
	setAttr -s 10 ".kix[4:9]"  1 1 1 1 1 1;
	setAttr -s 10 ".kiy[4:9]"  0 0 0 0 0 0;
	setAttr -s 10 ".kox[4:9]"  1 1 1 1 1 1;
	setAttr -s 10 ".koy[4:9]"  0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 -0.061089505066237927 25 -0.061089505066237927 
		37 -0.068536663877661025 51 -0.068536663877661025 63 0.060497115662739964 67 0.060497115662739964 
		87 0.060497115662739964 105 0 128 0;
	setAttr -s 10 ".kit[4:9]"  1 10 10 10 3 3;
	setAttr -s 10 ".kot[4:9]"  1 10 10 10 3 3;
	setAttr -s 10 ".kix[4:9]"  1 1 1 1 1 1;
	setAttr -s 10 ".kiy[4:9]"  0 0 0 0 0 0;
	setAttr -s 10 ".kox[4:9]"  1 1 1 1 1 1;
	setAttr -s 10 ".koy[4:9]"  0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 -0.51287567215622842 25 -0.51287567215622842 
		37 -0.32249451314412131 51 -0.32249451314412131 63 0.20087513172616547 67 0.20087513172616547 
		87 0.20087513172616547 105 0 128 0;
	setAttr -s 10 ".kit[4:9]"  1 10 10 10 3 3;
	setAttr -s 10 ".kot[4:9]"  1 10 10 10 3 3;
	setAttr -s 10 ".kix[4:9]"  1 1 1 1 1 1;
	setAttr -s 10 ".kiy[4:9]"  0 0 0 0 0 0;
	setAttr -s 10 ".kox[4:9]"  1 1 1 1 1 1;
	setAttr -s 10 ".koy[4:9]"  0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraLeg_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraLeg_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraLeg_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveLeg_R_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveLeg_R_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveLeg_R_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveLeg_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveLeg_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveLeg_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveLeg_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.33022172654533777 12 0.33022172654533777 
		25 0.33022172654533777 35 0.33022172654533777 51 0.33022172654533777 63 0.33022172654533777 
		67 0.33022172654533777 87 0.33022172654533777 105 0.33022172654533777 128 0.33022172654533777;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveLeg_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveLeg_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.13911956167322667 12 -0.13911956167322667 
		25 -0.13911956167322667 35 -0.13911956167322667 51 -0.13911956167322667 63 -0.13911956167322667 
		67 -0.13911956167322667 87 -0.13911956167322667 105 -0.13911956167322667 128 -0.13911956167322667;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraLeg_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraLeg_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraLeg_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraLeg_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraLeg_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraLeg_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveTooth1_L_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 1 12 1 20 1 27 1 35 1 48 1 51 1 55 1 
		67 1 72 1 77 1 87 1 105 1 128 1;
	setAttr -s 14 ".kit[3:13]"  1 1 10 1 10 10 1 10 
		10 3 3;
	setAttr -s 14 ".kot[3:13]"  1 1 10 1 10 10 1 10 
		10 3 3;
	setAttr -s 14 ".kix[3:13]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[3:13]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[3:13]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[3:13]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveTooth1_L_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 1 12 1 20 1 27 1 35 1 48 1 51 1 55 1 
		67 1 72 1 77 1 87 1 105 1 128 1;
	setAttr -s 14 ".kit[3:13]"  1 1 10 1 10 10 1 10 
		10 3 3;
	setAttr -s 14 ".kot[3:13]"  1 1 10 1 10 10 1 10 
		10 3 3;
	setAttr -s 14 ".kix[3:13]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[3:13]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[3:13]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[3:13]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveTooth1_L_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 1 12 1 20 1 27 1 35 1 48 1 51 1 55 1 
		67 1 72 1 77 1 87 1 105 1 128 1;
	setAttr -s 14 ".kit[3:13]"  1 1 10 1 10 10 1 10 
		10 3 3;
	setAttr -s 14 ".kot[3:13]"  1 1 10 1 10 10 1 10 
		10 3 3;
	setAttr -s 14 ".kix[3:13]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[3:13]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[3:13]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[3:13]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveTooth1_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 20 ".ktv[0:19]"  0 -27.541549434058677 7 -9.0939962813461506 
		12 0 20 -16.497982660374589 27 -9.5861738357788404 30 -19.044634575786297 35 -9.508234620559417 
		43 -22.106496278933616 48 -23.372763725013478 51 -19.759407748489217 55 -4.129307541437953 
		62 -25.730541592723835 67 -15.660313086127241 72 0 77 0 87 -1.8932346246003764 97 
		-4.3509907587425625 105 -29.660352965262227 119 -15.155862464523196 128 -27.541549434058677;
	setAttr -s 20 ".kit[4:19]"  1 10 1 10 10 1 10 10 
		10 1 10 10 10 3 10 3;
	setAttr -s 20 ".kot[4:19]"  1 10 1 10 10 1 10 10 
		10 1 10 10 10 3 10 3;
	setAttr -s 20 ".kix[4:19]"  0.62958228588104248 0.99998700618743896 
		1 1 1 1 0.96190136671066284 0.89330422878265381 0.59601199626922607 1 1 1 1 1 0.99883872270584106 
		1;
	setAttr -s 20 ".kiy[4:19]"  0.77693378925323486 0.0051010437309741974 
		0 0 0 0 -0.27339679002761841 -0.44945269823074341 0.80297553539276123 0 0 0 0 0 0.048178881406784058 
		0;
	setAttr -s 20 ".kox[4:19]"  0.62958228588104248 0.99998700618743896 
		1 1 1 1 0.96190136671066284 0.89330422878265381 0.59601199626922607 1 1 1 1 1 0.99883872270584106 
		1;
	setAttr -s 20 ".koy[4:19]"  0.77693378925323486 0.0051010437309741974 
		0 0 0 0 -0.27339679002761841 -0.44945269823074341 0.80297553539276123 0 0 0 0 0 0.048178881406784058 
		0;
createNode animCurveTA -n "char_FKCurveTooth1_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 20 ".ktv[0:19]"  0 8.4599709196312922 7 -37.702737726026029 
		12 0 20 19.083234163158291 27 8.3630891967224628 30 -29.60919906498534 35 -12.656993673411185 
		43 7.5896791187782169 48 -10.134756408675058 51 -4.5134161253784706 55 58.547022514095765 
		62 37.509057123845466 67 -29.2579070490183 72 0 77 -13.617098762807185 87 17.925579675835582 
		97 -8.4763175302064155 105 1.9085579003517894 119 4.403683760281746 128 8.4599709196312922;
	setAttr -s 20 ".kit[4:19]"  1 10 1 10 10 1 3 10 
		10 1 10 10 3 3 9 3;
	setAttr -s 20 ".kot[4:19]"  1 10 1 10 10 1 3 10 
		10 1 10 10 3 3 9 3;
	setAttr -s 20 ".kix[4:19]"  0.5737718939781189 0.58795875310897827 
		1 0.99487960338592529 0.78386318683624268 0.99487960338592529 1 0.25255268812179565 
		0.4537411630153656 1 0.84772360324859619 0.99106454849243164 1 1 0.9890601634979248 
		1;
	setAttr -s 20 ".kiy[4:19]"  -0.81901508569717407 -0.80889087915420532 
		0 0.10106753557920456 -0.62093359231948853 0.10106753557920456 0 -0.96758317947387695 
		-0.89113348722457886 0 0.53043830394744873 0.13338273763656616 0 0 0.14751234650611877 
		0;
	setAttr -s 20 ".kox[4:19]"  0.5737718939781189 0.58795875310897827 
		1 0.99487960338592529 0.78386318683624268 0.99487960338592529 1 0.25255268812179565 
		0.4537411630153656 1 0.84772360324859619 0.99106454849243164 1 1 0.9890601634979248 
		1;
	setAttr -s 20 ".koy[4:19]"  -0.81901508569717407 -0.80889087915420532 
		0 0.10106753557920456 -0.62093359231948853 0.10106753557920456 0 -0.96758317947387695 
		-0.89113348722457886 0 0.53043830394744873 0.13338273763656616 0 0 0.14751234650611877 
		0;
createNode animCurveTA -n "char_FKCurveTooth1_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 20 ".ktv[0:19]"  0 6.8137435045968227 7 2.3655968365548099 
		12 0 20 0 27 0 30 -0.78258452229674735 35 0 43 1.9385355882115467 48 1.9849400142117781 
		51 4.3413425109481114 55 -5.9144878672551897 62 -25.579026080213744 67 -26.016611307749034 
		72 0 77 0 87 0.77781150683014166 97 -1.2131529305898523 105 0.23724384904526161 119 
		4.9099265857903207 128 6.8137435045968227;
	setAttr -s 20 ".kit[4:19]"  1 10 1 10 10 1 10 10 
		10 1 10 10 10 3 9 3;
	setAttr -s 20 ".kot[4:19]"  1 10 1 10 10 1 10 10 
		10 1 10 10 10 3 9 3;
	setAttr -s 20 ".kix[4:19]"  1 1 1 1 1 1 0.57464009523391724 1 1 1 1 
		1 1 1 0.98897761106491089 1;
	setAttr -s 20 ".kiy[4:19]"  0 0 0 0 0 0 -0.81840628385543823 0 0 0 
		0 0 0 0 0.14806483685970306 0;
	setAttr -s 20 ".kox[4:19]"  1 1 1 1 1 1 0.57464009523391724 1 1 1 1 
		1 1 1 0.98897761106491089 1;
	setAttr -s 20 ".koy[4:19]"  0 0 0 0 0 0 -0.81840628385543823 0 0 0 
		0 0 0 0 0.14806483685970306 0;
createNode animCurveTL -n "char_FKCurveTooth1_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 20 ".ktv[0:19]"  0 -0.028863465787140358 7 0.09280511072592626 
		12 0 20 -0.029769545824366129 27 -0.018052672380549854 30 -0.016513806345069663 35 
		-1.6400364718384463e-005 43 -0.019407377144657185 48 -0.0036329775183042189 51 -0.019407377144657185 
		55 -0.025513026407434868 62 -0.0059196235299232205 67 0.14855407626605327 72 0 77 
		0.01100636055120615 87 -0.0047893691413634313 97 0.011259630884261476 105 -0.020362046739529252 
		119 -0.0082658633961034591 128 -0.028863465787140358;
	setAttr -s 20 ".kit[4:19]"  1 10 1 10 10 1 10 10 
		10 1 10 10 10 3 10 3;
	setAttr -s 20 ".kot[4:19]"  1 10 1 10 10 1 10 10 
		10 1 10 10 10 3 10 3;
	setAttr -s 20 ".kix[4:19]"  1 1 1 1 1 1 1 1 0.99984228610992432 1 1 
		1 1 1 1 1;
	setAttr -s 20 ".kiy[4:19]"  0 0 0 0 0 0 0 0 0.017756063491106033 0 
		0 0 0 0 0 0;
	setAttr -s 20 ".kox[4:19]"  1 1 1 1 1 1 1 1 0.99984228610992432 1 1 
		1 1 1 1 1;
	setAttr -s 20 ".koy[4:19]"  0 0 0 0 0 0 0 0 0.017756063491106033 0 
		0 0 0 0 0 0;
createNode animCurveTL -n "char_FKCurveTooth1_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 20 ".ktv[0:19]"  0 -0.023775464972591611 7 -0.036621282319434643 
		12 0 20 -0.017724413179221309 27 -0.010748334091146498 30 -0.038745688302936045 35 
		-0.022251623807143833 43 -0.025078203698768769 48 -0.028064401669467821 51 -0.025078203698768769 
		55 -0.053950673878557266 62 -0.02623716235020394 67 -0.014452972629954607 72 0 77 
		-0.014921549440768954 87 -0.017757006791607396 97 -0.018833978235473187 105 -0.019322674325854564 
		119 -0.022852329876106473 128 -0.023775464972591611;
	setAttr -s 20 ".kit[4:19]"  1 10 1 10 10 1 10 10 
		10 1 10 10 10 3 10 3;
	setAttr -s 20 ".kot[4:19]"  1 10 1 10 10 1 10 10 
		10 1 10 10 10 3 10 3;
	setAttr -s 20 ".kix[4:19]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 20 ".kiy[4:19]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 20 ".kox[4:19]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 20 ".koy[4:19]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKCurveTooth1_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 20 ".ktv[0:19]"  0 -0.052162964274260919 7 -0.094242145364446306 
		12 0 20 -0.023280488009991603 27 -0.014117616217030282 30 -0.081888486384589718 35 
		0.0088213371083157646 43 -0.030819980399576889 48 -0.038323270109271265 51 -0.030819980399576889 
		55 -0.015292022824556528 62 -0.1110658585007397 67 -0.052823840941463883 72 0 77 
		-0.022047361182320566 87 0.0096269358234385878 97 -0.017952979417691368 105 -0.041127091473362257 
		119 -0.042169197988075981 128 -0.052162964274260919;
	setAttr -s 20 ".kit[4:19]"  1 10 1 10 10 1 10 10 
		10 1 10 10 10 3 10 3;
	setAttr -s 20 ".kot[4:19]"  1 10 1 10 10 1 10 10 
		10 1 10 10 10 3 10 3;
	setAttr -s 20 ".kix[4:19]"  1 0.99632060527801514 1 1 1 1 1 0.99562680721282959 
		0.94872194528579712 1 1 1 1 1 1 1;
	setAttr -s 20 ".kiy[4:19]"  0 0.08570457249879837 0 0 0 0 0 -0.093419216573238373 
		0.31611171364784241 0 0 0 0 0 0 0;
	setAttr -s 20 ".kox[4:19]"  1 0.99632060527801514 1 1 1 1 1 0.99562680721282959 
		0.94872194528579712 1 1 1 1 1 1 1;
	setAttr -s 20 ".koy[4:19]"  0 0.08570457249879837 0 0 0 0 0 -0.093419216573238373 
		0.31611171364784241 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKExtraTooth1_L_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKExtraTooth1_L_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKExtraTooth1_L_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraTooth1_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraTooth1_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraTooth1_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKExtraTooth1_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKExtraTooth1_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKExtraTooth1_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "FKCurveR_Shoulder1_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -60.970082317325229 12 -58.430003509226957 
		25 -58.430003509226957 35 -66.586838402719948 51 -66.586838402719948 59 -56.966373388469471 
		64 -58.430003509226957 67 -58.430003509226957 87 -58.430003509226957 95 -69.005816128318074 
		105 -60.970082317325229 111 -59.815561086742832 128 -60.970082317325229;
	setAttr -s 13 ".kit[3:12]"  1 1 10 10 10 10 10 3 
		10 3;
	setAttr -s 13 ".kot[3:12]"  1 1 10 10 10 10 10 3 
		10 3;
	setAttr -s 13 ".kix[3:12]"  1 1 1 1 1 1 0.99728143215179443 1 1 1;
	setAttr -s 13 ".kiy[3:12]"  0 0 0 0 0 0 -0.073687039315700531 0 0 0;
	setAttr -s 13 ".kox[3:12]"  1 1 1 1 1 1 0.99728143215179443 1 1 1;
	setAttr -s 13 ".koy[3:12]"  0 0 0 0 0 0 -0.073687039315700531 0 0 0;
createNode animCurveTA -n "FKCurveR_Shoulder1_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -5.1174438057844904 12 9.1785525144985627 
		25 9.1785525144985627 35 14.371032396502411 51 14.371032396502411 59 7.9788660451852582 
		64 9.1785525144985627 67 9.1785525144985627 87 9.1785525144985627 95 5.098634259834161 
		105 -5.1174438057844904 111 -7.0052939751345153 128 -5.1174438057844904;
	setAttr -s 13 ".kit[3:12]"  1 1 10 10 10 10 10 3 
		10 3;
	setAttr -s 13 ".kot[3:12]"  1 1 10 10 10 10 10 3 
		10 3;
	setAttr -s 13 ".kix[3:12]"  1 1 1 1 1 1 0.92334318161010742 1 1 1;
	setAttr -s 13 ".kiy[3:12]"  0 0 0 0 0 0 -0.38397571444511414 0 0 0;
	setAttr -s 13 ".kox[3:12]"  1 1 1 1 1 1 0.92334318161010742 1 1 1;
	setAttr -s 13 ".koy[3:12]"  0 0 0 0 0 0 -0.38397571444511414 0 0 0;
createNode animCurveTA -n "FKCurveR_Shoulder1_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 -36.986337964869008 6 -51.200214343854256 
		10 -54.785334946385376 13 -53.072774030500895 25 -53.072774030500895 31 -42.744866015449063 
		37 -48.483917496528463 41 -48.48391749652847 51 -48.48391749652847 58 -29.407506147960792 
		70 -43.861977973286479 87 -43.861977973286479 105 -36.986337964869008 128 -36.986337964869008;
	setAttr -s 14 ".kit[0:13]"  1 10 10 10 10 10 1 10 
		1 10 10 10 3 3;
	setAttr -s 14 ".kot[0:13]"  1 10 10 10 10 10 1 10 
		1 10 10 10 3 3;
	setAttr -s 14 ".kix[0:13]"  0.98410087823867798 0.73155868053436279 
		1 1 1 0.98053795099258423 1 1 1 0.99198567867279053 1 1 1 1;
	setAttr -s 14 ".kiy[0:13]"  0.17761033773422241 -0.68177849054336548 
		0 0 0 0.19632980227470398 0 0 0 0.12634986639022827 0 0 0 0;
	setAttr -s 14 ".kox[0:13]"  0.98410087823867798 0.73155868053436279 
		1 1 1 0.98053795099258423 1 1 1 0.99198567867279053 1 1 1 1;
	setAttr -s 14 ".koy[0:13]"  0.17761033773422241 -0.68177849054336548 
		0 0 0 0.19632980227470398 0 0 0 0.12634986639022827 0 0 0 0;
createNode animCurveTA -n "FKCurveR_Shoulder1_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 10.660406869524985 6 -2.9384590084371243 
		10 -2.4884876879952404 13 -0.019866668306514738 25 -0.019866668306514738 31 38.921630235802589 
		37 -35.919298042256862 41 -33.213063510829478 51 -33.213063510829478 58 76.75381054621441 
		70 13.624330904229584 87 13.624330904229584 105 10.660406869524985 128 10.660406869524985;
	setAttr -s 14 ".kit[0:13]"  1 10 10 10 10 10 1 10 
		1 10 10 10 3 3;
	setAttr -s 14 ".kot[0:13]"  1 10 10 10 10 10 1 10 
		1 10 10 10 3 3;
	setAttr -s 14 ".kix[0:13]"  1 1 1 1 1 0.53809857368469238 1 1 1 0.61244869232177734 
		1 1 1 1;
	setAttr -s 14 ".kiy[0:13]"  0 0 0 0 0 -0.84288191795349121 0 0 0 0.79051035642623901 
		0 0 0 0;
	setAttr -s 14 ".kox[0:13]"  1 1 1 1 1 0.53809857368469238 1 1 1 0.61244869232177734 
		1 1 1 1;
	setAttr -s 14 ".koy[0:13]"  0 0 0 0 0 -0.84288191795349121 0 0 0 0.79051035642623901 
		0 0 0 0;
createNode animCurveTA -n "char_FKExtraPen1_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraPen1_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraPen1_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraPen1_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraPen1_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraPen1_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveHair1_L_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 12 1 25 1 35 1 51 1 68 1 73 1 87 1 
		100 1 116 1 128 1;
	setAttr -s 11 ".kit[3:10]"  1 1 10 10 1 3 10 3;
	setAttr -s 11 ".kot[3:10]"  1 1 10 10 1 3 10 3;
	setAttr -s 11 ".kix[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[3:10]"  0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[3:10]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveHair1_L_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 12 1 25 1 35 1 51 1 68 1 73 1 87 1 
		100 1 116 1 128 1;
	setAttr -s 11 ".kit[3:10]"  1 1 10 10 1 3 10 3;
	setAttr -s 11 ".kot[3:10]"  1 1 10 10 1 3 10 3;
	setAttr -s 11 ".kix[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[3:10]"  0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[3:10]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveHair1_L_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 12 1 25 1 35 1 51 1 68 1 73 1 87 1 
		100 1 116 1 128 1;
	setAttr -s 11 ".kit[3:10]"  1 1 10 10 1 3 10 3;
	setAttr -s 11 ".kot[3:10]"  1 1 10 10 1 3 10 3;
	setAttr -s 11 ".kix[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[3:10]"  0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[3:10]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveHair1_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 30.524599611915377 6 43.903962843304456 
		12 37.340252657297476 25 23.423037785070644 29 39.826232726786131 31 70.146119069954111 
		35 53.718540885692292 40 50.235181809781629 51 51.432062073962406 53 69.780438011759585 
		57 32.89542281319531 62 56.879418722372321 68 20.919134024526194 73 25.706094774547264 
		79 24.55897284297696 87 25.706094774547264 97 26.083389923325363 100 22.236742693915893 
		116 30.524599611915377 122 31.798068879694295 128 30.524599611915377;
	setAttr -s 21 ".kit[3:20]"  3 10 10 9 10 1 10 10 
		10 10 10 10 1 10 3 10 10 3;
	setAttr -s 21 ".kot[3:20]"  3 10 10 9 10 1 10 10 
		10 10 10 10 1 10 3 10 10 3;
	setAttr -s 21 ".kix[8:20]"  1 0.52582669258117676 0.79978841543197632 
		0.8687511682510376 0.55885988473892212 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".kiy[8:20]"  0 -0.85059171915054321 -0.60028201341629028 
		-0.49524897336959839 -0.82926207780838013 0 0 0 0 0 0 0 0;
	setAttr -s 21 ".kox[8:20]"  1 0.52582669258117676 0.79978841543197632 
		0.8687511682510376 0.55885988473892212 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".koy[8:20]"  0 -0.85059171915054321 -0.60028201341629028 
		-0.49524897336959839 -0.82926207780838013 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveHair1_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 -20.226445302148342 6 -44.896859715682339 
		12 10.254895306695973 25 31.172652277956846 29 4.9027283917522713 31 -9.0718535291973925 
		35 -15.210760236750266 40 -16.320517641386139 51 -14.542192519570387 53 8.4162898818360201 
		57 55.025558167378868 62 2.7203920110076267 68 -16.413727361554741 73 -9.3028816413985496 
		79 -11.243887370331544 87 -9.3028816413985496 97 -43.618930473268762 100 -49.535595778650631 
		116 -20.226445302148342 122 -16.391487999790755 128 -20.226445302148342;
	setAttr -s 21 ".kit[3:20]"  3 10 10 1 10 1 10 10 
		10 10 10 10 1 10 3 10 10 3;
	setAttr -s 21 ".kot[3:20]"  3 10 10 1 10 1 10 10 
		10 10 10 10 1 10 3 10 10 3;
	setAttr -s 21 ".kix[6:20]"  1 1 1 0.16252915561199188 0.94923985004425049 
		0.2821279764175415 0.86791485548019409 1 1 1 0.52516430616378784 1 0.78512930870056152 
		1 1;
	setAttr -s 21 ".kiy[6:20]"  0 0 0 0.98670369386672974 -0.31455335021018982 
		-0.95937681198120117 -0.49671313166618347 0 0 0 -0.85100084543228149 0 0.61933189630508423 
		0 0;
	setAttr -s 21 ".kox[6:20]"  1 1 1 0.16252915561199188 0.94923985004425049 
		0.2821279764175415 0.86791485548019409 1 1 1 0.52516430616378784 1 0.78512930870056152 
		1 1;
	setAttr -s 21 ".koy[6:20]"  0 0 0 0.98670369386672974 -0.31455335021018982 
		-0.95937681198120117 -0.49671313166618347 0 0 0 -0.85100084543228149 0 0.61933189630508423 
		0 0;
createNode animCurveTA -n "char_FKCurveHair1_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 17.701770262088139 6 5.045651104868516 
		12 -29.812242416971255 25 -40.928765009656857 29 -17.674764119262122 31 0.87296545235415424 
		35 14.40871992106957 40 24.034156459843157 51 19.140857703055083 53 21.268213056752156 
		57 -7.793160189052549 62 -16.190190813835542 68 37.553080233435224 73 24.400199249491894 
		79 30.28313695365302 87 24.400199249491894 97 21.822297061885109 100 24.583878842918715 
		116 17.701770262088139 122 17.301482326755359 128 17.701770262088139;
	setAttr -s 21 ".kit[3:20]"  3 10 10 9 10 1 10 10 
		3 3 10 10 1 10 3 10 10 3;
	setAttr -s 21 ".kot[3:20]"  3 10 10 9 10 1 10 10 
		3 3 10 10 1 10 3 10 10 3;
	setAttr -s 21 ".kix[8:20]"  1 1 0.41706162691116333 1 1 0.94501692056655884 
		1 1 1 1 1 1 1;
	setAttr -s 21 ".kiy[8:20]"  0 0 -0.9088781476020813 0 0 -0.32702156901359558 
		0 0 0 0 0 0 0;
	setAttr -s 21 ".kox[8:20]"  1 1 0.41706162691116333 1 1 0.94501692056655884 
		1 1 1 1 1 1 1;
	setAttr -s 21 ".koy[8:20]"  0 0 -0.9088781476020813 0 0 -0.32702156901359558 
		0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraHair1_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraHair1_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraHair1_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveHead1_M_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 12 1 25 1 36 1 51 1 63 1 67 1 87 1 
		108 1 119 1 128 1;
	setAttr -s 11 ".kit[3:10]"  1 1 10 10 10 3 10 3;
	setAttr -s 11 ".kot[3:10]"  1 1 10 10 10 3 10 3;
	setAttr -s 11 ".kix[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[3:10]"  0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[3:10]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveHead1_M_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 12 1 25 1 36 1 51 1 63 1 67 1 87 1 
		108 1 119 1 128 1;
	setAttr -s 11 ".kit[3:10]"  1 1 10 10 10 3 10 3;
	setAttr -s 11 ".kot[3:10]"  1 1 10 10 10 3 10 3;
	setAttr -s 11 ".kix[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[3:10]"  0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[3:10]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveHead1_M_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 12 1 25 1 36 1 51 1 63 1 67 1 87 1 
		108 1 119 1 128 1;
	setAttr -s 11 ".kit[3:10]"  1 1 10 10 10 3 10 3;
	setAttr -s 11 ".kot[3:10]"  1 1 10 10 10 3 10 3;
	setAttr -s 11 ".kix[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[3:10]"  0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[3:10]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveHead1_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 19.649599090973453 6 63.240364722892778 
		12 32.458661511805076 25 32.458661511805076 28 30.639011435974098 31 22.11758591337945 
		36 13.088631036651476 51 13.088631036651476 56 -39.455990689892815 63 -48.844202586909155 
		67 -48.844202586909155 87 -48.844202586909155 95 -15.707666412520506 108 14.505540506756699 
		119 16.434324185760175 128 19.649599090973453;
	setAttr -s 16 ".kit[0:15]"  9 10 10 10 10 10 1 1 
		10 10 10 10 10 3 10 3;
	setAttr -s 16 ".kot[0:15]"  9 10 10 10 10 10 1 1 
		10 10 10 10 10 3 10 3;
	setAttr -s 16 ".kix[6:15]"  1 1 0.34705090522766113 1 1 1 0.53491431474685669 
		1 1 1;
	setAttr -s 16 ".kiy[6:15]"  0 0 -0.93784630298614502 0 0 0 0.8449062705039978 
		0 0 0;
	setAttr -s 16 ".kox[6:15]"  1 1 0.34705090522766113 1 1 1 0.53491431474685669 
		1 1 1;
	setAttr -s 16 ".koy[6:15]"  0 0 -0.93784630298614502 0 0 0 0.8449062705039978 
		0 0 0;
createNode animCurveTA -n "char_FKCurveHead1_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 -30.214171376615486 6 -26.704089142051409 
		12 -22.461523647344926 25 -22.461523647344926 28 -21.423680656234804 31 -28.188391525015902 
		36 -21.979231046812068 51 -21.979231046812068 56 23.188667601270687 63 41.974947198246959 
		67 41.974947198246959 87 41.974947198246959 95 34.873996488897838 108 -24.50587631500208 
		119 -26.737393808845205 128 -30.214171376615486;
	setAttr -s 16 ".kit[0:15]"  3 10 10 10 10 10 1 1 
		10 10 10 10 10 3 10 3;
	setAttr -s 16 ".kot[0:15]"  3 10 10 10 10 10 1 1 
		10 10 10 10 10 3 10 3;
	setAttr -s 16 ".kix[6:15]"  1 1 0.33734825253486633 1 1 1 0.51656389236450195 
		1 1 1;
	setAttr -s 16 ".kiy[6:15]"  0 0 0.94137990474700928 0 0 0 -0.85624867677688599 
		0 0 0;
	setAttr -s 16 ".kox[6:15]"  1 1 0.33734825253486633 1 1 1 0.51656389236450195 
		1 1 1;
	setAttr -s 16 ".koy[6:15]"  0 0 0.94137990474700928 0 0 0 -0.85624867677688599 
		0 0 0;
createNode animCurveTA -n "char_FKCurveHead1_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 -39.886477028299176 6 -59.11528159030253 
		12 -34.814820921499539 25 -34.814820921499539 28 -32.535945636760054 31 -70.421209855196537 
		36 -70.544225003522087 51 -70.544225003522087 56 -71.017107826977025 63 -88.949299032836024 
		67 -88.949299032836024 87 -88.949299032836024 95 -49.073994177906201 108 -37.518179133843233 
		119 -38.352458053163573 128 -39.886477028299176;
	setAttr -s 16 ".kit[0:15]"  3 10 10 10 10 10 1 1 
		10 10 10 10 10 3 10 3;
	setAttr -s 16 ".kot[0:15]"  3 10 10 10 10 10 1 1 
		10 10 10 10 10 3 10 3;
	setAttr -s 16 ".kix[6:15]"  1 1 1 1 1 1 0.6149437427520752 1 1 1;
	setAttr -s 16 ".kiy[6:15]"  0 0 0 0 0 0 0.78857100009918213 0 0 0;
	setAttr -s 16 ".kox[6:15]"  1 1 1 1 1 1 0.6149437427520752 1 1 1;
	setAttr -s 16 ".koy[6:15]"  0 0 0 0 0 0 0.78857100009918213 0 0 0;
createNode animCurveTA -n "char_FKExtraHead1_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraHead1_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraHead1_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveNeck1_M_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 36 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveNeck1_M_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 36 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveNeck1_M_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 36 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveNeck1_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 16.978679829010165 6 16.848048280712888 
		12 22.756523070602093 25 22.756523070602093 31 3.8589270115130834 36 2.155780658729106 
		51 2.155780658729106 56 2.1325766045740564 63 14.741487826426862 67 14.741487826426862 
		87 14.741487826426862 95 35.322224810995237 105 16.978679829010165 128 16.978679829010165;
	setAttr -s 14 ".kit[0:13]"  3 10 10 10 10 1 1 10 
		10 10 10 10 3 3;
	setAttr -s 14 ".kot[0:13]"  3 10 10 10 10 1 1 10 
		10 10 10 10 3 3;
	setAttr -s 14 ".kix[5:13]"  1 1 1 1 1 1 0.99788922071456909 1 1;
	setAttr -s 14 ".kiy[5:13]"  0 0 0 0 0 0 0.064939923584461212 0 0;
	setAttr -s 14 ".kox[5:13]"  1 1 1 1 1 1 0.99788922071456909 1 1;
	setAttr -s 14 ".koy[5:13]"  0 0 0 0 0 0 0.064939923584461212 0 0;
createNode animCurveTA -n "char_FKCurveNeck1_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 -13.679820867901928 6 -1.0006887523474299 
		12 -10.808482412036181 25 -10.808482412036181 31 4.1063697217011796 36 -1.003126549884328 
		51 -1.003126549884328 56 26.907873389568461 63 7.5056122349411813 67 7.5056122349411813 
		87 7.5056122349411813 95 3.8126335123063066 105 -13.679820867901928 128 -13.679820867901928;
	setAttr -s 14 ".kit[0:13]"  3 10 10 10 10 1 1 10 
		10 10 10 10 3 3;
	setAttr -s 14 ".kot[0:13]"  3 10 10 10 10 1 1 10 
		10 10 10 10 3 3;
	setAttr -s 14 ".kix[5:13]"  1 1 0.93747562170028687 1 1 1 0.85132575035095215 
		1 1;
	setAttr -s 14 ".kiy[5:13]"  0 0 0.34805086255073547 0 0 0 -0.52463746070861816 
		0 0;
	setAttr -s 14 ".kox[5:13]"  1 1 0.93747562170028687 1 1 1 0.85132575035095215 
		1 1;
	setAttr -s 14 ".koy[5:13]"  0 0 0.34805086255073547 0 0 0 -0.52463746070861816 
		0 0;
createNode animCurveTA -n "char_FKCurveNeck1_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 -6.4072944111053358 6 -14.788112769971811 
		12 -23.868922039275827 25 -23.868922039275827 31 8.5715326652959778 36 13.460911068892379 
		51 13.460911068892379 56 -31.902834425920911 63 -32.389357024431213 67 -32.389357024431213 
		87 -32.389357024431213 95 -19.273678765261838 105 -6.4072944111053358 128 -6.4072944111053358;
	setAttr -s 14 ".kit[0:13]"  3 10 10 10 10 1 1 10 
		10 10 10 10 3 3;
	setAttr -s 14 ".kot[0:13]"  3 10 10 10 10 1 1 10 
		10 10 10 10 3 3;
	setAttr -s 14 ".kix[5:13]"  1 1 1 1 1 1 0.79777824878692627 1 1;
	setAttr -s 14 ".kiy[5:13]"  0 0 0 0 0 0 0.60295099020004272 0 0;
	setAttr -s 14 ".kox[5:13]"  1 1 1 1 1 1 0.79777824878692627 1 1;
	setAttr -s 14 ".koy[5:13]"  0 0 0 0 0 0 0.60295099020004272 0 0;
createNode animCurveTA -n "char_FKExtraNeck1_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraNeck1_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraNeck1_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveSpine3_M_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 1 12 1 19 1 25 1 35 1 51 1 63 1 67 1 
		77 1 87 1 107 1 128 1;
	setAttr -s 12 ".kit[0:11]"  1 10 10 10 1 1 10 10 
		10 10 3 3;
	setAttr -s 12 ".kot[0:11]"  1 10 10 10 1 1 10 10 
		10 10 3 3;
	setAttr -s 12 ".kix[0:11]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[0:11]"  0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[0:11]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[0:11]"  0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveSpine3_M_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 1 12 1 19 1 25 1 35 1 51 1 63 1 67 1 
		77 1 87 1 107 1 128 1;
	setAttr -s 12 ".kit[0:11]"  1 10 10 10 1 1 10 10 
		10 10 3 3;
	setAttr -s 12 ".kot[0:11]"  1 10 10 10 1 1 10 10 
		10 10 3 3;
	setAttr -s 12 ".kix[0:11]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[0:11]"  0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[0:11]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[0:11]"  0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveSpine3_M_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 1 12 1 19 1 25 1 35 1 51 1 63 1 67 1 
		77 1 87 1 107 1 128 1;
	setAttr -s 12 ".kit[0:11]"  1 10 10 10 1 1 10 10 
		10 10 3 3;
	setAttr -s 12 ".kot[0:11]"  1 10 10 10 1 1 10 10 
		10 10 3 3;
	setAttr -s 12 ".kix[0:11]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[0:11]"  0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[0:11]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[0:11]"  0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveSpine3_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 -4.1759924717065973 6 -5.3352702593911427 
		12 -1.7616302111028659 19 -1.3262737686351076 25 -1.7616302111028659 35 2.7516955886285288 
		51 2.7516955886285288 56 -18.100147994179167 63 -8.5321232206364641 67 -8.5321232206364641 
		77 -8.5321232206364641 87 -8.6262555475320077 95 8.925738876240187 107 -0.095752846115433374 
		117 -1.4462568950457093 128 -4.1759924717065973;
	setAttr -s 16 ".kit[0:15]"  1 10 10 10 10 1 1 10 
		10 10 10 10 10 3 10 3;
	setAttr -s 16 ".kot[0:15]"  1 10 10 10 10 1 1 10 
		10 10 10 10 10 3 10 3;
	setAttr -s 16 ".kix[0:15]"  0.9814109206199646 1 1 1 1 1 1 0.89715576171875 
		1 1 1 1 0.97595793008804321 1 1 1;
	setAttr -s 16 ".kiy[0:15]"  0.19191823899745941 0 0 0 0 0 0 -0.44171431660652161 
		0 0 0 0 0.21795882284641266 0 0 0;
	setAttr -s 16 ".kox[0:15]"  0.9814109206199646 1 1 1 1 1 1 0.89715576171875 
		1 1 1 1 0.97595793008804321 1 1 1;
	setAttr -s 16 ".koy[0:15]"  0.19191823899745941 0 0 0 0 0 0 -0.44171431660652161 
		0 0 0 0 0.21795882284641266 0 0 0;
createNode animCurveTA -n "char_FKCurveSpine3_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 -1.201 6 -19.150749107117328 12 -22.636636189422745 
		19 -21.532394775308607 25 -22.636636189422745 35 -34.401150927100204 51 -34.401150927100204 
		56 11.572069786567869 63 19.22641912091504 67 19.22641912091504 77 19.22641912091504 
		87 19.974405730785165 95 29.165578347289269 107 10.349034306159099 117 -2.4271822985642224 
		128 -1.201;
	setAttr -s 16 ".kit[0:15]"  9 10 10 10 10 1 1 10 
		10 10 10 10 10 3 10 3;
	setAttr -s 16 ".kot[0:15]"  9 10 10 10 10 1 1 10 
		10 10 10 10 10 3 10 3;
	setAttr -s 16 ".kix[5:15]"  1 1 0.39297837018966675 1 1 1 1 0.96968632936477661 
		1 1 1;
	setAttr -s 16 ".kiy[5:15]"  0 0 0.91954779624938965 0 0 0 0 -0.24435289204120636 
		0 0 0;
	setAttr -s 16 ".kox[5:15]"  1 1 0.39297837018966675 1 1 1 1 0.96968632936477661 
		1 1 1;
	setAttr -s 16 ".koy[5:15]"  0 0 0.91954779624938965 0 0 0 0 -0.24435289204120636 
		0 0 0;
createNode animCurveTA -n "char_FKCurveSpine3_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 -38.617693158088045 6 -52.44903484973117 
		12 -26.888493302649636 19 -27.164731195508907 25 -26.888493302649636 35 -46.003991014237251 
		51 -46.003991014237251 56 -40.075986495869245 63 -34.083408392165921 67 -34.083408392165921 
		77 -34.083408392165921 87 -34.443971697160151 95 -34.820564896503733 107 -40.872018509929056 
		117 -39.751634023233251 128 -38.617693158088045;
	setAttr -s 16 ".kit[0:15]"  1 10 10 10 10 1 1 10 
		10 10 10 10 10 3 10 3;
	setAttr -s 16 ".kot[0:15]"  1 10 10 10 10 1 1 10 
		10 10 10 10 10 3 10 3;
	setAttr -s 16 ".kix[0:15]"  1 0.89019221067428589 1 1 1 1 1 0.887168288230896 
		1 1 1 1 1 1 1 1;
	setAttr -s 16 ".kiy[0:15]"  0 0.45558515191078186 0 0 0 0 0 0.4614461362361908 
		0 0 0 0 0 0 0 0;
	setAttr -s 16 ".kox[0:15]"  1 0.89019221067428589 1 1 1 1 1 0.887168288230896 
		1 1 1 1 1 1 1 1;
	setAttr -s 16 ".koy[0:15]"  0 0.45558515191078186 0 0 0 0 0 0.4614461362361908 
		0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraSpine3_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraSpine3_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraSpine3_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveSpine4_L_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 12 1 19 1 25 1 35 1 51 1 63 1 67 1 
		87 1 107 1 128 1;
	setAttr -s 11 ".kit[0:10]"  1 10 10 10 1 1 10 10 
		10 3 3;
	setAttr -s 11 ".kot[0:10]"  1 10 10 10 1 1 10 10 
		10 3 3;
	setAttr -s 11 ".kix[0:10]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[0:10]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[0:10]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[0:10]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveSpine4_L_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 12 1 19 1 25 1 35 1 51 1 63 1 67 1 
		87 1 107 1 128 1;
	setAttr -s 11 ".kit[0:10]"  1 10 10 10 1 1 10 10 
		10 3 3;
	setAttr -s 11 ".kot[0:10]"  1 10 10 10 1 1 10 10 
		10 3 3;
	setAttr -s 11 ".kix[0:10]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[0:10]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[0:10]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[0:10]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveSpine4_L_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 12 1 19 1 25 1 35 1 51 1 63 1 67 1 
		87 1 107 1 128 1;
	setAttr -s 11 ".kit[0:10]"  1 10 10 10 1 1 10 10 
		10 3 3;
	setAttr -s 11 ".kot[0:10]"  1 10 10 10 1 1 10 10 
		10 3 3;
	setAttr -s 11 ".kix[0:10]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[0:10]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[0:10]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[0:10]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveSpine4_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 19.548247782583122 6 22.2777872295677 
		12 12.799677014909973 19 14.073934601352439 25 12.799677014909973 31 15.439791826164845 
		35 10.078452555958116 51 10.078452555958116 63 29.956966307755827 67 29.956966307755827 
		77 29.579167593596786 87 29.956966307755827 95 37.182424317546726 107 17.532978455689044 
		117 18.337107334038905 128 19.548247782583122;
	setAttr -s 16 ".kit[0:15]"  1 10 10 10 10 10 1 1 
		10 10 10 10 10 3 10 3;
	setAttr -s 16 ".kot[0:15]"  1 10 10 10 10 10 1 1 
		10 10 10 10 10 3 10 3;
	setAttr -s 16 ".kix[0:15]"  0.99902385473251343 1 1 1 1 1 1 1 1 1 1 
		1 0.95096158981323242 1 1 1;
	setAttr -s 16 ".kiy[0:15]"  0.044174551963806152 0 0 0 0 0 0 0 0 0 
		0 0 -0.30930912494659424 0 0 0;
	setAttr -s 16 ".kox[0:15]"  0.99902385473251343 1 1 1 1 1 1 1 1 1 1 
		1 0.95096158981323242 1 1 1;
	setAttr -s 16 ".koy[0:15]"  0.044174544513225555 0 0 0 0 0 0 0 0 0 
		0 0 -0.30930912494659424 0 0 0;
createNode animCurveTA -n "char_FKCurveSpine4_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 4.2832309672587163 6 -4.2153997397951688 
		12 18.444957714225655 19 18.378326366792834 25 18.444957714225655 31 31.709362300413016 
		35 25.047214422384894 51 25.047214422384894 63 -12.600622510469316 67 -12.600622510469316 
		77 -12.922424074584947 87 -12.600622510469316 95 -14.749099473808009 107 8.9756440143595864 
		117 7.3288465307260715 128 4.2832309672587163;
	setAttr -s 16 ".kit[0:15]"  1 10 10 10 10 10 1 1 
		10 10 10 10 10 3 10 3;
	setAttr -s 16 ".kot[0:15]"  1 10 10 10 10 10 1 1 
		10 10 10 10 10 3 10 3;
	setAttr -s 16 ".kix[0:15]"  0.97932004928588867 0.8506934642791748 
		1 1 1 0.94512051343917847 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 16 ".kiy[0:15]"  -0.20231726765632629 0.52566206455230713 
		0 0 0 0.3267219066619873 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 16 ".kox[0:15]"  0.97932004928588867 0.8506934642791748 
		1 1 1 0.94512051343917847 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 16 ".koy[0:15]"  -0.20231726765632629 0.52566206455230713 
		0 0 0 0.3267219066619873 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveSpine4_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 5.393 6 -4.2375740231503007 12 -13.280623590664682 
		19 -13.285559823924098 25 -13.280623590664682 31 -8.4111051486523039 35 -20.550312246506135 
		51 -20.550312246506135 63 9.6648721240848516 67 9.6648721240848516 77 9.4770476181040344 
		87 9.6648721240848516 95 6.0501442085608845 107 -5.2222987133320684 117 4.3251219165337647 
		128 5.393;
	setAttr -s 16 ".kit[0:15]"  1 10 10 10 10 10 1 1 
		10 10 10 10 10 3 10 3;
	setAttr -s 16 ".kot[0:15]"  1 10 10 10 10 10 1 1 
		10 10 10 10 10 3 10 3;
	setAttr -s 16 ".kix[0:15]"  0.98497766256332397 0.77524417638778687 
		1 1 1 0.93458479642868042 1 1 1 1 1 1 0.93173491954803467 1 1 1;
	setAttr -s 16 ".kiy[0:15]"  0.17268197238445282 -0.63166165351867676 
		0 0 0 -0.35574039816856384 0 0 0 0 0 0 -0.36313933134078979 0 0 0;
	setAttr -s 16 ".kox[0:15]"  0.98497766256332397 0.77524417638778687 
		1 1 1 0.93458479642868042 1 1 1 1 1 1 0.93173491954803467 1 1 1;
	setAttr -s 16 ".koy[0:15]"  0.17268197238445282 -0.63166165351867676 
		0 0 0 -0.35574039816856384 0 0 0 0 0 0 -0.36313933134078979 0 0 0;
createNode animCurveTA -n "char_FKExtraSpine4_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraSpine4_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraSpine4_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurvePelvis1_M_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurvePelvis1_M_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurvePelvis1_M_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurvePelvis1_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		95 -12.006755804537228 105 0 128 0;
	setAttr -s 11 ".kit[3:10]"  1 1 10 10 10 10 3 3;
	setAttr -s 11 ".kot[3:10]"  1 1 10 10 10 10 3 3;
	setAttr -s 11 ".kix[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[3:10]"  0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[3:10]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurvePelvis1_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		95 8.7985858488078765 105 0 128 0;
	setAttr -s 11 ".kit[3:10]"  1 1 10 10 10 10 3 3;
	setAttr -s 11 ".kot[3:10]"  1 1 10 10 10 10 3 3;
	setAttr -s 11 ".kix[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[3:10]"  0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[3:10]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurvePelvis1_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -0.83191351642244571 12 -0.83191351642244571 
		25 -0.83191351642244571 35 -0.83191351642244571 51 -0.83191351642244571 63 -0.83191351642244571 
		67 -0.83191351642244571 87 -0.83191351642244571 95 -1.7467971108020806 105 -0.83191351642244571 
		128 -0.83191351642244571;
	setAttr -s 11 ".kit[3:10]"  1 1 10 10 10 10 3 3;
	setAttr -s 11 ".kot[3:10]"  1 1 10 10 10 10 3 3;
	setAttr -s 11 ".kix[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[3:10]"  0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[3:10]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraPelvis1_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraPelvis1_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraPelvis1_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_RootCurveRoot1_M_CenterBtwFeet";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 12 0 25 0 37 0 44 0 51 0 67 0 87 0 
		99 0 108 0 128 0;
	setAttr -s 11 ".kit[0:10]"  1 10 10 1 10 1 10 3 
		10 10 3;
	setAttr -s 11 ".kot[0:10]"  1 10 10 1 10 1 10 3 
		10 10 3;
	setAttr -s 11 ".kix[0:10]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[0:10]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[0:10]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[0:10]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_RootCurveRoot1_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 3.0405827598215973 12 -1.8226570952003962 
		19 -1.4841055570362263 25 -1.8226570952003962 37 -1.8226570952003962 44 -1.8226570952003962 
		51 -1.8226570952003962 67 3.58822151995144 77 4.1215473840584975 87 3.58822151995144 
		95 12.367477686795411 99 9.0406034083972742 108 2.8989728244888675 119 3.2442361687317924 
		128 3.0405827598215973;
	setAttr -s 15 ".kit[0:14]"  1 10 10 10 1 10 1 10 
		10 3 10 10 10 10 3;
	setAttr -s 15 ".kot[0:14]"  1 10 10 10 1 10 1 10 
		10 3 10 10 10 10 3;
	setAttr -s 15 ".kix[0:14]"  0.99586021900177002 1 1 1 1 1 1 1 1 1 0.97284781932830811 
		0.93436050415039063 1 1 1;
	setAttr -s 15 ".kiy[0:14]"  -0.090898633003234863 0 0 0 0 0 0 0 0 0 
		0.23144549131393433 -0.35632911324501038 0 0 0;
	setAttr -s 15 ".kox[0:14]"  0.99586021900177002 1 1 1 1 1 1 1 1 1 0.97284781932830811 
		0.93436050415039063 1 1 1;
	setAttr -s 15 ".koy[0:14]"  -0.090898625552654266 0 0 0 0 0 0 0 0 0 
		0.23144549131393433 -0.35632911324501038 0 0 0;
createNode animCurveTA -n "char_RootCurveRoot1_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 23.714440424736864 12 -4.5381767366842212 
		19 -5.2532591922466532 25 -4.5381767366842212 37 -4.5381767366842212 44 -4.5381767366842212 
		51 -4.5381767366842212 67 38.179956986177139 77 38.910285869317256 87 38.179956986177139 
		95 22.159623662965121 99 22.70691852254393 108 16.21022710023799 119 22.075919244946782 
		128 23.714440424736864;
	setAttr -s 15 ".kit[0:14]"  3 10 10 10 1 10 1 10 
		10 3 10 10 10 9 3;
	setAttr -s 15 ".kot[0:14]"  3 10 10 10 1 10 1 10 
		10 3 10 10 10 9 3;
	setAttr -s 15 ".kix[4:14]"  1 1 1 1 1 1 1 1 0.99986362457275391 0.9812430739402771 
		1;
	setAttr -s 15 ".kiy[4:14]"  0 0 0 0 0 0 0 0 -0.016517268493771553 0.19277477264404297 
		0;
	setAttr -s 15 ".kox[4:14]"  1 1 1 1 1 1 1 1 0.99986362457275391 0.9812430739402771 
		1;
	setAttr -s 15 ".koy[4:14]"  0 0 0 0 0 0 0 0 -0.016517268493771553 0.19277477264404297 
		0;
createNode animCurveTA -n "char_RootCurveRoot1_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 8.6470827930312559 12 6.2382213084437721 
		19 4.6238855999052184 25 6.2382213084437721 37 6.2382213084437721 44 6.2382213084437721 
		51 6.2382213084437721 56 26.572137082947471 67 7.9206322365867692 77 9.2372747221989577 
		87 7.9206322365867692 95 11.778101534952739 99 10.734100279210983 108 8.2331844452326681 
		119 8.5576896193082224 128 8.6470827930312559;
	setAttr -s 16 ".kit[0:15]"  9 10 10 10 1 10 1 10 
		10 10 3 10 9 10 10 3;
	setAttr -s 16 ".kot[0:15]"  9 10 10 10 1 10 1 10 
		10 10 3 10 9 10 10 3;
	setAttr -s 16 ".kix[4:15]"  1 1 1 0.99848783016204834 1 1 1 1 0.9899604320526123 
		1 1 1;
	setAttr -s 16 ".kiy[4:15]"  0 0 0 0.054973520338535309 0 0 0 0 -0.14134465157985687 
		0 0 0;
	setAttr -s 16 ".kox[4:15]"  1 1 1 0.99848783016204834 1 1 1 1 0.9899604320526123 
		1 1 1;
	setAttr -s 16 ".koy[4:15]"  0 0 0 0.054973520338535309 0 0 0 0 -0.14134465157985687 
		0 0 0;
createNode animCurveTL -n "char_RootCurveRoot1_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 -0.11500744677504726 12 -0.0022598665398585183 
		25 -0.0022598665398585183 37 -0.0032349667107483956 44 -0.0066527636473104213 51 
		-0.0022598665398585183 56 -0.18792026042843821 67 -0.088631701841795613 87 -0.088631701841795613 
		95 -0.056867828601230144 99 -0.030749820043135936 108 -0.094574880193149247 119 -0.098209123843059687 
		128 -0.11500744677504726;
	setAttr -s 14 ".kit[0:13]"  1 10 10 1 10 1 10 10 
		3 10 10 10 1 3;
	setAttr -s 14 ".kot[0:13]"  1 10 10 1 10 1 10 10 
		3 10 10 10 1 3;
	setAttr -s 14 ".kix[0:13]"  1 1 1 1 1 1 0.98713892698287964 1 1 1 1 
		1 0.9998205304145813 1;
	setAttr -s 14 ".kiy[0:13]"  0 0 0 0 0 0 -0.1598643958568573 0 0 0 0 
		0 -0.018946601077914238 0;
	setAttr -s 14 ".kox[0:13]"  1 1 1 1 1 1 0.98713892698287964 1 1 1 1 
		1 0.9998205304145813 1;
	setAttr -s 14 ".koy[0:13]"  0 0 0 0 0 0 -0.1598643958568573 0 0 0 0 
		0 -0.018946601077914238 0;
createNode animCurveTL -n "char_RootCurveRoot1_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -0.26403992941414445 6 -0.36895929462321142 
		12 -0.26403992941414445 25 -0.26403992941414445 31 -0.38654577798684964 37 -0.2952297582043848 
		44 -0.29386017935425202 51 -0.29562050013423002 67 -0.26403992941414467 87 -0.26403992941414467 
		99 -0.2640399294141445 108 -0.26403992941414445 128 -0.26403992941414445;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 10 1 10 1 
		10 3 10 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 10 1 10 1 
		10 3 10 10 3;
	setAttr -s 13 ".kix[5:12]"  1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[5:12]"  0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[5:12]"  1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[5:12]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_RootCurveRoot1_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 -0.0438000161016944 12 -0.0438000161016944 
		25 -0.0438000161016944 31 0.028410979774149747 37 -0.21325524097632476 44 -0.23349386541013642 
		51 -0.2378365426700772 56 0.048094148551418817 63 -0.091797813997056929 67 -0.11628355696460105 
		87 -0.11628355696460105 95 -0.11144655417278163 99 -0.087635000641277133 112 0.039627829593276098 
		128 -0.0438000161016944;
	setAttr -s 15 ".kit[0:14]"  9 10 10 10 1 1 1 10 
		10 10 3 10 10 3 3;
	setAttr -s 15 ".kot[0:14]"  9 10 10 10 1 1 1 10 
		10 10 3 10 10 3 3;
	setAttr -s 15 ".kix[4:14]"  0.99539452791213989 0.99953639507293701 
		1 0.93935203552246094 1 1 1 1 1 1 1;
	setAttr -s 15 ".kiy[4:14]"  -0.095862783491611481 -0.030447518453001976 
		0 0.34295457601547241 0 0 0 0 0 0 0;
	setAttr -s 15 ".kox[4:14]"  0.99539458751678467 0.99953639507293701 
		1 0.93935203552246094 1 1 1 1 1 1 1;
	setAttr -s 15 ".koy[4:14]"  -0.095862790942192078 -0.030447518453001976 
		0 0.34295457601547241 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_RootExtraRoot1_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_RootExtraRoot1_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_RootExtraRoot1_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_RootExtraRoot1_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_RootExtraRoot1_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_RootExtraRoot1_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Clavicle1_L_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Clavicle1_L_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Clavicle1_L_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 -39.049273644778822 25 -39.049273644778822 
		35 -40.869416340091959 51 -40.869416340091959 63 -39.049273644778822 67 -39.049273644778822 
		87 -39.049273644778822 105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 19.482539041175365 25 19.482539041175365 
		35 4.9707334210844127 51 4.9707334210844127 63 19.482539041175365 67 19.482539041175365 
		87 19.482539041175365 105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 -25.82137584186977 25 -25.82137584186977 
		35 -8.644201228691168 51 -8.644201228691168 63 -25.82137584186977 67 -25.82137584186977 
		87 -25.82137584186977 105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 2.1942103669999999e-008 12 2.1942103669999999e-008 
		25 2.1942103669999999e-008 35 2.1942103669999999e-008 51 2.1942103669999999e-008 
		63 2.1942103669999999e-008 67 2.1942103669999999e-008 87 2.1942103669999999e-008 
		105 2.1942103669999999e-008 128 2.1942103669999999e-008;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_L_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 12 1 25 1 35 1 51 1 59 1 64 1 67 1 
		87 1 105 1 128 1;
	setAttr -s 11 ".kit[3:10]"  1 1 10 10 10 10 3 3;
	setAttr -s 11 ".kot[3:10]"  1 1 10 10 10 10 3 3;
	setAttr -s 11 ".kix[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[3:10]"  0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[3:10]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_L_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 12 1 25 1 35 1 51 1 59 1 64 1 67 1 
		87 1 105 1 128 1;
	setAttr -s 11 ".kit[3:10]"  1 1 10 10 10 10 3 3;
	setAttr -s 11 ".kot[3:10]"  1 1 10 10 10 10 3 3;
	setAttr -s 11 ".kix[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[3:10]"  0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[3:10]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_L_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 12 1 25 1 35 1 51 1 59 1 64 1 67 1 
		87 1 105 1 128 1;
	setAttr -s 11 ".kit[3:10]"  1 1 10 10 10 10 3 3;
	setAttr -s 11 ".kot[3:10]"  1 1 10 10 10 10 3 3;
	setAttr -s 11 ".kix[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[3:10]"  0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[3:10]"  1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[3:10]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Shoulder1_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -0.68127875452050601 12 0.87373607824652832 
		25 0.87373607824652832 35 -11.392050243707255 51 -11.392050243707255 59 11.87602648501068 
		64 0.87373607824652832 67 0.87373607824652832 87 0.87373607824652832 95 -7.0319749919458223 
		105 -0.68127875452050601 111 -0.23000169686518857 128 -0.68127875452050601;
	setAttr -s 13 ".kit[3:12]"  1 1 10 10 10 10 10 3 
		10 3;
	setAttr -s 13 ".kot[3:12]"  1 1 10 10 10 10 10 3 
		10 3;
	setAttr -s 13 ".kix[3:12]"  1 1 0.89655905961990356 1 1 1 0.99897849559783936 
		1 1 1;
	setAttr -s 13 ".kiy[3:12]"  0 0 0.44292429089546204 0 0 0 -0.045187346637248993 
		0 0 0;
	setAttr -s 13 ".kox[3:12]"  1 1 0.89655905961990356 1 1 1 0.99897849559783936 
		1 1 1;
	setAttr -s 13 ".koy[3:12]"  0 0 0.44292429089546204 0 0 0 -0.045187346637248993 
		0 0 0;
createNode animCurveTA -n "char_FKExtraR_Shoulder1_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Shoulder1_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Shoulder1_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_L_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 59 1 69 1 87 1 
		111 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_L_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 59 1 69 1 87 1 
		111 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_L_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 59 1 69 1 87 1 
		111 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Elbow1_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 48.213367515818511 12 20.522678395143831 
		25 20.522678395143831 35 20.522678395143831 51 20.522678395143831 59 76.128471187956578 
		69 20.522678395143831 79 31.539321434619016 87 29.117582344993934 95 33.426596170391747 
		100 14.97991209026889 111 48.213367515818511 128 48.213367515818511;
	setAttr -s 13 ".kit[3:12]"  1 1 10 10 10 10 10 10 
		3 3;
	setAttr -s 13 ".kot[3:12]"  1 1 10 10 10 10 10 10 
		3 3;
	setAttr -s 13 ".kix[3:12]"  1 1 1 0.65057456493377686 1 1 0.86899375915527344 
		0.90015041828155518 1 1;
	setAttr -s 13 ".kiy[3:12]"  0 0 0 -0.75944244861602783 0 0 -0.49482309818267822 
		0.43557918071746826 0 0;
	setAttr -s 13 ".kox[3:12]"  1 1 1 0.65057456493377686 1 1 0.86899375915527344 
		0.90015041828155518 1 1;
	setAttr -s 13 ".koy[3:12]"  0 0 0 -0.75944244861602783 0 0 -0.49482309818267822 
		0.43557918071746826 0 0;
createNode animCurveTA -n "char_FKExtraR_Elbow1_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Elbow1_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Elbow1_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveDevice3_L_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveDevice3_L_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveDevice3_L_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveDevice3_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -83.798780827240449 12 -83.798780827240449 
		25 -83.798780827240449 35 -83.798780827240449 51 -83.798780827240449 63 -83.798780827240449 
		67 -83.798780827240449 87 -83.798780827240449 105 -83.798780827240449 128 -83.798780827240449;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveDevice3_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.15209529104924274 12 -0.15209529104924274 
		25 -0.15209529104924274 35 -0.15209529104924274 51 -0.15209529104924274 63 -0.15209529104924274 
		67 -0.15209529104924274 87 -0.15209529104924274 105 -0.15209529104924274 128 -0.15209529104924274;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveDevice3_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -4.6558253190878789 12 -4.6558253190878789 
		25 -4.6558253190878789 35 -4.6558253190878789 51 -4.6558253190878789 63 -4.6558253190878789 
		67 -4.6558253190878789 87 -4.6558253190878789 105 -4.6558253190878789 128 -4.6558253190878789;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKCurveDevice3_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.070796223027113955 12 0.070796223027113955 
		25 0.070796223027113955 35 0.070796223027113955 51 0.070796223027113955 63 0.070796223027113955 
		67 0.070796223027113955 87 0.070796223027113955 105 0.070796223027113955 128 0.070796223027113955;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKCurveDevice3_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.0024602716719113347 12 0.0024602716719113347 
		25 0.0024602716719113347 35 0.0024602716719113347 51 0.0024602716719113347 63 0.0024602716719113347 
		67 0.0024602716719113347 87 0.0024602716719113347 105 0.0024602716719113347 128 0.0024602716719113347;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKCurveDevice3_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.20119425626585011 12 0.20119425626585011 
		25 0.20119425626585011 35 0.20119425626585011 51 0.20119425626585011 63 0.20119425626585011 
		67 0.20119425626585011 87 0.20119425626585011 105 0.20119425626585011 128 0.20119425626585011;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKExtraDevice3_L_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKExtraDevice3_L_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKExtraDevice3_L_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraDevice3_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraDevice3_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraDevice3_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKExtraDevice3_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKExtraDevice3_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKExtraDevice3_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb5_L_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb5_L_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb5_L_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb5_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 64.163191954635607 12 64.163191954635607 
		25 64.163191954635607 35 64.163191954635607 51 64.163191954635607 63 64.163191954635607 
		67 64.163191954635607 87 64.163191954635607 105 64.163191954635607 128 64.163191954635607;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb5_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 2.4325234183121345 12 2.4325234183121345 
		25 2.4325234183121345 35 2.4325234183121345 51 2.4325234183121345 63 2.4325234183121345 
		67 2.4325234183121345 87 2.4325234183121345 105 2.4325234183121345 128 2.4325234183121345;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb5_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 8.5957802944005888 12 8.5957802944005888 
		25 8.5957802944005888 35 8.5957802944005888 51 8.5957802944005888 63 8.5957802944005888 
		67 8.5957802944005888 87 8.5957802944005888 105 8.5957802944005888 128 8.5957802944005888;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb5_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb5_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb5_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb6_L_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb6_L_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb6_L_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb6_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 30.907503992135247 12 30.907503992135247 
		25 30.907503992135247 35 30.907503992135247 51 30.907503992135247 63 30.907503992135247 
		67 30.907503992135247 87 30.907503992135247 105 30.907503992135247 128 30.907503992135247;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb6_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -37.423813770375673 12 -37.423813770375673 
		25 -37.423813770375673 35 -37.423813770375673 51 -37.423813770375673 63 -37.423813770375673 
		67 -37.423813770375673 87 -37.423813770375673 105 -37.423813770375673 128 -37.423813770375673;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb6_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -55.763523784114774 12 -55.763523784114774 
		25 -55.763523784114774 35 -55.763523784114774 51 -55.763523784114774 63 -55.763523784114774 
		67 -55.763523784114774 87 -55.763523784114774 105 -55.763523784114774 128 -55.763523784114774;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb6_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb6_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb6_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle5_L_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle5_L_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle5_L_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle5_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 65.894016206888068 12 65.894016206888068 
		25 65.894016206888068 35 65.894016206888068 51 65.894016206888068 63 65.894016206888068 
		67 65.894016206888068 87 65.894016206888068 105 65.894016206888068 128 65.894016206888068;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle5_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 18.465908619718412 12 18.465908619718412 
		25 18.465908619718412 35 18.465908619718412 51 18.465908619718412 63 18.465908619718412 
		67 18.465908619718412 87 18.465908619718412 105 18.465908619718412 128 18.465908619718412;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle5_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -36.952741198413079 12 -36.952741198413079 
		25 -36.952741198413079 35 -36.952741198413079 51 -36.952741198413079 63 -36.952741198413079 
		67 -36.952741198413079 87 -36.952741198413079 105 -36.952741198413079 128 -36.952741198413079;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle5_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle5_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle5_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle6_L_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle6_L_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle6_L_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle6_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 17.446522746060875 12 17.446522746060875 
		25 17.446522746060875 35 17.446522746060875 51 17.446522746060875 63 17.446522746060875 
		67 17.446522746060875 87 17.446522746060875 105 17.446522746060875 128 17.446522746060875;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle6_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle6_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle6_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle6_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle6_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_L_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 59 1 64 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_L_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 59 1 64 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_L_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 59 1 64 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 12 0 25 0 35 0 51 0 59 -4.0668961194799573 
		64 0 75 3.6132043507180902 87 0 95 7.3086693228173845 105 0 128 0;
	setAttr -s 12 ".kit[3:11]"  1 1 10 10 10 10 10 3 
		3;
	setAttr -s 12 ".kot[3:11]"  1 1 10 10 10 10 10 3 
		3;
	setAttr -s 12 ".kix[3:11]"  1 1 1 0.96983814239501953 1 0.99535262584686279 
		1 1 1;
	setAttr -s 12 ".kiy[3:11]"  0 0 0 0.24375009536743164 0 0.096297413110733032 
		0 0 0;
	setAttr -s 12 ".kox[3:11]"  1 1 1 0.96983814239501953 1 0.99535262584686279 
		1 1 1;
	setAttr -s 12 ".koy[3:11]"  0 0 0 0.24375009536743164 0 0.096297413110733032 
		0 0 0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 24.211026325508492 12 24.211026325508492 
		25 24.211026325508492 35 24.211026325508492 51 24.211026325508492 59 20.32415744405672 
		64 24.211026325508492 75 29.224520416848272 87 24.211026325508492 95 32.754590853126331 
		105 24.211026325508492 128 24.211026325508492;
	setAttr -s 12 ".kit[3:11]"  1 1 10 10 10 10 10 3 
		3;
	setAttr -s 12 ".kot[3:11]"  1 1 10 10 10 10 10 3 
		3;
	setAttr -s 12 ".kix[3:11]"  1 1 1 0.96010386943817139 1 0.99575668573379517 
		1 1 1;
	setAttr -s 12 ".kiy[3:11]"  0 0 0 0.27964344620704651 0 0.092024862766265869 
		0 0 0;
	setAttr -s 12 ".kox[3:11]"  1 1 1 0.96010386943817139 1 0.99575668573379517 
		1 1 1;
	setAttr -s 12 ".koy[3:11]"  0 0 0 0.27964344620704651 0 0.092024862766265869 
		0 0 0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 12 0 25 0 35 0 51 0 59 15.122834533319619 
		64 0 75 -6.2091938549328409 87 0 95 -4.6868725557736433 105 0 128 0;
	setAttr -s 12 ".kit[3:11]"  1 1 10 10 10 10 10 3 
		3;
	setAttr -s 12 ".kot[3:11]"  1 1 10 10 10 10 10 3 
		3;
	setAttr -s 12 ".kix[3:11]"  1 1 1 0.81996732950210571 1 0.99920684099197388 
		1 1 1;
	setAttr -s 12 ".kiy[3:11]"  0 0 0 -0.5724102258682251 0 0.039822660386562347 
		0 0 0;
	setAttr -s 12 ".kox[3:11]"  1 1 1 0.81996732950210571 1 0.99920684099197388 
		1 1 1;
	setAttr -s 12 ".koy[3:11]"  0 0 0 -0.5724102258682251 0 0.039822660386562347 
		0 0 0;
createNode animCurveTA -n "char_FKExtraR_Wrist1_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Wrist1_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Wrist1_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Hip1_L_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Hip1_L_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Hip1_L_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Hip1_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Hip1_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Hip1_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Hip1_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Hip1_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Hip1_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Knee1_L_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Knee1_L_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Knee1_L_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Knee1_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Knee1_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Knee1_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Knee1_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ankle1_L_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ankle1_L_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ankle1_L_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ankle1_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ankle1_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ankle1_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ankle1_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ankle1_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ankle1_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ball1_L_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ball1_L_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ball1_L_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ball1_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ball1_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ball1_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ball1_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ball1_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ball1_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Clavicle1_R_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 6 1 12 1 25 1 51 1 63 1 67 1 87 1 105 
		1 128 1;
	setAttr -s 10 ".kit[4:9]"  1 10 10 10 3 3;
	setAttr -s 10 ".kot[4:9]"  1 10 10 10 3 3;
	setAttr -s 10 ".kix[4:9]"  1 1 1 1 1 1;
	setAttr -s 10 ".kiy[4:9]"  0 0 0 0 0 0;
	setAttr -s 10 ".kox[4:9]"  1 1 1 1 1 1;
	setAttr -s 10 ".koy[4:9]"  0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Clavicle1_R_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 6 1 12 1 25 1 51 1 63 1 67 1 87 1 105 
		1 128 1;
	setAttr -s 10 ".kit[4:9]"  1 10 10 10 3 3;
	setAttr -s 10 ".kot[4:9]"  1 10 10 10 3 3;
	setAttr -s 10 ".kix[4:9]"  1 1 1 1 1 1;
	setAttr -s 10 ".kiy[4:9]"  0 0 0 0 0 0;
	setAttr -s 10 ".kox[4:9]"  1 1 1 1 1 1;
	setAttr -s 10 ".koy[4:9]"  0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Clavicle1_R_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 6 1 12 1 25 1 51 1 63 1 67 1 87 1 105 
		1 128 1;
	setAttr -s 10 ".kit[4:9]"  1 10 10 10 3 3;
	setAttr -s 10 ".kot[4:9]"  1 10 10 10 3 3;
	setAttr -s 10 ".kix[4:9]"  1 1 1 1 1 1;
	setAttr -s 10 ".kiy[4:9]"  0 0 0 0 0 0;
	setAttr -s 10 ".kox[4:9]"  1 1 1 1 1 1;
	setAttr -s 10 ".koy[4:9]"  0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 6 -8.5945858876946506 12 0 25 0 37 
		-8.7845510745241207 51 -8.7845510745241207 63 0 67 0 87 0 105 0 128 0;
	setAttr -s 11 ".kit[5:10]"  1 10 10 10 3 3;
	setAttr -s 11 ".kot[5:10]"  1 10 10 10 3 3;
	setAttr -s 11 ".kix[5:10]"  1 1 1 1 1 1;
	setAttr -s 11 ".kiy[5:10]"  0 0 0 0 0 0;
	setAttr -s 11 ".kox[5:10]"  1 1 1 1 1 1;
	setAttr -s 11 ".koy[5:10]"  0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 6 -3.3948601740827566 12 0 25 0 37 
		6.8011294847065509 51 6.8011294847065509 63 0 67 0 87 0 105 0 128 0;
	setAttr -s 11 ".kit[5:10]"  1 10 10 10 3 3;
	setAttr -s 11 ".kot[5:10]"  1 10 10 10 3 3;
	setAttr -s 11 ".kix[5:10]"  1 1 1 1 1 1;
	setAttr -s 11 ".kiy[5:10]"  0 0 0 0 0 0;
	setAttr -s 11 ".kox[5:10]"  1 1 1 1 1 1;
	setAttr -s 11 ".koy[5:10]"  0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 6 1.079025391531373 12 0 25 0 37 2.2973059038892729 
		51 2.2973059038892729 63 0 67 0 87 0 105 0 128 0;
	setAttr -s 11 ".kit[5:10]"  1 10 10 10 3 3;
	setAttr -s 11 ".kot[5:10]"  1 10 10 10 3 3;
	setAttr -s 11 ".kix[5:10]"  1 1 1 1 1 1;
	setAttr -s 11 ".kiy[5:10]"  0 0 0 0 0 0;
	setAttr -s 11 ".kox[5:10]"  1 1 1 1 1 1;
	setAttr -s 11 ".koy[5:10]"  0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -2.194210208e-008 12 -2.194210208e-008 
		25 -2.194210208e-008 35 -2.194210208e-008 51 -2.194210208e-008 63 -2.194210208e-008 
		67 -2.194210208e-008 87 -2.194210208e-008 105 -2.194210208e-008 128 -2.194210208e-008;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_R_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 1 6 1 10 1 13 1 25 1 31 1 37 1 41 1 51 
		1 70 1 87 1 105 1 128 1;
	setAttr -s 13 ".kit[0:12]"  1 10 10 10 10 10 1 10 
		1 10 10 3 3;
	setAttr -s 13 ".kot[0:12]"  1 10 10 10 10 10 1 10 
		1 10 10 3 3;
	setAttr -s 13 ".kix[0:12]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[0:12]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[0:12]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[0:12]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_R_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 1 6 1 10 1 13 1 25 1 31 1 37 1 41 1 51 
		1 70 1 87 1 105 1 128 1;
	setAttr -s 13 ".kit[0:12]"  1 10 10 10 10 10 1 10 
		1 10 10 3 3;
	setAttr -s 13 ".kot[0:12]"  1 10 10 10 10 10 1 10 
		1 10 10 3 3;
	setAttr -s 13 ".kix[0:12]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[0:12]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[0:12]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[0:12]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_R_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 1 6 1 10 1 13 1 25 1 31 1 37 1 41 1 51 
		1 70 1 87 1 105 1 128 1;
	setAttr -s 13 ".kit[0:12]"  1 10 10 10 10 10 1 10 
		1 10 10 3 3;
	setAttr -s 13 ".kot[0:12]"  1 10 10 10 10 10 1 10 
		1 10 10 3 3;
	setAttr -s 13 ".kix[0:12]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[0:12]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[0:12]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[0:12]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Shoulder1_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 17.19229314797029 6 14.402664337793794 
		10 -0.9540775363279721 13 3.3217116017713675 25 3.3217116017713675 31 -11.146540422406732 
		37 5.5444813785453206 41 5.544481378545326 51 5.544481378545326 58 6.7392075621285406 
		70 24.250282979971047 87 24.250282979971047 105 17.19229314797029 128 17.19229314797029;
	setAttr -s 14 ".kit[0:13]"  1 10 10 10 10 10 1 10 
		1 10 10 10 3 3;
	setAttr -s 14 ".kot[0:13]"  1 10 10 10 10 10 1 10 
		1 10 10 10 3 3;
	setAttr -s 14 ".kix[0:13]"  0.91759800910949707 1 0.76991492509841919 
		1 1 0.99532973766326904 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[0:13]"  0.39750954508781433 0 -0.63814651966094971 
		0 0 0.09653366357088089 0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[0:13]"  0.91759806871414185 1 0.76991492509841919 
		1 1 0.99532973766326904 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[0:13]"  0.39750951528549194 0 -0.63814651966094971 
		0 0 0.09653366357088089 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Shoulder1_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Shoulder1_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Shoulder1_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_R_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 1 6 1 10 1 13 1 25 1 31 1 37 1 41 1 51 
		1 70 1 87 1 105 1 128 1;
	setAttr -s 13 ".kit[6:12]"  1 10 1 10 10 3 3;
	setAttr -s 13 ".kot[6:12]"  1 10 1 10 10 3 3;
	setAttr -s 13 ".kix[6:12]"  1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[6:12]"  0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[6:12]"  1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[6:12]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_R_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 1 6 1 10 1 13 1 25 1 31 1 37 1 41 1 51 
		1 70 1 87 1 105 1 128 1;
	setAttr -s 13 ".kit[6:12]"  1 10 1 10 10 3 3;
	setAttr -s 13 ".kot[6:12]"  1 10 1 10 10 3 3;
	setAttr -s 13 ".kix[6:12]"  1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[6:12]"  0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[6:12]"  1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[6:12]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_R_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 1 6 1 10 1 13 1 25 1 31 1 37 1 41 1 51 
		1 70 1 87 1 105 1 128 1;
	setAttr -s 13 ".kit[6:12]"  1 10 1 10 10 3 3;
	setAttr -s 13 ".kot[6:12]"  1 10 1 10 10 3 3;
	setAttr -s 13 ".kix[6:12]"  1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[6:12]"  0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[6:12]"  1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[6:12]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Elbow1_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 36.067317209388015 6 50.083121748384571 
		10 41.005543166361797 13 36.067317209388015 25 36.067317209388015 31 63.350404813799223 
		37 16.294347424642641 41 20.547957168391655 51 20.547957168391655 58 10.617714925302545 
		70 65.727347184824382 87 65.727347184824382 105 36.067317209388015 128 36.067317209388015;
	setAttr -s 14 ".kit[6:13]"  1 10 1 10 10 10 3 3;
	setAttr -s 14 ".kot[6:13]"  1 10 1 10 10 10 3 3;
	setAttr -s 14 ".kix[6:13]"  1 1 1 0.62620705366134644 1 1 1 1;
	setAttr -s 14 ".kiy[6:13]"  0 0 0 0.77965676784515381 0 0 0 0;
	setAttr -s 14 ".kox[6:13]"  1 1 1 0.62620705366134644 1 1 1 1;
	setAttr -s 14 ".koy[6:13]"  0 0 0 0.77965676784515381 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Elbow1_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Elbow1_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Elbow1_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb5_R_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 10 1 13 1 25 1 37 1 51 1 63 1 67 1 
		87 1 105 1 128 1;
	setAttr -s 11 ".kit[4:10]"  1 1 10 10 10 3 3;
	setAttr -s 11 ".kot[4:10]"  1 1 10 10 10 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb5_R_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 10 1 13 1 25 1 37 1 51 1 63 1 67 1 
		87 1 105 1 128 1;
	setAttr -s 11 ".kit[4:10]"  1 1 10 10 10 3 3;
	setAttr -s 11 ".kot[4:10]"  1 1 10 10 10 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb5_R_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 10 1 13 1 25 1 37 1 51 1 63 1 67 1 
		87 1 105 1 128 1;
	setAttr -s 11 ".kit[4:10]"  1 1 10 10 10 3 3;
	setAttr -s 11 ".kot[4:10]"  1 1 10 10 10 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb5_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 27.905251822156437 10 51.396487776820749 
		13 51.396487776820749 25 51.396487776820749 37 29.178646816977569 51 29.178646816977569 
		63 51.396487776820749 67 51.396487776820749 87 51.396487776820749 105 27.905251822156437 
		128 27.905251822156437;
	setAttr -s 11 ".kit[4:10]"  1 1 10 10 10 3 3;
	setAttr -s 11 ".kot[4:10]"  1 1 10 10 10 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb5_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 10 0 13 0 25 0 37 4.1512616609762931 
		51 4.1512616609762931 63 0 67 0 87 0 105 0 128 0;
	setAttr -s 11 ".kit[4:10]"  1 1 10 10 10 3 3;
	setAttr -s 11 ".kot[4:10]"  1 1 10 10 10 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb5_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 10 20.879391779818722 13 10.865522145334484 
		25 10.865522145334484 37 10.050062773385678 51 10.050062773385678 63 10.865522145334484 
		67 10.865522145334484 87 10.865522145334484 105 0 128 0;
	setAttr -s 11 ".kit[4:10]"  1 1 10 10 10 3 3;
	setAttr -s 11 ".kot[4:10]"  1 1 10 10 10 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb5_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb5_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb5_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb6_R_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 10 1 13 1 25 1 37 1 51 1 63 1 67 1 
		87 1 105 1 128 1;
	setAttr -s 11 ".kit[4:10]"  1 1 10 10 10 3 3;
	setAttr -s 11 ".kot[4:10]"  1 1 10 10 10 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb6_R_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 10 1 13 1 25 1 37 1 51 1 63 1 67 1 
		87 1 105 1 128 1;
	setAttr -s 11 ".kit[4:10]"  1 1 10 10 10 3 3;
	setAttr -s 11 ".kot[4:10]"  1 1 10 10 10 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb6_R_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 10 1 13 1 25 1 37 1 51 1 63 1 67 1 
		87 1 105 1 128 1;
	setAttr -s 11 ".kit[4:10]"  1 1 10 10 10 3 3;
	setAttr -s 11 ".kot[4:10]"  1 1 10 10 10 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb6_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 28.959457180709169 6 28.874316861411266 
		10 28.959457180709169 13 28.959457180709169 25 28.959457180709169 37 23.569040215624526 
		51 23.569040215624526 63 28.959457180709169 67 28.959457180709169 87 28.959457180709169 
		105 28.959457180709169 128 28.959457180709169;
	setAttr -s 12 ".kit[5:11]"  1 1 10 10 10 3 3;
	setAttr -s 12 ".kot[5:11]"  1 1 10 10 10 3 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb6_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -12.483272772594933 6 -12.450785350694028 
		10 -12.483272772594933 13 -12.483272772594933 25 -12.483272772594933 37 -7.0300988822361123 
		51 -7.0300988822361123 63 -12.483272772594933 67 -12.483272772594933 87 -12.483272772594933 
		105 -12.483272772594933 128 -12.483272772594933;
	setAttr -s 12 ".kit[5:11]"  1 1 10 10 10 3 3;
	setAttr -s 12 ".kot[5:11]"  1 1 10 10 10 3 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb6_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 21.335853393578894 6 21.354233299570602 
		10 21.335853393578894 13 21.335853393578894 25 21.335853393578894 37 12.150982484171623 
		51 12.150982484171623 63 21.335853393578894 67 21.335853393578894 87 21.335853393578894 
		105 21.335853393578894 128 21.335853393578894;
	setAttr -s 12 ".kit[5:11]"  1 1 10 10 10 3 3;
	setAttr -s 12 ".kot[5:11]"  1 1 10 10 10 3 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb6_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb6_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb6_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle5_R_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 1 6 1 10 1 13 1 25 1 37 1 51 1 63 1 71 
		1 87 1 105 1 128 1;
	setAttr -s 12 ".kit[5:11]"  1 1 10 10 1 3 3;
	setAttr -s 12 ".kot[5:11]"  1 1 10 10 1 3 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle5_R_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 1 6 1 10 1 13 1 25 1 37 1 51 1 63 1 71 
		1 87 1 105 1 128 1;
	setAttr -s 12 ".kit[5:11]"  1 1 10 10 1 3 3;
	setAttr -s 12 ".kot[5:11]"  1 1 10 10 1 3 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle5_R_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 1 6 1 10 1 13 1 25 1 37 1 51 1 63 1 71 
		1 87 1 105 1 128 1;
	setAttr -s 12 ".kit[5:11]"  1 1 10 10 1 3 3;
	setAttr -s 12 ".kot[5:11]"  1 1 10 10 1 3 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle5_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 36.340151082658281 6 27.569765734488836 
		10 76.977476767186474 13 54.937762236239074 25 54.937762236239074 37 26.377087634956681 
		51 26.377087634956681 63 54.937762236239074 71 38.591655435069086 87 44.071750956899137 
		96 67.348733760853506 105 36.340151082658281 128 36.340151082658281;
	setAttr -s 13 ".kit[5:12]"  1 1 10 10 1 10 3 3;
	setAttr -s 13 ".kot[5:12]"  1 1 10 10 1 10 3 3;
	setAttr -s 13 ".kix[5:12]"  1 1 0.95248591899871826 0.97303289175033569 
		0.83523505926132202 0.97562998533248901 1 1;
	setAttr -s 13 ".kiy[5:12]"  0 0 0.30458280444145203 -0.23066672682762146 
		0.5498930811882019 -0.21942226588726044 0 0;
	setAttr -s 13 ".kox[5:12]"  1 1 0.95248591899871826 0.97303289175033569 
		0.83523505926132202 0.97562998533248901 1 1;
	setAttr -s 13 ".koy[5:12]"  0 0 0.30458280444145203 -0.23066672682762146 
		0.5498930811882019 -0.21942226588726044 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle5_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 6 0 10 0 13 0 25 0 37 13.203539990871027 
		51 13.203539990871027 63 0 71 0 87 0 105 0 128 0;
	setAttr -s 12 ".kit[5:11]"  1 1 10 10 1 3 3;
	setAttr -s 12 ".kot[5:11]"  1 1 10 10 1 3 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle5_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 6 0 10 0 13 0 25 0 37 8.4529388124342706 
		51 8.4529388124342706 63 0 71 0 87 0 105 0 128 0;
	setAttr -s 12 ".kit[5:11]"  1 1 10 10 1 3 3;
	setAttr -s 12 ".kot[5:11]"  1 1 10 10 1 3 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle5_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle5_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle5_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle6_R_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 1 6 1 10 1 13 1 25 1 37 1 51 1 63 1 71 
		1 87 1 105 1 128 1;
	setAttr -s 12 ".kit[5:11]"  1 1 10 10 1 3 3;
	setAttr -s 12 ".kot[5:11]"  1 1 10 10 1 3 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle6_R_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 1 6 1 10 1 13 1 25 1 37 1 51 1 63 1 71 
		1 87 1 105 1 128 1;
	setAttr -s 12 ".kit[5:11]"  1 1 10 10 1 3 3;
	setAttr -s 12 ".kot[5:11]"  1 1 10 10 1 3 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle6_R_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 1 6 1 10 1 13 1 25 1 37 1 51 1 63 1 71 
		1 87 1 105 1 128 1;
	setAttr -s 12 ".kit[5:11]"  1 1 10 10 1 3 3;
	setAttr -s 12 ".kot[5:11]"  1 1 10 10 1 3 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle6_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 25.092322839093878 6 5.9220031003208797 
		10 27.539467956697091 13 27.539467956697091 25 27.539467956697091 37 1.0804584007175448 
		51 1.0804584007175448 63 27.539467956697091 71 11.193361155527052 87 16.58750494534101 
		96 31.436119795791772 105 25.092322839093878 128 25.092322839093878;
	setAttr -s 13 ".kit[5:12]"  1 1 10 10 1 10 3 3;
	setAttr -s 13 ".kot[5:12]"  1 1 10 10 1 10 3 3;
	setAttr -s 13 ".kix[5:12]"  1 1 0.9666934609413147 0.97262191772460938 
		0.83523505926132202 0.97073459625244141 1 1;
	setAttr -s 13 ".kiy[5:12]"  0 0 0.25593715906143188 -0.23239313066005707 
		0.5498930811882019 0.24015504121780396 0 0;
	setAttr -s 13 ".kox[5:12]"  1 1 0.9666934609413147 0.97262191772460938 
		0.83523505926132202 0.97073459625244141 1 1;
	setAttr -s 13 ".koy[5:12]"  0 0 0.25593715906143188 -0.23239313066005707 
		0.5498930811882019 0.24015504121780396 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle6_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 6 0 10 0 13 0 25 0 37 11.58822102418697 
		51 11.58822102418697 63 0 71 0 87 0 105 0 128 0;
	setAttr -s 12 ".kit[5:11]"  1 1 10 10 1 3 3;
	setAttr -s 12 ".kot[5:11]"  1 1 10 10 1 3 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle6_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 6 0 10 0 13 0 25 0 37 -19.857313307320922 
		51 -19.857313307320922 63 0 71 0 87 0 105 0 128 0;
	setAttr -s 12 ".kit[5:11]"  1 1 10 10 1 3 3;
	setAttr -s 12 ".kot[5:11]"  1 1 10 10 1 3 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle6_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle6_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle6_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_R_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 1 6 1 10 1 13 1 25 1 31 1 37 1 41 1 51 
		1 70 1 87 1 103 1 109 1 128 1;
	setAttr -s 14 ".kit[6:13]"  1 10 1 10 10 3 10 3;
	setAttr -s 14 ".kot[6:13]"  1 10 1 10 10 3 10 3;
	setAttr -s 14 ".kix[6:13]"  1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[6:13]"  0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[6:13]"  1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[6:13]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_R_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 1 6 1 10 1 13 1 25 1 31 1 37 1 41 1 51 
		1 70 1 87 1 103 1 109 1 128 1;
	setAttr -s 14 ".kit[6:13]"  1 10 1 10 10 3 10 3;
	setAttr -s 14 ".kot[6:13]"  1 10 1 10 10 3 10 3;
	setAttr -s 14 ".kix[6:13]"  1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[6:13]"  0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[6:13]"  1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[6:13]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_R_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 1 6 1 10 1 13 1 25 1 31 1 37 1 41 1 51 
		1 70 1 87 1 103 1 109 1 128 1;
	setAttr -s 14 ".kit[6:13]"  1 10 1 10 10 3 10 3;
	setAttr -s 14 ".kot[6:13]"  1 10 1 10 10 3 10 3;
	setAttr -s 14 ".kix[6:13]"  1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[6:13]"  0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[6:13]"  1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[6:13]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 5.3442930176413892 6 -30.335465000526348 
		10 -16.321525974766114 13 5.3442930176413892 25 5.3442930176413892 31 12.336971269843813 
		37 -10.158207978326578 41 -8.5105586337705521 51 -8.5105586337705521 58 1.0849586377767382 
		70 5.3442930176413892 87 5.3442930176413892 98 15.496434036103331 103 -10.694666115875844 
		109 5.3442930176413892 128 5.3442930176413892;
	setAttr -s 16 ".kit[6:15]"  1 10 1 10 10 10 10 3 
		10 3;
	setAttr -s 16 ".kot[6:15]"  1 10 1 10 10 10 10 3 
		10 3;
	setAttr -s 16 ".kix[6:15]"  1 1 1 0.93422102928161621 1 1 0.88544392585754395 
		1 1 1;
	setAttr -s 16 ".kiy[6:15]"  0 0 0 0.35669469833374023 0 0 -0.46474626660346985 
		0 0 0;
	setAttr -s 16 ".kox[6:15]"  1 1 1 0.93422102928161621 1 1 0.88544392585754395 
		1 1 1;
	setAttr -s 16 ".koy[6:15]"  0 0 0 0.35669469833374023 0 0 -0.46474626660346985 
		0 0 0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 30.381278874765098 6 30.91043203589896 
		10 27.139905712566545 13 30.381278874765098 25 30.381278874765098 31 48.135671310319424 
		37 47.917520905392024 41 48.357090309234685 51 48.357090309234685 58 35.903663335566058 
		70 30.381278874765098 87 30.381278874765098 98 27.823047386925918 103 32.330355530422509 
		109 30.381278874765098 128 30.381278874765098;
	setAttr -s 16 ".kit[6:15]"  1 10 1 10 10 10 10 3 
		10 3;
	setAttr -s 16 ".kot[6:15]"  1 10 1 10 10 10 10 3 
		10 3;
	setAttr -s 16 ".kix[6:15]"  1 1 1 0.89607894420623779 1 1 1 1 1 1;
	setAttr -s 16 ".kiy[6:15]"  0 0 0 -0.44389462471008301 0 0 0 0 0 0;
	setAttr -s 16 ".kox[6:15]"  1 1 1 0.89607894420623779 1 1 1 1 1 1;
	setAttr -s 16 ".koy[6:15]"  0 0 0 -0.44389462471008301 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 11.798366512855891 6 -10.184276027455608 
		10 0.56312011314008137 13 11.798366512855891 25 11.798366512855891 31 18.312147317919369 
		37 11.667814968517455 41 -0.056730004259644175 51 -0.056730004259644175 58 6.0396024706950673 
		70 11.798366512855891 87 11.798366512855891 98 17.284899413801373 103 2.0203694428263219 
		109 11.798366512855891 128 11.798366512855891;
	setAttr -s 16 ".kit[6:15]"  1 10 1 10 10 10 10 3 
		10 3;
	setAttr -s 16 ".kot[6:15]"  1 10 1 10 10 10 10 3 
		10 3;
	setAttr -s 16 ".kix[6:15]"  1 1 1 0.95055770874023438 1 1 0.95242846012115479 
		1 1 1;
	setAttr -s 16 ".kiy[6:15]"  0 0 0 0.31054797768592834 0 0 -0.3047620952129364 
		0 0 0;
	setAttr -s 16 ".kox[6:15]"  1 1 1 0.95055770874023438 1 1 0.95242846012115479 
		1 1 1;
	setAttr -s 16 ".koy[6:15]"  0 0 0 0.31054797768592834 0 0 -0.3047620952129364 
		0 0 0;
createNode animCurveTA -n "char_FKExtraR_Wrist1_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Wrist1_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Wrist1_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Hip1_R_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Hip1_R_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Hip1_R_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Hip1_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Hip1_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Hip1_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Hip1_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Hip1_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Hip1_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Knee1_R_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Knee1_R_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Knee1_R_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Knee1_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Knee1_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Knee1_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Knee1_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ankle1_R_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ankle1_R_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ankle1_R_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ankle1_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ankle1_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ankle1_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ankle1_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ankle1_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ankle1_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ball1_R_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ball1_R_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ball1_R_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ball1_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ball1_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ball1_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ball1_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ball1_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ball1_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_All_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_All_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_All_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_All_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_All_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "char_All_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_All_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_All_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "char_All_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 12 0 25 0 35 0 51 0 63 0 67 0 87 0 
		105 0 128 0;
	setAttr -s 10 ".kit[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kot[3:9]"  1 1 10 10 10 3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "char_All_visibility";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 12 1 25 1 35 1 51 1 63 1 67 1 87 1 
		105 1 128 1;
	setAttr -s 10 ".kit[0:9]"  9 9 9 1 1 9 9 9 
		3 3;
	setAttr -s 10 ".kot[8:9]"  3 3;
	setAttr -s 10 ".kix[3:9]"  1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0 0 0 0 0 0 0;
createNode lightLinker -n "lightLinker1";
	setAttr -s 3 ".lnk";
	setAttr -s 3 ".slnk";
select -ne :time1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 128;
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
	setAttr -s 4 ".sol";
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
connectAttr "maugli_idleSource.cl" "clipLibrary1.sc[0]";
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
// End of maugli_idle.ma
