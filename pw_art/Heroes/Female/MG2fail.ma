//Maya ASCII 2008 scene
//Name: Minigame2_fail.ma
//Last modified: Mon, Dec 07, 2009 03:46:59 PM
//Codeset: 1251
requires maya "2008";
requires "Mayatomr" "9.0.1.4m - 3.6.51.0 ";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Unlimited 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200802250025-718075";
fileInfo "osv" "Microsoft Windows XP Service Pack 3 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 649 ".cel[0].cev";
	setAttr ".cd[0].cm" -type "characterMapping" 649 "cmp_lock20|back_skirt_b_CTRL.rotateZ" 
		2 1 "cmp_lock20|back_skirt_b_CTRL.rotateY" 2 2 "cmp_lock20|back_skirt_b_CTRL.rotateX" 
		2 3 "cmp_lock19|back_skirt_b_CTRL.rotateZ" 2 4 "cmp_lock19|back_skirt_b_CTRL.rotateY" 
		2 5 "cmp_lock19|back_skirt_b_CTRL.rotateX" 2 6 "R_cloak_C_CTRL.rotateZ" 
		2 7 "R_cloak_C_CTRL.rotateY" 2 8 "R_cloak_C_CTRL.rotateX" 2 
		9 "R_cloak_B_CTRL.rotateZ" 2 10 "R_cloak_B_CTRL.rotateY" 2 11 "R_cloak_B_CTRL.rotateX" 
		2 12 "R_cloak_A_CTRL.rotateZ" 2 13 "R_cloak_A_CTRL.rotateY" 2 
		14 "R_cloak_A_CTRL.rotateX" 2 15 "L_cloak_C_CTRL.rotateZ" 2 16 "L_cloak_C_CTRL.rotateY" 
		2 17 "L_cloak_C_CTRL.rotateX" 2 18 "L_cloak_B_CTRL.rotateZ" 2 
		19 "L_cloak_B_CTRL.rotateY" 2 20 "L_cloak_B_CTRL.rotateX" 2 21 "L_cloak_A_CTRL.rotateZ" 
		2 22 "L_cloak_A_CTRL.rotateY" 2 23 "L_cloak_A_CTRL.rotateX" 2 
		24 "cloak_D_CTRL.rotateZ" 2 25 "cloak_D_CTRL.rotateY" 2 26 "cloak_D_CTRL.rotateX" 
		2 27 "cloak_C_CTRL.rotateZ" 2 28 "cloak_C_CTRL.rotateY" 2 
		29 "cloak_C_CTRL.rotateX" 2 30 "cloak_B_CTRL.rotateZ" 2 31 "cloak_B_CTRL.rotateY" 
		2 32 "cloak_B_CTRL.rotateX" 2 33 "cloak_A_CTRL.rotateZ" 2 
		34 "cloak_A_CTRL.rotateY" 2 35 "cloak_A_CTRL.rotateX" 2 36 "cmp_lock18|back_skirt_b_CTRL.rotateZ" 
		2 37 "cmp_lock18|back_skirt_b_CTRL.rotateY" 2 38 "cmp_lock18|back_skirt_b_CTRL.rotateX" 
		2 39 "cmp_lock18|back_skirt_b_CTRL.translateZ" 1 1 "cmp_lock18|back_skirt_b_CTRL.translateY" 
		1 2 "cmp_lock18|back_skirt_b_CTRL.translateX" 1 3 "cmp_lock17|back_skirt_b_CTRL.rotateZ" 
		2 40 "cmp_lock17|back_skirt_b_CTRL.rotateY" 2 41 "cmp_lock17|back_skirt_b_CTRL.rotateX" 
		2 42 "cmp_lock17|back_skirt_b_CTRL.translateZ" 1 4 "cmp_lock17|back_skirt_b_CTRL.translateY" 
		1 5 "cmp_lock17|back_skirt_b_CTRL.translateX" 1 6 "cmp_lock5|back_skirt_b_CTRL.rotateZ" 
		2 43 "cmp_lock5|back_skirt_b_CTRL.rotateY" 2 44 "cmp_lock5|back_skirt_b_CTRL.rotateX" 
		2 45 "cmp_lock5|back_skirt_b_CTRL.translateZ" 1 7 "cmp_lock5|back_skirt_b_CTRL.translateY" 
		1 8 "cmp_lock5|back_skirt_b_CTRL.translateX" 1 9 "back_skirt_a_CTRL.rotateZ" 
		2 46 "back_skirt_a_CTRL.rotateY" 2 47 "back_skirt_a_CTRL.rotateX" 
		2 48 "back_skirt_a_CTRL.translateZ" 1 10 "back_skirt_a_CTRL.translateY" 
		1 11 "back_skirt_a_CTRL.translateX" 1 12 "front_skirt_b_CTRL.rotateZ" 
		2 49 "front_skirt_b_CTRL.rotateY" 2 50 "front_skirt_b_CTRL.rotateX" 
		2 51 "front_skirt_b_CTRL.translateZ" 1 13 "front_skirt_b_CTRL.translateY" 
		1 14 "front_skirt_b_CTRL.translateX" 1 15 "front_skirt_a_CTRL.rotateZ" 
		2 52 "front_skirt_a_CTRL.rotateY" 2 53 "front_skirt_a_CTRL.rotateX" 
		2 54 "front_skirt_a_CTRL.translateZ" 1 16 "front_skirt_a_CTRL.translateY" 
		1 17 "front_skirt_a_CTRL.translateX" 1 18 "skirt_HipA_L_CTRL.rotateZ" 
		2 55 "skirt_HipA_L_CTRL.rotateY" 2 56 "skirt_HipA_L_CTRL.rotateX" 
		2 57 "skirt_HipA_L_CTRL.translateZ" 1 19 "skirt_HipA_L_CTRL.translateY" 
		1 20 "skirt_HipA_L_CTRL.translateX" 1 21 "skirt_Hip_L_CTRL.rotateZ" 
		2 58 "skirt_Hip_L_CTRL.rotateY" 2 59 "skirt_Hip_L_CTRL.rotateX" 
		2 60 "skirt_Hip_L_CTRL.translateZ" 1 22 "skirt_Hip_L_CTRL.translateY" 
		1 23 "skirt_Hip_L_CTRL.translateX" 1 24 "skirt_HipA_R_CTRL.rotateZ" 
		2 61 "skirt_HipA_R_CTRL.rotateY" 2 62 "skirt_HipA_R_CTRL.rotateX" 
		2 63 "skirt_HipA_R_CTRL.translateZ" 1 25 "skirt_HipA_R_CTRL.translateY" 
		1 26 "skirt_HipA_R_CTRL.translateX" 1 27 "skirt_Hip_R_CTRL.rotateZ" 
		2 64 "skirt_Hip_R_CTRL.rotateY" 2 65 "skirt_Hip_R_CTRL.rotateX" 
		2 66 "skirt_Hip_R_CTRL.translateZ" 1 28 "skirt_Hip_R_CTRL.translateY" 
		1 29 "skirt_Hip_R_CTRL.translateX" 1 30 "Center_M.CenterBtwFeet" 
		0 1 "Center_M.rotateZ" 2 67 "Center_M.rotateY" 2 68 "Center_M.rotateX" 
		2 69 "Center_M.translateZ" 1 31 "Center_M.translateY" 1 32 "Center_M.translateX" 
		1 33 "CenterExtra_M.rotateZ" 2 70 "CenterExtra_M.rotateY" 2 
		71 "CenterExtra_M.rotateX" 2 72 "CenterExtra_M.translateZ" 1 34 "CenterExtra_M.translateY" 
		1 35 "CenterExtra_M.translateX" 1 36 "Fingers_L.Cup" 0 2 "Fingers_L.Spread" 
		0 3 "Fingers_L.ThumbFingerCurl" 0 4 "Fingers_L.PinkyFingerCurl" 
		0 5 "Fingers_L.RingFingerCurl" 0 6 "Fingers_L.MiddleFingerCurl" 
		0 7 "Fingers_L.IndexFingerCurl" 0 8 "IKExtraLegBall_L.rotateZ" 
		2 73 "IKExtraLegBall_L.rotateY" 2 74 "IKExtraLegBall_L.rotateX" 
		2 75 "IKLegBall_L.rotateX" 2 76 "IKExtraLegToe_L.rotateZ" 2 
		77 "IKExtraLegToe_L.rotateY" 2 78 "IKExtraLegToe_L.rotateX" 2 79 "IKLegToe_L.rotateZ" 
		2 80 "IKLegToe_L.rotateY" 2 81 "IKLegToe_L.rotateX" 2 82 "IKExtraLegHeel_L.rotateZ" 
		2 83 "IKExtraLegHeel_L.rotateY" 2 84 "IKExtraLegHeel_L.rotateX" 
		2 85 "IKLegHeel_L.rotateZ" 2 86 "IKLegHeel_L.rotateY" 2 87 "IKLegHeel_L.rotateX" 
		2 88 "FKIKLeg_L.IKVis" 0 9 "FKIKLeg_L.FKVis" 0 10 "FKIKLeg_L.FKIKBlend" 
		0 11 "PoleExtraLeg_L.translateZ" 1 37 "PoleExtraLeg_L.translateY" 
		1 38 "PoleExtraLeg_L.translateX" 1 39 "PoleLeg_L.follow" 0 
		12 "PoleLeg_L.translateZ" 1 40 "PoleLeg_L.translateY" 1 41 "PoleLeg_L.translateX" 
		1 42 "IKExtraLeg_L.rotateZ" 2 89 "IKExtraLeg_L.rotateY" 2 
		90 "IKExtraLeg_L.rotateX" 2 91 "IKExtraLeg_L.translateZ" 1 43 "IKExtraLeg_L.translateY" 
		1 44 "IKExtraLeg_L.translateX" 1 45 "IKLeg_L.Lenght2" 0 13 "IKLeg_L.Lenght1" 
		0 14 "IKLeg_L.antiPop" 0 15 "IKLeg_L.stretchy" 0 16 "IKLeg_L.rollAngle" 
		0 17 "IKLeg_L.roll" 0 18 "IKLeg_L.toe" 0 19 "IKLeg_L.swivel" 
		0 20 "IKLeg_L.rotateZ" 2 92 "IKLeg_L.rotateY" 2 93 "IKLeg_L.rotateX" 
		2 94 "IKLeg_L.translateZ" 1 46 "IKLeg_L.translateY" 1 47 "IKLeg_L.translateX" 
		1 48 "FKIKArm_L.IKVis" 0 21 "FKIKArm_L.FKVis" 0 22 "FKIKArm_L.FKIKBlend" 
		0 23 "PoleExtraArm_L.translateZ" 1 49 "PoleExtraArm_L.translateY" 
		1 50 "PoleExtraArm_L.translateX" 1 51 "PoleArm_L.follow" 0 
		24 "PoleArm_L.translateZ" 1 52 "PoleArm_L.translateY" 1 53 "PoleArm_L.translateX" 
		1 54 "IKExtraArm_L.rotateZ" 2 95 "IKExtraArm_L.rotateY" 2 
		96 "IKExtraArm_L.rotateX" 2 97 "IKExtraArm_L.translateZ" 1 55 "IKExtraArm_L.translateY" 
		1 56 "IKExtraArm_L.translateX" 1 57 "IKArm_L.Lenght2" 0 25 "IKArm_L.Lenght1" 
		0 26 "IKArm_L.antiPop" 0 27 "IKArm_L.stretchy" 0 28 "IKArm_L.follow" 
		0 29 "IKArm_L.rotateZ" 2 98 "IKArm_L.rotateY" 2 99 "IKArm_L.rotateX" 
		2 100 "IKArm_L.translateZ" 1 58 "IKArm_L.translateY" 1 59 "IKArm_L.translateX" 
		1 60 "Fingers_R.Cup" 0 30 "Fingers_R.Spread" 0 31 "Fingers_R.ThumbFingerCurl" 
		0 32 "Fingers_R.PinkyFingerCurl" 0 33 "Fingers_R.RingFingerCurl" 
		0 34 "Fingers_R.MiddleFingerCurl" 0 35 "Fingers_R.IndexFingerCurl" 
		0 36 "IKExtraSpine4_M.scaleZ" 0 37 "IKExtraSpine4_M.scaleY" 0 
		38 "IKExtraSpine4_M.scaleX" 0 39 "IKExtraSpine4_M.rotateZ" 2 101 "IKExtraSpine4_M.rotateY" 
		2 102 "IKExtraSpine4_M.rotateX" 2 103 "IKExtraSpine4_M.translateZ" 
		1 61 "IKExtraSpine4_M.translateY" 1 62 "IKExtraSpine4_M.translateX" 
		1 63 "IKExtraSpine4_M.visibility" 0 40 "IKSpine4_M.stretchy" 0 
		41 "IKSpine4_M.stiff" 0 42 "IKSpine4_M.rotateZ" 2 104 "IKSpine4_M.rotateY" 
		2 105 "IKSpine4_M.rotateX" 2 106 "IKSpine4_M.translateZ" 1 64 "IKSpine4_M.translateY" 
		1 65 "IKSpine4_M.translateX" 1 66 "IKExtraSpine2_M.scaleZ" 0 
		43 "IKExtraSpine2_M.scaleY" 0 44 "IKExtraSpine2_M.scaleX" 0 45 "IKExtraSpine2_M.rotateZ" 
		2 107 "IKExtraSpine2_M.rotateY" 2 108 "IKExtraSpine2_M.rotateX" 2 
		109 "IKExtraSpine2_M.translateZ" 1 67 "IKExtraSpine2_M.translateY" 1 
		68 "IKExtraSpine2_M.translateX" 1 69 "IKExtraSpine2_M.visibility" 0 
		46 "IKSpine2_M.stiff" 0 47 "IKSpine2_M.rotateZ" 2 110 "IKSpine2_M.rotateY" 
		2 111 "IKSpine2_M.rotateX" 2 112 "IKSpine2_M.translateZ" 1 70 "IKSpine2_M.translateY" 
		1 71 "IKSpine2_M.translateX" 1 72 "IKExtraSpine0_M.scaleZ" 0 
		48 "IKExtraSpine0_M.scaleY" 0 49 "IKExtraSpine0_M.scaleX" 0 50 "IKExtraSpine0_M.rotateZ" 
		2 113 "IKExtraSpine0_M.rotateY" 2 114 "IKExtraSpine0_M.rotateX" 2 
		115 "IKExtraSpine0_M.translateZ" 1 73 "IKExtraSpine0_M.translateY" 1 
		74 "IKExtraSpine0_M.translateX" 1 75 "IKExtraSpine0_M.visibility" 0 
		51 "IKSpine0_M.stiff" 0 52 "IKSpine0_M.rotateZ" 2 116 "IKSpine0_M.rotateY" 
		2 117 "IKSpine0_M.rotateX" 2 118 "IKSpine0_M.translateZ" 1 76 "IKSpine0_M.translateY" 
		1 77 "IKSpine0_M.translateX" 1 78 "IKExtraLegBall_R.rotateZ" 2 
		119 "IKExtraLegBall_R.rotateY" 2 120 "IKExtraLegBall_R.rotateX" 2 
		121 "IKLegBall_R.rotateX" 2 122 "IKExtraLegToe_R.rotateZ" 2 123 "IKExtraLegToe_R.rotateY" 
		2 124 "IKExtraLegToe_R.rotateX" 2 125 "IKLegToe_R.rotateZ" 2 
		126 "IKLegToe_R.rotateY" 2 127 "IKLegToe_R.rotateX" 2 128 "IKExtraLegHeel_R.rotateZ" 
		2 129 "IKExtraLegHeel_R.rotateY" 2 130 "IKExtraLegHeel_R.rotateX" 
		2 131 "IKLegHeel_R.rotateZ" 2 132 "IKLegHeel_R.rotateY" 2 133 "IKLegHeel_R.rotateX" 
		2 134 "FKIKLeg_R.IKVis" 0 53 "FKIKLeg_R.FKVis" 0 54 "FKIKLeg_R.FKIKBlend" 
		0 55 "PoleExtraLeg_R.translateZ" 1 79 "PoleExtraLeg_R.translateY" 
		1 80 "PoleExtraLeg_R.translateX" 1 81 "PoleLeg_R.follow" 0 
		56 "PoleLeg_R.translateZ" 1 82 "PoleLeg_R.translateY" 1 83 "PoleLeg_R.translateX" 
		1 84 "IKExtraLeg_R.rotateZ" 2 135 "IKExtraLeg_R.rotateY" 2 
		136 "IKExtraLeg_R.rotateX" 2 137 "IKExtraLeg_R.translateZ" 1 85 "IKExtraLeg_R.translateY" 
		1 86 "IKExtraLeg_R.translateX" 1 87 "IKLeg_R.Lenght2" 0 57 "IKLeg_R.Lenght1" 
		0 58 "IKLeg_R.antiPop" 0 59 "IKLeg_R.stretchy" 0 60 "IKLeg_R.rollAngle" 
		0 61 "IKLeg_R.roll" 0 62 "IKLeg_R.toe" 0 63 "IKLeg_R.swivel" 
		0 64 "IKLeg_R.rotateZ" 2 138 "IKLeg_R.rotateY" 2 139 "IKLeg_R.rotateX" 
		2 140 "IKLeg_R.translateZ" 1 88 "IKLeg_R.translateY" 1 89 "IKLeg_R.translateX" 
		1 90 "FKIKArm_R.IKVis" 0 65 "FKIKArm_R.FKVis" 0 66 "FKIKArm_R.FKIKBlend" 
		0 67 "PoleExtraArm_R.translateZ" 1 91 "PoleExtraArm_R.translateY" 
		1 92 "PoleExtraArm_R.translateX" 1 93 "PoleArm_R.follow" 0 
		68 "PoleArm_R.translateZ" 1 94 "PoleArm_R.translateY" 1 95 "PoleArm_R.translateX" 
		1 96 "IKExtraArm_R.rotateZ" 2 141 "IKExtraArm_R.rotateY" 2 
		142 "IKExtraArm_R.rotateX" 2 143 "IKExtraArm_R.translateZ" 1 97 "IKExtraArm_R.translateY" 
		1 98 "IKExtraArm_R.translateX" 1 99 "IKArm_R.Lenght2" 0 69 "IKArm_R.Lenght1" 
		0 70 "IKArm_R.antiPop" 0 71 "IKArm_R.stretchy" 0 72 "IKArm_R.follow" 
		0 73 "IKArm_R.rotateZ" 2 144 "IKArm_R.rotateY" 2 145 "IKArm_R.rotateX" 
		2 146 "IKArm_R.translateZ" 1 100 "IKArm_R.translateY" 1 101 "IKArm_R.translateX" 
		1 102 "HipSwingerRoot_M.rotateZ" 2 147 "HipSwingerRoot_M.rotateY" 
		2 148 "HipSwingerRoot_M.rotateX" 2 149 "FKExtraHip_L.rotateZ" 2 
		150 "FKExtraHip_L.rotateY" 2 151 "FKExtraHip_L.rotateX" 2 152 "FKHip_L.scaleZ" 
		0 74 "FKHip_L.scaleY" 0 75 "FKHip_L.scaleX" 0 76 "FKHip_L.rotateZ" 
		2 153 "FKHip_L.rotateY" 2 154 "FKHip_L.rotateX" 2 155 "FKExtraKnee_L.rotateZ" 
		2 156 "FKExtraKnee_L.rotateY" 2 157 "FKExtraKnee_L.rotateX" 2 
		158 "FKKnee_L.scaleZ" 0 77 "FKKnee_L.scaleY" 0 78 "FKKnee_L.scaleX" 
		0 79 "FKKnee_L.rotateZ" 2 159 "FKKnee_L.rotateY" 2 160 "FKKnee_L.rotateX" 
		2 161 "FKExtraAnkle_L.rotateZ" 2 162 "FKExtraAnkle_L.rotateY" 2 
		163 "FKExtraAnkle_L.rotateX" 2 164 "FKAnkle_L.scaleZ" 0 80 "FKAnkle_L.scaleY" 
		0 81 "FKAnkle_L.scaleX" 0 82 "FKAnkle_L.rotateZ" 2 165 "FKAnkle_L.rotateY" 
		2 166 "FKAnkle_L.rotateX" 2 167 "FKExtraMiddleToe1_L.rotateZ" 2 
		168 "FKExtraMiddleToe1_L.rotateY" 2 169 "FKExtraMiddleToe1_L.rotateX" 
		2 170 "FKMiddleToe1_L.scaleZ" 0 83 "FKMiddleToe1_L.scaleY" 0 
		84 "FKMiddleToe1_L.scaleX" 0 85 "FKMiddleToe1_L.rotateZ" 2 171 "FKMiddleToe1_L.rotateY" 
		2 172 "FKMiddleToe1_L.rotateX" 2 173 "FKExtraScapula_L.scaleZ" 0 
		86 "FKExtraScapula_L.scaleY" 0 87 "FKExtraScapula_L.scaleX" 0 88 "FKExtraScapula_L.rotateZ" 
		2 174 "FKExtraScapula_L.rotateY" 2 175 "FKExtraScapula_L.rotateX" 
		2 176 "FKExtraScapula_L.translateZ" 1 103 "FKExtraScapula_L.translateY" 
		1 104 "FKExtraScapula_L.translateX" 1 105 "FKScapula_L.scaleZ" 0 
		89 "FKScapula_L.scaleY" 0 90 "FKScapula_L.scaleX" 0 91 "FKScapula_L.rotateZ" 
		2 177 "FKScapula_L.rotateY" 2 178 "FKScapula_L.rotateX" 2 179 "FKScapula_L.translateZ" 
		1 106 "FKScapula_L.translateY" 1 107 "FKScapula_L.translateX" 1 
		108 "FKExtraShoulder_L.rotateZ" 2 180 "FKExtraShoulder_L.rotateY" 2 
		181 "FKExtraShoulder_L.rotateX" 2 182 "FKShoulder_L.scaleZ" 0 92 "FKShoulder_L.scaleY" 
		0 93 "FKShoulder_L.scaleX" 0 94 "FKShoulder_L.rotateZ" 2 183 "FKShoulder_L.rotateY" 
		2 184 "FKShoulder_L.rotateX" 2 185 "FKExtraElbow_L.rotateZ" 2 
		186 "FKExtraElbow_L.rotateY" 2 187 "FKExtraElbow_L.rotateX" 2 188 "FKElbow_L.scaleZ" 
		0 95 "FKElbow_L.scaleY" 0 96 "FKElbow_L.scaleX" 0 97 "FKElbow_L.rotateZ" 
		2 189 "FKElbow_L.rotateY" 2 190 "FKElbow_L.rotateX" 2 191 "FKExtraWrist_L.rotateZ" 
		2 192 "FKExtraWrist_L.rotateY" 2 193 "FKExtraWrist_L.rotateX" 2 
		194 "FKWrist_L.scaleZ" 0 98 "FKWrist_L.scaleY" 0 99 "FKWrist_L.scaleX" 
		0 100 "FKWrist_L.rotateZ" 2 195 "FKWrist_L.rotateY" 2 196 "FKWrist_L.rotateX" 
		2 197 "FKExtraMiddleFinger1_L.rotateZ" 2 198 "FKExtraMiddleFinger1_L.rotateY" 
		2 199 "FKExtraMiddleFinger1_L.rotateX" 2 200 "FKMiddleFinger1_L.scaleZ" 
		0 101 "FKMiddleFinger1_L.scaleY" 0 102 "FKMiddleFinger1_L.scaleX" 
		0 103 "FKMiddleFinger1_L.rotateZ" 2 201 "FKMiddleFinger1_L.rotateY" 
		2 202 "FKMiddleFinger1_L.rotateX" 2 203 "FKExtraMiddleFinger2_L.rotateZ" 
		2 204 "FKExtraMiddleFinger2_L.rotateY" 2 205 "FKExtraMiddleFinger2_L.rotateX" 
		2 206 "FKMiddleFinger2_L.scaleZ" 0 104 "FKMiddleFinger2_L.scaleY" 
		0 105 "FKMiddleFinger2_L.scaleX" 0 106 "FKMiddleFinger2_L.rotateZ" 
		2 207 "FKMiddleFinger2_L.rotateY" 2 208 "FKMiddleFinger2_L.rotateX" 
		2 209 "FKExtraMiddleFinger3_L.rotateZ" 2 210 "FKExtraMiddleFinger3_L.rotateY" 
		2 211 "FKExtraMiddleFinger3_L.rotateX" 2 212 "FKMiddleFinger3_L.scaleZ" 
		0 107 "FKMiddleFinger3_L.scaleY" 0 108 "FKMiddleFinger3_L.scaleX" 
		0 109 "FKMiddleFinger3_L.rotateZ" 2 213 "FKMiddleFinger3_L.rotateY" 
		2 214 "FKMiddleFinger3_L.rotateX" 2 215 "FKExtraThumbFinger1_L.rotateZ" 
		2 216 "FKExtraThumbFinger1_L.rotateY" 2 217 "FKExtraThumbFinger1_L.rotateX" 
		2 218 "FKThumbFinger1_L.scaleZ" 0 110 "FKThumbFinger1_L.scaleY" 0 
		111 "FKThumbFinger1_L.scaleX" 0 112 "FKThumbFinger1_L.rotateZ" 2 
		219 "FKThumbFinger1_L.rotateY" 2 220 "FKThumbFinger1_L.rotateX" 2 
		221 "FKExtraThumbFinger2_L.rotateZ" 2 222 "FKExtraThumbFinger2_L.rotateY" 
		2 223 "FKExtraThumbFinger2_L.rotateX" 2 224 "FKThumbFinger2_L.scaleZ" 
		0 113 "FKThumbFinger2_L.scaleY" 0 114 "FKThumbFinger2_L.scaleX" 0 
		115 "FKThumbFinger2_L.rotateZ" 2 225 "FKThumbFinger2_L.rotateY" 2 
		226 "FKThumbFinger2_L.rotateX" 2 227 "FKExtraThumbFinger3_L.rotateZ" 2 
		228 "FKExtraThumbFinger3_L.rotateY" 2 229 "FKExtraThumbFinger3_L.rotateX" 
		2 230 "FKThumbFinger3_L.scaleZ" 0 116 "FKThumbFinger3_L.scaleY" 0 
		117 "FKThumbFinger3_L.scaleX" 0 118 "FKThumbFinger3_L.rotateZ" 2 
		231 "FKThumbFinger3_L.rotateY" 2 232 "FKThumbFinger3_L.rotateX" 2 
		233 "FKExtraHip_R.rotateZ" 2 234 "FKExtraHip_R.rotateY" 2 235 "FKExtraHip_R.rotateX" 
		2 236 "FKHip_R.scaleZ" 0 119 "FKHip_R.scaleY" 0 120 "FKHip_R.scaleX" 
		0 121 "FKHip_R.rotateZ" 2 237 "FKHip_R.rotateY" 2 238 "FKHip_R.rotateX" 
		2 239 "FKExtraKnee_R.rotateZ" 2 240 "FKExtraKnee_R.rotateY" 2 
		241 "FKExtraKnee_R.rotateX" 2 242 "FKKnee_R.scaleZ" 0 122 "FKKnee_R.scaleY" 
		0 123 "FKKnee_R.scaleX" 0 124 "FKKnee_R.rotateZ" 2 243 "FKKnee_R.rotateY" 
		2 244 "FKKnee_R.rotateX" 2 245 "FKExtraAnkle_R.rotateZ" 2 246 "FKExtraAnkle_R.rotateY" 
		2 247 "FKExtraAnkle_R.rotateX" 2 248 "FKAnkle_R.scaleZ" 0 125 "FKAnkle_R.scaleY" 
		0 126 "FKAnkle_R.scaleX" 0 127 "FKAnkle_R.rotateZ" 2 249 "FKAnkle_R.rotateY" 
		2 250 "FKAnkle_R.rotateX" 2 251 "FKExtraMiddleToe1_R.rotateZ" 2 
		252 "FKExtraMiddleToe1_R.rotateY" 2 253 "FKExtraMiddleToe1_R.rotateX" 
		2 254 "FKMiddleToe1_R.scaleZ" 0 128 "FKMiddleToe1_R.scaleY" 0 
		129 "FKMiddleToe1_R.scaleX" 0 130 "FKMiddleToe1_R.rotateZ" 2 255 "FKMiddleToe1_R.rotateY" 
		2 256 "FKMiddleToe1_R.rotateX" 2 257 "FKExtraBackA_M.rotateZ" 2 
		258 "FKExtraBackA_M.rotateY" 2 259 "FKExtraBackA_M.rotateX" 2 260 "FKBackA_M.scaleZ" 
		0 131 "FKBackA_M.scaleY" 0 132 "FKBackA_M.scaleX" 0 133 "FKBackA_M.rotateZ" 
		2 261 "FKBackA_M.rotateY" 2 262 "FKBackA_M.rotateX" 2 263 "FKExtraBackB_M.rotateZ" 
		2 264 "FKExtraBackB_M.rotateY" 2 265 "FKExtraBackB_M.rotateX" 2 
		266 "FKBackB_M.scaleZ" 0 134 "FKBackB_M.scaleY" 0 135 "FKBackB_M.scaleX" 
		0 136 "FKBackB_M.rotateZ" 2 267 "FKBackB_M.rotateY" 2 268 "FKBackB_M.rotateX" 
		2 269 "FKExtraChest_M.rotateZ" 2 270 "FKExtraChest_M.rotateY" 2 
		271 "FKExtraChest_M.rotateX" 2 272 "FKChest_M.scaleZ" 0 137 "FKChest_M.scaleY" 
		0 138 "FKChest_M.scaleX" 0 139 "FKChest_M.rotateZ" 2 273 "FKChest_M.rotateY" 
		2 274 "FKChest_M.rotateX" 2 275 "FKExtraNeck_M.rotateZ" 2 276 "FKExtraNeck_M.rotateY" 
		2 277 "FKExtraNeck_M.rotateX" 2 278 "FKNeck_M.scaleZ" 0 140 "FKNeck_M.scaleY" 
		0 141 "FKNeck_M.scaleX" 0 142 "FKNeck_M.rotateZ" 2 279 "FKNeck_M.rotateY" 
		2 280 "FKNeck_M.rotateX" 2 281 "FKExtraHead_M.rotateZ" 2 282 "FKExtraHead_M.rotateY" 
		2 283 "FKExtraHead_M.rotateX" 2 284 "FKHead_M.scaleZ" 0 143 "FKHead_M.scaleY" 
		0 144 "FKHead_M.scaleX" 0 145 "FKHead_M.rotateZ" 2 285 "FKHead_M.rotateY" 
		2 286 "FKHead_M.rotateX" 2 287 "FKExtraScapula_R.scaleZ" 0 146 "FKExtraScapula_R.scaleY" 
		0 147 "FKExtraScapula_R.scaleX" 0 148 "FKExtraScapula_R.rotateZ" 
		2 288 "FKExtraScapula_R.rotateY" 2 289 "FKExtraScapula_R.rotateX" 
		2 290 "FKExtraScapula_R.translateZ" 1 109 "FKExtraScapula_R.translateY" 
		1 110 "FKExtraScapula_R.translateX" 1 111 "FKScapula_R.scaleZ" 0 
		149 "FKScapula_R.scaleY" 0 150 "FKScapula_R.scaleX" 0 151 "FKScapula_R.rotateZ" 
		2 291 "FKScapula_R.rotateY" 2 292 "FKScapula_R.rotateX" 2 293 "FKScapula_R.translateZ" 
		1 112 "FKScapula_R.translateY" 1 113 "FKScapula_R.translateX" 1 
		114 "FKExtraShoulder_R.rotateZ" 2 294 "FKExtraShoulder_R.rotateY" 2 
		295 "FKExtraShoulder_R.rotateX" 2 296 "FKShoulder_R.scaleZ" 0 152 "FKShoulder_R.scaleY" 
		0 153 "FKShoulder_R.scaleX" 0 154 "FKShoulder_R.rotateZ" 2 297 "FKShoulder_R.rotateY" 
		2 298 "FKShoulder_R.rotateX" 2 299 "FKExtraElbow_R.rotateZ" 2 
		300 "FKExtraElbow_R.rotateY" 2 301 "FKExtraElbow_R.rotateX" 2 302 "FKElbow_R.scaleZ" 
		0 155 "FKElbow_R.scaleY" 0 156 "FKElbow_R.scaleX" 0 157 "FKElbow_R.rotateZ" 
		2 303 "FKElbow_R.rotateY" 2 304 "FKElbow_R.rotateX" 2 305 "FKExtraWrist_R.rotateZ" 
		2 306 "FKExtraWrist_R.rotateY" 2 307 "FKExtraWrist_R.rotateX" 2 
		308 "FKWrist_R.scaleZ" 0 158 "FKWrist_R.scaleY" 0 159 "FKWrist_R.scaleX" 
		0 160 "FKWrist_R.rotateZ" 2 309 "FKWrist_R.rotateY" 2 310 "FKWrist_R.rotateX" 
		2 311 "FKExtraMiddleFinger1_R.rotateZ" 2 312 "FKExtraMiddleFinger1_R.rotateY" 
		2 313 "FKExtraMiddleFinger1_R.rotateX" 2 314 "FKMiddleFinger1_R.scaleZ" 
		0 161 "FKMiddleFinger1_R.scaleY" 0 162 "FKMiddleFinger1_R.scaleX" 
		0 163 "FKMiddleFinger1_R.rotateZ" 2 315 "FKMiddleFinger1_R.rotateY" 
		2 316 "FKMiddleFinger1_R.rotateX" 2 317 "FKExtraMiddleFinger2_R.rotateZ" 
		2 318 "FKExtraMiddleFinger2_R.rotateY" 2 319 "FKExtraMiddleFinger2_R.rotateX" 
		2 320 "FKMiddleFinger2_R.scaleZ" 0 164 "FKMiddleFinger2_R.scaleY" 
		0 165 "FKMiddleFinger2_R.scaleX" 0 166 "FKMiddleFinger2_R.rotateZ" 
		2 321 "FKMiddleFinger2_R.rotateY" 2 322 "FKMiddleFinger2_R.rotateX" 
		2 323 "FKExtraMiddleFinger3_R.rotateZ" 2 324 "FKExtraMiddleFinger3_R.rotateY" 
		2 325 "FKExtraMiddleFinger3_R.rotateX" 2 326 "FKMiddleFinger3_R.scaleZ" 
		0 167 "FKMiddleFinger3_R.scaleY" 0 168 "FKMiddleFinger3_R.scaleX" 
		0 169 "FKMiddleFinger3_R.rotateZ" 2 327 "FKMiddleFinger3_R.rotateY" 
		2 328 "FKMiddleFinger3_R.rotateX" 2 329 "FKExtraThumbFinger1_R.rotateZ" 
		2 330 "FKExtraThumbFinger1_R.rotateY" 2 331 "FKExtraThumbFinger1_R.rotateX" 
		2 332 "FKThumbFinger1_R.scaleZ" 0 170 "FKThumbFinger1_R.scaleY" 0 
		171 "FKThumbFinger1_R.scaleX" 0 172 "FKThumbFinger1_R.rotateZ" 2 
		333 "FKThumbFinger1_R.rotateY" 2 334 "FKThumbFinger1_R.rotateX" 2 
		335 "FKExtraThumbFinger2_R.rotateZ" 2 336 "FKExtraThumbFinger2_R.rotateY" 
		2 337 "FKExtraThumbFinger2_R.rotateX" 2 338 "FKThumbFinger2_R.scaleZ" 
		0 173 "FKThumbFinger2_R.scaleY" 0 174 "FKThumbFinger2_R.scaleX" 0 
		175 "FKThumbFinger2_R.rotateZ" 2 339 "FKThumbFinger2_R.rotateY" 2 
		340 "FKThumbFinger2_R.rotateX" 2 341 "FKExtraThumbFinger3_R.rotateZ" 2 
		342 "FKExtraThumbFinger3_R.rotateY" 2 343 "FKExtraThumbFinger3_R.rotateX" 
		2 344 "FKThumbFinger3_R.scaleZ" 0 176 "FKThumbFinger3_R.scaleY" 0 
		177 "FKThumbFinger3_R.scaleX" 0 178 "FKThumbFinger3_R.rotateZ" 2 
		345 "FKThumbFinger3_R.rotateY" 2 346 "FKThumbFinger3_R.rotateX" 2 
		347 "Group.scaleZ" 0 179 "Group.scaleY" 0 180 "Group.scaleX" 0 
		181 "Group.rotateZ" 2 348 "Group.rotateY" 2 349 "Group.rotateX" 
		2 350 "Group.translateZ" 1 115 "Group.translateY" 1 116 "Group.translateX" 
		1 117 "Group.visibility" 0 182  ;
	setAttr ".cd[0].cim" -type "Int32Array" 649 0 1 2 3 4
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
		 497 498 499 500 501 502 503 504 505 506 507 508
		 509 510 511 512 513 514 515 516 517 518 519 520
		 521 522 523 524 525 526 527 528 529 530 531 532
		 533 534 535 536 537 538 539 540 541 542 543 544
		 545 546 547 548 549 550 551 552 553 554 555 556
		 557 558 559 560 561 562 563 564 565 566 567 568
		 569 570 571 572 573 574 575 576 577 578 579 580
		 581 582 583 584 585 586 587 588 589 590 591 592
		 593 594 595 596 597 598 599 600 601 602 603 604
		 605 606 607 608 609 610 611 612 613 614 615 616
		 617 618 619 620 621 622 623 624 625 626 627 628
		 629 630 631 632 633 634 635 636 637 638 639 640
		 641 642 643 644 645 646 647 648 ;
