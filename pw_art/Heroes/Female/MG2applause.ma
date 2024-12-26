//Maya ASCII 2008 scene
//Name: Minigame2_applause.ma
//Last modified: Thu, Nov 26, 2009 03:09:32 PM
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
createNode animClip -n "Minigame2_applauseSource";
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
	setAttr ".se" 96;
	setAttr ".ci" no;
createNode animCurveTA -n "back_skirt_b_CTRL_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -35.107866749865821 96 -35.107866749865821;
createNode animCurveTA -n "back_skirt_b_CTRL_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "back_skirt_b_CTRL_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_angularValues_4_2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_angularValues_5_2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_angularValues_6_2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_R_cloak_C_CTRL_rotateZ2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_R_cloak_C_CTRL_rotateY2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_R_cloak_C_CTRL_rotateX2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_R_cloak_B_CTRL_rotateZ2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_R_cloak_B_CTRL_rotateY2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_R_cloak_B_CTRL_rotateX2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_R_cloak_A_CTRL_rotateZ2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_R_cloak_A_CTRL_rotateY2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_R_cloak_A_CTRL_rotateX2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_L_cloak_C_CTRL_rotateZ2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_L_cloak_C_CTRL_rotateY2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_L_cloak_C_CTRL_rotateX2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_L_cloak_B_CTRL_rotateZ2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_L_cloak_B_CTRL_rotateY2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_L_cloak_B_CTRL_rotateX2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_L_cloak_A_CTRL_rotateZ2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_L_cloak_A_CTRL_rotateY2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_L_cloak_A_CTRL_rotateX2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_cloak_D_CTRL_rotateZ2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_cloak_D_CTRL_rotateY2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_cloak_D_CTRL_rotateX2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_cloak_C_CTRL_rotateZ2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_cloak_C_CTRL_rotateY2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_cloak_C_CTRL_rotateX2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_cloak_B_CTRL_rotateZ2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_cloak_B_CTRL_rotateY2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_cloak_B_CTRL_rotateX2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_cloak_A_CTRL_rotateZ2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_cloak_A_CTRL_rotateY2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_cloak_A_CTRL_rotateX2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_angularValues_37_2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_angularValues_38_2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_angularValues_39_2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "back_skirt_b_CTRL_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "back_skirt_b_CTRL_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "back_skirt_b_CTRL_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_angularValues_40_2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_angularValues_41_2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_angularValues_42_2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_linearValues_4_2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_linearValues_5_2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_linearValues_6_2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_back_skirt_b_CTRL_rotateZ2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_back_skirt_b_CTRL_rotateY2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_back_skirt_b_CTRL_rotateX2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_back_skirt_b_CTRL_translateZ2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_back_skirt_b_CTRL_translateY2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_back_skirt_b_CTRL_translateX2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_back_skirt_a_CTRL_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 2.6938795237463498 96 2.6938795237463498;
createNode animCurveTA -n "girl_back_skirt_a_CTRL_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -12.342679124221798 96 -12.342679124221798;
createNode animCurveTA -n "girl_back_skirt_a_CTRL_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 7.3397129639479664 96 7.3397129639479664;
createNode animCurveTL -n "girl_back_skirt_a_CTRL_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.1506711017189028 96 -0.1506711017189028;
createNode animCurveTL -n "girl_back_skirt_a_CTRL_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.3878246215110126 96 0.3878246215110126;
createNode animCurveTL -n "girl_back_skirt_a_CTRL_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.19170657084941162 96 -0.19170657084941162;
createNode animCurveTA -n "girl_front_skirt_b_CTRL_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 20.536714960000001 96 20.536714960000001;
createNode animCurveTA -n "girl_front_skirt_b_CTRL_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.68059892 96 1.68059892;
createNode animCurveTA -n "girl_front_skirt_b_CTRL_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 2.246740264 96 2.246740264;
createNode animCurveTL -n "girl_front_skirt_b_CTRL_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_front_skirt_b_CTRL_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_front_skirt_b_CTRL_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_front_skirt_a_CTRL_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.96208267020000005 96 0.96208267020000005;
createNode animCurveTA -n "girl_front_skirt_a_CTRL_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_front_skirt_a_CTRL_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_front_skirt_a_CTRL_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.089153431075066639 96 0.089153431075066639;
createNode animCurveTL -n "girl_front_skirt_a_CTRL_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.20970195830660243 96 -0.20970195830660243;
createNode animCurveTL -n "girl_front_skirt_a_CTRL_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.0068805126335673514 96 -0.0068805126335673514;
createNode animCurveTA -n "girl_skirt_HipA_L_CTRL_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_skirt_HipA_L_CTRL_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_skirt_HipA_L_CTRL_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_skirt_HipA_L_CTRL_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_skirt_HipA_L_CTRL_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_skirt_HipA_L_CTRL_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_skirt_Hip_L_CTRL_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_skirt_Hip_L_CTRL_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_skirt_Hip_L_CTRL_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_skirt_Hip_L_CTRL_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.01408065876666875 96 0.01408065876666875;
createNode animCurveTL -n "girl_skirt_Hip_L_CTRL_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.0059453893140569321 96 -0.0059453893140569321;
createNode animCurveTL -n "girl_skirt_Hip_L_CTRL_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.0013409990355031896 96 0.0013409990355031896;
createNode animCurveTA -n "girl_skirt_HipA_R_CTRL_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 6.6401439609999997 96 6.6401439609999997;
createNode animCurveTA -n "girl_skirt_HipA_R_CTRL_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -10.419421379999999 96 -10.419421379999999;
createNode animCurveTA -n "girl_skirt_HipA_R_CTRL_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -3.6296225309999994 96 -3.6296225309999994;
createNode animCurveTL -n "girl_skirt_HipA_R_CTRL_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_skirt_HipA_R_CTRL_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_skirt_HipA_R_CTRL_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_skirt_Hip_R_CTRL_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.059443428020000008 96 -0.059443428020000008;
createNode animCurveTA -n "girl_skirt_Hip_R_CTRL_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.12010888460000001 96 -0.12010888460000001;
createNode animCurveTA -n "girl_skirt_Hip_R_CTRL_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.58331804030000001 96 0.58331804030000001;
createNode animCurveTL -n "girl_skirt_Hip_R_CTRL_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.028480309728328882 96 -0.028480309728328882;
createNode animCurveTL -n "girl_skirt_Hip_R_CTRL_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.0036166365236135014 96 0.0036166365236135014;
createNode animCurveTL -n "girl_skirt_Hip_R_CTRL_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.0362163539759899 96 -0.0362163539759899;
createNode animCurveTU -n "girl_Center_M_CenterBtwFeet1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_Center_M_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -38.239471219814469 90 -38.239471219814469 
		96 -38.239471219814469;
createNode animCurveTA -n "girl_Center_M_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 90 0 96 0;
createNode animCurveTA -n "girl_Center_M_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 17 ".ktv[0:16]"  0 7.8960619584932568 6 5.1043377927176774 
		12 3.2703170725530621 18 2.8331795305818086 24 3.446286866248339 30 5.1108114688478485 
		36 7.1574997734179062 42 9.0742619398950506 48 10.726753852985309 54 11.94208320734967 
		60 12.422243979601568 66 11.798265676116742 72 10.142382036149904 78 7.7730662054629649 
		84 6.476727835940058 90 6.8640854226229102 96 7.8960619584932568;
	setAttr -s 17 ".kit[1:16]"  1 9 9 9 1 9 9 9 
		9 9 9 9 1 1 1 3;
	setAttr -s 17 ".kot[1:16]"  1 9 9 9 1 9 9 9 
		9 9 9 9 1 1 1 3;
	setAttr -s 17 ".kix[1:16]"  0.97908037900924683 0.99512571096420288 
		0.99997055530548096 0.9950980544090271 0.98478865623474121 0.98537349700927734 0.98808902502059937 
		0.99226164817810059 0.99727469682693481 0.99998033046722412 0.99508851766586304 0.98492449522018433 
		0.9810059666633606 0.99971538782119751 0.99532580375671387 1;
	setAttr -s 17 ".kiy[1:16]"  -0.20347392559051514 -0.098614931106567383 
		0.0076779047958552837 0.098893292248249054 0.17375676333904266 0.170408695936203 
		0.15388309955596924 0.12416400760412216 0.073778100311756134 -0.0062750987708568573 
		-0.098989136517047882 -0.172984778881073 -0.19397753477096558 -0.023856755346059799 
		0.096574120223522186 0;
	setAttr -s 17 ".kox[1:16]"  0.97908037900924683 0.99512571096420288 
		0.99997055530548096 0.9950980544090271 0.98478865623474121 0.98537349700927734 0.98808902502059937 
		0.99226164817810059 0.99727469682693481 0.99998033046722412 0.99508851766586304 0.98492449522018433 
		0.98100602626800537 0.99971538782119751 0.99532586336135864 1;
	setAttr -s 17 ".koy[1:16]"  -0.20347392559051514 -0.098614931106567383 
		0.0076779047958552837 0.098893292248249054 0.17375676333904266 0.170408695936203 
		0.15388309955596924 0.12416400760412216 0.073778100311756134 -0.0062750987708568573 
		-0.098989136517047882 -0.172984778881073 -0.19397749006748199 -0.023856742307543755 
		0.096574097871780396 0;
createNode animCurveTL -n "girl_Center_M_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.68530052330451496 90 -0.68530052330451496 
		96 -0.68530052330451496;
createNode animCurveTL -n "girl_Center_M_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.65142083148962104 90 -0.65142083148962104 
		96 -0.65142083148962104;
createNode animCurveTL -n "girl_Center_M_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.52813520669109548 90 0.52813520669109548 
		96 0.52813520669109548;
createNode animCurveTA -n "girl_CenterExtra_M_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_CenterExtra_M_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_CenterExtra_M_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_CenterExtra_M_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_CenterExtra_M_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_CenterExtra_M_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_Fingers_L_Cup1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_Fingers_L_Spread1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_Fingers_L_ThumbFingerCurl1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_Fingers_L_PinkyFingerCurl1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_Fingers_L_RingFingerCurl1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_Fingers_L_MiddleFingerCurl1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_Fingers_L_IndexFingerCurl1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraLegBall_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraLegBall_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraLegBall_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKLegBall_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraLegToe_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraLegToe_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraLegToe_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKLegToe_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKLegToe_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKLegToe_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraLegHeel_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraLegHeel_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraLegHeel_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKLegHeel_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKLegHeel_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKLegHeel_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKIKLeg_L_IKVis1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
	setAttr -s 2 ".kot[0:1]"  5 5;
createNode animCurveTU -n "girl_FKIKLeg_L_FKVis1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
	setAttr -s 2 ".kot[0:1]"  5 5;
createNode animCurveTU -n "girl_FKIKLeg_L_FKIKBlend1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_PoleExtraLeg_L_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_PoleExtraLeg_L_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_PoleExtraLeg_L_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_PoleLeg_L_follow1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 10 96 10;
createNode animCurveTL -n "girl_PoleLeg_L_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_PoleLeg_L_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_PoleLeg_L_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraLeg_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraLeg_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraLeg_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKExtraLeg_L_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKExtraLeg_L_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKExtraLeg_L_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_IKLeg_L_Lenght4";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_IKLeg_L_Lenght3";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_IKLeg_L_antiPop1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_IKLeg_L_stretchy1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_IKLeg_L_rollAngle1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 25 96 25;
createNode animCurveTU -n "girl_IKLeg_L_roll1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_IKLeg_L_toe1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_IKLeg_L_swivel1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKLeg_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKLeg_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKLeg_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKLeg_L_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKLeg_L_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKLeg_L_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKIKArm_L_IKVis1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
	setAttr -s 2 ".kot[0:1]"  5 5;
createNode animCurveTU -n "girl_FKIKArm_L_FKVis1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
	setAttr -s 2 ".kot[0:1]"  5 5;
createNode animCurveTU -n "girl_FKIKArm_L_FKIKBlend1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 10 96 10;
createNode animCurveTL -n "girl_PoleExtraArm_L_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_PoleExtraArm_L_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_PoleExtraArm_L_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_PoleArm_L_follow1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_PoleArm_L_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 18 -1.1639004767215504 66 -0.92268749848966669 
		96 0;
createNode animCurveTL -n "girl_PoleArm_L_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 18 -1.2787190258702614 66 -1.6083290678125437 
		96 0;
createNode animCurveTL -n "girl_PoleArm_L_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 18 0.51360986941372511 66 0.31070413209069314 
		96 0;
createNode animCurveTA -n "girl_IKExtraArm_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraArm_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraArm_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKExtraArm_L_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKExtraArm_L_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKExtraArm_L_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_IKArm_L_Lenght4";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_IKArm_L_Lenght3";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_IKArm_L_antiPop1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_IKArm_L_stretchy1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_IKArm_L_follow1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKArm_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 -64.016327 12 -102.4887052626936 18 -218.32749618166818 
		24 -207.94301912336468 30 -209.01924701904341 36 -209.58381244186003 42 -212.59996252877781 
		48 -213.74058130896199 54 -217.0736815417545 60 -218.79346341452128 66 -207.94301912336468 
		72 -135.43158156944213 78 -98.686441644867458 84 -75.51007479587058 90 -64.016327 
		96 -64.016327;
createNode animCurveTA -n "girl_IKArm_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 -21.201885600000001 12 47.177781882020057 
		18 60.006352871064529 24 34.336234075298876 30 34.037900310977115 36 31.267870070867733 
		42 33.87243442226422 48 31.371236521566697 54 32.443089898537878 60 31.102184691827386 
		66 34.336234075298876 72 41.81061620986253 78 28.775396132653022 84 -10.550350563946337 
		90 -21.201885600000001 96 -21.201885600000001;
createNode animCurveTA -n "girl_IKArm_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 23.577065820000001 12 13.079223474036754 
		18 138.76259748338714 24 147.36645498056302 30 155.13951283457527 36 150.10002727124072 
		42 158.28939312725367 48 153.68064879810834 54 159.14148037760063 60 157.62293622807815 
		66 147.36645498056302 72 59.782511666056003 78 37.263871127423521 84 22.466356768921191 
		90 23.577065820000001 96 23.577065820000001;
createNode animCurveTL -n "girl_IKArm_L_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 17 ".ktv[0:16]"  0 -1.114764949 6 -1.0550335056815836 12 
		-0.83544871388512876 18 -0.5517795275826376 24 -0.42333621304710434 30 -0.42944643596845061 
		36 -0.40425751072385957 42 -0.43829411252032235 48 -0.37880208435844209 54 -0.39384446709825155 
		60 -0.35295787949839291 66 -0.38615323100342414 72 -0.61408242116709078 78 -0.98990484393889355 
		84 -1.1072071298695541 90 -1.114764949 96 -1.114764949;
	setAttr -s 17 ".kit[4:16]"  3 9 9 9 9 9 9 3 
		9 9 9 9 9;
	setAttr -s 17 ".kot[4:16]"  3 9 9 9 9 9 9 3 
		9 9 9 9 9;
createNode animCurveTL -n "girl_IKArm_L_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 17 ".ktv[0:16]"  0 -0.78014303230000004 6 -0.88544800970013582 
		12 -1.0306926860705345 18 -1.305190497799217 24 -1.348490994275783 30 -1.3528887296398122 
		36 -1.3622287122889907 42 -1.3805715710859718 48 -1.3871767796356893 54 -1.4005893777293072 
		60 -1.4092796567702126 66 -1.4125143870879977 72 -1.2755863911189953 78 -0.99734934210308501 
		84 -0.78725283162609705 90 -0.78014303230000004 96 -0.78014303230000004;
	setAttr -s 17 ".kit[4:16]"  3 9 9 9 9 9 9 3 
		9 9 9 9 9;
	setAttr -s 17 ".kot[4:16]"  3 9 9 9 9 9 9 3 
		9 9 9 9 9;
createNode animCurveTL -n "girl_IKArm_L_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 17 ".ktv[0:16]"  0 -0.21085409329999999 6 -0.21947294886827245 
		12 -0.27028815514996846 18 -0.45450270559051376 24 -0.57257284303799649 30 -0.57084083846614186 
		36 -0.57814229626240876 42 -0.57330758733590181 48 -0.58636081895949166 54 -0.58674422658149716 
		60 -0.59451254589375091 66 -0.57919408482291435 72 -0.39961913453239017 78 -0.25857141239529524 
		84 -0.16967910737992431 90 -0.21085409329999999 96 -0.21085409329999999;
	setAttr -s 17 ".kit[4:16]"  3 9 9 9 9 9 9 3 
		9 9 9 9 9;
	setAttr -s 17 ".kot[4:16]"  3 9 9 9 9 9 9 3 
		9 9 9 9 9;
