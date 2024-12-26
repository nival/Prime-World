//Maya ASCII 2008 scene
//Name: stun.ma
//Last modified: Wed, Dec 16, 2009 05:35:20 PM
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
createNode animClip -n "stunSource";
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
	setAttr ".se" 80;
	setAttr ".ci" no;
createNode animCurveTA -n "animCurveTA2052";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2053";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2054";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2055";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  9 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  9 10 10 10 10;
createNode animCurveTA -n "animCurveTA2056";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -5.2047506862742576 20 -5.2047506862742576 
		40 -5.2047506862742576 60 -5.2047506862742576 80 -5.2047506862742576;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2057";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2058";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2059";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2060";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2061";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2062";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2063";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2064";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2065";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2066";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2067";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2068";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2069";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2070";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2071";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2072";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2073";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2074";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2075";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2076";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2077";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2078";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2079";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2080";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2081";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2082";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2083";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2084";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2085";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2086";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2087";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2088";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2089";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2090";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL694";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL695";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL696";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2091";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2092";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2093";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL697";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL698";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL699";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2094";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -14.368948490926961 20 -14.368948490926961 
		40 -14.368948490926961 60 -14.368948490926961 80 -14.368948490926961;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2095";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2096";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL700";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL701";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL702";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2097";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 7.9832676905363096 20 7.9832676905363096 
		40 7.9832676905363096 60 7.9832676905363096 80 7.9832676905363096;
	setAttr -s 5 ".kit[0:4]"  9 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  9 10 10 10 10;
createNode animCurveTA -n "animCurveTA2098";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2099";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL703";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL704";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL705";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2100";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2101";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2102";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL706";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL707";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL708";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2103";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2104";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2105";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL709";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL710";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL711";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2106";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2107";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2108";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL712";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL713";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL714";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2109";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2110";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2111";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL715";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL716";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL717";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2112";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2113";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2114";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL718";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL719";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL720";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2115";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2116";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2117";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL721";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL722";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL723";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1089";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2118";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.043366079873241731 20 13.571405309571343 
		40 -0.04336607987324155 60 -20.467524826274349 80 -0.043366079873241668;
	setAttr -s 5 ".kit[1:4]"  10 1 10 1;
	setAttr -s 5 ".kot[1:4]"  10 1 10 1;
	setAttr -s 5 ".kix[0:4]"  0.88720941543579102 1 0.82336205244064331 
		1 0.81498563289642334;
	setAttr -s 5 ".kiy[0:4]"  0.4613669216632843 0 -0.56751656532287598 
		0 0.57948118448257446;
	setAttr -s 5 ".kox[0:4]"  0.88720947504043579 1 0.82336205244064331 
		1 0.81498569250106812;
	setAttr -s 5 ".koy[0:4]"  0.46136689186096191 0 -0.56751656532287598 
		0 0.57948118448257446;
createNode animCurveTA -n "animCurveTA2119";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.31427152913327155 20 -4.1171341888462063 
		40 0.31427152913327211 60 5.3977729435734743 80 0.31427152913327167;
	setAttr -s 5 ".kit[0:4]"  9 10 1 10 10;
	setAttr -s 5 ".kot[0:4]"  9 10 1 10 10;
	setAttr -s 5 ".kix[2:4]"  0.97868621349334717 1 0.99125999212265015;
	setAttr -s 5 ".kiy[2:4]"  0.20536144077777863 0 -0.13192257285118103;
	setAttr -s 5 ".kox[2:4]"  0.97868621349334717 1 0.99126005172729492;
	setAttr -s 5 ".koy[2:4]"  0.20536139607429504 0 -0.13192258775234222;
createNode animCurveTA -n "animCurveTA2120";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10.456066404637159 20 -0.41684881802259705 
		40 -12.823561090426885 60 -1.1315509951517662 80 10.456066404637159;
	setAttr -s 5 ".kit[0:4]"  3 1 10 1 3;
	setAttr -s 5 ".kot[0:4]"  3 1 10 1 3;
	setAttr -s 5 ".kix[1:4]"  0.88050585985183716 0.99995625019073486 
		0.85766202211380005 1;
	setAttr -s 5 ".kiy[1:4]"  -0.47403532266616821 -0.0093550216406583786 
		0.51421380043029785 0;
	setAttr -s 5 ".kox[1:4]"  0.88050585985183716 0.99995625019073486 
		0.85766202211380005 1;
	setAttr -s 5 ".koy[1:4]"  -0.47403532266616821 -0.0093550216406583786 
		0.51421380043029785 0;
createNode animCurveTL -n "animCurveTL724";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.034304576939319542 20 -0.068667451027442761 
		40 -0.08569997485074099 60 -0.064293295854823684 80 -0.034304576939319542;
	setAttr -s 5 ".kit[0:4]"  3 1 10 1 3;
	setAttr -s 5 ".kot[0:4]"  3 1 10 1 3;
	setAttr -s 5 ".kix[1:4]"  0.99804574251174927 1 0.99780821800231934 
		1;
	setAttr -s 5 ".kiy[1:4]"  -0.06248893216252327 0 0.066172242164611816 
		0;
	setAttr -s 5 ".kox[1:4]"  0.99804568290710449 1 0.99780821800231934 
		1;
	setAttr -s 5 ".koy[1:4]"  -0.06248893216252327 0 0.066172242164611816 
		0;
createNode animCurveTL -n "animCurveTL725";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.20789996618766854 20 0.10299174427901962 
		40 -0.1188350062350025 60 0.099765750957370086 80 0.20789996618766854;
	setAttr -s 5 ".kit[1:4]"  1 3 1 3;
	setAttr -s 5 ".kot[1:4]"  1 3 1 3;
	setAttr -s 5 ".kix[1:4]"  0.94526296854019165 1 0.92935341596603394 
		1;
	setAttr -s 5 ".kiy[1:4]"  -0.32630956172943115 0 0.36919140815734863 
		0;
	setAttr -s 5 ".kox[1:4]"  0.94526296854019165 1 0.92935341596603394 
		1;
	setAttr -s 5 ".koy[1:4]"  -0.32630956172943115 0 0.36919140815734863 
		0;
createNode animCurveTL -n "animCurveTL726";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.1085850498816894 20 -0.042920219378924734 
		40 0.05380753350566167 60 0.2830242120933264 80 0.1085850498816894;
	setAttr -s 5 ".kit[0:4]"  9 10 1 10 10;
	setAttr -s 5 ".kot[0:4]"  9 10 1 10 10;
	setAttr -s 5 ".kix[2:4]"  0.94928282499313354 0.99915719032287598 
		0.96743053197860718;
	setAttr -s 5 ".kiy[2:4]"  0.31442356109619141 0.041048508137464523 
		-0.25313663482666016;
	setAttr -s 5 ".kox[2:4]"  0.94928276538848877 0.99915719032287598 
		0.96743053197860718;
	setAttr -s 5 ".koy[2:4]"  0.31442362070083618 0.041048508137464523 
		-0.25313663482666016;
createNode animCurveTA -n "animCurveTA2121";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2122";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2123";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL727";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL728";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL729";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1090";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1091";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1092";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.30000000000000077 20 -0.30000000000000077 
		40 -0.30000000000000077 60 -0.30000000000000077 80 -0.30000000000000077;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1093";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.30000000000000077 20 -0.30000000000000077 
		40 -0.30000000000000077 60 -0.30000000000000077 80 -0.30000000000000077;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1094";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.30000000000000077 20 -0.30000000000000077 
		40 -0.30000000000000077 60 -0.30000000000000077 80 -0.30000000000000077;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1095";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.30000000000000077 20 -0.30000000000000077 
		40 -0.30000000000000077 60 -0.30000000000000077 80 -0.30000000000000077;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1096";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.30000000000000077 20 -0.30000000000000077 
		40 -0.30000000000000077 60 -0.30000000000000077 80 -0.30000000000000077;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2124";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2125";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2126";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2127";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2128";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2129";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2130";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2131";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2132";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2133";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2134";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2135";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2136";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2137";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2138";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2139";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1097";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 9;
	setAttr -s 5 ".kot[0:4]"  3 5 5 5 5;
createNode animCurveTU -n "animCurveTU1098";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 9;
	setAttr -s 5 ".kot[0:4]"  3 5 5 5 5;
createNode animCurveTU -n "animCurveTU1099";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 20 10 40 10 60 10 80 10;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL730";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL731";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL732";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1100";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 20 10 40 10 60 10 80 10;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL733";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.22464769340943472 20 0.22464769340943472 
		40 0.22464769340943472 60 0.22464769340943472 80 0.22464769340943472;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL734";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.19416530018464082 20 0.19416530018464082 
		40 0.19416530018464082 60 0.19416530018464082 80 0.19416530018464082;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL735";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.47504801816095116 20 -0.47504801816095116 
		40 -0.47504801816095116 60 -0.47504801816095116 80 -0.47504801816095116;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2140";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2141";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2142";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL736";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 5.5511151231257827e-017 20 5.5511151231257827e-017 
		40 5.5511151231257827e-017 60 5.5511151231257827e-017;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL737";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 6.9388939039072284e-018 20 6.9388939039072284e-018 
		40 6.9388939039072284e-018 60 6.9388939039072284e-018;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL738";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 2.7755575615628914e-017 20 2.7755575615628914e-017 
		40 2.7755575615628914e-017 60 2.7755575615628914e-017;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1101";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1102";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1103";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1104";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1105";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 25 20 25 40 25 60 25 80 25;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1106";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1107";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1108";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2143";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 20.128361339199554 20 20.128361339199554 
		40 20.128361339199554 60 20.128361339199554 80 20.128361339199554;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2144";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2145";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL739";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL740";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.19707483477738794 20 0.19707483477738794 
		40 0.19707483477738794 60 0.19707483477738794 80 0.19707483477738794;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL741";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.18298804813669703 20 0.18298804813669703 
		40 0.18298804813669703 60 0.18298804813669703 80 0.18298804813669703;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1109";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 9;
	setAttr -s 5 ".kot[0:4]"  3 5 5 5 5;
createNode animCurveTU -n "animCurveTU1110";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 9;
	setAttr -s 5 ".kot[0:4]"  3 5 5 5 5;
createNode animCurveTU -n "animCurveTU1111";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 20 10 40 10 60 10 80 10;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL742";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL743";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL744";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1112";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL745";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.048053822278108518 20 -0.09448417506164028 
		40 0.042749642896328377 60 -0.23215703081960162 80 -0.048053822278108518;
	setAttr -s 5 ".kit[0:4]"  3 10 10 1 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 1 3;
	setAttr -s 5 ".kix[3:4]"  0.9986947774887085 1;
	setAttr -s 5 ".kiy[3:4]"  -0.051076397299766541 0;
	setAttr -s 5 ".kox[3:4]"  0.9986947774887085 1;
	setAttr -s 5 ".koy[3:4]"  -0.051076382398605347 0;
createNode animCurveTL -n "animCurveTL746";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.4447193721881446 20 -1.4906136696522498 
		40 -1.4978664639034098 60 -1.4770532367998293 80 -1.4447193721881446;
	setAttr -s 5 ".kit[0:4]"  3 9 9 1 3;
	setAttr -s 5 ".kot[0:4]"  3 9 9 1 3;
	setAttr -s 5 ".kix[3:4]"  0.99797689914703369 1;
	setAttr -s 5 ".kiy[3:4]"  0.063577383756637573 0;
	setAttr -s 5 ".kox[3:4]"  0.99797689914703369 1;
	setAttr -s 5 ".koy[3:4]"  0.063577376306056976 0;
createNode animCurveTL -n "animCurveTL747";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.52545265516213069 20 0.072447195191360572 
		40 0.0055927604018012438 60 0.58108279875615854 80 0.52545265516213069;
	setAttr -s 5 ".kit[2:4]"  10 1 1;
	setAttr -s 5 ".kot[2:4]"  10 1 1;
	setAttr -s 5 ".kix[0:4]"  0.99005979299545288 0.87071794271469116 
		0.93432468175888062 0.95371884107589722 0.98115944862365723;
	setAttr -s 5 ".kiy[0:4]"  -0.14064700901508331 -0.49178275465965271 
		0.35642310976982117 0.30069997906684875 -0.19319991767406464;
	setAttr -s 5 ".kox[0:4]"  0.99005979299545288 0.87071794271469116 
		0.93432468175888062 0.95371884107589722 0.98115944862365723;
	setAttr -s 5 ".koy[0:4]"  -0.14064699411392212 -0.4917827844619751 
		0.35642310976982117 0.30070000886917114 -0.19319993257522583;
createNode animCurveTA -n "animCurveTA2146";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2147";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2148";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL748";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL749";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1.7347234759768071e-018 20 1.7347234759768071e-018 
		40 1.7347234759768071e-018 60 1.7347234759768071e-018;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL750";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1113";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1114";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1115";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1116";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1117";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "girl_IKArm_L_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 81 ".ktv[0:80]"  0 14.565472417990296 1 17.754796774435395 
		2 -158.99871924505914 3 -155.74216298010339 4 -152.52738769704942 5 -149.40757277504221 
		6 -146.43349250709483 7 -143.65015865758286 8 -141.09435935136767 9 -138.79338093290525 
		10 -136.76487835738587 11 -135.01767892002067 12 -133.55316287581996 13 -132.36689810825527 
		14 -131.45027338139803 15 -130.79197222735141 16 -130.37921521899978 17 -130.19876276794332 
		18 -130.23770126929475 19 -130.48406813829379 20 -130.92736399272869 21 -131.53010145486931 
		22 -132.25288268432885 23 -133.08500688308274 24 -134.01747875229319 25 -135.0429952056131 
		26 -136.15600953988249 27 -137.35282300412041 28 -138.63176704763302 29 -139.99341970232047 
		30 -141.44093359980167 31 -142.9804132997418 32 -144.62143465869514 33 -146.37761500126953 
		34 -148.26736640203075 35 -150.31468519383586 36 -152.55002433495753 37 -155.01104238265006 
		38 -157.74310405789964 39 -160.79890143446022 40 195.76348270017246 41 191.88315900207544 
		42 187.53568028319012 43 182.74147533569518 44 177.564405094693 45 172.11869930715105 
		46 166.56434543662496 47 161.08862001153432 48 155.87784741501085 49 151.08937580376337 
		50 146.83405884395037 51 143.1726353536117 52 140.12315003768657 53 137.6732625767016 
		54 135.79272635970628 55 134.44326631755504 56 133.58539517395289 57 133.18255458077877 
		58 133.20345092466573 59 133.62322747990646 60 134.424039987474 61 135.58403835040087 
		62 137.05723384505154 63 138.80283995817214 64 140.78867115296327 65 142.98934919790511 
		66 145.38509823815818 67 147.96070928248753 68 150.70477655212906 69 153.60903573428385 
		70 156.66774172987186 71 159.87701704717699 72 163.23413104916824 73 166.73650528418085 
		74 170.38076101407046 75 -5.8386938912942581 76 -1.9311604738384651 77 2.0887184150429889 
		78 6.1993851611170854 79 10.371149347637406 80 14.565472417990092;
createNode animCurveTA -n "girl_IKArm_L_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 81 ".ktv[0:80]"  0 110.24850289108555 1 110.1647178960398 
		2 69.845262814250262 3 69.773313072383075 4 69.614304318304647 5 69.366450279249463 
		6 69.031409932109611 7 68.614141008123426 8 68.122540425403798 9 67.566942745628936 
		10 66.95955393328714 11 66.313896575601632 12 65.644313853742645 13 64.965559849223055 
		14 64.29248190543511 15 63.63978730117725 16 63.021878922474741 17 62.452746810811988 
		18 61.945888044416257 19 61.51426286957193 20 61.170248132033322 21 60.913233069952931 
		22 60.736055163148599 23 60.6403788653638 24 60.627301019312149 25 60.697360173261906 
		26 60.850536929767571 27 61.086245252264639 28 61.403317070531962 29 61.799968777765628 
		30 62.273759171785926 31 62.821515405955118 32 63.439243427703914 33 64.121979426425725 
		34 64.863616381242537 35 65.656640616251465 36 66.491795194971445 37 67.35761702442943 
		38 68.23987388635787 39 69.120830416952742 40 69.978408758826234 41 70.785134911509971 
		42 71.507845168574477 43 72.112063449045039 44 72.565327932546538 45 72.840477525348319 
		46 72.919239930207482 47 72.795066565817706 48 72.474207109634435 49 71.974573758080695 
		50 71.322875823278679 51 70.551064346679766 52 69.693107247942308 53 68.78260122261446 
		54 67.851355545888879 55 66.928712674654705 56 66.041378020283958 57 65.213480512713701 
		58 64.466772455112732 59 63.820819161690594 60 63.293155209236431 61 62.893859375440101 
		62 62.620715098782696 63 62.469819296200264 64 62.435656043260337 65 62.511440949050865 
		66 62.689334904440628 67 62.960577001790128 68 63.315562538522421 69 63.74389209517161 
		70 64.23440884691459 71 64.775239276017018 72 65.353855873001493 73 65.957151336556521 
		74 66.57160323216516 75 112.81653692454405 76 112.22095160253299 77 111.65487344001214 
		78 111.13060126001979 79 110.65892376155684 80 110.24850289108559;
