//Maya ASCII 2008 scene
//Name: Minigame2_idleBig.ma
//Last modified: Fri, Dec 11, 2009 06:06:04 PM
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
createNode animClip -n "Minigame2_idleBigSource";
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
	setAttr ".se" 970;
	setAttr ".ci" no;
createNode animCurveTA -n "animCurveTA3151";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3152";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3153";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3154";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3155";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3156";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3157";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3158";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3159";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3160";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3161";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3162";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3163";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3164";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3165";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3166";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3167";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3168";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3169";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3170";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3171";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3172";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3173";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3174";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3175";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3176";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3177";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3178";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3179";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3180";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3181";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3182";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3183";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3184";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3185";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3186";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3187";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3188";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3189";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1054";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1055";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1056";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3190";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3191";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3192";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1057";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1058";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1059";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3193";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3194";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3195";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1060";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1061";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1062";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3196";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 20.493535127874438 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 
		0 680 0 690 0 706 0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 
		0 860 0 875 0 890 0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3197";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 -2.421557964481051 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 
		0 680 0 690 0 706 0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 
		0 860 0 875 0 890 0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3198";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 14.707211730462079 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 
		0 680 0 690 0 706 0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 
		0 860 0 875 0 890 0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1063";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1064";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1065";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3199";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3200";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3201";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1066";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1067";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1068";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3202";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 -6.2874359163474747 912 0 920 -6.9695807966301713 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3203";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 10.397892429480084 912 0 920 -7.5613914208921384 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3204";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 8.332034979251544 912 0 920 -7.1888992314866256 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1069";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1070";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1071";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3205";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3206";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3207";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1072";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1073";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1074";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3208";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3209";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3210";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1075";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1076";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1077";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3211";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3212";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3213";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1078";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1079";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1080";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3214";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3215";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3216";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1081";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1082";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1083";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1639";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 58 ".ktv[0:57]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 400 0 411 0 420 0 428 0 441 0 450 0 464 
		0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 0 714 0 720 
		0 750 0 760 0 770 0 790 0 795 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 
		0 890 0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 58 ".kit[14:57]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 9 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 9 9 10 10 10 10 10 
		10 1;
	setAttr -s 58 ".kot[14:57]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 9 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 9 9 10 10 10 10 10 
		10 1;
	setAttr -s 58 ".kix[57]"  1;
	setAttr -s 58 ".kiy[57]"  0;
	setAttr -s 58 ".kox[57]"  1;
	setAttr -s 58 ".koy[57]"  0;
createNode animCurveTA -n "animCurveTA3217";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 58 ".ktv[0:57]"  0 78.185296782687701 50 78.185296782687701 
		65 78.185296782687701 81 78.185296782687701 140 78.185296782687701 150 78.185296782687701 
		160 78.1852967826878 168 78.1852967826879 178 78.1852967826879 230 78.1852967826879 
		242 78.185296782687928 275 78.185296782687928 290 80.79945840748691 300 80.79945840748691 
		350 80.79945840748691 400 80.79945840748691 411 80.79945840748691 420 80.79945840748691 
		428 138.62541114164017 441 177.95753417111624 450 177.95753417111624 464 177.95753417111624 
		480 115.68592291873132 492 71.228628035065668 504 71.228628035065668 510 71.228628035065668 
		620 71.228628035065668 626 71.336289154596997 630 71.228628035065725 638 71.228628035065768 
		670 71.228628035065753 680 71.228628035065768 690 71.228628035065768 706 71.228628035065768 
		714 60.311763704338048 720 52.514008637485254 750 52.514008637485254 760 52.514008637485254 
		770 52.514008637485212 790 48.227760480221377 795 50.370884558853319 800 48.388234779210315 
		810 48.388234779210315 821 39.175317902681542 830 48.388234779210315 837 39.175317902681542 
		843 48.388234779210315 850 39.175317902681542 860 48.388234779210315 875 57.784851155646358 
		890 57.784851155646358 905 -0.9983198914776038 912 -0.9983198914776038 920 -0.9983198914776038 
		930 38.910063622506613 937 78.185296782687701 950 78.185296782687701 970 78.185296782687701;
	setAttr -s 58 ".kit[14:57]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 9 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 9 9 10 10 10 10 10 
		10 1;
	setAttr -s 58 ".kot[14:57]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 9 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 9 9 10 10 10 10 10 
		10 1;
	setAttr -s 58 ".kix[57]"  1;
	setAttr -s 58 ".kiy[57]"  0;
	setAttr -s 58 ".kox[57]"  1;
	setAttr -s 58 ".koy[57]"  0;
createNode animCurveTA -n "animCurveTA3218";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 58 ".ktv[0:57]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0.88131131374599969 300 0.88131131374599969 350 0.88131131374599969 
		400 0.88131131374599969 411 0.88131131374599969 420 0.88131131374599969 428 -3.323215391054859 
		441 -2.321012746846848 450 -2.321012746846848 464 -2.321012746846848 480 16.588910615553917 
		492 3.7185061869085718 504 3.7185061869085718 510 3.7185061869085718 620 3.7185061869085718 
		626 2.8914463771941636 630 3.7185061869085603 638 3.7185061869085487 670 3.7185061869085718 
		680 3.7185061869085789 690 3.7185061869085718 706 3.7185061869085718 714 2.8424596489852632 
		720 2.2167125274850101 750 2.2167125274850101 760 2.2167125274850101 770 2.2167125274850088 
		790 2.898062202984192 795 2.5573873652346015 800 -2.4763205657762377 810 -2.4763205657762377 
		821 -2.327523501659452 830 -2.4763205657762377 837 -2.327523501659452 843 -2.4763205657762377 
		850 -2.327523501659452 860 -2.4763205657762377 875 1.9722506856848736 890 1.9722506856848736 
		905 1.0238958664338005 912 1.0238958664338005 920 1.0238958664338005 930 0.36041359475731893 
		937 0 950 0 970 0;
	setAttr -s 58 ".kit[14:57]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 9 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 9 9 10 10 10 10 10 
		10 1;
	setAttr -s 58 ".kot[14:57]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 9 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 9 9 10 10 10 10 10 
		10 1;
	setAttr -s 58 ".kix[57]"  1;
	setAttr -s 58 ".kiy[57]"  0;
	setAttr -s 58 ".kox[57]"  1;
	setAttr -s 58 ".koy[57]"  0;
createNode animCurveTA -n "animCurveTA3219";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 58 ".ktv[0:57]"  0 0 50 0 65 0 81 0 140 0 150 0 160 2.6663605447088425 
		168 5.3327182287250432 178 5.3327182287250432 230 5.3327182287250432 242 -0.30677531632850225 
		275 -0.30677531632850225 290 42.198891113523906 300 42.198891113523906 350 42.198891113523906 
		400 40.518611394437897 411 20.60357287842367 420 -3.225350586728283 428 3.8497941115936687 
		441 0.51576528678175126 450 0.51576528678175126 464 0.51576528678175126 480 -17.094291851979509 
		492 -3.7344716685695061 504 -3.7344716685695061 510 -3.7344716685695061 620 -3.7344716685695061 
		626 -5.9526127051133555 630 4.7446896911282481 638 13.223972347185459 670 6.2079937523974085 
		680 -0.5449411117351709 690 2.5653907225406356 706 2.5653907225406356 714 1.9635989451932701 
		720 -5.7821093928344478 750 -2.1577627284128629 760 1.533747960191381 770 14.290358061725057 
		790 13.996810777869964 795 7.7652793690306741 800 0.72044023647455191 810 0.72044023647455191 
		821 0.61715185928754623 830 0.72044023647455191 837 0.61715185928754623 843 0.72044023647455191 
		850 0.61715185928754623 860 0.72044023647455191 875 1.6191248062492227 890 1.6191248062492227 
		905 0.85679368219181851 912 0.85679368219181851 920 0.85679368219181851 930 0.30159325873602266 
		937 0 950 0 970 0;
	setAttr -s 58 ".kit[14:57]"  9 1 10 10 10 10 10 10 
		10 10 10 10 10 10 10 3 10 10 10 9 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 9 9 10 10 10 10 10 
		10 1;
	setAttr -s 58 ".kot[14:57]"  9 1 10 10 10 10 10 10 
		10 10 10 10 10 10 10 3 10 10 10 9 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 9 9 10 10 10 10 10 
		10 1;
	setAttr -s 58 ".kix[15:57]"  0.99983566999435425 0.65773612260818481 
		0.88866186141967773 0.99567776918411255 1 1 1 0.9968564510345459 1 1 1 1 1 0.76693588495254517 
		1 0.98558551073074341 0.99548375606536865 1 0.99991381168365479 1 0.99820828437805176 
		0.99544596672058105 0.91846537590026855 1 1 0.821097731590271 1 1 1 1 1 1 1 1 0.99987697601318359 
		0.99991154670715332 1 1 1 1 1 1 1;
	setAttr -s 58 ".kiy[15:57]"  -0.018128877505660057 -0.75324845314025879 
		-0.45856305956840515 0.092875123023986816 0 0 0 -0.079229392111301422 0 0 0 0 0 0.64172375202178955 
		0 -0.1691778153181076 -0.094932526350021362 0 -0.013127940706908703 0 -0.059835337102413177 
		0.095328181982040405 0.39550146460533142 0 0 -0.57078760862350464 0 0 0 0 0 0 0 0 
		0.015683075413107872 -0.013304010964930058 0 0 0 0 0 0 0;
	setAttr -s 58 ".kox[15:57]"  0.99983566999435425 0.65773612260818481 
		0.88866186141967773 0.99567776918411255 1 1 1 0.9968564510345459 1 1 1 1 1 0.76693588495254517 
		1 0.98558551073074341 0.99548375606536865 1 0.99991381168365479 1 0.99820828437805176 
		0.99544596672058105 0.91846537590026855 1 1 0.821097731590271 1 1 1 1 1 1 1 1 0.99987697601318359 
		0.99991154670715332 1 1 1 1 1 1 1;
	setAttr -s 58 ".koy[15:57]"  -0.018128877505660057 -0.75324845314025879 
		-0.45856305956840515 0.092875123023986816 0 0 0 -0.079229392111301422 0 0 0 0 0 0.64172375202178955 
		0 -0.1691778153181076 -0.094932526350021362 0 -0.013127940706908703 0 -0.059835337102413177 
		0.095328181982040405 0.39550146460533142 0 0 -0.57078760862350464 0 0 0 0 0 0 0 0 
		0.015683075413107872 -0.013304010964930058 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL1084";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 60 ".ktv[0:59]"  0 1.2593205487904804 50 1.2593205487904804 
		65 1.2503664555394503 81 1.2503664555394503 140 1.2503664555394503 150 1.2442527002046928 
		160 0.5052674841668946 168 -0.15739635327719137 178 -0.14591195459271322 230 -0.14591195459271455 
		242 -0.11715862395320586 275 -0.11715862395320586 290 1.1260945021039515 300 1.1257503260692125 
		350 1.1257503260692125 400 1.1219872321049467 411 1.1982383061208943 420 1.2716377210015724 
		428 1.192944156626603 441 1.0934641205322642 450 1.1862995520487922 464 1.0222928355957839 
		480 1.2672516300787522 492 1.1893930924903402 504 1.230649797367052 510 1.230649797367052 
		620 1.230649797367052 626 1.2075386142335165 630 1.0642847791216798 638 0.88773783857580213 
		670 1.0813501929757026 680 1.1171713383472865 690 1.1239359907062032 706 1.1239359907062032 
		714 0.82486114281638323 720 1.179743872330647 750 1.1915279007744661 760 1.1673963962917533 
		770 1.1815023507332219 790 1.1644594232305108 795 1.0630012843394017 800 1.2291348171952401 
		810 1.2228281616066061 821 1.2228281616066061 830 1.2228281616066061 837 1.2228281616066061 
		843 1.2228281616066061 850 1.2228281616066061 860 1.222828161606607 869 1.1429546755773889 
		875 1.2017647252141905 890 1.2097329695513477 898 1.1523034531205854 905 1.0336572743088719 
		912 1.1917895859573995 920 1.1648450495163485 930 1.1706787567430565 937 1.2425042426475539 
		950 1.2483143421216818 970 1.2593205487904804;
	setAttr -s 60 ".kit[2:59]"  9 9 10 10 10 10 10 10 
		10 10 10 10 9 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 9 9 9 9 10 10 10 9 9 10 10 10 10 10 
		10 10 10 10 10 10 9 9 10 10 10 10 10 10 10 1;
	setAttr -s 60 ".kot[2:59]"  9 9 10 10 10 10 10 10 
		10 10 10 10 9 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 9 9 9 9 10 10 10 9 9 10 10 10 10 10 
		10 10 10 10 10 10 9 9 10 10 10 10 10 10 10 1;
	setAttr -s 60 ".kix[59]"  1;
	setAttr -s 60 ".kiy[59]"  0;
	setAttr -s 60 ".kox[59]"  1;
	setAttr -s 60 ".koy[59]"  0;
createNode animCurveTL -n "animCurveTL1085";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 60 ".ktv[0:59]"  0 -3.5437860563066366 50 -3.524354276443308 
		65 -3.761567899446725 81 -3.761567899446725 140 -3.7337544554192319 150 -3.7296125134448732 
		160 -3.6192421154387686 168 -3.6342871087148954 178 -3.627555540785929 230 -3.6289851739774797 
		242 -3.6206165972134468 275 -3.6206165972134468 290 -3.6356848006919327 300 -3.6356848006919327 
		350 -3.6356848006919327 400 -3.6356848006919327 411 -3.6300392282566833 420 -3.66157257680669 
		428 -3.3689364219122875 441 -2.8596169532933238 450 -2.0442496335764848 464 -1.3600249299844891 
		480 -0.15902823833887636 492 -0.81593857023588201 504 -0.74535442105071537 510 -0.68961017407091474 
		620 -0.74492243384993417 626 -0.73531149474223712 630 -0.726035204657554 638 -0.70671571189854498 
		670 -0.75916268459512704 680 -0.7408973796934698 690 -0.74378196401342567 706 -0.74378196401342567 
		714 -0.41710822527281644 720 -0.93347990521694768 750 -0.75225736858571923 760 -0.60295454920886271 
		770 -0.7228313329787861 790 -0.65452532148434006 795 -0.67976862199967214 800 -0.2127866261161025 
		810 -0.30744534212515978 821 -0.30744534212515978 830 -0.30744534212515978 837 -0.30744534212515978 
		843 -0.30744534212515978 850 -0.30744534212515978 860 -0.18962599871127811 869 -0.6163459942770293 
		875 -0.7553541830507049 890 -0.6781690968646128 898 -1.191588274179302 905 -1.8195886583420389 
		912 -2.7184604871058031 920 -3.2361084062959304 930 -3.6685571606903649 937 -3.7930094368479774 
		950 -3.4222545450500794 970 -3.5437860563066366;
	setAttr -s 60 ".kit[2:59]"  9 9 10 10 10 10 10 10 
		10 10 10 10 9 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 9 10 10 9 9 9 10 10 10 10 10 
		10 10 10 10 10 10 9 9 10 10 10 10 10 10 10 1;
	setAttr -s 60 ".kot[2:59]"  9 9 10 10 10 10 10 10 
		10 10 10 10 9 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 9 10 10 9 9 9 10 10 10 10 10 
		10 10 10 10 10 10 9 9 10 10 10 10 10 10 10 1;
	setAttr -s 60 ".kix[59]"  1;
	setAttr -s 60 ".kiy[59]"  0;
	setAttr -s 60 ".kox[59]"  1;
	setAttr -s 60 ".koy[59]"  0;
createNode animCurveTL -n "animCurveTL1086";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 60 ".ktv[0:59]"  0 0.83189686284409969 50 0.7463675643365717 
		65 0.69409885708929142 81 0.69409885708929142 140 0.73933338516029501 150 0.68385999773908757 
		160 0.49344607344294122 168 0.76722933676237193 178 0.69281751869573704 230 0.72204849382310399 
		242 0.62968736202853215 275 0.62968736202853215 290 0.44943595148798177 300 0.51038125831096615 
		350 0.51038125831096615 400 0.54370605866956279 411 0.48037335015646143 420 0.6431073445408072 
		428 0.79740962792676717 441 0.87793894532697614 450 0.86828648624565119 464 0.8603867224476458 
		480 0.76583399649959694 492 0.83938497186405225 504 0.84894386782896181 510 0.91178847598722124 
		620 0.85451740390809672 626 0.85454697470330376 630 0.81819662803631221 638 0.79111575047396943 
		670 0.9027235036383976 680 0.83152087861187385 690 0.86555053504885071 706 0.86555053504885071 
		714 0.64149694126474277 720 0.57739338985075095 750 0.65499355054443631 760 0.68218856819715101 
		770 0.54880802922086669 790 0.59313229168470183 795 0.64311121813214367 800 0.87302250558594308 
		810 0.82458042232856199 821 0.82458042232856199 830 0.82458042232856199 837 0.82458042232856199 
		843 0.82458042232856199 850 0.82458042232856199 860 0.81645241877245034 869 0.67732304450236991 
		875 0.60878625780003393 890 0.58022003133224131 898 0.62268560766520897 905 0.60999001544867026 
		912 0.71488043021531122 920 0.68200668235455963 930 0.74933034809505461 937 0.74176740219081161 
		950 0.83633234395000677 970 0.83189686284409969;
	setAttr -s 60 ".kit[2:59]"  9 9 10 10 10 10 9 9 
		10 10 3 10 9 1 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 9 10 10 9 10 9 9 10 10 10 10 
		10 10 10 10 10 10 9 9 10 10 10 10 10 10 10 1;
	setAttr -s 60 ".kot[2:59]"  9 9 10 10 10 10 9 9 
		10 10 3 10 9 1 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 9 10 10 9 10 9 9 10 10 10 10 
		10 10 10 10 10 10 9 9 10 10 10 10 10 10 10 1;
	setAttr -s 60 ".kix[15:59]"  0.99963408708572388 0.98906636238098145 
		0.87270098924636841 0.94807279109954834 1 1 1 0.99974697828292847 1 1 0.99999904632568359 
		1 1 1 1 0.99958378076553345 1 1 0.96294724941253662 0.85086196660995483 0.99993681907653809 
		0.99692553281784058 1 0.99605798721313477 0.99365776777267456 1 1 1 1 1 1 1 1 1 0.92351377010345459 
		0.99051523208618164 0.99983572959899902 1 1 1 1 1 1 1 0.99732357263565063;
	setAttr -s 60 ".kiy[15:59]"  0.027050558477640152 0.14747162163257599 
		0.48825511336326599 0.31805360317230225 0 0 0 -0.022496180608868599 0 0 0.0014414303004741669 
		0 0 0 0 0.028848800808191299 0 0 -0.26969000697135925 -0.52538931369781494 0.011246456764638424 
		0.078354701399803162 0 -0.088705211877822876 0.11244603246450424 0 0 0 0 0 0 0 0 
		0 -0.38356509804725647 -0.13740310072898865 0.018126614391803741 0 0 0 0 0 0 0 -0.07311461865901947;
	setAttr -s 60 ".kox[15:59]"  0.99963408708572388 0.98906636238098145 
		0.87270098924636841 0.94807279109954834 1 1 1 0.99974697828292847 1 1 0.99999904632568359 
		1 1 1 1 0.99958378076553345 1 1 0.96294724941253662 0.85086196660995483 0.99993681907653809 
		0.99692553281784058 1 0.99605798721313477 0.99365776777267456 1 1 1 1 1 1 1 1 1 0.92351377010345459 
		0.99051523208618164 0.99983572959899902 1 1 1 1 1 1 1 0.99732357263565063;
	setAttr -s 60 ".koy[15:59]"  0.027050565928220749 0.14747162163257599 
		0.48825511336326599 0.31805360317230225 0 0 0 -0.022496180608868599 0 0 0.0014414303004741669 
		0 0 0 0 0.028848800808191299 0 0 -0.26969000697135925 -0.52538931369781494 0.011246456764638424 
		0.078354701399803162 0 -0.088705211877822876 0.11244603246450424 0 0 0 0 0 0 0 0 
		0 -0.38356509804725647 -0.13740310072898865 0.018126614391803741 0 0 0 0 0 0 0 -0.07311461865901947;
createNode animCurveTA -n "animCurveTA3220";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3221";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3222";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1087";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1088";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1089";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1640";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 55 ".ktv[0:54]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 172 0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 400 0 420 0 428 0 441 0 450 
		0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 0 720 
		0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 0 905 0 912 
		0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 55 ".kit[34:54]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 55 ".kot[34:54]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 55 ".kix[54]"  1;
	setAttr -s 55 ".kiy[54]"  0;
	setAttr -s 55 ".kox[54]"  1;
	setAttr -s 55 ".koy[54]"  0;
createNode animCurveTU -n "animCurveTU1641";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 55 ".ktv[0:54]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 172 0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 400 0 420 0 428 0 441 0 450 
		0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 0 720 
		0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 0 905 0 912 
		0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 55 ".kit[34:54]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 55 ".kot[34:54]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 55 ".kix[54]"  1;
	setAttr -s 55 ".kiy[54]"  0;
	setAttr -s 55 ".kox[54]"  1;
	setAttr -s 55 ".koy[54]"  0;
createNode animCurveTU -n "animCurveTU1642";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 56 ".ktv[0:55]"  0 0 50 0 65 0.4 81 0.4 140 0.4 150 0.4 
		160 0.4 168 0 172 0 178 1.8000000000000003 230 1.0000000000000002 242 0.4 275 0.4 
		290 0.4 300 0.4 350 0.4 360 0.4 400 0.4 420 0.4 428 0.4 441 0.4 450 0.4 464 0.4 480 
		0.4 492 0.4 504 0.4 510 0.4 620 0.4 626 0.4 630 0.4 638 0.4 670 0.4 680 0.4 690 0.4 
		706 0.4 720 -0.40000000000000036 760 -0.40000000000000036 770 0.19999999999999973 
		790 0.19999999999999973 800 10 810 10 821 10 830 10 837 10 843 10 850 10 860 10 875 
		0.19999999999999973 890 0.19999999999999973 905 1.4999999999999996 912 1.4999999999999996 
		920 1.4999999999999996 930 0.74400301445403505 937 0 950 0 970 0;
	setAttr -s 56 ".kit[34:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kot[34:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kix[55]"  1;
	setAttr -s 56 ".kiy[55]"  0;
	setAttr -s 56 ".kox[55]"  1;
	setAttr -s 56 ".koy[55]"  0;
createNode animCurveTU -n "animCurveTU1643";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 56 ".ktv[0:55]"  0 0 50 0.30434782242807662 65 0.4 81 0.4 
		140 0.4 150 0.4 160 0.4 168 0 172 0 178 1.8000000000000003 230 1.0000000000000002 
		242 0.4 275 0.4 290 0.4 300 0.4 350 0.4 360 0.4 400 0.4 420 0.4 428 0.4 441 0.4 450 
		0.4 464 0.4 480 0.4 492 0.4 504 0.4 510 0.4 620 0.4 626 0.4 630 0.4 638 0.4 670 0.4 
		680 0.4 690 0.4 706 0.4 720 -0.40000000000000036 760 -0.40000000000000036 770 0.19999999999999973 
		790 -0.40000000000000036 800 10 810 10 821 10 830 10 837 10 843 10 850 10 860 10 
		875 10 890 10 905 1.4999999999999996 912 1.4999999999999996 920 1.4999999999999996 
		930 1.4999999999999996 937 1.4999999999999996 950 1.4999999999999996 970 0;
	setAttr -s 56 ".kit[34:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kot[34:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kix[55]"  0.96761733293533325;
	setAttr -s 56 ".kiy[55]"  0.25242191553115845;
	setAttr -s 56 ".kox[55]"  0.96761733293533325;
	setAttr -s 56 ".koy[55]"  0.25242191553115845;
createNode animCurveTU -n "animCurveTU1644";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 56 ".ktv[0:55]"  0 0 50 0.30434782242807662 65 0.4 81 0.4 
		140 0.4 150 0.4 160 0.4 168 0 172 0 178 1.8000000000000003 230 1.0000000000000002 
		242 0.4 275 0.4 290 0.4 300 0.4 350 0.4 360 0.4 400 0.4 420 0.4 428 0.4 441 0.4 450 
		0.4 464 0.4 480 0.4 492 0.4 504 0.4 510 0.4 620 0.4 626 0.4 630 0.4 638 0.4 670 0.4 
		680 0.4 690 0.4 706 0.4 720 -0.40000000000000036 760 -0.40000000000000036 770 0.19999999999999973 
		790 -0.40000000000000036 800 10 810 10 821 10 830 10 837 10 843 10 850 10 860 10 
		875 10 890 10 905 1.4999999999999996 912 1.4999999999999996 920 1.4999999999999996 
		930 1.4999999999999996 937 1.4999999999999996 950 1.4999999999999996 970 0;
	setAttr -s 56 ".kit[34:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kot[34:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kix[55]"  0.96761733293533325;
	setAttr -s 56 ".kiy[55]"  0.25242191553115845;
	setAttr -s 56 ".kox[55]"  0.96761733293533325;
	setAttr -s 56 ".koy[55]"  0.25242191553115845;
createNode animCurveTU -n "animCurveTU1645";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 56 ".ktv[0:55]"  0 0 50 0 65 0.4 81 0.4 140 0.4 150 0.4 
		160 0.4 168 0 172 0 178 1.8000000000000003 230 1.0000000000000002 242 0.4 275 0.4 
		290 0.4 300 0.4 350 0.4 360 0.4 400 0.4 420 0.4 428 0.4 441 0.4 450 0.4 464 0.4 480 
		0.4 492 0.4 504 0.4 510 0.4 620 0.4 626 0.4 630 0.4 638 0.4 670 0.4 680 0.4 690 0.4 
		706 0.4 720 -0.40000000000000036 760 -0.40000000000000036 770 0.19999999999999973 
		790 0.19999999999999973 800 10 810 10 821 10 830 10 837 10 843 10 850 10 860 10 875 
		0.19999999999999973 890 0.19999999999999973 905 1.4999999999999996 912 1.4999999999999996 
		920 1.4999999999999996 930 0.74400301445403505 937 0 950 0 970 0;
	setAttr -s 56 ".kit[34:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kot[34:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kix[55]"  1;
	setAttr -s 56 ".kiy[55]"  0;
	setAttr -s 56 ".kox[55]"  1;
	setAttr -s 56 ".koy[55]"  0;
createNode animCurveTU -n "animCurveTU1646";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 56 ".ktv[0:55]"  0 0 50 0.30434782242807662 65 0.4 81 0.4 
		140 0.4 150 0.4 160 0.4 168 0 172 0 178 1.8000000000000003 230 1.0000000000000002 
		242 0.4 275 0.4 290 0.4 300 0.4 350 0.4 360 0.4 400 0.4 420 0.4 428 0.4 441 0.4 450 
		0.4 464 0.4 480 0.4 492 0.4 504 0.4 510 0.4 620 0.4 626 0.4 630 0.4 638 0.4 670 0.4 
		680 0.4 690 0.4 706 0.4 720 -0.40000000000000036 760 -0.40000000000000036 770 0.19999999999999973 
		790 -0.40000000000000036 800 10 810 10 821 10 830 10 837 10 843 10 850 10 860 10 
		875 10 890 10 905 1.4999999999999996 912 1.4999999999999996 920 1.4999999999999996 
		930 1.4999999999999996 937 1.4999999999999996 950 1.4999999999999996 970 0;
	setAttr -s 56 ".kit[34:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kot[34:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kix[55]"  0.96761733293533325;
	setAttr -s 56 ".kiy[55]"  0.25242191553115845;
	setAttr -s 56 ".kox[55]"  0.96761733293533325;
	setAttr -s 56 ".koy[55]"  0.25242191553115845;
createNode animCurveTA -n "animCurveTA3223";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3224";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3225";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3226";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		-24.240283762212286 178 -24.240283762212286 230 -24.240283762212286 242 -12.424386115152553 
		275 -12.424386115152553 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3227";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3228";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3229";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3230";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3231";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3232";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 -5.8290563674033722 
		441 -10.599671614748683 450 -4.3090022306225482 464 0 480 0 492 0 504 0 510 0 620 
		0 626 0 630 0 638 0 670 0 680 0 690 0 706 0 720 0 750 0 760 0 790 0 800 0 810 0 821 
		0 830 0 837 0 843 0 850 0 860 0 875 0 890 0 905 0 912 0 920 0 930 0 937 0 950 0 970 
		0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3233";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3234";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3235";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3236";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3237";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3238";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1647";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 370 1 380 1 400 1 420 1 428 1 441 
		1 450 1 464 1 480 1 492 1 504 1 510 1 620 1 626 1 630 1 638 1 670 1 680 1 690 1 706 
		1 720 1 750 1 760 1 790 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 1 890 
		1 905 1 912 1 920 1 930 1 937 1 950 1 970 1;
	setAttr -s 57 ".kit[56]"  1;
	setAttr -s 57 ".kot[0:56]"  5 5 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 9 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 5 5 5 5 5;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
createNode animCurveTU -n "animCurveTU1648";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[56]"  1;
	setAttr -s 57 ".kot[0:56]"  5 5 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 9 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 5 5 5 5 5;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
createNode animCurveTU -n "animCurveTU1649";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 10 50 10 65 10 81 10 140 10 150 10 160 
		10 168 10 178 10 230 10 242 10 275 10 290 10 300 10 350 10 360 10 370 10 380 10 400 
		10 420 10 428 10 441 10 450 10 464 10 480 10 492 10 504 10 510 10 620 10 626 10 630 
		10 638 10 670 10 680 10 690 10 706 10 720 10 750 10 760 10 790 10 800 10 810 10 821 
		10 830 10 837 10 843 10 850 10 860 10 875 10 890 10 905 10 912 10 920 10 930 10 937 
		10 950 10 970 10;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1090";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1091";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1092";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1650";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 10 50 10 65 10 81 10 140 10 150 10 160 
		10 168 10 178 10 230 10 242 10 275 10 290 10 300 10 350 10 360 10 370 10 380 10 400 
		10 420 10 428 10 441 10 450 10 464 10 480 10 492 10 504 10 510 10 620 10 626 10 630 
		10 638 10 670 10 680 10 690 10 706 10 720 10 750 10 760 10 790 10 800 10 810 10 821 
		10 830 10 837 10 843 10 850 10 860 10 875 10 890 10 905 10 912 10 920 10 930 10 937 
		10 950 10 970 10;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1093";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.32809120925015067 50 0.32809120925015067 
		65 0.32809120925015067 81 0.32809120925015067 140 0.32809120925015067 150 0.32809120925015067 
		160 0.63352780668138287 168 1.2698685243958368 178 1.2698685243958368 230 1.2698685243958368 
		242 1.2698685243958368 275 1.2698685243958368 290 0.32809120925015067 300 0.32809120925015067 
		350 0.32809120925015067 360 0.32809120925015067 370 0.32809120925015067 380 0.32809120925015067 
		400 0.32809120925015067 420 0.32809120925015067 428 0.1561943303120775 441 0.38124702819644873 
		450 0.077290926812239993 464 -0.08108279411062165 480 0.075703298429811675 492 -0.08108279411062165 
		504 -0.08108279411062165 510 -0.08108279411062165 620 -0.08108279411062165 626 -0.08108279411062165 
		630 -0.028848059705081044 638 0.023387421930386194 670 0.023387421930386194 680 0.023387421930386194 
		690 0.023387421930386194 706 0.023387421930386194 720 0.023387421930386194 750 0.037627086939570495 
		760 0.0518667519487548 790 0.0518667519487548 800 0.043171773651945342 810 0.044491854623602771 
		821 0.044491854623602771 830 0.044491854623602771 837 0.044491854623602771 843 0.044491854623602771 
		850 0.044491854623602771 860 0.044491854623602771 875 0.0518667519487548 890 0.0518667519487548 
		905 0.0518667519487548 912 0.061832477284200764 920 0.074009126040702949 930 0.20206598228219094 
		937 0.32809120925015067 950 0.32809120925015067 970 0.32809120925015067;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1094";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 1.0303807660507804 50 1.0303807660507804 
		65 1.0303807660507804 81 1.0303807660507804 140 1.0303807660507804 150 1.0303807660507804 
		160 0.74697346057827263 168 0.48751976484875575 178 0.48751976484875575 230 0.48751976484875575 
		242 0.48751976484875575 275 0.48751976484875575 290 1.0303807660507804 300 1.0303807660507804 
		350 1.0303807660507804 360 1.0303807660507804 370 1.0303807660507804 380 1.0303807660507804 
		400 1.0303807660507804 420 1.0303807660507804 428 1.2694792625672331 441 1.1126781270105095 
		450 1.1613698865456237 464 1.2577582188181524 480 1.3314446866239573 492 1.2577582188181524 
		504 1.2577582188181524 510 1.2577582188181524 620 1.2577582188181524 626 1.2577582188181524 
		630 1.2977979870436958 638 1.3378383280473609 670 1.3378383280473609 680 1.3378383280473609 
		690 1.3378383280473609 706 1.3378383280473609 720 1.3378383280473609 750 1.3275770193067493 
		760 1.3173157105661375 790 1.3173157105661375 800 1.35852495015321 810 1.352803904387244 
		821 1.352803904387244 830 1.352803904387244 837 1.352803904387244 843 1.352803904387244 
		850 1.352803904387244 860 1.352803904387244 875 1.3173157105661375 890 1.3173157105661375 
		905 1.3173157105661375 912 1.3207178559337169 920 1.3248747765556639 930 1.176450385667176 
		937 1.0303807660507804 950 1.0303807660507804 970 1.0303807660507804;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1095";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 -0.092428067553769991 50 -0.092428067553769991 
		65 -0.092428067553769991 81 -0.092428067553769991 140 -0.092428067553769991 150 -0.092428067553769991 
		160 -0.2941525906023062 168 -0.22189573302318588 178 -0.22189573302318588 230 -0.22189573302318588 
		242 -0.22189573302318588 275 -0.22189573302318588 290 -0.092428067553769991 300 -0.092428067553769991 
		350 -0.092428067553769991 360 -0.092428067553769991 370 -0.092428067553769991 380 
		-0.092428067553769991 400 -0.092428067553769991 420 -0.092428067553769991 428 0.25128001472682804 
		441 0.23834809158399739 450 -0.0098116098561057772 464 0.073798840625125164 480 0.32446781808198327 
		492 0.073798840625125164 504 0.073798840625125164 510 0.073798840625125164 620 0.073798840625125164 
		626 0.073798840625125164 630 -0.052900883420661668 638 -0.17960241993523154 670 -0.17960241993523154 
		680 -0.17960241993523154 690 -0.17960241993523154 706 -0.17960241993523154 720 -0.17960241993523154 
		750 -0.14212618829200041 760 -0.10464995664876932 790 -0.10464995664876932 800 -0.21739787303772773 
		810 -0.20709899365445766 821 -0.20709899365445766 830 -0.20709899365445766 837 -0.20709899365445766 
		843 -0.20709899365445766 850 -0.20709899365445766 860 -0.20709899365445766 875 -0.10464995664876932 
		890 -0.10464995664876932 905 -0.10464995664876932 912 -0.098108850948375265 920 -0.090116583058996572 
		930 -0.09161441993266109 937 -0.092428067553769991 950 -0.092428067553769991 970 
		-0.092428067553769991;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3239";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3240";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3241";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1096";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1097";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1098";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1651";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 59 ".ktv[0:58]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 370 1 380 1 400 1 420 1 428 1 441 
		1 450 1 464 1 472 1 480 1 492 1 504 1 510 1 620 1 626 1 630 1 638 1 670 1 680 1 690 
		1 706 1 720 1 750 1 760 1 790 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 
		1 890 1 905 1 907 1 912 1 920 1 930 1 937 1 950 1 970 1;
	setAttr -s 59 ".kit[36:58]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 59 ".kot[36:58]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 59 ".kix[58]"  1;
	setAttr -s 59 ".kiy[58]"  0;
	setAttr -s 59 ".kox[58]"  1;
	setAttr -s 59 ".koy[58]"  0;
createNode animCurveTU -n "animCurveTU1652";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 59 ".ktv[0:58]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 370 1 380 1 400 1 420 1 428 1 441 
		1 450 1 464 1 472 1 480 1 492 1 504 1 510 1 620 1 626 1 630 1 638 1 670 1 680 1 690 
		1 706 1 720 1 750 1 760 1 790 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 
		1 890 1 905 1 907 1 912 1 920 1 930 1 937 1 950 1 970 1;
	setAttr -s 59 ".kit[36:58]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 59 ".kot[36:58]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 59 ".kix[58]"  1;
	setAttr -s 59 ".kiy[58]"  0;
	setAttr -s 59 ".kox[58]"  1;
	setAttr -s 59 ".koy[58]"  0;
createNode animCurveTU -n "animCurveTU1653";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 59 ".ktv[0:58]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 472 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 
		0 706 0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 
		0 890 0 905 0 907 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 59 ".kit[36:58]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 59 ".kot[36:58]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 59 ".kix[58]"  1;
	setAttr -s 59 ".kiy[58]"  0;
	setAttr -s 59 ".kox[58]"  1;
	setAttr -s 59 ".koy[58]"  0;
createNode animCurveTU -n "animCurveTU1654";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 59 ".ktv[0:58]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 472 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 
		0 706 0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 
		0 890 0 905 0 907 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 59 ".kit[36:58]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 59 ".kot[36:58]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 59 ".kix[58]"  1;
	setAttr -s 59 ".kiy[58]"  0;
	setAttr -s 59 ".kox[58]"  1;
	setAttr -s 59 ".koy[58]"  0;
createNode animCurveTU -n "animCurveTU1655";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 59 ".ktv[0:58]"  0 25 50 25 65 25 81 25 140 25 150 25 160 
		25 168 25 178 25 230 25 242 25 275 25 290 25 300 25 350 25 360 25 370 25 380 25 400 
		25 420 25 428 25 441 25 450 25 464 25 472 25 480 25 492 25 504 25 510 25 620 25 626 
		25 630 25 638 25 670 25 680 25 690 25 706 25 720 25 750 25 760 25 790 25 800 25 810 
		25 821 25 830 25 837 25 843 25 850 25 860 25 875 25 890 25 905 25 907 25 912 25 920 
		25 930 25 937 25 950 25 970 25;
	setAttr -s 59 ".kit[36:58]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 59 ".kot[36:58]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 59 ".kix[58]"  1;
	setAttr -s 59 ".kiy[58]"  0;
	setAttr -s 59 ".kox[58]"  1;
	setAttr -s 59 ".koy[58]"  0;
createNode animCurveTU -n "animCurveTU1656";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 59 ".ktv[0:58]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 472 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 
		0 706 0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 
		0 890 0 905 0 907 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 59 ".kit[36:58]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 59 ".kot[36:58]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 59 ".kix[58]"  1;
	setAttr -s 59 ".kiy[58]"  0;
	setAttr -s 59 ".kox[58]"  1;
	setAttr -s 59 ".koy[58]"  0;
createNode animCurveTU -n "animCurveTU1657";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 59 ".ktv[0:58]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 472 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 
		0 706 0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 
		0 890 0 905 0 907 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 59 ".kit[36:58]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 59 ".kot[36:58]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 59 ".kix[58]"  1;
	setAttr -s 59 ".kiy[58]"  0;
	setAttr -s 59 ".kox[58]"  1;
	setAttr -s 59 ".koy[58]"  0;
createNode animCurveTU -n "animCurveTU1658";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 59 ".ktv[0:58]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 472 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 
		0 706 0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 
		0 890 0 905 0 907 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 59 ".kit[36:58]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 59 ".kot[36:58]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 59 ".kix[58]"  1;
	setAttr -s 59 ".kiy[58]"  0;
	setAttr -s 59 ".kox[58]"  1;
	setAttr -s 59 ".koy[58]"  0;
createNode animCurveTA -n "animCurveTA3242";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 60 ".ktv[0:59]"  0 93.873882999977099 50 93.873882999977099 
		65 93.873882999977099 81 93.873882999977099 140 93.873882999977099 150 93.873882999977099 
		160 93.873882999977099 168 93.873882999977099 178 93.873882999977099 230 93.873882999977099 
		242 93.873882999977099 275 93.873882999977099 290 93.873882999977099 300 93.873882999977099 
		350 93.873882999977099 360 93.873882999977099 370 93.873882999977099 380 93.873882999977099 
		400 93.873882999977099 420 93.873882999977099 428 93.873882999977099 441 169.26279766952945 
		450 173.2210028352018 464 169.26279766952945 472 84.784413765697948 480 84.784413765697948 
		492 84.784413765697948 504 84.784413765697948 510 84.784413765697948 620 84.784413765697948 
		626 84.784413765697948 630 84.784413765697948 638 84.784413765697948 670 84.784413765697948 
		680 84.784413765697948 690 84.784413765697948 706 84.784413765697948 720 84.784413765697948 
		750 84.784413765697948 760 84.784413765697948 790 84.784413765697948 800 84.784413765697948 
		810 84.784413765697948 821 84.784413765697948 830 84.784413765697948 837 84.784413765697948 
		843 84.784413765697948 850 84.784413765697948 860 84.784413765697948 875 84.784413765697948 
		890 84.784413765697948 898 31.708603876666292 905 7.6728250519002721 907 7.6728250519002721 
		912 7.6728250519002721 920 7.6728250519002721 930 41.745237216811212 937 93.873882999977099 
		950 93.873882999977099 970 93.873882999977099;
	setAttr -s 60 ".kit[36:59]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 60 ".kot[36:59]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 60 ".kix[59]"  1;
	setAttr -s 60 ".kiy[59]"  0;
	setAttr -s 60 ".kox[59]"  1;
	setAttr -s 60 ".koy[59]"  0;
createNode animCurveTA -n "animCurveTA3243";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 60 ".ktv[0:59]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 11.47993613396738 464 0 472 -32.956164036317588 480 -32.956164036317588 492 
		-32.956164036317588 504 -32.956164036317588 510 -32.956164036317588 620 -32.956164036317588 
		626 -32.956164036317588 630 -32.956164036317588 638 -32.956164036317588 670 -32.956164036317588 
		680 -32.956164036317588 690 -32.956164036317588 706 -32.956164036317588 720 -32.956164036317588 
		750 -32.956164036317588 760 -32.956164036317588 790 -32.956164036317588 800 -32.956164036317588 
		810 -32.956164036317588 821 -32.956164036317588 830 -32.956164036317588 837 -32.956164036317588 
		843 -32.956164036317588 850 -32.956164036317588 860 -32.956164036317588 875 -32.956164036317588 
		890 -32.956164036317588 898 -18.671535318132701 905 6.0142769980126607 907 6.0142769980126607 
		912 6.0142769980126607 920 6.0142769980126607 930 -26.048410061015616 937 0 950 0 
		970 0;
	setAttr -s 60 ".kit[36:59]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 60 ".kot[36:59]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 60 ".kix[59]"  1;
	setAttr -s 60 ".kiy[59]"  0;
	setAttr -s 60 ".kox[59]"  1;
	setAttr -s 60 ".koy[59]"  0;
createNode animCurveTA -n "animCurveTA3244";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 60 ".ktv[0:59]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 41.947127007346829 464 -40.079058337511242 472 32.532079582450208 480 32.532079582450208 
		492 32.532079582450208 504 32.532079582450208 510 32.532079582450208 620 32.532079582450208 
		626 32.532079582450208 630 32.532079582450208 638 32.532079582450208 670 32.532079582450208 
		680 32.532079582450208 690 32.532079582450208 706 32.532079582450208 720 32.532079582450208 
		750 32.532079582450208 760 32.532079582450208 790 32.532079582450208 800 32.532079582450208 
		810 32.532079582450208 821 32.532079582450208 830 32.532079582450208 837 32.532079582450208 
		843 32.532079582450208 850 32.532079582450208 860 32.532079582450208 875 32.532079582450208 
		890 32.532079582450208 898 21.184910410299668 905 -21.394643465736873 907 0.34566212375141409 
		912 0.34566212375141409 920 0.34566212375141409 930 31.853466163247511 937 0 950 
		0 970 0;
	setAttr -s 60 ".kit[36:59]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 60 ".kot[36:59]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 60 ".kix[59]"  1;
	setAttr -s 60 ".kiy[59]"  0;
	setAttr -s 60 ".kox[59]"  1;
	setAttr -s 60 ".koy[59]"  0;
createNode animCurveTL -n "animCurveTL1099";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 60 ".ktv[0:59]"  0 1.2768283457414795 50 1.2768283457414795 
		65 1.2768283457414795 81 1.2768283457414795 140 1.2768283457414795 150 1.2768283457414795 
		160 1.2768283457414795 168 1.2768283457414795 178 1.2768283457414795 230 1.2768283457414795 
		242 1.2768283457414795 275 1.2768283457414795 290 1.2768283457414795 300 1.2768283457414795 
		350 1.2768283457414795 360 1.2768283457414795 370 1.2768283457414795 380 1.2768283457414795 
		400 1.2768283457414795 420 1.2768283457414795 428 1.2768283457414795 441 1.2768283457414795 
		450 1.4696674417963873 464 1.2111080505094087 472 1.2496494386858423 480 1.2496494386858423 
		492 1.2496494386858423 504 1.2496494386858423 510 1.2496494386858423 620 1.2496494386858423 
		626 1.2496494386858423 630 1.2496494386858423 638 1.2496494386858423 670 1.2496494386858423 
		680 1.2496494386858423 690 1.2496494386858423 706 1.2496494386858423 720 1.2496494386858423 
		750 1.2496494386858423 760 1.2496494386858423 790 1.2496494386858423 800 1.2496494386858423 
		810 1.2496494386858423 821 1.2496494386858423 830 1.2496494386858423 837 1.2496494386858423 
		843 1.2496494386858423 850 1.2496494386858423 860 1.2496494386858423 875 1.2496494386858423 
		890 1.2496494386858423 898 1.3012755584858091 905 1.2677671038114477 907 1.2677671038114477 
		912 1.2677671038114477 920 1.2677671038114477 930 1.3116150197576237 937 1.2768283457414795 
		950 1.2768283457414795 970 1.2768283457414795;
	setAttr -s 60 ".kit[36:59]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 3 3 10 10 10 10 10 1;
	setAttr -s 60 ".kot[36:59]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 3 3 10 10 10 10 10 1;
	setAttr -s 60 ".kix[59]"  1;
	setAttr -s 60 ".kiy[59]"  0;
	setAttr -s 60 ".kox[59]"  1;
	setAttr -s 60 ".koy[59]"  0;
createNode animCurveTL -n "animCurveTL1100";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 60 ".ktv[0:59]"  0 -3.4570210806142736 50 -3.4570210806142736 
		65 -3.4570210806142736 81 -3.4570210806142736 140 -3.4570210806142736 150 -3.4570210806142736 
		160 -3.4570210806142736 168 -3.4570210806142736 178 -3.4570210806142736 230 -3.4570210806142736 
		242 -3.4570210806142736 275 -3.4570210806142736 290 -3.4570210806142736 300 -3.4570210806142736 
		350 -3.4570210806142736 360 -3.4570210806142736 370 -3.4570210806142736 380 -3.4570210806142736 
		400 -3.4570210806142736 420 -3.4570210806142736 428 -3.4570210806142736 441 -3.6923611474682603 
		450 -2.4541402073109495 464 -0.680245189883941 472 -0.38972872129662461 480 -0.38972872129662461 
		492 -0.38972872129662461 504 -0.38972872129662461 510 -0.38972872129662461 620 -0.38972872129662461 
		626 -0.38972872129662461 630 -0.38972872129662461 638 -0.38972872129662461 670 -0.38972872129662461 
		680 -0.38972872129662461 690 -0.38972872129662461 706 -0.38972872129662461 720 -0.38972872129662461 
		750 -0.38972872129662461 760 -0.38972872129662461 790 -0.38972872129662461 800 -0.38972872129662461 
		810 -0.38972872129662461 821 -0.38972872129662461 830 -0.38972872129662461 837 -0.38972872129662461 
		843 -0.38972872129662461 850 -0.38972872129662461 860 -0.38972872129662461 875 -0.38972872129662461 
		890 -0.38972872129662461 898 -1.3552781719318427 905 -2.6849245466760099 907 -2.7910112987919327 
		912 -2.7910112987919327 920 -2.7910112987919327 930 -2.9957387252965639 937 -3.4570210806142736 
		950 -3.4570210806142736 970 -3.4570210806142736;
	setAttr -s 60 ".kit[36:59]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 3 3 10 10 10 10 10 1;
	setAttr -s 60 ".kot[36:59]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 3 3 10 10 10 10 10 1;
	setAttr -s 60 ".kix[59]"  1;
	setAttr -s 60 ".kiy[59]"  0;
	setAttr -s 60 ".kox[59]"  1;
	setAttr -s 60 ".koy[59]"  0;
createNode animCurveTL -n "animCurveTL1101";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 60 ".ktv[0:59]"  0 0.48689012283932087 50 0.48689012283932087 
		65 0.48689012283932087 81 0.48689012283932087 140 0.48689012283932087 150 0.48689012283932087 
		160 0.48689012283932087 168 0.48689012283932087 178 0.48689012283932087 230 0.48689012283932087 
		242 0.48689012283932087 275 0.48689012283932087 290 0.48689012283932087 300 0.48689012283932087 
		350 0.48689012283932087 360 0.48689012283932087 370 0.48689012283932087 380 0.48689012283932087 
		400 0.48689012283932087 420 0.48689012283932087 428 0.48689012283932087 441 0.68432321929460183 
		450 0.47987833016936099 464 0.60409982904558535 472 0.54982770932241254 480 0.54982770932241254 
		492 0.54982770932241254 504 0.54982770932241254 510 0.54982770932241254 620 0.54982770932241254 
		626 0.54982770932241254 630 0.54982770932241254 638 0.54982770932241254 670 0.54982770932241254 
		680 0.54982770932241254 690 0.54982770932241254 706 0.54982770932241254 720 0.54982770932241254 
		750 0.54982770932241254 760 0.54982770932241254 790 0.54982770932241254 800 0.54982770932241254 
		810 0.54982770932241254 821 0.54982770932241254 830 0.54982770932241254 837 0.54982770932241254 
		843 0.54982770932241254 850 0.54982770932241254 860 0.54982770932241254 875 0.54982770932241254 
		890 0.54982770932241254 898 0.4996670426783868 905 0.49787885055806425 907 0.49787885055806425 
		912 0.49787885055806425 920 0.49787885055806425 930 0.49408117259821671 937 0.48689012283932087 
		950 0.48689012283932087 970 0.48689012283932087;
	setAttr -s 60 ".kit[36:59]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 3 3 10 10 10 10 10 1;
	setAttr -s 60 ".kot[36:59]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 3 3 10 10 10 10 10 1;
	setAttr -s 60 ".kix[59]"  1;
	setAttr -s 60 ".kiy[59]"  0;
	setAttr -s 60 ".kox[59]"  1;
	setAttr -s 60 ".koy[59]"  0;
createNode animCurveTU -n "animCurveTU1659";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[56]"  1;
	setAttr -s 57 ".kot[0:56]"  5 5 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 9 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 5 5 5 5 5;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
createNode animCurveTU -n "animCurveTU1660";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 370 1 380 1 400 1 420 1 428 1 441 
		1 450 1 464 1 480 1 492 1 504 1 510 1 620 1 626 1 630 1 638 1 670 1 680 1 690 1 706 
		1 720 1 750 1 760 1 790 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 1 890 
		1 905 1 912 1 920 1 930 1 937 1 950 1 970 1;
	setAttr -s 57 ".kit[56]"  1;
	setAttr -s 57 ".kot[0:56]"  5 5 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 9 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 5 5 5 5 5;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
createNode animCurveTU -n "animCurveTU1661";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 10 50 10 65 10 81 10 140 10 150 10 160 
		10 168 10 178 10 230 10 242 10 275 10 290 10 300 10 350 10 360 10 370 10 380 10 400 
		10 420 10 428 10 441 10 450 10 464 10 480 10 492 10 504 10 510 10 620 10 626 10 630 
		10 638 10 670 10 680 10 690 10 706 10 720 10 750 10 760 10 790 10 800 10 810 10 821 
		10 830 10 837 10 843 10 850 10 860 10 875 10 890 10 905 10 912 10 920 10 930 10 937 
		10 950 10 970 10;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1102";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1103";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1104";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1662";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 69 ".ktv[0:68]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 411 0 420 0 428 
		0 441 0 450 0 464 0 472 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 
		0 690 0 706 0 714 0 720 0 727 0 731 0 735 0 740 0 745 0 749 0 754 0 760 0 770 0 790 
		0 795 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 0 898 0 905 0 912 
		0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 69 ".kit[37:68]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 69 ".kot[37:68]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 69 ".kix[68]"  1;
	setAttr -s 69 ".kiy[68]"  0;
	setAttr -s 69 ".kox[68]"  1;
	setAttr -s 69 ".koy[68]"  0;
createNode animCurveTL -n "animCurveTL1105";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 69 ".ktv[0:68]"  0 1.1993960761131948 50 1.1993960761131948 
		65 1.1993960761131948 81 1.1993960761131948 140 1.1993960761131948 150 1.1993960761131948 
		160 0.41742268582791653 168 -0.36454986549148066 178 -0.36454986549148066 230 -0.36454986549148066 
		242 -0.3781556170221993 275 -0.3781556170221993 290 1.1993960761131948 300 1.1993960761131948 
		350 1.1993960761131948 360 1.1993960761131948 370 1.1993960761131948 380 1.1993960761131948 
		400 1.1993960761131948 411 1.1743323499396576 420 1.1993960761131948 428 0.96882328371965176 
		441 1.0891161922316361 450 2.2154564903029335 464 2.0657679291127313 472 1.5973172661715336 
		480 1.246426093216759 492 1.1536021721124299 504 1.2845546711011511 510 1.2845546711011511 
		620 1.2845546711011511 626 1.0928029774091557 630 0.85725499680613093 638 0.4062505151595337 
		670 0.71204601928437317 680 0.58064040334277855 690 0.58064040334277855 706 0.58064040334277855 
		714 0.98946918203123047 720 1.0507012473563293 727 1.035534100091859 731 1.0507012473563293 
		735 1.035534100091859 740 1.0507012473563293 745 1.035534100091859 749 1.0507012473563293 
		754 1.035534100091859 760 0.92885302092272082 770 0.89330576195619105 790 0.89330576195619105 
		795 0.80752382390554478 800 0.86758767729967812 810 0.86758767729967812 821 0.86758767729967812 
		830 0.86758767729967812 837 0.86758767729967812 843 0.86758767729967812 850 0.86758767729967812 
		860 0.86758767729967812 875 0.75583529213158285 890 0.98393811073052506 898 1.0158159444476349 
		905 1.0355957963947224 912 1.0355957963947224 920 1.0355957963947224 930 0.93077575009208813 
		937 1.1993960761131948 950 1.1993960761131948 970 1.1993960761131948;
	setAttr -s 69 ".kit[37:68]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 69 ".kot[37:68]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 69 ".kix[68]"  1;
	setAttr -s 69 ".kiy[68]"  0;
	setAttr -s 69 ".kox[68]"  1;
	setAttr -s 69 ".koy[68]"  0;
createNode animCurveTL -n "animCurveTL1106";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 69 ".ktv[0:68]"  0 -4.3631891015750739 50 -4.3631891015750739 
		65 -4.3631891015750739 81 -4.3631891015750739 140 -4.3631891015750739 150 -4.3631891015750739 
		160 -4.3241435127006129 168 -4.2850979657174975 178 -4.2850979657174975 230 -4.2850979657174975 
		242 -4.289718727148351 275 -4.289718727148351 290 -4.3631891015750739 300 -4.3631891015750739 
		350 -4.3631891015750739 360 -4.3631891015750739 370 -4.3631891015750739 380 -4.3631891015750739 
		400 -4.3631891015750739 411 -4.1371377569365189 420 -4.3631891015750739 428 -4.3391766574980881 
		441 -3.45141459260741 450 -2.2988231515662898 464 -1.664374204997515 472 -1.0217363395613051 
		480 -0.40374280228392512 492 -1.5892099779309348 504 -0.55326449265626865 510 -0.55326449265626865 
		620 -0.55326449265626865 626 -0.81952148227164923 630 -1.3302139656700493 638 -2.1615605654409391 
		670 -2.1821466344115272 680 -1.8396124711083996 690 -1.8396124711083996 706 -1.8396124711083996 
		714 -1.2371654759944357 720 -1.2436192630070397 727 -1.5042257852839256 731 -1.2436192630070397 
		735 -1.5042257852839256 740 -1.2436192630070397 745 -1.5042257852839256 749 -1.2436192630070397 
		754 -1.5042257852839256 760 -1.2326450876913051 770 -1.2396714378120746 790 -1.2396714378120746 
		795 -1.3474644662229436 800 -1.2414228930500566 810 -1.2414228930500566 821 -1.2414228930500566 
		830 -1.2414228930500566 837 -1.2414228930500566 843 -1.2414228930500566 850 -1.2414228930500566 
		860 -1.2414228930500566 875 -1.8085679061072681 890 -1.3391594571586005 898 -1.733790755160642 
		905 -1.7175254329772303 912 -1.7175254329772303 920 -1.7175254329772303 930 -3.3902368535376777 
		937 -4.3631891015750739 950 -4.3631891015750739 970 -4.3631891015750739;
	setAttr -s 69 ".kit[37:68]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 69 ".kot[37:68]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 69 ".kix[68]"  1;
	setAttr -s 69 ".kiy[68]"  0;
	setAttr -s 69 ".kox[68]"  1;
	setAttr -s 69 ".koy[68]"  0;
createNode animCurveTL -n "animCurveTL1107";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 69 ".ktv[0:68]"  0 -0.39613925592663957 50 -0.39613925592663957 
		65 -0.39613925592663957 81 -0.39613925592663957 140 -0.39613925592663957 150 -0.39613925592663957 
		160 -0.19883424448437573 168 -0.0015294447272852282 178 -0.0015294447272852282 230 
		-0.0015294447272852282 242 0.29722234039306011 275 0.29722234039306011 290 -0.39613925592663957 
		300 -0.39613925592663957 350 -0.39613925592663957 360 -0.39613925592663957 370 -0.39613925592663957 
		380 -0.39613925592663957 400 -0.39613925592663957 411 -0.36210648935005885 420 -0.39613925592663957 
		428 -0.42191016422535632 441 -0.45927899207776424 450 -1.1448397981983895 464 -1.150574126616059 
		472 -0.4010603076148137 480 0.27189485688622589 492 -0.59450546673871263 504 -0.45743465503674163 
		510 -0.45743465503674163 620 -0.45743465503674163 626 -0.76068031523801749 630 0.2720809012330202 
		638 1.3937484828470099 670 1.2930169870261001 680 1.4538568896743 690 1.4538568896743 
		706 1.4538568896743 714 0.99144253156150253 720 0.65243078598784288 727 0.49628130066478904 
		731 0.65243078598784288 735 0.49628130066478904 740 0.65243078598784288 745 0.49628130066478904 
		749 0.65243078598784288 754 0.49628130066478904 760 0.64361783577345366 770 0.2411713548413531 
		790 0.2411713548413531 795 0.61371135385071207 800 0.66503327894282582 810 0.66503327894282582 
		821 0.66503327894282582 830 0.66503327894282582 837 0.66503327894282582 843 0.66503327894282582 
		850 0.66503327894282582 860 0.66503327894282582 875 0.51642656379893059 890 0.5075487707455788 
		898 0.024189038455126165 905 -0.11670763748245444 912 -0.11670763748245444 920 -0.11670763748245444 
		930 -0.56112276576995113 937 -0.39613925592663957 950 -0.39613925592663957 970 -0.39613925592663957;
	setAttr -s 69 ".kit[37:68]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 69 ".kot[37:68]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 69 ".kix[68]"  1;
	setAttr -s 69 ".kiy[68]"  0;
	setAttr -s 69 ".kox[68]"  1;
	setAttr -s 69 ".koy[68]"  0;
createNode animCurveTA -n "animCurveTA3245";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3246";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3247";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1108";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1109";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1110";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1663";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 74 ".ktv[0:73]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 172 1 178 1 230 1 242 1 252 1 264 1 275 1 290 1 300 1 350 1 360 1 374 1 383 1 391 
		1 400 1 411 1 420 1 428 1 441 1 445 1 450 1 464 1 480 1 492 1 504 1 510 1 620 1 626 
		1 630 1 638 1 655 1 670 1 680 1 690 1 706 1 714 1 720 1 727 1 731 1 735 1 740 1 745 
		1 749 1 754 1 760 1 770 1 790 1 795 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 
		1 875 1 890 1 898 1 905 1 912 1 920 1 930 1 937 1 950 1 970 1;
	setAttr -s 74 ".kit[42:73]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 74 ".kot[42:73]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 74 ".kix[73]"  1;
	setAttr -s 74 ".kiy[73]"  0;
	setAttr -s 74 ".kox[73]"  1;
	setAttr -s 74 ".koy[73]"  0;
createNode animCurveTU -n "animCurveTU1664";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 74 ".ktv[0:73]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 172 1 178 1 230 1 242 1 252 1 264 1 275 1 290 1 300 1 350 1 360 1 374 1 383 1 391 
		1 400 1 411 1 420 1 428 1 441 1 445 1 450 1 464 1 480 1 492 1 504 1 510 1 620 1 626 
		1 630 1 638 1 655 1 670 1 680 1 690 1 706 1 714 1 720 1 727 1 731 1 735 1 740 1 745 
		1 749 1 754 1 760 1 770 1 790 1 795 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 
		1 875 1 890 1 898 1 905 1 912 1 920 1 930 1 937 1 950 1 970 1;
	setAttr -s 74 ".kit[42:73]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 74 ".kot[42:73]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 74 ".kix[73]"  1;
	setAttr -s 74 ".kiy[73]"  0;
	setAttr -s 74 ".kox[73]"  1;
	setAttr -s 74 ".koy[73]"  0;
createNode animCurveTU -n "animCurveTU1665";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 74 ".ktv[0:73]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 172 0 178 0 230 0 242 0 252 0 264 0 275 0 290 0 300 0 350 0 360 0 374 0 383 0 391 
		0 400 0 411 0 420 0 428 0 441 0 445 0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 
		0 630 0 638 0 655 0 670 0 680 0 690 0 706 0 714 0 720 0 727 0 731 0 735 0 740 0 745 
		0 749 0 754 0 760 0 770 0 790 0 795 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 
		0 875 0 890 0 898 0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 74 ".kit[42:73]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 74 ".kot[42:73]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 74 ".kix[73]"  1;
	setAttr -s 74 ".kiy[73]"  0;
	setAttr -s 74 ".kox[73]"  1;
	setAttr -s 74 ".koy[73]"  0;
createNode animCurveTU -n "animCurveTU1666";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 74 ".ktv[0:73]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 172 0 178 0 230 0 242 0 252 0 264 0 275 0 290 0 300 0 350 0 360 0 374 0 383 0 391 
		0 400 0 411 0 420 0 428 0 441 0 445 0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 
		0 630 0 638 0 655 0 670 0 680 0 690 0 706 0 714 0 720 0 727 0 731 0 735 0 740 0 745 
		0 749 0 754 0 760 0 770 0 790 0 795 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 
		0 875 0 890 0 898 0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 74 ".kit[42:73]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 74 ".kot[42:73]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 74 ".kix[73]"  1;
	setAttr -s 74 ".kiy[73]"  0;
	setAttr -s 74 ".kox[73]"  1;
	setAttr -s 74 ".koy[73]"  0;
createNode animCurveTU -n "animCurveTU1667";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 74 ".ktv[0:73]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 172 0 178 0 230 0 242 0 252 0 264 0 275 0 290 0 300 0 350 0 360 0 374 0 383 0 391 
		0 400 0 411 0 420 0 428 0 441 0 445 0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 
		0 630 0 638 0 655 0 670 0 680 0 690 0 706 0 714 0 720 0 727 0 731 0 735 0 740 0 745 
		0 749 0 754 0 760 0 770 0 790 0 795 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 
		0 875 0 890 0 898 0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 74 ".kit[42:73]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 74 ".kot[42:73]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 74 ".kix[73]"  1;
	setAttr -s 74 ".kiy[73]"  0;
	setAttr -s 74 ".kox[73]"  1;
	setAttr -s 74 ".koy[73]"  0;
createNode animCurveTA -n "animCurveTA3248";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 85 ".ktv[0:84]"  0 88.534804986013214 50 88.534804986013214 
		65 76.365200036303321 81 76.365200036303321 140 76.365200036303321 150 72.497507631749571 
		160 28.374826349071185 168 9.7737904637939952 172 -7.6873313984659069 178 -7.6873313984659069 
		230 -7.6873313984659113 242 -33.607238708990224 247 -55.184723482138146 252 -41.222241152488074 
		258 -54.968289389078784 264 -46.964645443207807 269 -69.329253905073642 275 -53.954852580865506 
		283 9.3107381760744232 290 -71.323038692362189 300 -71.323038692362189 350 -71.323038692362189 
		360 -152.60933432503828 367 -189.2502113910883 374 -141.701423741323 379 -183.82106348695879 
		383 -128.81636500181162 387 -178.62206378583122 391 -116.35276903989087 395 -166.93989367144809 
		400 -106.91230903002293 411 -144.01497379208502 420 -121.72648734279478 428 -81.371074278772767 
		441 -26.484577286823935 445 21.897266258229429 450 33.288598747400016 464 59.968145856044771 
		472 179.60930330497447 480 307.58376888202719 492 410.7830091835213 499 400.16176146590453 
		504 353.05284775833292 510 353.05284775833292 620 353.05284775833292 626 360.11486635938746 
		630 354.8343754977347 638 395.76853598118532 655 395.76853598118532 670 371.11178729231676 
		680 320.38998445000811 690 314.68811365454013 706 314.68811365454013 714 294.63308781494072 
		720 300.16355989046849 727 290.98012727249369 731 300.16355989046849 735 290.98012727249369 
		740 300.16355989046849 745 290.98012727249369 749 300.16355989046849 754 290.98012727249369 
		760 351.48441646100781 770 346.89997743798551 790 338.0784168469155 795 302.40573329369801 
		800 286.33674475037503 810 286.33674475037503 821 296.55812692990787 830 286.33674475037503 
		837 296.55812692990787 843 286.33674475037503 850 296.55812692990787 860 286.33674475037503 
		875 286.33674475037503 890 318.04745940100906 894 318.06284416023192 898 336.45706982541014 
		905 360.3084219808033 912 334.07915046860501 920 297.9353686883598 930 391.3795836838122 
		937 448.53480498601323 950 448.53480498601323 970 448.53480498601323;
	setAttr -s 85 ".kit[22:84]"  3 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 9 10 10 10 10 10 10 10 10 10 10 10 
		3 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 85 ".kot[22:84]"  3 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 9 10 10 10 10 10 10 10 10 10 10 10 
		3 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 85 ".kix[84]"  1;
	setAttr -s 85 ".kiy[84]"  0;
	setAttr -s 85 ".kox[84]"  1;
	setAttr -s 85 ".koy[84]"  0;
createNode animCurveTA -n "animCurveTA3249";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 85 ".ktv[0:84]"  0 57.148763240415768 50 57.148763240415768 
		65 52.98474738956957 81 52.98474738956957 140 52.98474738956957 150 40.009683365235411 
		160 2.5296936551791087 168 -1.1184756658059718 172 24.171957197667822 178 24.171957197667822 
		230 24.171957197667819 242 -19.52563076053778 247 -21.407861284884692 252 -27.507515703648128 
		258 -14.62796360894486 264 -29.977122778872875 269 -12.199499113751662 275 -16.115149067472693 
		283 -13.270681028079675 290 69.704136629742834 300 69.704136629742834 350 69.70413662974282 
		360 202.31188136684017 367 154.5093173642002 374 208.68701101157072 379 155.01538296709268 
		383 212.58247711630318 387 164.41673011914287 391 216.00129636324462 395 160.29420340836953 
		400 219.8374709864614 411 151.44332048966098 420 132.60414152597713 428 212.8163626679783 
		441 261.74837152678907 445 280.3169331185436 450 300.9886046829763 464 303.0675480037691 
		472 306.09589486950063 480 312.02119029009577 492 403.85411920343273 499 381.90619759052601 
		504 383.27332684026334 510 383.27332684026334 620 383.27332684026334 626 382.60425261873291 
		630 344.51994336745332 638 407.31269108705897 655 407.31269108705897 670 435.39926262107696 
		680 345.68390678074161 690 352.86283836533715 706 352.86283836533715 714 354.59047700180633 
		720 313.72309345517056 727 358.84842576213663 731 313.72309345517056 735 358.84842576213663 
		740 313.72309345517056 745 358.84842576213663 749 313.72309345517056 754 358.84842576213663 
		760 333.31085251610887 770 347.55714126337517 790 356.51327443582699 795 363.58319182488941 
		800 351.79648477958892 810 351.79648477958892 821 379.97284761040527 830 351.79648477958892 
		837 379.97284761040527 843 351.79648477958892 850 379.97284761040527 860 351.79648477958892 
		875 351.79648477958892 890 365.06916418903046 894 354.8976071124174 898 369.8589788292046 
		905 411.16301350883367 912 389.23090678181984 920 371.37777850035366 930 434.95653871126439 
		937 417.14876324041569 950 417.14876324041569 970 417.14876324041575;
	setAttr -s 85 ".kit[22:84]"  1 10 10 10 10 10 10 10 
		2 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 9 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 85 ".kot[22:84]"  1 10 10 10 10 10 10 10 
		2 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 9 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 85 ".kix[22:84]"  0.14211377501487732 0.97273284196853638 
		0.99975627660751343 0.97526836395263672 0.85168391466140747 0.9758681058883667 0.9654732346534729 
		0.97598868608474731 0.15835165977478027 0.4011063277721405 0.46761766076087952 0.29658666253089905 
		0.4334615170955658 0.40123304724693298 1 1 0.95965355634689331 0.36393600702285767 
		0.46082401275634766 1 1 1 1 1 0.68004852533340454 1 1 0.61244428157806396 0.41999533772468567 
		1 0.99929046630859375 1 0.98561108112335205 1 1 1 1 1 1 0.73140484094619751 0.93801224231719971 
		0.92688339948654175 0.94802278280258179 0.97083032131195068 1 1 1 1 1 1 1 1 1 0.9963681697845459 
		0.95420986413955688 0.34979373216629028 0.8097999095916748 0.58433860540390015 0.60093110799789429 
		0.57856953144073486 1 1 1;
	setAttr -s 85 ".kiy[22:84]"  0.98985040187835693 0.23192822933197021 
		0.022075917571783066 0.22102397680282593 0.52405589818954468 0.21836084127426147 
		-0.26050209999084473 0.21782131493091583 0.98738276958465576 -0.91603147983551025 
		0.88393086194992065 0.955005943775177 0.90117204189300537 0.91597598791122437 0 0 
		0.28118520975112915 0.93142396211624146 0.88749158382415771 0 0 0 0 0 0.73316711187362671 
		0 0 -0.79051375389099121 -0.90752619504928589 0 0.037664521485567093 0 0.1690286248922348 
		0 0 0 0 0 0 0.68194347620010376 -0.34660187363624573 0.37534946203231812 0.31820249557495117 
		-0.2397674024105072 0 0 0 0 0 0 0 0 0 0.085149846971035004 0.29913803935050964 0.93682676553726196 
		0.58670622110366821 -0.81150996685028076 0.79930084943771362 0.81563305854797363 
		0 0 0;
	setAttr -s 85 ".kox[22:84]"  0.96996933221817017 0.97273284196853638 
		0.99975627660751343 0.97526836395263672 0.85168391466140747 0.9758681058883667 0.9654732346534729 
		0.97598868608474731 0.29362753033638 0.4011063277721405 0.46761766076087952 0.29658666253089905 
		0.4334615170955658 0.40123304724693298 1 1 0.95965355634689331 0.36393600702285767 
		0.46082401275634766 1 1 1 1 1 0.68004852533340454 1 1 0.61244428157806396 0.41999533772468567 
		1 0.99929046630859375 1 0.98561108112335205 1 1 1 1 1 1 0.73140484094619751 0.93801224231719971 
		0.92688339948654175 0.94802278280258179 0.97083032131195068 1 1 1 1 1 1 1 1 1 0.9963681697845459 
		0.95420986413955688 0.34979373216629028 0.8097999095916748 0.58433860540390015 0.60093110799789429 
		0.57856953144073486 1 1 1;
	setAttr -s 85 ".koy[22:84]"  0.24322733283042908 0.23192822933197021 
		0.022075917571783066 0.22102397680282593 0.52405589818954468 0.21836084127426147 
		-0.26050209999084473 0.21782131493091583 -0.95591992139816284 -0.91603147983551025 
		0.88393086194992065 0.955005943775177 0.90117204189300537 0.91597598791122437 0 0 
		0.28118520975112915 0.93142396211624146 0.88749158382415771 0 0 0 0 0 0.73316711187362671 
		0 0 -0.79051375389099121 -0.90752619504928589 0 0.037664521485567093 0 0.1690286248922348 
		0 0 0 0 0 0 0.68194347620010376 -0.34660187363624573 0.37534946203231812 0.31820249557495117 
		-0.2397674024105072 0 0 0 0 0 0 0 0 0 0.085149846971035004 0.29913803935050964 0.93682676553726196 
		0.58670622110366821 -0.81150996685028076 0.79930084943771362 0.81563305854797363 
		0 0 0;
createNode animCurveTA -n "animCurveTA3250";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 85 ".ktv[0:84]"  0 -82.181665956692072 50 -82.181665956692072 
		65 -68.648618187645326 81 -68.648618187645326 140 -68.648618187645326 150 -60.498217745434602 
		160 -20.164853373432916 168 -10.357641294099054 172 5.5762877532259028 178 5.5762877532259028 
		230 5.5762877532258974 242 -45.478228154350425 247 -25.631260925257063 252 -60.815943808591776 
		258 -22.202152217021489 264 -72.318269118291624 269 -34.064868842773777 275 -57.799527479088596 
		283 -3.2369124252656172 290 72.359802653036283 300 72.359802653036283 350 72.359802653036269 
		360 87.495989207818909 367 59.474161157010812 374 91.582750109408991 379 59.815082524824057 
		383 92.964716659121123 387 74.175435119822595 391 93.429439011871494 395 62.311283595620061 
		400 101.39498832283394 411 164.77006977099848 420 138.73846579627124 428 191.03409212358309 
		441 290.99363980346385 445 400.2859942949197 450 466.58512755357754 464 554.20371956840995 
		472 592.32882032220141 480 615.04215336062168 492 691.38547558286041 499 702.34032472029185 
		504 703.22536969290638 510 703.22536969290638 620 703.22536969290638 626 701.16130029476949 
		630 618.40072330329019 638 540.63606959044216 655 540.63606959044216 670 544.45393461260755 
		680 623.55475428521265 690 623.95976913879258 706 623.95976913879258 714 682.96073509091286 
		720 618.1966711726036 727 637.16139982147149 731 618.1966711726036 735 637.16139982147149 
		740 618.1966711726036 745 637.16139982147149 749 618.1966711726036 754 637.16139982147149 
		760 663.19915627809507 770 719.06870538751491 790 706.0772923769207 795 665.08238968040359 
		800 612.65467731252568 810 612.65467731252568 821 611.28355420613605 830 612.65467731252568 
		837 611.28355420613605 843 612.65467731252568 850 611.28355420613605 860 612.65467731252568 
		875 612.65467731252568 890 663.66435878987238 894 665.70586442099636 898 731.98656264189106 
		905 741.07900099624555 912 741.94590714005528 920 749.40444520399421 930 690.67091354566321 
		937 637.8183340433078 950 637.8183340433078 970 637.81833404330791;
	setAttr -s 85 ".kit[52:84]"  9 10 10 10 10 10 10 10 
		10 10 10 10 3 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 1;
	setAttr -s 85 ".kot[52:84]"  9 10 10 10 10 10 10 10 
		10 10 10 10 3 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 1;
	setAttr -s 85 ".kix[84]"  1;
	setAttr -s 85 ".kiy[84]"  0;
	setAttr -s 85 ".kox[84]"  1;
	setAttr -s 85 ".koy[84]"  0;
createNode animCurveTL -n "animCurveTL1111";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 85 ".ktv[0:84]"  0 0.87423592510602477 50 0.88656561072043738 
		65 0.88396200715084339 81 0.88396200715084339 140 0.88396200715084339 150 0.90543334752471649 
		160 0.29229601792459037 168 -0.37713938347526366 172 -0.4437246613655903 178 -0.37854193885045273 
		230 -0.42339140438776068 242 0.14754859552563238 247 0.1731203122598971 252 0.2483815776131848 
		258 0.1927851117160258 264 0.28257553967645044 269 0.19269008424942385 275 0.31747699230395998 
		283 0.32523013057247907 290 0.42627449996599998 300 0.43286340693333036 350 0.43286340693333036 
		360 0.65096817393360906 367 0.77321349667171047 374 0.59259320609614596 379 0.67334859907201139 
		383 0.53031190701564257 387 0.68374966904066825 391 0.4762759384429982 395 0.58123727545758097 
		400 0.44055272490828967 411 0.71941380674814326 420 1.1680876168137466 428 1.3395558607515872 
		441 1.9983690937560903 445 2.1191536723241651 450 2.2876511934865551 464 2.0251113898476096 
		472 2.2301005039328627 480 2.0538452393322224 492 0.86895180246645642 499 1.0911728723414473 
		504 1.0866709513824224 510 1.0866709513824224 620 1.0866709513824224 626 1.0961615550713448 
		630 1.4223041310333535 638 1.340852034291288 655 1.5270868384647351 670 1.7813219516327412 
		680 1.7004559718724512 690 1.6873778922053693 706 1.6873778922053693 714 1.4614538229587386 
		720 2.0991575145362975 727 1.8572667338995283 731 2.0991575145362975 735 1.8572667338995283 
		740 2.0991575145362975 745 1.8572667338995283 749 2.0991575145362975 754 1.8572667338995283 
		760 1.5613142044461799 770 1.2916271413776905 790 1.0237854145454355 795 1.4283952379472189 
		800 1.9161138404646438 810 1.8559523893440062 821 1.7693687084338947 830 1.7667594731310485 
		837 1.7693687084338947 843 1.7667594731310485 850 1.7693687084338947 860 1.7667594731310485 
		875 1.6550070879629533 890 1.5246471749539139 894 1.4585621887552298 898 1.0046127936612932 
		905 0.76927502464763498 912 0.91839988829813712 920 0.86954139556117083 930 0.86040734027126642 
		937 0.87962575547757238 950 0.86322971843722618 970 0.87423592510602477;
	setAttr -s 85 ".kit[7:84]"  3 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 3 10 
		10 10 3 10 10 1 10 10 10 10 10 10 10 10 10 9 10 
		10 10 10 9 10 2 10 10 10 10 10 10 10 10 10 2 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 1;
	setAttr -s 85 ".kot[7:84]"  3 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 3 10 
		10 10 3 10 10 1 10 10 10 10 10 10 10 10 10 9 10 
		10 10 10 9 10 2 10 10 10 10 10 10 10 10 10 2 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 1;
	setAttr -s 85 ".kix[37:84]"  0.98209309577941895 0.99855178594589233 
		0.43985733389854431 0.54961413145065308 1 1 1 1 1 0.85304808616638184 0.99218738079071045 
		0.92429518699645996 0.97903710603713989 1 1 0.96236062049865723 0.74982637166976929 
		0.29925402998924255 1 1 1 1 1 1 0.56329011917114258 0.68602341413497925 0.88081377744674683 
		0.92791187763214111 0.34993487596511841 0.76001793146133423 0.9787251353263855 1 
		1 1 1 1 1 0.9719194769859314 0.95510965585708618 0.45629245042800903 0.46963763236999512 
		0.9833599328994751 1 1 1 1 1 1;
	setAttr -s 85 ".kiy[37:84]"  -0.18839624524116516 0.053797900676727295 
		-0.8980676531791687 -0.83541858196258545 0 0 0 0 0 0.52183234691619873 0.12475680559873581 
		0.38167864084243774 0.20368207991123199 0 0 -0.27177578210830688 0.66163474321365356 
		0.95417344570159912 0 0 0 0 0 0 -0.82625919580459595 -0.72757947444915771 -0.4734627902507782 
		-0.3727995753288269 0.93677407503128052 0.64990216493606567 -0.20517569780349731 
		0 0 0 0 0 0 -0.23531365394592285 -0.29625231027603149 -0.88982993364334106 -0.88285928964614868 
		-0.18166762590408325 0 0 0 0 0 0;
	setAttr -s 85 ".kox[37:84]"  0.98209315538406372 0.99855178594589233 
		0.43985733389854431 0.54961413145065308 1 1 1 1 1 0.85304808616638184 0.99218738079071045 
		0.92429518699645996 0.97903710603713989 1 1 0.96236062049865723 0.74982637166976929 
		0.69426161050796509 1 1 1 1 1 1 0.56329011917114258 0.68602341413497925 0.88081377744674683 
		0.38087090849876404 0.34993487596511841 0.76001793146133423 0.9787251353263855 1 
		1 1 1 1 1 0.9719194769859314 0.95510965585708618 0.45629245042800903 0.46963763236999512 
		0.9833599328994751 1 1 1 1 1 1;
	setAttr -s 85 ".koy[37:84]"  -0.18839636445045471 0.053797900676727295 
		-0.8980676531791687 -0.83541858196258545 0 0 0 0 0 0.52183234691619873 0.12475680559873581 
		0.38167864084243774 0.20368207991123199 0 0 -0.27177578210830688 0.66163474321365356 
		-0.7197226881980896 0 0 0 0 0 0 -0.82625919580459595 -0.72757947444915771 -0.4734627902507782 
		0.92462819814682007 0.93677407503128052 0.64990216493606567 -0.20517569780349731 
		0 0 0 0 0 0 -0.23531365394592285 -0.29625231027603149 -0.88982993364334106 -0.88285928964614868 
		-0.18166762590408325 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL1112";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 85 ".ktv[0:84]"  0 -3.1428054520501574 50 -3.1104726464562633 
		65 -3.4157822720080584 81 -3.4157822720080584 140 -3.3698139502825732 150 -3.2835695412171639 
		160 -3.3264993148799942 168 -3.5704291680956333 172 -3.5782418647948444 178 -3.5782418647948444 
		230 -3.5646811865268782 242 -3.8983445044982505 247 -3.9777610725523429 252 -3.9846253264575768 
		258 -4.000234553799527 264 -3.9815985721255336 269 -4.0588994788499724 275 -3.9789422210937757 
		283 -3.5034906292396504 290 -3.4115051654944315 300 -3.4115051654944315 350 -3.4115051654944315 
		360 -3.4804425731682831 367 -3.4622043886094289 374 -3.4755037938561091 379 -3.4750551867403607 
		383 -3.4720224470586274 387 -3.4701588518433479 391 -3.4678694489880835 395 -3.4647816384434513 
		400 -3.4629136497326036 411 -3.3168837467194887 420 -3.2670432171802775 428 -2.6892229822114184 
		441 -2.4169155431810636 445 -2.3344349498117931 450 -2.1281568869634535 464 -1.7238337689584342 
		472 -0.45783339475295892 480 0.31882532169754763 492 -0.30329757940992164 499 -0.38902637898727782 
		504 -0.44127361318922953 510 -0.3855293662094289 620 -0.42982449649746995 626 -0.29889182753253213 
		630 -0.6346479702247001 638 -0.98836657761406155 655 -0.92741570835514864 670 -0.98710092063224275 
		680 -0.87063737839235689 690 -0.91212999777110149 706 -0.91212999777110149 714 -0.62605919229386675 
		720 -0.43339809746559199 727 -1.0964709244675612 731 -0.43339809746559199 735 -1.0964709244675612 
		740 -0.43339809746559199 745 -1.0964709244675612 749 -0.43339809746559199 754 -1.0964709244675612 
		760 -0.49679599044290557 770 -0.58016316450178262 790 -0.79866172843233807 795 -1.0092287500147255 
		800 -0.34157887046529023 810 -0.38065259513073102 821 -0.67354207293692192 830 -0.46134089767620456 
		837 -0.67354207293692192 843 -0.46134089767620456 850 -0.67354207293692192 860 -0.46134089767620456 
		875 -1.0284859107334161 890 -0.88582175903100357 894 -0.89054420529807377 898 -1.2759591534769583 
		905 -1.5941230612929986 912 -2.5594159337864046 920 -3.5102121402003319 930 -3.3562972030432427 
		937 -3.3920288325914982 950 -3.0212739407936002 970 -3.1428054520501574;
	setAttr -s 85 ".kit[2:84]"  9 9 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 2 2 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 3 10 10 10 10 9 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 85 ".kot[2:84]"  9 9 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 2 2 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 3 10 10 10 10 9 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 85 ".kix[84]"  1;
	setAttr -s 85 ".kiy[84]"  0;
	setAttr -s 85 ".kox[84]"  1;
	setAttr -s 85 ".koy[84]"  0;
createNode animCurveTL -n "animCurveTL1113";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 85 ".ktv[0:84]"  0 -0.13730793645266492 50 -0.22371807466553151 
		65 -0.31442405278434671 81 -0.31442405278434671 140 -0.26918952471334312 150 -0.26421205067122 
		160 0.14265058961655669 168 0.36723613110800479 172 0.35978730090755384 178 0.35978730090755384 
		230 0.36827477746089499 242 0.18844022300262542 247 0.18608287761684422 252 0.1831448443554734 
		258 0.18074619653559262 264 0.1731357731684508 269 0.17091477062438665 275 0.16435157608542039 
		283 0.49130823468977186 290 -0.51984585432950337 300 -0.45890054750651899 350 -0.45890054750651899 
		360 0.92013517894382879 367 0.86987028900676178 374 0.90399259636803297 379 0.88484887618200925 
		383 0.88784384727271104 387 0.8789423771004311 391 0.8625971068741527 395 0.89013154878394418 
		400 0.81331997105076992 411 0.0021612548009716237 420 -0.076022563778573637 428 -0.45331311661744689 
		441 -0.40099935250215613 445 -0.51800918022476472 450 -0.61244918703756024 464 -0.64367172720494303 
		472 -0.45540024267655915 480 0.010748362780657938 492 0.017855592507177942 499 -0.017281155275235938 
		504 -0.28599090776524616 510 -0.22314629960698673 620 -0.28550389667740578 626 0.026111898273326606 
		630 0.39777137342641944 638 0.54552119889056927 655 0.48277780910369672 670 0.48796540353900175 
		680 0.59048435608905736 690 0.5531773261224795 706 0.5531773261224795 714 0.30777723429966841 
		720 0.22652798759456649 727 0.001371590006655321 731 0.22652798759456649 735 0.001371590006655321 
		740 0.22652798759456649 745 0.001371590006655321 749 0.22652798759456649 754 0.001371590006655321 
		760 0.49676553265555545 770 0.42056779704264557 790 0.48123242474040384 795 0.43548262237929181 
		800 0.2518537174407105 810 0.12419212050565731 821 0.083632830784961865 830 0.20607767574234304 
		837 0.083632830784961865 843 0.20607767574234304 850 0.083632830784961865 860 0.20607767574234304 
		875 0.057470960598447807 890 -0.008306191192381962 894 0.097202442662390365 898 0.17357736433335258 
		905 0.052279686972617867 912 0.11379471081593476 920 0.038194991677471979 930 -0.062609254499164477 
		937 -0.22743739710595301 950 -0.13287245534675785 970 -0.13730793645266492;
	setAttr -s 85 ".kit[7:84]"  9 10 9 10 10 10 10 10 
		10 10 10 10 3 10 10 3 10 10 10 10 10 10 10 1 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 3 10 3 9 
		10 10 10 9 10 10 10 10 10 10 10 10 10 10 10 3 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 1;
	setAttr -s 85 ".kot[7:84]"  9 10 9 10 10 10 10 10 
		10 10 10 10 3 10 10 3 10 10 10 10 10 10 10 1 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 3 10 3 9 
		10 10 10 9 10 10 10 10 10 10 10 10 10 10 10 3 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 1;
	setAttr -s 85 ".kix[30:84]"  0.991474449634552 0.59980422258377075 0.77943021059036255 
		0.90702039003372192 0.99354571104049683 0.81737202405929565 1 1 0.63174599409103394 
		1 1 1 0.87196642160415649 1 0.99792873859405518 1 0.61014574766159058 1 0.99854737520217896 
		1 1 1 0.95603173971176147 0.81924647092819214 0.81650370359420776 1 1 1 1 1 1 0.80499082803726196 
		0.78621160984039307 0.99987936019897461 1 1 0.84891998767852783 1 1 1 1 1 1 0.99950754642486572 
		0.9777827262878418 0.99803799390792847 0.82613283395767212 0.99257820844650269 0.99189406633377075 
		0.99960356950759888 0.95939439535140991 0.90545463562011719 0.9944918155670166 1 
		0.99726837873458862;
	setAttr -s 85 ".kiy[30:84]"  -0.13030135631561279 -0.80014675855636597 
		-0.62648916244506836 -0.4210866391658783 -0.11343266069889069 -0.57611018419265747 
		0 0 0.77517545223236084 0 0 0 -0.48956570029258728 0.0001259511336684227 0.064329802989959717 
		0 0.79228919744491577 0 -0.053880132734775543 0 0 0 -0.29326313734054565 -0.57344144582748413 
		-0.57734018564224243 0 0 0 0 0 0 0.59328728914260864 0.61795729398727417 -0.015531234443187714 
		0 0 -0.52852147817611694 0 0 0 0 0 0 -0.031378831714391708 -0.20962083339691162 0.062610849738121033 
		0.56347543001174927 -0.12160727381706238 -0.12706713378429413 -0.028158221393823624 
		-0.28206810355186462 -0.42444300651550293 -0.10481436550617218 0 -0.073863513767719269;
	setAttr -s 85 ".kox[30:84]"  0.99147450923919678 0.59980422258377075 
		0.77943021059036255 0.90702039003372192 0.99354571104049683 0.81737202405929565 1 
		1 0.63174599409103394 1 1 1 0.87196642160415649 1 0.99792873859405518 1 0.61014574766159058 
		1 0.99854737520217896 1 1 1 0.95603173971176147 0.81924647092819214 0.81650370359420776 
		1 1 1 1 1 1 0.80499082803726196 0.78621160984039307 0.99987936019897461 1 1 0.84891998767852783 
		1 1 1 1 1 1 0.99950754642486572 0.9777827262878418 0.99803799390792847 0.82613283395767212 
		0.99257820844650269 0.99189406633377075 0.99960356950759888 0.95939439535140991 0.90545463562011719 
		0.9944918155670166 1 0.99726837873458862;
	setAttr -s 85 ".koy[30:84]"  -0.13030137121677399 -0.80014675855636597 
		-0.62648916244506836 -0.4210866391658783 -0.11343266069889069 -0.57611018419265747 
		0 0 0.77517545223236084 0 0 0 -0.48956570029258728 0.0001259511336684227 0.064329802989959717 
		0 0.79228919744491577 0 -0.053880132734775543 0 0 0 -0.29326313734054565 -0.57344144582748413 
		-0.57734018564224243 0 0 0 0 0 0 0.59328728914260864 0.61795729398727417 -0.015531234443187714 
		0 0 -0.52852147817611694 0 0 0 0 0 0 -0.031378831714391708 -0.20962083339691162 0.062610849738121033 
		0.56347543001174927 -0.12160727381706238 -0.12706713378429413 -0.028158221393823624 
		-0.28206810355186462 -0.42444300651550293 -0.10481436550617218 0 -0.073863513767719269;
createNode animCurveTU -n "animCurveTU1668";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 172 0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 
		0 441 0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 
		0 706 0 720 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[36:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[36:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1669";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 172 0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 
		0 441 0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 
		0 706 0 720 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[36:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[36:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1670";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 58 ".ktv[0:57]"  0 -0.89999999999999991 50 -0.89999999999999991 
		65 -0.89999999999999991 81 -0.89999999999999991 140 -0.89999999999999991 150 -0.89999999999999991 
		160 -0.89999999999999991 168 -1.2999999999999998 172 -1.3 178 0.50000000000000022 
		230 -0.29999999999999982 242 -0.89999999999999991 275 -0.89999999999999991 290 -0.89999999999999991 
		300 -0.89999999999999991 350 -0.89999999999999991 360 -0.89999999999999991 370 -0.89999999999999991 
		380 -0.89999999999999991 400 -0.89999999999999991 420 -0.89999999999999991 428 -0.89999999999999991 
		441 -0.89999999999999991 450 -0.89999999999999991 464 -0.89999999999999991 480 -0.89999999999999991 
		492 -0.89999999999999991 504 -0.89999999999999991 510 -0.89999999999999991 620 -0.89999999999999991 
		626 -0.89999999999999991 630 -0.89999999999999991 638 -0.89999999999999991 670 -0.89999999999999991 
		680 -0.89999999999999991 690 -0.89999999999999991 706 -0.89999999999999991 720 -1.2000000000000011 
		760 -1.2000000000000011 770 -0.60000000000000098 790 -0.60000000000000098 800 10 
		810 10 821 10 830 10 837 10 843 10 850 10 860 10 875 -0.60000000000000098 890 -0.60000000000000098 
		905 -0.40000000000000036 912 -0.40000000000000036 920 -0.40000000000000036 930 -0.65199899292015506 
		937 -0.89999999999999991 950 -0.89999999999999991 970 -0.89999999999999991;
	setAttr -s 58 ".kit[36:57]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kot[36:57]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kix[57]"  1;
	setAttr -s 58 ".kiy[57]"  0;
	setAttr -s 58 ".kox[57]"  1;
	setAttr -s 58 ".koy[57]"  0;
createNode animCurveTU -n "animCurveTU1671";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 58 ".ktv[0:57]"  0 -0.59999999999999987 50 -0.59999999999999987 
		65 -0.59999999999999987 81 -0.59999999999999987 140 -0.59999999999999987 150 -0.59999999999999987 
		160 -0.59999999999999987 168 -0.99999999999999989 172 -1 178 0.80000000000000027 
		230 -1.4 242 -0.59999999999999987 275 -0.59999999999999987 290 -0.59999999999999987 
		300 -0.59999999999999987 350 -0.59999999999999987 360 -0.59999999999999987 370 -0.59999999999999987 
		380 -0.59999999999999987 400 -0.59999999999999987 420 -0.59999999999999987 428 -0.59999999999999987 
		441 -0.59999999999999987 450 -0.59999999999999987 464 -0.59999999999999987 480 -0.59999999999999987 
		492 -0.59999999999999987 504 -0.59999999999999987 510 -0.59999999999999987 620 -0.59999999999999987 
		626 -0.59999999999999987 630 -0.59999999999999987 638 -0.59999999999999987 670 -0.59999999999999987 
		680 -0.59999999999999987 690 -0.59999999999999987 706 -0.59999999999999987 720 -1.2000000000000011 
		760 -1.2000000000000011 770 -0.60000000000000098 790 -1.2000000000000011 800 10 810 
		10 821 10 830 10 837 10 843 10 850 10 860 10 875 10 890 10 905 -0.40000000000000036 
		912 -0.40000000000000036 920 -0.40000000000000036 930 -0.40000000000000036 937 -0.40000000000000036 
		950 -0.40000000000000036 970 -0.59999999999999987;
	setAttr -s 58 ".kit[36:57]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kot[36:57]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kix[57]"  1;
	setAttr -s 58 ".kiy[57]"  0;
	setAttr -s 58 ".kox[57]"  1;
	setAttr -s 58 ".koy[57]"  0;
createNode animCurveTU -n "animCurveTU1672";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 58 ".ktv[0:57]"  0 -0.59999999999999987 50 -0.59999999999999987 
		65 -0.59999999999999987 81 -0.59999999999999987 140 -0.59999999999999987 150 -0.59999999999999987 
		160 -0.59999999999999987 168 -0.99999999999999989 172 -1 178 0.80000000000000027 
		230 -1.4 242 -0.59999999999999987 275 -0.59999999999999987 290 -0.59999999999999987 
		300 -0.59999999999999987 350 -0.59999999999999987 360 -0.59999999999999987 370 -0.59999999999999987 
		380 -0.59999999999999987 400 -0.59999999999999987 420 -0.59999999999999987 428 -0.59999999999999987 
		441 -0.59999999999999987 450 -0.59999999999999987 464 -0.59999999999999987 480 -0.59999999999999987 
		492 -0.59999999999999987 504 -0.59999999999999987 510 -0.59999999999999987 620 -0.59999999999999987 
		626 -0.59999999999999987 630 -0.59999999999999987 638 -0.59999999999999987 670 -0.59999999999999987 
		680 -0.59999999999999987 690 -0.59999999999999987 706 -0.59999999999999987 720 -1.2000000000000011 
		760 -1.2000000000000011 770 -0.60000000000000098 790 -1.2000000000000011 800 10 810 
		10 821 10 830 10 837 10 843 10 850 10 860 10 875 10 890 10 905 -0.40000000000000036 
		912 -0.40000000000000036 920 -0.40000000000000036 930 -0.40000000000000036 937 -0.40000000000000036 
		950 -0.40000000000000036 970 -0.59999999999999987;
	setAttr -s 58 ".kit[36:57]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kot[36:57]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kix[57]"  1;
	setAttr -s 58 ".kiy[57]"  0;
	setAttr -s 58 ".kox[57]"  1;
	setAttr -s 58 ".koy[57]"  0;
createNode animCurveTU -n "animCurveTU1673";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 58 ".ktv[0:57]"  0 -0.89999999999999991 50 -0.89999999999999991 
		65 -0.89999999999999991 81 -0.89999999999999991 140 -0.89999999999999991 150 -0.89999999999999991 
		160 -0.89999999999999991 168 -1.2999999999999998 172 -1.3 178 0.50000000000000022 
		230 -0.29999999999999982 242 -0.89999999999999991 275 -0.89999999999999991 290 -0.89999999999999991 
		300 -0.89999999999999991 350 -0.89999999999999991 360 -0.89999999999999991 370 -0.89999999999999991 
		380 -0.89999999999999991 400 -0.89999999999999991 420 -0.89999999999999991 428 -0.89999999999999991 
		441 -0.89999999999999991 450 -0.89999999999999991 464 -0.89999999999999991 480 -0.89999999999999991 
		492 -0.89999999999999991 504 -0.89999999999999991 510 -0.89999999999999991 620 -0.89999999999999991 
		626 -0.89999999999999991 630 -0.89999999999999991 638 -0.89999999999999991 670 -0.89999999999999991 
		680 -0.89999999999999991 690 -0.89999999999999991 706 -0.89999999999999991 720 -1.2000000000000011 
		760 -1.2000000000000011 770 -0.60000000000000098 790 -0.60000000000000098 800 10 
		810 10 821 10 830 10 837 10 843 10 850 10 860 10 875 -0.60000000000000098 890 -0.60000000000000098 
		905 -0.40000000000000036 912 -0.40000000000000036 920 -0.40000000000000036 930 -0.65199899292015506 
		937 -0.89999999999999991 950 -0.89999999999999991 970 -0.89999999999999991;
	setAttr -s 58 ".kit[36:57]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kot[36:57]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kix[57]"  1;
	setAttr -s 58 ".kiy[57]"  0;
	setAttr -s 58 ".kox[57]"  1;
	setAttr -s 58 ".koy[57]"  0;
createNode animCurveTU -n "animCurveTU1674";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 58 ".ktv[0:57]"  0 -0.59999999999999987 50 -0.59999999999999987 
		65 -0.59999999999999987 81 -0.59999999999999987 140 -0.59999999999999987 150 -0.59999999999999987 
		160 -0.59999999999999987 168 -0.99999999999999989 172 -1 178 0.80000000000000027 
		230 -1.4 242 -0.59999999999999987 275 -0.59999999999999987 290 -0.59999999999999987 
		300 -0.59999999999999987 350 -0.59999999999999987 360 -0.59999999999999987 370 -0.59999999999999987 
		380 -0.59999999999999987 400 -0.59999999999999987 420 -0.59999999999999987 428 -0.59999999999999987 
		441 -0.59999999999999987 450 -0.59999999999999987 464 -0.59999999999999987 480 -0.59999999999999987 
		492 -0.59999999999999987 504 -0.59999999999999987 510 -0.59999999999999987 620 -0.59999999999999987 
		626 -0.59999999999999987 630 -0.59999999999999987 638 -0.59999999999999987 670 -0.59999999999999987 
		680 -0.59999999999999987 690 -0.59999999999999987 706 -0.59999999999999987 720 -1.2000000000000011 
		760 -1.2000000000000011 770 -0.60000000000000098 790 -1.2000000000000011 800 10 810 
		10 821 10 830 10 837 10 843 10 850 10 860 10 875 10 890 10 905 -0.40000000000000036 
		912 -0.40000000000000036 920 -0.40000000000000036 930 -0.40000000000000036 937 -0.40000000000000036 
		950 -0.40000000000000036 970 -0.59999999999999987;
	setAttr -s 58 ".kit[36:57]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kot[36:57]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kix[57]"  1;
	setAttr -s 58 ".kiy[57]"  0;
	setAttr -s 58 ".kox[57]"  1;
	setAttr -s 58 ".koy[57]"  0;
createNode animCurveTU -n "animCurveTU1675";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1676";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1677";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA3251";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3252";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3253";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1114";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1115";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1116";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1678";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
	setAttr ".kot[1]"  4;
createNode animCurveTU -n "animCurveTU1679";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 10;
createNode animCurveTU -n "animCurveTU1680";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3254";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3255";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3256";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1117";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1118";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1119";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1681";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1682";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1683";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA3257";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3258";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3259";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1120";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1121";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1122";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1684";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
	setAttr ".kot[1]"  4;
createNode animCurveTU -n "animCurveTU1685";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3260";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3261";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3262";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1123";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1124";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1125";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1686";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1687";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1688";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA3263";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3264";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3265";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1126";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1127";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1128";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1689";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
	setAttr ".kot[1]"  4;
createNode animCurveTU -n "animCurveTU1690";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3266";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3267";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3268";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1129";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1130";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1131";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3269";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3270";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3271";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3272";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		-32.208930434956571 178 -32.208930434956571 230 -32.208930434956571 242 -14.247122293979771 
		275 -14.247122293979771 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3273";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3274";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3275";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3276";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 59 ".ktv[0:58]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 457 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 
		0 706 0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 
		0 890 0 901 0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 59 ".kit[36:58]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 59 ".kot[36:58]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 59 ".kix[58]"  1;
	setAttr -s 59 ".kiy[58]"  0;
	setAttr -s 59 ".kox[58]"  1;
	setAttr -s 59 ".koy[58]"  0;
createNode animCurveTA -n "animCurveTA3277";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 59 ".ktv[0:58]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 457 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 
		0 706 0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 
		0 890 0 901 0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 59 ".kit[36:58]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 59 ".kot[36:58]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 59 ".kix[58]"  1;
	setAttr -s 59 ".kiy[58]"  0;
	setAttr -s 59 ".kox[58]"  1;
	setAttr -s 59 ".koy[58]"  0;
createNode animCurveTA -n "animCurveTA3278";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 59 ".ktv[0:58]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 457 0 464 -12.816765409884134 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 
		0 670 0 680 0 690 0 706 0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 
		0 850 0 860 0 875 0 890 0 901 0 905 -14.962522555194107 912 -8.2282677055886708 920 
		0 930 0 937 0 950 0 970 0;
	setAttr -s 59 ".kit[36:58]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 59 ".kot[36:58]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 59 ".kix[58]"  1;
	setAttr -s 59 ".kiy[58]"  0;
	setAttr -s 59 ".kox[58]"  1;
	setAttr -s 59 ".koy[58]"  0;
createNode animCurveTA -n "animCurveTA3279";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3280";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3281";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3282";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3283";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3284";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1691";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 370 1 380 1 400 1 420 1 428 1 441 
		1 450 1 464 1 480 1 492 1 504 1 510 1 620 1 626 1 630 1 638 1 670 1 680 1 690 1 706 
		1 720 1 750 1 760 1 790 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 1 890 
		1 905 1 912 1 920 1 930 1 937 1 950 1 970 1;
	setAttr -s 57 ".kit[56]"  1;
	setAttr -s 57 ".kot[0:56]"  5 5 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 9 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 5 5 5 5 5;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
createNode animCurveTU -n "animCurveTU1692";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 370 1 380 1 400 1 420 1 428 1 441 
		1 450 1 464 1 480 1 492 1 504 1 510 1 620 1 626 1 630 1 638 1 670 1 680 1 690 1 706 
		1 720 1 750 1 760 1 790 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 1 890 
		1 905 1 912 1 920 1 930 1 937 1 950 1 970 1;
	setAttr -s 57 ".kit[56]"  1;
	setAttr -s 57 ".kot[0:56]"  5 5 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 9 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 5 5 5 5 5;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
createNode animCurveTU -n "animCurveTU1693";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 10 50 10 65 10 81 10 140 10 150 10 160 
		10 168 10 178 10 230 10 242 10 275 10 290 10 300 10 350 10 360 10 370 10 380 10 400 
		10 420 10 428 10 441 10 450 10 464 10 480 10 492 10 504 10 510 10 620 10 626 10 630 
		10 638 10 670 10 680 10 690 10 706 10 720 10 750 10 760 10 790 10 800 10 810 10 821 
		10 830 10 837 10 843 10 850 10 860 10 875 10 890 10 905 10 912 10 920 10 930 10 937 
		10 950 10 970 10;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1132";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1133";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1134";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1694";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 58 ".ktv[0:57]"  0 10 50 10 65 10 81 10 140 10 150 10 160 
		10 168 10 178 10 230 10 242 10 275 10 290 10 300 10 350 10 360 10 370 10 380 10 400 
		10 420 10 428 10 441 10 450 10 464 10 480 10 492 10 504 10 510 10 620 10 626 10 630 
		10 638 10 670 10 680 10 690 10 706 10 720 10 750 10 760 10 790 10 795 10 800 10 810 
		10 821 10 830 10 837 10 843 10 850 10 860 10 875 10 890 10 905 10 912 10 920 10 930 
		10 937 10 950 10 970 10;
	setAttr -s 58 ".kit[35:57]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kot[35:57]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kix[57]"  1;
	setAttr -s 58 ".kiy[57]"  0;
	setAttr -s 58 ".kox[57]"  1;
	setAttr -s 58 ".koy[57]"  0;
createNode animCurveTL -n "animCurveTL1135";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 58 ".ktv[0:57]"  0 0.32982634761357144 50 0.32982634761357144 
		65 0.32982634761357144 81 0.32982634761357144 140 0.32982634761357144 150 0.32982634761357144 
		160 0.65309871932885388 168 1.4019165205691348 178 1.4019165205691348 230 1.4019165205691348 
		242 1.4019165205691348 275 1.4019165205691348 290 0.32982634761357144 300 0.32982634761357144 
		350 0.32982634761357144 360 0.32982634761357144 370 0.32982634761357144 380 0.32982634761357144 
		400 0.32982634761357144 420 0.32982634761357144 428 0.10679438908705338 441 -0.097157581761012288 
		450 0.039084882156473703 464 0.15236101748692107 480 0.14726017277144535 492 -0.03660274813352072 
		504 0.0012199016021987399 510 0.0077142685952632239 620 0.0077142685952632239 626 
		0.0077142685952632239 630 0.0922517294134578 638 0.17679039955953285 670 0.17679039955953285 
		680 0.17679039955953285 690 0.17679039955953285 706 0.17679039955953285 720 0.17679039955953285 
		750 0.17679039955953285 760 0.17679039955953285 790 0.17679039955953285 795 0.076004082104860912 
		800 0.092199335502865687 810 0.10551056586107213 821 0.10551056586107213 830 0.10551056586107213 
		837 0.10551056586107213 843 0.10551056586107213 850 0.10551056586107213 860 0.10784294538399221 
		875 0.17679039955953285 890 0.17679039955953285 905 0.17679039955953285 912 0.11004921511747168 
		920 0.048247882469775731 930 0.2039228980788341 937 0.32982634761357144 950 0.32982634761357144 
		970 0.32982634761357144;
	setAttr -s 58 ".kit[35:57]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kot[35:57]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kix[57]"  1;
	setAttr -s 58 ".kiy[57]"  0;
	setAttr -s 58 ".kox[57]"  1;
	setAttr -s 58 ".koy[57]"  0;
createNode animCurveTL -n "animCurveTL1136";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 58 ".ktv[0:57]"  0 0.81796417501297725 50 0.81796417501297725 
		65 0.81796417501297725 81 0.81796417501297725 140 0.81796417501297725 150 0.81796417501297725 
		160 0.71425909343524285 168 0.70592514290551878 178 0.70592514290551878 230 0.70592514290551878 
		242 0.70592514290551878 275 0.70592514290551878 290 0.81796417501297725 300 0.81796417501297725 
		350 0.81796417501297725 360 0.81796417501297725 370 0.81796417501297725 380 0.81796417501297725 
		400 0.81796417501297725 420 0.81796417501297725 428 0.88685251937037446 441 0.98191637695112677 
		450 1.0872750987352435 464 1.1384914917615805 480 1.0202138060580579 492 1.1931087919743988 
		504 1.2038836480625452 510 1.2010738192545443 620 1.2010738192545443 626 1.2010738192545443 
		630 1.1735745745364683 638 1.1460749364353522 670 1.1460749364353522 680 1.1460749364353522 
		690 1.1460749364353522 706 1.1460749364353522 720 1.1460749364353522 750 1.1460749364353522 
		760 1.1460749364353522 790 1.1460749364353522 795 1.1891601971889629 800 1.3043237089945561 
		810 1.3139841781853254 821 1.3139841781853254 830 1.3139841781853254 837 1.3139841781853254 
		843 1.3139841781853254 850 1.3139841781853254 860 1.2791913863529785 875 1.1460749364353522 
		890 1.1460749364353522 905 1.1460749364353522 912 1.2623512623649988 920 1.3620869574919523 
		930 1.0600275196175157 937 0.81796417501297725 950 0.81796417501297725 970 0.81796417501297725;
	setAttr -s 58 ".kit[35:57]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kot[35:57]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kix[57]"  1;
	setAttr -s 58 ".kiy[57]"  0;
	setAttr -s 58 ".kox[57]"  1;
	setAttr -s 58 ".koy[57]"  0;
createNode animCurveTL -n "animCurveTL1137";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 58 ".ktv[0:57]"  0 0.24529330917097836 50 0.24529330917097836 
		65 0.24529330917097836 81 0.24529330917097836 140 0.24529330917097836 150 0.24529330917097836 
		160 0.50279040399991615 168 0.49331486456743168 178 0.49331486456743168 230 0.49331486456743168 
		242 0.49331486456743168 275 0.49331486456743168 290 0.24529330917097836 300 0.24529330917097836 
		350 0.24529330917097836 360 0.24529330917097836 370 0.24529330917097836 380 0.24529330917097836 
		400 0.24529330917097836 420 0.24529330917097836 428 0.061548220361892392 441 -0.088832401654279067 
		450 -0.045126148070855965 464 -0.10125596229059487 480 0.12339327303210039 492 0.017286006510319883 
		504 0.19552313786450393 510 0.17294957827078247 620 0.17294957827078247 626 0.17294957827078247 
		630 0.19525134142493006 638 0.21755342361094474 670 0.21755342361094474 680 0.21755342361094474 
		690 0.21755342361094474 706 0.21755342361094474 720 0.21755342361094474 750 0.21755342361094474 
		760 0.21755342361094474 790 0.21755342361094474 795 0.18557162650940226 800 0.48357216107120982 
		810 0.5101485500290498 821 0.5101485500290498 830 0.5101485500290498 837 0.5101485500290498 
		843 0.5101485500290498 850 0.5101485500290498 860 0.41887122479118671 875 0.21755342361094474 
		890 0.21755342361094474 905 0.21755342361094474 912 0.039815085366270958 920 -0.17377565074516946 
		930 0.050299056386592544 937 0.24529330917097836 950 0.24529330917097836 970 0.24529330917097836;
	setAttr -s 58 ".kit[35:57]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kot[35:57]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kix[57]"  1;
	setAttr -s 58 ".kiy[57]"  0;
	setAttr -s 58 ".kox[57]"  1;
	setAttr -s 58 ".koy[57]"  0;
createNode animCurveTA -n "animCurveTA3285";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3286";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3287";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1138";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1139";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1140";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1695";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 65 ".ktv[0:64]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 370 1 380 1 400 1 420 1 428 1 441 
		1 443 1 450 1 464 1 472 1 480 1 486 1 492 1 504 1 510 1 620 1 626 1 630 1 638 1 670 
		1 680 1 690 1 706 1 714 1 717 1 720 1 750 1 760 1 790 1 797 1 800 1 810 1 821 1 830 
		1 837 1 843 1 850 1 860 1 868 1 875 1 890 1 905 1 912 1 920 1 925 1 930 1 937 1 950 
		1 970 1;
	setAttr -s 65 ".kit[38:64]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 1;
	setAttr -s 65 ".kot[38:64]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 1;
	setAttr -s 65 ".kix[64]"  1;
	setAttr -s 65 ".kiy[64]"  0;
	setAttr -s 65 ".kox[64]"  1;
	setAttr -s 65 ".koy[64]"  0;
createNode animCurveTU -n "animCurveTU1696";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 65 ".ktv[0:64]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 370 1 380 1 400 1 420 1 428 1 441 
		1 443 1 450 1 464 1 472 1 480 1 486 1 492 1 504 1 510 1 620 1 626 1 630 1 638 1 670 
		1 680 1 690 1 706 1 714 1 717 1 720 1 750 1 760 1 790 1 797 1 800 1 810 1 821 1 830 
		1 837 1 843 1 850 1 860 1 868 1 875 1 890 1 905 1 912 1 920 1 925 1 930 1 937 1 950 
		1 970 1;
	setAttr -s 65 ".kit[38:64]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 1;
	setAttr -s 65 ".kot[38:64]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 1;
	setAttr -s 65 ".kix[64]"  1;
	setAttr -s 65 ".kiy[64]"  0;
	setAttr -s 65 ".kox[64]"  1;
	setAttr -s 65 ".koy[64]"  0;
createNode animCurveTU -n "animCurveTU1697";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 65 ".ktv[0:64]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 443 0 450 0 464 0 472 0 480 0 486 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 
		0 680 0 690 0 706 0 714 0 717 0 720 0 750 0 760 0 790 0 797 0 800 0 810 0 821 0 830 
		0 837 0 843 0 850 0 860 0 868 0 875 0 890 0 905 0 912 0 920 0 925 0 930 0 937 0 950 
		0 970 0;
	setAttr -s 65 ".kit[38:64]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 1;
	setAttr -s 65 ".kot[38:64]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 1;
	setAttr -s 65 ".kix[64]"  1;
	setAttr -s 65 ".kiy[64]"  0;
	setAttr -s 65 ".kox[64]"  1;
	setAttr -s 65 ".koy[64]"  0;
createNode animCurveTU -n "animCurveTU1698";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 65 ".ktv[0:64]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 443 0 450 0 464 0 472 0 480 0 486 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 
		0 680 0 690 0 706 0 714 0 717 0 720 0 750 0 760 0 790 0 797 0 800 0 810 0 821 0 830 
		0 837 0 843 0 850 0 860 0 868 0 875 0 890 0 905 0 912 0 920 0 925 0 930 0 937 0 950 
		0 970 0;
	setAttr -s 65 ".kit[38:64]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 1;
	setAttr -s 65 ".kot[38:64]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 1;
	setAttr -s 65 ".kix[64]"  1;
	setAttr -s 65 ".kiy[64]"  0;
	setAttr -s 65 ".kox[64]"  1;
	setAttr -s 65 ".koy[64]"  0;
createNode animCurveTU -n "animCurveTU1699";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 65 ".ktv[0:64]"  0 25 50 25 65 25 81 25 140 25 150 25 160 
		25 168 25 178 25 230 25 242 25 275 25 290 25 300 25 350 25 360 25 370 25 380 25 400 
		25 420 25 428 25 441 25 443 25 450 25 464 25 472 25 480 25 486 25 492 25 504 25 510 
		25 620 25 626 25 630 25 638 25 670 25 680 25 690 25 706 25 714 25 717 25 720 25 750 
		25 760 25 790 25 797 25 800 25 810 25 821 25 830 25 837 25 843 25 850 25 860 25 868 
		25 875 25 890 25 905 25 912 25 920 25 925 25 930 25 937 25 950 25 970 25;
	setAttr -s 65 ".kit[38:64]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 1;
	setAttr -s 65 ".kot[38:64]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 1;
	setAttr -s 65 ".kix[64]"  1;
	setAttr -s 65 ".kiy[64]"  0;
	setAttr -s 65 ".kox[64]"  1;
	setAttr -s 65 ".koy[64]"  0;
createNode animCurveTU -n "animCurveTU1700";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 65 ".ktv[0:64]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 443 0 450 0 464 0 472 0 480 0 486 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 
		0 680 0 690 0 706 0 714 0 717 0 720 0 750 0 760 0 790 0 797 0 800 0 810 0 821 0 830 
		0 837 0 843 0 850 0 860 0 868 0 875 0 890 0 905 0 912 0 920 0 925 0 930 0 937 0 950 
		0 970 0;
	setAttr -s 65 ".kit[38:64]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 1;
	setAttr -s 65 ".kot[38:64]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 1;
	setAttr -s 65 ".kix[64]"  1;
	setAttr -s 65 ".kiy[64]"  0;
	setAttr -s 65 ".kox[64]"  1;
	setAttr -s 65 ".koy[64]"  0;
createNode animCurveTU -n "animCurveTU1701";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 65 ".ktv[0:64]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 443 0 450 0 464 0 472 0 480 0 486 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 
		0 680 0 690 0 706 0 714 0 717 0 720 0 750 0 760 0 790 0 797 0 800 0 810 0 821 0 830 
		0 837 0 843 0 850 0 860 0 868 0 875 0 890 0 905 0 912 0 920 0 925 0 930 0 937 0 950 
		0 970 0;
	setAttr -s 65 ".kit[38:64]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 1;
	setAttr -s 65 ".kot[38:64]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 1;
	setAttr -s 65 ".kix[64]"  1;
	setAttr -s 65 ".kiy[64]"  0;
	setAttr -s 65 ".kox[64]"  1;
	setAttr -s 65 ".koy[64]"  0;
createNode animCurveTU -n "animCurveTU1702";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 65 ".ktv[0:64]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 443 0 450 0 464 0 472 0 480 0 486 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 
		0 680 0 690 0 706 0 714 0 717 0 720 0 750 0 760 0 790 0 797 0 800 0 810 0 821 0 830 
		0 837 0 843 0 850 0 860 0 868 0 875 0 890 0 905 0 912 0 920 0 925 0 930 0 937 0 950 
		0 970 0;
	setAttr -s 65 ".kit[38:64]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 1;
	setAttr -s 65 ".kot[38:64]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 1;
	setAttr -s 65 ".kix[64]"  1;
	setAttr -s 65 ".kiy[64]"  0;
	setAttr -s 65 ".kox[64]"  1;
	setAttr -s 65 ".koy[64]"  0;
createNode animCurveTA -n "animCurveTA3288";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 65 ".ktv[0:64]"  0 64.362913341968763 50 64.362913341968763 
		65 64.362913341968763 81 64.362913341968763 140 64.362913341968763 150 64.362913341968763 
		160 64.362913341968763 168 64.362913341968763 178 64.362913341968763 230 64.362913341968763 
		242 64.362913341968763 275 64.362913341968763 290 64.362913341968763 300 64.362913341968763 
		350 64.362913341968763 360 64.362913341968763 370 64.362913341968763 380 64.362913341968763 
		400 64.362913341968763 420 64.362913341968763 428 153.04612901987906 441 186.25755537456507 
		443 186.25755537456502 450 186.25755537456502 464 186.25755537456502 472 157.81893135703802 
		480 129.92683715131807 486 74.346210755193297 492 74.346210755193297 504 74.346210755193297 
		510 74.346210755193297 620 74.346210755193297 626 74.346210755193297 630 74.346210755193297 
		638 74.346210755193297 670 74.346210755193297 680 74.346210755193297 690 74.346210755193297 
		706 74.346210755193297 714 60.394514793746168 717 37.532796196672649 720 37.532796196672649 
		750 37.532796196672649 760 37.532796196672649 790 37.532796196672649 797 37.532796196672649 
		800 37.532796196672649 810 37.532796196672649 821 37.532796196672649 830 37.532796196672649 
		837 37.532796196672649 843 37.532796196672649 850 37.532796196672649 860 43.930924159197886 
		868 37.532796196672649 875 37.532796196672649 890 37.532796196672649 905 1.2600590135642347 
		912 10.643183898088568 920 31.18618457203868 925 64.362913341968763 930 64.362913341968763 
		937 64.362913341968763 950 64.362913341968763 970 64.362913341968763;
	setAttr -s 65 ".kit[37:64]"  3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 65 ".kot[37:64]"  3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 65 ".kix[64]"  1;
	setAttr -s 65 ".kiy[64]"  0;
	setAttr -s 65 ".kox[64]"  1;
	setAttr -s 65 ".koy[64]"  0;
createNode animCurveTA -n "animCurveTA3289";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 65 ".ktv[0:64]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 -13.577548026932524 
		441 -1.0414914719092834 443 -1.0414914719092834 450 -1.0414914719092834 464 -1.0414914719092834 
		472 -16.590820658382881 480 -17.378095004929463 486 6.4170008652704125 492 6.4170008652704125 
		504 6.4170008652704125 510 6.4170008652704125 620 6.4170008652704125 626 6.4170008652704125 
		630 6.4170008652704125 638 6.4170008652704125 670 6.4170008652704125 680 6.4170008652704125 
		690 6.4170008652704125 706 6.4170008652704125 714 6.2707350827724069 717 -1.8258568521898206 
		720 -1.8258568521898206 750 -1.8258568521898206 760 -1.8258568521898206 790 -1.8258568521898206 
		797 -1.8258568521898206 800 -1.8258568521898206 810 -1.8258568521898206 821 -1.8258568521898206 
		830 -1.8258568521898206 837 -1.8258568521898206 843 -1.8258568521898206 850 -1.8258568521898206 
		860 17.414813760525 868 -1.8258568521898206 875 -1.8258568521898206 890 -1.8258568521898206 
		905 1.1388297058160806 912 0.62627111544627767 920 0 925 0 930 0 937 0 950 0 970 
		0;
	setAttr -s 65 ".kit[38:64]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 1;
	setAttr -s 65 ".kot[38:64]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 1;
	setAttr -s 65 ".kix[64]"  1;
	setAttr -s 65 ".kiy[64]"  0;
	setAttr -s 65 ".kox[64]"  1;
	setAttr -s 65 ".koy[64]"  0;
createNode animCurveTA -n "animCurveTA3290";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 65 ".ktv[0:64]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 47.490864883446115 
		441 -27.644236835586796 443 -3.771741179839613 450 -3.771741179839613 464 -3.771741179839613 
		472 40.318842640464339 480 39.122511665996001 486 -4.0075641020227151 492 -10.883342219977765 
		504 -10.883342219977765 510 -10.883342219977765 620 -10.883342219977765 626 -10.883342219977765 
		630 -10.883342219977765 638 -10.883342219977765 670 -10.883342219977765 680 -10.883342219977765 
		690 -10.883342219977765 706 -10.883342219977765 714 11.191895067231894 717 -3.6834209090520038 
		720 -3.6834209090520038 750 -3.6834209090520038 760 -3.6834209090520038 790 -3.6834209090520038 
		797 -3.6834209090520038 800 -3.6834209090520038 810 -3.6834209090520038 821 -3.6834209090520038 
		830 -3.6834209090520038 837 -3.6834209090520038 843 -3.6834209090520038 850 -3.6834209090520038 
		860 8.0383374626413016 868 -3.6834209090520038 875 -3.6834209090520038 890 -3.6834209090520038 
		905 -3.0461999131924857 912 35.009498882057457 920 -10.66647464156526 925 0 930 0 
		937 0 950 0 970 0;
	setAttr -s 65 ".kit[37:64]"  3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 65 ".kot[37:64]"  3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 65 ".kix[64]"  1;
	setAttr -s 65 ".kiy[64]"  0;
	setAttr -s 65 ".kox[64]"  1;
	setAttr -s 65 ".koy[64]"  0;
createNode animCurveTL -n "animCurveTL1141";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 65 ".ktv[0:64]"  0 1.2768283457414795 50 1.2768283457414795 
		65 1.2768283457414795 81 1.2768283457414795 140 1.2768283457414795 150 1.2768283457414795 
		160 1.2768283457414795 168 1.2768283457414795 178 1.2768283457414795 230 1.2768283457414795 
		242 1.2768283457414795 275 1.2768283457414795 290 1.2768283457414795 300 1.2768283457414795 
		350 1.2768283457414795 360 1.2768283457414795 370 1.2768283457414795 380 1.2768283457414795 
		400 1.2768283457414795 420 1.2768283457414795 428 1.4009795590198633 441 1.2454501698252416 
		443 1.2454501698252416 450 1.2454501698252416 464 1.2454501698252416 472 1.461376237431564 
		480 1.4390945939367521 486 1.239591479484899 492 1.239591479484899 504 1.239591479484899 
		510 1.239591479484899 620 1.239591479484899 626 1.239591479484899 630 1.239591479484899 
		638 1.239591479484899 670 1.239591479484899 680 1.239591479484899 690 1.239591479484899 
		706 1.239591479484899 714 1.3387196962231132 717 1.239591479484899 720 1.239591479484899 
		750 1.239591479484899 760 1.239591479484899 790 1.239591479484899 797 1.239591479484899 
		800 1.239591479484899 810 1.239591479484899 821 1.239591479484899 830 1.239591479484899 
		837 1.239591479484899 843 1.239591479484899 850 1.239591479484899 860 1.345431704776739 
		868 1.239591479484899 875 1.239591479484899 890 1.239591479484899 905 1.239591479484899 
		912 1.4533626499228882 920 1.2768283457414795 925 1.2768283457414795 930 1.2768283457414795 
		937 1.2768283457414795 950 1.2768283457414795 970 1.2768283457414795;
	setAttr -s 65 ".kit[37:64]"  3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 65 ".kot[37:64]"  3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 65 ".kix[64]"  1;
	setAttr -s 65 ".kiy[64]"  0;
	setAttr -s 65 ".kox[64]"  1;
	setAttr -s 65 ".koy[64]"  0;
createNode animCurveTL -n "animCurveTL1142";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 65 ".ktv[0:64]"  0 -3.9472376747979365 50 -3.9472376747979365 
		65 -3.9472376747979365 81 -3.9472376747979365 140 -3.9472376747979365 150 -3.9472376747979365 
		160 -3.9472376747979365 168 -3.9472376747979365 178 -3.9472376747979365 230 -3.9472376747979365 
		242 -3.9472376747979365 275 -3.9472376747979365 290 -3.9472376747979365 300 -3.9472376747979365 
		350 -3.9472376747979365 360 -3.9472376747979365 370 -3.9472376747979365 380 -3.9472376747979365 
		400 -3.9472376747979365 420 -3.9472376747979365 428 -3.8008877897549764 441 -2.3814433686616763 
		443 -2.320447149768798 450 -2.320447149768798 464 -2.320447149768798 472 -1.7011951826749954 
		480 -1.0306226566212904 486 -1.1328838571241655 492 -1.1328838571241655 504 -1.1328838571241655 
		510 -1.1328838571241655 620 -1.1328838571241655 626 -1.1328838571241655 630 -1.1328838571241655 
		638 -1.1328838571241655 670 -1.1328838571241655 680 -1.1328838571241655 690 -1.1328838571241655 
		706 -1.1328838571241655 714 -1.0341267916566768 717 -1.1328838571241655 720 -1.1328838571241655 
		750 -1.1328838571241655 760 -1.1328838571241655 790 -1.1328838571241655 797 -1.1328838571241655 
		800 -0.61710461512155712 810 -0.61710461512155712 821 -0.61710461512155712 830 -0.61710461512155712 
		837 -0.61710461512155712 843 -0.61710461512155712 850 -0.61710461512155712 860 -0.61127234977462219 
		868 -1.1328838571241655 875 -1.1328838571241655 890 -1.1328838571241655 905 -1.0650794278645077 
		912 -2.3749711599963312 920 -3.8212736828938794 925 -3.9472376747979365 930 -3.9472376747979365 
		937 -3.9472376747979365 950 -3.9472376747979365 970 -3.9472376747979365;
	setAttr -s 65 ".kit[37:64]"  3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 3 3 10 10 10 10 
		10 10 1;
	setAttr -s 65 ".kot[37:64]"  3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 3 3 10 10 10 10 
		10 10 1;
	setAttr -s 65 ".kix[64]"  1;
	setAttr -s 65 ".kiy[64]"  0;
	setAttr -s 65 ".kox[64]"  1;
	setAttr -s 65 ".koy[64]"  0;
createNode animCurveTL -n "animCurveTL1143";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 65 ".ktv[0:64]"  0 0.76735808688697926 50 0.76735808688697926 
		65 0.76735808688697926 81 0.76735808688697926 140 0.76735808688697926 150 0.76735808688697926 
		160 0.76735808688697926 168 0.76735808688697926 178 0.76735808688697926 230 0.76735808688697926 
		242 0.76735808688697926 275 0.76735808688697926 290 0.76735808688697926 300 0.76735808688697926 
		350 0.76735808688697926 360 0.76735808688697926 370 0.76735808688697926 380 0.76735808688697926 
		400 0.76735808688697926 420 0.76735808688697926 428 1.2560054337246211 441 1.0155786564812685 
		443 1.0155786564812685 450 1.0155786564812685 464 1.0155786564812685 472 1.0182101461214303 
		480 1.015620453121014 486 1.0031693043566214 492 1.0031693043566214 504 1.0031693043566214 
		510 1.0031693043566214 620 1.0031693043566214 626 1.0031693043566214 630 1.0031693043566214 
		638 1.0031693043566214 670 1.0031693043566214 680 1.0031693043566214 690 1.0031693043566214 
		706 1.0031693043566214 714 0.95983467739604689 717 0.60201009194861688 720 0.60201009194861688 
		750 0.60201009194861688 760 0.60201009194861688 790 0.60201009194861688 797 0.60201009194861688 
		800 0.85565274967204974 810 0.85565274967204974 821 0.85565274967204974 830 0.85565274967204974 
		837 0.85565274967204974 843 0.85565274967204974 850 0.85565274967204974 860 0.8569912425926568 
		868 0.60201009194861688 875 0.60201009194861688 890 0.60201009194861688 905 0.78386029848943983 
		912 0.68967340202234906 920 0.81730181992553963 925 0.76735808688697926 930 0.76735808688697926 
		937 0.76735808688697926 950 0.76735808688697926 970 0.76735808688697926;
	setAttr -s 65 ".kit[37:64]"  3 3 1 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 65 ".kot[37:64]"  3 3 1 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 65 ".kix[39:64]"  0.98201334476470947 1 1 1 1 1 1 1 1 1 1 
		1 1 1 1 1 1 1 0.99293065071105957 0.99777078628540039 1 1 1 1 1 1;
	setAttr -s 65 ".kiy[39:64]"  -0.18881146609783173 0 0 0 0 0 0 0 0 0 
		0 0 0 0 0 0 0 0 0.11869575828313828 0.066733941435813904 0 0 0 0 0 0;
	setAttr -s 65 ".kox[39:64]"  0.98201334476470947 1 1 1 1 1 1 1 1 1 1 
		1 1 1 1 1 1 1 0.99293065071105957 0.99777078628540039 1 1 1 1 1 1;
	setAttr -s 65 ".koy[39:64]"  -0.18881165981292725 0 0 0 0 0 0 0 0 0 
		0 0 0 0 0 0 0 0 0.11869575828313828 0.066733941435813904 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1703";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[56]"  1;
	setAttr -s 57 ".kot[0:56]"  5 5 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 9 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 5 5 5 5 5;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
createNode animCurveTU -n "animCurveTU1704";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 370 1 380 1 400 1 420 1 428 1 441 
		1 450 1 464 1 480 1 492 1 504 1 510 1 620 1 626 1 630 1 638 1 670 1 680 1 690 1 706 
		1 720 1 750 1 760 1 790 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 1 890 
		1 905 1 912 1 920 1 930 1 937 1 950 1 970 1;
	setAttr -s 57 ".kit[56]"  1;
	setAttr -s 57 ".kot[0:56]"  5 5 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 9 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 5 5 5 5 5;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
createNode animCurveTU -n "animCurveTU1705";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 10 50 10 65 10 81 10 140 10 150 10 160 
		10 168 10 178 10 230 10 242 10 275 10 290 10 300 10 350 10 360 10 370 10 380 10 400 
		10 420 10 428 10 441 10 450 10 464 10 480 10 492 10 504 10 510 10 620 10 626 10 630 
		10 638 10 670 10 680 10 690 10 706 10 720 10 750 10 760 10 790 10 800 10 810 10 821 
		10 830 10 837 10 843 10 850 10 860 10 875 10 890 10 905 10 912 10 920 10 930 10 937 
		10 950 10 970 10;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTL -n "animCurveTL1144";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1145";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1146";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1706";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 68 ".ktv[0:67]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 472 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 
		0 706 0 714 0 720 0 727 0 731 0 735 0 740 0 745 0 749 0 754 0 760 0 770 0 790 0 795 
		0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 0 898 0 905 0 912 0 920 
		0 930 0 937 0 950 0 970 0;
	setAttr -s 68 ".kit[36:67]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 68 ".kot[36:67]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 68 ".kix[67]"  1;
	setAttr -s 68 ".kiy[67]"  0;
	setAttr -s 68 ".kox[67]"  1;
	setAttr -s 68 ".koy[67]"  0;
createNode animCurveTL -n "animCurveTL1147";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 69 ".ktv[0:68]"  0 1.0806409153797385 50 1.0806409153797385 
		65 1.0124628671008518 81 1.0124628671008518 140 1.0124628671008518 150 1.0124628671008518 
		160 0.3100198204424961 168 -0.39242247257672513 178 -0.39242247257672513 230 -0.39242247257672513 
		242 -0.31019308572991866 275 -0.31019308572991866 290 1.0124628671008518 300 1.0124628671008518 
		350 1.0124628671008518 360 1.0124628671008518 370 1.0124628671008518 380 1.0124628671008518 
		400 1.0124628671008518 420 1.0688243933512198 428 0.90243161656038717 441 1.1885991242604326 
		450 1.9885245754383638 464 1.8241874864566427 472 1.1326870274840775 480 1.0181085010750164 
		492 1.0217151679435692 504 1.1881712663452322 510 1.1881712663452322 620 1.1881712663452322 
		626 1.0028500372377653 630 0.84960008382960872 638 0.65823175025381842 670 0.92554812555185517 
		680 0.92554812555182897 690 0.92554812555182897 706 0.92554812555182897 714 0.97202154912343008 
		720 1.0121556401849743 727 1.0506748783447026 731 1.0121556401849743 735 1.0506748783447026 
		740 1.0121556401849743 745 1.0506748783447026 749 1.0121556401849743 754 1.0506748783447026 
		760 0.91287662646474632 770 0.94002247278576467 790 0.95154197893114834 795 0.7470752243524732 
		800 0.90501483096723978 810 0.90501483096723978 821 0.90501483096723978 830 0.90501483096723978 
		837 0.90501483096723978 843 0.90501483096723978 850 0.90501483096723978 860 0.90501483096723978 
		875 0.79326244579914451 890 0.81830465125146368 894 0.86346566900156996 898 0.81251674233908155 
		905 0.86082825066087354 912 0.86082825066087354 920 0.86082825066087354 930 0.8327678877461967 
		937 1.0806409153797385 950 1.0806409153797385 970 1.0806409153797385;
	setAttr -s 69 ".kit[36:68]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 1;
	setAttr -s 69 ".kot[36:68]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 1;
	setAttr -s 69 ".kix[68]"  1;
	setAttr -s 69 ".kiy[68]"  0;
	setAttr -s 69 ".kox[68]"  1;
	setAttr -s 69 ".koy[68]"  0;
createNode animCurveTL -n "animCurveTL1148";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 69 ".ktv[0:68]"  0 -4.9802978173191903 50 -4.9802978173191903 
		65 -5.1780745602812814 81 -5.1780745602812814 140 -5.1780745602812814 150 -5.1780745602812814 
		160 -5.2996564457159776 168 -5.4212382007075473 178 -5.4212382007075473 230 -5.4212382007075473 
		242 -5.1041547726934873 275 -5.1041547726934873 290 -5.1780745602812814 300 -5.1780745602812814 
		350 -5.1780745602812814 360 -5.1780745602812814 370 -5.1780745602812814 380 -5.1780745602812814 
		400 -5.1780745602812814 420 -5.2448056417786484 428 -4.9428297313271932 441 -3.4897271509588506 
		450 -2.8454047373853402 464 -2.3382075989020836 472 -2.0456127885949362 480 -1.824937292356926 
		492 -2.017267533063583 504 -2.6057966667242671 510 -2.6057966667242671 620 -2.6057966667242671 
		626 -2.1272259462646712 630 -2.3172148528680117 638 -3.040270197044304 670 -2.8941265977133028 
		680 -2.8400563665601375 690 -2.8400563665601375 706 -2.8400563665601375 714 -2.8647312891586814 
		720 -2.7644316352732403 727 -2.6845609160028525 731 -2.7644316352732403 735 -2.6845609160028525 
		740 -2.7644316352732403 745 -2.6845609160028525 749 -2.7644316352732403 754 -2.6845609160028525 
		760 -2.2985801247925193 770 -2.1849411513095203 790 -2.3578858129966696 795 -2.8350157662834525 
		800 -2.0648358078756321 810 -2.0648358078756321 821 -2.0648358078756321 830 -2.0648358078756321 
		837 -2.0648358078756321 843 -2.0648358078756321 850 -2.0648358078756321 860 -2.0648358078756321 
		875 -2.6319808209328452 890 -2.5989131458720238 894 -2.3672781875533535 898 -1.9751726173794997 
		905 -2.9081645081561271 912 -2.9081645081561271 920 -2.9081645081561271 930 -4.5676544709327276 
		937 -4.9802978173191903 950 -4.9802978173191903 970 -4.9802978173191903;
	setAttr -s 69 ".kit[36:68]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 1;
	setAttr -s 69 ".kot[36:68]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 1;
	setAttr -s 69 ".kix[68]"  1;
	setAttr -s 69 ".kiy[68]"  0;
	setAttr -s 69 ".kox[68]"  1;
	setAttr -s 69 ".koy[68]"  0;
createNode animCurveTL -n "animCurveTL1149";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 69 ".ktv[0:68]"  0 1.0047115956882351 50 1.0047115956882351 
		65 1.0106658847601775 81 1.0106658847601775 140 1.0106658847601775 150 1.0106658847601775 
		160 1.1688446876254173 168 1.3270233207833237 178 1.3270233207833237 230 1.3270233207833237 
		242 1.0613370057167433 275 1.0613370057167433 290 1.0106658847601775 300 1.0106658847601775 
		350 1.0106658847601775 360 1.0106658847601775 370 1.0106658847601775 380 1.0106658847601775 
		400 1.0106658847601775 420 1.0291870336177107 428 2.0288676445257119 441 2.3563206428691652 
		450 2.6962984626802844 464 2.690564134262615 472 2.5559776738183722 480 2.0626695233745012 
		492 0.9677637084496451 504 0.70128702319548686 510 0.70128702319548686 620 0.70128702319548686 
		626 0.78567195333860673 630 1.6471315998250686 638 2.411860260850903 670 2.4695337570578788 
		680 1.5071273992780712 690 1.5071273992780712 706 1.5071273992780712 714 1.2205934632439523 
		720 1.2266102879454959 727 1.3037083468724422 731 1.2266102879454959 735 1.3037083468724422 
		740 1.2266102879454959 745 1.3037083468724422 749 1.2266102879454959 754 1.3037083468724422 
		760 1.2055359902002138 770 0.78888752147902497 790 0.71701838409324004 795 1.5393957134222955 
		800 1.600744175992612 810 1.600744175992612 821 1.600744175992612 830 1.600744175992612 
		837 1.600744175992612 843 1.600744175992612 850 1.600744175992612 860 1.600744175992612 
		875 1.4521374608487168 890 1.2936796595734106 894 0.96377605149259127 898 0.66790451601324918 
		905 0.98026231027677913 912 0.98026231027677913 920 0.98026231027677913 930 0.58092488786114438 
		937 1.0047115956882351 950 1.0047115956882351 970 1.0047115956882351;
	setAttr -s 69 ".kit[36:68]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 1;
	setAttr -s 69 ".kot[36:68]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 1;
	setAttr -s 69 ".kix[68]"  1;
	setAttr -s 69 ".kiy[68]"  0;
	setAttr -s 69 ".kox[68]"  1;
	setAttr -s 69 ".koy[68]"  0;
createNode animCurveTA -n "animCurveTA3291";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3292";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3293";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1150";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1151";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1152";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1707";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 71 ".ktv[0:70]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 172 1 178 1 230 1 242 1 252 1 258 1 264 1 269 1 275 1 290 1 300 1 350 1 400 1 420 
		1 428 1 441 1 445 1 450 1 464 1 472 1 480 1 492 1 504 1 510 1 620 1 626 1 630 1 638 
		1 655 1 670 1 680 1 690 1 706 1 714 1 720 1 727 1 731 1 735 1 740 1 745 1 749 1 754 
		1 760 1 770 1 790 1 795 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 1 890 
		1 905 1 912 1 920 1 930 1 937 1 950 1 970 1;
	setAttr -s 71 ".kit[19:70]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 9 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 1;
	setAttr -s 71 ".kot[19:70]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 9 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 1;
	setAttr -s 71 ".kix[70]"  1;
	setAttr -s 71 ".kiy[70]"  0;
	setAttr -s 71 ".kox[70]"  1;
	setAttr -s 71 ".koy[70]"  0;
createNode animCurveTU -n "animCurveTU1708";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 71 ".ktv[0:70]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 172 1 178 1 230 1 242 1 252 1 258 1 264 1 269 1 275 1 290 1 300 1 350 1 400 1 420 
		1 428 1 441 1 445 1 450 1 464 1 472 1 480 1 492 1 504 1 510 1 620 1 626 1 630 1 638 
		1 655 1 670 1 680 1 690 1 706 1 714 1 720 1 727 1 731 1 735 1 740 1 745 1 749 1 754 
		1 760 1 770 1 790 1 795 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 1 890 
		1 905 1 912 1 920 1 930 1 937 1 950 1 970 1;
	setAttr -s 71 ".kit[19:70]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 9 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 1;
	setAttr -s 71 ".kot[19:70]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 9 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 1;
	setAttr -s 71 ".kix[70]"  1;
	setAttr -s 71 ".kiy[70]"  0;
	setAttr -s 71 ".kox[70]"  1;
	setAttr -s 71 ".koy[70]"  0;
createNode animCurveTU -n "animCurveTU1709";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 71 ".ktv[0:70]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 172 0 178 0 230 0 242 0 252 0 258 0 264 0 269 0 275 0 290 0 300 0 350 0 400 0 420 
		0 428 0 441 0 445 0 450 0 464 0 472 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 
		0 655 0 670 0 680 0 690 0 706 0 714 0 720 0 727 0 731 0 735 0 740 0 745 0 749 0 754 
		0 760 0 770 0 790 0 795 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 71 ".kit[19:70]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 9 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 1;
	setAttr -s 71 ".kot[19:70]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 9 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 1;
	setAttr -s 71 ".kix[70]"  1;
	setAttr -s 71 ".kiy[70]"  0;
	setAttr -s 71 ".kox[70]"  1;
	setAttr -s 71 ".koy[70]"  0;
createNode animCurveTU -n "animCurveTU1710";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 71 ".ktv[0:70]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 172 0 178 0 230 0 242 0 252 0 258 0 264 0 269 0 275 0 290 0 300 0 350 0 400 0 420 
		0 428 0 441 0 445 0 450 0 464 0 472 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 
		0 655 0 670 0 680 0 690 0 706 0 714 0 720 0 727 0 731 0 735 0 740 0 745 0 749 0 754 
		0 760 0 770 0 790 0 795 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 71 ".kit[19:70]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 9 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 1;
	setAttr -s 71 ".kot[19:70]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 9 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 1;
	setAttr -s 71 ".kix[70]"  1;
	setAttr -s 71 ".kiy[70]"  0;
	setAttr -s 71 ".kox[70]"  1;
	setAttr -s 71 ".koy[70]"  0;
createNode animCurveTU -n "animCurveTU1711";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 71 ".ktv[0:70]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 172 0 178 0 230 0 242 0 252 0 258 0 264 0 269 0 275 0 290 0 300 0 350 0 400 0 420 
		0 428 0 441 0 445 0 450 0 464 0 472 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 
		0 655 0 670 0 680 0 690 0 706 0 714 0 720 0 727 0 731 0 735 0 740 0 745 0 749 0 754 
		0 760 0 770 0 790 0 795 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 71 ".kit[19:70]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 9 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 1;
	setAttr -s 71 ".kot[19:70]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 9 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 1;
	setAttr -s 71 ".kix[70]"  1;
	setAttr -s 71 ".kiy[70]"  0;
	setAttr -s 71 ".kox[70]"  1;
	setAttr -s 71 ".koy[70]"  0;
createNode animCurveTA -n "animCurveTA3294";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 76 ".ktv[0:75]"  0 105.19868997262471 50 105.19868997262471 
		65 105.19868997262471 81 105.19868997262471 140 105.19868997262471 150 101.84560429801644 
		160 130.59791612838339 168 162.89377627494568 172 181.34895578908166 178 181.34895578908166 
		230 181.34895578908166 242 153.29121982254446 247 172.81543470336268 252 152.49149611073662 
		258 193.29850966292119 264 155.92286011354486 269 197.98876390068725 275 167.5483994684194 
		283 138.03823720773312 290 203.0524787580373 300 203.0524787580373 350 203.0524787580373 
		400 203.0524787580373 411 146.56530859029846 420 148.12071045964532 428 164.63926745219575 
		441 203.19689332296414 445 286.31502578047184 450 318.97071618739722 464 321.09616266418539 
		472 274.93360570646263 480 220.24497276125081 492 89.484974255364321 499 111.17276985266753 
		504 139.34481854617621 510 139.34481854617621 620 139.34481854617621 626 132.31006342726855 
		630 176.41039817839439 638 225.9417774155869 655 225.9417774155869 670 233.5622648861164 
		680 235.63919973006213 690 242.69715065661575 706 242.69715065661575 714 211.08700833880991 
		720 185.32442173452668 727 259.52179186549472 731 185.32442173452668 735 259.52179186549472 
		740 185.32442173452668 745 259.52179186549472 749 185.32442173452668 754 259.52179186549472 
		760 295.87336886259152 770 290.78940869954147 790 314.90625978206214 795 378.69639731699704 
		800 433.78250121197954 810 447.29862092398508 821 455.1673751774656 830 447.29862092398508 
		837 455.1673751774656 843 447.29862092398508 850 455.1673751774656 860 447.29862092398508 
		875 447.29862092398508 890 402.13662105111854 898 434.25449398372831 905 398.71342927306063 
		912 379.49551266859919 920 376.2556898885706 930 454.76121290262904 937 465.19868997262466 
		950 465.19868997262466 970 465.19868997262466;
	setAttr -s 76 ".kit[21:75]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 9 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 76 ".kot[21:75]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 9 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 76 ".kix[75]"  1;
	setAttr -s 76 ".kiy[75]"  0;
	setAttr -s 76 ".kox[75]"  1;
	setAttr -s 76 ".koy[75]"  0;
createNode animCurveTA -n "animCurveTA3295";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 76 ".ktv[0:75]"  0 36.654829240123455 50 36.654829240123455 
		65 36.654829240123455 81 36.654829240123455 140 36.654829240123455 150 27.648278699369861 
		160 -6.5316763742589163 168 -2.1158697339443724 172 24.31937079525094 178 24.31937079525094 
		230 24.31937079525094 242 -37.919491888302673 247 -12.167045661765588 252 -51.763629122316971 
		258 -22.163624351936249 264 -58.874265406261586 269 -30.238287305757861 275 -44.180510636275727 
		283 -14.583897200753906 290 65.371853322193061 300 65.371853322193076 350 65.371853322193076 
		400 65.371853322193076 411 20.490844873578922 420 49.756946827669381 428 41.319171186148836 
		441 59.092726921066109 445 65.431144699446648 450 50.238391090309854 464 73.054842617379109 
		472 30.824370682258611 480 -32.153656407266666 492 -1.133468659317584 499 -12.782126198971879 
		504 0.45648380141299905 510 0.45648380141300016 620 0.45648380141302269 626 -3.8177778547760544 
		630 -49.300131310820589 638 -24.765268219401467 655 -24.765268219401467 670 -1.7189071632462931 
		680 -43.730125211997233 690 -37.169730721250545 706 -37.169730721250545 714 -19.278137116174204 
		720 -118.77098600873957 727 -49.351252948168032 731 -118.77098600873957 735 -49.351252948168032 
		740 -118.77098600873957 745 -49.351252948168032 749 -118.77098600873957 754 -49.351252948168032 
		760 -110.82356969567404 770 -153.50537388229176 790 -162.54518505261103 795 -160.74592251608127 
		800 -133.43420361821066 810 -147.87840691390448 821 -122.31312455292331 830 -147.87840691390448 
		837 -122.31312455292331 843 -147.87840691390448 850 -122.31312455292331 860 -147.87840691390448 
		875 -147.87840691390448 890 -132.92981562158874 898 -9.5522509813927741 905 -27.600599080784882 
		912 -37.200583456451596 920 -35.434670368830432 930 8.7391723693402579 937 36.654829240123476 
		950 36.654829240123476 970 36.654829240123476;
	setAttr -s 76 ".kit[21:75]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 9 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 76 ".kot[21:75]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 9 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 76 ".kix[75]"  1;
	setAttr -s 76 ".kiy[75]"  0;
	setAttr -s 76 ".kox[75]"  1;
	setAttr -s 76 ".koy[75]"  0;
createNode animCurveTA -n "animCurveTA3296";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 76 ".ktv[0:75]"  0 57.613096452811924 50 57.613096452811924 
		65 57.613096452811924 81 57.613096452811924 140 57.613096452811924 150 53.438798372014695 
		160 18.711273861482429 168 -5.6108884846018832 172 -4.1783530952378003 178 -4.1783530952378003 
		230 -4.1783530952378056 242 93.551593209595183 247 114.75969473717952 252 94.064321161158347 
		258 113.91475042445458 264 95.033454986844674 269 118.91026524580926 275 95.883989703362403 
		283 17.526121895320784 290 -25.435737238342902 300 -25.435737238342902 350 -25.435737238342909 
		400 -25.435737238342909 411 25.106224455933493 420 27.484819644746494 428 68.198782407374296 
		441 113.47695932552554 445 89.387697203690749 450 124.55243130349587 464 180.2087595355448 
		472 154.28185728888937 480 99.738338515730547 492 49.949722103567524 499 27.830577281833431 
		504 39.20292972073721 510 39.20292972073721 620 39.20292972073721 626 41.932156910136861 
		630 92.949609739934985 638 108.70627626580927 655 108.70627626580927 670 99.081451833437853 
		680 118.45577987791668 690 115.70198553497278 706 115.70198553497278 714 15.820508443663162 
		720 52.405073642870079 727 92.674003507165111 731 52.405073642870079 735 92.674003507165111 
		740 52.405073642870079 745 92.674003507165111 749 52.405073642870079 754 92.674003507165111 
		760 182.76700781757677 770 155.4541096415152 790 179.1599782864271 795 228.07860476182091 
		800 277.23680124526965 810 289.79157105448365 821 294.29234557291949 830 289.79157105448365 
		837 294.29234557291949 843 289.79157105448365 850 294.29234557291949 860 289.79157105448365 
		875 289.79157105448365 890 256.98755539691928 898 357.43447827376275 905 367.1214999668469 
		912 376.42035783320455 920 388.12559817306135 930 407.25177699209974 937 417.61309645281193 
		950 417.61309645281193 970 417.61309645281193;
	setAttr -s 76 ".kit[21:75]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 9 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 76 ".kot[21:75]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 9 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 76 ".kix[75]"  1;
	setAttr -s 76 ".kiy[75]"  0;
	setAttr -s 76 ".kox[75]"  1;
	setAttr -s 76 ".koy[75]"  0;
createNode animCurveTL -n "animCurveTL1153";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 77 ".ktv[0:76]"  0 0.88474536422881123 50 0.88474536422881123 
		65 0.8816643709120302 81 0.8816643709120302 140 0.8816643709120302 150 0.90049237069275456 
		160 0.27312578173480073 168 -0.37324484196992858 172 -0.43983011986025522 178 -0.37464739734511765 
		230 -0.4194968628824256 242 0.024010506821760647 247 0.18631457886734629 252 0.10540920412128692 
		258 0.16726370748279462 264 0.13770052549530415 269 0.19186360676221323 275 0.19393890360008825 
		283 0.25011736928412553 290 0.41834159424422301 300 0.4249305012115534 350 0.4249305012115534 
		400 0.41719086180434495 411 0.81902762626280701 420 1.0669781954351256 428 1.3071937294342275 
		441 2.0247291463453285 445 2.1263763352459528 450 2.289040152336471 464 2.0603686979093467 
		472 2.2093718426660227 480 1.9747044660647994 492 0.89875039095218101 499 1.181082272027496 
		504 1.0922755117526401 510 1.0922755117526401 620 1.0922755117526401 626 1.1141633399170461 
		630 1.4247312571068216 638 1.4094153097988951 655 1.5956501139723422 670 1.85040952130365 
		680 1.7508920494229718 690 1.7508920494229718 706 1.7508920494229718 714 1.5281784707212021 
		720 2.0458250065681058 727 1.8579981084685668 731 2.0458250065681058 735 1.8579981084685668 
		740 2.0458250065681058 745 1.8579981084685668 749 2.0458250065681058 754 1.8579981084685668 
		760 1.5808474319292873 770 1.1578904898682247 790 1.0811448267007937 795 1.2424901227808147 
		800 1.9422856626708673 810 1.9066804787591785 821 1.7911456773495382 830 1.8174875625462208 
		837 1.7911456773495382 843 1.8174875625462208 850 1.7911456773495382 860 1.8174875625462208 
		875 1.7057351773781255 890 1.5906048359989085 894 1.4796830910240077 898 1.0683454394295806 
		905 0.78191658130591568 912 0.93121315727515031 920 0.82554647682768101 930 0.85199230086483468 
		937 0.89013519460035884 950 0.87373915756001264 970 0.88474536422881123;
	setAttr -s 77 ".kit[7:76]"  3 10 10 10 10 10 10 10 
		10 10 10 10 10 10 9 10 10 10 10 3 10 10 1 10 10 
		10 10 10 10 10 10 10 9 10 10 10 10 9 10 3 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 77 ".kot[7:76]"  3 10 10 10 10 10 10 10 
		10 10 10 10 10 10 9 10 10 10 10 3 10 10 1 10 10 
		10 10 10 10 10 10 10 9 10 10 10 10 9 10 3 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 77 ".kix[29:76]"  0.96791690587997437 0.98734492063522339 
		0.45338088274002075 0.62375503778457642 0.90017956495285034 1 1 1 1 1 0.97960770130157471 
		0.92413479089736938 0.98308682441711426 1 1 0.96336513757705688 0.84532874822616577 
		1 1 1 1 1 1 1 0.61920648813247681 0.6059839129447937 0.89453363418579102 0.99488633871078491 
		0.36098206043243408 1 1 1 1 1 1 1 1 0.97521495819091797 0.9418070912361145 0.45475116372108459 
		0.46517133712768555 0.95943379402160645 0.99621444940567017 1 1 1 1 1;
	setAttr -s 77 ".kiy[29:76]"  -0.25127053260803223 -0.15858764946460724 
		-0.89131689071655273 -0.7816198468208313 0.43551883101463318 0 0 0 0 0 0.20091995596885681 
		0.38206663727760315 0.18313984572887421 0 0 -0.26819336414337158 0.53424650430679321 
		0 0 0 0 0 0 0 -0.7852281928062439 -0.79547691345214844 -0.44700077176094055 0.1010003462433815 
		0.93257278203964233 0 0 0 0 0 0 0 0 -0.22125943005084991 -0.33615395426750183 -0.89061856269836426 
		-0.88522058725357056 -0.28193399310112 0.086929470300674438 0 0 0 0 0;
	setAttr -s 77 ".kox[29:76]"  0.96791696548461914 0.98734492063522339 
		0.45338088274002075 0.62375503778457642 0.90017956495285034 1 1 1 1 1 0.97960770130157471 
		0.92413479089736938 0.98308682441711426 1 1 0.96336513757705688 0.84532874822616577 
		1 1 1 1 1 1 1 0.61920648813247681 0.6059839129447937 0.89453363418579102 0.99488633871078491 
		0.36098206043243408 1 1 1 1 1 1 1 1 0.97521495819091797 0.9418070912361145 0.45475116372108459 
		0.46517133712768555 0.95943379402160645 0.99621444940567017 1 1 1 1 1;
	setAttr -s 77 ".koy[29:76]"  -0.25127050280570984 -0.15858764946460724 
		-0.89131689071655273 -0.7816198468208313 0.43551883101463318 0 0 0 0 0 0.20091995596885681 
		0.38206663727760315 0.18313984572887421 0 0 -0.26819336414337158 0.53424650430679321 
		0 0 0 0 0 0 0 -0.7852281928062439 -0.79547691345214844 -0.44700077176094055 0.1010003462433815 
		0.93257278203964233 0 0 0 0 0 0 0 0 -0.22125943005084991 -0.33615395426750183 -0.89061856269836426 
		-0.88522058725357056 -0.28193399310112 0.086929470300674438 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL1154";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 77 ".ktv[0:76]"  0 -4.051477365794228 50 -4.0069893362383162 
		65 -4.3164549887822101 81 -4.3164549887822101 140 -4.3025181956649936 150 -4.3406165668689303 
		160 -4.3093864836785025 168 -3.9484719764304623 172 -3.9562846731296735 178 -3.9562846731296735 
		230 -3.9427239948617072 242 -4.1436258877408951 247 -4.0959008201311091 252 -4.2000593955286236 
		258 -4.1279789400635636 264 -4.2129289657736626 269 -4.1651691406381239 275 -4.2242236043364203 
		283 -4.2683738134135822 290 -3.972685283066566 300 -3.972685283066566 350 -3.972685283066566 
		400 -3.9940740610756218 411 -4.1843043950596295 420 -4.1846360681074843 428 -3.0360234024109984 
		441 -2.4878414907046653 445 -2.436114273415114 450 -2.2070927550678272 464 -1.7703857700465699 
		472 -0.84100931917629884 480 -0.52912116103973372 492 -1.4285727930512224 499 -1.3980239930642135 
		504 -1.0973148039676028 510 -1.0415705569878022 620 -1.0860246151616137 626 -1.3223537266850978 
		630 -1.2870954976126019 638 -1.1386940405194557 655 -1.0777431712605428 670 -1.1315938626955544 
		680 -1.2253716639317285 690 -1.1848373002331669 706 -1.1848373002331669 714 -1.0029033111239025 
		720 -1.7087658296753545 727 -1.204804614968263 731 -1.7087658296753545 735 -1.204804614968263 
		740 -1.7087658296753545 745 -1.204804614968263 749 -1.7087658296753545 754 -1.204804614968263 
		760 -1.4249770424256469 770 -1.7367197032072834 790 -1.5951687358946636 795 -1.3452940812512708 
		800 -0.43733241313558036 810 -0.44213822230835187 821 -0.7097382040218706 830 -0.52282652485382541 
		837 -0.7097382040218706 843 -0.52282652485382541 850 -0.7097382040218706 860 -0.52282652485382541 
		875 -1.0899715379110371 890 -1.1017107142854845 894 -1.6296069927268602 898 -2.0041864589450924 
		905 -2.2607522868540331 912 -2.7964394385310611 920 -3.316166314459315 930 -4.1997686494494229 
		937 -4.3007007463355693 950 -3.9299458545376718 970 -4.051477365794228;
	setAttr -s 77 ".kit[2:76]"  9 9 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 9 10 10 3 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 3 2 10 10 10 
		9 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 77 ".kot[2:76]"  9 9 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 9 10 10 3 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 3 2 10 10 10 
		9 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 77 ".kix[76]"  1;
	setAttr -s 77 ".kiy[76]"  0;
	setAttr -s 77 ".kox[76]"  1;
	setAttr -s 77 ".koy[76]"  0;
createNode animCurveTL -n "animCurveTL1155";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 78 ".ktv[0:77]"  0 1.9551928992468008 50 1.8733635857863755 
		65 1.8134080263324501 81 1.8134080263324501 140 1.8586425544034537 150 1.7051347170683868 
		160 2.1858934119859001 168 2.5971917527125465 172 2.589742922512102 178 2.589742922512102 
		230 2.598230399065443 242 2.324375316918954 247 2.3528106262832309 252 2.3190799382718019 
		258 2.3376323725420987 264 2.3090708670847793 269 2.3064651895063921 275 2.300286670001749 
		283 2.4596927841389369 290 1.6764509637371403 300 1.7373962705601247 350 1.7373962705601247 
		370 1.7792447256581854 400 1.8253280557557745 411 2.0793838470778394 420 2.056586595768946 
		428 2.462454357056123 441 2.4506360690294664 445 2.2310213780876191 450 2.2708601264903177 
		464 2.1865345272986585 472 2.539380113703849 480 2.5235347420091871 492 1.7781625441030233 
		499 1.8343525925389605 504 1.763469033548051 510 1.8263136417063104 620 1.7639560446358913 
		626 1.8002695482857412 630 2.4391973566242395 638 2.6602794981011622 655 2.5975361083142898 
		670 2.5628846440132724 680 2.5048343959341786 690 2.5202319562792468 706 2.5202319562792468 
		714 2.2218893008989076 720 1.757992442456402 727 2.2548663131778071 731 1.757992442456402 
		735 2.2548663131778071 740 1.757992442456402 745 2.2548663131778071 749 1.757992442456402 
		754 2.2548663131778071 760 1.9688681184649974 770 1.8677250293523178 790 1.8343850717870507 
		795 2.6290577065565932 800 2.4878555062815382 810 2.3771192880292826 821 2.2545647871345511 
		830 2.4590048432659684 837 2.2545647871345511 843 2.4590048432659684 850 2.2545647871345511 
		860 2.4590048432659684 875 2.3103981281220731 890 2.1194219250446253 894 1.8961785646055276 
		898 1.3143948459404919 905 1.1916815950471471 912 1.2229846010668817 920 1.1824565524279813 
		930 1.7238561558332037 937 1.8650634385935128 950 1.9596283803527079 970 1.9551928992468008;
	setAttr -s 78 ".kit[7:77]"  9 10 10 10 10 10 10 10 
		10 10 10 10 3 10 9 9 10 3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 3 10 3 1 10 10 10 9 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 78 ".kot[7:77]"  9 10 10 10 10 10 10 10 
		10 10 10 10 3 10 9 9 10 3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 3 10 3 1 10 10 10 9 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 78 ".kix[41:77]"  0.99728494882583618 1 1 1 0.9369657039642334 
		0.52214568853378296 0.99711692333221436 1 1 1 1 1 1 0.86686307191848755 0.80926781892776489 
		1 1 0.45439326763153076 0.89303803443908691 0.94870072603225708 0.99254083633422852 
		1 1 1 1 0.99776303768157959 0.94689303636550903 0.8368988037109375 0.31444859504699707 
		0.461678147315979 1 1 1 0.63873869180679321 0.94277781248092651 1 0.99754929542541504;
	setAttr -s 78 ".kiy[41:77]"  -0.073639154434204102 0 0 0 -0.34942138195037842 
		-0.8528563380241394 0.075881212949752808 0 0 0 0 0 0 0.49854618310928345 -0.5874398946762085 
		0 0 0.89080113172531128 -0.4499812126159668 -0.31617546081542969 0.12191225588321686 
		0 0 0 0 0.066850237548351288 -0.3215487003326416 -0.54735779762268066 -0.94927453994750977 
		-0.88704746961593628 0 0 0 0.7694237232208252 0.33342155814170837 0 -0.06996753066778183;
	setAttr -s 78 ".kox[41:77]"  0.99728494882583618 1 1 1 0.9369657039642334 
		0.52214568853378296 0.99711692333221436 1 1 1 1 1 1 0.86686307191848755 0.80926781892776489 
		1 1 0.45439326763153076 0.89303803443908691 0.94870072603225708 0.99254083633422852 
		1 1 1 1 0.99776303768157959 0.94689303636550903 0.8368988037109375 0.31444859504699707 
		0.461678147315979 1 1 1 0.63873869180679321 0.94277781248092651 1 0.99754929542541504;
	setAttr -s 78 ".koy[41:77]"  -0.073639154434204102 0 0 0 -0.34942138195037842 
		-0.8528563380241394 0.075881212949752808 0 0 0 0 0 0 0.49854618310928345 -0.5874398946762085 
		0 0 0.89080113172531128 -0.4499812126159668 -0.31617546081542969 0.12191225588321686 
		0 0 0 0 0.066850237548351288 -0.3215487003326416 -0.54735779762268066 -0.94927453994750977 
		-0.88704746961593628 0 0 0 0.7694237232208252 0.33342155814170837 0 -0.06996753066778183;
createNode animCurveTA -n "animCurveTA3297";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 59 ".ktv[0:58]"  0 0 50 0 65 0 81 0 140 0 150 0 160 -7.9550271911131265 
		168 -15.910045847413588 178 -15.910045847413588 230 -15.910045847413588 242 -15.910045847413588 
		275 -15.910045847413588 290 13.85698763785396 300 13.85698763785396 350 13.85698763785396 
		360 13.85698763785396 370 13.85698763785396 380 13.85698763785396 400 13.85698763785396 
		420 0 428 0 441 0 450 0 464 0 472 5.50289241483999 480 0 492 0 504 0 510 0 620 0 
		626 0 630 7.2377394935018255 638 14.475582524536907 670 14.475582524536907 680 14.475582524536907 
		690 14.475582524536907 706 14.475582524536907 720 0 750 0 760 0 790 0 800 3.0251083005940109 
		810 5.6111560619298899 821 5.6111560619298899 830 5.6111560619298899 837 5.6111560619298899 
		843 5.6111560619298899 850 5.6111560619298899 860 5.4023256346888768 868 1.5180632354036292 
		875 0 890 0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 59 ".kit[36:58]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 59 ".kot[36:58]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 59 ".kix[58]"  1;
	setAttr -s 59 ".kiy[58]"  0;
	setAttr -s 59 ".kox[58]"  1;
	setAttr -s 59 ".koy[58]"  0;
createNode animCurveTA -n "animCurveTA3298";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  0 7.1602109570938932 50 7.1602109570938932 
		65 -6.4180932322679478 81 -6.4180932322679478 140 -6.4180932322679487 150 -6.4180932322679487 
		160 -3.2090448946674273 168 0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 
		0 380 0 400 0 420 0 428 17.469846517291185 441 0 450 15.907699208588951 464 0 472 
		-0.58812528231284877 480 -20.111291914429529 486 6.0918734631774694 492 0 504 0 510 
		0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 0 714 10.125301006246294 720 -8.6856090627994682 
		750 0.32314078375002903 760 2.7823637146694487 790 1.5230450105727007 800 -4.9765644454235938 
		810 6.7640608746361046 821 6.7640608746361046 830 6.7640608746361046 837 6.7640608746361046 
		843 6.7640608746361046 850 6.7640608746361046 860 -2.5113608724573648 868 -9.6341974816032518 
		875 2.4558758153473446 890 2.4558758153473446 898 -12.695665145839188 905 0 912 12.35350774123906 
		920 0 930 -6.8501645875229169 937 -3.7465018741357841 950 5.0446583039923318 970 
		7.1602109570938932;
	setAttr -s 62 ".kit[37:61]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 62 ".kot[37:61]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 62 ".kix[61]"  1;
	setAttr -s 62 ".kiy[61]"  0;
	setAttr -s 62 ".kox[61]"  1;
	setAttr -s 62 ".koy[61]"  0;
createNode animCurveTA -n "animCurveTA3299";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 59 ".ktv[0:58]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 472 -13.787409893111173 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 
		0 670 0 680 0 690 0 706 0 720 0 750 0 760 0 790 0 800 12.423278787663008 810 12.463836052530151 
		821 12.463836052530151 830 12.463836052530151 837 12.463836052530151 843 12.463836052530151 
		850 12.463836052530151 860 15.107866081715496 868 8.158292659702056 875 0 890 0 905 
		0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 59 ".kit[36:58]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 59 ".kot[36:58]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 59 ".kix[58]"  1;
	setAttr -s 59 ".kiy[58]"  0;
	setAttr -s 59 ".kox[58]"  1;
	setAttr -s 59 ".koy[58]"  0;
createNode animCurveTA -n "animCurveTA3300";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3301";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3302";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1712";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU1713";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1714";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000004;
createNode animCurveTA -n "animCurveTA3303";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -93.148410662823451;
createNode animCurveTA -n "animCurveTA3304";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.087147345469543197;
createNode animCurveTA -n "animCurveTA3305";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -15.275860387989701;
createNode animCurveTA -n "animCurveTA3306";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3307";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3308";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1715";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU1716";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999967;
createNode animCurveTU -n "animCurveTU1717";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA3309";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 83.913182451591126;
createNode animCurveTA -n "animCurveTA3310";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.6823378597082943;
createNode animCurveTA -n "animCurveTA3311";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 5.0280589807764775;
createNode animCurveTA -n "animCurveTA3312";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3313";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3314";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1718";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000004;
createNode animCurveTU -n "animCurveTU1719";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTU -n "animCurveTU1720";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTA -n "animCurveTA3315";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3316";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 26.093661828935559;
createNode animCurveTA -n "animCurveTA3317";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3318";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3319";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3320";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1721";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000004;
createNode animCurveTU -n "animCurveTU1722";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1723";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000004;
createNode animCurveTA -n "animCurveTA3321";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 4.1383308710323172;
createNode animCurveTA -n "animCurveTA3322";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3323";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1724";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000004;
createNode animCurveTU -n "animCurveTU1725";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTU -n "animCurveTU1726";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA3324";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3325";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3326";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1156";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1157";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1158";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1727";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 64 ".ktv[0:63]"  0 0.99999999999999989 50 0.99999999999999989 
		65 0.99999999999999989 81 0.99999999999999989 140 0.99999999999999989 150 0.99999999999999989 
		160 0.99999999999999989 168 0.99999999999999989 178 0.99999999999999989 230 0.99999999999999989 
		242 0.99999999999999989 275 0.99999999999999989 290 0.99999999999999989 300 0.99999999999999989 
		350 0.99999999999999989 360 0.99999999999999989 370 0.99999999999999989 380 0.99999999999999989 
		400 0.99999999999999989 420 0.99999999999999989 428 0.99999999999999989 441 0.99999999999999989 
		450 0.99999999999999989 464 0.99999999999999989 480 0.99999999999999989 492 0.99999999999999989 
		504 0.99999999999999989 510 0.99999999999999989 620 0.99999999999999989 626 0.99999999999999989 
		630 0.99999999999999989 638 0.99999999999999989 670 0.99999999999999989 680 0.99999999999999989 
		690 0.99999999999999989 706 0.99999999999999989 720 0.99999999999999989 727 0.99999999999999989 
		731 0.99999999999999989 735 0.99999999999999989 740 0.99999999999999989 745 0.99999999999999989 
		749 0.99999999999999989 754 0.99999999999999989 770 0.99999999999999989 790 0.99999999999999989 
		795 0.99999999999999989 800 0.99999999999999989 810 0.99999999999999989 821 0.99999999999999989 
		830 0.99999999999999989 837 0.99999999999999989 843 0.99999999999999989 850 0.99999999999999989 
		860 0.99999999999999989 875 0.99999999999999989 890 0.99999999999999989 905 0.99999999999999989 
		912 0.99999999999999989 920 0.99999999999999989 930 0.99999999999999989 937 0.99999999999999989 
		950 0.99999999999999989 970 0.99999999999999989;
	setAttr -s 64 ".kit[35:63]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 64 ".kot[35:63]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 64 ".kix[63]"  1;
	setAttr -s 64 ".kiy[63]"  0;
	setAttr -s 64 ".kox[63]"  1;
	setAttr -s 64 ".koy[63]"  0;
createNode animCurveTU -n "animCurveTU1728";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 64 ".ktv[0:63]"  0 0.99999999999999989 50 0.99999999999999989 
		65 0.99999999999999989 81 0.99999999999999989 140 0.99999999999999989 150 0.99999999999999989 
		160 0.99999999999999989 168 0.99999999999999989 178 0.99999999999999989 230 0.99999999999999989 
		242 0.99999999999999989 275 0.99999999999999989 290 0.99999999999999989 300 0.99999999999999989 
		350 0.99999999999999989 360 0.99999999999999989 370 0.99999999999999989 380 0.99999999999999989 
		400 0.99999999999999989 420 0.99999999999999989 428 0.99999999999999989 441 0.99999999999999989 
		450 0.99999999999999989 464 0.99999999999999989 480 0.99999999999999989 492 0.99999999999999989 
		504 0.99999999999999989 510 0.99999999999999989 620 0.99999999999999989 626 0.99999999999999989 
		630 0.99999999999999989 638 0.99999999999999989 670 0.99999999999999989 680 0.99999999999999989 
		690 0.99999999999999989 706 0.99999999999999989 720 0.99999999999999989 727 0.99999999999999989 
		731 0.99999999999999989 735 0.99999999999999989 740 0.99999999999999989 745 0.99999999999999989 
		749 0.99999999999999989 754 0.99999999999999989 770 0.99999999999999989 790 0.99999999999999989 
		795 0.99999999999999989 800 0.99999999999999989 810 0.99999999999999989 821 0.99999999999999989 
		830 0.99999999999999989 837 0.99999999999999989 843 0.99999999999999989 850 0.99999999999999989 
		860 0.99999999999999989 875 0.99999999999999989 890 0.99999999999999989 905 0.99999999999999989 
		912 0.99999999999999989 920 0.99999999999999989 930 0.99999999999999989 937 0.99999999999999989 
		950 0.99999999999999989 970 0.99999999999999989;
	setAttr -s 64 ".kit[35:63]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 64 ".kot[35:63]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 64 ".kix[63]"  1;
	setAttr -s 64 ".kiy[63]"  0;
	setAttr -s 64 ".kox[63]"  1;
	setAttr -s 64 ".koy[63]"  0;
createNode animCurveTU -n "animCurveTU1729";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 64 ".ktv[0:63]"  0 0.99999999999999989 50 0.99999999999999989 
		65 0.99999999999999989 81 0.99999999999999989 140 0.99999999999999989 150 0.99999999999999989 
		160 0.99999999999999989 168 0.99999999999999989 178 0.99999999999999989 230 0.99999999999999989 
		242 0.99999999999999989 275 0.99999999999999989 290 0.99999999999999989 300 0.99999999999999989 
		350 0.99999999999999989 360 0.99999999999999989 370 0.99999999999999989 380 0.99999999999999989 
		400 0.99999999999999989 420 0.99999999999999989 428 0.99999999999999989 441 0.99999999999999989 
		450 0.99999999999999989 464 0.99999999999999989 480 0.99999999999999989 492 0.99999999999999989 
		504 0.99999999999999989 510 0.99999999999999989 620 0.99999999999999989 626 0.99999999999999989 
		630 0.99999999999999989 638 0.99999999999999989 670 0.99999999999999989 680 0.99999999999999989 
		690 0.99999999999999989 706 0.99999999999999989 720 0.99999999999999989 727 0.99999999999999989 
		731 0.99999999999999989 735 0.99999999999999989 740 0.99999999999999989 745 0.99999999999999989 
		749 0.99999999999999989 754 0.99999999999999989 770 0.99999999999999989 790 0.99999999999999989 
		795 0.99999999999999989 800 0.99999999999999989 810 0.99999999999999989 821 0.99999999999999989 
		830 0.99999999999999989 837 0.99999999999999989 843 0.99999999999999989 850 0.99999999999999989 
		860 0.99999999999999989 875 0.99999999999999989 890 0.99999999999999989 905 0.99999999999999989 
		912 0.99999999999999989 920 0.99999999999999989 930 0.99999999999999989 937 0.99999999999999989 
		950 0.99999999999999989 970 0.99999999999999989;
	setAttr -s 64 ".kit[35:63]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 64 ".kot[35:63]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 64 ".kix[63]"  1;
	setAttr -s 64 ".kiy[63]"  0;
	setAttr -s 64 ".kox[63]"  1;
	setAttr -s 64 ".koy[63]"  0;
createNode animCurveTA -n "animCurveTA3327";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 67 ".ktv[0:66]"  0 0 50 0 65 0 81 0 140 0 150 0 160 3.1421057356177009 
		168 4.5370143020242217 178 6.2842081001238794 230 6.2842081001238794 242 0 275 0 
		290 1.308473539629361 300 1.308473539629361 350 1.308473539629361 360 33.904004041072255 
		370 33.904004041072255 380 33.904004041072255 400 33.904004041072255 411 0 420 0 
		428 0 441 13.47523710025653 450 39.684556293057305 464 39.684556293057305 480 0 492 
		0 504 9.9443577797157285 510 9.9443577797157285 620 9.9443577797157268 626 9.9443577797157268 
		630 9.9443577797157268 638 9.9443577797157268 670 9.9443577797157268 680 9.9443577797157268 
		690 9.9443577797157268 706 9.9443577797157268 720 17.901367641816059 727 18.147702272832795 
		731 17.901367641816059 735 18.147702272832795 740 17.901367641816059 745 18.147702272832795 
		749 17.901367641816059 754 18.147702272832795 760 0 770 10.964154998241117 790 10.964154998241117 
		795 10.256837133245533 800 13.301045576053516 810 13.301045576053516 821 13.301045576053516 
		830 13.301045576053516 837 13.301045576053516 843 13.301045576053516 850 13.301045576053516 
		860 13.301045576053516 875 12.956788938228684 890 10.964154998241117 898 0 905 12.189745898308942 
		912 12.189745898308942 920 12.189745898308942 930 6.046138463619906 937 0 950 0 970 
		0;
	setAttr -s 67 ".kit[36:66]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 1;
	setAttr -s 67 ".kot[36:66]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 1;
	setAttr -s 67 ".kix[66]"  1;
	setAttr -s 67 ".kiy[66]"  0;
	setAttr -s 67 ".kox[66]"  1;
	setAttr -s 67 ".koy[66]"  0;
createNode animCurveTA -n "animCurveTA3328";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 67 ".ktv[0:66]"  0 0 50 0 65 0 81 0 140 0 150 0 160 4.954780979560903 
		168 19.343180847086323 178 9.9095566432220039 230 9.9095566432220039 242 0 275 0 
		290 12.813959982900023 300 12.813959982900023 350 12.813959982900023 360 17.251157419036517 
		370 17.251157419036517 380 17.251157419036517 400 17.251157419036517 411 0 420 0 
		428 0 441 10.478472253545176 450 1.262600204988632 464 1.262600204988632 480 0 492 
		0 504 -16.067084123698855 510 -16.067084123698855 620 -16.067084123698855 626 -16.067084123698855 
		630 -16.067084123698855 638 -16.067084123698855 670 -16.067084123698855 680 -16.067084123698855 
		690 -16.067084123698855 706 -16.067084123698855 720 14.04825510442063 727 20.55495596670244 
		731 14.04825510442063 735 20.55495596670244 740 14.04825510442063 745 20.55495596670244 
		749 14.04825510442063 754 20.55495596670244 760 0 770 13.800041460981326 790 13.800041460981326 
		795 14.582337086987993 800 15.625792686541585 810 15.625792686541585 821 15.625792686541585 
		830 15.625792686541585 837 15.625792686541585 843 15.625792686541585 850 15.625792686541585 
		860 15.625792686541585 875 18.125577298588116 890 13.800041460981326 898 0 905 8.0461251686510877 
		912 8.0461251686510877 920 8.0461251686510877 930 3.9908942595797532 937 0 950 0 
		970 0;
	setAttr -s 67 ".kit[36:66]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 1;
	setAttr -s 67 ".kot[36:66]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 1;
	setAttr -s 67 ".kix[66]"  1;
	setAttr -s 67 ".kiy[66]"  0;
	setAttr -s 67 ".kox[66]"  1;
	setAttr -s 67 ".koy[66]"  0;
createNode animCurveTA -n "animCurveTA3329";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 67 ".ktv[0:66]"  0 0 50 0 65 0 81 0 140 0 150 0 160 -3.5631925267355111 
		168 -18.398209657855368 178 -7.1263812305826839 230 -7.1263812305826839 242 0 275 
		0 290 -10.921127623199855 300 -10.921127623199855 350 -10.921127623199855 360 3.7540406234365946 
		370 3.7540406234365964 380 3.7540406234365964 400 3.7540406234365964 411 0 420 0 
		428 0 441 3.2348467030921251 450 33.623152354320077 464 33.623152354320077 480 0 
		492 0 504 16.668607752579678 510 16.668607752579678 620 16.668607752579678 626 16.668607752579678 
		630 16.668607752579678 638 16.668607752579678 670 16.668607752579678 680 16.668607752579678 
		690 16.668607752579678 706 16.668607752579678 720 3.8832261077831278 727 -4.3612350901422978 
		731 3.8832261077831278 735 -4.3612350901422978 740 3.8832261077831278 745 -4.3612350901422978 
		749 3.8832261077831278 754 -4.3612350901422978 760 0 770 -1.5466032260386529 790 
		-1.5466032260386529 795 -9.5505693180355529 800 -21.254254398643344 810 -21.254254398643344 
		821 -21.254254398643344 830 -21.254254398643344 837 -21.254254398643344 843 -21.254254398643344 
		850 -21.254254398643344 860 -21.254254398643344 875 -5.8853361309788408 890 -1.5466032260386529 
		898 0 905 -12.55661534709947 912 -12.55661534709947 920 -12.55661534709947 930 -6.2281064741639343 
		937 0 950 0 970 0;
	setAttr -s 67 ".kit[36:66]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 1;
	setAttr -s 67 ".kot[36:66]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 1;
	setAttr -s 67 ".kix[66]"  1;
	setAttr -s 67 ".kiy[66]"  0;
	setAttr -s 67 ".kox[66]"  1;
	setAttr -s 67 ".koy[66]"  0;
createNode animCurveTL -n "animCurveTL1159";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 64 ".ktv[0:63]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 727 0 731 0 735 0 740 0 745 0 749 0 754 0 770 0 790 0 795 0 800 0 810 0 821 
		0 830 0 837 0 843 0 850 0 860 0 875 0 890 0 905 0 912 0 920 0 930 0 937 0 950 0 970 
		0;
	setAttr -s 64 ".kit[35:63]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 64 ".kot[35:63]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 64 ".kix[63]"  1;
	setAttr -s 64 ".kiy[63]"  0;
	setAttr -s 64 ".kox[63]"  1;
	setAttr -s 64 ".koy[63]"  0;
createNode animCurveTL -n "animCurveTL1160";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 64 ".ktv[0:63]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 727 0 731 0 735 0 740 0 745 0 749 0 754 0 770 0 790 0 795 0 800 0 810 0 821 
		0 830 0 837 0 843 0 850 0 860 0 875 0 890 0 905 0 912 0 920 0 930 0 937 0 950 0 970 
		0;
	setAttr -s 64 ".kit[35:63]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 64 ".kot[35:63]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 64 ".kix[63]"  1;
	setAttr -s 64 ".kiy[63]"  0;
	setAttr -s 64 ".kox[63]"  1;
	setAttr -s 64 ".koy[63]"  0;
createNode animCurveTL -n "animCurveTL1161";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 64 ".ktv[0:63]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 727 0 731 0 735 0 740 0 745 0 749 0 754 0 770 0 790 0 795 0 800 0 810 0 821 
		0 830 0 837 0 843 0 850 0 860 0 875 0 890 0 905 0 912 0 920 0 930 0 937 0 950 0 970 
		0;
	setAttr -s 64 ".kit[35:63]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 64 ".kot[35:63]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 64 ".kix[63]"  1;
	setAttr -s 64 ".kiy[63]"  0;
	setAttr -s 64 ".kox[63]"  1;
	setAttr -s 64 ".koy[63]"  0;
createNode animCurveTA -n "animCurveTA3330";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3331";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3332";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1730";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1731";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1732";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999978;
createNode animCurveTA -n "animCurveTA3333";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3334";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3335";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3336";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3337";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3338";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1733";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1734";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1735";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA3339";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3340";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3341";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3342";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3343";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3344";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1736";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1737";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1738";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTA -n "animCurveTA3345";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3346";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3347";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3348";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3349";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3350";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1739";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.99999999999999989 50 0.99999999999999989 
		65 0.99999999999999989 81 0.99999999999999989 140 0.99999999999999989 150 0.99999999999999989 
		160 0.99999999999999989 168 0.99999999999999989 178 0.99999999999999989 230 0.99999999999999989 
		242 0.99999999999999989 275 0.99999999999999989 290 0.99999999999999989 300 0.99999999999999989 
		350 0.99999999999999989 360 0.99999999999999989 370 0.99999999999999989 380 0.99999999999999989 
		400 0.99999999999999989 420 0.99999999999999989 428 0.99999999999999989 441 0.99999999999999989 
		450 0.99999999999999989 464 0.99999999999999989 480 0.99999999999999989 492 0.99999999999999989 
		504 0.99999999999999989 510 0.99999999999999989 620 0.99999999999999989 626 0.99999999999999989 
		630 0.99999999999999989 638 0.99999999999999989 670 0.99999999999999989 680 0.99999999999999989 
		690 0.99999999999999989 706 0.99999999999999989 720 0.99999999999999989 750 0.99999999999999989 
		760 0.99999999999999989 790 0.99999999999999989 800 0.99999999999999989 810 0.99999999999999989 
		821 0.99999999999999989 830 0.99999999999999989 837 0.99999999999999989 843 0.99999999999999989 
		850 0.99999999999999989 860 0.99999999999999989 875 0.99999999999999989 890 0.99999999999999989 
		905 0.99999999999999989 912 0.99999999999999989 920 0.99999999999999989 930 0.99999999999999989 
		937 0.99999999999999989 950 0.99999999999999989 970 0.99999999999999989;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1740";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.99999999999999989 50 0.99999999999999989 
		65 0.99999999999999989 81 0.99999999999999989 140 0.99999999999999989 150 0.99999999999999989 
		160 0.99999999999999989 168 0.99999999999999989 178 0.99999999999999989 230 0.99999999999999989 
		242 0.99999999999999989 275 0.99999999999999989 290 0.99999999999999989 300 0.99999999999999989 
		350 0.99999999999999989 360 0.99999999999999989 370 0.99999999999999989 380 0.99999999999999989 
		400 0.99999999999999989 420 0.99999999999999989 428 0.99999999999999989 441 0.99999999999999989 
		450 0.99999999999999989 464 0.99999999999999989 480 0.99999999999999989 492 0.99999999999999989 
		504 0.99999999999999989 510 0.99999999999999989 620 0.99999999999999989 626 0.99999999999999989 
		630 0.99999999999999989 638 0.99999999999999989 670 0.99999999999999989 680 0.99999999999999989 
		690 0.99999999999999989 706 0.99999999999999989 720 0.99999999999999989 750 0.99999999999999989 
		760 0.99999999999999989 790 0.99999999999999989 800 0.99999999999999989 810 0.99999999999999989 
		821 0.99999999999999989 830 0.99999999999999989 837 0.99999999999999989 843 0.99999999999999989 
		850 0.99999999999999989 860 0.99999999999999989 875 0.99999999999999989 890 0.99999999999999989 
		905 0.99999999999999989 912 0.99999999999999989 920 0.99999999999999989 930 0.99999999999999989 
		937 0.99999999999999989 950 0.99999999999999989 970 0.99999999999999989;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1741";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.99999999999999989 50 0.99999999999999989 
		65 0.99999999999999989 81 0.99999999999999989 140 0.99999999999999989 150 0.99999999999999989 
		160 0.99999999999999989 168 0.99999999999999989 178 0.99999999999999989 230 0.99999999999999989 
		242 0.99999999999999989 275 0.99999999999999989 290 0.99999999999999989 300 0.99999999999999989 
		350 0.99999999999999989 360 0.99999999999999989 370 0.99999999999999989 380 0.99999999999999989 
		400 0.99999999999999989 420 0.99999999999999989 428 0.99999999999999989 441 0.99999999999999989 
		450 0.99999999999999989 464 0.99999999999999989 480 0.99999999999999989 492 0.99999999999999989 
		504 0.99999999999999989 510 0.99999999999999989 620 0.99999999999999989 626 0.99999999999999989 
		630 0.99999999999999989 638 0.99999999999999989 670 0.99999999999999989 680 0.99999999999999989 
		690 0.99999999999999989 706 0.99999999999999989 720 0.99999999999999989 750 0.99999999999999989 
		760 0.99999999999999989 790 0.99999999999999989 800 0.99999999999999989 810 0.99999999999999989 
		821 0.99999999999999989 830 0.99999999999999989 837 0.99999999999999989 843 0.99999999999999989 
		850 0.99999999999999989 860 0.99999999999999989 875 0.99999999999999989 890 0.99999999999999989 
		905 0.99999999999999989 912 0.99999999999999989 920 0.99999999999999989 930 0.99999999999999989 
		937 0.99999999999999989 950 0.99999999999999989 970 0.99999999999999989;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3351";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 21.441017057914681 50 21.441017057914681 
		65 16.244152037452814 81 16.244152037452814 140 16.244152037452814 150 16.244152037452814 
		160 16.244152037452814 168 16.244152037452814 178 16.244152037452814 230 16.244152037452814 
		242 16.244152037452814 275 16.244152037452814 290 16.244152037452814 300 16.244152037452814 
		350 16.244152037452814 360 16.244152037452814 370 16.244152037452814 380 16.244152037452814 
		400 16.244152037452814 420 16.244152037452814 428 16.244152037452814 441 16.244152037452814 
		450 16.244152037452814 464 16.244152037452814 480 16.244152037452814 492 16.244152037452814 
		504 16.244152037452814 510 16.244152037452814 620 16.244152037452814 626 16.244152037452814 
		630 16.244152037452814 638 16.244152037452814 670 16.244152037452814 680 16.244152037452814 
		690 16.244152037452814 706 16.244152037452814 720 16.244152037452814 750 16.244152037452814 
		760 16.244152037452814 790 16.244152037452814 800 16.244152037452814 810 16.244152037452814 
		821 16.244152037452814 830 16.244152037452814 837 16.244152037452814 843 16.244152037452814 
		850 16.244152037452814 860 16.244152037452814 875 16.244152037452814 890 16.244152037452814 
		905 16.244152037452814 912 16.244152037452814 920 16.244152037452814 930 18.863361550730279 
		937 21.441017057914681 950 21.441017057914681 970 21.441017057914681;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3352";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3353";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3354";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3355";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3356";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1742";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.99999999999999944 50 0.99999999999999944 
		65 0.99999999999999944 81 0.99999999999999944 140 0.99999999999999944 150 0.99999999999999944 
		160 0.99999999999999944 168 0.99999999999999944 178 0.99999999999999944 230 0.99999999999999944 
		242 0.99999999999999944 275 0.99999999999999944 290 0.99999999999999944 300 0.99999999999999944 
		350 0.99999999999999944 360 0.99999999999999944 370 0.99999999999999944 380 0.99999999999999944 
		400 0.99999999999999944 420 0.99999999999999944 428 0.99999999999999944 441 0.99999999999999944 
		450 0.99999999999999944 464 0.99999999999999944 480 0.99999999999999944 492 0.99999999999999944 
		504 0.99999999999999944 510 0.99999999999999944 620 0.99999999999999944 626 0.99999999999999944 
		630 0.99999999999999944 638 0.99999999999999944 670 0.99999999999999944 680 0.99999999999999944 
		690 0.99999999999999944 706 0.99999999999999944 720 0.99999999999999944 750 0.99999999999999944 
		760 0.99999999999999944 790 0.99999999999999944 800 0.99999999999999944 810 0.99999999999999944 
		821 0.99999999999999944 830 0.99999999999999944 837 0.99999999999999944 843 0.99999999999999944 
		850 0.99999999999999944 860 0.99999999999999944 875 0.99999999999999944 890 0.99999999999999944 
		905 0.99999999999999944 912 0.99999999999999944 920 0.99999999999999944 930 0.99999999999999944 
		937 0.99999999999999944 950 0.99999999999999944 970 0.99999999999999944;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1743";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.99999999999999956 50 0.99999999999999956 
		65 0.99999999999999956 81 0.99999999999999956 140 0.99999999999999956 150 0.99999999999999956 
		160 0.99999999999999956 168 0.99999999999999956 178 0.99999999999999956 230 0.99999999999999956 
		242 0.99999999999999956 275 0.99999999999999956 290 0.99999999999999956 300 0.99999999999999956 
		350 0.99999999999999956 360 0.99999999999999956 370 0.99999999999999956 380 0.99999999999999956 
		400 0.99999999999999956 420 0.99999999999999956 428 0.99999999999999956 441 0.99999999999999956 
		450 0.99999999999999956 464 0.99999999999999956 480 0.99999999999999956 492 0.99999999999999956 
		504 0.99999999999999956 510 0.99999999999999956 620 0.99999999999999956 626 0.99999999999999956 
		630 0.99999999999999956 638 0.99999999999999956 670 0.99999999999999956 680 0.99999999999999956 
		690 0.99999999999999956 706 0.99999999999999956 720 0.99999999999999956 750 0.99999999999999956 
		760 0.99999999999999956 790 0.99999999999999956 800 0.99999999999999956 810 0.99999999999999956 
		821 0.99999999999999956 830 0.99999999999999956 837 0.99999999999999956 843 0.99999999999999956 
		850 0.99999999999999956 860 0.99999999999999956 875 0.99999999999999956 890 0.99999999999999956 
		905 0.99999999999999956 912 0.99999999999999956 920 0.99999999999999956 930 0.99999999999999956 
		937 0.99999999999999956 950 0.99999999999999956 970 0.99999999999999956;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1744";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.99999999999999967 50 0.99999999999999967 
		65 0.99999999999999967 81 0.99999999999999967 140 0.99999999999999967 150 0.99999999999999967 
		160 0.99999999999999967 168 0.99999999999999967 178 0.99999999999999967 230 0.99999999999999967 
		242 0.99999999999999967 275 0.99999999999999967 290 0.99999999999999967 300 0.99999999999999967 
		350 0.99999999999999967 360 0.99999999999999967 370 0.99999999999999967 380 0.99999999999999967 
		400 0.99999999999999967 420 0.99999999999999967 428 0.99999999999999967 441 0.99999999999999967 
		450 0.99999999999999967 464 0.99999999999999967 480 0.99999999999999967 492 0.99999999999999967 
		504 0.99999999999999967 510 0.99999999999999967 620 0.99999999999999967 626 0.99999999999999967 
		630 0.99999999999999967 638 0.99999999999999967 670 0.99999999999999967 680 0.99999999999999967 
		690 0.99999999999999967 706 0.99999999999999967 720 0.99999999999999967 750 0.99999999999999967 
		760 0.99999999999999967 790 0.99999999999999967 800 0.99999999999999967 810 0.99999999999999967 
		821 0.99999999999999967 830 0.99999999999999967 837 0.99999999999999967 843 0.99999999999999967 
		850 0.99999999999999967 860 0.99999999999999967 875 0.99999999999999967 890 0.99999999999999967 
		905 0.99999999999999967 912 0.99999999999999967 920 0.99999999999999967 930 0.99999999999999967 
		937 0.99999999999999967 950 0.99999999999999967 970 0.99999999999999967;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3357";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3358";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3359";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3360";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3361";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3362";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1745";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.99999999999999989 50 0.99999999999999989 
		65 0.99999999999999989 81 0.99999999999999989 140 0.99999999999999989 150 0.99999999999999989 
		160 0.99999999999999989 168 0.99999999999999989 178 0.99999999999999989 230 0.99999999999999989 
		242 0.99999999999999989 275 0.99999999999999989 290 0.99999999999999989 300 0.99999999999999989 
		350 0.99999999999999989 360 0.99999999999999989 370 0.99999999999999989 380 0.99999999999999989 
		400 0.99999999999999989 420 0.99999999999999989 428 0.99999999999999989 441 0.99999999999999989 
		450 0.99999999999999989 464 0.99999999999999989 480 0.99999999999999989 492 0.99999999999999989 
		504 0.99999999999999989 510 0.99999999999999989 620 0.99999999999999989 626 0.99999999999999989 
		630 0.99999999999999989 638 0.99999999999999989 670 0.99999999999999989 680 0.99999999999999989 
		690 0.99999999999999989 706 0.99999999999999989 720 0.99999999999999989 750 0.99999999999999989 
		760 0.99999999999999989 790 0.99999999999999989 800 0.99999999999999989 810 0.99999999999999989 
		821 0.99999999999999989 830 0.99999999999999989 837 0.99999999999999989 843 0.99999999999999989 
		850 0.99999999999999989 860 0.99999999999999989 875 0.99999999999999989 890 0.99999999999999989 
		905 0.99999999999999989 912 0.99999999999999989 920 0.99999999999999989 930 0.99999999999999989 
		937 0.99999999999999989 950 0.99999999999999989 970 0.99999999999999989;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1746";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 370 1 380 1 400 1 420 1 428 1 441 
		1 450 1 464 1 480 1 492 1 504 1 510 1 620 1 626 1 630 1 638 1 670 1 680 1 690 1 706 
		1 720 1 750 1 760 1 790 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 1 890 
		1 905 1 912 1 920 1 930 1 937 1 950 1 970 1;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1747";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 370 1 380 1 400 1 420 1 428 1 441 
		1 450 1 464 1 480 1 492 1 504 1 510 1 620 1 626 1 630 1 638 1 670 1 680 1 690 1 706 
		1 720 1 750 1 760 1 790 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 1 890 
		1 905 1 912 1 920 1 930 1 937 1 950 1 970 1;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3363";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3364";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3365";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3366";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3367";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3368";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1748";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.99999999999999989 50 0.99999999999999989 
		65 0.99999999999999989 81 0.99999999999999989 140 0.99999999999999989 150 0.99999999999999989 
		160 0.99999999999999989 168 0.99999999999999989 178 0.99999999999999989 230 0.99999999999999989 
		242 0.99999999999999989 275 0.99999999999999989 290 0.99999999999999989 300 0.99999999999999989 
		350 0.99999999999999989 360 0.99999999999999989 370 0.99999999999999989 380 0.99999999999999989 
		400 0.99999999999999989 420 0.99999999999999989 428 0.99999999999999989 441 0.99999999999999989 
		450 0.99999999999999989 464 0.99999999999999989 480 0.99999999999999989 492 0.99999999999999989 
		504 0.99999999999999989 510 0.99999999999999989 620 0.99999999999999989 626 0.99999999999999989 
		630 0.99999999999999989 638 0.99999999999999989 670 0.99999999999999989 680 0.99999999999999989 
		690 0.99999999999999989 706 0.99999999999999989 720 0.99999999999999989 750 0.99999999999999989 
		760 0.99999999999999989 790 0.99999999999999989 800 0.99999999999999989 810 0.99999999999999989 
		821 0.99999999999999989 830 0.99999999999999989 837 0.99999999999999989 843 0.99999999999999989 
		850 0.99999999999999989 860 0.99999999999999989 875 0.99999999999999989 890 0.99999999999999989 
		905 0.99999999999999989 912 0.99999999999999989 920 0.99999999999999989 930 0.99999999999999989 
		937 0.99999999999999989 950 0.99999999999999989 970 0.99999999999999989;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1749";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.99999999999999978 50 0.99999999999999978 
		65 0.99999999999999978 81 0.99999999999999978 140 0.99999999999999978 150 0.99999999999999978 
		160 0.99999999999999978 168 0.99999999999999978 178 0.99999999999999978 230 0.99999999999999978 
		242 0.99999999999999978 275 0.99999999999999978 290 0.99999999999999978 300 0.99999999999999978 
		350 0.99999999999999978 360 0.99999999999999978 370 0.99999999999999978 380 0.99999999999999978 
		400 0.99999999999999978 420 0.99999999999999978 428 0.99999999999999978 441 0.99999999999999978 
		450 0.99999999999999978 464 0.99999999999999978 480 0.99999999999999978 492 0.99999999999999978 
		504 0.99999999999999978 510 0.99999999999999978 620 0.99999999999999978 626 0.99999999999999978 
		630 0.99999999999999978 638 0.99999999999999978 670 0.99999999999999978 680 0.99999999999999978 
		690 0.99999999999999978 706 0.99999999999999978 720 0.99999999999999978 750 0.99999999999999978 
		760 0.99999999999999978 790 0.99999999999999978 800 0.99999999999999978 810 0.99999999999999978 
		821 0.99999999999999978 830 0.99999999999999978 837 0.99999999999999978 843 0.99999999999999978 
		850 0.99999999999999978 860 0.99999999999999978 875 0.99999999999999978 890 0.99999999999999978 
		905 0.99999999999999978 912 0.99999999999999978 920 0.99999999999999978 930 0.99999999999999978 
		937 0.99999999999999978 950 0.99999999999999978 970 0.99999999999999978;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1750";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 370 1 380 1 400 1 420 1 428 1 441 
		1 450 1 464 1 480 1 492 1 504 1 510 1 620 1 626 1 630 1 638 1 670 1 680 1 690 1 706 
		1 720 1 750 1 760 1 790 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 1 890 
		1 905 1 912 1 920 1 930 1 937 1 950 1 970 1;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3369";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 -4.6159099819999998 50 -4.6159099819999998 
		65 -4.6159099819999998 81 -4.6159099819999998 140 -4.6159099819999998 150 -4.6159099819999998 
		160 -4.6159099819999998 168 -4.6159099819999998 178 -4.6159099819999998 230 -4.6159099819999998 
		242 -4.6159099819999998 275 -4.6159099819999998 290 -4.6159099819999998 300 -4.6159099819999998 
		350 -4.6159099819999998 360 -4.6159099819999998 370 -4.6159099819999998 380 -4.6159099819999998 
		400 -4.6159099819999998 420 -4.6159099819999998 428 -4.6159099819999998 441 -4.6159099819999998 
		450 -4.6159099819999998 464 -4.6159099819999998 480 -4.6159099819999998 492 -4.6159099819999998 
		504 -4.6159099819999998 510 -4.6159099819999998 620 -4.6159099819999998 626 -4.6159099819999998 
		630 -4.6159099819999998 638 -4.6159099819999998 670 -4.6159099819999998 680 -4.6159099819999998 
		690 -4.6159099819999998 706 -4.6159099819999998 720 -4.6159099819999998 750 -4.6159099819999998 
		760 -4.6159099819999998 790 -4.6159099819999998 800 -4.6159099819999998 810 -4.6159099819999998 
		821 -4.6159099819999998 830 -4.6159099819999998 837 -4.6159099819999998 843 -4.6159099819999998 
		850 -4.6159099819999998 860 -4.6159099819999998 875 -4.6159099819999998 890 -4.6159099819999998 
		905 -4.6159099819999998 912 -4.6159099819999998 920 -4.6159099819999998 930 -4.6159099819999998 
		937 -4.6159099819999998 950 -4.6159099819999998 970 -4.6159099819999998;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3370";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 -20.29236869 50 -20.29236869 65 -20.29236869 
		81 -20.29236869 140 -20.29236869 150 -20.29236869 160 -20.29236869 168 -20.29236869 
		178 -20.29236869 230 -20.29236869 242 -20.29236869 275 -20.29236869 290 -20.29236869 
		300 -20.29236869 350 -20.29236869 360 -20.29236869 370 -20.29236869 380 -20.29236869 
		400 -20.29236869 420 -20.29236869 428 -20.29236869 441 -20.29236869 450 -20.29236869 
		464 -20.29236869 480 -20.29236869 492 -20.29236869 504 -20.29236869 510 -20.29236869 
		620 -20.29236869 626 -20.29236869 630 -20.29236869 638 -20.29236869 670 -20.29236869 
		680 -20.29236869 690 -20.29236869 706 -20.29236869 720 -20.29236869 750 -20.29236869 
		760 -20.29236869 790 -20.29236869 800 -20.29236869 810 -20.29236869 821 -20.29236869 
		830 -20.29236869 837 -20.29236869 843 -20.29236869 850 -20.29236869 860 -20.29236869 
		875 -20.29236869 890 -20.29236869 905 -20.29236869 912 -20.29236869 920 -20.29236869 
		930 -20.29236869 937 -20.29236869 950 -20.29236869 970 -20.29236869;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3371";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 -6.2745051959999998 50 -6.2745051959999998 
		65 -6.2745051959999998 81 -6.2745051959999998 140 -6.2745051959999998 150 -6.2745051959999998 
		160 -6.2745051959999998 168 -6.2745051959999998 178 -6.2745051959999998 230 -6.2745051959999998 
		242 -6.2745051959999998 275 -6.2745051959999998 290 -6.2745051959999998 300 -6.2745051959999998 
		350 -6.2745051959999998 360 -6.2745051959999998 370 -6.2745051959999998 380 -6.2745051959999998 
		400 -6.2745051959999998 420 -6.2745051959999998 428 -6.2745051959999998 441 -6.2745051959999998 
		450 -6.2745051959999998 464 -6.2745051959999998 480 -6.2745051959999998 492 -6.2745051959999998 
		504 -6.2745051959999998 510 -6.2745051959999998 620 -6.2745051959999998 626 -6.2745051959999998 
		630 -6.2745051959999998 638 -6.2745051959999998 670 -6.2745051959999998 680 -6.2745051959999998 
		690 -6.2745051959999998 706 -6.2745051959999998 720 -6.2745051959999998 750 -6.2745051959999998 
		760 -6.2745051959999998 790 -6.2745051959999998 800 -6.2745051959999998 810 -6.2745051959999998 
		821 -6.2745051959999998 830 -6.2745051959999998 837 -6.2745051959999998 843 -6.2745051959999998 
		850 -6.2745051959999998 860 -6.2745051959999998 875 -6.2745051959999998 890 -6.2745051959999998 
		905 -6.2745051959999998 912 -6.2745051959999998 920 -6.2745051959999998 930 -6.2745051959999998 
		937 -6.2745051959999998 950 -6.2745051959999998 970 -6.2745051959999998;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3372";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3373";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3374";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1751";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.99999999999999978 50 0.99999999999999978 
		65 0.99999999999999978 81 0.99999999999999978 140 0.99999999999999978 150 0.99999999999999978 
		160 0.99999999999999978 168 0.99999999999999978 178 0.99999999999999978 230 0.99999999999999978 
		242 0.99999999999999978 275 0.99999999999999978 290 0.99999999999999978 300 0.99999999999999978 
		350 0.99999999999999978 360 0.99999999999999978 370 0.99999999999999978 380 0.99999999999999978 
		400 0.99999999999999978 420 0.99999999999999978 428 0.99999999999999978 441 0.99999999999999978 
		450 0.99999999999999978 464 0.99999999999999978 480 0.99999999999999978 492 0.99999999999999978 
		504 0.99999999999999978 510 0.99999999999999978 620 0.99999999999999978 626 0.99999999999999978 
		630 0.99999999999999978 638 0.99999999999999978 670 0.99999999999999978 680 0.99999999999999978 
		690 0.99999999999999978 706 0.99999999999999978 720 0.99999999999999978 750 0.99999999999999978 
		760 0.99999999999999978 790 0.99999999999999978 800 0.99999999999999978 810 0.99999999999999978 
		821 0.99999999999999978 830 0.99999999999999978 837 0.99999999999999978 843 0.99999999999999978 
		850 0.99999999999999978 860 0.99999999999999978 875 0.99999999999999978 890 0.99999999999999978 
		905 0.99999999999999978 912 0.99999999999999978 920 0.99999999999999978 930 0.99999999999999978 
		937 0.99999999999999978 950 0.99999999999999978 970 0.99999999999999978;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1752";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.99999999999999978 50 0.99999999999999978 
		65 0.99999999999999978 81 0.99999999999999978 140 0.99999999999999978 150 0.99999999999999978 
		160 0.99999999999999978 168 0.99999999999999978 178 0.99999999999999978 230 0.99999999999999978 
		242 0.99999999999999978 275 0.99999999999999978 290 0.99999999999999978 300 0.99999999999999978 
		350 0.99999999999999978 360 0.99999999999999978 370 0.99999999999999978 380 0.99999999999999978 
		400 0.99999999999999978 420 0.99999999999999978 428 0.99999999999999978 441 0.99999999999999978 
		450 0.99999999999999978 464 0.99999999999999978 480 0.99999999999999978 492 0.99999999999999978 
		504 0.99999999999999978 510 0.99999999999999978 620 0.99999999999999978 626 0.99999999999999978 
		630 0.99999999999999978 638 0.99999999999999978 670 0.99999999999999978 680 0.99999999999999978 
		690 0.99999999999999978 706 0.99999999999999978 720 0.99999999999999978 750 0.99999999999999978 
		760 0.99999999999999978 790 0.99999999999999978 800 0.99999999999999978 810 0.99999999999999978 
		821 0.99999999999999978 830 0.99999999999999978 837 0.99999999999999978 843 0.99999999999999978 
		850 0.99999999999999978 860 0.99999999999999978 875 0.99999999999999978 890 0.99999999999999978 
		905 0.99999999999999978 912 0.99999999999999978 920 0.99999999999999978 930 0.99999999999999978 
		937 0.99999999999999978 950 0.99999999999999978 970 0.99999999999999978;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1753";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.99999999999999978 50 0.99999999999999978 
		65 0.99999999999999978 81 0.99999999999999978 140 0.99999999999999978 150 0.99999999999999978 
		160 0.99999999999999978 168 0.99999999999999978 178 0.99999999999999978 230 0.99999999999999978 
		242 0.99999999999999978 275 0.99999999999999978 290 0.99999999999999978 300 0.99999999999999978 
		350 0.99999999999999978 360 0.99999999999999978 370 0.99999999999999978 380 0.99999999999999978 
		400 0.99999999999999978 420 0.99999999999999978 428 0.99999999999999978 441 0.99999999999999978 
		450 0.99999999999999978 464 0.99999999999999978 480 0.99999999999999978 492 0.99999999999999978 
		504 0.99999999999999978 510 0.99999999999999978 620 0.99999999999999978 626 0.99999999999999978 
		630 0.99999999999999978 638 0.99999999999999978 670 0.99999999999999978 680 0.99999999999999978 
		690 0.99999999999999978 706 0.99999999999999978 720 0.99999999999999978 750 0.99999999999999978 
		760 0.99999999999999978 790 0.99999999999999978 800 0.99999999999999978 810 0.99999999999999978 
		821 0.99999999999999978 830 0.99999999999999978 837 0.99999999999999978 843 0.99999999999999978 
		850 0.99999999999999978 860 0.99999999999999978 875 0.99999999999999978 890 0.99999999999999978 
		905 0.99999999999999978 912 0.99999999999999978 920 0.99999999999999978 930 0.99999999999999978 
		937 0.99999999999999978 950 0.99999999999999978 970 0.99999999999999978;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3375";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 -5.7226119337660339 81 -5.7226119337660339 
		140 -5.7226119337660339 150 -5.7226119337660339 160 -5.7226119337660339 168 -5.7226119337660339 
		178 -5.7226119337660339 230 -5.7226119337660339 242 -5.7226119337660339 275 -5.7226119337660339 
		290 -5.7226119337660339 300 -5.7226119337660339 350 -5.7226119337660339 360 -5.7226119337660339 
		370 -5.7226119337660339 380 -5.7226119337660339 400 -5.7226119337660339 420 -5.7226119337660339 
		428 -5.7226119337660339 441 -5.7226119337660339 450 -5.7226119337660339 464 -5.7226119337660339 
		480 -5.7226119337660339 492 -5.7226119337660339 504 -5.7226119337660339 510 -5.7226119337660339 
		620 -5.7226119337660339 626 -5.7226119337660339 630 -5.7226119337660339 638 -5.7226119337660339 
		670 -5.7226119337660339 680 -5.7226119337660339 690 -5.7226119337660339 706 -5.7226119337660339 
		720 11.941938331565384 750 -5.7226119337660339 760 -5.7226119337660339 790 -5.7226119337660339 
		800 -5.7226119337660339 810 -5.7226119337660339 821 -5.7226119337660339 830 -5.7226119337660339 
		837 -5.7226119337660339 843 -5.7226119337660339 850 -5.7226119337660339 860 -5.7226119337660339 
		875 -5.7226119337660339 890 -5.7226119337660339 905 -5.7226119337660339 912 -5.7226119337660339 
		920 -5.7226119337660339 930 -2.8384270857483247 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3376";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 -0.69824840658652454 81 -0.69824840658652454 
		140 -0.69824840658652454 150 -0.69824840658652454 160 -0.69824840658652454 168 -0.69824840658652454 
		178 -0.69824840658652454 230 -0.69824840658652454 242 -0.69824840658652454 275 -0.69824840658652454 
		290 -0.69824840658652454 300 -0.69824840658652454 350 -0.69824840658652454 360 -0.69824840658652454 
		370 -0.69824840658652454 380 -0.69824840658652454 400 -0.69824840658652454 420 -0.69824840658652454 
		428 -0.69824840658652454 441 -0.69824840658652454 450 -0.69824840658652454 464 -0.69824840658652454 
		480 -0.69824840658652454 492 -0.69824840658652454 504 -0.69824840658652454 510 -0.69824840658652454 
		620 -0.69824840658652454 626 -0.69824840658652454 630 -0.69824840658652454 638 -0.69824840658652454 
		670 -0.69824840658652454 680 -0.69824840658652454 690 -0.69824840658652454 706 -0.69824840658652454 
		720 4.3378992258930946 750 -0.69824840658652454 760 -0.69824840658652454 790 -0.69824840658652454 
		800 -0.69824840658652454 810 -0.69824840658652454 821 -0.69824840658652454 830 -0.69824840658652454 
		837 -0.69824840658652454 843 -0.69824840658652454 850 -0.69824840658652454 860 -0.69824840658652454 
		875 -0.69824840658652454 890 -0.69824840658652454 905 -0.69824840658652454 912 -0.69824840658652454 
		920 -0.69824840658652454 930 -0.2457849733566537 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3377";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 1.6090787096072037 81 1.6090787096072037 
		140 1.6090787096072037 150 1.6090787096072037 160 1.6090787096072037 168 1.6090787096072037 
		178 1.6090787096072037 230 1.6090787096072037 242 1.6090787096072037 275 1.6090787096072037 
		290 1.6090787096072037 300 1.6090787096072037 350 1.6090787096072037 360 1.6090787096072037 
		370 1.6090787096072037 380 1.6090787096072037 400 1.6090787096072037 420 1.6090787096072037 
		428 1.6090787096072037 441 1.6090787096072037 450 1.6090787096072037 464 1.6090787096072037 
		480 1.6090787096072037 492 1.6090787096072037 504 1.6090787096072037 510 1.6090787096072037 
		620 1.6090787096072037 626 1.6090787096072037 630 1.6090787096072037 638 1.6090787096072037 
		670 1.6090787096072037 680 1.6090787096072037 690 1.6090787096072037 706 1.6090787096072037 
		720 63.331878193626714 750 1.6090787096072037 760 1.6090787096072037 790 1.6090787096072037 
		800 1.6090787096072037 810 1.6090787096072037 821 1.6090787096072037 830 1.6090787096072037 
		837 1.6090787096072037 843 1.6090787096072037 850 1.6090787096072037 860 1.6090787096072037 
		875 1.6090787096072037 890 1.6090787096072037 905 1.6090787096072037 912 1.6090787096072037 
		920 1.6090787096072037 930 0.56639924135732 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3378";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3379";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3380";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1754";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 1.0000000000000007 50 1.0000000000000007 
		65 1.0000000000000007 81 1.0000000000000007 140 1.0000000000000007 150 1.0000000000000007 
		160 1.0000000000000007 168 1.0000000000000007 178 1.0000000000000007 230 1.0000000000000007 
		242 1.0000000000000007 275 1.0000000000000007 290 1.0000000000000007 300 1.0000000000000007 
		350 1.0000000000000007 360 1.0000000000000007 370 1.0000000000000007 380 1.0000000000000007 
		400 1.0000000000000007 420 1.0000000000000007 428 1.0000000000000007 441 1.0000000000000007 
		450 1.0000000000000007 464 1.0000000000000007 480 1.0000000000000007 492 1.0000000000000007 
		504 1.0000000000000007 510 1.0000000000000007 620 1.0000000000000007 626 1.0000000000000007 
		630 1.0000000000000007 638 1.0000000000000007 670 1.0000000000000007 680 1.0000000000000007 
		690 1.0000000000000007 706 1.0000000000000007 720 1.0000000000000007 750 1.0000000000000007 
		760 1.0000000000000007 790 1.0000000000000007 800 1.0000000000000007 810 1.0000000000000007 
		821 1.0000000000000007 830 1.0000000000000007 837 1.0000000000000007 843 1.0000000000000007 
		850 1.0000000000000007 860 1.0000000000000007 875 1.0000000000000007 890 1.0000000000000007 
		905 1.0000000000000007 912 1.0000000000000007 920 1.0000000000000007 930 1.0000000000000007 
		937 1.0000000000000007 950 1.0000000000000007 970 1.0000000000000007;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1755";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 1.0000000000000004 50 1.0000000000000004 
		65 1.0000000000000004 81 1.0000000000000004 140 1.0000000000000004 150 1.0000000000000004 
		160 1.0000000000000004 168 1.0000000000000004 178 1.0000000000000004 230 1.0000000000000004 
		242 1.0000000000000004 275 1.0000000000000004 290 1.0000000000000004 300 1.0000000000000004 
		350 1.0000000000000004 360 1.0000000000000004 370 1.0000000000000004 380 1.0000000000000004 
		400 1.0000000000000004 420 1.0000000000000004 428 1.0000000000000004 441 1.0000000000000004 
		450 1.0000000000000004 464 1.0000000000000004 480 1.0000000000000004 492 1.0000000000000004 
		504 1.0000000000000004 510 1.0000000000000004 620 1.0000000000000004 626 1.0000000000000004 
		630 1.0000000000000004 638 1.0000000000000004 670 1.0000000000000004 680 1.0000000000000004 
		690 1.0000000000000004 706 1.0000000000000004 720 1.0000000000000004 750 1.0000000000000004 
		760 1.0000000000000004 790 1.0000000000000004 800 1.0000000000000004 810 1.0000000000000004 
		821 1.0000000000000004 830 1.0000000000000004 837 1.0000000000000004 843 1.0000000000000004 
		850 1.0000000000000004 860 1.0000000000000004 875 1.0000000000000004 890 1.0000000000000004 
		905 1.0000000000000004 912 1.0000000000000004 920 1.0000000000000004 930 1.0000000000000004 
		937 1.0000000000000004 950 1.0000000000000004 970 1.0000000000000004;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1756";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 1.0000000000000002 50 1.0000000000000002 
		65 1.0000000000000002 81 1.0000000000000002 140 1.0000000000000002 150 1.0000000000000002 
		160 1.0000000000000002 168 1.0000000000000002 178 1.0000000000000002 230 1.0000000000000002 
		242 1.0000000000000002 275 1.0000000000000002 290 1.0000000000000002 300 1.0000000000000002 
		350 1.0000000000000002 360 1.0000000000000002 370 1.0000000000000002 380 1.0000000000000002 
		400 1.0000000000000002 420 1.0000000000000002 428 1.0000000000000002 441 1.0000000000000002 
		450 1.0000000000000002 464 1.0000000000000002 480 1.0000000000000002 492 1.0000000000000002 
		504 1.0000000000000002 510 1.0000000000000002 620 1.0000000000000002 626 1.0000000000000002 
		630 1.0000000000000002 638 1.0000000000000002 670 1.0000000000000002 680 1.0000000000000002 
		690 1.0000000000000002 706 1.0000000000000002 720 1.0000000000000002 750 1.0000000000000002 
		760 1.0000000000000002 790 1.0000000000000002 800 1.0000000000000002 810 1.0000000000000002 
		821 1.0000000000000002 830 1.0000000000000002 837 1.0000000000000002 843 1.0000000000000002 
		850 1.0000000000000002 860 1.0000000000000002 875 1.0000000000000002 890 1.0000000000000002 
		905 1.0000000000000002 912 1.0000000000000002 920 1.0000000000000002 930 1.0000000000000002 
		937 1.0000000000000002 950 1.0000000000000002 970 1.0000000000000002;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3381";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 12.976135011552399 81 12.976135011552399 
		140 12.976135011552399 150 12.976135011552399 160 12.976135011552399 168 12.976135011552399 
		178 12.976135011552399 230 12.976135011552399 242 12.976135011552399 275 12.976135011552399 
		290 12.976135011552399 300 12.976135011552399 350 12.976135011552399 360 12.976135011552399 
		370 12.976135011552399 380 12.976135011552399 400 12.976135011552399 420 12.976135011552399 
		428 12.976135011552399 441 12.976135011552399 450 12.976135011552399 464 12.976135011552399 
		480 12.976135011552399 492 12.976135011552399 504 12.976135011552399 510 12.976135011552399 
		620 12.976135011552399 626 12.976135011552399 630 12.976135011552399 638 12.976135011552399 
		670 12.976135011552399 680 12.976135011552399 690 12.976135011552399 706 12.976135011552399 
		720 12.976135011552399 750 12.976135011552399 760 12.976135011552399 790 12.976135011552399 
		800 12.976135011552399 810 12.976135011552399 821 12.976135011552399 830 12.976135011552399 
		837 12.976135011552399 843 12.976135011552399 850 12.976135011552399 860 12.976135011552399 
		875 12.976135011552399 890 12.976135011552399 905 12.976135011552399 912 12.976135011552399 
		920 12.976135011552399 930 6.436189083420282 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3382";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 -6.1290792055982282 81 -6.1290792055982282 
		140 -6.1290792055982282 150 -6.1290792055982282 160 -6.1290792055982282 168 -6.1290792055982282 
		178 -6.1290792055982282 230 -6.1290792055982282 242 -6.1290792055982282 275 -6.1290792055982282 
		290 -6.1290792055982282 300 -6.1290792055982282 350 -6.1290792055982282 360 -6.1290792055982282 
		370 -6.1290792055982282 380 -6.1290792055982282 400 -6.1290792055982282 420 -6.1290792055982282 
		428 -6.1290792055982282 441 -6.1290792055982282 450 -6.1290792055982282 464 -6.1290792055982282 
		480 -6.1290792055982282 492 -6.1290792055982282 504 -6.1290792055982282 510 -6.1290792055982282 
		620 -6.1290792055982282 626 -6.1290792055982282 630 -6.1290792055982282 638 -6.1290792055982282 
		670 -6.1290792055982282 680 -6.1290792055982282 690 -6.1290792055982282 706 -6.1290792055982282 
		720 -6.1290792055982282 750 -6.1290792055982282 760 -6.1290792055982282 790 -6.1290792055982282 
		800 -6.1290792055982282 810 -6.1290792055982282 821 -6.1290792055982282 830 -6.1290792055982282 
		837 -6.1290792055982282 843 -6.1290792055982282 850 -6.1290792055982282 860 -6.1290792055982282 
		875 -6.1290792055982282 890 -6.1290792055982282 905 -6.1290792055982282 912 -6.1290792055982282 
		920 -6.1290792055982282 930 -3.0400356182956103 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3383";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 -3.2589361381724546 81 -3.2589361381724546 
		140 -3.2589361381724546 150 -3.2589361381724546 160 -3.2589361381724546 168 -3.2589361381724546 
		178 -3.2589361381724546 230 -3.2589361381724546 242 -3.2589361381724546 275 -3.2589361381724546 
		290 -3.2589361381724546 300 -3.2589361381724546 350 -3.2589361381724546 360 -3.2589361381724546 
		370 -3.2589361381724546 380 -3.2589361381724546 400 -3.2589361381724546 420 -3.2589361381724546 
		428 -3.2589361381724546 441 -3.2589361381724546 450 -3.2589361381724546 464 -3.2589361381724546 
		480 -3.2589361381724546 492 -3.2589361381724546 504 -3.2589361381724546 510 -3.2589361381724546 
		620 -3.2589361381724546 626 -3.2589361381724546 630 -3.2589361381724546 638 -3.2589361381724546 
		670 -3.2589361381724546 680 -3.2589361381724546 690 -3.2589361381724546 706 -3.2589361381724546 
		720 -3.2589361381724546 750 -3.2589361381724546 760 -3.2589361381724546 790 -3.2589361381724546 
		800 -3.2589361381724546 810 -3.2589361381724546 821 -3.2589361381724546 830 -3.2589361381724546 
		837 -3.2589361381724546 843 -3.2589361381724546 850 -3.2589361381724546 860 -3.2589361381724546 
		875 -3.2589361381724546 890 -3.2589361381724546 905 -3.2589361381724546 912 -3.2589361381724546 
		920 -3.2589361381724546 930 -1.6164389203577325 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3384";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3385";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3386";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1757";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTU -n "animCurveTU1758";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU1759";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTA -n "animCurveTA3387";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -105.77848472630944;
createNode animCurveTA -n "animCurveTA3388";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -8.2096526943984909;
createNode animCurveTA -n "animCurveTA3389";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -8.1666847929670165;
createNode animCurveTA -n "animCurveTA3390";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3391";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3392";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1760";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU1761";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1762";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTA -n "animCurveTA3393";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 75.333348250175646;
createNode animCurveTA -n "animCurveTA3394";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3395";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3396";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3397";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3398";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1763";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTU -n "animCurveTU1764";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTU -n "animCurveTU1765";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTA -n "animCurveTA3399";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3400";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 23.040000415782014;
createNode animCurveTA -n "animCurveTA3401";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3402";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3403";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3404";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1766";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1767";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1768";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA3405";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3406";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3407";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3408";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3409";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3410";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1769";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 55 ".ktv[0:54]"  0 0.99999999999999967 50 0.99999999999999967 
		65 0.99999999999999967 81 0.99999999999999967 140 0.99999999999999967 150 0.99999999999999967 
		160 0.99999999999999967 168 0.99999999999999967 178 0.99999999999999967 230 0.99999999999999967 
		242 0.99999999999999967 275 0.99999999999999967 290 0.99999999999999967 300 0.99999999999999967 
		350 0.99999999999999967 360 0.99999999999999967 400 0.99999999999999967 411 0.99999999999999967 
		420 0.99999999999999967 428 0.99999999999999967 441 0.99999999999999967 450 0.99999999999999967 
		464 0.99999999999999967 480 0.99999999999999967 492 0.99999999999999967 510 0.99999999999999967 
		620 0.99999999999999967 626 0.99999999999999967 630 0.99999999999999967 638 0.99999999999999967 
		670 0.99999999999999967 680 0.99999999999999967 690 0.99999999999999967 706 0.99999999999999967 
		720 0.99999999999999967 750 0.99999999999999967 760 0.99999999999999967 790 0.99999999999999967 
		800 0.99999999999999967 810 0.99999999999999967 821 0.99999999999999967 830 0.99999999999999967 
		837 0.99999999999999967 843 0.99999999999999967 850 0.99999999999999967 860 0.99999999999999967 
		875 0.99999999999999967 890 0.99999999999999967 905 0.99999999999999967 912 0.99999999999999967 
		920 0.99999999999999967 930 0.99999999999999967 937 0.99999999999999967 950 0.99999999999999967 
		970 0.99999999999999967;
	setAttr -s 55 ".kit[33:54]"  9 10 10 9 9 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 55 ".kot[33:54]"  9 10 10 9 9 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 55 ".kix[54]"  1;
	setAttr -s 55 ".kiy[54]"  0;
	setAttr -s 55 ".kox[54]"  1;
	setAttr -s 55 ".koy[54]"  0;
createNode animCurveTU -n "animCurveTU1770";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 55 ".ktv[0:54]"  0 0.99999999999999944 50 0.99999999999999944 
		65 0.99999999999999944 81 0.99999999999999944 140 0.99999999999999944 150 0.99999999999999944 
		160 0.99999999999999944 168 0.99999999999999944 178 0.99999999999999944 230 0.99999999999999944 
		242 0.99999999999999944 275 0.99999999999999944 290 0.99999999999999944 300 0.99999999999999944 
		350 0.99999999999999944 360 0.99999999999999944 400 0.99999999999999944 411 0.99999999999999944 
		420 0.99999999999999944 428 0.99999999999999944 441 0.99999999999999944 450 0.99999999999999944 
		464 0.99999999999999944 480 0.99999999999999944 492 0.99999999999999944 510 0.99999999999999944 
		620 0.99999999999999944 626 0.99999999999999944 630 0.99999999999999944 638 0.99999999999999944 
		670 0.99999999999999944 680 0.99999999999999944 690 0.99999999999999944 706 0.99999999999999944 
		720 0.99999999999999944 750 0.99999999999999944 760 0.99999999999999944 790 0.99999999999999944 
		800 0.99999999999999944 810 0.99999999999999944 821 0.99999999999999944 830 0.99999999999999944 
		837 0.99999999999999944 843 0.99999999999999944 850 0.99999999999999944 860 0.99999999999999944 
		875 0.99999999999999944 890 0.99999999999999944 905 0.99999999999999944 912 0.99999999999999944 
		920 0.99999999999999944 930 0.99999999999999944 937 0.99999999999999944 950 0.99999999999999944 
		970 0.99999999999999944;
	setAttr -s 55 ".kit[33:54]"  9 10 10 9 9 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 55 ".kot[33:54]"  9 10 10 9 9 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 55 ".kix[54]"  1;
	setAttr -s 55 ".kiy[54]"  0;
	setAttr -s 55 ".kox[54]"  1;
	setAttr -s 55 ".koy[54]"  0;
createNode animCurveTU -n "animCurveTU1771";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 55 ".ktv[0:54]"  0 0.99999999999999989 50 0.99999999999999989 
		65 0.99999999999999989 81 0.99999999999999989 140 0.99999999999999989 150 0.99999999999999989 
		160 0.99999999999999989 168 0.99999999999999989 178 0.99999999999999989 230 0.99999999999999989 
		242 0.99999999999999989 275 0.99999999999999989 290 0.99999999999999989 300 0.99999999999999989 
		350 0.99999999999999989 360 0.99999999999999989 400 0.99999999999999989 411 0.99999999999999989 
		420 0.99999999999999989 428 0.99999999999999989 441 0.99999999999999989 450 0.99999999999999989 
		464 0.99999999999999989 480 0.99999999999999989 492 0.99999999999999989 510 0.99999999999999989 
		620 0.99999999999999989 626 0.99999999999999989 630 0.99999999999999989 638 0.99999999999999989 
		670 0.99999999999999989 680 0.99999999999999989 690 0.99999999999999989 706 0.99999999999999989 
		720 0.99999999999999989 750 0.99999999999999989 760 0.99999999999999989 790 0.99999999999999989 
		800 0.99999999999999989 810 0.99999999999999989 821 0.99999999999999989 830 0.99999999999999989 
		837 0.99999999999999989 843 0.99999999999999989 850 0.99999999999999989 860 0.99999999999999989 
		875 0.99999999999999989 890 0.99999999999999989 905 0.99999999999999989 912 0.99999999999999989 
		920 0.99999999999999989 930 0.99999999999999989 937 0.99999999999999989 950 0.99999999999999989 
		970 0.99999999999999989;
	setAttr -s 55 ".kit[33:54]"  9 10 10 9 9 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 55 ".kot[33:54]"  9 10 10 9 9 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 55 ".kix[54]"  1;
	setAttr -s 55 ".kiy[54]"  0;
	setAttr -s 55 ".kox[54]"  1;
	setAttr -s 55 ".koy[54]"  0;
createNode animCurveTA -n "animCurveTA3411";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 58 ".ktv[0:57]"  0 2.1419574297606134 50 2.1419574297606134 
		65 1.2873436167320449 81 1.2873436167320449 140 1.2873436167320449 150 -3.1685111274198374 
		160 12.181459178374276 168 10.814507846065339 178 14.928234529312936 230 14.928234529312936 
		242 2.7991058194807295 275 8.6834482742648333 290 24.899442345975807 300 22.293314899751223 
		350 22.293314899751223 360 20.025132904758088 400 20.025132904758088 411 24.525164775761304 
		420 4.5434961754841856 428 4.6122695351930716 441 4.735625906510796 450 4.735625906510796 
		464 4.735625906510796 480 6.7804415727059331 492 1.3659693571406655 499 6.3488082318898176 
		510 1.3659693571406655 620 1.3659693571406655 626 -1.8429220602337937 630 1.0443494774535591 
		638 15.690501267301105 670 10.683258160057536 680 10.683258160057536 690 10.683258160057536 
		706 10.683258160057536 720 -4.411021212433484 750 -2.9656975770955292 760 2.2420894844366104 
		770 11.017606192403111 790 11.389169136780145 795 11.933064424330038 800 8.0482400982988889 
		810 13.368593567059209 821 20.228342537761936 830 20.228342537761936 837 20.228342537761936 
		843 20.228342537761936 850 20.228342537761936 860 20.228342537761936 875 11.017606192403111 
		890 2.0557829179777736 905 2.6415226002960925 912 2.6415226002960925 920 2.6415226002960925 
		930 2.3178054674671769 937 2.1419574297606134 950 2.1419574297606134 970 2.1419574297606134;
	setAttr -s 58 ".kit[34:57]"  9 10 10 9 9 9 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kot[34:57]"  9 10 10 9 9 9 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kix[57]"  1;
	setAttr -s 58 ".kiy[57]"  0;
	setAttr -s 58 ".kox[57]"  1;
	setAttr -s 58 ".koy[57]"  0;
createNode animCurveTA -n "animCurveTA3412";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 58 ".ktv[0:57]"  0 0 50 0 65 0.25264255732020968 81 0.25264255732020968 
		140 0.25264255732020968 150 0.96074116763528583 160 0.19499493493095993 168 0.20387669322430957 
		178 0.18099682779585932 230 0.18099682779585932 242 0.24533707097337457 275 3.1567256020302401 
		290 0.12191094258439723 300 0.13778432601650323 350 0.13778432601650323 360 0.73611538648522801 
		400 0.73611538648522801 411 0.54437687449281424 420 0 428 4.1902029993145922 441 
		0.46433103866621617 450 0.46433103866621617 464 0.46433103866621617 480 -5.8020292253638273 
		492 0.15833753449230811 499 -0.24286343688745757 510 0.15833753449230811 620 0.15833753449230814 
		626 -0.15074102128643396 630 -0.50778402714698301 638 0.29906007241587224 670 -0.19976173704713862 
		680 -0.19976173704713862 690 -0.19976173704713862 706 -0.19976173704713862 720 0.391075756074593 
		750 0.59703779123450851 760 0.2772655035145275 770 0.12169067621121535 790 1.4296706891423354 
		795 3.2037426740649901 800 -6.533237032903652 810 -6.9651726891097567 821 -3.9028097961059292 
		830 -3.9028097961059292 837 -3.9028097961059292 843 -3.9028097961059292 850 -3.9028097961059292 
		860 -3.9028097961059292 875 0.12169067621121535 890 -0.36495683962044739 905 0.13075614013775494 
		912 0.13075614013775494 920 0.13075614013775494 930 0.046026448634644383 937 0 950 
		0 970 0;
	setAttr -s 58 ".kit[34:57]"  9 10 10 9 9 9 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kot[34:57]"  9 10 10 9 9 9 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kix[57]"  1;
	setAttr -s 58 ".kiy[57]"  0;
	setAttr -s 58 ".kox[57]"  1;
	setAttr -s 58 ".koy[57]"  0;
createNode animCurveTA -n "animCurveTA3413";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 58 ".ktv[0:57]"  0 0 50 0 65 0.27357728321208158 81 0.27357728321208158 
		140 0.27357728321208158 150 0.32247813031482353 160 0.31415581513785606 168 0.31161997752217024 
		178 0.32544247913138752 230 0.32544247913138752 242 0.28014729670640881 275 0.059863269762357035 
		290 0.35186675817175733 300 0.34595955949978752 350 0.34595955949978752 360 -1.7420722879309647 
		400 -1.7420722879309647 411 -0.77320079941719289 420 0 428 1.1306369647856387 441 
		-1.3654792820938326 450 -1.3654792820938326 464 -1.3654792820938326 480 -3.6329086207885264 
		492 -5.5001817688223644 499 -5.4117751640020648 510 -5.5001817688223644 620 -5.5001817688223644 
		626 -5.5003945493148674 630 -5.570904735299421 638 -5.6832541615709218 670 -5.6875959495477151 
		680 -5.6875959495477151 690 -5.6875959495477151 706 -5.6875959495477151 720 0.95951626894352227 
		750 1.2395988114210534 760 0.99836318075465924 770 1.0289754083372953 790 -6.4746268941999654 
		795 -3.6022977377404777 800 3.0386711052093083 810 -3.1487894246616035 821 -5.5679712246119379 
		830 -2.1109754288418952 837 -5.5679712246119379 843 -2.1109754288418952 850 -5.5679712246119379 
		860 -2.1109754288418952 875 1.0289754083372953 890 -3.5180839577785652 905 4.0906840405621248 
		912 4.0906840405621248 920 4.0906840405621248 930 2.0289875017808456 937 0 950 0 
		970 0;
	setAttr -s 58 ".kit[34:57]"  9 10 10 9 9 9 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kot[34:57]"  9 10 10 9 9 9 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kix[57]"  1;
	setAttr -s 58 ".kiy[57]"  0;
	setAttr -s 58 ".kox[57]"  1;
	setAttr -s 58 ".koy[57]"  0;
createNode animCurveTA -n "animCurveTA3414";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3415";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3416";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1772";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 54 ".ktv[0:53]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 400 1 420 1 428 1 441 1 450 1 464 
		1 480 1 492 1 510 1 620 1 626 1 630 1 638 1 670 1 680 1 690 1 706 1 720 1 750 1 760 
		1 790 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 1 890 1 905 1 912 1 920 
		1 930 1 937 1 950 1 970 1;
	setAttr -s 54 ".kit[32:53]"  9 10 10 9 9 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 54 ".kot[32:53]"  9 10 10 9 9 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 54 ".kix[53]"  1;
	setAttr -s 54 ".kiy[53]"  0;
	setAttr -s 54 ".kox[53]"  1;
	setAttr -s 54 ".koy[53]"  0;
createNode animCurveTU -n "animCurveTU1773";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 54 ".ktv[0:53]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 400 1 420 1 428 1 441 1 450 1 464 
		1 480 1 492 1 510 1 620 1 626 1 630 1 638 1 670 1 680 1 690 1 706 1 720 1 750 1 760 
		1 790 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 1 890 1 905 1 912 1 920 
		1 930 1 937 1 950 1 970 1;
	setAttr -s 54 ".kit[32:53]"  9 10 10 9 9 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 54 ".kot[32:53]"  9 10 10 9 9 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 54 ".kix[53]"  1;
	setAttr -s 54 ".kiy[53]"  0;
	setAttr -s 54 ".kox[53]"  1;
	setAttr -s 54 ".koy[53]"  0;
createNode animCurveTU -n "animCurveTU1774";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 54 ".ktv[0:53]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 400 1 420 1 428 1 441 1 450 1 464 
		1 480 1 492 1 510 1 620 1 626 1 630 1 638 1 670 1 680 1 690 1 706 1 720 1 750 1 760 
		1 790 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 1 890 1 905 1 912 1 920 
		1 930 1 937 1 950 1 970 1;
	setAttr -s 54 ".kit[32:53]"  9 10 10 9 9 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 54 ".kot[32:53]"  9 10 10 9 9 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 54 ".kix[53]"  1;
	setAttr -s 54 ".kiy[53]"  0;
	setAttr -s 54 ".kox[53]"  1;
	setAttr -s 54 ".koy[53]"  0;
createNode animCurveTA -n "animCurveTA3417";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 58 ".ktv[0:57]"  0 4.3363032611727439 50 4.3363032611727439 
		65 3.1815961039464042 81 3.1815961039464042 140 3.1815961039464042 150 -1.8840882189500545 
		160 23.129979916874571 168 5.4675502505525122 178 12.486701932756091 230 10.588362002369072 
		242 3.8920128904824782 275 10.888947416958858 290 27.329588610207125 300 23.159249217780548 
		350 20.440588563261514 360 21.820818208706203 400 19.308854425718131 411 20.987685826810896 
		420 10.96945803147468 428 2.3670847628326599 441 -3.4492201412068613 450 -3.4492201412068617 
		464 -3.4492201412068617 480 4.062553267663394 492 3.6021059259653994 499 7.1316806652709781 
		510 3.6021059259653994 620 3.6021059259653985 626 0.99685906509209865 630 3.3925400524761962 
		638 18.972417077329027 670 13.060906072081453 680 13.060906072081453 690 13.060906072081453 
		706 13.060906072081453 720 -1.3304432385270402 750 -1.1921143781897805 760 3.4149404455446257 
		770 14.121194864490887 790 14.74955580438899 795 13.335566106006038 800 -4.1388810021994873 
		810 0.23083346035536065 821 0.23083346035536065 830 0.23083346035536065 837 0.23083346035536065 
		843 0.23083346035536065 850 0.23083346035536065 860 0.23083346035536065 875 14.121194864490887 
		890 12.342921359202929 905 3.4630338549679798 912 3.4630338549679798 920 3.4630338549679802 
		930 4.0289105113825991 937 4.3363032611727439 950 4.3363032611727439 970 4.3363032611727439;
	setAttr -s 58 ".kit[9:57]"  1 10 10 10 10 10 10 1 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		9 10 10 9 9 9 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 58 ".kot[9:57]"  1 10 10 10 10 10 10 1 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		9 10 10 9 9 9 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 58 ".kix[9:57]"  0.99959444999694824 0.99999392032623291 
		0.96883749961853027 0.96852898597717285 1 1 1 0.99814301729202271 1 0.86746317148208618 
		0.94103574752807617 1 1 1 1 1 1 1 1 1 1 0.99208635091781616 1 1 1 0.96987342834472656 
		1 1 0.92818772792816162 0.98098856210708618 0.99986469745635986 1 0.90937173366546631 
		1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 58 ".kiy[9:57]"  -0.028476482257246971 0.0034974478185176849 
		0.24769710004329681 0.24890100955963135 0 0 0 -0.060914561152458191 0 -0.49750158190727234 
		-0.33830702304840088 0 0 0 0 0 0 0 0 0 0 0.12555702030658722 0 0 0 -0.24360933899879456 
		0 0 0.3721122145652771 0.1940653920173645 -0.016451932489871979 0 -0.41598436236381531 
		0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 58 ".kox[9:57]"  0.99959444999694824 0.99999392032623291 
		0.96883749961853027 0.96852898597717285 1 1 1 0.99814301729202271 1 0.86746317148208618 
		0.94103574752807617 1 1 1 1 1 1 1 1 1 1 0.99208635091781616 1 1 1 0.96987342834472656 
		1 1 0.92818772792816162 0.98098856210708618 0.99986469745635986 1 0.90937173366546631 
		1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 58 ".koy[9:57]"  -0.028476478531956673 0.0034974478185176849 
		0.24769710004329681 0.24890100955963135 0 0 0 -0.060914561152458191 0 -0.49750158190727234 
		-0.33830702304840088 0 0 0 0 0 0 0 0 0 0 0.12555702030658722 0 0 0 -0.24360933899879456 
		0 0 0.3721122145652771 0.1940653920173645 -0.016451932489871979 0 -0.41598436236381531 
		0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA3418";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 58 ".ktv[0:57]"  0 0 50 0 65 0.3066118020881663 81 0.3066118020881663 
		140 0.3066118020881663 150 0.49274439062803027 160 0.4003746301468542 168 0.31963524988824327 
		178 0.35636014977388736 230 0.34693321342045869 242 2.779874608867233 275 10.883347575828889 
		290 0.41585624528852538 300 0.40180452533271849 350 0.39149337352052921 360 -1.8424771251040568 
		400 0.49733597751358977 411 2.0907908445682541 420 3.9016386345704572 428 2.8253643035201002 
		441 1.0424072212942355 450 1.0424072212942355 464 1.0424072212942355 480 0.73597169473989255 
		492 -0.27364057189968716 499 -0.92804542511007804 510 -0.27364057189968716 620 -0.27364057189968705 
		626 -0.54327611881423177 630 -2.3964658681518882 638 -3.6288479478174565 670 -3.8536139795411004 
		680 -3.8536139795411004 690 -3.8536139795411004 706 -3.8536139795411004 720 -0.56112008295018989 
		750 0.98226721297093622 760 1.8527521823178161 770 0.94518082431427941 790 2.1467974327641679 
		795 3.2141610842308146 800 2.9125438365271448 810 2.536944933840259 821 2.536944933840259 
		830 2.536944933840259 837 2.536944933840259 843 2.536944933840259 850 2.536944933840259 
		860 2.536944933840259 875 0.94518082431427941 890 0.86686958154306815 905 2.8318191230284739 
		912 2.8318191230284739 920 2.8318191230284739 930 0.99680655356879388 937 0 950 0 
		970 0;
	setAttr -s 58 ".kit[16:57]"  1 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 9 10 10 9 9 9 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kot[16:57]"  1 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 9 10 10 9 9 9 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kix[16:57]"  0.99908030033111572 1 1 1 1 1 1 1 1 1 1 
		1 1 1 1 1 1 1 0.99835300445556641 1 1 0.9999995231628418 0.99998688697814941 0.99887269735336304 
		1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 58 ".kiy[16:57]"  0.042879126965999603 0 0 0 0 0 0 0 0 0 
		0 0 0 0 0 0 0 0 0.057370215654373169 0 0 -0.00097091984935104847 0.0051319901831448078 
		0.047467805445194244 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 58 ".kox[16:57]"  0.99908030033111572 1 1 1 1 1 1 1 1 1 1 
		1 1 1 1 1 1 1 0.99835300445556641 1 1 0.9999995231628418 0.99998688697814941 0.99887269735336304 
		1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 58 ".koy[16:57]"  0.042879130691289902 0 0 0 0 0 0 0 0 0 
		0 0 0 0 0 0 0 0 0.057370215654373169 0 0 -0.00097091984935104847 0.0051319901831448078 
		0.047467805445194244 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA3419";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 58 ".ktv[0:57]"  0 0 50 0 65 -0.33262850584931353 81 -0.33262850584931353 
		140 -0.33262850584931353 150 -1.8534258233261456 160 -0.20737850315309778 168 -0.32013408773639901 
		178 -0.27867527514572871 230 -0.29032712497783419 242 -18.412595677224864 275 -18.328370105121074 
		290 -0.17808875342045141 300 -0.20785883578769221 350 -0.22668304325277086 360 1.5755051361370758 
		400 -0.63658303019159612 411 2.5830767215953112 420 4.7582496739995994 428 2.5339472972143677 
		441 -7.3571699812551428 450 -7.3571699812551428 464 -7.3571699812551428 480 -6.5319049122476578 
		492 -5.9173306523064459 499 -5.8711034433815303 510 -5.9173306523064459 620 -5.9173306523064459 
		626 -5.8987549014312224 630 -3.7599366477055978 638 -2.3731825906852801 670 -1.9871122633972662 
		680 -1.9871122633972662 690 -1.9871122633972662 706 -1.9871122633972662 720 -0.30051087966277695 
		750 2.1348106654551029 760 4.7016565981793761 770 4.963811632148305 790 0.75974648447758175 
		795 2.6067945875227796 800 -13.858547423399765 810 -12.850673636488038 821 -18.716728667598538 
		830 -12.850673636488038 837 -18.716728667598538 843 -12.850673636488038 850 -18.716728667598538 
		860 -12.850673636488038 875 4.963811632148305 890 3.8899880991351914 905 6.590399683434061 
		912 6.590399683434061 920 6.590399683434061 930 3.2688515270176048 937 0 950 0 970 
		0;
	setAttr -s 58 ".kit[34:57]"  9 10 10 9 9 9 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kot[34:57]"  9 10 10 9 9 9 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kix[57]"  1;
	setAttr -s 58 ".kiy[57]"  0;
	setAttr -s 58 ".kox[57]"  1;
	setAttr -s 58 ".koy[57]"  0;
createNode animCurveTA -n "animCurveTA3420";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3421";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3422";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1775";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 58 ".ktv[0:57]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 400 1 411 1 420 1 428 1 441 1 450 
		1 464 1 480 1 492 1 499 1 510 1 620 1 626 1 630 1 638 1 670 1 680 1 690 1 706 1 720 
		1 750 1 760 1 770 1 790 1 795 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 
		1 890 1 905 1 912 1 920 1 930 1 937 1 950 1 970 1;
	setAttr -s 58 ".kit[34:57]"  9 10 10 9 9 9 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kot[34:57]"  9 10 10 9 9 9 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kix[57]"  1;
	setAttr -s 58 ".kiy[57]"  0;
	setAttr -s 58 ".kox[57]"  1;
	setAttr -s 58 ".koy[57]"  0;
createNode animCurveTU -n "animCurveTU1776";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 58 ".ktv[0:57]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 400 1 411 1 420 1 428 1 441 1 450 
		1 464 1 480 1 492 1 499 1 510 1 620 1 626 1 630 1 638 1 670 1 680 1 690 1 706 1 720 
		1 750 1 760 1 770 1 790 1 795 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 
		1 890 1 905 1 912 1 920 1 930 1 937 1 950 1 970 1;
	setAttr -s 58 ".kit[34:57]"  9 10 10 9 9 9 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kot[34:57]"  9 10 10 9 9 9 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kix[57]"  1;
	setAttr -s 58 ".kiy[57]"  0;
	setAttr -s 58 ".kox[57]"  1;
	setAttr -s 58 ".koy[57]"  0;
createNode animCurveTU -n "animCurveTU1777";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 58 ".ktv[0:57]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 400 1 411 1 420 1 428 1 441 1 450 
		1 464 1 480 1 492 1 499 1 510 1 620 1 626 1 630 1 638 1 670 1 680 1 690 1 706 1 720 
		1 750 1 760 1 770 1 790 1 795 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 
		1 890 1 905 1 912 1 920 1 930 1 937 1 950 1 970 1;
	setAttr -s 58 ".kit[34:57]"  9 10 10 9 9 9 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kot[34:57]"  9 10 10 9 9 9 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kix[57]"  1;
	setAttr -s 58 ".kiy[57]"  0;
	setAttr -s 58 ".kox[57]"  1;
	setAttr -s 58 ".koy[57]"  0;
createNode animCurveTA -n "animCurveTA3423";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 58 ".ktv[0:57]"  0 3.7846242423372511 50 3.7846242423372511 
		65 3.7846242423372511 81 3.7846242423372511 140 3.7846242423372511 150 -1.0910069902198998 
		160 9.2314659990978036 168 1.8916481486151191 178 8.467427969527634 230 6.9621777429120124 
		242 1.8602506946196566 275 1.8602506946196571 290 6.056751628799022 300 6.056751628799022 
		350 5.0197586094998918 360 5.367561627503215 400 2.5272340217487819 411 10.163038386690529 
		420 3.375754157919197 428 2.8545135138316122 441 -6.7458145630565323 450 -6.7458145630565332 
		464 -6.7458145630565332 480 5.334415006797772 492 -8.6110088914043779 499 -4.3433496357896777 
		510 -8.6110088914043779 620 -8.6110088914043779 626 -9.8054826286993126 630 -11.521013277964206 
		638 -0.34796165510121163 670 -4.518452559794695 680 -7.4630195995221777 690 -7.4630195995221777 
		706 -7.4630195995221777 720 5.0518538769321069 750 -0.087804422099993465 760 -0.27454674158051007 
		770 9.0852887074167796 790 8.1979107631009995 795 8.0991199241906155 800 -2.0701420186255493 
		810 -1.9752296121920931 821 -1.9752296121920987 830 -1.9752296121920931 837 -1.9752296121920987 
		843 -1.9752296121920931 850 -1.9752296121920987 860 -1.9752296121920931 875 9.0852887074167796 
		890 9.0852887074167796 905 -0.2610507069522191 912 -0.26105070695221916 920 -0.26105070695221927 
		930 1.7779612963163069 937 3.7846242423372511 950 3.7846242423372511 970 3.7846242423372511;
	setAttr -s 58 ".kit[34:57]"  9 10 10 9 9 9 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kot[34:57]"  9 10 10 9 9 9 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kix[57]"  1;
	setAttr -s 58 ".kiy[57]"  0;
	setAttr -s 58 ".kox[57]"  1;
	setAttr -s 58 ".koy[57]"  0;
createNode animCurveTA -n "animCurveTA3424";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 58 ".ktv[0:57]"  0 0 50 0 65 0 81 0 140 0 150 0.45015067389326086 
		160 0.078883288043935615 168 -0.047601687603267641 178 0.092105775338567661 230 0.060166203411555097 
		242 -1.5453977912452335 275 -1.5453977912452335 290 0 300 0 350 0 360 -11.566282287113008 
		400 -10.729157618979769 411 -0.87444063671978056 420 1.9687512984021647 428 -3.0478272785170426 
		441 1.5162473310891855 450 1.5162473310891855 464 1.5162473310891855 480 1.5618370673274473 
		492 1.6108081686973259 499 0.38546581552682424 510 1.6108081686973259 620 1.6108081686973259 
		626 1.5123472936116327 630 0.99354067969215498 638 0.68229367873827096 670 0.41215547043592232 
		680 -0.3293562671297553 690 -0.3293562671297553 706 -0.3293562671297553 720 -2.4851405110931242 
		750 -0.52232892446880985 760 0.80042384259007604 770 0.18901541403453653 790 2.2215951538083694 
		795 2.1607202685412701 800 -5.0422513306396253 810 -3.4183953186987432 821 -3.4183953186987464 
		830 -3.4183953186987432 837 -3.4183953186987464 843 -3.4183953186987432 850 -3.4183953186987464 
		860 -3.4183953186987432 875 0.18901541403453653 890 0.18901541403453653 905 -1.7706390229131721 
		912 -1.7706390229131721 920 -1.7706390229131721 930 -0.62326882663216931 937 0 950 
		0 970 0;
	setAttr -s 58 ".kit[16:57]"  1 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 9 10 10 9 9 9 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kot[16:57]"  1 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 9 10 10 9 9 9 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kix[16:57]"  0.99976640939712524 1 1 0.99993634223937988 
		1 1 1 1 1 1 1 1 1 1 1 1 1 1 0.99929285049438477 1 1 0.99982672929763794 0.99969255924224854 
		0.99914848804473877 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 58 ".kiy[16:57]"  0.021614182740449905 0 0 -0.011281690560281277 
		0 0 0 0 0 0 0 0 0 0 0 0 0 0 -0.037598926573991776 0 0 0.018619740381836891 0.024796493351459503 
		0.041260097175836563 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 58 ".kox[16:57]"  0.99976640939712524 1 1 0.99993634223937988 
		1 1 1 1 1 1 1 1 1 1 1 1 1 1 0.99929285049438477 1 1 0.99982672929763794 0.99969255924224854 
		0.99914848804473877 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 58 ".koy[16:57]"  0.021614177152514458 0 0 -0.011281690560281277 
		0 0 0 0 0 0 0 0 0 0 0 0 0 0 -0.037598926573991776 0 0 0.018619740381836891 0.024796493351459503 
		0.041260097175836563 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA3425";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 58 ".ktv[0:57]"  0 0 50 0 65 0 81 0 140 0 150 -0.90080210260350979 
		160 -0.60386125550615333 168 -1.2170517286121405 178 -1.2144950748071164 230 -1.21649540151497 
		242 -5.4115360521973148 275 -5.4115360521973148 290 0 300 0 350 0 360 12.58409851860122 
		400 9.5958595140523641 411 14.03413192062674 420 9.49519131010174 428 -2.6461523940604463 
		441 -4.5744720692094809 450 -4.5744720692094818 464 -4.5744720692094818 480 -5.3615843919456401 
		492 -4.6975531210836223 499 -4.582289016706329 510 -4.6975531210836223 620 -4.6975531210836223 
		626 -4.7301052719996219 630 -8.6179271634037473 638 -3.6846921429928381 670 -3.7245410609050476 
		680 0.35389538521213471 690 0.35389538521213471 706 0.35389538521213504 720 0.21884754843981755 
		750 1.3731428124223559 760 3.688727672336233 770 3.7697253855704655 790 1.3708264371279553 
		795 1.9008988193047669 800 6.6805885430168788 810 8.7970087157436687 821 4.356377106234123 
		830 8.7970087157436687 837 4.356377106234123 843 8.7970087157436687 850 4.356377106234123 
		860 8.7970087157436687 875 3.7697253855704655 890 3.7697253855704655 905 5.9745523697974416 
		912 5.9745523697974416 920 5.9745523697974416 930 2.9633899666101122 937 0 950 0 
		970 0;
	setAttr -s 58 ".kit[15:57]"  3 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 9 10 10 9 9 9 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		1;
	setAttr -s 58 ".kot[15:57]"  3 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 9 10 10 9 9 9 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		1;
	setAttr -s 58 ".kix[57]"  1;
	setAttr -s 58 ".kiy[57]"  0;
	setAttr -s 58 ".kox[57]"  1;
	setAttr -s 58 ".koy[57]"  0;
createNode animCurveTA -n "animCurveTA3426";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3427";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3428";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1778";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 370 1 380 1 400 1 420 1 428 1 441 
		1 450 1 464 1 480 1 492 1 504 1 510 1 620 1 626 1 630 1 638 1 670 1 680 1 690 1 706 
		1 720 1 750 1 760 1 790 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 1 890 
		1 905 1 912 1 920 1 930 1 937 1 950 1 970 1;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1779";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 1.0000000000000004 50 1.0000000000000004 
		65 1.0000000000000004 81 1.0000000000000004 140 1.0000000000000004 150 1.0000000000000004 
		160 1.0000000000000004 168 1.0000000000000004 178 1.0000000000000004 230 1.0000000000000004 
		242 1.0000000000000004 275 1.0000000000000004 290 1.0000000000000004 300 1.0000000000000004 
		350 1.0000000000000004 360 1.0000000000000004 370 1.0000000000000004 380 1.0000000000000004 
		400 1.0000000000000004 420 1.0000000000000004 428 1.0000000000000004 441 1.0000000000000004 
		450 1.0000000000000004 464 1.0000000000000004 480 1.0000000000000004 492 1.0000000000000004 
		504 1.0000000000000004 510 1.0000000000000004 620 1.0000000000000004 626 1.0000000000000004 
		630 1.0000000000000004 638 1.0000000000000004 670 1.0000000000000004 680 1.0000000000000004 
		690 1.0000000000000004 706 1.0000000000000004 720 1.0000000000000004 750 1.0000000000000004 
		760 1.0000000000000004 790 1.0000000000000004 800 1.0000000000000004 810 1.0000000000000004 
		821 1.0000000000000004 830 1.0000000000000004 837 1.0000000000000004 843 1.0000000000000004 
		850 1.0000000000000004 860 1.0000000000000004 875 1.0000000000000004 890 1.0000000000000004 
		905 1.0000000000000004 912 1.0000000000000004 920 1.0000000000000004 930 1.0000000000000004 
		937 1.0000000000000004 950 1.0000000000000004 970 1.0000000000000004;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1780";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 1.0000000000000002 50 1.0000000000000002 
		65 1.0000000000000002 81 1.0000000000000002 140 1.0000000000000002 150 1.0000000000000002 
		160 1.0000000000000002 168 1.0000000000000002 178 1.0000000000000002 230 1.0000000000000002 
		242 1.0000000000000002 275 1.0000000000000002 290 1.0000000000000002 300 1.0000000000000002 
		350 1.0000000000000002 360 1.0000000000000002 370 1.0000000000000002 380 1.0000000000000002 
		400 1.0000000000000002 420 1.0000000000000002 428 1.0000000000000002 441 1.0000000000000002 
		450 1.0000000000000002 464 1.0000000000000002 480 1.0000000000000002 492 1.0000000000000002 
		504 1.0000000000000002 510 1.0000000000000002 620 1.0000000000000002 626 1.0000000000000002 
		630 1.0000000000000002 638 1.0000000000000002 670 1.0000000000000002 680 1.0000000000000002 
		690 1.0000000000000002 706 1.0000000000000002 720 1.0000000000000002 750 1.0000000000000002 
		760 1.0000000000000002 790 1.0000000000000002 800 1.0000000000000002 810 1.0000000000000002 
		821 1.0000000000000002 830 1.0000000000000002 837 1.0000000000000002 843 1.0000000000000002 
		850 1.0000000000000002 860 1.0000000000000002 875 1.0000000000000002 890 1.0000000000000002 
		905 1.0000000000000002 912 1.0000000000000002 920 1.0000000000000002 930 1.0000000000000002 
		937 1.0000000000000002 950 1.0000000000000002 970 1.0000000000000002;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3429";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 58 ".ktv[0:57]"  0 3.0532774173010191 50 3.0532774173010191 
		65 3.0532774173010191 81 3.0532774173010191 140 3.0532774173010191 150 31.968681018863105 
		160 -5.7439101260375152 168 2.3791638215790525 178 -14.541088231023942 230 -14.541088231023942 
		242 2.7100154412860262 275 3.9098431075420277 290 -27.820295676282669 300 -23.953354746643811 
		350 -23.953354746643811 360 -29.683866289703289 370 -29.683866289703289 380 -29.683866289703289 
		400 -29.683866289703289 420 3.5941868910293779 428 1.8124932118179193 441 -2.1389533789446196 
		450 -2.1389533789446196 464 -2.1389533789446196 480 -1.5829949752016486 492 -1.1279875999740419 
		504 -1.1279875999740419 510 -1.1279875999740419 620 -1.1279875999740419 626 6.2339160253047803 
		630 13.344780211310846 638 -4.9824335209664872 670 -4.9824335209664872 680 -4.9824335209664872 
		690 -4.9824335209664872 706 -4.9824335209664872 720 -9.2792740437247527 750 -9.2792740437247527 
		760 -9.2792740437247527 770 -25.311947620345578 790 -25.311947620345578 800 7.5629197339001193 
		810 7.5629197339001193 821 3.6469602629707074 830 7.5629197339001193 837 3.6469602629707074 
		843 7.5629197339001193 850 3.6469602629707074 860 7.5629197339001193 875 -25.311947620345578 
		890 -5.4752052532307234 905 8.1817414880586909 912 8.1817414880586909 920 8.1817414880586909 
		930 5.597005957680496 937 3.0532774173010186 950 3.0532774173010186 970 3.0532774173010191;
	setAttr -s 58 ".kit[35:57]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kot[35:57]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 58 ".kix[57]"  1;
	setAttr -s 58 ".kiy[57]"  0;
	setAttr -s 58 ".kox[57]"  1;
	setAttr -s 58 ".koy[57]"  0;
createNode animCurveTA -n "animCurveTA3430";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 -0.48258715413737602 50 -0.48258715413737602 
		65 -0.48258715413737602 81 -0.48258715413737602 140 -0.48258715413737602 150 -2.0749987233327016 
		160 0.085087934563973233 168 0.65276241421642567 178 0.65276241421642567 230 0.65276241421642567 
		242 5.7496083611696891 275 0.048570682103171475 290 -3.0550791038795588 300 -3.0550791038795588 
		350 -3.0550791038795588 360 6.0873220391141913 370 6.0873220391141913 380 6.0873220391141913 
		400 6.0873220391141913 420 -3.6936209907593005 428 -0.50248938847804725 441 2.4393941412132403 
		450 2.4393941412132398 464 2.4393941412132398 480 -1.320098334979084 492 -4.3969414805519742 
		504 -4.3969414805519742 510 -4.3969414805519742 620 -4.3969414805519751 626 -4.3969414805519857 
		630 -5.5324936874234689 638 -6.6680621386312637 670 -6.6680621386312637 680 -6.6680621386312637 
		690 -6.6680621386312637 706 -6.6680621386312637 720 -1.1603785398594901 750 -1.1603785398594904 
		760 -1.1603785398594904 790 -1.1603785398594904 800 -4.8030978021640642 810 -4.8030978021640642 
		821 -2.3547727929244702 830 -4.8030978021640642 837 -2.3547727929244702 843 -4.8030978021640642 
		850 -2.3547727929244702 860 -4.8030978021640642 875 -1.1603785398594904 890 8.3140765660553733 
		905 -4.8750235047359967 912 -4.8750235047359967 920 -4.8750235047359967 930 -2.6612444181351536 
		937 -0.48258715413737591 950 -0.48258715413737591 970 -0.48258715413737602;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3431";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.35401911260776192 50 0.35401911260776192 
		65 0.35401911260776192 81 0.35401911260776192 140 0.35401911260776192 150 -1.6617588684815174 
		160 0.97401430891609964 168 1.5940088400421917 178 1.5940088400421917 230 1.5940088400421917 
		242 1.9984777624082155 275 2.5159845007932105 290 -2.2384606052132869 300 -2.2384606052132869 
		350 -2.2384606052132869 360 -9.6023739270547352 370 -9.6023739270547352 380 -9.6023739270547352 
		400 -9.6023739270547352 420 12.915175819167239 428 11.798797869072834 441 9.1845984077200686 
		450 9.1845984077200686 464 9.1845984077200686 480 6.6083857308187843 492 4.4999622224174853 
		504 4.4999622224174853 510 4.4999622224174853 620 4.4999622224174853 626 4.4999622224174862 
		630 9.4289941351882174 638 14.358096558897625 670 14.358096558897625 680 14.358096558897625 
		690 14.358096558897625 706 14.358096558897625 720 7.1285231772794244 750 7.1285231772794235 
		760 7.1285231772794235 790 7.1285231772794235 800 6.4345261300304548 810 6.4345261300304548 
		821 21.642258948933257 830 6.4345261300304548 837 21.642258948933257 843 6.4345261300304548 
		850 21.642258948933257 860 6.4345261300304548 875 7.1285231772794235 890 4.6760430046690589 
		905 16.810342455612137 912 16.810342455612137 920 16.810342455612137 930 8.516388499382856 
		937 0.3540191126077627 950 0.3540191126077627 970 0.35401911260776192;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3432";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3433";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3434";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1781";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 400 1 420 1 428 1 450 1 464 1 480 
		1 492 1 504 1 510 1 560 1 620 1 626 1 630 1 638 1 670 1 680 1 690 1 706 1 720 1 750 
		1 760 1 770 1 790 1 795 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 1 890 
		1 905 1 912 1 920 1 930 1 937 1 950 1 970 1;
	setAttr -s 57 ".kit[33:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[33:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1782";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 400 1 420 1 428 1 450 1 464 1 480 
		1 492 1 504 1 510 1 560 1 620 1 626 1 630 1 638 1 670 1 680 1 690 1 706 1 720 1 750 
		1 760 1 770 1 790 1 795 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 1 890 
		1 905 1 912 1 920 1 930 1 937 1 950 1 970 1;
	setAttr -s 57 ".kit[33:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[33:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1783";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 400 1 420 1 428 1 450 1 464 1 480 
		1 492 1 504 1 510 1 560 1 620 1 626 1 630 1 638 1 670 1 680 1 690 1 706 1 720 1 750 
		1 760 1 770 1 790 1 795 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 1 890 
		1 905 1 912 1 920 1 930 1 937 1 950 1 970 1;
	setAttr -s 57 ".kit[33:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[33:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3435";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  0 6.6307955188299239 50 6.6307955188299239 
		65 6.4641863380396174 81 6.4641863380396174 140 6.4641863380396174 150 -0.13184110446635935 
		160 -15.273307503160874 168 1.5338366053643686 178 -2.1787048677594063 230 -3.0236996213965255 
		242 9.774720978040758 275 -1.6518764480532133 290 -37.456791939374646 300 -33.084446737334659 
		350 -35.750797839283891 360 -27.203218700379278 400 -21.512676473700314 411 -3.5297482097080004 
		420 6.8181951558323126 428 -6.609895136944151 435 -2.4801023980847487 445 13.682204934647245 
		450 -33.256511721975102 464 -33.256511721975102 480 -1.1811346386754362 492 16.491134002806309 
		499 2.3558244541915281 504 16.491134002806309 510 16.491134002806309 560 16.491134002806309 
		567 20.931358879976543 620 20.931358879976543 626 27.152353942863019 630 7.1112353750467152 
		638 4.7451218493374681 670 4.7451218493374681 680 -2.0876354931862569 690 -2.0876354931862569 
		706 -2.0876354931862569 720 21.086308537774638 750 16.146142760756366 760 7.5924712101502001 
		770 -7.2046070406706892 790 -2.0307982478191771 795 -9.6765098418802733 800 18.91355172273806 
		810 16.104864664564651 821 4.4771789948747607 830 4.839665223346544 837 4.4771789948747607 
		843 4.839665223346544 850 4.4771789948747607 860 4.839665223346544 875 2.1779395916435318 
		890 -1.5308293093376828 905 0.9907383579245066 912 0.9907383579245066 920 0.9907383579245066 
		930 7.3935962505121067 937 13.69487215536908 950 13.69487215536908 970 6.6307955188299239;
	setAttr -s 62 ".kit[38:61]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 62 ".kot[38:61]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 62 ".kix[61]"  1;
	setAttr -s 62 ".kiy[61]"  0;
	setAttr -s 62 ".kox[61]"  1;
	setAttr -s 62 ".koy[61]"  0;
createNode animCurveTA -n "animCurveTA3436";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 61 ".ktv[0:60]"  0 2.8701831055247999 50 2.8701831055247999 
		65 0.12261647525028625 81 0.12261647525028625 140 0.12261647525028625 150 -5.2991978838039602 
		160 -7.073600265979513 168 -3.9537482138722257 178 -3.9537482138722257 230 -3.352464909175398 
		242 -1.4713259340201332 275 -7.3441758099040655 290 -7.3980001588876991 300 -7.3980001588876991 
		350 -14.675157437694345 360 27.146994385086657 400 25.534032573211427 411 -8.2463511202950617 
		420 -1.0222889862231879 428 2.6539792867738603 445 -8.6985929066609042 450 -6.8666748871113636 
		464 -6.8666748871113636 480 22.615730387172817 492 -9.3579559098311567 499 -3.9886923629215758 
		504 -9.3579559098311567 510 -9.3579559098311567 560 -9.3579559098311567 567 8.6076224113729491 
		620 8.6076224113729491 626 8.841303003504617 630 13.498756684462965 638 -6.836657527294105 
		670 -6.836657527294105 680 4.7398911939237935 690 4.7398911939237935 706 4.7398911939237927 
		720 2.8398656510270204 750 2.5081140913969042 760 2.1763625317667881 770 -13.538942261524005 
		790 -7.3072491957393328 795 0.85138558669684838 800 3.6505134906821777 810 6.2943132805718909 
		821 -0.12467444054102768 830 6.863340095993709 837 -0.12467444054102768 843 6.863340095993709 
		850 -0.12467444054102768 860 6.863340095993709 875 -2.9077336841532229 890 -1.7897475847474984 
		905 7.0745697286585632 912 7.0745697286585632 920 7.0745697286585632 930 3.5276469892408282 
		937 0.03699646157665501 950 0.03699646157665501 970 2.8701831055247999;
	setAttr -s 61 ".kit[37:60]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 61 ".kot[37:60]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 61 ".kix[60]"  1;
	setAttr -s 61 ".kiy[60]"  0;
	setAttr -s 61 ".kox[60]"  1;
	setAttr -s 61 ".koy[60]"  0;
createNode animCurveTA -n "animCurveTA3437";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 61 ".ktv[0:60]"  0 25.519820595404102 50 25.519820595404102 
		65 22.568210604506039 81 22.568210604506039 140 22.568210604506039 150 18.272891948316037 
		160 17.093308412653421 168 6.0278096740760967 178 6.0278096740760967 230 -7.1754949316567611 
		242 17.527045612967214 275 15.840813292646105 290 1.8434283474339708 300 1.8434283474339708 
		350 20.673855015608076 360 -72.817407554239864 400 -73.297899537625398 411 0.55575693676767979 
		420 30.364878713564014 428 26.644847953146666 445 -2.2234788490801356 450 -10.589838551289354 
		464 -10.589838551289354 480 -36.114418931822811 492 -1.4128800529030479 499 0.78896593889768707 
		504 -1.4128800529030479 510 -1.4128800529030479 560 -1.4128800529030481 567 11.450518797744211 
		620 11.450518797744211 626 7.3160722309548145 630 6.879819990834581 638 -27.084134965671016 
		670 -27.084134965671016 680 -5.0175163080209577 690 -5.0175163080209577 706 -5.0175163080209568 
		720 5.713147344439089 750 -4.441595650620032 760 -14.228549445101516 770 -18.552881161047015 
		790 -11.767950584218815 795 -15.293816296216209 800 -7.2436042493209154 810 -5.8598090903388647 
		821 2.368040651189359 830 -4.217085249854537 837 2.368040651189359 843 -4.217085249854537 
		850 2.368040651189359 860 -4.217085249854537 875 -17.740312618340017 890 -7.068416375465655 
		905 10.600796374159749 912 10.600796374159749 920 10.600796374159749 930 8.3214710616164798 
		937 6.0783074654536753 950 6.0783074654536753 970 25.519820595404102;
	setAttr -s 61 ".kit[37:60]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 61 ".kot[37:60]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 61 ".kix[60]"  1;
	setAttr -s 61 ".kiy[60]"  0;
	setAttr -s 61 ".kox[60]"  1;
	setAttr -s 61 ".koy[60]"  0;
createNode animCurveTU -n "animCurveTU1784";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000004;
createNode animCurveTU -n "animCurveTU1785";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTU -n "animCurveTU1786";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000004;
createNode animCurveTA -n "animCurveTA3438";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3439";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3440";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1162";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1163";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1164";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1787";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 64 ".ktv[0:63]"  0 0.99999999999999989 50 0.99999999999999989 
		65 0.99999999999999989 81 0.99999999999999989 140 0.99999999999999989 150 0.99999999999999989 
		160 0.99999999999999989 168 0.99999999999999989 178 0.99999999999999989 230 0.99999999999999989 
		242 0.99999999999999989 275 0.99999999999999989 290 0.99999999999999989 300 0.99999999999999989 
		350 0.99999999999999989 360 0.99999999999999989 370 0.99999999999999989 380 0.99999999999999989 
		400 0.99999999999999989 420 0.99999999999999989 428 0.99999999999999989 441 0.99999999999999989 
		450 0.99999999999999989 464 0.99999999999999989 480 0.99999999999999989 492 0.99999999999999989 
		504 0.99999999999999989 510 0.99999999999999989 620 0.99999999999999989 626 0.99999999999999989 
		630 0.99999999999999989 638 0.99999999999999989 670 0.99999999999999989 680 0.99999999999999989 
		690 0.99999999999999989 706 0.99999999999999989 720 0.99999999999999989 727 0.99999999999999989 
		731 0.99999999999999989 735 0.99999999999999989 740 0.99999999999999989 745 0.99999999999999989 
		749 0.99999999999999989 754 0.99999999999999989 760 0.99999999999999989 790 0.99999999999999989 
		795 0.99999999999999989 800 0.99999999999999989 810 0.99999999999999989 821 0.99999999999999989 
		830 0.99999999999999989 837 0.99999999999999989 843 0.99999999999999989 850 0.99999999999999989 
		860 0.99999999999999989 875 0.99999999999999989 890 0.99999999999999989 905 0.99999999999999989 
		912 0.99999999999999989 920 0.99999999999999989 930 0.99999999999999989 937 0.99999999999999989 
		950 0.99999999999999989 970 0.99999999999999989;
	setAttr -s 64 ".kit[35:63]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 64 ".kot[35:63]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 64 ".kix[63]"  1;
	setAttr -s 64 ".kiy[63]"  0;
	setAttr -s 64 ".kox[63]"  1;
	setAttr -s 64 ".koy[63]"  0;
createNode animCurveTU -n "animCurveTU1788";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 64 ".ktv[0:63]"  0 0.99999999999999956 50 0.99999999999999956 
		65 0.99999999999999956 81 0.99999999999999956 140 0.99999999999999956 150 0.99999999999999956 
		160 0.99999999999999956 168 0.99999999999999956 178 0.99999999999999956 230 0.99999999999999956 
		242 0.99999999999999956 275 0.99999999999999956 290 0.99999999999999956 300 0.99999999999999956 
		350 0.99999999999999956 360 0.99999999999999956 370 0.99999999999999956 380 0.99999999999999956 
		400 0.99999999999999956 420 0.99999999999999956 428 0.99999999999999956 441 0.99999999999999956 
		450 0.99999999999999956 464 0.99999999999999956 480 0.99999999999999956 492 0.99999999999999956 
		504 0.99999999999999956 510 0.99999999999999956 620 0.99999999999999956 626 0.99999999999999956 
		630 0.99999999999999956 638 0.99999999999999956 670 0.99999999999999956 680 0.99999999999999956 
		690 0.99999999999999956 706 0.99999999999999956 720 0.99999999999999956 727 0.99999999999999956 
		731 0.99999999999999956 735 0.99999999999999956 740 0.99999999999999956 745 0.99999999999999956 
		749 0.99999999999999956 754 0.99999999999999956 760 0.99999999999999956 790 0.99999999999999956 
		795 0.99999999999999956 800 0.99999999999999956 810 0.99999999999999956 821 0.99999999999999956 
		830 0.99999999999999956 837 0.99999999999999956 843 0.99999999999999956 850 0.99999999999999956 
		860 0.99999999999999956 875 0.99999999999999956 890 0.99999999999999956 905 0.99999999999999956 
		912 0.99999999999999956 920 0.99999999999999956 930 0.99999999999999956 937 0.99999999999999956 
		950 0.99999999999999956 970 0.99999999999999956;
	setAttr -s 64 ".kit[35:63]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 64 ".kot[35:63]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 64 ".kix[63]"  1;
	setAttr -s 64 ".kiy[63]"  0;
	setAttr -s 64 ".kox[63]"  1;
	setAttr -s 64 ".koy[63]"  0;
createNode animCurveTU -n "animCurveTU1789";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 64 ".ktv[0:63]"  0 0.99999999999999922 50 0.99999999999999922 
		65 0.99999999999999922 81 0.99999999999999922 140 0.99999999999999922 150 0.99999999999999922 
		160 0.99999999999999922 168 0.99999999999999922 178 0.99999999999999922 230 0.99999999999999922 
		242 0.99999999999999922 275 0.99999999999999922 290 0.99999999999999922 300 0.99999999999999922 
		350 0.99999999999999922 360 0.99999999999999922 370 0.99999999999999922 380 0.99999999999999922 
		400 0.99999999999999922 420 0.99999999999999922 428 0.99999999999999922 441 0.99999999999999922 
		450 0.99999999999999922 464 0.99999999999999922 480 0.99999999999999922 492 0.99999999999999922 
		504 0.99999999999999922 510 0.99999999999999922 620 0.99999999999999922 626 0.99999999999999922 
		630 0.99999999999999922 638 0.99999999999999922 670 0.99999999999999922 680 0.99999999999999922 
		690 0.99999999999999922 706 0.99999999999999922 720 0.99999999999999922 727 0.99999999999999922 
		731 0.99999999999999922 735 0.99999999999999922 740 0.99999999999999922 745 0.99999999999999922 
		749 0.99999999999999922 754 0.99999999999999922 760 0.99999999999999922 790 0.99999999999999922 
		795 0.99999999999999922 800 0.99999999999999922 810 0.99999999999999922 821 0.99999999999999922 
		830 0.99999999999999922 837 0.99999999999999922 843 0.99999999999999922 850 0.99999999999999922 
		860 0.99999999999999922 875 0.99999999999999922 890 0.99999999999999922 905 0.99999999999999922 
		912 0.99999999999999922 920 0.99999999999999922 930 0.99999999999999922 937 0.99999999999999922 
		950 0.99999999999999922 970 0.99999999999999922;
	setAttr -s 64 ".kit[35:63]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 64 ".kot[35:63]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 64 ".kix[63]"  1;
	setAttr -s 64 ".kiy[63]"  0;
	setAttr -s 64 ".kox[63]"  1;
	setAttr -s 64 ".koy[63]"  0;
createNode animCurveTA -n "animCurveTA3441";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 66 ".ktv[0:65]"  0 0 50 0 65 0 81 0 140 0 150 0 160 8.0288899760130121 
		168 11.889541682864611 178 16.057771337967239 230 16.057771337967239 242 0 275 0 
		290 11.566874255067566 300 11.566874255067566 350 11.566874255067566 360 11.566874255067566 
		370 11.566874255067566 380 11.566874255067566 400 11.566874255067566 411 0 420 0 
		428 0 441 15.09416472536865 450 37.431599673966929 464 53.575400265345031 480 0 492 
		0 504 11.257846822493768 510 11.257846822493768 620 11.257846822493768 626 11.257846822493768 
		630 19.538927359387667 638 27.820126359049155 670 27.820126359049155 680 27.820126359049155 
		690 27.820126359049155 706 27.820126359049155 720 10.117090119927035 727 13.652175997482168 
		731 10.117090119927035 735 13.652175997482168 740 10.117090119927035 745 13.652175997482168 
		749 10.117090119927035 754 13.652175997482168 760 0 790 3.1928099026512555 795 23.295504993455378 
		800 8.8256022830138932 810 8.8256022830138932 821 8.8256022830138932 830 8.8256022830138932 
		837 8.8256022830138932 843 8.8256022830138932 850 8.8256022830138932 860 8.8256022830138932 
		875 16.512063303863922 890 -1.2769102257656257 898 0 905 0 912 0 920 0 930 0 937 
		0 950 0 970 0;
	setAttr -s 66 ".kit[36:65]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 1;
	setAttr -s 66 ".kot[36:65]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 1;
	setAttr -s 66 ".kix[65]"  1;
	setAttr -s 66 ".kiy[65]"  0;
	setAttr -s 66 ".kox[65]"  1;
	setAttr -s 66 ".koy[65]"  0;
createNode animCurveTA -n "animCurveTA3442";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 66 ".ktv[0:65]"  0 0 50 0 65 0 81 0 140 0 150 0 160 8.930652725917632 
		168 22.731055210977146 178 17.861295870290643 230 17.861295870290643 242 0 275 0 
		290 17.272343395837769 300 17.272343395837769 350 17.272343395837769 360 17.272343395837769 
		370 17.272343395837769 380 17.272343395837769 400 17.272343395837769 411 0 420 0 
		428 0 441 19.987024228954784 450 19.211426907152102 464 33.846926017282307 480 0 
		492 0 504 -2.0055670842135394 510 -2.0055670842135394 620 -2.0055670842135407 626 
		-2.0055670842135407 630 6.2576768681742339 638 14.521039028173146 670 14.521039028173146 
		680 14.521039028173146 690 14.521039028173146 706 14.521039028173146 720 20.730849357083802 
		727 26.45370548816593 731 20.730849357083802 735 26.45370548816593 740 20.730849357083802 
		745 26.45370548816593 749 20.730849357083802 754 26.45370548816593 760 0 790 0.17168152442734722 
		795 18.714788835872692 800 48.817944516960324 810 48.817944516960324 821 48.817944516960324 
		830 48.817944516960324 837 48.817944516960324 843 48.817944516960324 850 48.817944516960324 
		860 48.817944516960324 875 15.046527098669948 890 8.0463121004843483 898 0 905 0 
		912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 66 ".kit[36:65]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 1;
	setAttr -s 66 ".kot[36:65]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 1;
	setAttr -s 66 ".kix[65]"  1;
	setAttr -s 66 ".kiy[65]"  0;
	setAttr -s 66 ".kox[65]"  1;
	setAttr -s 66 ".koy[65]"  0;
createNode animCurveTA -n "animCurveTA3443";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 66 ".ktv[0:65]"  0 0 50 0 65 0 81 0 140 0 150 0 160 -6.1459422698254151 
		168 -17.001413788796562 178 -12.291877945774447 230 -12.291877945774447 242 0 275 
		0 290 -10.622582881163728 300 -10.622582881163728 350 -10.622582881163728 360 -10.622582881163728 
		370 -10.622582881163728 380 -10.622582881163728 400 -10.622582881163728 411 0 420 
		0 428 0 441 -1.7041453851090946 450 13.779616966809289 464 21.767757085794212 480 
		0 492 0 504 4.6170957497496872 510 4.6170957497496872 620 4.6170957497496872 626 
		4.6170957497496872 630 2.3319936937310657 638 0.046858948800343372 670 0.046858948800343227 
		680 0.046858948800343227 690 0.046858948800343227 706 0.046858948800343227 720 -6.3419530007527811 
		727 -6.9486316206955561 731 -6.3419530007527811 735 -6.9486316206955561 740 -6.3419530007527811 
		745 -6.9486316206955561 749 -6.3419530007527811 754 -6.9486316206955561 760 0 790 
		-1.7159405542710096 795 -5.981469569318274 800 -7.9068274583784719 810 -7.9068274583784719 
		821 -7.9068274583784719 830 -7.9068274583784719 837 -7.9068274583784719 843 -7.9068274583784719 
		850 -7.9068274583784719 860 -7.9068274583784719 875 2.3517837717130079 890 -5.3118250084557834 
		898 0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 66 ".kit[36:65]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 1;
	setAttr -s 66 ".kot[36:65]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 1;
	setAttr -s 66 ".kix[65]"  1;
	setAttr -s 66 ".kiy[65]"  0;
	setAttr -s 66 ".kox[65]"  1;
	setAttr -s 66 ".koy[65]"  0;
createNode animCurveTL -n "animCurveTL1165";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 64 ".ktv[0:63]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 727 0 731 0 735 0 740 0 745 0 749 0 754 0 760 0 790 0 795 0 800 0 810 0 821 
		0 830 0 837 0 843 0 850 0 860 0 875 0 890 0 905 0 912 0 920 0 930 0 937 0 950 0 970 
		0;
	setAttr -s 64 ".kit[35:63]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 64 ".kot[35:63]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 64 ".kix[63]"  1;
	setAttr -s 64 ".kiy[63]"  0;
	setAttr -s 64 ".kox[63]"  1;
	setAttr -s 64 ".koy[63]"  0;
createNode animCurveTL -n "animCurveTL1166";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 64 ".ktv[0:63]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 727 0 731 0 735 0 740 0 745 0 749 0 754 0 760 0 790 0 795 0 800 0 810 0 821 
		0 830 0 837 0 843 0 850 0 860 0 875 0 890 0 905 0 912 0 920 0 930 0 937 0 950 0 970 
		0;
	setAttr -s 64 ".kit[35:63]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 64 ".kot[35:63]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 64 ".kix[63]"  1;
	setAttr -s 64 ".kiy[63]"  0;
	setAttr -s 64 ".kox[63]"  1;
	setAttr -s 64 ".koy[63]"  0;
createNode animCurveTL -n "animCurveTL1167";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 64 ".ktv[0:63]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 727 0 731 0 735 0 740 0 745 0 749 0 754 0 760 0 790 0 795 0 800 0 810 0 821 
		0 830 0 837 0 843 0 850 0 860 0 875 0 890 0 905 0 912 0 920 0 930 0 937 0 950 0 970 
		0;
	setAttr -s 64 ".kit[35:63]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 64 ".kot[35:63]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 64 ".kix[63]"  1;
	setAttr -s 64 ".kiy[63]"  0;
	setAttr -s 64 ".kox[63]"  1;
	setAttr -s 64 ".koy[63]"  0;
createNode animCurveTA -n "animCurveTA3444";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3445";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3446";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1790";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU1791";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTU -n "animCurveTU1792";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999978;
createNode animCurveTA -n "animCurveTA3447";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3448";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3449";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3450";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3451";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3452";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1793";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999967;
createNode animCurveTU -n "animCurveTU1794";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999956;
createNode animCurveTU -n "animCurveTU1795";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999978;
createNode animCurveTA -n "animCurveTA3453";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3454";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3455";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3456";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3457";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3458";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1796";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.999999999999999;
createNode animCurveTU -n "animCurveTU1797";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999933;
createNode animCurveTU -n "animCurveTU1798";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999922;
createNode animCurveTA -n "animCurveTA3459";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3460";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3461";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3462";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3463";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3464";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1799";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 1.0000000000000002 50 1.0000000000000002 
		65 1.0000000000000002 81 1.0000000000000002 140 1.0000000000000002 150 1.0000000000000002 
		160 1.0000000000000002 168 1.0000000000000002 178 1.0000000000000002 230 1.0000000000000002 
		242 1.0000000000000002 275 1.0000000000000002 290 1.0000000000000002 300 1.0000000000000002 
		350 1.0000000000000002 360 1.0000000000000002 370 1.0000000000000002 380 1.0000000000000002 
		400 1.0000000000000002 420 1.0000000000000002 428 1.0000000000000002 441 1.0000000000000002 
		450 1.0000000000000002 464 1.0000000000000002 480 1.0000000000000002 492 1.0000000000000002 
		504 1.0000000000000002 510 1.0000000000000002 620 1.0000000000000002 626 1.0000000000000002 
		630 1.0000000000000002 638 1.0000000000000002 670 1.0000000000000002 680 1.0000000000000002 
		690 1.0000000000000002 706 1.0000000000000002 720 1.0000000000000002 750 1.0000000000000002 
		760 1.0000000000000002 790 1.0000000000000002 800 1.0000000000000002 810 1.0000000000000002 
		821 1.0000000000000002 830 1.0000000000000002 837 1.0000000000000002 843 1.0000000000000002 
		850 1.0000000000000002 860 1.0000000000000002 875 1.0000000000000002 890 1.0000000000000002 
		905 1.0000000000000002 912 1.0000000000000002 920 1.0000000000000002 930 1.0000000000000002 
		937 1.0000000000000002 950 1.0000000000000002 970 1.0000000000000002;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1800";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.99999999999999978 50 0.99999999999999978 
		65 0.99999999999999978 81 0.99999999999999978 140 0.99999999999999978 150 0.99999999999999978 
		160 0.99999999999999978 168 0.99999999999999978 178 0.99999999999999978 230 0.99999999999999978 
		242 0.99999999999999978 275 0.99999999999999978 290 0.99999999999999978 300 0.99999999999999978 
		350 0.99999999999999978 360 0.99999999999999978 370 0.99999999999999978 380 0.99999999999999978 
		400 0.99999999999999978 420 0.99999999999999978 428 0.99999999999999978 441 0.99999999999999978 
		450 0.99999999999999978 464 0.99999999999999978 480 0.99999999999999978 492 0.99999999999999978 
		504 0.99999999999999978 510 0.99999999999999978 620 0.99999999999999978 626 0.99999999999999978 
		630 0.99999999999999978 638 0.99999999999999978 670 0.99999999999999978 680 0.99999999999999978 
		690 0.99999999999999978 706 0.99999999999999978 720 0.99999999999999978 750 0.99999999999999978 
		760 0.99999999999999978 790 0.99999999999999978 800 0.99999999999999978 810 0.99999999999999978 
		821 0.99999999999999978 830 0.99999999999999978 837 0.99999999999999978 843 0.99999999999999978 
		850 0.99999999999999978 860 0.99999999999999978 875 0.99999999999999978 890 0.99999999999999978 
		905 0.99999999999999978 912 0.99999999999999978 920 0.99999999999999978 930 0.99999999999999978 
		937 0.99999999999999978 950 0.99999999999999978 970 0.99999999999999978;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1801";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.99999999999999956 50 0.99999999999999956 
		65 0.99999999999999956 81 0.99999999999999956 140 0.99999999999999956 150 0.99999999999999956 
		160 0.99999999999999956 168 0.99999999999999956 178 0.99999999999999956 230 0.99999999999999956 
		242 0.99999999999999956 275 0.99999999999999956 290 0.99999999999999956 300 0.99999999999999956 
		350 0.99999999999999956 360 0.99999999999999956 370 0.99999999999999956 380 0.99999999999999956 
		400 0.99999999999999956 420 0.99999999999999956 428 0.99999999999999956 441 0.99999999999999956 
		450 0.99999999999999956 464 0.99999999999999956 480 0.99999999999999956 492 0.99999999999999956 
		504 0.99999999999999956 510 0.99999999999999956 620 0.99999999999999956 626 0.99999999999999956 
		630 0.99999999999999956 638 0.99999999999999956 670 0.99999999999999956 680 0.99999999999999956 
		690 0.99999999999999956 706 0.99999999999999956 720 0.99999999999999956 750 0.99999999999999956 
		760 0.99999999999999956 790 0.99999999999999956 800 0.99999999999999956 810 0.99999999999999956 
		821 0.99999999999999956 830 0.99999999999999956 837 0.99999999999999956 843 0.99999999999999956 
		850 0.99999999999999956 860 0.99999999999999956 875 0.99999999999999956 890 0.99999999999999956 
		905 0.99999999999999956 912 0.99999999999999956 920 0.99999999999999956 930 0.99999999999999956 
		937 0.99999999999999956 950 0.99999999999999956 970 0.99999999999999956;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3465";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 -9.8496280095381739 50 -9.8496280095381739 
		65 -9.8496280095381739 81 -9.8496280095381739 140 -9.8496280095381739 150 -9.8496280095381739 
		160 -9.8496280095381739 168 -9.8496280095381739 178 -9.8496280095381739 230 -9.8496280095381739 
		242 -9.8496280095381739 275 -9.8496280095381739 290 -9.8496280095381739 300 -9.8496280095381739 
		350 -9.8496280095381739 360 -9.8496280095381739 370 -9.8496280095381739 380 -9.8496280095381739 
		400 -9.8496280095381739 420 -9.8496280095381739 428 -9.8496280095381739 441 -9.8496280095381739 
		450 -9.8496280095381739 464 -9.8496280095381739 480 -9.8496280095381739 492 -9.8496280095381739 
		504 -9.8496280095381739 510 -9.8496280095381739 620 -9.8496280095381739 626 -9.8496280095381739 
		630 -9.8496280095381739 638 -9.8496280095381739 670 -9.8496280095381739 680 -9.8496280095381739 
		690 -9.8496280095381739 706 -9.8496280095381739 720 -9.8496280095381739 750 -9.8496280095381739 
		760 -9.8496280095381739 790 -9.8496280095381739 800 -9.8496280095381739 810 -9.8496280095381739 
		821 -9.8496280095381739 830 -9.8496280095381739 837 -9.8496280095381739 843 -9.8496280095381739 
		850 -9.8496280095381739 860 -9.8496280095381739 875 -9.8496280095381739 890 -9.8496280095381739 
		905 -9.8496280095381739 912 -9.8496280095381739 920 -9.8496280095381739 930 -9.8496280095381739 
		937 -9.8496280095381739 950 -9.8496280095381739 970 -9.8496280095381739;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3466";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 -2.0984782587122006 50 -2.0984782587122006 
		65 -2.0984782587122006 81 -2.0984782587122006 140 -2.0984782587122006 150 -2.0984782587122006 
		160 -2.0984782587122006 168 -2.0984782587122006 178 -2.0984782587122006 230 -2.0984782587122006 
		242 -2.0984782587122006 275 -2.0984782587122006 290 -2.0984782587122006 300 -2.0984782587122006 
		350 -2.0984782587122006 360 -2.0984782587122006 370 -2.0984782587122006 380 -2.0984782587122006 
		400 -2.0984782587122006 420 -2.0984782587122006 428 -2.0984782587122006 441 -2.0984782587122006 
		450 -2.0984782587122006 464 -2.0984782587122006 480 -2.0984782587122006 492 -2.0984782587122006 
		504 -2.0984782587122006 510 -2.0984782587122006 620 -2.0984782587122006 626 -2.0984782587122006 
		630 -2.0984782587122006 638 -2.0984782587122006 670 -2.0984782587122006 680 -2.0984782587122006 
		690 -2.0984782587122006 706 -2.0984782587122006 720 -2.0984782587122006 750 -2.0984782587122006 
		760 -2.0984782587122006 790 -2.0984782587122006 800 -2.0984782587122006 810 -2.0984782587122006 
		821 -2.0984782587122006 830 -2.0984782587122006 837 -2.0984782587122006 843 -2.0984782587122006 
		850 -2.0984782587122006 860 -2.0984782587122006 875 -2.0984782587122006 890 -2.0984782587122006 
		905 -2.0984782587122006 912 -2.0984782587122006 920 -2.0984782587122006 930 -2.0984782587122006 
		937 -2.0984782587122006 950 -2.0984782587122006 970 -2.0984782587122006;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3467";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 -1.156749226655551 50 -1.156749226655551 
		65 -1.156749226655551 81 -1.156749226655551 140 -1.156749226655551 150 -1.156749226655551 
		160 -1.156749226655551 168 -1.156749226655551 178 -1.156749226655551 230 -1.156749226655551 
		242 -1.156749226655551 275 -1.156749226655551 290 -1.156749226655551 300 -1.156749226655551 
		350 -1.156749226655551 360 -1.156749226655551 370 -1.156749226655551 380 -1.156749226655551 
		400 -1.156749226655551 420 -1.156749226655551 428 -1.156749226655551 441 -1.156749226655551 
		450 -1.156749226655551 464 -1.156749226655551 480 -1.156749226655551 492 -1.156749226655551 
		504 -1.156749226655551 510 -1.156749226655551 620 -1.156749226655551 626 -1.156749226655551 
		630 -1.156749226655551 638 -1.156749226655551 670 -1.156749226655551 680 -1.156749226655551 
		690 -1.156749226655551 706 -1.156749226655551 720 -1.156749226655551 750 -1.156749226655551 
		760 -1.156749226655551 790 -1.156749226655551 800 -1.156749226655551 810 -1.156749226655551 
		821 -1.156749226655551 830 -1.156749226655551 837 -1.156749226655551 843 -1.156749226655551 
		850 -1.156749226655551 860 -1.156749226655551 875 -1.156749226655551 890 -1.156749226655551 
		905 -1.156749226655551 912 -1.156749226655551 920 -1.156749226655551 930 -1.156749226655551 
		937 -1.156749226655551 950 -1.156749226655551 970 -1.156749226655551;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3468";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3469";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3470";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1802";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.99999999999999978 50 0.99999999999999978 
		65 0.99999999999999978 81 0.99999999999999978 140 0.99999999999999978 150 0.99999999999999978 
		160 0.99999999999999978 168 0.99999999999999978 178 0.99999999999999978 230 0.99999999999999978 
		242 0.99999999999999978 275 0.99999999999999978 290 0.99999999999999978 300 0.99999999999999978 
		350 0.99999999999999978 360 0.99999999999999978 370 0.99999999999999978 380 0.99999999999999978 
		400 0.99999999999999978 420 0.99999999999999978 428 0.99999999999999978 441 0.99999999999999978 
		450 0.99999999999999978 464 0.99999999999999978 480 0.99999999999999978 492 0.99999999999999978 
		504 0.99999999999999978 510 0.99999999999999978 620 0.99999999999999978 626 0.99999999999999978 
		630 0.99999999999999978 638 0.99999999999999978 670 0.99999999999999978 680 0.99999999999999978 
		690 0.99999999999999978 706 0.99999999999999978 720 0.99999999999999978 750 0.99999999999999978 
		760 0.99999999999999978 790 0.99999999999999978 800 0.99999999999999978 810 0.99999999999999978 
		821 0.99999999999999978 830 0.99999999999999978 837 0.99999999999999978 843 0.99999999999999978 
		850 0.99999999999999978 860 0.99999999999999978 875 0.99999999999999978 890 0.99999999999999978 
		905 0.99999999999999978 912 0.99999999999999978 920 0.99999999999999978 930 0.99999999999999978 
		937 0.99999999999999978 950 0.99999999999999978 970 0.99999999999999978;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1803";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.99999999999999967 50 0.99999999999999967 
		65 0.99999999999999967 81 0.99999999999999967 140 0.99999999999999967 150 0.99999999999999967 
		160 0.99999999999999967 168 0.99999999999999967 178 0.99999999999999967 230 0.99999999999999967 
		242 0.99999999999999967 275 0.99999999999999967 290 0.99999999999999967 300 0.99999999999999967 
		350 0.99999999999999967 360 0.99999999999999967 370 0.99999999999999967 380 0.99999999999999967 
		400 0.99999999999999967 420 0.99999999999999967 428 0.99999999999999967 441 0.99999999999999967 
		450 0.99999999999999967 464 0.99999999999999967 480 0.99999999999999967 492 0.99999999999999967 
		504 0.99999999999999967 510 0.99999999999999967 620 0.99999999999999967 626 0.99999999999999967 
		630 0.99999999999999967 638 0.99999999999999967 670 0.99999999999999967 680 0.99999999999999967 
		690 0.99999999999999967 706 0.99999999999999967 720 0.99999999999999967 750 0.99999999999999967 
		760 0.99999999999999967 790 0.99999999999999967 800 0.99999999999999967 810 0.99999999999999967 
		821 0.99999999999999967 830 0.99999999999999967 837 0.99999999999999967 843 0.99999999999999967 
		850 0.99999999999999967 860 0.99999999999999967 875 0.99999999999999967 890 0.99999999999999967 
		905 0.99999999999999967 912 0.99999999999999967 920 0.99999999999999967 930 0.99999999999999967 
		937 0.99999999999999967 950 0.99999999999999967 970 0.99999999999999967;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1804";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.99999999999999933 50 0.99999999999999933 
		65 0.99999999999999933 81 0.99999999999999933 140 0.99999999999999933 150 0.99999999999999933 
		160 0.99999999999999933 168 0.99999999999999933 178 0.99999999999999933 230 0.99999999999999933 
		242 0.99999999999999933 275 0.99999999999999933 290 0.99999999999999933 300 0.99999999999999933 
		350 0.99999999999999933 360 0.99999999999999933 370 0.99999999999999933 380 0.99999999999999933 
		400 0.99999999999999933 420 0.99999999999999933 428 0.99999999999999933 441 0.99999999999999933 
		450 0.99999999999999933 464 0.99999999999999933 480 0.99999999999999933 492 0.99999999999999933 
		504 0.99999999999999933 510 0.99999999999999933 620 0.99999999999999933 626 0.99999999999999933 
		630 0.99999999999999933 638 0.99999999999999933 670 0.99999999999999933 680 0.99999999999999933 
		690 0.99999999999999933 706 0.99999999999999933 720 0.99999999999999933 750 0.99999999999999933 
		760 0.99999999999999933 790 0.99999999999999933 800 0.99999999999999933 810 0.99999999999999933 
		821 0.99999999999999933 830 0.99999999999999933 837 0.99999999999999933 843 0.99999999999999933 
		850 0.99999999999999933 860 0.99999999999999933 875 0.99999999999999933 890 0.99999999999999933 
		905 0.99999999999999933 912 0.99999999999999933 920 0.99999999999999933 930 0.99999999999999933 
		937 0.99999999999999933 950 0.99999999999999933 970 0.99999999999999933;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3471";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 -21.724355717678407 50 -21.724355717678407 
		65 -21.724355717678407 81 -21.724355717678407 140 -21.724355717678407 150 -21.724355717678407 
		160 -21.724355717678407 168 -21.724355717678407 178 -21.724355717678407 230 -21.724355717678407 
		242 -21.724355717678407 275 -21.724355717678407 290 -21.724355717678407 300 -21.724355717678407 
		350 -21.724355717678407 360 -21.724355717678407 370 -21.724355717678407 380 -21.724355717678407 
		400 -21.724355717678407 420 -21.724355717678407 428 -21.724355717678407 441 -21.724355717678407 
		450 -21.724355717678407 464 -21.724355717678407 480 -21.724355717678407 492 -21.724355717678407 
		504 -21.724355717678407 510 -21.724355717678407 620 -21.724355717678407 626 -21.724355717678407 
		630 -21.724355717678407 638 -21.724355717678407 670 -21.724355717678407 680 -21.724355717678407 
		690 -21.724355717678407 706 -21.724355717678407 720 -21.724355717678407 750 -21.724355717678407 
		760 -21.724355717678407 790 -21.724355717678407 800 -21.724355717678407 810 -21.724355717678407 
		821 -21.724355717678407 830 -21.724355717678407 837 -21.724355717678407 843 -21.724355717678407 
		850 -21.724355717678407 860 -21.724355717678407 875 -21.724355717678407 890 -21.724355717678407 
		905 -21.724355717678407 912 -21.724355717678407 920 -21.724355717678407 930 -21.724355717678407 
		937 -21.724355717678407 950 -21.724355717678407 970 -21.724355717678407;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3472";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.54486597751175991 50 0.54486597751175991 
		65 0.54486597751175991 81 0.54486597751175991 140 0.54486597751175991 150 0.54486597751175991 
		160 0.54486597751175991 168 0.54486597751175991 178 0.54486597751175991 230 0.54486597751175991 
		242 0.54486597751175991 275 0.54486597751175991 290 0.54486597751175991 300 0.54486597751175991 
		350 0.54486597751175991 360 0.54486597751175991 370 0.54486597751175991 380 0.54486597751175991 
		400 0.54486597751175991 420 0.54486597751175991 428 0.54486597751175991 441 0.54486597751175991 
		450 0.54486597751175991 464 0.54486597751175991 480 0.54486597751175991 492 0.54486597751175991 
		504 0.54486597751175991 510 0.54486597751175991 620 0.54486597751175991 626 0.54486597751175991 
		630 0.54486597751175991 638 0.54486597751175991 670 0.54486597751175991 680 0.54486597751175991 
		690 0.54486597751175991 706 0.54486597751175991 720 0.54486597751175991 750 0.54486597751175991 
		760 0.54486597751175991 790 0.54486597751175991 800 0.54486597751175991 810 0.54486597751175991 
		821 0.54486597751175991 830 0.54486597751175991 837 0.54486597751175991 843 0.54486597751175991 
		850 0.54486597751175991 860 0.54486597751175991 875 0.54486597751175991 890 0.54486597751175991 
		905 0.54486597751175991 912 0.54486597751175991 920 0.54486597751175991 930 0.54486597751175991 
		937 0.54486597751175991 950 0.54486597751175991 970 0.54486597751175991;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3473";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.57631240306333031 50 0.57631240306333031 
		65 0.57631240306333031 81 0.57631240306333031 140 0.57631240306333031 150 0.57631240306333031 
		160 0.57631240306333031 168 0.57631240306333031 178 0.57631240306333031 230 0.57631240306333031 
		242 0.57631240306333031 275 0.57631240306333031 290 0.57631240306333031 300 0.57631240306333031 
		350 0.57631240306333031 360 0.57631240306333031 370 0.57631240306333031 380 0.57631240306333031 
		400 0.57631240306333031 420 0.57631240306333031 428 0.57631240306333031 441 0.57631240306333031 
		450 0.57631240306333031 464 0.57631240306333031 480 0.57631240306333031 492 0.57631240306333031 
		504 0.57631240306333031 510 0.57631240306333031 620 0.57631240306333031 626 0.57631240306333031 
		630 0.57631240306333031 638 0.57631240306333031 670 0.57631240306333031 680 0.57631240306333031 
		690 0.57631240306333031 706 0.57631240306333031 720 0.57631240306333031 750 0.57631240306333031 
		760 0.57631240306333031 790 0.57631240306333031 800 0.57631240306333031 810 0.57631240306333031 
		821 0.57631240306333031 830 0.57631240306333031 837 0.57631240306333031 843 0.57631240306333031 
		850 0.57631240306333031 860 0.57631240306333031 875 0.57631240306333031 890 0.57631240306333031 
		905 0.57631240306333031 912 0.57631240306333031 920 0.57631240306333031 930 0.57631240306333031 
		937 0.57631240306333031 950 0.57631240306333031 970 0.57631240306333031;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3474";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3475";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3476";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1805";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.99999999999999944 50 0.99999999999999944 
		65 0.99999999999999944 81 0.99999999999999944 140 0.99999999999999944 150 0.99999999999999944 
		160 0.99999999999999944 168 0.99999999999999944 178 0.99999999999999944 230 0.99999999999999944 
		242 0.99999999999999944 275 0.99999999999999944 290 0.99999999999999944 300 0.99999999999999944 
		350 0.99999999999999944 360 0.99999999999999944 370 0.99999999999999944 380 0.99999999999999944 
		400 0.99999999999999944 420 0.99999999999999944 428 0.99999999999999944 441 0.99999999999999944 
		450 0.99999999999999944 464 0.99999999999999944 480 0.99999999999999944 492 0.99999999999999944 
		504 0.99999999999999944 510 0.99999999999999944 620 0.99999999999999944 626 0.99999999999999944 
		630 0.99999999999999944 638 0.99999999999999944 670 0.99999999999999944 680 0.99999999999999944 
		690 0.99999999999999944 706 0.99999999999999944 720 0.99999999999999944 750 0.99999999999999944 
		760 0.99999999999999944 790 0.99999999999999944 800 0.99999999999999944 810 0.99999999999999944 
		821 0.99999999999999944 830 0.99999999999999944 837 0.99999999999999944 843 0.99999999999999944 
		850 0.99999999999999944 860 0.99999999999999944 875 0.99999999999999944 890 0.99999999999999944 
		905 0.99999999999999944 912 0.99999999999999944 920 0.99999999999999944 930 0.99999999999999944 
		937 0.99999999999999944 950 0.99999999999999944 970 0.99999999999999944;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1806";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.99999999999999978 50 0.99999999999999978 
		65 0.99999999999999978 81 0.99999999999999978 140 0.99999999999999978 150 0.99999999999999978 
		160 0.99999999999999978 168 0.99999999999999978 178 0.99999999999999978 230 0.99999999999999978 
		242 0.99999999999999978 275 0.99999999999999978 290 0.99999999999999978 300 0.99999999999999978 
		350 0.99999999999999978 360 0.99999999999999978 370 0.99999999999999978 380 0.99999999999999978 
		400 0.99999999999999978 420 0.99999999999999978 428 0.99999999999999978 441 0.99999999999999978 
		450 0.99999999999999978 464 0.99999999999999978 480 0.99999999999999978 492 0.99999999999999978 
		504 0.99999999999999978 510 0.99999999999999978 620 0.99999999999999978 626 0.99999999999999978 
		630 0.99999999999999978 638 0.99999999999999978 670 0.99999999999999978 680 0.99999999999999978 
		690 0.99999999999999978 706 0.99999999999999978 720 0.99999999999999978 750 0.99999999999999978 
		760 0.99999999999999978 790 0.99999999999999978 800 0.99999999999999978 810 0.99999999999999978 
		821 0.99999999999999978 830 0.99999999999999978 837 0.99999999999999978 843 0.99999999999999978 
		850 0.99999999999999978 860 0.99999999999999978 875 0.99999999999999978 890 0.99999999999999978 
		905 0.99999999999999978 912 0.99999999999999978 920 0.99999999999999978 930 0.99999999999999978 
		937 0.99999999999999978 950 0.99999999999999978 970 0.99999999999999978;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1807";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.99999999999999989 50 0.99999999999999989 
		65 0.99999999999999989 81 0.99999999999999989 140 0.99999999999999989 150 0.99999999999999989 
		160 0.99999999999999989 168 0.99999999999999989 178 0.99999999999999989 230 0.99999999999999989 
		242 0.99999999999999989 275 0.99999999999999989 290 0.99999999999999989 300 0.99999999999999989 
		350 0.99999999999999989 360 0.99999999999999989 370 0.99999999999999989 380 0.99999999999999989 
		400 0.99999999999999989 420 0.99999999999999989 428 0.99999999999999989 441 0.99999999999999989 
		450 0.99999999999999989 464 0.99999999999999989 480 0.99999999999999989 492 0.99999999999999989 
		504 0.99999999999999989 510 0.99999999999999989 620 0.99999999999999989 626 0.99999999999999989 
		630 0.99999999999999989 638 0.99999999999999989 670 0.99999999999999989 680 0.99999999999999989 
		690 0.99999999999999989 706 0.99999999999999989 720 0.99999999999999989 750 0.99999999999999989 
		760 0.99999999999999989 790 0.99999999999999989 800 0.99999999999999989 810 0.99999999999999989 
		821 0.99999999999999989 830 0.99999999999999989 837 0.99999999999999989 843 0.99999999999999989 
		850 0.99999999999999989 860 0.99999999999999989 875 0.99999999999999989 890 0.99999999999999989 
		905 0.99999999999999989 912 0.99999999999999989 920 0.99999999999999989 930 0.99999999999999989 
		937 0.99999999999999989 950 0.99999999999999989 970 0.99999999999999989;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3477";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3478";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3479";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3480";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3481";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3482";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1808";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.99999999999999989 50 0.99999999999999989 
		65 0.99999999999999989 81 0.99999999999999989 140 0.99999999999999989 150 0.99999999999999989 
		160 0.99999999999999989 168 0.99999999999999989 178 0.99999999999999989 230 0.99999999999999989 
		242 0.99999999999999989 275 0.99999999999999989 290 0.99999999999999989 300 0.99999999999999989 
		350 0.99999999999999989 360 0.99999999999999989 370 0.99999999999999989 380 0.99999999999999989 
		400 0.99999999999999989 420 0.99999999999999989 428 0.99999999999999989 441 0.99999999999999989 
		450 0.99999999999999989 464 0.99999999999999989 480 0.99999999999999989 492 0.99999999999999989 
		504 0.99999999999999989 510 0.99999999999999989 620 0.99999999999999989 626 0.99999999999999989 
		630 0.99999999999999989 638 0.99999999999999989 670 0.99999999999999989 680 0.99999999999999989 
		690 0.99999999999999989 706 0.99999999999999989 720 0.99999999999999989 750 0.99999999999999989 
		760 0.99999999999999989 790 0.99999999999999989 800 0.99999999999999989 810 0.99999999999999989 
		821 0.99999999999999989 830 0.99999999999999989 837 0.99999999999999989 843 0.99999999999999989 
		850 0.99999999999999989 860 0.99999999999999989 875 0.99999999999999989 890 0.99999999999999989 
		905 0.99999999999999989 912 0.99999999999999989 920 0.99999999999999989 930 0.99999999999999989 
		937 0.99999999999999989 950 0.99999999999999989 970 0.99999999999999989;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1809";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.99999999999999956 50 0.99999999999999956 
		65 0.99999999999999956 81 0.99999999999999956 140 0.99999999999999956 150 0.99999999999999956 
		160 0.99999999999999956 168 0.99999999999999956 178 0.99999999999999956 230 0.99999999999999956 
		242 0.99999999999999956 275 0.99999999999999956 290 0.99999999999999956 300 0.99999999999999956 
		350 0.99999999999999956 360 0.99999999999999956 370 0.99999999999999956 380 0.99999999999999956 
		400 0.99999999999999956 420 0.99999999999999956 428 0.99999999999999956 441 0.99999999999999956 
		450 0.99999999999999956 464 0.99999999999999956 480 0.99999999999999956 492 0.99999999999999956 
		504 0.99999999999999956 510 0.99999999999999956 620 0.99999999999999956 626 0.99999999999999956 
		630 0.99999999999999956 638 0.99999999999999956 670 0.99999999999999956 680 0.99999999999999956 
		690 0.99999999999999956 706 0.99999999999999956 720 0.99999999999999956 750 0.99999999999999956 
		760 0.99999999999999956 790 0.99999999999999956 800 0.99999999999999956 810 0.99999999999999956 
		821 0.99999999999999956 830 0.99999999999999956 837 0.99999999999999956 843 0.99999999999999956 
		850 0.99999999999999956 860 0.99999999999999956 875 0.99999999999999956 890 0.99999999999999956 
		905 0.99999999999999956 912 0.99999999999999956 920 0.99999999999999956 930 0.99999999999999956 
		937 0.99999999999999956 950 0.99999999999999956 970 0.99999999999999956;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1810";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 370 1 380 1 400 1 420 1 428 1 441 
		1 450 1 464 1 480 1 492 1 504 1 510 1 620 1 626 1 630 1 638 1 670 1 680 1 690 1 706 
		1 720 1 750 1 760 1 790 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 1 890 
		1 905 1 912 1 920 1 930 1 937 1 950 1 970 1;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3483";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 2.735941457 50 2.735941457 65 2.735941457 
		81 2.735941457 140 2.735941457 150 2.735941457 160 2.735941457 168 2.735941457 178 
		2.735941457 230 2.735941457 242 2.735941457 275 2.735941457 290 2.735941457 300 2.735941457 
		350 2.735941457 360 2.735941457 370 2.735941457 380 2.735941457 400 2.735941457 420 
		2.735941457 428 2.735941457 441 2.735941457 450 2.735941457 464 2.735941457 480 2.735941457 
		492 2.735941457 504 2.735941457 510 2.735941457 620 2.735941457 626 2.735941457 630 
		2.735941457 638 2.735941457 670 2.735941457 680 2.735941457 690 2.735941457 706 2.735941457 
		720 2.735941457 750 2.735941457 760 2.735941457 790 2.735941457 800 2.735941457 810 
		2.735941457 821 2.735941457 830 2.735941457 837 2.735941457 843 2.735941457 850 2.735941457 
		860 2.735941457 875 2.735941457 890 2.735941457 905 2.735941457 912 2.735941457 920 
		2.735941457 930 2.735941457 937 2.735941457 950 2.735941457 970 2.735941457;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3484";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 -18.208718699999999 50 -18.208718699999999 
		65 -18.208718699999999 81 -18.208718699999999 140 -18.208718699999999 150 -18.208718699999999 
		160 -18.208718699999999 168 -18.208718699999999 178 -18.208718699999999 230 -18.208718699999999 
		242 -18.208718699999999 275 -18.208718699999999 290 -18.208718699999999 300 -18.208718699999999 
		350 -18.208718699999999 360 -18.208718699999999 370 -18.208718699999999 380 -18.208718699999999 
		400 -18.208718699999999 420 -18.208718699999999 428 -18.208718699999999 441 -18.208718699999999 
		450 -18.208718699999999 464 -18.208718699999999 480 -18.208718699999999 492 -18.208718699999999 
		504 -18.208718699999999 510 -18.208718699999999 620 -18.208718699999999 626 -18.208718699999999 
		630 -18.208718699999999 638 -18.208718699999999 670 -18.208718699999999 680 -18.208718699999999 
		690 -18.208718699999999 706 -18.208718699999999 720 -18.208718699999999 750 -18.208718699999999 
		760 -18.208718699999999 790 -18.208718699999999 800 -18.208718699999999 810 -18.208718699999999 
		821 -18.208718699999999 830 -18.208718699999999 837 -18.208718699999999 843 -18.208718699999999 
		850 -18.208718699999999 860 -18.208718699999999 875 -18.208718699999999 890 -18.208718699999999 
		905 -18.208718699999999 912 -18.208718699999999 920 -18.208718699999999 930 -18.208718699999999 
		937 -18.208718699999999 950 -18.208718699999999 970 -18.208718699999999;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3485";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 36.37463082 50 36.37463082 65 36.37463082 
		81 36.37463082 140 36.37463082 150 36.37463082 160 36.37463082 168 36.37463082 178 
		36.37463082 230 36.37463082 242 36.37463082 275 36.37463082 290 36.37463082 300 36.37463082 
		350 36.37463082 360 36.37463082 370 36.37463082 380 36.37463082 400 36.37463082 420 
		36.37463082 428 36.37463082 441 36.37463082 450 36.37463082 464 36.37463082 480 36.37463082 
		492 36.37463082 504 36.37463082 510 36.37463082 620 36.37463082 626 36.37463082 630 
		36.37463082 638 36.37463082 670 36.37463082 680 36.37463082 690 36.37463082 706 36.37463082 
		720 36.37463082 750 36.37463082 760 36.37463082 790 36.37463082 800 36.37463082 810 
		36.37463082 821 36.37463082 830 36.37463082 837 36.37463082 843 36.37463082 850 36.37463082 
		860 36.37463082 875 36.37463082 890 36.37463082 905 36.37463082 912 36.37463082 920 
		36.37463082 930 36.37463082 937 36.37463082 950 36.37463082 970 36.37463082;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3486";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3487";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3488";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1811";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.99999999999999967 50 0.99999999999999967 
		65 0.99999999999999967 81 0.99999999999999967 140 0.99999999999999967 150 0.99999999999999967 
		160 0.99999999999999967 168 0.99999999999999967 178 0.99999999999999967 230 0.99999999999999967 
		242 0.99999999999999967 275 0.99999999999999967 290 0.99999999999999967 300 0.99999999999999967 
		350 0.99999999999999967 360 0.99999999999999967 370 0.99999999999999967 380 0.99999999999999967 
		400 0.99999999999999967 420 0.99999999999999967 428 0.99999999999999967 441 0.99999999999999967 
		450 0.99999999999999967 464 0.99999999999999967 480 0.99999999999999967 492 0.99999999999999967 
		504 0.99999999999999967 510 0.99999999999999967 620 0.99999999999999967 626 0.99999999999999967 
		630 0.99999999999999967 638 0.99999999999999967 670 0.99999999999999967 680 0.99999999999999967 
		690 0.99999999999999967 706 0.99999999999999967 720 0.99999999999999967 750 0.99999999999999967 
		760 0.99999999999999967 790 0.99999999999999967 800 0.99999999999999967 810 0.99999999999999967 
		821 0.99999999999999967 830 0.99999999999999967 837 0.99999999999999967 843 0.99999999999999967 
		850 0.99999999999999967 860 0.99999999999999967 875 0.99999999999999967 890 0.99999999999999967 
		905 0.99999999999999967 912 0.99999999999999967 920 0.99999999999999967 930 0.99999999999999967 
		937 0.99999999999999967 950 0.99999999999999967 970 0.99999999999999967;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1812";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.99999999999999989 50 0.99999999999999989 
		65 0.99999999999999989 81 0.99999999999999989 140 0.99999999999999989 150 0.99999999999999989 
		160 0.99999999999999989 168 0.99999999999999989 178 0.99999999999999989 230 0.99999999999999989 
		242 0.99999999999999989 275 0.99999999999999989 290 0.99999999999999989 300 0.99999999999999989 
		350 0.99999999999999989 360 0.99999999999999989 370 0.99999999999999989 380 0.99999999999999989 
		400 0.99999999999999989 420 0.99999999999999989 428 0.99999999999999989 441 0.99999999999999989 
		450 0.99999999999999989 464 0.99999999999999989 480 0.99999999999999989 492 0.99999999999999989 
		504 0.99999999999999989 510 0.99999999999999989 620 0.99999999999999989 626 0.99999999999999989 
		630 0.99999999999999989 638 0.99999999999999989 670 0.99999999999999989 680 0.99999999999999989 
		690 0.99999999999999989 706 0.99999999999999989 720 0.99999999999999989 750 0.99999999999999989 
		760 0.99999999999999989 790 0.99999999999999989 800 0.99999999999999989 810 0.99999999999999989 
		821 0.99999999999999989 830 0.99999999999999989 837 0.99999999999999989 843 0.99999999999999989 
		850 0.99999999999999989 860 0.99999999999999989 875 0.99999999999999989 890 0.99999999999999989 
		905 0.99999999999999989 912 0.99999999999999989 920 0.99999999999999989 930 0.99999999999999989 
		937 0.99999999999999989 950 0.99999999999999989 970 0.99999999999999989;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1813";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0.99999999999999989 50 0.99999999999999989 
		65 0.99999999999999989 81 0.99999999999999989 140 0.99999999999999989 150 0.99999999999999989 
		160 0.99999999999999989 168 0.99999999999999989 178 0.99999999999999989 230 0.99999999999999989 
		242 0.99999999999999989 275 0.99999999999999989 290 0.99999999999999989 300 0.99999999999999989 
		350 0.99999999999999989 360 0.99999999999999989 370 0.99999999999999989 380 0.99999999999999989 
		400 0.99999999999999989 420 0.99999999999999989 428 0.99999999999999989 441 0.99999999999999989 
		450 0.99999999999999989 464 0.99999999999999989 480 0.99999999999999989 492 0.99999999999999989 
		504 0.99999999999999989 510 0.99999999999999989 620 0.99999999999999989 626 0.99999999999999989 
		630 0.99999999999999989 638 0.99999999999999989 670 0.99999999999999989 680 0.99999999999999989 
		690 0.99999999999999989 706 0.99999999999999989 720 0.99999999999999989 750 0.99999999999999989 
		760 0.99999999999999989 790 0.99999999999999989 800 0.99999999999999989 810 0.99999999999999989 
		821 0.99999999999999989 830 0.99999999999999989 837 0.99999999999999989 843 0.99999999999999989 
		850 0.99999999999999989 860 0.99999999999999989 875 0.99999999999999989 890 0.99999999999999989 
		905 0.99999999999999989 912 0.99999999999999989 920 0.99999999999999989 930 0.99999999999999989 
		937 0.99999999999999989 950 0.99999999999999989 970 0.99999999999999989;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3489";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 21.723568696251505 50 21.723568696251505 
		65 21.723568696251505 81 21.723568696251505 140 21.723568696251505 150 21.723568696251505 
		160 21.723568696251505 168 21.723568696251505 178 21.723568696251505 230 21.723568696251505 
		242 21.723568696251505 275 21.723568696251505 290 21.723568696251505 300 21.723568696251505 
		350 21.723568696251505 360 21.723568696251505 370 21.723568696251505 380 21.723568696251505 
		400 21.723568696251505 420 21.723568696251505 428 21.723568696251505 441 21.723568696251505 
		450 21.723568696251505 464 21.723568696251505 480 21.723568696251505 492 21.723568696251505 
		504 21.723568696251505 510 21.723568696251505 620 21.723568696251505 626 21.723568696251505 
		630 21.723568696251505 638 21.723568696251505 670 21.723568696251505 680 21.723568696251505 
		690 21.723568696251505 706 21.723568696251505 720 21.723568696251505 750 21.723568696251505 
		760 21.723568696251505 790 21.723568696251505 800 21.723568696251505 810 21.723568696251505 
		821 21.723568696251505 830 21.723568696251505 837 21.723568696251505 843 21.723568696251505 
		850 21.723568696251505 860 21.723568696251505 875 21.723568696251505 890 21.723568696251505 
		905 21.723568696251505 912 21.723568696251505 920 21.723568696251505 930 21.723568696251505 
		937 21.723568696251505 950 21.723568696251505 970 21.723568696251505;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3490";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 -5.7652344785195542 50 -5.7652344785195542 
		65 -5.7652344785195542 81 -5.7652344785195542 140 -5.7652344785195542 150 -5.7652344785195542 
		160 -5.7652344785195542 168 -5.7652344785195542 178 -5.7652344785195542 230 -5.7652344785195542 
		242 -5.7652344785195542 275 -5.7652344785195542 290 -5.7652344785195542 300 -5.7652344785195542 
		350 -5.7652344785195542 360 -5.7652344785195542 370 -5.7652344785195542 380 -5.7652344785195542 
		400 -5.7652344785195542 420 -5.7652344785195542 428 -5.7652344785195542 441 -5.7652344785195542 
		450 -5.7652344785195542 464 -5.7652344785195542 480 -5.7652344785195542 492 -5.7652344785195542 
		504 -5.7652344785195542 510 -5.7652344785195542 620 -5.7652344785195542 626 -5.7652344785195542 
		630 -5.7652344785195542 638 -5.7652344785195542 670 -5.7652344785195542 680 -5.7652344785195542 
		690 -5.7652344785195542 706 -5.7652344785195542 720 -5.7652344785195542 750 -5.7652344785195542 
		760 -5.7652344785195542 790 -5.7652344785195542 800 -5.7652344785195542 810 -5.7652344785195542 
		821 -5.7652344785195542 830 -5.7652344785195542 837 -5.7652344785195542 843 -5.7652344785195542 
		850 -5.7652344785195542 860 -5.7652344785195542 875 -5.7652344785195542 890 -5.7652344785195542 
		905 -5.7652344785195542 912 -5.7652344785195542 920 -5.7652344785195542 930 -5.7652344785195542 
		937 -5.7652344785195542 950 -5.7652344785195542 970 -5.7652344785195542;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3491";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 24.323700513426093 50 24.323700513426093 
		65 24.323700513426093 81 24.323700513426093 140 24.323700513426093 150 24.323700513426093 
		160 24.323700513426093 168 24.323700513426093 178 24.323700513426093 230 24.323700513426093 
		242 24.323700513426093 275 24.323700513426093 290 24.323700513426093 300 24.323700513426093 
		350 24.323700513426093 360 24.323700513426093 370 24.323700513426093 380 24.323700513426093 
		400 24.323700513426093 420 24.323700513426093 428 24.323700513426093 441 24.323700513426093 
		450 24.323700513426093 464 24.323700513426093 480 24.323700513426093 492 24.323700513426093 
		504 24.323700513426093 510 24.323700513426093 620 24.323700513426093 626 24.323700513426093 
		630 24.323700513426093 638 24.323700513426093 670 24.323700513426093 680 24.323700513426093 
		690 24.323700513426093 706 24.323700513426093 720 24.323700513426093 750 24.323700513426093 
		760 24.323700513426093 790 24.323700513426093 800 24.323700513426093 810 24.323700513426093 
		821 24.323700513426093 830 24.323700513426093 837 24.323700513426093 843 24.323700513426093 
		850 24.323700513426093 860 24.323700513426093 875 24.323700513426093 890 24.323700513426093 
		905 24.323700513426093 912 24.323700513426093 920 24.323700513426093 930 24.323700513426093 
		937 24.323700513426093 950 24.323700513426093 970 24.323700513426093;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3492";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3493";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3494";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1814";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 370 1 380 1 400 1 420 1 428 1 441 
		1 450 1 464 1 480 1 492 1 504 1 510 1 620 1 626 1 630 1 638 1 670 1 680 1 690 1 706 
		1 720 1 750 1 760 1 790 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 1 890 
		1 905 1 912 1 920 1 930 1 937 1 950 1 970 1;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1815";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 1.0000000000000002 50 1.0000000000000002 
		65 1.0000000000000002 81 1.0000000000000002 140 1.0000000000000002 150 1.0000000000000002 
		160 1.0000000000000002 168 1.0000000000000002 178 1.0000000000000002 230 1.0000000000000002 
		242 1.0000000000000002 275 1.0000000000000002 290 1.0000000000000002 300 1.0000000000000002 
		350 1.0000000000000002 360 1.0000000000000002 370 1.0000000000000002 380 1.0000000000000002 
		400 1.0000000000000002 420 1.0000000000000002 428 1.0000000000000002 441 1.0000000000000002 
		450 1.0000000000000002 464 1.0000000000000002 480 1.0000000000000002 492 1.0000000000000002 
		504 1.0000000000000002 510 1.0000000000000002 620 1.0000000000000002 626 1.0000000000000002 
		630 1.0000000000000002 638 1.0000000000000002 670 1.0000000000000002 680 1.0000000000000002 
		690 1.0000000000000002 706 1.0000000000000002 720 1.0000000000000002 750 1.0000000000000002 
		760 1.0000000000000002 790 1.0000000000000002 800 1.0000000000000002 810 1.0000000000000002 
		821 1.0000000000000002 830 1.0000000000000002 837 1.0000000000000002 843 1.0000000000000002 
		850 1.0000000000000002 860 1.0000000000000002 875 1.0000000000000002 890 1.0000000000000002 
		905 1.0000000000000002 912 1.0000000000000002 920 1.0000000000000002 930 1.0000000000000002 
		937 1.0000000000000002 950 1.0000000000000002 970 1.0000000000000002;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1816";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 1.0000000000000002 50 1.0000000000000002 
		65 1.0000000000000002 81 1.0000000000000002 140 1.0000000000000002 150 1.0000000000000002 
		160 1.0000000000000002 168 1.0000000000000002 178 1.0000000000000002 230 1.0000000000000002 
		242 1.0000000000000002 275 1.0000000000000002 290 1.0000000000000002 300 1.0000000000000002 
		350 1.0000000000000002 360 1.0000000000000002 370 1.0000000000000002 380 1.0000000000000002 
		400 1.0000000000000002 420 1.0000000000000002 428 1.0000000000000002 441 1.0000000000000002 
		450 1.0000000000000002 464 1.0000000000000002 480 1.0000000000000002 492 1.0000000000000002 
		504 1.0000000000000002 510 1.0000000000000002 620 1.0000000000000002 626 1.0000000000000002 
		630 1.0000000000000002 638 1.0000000000000002 670 1.0000000000000002 680 1.0000000000000002 
		690 1.0000000000000002 706 1.0000000000000002 720 1.0000000000000002 750 1.0000000000000002 
		760 1.0000000000000002 790 1.0000000000000002 800 1.0000000000000002 810 1.0000000000000002 
		821 1.0000000000000002 830 1.0000000000000002 837 1.0000000000000002 843 1.0000000000000002 
		850 1.0000000000000002 860 1.0000000000000002 875 1.0000000000000002 890 1.0000000000000002 
		905 1.0000000000000002 912 1.0000000000000002 920 1.0000000000000002 930 1.0000000000000002 
		937 1.0000000000000002 950 1.0000000000000002 970 1.0000000000000002;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3495";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3496";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTA -n "animCurveTA3497";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 57 ".ktv[0:56]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 638 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 930 0 937 0 950 0 970 0;
	setAttr -s 57 ".kit[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kot[35:56]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 57 ".kix[56]"  1;
	setAttr -s 57 ".kiy[56]"  0;
	setAttr -s 57 ".kox[56]"  1;
	setAttr -s 57 ".koy[56]"  0;
createNode animCurveTU -n "animCurveTU1817";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 56 ".ktv[0:55]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 370 1 380 1 400 1 420 1 428 1 441 
		1 450 1 464 1 480 1 492 1 504 1 510 1 620 1 626 1 630 1 640 1 670 1 680 1 690 1 706 
		1 720 1 750 1 760 1 790 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 1 890 
		1 905 1 912 1 920 1 937 1 950 1 970 1;
	setAttr -s 56 ".kit[35:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kot[35:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kix[55]"  1;
	setAttr -s 56 ".kiy[55]"  0;
	setAttr -s 56 ".kox[55]"  1;
	setAttr -s 56 ".koy[55]"  0;
createNode animCurveTU -n "animCurveTU1818";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 56 ".ktv[0:55]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 370 1 380 1 400 1 420 1 428 1 441 
		1 450 1 464 1 480 1 492 1 504 1 510 1 620 1 626 1 630 1 640 1 670 1 680 1 690 1 706 
		1 720 1 750 1 760 1 790 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 1 890 
		1 905 1 912 1 920 1 937 1 950 1 970 1;
	setAttr -s 56 ".kit[35:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kot[35:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kix[55]"  1;
	setAttr -s 56 ".kiy[55]"  0;
	setAttr -s 56 ".kox[55]"  1;
	setAttr -s 56 ".koy[55]"  0;
createNode animCurveTU -n "animCurveTU1819";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 56 ".ktv[0:55]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 370 1 380 1 400 1 420 1 428 1 441 
		1 450 1 464 1 480 1 492 1 504 1 510 1 620 1 626 1 630 1 640 1 670 1 680 1 690 1 706 
		1 720 1 750 1 760 1 790 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 1 890 
		1 905 1 912 1 920 1 937 1 950 1 970 1;
	setAttr -s 56 ".kit[35:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kot[35:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kix[55]"  1;
	setAttr -s 56 ".kiy[55]"  0;
	setAttr -s 56 ".kox[55]"  1;
	setAttr -s 56 ".koy[55]"  0;
createNode animCurveTA -n "animCurveTA3498";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 56 ".ktv[0:55]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 640 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 937 0 950 0 970 0;
	setAttr -s 56 ".kit[35:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kot[35:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kix[55]"  1;
	setAttr -s 56 ".kiy[55]"  0;
	setAttr -s 56 ".kox[55]"  1;
	setAttr -s 56 ".koy[55]"  0;
createNode animCurveTA -n "animCurveTA3499";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 56 ".ktv[0:55]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 640 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 937 0 950 0 970 0;
	setAttr -s 56 ".kit[35:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kot[35:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kix[55]"  1;
	setAttr -s 56 ".kiy[55]"  0;
	setAttr -s 56 ".kox[55]"  1;
	setAttr -s 56 ".koy[55]"  0;
createNode animCurveTA -n "animCurveTA3500";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 56 ".ktv[0:55]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 640 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 937 0 950 0 970 0;
	setAttr -s 56 ".kit[35:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kot[35:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kix[55]"  1;
	setAttr -s 56 ".kiy[55]"  0;
	setAttr -s 56 ".kox[55]"  1;
	setAttr -s 56 ".koy[55]"  0;
createNode animCurveTL -n "animCurveTL1168";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 56 ".ktv[0:55]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 640 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 937 0 950 0 970 0;
	setAttr -s 56 ".kit[35:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kot[35:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kix[55]"  1;
	setAttr -s 56 ".kiy[55]"  0;
	setAttr -s 56 ".kox[55]"  1;
	setAttr -s 56 ".koy[55]"  0;
createNode animCurveTL -n "animCurveTL1169";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 56 ".ktv[0:55]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 640 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 937 0 950 0 970 0;
	setAttr -s 56 ".kit[35:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kot[35:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kix[55]"  1;
	setAttr -s 56 ".kiy[55]"  0;
	setAttr -s 56 ".kox[55]"  1;
	setAttr -s 56 ".koy[55]"  0;
createNode animCurveTL -n "animCurveTL1170";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 56 ".ktv[0:55]"  0 0 50 0 65 0 81 0 140 0 150 0 160 0 168 
		0 178 0 230 0 242 0 275 0 290 0 300 0 350 0 360 0 370 0 380 0 400 0 420 0 428 0 441 
		0 450 0 464 0 480 0 492 0 504 0 510 0 620 0 626 0 630 0 640 0 670 0 680 0 690 0 706 
		0 720 0 750 0 760 0 790 0 800 0 810 0 821 0 830 0 837 0 843 0 850 0 860 0 875 0 890 
		0 905 0 912 0 920 0 937 0 950 0 970 0;
	setAttr -s 56 ".kit[35:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kot[35:55]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 1;
	setAttr -s 56 ".kix[55]"  1;
	setAttr -s 56 ".kiy[55]"  0;
	setAttr -s 56 ".kox[55]"  1;
	setAttr -s 56 ".koy[55]"  0;
createNode animCurveTU -n "animCurveTU1820";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 56 ".ktv[0:55]"  0 1 50 1 65 1 81 1 140 1 150 1 160 1 168 
		1 178 1 230 1 242 1 275 1 290 1 300 1 350 1 360 1 370 1 380 1 400 1 420 1 428 1 441 
		1 450 1 464 1 480 1 492 1 504 1 510 1 620 1 626 1 630 1 640 1 670 1 680 1 690 1 706 
		1 720 1 750 1 760 1 790 1 800 1 810 1 821 1 830 1 837 1 843 1 850 1 860 1 875 1 890 
		1 905 1 912 1 920 1 937 1 950 1 970 1;
	setAttr -s 56 ".kit[55]"  1;
	setAttr -s 56 ".kot[0:55]"  5 5 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 9 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 5 5 5 5;
	setAttr -s 56 ".kix[55]"  1;
	setAttr -s 56 ".kiy[55]"  0;
createNode lightLinker -n "lightLinker1";
	setAttr -s 5 ".lnk";
	setAttr -s 5 ".slnk";
createNode lightLinker -n "_1:lightLinker1";
	setAttr -s 6 ".lnk";
	setAttr -s 6 ".slnk";
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
	setAttr -s 9 ".st";
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
	setAttr -s 9 ".s";
select -ne :postProcessList1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -s 9 ".u";
select -ne :lightList1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 2 ".ln";
select -ne :defaultTextureList1;
	setAttr -s 8 ".tx";
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
	setAttr -s 5 ".gn";
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
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -av ".w";
	setAttr -av ".h";
	setAttr ".pa" 1;
	setAttr -k on ".al";
	setAttr -av ".dar";
	setAttr -k on ".off";
	setAttr -k on ".fld";
	setAttr -k on ".zsl";
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
connectAttr "Minigame2_idleBigSource.cl" "clipLibrary1.sc[0]";
connectAttr "animCurveTA3151.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "animCurveTA3152.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "animCurveTA3153.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "animCurveTA3154.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "animCurveTA3155.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "animCurveTA3156.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "animCurveTA3157.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "animCurveTA3158.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "animCurveTA3159.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "animCurveTA3160.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "animCurveTA3161.a" "clipLibrary1.cel[0].cev[10].cevr";
connectAttr "animCurveTA3162.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "animCurveTA3163.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "animCurveTA3164.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "animCurveTA3165.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "animCurveTA3166.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "animCurveTA3167.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "animCurveTA3168.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "animCurveTA3169.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "animCurveTA3170.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "animCurveTA3171.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "animCurveTA3172.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "animCurveTA3173.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "animCurveTA3174.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "animCurveTA3175.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "animCurveTA3176.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "animCurveTA3177.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "animCurveTA3178.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "animCurveTA3179.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "animCurveTA3180.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "animCurveTA3181.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "animCurveTA3182.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "animCurveTA3183.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "animCurveTA3184.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "animCurveTA3185.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "animCurveTA3186.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "animCurveTA3187.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "animCurveTA3188.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "animCurveTA3189.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "animCurveTL1054.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "animCurveTL1055.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "animCurveTL1056.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "animCurveTA3190.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "animCurveTA3191.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "animCurveTA3192.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "animCurveTL1057.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "animCurveTL1058.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "animCurveTL1059.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "animCurveTA3193.a" "clipLibrary1.cel[0].cev[48].cevr";
connectAttr "animCurveTA3194.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "animCurveTA3195.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "animCurveTL1060.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "animCurveTL1061.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "animCurveTL1062.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "animCurveTA3196.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "animCurveTA3197.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "animCurveTA3198.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "animCurveTL1063.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "animCurveTL1064.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "animCurveTL1065.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "animCurveTA3199.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "animCurveTA3200.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "animCurveTA3201.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "animCurveTL1066.a" "clipLibrary1.cel[0].cev[63].cevr";
connectAttr "animCurveTL1067.a" "clipLibrary1.cel[0].cev[64].cevr";
connectAttr "animCurveTL1068.a" "clipLibrary1.cel[0].cev[65].cevr";
connectAttr "animCurveTA3202.a" "clipLibrary1.cel[0].cev[66].cevr";
connectAttr "animCurveTA3203.a" "clipLibrary1.cel[0].cev[67].cevr";
connectAttr "animCurveTA3204.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "animCurveTL1069.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "animCurveTL1070.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "animCurveTL1071.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "animCurveTA3205.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "animCurveTA3206.a" "clipLibrary1.cel[0].cev[73].cevr";
connectAttr "animCurveTA3207.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "animCurveTL1072.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "animCurveTL1073.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "animCurveTL1074.a" "clipLibrary1.cel[0].cev[77].cevr";
connectAttr "animCurveTA3208.a" "clipLibrary1.cel[0].cev[78].cevr";
connectAttr "animCurveTA3209.a" "clipLibrary1.cel[0].cev[79].cevr";
connectAttr "animCurveTA3210.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "animCurveTL1075.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "animCurveTL1076.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "animCurveTL1077.a" "clipLibrary1.cel[0].cev[83].cevr";
connectAttr "animCurveTA3211.a" "clipLibrary1.cel[0].cev[84].cevr";
connectAttr "animCurveTA3212.a" "clipLibrary1.cel[0].cev[85].cevr";
connectAttr "animCurveTA3213.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "animCurveTL1078.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "animCurveTL1079.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "animCurveTL1080.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr "animCurveTA3214.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "animCurveTA3215.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "animCurveTA3216.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "animCurveTL1081.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "animCurveTL1082.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "animCurveTL1083.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "animCurveTU1639.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "animCurveTA3217.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "animCurveTA3218.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "animCurveTA3219.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "animCurveTL1084.a" "clipLibrary1.cel[0].cev[100].cevr";
connectAttr "animCurveTL1085.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "animCurveTL1086.a" "clipLibrary1.cel[0].cev[102].cevr";
connectAttr "animCurveTA3220.a" "clipLibrary1.cel[0].cev[103].cevr";
connectAttr "animCurveTA3221.a" "clipLibrary1.cel[0].cev[104].cevr";
connectAttr "animCurveTA3222.a" "clipLibrary1.cel[0].cev[105].cevr";
connectAttr "animCurveTL1087.a" "clipLibrary1.cel[0].cev[106].cevr";
connectAttr "animCurveTL1088.a" "clipLibrary1.cel[0].cev[107].cevr";
connectAttr "animCurveTL1089.a" "clipLibrary1.cel[0].cev[108].cevr";
connectAttr "animCurveTU1640.a" "clipLibrary1.cel[0].cev[109].cevr";
connectAttr "animCurveTU1641.a" "clipLibrary1.cel[0].cev[110].cevr";
connectAttr "animCurveTU1642.a" "clipLibrary1.cel[0].cev[111].cevr";
connectAttr "animCurveTU1643.a" "clipLibrary1.cel[0].cev[112].cevr";
connectAttr "animCurveTU1644.a" "clipLibrary1.cel[0].cev[113].cevr";
connectAttr "animCurveTU1645.a" "clipLibrary1.cel[0].cev[114].cevr";
connectAttr "animCurveTU1646.a" "clipLibrary1.cel[0].cev[115].cevr";
connectAttr "animCurveTA3223.a" "clipLibrary1.cel[0].cev[116].cevr";
connectAttr "animCurveTA3224.a" "clipLibrary1.cel[0].cev[117].cevr";
connectAttr "animCurveTA3225.a" "clipLibrary1.cel[0].cev[118].cevr";
connectAttr "animCurveTA3226.a" "clipLibrary1.cel[0].cev[119].cevr";
connectAttr "animCurveTA3227.a" "clipLibrary1.cel[0].cev[120].cevr";
connectAttr "animCurveTA3228.a" "clipLibrary1.cel[0].cev[121].cevr";
connectAttr "animCurveTA3229.a" "clipLibrary1.cel[0].cev[122].cevr";
connectAttr "animCurveTA3230.a" "clipLibrary1.cel[0].cev[123].cevr";
connectAttr "animCurveTA3231.a" "clipLibrary1.cel[0].cev[124].cevr";
connectAttr "animCurveTA3232.a" "clipLibrary1.cel[0].cev[125].cevr";
connectAttr "animCurveTA3233.a" "clipLibrary1.cel[0].cev[126].cevr";
connectAttr "animCurveTA3234.a" "clipLibrary1.cel[0].cev[127].cevr";
connectAttr "animCurveTA3235.a" "clipLibrary1.cel[0].cev[128].cevr";
connectAttr "animCurveTA3236.a" "clipLibrary1.cel[0].cev[129].cevr";
connectAttr "animCurveTA3237.a" "clipLibrary1.cel[0].cev[130].cevr";
connectAttr "animCurveTA3238.a" "clipLibrary1.cel[0].cev[131].cevr";
connectAttr "animCurveTU1647.a" "clipLibrary1.cel[0].cev[132].cevr";
connectAttr "animCurveTU1648.a" "clipLibrary1.cel[0].cev[133].cevr";
connectAttr "animCurveTU1649.a" "clipLibrary1.cel[0].cev[134].cevr";
connectAttr "animCurveTL1090.a" "clipLibrary1.cel[0].cev[135].cevr";
connectAttr "animCurveTL1091.a" "clipLibrary1.cel[0].cev[136].cevr";
connectAttr "animCurveTL1092.a" "clipLibrary1.cel[0].cev[137].cevr";
connectAttr "animCurveTU1650.a" "clipLibrary1.cel[0].cev[138].cevr";
connectAttr "animCurveTL1093.a" "clipLibrary1.cel[0].cev[139].cevr";
connectAttr "animCurveTL1094.a" "clipLibrary1.cel[0].cev[140].cevr";
connectAttr "animCurveTL1095.a" "clipLibrary1.cel[0].cev[141].cevr";
connectAttr "animCurveTA3239.a" "clipLibrary1.cel[0].cev[142].cevr";
connectAttr "animCurveTA3240.a" "clipLibrary1.cel[0].cev[143].cevr";
connectAttr "animCurveTA3241.a" "clipLibrary1.cel[0].cev[144].cevr";
connectAttr "animCurveTL1096.a" "clipLibrary1.cel[0].cev[145].cevr";
connectAttr "animCurveTL1097.a" "clipLibrary1.cel[0].cev[146].cevr";
connectAttr "animCurveTL1098.a" "clipLibrary1.cel[0].cev[147].cevr";
connectAttr "animCurveTU1651.a" "clipLibrary1.cel[0].cev[148].cevr";
connectAttr "animCurveTU1652.a" "clipLibrary1.cel[0].cev[149].cevr";
connectAttr "animCurveTU1653.a" "clipLibrary1.cel[0].cev[150].cevr";
connectAttr "animCurveTU1654.a" "clipLibrary1.cel[0].cev[151].cevr";
connectAttr "animCurveTU1655.a" "clipLibrary1.cel[0].cev[152].cevr";
connectAttr "animCurveTU1656.a" "clipLibrary1.cel[0].cev[153].cevr";
connectAttr "animCurveTU1657.a" "clipLibrary1.cel[0].cev[154].cevr";
connectAttr "animCurveTU1658.a" "clipLibrary1.cel[0].cev[155].cevr";
connectAttr "animCurveTA3242.a" "clipLibrary1.cel[0].cev[156].cevr";
connectAttr "animCurveTA3243.a" "clipLibrary1.cel[0].cev[157].cevr";
connectAttr "animCurveTA3244.a" "clipLibrary1.cel[0].cev[158].cevr";
connectAttr "animCurveTL1099.a" "clipLibrary1.cel[0].cev[159].cevr";
connectAttr "animCurveTL1100.a" "clipLibrary1.cel[0].cev[160].cevr";
connectAttr "animCurveTL1101.a" "clipLibrary1.cel[0].cev[161].cevr";
connectAttr "animCurveTU1659.a" "clipLibrary1.cel[0].cev[162].cevr";
connectAttr "animCurveTU1660.a" "clipLibrary1.cel[0].cev[163].cevr";
connectAttr "animCurveTU1661.a" "clipLibrary1.cel[0].cev[164].cevr";
connectAttr "animCurveTL1102.a" "clipLibrary1.cel[0].cev[165].cevr";
connectAttr "animCurveTL1103.a" "clipLibrary1.cel[0].cev[166].cevr";
connectAttr "animCurveTL1104.a" "clipLibrary1.cel[0].cev[167].cevr";
connectAttr "animCurveTU1662.a" "clipLibrary1.cel[0].cev[168].cevr";
connectAttr "animCurveTL1105.a" "clipLibrary1.cel[0].cev[169].cevr";
connectAttr "animCurveTL1106.a" "clipLibrary1.cel[0].cev[170].cevr";
connectAttr "animCurveTL1107.a" "clipLibrary1.cel[0].cev[171].cevr";
connectAttr "animCurveTA3245.a" "clipLibrary1.cel[0].cev[172].cevr";
connectAttr "animCurveTA3246.a" "clipLibrary1.cel[0].cev[173].cevr";
connectAttr "animCurveTA3247.a" "clipLibrary1.cel[0].cev[174].cevr";
connectAttr "animCurveTL1108.a" "clipLibrary1.cel[0].cev[175].cevr";
connectAttr "animCurveTL1109.a" "clipLibrary1.cel[0].cev[176].cevr";
connectAttr "animCurveTL1110.a" "clipLibrary1.cel[0].cev[177].cevr";
connectAttr "animCurveTU1663.a" "clipLibrary1.cel[0].cev[178].cevr";
connectAttr "animCurveTU1664.a" "clipLibrary1.cel[0].cev[179].cevr";
connectAttr "animCurveTU1665.a" "clipLibrary1.cel[0].cev[180].cevr";
connectAttr "animCurveTU1666.a" "clipLibrary1.cel[0].cev[181].cevr";
connectAttr "animCurveTU1667.a" "clipLibrary1.cel[0].cev[182].cevr";
connectAttr "animCurveTA3248.a" "clipLibrary1.cel[0].cev[183].cevr";
connectAttr "animCurveTA3249.a" "clipLibrary1.cel[0].cev[184].cevr";
connectAttr "animCurveTA3250.a" "clipLibrary1.cel[0].cev[185].cevr";
connectAttr "animCurveTL1111.a" "clipLibrary1.cel[0].cev[186].cevr";
connectAttr "animCurveTL1112.a" "clipLibrary1.cel[0].cev[187].cevr";
connectAttr "animCurveTL1113.a" "clipLibrary1.cel[0].cev[188].cevr";
connectAttr "animCurveTU1668.a" "clipLibrary1.cel[0].cev[189].cevr";
connectAttr "animCurveTU1669.a" "clipLibrary1.cel[0].cev[190].cevr";
connectAttr "animCurveTU1670.a" "clipLibrary1.cel[0].cev[191].cevr";
connectAttr "animCurveTU1671.a" "clipLibrary1.cel[0].cev[192].cevr";
connectAttr "animCurveTU1672.a" "clipLibrary1.cel[0].cev[193].cevr";
connectAttr "animCurveTU1673.a" "clipLibrary1.cel[0].cev[194].cevr";
connectAttr "animCurveTU1674.a" "clipLibrary1.cel[0].cev[195].cevr";
connectAttr "animCurveTU1675.a" "clipLibrary1.cel[0].cev[196].cevr";
connectAttr "animCurveTU1676.a" "clipLibrary1.cel[0].cev[197].cevr";
connectAttr "animCurveTU1677.a" "clipLibrary1.cel[0].cev[198].cevr";
connectAttr "animCurveTA3251.a" "clipLibrary1.cel[0].cev[199].cevr";
connectAttr "animCurveTA3252.a" "clipLibrary1.cel[0].cev[200].cevr";
connectAttr "animCurveTA3253.a" "clipLibrary1.cel[0].cev[201].cevr";
connectAttr "animCurveTL1114.a" "clipLibrary1.cel[0].cev[202].cevr";
connectAttr "animCurveTL1115.a" "clipLibrary1.cel[0].cev[203].cevr";
connectAttr "animCurveTL1116.a" "clipLibrary1.cel[0].cev[204].cevr";
connectAttr "animCurveTU1678.a" "clipLibrary1.cel[0].cev[205].cevr";
connectAttr "animCurveTU1679.a" "clipLibrary1.cel[0].cev[206].cevr";
connectAttr "animCurveTU1680.a" "clipLibrary1.cel[0].cev[207].cevr";
connectAttr "animCurveTA3254.a" "clipLibrary1.cel[0].cev[208].cevr";
connectAttr "animCurveTA3255.a" "clipLibrary1.cel[0].cev[209].cevr";
connectAttr "animCurveTA3256.a" "clipLibrary1.cel[0].cev[210].cevr";
connectAttr "animCurveTL1117.a" "clipLibrary1.cel[0].cev[211].cevr";
connectAttr "animCurveTL1118.a" "clipLibrary1.cel[0].cev[212].cevr";
connectAttr "animCurveTL1119.a" "clipLibrary1.cel[0].cev[213].cevr";
connectAttr "animCurveTU1681.a" "clipLibrary1.cel[0].cev[214].cevr";
connectAttr "animCurveTU1682.a" "clipLibrary1.cel[0].cev[215].cevr";
connectAttr "animCurveTU1683.a" "clipLibrary1.cel[0].cev[216].cevr";
connectAttr "animCurveTA3257.a" "clipLibrary1.cel[0].cev[217].cevr";
connectAttr "animCurveTA3258.a" "clipLibrary1.cel[0].cev[218].cevr";
connectAttr "animCurveTA3259.a" "clipLibrary1.cel[0].cev[219].cevr";
connectAttr "animCurveTL1120.a" "clipLibrary1.cel[0].cev[220].cevr";
connectAttr "animCurveTL1121.a" "clipLibrary1.cel[0].cev[221].cevr";
connectAttr "animCurveTL1122.a" "clipLibrary1.cel[0].cev[222].cevr";
connectAttr "animCurveTU1684.a" "clipLibrary1.cel[0].cev[223].cevr";
connectAttr "animCurveTU1685.a" "clipLibrary1.cel[0].cev[224].cevr";
connectAttr "animCurveTA3260.a" "clipLibrary1.cel[0].cev[225].cevr";
connectAttr "animCurveTA3261.a" "clipLibrary1.cel[0].cev[226].cevr";
connectAttr "animCurveTA3262.a" "clipLibrary1.cel[0].cev[227].cevr";
connectAttr "animCurveTL1123.a" "clipLibrary1.cel[0].cev[228].cevr";
connectAttr "animCurveTL1124.a" "clipLibrary1.cel[0].cev[229].cevr";
connectAttr "animCurveTL1125.a" "clipLibrary1.cel[0].cev[230].cevr";
connectAttr "animCurveTU1686.a" "clipLibrary1.cel[0].cev[231].cevr";
connectAttr "animCurveTU1687.a" "clipLibrary1.cel[0].cev[232].cevr";
connectAttr "animCurveTU1688.a" "clipLibrary1.cel[0].cev[233].cevr";
connectAttr "animCurveTA3263.a" "clipLibrary1.cel[0].cev[234].cevr";
connectAttr "animCurveTA3264.a" "clipLibrary1.cel[0].cev[235].cevr";
connectAttr "animCurveTA3265.a" "clipLibrary1.cel[0].cev[236].cevr";
connectAttr "animCurveTL1126.a" "clipLibrary1.cel[0].cev[237].cevr";
connectAttr "animCurveTL1127.a" "clipLibrary1.cel[0].cev[238].cevr";
connectAttr "animCurveTL1128.a" "clipLibrary1.cel[0].cev[239].cevr";
connectAttr "animCurveTU1689.a" "clipLibrary1.cel[0].cev[240].cevr";
connectAttr "animCurveTU1690.a" "clipLibrary1.cel[0].cev[241].cevr";
connectAttr "animCurveTA3266.a" "clipLibrary1.cel[0].cev[242].cevr";
connectAttr "animCurveTA3267.a" "clipLibrary1.cel[0].cev[243].cevr";
connectAttr "animCurveTA3268.a" "clipLibrary1.cel[0].cev[244].cevr";
connectAttr "animCurveTL1129.a" "clipLibrary1.cel[0].cev[245].cevr";
connectAttr "animCurveTL1130.a" "clipLibrary1.cel[0].cev[246].cevr";
connectAttr "animCurveTL1131.a" "clipLibrary1.cel[0].cev[247].cevr";
connectAttr "animCurveTA3269.a" "clipLibrary1.cel[0].cev[248].cevr";
connectAttr "animCurveTA3270.a" "clipLibrary1.cel[0].cev[249].cevr";
connectAttr "animCurveTA3271.a" "clipLibrary1.cel[0].cev[250].cevr";
connectAttr "animCurveTA3272.a" "clipLibrary1.cel[0].cev[251].cevr";
connectAttr "animCurveTA3273.a" "clipLibrary1.cel[0].cev[252].cevr";
connectAttr "animCurveTA3274.a" "clipLibrary1.cel[0].cev[253].cevr";
connectAttr "animCurveTA3275.a" "clipLibrary1.cel[0].cev[254].cevr";
connectAttr "animCurveTA3276.a" "clipLibrary1.cel[0].cev[255].cevr";
connectAttr "animCurveTA3277.a" "clipLibrary1.cel[0].cev[256].cevr";
connectAttr "animCurveTA3278.a" "clipLibrary1.cel[0].cev[257].cevr";
connectAttr "animCurveTA3279.a" "clipLibrary1.cel[0].cev[258].cevr";
connectAttr "animCurveTA3280.a" "clipLibrary1.cel[0].cev[259].cevr";
connectAttr "animCurveTA3281.a" "clipLibrary1.cel[0].cev[260].cevr";
connectAttr "animCurveTA3282.a" "clipLibrary1.cel[0].cev[261].cevr";
connectAttr "animCurveTA3283.a" "clipLibrary1.cel[0].cev[262].cevr";
connectAttr "animCurveTA3284.a" "clipLibrary1.cel[0].cev[263].cevr";
connectAttr "animCurveTU1691.a" "clipLibrary1.cel[0].cev[264].cevr";
connectAttr "animCurveTU1692.a" "clipLibrary1.cel[0].cev[265].cevr";
connectAttr "animCurveTU1693.a" "clipLibrary1.cel[0].cev[266].cevr";
connectAttr "animCurveTL1132.a" "clipLibrary1.cel[0].cev[267].cevr";
connectAttr "animCurveTL1133.a" "clipLibrary1.cel[0].cev[268].cevr";
connectAttr "animCurveTL1134.a" "clipLibrary1.cel[0].cev[269].cevr";
connectAttr "animCurveTU1694.a" "clipLibrary1.cel[0].cev[270].cevr";
connectAttr "animCurveTL1135.a" "clipLibrary1.cel[0].cev[271].cevr";
connectAttr "animCurveTL1136.a" "clipLibrary1.cel[0].cev[272].cevr";
connectAttr "animCurveTL1137.a" "clipLibrary1.cel[0].cev[273].cevr";
connectAttr "animCurveTA3285.a" "clipLibrary1.cel[0].cev[274].cevr";
connectAttr "animCurveTA3286.a" "clipLibrary1.cel[0].cev[275].cevr";
connectAttr "animCurveTA3287.a" "clipLibrary1.cel[0].cev[276].cevr";
connectAttr "animCurveTL1138.a" "clipLibrary1.cel[0].cev[277].cevr";
connectAttr "animCurveTL1139.a" "clipLibrary1.cel[0].cev[278].cevr";
connectAttr "animCurveTL1140.a" "clipLibrary1.cel[0].cev[279].cevr";
connectAttr "animCurveTU1695.a" "clipLibrary1.cel[0].cev[280].cevr";
connectAttr "animCurveTU1696.a" "clipLibrary1.cel[0].cev[281].cevr";
connectAttr "animCurveTU1697.a" "clipLibrary1.cel[0].cev[282].cevr";
connectAttr "animCurveTU1698.a" "clipLibrary1.cel[0].cev[283].cevr";
connectAttr "animCurveTU1699.a" "clipLibrary1.cel[0].cev[284].cevr";
connectAttr "animCurveTU1700.a" "clipLibrary1.cel[0].cev[285].cevr";
connectAttr "animCurveTU1701.a" "clipLibrary1.cel[0].cev[286].cevr";
connectAttr "animCurveTU1702.a" "clipLibrary1.cel[0].cev[287].cevr";
connectAttr "animCurveTA3288.a" "clipLibrary1.cel[0].cev[288].cevr";
connectAttr "animCurveTA3289.a" "clipLibrary1.cel[0].cev[289].cevr";
connectAttr "animCurveTA3290.a" "clipLibrary1.cel[0].cev[290].cevr";
connectAttr "animCurveTL1141.a" "clipLibrary1.cel[0].cev[291].cevr";
connectAttr "animCurveTL1142.a" "clipLibrary1.cel[0].cev[292].cevr";
connectAttr "animCurveTL1143.a" "clipLibrary1.cel[0].cev[293].cevr";
connectAttr "animCurveTU1703.a" "clipLibrary1.cel[0].cev[294].cevr";
connectAttr "animCurveTU1704.a" "clipLibrary1.cel[0].cev[295].cevr";
connectAttr "animCurveTU1705.a" "clipLibrary1.cel[0].cev[296].cevr";
connectAttr "animCurveTL1144.a" "clipLibrary1.cel[0].cev[297].cevr";
connectAttr "animCurveTL1145.a" "clipLibrary1.cel[0].cev[298].cevr";
connectAttr "animCurveTL1146.a" "clipLibrary1.cel[0].cev[299].cevr";
connectAttr "animCurveTU1706.a" "clipLibrary1.cel[0].cev[300].cevr";
connectAttr "animCurveTL1147.a" "clipLibrary1.cel[0].cev[301].cevr";
connectAttr "animCurveTL1148.a" "clipLibrary1.cel[0].cev[302].cevr";
connectAttr "animCurveTL1149.a" "clipLibrary1.cel[0].cev[303].cevr";
connectAttr "animCurveTA3291.a" "clipLibrary1.cel[0].cev[304].cevr";
connectAttr "animCurveTA3292.a" "clipLibrary1.cel[0].cev[305].cevr";
connectAttr "animCurveTA3293.a" "clipLibrary1.cel[0].cev[306].cevr";
connectAttr "animCurveTL1150.a" "clipLibrary1.cel[0].cev[307].cevr";
connectAttr "animCurveTL1151.a" "clipLibrary1.cel[0].cev[308].cevr";
connectAttr "animCurveTL1152.a" "clipLibrary1.cel[0].cev[309].cevr";
connectAttr "animCurveTU1707.a" "clipLibrary1.cel[0].cev[310].cevr";
connectAttr "animCurveTU1708.a" "clipLibrary1.cel[0].cev[311].cevr";
connectAttr "animCurveTU1709.a" "clipLibrary1.cel[0].cev[312].cevr";
connectAttr "animCurveTU1710.a" "clipLibrary1.cel[0].cev[313].cevr";
connectAttr "animCurveTU1711.a" "clipLibrary1.cel[0].cev[314].cevr";
connectAttr "animCurveTA3294.a" "clipLibrary1.cel[0].cev[315].cevr";
connectAttr "animCurveTA3295.a" "clipLibrary1.cel[0].cev[316].cevr";
connectAttr "animCurveTA3296.a" "clipLibrary1.cel[0].cev[317].cevr";
connectAttr "animCurveTL1153.a" "clipLibrary1.cel[0].cev[318].cevr";
connectAttr "animCurveTL1154.a" "clipLibrary1.cel[0].cev[319].cevr";
connectAttr "animCurveTL1155.a" "clipLibrary1.cel[0].cev[320].cevr";
connectAttr "animCurveTA3297.a" "clipLibrary1.cel[0].cev[321].cevr";
connectAttr "animCurveTA3298.a" "clipLibrary1.cel[0].cev[322].cevr";
connectAttr "animCurveTA3299.a" "clipLibrary1.cel[0].cev[323].cevr";
connectAttr "animCurveTA3300.a" "clipLibrary1.cel[0].cev[324].cevr";
connectAttr "animCurveTA3301.a" "clipLibrary1.cel[0].cev[325].cevr";
connectAttr "animCurveTA3302.a" "clipLibrary1.cel[0].cev[326].cevr";
connectAttr "animCurveTU1712.a" "clipLibrary1.cel[0].cev[327].cevr";
connectAttr "animCurveTU1713.a" "clipLibrary1.cel[0].cev[328].cevr";
connectAttr "animCurveTU1714.a" "clipLibrary1.cel[0].cev[329].cevr";
connectAttr "animCurveTA3303.a" "clipLibrary1.cel[0].cev[330].cevr";
connectAttr "animCurveTA3304.a" "clipLibrary1.cel[0].cev[331].cevr";
connectAttr "animCurveTA3305.a" "clipLibrary1.cel[0].cev[332].cevr";
connectAttr "animCurveTA3306.a" "clipLibrary1.cel[0].cev[333].cevr";
connectAttr "animCurveTA3307.a" "clipLibrary1.cel[0].cev[334].cevr";
connectAttr "animCurveTA3308.a" "clipLibrary1.cel[0].cev[335].cevr";
connectAttr "animCurveTU1715.a" "clipLibrary1.cel[0].cev[336].cevr";
connectAttr "animCurveTU1716.a" "clipLibrary1.cel[0].cev[337].cevr";
connectAttr "animCurveTU1717.a" "clipLibrary1.cel[0].cev[338].cevr";
connectAttr "animCurveTA3309.a" "clipLibrary1.cel[0].cev[339].cevr";
connectAttr "animCurveTA3310.a" "clipLibrary1.cel[0].cev[340].cevr";
connectAttr "animCurveTA3311.a" "clipLibrary1.cel[0].cev[341].cevr";
connectAttr "animCurveTA3312.a" "clipLibrary1.cel[0].cev[342].cevr";
connectAttr "animCurveTA3313.a" "clipLibrary1.cel[0].cev[343].cevr";
connectAttr "animCurveTA3314.a" "clipLibrary1.cel[0].cev[344].cevr";
connectAttr "animCurveTU1718.a" "clipLibrary1.cel[0].cev[345].cevr";
connectAttr "animCurveTU1719.a" "clipLibrary1.cel[0].cev[346].cevr";
connectAttr "animCurveTU1720.a" "clipLibrary1.cel[0].cev[347].cevr";
connectAttr "animCurveTA3315.a" "clipLibrary1.cel[0].cev[348].cevr";
connectAttr "animCurveTA3316.a" "clipLibrary1.cel[0].cev[349].cevr";
connectAttr "animCurveTA3317.a" "clipLibrary1.cel[0].cev[350].cevr";
connectAttr "animCurveTA3318.a" "clipLibrary1.cel[0].cev[351].cevr";
connectAttr "animCurveTA3319.a" "clipLibrary1.cel[0].cev[352].cevr";
connectAttr "animCurveTA3320.a" "clipLibrary1.cel[0].cev[353].cevr";
connectAttr "animCurveTU1721.a" "clipLibrary1.cel[0].cev[354].cevr";
connectAttr "animCurveTU1722.a" "clipLibrary1.cel[0].cev[355].cevr";
connectAttr "animCurveTU1723.a" "clipLibrary1.cel[0].cev[356].cevr";
connectAttr "animCurveTA3321.a" "clipLibrary1.cel[0].cev[357].cevr";
connectAttr "animCurveTA3322.a" "clipLibrary1.cel[0].cev[358].cevr";
connectAttr "animCurveTA3323.a" "clipLibrary1.cel[0].cev[359].cevr";
connectAttr "animCurveTU1724.a" "clipLibrary1.cel[0].cev[360].cevr";
connectAttr "animCurveTU1725.a" "clipLibrary1.cel[0].cev[361].cevr";
connectAttr "animCurveTU1726.a" "clipLibrary1.cel[0].cev[362].cevr";
connectAttr "animCurveTA3324.a" "clipLibrary1.cel[0].cev[363].cevr";
connectAttr "animCurveTA3325.a" "clipLibrary1.cel[0].cev[364].cevr";
connectAttr "animCurveTA3326.a" "clipLibrary1.cel[0].cev[365].cevr";
connectAttr "animCurveTL1156.a" "clipLibrary1.cel[0].cev[366].cevr";
connectAttr "animCurveTL1157.a" "clipLibrary1.cel[0].cev[367].cevr";
connectAttr "animCurveTL1158.a" "clipLibrary1.cel[0].cev[368].cevr";
connectAttr "animCurveTU1727.a" "clipLibrary1.cel[0].cev[369].cevr";
connectAttr "animCurveTU1728.a" "clipLibrary1.cel[0].cev[370].cevr";
connectAttr "animCurveTU1729.a" "clipLibrary1.cel[0].cev[371].cevr";
connectAttr "animCurveTA3327.a" "clipLibrary1.cel[0].cev[372].cevr";
connectAttr "animCurveTA3328.a" "clipLibrary1.cel[0].cev[373].cevr";
connectAttr "animCurveTA3329.a" "clipLibrary1.cel[0].cev[374].cevr";
connectAttr "animCurveTL1159.a" "clipLibrary1.cel[0].cev[375].cevr";
connectAttr "animCurveTL1160.a" "clipLibrary1.cel[0].cev[376].cevr";
connectAttr "animCurveTL1161.a" "clipLibrary1.cel[0].cev[377].cevr";
connectAttr "animCurveTA3330.a" "clipLibrary1.cel[0].cev[378].cevr";
connectAttr "animCurveTA3331.a" "clipLibrary1.cel[0].cev[379].cevr";
connectAttr "animCurveTA3332.a" "clipLibrary1.cel[0].cev[380].cevr";
connectAttr "animCurveTU1730.a" "clipLibrary1.cel[0].cev[381].cevr";
connectAttr "animCurveTU1731.a" "clipLibrary1.cel[0].cev[382].cevr";
connectAttr "animCurveTU1732.a" "clipLibrary1.cel[0].cev[383].cevr";
connectAttr "animCurveTA3333.a" "clipLibrary1.cel[0].cev[384].cevr";
connectAttr "animCurveTA3334.a" "clipLibrary1.cel[0].cev[385].cevr";
connectAttr "animCurveTA3335.a" "clipLibrary1.cel[0].cev[386].cevr";
connectAttr "animCurveTA3336.a" "clipLibrary1.cel[0].cev[387].cevr";
connectAttr "animCurveTA3337.a" "clipLibrary1.cel[0].cev[388].cevr";
connectAttr "animCurveTA3338.a" "clipLibrary1.cel[0].cev[389].cevr";
connectAttr "animCurveTU1733.a" "clipLibrary1.cel[0].cev[390].cevr";
connectAttr "animCurveTU1734.a" "clipLibrary1.cel[0].cev[391].cevr";
connectAttr "animCurveTU1735.a" "clipLibrary1.cel[0].cev[392].cevr";
connectAttr "animCurveTA3339.a" "clipLibrary1.cel[0].cev[393].cevr";
connectAttr "animCurveTA3340.a" "clipLibrary1.cel[0].cev[394].cevr";
connectAttr "animCurveTA3341.a" "clipLibrary1.cel[0].cev[395].cevr";
connectAttr "animCurveTA3342.a" "clipLibrary1.cel[0].cev[396].cevr";
connectAttr "animCurveTA3343.a" "clipLibrary1.cel[0].cev[397].cevr";
connectAttr "animCurveTA3344.a" "clipLibrary1.cel[0].cev[398].cevr";
connectAttr "animCurveTU1736.a" "clipLibrary1.cel[0].cev[399].cevr";
connectAttr "animCurveTU1737.a" "clipLibrary1.cel[0].cev[400].cevr";
connectAttr "animCurveTU1738.a" "clipLibrary1.cel[0].cev[401].cevr";
connectAttr "animCurveTA3345.a" "clipLibrary1.cel[0].cev[402].cevr";
connectAttr "animCurveTA3346.a" "clipLibrary1.cel[0].cev[403].cevr";
connectAttr "animCurveTA3347.a" "clipLibrary1.cel[0].cev[404].cevr";
connectAttr "animCurveTA3348.a" "clipLibrary1.cel[0].cev[405].cevr";
connectAttr "animCurveTA3349.a" "clipLibrary1.cel[0].cev[406].cevr";
connectAttr "animCurveTA3350.a" "clipLibrary1.cel[0].cev[407].cevr";
connectAttr "animCurveTU1739.a" "clipLibrary1.cel[0].cev[408].cevr";
connectAttr "animCurveTU1740.a" "clipLibrary1.cel[0].cev[409].cevr";
connectAttr "animCurveTU1741.a" "clipLibrary1.cel[0].cev[410].cevr";
connectAttr "animCurveTA3351.a" "clipLibrary1.cel[0].cev[411].cevr";
connectAttr "animCurveTA3352.a" "clipLibrary1.cel[0].cev[412].cevr";
connectAttr "animCurveTA3353.a" "clipLibrary1.cel[0].cev[413].cevr";
connectAttr "animCurveTA3354.a" "clipLibrary1.cel[0].cev[414].cevr";
connectAttr "animCurveTA3355.a" "clipLibrary1.cel[0].cev[415].cevr";
connectAttr "animCurveTA3356.a" "clipLibrary1.cel[0].cev[416].cevr";
connectAttr "animCurveTU1742.a" "clipLibrary1.cel[0].cev[417].cevr";
connectAttr "animCurveTU1743.a" "clipLibrary1.cel[0].cev[418].cevr";
connectAttr "animCurveTU1744.a" "clipLibrary1.cel[0].cev[419].cevr";
connectAttr "animCurveTA3357.a" "clipLibrary1.cel[0].cev[420].cevr";
connectAttr "animCurveTA3358.a" "clipLibrary1.cel[0].cev[421].cevr";
connectAttr "animCurveTA3359.a" "clipLibrary1.cel[0].cev[422].cevr";
connectAttr "animCurveTA3360.a" "clipLibrary1.cel[0].cev[423].cevr";
connectAttr "animCurveTA3361.a" "clipLibrary1.cel[0].cev[424].cevr";
connectAttr "animCurveTA3362.a" "clipLibrary1.cel[0].cev[425].cevr";
connectAttr "animCurveTU1745.a" "clipLibrary1.cel[0].cev[426].cevr";
connectAttr "animCurveTU1746.a" "clipLibrary1.cel[0].cev[427].cevr";
connectAttr "animCurveTU1747.a" "clipLibrary1.cel[0].cev[428].cevr";
connectAttr "animCurveTA3363.a" "clipLibrary1.cel[0].cev[429].cevr";
connectAttr "animCurveTA3364.a" "clipLibrary1.cel[0].cev[430].cevr";
connectAttr "animCurveTA3365.a" "clipLibrary1.cel[0].cev[431].cevr";
connectAttr "animCurveTA3366.a" "clipLibrary1.cel[0].cev[432].cevr";
connectAttr "animCurveTA3367.a" "clipLibrary1.cel[0].cev[433].cevr";
connectAttr "animCurveTA3368.a" "clipLibrary1.cel[0].cev[434].cevr";
connectAttr "animCurveTU1748.a" "clipLibrary1.cel[0].cev[435].cevr";
connectAttr "animCurveTU1749.a" "clipLibrary1.cel[0].cev[436].cevr";
connectAttr "animCurveTU1750.a" "clipLibrary1.cel[0].cev[437].cevr";
connectAttr "animCurveTA3369.a" "clipLibrary1.cel[0].cev[438].cevr";
connectAttr "animCurveTA3370.a" "clipLibrary1.cel[0].cev[439].cevr";
connectAttr "animCurveTA3371.a" "clipLibrary1.cel[0].cev[440].cevr";
connectAttr "animCurveTA3372.a" "clipLibrary1.cel[0].cev[441].cevr";
connectAttr "animCurveTA3373.a" "clipLibrary1.cel[0].cev[442].cevr";
connectAttr "animCurveTA3374.a" "clipLibrary1.cel[0].cev[443].cevr";
connectAttr "animCurveTU1751.a" "clipLibrary1.cel[0].cev[444].cevr";
connectAttr "animCurveTU1752.a" "clipLibrary1.cel[0].cev[445].cevr";
connectAttr "animCurveTU1753.a" "clipLibrary1.cel[0].cev[446].cevr";
connectAttr "animCurveTA3375.a" "clipLibrary1.cel[0].cev[447].cevr";
connectAttr "animCurveTA3376.a" "clipLibrary1.cel[0].cev[448].cevr";
connectAttr "animCurveTA3377.a" "clipLibrary1.cel[0].cev[449].cevr";
connectAttr "animCurveTA3378.a" "clipLibrary1.cel[0].cev[450].cevr";
connectAttr "animCurveTA3379.a" "clipLibrary1.cel[0].cev[451].cevr";
connectAttr "animCurveTA3380.a" "clipLibrary1.cel[0].cev[452].cevr";
connectAttr "animCurveTU1754.a" "clipLibrary1.cel[0].cev[453].cevr";
connectAttr "animCurveTU1755.a" "clipLibrary1.cel[0].cev[454].cevr";
connectAttr "animCurveTU1756.a" "clipLibrary1.cel[0].cev[455].cevr";
connectAttr "animCurveTA3381.a" "clipLibrary1.cel[0].cev[456].cevr";
connectAttr "animCurveTA3382.a" "clipLibrary1.cel[0].cev[457].cevr";
connectAttr "animCurveTA3383.a" "clipLibrary1.cel[0].cev[458].cevr";
connectAttr "animCurveTA3384.a" "clipLibrary1.cel[0].cev[459].cevr";
connectAttr "animCurveTA3385.a" "clipLibrary1.cel[0].cev[460].cevr";
connectAttr "animCurveTA3386.a" "clipLibrary1.cel[0].cev[461].cevr";
connectAttr "animCurveTU1757.a" "clipLibrary1.cel[0].cev[462].cevr";
connectAttr "animCurveTU1758.a" "clipLibrary1.cel[0].cev[463].cevr";
connectAttr "animCurveTU1759.a" "clipLibrary1.cel[0].cev[464].cevr";
connectAttr "animCurveTA3387.a" "clipLibrary1.cel[0].cev[465].cevr";
connectAttr "animCurveTA3388.a" "clipLibrary1.cel[0].cev[466].cevr";
connectAttr "animCurveTA3389.a" "clipLibrary1.cel[0].cev[467].cevr";
connectAttr "animCurveTA3390.a" "clipLibrary1.cel[0].cev[468].cevr";
connectAttr "animCurveTA3391.a" "clipLibrary1.cel[0].cev[469].cevr";
connectAttr "animCurveTA3392.a" "clipLibrary1.cel[0].cev[470].cevr";
connectAttr "animCurveTU1760.a" "clipLibrary1.cel[0].cev[471].cevr";
connectAttr "animCurveTU1761.a" "clipLibrary1.cel[0].cev[472].cevr";
connectAttr "animCurveTU1762.a" "clipLibrary1.cel[0].cev[473].cevr";
connectAttr "animCurveTA3393.a" "clipLibrary1.cel[0].cev[474].cevr";
connectAttr "animCurveTA3394.a" "clipLibrary1.cel[0].cev[475].cevr";
connectAttr "animCurveTA3395.a" "clipLibrary1.cel[0].cev[476].cevr";
connectAttr "animCurveTA3396.a" "clipLibrary1.cel[0].cev[477].cevr";
connectAttr "animCurveTA3397.a" "clipLibrary1.cel[0].cev[478].cevr";
connectAttr "animCurveTA3398.a" "clipLibrary1.cel[0].cev[479].cevr";
connectAttr "animCurveTU1763.a" "clipLibrary1.cel[0].cev[480].cevr";
connectAttr "animCurveTU1764.a" "clipLibrary1.cel[0].cev[481].cevr";
connectAttr "animCurveTU1765.a" "clipLibrary1.cel[0].cev[482].cevr";
connectAttr "animCurveTA3399.a" "clipLibrary1.cel[0].cev[483].cevr";
connectAttr "animCurveTA3400.a" "clipLibrary1.cel[0].cev[484].cevr";
connectAttr "animCurveTA3401.a" "clipLibrary1.cel[0].cev[485].cevr";
connectAttr "animCurveTA3402.a" "clipLibrary1.cel[0].cev[486].cevr";
connectAttr "animCurveTA3403.a" "clipLibrary1.cel[0].cev[487].cevr";
connectAttr "animCurveTA3404.a" "clipLibrary1.cel[0].cev[488].cevr";
connectAttr "animCurveTU1766.a" "clipLibrary1.cel[0].cev[489].cevr";
connectAttr "animCurveTU1767.a" "clipLibrary1.cel[0].cev[490].cevr";
connectAttr "animCurveTU1768.a" "clipLibrary1.cel[0].cev[491].cevr";
connectAttr "animCurveTA3405.a" "clipLibrary1.cel[0].cev[492].cevr";
connectAttr "animCurveTA3406.a" "clipLibrary1.cel[0].cev[493].cevr";
connectAttr "animCurveTA3407.a" "clipLibrary1.cel[0].cev[494].cevr";
connectAttr "animCurveTA3408.a" "clipLibrary1.cel[0].cev[495].cevr";
connectAttr "animCurveTA3409.a" "clipLibrary1.cel[0].cev[496].cevr";
connectAttr "animCurveTA3410.a" "clipLibrary1.cel[0].cev[497].cevr";
connectAttr "animCurveTU1769.a" "clipLibrary1.cel[0].cev[498].cevr";
connectAttr "animCurveTU1770.a" "clipLibrary1.cel[0].cev[499].cevr";
connectAttr "animCurveTU1771.a" "clipLibrary1.cel[0].cev[500].cevr";
connectAttr "animCurveTA3411.a" "clipLibrary1.cel[0].cev[501].cevr";
connectAttr "animCurveTA3412.a" "clipLibrary1.cel[0].cev[502].cevr";
connectAttr "animCurveTA3413.a" "clipLibrary1.cel[0].cev[503].cevr";
connectAttr "animCurveTA3414.a" "clipLibrary1.cel[0].cev[504].cevr";
connectAttr "animCurveTA3415.a" "clipLibrary1.cel[0].cev[505].cevr";
connectAttr "animCurveTA3416.a" "clipLibrary1.cel[0].cev[506].cevr";
connectAttr "animCurveTU1772.a" "clipLibrary1.cel[0].cev[507].cevr";
connectAttr "animCurveTU1773.a" "clipLibrary1.cel[0].cev[508].cevr";
connectAttr "animCurveTU1774.a" "clipLibrary1.cel[0].cev[509].cevr";
connectAttr "animCurveTA3417.a" "clipLibrary1.cel[0].cev[510].cevr";
connectAttr "animCurveTA3418.a" "clipLibrary1.cel[0].cev[511].cevr";
connectAttr "animCurveTA3419.a" "clipLibrary1.cel[0].cev[512].cevr";
connectAttr "animCurveTA3420.a" "clipLibrary1.cel[0].cev[513].cevr";
connectAttr "animCurveTA3421.a" "clipLibrary1.cel[0].cev[514].cevr";
connectAttr "animCurveTA3422.a" "clipLibrary1.cel[0].cev[515].cevr";
connectAttr "animCurveTU1775.a" "clipLibrary1.cel[0].cev[516].cevr";
connectAttr "animCurveTU1776.a" "clipLibrary1.cel[0].cev[517].cevr";
connectAttr "animCurveTU1777.a" "clipLibrary1.cel[0].cev[518].cevr";
connectAttr "animCurveTA3423.a" "clipLibrary1.cel[0].cev[519].cevr";
connectAttr "animCurveTA3424.a" "clipLibrary1.cel[0].cev[520].cevr";
connectAttr "animCurveTA3425.a" "clipLibrary1.cel[0].cev[521].cevr";
connectAttr "animCurveTA3426.a" "clipLibrary1.cel[0].cev[522].cevr";
connectAttr "animCurveTA3427.a" "clipLibrary1.cel[0].cev[523].cevr";
connectAttr "animCurveTA3428.a" "clipLibrary1.cel[0].cev[524].cevr";
connectAttr "animCurveTU1778.a" "clipLibrary1.cel[0].cev[525].cevr";
connectAttr "animCurveTU1779.a" "clipLibrary1.cel[0].cev[526].cevr";
connectAttr "animCurveTU1780.a" "clipLibrary1.cel[0].cev[527].cevr";
connectAttr "animCurveTA3429.a" "clipLibrary1.cel[0].cev[528].cevr";
connectAttr "animCurveTA3430.a" "clipLibrary1.cel[0].cev[529].cevr";
connectAttr "animCurveTA3431.a" "clipLibrary1.cel[0].cev[530].cevr";
connectAttr "animCurveTA3432.a" "clipLibrary1.cel[0].cev[531].cevr";
connectAttr "animCurveTA3433.a" "clipLibrary1.cel[0].cev[532].cevr";
connectAttr "animCurveTA3434.a" "clipLibrary1.cel[0].cev[533].cevr";
connectAttr "animCurveTU1781.a" "clipLibrary1.cel[0].cev[534].cevr";
connectAttr "animCurveTU1782.a" "clipLibrary1.cel[0].cev[535].cevr";
connectAttr "animCurveTU1783.a" "clipLibrary1.cel[0].cev[536].cevr";
connectAttr "animCurveTA3435.a" "clipLibrary1.cel[0].cev[537].cevr";
connectAttr "animCurveTA3436.a" "clipLibrary1.cel[0].cev[538].cevr";
connectAttr "animCurveTA3437.a" "clipLibrary1.cel[0].cev[539].cevr";
connectAttr "animCurveTU1784.a" "clipLibrary1.cel[0].cev[540].cevr";
connectAttr "animCurveTU1785.a" "clipLibrary1.cel[0].cev[541].cevr";
connectAttr "animCurveTU1786.a" "clipLibrary1.cel[0].cev[542].cevr";
connectAttr "animCurveTA3438.a" "clipLibrary1.cel[0].cev[543].cevr";
connectAttr "animCurveTA3439.a" "clipLibrary1.cel[0].cev[544].cevr";
connectAttr "animCurveTA3440.a" "clipLibrary1.cel[0].cev[545].cevr";
connectAttr "animCurveTL1162.a" "clipLibrary1.cel[0].cev[546].cevr";
connectAttr "animCurveTL1163.a" "clipLibrary1.cel[0].cev[547].cevr";
connectAttr "animCurveTL1164.a" "clipLibrary1.cel[0].cev[548].cevr";
connectAttr "animCurveTU1787.a" "clipLibrary1.cel[0].cev[549].cevr";
connectAttr "animCurveTU1788.a" "clipLibrary1.cel[0].cev[550].cevr";
connectAttr "animCurveTU1789.a" "clipLibrary1.cel[0].cev[551].cevr";
connectAttr "animCurveTA3441.a" "clipLibrary1.cel[0].cev[552].cevr";
connectAttr "animCurveTA3442.a" "clipLibrary1.cel[0].cev[553].cevr";
connectAttr "animCurveTA3443.a" "clipLibrary1.cel[0].cev[554].cevr";
connectAttr "animCurveTL1165.a" "clipLibrary1.cel[0].cev[555].cevr";
connectAttr "animCurveTL1166.a" "clipLibrary1.cel[0].cev[556].cevr";
connectAttr "animCurveTL1167.a" "clipLibrary1.cel[0].cev[557].cevr";
connectAttr "animCurveTA3444.a" "clipLibrary1.cel[0].cev[558].cevr";
connectAttr "animCurveTA3445.a" "clipLibrary1.cel[0].cev[559].cevr";
connectAttr "animCurveTA3446.a" "clipLibrary1.cel[0].cev[560].cevr";
connectAttr "animCurveTU1790.a" "clipLibrary1.cel[0].cev[561].cevr";
connectAttr "animCurveTU1791.a" "clipLibrary1.cel[0].cev[562].cevr";
connectAttr "animCurveTU1792.a" "clipLibrary1.cel[0].cev[563].cevr";
connectAttr "animCurveTA3447.a" "clipLibrary1.cel[0].cev[564].cevr";
connectAttr "animCurveTA3448.a" "clipLibrary1.cel[0].cev[565].cevr";
connectAttr "animCurveTA3449.a" "clipLibrary1.cel[0].cev[566].cevr";
connectAttr "animCurveTA3450.a" "clipLibrary1.cel[0].cev[567].cevr";
connectAttr "animCurveTA3451.a" "clipLibrary1.cel[0].cev[568].cevr";
connectAttr "animCurveTA3452.a" "clipLibrary1.cel[0].cev[569].cevr";
connectAttr "animCurveTU1793.a" "clipLibrary1.cel[0].cev[570].cevr";
connectAttr "animCurveTU1794.a" "clipLibrary1.cel[0].cev[571].cevr";
connectAttr "animCurveTU1795.a" "clipLibrary1.cel[0].cev[572].cevr";
connectAttr "animCurveTA3453.a" "clipLibrary1.cel[0].cev[573].cevr";
connectAttr "animCurveTA3454.a" "clipLibrary1.cel[0].cev[574].cevr";
connectAttr "animCurveTA3455.a" "clipLibrary1.cel[0].cev[575].cevr";
connectAttr "animCurveTA3456.a" "clipLibrary1.cel[0].cev[576].cevr";
connectAttr "animCurveTA3457.a" "clipLibrary1.cel[0].cev[577].cevr";
connectAttr "animCurveTA3458.a" "clipLibrary1.cel[0].cev[578].cevr";
connectAttr "animCurveTU1796.a" "clipLibrary1.cel[0].cev[579].cevr";
connectAttr "animCurveTU1797.a" "clipLibrary1.cel[0].cev[580].cevr";
connectAttr "animCurveTU1798.a" "clipLibrary1.cel[0].cev[581].cevr";
connectAttr "animCurveTA3459.a" "clipLibrary1.cel[0].cev[582].cevr";
connectAttr "animCurveTA3460.a" "clipLibrary1.cel[0].cev[583].cevr";
connectAttr "animCurveTA3461.a" "clipLibrary1.cel[0].cev[584].cevr";
connectAttr "animCurveTA3462.a" "clipLibrary1.cel[0].cev[585].cevr";
connectAttr "animCurveTA3463.a" "clipLibrary1.cel[0].cev[586].cevr";
connectAttr "animCurveTA3464.a" "clipLibrary1.cel[0].cev[587].cevr";
connectAttr "animCurveTU1799.a" "clipLibrary1.cel[0].cev[588].cevr";
connectAttr "animCurveTU1800.a" "clipLibrary1.cel[0].cev[589].cevr";
connectAttr "animCurveTU1801.a" "clipLibrary1.cel[0].cev[590].cevr";
connectAttr "animCurveTA3465.a" "clipLibrary1.cel[0].cev[591].cevr";
connectAttr "animCurveTA3466.a" "clipLibrary1.cel[0].cev[592].cevr";
connectAttr "animCurveTA3467.a" "clipLibrary1.cel[0].cev[593].cevr";
connectAttr "animCurveTA3468.a" "clipLibrary1.cel[0].cev[594].cevr";
connectAttr "animCurveTA3469.a" "clipLibrary1.cel[0].cev[595].cevr";
connectAttr "animCurveTA3470.a" "clipLibrary1.cel[0].cev[596].cevr";
connectAttr "animCurveTU1802.a" "clipLibrary1.cel[0].cev[597].cevr";
connectAttr "animCurveTU1803.a" "clipLibrary1.cel[0].cev[598].cevr";
connectAttr "animCurveTU1804.a" "clipLibrary1.cel[0].cev[599].cevr";
connectAttr "animCurveTA3471.a" "clipLibrary1.cel[0].cev[600].cevr";
connectAttr "animCurveTA3472.a" "clipLibrary1.cel[0].cev[601].cevr";
connectAttr "animCurveTA3473.a" "clipLibrary1.cel[0].cev[602].cevr";
connectAttr "animCurveTA3474.a" "clipLibrary1.cel[0].cev[603].cevr";
connectAttr "animCurveTA3475.a" "clipLibrary1.cel[0].cev[604].cevr";
connectAttr "animCurveTA3476.a" "clipLibrary1.cel[0].cev[605].cevr";
connectAttr "animCurveTU1805.a" "clipLibrary1.cel[0].cev[606].cevr";
connectAttr "animCurveTU1806.a" "clipLibrary1.cel[0].cev[607].cevr";
connectAttr "animCurveTU1807.a" "clipLibrary1.cel[0].cev[608].cevr";
connectAttr "animCurveTA3477.a" "clipLibrary1.cel[0].cev[609].cevr";
connectAttr "animCurveTA3478.a" "clipLibrary1.cel[0].cev[610].cevr";
connectAttr "animCurveTA3479.a" "clipLibrary1.cel[0].cev[611].cevr";
connectAttr "animCurveTA3480.a" "clipLibrary1.cel[0].cev[612].cevr";
connectAttr "animCurveTA3481.a" "clipLibrary1.cel[0].cev[613].cevr";
connectAttr "animCurveTA3482.a" "clipLibrary1.cel[0].cev[614].cevr";
connectAttr "animCurveTU1808.a" "clipLibrary1.cel[0].cev[615].cevr";
connectAttr "animCurveTU1809.a" "clipLibrary1.cel[0].cev[616].cevr";
connectAttr "animCurveTU1810.a" "clipLibrary1.cel[0].cev[617].cevr";
connectAttr "animCurveTA3483.a" "clipLibrary1.cel[0].cev[618].cevr";
connectAttr "animCurveTA3484.a" "clipLibrary1.cel[0].cev[619].cevr";
connectAttr "animCurveTA3485.a" "clipLibrary1.cel[0].cev[620].cevr";
connectAttr "animCurveTA3486.a" "clipLibrary1.cel[0].cev[621].cevr";
connectAttr "animCurveTA3487.a" "clipLibrary1.cel[0].cev[622].cevr";
connectAttr "animCurveTA3488.a" "clipLibrary1.cel[0].cev[623].cevr";
connectAttr "animCurveTU1811.a" "clipLibrary1.cel[0].cev[624].cevr";
connectAttr "animCurveTU1812.a" "clipLibrary1.cel[0].cev[625].cevr";
connectAttr "animCurveTU1813.a" "clipLibrary1.cel[0].cev[626].cevr";
connectAttr "animCurveTA3489.a" "clipLibrary1.cel[0].cev[627].cevr";
connectAttr "animCurveTA3490.a" "clipLibrary1.cel[0].cev[628].cevr";
connectAttr "animCurveTA3491.a" "clipLibrary1.cel[0].cev[629].cevr";
connectAttr "animCurveTA3492.a" "clipLibrary1.cel[0].cev[630].cevr";
connectAttr "animCurveTA3493.a" "clipLibrary1.cel[0].cev[631].cevr";
connectAttr "animCurveTA3494.a" "clipLibrary1.cel[0].cev[632].cevr";
connectAttr "animCurveTU1814.a" "clipLibrary1.cel[0].cev[633].cevr";
connectAttr "animCurveTU1815.a" "clipLibrary1.cel[0].cev[634].cevr";
connectAttr "animCurveTU1816.a" "clipLibrary1.cel[0].cev[635].cevr";
connectAttr "animCurveTA3495.a" "clipLibrary1.cel[0].cev[636].cevr";
connectAttr "animCurveTA3496.a" "clipLibrary1.cel[0].cev[637].cevr";
connectAttr "animCurveTA3497.a" "clipLibrary1.cel[0].cev[638].cevr";
connectAttr "animCurveTU1817.a" "clipLibrary1.cel[0].cev[639].cevr";
connectAttr "animCurveTU1818.a" "clipLibrary1.cel[0].cev[640].cevr";
connectAttr "animCurveTU1819.a" "clipLibrary1.cel[0].cev[641].cevr";
connectAttr "animCurveTA3498.a" "clipLibrary1.cel[0].cev[642].cevr";
connectAttr "animCurveTA3499.a" "clipLibrary1.cel[0].cev[643].cevr";
connectAttr "animCurveTA3500.a" "clipLibrary1.cel[0].cev[644].cevr";
connectAttr "animCurveTL1168.a" "clipLibrary1.cel[0].cev[645].cevr";
connectAttr "animCurveTL1169.a" "clipLibrary1.cel[0].cev[646].cevr";
connectAttr "animCurveTL1170.a" "clipLibrary1.cel[0].cev[647].cevr";
connectAttr "animCurveTU1820.a" "clipLibrary1.cel[0].cev[648].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr ":defaultLightSet.msg" "_1:lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "_1:lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "_1:lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "_1:lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
connectAttr "_1:lightLinker1.msg" ":lightList1.ln" -na;
// End of Minigame2_idleBig.ma
