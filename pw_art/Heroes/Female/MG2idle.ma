//Maya ASCII 2008 scene
//Name: Minigame2_idle.ma
//Last modified: Wed, Nov 25, 2009 09:22:42 AM
//Codeset: 1251
requires maya "2008";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Unlimited 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200802250025-718075";
fileInfo "osv" "Microsoft Windows XP Service Pack 3 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 587 ".cel[0].cev";
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
createNode animClip -n "Minigame2_idleSource1";
	setAttr ".ihi" 0;
	setAttr -s 587 ".ac";
	setAttr ".ac[0:2]" yes yes yes;
	setAttr ".ac[39:41]" yes yes yes;
	setAttr ".ac[54:392]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
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
		yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[394]" yes;
	setAttr ".ac[396:572]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[574]" yes;
	setAttr ".ac[576:638]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes;
	setAttr ".se" 154;
	setAttr ".ci" no;
createNode animCurveTA -n "animCurveTA2304";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -35.107866749865821;
createNode animCurveTA -n "animCurveTA2305";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2306";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL793";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL794";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL795";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2307";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 2.6938795240000002;
createNode animCurveTA -n "animCurveTA2308";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -12.34267912;
createNode animCurveTA -n "animCurveTA2309";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 7.3397129640000003;
createNode animCurveTL -n "animCurveTL796";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.1506711017;
createNode animCurveTL -n "animCurveTL797";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.38782462150000002;
createNode animCurveTL -n "animCurveTL798";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.1917065708;
createNode animCurveTA -n "animCurveTA2310";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 20.53671496225779;
createNode animCurveTA -n "animCurveTA2311";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.6805989200445988;
createNode animCurveTA -n "animCurveTA2312";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 2.2467402642753678;
createNode animCurveTL -n "animCurveTL799";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL800";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL801";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2313";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.96208267017540849;
createNode animCurveTA -n "animCurveTA2314";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2315";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL802";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.089153431075066639;
createNode animCurveTL -n "animCurveTL803";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.20970195830660243;
createNode animCurveTL -n "animCurveTL804";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.0068805126335673514;
createNode animCurveTA -n "animCurveTA2316";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2317";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2318";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL805";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL806";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL807";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2319";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2320";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2321";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL808";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.01408065876666875;
createNode animCurveTL -n "animCurveTL809";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.0059453893140569321;
createNode animCurveTL -n "animCurveTL810";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.0013409990355031896;
createNode animCurveTA -n "animCurveTA2322";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 6.6401439613358022;
createNode animCurveTA -n "animCurveTA2323";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -10.419421379939381;
createNode animCurveTA -n "animCurveTA2324";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -3.6296225312594381;
createNode animCurveTL -n "animCurveTL811";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL812";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL813";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2325";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.059443428019813609;
createNode animCurveTA -n "animCurveTA2326";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.12010888458262685;
createNode animCurveTA -n "animCurveTA2327";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.58331804034238477;
createNode animCurveTL -n "animCurveTL814";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.028480309728328882;
createNode animCurveTL -n "animCurveTL815";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.0036166365236135014;
createNode animCurveTL -n "animCurveTL816";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.0362163539759899;
createNode animCurveTU -n "animCurveTU1263";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2328";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -38.239471219814469;
createNode animCurveTA -n "animCurveTA2329";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2330";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 7.8960619584932568;
createNode animCurveTL -n "animCurveTL817";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.68530052330451496;
createNode animCurveTL -n "animCurveTL818";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.65142083148962104;
createNode animCurveTL -n "animCurveTL819";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.52813520669109548;
createNode animCurveTA -n "animCurveTA2331";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2332";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2333";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL820";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL821";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL822";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1264";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1265";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1266";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1267";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1268";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1269";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1270";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2334";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2335";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2336";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2337";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2338";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2339";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2340";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2341";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2342";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2343";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2344";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2345";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2346";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2347";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2348";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2349";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1271";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU1272";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU1273";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL823";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL824";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL825";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1274";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 10;
createNode animCurveTL -n "animCurveTL826";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL827";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL828";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2350";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2351";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2352";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL829";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL830";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL831";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1275";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1276";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1277";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1278";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1279";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 25;
createNode animCurveTU -n "animCurveTU1280";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1281";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1282";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2353";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2354";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2355";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL832";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL833";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL834";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1283";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU1284";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU1285";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 10;
createNode animCurveTL -n "animCurveTL835";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL836";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL837";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1286";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL838";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL839";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL840";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2356";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2357";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2358";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL841";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL842";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL843";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1287";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1288";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1289";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1290";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1291";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2359";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -64.016326996178236;
createNode animCurveTA -n "animCurveTA2360";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -21.201885601093959;
createNode animCurveTA -n "animCurveTA2361";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 23.577065824573946;
createNode animCurveTL -n "animCurveTL844";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.1147649494746448;
createNode animCurveTL -n "animCurveTL845";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.78014303228689219;
createNode animCurveTL -n "animCurveTL846";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.21085409327663884;
createNode animCurveTU -n "animCurveTU1292";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1293";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1294";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1295";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1296";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1297";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1298";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1299";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1300";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1301";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA2362";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2363";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2364";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL847";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL848";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL849";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1302";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU1303";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 10;
createNode animCurveTU -n "animCurveTU1304";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2365";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2366";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2367";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL850";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL851";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL852";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1305";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1306";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1307";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA2368";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2369";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2370";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL853";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL854";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL855";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1308";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU1309";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2371";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2372";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2373";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL856";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL857";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL858";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1310";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1311";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1312";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA2374";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2375";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2376";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL859";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL860";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL861";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1313";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU1314";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2377";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2378";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2379";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL862";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL863";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL864";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2380";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2381";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2382";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2383";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2384";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2385";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2386";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2387";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2388";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2389";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2390";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2391";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2392";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2393";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2394";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2395";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1315";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU1316";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU1317";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL865";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL866";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL867";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1318";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 10;
createNode animCurveTL -n "animCurveTL868";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL869";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL870";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2396";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2397";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2398";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL871";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL872";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL873";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1319";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1320";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1321";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1322";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1323";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 25;
createNode animCurveTU -n "animCurveTU1324";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1325";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1326";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2399";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2400";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2401";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL874";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL875";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL876";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1327";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU1328";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU1329";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 10;
createNode animCurveTL -n "animCurveTL877";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL878";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL879";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1330";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL880";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.8324655288625988;
createNode animCurveTL -n "animCurveTL881";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.5248853769364021;
createNode animCurveTL -n "animCurveTL882";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.72634564248961153;
createNode animCurveTA -n "animCurveTA2402";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2403";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2404";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL883";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL884";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL885";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1331";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1332";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1333";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1334";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1335";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2405";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 74.385551548658 98 74.086510953575981 
		104 74.633168565489328 110 75.21406770801579 116 74.500646806467827 122 73.902568404421871 
		128 74.633168565489328 134 75.21406770801579 140 74.500646806467827 146 73.902568404421871 
		154 74.385551548658;
	setAttr -s 11 ".kit[0:10]"  3 3 9 9 9 9 9 9 
		9 1 9;
	setAttr -s 11 ".kot[0:10]"  3 3 9 9 9 9 1 9 
		9 9 9;
	setAttr -s 11 ".kix[9:10]"  0.99864077568054199 0.99950069189071655;
	setAttr -s 11 ".kiy[9:10]"  -0.052121296525001526 0.031595420092344284;
	setAttr -s 11 ".kox[6:10]"  0.99879199266433716 0.99998331069946289 
		0.99836665391921997 0.99999082088470459 0.99950069189071655;
	setAttr -s 11 ".koy[6:10]"  0.049139529466629028 -0.0057822614908218384 
		-0.05713147297501564 -0.004304512869566679 0.031595420092344284;
createNode animCurveTA -n "animCurveTA2406";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 18.642817836503916 98 18.380159881921383 
		104 23.885262090250514 110 26.229327772188952 116 23.533283042503154 122 17.664715798514674 
		128 23.885262090250514 134 26.229327772188952 140 23.533283042503154 146 17.664715798514674 
		154 18.642817836503916;
	setAttr -s 11 ".kit[0:10]"  3 3 9 9 9 9 9 9 
		9 1 9;
	setAttr -s 11 ".kot[0:10]"  3 3 9 9 9 9 1 9 
		9 9 9;
	setAttr -s 11 ".kix[9:10]"  0.89006704092025757 0.99795722961425781;
	setAttr -s 11 ".kiy[9:10]"  -0.4558296799659729 0.063885919749736786;
	setAttr -s 11 ".kox[6:10]"  0.94605404138565063 0.99988210201263428 
		0.93672841787338257 0.98368155956268311 0.99795722961425781;
	setAttr -s 11 ".koy[6:10]"  0.3240090012550354 -0.015356187708675861 
		-0.35005691647529602 -0.17991827428340912 0.063885919749736786;
createNode animCurveTA -n "animCurveTA2407";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 2.8749941738113645 98 2.7712635215742765 
		104 -6.7671828925936088 110 -11.086777882693578 116 -6.091975123430764 122 4.0654494630489948 
		128 -6.7671828925936088 134 -11.086777882693578 140 -6.091975123430764 146 4.0654494630489948 
		154 2.8749941738113645;
	setAttr -s 11 ".kit[0:10]"  3 3 9 9 9 9 9 9 
		9 1 9;
	setAttr -s 11 ".kot[0:10]"  3 3 9 9 9 9 1 9 
		9 9 9;
	setAttr -s 11 ".kix[9:10]"  0.74833220243453979 0.99697834253311157;
	setAttr -s 11 ".kiy[9:10]"  0.66332417726516724 -0.077679760754108429;
	setAttr -s 11 ".kox[6:10]"  0.8557242751121521 0.99956625699996948 
		0.83417177200317383 0.94810408353805542 0.99697834253311157;
	setAttr -s 11 ".koy[6:10]"  -0.51743197441101074 0.029448747634887695 
		0.55150473117828369 0.31795981526374817 -0.077679760754108429;
createNode animCurveTL -n "animCurveTL886";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.79868788221471698 154 -0.79868788221471698;
createNode animCurveTL -n "animCurveTL887";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -1.1467822548654889 154 -1.1467822548654889;
createNode animCurveTL -n "animCurveTL888";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.1096578498486085 154 1.1096578498486085;
createNode animCurveTA -n "animCurveTA2408";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2409";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2410";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2411";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2412";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2413";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1336";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU1337";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1338";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000004;
createNode animCurveTA -n "animCurveTA2414";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -93.148410662823451 17 -94.270841943172854 
		36 -93.432215289842148 56 -94.270841943172854 77 -93.148410662823451;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 9 1 3;
	setAttr -s 5 ".kox[3:4]"  0.99998927116394043 1;
	setAttr -s 5 ".koy[3:4]"  -0.0046436921693384647 0;