createNode animCurveTU -n "girl_Fingers_R_Cup1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_Fingers_R_Spread1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_Fingers_R_ThumbFingerCurl1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_Fingers_R_PinkyFingerCurl1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_Fingers_R_RingFingerCurl1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_Fingers_R_MiddleFingerCurl1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_Fingers_R_IndexFingerCurl1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_IKExtraSpine4_M_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_IKExtraSpine4_M_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_IKExtraSpine4_M_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTA -n "girl_IKExtraSpine4_M_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraSpine4_M_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraSpine4_M_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKExtraSpine4_M_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKExtraSpine4_M_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKExtraSpine4_M_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_IKExtraSpine4_M_visibility1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
	setAttr -s 2 ".kot[0:1]"  5 5;
createNode animCurveTU -n "girl_IKSpine4_M_stretchy1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 10 96 10;
createNode animCurveTU -n "girl_IKSpine4_M_stiff1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKSpine4_M_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKSpine4_M_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKSpine4_M_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKSpine4_M_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKSpine4_M_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKSpine4_M_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_IKExtraSpine2_M_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_IKExtraSpine2_M_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_IKExtraSpine2_M_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTA -n "girl_IKExtraSpine2_M_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraSpine2_M_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraSpine2_M_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKExtraSpine2_M_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKExtraSpine2_M_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKExtraSpine2_M_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_IKExtraSpine2_M_visibility1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
	setAttr -s 2 ".kot[0:1]"  5 5;
createNode animCurveTU -n "girl_IKSpine2_M_stiff1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKSpine2_M_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKSpine2_M_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKSpine2_M_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKSpine2_M_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKSpine2_M_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKSpine2_M_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_IKExtraSpine0_M_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_IKExtraSpine0_M_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_IKExtraSpine0_M_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTA -n "girl_IKExtraSpine0_M_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraSpine0_M_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraSpine0_M_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKExtraSpine0_M_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKExtraSpine0_M_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKExtraSpine0_M_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_IKExtraSpine0_M_visibility1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
	setAttr -s 2 ".kot[0:1]"  5 5;
createNode animCurveTU -n "girl_IKSpine0_M_stiff1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKSpine0_M_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKSpine0_M_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKSpine0_M_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKSpine0_M_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKSpine0_M_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKSpine0_M_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraLegBall_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraLegBall_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraLegBall_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKLegBall_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraLegToe_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraLegToe_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraLegToe_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKLegToe_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKLegToe_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKLegToe_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraLegHeel_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraLegHeel_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraLegHeel_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKLegHeel_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKLegHeel_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKLegHeel_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKIKLeg_R_IKVis1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
	setAttr -s 2 ".kot[0:1]"  5 5;
createNode animCurveTU -n "girl_FKIKLeg_R_FKVis1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
	setAttr -s 2 ".kot[0:1]"  5 5;
createNode animCurveTU -n "girl_FKIKLeg_R_FKIKBlend1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_PoleExtraLeg_R_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_PoleExtraLeg_R_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_PoleExtraLeg_R_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_PoleLeg_R_follow1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 10 96 10;
createNode animCurveTL -n "girl_PoleLeg_R_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_PoleLeg_R_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_PoleLeg_R_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraLeg_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraLeg_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraLeg_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKExtraLeg_R_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKExtraLeg_R_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKExtraLeg_R_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_IKLeg_R_Lenght4";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_IKLeg_R_Lenght3";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_IKLeg_R_antiPop1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_IKLeg_R_stretchy1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_IKLeg_R_rollAngle1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 25 96 25;
createNode animCurveTU -n "girl_IKLeg_R_roll1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_IKLeg_R_toe1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_IKLeg_R_swivel1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKLeg_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKLeg_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKLeg_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKLeg_R_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKLeg_R_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKLeg_R_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKIKArm_R_IKVis1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
	setAttr -s 2 ".kot[0:1]"  5 5;
createNode animCurveTU -n "girl_FKIKArm_R_FKVis1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
	setAttr -s 2 ".kot[0:1]"  5 5;
createNode animCurveTU -n "girl_FKIKArm_R_FKIKBlend1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 10 96 10;
createNode animCurveTL -n "girl_PoleExtraArm_R_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_PoleExtraArm_R_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_PoleExtraArm_R_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_PoleArm_R_follow1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_PoleArm_R_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -1.8324655288625988 18 -1.5691254836649049 
		24 -1.6253066961003373 96 -1.8324655288625988;
createNode animCurveTL -n "girl_PoleArm_R_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -1.5248853769364021 18 -1.3817505311990448 
		24 -1.4510208664800019 96 -1.5248853769364021;
createNode animCurveTL -n "girl_PoleArm_R_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.72634564248961153 18 0.21471597918739083 
		24 0.14193416341327103 96 0.72634564248961153;
createNode animCurveTA -n "girl_IKExtraArm_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraArm_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKExtraArm_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKExtraArm_R_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKExtraArm_R_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_IKExtraArm_R_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_IKArm_R_Lenght4";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_IKArm_R_Lenght3";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_IKArm_R_antiPop1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_IKArm_R_stretchy1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_IKArm_R_follow1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_IKArm_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 26 ".ktv[0:25]"  0 74.385551550000002 12 83.071330538481419 
		18 83.561433602638843 24 94.548425418299104 27 93.685222290206525 30 89.231591918760785 
		33 86.527347146967259 38 91.170046310343267 40 93.82502156360718 42 93.829516643134397 
		45 90.513832816131128 48 91.6783695442859 50 93.606644131263508 52 96.625407890149148 
		54 97.549819429381486 56 95.164894677536225 58 92.742894516603414 60 93.920057602715616 
		62 95.839298567936723 64 99.449934670934482 66 100.65148874015918 72 91.044101786918318 
		78 92.972371565158497 84 66.672486518099731 90 65.471592204538624 96 74.385551550000002;
createNode animCurveTA -n "girl_IKArm_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 26 ".ktv[0:25]"  0 18.642817839999999 12 -4.3613599373824394 
		18 -6.513709141652452 24 -15.616648431325915 27 -12.483531964329973 30 -11.255377709657189 
		33 -9.1477927979825662 38 -6.7919275857959196 40 -5.3854449673348332 42 -5.4882527111478234 
		45 -7.7965346696602609 48 -9.7036394447042369 50 -8.9343042134388515 52 -6.6866742160629533 
		54 -6.2643368446388576 56 -8.6992330588823616 58 -10.504325640157598 60 -11.516123117096011 
		62 -11.137356144064103 64 -9.3082105090528859 66 -12.29867393142742 72 -42.431775536299092 
		78 -26.558923326863734 84 21.974254342738195 90 19.88660674860327 96 18.642817839999999;
createNode animCurveTA -n "girl_IKArm_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 26 ".ktv[0:25]"  0 2.8749941739999998 12 -5.9809041312581837 
		18 -52.811291412089467 24 -47.415890429126506 27 -29.783549852434696 30 -21.206565159434515 
		33 -43.036658369057299 38 -33.821879607361481 40 -22.521584852096588 42 -32.943282087036934 
		45 -56.146146749236372 48 -52.155119127982218 50 -44.837686233681829 52 -28.132821769231946 
		54 -26.636795942294317 56 -46.431321333769432 58 -63.032025906716719 60 -57.905385570648768 
		62 -49.712291160266957 64 -31.610283703130488 66 -23.272042214174093 72 -20.829036100974172 
		78 -0.33705048716848607 84 -34.620616065827754 90 -9.6797360450162717 96 2.8749941739999998;
createNode animCurveTL -n "girl_IKArm_R_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 17 ".ktv[0:16]"  0 -0.79868788219999998 6 -0.66953581508410032 
		12 -0.5349504623312239 18 -0.40974503189216971 24 -0.47968032318978737 30 -0.35898489596597455 
		36 -0.46827815619997576 42 -0.32785751218000436 48 -0.45072966154911098 54 -0.32317953444430181 
		60 -0.43808881373210851 66 -0.34102008221582769 72 -0.43446511377298858 78 -0.45022015673630389 
		84 -0.6795339367104406 90 -0.75022825118950875 96 -0.79868788219999998;
	setAttr -s 17 ".kit[4:16]"  3 9 9 9 9 9 9 3 
		9 9 9 9 9;
	setAttr -s 17 ".kot[4:16]"  3 9 9 9 9 9 9 3 
		9 9 9 9 9;
createNode animCurveTL -n "girl_IKArm_R_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 17 ".ktv[0:16]"  0 -1.146782255 6 -1.176817619445558 12 
		-1.2486738789896006 18 -1.3107224803650162 24 -1.3256177903671562 30 -1.3600454715704262 
		36 -1.3446037085845177 42 -1.3321145922053861 48 -1.3740279683022285 54 -1.3576272638052531 
		60 -1.3952301702622369 66 -1.4105158462979375 72 -1.1855353130625961 78 -1.0977826443646499 
		84 -1.1418301858462927 90 -1.115444808794072 96 -1.146782255;
	setAttr -s 17 ".kit[4:16]"  3 9 9 9 9 9 9 3 
		9 9 9 9 9;
	setAttr -s 17 ".kot[4:16]"  3 9 9 9 9 9 9 3 
		9 9 9 9 9;
createNode animCurveTL -n "girl_IKArm_R_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 1.1096578500000001 12 1.2434104052231363 
		18 1.4588671735951364 24 1.4548777740704284 30 1.4168148632711541 36 1.4711297796431813 
		42 1.4369004840971287 48 1.4451948141295936 54 1.4285365082263455 60 1.4390627767633362 
		66 1.4349525200104889 72 1.2934731132076642 78 1.1784873214455356 84 1.0975200569045551 
		90 1.1271056924657252 96 1.1096578500000001;
	setAttr -s 16 ".kit[3:15]"  3 9 9 9 9 9 9 3 
		9 9 9 9 9;
	setAttr -s 16 ".kot[3:15]"  3 9 9 9 9 9 9 3 
		9 9 9 9 9;
createNode animCurveTA -n "girl_HipSwingerRoot_M_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_HipSwingerRoot_M_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_HipSwingerRoot_M_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraHip_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraHip_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraHip_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKHip_L_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999989 96 0.99999999999999989;
createNode animCurveTU -n "girl_FKHip_L_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_FKHip_L_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000004 96 1.0000000000000004;
createNode animCurveTA -n "girl_FKHip_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -93.148410662823451 96 -93.148410662823451;
createNode animCurveTA -n "girl_FKHip_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.087147345469543197 96 -0.087147345469543197;
createNode animCurveTA -n "girl_FKHip_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -15.275860387989701 96 -15.275860387989701;
createNode animCurveTA -n "girl_FKExtraKnee_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraKnee_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraKnee_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKKnee_L_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999989 96 0.99999999999999989;
createNode animCurveTU -n "girl_FKKnee_L_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999967 96 0.99999999999999967;
createNode animCurveTU -n "girl_FKKnee_L_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTA -n "girl_FKKnee_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 83.913182451591126 11 87.239562485587939 
		21 84.759744267737275 31 79.797647091711553 41 74.840273726247887 50 75.094724129877108 
		60 86.255812352749771 70 78.394210548801539 80 76.096836589870392 96 83.913182451591126;
createNode animCurveTA -n "girl_FKKnee_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -1.6823378597082943 96 -1.6823378597082943;
createNode animCurveTA -n "girl_FKKnee_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 5.0280589807764775 96 5.0280589807764775;
createNode animCurveTA -n "girl_FKExtraAnkle_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraAnkle_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraAnkle_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKAnkle_L_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000004 96 1.0000000000000004;
createNode animCurveTU -n "girl_FKAnkle_L_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000002 96 1.0000000000000002;
createNode animCurveTU -n "girl_FKAnkle_L_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000002 96 1.0000000000000002;
createNode animCurveTA -n "girl_FKAnkle_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKAnkle_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 26.093661828935559 96 26.093661828935559;
createNode animCurveTA -n "girl_FKAnkle_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraMiddleToe1_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraMiddleToe1_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraMiddleToe1_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKMiddleToe1_L_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000004 96 1.0000000000000004;
createNode animCurveTU -n "girl_FKMiddleToe1_L_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_FKMiddleToe1_L_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000004 96 1.0000000000000004;
createNode animCurveTA -n "girl_FKMiddleToe1_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 4.1383308710323172 96 4.1383308710323172;
createNode animCurveTA -n "girl_FKMiddleToe1_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKMiddleToe1_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKExtraScapula_L_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000004 96 1.0000000000000004;
createNode animCurveTU -n "girl_FKExtraScapula_L_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000002 96 1.0000000000000002;
createNode animCurveTU -n "girl_FKExtraScapula_L_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTA -n "girl_FKExtraScapula_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraScapula_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraScapula_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_FKExtraScapula_L_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_FKExtraScapula_L_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_FKExtraScapula_L_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKScapula_L_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999989 96 0.99999999999999989;
createNode animCurveTU -n "girl_FKScapula_L_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999989 96 0.99999999999999989;
createNode animCurveTU -n "girl_FKScapula_L_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999989 96 0.99999999999999989;
createNode animCurveTA -n "girl_FKScapula_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -5.7485006011304165 96 -5.7485006011304165;
createNode animCurveTA -n "girl_FKScapula_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKScapula_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_FKScapula_L_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_FKScapula_L_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_FKScapula_L_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraShoulder_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraShoulder_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraShoulder_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKShoulder_L_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_FKShoulder_L_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_FKShoulder_L_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999978 96 0.99999999999999978;
createNode animCurveTA -n "girl_FKShoulder_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKShoulder_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKShoulder_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraElbow_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraElbow_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraElbow_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKElbow_L_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_FKElbow_L_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_FKElbow_L_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTA -n "girl_FKElbow_L_rotateZ2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKElbow_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKElbow_L_rotateX2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraWrist_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraWrist_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraWrist_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKWrist_L_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_FKWrist_L_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_FKWrist_L_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000002 96 1.0000000000000002;
createNode animCurveTA -n "girl_FKWrist_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKWrist_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKWrist_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger1_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger1_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger1_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKMiddleFinger1_L_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999989 96 0.99999999999999989;
createNode animCurveTU -n "girl_FKMiddleFinger1_L_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999989 96 0.99999999999999989;
createNode animCurveTU -n "girl_FKMiddleFinger1_L_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999989 96 0.99999999999999989;
createNode animCurveTA -n "girl_FKMiddleFinger1_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 21.441017057914681 96 21.441017057914681;
createNode animCurveTA -n "girl_FKMiddleFinger1_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKMiddleFinger1_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger2_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger2_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger2_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKMiddleFinger2_L_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999944 96 0.99999999999999944;
createNode animCurveTU -n "girl_FKMiddleFinger2_L_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999956 96 0.99999999999999956;
createNode animCurveTU -n "girl_FKMiddleFinger2_L_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999967 96 0.99999999999999967;
createNode animCurveTA -n "girl_FKMiddleFinger2_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKMiddleFinger2_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKMiddleFinger2_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger3_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger3_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger3_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKMiddleFinger3_L_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999989 96 0.99999999999999989;
createNode animCurveTU -n "girl_FKMiddleFinger3_L_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_FKMiddleFinger3_L_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTA -n "girl_FKMiddleFinger3_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKMiddleFinger3_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKMiddleFinger3_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger1_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger1_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger1_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKThumbFinger1_L_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999989 96 0.99999999999999989;
createNode animCurveTU -n "girl_FKThumbFinger1_L_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999978 96 0.99999999999999978;
createNode animCurveTU -n "girl_FKThumbFinger1_L_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTA -n "girl_FKThumbFinger1_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -4.6159099819999998 96 -4.6159099819999998;
createNode animCurveTA -n "girl_FKThumbFinger1_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -20.29236869 96 -20.29236869;
createNode animCurveTA -n "girl_FKThumbFinger1_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -6.2745051959999998 96 -6.2745051959999998;
createNode animCurveTA -n "girl_FKExtraThumbFinger2_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger2_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger2_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKThumbFinger2_L_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999978 96 0.99999999999999978;
createNode animCurveTU -n "girl_FKThumbFinger2_L_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999978 96 0.99999999999999978;
createNode animCurveTU -n "girl_FKThumbFinger2_L_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999978 96 0.99999999999999978;
createNode animCurveTA -n "girl_FKThumbFinger2_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKThumbFinger2_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKThumbFinger2_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger3_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger3_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger3_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKThumbFinger3_L_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000007 96 1.0000000000000007;
createNode animCurveTU -n "girl_FKThumbFinger3_L_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000004 96 1.0000000000000004;
createNode animCurveTU -n "girl_FKThumbFinger3_L_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000002 96 1.0000000000000002;
createNode animCurveTA -n "girl_FKThumbFinger3_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKThumbFinger3_L_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKThumbFinger3_L_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraHip_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraHip_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraHip_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKHip_R_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000002 96 1.0000000000000002;
createNode animCurveTU -n "girl_FKHip_R_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999989 96 0.99999999999999989;
createNode animCurveTU -n "girl_FKHip_R_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000002 96 1.0000000000000002;
createNode animCurveTA -n "girl_FKHip_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -105.77848472630944 96 -105.77848472630944;
createNode animCurveTA -n "girl_FKHip_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -8.2096526943984909 96 -8.2096526943984909;
createNode animCurveTA -n "girl_FKHip_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -8.1666847929670165 96 -8.1666847929670165;
createNode animCurveTA -n "girl_FKExtraKnee_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraKnee_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraKnee_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKKnee_R_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999989 96 0.99999999999999989;
createNode animCurveTU -n "girl_FKKnee_R_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_FKKnee_R_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000002 96 1.0000000000000002;
createNode animCurveTA -n "girl_FKKnee_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 75.333348250175646 7 81.093348056088146 
		18 78.605660988721468 28 72.588866973893886 37 66.410029425841373 48 68.620625490267528 
		54 75.948036579264354 57 80.487148385928649 60 81.095350839655026 71 70.692362565264489 
		80 67.587765588735806 86 71.665778613800498 92 76.554363688586605 96 75.333348250175646;
	setAttr -s 14 ".kit[5:13]"  1 1 9 9 9 1 9 1 
		3;
	setAttr -s 14 ".kot[5:13]"  1 1 9 9 9 1 9 1 
		3;
	setAttr -s 14 ".kix[5:13]"  0.89599913358688354 0.77618354558944702 
		0.91219854354858398 0.93898022174835205 0.9427870512008667 0.99999898672103882 0.9312625527381897 
		0.99969422817230225 1;
	setAttr -s 14 ".kiy[5:13]"  0.4440557062625885 0.63050711154937744 
		0.40974846482276917 -0.34397119283676147 -0.33339563012123108 -0.0014374933671206236 
		0.36434882879257202 0.024728564545512199 0;
	setAttr -s 14 ".kox[5:13]"  0.89599919319152832 0.7761836051940918 
		0.91219854354858398 0.93898022174835205 0.9427870512008667 0.99999898672103882 0.9312625527381897 
		0.99969422817230225 1;
	setAttr -s 14 ".koy[5:13]"  0.44405573606491089 0.63050705194473267 
		0.40974846482276917 -0.34397119283676147 -0.33339563012123108 -0.0014374970924109221 
		0.36434882879257202 0.024728575721383095 0;
