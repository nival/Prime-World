//Maya ASCII 2008 scene
//Name: death.ma
//Last modified: Wed, Jan 27, 2010 02:24:08 PM
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
createNode animClip -n "deathSource";
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
	setAttr -s 9 ".ktv[0:8]"  0 0 4 0 10 0 15 0 21 0 27 0 34 0 41 0 45 
		0;
createNode animCurveTA -n "Maugli_Center_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 4 4.3321296656265869 10 0 15 10.864068325655875 
		21 15.765990662282128 27 20.458273295837323 34 18.967767826310094 37 19.420679761616721 
		41 18.967767826310094 45 18.967767826310094;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "Maugli_Center_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 4 -5.4673076704163268 10 0 15 -29.550630210121707 
		21 -24.144192222258891 27 33.355278756355162 34 70.251972820686802 37 72.019661954125596 
		41 70.251972820686802 45 70.251972820686802;
	setAttr -s 10 ".kit[6:9]"  1 10 10 10;
	setAttr -s 10 ".kot[6:9]"  1 10 10 10;
	setAttr -s 10 ".kix[6:9]"  0.95857000350952148 1 1 1;
	setAttr -s 10 ".kiy[6:9]"  0.28485706448554993 0 0 0;
	setAttr -s 10 ".kox[6:9]"  0.95857006311416626 1 1 1;
	setAttr -s 10 ".koy[6:9]"  0.28485703468322754 0 0 0;
createNode animCurveTA -n "Maugli_Center_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 4.0494833724385515 4 -13.914869521011555 
		10 4.0494833724385515 15 -2.050131371344913 21 1.5820041970111325 27 14.743126347154057 
		34 15.468319536320692 37 14.887108177996385 41 15.468319536320692 45 15.468319536320692;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "Maugli_Center_M_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 4 0 10 0 15 0 21 -0.013715377637763367 
		27 -0.16632831012796087 34 -0.3892530198302574 37 -0.36372692378704752 41 -0.3892530198302574 
		45 -0.3892530198302574;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 1 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 1 10 10 10 
		10 10;
	setAttr -s 10 ".kix[4:9]"  0.99658924341201782 0.75570458173751831 
		1 1 1 1;
	setAttr -s 10 ".kiy[4:9]"  -0.08252263069152832 -0.65491271018981934 
		0 0 0 0;
	setAttr -s 10 ".kox[4:9]"  0.99658924341201782 0.75570458173751831 
		1 1 1 1;
	setAttr -s 10 ".koy[4:9]"  -0.082522615790367126 -0.65491271018981934 
		0 0 0 0;
createNode animCurveTL -n "Maugli_Center_M_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 4 0 10 0 15 0 21 -0.055801169751892532 
		27 0.090617262679376462 34 0.26609558421786439 37 0.25975755475201517 41 0.26609558421786439 
		45 0.26609558421786439;
createNode animCurveTL -n "Maugli_Center_M_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 4 0 10 0 15 0 21 -0.14717675424582116 
		27 0.67278273308550995 34 0.98190698159471235 37 0.96911770688284349 41 0.98190698159471235 
		45 0.98190698159471235;
createNode animCurveTU -n "Maugli_Fingers_L_Man_MiddleFingerCurl";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBall_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegToe_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegToe_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegToe_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTU -n "Maugli_FKIKLeg_L_Man_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLeg_L_Man_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLeg_L_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 11 10 16 10 21 10 27 10 
		45 10;
createNode animCurveTA -n "Maugli_IKLegHeel_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegHeel_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegHeel_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTL -n "Maugli_PoleLeg_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 6 0 11 -0.14096260039734482 16 
		-0.18175315856466054 21 0 27 -0.66291505467635214 34 -0.80150906782825471 45 -0.80150906782825471;
createNode animCurveTL -n "Maugli_PoleLeg_L_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 6 0 11 -0.065116787317671024 16 
		-0.10303403284786755 21 0 27 -0.13029948311726505 34 -0.3993975853545717 45 -0.3993975853545717;
createNode animCurveTL -n "Maugli_PoleLeg_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 6 0 11 -0.067937975625204955 16 
		-0.065651194441375224 21 0 27 0.49682189773890478 34 0.31096899368115488 45 0.31096899368115488;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 25 3 25 6 25 11 25 16 25 21 25 27 25 
		45 25;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_toe";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_IKLeg_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -5.0105185448650458 3 -5.0105185448650458 
		6 -5.0105185448650458 11 -5.0105185448650458 16 -22.798767958703976 21 -22.798767958703976 
		27 -22.798767958703976 45 -22.798767958703976;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_IKLeg_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -6.3694432300697281 3 -6.3694432300697281 
		6 -6.3694432300697281 11 -6.3694432300697281 16 4.7036692594846796 21 4.7036692594846796 
		27 4.7036692594846796 45 4.7036692594846796;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_IKLeg_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 13.378201002477269 3 13.378201002477269 
		6 13.378201002477269 11 13.378201002477269 16 4.3399302753842548 21 4.3399302753842548 
		27 4.3399302753842548 45 4.3399302753842548;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKLeg_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.069000150376690925 3 0.069000150376690925 
		6 0.069000150376690925 11 0.069000150376690925 16 0.41127132054127641 21 0.41127132054127641 
		27 0.41127132054127641 45 0.41127132054127641;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKLeg_L_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.015303353529604964 3 -0.015303353529604964 
		6 -0.015303353529604964 11 -0.015303353529604964 16 0.14248448627580768 21 0.14248448627580768 
		27 0.14248448627580768 45 0.14248448627580768;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKLeg_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.16760982461393598 3 0.16760982461393598 
		6 0.16760982461393598 11 0.16760982461393598 16 0.066371420369481085 21 0.066371420369481085 
		27 0.066371420369481085 45 0.066371420369481085;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_FKIKArm_L_Man_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKArm_L_Man_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKArm_L_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 11 10 16 10 21 10 27 10 
		45 10;
createNode animCurveTU -n "Maugli_PoleArm_L_Man_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 4 10 10 10 15 10 21 10 27 10 34 10 
		45 10;
createNode animCurveTL -n "Maugli_PoleArm_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.39549705228612952 4 -0.075472120826410694 
		10 0.10610309361019563 15 -0.061626182266185457 21 0.47230265737033245 27 0.39549705228612952 
		34 0.16454061135135298 45 0.16454061135135298;
createNode animCurveTL -n "Maugli_PoleArm_L_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.86201805279910448 4 -0.85344631861841869 
		10 -0.6241771717282345 15 -0.81470662116603698 21 -0.87721297754370575 27 -0.86201805279910448 
		34 -0.69394122366198896 45 -0.69394122366198896;
createNode animCurveTL -n "Maugli_PoleArm_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.30818663726222251 4 -0.2878949573327792 
		10 -0.20955221790444631 15 0.012250508502870325 21 0.023274045799151009 27 -0.30818663726222251 
		34 0.070185004311518015 45 0.070185004311518015;
createNode animCurveTU -n "Maugli_IKArm_L_Man_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 4 1 10 1 15 1 21 1 27 1 31 1 34 1 45 
		1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "Maugli_IKArm_L_Man_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 4 1 10 1 15 1 21 1 27 1 31 1 34 1 45 
		1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "Maugli_IKArm_L_Man_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 4 0 10 0 15 0 21 0 27 0 31 0 34 0 45 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "Maugli_IKArm_L_Man_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 4 0 10 0 15 0 21 0 27 0 31 0 34 0 45 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "Maugli_IKArm_L_Man_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 4 0 10 0 15 0 21 0 27 0 31 0 34 0 45 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "Maugli_IKArm_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -97.78067605427789 4 -97.78067605427789 
		10 16.446071177491525 15 -56.569428989422811 21 -40.535225926921591 27 -62.832080131539541 
		31 -88.100836955926965 34 -88.100836955926965 45 -88.100836955926965;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "Maugli_IKArm_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 10.92155845877172 4 10.92155845877172 
		10 32.230294438298749 15 -34.677532247971172 21 -36.852646903853653 27 33.958558709730148 
		31 -22.357811129405139 34 -22.357811129405139 45 -22.357811129405139;
	setAttr -s 9 ".kit[0:8]"  9 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  9 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "Maugli_IKArm_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 14.178018067197163 4 14.178018067197163 
		10 -36.556697624334539 15 -44.619143794939134 21 -36.219173631513719 27 -9.1334696952913834 
		31 -4.4787786032802028 34 -4.4787786032802028 45 -4.4787786032802028;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "Maugli_IKArm_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.79120002893813179 4 -0.36761099367231642 
		10 -0.83217626394129485 15 0.21585964487490289 21 -0.36913549841503573 27 -0.98189277484030524 
		31 -1.1308602237079404 34 -1.1426244777505743 45 -1.1426244777505743;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "Maugli_IKArm_L_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.30360130511963851 4 -0.35017158690642175 
		10 0.2465014471589963 15 0.16711862617473477 21 -0.42773925411020408 27 -0.57936724666252315 
		31 -0.99863721348354451 34 -1.0938164585269714 45 -1.0938164585269714;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "Maugli_IKArm_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.80061447835185851 4 -0.8942523871122543 
		10 -0.37333758835609071 15 -0.59422231074424547 21 -0.60809131046201481 27 0.35636962331429872 
		31 0.89090585627293406 34 0.91459393772233799 45 0.91459393772233799;
	setAttr -s 9 ".kit[0:8]"  9 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  9 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "Maugli_Fingers_R_Man_MiddleFingerCurl";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 6 0 9 0 11 -2 16 -2 21 -2 27 -2 
		45 0;
	setAttr -s 9 ".kit[5:8]"  1 1 1 10;
	setAttr -s 9 ".kot[5:8]"  1 1 1 10;
	setAttr -s 9 ".kix[5:8]"  1 1 1 0.28734788298606873;
	setAttr -s 9 ".kiy[5:8]"  0 0 0 0.95782625675201416;
	setAttr -s 9 ".kox[5:8]"  1 1 1 0.28734791278839111;
	setAttr -s 9 ".koy[5:8]"  0 0 0 0.95782631635665894;
