//Maya ASCII 2008 scene
//Name: attack2.ma
//Last modified: Mon, Feb 01, 2010 11:40:02 AM
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
createNode animClip -n "attack02Source";
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
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 38 0 45 
		0;
createNode animCurveTA -n "Maugli_Center_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 6 0 15 0 20 1.9530908742366426 
		27 1.9530908742366395 33 19.610067678399194 38 0 45 0;
createNode animCurveTA -n "Maugli_Center_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 6 0 15 0 20 2.2740115297292212 
		27 2.2740115297292376 33 15.446343408585509 38 0 45 0;
createNode animCurveTA -n "Maugli_Center_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 4.0494833724385515 3 -7.4518449057176133 
		6 64.475550718298535 15 64.475550718298535 20 22.692081423913685 27 0.54236304266603652 
		33 8.5860940041844316 38 4.0494833724385515 45 4.0494833724385515;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "Maugli_Center_M_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0.2819295344432855 6 0.41030735835121568 
		15 0.24587536015576261 20 0.10080051734101392 27 0.10617285855172232 33 0.10617285855172232 
		38 0 45 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "Maugli_Center_M_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 -0.061220928813071979 6 -0.6144947502435758 
		15 -0.9258531872274689 20 -0.26291658059266099 27 -0.1171228229562785 33 -0.1171228229562785 
		38 0 45 0;
createNode animCurveTL -n "Maugli_Center_M_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0.0058191266342244221 6 0.076137494649293924 
		15 0.050331327263776107 20 0.0010173026061773647 27 -0.0012360162963203599 33 -0.0012360162963203599 
		38 0 45 0;
	setAttr -s 9 ".kit[1:8]"  1 10 9 10 10 10 10 10;
	setAttr -s 9 ".kot[1:8]"  1 10 9 10 10 10 10 10;
	setAttr -s 9 ".kix[1:8]"  0.99197781085968018 1 0.98729056119918823 
		1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  0.1264120489358902 0 -0.15892596542835236 
		0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  0.99197781085968018 1 0.98729056119918823 
		1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  0.12641206383705139 0 -0.15892596542835236 
		0 0 0 0 0;
createNode animCurveTU -n "Maugli_Fingers_L_Man_MiddleFingerCurl";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBall_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegToe_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegToe_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 3.1805546814635168e-015 3 3.1805546814635168e-015 
		6 3.1805546814635168e-015 15 0 20 3.1805546814635168e-015 27 3.1805546814635168e-015 
		33 3.1805546814635168e-015 45 3.1805546814635168e-015;
createNode animCurveTA -n "Maugli_IKLegToe_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTU -n "Maugli_FKIKLeg_L_Man_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLeg_L_Man_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLeg_L_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 15 10 20 10 27 10 33 10 
		45 10;
createNode animCurveTA -n "Maugli_IKLegHeel_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegHeel_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -3.1805546814635168e-015 3 -3.1805546814635168e-015 
		6 -3.1805546814635168e-015 15 0 20 -3.1805546814635168e-015 27 -3.1805546814635168e-015 
		33 -3.1805546814635168e-015 45 -3.1805546814635168e-015;
createNode animCurveTA -n "Maugli_IKLegHeel_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "Maugli_PoleLeg_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 -0.44422621777226079 6 -0.26421915143427599 
		15 -0.26421915143427599 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "Maugli_PoleLeg_L_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 -0.16988635459036244 6 -0.12678324657923667 
		15 -0.12678324657923667 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "Maugli_PoleLeg_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 -0.29691906480501024 6 -0.5596066207074476 
		15 -0.5596066207074476 20 0 27 0 33 0 45 0;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 25 3 25 6 25 15 25 20 25 27 25 33 25 
		45 25;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_toe";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_IKLeg_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -5.0105185448650458 3 -9.2384719061330163 
		6 5.4247658815711226 15 5.4247658815711226 20 -5.0105185448650458 27 -5.0105185448650458 
		33 -5.0105185448650458 45 -5.0105185448650458;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_IKLeg_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -6.3694432300697281 3 12.618972829240336 
		6 16.638616149585239 15 16.638616149585239 20 -6.3694432300697281 27 -6.3694432300697281 
		33 -6.3694432300697281 45 -6.3694432300697281;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_IKLeg_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 13.378201002477269 3 -19.58833553486766 
		6 1.8485173826171712 15 1.8485173826171712 20 13.378201002477269 27 13.378201002477269 
		33 13.378201002477269 45 13.378201002477269;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKLeg_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.069000150376690925 3 -0.14749565730907724 
		6 -0.062252178610444318 15 -0.062252178610444318 20 0.069000150376690925 27 0.069000150376690925 
		33 0.069000150376690925 45 0.069000150376690925;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKLeg_L_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.015303353529604964 3 -0.1119504166723669 
		6 -0.058555971978181742 15 -0.058555971978181742 20 -0.015303353529604964 27 -0.015303353529604964 
		33 -0.015303353529604964 45 -0.015303353529604964;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKLeg_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.16760982461393598 3 0.1126377035925093 
		6 0.14981256896186959 15 0.14981256896186959 20 0.16760982461393598 27 0.16760982461393598 
		33 0.16760982461393598 45 0.16760982461393598;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_FKIKArm_L_Man_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKArm_L_Man_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKArm_L_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 15 10 20 10 27 10 33 10 
		45 10;
createNode animCurveTU -n "Maugli_PoleArm_L_Man_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 10 3 10 6 10 15 10 20 10 27 10 33 10 
		38 10 45 10;
createNode animCurveTL -n "Maugli_PoleArm_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.39549705228612952 3 0.39333077133622713 
		4 0.11381446218760226 6 0.39333077133622713 15 0.39333077133622713 20 0.25589777844321598 
		27 0.25589777844321598 33 0.062619828050989548 38 0.39879197240025666 45 0.39549705228612952;
createNode animCurveTL -n "Maugli_PoleArm_L_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.86201805279910448 3 -0.59427898360876152 
		4 -0.43220908984885342 6 -0.59427898360876152 15 -0.59427898360876152 20 -0.86599331471835017 
		27 -0.86599331471835017 33 -1.3061885270102374 38 -0.70565317452179577 45 -0.86201805279910448;
createNode animCurveTL -n "Maugli_PoleArm_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.30818663726222251 3 -0.2957513979957605 
		4 -0.053398153472341524 6 -0.2957513979957605 15 -0.2957513979957605 20 -0.363381656387469 
		27 -0.363381656387469 33 -0.40878484243287028 38 -0.090622008845673285 45 -0.30818663726222251;
createNode animCurveTU -n "Maugli_IKArm_L_Man_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 38 1 45 
		1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "Maugli_IKArm_L_Man_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 38 1 45 
		1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "Maugli_IKArm_L_Man_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 38 0 45 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "Maugli_IKArm_L_Man_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 38 0 45 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "Maugli_IKArm_L_Man_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 38 0 45 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "Maugli_IKArm_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -97.78067605427789 3 -89.953004756025976 
		6 37.887792137715408 15 37.887792137715408 20 -32.997785062572305 27 -15.291503289355598 
		33 -15.291503289355598 38 -19.026554823111947 42 -50.04992858621403 45 -97.78067605427789;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 3;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 3;
createNode animCurveTA -n "Maugli_IKArm_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 10.92155845877172 3 27.100382890998091 
		6 -26.041762967966168 15 -26.041762967966168 20 16.727209463332787 27 28.571561125014306 
		33 28.571561125014306 38 47.39746750973422 42 6.7216268595981719 45 10.92155845877172;
	setAttr -s 10 ".kit[0:9]"  9 10 10 10 10 10 10 10 
		10 9;
	setAttr -s 10 ".kot[0:9]"  9 10 10 10 10 10 10 10 
		10 9;
createNode animCurveTA -n "Maugli_IKArm_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 14.178018067197163 3 -41.025329108858003 
		6 36.682008449560158 15 36.682008449560158 20 -16.715642668169473 27 5.0742879772345226 
		33 5.0742879772345226 38 14.201628002226798 42 -19.082166867108011 45 14.178018067197163;
	setAttr -s 10 ".kit[0:9]"  3 10 1 10 10 10 10 10 
		10 3;
	setAttr -s 10 ".kot[0:9]"  3 10 1 10 10 10 10 10 
		10 3;
	setAttr -s 10 ".kix[2:9]"  0.94002199172973633 1 0.5870131254196167 
		1 1 0.57976585626602173 0.99999845027923584 1;
	setAttr -s 10 ".kiy[2:9]"  0.34111404418945313 0 -0.80957740545272827 
		0 0 -0.81478315591812134 -0.0017660161247476935 0;
	setAttr -s 10 ".kox[2:9]"  0.94002193212509155 1 0.5870131254196167 
		1 1 0.57976585626602173 0.99999845027923584 1;
	setAttr -s 10 ".koy[2:9]"  0.34111404418945313 0 -0.80957740545272827 
		0 0 -0.81478315591812134 -0.0017660161247476935 0;
createNode animCurveTL -n "Maugli_IKArm_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -0.79120002893813179 3 0.40779127304079993 
		4 0.36906941690815109 5 0.24165086858342583 6 0.30764614273352592 15 0.16017278625905276 
		20 -0.54243121522071158 27 -0.51404871260343177 33 -0.51404871260343177 38 -0.80692850123605342 
		42 -0.7709650275459401 45 -0.79120002893813179;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 10 10 10 
		10 10 9 10;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 10 10 10 
		10 10 9 10;
createNode animCurveTL -n "Maugli_IKArm_L_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -0.30360130511963851 3 -1.058741046231527 
		4 -1.0874067434606889 5 -1.0573697409331504 6 -1.3034096343535677 15 -1.4777453681420627 
		20 -0.53016037729835208 27 0.30042048019598117 33 0.30042048019598117 38 0.31795426793734316 
		42 -0.045545606131116259 45 -0.30360130511963851;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 10;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 10;