createNode animCurveTA -n "girl_FKKnee_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKKnee_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraAnkle_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraAnkle_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraAnkle_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKAnkle_R_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000002 96 1.0000000000000002;
createNode animCurveTU -n "girl_FKAnkle_R_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000002 96 1.0000000000000002;
createNode animCurveTU -n "girl_FKAnkle_R_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000002 96 1.0000000000000002;
createNode animCurveTA -n "girl_FKAnkle_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKAnkle_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 23.040000415782014 96 23.040000415782014;
createNode animCurveTA -n "girl_FKAnkle_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraMiddleToe1_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraMiddleToe1_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraMiddleToe1_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKMiddleToe1_R_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_FKMiddleToe1_R_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_FKMiddleToe1_R_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTA -n "girl_FKMiddleToe1_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKMiddleToe1_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKMiddleToe1_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraBackA_M_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraBackA_M_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraBackA_M_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKBackA_M_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999967 96 0.99999999999999967;
	setAttr -s 2 ".kit[1]"  3;
	setAttr -s 2 ".kot[1]"  3;
createNode animCurveTU -n "girl_FKBackA_M_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999944 96 0.99999999999999944;
	setAttr -s 2 ".kit[1]"  3;
	setAttr -s 2 ".kot[1]"  3;
createNode animCurveTU -n "girl_FKBackA_M_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999989 96 0.99999999999999989;
	setAttr -s 2 ".kit[1]"  3;
	setAttr -s 2 ".kot[1]"  3;
createNode animCurveTA -n "girl_FKBackA_M_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 17 ".ktv[0:16]"  0 -1.4940187201541966 6 -0.39841174568838633 
		12 0.24857735345939186 18 0.13660052702710526 24 -1.1257708509171414 30 -0.21865672540726119 
		36 2.1376432541988488 42 4.6114497441889855 48 5.3252756430867345 54 4.3941467840929533 
		60 2.6175874701673534 66 0.42273978113032051 72 -1.5774174410461437 78 -3.0805939499028745 
		84 -3.3951201045651445 90 -2.5760788398991821 96 -1.4940187201541966;
	setAttr -s 17 ".kit[6:16]"  1 1 9 9 9 9 9 9 
		9 1 3;
	setAttr -s 17 ".kot[6:16]"  1 1 9 9 9 9 9 9 
		9 1 3;
	setAttr -s 17 ".kix[6:16]"  0.9671444296836853 0.99031805992126465 
		0.99995505809783936 0.99309301376342773 0.98531597852706909 0.98365741968154907 0.98851752281188965 
		0.99686950445175171 0.99975782632827759 0.98855572938919067 1;
	setAttr -s 17 ".kiy[6:16]"  0.25422757863998413 0.13881725072860718 
		-0.0094812046736478806 -0.11732916533946991 -0.1707407534122467 -0.18005020916461945 
		-0.1511065810918808 -0.079063981771469116 0.022008288651704788 0.15085604786872864 
		0;
	setAttr -s 17 ".kox[6:16]"  0.9671444296836853 0.99031805992126465 
		0.99995505809783936 0.99309301376342773 0.98531597852706909 0.98365741968154907 0.98851752281188965 
		0.99686950445175171 0.99975782632827759 0.98855578899383545 1;
	setAttr -s 17 ".koy[6:16]"  0.25422757863998413 0.13881726562976837 
		-0.0094812046736478806 -0.11732916533946991 -0.1707407534122467 -0.18005020916461945 
		-0.1511065810918808 -0.079063981771469116 0.022008288651704788 0.15085603296756744 
		0;
createNode animCurveTA -n "girl_FKBackA_M_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 17 ".ktv[0:16]"  0 0.21231936819650479 6 0.087200184748729051 
		12 0.018034247358809749 18 0.048446191813566374 24 0.18091023979733087 30 -0.10877428691015714 
		36 -0.43962242193902212 42 -0.69392295616310939 48 -0.81318783324359056 54 -0.62973178946753483 
		60 -0.35964969950151993 66 -0.027555718022338666 72 0.30049857248932765 78 0.52217266634800152 
		84 0.62195296950958445 90 0.5532431212136969 96 0.21231936819650479;
	setAttr -s 17 ".kit[14:16]"  1 9 3;
	setAttr -s 17 ".kot[14:16]"  1 9 3;
	setAttr -s 17 ".kix[14:16]"  0.99999994039535522 0.99984025955200195 
		1;
	setAttr -s 17 ".kiy[14:16]"  -0.00034831056836992502 -0.01787077821791172 
		0;
	setAttr -s 17 ".kox[14:16]"  0.99999994039535522 0.99984025955200195 
		1;
	setAttr -s 17 ".koy[14:16]"  -0.00034831033553928137 -0.01787077821791172 
		0;
createNode animCurveTA -n "girl_FKBackA_M_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 17 ".ktv[0:16]"  0 8.0864829283442798 6 8.0883596319015716 
		12 8.0892312909379651 18 8.0891432381438317 24 8.0866860667625691 30 8.0882584533386979 
		36 8.0817975025201463 42 8.0533533934114168 48 8.0652239571163609 54 8.0620671906028392 
		60 8.0866591646511026 66 8.0883151854065449 72 8.0800115031342159 78 8.0664113427272959 
		84 8.0704358569265473 90 8.0704358569265473 96 8.0864829283442798;
	setAttr -s 17 ".kit[3:16]"  1 9 1 9 9 9 9 9 
		9 9 9 9 9 3;
	setAttr -s 17 ".kot[3:16]"  1 9 1 9 9 9 9 9 
		9 9 9 9 9 3;
	setAttr -s 17 ".kix[3:16]"  1 1 0.9999995231628418 0.99999892711639404 
		0.9999997615814209 1 0.99999964237213135 0.99999940395355225 1 0.9999995231628418 
		1 1 0.9999997615814209 1;
	setAttr -s 17 ".kiy[3:16]"  -4.5617955038323998e-005 -3.8606023736065254e-005 
		-0.00098209909629076719 -0.0015230190474539995 -0.00072315719444304705 0.00038021116051822901 
		0.00093528709840029478 0.0011452838080003858 -0.00029005887336097658 -0.00095573533326387405 
		-0.00041781653999350965 0.00017560251581016928 0.00070018525002524257 0;
	setAttr -s 17 ".kox[3:16]"  1 1 0.9999995231628418 0.99999892711639404 
		0.9999997615814209 1 0.99999964237213135 0.99999940395355225 1 0.9999995231628418 
		1 1 0.9999997615814209 1;
	setAttr -s 17 ".koy[3:16]"  -4.5617955038323998e-005 -3.8606023736065254e-005 
		-0.00098209909629076719 -0.0015230190474539995 -0.00072315719444304705 0.00038021116051822901 
		0.00093528709840029478 0.0011452838080003858 -0.00029005887336097658 -0.00095573533326387405 
		-0.00041781653999350965 0.00017560251581016928 0.00070018525002524257 0;
createNode animCurveTA -n "girl_FKExtraBackB_M_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraBackB_M_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraBackB_M_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKBackB_M_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_FKBackB_M_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_FKBackB_M_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTA -n "girl_FKBackB_M_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -5.9919002747580032 96 -5.9919002747580032;
createNode animCurveTA -n "girl_FKBackB_M_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0482071512878739 96 1.0482071512878739;
createNode animCurveTA -n "girl_FKBackB_M_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 9.8867372438892591 96 9.8867372438892591;
createNode animCurveTA -n "girl_FKExtraChest_M_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraChest_M_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraChest_M_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKChest_M_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_FKChest_M_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_FKChest_M_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTA -n "girl_FKChest_M_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -4.0762394232620087 96 -4.0762394232620087;
createNode animCurveTA -n "girl_FKChest_M_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKChest_M_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraNeck_M_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraNeck_M_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraNeck_M_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKNeck_M_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_FKNeck_M_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000004 96 1.0000000000000004;
createNode animCurveTU -n "girl_FKNeck_M_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000002 96 1.0000000000000002;
createNode animCurveTA -n "girl_FKNeck_M_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 3.3359955434418795 12 -0.6109607164142149 
		24 -7.5963642934008293 36 -17.738046914793074 48 -19.586607091475948 60 -18.903706946254516 
		72 -7.3705467087358176 84 0.94960225806554699 96 3.3359955434418795;
createNode animCurveTA -n "girl_FKNeck_M_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKNeck_M_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 7.9199999167549402 96 7.9199999167549402;
createNode animCurveTA -n "girl_FKExtraHead_M_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraHead_M_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraHead_M_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKHead_M_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_FKHead_M_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_FKHead_M_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTA -n "girl_FKHead_M_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 5.7727404330954437 6 5.7592798618085403 
		12 5.6409084145334338 18 5.3672765276297874 24 3.7080520220922848 30 1.1507383593889029 
		72 -7.4892617523763478 78 -2.5527237698456213 84 5.7727404330954437 90 5.7727404330954437 
		96 5.7727404330954437;
createNode animCurveTA -n "girl_FKHead_M_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 6 -0.39465492313429118 12 -1.2286435670046525 
		18 -2.1284113509240958 24 -2.5261247913548428 30 -2.6877609008253787 72 -2.6877609008253787 
		78 -2.1284113628187566 84 0 90 0 96 0;
createNode animCurveTA -n "girl_FKHead_M_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 45.75470585545532 6 41.847839442196303 
		12 33.506489010358287 18 24.185731713065483 24 19.880516559944901 30 18.085930484294181 
		72 18.085930484294181 78 24.185731586373983 84 45.75470585545532 90 45.75470585545532 
		96 45.75470585545532;
createNode animCurveTU -n "girl_FKExtraScapula_R_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000004 96 1.0000000000000004;
createNode animCurveTU -n "girl_FKExtraScapula_R_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000002 96 1.0000000000000002;
createNode animCurveTU -n "girl_FKExtraScapula_R_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000004 96 1.0000000000000004;
createNode animCurveTA -n "girl_FKExtraScapula_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraScapula_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraScapula_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_FKExtraScapula_R_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_FKExtraScapula_R_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_FKExtraScapula_R_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKScapula_R_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999989 96 0.99999999999999989;
createNode animCurveTU -n "girl_FKScapula_R_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999956 96 0.99999999999999956;
createNode animCurveTU -n "girl_FKScapula_R_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999922 96 0.99999999999999922;
createNode animCurveTA -n "girl_FKScapula_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKScapula_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKScapula_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_FKScapula_R_translateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_FKScapula_R_translateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_FKScapula_R_translateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraShoulder_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraShoulder_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraShoulder_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKShoulder_R_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999989 96 0.99999999999999989;
createNode animCurveTU -n "girl_FKShoulder_R_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000002 96 1.0000000000000002;
createNode animCurveTU -n "girl_FKShoulder_R_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999978 96 0.99999999999999978;
createNode animCurveTA -n "girl_FKShoulder_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKShoulder_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKShoulder_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraElbow_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraElbow_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraElbow_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKElbow_R_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999967 96 0.99999999999999967;
createNode animCurveTU -n "girl_FKElbow_R_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999956 96 0.99999999999999956;
createNode animCurveTU -n "girl_FKElbow_R_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999978 96 0.99999999999999978;
createNode animCurveTA -n "girl_FKElbow_R_rotateZ2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKElbow_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKElbow_R_rotateX2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraWrist_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraWrist_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraWrist_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKWrist_R_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.999999999999999 96 0.999999999999999;
createNode animCurveTU -n "girl_FKWrist_R_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999933 96 0.99999999999999933;
createNode animCurveTU -n "girl_FKWrist_R_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999922 96 0.99999999999999922;
createNode animCurveTA -n "girl_FKWrist_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKWrist_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKWrist_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger1_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger1_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger1_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKMiddleFinger1_R_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000002 96 1.0000000000000002;
createNode animCurveTU -n "girl_FKMiddleFinger1_R_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999978 96 0.99999999999999978;
createNode animCurveTU -n "girl_FKMiddleFinger1_R_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999956 96 0.99999999999999956;
createNode animCurveTA -n "girl_FKMiddleFinger1_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -9.8496280095381739 16 -9.8496280095381739 
		21 5.1734627137595437 63 5.1734627137595437 96 -9.8496280095381739;
createNode animCurveTA -n "girl_FKMiddleFinger1_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -2.0984782587122006 16 -2.0984782587122006 
		21 -2.0984782587122006 63 -2.0984782587122006 96 -2.0984782587122006;
createNode animCurveTA -n "girl_FKMiddleFinger1_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.156749226655551 16 -1.156749226655551 
		21 -1.156749226655551 63 -1.156749226655551 96 -1.156749226655551;
createNode animCurveTA -n "girl_FKExtraMiddleFinger2_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger2_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger2_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKMiddleFinger2_R_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999978 96 0.99999999999999978;
createNode animCurveTU -n "girl_FKMiddleFinger2_R_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999967 96 0.99999999999999967;
createNode animCurveTU -n "girl_FKMiddleFinger2_R_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999933 96 0.99999999999999933;
createNode animCurveTA -n "girl_FKMiddleFinger2_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -21.724355717678407 16 -21.724355717678407 
		21 -9.9983739682055592 63 -9.9983739682055592 96 -21.724355717678407;
createNode animCurveTA -n "girl_FKMiddleFinger2_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.54486597751175991 16 0.54486597751175991 
		21 0.54486597751175991 63 0.54486597751175991 96 0.54486597751175991;
createNode animCurveTA -n "girl_FKMiddleFinger2_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.57631240306333031 16 0.57631240306333031 
		21 0.57631240306333031 63 0.57631240306333031 96 0.57631240306333031;