createNode animCurveTA -n "girl_IKArm_L_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 81 ".ktv[0:80]"  0 -151.41659746213733 1 -154.46657605508537 
		2 22.288148977545678 3 18.899215018217035 4 15.423090105763949 5 11.917638344897862 
		6 8.4383945325954119 7 5.0352145859632644 8 1.749823274580188 9 -1.3854518783599674 
		10 -4.3478003509933574 11 -7.1231112217357735 12 -9.7045805662575937 13 -12.091065555592255 
		14 -14.285442132024398 15 -16.293125488623897 16 -18.120828315334116 17 -19.775557151645543 
		18 -21.263854142887283 19 -22.591175299410271 20 -23.761434364256175 21 -24.798865201702458 
		22 -25.727797423541791 23 -26.549544652471223 24 -27.263731210896729 25 -27.868305050422322 
		26 -28.359521689982735 27 -28.731854616417614 28 -28.977860899239957 29 -29.087966473403345 
		30 -29.050182298595793 31 -28.849726357520673 32 -28.46854432732853 33 -27.884726404274151 
		34 -27.071795650853989 35 -25.997909082214697 36 -24.624998745689439 37 -22.908013770843215 
		38 -20.79443844593942 39 -18.224655536499402 40 -15.13388162104906 41 -11.476119364117313 
		42 -7.2478292759710561 43 -2.4717401175691931 44 2.7862697336957374 45 8.4102808080325442 
		46 14.238981956214413 47 20.084165382297261 48 25.75897651675476 49 31.105948092480002 
		50 36.014502918662565 51 40.424554701403068 52 44.319039480060042 53 47.711572518400665 
		54 50.633896021907852 55 53.125932298218316 56 55.228863329767705 57 56.98091635724662 
		58 58.414905904467503 59 59.556959218142282 60 60.425803088071504 61 61.013765426358617 
		62 61.329218568191692 63 61.400998809373462 64 61.248936339453714 65 60.885682267167347 
		66 60.318080383167569 67 59.548238533382651 68 58.574391806813267 69 57.39164655136198 
		70 55.992678384256642 71 54.368450951493813 72 52.509003878769207 73 50.404450468480036 
		74 48.046027574918604 75 -134.57251429493849 76 -137.45339590895765 77 -140.59317913610431 
		78 -143.98120674413755 79 -147.59840228338237 80 -151.4165974621371;
createNode animCurveTL -n "girl_IKArm_L_translateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 81 ".ktv[0:80]"  0 0.79355824830782362 1 0.79608998119046293 
		2 0.79969215001140626 3 0.80428876762453294 4 0.80979049666711456 5 0.8160963596349684 
		6 0.82309558122072746 7 0.83066954098251822 8 0.83869385036789712 9 0.84704050470305736 
		10 0.85558013341858707 11 0.86418423361447827 12 0.87272738847135356 13 0.88108939002524789 
		14 0.88915720539454757 15 0.89682671920026236 16 0.90400419056307202 17 0.91060731541722406 
		18 0.91656596655225409 19 0.92182230374361884 20 0.92633053004902921 21 0.93010805111438222 
		22 0.93319712286790102 23 0.93560518927399849 24 0.93734923723167363 25 0.93845503920409534 
		26 0.93895634405469286 27 0.93889392688313267 28 0.93831457529328466 29 0.9372699943826972 
		30 0.93581564186530386 31 0.93400953613772808 32 0.93191098708492603 33 0.92957936281022313 
		34 0.9270727456297041 35 0.92444664707158752 36 0.92175266060851824 37 0.91903715189461987 
		38 0.91633982916805401 39 0.91369237893858068 40 0.91111700178749677 41 0.90862319679958903 
		42 0.90620836330415555 43 0.90386771765399132 44 0.90159622911627091 45 0.89938937997856749 
		46 0.89724334805224348 47 0.89515482563440996 48 0.89312046871746986 49 0.89113599576274316 
		50 0.88919516480984706 51 0.88728859908216018 52 0.88540263367105432 53 0.88351815353697694 
		54 0.88160962798941123 55 0.8796442876733126 56 0.87758156853784275 57 0.8753727360167276 
		58 0.87296084146519881 59 0.87028089734275804 60 0.86726036588314015 61 0.86389202018448952 
		62 0.86019858368404378 63 0.85615958020751881 64 0.8517729206341258 65 0.84705632970678479 
		66 0.84204741545285255 67 0.83680313551913477 68 0.83139832023441951 69 0.82592356129069211 
		70 0.82048256365461469 71 0.81518909012896001 72 0.81016359271997729 73 0.8055298668345241 
		74 0.80141130833183993 75 0.79792759796918977 76 0.79519134841023442 77 0.79330499356134387 
		78 0.79235791461081106 79 0.79242380818193592 80 0.79355824830782273;
createNode animCurveTL -n "girl_IKArm_L_translateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 81 ".ktv[0:80]"  0 -0.42486674245465905 1 -0.41921695129857994 
		2 -0.41195224749075149 3 -0.40318059582395588 4 -0.39300834180730954 5 -0.38154113302618486 
		6 -0.36888460759123359 7 -0.35514489430675378 8 -0.34042888740697608 9 -0.32484436175068371 
		10 -0.30849984770420574 11 -0.29150442709944274 12 -0.27396739000629294 13 -0.2559978356560591 
		14 -0.23770426192813379 15 -0.21919419901202872 16 -0.20057392952205114 17 -0.18194847232208008 
		18 -0.16342152403731042 19 -0.14509611537460268 20 -0.12707509110752899 21 -0.10989321877119351 
		22 -0.093990020349726602 23 -0.079330676114195559 24 -0.065886024668146095 25 -0.053632737162824337 
		26 -0.042552992293639832 27 -0.032634424387361805 28 -0.023869645452759037 29 -0.016255979184907152 
		30 -0.0097948423838618882 31 -0.0044912780217897554 32 -0.00035319889967483711 33 
		0.0026092502337290123 34 0.0043846246071446958 35 0.0049610466001399033 36 0.0043272660133974149 
		37 0.0024738633382770624 38 -0.00060539824615119323 39 -0.0049119835161111659 40 
		-0.010440749418184767 41 -0.017003774661683683 42 -0.024461875748607979 43 -0.032860528646145165 
		44 -0.042222450032552983 45 -0.052546812365893508 46 -0.063809953771743894 47 -0.075966916220220865 
		48 -0.088953949984274888 49 -0.1026923197883326 50 -0.11709240533008816 51 -0.13205859731263739 
		52 -0.14749419027800664 53 -0.16330689292342687 54 -0.17941365372009913 55 -0.1957454386806716 
		56 -0.21225108823113167 57 -0.2289010046846682 58 -0.2456893505582671 59 -0.262635573213306 
		60 -0.27978445130729723 61 -0.29660196399652355 62 -0.31253991068635945 63 -0.32763359083774285 
		64 -0.34190585539619983 65 -0.3553642074189719 66 -0.36800024923142483 67 -0.37978920490347889 
		68 -0.39069084397810228 69 -0.40065097233927693 70 -0.40960339476858898 71 -0.4174721592650828 
		72 -0.42417394912061301 73 -0.42962018946846747 74 -0.43371942259856167 75 -0.43637886647551399 
		76 -0.43750579813368029 77 -0.43700838152315735 78 -0.43479594380062758 79 -0.43077864428103646 
		80 -0.42486674245465977;
createNode animCurveTL -n "girl_IKArm_L_translateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 81 ".ktv[0:80]"  0 -0.73641066598519922 1 -0.74242545238273094 
		2 -0.74950222759815288 3 -0.75764481911864534 4 -0.766847415925758 5 -0.7770919684890919 
		6 -0.7883457506321061 7 -0.8005590715885007 8 -0.81366321150494691 9 -0.82756856922966238 
		10 -0.84216314790593627 11 -0.85731129137063711 12 -0.87285278240054232 13 -0.88860228457697044 
		14 -0.90434914082753992 15 -0.91985752704654844 16 -0.93486696390169088 17 -0.94909307804115395 
		18 -0.96222887751590158 19 -0.97394598089380624 20 -0.98389647999624863 21 -0.9921066150101514 
		22 -0.99876417741412304 23 -1.0037551204063249 24 -1.006973927075657 25 -1.0083253005211756 
		26 -1.0077258976331644 27 -1.0051059164997052 28 -1.0004106033273172 29 -0.99360171251835583 
		30 -0.98465876744019687 31 -0.97358039670029917 32 -0.96038533859605735 33 -0.94511378750367092 
		34 -0.92782813484257087 35 -0.90861415662223455 36 -0.88758188672418648 37 -0.86486692909286889 
		38 -0.84063103881625167 39 -0.81506349261343569 40 -0.788382044084738 41 -0.76047631550372619 
		42 -0.73140575899158433 43 -0.70166348553044122 44 -0.67173486482963607 45 -0.64209186653750328 
		46 -0.61318652995892775 47 -0.58544577544500132 48 -0.55926669289906361 49 -0.53501161695518507 
		50 -0.51300499272100542 51 -0.49353054914235095 52 -0.47682983057227046 53 -0.46310096330241213 
		54 -0.45249901061210973 55 -0.44513673990064473 56 -0.44108625235693277 57 -0.44038088429575017 
		58 -0.44301773798896615 59 -0.44896026513548226 60 -0.45814075689008504 61 -0.47023861436779213 
		62 -0.48462562692540723 63 -0.5007849527385253 64 -0.51824372290000276 65 -0.53657088042026579 
		66 -0.55537660266954325 67 -0.57431070181750976 68 -0.59306174023325942 69 -0.61135598787084189 
		70 -0.62895620885742787 71 -0.64566015977611846 72 -0.66129881447726535 73 -0.67573359709559089 
		74 -0.68885425169955838 75 -0.70057510598620876 76 -0.71083145538318848 77 -0.71957542521267381 
		78 -0.72677148548673132 79 -0.73239171638598655 80 -0.73641066598519977;
createNode animCurveTU -n "animCurveTU1118";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1119";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1120";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.4000000000000004 20 1.4000000000000004 
		40 1.4000000000000004 60 1.4000000000000004 80 1.4000000000000004;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1121";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.4000000000000004 20 1.4000000000000004 
		40 1.4000000000000004 60 1.4000000000000004 80 1.4000000000000004;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1122";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.4000000000000004 20 1.4000000000000004 
		40 1.4000000000000004 60 1.4000000000000004 80 1.4000000000000004;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1123";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.4000000000000004 20 1.4000000000000004 
		40 1.4000000000000004 60 1.4000000000000004 80 1.4000000000000004;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1124";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.4000000000000004 20 1.4000000000000004 
		40 1.4000000000000004 60 1.4000000000000004 80 1.4000000000000004;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1125";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 20 1 40 1 60 1;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1126";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 20 1 40 1 60 1;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1127";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 20 1 40 1 60 1;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2152";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2153";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2154";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL754";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL755";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL756";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1128";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 20 1 40 1 60 1;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1129";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 10 20 10 40 10 60 10;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1130";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2155";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2156";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2157";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL757";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL758";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL759";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1131";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 20 1 40 1 60 1;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1132";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 20 1 40 1 60 1;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1133";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 20 1 40 1 60 1;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2158";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2159";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2160";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL760";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL761";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL762";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1134";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 20 1 40 1 60 1;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1135";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2161";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2162";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2163";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL763";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL764";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL765";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1136";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 20 1 40 1 60 1;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1137";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 20 1 40 1 60 1;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1138";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 20 1 40 1 60 1;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2164";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2165";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2166";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL766";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL767";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL768";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1139";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 20 1 40 1 60 1;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1140";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2167";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2168";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2169";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL769";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL770";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL771";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2170";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2171";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 9.9392333795734874e-017 20 9.9392333795734874e-017 
		40 9.9392333795734874e-017 60 9.9392333795734874e-017;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2172";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2173";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2174";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2175";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 9.9392333795734924e-017 20 9.9392333795734924e-017 
		40 9.9392333795734924e-017 60 9.9392333795734924e-017;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2176";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2177";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2178";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2179";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2180";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2181";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 9.9392333795734899e-017 20 9.9392333795734899e-017 
		40 9.9392333795734899e-017 60 9.9392333795734899e-017;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2182";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2183";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2184";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2185";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1141";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 9;
	setAttr -s 5 ".kot[0:4]"  3 5 5 5 5;
createNode animCurveTU -n "animCurveTU1142";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 9;
	setAttr -s 5 ".kot[0:4]"  3 5 5 5 5;
createNode animCurveTU -n "animCurveTU1143";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 20 10 40 10 60 10 80 10;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL772";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL773";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL774";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1144";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 20 10 40 10 60 10 80 10;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL775";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.067033432403714843 20 0.067033432403714843 
		40 0.067033432403714843 60 0.067033432403714843 80 0.067033432403714843;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL776";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.16933803890603863 20 0.16933803890603863 
		40 0.16933803890603863 60 0.16933803890603863 80 0.16933803890603863;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL777";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.57509011135883603 20 0.57509011135883603 
		40 0.57509011135883603 60 0.57509011135883603 80 0.57509011135883603;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2186";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2187";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2188";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL778";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL779";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL780";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1145";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1146";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1147";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1148";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1149";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 25 20 25 40 25 60 25 80 25;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1150";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1151";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1152";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2189";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -16.972634475184972 20 -16.972634475184972 
		40 -16.972634475184972 60 -16.972634475184972 80 -16.972634475184972;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2190";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2191";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL781";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL782";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL783";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.057044533275492443 20 -0.057044533275492443 
		40 -0.057044533275492443 60 -0.057044533275492443 80 -0.057044533275492443;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1153";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 9;
	setAttr -s 5 ".kot[0:4]"  3 5 5 5 5;
createNode animCurveTU -n "animCurveTU1154";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 9;
	setAttr -s 5 ".kot[0:4]"  3 5 5 5 5;
createNode animCurveTU -n "animCurveTU1155";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10 20 10 40 10 60 10 80 10;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL784";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL785";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL786";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1156";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL787";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.1149442041345452 20 -0.097172299753446323 
		40 0.035812779136394912 60 0.71833519872806573 80 0.1149442041345452;
	setAttr -s 5 ".kit[0:4]"  1 9 9 10 1;
	setAttr -s 5 ".kot[0:4]"  1 9 9 10 1;
	setAttr -s 5 ".kix[0:4]"  0.90521645545959473 0.99824345111846924 
		0.8530845046043396 0.99824345111846924 0.89639616012573242;
	setAttr -s 5 ".kiy[0:4]"  -0.42495080828666687 -0.059244319796562195 
		0.52177268266677856 0.059244319796562195 -0.44325387477874756;
	setAttr -s 5 ".kox[0:4]"  0.90521645545959473 0.99824345111846924 
		0.8530845046043396 0.99824345111846924 0.89639604091644287;
	setAttr -s 5 ".koy[0:4]"  -0.42495077848434448 -0.059244319796562195 
		0.52177268266677856 0.059244319796562195 -0.44325393438339233;
createNode animCurveTL -n "animCurveTL788";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.8107021912369119 20 -1.8163251025248037 
		40 -1.4632252176894622 60 -1.5264123973140504 80 -1.8107021912369119;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTL -n "animCurveTL789";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.21088946644300444 20 -0.057595471272524734 
		40 0.024831996062258721 60 -0.26811594263892036 80 -0.21088946644300444;
	setAttr -s 5 ".kit[2:4]"  10 10 1;
	setAttr -s 5 ".kot[2:4]"  10 10 1;
	setAttr -s 5 ".kix[0:4]"  0.9868893027305603 0.95090913772583008 
		0.98776358366012573 0.98472946882247925 0.98107033967971802;
	setAttr -s 5 ".kiy[0:4]"  0.16139885783195496 0.30947020649909973 
		-0.15595835447311401 -0.1740913987159729 0.19365191459655762;
	setAttr -s 5 ".kox[0:4]"  0.9868893027305603 0.95090919733047485 
		0.98776358366012573 0.98472946882247925 0.98107033967971802;
	setAttr -s 5 ".koy[0:4]"  0.16139887273311615 0.30947005748748779 
		-0.15595835447311401 -0.1740913987159729 0.19365191459655762;