createNode animClip -n "Minigame2_failSource";
	setAttr ".ihi" 0;
	setAttr -s 649 ".ac";
	setAttr ".ac[0:499]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
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
		yes yes yes yes;
	setAttr ".ac[500:648]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		no no no yes yes yes no no no no;
	setAttr ".se" 92;
	setAttr ".ci" no;
createNode animCurveTA -n "girl_back_skirt_b_CTRL_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -35.107866749865821 10 -35.107866749865821 
		26 -35.107866749865821 34 -35.107866749865821 41 -35.107866749865821 55 -35.107866749865821 
		62 -35.107866749865821 78 -35.107866749865821 92 -35.107866749865821;
createNode animCurveTA -n "girl_back_skirt_b_CTRL_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_back_skirt_b_CTRL_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_angularValues_4_";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_angularValues_5_";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_angularValues_6_";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_R_cloak_C_CTRL_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_R_cloak_C_CTRL_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_R_cloak_C_CTRL_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_R_cloak_B_CTRL_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_R_cloak_B_CTRL_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_R_cloak_B_CTRL_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_R_cloak_A_CTRL_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_R_cloak_A_CTRL_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_R_cloak_A_CTRL_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_L_cloak_C_CTRL_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_L_cloak_C_CTRL_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_L_cloak_C_CTRL_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_L_cloak_B_CTRL_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_L_cloak_B_CTRL_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_L_cloak_B_CTRL_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_L_cloak_A_CTRL_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_L_cloak_A_CTRL_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_L_cloak_A_CTRL_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_cloak_D_CTRL_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_cloak_D_CTRL_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_cloak_D_CTRL_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_cloak_C_CTRL_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_cloak_C_CTRL_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_cloak_C_CTRL_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_cloak_B_CTRL_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_cloak_B_CTRL_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_cloak_B_CTRL_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_cloak_A_CTRL_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_cloak_A_CTRL_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_cloak_A_CTRL_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_angularValues_37_";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_angularValues_38_";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_angularValues_39_";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_back_skirt_b_CTRL_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_back_skirt_b_CTRL_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_back_skirt_b_CTRL_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_angularValues_40_";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_angularValues_41_";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_angularValues_42_";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_linearValues_4_";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_linearValues_5_";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_linearValues_6_";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_angularValues_43_";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_angularValues_44_";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_angularValues_45_";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_linearValues_7_";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_linearValues_8_";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_linearValues_9_";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_back_skirt_a_CTRL_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 2.6938795237463498 10 2.6938795237463498 
		26 2.6938795237463498 34 2.6938795237463498 41 2.6938795237463498 55 2.6938795237463498 
		62 2.6938795237463498 78 2.6938795237463498 92 2.6938795237463498;
createNode animCurveTA -n "girl_back_skirt_a_CTRL_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -12.342679124221798 10 -12.342679124221798 
		26 -12.342679124221798 34 -12.342679124221798 41 -12.342679124221798 55 -12.342679124221798 
		62 -12.342679124221798 78 -12.342679124221798 92 -12.342679124221798;
createNode animCurveTA -n "girl_back_skirt_a_CTRL_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 7.3397129639479664 10 7.3397129639479664 
		26 7.3397129639479664 34 7.3397129639479664 41 7.3397129639479664 55 7.3397129639479664 
		62 7.3397129639479664 78 7.3397129639479664 92 7.3397129639479664;
createNode animCurveTL -n "girl_back_skirt_a_CTRL_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.1506711017189028 10 -0.1506711017189028 
		26 -0.1506711017189028 34 -0.1506711017189028 41 -0.1506711017189028 55 -0.1506711017189028 
		62 -0.1506711017189028 78 -0.1506711017189028 92 -0.1506711017189028;
createNode animCurveTL -n "girl_back_skirt_a_CTRL_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.3878246215110126 10 0.3878246215110126 
		26 0.3878246215110126 34 0.3878246215110126 41 0.3878246215110126 55 0.3878246215110126 
		62 0.3878246215110126 78 0.3878246215110126 92 0.3878246215110126;
createNode animCurveTL -n "girl_back_skirt_a_CTRL_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.19170657084941162 10 -0.19170657084941162 
		26 -0.19170657084941162 34 -0.19170657084941162 41 -0.19170657084941162 55 -0.19170657084941162 
		62 -0.19170657084941162 78 -0.19170657084941162 92 -0.19170657084941162;
createNode animCurveTA -n "girl_front_skirt_b_CTRL_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 20.536714960000001 10 20.536714960000001 
		26 20.536714960000001 34 20.536714960000001 41 20.536714960000001 55 20.536714960000001 
		62 20.536714960000001 78 20.536714960000001 92 20.536714960000001;
createNode animCurveTA -n "girl_front_skirt_b_CTRL_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.68059892 10 1.68059892 26 1.68059892 
		34 1.68059892 41 1.68059892 55 1.68059892 62 1.68059892 78 1.68059892 92 1.68059892;
createNode animCurveTA -n "girl_front_skirt_b_CTRL_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 2.246740264 10 2.246740264 26 2.246740264 
		34 2.246740264 41 2.246740264 55 2.246740264 62 2.246740264 78 2.246740264 92 2.246740264;
createNode animCurveTL -n "girl_front_skirt_b_CTRL_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_front_skirt_b_CTRL_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_front_skirt_b_CTRL_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_front_skirt_a_CTRL_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.96208267020000005 10 0.96208267020000005 
		26 0.96208267020000005 34 0.96208267020000005 41 0.96208267020000005 55 0.96208267020000005 
		62 0.96208267020000005 78 0.96208267020000005 92 0.96208267020000005;
createNode animCurveTA -n "girl_front_skirt_a_CTRL_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_front_skirt_a_CTRL_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_front_skirt_a_CTRL_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.089153431075066639 10 0.089153431075066639 
		26 0.089153431075066639 34 0.089153431075066639 41 0.089153431075066639 55 0.089153431075066639 
		62 0.089153431075066639 78 0.089153431075066639 92 0.089153431075066639;
createNode animCurveTL -n "girl_front_skirt_a_CTRL_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.20970195830660243 10 -0.20970195830660243 
		26 -0.20970195830660243 34 -0.20970195830660243 41 -0.20970195830660243 55 -0.20970195830660243 
		62 -0.20970195830660243 78 -0.20970195830660243 92 -0.20970195830660243;
createNode animCurveTL -n "girl_front_skirt_a_CTRL_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.0068805126335673514 10 -0.0068805126335673514 
		26 -0.0068805126335673514 34 -0.0068805126335673514 41 -0.0068805126335673514 55 
		-0.0068805126335673514 62 -0.0068805126335673514 78 -0.0068805126335673514 92 -0.0068805126335673514;
createNode animCurveTA -n "girl_skirt_HipA_L_CTRL_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_skirt_HipA_L_CTRL_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_skirt_HipA_L_CTRL_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_skirt_HipA_L_CTRL_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_skirt_HipA_L_CTRL_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_skirt_HipA_L_CTRL_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_skirt_Hip_L_CTRL_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_skirt_Hip_L_CTRL_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_skirt_Hip_L_CTRL_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_skirt_Hip_L_CTRL_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.01408065876666875 10 0.01408065876666875 
		26 0.01408065876666875 34 0.01408065876666875 41 0.01408065876666875 55 0.01408065876666875 
		62 0.01408065876666875 78 0.01408065876666875 92 0.01408065876666875;
createNode animCurveTL -n "girl_skirt_Hip_L_CTRL_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.0059453893140569321 10 -0.0059453893140569321 
		26 -0.0059453893140569321 34 -0.0059453893140569321 41 -0.0059453893140569321 55 
		-0.0059453893140569321 62 -0.0059453893140569321 78 -0.0059453893140569321 92 -0.0059453893140569321;
createNode animCurveTL -n "girl_skirt_Hip_L_CTRL_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.0013409990355031896 10 0.0013409990355031896 
		26 0.0013409990355031896 34 0.0013409990355031896 41 0.0013409990355031896 55 0.0013409990355031896 
		62 0.0013409990355031896 78 0.0013409990355031896 92 0.0013409990355031896;