createNode animCurveTA -n "girl_FKExtraMiddleFinger3_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger3_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraMiddleFinger3_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKMiddleFinger3_R_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999944 96 0.99999999999999944;
createNode animCurveTU -n "girl_FKMiddleFinger3_R_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999978 96 0.99999999999999978;
createNode animCurveTU -n "girl_FKMiddleFinger3_R_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999989 96 0.99999999999999989;
createNode animCurveTA -n "girl_FKMiddleFinger3_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 16 0 21 -3.4507295791636303 63 -3.4507295791636303 
		96 0;
createNode animCurveTA -n "girl_FKMiddleFinger3_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 16 0 21 0 63 0 96 0;
createNode animCurveTA -n "girl_FKMiddleFinger3_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 16 0 21 0 63 0 96 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger1_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger1_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger1_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKThumbFinger1_R_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999989 96 0.99999999999999989;
createNode animCurveTU -n "girl_FKThumbFinger1_R_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999956 96 0.99999999999999956;
createNode animCurveTU -n "girl_FKThumbFinger1_R_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTA -n "girl_FKThumbFinger1_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 2.735941457 96 2.735941457;
createNode animCurveTA -n "girl_FKThumbFinger1_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -18.208718699999999 96 -18.208718699999999;
createNode animCurveTA -n "girl_FKThumbFinger1_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 36.37463082 96 36.37463082;
createNode animCurveTA -n "girl_FKExtraThumbFinger2_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger2_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger2_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKThumbFinger2_R_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999967 96 0.99999999999999967;
createNode animCurveTU -n "girl_FKThumbFinger2_R_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999989 96 0.99999999999999989;
createNode animCurveTU -n "girl_FKThumbFinger2_R_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999989 96 0.99999999999999989;
createNode animCurveTA -n "girl_FKThumbFinger2_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -1.0012879291189114 96 -1.0012879291189114;
createNode animCurveTA -n "girl_FKThumbFinger2_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.44921033998490534 96 -0.44921033998490534;
createNode animCurveTA -n "girl_FKThumbFinger2_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 24.800969063594167 96 24.800969063594167;
createNode animCurveTA -n "girl_FKExtraThumbFinger3_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger3_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKExtraThumbFinger3_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_FKThumbFinger3_R_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_FKThumbFinger3_R_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000002 96 1.0000000000000002;
createNode animCurveTU -n "girl_FKThumbFinger3_R_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000002 96 1.0000000000000002;
createNode animCurveTA -n "girl_FKThumbFinger3_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKThumbFinger3_R_rotateY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_FKThumbFinger3_R_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_Group_scaleZ2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_Group_scaleY2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTU -n "girl_Group_scaleX2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
createNode animCurveTA -n "girl_Group_rotateZ2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_Group_rotateY2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTA -n "girl_Group_rotateX2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_Group_translateZ2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_Group_translateY2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTL -n "girl_Group_translateX2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 96 0;
createNode animCurveTU -n "girl_Group_visibility2";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 96 1;
	setAttr -s 2 ".kot[0:1]"  5 5;
createNode lightLinker -n "lightLinker1";
	setAttr -s 5 ".lnk";
	setAttr -s 5 ".slnk";
createNode lightLinker -n "_FemaleOldAnimating:lightLinker1";
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
	setAttr -s 8 ".st";
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
	setAttr -s 8 ".s";
select -ne :postProcessList1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -s 14 ".u";
select -ne :lightList1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 2 ".ln";
select -ne :defaultTextureList1;
	setAttr -s 6 ".tx";
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
	setAttr -s 2 ".st";
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
connectAttr "Minigame2_applauseSource.cl" "clipLibrary1.sc[0]";
connectAttr "back_skirt_b_CTRL_rotateZ.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "back_skirt_b_CTRL_rotateY.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "back_skirt_b_CTRL_rotateX.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "girl_angularValues_4_2.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "girl_angularValues_5_2.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "girl_angularValues_6_2.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "girl_R_cloak_C_CTRL_rotateZ2.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "girl_R_cloak_C_CTRL_rotateY2.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "girl_R_cloak_C_CTRL_rotateX2.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "girl_R_cloak_B_CTRL_rotateZ2.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "girl_R_cloak_B_CTRL_rotateY2.a" "clipLibrary1.cel[0].cev[10].cevr";
connectAttr "girl_R_cloak_B_CTRL_rotateX2.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "girl_R_cloak_A_CTRL_rotateZ2.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "girl_R_cloak_A_CTRL_rotateY2.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "girl_R_cloak_A_CTRL_rotateX2.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "girl_L_cloak_C_CTRL_rotateZ2.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "girl_L_cloak_C_CTRL_rotateY2.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "girl_L_cloak_C_CTRL_rotateX2.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "girl_L_cloak_B_CTRL_rotateZ2.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "girl_L_cloak_B_CTRL_rotateY2.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "girl_L_cloak_B_CTRL_rotateX2.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "girl_L_cloak_A_CTRL_rotateZ2.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "girl_L_cloak_A_CTRL_rotateY2.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "girl_L_cloak_A_CTRL_rotateX2.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "girl_cloak_D_CTRL_rotateZ2.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "girl_cloak_D_CTRL_rotateY2.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "girl_cloak_D_CTRL_rotateX2.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "girl_cloak_C_CTRL_rotateZ2.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "girl_cloak_C_CTRL_rotateY2.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "girl_cloak_C_CTRL_rotateX2.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "girl_cloak_B_CTRL_rotateZ2.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "girl_cloak_B_CTRL_rotateY2.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "girl_cloak_B_CTRL_rotateX2.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "girl_cloak_A_CTRL_rotateZ2.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "girl_cloak_A_CTRL_rotateY2.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "girl_cloak_A_CTRL_rotateX2.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "girl_angularValues_37_2.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "girl_angularValues_38_2.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "girl_angularValues_39_2.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "back_skirt_b_CTRL_translateZ.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "back_skirt_b_CTRL_translateY.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "back_skirt_b_CTRL_translateX.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "girl_angularValues_40_2.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "girl_angularValues_41_2.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "girl_angularValues_42_2.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "girl_linearValues_4_2.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "girl_linearValues_5_2.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "girl_linearValues_6_2.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "girl_back_skirt_b_CTRL_rotateZ2.a" "clipLibrary1.cel[0].cev[48].cevr"
		;
connectAttr "girl_back_skirt_b_CTRL_rotateY2.a" "clipLibrary1.cel[0].cev[49].cevr"
		;
connectAttr "girl_back_skirt_b_CTRL_rotateX2.a" "clipLibrary1.cel[0].cev[50].cevr"
		;
connectAttr "girl_back_skirt_b_CTRL_translateZ2.a" "clipLibrary1.cel[0].cev[51].cevr"
		;
connectAttr "girl_back_skirt_b_CTRL_translateY2.a" "clipLibrary1.cel[0].cev[52].cevr"
		;
connectAttr "girl_back_skirt_b_CTRL_translateX2.a" "clipLibrary1.cel[0].cev[53].cevr"
		;
connectAttr "girl_back_skirt_a_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[54].cevr"
		;
connectAttr "girl_back_skirt_a_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[55].cevr"
		;
connectAttr "girl_back_skirt_a_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[56].cevr"
		;
connectAttr "girl_back_skirt_a_CTRL_translateZ1.a" "clipLibrary1.cel[0].cev[57].cevr"
		;
connectAttr "girl_back_skirt_a_CTRL_translateY1.a" "clipLibrary1.cel[0].cev[58].cevr"
		;
connectAttr "girl_back_skirt_a_CTRL_translateX1.a" "clipLibrary1.cel[0].cev[59].cevr"
		;
connectAttr "girl_front_skirt_b_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[60].cevr"
		;
connectAttr "girl_front_skirt_b_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[61].cevr"
		;
connectAttr "girl_front_skirt_b_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[62].cevr"
		;
connectAttr "girl_front_skirt_b_CTRL_translateZ1.a" "clipLibrary1.cel[0].cev[63].cevr"
		;
connectAttr "girl_front_skirt_b_CTRL_translateY1.a" "clipLibrary1.cel[0].cev[64].cevr"
		;
connectAttr "girl_front_skirt_b_CTRL_translateX1.a" "clipLibrary1.cel[0].cev[65].cevr"
		;
connectAttr "girl_front_skirt_a_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[66].cevr"
		;
connectAttr "girl_front_skirt_a_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[67].cevr"
		;
connectAttr "girl_front_skirt_a_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[68].cevr"
		;
connectAttr "girl_front_skirt_a_CTRL_translateZ1.a" "clipLibrary1.cel[0].cev[69].cevr"
		;
connectAttr "girl_front_skirt_a_CTRL_translateY1.a" "clipLibrary1.cel[0].cev[70].cevr"
		;
connectAttr "girl_front_skirt_a_CTRL_translateX1.a" "clipLibrary1.cel[0].cev[71].cevr"
		;
connectAttr "girl_skirt_HipA_L_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[72].cevr"
		;
connectAttr "girl_skirt_HipA_L_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[73].cevr"
		;
connectAttr "girl_skirt_HipA_L_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[74].cevr"
		;
connectAttr "girl_skirt_HipA_L_CTRL_translateZ1.a" "clipLibrary1.cel[0].cev[75].cevr"
		;
connectAttr "girl_skirt_HipA_L_CTRL_translateY1.a" "clipLibrary1.cel[0].cev[76].cevr"
		;
connectAttr "girl_skirt_HipA_L_CTRL_translateX1.a" "clipLibrary1.cel[0].cev[77].cevr"
		;
connectAttr "girl_skirt_Hip_L_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[78].cevr"
		;
connectAttr "girl_skirt_Hip_L_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[79].cevr"
		;
connectAttr "girl_skirt_Hip_L_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[80].cevr"
		;
connectAttr "girl_skirt_Hip_L_CTRL_translateZ1.a" "clipLibrary1.cel[0].cev[81].cevr"
		;
connectAttr "girl_skirt_Hip_L_CTRL_translateY1.a" "clipLibrary1.cel[0].cev[82].cevr"
		;
connectAttr "girl_skirt_Hip_L_CTRL_translateX1.a" "clipLibrary1.cel[0].cev[83].cevr"
		;
connectAttr "girl_skirt_HipA_R_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[84].cevr"
		;
connectAttr "girl_skirt_HipA_R_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[85].cevr"
		;
connectAttr "girl_skirt_HipA_R_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[86].cevr"
		;
connectAttr "girl_skirt_HipA_R_CTRL_translateZ1.a" "clipLibrary1.cel[0].cev[87].cevr"
		;
connectAttr "girl_skirt_HipA_R_CTRL_translateY1.a" "clipLibrary1.cel[0].cev[88].cevr"
		;
connectAttr "girl_skirt_HipA_R_CTRL_translateX1.a" "clipLibrary1.cel[0].cev[89].cevr"
		;
connectAttr "girl_skirt_Hip_R_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[90].cevr"
		;
connectAttr "girl_skirt_Hip_R_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[91].cevr"
		;
connectAttr "girl_skirt_Hip_R_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[92].cevr"
		;
connectAttr "girl_skirt_Hip_R_CTRL_translateZ1.a" "clipLibrary1.cel[0].cev[93].cevr"
		;
connectAttr "girl_skirt_Hip_R_CTRL_translateY1.a" "clipLibrary1.cel[0].cev[94].cevr"
		;
connectAttr "girl_skirt_Hip_R_CTRL_translateX1.a" "clipLibrary1.cel[0].cev[95].cevr"
		;
connectAttr "girl_Center_M_CenterBtwFeet1.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "girl_Center_M_rotateZ1.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "girl_Center_M_rotateY1.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "girl_Center_M_rotateX1.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "girl_Center_M_translateZ1.a" "clipLibrary1.cel[0].cev[100].cevr";
connectAttr "girl_Center_M_translateY1.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "girl_Center_M_translateX1.a" "clipLibrary1.cel[0].cev[102].cevr";
connectAttr "girl_CenterExtra_M_rotateZ1.a" "clipLibrary1.cel[0].cev[103].cevr";
connectAttr "girl_CenterExtra_M_rotateY1.a" "clipLibrary1.cel[0].cev[104].cevr";
connectAttr "girl_CenterExtra_M_rotateX1.a" "clipLibrary1.cel[0].cev[105].cevr";
connectAttr "girl_CenterExtra_M_translateZ1.a" "clipLibrary1.cel[0].cev[106].cevr"
		;
connectAttr "girl_CenterExtra_M_translateY1.a" "clipLibrary1.cel[0].cev[107].cevr"
		;
connectAttr "girl_CenterExtra_M_translateX1.a" "clipLibrary1.cel[0].cev[108].cevr"
		;
connectAttr "girl_Fingers_L_Cup1.a" "clipLibrary1.cel[0].cev[109].cevr";
connectAttr "girl_Fingers_L_Spread1.a" "clipLibrary1.cel[0].cev[110].cevr";
connectAttr "girl_Fingers_L_ThumbFingerCurl1.a" "clipLibrary1.cel[0].cev[111].cevr"
		;
connectAttr "girl_Fingers_L_PinkyFingerCurl1.a" "clipLibrary1.cel[0].cev[112].cevr"
		;
connectAttr "girl_Fingers_L_RingFingerCurl1.a" "clipLibrary1.cel[0].cev[113].cevr"
		;
connectAttr "girl_Fingers_L_MiddleFingerCurl1.a" "clipLibrary1.cel[0].cev[114].cevr"
		;
connectAttr "girl_Fingers_L_IndexFingerCurl1.a" "clipLibrary1.cel[0].cev[115].cevr"
		;
connectAttr "girl_IKExtraLegBall_L_rotateZ1.a" "clipLibrary1.cel[0].cev[116].cevr"
		;
connectAttr "girl_IKExtraLegBall_L_rotateY1.a" "clipLibrary1.cel[0].cev[117].cevr"
		;
connectAttr "girl_IKExtraLegBall_L_rotateX1.a" "clipLibrary1.cel[0].cev[118].cevr"
		;
connectAttr "girl_IKLegBall_L_rotateX1.a" "clipLibrary1.cel[0].cev[119].cevr";
connectAttr "girl_IKExtraLegToe_L_rotateZ1.a" "clipLibrary1.cel[0].cev[120].cevr"
		;
connectAttr "girl_IKExtraLegToe_L_rotateY1.a" "clipLibrary1.cel[0].cev[121].cevr"
		;
connectAttr "girl_IKExtraLegToe_L_rotateX1.a" "clipLibrary1.cel[0].cev[122].cevr"
		;
connectAttr "girl_IKLegToe_L_rotateZ1.a" "clipLibrary1.cel[0].cev[123].cevr";
connectAttr "girl_IKLegToe_L_rotateY1.a" "clipLibrary1.cel[0].cev[124].cevr";
connectAttr "girl_IKLegToe_L_rotateX1.a" "clipLibrary1.cel[0].cev[125].cevr";
connectAttr "girl_IKExtraLegHeel_L_rotateZ1.a" "clipLibrary1.cel[0].cev[126].cevr"
		;
connectAttr "girl_IKExtraLegHeel_L_rotateY1.a" "clipLibrary1.cel[0].cev[127].cevr"
		;
connectAttr "girl_IKExtraLegHeel_L_rotateX1.a" "clipLibrary1.cel[0].cev[128].cevr"
		;
connectAttr "girl_IKLegHeel_L_rotateZ1.a" "clipLibrary1.cel[0].cev[129].cevr";
connectAttr "girl_IKLegHeel_L_rotateY1.a" "clipLibrary1.cel[0].cev[130].cevr";
connectAttr "girl_IKLegHeel_L_rotateX1.a" "clipLibrary1.cel[0].cev[131].cevr";
connectAttr "girl_FKIKLeg_L_IKVis1.a" "clipLibrary1.cel[0].cev[132].cevr";
connectAttr "girl_FKIKLeg_L_FKVis1.a" "clipLibrary1.cel[0].cev[133].cevr";
connectAttr "girl_FKIKLeg_L_FKIKBlend1.a" "clipLibrary1.cel[0].cev[134].cevr";
connectAttr "girl_PoleExtraLeg_L_translateZ1.a" "clipLibrary1.cel[0].cev[135].cevr"
		;
connectAttr "girl_PoleExtraLeg_L_translateY1.a" "clipLibrary1.cel[0].cev[136].cevr"
		;