createNode animCurveTL -n "Maugli_IKArm_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -0.80061447835185851 3 -1.021535371985818 
		4 -0.27471457183363607 5 -0.028398441225472051 6 -0.18831804546474884 15 -0.32717411954456488 
		20 -0.58710998331013986 27 -1.0675458314983963 33 -1.0675458314983963 38 -0.70366302500771405 
		42 -0.73574341126760723 45 -0.80061447835185851;
	setAttr -s 12 ".kit[0:11]"  9 10 10 10 10 10 10 10 
		10 10 9 10;
	setAttr -s 12 ".kot[0:11]"  9 10 10 10 10 10 10 10 
		10 10 9 10;
createNode animCurveTU -n "Maugli_Fingers_R_Man_MiddleFingerCurl";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 5 0 6 -2 15 -2 20 -2 27 -2 33 -2 
		35 0 45 0;
createNode animCurveTU -n "Maugli_FKIKSpine_M_Man_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKSpine_M_Man_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKSpine_M_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBall_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegToe_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -7.0622500768802538e-031 3 -7.0622500768802538e-031 
		6 -7.0622500768802538e-031 15 0 20 -7.0622500768802538e-031 27 -7.0622500768802538e-031 
		33 -7.0622500768802538e-031 45 -7.0622500768802538e-031;
createNode animCurveTA -n "Maugli_IKLegToe_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 3.1805546814635168e-015 3 3.1805546814635168e-015 
		6 3.1805546814635168e-015 15 0 20 3.1805546814635168e-015 27 3.1805546814635168e-015 
		33 3.1805546814635168e-015 45 3.1805546814635168e-015;
createNode animCurveTA -n "Maugli_IKLegToe_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegHeel_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegHeel_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 3.1805546814635168e-015 3 3.1805546814635168e-015 
		6 3.1805546814635168e-015 15 0 20 3.1805546814635168e-015 27 3.1805546814635168e-015 
		33 3.1805546814635168e-015 45 3.1805546814635168e-015;
createNode animCurveTA -n "Maugli_IKLegHeel_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTU -n "Maugli_FKIKLeg_R_Man_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLeg_R_Man_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLeg_R_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 15 10 20 10 27 10 33 10 
		45 10;
createNode animCurveTL -n "Maugli_PoleLeg_R_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 -0.27164726300088682 6 -0.15249196793231395 
		15 -0.15249196793231395 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "Maugli_PoleLeg_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0.01129157767972162 6 -0.12587469984903266 
		15 -0.12587469984903266 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "Maugli_PoleLeg_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0.077595994337497004 6 0.25661518493412638 
		15 0.25661518493412638 20 0 27 0 33 0 45 0;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 25 3 25 6 25 15 25 20 25 27 25 33 25 
		45 25;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_toe";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_IKLeg_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 4.1314268552009148 6 -14.634738034075712 
		15 -14.634738034075712 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_IKLeg_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 -5.1535268089140827 6 -7.0703233001987646 
		15 -7.0703233001987646 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 9 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 9 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_IKLeg_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 -38.618352505967536 6 -5.9230371348681041 
		15 -5.9230371348681041 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKLeg_R_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 -0.11017594035094118 6 -0.099110615249111855 
		15 -0.099110615249111855 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKLeg_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 -0.027406726573689515 6 0.26348653954249912 
		15 0.26348653954249912 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKLeg_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0.013376264849425232 6 -0.086436096275389604 
		15 -0.086436096275389604 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_FKIKArm_R_Man_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKArm_R_Man_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKArm_R_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 15 10 20 10 27 10 33 10 
		45 10;
createNode animCurveTU -n "Maugli_PoleArm_R_Man_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 10 3 10 6 10 9 10 15 10 20 10 27 10 33 
		10 38 10 45 10;
createNode animCurveTL -n "Maugli_PoleArm_R_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0.70603635746209714 6 0.70603635746209714 
		9 0.1965355365829127 15 -0.10996172219438508 20 0.5785497971693192 27 0.59524271815004848 
		33 0.071119465440706311 38 -0.027961354693342457 45 0;
createNode animCurveTL -n "Maugli_PoleArm_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 -1.2585343343145192 6 -1.2585343343145192 
		9 -0.74535527958034609 15 -1.4039037596634998 20 -0.86205578063792943 27 -0.79196283487842067 
		33 -0.83837102295605526 38 -0.57905206078907812 45 0;
createNode animCurveTL -n "Maugli_PoleArm_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1.1102230246251565e-016 3 -0.049048241695864386 
		6 -0.049048241695864386 9 0.14731684204702655 15 0.50139924530257252 20 0.030201044854369162 
		27 -0.00022990183551480298 33 0.033135815306288834 38 0.076985139824331736 45 1.1102230246251565e-016;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -6.2725381128105917e-045 3 -6.2725381128105917e-045 
		6 -6.2725381128105917e-045 15 0 20 -6.2725381128105917e-045 27 -6.2725381128105917e-045 
		33 -6.2725381128105917e-045 45 -6.2725381128105917e-045;
createNode animCurveTU -n "Maugli_IKArm_R_Man_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
createNode animCurveTU -n "Maugli_IKArm_R_Man_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
createNode animCurveTU -n "Maugli_IKArm_R_Man_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTU -n "Maugli_IKArm_R_Man_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTU -n "Maugli_IKArm_R_Man_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKArm_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -12.754512848885321 3 19.196991125174446 
		5 3.7969075160989578 6 -15.155699509648016 9 -87.499097057378648 15 4.6268727267193563 
		20 -41.736421432968726 27 -10.998908395019075 33 87.381396782792095 35 26.0426000963799 
		38 -33.693586108089676 45 -192.7545128488853;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 3;
createNode animCurveTA -n "Maugli_IKArm_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -51.071041253431346 3 -61.63613767440394 
		5 -72.713345369725801 6 -79.796620885140456 9 -130.249097597233 15 -162.85703388074455 
		20 -103.58392430754292 27 -171.49024052282977 33 -248.66319210778641 35 -242.72128690602702 
		38 -188.48210953442722 45 -128.92895874656867;
	setAttr -s 12 ".kit[0:11]"  9 10 10 10 10 10 10 10 
		10 10 10 10;
	setAttr -s 12 ".kot[0:11]"  9 10 10 10 10 10 10 10 
		10 10 10 10;
createNode animCurveTA -n "Maugli_IKArm_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -30.429381170308442 3 -174.8097469311906 
		5 -148.68951376646518 6 -156.32917705284703 9 -145.19094768366639 15 -118.96460407690165 
		20 -146.62948696078828 27 -135.09546620072487 33 -207.82570081818508 35 -189.07616699098062 
		38 -205.88030535707574 45 -210.42938117030846;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 10;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 10;
createNode animCurveTL -n "Maugli_IKArm_R_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -0.50891155850440861 3 0.78406948626176443 
		4 0.73442259324665526 5 0.29294478934872814 6 -1.0147770782765519 9 -1.1354621601747059 
		15 -1.126388093348651 20 -0.20194330498198174 27 -0.51044923455832214 33 -0.98937625489942049 
		35 -0.62375527040149736 38 -0.10170933191764801 45 -0.50891155850440861;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[10:12]"  0.1619461327791214 0.94545936584472656 
		1;
	setAttr -s 13 ".kiy[10:12]"  0.98679965734481812 0.32574012875556946 
		0;
	setAttr -s 13 ".kox[10:12]"  0.16194610297679901 0.94545936584472656 
		1;
	setAttr -s 13 ".koy[10:12]"  0.98679959774017334 0.32574012875556946 
		0;
createNode animCurveTL -n "Maugli_IKArm_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -0.17073023409560481 3 1.0781542861432079 
		4 -0.20800653481898032 5 -1.9100648266050473 6 -2.4945667899353814 9 -2.6392459113786457 
		15 -2.4370015968012644 20 -1.7098123540477972 27 -0.47335478116002028 33 0.028748697001326939 
		35 -0.25624255306495325 38 -0.97395107604049347 45 -0.17073023409560481;
	setAttr -s 13 ".kit[4:12]"  1 10 1 10 10 10 10 10 
		10;
	setAttr -s 13 ".kot[4:12]"  1 10 1 10 10 10 10 10 
		10;
	setAttr -s 13 ".kix[4:12]"  0.93638253211975098 0.98208355903625488 
		0.82481002807617188 0.19960345327854156 0.24184904992580414 0.77547949552536011 0.16396822035312653 
		0.96863436698913574 0.27896478772163391;
	setAttr -s 13 ".kiy[4:12]"  -0.35098123550415039 0.18844608962535858 
		0.56540995836257935 0.97987675666809082 0.9703139066696167 0.63137280941009521 -0.98646557331085205 
		0.24849048256874084 0.96030133962631226;
	setAttr -s 13 ".kox[4:12]"  0.93638205528259277 0.98208355903625488 
		0.82481002807617188 0.19960345327854156 0.24184904992580414 0.77547949552536011 0.16396822035312653 
		0.96863436698913574 0.27896478772163391;
	setAttr -s 13 ".koy[4:12]"  -0.35098245739936829 0.18844608962535858 
		0.56540995836257935 0.97987675666809082 0.9703139066696167 0.63137280941009521 -0.98646557331085205 
		0.24849048256874084 0.96030133962631226;
createNode animCurveTL -n "Maugli_IKArm_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0.44722353666474202 3 1.0578316527692619 
		4 0.69645164683716354 5 0.70459498239336515 6 1.1563351763170369 9 1.430984780712045 
		15 1.6991032448651167 20 1.697782931045958 27 2.2793361463833333 33 2.2813588264589768 
		35 2.3486658546146479 38 1.5434502030399866 45 0.44722353666474202;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 10 10 10 10 
		10 10 10 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 10 10 10 10 
		10 10 10 10 3;
