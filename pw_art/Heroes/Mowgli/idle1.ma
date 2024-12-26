//Maya ASCII 2008 scene
//Name: idle01.ma
//Last modified: Tue, Jan 26, 2010 06:23:33 PM
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
	setAttr -s 375 ".cel[0].cev";
	setAttr ".cd[0].cm" -type "characterMapping" 486 "Center_M_Man.CenterBtwFeet" 
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
		0 153 "curve1.scaleZ" 0 154 "IKXSplineTailCurve_M.translateX" 1 
		130 "IKXSplineTailCurve_M.translateY" 1 131 "IKXSplineTailCurve_M.translateZ" 
		1 132 "IKXSplineTailCurve_M.rotateX" 2 277 "IKXSplineTailCurve_M.rotateY" 
		2 278 "IKXSplineTailCurve_M.rotateZ" 2 279 "IKXSplineTailCurve_M.scaleX" 
		0 155 "IKXSplineTailCurve_M.scaleY" 0 156 "IKXSplineTailCurve_M.scaleZ" 
		0 157  ;
	setAttr ".cd[0].cim" -type "Int32Array" 486 0 1 2 3 4
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
		 485 ;
createNode animClip -n "idle01Source";
	setAttr ".ihi" 0;
	setAttr -s 375 ".ac";
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
	setAttr ".ac[459:485]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".se" 60;
	setAttr ".ci" no;
createNode animCurveTU -n "Maugli_Center_M_Man_CenterBtwFeet";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_Center_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_Center_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_Center_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 4.0494833724385515 30 4.0494833724385515 
		60 4.0494833724385515;
createNode animCurveTL -n "Maugli_Center_M_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_Center_M_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_Center_M_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "Maugli_Fingers_L_Man_MiddleFingerCurl";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegBall_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegToe_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegToe_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 3.1805546814635168e-015 30 3.1805546814635168e-015 
		60 3.1805546814635168e-015;
createNode animCurveTA -n "Maugli_IKLegToe_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "Maugli_FKIKLeg_L_Man_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTU -n "Maugli_FKIKLeg_L_Man_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTU -n "Maugli_FKIKLeg_L_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 10 30 10 60 10;
createNode animCurveTA -n "Maugli_IKLegHeel_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegHeel_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -3.1805546814635168e-015 30 -3.1805546814635168e-015 
		60 -3.1805546814635168e-015;
createNode animCurveTA -n "Maugli_IKLegHeel_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_PoleLeg_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_PoleLeg_L_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_PoleLeg_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_Lenght2";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_Lenght1";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_antiPop";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_stretchy";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_rollAngle";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 25 30 25 60 25;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_roll";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_toe";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "Maugli_IKLeg_L_Man_swivel";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_IKLeg_L_Man_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -5.0105185448650458 30 -14.447854540100119 
		60 -5.0105185448650458;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_IKLeg_L_Man_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -6.3694432300697281 30 2.9665452534313346 
		60 -6.3694432300697281;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_IKLeg_L_Man_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 13.378201002477269 30 25.834422928074826 
		60 13.378201002477269;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "Maugli_IKLeg_L_Man_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.069000150376690925 30 0.063475762296392998 
		60 0.069000150376690925;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "Maugli_IKLeg_L_Man_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.015303353529604964 30 -0.017727495214302686 
		60 -0.015303353529604964;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "Maugli_IKLeg_L_Man_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.16760982461393598 30 0.16083319687146655 
		60 0.16760982461393598;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "Maugli_FKIKArm_L_Man_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTU -n "Maugli_FKIKArm_L_Man_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTU -n "Maugli_FKIKArm_L_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 10 30 10 60 10;
createNode animCurveTU -n "Maugli_PoleArm_L_Man_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 10 30 10 60 10;
createNode animCurveTL -n "Maugli_PoleArm_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.39549705228612952 30 0.39549705228612952 
		60 0.39549705228612952;
createNode animCurveTL -n "Maugli_PoleArm_L_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.86201805279910448 30 -0.86201805279910448 
		60 -0.86201805279910448;
createNode animCurveTL -n "Maugli_PoleArm_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.30818663726222251 30 -0.30818663726222251 
		60 -0.30818663726222251;
