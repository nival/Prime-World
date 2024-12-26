//Maya ASCII 2008 scene
//Name: blocked.ma
//Last modified: Thu, Jan 28, 2010 04:02:01 PM
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
createNode animClip -n "blockedSource";
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
	setAttr ".se" 24;
	setAttr ".ci" no;
createNode animCurveTU -n "Maugli_Center_M_Man_CenterBtwFeet";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_Center_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_Center_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_Center_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 19.169926907525088 6 -5.7815246828733144 
		10 17.596261283209969 14 4.0494833724385515 18 4.0494833724385515 24 4.0494833724385515;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.99662256240844727 0.84095621109008789 
		1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 -0.082118645310401917 0.54110318422317505 
		0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.99662256240844727 0.84095621109008789 
		1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 -0.082118645310401917 0.54110318422317505 
		0 0 0;
createNode animCurveTL -n "Maugli_Center_M_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0.40595533432892233 14 0 18 
		0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_Center_M_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 -0.35209508223216496 14 0 18 
		0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_Center_M_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0.03987534071874306 14 0 18 
		0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_Fingers_L_Man_MiddleFingerCurl";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 4.6 6 1.6192000592231732 10 0 14 0 18 
		0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.072274267673492432 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 -0.99738478660583496 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.072274267673492432 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 -0.99738478660583496 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegBall_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegToe_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegToe_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 3.1805546814635168e-015 6 3.1805546814635168e-015 
		10 3.1805546814635168e-015 14 3.1805546814635168e-015 18 3.1805546814635168e-015 
		24 3.1805546814635168e-015;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegToe_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKLeg_L_Man_IKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKLeg_L_Man_FKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKLeg_L_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 10 6 10 10 10 14 10 18 10 24 10;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegHeel_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegHeel_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -3.1805546814635168e-015 6 -3.1805546814635168e-015 
		10 -3.1805546814635168e-015 14 -3.1805546814635168e-015 18 -3.1805546814635168e-015 
		24 -3.1805546814635168e-015;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegHeel_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_PoleLeg_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
createNode animCurveTL -n "Maugli_PoleLeg_L_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
createNode animCurveTL -n "Maugli_PoleLeg_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 25 6 25 10 25 14 25 18 25 24 25;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_toe";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLeg_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -5.0105185448650458 6 -5.0105185448650458 
		10 -5.0105185448650458 14 -5.0105185448650458 18 -5.0105185448650458 24 -5.0105185448650458;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLeg_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -6.3694432300697281 6 -6.3694432300697281 
		10 -6.3694432300697281 14 -6.3694432300697281 18 -6.3694432300697281 24 -6.3694432300697281;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLeg_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 13.378201002477269 6 13.378201002477269 
		10 13.378201002477269 14 13.378201002477269 18 13.378201002477269 24 13.378201002477269;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_IKLeg_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.069000150376690925 6 0.069000150376690925 
		10 0.069000150376690925 14 0.069000150376690925 18 0.069000150376690925 24 0.069000150376690925;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_IKLeg_L_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.015303353529604964 6 -0.015303353529604964 
		10 -0.015303353529604964 14 -0.015303353529604964 18 -0.015303353529604964 24 -0.015303353529604964;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_IKLeg_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.16760982461393598 6 0.16760982461393598 
		10 0.16760982461393598 14 0.16760982461393598 18 0.16760982461393598 24 0.16760982461393598;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKArm_L_Man_IKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKArm_L_Man_FKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKArm_L_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 10 6 10 10 10 14 10 18 10 24 10;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_PoleArm_L_Man_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 10 6 10 10 10 14 10 18 10 24 10;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_PoleArm_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.30187358991198376 6 0.36254159232506533 
		10 0.39549705228612952 14 0.39549705228612952 18 0.25710452390026034 24 0.39549705228612952;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 0.82232499122619629;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0.56901818513870239;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 0.82232499122619629;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0.56901818513870239;
createNode animCurveTL -n "Maugli_PoleArm_L_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.67336977492758876 6 -0.7956138565595593 
		10 -0.86201805279910448 14 -0.86201805279910448 18 -0.97609601114871247 24 -0.86201805279910448;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.87029153108596802 1 1 1 0.86863160133361816;
	setAttr -s 6 ".kiy[0:5]"  0 -0.49253696203231812 0 0 0 0.49545860290527344;
	setAttr -s 6 ".kox[0:5]"  1 0.87029153108596802 1 1 1 0.86863160133361816;
	setAttr -s 6 ".koy[0:5]"  0 -0.49253696203231812 0 0 0 0.49545860290527344;
createNode animCurveTL -n "Maugli_PoleArm_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.052664568395363105 6 -0.2182428657313428 
		10 -0.30818663726222251 14 -0.30818663726222251 18 -0.41904777186613379 24 -0.30818663726222251;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.79364484548568726 1 1 1 0.87462091445922852;
	setAttr -s 6 ".kiy[0:5]"  0 -0.60838127136230469 0 0 0 0.48480740189552307;
	setAttr -s 6 ".kox[0:5]"  1 0.79364484548568726 1 1 1 0.87462097406387329;
	setAttr -s 6 ".koy[0:5]"  0 -0.60838127136230469 0 0 0 0.48480743169784546;
createNode animCurveTU -n "Maugli_IKArm_L_Man_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKArm_L_Man_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKArm_L_Man_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKArm_L_Man_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKArm_L_Man_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKArm_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -84.941336550094036 6 -46.334524830383195 
		10 -58.824210888565709 14 -77.224508239228342 18 -97.78067605427789 24 -97.78067605427789;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.5902785062789917 0.44335320591926575 
		0.36512544751167297 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0.80719965696334839 -0.89634698629379272 
		-0.9309583306312561 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.5902785062789917 0.44335320591926575 
		0.36512544751167297 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0.80719965696334839 -0.89634698629379272 
		-0.9309583306312561 0 0;
createNode animCurveTA -n "Maugli_IKArm_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 19.351892783302421 6 -2.0985078687748957 
		10 9.5679313160447883 14 22.796791484630951 18 10.92155845877172 24 10.92155845877172;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.89001023769378662 0.5230712890625 0.99609839916229248 
		1 1;
	setAttr -s 6 ".kiy[0:5]"  0 -0.45594069361686707 0.85228896141052246 
		0.088249020278453827 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.89001023769378662 0.5230712890625 0.99609839916229248 
		1 1;
	setAttr -s 6 ".koy[0:5]"  0 -0.45594069361686707 0.85228896141052246 
		0.088249020278453827 0 0;
createNode animCurveTA -n "Maugli_IKArm_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -23.456909615172744 6 -17.870277497843063 
		10 -0.34872621701621964 14 -4.5813380236830561 18 14.178018067197163 24 14.178018067197163;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.63706433773040771 0.75453311204910278 
		0.7247195839881897 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0.77081060409545898 0.65626204013824463 
		0.68904387950897217 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.63706433773040771 0.75453311204910278 
		0.7247195839881897 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0.77081060409545898 0.65626204013824463 
		0.68904387950897217 0 0;
createNode animCurveTL -n "Maugli_IKArm_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.71087397470952018 6 -0.49832346904420544 
		10 -0.36583471381642579 14 -0.64633339708524418 18 -0.79120002893813179 24 -0.79120002893813179;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.69480162858963013 0.87434959411621094 
		0.53116345405578613 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0.71920144557952881 -0.48529660701751709 
		-0.84726935625076294 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.69480162858963013 0.87434959411621094 
		0.53116345405578613 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0.71920144557952881 -0.48529660701751709 
		-0.84726935625076294 0 0;
createNode animCurveTL -n "Maugli_IKArm_L_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -1.7597179554642883 6 -0.31302351661455796 
		10 -1.4296177379054467 14 -0.67995170714346953 18 -0.30360130511963851 24 -0.30360130511963851;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.71054428815841675 0.58789736032485962 
		0.23044884204864502 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0.70365244150161743 -0.80893552303314209 
		0.97308439016342163 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.71054428815841675 0.58789736032485962 
		0.23044884204864502 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0.70365244150161743 -0.80893552303314209 
		0.97308439016342163 0 0;
createNode animCurveTL -n "Maugli_IKArm_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -1.1306425046017448 6 -0.34145642944291915 
		10 -0.23219432124511025 14 -0.45028417773786866 18 -0.80061447835185851 24 -0.80061447835185851;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.34784170985221863 0.92586684226989746 
		0.42472076416015625 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0.93755322694778442 -0.37785002589225769 
		-0.90532439947128296 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.34784170985221863 0.92586684226989746 
		0.42472076416015625 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0.93755322694778442 -0.37785002589225769 
		-0.90532439947128296 0 0;