createNode animCurveTA -n "Maugli_FKScapula_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -7.1990267140314277 3 -11.344374324085589 
		6 -28.243097453153496 15 -28.243097453153496 20 -28.243097453153496 27 -28.243097453153496 
		33 -28.243097453153496 38 6.8421129968635936 45 -7.1990267140314277;
createNode animCurveTA -n "Maugli_FKScapula_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 9.9598426785175036 3 24.960878886093845 
		6 -8.1767819210082244 15 -8.1767819210082244 20 -8.1767819210082244 27 -8.1767819210082244 
		33 -8.1767819210082244 38 -38.662467189907211 45 9.9598426785175036;
createNode animCurveTA -n "Maugli_FKScapula_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -7.1981747374653153 3 -9.1627912541616521 
		6 3.4867734964514869 15 3.4867734964514869 20 3.4867734964514869 27 3.4867734964514869 
		33 3.4867734964514869 38 10.077068102662579 45 -7.1981747374653153;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTL -n "Maugli_FKScapula_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "Maugli_FKScapula_L_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "Maugli_FKScapula_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -5.5511151231257827e-017 3 -5.5511151231257827e-017 
		6 -5.5511151231257827e-017 15 0 20 -5.5511151231257827e-017 27 -5.5511151231257827e-017 
		33 -5.5511151231257827e-017 45 -5.5511151231257827e-017;
createNode animCurveTA -n "Maugli_FKMiddleFinger1_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 17.622819694952526 3 17.622819694952526 
		6 17.622819694952526 15 17.622819694952526 20 17.622819694952526 27 17.622819694952526 
		33 17.622819694952526 45 17.622819694952526;
createNode animCurveTA -n "Maugli_FKMiddleFinger2_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -23.252905752704581 3 -23.252905752704581 
		6 -23.252905752704581 15 -23.252905752704581 20 -23.252905752704581 27 -23.252905752704581 
		33 -23.252905752704581 45 -23.252905752704581;
createNode animCurveTA -n "Maugli_FKMiddleFinger3_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_FKThumbFinger1_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -10.372922440313587 3 -10.372922440313587 
		6 -10.372922440313587 15 -10.372922440313587 20 -10.372922440313587 27 -10.372922440313587 
		33 -10.372922440313587 45 -10.372922440313587;
createNode animCurveTA -n "Maugli_FKThumbFinger1_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 2.7620263328639107 3 2.7620263328639107 
		6 2.7620263328639107 15 2.7620263328639107 20 2.7620263328639107 27 2.7620263328639107 
		33 2.7620263328639107 45 2.7620263328639107;
createNode animCurveTA -n "Maugli_FKThumbFinger1_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -32.466562028725463 3 -32.466562028725463 
		6 -32.466562028725463 15 -32.466562028725463 20 -32.466562028725463 27 -32.466562028725463 
		33 -32.466562028725463 45 -32.466562028725463;
createNode animCurveTA -n "Maugli_FKThumbFinger2_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -26.277332307519721 3 -26.277332307519721 
		6 -26.277332307519721 15 -26.277332307519721 20 -26.277332307519721 27 -26.277332307519721 
		33 -26.277332307519721 45 -26.277332307519721;
createNode animCurveTA -n "Maugli_FKBackA_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 7.8357327658317191 3 -5.4763721250390986 
		6 6.4055717369175564 15 11.677204008095444 20 5.5200947496562005 27 10.582470551048013 
		33 12.864834591151608 38 7.8357327658317191 45 7.8357327658317191;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 9 9 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 9 9 10 
		10;
createNode animCurveTA -n "Maugli_FKBackA_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -7.5265731098501263 3 -7.1963732709887047 
		6 0.29990014233482543 15 -2.7094006302696481 20 2.9816958823062691 27 -8.4163047868544698 
		33 -14.923678682216856 38 -7.5265731098501263 45 -7.5265731098501263;
	setAttr -s 9 ".kit[0:8]"  3 1 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 1 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kix[1:8]"  0.9953654408454895 0.9813687801361084 0.99500775337219238 
		0.97036796808242798 0.81108343601226807 0.99910432100296021 1 1;
	setAttr -s 9 ".kiy[1:8]"  0.09616495668888092 0.19213347136974335 
		0.099798202514648438 -0.24163199961185455 -0.584930419921875 0.042313195765018463 
		0 0;
	setAttr -s 9 ".kox[1:8]"  0.9953654408454895 0.9813687801361084 0.99500775337219238 
		0.97036796808242798 0.81108343601226807 0.99910432100296021 1 1;
	setAttr -s 9 ".koy[1:8]"  0.096164971590042114 0.19213347136974335 
		0.099798202514648438 -0.24163199961185455 -0.584930419921875 0.042313195765018463 
		0 0;
createNode animCurveTA -n "Maugli_FKBackA_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -5.4975000363152615 3 -11.697743027196484 
		6 21.161852132882387 15 26.46175362899357 20 2.9723113904849465 27 17.269930590268984 
		33 22.529215364620924 38 -5.4975000363152615 45 -5.4975000363152615;
	setAttr -s 9 ".kit[0:8]"  3 1 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 1 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kix[1:8]"  0.92163705825805664 0.51486921310424805 
		0.82681608200073242 0.92813414335250854 0.78556376695632935 0.67814701795578003 1 
		1;
	setAttr -s 9 ".kiy[1:8]"  0.38805311918258667 0.85726869106292725 
		-0.56247240304946899 -0.37224578857421875 0.61878073215484619 -0.73492628335952759 
		0 0;
	setAttr -s 9 ".kox[1:8]"  0.92163723707199097 0.51486921310424805 
		0.82681608200073242 0.92813414335250854 0.78556376695632935 0.67814701795578003 1 
		1;
	setAttr -s 9 ".koy[1:8]"  0.38805264234542847 0.85726869106292725 
		-0.56247240304946899 -0.37224578857421875 0.61878073215484619 -0.73492628335952759 
		0 0;
createNode animCurveTA -n "Maugli_FKBackB_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 2.7266862105714793 3 -5.508574505928916 
		6 10.750110269730422 15 16.261636550857936 20 10.35938231400258 27 15.638182665730222 
		33 17.522347415421972 38 2.7266862105714793 45 2.7266862105714793;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 9 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 9 10 10 
		10;
createNode animCurveTA -n "Maugli_FKBackB_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.24259990801533335 3 -3.8001840222380867 
		6 1.7741357876743797 15 -1.4140950300514488 20 -1.8987833066161504 27 -8.7555822779724579 
		33 -19.638638609299615 38 0.24259990801533335 45 0.24259990801533335;
	setAttr -s 9 ".kit[0:8]"  3 10 1 1 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 1 1 10 10 10 10 
		10;
	setAttr -s 9 ".kix[2:8]"  0.94668114185333252 0.98799610137939453 
		1 0.81364899873733521 0.91923123598098755 1 1;
	setAttr -s 9 ".kiy[2:8]"  0.32217216491699219 -0.15447887778282166 
		0 -0.58135640621185303 0.3937181830406189 0 0;
	setAttr -s 9 ".kox[2:8]"  0.94668114185333252 0.98799616098403931 
		1 0.81364899873733521 0.91923123598098755 1 1;
	setAttr -s 9 ".koy[2:8]"  0.3221721351146698 -0.15447887778282166 
		0 -0.58135640621185303 0.3937181830406189 0 0;
createNode animCurveTA -n "Maugli_FKBackB_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.5001242681430698 3 -18.997072411474811 
		6 20.088723358888039 15 23.070204237982853 20 7.5206905995454116 27 19.683684654342269 
		33 30.122026118103854 38 1.5001242681430698 45 1.5001242681430698;
	setAttr -s 9 ".kit[0:8]"  3 10 1 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 1 10 10 10 10 10 
		10;
	setAttr -s 9 ".kix[2:8]"  0.90581899881362915 0.90500861406326294 
		0.98925834894180298 0.73949116468429565 0.75611227750778198 1 1;
	setAttr -s 9 ".kiy[2:8]"  0.42366492748260498 -0.42539322376251221 
		-0.14617756009101868 0.67316627502441406 -0.6544419527053833 0 0;
	setAttr -s 9 ".kox[2:8]"  0.90581899881362915 0.90500861406326294 
		0.98925834894180298 0.73949116468429565 0.75611227750778198 1 1;
	setAttr -s 9 ".koy[2:8]"  0.42366492748260498 -0.42539322376251221 
		-0.14617756009101868 0.67316627502441406 -0.6544419527053833 0 0;
createNode animCurveTA -n "Maugli_FKChest_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -12.769021381384317 3 -19.723527175141786 
		6 -0.006699395973682739 15 3.9403823740726858 20 2.937786003739677 27 7.4353292875786918 
		33 8.5482241386395685 38 -12.769021381384317 45 -12.769021381384317;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 9 9 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 9 9 10 10 
		10;
createNode animCurveTA -n "Maugli_FKChest_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 4.6070431346914544 3 -3.6285577503922597 
		6 22.899301270594027 15 22.934886831019224 20 -8.8577338733942597 27 -11.649618249971148 
		33 -16.270319494250067 38 4.6070431346914544 45 4.6070431346914544;
	setAttr -s 9 ".kit[0:8]"  3 1 10 1 9 9 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 1 10 1 9 9 10 10 
		10;
	setAttr -s 9 ".kix[1:8]"  0.9544188380241394 1 0.91025054454803467 
		0.55239486694335938 0.95820647478103638 0.79086852073669434 1 1;
	setAttr -s 9 ".kiy[1:8]"  0.29847085475921631 0 -0.41405782103538513 
		-0.83358258008956909 -0.28607773780822754 0.61198616027832031 0 0;
	setAttr -s 9 ".kox[1:8]"  0.95441871881484985 1 0.91025060415267944 
		0.55239486694335938 0.95820647478103638 0.79086852073669434 1 1;
	setAttr -s 9 ".koy[1:8]"  0.29847106337547302 0 -0.41405788064002991 
		-0.83358258008956909 -0.28607773780822754 0.61198616027832031 0 0;