createNode animCurveTU -n "Maugli_IKArm_L_Man_Lenght2";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "Maugli_IKArm_L_Man_Lenght1";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "Maugli_IKArm_L_Man_antiPop";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "Maugli_IKArm_L_Man_stretchy";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "Maugli_IKArm_L_Man_follow";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_IKArm_L_Man_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -97.78067605427789 30 -101.25255682123705 
		60 -97.78067605427789;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_IKArm_L_Man_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 10.92155845877172 30 11.690969065815016 
		60 10.92155845877172;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_IKArm_L_Man_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 14.178018067197163 30 13.598106694263153 
		60 14.178018067197163;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "Maugli_IKArm_L_Man_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.79120002893813179 30 -0.79728934298356413 
		60 -0.79120002893813179;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "Maugli_IKArm_L_Man_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.30360130511963851 30 -0.33063260007077644 
		60 -0.30360130511963851;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "Maugli_IKArm_L_Man_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.80061447835185851 30 -0.8043307536973261 
		60 -0.80061447835185851;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "Maugli_Fingers_R_Man_MiddleFingerCurl";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "Maugli_FKIKSpine_M_Man_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTU -n "Maugli_FKIKSpine_M_Man_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTU -n "Maugli_FKIKSpine_M_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegBall_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegToe_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -7.0622500768802538e-031 30 -7.0622500768802538e-031 
		60 -7.0622500768802538e-031;
createNode animCurveTA -n "Maugli_IKLegToe_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 3.1805546814635168e-015 30 3.1805546814635168e-015 
		60 3.1805546814635168e-015;
createNode animCurveTA -n "Maugli_IKLegToe_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegHeel_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegHeel_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 3.1805546814635168e-015 30 3.1805546814635168e-015 
		60 3.1805546814635168e-015;
createNode animCurveTA -n "Maugli_IKLegHeel_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "Maugli_FKIKLeg_R_Man_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTU -n "Maugli_FKIKLeg_R_Man_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTU -n "Maugli_FKIKLeg_R_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 10 30 10 60 10;
createNode animCurveTL -n "Maugli_PoleLeg_R_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_PoleLeg_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_PoleLeg_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_Lenght2";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_Lenght1";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_antiPop";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_stretchy";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_rollAngle";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 25 30 25 60 25;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_roll";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_toe";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "Maugli_IKLeg_R_Man_swivel";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_IKLeg_R_Man_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 8.4619142664415712 60 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_IKLeg_R_Man_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 -4.6329862978946723 60 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_IKLeg_R_Man_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 -1.0196329734419229 60 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "Maugli_IKLeg_R_Man_translateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0.021543807574691286 60 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "Maugli_IKLeg_R_Man_translateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 -0.059956636547662458 60 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "Maugli_IKLeg_R_Man_translateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0.015863671096912266 60 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "Maugli_FKIKArm_R_Man_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTU -n "Maugli_FKIKArm_R_Man_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTU -n "Maugli_FKIKArm_R_Man_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 10 30 10 60 10;
createNode animCurveTU -n "Maugli_PoleArm_R_Man_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 10 30 10 60 10;
createNode animCurveTL -n "Maugli_PoleArm_R_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_PoleArm_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_PoleArm_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.1102230246251565e-016 30 1.1102230246251565e-016 
		60 1.1102230246251565e-016;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -6.2725381128105917e-045 30 -6.2725381128105917e-045 
		60 -6.2725381128105917e-045;
createNode animCurveTU -n "Maugli_IKArm_R_Man_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
createNode animCurveTU -n "Maugli_IKArm_R_Man_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
createNode animCurveTU -n "Maugli_IKArm_R_Man_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "Maugli_IKArm_R_Man_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "Maugli_IKArm_R_Man_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKArm_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -12.754512848885321 15 -19.428028203314987 
		30 -12.495157898523006 45 -5.328127159575673 60 -12.754512848885321;
	setAttr -s 5 ".kit[0:4]"  9 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  9 10 10 10 10;
createNode animCurveTA -n "Maugli_IKArm_R_Man_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -51.071041253431346 15 -51.549534618167904 
		30 -50.18764861489133 45 -50.834154010793092 60 -51.071041253431346;
	setAttr -s 5 ".kit[1:4]"  10 9 9 9;
	setAttr -s 5 ".kot[1:4]"  10 9 9 9;
createNode animCurveTA -n "Maugli_IKArm_R_Man_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -30.429381170308442 15 -28.803040966325632 
		30 -23.536006204005801 45 -28.666033837272437 60 -30.429381170308442;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 9 9 3;
createNode animCurveTL -n "Maugli_IKArm_R_Man_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.50891155850440861 15 -0.4645392834302115 
		30 -0.51623663299359845 45 -0.5324430579470919 60 -0.50891155850440861;
	setAttr -s 5 ".kit[1:4]"  10 9 10 1;
	setAttr -s 5 ".kot[1:4]"  10 9 10 1;
	setAttr -s 5 ".kix[4]"  0.99541676044464111;
	setAttr -s 5 ".kiy[4]"  0.095632493495941162;
	setAttr -s 5 ".kox[4]"  0.99541670083999634;
	setAttr -s 5 ".koy[4]"  0.095632508397102356;