createNode animCurveTU -n "Maugli_FKIKSpine_M_Man_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKSpine_M_Man_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKSpine_M_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBall_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegToe_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegToe_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegToe_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegHeel_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegHeel_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegHeel_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTU -n "Maugli_FKIKLeg_R_Man_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLeg_R_Man_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLeg_R_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 11 10 16 10 21 10 27 10 
		45 10;
createNode animCurveTL -n "Maugli_PoleLeg_R_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 -0.33142020562531788 
		45 -0.33142020562531788;
createNode animCurveTL -n "Maugli_PoleLeg_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 -0.23301113531204237 
		45 -0.23301113531204237;
createNode animCurveTL -n "Maugli_PoleLeg_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0.51063726801875531 
		45 0.51063726801875531;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 41 1;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 41 1;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 41 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 41 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 25 3 25 6 25 11 25 16 25 21 25 27 25 
		41 25;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 41 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_toe";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 41 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 41 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_IKLeg_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 6 0 11 0 16 0 21 0 27 -22.360860331731672 
		34 -12.908127849532134 37 -16.436928551654358 41 -12.908127849532134;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "Maugli_IKLeg_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 6 0 11 0 16 0 21 0 27 -11.291595308798138 
		34 32.344505786457084 37 28.985112002184767 41 32.344505786457084;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "Maugli_IKLeg_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 6 0 11 0 16 0 21 0 27 -50.884236829233885 
		34 -42.230377351509979 37 -43.081924017492703 41 -42.230377351509979;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "Maugli_IKLeg_R_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0.77569750021774686 
		34 1.0627865299635459 37 1.1007347304311415 41 1.1008703138760447;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "Maugli_IKLeg_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 6 0 11 0 16 0 21 0 27 -0.099480578781944509 
		34 0.14381631102981668 37 0.14921092879984788 41 0.16863857056690981;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "Maugli_IKLeg_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 6 0 11 0 16 0 21 0 27 -0.0060213524330821255 
		34 0.18210052967832321 37 0.18313315449865991 41 0.22754089837812766;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "Maugli_FKIKArm_R_Man_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKArm_R_Man_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKArm_R_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 11 10 16 10 21 10 27 10 
		45 10;
createNode animCurveTU -n "Maugli_PoleArm_R_Man_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10 4 10 10 10 15 10 21 10 27 10 45 10;
createNode animCurveTL -n "Maugli_PoleArm_R_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 10 0 15 0 21 0.28572818030963443 
		27 0.40712179560313078 34 0.55864906614291632 45 0.55864906614291632;
createNode animCurveTL -n "Maugli_PoleArm_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 10 0 15 0 21 -0.5026343622347561 
		27 -0.62447877108605809 34 -0.85925474239578836 45 -0.85925474239578836;
createNode animCurveTL -n "Maugli_PoleArm_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1.1102230246251565e-016 4 0 10 0 15 0 
		21 -0.015723601661275913 27 0.38539029110171147 34 -0.24083501344441371 45 -0.24083501344441371;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTU -n "Maugli_IKArm_R_Man_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 10 1 15 1 21 1 27 1 36 1 45 1;
createNode animCurveTU -n "Maugli_IKArm_R_Man_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 10 1 15 1 21 1 27 1 36 1 45 1;
createNode animCurveTU -n "Maugli_IKArm_R_Man_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 10 0 15 0 21 0 27 0 36 0 45 0;
createNode animCurveTU -n "Maugli_IKArm_R_Man_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 10 0 15 0 21 0 27 0 36 0 45 0;
createNode animCurveTU -n "Maugli_IKArm_R_Man_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 10 0 15 0 21 0 27 0 36 0 45 0;
createNode animCurveTA -n "Maugli_IKArm_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -12.754512848885321 10 -13.352295017594962 
		15 0.24329853142903254 21 76.138103151846479 27 54.081659974886719 30 58.938265951826679 
		36 83.263375055197272 45 83.263375055197272;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_IKArm_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -51.071041253431346 10 -52.138012194106842 
		15 -42.504940373147015 21 -35.33320988283085 27 -18.35928002025695 30 -5.6358700700223183 
		36 -27.12111077309002 45 -27.12111077309002;
	setAttr -s 8 ".kit[0:7]"  9 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  9 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_IKArm_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -30.429381170308442 10 -36.896656024303091 
		15 -43.780269290602838 21 5.2760657835054783 27 -9.8349734761502781 30 -45.075829433251322 
		36 -18.694701785942616 45 -18.694701785942616;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKArm_R_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.50891155850440861 10 -0.59350213003195895 
		15 -0.76103521099558524 21 -0.65361938836548195 27 -0.73820179128246421 30 -0.75041704356637318 
		36 -1.5003690318512923 40 -1.4525608641871106 45 -1.5070029244642291;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 3 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 3 10 
		3;
createNode animCurveTL -n "Maugli_IKArm_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.17073023409560481 10 0.048868739911723656 
		15 -0.4192811496406641 21 -0.73786165601069431 27 -0.86772582287326694 30 -0.77885223278560978 
		36 -0.84427643289227639 40 -0.88312779236316929 45 -0.89794824993313715;
createNode animCurveTL -n "Maugli_IKArm_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.44722353666474202 10 0.43629396974439016 
		15 0.0022600585059551859 21 0.87230109723021976 27 1.6132428103343568 30 2.2191350130151966 
		36 2.9862471172217142 40 2.9664781908997817 45 2.9996048862712716;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "Maugli_FKScapula_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -7.1990267140314277 3 -7.1990267140314277 
		6 -6.133808520202642 11 -16.54044743712188 16 -7.1990267140314277 21 -7.1990267140314277 
		27 -7.1990267140314277 34 52.987745903463782 45 52.987745903463782;
createNode animCurveTA -n "Maugli_FKScapula_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 9.9598426785175036 3 9.9598426785175036 
		6 -17.430277860594195 11 -12.798203314220094 16 9.9598426785175036 21 9.9598426785175036 
		27 9.9598426785175036 34 -37.107892296562184 45 -37.107892296562184;
createNode animCurveTA -n "Maugli_FKScapula_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -7.1981747374653153 3 -7.1981747374653153 
		6 4.1583713246915845 11 -4.2509584576183101 16 -7.1981747374653153 21 -7.1981747374653153 
		27 -7.1981747374653153 34 -9.4837731969350667 45 -9.4837731969350667;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "Maugli_FKScapula_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTL -n "Maugli_FKScapula_L_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTL -n "Maugli_FKScapula_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -5.5511151231257827e-017 3 -5.5511151231257827e-017 
		6 -5.5511151231257827e-017 11 -5.5511151231257827e-017 16 -5.5511151231257827e-017 
		21 -5.5511151231257827e-017 27 -5.5511151231257827e-017 45 -5.5511151231257827e-017;
createNode animCurveTA -n "Maugli_FKMiddleFinger1_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 17.622819694952526 3 17.622819694952526 
		6 17.622819694952526 11 17.622819694952526 16 17.622819694952526 21 17.622819694952526 
		27 17.622819694952526 45 17.622819694952526;
createNode animCurveTA -n "Maugli_FKMiddleFinger2_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -23.252905752704581 3 -23.252905752704581 
		6 -23.252905752704581 11 -23.252905752704581 16 -23.252905752704581 21 -23.252905752704581 
		27 -23.252905752704581 45 -23.252905752704581;
createNode animCurveTA -n "Maugli_FKMiddleFinger3_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_FKThumbFinger1_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -10.372922440313587 3 -10.372922440313587 
		6 -10.372922440313587 11 -10.372922440313587 16 -10.372922440313587 21 -10.372922440313587 
		27 -10.372922440313587 45 -10.372922440313587;
