//Maya ASCII 2008 scene
//Name: attack1.ma
//Last modified: Mon, Dec 28, 2009 04:58:00 PM
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
createNode animClip -n "attackSource4";
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
	setAttr ".se" 45;
	setAttr ".ci" no;
createNode animCurveTA -n "animCurveTA2752";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 6 0 9 14.143824556133062 17 0.28634316445553581 
		24 0 30 0 38 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2753";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 6 0 9 -5.0294030722632446 17 7.6554766452839882 
		24 0 30 0 38 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2754";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 6 0 9 -2.6098163802204439 17 -6.7053304855171971 
		24 0 30 0 38 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2755";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 6 0 9 14.143824556133062 17 0.28634316445553581 
		24 0 30 0 38 0 45 0;
	setAttr -s 8 ".kit[0:7]"  9 10 10 10 10 10 10 9;
	setAttr -s 8 ".kot[0:7]"  9 10 10 10 10 10 10 9;
createNode animCurveTA -n "animCurveTA2756";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -5.2047506862742576 6 0 9 -5.0294030722632446 
		17 7.6554766452839882 24 0 30 0 38 -5.2047506862742576 45 -5.2047506862742576;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2757";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 6 0 9 -2.6098163802204439 17 -6.7053304855171971 
		24 0 30 0 38 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2758";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2759";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2760";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2761";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2762";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2763";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2764";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2765";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2766";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2767";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2768";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2769";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2770";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2771";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2772";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2773";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2774";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2775";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2776";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2777";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2778";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2779";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2780";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2781";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2782";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2783";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2784";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2785";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2786";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2787";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2788";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 9 -2.5703618278138771 12 2.5043233130146514 
		17 -1.8893847472373044 22 0.4505589466290279 30 0 38 0 45 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTA -n "animCurveTA2789";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 9 -15.25480915858053 12 7.0634832949663915 
		17 -9.9178710605423426 22 -0.9940031785685759 30 0 38 0 45 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTA -n "animCurveTA2790";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 9 -5.2491970402413015 12 4.3622151462254726 
		17 -3.6318550819702868 22 -1.5601619803545015 30 0 38 0 45 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTL -n "animCurveTL928";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL929";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL930";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2791";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 9 -2.5703618278138771 12 2.5043233130146514 
		17 -1.8893847472373044 22 0.4505589466290279 30 0 38 0 45 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTA -n "animCurveTA2792";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 9 -15.25480915858053 12 7.0634832949663915 
		17 -9.9178710605423426 22 -0.9940031785685759 30 0 38 0 45 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTA -n "animCurveTA2793";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 6 0 9 -5.2491970402413015 12 4.3622151462254726 
		17 -3.6318550819702868 22 -1.5601619803545015 30 0 38 0 45 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTL -n "animCurveTL931";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL932";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL933";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2794";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -14.368948490926961 6 0 9 0 17 0 30 0 
		38 -14.368948490926961 45 -14.368948490926961;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2795";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2796";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL934";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL935";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL936";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2797";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 7.9832676905363096 6 0 9 0 17 0 30 0 
		38 7.9832676905363096 45 7.9832676905363096;
	setAttr -s 7 ".kit[0:6]"  9 10 10 10 10 10 9;
	setAttr -s 7 ".kot[0:6]"  9 10 10 10 10 10 9;
createNode animCurveTA -n "animCurveTA2798";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2799";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL937";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL938";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL939";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2800";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2801";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2802";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL940";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL941";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL942";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2803";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2804";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2805";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL943";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL944";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL945";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2806";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2807";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2808";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL946";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL947";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL948";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2809";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2810";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2811";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL949";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL950";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL951";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2812";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2813";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2814";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL952";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL953";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL954";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2815";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2816";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2817";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL955";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL956";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL957";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1453";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2818";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 35.626819308748615 9 57.63842772218333 
		17 57.63842772218333 30 36.661586180116615 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2819";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 -5.0516578287140792 9 6.7643297413697949 
		17 6.7643297413697949 30 -5.4250534117537628 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2820";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 16.136210922816513 9 -6.6356153087207534 
		17 -6.6356153087207534 30 6.472729023200495 38 2.6640925025152633 45 0;
	setAttr -s 7 ".kit[0:6]"  3 3 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 3 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL958";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.013109125800625065 6 -0.11800815006597931 
		9 -0.041836924173990833 17 -0.041836924173990833 30 -0.13534101539173848 38 -0.044295041036179761 
		45 -0.013109125800625065;
	setAttr -s 7 ".kit[0:6]"  3 9 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 9 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL959";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.075951676950020475 6 0.7431668458271069 
		9 0.059861361290805881 17 0.11419879496320427 30 0.68895195615866633 38 0.021068439483346815 
		45 0.075951676950020475;
	setAttr -s 7 ".kit[0:6]"  3 10 3 9 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 3 9 10 10 3;
createNode animCurveTL -n "animCurveTL960";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.10545061589477858 6 -0.0072355880660480709 
		9 0.011970088969635861 17 0.016532930759725006 30 -0.045236591984389896 34 -0.11417985195074122 
		38 0.099843522334449847 45 0.10545061589477858;
	setAttr -s 8 ".kit[0:7]"  3 10 10 9 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 9 10 10 10 3;
createNode animCurveTA -n "animCurveTA2821";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2822";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2823";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL961";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL962";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL963";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1454";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1455";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1456";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.30000000000000077 6 5 9 -1.2000000000000008 
		17 -0.30000000000000077 30 0.99999999999999933 38 -0.30000000000000077 45 -0.30000000000000077;
	setAttr -s 7 ".kit[0:6]"  3 10 3 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 3 10 10 10 3;
createNode animCurveTU -n "animCurveTU1457";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.30000000000000077 6 5 9 -1.2000000000000008 
		17 -0.30000000000000077 30 0.99999999999999933 38 0.34999989103526363 45 -0.30000000000000077;
	setAttr -s 7 ".kit[0:6]"  3 10 3 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 3 10 10 10 3;
createNode animCurveTU -n "animCurveTU1458";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.30000000000000077 6 5 9 -1.2000000000000008 
		17 -0.30000000000000077 30 0.99999999999999933 38 0.34999989103526363 45 -0.30000000000000077;
	setAttr -s 7 ".kit[0:6]"  3 10 3 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 3 10 10 10 3;
createNode animCurveTU -n "animCurveTU1459";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.30000000000000077 6 5 9 -1.2000000000000008 
		17 -0.30000000000000077 30 0.99999999999999933 38 -0.30000000000000077 45 -0.30000000000000077;
	setAttr -s 7 ".kit[0:6]"  3 10 3 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 3 10 10 10 3;
createNode animCurveTU -n "animCurveTU1460";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.30000000000000077 6 5 9 -1.2000000000000008 
		17 -0.30000000000000077 30 0.99999999999999933 38 0.34999989103526363 45 -0.30000000000000077;
	setAttr -s 7 ".kit[0:6]"  3 10 3 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 3 10 10 10 3;
createNode animCurveTA -n "animCurveTA2824";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2825";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2826";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2827";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2828";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2829";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2830";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2831";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 11.70690242775609 17 9.1202408675322673 
		30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2832";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 -23.810224299061208 17 -21.012374209156039 
		30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2833";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 -41.021088618637364 17 -31.215945197559613 
		30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2834";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2835";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2836";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2837";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2838";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2839";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1461";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 3;
	setAttr -s 7 ".kot[0:6]"  3 5 5 5 5 5 3;
createNode animCurveTU -n "animCurveTU1462";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 3;
	setAttr -s 7 ".kot[0:6]"  3 5 5 5 5 5 3;
createNode animCurveTU -n "animCurveTU1463";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10 6 10 9 10 17 10 30 10 38 10 45 10;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL964";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL965";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL966";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1464";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10 6 10 9 10 17 10 30 10 38 10 45 10;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL967";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.22464769340943472 6 0.21937247600091681 
		9 0.21937247600091681 17 0.21937247600091681 30 0.21937247600091681 38 0.22464769340943472 
		45 0.22464769340943472;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL968";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.19416530018464082 6 1.0210385364436703 
		9 1.0210385364436703 17 1.0210385364436703 30 1.0210385364436703 38 0.19416530018464082 
		45 0.19416530018464082;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL969";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.47504801816095116 6 -0.13551709681770197 
		9 -0.13551709681770197 17 -0.13551709681770197 30 -0.13551709681770197 38 -0.47504801816095116 
		45 -0.47504801816095116;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2840";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2841";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2842";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL970";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 5.5511151231257827e-017 20 5.5511151231257827e-017 
		40 5.5511151231257827e-017;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL971";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 6.9388939039072284e-018 20 6.9388939039072284e-018 
		40 6.9388939039072284e-018;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL972";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 2.7755575615628914e-017 20 2.7755575615628914e-017 
		40 2.7755575615628914e-017;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1465";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 4 1 6 1 9 1 17 1 30 1 32 1 38 1 45 
		1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTU -n "animCurveTU1466";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 4 1 6 1 9 1 17 1 30 1 32 1 38 1 45 
		1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTU -n "animCurveTU1467";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 4 0 6 0 9 0 17 0 30 0 32 0 38 0 45 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTU -n "animCurveTU1468";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 4 0 6 0 9 0 17 0 30 0 32 0 38 0 45 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTU -n "animCurveTU1469";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 25 4 25 6 25 9 25 17 25 30 25 32 25 38 
		25 45 25;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTU -n "animCurveTU1470";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 4 0 6 0 9 0 17 0 30 0 32 0 38 0 45 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTU -n "animCurveTU1471";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 4 0 6 0 9 0 17 0 30 0 32 0 38 0 45 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTU -n "animCurveTU1472";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 4 0 6 0 9 0 17 0 30 0 32 0 38 0 45 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTA -n "animCurveTA2843";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 20.128361339199554 2 45.798056712491238 
		4 57.403961689777049 6 57.403961689777049 9 57.403961689777049 17 57.403961689777049 
		30 57.403961689777049 32 57.403961689777049 34 27.436576598063994 38 20.128361339199554 
		45 20.128361339199554;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 10 10 10 10 
		10 10 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 10 10 10 10 
		10 10 3;
createNode animCurveTA -n "animCurveTA2844";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 -0.37358874926200808 4 0 6 0 9 0 
		17 0 30 0 32 0 34 -6.2475419180195928 38 0 45 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 10 10 10 10 
		10 10 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 10 10 10 10 
		10 10 3;
createNode animCurveTA -n "animCurveTA2845";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 8.3073100262856912 4 0 6 0 9 0 17 
		0 30 0 32 0 34 25.918494890837653 38 0 45 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 10 10 10 10 
		10 10 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 10 10 10 10 
		10 10 3;
createNode animCurveTL -n "animCurveTL973";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 0.057206836627048174 4 0 6 0 9 0 
		17 0 30 0 32 0 34 0.14067150453013366 38 0 45 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 10 10 10 10 
		10 10 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 10 10 10 10 
		10 10 3;
createNode animCurveTL -n "animCurveTL974";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.19707483477738794 4 0.95112182706391835 
		6 0.95112182706391835 9 0.95112182706391835 17 0.95112182706391835 30 0.95112182706391835 
		32 0.95112182706391835 38 0.19707483477738794 45 0.19707483477738794;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTL -n "animCurveTL975";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.18298804813669703 4 0 6 0 9 0 17 0 
		30 0 32 0 38 0.18298804813669703 45 0.18298804813669703;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTU -n "animCurveTU1473";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 3;
	setAttr -s 7 ".kot[0:6]"  3 5 5 5 5 5 3;
createNode animCurveTU -n "animCurveTU1474";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 3;
	setAttr -s 7 ".kot[0:6]"  3 5 5 5 5 5 3;
createNode animCurveTU -n "animCurveTU1475";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10 6 10 9 10 17 10 30 10 38 10 45 10;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL976";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL977";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL978";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1476";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL979";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 -0.45756509874691037 9 -0.48766792983287871 
		17 -0.48766792983287871 30 -0.44678457507928687 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL980";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 -0.58186877643144008 9 0.24150629563456261 
		17 0.24150629563456261 30 0.079752814804550543 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL981";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 6 0.12910201701682569 9 -0.5049127185095309 
		17 -0.5049127185095309 30 -0.35550391475048776 34 -0.30153600730546287 38 -0.004340709504466746 
		45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2846";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2847";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2848";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL982";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL983";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.7347234759768071e-018 20 1.7347234759768071e-018 
		40 1.7347234759768071e-018;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL984";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1477";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1478";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1479";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1480";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1481";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2849";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -73.688065524612256 6 -97.811094937507093 
		9 1.9806030520606384 17 -1.3830839467700884 30 -58.390266249557051 38 -73.688065524612256 
		45 -73.688065524612256;
	setAttr -s 7 ".kit[0:6]"  3 10 3 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 3 10 10 10 3;
createNode animCurveTA -n "animCurveTA2850";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10.899517849852639 6 2.5570657203053009 
		9 35.091862672623442 17 11.967579400137817 30 0.5476429292859224 38 10.899517849852639 
		45 10.899517849852639;
	setAttr -s 7 ".kit[0:6]"  3 10 1 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 1 10 10 10 3;
	setAttr -s 7 ".kix[2:6]"  0.89565801620483398 0.75769788026809692 
		0.99964559078216553 1 1;
	setAttr -s 7 ".kiy[2:6]"  -0.44474342465400696 -0.65260559320449829 
		-0.026620835065841675 0 0;
	setAttr -s 7 ".kox[2:6]"  0.89565801620483398 0.75769788026809692 
		0.99964559078216553 1 1;
	setAttr -s 7 ".koy[2:6]"  -0.44474342465400696 -0.65260559320449829 
		-0.026620835065841675 0 0;