createNode animCurveTL -n "Maugli_IKArm_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.17073023409560481 15 -0.07693079448016199 
		30 -0.13100952145681991 45 -0.23194581350707255 60 -0.17073023409560481;
	setAttr -s 5 ".kit[2:4]"  9 10 9;
	setAttr -s 5 ".kot[2:4]"  9 10 9;
createNode animCurveTL -n "Maugli_IKArm_R_Man_translateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.44722353666474202 15 0.42538866025277633 
		30 0.44183266301042379 45 0.45453948041822584 60 0.44722353666474202;
	setAttr -s 5 ".kit[1:4]"  10 1 10 1;
	setAttr -s 5 ".kot[1:4]"  10 1 10 1;
	setAttr -s 5 ".kix[0:4]"  0.99955528974533081 1 0.99956029653549194 
		1 0.99979770183563232;
	setAttr -s 5 ".kiy[0:4]"  -0.029820563271641731 0 0.029651155695319176 
		0 -0.020116155967116356;
	setAttr -s 5 ".kox[0:4]"  0.99955528974533081 1 0.99956029653549194 
		1 0.99979764223098755;
	setAttr -s 5 ".koy[0:4]"  -0.029820559546351433 0 0.029651148244738579 
		0 -0.020116152241826057;
createNode animCurveTA -n "Maugli_FKScapula_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -7.1990267140314277 30 -7.1990267140314277 
		60 -7.1990267140314277;
createNode animCurveTA -n "Maugli_FKScapula_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 9.9598426785175036 30 9.9598426785175036 
		60 9.9598426785175036;
createNode animCurveTA -n "Maugli_FKScapula_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -7.1981747374653153 30 -7.1981747374653153 
		60 -7.1981747374653153;
createNode animCurveTL -n "Maugli_FKScapula_L_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_FKScapula_L_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_FKScapula_L_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -5.5511151231257827e-017 30 -5.5511151231257827e-017 
		60 -5.5511151231257827e-017;
createNode animCurveTA -n "Maugli_FKMiddleFinger1_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 17.622819694952526 30 17.622819694952526 
		60 17.622819694952526;
createNode animCurveTA -n "Maugli_FKMiddleFinger2_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -23.252905752704581 30 -23.252905752704581 
		60 -23.252905752704581;
createNode animCurveTA -n "Maugli_FKMiddleFinger3_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_FKThumbFinger1_L_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -10.372922440313587 30 -10.372922440313587 
		60 -10.372922440313587;
createNode animCurveTA -n "Maugli_FKThumbFinger1_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 2.7620263328639107 30 2.7620263328639107 
		60 2.7620263328639107;
createNode animCurveTA -n "Maugli_FKThumbFinger1_L_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -32.466562028725463 30 -32.466562028725463 
		60 -32.466562028725463;
createNode animCurveTA -n "Maugli_FKThumbFinger2_L_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -26.277332307519721 30 -26.277332307519721 
		60 -26.277332307519721;
createNode animCurveTA -n "Maugli_FKBackA_M_Man_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 7.8357327658317191 15 5.238014707157177 
		30 7.8357327658317191 45 9.6886454143918161 60 7.8357327658317191;
	setAttr -s 5 ".kit[1:4]"  10 9 10 9;
	setAttr -s 5 ".kot[1:4]"  10 9 10 9;
createNode animCurveTA -n "Maugli_FKBackA_M_Man_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -7.5265731098501263 15 -7.766571389547428 
		30 -7.5265731098501263 45 -7.345841788547042 60 -7.5265731098501263;
	setAttr -s 5 ".kit[1:4]"  10 9 10 9;
	setAttr -s 5 ".kot[1:4]"  10 9 10 9;
createNode animCurveTA -n "Maugli_FKBackA_M_Man_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -5.4975000363152615 15 -5.1517834258345037 
		30 -5.4975000363152615 45 -5.7373290045839589 60 -5.4975000363152615;
	setAttr -s 5 ".kit[1:4]"  10 9 10 9;
	setAttr -s 5 ".kot[1:4]"  10 9 10 9;
createNode animCurveTA -n "Maugli_FKBackB_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 2.7266862105714793 30 2.7266862105714793 
		60 2.7266862105714793;
createNode animCurveTA -n "Maugli_FKBackB_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.24259990801533335 30 0.24259990801533335 
		60 0.24259990801533335;
createNode animCurveTA -n "Maugli_FKBackB_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.5001242681430698 30 1.5001242681430698 
		60 1.5001242681430698;
createNode animCurveTA -n "Maugli_FKChest_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -12.769021381384317 30 -12.769021381384317 
		60 -12.769021381384317;
createNode animCurveTA -n "Maugli_FKChest_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 4.6070431346914544 30 4.6070431346914544 
		60 4.6070431346914544;