createNode animCurveTA -n "animCurveTA2192";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2193";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2194";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL790";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -4.4408920985006262e-016 20 -4.4408920985006262e-016 
		40 -4.4408920985006262e-016 60 -4.4408920985006262e-016;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL791";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1.7347234759768071e-018 20 1.7347234759768071e-018 
		40 1.7347234759768071e-018 60 1.7347234759768071e-018;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL792";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1157";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1158";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1159";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1160";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1161";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "girl_IKArm_R_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 81 ".ktv[0:80]"  0 6.9510950294661136 1 12.448505451561292 
		2 17.739803981373964 3 22.757834605775717 4 27.466067335472815 5 31.853106781297704 
		6 35.925467313715657 7 39.700641296435649 8 43.201512953027802 9 46.452344809805247 
		10 49.476171780688517 11 52.293230340658582 12 54.920107466162584 13 57.36932344457113 
		14 59.649145712100271 15 61.763488452942184 16 63.711795100029619 17 65.488810431786987 
		18 67.08420407595905 19 68.481895833134132 20 69.659066182420133 21 70.617045014839434 
		22 -108.63287803670428 23 -108.10840762782414 24 -107.83283851619956 25 -107.83573464237054 
		26 -108.15379270193495 27 -108.83185617512088 28 -109.92395425637017 29 -111.49406156553307 
		30 -113.61605170096561 31 -116.37174057204568 32 -119.84541776125995 33 -124.11234806168932 
		34 -129.21924433551195 35 -135.15662868995923 36 -141.82990507769495 37 -149.04449023979947 
		38 -156.52369951057273 39 196.03713797836434 40 188.90213041590698 41 182.24265477170255 
		42 176.16963988568492 43 170.72477188655958 44 165.88359102807323 45 161.58597458891506 
		46 157.75854855410714 47 154.32824679395725 48 151.22904260306805 49 148.40439644227527 
		50 145.80760509662474 51 143.40106988984613 52 141.15527840586179 53 139.04769512777978 
		54 137.06188602658051 55 135.18680289187606 56 133.41634378938213 57 131.74909620669746 
		58 130.18842136320765 59 128.74282204229172 60 127.42675566579837 61 126.25390259652384 
		62 125.23401573765577 63 124.38514309986421 64 123.73134179574346 65 123.30344653663008 
		66 123.14029302409071 67 123.290535327732 68 123.81502454581042 69 124.78974779381591 
		70 126.30905676647146 71 128.48834453276118 72 131.46410626417631 73 135.38680788648324 
		74 140.39901229159065 75 146.58824480147712 76 153.91190700666181 77 162.11963599988513 
		78 170.73965882259859 79 179.18732184680266 80 6.9510950294657317;
createNode animCurveTA -n "girl_IKArm_R_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 81 ".ktv[0:80]"  0 -101.09115391664291 1 -101.36576503552337 
		2 -101.72759382944419 3 -102.16396250176888 4 -102.66039959511231 5 -103.20171103695689 
		6 -103.77276906351933 7 -104.359010696138 8 -104.9467028129642 9 -105.52304372997995 
		10 -106.07616949595443 11 -106.59510706431264 12 -107.06970944738053 13 -107.49058996313103 
		14 -107.84906632820503 15 -108.13712038124399 16 -108.3473772540757 17 -108.47310638569557 
		18 -108.50825233238916 19 -108.4474978347082 20 -108.2863765205791 21 -108.03725725200839 
		22 -72.282934858319521 23 -72.670456156656513 24 -73.120677525789404 25 -73.627989865688875 
		26 -74.185669437578525 27 -74.785665513905627 28 -75.418324615557324 29 -76.072005900497331 
		30 -76.732615448273521 31 -77.383041410296329 32 -78.002599724186283 33 -78.566622259831689 
		34 -79.046574317399845 35 -79.411150702857668 36 -79.62888603730643 37 -79.672309291350416 
		38 -79.522702492156654 39 -79.173546697028286 40 -78.63097573505226 41 -77.911289200736576 
		42 -77.037576674976251 43 -76.037754050082555 44 -74.941366161083621 45 -73.777185722144495 
		46 -72.572070306131238 47 -71.350675013123876 48 -70.135584727489075 49 -68.947568071532118 
		50 -67.805902824007703 51 -66.728643699021958 52 -65.732860805733438 53 -64.834784629848102 
		54 -64.049939228524522 55 -63.393208812013043 56 -62.878879484544328 57 -62.520620880670556 
		58 -62.331454931832525 59 -62.323671790278148 60 -62.508697847328527 61 -62.890303093410203 
		62 -63.453787693067547 63 -64.181925345384002 64 -65.057175403346065 65 -66.061527731999973 
		66 -67.176350839856369 67 -68.382100273342076 68 -69.657952931322868 69 -70.981296085553979 
		70 -72.32703454897046 71 -73.66667983192383 72 -74.967239366741211 73 -76.19000098367367 
		74 -77.289838452350466 75 -78.215954938007073 76 -78.916011495072652 77 -79.345147001448169 
		78 -79.478569085112412 79 -79.321451717048717 80 -101.09115391664291;
createNode animCurveTA -n "girl_IKArm_R_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 81 ".ktv[0:80]"  0 -145.58008644013492 1 -140.24458616670435 
		2 -135.25778817649262 3 -130.68065624225636 4 -126.54335342237488 5 -122.85071282647391 
		6 -119.58944685639955 7 -116.73506610573472 8 -114.25745815929744 9 -112.12489629164024 
		10 -110.30665060086829 11 -108.77456547329464 12 -107.50392593679631 13 -106.47389656050068 
		14 -105.66773650649172 15 -105.07293621637683 16 -104.68138007746056 17 -104.48961846167907 
		18 -104.49931806452777 19 -104.71798046095199 20 -105.1600259324477 21 -105.81458151367501 
		22 73.339264833915706 23 72.292063419786658 24 71.028602793953198 25 69.527256741446053 
		26 67.759106414717721 27 65.686959166099086 28 63.264303956478884 29 60.43458962227799 
		30 57.131272966938347 31 53.27981586381685 32 48.803158959196935 33 43.633266717521543 
		34 37.730654303427002 35 31.1120632818897 36 23.879403469967666 37 16.234646485130163 
		38 8.4619408591351188 39 0.87351338634496833 40 -6.2588794311305005 41 -12.777299424150845 
		42 -18.592430451278162 43 -23.666961732831922 44 -28.029502750667621 45 -31.744116197273282 
		46 -34.887910533799364 47 -37.53750472791959 48 -39.762332889116657 49 -41.62221149720029 
		50 -43.16703798307141 51 -44.437557102680465 52 -45.466440761091754 53 -46.27942028702622 
		54 -46.896225849694993 55 -47.331339853206337 56 -47.594501028233282 57 -47.690968637243401 
		58 -47.621489176593442 59 -47.381938423070366 60 -46.962542403529461 61 -46.38236854784131 
		62 -45.667242714186557 63 -44.808220733870506 64 -43.790264481618699 65 -42.59147794172155 
		66 -41.181784718008572 67 -39.521144414320567 68 -37.55715775702518 69 -35.222131503612339 
		70 -32.429859791981919 71 -29.072961496407387 72 -25.022829014567986 73 -20.136807687779832 
		74 -14.280041458923968 75 -7.3726558970594755 76 0.53514883082524634 77 9.1854451912037369 
		78 18.098924209682075 79 26.683420602014351 80 -145.58008644013523;
createNode animCurveTL -n "girl_IKArm_R_translateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 81 ".ktv[0:80]"  0 0.81038048322700762 1 0.80946405780208108 
		2 0.80961348669916822 3 0.81078553486306681 4 0.81292373450350963 5 0.81595971381196186 
		6 0.81981465040029855 7 0.82440085795069384 8 0.82962352092854541 9 0.83538255348843693 
		10 0.84157459945019175 11 0.84809509527048066 12 0.85484038836767162 13 0.86170984553012886 
		14 0.86860789381650028 15 0.87544592796486365 16 0.88214401999980296 17 0.88863231724305169 
		18 0.89485218534499467 19 0.90075678032725737 20 0.9063113066685502 21 0.91149522919814707 
		22 0.91628636409314668 23 0.92066491205675804 24 0.92462238064478264 25 0.92816092013146001 
		26 0.93129261697956212 27 0.93403852855604441 28 0.93642767416916772 29 0.93849581571348972 
		30 0.94028420079597685 31 0.94183814463920079 32 0.94320558771661078 33 0.94443552398769404 
		34 0.94557643644921407 35 0.94667463259086126 36 0.94777256862584558 37 0.94890711269918793 
		38 0.95010781218106954 39 0.95139508516219573 40 0.95277839467282011 41 0.95425327580039676 
		42 0.95579534635501906 43 0.95737408914195932 44 0.95895913053501181 45 0.96052116968603984 
		46 0.96203245130835002 47 0.96346670407842394 48 0.96479864667379944 49 0.96600316418402654 
		50 0.96705412867429708 51 0.96792302257736607 52 0.96857739692652922 53 0.96897929457679144 
		54 0.96908365094508753 55 0.96883678747351754 56 0.96817504528080889 57 0.96702359774286872 
		58 0.96529550307930201 59 0.96289101827836587 60 0.9596972743957739 61 0.95560016762242794 
		62 0.95056965763778223 63 0.94462141085556262 64 0.93779018003892345 65 0.93013230177934769 
		66 0.9217265605461038 67 0.91267448513386906 68 0.90309945480838083 69 0.89314500258614471 
		70 0.88297238756003349 71 0.87275756416157879 72 0.86268761265316218 73 0.85295719865579089 
		74 0.84376411754786051 75 0.83530549703901169 76 0.82777368041666666 77 0.82135231565037037 
		78 0.81621263882312567 79 0.81250996001000564 80 0.81038048322700718;
createNode animCurveTL -n "girl_IKArm_R_translateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 81 ".ktv[0:80]"  0 -0.46421362373332142 1 -0.46689098732753431 
		2 -0.46797819471690577 3 -0.46753425300580548 4 -0.46561562967463771 5 -0.46227735194681163 
		6 -0.4575738932631418 7 -0.45155984579726732 8 -0.4442903685786917 9 -0.43582144019342733 
		10 -0.42620988020751682 11 -0.41551322731567047 12 -0.40378945790049703 13 -0.39109660245145583 
		14 -0.37749230323203914 15 -0.36303336603808906 16 -0.34777535030168139 17 -0.33177235775331254 
		18 -0.31507677574547133 19 -0.29773963716592039 20 -0.2798108369216516 21 -0.26190954775208869 
		22 -0.24459800557807893 23 -0.22784611765670976 24 -0.21163097331350522 25 -0.19593709927228536 
		26 -0.18075612689404852 27 -0.16608680252876337 28 -0.15193444631499547 29 -0.13831073253759257 
		30 -0.12523295676874369 31 -0.11272360255649111 32 -0.10080940981677369 33 -0.089520816486155175 
		34 -0.078890754635109944 35 -0.068953784630611081 36 -0.059744848547157524 37 -0.051298068278231988 
		38 -0.043645020321840193 39 -0.036813099026543887 40 -0.0308233885348052 41 -0.025491716383601086 
		42 -0.020741577780389063 43 -0.016734246469050605 44 -0.013608850383751474 45 -0.0114811070707024 
		46 -0.01044304666402953 47 -0.010563951696509276 48 -0.01189228182167492 49 -0.0144585872319122 
		50 -0.018279263274010076 51 -0.023361000981801876 52 -0.02970563312966059 53 -0.037315450344396782 
		54 -0.046198405066054389 55 -0.056373281499680315 56 -0.067874285808108864 57 -0.080755420384882037 
		58 -0.095093717987616316 59 -0.11099174558610023 60 -0.12857864450025897 61 -0.14730510156341525 
		62 -0.16648266983241289 63 -0.18605024084404664 64 -0.20593984950865793 65 -0.22607197124442879 
		66 -0.24635376110981 67 -0.26667718774279869 68 -0.28691898751046935 69 -0.30694138090213663 
		70 -0.32659348288434326 71 -0.345713199209705 72 -0.36412953440959017 73 -0.38166433784679205 
		74 -0.3981352727790658 75 -0.4133572064445295 76 -0.42714387528978331 77 -0.43930891014114098 
		78 -0.44966627228647466 79 -0.45803010092459301 80 -0.46421362373332148;
createNode animCurveTL -n "girl_IKArm_R_translateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 81 ".ktv[0:80]"  0 1.0451148929299854 1 1.0397615908261379 
		2 1.0335236903357599 3 1.0263934539547492 4 1.0183683445533021 5 1.0094535760597416 
		6 0.99966459871821156 7 0.98902952892694096 8 0.97759145742585785 9 0.96541064134430532 
		10 0.95256646455853389 11 0.93915923494406328 12 0.9253117134652058 13 0.91117038246278625 
		14 0.89690643350998855 15 0.88271646888236366 16 0.8688229072755469 17 0.85547419020035864 
		18 0.84294453910855549 19 0.83153378743976536 20 0.82156664812933866 21 0.81304952381969353 
		22 0.80584638212718462 23 0.80008451120870783 24 0.79588647572366811 25 0.79336809904751304 
		26 0.79263635534142796 27 0.79378742201403552 28 0.79690476668870625 29 0.80205731554547033 
		30 0.80929777809896919 31 0.81866094720124538 32 0.83016228946877568 33 0.84379626961536303 
		34 0.85953521937235744 35 0.87732784078466597 36 0.89709800740079959 37 0.91874317391704863 
		38 0.94213349300086935 39 0.96711021137614162 40 0.99348448251277954 41 1.0213934365768722 
		42 1.0508037189561521 43 1.0812402427476826 44 1.1122237743120262 45 1.143276228027188 
		46 1.1739271525281472 47 1.2037191320510769 48 1.232212975148907 49 1.2589934704223258 
		50 1.2836735532340156 51 1.3058984727022853 52 1.3253487930648804 53 1.34174349312702 
		54 1.3548415976178532 55 1.3644436595366427 56 1.3703925287513599 57 1.372574120969019 
		58 1.3709176680803459 59 1.3653961562096035 60 1.3560270514175059 61 1.3431195403494292 
		62 1.3273630079164929 63 1.3093525977929621 64 1.2896470165188465 65 1.2687678023338362 
		66 1.2471971592124873 67 1.2253772351949159 68 1.2037088381100731 69 1.1825505349343628 
		70 1.1622181265224099 71 1.1429846179987226 72 1.125080663547054 73 1.1086963087419994 
		74 1.0939821751907359 75 1.0810526659122563 76 1.0699892227322645 77 1.0608443827323062 
		78 1.0536464411710686 79 1.0484046228590991 80 1.0451148929299849;
createNode animCurveTA -n "animCurveTA2198";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2199";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2200";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2201";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 7.0568556994971777e-015 20 7.0568556994971777e-015 
		40 7.0568556994971777e-015 60 7.0568556994971777e-015;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2202";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -1.9586709197597583e-031 20 -1.9586709197597583e-031 
		40 -1.9586709197597583e-031 60 -1.9586709197597583e-031;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2203";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -3.1805546814635168e-015 20 -3.1805546814635168e-015 
		40 -3.1805546814635168e-015 60 -3.1805546814635168e-015;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1162";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978 60 0.99999999999999978;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1163";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.99999999999999967 20 0.99999999999999967 
		40 0.99999999999999967 60 0.99999999999999967;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1164";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.99999999999999967 20 0.99999999999999967 
		40 0.99999999999999967 60 0.99999999999999967;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2204";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2205";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2206";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2207";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -9.1440947092076214e-015 20 -9.1440947092076214e-015 
		40 -9.1440947092076214e-015 60 -9.1440947092076214e-015;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2208";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -1.2722218725854075e-014 20 -1.2722218725854075e-014 
		40 -1.2722218725854075e-014 60 -1.2722218725854075e-014;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2209";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 7.5538173684758548e-014 20 7.5538173684758548e-014 
		40 7.5538173684758548e-014 60 7.5538173684758548e-014;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1165";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978 60 0.99999999999999978;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1166";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 20 1 40 1 60 1;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1167";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 20 1 40 1 60 1;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2210";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2211";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2212";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2213";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2214";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2215";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1168";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989 60 0.99999999999999989;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1169";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 20 1 40 1 60 1;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1170";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989 60 0.99999999999999989;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2216";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2217";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2218";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2219";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -4.3255543667903831e-013 20 -4.3255543667903831e-013 
		40 -4.3255543667903831e-013 60 -4.3255543667903831e-013;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2220";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1.2722218725854056e-014 20 1.2722218725854056e-014 
		40 1.2722218725854056e-014 60 1.2722218725854056e-014;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2221";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 3.1805546814635649e-015 20 3.1805546814635649e-015 
		40 3.1805546814635649e-015 60 3.1805546814635649e-015;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1171";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989 60 0.99999999999999989;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1172";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989 60 0.99999999999999989;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1173";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1.0000000000000002 20 1.0000000000000002 
		40 1.0000000000000002 60 1.0000000000000002;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2222";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2223";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2224";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1174";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1.0000000000000002 20 1.0000000000000002 
		40 1.0000000000000002 60 1.0000000000000002;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1175";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 20 1 40 1 60 1;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1176";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 20 1 40 1 60 1;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2225";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -9.5416640443905503e-015 20 -9.5416640443905503e-015 
		40 -9.5416640443905503e-015 60 -9.5416640443905503e-015;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2226";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -1.1131941385122309e-014 20 -1.1131941385122309e-014 
		40 -1.1131941385122309e-014 60 -1.1131941385122309e-014;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2227";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 6.3611093629270327e-015 20 6.3611093629270327e-015 
		40 6.3611093629270327e-015 60 6.3611093629270327e-015;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL796";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL797";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 4.4408920985006262e-016 20 4.4408920985006262e-016 
		40 4.4408920985006262e-016 60 4.4408920985006262e-016;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL798";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -1.1102230246251565e-016 20 -1.1102230246251565e-016 
		40 -1.1102230246251565e-016 60 -1.1102230246251565e-016;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1177";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.0000000000000002 20 1.0000000000000002 
		40 1.0000000000000002 60 1.0000000000000002 80 1.0000000000000002;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1178";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1179";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2228";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 13.761299702586902 20 19.047098868431707 
		40 24.332898034276518 60 19.928065374076208 80 13.761299702586902;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTA -n "animCurveTA2229";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 18.671879421672763 20 17.097999899336919 
		40 15.52412037700107 60 16.70453002200253 80 18.671879421672763;
	setAttr -s 5 ".kit[0:4]"  3 9 10 9 10;
	setAttr -s 5 ".kot[0:4]"  3 9 10 9 10;
