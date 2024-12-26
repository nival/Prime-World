//Maya ASCII 2008 scene
//Name: ability01.ma
//Last modified: Fri, Jan 29, 2010 12:16:13 PM
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
	setAttr -s 387 ".cel[0].cev";
	setAttr ".cd[0].cm" -type "characterMapping" 498 "Center_M_Man.CenterBtwFeet" 
		0 1 "Center_M_Man.rotateZ" 2 1 "Center_M_Man.rotateY" 2 
		2 "Center_M_Man.rotateX" 2 3 "Center_M_Man.translateZ" 1 1 "Center_M_Man.translateY" 
		1 2 "Center_M_Man.translateX" 1 3 "Fingers_L_Man.MiddleFingerCurl" 
		0 2 "IKLegBall_L_Man.rotateX" 2 4 "IKLegToe_L_Man.rotateZ" 2 
		5 "IKLegToe_L_Man.rotateY" 2 6 "IKLegToe_L_Man.rotateX" 2 7 "FKIKLeg_L_Man.IKVis" 
		0 3 "FKIKLeg_L_Man.FKVis" 0 4 "FKIKLeg_L_Man.FKIKBlend" 0 
		5 "IKLegHeel_L_Man.rotateZ" 2 8 "IKLegHeel_L_Man.rotateY" 2 9 "IKLegHeel_L_Man.rotateX" 
		2 10 "PoleLeg_L_Man.translateZ" 1 4 "PoleLeg_L_Man.translateY" 
		1 5 "PoleLeg_L_Man.translateX" 1 6 "IKLeg_L_Man.Lenght2" 0 
		7 "IKLeg_L_Man.Lenght1" 0 8 "IKLeg_L_Man.antiPop" 0 9 "IKLeg_L_Man.stretchy" 
		0 10 "IKLeg_L_Man.rollAngle" 0 11 "IKLeg_L_Man.roll" 0 12 "IKLeg_L_Man.toe" 
		0 13 "IKLeg_L_Man.swivel" 0 14 "IKLeg_L_Man.rotateZ" 2 11 "IKLeg_L_Man.rotateY" 
		2 12 "IKLeg_L_Man.rotateX" 2 13 "IKLeg_L_Man.translateZ" 1 
		7 "IKLeg_L_Man.translateY" 1 8 "IKLeg_L_Man.translateX" 1 9 "FKIKArm_L_Man.IKVis" 
		0 15 "FKIKArm_L_Man.FKVis" 0 16 "FKIKArm_L_Man.FKIKBlend" 0 
		17 "PoleArm_L_Man.follow" 0 18 "PoleArm_L_Man.translateZ" 1 10 "PoleArm_L_Man.translateY" 
		1 11 "PoleArm_L_Man.translateX" 1 12 "IKArm_L_Man.Lenght2" 0 
		19 "IKArm_L_Man.Lenght1" 0 20 "IKArm_L_Man.antiPop" 0 21 "IKArm_L_Man.stretchy" 
		0 22 "IKArm_L_Man.follow" 0 23 "IKArm_L_Man.rotateZ" 2 14 "IKArm_L_Man.rotateY" 
		2 15 "IKArm_L_Man.rotateX" 2 16 "IKArm_L_Man.translateZ" 1 
		13 "IKArm_L_Man.translateY" 1 14 "IKArm_L_Man.translateX" 1 15 "Fingers_R_Man.MiddleFingerCurl" 
		0 24 "FKIKSpine_M_Man.IKVis" 0 25 "FKIKSpine_M_Man.FKVis" 0 
		26 "FKIKSpine_M_Man.FKIKBlend" 0 27 "IKSpine4_M_Man.stretchy" 0 
		28 "IKSpine4_M_Man.stiff" 0 29 "IKSpine4_M_Man.rotateZ" 2 17 "IKSpine4_M_Man.rotateY" 
		2 18 "IKSpine4_M_Man.rotateX" 2 19 "IKSpine4_M_Man.translateZ" 
		1 16 "IKSpine4_M_Man.translateY" 1 17 "IKSpine4_M_Man.translateX" 
		1 18 "IKSpine2_M_Man.stiff" 0 30 "IKSpine2_M_Man.rotateZ" 2 
		20 "IKSpine2_M_Man.rotateY" 2 21 "IKSpine2_M_Man.rotateX" 2 22 "IKSpine2_M_Man.translateZ" 
		1 19 "IKSpine2_M_Man.translateY" 1 20 "IKSpine2_M_Man.translateX" 
		1 21 "IKSpine0_M_Man.stiff" 0 31 "IKSpine0_M_Man.rotateZ" 2 
		23 "IKSpine0_M_Man.rotateY" 2 24 "IKSpine0_M_Man.rotateX" 2 25 "IKSpine0_M_Man.translateZ" 
		1 22 "IKSpine0_M_Man.translateY" 1 23 "IKSpine0_M_Man.translateX" 
		1 24 "IKLegBall_R_Man.rotateX" 2 26 "IKLegToe_R_Man.rotateZ" 2 
		27 "IKLegToe_R_Man.rotateY" 2 28 "IKLegToe_R_Man.rotateX" 2 29 "IKLegHeel_R_Man.rotateZ" 
		2 30 "IKLegHeel_R_Man.rotateY" 2 31 "IKLegHeel_R_Man.rotateX" 2 
		32 "FKIKLeg_R_Man.IKVis" 0 32 "FKIKLeg_R_Man.FKVis" 0 33 "FKIKLeg_R_Man.FKIKBlend" 
		0 34 "PoleLeg_R_Man.translateZ" 1 25 "PoleLeg_R_Man.translateY" 
		1 26 "PoleLeg_R_Man.translateX" 1 27 "IKLeg_R_Man.Lenght2" 0 
		36 "IKLeg_R_Man.Lenght1" 0 37 "IKLeg_R_Man.antiPop" 0 38 "IKLeg_R_Man.stretchy" 
		0 39 "IKLeg_R_Man.rollAngle" 0 40 "IKLeg_R_Man.roll" 0 41 "IKLeg_R_Man.toe" 
		0 42 "IKLeg_R_Man.swivel" 0 43 "IKLeg_R_Man.rotateZ" 2 33 "IKLeg_R_Man.rotateY" 
		2 34 "IKLeg_R_Man.rotateX" 2 35 "IKLeg_R_Man.translateZ" 1 
		28 "IKLeg_R_Man.translateY" 1 29 "IKLeg_R_Man.translateX" 1 30 "FKIKArm_R_Man.IKVis" 
		0 44 "FKIKArm_R_Man.FKVis" 0 45 "FKIKArm_R_Man.FKIKBlend" 0 
		46 "PoleArm_R_Man.follow" 0 47 "PoleArm_R_Man.translateZ" 1 31 "PoleArm_R_Man.translateY" 
		1 32 "PoleArm_R_Man.translateX" 1 33 "HipSwingerRoot_M_Man.rotateZ" 
		2 36 "HipSwingerRoot_M_Man.rotateY" 2 37 "HipSwingerRoot_M_Man.rotateX" 
		2 38 "IKArm_R_Man.Lenght2" 0 48 "IKArm_R_Man.Lenght1" 0 49 "IKArm_R_Man.antiPop" 
		0 50 "IKArm_R_Man.stretchy" 0 51 "IKArm_R_Man.follow" 0 52 "IKArm_R_Man.rotateZ" 
		2 39 "IKArm_R_Man.rotateY" 2 40 "IKArm_R_Man.rotateX" 2 41 "IKArm_R_Man.translateZ" 
		1 34 "IKArm_R_Man.translateY" 1 35 "IKArm_R_Man.translateX" 1 
		36 "FKHip_L_Man.rotateZ" 2 42 "FKHip_L_Man.rotateY" 2 43 "FKHip_L_Man.rotateX" 
		2 44 "FKKnee_L_Man.rotateZ" 2 45 "FKAnkle_L_Man.rotateZ" 2 
		46 "FKAnkle_L_Man.rotateY" 2 47 "FKAnkle_L_Man.rotateX" 2 48 "FKMiddleToe1_L_Man.rotateZ" 
		2 49 "FKScapula_L_Man.rotateZ" 2 50 "FKScapula_L_Man.rotateY" 2 
		51 "FKScapula_L_Man.rotateX" 2 52 "FKScapula_L_Man.translateZ" 1 
		37 "FKScapula_L_Man.translateY" 1 38 "FKScapula_L_Man.translateX" 1 
		39 "FKShoulder_L_Man.rotateZ" 2 53 "FKShoulder_L_Man.rotateY" 2 
		54 "FKShoulder_L_Man.rotateX" 2 55 "FKElbow_L_Man.rotateY" 2 56 "FKWrist_L_Man.rotateZ" 
		2 57 "FKWrist_L_Man.rotateY" 2 58 "FKWrist_L_Man.rotateX" 2 
		59 "FKMiddleFinger1_L_Man.rotateZ" 2 60 "FKMiddleFinger2_L_Man.rotateZ" 
		2 61 "FKMiddleFinger3_L_Man.rotateZ" 2 62 "FKThumbFinger1_L_Man.rotateZ" 
		2 63 "FKThumbFinger1_L_Man.rotateY" 2 64 "FKThumbFinger1_L_Man.rotateX" 
		2 65 "FKThumbFinger2_L_Man.rotateY" 2 66 "FKHip_R_Man.rotateZ" 
		2 67 "FKHip_R_Man.rotateY" 2 68 "FKHip_R_Man.rotateX" 2 69 "FKKnee_R_Man.rotateZ" 
		2 70 "FKAnkle_R_Man.rotateZ" 2 71 "FKAnkle_R_Man.rotateY" 2 
		72 "FKAnkle_R_Man.rotateX" 2 73 "FKMiddleToe1_R_Man.rotateZ" 2 
		74 "FKBackA_M_Man.rotateZ" 2 75 "FKBackA_M_Man.rotateY" 2 76 "FKBackA_M_Man.rotateX" 
		2 77 "FKBackB_M_Man.rotateZ" 2 78 "FKBackB_M_Man.rotateY" 2 
		79 "FKBackB_M_Man.rotateX" 2 80 "FKChest_M_Man.rotateZ" 2 81 "FKChest_M_Man.rotateY" 
		2 82 "FKChest_M_Man.rotateX" 2 83 "FKNeck_M_Man.rotateZ" 2 
		84 "FKNeck_M_Man.rotateY" 2 85 "FKNeck_M_Man.rotateX" 2 86 "FKHead_M_Man.rotateZ" 
		2 87 "FKHead_M_Man.rotateY" 2 88 "FKHead_M_Man.rotateX" 2 
		89 "FKScapula_R_Man.rotateZ" 2 90 "FKScapula_R_Man.rotateY" 2 91 "FKScapula_R_Man.rotateX" 
		2 92 "FKScapula_R_Man.translateZ" 1 40 "FKScapula_R_Man.translateY" 
		1 41 "FKScapula_R_Man.translateX" 1 42 "FKShoulder_R_Man.rotateZ" 
		2 93 "FKShoulder_R_Man.rotateY" 2 94 "FKShoulder_R_Man.rotateX" 
		2 95 "FKElbow_R_Man.rotateY" 2 96 "FKWrist_R_Man.rotateZ" 2 
		97 "FKWrist_R_Man.rotateY" 2 98 "FKWrist_R_Man.rotateX" 2 99 "FKMiddleFinger1_R_Man.rotateZ" 
		2 100 "FKMiddleFinger2_R_Man.rotateZ" 2 101 "FKMiddleFinger3_R_Man.rotateZ" 
		2 102 "FKThumbFinger1_R_Man.rotateZ" 2 103 "FKThumbFinger1_R_Man.rotateY" 
		2 104 "FKThumbFinger1_R_Man.rotateX" 2 105 "FKThumbFinger2_R_Man.rotateY" 
		2 106 "Main_Man.visibility" 0 53 "Center_M.CenterBtwFeet" 0 
		54 "Center_M.rotateZ" 2 107 "Center_M.rotateY" 2 108 "Center_M.rotateX" 
		2 109 "Center_M.translateZ" 1 43 "Center_M.translateY" 1 44 "Center_M.translateX" 
		1 45 "IKLegBackBall_L.rotateX" 2 110 "IKLegBackHeel_L.rotateZ" 2 
		111 "IKLegBackHeel_L.rotateY" 2 112 "IKLegBackHeel_L.rotateX" 2 113 "FKIKLegBack_L.IKVis" 
		0 55 "FKIKLegBack_L.FKVis" 0 56 "FKIKLegBack_L.FKIKBlend" 0 
		57 "PoleLegBack_L.follow" 0 58 "PoleLegBack_L.translateZ" 1 46 "PoleLegBack_L.translateY" 
		1 47 "PoleLegBack_L.translateX" 1 48 "IKLegBack_L.Lenght2" 0 
		59 "IKLegBack_L.Lenght1" 0 60 "IKLegBack_L.antiPop" 0 61 "IKLegBack_L.stretchy" 
		0 62 "IKLegBack_L.legAim" 0 63 "IKLegBack_L.rollAngle" 0 64 "IKLegBack_L.roll" 
		0 65 "IKLegBack_L.swivel" 0 66 "IKLegBack_L.rotateZ" 2 114 "IKLegBack_L.rotateY" 
		2 115 "IKLegBack_L.rotateX" 2 116 "IKLegBack_L.translateZ" 1 
		49 "IKLegBack_L.translateY" 1 50 "IKLegBack_L.translateX" 1 51 "BendNeck_M.translateZ" 
		1 58 "BendNeck_M.translateY" 1 59 "BendNeck_M.translateX" 1 
		60 "FKIKSpine_M.IKVis" 0 79 "FKIKSpine_M.FKVis" 0 80 "FKIKSpine_M.FKIKBlend" 
		0 81 "IKSpine4_M.stretchy" 0 82 "IKSpine4_M.stiff" 0 83 "IKSpine4_M.rotateZ" 
		2 124 "IKSpine4_M.rotateY" 2 125 "IKSpine4_M.rotateX" 2 126 "IKSpine4_M.translateZ" 
		1 61 "IKSpine4_M.translateY" 1 62 "IKSpine4_M.translateX" 1 
		63 "IKSpine2_M.stiff" 0 84 "IKSpine2_M.translateZ" 1 64 "IKSpine2_M.translateY" 
		1 65 "IKSpine2_M.translateX" 1 66 "IKSpine0_M.stiff" 0 85 "IKSpine0_M.rotateZ" 
		2 127 "IKSpine0_M.rotateY" 2 128 "IKSpine0_M.rotateX" 2 129 "IKSpine0_M.translateZ" 
		1 67 "IKSpine0_M.translateY" 1 68 "IKSpine0_M.translateX" 1 
		69 "IKLegBackBall_R.rotateX" 2 130 "IKLegBackHeel_R.rotateZ" 2 131 "IKLegBackHeel_R.rotateY" 
		2 132 "IKLegBackHeel_R.rotateX" 2 133 "FKIKLegBack_R.IKVis" 0 
		86 "FKIKLegBack_R.FKVis" 0 87 "FKIKLegBack_R.FKIKBlend" 0 88 "PoleLegBack_R.follow" 
		0 89 "PoleLegBack_R.translateZ" 1 70 "PoleLegBack_R.translateY" 
		1 71 "PoleLegBack_R.translateX" 1 72 "IKLegBack_R.Lenght2" 0 
		90 "IKLegBack_R.Lenght1" 0 91 "IKLegBack_R.antiPop" 0 92 "IKLegBack_R.stretchy" 
		0 93 "IKLegBack_R.legAim" 0 94 "IKLegBack_R.rollAngle" 0 95 "IKLegBack_R.roll" 
		0 96 "IKLegBack_R.swivel" 0 97 "IKLegBack_R.rotateZ" 2 134 "IKLegBack_R.rotateY" 
		2 135 "IKLegBack_R.rotateX" 2 136 "IKLegBack_R.translateZ" 1 
		73 "IKLegBack_R.translateY" 1 74 "IKLegBack_R.translateX" 1 75 "FKIKSplineTail_M.IKVis" 
		0 98 "FKIKSplineTail_M.FKVis" 0 99 "FKIKSplineTail_M.FKIKBlend" 
		0 100 "WagCurveSplineTail_M.increment" 0 101 "WagCurveSplineTail_M.multiply" 
		0 102 "WagCurveSplineTail_M.timeOffset" 0 103 "WagCurveSplineTail_M.enable" 
		0 104 "WagCurveSplineTail_M.rotateZ" 2 137 "WagCurveSplineTail_M.rotateY" 
		2 138 "WagCurveSplineTail_M.rotateX" 2 139 "IKSplineTail2_M.stretchy" 
		0 105 "IKSplineTail2_M.twist" 0 106 "IKSplineTail2_M.follow" 0 
		107 "IKSplineTail2_M.translateZ" 1 76 "IKSplineTail2_M.translateY" 1 
		77 "IKSplineTail2_M.translateX" 1 78 "IKSplineTail1_M.follow" 0 
		108 "IKSplineTail1_M.translateZ" 1 79 "IKSplineTail1_M.translateY" 1 
		80 "IKSplineTail1_M.translateX" 1 81 "HipSwingerRoot_M.rotateZ" 2 
		147 "HipSwingerRoot_M.rotateY" 2 148 "HipSwingerRoot_M.rotateX" 2 
		149 "FKRump_L.rotateZ" 2 150 "FKRump_L.rotateY" 2 151 "FKRump_L.rotateX" 
		2 152 "FKRump_L.translateZ" 1 88 "FKRump_L.translateY" 1 89 "FKRump_L.translateX" 
		1 90 "FKbackHip_L.rotateZ" 2 153 "FKbackHip_L.rotateY" 2 154 "FKbackHip_L.rotateX" 
		2 155 "FKbackKnee_L.rotateZ" 2 156 "FKbackKnee_L.rotateY" 2 
		157 "FKbackKnee_L.rotateX" 2 158 "FKbackFoot_L.rotateZ" 2 159 "FKbackFoot_L.rotateY" 
		2 160 "FKbackFoot_L.rotateX" 2 161 "FKRump_R.rotateZ" 2 174 "FKRump_R.rotateY" 
		2 175 "FKRump_R.rotateX" 2 176 "FKRump_R.translateZ" 1 94 "FKRump_R.translateY" 
		1 95 "FKRump_R.translateX" 1 96 "FKbackHip_R.rotateZ" 2 177 "FKbackHip_R.rotateY" 
		2 178 "FKbackHip_R.rotateX" 2 179 "FKbackKnee_R.rotateZ" 2 180 "FKbackKnee_R.rotateY" 
		2 181 "FKbackKnee_R.rotateX" 2 182 "FKbackFoot_R.rotateZ" 2 
		183 "FKbackFoot_R.rotateY" 2 184 "FKbackFoot_R.rotateX" 2 185 "FKTail0_M.rotateZ" 
		2 186 "FKTail0_M.rotateY" 2 187 "FKTail0_M.rotateX" 2 188 "FKTail1_M.rotateZ" 
		2 189 "FKTail1_M.rotateY" 2 190 "FKTail1_M.rotateX" 2 191 "FKTail2_M.rotateZ" 
		2 192 "FKTail2_M.rotateY" 2 193 "FKTail2_M.rotateX" 2 194 "FKTail3_M.rotateZ" 
		2 195 "FKTail3_M.rotateY" 2 196 "FKTail3_M.rotateX" 2 197 "FKBackA_M.rotateZ" 
		2 198 "FKBackA_M.rotateY" 2 199 "FKBackA_M.rotateX" 2 200 "FKBackB_M.rotateZ" 
		2 201 "FKBackB_M.rotateY" 2 202 "FKBackB_M.rotateX" 2 203 "FKChest_M.rotateZ" 
		2 204 "FKChest_M.rotateY" 2 205 "FKChest_M.rotateX" 2 206 "FKNeck_M.rotateZ" 
		2 219 "FKNeck_M.rotateY" 2 220 "FKNeck_M.rotateX" 2 221 "FKHead_M.Global" 
		0 121 "FKHead_M.rotateZ" 2 222 "FKHead_M.rotateY" 2 223 "FKHead_M.rotateX" 
		2 224 "Main.scaleZ" 0 122 "Main.scaleY" 0 123 "Main.scaleX" 
		0 124 "Main.rotateZ" 2 225 "Main.rotateY" 2 226 "Main.rotateX" 
		2 227 "Main.translateZ" 1 100 "Main.translateY" 1 101 "Main.translateX" 
		1 102 "Main.visibility" 0 125 "kolchan.rotateZ" 2 228 "kolchan.rotateY" 
		2 229 "kolchan.rotateX" 2 230 "yashik.rotateZ" 2 231 "yashik.rotateY" 
		2 232 "yashik.rotateX" 2 233 "yashik.translateZ" 1 103 "yashik.translateY" 
		1 104 "yashik.translateX" 1 105 "l_ear_control.rotateZ" 2 234 "l_ear_control.rotateY" 
		2 235 "l_ear_control.rotateX" 2 236 "r_ear_control1.rotateZ" 2 
		237 "r_ear_control1.rotateY" 2 238 "r_ear_control1.rotateX" 2 239 "jaw_C.rotateZ" 
		2 240 "spear_control.rotateZ" 2 241 "spear_control.rotateY" 2 
		242 "spear_control.rotateX" 2 243 "spear_control.translateZ" 1 106 "spear_control.translateY" 
		1 107 "spear_control.translateX" 1 108 "spear_control.World_Hands" 
		0 126 "IKLegFrontBall_L.rotateX" 2 244 "IKLegFrontBall_R.rotateX" 
		2 245 "IKLegFrontHeel_L.rotateZ" 2 246 "IKLegFrontHeel_L.rotateY" 
		2 247 "IKLegFrontHeel_L.rotateX" 2 248 "IKLegFrontHeel_R.rotateZ" 
		2 249 "IKLegFrontHeel_R.rotateY" 2 250 "IKLegFrontHeel_R.rotateX" 
		2 251 "IKLegFront_R.Lenght2" 0 127 "IKLegFront_R.Lenght1" 0 
		128 "IKLegFront_R.antiPop" 0 129 "IKLegFront_R.stretchy" 0 130 "IKLegFront_R.legAim" 
		0 131 "IKLegFront_R.rollAngle" 0 132 "IKLegFront_R.roll" 0 133 "IKLegFront_R.swivel" 
		0 134 "IKLegFront_R.rotateZ" 2 252 "IKLegFront_R.rotateY" 2 
		253 "IKLegFront_R.rotateX" 2 254 "IKLegFront_R.translateZ" 1 109 "IKLegFront_R.translateY" 
		1 110 "IKLegFront_R.translateX" 1 111 "IKLegFront_L.Lenght2" 0 
		135 "IKLegFront_L.Lenght1" 0 136 "IKLegFront_L.antiPop" 0 137 "IKLegFront_L.stretchy" 
		0 138 "IKLegFront_L.legAim" 0 139 "IKLegFront_L.rollAngle" 0 
		140 "IKLegFront_L.roll" 0 141 "IKLegFront_L.swivel" 0 142 "IKLegFront_L.rotateZ" 
		2 255 "IKLegFront_L.rotateY" 2 256 "IKLegFront_L.rotateX" 2 
		257 "IKLegFront_L.translateZ" 1 112 "IKLegFront_L.translateY" 1 113 "IKLegFront_L.translateX" 
		1 114 "FKIKLegFront_L.IKVis" 0 143 "FKIKLegFront_L.FKVis" 0 
		144 "FKIKLegFront_L.FKIKBlend" 0 145 "FKIKLegFront_R.IKVis" 0 146 "FKIKLegFront_R.FKVis" 
		0 147 "FKIKLegFront_R.FKIKBlend" 0 148 "FKScapula_L.rotateZ" 2 
		258 "FKScapula_L.rotateY" 2 259 "FKScapula_L.rotateX" 2 260 "FKScapula_L.translateZ" 
		1 115 "FKScapula_L.translateY" 1 116 "FKScapula_L.translateX" 1 
		117 "FKScapula_R.rotateZ" 2 261 "FKScapula_R.rotateY" 2 262 "FKScapula_R.rotateX" 
		2 263 "FKScapula_R.translateZ" 1 118 "FKScapula_R.translateY" 1 
		119 "FKScapula_R.translateX" 1 120 "FKfrontFoot_L.rotateZ" 2 264 "FKfrontFoot_L.rotateY" 
		2 265 "FKfrontFoot_L.rotateX" 2 266 "FKfrontFoot_R.rotateZ" 2 
		267 "FKfrontFoot_R.rotateY" 2 268 "FKfrontFoot_R.rotateX" 2 269 "FKfrontHip_R.rotateZ" 
		2 270 "FKfrontHip_L.rotateZ" 2 271 "FKfrontKnee_L.rotateZ" 2 
		272 "FKfrontKnee_R.rotateZ" 2 273 "PoleLegFront_L.follow" 0 149 "PoleLegFront_L.translateZ" 
		1 121 "PoleLegFront_L.translateY" 1 122 "PoleLegFront_L.translateX" 
		1 123 "PoleLegFront_R.follow" 0 150 "PoleLegFront_R.translateZ" 1 
		124 "PoleLegFront_R.translateY" 1 125 "PoleLegFront_R.translateX" 1 
		126 "curve1.translateX" 1 127 "curve1.translateY" 1 128 "curve1.translateZ" 
		1 129 "curve1.visibility" 0 151 "curve1.rotateX" 2 274 "curve1.rotateY" 
		2 275 "curve1.rotateZ" 2 276 "curve1.scaleX" 0 152 "curve1.scaleY" 
		0 153 "curve1.scaleZ" 0 154 "IKLegBackBall_R.rotateY" 2 277 "IKLegBackBall_R.rotateZ" 
		2 278 "IKLegBackBall_L.rotateY" 2 279 "IKLegBackBall_L.rotateZ" 2 
		280 "IKLegFrontBall_R.rotateY" 2 281 "IKLegFrontBall_R.rotateZ" 2 
		282 "IKLegFrontBall_L.rotateY" 2 283 "IKLegFrontBall_L.rotateZ" 2 
		284 "IKXSplineTailCurve_M.translateX" 1 130 "IKXSplineTailCurve_M.translateY" 
		1 131 "IKXSplineTailCurve_M.translateZ" 1 132 "IKXSplineTailCurve_M.rotateX" 
		2 285 "IKXSplineTailCurve_M.rotateY" 2 286 "IKXSplineTailCurve_M.rotateZ" 
		2 287 "IKXSplineTailCurve_M.scaleX" 0 155 "IKXSplineTailCurve_M.scaleY" 
		0 156 "IKXSplineTailCurve_M.scaleZ" 0 157 "IKLegBall_R_Man.rotateY" 
		2 288 "IKLegBall_R_Man.rotateZ" 2 289 "IKLegBall_L_Man.rotateY" 2 
		290 "IKLegBall_L_Man.rotateZ" 2 291  ;
	setAttr ".cd[0].cim" -type "Int32Array" 498 0 1 2 3 4
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
		 209 210 211 212 213 214 215 216 217 218 219 220
		 221 222 223 224 225 226 227 228 229 230 231 232
		 233 234 235 236 237 238 239 240 241 242 243 244
		 245 246 247 248 249 250 251 252 253 254 255 256
		 257 258 259 260 261 262 263 264 265 266 267 268
		 269 270 271 272 273 274 275 276 277 278 279 280
		 281 282 283 284 285 286 287 288 289 290 291 292
		 293 294 295 296 297 298 299 300 301 302 303 304
		 305 306 307 308 309 310 311 312 313 314 315 316
		 317 318 319 320 321 322 323 324 325 326 327 328
		 329 330 331 332 333 334 335 336 337 338 339 340
		 341 342 343 344 345 346 347 348 349 350 351 352
		 353 354 355 356 357 358 359 360 361 362 363 364
		 365 366 367 368 369 370 371 372 373 374 375 376
		 377 378 379 380 381 382 383 384 385 386 387 388
		 389 390 391 392 393 394 395 396 397 398 399 400
		 401 402 403 404 405 406 407 408 409 410 411 412
		 413 414 415 416 417 418 419 420 421 422 423 424
		 425 426 427 428 429 430 431 432 433 434 435 436
		 437 438 439 440 441 442 443 444 445 446 447 448
		 449 450 451 452 453 454 455 456 457 458 459 460
		 461 462 463 464 465 466 467 468 469 470 471 472
		 473 474 475 476 477 478 479 480 481 482 483 484
		 485 486 487 488 489 490 491 492 493 494 495 496
		 497 ;