connectAttr "girl_PoleExtraLeg_L_translateX1.a" "clipLibrary1.cel[0].cev[137].cevr"
		;
connectAttr "girl_PoleLeg_L_follow1.a" "clipLibrary1.cel[0].cev[138].cevr";
connectAttr "girl_PoleLeg_L_translateZ1.a" "clipLibrary1.cel[0].cev[139].cevr";
connectAttr "girl_PoleLeg_L_translateY1.a" "clipLibrary1.cel[0].cev[140].cevr";
connectAttr "girl_PoleLeg_L_translateX1.a" "clipLibrary1.cel[0].cev[141].cevr";
connectAttr "girl_IKExtraLeg_L_rotateZ1.a" "clipLibrary1.cel[0].cev[142].cevr";
connectAttr "girl_IKExtraLeg_L_rotateY1.a" "clipLibrary1.cel[0].cev[143].cevr";
connectAttr "girl_IKExtraLeg_L_rotateX1.a" "clipLibrary1.cel[0].cev[144].cevr";
connectAttr "girl_IKExtraLeg_L_translateZ1.a" "clipLibrary1.cel[0].cev[145].cevr"
		;
connectAttr "girl_IKExtraLeg_L_translateY1.a" "clipLibrary1.cel[0].cev[146].cevr"
		;
connectAttr "girl_IKExtraLeg_L_translateX1.a" "clipLibrary1.cel[0].cev[147].cevr"
		;
connectAttr "girl_IKLeg_L_Lenght4.a" "clipLibrary1.cel[0].cev[148].cevr";
connectAttr "girl_IKLeg_L_Lenght3.a" "clipLibrary1.cel[0].cev[149].cevr";
connectAttr "girl_IKLeg_L_antiPop1.a" "clipLibrary1.cel[0].cev[150].cevr";
connectAttr "girl_IKLeg_L_stretchy1.a" "clipLibrary1.cel[0].cev[151].cevr";
connectAttr "girl_IKLeg_L_rollAngle1.a" "clipLibrary1.cel[0].cev[152].cevr";
connectAttr "girl_IKLeg_L_roll1.a" "clipLibrary1.cel[0].cev[153].cevr";
connectAttr "girl_IKLeg_L_toe1.a" "clipLibrary1.cel[0].cev[154].cevr";
connectAttr "girl_IKLeg_L_swivel1.a" "clipLibrary1.cel[0].cev[155].cevr";
connectAttr "girl_IKLeg_L_rotateZ1.a" "clipLibrary1.cel[0].cev[156].cevr";
connectAttr "girl_IKLeg_L_rotateY1.a" "clipLibrary1.cel[0].cev[157].cevr";
connectAttr "girl_IKLeg_L_rotateX1.a" "clipLibrary1.cel[0].cev[158].cevr";
connectAttr "girl_IKLeg_L_translateZ1.a" "clipLibrary1.cel[0].cev[159].cevr";
connectAttr "girl_IKLeg_L_translateY1.a" "clipLibrary1.cel[0].cev[160].cevr";
connectAttr "girl_IKLeg_L_translateX1.a" "clipLibrary1.cel[0].cev[161].cevr";
connectAttr "girl_FKIKArm_L_IKVis1.a" "clipLibrary1.cel[0].cev[162].cevr";
connectAttr "girl_FKIKArm_L_FKVis1.a" "clipLibrary1.cel[0].cev[163].cevr";
connectAttr "girl_FKIKArm_L_FKIKBlend1.a" "clipLibrary1.cel[0].cev[164].cevr";
connectAttr "girl_PoleExtraArm_L_translateZ1.a" "clipLibrary1.cel[0].cev[165].cevr"
		;
connectAttr "girl_PoleExtraArm_L_translateY1.a" "clipLibrary1.cel[0].cev[166].cevr"
		;
connectAttr "girl_PoleExtraArm_L_translateX1.a" "clipLibrary1.cel[0].cev[167].cevr"
		;
connectAttr "girl_PoleArm_L_follow1.a" "clipLibrary1.cel[0].cev[168].cevr";
connectAttr "girl_PoleArm_L_translateZ1.a" "clipLibrary1.cel[0].cev[169].cevr";
connectAttr "girl_PoleArm_L_translateY1.a" "clipLibrary1.cel[0].cev[170].cevr";
connectAttr "girl_PoleArm_L_translateX1.a" "clipLibrary1.cel[0].cev[171].cevr";
connectAttr "girl_IKExtraArm_L_rotateZ1.a" "clipLibrary1.cel[0].cev[172].cevr";
connectAttr "girl_IKExtraArm_L_rotateY1.a" "clipLibrary1.cel[0].cev[173].cevr";
connectAttr "girl_IKExtraArm_L_rotateX1.a" "clipLibrary1.cel[0].cev[174].cevr";
connectAttr "girl_IKExtraArm_L_translateZ1.a" "clipLibrary1.cel[0].cev[175].cevr"
		;
connectAttr "girl_IKExtraArm_L_translateY1.a" "clipLibrary1.cel[0].cev[176].cevr"
		;
connectAttr "girl_IKExtraArm_L_translateX1.a" "clipLibrary1.cel[0].cev[177].cevr"
		;
connectAttr "girl_IKArm_L_Lenght4.a" "clipLibrary1.cel[0].cev[178].cevr";
connectAttr "girl_IKArm_L_Lenght3.a" "clipLibrary1.cel[0].cev[179].cevr";
connectAttr "girl_IKArm_L_antiPop1.a" "clipLibrary1.cel[0].cev[180].cevr";
connectAttr "girl_IKArm_L_stretchy1.a" "clipLibrary1.cel[0].cev[181].cevr";
connectAttr "girl_IKArm_L_follow1.a" "clipLibrary1.cel[0].cev[182].cevr";
connectAttr "girl_IKArm_L_rotateZ1.a" "clipLibrary1.cel[0].cev[183].cevr";
connectAttr "girl_IKArm_L_rotateY1.a" "clipLibrary1.cel[0].cev[184].cevr";
connectAttr "girl_IKArm_L_rotateX1.a" "clipLibrary1.cel[0].cev[185].cevr";
connectAttr "girl_IKArm_L_translateZ1.a" "clipLibrary1.cel[0].cev[186].cevr";
connectAttr "girl_IKArm_L_translateY1.a" "clipLibrary1.cel[0].cev[187].cevr";
connectAttr "girl_IKArm_L_translateX1.a" "clipLibrary1.cel[0].cev[188].cevr";
connectAttr "girl_Fingers_R_Cup1.a" "clipLibrary1.cel[0].cev[189].cevr";
connectAttr "girl_Fingers_R_Spread1.a" "clipLibrary1.cel[0].cev[190].cevr";
connectAttr "girl_Fingers_R_ThumbFingerCurl1.a" "clipLibrary1.cel[0].cev[191].cevr"
		;
connectAttr "girl_Fingers_R_PinkyFingerCurl1.a" "clipLibrary1.cel[0].cev[192].cevr"
		;
connectAttr "girl_Fingers_R_RingFingerCurl1.a" "clipLibrary1.cel[0].cev[193].cevr"
		;
connectAttr "girl_Fingers_R_MiddleFingerCurl1.a" "clipLibrary1.cel[0].cev[194].cevr"
		;
connectAttr "girl_Fingers_R_IndexFingerCurl1.a" "clipLibrary1.cel[0].cev[195].cevr"
		;
connectAttr "girl_IKExtraSpine4_M_scaleZ1.a" "clipLibrary1.cel[0].cev[196].cevr"
		;
connectAttr "girl_IKExtraSpine4_M_scaleY1.a" "clipLibrary1.cel[0].cev[197].cevr"
		;
connectAttr "girl_IKExtraSpine4_M_scaleX1.a" "clipLibrary1.cel[0].cev[198].cevr"
		;
connectAttr "girl_IKExtraSpine4_M_rotateZ1.a" "clipLibrary1.cel[0].cev[199].cevr"
		;
connectAttr "girl_IKExtraSpine4_M_rotateY1.a" "clipLibrary1.cel[0].cev[200].cevr"
		;
connectAttr "girl_IKExtraSpine4_M_rotateX1.a" "clipLibrary1.cel[0].cev[201].cevr"
		;
connectAttr "girl_IKExtraSpine4_M_translateZ1.a" "clipLibrary1.cel[0].cev[202].cevr"
		;
connectAttr "girl_IKExtraSpine4_M_translateY1.a" "clipLibrary1.cel[0].cev[203].cevr"
		;
connectAttr "girl_IKExtraSpine4_M_translateX1.a" "clipLibrary1.cel[0].cev[204].cevr"
		;
connectAttr "girl_IKExtraSpine4_M_visibility1.a" "clipLibrary1.cel[0].cev[205].cevr"
		;
connectAttr "girl_IKSpine4_M_stretchy1.a" "clipLibrary1.cel[0].cev[206].cevr";
connectAttr "girl_IKSpine4_M_stiff1.a" "clipLibrary1.cel[0].cev[207].cevr";
connectAttr "girl_IKSpine4_M_rotateZ1.a" "clipLibrary1.cel[0].cev[208].cevr";
connectAttr "girl_IKSpine4_M_rotateY1.a" "clipLibrary1.cel[0].cev[209].cevr";
connectAttr "girl_IKSpine4_M_rotateX1.a" "clipLibrary1.cel[0].cev[210].cevr";
connectAttr "girl_IKSpine4_M_translateZ1.a" "clipLibrary1.cel[0].cev[211].cevr";
connectAttr "girl_IKSpine4_M_translateY1.a" "clipLibrary1.cel[0].cev[212].cevr";
connectAttr "girl_IKSpine4_M_translateX1.a" "clipLibrary1.cel[0].cev[213].cevr";
connectAttr "girl_IKExtraSpine2_M_scaleZ1.a" "clipLibrary1.cel[0].cev[214].cevr"
		;
connectAttr "girl_IKExtraSpine2_M_scaleY1.a" "clipLibrary1.cel[0].cev[215].cevr"
		;
connectAttr "girl_IKExtraSpine2_M_scaleX1.a" "clipLibrary1.cel[0].cev[216].cevr"
		;
connectAttr "girl_IKExtraSpine2_M_rotateZ1.a" "clipLibrary1.cel[0].cev[217].cevr"
		;
connectAttr "girl_IKExtraSpine2_M_rotateY1.a" "clipLibrary1.cel[0].cev[218].cevr"
		;
connectAttr "girl_IKExtraSpine2_M_rotateX1.a" "clipLibrary1.cel[0].cev[219].cevr"
		;
connectAttr "girl_IKExtraSpine2_M_translateZ1.a" "clipLibrary1.cel[0].cev[220].cevr"
		;
connectAttr "girl_IKExtraSpine2_M_translateY1.a" "clipLibrary1.cel[0].cev[221].cevr"
		;
connectAttr "girl_IKExtraSpine2_M_translateX1.a" "clipLibrary1.cel[0].cev[222].cevr"
		;
connectAttr "girl_IKExtraSpine2_M_visibility1.a" "clipLibrary1.cel[0].cev[223].cevr"
		;
connectAttr "girl_IKSpine2_M_stiff1.a" "clipLibrary1.cel[0].cev[224].cevr";
connectAttr "girl_IKSpine2_M_rotateZ1.a" "clipLibrary1.cel[0].cev[225].cevr";
connectAttr "girl_IKSpine2_M_rotateY1.a" "clipLibrary1.cel[0].cev[226].cevr";
connectAttr "girl_IKSpine2_M_rotateX1.a" "clipLibrary1.cel[0].cev[227].cevr";
connectAttr "girl_IKSpine2_M_translateZ1.a" "clipLibrary1.cel[0].cev[228].cevr";
connectAttr "girl_IKSpine2_M_translateY1.a" "clipLibrary1.cel[0].cev[229].cevr";
connectAttr "girl_IKSpine2_M_translateX1.a" "clipLibrary1.cel[0].cev[230].cevr";
connectAttr "girl_IKExtraSpine0_M_scaleZ1.a" "clipLibrary1.cel[0].cev[231].cevr"
		;
connectAttr "girl_IKExtraSpine0_M_scaleY1.a" "clipLibrary1.cel[0].cev[232].cevr"
		;
connectAttr "girl_IKExtraSpine0_M_scaleX1.a" "clipLibrary1.cel[0].cev[233].cevr"
		;
connectAttr "girl_IKExtraSpine0_M_rotateZ1.a" "clipLibrary1.cel[0].cev[234].cevr"
		;
connectAttr "girl_IKExtraSpine0_M_rotateY1.a" "clipLibrary1.cel[0].cev[235].cevr"
		;
connectAttr "girl_IKExtraSpine0_M_rotateX1.a" "clipLibrary1.cel[0].cev[236].cevr"
		;
connectAttr "girl_IKExtraSpine0_M_translateZ1.a" "clipLibrary1.cel[0].cev[237].cevr"
		;
connectAttr "girl_IKExtraSpine0_M_translateY1.a" "clipLibrary1.cel[0].cev[238].cevr"
		;
connectAttr "girl_IKExtraSpine0_M_translateX1.a" "clipLibrary1.cel[0].cev[239].cevr"
		;
connectAttr "girl_IKExtraSpine0_M_visibility1.a" "clipLibrary1.cel[0].cev[240].cevr"
		;
connectAttr "girl_IKSpine0_M_stiff1.a" "clipLibrary1.cel[0].cev[241].cevr";
connectAttr "girl_IKSpine0_M_rotateZ1.a" "clipLibrary1.cel[0].cev[242].cevr";
connectAttr "girl_IKSpine0_M_rotateY1.a" "clipLibrary1.cel[0].cev[243].cevr";
connectAttr "girl_IKSpine0_M_rotateX1.a" "clipLibrary1.cel[0].cev[244].cevr";
connectAttr "girl_IKSpine0_M_translateZ1.a" "clipLibrary1.cel[0].cev[245].cevr";
connectAttr "girl_IKSpine0_M_translateY1.a" "clipLibrary1.cel[0].cev[246].cevr";
connectAttr "girl_IKSpine0_M_translateX1.a" "clipLibrary1.cel[0].cev[247].cevr";
connectAttr "girl_IKExtraLegBall_R_rotateZ1.a" "clipLibrary1.cel[0].cev[248].cevr"
		;
connectAttr "girl_IKExtraLegBall_R_rotateY1.a" "clipLibrary1.cel[0].cev[249].cevr"
		;
connectAttr "girl_IKExtraLegBall_R_rotateX1.a" "clipLibrary1.cel[0].cev[250].cevr"
		;
connectAttr "girl_IKLegBall_R_rotateX1.a" "clipLibrary1.cel[0].cev[251].cevr";
connectAttr "girl_IKExtraLegToe_R_rotateZ1.a" "clipLibrary1.cel[0].cev[252].cevr"
		;
connectAttr "girl_IKExtraLegToe_R_rotateY1.a" "clipLibrary1.cel[0].cev[253].cevr"
		;
connectAttr "girl_IKExtraLegToe_R_rotateX1.a" "clipLibrary1.cel[0].cev[254].cevr"
		;
connectAttr "girl_IKLegToe_R_rotateZ1.a" "clipLibrary1.cel[0].cev[255].cevr";
connectAttr "girl_IKLegToe_R_rotateY1.a" "clipLibrary1.cel[0].cev[256].cevr";
connectAttr "girl_IKLegToe_R_rotateX1.a" "clipLibrary1.cel[0].cev[257].cevr";
connectAttr "girl_IKExtraLegHeel_R_rotateZ1.a" "clipLibrary1.cel[0].cev[258].cevr"
		;
connectAttr "girl_IKExtraLegHeel_R_rotateY1.a" "clipLibrary1.cel[0].cev[259].cevr"
		;
connectAttr "girl_IKExtraLegHeel_R_rotateX1.a" "clipLibrary1.cel[0].cev[260].cevr"
		;
connectAttr "girl_IKLegHeel_R_rotateZ1.a" "clipLibrary1.cel[0].cev[261].cevr";
connectAttr "girl_IKLegHeel_R_rotateY1.a" "clipLibrary1.cel[0].cev[262].cevr";
connectAttr "girl_IKLegHeel_R_rotateX1.a" "clipLibrary1.cel[0].cev[263].cevr";
connectAttr "girl_FKIKLeg_R_IKVis1.a" "clipLibrary1.cel[0].cev[264].cevr";
connectAttr "girl_FKIKLeg_R_FKVis1.a" "clipLibrary1.cel[0].cev[265].cevr";
connectAttr "girl_FKIKLeg_R_FKIKBlend1.a" "clipLibrary1.cel[0].cev[266].cevr";
connectAttr "girl_PoleExtraLeg_R_translateZ1.a" "clipLibrary1.cel[0].cev[267].cevr"
		;