createNode animCurveTA -n "Maugli_FKChest_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 4.8308420450374907 3 -2.9604726316411916 
		6 -2.8504991520244971 15 -0.29514717970579896 20 21.186274144033224 27 28.522103373283482 
		33 37.126653930390518 38 4.8308420450374907 45 4.8308420450374907;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "Maugli_FKNeck_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 25.578538688645114 6 -51.454866395407883 
		15 -56.992633532429238 20 -39.521498843287461 27 4.0296970860089383 33 -8.5295628592278341 
		45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 3;
createNode animCurveTA -n "Maugli_FKNeck_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 12.142913525112947 6 -9.7021035810509808 
		15 -3.2034011670061511 20 4.2861281070543793 27 -25.177460256517559 33 -7.2248359344433002 
		45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 9 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 9 10 10 10 3;
createNode animCurveTA -n "Maugli_FKNeck_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 23.361538997010605 6 -40.982249404916601 
		15 -45.705456240465992 20 -16.858414171764625 27 40.997506660410586 33 -1.292529318902266 
		45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_FKHead_M_Man_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -6.9400884964770713 3 14.781386168099987 
		6 6.7033157228500864 15 11.341767788311579 20 2.5112097803009954 27 -1.4322809912502421 
		33 9.5362894562382436 38 7.7744737292117732 45 -6.9400884964770713;
	setAttr -s 9 ".kit[0:8]"  3 10 9 9 9 10 9 9 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 9 9 9 10 9 9 
		3;
createNode animCurveTA -n "Maugli_FKHead_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 3.508580449788079 3 2.7284397678499448 
		6 7.2000037858741583 15 -3.6193849352910643 20 -5.4538225710807371 27 6.1176146391522215 
		33 -14.237616538463456 38 8.0944773684760261 45 3.508580449788079;
	setAttr -s 9 ".kit[0:8]"  9 10 10 1 10 10 10 10 
		9;
	setAttr -s 9 ".kot[0:8]"  9 10 10 1 10 10 10 10 
		9;
	setAttr -s 9 ".kix[3:8]"  0.98589664697647095 1 0.94274085760116577 
		0.99560189247131348 0.79067379236221313 0.94589740037918091;
	setAttr -s 9 ".kiy[3:8]"  -0.16735537350177765 0 -0.33352604508399963 
		0.093684583902359009 0.61223769187927246 -0.32446578145027161;
	setAttr -s 9 ".kox[3:8]"  0.98589664697647095 1 0.94274085760116577 
		0.99560189247131348 0.79067379236221313 0.94589740037918091;
	setAttr -s 9 ".koy[3:8]"  -0.16735535860061646 0 -0.33352604508399963 
		0.093684583902359009 0.61223769187927246 -0.32446578145027161;
createNode animCurveTA -n "Maugli_FKHead_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 5.0972336912670713 3 8.595233502816999 
		6 -0.12226863063025026 15 -5.1288448436197527 20 -15.140490377819066 27 12.442787729907378 
		33 31.655939185785346 38 0.50087786114096677 45 5.0972336912670713;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTA -n "Maugli_FKScapula_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 3.6745332739058547 1 27.385356544262446 
		3 10.49129468566286 6 40.629555192666103 15 40.629555192666103 20 44.442162411326009 
		27 44.442162411326009 33 44.442162411326009 45 3.6745332739058547;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTA -n "Maugli_FKScapula_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -6.3459812884849134 1 -29.674888071613154 
		3 6.1020852318245815 6 -5.3215324622709259 15 -5.3215324622709259 20 -3.3747742575314623 
		27 -3.3747742575314623 33 -3.3747742575314623 45 -6.3459812884849134;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTA -n "Maugli_FKScapula_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.71910078156005675 1 10.71885548232019 
		3 4.3685739604585097 6 23.247197488947268 15 23.247197488947268 20 -11.555579479448269 
		27 -11.555579479448269 33 -11.555579479448269 45 -0.71910078156005675;
createNode animCurveTL -n "Maugli_FKScapula_R_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -2.7755575615628914e-017 3 -2.7755575615628914e-017 
		6 -2.7755575615628914e-017 15 0 20 -2.7755575615628914e-017 27 -2.7755575615628914e-017 
		33 -2.7755575615628914e-017 45 -2.7755575615628914e-017;
createNode animCurveTL -n "Maugli_FKScapula_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "Maugli_FKScapula_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 5.5511151231257827e-017 3 5.5511151231257827e-017 
		6 5.5511151231257827e-017 15 0 20 5.5511151231257827e-017 27 5.5511151231257827e-017 
		33 5.5511151231257827e-017 45 5.5511151231257827e-017;
createNode animCurveTA -n "Maugli_FKMiddleFinger1_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_FKMiddleFinger2_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -67.588216236699324 3 -67.588216236699324 
		6 -67.588216236699324 15 -67.588216236699324 20 -67.588216236699324 27 -67.588216236699324 
		33 -67.588216236699324 45 -67.588216236699324;
createNode animCurveTA -n "Maugli_FKMiddleFinger3_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -81.669521342510606 3 -81.669521342510606 
		6 -50.127763106059632 15 -50.127763106059632 20 -50.127763106059632 27 -50.127763106059632 
		33 -50.127763106059632 45 -81.669521342510606;
createNode animCurveTA -n "Maugli_FKThumbFinger1_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 25.665274764482422 3 25.665274764482422 
		6 21.479251289053622 15 21.479251289053622 20 21.479251289053622 27 21.479251289053622 
		33 21.479251289053622 45 25.665274764482422;
createNode animCurveTA -n "Maugli_FKThumbFinger1_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 36.541774445263137 3 36.541774445263137 
		6 15.303715382357385 15 15.303715382357385 20 15.303715382357385 27 15.303715382357385 
		33 15.303715382357385 45 36.541774445263137;
createNode animCurveTA -n "Maugli_FKThumbFinger1_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -67.421493922591793 3 -67.421493922591793 
		6 -70.813273286366112 15 -70.813273286366112 20 -70.813273286366112 27 -70.813273286366112 
		33 -70.813273286366112 45 -67.421493922591793;
createNode animCurveTA -n "Maugli_FKThumbFinger2_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 47.81080993924823 3 47.81080993924823 
		6 -5.1434129228580128 15 -5.1434129228580128 20 -5.1434129228580128 27 -5.1434129228580128 
		33 -5.1434129228580128 45 47.81080993924823;
createNode animCurveTU -n "Maugli_Main_Man_visibility";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_Center_M_CenterBtwFeet";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_Center_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -8.4444129496952112 3 -2.2011725163171088 
		6 -2.2011725163171092 15 -2.2011725163171127 20 -2.2011725163171092 27 -2.2011725163171119 
		33 -3.3573285976506599 45 -8.4444129496952112;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 9 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 9 3;
createNode animCurveTA -n "Maugli_Center_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.96917688750520981 3 -1.3139784179066183 
		6 -1.3139784179066187 15 -1.3139784179066192 20 -1.3139784179066187 27 -1.3139784179066183 
		33 -1.2245853980962191 45 -0.96917688750520981;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 9 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 9 10;
createNode animCurveTA -n "Maugli_Center_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 3.1650958122187984 3 7.338931820677387 
		6 -38.153240591899369 15 -42.410050604621958 20 5.2088054006294922 27 0.95834645064120982 
		33 1.5304668503576411 45 3.1650958122187984;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 9 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 9 10;
createNode animCurveTL -n "Maugli_Center_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.13106792216224994 3 -0.34682174069608007 
		6 -0.20989432242731354 15 -0.25018226360760765 20 -0.16889365194514672 27 -0.25020074020568273 
		33 -0.16284428446305008 45 -0.13106792216224994;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 9 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 9 3;
createNode animCurveTL -n "Maugli_Center_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.024349347202935689 3 -0.026885259677444151 
		6 0.60670672330180597 15 0.8277880882612052 20 0.30575720485542929 27 0.25183847662021858 
		33 0.080002269213451938 45 0.024349347202935689;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 3;
createNode animCurveTL -n "Maugli_Center_M_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.0012760952138130693 3 0.01919317453508422 
		6 -0.028613297339596902 15 -0.013321835031492715 20 -0.013242348145081143 27 -0.019391336599447986 
		33 -0.016288696399240139 45 -0.0012760952138130693;
	setAttr -s 8 ".kit[0:7]"  1 10 10 9 9 9 9 9;
	setAttr -s 8 ".kot[0:7]"  1 10 10 9 9 9 9 9;
	setAttr -s 8 ".kix[0:7]"  0.99844598770141602 1 1 0.99945801496505737 
		0.9998849630355835 0.99997532367706299 0.99954444169998169 0.99929642677307129;
	setAttr -s 8 ".kiy[0:7]"  0.055728472769260406 0 0 0.032919894903898239 
		-0.015172009356319904 -0.0070298607461154461 0.030178314074873924 0.037505097687244415;
	setAttr -s 8 ".kox[0:7]"  0.99844598770141602 1 1 0.99945801496505737 
		0.9998849630355835 0.99997532367706299 0.99954444169998169 0.99929642677307129;
	setAttr -s 8 ".koy[0:7]"  0.055728495121002197 0 0 0.032919894903898239 
		-0.015172009356319904 -0.0070298607461154461 0.030178314074873924 0.037505097687244415;