createNode animClip -n "ability01Source";
	setAttr ".ihi" 0;
	setAttr -s 387 ".ac";
	setAttr ".ac[0:56]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes;
	setAttr ".ac[79:126]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[135:140]" yes yes yes yes yes yes;
	setAttr ".ac[148:154]" yes yes yes yes yes yes yes;
	setAttr ".ac[163:183]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes;
	setAttr ".ac[191:236]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[256:309]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[319:324]" yes yes yes yes yes yes;
	setAttr ".ac[346:448]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes no no no yes yes yes no no no no yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes;
	setAttr ".ac[459:497]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes;
	setAttr ".se" 45;
	setAttr ".ci" no;
createNode animCurveTU -n "Maugli_Center_M_Man_CenterBtwFeet";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_Center_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_Center_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_Center_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 4.0494833724385515 6 26.804558344146887 
		23 24.469500101242822 34 4.0494833724385515 45 4.0494833724385515;
createNode animCurveTL -n "Maugli_Center_M_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0.40716939257256235 23 0.40716939257256235 
		34 0 45 0;
createNode animCurveTL -n "Maugli_Center_M_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 -0.6302626469778132 23 -0.6302626469778132 
		34 0 45 0;
createNode animCurveTL -n "Maugli_Center_M_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0.057951931848128489 23 0.057951931848128489 
		34 0 45 0;
createNode animCurveTU -n "Maugli_Fingers_L_Man_MiddleFingerCurl";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBall_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegToe_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegToe_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 3.1805546814635168e-015 6 3.1805546814635168e-015 
		23 0 34 3.1805546814635168e-015 45 3.1805546814635168e-015;
createNode animCurveTA -n "Maugli_IKLegToe_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "Maugli_FKIKLeg_L_Man_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLeg_L_Man_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLeg_L_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 6 10 23 10 34 10 45 10;
createNode animCurveTA -n "Maugli_IKLegHeel_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegHeel_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -3.1805546814635168e-015 6 -3.1805546814635168e-015 
		23 0 34 -3.1805546814635168e-015 45 -3.1805546814635168e-015;