createNode animCurveTA -n "Maugli_FKThumbFinger1_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 2.7620263328639107 3 2.7620263328639107 
		6 2.7620263328639107 11 2.7620263328639107 16 2.7620263328639107 21 2.7620263328639107 
		27 2.7620263328639107 45 2.7620263328639107;
createNode animCurveTA -n "Maugli_FKThumbFinger1_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -32.466562028725463 3 -32.466562028725463 
		6 -32.466562028725463 11 -32.466562028725463 16 -32.466562028725463 21 -32.466562028725463 
		27 -32.466562028725463 45 -32.466562028725463;
createNode animCurveTA -n "Maugli_FKThumbFinger2_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -26.277332307519721 3 -26.277332307519721 
		6 -26.277332307519721 11 -26.277332307519721 16 -26.277332307519721 21 -26.277332307519721 
		27 -26.277332307519721 45 -26.277332307519721;
createNode animCurveTA -n "Maugli_FKBackA_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 7.8357327658317191 4 17.248450542084385 
		10 -24.425326351202724 15 -13.005385514867285 21 13.697420921434485 27 2.0917405683571464 
		34 11.175234590474879 45 11.175234590474879;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_FKBackA_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -7.5265731098501263 4 -0.87710349622333905 
		10 -11.292922030695779 15 -12.621458367445898 21 -13.800970836302934 27 2.9982838197585444 
		34 12.96608495122573 45 12.96608495122573;
	setAttr -s 8 ".kit[0:7]"  3 10 1 9 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 1 9 10 10 10 10;
	setAttr -s 8 ".kix[2:7]"  0.94709181785583496 0.99294912815093994 
		1 0.68005460500717163 1 1;
	setAttr -s 8 ".kiy[2:7]"  -0.32096299529075623 -0.11854109913110733 
		0 0.73316144943237305 0 0;
	setAttr -s 8 ".kox[2:7]"  0.94709175825119019 0.99294912815093994 
		1 0.68005460500717163 1 1;
	setAttr -s 8 ".koy[2:7]"  -0.320963054895401 -0.11854109913110733 
		0 0.73316144943237305 0 0;
createNode animCurveTA -n "Maugli_FKBackA_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -5.4975000363152615 4 -9.9778474538883106 
		10 -0.42948405272876217 15 -0.36657935217322379 21 -7.2264187066682011 27 -6.2476790335437746 
		34 -4.7838227672819773 45 -4.7838227672819773;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 9 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 9 10 10;
createNode animCurveTA -n "Maugli_FKBackB_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 2.7266862105714793 4 15.609703031349113 
		10 1.1921476908087498 15 10.958953177682952 21 4.6313195693641029 27 2.3747946364061097 
		34 7.3389994465318917 45 7.3389994465318917;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 9 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 9 10 10 10;
createNode animCurveTA -n "Maugli_FKBackB_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.24259990801533335 4 1.7600300068148671 
		10 3.5324706863754254 15 4.9978139978900904 21 0.30279199337927054 27 28.362015803504377 
		34 0.74715924459570959 45 0.74715924459570959;
	setAttr -s 8 ".kit[0:7]"  3 9 9 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 9 9 10 10 10 10 10;
createNode animCurveTA -n "Maugli_FKBackB_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1.5001242681430698 4 -4.0123826310407598 
		10 9.2684378863868844 15 8.1301883675322291 21 10.90937563817964 27 -0.0062803675677883426 
		34 29.607137495286509 45 29.607137495286509;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_FKChest_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -12.769021381384317 4 19.182141498859519 
		10 -9.6746567166561448 15 5.5338913113835266 21 3.9448952989282882 27 7.3528721924020726 
		34 13.934159487075698 41 13.934159487075698 45 13.934159487075698;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "Maugli_FKChest_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 4.6070431346914544 4 -6.7968146610649542 
		10 7.3337125720176415 15 4.5465074773738161 21 -17.794307314075891 27 8.7205724761089645 
		34 8.9971292932046847 41 8.9971292932046847 45 8.9971292932046847;
	setAttr -s 9 ".kit[0:8]"  3 10 10 1 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 1 10 10 10 10 
		10;
	setAttr -s 9 ".kix[3:8]"  0.88496381044387817 0.98381620645523071 
		1 1 1 1;
	setAttr -s 9 ".kiy[3:8]"  -0.46565988659858704 0.17918042838573456 
		0 0 0 0;
	setAttr -s 9 ".kox[3:8]"  0.88496381044387817 0.98381620645523071 
		1 1 1 1;
	setAttr -s 9 ".koy[3:8]"  -0.46565991640090942 0.17918042838573456 
		0 0 0 0;
createNode animCurveTA -n "Maugli_FKChest_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 4.8308420450374907 4 4.9489294372616062 
		10 9.3871284169046767 15 9.2540775442837298 21 4.6528529320269705 27 -8.2334960117622709e-005 
		34 2.0398587290983792 37 6.9629921354106576 41 2.0398587290983792 45 2.0398587290983792;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 9 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 9 10 
		10 10;
createNode animCurveTA -n "Maugli_FKNeck_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 7.7390451519779058 10 -29.071290035454425 
		15 -29.205195992986273 21 0 27 -9.6061547205892044 34 33.157468289012776 45 33.157468289012776;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_FKNeck_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 -7.3866479212818703 10 -1.6350685156493336 
		15 -0.70376595642155604 21 0 27 18.635700129064897 34 -13.594231989246001 45 -13.594231989246001;
	setAttr -s 8 ".kit[0:7]"  3 10 1 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 1 10 10 10 10 10;
	setAttr -s 8 ".kix[2:7]"  0.99428999423980713 1 1 0.8771282434463501 
		1 1;
	setAttr -s 8 ".kiy[2:7]"  0.10671212524175644 0 0 -0.48025625944137573 
		0 0;
	setAttr -s 8 ".kox[2:7]"  0.99428999423980713 1 1 0.8771282434463501 
		1 1;
	setAttr -s 8 ".koy[2:7]"  0.10671212524175644 0 0 -0.48025625944137573 
		0 0;
createNode animCurveTA -n "Maugli_FKNeck_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 -10.123544420884651 10 -4.1112182536411135 
		15 3.2220540387584018 21 0 27 12.09259606537762 34 36.406499531901254 45 36.406499531901254;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_FKHead_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -6.9400884964770713 4 13.414722173731443 
		10 -31.033846465389328 15 -33.049572434909848 21 -6.9400884964770713 27 -31.576216945513185 
		34 -19.722108811448933 37 -11.778353983711492 41 -12.449532191393589 45 -12.449532191393589;
	setAttr -s 10 ".kit[0:9]"  3 10 1 10 10 10 1 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 1 10 10 10 1 10 
		10 10;
	setAttr -s 10 ".kix[2:9]"  0.94665020704269409 1 0.99793988466262817 
		0.88909482955932617 0.59115397930145264 1 1 1;
	setAttr -s 10 ".kiy[2:9]"  -0.32226306200027466 0 0.064154826104640961 
		-0.45772314071655273 0.80655878782272339 0 0 0;
	setAttr -s 10 ".kox[2:9]"  0.94665014743804932 1 0.99793988466262817 
		0.88909482955932617 0.59115403890609741 1 1 1;
	setAttr -s 10 ".koy[2:9]"  -0.32226306200027466 0 0.064154826104640961 
		-0.45772314071655273 0.80655872821807861 0 0 0;
createNode animCurveTA -n "Maugli_FKHead_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 3.508580449788079 4 -4.8521503324366089 
		10 -7.7143706490262538 15 -3.4929393085461027 21 3.508580449788079 27 21.067083549199094 
		34 21.37373819617045 37 28.308753636582118 41 20.893956568214215 45 20.893956568214215;
	setAttr -s 10 ".kit[0:9]"  9 1 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  9 1 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kix[1:9]"  0.88078129291534424 1 0.88203120231628418 
		0.68224859237670898 1 1 0.99935668706893921 1 1;
	setAttr -s 10 ".kiy[1:9]"  -0.47352328896522522 0 0.47119101881980896 
		0.73112022876739502 0 0 -0.035864494740962982 0 0;
	setAttr -s 10 ".kox[1:9]"  0.88078135251998901 1 0.88203120231628418 
		0.68224859237670898 1 1 0.99935668706893921 1 1;
	setAttr -s 10 ".koy[1:9]"  -0.47352316975593567 0 0.47119101881980896 
		0.73112022876739502 0 0 -0.035864494740962982 0 0;