createNode animCurveTA -n "Maugli_FKChest_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 4.8308420450374907 30 4.8308420450374907 
		60 4.8308420450374907;
createNode animCurveTA -n "Maugli_FKNeck_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_FKNeck_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_FKNeck_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_FKHead_M_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -6.9400884964770713 15 -2.8117665478526961 
		30 -6.9400884964770713 45 -7.4635503833749102 60 -6.9400884964770713;
createNode animCurveTA -n "Maugli_FKHead_M_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 3.508580449788079 15 3.1118237476987942 
		30 3.508580449788079 45 3.5378797416108712 60 3.508580449788079;
createNode animCurveTA -n "Maugli_FKHead_M_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 5.0972336912670713 15 4.493435252824078 
		30 5.0972336912670713 45 5.17285190690892 60 5.0972336912670713;
createNode animCurveTA -n "Maugli_FKScapula_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 3.6745332739058547 30 3.6745332739058547 
		60 3.6745332739058547;
createNode animCurveTA -n "Maugli_FKScapula_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -6.3459812884849134 30 -6.3459812884849134 
		60 -6.3459812884849134;
createNode animCurveTA -n "Maugli_FKScapula_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.71910078156005675 30 -0.71910078156005675 
		60 -0.71910078156005675;
createNode animCurveTL -n "Maugli_FKScapula_R_Man_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -2.7755575615628914e-017 30 -2.7755575615628914e-017 
		60 -2.7755575615628914e-017;
createNode animCurveTL -n "Maugli_FKScapula_R_Man_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_FKScapula_R_Man_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 5.5511151231257827e-017 30 5.5511151231257827e-017 
		60 5.5511151231257827e-017;
createNode animCurveTA -n "Maugli_FKMiddleFinger1_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_FKMiddleFinger2_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -67.588216236699324 30 -67.588216236699324 
		60 -67.588216236699324;
createNode animCurveTA -n "Maugli_FKMiddleFinger3_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -81.669521342510606 30 -81.669521342510606 
		60 -81.669521342510606;
createNode animCurveTA -n "Maugli_FKThumbFinger1_R_Man_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 25.665274764482422 30 25.665274764482422 
		60 25.665274764482422;
createNode animCurveTA -n "Maugli_FKThumbFinger1_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 36.541774445263137 30 36.541774445263137 
		60 36.541774445263137;
createNode animCurveTA -n "Maugli_FKThumbFinger1_R_Man_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -67.421493922591793 30 -67.421493922591793 
		60 -67.421493922591793;
createNode animCurveTA -n "Maugli_FKThumbFinger2_R_Man_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 47.81080993924823 30 47.81080993924823 
		60 47.81080993924823;
createNode animCurveTU -n "Maugli_Main_Man_visibility";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTU -n "Maugli_Center_M_CenterBtwFeet";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_Center_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -8.4444129496952112 30 -8.4444129496952112 
		60 -8.4444129496952112;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_Center_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.96917688750520981 30 -0.96917688750520981 
		60 -0.96917688750520981;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_Center_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 3.1650958122187984 30 3.1650958122187984 
		60 3.1650958122187984;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "Maugli_Center_M_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.13106792216224994 15 -0.17074140583983671 
		30 -0.21780321647380352 45 -0.16772699835955554 60 -0.13106792216224994;
	setAttr -s 5 ".kit[0:4]"  3 9 10 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 10 9 3;
createNode animCurveTL -n "Maugli_Center_M_translateY";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.024349347202935689 15 -0.032847471905034481 
		30 0.063014399497303197 45 0.1320873626515558 60 0.024349347202935689;
	setAttr -s 5 ".kit[1:4]"  10 1 10 2;
	setAttr -s 5 ".kot[1:4]"  10 1 10 2;
	setAttr -s 5 ".kix[0:4]"  0.99872666597366333 0.99925333261489868 
		0.98101907968521118 0.99925333261489868 0.97756338119506836;
	setAttr -s 5 ".kiy[0:4]"  -0.050448480993509293 0.038636185228824615 
		0.19391120970249176 -0.038636185228824615 -0.21064147353172302;
	setAttr -s 5 ".kox[0:4]"  0.98547297716140747 0.99925333261489868 
		0.98101907968521118 0.99925333261489868 1;
	setAttr -s 5 ".koy[0:4]"  -0.16983248293399811 0.038636185228824615 
		0.19391120970249176 -0.038636185228824615 0;
createNode animCurveTL -n "Maugli_Center_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.0012760952138130693 15 0.0024966984895456318 
		30 0.0080875321255873683 45 0.00694614502496331 60 -0.0012760952138130693;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTA -n "Maugli_IKLegBackBall_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "Maugli_FKIKLegBack_L_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegBack_L_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegBack_L_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 10 30 10 60 10;