createNode animCurveTA -n "Maugli_IKLegHeel_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_PoleLeg_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_PoleLeg_L_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_PoleLeg_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 3 1 6 1 23 1 34 1 45 1;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 3 1 6 1 23 1 34 1 45 1;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 0 6 0 23 0 34 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 0 6 0 23 0 34 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 25 3 25 6 25 23 25 34 25 45 25;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 0 6 0 23 0 34 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_toe";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 0 6 0 23 0 34 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 0 6 0 23 0 34 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTA -n "Maugli_IKLeg_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -5.0105185448650458 3 -5.0105185448650458 
		6 -5.0105185448650458 23 -5.0105185448650458 34 -5.0105185448650458 45 -5.0105185448650458;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTA -n "Maugli_IKLeg_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -6.3694432300697281 3 -6.3694432300697281 
		6 -6.3694432300697281 23 -6.3694432300697281 34 -6.3694432300697281 45 -6.3694432300697281;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTA -n "Maugli_IKLeg_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 13.378201002477269 3 13.378201002477269 
		6 32.415942468810663 23 32.415942468810663 34 13.378201002477269 45 13.378201002477269;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKLeg_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.069000150376690925 3 0.069000150376690925 
		6 0.045237523572568654 23 0.045237523572568654 34 0.069000150376690925 45 0.069000150376690925;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKLeg_L_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.015303353529604964 3 -0.015303353529604964 
		6 0.34104426858443382 23 0.34104426858443382 34 -0.015303353529604964 45 -0.015303353529604964;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKLeg_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.16760982461393598 3 0.16760982461393598 
		6 0.38049137113596543 23 0.38049137113596543 34 0.16760982461393598 45 0.16760982461393598;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTU -n "Maugli_FKIKArm_L_Man_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKArm_L_Man_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKArm_L_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 6 10 23 10 34 10 45 10;
createNode animCurveTU -n "Maugli_PoleArm_L_Man_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 6 10 23 10 34 10 45 10;
createNode animCurveTL -n "Maugli_PoleArm_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.39549705228612952 6 -0.06872461810015329 
		23 -0.06872461810015329 34 0.39549705228612952 45 0.39549705228612952;
createNode animCurveTL -n "Maugli_PoleArm_L_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.86201805279910448 6 -0.63704728871179939 
		23 -0.63704728871179939 34 -0.86201805279910448 45 -0.86201805279910448;
createNode animCurveTL -n "Maugli_PoleArm_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.30818663726222251 6 0.087320748050211963 
		23 0.087320748050211963 34 -0.30818663726222251 45 -0.30818663726222251;
createNode animCurveTU -n "Maugli_IKArm_L_Man_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 3 1 6 1 23 1 34 1 45 1;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKArm_L_Man_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 3 1 6 1 23 1 34 1 45 1;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKArm_L_Man_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 0 6 0 23 0 34 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKArm_L_Man_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 0 6 0 23 0 34 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKArm_L_Man_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 0 6 0 23 0 34 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTA -n "Maugli_IKArm_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -97.78067605427789 3 -77.337333785756471 
		6 27.624822025824027 23 -18.644684402383859 29 -69.609210491344456 34 -97.78067605427789 
		45 -97.78067605427789;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_IKArm_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10.92155845877172 3 27.10337952083303 
		6 56.628248462974788 23 63.224403385985468 29 20.806088677701783 34 10.92155845877172 
		45 10.92155845877172;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_IKArm_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 14.178018067197163 3 13.729522266048951 
		6 9.295820017559743 23 35.53316290636257 29 -4.5068105493919033 34 14.178018067197163 
		45 14.178018067197163;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKArm_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.79120002893813179 3 -0.2946197474580054 
		6 -0.36853795896822411 23 -0.38784949781271877 34 -0.79120002893813179 45 -0.79120002893813179;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKArm_L_Man_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.30360130511963851 3 -0.90730144200839624 
		6 -0.10754742196419864 23 -0.17667489006208209 34 -0.30360130511963851 45 -0.30360130511963851;
	setAttr -s 6 ".kit[1:5]"  10 3 3 10 10;
	setAttr -s 6 ".kot[1:5]"  10 3 3 10 10;
createNode animCurveTL -n "Maugli_IKArm_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.80061447835185851 3 -0.55886568467067366 
		6 -0.55736055272104756 23 -0.55298590273991211 34 -0.80061447835185851 45 -0.80061447835185851;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTU -n "Maugli_Fingers_R_Man_MiddleFingerCurl";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "Maugli_FKIKSpine_M_Man_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKSpine_M_Man_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKSpine_M_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBall_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegToe_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -7.0622500768802538e-031 6 -7.0622500768802538e-031 
		23 0 34 -7.0622500768802538e-031 45 -7.0622500768802538e-031;
createNode animCurveTA -n "Maugli_IKLegToe_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 3.1805546814635168e-015 6 3.1805546814635168e-015 
		23 0 34 3.1805546814635168e-015 45 3.1805546814635168e-015;
createNode animCurveTA -n "Maugli_IKLegToe_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegHeel_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegHeel_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 3.1805546814635168e-015 6 3.1805546814635168e-015 
		23 0 34 3.1805546814635168e-015 45 3.1805546814635168e-015;
createNode animCurveTA -n "Maugli_IKLegHeel_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "Maugli_FKIKLeg_R_Man_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLeg_R_Man_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLeg_R_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 6 10 23 10 34 10 45 10;
createNode animCurveTL -n "Maugli_PoleLeg_R_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_PoleLeg_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_PoleLeg_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 3 1 6 1 23 1 34 1 45 1;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 3 1 6 1 23 1 34 1 45 1;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 0 6 0 23 0 34 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 0 6 0 23 0 34 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 25 3 25 6 25 23 25 34 25 45 25;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 0 6 0 23 0 34 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_toe";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 0 6 0 23 0 34 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 0 6 0 23 0 34 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTA -n "Maugli_IKLeg_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 0 6 0 23 0 34 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTA -n "Maugli_IKLeg_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 0 6 0 23 0 34 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTA -n "Maugli_IKLeg_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 0 6 24.044350611635338 23 24.044350611635338 
		34 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKLeg_R_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 0 6 0.10042162637528618 23 0.10042162637528618 
		34 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKLeg_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 0 6 0.3411540090036832 23 0.3411540090036832 
		34 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKLeg_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 0 6 -0.23439771265398615 23 -0.23439771265398615 
		34 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTU -n "Maugli_FKIKArm_R_Man_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKArm_R_Man_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKArm_R_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 6 10 23 10 34 10 45 10;
createNode animCurveTU -n "Maugli_PoleArm_R_Man_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 6 10 23 10 34 10 45 10;
createNode animCurveTL -n "Maugli_PoleArm_R_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_PoleArm_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_PoleArm_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.1102230246251565e-016 6 1.1102230246251565e-016 
		23 0 34 1.1102230246251565e-016 45 1.1102230246251565e-016;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -6.2725381128105917e-045 6 -6.2725381128105917e-045 
		23 0 34 -6.2725381128105917e-045 45 -6.2725381128105917e-045;
createNode animCurveTU -n "Maugli_IKArm_R_Man_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
createNode animCurveTU -n "Maugli_IKArm_R_Man_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
createNode animCurveTU -n "Maugli_IKArm_R_Man_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "Maugli_IKArm_R_Man_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "Maugli_IKArm_R_Man_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKArm_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -12.754512848885321 3 78.264420784448816 
		6 63.539746351250045 23 70.437367200615839 29 94.668518586868132 34 -19.716384343879231 
		45 -12.754512848885321;
	setAttr -s 7 ".kit[0:6]"  9 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  9 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_IKArm_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -51.071041253431346 3 -46.723896779912657 
		6 -32.499667890896987 23 -31.359693626069717 29 -68.458240886846767 34 -51.071041253431346 
		45 -51.071041253431346;
	setAttr -s 7 ".kit[0:6]"  9 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  9 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_IKArm_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -30.429381170308442 3 3.2094499504636267 
		6 -89.252570771813993 23 -88.321405539803649 29 30.708053528734133 34 -30.429381170308442 
		45 -30.429381170308442;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKArm_R_Man_translateZ";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.50891155850440861 3 -0.25613821599350906 
		6 1.5528551741084076 23 1.5214258461962935 29 0.28935009735501077 34 -0.57097834800613823 
		45 -0.50891155850440861;
	setAttr -s 7 ".kit[0:6]"  9 10 1 1 10 1 3;
	setAttr -s 7 ".kot[0:6]"  9 10 1 1 10 1 3;
	setAttr -s 7 ".kix[2:6]"  0.95733648538589478 0.99996542930603027 
		0.17260685563087463 0.86214601993560791 1;
	setAttr -s 7 ".kiy[2:6]"  0.28897562623023987 0.0083189522847533226 
		-0.98499077558517456 -0.50665998458862305 0;
	setAttr -s 7 ".kox[2:6]"  0.95733648538589478 0.9999653697013855 
		0.17260685563087463 0.86214584112167358 1;
	setAttr -s 7 ".koy[2:6]"  0.28897562623023987 0.008318733423948288 
		-0.98499077558517456 -0.50666022300720215 0;
createNode animCurveTL -n "Maugli_IKArm_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.17073023409560481 3 -1.5041538101632164 
		6 -1.4278946944678714 23 -1.3680314010071171 29 -1.2574726768320033 34 -0.12213642422923111 
		45 -0.17073023409560481;
	setAttr -s 7 ".kit[2:6]"  3 10 10 10 10;
	setAttr -s 7 ".kot[2:6]"  3 10 10 10 10;
createNode animCurveTL -n "Maugli_IKArm_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.44722353666474202 3 0.95566927975161575 
		6 1.1355576323411865 23 1.1245706873982928 29 0.70895132573201636 34 0.44174905371920636 
		45 0.44722353666474202;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  0.99955528974533081 0.27901741862297058 
		1 1 0.47309273481369019 1 1;
	setAttr -s 7 ".kiy[0:6]"  -0.029820563271641731 0.96028602123260498 
		0 0 -0.88101261854171753 0 0;
	setAttr -s 7 ".kox[0:6]"  0.99955528974533081 0.27901741862297058 
		1 1 0.47309273481369019 1 1;
	setAttr -s 7 ".koy[0:6]"  -0.029820559546351433 0.96028602123260498 
		0 0 -0.88101261854171753 0 0;
createNode animCurveTA -n "Maugli_FKScapula_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -7.1990267140314277 6 13.972486591633453 
		23 13.972486591633453 34 -7.1990267140314277 45 -7.1990267140314277;
createNode animCurveTA -n "Maugli_FKScapula_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 9.9598426785175036 6 -33.171474839132273 
		23 -33.171474839132273 34 9.9598426785175036 45 9.9598426785175036;
createNode animCurveTA -n "Maugli_FKScapula_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -7.1981747374653153 6 4.8311668289980316 
		23 4.8311668289980316 34 -7.1981747374653153 45 -7.1981747374653153;
createNode animCurveTL -n "Maugli_FKScapula_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_FKScapula_L_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_FKScapula_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -5.5511151231257827e-017 6 -5.5511151231257827e-017 
		23 0 34 -5.5511151231257827e-017 45 -5.5511151231257827e-017;
createNode animCurveTA -n "Maugli_FKMiddleFinger1_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 17.622819694952526 6 17.622819694952526 
		23 17.622819694952526 34 17.622819694952526 45 17.622819694952526;
createNode animCurveTA -n "Maugli_FKMiddleFinger2_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -23.252905752704581 6 -23.252905752704581 
		23 -23.252905752704581 34 -23.252905752704581 45 -23.252905752704581;
createNode animCurveTA -n "Maugli_FKMiddleFinger3_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_FKThumbFinger1_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -10.372922440313587 6 -10.372922440313587 
		23 -10.372922440313587 34 -10.372922440313587 45 -10.372922440313587;
createNode animCurveTA -n "Maugli_FKThumbFinger1_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 2.7620263328639107 6 2.7620263328639107 
		23 2.7620263328639107 34 2.7620263328639107 45 2.7620263328639107;
createNode animCurveTA -n "Maugli_FKThumbFinger1_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -32.466562028725463 6 -32.466562028725463 
		23 -32.466562028725463 34 -32.466562028725463 45 -32.466562028725463;
createNode animCurveTA -n "Maugli_FKThumbFinger2_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -26.277332307519721 6 -26.277332307519721 
		23 -26.277332307519721 34 -26.277332307519721 45 -26.277332307519721;
createNode animCurveTA -n "Maugli_FKBackA_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 7.8357327658317191 3 6.8172792621831046 
		6 -10.358673714473735 23 -10.358673714473735 34 1.6395961443336253 45 7.8357327658317191;
	setAttr -s 6 ".kit[0:5]"  9 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  9 10 10 10 10 10;
createNode animCurveTA -n "Maugli_FKBackA_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -7.5265731098501263 3 -9.9826106013245379 
		6 -9.9377031050817823 23 -9.9377031050817823 34 -8.0724617425593035 45 -7.5265731098501263;
	setAttr -s 6 ".kit[0:5]"  9 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  9 10 10 10 10 10;
createNode animCurveTA -n "Maugli_FKBackA_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -5.4975000363152615 3 -1.4091712028719072 
		6 -1.1091444213655748 23 -1.1091444213655748 34 -4.6558246562163275 45 -5.4975000363152615;
	setAttr -s 6 ".kit[0:5]"  9 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  9 10 10 10 10 10;
createNode animCurveTA -n "Maugli_FKBackB_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 2.7266862105714793 3 17.791206388961093 
		6 -5.2979863807373002 23 -5.2979863807373002 34 2.7266862105714793 45 2.7266862105714793;
createNode animCurveTA -n "Maugli_FKBackB_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.24259990801533335 3 12.714153577083213 
		6 1.7549030870524871 23 1.7549030870524871 34 0.24259990801533335 45 0.24259990801533335;
createNode animCurveTA -n "Maugli_FKBackB_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1.5001242681430698 3 -1.7724275856604461 
		6 -0.84900534315248688 23 -0.84900534315248688 34 1.5001242681430698 45 1.5001242681430698;
createNode animCurveTA -n "Maugli_FKChest_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -12.769021381384317 3 -16.560414330871801 
		6 -25.476615103935575 23 -25.476615103935575 34 -12.769021381384317 45 -12.769021381384317;
createNode animCurveTA -n "Maugli_FKChest_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 4.6070431346914544 3 2.7321566134889794 
		6 -0.72533904392574822 23 -0.72533904392574822 34 4.6070431346914544 45 4.6070431346914544;
createNode animCurveTA -n "Maugli_FKChest_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 4.8308420450374907 3 13.78522001518817 
		6 9.1800055701666849 23 9.1800055701666849 34 4.8308420450374907 45 4.8308420450374907;
createNode animCurveTA -n "Maugli_FKNeck_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 0.7376560378696605 6 -9.0572942471747666 
		23 -9.0572942471747666 34 0 45 0;
createNode animCurveTA -n "Maugli_FKNeck_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 5.3746445405747556 6 9.2776726579589859 
		23 9.2776726579589859 34 0 45 0;
createNode animCurveTA -n "Maugli_FKNeck_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 -9.1187668907770814 6 -10.805321183188957 
		23 -10.805321183188957 34 0 45 0;
createNode animCurveTA -n "Maugli_FKHead_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -6.9400884964770713 3 -0.028858762646364226 
		6 -10.930645712500363 23 -10.930645712500363 34 7.4278477058328445 45 -6.9400884964770713;