createNode animCurveTA -n "girl_skirt_HipA_R_CTRL_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 6.6401439609999997 10 6.6401439609999997 
		26 6.6401439609999997 34 6.6401439609999997 41 6.6401439609999997 55 6.6401439609999997 
		62 6.6401439609999997 78 6.6401439609999997 92 6.6401439609999997;
createNode animCurveTA -n "girl_skirt_HipA_R_CTRL_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -10.419421379999999 10 -10.419421379999999 
		26 -10.419421379999999 34 -10.419421379999999 41 -10.419421379999999 55 -10.419421379999999 
		62 -10.419421379999999 78 -10.419421379999999 92 -10.419421379999999;
createNode animCurveTA -n "girl_skirt_HipA_R_CTRL_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -3.6296225309999994 10 -3.6296225309999994 
		26 -3.6296225309999994 34 -3.6296225309999994 41 -3.6296225309999994 55 -3.6296225309999994 
		62 -3.6296225309999994 78 -3.6296225309999994 92 -3.6296225309999994;
createNode animCurveTL -n "girl_skirt_HipA_R_CTRL_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_skirt_HipA_R_CTRL_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_skirt_HipA_R_CTRL_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_skirt_Hip_R_CTRL_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.059443428020000008 10 -0.059443428020000008 
		26 -0.059443428020000008 34 -0.059443428020000008 41 -0.059443428020000008 55 -0.059443428020000008 
		62 -0.059443428020000008 78 -0.059443428020000008 92 -0.059443428020000008;
createNode animCurveTA -n "girl_skirt_Hip_R_CTRL_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.12010888460000001 10 -0.12010888460000001 
		26 -0.12010888460000001 34 -0.12010888460000001 41 -0.12010888460000001 55 -0.12010888460000001 
		62 -0.12010888460000001 78 -0.12010888460000001 92 -0.12010888460000001;
createNode animCurveTA -n "girl_skirt_Hip_R_CTRL_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.58331804030000001 10 0.58331804030000001 
		26 0.58331804030000001 34 0.58331804030000001 41 0.58331804030000001 55 0.58331804030000001 
		62 0.58331804030000001 78 0.58331804030000001 92 0.58331804030000001;
createNode animCurveTL -n "girl_skirt_Hip_R_CTRL_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.028480309728328882 10 -0.028480309728328882 
		26 -0.028480309728328882 34 -0.028480309728328882 41 -0.028480309728328882 55 -0.028480309728328882 
		62 -0.028480309728328882 78 -0.028480309728328882 92 -0.028480309728328882;
createNode animCurveTL -n "girl_skirt_Hip_R_CTRL_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.0036166365236135014 10 0.0036166365236135014 
		26 0.0036166365236135014 34 0.0036166365236135014 41 0.0036166365236135014 55 0.0036166365236135014 
		62 0.0036166365236135014 78 0.0036166365236135014 92 0.0036166365236135014;
createNode animCurveTL -n "girl_skirt_Hip_R_CTRL_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.0362163539759899 10 -0.0362163539759899 
		26 -0.0362163539759899 34 -0.0362163539759899 41 -0.0362163539759899 55 -0.0362163539759899 
		62 -0.0362163539759899 78 -0.0362163539759899 92 -0.0362163539759899;
createNode animCurveTU -n "girl_Center_M_CenterBtwFeet";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_Center_M_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -38.239471219814469 10 -38.239471219814469 
		26 -38.239471219814469 34 -38.239471219814469 41 -38.239471219814469 55 -38.239471219814469 
		62 -38.239471219814469 78 -38.239471219814469 92 -38.239471219814469;
createNode animCurveTA -n "girl_Center_M_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_Center_M_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 7.8960619584932568 10 -1.6450068554051891 
		26 20.136061821941116 34 20.136061821941116 41 20.136061821941116 55 20.989053850567892 
		62 20.136061821941116 78 7.8960619584932568 92 7.8960619584932568;
createNode animCurveTL -n "girl_Center_M_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.68530052330451496 10 -0.68530052330451496 
		26 -0.68530052330451496 34 -0.68530052330451496 41 -0.68530052330451496 55 -0.68530052330451496 
		62 -0.68530052330451496 78 -0.68530052330451496 92 -0.68530052330451496;
createNode animCurveTL -n "girl_Center_M_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.65142083148962104 10 -0.65142083148962104 
		26 -0.65142083148962104 34 -0.65142083148962104 41 -0.65142083148962104 55 -0.65142083148962104 
		62 -0.65142083148962104 78 -0.65142083148962104 92 -0.65142083148962104;
createNode animCurveTL -n "girl_Center_M_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.52813520669109548 10 0.52813520669109548 
		26 0.52813520669109548 34 0.52813520669109548 41 0.52813520669109548 55 0.52813520669109548 
		62 0.52813520669109548 78 0.52813520669109548 92 0.52813520669109548;
createNode animCurveTA -n "girl_CenterExtra_M_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_CenterExtra_M_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_CenterExtra_M_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_CenterExtra_M_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_CenterExtra_M_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_CenterExtra_M_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_Fingers_L_Cup";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_Fingers_L_Spread";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_Fingers_L_ThumbFingerCurl";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_Fingers_L_PinkyFingerCurl";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_Fingers_L_RingFingerCurl";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_Fingers_L_MiddleFingerCurl";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_Fingers_L_IndexFingerCurl";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraLegBall_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraLegBall_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraLegBall_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKLegBall_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraLegToe_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraLegToe_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraLegToe_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKLegToe_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKLegToe_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKLegToe_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraLegHeel_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraLegHeel_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraLegHeel_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKLegHeel_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKLegHeel_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKLegHeel_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKIKLeg_L_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
	setAttr -s 9 ".kot[0:8]"  5 5 5 5 5 5 5 5 
		5;
createNode animCurveTU -n "girl_FKIKLeg_L_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
	setAttr -s 9 ".kot[0:8]"  5 5 5 5 5 5 5 5 
		5;
createNode animCurveTU -n "girl_FKIKLeg_L_FKIKBlend";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_PoleExtraLeg_L_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_PoleExtraLeg_L_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_PoleExtraLeg_L_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_PoleLeg_L_follow";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 10 10 10 26 10 34 10 41 10 55 10 62 10 
		78 10 92 10;
createNode animCurveTL -n "girl_PoleLeg_L_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_PoleLeg_L_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_PoleLeg_L_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraLeg_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraLeg_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraLeg_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKExtraLeg_L_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKExtraLeg_L_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKExtraLeg_L_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_IKLeg_L_Lenght2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_IKLeg_L_Lenght1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_IKLeg_L_antiPop";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_IKLeg_L_stretchy";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_IKLeg_L_rollAngle";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 25 10 25 26 25 34 25 41 25 55 25 62 25 
		78 25 92 25;
createNode animCurveTU -n "girl_IKLeg_L_roll";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_IKLeg_L_toe";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_IKLeg_L_swivel";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKLeg_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKLeg_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKLeg_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKLeg_L_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKLeg_L_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKLeg_L_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKIKArm_L_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
	setAttr -s 9 ".kot[0:8]"  5 5 5 5 5 5 5 5 
		5;
createNode animCurveTU -n "girl_FKIKArm_L_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
	setAttr -s 9 ".kot[0:8]"  5 5 5 5 5 5 5 5 
		5;
createNode animCurveTU -n "girl_FKIKArm_L_FKIKBlend";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 10 10 10 26 10 34 10 41 10 55 10 62 10 
		78 10 92 10;
createNode animCurveTL -n "girl_PoleExtraArm_L_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_PoleExtraArm_L_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_PoleExtraArm_L_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_PoleArm_L_follow";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_PoleArm_L_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 -1.6085487233320845 26 -1.6085487233320845 
		34 -1.6085487233320845 41 -1.6085487233320845 55 -1.6300228064733981 62 -1.6085487233320845 
		78 -1.3004066095684041 92 0;
createNode animCurveTL -n "girl_PoleArm_L_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 -1.917664570908205 26 -1.917664570908205 
		34 -1.917664570908205 41 -1.917664570908205 55 -1.9212945931607004 62 -1.917664570908205 
		78 -1.8655756043638605 92 0;
createNode animCurveTL -n "girl_PoleArm_L_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0.43461894730026895 26 0.43461894730026895 
		34 0.43461894730026895 41 0.43461894730026895 55 0.43203605547383189 62 0.43461894730026895 
		78 0.47168212740990267 92 0;
createNode animCurveTA -n "girl_IKExtraArm_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraArm_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraArm_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKExtraArm_L_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKExtraArm_L_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKExtraArm_L_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_IKArm_L_Lenght2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_IKArm_L_Lenght1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_IKArm_L_antiPop";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_IKArm_L_stretchy";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_IKArm_L_follow";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKArm_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -64.016327 10 -59.976169945768419 26 
		-121.26685298943814 34 -121.26685298943814 41 -121.26685298943814 48 -134.39376872599553 
		55 -134.39376872599553 62 -134.39376872599553 78 -225.63279257244838 85 -115.02810660226579 
		92 -64.016327;
createNode animCurveTA -n "girl_IKArm_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -21.201885600000001 10 1.36538396768987 
		26 75.099175235430252 34 75.099175235430252 41 75.099175235430252 48 58.480992201803822 
		55 58.480992201803822 62 58.480992201803822 78 62.188167569975413 85 52.687852596468488 
		92 -21.201885600000001;
createNode animCurveTA -n "girl_IKArm_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 23.577065820000001 10 -81.070129798997883 
		26 11.409285742920755 34 11.409285742920755 41 11.409285742920755 48 14.204284465640523 
		55 14.204284465640523 62 14.204284465640523 78 79.078012813090041 85 27.400632796528807 
		92 23.577065820000001;
createNode animCurveTL -n "girl_IKArm_L_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -1.114764949 10 0.15770649872467724 26 
		-0.75036146755955779 34 -0.75036146755955779 41 -0.75036146755955779 48 -0.50985462704450901 
		55 -0.50985462704450901 62 -0.50985462704450901 78 0.11719943611893457 85 -0.4940972677383777 
		92 -1.114764949;
createNode animCurveTL -n "girl_IKArm_L_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -0.78014303230000004 10 -1.2311408941885502 
		26 -1.9689039375193462 34 -1.9689039375193462 41 -1.9689039375193462 48 -1.7223601787516258 
		55 -1.7223601787516258 62 -1.7223601787516258 78 -0.98095142693108728 85 -1.2780237178582545 
		92 -0.78014303230000004;
createNode animCurveTL -n "girl_IKArm_L_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -0.21085409329999999 10 0.20346178254686326 
		26 -0.67698934948995571 34 -0.67698934948995571 41 -0.67698934948995571 48 -0.65858072108647325 
		55 -0.65858072108647325 62 -0.65858072108647325 78 -0.43888924887895064 85 -0.21334616729871192 
		92 -0.21085409329999999;
createNode animCurveTU -n "girl_Fingers_R_Cup";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_Fingers_R_Spread";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_Fingers_R_ThumbFingerCurl";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_Fingers_R_PinkyFingerCurl";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_Fingers_R_RingFingerCurl";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_Fingers_R_MiddleFingerCurl";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_Fingers_R_IndexFingerCurl";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_IKExtraSpine4_M_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_IKExtraSpine4_M_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_IKExtraSpine4_M_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTA -n "girl_IKExtraSpine4_M_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraSpine4_M_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraSpine4_M_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKExtraSpine4_M_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKExtraSpine4_M_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKExtraSpine4_M_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_IKExtraSpine4_M_visibility";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
	setAttr -s 9 ".kot[0:8]"  5 5 5 5 5 5 5 5 
		5;
createNode animCurveTU -n "girl_IKSpine4_M_stretchy";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 10 10 10 26 10 34 10 41 10 55 10 62 10 
		78 10 92 10;
createNode animCurveTU -n "girl_IKSpine4_M_stiff";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKSpine4_M_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKSpine4_M_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKSpine4_M_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKSpine4_M_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKSpine4_M_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKSpine4_M_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_IKExtraSpine2_M_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_IKExtraSpine2_M_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_IKExtraSpine2_M_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTA -n "girl_IKExtraSpine2_M_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraSpine2_M_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraSpine2_M_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKExtraSpine2_M_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKExtraSpine2_M_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKExtraSpine2_M_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_IKExtraSpine2_M_visibility";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
	setAttr -s 9 ".kot[0:8]"  5 5 5 5 5 5 5 5 
		5;
createNode animCurveTU -n "girl_IKSpine2_M_stiff";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKSpine2_M_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKSpine2_M_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKSpine2_M_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKSpine2_M_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKSpine2_M_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKSpine2_M_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_IKExtraSpine0_M_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_IKExtraSpine0_M_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_IKExtraSpine0_M_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTA -n "girl_IKExtraSpine0_M_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraSpine0_M_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraSpine0_M_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKExtraSpine0_M_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKExtraSpine0_M_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKExtraSpine0_M_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_IKExtraSpine0_M_visibility";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
	setAttr -s 9 ".kot[0:8]"  5 5 5 5 5 5 5 5 
		5;
createNode animCurveTU -n "girl_IKSpine0_M_stiff";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKSpine0_M_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKSpine0_M_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKSpine0_M_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKSpine0_M_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKSpine0_M_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKSpine0_M_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraLegBall_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraLegBall_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraLegBall_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKLegBall_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraLegToe_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraLegToe_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraLegToe_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKLegToe_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKLegToe_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKLegToe_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraLegHeel_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraLegHeel_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraLegHeel_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKLegHeel_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKLegHeel_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKLegHeel_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKIKLeg_R_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
	setAttr -s 9 ".kot[0:8]"  5 5 5 5 5 5 5 5 
		5;
createNode animCurveTU -n "girl_FKIKLeg_R_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
	setAttr -s 9 ".kot[0:8]"  5 5 5 5 5 5 5 5 
		5;
createNode animCurveTU -n "girl_FKIKLeg_R_FKIKBlend";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_PoleExtraLeg_R_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_PoleExtraLeg_R_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_PoleExtraLeg_R_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_PoleLeg_R_follow";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 10 10 10 26 10 34 10 41 10 55 10 62 10 
		78 10 92 10;
createNode animCurveTL -n "girl_PoleLeg_R_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_PoleLeg_R_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_PoleLeg_R_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraLeg_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraLeg_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraLeg_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKExtraLeg_R_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKExtraLeg_R_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKExtraLeg_R_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_IKLeg_R_Lenght2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_IKLeg_R_Lenght1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_IKLeg_R_antiPop";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_IKLeg_R_stretchy";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_IKLeg_R_rollAngle";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 25 10 25 26 25 34 25 41 25 55 25 62 25 
		78 25 92 25;
createNode animCurveTU -n "girl_IKLeg_R_roll";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_IKLeg_R_toe";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_IKLeg_R_swivel";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKLeg_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKLeg_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKLeg_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKLeg_R_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKLeg_R_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKLeg_R_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKIKArm_R_IKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
	setAttr -s 9 ".kot[0:8]"  5 5 5 5 5 5 5 5 
		5;
createNode animCurveTU -n "girl_FKIKArm_R_FKVis";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
	setAttr -s 9 ".kot[0:8]"  5 5 5 5 5 5 5 5 
		5;
createNode animCurveTU -n "girl_FKIKArm_R_FKIKBlend";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 10 10 10 26 10 34 10 41 10 55 10 62 10 
		78 10 92 10;
createNode animCurveTL -n "girl_PoleExtraArm_R_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_PoleExtraArm_R_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_PoleExtraArm_R_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_PoleArm_R_follow";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_PoleArm_R_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -1.8324655288625988 10 -1.5642660540162647 
		26 -1.5642660540162647 34 -1.5642660540162647 41 -1.5642660540162647 55 -1.5845330770886694 
		62 -1.5642660540162647 78 -1.2734446275990345 85 -1.4906973536017698 92 -1.8324655288625988;
createNode animCurveTL -n "girl_PoleArm_R_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -1.5248853769364021 10 -1.7027839295174565 
		26 -1.7027839295174565 34 -1.7027839295174565 41 -1.7027839295174565 55 -1.7127161554854993 
		62 -1.7027839295174565 78 -1.5602615629485528 85 -1.5432880186087254 92 -1.5248853769364021;
createNode animCurveTL -n "girl_PoleArm_R_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.72634564248961153 10 0.35773011875486005 
		26 0.35773011875486005 34 0.35773011875486005 41 0.35773011875486005 55 0.3710354436240571 
		62 0.35773011875486005 78 0.16680550687583828 85 0.57993153549544263 92 0.72634564248961153;
createNode animCurveTA -n "girl_IKExtraArm_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraArm_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKExtraArm_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKExtraArm_R_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKExtraArm_R_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_IKExtraArm_R_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_IKArm_R_Lenght2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_IKArm_R_Lenght1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_IKArm_R_antiPop";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_IKArm_R_stretchy";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_IKArm_R_follow";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_IKArm_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 74.385551550000002 10 41.991064310880908 
		26 64.098405830812254 34 64.098405830812254 41 64.098405830812254 55 75.017205176051462 
		62 64.098405830812254 78 -90.396710936738856 85 -28.963525097656341 92 74.385551550000002;
createNode animCurveTA -n "girl_IKArm_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 18.642817839999999 10 5.7893938731641077 
		26 -64.504273836183415 34 -64.504273836183415 41 -64.504273836183415 55 -63.698756004263956 
		62 -64.504273836183415 78 -71.116275269546236 85 -64.736985078016772 92 18.642817839999999;
createNode animCurveTA -n "girl_IKArm_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 2.8749941739999998 10 -113.29768634459371 
		26 -55.993947265967812 34 -55.993947265967812 41 -55.993947265967812 55 -41.495504599781604 
		62 -55.993947265967812 78 -241.83708549805192 85 -98.580888450890342 92 2.8749941739999998;
createNode animCurveTL -n "girl_IKArm_R_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -0.79868788219999998 10 0.27690275987924695 
		26 -0.75038198641482634 34 -0.75038198641482634 41 -0.75038198641482634 48 -0.53434324466551797 
		55 -0.53434324466551797 62 -0.53434324466551797 78 0.10381771860131661 85 -0.57334405319454396 
		92 -0.79868788219999998;
createNode animCurveTL -n "girl_IKArm_R_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -1.146782255 10 -0.73504080834388064 
		26 -1.8870159039195913 34 -1.8870159039195913 41 -1.8870159039195913 48 -1.5679684318236125 
		55 -1.5679684318236125 62 -1.5679684318236125 78 -0.93344220570384706 85 -0.97663489365467071 
		92 -1.146782255;
createNode animCurveTL -n "girl_IKArm_R_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1.1096578500000001 10 0.71982155591089003 
		26 0.94309648452097561 34 0.94309648452097561 41 0.94309648452097561 48 1.0710417630997526 
		55 1.0710417630997526 62 1.0710417630997526 78 1.3762010354529601 85 1.094256221907163 
		92 1.1096578500000001;
createNode animCurveTA -n "girl_HipSwingerRoot_M_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_HipSwingerRoot_M_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_HipSwingerRoot_M_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraHip_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraHip_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraHip_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKHip_L_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999989 10 0.99999999999999989 
		26 0.99999999999999989 34 0.99999999999999989 41 0.99999999999999989 55 0.99999999999999989 
		62 0.99999999999999989 78 0.99999999999999989 92 0.99999999999999989;
createNode animCurveTU -n "girl_FKHip_L_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_FKHip_L_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.0000000000000004 10 1.0000000000000004 
		26 1.0000000000000004 34 1.0000000000000004 41 1.0000000000000004 55 1.0000000000000004 
		62 1.0000000000000004 78 1.0000000000000004 92 1.0000000000000004;
createNode animCurveTA -n "girl_FKHip_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -93.148410662823451 10 -83.6654221918117 
		26 -106.15802135143267 34 -106.15802135143267 41 -106.15802135143267 55 -107.06464674939589 
		62 -106.15802135143267 78 -93.148410662823451 92 -93.148410662823451;
createNode animCurveTA -n "girl_FKHip_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.087147345469543197 10 -0.087147345469543197 
		26 -0.087147345469543197 34 -0.087147345469543197 41 -0.087147345469543197 55 -0.087147345469543197 
		62 -0.087147345469543197 78 -0.087147345469543197 92 -0.087147345469543197;
createNode animCurveTA -n "girl_FKHip_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -15.275860387989701 10 -15.275860387989701 
		26 -15.275860387989701 34 -15.275860387989701 41 -15.275860387989701 55 -15.275860387989701 
		62 -15.275860387989701 78 -15.275860387989701 92 -15.275860387989701;
createNode animCurveTA -n "girl_FKExtraKnee_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraKnee_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraKnee_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKKnee_L_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999989 10 0.99999999999999989 
		26 0.99999999999999989 34 0.99999999999999989 41 0.99999999999999989 55 0.99999999999999989 
		62 0.99999999999999989 78 0.99999999999999989 92 0.99999999999999989;
createNode animCurveTU -n "girl_FKKnee_L_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999967 10 0.99999999999999967 
		26 0.99999999999999967 34 0.99999999999999967 41 0.99999999999999967 55 0.99999999999999967 
		62 0.99999999999999967 78 0.99999999999999967 92 0.99999999999999967;
createNode animCurveTU -n "girl_FKKnee_L_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTA -n "girl_FKKnee_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 83.913182451591126 10 83.913182451591126 
		26 83.913182451591126 34 83.913182451591126 41 83.913182451591126 55 83.913182451591126 
		62 83.913182451591126 78 83.913182451591126 92 83.913182451591126;
createNode animCurveTA -n "girl_FKKnee_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -1.6823378597082943 10 -1.6823378597082943 
		26 -1.6823378597082943 34 -1.6823378597082943 41 -1.6823378597082943 55 -1.6823378597082943 
		62 -1.6823378597082943 78 -1.6823378597082943 92 -1.6823378597082943;
createNode animCurveTA -n "girl_FKKnee_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 5.0280589807764775 10 5.0280589807764775 
		26 5.0280589807764775 34 5.0280589807764775 41 5.0280589807764775 55 5.0280589807764775 
		62 5.0280589807764775 78 5.0280589807764775 92 5.0280589807764775;
createNode animCurveTA -n "girl_FKExtraAnkle_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraAnkle_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraAnkle_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKAnkle_L_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.0000000000000004 10 1.0000000000000004 
		26 1.0000000000000004 34 1.0000000000000004 41 1.0000000000000004 55 1.0000000000000004 
		62 1.0000000000000004 78 1.0000000000000004 92 1.0000000000000004;
createNode animCurveTU -n "girl_FKAnkle_L_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.0000000000000002 10 1.0000000000000002 
		26 1.0000000000000002 34 1.0000000000000002 41 1.0000000000000002 55 1.0000000000000002 
		62 1.0000000000000002 78 1.0000000000000002 92 1.0000000000000002;
createNode animCurveTU -n "girl_FKAnkle_L_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.0000000000000002 10 1.0000000000000002 
		26 1.0000000000000002 34 1.0000000000000002 41 1.0000000000000002 55 1.0000000000000002 
		62 1.0000000000000002 78 1.0000000000000002 92 1.0000000000000002;