createNode animCurveTA -n "Maugli_FKHead_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 5.0972336912670713 4 2.8211338050623969 
		10 -9.9777627856371147 15 -6.2104532704172284 21 5.0972336912670713 27 10.354087875963559 
		34 -25.687439130025204 37 -33.895846534689319 41 -27.615665325192886 45 -27.615665325192886;
	setAttr -s 10 ".kit[0:9]"  3 1 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 1 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kix[1:9]"  0.94118040800094604 0.9187016487121582 
		0.81247013807296753 0.8104705810546875 0.62778037786483765 0.39627283811569214 0.98975825309753418 
		1 1;
	setAttr -s 10 ".kiy[1:9]"  -0.33790451288223267 -0.39495217800140381 
		0.58300274610519409 0.58577936887741089 -0.77839052677154541 -0.91813278198242188 
		-0.14275379478931427 0 0;
	setAttr -s 10 ".kox[1:9]"  0.94118046760559082 0.9187016487121582 
		0.81247013807296753 0.8104705810546875 0.62778037786483765 0.39627283811569214 0.98975825309753418 
		1 1;
	setAttr -s 10 ".koy[1:9]"  -0.3379044234752655 -0.39495217800140381 
		0.58300274610519409 0.58577936887741089 -0.77839052677154541 -0.91813278198242188 
		-0.14275379478931427 0 0;
createNode animCurveTA -n "Maugli_FKScapula_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 3.6745332739058547 3 3.6745332739058547 
		6 0.48405934548617291 11 3.6745332739058547 16 3.6745332739058547 21 3.6745332739058547 
		27 0.2423970711608828 34 41.283969869909932 45 41.283969869909932;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "Maugli_FKScapula_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -6.3459812884849134 3 -6.3459812884849134 
		6 -23.862489129919876 11 -6.3459812884849134 16 -6.3459812884849134 21 -6.3459812884849134 
		27 0.10659116203328191 34 -3.6096164527779702 45 -3.6096164527779702;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "Maugli_FKScapula_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.71910078156005675 3 -0.71910078156005675 
		6 -4.815954351517294 11 -0.71910078156005675 16 -0.71910078156005675 21 -0.71910078156005675 
		27 -6.941630162440922 34 1.6407003392519379 45 1.6407003392519379;
createNode animCurveTL -n "Maugli_FKScapula_R_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -2.7755575615628914e-017 3 -2.7755575615628914e-017 
		6 -2.7755575615628914e-017 11 -2.7755575615628914e-017 16 -2.7755575615628914e-017 
		21 -2.7755575615628914e-017 27 -2.7755575615628914e-017 34 -2.7755575615628914e-017 
		45 -2.7755575615628914e-017;
createNode animCurveTL -n "Maugli_FKScapula_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 34 0 45 
		0;
createNode animCurveTL -n "Maugli_FKScapula_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 5.5511151231257827e-017 3 5.5511151231257827e-017 
		6 5.5511151231257827e-017 11 5.5511151231257827e-017 16 5.5511151231257827e-017 21 
		5.5511151231257827e-017 27 5.5511151231257827e-017 34 5.5511151231257827e-017 45 
		5.5511151231257827e-017;
createNode animCurveTA -n "Maugli_FKMiddleFinger1_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_FKMiddleFinger2_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -67.588216236699324 3 -67.588216236699324 
		6 -67.588216236699324 9 -67.588216236699324 11 -29.316125768745788 16 -29.316125768745788 
		21 -29.316125768745788 27 -29.316125768745788 45 -67.588216236699324;
	setAttr -s 9 ".kit[5:8]"  1 1 1 10;
	setAttr -s 9 ".kot[5:8]"  1 1 1 10;
	setAttr -s 9 ".kix[5:8]"  1 1 1 0.66824042797088623;
	setAttr -s 9 ".kiy[5:8]"  0 0 0 -0.74394536018371582;
	setAttr -s 9 ".kox[5:8]"  1 1 1 0.66824048757553101;
	setAttr -s 9 ".koy[5:8]"  0 0 0 -0.7439454197883606;
createNode animCurveTA -n "Maugli_FKMiddleFinger3_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -81.669521342510606 3 -81.669521342510606 
		6 -81.669521342510606 9 -81.669521342510606 11 -43.397430874557124 16 -43.397430874557124 
		21 -43.397430874557124 27 -43.397430874557124 45 -81.669521342510606;
	setAttr -s 9 ".kit[5:8]"  1 1 1 10;
	setAttr -s 9 ".kot[5:8]"  1 1 1 10;
	setAttr -s 9 ".kix[5:8]"  1 1 1 0.66824042797088623;
	setAttr -s 9 ".kiy[5:8]"  0 0 0 -0.74394536018371582;
	setAttr -s 9 ".kox[5:8]"  1 1 1 0.66824048757553101;
	setAttr -s 9 ".koy[5:8]"  0 0 0 -0.7439454197883606;
createNode animCurveTA -n "Maugli_FKThumbFinger1_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 25.665274764482422 3 25.665274764482422 
		6 25.665274764482422 11 25.665274764482422 16 25.665274764482422 21 25.665274764482422 
		27 25.665274764482422 45 25.665274764482422;
createNode animCurveTA -n "Maugli_FKThumbFinger1_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 36.541774445263137 3 36.541774445263137 
		6 36.541774445263137 11 36.541774445263137 16 36.541774445263137 21 36.541774445263137 
		27 36.541774445263137 45 36.541774445263137;
createNode animCurveTA -n "Maugli_FKThumbFinger1_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -67.421493922591793 3 -67.421493922591793 
		6 -67.421493922591793 11 -67.421493922591793 16 -67.421493922591793 21 -67.421493922591793 
		27 -67.421493922591793 45 -67.421493922591793;
createNode animCurveTA -n "Maugli_FKThumbFinger2_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 47.81080993924823 3 47.81080993924823 
		6 47.81080993924823 9 47.81080993924823 11 -12.129104140196551 16 -12.129104140196551 
		21 -12.129104140196551 27 -12.129104140196551 45 47.81080993924823;
	setAttr -s 9 ".kit[5:8]"  1 1 1 10;
	setAttr -s 9 ".kot[5:8]"  1 1 1 10;
	setAttr -s 9 ".kix[5:8]"  1 1 1 0.49751389026641846;
	setAttr -s 9 ".kiy[5:8]"  0 0 0 0.86745595932006836;
	setAttr -s 9 ".kox[5:8]"  1 1 1 0.49751392006874084;
	setAttr -s 9 ".koy[5:8]"  0 0 0 0.86745601892471313;
createNode animCurveTU -n "Maugli_Main_Man_visibility";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_Center_M_CenterBtwFeet";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_Center_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -8.4444129496952112 3 -8.4444129496952254 
		6 -8.4444129496952414 11 -8.4444129496952414 16 -15.42767604672405 21 -15.202203739940753 
		27 -15.202203739940753 45 -15.202203739940753;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_Center_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.96917688750520981 3 -0.96917688750520781 
		6 -0.96917688750520825 11 -0.96917688750520825 16 30.728449160098101 21 26.852622393322275 
		27 26.852622393322275 45 26.852622393322275;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_Center_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 3.1650958122187984 3 10.146167730746225 
		6 -7.8402182008459951 11 -7.8402182008459933 16 -2.9383159182288812 21 -3.9623821847995369 
		27 -3.9623821847995369 45 -3.9623821847995369;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTL -n "Maugli_Center_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.13106792216224994 3 -0.159299552263793 
		6 -0.5858359331897276 11 -0.77852835266771869 16 -1.5761653590344074 21 -1.6287048147677008 
		24 -1.5597501691660007 27 -1.6287048147677008 45 -1.6287048147677008;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 1 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 1 10 10 
		10;
	setAttr -s 9 ".kix[5:8]"  0.99951237440109253 1 1 1;
	setAttr -s 9 ".kiy[5:8]"  0.031226566061377525 0 0 0;
	setAttr -s 9 ".kox[5:8]"  0.99951237440109253 1 1 1;
	setAttr -s 9 ".koy[5:8]"  0.031226582825183868 0 0 0;
createNode animCurveTL -n "Maugli_Center_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.024349347202935689 3 0.14661869313999853 
		6 0.21294516881984193 11 0.43053304069441989 16 0.58546275349698629 21 0.58969355983597516 
		27 0.58969355983597516 45 0.58969355983597516;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTL -n "Maugli_Center_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.0012760952138130693 3 0.0049320532191426264 
		6 0.0029641021318727451 11 0.045196368553595032 16 0.048982111330104369 21 0.052717390024561037 
		27 0.052717390024561037 45 0.052717390024561037;
	setAttr -s 8 ".kit[0:7]"  3 10 10 1 9 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 1 9 10 10 10;
	setAttr -s 8 ".kix[3:7]"  0.99974334239959717 0.99974554777145386 
		1 1 1;
	setAttr -s 8 ".kiy[3:7]"  0.022655924782156944 0.022557325661182404 
		0 0 0;
	setAttr -s 8 ".kox[3:7]"  0.99974334239959717 0.99974554777145386 
		1 1 1;
	setAttr -s 8 ".koy[3:7]"  0.022655915468931198 0.022557325661182404 
		0 0 0;
createNode animCurveTA -n "Maugli_IKLegBackBall_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTU -n "Maugli_FKIKLegBack_L_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegBack_L_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegBack_L_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 11 10 16 10 21 10 27 10 
		45 10;