createNode animCurveTA -n "animCurveTA2230";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -2.222603041338048 20 8.9826404558288218 
		40 20.187883952995698 60 10.850181135241334 80 -2.222603041338048;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTL -n "animCurveTL799";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.3877787807814457e-017 20 0 40 0 60 
		0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL800";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL801";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.1102230246251565e-016 20 0 40 0 60 
		0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2231";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 6.3611093629270335e-015 20 6.3611093629270335e-015 
		40 6.3611093629270335e-015 60 6.3611093629270335e-015;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2232";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1.2722218725854064e-014 20 1.2722218725854064e-014 
		40 1.2722218725854064e-014 60 1.2722218725854064e-014;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2233";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -1.2722218725854064e-014 20 -1.2722218725854064e-014 
		40 -1.2722218725854064e-014 60 -1.2722218725854064e-014;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1180";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989 60 0.99999999999999989;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1181";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 20 1 40 1 60 1;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1182";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978 60 0.99999999999999978;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2234";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2235";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2236";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2237";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -9.5416640443905519e-015 20 -9.5416640443905519e-015 
		40 -9.5416640443905519e-015 60 -9.5416640443905519e-015;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2238";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -6.3611093629270312e-015 20 -6.3611093629270312e-015 
		40 -6.3611093629270312e-015 60 -6.3611093629270312e-015;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2239";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -2.5444437451708134e-014 20 -2.5444437451708134e-014 
		40 -2.5444437451708134e-014 60 -2.5444437451708134e-014;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1183";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.99999999999999967 20 0.99999999999999967 
		40 0.99999999999999967 60 0.99999999999999967;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1184";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.99999999999999956 20 0.99999999999999956 
		40 0.99999999999999956 60 0.99999999999999956;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1185";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.99999999999999956 20 0.99999999999999956 
		40 0.99999999999999956 60 0.99999999999999956;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2240";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2241";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2242";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2243";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 3.1805546814635152e-015 20 3.1805546814635152e-015 
		40 3.1805546814635152e-015 60 3.1805546814635152e-015;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2244";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -9.5416640443905487e-015 20 -9.5416640443905487e-015 
		40 -9.5416640443905487e-015 60 -9.5416640443905487e-015;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2245";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -1.2722218725854064e-014 20 -1.2722218725854064e-014 
		40 -1.2722218725854064e-014 60 -1.2722218725854064e-014;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1186";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978 60 0.99999999999999978;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1187";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989 60 0.99999999999999989;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1188";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978 60 0.99999999999999978;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2246";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2247";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2248";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2249";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 3.4986101496098681e-014 20 3.4986101496098681e-014 
		40 3.4986101496098681e-014 60 3.4986101496098681e-014;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2250";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -6.3611093629270335e-015 20 -6.3611093629270335e-015 
		40 -6.3611093629270335e-015 60 -6.3611093629270335e-015;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2251";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1.9421187711420696e-030 20 1.9421187711420696e-030 
		40 1.9421187711420696e-030 60 1.9421187711420696e-030;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1189";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1190";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989 60 0.99999999999999989 80 0.99999999999999989;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1191";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.0000000000000002 20 1.0000000000000002 
		40 1.0000000000000002 60 1.0000000000000002 80 1.0000000000000002;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2252";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -11.376097926754165 20 -11.376097926754165 
		40 -11.376097926754165 60 -11.376097926754165 80 -11.376097926754165;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2253";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -2.4214854623005775 20 -2.4214854623005775 
		40 -2.4214854623005775 60 -2.4214854623005775 80 -2.4214854623005775;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2254";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 8.5885793134867772 20 8.5885793134867772 
		40 8.5885793134867772 60 8.5885793134867772 80 8.5885793134867772;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2255";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -3.1805546814635183e-015 20 -3.1805546814635183e-015 
		40 -3.1805546814635183e-015 60 -3.1805546814635183e-015;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2256";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -1.2722218725854067e-014 20 -1.2722218725854067e-014 
		40 -1.2722218725854067e-014 60 -1.2722218725854067e-014;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2257";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -1.2722218725854067e-014 20 -1.2722218725854067e-014 
		40 -1.2722218725854067e-014 60 -1.2722218725854067e-014;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1192";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978 60 0.99999999999999978 80 0.99999999999999978;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1193";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978 60 0.99999999999999978 80 0.99999999999999978;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1194";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999956 20 0.99999999999999956 
		40 0.99999999999999956 60 0.99999999999999956 80 0.99999999999999956;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2258";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2259";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2260";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2261";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -6.3611093629270335e-015 20 -6.3611093629270335e-015 
		40 -6.3611093629270335e-015 60 -6.3611093629270335e-015;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2262";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 6.3611093629270335e-015 20 6.3611093629270335e-015 
		40 6.3611093629270335e-015 60 6.3611093629270335e-015;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2263";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 3.5311250384401278e-031 20 3.5311250384401278e-031 
		40 3.5311250384401278e-031 60 3.5311250384401278e-031;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1195";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978 60 0.99999999999999978 80 0.99999999999999978;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1196";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1197";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2264";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2265";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2266";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2267";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 3.1805546814635176e-015 20 3.1805546814635176e-015 
		40 3.1805546814635176e-015 60 3.1805546814635176e-015;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2268";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -4.7708320221952759e-015 20 -4.7708320221952759e-015 
		40 -4.7708320221952759e-015 60 -4.7708320221952759e-015;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2269";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 9.5416640443905519e-015 20 9.5416640443905519e-015 
		40 9.5416640443905519e-015 60 9.5416640443905519e-015;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1198";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999967 20 0.99999999999999967 
		40 0.99999999999999967 60 0.99999999999999967 80 0.99999999999999967;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1199";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1200";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2270";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.70926765869999764 20 -0.70926765869999764 
		40 -0.70926765869999764 60 -0.70926765869999764 80 -0.70926765869999764;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2271";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -19.59970992257588 20 -19.59970992257588 
		40 -19.59970992257588 60 -19.59970992257588 80 -19.59970992257588;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2272";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 15.579575611036303 20 15.579575611036303 
		40 15.579575611036303 60 15.579575611036303 80 15.579575611036303;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2273";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -2.8624992133171654e-014 20 -2.8624992133171654e-014 
		40 -2.8624992133171654e-014 60 -2.8624992133171654e-014;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2274";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 8.7465253740246656e-015 20 8.7465253740246656e-015 
		40 8.7465253740246656e-015 60 8.7465253740246656e-015;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2275";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 9.5416640443905519e-015 20 9.5416640443905519e-015 
		40 9.5416640443905519e-015 60 9.5416640443905519e-015;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1201";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989 60 0.99999999999999989 80 0.99999999999999989;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1202";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1203";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2276";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 20.33693740949867 20 20.33693740949867 
		40 20.33693740949867 60 20.33693740949867 80 20.33693740949867;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2277";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -14.826892265970072 20 -14.826892265970072 
		40 -14.826892265970072 60 -14.826892265970072 80 -14.826892265970072;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2278";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 48.641881730594498 20 48.641881730594498 
		40 48.641881730594498 60 48.641881730594498 80 48.641881730594498;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2279";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -3.144908237360738e-030 20 -3.144908237360738e-030 
		40 -3.144908237360738e-030 60 -3.144908237360738e-030;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2280";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 3.7769086842379261e-014 20 3.7769086842379261e-014 
		40 3.7769086842379261e-014 60 3.7769086842379261e-014;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2281";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 9.5416640443905503e-015 20 9.5416640443905503e-015 
		40 9.5416640443905503e-015 60 9.5416640443905503e-015;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1204";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978 60 0.99999999999999978 80 0.99999999999999978;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1205";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999933 20 0.99999999999999933 
		40 0.99999999999999933 60 0.99999999999999933 80 0.99999999999999933;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1206";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999967 20 0.99999999999999967 
		40 0.99999999999999967 60 0.99999999999999967 80 0.99999999999999967;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2282";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2283";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2284";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2285";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2286";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2287";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1207";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1.0000000000000002 20 1.0000000000000002 
		40 1.0000000000000002 60 1.0000000000000002;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1208";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1.0000000000000004 20 1.0000000000000004 
		40 1.0000000000000004 60 1.0000000000000004;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1209";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1.0000000000000004 20 1.0000000000000004 
		40 1.0000000000000004 60 1.0000000000000004;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2288";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2289";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2290";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2291";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2292";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2293";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1210";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978 60 0.99999999999999978;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1211";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 20 1 40 1 60 1;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1212";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978 60 0.99999999999999978;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2294";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2295";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2296";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2297";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2298";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2299";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1213";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989 60 0.99999999999999989;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1214";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 20 1 40 1 60 1;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1215";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989 60 0.99999999999999989;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2300";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2301";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2302";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2303";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2304";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2305";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1216";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978 60 0.99999999999999978;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1217";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1.0000000000000002 20 1.0000000000000002 
		40 1.0000000000000002 60 1.0000000000000002;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1218";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 20 1 40 1 60 1;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2306";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2307";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2308";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2309";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2310";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2311";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 4.8525382364188918e-030 20 4.8525382364188918e-030 
		40 4.8525382364188918e-030 60 4.8525382364188918e-030;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1219";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999967 20 0.99999999999999967 
		40 0.99999999999999967 60 0.99999999999999967 80 0.99999999999999967;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1220";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999944 20 0.99999999999999944 
		40 0.99999999999999944 60 0.99999999999999944 80 0.99999999999999944;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1221";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989 60 0.99999999999999989 80 0.99999999999999989;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2312";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 4.569796437176028 20 0.5196373864234034 
		40 -3.5338582958369571 60 -0.16222105335457543 80 4.569796437176028;
	setAttr -s 5 ".kit[0:4]"  3 1 10 1 3;
	setAttr -s 5 ".kot[0:4]"  3 1 10 1 3;
	setAttr -s 5 ".kix[1:4]"  0.98753821849822998 0.99996018409729004 
		0.98643368482589722 1;
	setAttr -s 5 ".kiy[1:4]"  -0.1573793888092041 -0.0089251510798931122 
		0.16416047513484955 0;
	setAttr -s 5 ".kox[1:4]"  0.98753821849822998 0.99996018409729004 
		0.98643368482589722 1;
	setAttr -s 5 ".koy[1:4]"  -0.15737937390804291 -0.0089251510798931122 
		0.16416049003601074 0;
createNode animCurveTA -n "animCurveTA2313";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.21960365775175439 20 1.1695944061600394 
		40 -0.2098222767741828 60 -4.1463579079803248 80 -0.21960365775175439;
	setAttr -s 5 ".kit[0:4]"  1 10 9 10 1;
	setAttr -s 5 ".kot[0:4]"  1 10 9 10 1;
	setAttr -s 5 ".kix[0:4]"  0.99683290719985962 1 0.99758768081665039 
		1 0.99763131141662598;
	setAttr -s 5 ".kiy[0:4]"  0.079525060951709747 0 -0.069417797029018402 
		-0.0001280379801755771 0.068787656724452972;
	setAttr -s 5 ".kox[0:4]"  0.99683290719985962 1 0.99758768081665039 
		1 0.99799144268035889;
	setAttr -s 5 ".koy[0:4]"  0.079525075852870941 0 -0.069417797029018402 
		-0.0001280379801755771 0.063349358737468719;
createNode animCurveTA -n "animCurveTA2314";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.053833699674938937 20 0.06905694230365092 
		40 0.0842523793667279 60 0.069223740474634199 80 0.053833699674938937;
	setAttr -s 5 ".kit[0:4]"  3 1 10 1 10;
	setAttr -s 5 ".kot[0:4]"  3 1 10 1 10;
	setAttr -s 5 ".kix[1:4]"  0.9999997615814209 1 0.9999997615814209 
		1;
	setAttr -s 5 ".kiy[1:4]"  0.00069428997812792659 0 -0.00079762976383790374 
		0;
	setAttr -s 5 ".kox[1:4]"  0.9999997615814209 1 0.99999970197677612 
		1;
	setAttr -s 5 ".koy[1:4]"  0.00069429009454324841 0 -0.00079762993846088648 
		0;
createNode animCurveTA -n "animCurveTA2315";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2316";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2317";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 2.4717875269080888e-030 20 2.4717875269080888e-030 
		40 2.4717875269080888e-030 60 2.4717875269080888e-030;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1222";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1223";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989 60 0.99999999999999989 80 0.99999999999999989;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1224";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989 60 0.99999999999999989 80 0.99999999999999989;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2318";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 2.5646896848981138 20 0.53272339609904562 
		40 -1.5019076397358115 60 0.021221433563283276 80 2.5646896848981138;
	setAttr -s 5 ".kit[0:4]"  3 9 10 9 10;
	setAttr -s 5 ".kot[0:4]"  3 9 10 9 10;
createNode animCurveTA -n "animCurveTA2319";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.27360234726338839 20 1.3695917066982208 
		40 -0.2703007991693715 60 -2.5436488866817157 80 -0.27360234726338839;
	setAttr -s 5 ".kit[1:4]"  10 9 10 9;
	setAttr -s 5 ".kot[1:4]"  10 9 10 9;
createNode animCurveTA -n "animCurveTA2320";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.036842736842407416 20 0.046510468660524197 
		40 0.056152673391622186 60 0.046543040137864596 80 0.036842736842407416;
	setAttr -s 5 ".kit[0:4]"  3 9 10 9 10;
	setAttr -s 5 ".kot[0:4]"  3 9 10 9 10;
createNode animCurveTA -n "animCurveTA2321";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2322";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2323";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -3.1362690564052959e-046 20 -3.1362690564052959e-046 
		40 -3.1362690564052959e-046 60 -3.1362690564052959e-046;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1225";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1226";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1227";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2324";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 7.2041008026261784 20 3.9420731883681581 
		40 0.70238143455663349 60 3.4265781355105469 80 7.2041008026261784;
	setAttr -s 5 ".kit[0:4]"  3 9 10 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 10 9 3;
createNode animCurveTA -n "animCurveTA2325";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.7873084157301844 20 2.2757370451242851 
		40 -1.8051516088437056 60 -6.9482776448356063 80 -1.7873084157301844;
	setAttr -s 5 ".kit[0:4]"  9 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  9 10 10 10 10;
createNode animCurveTA -n "animCurveTA2326";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.2591570400780937 20 -0.15719624942245625 
		40 -0.055141935853686846 60 -0.1582343823652273 80 -0.2591570400780937;
	setAttr -s 5 ".kit[0:4]"  3 9 10 9 10;
	setAttr -s 5 ".kot[0:4]"  3 9 10 9 10;
createNode animCurveTA -n "animCurveTA2327";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2328";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2329";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1228";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999967 20 0.99999999999999967 
		40 0.99999999999999967 60 0.99999999999999967 80 0.99999999999999967;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1229";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999944 20 0.99999999999999944 
		40 0.99999999999999944 60 0.99999999999999944 80 0.99999999999999944;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1230";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989 60 0.99999999999999989 80 0.99999999999999989;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2330";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 6.4585438217471856 20 4.054745932162831 
		40 1.6107840529938051 60 3.4670416533504365 80 6.4585438217471856;
	setAttr -s 5 ".kit[0:4]"  3 9 10 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 10 9 3;
