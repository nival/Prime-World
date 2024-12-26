//Maya ASCII 2008 scene
//Name: move.ma
//Last modified: Tue, Jan 26, 2010 06:26:04 PM
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
createNode animClip -n "moveSource";
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
	setAttr ".se" 25;
	setAttr ".ci" no;
createNode animCurveTU -n "Maugli_Center_M_Man_CenterBtwFeet";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTA -n "Maugli_Center_M_Man_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 -1.350759816219101 18 -0.67537977871597432 
		25 0;
	setAttr -s 5 ".kit[1:4]"  10 9 1 3;
	setAttr -s 5 ".kot[1:4]"  10 9 1 3;
	setAttr -s 5 ".kix[3:4]"  0.99692070484161377 1;
	setAttr -s 5 ".kiy[3:4]"  0.07841617614030838 0;
	setAttr -s 5 ".kox[3:4]"  0.99692070484161377 1;
	setAttr -s 5 ".koy[3:4]"  0.078416168689727783 0;
createNode animCurveTA -n "Maugli_Center_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 3.0971605587012943 18 1.9357250954779108 
		25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 9 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 9 3;
createNode animCurveTA -n "Maugli_Center_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 19.169926907525088 5 31.909572699008535 
		11 53.685293542317204 18 30.168640114436858 25 19.169926907525088;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTL -n "Maugli_Center_M_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0.07388824761483398 11 0.065320869284700878 
		18 0.099173983791654749 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTL -n "Maugli_Center_M_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 -0.26628686163041104 11 -0.62756468829139656 
		18 -0.14983725205880732 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTL -n "Maugli_Center_M_Man_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 -0.0074423551185932475 11 -0.043777693156996408 
		18 -0.026013710698867223 25 0;
	setAttr -s 5 ".kit[0:4]"  3 9 10 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 10 9 3;
createNode animCurveTU -n "Maugli_Fingers_L_Man_MiddleFingerCurl";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 4.6 25 4.6;
createNode animCurveTA -n "Maugli_IKLegBall_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegToe_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegToe_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 3.1805546814635168e-015 5 0 11 0 18 0 
		25 3.1805546814635168e-015;
createNode animCurveTA -n "Maugli_IKLegToe_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTU -n "Maugli_FKIKLeg_L_Man_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLeg_L_Man_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLeg_L_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 5 10 11 10 18 10 25 10;
createNode animCurveTA -n "Maugli_IKLegHeel_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegHeel_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -3.1805546814635168e-015 5 0 11 0 18 
		0 25 -3.1805546814635168e-015;
createNode animCurveTA -n "Maugli_IKLegHeel_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTL -n "Maugli_PoleLeg_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Maugli_PoleLeg_L_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Maugli_PoleLeg_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 25 5 25 11 25 18 25 25 25;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_toe";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "Maugli_IKLeg_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -5.0105185448650458 5 -5.0105185448650458 
		11 -8.8266462208277883 18 -5.0105185448650458 25 -5.0105185448650458;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "Maugli_IKLeg_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -6.3694432300697281 5 -6.3694432300697281 
		11 -8.8306158056525117 18 -6.3694432300697281 25 -6.3694432300697281;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "Maugli_IKLeg_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 13.378201002477269 5 -6.0790648459002696 
		11 2.1076037965432279 18 13.378201002477269 25 13.378201002477269;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "Maugli_IKLeg_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.069000150376690925 5 -0.026479309327680566 
		11 0.10035113115621315 18 0.069000150376690925 25 0.069000150376690925;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "Maugli_IKLeg_L_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.015303353529604964 5 -0.12618527050224299 
		11 -0.083035505861347322 18 -0.015303353529604964 25 -0.015303353529604964;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "Maugli_IKLeg_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.16760982461393598 5 0.099667320438897811 
		11 0.18798576294351738 18 0.16760982461393598 25 0.16760982461393598;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "Maugli_FKIKArm_L_Man_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKArm_L_Man_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKArm_L_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 5 10 11 10 18 10 25 10;
createNode animCurveTU -n "Maugli_PoleArm_L_Man_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 10 25 10;
createNode animCurveTL -n "Maugli_PoleArm_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.30187358991198376 25 0.30187358991198376;
createNode animCurveTL -n "Maugli_PoleArm_L_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.67336977492758876 25 -0.67336977492758876;
createNode animCurveTL -n "Maugli_PoleArm_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.052664568395363105 25 -0.052664568395363105;
createNode animCurveTU -n "Maugli_IKArm_L_Man_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 11 1 25 1;
	setAttr -s 3 ".kit[0:2]"  3 10 10;
	setAttr -s 3 ".kot[0:2]"  3 10 10;
createNode animCurveTU -n "Maugli_IKArm_L_Man_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 11 1 25 1;
	setAttr -s 3 ".kit[0:2]"  3 10 10;
	setAttr -s 3 ".kot[0:2]"  3 10 10;
createNode animCurveTU -n "Maugli_IKArm_L_Man_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 11 0 25 0;
	setAttr -s 3 ".kit[0:2]"  3 10 10;
	setAttr -s 3 ".kot[0:2]"  3 10 10;
createNode animCurveTU -n "Maugli_IKArm_L_Man_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 11 0 25 0;
	setAttr -s 3 ".kit[0:2]"  3 10 10;
	setAttr -s 3 ".kot[0:2]"  3 10 10;
createNode animCurveTU -n "Maugli_IKArm_L_Man_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 11 0 25 0;
	setAttr -s 3 ".kit[0:2]"  3 10 10;
	setAttr -s 3 ".kot[0:2]"  3 10 10;
createNode animCurveTA -n "Maugli_IKArm_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -84.941336550094036 5 -94.149553026797406 
		11 -101.79573467785826 18 -83.069074694304433 25 -84.941336550094036;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "Maugli_IKArm_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 19.351892783302421 5 19.559149272944605 
		11 20.240534876198339 18 29.552602039967837 25 19.351892783302421;
	setAttr -s 5 ".kit[0:4]"  3 10 1 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 1 10 3;
	setAttr -s 5 ".kix[2:4]"  0.99859529733657837 0.99944812059402466 
		1;
	setAttr -s 5 ".kiy[2:4]"  0.052985608577728271 -0.033216796815395355 
		0;
	setAttr -s 5 ".kox[2:4]"  0.99859529733657837 0.99944812059402466 
		1;
	setAttr -s 5 ".koy[2:4]"  0.052985608577728271 -0.033216796815395355 
		0;