createNode animCurveTA -n "animCurveTA2415";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.087147345469543197 77 -0.087147345469543197;
createNode animCurveTA -n "animCurveTA2416";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -15.275860387989701 77 -15.275860387989701;
createNode animCurveTA -n "animCurveTA2417";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2418";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2419";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1339";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU1340";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999967;
createNode animCurveTU -n "animCurveTU1341";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA2420";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 83.913182451591126 29 81.27348790971881 
		50 85.200597913796699 68 81.304532556914793 84 87.296137121418965 105 83.913;
	setAttr -s 6 ".kit[4:5]"  3 3;
	setAttr -s 6 ".kot[4:5]"  3 3;
createNode animCurveTA -n "animCurveTA2421";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.6823378597082943;
createNode animCurveTA -n "animCurveTA2422";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 5.0280589807764775;
createNode animCurveTA -n "animCurveTA2423";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2424";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2425";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1342";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000004;
createNode animCurveTU -n "animCurveTU1343";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTU -n "animCurveTU1344";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTA -n "animCurveTA2426";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2427";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 26.093661828935559;
createNode animCurveTA -n "animCurveTA2428";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2429";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2430";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2431";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1345";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000004;
createNode animCurveTU -n "animCurveTU1346";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1347";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000004;
createNode animCurveTA -n "animCurveTA2432";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 4.1383308710323172;
createNode animCurveTA -n "animCurveTA2433";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2434";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1348";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000004;
createNode animCurveTU -n "animCurveTU1349";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTU -n "animCurveTU1350";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA2435";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2436";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2437";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL889";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL890";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL891";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1351";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU1352";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU1353";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTA -n "animCurveTA2438";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -5.7485006011304165;
createNode animCurveTA -n "animCurveTA2439";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2440";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL892";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL893";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL894";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2441";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2442";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2443";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1354";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1355";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1356";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999978;
createNode animCurveTA -n "animCurveTA2444";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2445";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2446";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2447";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2448";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2449";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1357";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1358";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1359";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA2450";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2451";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2452";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2453";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1360";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1361";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1362";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTA -n "animCurveTA2454";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2455";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2456";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2457";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2458";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2459";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1363";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU1364";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU1365";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTA -n "animCurveTA2460";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 21.441017057914681;
createNode animCurveTA -n "animCurveTA2461";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2462";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2463";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2464";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2465";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1366";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999944;
createNode animCurveTU -n "animCurveTU1367";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999956;
createNode animCurveTU -n "animCurveTU1368";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999967;
createNode animCurveTA -n "animCurveTA2466";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2467";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2468";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2469";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2470";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2471";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1369";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU1370";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1371";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA2472";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2473";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2474";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2475";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2476";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2477";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1372";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU1373";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999978;
createNode animCurveTU -n "animCurveTU1374";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA2478";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -4.6159099816165661;
createNode animCurveTA -n "animCurveTA2479";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -20.292368692788873;
createNode animCurveTA -n "animCurveTA2480";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -6.2745051960127141;
createNode animCurveTA -n "animCurveTA2481";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2482";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2483";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1375";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999978;
createNode animCurveTU -n "animCurveTU1376";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999978;
createNode animCurveTU -n "animCurveTU1377";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999978;
createNode animCurveTA -n "animCurveTA2484";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2485";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2486";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2487";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2488";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2489";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1378";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000007;
createNode animCurveTU -n "animCurveTU1379";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000004;
createNode animCurveTU -n "animCurveTU1380";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTA -n "animCurveTA2490";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2491";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2492";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2493";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2494";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2495";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1381";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTU -n "animCurveTU1382";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU1383";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTA -n "animCurveTA2496";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -105.77848472630944;
createNode animCurveTA -n "animCurveTA2497";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -8.2096526943984909;
createNode animCurveTA -n "animCurveTA2498";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -8.1666847929670165;
createNode animCurveTA -n "animCurveTA2499";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2500";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2501";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1384";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU1385";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1386";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTA -n "animCurveTA2502";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 75.333348250175646 6 68.853348037741213 
		12 59.148334973596924 18 55.821467872510816 24 60.774110176360843 29 68.382198750953251 
		34 73.499989039227813 39 75.333348250175646 45 68.853348037741213 51 59.148334973596924 
		57 55.821467872510816 63 62.748232653449854 68 72.659464117979411 75 80.080397239986354 
		85 75.333;
	setAttr -s 15 ".kit[0:14]"  1 9 9 9 9 9 9 9 
		9 9 9 9 9 3 3;
	setAttr -s 15 ".kot[0:14]"  1 9 9 9 9 9 9 9 
		9 9 9 9 9 3 3;
	setAttr -s 15 ".kix[0:14]"  0.96864521503448486 0.81684392690658569 
		0.86929184198379517 0.99749338626861572 0.85829102993011475 0.83218127489089966 0.93969529867172241 
		0.9764021635055542 0.81684398651123047 0.86929172277450562 0.98788738250732422 0.78030258417129517 
		0.79759770631790161 1 1;
	setAttr -s 15 ".kiy[0:14]"  -0.24844813346862793 -0.5768587589263916 
		-0.49429935216903687 0.070760011672973633 0.51316320896148682 0.55450361967086792 
		0.34201276302337646 -0.21596023440361023 -0.57685869932174683 -0.49429935216903687 
		0.15517263114452362 0.62540215253829956 0.60318982601165771 0 0;
	setAttr -s 15 ".kox[0:14]"  0.96864521503448486 0.81684392690658569 
		0.86929184198379517 0.99749338626861572 0.85829102993011475 0.83218127489089966 0.93969529867172241 
		0.9764021635055542 0.81684398651123047 0.86929172277450562 0.98788738250732422 0.78030258417129517 
		0.79759770631790161 1 1;
	setAttr -s 15 ".koy[0:14]"  -0.24844810366630554 -0.5768587589263916 
		-0.49429935216903687 0.070760011672973633 0.51316320896148682 0.55450361967086792 
		0.34201276302337646 -0.21596023440361023 -0.57685869932174683 -0.49429935216903687 
		0.15517263114452362 0.62540215253829956 0.60318982601165771 0 0;
createNode animCurveTA -n "animCurveTA2503";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 39 0 86 0;
	setAttr -s 3 ".kit[2]"  3;
	setAttr -s 3 ".kot[2]"  3;
createNode animCurveTA -n "animCurveTA2504";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 39 0 86 0;
	setAttr -s 3 ".kit[2]"  3;
	setAttr -s 3 ".kot[2]"  3;
createNode animCurveTA -n "animCurveTA2505";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2506";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2507";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1387";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTU -n "animCurveTU1388";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTU -n "animCurveTU1389";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTA -n "animCurveTA2508";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 39 0 86 0 105 0;
	setAttr -s 4 ".kit[2:3]"  3 9;
	setAttr -s 4 ".kot[2:3]"  3 9;
createNode animCurveTA -n "animCurveTA2509";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 17 ".ktv[0:16]"  0 23.040000415782014 6 31.536000049977744 
		12 27.228455201798468 18 18.343177954347258 24 6.7367746107723798 29 2.502818720080183 
		34 13.643833319936531 39 23.040000415782014 45 31.536000049977744 51 27.228455201798468 
		57 18.343177954347258 63 6.7367746107723798 68 2.502818720080183 73 13.643833319936531 
		80 21.693172761020723 91 16.961511049609598 102 23.040000415782014;
	setAttr -s 17 ".kit[0:16]"  1 9 9 9 9 9 9 9 
		9 9 9 9 9 1 3 9 3;
	setAttr -s 17 ".kot[0:16]"  1 9 9 9 9 9 9 9 
		9 9 9 9 9 1 3 9 3;
	setAttr -s 17 ".kix[0:16]"  0.57282507419586182 0.98370712995529175 
		0.86666452884674072 0.74547040462493896 0.79846453666687012 0.94039106369018555 0.68099373579025269 
		0.76131343841552734 0.98370712995529175 0.86666440963745117 0.74547028541564941 0.79846465587615967 
		0.9403911828994751 0.76604175567626953 1 0.99948668479919434 1;
	setAttr -s 17 ".kiy[0:16]"  0.81967765092849731 0.17977820336818695 
		-0.4988914430141449 -0.66653871536254883 -0.60204184055328369 0.34009501338005066 
		0.73228919506072998 0.64838409423828125 0.17977815866470337 -0.49889147281646729 
		-0.66653883457183838 -0.60204178094863892 0.34009489417076111 0.64279091358184814 
		0 0.032037969678640366 0;
	setAttr -s 17 ".kox[0:16]"  0.57282513380050659 0.98370712995529175 
		0.86666452884674072 0.74547040462493896 0.79846453666687012 0.94039106369018555 0.68099373579025269 
		0.76131343841552734 0.98370712995529175 0.86666440963745117 0.74547028541564941 0.79846465587615967 
		0.9403911828994751 0.76604163646697998 1 0.99948668479919434 1;
	setAttr -s 17 ".koy[0:16]"  0.81967759132385254 0.17977820336818695 
		-0.4988914430141449 -0.66653871536254883 -0.60204184055328369 0.34009501338005066 
		0.73228919506072998 0.64838409423828125 0.17977815866470337 -0.49889147281646729 
		-0.66653883457183838 -0.60204178094863892 0.34009489417076111 0.6427910327911377 
		0 0.032037969678640366 0;
createNode animCurveTA -n "animCurveTA2510";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 39 0 86 0 105 0;
	setAttr -s 4 ".kit[2:3]"  3 9;
	setAttr -s 4 ".kot[2:3]"  3 9;
createNode animCurveTA -n "animCurveTA2511";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2512";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2513";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1390";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1391";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1392";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA2514";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 12 -5.457657711941418 18 -7.2576576606054051 
		39 -9.9392333795734899e-017 45 0 51 -5.457657711941418 57 -7.2576576606054051 86 
		0;
	setAttr -s 9 ".kit[8]"  3;
	setAttr -s 9 ".kot[8]"  3;
createNode animCurveTA -n "animCurveTA2515";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 39 0 45 0 86 0;
	setAttr -s 5 ".kit[4]"  3;
	setAttr -s 5 ".kot[4]"  3;
createNode animCurveTA -n "animCurveTA2516";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0 39 0 45 0 86 0;
	setAttr -s 5 ".kit[4]"  3;
	setAttr -s 5 ".kot[4]"  3;
createNode animCurveTA -n "animCurveTA2517";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2518";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2519";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1393";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999967;
createNode animCurveTU -n "animCurveTU1394";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999944;
createNode animCurveTU -n "animCurveTU1395";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTA -n "animCurveTA2520";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -1.4940187201541966 20 -5.0384807231034232 
		38 -1.4940187201541966 56 -5.0384807231034232 75 -0.013394673533400082 95 -0.16548413164944667 
		115 -0.92699801969394247 136 -1.4268668500086024 154 -1.4940187201541966;
	setAttr -s 9 ".kit[8]"  3;
	setAttr -s 9 ".kot[8]"  3;
createNode animCurveTA -n "animCurveTA2521";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.21231936819650479 20 0.71515789866580981 
		38 0.21231936819650479 56 0.71515789866580981 75 -2.1166297511279715 95 -0.81806150636268149 
		115 0.64778697422103193 136 -2.2173355586440047 154 0.21231936819650479;
	setAttr -s 9 ".kit[8]"  3;
	setAttr -s 9 ".kot[8]"  3;