createNode animCurveTA -n "animCurveTA2851";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 83.974725223152646 6 -24.044050809707123 
		9 34.601914182066579 17 23.792179822925924 30 6.1461417277298409 38 83.974725223152646 
		45 83.974725223152646;
	setAttr -s 7 ".kit[0:6]"  3 10 3 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 3 10 10 10 3;
createNode animCurveTL -n "animCurveTL985";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.3820708588750783 6 -0.40958226088371052 
		9 -0.22362760936037063 17 -0.21238770642337723 30 -0.38912092004069532 38 -0.42174231823144748 
		45 -0.3820708588750783;
	setAttr -s 7 ".kit[0:6]"  3 10 1 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 1 10 10 10 3;
	setAttr -s 7 ".kix[2:6]"  0.99582374095916748 1 1 1 1;
	setAttr -s 7 ".kiy[2:6]"  0.0912972092628479 0 0 0 0;
	setAttr -s 7 ".kox[2:6]"  0.99582374095916748 1 1 1 1;
	setAttr -s 7 ".koy[2:6]"  0.0912972092628479 0 0 0 0;
createNode animCurveTL -n "animCurveTL986";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.042044109170142896 6 -0.15515251658746249 
		9 0.63786097078616089 17 0.58775446172027546 30 0.46929917750388894 38 -0.029002879253830008 
		45 -0.042044109170142896;
	setAttr -s 7 ".kit[0:6]"  2 10 3 10 10 10 2;
	setAttr -s 7 ".kot[0:6]"  2 10 3 10 10 10 2;
createNode animCurveTL -n "animCurveTL987";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.54001242177491338 6 -0.84615183150905615 
		9 -0.38839648050678943 17 -0.42577390965087614 30 -0.67686961286288705 34 -0.75909929874135151 
		38 -0.53958852129585178 45 -0.54001242177491338;
	setAttr -s 8 ".kit[0:7]"  2 10 10 10 10 10 10 2;
	setAttr -s 8 ".kot[0:7]"  2 10 10 10 10 10 10 2;
createNode animCurveTU -n "animCurveTU1482";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1483";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1484";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.4000000000000004 6 -1.0999999999999996 
		7 1.5481481481481485 9 2.5000000000000004 10 -1.0586082569398934 17 -0.39999999999999969 
		30 2.9000000000000004 38 1.4000000000000004 45 1.4000000000000004;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTU -n "animCurveTU1485";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.4000000000000004 6 -1.0999999999999996 
		7 1.5481481481481485 9 2.5000000000000004 10 -1.0586082569398934 17 -0.39999999999999969 
		30 2.9000000000000004 38 2.2741377967483034 45 1.4000000000000004;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTU -n "animCurveTU1486";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.4000000000000004 6 -1.0999999999999996 
		7 1.5481481481481485 9 2.5000000000000004 10 -1.0586082569398934 17 -0.39999999999999969 
		30 2.9000000000000004 38 2.2741377967483034 45 1.4000000000000004;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTU -n "animCurveTU1487";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.4000000000000004 6 -1.0999999999999996 
		7 1.5481481481481485 9 2.5000000000000004 10 -1.0586082569398934 17 -0.39999999999999969 
		30 2.9000000000000004 38 1.4000000000000004 45 1.4000000000000004;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTU -n "animCurveTU1488";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.4000000000000004 6 -1.0999999999999996 
		7 1.5481481481481485 9 2.5000000000000004 10 -1.0586082569398934 17 -0.39999999999999969 
		30 2.9000000000000004 38 2.2741377967483034 45 1.4000000000000004;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTU -n "animCurveTU1489";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1490";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1491";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2852";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2853";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2854";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL988";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL989";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL990";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1492";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1493";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 10 20 10 40 10;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1494";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2855";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2856";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2857";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL991";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL992";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL993";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1495";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1496";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1497";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2858";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2859";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2860";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL994";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL995";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL996";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1498";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1499";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2861";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2862";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2863";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL997";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL998";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL999";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1500";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1501";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1502";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2864";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2865";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2866";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL1000";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL1001";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL1002";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1503";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1504";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2867";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2868";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2869";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL1003";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL1004";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL1005";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2870";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2871";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 9.9392333795734874e-017 20 9.9392333795734874e-017 
		40 9.9392333795734874e-017;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2872";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2873";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2874";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2875";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 9.9392333795734924e-017 20 9.9392333795734924e-017 
		40 9.9392333795734924e-017;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2876";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2877";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2878";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2879";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2880";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2881";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 9.9392333795734899e-017 20 9.9392333795734899e-017 
		40 9.9392333795734899e-017;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2882";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2883";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2884";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2885";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1505";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 3;
	setAttr -s 7 ".kot[0:6]"  3 5 5 5 5 5 3;
createNode animCurveTU -n "animCurveTU1506";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 3;
	setAttr -s 7 ".kot[0:6]"  3 5 5 5 5 5 3;
createNode animCurveTU -n "animCurveTU1507";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10 6 10 9 10 17 10 30 10 38 10 45 10;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL1006";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL1007";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL1008";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1508";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10 6 10 9 10 17 10 30 10 38 10 45 10;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL1009";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.067033432403714843 6 -0.28861863396503251 
		9 0.3850688040014798 17 0.3850688040014798 30 -0.24256388262986231 38 0.067033432403714843 
		45 0.067033432403714843;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL1010";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.16933803890603863 6 0.25941977735400873 
		9 0.45481690526861895 17 0.45481690526861895 30 0.26738528910848874 38 0.16933803890603863 
		45 0.16933803890603863;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL1011";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.57509011135883603 6 0.57093538357235851 
		9 1.0835434082803523 17 1.0835434082803523 30 0.71766287868446688 38 0.57509011135883603 
		45 0.57509011135883603;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2886";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2887";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2888";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL1012";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL1013";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL1014";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1509";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 38 1 45 1;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "animCurveTU1510";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 38 1 45 1;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "animCurveTU1511";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 38 0 45 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "animCurveTU1512";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 38 0 45 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "animCurveTU1513";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 25 38 25 45 25;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "animCurveTU1514";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 38 0 45 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "animCurveTU1515";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 38 0 45 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "animCurveTU1516";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 38 0 45 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "animCurveTA2889";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -16.972634475184972 38 -16.972634475184972 
		45 -16.972634475184972;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "animCurveTA2890";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 38 0 45 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "animCurveTA2891";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 38 0 45 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "animCurveTL1015";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 38 0 45 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "animCurveTL1016";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 38 0 45 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "animCurveTL1017";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.057044533275492443 38 -0.057044533275492443 
		45 -0.057044533275492443;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "animCurveTU1517";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 3;
	setAttr -s 7 ".kot[0:6]"  3 5 5 5 5 5 3;
createNode animCurveTU -n "animCurveTU1518";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 3;
	setAttr -s 7 ".kot[0:6]"  3 5 5 5 5 5 3;
createNode animCurveTU -n "animCurveTU1519";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10 6 10 9 10 17 10 30 10 38 10 45 10;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL1018";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL1019";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL1020";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1520";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL1021";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.2165701385911305 6 0.0051417542081573231 
		9 -0.53301631606704847 17 -0.53301631606704847 30 -0.42423604114710978 38 -0.2165701385911305 
		45 -0.2165701385911305;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL1022";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.053478567476916261 6 0.3511095502460253 
		7 -0.049585996492165274 9 -1.2539188879611385 17 -1.2539188879611385 30 0.33369864105428748 
		38 -0.053478567476916261 45 -0.053478567476916261;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL1023";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.5222747364155893 6 0.75301112567009332 
		7 0.42990661338037617 9 0.20915134494974641 17 0.20915134494974641 30 0.070941352695737536 
		34 0.16369118707881924 38 0.51793402691112256 45 0.5222747364155893;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		3;
createNode animCurveTA -n "animCurveTA2892";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2893";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2894";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL1024";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -4.4408920985006262e-016 20 -4.4408920985006262e-016 
		40 -4.4408920985006262e-016;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL1025";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.7347234759768071e-018 20 1.7347234759768071e-018 
		40 1.7347234759768071e-018;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL1026";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1521";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1522";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1523";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1524";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1525";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2895";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 72.410849029571423 6 -51.171490475492078 
		7 -5.1868813737796673 9 73.630896960842534 17 73.630896960842534 30 80.597648204593028 
		38 72.410849029571423 45 72.410849029571423;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2896";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -29.916944388919955 6 -8.4703564009970709 
		7 -17.417424571201344 9 17.198130134552461 17 17.198130134552461 30 22.045928453262395 
		38 -29.916944388919955 45 -29.916944388919955;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2897";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 72.717171353838793 6 24.960744874382364 
		7 -34.901554608044833 9 -47.236662398556341 17 -47.236662398556341 30 -32.203556985760208 
		38 72.717171353838793 45 72.717171353838793;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL1027";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.38771781685288609 6 -0.16814581049862998 
		7 -0.02732198400656774 9 0.41474814034533347 17 0.55118160896189083 30 -0.060115138290801173 
		38 -0.42738927620925526 45 -0.38771781685288609;
	setAttr -s 8 ".kit[0:7]"  3 1 10 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 1 10 10 10 10 10 3;
	setAttr -s 8 ".kix[1:7]"  0.470529705286026 0.16908755898475647 0.4992518424987793 
		0.82755082845687866 0.58179986476898193 1 1;
	setAttr -s 8 ".kiy[1:7]"  0.88238412141799927 0.98560100793838501 
		0.86645698547363281 -0.56139075756072998 -0.81333202123641968 0 0;
	setAttr -s 8 ".kox[1:7]"  0.47052976489067078 0.16908755898475647 
		0.4992518424987793 0.82755082845687866 0.58179986476898193 1 1;
	setAttr -s 8 ".koy[1:7]"  0.88238418102264404 0.98560100793838501 
		0.86645698547363281 -0.56139075756072998 -0.81333202123641968 0 0;
createNode animCurveTL -n "animCurveTL1028";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.01108452333757072 6 1.0443797056367712 
		7 -0.013273708763756054 9 -1.1000572629605214 17 -1.0007286299011557 30 -0.019736816806115387 
		38 0.024125753253883608 45 0.01108452333757072;
	setAttr -s 8 ".kit[0:7]"  9 10 10 3 10 10 10 9;
	setAttr -s 8 ".kot[0:7]"  9 10 10 3 10 10 10 9;
createNode animCurveTL -n "animCurveTL1029";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.736599410145234 6 0.62188327285368372 
		7 0.74932088356509896 9 1.0645365993435614 17 1.0618640782326634 30 0.64470079694221172 
		34 0.52994295086733989 38 0.7370233106242956 45 0.736599410145234;
	setAttr -s 9 ".kit[0:8]"  9 10 10 10 10 10 10 10 
		9;
	setAttr -s 9 ".kot[0:8]"  9 10 10 10 10 10 10 10 
		9;