createNode animCurveTA -n "girl_FKAnkle_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKAnkle_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 26.093661828935559 10 26.093661828935559 
		26 26.093661828935559 34 26.093661828935559 41 26.093661828935559 55 26.093661828935559 
		62 26.093661828935559 78 26.093661828935559 92 26.093661828935559;
createNode animCurveTA -n "girl_FKAnkle_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraMiddleToe1_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraMiddleToe1_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraMiddleToe1_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKMiddleToe1_L_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.0000000000000004 10 1.0000000000000004 
		26 1.0000000000000004 34 1.0000000000000004 41 1.0000000000000004 55 1.0000000000000004 
		62 1.0000000000000004 78 1.0000000000000004 92 1.0000000000000004;
createNode animCurveTU -n "girl_FKMiddleToe1_L_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_FKMiddleToe1_L_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.0000000000000004 10 1.0000000000000004 
		26 1.0000000000000004 34 1.0000000000000004 41 1.0000000000000004 55 1.0000000000000004 
		62 1.0000000000000004 78 1.0000000000000004 92 1.0000000000000004;
createNode animCurveTA -n "girl_FKMiddleToe1_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 4.1383308710323172 10 4.1383308710323172 
		26 4.1383308710323172 34 4.1383308710323172 41 4.1383308710323172 55 4.1383308710323172 
		62 4.1383308710323172 78 4.1383308710323172 92 4.1383308710323172;
createNode animCurveTA -n "girl_FKMiddleToe1_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKMiddleToe1_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKExtraScapula_L_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.0000000000000004 10 1.0000000000000004 
		26 1.0000000000000004 34 1.0000000000000004 41 1.0000000000000004 55 1.0000000000000004 
		62 1.0000000000000004 78 1.0000000000000004 92 1.0000000000000004;
createNode animCurveTU -n "girl_FKExtraScapula_L_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.0000000000000002 10 1.0000000000000002 
		26 1.0000000000000002 34 1.0000000000000002 41 1.0000000000000002 55 1.0000000000000002 
		62 1.0000000000000002 78 1.0000000000000002 92 1.0000000000000002;
createNode animCurveTU -n "girl_FKExtraScapula_L_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTA -n "girl_FKExtraScapula_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraScapula_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraScapula_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_FKExtraScapula_L_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_FKExtraScapula_L_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_FKExtraScapula_L_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKScapula_L_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999989 10 0.99999999999999989 
		26 0.99999999999999989 34 0.99999999999999989 41 0.99999999999999989 55 0.99999999999999989 
		62 0.99999999999999989 78 0.99999999999999989 92 0.99999999999999989;
createNode animCurveTU -n "girl_FKScapula_L_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999989 10 0.99999999999999989 
		26 0.99999999999999989 34 0.99999999999999989 41 0.99999999999999989 55 0.99999999999999989 
		62 0.99999999999999989 78 0.99999999999999989 92 0.99999999999999989;
createNode animCurveTU -n "girl_FKScapula_L_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999989 10 0.99999999999999989 
		26 0.99999999999999989 34 0.99999999999999989 41 0.99999999999999989 55 0.99999999999999989 
		62 0.99999999999999989 78 0.99999999999999989 92 0.99999999999999989;
createNode animCurveTA -n "girl_FKScapula_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -5.7485006011304165 10 2.5051297785372451 
		26 2.5051297785372451 34 2.5051297785372451 41 2.5051297785372451 55 1.811256494354353 
		62 2.5051297785372451 78 12.461856675320197 92 -5.7485006011304165;
createNode animCurveTA -n "girl_FKScapula_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKScapula_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_FKScapula_L_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_FKScapula_L_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_FKScapula_L_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraShoulder_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraShoulder_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraShoulder_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKShoulder_L_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_FKShoulder_L_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_FKShoulder_L_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999978 10 0.99999999999999978 
		26 0.99999999999999978 34 0.99999999999999978 41 0.99999999999999978 55 0.99999999999999978 
		62 0.99999999999999978 78 0.99999999999999978 92 0.99999999999999978;
createNode animCurveTA -n "girl_FKShoulder_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKShoulder_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKShoulder_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraElbow_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraElbow_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraElbow_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKElbow_L_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_FKElbow_L_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_FKElbow_L_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTA -n "girl_FKElbow_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKElbow_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKElbow_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraWrist_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraWrist_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraWrist_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKWrist_L_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_FKWrist_L_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_FKWrist_L_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.0000000000000002 10 1.0000000000000002 
		26 1.0000000000000002 34 1.0000000000000002 41 1.0000000000000002 55 1.0000000000000002 
		62 1.0000000000000002 78 1.0000000000000002 92 1.0000000000000002;
createNode animCurveTA -n "girl_FKWrist_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKWrist_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKWrist_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger1_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger1_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger1_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKMiddleFinger1_L_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999989 10 0.99999999999999989 
		26 0.99999999999999989 34 0.99999999999999989 41 0.99999999999999989 55 0.99999999999999989 
		62 0.99999999999999989 78 0.99999999999999989 92 0.99999999999999989;
createNode animCurveTU -n "girl_FKMiddleFinger1_L_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999989 10 0.99999999999999989 
		26 0.99999999999999989 34 0.99999999999999989 41 0.99999999999999989 55 0.99999999999999989 
		62 0.99999999999999989 78 0.99999999999999989 92 0.99999999999999989;
createNode animCurveTU -n "girl_FKMiddleFinger1_L_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999989 10 0.99999999999999989 
		26 0.99999999999999989 34 0.99999999999999989 41 0.99999999999999989 55 0.99999999999999989 
		62 0.99999999999999989 78 0.99999999999999989 92 0.99999999999999989;
createNode animCurveTA -n "girl_FKMiddleFinger1_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 21.441017057914681 10 21.441017057914681 
		26 21.441017057914681 34 21.441017057914681 41 21.441017057914681 55 21.441017057914681 
		62 21.441017057914681 78 21.441017057914681 92 21.441017057914681;
createNode animCurveTA -n "girl_FKMiddleFinger1_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKMiddleFinger1_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger2_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger2_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger2_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKMiddleFinger2_L_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999944 10 0.99999999999999944 
		26 0.99999999999999944 34 0.99999999999999944 41 0.99999999999999944 55 0.99999999999999944 
		62 0.99999999999999944 78 0.99999999999999944 92 0.99999999999999944;
createNode animCurveTU -n "girl_FKMiddleFinger2_L_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999956 10 0.99999999999999956 
		26 0.99999999999999956 34 0.99999999999999956 41 0.99999999999999956 55 0.99999999999999956 
		62 0.99999999999999956 78 0.99999999999999956 92 0.99999999999999956;
createNode animCurveTU -n "girl_FKMiddleFinger2_L_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999967 10 0.99999999999999967 
		26 0.99999999999999967 34 0.99999999999999967 41 0.99999999999999967 55 0.99999999999999967 
		62 0.99999999999999967 78 0.99999999999999967 92 0.99999999999999967;
createNode animCurveTA -n "girl_FKMiddleFinger2_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKMiddleFinger2_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKMiddleFinger2_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger3_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger3_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger3_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKMiddleFinger3_L_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999989 10 0.99999999999999989 
		26 0.99999999999999989 34 0.99999999999999989 41 0.99999999999999989 55 0.99999999999999989 
		62 0.99999999999999989 78 0.99999999999999989 92 0.99999999999999989;
createNode animCurveTU -n "girl_FKMiddleFinger3_L_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_FKMiddleFinger3_L_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTA -n "girl_FKMiddleFinger3_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKMiddleFinger3_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKMiddleFinger3_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger1_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger1_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger1_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKThumbFinger1_L_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999989 10 0.99999999999999989 
		26 0.99999999999999989 34 0.99999999999999989 41 0.99999999999999989 55 0.99999999999999989 
		62 0.99999999999999989 78 0.99999999999999989 92 0.99999999999999989;
createNode animCurveTU -n "girl_FKThumbFinger1_L_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999978 10 0.99999999999999978 
		26 0.99999999999999978 34 0.99999999999999978 41 0.99999999999999978 55 0.99999999999999978 
		62 0.99999999999999978 78 0.99999999999999978 92 0.99999999999999978;
createNode animCurveTU -n "girl_FKThumbFinger1_L_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTA -n "girl_FKThumbFinger1_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -4.6159099819999998 10 -4.6159099819999998 
		26 -4.6159099819999998 34 -4.6159099819999998 41 -4.6159099819999998 55 -4.6159099819999998 
		62 -4.6159099819999998 78 -4.6159099819999998 92 -4.6159099819999998;
createNode animCurveTA -n "girl_FKThumbFinger1_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -20.29236869 10 -20.29236869 26 -20.29236869 
		34 -20.29236869 41 -20.29236869 55 -20.29236869 62 -20.29236869 78 -20.29236869 92 
		-20.29236869;
createNode animCurveTA -n "girl_FKThumbFinger1_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -6.2745051959999998 10 -6.2745051959999998 
		26 -6.2745051959999998 34 -6.2745051959999998 41 -6.2745051959999998 55 -6.2745051959999998 
		62 -6.2745051959999998 78 -6.2745051959999998 92 -6.2745051959999998;
createNode animCurveTA -n "girl_FKExtraThumbFinger2_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger2_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger2_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKThumbFinger2_L_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999978 10 0.99999999999999978 
		26 0.99999999999999978 34 0.99999999999999978 41 0.99999999999999978 55 0.99999999999999978 
		62 0.99999999999999978 78 0.99999999999999978 92 0.99999999999999978;
createNode animCurveTU -n "girl_FKThumbFinger2_L_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999978 10 0.99999999999999978 
		26 0.99999999999999978 34 0.99999999999999978 41 0.99999999999999978 55 0.99999999999999978 
		62 0.99999999999999978 78 0.99999999999999978 92 0.99999999999999978;
createNode animCurveTU -n "girl_FKThumbFinger2_L_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999978 10 0.99999999999999978 
		26 0.99999999999999978 34 0.99999999999999978 41 0.99999999999999978 55 0.99999999999999978 
		62 0.99999999999999978 78 0.99999999999999978 92 0.99999999999999978;
createNode animCurveTA -n "girl_FKThumbFinger2_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKThumbFinger2_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKThumbFinger2_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger3_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger3_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger3_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKThumbFinger3_L_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.0000000000000007 10 1.0000000000000007 
		26 1.0000000000000007 34 1.0000000000000007 41 1.0000000000000007 55 1.0000000000000007 
		62 1.0000000000000007 78 1.0000000000000007 92 1.0000000000000007;
createNode animCurveTU -n "girl_FKThumbFinger3_L_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.0000000000000004 10 1.0000000000000004 
		26 1.0000000000000004 34 1.0000000000000004 41 1.0000000000000004 55 1.0000000000000004 
		62 1.0000000000000004 78 1.0000000000000004 92 1.0000000000000004;
createNode animCurveTU -n "girl_FKThumbFinger3_L_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.0000000000000002 10 1.0000000000000002 
		26 1.0000000000000002 34 1.0000000000000002 41 1.0000000000000002 55 1.0000000000000002 
		62 1.0000000000000002 78 1.0000000000000002 92 1.0000000000000002;
createNode animCurveTA -n "girl_FKThumbFinger3_L_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKThumbFinger3_L_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKThumbFinger3_L_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraHip_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraHip_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraHip_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKHip_R_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.0000000000000002 10 1.0000000000000002 
		26 1.0000000000000002 34 1.0000000000000002 41 1.0000000000000002 55 1.0000000000000002 
		62 1.0000000000000002 78 1.0000000000000002 92 1.0000000000000002;
createNode animCurveTU -n "girl_FKHip_R_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999989 10 0.99999999999999989 
		26 0.99999999999999989 34 0.99999999999999989 41 0.99999999999999989 55 0.99999999999999989 
		62 0.99999999999999989 78 0.99999999999999989 92 0.99999999999999989;
createNode animCurveTU -n "girl_FKHip_R_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.0000000000000002 10 1.0000000000000002 
		26 1.0000000000000002 34 1.0000000000000002 41 1.0000000000000002 55 1.0000000000000002 
		62 1.0000000000000002 78 1.0000000000000002 92 1.0000000000000002;
createNode animCurveTA -n "girl_FKHip_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -105.77848472630944 10 -96.295496255297621 
		26 -118.78809541491874 34 -118.78809541491874 41 -118.78809541491874 55 -119.69472081288197 
		62 -118.78809541491874 78 -105.77848472630944 92 -105.77848472630944;
createNode animCurveTA -n "girl_FKHip_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -8.2096526943984909 10 -8.2096526943984909 
		26 -8.2096526943984909 34 -8.2096526943984909 41 -8.2096526943984909 55 -8.2096526943984909 
		62 -8.2096526943984909 78 -8.2096526943984909 92 -8.2096526943984909;
createNode animCurveTA -n "girl_FKHip_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -8.1666847929670165 10 -8.1666847929670165 
		26 -8.1666847929670165 34 -8.1666847929670165 41 -8.1666847929670165 55 -8.1666847929670165 
		62 -8.1666847929670165 78 -8.1666847929670165 92 -8.1666847929670165;
createNode animCurveTA -n "girl_FKExtraKnee_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraKnee_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraKnee_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKKnee_R_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999989 10 0.99999999999999989 
		26 0.99999999999999989 34 0.99999999999999989 41 0.99999999999999989 55 0.99999999999999989 
		62 0.99999999999999989 78 0.99999999999999989 92 0.99999999999999989;
createNode animCurveTU -n "girl_FKKnee_R_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_FKKnee_R_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.0000000000000002 10 1.0000000000000002 
		26 1.0000000000000002 34 1.0000000000000002 41 1.0000000000000002 55 1.0000000000000002 
		62 1.0000000000000002 78 1.0000000000000002 92 1.0000000000000002;
createNode animCurveTA -n "girl_FKKnee_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 75.333348250175646 10 75.333348250175646 
		26 75.333348250175646 34 75.333348250175646 41 75.333348250175646 55 75.333348250175646 
		62 75.333348250175646 78 75.333348250175646 92 75.333348250175646;
createNode animCurveTA -n "girl_FKKnee_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKKnee_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraAnkle_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraAnkle_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraAnkle_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKAnkle_R_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.0000000000000002 10 1.0000000000000002 
		26 1.0000000000000002 34 1.0000000000000002 41 1.0000000000000002 55 1.0000000000000002 
		62 1.0000000000000002 78 1.0000000000000002 92 1.0000000000000002;
createNode animCurveTU -n "girl_FKAnkle_R_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.0000000000000002 10 1.0000000000000002 
		26 1.0000000000000002 34 1.0000000000000002 41 1.0000000000000002 55 1.0000000000000002 
		62 1.0000000000000002 78 1.0000000000000002 92 1.0000000000000002;
createNode animCurveTU -n "girl_FKAnkle_R_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.0000000000000002 10 1.0000000000000002 
		26 1.0000000000000002 34 1.0000000000000002 41 1.0000000000000002 55 1.0000000000000002 
		62 1.0000000000000002 78 1.0000000000000002 92 1.0000000000000002;
createNode animCurveTA -n "girl_FKAnkle_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKAnkle_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 23.040000415782014 10 23.040000415782014 
		26 23.040000415782014 34 23.040000415782014 41 23.040000415782014 55 23.040000415782014 
		62 23.040000415782014 78 23.040000415782014 92 23.040000415782014;
createNode animCurveTA -n "girl_FKAnkle_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraMiddleToe1_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraMiddleToe1_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraMiddleToe1_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKMiddleToe1_R_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_FKMiddleToe1_R_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_FKMiddleToe1_R_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTA -n "girl_FKMiddleToe1_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKMiddleToe1_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKMiddleToe1_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraBackA_M_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraBackA_M_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraBackA_M_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKBackA_M_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999967 10 0.99999999999999967 
		26 0.99999999999999967 34 0.99999999999999967 41 0.99999999999999967 55 0.99999999999999967 
		62 0.99999999999999967 78 0.99999999999999967 92 0.99999999999999967;
createNode animCurveTU -n "girl_FKBackA_M_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999944 10 0.99999999999999944 
		26 0.99999999999999944 34 0.99999999999999944 41 0.99999999999999944 55 0.99999999999999944 
		62 0.99999999999999944 78 0.99999999999999944 92 0.99999999999999944;
createNode animCurveTU -n "girl_FKBackA_M_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999989 10 0.99999999999999989 
		26 0.99999999999999989 34 0.99999999999999989 41 0.99999999999999989 55 0.99999999999999989 
		62 0.99999999999999989 78 0.99999999999999989 92 0.99999999999999989;
createNode animCurveTA -n "girl_FKBackA_M_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -1.4940187201541966 10 3.5368147617800454 
		26 21.608864495350513 34 22.765325626220474 41 26.686959808368957 48 32.042567387664896 
		55 32.042567387664896 62 32.042567387664896 78 -1.4940187201541966 92 -1.4940187201541966;
createNode animCurveTA -n "girl_FKBackA_M_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.21231936819650479 10 -0.10555194225793094 
		26 -7.8251949830058809 34 -7.9839464314745268 41 -8.4971393412842104 48 -9.1322064874371254 
		55 -9.1322064874371254 62 -9.1322064874371254 78 0.21231936819650479 92 0.21231936819650479;
createNode animCurveTA -n "girl_FKBackA_M_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 8.0864829283442798 10 8.0758540212989232 
		26 7.9696339774257954 34 7.8105878728448106 41 7.2482822413875088 48 6.4269981727608183 
		55 6.4269981727608183 62 6.4269981727608183 78 8.0864829283442798 92 8.0864829283442798;
createNode animCurveTA -n "girl_FKExtraBackB_M_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraBackB_M_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraBackB_M_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKBackB_M_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_FKBackB_M_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_FKBackB_M_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTA -n "girl_FKBackB_M_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -5.9919002747580032 10 0.96324120934084623 
		26 17.953530445420611 34 19.109551109266643 41 23.033601750277811 48 28.173327742189816 
		55 28.173327742189816 62 28.173327742189816 78 -5.9919002747580032 92 -5.9919002747580032;
createNode animCurveTA -n "girl_FKBackB_M_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1.0482071512878739 10 0.38512534490909106 
		26 -9.7931526688100465 34 -9.9941012634795676 41 -10.644256571137985 48 -11.417823700030585 
		55 -11.417823700030585 62 -11.417823700030585 78 1.0482071512878739 92 1.0482071512878739;
createNode animCurveTA -n "girl_FKBackB_M_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 9.8867372438892591 10 9.9005421620368406 
		26 10.105924648321892 34 9.9072908819425365 41 9.2040922460344419 48 8.2199948955437971 
		55 8.2199948955437971 62 8.2199948955437971 78 9.8867372438892591 92 9.8867372438892591;
createNode animCurveTA -n "girl_FKExtraChest_M_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraChest_M_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraChest_M_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKChest_M_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_FKChest_M_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_FKChest_M_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTA -n "girl_FKChest_M_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -4.0762394232620087 10 -4.0762394232620087 
		26 -9.1475565165630144 34 -7.9911358710622311 41 -4.0762394232620087 55 -4.0762394232620087 
		62 -4.0762394232620087 78 -4.0762394232620087 92 -4.0762394232620087;
createNode animCurveTA -n "girl_FKChest_M_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKChest_M_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraNeck_M_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraNeck_M_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraNeck_M_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKNeck_M_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_FKNeck_M_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.0000000000000004 10 1.0000000000000004 
		26 1.0000000000000004 34 1.0000000000000004 41 1.0000000000000004 55 1.0000000000000004 
		62 1.0000000000000004 78 1.0000000000000004 92 1.0000000000000004;
createNode animCurveTU -n "girl_FKNeck_M_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.0000000000000002 10 1.0000000000000002 
		26 1.0000000000000002 34 1.0000000000000002 41 1.0000000000000002 55 1.0000000000000002 
		62 1.0000000000000002 78 1.0000000000000002 92 1.0000000000000002;
createNode animCurveTA -n "girl_FKNeck_M_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 3.3359955434418795 10 -6.8385095673609122 
		26 3.3359955434418795 34 3.3359955434418795 41 3.3359955434418795 48 14.589179608012943 
		55 14.589179608012943 62 14.589179608012943 78 20.488372881589168 92 3.3359955434418795;
createNode animCurveTA -n "girl_FKNeck_M_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0.031435624406483925 
		62 0 78 -0.45108515750143602 92 0;
createNode animCurveTA -n "girl_FKNeck_M_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 7.9199999167549402 10 7.9199999167549402 
		26 7.9199999167549402 34 7.9199999167549402 41 7.9199999167549402 55 7.8152179280353167 
		62 7.9199999167549402 78 9.4235680138010203 92 7.9199999167549402;
createNode animCurveTA -n "girl_FKExtraHead_M_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraHead_M_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraHead_M_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKHead_M_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_FKHead_M_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_FKHead_M_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTA -n "girl_FKHead_M_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 5.7727404330954437 10 -37.905465603517094 
		26 -30.868017540560867 34 -30.868017540560867 41 -30.868017540560867 48 -19.194834176591975 
		55 -19.194834176591975 62 -19.194834176591975 78 20.464170346314457 92 5.7727404330954437;
createNode animCurveTA -n "girl_FKHead_M_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 10 1.7422161160203722 26 1.7422161160203722 
		34 1.7422161160203722 41 1.7422161160203722 48 2.5514535276774346 55 2.5514535276774346 
		62 2.5514535276774346 78 0.40651491964429531 92 0;
createNode animCurveTA -n "girl_FKHead_M_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 45.75470585545532 10 1.5479842265899517 
		26 1.5479842265899517 34 1.5479842265899517 41 1.5479842265899517 48 -8.0301712562826513 
		55 -8.0301712562826513 62 -8.0301712562826513 78 6.8543489502180996 92 45.75470585545532;
createNode animCurveTU -n "girl_FKExtraScapula_R_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.0000000000000004 10 1.0000000000000004 
		26 1.0000000000000004 34 1.0000000000000004 41 1.0000000000000004 55 1.0000000000000004 
		62 1.0000000000000004 78 1.0000000000000004 92 1.0000000000000004;
createNode animCurveTU -n "girl_FKExtraScapula_R_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.0000000000000002 10 1.0000000000000002 
		26 1.0000000000000002 34 1.0000000000000002 41 1.0000000000000002 55 1.0000000000000002 
		62 1.0000000000000002 78 1.0000000000000002 92 1.0000000000000002;
createNode animCurveTU -n "girl_FKExtraScapula_R_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.0000000000000004 10 1.0000000000000004 
		26 1.0000000000000004 34 1.0000000000000004 41 1.0000000000000004 55 1.0000000000000004 
		62 1.0000000000000004 78 1.0000000000000004 92 1.0000000000000004;