createNode animCurveTA -n "Maugli_FKHead_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 3.508580449788079 3 5.9617131837680546 
		6 3.9986888836947938 23 3.9986888836947938 34 3.508580449788079 45 3.508580449788079;
createNode animCurveTA -n "Maugli_FKHead_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 5.0972336912670713 3 12.426833831841654 
		6 3.0925910355728323 23 3.0925910355728323 34 5.0972336912670713 45 5.0972336912670713;
createNode animCurveTA -n "Maugli_FKScapula_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 3.6745332739058547 6 43.92945175828207 
		12 43.646045284894036 23 43.92945175828207 34 3.6745332739058547 45 3.6745332739058547;
createNode animCurveTA -n "Maugli_FKScapula_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -6.3459812884849134 6 28.814313595558197 
		12 37.159558125285784 23 28.814313595558197 34 -6.3459812884849134 45 -6.3459812884849134;
createNode animCurveTA -n "Maugli_FKScapula_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.71910078156005675 6 28.91792933253376 
		12 18.636358019953004 23 28.91792933253376 34 -0.71910078156005675 45 -0.71910078156005675;
createNode animCurveTL -n "Maugli_FKScapula_R_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -2.7755575615628914e-017 6 -2.7755575615628914e-017 
		23 0 34 -2.7755575615628914e-017 45 -2.7755575615628914e-017;
createNode animCurveTL -n "Maugli_FKScapula_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_FKScapula_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 5.5511151231257827e-017 6 5.5511151231257827e-017 
		23 0 34 5.5511151231257827e-017 45 5.5511151231257827e-017;
createNode animCurveTA -n "Maugli_FKMiddleFinger1_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_FKMiddleFinger2_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -67.588216236699324 6 -67.588216236699324 
		23 -67.588216236699324 34 -67.588216236699324 45 -67.588216236699324;
createNode animCurveTA -n "Maugli_FKMiddleFinger3_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -81.669521342510606 6 -81.669521342510606 
		23 -81.669521342510606 34 -81.669521342510606 45 -81.669521342510606;
createNode animCurveTA -n "Maugli_FKThumbFinger1_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 25.665274764482422 6 25.665274764482422 
		23 25.665274764482422 34 25.665274764482422 45 25.665274764482422;
createNode animCurveTA -n "Maugli_FKThumbFinger1_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 36.541774445263137 6 36.541774445263137 
		23 36.541774445263137 34 36.541774445263137 45 36.541774445263137;
createNode animCurveTA -n "Maugli_FKThumbFinger1_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -67.421493922591793 6 -67.421493922591793 
		23 -67.421493922591793 34 -67.421493922591793 45 -67.421493922591793;
createNode animCurveTA -n "Maugli_FKThumbFinger2_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 47.81080993924823 6 47.81080993924823 
		23 47.81080993924823 34 47.81080993924823 45 47.81080993924823;
createNode animCurveTU -n "Maugli_Main_Man_visibility";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_Center_M_CenterBtwFeet";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "Maugli_Center_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -8.4444129496952112 6 -8.4444129496952343 
		23 -8.4444129496952343 28 -6.2636833822994049 34 -8.4444129496952112 45 -8.4444129496952112;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTA -n "Maugli_Center_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.96917688750520981 6 -0.96917688750520603 
		23 -0.96917688750520603 28 -0.49172550955971817 34 -0.96917688750520947 45 -0.96917688750520981;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTA -n "Maugli_Center_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 3.1650958122187984 3 -0.31804474386109943 
		6 -24.614548488290012 23 -24.614548488290012 28 -12.221255164638229 34 3.9317352235946506 
		45 3.1650958122187984;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTL -n "Maugli_Center_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.13106792216224994 3 -0.22187674147282854 
		6 -0.65678885716174196 15 -0.70286319256800844 23 -0.56024921641311543 34 -0.2036268201491005 
		45 -0.13106792216224994;
	setAttr -s 7 ".kit[0:6]"  3 10 9 1 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 9 1 10 10 10;
	setAttr -s 7 ".kix[3:6]"  0.90963292121887207 0.78534305095672607 
		0.86305910348892212 0.98097705841064453;
	setAttr -s 7 ".kiy[3:6]"  0.41541308164596558 0.61906075477600098 
		0.50510293245315552 0.19412349164485931;
	setAttr -s 7 ".kox[3:6]"  0.90963292121887207 0.78534305095672607 
		0.86305910348892212 0.98097711801528931;
	setAttr -s 7 ".koy[3:6]"  0.41541305184364319 0.61906075477600098 
		0.50510293245315552 0.19412350654602051;
createNode animCurveTL -n "Maugli_Center_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.024349347202935689 3 0.24465163360128503 
		6 -0.4307080591694939 15 -0.6717956581386183 23 -0.46634190289785854 34 0.14308437811865893 
		45 0.024349347202935689;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  0.99872666597366333 0.40235891938209534 
		0.40002486109733582 0.99802869558334351 0.61366152763366699 0.83110630512237549 0.9513627290725708;
	setAttr -s 7 ".kiy[0:6]"  -0.050448480993509293 -0.91548198461532593 
		-0.91650426387786865 -0.062759287655353546 0.7895691990852356 0.55611354112625122 
		-0.30807295441627502;
	setAttr -s 7 ".kox[0:6]"  0.98547297716140747 0.40235891938209534 
		0.40002486109733582 0.99802869558334351 0.61366152763366699 0.83110630512237549 0.9513627290725708;
	setAttr -s 7 ".koy[0:6]"  -0.16983248293399811 -0.91548198461532593 
		-0.91650426387786865 -0.062759287655353546 0.7895691990852356 0.55611354112625122 
		-0.30807295441627502;
createNode animCurveTL -n "Maugli_Center_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.0012760952138130693 3 0.029147951158428373 
		6 -0.0046676466665312583 15 -0.0083214109382028466 23 0.00051496949227940181 34 0.0090553594102398688 
		45 -0.0012760952138130693;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_IKLegBackBall_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "Maugli_FKIKLegBack_L_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegBack_L_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegBack_L_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 6 10 23 10 34 10 45 10;
createNode animCurveTU -n "Maugli_PoleLegBack_L_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 6 10 23 10 34 10 45 10;
createNode animCurveTL -n "Maugli_PoleLegBack_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0.11363991563554407 23 0.11363991563554407 
		34 0 45 0;
createNode animCurveTL -n "Maugli_PoleLegBack_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 -0.016137706737785248 23 -0.016137706737785248 
		34 0 45 0;
createNode animCurveTL -n "Maugli_PoleLegBack_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 -0.20817956539049606 23 -0.20817956539049606 
		34 0 45 0;
createNode animCurveTU -n "Maugli_IKLegBack_L_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
createNode animCurveTU -n "Maugli_IKLegBack_L_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
createNode animCurveTU -n "Maugli_IKLegBack_L_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "Maugli_IKLegBack_L_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "Maugli_IKLegBack_L_legAim";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 6 10 23 10 34 10 45 10;
createNode animCurveTU -n "Maugli_IKLegBack_L_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 25 6 25 23 25 34 25 45 25;
createNode animCurveTU -n "Maugli_IKLegBack_L_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "Maugli_IKLegBack_L_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBack_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBack_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBack_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_IKLegBack_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_IKLegBack_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.76278640316887203 6 -0.76278640316887203 
		23 -0.76278640316887203 34 -0.76278640316887203 45 -0.76278640316887203;
createNode animCurveTL -n "Maugli_IKLegBack_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_BendNeck_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_BendNeck_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_BendNeck_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "Maugli_FKIKSpine_M_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKSpine_M_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKSpine_M_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBackBall_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "Maugli_FKIKLegBack_R_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegBack_R_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegBack_R_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 6 10 23 10 34 10 45 10;
createNode animCurveTU -n "Maugli_PoleLegBack_R_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 6 10 23 10 34 10 45 10;
createNode animCurveTL -n "Maugli_PoleLegBack_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -2.2204460492503131e-016 6 -2.2204460492503131e-016 
		23 0 34 -2.2204460492503131e-016 45 -2.2204460492503131e-016;
createNode animCurveTL -n "Maugli_PoleLegBack_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_PoleLegBack_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -5.5511151231257827e-017 6 -5.5511151231257827e-017 
		23 0 34 -5.5511151231257827e-017 45 -5.5511151231257827e-017;
createNode animCurveTU -n "Maugli_IKLegBack_R_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
createNode animCurveTU -n "Maugli_IKLegBack_R_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
createNode animCurveTU -n "Maugli_IKLegBack_R_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "Maugli_IKLegBack_R_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "Maugli_IKLegBack_R_legAim";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 6 10 23 10 34 10 45 10;
createNode animCurveTU -n "Maugli_IKLegBack_R_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 25 6 25 23 25 34 25 45 25;
createNode animCurveTU -n "Maugli_IKLegBack_R_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "Maugli_IKLegBack_R_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBack_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -17.042137663821414 6 -17.042137663821414 
		23 -17.042137663821414 34 -17.042137663821414 45 -17.042137663821414;
createNode animCurveTA -n "Maugli_IKLegBack_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBack_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_IKLegBack_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.1102230246251563e-016 6 1.1102230246251563e-016 
		23 0 34 1.1102230246251563e-016 45 1.1102230246251563e-016;
createNode animCurveTL -n "Maugli_IKLegBack_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.019491142195864015 6 0.019491142195864015 
		23 0.019491142195864015 34 0.019491142195864015 45 0.019491142195864015;
createNode animCurveTL -n "Maugli_IKLegBack_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.063585363072848899 6 -0.063585363072848899 
		23 -0.063585363072848899 34 -0.063585363072848899 45 -0.063585363072848899;
createNode animCurveTU -n "Maugli_FKIKSplineTail_M_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKSplineTail_M_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKSplineTail_M_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 6 10 23 10 34 10 45 10;
createNode animCurveTU -n "Maugli_WagCurveSplineTail_M_increment";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
createNode animCurveTU -n "Maugli_WagCurveSplineTail_M_multiply";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
createNode animCurveTU -n "Maugli_WagCurveSplineTail_M_timeOffset";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
createNode animCurveTU -n "Maugli_WagCurveSplineTail_M_enable";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTA -n "Maugli_WagCurveSplineTail_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_WagCurveSplineTail_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_WagCurveSplineTail_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "Maugli_IKSplineTail2_M_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "Maugli_IKSplineTail2_M_twist";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "Maugli_IKSplineTail2_M_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_IKSplineTail2_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.31618923007172439 6 -0.56480132462039268 
		12 0.2391964174164396 23 -0.96080639910172083 34 -0.55329789367464299 45 -0.31618923007172439;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKSplineTail2_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -1.0020975550085076 6 -0.59337542237490037 
		12 -0.61115130188677858 23 -0.61115130188677858 34 -1.3025513121533092 45 -1.0020975550085076;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKSplineTail2_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.80886811842270168 6 0.40905563758135244 
		12 -0.26836370401124476 23 0.056045345140765979 34 0.11757355079987752 45 0.80886811842270168;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKSplineTail1_M_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_IKSplineTail1_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 3.1086244689504383e-015 6 0.080470788007565686 
		12 -1.1982843569672146 23 -1.2301312836005753 34 -0.158959123888192 45 3.1086244689504383e-015;
createNode animCurveTL -n "Maugli_IKSplineTail1_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.16519211009181056 6 -0.51022840784311252 
		12 -1.1767822945389022 23 -1.181704634325514 34 -0.29005103871861748 45 -0.16519211009181056;
	setAttr -s 6 ".kit[0:5]"  9 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  9 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKSplineTail1_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.010972047845733357 6 -0.26250777561929461 
		12 0.13173605787888742 23 -0.048375971335961387 34 0.014169630580868287 45 0.010972047845733357;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_FKRump_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -18.638044314952673 6 -18.638044314952673 
		23 -18.638044314952673 34 -18.638044314952673 45 -18.638044314952673;
createNode animCurveTA -n "Maugli_FKRump_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 5.9273289705481567 6 5.9273289705481567 
		23 5.9273289705481567 34 5.9273289705481567 45 5.9273289705481567;
createNode animCurveTA -n "Maugli_FKRump_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 12.021048230974857 6 12.021048230974857 
		23 12.021048230974857 34 12.021048230974857 45 12.021048230974857;
createNode animCurveTL -n "Maugli_FKRump_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -5.5511151231257827e-017 6 -5.5511151231257827e-017 
		23 0 34 -5.5511151231257827e-017 45 -5.5511151231257827e-017;
createNode animCurveTL -n "Maugli_FKRump_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 2.2204460492503131e-016 6 2.2204460492503131e-016 
		23 0 34 2.2204460492503131e-016 45 2.2204460492503131e-016;
createNode animCurveTL -n "Maugli_FKRump_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 2.2204460492503131e-016 6 2.2204460492503131e-016 
		23 0 34 2.2204460492503131e-016 45 2.2204460492503131e-016;
createNode animCurveTA -n "Maugli_FKRump_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -18.710504463926263 6 -18.710504463926263 
		16 -12.39895461070885 23 -18.710504463926263 34 -18.710504463926263 45 -18.710504463926263;
createNode animCurveTA -n "Maugli_FKRump_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 8.2582530676151027 6 8.2582530676151027 
		16 7.6511017210204368 23 8.2582530676151027 34 8.2582530676151027 45 8.2582530676151027;
createNode animCurveTA -n "Maugli_FKRump_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 5.1050521316126698 6 5.1050521316126698 
		16 5.9793854250853657 23 5.1050521316126698 34 5.1050521316126698 45 5.1050521316126698;
createNode animCurveTL -n "Maugli_FKRump_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 5.5511151231257827e-017 6 5.5511151231257827e-017 
		23 0 34 5.5511151231257827e-017 45 5.5511151231257827e-017;
createNode animCurveTL -n "Maugli_FKRump_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_FKRump_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_FKBackA_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -6.1344158462123248 6 1.5708649270949848 
		23 1.5232377137554021 34 -6.1344158462123248 45 -6.1344158462123248;
createNode animCurveTA -n "Maugli_FKBackA_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -2.6442010631261756 6 -2.6584093135356595 
		23 -1.5355340924258152 34 -2.6442010631261756 45 -2.6442010631261756;
createNode animCurveTA -n "Maugli_FKBackA_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.28408691297585409 6 -0.072877057314549423 
		23 -0.4843405857435405 34 0.28408691297585409 45 0.28408691297585409;
createNode animCurveTA -n "Maugli_FKBackB_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -4.0937696667714745 3 3.1851617158919376 
		6 -2.1535759057712749 23 -7.6194942643638166 34 -4.0937696667714745 45 -4.0937696667714745;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTA -n "Maugli_FKBackB_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -8.7401097734428159 3 -6.0908673736001058 
		6 -3.163706874026559 23 -1.1559513501901444 34 -8.7401097734428159 45 -8.7401097734428159;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTA -n "Maugli_FKBackB_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.62309581808855541 3 0.93628596106759354 
		6 2.5743909164562537 23 2.0257655731191551 34 0.62309581808855541 45 0.62309581808855541;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTA -n "Maugli_FKChest_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -25.928322657740519 6 -21.564581590779433 
		23 -20.809492631066494 28 -23.303873116683945 34 -25.928322657740519 45 -25.928322657740519;