connectAttr "girl_PoleExtraLeg_R_translateY1.a" "clipLibrary1.cel[0].cev[268].cevr"
		;
connectAttr "girl_PoleExtraLeg_R_translateX1.a" "clipLibrary1.cel[0].cev[269].cevr"
		;
connectAttr "girl_PoleLeg_R_follow1.a" "clipLibrary1.cel[0].cev[270].cevr";
connectAttr "girl_PoleLeg_R_translateZ1.a" "clipLibrary1.cel[0].cev[271].cevr";
connectAttr "girl_PoleLeg_R_translateY1.a" "clipLibrary1.cel[0].cev[272].cevr";
connectAttr "girl_PoleLeg_R_translateX1.a" "clipLibrary1.cel[0].cev[273].cevr";
connectAttr "girl_IKExtraLeg_R_rotateZ1.a" "clipLibrary1.cel[0].cev[274].cevr";
connectAttr "girl_IKExtraLeg_R_rotateY1.a" "clipLibrary1.cel[0].cev[275].cevr";
connectAttr "girl_IKExtraLeg_R_rotateX1.a" "clipLibrary1.cel[0].cev[276].cevr";
connectAttr "girl_IKExtraLeg_R_translateZ1.a" "clipLibrary1.cel[0].cev[277].cevr"
		;
connectAttr "girl_IKExtraLeg_R_translateY1.a" "clipLibrary1.cel[0].cev[278].cevr"
		;
connectAttr "girl_IKExtraLeg_R_translateX1.a" "clipLibrary1.cel[0].cev[279].cevr"
		;
connectAttr "girl_IKLeg_R_Lenght4.a" "clipLibrary1.cel[0].cev[280].cevr";
connectAttr "girl_IKLeg_R_Lenght3.a" "clipLibrary1.cel[0].cev[281].cevr";
connectAttr "girl_IKLeg_R_antiPop1.a" "clipLibrary1.cel[0].cev[282].cevr";
connectAttr "girl_IKLeg_R_stretchy1.a" "clipLibrary1.cel[0].cev[283].cevr";
connectAttr "girl_IKLeg_R_rollAngle1.a" "clipLibrary1.cel[0].cev[284].cevr";
connectAttr "girl_IKLeg_R_roll1.a" "clipLibrary1.cel[0].cev[285].cevr";
connectAttr "girl_IKLeg_R_toe1.a" "clipLibrary1.cel[0].cev[286].cevr";
connectAttr "girl_IKLeg_R_swivel1.a" "clipLibrary1.cel[0].cev[287].cevr";
connectAttr "girl_IKLeg_R_rotateZ1.a" "clipLibrary1.cel[0].cev[288].cevr";
connectAttr "girl_IKLeg_R_rotateY1.a" "clipLibrary1.cel[0].cev[289].cevr";
connectAttr "girl_IKLeg_R_rotateX1.a" "clipLibrary1.cel[0].cev[290].cevr";
connectAttr "girl_IKLeg_R_translateZ1.a" "clipLibrary1.cel[0].cev[291].cevr";
connectAttr "girl_IKLeg_R_translateY1.a" "clipLibrary1.cel[0].cev[292].cevr";
connectAttr "girl_IKLeg_R_translateX1.a" "clipLibrary1.cel[0].cev[293].cevr";
connectAttr "girl_FKIKArm_R_IKVis1.a" "clipLibrary1.cel[0].cev[294].cevr";
connectAttr "girl_FKIKArm_R_FKVis1.a" "clipLibrary1.cel[0].cev[295].cevr";
connectAttr "girl_FKIKArm_R_FKIKBlend1.a" "clipLibrary1.cel[0].cev[296].cevr";
connectAttr "girl_PoleExtraArm_R_translateZ1.a" "clipLibrary1.cel[0].cev[297].cevr"
		;
connectAttr "girl_PoleExtraArm_R_translateY1.a" "clipLibrary1.cel[0].cev[298].cevr"
		;
connectAttr "girl_PoleExtraArm_R_translateX1.a" "clipLibrary1.cel[0].cev[299].cevr"
		;
connectAttr "girl_PoleArm_R_follow1.a" "clipLibrary1.cel[0].cev[300].cevr";
connectAttr "girl_PoleArm_R_translateZ1.a" "clipLibrary1.cel[0].cev[301].cevr";
connectAttr "girl_PoleArm_R_translateY1.a" "clipLibrary1.cel[0].cev[302].cevr";
connectAttr "girl_PoleArm_R_translateX1.a" "clipLibrary1.cel[0].cev[303].cevr";
connectAttr "girl_IKExtraArm_R_rotateZ1.a" "clipLibrary1.cel[0].cev[304].cevr";
connectAttr "girl_IKExtraArm_R_rotateY1.a" "clipLibrary1.cel[0].cev[305].cevr";
connectAttr "girl_IKExtraArm_R_rotateX1.a" "clipLibrary1.cel[0].cev[306].cevr";
connectAttr "girl_IKExtraArm_R_translateZ1.a" "clipLibrary1.cel[0].cev[307].cevr"
		;
connectAttr "girl_IKExtraArm_R_translateY1.a" "clipLibrary1.cel[0].cev[308].cevr"
		;
connectAttr "girl_IKExtraArm_R_translateX1.a" "clipLibrary1.cel[0].cev[309].cevr"
		;
connectAttr "girl_IKArm_R_Lenght4.a" "clipLibrary1.cel[0].cev[310].cevr";
connectAttr "girl_IKArm_R_Lenght3.a" "clipLibrary1.cel[0].cev[311].cevr";
connectAttr "girl_IKArm_R_antiPop1.a" "clipLibrary1.cel[0].cev[312].cevr";
connectAttr "girl_IKArm_R_stretchy1.a" "clipLibrary1.cel[0].cev[313].cevr";
connectAttr "girl_IKArm_R_follow1.a" "clipLibrary1.cel[0].cev[314].cevr";
connectAttr "girl_IKArm_R_rotateZ1.a" "clipLibrary1.cel[0].cev[315].cevr";
connectAttr "girl_IKArm_R_rotateY1.a" "clipLibrary1.cel[0].cev[316].cevr";
connectAttr "girl_IKArm_R_rotateX1.a" "clipLibrary1.cel[0].cev[317].cevr";
connectAttr "girl_IKArm_R_translateZ1.a" "clipLibrary1.cel[0].cev[318].cevr";
connectAttr "girl_IKArm_R_translateY1.a" "clipLibrary1.cel[0].cev[319].cevr";
connectAttr "girl_IKArm_R_translateX1.a" "clipLibrary1.cel[0].cev[320].cevr";
connectAttr "girl_HipSwingerRoot_M_rotateZ1.a" "clipLibrary1.cel[0].cev[321].cevr"
		;
connectAttr "girl_HipSwingerRoot_M_rotateY1.a" "clipLibrary1.cel[0].cev[322].cevr"
		;
connectAttr "girl_HipSwingerRoot_M_rotateX1.a" "clipLibrary1.cel[0].cev[323].cevr"
		;
connectAttr "girl_FKExtraHip_L_rotateZ1.a" "clipLibrary1.cel[0].cev[324].cevr";
connectAttr "girl_FKExtraHip_L_rotateY1.a" "clipLibrary1.cel[0].cev[325].cevr";
connectAttr "girl_FKExtraHip_L_rotateX1.a" "clipLibrary1.cel[0].cev[326].cevr";
connectAttr "girl_FKHip_L_scaleZ1.a" "clipLibrary1.cel[0].cev[327].cevr";
connectAttr "girl_FKHip_L_scaleY1.a" "clipLibrary1.cel[0].cev[328].cevr";
connectAttr "girl_FKHip_L_scaleX1.a" "clipLibrary1.cel[0].cev[329].cevr";
connectAttr "girl_FKHip_L_rotateZ1.a" "clipLibrary1.cel[0].cev[330].cevr";
connectAttr "girl_FKHip_L_rotateY1.a" "clipLibrary1.cel[0].cev[331].cevr";
connectAttr "girl_FKHip_L_rotateX1.a" "clipLibrary1.cel[0].cev[332].cevr";
connectAttr "girl_FKExtraKnee_L_rotateZ1.a" "clipLibrary1.cel[0].cev[333].cevr";
connectAttr "girl_FKExtraKnee_L_rotateY1.a" "clipLibrary1.cel[0].cev[334].cevr";
connectAttr "girl_FKExtraKnee_L_rotateX1.a" "clipLibrary1.cel[0].cev[335].cevr";
connectAttr "girl_FKKnee_L_scaleZ1.a" "clipLibrary1.cel[0].cev[336].cevr";
connectAttr "girl_FKKnee_L_scaleY1.a" "clipLibrary1.cel[0].cev[337].cevr";
connectAttr "girl_FKKnee_L_scaleX1.a" "clipLibrary1.cel[0].cev[338].cevr";
connectAttr "girl_FKKnee_L_rotateZ1.a" "clipLibrary1.cel[0].cev[339].cevr";
connectAttr "girl_FKKnee_L_rotateY1.a" "clipLibrary1.cel[0].cev[340].cevr";
connectAttr "girl_FKKnee_L_rotateX1.a" "clipLibrary1.cel[0].cev[341].cevr";
connectAttr "girl_FKExtraAnkle_L_rotateZ1.a" "clipLibrary1.cel[0].cev[342].cevr"
		;
connectAttr "girl_FKExtraAnkle_L_rotateY1.a" "clipLibrary1.cel[0].cev[343].cevr"
		;
connectAttr "girl_FKExtraAnkle_L_rotateX1.a" "clipLibrary1.cel[0].cev[344].cevr"
		;
connectAttr "girl_FKAnkle_L_scaleZ1.a" "clipLibrary1.cel[0].cev[345].cevr";
connectAttr "girl_FKAnkle_L_scaleY1.a" "clipLibrary1.cel[0].cev[346].cevr";
connectAttr "girl_FKAnkle_L_scaleX1.a" "clipLibrary1.cel[0].cev[347].cevr";
connectAttr "girl_FKAnkle_L_rotateZ1.a" "clipLibrary1.cel[0].cev[348].cevr";
connectAttr "girl_FKAnkle_L_rotateY1.a" "clipLibrary1.cel[0].cev[349].cevr";
connectAttr "girl_FKAnkle_L_rotateX1.a" "clipLibrary1.cel[0].cev[350].cevr";
connectAttr "girl_FKExtraMiddleToe1_L_rotateZ1.a" "clipLibrary1.cel[0].cev[351].cevr"
		;
connectAttr "girl_FKExtraMiddleToe1_L_rotateY1.a" "clipLibrary1.cel[0].cev[352].cevr"
		;
connectAttr "girl_FKExtraMiddleToe1_L_rotateX1.a" "clipLibrary1.cel[0].cev[353].cevr"
		;
connectAttr "girl_FKMiddleToe1_L_scaleZ1.a" "clipLibrary1.cel[0].cev[354].cevr";
connectAttr "girl_FKMiddleToe1_L_scaleY1.a" "clipLibrary1.cel[0].cev[355].cevr";
connectAttr "girl_FKMiddleToe1_L_scaleX1.a" "clipLibrary1.cel[0].cev[356].cevr";
connectAttr "girl_FKMiddleToe1_L_rotateZ1.a" "clipLibrary1.cel[0].cev[357].cevr"
		;
connectAttr "girl_FKMiddleToe1_L_rotateY1.a" "clipLibrary1.cel[0].cev[358].cevr"
		;
connectAttr "girl_FKMiddleToe1_L_rotateX1.a" "clipLibrary1.cel[0].cev[359].cevr"
		;
connectAttr "girl_FKExtraScapula_L_scaleZ1.a" "clipLibrary1.cel[0].cev[360].cevr"
		;
connectAttr "girl_FKExtraScapula_L_scaleY1.a" "clipLibrary1.cel[0].cev[361].cevr"
		;
connectAttr "girl_FKExtraScapula_L_scaleX1.a" "clipLibrary1.cel[0].cev[362].cevr"
		;
connectAttr "girl_FKExtraScapula_L_rotateZ1.a" "clipLibrary1.cel[0].cev[363].cevr"
		;
connectAttr "girl_FKExtraScapula_L_rotateY1.a" "clipLibrary1.cel[0].cev[364].cevr"
		;
connectAttr "girl_FKExtraScapula_L_rotateX1.a" "clipLibrary1.cel[0].cev[365].cevr"
		;
connectAttr "girl_FKExtraScapula_L_translateZ1.a" "clipLibrary1.cel[0].cev[366].cevr"
		;
connectAttr "girl_FKExtraScapula_L_translateY1.a" "clipLibrary1.cel[0].cev[367].cevr"
		;
connectAttr "girl_FKExtraScapula_L_translateX1.a" "clipLibrary1.cel[0].cev[368].cevr"
		;
connectAttr "girl_FKScapula_L_scaleZ1.a" "clipLibrary1.cel[0].cev[369].cevr";
connectAttr "girl_FKScapula_L_scaleY1.a" "clipLibrary1.cel[0].cev[370].cevr";
connectAttr "girl_FKScapula_L_scaleX1.a" "clipLibrary1.cel[0].cev[371].cevr";
connectAttr "girl_FKScapula_L_rotateZ1.a" "clipLibrary1.cel[0].cev[372].cevr";
connectAttr "girl_FKScapula_L_rotateY1.a" "clipLibrary1.cel[0].cev[373].cevr";
connectAttr "girl_FKScapula_L_rotateX1.a" "clipLibrary1.cel[0].cev[374].cevr";
connectAttr "girl_FKScapula_L_translateZ1.a" "clipLibrary1.cel[0].cev[375].cevr"
		;
connectAttr "girl_FKScapula_L_translateY1.a" "clipLibrary1.cel[0].cev[376].cevr"
		;
connectAttr "girl_FKScapula_L_translateX1.a" "clipLibrary1.cel[0].cev[377].cevr"
		;
connectAttr "girl_FKExtraShoulder_L_rotateZ1.a" "clipLibrary1.cel[0].cev[378].cevr"
		;
connectAttr "girl_FKExtraShoulder_L_rotateY1.a" "clipLibrary1.cel[0].cev[379].cevr"
		;
connectAttr "girl_FKExtraShoulder_L_rotateX1.a" "clipLibrary1.cel[0].cev[380].cevr"
		;
connectAttr "girl_FKShoulder_L_scaleZ1.a" "clipLibrary1.cel[0].cev[381].cevr";
connectAttr "girl_FKShoulder_L_scaleY1.a" "clipLibrary1.cel[0].cev[382].cevr";
connectAttr "girl_FKShoulder_L_scaleX1.a" "clipLibrary1.cel[0].cev[383].cevr";
connectAttr "girl_FKShoulder_L_rotateZ1.a" "clipLibrary1.cel[0].cev[384].cevr";
connectAttr "girl_FKShoulder_L_rotateY1.a" "clipLibrary1.cel[0].cev[385].cevr";
connectAttr "girl_FKShoulder_L_rotateX1.a" "clipLibrary1.cel[0].cev[386].cevr";
connectAttr "girl_FKExtraElbow_L_rotateZ1.a" "clipLibrary1.cel[0].cev[387].cevr"
		;
connectAttr "girl_FKExtraElbow_L_rotateY1.a" "clipLibrary1.cel[0].cev[388].cevr"
		;
connectAttr "girl_FKExtraElbow_L_rotateX1.a" "clipLibrary1.cel[0].cev[389].cevr"
		;
connectAttr "girl_FKElbow_L_scaleZ1.a" "clipLibrary1.cel[0].cev[390].cevr";
connectAttr "girl_FKElbow_L_scaleY1.a" "clipLibrary1.cel[0].cev[391].cevr";
connectAttr "girl_FKElbow_L_scaleX1.a" "clipLibrary1.cel[0].cev[392].cevr";
connectAttr "girl_FKElbow_L_rotateZ2.a" "clipLibrary1.cel[0].cev[393].cevr";
connectAttr "girl_FKElbow_L_rotateY1.a" "clipLibrary1.cel[0].cev[394].cevr";
connectAttr "girl_FKElbow_L_rotateX2.a" "clipLibrary1.cel[0].cev[395].cevr";
connectAttr "girl_FKExtraWrist_L_rotateZ1.a" "clipLibrary1.cel[0].cev[396].cevr"
		;
