//Maya ASCII 2008 scene
//Name: maugli_happy.ma
//Last modified: Tue, May 19, 2009 03:23:01 PM
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
createNode animClip -n "happySource";
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
	setAttr ".se" 126;
	setAttr ".ci" no;
createNode animCurveTU -n "char_AimCurveEye_Right1_M_follow";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 10 25 10 32 10 35 10 45 
		10 52 10 57 10 63 10 68 10 74 10 78 10 84 10 88 10 93 10 101 10 106 10 110 10 116 
		3.5200020599356634 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_AimCurveEye_Right1_M_cross";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_AimCurveEye_Right1_M_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 3.4299179804087934 7 2.6850642214584846 
		10 2.6850642214584846 16 2.6850642214584846 25 3.1367538846145551 32 3.4299179804087934 
		35 3.4299179804087934 45 3.4299179804087934 52 3.4299179804087934 57 3.4299179804087934 
		63 3.4299179804087934 68 3.4299179804087934 74 3.4299179804087934 78 3.4299179804087934 
		84 3.4299179804087934 88 3.4299179804087934 93 3.4299179804087934 101 3.1367538846145551 
		106 3.1367538846145551 110 3.1367538846145551 116 3.3267241582993039 126 3.4299179804087934;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_AimCurveEye_Right1_M_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 -0.81831860840024984 7 -0.81831860840024984 
		10 -0.81831860840024984 16 -0.81831860840024984 25 -0.81831860840024984 32 -0.81831860840024984 
		35 -0.81831860840024984 45 -0.81831860840024984 52 -0.81831860840024984 57 -0.81831860840024984 
		63 -0.81831860840024984 68 -0.81831860840024984 74 -0.81831860840024984 78 -0.81831860840024984 
		84 -0.81831860840024984 88 -0.81831860840024984 93 -0.81831860840024984 101 -0.81831860840024984 
		106 -0.81831860840024984 110 -0.81831860840024984 116 -0.81831860840024984 126 -0.81831860840024984;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_AimCurveEye_Right1_M_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0.059018783840309119 7 2.0470687031057695 
		10 2.0470687031057695 16 2.0470687031057695 25 0.84148762416222334 32 0.059018783840309119 
		35 0.059018783840309119 45 0.059018783840309119 52 0.059018783840309119 57 0.059018783840309119 
		63 0.059018783840309119 68 0.059018783840309119 74 0.059018783840309119 78 0.059018783840309119 
		84 0.059018783840309119 88 0.059018783840309119 93 0.059018783840309119 101 0.84148762416222334 
		106 0.84148762416222334 110 0.84148762416222334 116 0.33444797681716976 126 0.059018783840309119;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveArm_L_IKVis";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveArm_L_FKVis";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveArm_L_FKIKBlend";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveLeg_L_IKVis";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveLeg_L_FKVis";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveLeg_L_FKIKBlend";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 10 7 10 10 10 16 10 25 10 32 10 35 10 
		45 10 52 10 57 10 63 10 68 10 74 10 78 10 84 10 88 10 93 10 101 10 106 10 110 10 
		116 10 126 10;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveArm_R_IKVis";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveArm_R_FKVis";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveArm_R_FKIKBlend";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveLeg_R_IKVis";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveLeg_R_FKVis";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKIKControlCurveLeg_R_FKIKBlend";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 10 7 10 10 10 16 10 25 10 32 10 35 10 
		45 10 52 10 57 10 63 10 68 10 74 10 78 10 84 10 88 10 93 10 101 10 106 10 110 10 
		116 10 126 10;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKPoleVectorCurveArm_L_follow";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveArm_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveArm_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveArm_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraArm_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraArm_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraArm_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveArm_L_antiPop";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveArm_L_stretchy";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveArm_L_follow";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveArm_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveArm_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveArm_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveArm_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveArm_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveArm_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraArm_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraArm_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraArm_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraArm_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraArm_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraArm_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKPoleVectorCurveLeg_L_follow";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 10 7 10 10 10 16 10 25 10 32 10 35 10 
		45 10 52 10 57 10 63 10 68 10 74 10 78 10 84 10 88 10 93 10 101 10 106 10 110 10 
		116 10 126 10;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraLeg_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraLeg_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraLeg_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveLeg_L_antiPop";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveLeg_L_stretchy";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveLeg_L_swivel";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveLeg_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveLeg_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 43.567069197048298 7 43.567069197048298 
		10 43.567069197048298 16 43.567069197048298 25 43.567069197048298 32 43.567069197048298 
		35 43.567069197048298 45 43.567069197048298 52 43.567069197048298 57 43.567069197048298 
		63 43.567069197048298 68 43.567069197048298 74 43.567069197048298 78 43.567069197048298 
		84 43.567069197048298 88 43.567069197048298 93 43.567069197048298 101 43.567069197048298 
		106 43.567069197048298 110 43.567069197048298 116 43.567069197048298 126 43.567069197048298;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveLeg_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveLeg_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 -0.28844199405395621 7 -0.28844199405395621 
		10 -0.28844199405395621 16 -0.28844199405395621 25 -0.28844199405395621 32 -0.28844199405395621 
		35 -0.28844199405395621 45 -0.28844199405395621 52 -0.28844199405395621 57 -0.28844199405395621 
		63 -0.28844199405395621 68 -0.28844199405395621 74 -0.28844199405395621 78 -0.28844199405395621 
		84 -0.28844199405395621 88 -0.28844199405395621 93 -0.28844199405395621 101 -0.28844199405395621 
		106 -0.28844199405395621 110 -0.28844199405395621 116 -0.28844199405395621 126 -0.28844199405395621;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveLeg_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveLeg_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0.087756482507145378 7 0.087756482507145378 
		10 0.087756482507145378 16 0.087756482507145378 25 0.087756482507145378 32 0.087756482507145378 
		35 0.087756482507145378 45 0.087756482507145378 52 0.087756482507145378 57 0.087756482507145378 
		63 0.087756482507145378 68 0.087756482507145378 74 0.087756482507145378 78 0.087756482507145378 
		84 0.087756482507145378 88 0.087756482507145378 93 0.087756482507145378 101 0.087756482507145378 
		106 0.087756482507145378 110 0.087756482507145378 116 0.087756482507145378 126 0.087756482507145378;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraLeg_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraLeg_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraLeg_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraLeg_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraLeg_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraLeg_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKPoleVectorCurveArm_R_follow";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveArm_R_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveArm_R_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveArm_R_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraArm_R_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraArm_R_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraArm_R_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveArm_R_antiPop";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveArm_R_stretchy";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveArm_R_follow";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveArm_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveArm_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveArm_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveArm_R_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveArm_R_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveArm_R_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraArm_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraArm_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraArm_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraArm_R_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraArm_R_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraArm_R_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKPoleVectorCurveLeg_R_follow";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 10 7 10 10 10 16 10 25 10 32 10 35 10 
		45 10 52 10 57 10 63 10 68 10 74 10 78 10 84 10 88 10 93 10 101 10 106 10 110 10 
		116 10 126 10;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_R_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_R_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorCurveLeg_R_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraLeg_R_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraLeg_R_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKPoleVectorExtraLeg_R_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveLeg_R_antiPop";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 23 ".ktv[0:22]"  0 0 7 0 10 0 15 0 19 0 23 0 32 0 35 0 45 
		0 52 0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 23 ".kit[5:22]"  1 3 3 3 3 3 3 3 
		3 3 3 3 1 3 3 3 3 3;
	setAttr -s 23 ".kot[5:22]"  1 3 3 3 1 3 1 3 
		1 3 1 3 1 3 3 3 3 3;
	setAttr -s 23 ".kix[5:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".kiy[5:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 23 ".kox[5:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".koy[5:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveLeg_R_stretchy";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 23 ".ktv[0:22]"  0 0 7 0 10 0 15 0 19 0 23 0 32 0 35 0 45 
		0 52 0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 23 ".kit[5:22]"  1 3 3 3 3 3 3 3 
		3 3 3 3 1 3 3 3 3 3;
	setAttr -s 23 ".kot[5:22]"  1 3 3 3 1 3 1 3 
		1 3 1 3 1 3 3 3 3 3;
	setAttr -s 23 ".kix[5:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".kiy[5:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 23 ".kox[5:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".koy[5:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_IKCurveLeg_R_swivel";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 23 ".ktv[0:22]"  0 0 7 0 10 0 15 0 19 0 23 0 32 0 35 0 45 
		0 52 0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 23 ".kit[5:22]"  1 3 3 3 3 3 3 3 
		3 3 3 3 1 3 3 3 3 3;
	setAttr -s 23 ".kot[5:22]"  1 3 3 3 1 3 1 3 
		1 3 1 3 1 3 3 3 3 3;
	setAttr -s 23 ".kix[5:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".kiy[5:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 23 ".kox[5:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".koy[5:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveLeg_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 23 ".ktv[0:22]"  0 0 7 0 10 0 15 0 19 -3.2397482424158595 
		23 0 32 0 35 0 45 0 52 0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 
		0 116 0 126 0;
	setAttr -s 23 ".kit[5:22]"  1 3 3 3 3 3 3 3 
		3 3 3 3 1 3 3 3 3 3;
	setAttr -s 23 ".kot[5:22]"  1 3 3 3 1 3 1 3 
		1 3 1 3 1 3 3 3 3 3;
	setAttr -s 23 ".kix[5:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".kiy[5:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 23 ".kox[5:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".koy[5:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveLeg_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 23 ".ktv[0:22]"  0 0 7 0 10 0 15 0 19 1.4713410418735273 
		23 -15.791881762488233 32 -15.791881762488233 35 -15.791881762488233 45 -15.791881762488233 
		52 -15.791881762488233 57 -15.791881762488233 63 -15.791881762488233 68 -15.791881762488233 
		74 -15.791881762488233 78 -15.791881762488233 84 -15.791881762488233 88 -15.791881762488233 
		93 -15.791881762488233 101 -15.791881762488233 106 -15.791881762488233 110 0 116 
		0 126 0;
	setAttr -s 23 ".kit[5:22]"  1 3 3 3 3 3 3 3 
		3 3 3 3 1 3 3 3 3 3;
	setAttr -s 23 ".kot[5:22]"  1 3 3 3 1 3 1 3 
		1 3 1 3 1 3 3 3 3 3;
	setAttr -s 23 ".kix[5:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".kiy[5:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 23 ".kox[5:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".koy[5:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKCurveLeg_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 23 ".ktv[0:22]"  0 0 7 0 10 0 15 0 19 35.975686612296883 
		23 0 32 0 35 0 45 0 52 0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 
		0 116 0 126 0;
	setAttr -s 23 ".kit[5:22]"  1 3 3 3 3 3 3 3 
		3 3 3 3 1 3 3 3 3 3;
	setAttr -s 23 ".kot[5:22]"  1 3 3 3 1 3 1 3 
		1 3 1 3 1 3 3 3 3 3;
	setAttr -s 23 ".kix[5:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".kiy[5:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 23 ".kox[5:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".koy[5:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveLeg_R_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 23 ".ktv[0:22]"  0 0.33022172654533777 7 0.33022172654533777 
		10 0.33022172654533777 15 0.33022172654533777 19 0.022027550906825032 23 -0.21597607859596368 
		32 -0.21597607859596368 35 -0.21597607859596368 45 -0.21597607859596368 52 -0.21597607859596368 
		57 -0.21597607859596368 63 -0.21597607859596368 68 -0.21597607859596368 74 -0.21597607859596368 
		78 -0.21597607859596368 84 -0.21597607859596368 88 -0.21597607859596368 93 -0.21597607859596368 
		101 -0.21597607859596368 106 -0.21597607859596368 110 0.33022172654533777 116 0.33022172654533777 
		126 0.33022172654533777;
	setAttr -s 23 ".kit[5:22]"  1 3 3 3 3 3 3 3 
		3 3 3 3 1 3 3 3 3 3;
	setAttr -s 23 ".kot[5:22]"  1 3 3 3 1 3 1 3 
		1 3 1 3 1 3 3 3 3 3;
	setAttr -s 23 ".kix[5:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".kiy[5:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 23 ".kox[5:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".koy[5:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveLeg_R_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 23 ".ktv[0:22]"  0 0 7 0 10 0 15 0 19 0.21020231047095414 
		23 0 32 0 35 0 45 0 52 0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 
		0 116 0 126 0;
	setAttr -s 23 ".kit[5:22]"  1 3 3 3 3 3 3 3 
		3 3 3 3 1 3 3 3 3 3;
	setAttr -s 23 ".kot[5:22]"  1 3 3 3 1 3 1 3 
		1 3 1 3 1 3 3 3 3 3;
	setAttr -s 23 ".kix[5:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".kiy[5:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 23 ".kox[5:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".koy[5:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKCurveLeg_R_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 23 ".ktv[0:22]"  0 -0.13911956167322667 7 -0.13911956167322667 
		10 -0.13911956167322667 15 -0.13911956167322667 19 -0.15581675982176263 23 -0.27582821524686413 
		32 -0.27582821524686413 35 -0.27582821524686413 45 -0.27582821524686413 52 -0.27582821524686413 
		57 -0.27582821524686413 63 -0.27582821524686413 68 -0.27582821524686413 74 -0.27582821524686413 
		78 -0.27582821524686413 84 -0.27582821524686413 88 -0.27582821524686413 93 -0.27582821524686413 
		101 -0.27582821524686413 106 -0.27582821524686413 110 -0.13911956167322667 116 -0.13911956167322667 
		126 -0.13911956167322667;
	setAttr -s 23 ".kit[5:22]"  1 3 3 3 3 3 3 3 
		3 3 3 3 1 3 3 3 3 3;
	setAttr -s 23 ".kot[5:22]"  1 3 3 3 1 3 1 3 
		1 3 1 3 1 3 3 3 3 3;
	setAttr -s 23 ".kix[5:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".kiy[5:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 23 ".kox[5:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".koy[5:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraLeg_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraLeg_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_IKExtraLeg_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraLeg_R_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraLeg_R_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_IKExtraLeg_R_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveTooth1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 31 ".ktv[0:30]"  0 1 7 1 10 1 16 1 25 1 35 1 38 1 45 1 46 
		1 52 1 54 1 57 1 58 1 63 1 65 1 68 1 70 1 74 1 75 1 78 1 80 1 84 1 85 1 88 1 89 1 
		93 1 99 1 106 1 110 1 116 1 126 1;
	setAttr -s 31 ".kit[6:30]"  1 3 10 3 1 3 10 3 
		1 3 10 3 1 3 10 3 1 3 10 1 3 3 3 3 3;
	setAttr -s 31 ".kot[6:30]"  1 3 10 1 1 3 10 1 
		1 3 10 1 1 3 10 1 1 3 10 1 3 3 3 3 3;
	setAttr -s 31 ".kix[6:30]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1 1 1 1 1;
	setAttr -s 31 ".kiy[6:30]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0 0 0 0 0;
	setAttr -s 31 ".kox[6:30]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1 1 1 1 1;
	setAttr -s 31 ".koy[6:30]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveTooth1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 31 ".ktv[0:30]"  0 1 7 1 10 1 16 1 25 1 35 1 38 1 45 1 46 
		1 52 1 54 1 57 1 58 1 63 1 65 1 68 1 70 1 74 1 75 1 78 1 80 1 84 1 85 1 88 1 89 1 
		93 1 99 1 106 1 110 1 116 1 126 1;
	setAttr -s 31 ".kit[6:30]"  1 3 10 3 1 3 10 3 
		1 3 10 3 1 3 10 3 1 3 10 1 3 3 3 3 3;
	setAttr -s 31 ".kot[6:30]"  1 3 10 1 1 3 10 1 
		1 3 10 1 1 3 10 1 1 3 10 1 3 3 3 3 3;
	setAttr -s 31 ".kix[6:30]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1 1 1 1 1;
	setAttr -s 31 ".kiy[6:30]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0 0 0 0 0;
	setAttr -s 31 ".kox[6:30]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1 1 1 1 1;
	setAttr -s 31 ".koy[6:30]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveTooth1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 31 ".ktv[0:30]"  0 1 7 1 10 1 16 1 25 1 35 1 38 1 45 1 46 
		1 52 1 54 1 57 1 58 1 63 1 65 1 68 1 70 1 74 1 75 1 78 1 80 1 84 1 85 1 88 1 89 1 
		93 1 99 1 106 1 110 1 116 1 126 1;
	setAttr -s 31 ".kit[6:30]"  1 3 10 3 1 3 10 3 
		1 3 10 3 1 3 10 3 1 3 10 1 3 3 3 3 3;
	setAttr -s 31 ".kot[6:30]"  1 3 10 1 1 3 10 1 
		1 3 10 1 1 3 10 1 1 3 10 1 3 3 3 3 3;
	setAttr -s 31 ".kix[6:30]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1 1 1 1 1;
	setAttr -s 31 ".kiy[6:30]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0 0 0 0 0;
	setAttr -s 31 ".kox[6:30]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1 1 1 1 1;
	setAttr -s 31 ".koy[6:30]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveTooth1_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 56 ".ktv[0:55]"  0 -27.541549434058677 7 -107.60327246252713 
		10 -27.541549434058677 16 -30.421532560260061 25 -75.353799945162649 34 -8.5199716510823862 
		35 -19.053093886733475 38 -9.6571844688279427 39 -25.202656144620764 43 -81.159174888832666 
		45 -5.3914802346953312 46 -20.182563058428173 47 -22.125192708633577 48 -45.981786549728454 
		52 -19.053093886733475 54 -9.6571844688279427 55 -25.202656144620764 56 -81.159174888832666 
		57 -5.3914802346953312 58 -20.182563058428173 59 -22.125192708633577 60 -45.981786549728454 
		63 -19.053093886733475 65 -9.6571844688279427 66 -25.202656144620764 67 -81.159174888832666 
		68 -5.3914802346953312 70 -20.182563058428173 71 -22.125192708633577 72 -45.981786549728454 
		74 -19.053093886733475 75 -9.6571844688279427 76 -25.202656144620764 77 -81.159174888832666 
		78 -5.3914802346953312 80 -20.182563058428173 81 -22.125192708633577 82 -45.981786549728454 
		84 -19.053093886733475 85 -9.6571844688279427 86 -25.202656144620764 87 -81.159174888832666 
		88 -5.3914802346953312 89 -20.182563058428173 90 -22.125192708633577 91 -45.981786549728454 
		93 -19.053093886733475 96 -9.8678865990586644 99 -22.476111758624132 102 -12.820248203824882 
		106 -8.0116405436435958 110 -27.567711685898111 116 -33.246302558041315 120 -19.075623089654346 
		123 -26.336102911610102 126 -27.541549434058677;
	setAttr -s 56 ".kit[0:55]"  3 3 3 3 3 10 3 1 
		10 10 3 10 10 10 3 1 10 10 3 10 10 10 3 1 10 
		10 3 10 10 10 3 1 10 10 3 10 10 10 3 1 10 10 
		3 10 10 10 1 10 3 10 3 3 3 10 10 3;
	setAttr -s 56 ".kot[0:55]"  3 3 3 3 3 10 3 1 
		10 10 3 10 10 10 1 1 10 10 3 10 10 10 1 1 10 
		10 3 10 10 10 1 1 10 10 3 10 10 10 1 1 10 10 
		3 10 10 10 1 10 3 10 3 3 3 10 10 3;
	setAttr -s 56 ".kix[7:55]"  1 0.1323775053024292 0.50069361925125122 
		1 1 1 0.95195060968399048 1 1 0.053345128893852234 0.18931928277015686 1 1 1 0.92779135704040527 
		1 1 0.053345039486885071 0.18931928277015686 1 1 1 0.88130849599838257 1 1 0.053345039486885071 
		0.18931928277015686 1 1 1 0.88130801916122437 1 1 0.053345229476690292 0.18931993842124939 
		1 1 1 0.88130801916122437 1 0.95816457271575928 1 0.67875134944915771 1 1 1 0.88834798336029053 
		1 1;
	setAttr -s 56 ".kiy[7:55]"  0 -0.99119937419891357 0.86562460660934448 
		0 0 0 0.30625158548355103 0 0 -0.99857616424560547 0.98191559314727783 0 0 0 0.37309941649436951 
		0 0 -0.99857616424560547 0.98191559314727783 0 0 0 0.47254142165184021 0 0 -0.99857616424560547 
		0.98191559314727783 0 0 0 0.47254228591918945 0 0 -0.99857616424560547 0.98191541433334351 
		0 0 0 0.47254228591918945 0 -0.28621771931648254 0 0.73436814546585083 0 0 0 0.45917081832885742 
		0 0;
	setAttr -s 56 ".kox[7:55]"  1 0.1323775053024292 0.50069361925125122 
		1 1 1 0.95195060968399048 1 1 0.053345128893852234 0.18931928277015686 1 1 1 0.92779135704040527 
		1 1 0.053345039486885071 0.18931928277015686 1 1 1 0.88130849599838257 1 1 0.053345039486885071 
		0.18931928277015686 1 1 1 0.88130801916122437 1 1 0.053345229476690292 0.18931993842124939 
		1 1 1 0.88130801916122437 1 0.95816457271575928 1 0.67875134944915771 1 1 1 0.88834798336029053 
		1 1;
	setAttr -s 56 ".koy[7:55]"  0 -0.99119937419891357 0.86562460660934448 
		0 0 0 0.30625158548355103 0 0 -0.99857616424560547 0.98191559314727783 0 0 0 0.37309941649436951 
		0 0 -0.99857616424560547 0.98191559314727783 0 0 0 0.47254142165184021 0 0 -0.99857616424560547 
		0.98191559314727783 0 0 0 0.47254228591918945 0 0 -0.99857616424560547 0.98191541433334351 
		0 0 0 0.47254228591918945 0 -0.28621771931648254 0 0.73436814546585083 0 0 0 0.45917081832885742 
		0 0;
createNode animCurveTA -n "char_FKCurveTooth1_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 56 ".ktv[0:55]"  0 8.4599709196312922 7 26.408015534089245 
		10 8.4599709196312922 16 -15.460272802157778 25 32.923410317627628 34 3.785788774718343 
		35 39.63519601911355 38 17.560953257188686 39 -29.125904434326962 43 -59.650485615158217 
		45 -33.623777612431816 46 -2.4055619762400124 47 21.914607582075575 48 57.524580930313007 
		52 39.63519601911355 54 17.560953257188686 55 -29.125904434326962 56 -59.650485615158217 
		57 -33.623777612431816 58 -2.4055619762400124 59 21.914607582075575 60 57.524580930313007 
		63 39.63519601911355 65 17.560953257188686 66 -29.125904434326962 67 -59.650485615158217 
		68 -33.623777612431816 70 -2.4055619762400124 71 21.914607582075575 72 57.524580930313007 
		74 39.63519601911355 75 17.560953257188686 76 -29.125904434326962 77 -59.650485615158217 
		78 -33.623777612431816 80 -2.4055619762400124 81 21.914607582075575 82 57.524580930313007 
		84 39.63519601911355 85 17.560953257188686 86 -29.125904434326962 87 -59.650485615158217 
		88 -33.623777612431816 89 -2.4055619762400124 90 21.914607582075575 91 57.524580930313007 
		93 39.63519601911355 96 -30.431739316318264 99 -13.553922270485335 102 20.803394440429575 
		106 -29.923230500937123 110 21.99552584951379 116 -34.724550005022792 120 25.525155183124955 
		123 -3.2523644719799205 126 8.4599709196312922;
	setAttr -s 56 ".kit[0:55]"  3 3 3 3 3 10 3 1 
		10 10 3 10 10 10 3 1 10 10 3 10 10 10 3 1 10 
		10 3 10 10 10 3 1 10 10 3 10 10 10 3 1 10 10 
		3 10 10 10 1 10 3 10 3 3 3 10 10 3;
	setAttr -s 56 ".kot[0:55]"  3 3 3 3 3 10 3 1 
		10 10 3 10 10 10 1 1 10 10 3 10 10 10 1 1 10 
		10 3 10 10 10 1 1 10 10 3 10 10 10 1 1 10 10 
		3 10 10 10 1 10 3 10 3 3 3 10 10 3;
	setAttr -s 56 ".kix[7:55]"  1 0.12274201959371567 0.93086034059524536 
		1 0.068614162504673004 0.063607171177864075 0.4743863046169281 1 1 0.049410503357648849 
		0.64730626344680786 1 0.068614162504673004 0.063607171177864075 0.39588379859924316 
		1 1 0.049410417675971985 0.64730626344680786 1 0.10261955112218857 0.063607290387153625 
		0.30764797329902649 1 1 0.049410417675971985 0.64730626344680786 1 0.10261978954076767 
		0.063607059419155121 0.30764731764793396 1 1 0.049410592764616013 0.6473076343536377 
		1 0.068614035844802856 0.063607059419155121 0.30764731764793396 1 0.21060949563980103 
		1 0.63255584239959717 1 1 1 0.39097559452056885 0.55747079849243164 1;
	setAttr -s 56 ".kiy[7:55]"  0 -0.99243855476379395 -0.36537516117095947 
		0 0.99764329195022583 0.99797505140304565 0.88031679391860962 0 0 -0.99877852201461792 
		-0.7622300386428833 0 0.99764329195022583 0.99797505140304565 0.91830068826675415 
		0 0 -0.99877852201461792 -0.7622300386428833 0 0.99472063779830933 0.99797505140304565 
		0.95150023698806763 0 0 -0.99877852201461792 -0.7622300386428833 0 0.99472063779830933 
		0.99797505140304565 0.95150047540664673 0 0 -0.99877852201461792 -0.76222890615463257 
		0 0.99764329195022583 0.99797505140304565 0.95150047540664673 0 -0.97757023572921753 
		0 -0.77451479434967041 0 0 0 0.92040103673934937 -0.83019649982452393 0;
	setAttr -s 56 ".kox[7:55]"  1 0.12274201959371567 0.93086034059524536 
		1 0.068614162504673004 0.063607171177864075 0.4743863046169281 1 1 0.049410503357648849 
		0.64730626344680786 1 0.068614162504673004 0.063607171177864075 0.39588379859924316 
		1 1 0.049410417675971985 0.64730626344680786 1 0.10261955112218857 0.063607290387153625 
		0.30764797329902649 1 1 0.049410417675971985 0.64730626344680786 1 0.10261978954076767 
		0.063607059419155121 0.30764731764793396 1 1 0.049410592764616013 0.6473076343536377 
		1 0.068614035844802856 0.063607059419155121 0.30764731764793396 1 0.21060949563980103 
		1 0.63255584239959717 1 1 1 0.39097559452056885 0.55747079849243164 1;
	setAttr -s 56 ".koy[7:55]"  0 -0.99243855476379395 -0.36537516117095947 
		0 0.99764329195022583 0.99797505140304565 0.88031679391860962 0 0 -0.99877852201461792 
		-0.7622300386428833 0 0.99764329195022583 0.99797505140304565 0.91830068826675415 
		0 0 -0.99877852201461792 -0.7622300386428833 0 0.99472063779830933 0.99797505140304565 
		0.95150023698806763 0 0 -0.99877852201461792 -0.7622300386428833 0 0.99472063779830933 
		0.99797505140304565 0.95150047540664673 0 0 -0.99877852201461792 -0.76222890615463257 
		0 0.99764329195022583 0.99797505140304565 0.95150047540664673 0 -0.97757023572921753 
		0 -0.77451479434967041 0 0 0 0.92040103673934937 -0.83019649982452393 0;
createNode animCurveTA -n "char_FKCurveTooth1_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 56 ".ktv[0:55]"  0 6.8137435045968227 7 -9.4145107664346455 
		10 6.8137435045968227 16 6.9935090643884079 25 -28.622388527976394 34 20.761996925435156 
		35 38.192814596158044 38 7.8033474457007932 39 -4.3052984147130928 43 7.291565310351535 
		45 -46.323729953834793 46 -0.34138492013648553 47 10.116339978015898 48 6.2985595675180637 
		52 38.192814596158044 54 7.8033474457007932 55 -4.3052984147130928 56 7.291565310351535 
		57 -46.323729953834793 58 -0.34138492013648553 59 10.116339978015898 60 6.2985595675180637 
		63 38.192814596158044 65 7.8033474457007932 66 -4.3052984147130928 67 7.291565310351535 
		68 -46.323729953834793 70 -0.34138492013648553 71 10.116339978015898 72 6.2985595675180637 
		74 38.192814596158044 75 7.8033474457007932 76 -4.3052984147130928 77 7.291565310351535 
		78 -46.323729953834793 80 -0.34138492013648553 81 10.116339978015898 82 6.2985595675180637 
		84 38.192814596158044 85 7.8033474457007932 86 -4.3052984147130928 87 7.291565310351535 
		88 -46.323729953834793 89 -0.34138492013648553 90 10.116339978015898 91 6.2985595675180637 
		93 38.192814596158044 96 -5.5254470647297707 99 1.2444102310599305 102 20.112438283198809 
		106 -14.764071226577123 110 12.246431889573769 116 8.2087661246027945 120 8.0058289073591613 
		123 12.081569591479838 126 6.8137435045968227;
	setAttr -s 56 ".kit[0:55]"  3 3 3 3 3 10 3 1 
		10 10 3 10 10 10 3 1 10 10 3 10 10 10 3 1 10 
		10 3 10 10 10 3 1 10 10 3 10 10 10 3 1 10 10 
		3 10 10 10 1 10 3 10 3 3 3 10 10 3;
	setAttr -s 56 ".kot[0:55]"  3 3 3 3 3 10 3 1 
		10 10 3 10 10 10 1 1 10 10 3 10 10 10 1 1 10 
		10 3 10 10 10 1 1 10 10 3 10 10 10 1 1 10 10 
		3 10 10 10 1 10 3 10 3 3 3 10 10 3;
	setAttr -s 56 ".kix[7:55]"  1 0.99856704473495483 0.26310855150222778 
		1 0.067523017525672913 0.49864321947097778 0.32200226187705994 1 1 0.99114322662353516 
		0.090532399713993073 1 0.067523017525672913 0.49864321947097778 0.26254826784133911 
		1 1 0.99114310741424561 0.090532399713993073 1 0.1009969636797905 0.49864387512207031 
		0.19994974136352539 1 1 0.99114310741424561 0.090532399713993073 1 0.1009972020983696 
		0.49864250421524048 0.19994927942752838 1 1 0.99114322662353516 0.09053272008895874 
		1 0.067522905766963959 0.49864250421524048 0.19994927942752838 1 0.29622030258178711 
		1 0.64099371433258057 1 1 1 1 0.99463248252868652 1;
	setAttr -s 56 ".kiy[7:55]"  0 -0.053516913205385208 -0.96476620435714722 
		0 0.99771773815155029 0.86680740118026733 0.94673889875411987 0 0 -0.13279746472835541 
		-0.99589347839355469 0 0.99771773815155029 0.86680740118026733 0.96491885185241699 
		0 0 -0.13279768824577332 -0.99589347839355469 0 0.99488675594329834 0.86680698394775391 
		0.97980618476867676 0 0 -0.13279768824577332 -0.99589347839355469 0 0.99488675594329834 
		0.86680769920349121 0.97980618476867676 0 0 -0.13279722630977631 -0.99589347839355469 
		0 0.99771773815155029 0.86680769920349121 0.97980618476867676 0 -0.95511960983276367 
		0 -0.76754611730575562 0 0 0 0 -0.10347080230712891 0;
	setAttr -s 56 ".kox[7:55]"  1 0.99856704473495483 0.26310855150222778 
		1 0.067523017525672913 0.49864321947097778 0.32200226187705994 1 1 0.99114322662353516 
		0.090532399713993073 1 0.067523017525672913 0.49864321947097778 0.26254826784133911 
		1 1 0.99114310741424561 0.090532399713993073 1 0.1009969636797905 0.49864387512207031 
		0.19994974136352539 1 1 0.99114310741424561 0.090532399713993073 1 0.1009972020983696 
		0.49864250421524048 0.19994927942752838 1 1 0.99114322662353516 0.09053272008895874 
		1 0.067522905766963959 0.49864250421524048 0.19994927942752838 1 0.29622030258178711 
		1 0.64099371433258057 1 1 1 1 0.99463248252868652 1;
	setAttr -s 56 ".koy[7:55]"  0 -0.053516913205385208 -0.96476620435714722 
		0 0.99771773815155029 0.86680740118026733 0.94673889875411987 0 0 -0.13279746472835541 
		-0.99589347839355469 0 0.99771773815155029 0.86680740118026733 0.96491885185241699 
		0 0 -0.13279768824577332 -0.99589347839355469 0 0.99488675594329834 0.86680698394775391 
		0.97980618476867676 0 0 -0.13279768824577332 -0.99589347839355469 0 0.99488675594329834 
		0.86680769920349121 0.97980618476867676 0 0 -0.13279722630977631 -0.99589347839355469 
		0 0.99771773815155029 0.86680769920349121 0.97980618476867676 0 -0.95511960983276367 
		0 -0.76754611730575562 0 0 0 0 -0.10347080230712891 0;
createNode animCurveTL -n "char_FKCurveTooth1_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 51 ".ktv[0:50]"  0 -0.028863465787140358 7 -0.076013398987461872 
		10 -0.028863465787140358 16 0.027819834689015541 25 -0.11754574554176142 34 -0.047277059221025514 
		35 -0.090622219512180552 38 -0.03842417075787892 39 0.050095497037539689 43 0.13931071591298991 
		45 0.19444126567247125 46 0.05597177477406369 48 -0.090996942979303483 52 -0.090622219512180552 
		54 -0.03842417075787892 55 0.050095497037539689 56 0.13931071591298991 57 0.19444126567247125 
		58 0.05597177477406369 60 -0.090996942979303483 63 -0.090622219512180552 65 -0.03842417075787892 
		66 0.050095497037539689 67 0.13931071591298991 68 0.19444126567247125 70 0.05597177477406369 
		72 -0.090996942979303483 74 -0.090622219512180552 75 -0.03842417075787892 76 0.050095497037539689 
		77 0.13931071591298991 78 0.19444126567247125 80 0.05597177477406369 82 -0.090996942979303483 
		84 -0.090622219512180552 85 -0.03842417075787892 86 0.050095497037539689 87 0.13931071591298991 
		88 0.19444126567247125 89 0.05597177477406369 91 -0.090996942979303483 93 -0.090622219512180552 
		96 0.018065422744830036 99 -0.035414157384356493 102 -0.050944733957012905 106 -0.028863465787140358 
		110 -0.039279157500191487 116 0.0049186531755790568 120 -0.083141254360197647 123 
		-0.048919749740547913 126 -0.028863465787140358;
	setAttr -s 51 ".kit[0:50]"  3 3 3 3 3 10 3 1 
		10 10 3 10 10 3 1 10 10 3 10 10 3 1 10 10 3 
		10 10 3 1 10 10 3 10 10 3 1 10 10 3 10 10 1 
		10 3 10 3 3 3 10 10 3;
	setAttr -s 51 ".kot[0:50]"  3 3 3 3 3 10 3 1 
		10 10 3 10 10 1 1 10 10 3 10 10 1 1 10 10 3 
		10 10 1 1 10 10 3 10 10 1 1 10 10 3 10 10 1 
		10 3 10 3 3 3 10 10 3;
	setAttr -s 51 ".kix[7:50]"  1 0.68402886390686035 0.81086909770965576 
		1 0.33063510060310364 1 1 1 0.35119795799255371 0.41929396986961365 1 0.33063510060310364 
		1 1 1 0.35119745135307312 0.41929396986961365 1 0.42322152853012085 1 1 1 0.35119745135307312 
		0.41929396986961365 1 0.42322152853012085 1 1 1 0.35119852423667908 0.41929522156715393 
		1 0.33063474297523499 1 1 0.96394854784011841 1 1 1 1 1 1 1 1;
	setAttr -s 51 ".kiy[7:50]"  0 0.72945493459701538 0.58522748947143555 
		0 -0.94375866651535034 0 0 0 0.93630123138427734 0.90785050392150879 0 -0.94375866651535034 
		0 0 0 0.93630146980285645 0.90785050392150879 0 -0.90602618455886841 0 0 0 0.93630146980285645 
		0.90785050392150879 0 -0.90602618455886841 0 0 0 0.93630099296569824 0.90785002708435059 
		0 -0.94375878572463989 0 0 0.26608860492706299 0 0 0 0 0 0 0 0;
	setAttr -s 51 ".kox[7:50]"  1 0.68402886390686035 0.81086909770965576 
		1 0.33063510060310364 1 1 1 0.35119795799255371 0.41929396986961365 1 0.33063510060310364 
		1 1 1 0.35119745135307312 0.41929396986961365 1 0.42322152853012085 1 1 1 0.35119745135307312 
		0.41929396986961365 1 0.42322152853012085 1 1 1 0.35119852423667908 0.41929522156715393 
		1 0.33063474297523499 1 1 0.96394854784011841 1 1 1 1 1 1 1 1;
	setAttr -s 51 ".koy[7:50]"  0 0.72945493459701538 0.58522748947143555 
		0 -0.94375866651535034 0 0 0 0.93630123138427734 0.90785050392150879 0 -0.94375866651535034 
		0 0 0 0.93630146980285645 0.90785050392150879 0 -0.90602618455886841 0 0 0 0.93630146980285645 
		0.90785050392150879 0 -0.90602618455886841 0 0 0 0.93630099296569824 0.90785002708435059 
		0 -0.94375878572463989 0 0 0.26608860492706299 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKCurveTooth1_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 51 ".ktv[0:50]"  0 -0.023775464972591611 7 0.0053412024440567364 
		10 -0.023775464972591611 16 -0.059108465380110879 25 -0.028801883975215346 34 0.0085587391206734878 
		35 0.032155741278968315 38 0.0022407696860835399 39 -0.0097927684625716115 43 -0.0060347883243116835 
		45 0.041476172572576867 46 0.040768135110030121 48 0.059359660909356668 52 0.032155741278968315 
		54 0.0022407696860835399 55 -0.0097927684625716115 56 -0.0060347883243116835 57 0.041476172572576867 
		58 0.040768135110030121 60 0.059359660909356668 63 0.032155741278968315 65 0.0022407696860835399 
		66 -0.0097927684625716115 67 -0.0060347883243116835 68 0.041476172572576867 70 0.040768135110030121 
		72 0.059359660909356668 74 0.032155741278968315 75 0.0022407696860835399 76 -0.0097927684625716115 
		77 -0.0060347883243116835 78 0.041476172572576867 80 0.040768135110030121 82 0.059359660909356668 
		84 0.032155741278968315 85 0.0022407696860835399 86 -0.0097927684625716115 87 -0.0060347883243116835 
		88 0.041476172572576867 89 0.040768135110030121 91 0.059359660909356668 93 0.032155741278968315 
		96 -0.017928595613778863 99 -0.010873066647116469 102 -0.027978358441857313 106 -0.023775464972591611 
		110 0.0048134402506077884 116 -0.051326935041923615 120 -0.024702228739086347 123 
		-0.039480073188666726 126 -0.023775464972591611;
	setAttr -s 51 ".kit[0:50]"  3 3 3 3 3 10 3 1 
		10 10 3 10 10 3 1 10 10 3 10 10 3 1 10 10 3 
		10 10 3 1 10 10 3 10 10 3 1 10 10 3 10 10 1 
		10 3 10 3 3 3 10 10 3;
	setAttr -s 51 ".kot[0:50]"  3 3 3 3 3 10 3 1 
		10 10 3 10 10 1 1 10 10 3 10 10 1 1 10 10 3 
		10 10 1 1 10 10 3 10 10 1 1 10 10 3 10 10 1 
		10 3 10 3 3 3 10 10 3;
	setAttr -s 51 ".kix[7:50]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 51 ".kiy[7:50]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 51 ".kox[7:50]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 51 ".koy[7:50]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKCurveTooth1_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 51 ".ktv[0:50]"  0 -0.052162964274260919 7 -0.15254356393080748 
		10 -0.052162964274260919 16 -0.038648287204098443 25 -0.14799718169308829 34 -0.053829532022344313 
		35 -0.088310722733806371 38 -0.062484026982277285 39 -0.079998571851561298 43 -0.14814002276563823 
		45 -0.10674154951437151 46 -0.085548291597297002 48 -0.12974154454779127 52 -0.088310722733806371 
		54 -0.062484026982277285 55 -0.079998571851561298 56 -0.14814002276563823 57 -0.10674154951437151 
		58 -0.085548291597297002 60 -0.12974154454779127 63 -0.088310722733806371 65 -0.062484026982277285 
		66 -0.079998571851561298 67 -0.14814002276563823 68 -0.10674154951437151 70 -0.085548291597297002 
		72 -0.12974154454779127 74 -0.088310722733806371 75 -0.062484026982277285 76 -0.079998571851561298 
		77 -0.14814002276563823 78 -0.10674154951437151 80 -0.085548291597297002 82 -0.12974154454779127 
		84 -0.088310722733806371 85 -0.062484026982277285 86 -0.079998571851561298 87 -0.14814002276563823 
		88 -0.10674154951437151 89 -0.085548291597297002 91 -0.12974154454779127 93 -0.088310722733806371 
		96 -0.052514332946551209 99 -0.010033828937464066 102 -0.041114549236746498 106 -0.052162964274260919 
		110 -0.122372939651537 116 -0.0773976510501313 120 -0.043504351291440972 123 -0.069237561167806605 
		126 -0.052162964274260919;
	setAttr -s 51 ".kit[0:50]"  3 3 3 3 3 10 3 1 
		10 10 3 10 10 3 1 10 10 3 10 10 3 1 10 10 3 
		10 10 3 1 10 10 3 10 10 3 1 10 10 3 10 10 1 
		10 3 10 3 3 3 10 10 3;
	setAttr -s 51 ".kot[0:50]"  3 3 3 3 3 10 3 1 
		10 10 3 10 10 1 1 10 10 3 10 10 1 1 10 10 3 
		10 10 1 1 10 10 3 10 10 1 1 10 10 3 10 10 1 
		10 3 10 3 3 3 10 10 3;
	setAttr -s 51 ".kix[7:50]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 51 ".kiy[7:50]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 51 ".kox[7:50]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 51 ".koy[7:50]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKExtraTooth1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKExtraTooth1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKExtraTooth1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraTooth1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraTooth1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraTooth1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKExtraTooth1_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKExtraTooth1_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKExtraTooth1_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "FKCurveR_Shoulder1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 28 ".ktv[0:27]"  0 -36.986337964869008 7 1.3914936086559155 
		10 1.3914936086559155 15 -9.1917841058549694 20 -38.3270104901369 25 -46.841522471435589 
		35 -14.346831408719112 38 20.105732822471879 49 -28.838631781631911 56 -76.872715262986048 
		57 -76.872715262986048 63 -33.983761764019036 66 -76.872715262986048 68 -76.872715262986048 
		74 -33.983761764019036 77 -76.872715262986048 78 -76.872715262986048 84 -33.983761764019036 
		86 -76.872715262986048 88 -76.872715262986048 93 -33.983761764019036 97 -70.081209800376612 
		101 -36.092492739492684 106 -20.146448897251041 110 -27.064268108950795 114 -51.782850723821085 
		118 -33.603460813289068 126 -36.986337964869008;
	setAttr -s 28 ".kit[3:27]"  10 10 3 10 10 3 1 3 
		3 1 3 3 1 3 3 1 3 1 10 3 10 10 10 10 3;
	setAttr -s 28 ".kot[3:27]"  10 10 3 10 10 1 1 3 
		1 1 3 1 1 3 1 1 3 1 10 3 10 10 10 10 3;
	setAttr -s 28 ".kix[9:27]"  1 1 1 1 1 1 1 1 1 1 1 1 0.99060970544815063 
		1 0.88531029224395752 0.4348905086517334 0.91933870315551758 0.84012109041213989 
		1;
	setAttr -s 28 ".kiy[9:27]"  0 0 0 0 0 0 0 0 0 0 0 0 -0.13672012090682983 
		0 0.46500080823898315 -0.90048336982727051 -0.3934670090675354 0.54239886999130249 
		0;
	setAttr -s 28 ".kox[8:27]"  1 1 1 1 1 1 1 1 1 1 1 1 1 0.99060970544815063 
		1 0.88531029224395752 0.4348905086517334 0.91933870315551758 0.84012109041213989 
		1;
	setAttr -s 28 ".koy[8:27]"  0 0 0 0 0 0 0 0 0 0 0 0 0 -0.13672012090682983 
		0 0.46500080823898315 -0.90048336982727051 -0.3934670090675354 0.54239886999130249 
		0;
createNode animCurveTA -n "FKCurveR_Shoulder1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 28 ".ktv[0:27]"  0 15.957960813366103 7 23.076862560812017 
		10 23.076862560812017 15 8.4819002641473062 20 9.5669347361030077 25 -5.3421603644764968 
		35 -26.387886917752034 38 -15.274581595504417 49 47.930785268179314 56 -65.021626858534859 
		57 -65.021626858534859 63 38.244431784199804 66 -65.021626858534859 68 -65.021626858534859 
		74 38.244431784199804 77 -65.021626858534859 78 -65.021626858534859 84 38.244431784199804 
		86 -65.021626858534859 88 -65.021626858534859 93 38.244431784199804 97 6.3156500792269723 
		101 -30.264148452353623 106 -49.110461387344714 110 -56.973682782159905 114 1.4771384487136769 
		118 15.214121265807844 126 15.957960813366103;
	setAttr -s 28 ".kit[3:27]"  10 10 3 10 10 3 1 3 
		3 1 3 3 1 3 3 1 3 1 10 3 10 10 10 10 3;
	setAttr -s 28 ".kot[3:27]"  10 10 3 10 10 1 1 3 
		1 1 3 1 1 3 1 1 3 1 10 3 10 10 10 10 3;
	setAttr -s 28 ".kix[9:27]"  1 1 1 1 1 1 1 1 1 1 1 1 0.21767362952232361 
		1 0.54116582870483398 0.28912854194641113 0.20706726610660553 1 1;
	setAttr -s 28 ".kiy[9:27]"  0 0 0 0 0 0 0 0 0 0 0 0 -0.97602164745330811 
		0 -0.84091585874557495 0.95729029178619385 0.97832673788070679 0 0;
	setAttr -s 28 ".kox[8:27]"  1 1 1 1 1 1 1 1 1 1 1 1 1 0.21767362952232361 
		1 0.54116582870483398 0.28912854194641113 0.20706726610660553 1 1;
	setAttr -s 28 ".koy[8:27]"  0 0 0 0 0 0 0 0 0 0 0 0 0 -0.97602164745330811 
		0 -0.84091585874557495 0.95729029178619385 0.97832673788070679 0 0;
createNode animCurveTA -n "FKCurveR_Shoulder1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 28 ".ktv[0:27]"  0 -60.970082317325229 8 -59.375022124963628 
		12 -60.970082317325229 15 -123.73081911547276 18 -13.268060862152515 23 -16.343888915861886 
		29 -52.58667660854919 34 -11.350003803602027 39 -5.6232499505075735 49 -41.753079067250013 
		57 -11.56157740029666 60 -41.753079067250013 63 -41.753079067250013 68 -11.56157740029666 
		72 -41.753079067250013 74 -41.753079067250013 78 -11.56157740029666 82 -41.753079067250013 
		84 -41.753079067250013 88 -11.56157740029666 91 -41.753079067250013 93 -41.753079067250013 
		96 18.551979259553395 101 -2.8420514908082488 104 -2.3157892317719897 111 -76.729802766952773 
		118 -64.722546989938365 126 -60.970082317325229;
	setAttr -s 28 ".kit[1:27]"  10 3 10 3 3 10 10 10 
		1 3 1 3 3 1 3 3 1 3 3 1 1 10 3 3 3 
		10 3;
	setAttr -s 28 ".kot[1:27]"  10 3 10 3 3 10 10 10 
		1 3 1 1 3 1 1 3 1 1 3 1 1 10 3 3 3 
		10 3;
	setAttr -s 28 ".kix[9:27]"  1 1 1 1 1 1 1 1 1 1 1 1 1 0.36549484729766846 
		1 1 1 0.87617212533950806 1;
	setAttr -s 28 ".kiy[9:27]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0.93081337213516235 
		0 0 0 0.48199829459190369 0;
	setAttr -s 28 ".kox[9:27]"  1 1 1 1 1 1 1 1 1 1 1 1 1 0.36549484729766846 
		1 1 1 0.87617212533950806 1;
	setAttr -s 28 ".koy[9:27]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0.93081337213516235 
		0 0 0 0.48199829459190369 0;
createNode animCurveTA -n "FKCurveR_Shoulder1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 28 ".ktv[0:27]"  0 -5.1174438057844904 8 12.772509170308291 
		12 -5.1174438057844904 15 -67.624255267361917 18 64.104407963728974 23 60.678340721906444 
		29 65.092312231532148 34 -51.984503196544026 39 29.973866570644102 49 -52.855381390900064 
		57 25.228929040795581 60 -52.855381390900064 63 -52.855381390900064 68 25.228929040795581 
		72 -52.855381390900064 74 -52.855381390900064 78 25.228929040795581 82 -52.855381390900064 
		84 -52.855381390900064 88 25.228929040795581 91 -52.855381390900064 93 -52.855381390900064 
		96 -61.93392890103469 101 48.891506891617155 104 62.395998188834369 111 -11.327401385506557 
		118 -10.078551421816123 126 -5.1174438057844904;
	setAttr -s 28 ".kit[1:27]"  10 3 10 3 3 10 10 10 
		1 3 1 3 3 1 3 3 1 3 3 1 1 10 3 3 3 
		10 3;
	setAttr -s 28 ".kot[1:27]"  10 3 10 3 3 10 10 10 
		1 3 1 1 3 1 1 3 1 1 3 1 1 10 3 3 3 
		10 3;
	setAttr -s 28 ".kix[9:27]"  1 1 1 1 1 1 1 1 1 1 1 1 1 0.14850053191184998 
		1 1 1 1 1;
	setAttr -s 28 ".kiy[9:27]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0.98891234397888184 
		0 0 0 0 0;
	setAttr -s 28 ".kox[9:27]"  1 1 1 1 1 1 1 1 1 1 1 1 1 0.14850053191184998 
		1 1 1 1 1;
	setAttr -s 28 ".koy[9:27]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0.98891234397888184 
		0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraPen1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraPen1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraPen1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraPen1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraPen1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraPen1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveHair1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 1 7 1 10 1 14 1 25 1 32 1 35 1 52 1 57 
		1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 21 ".kit[3:20]"  10 3 3 1 1 10 1 10 
		1 10 1 10 1 3 3 3 3 3;
	setAttr -s 21 ".kot[3:20]"  10 3 3 1 1 10 1 10 
		1 10 1 10 1 3 3 3 3 3;
	setAttr -s 21 ".kix[6:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".kiy[6:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 21 ".kox[6:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".koy[6:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveHair1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 1 7 1 10 1 14 1 25 1 32 1 35 1 52 1 57 
		1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 21 ".kit[3:20]"  10 3 3 1 1 10 1 10 
		1 10 1 10 1 3 3 3 3 3;
	setAttr -s 21 ".kot[3:20]"  10 3 3 1 1 10 1 10 
		1 10 1 10 1 3 3 3 3 3;
	setAttr -s 21 ".kix[6:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".kiy[6:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 21 ".kox[6:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".koy[6:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveHair1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 1 7 1 10 1 14 1 25 1 32 1 35 1 52 1 57 
		1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 21 ".kit[3:20]"  10 3 3 1 1 10 1 10 
		1 10 1 10 1 3 3 3 3 3;
	setAttr -s 21 ".kot[3:20]"  10 3 3 1 1 10 1 10 
		1 10 1 10 1 3 3 3 3 3;
	setAttr -s 21 ".kix[6:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".kiy[6:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 21 ".kox[6:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".koy[6:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveHair1_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 30.524599611915377 7 47.010280309452526 
		10 30.524599611915377 14 28.358501332984357 19 45.258407083438676 23 39.56489327175656 
		25 60.507493858584823 32 30.524599611915377 35 50.551842475098404 38 61.451056129286215 
		40 43.367295060919282 43 27.110356978534863 47 41.819428545393322 52 44.540864458872633 
		54 42.721686281268894 56 43.367295060919282 57 45.023915771539976 59 41.819428545393322 
		63 44.540864458872633 65 42.721686281268894 66 43.367295060919282 68 45.023915771539976 
		71 41.819428545393322 74 44.540864458872633 75 42.721686281268894 77 43.367295060919282 
		78 45.023915771539976 82 41.819428545393322 84 44.540864458872633 85 42.721686281268894 
		86 43.367295060919282 88 45.023915771539976 91 41.819428545393322 93 44.540864458872633 
		97 17.278591752325038 101 15.838116421867046 106 34.663871640006967 110 42.570102694296764 
		116 37.233300910641042 120 27.132031338492485 126 30.524599611915377;
	setAttr -s 41 ".kit[0:40]"  3 3 3 10 10 10 3 3 
		1 10 9 10 10 1 10 9 10 10 1 10 9 10 10 1 10 
		9 10 10 1 10 9 10 10 1 10 3 3 3 3 10 3;
	setAttr -s 41 ".kot[0:40]"  3 3 3 10 10 10 3 3 
		1 10 9 10 10 1 10 9 10 10 1 10 9 10 10 1 10 
		9 10 10 1 10 9 10 10 1 10 3 3 3 3 10 3;
	setAttr -s 41 ".kix[8:40]"  1 0.79909247159957886 0.26790982484817505 
		0.99336409568786621 1 1 1 0.92789489030838013 1 1 1 1 0.9278947114944458 1 1 1 1 
		0.9278947114944458 1 1 1 1 0.92789500951766968 1 1 1 1 1 1 1 1 0.9434850811958313 
		1;
	setAttr -s 41 ".kiy[8:40]"  0 -0.6012081503868103 -0.96344399452209473 
		-0.11501182615756989 0 0 0 0.37284186482429504 0 0 0 0 0.3728422224521637 0 0 0 0 
		0.3728422224521637 0 0 0 0 0.372841477394104 0 0 0 0 0 0 0 0 -0.33141505718231201 
		0;
	setAttr -s 41 ".kox[8:40]"  1 0.79909247159957886 0.26790982484817505 
		0.99336409568786621 1 1 1 0.92789489030838013 1 1 1 1 0.9278947114944458 1 1 1 1 
		0.9278947114944458 1 1 1 1 0.92789500951766968 1 1 1 1 1 1 1 1 0.9434850811958313 
		1;
	setAttr -s 41 ".koy[8:40]"  0 -0.6012081503868103 -0.96344399452209473 
		-0.11501182615756989 0 0 0 0.37284186482429504 0 0 0 0 0.3728422224521637 0 0 0 0 
		0.3728422224521637 0 0 0 0 0.372841477394104 0 0 0 0 0 0 0 0 -0.33141505718231201 
		0;
createNode animCurveTA -n "char_FKCurveHair1_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -20.226445302148342 7 -24.219747101915793 
		10 -20.226445302148342 14 -39.943193794762294 19 -16.785524823812938 23 -17.179181849734526 
		25 -19.018222973319947 32 -20.226445302148342 35 3.5943007833236158 38 18.645673033564794 
		40 12.409689517027578 43 9.4452030048391222 47 -7.2231555207523357 52 5.2196342974307992 
		54 15.064105822338917 56 12.409689517027578 57 9.670837164032152 59 -7.2231555207523357 
		63 5.2196342974307992 65 15.064105822338917 66 12.409689517027578 68 9.670837164032152 
		71 -7.2231555207523357 74 5.2196342974307992 75 15.064105822338917 77 12.409689517027578 
		78 9.670837164032152 82 -7.2231555207523357 84 5.2196342974307992 85 15.064105822338917 
		86 12.409689517027578 88 9.670837164032152 91 -7.2231555207523357 93 5.2196342974307992 
		97 -2.4332313707242204 101 -14.250274540295376 106 -42.089418871818872 110 -6.8634479038359082 
		116 -35.940408328394177 120 -27.525316243085516 126 -20.226445302148342;
	setAttr -s 41 ".kit[0:40]"  3 3 3 10 10 10 3 3 
		1 10 9 10 10 1 10 9 10 10 1 10 9 10 10 1 10 
		9 10 10 1 10 9 10 10 1 10 3 3 3 3 10 3;
	setAttr -s 41 ".kot[0:40]"  3 3 3 10 10 10 3 3 
		1 10 9 10 10 1 10 9 10 10 1 10 9 10 10 1 10 
		9 10 10 1 10 9 10 10 1 10 3 3 3 3 10 3;
	setAttr -s 41 ".kix[8:40]"  0.3583977222442627 0.73477852344512939 
		0.72013729810714722 0.56284773349761963 0.97108703851699829 0.33072575926780701 1 
		0.72815412282943726 1 0.93214565515518188 0.27811399102210999 1 0.72815370559692383 
		1 0.93214577436447144 0.24816077947616577 1 0.72815370559692383 1 0.93214577436447144 
		0.27880862355232239 1 0.72815454006195068 1 0.90636968612670898 0.3283933699131012 
		0.61734902858734131 1 1 1 1 0.77221357822418213 1;
	setAttr -s 41 ".kiy[8:40]"  0.93356889486312866 0.67830711603164673 
		-0.69383156299591064 -0.8265606164932251 -0.23872578144073486 0.94372689723968506 
		0 -0.68541347980499268 0 -0.36208346486091614 0.96054810285568237 0 -0.6854138970375061 
		0 -0.36208328604698181 0.96871882677078247 0 -0.6854138970375061 0 -0.36208328604698181 
		0.96034669876098633 0 -0.68541300296783447 0 -0.42248547077178955 0.94454103708267212 
		-0.78668946027755737 0 0 0 0 0.63536298274993896 0;
	setAttr -s 41 ".kox[8:40]"  0.35839781165122986 0.73477852344512939 
		0.72013729810714722 0.56284773349761963 0.97108703851699829 0.33072578907012939 1 
		0.72815412282943726 1 0.93214565515518188 0.27811405062675476 1 0.72815370559692383 
		1 0.93214577436447144 0.24816088378429413 1 0.72815370559692383 1 0.93214577436447144 
		0.27880871295928955 1 0.72815454006195068 1 0.90636968612670898 0.32839339971542358 
		0.61734902858734131 1 1 1 1 0.77221357822418213 1;
	setAttr -s 41 ".koy[8:40]"  0.93356895446777344 0.67830711603164673 
		-0.69383156299591064 -0.8265606164932251 -0.23872578144073486 0.94372689723968506 
		0 -0.68541347980499268 0 -0.36208346486091614 0.96054798364639282 0 -0.6854138970375061 
		0 -0.36208328604698181 0.96871882677078247 0 -0.6854138970375061 0 -0.36208328604698181 
		0.96034657955169678 0 -0.68541300296783447 0 -0.42248547077178955 0.94454103708267212 
		-0.78668946027755737 0 0 0 0 0.63536298274993896 0;
createNode animCurveTA -n "char_FKCurveHair1_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 17.701770262088139 7 11.425748592081741 
		10 17.701770262088139 14 -10.151493194975554 19 21.313571525109595 23 23.125395160657803 
		25 13.413738857865098 32 17.701770262088139 35 6.4998527135314399 38 -2.9453128050965427 
		40 -5.3248142719101228 43 -7.271078912482821 47 4.6769336448428716 52 -6.9089331149102264 
		54 -4.726320802186498 56 -5.3248142719101228 57 -5.5310213400801072 59 4.6769336448428716 
		63 -6.9089331149102264 65 -4.726320802186498 66 -5.3248142719101228 68 -5.5310213400801072 
		71 4.6769336448428716 74 -6.9089331149102264 75 -4.726320802186498 77 -5.3248142719101228 
		78 -5.5310213400801072 82 4.6769336448428716 84 -6.9089331149102264 85 -4.726320802186498 
		86 -5.3248142719101228 88 -5.5310213400801072 91 4.6769336448428716 93 -6.9089331149102264 
		97 4.3342204865661129 101 -3.3104852972023626 106 -11.472843276762926 110 5.403620072060491 
		116 -8.8084798297840123 120 27.972799575635033 126 17.701770262088139;
	setAttr -s 41 ".kit[0:40]"  3 3 3 10 10 10 3 3 
		1 10 9 10 10 1 10 9 10 10 1 10 9 10 10 1 10 
		9 10 10 1 10 9 10 10 1 10 3 3 3 3 10 3;
	setAttr -s 41 ".kot[0:40]"  3 3 3 10 10 10 3 3 
		1 10 9 10 10 1 10 9 10 10 1 10 9 10 10 1 10 
		9 10 10 1 10 9 10 10 1 10 3 3 3 3 10 3;
	setAttr -s 41 ".kix[8:40]"  1 1 0.91089838743209839 1 0.99977809190750122 
		1 1 0.9902808666229248 1 0.99284791946411133 1 1 0.9902808666229248 1 0.99284791946411133 
		1 1 0.9902808666229248 1 0.99284791946411133 1 1 0.99028098583221436 1 0.9897492527961731 
		1 0.97336858510971069 1 1 1 1 0.58453059196472168 1;
	setAttr -s 41 ".kiy[8:40]"  0 0 -0.4126308262348175 0 0.021064108237624168 
		0 0 -0.1390816867351532 0 -0.11938552558422089 0 0 -0.13908185064792633 0 -0.11938545107841492 
		0 0 -0.13908185064792633 0 -0.11938545107841492 0 0 -0.13908153772354126 0 -0.14281558990478516 
		0 0.22924569249153137 0 0 0 0 0.81137162446975708 0;
	setAttr -s 41 ".kox[8:40]"  1 1 0.91089838743209839 1 0.99977809190750122 
		1 1 0.9902808666229248 1 0.99284791946411133 1 1 0.9902808666229248 1 0.99284791946411133 
		1 1 0.9902808666229248 1 0.99284791946411133 1 1 0.99028098583221436 1 0.9897492527961731 
		1 0.97336858510971069 1 1 1 1 0.58453059196472168 1;
	setAttr -s 41 ".koy[8:40]"  0 0 -0.4126308262348175 0 0.021064108237624168 
		0 0 -0.1390816867351532 0 -0.11938552558422089 0 0 -0.13908185064792633 0 -0.11938545107841492 
		0 0 -0.13908185064792633 0 -0.11938545107841492 0 0 -0.13908153772354126 0 -0.14281558990478516 
		0 0.22924569249153137 0 0 0 0 0.81137162446975708 0;
createNode animCurveTA -n "char_FKExtraHair1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraHair1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraHair1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveHead1_M_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 24 ".ktv[0:23]"  0 1 7 1 10 1 16 1 22 1 47 1 52 1 57 1 59 
		1 63 1 68 1 71 1 74 1 78 1 82 1 84 1 88 1 91 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 24 ".kit[4:23]"  10 9 3 9 9 3 9 9 
		3 9 9 3 9 9 1 3 3 3 3 3;
	setAttr -s 24 ".kot[4:23]"  10 9 1 9 9 1 9 9 
		1 9 9 1 9 9 1 3 3 3 3 3;
	setAttr -s 24 ".kix[18:23]"  1 1 1 1 1 1;
	setAttr -s 24 ".kiy[18:23]"  0 0 0 0 0 0;
	setAttr -s 24 ".kox[6:23]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 24 ".koy[6:23]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveHead1_M_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 24 ".ktv[0:23]"  0 1 7 1 10 1 16 1 22 1 47 1 52 1 57 1 59 
		1 63 1 68 1 71 1 74 1 78 1 82 1 84 1 88 1 91 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 24 ".kit[4:23]"  10 9 3 9 9 3 9 9 
		3 9 9 3 9 9 1 3 3 3 3 3;
	setAttr -s 24 ".kot[4:23]"  10 9 1 9 9 1 9 9 
		1 9 9 1 9 9 1 3 3 3 3 3;
	setAttr -s 24 ".kix[18:23]"  1 1 1 1 1 1;
	setAttr -s 24 ".kiy[18:23]"  0 0 0 0 0 0;
	setAttr -s 24 ".kox[6:23]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 24 ".koy[6:23]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveHead1_M_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 24 ".ktv[0:23]"  0 1 7 1 10 1 16 1 22 1 47 1 52 1 57 1 59 
		1 63 1 68 1 71 1 74 1 78 1 82 1 84 1 88 1 91 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 24 ".kit[4:23]"  10 9 3 9 9 3 9 9 
		3 9 9 3 9 9 1 3 3 3 3 3;
	setAttr -s 24 ".kot[4:23]"  10 9 1 9 9 1 9 9 
		1 9 9 1 9 9 1 3 3 3 3 3;
	setAttr -s 24 ".kix[18:23]"  1 1 1 1 1 1;
	setAttr -s 24 ".kiy[18:23]"  0 0 0 0 0 0;
	setAttr -s 24 ".kox[6:23]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 24 ".koy[6:23]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveHead1_M_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 30 ".ktv[0:29]"  0 19.649599090973453 7 0.44514862933112265 
		10 0.44514862933112265 16 -23.844224453826339 22 -9.3214730133236401 28 1.5541390940218975 
		32 0.74247817862687604 47 -1.6068998143680415 52 -0.74042830366851076 55 -1.5936385336036547 
		57 -3.9316888350350778 59 -1.6068998143680415 63 -0.74042830366851076 65 -1.5936385336036547 
		68 -3.9316888350350778 71 -1.6068998143680415 74 -0.74042830366851076 76 -1.5936385336036547 
		78 -3.9316888350350778 82 -1.6068998143680415 84 -0.74042830366851076 86 -1.5936385336036547 
		88 -3.9316888350350778 91 -1.6068998143680415 93 -0.74042830366851076 101 -21.564751736955451 
		106 -21.564751736955451 110 -21.564751736955451 116 5.1421391096513736 126 19.649599090973453;
	setAttr -s 30 ".kit[0:29]"  3 3 3 3 10 10 10 9 
		3 9 9 9 3 9 9 9 3 9 9 9 3 9 9 9 1 
		3 3 3 3 3;
	setAttr -s 30 ".kot[0:29]"  3 3 3 3 10 10 10 9 
		1 9 9 9 1 9 9 9 1 9 9 9 1 9 9 9 1 
		3 3 3 3 3;
	setAttr -s 30 ".kix[24:29]"  1 1 1 1 1 1;
	setAttr -s 30 ".kiy[24:29]"  0 0 0 0 0 0;
	setAttr -s 30 ".kox[8:29]"  1 0.9484398365020752 0.99999856948852539 
		0.96334069967269897 1 0.9484398365020752 0.99999940395355225 0.96334081888198853 
		1 0.92272639274597168 0.99999940395355225 0.96334081888198853 1 0.92272669076919556 
		0.99999904632568359 0.94843971729278564 1 1 1 1 1 1;
	setAttr -s 30 ".koy[8:29]"  0 -0.31695732474327087 -0.0017358952900394797 
		0.26828086376190186 0 -0.31695708632469177 -0.0011572655057534575 0.2682807445526123 
		0 -0.38545548915863037 -0.0011572641087695956 0.2682807445526123 0 -0.38545495271682739 
		-0.0013887161621823907 0.3169575035572052 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveHead1_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 30 ".ktv[0:29]"  0 -30.214171376615486 7 -23.621291190903307 
		10 -23.621291190903307 16 -8.3080273076286222 22 -9.1864041419069054 28 -10.163232470201764 
		32 -6.4364226587410087 47 2.801004397029113 52 -9.7725138580672031 55 1.8147574996485261 
		57 18.660105636854873 59 2.801004397029113 63 -9.7725138580672031 65 1.8147574996485261 
		68 18.660105636854873 71 2.801004397029113 74 -9.7725138580672031 76 1.8147574996485261 
		78 18.660105636854873 82 2.801004397029113 84 -9.7725138580672031 86 1.8147574996485261 
		88 18.660105636854873 91 2.801004397029113 93 -9.7725138580672031 101 -34.959570449839781 
		106 -34.959570449839781 110 -34.959570449839781 116 -31.884552827912117 126 -30.214171376615486;
	setAttr -s 30 ".kit[4:29]"  10 10 10 1 3 1 3 1 
		3 1 3 1 3 1 3 1 3 1 3 1 1 3 3 3 3 
		3;
	setAttr -s 30 ".kot[4:29]"  10 10 10 1 1 1 3 1 
		1 1 3 1 1 1 3 1 1 1 3 1 1 3 3 3 3 
		3;
	setAttr -s 30 ".kix[7:29]"  0.47394967079162598 1 0.37002769112586975 
		1 0.46975803375244141 1 0.2795339822769165 1 0.36611631512641907 1 0.2795339822769165 
		1 0.34828490018844604 1 0.31332135200500488 1 0.34828490018844604 1 1 1 1 1 1;
	setAttr -s 30 ".kiy[7:29]"  -0.88055193424224854 0 0.92902070283889771 
		0 -0.88279521465301514 0 0.960135817527771 0 -0.9305691123008728 0 0.960135817527771 
		0 -0.93738871812820435 0 0.94964724779129028 0 -0.93738871812820435 0 0 0 0 0 0;
	setAttr -s 30 ".kox[7:29]"  0.47394964098930359 1 0.37002769112586975 
		1 0.46975800395011902 1 0.2795339822769165 1 0.36611625552177429 1 0.2795339822769165 
		1 0.34828484058380127 1 0.31332135200500488 1 0.34828484058380127 1 1 1 1 1 1;
	setAttr -s 30 ".koy[7:29]"  -0.88055199384689331 0 0.92902070283889771 
		0 -0.88279527425765991 0 0.960135817527771 0 -0.9305691123008728 0 0.960135817527771 
		0 -0.93738871812820435 0 0.94964724779129028 0 -0.93738871812820435 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveHead1_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 30 ".ktv[0:29]"  0 -39.886477028299176 7 -29.279543830019492 
		10 -29.279543830019492 16 -13.910230868156477 22 -21.207947516261971 28 -4.4770725333715298 
		32 -2.380922814894098 47 -0.35655306859968272 52 0.020274143055550892 55 -0.18522933947567338 
		57 1.2643033049609156 59 -0.35655306859968272 63 0.020274143055550892 65 -0.18522933947567338 
		68 1.2643033049609156 71 -0.35655306859968272 74 0.020274143055550892 76 -0.18522933947567338 
		78 1.2643033049609156 82 -0.35655306859968272 84 0.020274143055550892 86 -0.18522933947567338 
		88 1.2643033049609156 91 -0.35655306859968272 93 0.020274143055550892 101 26.046558807125962 
		106 26.046558807125962 110 -14.262847506340661 116 -34.031742703814359 126 -39.886477028299176;
	setAttr -s 30 ".kit[4:29]"  10 10 10 3 3 3 9 3 
		3 3 9 3 3 3 9 3 3 3 9 3 1 3 3 3 3 
		3;
	setAttr -s 30 ".kot[4:29]"  10 10 10 3 1 3 9 3 
		1 3 9 3 1 3 9 3 1 3 9 3 1 3 3 3 3 
		3;
	setAttr -s 30 ".kix[24:29]"  1 1 1 1 1 1;
	setAttr -s 30 ".kiy[24:29]"  0 0 0 0 0 0;
	setAttr -s 30 ".kox[8:29]"  1 1 0.99974864721298218 1 1 1 0.99988830089569092 
		1 1 1 0.99988830089569092 1 1 1 0.99983906745910645 1 1 1 1 1 1 1;
	setAttr -s 30 ".koy[8:29]"  0 0 -0.022420588880777359 0 0 0 -0.014949160628020763 
		0 0 0 -0.014949142001569271 0 0 0 -0.017938083037734032 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraHead1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraHead1_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraHead1_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveNeck1_M_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 29 ".ktv[0:28]"  0 1 7 1 10 1 16 1 22 1 32 1 47 1 52 1 55 
		1 57 1 59 1 63 1 65 1 68 1 71 1 74 1 76 1 78 1 82 1 84 1 86 1 88 1 91 1 93 1 101 
		1 106 1 110 1 116 1 126 1;
	setAttr -s 29 ".kit[0:28]"  3 3 3 3 10 3 10 1 
		10 10 10 1 10 10 10 1 10 10 10 1 10 10 10 1 3 
		3 3 3 3;
	setAttr -s 29 ".kot[0:28]"  3 3 3 3 10 3 10 1 
		10 10 10 1 10 10 10 1 10 10 10 1 10 10 10 1 3 
		3 3 3 3;
	setAttr -s 29 ".kix[7:28]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1 1;
	setAttr -s 29 ".kiy[7:28]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0 0;
	setAttr -s 29 ".kox[7:28]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1 1;
	setAttr -s 29 ".koy[7:28]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0 0;
createNode animCurveTU -n "char_FKCurveNeck1_M_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 29 ".ktv[0:28]"  0 1 7 1 10 1 16 1 22 1 32 1 47 1 52 1 55 
		1 57 1 59 1 63 1 65 1 68 1 71 1 74 1 76 1 78 1 82 1 84 1 86 1 88 1 91 1 93 1 101 
		1 106 1 110 1 116 1 126 1;
	setAttr -s 29 ".kit[0:28]"  3 3 3 3 10 3 10 1 
		10 10 10 1 10 10 10 1 10 10 10 1 10 10 10 1 3 
		3 3 3 3;
	setAttr -s 29 ".kot[0:28]"  3 3 3 3 10 3 10 1 
		10 10 10 1 10 10 10 1 10 10 10 1 10 10 10 1 3 
		3 3 3 3;
	setAttr -s 29 ".kix[7:28]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1 1;
	setAttr -s 29 ".kiy[7:28]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0 0;
	setAttr -s 29 ".kox[7:28]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1 1;
	setAttr -s 29 ".koy[7:28]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0 0;
createNode animCurveTU -n "char_FKCurveNeck1_M_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 29 ".ktv[0:28]"  0 1 7 1 10 1 16 1 22 1 32 1 47 1 52 1 55 
		1 57 1 59 1 63 1 65 1 68 1 71 1 74 1 76 1 78 1 82 1 84 1 86 1 88 1 91 1 93 1 101 
		1 106 1 110 1 116 1 126 1;
	setAttr -s 29 ".kit[0:28]"  3 3 3 3 10 3 10 1 
		10 10 10 1 10 10 10 1 10 10 10 1 10 10 10 1 3 
		3 3 3 3;
	setAttr -s 29 ".kot[0:28]"  3 3 3 3 10 3 10 1 
		10 10 10 1 10 10 10 1 10 10 10 1 10 10 10 1 3 
		3 3 3 3;
	setAttr -s 29 ".kix[7:28]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1 1;
	setAttr -s 29 ".kiy[7:28]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0 0;
	setAttr -s 29 ".kox[7:28]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1 1;
	setAttr -s 29 ".koy[7:28]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0 0;
createNode animCurveTA -n "char_FKCurveNeck1_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 36 ".ktv[0:35]"  0 16.978679829010165 7 16.978679829010165 
		10 16.978679829010165 16 -11.297740639471115 22 0.072095742557156672 28 2.2532217719371315 
		32 11.518024281763193 34 16.806781877012209 40 23.014295167486825 47 22.653569452505746 
		52 24.143158686788997 55 22.416559685868368 56 22.27901983774019 57 25.774571127656234 
		59 22.653569452505746 63 24.143158686788997 65 22.416559685868368 67 22.27901983774019 
		68 25.774571127656234 71 22.653569452505746 74 24.143158686788997 76 22.416559685868368 
		77 22.27901983774019 78 25.774571127656234 82 22.653569452505746 84 24.143158686788997 
		86 22.416559685868368 87 22.27901983774019 88 25.774571127656234 91 22.653569452505746 
		93 24.143158686788997 101 -1.6543431653247815 106 -1.6543431653247815 110 -1.6543431653247815 
		116 10.419851896721404 126 16.978679829010165;
	setAttr -s 36 ".kit[0:35]"  3 3 3 3 10 10 3 10 
		10 10 1 9 10 10 10 1 9 10 10 10 1 9 10 10 10 
		1 9 10 10 10 1 3 3 3 3 3;
	setAttr -s 36 ".kot[0:35]"  3 3 3 3 10 10 3 10 
		10 10 1 9 10 10 10 1 9 10 10 10 1 9 10 10 10 
		1 9 10 10 10 1 3 3 3 3 3;
	setAttr -s 36 ".kix[10:35]"  1 0.97149515151977539 1 0.99787008762359619 
		1 1 0.97149515151977539 1 0.99880027770996094 1 1 0.95093506574630737 1 0.99923169612884521 
		1 1 0.9509352445602417 1 0.99880027770996094 1 1 1 1 1 1 1;
	setAttr -s 36 ".kiy[10:35]"  0 -0.23705959320068359 0 0.065231986343860626 
		0 0 -0.23705939948558807 0 0.048969656229019165 0 0 -0.30939045548439026 0 0.039192590862512589 
		0 0 -0.30938977003097534 0 0.048969656229019165 0 0 0 0 0 0 0;
	setAttr -s 36 ".kox[10:35]"  1 0.97149515151977539 1 0.99787008762359619 
		1 1 0.97149515151977539 1 0.99880027770996094 1 1 0.95093506574630737 1 0.99923169612884521 
		1 1 0.9509352445602417 1 0.99880027770996094 1 1 1 1 1 1 1;
	setAttr -s 36 ".koy[10:35]"  0 -0.23705959320068359 0 0.065231986343860626 
		0 0 -0.23705939948558807 0 0.048969656229019165 0 0 -0.30939045548439026 0 0.039192590862512589 
		0 0 -0.30938977003097534 0 0.048969656229019165 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveNeck1_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 36 ".ktv[0:35]"  0 -13.679820867901928 7 -13.679820867901928 
		10 -13.679820867901928 16 -34.330103593477276 22 -30.478773887241378 28 -7.7783583155149172 
		32 -4.2546649505338028 34 -10.319223966053844 40 -29.703847519004412 47 -28.860059468286661 
		52 -30.513271050821505 55 -30.778990031987792 56 -33.166597412855303 57 -31.362235391021169 
		59 -28.860059468286661 63 -30.513271050821505 65 -30.778990031987792 67 -33.166597412855303 
		68 -31.362235391021169 71 -28.860059468286661 74 -30.513271050821505 76 -30.778990031987792 
		77 -33.166597412855303 78 -31.362235391021169 82 -28.860059468286661 84 -30.513271050821505 
		86 -30.778990031987792 87 -33.166597412855303 88 -31.362235391021169 91 -28.860059468286661 
		93 -30.513271050821505 101 -9.4652178851964823 106 -9.4652178851964823 110 -9.4652178851964823 
		116 -12.196279749808511 126 -13.679820867901928;
	setAttr -s 36 ".kit[0:35]"  3 3 3 3 10 10 3 10 
		10 10 1 10 10 10 10 1 10 10 10 10 1 10 10 10 10 
		1 10 10 10 10 1 3 3 3 3 3;
	setAttr -s 36 ".kot[0:35]"  3 3 3 3 10 10 3 10 
		10 10 1 10 10 10 10 1 10 10 10 10 1 10 10 10 10 
		1 10 10 10 10 1 3 3 3 3 3;
	setAttr -s 36 ".kix[10:35]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1 1 1 1 1 1;
	setAttr -s 36 ".kiy[10:35]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0 0 0 0 0 0;
	setAttr -s 36 ".kox[10:35]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1 1 1 1 1 1;
	setAttr -s 36 ".koy[10:35]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveNeck1_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 36 ".ktv[0:35]"  0 -6.4072944111053358 7 -6.4072944111053358 
		10 -6.4072944111053358 16 12.027364739934201 22 4.7245128963745255 28 -3.573916681140008 
		32 -4.8510676478071533 34 -5.1898940864888292 40 -5.6047798044452612 47 -3.2659934852558417 
		52 -20.426749453510382 55 -8.753618173668638 56 -5.885241540988698 57 3.5023381640773819 
		59 -3.2659934852558417 63 -20.426749453510382 65 -8.753618173668638 67 -5.885241540988698 
		68 3.5023381640773819 71 -3.2659934852558417 74 -20.426749453510382 76 -8.753618173668638 
		77 -5.885241540988698 78 3.5023381640773819 82 -3.2659934852558417 84 -20.426749453510382 
		86 -8.753618173668638 87 -5.885241540988698 88 3.5023381640773819 91 -3.2659934852558417 
		93 -20.426749453510382 101 22.650413826315511 106 22.650413826315511 110 22.650413826315511 
		116 3.8210248741677582 126 -6.4072944111053358;
	setAttr -s 36 ".kit[0:35]"  3 3 3 3 10 10 3 10 
		10 10 1 10 10 10 10 1 10 10 10 10 1 10 10 10 10 
		1 10 10 10 10 1 3 3 3 3 3;
	setAttr -s 36 ".kot[0:35]"  3 3 3 3 10 10 3 10 
		10 10 1 10 10 10 10 1 10 10 10 10 1 10 10 10 10 
		1 10 10 10 10 1 3 3 3 3 3;
	setAttr -s 36 ".kix[10:35]"  1 0.46507942676544189 0.29754596948623657 
		0.90947377681732178 0.43190962076187134 1 0.46507978439331055 0.42349997162818909 
		0.94594532251358032 0.43190982937812805 1 0.36658543348312378 0.29754596948623657 
		0.96438097953796387 0.43190982937812805 1 0.36658614873886108 0.29754695296287537 
		0.94594532251358032 0.37064281105995178 1 1 1 1 1 1;
	setAttr -s 36 ".kiy[10:35]"  0 0.88526898622512817 0.95470750331878662 
		0.4157613217830658 -0.90191686153411865 0 0.88526886701583862 0.90589612722396851 
		0.32432594895362854 -0.90191680192947388 0 0.93038439750671387 0.95470750331878662 
		0.26451706886291504 -0.90191680192947388 0 0.93038409948348999 0.95470720529556274 
		0.32432594895362854 -0.92877548933029175 0 0 0 0 0 0;
	setAttr -s 36 ".kox[10:35]"  1 0.46507942676544189 0.29754596948623657 
		0.90947377681732178 0.43190962076187134 1 0.46507978439331055 0.42349997162818909 
		0.94594532251358032 0.43190982937812805 1 0.36658543348312378 0.29754596948623657 
		0.96438097953796387 0.43190982937812805 1 0.36658614873886108 0.29754695296287537 
		0.94594532251358032 0.37064281105995178 1 1 1 1 1 1;
	setAttr -s 36 ".koy[10:35]"  0 0.88526898622512817 0.95470750331878662 
		0.4157613217830658 -0.90191686153411865 0 0.88526886701583862 0.90589612722396851 
		0.32432594895362854 -0.90191680192947388 0 0.93038439750671387 0.95470750331878662 
		0.26451706886291504 -0.90191680192947388 0 0.93038409948348999 0.95470720529556274 
		0.32432594895362854 -0.92877548933029175 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraNeck1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraNeck1_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraNeck1_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveSpine3_M_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 5 1 10 1 14 1 30 1 35 1 45 1 52 1 57 
		1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 96 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[2:21]"  9 9 10 10 3 3 3 3 
		3 3 3 3 3 1 10 3 3 3 3 3;
	setAttr -s 22 ".kot[2:21]"  9 9 10 10 3 1 3 1 
		3 1 3 1 3 1 10 3 3 3 3 3;
	setAttr -s 22 ".kix[15:21]"  1 1 1 1 1 1 1;
	setAttr -s 22 ".kiy[15:21]"  0 0 0 0 0 0 0;
	setAttr -s 22 ".kox[7:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[7:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveSpine3_M_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 5 1 10 1 14 1 30 1 35 1 45 1 52 1 57 
		1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 96 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[2:21]"  9 9 10 10 3 3 3 3 
		3 3 3 3 3 1 10 3 3 3 3 3;
	setAttr -s 22 ".kot[2:21]"  9 9 10 10 3 1 3 1 
		3 1 3 1 3 1 10 3 3 3 3 3;
	setAttr -s 22 ".kix[15:21]"  1 1 1 1 1 1 1;
	setAttr -s 22 ".kiy[15:21]"  0 0 0 0 0 0 0;
	setAttr -s 22 ".kox[7:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[7:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveSpine3_M_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 5 1 10 1 14 1 30 1 35 1 45 1 52 1 57 
		1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 96 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[2:21]"  9 9 10 10 3 3 3 3 
		3 3 3 3 3 1 10 3 3 3 3 3;
	setAttr -s 22 ".kot[2:21]"  9 9 10 10 3 1 3 1 
		3 1 3 1 3 1 10 3 3 3 3 3;
	setAttr -s 22 ".kix[15:21]"  1 1 1 1 1 1 1;
	setAttr -s 22 ".kiy[15:21]"  0 0 0 0 0 0 0;
	setAttr -s 22 ".kox[7:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[7:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveSpine3_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 33 ".ktv[0:32]"  0 -4.1759924717065973 5 9.2826218606717319 
		10 -23.988537095226679 14 -24.760212035296984 20 -3.9536351513055541 26 10.702737851171806 
		30 -1.941145502028724 35 -6.8927594816508693 39 -5.766587760600431 45 0.45136402288007593 
		52 7.0089521361193423 54 8.685220896595057 57 7.8577265863169758 58 5.7595937497298664 
		63 7.0089521361193423 65 8.685220896595057 68 7.8577265863169758 70 5.7595937497298664 
		74 7.0089521361193423 75 8.685220896595057 78 7.8577265863169758 80 5.7595937497298664 
		84 7.0089521361193423 85 8.685220896595057 88 7.8577265863169758 89 5.7595937497298664 
		93 7.0089521361193423 96 3.7109373127949161 101 0.097726249022902112 106 -4.5721107058156552 
		110 -23.019116728395566 116 -4.3154261717107936 126 -4.1759924717065973;
	setAttr -s 33 ".kit[2:32]"  9 9 10 10 10 10 10 9 
		1 3 9 3 1 3 9 3 1 3 9 3 1 3 9 3 1 
		10 3 3 3 3 3;
	setAttr -s 33 ".kot[2:32]"  9 9 10 10 10 10 10 9 
		1 3 9 3 1 3 9 3 1 3 9 3 1 3 9 3 1 
		10 3 3 3 3 3;
	setAttr -s 33 ".kix[10:32]"  0.84163862466812134 1 0.9338613748550415 
		1 0.78989869356155396 1 0.95613330602645874 1 0.75166100263595581 1 0.95613342523574829 
		1 0.79068940877914429 1 0.93386149406433105 1 0.96845132112503052 0.91112238168716431 
		1 1 1 1 1;
	setAttr -s 33 ".kiy[10:32]"  0.54004114866256714 0 -0.3576350212097168 
		0 0.61323726177215576 0 -0.29293176531791687 0 0.65954965353012085 0 -0.29293137788772583 
		0 0.61221742630004883 0 -0.35763475298881531 0 0.24920274317264557 -0.41213589906692505 
		0 0 0 0 0;
	setAttr -s 33 ".kox[10:32]"  0.84163862466812134 1 0.9338613748550415 
		1 0.78989869356155396 1 0.95613330602645874 1 0.75166100263595581 1 0.95613342523574829 
		1 0.79068940877914429 1 0.93386149406433105 1 0.96845132112503052 0.91112238168716431 
		1 1 1 1 1;
	setAttr -s 33 ".koy[10:32]"  0.54004114866256714 0 -0.3576350212097168 
		0 0.61323726177215576 0 -0.29293176531791687 0 0.65954965353012085 0 -0.29293137788772583 
		0 0.61221742630004883 0 -0.35763475298881531 0 0.24920272827148438 -0.41213589906692505 
		0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveSpine3_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 33 ".ktv[0:32]"  0 -1.201 5 9.4009549644756198 10 3.0068325312014048 
		14 -23.652016694237453 20 -16.77391116766832 26 6.1734744560684662 30 6.4175481745539802 
		35 -7.1255318609670715 39 -1.8040215325306748 45 -13.146491169288131 52 14.534746916054056 
		54 17.54178567095278 57 -9.4651688912269787 58 -13.024251462835334 63 14.534746916054056 
		65 17.54178567095278 68 -9.4651688912269787 70 -13.024251462835334 74 14.534746916054056 
		75 17.54178567095278 78 -9.4651688912269787 80 -13.024251462835334 84 14.534746916054056 
		85 17.54178567095278 88 -9.4651688912269787 89 -13.024251462835334 93 14.534746916054056 
		96 15.227696055510265 101 24.474952865065106 106 -28.104412920840751 110 -35.860264821502142 
		116 -10.671006890065918 126 -1.201;
	setAttr -s 33 ".kit[2:32]"  9 9 10 10 10 10 10 9 
		9 3 9 3 9 3 9 3 9 3 9 3 9 3 9 3 1 
		10 3 3 3 3 3;
	setAttr -s 33 ".kot[2:32]"  9 9 10 10 10 10 10 9 
		1 3 9 3 1 3 9 3 1 3 9 3 1 3 9 3 1 
		10 3 3 3 3 3;
	setAttr -s 33 ".kix[26:32]"  0.32906728982925415 1 1 1 1 1 1;
	setAttr -s 33 ".kiy[26:32]"  0.94430649280548096 0 0 0 0 0 0;
	setAttr -s 33 ".kox[10:32]"  0.47775104641914368 1 0.24247370660305023 
		1 0.40996706485748291 1 0.2982010543346405 1 0.36953464150428772 1 0.29820144176483154 
		1 0.41087660193443298 1 0.24247391521930695 1 0.3290674090385437 1 1 1 1 1 1;
	setAttr -s 33 ".koy[10:32]"  0.87849521636962891 0 -0.97015798091888428 
		0 0.91210025548934937 0 -0.95450311899185181 0 0.92921692132949829 0 -0.95450299978256226 
		0 0.91169100999832153 0 -0.97015786170959473 0 0.94430643320083618 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveSpine3_M_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 33 ".ktv[0:32]"  0 -38.617693158088045 5 -37.646863881148569 
		10 -40.243521516331533 14 -41.474312879506158 20 5.9858502855808666 26 17.117618549892377 
		30 20.901092308794194 35 13.979561570531589 39 21.153040432294425 45 21.160414047479218 
		52 11.616198643213048 54 11.634997778600804 57 9.8764996825417057 58 10.483863043471748 
		63 11.616198643213048 65 11.634997778600804 68 9.8764996825417057 70 10.483863043471748 
		74 11.616198643213048 75 11.634997778600804 78 9.8764996825417057 80 10.483863043471748 
		84 11.616198643213048 85 11.634997778600804 88 9.8764996825417057 89 10.483863043471748 
		93 11.616198643213048 96 8.6348119073820513 101 5.1747236902701221 106 5.3397587983489361 
		110 -21.224593745091024 116 -38.073937830158066 126 -38.617693158088045;
	setAttr -s 33 ".kit[0:32]"  3 3 9 9 10 10 10 10 
		10 9 3 10 9 9 3 10 9 9 3 10 9 9 3 10 9 
		9 1 10 3 3 3 3 3;
	setAttr -s 33 ".kot[0:32]"  3 3 9 9 10 10 10 10 
		10 9 1 10 9 9 1 10 9 9 1 10 9 9 1 10 9 
		9 1 10 3 3 3 3 3;
	setAttr -s 33 ".kix[26:32]"  1 0.92145699262619019 1 1 1 1 1;
	setAttr -s 33 ".kiy[26:32]"  0 -0.38848033547401428 0 0 0 0 0;
	setAttr -s 33 ".kox[10:32]"  1 1 0.98883700370788574 0.98867118358612061 
		1 1 0.99281245470046997 0.98867118358612061 1 1 0.99281245470046997 0.98867118358612061 
		1 1 0.98883700370788574 0.98380708694458008 1 0.92145699262619019 1 1 1 1 1;
	setAttr -s 33 ".koy[10:32]"  0 0 -0.14900112152099609 0.15009751915931702 
		0 0 -0.11968022584915161 0.15009742975234985 0 0 -0.11968005448579788 0.15009742975234985 
		0 0 -0.14900098741054535 0.17923097312450409 0 -0.38848033547401428 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraSpine3_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraSpine3_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraSpine3_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveSpine4_L_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 14 1 16 1 33 1 45 1 52 1 57 
		1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 96 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[0:21]"  3 9 9 9 9 10 9 3 
		9 3 9 3 9 3 9 1 10 3 3 3 3 3;
	setAttr -s 22 ".kot[0:21]"  3 9 9 9 9 10 9 1 
		9 1 9 1 9 1 9 1 10 3 3 3 3 3;
	setAttr -s 22 ".kix[15:21]"  1 1 1 1 1 1 1;
	setAttr -s 22 ".kiy[15:21]"  0 0 0 0 0 0 0;
	setAttr -s 22 ".kox[7:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[7:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveSpine4_L_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 14 1 16 1 33 1 45 1 52 1 57 
		1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 96 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[0:21]"  3 9 9 9 9 10 9 3 
		9 3 9 3 9 3 9 1 10 3 3 3 3 3;
	setAttr -s 22 ".kot[0:21]"  3 9 9 9 9 10 9 1 
		9 1 9 1 9 1 9 1 10 3 3 3 3 3;
	setAttr -s 22 ".kix[15:21]"  1 1 1 1 1 1 1;
	setAttr -s 22 ".kiy[15:21]"  0 0 0 0 0 0 0;
	setAttr -s 22 ".kox[7:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[7:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveSpine4_L_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 14 1 16 1 33 1 45 1 52 1 57 
		1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 96 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[0:21]"  3 9 9 9 9 10 9 3 
		9 3 9 3 9 3 9 1 10 3 3 3 3 3;
	setAttr -s 22 ".kot[0:21]"  3 9 9 9 9 10 9 1 
		9 1 9 1 9 1 9 1 10 3 3 3 3 3;
	setAttr -s 22 ".kix[15:21]"  1 1 1 1 1 1 1;
	setAttr -s 22 ".kiy[15:21]"  0 0 0 0 0 0 0;
	setAttr -s 22 ".kox[7:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[7:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveSpine4_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 33 ".ktv[0:32]"  0 19.548247782583122 7 20.166560998912061 
		10 9.6365021066533565 14 0.24130546836750427 16 -8.3419722730691124 20 -4.53036871747888 
		33 0.9002235370687478 35 5.1493075642632489 39 5.127927759310718 45 6.2344501979929383 
		52 1.3210875890056448 55 1.4601625582831288 57 1.7989230399930711 59 1.6338027965133395 
		63 1.3210875890056448 65 1.4601625582831288 68 1.7989230399930711 71 1.6338027965133395 
		74 1.3210875890056448 76 1.4601625582831288 78 1.7989230399930711 82 1.6338027965133395 
		84 1.3210875890056448 86 1.4601625582831288 88 1.7989230399930711 91 1.6338027965133395 
		93 1.3210875890056448 96 -0.66803123251671537 101 -1.497509268211429 106 -3.2832844423331449 
		110 0.25998300096118693 116 13.854689204898488 126 19.548247782583122;
	setAttr -s 33 ".kit[0:32]"  3 9 9 9 9 10 10 10 
		10 9 3 9 9 9 3 9 9 9 3 9 9 9 3 9 9 
		9 1 10 3 3 3 3 3;
	setAttr -s 33 ".kot[0:32]"  3 9 9 9 9 10 10 10 
		10 9 1 9 9 9 1 9 9 9 1 9 9 9 1 9 9 
		9 3 10 3 3 3 3 3;
	setAttr -s 33 ".kix[26:32]"  1 1 1 1 1 1 1;
	setAttr -s 33 ".kiy[26:32]"  0 0 0 0 0 0 0;
	setAttr -s 33 ".kox[10:32]"  1 0.99875044822692871 0.99974173307418823 
		0.99913173913955688 1 0.99875044822692871 0.9998852014541626 0.99913173913955688 
		1 0.99804961681365967 0.9998852014541626 0.99913173913955688 1 0.99804961681365967 
		0.99983465671539307 0.99875044822692871 1 1 1 1 1 1 1;
	setAttr -s 33 ".koy[10:32]"  0 0.049976296722888947 0.022723585367202759 
		-0.041662819683551788 0 0.04997626319527626 0.015151243656873703 -0.041662793606519699 
		0 0.062426578253507614 0.015151225961744785 -0.041662793606519699 0 0.06242646649479866 
		0.018180549144744873 -0.049976333975791931 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveSpine4_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 33 ".ktv[0:32]"  0 4.2832309672587163 7 10.731526835325141 
		10 2.2584138487381868 14 6.9480998485118297 16 12.029473364950002 20 18.594378461561959 
		33 -4.1996653317548551 35 -9.0166761227983443 39 -9.4245410398584308 45 -4.1559993463610212 
		52 -2.437302584509319 55 -2.535628822173738 57 6.2391687015646013 59 6.7151171685763922 
		63 -2.437302584509319 65 -2.535628822173738 68 6.2391687015646013 71 6.7151171685763922 
		74 -2.437302584509319 76 -2.535628822173738 78 6.2391687015646013 82 6.7151171685763922 
		84 -2.437302584509319 86 -2.535628822173738 88 6.2391687015646013 91 6.7151171685763922 
		93 -2.437302584509319 96 0.66102076591930736 101 6.8267752476836883 106 4.7346336640447957 
		110 -1.685535134210433 116 2.1605567214889234 126 4.2832309672587163;
	setAttr -s 33 ".kit[1:32]"  9 9 9 9 10 10 10 10 
		1 3 10 1 3 3 10 1 3 3 10 1 3 3 10 1 3 
		1 10 3 3 3 3 3;
	setAttr -s 33 ".kot[1:32]"  9 9 9 9 10 10 10 10 
		1 1 10 1 3 1 10 1 3 1 10 1 3 1 10 1 3 
		1 10 3 3 3 3 3;
	setAttr -s 33 ".kix[9:32]"  0.97345757484436035 1 1 0.97345757484436035 
		1 1 1 0.95194739103317261 1 1 1 0.94657903909683228 1 1 1 0.96198552846908569 1 1 
		0.8550947904586792 1 1 1 1 1;
	setAttr -s 33 ".kiy[9:32]"  0.22886750102043152 0 0 0.22886750102043152 
		0 0 0 0.30626153945922852 0 0 0 0.32247194647789001 0 0 0 0.27310037612915039 0 0 
		0.51847177743911743 0 0 0 0 0;
	setAttr -s 33 ".kox[9:32]"  0.97345757484436035 1 1 0.97345757484436035 
		1 1 1 0.95194745063781738 1 1 1 0.94657903909683228 1 1 1 0.96198558807373047 1 1 
		0.8550947904586792 1 1 1 1 1;
	setAttr -s 33 ".koy[9:32]"  0.22886742651462555 0 0 0.22886742651462555 
		0 0 0 0.30626147985458374 0 0 0 0.32247185707092285 0 0 0 0.273100346326828 0 0 0.51847177743911743 
		0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveSpine4_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 33 ".ktv[0:32]"  0 5.393 7 5.4739138631599653 10 2.0689892657055684 
		14 0.21649588584174415 16 -0.26606431486213045 20 2.3421698135137903 33 0.44573560440323351 
		35 3.3716988205715941 39 5.4952888111996909 45 6.6478821140513906 52 4.4227254580739546 
		55 3.2959456361351407 57 4.4281633257692059 59 2.9343387558818423 63 4.4227254580739546 
		65 3.2959456361351407 68 4.4281633257692059 71 2.9343387558818423 74 4.4227254580739546 
		76 3.2959456361351407 78 4.4281633257692059 82 2.9343387558818423 84 4.4227254580739546 
		86 3.2959456361351407 88 4.4281633257692059 91 2.9343387558818423 93 4.4227254580739546 
		96 2.4668397563328242 101 -33.727491019369957 106 -0.10471921951443569 110 21.261524348879899 
		116 11.242614566534133 126 5.393;
	setAttr -s 33 ".kit[0:32]"  3 9 9 9 9 10 10 10 
		10 9 3 10 9 10 3 10 9 10 3 10 9 10 3 10 9 
		10 1 10 3 3 3 3 3;
	setAttr -s 33 ".kot[0:32]"  3 9 9 9 9 10 10 10 
		10 9 1 10 9 10 1 10 9 10 1 10 9 10 1 10 9 
		10 1 10 3 3 3 3 3;
	setAttr -s 33 ".kix[26:32]"  1 1 1 1 1 1 1;
	setAttr -s 33 ".kiy[26:32]"  0 0 0 0 0 0 0;
	setAttr -s 33 ".kox[10:32]"  1 1 0.99888163805007935 1 1 1 0.99950253963470459 
		1 1 1 0.99950253963470459 1 1 1 0.99928385019302368 1 1 1 1 1 1 1 1;
	setAttr -s 33 ".koy[10:32]"  0 0 -0.04728129506111145 0 0 0 -0.031540483236312866 
		0 0 0 -0.031540445983409882 0 0 0 -0.03784024715423584 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraSpine4_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraSpine4_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraSpine4_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurvePelvis1_M_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 23 ".ktv[0:22]"  0 1 7 1 10 1 16 1 23 1 32 1 35 1 41 1 46 
		1 52 1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 23 ".kit[4:22]"  10 3 3 10 10 3 3 3 
		3 3 3 3 3 1 3 3 3 3 3;
	setAttr -s 23 ".kot[4:22]"  10 3 3 10 10 1 3 1 
		3 1 3 1 3 1 3 3 3 3 3;
	setAttr -s 23 ".kix[17:22]"  1 1 1 1 1 1;
	setAttr -s 23 ".kiy[17:22]"  0 0 0 0 0 0;
	setAttr -s 23 ".kox[9:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".koy[9:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurvePelvis1_M_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 23 ".ktv[0:22]"  0 1 7 1 10 1 16 1 23 1 32 1 35 1 41 1 46 
		1 52 1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 23 ".kit[4:22]"  10 3 3 10 10 3 3 3 
		3 3 3 3 3 1 3 3 3 3 3;
	setAttr -s 23 ".kot[4:22]"  10 3 3 10 10 1 3 1 
		3 1 3 1 3 1 3 3 3 3 3;
	setAttr -s 23 ".kix[17:22]"  1 1 1 1 1 1;
	setAttr -s 23 ".kiy[17:22]"  0 0 0 0 0 0;
	setAttr -s 23 ".kox[9:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".koy[9:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurvePelvis1_M_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 23 ".ktv[0:22]"  0 1 7 1 10 1 16 1 23 1 32 1 35 1 41 1 46 
		1 52 1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 23 ".kit[4:22]"  10 3 3 10 10 3 3 3 
		3 3 3 3 3 1 3 3 3 3 3;
	setAttr -s 23 ".kot[4:22]"  10 3 3 10 10 1 3 1 
		3 1 3 1 3 1 3 3 3 3 3;
	setAttr -s 23 ".kix[17:22]"  1 1 1 1 1 1;
	setAttr -s 23 ".kiy[17:22]"  0 0 0 0 0 0;
	setAttr -s 23 ".kox[9:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".koy[9:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurvePelvis1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 24 ".ktv[0:23]"  0 0 7 0 10 0 16 0 23 7.6768638725076235 
		27 1.0258089912233801 32 0 35 0 41 3.4925594180470809 46 -0.89673437345256302 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 24 ".kit[4:23]"  10 10 3 3 10 10 3 3 
		3 3 3 3 3 3 1 3 3 3 3 3;
	setAttr -s 24 ".kot[4:23]"  10 10 3 3 10 10 1 3 
		1 3 1 3 1 3 1 3 3 3 3 3;
	setAttr -s 24 ".kix[18:23]"  1 1 1 1 1 1;
	setAttr -s 24 ".kiy[18:23]"  0 0 0 0 0 0;
	setAttr -s 24 ".kox[10:23]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 24 ".koy[10:23]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurvePelvis1_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 24 ".ktv[0:23]"  0 0 7 0 10 0 16 0 23 -0.028842429724606541 
		27 0.36147464375421634 32 0 35 0 41 -1.2378290618049028 46 0.11891002092921719 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 24 ".kit[4:23]"  10 10 3 3 10 10 3 3 
		3 3 3 3 3 3 1 3 3 3 3 3;
	setAttr -s 24 ".kot[4:23]"  10 10 3 3 10 10 1 3 
		1 3 1 3 1 3 1 3 3 3 3 3;
	setAttr -s 24 ".kix[18:23]"  1 1 1 1 1 1;
	setAttr -s 24 ".kiy[18:23]"  0 0 0 0 0 0;
	setAttr -s 24 ".kox[10:23]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 24 ".koy[10:23]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurvePelvis1_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 24 ".ktv[0:23]"  0 -0.83191351642244571 7 -0.83191351642244571 
		10 -0.83191351642244571 16 -0.83191351642244571 23 -0.83988588984780266 27 -0.53583585328472727 
		32 -0.83191351642244571 35 -0.83191351642244571 41 -1.6793076091010075 46 -0.79917641483357194 
		52 -0.83191351642244571 57 -0.83191351642244571 63 -0.83191351642244571 68 -0.83191351642244571 
		74 -0.83191351642244571 78 -0.83191351642244571 84 -0.83191351642244571 88 -0.83191351642244571 
		93 -0.83191351642244571 101 -0.83191351642244571 106 -0.83191351642244571 110 -0.83191351642244571 
		116 -0.83191351642244571 126 -0.83191351642244571;
	setAttr -s 24 ".kit[4:23]"  10 10 3 3 10 10 3 3 
		3 3 3 3 3 3 1 3 3 3 3 3;
	setAttr -s 24 ".kot[4:23]"  10 10 3 3 10 10 1 3 
		1 3 1 3 1 3 1 3 3 3 3 3;
	setAttr -s 24 ".kix[18:23]"  1 1 1 1 1 1;
	setAttr -s 24 ".kiy[18:23]"  0 0 0 0 0 0;
	setAttr -s 24 ".kox[10:23]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 24 ".koy[10:23]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraPelvis1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraPelvis1_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraPelvis1_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_RootCurveRoot1_M_CenterBtwFeet";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 0 7 0 10 0 16 0 29 0 35 0 42 0 46 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 116 0 126 0;
	setAttr -s 21 ".kit[1:20]"  9 9 9 10 3 10 10 3 
		3 3 3 3 3 3 3 1 3 3 3 3;
	setAttr -s 21 ".kot[1:20]"  9 9 9 10 3 10 10 1 
		3 1 3 1 3 1 3 1 3 3 3 3;
	setAttr -s 21 ".kix[16:20]"  1 1 1 1 1;
	setAttr -s 21 ".kiy[16:20]"  0 0 0 0 0;
	setAttr -s 21 ".kox[8:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".koy[8:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_RootCurveRoot1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 29 ".ktv[0:28]"  0 3.0405827598215973 7 -3.3633772171590151 
		10 -4.0828395261086783 16 -1.6805892886523854 29 -6.6882257101112801 35 3.6267360183179491 
		42 4.966313769740256 46 1.9225968502362887 52 -1.6715472983642528 56 1.6977875697405542 
		57 6.362971331229109 60 1.20729721045912 63 -1.6715472983642528 66 1.6977875697405542 
		68 6.362971331229109 72 1.20729721045912 74 -1.6715472983642528 77 1.6977875697405542 
		78 6.362971331229109 82 1.20729721045912 84 -1.6715472983642528 86 1.6977875697405542 
		88 6.362971331229109 91 1.20729721045912 93 -1.6715472983642528 101 -10.011164173331293 
		106 0.6972322182932833 116 -1.2206533025799415 126 3.0405827598215973;
	setAttr -s 29 ".kit[1:28]"  9 3 3 10 3 10 10 3 
		9 3 9 3 9 3 9 3 9 3 9 3 9 3 9 1 3 
		3 3 3;
	setAttr -s 29 ".kot[1:28]"  9 3 3 10 3 10 10 1 
		9 3 9 1 9 3 9 1 9 3 9 1 9 3 9 1 3 
		3 3 3;
	setAttr -s 29 ".kix[24:28]"  1 1 1 1 1;
	setAttr -s 29 ".kiy[24:28]"  0 0 0 0 0;
	setAttr -s 29 ".kox[8:28]"  1 0.76518720388412476 1 0.81879156827926636 
		1 0.76518738269805908 1 0.81879174709320068 1 0.68906408548355103 1 0.81879174709320068 
		1 0.68906474113464355 1 0.76518696546554565 1 1 1 1 1;
	setAttr -s 29 ".koy[8:28]"  0 0.64380788803100586 0 -0.57409101724624634 
		0 0.64380759000778198 0 -0.57409077882766724 0 0.72470039129257202 0 -0.57409077882766724 
		0 0.72469979524612427 0 -0.64380812644958496 0 0 0 0 0;
createNode animCurveTA -n "char_RootCurveRoot1_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 29 ".ktv[0:28]"  0 23.714440424736864 7 50.848341100916294 
		10 58.650424024109292 16 -6.7303361891120099 29 5.4210062324398649 35 7.6414284327292519 
		42 12.14909252016105 46 5.0548353307408673 52 6.2305165535617961 56 -1.7016868149661837 
		57 -11.340317861220285 60 -0.93039941459812836 63 6.2305165535617961 66 -1.7016868149661837 
		68 -11.340317861220285 72 -0.93039941459812836 74 6.2305165535617961 77 -1.7016868149661837 
		78 -11.340317861220285 82 -0.93039941459812836 84 6.2305165535617961 86 -1.7016868149661837 
		88 -11.340317861220285 91 -0.93039941459812836 93 6.2305165535617961 101 6.6912892731543101 
		106 -14.496914338927146 116 14.199721120901422 126 23.714440424736864;
	setAttr -s 29 ".kit[1:28]"  9 3 3 10 3 10 10 3 
		10 3 10 3 10 3 10 3 10 3 10 3 10 3 10 1 3 
		3 3 3;
	setAttr -s 29 ".kot[1:28]"  9 3 3 10 3 10 10 1 
		10 3 10 1 10 3 10 1 10 3 10 1 10 3 10 1 3 
		3 3 3;
	setAttr -s 29 ".kix[24:28]"  1 1 1 1 1;
	setAttr -s 29 ".kiy[24:28]"  0 0 0 0 0;
	setAttr -s 29 ".kox[8:28]"  1 0.47751054167747498 1 0.54626482725143433 
		1 0.47751080989837646 1 0.54626506567001343 1 0.39872333407402039 1 0.54626506567001343 
		1 0.39872390031814575 1 0.47751027345657349 1 1 1 1 1;
	setAttr -s 29 ".koy[8:28]"  0 -0.87862598896026611 0 0.83761250972747803 
		0 -0.87862586975097656 0 0.8376123309135437 0 -0.91707128286361694 0 0.8376123309135437 
		0 -0.91707098484039307 0 0.87862610816955566 0 0 0 0 0;
createNode animCurveTA -n "char_RootCurveRoot1_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 29 ".ktv[0:28]"  0 8.6470827930312559 7 13.642760661643297 
		10 12.76379955322807 16 9.0627116356779993 29 -9.9277084918389438 35 -24.66202655716036 
		42 -18.582502455627814 46 -8.7276988959521322 52 -6.1283963592979713 56 -6.7139206348801821 
		57 -7.4598312110638894 60 -6.6227129585713884 63 -6.1283963592979713 66 -6.7139206348801821 
		68 -7.4598312110638894 72 -6.6227129585713884 74 -6.1283963592979713 77 -6.7139206348801821 
		78 -7.4598312110638894 82 -6.6227129585713884 84 -6.1283963592979713 86 -6.7139206348801821 
		88 -7.4598312110638894 91 -6.6227129585713884 93 -6.1283963592979713 101 -0.37309833028977379 
		106 -5.8703641604519721 116 8.7398639041563744 126 8.6470827930312559;
	setAttr -s 29 ".kit[2:28]"  9 9 10 3 10 10 3 9 
		3 9 3 9 3 9 3 9 3 9 3 9 3 9 1 3 3 
		3 3;
	setAttr -s 29 ".kot[2:28]"  9 9 10 3 10 10 1 9 
		3 9 1 9 3 9 1 9 3 9 1 9 3 9 1 3 3 
		3 3;
	setAttr -s 29 ".kix[24:28]"  1 1 1 1 1;
	setAttr -s 29 ".kiy[24:28]"  0 0 0 0 0;
	setAttr -s 29 ".kox[8:28]"  1 0.99041944742202759 1 0.99331748485565186 
		1 0.99041944742202759 1 0.99331760406494141 1 0.98514997959136963 1 0.99331760406494141 
		1 0.98514997959136963 1 0.99041944742202759 1 1 1 1 1;
	setAttr -s 29 ".koy[8:28]"  0 -0.13809175789356232 0 0.11541321128606796 
		0 -0.13809166848659515 0 0.11541315913200378 0 -0.17169643938541412 0 0.11541315913200378 
		0 -0.17169614136219025 0 0.13809186220169067 0 0 0 0 0;
createNode animCurveTL -n "char_RootCurveRoot1_M_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 -0.11500744677504726 7 -0.11500744677504726 
		10 -0.11500744677504726 16 -0.040637750135348594 29 -0.10102136455884542 35 -0.013161339761841855 
		38 0.020513699425597914 42 0.017527929796701133 46 -0.095824778823143358 52 -0.23716878372233668 
		57 -0.22127299540886144 63 -0.23716878372233668 68 -0.22127299540886144 74 -0.23716878372233668 
		78 -0.22127299540886144 84 -0.23716878372233668 88 -0.22127299540886144 93 -0.23716878372233668 
		101 -0.23541611299518517 106 -0.030140574327069597 116 -0.15777131929918853 126 -0.11500744677504726;
	setAttr -s 22 ".kit[4:21]"  10 3 10 10 10 3 3 3 
		3 3 3 3 3 1 3 3 3 3;
	setAttr -s 22 ".kot[4:21]"  10 3 10 10 10 1 3 1 
		3 1 3 1 3 3 3 3 3 3;
	setAttr -s 22 ".kix[17:21]"  1 1 1 1 1;
	setAttr -s 22 ".kiy[17:21]"  0 0 0 0 0;
	setAttr -s 22 ".kox[9:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[9:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_RootCurveRoot1_M_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 23 ".ktv[0:22]"  0 -0.26403992941414445 7 -0.51640203272429164 
		10 -0.59922763756356356 16 -0.089808235942299031 29 -0.089060051136837626 35 -0.19323880616657774 
		38 -0.12273668672423577 42 -0.11362340619071748 46 -0.097355629549113809 52 -0.094734488933527983 
		57 -0.094734488933527983 63 -0.094734488933527983 68 -0.094734488933527983 74 -0.094734488933527983 
		78 -0.094734488933527983 84 -0.094734488933527983 88 -0.094734488933527983 93 -0.094734488933527983 
		101 -0.16999863070834548 106 -0.16999863070834548 116 -0.38651038541786942 122 -0.23753502208745181 
		126 -0.26403992941414445;
	setAttr -s 23 ".kit[1:22]"  9 3 3 10 3 10 10 10 
		3 3 3 3 3 3 3 3 1 3 3 3 10 3;
	setAttr -s 23 ".kot[1:22]"  9 3 3 10 3 10 10 10 
		1 3 1 3 1 3 1 3 1 3 3 3 10 3;
	setAttr -s 23 ".kix[17:22]"  1 1 1 1 1 1;
	setAttr -s 23 ".kiy[17:22]"  0 0 0 0 0 0;
	setAttr -s 23 ".kox[9:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".koy[9:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_RootCurveRoot1_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 29 ".ktv[0:28]"  0 -0.0438000161016944 7 -0.17244812949150928 
		10 -0.0438000161016944 16 0.22524030889087515 29 -0.10469696192013081 35 -0.075432991798141946 
		42 -0.032188465818908579 46 -0.077969703031495169 52 -0.057445821214659881 56 -0.086517434045909475 
		57 -0.057445821214659881 60 -0.028344266676528895 63 -0.057445821214659881 66 -0.086517434045909475 
		68 -0.057445821214659881 72 -0.028344266676528895 74 -0.057445821214659881 77 -0.086517434045909475 
		78 -0.057445821214659881 82 -0.028344266676528895 84 -0.057445821214659881 86 -0.086517434045909475 
		88 -0.057445821214659881 91 -0.028344266676528895 93 -0.057445821214659881 101 -0.06980002904636555 
		106 0.064348872475064114 116 -0.023926585607869671 126 -0.0438000161016944;
	setAttr -s 29 ".kit[0:28]"  3 9 9 9 10 1 10 10 
		1 10 9 10 1 10 9 10 1 10 9 10 1 10 9 10 1 
		3 3 9 3;
	setAttr -s 29 ".kot[0:28]"  3 9 9 9 10 1 10 10 
		1 10 9 10 1 10 9 10 1 10 9 10 1 10 9 10 1 
		3 3 9 3;
	setAttr -s 29 ".kix[5:28]"  0.98157036304473877 1 1 0.97799414396286011 
		1 0.91656118631362915 1 0.96825140714645386 1 0.96020638942718506 1 0.95998537540435791 
		1 0.94414103031158447 1 0.96843016147613525 1 0.94414103031158447 1 0.87987023591995239 
		1 1 0.98709595203399658 1;
	setAttr -s 29 ".kiy[5:28]"  -0.19110068678855896 0 0 -0.20863229036331177 
		0 0.39989453554153442 0 -0.24997827410697937 0 0.27929118275642395 0 -0.28004994988441467 
		0 0.3295418918132782 0 -0.24928514659404755 0 0.3295418918132782 0 -0.47521409392356873 
		0 0 -0.16013003885746002 0;
	setAttr -s 29 ".kox[5:28]"  0.98157048225402832 1 1 0.97799420356750488 
		1 0.91656118631362915 1 0.96825152635574341 1 0.96020638942718506 1 0.95998543500900269 
		1 0.94414103031158447 1 0.96843016147613525 1 0.94414103031158447 1 0.87987023591995239 
		1 1 0.98709595203399658 1;
	setAttr -s 29 ".koy[5:28]"  -0.19110068678855896 0 0 -0.20863226056098938 
		0 0.39989453554153442 0 -0.24997824430465698 0 0.27929118275642395 0 -0.28004994988441467 
		0 0.3295418918132782 0 -0.24928514659404755 0 0.3295418918132782 0 -0.47521409392356873 
		0 0 -0.16013003885746002 0;
createNode animCurveTA -n "char_RootExtraRoot1_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_RootExtraRoot1_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_RootExtraRoot1_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_RootExtraRoot1_M_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_RootExtraRoot1_M_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_RootExtraRoot1_M_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Clavicle1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 116 1 126 1;
	setAttr -s 21 ".kit[16:20]"  1 3 3 3 3;
	setAttr -s 21 ".kot[8:20]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3;
	setAttr -s 21 ".kix[16:20]"  1 1 1 1 1;
	setAttr -s 21 ".kiy[16:20]"  0 0 0 0 0;
	setAttr -s 21 ".kox[8:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".koy[8:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Clavicle1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 116 1 126 1;
	setAttr -s 21 ".kit[16:20]"  1 3 3 3 3;
	setAttr -s 21 ".kot[8:20]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3;
	setAttr -s 21 ".kix[16:20]"  1 1 1 1 1;
	setAttr -s 21 ".kiy[16:20]"  0 0 0 0 0;
	setAttr -s 21 ".kox[8:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".koy[8:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Clavicle1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 116 1 126 1;
	setAttr -s 21 ".kit[16:20]"  1 3 3 3 3;
	setAttr -s 21 ".kot[8:20]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3;
	setAttr -s 21 ".kix[16:20]"  1 1 1 1 1;
	setAttr -s 21 ".kiy[16:20]"  0 0 0 0 0;
	setAttr -s 21 ".kox[8:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".koy[8:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 -6.5816496042071879 10 -6.5816496042071879 
		16 1.4142038530491636 25 0.55661099761670718 32 0 35 50.24821897937003 45 0 52 31.561278730344608 
		57 0 63 31.561278730344608 68 0 74 31.561278730344608 78 0 84 31.561278730344608 
		88 0 93 31.561278730344608 96 23.349556885150008 101 2.8413151463311519 106 -19.88397845950734 
		116 -4.7011650778091001 126 0;
	setAttr -s 22 ".kit[16:21]"  1 10 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 10 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 0.46966803073883057 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 -0.88284313678741455 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 0.46966803073883057 1 
		1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 -0.88284313678741455 
		0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 17.448374202433158 10 17.448374202433158 
		16 -45.835603936162428 25 -18.040257193659837 32 0 35 9.5412940342878318 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 96 -33.831064051437728 101 -46.167329797249245 
		106 -46.479265584792671 116 6.6242002369680799 126 0;
	setAttr -s 22 ".kit[16:21]"  1 10 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 10 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 0.31418687105178833 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 -0.94936114549636841 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 0.31418687105178833 1 
		1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 -0.94936114549636841 
		0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 -6.206212611641309 10 -6.206212611641309 
		16 -8.5125705408241004 25 -3.3504295514360867 32 0 35 10.725466967658141 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 96 0.6391821793913125 101 -4.60228074968866 
		106 17.055186015069314 116 -1.8518213409249207 126 0;
	setAttr -s 22 ".kit[16:21]"  1 10 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 10 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 2.1942103669999999e-008 7 2.1942103669999999e-008 
		10 2.1942103669999999e-008 16 2.1942103669999999e-008 25 2.1942103669999999e-008 
		32 2.1942103669999999e-008 35 2.1942103669999999e-008 45 2.1942103669999999e-008 
		52 2.1942103669999999e-008 57 2.1942103669999999e-008 63 2.1942103669999999e-008 
		68 2.1942103669999999e-008 74 2.1942103669999999e-008 78 2.1942103669999999e-008 
		84 2.1942103669999999e-008 88 2.1942103669999999e-008 93 2.1942103669999999e-008 
		101 2.1942103669999999e-008 106 2.1942103669999999e-008 110 2.1942103669999999e-008 
		116 2.1942103669999999e-008 126 2.1942103669999999e-008;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 1 12 1 18 1 23 1 49 1 57 1 60 1 63 1 
		68 1 72 1 74 1 78 1 82 1 84 1 88 1 91 1 93 1 101 1 104 1 111 1 126 1;
	setAttr -s 21 ".kit[4:20]"  1 3 1 3 3 1 3 3 
		1 3 3 1 1 3 3 3 3;
	setAttr -s 21 ".kot[4:20]"  1 3 1 1 3 1 1 3 
		1 1 3 1 1 3 3 3 3;
	setAttr -s 21 ".kix[4:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".kiy[4:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 21 ".kox[4:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".koy[4:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 1 12 1 18 1 23 1 49 1 57 1 60 1 63 1 
		68 1 72 1 74 1 78 1 82 1 84 1 88 1 91 1 93 1 101 1 104 1 111 1 126 1;
	setAttr -s 21 ".kit[4:20]"  1 3 1 3 3 1 3 3 
		1 3 3 1 1 3 3 3 3;
	setAttr -s 21 ".kot[4:20]"  1 3 1 1 3 1 1 3 
		1 1 3 1 1 3 3 3 3;
	setAttr -s 21 ".kix[4:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".kiy[4:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 21 ".kox[4:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".koy[4:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 1 12 1 18 1 23 1 49 1 57 1 60 1 63 1 
		68 1 72 1 74 1 78 1 82 1 84 1 88 1 91 1 93 1 101 1 104 1 111 1 126 1;
	setAttr -s 21 ".kit[4:20]"  1 3 1 3 3 1 3 3 
		1 3 3 1 1 3 3 3 3;
	setAttr -s 21 ".kot[4:20]"  1 3 1 1 3 1 1 3 
		1 1 3 1 1 3 3 3 3;
	setAttr -s 21 ".kix[4:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".kiy[4:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 21 ".kox[4:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".koy[4:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Shoulder1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 28 ".ktv[0:27]"  0 -0.68127875452050601 8 -17.886440483680762 
		12 -0.68127875452050601 15 27.729508635278361 18 30.405207492733581 23 -13.685685958450868 
		29 -35.857981823432468 34 -46.168009771125732 39 -30.331811797995389 49 22.862385925206034 
		57 -30.847779243131797 60 22.862385925206034 63 22.862385925206034 68 -30.847779243131797 
		72 22.862385925206034 74 22.862385925206034 78 -30.847779243131797 82 22.862385925206034 
		84 22.862385925206034 88 -30.847779243131797 91 22.862385925206034 93 22.862385925206034 
		96 8.7000650614715056 101 -22.494081754705494 104 -2.2167325814973728 111 -5.4132241998002977 
		118 -32.173052089993725 126 -0.68127875452050601;
	setAttr -s 28 ".kit[1:27]"  10 3 10 3 3 10 10 10 
		1 3 1 3 3 1 3 3 1 3 3 1 1 10 3 3 3 
		10 3;
	setAttr -s 28 ".kot[1:27]"  10 3 10 3 3 10 10 10 
		1 3 1 1 3 1 1 3 1 1 3 1 1 10 3 3 3 
		10 3;
	setAttr -s 28 ".kix[9:27]"  1 1 1 1 1 1 1 1 1 1 1 1 1 0.31923586130142212 
		1 1 1 0.98663133382797241 1;
	setAttr -s 28 ".kiy[9:27]"  0 0 0 0 0 0 0 0 0 0 0 0 0 -0.94767528772354126 
		0 0 0 0.16296795010566711 0;
	setAttr -s 28 ".kox[9:27]"  1 1 1 1 1 1 1 1 1 1 1 1 1 0.31923586130142212 
		1 1 1 0.98663133382797241 1;
	setAttr -s 28 ".koy[9:27]"  0 0 0 0 0 0 0 0 0 0 0 0 0 -0.94767528772354126 
		0 0 0 0.16296795010566711 0;
createNode animCurveTA -n "char_FKExtraR_Shoulder1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Shoulder1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Shoulder1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 23 ".ktv[0:22]"  0 1 12 1 15 1 20 1 34 1 44 1 51 1 57 1 
		60 1 63 1 68 1 72 1 74 1 78 1 82 1 84 1 88 1 91 1 93 1 101 1 104 1 111 1 126 1;
	setAttr -s 23 ".kit[6:22]"  1 3 1 3 3 1 3 3 
		1 3 3 1 1 3 3 3 3;
	setAttr -s 23 ".kot[6:22]"  1 3 1 1 3 1 1 3 
		1 1 3 1 1 3 3 3 3;
	setAttr -s 23 ".kix[6:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".kiy[6:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 23 ".kox[6:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".koy[6:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 23 ".ktv[0:22]"  0 1 12 1 15 1 20 1 34 1 44 1 51 1 57 1 
		60 1 63 1 68 1 72 1 74 1 78 1 82 1 84 1 88 1 91 1 93 1 101 1 104 1 111 1 126 1;
	setAttr -s 23 ".kit[6:22]"  1 3 1 3 3 1 3 3 
		1 3 3 1 1 3 3 3 3;
	setAttr -s 23 ".kot[6:22]"  1 3 1 1 3 1 1 3 
		1 1 3 1 1 3 3 3 3;
	setAttr -s 23 ".kix[6:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".kiy[6:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 23 ".kox[6:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".koy[6:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 23 ".ktv[0:22]"  0 1 12 1 15 1 20 1 34 1 44 1 51 1 57 1 
		60 1 63 1 68 1 72 1 74 1 78 1 82 1 84 1 88 1 91 1 93 1 101 1 104 1 111 1 126 1;
	setAttr -s 23 ".kit[6:22]"  1 3 1 3 3 1 3 3 
		1 3 3 1 1 3 3 3 3;
	setAttr -s 23 ".kot[6:22]"  1 3 1 1 3 1 1 3 
		1 1 3 1 1 3 3 3 3;
	setAttr -s 23 ".kix[6:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".kiy[6:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 23 ".kox[6:22]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 23 ".koy[6:22]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Elbow1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 32 ".ktv[0:31]"  0 48.213367515818511 4 70.072384137860766 
		12 -8.053570689231174 15 -8.053570689231174 20 68.680803157720689 29 17.353017381652215 
		34 131.51152580250866 36 133.22190707708208 41 31.93382626207838 44 14.800061043163449 
		51 121.78899175438896 56 31.93382626207838 57 14.800061043163449 60 99.095246886995213 
		63 99.095246886995213 66 31.93382626207838 68 14.800061043163449 72 99.095246886995213 
		74 99.095246886995213 77 31.93382626207838 78 14.800061043163449 82 99.095246886995213 
		84 99.095246886995213 86 31.93382626207838 88 14.800061043163449 91 99.095246886995213 
		93 99.095246886995213 101 30.410767690769152 104 37.952771984507159 111 71.575986952271876 
		118 47.586611293142276 126 48.213367515818511;
	setAttr -s 32 ".kit[1:31]"  10 3 3 3 10 3 10 10 
		3 1 10 3 1 3 10 3 1 3 10 3 1 3 10 3 1 
		1 3 3 3 10 3;
	setAttr -s 32 ".kot[1:31]"  10 3 3 3 10 3 10 10 
		3 1 10 3 1 1 10 3 1 1 10 3 1 1 10 3 1 
		1 3 3 3 10 3;
	setAttr -s 32 ".kix[10:31]"  1 0.10649685561656952 1 1 1 0.1125640869140625 
		1 1 1 0.090257219970226288 1 1 1 0.09025738388299942 1 1 1 1 1 1 1 1;
	setAttr -s 32 ".kiy[10:31]"  0 -0.99431306123733521 0 0 0 -0.99364447593688965 
		0 0 0 -0.99591845273971558 0 0 0 -0.99591845273971558 0 0 0 0 0 0 0 0;
	setAttr -s 32 ".kox[10:31]"  1 0.10649685561656952 1 1 1 0.1125640869140625 
		1 1 1 0.090257219970226288 1 1 1 0.09025738388299942 1 1 1 1 1 1 1 1;
	setAttr -s 32 ".koy[10:31]"  0 -0.99431306123733521 0 0 0 -0.99364447593688965 
		0 0 0 -0.99591845273971558 0 0 0 -0.99591845273971558 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Elbow1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Elbow1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Elbow1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveDevice3_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 1 7 1 10 1 18 1 34 1 50 1 64 1 78 1 106 
		1 110 1 116 1 126 1;
	setAttr -s 12 ".kit[3:11]"  1 10 10 10 10 3 3 3 
		3;
	setAttr -s 12 ".kot[3:11]"  1 10 1 1 1 3 3 3 
		3;
	setAttr -s 12 ".kix[3:11]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[3:11]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[3:11]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[3:11]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveDevice3_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 1 7 1 10 1 18 1 34 1 50 1 64 1 78 1 106 
		1 110 1 116 1 126 1;
	setAttr -s 12 ".kit[3:11]"  1 10 10 10 10 3 3 3 
		3;
	setAttr -s 12 ".kot[3:11]"  1 10 1 1 1 3 3 3 
		3;
	setAttr -s 12 ".kix[3:11]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[3:11]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[3:11]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[3:11]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveDevice3_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 1 7 1 10 1 18 1 34 1 50 1 64 1 78 1 106 
		1 110 1 116 1 126 1;
	setAttr -s 12 ".kit[3:11]"  1 10 10 10 10 3 3 3 
		3;
	setAttr -s 12 ".kot[3:11]"  1 10 1 1 1 3 3 3 
		3;
	setAttr -s 12 ".kix[3:11]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[3:11]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[3:11]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[3:11]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveDevice3_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 89 ".ktv[0:88]"  17 -83.798780827240449 18 -88.053957993486719 
		19 -139.42946874503582 20 -130.54786611578845 21 -118.17855081511713 22 -113.86838287890599 
		23 -116.21671591993848 24 -125.02768377000176 25 -132.06177367857887 26 -145.73339155413629 
		27 -164.36254901685191 28 -177.33424331084677 29 -178.79764256658476 30 -165.30339917125372 
		31 -149.05249539781261 32 -154.5026071722607 33 -37.575399390330958 34 -75.539379562897011 
		35 -250.55999360785435 36 -224.6527561839965 37 -194.19863401684606 38 -157.72416246164593 
		39 -136.26773389318549 40 -133.43963237243619 41 -131.47012051681753 42 -129.78926431457745 
		43 -129.74081553327261 44 -122.44256352114314 45 -118.01495841391304 46 -130.00540020155492 
		47 -149.73743297767666 48 -32.644901501869413 49 -83.888899703247574 50 -264.34178541626045 
		51 -258.01062876633029 52 -67.305945608685505 53 -49.342958499891317 54 4.663095449356617 
		55 -116.85779106590903 56 -109.01500065348651 57 -104.93808409420647 58 -104.65919729995925 
		59 -19.074697896079304 60 -253.038386029484 61 -269.96770957290477 62 -264.15448587977545 
		63 -258.12266697111215 64 -75.996278820357418 65 -74.291940171797577 66 -105.14024806001987 
		67 -108.42322257390526 68 -105.62831954110062 69 -100.02348954706264 70 -115.05085334998988 
		71 -69.731445642099317 72 -268.87792891759312 73 -262.50016619933444 74 -255.92224842728763 
		75 -69.802662074004004 76 -49.899470090637202 77 -116.68415114030734 78 -108.13006808201551 
		79 -103.79989549372486 80 -120.81798532896825 81 -46.835656665862771 82 -249.46870453670141 
		83 -265.02114131854177 84 -252.48633674851402 85 -72.819519432750297 86 -88.439161231469996 
		87 -100.38711684930662 88 -110.68543087539499 89 -115.40085695778112 90 -33.198566164227913 
		91 -245.16513165643181 92 -81.239183785729253 93 -249.67043213607423 94 -254.25178163752759 
		95 76.694965331788751 96 9.3112235840298379 97 -32.51902033525127 98 -42.233906363209222 
		99 -32.713714392805159 100 -13.696826092033959 101 -181.12365141880562 102 -189.72685485888314 
		103 -119.40264481292225 104 -181.08672394566238 105 -83.665345993799605;
createNode animCurveTA -n "char_FKCurveDevice3_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 89 ".ktv[0:88]"  17 -0.15209529104924274 18 -1.9470399497256088 
		19 -2.3523713550073246 20 10.377709553132105 21 6.8710756096639463 22 8.5506783940473063 
		23 13.931714459003567 24 10.402900485938547 25 -4.1370872018827489 26 -18.472069619689897 
		27 -24.401061805497999 28 -20.644460802692667 29 -13.031374427169203 30 -4.4919124684020639 
		31 15.043208666371443 32 44.269081616761397 33 123.1561455224176 34 149.11303492736826 
		35 16.395440526690983 36 19.118054530613509 37 34.496513249648828 38 45.728746664325058 
		39 41.35460270898988 40 37.807056364855065 41 32.956323016473597 42 21.355000129960544 
		43 7.6607709090228564 44 5.5830887723074705 45 12.194945445026658 46 22.523949910487133 
		47 44.468972083987666 48 113.18172373401555 49 143.11690611571436 50 5.6608191010104294 
		51 -0.29202631206001772 52 162.46112510218828 53 133.9455226074372 54 109.96899995280637 
		55 57.179365259699928 56 40.213004889533451 57 -17.187968605005246 58 -0.1269108387116776 
		59 115.07783226134814 60 13.09765318522968 61 4.37333009005014 62 8.7446256236496076 
		63 12.775010018052988 64 147.55774176617462 65 107.73550179378097 66 70.210952696352379 
		67 47.639693562433976 68 -14.679305794546941 69 -2.3717407004804514 70 42.340745070543697 
		71 154.41115650981428 72 -6.5921983744937984 73 0.87779138822789604 74 8.2608530131830911 
		75 149.69472984500635 76 110.03019773671031 77 59.021638167674944 78 -10.6153972576573 
		79 1.021665490271277 80 42.62461775734964 81 136.08845317501658 82 3.0759138642639003 
		83 -2.0079872743687028 84 4.2595216680574159 85 146.2069837588576 86 98.419158284617708 
		87 32.457093585000301 88 -2.9942552187610065 89 12.710668995259761 90 131.43851660900413 
		91 -2.8330249545801989 92 188.74530705239721 93 -2.6528258553144113 94 20.202083419132723 
		95 56.99161351194104 96 63.922748704159154 97 51.588162870306434 98 19.468289751707516 
		99 -17.842239342064286 100 -46.187813539137927 101 -121.97205479895383 102 -110.05225199689626 
		103 -85.319619378552304 104 -67.106717298446341 105 -0.67250980006146299;
createNode animCurveTA -n "char_FKCurveDevice3_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 89 ".ktv[0:88]"  17 -4.6558253190878789 18 296.7994991235073 
		19 249.3141552412109 20 241.47633381577336 21 -130.98396908091337 22 -155.25271332403238 
		23 -181.25279222670824 24 -200.93746346818159 25 -210.54971047741972 26 -215.61476295120832 
		27 -216.89326665221242 28 -223.27588674447406 29 -240.34290550959176 30 -275.37517170780825 
		31 -326.06774005560027 32 -386.98017614403193 33 -316.08197557377287 34 -395.67816342090566 
		35 -257.76415494755497 36 -289.90700919110117 37 -312.23094188882942 38 -309.72299162634374 
		39 -304.51865584202295 40 -667.09556166924017 41 -664.8926231945444 42 -663.77417100160824 
		43 -675.54525599398835 44 -701.43885435381651 45 -738.20090768262139 46 -783.61632529288022 
		47 -835.32273338764901 48 -757.52499712567635 49 -850.77257550352886 50 -713.12296867264115 
		51 -744.12614211635582 52 -951.01656110392059 53 -972.29618907058602 54 -950.12435429660047 
		55 -1095.5149949079369 56 -1110.1918026673068 57 -1118.3277120546511 58 -1168.1993703638925 
		59 -1129.9442976690589 60 -1038.3323467368921 61 -1070.6938067645565 62 -1098.4808377606967 
		63 -1126.1764799729565 64 -1333.4641194533449 65 -1354.4308512089335 66 -1404.0245407219329 
		67 -1432.8278007512747 68 -1445.2210874977416 69 -1484.8417756432696 70 -1540.7256067456017 
		71 -1531.0494291450302 72 -1387.4263609501897 73 -1408.6615924680157 74 -1429.4889612120235 
		75 -1629.0511285876617 76 -1627.3202589877151 77 -1706.6766365078965 78 -1700.30681687017 
		79 -1735.6329462644937 80 -1789.7696305946811 81 -1748.2147471214976 82 -1618.8659124745918 
		83 -1637.4873378913876 84 -1650.9954596475472 85 -1852.176584771817 86 -1866.42176494042 
		87 -1881.9869403520634 88 -1895.7834241839107 89 -1932.8820740890105 90 -1889.8865256190204 
		91 -1770.0379359797878 92 -1962.9849440716541 93 -1790.0099937776092 94 -1816.0672339355922 
		95 -1877.6852035425754 96 -1982.9664099294218 97 -2062.5995794900782 98 -2110.4408192583105 
		99 -1780.7834129229886 100 -1808.1980389456307 101 -2005.7543132185117 102 -2006.7181306189943 
		103 -2090.4359322011492 104 -2040.1932764589003 105 -2.2281180456855405;
createNode animCurveTL -n "char_FKCurveDevice3_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 89 ".ktv[0:88]"  17 0.070796223027113955 18 -0.11337724510903087 
		19 -0.66538700034893461 20 -1.9256405909131349 21 -2.2967566946716134 22 -2.7249218646427402 
		23 -3.1674296798146742 24 -3.566453997279643 25 -3.4715058131034593 26 -2.4211236670470213 
		27 -0.62203506239109529 28 1.1030291389835174 29 2.1500115487772207 30 1.5960020464670479 
		31 -0.64736533973646249 32 -2.6285286443750571 33 -2.5682994474659093 34 -0.43055201803301479 
		35 0.71819555080069308 36 0.85488257568077752 37 -0.029379782360087814 38 -2.4734095893065358 
		39 -4.4789662184929746 40 -4.8293873020839433 41 -3.4455511356608213 42 -0.53504586913028795 
		43 1.8460495591370827 44 2.5706570998867573 45 1.9701949951295294 46 0.32816560040721665 
		47 -1.3377511326435381 48 -2.2322305378961804 49 -2.0104489855972587 50 -1.499483982136959 
		51 -1.6635665045194552 52 -2.1805901740577829 53 -2.4056650434924514 54 -2.305613758618986 
		55 -1.6721236892754685 56 -0.77809829699802102 57 2.1346119611924328 58 -0.18773555085133808 
		59 -1.9775494278003318 60 -0.032922756174469936 61 0.11550434983382682 62 -0.16648731555648344 
		63 -0.40574108759763478 64 -0.49539204965025052 65 -0.17263048023953548 66 0.32532096827301937 
		67 0.24121030406889915 68 2.0686457997910761 69 0.72948499582675441 70 -1.4380921532389475 
		71 -0.12615273582240799 72 0.58161716550051801 73 0.092691763649199815 74 -0.34965955475347016 
		75 -0.58500606580628123 76 -0.54274913016547877 77 -0.06978967761988808 78 1.9390623073046906 
		79 0.71946223116447161 80 -1.1146023131152794 81 -0.91315936441720402 82 0.49122144398553419 
		83 0.20588870884542276 84 -0.25827069712333367 85 0.52625007904846111 86 1.2315621049470313 
		87 1.9388021535425739 88 1.7490642640301666 89 0.11754781207408804 90 -0.86095678115395702 
		91 0.31949565754306297 92 0.12673539184623064 93 -0.15300523058903309 94 1.370941042336665 
		95 3.1893612508700713 96 1.9766882156401908 97 -0.46235678481659681 98 -2.3783245511869748 
		99 -2.5130348579303678 100 -1.5228217490687781 101 -0.86306792032332869 102 -0.51569187795267246 
		103 -0.20814760023750911 104 -0.059652582503389562 105 0.0651373538492801;
createNode animCurveTL -n "char_FKCurveDevice3_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 89 ".ktv[0:88]"  17 0.0024602716719113347 18 0.0331106920947856 
		19 0.15727471169342411 20 0.39072162004943445 21 0.053792351391671156 22 -0.037362827594156656 
		23 0.12175536039736801 24 -0.44907941204092261 25 -2.1643555011400872 26 -4.022973448585776 
		27 -5.2176611457545805 28 -5.542483383813833 29 -5.5074259821064189 30 -5.6694448329072644 
		31 -5.0870177254335314 32 -2.9799784867492534 33 -0.13531877120222655 34 1.012389878073787 
		35 2.0331089098120492 36 4.4392914666858037 37 5.9160819379096612 38 5.5363190424297199 
		39 3.8112009598642338 40 1.4225050521775444 41 -1.8059351900793152 42 -4.2394326219790166 
		43 -4.5332547193566821 44 -3.6977688087004976 45 -3.3779375600775632 46 -4.337978367155614 
		47 -4.6842172505674053 48 -3.3182960365967409 49 -1.3324829517165679 50 0.33433232156576709 
		51 1.3161255011632123 52 1.7383116283069027 53 1.728497719138272 54 0.76953814880648808 
		55 -0.80329330231033647 56 -1.9648787366015621 57 -1.4441249604737632 58 -1.6459575864143867 
		59 1.1652541852889451 60 1.6111792497789643 61 -0.380498609565952 62 0.29350434490045013 
		63 0.93935809090441358 64 0.75429954310736158 65 -0.48984015191068631 66 -1.8578733898936732 
		67 -2.240957383576498 68 -1.2843345138247493 69 -0.82438727755359409 70 -0.2258894243707196 
		71 1.2529615281901121 72 -0.65744943065151296 73 0.10988518934245203 74 0.74076713297603691 
		75 0.82024359002617631 76 -0.17681476309726651 77 -1.4972602630367815 78 -1.0592415138825868 
		79 -0.67122076566417654 80 -0.13530679273913357 81 1.3604721147505672 82 0.89998979312347083 
		83 -0.68268525178698136 84 0.49057964002412391 85 0.29951099009100235 86 -1.2028278873861338 
		87 -0.87120455815422215 88 -0.77029765410416662 89 -0.83139394742402573 90 0.71480691843663535 
		91 0.64398376629942367 92 -0.70924843372746682 93 0.23028933693968281 94 0.11719721582278719 
		95 1.6410802969691567 96 3.4664049789577325 97 3.425554978333702 98 1.4765557797140001 
		99 -0.80036977943036458 100 -1.7879226225269382 101 -1.6502809059347379 102 -1.172616091355398 
		103 -0.61011866313576668 104 -0.023729343773787548 105 0.012043036141756946;
createNode animCurveTL -n "char_FKCurveDevice3_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 89 ".ktv[0:88]"  17 0.20119425626585011 18 -0.13088648637229772 
		19 -0.44688154667648838 20 -0.094095118537363354 21 0.29725329927791577 22 0.45020714675960943 
		23 0.57182564176204198 24 0.8403548033267767 25 1.0326928578773547 26 0.84790703055466043 
		27 0.40354022096795006 28 0.052983247339828954 29 0.095272517402212542 30 1.1443718905836908 
		31 2.9172466832391031 32 4.2406527557125493 33 5.2440618890445396 34 5.9162506238888239 
		35 5.76374026792503 36 4.2247928057938564 37 1.723810268385614 38 0.60280516397915629 
		39 1.7153602496968039 40 3.7653832210349507 41 5.2473187102236611 42 5.2921687873909686 
		43 5.0150019970448501 44 5.513618218782371 45 5.9842899695774667 46 5.6188638387117358 
		47 5.0970060047865537 48 5.7710564323548112 49 6.6042891713558438 50 6.8765805821525143 
		51 6.7071332189802035 52 6.4376722120552508 53 6.3777593612984234 54 6.6853786053858579 
		55 7.0042291065075784 56 6.9815672990551132 57 6.8414937819600219 58 6.8869668828738089 
		59 6.5545942494007869 60 6.8216392947783682 61 6.9987954094724714 62 6.9809916794633375 
		63 6.8883659186538013 64 6.8973061338905195 65 7.0101415425514579 66 6.8456672078228555 
		67 6.651038053505367 68 6.5383350699405476 69 6.6922769362706491 70 6.4021834731304166 
		71 6.43854748632039 72 6.491530957470296 73 6.4799650473659263 74 6.3616774176680968 
		75 6.2807223315453333 76 6.3569500202832874 77 6.198416581600414 78 5.91347625749661 
		79 6.0057633737875529 80 5.7340788397784124 81 5.523040706428227 82 5.6491693443311553 
		83 5.6073742420539396 84 5.5227389909762401 85 5.5224803862947232 86 5.3644442788154159 
		87 5.1206034704703178 88 4.9849622762366836 89 4.9630187128375338 90 4.6990258972605394 
		91 4.7351369334802795 92 4.6329395477015884 93 4.5658497101490072 94 4.3624462591515769 
		95 2.6433831745000611 96 0.54649014660934958 97 -0.73156695261129223 98 -1.1481765083443329 
		99 -0.35319378716625582 100 0.58704817538311527 101 0.79870356763058514 102 0.5671978579896968 
		103 0.31443861186942834 104 0.20259041078451834 105 0.20781400077361423;
createNode animCurveTU -n "char_FKExtraDevice3_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKExtraDevice3_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKExtraDevice3_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraDevice3_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraDevice3_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraDevice3_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKExtraDevice3_L_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKExtraDevice3_L_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_FKExtraDevice3_L_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb5_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 11 1 13 1 17 1 25 1 32 1 35 1 45 1 
		52 1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb5_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 11 1 13 1 17 1 25 1 32 1 35 1 45 1 
		52 1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb5_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 11 1 13 1 17 1 25 1 32 1 35 1 45 1 
		52 1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb5_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 64.163191954635607 11 64.163191954635607 
		13 64.163191954635607 17 31.322407729170752 25 25.093462510544875 32 47.195393689517566 
		35 47.195393689517566 45 47.195393689517566 52 47.195393689517566 57 47.195393689517566 
		63 47.195393689517566 68 47.195393689517566 74 47.195393689517566 78 47.195393689517566 
		84 47.195393689517566 88 47.195393689517566 93 47.195393689517566 101 19.577495863468304 
		106 19.577495863468304 110 64.163191954635607 116 64.163191954635607 126 64.163191954635607;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb5_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 2.4325234183121345 11 2.4325234183121345 
		13 2.4325234183121345 17 -25.103417923348566 25 6.2940062737167501 32 -22.521053759754132 
		35 -22.521053759754132 45 -22.521053759754132 52 -22.521053759754132 57 -22.521053759754132 
		63 -22.521053759754132 68 -22.521053759754132 74 -22.521053759754132 78 -22.521053759754132 
		84 -22.521053759754132 88 -22.521053759754132 93 -22.521053759754132 101 -13.081323569139558 
		106 -13.081323569139558 110 2.4325234183121345 116 2.4325234183121345 126 2.4325234183121345;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb5_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 8.5957802944005888 11 8.5957802944005888 
		13 8.5957802944005888 17 -17.617574901281333 25 4.3096208225361243 32 62.535234117967207 
		35 62.535234117967207 45 62.535234117967207 52 62.535234117967207 57 62.535234117967207 
		63 62.535234117967207 68 62.535234117967207 74 62.535234117967207 78 62.535234117967207 
		84 62.535234117967207 88 62.535234117967207 93 62.535234117967207 101 6.5278009465040476 
		106 6.5278009465040476 110 8.5957802944005888 116 8.5957802944005888 126 8.5957802944005888;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb5_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb5_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb5_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb6_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 11 1 13 1 17 1 25 1 32 1 35 1 45 1 
		52 1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb6_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 11 1 13 1 17 1 25 1 32 1 35 1 45 1 
		52 1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb6_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 11 1 13 1 17 1 25 1 32 1 35 1 45 1 
		52 1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb6_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 30.907503992135247 11 30.907503992135247 
		13 30.907503992135247 17 47.665721220661005 25 8.7274997155215761 32 38.917569590418282 
		35 38.917569590418282 45 38.917569590418282 52 38.917569590418282 57 38.917569590418282 
		63 38.917569590418282 68 38.917569590418282 74 38.917569590418282 78 38.917569590418282 
		84 38.917569590418282 88 38.917569590418282 93 38.917569590418282 101 -23.377835408669196 
		106 -23.377835408669196 110 30.907503992135247 116 30.907503992135247 126 30.907503992135247;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb6_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 -37.423813770375673 11 -37.423813770375673 
		13 -37.423813770375673 17 -48.872799380007528 25 -37.227950256389114 32 -10.177587185512857 
		35 -10.177587185512857 45 -10.177587185512857 52 -10.177587185512857 57 -10.177587185512857 
		63 -10.177587185512857 68 -10.177587185512857 74 -10.177587185512857 78 -10.177587185512857 
		84 -10.177587185512857 88 -10.177587185512857 93 -10.177587185512857 101 -46.045372386727109 
		106 -46.045372386727109 110 -37.423813770375673 116 -37.423813770375673 126 -37.423813770375673;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb6_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 -55.763523784114774 11 -55.763523784114774 
		13 -55.763523784114774 17 -46.704734005518844 25 -19.089662620095979 32 33.651281382517972 
		35 33.651281382517972 45 33.651281382517972 52 33.651281382517972 57 33.651281382517972 
		63 33.651281382517972 68 33.651281382517972 74 33.651281382517972 78 33.651281382517972 
		84 33.651281382517972 88 33.651281382517972 93 33.651281382517972 101 -7.0708495436256191 
		106 -7.0708495436256191 110 -55.763523784114774 116 -55.763523784114774 126 -55.763523784114774;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb6_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb6_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb6_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle5_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 11 1 13 1 17 1 25 1 32 1 35 1 45 1 
		52 1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle5_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 11 1 13 1 17 1 25 1 32 1 35 1 45 1 
		52 1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle5_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 11 1 13 1 17 1 25 1 32 1 35 1 45 1 
		52 1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle5_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 65.894016206888068 11 65.894016206888068 
		13 65.894016206888068 17 26.278830210474641 25 31.231644985760397 32 102.87706092817879 
		35 102.87706092817879 45 102.87706092817879 52 102.87706092817879 57 102.87706092817879 
		63 102.87706092817879 68 102.87706092817879 74 102.87706092817879 78 102.87706092817879 
		84 102.87706092817879 88 102.87706092817879 93 102.87706092817879 101 7.917651468953836 
		106 7.917651468953836 110 65.894016206888068 116 65.894016206888068 126 65.894016206888068;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle5_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 18.465908619718412 11 18.465908619718412 
		13 18.465908619718412 17 -4.3854201932003489 25 10.145307262730523 32 35.825603667393516 
		35 35.825603667393516 45 35.825603667393516 52 35.825603667393516 57 35.825603667393516 
		63 35.825603667393516 68 35.825603667393516 74 35.825603667393516 78 35.825603667393516 
		84 35.825603667393516 88 35.825603667393516 93 35.825603667393516 101 2.9372518458680337 
		106 2.9372518458680337 110 18.465908619718412 116 18.465908619718412 126 18.465908619718412;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle5_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 -36.952741198413079 11 -36.952741198413079 
		13 -36.952741198413079 17 -28.221519678895429 25 -12.256297664343803 32 -12.149249537764412 
		35 -12.149249537764412 45 -12.149249537764412 52 -12.149249537764412 57 -12.149249537764412 
		63 -12.149249537764412 68 -12.149249537764412 74 -12.149249537764412 78 -12.149249537764412 
		84 -12.149249537764412 88 -12.149249537764412 93 -12.149249537764412 101 -11.458884576644754 
		106 -11.458884576644754 110 -36.952741198413079 116 -36.952741198413079 126 -36.952741198413079;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle5_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle5_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle5_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle6_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 11 1 13 1 17 1 25 1 32 1 35 1 45 1 
		52 1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle6_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 11 1 13 1 17 1 25 1 32 1 35 1 45 1 
		52 1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle6_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 11 1 13 1 17 1 25 1 32 1 35 1 45 1 
		52 1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle6_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 17.446522746060875 11 17.446522746060875 
		13 17.446522746060875 17 -19.535334140422016 25 7.8132767495266506 32 40.758787718516473 
		35 40.758787718516473 45 40.758787718516473 52 40.758787718516473 57 40.758787718516473 
		63 40.758787718516473 68 40.758787718516473 74 40.758787718516473 78 40.758787718516473 
		84 40.758787718516473 88 40.758787718516473 93 40.758787718516473 101 -12.059648910365372 
		106 -12.059648910365372 110 17.446522746060875 116 17.446522746060875 126 17.446522746060875;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle6_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 11 0 13 0 17 0.98203309144991502 25 
		0 32 -3.2113782589535242 35 -3.2113782589535242 45 -3.2113782589535242 52 -3.2113782589535242 
		57 -3.2113782589535242 63 -3.2113782589535242 68 -3.2113782589535242 74 -3.2113782589535242 
		78 -3.2113782589535242 84 -3.2113782589535242 88 -3.2113782589535242 93 -3.2113782589535242 
		101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle6_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 11 0 13 0 17 -24.620822146455318 25 
		0 32 -2.615746753355499 35 -2.615746753355499 45 -2.615746753355499 52 -2.615746753355499 
		57 -2.615746753355499 63 -2.615746753355499 68 -2.615746753355499 74 -2.615746753355499 
		78 -2.615746753355499 84 -2.615746753355499 88 -2.615746753355499 93 -2.615746753355499 
		101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle6_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle6_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle6_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 29 ".ktv[0:28]"  0 1 12 1 15 1 18 1 20 1 32 1 44 1 51 1 
		57 1 60 1 61 1 63 1 68 1 71 1 72 1 74 1 78 1 82 1 83 1 84 1 88 1 91 1 92 1 93 1 101 
		1 104 1 111 1 116 1 126 1;
	setAttr -s 29 ".kit[7:28]"  1 3 10 1 3 3 10 1 
		3 3 10 1 3 3 10 1 1 3 3 3 3 3;
	setAttr -s 29 ".kot[7:28]"  1 3 10 1 1 3 10 1 
		1 3 10 1 1 3 10 1 1 3 3 3 3 3;
	setAttr -s 29 ".kix[7:28]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1 1;
	setAttr -s 29 ".kiy[7:28]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0 0;
	setAttr -s 29 ".kox[7:28]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1 1;
	setAttr -s 29 ".koy[7:28]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0 0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 29 ".ktv[0:28]"  0 1 12 1 15 1 18 1 20 1 32 1 44 1 51 1 
		57 1 60 1 61 1 63 1 68 1 71 1 72 1 74 1 78 1 82 1 83 1 84 1 88 1 91 1 92 1 93 1 101 
		1 104 1 111 1 116 1 126 1;
	setAttr -s 29 ".kit[7:28]"  1 3 10 1 3 3 10 1 
		3 3 10 1 3 3 10 1 1 3 3 3 3 3;
	setAttr -s 29 ".kot[7:28]"  1 3 10 1 1 3 10 1 
		1 3 10 1 1 3 10 1 1 3 3 3 3 3;
	setAttr -s 29 ".kix[7:28]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1 1;
	setAttr -s 29 ".kiy[7:28]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0 0;
	setAttr -s 29 ".kox[7:28]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1 1;
	setAttr -s 29 ".koy[7:28]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0 0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 29 ".ktv[0:28]"  0 1 12 1 15 1 18 1 20 1 32 1 44 1 51 1 
		57 1 60 1 61 1 63 1 68 1 71 1 72 1 74 1 78 1 82 1 83 1 84 1 88 1 91 1 92 1 93 1 101 
		1 104 1 111 1 116 1 126 1;
	setAttr -s 29 ".kit[7:28]"  1 3 10 1 3 3 10 1 
		3 3 10 1 3 3 10 1 1 3 3 3 3 3;
	setAttr -s 29 ".kot[7:28]"  1 3 10 1 1 3 10 1 
		1 3 10 1 1 3 10 1 1 3 3 3 3 3;
	setAttr -s 29 ".kix[7:28]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1 1;
	setAttr -s 29 ".kiy[7:28]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0 0;
	setAttr -s 29 ".kox[7:28]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1 1;
	setAttr -s 29 ".koy[7:28]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0 0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 40 ".ktv[0:39]"  0 0 12 0 15 0 18 -28.556959667163444 20 
		5.5857398992132792 24 2.4714118732419728 32 0.47028984975617816 40 18.161178446551723 
		44 -1.7965036329654047 47 -18.161528508991843 51 -5.3148331637844821 56 18.161178446551723 
		57 -11.373072784944522 58 -25.064422297761336 60 -9.3588915498806191 61 -5.3148331637844821 
		63 -4.2871268589854603 67 18.161178446551723 68 -11.373072784944522 70 -25.064422297761336 
		71 -9.3588915498806191 72 -5.3148331637844821 74 -4.2871268589854603 77 18.161178446551723 
		78 -11.373072784944522 80 -25.064422297761336 82 -9.3588915498806191 83 -5.3148331637844821 
		84 -4.2871268589854603 86 18.161178446551723 88 -11.373072784944522 89 -25.064422297761336 
		91 -9.3588915498806191 92 -5.3148331637844821 93 -4.2871268589854603 101 -68.705524318673724 
		104 -61.50514981019667 111 -10.418077892423513 116 -0.71491587080569741 126 0;
	setAttr -s 40 ".kit[5:39]"  10 3 10 3 10 1 10 3 
		10 10 1 3 10 3 10 10 1 3 10 3 10 10 1 3 10 
		3 10 10 1 1 3 3 3 3 3;
	setAttr -s 40 ".kot[5:39]"  10 3 10 3 10 1 10 3 
		10 10 1 1 10 3 10 10 1 1 10 3 10 10 1 1 10 
		3 10 10 1 1 3 3 3 3 3;
	setAttr -s 40 ".kix[10:39]"  1 0.88405483961105347 1 0.94340425729751587 
		0.27862304449081421 1 1 0.80305850505828857 1 0.94340413808822632 0.18988905847072601 
		1 1 0.73316711187362671 1 0.96695607900619507 0.27862274646759033 1 1 0.73316776752471924 
		1 0.94340413808822632 0.27862274646759033 1 1 1 1 1 1 1;
	setAttr -s 40 ".kiy[10:39]"  0 -0.46738329529762268 0 0.33164513111114502 
		0.96040052175521851 0 0 -0.59590011835098267 0 0.33164548873901367 0.98180556297302246 
		0 0 -0.68004846572875977 0 0.25494328141212463 0.96040064096450806 0 0 -0.68004786968231201 
		0 0.33164548873901367 0.96040064096450806 0 0 0 0 0 0 0;
	setAttr -s 40 ".kox[10:39]"  1 0.88405483961105347 1 0.94340425729751587 
		0.27862304449081421 1 1 0.80305850505828857 1 0.94340413808822632 0.18988905847072601 
		1 1 0.73316711187362671 1 0.96695607900619507 0.27862274646759033 1 1 0.73316776752471924 
		1 0.94340413808822632 0.27862274646759033 1 1 1 1 1 1 1;
	setAttr -s 40 ".koy[10:39]"  0 -0.46738329529762268 0 0.33164513111114502 
		0.96040052175521851 0 0 -0.59590011835098267 0 0.33164548873901367 0.98180556297302246 
		0 0 -0.68004846572875977 0 0.25494328141212463 0.96040064096450806 0 0 -0.68004786968231201 
		0 0.33164548873901367 0.96040064096450806 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 40 ".ktv[0:39]"  0 24.211026325508492 12 24.211026325508492 
		15 24.211026325508492 18 28.614396383403644 20 51.42575914361305 24 92.836892706710501 
		32 102.72841903814842 40 75.807954780412047 44 110.62890208127644 47 129.17601732979861 
		51 115.21079279114811 56 75.807954780412047 57 77.486741315571052 58 82.066337158667992 
		60 99.213747261705109 61 115.21079279114811 63 103.64578477796823 67 75.807954780412047 
		68 77.486741315571052 70 82.066337158667992 71 99.213747261705109 72 115.21079279114811 
		74 103.64578477796823 77 75.807954780412047 78 77.486741315571052 80 82.066337158667992 
		82 99.213747261705109 83 115.21079279114811 84 103.64578477796823 86 75.807954780412047 
		88 77.486741315571052 89 82.066337158667992 91 99.213747261705109 92 115.21079279114811 
		93 103.64578477796823 101 38.262325794467714 104 21.609038770370219 111 36.437301316854395 
		116 28.639573150688449 126 24.211026325508492;
	setAttr -s 40 ".kit[5:39]"  10 3 10 3 10 1 10 3 
		10 10 1 3 10 3 10 10 1 3 10 3 10 10 1 3 10 
		3 10 10 1 1 3 3 3 3 3;
	setAttr -s 40 ".kot[5:39]"  10 3 10 3 10 1 10 3 
		10 10 1 1 10 3 10 10 1 1 10 3 10 10 1 1 10 
		3 10 10 1 1 3 3 3 3 3;
	setAttr -s 40 ".kix[10:39]"  1 1 1 0.25499048829078674 0.17034049332141876 
		1 1 1 1 0.25499019026756287 0.11448711156845093 1 1 1 1 0.33170360326766968 0.17034028470516205 
		1 1 1 1 0.25499019026756287 0.17034028470516205 1 1 1 1 1 1 1;
	setAttr -s 40 ".kiy[10:39]"  0 0 0 0.96694356203079224 0.9853852391242981 
		0 0 0 0 0.96694368124008179 0.99342477321624756 0 0 0 0 0.94338363409042358 0.9853852391242981 
		0 0 0 0 0.96694368124008179 0.9853852391242981 0 0 0 0 0 0 0;
	setAttr -s 40 ".kox[10:39]"  1 1 1 0.25499048829078674 0.17034049332141876 
		1 1 1 1 0.25499019026756287 0.11448711156845093 1 1 1 1 0.33170360326766968 0.17034028470516205 
		1 1 1 1 0.25499019026756287 0.17034028470516205 1 1 1 1 1 1 1;
	setAttr -s 40 ".koy[10:39]"  0 0 0 0.96694356203079224 0.9853852391242981 
		0 0 0 0 0.96694368124008179 0.99342477321624756 0 0 0 0 0.94338363409042358 0.9853852391242981 
		0 0 0 0 0.96694368124008179 0.9853852391242981 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 40 ".ktv[0:39]"  0 0 12 0 15 0 18 -3.9770967114637497 20 
		-23.207266133392132 24 47.606773769151062 32 0.91568255442581137 40 41.295480466360949 
		44 -31.144644423668797 47 -49.557241580702986 51 19.482257479832324 56 41.295480466360949 
		57 -14.994722365442954 58 -36.075348490179906 60 7.7743598748138716 61 19.482257479832324 
		63 20.964185427545509 67 41.295480466360949 68 -14.994722365442954 70 -36.075348490179906 
		71 7.7743598748138716 72 19.482257479832324 74 20.964185427545509 77 41.295480466360949 
		78 -14.994722365442954 80 -36.075348490179906 82 7.7743598748138716 83 19.482257479832324 
		84 20.964185427545509 86 41.295480466360949 88 -14.994722365442954 89 -36.075348490179906 
		91 7.7743598748138716 92 19.482257479832324 93 20.964185427545509 101 -14.941425640920022 
		104 -18.191801178695638 111 -15.844069745630136 116 -5.5771158142382413 126 0;
	setAttr -s 40 ".kit[5:39]"  10 3 10 3 10 1 10 3 
		10 10 1 3 10 3 10 10 1 3 10 3 10 10 1 3 10 
		3 10 10 1 1 3 3 3 3 3;
	setAttr -s 40 ".kot[5:39]"  10 3 10 3 10 1 10 3 
		10 10 1 1 10 3 10 10 1 1 10 3 10 10 1 1 10 
		3 10 10 1 1 3 3 3 3 3;
	setAttr -s 40 ".kix[10:39]"  1 0.31540584564208984 1 0.24403089284896851 
		0.10258454084396362 1 1 0.25666528940200806 1 0.24403060972690582 0.068590655922889709 
		1 1 0.20781092345714569 1 0.31809148192405701 0.10258442163467407 1 1 0.20781128108501434 
		1 0.24403060972690582 0.10258442163467407 1 1 1 1 1 1 1;
	setAttr -s 40 ".kiy[10:39]"  0 -0.94895690679550171 0 0.96976745128631592 
		0.99472427368164063 0 0 -0.96650040149688721 0 0.96976745128631592 0.99764484167098999 
		0 0 -0.9781690239906311 0 0.94806003570556641 0.9947243332862854 0 0 -0.97816890478134155 
		0 0.96976745128631592 0.9947243332862854 0 0 0 0 0 0 0;
	setAttr -s 40 ".kox[10:39]"  1 0.31540584564208984 1 0.24403089284896851 
		0.10258454084396362 1 1 0.25666528940200806 1 0.24403060972690582 0.068590655922889709 
		1 1 0.20781092345714569 1 0.31809148192405701 0.10258442163467407 1 1 0.20781128108501434 
		1 0.24403060972690582 0.10258442163467407 1 1 1 1 1 1 1;
	setAttr -s 40 ".koy[10:39]"  0 -0.94895690679550171 0 0.96976745128631592 
		0.99472427368164063 0 0 -0.96650040149688721 0 0.96976745128631592 0.99764484167098999 
		0 0 -0.9781690239906311 0 0.94806003570556641 0.9947243332862854 0 0 -0.97816890478134155 
		0 0.96976745128631592 0.9947243332862854 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Wrist1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Wrist1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Wrist1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Hip1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Hip1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Hip1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Hip1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Hip1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Hip1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Hip1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Hip1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Hip1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Knee1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Knee1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Knee1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Knee1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Knee1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Knee1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Knee1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ankle1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ankle1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ankle1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ankle1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ankle1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ankle1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ankle1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ankle1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ankle1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ball1_L_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ball1_L_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ball1_L_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ball1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ball1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ball1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ball1_L_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ball1_L_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ball1_L_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Clavicle1_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Clavicle1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Clavicle1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 -37.15622838373644 25 -14.624175506066008 
		32 0 35 21.94948320344783 45 -17.323190669297919 52 0 57 0 63 0 68 0 74 0 78 0 84 
		0 88 0 93 0 101 -14.624175506066008 106 -14.624175506066008 110 -14.624175506066008 
		116 -5.1477127906213029 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0.6135705650167127 25 0.24149285378189847 
		32 0 35 16.111705455966167 45 -13.680528236940143 52 0 57 0 63 0 68 0 74 0 78 0 84 
		0 88 0 93 0 101 0.24149285378189847 106 0.24149285378189847 110 0.24149285378189847 
		116 0.085005534277202408 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Clavicle1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 -10.224451131120938 25 
		-4.0242019790188293 32 0 35 5.4979476392626099 45 0.53444114707571955 52 0 57 0 63 
		0 68 0 74 0 78 0 84 0 88 0 93 0 101 -4.0242019790188293 106 -4.0242019790188293 110 
		-4.0242019790188293 116 -1.4165199255743457 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 -2.194210208e-008 7 -2.194210208e-008 
		10 -2.194210208e-008 16 -2.194210208e-008 25 -2.194210208e-008 32 -2.194210208e-008 
		35 -2.194210208e-008 45 -2.194210208e-008 52 -2.194210208e-008 57 -2.194210208e-008 
		63 -2.194210208e-008 68 -2.194210208e-008 74 -2.194210208e-008 78 -2.194210208e-008 
		84 -2.194210208e-008 88 -2.194210208e-008 93 -2.194210208e-008 101 -2.194210208e-008 
		106 -2.194210208e-008 110 -2.194210208e-008 116 -2.194210208e-008 126 -2.194210208e-008;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Clavicle1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 20 ".ktv[0:19]"  0 1 7 1 10 1 25 1 35 1 49 1 56 1 57 1 63 
		1 66 1 68 1 74 1 77 1 78 1 84 1 86 1 88 1 93 1 101 1 126 1;
	setAttr -s 20 ".kit[4:19]"  10 3 1 3 3 1 3 3 
		1 3 3 1 3 1 3 3;
	setAttr -s 20 ".kot[4:19]"  10 1 1 3 1 1 3 1 
		1 3 1 1 3 1 3 3;
	setAttr -s 20 ".kix[6:19]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 20 ".kiy[6:19]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 20 ".kox[5:19]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 20 ".koy[5:19]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 20 ".ktv[0:19]"  0 1 7 1 10 1 25 1 35 1 49 1 56 1 57 1 63 
		1 66 1 68 1 74 1 77 1 78 1 84 1 86 1 88 1 93 1 101 1 126 1;
	setAttr -s 20 ".kit[4:19]"  10 3 1 3 3 1 3 3 
		1 3 3 1 3 1 3 3;
	setAttr -s 20 ".kot[4:19]"  10 1 1 3 1 1 3 1 
		1 3 1 1 3 1 3 3;
	setAttr -s 20 ".kix[6:19]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 20 ".kiy[6:19]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 20 ".kox[5:19]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 20 ".koy[5:19]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Shoulder1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 20 ".ktv[0:19]"  0 1 7 1 10 1 25 1 35 1 49 1 56 1 57 1 63 
		1 66 1 68 1 74 1 77 1 78 1 84 1 86 1 88 1 93 1 101 1 126 1;
	setAttr -s 20 ".kit[4:19]"  10 3 1 3 3 1 3 3 
		1 3 3 1 3 1 3 3;
	setAttr -s 20 ".kot[4:19]"  10 1 1 3 1 1 3 1 
		1 3 1 1 3 1 3 3;
	setAttr -s 20 ".kix[6:19]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 20 ".kiy[6:19]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 20 ".kox[5:19]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 20 ".koy[5:19]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Shoulder1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 28 ".ktv[0:27]"  0 17.19229314797029 7 3.246201707212736 
		10 3.246201707212736 15 30.039428306713887 20 -37.951801727268581 25 -33.465190950751932 
		35 -12.574251299522723 38 -38.563332463935517 49 -19.129863919965242 56 28.451521642621184 
		57 28.451521642621184 63 -25.521598158165016 66 28.451521642621184 68 28.451521642621184 
		74 -25.521598158165016 77 28.451521642621184 78 28.451521642621184 84 -25.521598158165016 
		86 28.451521642621184 88 28.451521642621184 93 -25.521598158165016 97 -6.9533939100138449 
		101 -35.853751725030101 106 -0.21868874735159333 110 -3.4346596405484435 114 1.8443390381263844 
		118 28.654269834322463 126 17.19229314797029;
	setAttr -s 28 ".kit[3:27]"  10 10 3 10 10 3 1 3 
		3 1 3 3 1 3 3 1 3 1 10 3 10 10 10 10 3;
	setAttr -s 28 ".kot[3:27]"  10 10 3 10 10 1 1 3 
		1 1 3 1 1 3 1 1 3 1 10 3 10 10 10 10 3;
	setAttr -s 28 ".kix[9:27]"  1 1 1 1 1 1 1 1 1 1 1 1 0.82837283611297607 
		1 0.46843460202217102 0.99100691080093384 0.42989757657051086 0.83089244365692139 
		1;
	setAttr -s 28 ".kiy[9:27]"  0 0 0 0 0 0 0 0 0 0 0 0 -0.56017708778381348 
		0 0.88349819183349609 0.13381056487560272 0.90287762880325317 0.55643296241760254 
		0;
	setAttr -s 28 ".kox[8:27]"  1 1 1 1 1 1 1 1 1 1 1 1 1 0.82837283611297607 
		1 0.46843460202217102 0.99100691080093384 0.42989757657051086 0.83089244365692139 
		1;
	setAttr -s 28 ".koy[8:27]"  0 0 0 0 0 0 0 0 0 0 0 0 0 -0.56017708778381348 
		0 0.88349819183349609 0.13381056487560272 0.90287762880325317 0.55643296241760254 
		0;
createNode animCurveTA -n "char_FKExtraR_Shoulder1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Shoulder1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Shoulder1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 10 1 17 1 20 1 29 1 43 1 49 1 56 1 
		57 1 63 1 66 1 68 1 74 1 77 1 78 1 84 1 86 1 88 1 93 1 103 1 110 1 126 1;
	setAttr -s 22 ".kit[4:21]"  9 10 1 1 3 1 1 3 
		1 1 3 1 1 3 1 3 3 3;
	setAttr -s 22 ".kot[4:21]"  9 10 1 1 3 1 1 3 
		1 1 3 1 1 3 1 3 3 3;
	setAttr -s 22 ".kix[6:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".kiy[6:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 22 ".kox[6:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[6:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 10 1 17 1 20 1 29 1 43 1 49 1 56 1 
		57 1 63 1 66 1 68 1 74 1 77 1 78 1 84 1 86 1 88 1 93 1 103 1 110 1 126 1;
	setAttr -s 22 ".kit[4:21]"  9 10 1 1 3 1 1 3 
		1 1 3 1 1 3 1 3 3 3;
	setAttr -s 22 ".kot[4:21]"  9 10 1 1 3 1 1 3 
		1 1 3 1 1 3 1 3 3 3;
	setAttr -s 22 ".kix[6:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".kiy[6:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 22 ".kox[6:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[6:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Elbow1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 10 1 17 1 20 1 29 1 43 1 49 1 56 1 
		57 1 63 1 66 1 68 1 74 1 77 1 78 1 84 1 86 1 88 1 93 1 103 1 110 1 126 1;
	setAttr -s 22 ".kit[4:21]"  9 10 1 1 3 1 1 3 
		1 1 3 1 1 3 1 3 3 3;
	setAttr -s 22 ".kot[4:21]"  9 10 1 1 3 1 1 3 
		1 1 3 1 1 3 1 3 3 3;
	setAttr -s 22 ".kix[6:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".kiy[6:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 22 ".kox[6:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[6:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Elbow1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 29 ".ktv[0:28]"  0 36.067317209388015 6 15.156865903201073 
		10 61.002657004304936 14 82.665242763391774 17 76.329462581606691 20 15.808314956781574 
		25 3.8529570859660081 29 10.348541928105735 34 128.20769190176338 43 36.707694409073135 
		49 31.556265538068796 52 25.161963489424988 56 106.65468837453062 57 106.65468837453062 
		63 31.556265538068796 66 106.65468837453062 68 106.65468837453062 74 31.556265538068796 
		77 106.65468837453062 78 106.65468837453062 84 31.556265538068796 86 106.65468837453062 
		88 106.65468837453062 93 31.556265538068796 97 79.177941502277164 103 48.252833773831689 
		110 25.472268489655654 120 42.120209095918263 126 36.067317209388015;
	setAttr -s 29 ".kit[1:28]"  10 3 10 3 3 10 1 10 
		10 1 10 1 3 1 1 3 1 1 3 1 1 3 1 10 3 
		3 10 3;
	setAttr -s 29 ".kot[1:28]"  10 3 10 3 3 10 1 10 
		10 1 10 1 3 1 1 3 1 1 3 1 1 3 1 10 3 
		3 10 3;
	setAttr -s 29 ".kix[7:28]"  0.54146093130111694 0.71213424205780029 
		0.28418344259262085 1 0.17526441812515259 1 1 1 1 1 1 1 1 1 1 1 1 0.75286394357681274 
		1 1 0.9448198676109314 1;
	setAttr -s 29 ".kiy[7:28]"  0.84072595834732056 0.70204335451126099 
		-0.95876997709274292 0 0.98452132940292358 0 0 0 0 0 0 0 0 0 0 0 0 0.65817612409591675 
		0 0 0.32759016752243042 0;
	setAttr -s 29 ".kox[7:28]"  0.54146081209182739 0.71213424205780029 
		0.28418344259262085 1 0.17526441812515259 1 1 1 1 1 1 1 1 1 1 1 1 0.75286394357681274 
		1 1 0.9448198676109314 1;
	setAttr -s 29 ".koy[7:28]"  0.84072601795196533 0.70204335451126099 
		-0.95876997709274292 0 0.98452132940292358 0 0 0 0 0 0 0 0 0 0 0 0 0.65817612409591675 
		0 0 0.32759016752243042 0;
createNode animCurveTA -n "char_FKExtraR_Elbow1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Elbow1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Elbow1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb5_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb5_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb5_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb5_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 27.905251822156437 7 27.905251822156437 
		10 27.905251822156437 16 27.905251822156437 25 27.905251822156437 32 -27.756544765157578 
		35 -27.756544765157578 45 -27.756544765157578 52 -27.756544765157578 57 -27.756544765157578 
		63 -27.756544765157578 68 -27.756544765157578 74 -27.756544765157578 78 -27.756544765157578 
		84 -27.756544765157578 88 -27.756544765157578 93 -27.756544765157578 101 27.905251822156437 
		106 27.905251822156437 110 27.905251822156437 116 27.905251822156437 126 27.905251822156437;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb5_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 -73.28650006345265 
		35 -73.28650006345265 45 -73.28650006345265 52 -73.28650006345265 57 -73.28650006345265 
		63 -73.28650006345265 68 -73.28650006345265 74 -73.28650006345265 78 -73.28650006345265 
		84 -73.28650006345265 88 -73.28650006345265 93 -73.28650006345265 101 0 106 0 110 
		0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb5_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 118.08063122739006 
		35 118.08063122739006 45 118.08063122739006 52 118.08063122739006 57 118.08063122739006 
		63 118.08063122739006 68 118.08063122739006 74 118.08063122739006 78 118.08063122739006 
		84 118.08063122739006 88 118.08063122739006 93 118.08063122739006 101 0 106 0 110 
		0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb5_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb5_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb5_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb6_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb6_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Thumb6_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb6_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 28.959457180709169 7 28.959457180709169 
		10 28.959457180709169 16 28.959457180709169 25 28.959457180709169 32 61.946865629909794 
		35 61.946865629909794 45 61.946865629909794 52 61.946865629909794 57 61.946865629909794 
		63 61.946865629909794 68 61.946865629909794 74 61.946865629909794 78 61.946865629909794 
		84 61.946865629909794 88 61.946865629909794 93 61.946865629909794 101 28.959457180709169 
		106 28.959457180709169 110 28.959457180709169 116 28.959457180709169 126 28.959457180709169;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb6_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 -12.483272772594933 7 -12.483272772594933 
		10 -12.483272772594933 16 -12.483272772594933 25 -12.483272772594933 32 -11.364074149084164 
		35 -11.364074149084164 45 -11.364074149084164 52 -11.364074149084164 57 -11.364074149084164 
		63 -11.364074149084164 68 -11.364074149084164 74 -11.364074149084164 78 -11.364074149084164 
		84 -11.364074149084164 88 -11.364074149084164 93 -11.364074149084164 101 -12.483272772594933 
		106 -12.483272772594933 110 -12.483272772594933 116 -12.483272772594933 126 -12.483272772594933;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Thumb6_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 21.335853393578894 7 21.335853393578894 
		10 21.335853393578894 16 21.335853393578894 25 21.335853393578894 32 51.904519160068361 
		35 51.904519160068361 45 51.904519160068361 52 51.904519160068361 57 51.904519160068361 
		63 51.904519160068361 68 51.904519160068361 74 51.904519160068361 78 51.904519160068361 
		84 51.904519160068361 88 51.904519160068361 93 51.904519160068361 101 21.335853393578894 
		106 21.335853393578894 110 21.335853393578894 116 21.335853393578894 126 21.335853393578894;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb6_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb6_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Thumb6_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle5_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle5_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle5_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle5_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 31.36933547988048 7 31.36933547988048 
		10 31.36933547988048 16 31.36933547988048 25 31.36933547988048 32 112.54268521375866 
		35 112.54268521375866 45 112.54268521375866 52 112.54268521375866 57 112.54268521375866 
		63 112.54268521375866 68 112.54268521375866 74 112.54268521375866 78 112.54268521375866 
		84 112.54268521375866 88 112.54268521375866 93 112.54268521375866 101 31.36933547988048 
		106 31.36933547988048 110 31.36933547988048 116 31.36933547988048 126 31.36933547988048;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle5_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 33.852202196176009 
		35 33.852202196176009 45 33.852202196176009 52 33.852202196176009 57 33.852202196176009 
		63 33.852202196176009 68 33.852202196176009 74 33.852202196176009 78 33.852202196176009 
		84 33.852202196176009 88 33.852202196176009 93 33.852202196176009 101 0 106 0 110 
		0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle5_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle5_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle5_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle5_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle6_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle6_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Middle6_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle6_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 20.121507236316084 7 20.121507236316084 
		10 20.121507236316084 16 20.121507236316084 25 20.121507236316084 32 48.053005650362707 
		35 48.053005650362707 45 48.053005650362707 52 48.053005650362707 57 48.053005650362707 
		63 48.053005650362707 68 48.053005650362707 74 48.053005650362707 78 48.053005650362707 
		84 48.053005650362707 88 48.053005650362707 93 48.053005650362707 101 20.121507236316084 
		106 20.121507236316084 110 20.121507236316084 116 20.121507236316084 126 20.121507236316084;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle6_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Middle6_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle6_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle6_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Middle6_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 28 ".ktv[0:27]"  0 1 7 1 10 1 16 1 25 1 27 1 30 1 31 1 49 
		1 55 1 56 1 57 1 63 1 65 1 66 1 68 1 74 1 76 1 77 1 78 1 84 1 86 1 87 1 88 1 93 1 
		103 1 116 1 126 1;
	setAttr -s 28 ".kit[7:27]"  1 3 1 1 3 3 1 1 
		3 3 1 1 3 3 1 1 3 1 3 3 3;
	setAttr -s 28 ".kot[7:27]"  1 1 1 1 3 1 1 1 
		3 1 1 1 3 1 1 1 3 1 3 3 3;
	setAttr -s 28 ".kix[7:27]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1;
	setAttr -s 28 ".kiy[7:27]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0;
	setAttr -s 28 ".kox[7:27]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1;
	setAttr -s 28 ".koy[7:27]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 28 ".ktv[0:27]"  0 1 7 1 10 1 16 1 25 1 27 1 30 1 31 1 49 
		1 55 1 56 1 57 1 63 1 65 1 66 1 68 1 74 1 76 1 77 1 78 1 84 1 86 1 87 1 88 1 93 1 
		103 1 116 1 126 1;
	setAttr -s 28 ".kit[7:27]"  1 3 1 1 3 3 1 1 
		3 3 1 1 3 3 1 1 3 1 3 3 3;
	setAttr -s 28 ".kot[7:27]"  1 1 1 1 3 1 1 1 
		3 1 1 1 3 1 1 1 3 1 3 3 3;
	setAttr -s 28 ".kix[7:27]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1;
	setAttr -s 28 ".kiy[7:27]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0;
	setAttr -s 28 ".kox[7:27]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1;
	setAttr -s 28 ".koy[7:27]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0;
createNode animCurveTU -n "char_FKCurveR_Wrist1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 28 ".ktv[0:27]"  0 1 7 1 10 1 16 1 25 1 27 1 30 1 31 1 49 
		1 55 1 56 1 57 1 63 1 65 1 66 1 68 1 74 1 76 1 77 1 78 1 84 1 86 1 87 1 88 1 93 1 
		103 1 116 1 126 1;
	setAttr -s 28 ".kit[7:27]"  1 3 1 1 3 3 1 1 
		3 3 1 1 3 3 1 1 3 1 3 3 3;
	setAttr -s 28 ".kot[7:27]"  1 1 1 1 3 1 1 1 
		3 1 1 1 3 1 1 1 3 1 3 3 3;
	setAttr -s 28 ".kix[7:27]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1;
	setAttr -s 28 ".kiy[7:27]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0;
	setAttr -s 28 ".kox[7:27]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		1;
	setAttr -s 28 ".koy[7:27]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
		0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 36 ".ktv[0:35]"  0 5.3442930176413892 7 5.3442930176413892 
		10 5.3442930176413892 16 -27.561288228671092 25 -3.2724047919798216 27 -26.343871874467514 
		30 -26.343871874467514 31 -8.5631548989701596 34 30.416523416161613 40 9.9923144576672058 
		45 -9.677502837002022 49 -26.343871874467514 55 -8.5631548989701596 56 7.8356000924429274 
		57 7.8356000924429274 59 11.642075569070711 63 -26.343871874467514 65 -8.5631548989701596 
		66 7.8356000924429274 68 7.8356000924429274 71 11.642075569070711 74 -26.343871874467514 
		76 -8.5631548989701596 77 7.8356000924429274 78 7.8356000924429274 82 11.642075569070711 
		84 -26.343871874467514 86 -8.5631548989701596 87 7.8356000924429274 88 7.8356000924429274 
		91 11.642075569070711 93 -26.343871874467514 97 10.530417971190147 103 -26.823030045311921 
		116 -5.9786113267797818 126 5.3442930176413892;
	setAttr -s 36 ".kit[7:35]"  1 10 10 10 3 1 1 3 
		10 3 1 1 3 10 3 1 1 3 10 3 1 1 3 10 1 
		10 3 3 3;
	setAttr -s 36 ".kot[7:35]"  1 10 10 10 1 1 1 3 
		10 1 1 1 3 10 1 1 1 3 10 1 1 1 3 10 1 
		10 3 3 3;
	setAttr -s 36 ".kix[7:35]"  1 0.6795729398727417 0.46412524580955505 
		0.4276159405708313 1 1 1 1 0.31787490844726563 1 1 1 1 0.31787505745887756 1 1 1 
		1 0.31787505745887756 1 1 1 1 0.26908206939697266 1 0.99968540668487549 1 1 1;
	setAttr -s 36 ".kiy[7:35]"  0 0.7336079478263855 -0.88576960563659668 
		-0.9039604663848877 0 0 0 0 -0.94813269376754761 0 0 0 0 -0.94813257455825806 0 0 
		0 0 -0.94813257455825806 0 0 0 0 -0.96311724185943604 0 -0.025080757215619087 0 0 
		0;
	setAttr -s 36 ".kox[7:35]"  1 0.6795729398727417 0.46412524580955505 
		0.4276159405708313 1 1 1 1 0.31787490844726563 1 1 1 1 0.31787505745887756 1 1 1 
		1 0.31787505745887756 1 1 1 1 0.26908206939697266 1 0.99968540668487549 1 1 1;
	setAttr -s 36 ".koy[7:35]"  0 0.7336079478263855 -0.88576960563659668 
		-0.9039604663848877 0 0 0 0 -0.94813269376754761 0 0 0 0 -0.94813257455825806 0 0 
		0 0 -0.94813257455825806 0 0 0 0 -0.96311724185943604 0 -0.025080757215619087 0 0 
		0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 36 ".ktv[0:35]"  0 30.381278874765098 7 30.381278874765098 
		10 30.381278874765098 16 31.361620117816532 25 14.375505688541931 27 71.794506928197123 
		30 71.794506928197123 31 73.334320256024554 34 107.22844606015437 40 118.66840029968246 
		45 73.568275008254489 49 71.794506928197123 55 73.334320256024554 56 109.55556718247317 
		57 109.55556718247317 59 88.007743108530732 63 71.794506928197123 65 73.334320256024554 
		66 109.55556718247317 68 109.55556718247317 71 88.007743108530732 74 71.794506928197123 
		76 73.334320256024554 77 109.55556718247317 78 109.55556718247317 82 88.007743108530732 
		84 71.794506928197123 86 73.334320256024554 87 109.55556718247317 88 109.55556718247317 
		91 88.007743108530732 93 71.794506928197123 97 35.784095808143441 103 55.880684168115188 
		116 39.357074790737762 126 30.381278874765098;
	setAttr -s 36 ".kit[7:35]"  1 10 10 10 3 1 1 3 
		10 3 1 1 3 10 3 1 1 3 10 3 1 1 3 10 1 
		10 3 3 3;
	setAttr -s 36 ".kot[7:35]"  1 10 10 10 1 1 1 3 
		10 1 1 1 3 10 1 1 1 3 10 1 1 1 3 10 1 
		10 3 3 3;
	setAttr -s 36 ".kix[7:35]"  1 0.35452893376350403 0.52947044372558594 
		1 1 1 1 1 0.29038813710212708 1 1 1 1 0.2903883159160614 1 1 1 1 0.2903883159160614 
		1 1 1 1 0.24516913294792175 1 0.76825451850891113 1 1 1;
	setAttr -s 36 ".kiy[7:35]"  0 0.93504500389099121 -0.8483283519744873 
		0 0 0 0 0 -0.9569089412689209 0 0 0 0 -0.9569089412689209 0 0 0 0 -0.9569089412689209 
		0 0 0 0 -0.96948033571243286 0 -0.64014452695846558 0 0 0;
	setAttr -s 36 ".kox[7:35]"  1 0.35452893376350403 0.52947044372558594 
		1 1 1 1 1 0.29038813710212708 1 1 1 1 0.2903883159160614 1 1 1 1 0.2903883159160614 
		1 1 1 1 0.24516913294792175 1 0.76825451850891113 1 1 1;
	setAttr -s 36 ".koy[7:35]"  0 0.93504500389099121 -0.8483283519744873 
		0 0 0 0 0 -0.9569089412689209 0 0 0 0 -0.9569089412689209 0 0 0 0 -0.9569089412689209 
		0 0 0 0 -0.96948033571243286 0 -0.64014452695846558 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Wrist1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 36 ".ktv[0:35]"  0 11.798366512855891 7 11.798366512855891 
		10 11.798366512855891 16 -8.5303248639850207 25 -15.391445265357472 27 -39.539474297438126 
		30 -39.539474297438126 31 9.4205170929147464 34 10.261507044274415 40 39.320958889095351 
		45 -15.056856619901204 49 -39.539474297438126 55 9.4205170929147464 56 -9.2582359428365368 
		57 -9.2582359428365368 59 21.990739630131419 63 -39.539474297438126 65 9.4205170929147464 
		66 -9.2582359428365368 68 -9.2582359428365368 71 21.990739630131419 74 -39.539474297438126 
		76 9.4205170929147464 77 -9.2582359428365368 78 -9.2582359428365368 82 21.990739630131419 
		84 -39.539474297438126 86 9.4205170929147464 87 -9.2582359428365368 88 -9.2582359428365368 
		91 21.990739630131419 93 -39.539474297438126 97 8.2627771853178889 103 -27.334703702176672 
		116 -1.9764822639962665 126 11.798366512855891;
	setAttr -s 36 ".kit[7:35]"  1 10 10 10 3 1 1 3 
		10 3 1 1 3 10 3 1 1 3 10 3 1 1 3 10 1 
		10 3 3 3;
	setAttr -s 36 ".kot[7:35]"  1 10 10 10 1 1 1 3 
		10 1 1 1 3 10 1 1 1 3 10 1 1 1 3 10 1 
		10 3 3 3;
	setAttr -s 36 ".kix[7:35]"  1 1 0.63856524229049683 0.21296386420726776 
		1 1 1 1 0.35392951965332031 1 1 1 1 0.35392972826957703 1 1 1 1 0.35392972826957703 
		1 1 1 1 0.30075302720069885 1 0.84263843297958374 1 1 1;
	setAttr -s 36 ".kiy[7:35]"  0 0 -0.76956772804260254 -0.97706007957458496 
		0 0 0 0 -0.93527203798294067 0 0 0 0 -0.93527203798294067 0 0 0 0 -0.93527203798294067 
		0 0 0 0 -0.95370203256607056 0 0.53847968578338623 0 0 0;
	setAttr -s 36 ".kox[7:35]"  1 1 0.63856524229049683 0.21296386420726776 
		1 1 1 1 0.35392951965332031 1 1 1 1 0.35392972826957703 1 1 1 1 0.35392972826957703 
		1 1 1 1 0.30075302720069885 1 0.84263843297958374 1 1 1;
	setAttr -s 36 ".koy[7:35]"  0 0 -0.76956772804260254 -0.97706007957458496 
		0 0 0 0 -0.93527203798294067 0 0 0 0 -0.93527203798294067 0 0 0 0 -0.93527203798294067 
		0 0 0 0 -0.95370203256607056 0 0.53847968578338623 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Wrist1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Wrist1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Wrist1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Hip1_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Hip1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Hip1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Hip1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Hip1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Hip1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Hip1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Hip1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Hip1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Knee1_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Knee1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Knee1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Knee1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Knee1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Knee1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Knee1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ankle1_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ankle1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ankle1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ankle1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ankle1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ankle1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ankle1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ankle1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ankle1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ball1_R_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ball1_R_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_FKCurveR_Ball1_R_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ball1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ball1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKCurveR_Ball1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ball1_R_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ball1_R_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_FKExtraR_Ball1_R_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_All_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_All_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_All_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_All_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_All_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "char_All_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_All_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_All_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "char_All_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 7 0 10 0 16 0 25 0 32 0 35 0 45 0 52 
		0 57 0 63 0 68 0 74 0 78 0 84 0 88 0 93 0 101 0 106 0 110 0 116 0 126 0;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "char_All_visibility";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1 7 1 10 1 16 1 25 1 32 1 35 1 45 1 52 
		1 57 1 63 1 68 1 74 1 78 1 84 1 88 1 93 1 101 1 106 1 110 1 116 1 126 1;
	setAttr -s 22 ".kit[16:21]"  1 3 3 3 3 3;
	setAttr -s 22 ".kot[8:21]"  1 3 1 3 1 3 1 3 
		1 3 3 3 3 3;
	setAttr -s 22 ".kix[16:21]"  1 1 1 1 1 1;
	setAttr -s 22 ".kiy[16:21]"  0 0 0 0 0 0;
	setAttr -s 22 ".kox[8:21]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 22 ".koy[8:21]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode lightLinker -n "lightLinker1";
	setAttr -s 3 ".lnk";
	setAttr -s 3 ".slnk";
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
	setAttr -k on ".cch";
	setAttr -k on ".nds";
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
connectAttr "happySource.cl" "clipLibrary1.sc[0]";
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
// End of maugli_happy.ma