createNode animCurveTA -n "Maugli_FKChest_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -6.0685067306724134 6 -6.6726139940139113 
		23 -3.7723225497162085 28 -11.233419890386454 34 -6.0685067306724134 45 -6.0685067306724134;
createNode animCurveTA -n "Maugli_FKChest_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 2.6635387051032011 6 1.5182230731329178 
		23 2.3091796721804574 28 2.0110805283398947 34 2.6635387051032011 45 2.6635387051032011;
createNode animCurveTA -n "Maugli_FKNeck_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 22.628337533497174 3 41.678226433402578 
		6 32.707578747224211 23 26.984146138345203 34 31.683917875347852 45 22.628337533497174;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTA -n "Maugli_FKNeck_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 3.6826813105759961 3 -4.4810597381125836 
		6 -8.2375569813888756 23 7.2070949910126005 34 3.6826813105759952 45 3.6826813105759961;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTA -n "Maugli_FKNeck_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 2.2991021693981635 3 10.498101502216311 
		6 8.3438708018834706 23 0.50347579563169842 34 2.2991021693981639 45 2.2991021693981635;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTU -n "Maugli_FKHead_M_Global";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 6 10 23 10 34 10 45 10;
createNode animCurveTA -n "Maugli_FKHead_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -7.8426637274840703 3 16.863962435410844 
		6 -22.235838751870229 23 -62.543339782992504 34 -7.8426637274840703 45 -7.8426637274840703;
createNode animCurveTA -n "Maugli_FKHead_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -7.5490945101966842 3 17.953998506786398 
		6 -20.452221181829501 23 4.8844439774726691 34 -7.5490945101966842 45 -7.5490945101966842;
createNode animCurveTA -n "Maugli_FKHead_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 5.461028169262887 3 37.013778232893067 
		6 21.829193416401878 23 -19.026851508947328 34 5.461028169262887 45 5.461028169262887;
createNode animCurveTU -n "Maugli_Main_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
createNode animCurveTU -n "Maugli_Main_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
createNode animCurveTU -n "Maugli_Main_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
createNode animCurveTA -n "Maugli_Main_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_Main_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_Main_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_Main_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_Main_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_Main_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "Maugli_Main_visibility";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTA -n "Maugli_kolchan_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -16.498609615445837 3 -6.2857959681158517 
		6 -1.4488429177603113 13 -26.342787831615002 23 -16.498609615445837 34 -0.91453897280914243 
		45 -16.498609615445837;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_kolchan_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -6.4006181765439756 3 -6.6191838674605856 
		6 -6.6502830839388176 13 -4.7503709188579393 23 -6.4006181765439756 34 -6.6508398518396268 
		45 -6.4006181765439756;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_kolchan_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.8111494521402616 3 0.65023481395916838 
		6 0.0910487942406598 13 -3.1298459485579646 23 1.8111494521402616 34 0.029168623583269288 
		45 1.8111494521402616;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_yashik_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_yashik_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_yashik_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_yashik_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_yashik_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_yashik_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_l_ear_control_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 -75.790019548807919 23 -75.790019548807919 
		34 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "Maugli_l_ear_control_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 19.002640290439679 23 19.002640290439679 
		34 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "Maugli_l_ear_control_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 29.926601716007216 23 29.926601716007216 
		34 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "Maugli_r_ear_control1_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 -52.718616700919284 23 -52.718616700919284 
		34 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "Maugli_r_ear_control1_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 -7.7471413195830161 23 -7.7471413195830161 
		34 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "Maugli_r_ear_control1_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 -57.164096342872824 23 -57.164096342872824 
		34 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "Maugli_jaw_C_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 13.314636802006575 6 0 23 -4.4792081060940552 
		34 5.8537406002132508 45 0;
createNode animCurveTA -n "Maugli_spear_control_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_spear_control_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_spear_control_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_spear_control_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.041982630251665931 6 0.041982630251665931 
		23 0.041982630251665931 34 0.041982630251665931 45 0.041982630251665931;
createNode animCurveTL -n "Maugli_spear_control_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.05682005777595385 6 -0.05682005777595385 
		23 -0.05682005777595385 34 -0.05682005777595385 45 -0.05682005777595385;
createNode animCurveTL -n "Maugli_spear_control_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.19304667407551657 6 0.19304667407551657 
		23 0.19304667407551657 34 0.19304667407551657 45 0.19304667407551657;
createNode animCurveTU -n "Maugli_spear_control_World_Hands";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTA -n "Maugli_IKLegFrontBall_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegFrontBall_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.1 6 1.1 23 1.1 34 1.1 45 1.1;
createNode animCurveTU -n "Maugli_IKLegFront_R_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.1 6 1.1 23 1.1 34 1.1 45 1.1;
createNode animCurveTU -n "Maugli_IKLegFront_R_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_legAim";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 6 10 23 10 34 10 45 10;
createNode animCurveTU -n "Maugli_IKLegFront_R_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 25 6 25 23 25 34 25 45 25;
createNode animCurveTU -n "Maugli_IKLegFront_R_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegFront_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 13.452853449395933 6 13.452853449395933 
		23 13.452853449395933 34 13.452853449395933 45 13.452853449395933;
createNode animCurveTA -n "Maugli_IKLegFront_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegFront_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 23 0 28 27.601207894645906 34 0 
		45 0;
createNode animCurveTL -n "Maugli_IKLegFront_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 5.5511151231257852e-017 6 5.5511151231257852e-017 
		23 0 28 0.15734413659073659 34 5.5511151231257852e-017 45 5.5511151231257852e-017;
createNode animCurveTL -n "Maugli_IKLegFront_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.78767523172948961 6 -0.78767523172948961 
		23 -0.78767523172948961 34 -0.78767523172948961 45 -0.78767523172948961;
createNode animCurveTL -n "Maugli_IKLegFront_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.077325821529500835 6 -0.077325821529500835 
		23 -0.077325821529500835 34 -0.077325821529500835 45 -0.077325821529500835;
createNode animCurveTU -n "Maugli_IKLegFront_L_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.1 6 1.1 23 1.1 34 1.1 45 1.1;
createNode animCurveTU -n "Maugli_IKLegFront_L_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.1 6 1.1 23 1.1 34 1.1 45 1.1;
createNode animCurveTU -n "Maugli_IKLegFront_L_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "Maugli_IKLegFront_L_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "Maugli_IKLegFront_L_legAim";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 6 10 23 10 34 10 45 10;
createNode animCurveTU -n "Maugli_IKLegFront_L_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 25 6 25 23 25 34 25 45 25;
createNode animCurveTU -n "Maugli_IKLegFront_L_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "Maugli_IKLegFront_L_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegFront_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -4.3689304491953465 6 -4.3689304491953465 
		23 -4.3689304491953465 34 -4.3689304491953465 45 -4.3689304491953465;
createNode animCurveTA -n "Maugli_IKLegFront_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_IKLegFront_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_IKLegFront_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_IKLegFront_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.063844748963588188 6 -0.063844748963588188 
		23 -0.063844748963588188 34 -0.063844748963588188 45 -0.063844748963588188;
createNode animCurveTL -n "Maugli_IKLegFront_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.072835230653514785 6 -0.072835230653514785 
		23 -0.072835230653514785 34 -0.072835230653514785 45 -0.072835230653514785;
createNode animCurveTU -n "Maugli_FKIKLegFront_L_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegFront_L_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegFront_L_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 6 10 23 10 34 10 45 10;
createNode animCurveTU -n "Maugli_FKIKLegFront_R_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegFront_R_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegFront_R_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 6 10 23 10 34 10 45 10;
createNode animCurveTA -n "Maugli_FKScapula_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_FKScapula_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_FKScapula_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_FKScapula_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -2.2204460492503131e-016 6 -2.2204460492503131e-016 
		23 0 34 -2.2204460492503131e-016 45 -2.2204460492503131e-016;
createNode animCurveTL -n "Maugli_FKScapula_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.1102230246251565e-016 6 -1.1102230246251565e-016 
		23 0 34 -1.1102230246251565e-016 45 -1.1102230246251565e-016;
createNode animCurveTL -n "Maugli_FKScapula_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 4.4408920985006262e-016 6 4.4408920985006262e-016 
		23 0 34 4.4408920985006262e-016 45 4.4408920985006262e-016;
createNode animCurveTA -n "Maugli_FKScapula_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_FKScapula_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "Maugli_FKScapula_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "Maugli_FKScapula_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.1102230246251565e-016 6 -1.1102230246251565e-016 
		23 0 34 -1.1102230246251565e-016 45 -1.1102230246251565e-016;
createNode animCurveTL -n "Maugli_FKScapula_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -2.2204460492503131e-016 6 -2.2204460492503131e-016 
		23 0 34 -2.2204460492503131e-016 45 -2.2204460492503131e-016;
createNode animCurveTL -n "Maugli_FKScapula_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -2.2204460492503131e-016 6 -2.2204460492503131e-016 
		23 0 34 -2.2204460492503131e-016 45 -2.2204460492503131e-016;
createNode animCurveTU -n "Maugli_PoleLegFront_L_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 6 10 23 10 34 10 45 10;
createNode animCurveTL -n "Maugli_PoleLegFront_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.34369246973235407 6 0.34369246973235407 
		23 0.34369246973235407 34 0.34369246973235407 45 0.34369246973235407;
createNode animCurveTL -n "Maugli_PoleLegFront_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.08732959492146955 6 0.08732959492146955 
		23 0.08732959492146955 34 0.08732959492146955 45 0.08732959492146955;
createNode animCurveTL -n "Maugli_PoleLegFront_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.27202670267238233 6 -0.27202670267238233 
		23 -0.27202670267238233 34 -0.27202670267238233 45 -0.27202670267238233;
createNode animCurveTU -n "Maugli_PoleLegFront_R_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 6 10 23 10 34 10 45 10;
createNode animCurveTL -n "Maugli_PoleLegFront_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.31678960075780738 6 0.31678960075780738 
		23 0.31678960075780738 34 0.31678960075780738 45 0.31678960075780738;
createNode animCurveTL -n "Maugli_PoleLegFront_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.11971028970415042 6 -0.11971028970415042 
		23 -0.11971028970415042 34 -0.11971028970415042 45 -0.11971028970415042;
createNode animCurveTL -n "Maugli_PoleLegFront_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.0005730959429199018 6 0.0005730959429199018 
		23 0.0005730959429199018 34 0.0005730959429199018 45 0.0005730959429199018;
createNode animCurveTL -n "curve1_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "curve1_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "curve1_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "curve1_visibility";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTA -n "curve1_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "curve1_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "curve1_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTU -n "curve1_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
createNode animCurveTU -n "curve1_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
createNode animCurveTU -n "curve1_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
createNode animCurveTA -n "IKLegBackBall_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  18 0 34 0 45 0;
createNode animCurveTA -n "IKLegBackBall_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  18 0 34 0 45 0;
createNode animCurveTA -n "IKLegBackBall_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  18 0 34 0 45 0;
createNode animCurveTA -n "IKLegBackBall_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  18 0 34 0 45 0;
createNode animCurveTA -n "IKLegFrontBall_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  18 0 34 0 45 0;
createNode animCurveTA -n "IKLegFrontBall_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  18 0 34 0 45 0;
createNode animCurveTA -n "IKLegFrontBall_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  18 0 34 0 45 0;
createNode animCurveTA -n "IKLegFrontBall_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  18 0 34 0 45 0;
createNode animCurveTL -n "IKXSplineTailCurve_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 4.0142992214232583e-036 6 4.0142992214232583e-036 
		23 0 34 4.0142992214232583e-036 45 4.0142992214232583e-036;
createNode animCurveTL -n "IKXSplineTailCurve_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTL -n "IKXSplineTailCurve_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 23 0 34 0 45 0;
createNode animCurveTA -n "IKXSplineTailCurve_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.272221872585407e-014 6 -1.272221872585407e-014 
		23 0 34 -1.272221872585407e-014 45 -1.272221872585407e-014;
createNode animCurveTA -n "IKXSplineTailCurve_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.2722218725854067e-014 6 1.2722218725854067e-014 
		23 0 34 1.2722218725854067e-014 45 1.2722218725854067e-014;
createNode animCurveTA -n "IKXSplineTailCurve_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 2.8249000307521015e-030 6 2.8249000307521015e-030 
		23 0 34 2.8249000307521015e-030 45 2.8249000307521015e-030;
createNode animCurveTU -n "IKXSplineTailCurve_M_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
createNode animCurveTU -n "IKXSplineTailCurve_M_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
createNode animCurveTU -n "IKXSplineTailCurve_M_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 6 1 23 1 34 1 45 1;
createNode animCurveTA -n "IKLegBall_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  18 0 34 0 45 0;
createNode animCurveTA -n "IKLegBall_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  18 0 34 0 45 0;
createNode animCurveTA -n "IKLegBall_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  18 0 34 0 45 0;
createNode animCurveTA -n "IKLegBall_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  18 0 34 0 45 0;
createNode lightLinker -n "lightLinker3";
	setAttr -s 7 ".lnk";
	setAttr -s 7 ".slnk";
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
	setAttr -s 7 ".st";
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
	setAttr -s 7 ".s";
select -ne :postProcessList1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -s 11 ".u";
select -ne :lightList1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
select -ne :defaultTextureList1;
	setAttr -s 4 ".tx";
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
	setAttr -s 660 ".gn";
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
	addAttr -ci true -sn "shave_old_preRenderMel" -ln "shave_old_preRenderMel" -dt "string";
	addAttr -ci true -sn "shave_old_postRenderMel" -ln "shave_old_postRenderMel" -dt "string";
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
	setAttr -av ".bfs";
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
	setAttr ".prm" -type "string" "";
	setAttr ".pom" -type "string" "";
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
	setAttr ".shave_old_preRenderMel" -type "string" "";
	setAttr ".shave_old_postRenderMel" -type "string" "";
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
	setAttr -s 5 ".sol";
connectAttr "ability01Source.cl" "clipLibrary1.sc[0]";
connectAttr "Maugli_Center_M_Man_CenterBtwFeet.a" "clipLibrary1.cel[0].cev[0].cevr"
		;
connectAttr "Maugli_Center_M_Man_rotateZ.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "Maugli_Center_M_Man_rotateY.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "Maugli_Center_M_Man_rotateX.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "Maugli_Center_M_Man_translateZ.a" "clipLibrary1.cel[0].cev[4].cevr"
		;
connectAttr "Maugli_Center_M_Man_translateY.a" "clipLibrary1.cel[0].cev[5].cevr"
		;
connectAttr "Maugli_Center_M_Man_translateX.a" "clipLibrary1.cel[0].cev[6].cevr"
		;
connectAttr "Maugli_Fingers_L_Man_MiddleFingerCurl.a" "clipLibrary1.cel[0].cev[7].cevr"
		;
connectAttr "Maugli_IKLegBall_L_Man_rotateX.a" "clipLibrary1.cel[0].cev[8].cevr"
		;
connectAttr "Maugli_IKLegToe_L_Man_rotateZ.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "Maugli_IKLegToe_L_Man_rotateY.a" "clipLibrary1.cel[0].cev[10].cevr"
		;
connectAttr "Maugli_IKLegToe_L_Man_rotateX.a" "clipLibrary1.cel[0].cev[11].cevr"
		;
connectAttr "Maugli_FKIKLeg_L_Man_IKVis.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "Maugli_FKIKLeg_L_Man_FKVis.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "Maugli_FKIKLeg_L_Man_FKIKBlend.a" "clipLibrary1.cel[0].cev[14].cevr"
		;