createNode animCurveTA -n "Maugli_IKLegBackBall_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTU -n "Maugli_FKIKLegBack_L_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegBack_L_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegBack_L_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 15 10 20 10 27 10 33 10 
		45 10;
createNode animCurveTU -n "Maugli_PoleLegBack_L_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 15 10 20 10 27 10 33 10 
		45 10;
createNode animCurveTL -n "Maugli_PoleLegBack_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "Maugli_PoleLegBack_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "Maugli_PoleLegBack_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTU -n "Maugli_IKLegBack_L_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
createNode animCurveTU -n "Maugli_IKLegBack_L_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
createNode animCurveTU -n "Maugli_IKLegBack_L_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTU -n "Maugli_IKLegBack_L_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTU -n "Maugli_IKLegBack_L_legAim";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 15 10 20 10 27 10 33 10 
		45 10;
createNode animCurveTU -n "Maugli_IKLegBack_L_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 25 3 25 6 25 15 25 20 25 27 25 33 25 
		45 25;
createNode animCurveTU -n "Maugli_IKLegBack_L_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTU -n "Maugli_IKLegBack_L_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBack_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBack_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBack_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "Maugli_IKLegBack_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "Maugli_IKLegBack_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.76278640316887203 3 -0.76278640316887203 
		6 -0.76278640316887203 15 -0.76278640316887203 20 -0.76278640316887203 27 -0.76278640316887203 
		33 -0.76278640316887203 45 -0.76278640316887203;
createNode animCurveTL -n "Maugli_IKLegBack_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "Maugli_BendNeck_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "Maugli_BendNeck_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "Maugli_BendNeck_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTU -n "Maugli_FKIKSpine_M_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKSpine_M_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKSpine_M_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBackBall_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTU -n "Maugli_FKIKLegBack_R_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegBack_R_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegBack_R_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 15 10 20 10 27 10 33 10 
		45 10;
createNode animCurveTU -n "Maugli_PoleLegBack_R_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 15 10 20 10 27 10 33 10 
		45 10;
createNode animCurveTL -n "Maugli_PoleLegBack_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -2.2204460492503131e-016 3 -2.2204460492503131e-016 
		6 -2.2204460492503131e-016 15 0 20 -2.2204460492503131e-016 27 -2.2204460492503131e-016 
		33 -2.2204460492503131e-016 45 -2.2204460492503131e-016;
createNode animCurveTL -n "Maugli_PoleLegBack_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "Maugli_PoleLegBack_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -5.5511151231257827e-017 3 -5.5511151231257827e-017 
		6 -5.5511151231257827e-017 15 0 20 -5.5511151231257827e-017 27 -5.5511151231257827e-017 
		33 -5.5511151231257827e-017 45 -5.5511151231257827e-017;
createNode animCurveTU -n "Maugli_IKLegBack_R_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
createNode animCurveTU -n "Maugli_IKLegBack_R_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
createNode animCurveTU -n "Maugli_IKLegBack_R_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTU -n "Maugli_IKLegBack_R_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTU -n "Maugli_IKLegBack_R_legAim";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 15 10 20 10 27 10 33 10 
		45 10;
createNode animCurveTU -n "Maugli_IKLegBack_R_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 25 3 25 6 25 15 25 20 25 27 25 33 25 
		45 25;
createNode animCurveTU -n "Maugli_IKLegBack_R_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTU -n "Maugli_IKLegBack_R_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBack_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -17.042137663821414 3 -17.042137663821414 
		6 -17.042137663821414 15 -17.042137663821414 20 -17.042137663821414 27 -17.042137663821414 
		33 -17.042137663821414 45 -17.042137663821414;
createNode animCurveTA -n "Maugli_IKLegBack_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBack_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "Maugli_IKLegBack_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1.1102230246251563e-016 3 1.1102230246251563e-016 
		6 1.1102230246251563e-016 15 0 20 1.1102230246251563e-016 27 1.1102230246251563e-016 
		33 1.1102230246251563e-016 45 1.1102230246251563e-016;
createNode animCurveTL -n "Maugli_IKLegBack_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.019491142195864015 3 0.019491142195864015 
		6 0.019491142195864015 15 0.019491142195864015 20 0.019491142195864015 27 0.019491142195864015 
		33 0.019491142195864015 45 0.019491142195864015;
createNode animCurveTL -n "Maugli_IKLegBack_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.063585363072848899 3 -0.063585363072848899 
		6 -0.063585363072848899 15 -0.063585363072848899 20 -0.063585363072848899 27 -0.063585363072848899 
		33 -0.063585363072848899 45 -0.063585363072848899;
createNode animCurveTU -n "Maugli_FKIKSplineTail_M_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKSplineTail_M_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKSplineTail_M_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 15 10 20 10 27 10 33 10 
		45 10;
createNode animCurveTU -n "Maugli_WagCurveSplineTail_M_increment";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
createNode animCurveTU -n "Maugli_WagCurveSplineTail_M_multiply";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
createNode animCurveTU -n "Maugli_WagCurveSplineTail_M_timeOffset";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
createNode animCurveTU -n "Maugli_WagCurveSplineTail_M_enable";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTA -n "Maugli_WagCurveSplineTail_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_WagCurveSplineTail_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_WagCurveSplineTail_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTU -n "Maugli_IKSplineTail2_M_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTU -n "Maugli_IKSplineTail2_M_twist";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTU -n "Maugli_IKSplineTail2_M_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "Maugli_IKSplineTail2_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.31618923007172439 3 -0.10436363035411711 
		6 -0.53240706827130335 15 1.1552822098757107 20 -0.45307112537683525 27 -0.31618923007172439 
		33 -0.56899189774700354 45 -0.31618923007172439;
	setAttr -s 8 ".kit[0:7]"  9 10 10 10 10 10 1 1;
	setAttr -s 8 ".kot[0:7]"  9 10 10 10 10 10 1 1;
	setAttr -s 8 ".kix[6:7]"  0.79373061656951904 0.49509531259536743;
	setAttr -s 8 ".kiy[6:7]"  -0.60826951265335083 0.86883866786956787;
	setAttr -s 8 ".kox[6:7]"  0.79373061656951904 0.49509531259536743;
	setAttr -s 8 ".koy[6:7]"  -0.60826951265335083 0.86883866786956787;
createNode animCurveTL -n "Maugli_IKSplineTail2_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -1.0020975550085076 3 -1.031171742924661 
		6 0.43905010060293259 15 0.65672639489593143 20 -0.24288168880291972 27 -1.0020975550085076 
		33 -1.1846782094877684 45 -1.0020975550085076;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 3;
createNode animCurveTL -n "Maugli_IKSplineTail2_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.80886811842270168 3 0.91405484485345612 
		6 0.071554602690299896 15 -0.64743471577407019 20 0.1919773714486058 27 0.80886811842270168 
		33 -0.14725372293183858 45 0.80886811842270168;
	setAttr -s 8 ".kit[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kix[0:7]"  0.41808897256851196 0.26179462671279907 
		0.24815301597118378 0.96828103065490723 0.26485896110534668 0.78741621971130371 1 
		0.38594341278076172;
	setAttr -s 8 ".kiy[0:7]"  0.90840607881546021 -0.96512359380722046 
		-0.96872085332870483 0.24986374378204346 0.9642871618270874 -0.61642169952392578 
		0 0.92252242565155029;
	setAttr -s 8 ".kox[0:7]"  0.41808891296386719 0.26179462671279907 
		0.24815301597118378 0.96828103065490723 0.26485896110534668 0.78741621971130371 1 
		0.38594344258308411;
	setAttr -s 8 ".koy[0:7]"  0.90840613842010498 -0.96512359380722046 
		-0.96872085332870483 0.24986374378204346 0.9642871618270874 -0.61642169952392578 
		0 0.92252248525619507;
createNode animCurveTU -n "Maugli_IKSplineTail1_M_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "Maugli_IKSplineTail1_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 3.1086244689504383e-015 3 -0.42477865160300787 
		6 -0.071027038166166845 15 -0.6612440309439539 20 0.14934859436474834 27 3.1086244689504383e-015 
		33 -0.00086357670863002056 45 3.1086244689504383e-015;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 9 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 9 10 3;
createNode animCurveTL -n "Maugli_IKSplineTail1_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.16519211009181056 3 -0.10661114231248447 
		6 0.52288783244302905 15 0.79118175294967097 20 -0.21746508783983387 27 -0.16519211009181056 
		33 -0.12974839757463918 45 -0.16519211009181056;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 9 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 9 10 3;
createNode animCurveTL -n "Maugli_IKSplineTail1_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.010972047845733357 3 0.18213432656276435 
		6 -0.27416564223182893 15 0.23897506709531693 20 0.45783460524927005 27 0.010972047845733357 
		33 0.14604203684498318 45 0.010972047845733357;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 3;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_FKRump_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -18.638044314952673 3 -17.371409693292826 
		6 -17.371409693292826 15 -17.371409693292826 20 -16.894569921635178 27 -16.894569921635178 
		33 -16.894569921635178 45 -18.638044314952673;
createNode animCurveTA -n "Maugli_FKRump_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 5.9273289705481567 3 7.7805595077458065 
		6 7.7805595077458065 15 7.7805595077458065 20 7.6352737017559473 27 7.6352737017559473 
		33 7.6352737017559473 45 5.9273289705481567;
createNode animCurveTA -n "Maugli_FKRump_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 12.021048230974857 3 17.058639263800064 
		6 17.058639263800064 15 17.058639263800064 20 17.122594910424677 27 17.122594910424677 
		33 17.122594910424677 45 12.021048230974857;