createNode animCurveTU -n "Maugli_PoleLegBack_L_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 11 10 16 10 21 10 27 10 
		45 10;
createNode animCurveTL -n "Maugli_PoleLegBack_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 6 0 11 0.9567785901323993 12 0.10027090043195984 
		13 -0.079986023918929144 16 -0.15718129941029677 21 -0.15718129941029677 27 -0.15718129941029677 
		45 -0.15718129941029677;
createNode animCurveTL -n "Maugli_PoleLegBack_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 6 0 11 -0.44190597162753709 12 
		-0.058239084376940524 13 -0.13760041567317438 16 -0.17299878929764209 21 -0.17299878929764209 
		27 -0.17299878929764209 45 -0.17299878929764209;
createNode animCurveTL -n "Maugli_PoleLegBack_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 6 0 11 0.12753999542186545 12 -0.26431401713423908 
		13 -0.25663453706951217 16 0.65264961838772517 21 0.65264961838772517 27 0.65264961838772517 
		45 0.65264961838772517;
createNode animCurveTU -n "Maugli_IKLegBack_L_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
createNode animCurveTU -n "Maugli_IKLegBack_L_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
createNode animCurveTU -n "Maugli_IKLegBack_L_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTU -n "Maugli_IKLegBack_L_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTU -n "Maugli_IKLegBack_L_legAim";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 11 10 16 10 21 10 27 10 
		45 10;
createNode animCurveTU -n "Maugli_IKLegBack_L_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 25 3 25 6 25 11 25 16 25 21 25 27 25 
		45 25;
createNode animCurveTU -n "Maugli_IKLegBack_L_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTU -n "Maugli_IKLegBack_L_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBack_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 6 0 11 0 13 -2.4911413906284432 
		16 -5.916811323630772 21 -5.916811323630772 27 -5.916811323630772 45 -5.916811323630772;
createNode animCurveTA -n "Maugli_IKLegBack_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 6 0 11 0 13 5.6686184875398853 
		16 50.173555129841219 21 50.173555129841219 27 50.173555129841219 45 50.173555129841219;
createNode animCurveTA -n "Maugli_IKLegBack_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 6 0 11 0 13 1.7048265228085986 
		16 119.29568120857127 21 119.29568120857127 27 119.29568120857127 45 119.29568120857127;
createNode animCurveTL -n "Maugli_IKLegBack_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 -0.14518996216905866 
		21 -0.063041152552844149 27 -0.14518996216905866 45 -0.14518996216905866;
createNode animCurveTL -n "Maugli_IKLegBack_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.76278640316887203 3 -0.76278640316887203 
		6 -0.76278640316887203 11 -0.76278640316887203 12 0.22871607820226103 13 0.45772632506506872 
		16 1.3605259713223692 21 1.4804367839537398 27 1.4804367839537398 45 1.4804367839537398;
createNode animCurveTL -n "Maugli_IKLegBack_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 -0.1596592239829866 
		21 -0.082595896128831559 27 -0.082595896128831559 45 -0.082595896128831559;
createNode animCurveTL -n "Maugli_BendNeck_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTL -n "Maugli_BendNeck_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTL -n "Maugli_BendNeck_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTU -n "Maugli_FKIKSpine_M_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKSpine_M_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKSpine_M_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBackBall_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTU -n "Maugli_FKIKLegBack_R_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegBack_R_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegBack_R_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 11 10 16 10 21 10 27 10 
		45 10;
createNode animCurveTU -n "Maugli_PoleLegBack_R_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 11 10 16 10 21 10 27 10 
		45 10;
createNode animCurveTL -n "Maugli_PoleLegBack_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -2.2204460492503131e-016 3 -2.2204460492503131e-016 
		6 -2.2204460492503131e-016 11 0.46763480777141664 16 -2.2204460492503131e-016 21 
		-2.2204460492503131e-016 27 -2.2204460492503131e-016 45 -2.2204460492503131e-016;
createNode animCurveTL -n "Maugli_PoleLegBack_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0.0089216463507840113 16 
		0 21 0 27 0 45 0;
createNode animCurveTL -n "Maugli_PoleLegBack_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -5.5511151231257827e-017 3 -5.5511151231257827e-017 
		6 -5.5511151231257827e-017 11 0.061081011155340252 16 -5.5511151231257827e-017 21 
		-5.5511151231257827e-017 27 -5.5511151231257827e-017 45 -5.5511151231257827e-017;
createNode animCurveTU -n "Maugli_IKLegBack_R_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 6 1 11 1 16 1 21 1 32 1;
createNode animCurveTU -n "Maugli_IKLegBack_R_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 6 1 11 1 16 1 21 1 32 1;
createNode animCurveTU -n "Maugli_IKLegBack_R_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 6 0 11 0 16 0 21 0 32 0;
createNode animCurveTU -n "Maugli_IKLegBack_R_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 6 0 11 0 16 0 21 0 32 0;
createNode animCurveTU -n "Maugli_IKLegBack_R_legAim";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10 3 10 6 10 11 10 16 10 21 10 32 10;
createNode animCurveTU -n "Maugli_IKLegBack_R_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 25 3 25 6 25 11 25 16 25 21 25 32 25;
createNode animCurveTU -n "Maugli_IKLegBack_R_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 6 0 11 0 16 0 21 0 32 0;
createNode animCurveTU -n "Maugli_IKLegBack_R_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 6 0 11 0 16 0 21 0 32 0;
createNode animCurveTA -n "Maugli_IKLegBack_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -17.042137663821414 3 -17.042137663821414 
		6 -17.042137663821414 11 -17.042137663821414 16 -17.591768954288412 21 -18.927685305862546 
		27 -6.8389932405203062 32 -18.927685305862546;
createNode animCurveTA -n "Maugli_IKLegBack_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 50.899398636570851 
		21 68.647739120070199 27 79.815987868588167 32 68.647739120070199;
createNode animCurveTA -n "Maugli_IKLegBack_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 116.82521638458236 
		21 126.77854118336504 27 129.04775735985854 32 126.77854118336504;
createNode animCurveTL -n "Maugli_IKLegBack_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1.1102230246251563e-016 3 1.1102230246251563e-016 
		6 1.1102230246251563e-016 11 1.1102230246251563e-016 16 0.11318251775347871 21 -0.083549063494846365 
		27 0.011120476134207871 32 -0.083549063494846282;
createNode animCurveTL -n "Maugli_IKLegBack_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.019491142195864015 3 0.019491142195864015 
		6 0.019491142195864015 11 0.019491142195864015 16 1.1500717561655742 21 1.3145022080195781 
		32 1.3145022080195781;
createNode animCurveTL -n "Maugli_IKLegBack_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.063585363072848899 3 -0.063585363072848899 
		6 -0.063585363072848899 11 -0.063585363072848899 16 -0.063585363072848899 21 -0.033713971461866166 
		32 -0.17170555244840874;
createNode animCurveTU -n "Maugli_FKIKSplineTail_M_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKSplineTail_M_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKSplineTail_M_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 11 10 16 10 21 10 27 10 
		45 10;
createNode animCurveTU -n "Maugli_WagCurveSplineTail_M_increment";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
createNode animCurveTU -n "Maugli_WagCurveSplineTail_M_multiply";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
createNode animCurveTU -n "Maugli_WagCurveSplineTail_M_timeOffset";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
createNode animCurveTU -n "Maugli_WagCurveSplineTail_M_enable";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTA -n "Maugli_WagCurveSplineTail_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_WagCurveSplineTail_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_WagCurveSplineTail_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTU -n "Maugli_IKSplineTail2_M_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTU -n "Maugli_IKSplineTail2_M_twist";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTU -n "Maugli_IKSplineTail2_M_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTL -n "Maugli_IKSplineTail2_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.31618923007172439 3 -0.13518562936194378 
		6 0.43714411414225562 11 0.76323354912474439 16 0.1484112233501802 21 -0.26554863351780067 
		27 -1.1025502877468993 45 -1.1025502877468993;
	setAttr -s 8 ".kit[0:7]"  9 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  9 10 10 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKSplineTail2_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -1.0020975550085076 3 -0.29100997061501932 
		6 0.79244184962722919 11 0.53510791223125187 16 -0.026163171787761286 21 0.18951621094610527 
		27 0.12959994288912835 45 0.12959994288912835;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKSplineTail2_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.80886811842270168 3 0.75486680955319974 
		6 -0.30381303421381201 11 -0.76838587725463403 16 0.38485892999137172 21 1.304133622989186 
		27 1.4074821827389057 45 1.4074821827389057;
	setAttr -s 8 ".kit[0:7]"  9 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  9 10 10 10 10 10 10 10;