createNode animCurveTU -n "Maugli_Fingers_R_Man_MiddleFingerCurl";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKSpine_M_Man_IKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKSpine_M_Man_FKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKSpine_M_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegBall_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegToe_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -7.0622500768802538e-031 6 -7.0622500768802538e-031 
		10 -7.0622500768802538e-031 14 -7.0622500768802538e-031 18 -7.0622500768802538e-031 
		24 -7.0622500768802538e-031;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegToe_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 3.1805546814635168e-015 6 3.1805546814635168e-015 
		10 3.1805546814635168e-015 14 3.1805546814635168e-015 18 3.1805546814635168e-015 
		24 3.1805546814635168e-015;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegToe_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegHeel_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegHeel_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 3.1805546814635168e-015 6 3.1805546814635168e-015 
		10 3.1805546814635168e-015 14 3.1805546814635168e-015 18 3.1805546814635168e-015 
		24 3.1805546814635168e-015;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegHeel_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKLeg_R_Man_IKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKLeg_R_Man_FKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKLeg_R_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 10 6 10 10 10 14 10 18 10 24 10;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_PoleLeg_R_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_PoleLeg_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_PoleLeg_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 25 6 25 10 25 14 25 18 25 24 25;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_toe";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLeg_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLeg_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLeg_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_IKLeg_R_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_IKLeg_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_IKLeg_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKArm_R_Man_IKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKArm_R_Man_FKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKArm_R_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 10 6 10 10 10 14 10 18 10 24 10;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_PoleArm_R_Man_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 10 6 10 10 10 14 10 18 10 24 10;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_PoleArm_R_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.16593047685129286 6 0.058407529987944101 
		10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.89521664381027222 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 -0.44563117623329163 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.89521664381027222 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 -0.44563117623329163 0 0 0 0;
createNode animCurveTL -n "Maugli_PoleArm_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.11674023114788831 6 -0.041092562867040827 
		10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_PoleArm_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.10282366384186119 6 0.036193930996149065 
		10 1.1102230246251565e-016 14 1.1102230246251565e-016 18 1.1102230246251565e-016 
		24 1.1102230246251565e-016;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -6.2725381128105917e-045 6 -6.2725381128105917e-045 
		10 -6.2725381128105917e-045 14 -6.2725381128105917e-045 18 -6.2725381128105917e-045 
		24 -6.2725381128105917e-045;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKArm_R_Man_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKArm_R_Man_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKArm_R_Man_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKArm_R_Man_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKArm_R_Man_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKArm_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -4.8790848169292413 6 -16.973824995513723 
		10 4.5987463381781746 14 60.526449667481693 18 -24.31701750665756 24 -12.754512848885321;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.89576393365859985 0.19342304766178131 
		0.46718373894691467 0.25219714641571045 0.70392531156539917;
	setAttr -s 6 ".kiy[0:5]"  0 0.44453006982803345 0.98111546039581299 
		-0.88416028022766113 -0.96767586469650269 0.71027398109436035;
	setAttr -s 6 ".kox[0:5]"  1 0.89576393365859985 0.19342304766178131 
		0.46718373894691467 0.25219714641571045 0.70392531156539917;
	setAttr -s 6 ".koy[0:5]"  0 0.44453006982803345 0.98111546039581299 
		-0.88416028022766113 -0.96767586469650269 0.71027398109436035;
createNode animCurveTA -n "Maugli_IKArm_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -54.828555067778908 6 -46.696892949997185 
		10 -47.179168477831816 14 -60.265143126087082 18 -52.810041505224198 24 -51.071041253431346;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  0.99325102567672729 1 1 0.93830698728561401 
		1 1;
	setAttr -s 6 ".kiy[0:5]"  -0.11598449945449829 0 0 -0.34580340981483459 
		0 0;
	setAttr -s 6 ".kox[0:5]"  0.99325102567672729 1 1 0.93830698728561401 
		1 1;
	setAttr -s 6 ".koy[0:5]"  -0.11598444730043411 0 0 -0.34580340981483459 
		0 0;
createNode animCurveTA -n "Maugli_IKArm_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -27.117038477838772 6 -48.11037649302623 
		10 -51.981135731674065 14 -1.5464518807326364 18 -35.283008401950113 24 -30.429381170308442;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.60915684700012207 0.31177198886871338 
		0.67505830526351929 0.55156338214874268 0.92080789804458618;
	setAttr -s 6 ".kiy[0:5]"  0 -0.79304975271224976 0.95015686750411987 
		0.73776429891586304 -0.83413296937942505 0.39001637697219849;
	setAttr -s 6 ".kox[0:5]"  1 0.60915684700012207 0.31177198886871338 
		0.67505830526351929 0.55156338214874268 0.92080795764923096;
	setAttr -s 6 ".koy[0:5]"  0 -0.79304975271224976 0.95015686750411987 
		0.73776429891586304 -0.83413296937942505 0.39001640677452087;
createNode animCurveTL -n "Maugli_IKArm_R_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.24375838155221463 6 -0.35236724731098851 
		10 0.17731597217202033 14 -0.2680089816177581 18 -0.57428372471311184 24 -0.50891155850440861;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.62068325281143188 0.9534308910369873 
		0.33437645435333252 0.81049245595932007 0.95051276683807373;
	setAttr -s 6 ".kiy[0:5]"  0 0.78406137228012085 0.30161166191101074 
		-0.94243961572647095 -0.58574908971786499 0.3106854259967804;
	setAttr -s 6 ".kox[0:5]"  1 0.62068325281143188 0.9534308910369873 
		0.33437645435333252 0.81049245595932007 0.95051282644271851;
	setAttr -s 6 ".koy[0:5]"  0 0.78406137228012085 0.30161166191101074 
		-0.94243961572647095 -0.58574908971786499 0.31068545579910278;
createNode animCurveTL -n "Maugli_IKArm_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.5675789344441291 6 -0.26491127704953493 
		10 -1.5580646593515097 14 -0.6342717200217125 18 -0.06405595491879669 24 -0.17073023409560481;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.31895765662193298 0.58535540103912354 
		0.17571362853050232 0.58382415771484375 0.8823390007019043;
	setAttr -s 6 ".kiy[0:5]"  0 -0.9477689266204834 -0.81077677011489868 
		0.98444128036499023 0.81188011169433594 -0.47061440348625183;
	setAttr -s 6 ".kox[0:5]"  1 0.31895765662193298 0.58535540103912354 
		0.17571362853050232 0.58382415771484375 0.8823390007019043;
	setAttr -s 6 ".koy[0:5]"  0 -0.9477689266204834 -0.81077677011489868 
		0.98444128036499023 0.81188011169433594 -0.47061440348625183;
createNode animCurveTL -n "Maugli_IKArm_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.5348454704179556 6 0.39375661956108066 
		10 0.46933093006043392 14 0.5018220681803911 18 0.46230745101141568 24 0.44722353666474202;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.98122751712799072 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 -0.19285400211811066 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.98122751712799072 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 -0.19285400211811066 0 0 0 0;
createNode animCurveTA -n "Maugli_FKScapula_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 16.010244166512202 6 -7.7552712143287534 
		10 -4.4739154189071044 14 -7.1990267140314277 18 -7.1990267140314277 24 -7.1990267140314277;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.68193733692169189 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 -0.73141056299209595 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.68193733692169189 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 -0.73141056299209595 0 0 0 0;
createNode animCurveTA -n "Maugli_FKScapula_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 14.453583717594759 6 -20.621839593368634 
		10 18.313941053531778 14 9.9598426785175036 18 9.9598426785175036 24 9.9598426785175036;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.98017752170562744 0.44693347811698914 
		1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0.19812114536762238 0.89456713199615479 
		0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.98017752170562744 0.44693347811698914 
		1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0.19812114536762238 0.89456713199615479 
		0 0 0;
createNode animCurveTA -n "Maugli_FKScapula_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 8.5771851995081878 6 -0.40543139523343841 
		10 -11.493021027128215 14 -7.1981747374653153 18 -7.1981747374653153 24 -7.1981747374653153;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.68935436010360718 0.91376423835754395 
		1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 -0.72442424297332764 -0.40624499320983887 
		0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.68935436010360718 0.91376423835754395 
		1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 -0.72442424297332764 -0.40624499320983887 
		0 0 0;
createNode animCurveTL -n "Maugli_FKScapula_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_FKScapula_L_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_FKScapula_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -5.5511151231257827e-017 6 -5.5511151231257827e-017 
		10 -5.5511151231257827e-017 14 -5.5511151231257827e-017 18 -5.5511151231257827e-017 
		24 -5.5511151231257827e-017;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_FKMiddleFinger1_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 17.622819694952526 6 17.622819694952526 
		10 17.622819694952526 14 17.622819694952526 18 17.622819694952526 24 17.622819694952526;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_FKMiddleFinger2_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -23.252905752704581 6 -23.252905752704581 
		10 -23.252905752704581 14 -23.252905752704581 18 -23.252905752704581 24 -23.252905752704581;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_FKMiddleFinger3_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_FKThumbFinger1_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -8.9121374222325116 6 -9.858726095142023 
		10 -10.372922440313587 14 -10.372922440313587 18 -10.372922440313587 24 -10.372922440313587;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_FKThumbFinger1_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 15.368506266811023 6 7.1995074319167189 
		10 2.7620263328639107 14 2.7620263328639107 18 2.7620263328639107 24 2.7620263328639107;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.83458113670349121 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 -0.55088508129119873 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.83458113670349121 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 -0.55088508129119873 0 0 0 0;