createNode animCurveTL -n "Maugli_FKRump_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -5.5511151231257827e-017 3 -5.5511151231257827e-017 
		6 -5.5511151231257827e-017 15 0 20 -5.5511151231257827e-017 27 -5.5511151231257827e-017 
		33 -5.5511151231257827e-017 45 -5.5511151231257827e-017;
createNode animCurveTL -n "Maugli_FKRump_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 2.2204460492503131e-016 3 2.2204460492503131e-016 
		6 2.2204460492503131e-016 15 0 20 2.2204460492503131e-016 27 2.2204460492503131e-016 
		33 2.2204460492503131e-016 45 2.2204460492503131e-016;
createNode animCurveTL -n "Maugli_FKRump_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 2.2204460492503131e-016 3 2.2204460492503131e-016 
		6 2.2204460492503131e-016 15 0 20 2.2204460492503131e-016 27 2.2204460492503131e-016 
		33 2.2204460492503131e-016 45 2.2204460492503131e-016;
createNode animCurveTA -n "Maugli_FKRump_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -18.710504463926263 3 -20.962508546914744 
		6 -13.919695153372196 15 -13.919695153372196 20 -15.991065966471341 27 -15.991065966471341 
		33 -15.991065966471341 45 -18.710504463926263;
createNode animCurveTA -n "Maugli_FKRump_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 8.2582530676151027 3 10.903627318119341 
		6 10.292963159775988 15 10.292963159775988 20 10.72521067142522 27 10.72521067142522 
		33 10.72521067142522 45 8.2582530676151027;
createNode animCurveTA -n "Maugli_FKRump_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 5.1050521316126698 3 6.3635146888837477 
		6 12.170112585053891 15 12.170112585053891 20 11.792269757405402 27 11.792269757405402 
		33 11.792269757405402 45 5.1050521316126698;
createNode animCurveTL -n "Maugli_FKRump_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 5.5511151231257827e-017 3 5.5511151231257827e-017 
		6 5.5511151231257827e-017 15 0 20 5.5511151231257827e-017 27 5.5511151231257827e-017 
		33 5.5511151231257827e-017 45 5.5511151231257827e-017;
createNode animCurveTL -n "Maugli_FKRump_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "Maugli_FKRump_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_FKBackA_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -6.1344158462123248 3 -1.9469491819455829 
		6 7.3214016294965418 15 7.3214016294965418 20 -6.1344158462123248 27 -6.1344158462123248 
		33 -6.1344158462123248 45 -6.1344158462123248;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_FKBackA_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -2.6442010631261756 3 -2.6578742866646885 
		6 -2.6377556919626377 15 -2.6377556919626377 20 -2.6442010631261756 27 -2.6442010631261756 
		33 -2.6442010631261756 45 -2.6442010631261756;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_FKBackA_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.28408691297585409 3 0.090318661129058286 
		6 -0.33878214061872597 15 -0.33878214061872597 20 0.28408691297585409 27 0.28408691297585409 
		33 0.28408691297585409 45 0.28408691297585409;
	setAttr -s 8 ".kit[1:7]"  9 10 10 10 10 10 10;
	setAttr -s 8 ".kot[1:7]"  9 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_FKBackB_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -4.0937696667714745 3 18.676210616818985 
		6 22.52177647499802 15 18.854572468286012 20 19.628693838990646 27 24.160044601377116 
		33 16.397458616342277 45 -4.0937696667714745;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 3;
createNode animCurveTA -n "Maugli_FKBackB_M_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -8.7401097734428159 3 7.6580097939129752 
		6 -3.0773443770027038 15 -3.2501053911133106 20 -0.25221346691699342 27 4.0560050196019368 
		33 0.78097749744491518 45 -8.7401097734428159;
	setAttr -s 8 ".kit[0:7]"  3 10 9 9 9 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 9 9 9 10 10 3;
createNode animCurveTA -n "Maugli_FKBackB_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.62309581808855541 3 -5.7833585583159035 
		6 -2.8016138808386577 15 -2.5991540949622931 20 -5.1049944916884069 27 -7.3631594582155184 
		33 -5.8842227292790401 45 0.62309581808855541;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 9 10 9 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 9 10 9 3;
createNode animCurveTA -n "Maugli_FKChest_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -25.928322657740519 3 -25.928322657740519 
		6 -25.928322657740519 15 -25.928322657740519 20 -25.928322657740519 27 -25.928322657740519 
		33 -25.928322657740519 38 -25.928322657740519 45 -25.928322657740519;
createNode animCurveTA -n "Maugli_FKChest_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -6.0685067306724134 3 -6.0685067306724134 
		6 -6.0685067306724134 15 -6.0685067306724134 20 -6.0685067306724134 27 -6.0685067306724134 
		33 -6.0685067306724134 38 -6.0685067306724134 45 -6.0685067306724134;
createNode animCurveTA -n "Maugli_FKChest_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 2.6635387051032011 3 2.6635387051032011 
		6 2.6635387051032011 15 2.6635387051032011 20 2.6635387051032011 27 2.6635387051032011 
		33 2.6635387051032011 38 2.6635387051032011 45 2.6635387051032011;
createNode animCurveTA -n "Maugli_FKNeck_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 22.628337533497174 3 23.451011261089779 
		6 54.279200185957514 15 56.741350938182762 20 43.187962531257902 27 19.657458233860005 
		33 5.9944476838177252 45 22.628337533497174;
	setAttr -s 8 ".kit[0:7]"  3 1 1 10 10 10 10 1;
	setAttr -s 8 ".kot[0:7]"  3 1 1 10 10 10 10 1;
	setAttr -s 8 ".kix[1:7]"  0.99536657333374023 0.96885132789611816 
		1 0.52571791410446167 0.5552031397819519 0.99628663063049316 0.94710636138916016;
	setAttr -s 8 ".kiy[1:7]"  0.096153154969215393 0.24764314293861389 
		0 -0.85065895318984985 -0.83171474933624268 0.086098469793796539 0.32091993093490601;
	setAttr -s 8 ".kox[1:7]"  0.99536657333374023 0.96885138750076294 
		1 0.52571791410446167 0.5552031397819519 0.99628663063049316 0.94710624217987061;
	setAttr -s 8 ".koy[1:7]"  0.096153169870376587 0.24764314293861389 
		0 -0.85065895318984985 -0.83171474933624268 0.086098469793796539 0.32092022895812988;
createNode animCurveTA -n "Maugli_FKNeck_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 3.6826813105759961 3 -4.3853754964886793 
		6 -3.5141921543283332 15 -3.5141921543283332 20 -2.5861791166219295 27 2.7646700269825244 
		33 4.7895278261489835 45 3.6826813105759961;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 9 9 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 9 9 10 10;
createNode animCurveTA -n "Maugli_FKNeck_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 2.2991021693981635 3 -0.60643737733907999 
		6 -6.1268268212913926 15 -6.1268268212913926 20 -11.728957222640958 27 -6.5563609769740809 
		33 -2.7717929843652609 45 2.2991021693981635;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 3;
createNode animCurveTU -n "Maugli_FKHead_M_Global";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 15 10 20 10 27 10 33 10 
		45 10;
createNode animCurveTA -n "Maugli_FKHead_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -7.8426637274840703 3 16.308637715198689 
		6 65.168178147629561 15 65.168178147629561 20 -17.458059703825118 27 -17.458059703825118 
		33 -17.458059703825118 45 -7.8426637274840703;
	setAttr -s 8 ".kit[0:7]"  1 10 10 10 10 10 10 1;
	setAttr -s 8 ".kot[0:7]"  1 10 10 10 10 10 10 1;
	setAttr -s 8 ".kix[0:7]"  0.93378567695617676 0.1550532728433609 
		1 1 1 1 1 0.85659629106521606;
	setAttr -s 8 ".kiy[0:7]"  0.35783290863037109 0.98790615797042847 
		0 0 0 0 0 0.5159873366355896;
	setAttr -s 8 ".kox[0:7]"  0.93378567695617676 0.1550532728433609 
		1 1 1 1 1 0.85659617185592651;
	setAttr -s 8 ".koy[0:7]"  0.35783287882804871 0.98790615797042847 
		0 0 0 0 0 0.51598739624023438;
createNode animCurveTA -n "Maugli_FKHead_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -7.5490945101966842 3 -8.5854869135165064 
		6 -10.250406724172178 15 -10.250406724172178 20 -10.708490740125105 27 -10.708490740125105 
		33 -10.708490740125105 45 -7.5490945101966842;
	setAttr -s 8 ".kit[0:7]"  3 9 10 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 9 10 10 10 10 10 3;
createNode animCurveTA -n "Maugli_FKHead_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 5.461028169262887 3 2.5067387597481039 
		6 3.9616376662189174 15 3.9616376662189174 20 2.1409441235796929 27 2.1409441235796929 
		33 2.1409441235796929 45 5.461028169262887;
	setAttr -s 8 ".kit[0:7]"  3 1 10 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 1 10 10 10 10 10 3;
	setAttr -s 8 ".kix[1:7]"  0.97489631175994873 1 1 1 1 1 1;
	setAttr -s 8 ".kiy[1:7]"  -0.22265951335430145 0 0 0 0 0 0;
	setAttr -s 8 ".kox[1:7]"  0.97489625215530396 1 1 1 1 1 1;
	setAttr -s 8 ".koy[1:7]"  -0.22265955805778503 0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_Main_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
createNode animCurveTU -n "Maugli_Main_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
createNode animCurveTU -n "Maugli_Main_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
createNode animCurveTA -n "Maugli_Main_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_Main_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_Main_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "Maugli_Main_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "Maugli_Main_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "Maugli_Main_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTU -n "Maugli_Main_visibility";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTA -n "Maugli_kolchan_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -16.498609615445837 3 -16.934618219481347 
		6 23.158878578144229 15 -28.395552824734335 20 -25.940557435026662 24 -7.0896788328416189 
		29 -18.102833600944912 45 -16.498609615445837;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 3;