connectAttr "girl_FKExtraWrist_L_rotateY1.a" "clipLibrary1.cel[0].cev[397].cevr"
		;
connectAttr "girl_FKExtraWrist_L_rotateX1.a" "clipLibrary1.cel[0].cev[398].cevr"
		;
connectAttr "girl_FKWrist_L_scaleZ1.a" "clipLibrary1.cel[0].cev[399].cevr";
connectAttr "girl_FKWrist_L_scaleY1.a" "clipLibrary1.cel[0].cev[400].cevr";
connectAttr "girl_FKWrist_L_scaleX1.a" "clipLibrary1.cel[0].cev[401].cevr";
connectAttr "girl_FKWrist_L_rotateZ1.a" "clipLibrary1.cel[0].cev[402].cevr";
connectAttr "girl_FKWrist_L_rotateY1.a" "clipLibrary1.cel[0].cev[403].cevr";
connectAttr "girl_FKWrist_L_rotateX1.a" "clipLibrary1.cel[0].cev[404].cevr";
connectAttr "girl_FKExtraMiddleFinger1_L_rotateZ1.a" "clipLibrary1.cel[0].cev[405].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger1_L_rotateY1.a" "clipLibrary1.cel[0].cev[406].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger1_L_rotateX1.a" "clipLibrary1.cel[0].cev[407].cevr"
		;
connectAttr "girl_FKMiddleFinger1_L_scaleZ1.a" "clipLibrary1.cel[0].cev[408].cevr"
		;
connectAttr "girl_FKMiddleFinger1_L_scaleY1.a" "clipLibrary1.cel[0].cev[409].cevr"
		;
connectAttr "girl_FKMiddleFinger1_L_scaleX1.a" "clipLibrary1.cel[0].cev[410].cevr"
		;
connectAttr "girl_FKMiddleFinger1_L_rotateZ1.a" "clipLibrary1.cel[0].cev[411].cevr"
		;
connectAttr "girl_FKMiddleFinger1_L_rotateY1.a" "clipLibrary1.cel[0].cev[412].cevr"
		;
connectAttr "girl_FKMiddleFinger1_L_rotateX1.a" "clipLibrary1.cel[0].cev[413].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger2_L_rotateZ1.a" "clipLibrary1.cel[0].cev[414].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger2_L_rotateY1.a" "clipLibrary1.cel[0].cev[415].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger2_L_rotateX1.a" "clipLibrary1.cel[0].cev[416].cevr"
		;
connectAttr "girl_FKMiddleFinger2_L_scaleZ1.a" "clipLibrary1.cel[0].cev[417].cevr"
		;
connectAttr "girl_FKMiddleFinger2_L_scaleY1.a" "clipLibrary1.cel[0].cev[418].cevr"
		;
connectAttr "girl_FKMiddleFinger2_L_scaleX1.a" "clipLibrary1.cel[0].cev[419].cevr"
		;
connectAttr "girl_FKMiddleFinger2_L_rotateZ1.a" "clipLibrary1.cel[0].cev[420].cevr"
		;
connectAttr "girl_FKMiddleFinger2_L_rotateY1.a" "clipLibrary1.cel[0].cev[421].cevr"
		;
connectAttr "girl_FKMiddleFinger2_L_rotateX1.a" "clipLibrary1.cel[0].cev[422].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger3_L_rotateZ1.a" "clipLibrary1.cel[0].cev[423].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger3_L_rotateY1.a" "clipLibrary1.cel[0].cev[424].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger3_L_rotateX1.a" "clipLibrary1.cel[0].cev[425].cevr"
		;
connectAttr "girl_FKMiddleFinger3_L_scaleZ1.a" "clipLibrary1.cel[0].cev[426].cevr"
		;
connectAttr "girl_FKMiddleFinger3_L_scaleY1.a" "clipLibrary1.cel[0].cev[427].cevr"
		;
connectAttr "girl_FKMiddleFinger3_L_scaleX1.a" "clipLibrary1.cel[0].cev[428].cevr"
		;
connectAttr "girl_FKMiddleFinger3_L_rotateZ1.a" "clipLibrary1.cel[0].cev[429].cevr"
		;
connectAttr "girl_FKMiddleFinger3_L_rotateY1.a" "clipLibrary1.cel[0].cev[430].cevr"
		;
connectAttr "girl_FKMiddleFinger3_L_rotateX1.a" "clipLibrary1.cel[0].cev[431].cevr"
		;
connectAttr "girl_FKExtraThumbFinger1_L_rotateZ1.a" "clipLibrary1.cel[0].cev[432].cevr"
		;
connectAttr "girl_FKExtraThumbFinger1_L_rotateY1.a" "clipLibrary1.cel[0].cev[433].cevr"
		;
connectAttr "girl_FKExtraThumbFinger1_L_rotateX1.a" "clipLibrary1.cel[0].cev[434].cevr"
		;
connectAttr "girl_FKThumbFinger1_L_scaleZ1.a" "clipLibrary1.cel[0].cev[435].cevr"
		;
connectAttr "girl_FKThumbFinger1_L_scaleY1.a" "clipLibrary1.cel[0].cev[436].cevr"
		;
connectAttr "girl_FKThumbFinger1_L_scaleX1.a" "clipLibrary1.cel[0].cev[437].cevr"
		;
connectAttr "girl_FKThumbFinger1_L_rotateZ1.a" "clipLibrary1.cel[0].cev[438].cevr"
		;
connectAttr "girl_FKThumbFinger1_L_rotateY1.a" "clipLibrary1.cel[0].cev[439].cevr"
		;
connectAttr "girl_FKThumbFinger1_L_rotateX1.a" "clipLibrary1.cel[0].cev[440].cevr"
		;
connectAttr "girl_FKExtraThumbFinger2_L_rotateZ1.a" "clipLibrary1.cel[0].cev[441].cevr"
		;
connectAttr "girl_FKExtraThumbFinger2_L_rotateY1.a" "clipLibrary1.cel[0].cev[442].cevr"
		;
connectAttr "girl_FKExtraThumbFinger2_L_rotateX1.a" "clipLibrary1.cel[0].cev[443].cevr"
		;
connectAttr "girl_FKThumbFinger2_L_scaleZ1.a" "clipLibrary1.cel[0].cev[444].cevr"
		;
connectAttr "girl_FKThumbFinger2_L_scaleY1.a" "clipLibrary1.cel[0].cev[445].cevr"
		;
connectAttr "girl_FKThumbFinger2_L_scaleX1.a" "clipLibrary1.cel[0].cev[446].cevr"
		;
connectAttr "girl_FKThumbFinger2_L_rotateZ1.a" "clipLibrary1.cel[0].cev[447].cevr"
		;
connectAttr "girl_FKThumbFinger2_L_rotateY1.a" "clipLibrary1.cel[0].cev[448].cevr"
		;
connectAttr "girl_FKThumbFinger2_L_rotateX1.a" "clipLibrary1.cel[0].cev[449].cevr"
		;
connectAttr "girl_FKExtraThumbFinger3_L_rotateZ1.a" "clipLibrary1.cel[0].cev[450].cevr"
		;
connectAttr "girl_FKExtraThumbFinger3_L_rotateY1.a" "clipLibrary1.cel[0].cev[451].cevr"
		;
connectAttr "girl_FKExtraThumbFinger3_L_rotateX1.a" "clipLibrary1.cel[0].cev[452].cevr"
		;
connectAttr "girl_FKThumbFinger3_L_scaleZ1.a" "clipLibrary1.cel[0].cev[453].cevr"
		;
connectAttr "girl_FKThumbFinger3_L_scaleY1.a" "clipLibrary1.cel[0].cev[454].cevr"
		;
connectAttr "girl_FKThumbFinger3_L_scaleX1.a" "clipLibrary1.cel[0].cev[455].cevr"
		;
connectAttr "girl_FKThumbFinger3_L_rotateZ1.a" "clipLibrary1.cel[0].cev[456].cevr"
		;
connectAttr "girl_FKThumbFinger3_L_rotateY1.a" "clipLibrary1.cel[0].cev[457].cevr"
		;
connectAttr "girl_FKThumbFinger3_L_rotateX1.a" "clipLibrary1.cel[0].cev[458].cevr"
		;
connectAttr "girl_FKExtraHip_R_rotateZ1.a" "clipLibrary1.cel[0].cev[459].cevr";
connectAttr "girl_FKExtraHip_R_rotateY1.a" "clipLibrary1.cel[0].cev[460].cevr";
connectAttr "girl_FKExtraHip_R_rotateX1.a" "clipLibrary1.cel[0].cev[461].cevr";
connectAttr "girl_FKHip_R_scaleZ1.a" "clipLibrary1.cel[0].cev[462].cevr";
connectAttr "girl_FKHip_R_scaleY1.a" "clipLibrary1.cel[0].cev[463].cevr";
connectAttr "girl_FKHip_R_scaleX1.a" "clipLibrary1.cel[0].cev[464].cevr";
connectAttr "girl_FKHip_R_rotateZ1.a" "clipLibrary1.cel[0].cev[465].cevr";
connectAttr "girl_FKHip_R_rotateY1.a" "clipLibrary1.cel[0].cev[466].cevr";
connectAttr "girl_FKHip_R_rotateX1.a" "clipLibrary1.cel[0].cev[467].cevr";
connectAttr "girl_FKExtraKnee_R_rotateZ1.a" "clipLibrary1.cel[0].cev[468].cevr";
connectAttr "girl_FKExtraKnee_R_rotateY1.a" "clipLibrary1.cel[0].cev[469].cevr";
connectAttr "girl_FKExtraKnee_R_rotateX1.a" "clipLibrary1.cel[0].cev[470].cevr";
connectAttr "girl_FKKnee_R_scaleZ1.a" "clipLibrary1.cel[0].cev[471].cevr";
connectAttr "girl_FKKnee_R_scaleY1.a" "clipLibrary1.cel[0].cev[472].cevr";
connectAttr "girl_FKKnee_R_scaleX1.a" "clipLibrary1.cel[0].cev[473].cevr";
connectAttr "girl_FKKnee_R_rotateZ1.a" "clipLibrary1.cel[0].cev[474].cevr";
connectAttr "girl_FKKnee_R_rotateY1.a" "clipLibrary1.cel[0].cev[475].cevr";
connectAttr "girl_FKKnee_R_rotateX1.a" "clipLibrary1.cel[0].cev[476].cevr";
connectAttr "girl_FKExtraAnkle_R_rotateZ1.a" "clipLibrary1.cel[0].cev[477].cevr"
		;
connectAttr "girl_FKExtraAnkle_R_rotateY1.a" "clipLibrary1.cel[0].cev[478].cevr"
		;
connectAttr "girl_FKExtraAnkle_R_rotateX1.a" "clipLibrary1.cel[0].cev[479].cevr"
		;
connectAttr "girl_FKAnkle_R_scaleZ1.a" "clipLibrary1.cel[0].cev[480].cevr";
connectAttr "girl_FKAnkle_R_scaleY1.a" "clipLibrary1.cel[0].cev[481].cevr";
connectAttr "girl_FKAnkle_R_scaleX1.a" "clipLibrary1.cel[0].cev[482].cevr";
connectAttr "girl_FKAnkle_R_rotateZ1.a" "clipLibrary1.cel[0].cev[483].cevr";
connectAttr "girl_FKAnkle_R_rotateY1.a" "clipLibrary1.cel[0].cev[484].cevr";
connectAttr "girl_FKAnkle_R_rotateX1.a" "clipLibrary1.cel[0].cev[485].cevr";
connectAttr "girl_FKExtraMiddleToe1_R_rotateZ1.a" "clipLibrary1.cel[0].cev[486].cevr"
		;
connectAttr "girl_FKExtraMiddleToe1_R_rotateY1.a" "clipLibrary1.cel[0].cev[487].cevr"
		;
connectAttr "girl_FKExtraMiddleToe1_R_rotateX1.a" "clipLibrary1.cel[0].cev[488].cevr"
		;
connectAttr "girl_FKMiddleToe1_R_scaleZ1.a" "clipLibrary1.cel[0].cev[489].cevr";
connectAttr "girl_FKMiddleToe1_R_scaleY1.a" "clipLibrary1.cel[0].cev[490].cevr";
connectAttr "girl_FKMiddleToe1_R_scaleX1.a" "clipLibrary1.cel[0].cev[491].cevr";
connectAttr "girl_FKMiddleToe1_R_rotateZ1.a" "clipLibrary1.cel[0].cev[492].cevr"
		;
connectAttr "girl_FKMiddleToe1_R_rotateY1.a" "clipLibrary1.cel[0].cev[493].cevr"
		;
connectAttr "girl_FKMiddleToe1_R_rotateX1.a" "clipLibrary1.cel[0].cev[494].cevr"
		;
connectAttr "girl_FKExtraBackA_M_rotateZ1.a" "clipLibrary1.cel[0].cev[495].cevr"
		;
connectAttr "girl_FKExtraBackA_M_rotateY1.a" "clipLibrary1.cel[0].cev[496].cevr"
		;
connectAttr "girl_FKExtraBackA_M_rotateX1.a" "clipLibrary1.cel[0].cev[497].cevr"
		;
connectAttr "girl_FKBackA_M_scaleZ1.a" "clipLibrary1.cel[0].cev[498].cevr";
connectAttr "girl_FKBackA_M_scaleY1.a" "clipLibrary1.cel[0].cev[499].cevr";
connectAttr "girl_FKBackA_M_scaleX1.a" "clipLibrary1.cel[0].cev[500].cevr";
connectAttr "girl_FKBackA_M_rotateZ1.a" "clipLibrary1.cel[0].cev[501].cevr";
connectAttr "girl_FKBackA_M_rotateY1.a" "clipLibrary1.cel[0].cev[502].cevr";
connectAttr "girl_FKBackA_M_rotateX1.a" "clipLibrary1.cel[0].cev[503].cevr";
connectAttr "girl_FKExtraBackB_M_rotateZ1.a" "clipLibrary1.cel[0].cev[504].cevr"
		;
connectAttr "girl_FKExtraBackB_M_rotateY1.a" "clipLibrary1.cel[0].cev[505].cevr"
		;
connectAttr "girl_FKExtraBackB_M_rotateX1.a" "clipLibrary1.cel[0].cev[506].cevr"
		;
connectAttr "girl_FKBackB_M_scaleZ1.a" "clipLibrary1.cel[0].cev[507].cevr";
connectAttr "girl_FKBackB_M_scaleY1.a" "clipLibrary1.cel[0].cev[508].cevr";
connectAttr "girl_FKBackB_M_scaleX1.a" "clipLibrary1.cel[0].cev[509].cevr";
connectAttr "girl_FKBackB_M_rotateZ1.a" "clipLibrary1.cel[0].cev[510].cevr";
connectAttr "girl_FKBackB_M_rotateY1.a" "clipLibrary1.cel[0].cev[511].cevr";
connectAttr "girl_FKBackB_M_rotateX1.a" "clipLibrary1.cel[0].cev[512].cevr";
connectAttr "girl_FKExtraChest_M_rotateZ1.a" "clipLibrary1.cel[0].cev[513].cevr"
		;
connectAttr "girl_FKExtraChest_M_rotateY1.a" "clipLibrary1.cel[0].cev[514].cevr"
		;
connectAttr "girl_FKExtraChest_M_rotateX1.a" "clipLibrary1.cel[0].cev[515].cevr"
		;