createNode animCurveTU -n "Maugli_IKSplineTail1_M_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTL -n "Maugli_IKSplineTail1_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 3.1086244689504383e-015 3 0.064916712099393425 
		6 -0.21351290217785102 11 -0.23367690903874383 16 -1.0156466728075504 21 -1.1916472272506593 
		27 -0.77974056736150432 45 -0.77974056736150432;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKSplineTail1_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.16519211009181056 3 0.0077014660506997679 
		6 0.18299126975328539 11 0.5689183238863329 16 0.68721428883974101 21 0.75958840506284808 
		27 0.77323912973819198 45 0.77323912973819198;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKSplineTail1_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.010972047845733357 3 -0.006961744946863746 
		6 0.18206915477189825 11 0.30728013580179031 16 0.79918333154989507 21 0.096192635718181929 
		27 0.10509089208490251 45 0.10509089208490251;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_FKRump_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -18.638044314952673 3 -18.638044314952673 
		6 -18.638044314952673 11 -18.638044314952673 16 -3.3787936346791536 21 -3.3787936346791536 
		27 -3.3787936346791536 45 -3.3787936346791536;
createNode animCurveTA -n "Maugli_FKRump_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 5.9273289705481567 3 5.9273289705481567 
		6 5.9273289705481567 11 5.9273289705481567 16 2.5089453242431246 21 2.5089453242431246 
		27 2.5089453242431246 45 2.5089453242431246;
createNode animCurveTA -n "Maugli_FKRump_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 12.021048230974857 3 12.021048230974857 
		6 12.021048230974857 11 12.021048230974857 16 13.150572990791268 21 13.150572990791268 
		27 13.150572990791268 45 13.150572990791268;
createNode animCurveTL -n "Maugli_FKRump_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -5.5511151231257827e-017 3 -5.5511151231257827e-017 
		6 -5.5511151231257827e-017 11 -5.5511151231257827e-017 16 -5.5511151231257827e-017 
		21 -5.5511151231257827e-017 27 -5.5511151231257827e-017 45 -5.5511151231257827e-017;
createNode animCurveTL -n "Maugli_FKRump_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 2.2204460492503131e-016 3 2.2204460492503131e-016 
		6 2.2204460492503131e-016 11 2.2204460492503131e-016 16 2.2204460492503131e-016 21 
		2.2204460492503131e-016 27 2.2204460492503131e-016 45 2.2204460492503131e-016;
createNode animCurveTL -n "Maugli_FKRump_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 2.2204460492503131e-016 3 2.2204460492503131e-016 
		6 2.2204460492503131e-016 11 2.2204460492503131e-016 16 2.2204460492503131e-016 21 
		2.2204460492503131e-016 27 2.2204460492503131e-016 45 2.2204460492503131e-016;
createNode animCurveTA -n "Maugli_FKRump_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -18.710504463926263 3 -18.710504463926263 
		6 -26.997526062979947 11 -26.997526062979947 16 -23.638520495929505 21 -24.352073577417293 
		27 -24.352073577417293 45 -24.352073577417293;
createNode animCurveTA -n "Maugli_FKRump_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 8.2582530676151027 3 8.2582530676151027 
		6 8.9022390064672496 11 8.9022390064672496 16 -9.2529416205008008 21 -6.6399390495352266 
		27 -6.6399390495352266 45 -6.6399390495352266;
createNode animCurveTA -n "Maugli_FKRump_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 5.1050521316126698 3 5.1050521316126698 
		6 3.8665433719597271 11 3.8665433719597271 16 1.1670420198380833 21 1.2310753650138653 
		27 1.2310753650138653 45 1.2310753650138653;
createNode animCurveTL -n "Maugli_FKRump_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 5.5511151231257827e-017 3 5.5511151231257827e-017 
		6 5.5511151231257827e-017 11 5.5511151231257827e-017 16 5.5511151231257827e-017 21 
		5.5511151231257827e-017 27 5.5511151231257827e-017 45 5.5511151231257827e-017;
createNode animCurveTL -n "Maugli_FKRump_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTL -n "Maugli_FKRump_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_FKBackA_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -6.1344158462123248 3 -6.1344158462123248 
		6 -6.1344158462123248 11 -6.1344158462123248 16 -6.1344158462123248 21 -6.1344158462123248 
		27 -6.1344158462123248 45 -6.1344158462123248;
createNode animCurveTA -n "Maugli_FKBackA_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -2.6442010631261756 3 -2.6442010631261756 
		6 -2.6442010631261756 11 -2.6442010631261756 16 -2.6442010631261756 21 -2.6442010631261756 
		27 -2.6442010631261756 45 -2.6442010631261756;
createNode animCurveTA -n "Maugli_FKBackA_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.28408691297585409 3 0.28408691297585409 
		6 0.28408691297585409 11 0.28408691297585409 16 0.28408691297585409 21 0.28408691297585409 
		27 0.28408691297585409 45 0.28408691297585409;
createNode animCurveTA -n "Maugli_FKBackB_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -4.0937696667714745 3 6.1588781595991113 
		6 -11.422313990770018 11 -11.422313990770018 16 -11.422313990770018 21 0.074090412031167008 
		24 4.5850291766227498 27 0.074090412031166994 45 0.074090412031166994;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "Maugli_FKBackB_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -8.7401097734428159 3 -8.712325373236105 
		6 -24.654348189824923 11 -24.654348189824923 16 -24.654348189824923 21 -23.470102617751834 
		24 -25.957986080903197 27 -23.470102617751834 45 -23.470102617751834;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "Maugli_FKBackB_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.62309581808855541 3 -0.9364330258707978 
		6 -2.799253227700623 11 -2.799253227700623 16 -2.799253227700623 21 -2.5865397553035492 
		24 -2.2741547162200417 27 -2.5865397553035492 45 -2.5865397553035492;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "Maugli_FKChest_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -25.928322657740519 3 -25.928322657740519 
		6 -25.928322657740519 11 -25.928322657740519 16 -26.290749211997447 21 -26.290749211997447 
		27 -26.290749211997447 45 -26.290749211997447;
createNode animCurveTA -n "Maugli_FKChest_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -6.0685067306724134 3 -6.0685067306724134 
		6 -6.0685067306724134 11 -6.0685067306724134 16 -0.63405091542517256 21 -0.63405091542517256 
		27 -0.63405091542517256 45 -0.63405091542517256;
createNode animCurveTA -n "Maugli_FKChest_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 2.6635387051032011 3 2.6635387051032011 
		6 2.6635387051032011 11 2.6635387051032011 16 -0.60642098706677805 21 -0.60642098706677816 
		27 -0.60642098706677816 45 -0.60642098706677816;
createNode animCurveTA -n "Maugli_FKNeck_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 22.628337533497174 3 42.178970494285352 
		6 24.303486513141291 11 1.2792050829886159 16 5.8804247857593124 21 30.290734483890333 
		25 57.941124230842533 31 59.625195265049413 45 59.625195265049413;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 1 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 1 10 
		10;
	setAttr -s 9 ".kix[6:8]"  0.99029093980789185 1 1;
	setAttr -s 9 ".kiy[6:8]"  0.13901053369045258 0 0;
	setAttr -s 9 ".kox[6:8]"  0.99029093980789185 1 1;
	setAttr -s 9 ".koy[6:8]"  0.13901053369045258 0 0;
createNode animCurveTA -n "Maugli_FKNeck_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 3.6826813105759961 3 -2.555023156650607 
		6 -7.4398560514675367 11 -19.725562775133628 16 -13.046742366705089 21 -37.873573485931111 
		25 -38.686704047608643 31 -33.812969949929339 45 -33.812969949929339;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "Maugli_FKNeck_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 2.2991021693981635 3 -6.6564346855885503 
		6 -15.361697071991761 11 -5.664280691493274 16 16.474796605271539 21 36.964988472627063 
		25 36.26427213112931 31 24.364960846360574 45 24.364960846360574;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "Maugli_FKHead_M_Global";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 11 10 16 10 25 10 33 10 
		45 10;
createNode animCurveTA -n "Maugli_FKHead_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -7.8426637274840703 3 47.695004030573983 
		6 -53.66487725656286 11 -49.681614918305677 16 -111.98934522021051 21 -119.2513900149217 
		25 -150.72626435478708 29 -250.43120807301275 33 -90.088103751039597 45 -90.088103751039597;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "Maugli_FKHead_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -7.5490945101966842 3 -15.19622308879333 
		6 7.8109725076937053 11 -19.703950589360264 16 -36.268759605384574 21 -38.392184851255237 
		25 -97.17477190848669 29 -105.75700952076295 33 -99.286559033325432 45 -99.286559033325432;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "Maugli_FKHead_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 5.461028169262887 3 0.11845995925296905 
		6 8.2614277790556017 11 46.295434673990187 16 65.047710150104237 21 46.215292477752477 
		25 -46.06500068503108 29 -157.4318410318175 33 1.0526541767991433 45 1.0526541767991433;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "Maugli_Main_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