createNode animCurveTA -n "Maugli_kolchan_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -6.4006181765439756 3 -6.3867330312625192 
		6 -3.5659895902248273 15 -5.2793009622166229 20 -6.0189827707494139 24 -6.6094756322669701 
		29 -6.3477203659411563 45 -6.4006181765439756;
	setAttr -s 8 ".kit[0:7]"  3 10 10 9 1 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 9 1 10 10 10;
	setAttr -s 8 ".kix[4:7]"  0.99997532367706299 1 1 1;
	setAttr -s 8 ".kiy[4:7]"  0.0070264530368149281 0 0 0;
	setAttr -s 8 ".kox[4:7]"  0.99997532367706299 1 1 1;
	setAttr -s 8 ".koy[4:7]"  0.0070264535024762154 0 0 0;
createNode animCurveTA -n "Maugli_kolchan_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1.8111494521402616 3 1.8597032697620373 
		6 -3.911490537254831 15 0.35441602569186154 20 2.83477539945644 24 0.74283203579223744 
		29 1.9892633532358193 45 1.8111494521402616;
	setAttr -s 8 ".kit[0:7]"  3 9 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 9 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_yashik_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 34.391117562341087 15 -37.322277194541059 
		20 -29.906337107558361 27 11.02362405240917 33 0 45 0;
	setAttr -s 8 ".kit[1:7]"  3 10 10 10 10 10 10;
	setAttr -s 8 ".kot[1:7]"  3 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_yashik_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 12.615522188229306 15 -2.5311940913457183 
		20 -0.39691365559367353 27 1.9585570868284066 33 0 45 0;
	setAttr -s 8 ".kit[1:7]"  3 10 10 10 10 10 10;
	setAttr -s 8 ".kot[1:7]"  3 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_yashik_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 3.864481254646551 15 -6.1379901002771717 
		20 21.623185563058655 27 -9.9505493035808161 33 0 45 0;
	setAttr -s 8 ".kit[1:7]"  3 10 10 10 10 10 10;
	setAttr -s 8 ".kot[1:7]"  3 10 10 10 10 10 10;
createNode animCurveTL -n "Maugli_yashik_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0.027117527680984698 15 -0.0022749989417905105 
		20 -0.00039764485540063786 27 0.0014771392774408513 33 0 45 0;
	setAttr -s 8 ".kit[1:7]"  3 10 10 10 10 10 10;
	setAttr -s 8 ".kot[1:7]"  3 10 10 10 10 10 10;
createNode animCurveTL -n "Maugli_yashik_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 -0.23684036434220893 15 -0.18668641841499306 
		20 -0.11352332575698168 27 -0.064436674269146149 33 0 45 0;
	setAttr -s 8 ".kit[1:7]"  3 10 10 10 10 10 10;
	setAttr -s 8 ".kot[1:7]"  3 10 10 10 10 10 10;
createNode animCurveTL -n "Maugli_yashik_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0.19796652222263364 15 0.27847591138679906 
		20 -0.093630506010787984 27 -0.0011346719104425574 33 0 45 0;
	setAttr -s 8 ".kit[1:7]"  3 10 10 10 10 10 10;
	setAttr -s 8 ".kot[1:7]"  3 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_l_ear_control_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 -22.548991288590667 15 -22.548991288590667 
		20 -22.548991288590667 27 0 33 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_l_ear_control_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 -25.872121951131092 15 -25.872121951131092 
		20 -25.872121951131092 27 0 33 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_l_ear_control_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 90.578862948410389 15 90.578862948410389 
		20 90.578862948410389 27 0 33 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_r_ear_control1_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 17.079548195475276 15 17.079548195475276 
		20 17.079548195475276 27 0 33 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_r_ear_control1_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 38.193575252580082 15 38.193575252580082 
		20 38.193575252580082 27 0 33 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_r_ear_control1_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 -63.47995547966314 15 -63.47995547966314 
		20 -63.47995547966314 27 0 33 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_jaw_C_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 10.815728045440752 6 10.815728045440752 
		15 10.815728045440752 20 -6.0415323717637976 27 -6.0415323717637976 33 -6.0415323717637976 
		45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 3;
createNode animCurveTA -n "Maugli_spear_control_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 15 0 45 0;
createNode animCurveTA -n "Maugli_spear_control_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 15 0 45 0;
createNode animCurveTA -n "Maugli_spear_control_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 15 0 45 0;
createNode animCurveTL -n "Maugli_spear_control_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.041982630251665931 15 0.041982630251665931 
		45 0.041982630251665931;
createNode animCurveTL -n "Maugli_spear_control_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.05682005777595385 15 -0.05682005777595385 
		45 -0.05682005777595385;
createNode animCurveTL -n "Maugli_spear_control_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.19304667407551657 15 0.19304667407551657 
		45 0.19304667407551657;
createNode animCurveTU -n "Maugli_spear_control_World_Hands";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 15 1 45 1;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTA -n "Maugli_IKLegFrontBall_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegFrontBall_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1.1 3 1.1 4 1.1 6 1.1 15 1.1 18 1.1 20 
		1.1 27 1.1 33 1.1 45 1.1;
createNode animCurveTU -n "Maugli_IKLegFront_R_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1.1 3 1.1 4 1.1 6 1.1 15 1.1 18 1.1 20 
		1.1 27 1.1 33 1.1 45 1.1;
createNode animCurveTU -n "Maugli_IKLegFront_R_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 4 0 6 0 15 0 18 0 20 0 27 0 33 
		0 45 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 4 0 6 0 15 0 18 0 20 0 27 0 33 
		0 45 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_legAim";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 10 3 10 4 10 6 10 15 10 18 10 20 10 27 
		10 33 10 45 10;
createNode animCurveTU -n "Maugli_IKLegFront_R_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 25 3 25 4 25 6 25 15 25 18 25 20 25 27 
		25 33 25 45 25;
createNode animCurveTU -n "Maugli_IKLegFront_R_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 4 0 6 0 15 0 18 0 20 0 27 0 33 
		0 45 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 4 0 6 0 15 0 18 0 20 0 27 0 33 
		0 45 0;
createNode animCurveTA -n "Maugli_IKLegFront_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 13.452853449395933 3 13.452853449395933 
		4 13.452853449395933 6 13.452853449395933 15 13.282599553960731 18 13.452853449395933 
		20 13.452853449395933 27 13.452853449395933 33 13.452853449395933 45 13.452853449395933;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "Maugli_IKLegFront_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 4 0 6 0 15 -11.329738449793471 
		18 0 20 0 27 0 33 0 45 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "Maugli_IKLegFront_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 4 0 6 0 15 24.476375962604283 18 
		0 20 0 27 0 33 0 45 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "Maugli_IKLegFront_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 5.5511151231257852e-017 3 5.5511151231257852e-017 
		4 5.5511151231257852e-017 6 0.80062127641535719 15 1.6883721780218919 18 5.5511151231257852e-017 
		20 5.5511151231257852e-017 27 5.5511151231257852e-017 33 5.5511151231257852e-017 
		45 5.5511151231257852e-017;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "Maugli_IKLegFront_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.78767523172948961 3 -0.78767523172948961 
		4 -0.78767523172948961 6 -0.29637855865056439 15 -0.37978548601806972 18 -0.78767523172948961 
		20 -0.78767523172948961 27 -0.78767523172948961 33 -0.78767523172948961 45 -0.78767523172948961;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "Maugli_IKLegFront_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.077325821529500835 3 -0.077325821529500835 
		4 -0.077325821529500835 6 0.094893735697144876 15 0.13008946024539902 18 -0.077325821529500835 
		20 -0.077325821529500835 27 -0.077325821529500835 33 -0.077325821529500835 45 -0.077325821529500835;
	setAttr -s 10 ".kit[3:9]"  1 10 10 10 10 10 10;
	setAttr -s 10 ".kot[3:9]"  1 10 10 10 10 10 10;
	setAttr -s 10 ".kix[3:9]"  0.98253470659255981 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  0.18607935309410095 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  0.98253476619720459 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  0.18607932329177856 0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegFront_L_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1.1 3 1.1 4 1.1 6 1.1 15 1.1 18 1.1 20 
		1.1 27 1.1 33 1.1 45 1.1;
createNode animCurveTU -n "Maugli_IKLegFront_L_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1.1 3 1.1 4 1.1 6 1.1 15 1.1 18 1.1 20 
		1.1 27 1.1 33 1.1 45 1.1;
createNode animCurveTU -n "Maugli_IKLegFront_L_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 4 0 6 0 15 0 18 0 20 0 27 0 33 
		0 45 0;
createNode animCurveTU -n "Maugli_IKLegFront_L_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 4 0 6 0 15 0 18 0 20 0 27 0 33 
		0 45 0;
createNode animCurveTU -n "Maugli_IKLegFront_L_legAim";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 10 3 10 4 10 6 10 15 10 18 10 20 10 27 
		10 33 10 45 10;
createNode animCurveTU -n "Maugli_IKLegFront_L_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 25 3 25 4 25 6 25 15 25 18 25 20 25 27 
		25 33 25 45 25;
createNode animCurveTU -n "Maugli_IKLegFront_L_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 4 0 6 0 15 0 18 0 20 0 27 0 33 
		0 45 0;
createNode animCurveTU -n "Maugli_IKLegFront_L_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 4 0 6 0 15 0 18 0 20 0 27 0 33 
		0 45 0;