createNode animCurveTA -n "girl_FKExtraScapula_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraScapula_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraScapula_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_FKExtraScapula_R_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_FKExtraScapula_R_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_FKExtraScapula_R_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKScapula_R_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999989 10 0.99999999999999989 
		26 0.99999999999999989 34 0.99999999999999989 41 0.99999999999999989 55 0.99999999999999989 
		62 0.99999999999999989 78 0.99999999999999989 92 0.99999999999999989;
createNode animCurveTU -n "girl_FKScapula_R_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999956 10 0.99999999999999956 
		26 0.99999999999999956 34 0.99999999999999956 41 0.99999999999999956 55 0.99999999999999956 
		62 0.99999999999999956 78 0.99999999999999956 92 0.99999999999999956;
createNode animCurveTU -n "girl_FKScapula_R_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999922 10 0.99999999999999922 
		26 0.99999999999999922 34 0.99999999999999922 41 0.99999999999999922 55 0.99999999999999922 
		62 0.99999999999999922 78 0.99999999999999922 92 0.99999999999999922;
createNode animCurveTA -n "girl_FKScapula_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 1.1826288973797254 26 1.1826288973797254 
		34 1.1826288973797254 41 1.1826288973797254 55 0.37817673825020276 62 1.1826288973797254 
		78 12.726106473332527 92 0;
createNode animCurveTA -n "girl_FKScapula_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKScapula_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_FKScapula_R_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_FKScapula_R_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_FKScapula_R_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraShoulder_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraShoulder_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraShoulder_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKShoulder_R_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999989 10 0.99999999999999989 
		26 0.99999999999999989 34 0.99999999999999989 41 0.99999999999999989 55 0.99999999999999989 
		62 0.99999999999999989 78 0.99999999999999989 92 0.99999999999999989;
createNode animCurveTU -n "girl_FKShoulder_R_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.0000000000000002 10 1.0000000000000002 
		26 1.0000000000000002 34 1.0000000000000002 41 1.0000000000000002 55 1.0000000000000002 
		62 1.0000000000000002 78 1.0000000000000002 92 1.0000000000000002;
createNode animCurveTU -n "girl_FKShoulder_R_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999978 10 0.99999999999999978 
		26 0.99999999999999978 34 0.99999999999999978 41 0.99999999999999978 55 0.99999999999999978 
		62 0.99999999999999978 78 0.99999999999999978 92 0.99999999999999978;
createNode animCurveTA -n "girl_FKShoulder_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKShoulder_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKShoulder_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraElbow_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraElbow_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraElbow_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKElbow_R_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999967 10 0.99999999999999967 
		26 0.99999999999999967 34 0.99999999999999967 41 0.99999999999999967 55 0.99999999999999967 
		62 0.99999999999999967 78 0.99999999999999967 92 0.99999999999999967;
createNode animCurveTU -n "girl_FKElbow_R_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999956 10 0.99999999999999956 
		26 0.99999999999999956 34 0.99999999999999956 41 0.99999999999999956 55 0.99999999999999956 
		62 0.99999999999999956 78 0.99999999999999956 92 0.99999999999999956;
createNode animCurveTU -n "girl_FKElbow_R_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999978 10 0.99999999999999978 
		26 0.99999999999999978 34 0.99999999999999978 41 0.99999999999999978 55 0.99999999999999978 
		62 0.99999999999999978 78 0.99999999999999978 92 0.99999999999999978;
createNode animCurveTA -n "girl_FKElbow_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKElbow_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKElbow_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraWrist_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraWrist_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraWrist_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKWrist_R_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.999999999999999 10 0.999999999999999 
		26 0.999999999999999 34 0.999999999999999 41 0.999999999999999 55 0.999999999999999 
		62 0.999999999999999 78 0.999999999999999 92 0.999999999999999;
createNode animCurveTU -n "girl_FKWrist_R_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999933 10 0.99999999999999933 
		26 0.99999999999999933 34 0.99999999999999933 41 0.99999999999999933 55 0.99999999999999933 
		62 0.99999999999999933 78 0.99999999999999933 92 0.99999999999999933;
createNode animCurveTU -n "girl_FKWrist_R_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999922 10 0.99999999999999922 
		26 0.99999999999999922 34 0.99999999999999922 41 0.99999999999999922 55 0.99999999999999922 
		62 0.99999999999999922 78 0.99999999999999922 92 0.99999999999999922;
createNode animCurveTA -n "girl_FKWrist_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKWrist_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKWrist_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger1_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger1_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger1_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKMiddleFinger1_R_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.0000000000000002 10 1.0000000000000002 
		26 1.0000000000000002 34 1.0000000000000002 41 1.0000000000000002 55 1.0000000000000002 
		62 1.0000000000000002 78 1.0000000000000002 92 1.0000000000000002;
createNode animCurveTU -n "girl_FKMiddleFinger1_R_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999978 10 0.99999999999999978 
		26 0.99999999999999978 34 0.99999999999999978 41 0.99999999999999978 55 0.99999999999999978 
		62 0.99999999999999978 78 0.99999999999999978 92 0.99999999999999978;
createNode animCurveTU -n "girl_FKMiddleFinger1_R_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999956 10 0.99999999999999956 
		26 0.99999999999999956 34 0.99999999999999956 41 0.99999999999999956 55 0.99999999999999956 
		62 0.99999999999999956 78 0.99999999999999956 92 0.99999999999999956;
createNode animCurveTA -n "girl_FKMiddleFinger1_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -9.8496280095381739 10 17.849145909027573 
		26 17.849145909027573 34 17.849145909027573 41 17.849145909027573 55 17.849145909027573 
		62 17.849145909027573 78 17.849145909027573 92 -9.8496280095381739;
createNode animCurveTA -n "girl_FKMiddleFinger1_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -2.0984782587122006 10 -2.0984782587122006 
		26 -2.0984782587122006 34 -2.0984782587122006 41 -2.0984782587122006 55 -2.0984782587122006 
		62 -2.0984782587122006 78 -2.0984782587122006 92 -2.0984782587122006;
createNode animCurveTA -n "girl_FKMiddleFinger1_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -1.156749226655551 10 -1.156749226655551 
		26 -1.156749226655551 34 -1.156749226655551 41 -1.156749226655551 55 -1.156749226655551 
		62 -1.156749226655551 78 -1.156749226655551 92 -1.156749226655551;
createNode animCurveTA -n "girl_FKExtraMiddleFinger2_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger2_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger2_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKMiddleFinger2_R_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999978 10 0.99999999999999978 
		26 0.99999999999999978 34 0.99999999999999978 41 0.99999999999999978 55 0.99999999999999978 
		62 0.99999999999999978 78 0.99999999999999978 92 0.99999999999999978;
createNode animCurveTU -n "girl_FKMiddleFinger2_R_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999967 10 0.99999999999999967 
		26 0.99999999999999967 34 0.99999999999999967 41 0.99999999999999967 55 0.99999999999999967 
		62 0.99999999999999967 78 0.99999999999999967 92 0.99999999999999967;
createNode animCurveTU -n "girl_FKMiddleFinger2_R_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999933 10 0.99999999999999933 
		26 0.99999999999999933 34 0.99999999999999933 41 0.99999999999999933 55 0.99999999999999933 
		62 0.99999999999999933 78 0.99999999999999933 92 0.99999999999999933;
createNode animCurveTA -n "girl_FKMiddleFinger2_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -21.724355717678407 10 4.2225146516683045 
		26 4.2225146516683045 34 4.2225146516683045 41 4.2225146516683045 55 4.2225146516683045 
		62 4.2225146516683045 78 4.2225146516683045 92 -21.724355717678407;
createNode animCurveTA -n "girl_FKMiddleFinger2_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.54486597751175991 10 0.54486597751175991 
		26 0.54486597751175991 34 0.54486597751175991 41 0.54486597751175991 55 0.54486597751175991 
		62 0.54486597751175991 78 0.54486597751175991 92 0.54486597751175991;
createNode animCurveTA -n "girl_FKMiddleFinger2_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.57631240306333031 10 0.57631240306333031 
		26 0.57631240306333031 34 0.57631240306333031 41 0.57631240306333031 55 0.57631240306333031 
		62 0.57631240306333031 78 0.57631240306333031 92 0.57631240306333031;
createNode animCurveTA -n "girl_FKExtraMiddleFinger3_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger3_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger3_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKMiddleFinger3_R_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999944 10 0.99999999999999944 
		26 0.99999999999999944 34 0.99999999999999944 41 0.99999999999999944 55 0.99999999999999944 
		62 0.99999999999999944 78 0.99999999999999944 92 0.99999999999999944;
createNode animCurveTU -n "girl_FKMiddleFinger3_R_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999978 10 0.99999999999999978 
		26 0.99999999999999978 34 0.99999999999999978 41 0.99999999999999978 55 0.99999999999999978 
		62 0.99999999999999978 78 0.99999999999999978 92 0.99999999999999978;
createNode animCurveTU -n "girl_FKMiddleFinger3_R_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999989 10 0.99999999999999989 
		26 0.99999999999999989 34 0.99999999999999989 41 0.99999999999999989 55 0.99999999999999989 
		62 0.99999999999999989 78 0.99999999999999989 92 0.99999999999999989;
createNode animCurveTA -n "girl_FKMiddleFinger3_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKMiddleFinger3_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKMiddleFinger3_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger1_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger1_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger1_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKThumbFinger1_R_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999989 10 0.99999999999999989 
		26 0.99999999999999989 34 0.99999999999999989 41 0.99999999999999989 55 0.99999999999999989 
		62 0.99999999999999989 78 0.99999999999999989 92 0.99999999999999989;
createNode animCurveTU -n "girl_FKThumbFinger1_R_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999956 10 0.99999999999999956 
		26 0.99999999999999956 34 0.99999999999999956 41 0.99999999999999956 55 0.99999999999999956 
		62 0.99999999999999956 78 0.99999999999999956 92 0.99999999999999956;
createNode animCurveTU -n "girl_FKThumbFinger1_R_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTA -n "girl_FKThumbFinger1_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 2.735941457 10 2.735941457 26 2.735941457 
		34 2.735941457 41 2.735941457 55 2.735941457 62 2.735941457 78 2.735941457 92 2.735941457;
createNode animCurveTA -n "girl_FKThumbFinger1_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -18.208718699999999 10 -18.208718699999999 
		26 -18.208718699999999 34 -18.208718699999999 41 -18.208718699999999 55 -18.208718699999999 
		62 -18.208718699999999 78 -18.208718699999999 92 -18.208718699999999;
createNode animCurveTA -n "girl_FKThumbFinger1_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 36.37463082 10 36.37463082 26 36.37463082 
		34 36.37463082 41 36.37463082 55 36.37463082 62 36.37463082 78 36.37463082 92 36.37463082;
createNode animCurveTA -n "girl_FKExtraThumbFinger2_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger2_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger2_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKThumbFinger2_R_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999967 10 0.99999999999999967 
		26 0.99999999999999967 34 0.99999999999999967 41 0.99999999999999967 55 0.99999999999999967 
		62 0.99999999999999967 78 0.99999999999999967 92 0.99999999999999967;
createNode animCurveTU -n "girl_FKThumbFinger2_R_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999989 10 0.99999999999999989 
		26 0.99999999999999989 34 0.99999999999999989 41 0.99999999999999989 55 0.99999999999999989 
		62 0.99999999999999989 78 0.99999999999999989 92 0.99999999999999989;
createNode animCurveTU -n "girl_FKThumbFinger2_R_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999989 10 0.99999999999999989 
		26 0.99999999999999989 34 0.99999999999999989 41 0.99999999999999989 55 0.99999999999999989 
		62 0.99999999999999989 78 0.99999999999999989 92 0.99999999999999989;
createNode animCurveTA -n "girl_FKThumbFinger2_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -1.0012879291189114 10 -1.0012879291189114 
		26 -1.0012879291189114 34 -1.0012879291189114 41 -1.0012879291189114 55 -1.0012879291189114 
		62 -1.0012879291189114 78 -1.0012879291189114 92 -1.0012879291189114;
createNode animCurveTA -n "girl_FKThumbFinger2_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.44921033998490534 10 -0.44921033998490534 
		26 -0.44921033998490534 34 -0.44921033998490534 41 -0.44921033998490534 55 -0.44921033998490534 
		62 -0.44921033998490534 78 -0.44921033998490534 92 -0.44921033998490534;
createNode animCurveTA -n "girl_FKThumbFinger2_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 24.800969063594167 10 24.800969063594167 
		26 24.800969063594167 34 24.800969063594167 41 24.800969063594167 55 24.800969063594167 
		62 24.800969063594167 78 24.800969063594167 92 24.800969063594167;
createNode animCurveTA -n "girl_FKExtraThumbFinger3_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger3_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger3_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_FKThumbFinger3_R_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_FKThumbFinger3_R_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.0000000000000002 10 1.0000000000000002 
		26 1.0000000000000002 34 1.0000000000000002 41 1.0000000000000002 55 1.0000000000000002 
		62 1.0000000000000002 78 1.0000000000000002 92 1.0000000000000002;
createNode animCurveTU -n "girl_FKThumbFinger3_R_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.0000000000000002 10 1.0000000000000002 
		26 1.0000000000000002 34 1.0000000000000002 41 1.0000000000000002 55 1.0000000000000002 
		62 1.0000000000000002 78 1.0000000000000002 92 1.0000000000000002;
createNode animCurveTA -n "girl_FKThumbFinger3_R_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKThumbFinger3_R_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_FKThumbFinger3_R_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_Group_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_Group_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTU -n "girl_Group_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
createNode animCurveTA -n "girl_Group_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_Group_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTA -n "girl_Group_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_Group_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_Group_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTL -n "girl_Group_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 10 0 26 0 34 0 41 0 55 0 62 0 78 0 
		92 0;
createNode animCurveTU -n "girl_Group_visibility";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 10 1 26 1 34 1 41 1 55 1 62 1 78 1 
		92 1;
	setAttr -s 9 ".kot[0:8]"  5 5 5 5 5 5 5 5 
		5;
createNode lightLinker -n "lightLinker1";
	setAttr -s 5 ".lnk";
	setAttr -s 5 ".slnk";
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
	setAttr -s 5 ".st";
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
	setAttr -s 5 ".s";
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
	setAttr -s 3 ".tx";
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
	setAttr -s 2 ".gn";
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
	setAttr -s 3 ".sol";
connectAttr "Minigame2_failSource.cl" "clipLibrary1.sc[0]";
connectAttr "girl_back_skirt_b_CTRL_rotateZ.a" "clipLibrary1.cel[0].cev[0].cevr"
		;
connectAttr "girl_back_skirt_b_CTRL_rotateY.a" "clipLibrary1.cel[0].cev[1].cevr"
		;
connectAttr "girl_back_skirt_b_CTRL_rotateX.a" "clipLibrary1.cel[0].cev[2].cevr"
		;
connectAttr "girl_angularValues_4_.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "girl_angularValues_5_.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "girl_angularValues_6_.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "girl_R_cloak_C_CTRL_rotateZ.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "girl_R_cloak_C_CTRL_rotateY.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "girl_R_cloak_C_CTRL_rotateX.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "girl_R_cloak_B_CTRL_rotateZ.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "girl_R_cloak_B_CTRL_rotateY.a" "clipLibrary1.cel[0].cev[10].cevr";
connectAttr "girl_R_cloak_B_CTRL_rotateX.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "girl_R_cloak_A_CTRL_rotateZ.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "girl_R_cloak_A_CTRL_rotateY.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "girl_R_cloak_A_CTRL_rotateX.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "girl_L_cloak_C_CTRL_rotateZ.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "girl_L_cloak_C_CTRL_rotateY.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "girl_L_cloak_C_CTRL_rotateX.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "girl_L_cloak_B_CTRL_rotateZ.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "girl_L_cloak_B_CTRL_rotateY.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "girl_L_cloak_B_CTRL_rotateX.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "girl_L_cloak_A_CTRL_rotateZ.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "girl_L_cloak_A_CTRL_rotateY.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "girl_L_cloak_A_CTRL_rotateX.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "girl_cloak_D_CTRL_rotateZ.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "girl_cloak_D_CTRL_rotateY.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "girl_cloak_D_CTRL_rotateX.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "girl_cloak_C_CTRL_rotateZ.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "girl_cloak_C_CTRL_rotateY.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "girl_cloak_C_CTRL_rotateX.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "girl_cloak_B_CTRL_rotateZ.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "girl_cloak_B_CTRL_rotateY.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "girl_cloak_B_CTRL_rotateX.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "girl_cloak_A_CTRL_rotateZ.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "girl_cloak_A_CTRL_rotateY.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "girl_cloak_A_CTRL_rotateX.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "girl_angularValues_37_.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "girl_angularValues_38_.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "girl_angularValues_39_.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "girl_back_skirt_b_CTRL_translateZ.a" "clipLibrary1.cel[0].cev[39].cevr"
		;
connectAttr "girl_back_skirt_b_CTRL_translateY.a" "clipLibrary1.cel[0].cev[40].cevr"
		;
connectAttr "girl_back_skirt_b_CTRL_translateX.a" "clipLibrary1.cel[0].cev[41].cevr"
		;
connectAttr "girl_angularValues_40_.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "girl_angularValues_41_.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "girl_angularValues_42_.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "girl_linearValues_4_.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "girl_linearValues_5_.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "girl_linearValues_6_.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "girl_angularValues_43_.a" "clipLibrary1.cel[0].cev[48].cevr";
connectAttr "girl_angularValues_44_.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "girl_angularValues_45_.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "girl_linearValues_7_.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "girl_linearValues_8_.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "girl_linearValues_9_.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "girl_back_skirt_a_CTRL_rotateZ.a" "clipLibrary1.cel[0].cev[54].cevr"
		;
connectAttr "girl_back_skirt_a_CTRL_rotateY.a" "clipLibrary1.cel[0].cev[55].cevr"
		;
connectAttr "girl_back_skirt_a_CTRL_rotateX.a" "clipLibrary1.cel[0].cev[56].cevr"
		;
connectAttr "girl_back_skirt_a_CTRL_translateZ.a" "clipLibrary1.cel[0].cev[57].cevr"
		;
connectAttr "girl_back_skirt_a_CTRL_translateY.a" "clipLibrary1.cel[0].cev[58].cevr"
		;
connectAttr "girl_back_skirt_a_CTRL_translateX.a" "clipLibrary1.cel[0].cev[59].cevr"
		;
connectAttr "girl_front_skirt_b_CTRL_rotateZ.a" "clipLibrary1.cel[0].cev[60].cevr"
		;
connectAttr "girl_front_skirt_b_CTRL_rotateY.a" "clipLibrary1.cel[0].cev[61].cevr"
		;
connectAttr "girl_front_skirt_b_CTRL_rotateX.a" "clipLibrary1.cel[0].cev[62].cevr"
		;
connectAttr "girl_front_skirt_b_CTRL_translateZ.a" "clipLibrary1.cel[0].cev[63].cevr"
		;
connectAttr "girl_front_skirt_b_CTRL_translateY.a" "clipLibrary1.cel[0].cev[64].cevr"
		;
connectAttr "girl_front_skirt_b_CTRL_translateX.a" "clipLibrary1.cel[0].cev[65].cevr"
		;
connectAttr "girl_front_skirt_a_CTRL_rotateZ.a" "clipLibrary1.cel[0].cev[66].cevr"
		;
connectAttr "girl_front_skirt_a_CTRL_rotateY.a" "clipLibrary1.cel[0].cev[67].cevr"
		;
connectAttr "girl_front_skirt_a_CTRL_rotateX.a" "clipLibrary1.cel[0].cev[68].cevr"
		;
connectAttr "girl_front_skirt_a_CTRL_translateZ.a" "clipLibrary1.cel[0].cev[69].cevr"
		;
connectAttr "girl_front_skirt_a_CTRL_translateY.a" "clipLibrary1.cel[0].cev[70].cevr"
		;
connectAttr "girl_front_skirt_a_CTRL_translateX.a" "clipLibrary1.cel[0].cev[71].cevr"
		;
connectAttr "girl_skirt_HipA_L_CTRL_rotateZ.a" "clipLibrary1.cel[0].cev[72].cevr"
		;
connectAttr "girl_skirt_HipA_L_CTRL_rotateY.a" "clipLibrary1.cel[0].cev[73].cevr"
		;
connectAttr "girl_skirt_HipA_L_CTRL_rotateX.a" "clipLibrary1.cel[0].cev[74].cevr"
		;
connectAttr "girl_skirt_HipA_L_CTRL_translateZ.a" "clipLibrary1.cel[0].cev[75].cevr"
		;
connectAttr "girl_skirt_HipA_L_CTRL_translateY.a" "clipLibrary1.cel[0].cev[76].cevr"
		;
connectAttr "girl_skirt_HipA_L_CTRL_translateX.a" "clipLibrary1.cel[0].cev[77].cevr"
		;
connectAttr "girl_skirt_Hip_L_CTRL_rotateZ.a" "clipLibrary1.cel[0].cev[78].cevr"
		;
connectAttr "girl_skirt_Hip_L_CTRL_rotateY.a" "clipLibrary1.cel[0].cev[79].cevr"
		;
connectAttr "girl_skirt_Hip_L_CTRL_rotateX.a" "clipLibrary1.cel[0].cev[80].cevr"
		;
connectAttr "girl_skirt_Hip_L_CTRL_translateZ.a" "clipLibrary1.cel[0].cev[81].cevr"
		;
connectAttr "girl_skirt_Hip_L_CTRL_translateY.a" "clipLibrary1.cel[0].cev[82].cevr"
		;
connectAttr "girl_skirt_Hip_L_CTRL_translateX.a" "clipLibrary1.cel[0].cev[83].cevr"
		;
connectAttr "girl_skirt_HipA_R_CTRL_rotateZ.a" "clipLibrary1.cel[0].cev[84].cevr"
		;
connectAttr "girl_skirt_HipA_R_CTRL_rotateY.a" "clipLibrary1.cel[0].cev[85].cevr"
		;
connectAttr "girl_skirt_HipA_R_CTRL_rotateX.a" "clipLibrary1.cel[0].cev[86].cevr"
		;
connectAttr "girl_skirt_HipA_R_CTRL_translateZ.a" "clipLibrary1.cel[0].cev[87].cevr"
		;
connectAttr "girl_skirt_HipA_R_CTRL_translateY.a" "clipLibrary1.cel[0].cev[88].cevr"
		;
connectAttr "girl_skirt_HipA_R_CTRL_translateX.a" "clipLibrary1.cel[0].cev[89].cevr"
		;
connectAttr "girl_skirt_Hip_R_CTRL_rotateZ.a" "clipLibrary1.cel[0].cev[90].cevr"
		;
connectAttr "girl_skirt_Hip_R_CTRL_rotateY.a" "clipLibrary1.cel[0].cev[91].cevr"
		;