createNode animCurveTA -n "Maugli_IKArm_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -23.456909615172744 5 3.7271009545859597 
		11 34.74140189392547 18 -12.761707017723062 25 -23.456909615172744;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTL -n "Maugli_IKArm_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.71087397470952018 5 -1.1774536973959635 
		11 -1.7061219516498909 18 -0.91526073321641099 25 -0.71087397470952018;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTL -n "Maugli_IKArm_L_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.7597179554642883 5 -1.9069135080944615 
		11 -1.9772913019290594 18 -1.7443561324481338 25 -1.7597179554642883;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "Maugli_IKArm_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.1306425046017448 5 -1.1343806279419053 
		11 -1.0989906273137837 18 -1.110349779751187 25 -1.1306425046017448;
	setAttr -s 5 ".kit[0:4]"  3 10 10 9 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 9 10;
createNode animCurveTU -n "Maugli_Fingers_R_Man_MiddleFingerCurl";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTU -n "Maugli_FKIKSpine_M_Man_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKSpine_M_Man_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKSpine_M_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegBall_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegToe_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -7.0622500768802538e-031 5 0 11 0 18 
		0 25 -7.0622500768802538e-031;
createNode animCurveTA -n "Maugli_IKLegToe_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 3.1805546814635168e-015 5 0 11 0 18 0 
		25 3.1805546814635168e-015;
createNode animCurveTA -n "Maugli_IKLegToe_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegHeel_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegHeel_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 3.1805546814635168e-015 5 0 11 0 18 0 
		25 3.1805546814635168e-015;
createNode animCurveTA -n "Maugli_IKLegHeel_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTU -n "Maugli_FKIKLeg_R_Man_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLeg_R_Man_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLeg_R_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 5 10 11 10 18 10 25 10;
createNode animCurveTL -n "Maugli_PoleLeg_R_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTL -n "Maugli_PoleLeg_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTL -n "Maugli_PoleLeg_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 25 5 25 11 25 18 25 25 25;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_toe";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "Maugli_IKLeg_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 11.511562366554475 11 -8.8355367665149789 
		18 0 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "Maugli_IKLeg_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 -3.6207040252915346 11 3.284912121517114 
		18 0 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "Maugli_IKLeg_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 1.0757301985180805 11 -2.0276562387949393 
		18 0 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "Maugli_IKLeg_R_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 -0.077455888528157615 11 0.029196538152977968 
		18 0 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "Maugli_IKLeg_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 -0.17237417960538462 11 0.03280985536340289 
		18 0 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "Maugli_IKLeg_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0.077099844190001238 11 -0.15533175456498813 
		18 0 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "Maugli_FKIKArm_R_Man_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKArm_R_Man_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKArm_R_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 5 10 11 10 18 10 25 10;
createNode animCurveTU -n "Maugli_PoleArm_R_Man_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 10 25 10;
createNode animCurveTL -n "Maugli_PoleArm_R_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.16593047685129286 25 0.16593047685129286;
createNode animCurveTL -n "Maugli_PoleArm_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.11674023114788831 25 -0.11674023114788831;
createNode animCurveTL -n "Maugli_PoleArm_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.10282366384186119 25 0.10282366384186119;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -6.2725381128105917e-045 5 0 11 0 18 
		0 25 -6.2725381128105917e-045;
createNode animCurveTU -n "Maugli_IKArm_R_Man_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 5 1 25 1;
createNode animCurveTU -n "Maugli_IKArm_R_Man_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 5 1 25 1;
createNode animCurveTU -n "Maugli_IKArm_R_Man_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 25 0;
createNode animCurveTU -n "Maugli_IKArm_R_Man_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 25 0;
createNode animCurveTU -n "Maugli_IKArm_R_Man_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 25 0;
createNode animCurveTA -n "Maugli_IKArm_R_Man_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -4.8790848169292413 5 -2.8497025445126942 
		11 5.567537991139532 25 -4.8790848169292413;
	setAttr -s 4 ".kit[1:3]"  9 10 3;
	setAttr -s 4 ".kot[1:3]"  9 10 3;
createNode animCurveTA -n "Maugli_IKArm_R_Man_rotateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -54.828555067778908 5 -56.594569212063632 
		11 -53.417930933824394 25 -54.828555067778908;
	setAttr -s 4 ".kit[1:3]"  10 9 1;
	setAttr -s 4 ".kot[1:3]"  10 9 1;
	setAttr -s 4 ".kix[0:3]"  0.99325102567672729 1 0.99893289804458618 
		0.98877096176147461;
	setAttr -s 4 ".kiy[0:3]"  -0.11598449945449829 0 0.046184808015823364 
		-0.14943893253803253;
	setAttr -s 4 ".kox[0:3]"  0.99325102567672729 1 0.99893289804458618 
		0.98877096176147461;
	setAttr -s 4 ".koy[0:3]"  -0.11598444730043411 0 0.046184808015823364 
		-0.14943888783454895;
createNode animCurveTA -n "Maugli_IKArm_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -27.117038477838772 5 -21.818837113000598 
		11 3.9198438891529825 25 -27.117038477838772;
	setAttr -s 4 ".kit[0:3]"  3 10 10 3;
	setAttr -s 4 ".kot[0:3]"  3 10 10 3;
createNode animCurveTL -n "Maugli_IKArm_R_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.24375838155221463 5 -0.30207847311729247 
		11 -0.61408848384575387 18 -0.26163267267839579 25 -0.24375838155221463;
	setAttr -s 5 ".kit[0:4]"  3 10 10 1 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 1 3;
	setAttr -s 5 ".kix[3:4]"  0.99025684595108032 1;
	setAttr -s 5 ".kiy[3:4]"  0.1392529308795929 0;
	setAttr -s 5 ".kox[3:4]"  0.99025684595108032 1;
	setAttr -s 5 ".koy[3:4]"  0.1392529308795929 0;
createNode animCurveTL -n "Maugli_IKArm_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.5675789344441291 5 -0.86576768758096223 
		11 -1.4429476090061431 18 -0.71898562556490719 25 -0.5675789344441291;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTL -n "Maugli_IKArm_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.5348454704179556 5 0.53235922388158585 
		11 0.53319131200802272 18 0.48537413185638179 25 0.5348454704179556;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "Maugli_FKScapula_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 16.010244166512202 25 16.010244166512202;