createNode animCurveTA -n "animCurveTA2331";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.3874887135421104 20 -5.7131548194426127 
		40 -0.3874887135421104 60 8.5332089546221308 80 -0.3874887135421104;
	setAttr -s 5 ".kit[0:4]"  9 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  9 10 10 10 10;
createNode animCurveTA -n "animCurveTA2332";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.4486576947588268 20 -1.0716777517293186 
		40 -1.4486576947588268 60 -1.9869370283361074 80 -1.4486576947588268;
	setAttr -s 5 ".kit[1:4]"  10 9 10 9;
	setAttr -s 5 ".kot[1:4]"  10 9 10 9;
createNode animCurveTA -n "animCurveTA2333";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2334";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2335";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1231";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1232";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1233";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2336";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 14.287629093365242 20 16.390185368922072 
		40 18.492741644478901 60 16.915824477882602 80 14.287629093365242;
	setAttr -s 5 ".kit[0:4]"  3 9 10 9 10;
	setAttr -s 5 ".kot[0:4]"  3 9 10 9 10;
createNode animCurveTA -n "animCurveTA2337";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -2.3219135610087638 20 -2.3219135610087633 
		40 -2.3219135610087629 60 -2.3219135610087633 80 -2.3219135610087638;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2338";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.7248128620538499 20 1.7248128620538503 
		40 1.7248128620538508 60 1.7248128620538503 80 1.7248128620538499;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1234";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1.0000000000000002 20 1.0000000000000002 
		40 1.0000000000000002 60 1.0000000000000002;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1235";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1.0000000000000004 20 1.0000000000000004 
		40 1.0000000000000004 60 1.0000000000000004;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1236";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1.0000000000000002 20 1.0000000000000002 
		40 1.0000000000000002 60 1.0000000000000002;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2339";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2340";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2341";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL802";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -1.3877787807814457e-017 20 -1.3877787807814457e-017 
		40 -1.3877787807814457e-017 60 -1.3877787807814457e-017;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL803";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL804";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -1.1102230246251565e-016 20 -1.1102230246251565e-016 
		40 -1.1102230246251565e-016 60 -1.1102230246251565e-016;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1237";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978 60 0.99999999999999978 80 0.99999999999999978;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1238";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978 60 0.99999999999999978 80 0.99999999999999978;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1239";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989 60 0.99999999999999989 80 0.99999999999999989;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2342";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 21.741208243525953 20 24.362966641089603 
		40 26.984725038653245 60 25.018406218144442 80 21.741208243525953;
	setAttr -s 5 ".kit[0:4]"  3 9 10 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 10 9 3;