connectAttr "girl_skirt_Hip_R_CTRL_rotateX.a" "clipLibrary1.cel[0].cev[92].cevr"
		;
connectAttr "girl_skirt_Hip_R_CTRL_translateZ.a" "clipLibrary1.cel[0].cev[93].cevr"
		;
connectAttr "girl_skirt_Hip_R_CTRL_translateY.a" "clipLibrary1.cel[0].cev[94].cevr"
		;
connectAttr "girl_skirt_Hip_R_CTRL_translateX.a" "clipLibrary1.cel[0].cev[95].cevr"
		;
connectAttr "girl_Center_M_CenterBtwFeet.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "girl_Center_M_rotateZ.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "girl_Center_M_rotateY.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "girl_Center_M_rotateX.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "girl_Center_M_translateZ.a" "clipLibrary1.cel[0].cev[100].cevr";
connectAttr "girl_Center_M_translateY.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "girl_Center_M_translateX.a" "clipLibrary1.cel[0].cev[102].cevr";
connectAttr "girl_CenterExtra_M_rotateZ.a" "clipLibrary1.cel[0].cev[103].cevr";
connectAttr "girl_CenterExtra_M_rotateY.a" "clipLibrary1.cel[0].cev[104].cevr";
connectAttr "girl_CenterExtra_M_rotateX.a" "clipLibrary1.cel[0].cev[105].cevr";
connectAttr "girl_CenterExtra_M_translateZ.a" "clipLibrary1.cel[0].cev[106].cevr"
		;
connectAttr "girl_CenterExtra_M_translateY.a" "clipLibrary1.cel[0].cev[107].cevr"
		;
connectAttr "girl_CenterExtra_M_translateX.a" "clipLibrary1.cel[0].cev[108].cevr"
		;
connectAttr "girl_Fingers_L_Cup.a" "clipLibrary1.cel[0].cev[109].cevr";
connectAttr "girl_Fingers_L_Spread.a" "clipLibrary1.cel[0].cev[110].cevr";
connectAttr "girl_Fingers_L_ThumbFingerCurl.a" "clipLibrary1.cel[0].cev[111].cevr"
		;
connectAttr "girl_Fingers_L_PinkyFingerCurl.a" "clipLibrary1.cel[0].cev[112].cevr"
		;
connectAttr "girl_Fingers_L_RingFingerCurl.a" "clipLibrary1.cel[0].cev[113].cevr"
		;
connectAttr "girl_Fingers_L_MiddleFingerCurl.a" "clipLibrary1.cel[0].cev[114].cevr"
		;
connectAttr "girl_Fingers_L_IndexFingerCurl.a" "clipLibrary1.cel[0].cev[115].cevr"
		;
connectAttr "girl_IKExtraLegBall_L_rotateZ.a" "clipLibrary1.cel[0].cev[116].cevr"
		;
connectAttr "girl_IKExtraLegBall_L_rotateY.a" "clipLibrary1.cel[0].cev[117].cevr"
		;
connectAttr "girl_IKExtraLegBall_L_rotateX.a" "clipLibrary1.cel[0].cev[118].cevr"
		;
connectAttr "girl_IKLegBall_L_rotateX.a" "clipLibrary1.cel[0].cev[119].cevr";
connectAttr "girl_IKExtraLegToe_L_rotateZ.a" "clipLibrary1.cel[0].cev[120].cevr"
		;
connectAttr "girl_IKExtraLegToe_L_rotateY.a" "clipLibrary1.cel[0].cev[121].cevr"
		;
connectAttr "girl_IKExtraLegToe_L_rotateX.a" "clipLibrary1.cel[0].cev[122].cevr"
		;
connectAttr "girl_IKLegToe_L_rotateZ.a" "clipLibrary1.cel[0].cev[123].cevr";
connectAttr "girl_IKLegToe_L_rotateY.a" "clipLibrary1.cel[0].cev[124].cevr";
connectAttr "girl_IKLegToe_L_rotateX.a" "clipLibrary1.cel[0].cev[125].cevr";
connectAttr "girl_IKExtraLegHeel_L_rotateZ.a" "clipLibrary1.cel[0].cev[126].cevr"
		;
connectAttr "girl_IKExtraLegHeel_L_rotateY.a" "clipLibrary1.cel[0].cev[127].cevr"
		;
connectAttr "girl_IKExtraLegHeel_L_rotateX.a" "clipLibrary1.cel[0].cev[128].cevr"
		;
connectAttr "girl_IKLegHeel_L_rotateZ.a" "clipLibrary1.cel[0].cev[129].cevr";
connectAttr "girl_IKLegHeel_L_rotateY.a" "clipLibrary1.cel[0].cev[130].cevr";
connectAttr "girl_IKLegHeel_L_rotateX.a" "clipLibrary1.cel[0].cev[131].cevr";
connectAttr "girl_FKIKLeg_L_IKVis.a" "clipLibrary1.cel[0].cev[132].cevr";
connectAttr "girl_FKIKLeg_L_FKVis.a" "clipLibrary1.cel[0].cev[133].cevr";
connectAttr "girl_FKIKLeg_L_FKIKBlend.a" "clipLibrary1.cel[0].cev[134].cevr";
connectAttr "girl_PoleExtraLeg_L_translateZ.a" "clipLibrary1.cel[0].cev[135].cevr"
		;
connectAttr "girl_PoleExtraLeg_L_translateY.a" "clipLibrary1.cel[0].cev[136].cevr"
		;
connectAttr "girl_PoleExtraLeg_L_translateX.a" "clipLibrary1.cel[0].cev[137].cevr"
		;
connectAttr "girl_PoleLeg_L_follow.a" "clipLibrary1.cel[0].cev[138].cevr";
connectAttr "girl_PoleLeg_L_translateZ.a" "clipLibrary1.cel[0].cev[139].cevr";
connectAttr "girl_PoleLeg_L_translateY.a" "clipLibrary1.cel[0].cev[140].cevr";
connectAttr "girl_PoleLeg_L_translateX.a" "clipLibrary1.cel[0].cev[141].cevr";
connectAttr "girl_IKExtraLeg_L_rotateZ.a" "clipLibrary1.cel[0].cev[142].cevr";
connectAttr "girl_IKExtraLeg_L_rotateY.a" "clipLibrary1.cel[0].cev[143].cevr";
connectAttr "girl_IKExtraLeg_L_rotateX.a" "clipLibrary1.cel[0].cev[144].cevr";
connectAttr "girl_IKExtraLeg_L_translateZ.a" "clipLibrary1.cel[0].cev[145].cevr"
		;
connectAttr "girl_IKExtraLeg_L_translateY.a" "clipLibrary1.cel[0].cev[146].cevr"
		;
connectAttr "girl_IKExtraLeg_L_translateX.a" "clipLibrary1.cel[0].cev[147].cevr"
		;
connectAttr "girl_IKLeg_L_Lenght2.a" "clipLibrary1.cel[0].cev[148].cevr";
connectAttr "girl_IKLeg_L_Lenght1.a" "clipLibrary1.cel[0].cev[149].cevr";
connectAttr "girl_IKLeg_L_antiPop.a" "clipLibrary1.cel[0].cev[150].cevr";
connectAttr "girl_IKLeg_L_stretchy.a" "clipLibrary1.cel[0].cev[151].cevr";
connectAttr "girl_IKLeg_L_rollAngle.a" "clipLibrary1.cel[0].cev[152].cevr";
connectAttr "girl_IKLeg_L_roll.a" "clipLibrary1.cel[0].cev[153].cevr";
connectAttr "girl_IKLeg_L_toe.a" "clipLibrary1.cel[0].cev[154].cevr";
connectAttr "girl_IKLeg_L_swivel.a" "clipLibrary1.cel[0].cev[155].cevr";
connectAttr "girl_IKLeg_L_rotateZ.a" "clipLibrary1.cel[0].cev[156].cevr";
connectAttr "girl_IKLeg_L_rotateY.a" "clipLibrary1.cel[0].cev[157].cevr";
connectAttr "girl_IKLeg_L_rotateX.a" "clipLibrary1.cel[0].cev[158].cevr";
connectAttr "girl_IKLeg_L_translateZ.a" "clipLibrary1.cel[0].cev[159].cevr";
connectAttr "girl_IKLeg_L_translateY.a" "clipLibrary1.cel[0].cev[160].cevr";
connectAttr "girl_IKLeg_L_translateX.a" "clipLibrary1.cel[0].cev[161].cevr";
connectAttr "girl_FKIKArm_L_IKVis.a" "clipLibrary1.cel[0].cev[162].cevr";
connectAttr "girl_FKIKArm_L_FKVis.a" "clipLibrary1.cel[0].cev[163].cevr";
connectAttr "girl_FKIKArm_L_FKIKBlend.a" "clipLibrary1.cel[0].cev[164].cevr";
connectAttr "girl_PoleExtraArm_L_translateZ.a" "clipLibrary1.cel[0].cev[165].cevr"
		;
connectAttr "girl_PoleExtraArm_L_translateY.a" "clipLibrary1.cel[0].cev[166].cevr"
		;
connectAttr "girl_PoleExtraArm_L_translateX.a" "clipLibrary1.cel[0].cev[167].cevr"
		;
connectAttr "girl_PoleArm_L_follow.a" "clipLibrary1.cel[0].cev[168].cevr";
connectAttr "girl_PoleArm_L_translateZ.a" "clipLibrary1.cel[0].cev[169].cevr";
connectAttr "girl_PoleArm_L_translateY.a" "clipLibrary1.cel[0].cev[170].cevr";
connectAttr "girl_PoleArm_L_translateX.a" "clipLibrary1.cel[0].cev[171].cevr";
connectAttr "girl_IKExtraArm_L_rotateZ.a" "clipLibrary1.cel[0].cev[172].cevr";
connectAttr "girl_IKExtraArm_L_rotateY.a" "clipLibrary1.cel[0].cev[173].cevr";
connectAttr "girl_IKExtraArm_L_rotateX.a" "clipLibrary1.cel[0].cev[174].cevr";
connectAttr "girl_IKExtraArm_L_translateZ.a" "clipLibrary1.cel[0].cev[175].cevr"
		;
connectAttr "girl_IKExtraArm_L_translateY.a" "clipLibrary1.cel[0].cev[176].cevr"
		;
connectAttr "girl_IKExtraArm_L_translateX.a" "clipLibrary1.cel[0].cev[177].cevr"
		;
connectAttr "girl_IKArm_L_Lenght2.a" "clipLibrary1.cel[0].cev[178].cevr";
connectAttr "girl_IKArm_L_Lenght1.a" "clipLibrary1.cel[0].cev[179].cevr";
connectAttr "girl_IKArm_L_antiPop.a" "clipLibrary1.cel[0].cev[180].cevr";
connectAttr "girl_IKArm_L_stretchy.a" "clipLibrary1.cel[0].cev[181].cevr";
connectAttr "girl_IKArm_L_follow.a" "clipLibrary1.cel[0].cev[182].cevr";
connectAttr "girl_IKArm_L_rotateZ.a" "clipLibrary1.cel[0].cev[183].cevr";
connectAttr "girl_IKArm_L_rotateY.a" "clipLibrary1.cel[0].cev[184].cevr";
connectAttr "girl_IKArm_L_rotateX.a" "clipLibrary1.cel[0].cev[185].cevr";
connectAttr "girl_IKArm_L_translateZ.a" "clipLibrary1.cel[0].cev[186].cevr";
connectAttr "girl_IKArm_L_translateY.a" "clipLibrary1.cel[0].cev[187].cevr";
connectAttr "girl_IKArm_L_translateX.a" "clipLibrary1.cel[0].cev[188].cevr";
connectAttr "girl_Fingers_R_Cup.a" "clipLibrary1.cel[0].cev[189].cevr";
connectAttr "girl_Fingers_R_Spread.a" "clipLibrary1.cel[0].cev[190].cevr";
connectAttr "girl_Fingers_R_ThumbFingerCurl.a" "clipLibrary1.cel[0].cev[191].cevr"
		;
connectAttr "girl_Fingers_R_PinkyFingerCurl.a" "clipLibrary1.cel[0].cev[192].cevr"
		;
connectAttr "girl_Fingers_R_RingFingerCurl.a" "clipLibrary1.cel[0].cev[193].cevr"
		;
connectAttr "girl_Fingers_R_MiddleFingerCurl.a" "clipLibrary1.cel[0].cev[194].cevr"
		;
connectAttr "girl_Fingers_R_IndexFingerCurl.a" "clipLibrary1.cel[0].cev[195].cevr"
		;
connectAttr "girl_IKExtraSpine4_M_scaleZ.a" "clipLibrary1.cel[0].cev[196].cevr";
connectAttr "girl_IKExtraSpine4_M_scaleY.a" "clipLibrary1.cel[0].cev[197].cevr";
connectAttr "girl_IKExtraSpine4_M_scaleX.a" "clipLibrary1.cel[0].cev[198].cevr";
connectAttr "girl_IKExtraSpine4_M_rotateZ.a" "clipLibrary1.cel[0].cev[199].cevr"
		;
connectAttr "girl_IKExtraSpine4_M_rotateY.a" "clipLibrary1.cel[0].cev[200].cevr"
		;
connectAttr "girl_IKExtraSpine4_M_rotateX.a" "clipLibrary1.cel[0].cev[201].cevr"
		;
connectAttr "girl_IKExtraSpine4_M_translateZ.a" "clipLibrary1.cel[0].cev[202].cevr"
		;
connectAttr "girl_IKExtraSpine4_M_translateY.a" "clipLibrary1.cel[0].cev[203].cevr"
		;
connectAttr "girl_IKExtraSpine4_M_translateX.a" "clipLibrary1.cel[0].cev[204].cevr"
		;
connectAttr "girl_IKExtraSpine4_M_visibility.a" "clipLibrary1.cel[0].cev[205].cevr"
		;
connectAttr "girl_IKSpine4_M_stretchy.a" "clipLibrary1.cel[0].cev[206].cevr";
connectAttr "girl_IKSpine4_M_stiff.a" "clipLibrary1.cel[0].cev[207].cevr";
connectAttr "girl_IKSpine4_M_rotateZ.a" "clipLibrary1.cel[0].cev[208].cevr";
connectAttr "girl_IKSpine4_M_rotateY.a" "clipLibrary1.cel[0].cev[209].cevr";
connectAttr "girl_IKSpine4_M_rotateX.a" "clipLibrary1.cel[0].cev[210].cevr";
connectAttr "girl_IKSpine4_M_translateZ.a" "clipLibrary1.cel[0].cev[211].cevr";
connectAttr "girl_IKSpine4_M_translateY.a" "clipLibrary1.cel[0].cev[212].cevr";
connectAttr "girl_IKSpine4_M_translateX.a" "clipLibrary1.cel[0].cev[213].cevr";
connectAttr "girl_IKExtraSpine2_M_scaleZ.a" "clipLibrary1.cel[0].cev[214].cevr";
connectAttr "girl_IKExtraSpine2_M_scaleY.a" "clipLibrary1.cel[0].cev[215].cevr";
connectAttr "girl_IKExtraSpine2_M_scaleX.a" "clipLibrary1.cel[0].cev[216].cevr";
connectAttr "girl_IKExtraSpine2_M_rotateZ.a" "clipLibrary1.cel[0].cev[217].cevr"
		;
connectAttr "girl_IKExtraSpine2_M_rotateY.a" "clipLibrary1.cel[0].cev[218].cevr"
		;
connectAttr "girl_IKExtraSpine2_M_rotateX.a" "clipLibrary1.cel[0].cev[219].cevr"
		;
connectAttr "girl_IKExtraSpine2_M_translateZ.a" "clipLibrary1.cel[0].cev[220].cevr"
		;
connectAttr "girl_IKExtraSpine2_M_translateY.a" "clipLibrary1.cel[0].cev[221].cevr"
		;
connectAttr "girl_IKExtraSpine2_M_translateX.a" "clipLibrary1.cel[0].cev[222].cevr"
		;
connectAttr "girl_IKExtraSpine2_M_visibility.a" "clipLibrary1.cel[0].cev[223].cevr"
		;
connectAttr "girl_IKSpine2_M_stiff.a" "clipLibrary1.cel[0].cev[224].cevr";
connectAttr "girl_IKSpine2_M_rotateZ.a" "clipLibrary1.cel[0].cev[225].cevr";
connectAttr "girl_IKSpine2_M_rotateY.a" "clipLibrary1.cel[0].cev[226].cevr";
connectAttr "girl_IKSpine2_M_rotateX.a" "clipLibrary1.cel[0].cev[227].cevr";
connectAttr "girl_IKSpine2_M_translateZ.a" "clipLibrary1.cel[0].cev[228].cevr";
connectAttr "girl_IKSpine2_M_translateY.a" "clipLibrary1.cel[0].cev[229].cevr";
connectAttr "girl_IKSpine2_M_translateX.a" "clipLibrary1.cel[0].cev[230].cevr";
connectAttr "girl_IKExtraSpine0_M_scaleZ.a" "clipLibrary1.cel[0].cev[231].cevr";
connectAttr "girl_IKExtraSpine0_M_scaleY.a" "clipLibrary1.cel[0].cev[232].cevr";
connectAttr "girl_IKExtraSpine0_M_scaleX.a" "clipLibrary1.cel[0].cev[233].cevr";
connectAttr "girl_IKExtraSpine0_M_rotateZ.a" "clipLibrary1.cel[0].cev[234].cevr"
		;
connectAttr "girl_IKExtraSpine0_M_rotateY.a" "clipLibrary1.cel[0].cev[235].cevr"
		;
connectAttr "girl_IKExtraSpine0_M_rotateX.a" "clipLibrary1.cel[0].cev[236].cevr"
		;
connectAttr "girl_IKExtraSpine0_M_translateZ.a" "clipLibrary1.cel[0].cev[237].cevr"
		;
connectAttr "girl_IKExtraSpine0_M_translateY.a" "clipLibrary1.cel[0].cev[238].cevr"
		;
connectAttr "girl_IKExtraSpine0_M_translateX.a" "clipLibrary1.cel[0].cev[239].cevr"
		;
connectAttr "girl_IKExtraSpine0_M_visibility.a" "clipLibrary1.cel[0].cev[240].cevr"
		;
connectAttr "girl_IKSpine0_M_stiff.a" "clipLibrary1.cel[0].cev[241].cevr";
connectAttr "girl_IKSpine0_M_rotateZ.a" "clipLibrary1.cel[0].cev[242].cevr";
connectAttr "girl_IKSpine0_M_rotateY.a" "clipLibrary1.cel[0].cev[243].cevr";
connectAttr "girl_IKSpine0_M_rotateX.a" "clipLibrary1.cel[0].cev[244].cevr";
connectAttr "girl_IKSpine0_M_translateZ.a" "clipLibrary1.cel[0].cev[245].cevr";
connectAttr "girl_IKSpine0_M_translateY.a" "clipLibrary1.cel[0].cev[246].cevr";
connectAttr "girl_IKSpine0_M_translateX.a" "clipLibrary1.cel[0].cev[247].cevr";
connectAttr "girl_IKExtraLegBall_R_rotateZ.a" "clipLibrary1.cel[0].cev[248].cevr"
		;
connectAttr "girl_IKExtraLegBall_R_rotateY.a" "clipLibrary1.cel[0].cev[249].cevr"
		;
connectAttr "girl_IKExtraLegBall_R_rotateX.a" "clipLibrary1.cel[0].cev[250].cevr"
		;
connectAttr "girl_IKLegBall_R_rotateX.a" "clipLibrary1.cel[0].cev[251].cevr";
connectAttr "girl_IKExtraLegToe_R_rotateZ.a" "clipLibrary1.cel[0].cev[252].cevr"
		;
connectAttr "girl_IKExtraLegToe_R_rotateY.a" "clipLibrary1.cel[0].cev[253].cevr"
		;
connectAttr "girl_IKExtraLegToe_R_rotateX.a" "clipLibrary1.cel[0].cev[254].cevr"
		;
connectAttr "girl_IKLegToe_R_rotateZ.a" "clipLibrary1.cel[0].cev[255].cevr";
connectAttr "girl_IKLegToe_R_rotateY.a" "clipLibrary1.cel[0].cev[256].cevr";
connectAttr "girl_IKLegToe_R_rotateX.a" "clipLibrary1.cel[0].cev[257].cevr";
connectAttr "girl_IKExtraLegHeel_R_rotateZ.a" "clipLibrary1.cel[0].cev[258].cevr"
		;
connectAttr "girl_IKExtraLegHeel_R_rotateY.a" "clipLibrary1.cel[0].cev[259].cevr"
		;
connectAttr "girl_IKExtraLegHeel_R_rotateX.a" "clipLibrary1.cel[0].cev[260].cevr"
		;
connectAttr "girl_IKLegHeel_R_rotateZ.a" "clipLibrary1.cel[0].cev[261].cevr";
connectAttr "girl_IKLegHeel_R_rotateY.a" "clipLibrary1.cel[0].cev[262].cevr";
connectAttr "girl_IKLegHeel_R_rotateX.a" "clipLibrary1.cel[0].cev[263].cevr";
connectAttr "girl_FKIKLeg_R_IKVis.a" "clipLibrary1.cel[0].cev[264].cevr";
connectAttr "girl_FKIKLeg_R_FKVis.a" "clipLibrary1.cel[0].cev[265].cevr";
connectAttr "girl_FKIKLeg_R_FKIKBlend.a" "clipLibrary1.cel[0].cev[266].cevr";
connectAttr "girl_PoleExtraLeg_R_translateZ.a" "clipLibrary1.cel[0].cev[267].cevr"
		;
connectAttr "girl_PoleExtraLeg_R_translateY.a" "clipLibrary1.cel[0].cev[268].cevr"
		;
connectAttr "girl_PoleExtraLeg_R_translateX.a" "clipLibrary1.cel[0].cev[269].cevr"
		;
connectAttr "girl_PoleLeg_R_follow.a" "clipLibrary1.cel[0].cev[270].cevr";
connectAttr "girl_PoleLeg_R_translateZ.a" "clipLibrary1.cel[0].cev[271].cevr";
connectAttr "girl_PoleLeg_R_translateY.a" "clipLibrary1.cel[0].cev[272].cevr";
connectAttr "girl_PoleLeg_R_translateX.a" "clipLibrary1.cel[0].cev[273].cevr";
connectAttr "girl_IKExtraLeg_R_rotateZ.a" "clipLibrary1.cel[0].cev[274].cevr";
connectAttr "girl_IKExtraLeg_R_rotateY.a" "clipLibrary1.cel[0].cev[275].cevr";
connectAttr "girl_IKExtraLeg_R_rotateX.a" "clipLibrary1.cel[0].cev[276].cevr";
connectAttr "girl_IKExtraLeg_R_translateZ.a" "clipLibrary1.cel[0].cev[277].cevr"
		;
connectAttr "girl_IKExtraLeg_R_translateY.a" "clipLibrary1.cel[0].cev[278].cevr"
		;