createNode animCurveTA -n "Maugli_FKScapula_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 14.453583717594759 25 14.453583717594759;
createNode animCurveTA -n "Maugli_FKScapula_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 8.5771851995081878 25 8.5771851995081878;
createNode animCurveTL -n "Maugli_FKScapula_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 25 0;
createNode animCurveTL -n "Maugli_FKScapula_L_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 25 0;
createNode animCurveTL -n "Maugli_FKScapula_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -5.5511151231257827e-017 25 -5.5511151231257827e-017;
createNode animCurveTA -n "Maugli_FKMiddleFinger1_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 17.622819694952526 5 17.622819694952526 
		11 17.622819694952526 18 17.622819694952526 25 17.622819694952526;
createNode animCurveTA -n "Maugli_FKMiddleFinger2_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -23.252905752704581 5 -23.252905752704581 
		11 -23.252905752704581 18 -23.252905752704581 25 -23.252905752704581;
createNode animCurveTA -n "Maugli_FKMiddleFinger3_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_FKThumbFinger1_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -8.9121374222325116 25 -8.9121374222325116;
createNode animCurveTA -n "Maugli_FKThumbFinger1_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 15.368506266811023 25 15.368506266811023;
createNode animCurveTA -n "Maugli_FKThumbFinger1_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -23.424398022041203 25 -23.424398022041203;
createNode animCurveTA -n "Maugli_FKThumbFinger2_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 43.562669387098943 25 43.562669387098943;
createNode animCurveTA -n "Maugli_FKBackA_M_Man_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 31.339401832138403 18 17.998867710533556 
		25 31.339401832138403;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_FKBackA_M_Man_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -12.230132580790263 18 -14.847368459382139 
		25 -12.230132580790263;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_FKBackA_M_Man_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -12.926179688964792 18 -9.7889009256624089 
		25 -12.926179688964792;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_FKBackB_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 7.2569396922509739 11 10.90630094170664 
		18 5.8695028682880386 25 7.2569396922509739;
	setAttr -s 4 ".kit[2:3]"  9 1;
	setAttr -s 4 ".kot[2:3]"  9 1;
	setAttr -s 4 ".kix[3]"  0.97776436805725098;
	setAttr -s 4 ".kiy[3]"  0.20970676839351654;
	setAttr -s 4 ".kox[3]"  0.97678393125534058;
	setAttr -s 4 ".koy[3]"  0.21422736346721649;
createNode animCurveTA -n "Maugli_FKBackB_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1.2968979376576604 11 -0.7793492249970706 
		18 0.10136432765274456 25 1.2968979376576604;
	setAttr -s 4 ".kit[2:3]"  9 10;
	setAttr -s 4 ".kot[2:3]"  9 10;
createNode animCurveTA -n "Maugli_FKBackB_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -2.842118883650758 11 -2.0589288745777359 
		18 -2.4620565959685137 25 -2.842118883650758;
	setAttr -s 4 ".kit[2:3]"  9 10;
	setAttr -s 4 ".kot[2:3]"  9 10;
createNode animCurveTA -n "Maugli_FKChest_M_Man_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -12.142222007810011 11 1.0256543567737479 
		25 -12.142222007810011;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_FKChest_M_Man_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 12.305762111416071 11 8.3225983057640747 
		25 12.305762111416071;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_FKChest_M_Man_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -17.630084171996455 11 -12.52607021943335 
		25 -17.630084171996455;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_FKNeck_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -21.349332740018081 5 -24.57505807443998 
		11 -30.58774873438783 18 -5.0606468145277912 25 -21.349332740018081;
createNode animCurveTA -n "Maugli_FKNeck_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -0.44123125050354439 5 2.7211830119095382 
		11 5.3375077549703738 25 -0.44123125050354439;
createNode animCurveTA -n "Maugli_FKNeck_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 19.641362431357976 5 17.40575342968987 
		11 18.387014836545625 25 19.641362431357976;
createNode animCurveTA -n "Maugli_FKHead_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -17.660014913242996 5 -31.612138814388818 
		11 -30.920947340546348 18 -16.166923847497468 25 -17.660014913242996;
createNode animCurveTA -n "Maugli_FKHead_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 6.3177172652768183 5 5.3555515409105947 
		11 1.7021776080730009 18 1.491820207966972 25 6.3177172652768183;
createNode animCurveTA -n "Maugli_FKHead_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 16.700037308578423 5 15.085801787657767 
		11 18.398017725091066 18 9.3792760609983894 25 16.700037308578423;
createNode animCurveTA -n "Maugli_FKScapula_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 3.234691603003407 25 3.234691603003407;
createNode animCurveTA -n "Maugli_FKScapula_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -4.1984829852594405 25 -4.1984829852594405;
createNode animCurveTA -n "Maugli_FKScapula_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.2882750967306602 25 1.2882750967306602;
createNode animCurveTL -n "Maugli_FKScapula_R_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -2.7755575615628914e-017 25 -2.7755575615628914e-017;
createNode animCurveTL -n "Maugli_FKScapula_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 25 0;
createNode animCurveTL -n "Maugli_FKScapula_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 5.5511151231257827e-017 25 5.5511151231257827e-017;
createNode animCurveTA -n "Maugli_FKMiddleFinger1_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_FKMiddleFinger2_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -67.588216236699324 5 -67.588216236699324 
		11 -67.588216236699324 18 -67.588216236699324 25 -67.588216236699324;
createNode animCurveTA -n "Maugli_FKMiddleFinger3_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -81.669521342510606 5 -81.669521342510606 
		11 -81.669521342510606 18 -81.669521342510606 25 -81.669521342510606;
createNode animCurveTA -n "Maugli_FKThumbFinger1_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 25.665274764482422 5 25.665274764482422 
		11 25.665274764482422 18 25.665274764482422 25 25.665274764482422;
createNode animCurveTA -n "Maugli_FKThumbFinger1_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 36.541774445263137 5 36.541774445263137 
		11 36.541774445263137 18 36.541774445263137 25 36.541774445263137;
createNode animCurveTA -n "Maugli_FKThumbFinger1_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -67.421493922591793 5 -67.421493922591793 
		11 -67.421493922591793 18 -67.421493922591793 25 -67.421493922591793;
createNode animCurveTA -n "Maugli_FKThumbFinger2_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 47.81080993924823 5 47.81080993924823 
		11 47.81080993924823 18 47.81080993924823 25 47.81080993924823;