connectAttr "Maugli_IKLegHeel_L_Man_rotateZ.a" "clipLibrary1.cel[0].cev[15].cevr"
		;
connectAttr "Maugli_IKLegHeel_L_Man_rotateY.a" "clipLibrary1.cel[0].cev[16].cevr"
		;
connectAttr "Maugli_IKLegHeel_L_Man_rotateX.a" "clipLibrary1.cel[0].cev[17].cevr"
		;
connectAttr "Maugli_PoleLeg_L_Man_translateZ.a" "clipLibrary1.cel[0].cev[18].cevr"
		;
connectAttr "Maugli_PoleLeg_L_Man_translateY.a" "clipLibrary1.cel[0].cev[19].cevr"
		;
connectAttr "Maugli_PoleLeg_L_Man_translateX.a" "clipLibrary1.cel[0].cev[20].cevr"
		;
connectAttr "Maugli_IKLeg_L_Man_Lenght2.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "Maugli_IKLeg_L_Man_Lenght1.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "Maugli_IKLeg_L_Man_antiPop.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "Maugli_IKLeg_L_Man_stretchy.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "Maugli_IKLeg_L_Man_rollAngle.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "Maugli_IKLeg_L_Man_roll.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "Maugli_IKLeg_L_Man_toe.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "Maugli_IKLeg_L_Man_swivel.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "Maugli_IKLeg_L_Man_rotateZ.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "Maugli_IKLeg_L_Man_rotateY.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "Maugli_IKLeg_L_Man_rotateX.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "Maugli_IKLeg_L_Man_translateZ.a" "clipLibrary1.cel[0].cev[32].cevr"
		;
connectAttr "Maugli_IKLeg_L_Man_translateY.a" "clipLibrary1.cel[0].cev[33].cevr"
		;
connectAttr "Maugli_IKLeg_L_Man_translateX.a" "clipLibrary1.cel[0].cev[34].cevr"
		;
connectAttr "Maugli_FKIKArm_L_Man_IKVis.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "Maugli_FKIKArm_L_Man_FKVis.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "Maugli_FKIKArm_L_Man_FKIKBlend.a" "clipLibrary1.cel[0].cev[37].cevr"
		;
connectAttr "Maugli_PoleArm_L_Man_follow.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "Maugli_PoleArm_L_Man_translateZ.a" "clipLibrary1.cel[0].cev[39].cevr"
		;
connectAttr "Maugli_PoleArm_L_Man_translateY.a" "clipLibrary1.cel[0].cev[40].cevr"
		;
connectAttr "Maugli_PoleArm_L_Man_translateX.a" "clipLibrary1.cel[0].cev[41].cevr"
		;
connectAttr "Maugli_IKArm_L_Man_Lenght2.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "Maugli_IKArm_L_Man_Lenght1.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "Maugli_IKArm_L_Man_antiPop.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "Maugli_IKArm_L_Man_stretchy.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "Maugli_IKArm_L_Man_follow.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "Maugli_IKArm_L_Man_rotateZ.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "Maugli_IKArm_L_Man_rotateY.a" "clipLibrary1.cel[0].cev[48].cevr";
connectAttr "Maugli_IKArm_L_Man_rotateX.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "Maugli_IKArm_L_Man_translateZ.a" "clipLibrary1.cel[0].cev[50].cevr"
		;
connectAttr "Maugli_IKArm_L_Man_translateY.a" "clipLibrary1.cel[0].cev[51].cevr"
		;
connectAttr "Maugli_IKArm_L_Man_translateX.a" "clipLibrary1.cel[0].cev[52].cevr"
		;
connectAttr "Maugli_Fingers_R_Man_MiddleFingerCurl.a" "clipLibrary1.cel[0].cev[53].cevr"
		;
connectAttr "Maugli_FKIKSpine_M_Man_IKVis.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "Maugli_FKIKSpine_M_Man_FKVis.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "Maugli_FKIKSpine_M_Man_FKIKBlend.a" "clipLibrary1.cel[0].cev[56].cevr"
		;
connectAttr "Maugli_IKLegBall_R_Man_rotateX.a" "clipLibrary1.cel[0].cev[79].cevr"
		;
connectAttr "Maugli_IKLegToe_R_Man_rotateZ.a" "clipLibrary1.cel[0].cev[80].cevr"
		;
connectAttr "Maugli_IKLegToe_R_Man_rotateY.a" "clipLibrary1.cel[0].cev[81].cevr"
		;
connectAttr "Maugli_IKLegToe_R_Man_rotateX.a" "clipLibrary1.cel[0].cev[82].cevr"
		;
connectAttr "Maugli_IKLegHeel_R_Man_rotateZ.a" "clipLibrary1.cel[0].cev[83].cevr"
		;
connectAttr "Maugli_IKLegHeel_R_Man_rotateY.a" "clipLibrary1.cel[0].cev[84].cevr"
		;
connectAttr "Maugli_IKLegHeel_R_Man_rotateX.a" "clipLibrary1.cel[0].cev[85].cevr"
		;
connectAttr "Maugli_FKIKLeg_R_Man_IKVis.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "Maugli_FKIKLeg_R_Man_FKVis.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "Maugli_FKIKLeg_R_Man_FKIKBlend.a" "clipLibrary1.cel[0].cev[88].cevr"
		;
connectAttr "Maugli_PoleLeg_R_Man_translateZ.a" "clipLibrary1.cel[0].cev[89].cevr"
		;
connectAttr "Maugli_PoleLeg_R_Man_translateY.a" "clipLibrary1.cel[0].cev[90].cevr"
		;
connectAttr "Maugli_PoleLeg_R_Man_translateX.a" "clipLibrary1.cel[0].cev[91].cevr"
		;
connectAttr "Maugli_IKLeg_R_Man_Lenght2.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "Maugli_IKLeg_R_Man_Lenght1.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "Maugli_IKLeg_R_Man_antiPop.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "Maugli_IKLeg_R_Man_stretchy.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "Maugli_IKLeg_R_Man_rollAngle.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "Maugli_IKLeg_R_Man_roll.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "Maugli_IKLeg_R_Man_toe.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "Maugli_IKLeg_R_Man_swivel.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "Maugli_IKLeg_R_Man_rotateZ.a" "clipLibrary1.cel[0].cev[100].cevr";
connectAttr "Maugli_IKLeg_R_Man_rotateY.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "Maugli_IKLeg_R_Man_rotateX.a" "clipLibrary1.cel[0].cev[102].cevr";
connectAttr "Maugli_IKLeg_R_Man_translateZ.a" "clipLibrary1.cel[0].cev[103].cevr"
		;
connectAttr "Maugli_IKLeg_R_Man_translateY.a" "clipLibrary1.cel[0].cev[104].cevr"
		;
connectAttr "Maugli_IKLeg_R_Man_translateX.a" "clipLibrary1.cel[0].cev[105].cevr"
		;
connectAttr "Maugli_FKIKArm_R_Man_IKVis.a" "clipLibrary1.cel[0].cev[106].cevr";
connectAttr "Maugli_FKIKArm_R_Man_FKVis.a" "clipLibrary1.cel[0].cev[107].cevr";
connectAttr "Maugli_FKIKArm_R_Man_FKIKBlend.a" "clipLibrary1.cel[0].cev[108].cevr"
		;
connectAttr "Maugli_PoleArm_R_Man_follow.a" "clipLibrary1.cel[0].cev[109].cevr";
connectAttr "Maugli_PoleArm_R_Man_translateZ.a" "clipLibrary1.cel[0].cev[110].cevr"
		;
connectAttr "Maugli_PoleArm_R_Man_translateY.a" "clipLibrary1.cel[0].cev[111].cevr"
		;
connectAttr "Maugli_PoleArm_R_Man_translateX.a" "clipLibrary1.cel[0].cev[112].cevr"
		;
connectAttr "Maugli_HipSwingerRoot_M_Man_rotateZ.a" "clipLibrary1.cel[0].cev[113].cevr"
		;
connectAttr "Maugli_HipSwingerRoot_M_Man_rotateY.a" "clipLibrary1.cel[0].cev[114].cevr"
		;
connectAttr "Maugli_HipSwingerRoot_M_Man_rotateX.a" "clipLibrary1.cel[0].cev[115].cevr"
		;
connectAttr "Maugli_IKArm_R_Man_Lenght2.a" "clipLibrary1.cel[0].cev[116].cevr";
connectAttr "Maugli_IKArm_R_Man_Lenght1.a" "clipLibrary1.cel[0].cev[117].cevr";
connectAttr "Maugli_IKArm_R_Man_antiPop.a" "clipLibrary1.cel[0].cev[118].cevr";
connectAttr "Maugli_IKArm_R_Man_stretchy.a" "clipLibrary1.cel[0].cev[119].cevr";
connectAttr "Maugli_IKArm_R_Man_follow.a" "clipLibrary1.cel[0].cev[120].cevr";
connectAttr "Maugli_IKArm_R_Man_rotateZ.a" "clipLibrary1.cel[0].cev[121].cevr";
connectAttr "Maugli_IKArm_R_Man_rotateY.a" "clipLibrary1.cel[0].cev[122].cevr";
connectAttr "Maugli_IKArm_R_Man_rotateX.a" "clipLibrary1.cel[0].cev[123].cevr";
connectAttr "Maugli_IKArm_R_Man_translateZ.a" "clipLibrary1.cel[0].cev[124].cevr"
		;
connectAttr "Maugli_IKArm_R_Man_translateY.a" "clipLibrary1.cel[0].cev[125].cevr"
		;
connectAttr "Maugli_IKArm_R_Man_translateX.a" "clipLibrary1.cel[0].cev[126].cevr"
		;
connectAttr "Maugli_FKScapula_L_Man_rotateZ.a" "clipLibrary1.cel[0].cev[135].cevr"
		;
connectAttr "Maugli_FKScapula_L_Man_rotateY.a" "clipLibrary1.cel[0].cev[136].cevr"
		;
connectAttr "Maugli_FKScapula_L_Man_rotateX.a" "clipLibrary1.cel[0].cev[137].cevr"
		;
connectAttr "Maugli_FKScapula_L_Man_translateZ.a" "clipLibrary1.cel[0].cev[138].cevr"
		;
connectAttr "Maugli_FKScapula_L_Man_translateY.a" "clipLibrary1.cel[0].cev[139].cevr"
		;
connectAttr "Maugli_FKScapula_L_Man_translateX.a" "clipLibrary1.cel[0].cev[140].cevr"
		;
connectAttr "Maugli_FKMiddleFinger1_L_Man_rotateZ.a" "clipLibrary1.cel[0].cev[148].cevr"
		;
connectAttr "Maugli_FKMiddleFinger2_L_Man_rotateZ.a" "clipLibrary1.cel[0].cev[149].cevr"
		;
connectAttr "Maugli_FKMiddleFinger3_L_Man_rotateZ.a" "clipLibrary1.cel[0].cev[150].cevr"
		;
connectAttr "Maugli_FKThumbFinger1_L_Man_rotateZ.a" "clipLibrary1.cel[0].cev[151].cevr"
		;
connectAttr "Maugli_FKThumbFinger1_L_Man_rotateY.a" "clipLibrary1.cel[0].cev[152].cevr"
		;
connectAttr "Maugli_FKThumbFinger1_L_Man_rotateX.a" "clipLibrary1.cel[0].cev[153].cevr"
		;
connectAttr "Maugli_FKThumbFinger2_L_Man_rotateY.a" "clipLibrary1.cel[0].cev[154].cevr"
		;
connectAttr "Maugli_FKBackA_M_Man_rotateZ.a" "clipLibrary1.cel[0].cev[163].cevr"
		;
connectAttr "Maugli_FKBackA_M_Man_rotateY.a" "clipLibrary1.cel[0].cev[164].cevr"
		;
connectAttr "Maugli_FKBackA_M_Man_rotateX.a" "clipLibrary1.cel[0].cev[165].cevr"
		;
connectAttr "Maugli_FKBackB_M_Man_rotateZ.a" "clipLibrary1.cel[0].cev[166].cevr"
		;
connectAttr "Maugli_FKBackB_M_Man_rotateY.a" "clipLibrary1.cel[0].cev[167].cevr"
		;
connectAttr "Maugli_FKBackB_M_Man_rotateX.a" "clipLibrary1.cel[0].cev[168].cevr"
		;
connectAttr "Maugli_FKChest_M_Man_rotateZ.a" "clipLibrary1.cel[0].cev[169].cevr"
		;
connectAttr "Maugli_FKChest_M_Man_rotateY.a" "clipLibrary1.cel[0].cev[170].cevr"
		;
connectAttr "Maugli_FKChest_M_Man_rotateX.a" "clipLibrary1.cel[0].cev[171].cevr"
		;
connectAttr "Maugli_FKNeck_M_Man_rotateZ.a" "clipLibrary1.cel[0].cev[172].cevr";
connectAttr "Maugli_FKNeck_M_Man_rotateY.a" "clipLibrary1.cel[0].cev[173].cevr";
connectAttr "Maugli_FKNeck_M_Man_rotateX.a" "clipLibrary1.cel[0].cev[174].cevr";
connectAttr "Maugli_FKHead_M_Man_rotateZ.a" "clipLibrary1.cel[0].cev[175].cevr";
connectAttr "Maugli_FKHead_M_Man_rotateY.a" "clipLibrary1.cel[0].cev[176].cevr";
connectAttr "Maugli_FKHead_M_Man_rotateX.a" "clipLibrary1.cel[0].cev[177].cevr";
connectAttr "Maugli_FKScapula_R_Man_rotateZ.a" "clipLibrary1.cel[0].cev[178].cevr"
		;
connectAttr "Maugli_FKScapula_R_Man_rotateY.a" "clipLibrary1.cel[0].cev[179].cevr"
		;
connectAttr "Maugli_FKScapula_R_Man_rotateX.a" "clipLibrary1.cel[0].cev[180].cevr"
		;
connectAttr "Maugli_FKScapula_R_Man_translateZ.a" "clipLibrary1.cel[0].cev[181].cevr"
		;
connectAttr "Maugli_FKScapula_R_Man_translateY.a" "clipLibrary1.cel[0].cev[182].cevr"
		;
connectAttr "Maugli_FKScapula_R_Man_translateX.a" "clipLibrary1.cel[0].cev[183].cevr"
		;
connectAttr "Maugli_FKMiddleFinger1_R_Man_rotateZ.a" "clipLibrary1.cel[0].cev[191].cevr"
		;
connectAttr "Maugli_FKMiddleFinger2_R_Man_rotateZ.a" "clipLibrary1.cel[0].cev[192].cevr"
		;
connectAttr "Maugli_FKMiddleFinger3_R_Man_rotateZ.a" "clipLibrary1.cel[0].cev[193].cevr"
		;
connectAttr "Maugli_FKThumbFinger1_R_Man_rotateZ.a" "clipLibrary1.cel[0].cev[194].cevr"
		;
connectAttr "Maugli_FKThumbFinger1_R_Man_rotateY.a" "clipLibrary1.cel[0].cev[195].cevr"
		;
connectAttr "Maugli_FKThumbFinger1_R_Man_rotateX.a" "clipLibrary1.cel[0].cev[196].cevr"
		;