createNode animCurveTA -n "Maugli_IKLegFront_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -4.3689304491953465 3 -4.3689304491953465 
		4 -4.3689304491953465 6 -4.3689304491953465 15 -0.99657083328664842 18 -4.3689304491953465 
		20 -4.3689304491953465 27 -4.3689304491953465 33 -4.3689304491953465 45 -4.3689304491953465;
createNode animCurveTA -n "Maugli_IKLegFront_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 4 0 6 0 15 14.260079560003678 18 
		0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_IKLegFront_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 4 0 6 0 15 26.465614643988658 18 
		0 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "Maugli_IKLegFront_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 4 0 6 0.57486329500870759 15 1.4247415764055191 
		18 0 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "Maugli_IKLegFront_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.063844748963588188 3 -0.063844748963588188 
		4 -0.063844748963588188 6 -0.0046600523029388941 15 -0.053263426479239234 18 -0.063844748963588188 
		20 -0.063844748963588188 27 -0.063844748963588188 33 -0.063844748963588188 45 -0.063844748963588188;
	setAttr -s 10 ".kit[4:9]"  9 10 10 10 10 10;
	setAttr -s 10 ".kot[4:9]"  9 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKLegFront_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.072835230653514785 3 -0.072835230653514785 
		4 -0.072835230653514785 6 -0.26800919196489753 15 -0.27868518082953481 18 -0.072835230653514785 
		20 -0.072835230653514785 27 -0.072835230653514785 33 -0.072835230653514785 45 -0.072835230653514785;
	setAttr -s 10 ".kit[3:9]"  1 10 10 10 10 10 10;
	setAttr -s 10 ".kot[3:9]"  1 10 10 10 10 10 10;
	setAttr -s 10 ".kix[3:9]"  0.99877339601516724 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[3:9]"  -0.049515791237354279 0 0 0 0 0 0;
	setAttr -s 10 ".kox[3:9]"  0.99877339601516724 1 1 1 1 1 1;
	setAttr -s 10 ".koy[3:9]"  -0.049515783786773682 0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKLegFront_L_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegFront_L_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegFront_L_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 15 10 20 10 27 10 33 10 
		45 10;
createNode animCurveTU -n "Maugli_FKIKLegFront_R_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegFront_R_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegFront_R_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 15 10 20 10 27 10 33 10 
		45 10;
createNode animCurveTA -n "Maugli_FKScapula_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_FKScapula_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_FKScapula_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "Maugli_FKScapula_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -2.2204460492503131e-016 3 -2.2204460492503131e-016 
		6 -2.2204460492503131e-016 15 0 20 -2.2204460492503131e-016 27 -2.2204460492503131e-016 
		33 -2.2204460492503131e-016 45 -2.2204460492503131e-016;
createNode animCurveTL -n "Maugli_FKScapula_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -1.1102230246251565e-016 3 -1.1102230246251565e-016 
		6 -1.1102230246251565e-016 15 0 20 -1.1102230246251565e-016 27 -1.1102230246251565e-016 
		33 -1.1102230246251565e-016 45 -1.1102230246251565e-016;
createNode animCurveTL -n "Maugli_FKScapula_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 4.4408920985006262e-016 3 4.4408920985006262e-016 
		6 4.4408920985006262e-016 15 0 20 4.4408920985006262e-016 27 4.4408920985006262e-016 
		33 4.4408920985006262e-016 45 4.4408920985006262e-016;
createNode animCurveTA -n "Maugli_FKScapula_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_FKScapula_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "Maugli_FKScapula_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "Maugli_FKScapula_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -1.1102230246251565e-016 3 -1.1102230246251565e-016 
		6 -1.1102230246251565e-016 15 0 20 -1.1102230246251565e-016 27 -1.1102230246251565e-016 
		33 -1.1102230246251565e-016 45 -1.1102230246251565e-016;
createNode animCurveTL -n "Maugli_FKScapula_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -2.2204460492503131e-016 3 -2.2204460492503131e-016 
		6 -2.2204460492503131e-016 15 0 20 -2.2204460492503131e-016 27 -2.2204460492503131e-016 
		33 -2.2204460492503131e-016 45 -2.2204460492503131e-016;
createNode animCurveTL -n "Maugli_FKScapula_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -2.2204460492503131e-016 3 -2.2204460492503131e-016 
		6 -2.2204460492503131e-016 15 0 20 -2.2204460492503131e-016 27 -2.2204460492503131e-016 
		33 -2.2204460492503131e-016 45 -2.2204460492503131e-016;
createNode animCurveTU -n "Maugli_PoleLegFront_L_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 15 10 20 10 27 10 33 10 
		45 10;
createNode animCurveTL -n "Maugli_PoleLegFront_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.34369246973235407 3 -0.30726318867366315 
		6 0.077459051071290128 15 0.077459051071290128 20 0.077459051071290128 27 0.077459051071290128 
		33 0.077459051071290128 45 0.34369246973235407;
createNode animCurveTL -n "Maugli_PoleLegFront_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.08732959492146955 3 -0.073538509457235543 
		6 -0.16524641320541572 15 -0.16524641320541572 20 -0.16524641320541572 27 -0.16524641320541572 
		33 -0.16524641320541572 45 0.08732959492146955;
createNode animCurveTL -n "Maugli_PoleLegFront_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.27202670267238233 3 0.21839391556009391 
		6 0.2197886510739398 15 0.2197886510739398 20 0.2197886510739398 27 0.2197886510739398 
		33 0.2197886510739398 45 -0.27202670267238233;
createNode animCurveTU -n "Maugli_PoleLegFront_R_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 15 10 20 10 27 10 33 10 
		45 10;
createNode animCurveTL -n "Maugli_PoleLegFront_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.31678960075780738 3 0.31678960075780738 
		6 0.20668339714033865 15 0.20668339714033865 20 0.20668339714033865 27 0.20668339714033865 
		33 0.20668339714033865 45 0.31678960075780738;
createNode animCurveTL -n "Maugli_PoleLegFront_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.11971028970415042 3 -0.11971028970415042 
		6 -0.37143850365821329 15 -0.37143850365821329 20 -0.37143850365821329 27 -0.37143850365821329 
		33 -0.37143850365821329 45 -0.11971028970415042;
createNode animCurveTL -n "Maugli_PoleLegFront_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.0005730959429199018 3 0.0005730959429199018 
		6 -0.034146367016341071 15 -0.034146367016341071 20 -0.034146367016341071 27 -0.034146367016341071 
		33 -0.034146367016341071 45 0.0005730959429199018;
createNode animCurveTL -n "curve1_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "curve1_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "curve1_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTU -n "curve1_visibility";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTA -n "curve1_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "curve1_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "curve1_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTU -n "curve1_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
createNode animCurveTU -n "curve1_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
createNode animCurveTU -n "curve1_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
createNode animCurveTA -n "IKLegBackBall_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  3 0 6 0 12 0 33 0 45 0;
createNode animCurveTA -n "IKLegBackBall_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  3 0 6 0 12 0 33 0 45 0;
createNode animCurveTA -n "IKLegBackBall_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  3 0 6 0 12 0 33 0 45 0;
createNode animCurveTA -n "IKLegBackBall_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  3 0 6 0 12 0 33 0 45 0;
createNode animCurveTA -n "IKLegFrontBall_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  3 0 6 0 12 0 33 0 45 0;
createNode animCurveTA -n "IKLegFrontBall_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  3 0 6 0 12 0 33 0 45 0;
createNode animCurveTA -n "IKLegFrontBall_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  3 0 6 0 12 0 33 0 45 0;
createNode animCurveTA -n "IKLegFrontBall_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  3 0 6 0 12 0 33 0 45 0;
createNode animCurveTL -n "IKXSplineTailCurve_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 4.0142992214232583e-036 3 4.0142992214232583e-036 
		6 4.0142992214232583e-036 15 0 20 4.0142992214232583e-036 27 4.0142992214232583e-036 
		33 4.0142992214232583e-036 45 4.0142992214232583e-036;
createNode animCurveTL -n "IKXSplineTailCurve_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTL -n "IKXSplineTailCurve_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 20 0 27 0 33 0 45 0;
createNode animCurveTA -n "IKXSplineTailCurve_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -1.272221872585407e-014 3 -1.272221872585407e-014 
		6 -1.272221872585407e-014 15 0 20 -1.272221872585407e-014 27 -1.272221872585407e-014 
		33 -1.272221872585407e-014 45 -1.272221872585407e-014;
createNode animCurveTA -n "IKXSplineTailCurve_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1.2722218725854067e-014 3 1.2722218725854067e-014 
		6 1.2722218725854067e-014 15 0 20 1.2722218725854067e-014 27 1.2722218725854067e-014 
		33 1.2722218725854067e-014 45 1.2722218725854067e-014;
createNode animCurveTA -n "IKXSplineTailCurve_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 2.8249000307521015e-030 3 2.8249000307521015e-030 
		6 2.8249000307521015e-030 15 0 20 2.8249000307521015e-030 27 2.8249000307521015e-030 
		33 2.8249000307521015e-030 45 2.8249000307521015e-030;
createNode animCurveTU -n "IKXSplineTailCurve_M_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
createNode animCurveTU -n "IKXSplineTailCurve_M_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
createNode animCurveTU -n "IKXSplineTailCurve_M_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 15 1 20 1 27 1 33 1 45 1;
createNode animCurveTA -n "IKLegBall_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  3 0 6 0 12 0 33 0 45 0;
createNode animCurveTA -n "IKLegBall_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  3 0 6 0 12 0 33 0 45 0;
createNode animCurveTA -n "IKLegBall_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  3 0 6 0 12 0 33 0 45 0;
createNode animCurveTA -n "IKLegBall_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  3 0 6 0 12 0 33 0 45 0;
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
connectAttr "attack02Source.cl" "clipLibrary1.sc[0]";
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
// End of attack2.ma