createNode animCurveTA -n "Maugli_FKThumbFinger1_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -23.424398022041203 6 -29.28372018195833 
		10 -32.466562028725463 14 -32.466562028725463 18 -32.466562028725463 24 -32.466562028725463;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.90382093191146851 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 -0.42791092395782471 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.90382093191146851 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 -0.42791092395782471 0 0 0 0;
createNode animCurveTA -n "Maugli_FKThumbFinger2_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 43.562669387098943 6 -1.69365081185166 
		10 -26.277332307519721 14 -26.277332307519721 18 -26.277332307519721 24 -26.277332307519721;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.26377707719802856 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 -0.96458369493484497 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.26377707719802856 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 -0.96458369493484497 0 0 0 0;
createNode animCurveTA -n "Maugli_FKBackA_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 31.339401832138403 6 16.109024579772079 
		10 17.195720661984922 14 17.809203015884659 18 -2.940042078010479 24 7.8357327658317191;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 3;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 3;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 0.88641369342803955 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 -0.4628937840461731 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 0.88641369342803955 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 -0.4628937840461731 0;
createNode animCurveTA -n "Maugli_FKBackA_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -12.230132580790263 6 -9.1822261041775164 
		10 -9.9447807884114479 14 -9.5760299740568353 18 -6.9103257560899047 24 -7.5265731098501263;
	setAttr -s 6 ".kit[0:5]"  1 10 9 9 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 9 9 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 0.99966800212860107 0.98084288835525513 
		1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 -0.025765847414731979 0.19479992985725403 
		0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 0.99966800212860107 0.98084288835525513 
		1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 -0.025765847414731979 0.19479992985725403 
		0 0;
createNode animCurveTA -n "Maugli_FKBackA_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -12.926179688964792 6 -8.1123953696891977 
		10 -4.4684697971008696 14 -5.6718025998879327 18 -5.5240785176020424 24 -5.4975000363152615;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.91435366868972778 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0.40491661429405212 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.91435366868972778 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0.40491661429405212 0 0 0 0;
createNode animCurveTA -n "Maugli_FKBackB_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 7.2569396922509739 6 -13.847707402872965 
		10 16.831723273509315 14 8.1325903792716403 18 2.7266862105714793 24 2.7266862105714793;
	setAttr -s 6 ".kit[0:5]"  1 10 10 9 9 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 9 9 10;
	setAttr -s 6 ".kix[0:5]"  0.98524564504623413 0.89394956827163696 
		0.57076817750930786 0.73476845026016235 0.96219760179519653 1;
	setAttr -s 6 ".kiy[0:5]"  0.1711462140083313 0.44816774129867554 
		0.82111120223999023 -0.67831796407699585 -0.27235239744186401 0;
	setAttr -s 6 ".kox[0:5]"  0.98524558544158936 0.89394956827163696 
		0.57076817750930786 0.73476845026016235 0.96219760179519653 1;
	setAttr -s 6 ".koy[0:5]"  0.1711461991071701 0.44816774129867554 
		0.82111120223999023 -0.67831796407699585 -0.27235239744186401 0;
createNode animCurveTA -n "Maugli_FKBackB_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1.2968979376576604 6 4.0786015240836901 
		10 -1.9521376464906253 14 -0.65017050746722516 18 0.24259990801533335 24 0.24259990801533335;
	setAttr -s 6 ".kit[0:5]"  1 10 10 9 9 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 9 9 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 0.98984003067016602 0.99890923500061035 
		1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0.14218579232692719 0.046694360673427582 
		0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 0.98984003067016602 0.99890923500061035 
		1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0.14218579232692719 0.046694360673427582 
		0;
createNode animCurveTA -n "Maugli_FKBackB_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -2.842118883650758 6 2.008240346559746 
		10 -0.19154145794465846 14 0.76871136763552372 18 1.5001242681430698 24 1.5001242681430698;
	setAttr -s 6 ".kit[0:5]"  1 10 10 9 9 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 9 9 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 0.99392646551132202 0.99926751852035522 
		1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0.11004679650068283 0.038268636912107468 
		0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 0.99392646551132202 0.99926751852035522 
		1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0.11004679650068283 0.038268636912107468 
		0;
createNode animCurveTA -n "Maugli_FKChest_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -12.142222007810011 6 9.8837333537213379 
		10 -4.1309094654251099 14 0.29454518258654205 18 -12.769021381384317 24 -12.769021381384317;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 9 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 9 10;
	setAttr -s 6 ".kix[0:5]"  1 0.92215603590011597 0.84700286388397217 
		0.87050849199295044 0.82538563013076782 1;
	setAttr -s 6 ".kiy[0:5]"  0 0.38681799173355103 -0.53158825635910034 
		-0.49215331673622131 -0.56456935405731201 0;
	setAttr -s 6 ".kox[0:5]"  1 0.92215603590011597 0.84700286388397217 
		0.87050849199295044 0.82538563013076782 1;
	setAttr -s 6 ".koy[0:5]"  0 0.38681799173355103 -0.53158825635910034 
		-0.49215331673622131 -0.56456935405731201 0;
createNode animCurveTA -n "Maugli_FKChest_M_Man_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 12.305762111416071 6 4.5135972174656285 
		10 2.1403157287659678 14 0.37977182842360263 18 4.6070431346914544 24 4.6070431346914544;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 10;
	setAttr -s 6 ".kot[0:5]"  1 9 9 9 9 10;
	setAttr -s 6 ".kix[0:5]"  1 0.88274550437927246 0.96529340744018555 
		0.9872167706489563 0.97636920213699341 1;
	setAttr -s 6 ".kiy[0:5]"  0 -0.46985143423080444 -0.26116809248924255 
		0.15938311815261841 0.21610897779464722 0;
	setAttr -s 6 ".kox[0:5]"  1 0.88274550437927246 0.96529340744018555 
		0.9872167706489563 0.97636920213699341 1;
	setAttr -s 6 ".koy[0:5]"  0 -0.46985143423080444 -0.26116809248924255 
		0.15938311815261841 0.21610897779464722 0;
createNode animCurveTA -n "Maugli_FKChest_M_Man_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -17.630084171996455 6 -0.12187423326138712 
		10 4.8710949500003151 14 5.8173215190503154 18 4.8308420450374907 24 4.8308420450374907;
	setAttr -s 6 ".kit[0:5]"  1 10 9 9 9 10;
	setAttr -s 6 ".kot[0:5]"  1 10 9 9 9 10;
	setAttr -s 6 ".kix[0:5]"  1 0.64710909128189087 0.93205803632736206 
		0.99999654293060303 0.99866867065429688 1;
	setAttr -s 6 ".kiy[0:5]"  0 0.7623974084854126 0.36230909824371338 
		-0.002634537173435092 -0.051583178341388702 0;
	setAttr -s 6 ".kox[0:5]"  1 0.64710909128189087 0.93205803632736206 
		0.99999654293060303 0.99866867065429688 1;
	setAttr -s 6 ".koy[0:5]"  0 0.7623974084854126 0.36230909824371338 
		-0.002634537173435092 -0.051583178341388702 0;
createNode animCurveTA -n "Maugli_FKNeck_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -21.349332740018081 6 0.93377916218734136 
		10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  0.94740694761276245 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  -0.32003137469291687 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.94740694761276245 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  -0.32003137469291687 0 0 0 0 0;
createNode animCurveTA -n "Maugli_FKNeck_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.44123125050354439 6 -1.3448200292839316 
		10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTA -n "Maugli_FKNeck_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 19.641362431357976 6 1.2298426061426411 
		10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 1 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 1 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.87321597337722778 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 -0.48733341693878174 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.87321609258651733 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 -0.48733335733413696 0 0 0 0;
createNode animCurveTA -n "Maugli_FKHead_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -17.660014913242996 6 7.0844220869133263 
		10 10.443605142715551 14 -24.247933760629564 18 7.6172475573045721 24 -6.9400884964770713;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 3;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 3;