connectAttr "Maugli_FKThumbFinger2_R_Man_rotateY.a" "clipLibrary1.cel[0].cev[197].cevr"
		;
connectAttr "Maugli_Main_Man_visibility.a" "clipLibrary1.cel[0].cev[198].cevr";
connectAttr "Maugli_Center_M_CenterBtwFeet.a" "clipLibrary1.cel[0].cev[199].cevr"
		;
connectAttr "Maugli_Center_M_rotateZ.a" "clipLibrary1.cel[0].cev[200].cevr";
connectAttr "Maugli_Center_M_rotateY.a" "clipLibrary1.cel[0].cev[201].cevr";
connectAttr "Maugli_Center_M_rotateX.a" "clipLibrary1.cel[0].cev[202].cevr";
connectAttr "Maugli_Center_M_translateZ.a" "clipLibrary1.cel[0].cev[203].cevr";
connectAttr "Maugli_Center_M_translateY.a" "clipLibrary1.cel[0].cev[204].cevr";
connectAttr "Maugli_Center_M_translateX.a" "clipLibrary1.cel[0].cev[205].cevr";
connectAttr "Maugli_IKLegBackBall_L_rotateX.a" "clipLibrary1.cel[0].cev[206].cevr"
		;
connectAttr "Maugli_IKLegBackHeel_L_rotateZ.a" "clipLibrary1.cel[0].cev[207].cevr"
		;
connectAttr "Maugli_IKLegBackHeel_L_rotateY.a" "clipLibrary1.cel[0].cev[208].cevr"
		;
connectAttr "Maugli_IKLegBackHeel_L_rotateX.a" "clipLibrary1.cel[0].cev[209].cevr"
		;
connectAttr "Maugli_FKIKLegBack_L_IKVis.a" "clipLibrary1.cel[0].cev[210].cevr";
connectAttr "Maugli_FKIKLegBack_L_FKVis.a" "clipLibrary1.cel[0].cev[211].cevr";
connectAttr "Maugli_FKIKLegBack_L_FKIKBlend.a" "clipLibrary1.cel[0].cev[212].cevr"
		;
connectAttr "Maugli_PoleLegBack_L_follow.a" "clipLibrary1.cel[0].cev[213].cevr";
connectAttr "Maugli_PoleLegBack_L_translateZ.a" "clipLibrary1.cel[0].cev[214].cevr"
		;
connectAttr "Maugli_PoleLegBack_L_translateY.a" "clipLibrary1.cel[0].cev[215].cevr"
		;
connectAttr "Maugli_PoleLegBack_L_translateX.a" "clipLibrary1.cel[0].cev[216].cevr"
		;
connectAttr "Maugli_IKLegBack_L_Lenght2.a" "clipLibrary1.cel[0].cev[217].cevr";
connectAttr "Maugli_IKLegBack_L_Lenght1.a" "clipLibrary1.cel[0].cev[218].cevr";
connectAttr "Maugli_IKLegBack_L_antiPop.a" "clipLibrary1.cel[0].cev[219].cevr";
connectAttr "Maugli_IKLegBack_L_stretchy.a" "clipLibrary1.cel[0].cev[220].cevr";
connectAttr "Maugli_IKLegBack_L_legAim.a" "clipLibrary1.cel[0].cev[221].cevr";
connectAttr "Maugli_IKLegBack_L_rollAngle.a" "clipLibrary1.cel[0].cev[222].cevr"
		;
connectAttr "Maugli_IKLegBack_L_roll.a" "clipLibrary1.cel[0].cev[223].cevr";
connectAttr "Maugli_IKLegBack_L_swivel.a" "clipLibrary1.cel[0].cev[224].cevr";
connectAttr "Maugli_IKLegBack_L_rotateZ.a" "clipLibrary1.cel[0].cev[225].cevr";
connectAttr "Maugli_IKLegBack_L_rotateY.a" "clipLibrary1.cel[0].cev[226].cevr";
connectAttr "Maugli_IKLegBack_L_rotateX.a" "clipLibrary1.cel[0].cev[227].cevr";
connectAttr "Maugli_IKLegBack_L_translateZ.a" "clipLibrary1.cel[0].cev[228].cevr"
		;
connectAttr "Maugli_IKLegBack_L_translateY.a" "clipLibrary1.cel[0].cev[229].cevr"
		;
connectAttr "Maugli_IKLegBack_L_translateX.a" "clipLibrary1.cel[0].cev[230].cevr"
		;
connectAttr "Maugli_BendNeck_M_translateZ.a" "clipLibrary1.cel[0].cev[231].cevr"
		;
connectAttr "Maugli_BendNeck_M_translateY.a" "clipLibrary1.cel[0].cev[232].cevr"
		;
connectAttr "Maugli_BendNeck_M_translateX.a" "clipLibrary1.cel[0].cev[233].cevr"
		;
connectAttr "Maugli_FKIKSpine_M_IKVis.a" "clipLibrary1.cel[0].cev[234].cevr";
connectAttr "Maugli_FKIKSpine_M_FKVis.a" "clipLibrary1.cel[0].cev[235].cevr";
connectAttr "Maugli_FKIKSpine_M_FKIKBlend.a" "clipLibrary1.cel[0].cev[236].cevr"
		;
connectAttr "Maugli_IKLegBackBall_R_rotateX.a" "clipLibrary1.cel[0].cev[256].cevr"
		;
connectAttr "Maugli_IKLegBackHeel_R_rotateZ.a" "clipLibrary1.cel[0].cev[257].cevr"
		;
connectAttr "Maugli_IKLegBackHeel_R_rotateY.a" "clipLibrary1.cel[0].cev[258].cevr"
		;
connectAttr "Maugli_IKLegBackHeel_R_rotateX.a" "clipLibrary1.cel[0].cev[259].cevr"
		;
connectAttr "Maugli_FKIKLegBack_R_IKVis.a" "clipLibrary1.cel[0].cev[260].cevr";
connectAttr "Maugli_FKIKLegBack_R_FKVis.a" "clipLibrary1.cel[0].cev[261].cevr";
connectAttr "Maugli_FKIKLegBack_R_FKIKBlend.a" "clipLibrary1.cel[0].cev[262].cevr"
		;
connectAttr "Maugli_PoleLegBack_R_follow.a" "clipLibrary1.cel[0].cev[263].cevr";
connectAttr "Maugli_PoleLegBack_R_translateZ.a" "clipLibrary1.cel[0].cev[264].cevr"
		;
connectAttr "Maugli_PoleLegBack_R_translateY.a" "clipLibrary1.cel[0].cev[265].cevr"
		;
connectAttr "Maugli_PoleLegBack_R_translateX.a" "clipLibrary1.cel[0].cev[266].cevr"
		;
connectAttr "Maugli_IKLegBack_R_Lenght2.a" "clipLibrary1.cel[0].cev[267].cevr";
connectAttr "Maugli_IKLegBack_R_Lenght1.a" "clipLibrary1.cel[0].cev[268].cevr";
connectAttr "Maugli_IKLegBack_R_antiPop.a" "clipLibrary1.cel[0].cev[269].cevr";
connectAttr "Maugli_IKLegBack_R_stretchy.a" "clipLibrary1.cel[0].cev[270].cevr";
connectAttr "Maugli_IKLegBack_R_legAim.a" "clipLibrary1.cel[0].cev[271].cevr";
connectAttr "Maugli_IKLegBack_R_rollAngle.a" "clipLibrary1.cel[0].cev[272].cevr"
		;
connectAttr "Maugli_IKLegBack_R_roll.a" "clipLibrary1.cel[0].cev[273].cevr";
connectAttr "Maugli_IKLegBack_R_swivel.a" "clipLibrary1.cel[0].cev[274].cevr";
connectAttr "Maugli_IKLegBack_R_rotateZ.a" "clipLibrary1.cel[0].cev[275].cevr";
connectAttr "Maugli_IKLegBack_R_rotateY.a" "clipLibrary1.cel[0].cev[276].cevr";
connectAttr "Maugli_IKLegBack_R_rotateX.a" "clipLibrary1.cel[0].cev[277].cevr";
connectAttr "Maugli_IKLegBack_R_translateZ.a" "clipLibrary1.cel[0].cev[278].cevr"
		;
connectAttr "Maugli_IKLegBack_R_translateY.a" "clipLibrary1.cel[0].cev[279].cevr"
		;
connectAttr "Maugli_IKLegBack_R_translateX.a" "clipLibrary1.cel[0].cev[280].cevr"
		;
connectAttr "Maugli_FKIKSplineTail_M_IKVis.a" "clipLibrary1.cel[0].cev[281].cevr"
		;
connectAttr "Maugli_FKIKSplineTail_M_FKVis.a" "clipLibrary1.cel[0].cev[282].cevr"
		;
connectAttr "Maugli_FKIKSplineTail_M_FKIKBlend.a" "clipLibrary1.cel[0].cev[283].cevr"
		;
connectAttr "Maugli_WagCurveSplineTail_M_increment.a" "clipLibrary1.cel[0].cev[284].cevr"
		;
connectAttr "Maugli_WagCurveSplineTail_M_multiply.a" "clipLibrary1.cel[0].cev[285].cevr"
		;
connectAttr "Maugli_WagCurveSplineTail_M_timeOffset.a" "clipLibrary1.cel[0].cev[286].cevr"
		;
connectAttr "Maugli_WagCurveSplineTail_M_enable.a" "clipLibrary1.cel[0].cev[287].cevr"
		;
connectAttr "Maugli_WagCurveSplineTail_M_rotateZ.a" "clipLibrary1.cel[0].cev[288].cevr"
		;
connectAttr "Maugli_WagCurveSplineTail_M_rotateY.a" "clipLibrary1.cel[0].cev[289].cevr"
		;
connectAttr "Maugli_WagCurveSplineTail_M_rotateX.a" "clipLibrary1.cel[0].cev[290].cevr"
		;
connectAttr "Maugli_IKSplineTail2_M_stretchy.a" "clipLibrary1.cel[0].cev[291].cevr"
		;
connectAttr "Maugli_IKSplineTail2_M_twist.a" "clipLibrary1.cel[0].cev[292].cevr"
		;
connectAttr "Maugli_IKSplineTail2_M_follow.a" "clipLibrary1.cel[0].cev[293].cevr"
		;
connectAttr "Maugli_IKSplineTail2_M_translateZ.a" "clipLibrary1.cel[0].cev[294].cevr"
		;
connectAttr "Maugli_IKSplineTail2_M_translateY.a" "clipLibrary1.cel[0].cev[295].cevr"
		;
connectAttr "Maugli_IKSplineTail2_M_translateX.a" "clipLibrary1.cel[0].cev[296].cevr"
		;
connectAttr "Maugli_IKSplineTail1_M_follow.a" "clipLibrary1.cel[0].cev[297].cevr"
		;
connectAttr "Maugli_IKSplineTail1_M_translateZ.a" "clipLibrary1.cel[0].cev[298].cevr"
		;
connectAttr "Maugli_IKSplineTail1_M_translateY.a" "clipLibrary1.cel[0].cev[299].cevr"
		;
connectAttr "Maugli_IKSplineTail1_M_translateX.a" "clipLibrary1.cel[0].cev[300].cevr"
		;
connectAttr "Maugli_HipSwingerRoot_M_rotateZ.a" "clipLibrary1.cel[0].cev[301].cevr"
		;
connectAttr "Maugli_HipSwingerRoot_M_rotateY.a" "clipLibrary1.cel[0].cev[302].cevr"
		;
connectAttr "Maugli_HipSwingerRoot_M_rotateX.a" "clipLibrary1.cel[0].cev[303].cevr"
		;
connectAttr "Maugli_FKRump_L_rotateZ.a" "clipLibrary1.cel[0].cev[304].cevr";
connectAttr "Maugli_FKRump_L_rotateY.a" "clipLibrary1.cel[0].cev[305].cevr";
connectAttr "Maugli_FKRump_L_rotateX.a" "clipLibrary1.cel[0].cev[306].cevr";
connectAttr "Maugli_FKRump_L_translateZ.a" "clipLibrary1.cel[0].cev[307].cevr";
connectAttr "Maugli_FKRump_L_translateY.a" "clipLibrary1.cel[0].cev[308].cevr";
connectAttr "Maugli_FKRump_L_translateX.a" "clipLibrary1.cel[0].cev[309].cevr";
connectAttr "Maugli_FKRump_R_rotateZ.a" "clipLibrary1.cel[0].cev[319].cevr";
connectAttr "Maugli_FKRump_R_rotateY.a" "clipLibrary1.cel[0].cev[320].cevr";
connectAttr "Maugli_FKRump_R_rotateX.a" "clipLibrary1.cel[0].cev[321].cevr";
connectAttr "Maugli_FKRump_R_translateZ.a" "clipLibrary1.cel[0].cev[322].cevr";
connectAttr "Maugli_FKRump_R_translateY.a" "clipLibrary1.cel[0].cev[323].cevr";
connectAttr "Maugli_FKRump_R_translateX.a" "clipLibrary1.cel[0].cev[324].cevr";
connectAttr "Maugli_FKBackA_M_rotateZ.a" "clipLibrary1.cel[0].cev[346].cevr";
connectAttr "Maugli_FKBackA_M_rotateY.a" "clipLibrary1.cel[0].cev[347].cevr";
connectAttr "Maugli_FKBackA_M_rotateX.a" "clipLibrary1.cel[0].cev[348].cevr";
connectAttr "Maugli_FKBackB_M_rotateZ.a" "clipLibrary1.cel[0].cev[349].cevr";
connectAttr "Maugli_FKBackB_M_rotateY.a" "clipLibrary1.cel[0].cev[350].cevr";
connectAttr "Maugli_FKBackB_M_rotateX.a" "clipLibrary1.cel[0].cev[351].cevr";
connectAttr "Maugli_FKChest_M_rotateZ.a" "clipLibrary1.cel[0].cev[352].cevr";
connectAttr "Maugli_FKChest_M_rotateY.a" "clipLibrary1.cel[0].cev[353].cevr";
connectAttr "Maugli_FKChest_M_rotateX.a" "clipLibrary1.cel[0].cev[354].cevr";
connectAttr "Maugli_FKNeck_M_rotateZ.a" "clipLibrary1.cel[0].cev[355].cevr";
connectAttr "Maugli_FKNeck_M_rotateY.a" "clipLibrary1.cel[0].cev[356].cevr";
connectAttr "Maugli_FKNeck_M_rotateX.a" "clipLibrary1.cel[0].cev[357].cevr";
connectAttr "Maugli_FKHead_M_Global.a" "clipLibrary1.cel[0].cev[358].cevr";
connectAttr "Maugli_FKHead_M_rotateZ.a" "clipLibrary1.cel[0].cev[359].cevr";
connectAttr "Maugli_FKHead_M_rotateY.a" "clipLibrary1.cel[0].cev[360].cevr";
connectAttr "Maugli_FKHead_M_rotateX.a" "clipLibrary1.cel[0].cev[361].cevr";
connectAttr "Maugli_Main_scaleZ.a" "clipLibrary1.cel[0].cev[362].cevr";
connectAttr "Maugli_Main_scaleY.a" "clipLibrary1.cel[0].cev[363].cevr";
connectAttr "Maugli_Main_scaleX.a" "clipLibrary1.cel[0].cev[364].cevr";
connectAttr "Maugli_Main_rotateZ.a" "clipLibrary1.cel[0].cev[365].cevr";
connectAttr "Maugli_Main_rotateY.a" "clipLibrary1.cel[0].cev[366].cevr";
connectAttr "Maugli_Main_rotateX.a" "clipLibrary1.cel[0].cev[367].cevr";
connectAttr "Maugli_Main_translateZ.a" "clipLibrary1.cel[0].cev[368].cevr";
connectAttr "Maugli_Main_translateY.a" "clipLibrary1.cel[0].cev[369].cevr";
connectAttr "Maugli_Main_translateX.a" "clipLibrary1.cel[0].cev[370].cevr";
connectAttr "Maugli_Main_visibility.a" "clipLibrary1.cel[0].cev[371].cevr";
connectAttr "Maugli_kolchan_rotateZ.a" "clipLibrary1.cel[0].cev[372].cevr";
connectAttr "Maugli_kolchan_rotateY.a" "clipLibrary1.cel[0].cev[373].cevr";
connectAttr "Maugli_kolchan_rotateX.a" "clipLibrary1.cel[0].cev[374].cevr";
connectAttr "Maugli_yashik_rotateZ.a" "clipLibrary1.cel[0].cev[375].cevr";
connectAttr "Maugli_yashik_rotateY.a" "clipLibrary1.cel[0].cev[376].cevr";
connectAttr "Maugli_yashik_rotateX.a" "clipLibrary1.cel[0].cev[377].cevr";
connectAttr "Maugli_yashik_translateZ.a" "clipLibrary1.cel[0].cev[378].cevr";
connectAttr "Maugli_yashik_translateY.a" "clipLibrary1.cel[0].cev[379].cevr";
connectAttr "Maugli_yashik_translateX.a" "clipLibrary1.cel[0].cev[380].cevr";
connectAttr "Maugli_l_ear_control_rotateZ.a" "clipLibrary1.cel[0].cev[381].cevr"
		;