createNode animCurveTU -n "Maugli_PoleLegBack_L_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 10 30 10 60 10;
createNode animCurveTL -n "Maugli_PoleLegBack_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_PoleLegBack_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_PoleLegBack_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "Maugli_IKLegBack_L_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
createNode animCurveTU -n "Maugli_IKLegBack_L_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
createNode animCurveTU -n "Maugli_IKLegBack_L_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "Maugli_IKLegBack_L_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "Maugli_IKLegBack_L_legAim";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 10 30 10 60 10;
createNode animCurveTU -n "Maugli_IKLegBack_L_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 25 30 25 60 25;
createNode animCurveTU -n "Maugli_IKLegBack_L_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "Maugli_IKLegBack_L_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegBack_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegBack_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegBack_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_IKLegBack_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_IKLegBack_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.76278640316887203 30 -0.76278640316887203 
		60 -0.76278640316887203;
createNode animCurveTL -n "Maugli_IKLegBack_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_BendNeck_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_BendNeck_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_BendNeck_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "Maugli_FKIKSpine_M_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTU -n "Maugli_FKIKSpine_M_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTU -n "Maugli_FKIKSpine_M_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegBackBall_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegBackHeel_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "Maugli_FKIKLegBack_R_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegBack_R_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegBack_R_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 10 30 10 60 10;
createNode animCurveTU -n "Maugli_PoleLegBack_R_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 10 30 10 60 10;
createNode animCurveTL -n "Maugli_PoleLegBack_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -2.2204460492503131e-016 30 -2.2204460492503131e-016 
		60 -2.2204460492503131e-016;
createNode animCurveTL -n "Maugli_PoleLegBack_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_PoleLegBack_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -5.5511151231257827e-017 30 -5.5511151231257827e-017 
		60 -5.5511151231257827e-017;
createNode animCurveTU -n "Maugli_IKLegBack_R_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
createNode animCurveTU -n "Maugli_IKLegBack_R_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
createNode animCurveTU -n "Maugli_IKLegBack_R_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "Maugli_IKLegBack_R_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "Maugli_IKLegBack_R_legAim";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 10 30 10 60 10;
createNode animCurveTU -n "Maugli_IKLegBack_R_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 25 30 25 60 25;
createNode animCurveTU -n "Maugli_IKLegBack_R_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "Maugli_IKLegBack_R_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegBack_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -17.042137663821414 30 -17.042137663821414 
		60 -17.042137663821414;
createNode animCurveTA -n "Maugli_IKLegBack_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegBack_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_IKLegBack_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.1102230246251563e-016 30 1.1102230246251563e-016 
		60 1.1102230246251563e-016;
createNode animCurveTL -n "Maugli_IKLegBack_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.019491142195864015 30 0.019491142195864015 
		60 0.019491142195864015;
createNode animCurveTL -n "Maugli_IKLegBack_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.063585363072848899 30 -0.063585363072848899 
		60 -0.063585363072848899;
createNode animCurveTU -n "Maugli_FKIKSplineTail_M_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTU -n "Maugli_FKIKSplineTail_M_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTU -n "Maugli_FKIKSplineTail_M_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 10 30 10 60 10;
createNode animCurveTU -n "Maugli_WagCurveSplineTail_M_increment";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
createNode animCurveTU -n "Maugli_WagCurveSplineTail_M_multiply";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
createNode animCurveTU -n "Maugli_WagCurveSplineTail_M_timeOffset";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
createNode animCurveTU -n "Maugli_WagCurveSplineTail_M_enable";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTA -n "Maugli_WagCurveSplineTail_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_WagCurveSplineTail_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_WagCurveSplineTail_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "Maugli_IKSplineTail2_M_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 16 0 30 0 46 0 60 0;
createNode animCurveTU -n "Maugli_IKSplineTail2_M_twist";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 16 0 30 0 46 0 60 0;
createNode animCurveTU -n "Maugli_IKSplineTail2_M_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 16 0 30 0 46 0 60 0;
createNode animCurveTL -n "Maugli_IKSplineTail2_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.31618923007172439 16 -0.20746374223260014 
		30 0.041813942338092103 46 -0.21442708079874079 60 -0.31618923007172439;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTL -n "Maugli_IKSplineTail2_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.0020975550085076 16 -0.74896744597179421 
		30 -0.42954668889066783 46 -0.30035823441275511 60 -1.0020975550085076;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTL -n "Maugli_IKSplineTail2_M_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.80886811842270168 16 0.2770805953394157 
		30 -0.40000523827112511 46 0.29552038248337642 60 0.80886811842270168;
	setAttr -s 5 ".kit[0:4]"  3 9 10 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 10 9 3;