createNode animCurveTA -n "Maugli_FKHead_M_Man_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 6.3177172652768183 6 -0.10756937775551118 
		10 -0.84865577388228974 14 5.3994754207414095 18 3.7455262557255788 24 3.508580449788079;
	setAttr -s 6 ".kit[0:5]"  1 9 9 10 9 10;
	setAttr -s 6 ".kot[0:5]"  1 9 9 10 9 10;
	setAttr -s 6 ".kix[0:5]"  1 0.93625825643539429 0.94075679779052734 
		1 0.99513453245162964 1;
	setAttr -s 6 ".kiy[0:5]"  0 -0.3513125479221344 0.33908191323280334 
		0 -0.098525308072566986 0;
	setAttr -s 6 ".kox[0:5]"  1 0.93625825643539429 0.94075679779052734 
		1 0.99513453245162964 1;
	setAttr -s 6 ".koy[0:5]"  0 -0.3513125479221344 0.33908191323280334 
		0 -0.098525308072566986 0;
createNode animCurveTA -n "Maugli_FKHead_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 16.700037308578423 6 9.5354553113389393 
		10 3.9822293311001782 14 6.2227307305016275 18 5.5466143547304041 24 5.0972336912670713;
	setAttr -s 6 ".kit[0:5]"  1 10 10 9 9 3;
	setAttr -s 6 ".kot[0:5]"  1 10 10 9 9 3;
	setAttr -s 6 ".kix[0:5]"  1 0.83234363794326782 1 0.99479913711547852 
		0.99826812744140625 1;
	setAttr -s 6 ".kiy[0:5]"  0 -0.5542600154876709 0 0.10185624659061432 
		-0.058828826993703842 0;
	setAttr -s 6 ".kox[0:5]"  1 0.83234363794326782 1 0.99479913711547852 
		0.99826812744140625 1;
	setAttr -s 6 ".koy[0:5]"  0 -0.5542600154876709 0 0.10185624659061432 
		-0.058828826993703842 0;
createNode animCurveTA -n "Maugli_FKScapula_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 3.234691603003407 6 3.5197090000854061 
		10 8.0974718280578859 14 3.6745332739058547 18 3.6745332739058547 24 3.6745332739058547;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 0.99994874000549316 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0.010132705792784691 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 0.99994874000549316 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0.010132705792784691 0 0 0;
createNode animCurveTA -n "Maugli_FKScapula_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -4.1984829852594405 6 -5.5900618581013584 
		10 0.92357489653956248 14 -6.3459812884849134 18 -6.3459812884849134 24 -6.3459812884849134;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 0.99877840280532837 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 -0.049414373934268951 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 0.99877840280532837 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 -0.049414373934268951 0 0 0;
createNode animCurveTA -n "Maugli_FKScapula_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1.2882750967306602 6 -0.012504446557556857 
		10 -8.0836823991485858 14 -0.71910078156005675 18 -0.71910078156005675 24 -0.71910078156005675;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 0.99893230199813843 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 -0.046197246760129929 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 0.99893230199813843 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 -0.046197246760129929 0 0 0;
createNode animCurveTL -n "Maugli_FKScapula_R_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -2.7755575615628914e-017 6 -2.7755575615628914e-017 
		10 -2.7755575615628914e-017 14 -2.7755575615628914e-017 18 -2.7755575615628914e-017 
		24 -2.7755575615628914e-017;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_FKScapula_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_FKScapula_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 5.5511151231257827e-017 6 5.5511151231257827e-017 
		10 5.5511151231257827e-017 14 5.5511151231257827e-017 18 5.5511151231257827e-017 
		24 5.5511151231257827e-017;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_FKMiddleFinger1_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_FKMiddleFinger2_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -67.588216236699324 6 -67.588216236699324 
		10 -67.588216236699324 14 -67.588216236699324 18 -67.588216236699324 24 -67.588216236699324;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_FKMiddleFinger3_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -81.669521342510606 6 -81.669521342510606 
		10 -81.669521342510606 14 -81.669521342510606 18 -81.669521342510606 24 -81.669521342510606;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_FKThumbFinger1_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 25.665274764482422 6 25.665274764482422 
		10 25.665274764482422 14 25.665274764482422 18 25.665274764482422 24 25.665274764482422;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_FKThumbFinger1_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 36.541774445263137 6 36.541774445263137 
		10 36.541774445263137 14 36.541774445263137 18 36.541774445263137 24 36.541774445263137;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_FKThumbFinger1_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -67.421493922591793 6 -67.421493922591793 
		10 -67.421493922591793 14 -67.421493922591793 18 -67.421493922591793 24 -67.421493922591793;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_FKThumbFinger2_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 47.81080993924823 6 47.81080993924823 
		10 47.81080993924823 14 47.81080993924823 18 47.81080993924823 24 47.81080993924823;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_Main_Man_visibility";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_Center_M_CenterBtwFeet";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_Center_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 -5.4719794826840449 10 -8.4444129496952112 
		14 -8.4444129496952272 18 -8.4444129496952112 24 -8.4444129496952112;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.91458922624588013 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 -0.40438419580459595 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.91458922624588013 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 -0.40438419580459595 0 0 0 0;
createNode animCurveTA -n "Maugli_Center_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 -0.62802661062560927 10 -0.96917688750520981 
		14 -0.9691768875052087 18 -0.96917688750520981 24 -0.96917688750520981;
	setAttr -s 6 ".kit[0:5]"  1 9 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 9 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.99871492385864258 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 -0.050680767744779587 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.99871492385864258 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 -0.050680767744779587 0 0 0 0;
createNode animCurveTA -n "Maugli_Center_M_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 14.253673349941334 6 25.52905399474162 
		10 25.703919637466868 14 -5.8504392426952982 18 3.1650958122187984 24 3.1650958122187984;
	setAttr -s 6 ".kit[0:5]"  1 9 9 10 9 10;
	setAttr -s 6 ".kot[0:5]"  1 9 9 10 9 10;
	setAttr -s 6 ".kix[0:5]"  1 0.8576694130897522 0.43777093291282654 
		0.56111598014831543 0.90430790185928345 1;
	setAttr -s 6 ".kiy[0:5]"  0 0.51420152187347412 -0.899086594581604 
		-0.82773721218109131 0.42688062787055969 0;
	setAttr -s 6 ".kox[0:5]"  1 0.8576694130897522 0.43777093291282654 
		0.56111598014831543 0.90430790185928345 1;
	setAttr -s 6 ".koy[0:5]"  0 0.51420152187347412 -0.899086594581604 
		-0.82773721218109131 0.42688062787055969 0;
createNode animCurveTL -n "Maugli_Center_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0.50047976394431526 10 0.17740126934519607 
		14 -0.70006028062253156 18 -0.09976198877020459 24 -0.13106792216224994;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTL -n "Maugli_Center_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 -0.82664825044252044 10 0.060594968720114051 
		14 0.59337595674470345 18 -0.077467057099922076 24 0.024349347202935689;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.98387569189071655 0.18456408381462097 
		0.88803964853286743 0.50545543432235718 0.8911663293838501;
	setAttr -s 6 ".kiy[0:5]"  0 0.17885375022888184 0.98282051086425781 
		-0.45976704359054565 -0.86285275220870972 0.45367676019668579;
	setAttr -s 6 ".kox[0:5]"  1 0.98387569189071655 0.18456408381462097 
		0.88803964853286743 0.50545543432235718 0.8911663293838501;
	setAttr -s 6 ".koy[0:5]"  0 0.17885375022888184 0.98282051086425781 
		-0.45976704359054565 -0.86285275220870972 0.45367676019668579;
createNode animCurveTL -n "Maugli_Center_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 -0.020990778747009414 10 0.0010188165125213783 
		14 0.019771691683665035 18 -0.0012153380885657344 24 -0.0012760952138130693;
	setAttr -s 6 ".kit[0:5]"  1 10 9 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 9 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 0.9885178804397583 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0.15110412240028381 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 0.9885178804397583 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0.15110412240028381 0 0 0;
createNode animCurveTA -n "Maugli_IKLegBackBall_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKLegBack_L_IKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKLegBack_L_FKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKLegBack_L_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 10 6 10 10 10 14 10 18 10 24 10;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_PoleLegBack_L_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 10 6 10 10 10 14 10 18 10 24 10;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_PoleLegBack_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0.67202155286984011 18 
		0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_PoleLegBack_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 -0.76363781585663615 18 
		0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_PoleLegBack_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 -0.059820501851120214 18 
		0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegBack_L_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 10 1 11 1 14 1 18 1 24 1;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegBack_L_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 10 1 11 1 14 1 18 1 24 1;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegBack_L_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 10 0 11 0 14 0 18 0 24 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegBack_L_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 10 0 11 0 14 0 18 0 24 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegBack_L_legAim";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10 6 10 10 10 11 10 14 10 18 10 24 10;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegBack_L_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 25 6 25 10 25 11 25 14 25 18 25 24 25;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegBack_L_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 10 0 11 0 14 0 18 0 24 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegBack_L_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 10 0 11 0 14 0 18 0 24 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegBack_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 10 0 11 0 14 0 18 0 24 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegBack_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 10 0 11 0 14 0 18 0 24 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegBack_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 120.25945944718168 6 90.245173017805968 
		10 41.294787761528362 11 0 14 0 18 0 24 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 0.23508429527282715 0.10522758215665817 
		1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 -0.97197496891021729 -0.99444818496704102 
		0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 0.23508429527282715 0.10522758215665817 
		1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 -0.97197496891021729 -0.99444818496704102 
		0 0 0 0;