createNode animCurveTA -n "animCurveTA2522";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 8.0864829283442798 20 8.0577857673175437 
		38 8.0864829283442798 56 8.0577857673175437 75 16.349860126094711 95 20.049630857412652 
		115 15.521095065591366 136 9.4153312386211105 154 8.0864829283442798;
	setAttr -s 9 ".kit[0:8]"  3 9 9 3 9 9 9 9 
		3;
	setAttr -s 9 ".kot[0:8]"  3 9 9 3 9 9 9 9 
		3;
createNode animCurveTA -n "animCurveTA2523";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2524";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2525";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1396";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1397";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1398";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA2526";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -5.9919002747580032 20 -3.0354586948126059 
		38 -5.9919002747580032 56 -3.0354586948126059 75 -6.3209536666651598 136 -5.9919002747580032 
		154 -5.9919002747580032;
	setAttr -s 7 ".kit[6]"  3;
	setAttr -s 7 ".kot[6]"  3;
createNode animCurveTA -n "animCurveTA2527";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.0482071512878739 20 0.53177949262952107 
		38 1.0482071512878739 56 0.53177949262952107 75 1.4060714979123496 136 1.0482071512878739 
		154 1.0482071512878739;
	setAttr -s 7 ".kit[6]"  3;
	setAttr -s 7 ".kot[6]"  3;
createNode animCurveTA -n "animCurveTA2528";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 9.8867372438892591 20 9.9275087820028549 
		38 9.8867372438892591 56 9.9275087820028549 75 15.353788241146969 95 17.661934551903329 
		115 14.428584025029622 136 9.8867372438892591 154 9.8867372438892591;
	setAttr -s 9 ".kit[0:8]"  3 9 9 3 9 9 9 9 
		3;
	setAttr -s 9 ".kot[0:8]"  3 9 9 3 9 9 9 9 
		3;
createNode animCurveTA -n "animCurveTA2529";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2530";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2531";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1399";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1400";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1401";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA2532";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -4.0762394232620087;
createNode animCurveTA -n "animCurveTA2533";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2534";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2535";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2536";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2537";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1402";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1403";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000004;
createNode animCurveTU -n "animCurveTU1404";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTA -n "animCurveTA2538";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 3.3359955434418795 20 6.6703541435279146 
		43 2.8962578571418001 60 6.8253348134239085 75 3.3359955434418795;
createNode animCurveTA -n "animCurveTA2539";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTA -n "animCurveTA2540";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 7.9199999167549402 75 7.9199999167549402;
	setAttr -s 2 ".kit[1]"  9;
	setAttr -s 2 ".kot[1]"  9;
createNode animCurveTA -n "animCurveTA2541";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2542";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2543";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1405";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1406";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1407";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA2544";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 5.7727404330954437 24 4.5022782415350218 
		39 7.6013726251331102 47 5.7727404330954437 67 5.6950654962202787 87 3.0126450506440028 
		121 5.928669421841442 142 5.7727404330954437;
	setAttr -s 8 ".kit[0:7]"  3 9 9 3 9 9 9 3;
	setAttr -s 8 ".kot[0:7]"  3 9 9 3 9 9 9 3;
createNode animCurveTA -n "animCurveTA2545";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 47 0 67 3.6714649378608941 87 8.1556391549879343 
		121 6.3656103559114241 142 0;
	setAttr -s 6 ".kit[0:5]"  3 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  3 3 9 9 9 3;
createNode animCurveTA -n "animCurveTA2546";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 45.75470585545532 47 45.75470585545532 
		67 63.098389126846484 87 75.360091126304809 121 65.890359894192798 142 45.75470585545532;
	setAttr -s 6 ".kit[2:5]"  1 9 1 3;
	setAttr -s 6 ".kot[2:5]"  1 9 1 3;
	setAttr -s 6 ".kix[2:5]"  0.92250412702560425 0.9996337890625 0.94520747661590576 
		1;
	setAttr -s 6 ".kiy[2:5]"  0.38598728179931641 0.027061799541115761 
		-0.32647028565406799 0;
	setAttr -s 6 ".kox[2:5]"  0.92250412702560425 0.9996337890625 0.94520747661590576 
		1;
	setAttr -s 6 ".koy[2:5]"  0.38598728179931641 0.027061799541115761 
		-0.32647028565406799 0;
createNode animCurveTU -n "animCurveTU1408";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000004;
createNode animCurveTU -n "animCurveTU1409";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTU -n "animCurveTU1410";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000004;
createNode animCurveTA -n "animCurveTA2547";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2548";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2549";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL895";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL896";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL897";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1411";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU1412";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999956;
createNode animCurveTU -n "animCurveTU1413";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999922;
createNode animCurveTA -n "animCurveTA2550";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2551";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2552";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL898";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL899";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL900";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2553";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2554";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2555";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1414";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU1415";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTU -n "animCurveTU1416";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999978;
createNode animCurveTA -n "animCurveTA2556";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2557";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2558";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2559";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2560";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2561";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1417";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999967;
createNode animCurveTU -n "animCurveTU1418";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999956;
createNode animCurveTU -n "animCurveTU1419";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999978;
createNode animCurveTA -n "animCurveTA2562";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2563";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2564";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2565";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1420";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.999999999999999;
createNode animCurveTU -n "animCurveTU1421";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999933;
createNode animCurveTU -n "animCurveTU1422";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999922;
createNode animCurveTA -n "animCurveTA2566";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2567";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2568";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2569";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2570";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2571";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1423";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTU -n "animCurveTU1424";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999978;
createNode animCurveTU -n "animCurveTU1425";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999956;
createNode animCurveTA -n "animCurveTA2572";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 25 ".ktv[0:24]"  0 -9.8496280095381739 6 -6.2496278105122531 
		12 -0.48962757454664479 18 3.8303724691216492 24 -0.6225816515643372 29 -5.3025816988639338 
		34 -8.902581735273646 39 -10.736151079033149 45 -5.6961510281075514 51 0.42384903376372679 
		57 3.6638490664832482 63 -0.29615097349899611 68 -5.6961510280499308 73 -8.2161510535121174 
		86 -9.2961510643955645 98 -9.2961510643955645 104 -1.8045780398523845 110 6.015962322101907 
		116 4.9116745616156328 122 -18.79358448864879 128 -18.493781117564549 134 -5.725488682579658 
		140 -1.4554330664095316 148 -18.79358448864879 154 -9.8496280095381739;
	setAttr -s 25 ".kit[14:24]"  3 9 9 9 9 9 9 9 
		9 1 9;
	setAttr -s 25 ".kot[14:24]"  3 9 9 9 9 9 1 9 
		9 1 9;
	setAttr -s 25 ".kix[23:24]"  0.62588679790496826 0.78830796480178833;
	setAttr -s 25 ".kiy[23:24]"  -0.77991390228271484 0.6152808666229248;
	setAttr -s 25 ".kox[20:24]"  0.76591074466705322 0.80252033472061157 
		0.89843511581420898 0.62588679790496826 0.78830796480178833;
	setAttr -s 25 ".koy[20:24]"  0.64294701814651489 0.59662485122680664 
		-0.43910622596740723 -0.77991390228271484 0.6152808666229248;
createNode animCurveTA -n "animCurveTA2573";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -2.0984782587122006 98 -2.0984782587122006 
		148 -2.0984782587122006 154 -2.0984782587122006;
createNode animCurveTA -n "animCurveTA2574";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -1.156749226655551 98 -1.156749226655551 
		148 -1.156749226655551 154 -1.156749226655551;
createNode animCurveTA -n "animCurveTA2575";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2576";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2577";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1426";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999978;
createNode animCurveTU -n "animCurveTU1427";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999967;
createNode animCurveTU -n "animCurveTU1428";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999933;
createNode animCurveTA -n "animCurveTA2578";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -21.724355717678407 98 -21.724355717678407 
		104 -18.493781117564549 110 -2.4854887188137291 116 10.064566766154153 122 0.1749170480245491 
		128 -18.493781117564549 134 -2.4854887188137291 140 10.064566766154153 148 0.1749170480245491 
		154 -21.724355717678407;
	setAttr -s 11 ".kit[9:10]"  1 9;
	setAttr -s 11 ".kot[6:10]"  1 9 9 1 9;
	setAttr -s 11 ".kix[9:10]"  0.62588679790496826 0.46362906694412231;
	setAttr -s 11 ".kiy[9:10]"  -0.77991390228271484 -0.88602942228317261;
	setAttr -s 11 ".kox[6:10]"  0.76591074466705322 0.62588679790496826 
		0.99508637189865112 0.62588679790496826 0.46362906694412231;
	setAttr -s 11 ".koy[6:10]"  0.64294701814651489 0.77991390228271484 
		0.099010035395622253 -0.77991390228271484 -0.88602942228317261;
createNode animCurveTA -n "animCurveTA2579";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.54486597751175991 98 0.54486597751175991 
		148 0.54486597751175991 154 0.54486597751175991;
createNode animCurveTA -n "animCurveTA2580";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.57631240306333031 98 0.57631240306333031 
		148 0.57631240306333031 154 0.57631240306333031;
createNode animCurveTA -n "animCurveTA2581";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2582";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2583";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1429";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999944;
createNode animCurveTU -n "animCurveTU1430";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999978;
createNode animCurveTU -n "animCurveTU1431";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTA -n "animCurveTA2584";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2585";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2586";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2587";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2588";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2589";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1432";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU1433";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999956;
createNode animCurveTU -n "animCurveTU1434";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA2590";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 2.7359414572949285;
createNode animCurveTA -n "animCurveTA2591";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -18.208718700041828;
createNode animCurveTA -n "animCurveTA2592";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 36.374630818370996;
createNode animCurveTA -n "animCurveTA2593";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2594";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2595";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1435";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999967;
createNode animCurveTU -n "animCurveTU1436";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU1437";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTA -n "animCurveTA2596";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.0012879291189114;
createNode animCurveTA -n "animCurveTA2597";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.44921033998490534;
createNode animCurveTA -n "animCurveTA2598";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 24.800969063594167;
createNode animCurveTA -n "animCurveTA2599";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2600";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2601";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1438";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1439";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTU -n "animCurveTU1440";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTA -n "animCurveTA2602";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2603";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA2604";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode lightLinker -n "lightLinker1";
	setAttr -s 5 ".lnk";
	setAttr -s 5 ".slnk";