createNode animCurveTA -n "animCurveTA2898";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 -0.473644371911071 9 -0.25293060469486961 
		17 -0.13001727381768402 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2899";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 10.627661594022713 9 -3.496576501478899 
		17 1.854809026184324 30 4.6015209723315884 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2900";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 4.1686090493374506 9 -1.3998676653320565 
		17 4.0439824791843577 30 -4.1348916358345527 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2901";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 7.0568556994971777e-015 20 7.0568556994971777e-015 
		40 7.0568556994971777e-015;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2902";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -1.9586709197597583e-031 20 -1.9586709197597583e-031 
		40 -1.9586709197597583e-031;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2903";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -3.1805546814635168e-015 20 -3.1805546814635168e-015 
		40 -3.1805546814635168e-015;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1526";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1527";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999967 20 0.99999999999999967 
		40 0.99999999999999967;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1528";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999967 20 0.99999999999999967 
		40 0.99999999999999967;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2904";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2905";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2906";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2907";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -9.1440947092076214e-015 20 -9.1440947092076214e-015 
		40 -9.1440947092076214e-015;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2908";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -1.2722218725854075e-014 20 -1.2722218725854075e-014 
		40 -1.2722218725854075e-014;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2909";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 7.5538173684758548e-014 20 7.5538173684758548e-014 
		40 7.5538173684758548e-014;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1529";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1530";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1531";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2910";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2911";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2912";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2913";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2914";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2915";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1532";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1533";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1534";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2916";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2917";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2918";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2919";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -4.3255543667903831e-013 20 -4.3255543667903831e-013 
		40 -4.3255543667903831e-013;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2920";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.2722218725854056e-014 20 1.2722218725854056e-014 
		40 1.2722218725854056e-014;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2921";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 3.1805546814635649e-015 20 3.1805546814635649e-015 
		40 3.1805546814635649e-015;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1535";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1536";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1537";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.0000000000000002 20 1.0000000000000002 
		40 1.0000000000000002;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2922";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2923";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2924";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1538";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.0000000000000002 20 1.0000000000000002 
		40 1.0000000000000002;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1539";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1540";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2925";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -9.5416640443905503e-015 20 -9.5416640443905503e-015 
		40 -9.5416640443905503e-015;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2926";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -1.1131941385122309e-014 20 -1.1131941385122309e-014 
		40 -1.1131941385122309e-014;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2927";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 6.3611093629270327e-015 20 6.3611093629270327e-015 
		40 6.3611093629270327e-015;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL1030";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL1031";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 4.4408920985006262e-016 20 4.4408920985006262e-016 
		40 4.4408920985006262e-016;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL1032";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -1.1102230246251565e-016 20 -1.1102230246251565e-016 
		40 -1.1102230246251565e-016;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1541";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.0000000000000002 6 1.0000000000000002 
		9 1.0000000000000002 17 1.0000000000000002 30 1.0000000000000002 38 1.0000000000000002 
		45 1.0000000000000002;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1542";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1543";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2928";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2929";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2930";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL1033";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.3877787807814457e-017 6 0 9 0 17 0 
		30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL1034";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL1035";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -1.1102230246251565e-016 6 0 9 0 17 0 
		30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2931";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 6.3611093629270335e-015 20 6.3611093629270335e-015 
		40 6.3611093629270335e-015;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2932";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.2722218725854064e-014 20 1.2722218725854064e-014 
		40 1.2722218725854064e-014;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2933";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -1.2722218725854064e-014 20 -1.2722218725854064e-014 
		40 -1.2722218725854064e-014;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1544";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1545";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1546";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2934";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2935";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2936";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2937";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -9.5416640443905519e-015 20 -9.5416640443905519e-015 
		40 -9.5416640443905519e-015;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2938";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -6.3611093629270312e-015 20 -6.3611093629270312e-015 
		40 -6.3611093629270312e-015;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2939";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -2.5444437451708134e-014 20 -2.5444437451708134e-014 
		40 -2.5444437451708134e-014;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1547";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999967 20 0.99999999999999967 
		40 0.99999999999999967;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1548";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999956 20 0.99999999999999956 
		40 0.99999999999999956;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1549";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999956 20 0.99999999999999956 
		40 0.99999999999999956;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2940";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2941";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2942";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2943";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 3.1805546814635152e-015 20 3.1805546814635152e-015 
		40 3.1805546814635152e-015;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2944";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -9.5416640443905487e-015 20 -9.5416640443905487e-015 
		40 -9.5416640443905487e-015;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2945";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -1.2722218725854064e-014 20 -1.2722218725854064e-014 
		40 -1.2722218725854064e-014;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1550";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1551";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1552";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2946";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2947";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2948";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2949";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 3.4986101496098681e-014 20 3.4986101496098681e-014 
		40 3.4986101496098681e-014;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2950";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -6.3611093629270335e-015 20 -6.3611093629270335e-015 
		40 -6.3611093629270335e-015;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2951";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.9421187711420696e-030 20 1.9421187711420696e-030 
		40 1.9421187711420696e-030;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1553";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1554";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999989 6 0.99999999999999989 
		9 0.99999999999999989 17 0.99999999999999989 30 0.99999999999999989 38 0.99999999999999989 
		45 0.99999999999999989;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1555";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.0000000000000002 6 1.0000000000000002 
		9 1.0000000000000002 17 1.0000000000000002 30 1.0000000000000002 38 1.0000000000000002 
		45 1.0000000000000002;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2952";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -6.5315753133350283 6 -6.5315753133350283 
		9 -6.5315753133350283 17 -6.5315753133350283 30 -6.5315753133350283 38 -6.5315753133350283 
		45 -6.5315753133350283;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2953";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.50791434021845472 6 -0.50791434021845472 
		9 -0.50791434021845472 17 -0.50791434021845472 30 -0.50791434021845472 38 -0.50791434021845472 
		45 -0.50791434021845472;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2954";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 15.371706900000456 6 15.371706900000456 
		9 15.371706900000456 17 15.371706900000456 30 15.371706900000456 38 15.371706900000456 
		45 15.371706900000456;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2955";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -3.1805546814635183e-015 20 -3.1805546814635183e-015 
		40 -3.1805546814635183e-015;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2956";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -1.2722218725854067e-014 20 -1.2722218725854067e-014 
		40 -1.2722218725854067e-014;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2957";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -1.2722218725854067e-014 20 -1.2722218725854067e-014 
		40 -1.2722218725854067e-014;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1556";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 6 0.99999999999999978 
		9 0.99999999999999978 17 0.99999999999999978 30 0.99999999999999978 38 0.99999999999999978 
		45 0.99999999999999978;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1557";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 6 0.99999999999999978 
		9 0.99999999999999978 17 0.99999999999999978 30 0.99999999999999978 38 0.99999999999999978 
		45 0.99999999999999978;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1558";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999956 6 0.99999999999999956 
		9 0.99999999999999956 17 0.99999999999999956 30 0.99999999999999956 38 0.99999999999999956 
		45 0.99999999999999956;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2958";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2959";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2960";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2961";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -6.3611093629270335e-015 20 -6.3611093629270335e-015 
		40 -6.3611093629270335e-015;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2962";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 6.3611093629270335e-015 20 6.3611093629270335e-015 
		40 6.3611093629270335e-015;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2963";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 3.5311250384401278e-031 20 3.5311250384401278e-031 
		40 3.5311250384401278e-031;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1559";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 6 0.99999999999999978 
		9 0.99999999999999978 17 0.99999999999999978 30 0.99999999999999978 38 0.99999999999999978 
		45 0.99999999999999978;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1560";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1561";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2964";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2965";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2966";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2967";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 3.1805546814635176e-015 20 3.1805546814635176e-015 
		40 3.1805546814635176e-015;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2968";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -4.7708320221952759e-015 20 -4.7708320221952759e-015 
		40 -4.7708320221952759e-015;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2969";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 9.5416640443905519e-015 20 9.5416640443905519e-015 
		40 9.5416640443905519e-015;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1562";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999967 6 0.99999999999999967 
		9 0.99999999999999967 17 0.99999999999999967 30 0.99999999999999967 38 0.99999999999999967 
		45 0.99999999999999967;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1563";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1564";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2970";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -10.006950332467882 6 -10.006950332467882 
		9 -10.006950332467882 17 -10.006950332467882 30 -10.006950332467882 38 -10.006950332467882 
		45 -10.006950332467882;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2971";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -12.409127898568453 6 -12.409127898568453 
		9 -12.409127898568453 17 -12.409127898568453 30 -12.409127898568453 38 -12.409127898568453 
		45 -12.409127898568453;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2972";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 8.6298909566225337 6 8.6298909566225337 
		9 8.6298909566225337 17 8.6298909566225337 30 8.6298909566225337 38 8.6298909566225337 
		45 8.6298909566225337;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2973";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -2.8624992133171654e-014 20 -2.8624992133171654e-014 
		40 -2.8624992133171654e-014;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2974";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 8.7465253740246656e-015 20 8.7465253740246656e-015 
		40 8.7465253740246656e-015;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2975";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 9.5416640443905519e-015 20 9.5416640443905519e-015 
		40 9.5416640443905519e-015;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1565";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999989 6 0.99999999999999989 
		9 0.99999999999999989 17 0.99999999999999989 30 0.99999999999999989 38 0.99999999999999989 
		45 0.99999999999999989;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1566";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1567";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2976";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 20.33693740949867 6 11.182989207208745 
		9 11.182989207208745 17 11.182989207208745 30 11.182989207208745 38 20.33693740949867 
		45 20.33693740949867;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2977";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -14.826892265970072 6 -3.9841891407637053 
		9 -3.9841891407637053 17 -3.9841891407637053 30 -3.9841891407637053 38 -14.826892265970072 
		45 -14.826892265970072;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2978";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 48.641881730594498 6 24.575190458574639 
		9 24.575190458574639 17 24.575190458574639 30 24.575190458574639 38 48.641881730594498 
		45 48.641881730594498;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2979";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -3.144908237360738e-030 20 -3.144908237360738e-030 
		40 -3.144908237360738e-030;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2980";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 3.7769086842379261e-014 20 3.7769086842379261e-014 
		40 3.7769086842379261e-014;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2981";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 9.5416640443905503e-015 20 9.5416640443905503e-015 
		40 9.5416640443905503e-015;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1568";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 6 0.99999999999999978 
		9 0.99999999999999978 17 0.99999999999999978 30 0.99999999999999978 38 0.99999999999999978 
		45 0.99999999999999978;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1569";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999933 6 0.99999999999999933 
		9 0.99999999999999933 17 0.99999999999999933 30 0.99999999999999933 38 0.99999999999999933 
		45 0.99999999999999933;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1570";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999967 6 0.99999999999999967 
		9 0.99999999999999967 17 0.99999999999999967 30 0.99999999999999967 38 0.99999999999999967 
		45 0.99999999999999967;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2982";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2983";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2984";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA2985";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2986";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2987";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1571";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.0000000000000002 20 1.0000000000000002 
		40 1.0000000000000002;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1572";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.0000000000000004 20 1.0000000000000004 
		40 1.0000000000000004;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1573";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.0000000000000004 20 1.0000000000000004 
		40 1.0000000000000004;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2988";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2989";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2990";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2991";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2992";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2993";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1574";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1575";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1576";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2994";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2995";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2996";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2997";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2998";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2999";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1577";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1578";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1579";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3000";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3001";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3002";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3003";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3004";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3005";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1580";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1581";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.0000000000000002 20 1.0000000000000002 
		40 1.0000000000000002;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1582";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3006";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3007";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3008";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3009";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3010";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3011";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 4.8525382364188918e-030 20 4.8525382364188918e-030 
		40 4.8525382364188918e-030;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1583";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999967 6 0.99999999999999967 
		9 0.99999999999999967 17 0.99999999999999967 30 0.99999999999999967 38 0.99999999999999967 
		45 0.99999999999999967;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1584";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999944 6 0.99999999999999944 
		9 0.99999999999999944 17 0.99999999999999944 30 0.99999999999999944 38 0.99999999999999944 
		45 0.99999999999999944;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1585";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999989 6 0.99999999999999989 
		9 0.99999999999999989 17 0.99999999999999989 30 0.99999999999999989 38 0.99999999999999989 
		45 0.99999999999999989;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3012";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 15.336554014823967 9 3.1863924515205588 
		17 3.1863924515205588 30 6.4660211909248506 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3013";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 6.1756774298301602 9 -1.799496382260376 
		17 -1.799496382260376 30 -2.5199631408262593 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3014";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 -16.331882816833172 9 -8.5515103523030511 
		17 -8.5515103523030511 30 -2.6261747945946596 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3015";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3016";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3017";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 2.4717875269080888e-030 20 2.4717875269080888e-030 
		40 2.4717875269080888e-030;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1586";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1587";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999989 6 0.99999999999999989 
		9 0.99999999999999989 17 0.99999999999999989 30 0.99999999999999989 38 0.99999999999999989 
		45 0.99999999999999989;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1588";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999989 6 0.99999999999999989 
		9 0.99999999999999989 17 0.99999999999999989 30 0.99999999999999989 38 0.99999999999999989 
		45 0.99999999999999989;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3018";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 8.3586893044596557 9 5.8805129301414985 
		17 6.6562881439184309 30 8.3586893044596557 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3019";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 4.7145269015319657 9 3.9432101921922103 
		17 4.7205857846338963 30 4.7145269015319657 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3020";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 -24.183620061641889 9 -12.474856448846371 
		17 -12.373412787994143 30 -12.110131058152525 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3021";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3022";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3023";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -3.1362690564052959e-046 20 -3.1362690564052959e-046 
		40 -3.1362690564052959e-046;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1589";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1590";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1591";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3024";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 -7.5477766332639371 9 -17.353363750920717 
		17 -15.901082478161701 30 -7.5966412105785572 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3025";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 -3.5182943479978217 9 -2.3109405785988799 
		17 -1.1187149441501134 30 -7.2306738333082121 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3026";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -3.1362690564052959e-046 6 -10.678173360427362 
		9 8.9383464687815373 17 8.7588760853303214 30 -1.6816150357016186 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3027";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3028";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3029";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1592";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999967 6 0.99999999999999967 
		9 0.99999999999999967 17 0.99999999999999967 30 0.99999999999999967 38 0.99999999999999967 
		45 0.99999999999999967;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1593";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999944 6 0.99999999999999944 
		9 0.99999999999999944 17 0.99999999999999944 30 0.99999999999999944 38 0.99999999999999944 
		45 0.99999999999999944;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1594";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999989 6 0.99999999999999989 
		9 0.99999999999999989 17 0.99999999999999989 30 0.99999999999999989 38 0.99999999999999989 
		45 0.99999999999999989;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3030";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 -22.466309657948408 9 6.5763033047867649 
		17 6.5763033047867649 30 -4.8303123026532289 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3031";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 3.1328885617257285 9 6.387289463625371 
		17 6.387289463625371 30 3.587150078010779 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3032";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 11.770139324761239 9 -16.294333874085986 
		17 -16.294333874085986 30 -0.10569514667833578 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3033";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3034";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3035";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1595";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 27 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1596";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 27 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1597";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 27 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3036";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 1.02496643495093 9 9.7947468016988815 
		17 6.9383099044307519 27 3.716765066918998 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3037";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 -1.7131425659006878 9 1.950910299431549 
		17 1.5472298346684081 27 0.8288314991981045 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3038";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 3.7004519955232755 9 -27.644892886099747 
		17 -27.789318985139783 27 -27.869366514960134 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1598";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.0000000000000002 20 1.0000000000000002 
		40 1.0000000000000002;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1599";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.0000000000000004 20 1.0000000000000004 
		40 1.0000000000000004;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1600";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.0000000000000002 20 1.0000000000000002 
		40 1.0000000000000002;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3039";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3040";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3041";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL1036";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -1.3877787807814457e-017 20 -1.3877787807814457e-017 
		40 -1.3877787807814457e-017;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL1037";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL1038";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -1.1102230246251565e-016 20 -1.1102230246251565e-016 
		40 -1.1102230246251565e-016;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1601";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 6 0.99999999999999978 
		9 0.99999999999999978 17 0.99999999999999978 30 0.99999999999999978 38 0.99999999999999978 
		45 0.99999999999999978;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1602";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 6 0.99999999999999978 
		9 0.99999999999999978 17 0.99999999999999978 30 0.99999999999999978 38 0.99999999999999978 
		45 0.99999999999999978;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1603";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999989 6 0.99999999999999989 
		9 0.99999999999999989 17 0.99999999999999989 30 0.99999999999999989 38 0.99999999999999989 
		45 0.99999999999999989;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3042";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 7.0647556991172644 9 16.599128853490235 
		17 16.599128853490235 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3043";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 -19.52402646401767 9 2.4078429281288383 
		17 2.4078429281288383 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3044";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 7.6522092479974875 9 -4.7615874576563959 
		17 -4.7615874576563959 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL1039";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL1040";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 4.4408920985006262e-016 6 0 9 0 17 0 
		30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL1041";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3045";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3046";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3047";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1604";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1605";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1606";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3048";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3049";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3050";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3051";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3052";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3053";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1607";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999989 20 0.99999999999999989 
		40 0.99999999999999989;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1608";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999978 20 0.99999999999999978 
		40 0.99999999999999978;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1609";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999956 20 0.99999999999999956 
		40 0.99999999999999956;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3054";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3055";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3056";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3057";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3058";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3059";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1610";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.0000000000000002 20 1.0000000000000002 
		40 1.0000000000000002;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1611";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1612";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.0000000000000002 20 1.0000000000000002 
		40 1.0000000000000002;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3060";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3061";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3062";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3063";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3064";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3065";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1613";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 6 0.99999999999999978 
		9 0.99999999999999978 17 0.99999999999999978 30 0.99999999999999978 38 0.99999999999999978 
		45 0.99999999999999978;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1614";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1615";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.0000000000000002 6 1.0000000000000002 
		9 1.0000000000000002 17 1.0000000000000002 30 1.0000000000000002 38 1.0000000000000002 
		45 1.0000000000000002;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3066";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 6.5887416381602044 6 0 9 0 17 0 30 0 
		38 6.5887416381602044 45 6.5887416381602044;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3067";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3068";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3069";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3070";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3071";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1616";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999944 6 0.99999999999999944 
		9 0.99999999999999944 17 0.99999999999999944 30 0.99999999999999944 38 0.99999999999999944 
		45 0.99999999999999944;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1617";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999956 6 0.99999999999999956 
		9 0.99999999999999956 17 0.99999999999999956 30 0.99999999999999956 38 0.99999999999999956 
		45 0.99999999999999956;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1618";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999933 6 0.99999999999999933 
		9 0.99999999999999933 17 0.99999999999999933 30 0.99999999999999933 38 0.99999999999999933 
		45 0.99999999999999933;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3072";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10.802160318599565 6 0 9 0 17 0 30 0 
		38 10.802160318599565 45 10.802160318599565;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3073";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.18093193430354684 6 0 9 0 17 0 30 0 
		38 0.18093193430354684 45 0.18093193430354684;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3074";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -5.5598653650577603 6 0 9 0 17 0 30 0 
		38 -5.5598653650577603 45 -5.5598653650577603;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3075";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3076";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3077";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1619";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999967 6 0.99999999999999967 
		9 0.99999999999999967 17 0.99999999999999967 30 0.99999999999999967 38 0.99999999999999967 
		45 0.99999999999999967;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1620";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 6 0.99999999999999978 
		9 0.99999999999999978 17 0.99999999999999978 30 0.99999999999999978 38 0.99999999999999978 
		45 0.99999999999999978;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1621";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 6 0.99999999999999978 
		9 0.99999999999999978 17 0.99999999999999978 30 0.99999999999999978 38 0.99999999999999978 
		45 0.99999999999999978;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3078";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3079";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3080";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3081";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3082";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3083";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1622";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999989 6 0.99999999999999989 
		9 0.99999999999999989 17 0.99999999999999989 30 0.99999999999999989 38 0.99999999999999989 
		45 0.99999999999999989;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1623";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 6 0.99999999999999978 
		9 0.99999999999999978 17 0.99999999999999978 30 0.99999999999999978 38 0.99999999999999978 
		45 0.99999999999999978;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1624";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3084";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -5.2487233478977044 6 -5.2487233478977044 
		9 -5.2487233478977044 17 -5.2487233478977044 30 -5.2487233478977044 38 -5.2487233478977044 
		45 -5.2487233478977044;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3085";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -19.191038692298999 6 -19.191038692298999 
		9 -19.191038692298999 17 -19.191038692298999 30 -19.191038692298999 38 -19.191038692298999 
		45 -19.191038692298999;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3086";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 3.4639940811277468 6 3.4639940811277468 
		9 3.4639940811277468 17 3.4639940811277468 30 3.4639940811277468 38 3.4639940811277468 
		45 3.4639940811277468;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3087";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3088";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3089";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1625";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999989 6 0.99999999999999989 
		9 0.99999999999999989 17 0.99999999999999989 30 0.99999999999999989 38 0.99999999999999989 
		45 0.99999999999999989;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1626";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999989 6 0.99999999999999989 
		9 0.99999999999999989 17 0.99999999999999989 30 0.99999999999999989 38 0.99999999999999989 
		45 0.99999999999999989;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1627";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 6 0.99999999999999978 
		9 0.99999999999999978 17 0.99999999999999978 30 0.99999999999999978 38 0.99999999999999978 
		45 0.99999999999999978;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3090";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 15.804493166945804 6 13.877004431497326 
		9 13.877004431497326 17 13.877004431497326 30 13.877004431497326 38 15.804493166945804 
		45 15.804493166945804;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3091";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 3.5290061766020497 6 -9.8256854129170819 
		9 -9.8256854129170819 17 -9.8256854129170819 30 -9.8256854129170819 38 3.5290061766020497 
		45 3.5290061766020497;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3092";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 55.012788276203878 6 47.740341091290361 
		9 47.740341091290361 17 47.740341091290361 30 47.740341091290361 38 55.012788276203878 
		45 55.012788276203878;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3093";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3094";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA3095";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[0:2]"  9 1 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  1 1;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTU -n "animCurveTU1628";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.0000000000000002 6 1.0000000000000002 
		9 1.0000000000000002 17 1.0000000000000002 30 1.0000000000000002 38 1.0000000000000002 
		45 1.0000000000000002;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1629";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.0000000000000002 6 1.0000000000000002 
		9 1.0000000000000002 17 1.0000000000000002 30 1.0000000000000002 38 1.0000000000000002 
		45 1.0000000000000002;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1630";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3096";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 14.236890325621934 6 -1.3224722037367471 
		9 -1.3224722037367471 17 -1.3224722037367471 30 -1.3224722037367471 38 14.236890325621934 
		45 14.236890325621934;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3097";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -1.4378573021860341 6 -1.6804077282048093 
		9 -1.6804077282048093 17 -1.6804077282048093 30 -1.6804077282048093 38 -1.4378573021860341 
		45 -1.4378573021860341;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3098";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 2.5194410123137181 6 1.6351083250161258 
		9 1.6351083250161258 17 1.6351083250161258 30 1.6351083250161258 38 2.5194410123137181 
		45 2.5194410123137181;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1631";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1632";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1633";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3099";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3100";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA3101";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL1042";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL1043";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL1044";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 6 0 9 0 17 0 30 0 38 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU1634";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 30 1 38 1 45 1;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 3;
	setAttr -s 7 ".kot[0:6]"  3 5 5 5 5 5 3;
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
connectAttr "attackSource4.cl" "clipLibrary1.sc[0]";
connectAttr "animCurveTA2752.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "animCurveTA2753.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "animCurveTA2754.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "animCurveTA2755.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "animCurveTA2756.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "animCurveTA2757.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "animCurveTA2758.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "animCurveTA2759.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "animCurveTA2760.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "animCurveTA2761.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "animCurveTA2762.a" "clipLibrary1.cel[0].cev[10].cevr";
connectAttr "animCurveTA2763.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "animCurveTA2764.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "animCurveTA2765.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "animCurveTA2766.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "animCurveTA2767.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "animCurveTA2768.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "animCurveTA2769.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "animCurveTA2770.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "animCurveTA2771.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "animCurveTA2772.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "animCurveTA2773.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "animCurveTA2774.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "animCurveTA2775.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "animCurveTA2776.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "animCurveTA2777.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "animCurveTA2778.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "animCurveTA2779.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "animCurveTA2780.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "animCurveTA2781.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "animCurveTA2782.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "animCurveTA2783.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "animCurveTA2784.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "animCurveTA2785.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "animCurveTA2786.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "animCurveTA2787.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "animCurveTA2788.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "animCurveTA2789.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "animCurveTA2790.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "animCurveTL928.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "animCurveTL929.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "animCurveTL930.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "animCurveTA2791.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "animCurveTA2792.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "animCurveTA2793.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "animCurveTL931.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "animCurveTL932.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "animCurveTL933.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "animCurveTA2794.a" "clipLibrary1.cel[0].cev[48].cevr";
connectAttr "animCurveTA2795.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "animCurveTA2796.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "animCurveTL934.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "animCurveTL935.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "animCurveTL936.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "animCurveTA2797.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "animCurveTA2798.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "animCurveTA2799.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "animCurveTL937.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "animCurveTL938.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "animCurveTL939.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "animCurveTA2800.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "animCurveTA2801.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "animCurveTA2802.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "animCurveTL940.a" "clipLibrary1.cel[0].cev[63].cevr";
connectAttr "animCurveTL941.a" "clipLibrary1.cel[0].cev[64].cevr";
connectAttr "animCurveTL942.a" "clipLibrary1.cel[0].cev[65].cevr";
connectAttr "animCurveTA2803.a" "clipLibrary1.cel[0].cev[66].cevr";
connectAttr "animCurveTA2804.a" "clipLibrary1.cel[0].cev[67].cevr";
connectAttr "animCurveTA2805.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "animCurveTL943.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "animCurveTL944.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "animCurveTL945.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "animCurveTA2806.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "animCurveTA2807.a" "clipLibrary1.cel[0].cev[73].cevr";
connectAttr "animCurveTA2808.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "animCurveTL946.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "animCurveTL947.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "animCurveTL948.a" "clipLibrary1.cel[0].cev[77].cevr";
connectAttr "animCurveTA2809.a" "clipLibrary1.cel[0].cev[78].cevr";
connectAttr "animCurveTA2810.a" "clipLibrary1.cel[0].cev[79].cevr";
connectAttr "animCurveTA2811.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "animCurveTL949.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "animCurveTL950.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "animCurveTL951.a" "clipLibrary1.cel[0].cev[83].cevr";
connectAttr "animCurveTA2812.a" "clipLibrary1.cel[0].cev[84].cevr";
connectAttr "animCurveTA2813.a" "clipLibrary1.cel[0].cev[85].cevr";
connectAttr "animCurveTA2814.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "animCurveTL952.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "animCurveTL953.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "animCurveTL954.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr "animCurveTA2815.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "animCurveTA2816.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "animCurveTA2817.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "animCurveTL955.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "animCurveTL956.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "animCurveTL957.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "animCurveTU1453.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "animCurveTA2818.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "animCurveTA2819.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "animCurveTA2820.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "animCurveTL958.a" "clipLibrary1.cel[0].cev[100].cevr";
connectAttr "animCurveTL959.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "animCurveTL960.a" "clipLibrary1.cel[0].cev[102].cevr";
connectAttr "animCurveTA2821.a" "clipLibrary1.cel[0].cev[103].cevr";
connectAttr "animCurveTA2822.a" "clipLibrary1.cel[0].cev[104].cevr";
connectAttr "animCurveTA2823.a" "clipLibrary1.cel[0].cev[105].cevr";
connectAttr "animCurveTL961.a" "clipLibrary1.cel[0].cev[106].cevr";
connectAttr "animCurveTL962.a" "clipLibrary1.cel[0].cev[107].cevr";
connectAttr "animCurveTL963.a" "clipLibrary1.cel[0].cev[108].cevr";
connectAttr "animCurveTU1454.a" "clipLibrary1.cel[0].cev[109].cevr";
connectAttr "animCurveTU1455.a" "clipLibrary1.cel[0].cev[110].cevr";
connectAttr "animCurveTU1456.a" "clipLibrary1.cel[0].cev[111].cevr";
connectAttr "animCurveTU1457.a" "clipLibrary1.cel[0].cev[112].cevr";
connectAttr "animCurveTU1458.a" "clipLibrary1.cel[0].cev[113].cevr";
connectAttr "animCurveTU1459.a" "clipLibrary1.cel[0].cev[114].cevr";
connectAttr "animCurveTU1460.a" "clipLibrary1.cel[0].cev[115].cevr";
connectAttr "animCurveTA2824.a" "clipLibrary1.cel[0].cev[116].cevr";
connectAttr "animCurveTA2825.a" "clipLibrary1.cel[0].cev[117].cevr";
connectAttr "animCurveTA2826.a" "clipLibrary1.cel[0].cev[118].cevr";
connectAttr "animCurveTA2827.a" "clipLibrary1.cel[0].cev[119].cevr";
connectAttr "animCurveTA2828.a" "clipLibrary1.cel[0].cev[120].cevr";
connectAttr "animCurveTA2829.a" "clipLibrary1.cel[0].cev[121].cevr";
connectAttr "animCurveTA2830.a" "clipLibrary1.cel[0].cev[122].cevr";
connectAttr "animCurveTA2831.a" "clipLibrary1.cel[0].cev[123].cevr";
connectAttr "animCurveTA2832.a" "clipLibrary1.cel[0].cev[124].cevr";
connectAttr "animCurveTA2833.a" "clipLibrary1.cel[0].cev[125].cevr";
connectAttr "animCurveTA2834.a" "clipLibrary1.cel[0].cev[126].cevr";
connectAttr "animCurveTA2835.a" "clipLibrary1.cel[0].cev[127].cevr";
connectAttr "animCurveTA2836.a" "clipLibrary1.cel[0].cev[128].cevr";
connectAttr "animCurveTA2837.a" "clipLibrary1.cel[0].cev[129].cevr";
connectAttr "animCurveTA2838.a" "clipLibrary1.cel[0].cev[130].cevr";
connectAttr "animCurveTA2839.a" "clipLibrary1.cel[0].cev[131].cevr";
connectAttr "animCurveTU1461.a" "clipLibrary1.cel[0].cev[132].cevr";
connectAttr "animCurveTU1462.a" "clipLibrary1.cel[0].cev[133].cevr";
connectAttr "animCurveTU1463.a" "clipLibrary1.cel[0].cev[134].cevr";
connectAttr "animCurveTL964.a" "clipLibrary1.cel[0].cev[135].cevr";
connectAttr "animCurveTL965.a" "clipLibrary1.cel[0].cev[136].cevr";
connectAttr "animCurveTL966.a" "clipLibrary1.cel[0].cev[137].cevr";
connectAttr "animCurveTU1464.a" "clipLibrary1.cel[0].cev[138].cevr";
connectAttr "animCurveTL967.a" "clipLibrary1.cel[0].cev[139].cevr";
connectAttr "animCurveTL968.a" "clipLibrary1.cel[0].cev[140].cevr";
connectAttr "animCurveTL969.a" "clipLibrary1.cel[0].cev[141].cevr";
connectAttr "animCurveTA2840.a" "clipLibrary1.cel[0].cev[142].cevr";
connectAttr "animCurveTA2841.a" "clipLibrary1.cel[0].cev[143].cevr";
connectAttr "animCurveTA2842.a" "clipLibrary1.cel[0].cev[144].cevr";
connectAttr "animCurveTL970.a" "clipLibrary1.cel[0].cev[145].cevr";
connectAttr "animCurveTL971.a" "clipLibrary1.cel[0].cev[146].cevr";
connectAttr "animCurveTL972.a" "clipLibrary1.cel[0].cev[147].cevr";
connectAttr "animCurveTU1465.a" "clipLibrary1.cel[0].cev[148].cevr";
connectAttr "animCurveTU1466.a" "clipLibrary1.cel[0].cev[149].cevr";
connectAttr "animCurveTU1467.a" "clipLibrary1.cel[0].cev[150].cevr";
connectAttr "animCurveTU1468.a" "clipLibrary1.cel[0].cev[151].cevr";
connectAttr "animCurveTU1469.a" "clipLibrary1.cel[0].cev[152].cevr";
connectAttr "animCurveTU1470.a" "clipLibrary1.cel[0].cev[153].cevr";
connectAttr "animCurveTU1471.a" "clipLibrary1.cel[0].cev[154].cevr";
connectAttr "animCurveTU1472.a" "clipLibrary1.cel[0].cev[155].cevr";
connectAttr "animCurveTA2843.a" "clipLibrary1.cel[0].cev[156].cevr";
connectAttr "animCurveTA2844.a" "clipLibrary1.cel[0].cev[157].cevr";
connectAttr "animCurveTA2845.a" "clipLibrary1.cel[0].cev[158].cevr";
connectAttr "animCurveTL973.a" "clipLibrary1.cel[0].cev[159].cevr";
connectAttr "animCurveTL974.a" "clipLibrary1.cel[0].cev[160].cevr";
connectAttr "animCurveTL975.a" "clipLibrary1.cel[0].cev[161].cevr";
connectAttr "animCurveTU1473.a" "clipLibrary1.cel[0].cev[162].cevr";
connectAttr "animCurveTU1474.a" "clipLibrary1.cel[0].cev[163].cevr";
connectAttr "animCurveTU1475.a" "clipLibrary1.cel[0].cev[164].cevr";
connectAttr "animCurveTL976.a" "clipLibrary1.cel[0].cev[165].cevr";
connectAttr "animCurveTL977.a" "clipLibrary1.cel[0].cev[166].cevr";
connectAttr "animCurveTL978.a" "clipLibrary1.cel[0].cev[167].cevr";
connectAttr "animCurveTU1476.a" "clipLibrary1.cel[0].cev[168].cevr";
connectAttr "animCurveTL979.a" "clipLibrary1.cel[0].cev[169].cevr";
connectAttr "animCurveTL980.a" "clipLibrary1.cel[0].cev[170].cevr";
connectAttr "animCurveTL981.a" "clipLibrary1.cel[0].cev[171].cevr";
connectAttr "animCurveTA2846.a" "clipLibrary1.cel[0].cev[172].cevr";
connectAttr "animCurveTA2847.a" "clipLibrary1.cel[0].cev[173].cevr";
connectAttr "animCurveTA2848.a" "clipLibrary1.cel[0].cev[174].cevr";
connectAttr "animCurveTL982.a" "clipLibrary1.cel[0].cev[175].cevr";
connectAttr "animCurveTL983.a" "clipLibrary1.cel[0].cev[176].cevr";
connectAttr "animCurveTL984.a" "clipLibrary1.cel[0].cev[177].cevr";
connectAttr "animCurveTU1477.a" "clipLibrary1.cel[0].cev[178].cevr";
connectAttr "animCurveTU1478.a" "clipLibrary1.cel[0].cev[179].cevr";
connectAttr "animCurveTU1479.a" "clipLibrary1.cel[0].cev[180].cevr";
connectAttr "animCurveTU1480.a" "clipLibrary1.cel[0].cev[181].cevr";
connectAttr "animCurveTU1481.a" "clipLibrary1.cel[0].cev[182].cevr";
connectAttr "animCurveTA2849.a" "clipLibrary1.cel[0].cev[183].cevr";
connectAttr "animCurveTA2850.a" "clipLibrary1.cel[0].cev[184].cevr";
connectAttr "animCurveTA2851.a" "clipLibrary1.cel[0].cev[185].cevr";
connectAttr "animCurveTL985.a" "clipLibrary1.cel[0].cev[186].cevr";
connectAttr "animCurveTL986.a" "clipLibrary1.cel[0].cev[187].cevr";
connectAttr "animCurveTL987.a" "clipLibrary1.cel[0].cev[188].cevr";
connectAttr "animCurveTU1482.a" "clipLibrary1.cel[0].cev[189].cevr";
connectAttr "animCurveTU1483.a" "clipLibrary1.cel[0].cev[190].cevr";
connectAttr "animCurveTU1484.a" "clipLibrary1.cel[0].cev[191].cevr";
connectAttr "animCurveTU1485.a" "clipLibrary1.cel[0].cev[192].cevr";
connectAttr "animCurveTU1486.a" "clipLibrary1.cel[0].cev[193].cevr";
connectAttr "animCurveTU1487.a" "clipLibrary1.cel[0].cev[194].cevr";
connectAttr "animCurveTU1488.a" "clipLibrary1.cel[0].cev[195].cevr";
connectAttr "animCurveTU1489.a" "clipLibrary1.cel[0].cev[196].cevr";
connectAttr "animCurveTU1490.a" "clipLibrary1.cel[0].cev[197].cevr";
connectAttr "animCurveTU1491.a" "clipLibrary1.cel[0].cev[198].cevr";
connectAttr "animCurveTA2852.a" "clipLibrary1.cel[0].cev[199].cevr";
connectAttr "animCurveTA2853.a" "clipLibrary1.cel[0].cev[200].cevr";
connectAttr "animCurveTA2854.a" "clipLibrary1.cel[0].cev[201].cevr";
connectAttr "animCurveTL988.a" "clipLibrary1.cel[0].cev[202].cevr";
connectAttr "animCurveTL989.a" "clipLibrary1.cel[0].cev[203].cevr";
connectAttr "animCurveTL990.a" "clipLibrary1.cel[0].cev[204].cevr";
connectAttr "animCurveTU1492.a" "clipLibrary1.cel[0].cev[205].cevr";
connectAttr "animCurveTU1493.a" "clipLibrary1.cel[0].cev[206].cevr";
connectAttr "animCurveTU1494.a" "clipLibrary1.cel[0].cev[207].cevr";
connectAttr "animCurveTA2855.a" "clipLibrary1.cel[0].cev[208].cevr";
connectAttr "animCurveTA2856.a" "clipLibrary1.cel[0].cev[209].cevr";
connectAttr "animCurveTA2857.a" "clipLibrary1.cel[0].cev[210].cevr";
connectAttr "animCurveTL991.a" "clipLibrary1.cel[0].cev[211].cevr";
connectAttr "animCurveTL992.a" "clipLibrary1.cel[0].cev[212].cevr";
connectAttr "animCurveTL993.a" "clipLibrary1.cel[0].cev[213].cevr";
connectAttr "animCurveTU1495.a" "clipLibrary1.cel[0].cev[214].cevr";
connectAttr "animCurveTU1496.a" "clipLibrary1.cel[0].cev[215].cevr";
connectAttr "animCurveTU1497.a" "clipLibrary1.cel[0].cev[216].cevr";
connectAttr "animCurveTA2858.a" "clipLibrary1.cel[0].cev[217].cevr";
connectAttr "animCurveTA2859.a" "clipLibrary1.cel[0].cev[218].cevr";
connectAttr "animCurveTA2860.a" "clipLibrary1.cel[0].cev[219].cevr";
connectAttr "animCurveTL994.a" "clipLibrary1.cel[0].cev[220].cevr";
connectAttr "animCurveTL995.a" "clipLibrary1.cel[0].cev[221].cevr";
connectAttr "animCurveTL996.a" "clipLibrary1.cel[0].cev[222].cevr";
connectAttr "animCurveTU1498.a" "clipLibrary1.cel[0].cev[223].cevr";
connectAttr "animCurveTU1499.a" "clipLibrary1.cel[0].cev[224].cevr";
connectAttr "animCurveTA2861.a" "clipLibrary1.cel[0].cev[225].cevr";
connectAttr "animCurveTA2862.a" "clipLibrary1.cel[0].cev[226].cevr";
connectAttr "animCurveTA2863.a" "clipLibrary1.cel[0].cev[227].cevr";
connectAttr "animCurveTL997.a" "clipLibrary1.cel[0].cev[228].cevr";
connectAttr "animCurveTL998.a" "clipLibrary1.cel[0].cev[229].cevr";
connectAttr "animCurveTL999.a" "clipLibrary1.cel[0].cev[230].cevr";
connectAttr "animCurveTU1500.a" "clipLibrary1.cel[0].cev[231].cevr";
connectAttr "animCurveTU1501.a" "clipLibrary1.cel[0].cev[232].cevr";
connectAttr "animCurveTU1502.a" "clipLibrary1.cel[0].cev[233].cevr";
connectAttr "animCurveTA2864.a" "clipLibrary1.cel[0].cev[234].cevr";
connectAttr "animCurveTA2865.a" "clipLibrary1.cel[0].cev[235].cevr";
connectAttr "animCurveTA2866.a" "clipLibrary1.cel[0].cev[236].cevr";
connectAttr "animCurveTL1000.a" "clipLibrary1.cel[0].cev[237].cevr";
connectAttr "animCurveTL1001.a" "clipLibrary1.cel[0].cev[238].cevr";
connectAttr "animCurveTL1002.a" "clipLibrary1.cel[0].cev[239].cevr";
connectAttr "animCurveTU1503.a" "clipLibrary1.cel[0].cev[240].cevr";
connectAttr "animCurveTU1504.a" "clipLibrary1.cel[0].cev[241].cevr";
connectAttr "animCurveTA2867.a" "clipLibrary1.cel[0].cev[242].cevr";
connectAttr "animCurveTA2868.a" "clipLibrary1.cel[0].cev[243].cevr";
connectAttr "animCurveTA2869.a" "clipLibrary1.cel[0].cev[244].cevr";
connectAttr "animCurveTL1003.a" "clipLibrary1.cel[0].cev[245].cevr";
connectAttr "animCurveTL1004.a" "clipLibrary1.cel[0].cev[246].cevr";
connectAttr "animCurveTL1005.a" "clipLibrary1.cel[0].cev[247].cevr";
connectAttr "animCurveTA2870.a" "clipLibrary1.cel[0].cev[248].cevr";
connectAttr "animCurveTA2871.a" "clipLibrary1.cel[0].cev[249].cevr";
connectAttr "animCurveTA2872.a" "clipLibrary1.cel[0].cev[250].cevr";
connectAttr "animCurveTA2873.a" "clipLibrary1.cel[0].cev[251].cevr";
connectAttr "animCurveTA2874.a" "clipLibrary1.cel[0].cev[252].cevr";
connectAttr "animCurveTA2875.a" "clipLibrary1.cel[0].cev[253].cevr";
connectAttr "animCurveTA2876.a" "clipLibrary1.cel[0].cev[254].cevr";
connectAttr "animCurveTA2877.a" "clipLibrary1.cel[0].cev[255].cevr";
connectAttr "animCurveTA2878.a" "clipLibrary1.cel[0].cev[256].cevr";
connectAttr "animCurveTA2879.a" "clipLibrary1.cel[0].cev[257].cevr";
connectAttr "animCurveTA2880.a" "clipLibrary1.cel[0].cev[258].cevr";
connectAttr "animCurveTA2881.a" "clipLibrary1.cel[0].cev[259].cevr";
connectAttr "animCurveTA2882.a" "clipLibrary1.cel[0].cev[260].cevr";
connectAttr "animCurveTA2883.a" "clipLibrary1.cel[0].cev[261].cevr";
connectAttr "animCurveTA2884.a" "clipLibrary1.cel[0].cev[262].cevr";
connectAttr "animCurveTA2885.a" "clipLibrary1.cel[0].cev[263].cevr";
connectAttr "animCurveTU1505.a" "clipLibrary1.cel[0].cev[264].cevr";
connectAttr "animCurveTU1506.a" "clipLibrary1.cel[0].cev[265].cevr";
connectAttr "animCurveTU1507.a" "clipLibrary1.cel[0].cev[266].cevr";
connectAttr "animCurveTL1006.a" "clipLibrary1.cel[0].cev[267].cevr";
connectAttr "animCurveTL1007.a" "clipLibrary1.cel[0].cev[268].cevr";
connectAttr "animCurveTL1008.a" "clipLibrary1.cel[0].cev[269].cevr";
connectAttr "animCurveTU1508.a" "clipLibrary1.cel[0].cev[270].cevr";
connectAttr "animCurveTL1009.a" "clipLibrary1.cel[0].cev[271].cevr";
connectAttr "animCurveTL1010.a" "clipLibrary1.cel[0].cev[272].cevr";
connectAttr "animCurveTL1011.a" "clipLibrary1.cel[0].cev[273].cevr";
connectAttr "animCurveTA2886.a" "clipLibrary1.cel[0].cev[274].cevr";
connectAttr "animCurveTA2887.a" "clipLibrary1.cel[0].cev[275].cevr";
connectAttr "animCurveTA2888.a" "clipLibrary1.cel[0].cev[276].cevr";
connectAttr "animCurveTL1012.a" "clipLibrary1.cel[0].cev[277].cevr";
connectAttr "animCurveTL1013.a" "clipLibrary1.cel[0].cev[278].cevr";
connectAttr "animCurveTL1014.a" "clipLibrary1.cel[0].cev[279].cevr";
connectAttr "animCurveTU1509.a" "clipLibrary1.cel[0].cev[280].cevr";
connectAttr "animCurveTU1510.a" "clipLibrary1.cel[0].cev[281].cevr";
connectAttr "animCurveTU1511.a" "clipLibrary1.cel[0].cev[282].cevr";
connectAttr "animCurveTU1512.a" "clipLibrary1.cel[0].cev[283].cevr";
connectAttr "animCurveTU1513.a" "clipLibrary1.cel[0].cev[284].cevr";
connectAttr "animCurveTU1514.a" "clipLibrary1.cel[0].cev[285].cevr";
connectAttr "animCurveTU1515.a" "clipLibrary1.cel[0].cev[286].cevr";
connectAttr "animCurveTU1516.a" "clipLibrary1.cel[0].cev[287].cevr";
connectAttr "animCurveTA2889.a" "clipLibrary1.cel[0].cev[288].cevr";
connectAttr "animCurveTA2890.a" "clipLibrary1.cel[0].cev[289].cevr";
connectAttr "animCurveTA2891.a" "clipLibrary1.cel[0].cev[290].cevr";
connectAttr "animCurveTL1015.a" "clipLibrary1.cel[0].cev[291].cevr";
connectAttr "animCurveTL1016.a" "clipLibrary1.cel[0].cev[292].cevr";
connectAttr "animCurveTL1017.a" "clipLibrary1.cel[0].cev[293].cevr";
connectAttr "animCurveTU1517.a" "clipLibrary1.cel[0].cev[294].cevr";
connectAttr "animCurveTU1518.a" "clipLibrary1.cel[0].cev[295].cevr";
connectAttr "animCurveTU1519.a" "clipLibrary1.cel[0].cev[296].cevr";
connectAttr "animCurveTL1018.a" "clipLibrary1.cel[0].cev[297].cevr";
connectAttr "animCurveTL1019.a" "clipLibrary1.cel[0].cev[298].cevr";
connectAttr "animCurveTL1020.a" "clipLibrary1.cel[0].cev[299].cevr";
connectAttr "animCurveTU1520.a" "clipLibrary1.cel[0].cev[300].cevr";
connectAttr "animCurveTL1021.a" "clipLibrary1.cel[0].cev[301].cevr";
connectAttr "animCurveTL1022.a" "clipLibrary1.cel[0].cev[302].cevr";
connectAttr "animCurveTL1023.a" "clipLibrary1.cel[0].cev[303].cevr";
connectAttr "animCurveTA2892.a" "clipLibrary1.cel[0].cev[304].cevr";
connectAttr "animCurveTA2893.a" "clipLibrary1.cel[0].cev[305].cevr";
connectAttr "animCurveTA2894.a" "clipLibrary1.cel[0].cev[306].cevr";
connectAttr "animCurveTL1024.a" "clipLibrary1.cel[0].cev[307].cevr";
connectAttr "animCurveTL1025.a" "clipLibrary1.cel[0].cev[308].cevr";
connectAttr "animCurveTL1026.a" "clipLibrary1.cel[0].cev[309].cevr";
connectAttr "animCurveTU1521.a" "clipLibrary1.cel[0].cev[310].cevr";
connectAttr "animCurveTU1522.a" "clipLibrary1.cel[0].cev[311].cevr";
connectAttr "animCurveTU1523.a" "clipLibrary1.cel[0].cev[312].cevr";
connectAttr "animCurveTU1524.a" "clipLibrary1.cel[0].cev[313].cevr";
connectAttr "animCurveTU1525.a" "clipLibrary1.cel[0].cev[314].cevr";
connectAttr "animCurveTA2895.a" "clipLibrary1.cel[0].cev[315].cevr";
connectAttr "animCurveTA2896.a" "clipLibrary1.cel[0].cev[316].cevr";
connectAttr "animCurveTA2897.a" "clipLibrary1.cel[0].cev[317].cevr";
connectAttr "animCurveTL1027.a" "clipLibrary1.cel[0].cev[318].cevr";
connectAttr "animCurveTL1028.a" "clipLibrary1.cel[0].cev[319].cevr";
connectAttr "animCurveTL1029.a" "clipLibrary1.cel[0].cev[320].cevr";
connectAttr "animCurveTA2898.a" "clipLibrary1.cel[0].cev[321].cevr";
connectAttr "animCurveTA2899.a" "clipLibrary1.cel[0].cev[322].cevr";
connectAttr "animCurveTA2900.a" "clipLibrary1.cel[0].cev[323].cevr";
connectAttr "animCurveTA2901.a" "clipLibrary1.cel[0].cev[324].cevr";
connectAttr "animCurveTA2902.a" "clipLibrary1.cel[0].cev[325].cevr";
connectAttr "animCurveTA2903.a" "clipLibrary1.cel[0].cev[326].cevr";
connectAttr "animCurveTU1526.a" "clipLibrary1.cel[0].cev[327].cevr";
connectAttr "animCurveTU1527.a" "clipLibrary1.cel[0].cev[328].cevr";
connectAttr "animCurveTU1528.a" "clipLibrary1.cel[0].cev[329].cevr";
connectAttr "animCurveTA2904.a" "clipLibrary1.cel[0].cev[330].cevr";
connectAttr "animCurveTA2905.a" "clipLibrary1.cel[0].cev[331].cevr";
connectAttr "animCurveTA2906.a" "clipLibrary1.cel[0].cev[332].cevr";
connectAttr "animCurveTA2907.a" "clipLibrary1.cel[0].cev[333].cevr";
connectAttr "animCurveTA2908.a" "clipLibrary1.cel[0].cev[334].cevr";
connectAttr "animCurveTA2909.a" "clipLibrary1.cel[0].cev[335].cevr";
connectAttr "animCurveTU1529.a" "clipLibrary1.cel[0].cev[336].cevr";
connectAttr "animCurveTU1530.a" "clipLibrary1.cel[0].cev[337].cevr";
connectAttr "animCurveTU1531.a" "clipLibrary1.cel[0].cev[338].cevr";
connectAttr "animCurveTA2910.a" "clipLibrary1.cel[0].cev[339].cevr";
connectAttr "animCurveTA2911.a" "clipLibrary1.cel[0].cev[340].cevr";
connectAttr "animCurveTA2912.a" "clipLibrary1.cel[0].cev[341].cevr";
connectAttr "animCurveTA2913.a" "clipLibrary1.cel[0].cev[342].cevr";
connectAttr "animCurveTA2914.a" "clipLibrary1.cel[0].cev[343].cevr";
connectAttr "animCurveTA2915.a" "clipLibrary1.cel[0].cev[344].cevr";
connectAttr "animCurveTU1532.a" "clipLibrary1.cel[0].cev[345].cevr";
connectAttr "animCurveTU1533.a" "clipLibrary1.cel[0].cev[346].cevr";
connectAttr "animCurveTU1534.a" "clipLibrary1.cel[0].cev[347].cevr";
connectAttr "animCurveTA2916.a" "clipLibrary1.cel[0].cev[348].cevr";
connectAttr "animCurveTA2917.a" "clipLibrary1.cel[0].cev[349].cevr";
connectAttr "animCurveTA2918.a" "clipLibrary1.cel[0].cev[350].cevr";
connectAttr "animCurveTA2919.a" "clipLibrary1.cel[0].cev[351].cevr";
connectAttr "animCurveTA2920.a" "clipLibrary1.cel[0].cev[352].cevr";
connectAttr "animCurveTA2921.a" "clipLibrary1.cel[0].cev[353].cevr";
connectAttr "animCurveTU1535.a" "clipLibrary1.cel[0].cev[354].cevr";
connectAttr "animCurveTU1536.a" "clipLibrary1.cel[0].cev[355].cevr";
connectAttr "animCurveTU1537.a" "clipLibrary1.cel[0].cev[356].cevr";
connectAttr "animCurveTA2922.a" "clipLibrary1.cel[0].cev[357].cevr";
connectAttr "animCurveTA2923.a" "clipLibrary1.cel[0].cev[358].cevr";
connectAttr "animCurveTA2924.a" "clipLibrary1.cel[0].cev[359].cevr";
connectAttr "animCurveTU1538.a" "clipLibrary1.cel[0].cev[360].cevr";
connectAttr "animCurveTU1539.a" "clipLibrary1.cel[0].cev[361].cevr";
connectAttr "animCurveTU1540.a" "clipLibrary1.cel[0].cev[362].cevr";
connectAttr "animCurveTA2925.a" "clipLibrary1.cel[0].cev[363].cevr";
connectAttr "animCurveTA2926.a" "clipLibrary1.cel[0].cev[364].cevr";
connectAttr "animCurveTA2927.a" "clipLibrary1.cel[0].cev[365].cevr";
connectAttr "animCurveTL1030.a" "clipLibrary1.cel[0].cev[366].cevr";
connectAttr "animCurveTL1031.a" "clipLibrary1.cel[0].cev[367].cevr";
connectAttr "animCurveTL1032.a" "clipLibrary1.cel[0].cev[368].cevr";
connectAttr "animCurveTU1541.a" "clipLibrary1.cel[0].cev[369].cevr";
connectAttr "animCurveTU1542.a" "clipLibrary1.cel[0].cev[370].cevr";
connectAttr "animCurveTU1543.a" "clipLibrary1.cel[0].cev[371].cevr";
connectAttr "animCurveTA2928.a" "clipLibrary1.cel[0].cev[372].cevr";
connectAttr "animCurveTA2929.a" "clipLibrary1.cel[0].cev[373].cevr";
connectAttr "animCurveTA2930.a" "clipLibrary1.cel[0].cev[374].cevr";
connectAttr "animCurveTL1033.a" "clipLibrary1.cel[0].cev[375].cevr";
connectAttr "animCurveTL1034.a" "clipLibrary1.cel[0].cev[376].cevr";
connectAttr "animCurveTL1035.a" "clipLibrary1.cel[0].cev[377].cevr";
connectAttr "animCurveTA2931.a" "clipLibrary1.cel[0].cev[378].cevr";
connectAttr "animCurveTA2932.a" "clipLibrary1.cel[0].cev[379].cevr";
connectAttr "animCurveTA2933.a" "clipLibrary1.cel[0].cev[380].cevr";
connectAttr "animCurveTU1544.a" "clipLibrary1.cel[0].cev[381].cevr";
connectAttr "animCurveTU1545.a" "clipLibrary1.cel[0].cev[382].cevr";
connectAttr "animCurveTU1546.a" "clipLibrary1.cel[0].cev[383].cevr";
connectAttr "animCurveTA2934.a" "clipLibrary1.cel[0].cev[384].cevr";
connectAttr "animCurveTA2935.a" "clipLibrary1.cel[0].cev[385].cevr";
connectAttr "animCurveTA2936.a" "clipLibrary1.cel[0].cev[386].cevr";
connectAttr "animCurveTA2937.a" "clipLibrary1.cel[0].cev[387].cevr";
connectAttr "animCurveTA2938.a" "clipLibrary1.cel[0].cev[388].cevr";
connectAttr "animCurveTA2939.a" "clipLibrary1.cel[0].cev[389].cevr";
connectAttr "animCurveTU1547.a" "clipLibrary1.cel[0].cev[390].cevr";
connectAttr "animCurveTU1548.a" "clipLibrary1.cel[0].cev[391].cevr";
connectAttr "animCurveTU1549.a" "clipLibrary1.cel[0].cev[392].cevr";
connectAttr "animCurveTA2940.a" "clipLibrary1.cel[0].cev[393].cevr";
connectAttr "animCurveTA2941.a" "clipLibrary1.cel[0].cev[394].cevr";
connectAttr "animCurveTA2942.a" "clipLibrary1.cel[0].cev[395].cevr";
connectAttr "animCurveTA2943.a" "clipLibrary1.cel[0].cev[396].cevr";
connectAttr "animCurveTA2944.a" "clipLibrary1.cel[0].cev[397].cevr";
connectAttr "animCurveTA2945.a" "clipLibrary1.cel[0].cev[398].cevr";
connectAttr "animCurveTU1550.a" "clipLibrary1.cel[0].cev[399].cevr";
connectAttr "animCurveTU1551.a" "clipLibrary1.cel[0].cev[400].cevr";
connectAttr "animCurveTU1552.a" "clipLibrary1.cel[0].cev[401].cevr";
connectAttr "animCurveTA2946.a" "clipLibrary1.cel[0].cev[402].cevr";
connectAttr "animCurveTA2947.a" "clipLibrary1.cel[0].cev[403].cevr";
connectAttr "animCurveTA2948.a" "clipLibrary1.cel[0].cev[404].cevr";
connectAttr "animCurveTA2949.a" "clipLibrary1.cel[0].cev[405].cevr";
connectAttr "animCurveTA2950.a" "clipLibrary1.cel[0].cev[406].cevr";
connectAttr "animCurveTA2951.a" "clipLibrary1.cel[0].cev[407].cevr";
connectAttr "animCurveTU1553.a" "clipLibrary1.cel[0].cev[408].cevr";
connectAttr "animCurveTU1554.a" "clipLibrary1.cel[0].cev[409].cevr";
connectAttr "animCurveTU1555.a" "clipLibrary1.cel[0].cev[410].cevr";
connectAttr "animCurveTA2952.a" "clipLibrary1.cel[0].cev[411].cevr";
connectAttr "animCurveTA2953.a" "clipLibrary1.cel[0].cev[412].cevr";
connectAttr "animCurveTA2954.a" "clipLibrary1.cel[0].cev[413].cevr";
connectAttr "animCurveTA2955.a" "clipLibrary1.cel[0].cev[414].cevr";
connectAttr "animCurveTA2956.a" "clipLibrary1.cel[0].cev[415].cevr";
connectAttr "animCurveTA2957.a" "clipLibrary1.cel[0].cev[416].cevr";
connectAttr "animCurveTU1556.a" "clipLibrary1.cel[0].cev[417].cevr";
connectAttr "animCurveTU1557.a" "clipLibrary1.cel[0].cev[418].cevr";
connectAttr "animCurveTU1558.a" "clipLibrary1.cel[0].cev[419].cevr";
connectAttr "animCurveTA2958.a" "clipLibrary1.cel[0].cev[420].cevr";
connectAttr "animCurveTA2959.a" "clipLibrary1.cel[0].cev[421].cevr";
connectAttr "animCurveTA2960.a" "clipLibrary1.cel[0].cev[422].cevr";
connectAttr "animCurveTA2961.a" "clipLibrary1.cel[0].cev[423].cevr";
connectAttr "animCurveTA2962.a" "clipLibrary1.cel[0].cev[424].cevr";
connectAttr "animCurveTA2963.a" "clipLibrary1.cel[0].cev[425].cevr";
connectAttr "animCurveTU1559.a" "clipLibrary1.cel[0].cev[426].cevr";
connectAttr "animCurveTU1560.a" "clipLibrary1.cel[0].cev[427].cevr";
connectAttr "animCurveTU1561.a" "clipLibrary1.cel[0].cev[428].cevr";
connectAttr "animCurveTA2964.a" "clipLibrary1.cel[0].cev[429].cevr";
connectAttr "animCurveTA2965.a" "clipLibrary1.cel[0].cev[430].cevr";
connectAttr "animCurveTA2966.a" "clipLibrary1.cel[0].cev[431].cevr";
connectAttr "animCurveTA2967.a" "clipLibrary1.cel[0].cev[432].cevr";
connectAttr "animCurveTA2968.a" "clipLibrary1.cel[0].cev[433].cevr";
connectAttr "animCurveTA2969.a" "clipLibrary1.cel[0].cev[434].cevr";
connectAttr "animCurveTU1562.a" "clipLibrary1.cel[0].cev[435].cevr";
connectAttr "animCurveTU1563.a" "clipLibrary1.cel[0].cev[436].cevr";
connectAttr "animCurveTU1564.a" "clipLibrary1.cel[0].cev[437].cevr";
connectAttr "animCurveTA2970.a" "clipLibrary1.cel[0].cev[438].cevr";
connectAttr "animCurveTA2971.a" "clipLibrary1.cel[0].cev[439].cevr";
connectAttr "animCurveTA2972.a" "clipLibrary1.cel[0].cev[440].cevr";
connectAttr "animCurveTA2973.a" "clipLibrary1.cel[0].cev[441].cevr";
connectAttr "animCurveTA2974.a" "clipLibrary1.cel[0].cev[442].cevr";
connectAttr "animCurveTA2975.a" "clipLibrary1.cel[0].cev[443].cevr";
connectAttr "animCurveTU1565.a" "clipLibrary1.cel[0].cev[444].cevr";
connectAttr "animCurveTU1566.a" "clipLibrary1.cel[0].cev[445].cevr";
connectAttr "animCurveTU1567.a" "clipLibrary1.cel[0].cev[446].cevr";
connectAttr "animCurveTA2976.a" "clipLibrary1.cel[0].cev[447].cevr";
connectAttr "animCurveTA2977.a" "clipLibrary1.cel[0].cev[448].cevr";
connectAttr "animCurveTA2978.a" "clipLibrary1.cel[0].cev[449].cevr";
connectAttr "animCurveTA2979.a" "clipLibrary1.cel[0].cev[450].cevr";
connectAttr "animCurveTA2980.a" "clipLibrary1.cel[0].cev[451].cevr";
connectAttr "animCurveTA2981.a" "clipLibrary1.cel[0].cev[452].cevr";
connectAttr "animCurveTU1568.a" "clipLibrary1.cel[0].cev[453].cevr";
connectAttr "animCurveTU1569.a" "clipLibrary1.cel[0].cev[454].cevr";
connectAttr "animCurveTU1570.a" "clipLibrary1.cel[0].cev[455].cevr";
connectAttr "animCurveTA2982.a" "clipLibrary1.cel[0].cev[456].cevr";
connectAttr "animCurveTA2983.a" "clipLibrary1.cel[0].cev[457].cevr";
connectAttr "animCurveTA2984.a" "clipLibrary1.cel[0].cev[458].cevr";
connectAttr "animCurveTA2985.a" "clipLibrary1.cel[0].cev[459].cevr";
connectAttr "animCurveTA2986.a" "clipLibrary1.cel[0].cev[460].cevr";
connectAttr "animCurveTA2987.a" "clipLibrary1.cel[0].cev[461].cevr";
connectAttr "animCurveTU1571.a" "clipLibrary1.cel[0].cev[462].cevr";
connectAttr "animCurveTU1572.a" "clipLibrary1.cel[0].cev[463].cevr";
connectAttr "animCurveTU1573.a" "clipLibrary1.cel[0].cev[464].cevr";
connectAttr "animCurveTA2988.a" "clipLibrary1.cel[0].cev[465].cevr";
connectAttr "animCurveTA2989.a" "clipLibrary1.cel[0].cev[466].cevr";
connectAttr "animCurveTA2990.a" "clipLibrary1.cel[0].cev[467].cevr";
connectAttr "animCurveTA2991.a" "clipLibrary1.cel[0].cev[468].cevr";
connectAttr "animCurveTA2992.a" "clipLibrary1.cel[0].cev[469].cevr";
connectAttr "animCurveTA2993.a" "clipLibrary1.cel[0].cev[470].cevr";
connectAttr "animCurveTU1574.a" "clipLibrary1.cel[0].cev[471].cevr";
connectAttr "animCurveTU1575.a" "clipLibrary1.cel[0].cev[472].cevr";
connectAttr "animCurveTU1576.a" "clipLibrary1.cel[0].cev[473].cevr";
connectAttr "animCurveTA2994.a" "clipLibrary1.cel[0].cev[474].cevr";
connectAttr "animCurveTA2995.a" "clipLibrary1.cel[0].cev[475].cevr";
connectAttr "animCurveTA2996.a" "clipLibrary1.cel[0].cev[476].cevr";
connectAttr "animCurveTA2997.a" "clipLibrary1.cel[0].cev[477].cevr";
connectAttr "animCurveTA2998.a" "clipLibrary1.cel[0].cev[478].cevr";
connectAttr "animCurveTA2999.a" "clipLibrary1.cel[0].cev[479].cevr";
connectAttr "animCurveTU1577.a" "clipLibrary1.cel[0].cev[480].cevr";
connectAttr "animCurveTU1578.a" "clipLibrary1.cel[0].cev[481].cevr";
connectAttr "animCurveTU1579.a" "clipLibrary1.cel[0].cev[482].cevr";
connectAttr "animCurveTA3000.a" "clipLibrary1.cel[0].cev[483].cevr";
connectAttr "animCurveTA3001.a" "clipLibrary1.cel[0].cev[484].cevr";
connectAttr "animCurveTA3002.a" "clipLibrary1.cel[0].cev[485].cevr";
connectAttr "animCurveTA3003.a" "clipLibrary1.cel[0].cev[486].cevr";
connectAttr "animCurveTA3004.a" "clipLibrary1.cel[0].cev[487].cevr";
connectAttr "animCurveTA3005.a" "clipLibrary1.cel[0].cev[488].cevr";
connectAttr "animCurveTU1580.a" "clipLibrary1.cel[0].cev[489].cevr";
connectAttr "animCurveTU1581.a" "clipLibrary1.cel[0].cev[490].cevr";
connectAttr "animCurveTU1582.a" "clipLibrary1.cel[0].cev[491].cevr";
connectAttr "animCurveTA3006.a" "clipLibrary1.cel[0].cev[492].cevr";
connectAttr "animCurveTA3007.a" "clipLibrary1.cel[0].cev[493].cevr";
connectAttr "animCurveTA3008.a" "clipLibrary1.cel[0].cev[494].cevr";
connectAttr "animCurveTA3009.a" "clipLibrary1.cel[0].cev[495].cevr";
connectAttr "animCurveTA3010.a" "clipLibrary1.cel[0].cev[496].cevr";
connectAttr "animCurveTA3011.a" "clipLibrary1.cel[0].cev[497].cevr";
connectAttr "animCurveTU1583.a" "clipLibrary1.cel[0].cev[498].cevr";
connectAttr "animCurveTU1584.a" "clipLibrary1.cel[0].cev[499].cevr";
connectAttr "animCurveTU1585.a" "clipLibrary1.cel[0].cev[500].cevr";
connectAttr "animCurveTA3012.a" "clipLibrary1.cel[0].cev[501].cevr";
connectAttr "animCurveTA3013.a" "clipLibrary1.cel[0].cev[502].cevr";
connectAttr "animCurveTA3014.a" "clipLibrary1.cel[0].cev[503].cevr";
connectAttr "animCurveTA3015.a" "clipLibrary1.cel[0].cev[504].cevr";
connectAttr "animCurveTA3016.a" "clipLibrary1.cel[0].cev[505].cevr";
connectAttr "animCurveTA3017.a" "clipLibrary1.cel[0].cev[506].cevr";
connectAttr "animCurveTU1586.a" "clipLibrary1.cel[0].cev[507].cevr";
connectAttr "animCurveTU1587.a" "clipLibrary1.cel[0].cev[508].cevr";
connectAttr "animCurveTU1588.a" "clipLibrary1.cel[0].cev[509].cevr";
connectAttr "animCurveTA3018.a" "clipLibrary1.cel[0].cev[510].cevr";
connectAttr "animCurveTA3019.a" "clipLibrary1.cel[0].cev[511].cevr";
connectAttr "animCurveTA3020.a" "clipLibrary1.cel[0].cev[512].cevr";
connectAttr "animCurveTA3021.a" "clipLibrary1.cel[0].cev[513].cevr";
connectAttr "animCurveTA3022.a" "clipLibrary1.cel[0].cev[514].cevr";
connectAttr "animCurveTA3023.a" "clipLibrary1.cel[0].cev[515].cevr";
connectAttr "animCurveTU1589.a" "clipLibrary1.cel[0].cev[516].cevr";
connectAttr "animCurveTU1590.a" "clipLibrary1.cel[0].cev[517].cevr";
connectAttr "animCurveTU1591.a" "clipLibrary1.cel[0].cev[518].cevr";
connectAttr "animCurveTA3024.a" "clipLibrary1.cel[0].cev[519].cevr";
connectAttr "animCurveTA3025.a" "clipLibrary1.cel[0].cev[520].cevr";
connectAttr "animCurveTA3026.a" "clipLibrary1.cel[0].cev[521].cevr";
connectAttr "animCurveTA3027.a" "clipLibrary1.cel[0].cev[522].cevr";
connectAttr "animCurveTA3028.a" "clipLibrary1.cel[0].cev[523].cevr";
connectAttr "animCurveTA3029.a" "clipLibrary1.cel[0].cev[524].cevr";
connectAttr "animCurveTU1592.a" "clipLibrary1.cel[0].cev[525].cevr";
connectAttr "animCurveTU1593.a" "clipLibrary1.cel[0].cev[526].cevr";
connectAttr "animCurveTU1594.a" "clipLibrary1.cel[0].cev[527].cevr";
connectAttr "animCurveTA3030.a" "clipLibrary1.cel[0].cev[528].cevr";
connectAttr "animCurveTA3031.a" "clipLibrary1.cel[0].cev[529].cevr";
connectAttr "animCurveTA3032.a" "clipLibrary1.cel[0].cev[530].cevr";
connectAttr "animCurveTA3033.a" "clipLibrary1.cel[0].cev[531].cevr";
connectAttr "animCurveTA3034.a" "clipLibrary1.cel[0].cev[532].cevr";
connectAttr "animCurveTA3035.a" "clipLibrary1.cel[0].cev[533].cevr";
connectAttr "animCurveTU1595.a" "clipLibrary1.cel[0].cev[534].cevr";
connectAttr "animCurveTU1596.a" "clipLibrary1.cel[0].cev[535].cevr";
connectAttr "animCurveTU1597.a" "clipLibrary1.cel[0].cev[536].cevr";
connectAttr "animCurveTA3036.a" "clipLibrary1.cel[0].cev[537].cevr";
connectAttr "animCurveTA3037.a" "clipLibrary1.cel[0].cev[538].cevr";
connectAttr "animCurveTA3038.a" "clipLibrary1.cel[0].cev[539].cevr";
connectAttr "animCurveTU1598.a" "clipLibrary1.cel[0].cev[540].cevr";
connectAttr "animCurveTU1599.a" "clipLibrary1.cel[0].cev[541].cevr";
connectAttr "animCurveTU1600.a" "clipLibrary1.cel[0].cev[542].cevr";
connectAttr "animCurveTA3039.a" "clipLibrary1.cel[0].cev[543].cevr";
connectAttr "animCurveTA3040.a" "clipLibrary1.cel[0].cev[544].cevr";
connectAttr "animCurveTA3041.a" "clipLibrary1.cel[0].cev[545].cevr";
connectAttr "animCurveTL1036.a" "clipLibrary1.cel[0].cev[546].cevr";
connectAttr "animCurveTL1037.a" "clipLibrary1.cel[0].cev[547].cevr";
connectAttr "animCurveTL1038.a" "clipLibrary1.cel[0].cev[548].cevr";
connectAttr "animCurveTU1601.a" "clipLibrary1.cel[0].cev[549].cevr";
connectAttr "animCurveTU1602.a" "clipLibrary1.cel[0].cev[550].cevr";
connectAttr "animCurveTU1603.a" "clipLibrary1.cel[0].cev[551].cevr";
connectAttr "animCurveTA3042.a" "clipLibrary1.cel[0].cev[552].cevr";
connectAttr "animCurveTA3043.a" "clipLibrary1.cel[0].cev[553].cevr";
connectAttr "animCurveTA3044.a" "clipLibrary1.cel[0].cev[554].cevr";
connectAttr "animCurveTL1039.a" "clipLibrary1.cel[0].cev[555].cevr";
connectAttr "animCurveTL1040.a" "clipLibrary1.cel[0].cev[556].cevr";
connectAttr "animCurveTL1041.a" "clipLibrary1.cel[0].cev[557].cevr";
connectAttr "animCurveTA3045.a" "clipLibrary1.cel[0].cev[558].cevr";
connectAttr "animCurveTA3046.a" "clipLibrary1.cel[0].cev[559].cevr";
connectAttr "animCurveTA3047.a" "clipLibrary1.cel[0].cev[560].cevr";
connectAttr "animCurveTU1604.a" "clipLibrary1.cel[0].cev[561].cevr";
connectAttr "animCurveTU1605.a" "clipLibrary1.cel[0].cev[562].cevr";
connectAttr "animCurveTU1606.a" "clipLibrary1.cel[0].cev[563].cevr";
connectAttr "animCurveTA3048.a" "clipLibrary1.cel[0].cev[564].cevr";
connectAttr "animCurveTA3049.a" "clipLibrary1.cel[0].cev[565].cevr";
connectAttr "animCurveTA3050.a" "clipLibrary1.cel[0].cev[566].cevr";
connectAttr "animCurveTA3051.a" "clipLibrary1.cel[0].cev[567].cevr";
connectAttr "animCurveTA3052.a" "clipLibrary1.cel[0].cev[568].cevr";
connectAttr "animCurveTA3053.a" "clipLibrary1.cel[0].cev[569].cevr";
connectAttr "animCurveTU1607.a" "clipLibrary1.cel[0].cev[570].cevr";
connectAttr "animCurveTU1608.a" "clipLibrary1.cel[0].cev[571].cevr";
connectAttr "animCurveTU1609.a" "clipLibrary1.cel[0].cev[572].cevr";
connectAttr "animCurveTA3054.a" "clipLibrary1.cel[0].cev[573].cevr";
connectAttr "animCurveTA3055.a" "clipLibrary1.cel[0].cev[574].cevr";
connectAttr "animCurveTA3056.a" "clipLibrary1.cel[0].cev[575].cevr";
connectAttr "animCurveTA3057.a" "clipLibrary1.cel[0].cev[576].cevr";
connectAttr "animCurveTA3058.a" "clipLibrary1.cel[0].cev[577].cevr";
connectAttr "animCurveTA3059.a" "clipLibrary1.cel[0].cev[578].cevr";
connectAttr "animCurveTU1610.a" "clipLibrary1.cel[0].cev[579].cevr";
connectAttr "animCurveTU1611.a" "clipLibrary1.cel[0].cev[580].cevr";
connectAttr "animCurveTU1612.a" "clipLibrary1.cel[0].cev[581].cevr";
connectAttr "animCurveTA3060.a" "clipLibrary1.cel[0].cev[582].cevr";
connectAttr "animCurveTA3061.a" "clipLibrary1.cel[0].cev[583].cevr";
connectAttr "animCurveTA3062.a" "clipLibrary1.cel[0].cev[584].cevr";
connectAttr "animCurveTA3063.a" "clipLibrary1.cel[0].cev[585].cevr";
connectAttr "animCurveTA3064.a" "clipLibrary1.cel[0].cev[586].cevr";
connectAttr "animCurveTA3065.a" "clipLibrary1.cel[0].cev[587].cevr";
connectAttr "animCurveTU1613.a" "clipLibrary1.cel[0].cev[588].cevr";
connectAttr "animCurveTU1614.a" "clipLibrary1.cel[0].cev[589].cevr";
connectAttr "animCurveTU1615.a" "clipLibrary1.cel[0].cev[590].cevr";
connectAttr "animCurveTA3066.a" "clipLibrary1.cel[0].cev[591].cevr";
connectAttr "animCurveTA3067.a" "clipLibrary1.cel[0].cev[592].cevr";
connectAttr "animCurveTA3068.a" "clipLibrary1.cel[0].cev[593].cevr";
connectAttr "animCurveTA3069.a" "clipLibrary1.cel[0].cev[594].cevr";
connectAttr "animCurveTA3070.a" "clipLibrary1.cel[0].cev[595].cevr";
connectAttr "animCurveTA3071.a" "clipLibrary1.cel[0].cev[596].cevr";
connectAttr "animCurveTU1616.a" "clipLibrary1.cel[0].cev[597].cevr";
connectAttr "animCurveTU1617.a" "clipLibrary1.cel[0].cev[598].cevr";
connectAttr "animCurveTU1618.a" "clipLibrary1.cel[0].cev[599].cevr";
connectAttr "animCurveTA3072.a" "clipLibrary1.cel[0].cev[600].cevr";
connectAttr "animCurveTA3073.a" "clipLibrary1.cel[0].cev[601].cevr";
connectAttr "animCurveTA3074.a" "clipLibrary1.cel[0].cev[602].cevr";
connectAttr "animCurveTA3075.a" "clipLibrary1.cel[0].cev[603].cevr";
connectAttr "animCurveTA3076.a" "clipLibrary1.cel[0].cev[604].cevr";
connectAttr "animCurveTA3077.a" "clipLibrary1.cel[0].cev[605].cevr";
connectAttr "animCurveTU1619.a" "clipLibrary1.cel[0].cev[606].cevr";
connectAttr "animCurveTU1620.a" "clipLibrary1.cel[0].cev[607].cevr";
connectAttr "animCurveTU1621.a" "clipLibrary1.cel[0].cev[608].cevr";
connectAttr "animCurveTA3078.a" "clipLibrary1.cel[0].cev[609].cevr";
connectAttr "animCurveTA3079.a" "clipLibrary1.cel[0].cev[610].cevr";
connectAttr "animCurveTA3080.a" "clipLibrary1.cel[0].cev[611].cevr";
connectAttr "animCurveTA3081.a" "clipLibrary1.cel[0].cev[612].cevr";
connectAttr "animCurveTA3082.a" "clipLibrary1.cel[0].cev[613].cevr";
connectAttr "animCurveTA3083.a" "clipLibrary1.cel[0].cev[614].cevr";
connectAttr "animCurveTU1622.a" "clipLibrary1.cel[0].cev[615].cevr";
connectAttr "animCurveTU1623.a" "clipLibrary1.cel[0].cev[616].cevr";
connectAttr "animCurveTU1624.a" "clipLibrary1.cel[0].cev[617].cevr";
connectAttr "animCurveTA3084.a" "clipLibrary1.cel[0].cev[618].cevr";
connectAttr "animCurveTA3085.a" "clipLibrary1.cel[0].cev[619].cevr";
connectAttr "animCurveTA3086.a" "clipLibrary1.cel[0].cev[620].cevr";
connectAttr "animCurveTA3087.a" "clipLibrary1.cel[0].cev[621].cevr";
connectAttr "animCurveTA3088.a" "clipLibrary1.cel[0].cev[622].cevr";
connectAttr "animCurveTA3089.a" "clipLibrary1.cel[0].cev[623].cevr";
connectAttr "animCurveTU1625.a" "clipLibrary1.cel[0].cev[624].cevr";
connectAttr "animCurveTU1626.a" "clipLibrary1.cel[0].cev[625].cevr";
connectAttr "animCurveTU1627.a" "clipLibrary1.cel[0].cev[626].cevr";
connectAttr "animCurveTA3090.a" "clipLibrary1.cel[0].cev[627].cevr";
connectAttr "animCurveTA3091.a" "clipLibrary1.cel[0].cev[628].cevr";
connectAttr "animCurveTA3092.a" "clipLibrary1.cel[0].cev[629].cevr";
connectAttr "animCurveTA3093.a" "clipLibrary1.cel[0].cev[630].cevr";
connectAttr "animCurveTA3094.a" "clipLibrary1.cel[0].cev[631].cevr";
connectAttr "animCurveTA3095.a" "clipLibrary1.cel[0].cev[632].cevr";
connectAttr "animCurveTU1628.a" "clipLibrary1.cel[0].cev[633].cevr";
connectAttr "animCurveTU1629.a" "clipLibrary1.cel[0].cev[634].cevr";
connectAttr "animCurveTU1630.a" "clipLibrary1.cel[0].cev[635].cevr";
connectAttr "animCurveTA3096.a" "clipLibrary1.cel[0].cev[636].cevr";
connectAttr "animCurveTA3097.a" "clipLibrary1.cel[0].cev[637].cevr";
connectAttr "animCurveTA3098.a" "clipLibrary1.cel[0].cev[638].cevr";
connectAttr "animCurveTU1631.a" "clipLibrary1.cel[0].cev[639].cevr";
connectAttr "animCurveTU1632.a" "clipLibrary1.cel[0].cev[640].cevr";
connectAttr "animCurveTU1633.a" "clipLibrary1.cel[0].cev[641].cevr";
connectAttr "animCurveTA3099.a" "clipLibrary1.cel[0].cev[642].cevr";
connectAttr "animCurveTA3100.a" "clipLibrary1.cel[0].cev[643].cevr";
connectAttr "animCurveTA3101.a" "clipLibrary1.cel[0].cev[644].cevr";
connectAttr "animCurveTL1042.a" "clipLibrary1.cel[0].cev[645].cevr";
connectAttr "animCurveTL1043.a" "clipLibrary1.cel[0].cev[646].cevr";
connectAttr "animCurveTL1044.a" "clipLibrary1.cel[0].cev[647].cevr";
connectAttr "animCurveTU1634.a" "clipLibrary1.cel[0].cev[648].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of attack1.ma