createNode animCurveTU -n "Maugli_Main_Man_visibility";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_Center_M_CenterBtwFeet";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "Maugli_Center_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "Maugli_Center_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "Maugli_Center_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 14.253673349941334 5 4.9316689984012898 
		11 -22.801686550418776 18 -8.3763675773732746 25 14.253673349941334;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTL -n "Maugli_Center_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0.1255510365552257 11 -0.47499460977007923 
		18 -0.28799010264324254 25 0;
	setAttr -s 5 ".kit[0:4]"  1 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  1 10 10 10 10;
	setAttr -s 5 ".kix[0:4]"  0.68139857053756714 0.61105650663375854 
		0.7234349250793457 0.70082581043243408 0.62952160835266113;
	setAttr -s 5 ".kiy[0:4]"  0.73191261291503906 -0.79158693552017212 
		-0.69039255380630493 0.71333247423171997 0.77698296308517456;
	setAttr -s 5 ".kox[0:4]"  0.68139857053756714 0.61105650663375854 
		0.7234349250793457 0.70082581043243408 0.62952160835266113;
	setAttr -s 5 ".koy[0:4]"  0.73191261291503906 -0.79158693552017212 
		-0.69039255380630493 0.71333247423171997 0.77698296308517456;
createNode animCurveTL -n "Maugli_Center_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0.037764081062773958 11 0.53933296343913972 
		18 0.65528311865927824 25 0;
	setAttr -s 5 ".kit[0:4]"  3 1 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 1 10 10 3;
	setAttr -s 5 ".kix[1:4]"  0.85177195072174072 0.57441389560699463 
		0.65432560443878174 1;
	setAttr -s 5 ".kiy[1:4]"  0.52391284704208374 0.8185650110244751 
		-0.75621294975280762 0;
	setAttr -s 5 ".kox[1:4]"  0.85177189111709595 0.57441389560699463 
		0.65432560443878174 1;
	setAttr -s 5 ".koy[1:4]"  0.52391284704208374 0.8185650110244751 
		-0.75621294975280762 0;
createNode animCurveTL -n "Maugli_Center_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0.018509467089309339 11 0.018509467089309339 
		18 0.018509467089309339 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "Maugli_IKLegBackBall_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTU -n "Maugli_FKIKLegBack_L_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegBack_L_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegBack_L_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 5 10 11 10 18 10 25 10;
createNode animCurveTU -n "Maugli_PoleLegBack_L_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 5 10 11 10 18 10 25 10;
createNode animCurveTL -n "Maugli_PoleLegBack_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0.39348046613702642 18 -0.12862640125606339 
		25 0;
createNode animCurveTL -n "Maugli_PoleLegBack_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 -0.50501219394848984 18 -0.58717996115647086 
		25 0;
createNode animCurveTL -n "Maugli_PoleLegBack_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0.057961199655971463 18 -0.15997689810686394 
		25 0;
createNode animCurveTU -n "Maugli_IKLegBack_L_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
createNode animCurveTU -n "Maugli_IKLegBack_L_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
createNode animCurveTU -n "Maugli_IKLegBack_L_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTU -n "Maugli_IKLegBack_L_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTU -n "Maugli_IKLegBack_L_legAim";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 5 10 11 10 18 10 25 10;
createNode animCurveTU -n "Maugli_IKLegBack_L_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 25 5 25 11 25 18 25 25 25;
createNode animCurveTU -n "Maugli_IKLegBack_L_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTU -n "Maugli_IKLegBack_L_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegBack_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegBack_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegBack_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 120.25945944718168 5 -34.951716991152459 
		9 -44.028807080479574 11 0 18 0 22 120.48220846781126 25 120.25945944718168;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKLegBack_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.96308895096482727 5 0.39096112830088658 
		9 0.011537468793705763 11 0 18 0 22 0.49087538550062676 25 0.96308895096482727;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "Maugli_IKLegBack_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.75305475314980841 5 -1.7377323202881514 
		9 -1.7107056724675844 11 -1.1874261635941299 18 0.90132902250832769 22 0.96863410254052074 
		25 0.75305475314980841;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 9 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 9 3;
createNode animCurveTL -n "Maugli_IKLegBack_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0.284013866514149 11 0.284013866514149 
		18 0.284013866514149 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTL -n "Maugli_BendNeck_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTL -n "Maugli_BendNeck_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTL -n "Maugli_BendNeck_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTU -n "Maugli_FKIKSpine_M_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKSpine_M_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKSpine_M_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegBackBall_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTU -n "Maugli_FKIKLegBack_R_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegBack_R_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegBack_R_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 5 10 11 10 18 10 25 10;
createNode animCurveTU -n "Maugli_PoleLegBack_R_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 5 10 11 10 18 10 25 10;
	setAttr -s 5 ".kit[1:4]"  3 10 10 3;
	setAttr -s 5 ".kot[1:4]"  3 10 10 3;
createNode animCurveTL -n "Maugli_PoleLegBack_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -2.2204460492503131e-016 5 0.022025504873787353 
		11 0.68794038631126708 18 0.68730711518251408 25 -2.2204460492503131e-016;
	setAttr -s 5 ".kit[1:4]"  3 10 10 3;
	setAttr -s 5 ".kot[1:4]"  3 10 10 3;
createNode animCurveTL -n "Maugli_PoleLegBack_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 -0.008661384239948661 11 -0.73267660558050585 
		18 -0.69822747861569046 25 0;
	setAttr -s 5 ".kit[1:4]"  3 10 10 3;
	setAttr -s 5 ".kot[1:4]"  3 10 10 3;
createNode animCurveTL -n "Maugli_PoleLegBack_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -5.5511151231257827e-017 5 0.13140656781209989 
		11 0.024434323400477999 18 0.091169761182720702 25 -5.5511151231257827e-017;
	setAttr -s 5 ".kit[1:4]"  3 10 10 3;
	setAttr -s 5 ".kot[1:4]"  3 10 10 3;
createNode animCurveTU -n "Maugli_IKLegBack_R_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
createNode animCurveTU -n "Maugli_IKLegBack_R_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
createNode animCurveTU -n "Maugli_IKLegBack_R_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTU -n "Maugli_IKLegBack_R_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTU -n "Maugli_IKLegBack_R_legAim";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 5 10 11 10 18 10 25 10;
createNode animCurveTU -n "Maugli_IKLegBack_R_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 25 5 25 11 25 18 25 25 25;
createNode animCurveTU -n "Maugli_IKLegBack_R_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTU -n "Maugli_IKLegBack_R_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegBack_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -17.042137663821418 5 -17.042137663821421 
		11 -5.5854450873865824 18 -5.5854450873865824 25 -17.042137663821418;
	setAttr -s 5 ".kit[4]"  3;
	setAttr -s 5 ".kot[4]"  3;