createNode animCurveTL -n "Maugli_IKLegBack_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.96308895096482727 6 1.5663544403348943 
		10 0.15400117724779094 11 0 14 0 18 0 24 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 0.38092526793479919 0.10580690950155258 
		1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 -0.92460590600967407 -0.99438673257827759 
		0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 0.38092526793479919 0.10580690950155258 
		1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 -0.92460590600967407 -0.99438673257827759 
		0 0 0 0;
createNode animCurveTL -n "Maugli_IKLegBack_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.75305475314980841 6 -0.80316944045571326 
		10 -0.93904691544927732 11 -0.76278640316887203 14 -0.76278640316887203 18 -0.76278640316887203 
		24 -0.76278640316887203;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 0.19327913224697113 0.97187817096710205 
		1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 -0.9811437726020813 0.23548434674739838 
		0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 0.19327913224697113 0.97187817096710205 
		1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 -0.9811437726020813 0.23548434674739838 
		0 0 0 0;
createNode animCurveTL -n "Maugli_IKLegBack_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 10 0 11 0 14 0 18 0 24 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_BendNeck_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_BendNeck_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_BendNeck_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKSpine_M_IKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKSpine_M_FKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKSpine_M_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegBackBall_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKLegBack_R_IKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKLegBack_R_FKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKLegBack_R_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 10 6 10 10 10 14 10 18 10 24 10;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_PoleLegBack_R_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 10 6 10 10 10 14 10 18 10 24 10;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_PoleLegBack_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -2.2204460492503131e-016 6 -2.2204460492503131e-016 
		10 -2.2204460492503131e-016 14 0.67708444583117355 18 -2.2204460492503131e-016 24 
		-2.2204460492503131e-016;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_PoleLegBack_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 -0.090016569995861523 18 
		0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_PoleLegBack_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -5.5511151231257827e-017 6 0.025230061500312925 
		10 -5.5511151231257827e-017 14 -0.004476127459346585 18 -5.5511151231257827e-017 
		24 -5.5511151231257827e-017;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  0.78527766466140747 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0.61914384365081787 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.7852776050567627 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0.6191437840461731 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegBack_R_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 10 1 11 1 14 1 18 1 24 1;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegBack_R_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 10 1 11 1 14 1 18 1 24 1;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegBack_R_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 10 0 11 0 14 0 18 0 24 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegBack_R_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 10 0 11 0 14 0 18 0 24 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegBack_R_legAim";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10 6 10 10 10 11 10 14 10 18 10 24 10;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegBack_R_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 25 6 25 10 25 11 25 14 25 18 25 24 25;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegBack_R_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 10 0 11 0 14 0 18 0 24 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegBack_R_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 10 0 11 0 14 0 18 0 24 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegBack_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -17.042137663821418 6 -17.042137663821414 
		10 -17.042137663821414 11 -17.042137663821414 14 -17.042137663821414 18 -17.042137663821414 
		24 -17.042137663821414;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegBack_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.6633143465433158e-015 6 5.8548667139775915e-016 
		10 0 11 0 14 0 18 0 24 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegBack_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 105.66538207304833 6 70.483134799294021 
		10 59.194854430111015 11 0 14 0 18 0 24 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 0.38013145327568054 0.13425683975219727 
		1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 -0.92493247985839844 -0.99094653129577637 
		0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 0.38013145327568054 0.13425683975219727 
		1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 -0.92493247985839844 -0.99094653129577637 
		0 0 0 0;
createNode animCurveTL -n "Maugli_IKLegBack_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.4622462724835834 6 1.4092575454471863 
		10 0.36896699712296238 11 0 14 1.1102230246251563e-016 18 1.1102230246251563e-016 
		24 1.1102230246251563e-016;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 0.29163894057273865 0.11744707822799683 
		1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 -0.9565284252166748 -0.99307912588119507 
		0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 0.29163894057273865 0.11744707822799683 
		1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 -0.9565284252166748 -0.99307912588119507 
		0 0 0 0;
createNode animCurveTL -n "Maugli_IKLegBack_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.86611225864017405 6 -0.75657323814064947 
		10 -0.22119128373043584 11 0.019491142195864015 14 0.019491142195864015 18 0.019491142195864015 
		24 0.019491142195864015;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 0.29310443997383118 0.20997130870819092 
		1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 -0.95608043670654297 0.97770750522613525 
		0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 0.29310443997383118 0.20997130870819092 
		1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 -0.95608043670654297 0.97770750522613525 
		0 0 0 0;
createNode animCurveTL -n "Maugli_IKLegBack_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.16279811825569085 6 0.016101625269394543 
		10 -0.063585363072848899 11 -0.063585363072848899 14 -0.063585363072848899 18 -0.063585363072848899 
		24 -0.063585363072848899;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 0.82725322246551514 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 -0.5618293285369873 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 0.82725322246551514 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 -0.5618293285369873 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKSplineTail_M_IKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKSplineTail_M_FKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKSplineTail_M_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 10 6 10 10 10 14 10 18 10 24 10;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_WagCurveSplineTail_M_increment";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_WagCurveSplineTail_M_multiply";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_WagCurveSplineTail_M_timeOffset";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_WagCurveSplineTail_M_enable";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_WagCurveSplineTail_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_WagCurveSplineTail_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_WagCurveSplineTail_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKSplineTail2_M_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKSplineTail2_M_twist";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKSplineTail2_M_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_IKSplineTail2_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.50156583028862078 6 1.2368222777994256 
		10 2.0772062555494655 14 1.4239977969038713 18 -0.39620631951564023 24 -0.31618923007172439;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 3;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 3;
createNode animCurveTL -n "Maugli_IKSplineTail2_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 -1.0404535870756144 10 0.41821377535552484 
		14 0.69067505114424765 18 0.11047701236344354 24 -1.0020975550085076;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 3;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 3;
createNode animCurveTL -n "Maugli_IKSplineTail2_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.39341763880761793 6 -0.0035084435499789235 
		10 -0.70693747499804638 14 -0.55273050916867672 18 0.044212659746057481 24 0.80886811842270168;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 3;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 3;
	setAttr -s 6 ".kix[0:5]"  1 0.28992170095443726 0.43677359819412231 
		0.33455419540405273 0.23778837919235229 1;
	setAttr -s 6 ".kiy[0:5]"  0 -0.9570503830909729 -0.89957141876220703 
		0.94237655401229858 0.97131699323654175 0;
	setAttr -s 6 ".kox[0:5]"  1 0.28992170095443726 0.43677359819412231 
		0.33455419540405273 0.23778837919235229 1;
	setAttr -s 6 ".koy[0:5]"  0 -0.9570503830909729 -0.89957141876220703 
		0.94237655401229858 0.97131699323654175 0;
createNode animCurveTU -n "Maugli_IKSplineTail1_M_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_IKSplineTail1_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.82001054947299123 6 1.6642119761088139 
		10 0.52928752205479834 14 -0.37609371297962069 18 -0.14481689916084473 24 3.1086244689504383e-015;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 3;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 3;
createNode animCurveTL -n "Maugli_IKSplineTail1_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 -1.0578286572533935 10 -0.0071314574307739242 
		14 0.76915352407575055 18 -0.64655379546165936 24 -0.16519211009181056;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 3;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 3;
	setAttr -s 6 ".kix[0:5]"  0.99688762426376343 0.99977117776870728 
		0.14442980289459229 0.38491138815879822 0.33601316809654236 1;
	setAttr -s 6 ".kiy[0:5]"  -0.078835465013980865 -0.021389476954936981 
		0.98951500654220581 -0.92295348644256592 -0.94185733795166016 0;
	setAttr -s 6 ".kox[0:5]"  0.99688762426376343 0.99977117776870728 
		0.14442980289459229 0.38491138815879822 0.33601316809654236 1;
	setAttr -s 6 ".koy[0:5]"  -0.078835465013980865 -0.021389476954936981 
		0.98951500654220581 -0.92295348644256592 -0.94185733795166016 0;