select -ne :time1;
	setAttr -av -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 107;
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
connectAttr "Minigame2_idleSource1.cl" "clipLibrary1.sc[0]";
connectAttr "animCurveTA2304.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "animCurveTA2305.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "animCurveTA2306.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "animCurveTL793.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "animCurveTL794.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "animCurveTL795.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "animCurveTA2307.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "animCurveTA2308.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "animCurveTA2309.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "animCurveTL796.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "animCurveTL797.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "animCurveTL798.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "animCurveTA2310.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "animCurveTA2311.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "animCurveTA2312.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "animCurveTL799.a" "clipLibrary1.cel[0].cev[63].cevr";
connectAttr "animCurveTL800.a" "clipLibrary1.cel[0].cev[64].cevr";
connectAttr "animCurveTL801.a" "clipLibrary1.cel[0].cev[65].cevr";
connectAttr "animCurveTA2313.a" "clipLibrary1.cel[0].cev[66].cevr";
connectAttr "animCurveTA2314.a" "clipLibrary1.cel[0].cev[67].cevr";
connectAttr "animCurveTA2315.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "animCurveTL802.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "animCurveTL803.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "animCurveTL804.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "animCurveTA2316.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "animCurveTA2317.a" "clipLibrary1.cel[0].cev[73].cevr";
connectAttr "animCurveTA2318.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "animCurveTL805.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "animCurveTL806.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "animCurveTL807.a" "clipLibrary1.cel[0].cev[77].cevr";
connectAttr "animCurveTA2319.a" "clipLibrary1.cel[0].cev[78].cevr";
connectAttr "animCurveTA2320.a" "clipLibrary1.cel[0].cev[79].cevr";
connectAttr "animCurveTA2321.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "animCurveTL808.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "animCurveTL809.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "animCurveTL810.a" "clipLibrary1.cel[0].cev[83].cevr";
connectAttr "animCurveTA2322.a" "clipLibrary1.cel[0].cev[84].cevr";
connectAttr "animCurveTA2323.a" "clipLibrary1.cel[0].cev[85].cevr";
connectAttr "animCurveTA2324.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "animCurveTL811.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "animCurveTL812.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "animCurveTL813.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr "animCurveTA2325.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "animCurveTA2326.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "animCurveTA2327.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "animCurveTL814.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "animCurveTL815.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "animCurveTL816.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "animCurveTU1263.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "animCurveTA2328.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "animCurveTA2329.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "animCurveTA2330.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "animCurveTL817.a" "clipLibrary1.cel[0].cev[100].cevr";
connectAttr "animCurveTL818.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "animCurveTL819.a" "clipLibrary1.cel[0].cev[102].cevr";
connectAttr "animCurveTA2331.a" "clipLibrary1.cel[0].cev[103].cevr";
connectAttr "animCurveTA2332.a" "clipLibrary1.cel[0].cev[104].cevr";
connectAttr "animCurveTA2333.a" "clipLibrary1.cel[0].cev[105].cevr";
connectAttr "animCurveTL820.a" "clipLibrary1.cel[0].cev[106].cevr";
connectAttr "animCurveTL821.a" "clipLibrary1.cel[0].cev[107].cevr";
connectAttr "animCurveTL822.a" "clipLibrary1.cel[0].cev[108].cevr";
connectAttr "animCurveTU1264.a" "clipLibrary1.cel[0].cev[109].cevr";
connectAttr "animCurveTU1265.a" "clipLibrary1.cel[0].cev[110].cevr";
connectAttr "animCurveTU1266.a" "clipLibrary1.cel[0].cev[111].cevr";
connectAttr "animCurveTU1267.a" "clipLibrary1.cel[0].cev[112].cevr";
connectAttr "animCurveTU1268.a" "clipLibrary1.cel[0].cev[113].cevr";
connectAttr "animCurveTU1269.a" "clipLibrary1.cel[0].cev[114].cevr";
connectAttr "animCurveTU1270.a" "clipLibrary1.cel[0].cev[115].cevr";
connectAttr "animCurveTA2334.a" "clipLibrary1.cel[0].cev[116].cevr";
connectAttr "animCurveTA2335.a" "clipLibrary1.cel[0].cev[117].cevr";
connectAttr "animCurveTA2336.a" "clipLibrary1.cel[0].cev[118].cevr";
connectAttr "animCurveTA2337.a" "clipLibrary1.cel[0].cev[119].cevr";
connectAttr "animCurveTA2338.a" "clipLibrary1.cel[0].cev[120].cevr";
connectAttr "animCurveTA2339.a" "clipLibrary1.cel[0].cev[121].cevr";
connectAttr "animCurveTA2340.a" "clipLibrary1.cel[0].cev[122].cevr";
connectAttr "animCurveTA2341.a" "clipLibrary1.cel[0].cev[123].cevr";
connectAttr "animCurveTA2342.a" "clipLibrary1.cel[0].cev[124].cevr";
connectAttr "animCurveTA2343.a" "clipLibrary1.cel[0].cev[125].cevr";
connectAttr "animCurveTA2344.a" "clipLibrary1.cel[0].cev[126].cevr";
connectAttr "animCurveTA2345.a" "clipLibrary1.cel[0].cev[127].cevr";
connectAttr "animCurveTA2346.a" "clipLibrary1.cel[0].cev[128].cevr";
connectAttr "animCurveTA2347.a" "clipLibrary1.cel[0].cev[129].cevr";
connectAttr "animCurveTA2348.a" "clipLibrary1.cel[0].cev[130].cevr";
connectAttr "animCurveTA2349.a" "clipLibrary1.cel[0].cev[131].cevr";
connectAttr "animCurveTU1271.a" "clipLibrary1.cel[0].cev[132].cevr";
connectAttr "animCurveTU1272.a" "clipLibrary1.cel[0].cev[133].cevr";
connectAttr "animCurveTU1273.a" "clipLibrary1.cel[0].cev[134].cevr";
connectAttr "animCurveTL823.a" "clipLibrary1.cel[0].cev[135].cevr";
connectAttr "animCurveTL824.a" "clipLibrary1.cel[0].cev[136].cevr";
connectAttr "animCurveTL825.a" "clipLibrary1.cel[0].cev[137].cevr";
connectAttr "animCurveTU1274.a" "clipLibrary1.cel[0].cev[138].cevr";
connectAttr "animCurveTL826.a" "clipLibrary1.cel[0].cev[139].cevr";
connectAttr "animCurveTL827.a" "clipLibrary1.cel[0].cev[140].cevr";
connectAttr "animCurveTL828.a" "clipLibrary1.cel[0].cev[141].cevr";
connectAttr "animCurveTA2350.a" "clipLibrary1.cel[0].cev[142].cevr";
connectAttr "animCurveTA2351.a" "clipLibrary1.cel[0].cev[143].cevr";
connectAttr "animCurveTA2352.a" "clipLibrary1.cel[0].cev[144].cevr";
connectAttr "animCurveTL829.a" "clipLibrary1.cel[0].cev[145].cevr";
connectAttr "animCurveTL830.a" "clipLibrary1.cel[0].cev[146].cevr";
connectAttr "animCurveTL831.a" "clipLibrary1.cel[0].cev[147].cevr";
connectAttr "animCurveTU1275.a" "clipLibrary1.cel[0].cev[148].cevr";
connectAttr "animCurveTU1276.a" "clipLibrary1.cel[0].cev[149].cevr";
connectAttr "animCurveTU1277.a" "clipLibrary1.cel[0].cev[150].cevr";
connectAttr "animCurveTU1278.a" "clipLibrary1.cel[0].cev[151].cevr";
connectAttr "animCurveTU1279.a" "clipLibrary1.cel[0].cev[152].cevr";
connectAttr "animCurveTU1280.a" "clipLibrary1.cel[0].cev[153].cevr";
connectAttr "animCurveTU1281.a" "clipLibrary1.cel[0].cev[154].cevr";
connectAttr "animCurveTU1282.a" "clipLibrary1.cel[0].cev[155].cevr";
connectAttr "animCurveTA2353.a" "clipLibrary1.cel[0].cev[156].cevr";
connectAttr "animCurveTA2354.a" "clipLibrary1.cel[0].cev[157].cevr";
connectAttr "animCurveTA2355.a" "clipLibrary1.cel[0].cev[158].cevr";
connectAttr "animCurveTL832.a" "clipLibrary1.cel[0].cev[159].cevr";
connectAttr "animCurveTL833.a" "clipLibrary1.cel[0].cev[160].cevr";
connectAttr "animCurveTL834.a" "clipLibrary1.cel[0].cev[161].cevr";
connectAttr "animCurveTU1283.a" "clipLibrary1.cel[0].cev[162].cevr";
connectAttr "animCurveTU1284.a" "clipLibrary1.cel[0].cev[163].cevr";
connectAttr "animCurveTU1285.a" "clipLibrary1.cel[0].cev[164].cevr";
connectAttr "animCurveTL835.a" "clipLibrary1.cel[0].cev[165].cevr";
connectAttr "animCurveTL836.a" "clipLibrary1.cel[0].cev[166].cevr";
connectAttr "animCurveTL837.a" "clipLibrary1.cel[0].cev[167].cevr";
connectAttr "animCurveTU1286.a" "clipLibrary1.cel[0].cev[168].cevr";
connectAttr "animCurveTL838.a" "clipLibrary1.cel[0].cev[169].cevr";
connectAttr "animCurveTL839.a" "clipLibrary1.cel[0].cev[170].cevr";
connectAttr "animCurveTL840.a" "clipLibrary1.cel[0].cev[171].cevr";
connectAttr "animCurveTA2356.a" "clipLibrary1.cel[0].cev[172].cevr";
connectAttr "animCurveTA2357.a" "clipLibrary1.cel[0].cev[173].cevr";
connectAttr "animCurveTA2358.a" "clipLibrary1.cel[0].cev[174].cevr";
connectAttr "animCurveTL841.a" "clipLibrary1.cel[0].cev[175].cevr";
connectAttr "animCurveTL842.a" "clipLibrary1.cel[0].cev[176].cevr";
connectAttr "animCurveTL843.a" "clipLibrary1.cel[0].cev[177].cevr";
connectAttr "animCurveTU1287.a" "clipLibrary1.cel[0].cev[178].cevr";
connectAttr "animCurveTU1288.a" "clipLibrary1.cel[0].cev[179].cevr";
connectAttr "animCurveTU1289.a" "clipLibrary1.cel[0].cev[180].cevr";
connectAttr "animCurveTU1290.a" "clipLibrary1.cel[0].cev[181].cevr";
connectAttr "animCurveTU1291.a" "clipLibrary1.cel[0].cev[182].cevr";
connectAttr "animCurveTA2359.a" "clipLibrary1.cel[0].cev[183].cevr";
connectAttr "animCurveTA2360.a" "clipLibrary1.cel[0].cev[184].cevr";
connectAttr "animCurveTA2361.a" "clipLibrary1.cel[0].cev[185].cevr";
connectAttr "animCurveTL844.a" "clipLibrary1.cel[0].cev[186].cevr";
connectAttr "animCurveTL845.a" "clipLibrary1.cel[0].cev[187].cevr";
connectAttr "animCurveTL846.a" "clipLibrary1.cel[0].cev[188].cevr";
connectAttr "animCurveTU1292.a" "clipLibrary1.cel[0].cev[189].cevr";
connectAttr "animCurveTU1293.a" "clipLibrary1.cel[0].cev[190].cevr";
connectAttr "animCurveTU1294.a" "clipLibrary1.cel[0].cev[191].cevr";
connectAttr "animCurveTU1295.a" "clipLibrary1.cel[0].cev[192].cevr";
connectAttr "animCurveTU1296.a" "clipLibrary1.cel[0].cev[193].cevr";
connectAttr "animCurveTU1297.a" "clipLibrary1.cel[0].cev[194].cevr";
connectAttr "animCurveTU1298.a" "clipLibrary1.cel[0].cev[195].cevr";
connectAttr "animCurveTU1299.a" "clipLibrary1.cel[0].cev[196].cevr";
connectAttr "animCurveTU1300.a" "clipLibrary1.cel[0].cev[197].cevr";
connectAttr "animCurveTU1301.a" "clipLibrary1.cel[0].cev[198].cevr";
connectAttr "animCurveTA2362.a" "clipLibrary1.cel[0].cev[199].cevr";
connectAttr "animCurveTA2363.a" "clipLibrary1.cel[0].cev[200].cevr";
connectAttr "animCurveTA2364.a" "clipLibrary1.cel[0].cev[201].cevr";
connectAttr "animCurveTL847.a" "clipLibrary1.cel[0].cev[202].cevr";
connectAttr "animCurveTL848.a" "clipLibrary1.cel[0].cev[203].cevr";
connectAttr "animCurveTL849.a" "clipLibrary1.cel[0].cev[204].cevr";
connectAttr "animCurveTU1302.a" "clipLibrary1.cel[0].cev[205].cevr";
connectAttr "animCurveTU1303.a" "clipLibrary1.cel[0].cev[206].cevr";
connectAttr "animCurveTU1304.a" "clipLibrary1.cel[0].cev[207].cevr";
connectAttr "animCurveTA2365.a" "clipLibrary1.cel[0].cev[208].cevr";
connectAttr "animCurveTA2366.a" "clipLibrary1.cel[0].cev[209].cevr";
connectAttr "animCurveTA2367.a" "clipLibrary1.cel[0].cev[210].cevr";
connectAttr "animCurveTL850.a" "clipLibrary1.cel[0].cev[211].cevr";
connectAttr "animCurveTL851.a" "clipLibrary1.cel[0].cev[212].cevr";
connectAttr "animCurveTL852.a" "clipLibrary1.cel[0].cev[213].cevr";
connectAttr "animCurveTU1305.a" "clipLibrary1.cel[0].cev[214].cevr";
connectAttr "animCurveTU1306.a" "clipLibrary1.cel[0].cev[215].cevr";
connectAttr "animCurveTU1307.a" "clipLibrary1.cel[0].cev[216].cevr";
connectAttr "animCurveTA2368.a" "clipLibrary1.cel[0].cev[217].cevr";
connectAttr "animCurveTA2369.a" "clipLibrary1.cel[0].cev[218].cevr";
connectAttr "animCurveTA2370.a" "clipLibrary1.cel[0].cev[219].cevr";
connectAttr "animCurveTL853.a" "clipLibrary1.cel[0].cev[220].cevr";
connectAttr "animCurveTL854.a" "clipLibrary1.cel[0].cev[221].cevr";
connectAttr "animCurveTL855.a" "clipLibrary1.cel[0].cev[222].cevr";
connectAttr "animCurveTU1308.a" "clipLibrary1.cel[0].cev[223].cevr";
connectAttr "animCurveTU1309.a" "clipLibrary1.cel[0].cev[224].cevr";
connectAttr "animCurveTA2371.a" "clipLibrary1.cel[0].cev[225].cevr";
connectAttr "animCurveTA2372.a" "clipLibrary1.cel[0].cev[226].cevr";
connectAttr "animCurveTA2373.a" "clipLibrary1.cel[0].cev[227].cevr";
connectAttr "animCurveTL856.a" "clipLibrary1.cel[0].cev[228].cevr";
connectAttr "animCurveTL857.a" "clipLibrary1.cel[0].cev[229].cevr";
connectAttr "animCurveTL858.a" "clipLibrary1.cel[0].cev[230].cevr";
connectAttr "animCurveTU1310.a" "clipLibrary1.cel[0].cev[231].cevr";
connectAttr "animCurveTU1311.a" "clipLibrary1.cel[0].cev[232].cevr";
connectAttr "animCurveTU1312.a" "clipLibrary1.cel[0].cev[233].cevr";
connectAttr "animCurveTA2374.a" "clipLibrary1.cel[0].cev[234].cevr";
connectAttr "animCurveTA2375.a" "clipLibrary1.cel[0].cev[235].cevr";
connectAttr "animCurveTA2376.a" "clipLibrary1.cel[0].cev[236].cevr";
connectAttr "animCurveTL859.a" "clipLibrary1.cel[0].cev[237].cevr";
connectAttr "animCurveTL860.a" "clipLibrary1.cel[0].cev[238].cevr";
connectAttr "animCurveTL861.a" "clipLibrary1.cel[0].cev[239].cevr";
connectAttr "animCurveTU1313.a" "clipLibrary1.cel[0].cev[240].cevr";
connectAttr "animCurveTU1314.a" "clipLibrary1.cel[0].cev[241].cevr";
connectAttr "animCurveTA2377.a" "clipLibrary1.cel[0].cev[242].cevr";
connectAttr "animCurveTA2378.a" "clipLibrary1.cel[0].cev[243].cevr";
connectAttr "animCurveTA2379.a" "clipLibrary1.cel[0].cev[244].cevr";
connectAttr "animCurveTL862.a" "clipLibrary1.cel[0].cev[245].cevr";
connectAttr "animCurveTL863.a" "clipLibrary1.cel[0].cev[246].cevr";
connectAttr "animCurveTL864.a" "clipLibrary1.cel[0].cev[247].cevr";
connectAttr "animCurveTA2380.a" "clipLibrary1.cel[0].cev[248].cevr";
connectAttr "animCurveTA2381.a" "clipLibrary1.cel[0].cev[249].cevr";
connectAttr "animCurveTA2382.a" "clipLibrary1.cel[0].cev[250].cevr";
connectAttr "animCurveTA2383.a" "clipLibrary1.cel[0].cev[251].cevr";
connectAttr "animCurveTA2384.a" "clipLibrary1.cel[0].cev[252].cevr";
connectAttr "animCurveTA2385.a" "clipLibrary1.cel[0].cev[253].cevr";
connectAttr "animCurveTA2386.a" "clipLibrary1.cel[0].cev[254].cevr";
connectAttr "animCurveTA2387.a" "clipLibrary1.cel[0].cev[255].cevr";
connectAttr "animCurveTA2388.a" "clipLibrary1.cel[0].cev[256].cevr";
connectAttr "animCurveTA2389.a" "clipLibrary1.cel[0].cev[257].cevr";
connectAttr "animCurveTA2390.a" "clipLibrary1.cel[0].cev[258].cevr";
connectAttr "animCurveTA2391.a" "clipLibrary1.cel[0].cev[259].cevr";
connectAttr "animCurveTA2392.a" "clipLibrary1.cel[0].cev[260].cevr";
connectAttr "animCurveTA2393.a" "clipLibrary1.cel[0].cev[261].cevr";
connectAttr "animCurveTA2394.a" "clipLibrary1.cel[0].cev[262].cevr";
connectAttr "animCurveTA2395.a" "clipLibrary1.cel[0].cev[263].cevr";
connectAttr "animCurveTU1315.a" "clipLibrary1.cel[0].cev[264].cevr";
connectAttr "animCurveTU1316.a" "clipLibrary1.cel[0].cev[265].cevr";
connectAttr "animCurveTU1317.a" "clipLibrary1.cel[0].cev[266].cevr";
connectAttr "animCurveTL865.a" "clipLibrary1.cel[0].cev[267].cevr";
connectAttr "animCurveTL866.a" "clipLibrary1.cel[0].cev[268].cevr";
connectAttr "animCurveTL867.a" "clipLibrary1.cel[0].cev[269].cevr";
connectAttr "animCurveTU1318.a" "clipLibrary1.cel[0].cev[270].cevr";
connectAttr "animCurveTL868.a" "clipLibrary1.cel[0].cev[271].cevr";
connectAttr "animCurveTL869.a" "clipLibrary1.cel[0].cev[272].cevr";
connectAttr "animCurveTL870.a" "clipLibrary1.cel[0].cev[273].cevr";
connectAttr "animCurveTA2396.a" "clipLibrary1.cel[0].cev[274].cevr";
connectAttr "animCurveTA2397.a" "clipLibrary1.cel[0].cev[275].cevr";
connectAttr "animCurveTA2398.a" "clipLibrary1.cel[0].cev[276].cevr";
connectAttr "animCurveTL871.a" "clipLibrary1.cel[0].cev[277].cevr";
connectAttr "animCurveTL872.a" "clipLibrary1.cel[0].cev[278].cevr";
connectAttr "animCurveTL873.a" "clipLibrary1.cel[0].cev[279].cevr";
connectAttr "animCurveTU1319.a" "clipLibrary1.cel[0].cev[280].cevr";
connectAttr "animCurveTU1320.a" "clipLibrary1.cel[0].cev[281].cevr";
connectAttr "animCurveTU1321.a" "clipLibrary1.cel[0].cev[282].cevr";
connectAttr "animCurveTU1322.a" "clipLibrary1.cel[0].cev[283].cevr";
connectAttr "animCurveTU1323.a" "clipLibrary1.cel[0].cev[284].cevr";
connectAttr "animCurveTU1324.a" "clipLibrary1.cel[0].cev[285].cevr";
connectAttr "animCurveTU1325.a" "clipLibrary1.cel[0].cev[286].cevr";
connectAttr "animCurveTU1326.a" "clipLibrary1.cel[0].cev[287].cevr";
connectAttr "animCurveTA2399.a" "clipLibrary1.cel[0].cev[288].cevr";
connectAttr "animCurveTA2400.a" "clipLibrary1.cel[0].cev[289].cevr";
connectAttr "animCurveTA2401.a" "clipLibrary1.cel[0].cev[290].cevr";
connectAttr "animCurveTL874.a" "clipLibrary1.cel[0].cev[291].cevr";
connectAttr "animCurveTL875.a" "clipLibrary1.cel[0].cev[292].cevr";
connectAttr "animCurveTL876.a" "clipLibrary1.cel[0].cev[293].cevr";
connectAttr "animCurveTU1327.a" "clipLibrary1.cel[0].cev[294].cevr";
connectAttr "animCurveTU1328.a" "clipLibrary1.cel[0].cev[295].cevr";
connectAttr "animCurveTU1329.a" "clipLibrary1.cel[0].cev[296].cevr";
connectAttr "animCurveTL877.a" "clipLibrary1.cel[0].cev[297].cevr";
connectAttr "animCurveTL878.a" "clipLibrary1.cel[0].cev[298].cevr";
connectAttr "animCurveTL879.a" "clipLibrary1.cel[0].cev[299].cevr";
connectAttr "animCurveTU1330.a" "clipLibrary1.cel[0].cev[300].cevr";
connectAttr "animCurveTL880.a" "clipLibrary1.cel[0].cev[301].cevr";
connectAttr "animCurveTL881.a" "clipLibrary1.cel[0].cev[302].cevr";
connectAttr "animCurveTL882.a" "clipLibrary1.cel[0].cev[303].cevr";
connectAttr "animCurveTA2402.a" "clipLibrary1.cel[0].cev[304].cevr";
connectAttr "animCurveTA2403.a" "clipLibrary1.cel[0].cev[305].cevr";
connectAttr "animCurveTA2404.a" "clipLibrary1.cel[0].cev[306].cevr";
connectAttr "animCurveTL883.a" "clipLibrary1.cel[0].cev[307].cevr";
connectAttr "animCurveTL884.a" "clipLibrary1.cel[0].cev[308].cevr";
connectAttr "animCurveTL885.a" "clipLibrary1.cel[0].cev[309].cevr";
connectAttr "animCurveTU1331.a" "clipLibrary1.cel[0].cev[310].cevr";
connectAttr "animCurveTU1332.a" "clipLibrary1.cel[0].cev[311].cevr";
connectAttr "animCurveTU1333.a" "clipLibrary1.cel[0].cev[312].cevr";
connectAttr "animCurveTU1334.a" "clipLibrary1.cel[0].cev[313].cevr";
connectAttr "animCurveTU1335.a" "clipLibrary1.cel[0].cev[314].cevr";
connectAttr "animCurveTA2405.a" "clipLibrary1.cel[0].cev[315].cevr";
connectAttr "animCurveTA2406.a" "clipLibrary1.cel[0].cev[316].cevr";
connectAttr "animCurveTA2407.a" "clipLibrary1.cel[0].cev[317].cevr";
connectAttr "animCurveTL886.a" "clipLibrary1.cel[0].cev[318].cevr";
connectAttr "animCurveTL887.a" "clipLibrary1.cel[0].cev[319].cevr";
connectAttr "animCurveTL888.a" "clipLibrary1.cel[0].cev[320].cevr";
connectAttr "animCurveTA2408.a" "clipLibrary1.cel[0].cev[321].cevr";
connectAttr "animCurveTA2409.a" "clipLibrary1.cel[0].cev[322].cevr";
connectAttr "animCurveTA2410.a" "clipLibrary1.cel[0].cev[323].cevr";
connectAttr "animCurveTA2411.a" "clipLibrary1.cel[0].cev[324].cevr";
connectAttr "animCurveTA2412.a" "clipLibrary1.cel[0].cev[325].cevr";
connectAttr "animCurveTA2413.a" "clipLibrary1.cel[0].cev[326].cevr";
connectAttr "animCurveTU1336.a" "clipLibrary1.cel[0].cev[327].cevr";
connectAttr "animCurveTU1337.a" "clipLibrary1.cel[0].cev[328].cevr";
connectAttr "animCurveTU1338.a" "clipLibrary1.cel[0].cev[329].cevr";
connectAttr "animCurveTA2414.a" "clipLibrary1.cel[0].cev[330].cevr";
connectAttr "animCurveTA2415.a" "clipLibrary1.cel[0].cev[331].cevr";
connectAttr "animCurveTA2416.a" "clipLibrary1.cel[0].cev[332].cevr";
connectAttr "animCurveTA2417.a" "clipLibrary1.cel[0].cev[333].cevr";
connectAttr "animCurveTA2418.a" "clipLibrary1.cel[0].cev[334].cevr";
connectAttr "animCurveTA2419.a" "clipLibrary1.cel[0].cev[335].cevr";
connectAttr "animCurveTU1339.a" "clipLibrary1.cel[0].cev[336].cevr";
connectAttr "animCurveTU1340.a" "clipLibrary1.cel[0].cev[337].cevr";
connectAttr "animCurveTU1341.a" "clipLibrary1.cel[0].cev[338].cevr";
connectAttr "animCurveTA2420.a" "clipLibrary1.cel[0].cev[339].cevr";
connectAttr "animCurveTA2421.a" "clipLibrary1.cel[0].cev[340].cevr";
connectAttr "animCurveTA2422.a" "clipLibrary1.cel[0].cev[341].cevr";
connectAttr "animCurveTA2423.a" "clipLibrary1.cel[0].cev[342].cevr";
connectAttr "animCurveTA2424.a" "clipLibrary1.cel[0].cev[343].cevr";
connectAttr "animCurveTA2425.a" "clipLibrary1.cel[0].cev[344].cevr";
connectAttr "animCurveTU1342.a" "clipLibrary1.cel[0].cev[345].cevr";
connectAttr "animCurveTU1343.a" "clipLibrary1.cel[0].cev[346].cevr";
connectAttr "animCurveTU1344.a" "clipLibrary1.cel[0].cev[347].cevr";
connectAttr "animCurveTA2426.a" "clipLibrary1.cel[0].cev[348].cevr";
connectAttr "animCurveTA2427.a" "clipLibrary1.cel[0].cev[349].cevr";
connectAttr "animCurveTA2428.a" "clipLibrary1.cel[0].cev[350].cevr";
connectAttr "animCurveTA2429.a" "clipLibrary1.cel[0].cev[351].cevr";
connectAttr "animCurveTA2430.a" "clipLibrary1.cel[0].cev[352].cevr";
connectAttr "animCurveTA2431.a" "clipLibrary1.cel[0].cev[353].cevr";
connectAttr "animCurveTU1345.a" "clipLibrary1.cel[0].cev[354].cevr";
connectAttr "animCurveTU1346.a" "clipLibrary1.cel[0].cev[355].cevr";
connectAttr "animCurveTU1347.a" "clipLibrary1.cel[0].cev[356].cevr";
connectAttr "animCurveTA2432.a" "clipLibrary1.cel[0].cev[357].cevr";
connectAttr "animCurveTA2433.a" "clipLibrary1.cel[0].cev[358].cevr";
connectAttr "animCurveTA2434.a" "clipLibrary1.cel[0].cev[359].cevr";
connectAttr "animCurveTU1348.a" "clipLibrary1.cel[0].cev[360].cevr";
connectAttr "animCurveTU1349.a" "clipLibrary1.cel[0].cev[361].cevr";
connectAttr "animCurveTU1350.a" "clipLibrary1.cel[0].cev[362].cevr";
connectAttr "animCurveTA2435.a" "clipLibrary1.cel[0].cev[363].cevr";
connectAttr "animCurveTA2436.a" "clipLibrary1.cel[0].cev[364].cevr";
connectAttr "animCurveTA2437.a" "clipLibrary1.cel[0].cev[365].cevr";
connectAttr "animCurveTL889.a" "clipLibrary1.cel[0].cev[366].cevr";
connectAttr "animCurveTL890.a" "clipLibrary1.cel[0].cev[367].cevr";
connectAttr "animCurveTL891.a" "clipLibrary1.cel[0].cev[368].cevr";
connectAttr "animCurveTU1351.a" "clipLibrary1.cel[0].cev[369].cevr";
connectAttr "animCurveTU1352.a" "clipLibrary1.cel[0].cev[370].cevr";
connectAttr "animCurveTU1353.a" "clipLibrary1.cel[0].cev[371].cevr";
connectAttr "animCurveTA2438.a" "clipLibrary1.cel[0].cev[372].cevr";
connectAttr "animCurveTA2439.a" "clipLibrary1.cel[0].cev[373].cevr";
connectAttr "animCurveTA2440.a" "clipLibrary1.cel[0].cev[374].cevr";
connectAttr "animCurveTL892.a" "clipLibrary1.cel[0].cev[375].cevr";
connectAttr "animCurveTL893.a" "clipLibrary1.cel[0].cev[376].cevr";
connectAttr "animCurveTL894.a" "clipLibrary1.cel[0].cev[377].cevr";
connectAttr "animCurveTA2441.a" "clipLibrary1.cel[0].cev[378].cevr";
connectAttr "animCurveTA2442.a" "clipLibrary1.cel[0].cev[379].cevr";
connectAttr "animCurveTA2443.a" "clipLibrary1.cel[0].cev[380].cevr";
connectAttr "animCurveTU1354.a" "clipLibrary1.cel[0].cev[381].cevr";
connectAttr "animCurveTU1355.a" "clipLibrary1.cel[0].cev[382].cevr";
connectAttr "animCurveTU1356.a" "clipLibrary1.cel[0].cev[383].cevr";
connectAttr "animCurveTA2444.a" "clipLibrary1.cel[0].cev[384].cevr";
connectAttr "animCurveTA2445.a" "clipLibrary1.cel[0].cev[385].cevr";
connectAttr "animCurveTA2446.a" "clipLibrary1.cel[0].cev[386].cevr";
connectAttr "animCurveTA2447.a" "clipLibrary1.cel[0].cev[387].cevr";
connectAttr "animCurveTA2448.a" "clipLibrary1.cel[0].cev[388].cevr";
connectAttr "animCurveTA2449.a" "clipLibrary1.cel[0].cev[389].cevr";
connectAttr "animCurveTU1357.a" "clipLibrary1.cel[0].cev[390].cevr";
connectAttr "animCurveTU1358.a" "clipLibrary1.cel[0].cev[391].cevr";
connectAttr "animCurveTU1359.a" "clipLibrary1.cel[0].cev[392].cevr";
connectAttr "animCurveTA2450.a" "clipLibrary1.cel[0].cev[394].cevr";
connectAttr "animCurveTA2451.a" "clipLibrary1.cel[0].cev[396].cevr";
connectAttr "animCurveTA2452.a" "clipLibrary1.cel[0].cev[397].cevr";
connectAttr "animCurveTA2453.a" "clipLibrary1.cel[0].cev[398].cevr";
connectAttr "animCurveTU1360.a" "clipLibrary1.cel[0].cev[399].cevr";
connectAttr "animCurveTU1361.a" "clipLibrary1.cel[0].cev[400].cevr";
connectAttr "animCurveTU1362.a" "clipLibrary1.cel[0].cev[401].cevr";
connectAttr "animCurveTA2454.a" "clipLibrary1.cel[0].cev[402].cevr";
connectAttr "animCurveTA2455.a" "clipLibrary1.cel[0].cev[403].cevr";
connectAttr "animCurveTA2456.a" "clipLibrary1.cel[0].cev[404].cevr";
connectAttr "animCurveTA2457.a" "clipLibrary1.cel[0].cev[405].cevr";
connectAttr "animCurveTA2458.a" "clipLibrary1.cel[0].cev[406].cevr";
connectAttr "animCurveTA2459.a" "clipLibrary1.cel[0].cev[407].cevr";
connectAttr "animCurveTU1363.a" "clipLibrary1.cel[0].cev[408].cevr";
connectAttr "animCurveTU1364.a" "clipLibrary1.cel[0].cev[409].cevr";
connectAttr "animCurveTU1365.a" "clipLibrary1.cel[0].cev[410].cevr";
connectAttr "animCurveTA2460.a" "clipLibrary1.cel[0].cev[411].cevr";
connectAttr "animCurveTA2461.a" "clipLibrary1.cel[0].cev[412].cevr";
connectAttr "animCurveTA2462.a" "clipLibrary1.cel[0].cev[413].cevr";
connectAttr "animCurveTA2463.a" "clipLibrary1.cel[0].cev[414].cevr";
connectAttr "animCurveTA2464.a" "clipLibrary1.cel[0].cev[415].cevr";
connectAttr "animCurveTA2465.a" "clipLibrary1.cel[0].cev[416].cevr";
connectAttr "animCurveTU1366.a" "clipLibrary1.cel[0].cev[417].cevr";
connectAttr "animCurveTU1367.a" "clipLibrary1.cel[0].cev[418].cevr";
connectAttr "animCurveTU1368.a" "clipLibrary1.cel[0].cev[419].cevr";
connectAttr "animCurveTA2466.a" "clipLibrary1.cel[0].cev[420].cevr";
connectAttr "animCurveTA2467.a" "clipLibrary1.cel[0].cev[421].cevr";
connectAttr "animCurveTA2468.a" "clipLibrary1.cel[0].cev[422].cevr";
connectAttr "animCurveTA2469.a" "clipLibrary1.cel[0].cev[423].cevr";
connectAttr "animCurveTA2470.a" "clipLibrary1.cel[0].cev[424].cevr";
connectAttr "animCurveTA2471.a" "clipLibrary1.cel[0].cev[425].cevr";
connectAttr "animCurveTU1369.a" "clipLibrary1.cel[0].cev[426].cevr";
connectAttr "animCurveTU1370.a" "clipLibrary1.cel[0].cev[427].cevr";
connectAttr "animCurveTU1371.a" "clipLibrary1.cel[0].cev[428].cevr";
connectAttr "animCurveTA2472.a" "clipLibrary1.cel[0].cev[429].cevr";
connectAttr "animCurveTA2473.a" "clipLibrary1.cel[0].cev[430].cevr";
connectAttr "animCurveTA2474.a" "clipLibrary1.cel[0].cev[431].cevr";
connectAttr "animCurveTA2475.a" "clipLibrary1.cel[0].cev[432].cevr";
connectAttr "animCurveTA2476.a" "clipLibrary1.cel[0].cev[433].cevr";
connectAttr "animCurveTA2477.a" "clipLibrary1.cel[0].cev[434].cevr";
connectAttr "animCurveTU1372.a" "clipLibrary1.cel[0].cev[435].cevr";
connectAttr "animCurveTU1373.a" "clipLibrary1.cel[0].cev[436].cevr";
connectAttr "animCurveTU1374.a" "clipLibrary1.cel[0].cev[437].cevr";
connectAttr "animCurveTA2478.a" "clipLibrary1.cel[0].cev[438].cevr";
connectAttr "animCurveTA2479.a" "clipLibrary1.cel[0].cev[439].cevr";
connectAttr "animCurveTA2480.a" "clipLibrary1.cel[0].cev[440].cevr";
connectAttr "animCurveTA2481.a" "clipLibrary1.cel[0].cev[441].cevr";
connectAttr "animCurveTA2482.a" "clipLibrary1.cel[0].cev[442].cevr";
connectAttr "animCurveTA2483.a" "clipLibrary1.cel[0].cev[443].cevr";
connectAttr "animCurveTU1375.a" "clipLibrary1.cel[0].cev[444].cevr";
connectAttr "animCurveTU1376.a" "clipLibrary1.cel[0].cev[445].cevr";
connectAttr "animCurveTU1377.a" "clipLibrary1.cel[0].cev[446].cevr";
connectAttr "animCurveTA2484.a" "clipLibrary1.cel[0].cev[447].cevr";
connectAttr "animCurveTA2485.a" "clipLibrary1.cel[0].cev[448].cevr";
connectAttr "animCurveTA2486.a" "clipLibrary1.cel[0].cev[449].cevr";
connectAttr "animCurveTA2487.a" "clipLibrary1.cel[0].cev[450].cevr";
connectAttr "animCurveTA2488.a" "clipLibrary1.cel[0].cev[451].cevr";
connectAttr "animCurveTA2489.a" "clipLibrary1.cel[0].cev[452].cevr";
connectAttr "animCurveTU1378.a" "clipLibrary1.cel[0].cev[453].cevr";
connectAttr "animCurveTU1379.a" "clipLibrary1.cel[0].cev[454].cevr";
connectAttr "animCurveTU1380.a" "clipLibrary1.cel[0].cev[455].cevr";
connectAttr "animCurveTA2490.a" "clipLibrary1.cel[0].cev[456].cevr";
connectAttr "animCurveTA2491.a" "clipLibrary1.cel[0].cev[457].cevr";
connectAttr "animCurveTA2492.a" "clipLibrary1.cel[0].cev[458].cevr";
connectAttr "animCurveTA2493.a" "clipLibrary1.cel[0].cev[459].cevr";
connectAttr "animCurveTA2494.a" "clipLibrary1.cel[0].cev[460].cevr";
connectAttr "animCurveTA2495.a" "clipLibrary1.cel[0].cev[461].cevr";
connectAttr "animCurveTU1381.a" "clipLibrary1.cel[0].cev[462].cevr";
connectAttr "animCurveTU1382.a" "clipLibrary1.cel[0].cev[463].cevr";
connectAttr "animCurveTU1383.a" "clipLibrary1.cel[0].cev[464].cevr";
connectAttr "animCurveTA2496.a" "clipLibrary1.cel[0].cev[465].cevr";
connectAttr "animCurveTA2497.a" "clipLibrary1.cel[0].cev[466].cevr";
connectAttr "animCurveTA2498.a" "clipLibrary1.cel[0].cev[467].cevr";
connectAttr "animCurveTA2499.a" "clipLibrary1.cel[0].cev[468].cevr";
connectAttr "animCurveTA2500.a" "clipLibrary1.cel[0].cev[469].cevr";
connectAttr "animCurveTA2501.a" "clipLibrary1.cel[0].cev[470].cevr";
connectAttr "animCurveTU1384.a" "clipLibrary1.cel[0].cev[471].cevr";
connectAttr "animCurveTU1385.a" "clipLibrary1.cel[0].cev[472].cevr";
connectAttr "animCurveTU1386.a" "clipLibrary1.cel[0].cev[473].cevr";
connectAttr "animCurveTA2502.a" "clipLibrary1.cel[0].cev[474].cevr";
connectAttr "animCurveTA2503.a" "clipLibrary1.cel[0].cev[475].cevr";
connectAttr "animCurveTA2504.a" "clipLibrary1.cel[0].cev[476].cevr";
connectAttr "animCurveTA2505.a" "clipLibrary1.cel[0].cev[477].cevr";
connectAttr "animCurveTA2506.a" "clipLibrary1.cel[0].cev[478].cevr";
connectAttr "animCurveTA2507.a" "clipLibrary1.cel[0].cev[479].cevr";
connectAttr "animCurveTU1387.a" "clipLibrary1.cel[0].cev[480].cevr";
connectAttr "animCurveTU1388.a" "clipLibrary1.cel[0].cev[481].cevr";
connectAttr "animCurveTU1389.a" "clipLibrary1.cel[0].cev[482].cevr";
connectAttr "animCurveTA2508.a" "clipLibrary1.cel[0].cev[483].cevr";
connectAttr "animCurveTA2509.a" "clipLibrary1.cel[0].cev[484].cevr";
connectAttr "animCurveTA2510.a" "clipLibrary1.cel[0].cev[485].cevr";
connectAttr "animCurveTA2511.a" "clipLibrary1.cel[0].cev[486].cevr";
connectAttr "animCurveTA2512.a" "clipLibrary1.cel[0].cev[487].cevr";
connectAttr "animCurveTA2513.a" "clipLibrary1.cel[0].cev[488].cevr";
connectAttr "animCurveTU1390.a" "clipLibrary1.cel[0].cev[489].cevr";
connectAttr "animCurveTU1391.a" "clipLibrary1.cel[0].cev[490].cevr";
connectAttr "animCurveTU1392.a" "clipLibrary1.cel[0].cev[491].cevr";
connectAttr "animCurveTA2514.a" "clipLibrary1.cel[0].cev[492].cevr";
connectAttr "animCurveTA2515.a" "clipLibrary1.cel[0].cev[493].cevr";
connectAttr "animCurveTA2516.a" "clipLibrary1.cel[0].cev[494].cevr";
connectAttr "animCurveTA2517.a" "clipLibrary1.cel[0].cev[495].cevr";
connectAttr "animCurveTA2518.a" "clipLibrary1.cel[0].cev[496].cevr";
connectAttr "animCurveTA2519.a" "clipLibrary1.cel[0].cev[497].cevr";
connectAttr "animCurveTU1393.a" "clipLibrary1.cel[0].cev[498].cevr";
connectAttr "animCurveTU1394.a" "clipLibrary1.cel[0].cev[499].cevr";
connectAttr "animCurveTU1395.a" "clipLibrary1.cel[0].cev[500].cevr";
connectAttr "animCurveTA2520.a" "clipLibrary1.cel[0].cev[501].cevr";
connectAttr "animCurveTA2521.a" "clipLibrary1.cel[0].cev[502].cevr";
connectAttr "animCurveTA2522.a" "clipLibrary1.cel[0].cev[503].cevr";
connectAttr "animCurveTA2523.a" "clipLibrary1.cel[0].cev[504].cevr";
connectAttr "animCurveTA2524.a" "clipLibrary1.cel[0].cev[505].cevr";
connectAttr "animCurveTA2525.a" "clipLibrary1.cel[0].cev[506].cevr";
connectAttr "animCurveTU1396.a" "clipLibrary1.cel[0].cev[507].cevr";
connectAttr "animCurveTU1397.a" "clipLibrary1.cel[0].cev[508].cevr";
connectAttr "animCurveTU1398.a" "clipLibrary1.cel[0].cev[509].cevr";
connectAttr "animCurveTA2526.a" "clipLibrary1.cel[0].cev[510].cevr";
connectAttr "animCurveTA2527.a" "clipLibrary1.cel[0].cev[511].cevr";
connectAttr "animCurveTA2528.a" "clipLibrary1.cel[0].cev[512].cevr";
connectAttr "animCurveTA2529.a" "clipLibrary1.cel[0].cev[513].cevr";
connectAttr "animCurveTA2530.a" "clipLibrary1.cel[0].cev[514].cevr";
connectAttr "animCurveTA2531.a" "clipLibrary1.cel[0].cev[515].cevr";
connectAttr "animCurveTU1399.a" "clipLibrary1.cel[0].cev[516].cevr";
connectAttr "animCurveTU1400.a" "clipLibrary1.cel[0].cev[517].cevr";
connectAttr "animCurveTU1401.a" "clipLibrary1.cel[0].cev[518].cevr";
connectAttr "animCurveTA2532.a" "clipLibrary1.cel[0].cev[519].cevr";
connectAttr "animCurveTA2533.a" "clipLibrary1.cel[0].cev[520].cevr";
connectAttr "animCurveTA2534.a" "clipLibrary1.cel[0].cev[521].cevr";
connectAttr "animCurveTA2535.a" "clipLibrary1.cel[0].cev[522].cevr";
connectAttr "animCurveTA2536.a" "clipLibrary1.cel[0].cev[523].cevr";
connectAttr "animCurveTA2537.a" "clipLibrary1.cel[0].cev[524].cevr";
connectAttr "animCurveTU1402.a" "clipLibrary1.cel[0].cev[525].cevr";
connectAttr "animCurveTU1403.a" "clipLibrary1.cel[0].cev[526].cevr";
connectAttr "animCurveTU1404.a" "clipLibrary1.cel[0].cev[527].cevr";
connectAttr "animCurveTA2538.a" "clipLibrary1.cel[0].cev[528].cevr";
connectAttr "animCurveTA2539.a" "clipLibrary1.cel[0].cev[529].cevr";
connectAttr "animCurveTA2540.a" "clipLibrary1.cel[0].cev[530].cevr";
connectAttr "animCurveTA2541.a" "clipLibrary1.cel[0].cev[531].cevr";
connectAttr "animCurveTA2542.a" "clipLibrary1.cel[0].cev[532].cevr";
connectAttr "animCurveTA2543.a" "clipLibrary1.cel[0].cev[533].cevr";
connectAttr "animCurveTU1405.a" "clipLibrary1.cel[0].cev[534].cevr";
connectAttr "animCurveTU1406.a" "clipLibrary1.cel[0].cev[535].cevr";
connectAttr "animCurveTU1407.a" "clipLibrary1.cel[0].cev[536].cevr";
connectAttr "animCurveTA2544.a" "clipLibrary1.cel[0].cev[537].cevr";
connectAttr "animCurveTA2545.a" "clipLibrary1.cel[0].cev[538].cevr";
connectAttr "animCurveTA2546.a" "clipLibrary1.cel[0].cev[539].cevr";
connectAttr "animCurveTU1408.a" "clipLibrary1.cel[0].cev[540].cevr";
connectAttr "animCurveTU1409.a" "clipLibrary1.cel[0].cev[541].cevr";
connectAttr "animCurveTU1410.a" "clipLibrary1.cel[0].cev[542].cevr";
connectAttr "animCurveTA2547.a" "clipLibrary1.cel[0].cev[543].cevr";
connectAttr "animCurveTA2548.a" "clipLibrary1.cel[0].cev[544].cevr";
connectAttr "animCurveTA2549.a" "clipLibrary1.cel[0].cev[545].cevr";
connectAttr "animCurveTL895.a" "clipLibrary1.cel[0].cev[546].cevr";
connectAttr "animCurveTL896.a" "clipLibrary1.cel[0].cev[547].cevr";
connectAttr "animCurveTL897.a" "clipLibrary1.cel[0].cev[548].cevr";
connectAttr "animCurveTU1411.a" "clipLibrary1.cel[0].cev[549].cevr";
connectAttr "animCurveTU1412.a" "clipLibrary1.cel[0].cev[550].cevr";
connectAttr "animCurveTU1413.a" "clipLibrary1.cel[0].cev[551].cevr";
connectAttr "animCurveTA2550.a" "clipLibrary1.cel[0].cev[552].cevr";
connectAttr "animCurveTA2551.a" "clipLibrary1.cel[0].cev[553].cevr";
connectAttr "animCurveTA2552.a" "clipLibrary1.cel[0].cev[554].cevr";
connectAttr "animCurveTL898.a" "clipLibrary1.cel[0].cev[555].cevr";
connectAttr "animCurveTL899.a" "clipLibrary1.cel[0].cev[556].cevr";
connectAttr "animCurveTL900.a" "clipLibrary1.cel[0].cev[557].cevr";
connectAttr "animCurveTA2553.a" "clipLibrary1.cel[0].cev[558].cevr";
connectAttr "animCurveTA2554.a" "clipLibrary1.cel[0].cev[559].cevr";
connectAttr "animCurveTA2555.a" "clipLibrary1.cel[0].cev[560].cevr";
connectAttr "animCurveTU1414.a" "clipLibrary1.cel[0].cev[561].cevr";
connectAttr "animCurveTU1415.a" "clipLibrary1.cel[0].cev[562].cevr";
connectAttr "animCurveTU1416.a" "clipLibrary1.cel[0].cev[563].cevr";
connectAttr "animCurveTA2556.a" "clipLibrary1.cel[0].cev[564].cevr";
connectAttr "animCurveTA2557.a" "clipLibrary1.cel[0].cev[565].cevr";
connectAttr "animCurveTA2558.a" "clipLibrary1.cel[0].cev[566].cevr";
connectAttr "animCurveTA2559.a" "clipLibrary1.cel[0].cev[567].cevr";
connectAttr "animCurveTA2560.a" "clipLibrary1.cel[0].cev[568].cevr";
connectAttr "animCurveTA2561.a" "clipLibrary1.cel[0].cev[569].cevr";
connectAttr "animCurveTU1417.a" "clipLibrary1.cel[0].cev[570].cevr";
connectAttr "animCurveTU1418.a" "clipLibrary1.cel[0].cev[571].cevr";
connectAttr "animCurveTU1419.a" "clipLibrary1.cel[0].cev[572].cevr";
connectAttr "animCurveTA2562.a" "clipLibrary1.cel[0].cev[574].cevr";
connectAttr "animCurveTA2563.a" "clipLibrary1.cel[0].cev[576].cevr";
connectAttr "animCurveTA2564.a" "clipLibrary1.cel[0].cev[577].cevr";
connectAttr "animCurveTA2565.a" "clipLibrary1.cel[0].cev[578].cevr";
connectAttr "animCurveTU1420.a" "clipLibrary1.cel[0].cev[579].cevr";
connectAttr "animCurveTU1421.a" "clipLibrary1.cel[0].cev[580].cevr";
connectAttr "animCurveTU1422.a" "clipLibrary1.cel[0].cev[581].cevr";
connectAttr "animCurveTA2566.a" "clipLibrary1.cel[0].cev[582].cevr";
connectAttr "animCurveTA2567.a" "clipLibrary1.cel[0].cev[583].cevr";
connectAttr "animCurveTA2568.a" "clipLibrary1.cel[0].cev[584].cevr";
connectAttr "animCurveTA2569.a" "clipLibrary1.cel[0].cev[585].cevr";
connectAttr "animCurveTA2570.a" "clipLibrary1.cel[0].cev[586].cevr";
connectAttr "animCurveTA2571.a" "clipLibrary1.cel[0].cev[587].cevr";
connectAttr "animCurveTU1423.a" "clipLibrary1.cel[0].cev[588].cevr";
connectAttr "animCurveTU1424.a" "clipLibrary1.cel[0].cev[589].cevr";
connectAttr "animCurveTU1425.a" "clipLibrary1.cel[0].cev[590].cevr";
connectAttr "animCurveTA2572.a" "clipLibrary1.cel[0].cev[591].cevr";
connectAttr "animCurveTA2573.a" "clipLibrary1.cel[0].cev[592].cevr";
connectAttr "animCurveTA2574.a" "clipLibrary1.cel[0].cev[593].cevr";
connectAttr "animCurveTA2575.a" "clipLibrary1.cel[0].cev[594].cevr";
connectAttr "animCurveTA2576.a" "clipLibrary1.cel[0].cev[595].cevr";
connectAttr "animCurveTA2577.a" "clipLibrary1.cel[0].cev[596].cevr";
connectAttr "animCurveTU1426.a" "clipLibrary1.cel[0].cev[597].cevr";
connectAttr "animCurveTU1427.a" "clipLibrary1.cel[0].cev[598].cevr";
connectAttr "animCurveTU1428.a" "clipLibrary1.cel[0].cev[599].cevr";
connectAttr "animCurveTA2578.a" "clipLibrary1.cel[0].cev[600].cevr";
connectAttr "animCurveTA2579.a" "clipLibrary1.cel[0].cev[601].cevr";
connectAttr "animCurveTA2580.a" "clipLibrary1.cel[0].cev[602].cevr";
connectAttr "animCurveTA2581.a" "clipLibrary1.cel[0].cev[603].cevr";
connectAttr "animCurveTA2582.a" "clipLibrary1.cel[0].cev[604].cevr";
connectAttr "animCurveTA2583.a" "clipLibrary1.cel[0].cev[605].cevr";
connectAttr "animCurveTU1429.a" "clipLibrary1.cel[0].cev[606].cevr";
connectAttr "animCurveTU1430.a" "clipLibrary1.cel[0].cev[607].cevr";
connectAttr "animCurveTU1431.a" "clipLibrary1.cel[0].cev[608].cevr";
connectAttr "animCurveTA2584.a" "clipLibrary1.cel[0].cev[609].cevr";
connectAttr "animCurveTA2585.a" "clipLibrary1.cel[0].cev[610].cevr";
connectAttr "animCurveTA2586.a" "clipLibrary1.cel[0].cev[611].cevr";
connectAttr "animCurveTA2587.a" "clipLibrary1.cel[0].cev[612].cevr";
connectAttr "animCurveTA2588.a" "clipLibrary1.cel[0].cev[613].cevr";
connectAttr "animCurveTA2589.a" "clipLibrary1.cel[0].cev[614].cevr";
connectAttr "animCurveTU1432.a" "clipLibrary1.cel[0].cev[615].cevr";
connectAttr "animCurveTU1433.a" "clipLibrary1.cel[0].cev[616].cevr";
connectAttr "animCurveTU1434.a" "clipLibrary1.cel[0].cev[617].cevr";
connectAttr "animCurveTA2590.a" "clipLibrary1.cel[0].cev[618].cevr";
connectAttr "animCurveTA2591.a" "clipLibrary1.cel[0].cev[619].cevr";
connectAttr "animCurveTA2592.a" "clipLibrary1.cel[0].cev[620].cevr";
connectAttr "animCurveTA2593.a" "clipLibrary1.cel[0].cev[621].cevr";
connectAttr "animCurveTA2594.a" "clipLibrary1.cel[0].cev[622].cevr";
connectAttr "animCurveTA2595.a" "clipLibrary1.cel[0].cev[623].cevr";
connectAttr "animCurveTU1435.a" "clipLibrary1.cel[0].cev[624].cevr";
connectAttr "animCurveTU1436.a" "clipLibrary1.cel[0].cev[625].cevr";
connectAttr "animCurveTU1437.a" "clipLibrary1.cel[0].cev[626].cevr";
connectAttr "animCurveTA2596.a" "clipLibrary1.cel[0].cev[627].cevr";
connectAttr "animCurveTA2597.a" "clipLibrary1.cel[0].cev[628].cevr";
connectAttr "animCurveTA2598.a" "clipLibrary1.cel[0].cev[629].cevr";
connectAttr "animCurveTA2599.a" "clipLibrary1.cel[0].cev[630].cevr";
connectAttr "animCurveTA2600.a" "clipLibrary1.cel[0].cev[631].cevr";
connectAttr "animCurveTA2601.a" "clipLibrary1.cel[0].cev[632].cevr";
connectAttr "animCurveTU1438.a" "clipLibrary1.cel[0].cev[633].cevr";
connectAttr "animCurveTU1439.a" "clipLibrary1.cel[0].cev[634].cevr";
connectAttr "animCurveTU1440.a" "clipLibrary1.cel[0].cev[635].cevr";
connectAttr "animCurveTA2602.a" "clipLibrary1.cel[0].cev[636].cevr";
connectAttr "animCurveTA2603.a" "clipLibrary1.cel[0].cev[637].cevr";
connectAttr "animCurveTA2604.a" "clipLibrary1.cel[0].cev[638].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of Minigame2_idle.ma