connectAttr "girl_IKExtraLeg_R_translateX.a" "clipLibrary1.cel[0].cev[279].cevr"
		;
connectAttr "girl_IKLeg_R_Lenght2.a" "clipLibrary1.cel[0].cev[280].cevr";
connectAttr "girl_IKLeg_R_Lenght1.a" "clipLibrary1.cel[0].cev[281].cevr";
connectAttr "girl_IKLeg_R_antiPop.a" "clipLibrary1.cel[0].cev[282].cevr";
connectAttr "girl_IKLeg_R_stretchy.a" "clipLibrary1.cel[0].cev[283].cevr";
connectAttr "girl_IKLeg_R_rollAngle.a" "clipLibrary1.cel[0].cev[284].cevr";
connectAttr "girl_IKLeg_R_roll.a" "clipLibrary1.cel[0].cev[285].cevr";
connectAttr "girl_IKLeg_R_toe.a" "clipLibrary1.cel[0].cev[286].cevr";
connectAttr "girl_IKLeg_R_swivel.a" "clipLibrary1.cel[0].cev[287].cevr";
connectAttr "girl_IKLeg_R_rotateZ.a" "clipLibrary1.cel[0].cev[288].cevr";
connectAttr "girl_IKLeg_R_rotateY.a" "clipLibrary1.cel[0].cev[289].cevr";
connectAttr "girl_IKLeg_R_rotateX.a" "clipLibrary1.cel[0].cev[290].cevr";
connectAttr "girl_IKLeg_R_translateZ.a" "clipLibrary1.cel[0].cev[291].cevr";
connectAttr "girl_IKLeg_R_translateY.a" "clipLibrary1.cel[0].cev[292].cevr";
connectAttr "girl_IKLeg_R_translateX.a" "clipLibrary1.cel[0].cev[293].cevr";
connectAttr "girl_FKIKArm_R_IKVis.a" "clipLibrary1.cel[0].cev[294].cevr";
connectAttr "girl_FKIKArm_R_FKVis.a" "clipLibrary1.cel[0].cev[295].cevr";
connectAttr "girl_FKIKArm_R_FKIKBlend.a" "clipLibrary1.cel[0].cev[296].cevr";
connectAttr "girl_PoleExtraArm_R_translateZ.a" "clipLibrary1.cel[0].cev[297].cevr"
		;
connectAttr "girl_PoleExtraArm_R_translateY.a" "clipLibrary1.cel[0].cev[298].cevr"
		;
connectAttr "girl_PoleExtraArm_R_translateX.a" "clipLibrary1.cel[0].cev[299].cevr"
		;
connectAttr "girl_PoleArm_R_follow.a" "clipLibrary1.cel[0].cev[300].cevr";
connectAttr "girl_PoleArm_R_translateZ.a" "clipLibrary1.cel[0].cev[301].cevr";
connectAttr "girl_PoleArm_R_translateY.a" "clipLibrary1.cel[0].cev[302].cevr";
connectAttr "girl_PoleArm_R_translateX.a" "clipLibrary1.cel[0].cev[303].cevr";
connectAttr "girl_IKExtraArm_R_rotateZ.a" "clipLibrary1.cel[0].cev[304].cevr";
connectAttr "girl_IKExtraArm_R_rotateY.a" "clipLibrary1.cel[0].cev[305].cevr";
connectAttr "girl_IKExtraArm_R_rotateX.a" "clipLibrary1.cel[0].cev[306].cevr";
connectAttr "girl_IKExtraArm_R_translateZ.a" "clipLibrary1.cel[0].cev[307].cevr"
		;
connectAttr "girl_IKExtraArm_R_translateY.a" "clipLibrary1.cel[0].cev[308].cevr"
		;
connectAttr "girl_IKExtraArm_R_translateX.a" "clipLibrary1.cel[0].cev[309].cevr"
		;
connectAttr "girl_IKArm_R_Lenght2.a" "clipLibrary1.cel[0].cev[310].cevr";
connectAttr "girl_IKArm_R_Lenght1.a" "clipLibrary1.cel[0].cev[311].cevr";
connectAttr "girl_IKArm_R_antiPop.a" "clipLibrary1.cel[0].cev[312].cevr";
connectAttr "girl_IKArm_R_stretchy.a" "clipLibrary1.cel[0].cev[313].cevr";
connectAttr "girl_IKArm_R_follow.a" "clipLibrary1.cel[0].cev[314].cevr";
connectAttr "girl_IKArm_R_rotateZ.a" "clipLibrary1.cel[0].cev[315].cevr";
connectAttr "girl_IKArm_R_rotateY.a" "clipLibrary1.cel[0].cev[316].cevr";
connectAttr "girl_IKArm_R_rotateX.a" "clipLibrary1.cel[0].cev[317].cevr";
connectAttr "girl_IKArm_R_translateZ.a" "clipLibrary1.cel[0].cev[318].cevr";
connectAttr "girl_IKArm_R_translateY.a" "clipLibrary1.cel[0].cev[319].cevr";
connectAttr "girl_IKArm_R_translateX.a" "clipLibrary1.cel[0].cev[320].cevr";
connectAttr "girl_HipSwingerRoot_M_rotateZ.a" "clipLibrary1.cel[0].cev[321].cevr"
		;
connectAttr "girl_HipSwingerRoot_M_rotateY.a" "clipLibrary1.cel[0].cev[322].cevr"
		;
connectAttr "girl_HipSwingerRoot_M_rotateX.a" "clipLibrary1.cel[0].cev[323].cevr"
		;
connectAttr "girl_FKExtraHip_L_rotateZ.a" "clipLibrary1.cel[0].cev[324].cevr";
connectAttr "girl_FKExtraHip_L_rotateY.a" "clipLibrary1.cel[0].cev[325].cevr";
connectAttr "girl_FKExtraHip_L_rotateX.a" "clipLibrary1.cel[0].cev[326].cevr";
connectAttr "girl_FKHip_L_scaleZ.a" "clipLibrary1.cel[0].cev[327].cevr";
connectAttr "girl_FKHip_L_scaleY.a" "clipLibrary1.cel[0].cev[328].cevr";
connectAttr "girl_FKHip_L_scaleX.a" "clipLibrary1.cel[0].cev[329].cevr";
connectAttr "girl_FKHip_L_rotateZ.a" "clipLibrary1.cel[0].cev[330].cevr";
connectAttr "girl_FKHip_L_rotateY.a" "clipLibrary1.cel[0].cev[331].cevr";
connectAttr "girl_FKHip_L_rotateX.a" "clipLibrary1.cel[0].cev[332].cevr";
connectAttr "girl_FKExtraKnee_L_rotateZ.a" "clipLibrary1.cel[0].cev[333].cevr";
connectAttr "girl_FKExtraKnee_L_rotateY.a" "clipLibrary1.cel[0].cev[334].cevr";
connectAttr "girl_FKExtraKnee_L_rotateX.a" "clipLibrary1.cel[0].cev[335].cevr";
connectAttr "girl_FKKnee_L_scaleZ.a" "clipLibrary1.cel[0].cev[336].cevr";
connectAttr "girl_FKKnee_L_scaleY.a" "clipLibrary1.cel[0].cev[337].cevr";
connectAttr "girl_FKKnee_L_scaleX.a" "clipLibrary1.cel[0].cev[338].cevr";
connectAttr "girl_FKKnee_L_rotateZ.a" "clipLibrary1.cel[0].cev[339].cevr";
connectAttr "girl_FKKnee_L_rotateY.a" "clipLibrary1.cel[0].cev[340].cevr";
connectAttr "girl_FKKnee_L_rotateX.a" "clipLibrary1.cel[0].cev[341].cevr";
connectAttr "girl_FKExtraAnkle_L_rotateZ.a" "clipLibrary1.cel[0].cev[342].cevr";
connectAttr "girl_FKExtraAnkle_L_rotateY.a" "clipLibrary1.cel[0].cev[343].cevr";
connectAttr "girl_FKExtraAnkle_L_rotateX.a" "clipLibrary1.cel[0].cev[344].cevr";
connectAttr "girl_FKAnkle_L_scaleZ.a" "clipLibrary1.cel[0].cev[345].cevr";
connectAttr "girl_FKAnkle_L_scaleY.a" "clipLibrary1.cel[0].cev[346].cevr";
connectAttr "girl_FKAnkle_L_scaleX.a" "clipLibrary1.cel[0].cev[347].cevr";
connectAttr "girl_FKAnkle_L_rotateZ.a" "clipLibrary1.cel[0].cev[348].cevr";
connectAttr "girl_FKAnkle_L_rotateY.a" "clipLibrary1.cel[0].cev[349].cevr";
connectAttr "girl_FKAnkle_L_rotateX.a" "clipLibrary1.cel[0].cev[350].cevr";
connectAttr "girl_FKExtraMiddleToe1_L_rotateZ.a" "clipLibrary1.cel[0].cev[351].cevr"
		;
connectAttr "girl_FKExtraMiddleToe1_L_rotateY.a" "clipLibrary1.cel[0].cev[352].cevr"
		;
connectAttr "girl_FKExtraMiddleToe1_L_rotateX.a" "clipLibrary1.cel[0].cev[353].cevr"
		;
connectAttr "girl_FKMiddleToe1_L_scaleZ.a" "clipLibrary1.cel[0].cev[354].cevr";
connectAttr "girl_FKMiddleToe1_L_scaleY.a" "clipLibrary1.cel[0].cev[355].cevr";
connectAttr "girl_FKMiddleToe1_L_scaleX.a" "clipLibrary1.cel[0].cev[356].cevr";
connectAttr "girl_FKMiddleToe1_L_rotateZ.a" "clipLibrary1.cel[0].cev[357].cevr";
connectAttr "girl_FKMiddleToe1_L_rotateY.a" "clipLibrary1.cel[0].cev[358].cevr";
connectAttr "girl_FKMiddleToe1_L_rotateX.a" "clipLibrary1.cel[0].cev[359].cevr";
connectAttr "girl_FKExtraScapula_L_scaleZ.a" "clipLibrary1.cel[0].cev[360].cevr"
		;
connectAttr "girl_FKExtraScapula_L_scaleY.a" "clipLibrary1.cel[0].cev[361].cevr"
		;
connectAttr "girl_FKExtraScapula_L_scaleX.a" "clipLibrary1.cel[0].cev[362].cevr"
		;
connectAttr "girl_FKExtraScapula_L_rotateZ.a" "clipLibrary1.cel[0].cev[363].cevr"
		;
connectAttr "girl_FKExtraScapula_L_rotateY.a" "clipLibrary1.cel[0].cev[364].cevr"
		;
connectAttr "girl_FKExtraScapula_L_rotateX.a" "clipLibrary1.cel[0].cev[365].cevr"
		;
connectAttr "girl_FKExtraScapula_L_translateZ.a" "clipLibrary1.cel[0].cev[366].cevr"
		;
connectAttr "girl_FKExtraScapula_L_translateY.a" "clipLibrary1.cel[0].cev[367].cevr"
		;
connectAttr "girl_FKExtraScapula_L_translateX.a" "clipLibrary1.cel[0].cev[368].cevr"
		;
connectAttr "girl_FKScapula_L_scaleZ.a" "clipLibrary1.cel[0].cev[369].cevr";
connectAttr "girl_FKScapula_L_scaleY.a" "clipLibrary1.cel[0].cev[370].cevr";
connectAttr "girl_FKScapula_L_scaleX.a" "clipLibrary1.cel[0].cev[371].cevr";
connectAttr "girl_FKScapula_L_rotateZ.a" "clipLibrary1.cel[0].cev[372].cevr";
connectAttr "girl_FKScapula_L_rotateY.a" "clipLibrary1.cel[0].cev[373].cevr";
connectAttr "girl_FKScapula_L_rotateX.a" "clipLibrary1.cel[0].cev[374].cevr";
connectAttr "girl_FKScapula_L_translateZ.a" "clipLibrary1.cel[0].cev[375].cevr";
connectAttr "girl_FKScapula_L_translateY.a" "clipLibrary1.cel[0].cev[376].cevr";
connectAttr "girl_FKScapula_L_translateX.a" "clipLibrary1.cel[0].cev[377].cevr";
connectAttr "girl_FKExtraShoulder_L_rotateZ.a" "clipLibrary1.cel[0].cev[378].cevr"
		;
connectAttr "girl_FKExtraShoulder_L_rotateY.a" "clipLibrary1.cel[0].cev[379].cevr"
		;
connectAttr "girl_FKExtraShoulder_L_rotateX.a" "clipLibrary1.cel[0].cev[380].cevr"
		;
connectAttr "girl_FKShoulder_L_scaleZ.a" "clipLibrary1.cel[0].cev[381].cevr";
connectAttr "girl_FKShoulder_L_scaleY.a" "clipLibrary1.cel[0].cev[382].cevr";
connectAttr "girl_FKShoulder_L_scaleX.a" "clipLibrary1.cel[0].cev[383].cevr";
connectAttr "girl_FKShoulder_L_rotateZ.a" "clipLibrary1.cel[0].cev[384].cevr";
connectAttr "girl_FKShoulder_L_rotateY.a" "clipLibrary1.cel[0].cev[385].cevr";
connectAttr "girl_FKShoulder_L_rotateX.a" "clipLibrary1.cel[0].cev[386].cevr";
connectAttr "girl_FKExtraElbow_L_rotateZ.a" "clipLibrary1.cel[0].cev[387].cevr";
connectAttr "girl_FKExtraElbow_L_rotateY.a" "clipLibrary1.cel[0].cev[388].cevr";
connectAttr "girl_FKExtraElbow_L_rotateX.a" "clipLibrary1.cel[0].cev[389].cevr";
connectAttr "girl_FKElbow_L_scaleZ.a" "clipLibrary1.cel[0].cev[390].cevr";
connectAttr "girl_FKElbow_L_scaleY.a" "clipLibrary1.cel[0].cev[391].cevr";
connectAttr "girl_FKElbow_L_scaleX.a" "clipLibrary1.cel[0].cev[392].cevr";
connectAttr "girl_FKElbow_L_rotateZ.a" "clipLibrary1.cel[0].cev[393].cevr";
connectAttr "girl_FKElbow_L_rotateY.a" "clipLibrary1.cel[0].cev[394].cevr";
connectAttr "girl_FKElbow_L_rotateX.a" "clipLibrary1.cel[0].cev[395].cevr";
connectAttr "girl_FKExtraWrist_L_rotateZ.a" "clipLibrary1.cel[0].cev[396].cevr";
connectAttr "girl_FKExtraWrist_L_rotateY.a" "clipLibrary1.cel[0].cev[397].cevr";
connectAttr "girl_FKExtraWrist_L_rotateX.a" "clipLibrary1.cel[0].cev[398].cevr";
connectAttr "girl_FKWrist_L_scaleZ.a" "clipLibrary1.cel[0].cev[399].cevr";
connectAttr "girl_FKWrist_L_scaleY.a" "clipLibrary1.cel[0].cev[400].cevr";
connectAttr "girl_FKWrist_L_scaleX.a" "clipLibrary1.cel[0].cev[401].cevr";
connectAttr "girl_FKWrist_L_rotateZ.a" "clipLibrary1.cel[0].cev[402].cevr";
connectAttr "girl_FKWrist_L_rotateY.a" "clipLibrary1.cel[0].cev[403].cevr";
connectAttr "girl_FKWrist_L_rotateX.a" "clipLibrary1.cel[0].cev[404].cevr";
connectAttr "girl_FKExtraMiddleFinger1_L_rotateZ.a" "clipLibrary1.cel[0].cev[405].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger1_L_rotateY.a" "clipLibrary1.cel[0].cev[406].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger1_L_rotateX.a" "clipLibrary1.cel[0].cev[407].cevr"
		;
connectAttr "girl_FKMiddleFinger1_L_scaleZ.a" "clipLibrary1.cel[0].cev[408].cevr"
		;
connectAttr "girl_FKMiddleFinger1_L_scaleY.a" "clipLibrary1.cel[0].cev[409].cevr"
		;
connectAttr "girl_FKMiddleFinger1_L_scaleX.a" "clipLibrary1.cel[0].cev[410].cevr"
		;
connectAttr "girl_FKMiddleFinger1_L_rotateZ.a" "clipLibrary1.cel[0].cev[411].cevr"
		;
connectAttr "girl_FKMiddleFinger1_L_rotateY.a" "clipLibrary1.cel[0].cev[412].cevr"
		;
connectAttr "girl_FKMiddleFinger1_L_rotateX.a" "clipLibrary1.cel[0].cev[413].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger2_L_rotateZ.a" "clipLibrary1.cel[0].cev[414].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger2_L_rotateY.a" "clipLibrary1.cel[0].cev[415].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger2_L_rotateX.a" "clipLibrary1.cel[0].cev[416].cevr"
		;
connectAttr "girl_FKMiddleFinger2_L_scaleZ.a" "clipLibrary1.cel[0].cev[417].cevr"
		;
connectAttr "girl_FKMiddleFinger2_L_scaleY.a" "clipLibrary1.cel[0].cev[418].cevr"
		;
connectAttr "girl_FKMiddleFinger2_L_scaleX.a" "clipLibrary1.cel[0].cev[419].cevr"
		;
connectAttr "girl_FKMiddleFinger2_L_rotateZ.a" "clipLibrary1.cel[0].cev[420].cevr"
		;
connectAttr "girl_FKMiddleFinger2_L_rotateY.a" "clipLibrary1.cel[0].cev[421].cevr"
		;
connectAttr "girl_FKMiddleFinger2_L_rotateX.a" "clipLibrary1.cel[0].cev[422].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger3_L_rotateZ.a" "clipLibrary1.cel[0].cev[423].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger3_L_rotateY.a" "clipLibrary1.cel[0].cev[424].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger3_L_rotateX.a" "clipLibrary1.cel[0].cev[425].cevr"
		;
connectAttr "girl_FKMiddleFinger3_L_scaleZ.a" "clipLibrary1.cel[0].cev[426].cevr"
		;
connectAttr "girl_FKMiddleFinger3_L_scaleY.a" "clipLibrary1.cel[0].cev[427].cevr"
		;
connectAttr "girl_FKMiddleFinger3_L_scaleX.a" "clipLibrary1.cel[0].cev[428].cevr"
		;
connectAttr "girl_FKMiddleFinger3_L_rotateZ.a" "clipLibrary1.cel[0].cev[429].cevr"
		;
connectAttr "girl_FKMiddleFinger3_L_rotateY.a" "clipLibrary1.cel[0].cev[430].cevr"
		;
connectAttr "girl_FKMiddleFinger3_L_rotateX.a" "clipLibrary1.cel[0].cev[431].cevr"
		;
connectAttr "girl_FKExtraThumbFinger1_L_rotateZ.a" "clipLibrary1.cel[0].cev[432].cevr"
		;
connectAttr "girl_FKExtraThumbFinger1_L_rotateY.a" "clipLibrary1.cel[0].cev[433].cevr"
		;
connectAttr "girl_FKExtraThumbFinger1_L_rotateX.a" "clipLibrary1.cel[0].cev[434].cevr"
		;
connectAttr "girl_FKThumbFinger1_L_scaleZ.a" "clipLibrary1.cel[0].cev[435].cevr"
		;
connectAttr "girl_FKThumbFinger1_L_scaleY.a" "clipLibrary1.cel[0].cev[436].cevr"
		;
connectAttr "girl_FKThumbFinger1_L_scaleX.a" "clipLibrary1.cel[0].cev[437].cevr"
		;
connectAttr "girl_FKThumbFinger1_L_rotateZ.a" "clipLibrary1.cel[0].cev[438].cevr"
		;
connectAttr "girl_FKThumbFinger1_L_rotateY.a" "clipLibrary1.cel[0].cev[439].cevr"
		;
connectAttr "girl_FKThumbFinger1_L_rotateX.a" "clipLibrary1.cel[0].cev[440].cevr"
		;
connectAttr "girl_FKExtraThumbFinger2_L_rotateZ.a" "clipLibrary1.cel[0].cev[441].cevr"
		;
connectAttr "girl_FKExtraThumbFinger2_L_rotateY.a" "clipLibrary1.cel[0].cev[442].cevr"
		;
connectAttr "girl_FKExtraThumbFinger2_L_rotateX.a" "clipLibrary1.cel[0].cev[443].cevr"
		;
connectAttr "girl_FKThumbFinger2_L_scaleZ.a" "clipLibrary1.cel[0].cev[444].cevr"
		;
connectAttr "girl_FKThumbFinger2_L_scaleY.a" "clipLibrary1.cel[0].cev[445].cevr"
		;
connectAttr "girl_FKThumbFinger2_L_scaleX.a" "clipLibrary1.cel[0].cev[446].cevr"
		;
connectAttr "girl_FKThumbFinger2_L_rotateZ.a" "clipLibrary1.cel[0].cev[447].cevr"
		;
connectAttr "girl_FKThumbFinger2_L_rotateY.a" "clipLibrary1.cel[0].cev[448].cevr"
		;
connectAttr "girl_FKThumbFinger2_L_rotateX.a" "clipLibrary1.cel[0].cev[449].cevr"
		;
connectAttr "girl_FKExtraThumbFinger3_L_rotateZ.a" "clipLibrary1.cel[0].cev[450].cevr"
		;
connectAttr "girl_FKExtraThumbFinger3_L_rotateY.a" "clipLibrary1.cel[0].cev[451].cevr"
		;
connectAttr "girl_FKExtraThumbFinger3_L_rotateX.a" "clipLibrary1.cel[0].cev[452].cevr"
		;
connectAttr "girl_FKThumbFinger3_L_scaleZ.a" "clipLibrary1.cel[0].cev[453].cevr"
		;
connectAttr "girl_FKThumbFinger3_L_scaleY.a" "clipLibrary1.cel[0].cev[454].cevr"
		;
connectAttr "girl_FKThumbFinger3_L_scaleX.a" "clipLibrary1.cel[0].cev[455].cevr"
		;
connectAttr "girl_FKThumbFinger3_L_rotateZ.a" "clipLibrary1.cel[0].cev[456].cevr"
		;
connectAttr "girl_FKThumbFinger3_L_rotateY.a" "clipLibrary1.cel[0].cev[457].cevr"
		;
connectAttr "girl_FKThumbFinger3_L_rotateX.a" "clipLibrary1.cel[0].cev[458].cevr"
		;