createNode animCurveTA -n "animCurveTA2343";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 27.471710503044864 20 31.964434040617753 
		40 36.457157578190646 60 32.71322128701128 80 27.471710503044864;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA2344";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -3.8291288436876409 20 0.10696682549966423 
		40 4.0430624946869704 60 0.76298279504159439 80 -3.8291288436876409;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL805";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL806";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 4.4408920985006262e-016 20 0 40 0 60 
		0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL807";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2345";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2346";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2347";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1240";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978 60 0.99999999999999978;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1241";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 20 1 40 1 60 1;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1242";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 20 1 40 1 60 1;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2348";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2349";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2350";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2351";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2352";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2353";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1243";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989 60 0.99999999999999989;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1244";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978 60 0.99999999999999978;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1245";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.99999999999999956 20 0.99999999999999956 
		40 0.99999999999999956 60 0.99999999999999956;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2354";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2355";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2356";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2357";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2358";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2359";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1246";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1.0000000000000002 20 1.0000000000000002 
		40 1.0000000000000002 60 1.0000000000000002;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1247";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 20 1 40 1 60 1;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1248";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1.0000000000000002 20 1.0000000000000002 
		40 1.0000000000000002 60 1.0000000000000002;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2360";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2361";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2362";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2363";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2364";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2365";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1249";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978 60 0.99999999999999978 80 0.99999999999999978;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1250";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1251";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.0000000000000002 20 1.0000000000000002 
		40 1.0000000000000002 60 1.0000000000000002 80 1.0000000000000002;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2366";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 6.5887416381602044 20 6.5887416381602044 
		40 6.5887416381602044 60 6.5887416381602044 80 6.5887416381602044;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2367";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2368";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2369";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2370";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2371";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1252";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999944 20 0.99999999999999944 
		40 0.99999999999999944 60 0.99999999999999944 80 0.99999999999999944;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1253";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999956 20 0.99999999999999956 
		40 0.99999999999999956 60 0.99999999999999956 80 0.99999999999999956;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1254";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999933 20 0.99999999999999933 
		40 0.99999999999999933 60 0.99999999999999933 80 0.99999999999999933;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2372";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10.802160318599565 20 10.802160318599565 
		40 10.802160318599565 60 10.802160318599565 80 10.802160318599565;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2373";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.18093193430354684 20 0.18093193430354684 
		40 0.18093193430354684 60 0.18093193430354684 80 0.18093193430354684;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2374";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -5.5598653650577603 20 -5.5598653650577603 
		40 -5.5598653650577603 60 -5.5598653650577603 80 -5.5598653650577603;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2375";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2376";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2377";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1255";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999967 20 0.99999999999999967 
		40 0.99999999999999967 60 0.99999999999999967 80 0.99999999999999967;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1256";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978 60 0.99999999999999978 80 0.99999999999999978;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1257";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978 60 0.99999999999999978 80 0.99999999999999978;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2378";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2379";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2380";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2381";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2382";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2383";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1258";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989 60 0.99999999999999989 80 0.99999999999999989;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1259";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978 60 0.99999999999999978 80 0.99999999999999978;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1260";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2384";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -5.2487233478977044 20 -5.2487233478977044 
		40 -5.2487233478977044 60 -5.2487233478977044 80 -5.2487233478977044;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2385";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -19.191038692298999 20 -19.191038692298999 
		40 -19.191038692298999 60 -19.191038692298999 80 -19.191038692298999;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2386";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 3.4639940811277468 20 3.4639940811277468 
		40 3.4639940811277468 60 3.4639940811277468 80 3.4639940811277468;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2387";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2388";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2389";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1261";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989 60 0.99999999999999989 80 0.99999999999999989;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1262";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989 60 0.99999999999999989 80 0.99999999999999989;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1263";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978 60 0.99999999999999978 80 0.99999999999999978;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2390";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 15.804493166945804 20 15.804493166945804 
		40 15.804493166945804 60 15.804493166945804 80 15.804493166945804;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2391";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 3.5290061766020497 20 3.5290061766020497 
		40 3.5290061766020497 60 3.5290061766020497 80 3.5290061766020497;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2392";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 55.012788276203878 20 55.012788276203878 
		40 55.012788276203878 60 55.012788276203878 80 55.012788276203878;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2393";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2394";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "animCurveTA2395";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 20 0 40 0 60 0;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "animCurveTU1264";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.0000000000000002 20 1.0000000000000002 
		40 1.0000000000000002 60 1.0000000000000002 80 1.0000000000000002;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1265";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.0000000000000002 20 1.0000000000000002 
		40 1.0000000000000002 60 1.0000000000000002 80 1.0000000000000002;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1266";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2396";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 14.236890325621934 20 14.236890325621934 
		40 14.236890325621934 60 14.236890325621934 80 14.236890325621934;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2397";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.4378573021860341 20 -1.4378573021860341 
		40 -1.4378573021860341 60 -1.4378573021860341 80 -1.4378573021860341;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2398";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 2.5194410123137181 20 2.5194410123137181 
		40 2.5194410123137181 60 2.5194410123137181 80 2.5194410123137181;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1267";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1268";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1269";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2399";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2400";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2401";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL808";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL809";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL810";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 20 0 40 0 60 0 80 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU1270";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 20 1 40 1 60 1 80 1;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 9;
	setAttr -s 5 ".kot[0:4]"  3 5 5 5 5;
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
connectAttr "stunSource.cl" "clipLibrary1.sc[0]";
connectAttr "animCurveTA2052.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "animCurveTA2053.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "animCurveTA2054.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "animCurveTA2055.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "animCurveTA2056.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "animCurveTA2057.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "animCurveTA2058.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "animCurveTA2059.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "animCurveTA2060.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "animCurveTA2061.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "animCurveTA2062.a" "clipLibrary1.cel[0].cev[10].cevr";
connectAttr "animCurveTA2063.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "animCurveTA2064.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "animCurveTA2065.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "animCurveTA2066.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "animCurveTA2067.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "animCurveTA2068.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "animCurveTA2069.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "animCurveTA2070.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "animCurveTA2071.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "animCurveTA2072.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "animCurveTA2073.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "animCurveTA2074.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "animCurveTA2075.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "animCurveTA2076.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "animCurveTA2077.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "animCurveTA2078.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "animCurveTA2079.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "animCurveTA2080.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "animCurveTA2081.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "animCurveTA2082.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "animCurveTA2083.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "animCurveTA2084.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "animCurveTA2085.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "animCurveTA2086.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "animCurveTA2087.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "animCurveTA2088.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "animCurveTA2089.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "animCurveTA2090.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "animCurveTL694.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "animCurveTL695.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "animCurveTL696.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "animCurveTA2091.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "animCurveTA2092.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "animCurveTA2093.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "animCurveTL697.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "animCurveTL698.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "animCurveTL699.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "animCurveTA2094.a" "clipLibrary1.cel[0].cev[48].cevr";
connectAttr "animCurveTA2095.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "animCurveTA2096.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "animCurveTL700.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "animCurveTL701.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "animCurveTL702.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "animCurveTA2097.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "animCurveTA2098.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "animCurveTA2099.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "animCurveTL703.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "animCurveTL704.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "animCurveTL705.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "animCurveTA2100.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "animCurveTA2101.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "animCurveTA2102.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "animCurveTL706.a" "clipLibrary1.cel[0].cev[63].cevr";
connectAttr "animCurveTL707.a" "clipLibrary1.cel[0].cev[64].cevr";
connectAttr "animCurveTL708.a" "clipLibrary1.cel[0].cev[65].cevr";
connectAttr "animCurveTA2103.a" "clipLibrary1.cel[0].cev[66].cevr";
connectAttr "animCurveTA2104.a" "clipLibrary1.cel[0].cev[67].cevr";
connectAttr "animCurveTA2105.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "animCurveTL709.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "animCurveTL710.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "animCurveTL711.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "animCurveTA2106.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "animCurveTA2107.a" "clipLibrary1.cel[0].cev[73].cevr";
connectAttr "animCurveTA2108.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "animCurveTL712.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "animCurveTL713.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "animCurveTL714.a" "clipLibrary1.cel[0].cev[77].cevr";
connectAttr "animCurveTA2109.a" "clipLibrary1.cel[0].cev[78].cevr";
connectAttr "animCurveTA2110.a" "clipLibrary1.cel[0].cev[79].cevr";
connectAttr "animCurveTA2111.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "animCurveTL715.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "animCurveTL716.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "animCurveTL717.a" "clipLibrary1.cel[0].cev[83].cevr";
connectAttr "animCurveTA2112.a" "clipLibrary1.cel[0].cev[84].cevr";
connectAttr "animCurveTA2113.a" "clipLibrary1.cel[0].cev[85].cevr";
connectAttr "animCurveTA2114.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "animCurveTL718.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "animCurveTL719.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "animCurveTL720.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr "animCurveTA2115.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "animCurveTA2116.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "animCurveTA2117.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "animCurveTL721.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "animCurveTL722.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "animCurveTL723.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "animCurveTU1089.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "animCurveTA2118.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "animCurveTA2119.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "animCurveTA2120.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "animCurveTL724.a" "clipLibrary1.cel[0].cev[100].cevr";
connectAttr "animCurveTL725.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "animCurveTL726.a" "clipLibrary1.cel[0].cev[102].cevr";
connectAttr "animCurveTA2121.a" "clipLibrary1.cel[0].cev[103].cevr";
connectAttr "animCurveTA2122.a" "clipLibrary1.cel[0].cev[104].cevr";
connectAttr "animCurveTA2123.a" "clipLibrary1.cel[0].cev[105].cevr";
connectAttr "animCurveTL727.a" "clipLibrary1.cel[0].cev[106].cevr";
connectAttr "animCurveTL728.a" "clipLibrary1.cel[0].cev[107].cevr";
connectAttr "animCurveTL729.a" "clipLibrary1.cel[0].cev[108].cevr";
connectAttr "animCurveTU1090.a" "clipLibrary1.cel[0].cev[109].cevr";
connectAttr "animCurveTU1091.a" "clipLibrary1.cel[0].cev[110].cevr";
connectAttr "animCurveTU1092.a" "clipLibrary1.cel[0].cev[111].cevr";
connectAttr "animCurveTU1093.a" "clipLibrary1.cel[0].cev[112].cevr";
connectAttr "animCurveTU1094.a" "clipLibrary1.cel[0].cev[113].cevr";
connectAttr "animCurveTU1095.a" "clipLibrary1.cel[0].cev[114].cevr";
connectAttr "animCurveTU1096.a" "clipLibrary1.cel[0].cev[115].cevr";
connectAttr "animCurveTA2124.a" "clipLibrary1.cel[0].cev[116].cevr";
connectAttr "animCurveTA2125.a" "clipLibrary1.cel[0].cev[117].cevr";
connectAttr "animCurveTA2126.a" "clipLibrary1.cel[0].cev[118].cevr";
connectAttr "animCurveTA2127.a" "clipLibrary1.cel[0].cev[119].cevr";
connectAttr "animCurveTA2128.a" "clipLibrary1.cel[0].cev[120].cevr";
connectAttr "animCurveTA2129.a" "clipLibrary1.cel[0].cev[121].cevr";
connectAttr "animCurveTA2130.a" "clipLibrary1.cel[0].cev[122].cevr";
connectAttr "animCurveTA2131.a" "clipLibrary1.cel[0].cev[123].cevr";
connectAttr "animCurveTA2132.a" "clipLibrary1.cel[0].cev[124].cevr";
connectAttr "animCurveTA2133.a" "clipLibrary1.cel[0].cev[125].cevr";
connectAttr "animCurveTA2134.a" "clipLibrary1.cel[0].cev[126].cevr";
connectAttr "animCurveTA2135.a" "clipLibrary1.cel[0].cev[127].cevr";
connectAttr "animCurveTA2136.a" "clipLibrary1.cel[0].cev[128].cevr";
connectAttr "animCurveTA2137.a" "clipLibrary1.cel[0].cev[129].cevr";
connectAttr "animCurveTA2138.a" "clipLibrary1.cel[0].cev[130].cevr";
connectAttr "animCurveTA2139.a" "clipLibrary1.cel[0].cev[131].cevr";
connectAttr "animCurveTU1097.a" "clipLibrary1.cel[0].cev[132].cevr";
connectAttr "animCurveTU1098.a" "clipLibrary1.cel[0].cev[133].cevr";
connectAttr "animCurveTU1099.a" "clipLibrary1.cel[0].cev[134].cevr";
connectAttr "animCurveTL730.a" "clipLibrary1.cel[0].cev[135].cevr";
connectAttr "animCurveTL731.a" "clipLibrary1.cel[0].cev[136].cevr";
connectAttr "animCurveTL732.a" "clipLibrary1.cel[0].cev[137].cevr";
connectAttr "animCurveTU1100.a" "clipLibrary1.cel[0].cev[138].cevr";
connectAttr "animCurveTL733.a" "clipLibrary1.cel[0].cev[139].cevr";
connectAttr "animCurveTL734.a" "clipLibrary1.cel[0].cev[140].cevr";
connectAttr "animCurveTL735.a" "clipLibrary1.cel[0].cev[141].cevr";
connectAttr "animCurveTA2140.a" "clipLibrary1.cel[0].cev[142].cevr";
connectAttr "animCurveTA2141.a" "clipLibrary1.cel[0].cev[143].cevr";
connectAttr "animCurveTA2142.a" "clipLibrary1.cel[0].cev[144].cevr";
connectAttr "animCurveTL736.a" "clipLibrary1.cel[0].cev[145].cevr";
connectAttr "animCurveTL737.a" "clipLibrary1.cel[0].cev[146].cevr";
connectAttr "animCurveTL738.a" "clipLibrary1.cel[0].cev[147].cevr";
connectAttr "animCurveTU1101.a" "clipLibrary1.cel[0].cev[148].cevr";
connectAttr "animCurveTU1102.a" "clipLibrary1.cel[0].cev[149].cevr";
connectAttr "animCurveTU1103.a" "clipLibrary1.cel[0].cev[150].cevr";
connectAttr "animCurveTU1104.a" "clipLibrary1.cel[0].cev[151].cevr";
connectAttr "animCurveTU1105.a" "clipLibrary1.cel[0].cev[152].cevr";
connectAttr "animCurveTU1106.a" "clipLibrary1.cel[0].cev[153].cevr";
connectAttr "animCurveTU1107.a" "clipLibrary1.cel[0].cev[154].cevr";
connectAttr "animCurveTU1108.a" "clipLibrary1.cel[0].cev[155].cevr";
connectAttr "animCurveTA2143.a" "clipLibrary1.cel[0].cev[156].cevr";
connectAttr "animCurveTA2144.a" "clipLibrary1.cel[0].cev[157].cevr";
connectAttr "animCurveTA2145.a" "clipLibrary1.cel[0].cev[158].cevr";
connectAttr "animCurveTL739.a" "clipLibrary1.cel[0].cev[159].cevr";
connectAttr "animCurveTL740.a" "clipLibrary1.cel[0].cev[160].cevr";
connectAttr "animCurveTL741.a" "clipLibrary1.cel[0].cev[161].cevr";
connectAttr "animCurveTU1109.a" "clipLibrary1.cel[0].cev[162].cevr";
connectAttr "animCurveTU1110.a" "clipLibrary1.cel[0].cev[163].cevr";
connectAttr "animCurveTU1111.a" "clipLibrary1.cel[0].cev[164].cevr";
connectAttr "animCurveTL742.a" "clipLibrary1.cel[0].cev[165].cevr";
connectAttr "animCurveTL743.a" "clipLibrary1.cel[0].cev[166].cevr";
connectAttr "animCurveTL744.a" "clipLibrary1.cel[0].cev[167].cevr";
connectAttr "animCurveTU1112.a" "clipLibrary1.cel[0].cev[168].cevr";
connectAttr "animCurveTL745.a" "clipLibrary1.cel[0].cev[169].cevr";
connectAttr "animCurveTL746.a" "clipLibrary1.cel[0].cev[170].cevr";
connectAttr "animCurveTL747.a" "clipLibrary1.cel[0].cev[171].cevr";
connectAttr "animCurveTA2146.a" "clipLibrary1.cel[0].cev[172].cevr";
connectAttr "animCurveTA2147.a" "clipLibrary1.cel[0].cev[173].cevr";
connectAttr "animCurveTA2148.a" "clipLibrary1.cel[0].cev[174].cevr";
connectAttr "animCurveTL748.a" "clipLibrary1.cel[0].cev[175].cevr";
connectAttr "animCurveTL749.a" "clipLibrary1.cel[0].cev[176].cevr";
connectAttr "animCurveTL750.a" "clipLibrary1.cel[0].cev[177].cevr";
connectAttr "animCurveTU1113.a" "clipLibrary1.cel[0].cev[178].cevr";
connectAttr "animCurveTU1114.a" "clipLibrary1.cel[0].cev[179].cevr";
connectAttr "animCurveTU1115.a" "clipLibrary1.cel[0].cev[180].cevr";
connectAttr "animCurveTU1116.a" "clipLibrary1.cel[0].cev[181].cevr";
connectAttr "animCurveTU1117.a" "clipLibrary1.cel[0].cev[182].cevr";
connectAttr "girl_IKArm_L_rotateZ1.a" "clipLibrary1.cel[0].cev[183].cevr";
connectAttr "girl_IKArm_L_rotateY1.a" "clipLibrary1.cel[0].cev[184].cevr";
connectAttr "girl_IKArm_L_rotateX1.a" "clipLibrary1.cel[0].cev[185].cevr";
connectAttr "girl_IKArm_L_translateZ1.a" "clipLibrary1.cel[0].cev[186].cevr";
connectAttr "girl_IKArm_L_translateY1.a" "clipLibrary1.cel[0].cev[187].cevr";
connectAttr "girl_IKArm_L_translateX1.a" "clipLibrary1.cel[0].cev[188].cevr";
connectAttr "animCurveTU1118.a" "clipLibrary1.cel[0].cev[189].cevr";
connectAttr "animCurveTU1119.a" "clipLibrary1.cel[0].cev[190].cevr";
connectAttr "animCurveTU1120.a" "clipLibrary1.cel[0].cev[191].cevr";
connectAttr "animCurveTU1121.a" "clipLibrary1.cel[0].cev[192].cevr";
connectAttr "animCurveTU1122.a" "clipLibrary1.cel[0].cev[193].cevr";
connectAttr "animCurveTU1123.a" "clipLibrary1.cel[0].cev[194].cevr";
connectAttr "animCurveTU1124.a" "clipLibrary1.cel[0].cev[195].cevr";
connectAttr "animCurveTU1125.a" "clipLibrary1.cel[0].cev[196].cevr";
connectAttr "animCurveTU1126.a" "clipLibrary1.cel[0].cev[197].cevr";
connectAttr "animCurveTU1127.a" "clipLibrary1.cel[0].cev[198].cevr";
connectAttr "animCurveTA2152.a" "clipLibrary1.cel[0].cev[199].cevr";
connectAttr "animCurveTA2153.a" "clipLibrary1.cel[0].cev[200].cevr";
connectAttr "animCurveTA2154.a" "clipLibrary1.cel[0].cev[201].cevr";
connectAttr "animCurveTL754.a" "clipLibrary1.cel[0].cev[202].cevr";
connectAttr "animCurveTL755.a" "clipLibrary1.cel[0].cev[203].cevr";
connectAttr "animCurveTL756.a" "clipLibrary1.cel[0].cev[204].cevr";
connectAttr "animCurveTU1128.a" "clipLibrary1.cel[0].cev[205].cevr";
connectAttr "animCurveTU1129.a" "clipLibrary1.cel[0].cev[206].cevr";
connectAttr "animCurveTU1130.a" "clipLibrary1.cel[0].cev[207].cevr";
connectAttr "animCurveTA2155.a" "clipLibrary1.cel[0].cev[208].cevr";
connectAttr "animCurveTA2156.a" "clipLibrary1.cel[0].cev[209].cevr";
connectAttr "animCurveTA2157.a" "clipLibrary1.cel[0].cev[210].cevr";
connectAttr "animCurveTL757.a" "clipLibrary1.cel[0].cev[211].cevr";
connectAttr "animCurveTL758.a" "clipLibrary1.cel[0].cev[212].cevr";
connectAttr "animCurveTL759.a" "clipLibrary1.cel[0].cev[213].cevr";
connectAttr "animCurveTU1131.a" "clipLibrary1.cel[0].cev[214].cevr";
connectAttr "animCurveTU1132.a" "clipLibrary1.cel[0].cev[215].cevr";
connectAttr "animCurveTU1133.a" "clipLibrary1.cel[0].cev[216].cevr";
connectAttr "animCurveTA2158.a" "clipLibrary1.cel[0].cev[217].cevr";
connectAttr "animCurveTA2159.a" "clipLibrary1.cel[0].cev[218].cevr";
connectAttr "animCurveTA2160.a" "clipLibrary1.cel[0].cev[219].cevr";
connectAttr "animCurveTL760.a" "clipLibrary1.cel[0].cev[220].cevr";
connectAttr "animCurveTL761.a" "clipLibrary1.cel[0].cev[221].cevr";
connectAttr "animCurveTL762.a" "clipLibrary1.cel[0].cev[222].cevr";
connectAttr "animCurveTU1134.a" "clipLibrary1.cel[0].cev[223].cevr";
connectAttr "animCurveTU1135.a" "clipLibrary1.cel[0].cev[224].cevr";
connectAttr "animCurveTA2161.a" "clipLibrary1.cel[0].cev[225].cevr";
connectAttr "animCurveTA2162.a" "clipLibrary1.cel[0].cev[226].cevr";
connectAttr "animCurveTA2163.a" "clipLibrary1.cel[0].cev[227].cevr";
connectAttr "animCurveTL763.a" "clipLibrary1.cel[0].cev[228].cevr";
connectAttr "animCurveTL764.a" "clipLibrary1.cel[0].cev[229].cevr";
connectAttr "animCurveTL765.a" "clipLibrary1.cel[0].cev[230].cevr";
connectAttr "animCurveTU1136.a" "clipLibrary1.cel[0].cev[231].cevr";
connectAttr "animCurveTU1137.a" "clipLibrary1.cel[0].cev[232].cevr";
connectAttr "animCurveTU1138.a" "clipLibrary1.cel[0].cev[233].cevr";
connectAttr "animCurveTA2164.a" "clipLibrary1.cel[0].cev[234].cevr";
connectAttr "animCurveTA2165.a" "clipLibrary1.cel[0].cev[235].cevr";
connectAttr "animCurveTA2166.a" "clipLibrary1.cel[0].cev[236].cevr";
connectAttr "animCurveTL766.a" "clipLibrary1.cel[0].cev[237].cevr";
connectAttr "animCurveTL767.a" "clipLibrary1.cel[0].cev[238].cevr";
connectAttr "animCurveTL768.a" "clipLibrary1.cel[0].cev[239].cevr";
connectAttr "animCurveTU1139.a" "clipLibrary1.cel[0].cev[240].cevr";
connectAttr "animCurveTU1140.a" "clipLibrary1.cel[0].cev[241].cevr";
connectAttr "animCurveTA2167.a" "clipLibrary1.cel[0].cev[242].cevr";
connectAttr "animCurveTA2168.a" "clipLibrary1.cel[0].cev[243].cevr";
connectAttr "animCurveTA2169.a" "clipLibrary1.cel[0].cev[244].cevr";
connectAttr "animCurveTL769.a" "clipLibrary1.cel[0].cev[245].cevr";
connectAttr "animCurveTL770.a" "clipLibrary1.cel[0].cev[246].cevr";
connectAttr "animCurveTL771.a" "clipLibrary1.cel[0].cev[247].cevr";
connectAttr "animCurveTA2170.a" "clipLibrary1.cel[0].cev[248].cevr";
connectAttr "animCurveTA2171.a" "clipLibrary1.cel[0].cev[249].cevr";
connectAttr "animCurveTA2172.a" "clipLibrary1.cel[0].cev[250].cevr";
connectAttr "animCurveTA2173.a" "clipLibrary1.cel[0].cev[251].cevr";
connectAttr "animCurveTA2174.a" "clipLibrary1.cel[0].cev[252].cevr";
connectAttr "animCurveTA2175.a" "clipLibrary1.cel[0].cev[253].cevr";
connectAttr "animCurveTA2176.a" "clipLibrary1.cel[0].cev[254].cevr";
connectAttr "animCurveTA2177.a" "clipLibrary1.cel[0].cev[255].cevr";
connectAttr "animCurveTA2178.a" "clipLibrary1.cel[0].cev[256].cevr";
connectAttr "animCurveTA2179.a" "clipLibrary1.cel[0].cev[257].cevr";
connectAttr "animCurveTA2180.a" "clipLibrary1.cel[0].cev[258].cevr";
connectAttr "animCurveTA2181.a" "clipLibrary1.cel[0].cev[259].cevr";
connectAttr "animCurveTA2182.a" "clipLibrary1.cel[0].cev[260].cevr";
connectAttr "animCurveTA2183.a" "clipLibrary1.cel[0].cev[261].cevr";
connectAttr "animCurveTA2184.a" "clipLibrary1.cel[0].cev[262].cevr";
connectAttr "animCurveTA2185.a" "clipLibrary1.cel[0].cev[263].cevr";
connectAttr "animCurveTU1141.a" "clipLibrary1.cel[0].cev[264].cevr";
connectAttr "animCurveTU1142.a" "clipLibrary1.cel[0].cev[265].cevr";
connectAttr "animCurveTU1143.a" "clipLibrary1.cel[0].cev[266].cevr";
connectAttr "animCurveTL772.a" "clipLibrary1.cel[0].cev[267].cevr";
connectAttr "animCurveTL773.a" "clipLibrary1.cel[0].cev[268].cevr";
connectAttr "animCurveTL774.a" "clipLibrary1.cel[0].cev[269].cevr";
connectAttr "animCurveTU1144.a" "clipLibrary1.cel[0].cev[270].cevr";
connectAttr "animCurveTL775.a" "clipLibrary1.cel[0].cev[271].cevr";
connectAttr "animCurveTL776.a" "clipLibrary1.cel[0].cev[272].cevr";
connectAttr "animCurveTL777.a" "clipLibrary1.cel[0].cev[273].cevr";
connectAttr "animCurveTA2186.a" "clipLibrary1.cel[0].cev[274].cevr";
connectAttr "animCurveTA2187.a" "clipLibrary1.cel[0].cev[275].cevr";
connectAttr "animCurveTA2188.a" "clipLibrary1.cel[0].cev[276].cevr";
connectAttr "animCurveTL778.a" "clipLibrary1.cel[0].cev[277].cevr";
connectAttr "animCurveTL779.a" "clipLibrary1.cel[0].cev[278].cevr";
connectAttr "animCurveTL780.a" "clipLibrary1.cel[0].cev[279].cevr";
connectAttr "animCurveTU1145.a" "clipLibrary1.cel[0].cev[280].cevr";
connectAttr "animCurveTU1146.a" "clipLibrary1.cel[0].cev[281].cevr";
connectAttr "animCurveTU1147.a" "clipLibrary1.cel[0].cev[282].cevr";
connectAttr "animCurveTU1148.a" "clipLibrary1.cel[0].cev[283].cevr";
connectAttr "animCurveTU1149.a" "clipLibrary1.cel[0].cev[284].cevr";
connectAttr "animCurveTU1150.a" "clipLibrary1.cel[0].cev[285].cevr";
connectAttr "animCurveTU1151.a" "clipLibrary1.cel[0].cev[286].cevr";
connectAttr "animCurveTU1152.a" "clipLibrary1.cel[0].cev[287].cevr";
connectAttr "animCurveTA2189.a" "clipLibrary1.cel[0].cev[288].cevr";
connectAttr "animCurveTA2190.a" "clipLibrary1.cel[0].cev[289].cevr";
connectAttr "animCurveTA2191.a" "clipLibrary1.cel[0].cev[290].cevr";
connectAttr "animCurveTL781.a" "clipLibrary1.cel[0].cev[291].cevr";
connectAttr "animCurveTL782.a" "clipLibrary1.cel[0].cev[292].cevr";
connectAttr "animCurveTL783.a" "clipLibrary1.cel[0].cev[293].cevr";
connectAttr "animCurveTU1153.a" "clipLibrary1.cel[0].cev[294].cevr";
connectAttr "animCurveTU1154.a" "clipLibrary1.cel[0].cev[295].cevr";
connectAttr "animCurveTU1155.a" "clipLibrary1.cel[0].cev[296].cevr";
connectAttr "animCurveTL784.a" "clipLibrary1.cel[0].cev[297].cevr";
connectAttr "animCurveTL785.a" "clipLibrary1.cel[0].cev[298].cevr";
connectAttr "animCurveTL786.a" "clipLibrary1.cel[0].cev[299].cevr";
connectAttr "animCurveTU1156.a" "clipLibrary1.cel[0].cev[300].cevr";
connectAttr "animCurveTL787.a" "clipLibrary1.cel[0].cev[301].cevr";
connectAttr "animCurveTL788.a" "clipLibrary1.cel[0].cev[302].cevr";
connectAttr "animCurveTL789.a" "clipLibrary1.cel[0].cev[303].cevr";
connectAttr "animCurveTA2192.a" "clipLibrary1.cel[0].cev[304].cevr";
connectAttr "animCurveTA2193.a" "clipLibrary1.cel[0].cev[305].cevr";
connectAttr "animCurveTA2194.a" "clipLibrary1.cel[0].cev[306].cevr";
connectAttr "animCurveTL790.a" "clipLibrary1.cel[0].cev[307].cevr";
connectAttr "animCurveTL791.a" "clipLibrary1.cel[0].cev[308].cevr";
connectAttr "animCurveTL792.a" "clipLibrary1.cel[0].cev[309].cevr";
connectAttr "animCurveTU1157.a" "clipLibrary1.cel[0].cev[310].cevr";
connectAttr "animCurveTU1158.a" "clipLibrary1.cel[0].cev[311].cevr";
connectAttr "animCurveTU1159.a" "clipLibrary1.cel[0].cev[312].cevr";
connectAttr "animCurveTU1160.a" "clipLibrary1.cel[0].cev[313].cevr";
connectAttr "animCurveTU1161.a" "clipLibrary1.cel[0].cev[314].cevr";
connectAttr "girl_IKArm_R_rotateZ1.a" "clipLibrary1.cel[0].cev[315].cevr";
connectAttr "girl_IKArm_R_rotateY1.a" "clipLibrary1.cel[0].cev[316].cevr";
connectAttr "girl_IKArm_R_rotateX1.a" "clipLibrary1.cel[0].cev[317].cevr";
connectAttr "girl_IKArm_R_translateZ1.a" "clipLibrary1.cel[0].cev[318].cevr";
connectAttr "girl_IKArm_R_translateY1.a" "clipLibrary1.cel[0].cev[319].cevr";
connectAttr "girl_IKArm_R_translateX1.a" "clipLibrary1.cel[0].cev[320].cevr";
connectAttr "animCurveTA2198.a" "clipLibrary1.cel[0].cev[321].cevr";
connectAttr "animCurveTA2199.a" "clipLibrary1.cel[0].cev[322].cevr";
connectAttr "animCurveTA2200.a" "clipLibrary1.cel[0].cev[323].cevr";
connectAttr "animCurveTA2201.a" "clipLibrary1.cel[0].cev[324].cevr";
connectAttr "animCurveTA2202.a" "clipLibrary1.cel[0].cev[325].cevr";
connectAttr "animCurveTA2203.a" "clipLibrary1.cel[0].cev[326].cevr";
connectAttr "animCurveTU1162.a" "clipLibrary1.cel[0].cev[327].cevr";
connectAttr "animCurveTU1163.a" "clipLibrary1.cel[0].cev[328].cevr";
connectAttr "animCurveTU1164.a" "clipLibrary1.cel[0].cev[329].cevr";
connectAttr "animCurveTA2204.a" "clipLibrary1.cel[0].cev[330].cevr";
connectAttr "animCurveTA2205.a" "clipLibrary1.cel[0].cev[331].cevr";
connectAttr "animCurveTA2206.a" "clipLibrary1.cel[0].cev[332].cevr";
connectAttr "animCurveTA2207.a" "clipLibrary1.cel[0].cev[333].cevr";
connectAttr "animCurveTA2208.a" "clipLibrary1.cel[0].cev[334].cevr";
connectAttr "animCurveTA2209.a" "clipLibrary1.cel[0].cev[335].cevr";
connectAttr "animCurveTU1165.a" "clipLibrary1.cel[0].cev[336].cevr";
connectAttr "animCurveTU1166.a" "clipLibrary1.cel[0].cev[337].cevr";
connectAttr "animCurveTU1167.a" "clipLibrary1.cel[0].cev[338].cevr";
connectAttr "animCurveTA2210.a" "clipLibrary1.cel[0].cev[339].cevr";
connectAttr "animCurveTA2211.a" "clipLibrary1.cel[0].cev[340].cevr";
connectAttr "animCurveTA2212.a" "clipLibrary1.cel[0].cev[341].cevr";
connectAttr "animCurveTA2213.a" "clipLibrary1.cel[0].cev[342].cevr";
connectAttr "animCurveTA2214.a" "clipLibrary1.cel[0].cev[343].cevr";
connectAttr "animCurveTA2215.a" "clipLibrary1.cel[0].cev[344].cevr";
connectAttr "animCurveTU1168.a" "clipLibrary1.cel[0].cev[345].cevr";
connectAttr "animCurveTU1169.a" "clipLibrary1.cel[0].cev[346].cevr";
connectAttr "animCurveTU1170.a" "clipLibrary1.cel[0].cev[347].cevr";
connectAttr "animCurveTA2216.a" "clipLibrary1.cel[0].cev[348].cevr";
connectAttr "animCurveTA2217.a" "clipLibrary1.cel[0].cev[349].cevr";
connectAttr "animCurveTA2218.a" "clipLibrary1.cel[0].cev[350].cevr";
connectAttr "animCurveTA2219.a" "clipLibrary1.cel[0].cev[351].cevr";
connectAttr "animCurveTA2220.a" "clipLibrary1.cel[0].cev[352].cevr";
connectAttr "animCurveTA2221.a" "clipLibrary1.cel[0].cev[353].cevr";
connectAttr "animCurveTU1171.a" "clipLibrary1.cel[0].cev[354].cevr";
connectAttr "animCurveTU1172.a" "clipLibrary1.cel[0].cev[355].cevr";
connectAttr "animCurveTU1173.a" "clipLibrary1.cel[0].cev[356].cevr";
connectAttr "animCurveTA2222.a" "clipLibrary1.cel[0].cev[357].cevr";
connectAttr "animCurveTA2223.a" "clipLibrary1.cel[0].cev[358].cevr";
connectAttr "animCurveTA2224.a" "clipLibrary1.cel[0].cev[359].cevr";
connectAttr "animCurveTU1174.a" "clipLibrary1.cel[0].cev[360].cevr";
connectAttr "animCurveTU1175.a" "clipLibrary1.cel[0].cev[361].cevr";
connectAttr "animCurveTU1176.a" "clipLibrary1.cel[0].cev[362].cevr";
connectAttr "animCurveTA2225.a" "clipLibrary1.cel[0].cev[363].cevr";
connectAttr "animCurveTA2226.a" "clipLibrary1.cel[0].cev[364].cevr";
connectAttr "animCurveTA2227.a" "clipLibrary1.cel[0].cev[365].cevr";
connectAttr "animCurveTL796.a" "clipLibrary1.cel[0].cev[366].cevr";
connectAttr "animCurveTL797.a" "clipLibrary1.cel[0].cev[367].cevr";
connectAttr "animCurveTL798.a" "clipLibrary1.cel[0].cev[368].cevr";
connectAttr "animCurveTU1177.a" "clipLibrary1.cel[0].cev[369].cevr";
connectAttr "animCurveTU1178.a" "clipLibrary1.cel[0].cev[370].cevr";
connectAttr "animCurveTU1179.a" "clipLibrary1.cel[0].cev[371].cevr";
connectAttr "animCurveTA2228.a" "clipLibrary1.cel[0].cev[372].cevr";
connectAttr "animCurveTA2229.a" "clipLibrary1.cel[0].cev[373].cevr";
connectAttr "animCurveTA2230.a" "clipLibrary1.cel[0].cev[374].cevr";
connectAttr "animCurveTL799.a" "clipLibrary1.cel[0].cev[375].cevr";
connectAttr "animCurveTL800.a" "clipLibrary1.cel[0].cev[376].cevr";
connectAttr "animCurveTL801.a" "clipLibrary1.cel[0].cev[377].cevr";
connectAttr "animCurveTA2231.a" "clipLibrary1.cel[0].cev[378].cevr";
connectAttr "animCurveTA2232.a" "clipLibrary1.cel[0].cev[379].cevr";
connectAttr "animCurveTA2233.a" "clipLibrary1.cel[0].cev[380].cevr";
connectAttr "animCurveTU1180.a" "clipLibrary1.cel[0].cev[381].cevr";
connectAttr "animCurveTU1181.a" "clipLibrary1.cel[0].cev[382].cevr";
connectAttr "animCurveTU1182.a" "clipLibrary1.cel[0].cev[383].cevr";
connectAttr "animCurveTA2234.a" "clipLibrary1.cel[0].cev[384].cevr";
connectAttr "animCurveTA2235.a" "clipLibrary1.cel[0].cev[385].cevr";
connectAttr "animCurveTA2236.a" "clipLibrary1.cel[0].cev[386].cevr";
connectAttr "animCurveTA2237.a" "clipLibrary1.cel[0].cev[387].cevr";
connectAttr "animCurveTA2238.a" "clipLibrary1.cel[0].cev[388].cevr";
connectAttr "animCurveTA2239.a" "clipLibrary1.cel[0].cev[389].cevr";
connectAttr "animCurveTU1183.a" "clipLibrary1.cel[0].cev[390].cevr";
connectAttr "animCurveTU1184.a" "clipLibrary1.cel[0].cev[391].cevr";
connectAttr "animCurveTU1185.a" "clipLibrary1.cel[0].cev[392].cevr";
connectAttr "animCurveTA2240.a" "clipLibrary1.cel[0].cev[393].cevr";
connectAttr "animCurveTA2241.a" "clipLibrary1.cel[0].cev[394].cevr";
connectAttr "animCurveTA2242.a" "clipLibrary1.cel[0].cev[395].cevr";
connectAttr "animCurveTA2243.a" "clipLibrary1.cel[0].cev[396].cevr";
connectAttr "animCurveTA2244.a" "clipLibrary1.cel[0].cev[397].cevr";
connectAttr "animCurveTA2245.a" "clipLibrary1.cel[0].cev[398].cevr";
connectAttr "animCurveTU1186.a" "clipLibrary1.cel[0].cev[399].cevr";
connectAttr "animCurveTU1187.a" "clipLibrary1.cel[0].cev[400].cevr";
connectAttr "animCurveTU1188.a" "clipLibrary1.cel[0].cev[401].cevr";
connectAttr "animCurveTA2246.a" "clipLibrary1.cel[0].cev[402].cevr";
connectAttr "animCurveTA2247.a" "clipLibrary1.cel[0].cev[403].cevr";
connectAttr "animCurveTA2248.a" "clipLibrary1.cel[0].cev[404].cevr";
connectAttr "animCurveTA2249.a" "clipLibrary1.cel[0].cev[405].cevr";
connectAttr "animCurveTA2250.a" "clipLibrary1.cel[0].cev[406].cevr";
connectAttr "animCurveTA2251.a" "clipLibrary1.cel[0].cev[407].cevr";
connectAttr "animCurveTU1189.a" "clipLibrary1.cel[0].cev[408].cevr";
connectAttr "animCurveTU1190.a" "clipLibrary1.cel[0].cev[409].cevr";
connectAttr "animCurveTU1191.a" "clipLibrary1.cel[0].cev[410].cevr";
connectAttr "animCurveTA2252.a" "clipLibrary1.cel[0].cev[411].cevr";
connectAttr "animCurveTA2253.a" "clipLibrary1.cel[0].cev[412].cevr";
connectAttr "animCurveTA2254.a" "clipLibrary1.cel[0].cev[413].cevr";
connectAttr "animCurveTA2255.a" "clipLibrary1.cel[0].cev[414].cevr";
connectAttr "animCurveTA2256.a" "clipLibrary1.cel[0].cev[415].cevr";
connectAttr "animCurveTA2257.a" "clipLibrary1.cel[0].cev[416].cevr";
connectAttr "animCurveTU1192.a" "clipLibrary1.cel[0].cev[417].cevr";
connectAttr "animCurveTU1193.a" "clipLibrary1.cel[0].cev[418].cevr";
connectAttr "animCurveTU1194.a" "clipLibrary1.cel[0].cev[419].cevr";
connectAttr "animCurveTA2258.a" "clipLibrary1.cel[0].cev[420].cevr";
connectAttr "animCurveTA2259.a" "clipLibrary1.cel[0].cev[421].cevr";
connectAttr "animCurveTA2260.a" "clipLibrary1.cel[0].cev[422].cevr";
connectAttr "animCurveTA2261.a" "clipLibrary1.cel[0].cev[423].cevr";
connectAttr "animCurveTA2262.a" "clipLibrary1.cel[0].cev[424].cevr";
connectAttr "animCurveTA2263.a" "clipLibrary1.cel[0].cev[425].cevr";
connectAttr "animCurveTU1195.a" "clipLibrary1.cel[0].cev[426].cevr";
connectAttr "animCurveTU1196.a" "clipLibrary1.cel[0].cev[427].cevr";
connectAttr "animCurveTU1197.a" "clipLibrary1.cel[0].cev[428].cevr";
connectAttr "animCurveTA2264.a" "clipLibrary1.cel[0].cev[429].cevr";
connectAttr "animCurveTA2265.a" "clipLibrary1.cel[0].cev[430].cevr";
connectAttr "animCurveTA2266.a" "clipLibrary1.cel[0].cev[431].cevr";
connectAttr "animCurveTA2267.a" "clipLibrary1.cel[0].cev[432].cevr";
connectAttr "animCurveTA2268.a" "clipLibrary1.cel[0].cev[433].cevr";
connectAttr "animCurveTA2269.a" "clipLibrary1.cel[0].cev[434].cevr";
connectAttr "animCurveTU1198.a" "clipLibrary1.cel[0].cev[435].cevr";
connectAttr "animCurveTU1199.a" "clipLibrary1.cel[0].cev[436].cevr";
connectAttr "animCurveTU1200.a" "clipLibrary1.cel[0].cev[437].cevr";
connectAttr "animCurveTA2270.a" "clipLibrary1.cel[0].cev[438].cevr";
connectAttr "animCurveTA2271.a" "clipLibrary1.cel[0].cev[439].cevr";
connectAttr "animCurveTA2272.a" "clipLibrary1.cel[0].cev[440].cevr";
connectAttr "animCurveTA2273.a" "clipLibrary1.cel[0].cev[441].cevr";
connectAttr "animCurveTA2274.a" "clipLibrary1.cel[0].cev[442].cevr";
connectAttr "animCurveTA2275.a" "clipLibrary1.cel[0].cev[443].cevr";
connectAttr "animCurveTU1201.a" "clipLibrary1.cel[0].cev[444].cevr";
connectAttr "animCurveTU1202.a" "clipLibrary1.cel[0].cev[445].cevr";
connectAttr "animCurveTU1203.a" "clipLibrary1.cel[0].cev[446].cevr";
connectAttr "animCurveTA2276.a" "clipLibrary1.cel[0].cev[447].cevr";
connectAttr "animCurveTA2277.a" "clipLibrary1.cel[0].cev[448].cevr";
connectAttr "animCurveTA2278.a" "clipLibrary1.cel[0].cev[449].cevr";
connectAttr "animCurveTA2279.a" "clipLibrary1.cel[0].cev[450].cevr";
connectAttr "animCurveTA2280.a" "clipLibrary1.cel[0].cev[451].cevr";
connectAttr "animCurveTA2281.a" "clipLibrary1.cel[0].cev[452].cevr";
connectAttr "animCurveTU1204.a" "clipLibrary1.cel[0].cev[453].cevr";
connectAttr "animCurveTU1205.a" "clipLibrary1.cel[0].cev[454].cevr";
connectAttr "animCurveTU1206.a" "clipLibrary1.cel[0].cev[455].cevr";
connectAttr "animCurveTA2282.a" "clipLibrary1.cel[0].cev[456].cevr";
connectAttr "animCurveTA2283.a" "clipLibrary1.cel[0].cev[457].cevr";
connectAttr "animCurveTA2284.a" "clipLibrary1.cel[0].cev[458].cevr";
connectAttr "animCurveTA2285.a" "clipLibrary1.cel[0].cev[459].cevr";
connectAttr "animCurveTA2286.a" "clipLibrary1.cel[0].cev[460].cevr";
connectAttr "animCurveTA2287.a" "clipLibrary1.cel[0].cev[461].cevr";
connectAttr "animCurveTU1207.a" "clipLibrary1.cel[0].cev[462].cevr";
connectAttr "animCurveTU1208.a" "clipLibrary1.cel[0].cev[463].cevr";
connectAttr "animCurveTU1209.a" "clipLibrary1.cel[0].cev[464].cevr";
connectAttr "animCurveTA2288.a" "clipLibrary1.cel[0].cev[465].cevr";
connectAttr "animCurveTA2289.a" "clipLibrary1.cel[0].cev[466].cevr";
connectAttr "animCurveTA2290.a" "clipLibrary1.cel[0].cev[467].cevr";
connectAttr "animCurveTA2291.a" "clipLibrary1.cel[0].cev[468].cevr";
connectAttr "animCurveTA2292.a" "clipLibrary1.cel[0].cev[469].cevr";
connectAttr "animCurveTA2293.a" "clipLibrary1.cel[0].cev[470].cevr";
connectAttr "animCurveTU1210.a" "clipLibrary1.cel[0].cev[471].cevr";
connectAttr "animCurveTU1211.a" "clipLibrary1.cel[0].cev[472].cevr";
connectAttr "animCurveTU1212.a" "clipLibrary1.cel[0].cev[473].cevr";
connectAttr "animCurveTA2294.a" "clipLibrary1.cel[0].cev[474].cevr";
connectAttr "animCurveTA2295.a" "clipLibrary1.cel[0].cev[475].cevr";
connectAttr "animCurveTA2296.a" "clipLibrary1.cel[0].cev[476].cevr";
connectAttr "animCurveTA2297.a" "clipLibrary1.cel[0].cev[477].cevr";
connectAttr "animCurveTA2298.a" "clipLibrary1.cel[0].cev[478].cevr";
connectAttr "animCurveTA2299.a" "clipLibrary1.cel[0].cev[479].cevr";
connectAttr "animCurveTU1213.a" "clipLibrary1.cel[0].cev[480].cevr";
connectAttr "animCurveTU1214.a" "clipLibrary1.cel[0].cev[481].cevr";
connectAttr "animCurveTU1215.a" "clipLibrary1.cel[0].cev[482].cevr";
connectAttr "animCurveTA2300.a" "clipLibrary1.cel[0].cev[483].cevr";
connectAttr "animCurveTA2301.a" "clipLibrary1.cel[0].cev[484].cevr";
connectAttr "animCurveTA2302.a" "clipLibrary1.cel[0].cev[485].cevr";
connectAttr "animCurveTA2303.a" "clipLibrary1.cel[0].cev[486].cevr";
connectAttr "animCurveTA2304.a" "clipLibrary1.cel[0].cev[487].cevr";
connectAttr "animCurveTA2305.a" "clipLibrary1.cel[0].cev[488].cevr";
connectAttr "animCurveTU1216.a" "clipLibrary1.cel[0].cev[489].cevr";
connectAttr "animCurveTU1217.a" "clipLibrary1.cel[0].cev[490].cevr";
connectAttr "animCurveTU1218.a" "clipLibrary1.cel[0].cev[491].cevr";
connectAttr "animCurveTA2306.a" "clipLibrary1.cel[0].cev[492].cevr";
connectAttr "animCurveTA2307.a" "clipLibrary1.cel[0].cev[493].cevr";
connectAttr "animCurveTA2308.a" "clipLibrary1.cel[0].cev[494].cevr";
connectAttr "animCurveTA2309.a" "clipLibrary1.cel[0].cev[495].cevr";
connectAttr "animCurveTA2310.a" "clipLibrary1.cel[0].cev[496].cevr";
connectAttr "animCurveTA2311.a" "clipLibrary1.cel[0].cev[497].cevr";
connectAttr "animCurveTU1219.a" "clipLibrary1.cel[0].cev[498].cevr";
connectAttr "animCurveTU1220.a" "clipLibrary1.cel[0].cev[499].cevr";
connectAttr "animCurveTU1221.a" "clipLibrary1.cel[0].cev[500].cevr";
connectAttr "animCurveTA2312.a" "clipLibrary1.cel[0].cev[501].cevr";
connectAttr "animCurveTA2313.a" "clipLibrary1.cel[0].cev[502].cevr";
connectAttr "animCurveTA2314.a" "clipLibrary1.cel[0].cev[503].cevr";
connectAttr "animCurveTA2315.a" "clipLibrary1.cel[0].cev[504].cevr";
connectAttr "animCurveTA2316.a" "clipLibrary1.cel[0].cev[505].cevr";
connectAttr "animCurveTA2317.a" "clipLibrary1.cel[0].cev[506].cevr";
connectAttr "animCurveTU1222.a" "clipLibrary1.cel[0].cev[507].cevr";
connectAttr "animCurveTU1223.a" "clipLibrary1.cel[0].cev[508].cevr";
connectAttr "animCurveTU1224.a" "clipLibrary1.cel[0].cev[509].cevr";
connectAttr "animCurveTA2318.a" "clipLibrary1.cel[0].cev[510].cevr";
connectAttr "animCurveTA2319.a" "clipLibrary1.cel[0].cev[511].cevr";
connectAttr "animCurveTA2320.a" "clipLibrary1.cel[0].cev[512].cevr";
connectAttr "animCurveTA2321.a" "clipLibrary1.cel[0].cev[513].cevr";
connectAttr "animCurveTA2322.a" "clipLibrary1.cel[0].cev[514].cevr";
connectAttr "animCurveTA2323.a" "clipLibrary1.cel[0].cev[515].cevr";
connectAttr "animCurveTU1225.a" "clipLibrary1.cel[0].cev[516].cevr";
connectAttr "animCurveTU1226.a" "clipLibrary1.cel[0].cev[517].cevr";
connectAttr "animCurveTU1227.a" "clipLibrary1.cel[0].cev[518].cevr";
connectAttr "animCurveTA2324.a" "clipLibrary1.cel[0].cev[519].cevr";
connectAttr "animCurveTA2325.a" "clipLibrary1.cel[0].cev[520].cevr";
connectAttr "animCurveTA2326.a" "clipLibrary1.cel[0].cev[521].cevr";
connectAttr "animCurveTA2327.a" "clipLibrary1.cel[0].cev[522].cevr";
connectAttr "animCurveTA2328.a" "clipLibrary1.cel[0].cev[523].cevr";
connectAttr "animCurveTA2329.a" "clipLibrary1.cel[0].cev[524].cevr";
connectAttr "animCurveTU1228.a" "clipLibrary1.cel[0].cev[525].cevr";
connectAttr "animCurveTU1229.a" "clipLibrary1.cel[0].cev[526].cevr";
connectAttr "animCurveTU1230.a" "clipLibrary1.cel[0].cev[527].cevr";
connectAttr "animCurveTA2330.a" "clipLibrary1.cel[0].cev[528].cevr";
connectAttr "animCurveTA2331.a" "clipLibrary1.cel[0].cev[529].cevr";
connectAttr "animCurveTA2332.a" "clipLibrary1.cel[0].cev[530].cevr";
connectAttr "animCurveTA2333.a" "clipLibrary1.cel[0].cev[531].cevr";
connectAttr "animCurveTA2334.a" "clipLibrary1.cel[0].cev[532].cevr";
connectAttr "animCurveTA2335.a" "clipLibrary1.cel[0].cev[533].cevr";
connectAttr "animCurveTU1231.a" "clipLibrary1.cel[0].cev[534].cevr";
connectAttr "animCurveTU1232.a" "clipLibrary1.cel[0].cev[535].cevr";
connectAttr "animCurveTU1233.a" "clipLibrary1.cel[0].cev[536].cevr";
connectAttr "animCurveTA2336.a" "clipLibrary1.cel[0].cev[537].cevr";
connectAttr "animCurveTA2337.a" "clipLibrary1.cel[0].cev[538].cevr";
connectAttr "animCurveTA2338.a" "clipLibrary1.cel[0].cev[539].cevr";
connectAttr "animCurveTU1234.a" "clipLibrary1.cel[0].cev[540].cevr";
connectAttr "animCurveTU1235.a" "clipLibrary1.cel[0].cev[541].cevr";
connectAttr "animCurveTU1236.a" "clipLibrary1.cel[0].cev[542].cevr";
connectAttr "animCurveTA2339.a" "clipLibrary1.cel[0].cev[543].cevr";
connectAttr "animCurveTA2340.a" "clipLibrary1.cel[0].cev[544].cevr";
connectAttr "animCurveTA2341.a" "clipLibrary1.cel[0].cev[545].cevr";
connectAttr "animCurveTL802.a" "clipLibrary1.cel[0].cev[546].cevr";
connectAttr "animCurveTL803.a" "clipLibrary1.cel[0].cev[547].cevr";
connectAttr "animCurveTL804.a" "clipLibrary1.cel[0].cev[548].cevr";
connectAttr "animCurveTU1237.a" "clipLibrary1.cel[0].cev[549].cevr";
connectAttr "animCurveTU1238.a" "clipLibrary1.cel[0].cev[550].cevr";
connectAttr "animCurveTU1239.a" "clipLibrary1.cel[0].cev[551].cevr";
connectAttr "animCurveTA2342.a" "clipLibrary1.cel[0].cev[552].cevr";
connectAttr "animCurveTA2343.a" "clipLibrary1.cel[0].cev[553].cevr";
connectAttr "animCurveTA2344.a" "clipLibrary1.cel[0].cev[554].cevr";
connectAttr "animCurveTL805.a" "clipLibrary1.cel[0].cev[555].cevr";
connectAttr "animCurveTL806.a" "clipLibrary1.cel[0].cev[556].cevr";
connectAttr "animCurveTL807.a" "clipLibrary1.cel[0].cev[557].cevr";
connectAttr "animCurveTA2345.a" "clipLibrary1.cel[0].cev[558].cevr";
connectAttr "animCurveTA2346.a" "clipLibrary1.cel[0].cev[559].cevr";
connectAttr "animCurveTA2347.a" "clipLibrary1.cel[0].cev[560].cevr";
connectAttr "animCurveTU1240.a" "clipLibrary1.cel[0].cev[561].cevr";
connectAttr "animCurveTU1241.a" "clipLibrary1.cel[0].cev[562].cevr";
connectAttr "animCurveTU1242.a" "clipLibrary1.cel[0].cev[563].cevr";
connectAttr "animCurveTA2348.a" "clipLibrary1.cel[0].cev[564].cevr";
connectAttr "animCurveTA2349.a" "clipLibrary1.cel[0].cev[565].cevr";
connectAttr "animCurveTA2350.a" "clipLibrary1.cel[0].cev[566].cevr";
connectAttr "animCurveTA2351.a" "clipLibrary1.cel[0].cev[567].cevr";
connectAttr "animCurveTA2352.a" "clipLibrary1.cel[0].cev[568].cevr";
connectAttr "animCurveTA2353.a" "clipLibrary1.cel[0].cev[569].cevr";
connectAttr "animCurveTU1243.a" "clipLibrary1.cel[0].cev[570].cevr";
connectAttr "animCurveTU1244.a" "clipLibrary1.cel[0].cev[571].cevr";
connectAttr "animCurveTU1245.a" "clipLibrary1.cel[0].cev[572].cevr";
connectAttr "animCurveTA2354.a" "clipLibrary1.cel[0].cev[573].cevr";
connectAttr "animCurveTA2355.a" "clipLibrary1.cel[0].cev[574].cevr";
connectAttr "animCurveTA2356.a" "clipLibrary1.cel[0].cev[575].cevr";
connectAttr "animCurveTA2357.a" "clipLibrary1.cel[0].cev[576].cevr";
connectAttr "animCurveTA2358.a" "clipLibrary1.cel[0].cev[577].cevr";
connectAttr "animCurveTA2359.a" "clipLibrary1.cel[0].cev[578].cevr";
connectAttr "animCurveTU1246.a" "clipLibrary1.cel[0].cev[579].cevr";
connectAttr "animCurveTU1247.a" "clipLibrary1.cel[0].cev[580].cevr";
connectAttr "animCurveTU1248.a" "clipLibrary1.cel[0].cev[581].cevr";
connectAttr "animCurveTA2360.a" "clipLibrary1.cel[0].cev[582].cevr";
connectAttr "animCurveTA2361.a" "clipLibrary1.cel[0].cev[583].cevr";
connectAttr "animCurveTA2362.a" "clipLibrary1.cel[0].cev[584].cevr";
connectAttr "animCurveTA2363.a" "clipLibrary1.cel[0].cev[585].cevr";
connectAttr "animCurveTA2364.a" "clipLibrary1.cel[0].cev[586].cevr";
connectAttr "animCurveTA2365.a" "clipLibrary1.cel[0].cev[587].cevr";
connectAttr "animCurveTU1249.a" "clipLibrary1.cel[0].cev[588].cevr";
connectAttr "animCurveTU1250.a" "clipLibrary1.cel[0].cev[589].cevr";
connectAttr "animCurveTU1251.a" "clipLibrary1.cel[0].cev[590].cevr";
connectAttr "animCurveTA2366.a" "clipLibrary1.cel[0].cev[591].cevr";
connectAttr "animCurveTA2367.a" "clipLibrary1.cel[0].cev[592].cevr";
connectAttr "animCurveTA2368.a" "clipLibrary1.cel[0].cev[593].cevr";
connectAttr "animCurveTA2369.a" "clipLibrary1.cel[0].cev[594].cevr";
connectAttr "animCurveTA2370.a" "clipLibrary1.cel[0].cev[595].cevr";
connectAttr "animCurveTA2371.a" "clipLibrary1.cel[0].cev[596].cevr";
connectAttr "animCurveTU1252.a" "clipLibrary1.cel[0].cev[597].cevr";
connectAttr "animCurveTU1253.a" "clipLibrary1.cel[0].cev[598].cevr";
connectAttr "animCurveTU1254.a" "clipLibrary1.cel[0].cev[599].cevr";
connectAttr "animCurveTA2372.a" "clipLibrary1.cel[0].cev[600].cevr";
connectAttr "animCurveTA2373.a" "clipLibrary1.cel[0].cev[601].cevr";
connectAttr "animCurveTA2374.a" "clipLibrary1.cel[0].cev[602].cevr";
connectAttr "animCurveTA2375.a" "clipLibrary1.cel[0].cev[603].cevr";
connectAttr "animCurveTA2376.a" "clipLibrary1.cel[0].cev[604].cevr";
connectAttr "animCurveTA2377.a" "clipLibrary1.cel[0].cev[605].cevr";
connectAttr "animCurveTU1255.a" "clipLibrary1.cel[0].cev[606].cevr";
connectAttr "animCurveTU1256.a" "clipLibrary1.cel[0].cev[607].cevr";
connectAttr "animCurveTU1257.a" "clipLibrary1.cel[0].cev[608].cevr";
connectAttr "animCurveTA2378.a" "clipLibrary1.cel[0].cev[609].cevr";
connectAttr "animCurveTA2379.a" "clipLibrary1.cel[0].cev[610].cevr";
connectAttr "animCurveTA2380.a" "clipLibrary1.cel[0].cev[611].cevr";
connectAttr "animCurveTA2381.a" "clipLibrary1.cel[0].cev[612].cevr";
connectAttr "animCurveTA2382.a" "clipLibrary1.cel[0].cev[613].cevr";
connectAttr "animCurveTA2383.a" "clipLibrary1.cel[0].cev[614].cevr";
connectAttr "animCurveTU1258.a" "clipLibrary1.cel[0].cev[615].cevr";
connectAttr "animCurveTU1259.a" "clipLibrary1.cel[0].cev[616].cevr";
connectAttr "animCurveTU1260.a" "clipLibrary1.cel[0].cev[617].cevr";
connectAttr "animCurveTA2384.a" "clipLibrary1.cel[0].cev[618].cevr";
connectAttr "animCurveTA2385.a" "clipLibrary1.cel[0].cev[619].cevr";
connectAttr "animCurveTA2386.a" "clipLibrary1.cel[0].cev[620].cevr";
connectAttr "animCurveTA2387.a" "clipLibrary1.cel[0].cev[621].cevr";
connectAttr "animCurveTA2388.a" "clipLibrary1.cel[0].cev[622].cevr";
connectAttr "animCurveTA2389.a" "clipLibrary1.cel[0].cev[623].cevr";
connectAttr "animCurveTU1261.a" "clipLibrary1.cel[0].cev[624].cevr";
connectAttr "animCurveTU1262.a" "clipLibrary1.cel[0].cev[625].cevr";
connectAttr "animCurveTU1263.a" "clipLibrary1.cel[0].cev[626].cevr";
connectAttr "animCurveTA2390.a" "clipLibrary1.cel[0].cev[627].cevr";
connectAttr "animCurveTA2391.a" "clipLibrary1.cel[0].cev[628].cevr";
connectAttr "animCurveTA2392.a" "clipLibrary1.cel[0].cev[629].cevr";
connectAttr "animCurveTA2393.a" "clipLibrary1.cel[0].cev[630].cevr";
connectAttr "animCurveTA2394.a" "clipLibrary1.cel[0].cev[631].cevr";
connectAttr "animCurveTA2395.a" "clipLibrary1.cel[0].cev[632].cevr";
connectAttr "animCurveTU1264.a" "clipLibrary1.cel[0].cev[633].cevr";
connectAttr "animCurveTU1265.a" "clipLibrary1.cel[0].cev[634].cevr";
connectAttr "animCurveTU1266.a" "clipLibrary1.cel[0].cev[635].cevr";
connectAttr "animCurveTA2396.a" "clipLibrary1.cel[0].cev[636].cevr";
connectAttr "animCurveTA2397.a" "clipLibrary1.cel[0].cev[637].cevr";
connectAttr "animCurveTA2398.a" "clipLibrary1.cel[0].cev[638].cevr";
connectAttr "animCurveTU1267.a" "clipLibrary1.cel[0].cev[639].cevr";
connectAttr "animCurveTU1268.a" "clipLibrary1.cel[0].cev[640].cevr";
connectAttr "animCurveTU1269.a" "clipLibrary1.cel[0].cev[641].cevr";
connectAttr "animCurveTA2399.a" "clipLibrary1.cel[0].cev[642].cevr";
connectAttr "animCurveTA2400.a" "clipLibrary1.cel[0].cev[643].cevr";
connectAttr "animCurveTA2401.a" "clipLibrary1.cel[0].cev[644].cevr";
connectAttr "animCurveTL808.a" "clipLibrary1.cel[0].cev[645].cevr";
connectAttr "animCurveTL809.a" "clipLibrary1.cel[0].cev[646].cevr";
connectAttr "animCurveTL810.a" "clipLibrary1.cel[0].cev[647].cevr";
connectAttr "animCurveTU1270.a" "clipLibrary1.cel[0].cev[648].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of stun.ma