createNode animCurveTA -n "Maugli_IKLegBack_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.6633143465433158e-015 5 0 11 2.4102382750376243 
		18 2.4102382750376243 25 1.6633143465433158e-015;
createNode animCurveTA -n "Maugli_IKLegBack_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 105.66538207304833 5 87.314757726824055 
		11 -25.627731501423433 15 -32.6046250527423 18 0 22 0 23 75.304619889553067 25 105.66538207304833;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 3;
createNode animCurveTL -n "Maugli_IKLegBack_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1.4622462724835834 5 0.95677189159265785 
		11 0.39286229633116054 18 0 22 0 25 1.4622462724835834;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 3;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 3;
createNode animCurveTL -n "Maugli_IKLegBack_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.86611225864017405 5 -0.18089901161847277 
		11 -0.84008946778119342 15 -1.0815717806890122 18 -0.60996546443034383 22 0.33411094805158903 
		23 0.51882111393462305 25 0.86611225864017405;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 3;
createNode animCurveTL -n "Maugli_IKLegBack_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.16279811825569085 5 -0.26716290487623168 
		11 -0.28564064691870478 18 -0.28564064691870478 25 0.16279811825569085;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTU -n "Maugli_FKIKSplineTail_M_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKSplineTail_M_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKSplineTail_M_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 5 10 11 10 18 10 25 10;
createNode animCurveTU -n "Maugli_WagCurveSplineTail_M_increment";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
createNode animCurveTU -n "Maugli_WagCurveSplineTail_M_multiply";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
createNode animCurveTU -n "Maugli_WagCurveSplineTail_M_timeOffset";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
createNode animCurveTU -n "Maugli_WagCurveSplineTail_M_enable";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTA -n "Maugli_WagCurveSplineTail_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_WagCurveSplineTail_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_WagCurveSplineTail_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTU -n "Maugli_IKSplineTail2_M_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 5 0 11 0 25 0;
createNode animCurveTU -n "Maugli_IKSplineTail2_M_twist";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 5 0 11 0 25 0;
createNode animCurveTU -n "Maugli_IKSplineTail2_M_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 5 0 11 0 25 0;
createNode animCurveTL -n "Maugli_IKSplineTail2_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.50156583028862078 5 1.0476674715998813 
		11 1.11387017227468 18 0.19807271590457454 25 0.50156583028862078;
	setAttr -s 5 ".kit[0:4]"  1 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  1 10 10 10 1;
	setAttr -s 5 ".kix[0:4]"  0.42902287840843201 0.51375794410705566 
		0.45435935258865356 0.60616570711135864 0.41591030359268188;
	setAttr -s 5 ".kiy[0:4]"  0.90329360961914063 0.85793513059616089 
		-0.89081841707229614 -0.79533839225769043 0.90940564870834351;
	setAttr -s 5 ".kox[0:4]"  0.42902275919914246 0.51375794410705566 
		0.45435935258865356 0.60616570711135864 0.4127424955368042;
	setAttr -s 5 ".koy[0:4]"  0.9032936692237854 0.85793513059616089 
		-0.89081841707229614 -0.79533839225769043 0.91084778308868408;
createNode animCurveTL -n "Maugli_IKSplineTail2_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0.018045216813981302 11 0.51961409919034707 
		18 0.82312433966389653 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 1 10 3;
	setAttr -s 5 ".kix[2:4]"  0.34891492128372192 0.66818434000015259 
		1;
	setAttr -s 5 ".kiy[2:4]"  0.93715447187423706 -0.7439957857131958 
		0;
	setAttr -s 5 ".kox[2:4]"  0.34891489148139954 0.66818434000015259 
		1;
	setAttr -s 5 ".koy[2:4]"  0.93715441226959229 -0.7439957857131958 
		0;
createNode animCurveTL -n "Maugli_IKSplineTail2_M_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.39341763880761793 5 0.061652030397291391 
		11 -0.56490744744536525 25 0.39341763880761793;
	setAttr -s 4 ".kit[1:3]"  10 1 3;
	setAttr -s 4 ".kot[1:3]"  10 1 3;
	setAttr -s 4 ".kix[2:3]"  0.91209578514099121 1;
	setAttr -s 4 ".kiy[2:3]"  -0.4099772572517395 0;
	setAttr -s 4 ".kox[2:3]"  0.91209578514099121 1;
	setAttr -s 4 ".koy[2:3]"  -0.40997728705406189 0;
createNode animCurveTU -n "Maugli_IKSplineTail1_M_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTL -n "Maugli_IKSplineTail1_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.82001054947299123 5 1.1620306701115737 
		11 -0.095820642709593118 18 -0.47451324759600944 25 0.82001054947299123;
	setAttr -s 5 ".kit[0:4]"  1 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  1 10 10 10 1;
	setAttr -s 5 ".kix[0:4]"  0.2046714723110199 0.37168270349502563 
		0.25596463680267334 0.45401158928871155 0.13899789750576019;
	setAttr -s 5 ".kiy[0:4]"  0.97883069515228271 -0.92835986614227295 
		-0.9666861891746521 0.89099574089050293 0.99029272794723511;
	setAttr -s 5 ".kox[0:4]"  0.21219964325428009 0.37168270349502563 
		0.25596463680267334 0.45401158928871155 0.13703331351280212;
	setAttr -s 5 ".koy[0:4]"  0.9772263765335083 -0.92835986614227295 
		-0.9666861891746521 0.89099574089050293 0.9905664324760437;
createNode animCurveTL -n "Maugli_IKSplineTail1_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 -0.013180267080266983 11 0.58769266630829642 
		18 0.6555984061444895 25 0;
	setAttr -s 5 ".kit[0:4]"  9 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  9 10 10 10 3;
createNode animCurveTL -n "Maugli_IKSplineTail1_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 -0.16831497683779376 11 -0.018898517836500872 
		18 0.152716087001871 25 0;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_FKRump_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -18.638044314952673 5 -18.638044314952673 
		11 -23.735635520858633 18 -4.4734291043126948 25 -18.638044314952673;
createNode animCurveTA -n "Maugli_FKRump_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 5.9273289705481567 5 5.9273289705481567 
		11 6.9801773807865732 18 2.7639243040724106 25 5.9273289705481567;