connectAttr "girl_FKChest_M_scaleZ1.a" "clipLibrary1.cel[0].cev[516].cevr";
connectAttr "girl_FKChest_M_scaleY1.a" "clipLibrary1.cel[0].cev[517].cevr";
connectAttr "girl_FKChest_M_scaleX1.a" "clipLibrary1.cel[0].cev[518].cevr";
connectAttr "girl_FKChest_M_rotateZ1.a" "clipLibrary1.cel[0].cev[519].cevr";
connectAttr "girl_FKChest_M_rotateY1.a" "clipLibrary1.cel[0].cev[520].cevr";
connectAttr "girl_FKChest_M_rotateX1.a" "clipLibrary1.cel[0].cev[521].cevr";
connectAttr "girl_FKExtraNeck_M_rotateZ1.a" "clipLibrary1.cel[0].cev[522].cevr";
connectAttr "girl_FKExtraNeck_M_rotateY1.a" "clipLibrary1.cel[0].cev[523].cevr";
connectAttr "girl_FKExtraNeck_M_rotateX1.a" "clipLibrary1.cel[0].cev[524].cevr";
connectAttr "girl_FKNeck_M_scaleZ1.a" "clipLibrary1.cel[0].cev[525].cevr";
connectAttr "girl_FKNeck_M_scaleY1.a" "clipLibrary1.cel[0].cev[526].cevr";
connectAttr "girl_FKNeck_M_scaleX1.a" "clipLibrary1.cel[0].cev[527].cevr";
connectAttr "girl_FKNeck_M_rotateZ1.a" "clipLibrary1.cel[0].cev[528].cevr";
connectAttr "girl_FKNeck_M_rotateY1.a" "clipLibrary1.cel[0].cev[529].cevr";
connectAttr "girl_FKNeck_M_rotateX1.a" "clipLibrary1.cel[0].cev[530].cevr";
connectAttr "girl_FKExtraHead_M_rotateZ1.a" "clipLibrary1.cel[0].cev[531].cevr";
connectAttr "girl_FKExtraHead_M_rotateY1.a" "clipLibrary1.cel[0].cev[532].cevr";
connectAttr "girl_FKExtraHead_M_rotateX1.a" "clipLibrary1.cel[0].cev[533].cevr";
connectAttr "girl_FKHead_M_scaleZ1.a" "clipLibrary1.cel[0].cev[534].cevr";
connectAttr "girl_FKHead_M_scaleY1.a" "clipLibrary1.cel[0].cev[535].cevr";
connectAttr "girl_FKHead_M_scaleX1.a" "clipLibrary1.cel[0].cev[536].cevr";
connectAttr "girl_FKHead_M_rotateZ1.a" "clipLibrary1.cel[0].cev[537].cevr";
connectAttr "girl_FKHead_M_rotateY1.a" "clipLibrary1.cel[0].cev[538].cevr";
connectAttr "girl_FKHead_M_rotateX1.a" "clipLibrary1.cel[0].cev[539].cevr";
connectAttr "girl_FKExtraScapula_R_scaleZ1.a" "clipLibrary1.cel[0].cev[540].cevr"
		;
connectAttr "girl_FKExtraScapula_R_scaleY1.a" "clipLibrary1.cel[0].cev[541].cevr"
		;
connectAttr "girl_FKExtraScapula_R_scaleX1.a" "clipLibrary1.cel[0].cev[542].cevr"
		;
connectAttr "girl_FKExtraScapula_R_rotateZ1.a" "clipLibrary1.cel[0].cev[543].cevr"
		;
connectAttr "girl_FKExtraScapula_R_rotateY1.a" "clipLibrary1.cel[0].cev[544].cevr"
		;
connectAttr "girl_FKExtraScapula_R_rotateX1.a" "clipLibrary1.cel[0].cev[545].cevr"
		;
connectAttr "girl_FKExtraScapula_R_translateZ1.a" "clipLibrary1.cel[0].cev[546].cevr"
		;
connectAttr "girl_FKExtraScapula_R_translateY1.a" "clipLibrary1.cel[0].cev[547].cevr"
		;
connectAttr "girl_FKExtraScapula_R_translateX1.a" "clipLibrary1.cel[0].cev[548].cevr"
		;
connectAttr "girl_FKScapula_R_scaleZ1.a" "clipLibrary1.cel[0].cev[549].cevr";
connectAttr "girl_FKScapula_R_scaleY1.a" "clipLibrary1.cel[0].cev[550].cevr";
connectAttr "girl_FKScapula_R_scaleX1.a" "clipLibrary1.cel[0].cev[551].cevr";
connectAttr "girl_FKScapula_R_rotateZ1.a" "clipLibrary1.cel[0].cev[552].cevr";
connectAttr "girl_FKScapula_R_rotateY1.a" "clipLibrary1.cel[0].cev[553].cevr";
connectAttr "girl_FKScapula_R_rotateX1.a" "clipLibrary1.cel[0].cev[554].cevr";
connectAttr "girl_FKScapula_R_translateZ1.a" "clipLibrary1.cel[0].cev[555].cevr"
		;
connectAttr "girl_FKScapula_R_translateY1.a" "clipLibrary1.cel[0].cev[556].cevr"
		;
connectAttr "girl_FKScapula_R_translateX1.a" "clipLibrary1.cel[0].cev[557].cevr"
		;
connectAttr "girl_FKExtraShoulder_R_rotateZ1.a" "clipLibrary1.cel[0].cev[558].cevr"
		;
connectAttr "girl_FKExtraShoulder_R_rotateY1.a" "clipLibrary1.cel[0].cev[559].cevr"
		;
connectAttr "girl_FKExtraShoulder_R_rotateX1.a" "clipLibrary1.cel[0].cev[560].cevr"
		;
connectAttr "girl_FKShoulder_R_scaleZ1.a" "clipLibrary1.cel[0].cev[561].cevr";
connectAttr "girl_FKShoulder_R_scaleY1.a" "clipLibrary1.cel[0].cev[562].cevr";
connectAttr "girl_FKShoulder_R_scaleX1.a" "clipLibrary1.cel[0].cev[563].cevr";
connectAttr "girl_FKShoulder_R_rotateZ1.a" "clipLibrary1.cel[0].cev[564].cevr";
connectAttr "girl_FKShoulder_R_rotateY1.a" "clipLibrary1.cel[0].cev[565].cevr";
connectAttr "girl_FKShoulder_R_rotateX1.a" "clipLibrary1.cel[0].cev[566].cevr";
connectAttr "girl_FKExtraElbow_R_rotateZ1.a" "clipLibrary1.cel[0].cev[567].cevr"
		;
connectAttr "girl_FKExtraElbow_R_rotateY1.a" "clipLibrary1.cel[0].cev[568].cevr"
		;
connectAttr "girl_FKExtraElbow_R_rotateX1.a" "clipLibrary1.cel[0].cev[569].cevr"
		;
connectAttr "girl_FKElbow_R_scaleZ1.a" "clipLibrary1.cel[0].cev[570].cevr";
connectAttr "girl_FKElbow_R_scaleY1.a" "clipLibrary1.cel[0].cev[571].cevr";
connectAttr "girl_FKElbow_R_scaleX1.a" "clipLibrary1.cel[0].cev[572].cevr";
connectAttr "girl_FKElbow_R_rotateZ2.a" "clipLibrary1.cel[0].cev[573].cevr";
connectAttr "girl_FKElbow_R_rotateY1.a" "clipLibrary1.cel[0].cev[574].cevr";
connectAttr "girl_FKElbow_R_rotateX2.a" "clipLibrary1.cel[0].cev[575].cevr";
connectAttr "girl_FKExtraWrist_R_rotateZ1.a" "clipLibrary1.cel[0].cev[576].cevr"
		;
connectAttr "girl_FKExtraWrist_R_rotateY1.a" "clipLibrary1.cel[0].cev[577].cevr"
		;
connectAttr "girl_FKExtraWrist_R_rotateX1.a" "clipLibrary1.cel[0].cev[578].cevr"
		;
connectAttr "girl_FKWrist_R_scaleZ1.a" "clipLibrary1.cel[0].cev[579].cevr";
connectAttr "girl_FKWrist_R_scaleY1.a" "clipLibrary1.cel[0].cev[580].cevr";
connectAttr "girl_FKWrist_R_scaleX1.a" "clipLibrary1.cel[0].cev[581].cevr";
connectAttr "girl_FKWrist_R_rotateZ1.a" "clipLibrary1.cel[0].cev[582].cevr";
connectAttr "girl_FKWrist_R_rotateY1.a" "clipLibrary1.cel[0].cev[583].cevr";
connectAttr "girl_FKWrist_R_rotateX1.a" "clipLibrary1.cel[0].cev[584].cevr";
connectAttr "girl_FKExtraMiddleFinger1_R_rotateZ1.a" "clipLibrary1.cel[0].cev[585].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger1_R_rotateY1.a" "clipLibrary1.cel[0].cev[586].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger1_R_rotateX1.a" "clipLibrary1.cel[0].cev[587].cevr"
		;
connectAttr "girl_FKMiddleFinger1_R_scaleZ1.a" "clipLibrary1.cel[0].cev[588].cevr"
		;
connectAttr "girl_FKMiddleFinger1_R_scaleY1.a" "clipLibrary1.cel[0].cev[589].cevr"
		;
connectAttr "girl_FKMiddleFinger1_R_scaleX1.a" "clipLibrary1.cel[0].cev[590].cevr"
		;
connectAttr "girl_FKMiddleFinger1_R_rotateZ1.a" "clipLibrary1.cel[0].cev[591].cevr"
		;
connectAttr "girl_FKMiddleFinger1_R_rotateY1.a" "clipLibrary1.cel[0].cev[592].cevr"
		;
connectAttr "girl_FKMiddleFinger1_R_rotateX1.a" "clipLibrary1.cel[0].cev[593].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger2_R_rotateZ1.a" "clipLibrary1.cel[0].cev[594].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger2_R_rotateY1.a" "clipLibrary1.cel[0].cev[595].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger2_R_rotateX1.a" "clipLibrary1.cel[0].cev[596].cevr"
		;
connectAttr "girl_FKMiddleFinger2_R_scaleZ1.a" "clipLibrary1.cel[0].cev[597].cevr"
		;
connectAttr "girl_FKMiddleFinger2_R_scaleY1.a" "clipLibrary1.cel[0].cev[598].cevr"
		;
connectAttr "girl_FKMiddleFinger2_R_scaleX1.a" "clipLibrary1.cel[0].cev[599].cevr"
		;
connectAttr "girl_FKMiddleFinger2_R_rotateZ1.a" "clipLibrary1.cel[0].cev[600].cevr"
		;
connectAttr "girl_FKMiddleFinger2_R_rotateY1.a" "clipLibrary1.cel[0].cev[601].cevr"
		;
connectAttr "girl_FKMiddleFinger2_R_rotateX1.a" "clipLibrary1.cel[0].cev[602].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger3_R_rotateZ1.a" "clipLibrary1.cel[0].cev[603].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger3_R_rotateY1.a" "clipLibrary1.cel[0].cev[604].cevr"
		;
connectAttr "girl_FKExtraMiddleFinger3_R_rotateX1.a" "clipLibrary1.cel[0].cev[605].cevr"
		;
connectAttr "girl_FKMiddleFinger3_R_scaleZ1.a" "clipLibrary1.cel[0].cev[606].cevr"
		;
connectAttr "girl_FKMiddleFinger3_R_scaleY1.a" "clipLibrary1.cel[0].cev[607].cevr"
		;
connectAttr "girl_FKMiddleFinger3_R_scaleX1.a" "clipLibrary1.cel[0].cev[608].cevr"
		;
connectAttr "girl_FKMiddleFinger3_R_rotateZ1.a" "clipLibrary1.cel[0].cev[609].cevr"
		;
connectAttr "girl_FKMiddleFinger3_R_rotateY1.a" "clipLibrary1.cel[0].cev[610].cevr"
		;
connectAttr "girl_FKMiddleFinger3_R_rotateX1.a" "clipLibrary1.cel[0].cev[611].cevr"
		;
connectAttr "girl_FKExtraThumbFinger1_R_rotateZ1.a" "clipLibrary1.cel[0].cev[612].cevr"
		;
connectAttr "girl_FKExtraThumbFinger1_R_rotateY1.a" "clipLibrary1.cel[0].cev[613].cevr"
		;
connectAttr "girl_FKExtraThumbFinger1_R_rotateX1.a" "clipLibrary1.cel[0].cev[614].cevr"
		;
connectAttr "girl_FKThumbFinger1_R_scaleZ1.a" "clipLibrary1.cel[0].cev[615].cevr"
		;
connectAttr "girl_FKThumbFinger1_R_scaleY1.a" "clipLibrary1.cel[0].cev[616].cevr"
		;
connectAttr "girl_FKThumbFinger1_R_scaleX1.a" "clipLibrary1.cel[0].cev[617].cevr"
		;
connectAttr "girl_FKThumbFinger1_R_rotateZ1.a" "clipLibrary1.cel[0].cev[618].cevr"
		;
connectAttr "girl_FKThumbFinger1_R_rotateY1.a" "clipLibrary1.cel[0].cev[619].cevr"
		;
connectAttr "girl_FKThumbFinger1_R_rotateX1.a" "clipLibrary1.cel[0].cev[620].cevr"
		;
connectAttr "girl_FKExtraThumbFinger2_R_rotateZ1.a" "clipLibrary1.cel[0].cev[621].cevr"
		;
connectAttr "girl_FKExtraThumbFinger2_R_rotateY1.a" "clipLibrary1.cel[0].cev[622].cevr"
		;
connectAttr "girl_FKExtraThumbFinger2_R_rotateX1.a" "clipLibrary1.cel[0].cev[623].cevr"
		;
connectAttr "girl_FKThumbFinger2_R_scaleZ1.a" "clipLibrary1.cel[0].cev[624].cevr"
		;
connectAttr "girl_FKThumbFinger2_R_scaleY1.a" "clipLibrary1.cel[0].cev[625].cevr"
		;
connectAttr "girl_FKThumbFinger2_R_scaleX1.a" "clipLibrary1.cel[0].cev[626].cevr"
		;
connectAttr "girl_FKThumbFinger2_R_rotateZ1.a" "clipLibrary1.cel[0].cev[627].cevr"
		;
connectAttr "girl_FKThumbFinger2_R_rotateY1.a" "clipLibrary1.cel[0].cev[628].cevr"
		;
connectAttr "girl_FKThumbFinger2_R_rotateX1.a" "clipLibrary1.cel[0].cev[629].cevr"
		;
connectAttr "girl_FKExtraThumbFinger3_R_rotateZ1.a" "clipLibrary1.cel[0].cev[630].cevr"
		;
connectAttr "girl_FKExtraThumbFinger3_R_rotateY1.a" "clipLibrary1.cel[0].cev[631].cevr"
		;
connectAttr "girl_FKExtraThumbFinger3_R_rotateX1.a" "clipLibrary1.cel[0].cev[632].cevr"
		;
connectAttr "girl_FKThumbFinger3_R_scaleZ1.a" "clipLibrary1.cel[0].cev[633].cevr"
		;
connectAttr "girl_FKThumbFinger3_R_scaleY1.a" "clipLibrary1.cel[0].cev[634].cevr"
		;
connectAttr "girl_FKThumbFinger3_R_scaleX1.a" "clipLibrary1.cel[0].cev[635].cevr"
		;
connectAttr "girl_FKThumbFinger3_R_rotateZ1.a" "clipLibrary1.cel[0].cev[636].cevr"
		;
connectAttr "girl_FKThumbFinger3_R_rotateY1.a" "clipLibrary1.cel[0].cev[637].cevr"
		;
connectAttr "girl_FKThumbFinger3_R_rotateX1.a" "clipLibrary1.cel[0].cev[638].cevr"
		;
connectAttr "girl_Group_scaleZ2.a" "clipLibrary1.cel[0].cev[639].cevr";
connectAttr "girl_Group_scaleY2.a" "clipLibrary1.cel[0].cev[640].cevr";
connectAttr "girl_Group_scaleX2.a" "clipLibrary1.cel[0].cev[641].cevr";
connectAttr "girl_Group_rotateZ2.a" "clipLibrary1.cel[0].cev[642].cevr";
connectAttr "girl_Group_rotateY2.a" "clipLibrary1.cel[0].cev[643].cevr";
connectAttr "girl_Group_rotateX2.a" "clipLibrary1.cel[0].cev[644].cevr";
connectAttr "girl_Group_translateZ2.a" "clipLibrary1.cel[0].cev[645].cevr";
connectAttr "girl_Group_translateY2.a" "clipLibrary1.cel[0].cev[646].cevr";
connectAttr "girl_Group_translateX2.a" "clipLibrary1.cel[0].cev[647].cevr";
connectAttr "girl_Group_visibility2.a" "clipLibrary1.cel[0].cev[648].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr ":defaultLightSet.msg" "_FemaleOldAnimating:lightLinker1.slnk[0].sllk"
		;
connectAttr ":initialShadingGroup.msg" "_FemaleOldAnimating:lightLinker1.slnk[0].solk"
		;
connectAttr ":defaultLightSet.msg" "_FemaleOldAnimating:lightLinker1.slnk[1].sllk"
		;
connectAttr ":initialParticleSE.msg" "_FemaleOldAnimating:lightLinker1.slnk[1].solk"
		;
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
connectAttr "_FemaleOldAnimating:lightLinker1.msg" ":lightList1.ln" -na;
// End of Minigame2_applause.ma