connectAttr "girl_FKExtraHip_R_rotateZ.a" "clipLibrary1.cel[0].cev[459].cevr";
connectAttr "girl_FKExtraHip_R_rotateY.a" "clipLibrary1.cel[0].cev[460].cevr";
connectAttr "girl_FKExtraHip_R_rotateX.a" "clipLibrary1.cel[0].cev[461].cevr";
connectAttr "girl_FKHip_R_scaleZ.a" "clipLibrary1.cel[0].cev[462].cevr";
connectAttr "girl_FKHip_R_scaleY.a" "clipLibrary1.cel[0].cev[463].cevr";
connectAttr "girl_FKHip_R_scaleX.a" "clipLibrary1.cel[0].cev[464].cevr";
connectAttr "girl_FKHip_R_rotateZ.a" "clipLibrary1.cel[0].cev[465].cevr";
connectAttr "girl_FKHip_R_rotateY.a" "clipLibrary1.cel[0].cev[466].cevr";
connectAttr "girl_FKHip_R_rotateX.a" "clipLibrary1.cel[0].cev[467].cevr";
connectAttr "girl_FKExtraKnee_R_rotateZ.a" "clipLibrary1.cel[0].cev[468].cevr";
connectAttr "girl_FKExtraKnee_R_rotateY.a" "clipLibrary1.cel[0].cev[469].cevr";
connectAttr "girl_FKExtraKnee_R_rotateX.a" "clipLibrary1.cel[0].cev[470].cevr";
connectAttr "girl_FKKnee_R_scaleZ.a" "clipLibrary1.cel[0].cev[471].cevr";
connectAttr "girl_FKKnee_R_scaleY.a" "clipLibrary1.cel[0].cev[472].cevr";
connectAttr "girl_FKKnee_R_scaleX.a" "clipLibrary1.cel[0].cev[473].cevr";
connectAttr "girl_FKKnee_R_rotateZ.a" "clipLibrary1.cel[0].cev[474].cevr";
connectAttr "girl_FKKnee_R_rotateY.a" "clipLibrary1.cel[0].cev[475].cevr";
connectAttr "girl_FKKnee_R_rotateX.a" "clipLibrary1.cel[0].cev[476].cevr";
connectAttr "girl_FKExtraAnkle_R_rotateZ.a" "clipLibrary1.cel[0].cev[477].cevr";
connectAttr "girl_FKExtraAnkle_R_rotateY.a" "clipLibrary1.cel[0].cev[478].cevr";
connectAttr "girl_FKExtraAnkle_R_rotateX.a" "clipLibrary1.cel[0].cev[479].cevr";
connectAttr "girl_FKAnkle_R_scaleZ.a" "clipLibrary1.cel[0].cev[480].cevr";
connectAttr "girl_FKAnkle_R_scaleY.a" "clipLibrary1.cel[0].cev[481].cevr";
connectAttr "girl_FKAnkle_R_scaleX.a" "clipLibrary1.cel[0].cev[482].cevr";
connectAttr "girl_FKAnkle_R_rotateZ.a" "clipLibrary1.cel[0].cev[483].cevr";
connectAttr "girl_FKAnkle_R_rotateY.a" "clipLibrary1.cel[0].cev[484].cevr";
connectAttr "girl_FKAnkle_R_rotateX.a" "clipLibrary1.cel[0].cev[485].cevr";
connectAttr "girl_FKExtraMiddleToe1_R_rotateZ.a" "clipLibrary1.cel[0].cev[486].cevr"
		;
connectAttr "girl_FKExtraMiddleToe1_R_rotateY.a" "clipLibrary1.cel[0].cev[487].cevr"
		;
connectAttr "girl_FKExtraMiddleToe1_R_rotateX.a" "clipLibrary1.cel[0].cev[488].cevr"
		;
connectAttr "girl_FKMiddleToe1_R_scaleZ.a" "clipLibrary1.cel[0].cev[489].cevr";
connectAttr "girl_FKMiddleToe1_R_scaleY.a" "clipLibrary1.cel[0].cev[490].cevr";
connectAttr "girl_FKMiddleToe1_R_scaleX.a" "clipLibrary1.cel[0].cev[491].cevr";
connectAttr "girl_FKMiddleToe1_R_rotateZ.a" "clipLibrary1.cel[0].cev[492].cevr";
connectAttr "girl_FKMiddleToe1_R_rotateY.a" "clipLibrary1.cel[0].cev[493].cevr";
connectAttr "girl_FKMiddleToe1_R_rotateX.a" "clipLibrary1.cel[0].cev[494].cevr";
connectAttr "girl_FKExtraBackA_M_rotateZ.a" "clipLibrary1.cel[0].cev[495].cevr";
connectAttr "girl_FKExtraBackA_M_rotateY.a" "clipLibrary1.cel[0].cev[496].cevr";
connectAttr "girl_FKExtraBackA_M_rotateX.a" "clipLibrary1.cel[0].cev[497].cevr";
connectAttr "girl_FKBackA_M_scaleZ.a" "clipLibrary1.cel[0].cev[498].cevr";
connectAttr "girl_FKBackA_M_scaleY.a" "clipLibrary1.cel[0].cev[499].cevr";
connectAttr "girl_FKBackA_M_scaleX.a" "clipLibrary1.cel[0].cev[500].cevr";
connectAttr "girl_FKBackA_M_rotateZ.a" "clipLibrary1.cel[0].cev[501].cevr";
connectAttr "girl_FKBackA_M_rotateY.a" "clipLibrary1.cel[0].cev[502].cevr";
connectAttr "girl_FKBackA_M_rotateX.a" "clipLibrary1.cel[0].cev[503].cevr";
connectAttr "girl_FKExtraBackB_M_rotateZ.a" "clipLibrary1.cel[0].cev[504].cevr";
connectAttr "girl_FKExtraBackB_M_rotateY.a" "clipLibrary1.cel[0].cev[505].cevr";
connectAttr "girl_FKExtraBackB_M_rotateX.a" "clipLibrary1.cel[0].cev[506].cevr";
connectAttr "girl_FKBackB_M_scaleZ.a" "clipLibrary1.cel[0].cev[507].cevr";
connectAttr "girl_FKBackB_M_scaleY.a" "clipLibrary1.cel[0].cev[508].cevr";
connectAttr "girl_FKBackB_M_scaleX.a" "clipLibrary1.cel[0].cev[509].cevr";
connectAttr "girl_FKBackB_M_rotateZ.a" "clipLibrary1.cel[0].cev[510].cevr";
connectAttr "girl_FKBackB_M_rotateY.a" "clipLibrary1.cel[0].cev[511].cevr";
connectAttr "girl_FKBackB_M_rotateX.a" "clipLibrary1.cel[0].cev[512].cevr";
connectAttr "girl_FKExtraChest_M_rotateZ.a" "clipLibrary1.cel[0].cev[513].cevr";
connectAttr "girl_FKExtraChest_M_rotateY.a" "clipLibrary1.cel[0].cev[514].cevr";
connectAttr "girl_FKExtraChest_M_rotateX.a" "clipLibrary1.cel[0].cev[515].cevr";
connectAttr "girl_FKChest_M_scaleZ.a" "clipLibrary1.cel[0].cev[516].cevr";
connectAttr "girl_FKChest_M_scaleY.a" "clipLibrary1.cel[0].cev[517].cevr";
connectAttr "girl_FKChest_M_scaleX.a" "clipLibrary1.cel[0].cev[518].cevr";
connectAttr "girl_FKChest_M_rotateZ.a" "clipLibrary1.cel[0].cev[519].cevr";
connectAttr "girl_FKChest_M_rotateY.a" "clipLibrary1.cel[0].cev[520].cevr";
connectAttr "girl_FKChest_M_rotateX.a" "clipLibrary1.cel[0].cev[521].cevr";
connectAttr "girl_FKExtraNeck_M_rotateZ.a" "clipLibrary1.cel[0].cev[522].cevr";
connectAttr "girl_FKExtraNeck_M_rotateY.a" "clipLibrary1.cel[0].cev[523].cevr";
connectAttr "girl_FKExtraNeck_M_rotateX.a" "clipLibrary1.cel[0].cev[524].cevr";
connectAttr "girl_FKNeck_M_scaleZ.a" "clipLibrary1.cel[0].cev[525].cevr";
connectAttr "girl_FKNeck_M_scaleY.a" "clipLibrary1.cel[0].cev[526].cevr";
connectAttr "girl_FKNeck_M_scaleX.a" "clipLibrary1.cel[0].cev[527].cevr";
connectAttr "girl_FKNeck_M_rotateZ.a" "clipLibrary1.cel[0].cev[528].cevr";
connectAttr "girl_FKNeck_M_rotateY.a" "clipLibrary1.cel[0].cev[529].cevr";
connectAttr "girl_FKNeck_M_rotateX.a" "clipLibrary1.cel[0].cev[530].cevr";
connectAttr "girl_FKExtraHead_M_rotateZ.a" "clipLibrary1.cel[0].cev[531].cevr";
connectAttr "girl_FKExtraHead_M_rotateY.a" "clipLibrary1.cel[0].cev[532].cevr";
connectAttr "girl_FKExtraHead_M_rotateX.a" "clipLibrary1.cel[0].cev[533].cevr";
connectAttr "girl_FKHead_M_scaleZ.a" "clipLibrary1.cel[0].cev[534].cevr";
connectAttr "girl_FKHead_M_scaleY.a" "clipLibrary1.cel[0].cev[535].cevr";
connectAttr "girl_FKHead_M_scaleX.a" "clipLibrary1.cel[0].cev[536].cevr";
connectAttr "girl_FKHead_M_rotateZ.a" "clipLibrary1.cel[0].cev[537].cevr";
connectAttr "girl_FKHead_M_rotateY.a" "clipLibrary1.cel[0].cev[538].cevr";
connectAttr "girl_FKHead_M_rotateX.a" "clipLibrary1.cel[0].cev[539].cevr";
connectAttr "girl_FKExtraScapula_R_scaleZ.a" "clipLibrary1.cel[0].cev[540].cevr"
		;
connectAttr "girl_FKExtraScapula_R_scaleY.a" "clipLibrary1.cel[0].cev[541].cevr"
		;
connectAttr "girl_FKExtraScapula_R_scaleX.a" "clipLibrary1.cel[0].cev[542].cevr"
		;
connectAttr "girl_FKExtraScapula_R_rotateZ.a" "clipLibrary1.cel[0].cev[543].cevr"
		;
connectAttr "girl_FKExtraScapula_R_rotateY.a" "clipLibrary1.cel[0].cev[544].cevr"
		;
connectAttr "girl_FKExtraScapula_R_rotateX.a" "clipLibrary1.cel[0].cev[545].cevr"
		;
connectAttr "girl_FKExtraScapula_R_translateZ.a" "clipLibrary1.cel[0].cev[546].cevr"
		;
connectAttr "girl_FKExtraScapula_R_translateY.a" "clipLibrary1.cel[0].cev[547].cevr"
		;
connectAttr "girl_FKExtraScapula_R_translateX.a" "clipLibrary1.cel[0].cev[548].cevr"
		;
connectAttr "girl_FKScapula_R_scaleZ.a" "clipLibrary1.cel[0].cev[549].cevr";
connectAttr "girl_FKScapula_R_scaleY.a" "clipLibrary1.cel[0].cev[550].cevr";
connectAttr "girl_FKScapula_R_scaleX.a" "clipLibrary1.cel[0].cev[551].cevr";
connectAttr "girl_FKScapula_R_rotateZ.a" "clipLibrary1.cel[0].cev[552].cevr";
connectAttr "girl_FKScapula_R_rotateY.a" "clipLibrary1.cel[0].cev[553].cevr";
connectAttr "girl_FKScapula_R_rotateX.a" "clipLibrary1.cel[0].cev[554].cevr";
connectAttr "girl_FKScapula_R_translateZ.a" "clipLibrary1.cel[0].cev[555].cevr";
connectAttr "girl_FKScapula_R_translateY.a" "clipLibrary1.cel[0].cev[556].cevr";
connectAttr "girl_FKScapula_R_translateX.a" "clipLibrary1.cel[0].cev[557].cevr";
connectAttr "girl_FKExtraShoulder_R_rotateZ.a" "clipLibrary1.cel[0].cev[558].cevr"
		;
connectAttr "girl_FKExtraShoulder_R_rotateY.a" "clipLibrary1.cel[0].cev[559].cevr"
		;
connectAttr "girl_FKExtraShoulder_R_rotateX.a" "clipLibrary1.cel[0].cev[560].cevr"
		;
connectAttr "girl_FKShoulder_R_scaleZ.a" "clipLibrary1.cel[0].cev[561].cevr";
connectAttr "girl_FKShoulder_R_scaleY.a" "clipLibrary1.cel[0].cev[562].cevr";
connectAttr "girl_FKShoulder_R_scaleX.a" "clipLibrary1.cel[0].cev[563].cevr";
connectAttr "girl_FKShoulder_R_rotateZ.a" "clipLibrary1.cel[0].cev[564].cevr";
connectAttr "girl_FKShoulder_R_rotateY.a" "clipLibrary1.cel[0].cev[565].cevr";
connectAttr "girl_FKShoulder_R_rotateX.a" "clipLibrary1.cel[0].cev[566].cevr";
connectAttr "girl_FKExtraElbow_R_rotateZ.a" "clipLibrary1.cel[0].cev[567].cevr";
connectAttr "girl_FKExtraElbow_R_rotateY.a" "clipLibrary1.cel[0].cev[568].cevr";
connectAttr "girl_FKExtraElbow_R_rotateX.a" "clipLibrary1.cel[0].cev[569].cevr";
connectAttr "girl_FKElbow_R_scaleZ.a" "clipLibrary1.cel[0].cev[570].cevr";
connectAttr "girl_FKElbow_R_scaleY.a" "clipLibrary1.cel[0].cev[571].cevr";
connectAttr "girl_FKElbow_R_scaleX.a" "clipLibrary1.cel[0].cev[572].cevr";
connectAttr "girl_FKElbow_R_rotateZ.a" "clipLibrary1.cel[0].cev[573].cevr";
connectAttr "girl_FKElbow_R_rotateY.a" "clipLibrary1.cel[0].cev[574].cevr";
connectAttr "girl_FKElbow_R_rotateX.a" "clipLibrary1.cel[0].cev[575].cevr";
connectAttr "girl_FKExtraWrist_R_rotateZ.a" "clipLibrary1.cel[0].cev[576].cevr";
connectAttr "girl_FKExtraWrist_R_rotateY.a" "clipLibrary1.cel[0].cev[577].cevr";
connectAttr "girl_FKExtraWrist_R_rotateX.a" "clipLibrary1.cel[0].cev[578].cevr";
connectAttr "girl_FKWrist_R_scaleZ.a" "clipLibrary1.cel[0].cev[579].cevr";
connectAttr "girl_FKWrist_R_scaleY.a" "clipLibrary1.cel[0].cev[580].cevr";
connectAttr "girl_FKWrist_R_scaleX.a" "clipLibrary1.cel[0].cev[581].cevr";
connectAttr "girl_FKWrist_R_rotateZ.a" "clipLibrary1.cel[0].cev[582].cevr";
connectAttr "girl_FKWrist_R_rotateY.a" "clipLibrary1.cel[0].cev[583].cevr";
connectAttr "girl_FKWrist_R_rotateX.a" "clipLibrary1.cel[0].cev[584].cevr";
connectAttr "girl_FKExtraMiddleFinger1_R_rotateZ.a" "clipLibrary1.cel[0].cev[585].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger1_R_rotateY.a" "clipLibrary1.cel[0].cev[586].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger1_R_rotateX.a" "clipLibrary1.cel[0].cev[587].cevr"
		;
connectAttr "girl_FKMiddleFinger1_R_scaleZ.a" "clipLibrary1.cel[0].cev[588].cevr"
		;
connectAttr "girl_FKMiddleFinger1_R_scaleY.a" "clipLibrary1.cel[0].cev[589].cevr"
		;
connectAttr "girl_FKMiddleFinger1_R_scaleX.a" "clipLibrary1.cel[0].cev[590].cevr"
		;
connectAttr "girl_FKMiddleFinger1_R_rotateZ.a" "clipLibrary1.cel[0].cev[591].cevr"
		;
connectAttr "girl_FKMiddleFinger1_R_rotateY.a" "clipLibrary1.cel[0].cev[592].cevr"
		;
connectAttr "girl_FKMiddleFinger1_R_rotateX.a" "clipLibrary1.cel[0].cev[593].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger2_R_rotateZ.a" "clipLibrary1.cel[0].cev[594].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger2_R_rotateY.a" "clipLibrary1.cel[0].cev[595].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger2_R_rotateX.a" "clipLibrary1.cel[0].cev[596].cevr"
		;
connectAttr "girl_FKMiddleFinger2_R_scaleZ.a" "clipLibrary1.cel[0].cev[597].cevr"
		;
connectAttr "girl_FKMiddleFinger2_R_scaleY.a" "clipLibrary1.cel[0].cev[598].cevr"
		;
connectAttr "girl_FKMiddleFinger2_R_scaleX.a" "clipLibrary1.cel[0].cev[599].cevr"
		;
connectAttr "girl_FKMiddleFinger2_R_rotateZ.a" "clipLibrary1.cel[0].cev[600].cevr"
		;
connectAttr "girl_FKMiddleFinger2_R_rotateY.a" "clipLibrary1.cel[0].cev[601].cevr"
		;
connectAttr "girl_FKMiddleFinger2_R_rotateX.a" "clipLibrary1.cel[0].cev[602].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger3_R_rotateZ.a" "clipLibrary1.cel[0].cev[603].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger3_R_rotateY.a" "clipLibrary1.cel[0].cev[604].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger3_R_rotateX.a" "clipLibrary1.cel[0].cev[605].cevr"
		;
connectAttr "girl_FKMiddleFinger3_R_scaleZ.a" "clipLibrary1.cel[0].cev[606].cevr"
		;
connectAttr "girl_FKMiddleFinger3_R_scaleY.a" "clipLibrary1.cel[0].cev[607].cevr"
		;
connectAttr "girl_FKMiddleFinger3_R_scaleX.a" "clipLibrary1.cel[0].cev[608].cevr"
		;
connectAttr "girl_FKMiddleFinger3_R_rotateZ.a" "clipLibrary1.cel[0].cev[609].cevr"
		;
connectAttr "girl_FKMiddleFinger3_R_rotateY.a" "clipLibrary1.cel[0].cev[610].cevr"
		;
connectAttr "girl_FKMiddleFinger3_R_rotateX.a" "clipLibrary1.cel[0].cev[611].cevr"
		;
connectAttr "girl_FKExtraThumbFinger1_R_rotateZ.a" "clipLibrary1.cel[0].cev[612].cevr"
		;
connectAttr "girl_FKExtraThumbFinger1_R_rotateY.a" "clipLibrary1.cel[0].cev[613].cevr"
		;
connectAttr "girl_FKExtraThumbFinger1_R_rotateX.a" "clipLibrary1.cel[0].cev[614].cevr"
		;
connectAttr "girl_FKThumbFinger1_R_scaleZ.a" "clipLibrary1.cel[0].cev[615].cevr"
		;
connectAttr "girl_FKThumbFinger1_R_scaleY.a" "clipLibrary1.cel[0].cev[616].cevr"
		;
connectAttr "girl_FKThumbFinger1_R_scaleX.a" "clipLibrary1.cel[0].cev[617].cevr"
		;
connectAttr "girl_FKThumbFinger1_R_rotateZ.a" "clipLibrary1.cel[0].cev[618].cevr"
		;
connectAttr "girl_FKThumbFinger1_R_rotateY.a" "clipLibrary1.cel[0].cev[619].cevr"
		;
connectAttr "girl_FKThumbFinger1_R_rotateX.a" "clipLibrary1.cel[0].cev[620].cevr"
		;
connectAttr "girl_FKExtraThumbFinger2_R_rotateZ.a" "clipLibrary1.cel[0].cev[621].cevr"
		;
connectAttr "girl_FKExtraThumbFinger2_R_rotateY.a" "clipLibrary1.cel[0].cev[622].cevr"
		;
connectAttr "girl_FKExtraThumbFinger2_R_rotateX.a" "clipLibrary1.cel[0].cev[623].cevr"
		;
connectAttr "girl_FKThumbFinger2_R_scaleZ.a" "clipLibrary1.cel[0].cev[624].cevr"
		;
connectAttr "girl_FKThumbFinger2_R_scaleY.a" "clipLibrary1.cel[0].cev[625].cevr"
		;
connectAttr "girl_FKThumbFinger2_R_scaleX.a" "clipLibrary1.cel[0].cev[626].cevr"
		;
connectAttr "girl_FKThumbFinger2_R_rotateZ.a" "clipLibrary1.cel[0].cev[627].cevr"
		;
connectAttr "girl_FKThumbFinger2_R_rotateY.a" "clipLibrary1.cel[0].cev[628].cevr"
		;
connectAttr "girl_FKThumbFinger2_R_rotateX.a" "clipLibrary1.cel[0].cev[629].cevr"
		;
connectAttr "girl_FKExtraThumbFinger3_R_rotateZ.a" "clipLibrary1.cel[0].cev[630].cevr"
		;
connectAttr "girl_FKExtraThumbFinger3_R_rotateY.a" "clipLibrary1.cel[0].cev[631].cevr"
		;
connectAttr "girl_FKExtraThumbFinger3_R_rotateX.a" "clipLibrary1.cel[0].cev[632].cevr"
		;
connectAttr "girl_FKThumbFinger3_R_scaleZ.a" "clipLibrary1.cel[0].cev[633].cevr"
		;
connectAttr "girl_FKThumbFinger3_R_scaleY.a" "clipLibrary1.cel[0].cev[634].cevr"
		;
connectAttr "girl_FKThumbFinger3_R_scaleX.a" "clipLibrary1.cel[0].cev[635].cevr"
		;
connectAttr "girl_FKThumbFinger3_R_rotateZ.a" "clipLibrary1.cel[0].cev[636].cevr"
		;
connectAttr "girl_FKThumbFinger3_R_rotateY.a" "clipLibrary1.cel[0].cev[637].cevr"
		;
connectAttr "girl_FKThumbFinger3_R_rotateX.a" "clipLibrary1.cel[0].cev[638].cevr"
		;
connectAttr "girl_Group_scaleZ.a" "clipLibrary1.cel[0].cev[639].cevr";
connectAttr "girl_Group_scaleY.a" "clipLibrary1.cel[0].cev[640].cevr";
connectAttr "girl_Group_scaleX.a" "clipLibrary1.cel[0].cev[641].cevr";
connectAttr "girl_Group_rotateZ.a" "clipLibrary1.cel[0].cev[642].cevr";
connectAttr "girl_Group_rotateY.a" "clipLibrary1.cel[0].cev[643].cevr";
connectAttr "girl_Group_rotateX.a" "clipLibrary1.cel[0].cev[644].cevr";
connectAttr "girl_Group_translateZ.a" "clipLibrary1.cel[0].cev[645].cevr";
connectAttr "girl_Group_translateY.a" "clipLibrary1.cel[0].cev[646].cevr";
connectAttr "girl_Group_translateX.a" "clipLibrary1.cel[0].cev[647].cevr";
connectAttr "girl_Group_visibility.a" "clipLibrary1.cel[0].cev[648].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of Minigame2_fail.ma