createNode animCurveTU -n "Maugli_IKSplineTail1_M_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 16 0 30 0 60 0;
createNode animCurveTL -n "Maugli_IKSplineTail1_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 3.1086244689504383e-015 16 0.11051668924786751 
		30 -0.17508233066507506 46 -0.14178176671799281 60 3.1086244689504383e-015;
	setAttr -s 5 ".kit[2:4]"  9 9 10;
	setAttr -s 5 ".kot[2:4]"  9 9 10;
createNode animCurveTL -n "Maugli_IKSplineTail1_M_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.16519211009181056 16 -0.12240126127207512 
		30 -0.11798409442045887 46 -0.20548793379131514 60 -0.16519211009181056;
createNode animCurveTL -n "Maugli_IKSplineTail1_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.010972047845733357 16 -0.49874964996817089 
		30 0.24455840376631341 46 0.4910564903071073 60 0.010972047845733357;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_HipSwingerRoot_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_FKRump_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -18.638044314952673 30 -18.638044314952673 
		60 -18.638044314952673;
createNode animCurveTA -n "Maugli_FKRump_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 5.9273289705481567 30 5.9273289705481567 
		60 5.9273289705481567;
createNode animCurveTA -n "Maugli_FKRump_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 12.021048230974857 30 12.021048230974857 
		60 12.021048230974857;
createNode animCurveTL -n "Maugli_FKRump_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -5.5511151231257827e-017 30 -5.5511151231257827e-017 
		60 -5.5511151231257827e-017;
createNode animCurveTL -n "Maugli_FKRump_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 2.2204460492503131e-016 30 2.2204460492503131e-016 
		60 2.2204460492503131e-016;
createNode animCurveTL -n "Maugli_FKRump_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 2.2204460492503131e-016 30 2.2204460492503131e-016 
		60 2.2204460492503131e-016;
createNode animCurveTA -n "Maugli_FKRump_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -18.710504463926263 30 -18.710504463926263 
		60 -18.710504463926263;
createNode animCurveTA -n "Maugli_FKRump_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 8.2582530676151027 30 8.2582530676151027 
		60 8.2582530676151027;
createNode animCurveTA -n "Maugli_FKRump_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 5.1050521316126698 30 5.1050521316126698 
		60 5.1050521316126698;
createNode animCurveTL -n "Maugli_FKRump_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 5.5511151231257827e-017 30 5.5511151231257827e-017 
		60 5.5511151231257827e-017;
createNode animCurveTL -n "Maugli_FKRump_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_FKRump_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_FKBackA_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -6.1344158462123248 30 -6.1344158462123248 
		60 -6.1344158462123248;
createNode animCurveTA -n "Maugli_FKBackA_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -2.6442010631261756 30 -2.6442010631261756 
		60 -2.6442010631261756;
createNode animCurveTA -n "Maugli_FKBackA_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.28408691297585409 30 0.28408691297585409 
		60 0.28408691297585409;
createNode animCurveTA -n "Maugli_FKBackB_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -4.0937696667714745 30 1.1199402602312341 
		60 -4.0937696667714745;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_FKBackB_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -8.7401097734428159 30 -8.7604723829787972 
		60 -8.7401097734428159;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_FKBackB_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.62309581808855541 30 -0.17059264212803807 
		60 0.62309581808855541;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_FKChest_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -25.928322657740519 30 -25.928322657740519 
		60 -25.928322657740519;
createNode animCurveTA -n "Maugli_FKChest_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -6.0685067306724134 30 -6.0685067306724134 
		60 -6.0685067306724134;
createNode animCurveTA -n "Maugli_FKChest_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 2.6635387051032011 30 2.6635387051032011 
		60 2.6635387051032011;
createNode animCurveTA -n "Maugli_FKNeck_M_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 22.628337533497174 30 17.178942222553893 
		60 22.628337533497174;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_FKNeck_M_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 3.6826813105759961 30 2.8428378311542639 
		60 3.6826813105759961;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_FKNeck_M_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 2.2991021693981635 30 2.4066400968979353 
		60 2.2991021693981635;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "Maugli_FKHead_M_Global";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 10 30 10 60 10;
createNode animCurveTA -n "Maugli_FKHead_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -7.8426637274840703 30 -4.0792577576891169 
		60 -7.8426637274840703;
createNode animCurveTA -n "Maugli_FKHead_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -7.5490945101966842 30 -7.5490945101966842 
		60 -7.5490945101966842;
createNode animCurveTA -n "Maugli_FKHead_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 5.461028169262887 30 5.461028169262887 
		60 5.461028169262887;