createNode animCurveTA -n "Maugli_FKRump_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 12.021048230974857 5 12.021048230974857 
		11 11.447675161064303 18 13.100220041775998 25 12.021048230974857;
createNode animCurveTL -n "Maugli_FKRump_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -5.5511151231257827e-017 5 0 11 0 18 
		0 25 -5.5511151231257827e-017;
createNode animCurveTL -n "Maugli_FKRump_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 2.2204460492503131e-016 5 0 11 0 18 0 
		25 2.2204460492503131e-016;
createNode animCurveTL -n "Maugli_FKRump_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 2.2204460492503131e-016 5 0 11 0 18 0 
		25 2.2204460492503131e-016;
createNode animCurveTA -n "Maugli_FKRump_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -18.710504463926263 5 -18.710504463926263 
		11 -39.885615743024815 18 -39.885615743024815 22 -11.777743568425821 25 -18.710504463926263;
createNode animCurveTA -n "Maugli_FKRump_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 8.2582530676151027 5 8.2582530676151027 
		11 6.9300548207531385 18 6.9300548207531385 22 5.9820557748298553 25 8.2582530676151027;
createNode animCurveTA -n "Maugli_FKRump_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 5.1050521316126698 5 5.1050521316126698 
		11 3.2852683281666923 18 3.2852683281666923 22 6.5844581166610849 25 5.1050521316126698;
createNode animCurveTL -n "Maugli_FKRump_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 5.5511151231257827e-017 5 0 11 0 18 0 
		22 3.3662744892292704e-017 25 5.5511151231257827e-017;
createNode animCurveTL -n "Maugli_FKRump_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 5 0 11 0 18 0 22 0 25 0;
createNode animCurveTL -n "Maugli_FKRump_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 5 0 11 0 18 0 22 0 25 0;
createNode animCurveTA -n "Maugli_FKBackA_M_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -6.1344158462123248 5 5.4609425005607797 
		11 5.4609425005607797 18 -3.5618237532738517 25 -6.1344158462123248;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 10;
	setAttr -s 5 ".kot[0:4]"  3 9 9 9 10;
createNode animCurveTA -n "Maugli_FKBackA_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -2.6442010631261756 5 -2.6473542951928555 
		11 -2.6473542951928555 18 -2.6542776215079567 25 -2.6442010631261756;
	setAttr -s 5 ".kit[1:4]"  9 9 10 10;
	setAttr -s 5 ".kot[1:4]"  9 9 10 10;
createNode animCurveTA -n "Maugli_FKBackA_M_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.28408691297585409 5 -0.25299827030297789 
		11 -0.25299827030297789 18 0.16515797247982719 25 0.28408691297585409;
	setAttr -s 5 ".kit[0:4]"  10 9 9 9 10;
	setAttr -s 5 ".kot[0:4]"  10 9 9 9 10;
createNode animCurveTA -n "Maugli_FKBackB_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 18.274175359197418 11 28.543919633667738 
		18 8.016818966408664 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTA -n "Maugli_FKBackB_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "Maugli_FKBackB_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "Maugli_FKChest_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 -25.839134892527184 11 12.954954504655602 
		18 4.1608465492745843 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTA -n "Maugli_FKChest_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_FKChest_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_FKNeck_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 24.862696821213692 5 46.797141378895198 
		11 16.351935907811125 18 12.371265407042854 25 24.862696821213692;
	setAttr -s 5 ".kit[0:4]"  9 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  9 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.40380671620368958;
	setAttr -s 5 ".kiy[4]"  0.9148443341255188;
	setAttr -s 5 ".kox[4]"  0.40121603012084961;
	setAttr -s 5 ".koy[4]"  0.91598343849182129;
createNode animCurveTA -n "Maugli_FKNeck_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "Maugli_FKNeck_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "Maugli_FKHead_M_Global";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 5 10 11 10 18 10 25 10;
createNode animCurveTA -n "Maugli_FKHead_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -10.280351451802797 5 -10.917811927254361 
		11 7.9740026795900789 18 7.9740026795900789 25 -10.280351451802797;
	setAttr -s 5 ".kit[4]"  3;
	setAttr -s 5 ".kot[4]"  3;
createNode animCurveTA -n "Maugli_FKHead_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -6.477995107503193 5 0.74548512078777585 
		11 0.74548512078777585 18 0.74548512078777585 25 -6.477995107503193;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTA -n "Maugli_FKHead_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -3.6805445729346604 5 -2.014502516692271 
		11 -2.014502516692271 18 -2.014502516692271 25 -3.6805445729346604;
createNode animCurveTU -n "Maugli_Main_scaleZ";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 25 1;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTU -n "Maugli_Main_scaleY";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 25 1;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTU -n "Maugli_Main_scaleX";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 25 1;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "Maugli_Main_rotateZ";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 25 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "Maugli_Main_rotateY";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 25 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "Maugli_Main_rotateX";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 25 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTL -n "Maugli_Main_translateZ";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 25 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTL -n "Maugli_Main_translateY";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 25 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTL -n "Maugli_Main_translateX";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 25 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTU -n "Maugli_Main_visibility";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 25 1;
	setAttr -s 2 ".kit[1]"  9;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTA -n "Maugli_kolchan_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -16.498609615445837 5 -15.127377165571444 
		11 19.118432944495154 18 -26.946975021075406 25 -16.498609615445837;
	setAttr -s 5 ".kit[0:4]"  3 9 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 9 10 10 3;
createNode animCurveTA -n "Maugli_kolchan_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -6.4006181765439756 5 0.73744076242289502 
		11 -21.553112309788723 18 3.5424856267698104 25 -6.4006181765439756;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTA -n "Maugli_kolchan_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.8111494521402616 5 2.6450976196736593 
		11 -17.984552953700657 18 -11.843538840160512 25 1.8111494521402616;
	setAttr -s 5 ".kit[0:4]"  1 9 10 10 10;
	setAttr -s 5 ".kot[0:4]"  1 9 10 10 10;
	setAttr -s 5 ".kix[0:4]"  0.9406774640083313 0.72780150175094604 
		0.86369508504867554 0.80370444059371948 0.69959264993667603;
	setAttr -s 5 ".kiy[0:4]"  0.33930215239524841 -0.6857878565788269 
		-0.50401473045349121 0.59502869844436646 0.71454185247421265;
	setAttr -s 5 ".kox[0:4]"  0.9406774640083313 0.72780150175094604 
		0.86369508504867554 0.80370444059371948 0.6995927095413208;
	setAttr -s 5 ".koy[0:4]"  0.33930209279060364 -0.6857878565788269 
		-0.50401473045349121 0.59502869844436646 0.71454191207885742;