createNode animCurveTU -n "Maugli_Main_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
createNode animCurveTU -n "Maugli_Main_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
createNode animCurveTA -n "Maugli_Main_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_Main_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_Main_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTL -n "Maugli_Main_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTL -n "Maugli_Main_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTL -n "Maugli_Main_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTU -n "Maugli_Main_visibility";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTA -n "Maugli_kolchan_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -16.498609615445837 3 -5.9012097939039929 
		6 -6.8203877658143011 11 -28.368037989059204 16 -22.059721379673594 21 -44.18067423665007 
		27 -41.294698490864441 45 -41.294698490864441;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_kolchan_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -6.4006181765439756 3 -6.6233716706010455 
		6 -6.6128715524598318 11 -8.4427807728347108 16 -7.5630355034749179 21 -17.03461973758256 
		27 -16.776638950142182 45 -16.776638950142182;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_kolchan_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1.8111494521402616 3 0.60588953757056951 
		6 0.71182826412951727 11 -7.5343514272687973 16 -15.283007603387718 21 -16.937022446618212 
		27 -12.961154824542 45 -12.961154824542;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_yashik_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 6 5.5864200777026607 11 -10.843876101961881 
		16 1.8358310193391929 21 -13.921627574716574 27 4.5674252848500636 33 -76.206370179813234 
		37 -75.965041694054008 45 -75.965041694054008;
createNode animCurveTA -n "Maugli_yashik_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 6 2.9514921476989233 11 0 16 -2.4680929542125263 
		21 6.8910310211253956 27 -4.5549010798789347 33 18.532915940479818 37 18.774563459717839 
		45 18.774563459717839;
createNode animCurveTA -n "Maugli_yashik_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 6 -2.0872159646465902 11 0 16 -10.351217611117969 
		21 27.338180343810318 27 -64.358611298167546 33 -113.19795399367551 37 -119.22361841447722 
		45 -119.22361841447722;
createNode animCurveTL -n "Maugli_yashik_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 6 0 11 0 16 -0.024746756104767509 
		21 0.15347263969394201 27 0.77648145300651994 30 1.0131809698209566 33 1.2875621556692511 
		35 1.2678478809758782 37 1.3156277352558814 45 1.3156277352558814;
createNode animCurveTL -n "Maugli_yashik_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 6 0 11 0 16 -0.17960367867340696 
		21 -0.18821366966209549 27 0.11255325395738675 30 -0.12946884151286797 33 -0.02843137888860759 
		35 -0.10394233911508199 37 -0.072864440050193449 45 -0.072864440050193449;
createNode animCurveTL -n "Maugli_yashik_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 6 0 11 0 16 -0.083228571484863803 
		21 -0.24326969928424313 27 -0.097189544541089579 30 -0.37873946825939991 33 -0.67975296220173098 
		35 -0.76760284848544724 37 -0.844835812970406 45 -0.844835812970406;
createNode animCurveTA -n "Maugli_l_ear_control_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_l_ear_control_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_l_ear_control_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_r_ear_control1_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_r_ear_control1_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_r_ear_control1_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "Maugli_jaw_C_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 6 0 11 0 16 0 21 9.9964695946576256 
		25 -0.35518564601540265 29 9.9964695946576256 45 9.9964695946576256;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "Maugli_spear_control_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 6 0 11 0 12 35.319006246293711 
		17 18.291952550938827 20 -26.987058498709267 23 -10.633255681089395 26 -14.222481210606606 
		30 -14.793381371539224;
createNode animCurveTA -n "Maugli_spear_control_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 6 0 11 0 12 131.93206273991686 
		17 124.69554299432671 20 127.15520992523764 23 123.51893919223151 26 123.96912096910906 
		30 124.0352543837281;
createNode animCurveTA -n "Maugli_spear_control_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 6 0 11 0 12 -26.683078334164524 
		17 -48.533209541363661 20 -106.89801364034497 23 -86.058911281453575 26 -90.548257760736647 
		30 -90.477270503889486;
createNode animCurveTL -n "Maugli_spear_control_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0.041982630251665931 3 0.041982630251665931 
		6 0.041982630251665931 11 0.041982630251665931 12 -0.76171335134120355 17 -1.8326614961552945 
		20 -2.442776820623958 23 -2.5321695189548059 26 -2.6137185067670359 28 -2.5772850982417257 
		30 -2.6137185067670359;
	setAttr -s 11 ".kit[7:10]"  3 3 3 3;
	setAttr -s 11 ".kot[7:10]"  3 3 3 3;
createNode animCurveTL -n "Maugli_spear_control_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.05682005777595385 3 -0.05682005777595385 
		6 -0.05682005777595385 11 -0.05682005777595385 12 0.71130417730858431 30 0.71130417730858431;
createNode animCurveTL -n "Maugli_spear_control_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.19304667407551657 3 0.19304667407551657 
		6 0.19304667407551657 11 0.19304667407551657 12 1.2300175670317133 17 1.0507060957464027 
		30 0.98525085460936679;
	setAttr -s 7 ".kit[4:6]"  3 10 10;
	setAttr -s 7 ".kot[4:6]"  3 10 10;
createNode animCurveTU -n "Maugli_spear_control_World_Hands";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 3 1 6 1 11 1 12 0 30 0;
	setAttr -s 6 ".kot[0:5]"  5 5 5 5 5 5;
createNode animCurveTA -n "Maugli_IKLegFrontBall_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegFrontBall_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1.1 3 1.1 6 1.1 11 1.1 16 1.1 21 1.1;
createNode animCurveTU -n "Maugli_IKLegFront_R_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1.1 3 1.1 6 1.1 11 1.1 16 1.1 21 1.1;
createNode animCurveTU -n "Maugli_IKLegFront_R_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 0 6 0 11 0 16 0 21 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 0 6 0 11 0 16 0 21 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_legAim";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 10 3 10 6 10 11 10 16 10 21 10;
createNode animCurveTU -n "Maugli_IKLegFront_R_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 25 3 25 6 25 11 25 16 25 21 25;
createNode animCurveTU -n "Maugli_IKLegFront_R_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 0 6 0 11 0 16 0 21 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 0 6 0 11 0 16 0 21 0;
createNode animCurveTA -n "Maugli_IKLegFront_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 13.452853449395933 3 13.452853449395933 
		6 13.452853449395933 11 15.820604466469769 16 6.1855022518768692 21 2.0824837667411003;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTA -n "Maugli_IKLegFront_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 0 6 0 11 -29.763306737731337 16 8.3814379976667315 
		21 35.245908627750637;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTA -n "Maugli_IKLegFront_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 0 6 27.894029630803725 11 -10.110257116194816 
		16 -17.687739062613712 21 -10.83963366194746;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKLegFront_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 5.5511151231257852e-017 3 5.5511151231257852e-017 
		6 0.15745968366158947 11 0.30286613212824809 16 0.024740601806426232 21 -0.15785150635262246;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKLegFront_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.78767523172948961 3 -0.78767523172948961 
		6 -0.78767523172948961 11 -0.57327250768571891 16 -0.83704874904998117 21 -0.74621644182990399;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTL -n "Maugli_IKLegFront_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.077325821529500835 3 -0.077325821529500835 
		6 -0.077325821529500835 11 -0.22081999025365329 16 -0.22081999025365329 21 -0.42661536801427868;
createNode animCurveTU -n "Maugli_IKLegFront_L_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1.1 3 1.1 6 1.1 11 1.1 16 1.1 21 1.1 
		27 1.1 45 1.1;
createNode animCurveTU -n "Maugli_IKLegFront_L_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1.1 3 1.1 6 1.1 11 1.1 16 1.1 21 1.1 
		27 1.1 45 1.1;
createNode animCurveTU -n "Maugli_IKLegFront_L_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTU -n "Maugli_IKLegFront_L_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTU -n "Maugli_IKLegFront_L_legAim";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 11 10 16 10 21 10 27 10 
		45 10;
createNode animCurveTU -n "Maugli_IKLegFront_L_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 25 3 25 6 25 11 25 16 25 21 25 27 25 
		45 25;
createNode animCurveTU -n "Maugli_IKLegFront_L_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTU -n "Maugli_IKLegFront_L_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_IKLegFront_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -4.3689304491953465 3 -4.3689304491953465 
		6 -4.3689304491953465 11 -4.3689304491953465 16 -45.976700624816651 21 -30.539121999146349 
		24 -49.521939509243374 27 -30.539121999146349 45 -30.539121999146349;
createNode animCurveTA -n "Maugli_IKLegFront_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 6 0 11 0 16 42.381095892610276 
		21 69.915057204807795 24 68.748013911822113 27 69.915057204807795 45 69.915057204807795;
createNode animCurveTA -n "Maugli_IKLegFront_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 6 0 11 0 16 -31.593075606252839 
		21 -15.080727250760004 24 -19.749891477578469 27 -15.080727250760004 45 -15.080727250760004;
createNode animCurveTL -n "Maugli_IKLegFront_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 6 0 11 0 16 -0.10380621524019673 
		21 -0.10380621524019673 24 -0.052511679946369183 27 -0.10380621524019673 45 -0.10380621524019673;