createNode animCurveTU -n "Maugli_Main_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
createNode animCurveTU -n "Maugli_Main_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
createNode animCurveTU -n "Maugli_Main_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
createNode animCurveTA -n "Maugli_Main_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_Main_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_Main_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_Main_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_Main_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_Main_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "Maugli_Main_visibility";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTA -n "Maugli_kolchan_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -16.498609615445837 30 -10.716437729508922 
		60 -16.498609615445837;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_kolchan_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -6.4006181765439756 30 -9.7597458966341701 
		60 -6.4006181765439756;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_kolchan_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.8111494521402616 30 4.3330491528251951 
		60 1.8111494521402616;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_yashik_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_yashik_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_yashik_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_yashik_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_yashik_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_yashik_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_l_ear_control_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 1.9619322075408607 60 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_l_ear_control_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 6.1654728885594263 60 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_l_ear_control_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 -16.437633346909273 60 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_r_ear_control1_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 -5.1355351464095467 60 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_r_ear_control1_rotateY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 4.845712363434596 60 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_r_ear_control1_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 18.991894060039158 60 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "Maugli_jaw_C_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 4.3969582329520716 60 0;
createNode animCurveTA -n "Maugli_spear_control_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_spear_control_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_spear_control_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_spear_control_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.041982630251665931 30 0.041982630251665931 
		60 0.041982630251665931;
createNode animCurveTL -n "Maugli_spear_control_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.05682005777595385 30 -0.05682005777595385 
		60 -0.05682005777595385;
createNode animCurveTL -n "Maugli_spear_control_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.19304667407551657 30 0.19304667407551657 
		60 0.19304667407551657;
createNode animCurveTU -n "Maugli_spear_control_World_Hands";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTA -n "Maugli_IKLegFrontBall_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegFrontBall_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegFrontHeel_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.1 30 1.1 60 1.1;
createNode animCurveTU -n "Maugli_IKLegFront_R_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.1 30 1.1 60 1.1;
createNode animCurveTU -n "Maugli_IKLegFront_R_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_legAim";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 10 30 10 60 10;
createNode animCurveTU -n "Maugli_IKLegFront_R_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 25 30 25 60 25;
createNode animCurveTU -n "Maugli_IKLegFront_R_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "Maugli_IKLegFront_R_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegFront_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 13.452853449395933 30 13.452853449395933 
		60 13.452853449395933;
createNode animCurveTA -n "Maugli_IKLegFront_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegFront_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_IKLegFront_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 5.5511151231257852e-017 30 5.5511151231257852e-017 
		60 5.5511151231257852e-017;
createNode animCurveTL -n "Maugli_IKLegFront_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.78767523172948961 30 -0.78767523172948961 
		60 -0.78767523172948961;
createNode animCurveTL -n "Maugli_IKLegFront_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.077325821529500835 30 -0.077325821529500835 
		60 -0.077325821529500835;
createNode animCurveTU -n "Maugli_IKLegFront_L_Lenght2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.1 30 1.1 60 1.1;
createNode animCurveTU -n "Maugli_IKLegFront_L_Lenght1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.1 30 1.1 60 1.1;
createNode animCurveTU -n "Maugli_IKLegFront_L_antiPop";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "Maugli_IKLegFront_L_stretchy";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "Maugli_IKLegFront_L_legAim";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 10 30 10 60 10;
createNode animCurveTU -n "Maugli_IKLegFront_L_rollAngle";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 25 30 25 60 25;
createNode animCurveTU -n "Maugli_IKLegFront_L_roll";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "Maugli_IKLegFront_L_swivel";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegFront_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -4.3689304491953465 30 -4.3689304491953465 
		60 -4.3689304491953465;
createNode animCurveTA -n "Maugli_IKLegFront_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_IKLegFront_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_IKLegFront_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_IKLegFront_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.063844748963588188 30 -0.063844748963588188 
		60 -0.063844748963588188;
createNode animCurveTL -n "Maugli_IKLegFront_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.072835230653514785 30 -0.072835230653514785 
		60 -0.072835230653514785;
createNode animCurveTU -n "Maugli_FKIKLegFront_L_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegFront_L_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegFront_L_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 10 30 10 60 10;
createNode animCurveTU -n "Maugli_FKIKLegFront_R_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegFront_R_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTU -n "Maugli_FKIKLegFront_R_FKIKBlend";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 10 30 10 60 10;
createNode animCurveTA -n "Maugli_FKScapula_L_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_FKScapula_L_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_FKScapula_L_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_FKScapula_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -2.2204460492503131e-016 30 -2.2204460492503131e-016 
		60 -2.2204460492503131e-016;
createNode animCurveTL -n "Maugli_FKScapula_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -1.1102230246251565e-016 30 -1.1102230246251565e-016 
		60 -1.1102230246251565e-016;
createNode animCurveTL -n "Maugli_FKScapula_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 4.4408920985006262e-016 30 4.4408920985006262e-016 
		60 4.4408920985006262e-016;