createNode animCurveTL -n "Maugli_IKSplineTail1_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 -0.069939503353509486 10 0.099828633138470124 
		14 -0.01091369199448522 18 0.25676110838299682 24 0.010972047845733357;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 3;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 3;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_FKRump_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -18.638044314952673 6 -18.638044314952673 
		10 -18.638044314952673 14 -18.638044314952673 18 -18.638044314952673 24 -18.638044314952673;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_FKRump_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 5.9273289705481567 6 5.9273289705481567 
		10 5.9273289705481567 14 5.9273289705481567 18 5.9273289705481567 24 5.9273289705481567;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_FKRump_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 12.021048230974857 6 12.021048230974857 
		10 12.021048230974857 14 12.021048230974857 18 12.021048230974857 24 12.021048230974857;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_FKRump_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -5.5511151231257827e-017 6 -5.5511151231257827e-017 
		10 -5.5511151231257827e-017 14 -5.5511151231257827e-017 18 -5.5511151231257827e-017 
		24 -5.5511151231257827e-017;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_FKRump_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 2.2204460492503131e-016 6 2.2204460492503131e-016 
		10 2.2204460492503131e-016 14 2.2204460492503131e-016 18 2.2204460492503131e-016 
		24 2.2204460492503131e-016;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_FKRump_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 2.2204460492503131e-016 6 2.2204460492503131e-016 
		10 2.2204460492503131e-016 14 2.2204460492503131e-016 18 2.2204460492503131e-016 
		24 2.2204460492503131e-016;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_FKRump_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -18.710504463926263 6 -18.710504463926263 
		10 -18.710504463926263 14 -28.857007558094992 18 -14.304550782810898 24 -18.710504463926263;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 0.96084725856781006 0.88310849666595459 
		0.9333842396736145;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0.2770785391330719 0.46916875243186951 
		-0.35887876152992249;
	setAttr -s 6 ".kox[0:5]"  1 1 1 0.96084725856781006 0.88310849666595459 
		0.9333842396736145;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0.2770785391330719 0.46916875243186951 
		-0.35887876152992249;
createNode animCurveTA -n "Maugli_FKRump_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 8.2582530676151027 6 8.2582530676151027 
		10 8.2582530676151027 14 9.0217272788253986 18 7.8446116588349337 24 8.2582530676151027;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_FKRump_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 5.1050521316126698 6 5.1050521316126698 
		10 5.1050521316126698 14 3.5768500868743334 18 5.7224610223374386 24 5.1050521316126698;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_FKRump_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 5.5511151231257827e-017 6 5.5511151231257827e-017 
		10 5.5511151231257827e-017 14 5.5511151231257827e-017 18 5.5511151231257827e-017 
		24 5.5511151231257827e-017;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_FKRump_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_FKRump_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_FKBackA_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -6.1344158462123248 6 -3.2176459034837253 
		10 -18.960459375834066 14 -3.1445656591769535 18 -6.1344158462123248 24 -6.1344158462123248;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.83016681671142578 0.99998855590820313 
		0.76590758562088013 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 -0.55751514434814453 0.0047830361872911453 
		0.64295071363449097 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.83016681671142578 0.99998855590820313 
		0.76590758562088013 1 1;
	setAttr -s 6 ".koy[0:5]"  0 -0.55751514434814453 0.0047830361872911453 
		0.64295071363449097 0 0;
createNode animCurveTA -n "Maugli_FKBackA_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -2.6442010631261756 6 -2.6552208426898498 
		10 -2.5148757546988421 14 -2.5712127154803093 18 -2.6442010631261756 24 -2.6442010631261756;
	setAttr -s 6 ".kit[0:5]"  1 10 10 9 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 9 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 0.99996423721313477 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 -0.008464018814265728 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 0.99996423721313477 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 -0.008464018814265728 0 0;
createNode animCurveTA -n "Maugli_FKBackA_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.28408691297585409 6 0.14921645402251513 
		10 0.86366307678667409 14 -0.17729871117655785 18 0.28408691297585409 24 0.28408691297585409;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_FKBackB_M_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 7.0594173235210462 10 9.9228069185941035 
		14 9.4905614538747223 18 -4.0937696667714745 24 -4.0937696667714745;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 10;
	setAttr -s 6 ".kot[0:5]"  1 9 9 9 9 10;
	setAttr -s 6 ".kix[0:5]"  1 0.88737761974334717 0.98757612705230713 
		0.73689126968383789 0.81489270925521851 1;
	setAttr -s 6 ".kiy[0:5]"  0 0.46104320883750916 0.15714116394519806 
		-0.67601132392883301 -0.57961189746856689 0;
	setAttr -s 6 ".kox[0:5]"  1 0.88737761974334717 0.98757612705230713 
		0.73689126968383789 0.81489270925521851 1;
	setAttr -s 6 ".koy[0:5]"  0 0.46104320883750916 0.15714116394519806 
		-0.67601132392883301 -0.57961189746856689 0;
createNode animCurveTA -n "Maugli_FKBackB_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 -5.65072929256986 10 -8.6330355110495258 
		14 -8.6440149233468002 18 -8.7401097734428159 24 -8.7401097734428159;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.91122984886169434 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 -0.41189837455749512 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.91122984886169434 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 -0.41189837455749512 0 0 0 0;
createNode animCurveTA -n "Maugli_FKBackB_M_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 -0.55589567499515835 10 -1.5041935505422424 
		14 -1.4392699193692549 18 0.62309581808855541 24 0.62309581808855541;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 10;
	setAttr -s 6 ".kot[0:5]"  1 9 9 9 9 10;
	setAttr -s 6 ".kix[0:5]"  1 0.99691283702850342 0.99833279848098755 
		0.99044609069824219 0.99422013759613037 1;
	setAttr -s 6 ".kiy[0:5]"  0 -0.078516244888305664 -0.057720322161912918 
		0.13790056109428406 0.1073610708117485 0;
	setAttr -s 6 ".kox[0:5]"  1 0.99691283702850342 0.99833279848098755 
		0.99044609069824219 0.99422013759613037 1;
	setAttr -s 6 ".koy[0:5]"  0 -0.078516244888305664 -0.057720322161912918 
		0.13790056109428406 0.1073610708117485 0;
createNode animCurveTA -n "Maugli_FKChest_M_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 -1.0403458882289476 10 -0.87218001275035928 
		14 -1.9909375847374837 18 -25.928322657740519 24 -25.928322657740519;
	setAttr -s 6 ".kit[0:5]"  1 9 9 1 9 3;
	setAttr -s 6 ".kot[0:5]"  1 9 9 1 9 3;
	setAttr -s 6 ".kix[0:5]"  1 0.99895894527435303 0.99807018041610718 
		0.96044725179672241 0.6236727237701416 1;
	setAttr -s 6 ".kiy[0:5]"  0 -0.045619696378707886 -0.062096018344163895 
		-0.27846208214759827 -0.78168553113937378 0;
	setAttr -s 6 ".kox[0:5]"  1 0.99895894527435303 0.99807018041610718 
		0.96044725179672241 0.6236727237701416 1;
	setAttr -s 6 ".koy[0:5]"  0 -0.045619696378707886 -0.062096018344163895 
		-0.27846208214759827 -0.78168553113937378 0;
createNode animCurveTA -n "Maugli_FKChest_M_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 -4.2527416123670108 10 -6.6236033816524884 
		14 -8.4082039437312961 18 -6.0685067306724134 24 -6.0685067306724134;
	setAttr -s 6 ".kit[0:5]"  1 9 9 10 9 10;
	setAttr -s 6 ".kot[0:5]"  1 9 9 10 9 10;
	setAttr -s 6 ".kix[0:5]"  1 0.94479405879974365 0.96494793891906738 
		1 0.99257951974868774 1;
	setAttr -s 6 ".kiy[0:5]"  0 -0.32766503095626831 -0.26244112849235535 
		0 0.12159719318151474 0;
	setAttr -s 6 ".kox[0:5]"  1 0.94479405879974365 0.96494793891906738 
		1 0.99257951974868774 1;
	setAttr -s 6 ".koy[0:5]"  0 -0.32766503095626831 -0.26244112849235535 
		0 0.12159719318151474 0;
createNode animCurveTA -n "Maugli_FKChest_M_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0.59401158357065487 10 -0.15046338571986334 
		14 -2.8750808109926238 18 2.6635387051032011 24 2.6635387051032011;
	setAttr -s 6 ".kit[0:5]"  3 9 9 10 9 10;
	setAttr -s 6 ".kot[0:5]"  3 9 9 10 9 10;
createNode animCurveTA -n "Maugli_FKNeck_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 24.862696821213692 6 39.825453471573283 
		10 47.291409145508347 14 32.259257133610909 18 18.802713383640466 24 22.628337533497174;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 3;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 3;
createNode animCurveTA -n "Maugli_FKNeck_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 2.3863774418401911 10 4.2270582143056261 
		14 3.4684927109536616 18 3.6826813105759961 24 3.6826813105759961;
	setAttr -s 6 ".kit[0:5]"  1 9 10 10 9 10;
	setAttr -s 6 ".kot[0:5]"  1 9 10 10 9 10;
	setAttr -s 6 ".kix[0:5]"  1 0.97637152671813965 1 1 0.99993717670440674 
		1;
	setAttr -s 6 ".kiy[0:5]"  0 0.2160985916852951 0 0 0.011214184574782848 
		0;
	setAttr -s 6 ".kox[0:5]"  1 0.97637152671813965 1 1 0.99993717670440674 
		1;
	setAttr -s 6 ".koy[0:5]"  0 0.2160985916852951 0 0 0.011214184574782848 
		0;