createNode animCurveTL -n "Maugli_IKLegFront_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.063844748963588188 3 -0.063844748963588188 
		6 -0.063844748963588188 11 -0.063844748963588188 16 -0.89279399850206997 21 -1.059598156565515 
		27 -1.059598156565515 45 -1.059598156565515;
createNode animCurveTL -n "Maugli_IKLegFront_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.072835230653514785 3 -0.072835230653514785 
		6 -0.072835230653514785 11 -0.072835230653514785 16 -0.072835230653514452 21 -0.49810063810165078 
		27 -0.62566181405046706 45 -0.62566181405046706;
createNode animCurveTU -n "Maugli_FKIKLegFront_L_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegFront_L_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegFront_L_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 11 10 16 10 21 10 27 10 
		45 10;
createNode animCurveTU -n "Maugli_FKIKLegFront_R_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegFront_R_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegFront_R_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 11 10 16 10 21 10 27 10 
		45 10;
createNode animCurveTA -n "Maugli_FKScapula_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_FKScapula_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_FKScapula_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTL -n "Maugli_FKScapula_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -2.2204460492503131e-016 3 -2.2204460492503131e-016 
		6 -2.2204460492503131e-016 11 -2.2204460492503131e-016 16 -2.2204460492503131e-016 
		21 -2.2204460492503131e-016 27 -2.2204460492503131e-016 45 -2.2204460492503131e-016;
createNode animCurveTL -n "Maugli_FKScapula_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -1.1102230246251565e-016 3 -1.1102230246251565e-016 
		6 -1.1102230246251565e-016 11 -1.1102230246251565e-016 16 -1.1102230246251565e-016 
		21 -1.1102230246251565e-016 27 -1.1102230246251565e-016 45 -1.1102230246251565e-016;
createNode animCurveTL -n "Maugli_FKScapula_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 4.4408920985006262e-016 3 4.4408920985006262e-016 
		6 4.4408920985006262e-016 11 4.4408920985006262e-016 16 4.4408920985006262e-016 21 
		4.4408920985006262e-016 27 4.4408920985006262e-016 45 4.4408920985006262e-016;
createNode animCurveTA -n "Maugli_FKScapula_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_FKScapula_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "Maugli_FKScapula_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTL -n "Maugli_FKScapula_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -1.1102230246251565e-016 3 -1.1102230246251565e-016 
		6 -1.1102230246251565e-016 11 -1.1102230246251565e-016 16 -1.1102230246251565e-016 
		21 -1.1102230246251565e-016 27 -1.1102230246251565e-016 45 -1.1102230246251565e-016;
createNode animCurveTL -n "Maugli_FKScapula_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -2.2204460492503131e-016 3 -2.2204460492503131e-016 
		6 -2.2204460492503131e-016 11 -2.2204460492503131e-016 16 -2.2204460492503131e-016 
		21 -2.2204460492503131e-016 27 -2.2204460492503131e-016 45 -2.2204460492503131e-016;
createNode animCurveTL -n "Maugli_FKScapula_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -2.2204460492503131e-016 3 -2.2204460492503131e-016 
		6 -2.2204460492503131e-016 11 -2.2204460492503131e-016 16 -2.2204460492503131e-016 
		21 -2.2204460492503131e-016 27 -2.2204460492503131e-016 45 -2.2204460492503131e-016;
createNode animCurveTU -n "Maugli_PoleLegFront_L_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 11 10 16 10 21 10 27 10 
		45 10;
createNode animCurveTL -n "Maugli_PoleLegFront_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.34369246973235407 3 0.34369246973235407 
		6 0.34369246973235407 11 -0.21768824319729485 13 -0.84985875821346013 16 -1.1491126146761226 
		21 -1.183801631327694 24 -1.2648628176798054 27 -1.183801631327694 45 -1.183801631327694;
createNode animCurveTL -n "Maugli_PoleLegFront_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.08732959492146955 3 0.08732959492146955 
		6 0.08732959492146955 11 0.14226006401961189 13 -0.16693811080619819 16 -1.527688506520559 
		21 -0.46639331436601256 24 -0.94440325964473715 27 -0.46639331436601256 45 -0.46639331436601256;
createNode animCurveTL -n "Maugli_PoleLegFront_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.27202670267238233 3 -0.27202670267238233 
		6 -0.27202670267238233 11 -0.13916816802465318 13 -0.68358214903856007 16 -1.2252273272619696 
		21 -0.87223223734324351 24 -1.1492512281701097 27 -0.87223223734324351 45 -0.87223223734324351;
createNode animCurveTU -n "Maugli_PoleLegFront_R_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 10 3 10 6 10 11 10 16 10 21 10 27 10 
		45 10;
createNode animCurveTL -n "Maugli_PoleLegFront_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.31678960075780738 3 0.31678960075780738 
		6 0.31678960075780738 11 0.31678960075780738 16 -0.47492641781279776 21 -0.50970954345691299 
		27 -0.50970954345691299 45 -0.50970954345691299;
createNode animCurveTL -n "Maugli_PoleLegFront_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.11971028970415042 3 -0.11971028970415042 
		6 -0.11971028970415042 11 -0.11971028970415042 16 -0.24023291173071618 21 -0.086490878085798792 
		27 -0.086490878085798792 45 -0.086490878085798792;
createNode animCurveTL -n "Maugli_PoleLegFront_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.0005730959429199018 3 0.0005730959429199018 
		6 0.0005730959429199018 11 0.0005730959429199018 16 -0.36802071015059779 21 -0.065761537395031142 
		27 -0.065761537395031142 45 -0.065761537395031142;
createNode animCurveTL -n "curve1_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTL -n "curve1_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTL -n "curve1_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTU -n "curve1_visibility";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
	setAttr -s 8 ".kot[0:7]"  5 5 5 5 5 5 5 5;
createNode animCurveTA -n "curve1_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "curve1_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "curve1_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTU -n "curve1_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
createNode animCurveTU -n "curve1_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
createNode animCurveTU -n "curve1_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
createNode animCurveTA -n "IKLegBackBall_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  3 0 6 0 9 0 11 0 12 0 16 0 21 0 27 0 33 
		0 45 0;
createNode animCurveTA -n "IKLegBackBall_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  3 0 6 0 9 0 11 0 12 0 16 0 21 0 27 0 33 
		0 45 0;
createNode animCurveTA -n "IKLegBackBall_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  3 0 6 0 9 0 11 0 12 0 16 0 21 0 27 0 33 
		0 45 0;
createNode animCurveTA -n "IKLegBackBall_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  3 0 6 0 9 0 11 0 12 0 16 0 21 0 27 0 33 
		0 45 0;
createNode animCurveTA -n "IKLegFrontBall_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  3 0 6 0 9 0 11 0 12 0 16 0 21 0 27 0 33 
		0 45 0;
createNode animCurveTA -n "IKLegFrontBall_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  3 0 6 0 9 0 11 0 12 0 16 0 21 0 27 0 33 
		0 45 0;
createNode animCurveTA -n "IKLegFrontBall_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  3 0 6 0 9 0 11 0 12 0 16 0 21 0 27 0 33 
		0 45 0;
createNode animCurveTA -n "IKLegFrontBall_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  3 0 6 0 9 0 11 0 12 0 16 0 21 0 27 0 33 
		0 45 0;
createNode animCurveTL -n "IKXSplineTailCurve_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 4.0142992214232583e-036 3 4.0142992214232583e-036 
		6 4.0142992214232583e-036 11 4.0142992214232583e-036 16 4.0142992214232583e-036 21 
		4.0142992214232583e-036 27 4.0142992214232583e-036 45 4.0142992214232583e-036;
createNode animCurveTL -n "IKXSplineTailCurve_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTL -n "IKXSplineTailCurve_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "IKXSplineTailCurve_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "IKXSplineTailCurve_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTA -n "IKXSplineTailCurve_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 11 0 16 0 21 0 27 0 45 0;
createNode animCurveTU -n "IKXSplineTailCurve_M_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
createNode animCurveTU -n "IKXSplineTailCurve_M_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
createNode animCurveTU -n "IKXSplineTailCurve_M_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 3 1 6 1 11 1 16 1 21 1 27 1 45 1;
createNode animCurveTA -n "IKLegBall_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  3 0 6 0 9 0 11 0 12 0 16 0 21 0 27 0 33 
		0 45 0;
createNode animCurveTA -n "IKLegBall_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  3 0 6 0 9 0 11 0 12 0 16 0 21 0 27 0 33 
		0 45 0;
createNode animCurveTA -n "IKLegBall_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  3 0 6 0 9 0 11 0 12 0 16 0 21 0 27 0 33 
		0 45 0;
createNode animCurveTA -n "IKLegBall_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  3 0 6 0 9 0 11 0 12 0 16 0 21 0 27 0 33 
		0 45 0;
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
connectAttr "deathSource.cl" "clipLibrary1.sc[0]";
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
// End of death.ma