createNode animCurveTA -n "Maugli_yashik_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 5 0 11 29.621478182895672 15 -7.1219833064217486 
		18 0 25 0;
createNode animCurveTA -n "Maugli_yashik_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_yashik_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 5 0 11 11.631814225762275 15 -11.278486553274492 
		18 0 25 0;
createNode animCurveTL -n "Maugli_yashik_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTL -n "Maugli_yashik_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 5 0 11 -0.34373948848939084 15 -0.040267658376325052 
		18 0 25 0;
	setAttr -s 6 ".kit[3:5]"  9 10 10;
	setAttr -s 6 ".kot[3:5]"  9 10 10;
createNode animCurveTL -n "Maugli_yashik_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 5 0 11 0.14450668221523266 15 0.020293515595326637 
		18 0 25 0;
	setAttr -s 6 ".kit[3:5]"  9 10 10;
	setAttr -s 6 ".kot[3:5]"  9 10 10;
createNode animCurveTA -n "Maugli_l_ear_control_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -13.930813049671032 25 -13.930813049671032;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "Maugli_l_ear_control_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -33.163858461841365 25 -33.163858461841365;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "Maugli_l_ear_control_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 76.592706690898311 25 76.592706690898311;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "Maugli_r_ear_control1_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -13.924689998798502 25 -13.924689998798502;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "Maugli_r_ear_control1_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 26.777110246701266 25 26.777110246701266;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "Maugli_r_ear_control1_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -76.966651924884573 25 -76.966651924884573;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "Maugli_jaw_C_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 11 8.5012343717822159 25 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_spear_control_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_spear_control_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_spear_control_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTL -n "Maugli_spear_control_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.041982630251665931 5 0.041982630251665931 
		11 0.041982630251665931 18 0.041982630251665931 25 0.041982630251665931;
createNode animCurveTL -n "Maugli_spear_control_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.05682005777595385 5 -0.05682005777595385 
		11 -0.05682005777595385 18 -0.05682005777595385 25 -0.05682005777595385;
createNode animCurveTL -n "Maugli_spear_control_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.19304667407551657 5 0.19304667407551657 
		11 0.19304667407551657 18 0.19304667407551657 25 0.19304667407551657;
createNode animCurveTU -n "Maugli_spear_control_World_Hands";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTA -n "Maugli_IKLegFrontBall_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegFrontBall_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.1 5 1.1 11 1.1 18 1.1 25 1.1;
createNode animCurveTU -n "Maugli_IKLegFront_R_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.1 5 1.1 11 1.1 18 1.1 25 1.1;
createNode animCurveTU -n "Maugli_IKLegFront_R_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_legAim";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 5 10 11 10 18 10 25 10;
createNode animCurveTU -n "Maugli_IKLegFront_R_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 25 5 25 11 25 18 25 25 25;
createNode animCurveTU -n "Maugli_IKLegFront_R_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegFront_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 13.452853449395946 5 13.452853449395946 
		11 13.452853449395946 14 -23.385297421646268 18 13.452853449395946 25 13.452853449395946;
createNode animCurveTA -n "Maugli_IKLegFront_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 5 0 11 0 14 -6.7939930629960443 18 
		0 25 0;
createNode animCurveTA -n "Maugli_IKLegFront_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -49.030994147612226 3 -43.329676846058923 
		5 0 11 0 14 86.518056986061552 18 72.981179264712097 25 -49.030994147612226;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "Maugli_IKLegFront_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.6220354511696512 3 0.021330647641493283 
		5 0 11 0 18 0.67247496039546228 25 0.6220354511696512;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 3;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 3;
createNode animCurveTL -n "Maugli_IKLegFront_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -1.6310299622119784 5 -0.86950492642579191 
		11 1.3348230529098049 14 1.9870271889886262 18 0.065641382506331336 25 -1.6310299622119784;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 3;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 3;
createNode animCurveTL -n "Maugli_IKLegFront_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.21789294892402367 5 0.21789294892402367 
		11 0.21789294892402367 14 0.3162599861368518 18 0.21789294892402367 25 0.21789294892402367;
createNode animCurveTU -n "Maugli_IKLegFront_L_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.1 5 1.1 11 1.1 18 1.1 25 1.1;
createNode animCurveTU -n "Maugli_IKLegFront_L_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.1 5 1.1 11 1.1 18 1.1 25 1.1;
createNode animCurveTU -n "Maugli_IKLegFront_L_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTU -n "Maugli_IKLegFront_L_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTU -n "Maugli_IKLegFront_L_legAim";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 5 10 11 10 18 10 25 10;
createNode animCurveTU -n "Maugli_IKLegFront_L_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 25 5 25 11 25 18 25 25 25;
createNode animCurveTU -n "Maugli_IKLegFront_L_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTU -n "Maugli_IKLegFront_L_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegFront_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -4.3689304491953465 5 -4.3689304491953465 
		11 -4.3689304491953465 18 -4.3689304491953802 25 -4.3689304491953465;
createNode animCurveTA -n "Maugli_IKLegFront_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_IKLegFront_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 102.88572227693426 11 98.537216647069329 
		18 16.4315459823077 23 -23.412203591963056 25 0;
	setAttr -s 7 ".kit[6]"  3;
	setAttr -s 7 ".kot[6]"  3;
createNode animCurveTL -n "Maugli_IKLegFront_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 5 0 8 0.29444144675195172 11 0.3046555573810823 
		18 0.95369233806486164 23 0.18134234807788518 25 0;
	setAttr -s 7 ".kit[6]"  3;
	setAttr -s 7 ".kot[6]"  3;
createNode animCurveTL -n "Maugli_IKLegFront_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -1.0172215739306112 5 1.4253146218479933 
		8 1.9099747497010837 11 1.3568349436465426 18 -0.94801562546244789 23 -1.187252684955856 
		25 -1.0172215739306112;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kix[0:6]"  0.1678348183631897 0.090723998844623566 
		0.94607895612716675 0.11584680527448654 0.15531922876834869 0.95871955156326294 0.17547973990440369;
	setAttr -s 7 ".kiy[0:6]"  0.98581510782241821 0.99587607383728027 
		-0.32393589615821838 -0.99326711893081665 -0.98786437511444092 -0.28435331583023071 
		0.98448306322097778;
	setAttr -s 7 ".kox[0:6]"  0.16061185300350189 0.090723998844623566 
		0.94607895612716675 0.11584680527448654 0.15531922876834869 0.95871955156326294 0.17432919144630432;
	setAttr -s 7 ".koy[0:6]"  0.98701763153076172 0.99587607383728027 
		-0.32393589615821838 -0.99326711893081665 -0.98786437511444092 -0.28435331583023071 
		0.9846874475479126;