createNode animCurveTA -n "Maugli_FKScapula_R_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_FKScapula_R_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "Maugli_FKScapula_R_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "Maugli_FKScapula_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -1.1102230246251565e-016 30 -1.1102230246251565e-016 
		60 -1.1102230246251565e-016;
createNode animCurveTL -n "Maugli_FKScapula_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -2.2204460492503131e-016 30 -2.2204460492503131e-016 
		60 -2.2204460492503131e-016;
createNode animCurveTL -n "Maugli_FKScapula_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -2.2204460492503131e-016 30 -2.2204460492503131e-016 
		60 -2.2204460492503131e-016;
createNode animCurveTU -n "Maugli_PoleLegFront_L_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 10 30 10 60 10;
createNode animCurveTL -n "Maugli_PoleLegFront_L_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.34369246973235407 30 0.34369246973235407 
		60 0.34369246973235407;
createNode animCurveTL -n "Maugli_PoleLegFront_L_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.08732959492146955 30 0.08732959492146955 
		60 0.08732959492146955;
createNode animCurveTL -n "Maugli_PoleLegFront_L_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.27202670267238233 30 -0.27202670267238233 
		60 -0.27202670267238233;
createNode animCurveTU -n "Maugli_PoleLegFront_R_follow";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 10 30 10 60 10;
createNode animCurveTL -n "Maugli_PoleLegFront_R_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.31678960075780738 30 0.31678960075780738 
		60 0.31678960075780738;
createNode animCurveTL -n "Maugli_PoleLegFront_R_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.11971028970415042 30 -0.11971028970415042 
		60 -0.11971028970415042;
createNode animCurveTL -n "Maugli_PoleLegFront_R_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.0005730959429199018 30 0.0005730959429199018 
		60 0.0005730959429199018;
createNode animCurveTL -n "curve1_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "curve1_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "curve1_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "curve1_visibility";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTA -n "curve1_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "curve1_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "curve1_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTU -n "curve1_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
createNode animCurveTU -n "curve1_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
createNode animCurveTU -n "curve1_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
createNode animCurveTL -n "IKXSplineTailCurve_M_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 4.0142992214232583e-036 30 4.0142992214232583e-036 
		60 4.0142992214232583e-036;
createNode animCurveTL -n "IKXSplineTailCurve_M_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTL -n "IKXSplineTailCurve_M_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 30 0 60 0;
createNode animCurveTA -n "IKXSplineTailCurve_M_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -1.272221872585407e-014 30 -1.272221872585407e-014 
		60 -1.272221872585407e-014;
createNode animCurveTA -n "IKXSplineTailCurve_M_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.2722218725854067e-014 30 1.2722218725854067e-014 
		60 1.2722218725854067e-014;
createNode animCurveTA -n "IKXSplineTailCurve_M_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 2.8249000307521015e-030 30 2.8249000307521015e-030 
		60 2.8249000307521015e-030;
createNode animCurveTU -n "IKXSplineTailCurve_M_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
createNode animCurveTU -n "IKXSplineTailCurve_M_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
createNode animCurveTU -n "IKXSplineTailCurve_M_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 30 1 60 1;
createNode lightLinker -n "lightLinker3";
	setAttr -s 7 ".lnk";
	setAttr -s 7 ".slnk";
select -ne :time1;
	setAttr -av -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 60;
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
connectAttr "idle01Source.cl" "clipLibrary1.sc[0]";
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
connectAttr "IKXSplineTailCurve_M_translateX.a" "clipLibrary1.cel[0].cev[477].cevr"
		;
connectAttr "IKXSplineTailCurve_M_translateY.a" "clipLibrary1.cel[0].cev[478].cevr"
		;
connectAttr "IKXSplineTailCurve_M_translateZ.a" "clipLibrary1.cel[0].cev[479].cevr"
		;
connectAttr "IKXSplineTailCurve_M_rotateX.a" "clipLibrary1.cel[0].cev[480].cevr"
		;
connectAttr "IKXSplineTailCurve_M_rotateY.a" "clipLibrary1.cel[0].cev[481].cevr"
		;
connectAttr "IKXSplineTailCurve_M_rotateZ.a" "clipLibrary1.cel[0].cev[482].cevr"
		;
connectAttr "IKXSplineTailCurve_M_scaleX.a" "clipLibrary1.cel[0].cev[483].cevr";
connectAttr "IKXSplineTailCurve_M_scaleY.a" "clipLibrary1.cel[0].cev[484].cevr";
connectAttr "IKXSplineTailCurve_M_scaleZ.a" "clipLibrary1.cel[0].cev[485].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker3.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker3.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker3.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker3.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker3.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker3.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker3.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker3.slnk[1].solk";
connectAttr "lightLinker3.msg" ":lightList1.ln" -na;
// End of idle01.ma