createNode animCurveTA -n "Maugli_FKNeck_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 1.4898181761699851 10 -0.94719257045324179 
		14 0.38819207362840269 18 2.2991021693981635 24 2.2991021693981635;
	setAttr -s 6 ".kit[0:5]"  1 10 10 9 9 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 9 9 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 0.97816485166549683 0.99503183364868164 
		1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0.20783019065856934 0.099557928740978241 
		0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 0.97816485166549683 0.99503183364868164 
		1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0.20783019065856934 0.099557928740978241 
		0;
createNode animCurveTU -n "Maugli_FKHead_M_Global";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 10 6 10 10 10 14 10 18 10 24 10;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_FKHead_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -10.280351451802797 6 74.922797615648264 
		10 44.830190674154942 14 16.31787682475257 18 -7.8426637274840703 24 -7.8426637274840703;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 9 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 9 10;
	setAttr -s 6 ".kix[0:5]"  1 0.32744532823562622 0.25227707624435425 
		0.27858749032020569 0.62013393640518188 1;
	setAttr -s 6 ".kiy[0:5]"  0 0.94487011432647705 -0.9676550030708313 
		-0.96041089296340942 -0.784496009349823 0;
	setAttr -s 6 ".kox[0:5]"  1 0.32744532823562622 0.25227707624435425 
		0.27858749032020569 0.62013393640518188 1;
	setAttr -s 6 ".koy[0:5]"  0 0.94487011432647705 -0.9676550030708313 
		-0.96041089296340942 -0.784496009349823 0;
createNode animCurveTA -n "Maugli_FKHead_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -6.477995107503193 6 -7.1720675066585962 
		10 -3.4389606427902177 14 -8.2863795683982584 18 -7.5490945101966842 24 -7.5490945101966842;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 9 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 9 10;
createNode animCurveTA -n "Maugli_FKHead_M_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -3.6805445729346604 6 2.24319444631523 
		10 14.536275286824466 14 15.488327420884058 18 5.461028169262887 24 5.461028169262887;
	setAttr -s 6 ".kit[0:5]"  1 10 9 9 9 10;
	setAttr -s 6 ".kot[0:5]"  1 10 9 9 9 10;
	setAttr -s 6 ".kix[0:5]"  1 0.7236139178276062 0.75560480356216431 
		0.85977035760879517 0.88538765907287598 1;
	setAttr -s 6 ".kiy[0:5]"  0 0.69020497798919678 0.65502774715423584 
		-0.51068079471588135 -0.46485346555709839 0;
	setAttr -s 6 ".kox[0:5]"  1 0.7236139178276062 0.75560480356216431 
		0.85977035760879517 0.88538765907287598 1;
	setAttr -s 6 ".koy[0:5]"  0 0.69020497798919678 0.65502774715423584 
		-0.51068079471588135 -0.46485346555709839 0;
createNode animCurveTU -n "Maugli_Main_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_Main_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_Main_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_Main_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_Main_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_Main_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_Main_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_Main_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_Main_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_Main_visibility";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kot[0:5]"  1 5 5 5 5 5;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0 0 0 0 0;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_kolchan_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -16.498609615445837 6 -27.324927311932161 
		10 -19.779715092460261 14 -9.0488105953257847 18 -35.154284410145785 24 -16.498609615445837;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 0.9855615496635437 0.64139199256896973 
		0.70489591360092163 0.93163228034973145 0.52339291572570801;
	setAttr -s 6 ".kiy[0:5]"  0 -0.16931776702404022 0.76721328496932983 
		-0.70931077003479004 -0.36340230703353882 0.85209143161773682;
	setAttr -s 6 ".kox[0:5]"  1 0.9855615496635437 0.64139199256896973 
		0.70489591360092163 0.93163228034973145 0.52339297533035278;
	setAttr -s 6 ".koy[0:5]"  0 -0.16931776702404022 0.76721328496932983 
		-0.70931077003479004 -0.36340230703353882 0.85209149122238159;
createNode animCurveTA -n "Maugli_kolchan_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -6.4006181765439756 6 -6.4896185883952109 
		10 0.61480938598240964 14 -3.680168878204765 18 -5.4896312869253512 24 -6.4006181765439756;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 0.98351144790649414 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0.18084618449211121 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 0.98351144790649414 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0.18084618449211121 0 0 0;
createNode animCurveTA -n "Maugli_kolchan_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1.8111494521402616 6 -0.22012133985929586 
		10 -9.8670704958912268 14 -5.2888216653592703 18 3.7605556309723953 24 1.8111494521402616;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  0.9406774640083313 1 0.94913434982299805 
		0.74628275632858276 1 1;
	setAttr -s 6 ".kiy[0:5]"  0.33930215239524841 0 -0.31487122178077698 
		0.66562902927398682 0 0;
	setAttr -s 6 ".kox[0:5]"  0.9406774640083313 1 0.94913434982299805 
		0.74628275632858276 1 1;
	setAttr -s 6 ".koy[0:5]"  0.33930209279060364 0 -0.31487122178077698 
		0.66562902927398682 0 0;
createNode animCurveTA -n "Maugli_yashik_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_yashik_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_yashik_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_yashik_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_yashik_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_yashik_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_l_ear_control_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -13.930813049671032 6 -13.930813049671032 
		10 -13.930813049671032 14 -13.930813049671032 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_l_ear_control_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -33.163858461841365 6 -33.163858461841365 
		10 -33.163858461841365 14 -33.163858461841365 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_l_ear_control_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 76.592706690898311 6 76.592706690898311 
		10 76.592706690898311 14 76.592706690898311 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_r_ear_control1_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -13.924689998798502 6 -13.924689998798502 
		10 -13.924689998798502 14 -13.924689998798502 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_r_ear_control1_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 26.777110246701266 6 26.777110246701266 
		10 26.777110246701266 14 26.777110246701266 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_r_ear_control1_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -76.966651924884573 6 -76.966651924884573 
		10 -76.966651924884573 14 -76.966651924884573 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_jaw_C_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 17.748661559885502 14 13.376582921133988 
		18 8.7165193087420985 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 0.75239193439483643 0.86083483695983887 
		0.81907939910888672 0.79590910673141479;
	setAttr -s 6 ".kiy[0:5]"  0 0 0.65871566534042358 -0.5088844895362854 
		-0.57368010282516479 -0.60541611909866333;
	setAttr -s 6 ".kox[0:5]"  1 1 0.75239193439483643 0.86083483695983887 
		0.81907939910888672 0.79590910673141479;
	setAttr -s 6 ".koy[0:5]"  0 0 0.65871566534042358 -0.5088844895362854 
		-0.57368010282516479 -0.60541611909866333;
createNode animCurveTA -n "Maugli_spear_control_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_spear_control_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_spear_control_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_spear_control_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.041982630251665931 6 0.041982630251665931 
		10 0.041982630251665931 14 0.041982630251665931 18 0.041982630251665931 24 0.041982630251665931;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_spear_control_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.05682005777595385 6 -0.05682005777595385 
		10 -0.05682005777595385 14 -0.05682005777595385 18 -0.05682005777595385 24 -0.05682005777595385;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_spear_control_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.19304667407551657 6 0.19304667407551657 
		10 0.19304667407551657 14 0.19304667407551657 18 0.19304667407551657 24 0.19304667407551657;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_spear_control_World_Hands";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegFrontBall_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegFrontBall_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.1 3 1.1 6 1.1 10 1.1 14 1.1 18 1.1 
		24 1.1;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.1 3 1.1 6 1.1 10 1.1 14 1.1 18 1.1 
		24 1.1;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_legAim";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10 3 10 6 10 10 10 14 10 18 10 24 10;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 25 3 25 6 25 10 25 14 25 18 25 24 25;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegFront_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 13.452853449395946 3 13.452853449395933 
		6 13.452853449395933 10 13.452853449395933 14 13.452853449395933 18 13.452853449395933 
		24 13.452853449395933;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegFront_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegFront_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -49.030994147612226 3 0 6 0 10 0 14 0 
		18 0 24 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_IKLegFront_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.6220354511696512 3 0 6 5.5511151231257852e-017 
		10 5.5511151231257852e-017 14 5.5511151231257852e-017 18 5.5511151231257852e-017 
		24 5.5511151231257852e-017;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_IKLegFront_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -1.6310299622119784 3 -1.2206937838789034 
		6 -0.78767523172948961 10 -0.78767523172948961 14 -0.78767523172948961 18 -0.78767523172948961 
		24 -0.78767523172948961;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 0.23074832558631897 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0.97301340103149414 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 0.23074832558631897 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0.97301340103149414 0 0 0 0 0;