createNode animCurveTL -n "Maugli_IKLegFront_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.32739578435433486 5 -0.32739578435433475 
		11 -0.32739578435433475 18 -0.32739578435432909 25 -0.32739578435433486;
createNode animCurveTU -n "Maugli_FKIKLegFront_L_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegFront_L_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegFront_L_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 5 10 11 10 18 10 25 10;
createNode animCurveTU -n "Maugli_FKIKLegFront_R_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegFront_R_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegFront_R_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 5 10 11 10 18 10 25 10;
createNode animCurveTA -n "Maugli_FKScapula_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_FKScapula_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_FKScapula_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTL -n "Maugli_FKScapula_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -2.2204460492503131e-016 5 0 11 0 18 
		0 25 -2.2204460492503131e-016;
createNode animCurveTL -n "Maugli_FKScapula_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.1102230246251565e-016 5 0 11 0 18 
		0 25 -1.1102230246251565e-016;
createNode animCurveTL -n "Maugli_FKScapula_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 4.4408920985006262e-016 5 0 11 0 18 0 
		25 4.4408920985006262e-016;
createNode animCurveTA -n "Maugli_FKScapula_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_FKScapula_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "Maugli_FKScapula_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTL -n "Maugli_FKScapula_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.1102230246251565e-016 5 0 11 0 18 
		0 25 -1.1102230246251565e-016;
createNode animCurveTL -n "Maugli_FKScapula_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -2.2204460492503131e-016 5 0 11 0 18 
		0 25 -2.2204460492503131e-016;
createNode animCurveTL -n "Maugli_FKScapula_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -2.2204460492503131e-016 5 0 11 0 18 
		0 25 -2.2204460492503131e-016;
createNode animCurveTU -n "Maugli_PoleLegFront_L_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 5 10 11 10 18 10 25 10;
createNode animCurveTL -n "Maugli_PoleLegFront_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.41598215137401412 5 -0.60030286769351349 
		11 -0.83417084032616795 18 0.67891948525556323 25 0.41598215137401412;
createNode animCurveTL -n "Maugli_PoleLegFront_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.023081803484815026 5 -0.41622999698701812 
		11 -0.353182489172431 18 -0.44045424823885176 25 0.023081803484815026;
createNode animCurveTL -n "Maugli_PoleLegFront_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.022989116006067845 5 0.18850283815218338 
		11 0.26890867599629342 18 0.10496003145038227 25 -0.022989116006067845;
createNode animCurveTU -n "Maugli_PoleLegFront_R_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 5 10 11 10 18 10 25 10;
createNode animCurveTL -n "Maugli_PoleLegFront_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.31678960075780738 5 0.001087213673614318 
		11 -0.72721254445166184 18 0.23489491292968212 25 0.31678960075780738;
createNode animCurveTL -n "Maugli_PoleLegFront_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.11971028970415042 5 -0.36076753022288827 
		11 -0.21956587349982767 18 -0.1776661028598312 25 -0.11971028970415042;
createNode animCurveTL -n "Maugli_PoleLegFront_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.0005730959429199018 5 -0.1334853668438811 
		11 -0.11611813656064242 18 0.024111224822120476 25 0.0005730959429199018;
createNode animCurveTL -n "curve1_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTL -n "curve1_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTL -n "curve1_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTU -n "curve1_visibility";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
	setAttr -s 5 ".kot[0:4]"  5 5 5 5 5;
createNode animCurveTA -n "curve1_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "curve1_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "curve1_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTU -n "curve1_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
createNode animCurveTU -n "curve1_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
createNode animCurveTU -n "curve1_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
createNode animCurveTA -n "IKLegBackBall_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 4 0 8 0 12 0;
createNode animCurveTA -n "IKLegBackBall_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 4 0 8 0 12 0;
createNode animCurveTA -n "IKLegBackBall_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 4 0 8 0 12 0;
createNode animCurveTA -n "IKLegBackBall_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 4 0 8 0 12 0;
createNode animCurveTA -n "IKLegFrontBall_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 4 0 8 0 12 0;
createNode animCurveTA -n "IKLegFrontBall_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 4 0 8 0 12 0;
createNode animCurveTA -n "IKLegFrontBall_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 4 0 8 0 12 0;
createNode animCurveTA -n "IKLegFrontBall_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 4 0 8 0 12 0;
createNode animCurveTL -n "IKXSplineTailCurve_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 4.0142992214232583e-036 5 0 11 0 18 0 
		25 4.0142992214232583e-036;
createNode animCurveTL -n "IKXSplineTailCurve_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTL -n "IKXSplineTailCurve_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 11 0 18 0 25 0;
createNode animCurveTA -n "IKXSplineTailCurve_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.272221872585407e-014 5 0 11 0 18 0 
		25 -1.272221872585407e-014;
createNode animCurveTA -n "IKXSplineTailCurve_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.2722218725854067e-014 5 0 11 0 18 0 
		25 1.2722218725854067e-014;
createNode animCurveTA -n "IKXSplineTailCurve_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 2.8249000307521015e-030 5 0 11 0 18 0 
		25 2.8249000307521015e-030;
createNode animCurveTU -n "IKXSplineTailCurve_M_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
createNode animCurveTU -n "IKXSplineTailCurve_M_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
createNode animCurveTU -n "IKXSplineTailCurve_M_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 11 1 18 1 25 1;
createNode animCurveTA -n "IKLegBall_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 4 0 8 0 12 0;
createNode animCurveTA -n "IKLegBall_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 4 0 8 0 12 0;
createNode animCurveTA -n "IKLegBall_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 4 0 8 0 12 0;
createNode animCurveTA -n "IKLegBall_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 4 0 8 0 12 0;
createNode lightLinker -n "lightLinker3";
	setAttr -s 7 ".lnk";
	setAttr -s 7 ".slnk";
select -ne :time1;
	setAttr -av -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 25;
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
connectAttr "moveSource.cl" "clipLibrary1.sc[0]";
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
// End of move.ma