connectAttr "Maugli_l_ear_control_rotateY.a" "clipLibrary1.cel[0].cev[382].cevr"
		;
connectAttr "Maugli_l_ear_control_rotateX.a" "clipLibrary1.cel[0].cev[383].cevr"
		;
connectAttr "Maugli_r_ear_control1_rotateZ.a" "clipLibrary1.cel[0].cev[384].cevr"
		;
connectAttr "Maugli_r_ear_control1_rotateY.a" "clipLibrary1.cel[0].cev[385].cevr"
		;
connectAttr "Maugli_r_ear_control1_rotateX.a" "clipLibrary1.cel[0].cev[386].cevr"
		;
connectAttr "Maugli_jaw_C_rotateZ.a" "clipLibrary1.cel[0].cev[387].cevr";
connectAttr "Maugli_spear_control_rotateZ.a" "clipLibrary1.cel[0].cev[388].cevr"
		;
connectAttr "Maugli_spear_control_rotateY.a" "clipLibrary1.cel[0].cev[389].cevr"
		;
connectAttr "Maugli_spear_control_rotateX.a" "clipLibrary1.cel[0].cev[390].cevr"
		;
connectAttr "Maugli_spear_control_translateZ.a" "clipLibrary1.cel[0].cev[391].cevr"
		;
connectAttr "Maugli_spear_control_translateY.a" "clipLibrary1.cel[0].cev[392].cevr"
		;
connectAttr "Maugli_spear_control_translateX.a" "clipLibrary1.cel[0].cev[393].cevr"
		;
connectAttr "Maugli_spear_control_World_Hands.a" "clipLibrary1.cel[0].cev[394].cevr"
		;
connectAttr "Maugli_IKLegFrontBall_L_rotateX.a" "clipLibrary1.cel[0].cev[395].cevr"
		;
connectAttr "Maugli_IKLegFrontBall_R_rotateX.a" "clipLibrary1.cel[0].cev[396].cevr"
		;
connectAttr "Maugli_IKLegFrontHeel_L_rotateZ.a" "clipLibrary1.cel[0].cev[397].cevr"
		;
connectAttr "Maugli_IKLegFrontHeel_L_rotateY.a" "clipLibrary1.cel[0].cev[398].cevr"
		;
connectAttr "Maugli_IKLegFrontHeel_L_rotateX.a" "clipLibrary1.cel[0].cev[399].cevr"
		;
connectAttr "Maugli_IKLegFrontHeel_R_rotateZ.a" "clipLibrary1.cel[0].cev[400].cevr"
		;
connectAttr "Maugli_IKLegFrontHeel_R_rotateY.a" "clipLibrary1.cel[0].cev[401].cevr"
		;
connectAttr "Maugli_IKLegFrontHeel_R_rotateX.a" "clipLibrary1.cel[0].cev[402].cevr"
		;
connectAttr "Maugli_IKLegFront_R_Lenght2.a" "clipLibrary1.cel[0].cev[403].cevr";
connectAttr "Maugli_IKLegFront_R_Lenght1.a" "clipLibrary1.cel[0].cev[404].cevr";
connectAttr "Maugli_IKLegFront_R_antiPop.a" "clipLibrary1.cel[0].cev[405].cevr";
connectAttr "Maugli_IKLegFront_R_stretchy.a" "clipLibrary1.cel[0].cev[406].cevr"
		;
connectAttr "Maugli_IKLegFront_R_legAim.a" "clipLibrary1.cel[0].cev[407].cevr";
connectAttr "Maugli_IKLegFront_R_rollAngle.a" "clipLibrary1.cel[0].cev[408].cevr"
		;
connectAttr "Maugli_IKLegFront_R_roll.a" "clipLibrary1.cel[0].cev[409].cevr";
connectAttr "Maugli_IKLegFront_R_swivel.a" "clipLibrary1.cel[0].cev[410].cevr";
connectAttr "Maugli_IKLegFront_R_rotateZ.a" "clipLibrary1.cel[0].cev[411].cevr";
connectAttr "Maugli_IKLegFront_R_rotateY.a" "clipLibrary1.cel[0].cev[412].cevr";
connectAttr "Maugli_IKLegFront_R_rotateX.a" "clipLibrary1.cel[0].cev[413].cevr";
connectAttr "Maugli_IKLegFront_R_translateZ.a" "clipLibrary1.cel[0].cev[414].cevr"
		;
connectAttr "Maugli_IKLegFront_R_translateY.a" "clipLibrary1.cel[0].cev[415].cevr"
		;
connectAttr "Maugli_IKLegFront_R_translateX.a" "clipLibrary1.cel[0].cev[416].cevr"
		;
connectAttr "Maugli_IKLegFront_L_Lenght2.a" "clipLibrary1.cel[0].cev[417].cevr";
connectAttr "Maugli_IKLegFront_L_Lenght1.a" "clipLibrary1.cel[0].cev[418].cevr";
connectAttr "Maugli_IKLegFront_L_antiPop.a" "clipLibrary1.cel[0].cev[419].cevr";
connectAttr "Maugli_IKLegFront_L_stretchy.a" "clipLibrary1.cel[0].cev[420].cevr"
		;
connectAttr "Maugli_IKLegFront_L_legAim.a" "clipLibrary1.cel[0].cev[421].cevr";
connectAttr "Maugli_IKLegFront_L_rollAngle.a" "clipLibrary1.cel[0].cev[422].cevr"
		;
connectAttr "Maugli_IKLegFront_L_roll.a" "clipLibrary1.cel[0].cev[423].cevr";
connectAttr "Maugli_IKLegFront_L_swivel.a" "clipLibrary1.cel[0].cev[424].cevr";
connectAttr "Maugli_IKLegFront_L_rotateZ.a" "clipLibrary1.cel[0].cev[425].cevr";
connectAttr "Maugli_IKLegFront_L_rotateY.a" "clipLibrary1.cel[0].cev[426].cevr";
connectAttr "Maugli_IKLegFront_L_rotateX.a" "clipLibrary1.cel[0].cev[427].cevr";
connectAttr "Maugli_IKLegFront_L_translateZ.a" "clipLibrary1.cel[0].cev[428].cevr"
		;
connectAttr "Maugli_IKLegFront_L_translateY.a" "clipLibrary1.cel[0].cev[429].cevr"
		;
connectAttr "Maugli_IKLegFront_L_translateX.a" "clipLibrary1.cel[0].cev[430].cevr"
		;
connectAttr "Maugli_FKIKLegFront_L_IKVis.a" "clipLibrary1.cel[0].cev[431].cevr";
connectAttr "Maugli_FKIKLegFront_L_FKVis.a" "clipLibrary1.cel[0].cev[432].cevr";
connectAttr "Maugli_FKIKLegFront_L_FKIKBlend.a" "clipLibrary1.cel[0].cev[433].cevr"
		;
connectAttr "Maugli_FKIKLegFront_R_IKVis.a" "clipLibrary1.cel[0].cev[434].cevr";
connectAttr "Maugli_FKIKLegFront_R_FKVis.a" "clipLibrary1.cel[0].cev[435].cevr";
connectAttr "Maugli_FKIKLegFront_R_FKIKBlend.a" "clipLibrary1.cel[0].cev[436].cevr"
		;
connectAttr "Maugli_FKScapula_L_rotateZ.a" "clipLibrary1.cel[0].cev[437].cevr";
connectAttr "Maugli_FKScapula_L_rotateY.a" "clipLibrary1.cel[0].cev[438].cevr";
connectAttr "Maugli_FKScapula_L_rotateX.a" "clipLibrary1.cel[0].cev[439].cevr";
connectAttr "Maugli_FKScapula_L_translateZ.a" "clipLibrary1.cel[0].cev[440].cevr"
		;
connectAttr "Maugli_FKScapula_L_translateY.a" "clipLibrary1.cel[0].cev[441].cevr"
		;
connectAttr "Maugli_FKScapula_L_translateX.a" "clipLibrary1.cel[0].cev[442].cevr"
		;
connectAttr "Maugli_FKScapula_R_rotateZ.a" "clipLibrary1.cel[0].cev[443].cevr";
connectAttr "Maugli_FKScapula_R_rotateY.a" "clipLibrary1.cel[0].cev[444].cevr";
connectAttr "Maugli_FKScapula_R_rotateX.a" "clipLibrary1.cel[0].cev[445].cevr";
connectAttr "Maugli_FKScapula_R_translateZ.a" "clipLibrary1.cel[0].cev[446].cevr"
		;
connectAttr "Maugli_FKScapula_R_translateY.a" "clipLibrary1.cel[0].cev[447].cevr"
		;
connectAttr "Maugli_FKScapula_R_translateX.a" "clipLibrary1.cel[0].cev[448].cevr"
		;
connectAttr "Maugli_PoleLegFront_L_follow.a" "clipLibrary1.cel[0].cev[459].cevr"
		;
connectAttr "Maugli_PoleLegFront_L_translateZ.a" "clipLibrary1.cel[0].cev[460].cevr"
		;
connectAttr "Maugli_PoleLegFront_L_translateY.a" "clipLibrary1.cel[0].cev[461].cevr"
		;
connectAttr "Maugli_PoleLegFront_L_translateX.a" "clipLibrary1.cel[0].cev[462].cevr"
		;
connectAttr "Maugli_PoleLegFront_R_follow.a" "clipLibrary1.cel[0].cev[463].cevr"
		;
connectAttr "Maugli_PoleLegFront_R_translateZ.a" "clipLibrary1.cel[0].cev[464].cevr"
		;
connectAttr "Maugli_PoleLegFront_R_translateY.a" "clipLibrary1.cel[0].cev[465].cevr"
		;
connectAttr "Maugli_PoleLegFront_R_translateX.a" "clipLibrary1.cel[0].cev[466].cevr"
		;
connectAttr "curve1_translateX.a" "clipLibrary1.cel[0].cev[467].cevr";
connectAttr "curve1_translateY.a" "clipLibrary1.cel[0].cev[468].cevr";
connectAttr "curve1_translateZ.a" "clipLibrary1.cel[0].cev[469].cevr";
connectAttr "curve1_visibility.a" "clipLibrary1.cel[0].cev[470].cevr";
connectAttr "curve1_rotateX.a" "clipLibrary1.cel[0].cev[471].cevr";
connectAttr "curve1_rotateY.a" "clipLibrary1.cel[0].cev[472].cevr";
connectAttr "curve1_rotateZ.a" "clipLibrary1.cel[0].cev[473].cevr";
connectAttr "curve1_scaleX.a" "clipLibrary1.cel[0].cev[474].cevr";
connectAttr "curve1_scaleY.a" "clipLibrary1.cel[0].cev[475].cevr";
connectAttr "curve1_scaleZ.a" "clipLibrary1.cel[0].cev[476].cevr";
connectAttr "IKLegBackBall_R_rotateY.a" "clipLibrary1.cel[0].cev[477].cevr";
connectAttr "IKLegBackBall_R_rotateZ.a" "clipLibrary1.cel[0].cev[478].cevr";
connectAttr "IKLegBackBall_L_rotateY.a" "clipLibrary1.cel[0].cev[479].cevr";
connectAttr "IKLegBackBall_L_rotateZ.a" "clipLibrary1.cel[0].cev[480].cevr";
connectAttr "IKLegFrontBall_R_rotateY.a" "clipLibrary1.cel[0].cev[481].cevr";
connectAttr "IKLegFrontBall_R_rotateZ.a" "clipLibrary1.cel[0].cev[482].cevr";
connectAttr "IKLegFrontBall_L_rotateY.a" "clipLibrary1.cel[0].cev[483].cevr";
connectAttr "IKLegFrontBall_L_rotateZ.a" "clipLibrary1.cel[0].cev[484].cevr";
connectAttr "IKXSplineTailCurve_M_translateX.a" "clipLibrary1.cel[0].cev[485].cevr"
		;
connectAttr "IKXSplineTailCurve_M_translateY.a" "clipLibrary1.cel[0].cev[486].cevr"
		;
connectAttr "IKXSplineTailCurve_M_translateZ.a" "clipLibrary1.cel[0].cev[487].cevr"
		;
connectAttr "IKXSplineTailCurve_M_rotateX.a" "clipLibrary1.cel[0].cev[488].cevr"
		;
connectAttr "IKXSplineTailCurve_M_rotateY.a" "clipLibrary1.cel[0].cev[489].cevr"
		;
connectAttr "IKXSplineTailCurve_M_rotateZ.a" "clipLibrary1.cel[0].cev[490].cevr"
		;
connectAttr "IKXSplineTailCurve_M_scaleX.a" "clipLibrary1.cel[0].cev[491].cevr";
connectAttr "IKXSplineTailCurve_M_scaleY.a" "clipLibrary1.cel[0].cev[492].cevr";
connectAttr "IKXSplineTailCurve_M_scaleZ.a" "clipLibrary1.cel[0].cev[493].cevr";
connectAttr "IKLegBall_R_Man_rotateY.a" "clipLibrary1.cel[0].cev[494].cevr";
connectAttr "IKLegBall_R_Man_rotateZ.a" "clipLibrary1.cel[0].cev[495].cevr";
connectAttr "IKLegBall_L_Man_rotateY.a" "clipLibrary1.cel[0].cev[496].cevr";
connectAttr "IKLegBall_L_Man_rotateZ.a" "clipLibrary1.cel[0].cev[497].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker3.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker3.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker3.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker3.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker3.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker3.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker3.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker3.slnk[1].solk";
connectAttr "lightLinker3.msg" ":lightList1.ln" -na;
// End of ability01.ma