createNode animCurveTL -n "Maugli_IKLegFront_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.21789294892402367 3 -0.077325821529500835 
		6 -0.077325821529500835 10 -0.077325821529500835 14 -0.077325821529500835 18 -0.077325821529500835 
		24 -0.077325821529500835;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegFront_L_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1.1 6 1.1 10 1.1 14 1.1 18 1.1 24 1.1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegFront_L_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1.1 6 1.1 10 1.1 14 1.1 18 1.1 24 1.1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegFront_L_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegFront_L_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegFront_L_legAim";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 10 6 10 10 10 14 10 18 10 24 10;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegFront_L_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 25 6 25 10 25 14 25 18 25 24 25;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegFront_L_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_IKLegFront_L_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegFront_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -4.3689304491953465 6 -4.3689304491953465 
		10 -4.3689304491953465 14 -4.3689304491953465 18 -4.3689304491953465 24 -4.3689304491953465;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegFront_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_IKLegFront_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_IKLegFront_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_IKLegFront_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -1.0172215739306112 6 -0.063844748963588188 
		10 -0.063844748963588188 14 -0.063844748963588188 18 -0.063844748963588188 24 -0.063844748963588188;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  0.1678348183631897 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0.98581510782241821 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.16061185300350189 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0.98701763153076172 0 0 0 0 0;
createNode animCurveTL -n "Maugli_IKLegFront_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.32739578435433486 6 -0.072835230653514785 
		10 -0.072835230653514785 14 -0.072835230653514785 18 -0.072835230653514785 24 -0.072835230653514785;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKLegFront_L_IKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKLegFront_L_FKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKLegFront_L_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 10 6 10 10 10 14 10 18 10 24 10;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKLegFront_R_IKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKLegFront_R_FKVis";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_FKIKLegFront_R_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 10 6 10 10 10 14 10 18 10 24 10;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_FKScapula_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_FKScapula_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_FKScapula_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_FKScapula_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -2.2204460492503131e-016 6 -2.2204460492503131e-016 
		10 -2.2204460492503131e-016 14 -2.2204460492503131e-016 18 -2.2204460492503131e-016 
		24 -2.2204460492503131e-016;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_FKScapula_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -1.1102230246251565e-016 6 -1.1102230246251565e-016 
		10 -1.1102230246251565e-016 14 -1.1102230246251565e-016 18 -1.1102230246251565e-016 
		24 -1.1102230246251565e-016;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_FKScapula_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 4.4408920985006262e-016 6 4.4408920985006262e-016 
		10 4.4408920985006262e-016 14 4.4408920985006262e-016 18 4.4408920985006262e-016 
		24 4.4408920985006262e-016;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_FKScapula_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_FKScapula_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "Maugli_FKScapula_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_FKScapula_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -1.1102230246251565e-016 6 -1.1102230246251565e-016 
		10 -1.1102230246251565e-016 14 -1.1102230246251565e-016 18 -1.1102230246251565e-016 
		24 -1.1102230246251565e-016;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_FKScapula_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -2.2204460492503131e-016 6 -2.2204460492503131e-016 
		10 -2.2204460492503131e-016 14 -2.2204460492503131e-016 18 -2.2204460492503131e-016 
		24 -2.2204460492503131e-016;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_FKScapula_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -2.2204460492503131e-016 6 -2.2204460492503131e-016 
		10 -2.2204460492503131e-016 14 -2.2204460492503131e-016 18 -2.2204460492503131e-016 
		24 -2.2204460492503131e-016;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "Maugli_PoleLegFront_L_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 10 6 10 10 10 14 10 18 10 24 10;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_PoleLegFront_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.41598215137401412 6 0.17401169588200627 
		10 0.34369246973235407 14 0.34369246973235407 18 0.34369246973235407 24 0.34369246973235407;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  0.16183418035507202 0.97728216648101807 
		1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  -0.98681795597076416 -0.21194224059581757 
		0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.16183418035507202 0.97728216648101807 
		1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  -0.98681795597076416 -0.21194224059581757 
		0 0 0 0;
createNode animCurveTL -n "Maugli_PoleLegFront_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.023081803484815026 6 -0.019633497903617798 
		10 0.08732959492146955 14 0.08732959492146955 18 0.08732959492146955 24 0.08732959492146955;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  0.35471221804618835 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  -0.93497556447982788 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.35471221804618835 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  -0.93497556447982788 0 0 0 0 0;
createNode animCurveTL -n "Maugli_PoleLegFront_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.022989116006067845 6 -0.143759011563967 
		10 -0.27202670267238233 14 -0.27202670267238233 18 -0.27202670267238233 24 -0.27202670267238233;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  0.61895620822906494 0.80110883712768555 
		1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0.78542554378509521 -0.59851866960525513 
		0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.61895620822906494 0.80110883712768555 
		1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0.78542554378509521 -0.59851866960525513 
		0 0 0 0;
createNode animCurveTU -n "Maugli_PoleLegFront_R_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 10 6 10 10 10 14 10 18 10 24 10;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "Maugli_PoleLegFront_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.31678960075780738 6 0.25617474354487202 
		10 0.31678960075780738 14 0.31678960075780738 18 0.31678960075780738 24 0.31678960075780738;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  0.46685934066772461 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  -0.88433158397674561 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.46685931086540222 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  -0.88433152437210083 0 0 0 0 0;
createNode animCurveTL -n "Maugli_PoleLegFront_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.11971028970415042 6 -0.16599328306430033 
		10 -0.11971028970415042 14 -0.11971028970415042 18 -0.11971028970415042 24 -0.11971028970415042;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  0.56870448589324951 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  -0.82254201173782349 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.56870448589324951 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  -0.82254201173782349 0 0 0 0 0;
createNode animCurveTL -n "Maugli_PoleLegFront_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.0005730959429199018 6 -0.025166128084249395 
		10 0.0005730959429199018 14 0.0005730959429199018 18 0.0005730959429199018 24 0.0005730959429199018;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  0.7792123556137085 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  -0.62676000595092773 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.7792123556137085 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  -0.62676000595092773 0 0 0 0 0;
createNode animCurveTL -n "curve1_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "curve1_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "curve1_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "curve1_visibility";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "curve1_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "curve1_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "curve1_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "curve1_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "curve1_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "curve1_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "IKLegBackBall_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  6 0 10 0 14 0 18 0;
createNode animCurveTA -n "IKLegBackBall_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  6 0 10 0 14 0 18 0;
createNode animCurveTA -n "IKLegBackBall_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  6 0 10 0 14 0 18 0;
createNode animCurveTA -n "IKLegBackBall_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  6 0 10 0 14 0 18 0;
createNode animCurveTA -n "IKLegFrontBall_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  6 0 10 0 14 0 18 0;
createNode animCurveTA -n "IKLegFrontBall_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  6 0 10 0 14 0 18 0;
createNode animCurveTA -n "IKLegFrontBall_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  6 0 10 0 14 0 18 0;
createNode animCurveTA -n "IKLegFrontBall_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  6 0 10 0 14 0 18 0;
createNode animCurveTL -n "IKXSplineTailCurve_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 4.0142992214232583e-036 6 4.0142992214232583e-036 
		10 4.0142992214232583e-036 14 4.0142992214232583e-036 18 4.0142992214232583e-036 
		24 4.0142992214232583e-036;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "IKXSplineTailCurve_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "IKXSplineTailCurve_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 0 10 0 14 0 18 0 24 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "IKXSplineTailCurve_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -1.272221872585407e-014 6 -1.272221872585407e-014 
		10 -1.272221872585407e-014 14 -1.272221872585407e-014 18 -1.272221872585407e-014 
		24 -1.272221872585407e-014;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "IKXSplineTailCurve_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1.2722218725854067e-014 6 1.2722218725854067e-014 
		10 1.2722218725854067e-014 14 1.2722218725854067e-014 18 1.2722218725854067e-014 
		24 1.2722218725854067e-014;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "IKXSplineTailCurve_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 2.8249000307521015e-030 6 2.8249000307521015e-030 
		10 2.8249000307521015e-030 14 2.8249000307521015e-030 18 2.8249000307521015e-030 
		24 2.8249000307521015e-030;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "IKXSplineTailCurve_M_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "IKXSplineTailCurve_M_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "IKXSplineTailCurve_M_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 10 1 14 1 18 1 24 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "IKLegBall_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  6 0 10 0 14 0 18 0;
createNode animCurveTA -n "IKLegBall_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  6 0 10 0 14 0 18 0;
createNode animCurveTA -n "IKLegBall_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  6 0 10 0 14 0 18 0;
createNode animCurveTA -n "IKLegBall_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  6 0 10 0 14 0 18 0;
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
connectAttr "blockedSource.cl" "clipLibrary1.sc[0]";
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
// End of blocked.ma
