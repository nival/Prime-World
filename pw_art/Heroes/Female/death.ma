//Maya ASCII 2008 scene
//Name: death.ma
//Last modified: Thu, Dec 17, 2009 12:07:52 PM
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
createNode animClip -n "deathSource2";
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
	setAttr ".se" 70;
	setAttr ".ci" no;
createNode animCurveTA -n "animCurveTA3102";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3103";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3104";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3105";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3106";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -5.2047506862742576 2 0 6 0 10 0 14 0 
		16 0 22 0 46 0 69 0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3107";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3108";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3109";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3110";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3111";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3112";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3113";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3114";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3115";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3116";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3117";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3118";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3119";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3120";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3121";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3122";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3123";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3124";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3125";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3126";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3127";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3128";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3129";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3130";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3131";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3132";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3133";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3134";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3135";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3136";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3137";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3138";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3139";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3140";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1045";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1046";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1047";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3141";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3142";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3143";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1048";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1049";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1050";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3144";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -14.368948490926961 2 0 6 0 10 0 14 0 
		16 0 22 0 46 0 69 0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3145";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3146";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1051";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1052";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1053";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3147";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 7.9832676905363096 2 10.570970128434233 
		6 10.570970128434233 10 10.570970128434233 14 10.570970128434233 16 10.570970128434233 
		22 10.570970128434233 46 10.570970128434233 69 10.570970128434233 70 10.570970128434233;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3148";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0.37974132891678741 6 0.37974132891678741 
		10 0.37974132891678741 14 0.37974132891678741 16 0.37974132891678741 22 0.37974132891678741 
		46 0.37974132891678741 69 0.37974132891678741 70 0.37974132891678741;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3149";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 -0.5034279194551966 6 -0.5034279194551966 
		10 -0.5034279194551966 14 -0.5034279194551966 16 -0.5034279194551966 22 -0.5034279194551966 
		46 -0.5034279194551966 69 -0.5034279194551966 70 -0.5034279194551966;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1054";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 -0.01166853208876018 6 -0.01166853208876018 
		10 -0.01166853208876018 14 -0.01166853208876018 16 -0.01166853208876018 22 -0.01166853208876018 
		46 -0.01166853208876018 69 -0.01166853208876018 70 -0.01166853208876018;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1055";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0.023169871385866233 6 0.023169871385866233 
		10 0.023169871385866233 14 0.023169871385866233 16 0.023169871385866233 22 0.023169871385866233 
		46 0.023169871385866233 69 0.023169871385866233 70 0.023169871385866233;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1056";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 -0.00068555661697501159 6 -0.00068555661697501159 
		10 -0.00068555661697501159 14 -0.00068555661697501159 16 -0.00068555661697501159 
		22 -0.00068555661697501159 46 -0.00068555661697501159 69 -0.00068555661697501159 
		70 -0.00068555661697501159;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3150";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 20.344148217877017 14 17.285180372901383 
		16 15.180039355057028 22 19.107143147119771 46 19.107143147119771 69 19.107143147119771 
		70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3151";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 -16.56440030201961 14 -14.270242569216034 
		16 -12.704988461357361 22 -11.006834754404299 46 -11.006834754404299 69 -11.006834754404299 
		70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3152";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 -13.908029522247043 14 -9.8466297916520187 
		16 -7.9482457483626874 22 -9.2317284779192033 46 -9.2317284779192033 69 -9.2317284779192033 
		70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1057";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1058";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1059";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3153";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 -17.7573829969825 6 -17.7573829969825 
		10 -17.7573829969825 14 -17.7573829969825 16 -17.7573829969825 22 -17.7573829969825 
		46 -17.7573829969825 69 -17.7573829969825 70 -17.7573829969825;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3154";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 3.7146065564843975 6 3.7146065564843975 
		10 3.7146065564843975 14 3.7146065564843975 16 3.7146065564843975 22 3.7146065564843975 
		46 3.7146065564843975 69 3.7146065564843975 70 3.7146065564843975;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3155";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 -4.9827311229478353 6 -4.9827311229478353 
		10 -4.9827311229478353 14 -4.9827311229478353 16 -4.9827311229478353 22 -4.9827311229478353 
		46 -4.9827311229478353 69 -4.9827311229478353 70 -4.9827311229478353;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1060";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1061";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1062";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3156";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3157";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3158";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1063";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1064";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1065";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3159";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3160";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3161";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1066";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1067";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1068";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3162";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3163";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3164";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1069";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1070";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1071";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3165";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 1.5892747039432018 6 1.454322670443229 
		10 5.4240049351664847 14 5.4240049351664847 16 5.4240049351664847 22 5.4240049351664847 
		46 5.4240049351664847 69 5.4240049351664847 70 5.4240049351664847;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3166";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 3.7481930535578547 6 3.5955947332712488 
		10 4.3657667990279379 14 4.3657667990279379 16 4.3657667990279379 22 4.3657667990279379 
		46 4.3657667990279379 69 4.3657667990279379 70 4.3657667990279379;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3167";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 -4.3417055484966731 6 -4.7085759105833205 
		10 -2.8418040581717858 14 -2.8418040581717858 16 -2.8418040581717858 22 -2.8418040581717858 
		46 -2.8418040581717858 69 -2.8418040581717858 70 -2.8418040581717858;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1072";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1073";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1074";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1635";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3168";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 26.076352919613864 6 21.911108529400625 
		10 16.412059457560318 14 13.945642372509258 16 13.582134983355225 22 13.582134983355225 
		46 13.582134983355225 69 13.582134983355225 70 13.582134983355225;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3169";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 8.7019438000585509 6 7.6824652153172046 
		10 5.9350397474479708 14 5.1120638373568115 16 4.9858209747782638 22 4.9858209747782638 
		46 4.9858209747782638 69 4.9858209747782638 70 4.9858209747782638;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3170";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 -12.296212468566218 6 -13.040504215643679 
		10 -23.360813271702039 14 -27.763327405457591 16 -28.383620169474121 22 -28.383620169474121 
		46 -28.383620169474121 69 -28.383620169474121 70 -28.383620169474121;
	setAttr -s 10 ".kit[0:9]"  3 9 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 9 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1075";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.013109125800625065 2 -0.31988171115353214 
		6 -0.63421254666933713 10 -0.2324478376537002 14 0.042249536465850057 16 0.19396976784252729 
		22 0.82022321676250465 46 3.4068332325532644 69 5.4580608843366791 70 5.5655691412063302;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1076";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.075951676950020475 2 0.38390083098263311 
		6 -0.16003760046198942 10 -0.16932292079049938 14 -0.17305912683514513 16 -0.1743667984998134 
		22 -0.1743667984998134 46 -0.1743667984998134 69 -0.1743667984998134 70 -0.1743667984998134;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1077";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.10545061589477858 2 0.07103880492333281 
		6 0.042746262749068231 10 0.0015344037215848302 14 -0.017874931933000646 16 -0.020852285132850625 
		22 -0.020852285132850625 46 -0.020852285132850625 69 -0.020852285132850625 70 -0.020852285132850625;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3171";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3172";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3173";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1078";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1079";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1080";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1636";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1637";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1638";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.30000000000000077 2 -0.50000000000000078 
		6 1.0875000004346167 10 2.3874000033419334 14 0.41358502615640091 16 -0.20000000000000107 
		22 -0.20000000000000107 46 -0.60000000000000098 69 -0.4000000000000008 70 2.6999999999999993;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1639";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.30000000000000077 2 -0.50000000000000078 
		6 -0.30634920743822525 10 -0.072177768336088022 14 2.1233647276086707 16 2.6999999999999993 
		22 -0.18641210017334231 46 -2 69 -2 70 -1.0237452068750406;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1640";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.30000000000000077 2 -0.50000000000000078 
		6 -0.30634920743822525 10 -0.072177768336088022 14 2.1233647276086707 16 2.6999999999999993 
		22 -0.18641210017334231 46 -2 69 -2 70 -1.0237452068750406;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1641";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.30000000000000077 2 -0.50000000000000078 
		6 -0.4124999995653833 10 -0.11259999665806664 14 2.085985346955423 16 2.6999999999999993 
		22 0.19999999999999929 46 -0.70000000000000095 69 0.49999999999999911 70 2.6999999999999993;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1642";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.30000000000000077 2 -0.50000000000000078 
		6 -0.30634920743822525 10 -0.072177768336088022 14 2.1233647276086707 16 2.6999999999999993 
		22 -0.18641210017334231 46 -2 69 -2 70 -1.0237452068750406;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3174";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3175";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3176";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3177";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3178";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3179";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3180";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3181";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 6.8626905690311126 10 6.6769038103816438 
		14 6.6733492898159312 16 6.6721052080469603 22 6.6663157794015522 46 6.5874718389630305 
		69 6.5319569540439009 70 6.5318198144908566;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3182";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 -18.462562422796157 10 -17.962743943838174 
		14 -17.953181286283584 16 -17.949834357293685 22 -17.934259169993659 46 -17.72214685027868 
		69 -17.572796234956645 70 -17.572427291083986;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3183";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 -20.808745214026473 10 -20.245410868333039 
		14 -20.234633009011493 16 -20.230860759549838 22 -20.21330631125258 46 -19.97423921832323 
		69 -19.805909450961174 70 -19.805493622501949;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3184";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3185";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3186";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3187";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3188";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3189";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1643";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 2 1 6 1 10 1 14 1 16 1 22 1 46 1 69 
		1 70 1;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 9;
	setAttr -s 10 ".kot[0:9]"  3 5 5 5 5 5 5 5 
		5 5;
createNode animCurveTU -n "animCurveTU1644";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 9;
	setAttr -s 10 ".kot[0:9]"  3 5 5 5 5 5 5 5 
		5 5;
createNode animCurveTU -n "animCurveTU1645";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 10 2 10 6 10 10 10 14 10 16 10 22 10 
		46 10 69 10 70 10;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1081";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1082";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1083";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1646";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 10 2 10 6 10 10 10 14 10 16 10 22 10 
		46 10 69 10 70 10;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1084";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.22464769340943472 2 0.17230107799162178 
		6 0.17230107799162178 10 0.019750815870569576 14 0.12644714969679921 16 0.1642725643803504 
		22 0.1642725643803504 46 0.1642725643803504 69 0.1642725643803504 70 0.1642725643803504;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1085";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.19416530018464082 2 1.1537347923379162 
		6 1.1537347923379162 10 1.2879920049209204 14 1.2312565803177316 16 1.2081351667081679 
		22 1.2081351667081679 46 1.2081351667081679 69 1.2081351667081679 70 1.2081351667081679;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1086";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.47504801816095116 2 -0.38269535479207056 
		6 -0.38269535479207056 10 -0.48613013949478795 14 -0.32807457493731962 16 -0.27897817542455655 
		22 -0.27897817542455655 46 -0.27897817542455655 69 -0.27897817542455655 70 -0.27897817542455655;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3190";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3191";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3192";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1087";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 5.5511151231257827e-017;
createNode animCurveTL -n "animCurveTL1088";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 6.9388939039072284e-018;
createNode animCurveTL -n "animCurveTL1089";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 2.7755575615628914e-017;
createNode animCurveTU -n "animCurveTU1647";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 2 1 6 1 10 1 14 1 16 1 26 1 46 1 69 
		1 70 1;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1648";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 2 1 6 1 10 1 14 1 16 1 26 1 46 1 69 
		1 70 1;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1649";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 26 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1650";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 26 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1651";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 25 2 25 6 25 10 25 14 25 16 25 26 25 
		46 25 69 25 70 25;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1652";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 26 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1653";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 26 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1654";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 26 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3193";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 20.128361339199554 2 57.403961689777049 
		6 57.403961689777049 10 37.115280073447288 14 9.4994967328741406 16 3.092653374234267 
		26 3.092653374234267 46 3.092653374234267 69 3.092653374234267 70 3.092653374234267;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3194";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 -37.762025338625733 14 5.7417862600081255 
		16 19.78124089700102 26 19.78124089700102 46 19.78124089700102 69 19.78124089700102 
		70 19.78124089700102;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3195";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 35.989394202339128 14 17.905766970014891 
		16 9.8310545177753053 26 20.581635135789874 46 19.526966262645129 69 14.999648389612876 
		70 9.8310545177753053;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1090";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 0 6 0 10 -0.00012717395779471286 
		14 0.022512784588554029 16 0.12148843107095081 26 1.2138949659758052 36 2.2880686665401915 
		46 3.3600549630377885 69 5.3806145483830772 70 5.4930878044347535;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 10 10 10 10 
		10 10 10;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 10 10 10 10 
		10 10 10;
createNode animCurveTL -n "animCurveTL1091";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0.19707483477738794 2 0.95112182706391835 
		6 0.95112182706391835 10 0.26341601079142829 14 -0.19088600367228509 16 -0.29158876245756365 
		26 0.046619660320376205 36 -0.11952075465514936 46 -0.075239514135869878 69 -0.075239514135869878 
		70 -0.29158876245756365;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 10 10 10 10 
		10 10 10;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 10 10 10 10 
		10 10 10;
createNode animCurveTL -n "animCurveTL1092";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0.18298804813669703 2 0 6 0 10 -0.027548949747661731 
		14 -0.072034345723852394 16 -0.082645500206152495 26 -0.072798383854180609 36 -0.083737907597799477 
		46 -0.083655466070400045 69 -0.083437808057796811 70 -0.082645500206152495;
	setAttr -s 11 ".kit[0:10]"  3 10 10 9 10 10 10 10 
		10 10 10;
	setAttr -s 11 ".kot[0:10]"  3 10 10 9 10 10 10 10 
		10 10 10;
createNode animCurveTU -n "animCurveTU1655";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 9;
	setAttr -s 10 ".kot[0:9]"  3 5 5 5 5 5 5 5 
		5 5;
createNode animCurveTU -n "animCurveTU1656";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 2 1 6 1 10 1 14 1 16 1 22 1 46 1 69 
		1 70 1;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 9;
	setAttr -s 10 ".kot[0:9]"  3 5 5 5 5 5 5 5 
		5 5;
createNode animCurveTU -n "animCurveTU1657";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 10 2 10 6 10 10 10 14 10 16 10 22 10 
		46 10 69 10 70 10;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1093";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1094";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1095";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1658";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 6 0 10 0 14 0 16 0 46 0 69 0 70 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL1096";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 -0.62414738894456112 6 -1.016175695713023 
		10 -0.56389418610160447 14 -0.46072252685200693 16 -0.35010327946001574 46 2.8703110407026928 
		69 4.9345562444675366 70 4.8102821597474668;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL1097";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0.17076974518355748 6 -0.41220453804342544 
		10 -0.094319336707084589 14 -0.12556358206093807 16 -0.15210503027130384 46 -0.15210503027130384 
		69 -0.15210503027130384 70 -0.092742563631971198;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL1098";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 -0.15178229722638564 6 -0.19601680759513004 
		10 -0.3153628463666317 14 -0.66465755738389776 16 -0.75346384701322644 46 -0.75346384701322644 
		69 -0.75346384701322644 70 -0.38923659943325145;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA3196";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3197";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3198";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1099";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1100";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.7347234759768071e-018;
createNode animCurveTL -n "animCurveTL1101";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1659";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 6 1 10 1 14 1 26 1 46 1 69 1 70 
		1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU1660";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 6 1 10 1 14 1 26 1 46 1 69 1 70 
		1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU1661";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 6 0 10 0 14 0 26 0 46 0 69 0 70 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU1662";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 6 0 10 0 14 0 26 0 46 0 69 0 70 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU1663";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 6 0 10 0 14 0 26 0 46 0 69 0 70 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA3199";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -73.688065524612256 2 -47.239840394839426 
		6 -56.697573117336994 10 -54.645092619064584 14 -36.445496822386339 26 76.909777587886424 
		46 58.436097523344664 69 48.093234159251715 70 -84.563571496365981;
	setAttr -s 9 ".kit[0:8]"  3 9 10 10 10 10 10 3 
		10;
	setAttr -s 9 ".kot[0:8]"  3 9 10 10 10 10 10 3 
		10;
createNode animCurveTA -n "animCurveTA3200";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 10.899517849852639 2 -12.135150632320537 
		6 -12.093758872721212 10 -12.039949595771771 14 -11.967514002118241 26 -11.57636193627607 
		46 -2.8754238119709927 69 -2.3120814014302931 70 4.9223055802886719;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 9 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 9 10 
		10;
createNode animCurveTA -n "animCurveTA3201";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 83.974725223152646 2 -27.286019415650365 
		6 -32.334005775819406 10 -37.078347089832036 14 -41.788340882576925 26 -54.647345543646047 
		46 -63.258204154512676 69 -74.091823656412927 70 85.296713421282902;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 3 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 3 
		10;
createNode animCurveTL -n "animCurveTL1102";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.3820708588750783 2 -0.25808339214532472 
		6 -0.086210074094812267 10 0.078154274755205672 14 0.24523776097978725 26 0.90282177015185772 
		46 3.2128550071680499 69 5.3876295380541857 70 4.8044707355122895;
	setAttr -s 9 ".kit[0:8]"  3 9 10 10 10 1 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 9 10 10 10 1 10 10 
		10;
	setAttr -s 9 ".kix[5:8]"  0.32384636998176575 0.30442792177200317 
		0.44909524917602539 0.05706675723195076;
	setAttr -s 9 ".kiy[5:8]"  0.94610965251922607 0.95253539085388184 
		0.89348393678665161 -0.99837034940719604;
	setAttr -s 9 ".kox[5:8]"  0.32384645938873291 0.30442792177200317 
		0.44909524917602539 0.057066760957241058;
	setAttr -s 9 ".koy[5:8]"  0.94610965251922607 0.95253539085388184 
		0.89348393678665161 -0.99837040901184082;
createNode animCurveTL -n "animCurveTL1103";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.042044109170142896 2 -0.15648605724814885 
		6 -0.12939830272972747 10 -0.10359116842499277 14 -0.068850781639712491 26 0.11874723991051266 
		46 0.12358226436373781 69 0.091959526847378986 70 0.35603712811582339;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL1104";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.54001242177491338 2 -0.38066518014021622 
		6 -0.39019433716627921 10 -0.39451900214370444 14 -0.40034066882929781 26 -0.43177765768875725 
		46 -0.43325625801543277 69 -0.28693530920659049 70 -0.8469146317587376;
	setAttr -s 9 ".kit[0:8]"  3 9 10 10 10 10 10 3 
		10;
	setAttr -s 9 ".kot[0:8]"  3 9 10 10 10 10 10 3 
		10;
createNode animCurveTU -n "animCurveTU1664";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1665";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1666";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1.4000000000000004 2 -0.49999999999999978 
		6 1.2312499945700586 10 2.7875000039753539 14 0.90351836461715163 16 0.29999999999999982 
		22 0.29999999999999982 46 -0.10000000000000009 69 0.10000000000000009 70 3.2;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1667";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1.4000000000000004 2 -0.49999999999999978 
		6 -0.14955358168934318 10 0.33289000098805577 14 2.6079785550149133 16 3.2 22 0.30002892584078378 
		46 -2 69 -2 70 -0.71970357814970143;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1668";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1.4000000000000004 2 -0.49999999999999978 
		6 -0.14955358168934318 10 0.33289000098805577 14 2.6079785550149133 16 3.2 22 0.30002892584078378 
		46 -2 69 -2 70 -0.71970357814970143;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1669";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1.4000000000000004 2 -0.49999999999999978 
		6 -0.26875000542994143 10 0.28750000397535391 14 2.568518695246071 16 3.2 22 0.70000000000000018 
		46 -0.20000000000000007 69 1 70 3.2;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1670";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1.4000000000000004 2 -0.49999999999999978 
		6 -0.14955358168934318 10 0.33289000098805577 14 2.6079785550149133 16 3.2 22 0.30002892584078378 
		46 -2 69 -2 70 -0.71970357814970143;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1671";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1672";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1673";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA3202";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3203";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3204";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1105";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1106";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1107";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1674";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1675";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 10;
createNode animCurveTU -n "animCurveTU1676";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3205";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3206";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3207";
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
createNode animCurveTU -n "animCurveTU1677";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1678";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1679";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA3208";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3209";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3210";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1111";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1112";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1113";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1680";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1681";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3211";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3212";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3213";
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
createNode animCurveTU -n "animCurveTU1682";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1683";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1684";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA3214";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3215";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3216";
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
createNode animCurveTU -n "animCurveTU1685";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1686";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3217";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3218";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3219";
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
createNode animCurveTA -n "animCurveTA3220";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3221";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 9.9392333795734874e-017;
createNode animCurveTA -n "animCurveTA3222";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3223";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3224";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3225";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 9.9392333795734924e-017;
createNode animCurveTA -n "animCurveTA3226";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3227";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3228";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3229";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 -19.563598765460075 
		16 0 22 0 46 -15.498319143891267 69 0 70 -26.410855972056861;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3230";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3231";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 9.9392333795734899e-017;
createNode animCurveTA -n "animCurveTA3232";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3233";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3234";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3235";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1687";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 2 1 6 1 10 1 14 1 16 1 22 1 46 1 69 
		1 70 1;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 9;
	setAttr -s 10 ".kot[0:9]"  3 5 5 5 5 5 5 5 
		5 5;
createNode animCurveTU -n "animCurveTU1688";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 9;
	setAttr -s 10 ".kot[0:9]"  3 5 5 5 5 5 5 5 
		5 5;
createNode animCurveTU -n "animCurveTU1689";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 10 2 10 6 10 10 10 14 10 16 10 22 10 
		46 10 69 10 70 10;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
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
createNode animCurveTU -n "animCurveTU1690";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 10 2 10 6 10 10 10 14 10 16 10 22 10 
		46 10 69 10 70 10;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1126";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.067033432403714843 2 -0.21658930703824822 
		6 -0.21658930703824822 10 -0.10059079017549179 14 -0.04595956966298477 16 -0.03757925015127847 
		22 -0.03757925015127847 46 -0.03757925015127847 69 -0.03757925015127847 70 -0.03757925015127847;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1127";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.16933803890603863 2 0.39582367765690041 
		6 0.39582367765690041 10 0.45414070226929476 14 0.47760617380435688 16 0.4858190860093608 
		22 0.4858190860093608 46 0.4858190860093608 69 0.4858190860093608 70 0.4858190860093608;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1128";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.57509011135883603 2 0.31511943357368405 
		6 0.31511943357368405 10 0.11929644078085741 14 0.027070701059944607 16 0.012923457041544226 
		22 0.012923457041544226 46 0.012923457041544226 69 0.012923457041544226 70 0.012923457041544226;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3236";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3237";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3238";
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
createNode animCurveTU -n "animCurveTU1691";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 2 1 6 1 10 1 14 1 16 1 26 1 46 1 69 
		1 70 1;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1692";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 2 1 6 1 10 1 14 1 16 1 26 1 46 1 69 
		1 70 1;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1693";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 26 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1694";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 26 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1695";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 25 2 25 6 25 10 25 14 25 16 25 26 25 
		46 25 69 25 70 25;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1696";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 26 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1697";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 26 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1698";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 26 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3239";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -16.972634475184972 2 14.467361541149682 
		6 14.467361541149682 10 14.467361541149682 14 16.521840559226558 16 17.240907967579119 
		26 17.240907967579119 46 17.240907967579119 69 17.240907967579119 70 17.240907967579119;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3240";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 -6.6044435321448782 
		16 -8.9159979712433497 26 -8.9159979712433497 46 -8.9159979712433497 69 -8.9159979712433497 
		70 -8.9159979712433497;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3241";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 2.2081492559571694 
		16 28.407322027055862 26 37.190578820633235 46 34.108141221954433 69 24.648968359481497 
		70 5.7702947674064724;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1132";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 0 6 0 10 0 14 0.020397893740337233 
		16 0.2735145738242637 26 1.2937270078532102 36 2.3590084715251907 46 3.4266692549646569 
		69 5.4987399237635177 70 5.4961660657946965;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 10 10 10 10 
		10 2 10;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 10 10 10 10 
		10 2 10;
createNode animCurveTL -n "animCurveTL1133";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 0 6 0 10 0 14 0 16 -0.13023608125763175 
		26 -0.27744192703173753 36 -0.13234569701056975 46 -0.19654326524762078 69 -0.10070528407199153 
		70 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 10 10 10 10 
		10 10 10;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 10 10 10 10 
		10 10 10;
createNode animCurveTL -n "animCurveTL1134";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -0.057044533275492443 2 0.10311723350153656 
		6 0.10311723350153656 10 0.10311723350153656 14 0.030099870772867812 16 -0.0063687487971409995 
		26 -0.042383446598743935 36 -0.030726105166748084 46 -0.028887910297437248 69 -0.024034799800185642 
		70 -0.0063687487971409995;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 10 9 10 9 
		10 10 10;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 10 9 10 9 
		10 10 10;
createNode animCurveTU -n "animCurveTU1699";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 9;
	setAttr -s 10 ".kot[0:9]"  3 5 5 5 5 5 5 5 
		5 5;
createNode animCurveTU -n "animCurveTU1700";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 2 1 6 1 10 1 14 1 16 1 22 1 46 1 69 
		1 70 1;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 9;
	setAttr -s 10 ".kot[0:9]"  3 5 5 5 5 5 5 5 
		5 5;
createNode animCurveTU -n "animCurveTU1701";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 10 2 10 6 10 10 10 14 10 16 10 22 10 
		46 10 69 10 70 10;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1135";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1136";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1137";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1702";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 6 0 10 0 14 0 16 0 46 0 69 0 70 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL1138";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.2165701385911305 2 -0.46996092240846687 
		6 -1.0144828684389577 10 -0.53353356139677877 14 -0.42839869057176611 16 -0.31988567197467566 
		46 2.8682157515327309 69 4.9324609552975751 70 5.0123327639200026;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL1139";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.053478567476916261 2 0.062910510937959074 
		6 -0.43860828531739782 10 -0.11522897149820654 14 -0.10321948161461449 16 -0.099016161604895236 
		46 -0.77920813867010752 69 -0.77920813867010752 70 -0.098873785512882062;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL1140";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.5222747364155893 2 0.25281248117441679 
		6 0.21665591463339112 10 0.24059200406141512 14 0.15367794947584948 16 0.12325804086137399 
		46 0.13307874444091922 69 0.13307874444091922 70 0.21971494490597221;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA3242";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3243";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3244";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1141";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -4.4408920985006262e-016;
createNode animCurveTL -n "animCurveTL1142";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.7347234759768071e-018;
createNode animCurveTL -n "animCurveTL1143";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1703";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 2 1 6 1 10 1 14 1 46 1 69 1 70 1;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "animCurveTU1704";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 2 1 6 1 10 1 14 1 46 1 69 1 70 1;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "animCurveTU1705";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 6 0 10 0 14 0 46 0 69 0 70 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "animCurveTU1706";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 6 0 10 0 14 0 46 0 69 0 70 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "animCurveTU1707";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 6 0 10 0 14 0 46 0 69 0 70 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA3245";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 72.410849029571423 2 76.755578594910872 
		6 54.259044687164391 10 6.133061964745786 14 -43.525169638883803 16 -60.185378121940701 
		26 -75.820220758023993 46 -75.365932098370365 69 -62.878230730786335 70 84.101714325993385;
	setAttr -s 10 ".kit[0:9]"  3 1 10 10 10 10 10 10 
		1 10;
	setAttr -s 10 ".kot[0:9]"  3 1 10 10 10 10 10 10 
		1 10;
	setAttr -s 10 ".kix[1:9]"  0.99062347412109375 0.21145366132259369 
		0.15437775850296021 0.17026682198047638 0.57873433828353882 1 1 0.79248595237731934 
		0.012992903590202332;
	setAttr -s 10 ".kiy[1:9]"  -0.13662049174308777 -0.97738802433013916 
		-0.98801189661026001 -0.98539799451828003 -0.81551617383956909 0 0 0.6098901629447937 
		0.99991559982299805;
	setAttr -s 10 ".kox[1:9]"  0.99062347412109375 0.21145366132259369 
		0.15437775850296021 0.17026682198047638 0.57873433828353882 1 1 0.79248601198196411 
		0.012992903590202332;
	setAttr -s 10 ".koy[1:9]"  -0.13662043213844299 -0.97738802433013916 
		-0.98801189661026001 -0.98539799451828003 -0.81551617383956909 0 0 0.6098901629447937 
		0.99991559982299805;
createNode animCurveTA -n "animCurveTA3246";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -29.916944388919955 2 -8.8611436679442601 
		6 -14.801233004329694 10 -15.588740949790269 14 -16.662615759338955 16 -17.038471813064969 
		26 30.160788988335611 46 17.82740689820826 69 17.495124408120891 70 -1.5455319663275853;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3247";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 72.717171353838793 2 -20.25394964658533 
		6 -33.890387324579528 10 -49.548790033828503 14 -65.150615843141694 16 -71.88735977218667 
		26 -96.961114658832358 46 -101.61479534389095 69 -94.772410154096264 70 59.166699008704619;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		3 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		3 10;
createNode animCurveTL -n "animCurveTL1144";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.38771781685288609 2 -0.20675282998075994 
		6 -0.2463446856756413 10 -0.26619344320330779 14 -0.20886097830380113 16 -0.099271456010096126 
		26 0.88046035841156778 46 3.1636978257061492 69 5.3116389327824569 70 4.8214951424490158;
	setAttr -s 10 ".kit[0:9]"  3 3 10 10 10 1 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 3 10 10 10 1 10 10 
		10 10;
	setAttr -s 10 ".kix[5:9]"  0.4079425036907196 0.29301747679710388 
		0.30776521563529968 0.43460983037948608 0.067850463092327118;
	setAttr -s 10 ".kiy[5:9]"  0.91300761699676514 0.95610707998275757 
		0.95146232843399048 0.90061885118484497 -0.9976954460144043;
	setAttr -s 10 ".kox[5:9]"  0.40794247388839722 0.29301747679710388 
		0.30776521563529968 0.43460983037948608 0.067850470542907715;
	setAttr -s 10 ".koy[5:9]"  0.91300761699676514 0.95610707998275757 
		0.95146232843399048 0.90061885118484497 -0.99769550561904907;
createNode animCurveTL -n "animCurveTL1145";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.01108452333757072 2 0.056585727233924132 
		6 -0.014143206330331934 10 -0.081172663676809947 14 -0.13801917173949871 16 -0.14406160065500181 
		26 -0.00038947031781499941 46 -0.15123606663139488 69 -0.18355590058239046 70 0.20474085073341916;
	setAttr -s 10 ".kit[0:9]"  3 9 10 10 10 10 10 9 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 9 10 10 10 10 10 9 
		10 10;
createNode animCurveTL -n "animCurveTL1146";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.736599410145234 2 0.52049831158035387 
		6 0.43825905354455436 10 0.3639610794366796 14 0.29338506473320625 16 0.26324568975313434 
		26 0.15144673005705736 46 0.17893934267166722 69 0.11682175997537514 70 0.60964245050294064;
	setAttr -s 10 ".kit[0:9]"  3 9 10 10 10 10 10 10 
		3 10;
	setAttr -s 10 ".kot[0:9]"  3 9 10 10 10 10 10 10 
		3 10;
createNode animCurveTA -n "animCurveTA3248";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 3.6082301187437729 
		16 4.8711102247929565 22 6.8384923921758327 46 5.2902919838648579 69 6.6589010150200592 
		70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3249";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		-0.70492032948002292 70 -0.71000175418541434;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3250";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		-0.082294391060953792 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3251";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 7.0568556994971777e-015;
createNode animCurveTA -n "animCurveTA3252";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.9586709197597583e-031;
createNode animCurveTA -n "animCurveTA3253";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -3.1805546814635168e-015;
createNode animCurveTU -n "animCurveTU1708";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999978;
createNode animCurveTU -n "animCurveTU1709";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999967;
createNode animCurveTU -n "animCurveTU1710";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999967;
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
createNode animCurveTA -n "animCurveTA3257";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -9.1440947092076214e-015;
createNode animCurveTA -n "animCurveTA3258";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.2722218725854075e-014;
createNode animCurveTA -n "animCurveTA3259";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 7.5538173684758548e-014;
createNode animCurveTU -n "animCurveTU1711";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999978;
createNode animCurveTU -n "animCurveTU1712";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1713";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
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
createNode animCurveTU -n "animCurveTU1714";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU1715";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1716";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
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
createNode animCurveTA -n "animCurveTA3269";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -4.3255543667903831e-013;
createNode animCurveTA -n "animCurveTA3270";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.2722218725854056e-014;
createNode animCurveTA -n "animCurveTA3271";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 3.1805546814635649e-015;
createNode animCurveTU -n "animCurveTU1717";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU1718";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU1719";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTA -n "animCurveTA3272";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3273";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3274";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1720";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTU -n "animCurveTU1721";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1722";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA3275";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -9.5416640443905503e-015;
createNode animCurveTA -n "animCurveTA3276";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.1131941385122309e-014;
createNode animCurveTA -n "animCurveTA3277";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 6.3611093629270327e-015;
createNode animCurveTL -n "animCurveTL1147";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1148";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 4.4408920985006262e-016;
createNode animCurveTL -n "animCurveTL1149";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.1102230246251565e-016;
createNode animCurveTU -n "animCurveTU1723";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1.0000000000000002 2 1.0000000000000002 
		6 1.0000000000000002 10 1.0000000000000002 14 1.0000000000000002 16 1.0000000000000002 
		22 1.0000000000000002 46 1.0000000000000002 69 1.0000000000000002 70 1.0000000000000002;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1724";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 2 1 6 1 10 1 14 1 16 1 22 1 46 1 69 
		1 70 1;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1725";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 2 1 6 1 10 1 14 1 16 1 22 1 46 1 69 
		1 70 1;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3278";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 1.2648605762024898 14 1.7738122938865519 
		16 1.9519453336458172 22 1.9519453336458172 46 1.9519453336458172 69 1.9519453336458172 
		70 1.9519453336458172;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3279";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 -10.901212983919882 14 -16.035300775408327 
		16 -16.822859543086238 22 -16.822859543086238 46 -16.822859543086238 69 -16.822859543086238 
		70 -16.822859543086238;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3280";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 3.9653827865815825 14 5.560964480308451 
		16 6.1194178805271342 22 6.1194178805271342 46 6.1194178805271342 69 6.1194178805271342 
		70 6.1194178805271342;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1150";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1.3877787807814457e-017 2 0 6 0 10 0 
		14 0 16 0 22 0 46 0 69 0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1151";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1152";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -1.1102230246251565e-016 2 0 6 0 10 0 
		14 0 16 0 22 0 46 0 69 0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3281";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 6.3611093629270335e-015;
createNode animCurveTA -n "animCurveTA3282";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.2722218725854064e-014;
createNode animCurveTA -n "animCurveTA3283";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.2722218725854064e-014;
createNode animCurveTU -n "animCurveTU1726";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU1727";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1728";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999978;
createNode animCurveTA -n "animCurveTA3284";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
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
	setAttr ".ktv[0]"  0 -9.5416640443905519e-015;
createNode animCurveTA -n "animCurveTA3288";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -6.3611093629270312e-015;
createNode animCurveTA -n "animCurveTA3289";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -2.5444437451708134e-014;
createNode animCurveTU -n "animCurveTU1729";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999967;
createNode animCurveTU -n "animCurveTU1730";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999956;
createNode animCurveTU -n "animCurveTU1731";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999956;
createNode animCurveTA -n "animCurveTA3290";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
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
	setAttr ".ktv[0]"  0 3.1805546814635152e-015;
createNode animCurveTA -n "animCurveTA3294";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -9.5416640443905487e-015;
createNode animCurveTA -n "animCurveTA3295";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.2722218725854064e-014;
createNode animCurveTU -n "animCurveTU1732";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999978;
createNode animCurveTU -n "animCurveTU1733";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU1734";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999978;
createNode animCurveTA -n "animCurveTA3296";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3297";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3298";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3299";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 3.4986101496098681e-014;
createNode animCurveTA -n "animCurveTA3300";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -6.3611093629270335e-015;
createNode animCurveTA -n "animCurveTA3301";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.9421187711420696e-030;
createNode animCurveTU -n "animCurveTU1735";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 2 1 6 1 10 1 14 1 16 1 22 1 46 1 69 
		1 70 1;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1736";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.99999999999999989 2 0.99999999999999989 
		6 0.99999999999999989 10 0.99999999999999989 14 0.99999999999999989 16 0.99999999999999989 
		22 0.99999999999999989 46 0.99999999999999989 69 0.99999999999999989 70 0.99999999999999989;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1737";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1.0000000000000002 2 1.0000000000000002 
		6 1.0000000000000002 10 1.0000000000000002 14 1.0000000000000002 16 1.0000000000000002 
		22 1.0000000000000002 46 1.0000000000000002 69 1.0000000000000002 70 1.0000000000000002;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3302";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -6.5315753133350283 2 -6.5315753133350283 
		6 -6.5315753133350283 10 -6.5315753133350283 14 -6.5315753133350283 16 -6.5315753133350283 
		22 -6.5315753133350283 46 -6.5315753133350283 69 -6.5315753133350283 70 -6.5315753133350283;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3303";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.50791434021845472 2 -0.50791434021845472 
		6 -0.50791434021845472 10 -0.50791434021845472 14 -0.50791434021845472 16 -0.50791434021845472 
		22 -0.50791434021845472 46 -0.50791434021845472 69 -0.50791434021845472 70 -0.50791434021845472;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3304";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 15.371706900000456 2 15.371706900000456 
		6 15.371706900000456 10 15.371706900000456 14 15.371706900000456 16 15.371706900000456 
		22 15.371706900000456 46 15.371706900000456 69 15.371706900000456 70 15.371706900000456;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3305";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -3.1805546814635183e-015;
createNode animCurveTA -n "animCurveTA3306";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.2722218725854067e-014;
createNode animCurveTA -n "animCurveTA3307";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.2722218725854067e-014;
createNode animCurveTU -n "animCurveTU1738";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.99999999999999978 2 0.99999999999999978 
		6 0.99999999999999978 10 0.99999999999999978 14 0.99999999999999978 16 0.99999999999999978 
		22 0.99999999999999978 46 0.99999999999999978 69 0.99999999999999978 70 0.99999999999999978;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1739";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.99999999999999978 2 0.99999999999999978 
		6 0.99999999999999978 10 0.99999999999999978 14 0.99999999999999978 16 0.99999999999999978 
		22 0.99999999999999978 46 0.99999999999999978 69 0.99999999999999978 70 0.99999999999999978;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1740";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.99999999999999956 2 0.99999999999999956 
		6 0.99999999999999956 10 0.99999999999999956 14 0.99999999999999956 16 0.99999999999999956 
		22 0.99999999999999956 46 0.99999999999999956 69 0.99999999999999956 70 0.99999999999999956;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3308";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3309";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3310";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3311";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -6.3611093629270335e-015;
createNode animCurveTA -n "animCurveTA3312";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 6.3611093629270335e-015;
createNode animCurveTA -n "animCurveTA3313";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 3.5311250384401278e-031;
createNode animCurveTU -n "animCurveTU1741";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.99999999999999978 2 0.99999999999999978 
		6 0.99999999999999978 10 0.99999999999999978 14 0.99999999999999978 16 0.99999999999999978 
		22 0.99999999999999978 46 0.99999999999999978 69 0.99999999999999978 70 0.99999999999999978;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1742";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 2 1 6 1 10 1 14 1 16 1 22 1 46 1 69 
		1 70 1;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1743";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 2 1 6 1 10 1 14 1 16 1 22 1 46 1 69 
		1 70 1;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3314";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3315";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3316";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3317";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 3.1805546814635176e-015;
createNode animCurveTA -n "animCurveTA3318";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -4.7708320221952759e-015;
createNode animCurveTA -n "animCurveTA3319";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 9.5416640443905519e-015;
createNode animCurveTU -n "animCurveTU1744";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.99999999999999967 2 0.99999999999999967 
		6 0.99999999999999967 10 0.99999999999999967 14 0.99999999999999967 16 0.99999999999999967 
		22 0.99999999999999967 46 0.99999999999999967 69 0.99999999999999967 70 0.99999999999999967;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1745";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 2 1 6 1 10 1 14 1 16 1 22 1 46 1 69 
		1 70 1;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1746";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 2 1 6 1 10 1 14 1 16 1 22 1 46 1 69 
		1 70 1;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3320";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -10.006950332467882 2 -10.006950332467882 
		6 -10.006950332467882 10 -10.006950332467882 14 -10.006950332467882 16 -10.006950332467882 
		22 -10.006950332467882 46 -10.006950332467882 69 -10.006950332467882 70 -10.006950332467882;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3321";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -12.409127898568453 2 -12.409127898568453 
		6 -12.409127898568453 10 -12.409127898568453 14 -12.409127898568453 16 -12.409127898568453 
		22 -12.409127898568453 46 -12.409127898568453 69 -12.409127898568453 70 -12.409127898568453;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3322";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 8.6298909566225337 2 8.6298909566225337 
		6 8.6298909566225337 10 8.6298909566225337 14 8.6298909566225337 16 8.6298909566225337 
		22 8.6298909566225337 46 8.6298909566225337 69 8.6298909566225337 70 8.6298909566225337;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3323";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -2.8624992133171654e-014;
createNode animCurveTA -n "animCurveTA3324";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 8.7465253740246656e-015;
createNode animCurveTA -n "animCurveTA3325";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 9.5416640443905519e-015;
createNode animCurveTU -n "animCurveTU1747";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.99999999999999989 2 0.99999999999999989 
		6 0.99999999999999989 10 0.99999999999999989 14 0.99999999999999989 16 0.99999999999999989 
		22 0.99999999999999989 46 0.99999999999999989 69 0.99999999999999989 70 0.99999999999999989;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1748";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 2 1 6 1 10 1 14 1 16 1 22 1 46 1 69 
		1 70 1;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1749";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 2 1 6 1 10 1 14 1 16 1 22 1 46 1 69 
		1 70 1;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3326";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 20.33693740949867 2 11.182989207208745 
		6 11.182989207208745 10 11.182989207208745 14 11.182989207208745 16 11.182989207208745 
		22 11.182989207208745 46 11.182989207208745 69 11.182989207208745 70 11.182989207208745;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3327";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -14.826892265970072 2 -3.9841891407637053 
		6 -3.9841891407637053 10 -3.9841891407637053 14 -3.9841891407637053 16 -3.9841891407637053 
		22 -3.9841891407637053 46 -3.9841891407637053 69 -3.9841891407637053 70 -3.9841891407637053;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3328";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 48.641881730594498 2 24.575190458574639 
		6 24.575190458574639 10 24.575190458574639 14 24.575190458574639 16 24.575190458574639 
		22 24.575190458574639 46 24.575190458574639 69 24.575190458574639 70 24.575190458574639;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3329";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -3.144908237360738e-030;
createNode animCurveTA -n "animCurveTA3330";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 3.7769086842379261e-014;
createNode animCurveTA -n "animCurveTA3331";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 9.5416640443905503e-015;
createNode animCurveTU -n "animCurveTU1750";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.99999999999999978 2 0.99999999999999978 
		6 0.99999999999999978 10 0.99999999999999978 14 0.99999999999999978 16 0.99999999999999978 
		22 0.99999999999999978 46 0.99999999999999978 69 0.99999999999999978 70 0.99999999999999978;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1751";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.99999999999999933 2 0.99999999999999933 
		6 0.99999999999999933 10 0.99999999999999933 14 0.99999999999999933 16 0.99999999999999933 
		22 0.99999999999999933 46 0.99999999999999933 69 0.99999999999999933 70 0.99999999999999933;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1752";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.99999999999999967 2 0.99999999999999967 
		6 0.99999999999999967 10 0.99999999999999967 14 0.99999999999999967 16 0.99999999999999967 
		22 0.99999999999999967 46 0.99999999999999967 69 0.99999999999999967 70 0.99999999999999967;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3332";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3333";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3334";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
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
createNode animCurveTU -n "animCurveTU1753";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTU -n "animCurveTU1754";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000004;
createNode animCurveTU -n "animCurveTU1755";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000004;
createNode animCurveTA -n "animCurveTA3338";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
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
createNode animCurveTU -n "animCurveTU1756";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999978;
createNode animCurveTU -n "animCurveTU1757";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1758";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999978;
createNode animCurveTA -n "animCurveTA3344";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
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
createNode animCurveTU -n "animCurveTU1759";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU1760";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1761";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTA -n "animCurveTA3350";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3351";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3352";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3353";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3354";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3355";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1762";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999978;
createNode animCurveTU -n "animCurveTU1763";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTU -n "animCurveTU1764";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA3356";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3357";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3358";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3359";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3360";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3361";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 4.8525382364188918e-030;
createNode animCurveTU -n "animCurveTU1765";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999967 2 0.99999999999999967 
		6 0.99999999999999967 10 0.99999999999999967 14 0.99999999999999967 16 0.99999999999999967 
		46 0.99999999999999967 69 0.99999999999999967 70 0.99999999999999967;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU1766";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999944 2 0.99999999999999944 
		6 0.99999999999999944 10 0.99999999999999944 14 0.99999999999999944 16 0.99999999999999944 
		46 0.99999999999999944 69 0.99999999999999944 70 0.99999999999999944;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU1767";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999989 2 0.99999999999999989 
		6 0.99999999999999989 10 0.99999999999999989 14 0.99999999999999989 16 0.99999999999999989 
		46 0.99999999999999989 69 0.99999999999999989 70 0.99999999999999989;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA3362";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 2.9369089577886687 6 -0.43544133958918746 
		10 3.9415334375554649 14 8.8537446791138841 16 9.9498978201191584 46 9.9498978201191584 
		69 9.9498978201191584 70 -2.8917153083289122;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA3363";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0.31779363889420204 6 -2.9937069715115481 
		10 -1.2193022270180649 14 0.91065576570603501 16 1.6561408060748619 46 1.6561408060748619 
		69 1.6561408060748619 70 1.4425752519930548;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA3364";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 -4.3513379758710267 6 -5.1993085591285872 
		10 -3.6418825437819504 14 -1.5181191262098417 16 -0.77480218639653087 46 -0.77480218639653087 
		69 -0.77480218639653087 70 -1.1234753961979935;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA3365";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3366";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3367";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 2.4717875269080888e-030;
createNode animCurveTU -n "animCurveTU1768";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 6 1 10 1 14 1 16 1 46 1 69 1 70 
		1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU1769";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999989 2 0.99999999999999989 
		6 0.99999999999999989 10 0.99999999999999989 14 0.99999999999999989 16 0.99999999999999989 
		46 0.99999999999999989 69 0.99999999999999989 70 0.99999999999999989;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU1770";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999989 2 0.99999999999999989 
		6 0.99999999999999989 10 0.99999999999999989 14 0.99999999999999989 16 0.99999999999999989 
		46 0.99999999999999989 69 0.99999999999999989 70 0.99999999999999989;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA3368";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 10.584975422311024 6 0.87484382723385212 
		10 -3.281597527944466 14 -5.3450838807495389 16 -6.0673038551697909 46 -6.0673038551697909 
		69 -6.0673038551697909 70 -22.927525745550493;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA3369";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 8.5907521011568821 6 3.9091482288697579 
		10 5.6614439037820619 14 8.0012721526813042 16 8.8202117573802195 46 8.8202117573802195 
		69 8.8202117573802195 70 7.64524018358152;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA3370";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 -18.149961535764454 6 -15.239872914412953 
		10 -9.2744157240054932 14 -3.912256838666563 16 -2.7829189496457909 46 -2.7829189496457909 
		69 -2.7829189496457909 70 -5.2145423540201561;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA3371";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3372";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3373";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -3.1362690564052959e-046;
createNode animCurveTU -n "animCurveTU1771";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 6 1 10 1 14 1 16 1 46 1 69 1 70 
		1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU1772";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 6 1 10 1 14 1 16 1 46 1 69 1 70 
		1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU1773";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 6 1 10 1 14 1 16 1 46 1 69 1 70 
		1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA3374";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 8.0172778711835981 6 -0.25631954244328026 
		10 -0.59868179394675436 14 -1.0655395567785058 16 -1.2289397174201766 46 -1.2289397174201766 
		69 -1.2289397174201766 70 -16.63522872869061;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA3375";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 -1.1538803641846083 6 -1.8591583649326497 
		10 -2.081117287027749 14 -2.3837886398267396 16 -2.4897235767741424 46 -2.4897235767741424 
		69 -2.4897235767741424 70 0.15293623276183629;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA3376";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -3.1362690564052959e-046 2 1.7392886264686691 
		6 0.78062549680335735 10 3.8564462762480818 14 8.439109858691042 16 9.5187539895432884 
		46 9.5187539895432884 69 9.5187539895432884 70 9.8348919822049297;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA3377";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3378";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3379";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1774";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999967 2 0.99999999999999967 
		6 0.99999999999999967 10 0.99999999999999967 14 0.99999999999999967 16 0.99999999999999967 
		46 0.99999999999999967 69 0.99999999999999967 70 0.99999999999999967;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU1775";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999944 2 0.99999999999999944 
		6 0.99999999999999944 10 0.99999999999999944 14 0.99999999999999944 16 0.99999999999999944 
		46 0.99999999999999944 69 0.99999999999999944 70 0.99999999999999944;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU1776";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.99999999999999989 2 0.99999999999999989 
		6 0.99999999999999989 10 0.99999999999999989 14 0.99999999999999989 16 0.99999999999999989 
		46 0.99999999999999989 69 0.99999999999999989 70 0.99999999999999989;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA3380";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 15.078702407300867 6 22.475029029446517 
		10 3.3212245967198326 14 -16.867779244056866 16 -21.307006482681903 46 -21.307006482681903 
		69 -21.307006482681903 70 -35.68714226208067;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA3381";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 -4.560313409058633 6 -3.2920167462097565 
		10 -3.2588762504246205 14 -3.2136846510194896 16 -3.197867596682292 46 -3.197867596682292 
		69 -3.197867596682292 70 -6.5096266159489273;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA3382";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 13.973367508763793 6 11.79002883551945 
		10 9.6908992239471647 14 6.8284488514282877 16 5.8265915665426649 46 5.8265915665426649 
		69 5.8265915665426649 70 4.2843532801931179;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA3383";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3384";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3385";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1777";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 6 1 10 1 14 1 16 1 46 1 69 1 70 
		1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU1778";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 6 1 10 1 14 1 16 1 46 1 69 1 70 
		1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU1779";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 6 1 10 1 14 1 16 1 46 1 69 1 70 
		1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA3386";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 27.994149867778386 6 5.025453144174798 
		10 -6.6016287956936228 14 -13.981728387596039 16 -15.342674969158962 46 -15.342674969158962 
		69 -15.342674969158962 70 -37.440169221526197;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA3387";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 5.5680866933163013 6 4.4663966717575363 
		10 4.2779990550386868 14 4.0210931330862971 16 3.9311760914113467 46 3.9311760914113467 
		69 3.9311760914113467 70 16.439502013591692;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA3388";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 -19.658308077558303 6 -17.883399145380722 
		10 -28.479751737267264 14 -44.267251200747147 16 -47.986677958328336 46 -47.986677958328336 
		69 -47.986677958328336 70 -43.646794153391632;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU1780";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTU -n "animCurveTU1781";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000004;
createNode animCurveTU -n "animCurveTU1782";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTA -n "animCurveTA3389";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3390";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3391";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1153";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.3877787807814457e-017;
createNode animCurveTL -n "animCurveTL1154";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL1155";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.1102230246251565e-016;
createNode animCurveTU -n "animCurveTU1783";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.99999999999999978 2 0.99999999999999978 
		6 0.99999999999999978 10 0.99999999999999978 14 0.99999999999999978 16 0.99999999999999978 
		22 0.99999999999999978 46 0.99999999999999978 69 0.99999999999999978 70 0.99999999999999978;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1784";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.99999999999999978 2 0.99999999999999978 
		6 0.99999999999999978 10 0.99999999999999978 14 0.99999999999999978 16 0.99999999999999978 
		22 0.99999999999999978 46 0.99999999999999978 69 0.99999999999999978 70 0.99999999999999978;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1785";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.99999999999999989 2 0.99999999999999989 
		6 0.99999999999999989 10 0.99999999999999989 14 0.99999999999999989 16 0.99999999999999989 
		22 0.99999999999999989 46 0.99999999999999989 69 0.99999999999999989 70 0.99999999999999989;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3392";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 2.5272000481105028 14 3.5440890472749262 
		16 3.9000000742446033 22 3.9000000742446033 46 3.9000000742446033 69 3.9000000742446033 
		70 3.9000000742446033;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3393";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 -11.497228014609789 14 -16.91201789812034 
		16 -17.74263582501511 22 -17.74263582501511 46 -17.74263582501511 69 -17.74263582501511 
		70 -17.74263582501511;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3394";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 4.8887219576927423 14 6.8558347640050732 
		16 7.5443240087850949 22 7.5443240087850949 46 7.5443240087850949 69 7.5443240087850949 
		70 7.5443240087850949;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1156";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1157";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 4.4408920985006262e-016 2 0 6 0 10 0 
		14 0 16 0 22 0 46 0 69 0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL1158";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3395";
	setAttr ".tan" 9;
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
createNode animCurveTU -n "animCurveTU1786";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999978;
createNode animCurveTU -n "animCurveTU1787";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1788";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA3398";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3399";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3400";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
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
createNode animCurveTU -n "animCurveTU1789";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU1790";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999978;
createNode animCurveTU -n "animCurveTU1791";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999956;
createNode animCurveTA -n "animCurveTA3404";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
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
createNode animCurveTU -n "animCurveTU1792";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTU -n "animCurveTU1793";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU1794";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTA -n "animCurveTA3410";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3411";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3412";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3413";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3414";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3415";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1795";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.99999999999999978 2 0.99999999999999978 
		6 0.99999999999999978 10 0.99999999999999978 14 0.99999999999999978 16 0.99999999999999978 
		22 0.99999999999999978 46 0.99999999999999978 69 0.99999999999999978 70 0.99999999999999978;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1796";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 2 1 6 1 10 1 14 1 16 1 22 1 46 1 69 
		1 70 1;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1797";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1.0000000000000002 2 1.0000000000000002 
		6 1.0000000000000002 10 1.0000000000000002 14 1.0000000000000002 16 1.0000000000000002 
		22 1.0000000000000002 46 1.0000000000000002 69 1.0000000000000002 70 1.0000000000000002;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3416";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 6.5887416381602044 2 0 6 0 10 0 14 0 
		16 0 22 0 46 0 69 0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3417";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3418";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3419";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3420";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3421";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1798";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.99999999999999944 2 0.99999999999999944 
		6 0.99999999999999944 10 0.99999999999999944 14 0.99999999999999944 16 0.99999999999999944 
		22 0.99999999999999944 46 0.99999999999999944 69 0.99999999999999944 70 0.99999999999999944;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1799";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.99999999999999956 2 0.99999999999999956 
		6 0.99999999999999956 10 0.99999999999999956 14 0.99999999999999956 16 0.99999999999999956 
		22 0.99999999999999956 46 0.99999999999999956 69 0.99999999999999956 70 0.99999999999999956;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1800";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.99999999999999933 2 0.99999999999999933 
		6 0.99999999999999933 10 0.99999999999999933 14 0.99999999999999933 16 0.99999999999999933 
		22 0.99999999999999933 46 0.99999999999999933 69 0.99999999999999933 70 0.99999999999999933;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3422";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 10.802160318599565 2 0 6 0 10 0 14 0 
		16 0 22 0 46 0 69 0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3423";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.18093193430354684 2 0 6 0 10 0 14 0 
		16 0 22 0 46 0 69 0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3424";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -5.5598653650577603 2 0 6 0 10 0 14 0 
		16 0 22 0 46 0 69 0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3425";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3426";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3427";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1801";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.99999999999999967 2 0.99999999999999967 
		6 0.99999999999999967 10 0.99999999999999967 14 0.99999999999999967 16 0.99999999999999967 
		22 0.99999999999999967 46 0.99999999999999967 69 0.99999999999999967 70 0.99999999999999967;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1802";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.99999999999999978 2 0.99999999999999978 
		6 0.99999999999999978 10 0.99999999999999978 14 0.99999999999999978 16 0.99999999999999978 
		22 0.99999999999999978 46 0.99999999999999978 69 0.99999999999999978 70 0.99999999999999978;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1803";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.99999999999999978 2 0.99999999999999978 
		6 0.99999999999999978 10 0.99999999999999978 14 0.99999999999999978 16 0.99999999999999978 
		22 0.99999999999999978 46 0.99999999999999978 69 0.99999999999999978 70 0.99999999999999978;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3428";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3429";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3430";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 46 0 69 
		0 70 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3431";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3432";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3433";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1804";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.99999999999999989 2 0.99999999999999989 
		6 0.99999999999999989 10 0.99999999999999989 14 0.99999999999999989 16 0.99999999999999989 
		22 0.99999999999999989 46 0.99999999999999989 69 0.99999999999999989 70 0.99999999999999989;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1805";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.99999999999999978 2 0.99999999999999978 
		6 0.99999999999999978 10 0.99999999999999978 14 0.99999999999999978 16 0.99999999999999978 
		22 0.99999999999999978 46 0.99999999999999978 69 0.99999999999999978 70 0.99999999999999978;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1806";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 2 1 6 1 10 1 14 1 16 1 22 1 46 1 69 
		1 70 1;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3434";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -5.2487233478977044 2 -5.2487233478977044 
		6 -5.2487233478977044 10 -5.2487233478977044 14 -5.2487233478977044 16 -5.2487233478977044 
		22 -5.2487233478977044 46 -5.2487233478977044 69 -5.2487233478977044 70 -5.2487233478977044;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3435";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -19.191038692298999 2 -19.191038692298999 
		6 -19.191038692298999 10 -19.191038692298999 14 -19.191038692298999 16 -19.191038692298999 
		22 -19.191038692298999 46 -19.191038692298999 69 -19.191038692298999 70 -19.191038692298999;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3436";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 3.4639940811277468 2 3.4639940811277468 
		6 3.4639940811277468 10 3.4639940811277468 14 3.4639940811277468 16 3.4639940811277468 
		22 3.4639940811277468 46 3.4639940811277468 69 3.4639940811277468 70 3.4639940811277468;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3437";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3438";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3439";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1807";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.99999999999999989 2 0.99999999999999989 
		6 0.99999999999999989 10 0.99999999999999989 14 0.99999999999999989 16 0.99999999999999989 
		22 0.99999999999999989 46 0.99999999999999989 69 0.99999999999999989 70 0.99999999999999989;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1808";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.99999999999999989 2 0.99999999999999989 
		6 0.99999999999999989 10 0.99999999999999989 14 0.99999999999999989 16 0.99999999999999989 
		22 0.99999999999999989 46 0.99999999999999989 69 0.99999999999999989 70 0.99999999999999989;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1809";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.99999999999999978 2 0.99999999999999978 
		6 0.99999999999999978 10 0.99999999999999978 14 0.99999999999999978 16 0.99999999999999978 
		22 0.99999999999999978 46 0.99999999999999978 69 0.99999999999999978 70 0.99999999999999978;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3440";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 15.804493166945804 2 13.877004431497326 
		6 13.877004431497326 10 13.877004431497326 14 13.877004431497326 16 13.877004431497326 
		22 13.877004431497326 46 13.877004431497326 69 13.877004431497326 70 13.877004431497326;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3441";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 3.5290061766020497 2 -9.8256854129170819 
		6 -9.8256854129170819 10 -9.8256854129170819 14 -9.8256854129170819 16 -9.8256854129170819 
		22 -9.8256854129170819 46 -9.8256854129170819 69 -9.8256854129170819 70 -9.8256854129170819;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3442";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 55.012788276203878 2 47.740341091290361 
		6 47.740341091290361 10 47.740341091290361 14 47.740341091290361 16 47.740341091290361 
		22 47.740341091290361 46 47.740341091290361 69 47.740341091290361 70 47.740341091290361;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3443";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3444";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA3445";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU1810";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1.0000000000000002 2 1.0000000000000002 
		6 1.0000000000000002 10 1.0000000000000002 14 1.0000000000000002 16 1.0000000000000002 
		22 1.0000000000000002 46 1.0000000000000002 69 1.0000000000000002 70 1.0000000000000002;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1811";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1.0000000000000002 2 1.0000000000000002 
		6 1.0000000000000002 10 1.0000000000000002 14 1.0000000000000002 16 1.0000000000000002 
		22 1.0000000000000002 46 1.0000000000000002 69 1.0000000000000002 70 1.0000000000000002;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1812";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 2 1 6 1 10 1 14 1 16 1 22 1 46 1 69 
		1 70 1;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3446";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 14.236890325621934 2 -1.3224722037367471 
		6 -1.3224722037367471 10 -1.3224722037367471 14 -1.3224722037367471 16 -1.3224722037367471 
		22 -1.3224722037367471 46 -1.3224722037367471 69 -1.3224722037367471 70 -1.3224722037367471;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3447";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -1.4378573021860341 2 -1.6804077282048093 
		6 -1.6804077282048093 10 -1.6804077282048093 14 -1.6804077282048093 16 -1.6804077282048093 
		22 -1.6804077282048093 46 -1.6804077282048093 69 -1.6804077282048093 70 -1.6804077282048093;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA3448";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 2.5194410123137181 2 1.6351083250161258 
		6 1.6351083250161258 10 1.6351083250161258 14 1.6351083250161258 16 1.6351083250161258 
		22 1.6351083250161258 46 1.6351083250161258 69 1.6351083250161258 70 1.6351083250161258;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU1813";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 6 1 10 1 14 1 16 1 22 1 69 1 70 
		0.001;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU1814";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 6 1 10 1 14 1 16 1 22 1 69 1 70 
		0.001;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU1815";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 6 1 10 1 14 1 16 1 22 1 69 1 70 
		0.001;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA3449";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 69 -57.540194155650049 
		70 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 2 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 2 10 
		10;
createNode animCurveTA -n "animCurveTA3450";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 69 0 70 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA3451";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 69 0 70 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL1159";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 69 0 70 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL1160";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 69 0 70 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL1161";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 6 0 10 0 14 0 16 0 22 0 69 0 70 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU1816";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 6 1 10 1 14 1 16 1 22 1 69 1 70 
		1;
	setAttr -s 9 ".kit[0:8]"  3 9 9 9 9 9 9 9 
		9;
	setAttr -s 9 ".kot[0:8]"  3 5 5 5 5 5 5 5 
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
connectAttr "deathSource2.cl" "clipLibrary1.sc[0]";
connectAttr "animCurveTA3102.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "animCurveTA3103.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "animCurveTA3104.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "animCurveTA3105.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "animCurveTA3106.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "animCurveTA3107.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "animCurveTA3108.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "animCurveTA3109.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "animCurveTA3110.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "animCurveTA3111.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "animCurveTA3112.a" "clipLibrary1.cel[0].cev[10].cevr";
connectAttr "animCurveTA3113.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "animCurveTA3114.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "animCurveTA3115.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "animCurveTA3116.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "animCurveTA3117.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "animCurveTA3118.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "animCurveTA3119.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "animCurveTA3120.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "animCurveTA3121.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "animCurveTA3122.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "animCurveTA3123.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "animCurveTA3124.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "animCurveTA3125.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "animCurveTA3126.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "animCurveTA3127.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "animCurveTA3128.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "animCurveTA3129.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "animCurveTA3130.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "animCurveTA3131.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "animCurveTA3132.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "animCurveTA3133.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "animCurveTA3134.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "animCurveTA3135.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "animCurveTA3136.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "animCurveTA3137.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "animCurveTA3138.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "animCurveTA3139.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "animCurveTA3140.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "animCurveTL1045.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "animCurveTL1046.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "animCurveTL1047.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "animCurveTA3141.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "animCurveTA3142.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "animCurveTA3143.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "animCurveTL1048.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "animCurveTL1049.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "animCurveTL1050.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "animCurveTA3144.a" "clipLibrary1.cel[0].cev[48].cevr";
connectAttr "animCurveTA3145.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "animCurveTA3146.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "animCurveTL1051.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "animCurveTL1052.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "animCurveTL1053.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "animCurveTA3147.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "animCurveTA3148.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "animCurveTA3149.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "animCurveTL1054.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "animCurveTL1055.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "animCurveTL1056.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "animCurveTA3150.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "animCurveTA3151.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "animCurveTA3152.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "animCurveTL1057.a" "clipLibrary1.cel[0].cev[63].cevr";
connectAttr "animCurveTL1058.a" "clipLibrary1.cel[0].cev[64].cevr";
connectAttr "animCurveTL1059.a" "clipLibrary1.cel[0].cev[65].cevr";
connectAttr "animCurveTA3153.a" "clipLibrary1.cel[0].cev[66].cevr";
connectAttr "animCurveTA3154.a" "clipLibrary1.cel[0].cev[67].cevr";
connectAttr "animCurveTA3155.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "animCurveTL1060.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "animCurveTL1061.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "animCurveTL1062.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "animCurveTA3156.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "animCurveTA3157.a" "clipLibrary1.cel[0].cev[73].cevr";
connectAttr "animCurveTA3158.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "animCurveTL1063.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "animCurveTL1064.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "animCurveTL1065.a" "clipLibrary1.cel[0].cev[77].cevr";
connectAttr "animCurveTA3159.a" "clipLibrary1.cel[0].cev[78].cevr";
connectAttr "animCurveTA3160.a" "clipLibrary1.cel[0].cev[79].cevr";
connectAttr "animCurveTA3161.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "animCurveTL1066.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "animCurveTL1067.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "animCurveTL1068.a" "clipLibrary1.cel[0].cev[83].cevr";
connectAttr "animCurveTA3162.a" "clipLibrary1.cel[0].cev[84].cevr";
connectAttr "animCurveTA3163.a" "clipLibrary1.cel[0].cev[85].cevr";
connectAttr "animCurveTA3164.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "animCurveTL1069.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "animCurveTL1070.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "animCurveTL1071.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr "animCurveTA3165.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "animCurveTA3166.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "animCurveTA3167.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "animCurveTL1072.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "animCurveTL1073.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "animCurveTL1074.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "animCurveTU1635.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "animCurveTA3168.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "animCurveTA3169.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "animCurveTA3170.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "animCurveTL1075.a" "clipLibrary1.cel[0].cev[100].cevr";
connectAttr "animCurveTL1076.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "animCurveTL1077.a" "clipLibrary1.cel[0].cev[102].cevr";
connectAttr "animCurveTA3171.a" "clipLibrary1.cel[0].cev[103].cevr";
connectAttr "animCurveTA3172.a" "clipLibrary1.cel[0].cev[104].cevr";
connectAttr "animCurveTA3173.a" "clipLibrary1.cel[0].cev[105].cevr";
connectAttr "animCurveTL1078.a" "clipLibrary1.cel[0].cev[106].cevr";
connectAttr "animCurveTL1079.a" "clipLibrary1.cel[0].cev[107].cevr";
connectAttr "animCurveTL1080.a" "clipLibrary1.cel[0].cev[108].cevr";
connectAttr "animCurveTU1636.a" "clipLibrary1.cel[0].cev[109].cevr";
connectAttr "animCurveTU1637.a" "clipLibrary1.cel[0].cev[110].cevr";
connectAttr "animCurveTU1638.a" "clipLibrary1.cel[0].cev[111].cevr";
connectAttr "animCurveTU1639.a" "clipLibrary1.cel[0].cev[112].cevr";
connectAttr "animCurveTU1640.a" "clipLibrary1.cel[0].cev[113].cevr";
connectAttr "animCurveTU1641.a" "clipLibrary1.cel[0].cev[114].cevr";
connectAttr "animCurveTU1642.a" "clipLibrary1.cel[0].cev[115].cevr";
connectAttr "animCurveTA3174.a" "clipLibrary1.cel[0].cev[116].cevr";
connectAttr "animCurveTA3175.a" "clipLibrary1.cel[0].cev[117].cevr";
connectAttr "animCurveTA3176.a" "clipLibrary1.cel[0].cev[118].cevr";
connectAttr "animCurveTA3177.a" "clipLibrary1.cel[0].cev[119].cevr";
connectAttr "animCurveTA3178.a" "clipLibrary1.cel[0].cev[120].cevr";
connectAttr "animCurveTA3179.a" "clipLibrary1.cel[0].cev[121].cevr";
connectAttr "animCurveTA3180.a" "clipLibrary1.cel[0].cev[122].cevr";
connectAttr "animCurveTA3181.a" "clipLibrary1.cel[0].cev[123].cevr";
connectAttr "animCurveTA3182.a" "clipLibrary1.cel[0].cev[124].cevr";
connectAttr "animCurveTA3183.a" "clipLibrary1.cel[0].cev[125].cevr";
connectAttr "animCurveTA3184.a" "clipLibrary1.cel[0].cev[126].cevr";
connectAttr "animCurveTA3185.a" "clipLibrary1.cel[0].cev[127].cevr";
connectAttr "animCurveTA3186.a" "clipLibrary1.cel[0].cev[128].cevr";
connectAttr "animCurveTA3187.a" "clipLibrary1.cel[0].cev[129].cevr";
connectAttr "animCurveTA3188.a" "clipLibrary1.cel[0].cev[130].cevr";
connectAttr "animCurveTA3189.a" "clipLibrary1.cel[0].cev[131].cevr";
connectAttr "animCurveTU1643.a" "clipLibrary1.cel[0].cev[132].cevr";
connectAttr "animCurveTU1644.a" "clipLibrary1.cel[0].cev[133].cevr";
connectAttr "animCurveTU1645.a" "clipLibrary1.cel[0].cev[134].cevr";
connectAttr "animCurveTL1081.a" "clipLibrary1.cel[0].cev[135].cevr";
connectAttr "animCurveTL1082.a" "clipLibrary1.cel[0].cev[136].cevr";
connectAttr "animCurveTL1083.a" "clipLibrary1.cel[0].cev[137].cevr";
connectAttr "animCurveTU1646.a" "clipLibrary1.cel[0].cev[138].cevr";
connectAttr "animCurveTL1084.a" "clipLibrary1.cel[0].cev[139].cevr";
connectAttr "animCurveTL1085.a" "clipLibrary1.cel[0].cev[140].cevr";
connectAttr "animCurveTL1086.a" "clipLibrary1.cel[0].cev[141].cevr";
connectAttr "animCurveTA3190.a" "clipLibrary1.cel[0].cev[142].cevr";
connectAttr "animCurveTA3191.a" "clipLibrary1.cel[0].cev[143].cevr";
connectAttr "animCurveTA3192.a" "clipLibrary1.cel[0].cev[144].cevr";
connectAttr "animCurveTL1087.a" "clipLibrary1.cel[0].cev[145].cevr";
connectAttr "animCurveTL1088.a" "clipLibrary1.cel[0].cev[146].cevr";
connectAttr "animCurveTL1089.a" "clipLibrary1.cel[0].cev[147].cevr";
connectAttr "animCurveTU1647.a" "clipLibrary1.cel[0].cev[148].cevr";
connectAttr "animCurveTU1648.a" "clipLibrary1.cel[0].cev[149].cevr";
connectAttr "animCurveTU1649.a" "clipLibrary1.cel[0].cev[150].cevr";
connectAttr "animCurveTU1650.a" "clipLibrary1.cel[0].cev[151].cevr";
connectAttr "animCurveTU1651.a" "clipLibrary1.cel[0].cev[152].cevr";
connectAttr "animCurveTU1652.a" "clipLibrary1.cel[0].cev[153].cevr";
connectAttr "animCurveTU1653.a" "clipLibrary1.cel[0].cev[154].cevr";
connectAttr "animCurveTU1654.a" "clipLibrary1.cel[0].cev[155].cevr";
connectAttr "animCurveTA3193.a" "clipLibrary1.cel[0].cev[156].cevr";
connectAttr "animCurveTA3194.a" "clipLibrary1.cel[0].cev[157].cevr";
connectAttr "animCurveTA3195.a" "clipLibrary1.cel[0].cev[158].cevr";
connectAttr "animCurveTL1090.a" "clipLibrary1.cel[0].cev[159].cevr";
connectAttr "animCurveTL1091.a" "clipLibrary1.cel[0].cev[160].cevr";
connectAttr "animCurveTL1092.a" "clipLibrary1.cel[0].cev[161].cevr";
connectAttr "animCurveTU1655.a" "clipLibrary1.cel[0].cev[162].cevr";
connectAttr "animCurveTU1656.a" "clipLibrary1.cel[0].cev[163].cevr";
connectAttr "animCurveTU1657.a" "clipLibrary1.cel[0].cev[164].cevr";
connectAttr "animCurveTL1093.a" "clipLibrary1.cel[0].cev[165].cevr";
connectAttr "animCurveTL1094.a" "clipLibrary1.cel[0].cev[166].cevr";
connectAttr "animCurveTL1095.a" "clipLibrary1.cel[0].cev[167].cevr";
connectAttr "animCurveTU1658.a" "clipLibrary1.cel[0].cev[168].cevr";
connectAttr "animCurveTL1096.a" "clipLibrary1.cel[0].cev[169].cevr";
connectAttr "animCurveTL1097.a" "clipLibrary1.cel[0].cev[170].cevr";
connectAttr "animCurveTL1098.a" "clipLibrary1.cel[0].cev[171].cevr";
connectAttr "animCurveTA3196.a" "clipLibrary1.cel[0].cev[172].cevr";
connectAttr "animCurveTA3197.a" "clipLibrary1.cel[0].cev[173].cevr";
connectAttr "animCurveTA3198.a" "clipLibrary1.cel[0].cev[174].cevr";
connectAttr "animCurveTL1099.a" "clipLibrary1.cel[0].cev[175].cevr";
connectAttr "animCurveTL1100.a" "clipLibrary1.cel[0].cev[176].cevr";
connectAttr "animCurveTL1101.a" "clipLibrary1.cel[0].cev[177].cevr";
connectAttr "animCurveTU1659.a" "clipLibrary1.cel[0].cev[178].cevr";
connectAttr "animCurveTU1660.a" "clipLibrary1.cel[0].cev[179].cevr";
connectAttr "animCurveTU1661.a" "clipLibrary1.cel[0].cev[180].cevr";
connectAttr "animCurveTU1662.a" "clipLibrary1.cel[0].cev[181].cevr";
connectAttr "animCurveTU1663.a" "clipLibrary1.cel[0].cev[182].cevr";
connectAttr "animCurveTA3199.a" "clipLibrary1.cel[0].cev[183].cevr";
connectAttr "animCurveTA3200.a" "clipLibrary1.cel[0].cev[184].cevr";
connectAttr "animCurveTA3201.a" "clipLibrary1.cel[0].cev[185].cevr";
connectAttr "animCurveTL1102.a" "clipLibrary1.cel[0].cev[186].cevr";
connectAttr "animCurveTL1103.a" "clipLibrary1.cel[0].cev[187].cevr";
connectAttr "animCurveTL1104.a" "clipLibrary1.cel[0].cev[188].cevr";
connectAttr "animCurveTU1664.a" "clipLibrary1.cel[0].cev[189].cevr";
connectAttr "animCurveTU1665.a" "clipLibrary1.cel[0].cev[190].cevr";
connectAttr "animCurveTU1666.a" "clipLibrary1.cel[0].cev[191].cevr";
connectAttr "animCurveTU1667.a" "clipLibrary1.cel[0].cev[192].cevr";
connectAttr "animCurveTU1668.a" "clipLibrary1.cel[0].cev[193].cevr";
connectAttr "animCurveTU1669.a" "clipLibrary1.cel[0].cev[194].cevr";
connectAttr "animCurveTU1670.a" "clipLibrary1.cel[0].cev[195].cevr";
connectAttr "animCurveTU1671.a" "clipLibrary1.cel[0].cev[196].cevr";
connectAttr "animCurveTU1672.a" "clipLibrary1.cel[0].cev[197].cevr";
connectAttr "animCurveTU1673.a" "clipLibrary1.cel[0].cev[198].cevr";
connectAttr "animCurveTA3202.a" "clipLibrary1.cel[0].cev[199].cevr";
connectAttr "animCurveTA3203.a" "clipLibrary1.cel[0].cev[200].cevr";
connectAttr "animCurveTA3204.a" "clipLibrary1.cel[0].cev[201].cevr";
connectAttr "animCurveTL1105.a" "clipLibrary1.cel[0].cev[202].cevr";
connectAttr "animCurveTL1106.a" "clipLibrary1.cel[0].cev[203].cevr";
connectAttr "animCurveTL1107.a" "clipLibrary1.cel[0].cev[204].cevr";
connectAttr "animCurveTU1674.a" "clipLibrary1.cel[0].cev[205].cevr";
connectAttr "animCurveTU1675.a" "clipLibrary1.cel[0].cev[206].cevr";
connectAttr "animCurveTU1676.a" "clipLibrary1.cel[0].cev[207].cevr";
connectAttr "animCurveTA3205.a" "clipLibrary1.cel[0].cev[208].cevr";
connectAttr "animCurveTA3206.a" "clipLibrary1.cel[0].cev[209].cevr";
connectAttr "animCurveTA3207.a" "clipLibrary1.cel[0].cev[210].cevr";
connectAttr "animCurveTL1108.a" "clipLibrary1.cel[0].cev[211].cevr";
connectAttr "animCurveTL1109.a" "clipLibrary1.cel[0].cev[212].cevr";
connectAttr "animCurveTL1110.a" "clipLibrary1.cel[0].cev[213].cevr";
connectAttr "animCurveTU1677.a" "clipLibrary1.cel[0].cev[214].cevr";
connectAttr "animCurveTU1678.a" "clipLibrary1.cel[0].cev[215].cevr";
connectAttr "animCurveTU1679.a" "clipLibrary1.cel[0].cev[216].cevr";
connectAttr "animCurveTA3208.a" "clipLibrary1.cel[0].cev[217].cevr";
connectAttr "animCurveTA3209.a" "clipLibrary1.cel[0].cev[218].cevr";
connectAttr "animCurveTA3210.a" "clipLibrary1.cel[0].cev[219].cevr";
connectAttr "animCurveTL1111.a" "clipLibrary1.cel[0].cev[220].cevr";
connectAttr "animCurveTL1112.a" "clipLibrary1.cel[0].cev[221].cevr";
connectAttr "animCurveTL1113.a" "clipLibrary1.cel[0].cev[222].cevr";
connectAttr "animCurveTU1680.a" "clipLibrary1.cel[0].cev[223].cevr";
connectAttr "animCurveTU1681.a" "clipLibrary1.cel[0].cev[224].cevr";
connectAttr "animCurveTA3211.a" "clipLibrary1.cel[0].cev[225].cevr";
connectAttr "animCurveTA3212.a" "clipLibrary1.cel[0].cev[226].cevr";
connectAttr "animCurveTA3213.a" "clipLibrary1.cel[0].cev[227].cevr";
connectAttr "animCurveTL1114.a" "clipLibrary1.cel[0].cev[228].cevr";
connectAttr "animCurveTL1115.a" "clipLibrary1.cel[0].cev[229].cevr";
connectAttr "animCurveTL1116.a" "clipLibrary1.cel[0].cev[230].cevr";
connectAttr "animCurveTU1682.a" "clipLibrary1.cel[0].cev[231].cevr";
connectAttr "animCurveTU1683.a" "clipLibrary1.cel[0].cev[232].cevr";
connectAttr "animCurveTU1684.a" "clipLibrary1.cel[0].cev[233].cevr";
connectAttr "animCurveTA3214.a" "clipLibrary1.cel[0].cev[234].cevr";
connectAttr "animCurveTA3215.a" "clipLibrary1.cel[0].cev[235].cevr";
connectAttr "animCurveTA3216.a" "clipLibrary1.cel[0].cev[236].cevr";
connectAttr "animCurveTL1117.a" "clipLibrary1.cel[0].cev[237].cevr";
connectAttr "animCurveTL1118.a" "clipLibrary1.cel[0].cev[238].cevr";
connectAttr "animCurveTL1119.a" "clipLibrary1.cel[0].cev[239].cevr";
connectAttr "animCurveTU1685.a" "clipLibrary1.cel[0].cev[240].cevr";
connectAttr "animCurveTU1686.a" "clipLibrary1.cel[0].cev[241].cevr";
connectAttr "animCurveTA3217.a" "clipLibrary1.cel[0].cev[242].cevr";
connectAttr "animCurveTA3218.a" "clipLibrary1.cel[0].cev[243].cevr";
connectAttr "animCurveTA3219.a" "clipLibrary1.cel[0].cev[244].cevr";
connectAttr "animCurveTL1120.a" "clipLibrary1.cel[0].cev[245].cevr";
connectAttr "animCurveTL1121.a" "clipLibrary1.cel[0].cev[246].cevr";
connectAttr "animCurveTL1122.a" "clipLibrary1.cel[0].cev[247].cevr";
connectAttr "animCurveTA3220.a" "clipLibrary1.cel[0].cev[248].cevr";
connectAttr "animCurveTA3221.a" "clipLibrary1.cel[0].cev[249].cevr";
connectAttr "animCurveTA3222.a" "clipLibrary1.cel[0].cev[250].cevr";
connectAttr "animCurveTA3223.a" "clipLibrary1.cel[0].cev[251].cevr";
connectAttr "animCurveTA3224.a" "clipLibrary1.cel[0].cev[252].cevr";
connectAttr "animCurveTA3225.a" "clipLibrary1.cel[0].cev[253].cevr";
connectAttr "animCurveTA3226.a" "clipLibrary1.cel[0].cev[254].cevr";
connectAttr "animCurveTA3227.a" "clipLibrary1.cel[0].cev[255].cevr";
connectAttr "animCurveTA3228.a" "clipLibrary1.cel[0].cev[256].cevr";
connectAttr "animCurveTA3229.a" "clipLibrary1.cel[0].cev[257].cevr";
connectAttr "animCurveTA3230.a" "clipLibrary1.cel[0].cev[258].cevr";
connectAttr "animCurveTA3231.a" "clipLibrary1.cel[0].cev[259].cevr";
connectAttr "animCurveTA3232.a" "clipLibrary1.cel[0].cev[260].cevr";
connectAttr "animCurveTA3233.a" "clipLibrary1.cel[0].cev[261].cevr";
connectAttr "animCurveTA3234.a" "clipLibrary1.cel[0].cev[262].cevr";
connectAttr "animCurveTA3235.a" "clipLibrary1.cel[0].cev[263].cevr";
connectAttr "animCurveTU1687.a" "clipLibrary1.cel[0].cev[264].cevr";
connectAttr "animCurveTU1688.a" "clipLibrary1.cel[0].cev[265].cevr";
connectAttr "animCurveTU1689.a" "clipLibrary1.cel[0].cev[266].cevr";
connectAttr "animCurveTL1123.a" "clipLibrary1.cel[0].cev[267].cevr";
connectAttr "animCurveTL1124.a" "clipLibrary1.cel[0].cev[268].cevr";
connectAttr "animCurveTL1125.a" "clipLibrary1.cel[0].cev[269].cevr";
connectAttr "animCurveTU1690.a" "clipLibrary1.cel[0].cev[270].cevr";
connectAttr "animCurveTL1126.a" "clipLibrary1.cel[0].cev[271].cevr";
connectAttr "animCurveTL1127.a" "clipLibrary1.cel[0].cev[272].cevr";
connectAttr "animCurveTL1128.a" "clipLibrary1.cel[0].cev[273].cevr";
connectAttr "animCurveTA3236.a" "clipLibrary1.cel[0].cev[274].cevr";
connectAttr "animCurveTA3237.a" "clipLibrary1.cel[0].cev[275].cevr";
connectAttr "animCurveTA3238.a" "clipLibrary1.cel[0].cev[276].cevr";
connectAttr "animCurveTL1129.a" "clipLibrary1.cel[0].cev[277].cevr";
connectAttr "animCurveTL1130.a" "clipLibrary1.cel[0].cev[278].cevr";
connectAttr "animCurveTL1131.a" "clipLibrary1.cel[0].cev[279].cevr";
connectAttr "animCurveTU1691.a" "clipLibrary1.cel[0].cev[280].cevr";
connectAttr "animCurveTU1692.a" "clipLibrary1.cel[0].cev[281].cevr";
connectAttr "animCurveTU1693.a" "clipLibrary1.cel[0].cev[282].cevr";
connectAttr "animCurveTU1694.a" "clipLibrary1.cel[0].cev[283].cevr";
connectAttr "animCurveTU1695.a" "clipLibrary1.cel[0].cev[284].cevr";
connectAttr "animCurveTU1696.a" "clipLibrary1.cel[0].cev[285].cevr";
connectAttr "animCurveTU1697.a" "clipLibrary1.cel[0].cev[286].cevr";
connectAttr "animCurveTU1698.a" "clipLibrary1.cel[0].cev[287].cevr";
connectAttr "animCurveTA3239.a" "clipLibrary1.cel[0].cev[288].cevr";
connectAttr "animCurveTA3240.a" "clipLibrary1.cel[0].cev[289].cevr";
connectAttr "animCurveTA3241.a" "clipLibrary1.cel[0].cev[290].cevr";
connectAttr "animCurveTL1132.a" "clipLibrary1.cel[0].cev[291].cevr";
connectAttr "animCurveTL1133.a" "clipLibrary1.cel[0].cev[292].cevr";
connectAttr "animCurveTL1134.a" "clipLibrary1.cel[0].cev[293].cevr";
connectAttr "animCurveTU1699.a" "clipLibrary1.cel[0].cev[294].cevr";
connectAttr "animCurveTU1700.a" "clipLibrary1.cel[0].cev[295].cevr";
connectAttr "animCurveTU1701.a" "clipLibrary1.cel[0].cev[296].cevr";
connectAttr "animCurveTL1135.a" "clipLibrary1.cel[0].cev[297].cevr";
connectAttr "animCurveTL1136.a" "clipLibrary1.cel[0].cev[298].cevr";
connectAttr "animCurveTL1137.a" "clipLibrary1.cel[0].cev[299].cevr";
connectAttr "animCurveTU1702.a" "clipLibrary1.cel[0].cev[300].cevr";
connectAttr "animCurveTL1138.a" "clipLibrary1.cel[0].cev[301].cevr";
connectAttr "animCurveTL1139.a" "clipLibrary1.cel[0].cev[302].cevr";
connectAttr "animCurveTL1140.a" "clipLibrary1.cel[0].cev[303].cevr";
connectAttr "animCurveTA3242.a" "clipLibrary1.cel[0].cev[304].cevr";
connectAttr "animCurveTA3243.a" "clipLibrary1.cel[0].cev[305].cevr";
connectAttr "animCurveTA3244.a" "clipLibrary1.cel[0].cev[306].cevr";
connectAttr "animCurveTL1141.a" "clipLibrary1.cel[0].cev[307].cevr";
connectAttr "animCurveTL1142.a" "clipLibrary1.cel[0].cev[308].cevr";
connectAttr "animCurveTL1143.a" "clipLibrary1.cel[0].cev[309].cevr";
connectAttr "animCurveTU1703.a" "clipLibrary1.cel[0].cev[310].cevr";
connectAttr "animCurveTU1704.a" "clipLibrary1.cel[0].cev[311].cevr";
connectAttr "animCurveTU1705.a" "clipLibrary1.cel[0].cev[312].cevr";
connectAttr "animCurveTU1706.a" "clipLibrary1.cel[0].cev[313].cevr";
connectAttr "animCurveTU1707.a" "clipLibrary1.cel[0].cev[314].cevr";
connectAttr "animCurveTA3245.a" "clipLibrary1.cel[0].cev[315].cevr";
connectAttr "animCurveTA3246.a" "clipLibrary1.cel[0].cev[316].cevr";
connectAttr "animCurveTA3247.a" "clipLibrary1.cel[0].cev[317].cevr";
connectAttr "animCurveTL1144.a" "clipLibrary1.cel[0].cev[318].cevr";
connectAttr "animCurveTL1145.a" "clipLibrary1.cel[0].cev[319].cevr";
connectAttr "animCurveTL1146.a" "clipLibrary1.cel[0].cev[320].cevr";
connectAttr "animCurveTA3248.a" "clipLibrary1.cel[0].cev[321].cevr";
connectAttr "animCurveTA3249.a" "clipLibrary1.cel[0].cev[322].cevr";
connectAttr "animCurveTA3250.a" "clipLibrary1.cel[0].cev[323].cevr";
connectAttr "animCurveTA3251.a" "clipLibrary1.cel[0].cev[324].cevr";
connectAttr "animCurveTA3252.a" "clipLibrary1.cel[0].cev[325].cevr";
connectAttr "animCurveTA3253.a" "clipLibrary1.cel[0].cev[326].cevr";
connectAttr "animCurveTU1708.a" "clipLibrary1.cel[0].cev[327].cevr";
connectAttr "animCurveTU1709.a" "clipLibrary1.cel[0].cev[328].cevr";
connectAttr "animCurveTU1710.a" "clipLibrary1.cel[0].cev[329].cevr";
connectAttr "animCurveTA3254.a" "clipLibrary1.cel[0].cev[330].cevr";
connectAttr "animCurveTA3255.a" "clipLibrary1.cel[0].cev[331].cevr";
connectAttr "animCurveTA3256.a" "clipLibrary1.cel[0].cev[332].cevr";
connectAttr "animCurveTA3257.a" "clipLibrary1.cel[0].cev[333].cevr";
connectAttr "animCurveTA3258.a" "clipLibrary1.cel[0].cev[334].cevr";
connectAttr "animCurveTA3259.a" "clipLibrary1.cel[0].cev[335].cevr";
connectAttr "animCurveTU1711.a" "clipLibrary1.cel[0].cev[336].cevr";
connectAttr "animCurveTU1712.a" "clipLibrary1.cel[0].cev[337].cevr";
connectAttr "animCurveTU1713.a" "clipLibrary1.cel[0].cev[338].cevr";
connectAttr "animCurveTA3260.a" "clipLibrary1.cel[0].cev[339].cevr";
connectAttr "animCurveTA3261.a" "clipLibrary1.cel[0].cev[340].cevr";
connectAttr "animCurveTA3262.a" "clipLibrary1.cel[0].cev[341].cevr";
connectAttr "animCurveTA3263.a" "clipLibrary1.cel[0].cev[342].cevr";
connectAttr "animCurveTA3264.a" "clipLibrary1.cel[0].cev[343].cevr";
connectAttr "animCurveTA3265.a" "clipLibrary1.cel[0].cev[344].cevr";
connectAttr "animCurveTU1714.a" "clipLibrary1.cel[0].cev[345].cevr";
connectAttr "animCurveTU1715.a" "clipLibrary1.cel[0].cev[346].cevr";
connectAttr "animCurveTU1716.a" "clipLibrary1.cel[0].cev[347].cevr";
connectAttr "animCurveTA3266.a" "clipLibrary1.cel[0].cev[348].cevr";
connectAttr "animCurveTA3267.a" "clipLibrary1.cel[0].cev[349].cevr";
connectAttr "animCurveTA3268.a" "clipLibrary1.cel[0].cev[350].cevr";
connectAttr "animCurveTA3269.a" "clipLibrary1.cel[0].cev[351].cevr";
connectAttr "animCurveTA3270.a" "clipLibrary1.cel[0].cev[352].cevr";
connectAttr "animCurveTA3271.a" "clipLibrary1.cel[0].cev[353].cevr";
connectAttr "animCurveTU1717.a" "clipLibrary1.cel[0].cev[354].cevr";
connectAttr "animCurveTU1718.a" "clipLibrary1.cel[0].cev[355].cevr";
connectAttr "animCurveTU1719.a" "clipLibrary1.cel[0].cev[356].cevr";
connectAttr "animCurveTA3272.a" "clipLibrary1.cel[0].cev[357].cevr";
connectAttr "animCurveTA3273.a" "clipLibrary1.cel[0].cev[358].cevr";
connectAttr "animCurveTA3274.a" "clipLibrary1.cel[0].cev[359].cevr";
connectAttr "animCurveTU1720.a" "clipLibrary1.cel[0].cev[360].cevr";
connectAttr "animCurveTU1721.a" "clipLibrary1.cel[0].cev[361].cevr";
connectAttr "animCurveTU1722.a" "clipLibrary1.cel[0].cev[362].cevr";
connectAttr "animCurveTA3275.a" "clipLibrary1.cel[0].cev[363].cevr";
connectAttr "animCurveTA3276.a" "clipLibrary1.cel[0].cev[364].cevr";
connectAttr "animCurveTA3277.a" "clipLibrary1.cel[0].cev[365].cevr";
connectAttr "animCurveTL1147.a" "clipLibrary1.cel[0].cev[366].cevr";
connectAttr "animCurveTL1148.a" "clipLibrary1.cel[0].cev[367].cevr";
connectAttr "animCurveTL1149.a" "clipLibrary1.cel[0].cev[368].cevr";
connectAttr "animCurveTU1723.a" "clipLibrary1.cel[0].cev[369].cevr";
connectAttr "animCurveTU1724.a" "clipLibrary1.cel[0].cev[370].cevr";
connectAttr "animCurveTU1725.a" "clipLibrary1.cel[0].cev[371].cevr";
connectAttr "animCurveTA3278.a" "clipLibrary1.cel[0].cev[372].cevr";
connectAttr "animCurveTA3279.a" "clipLibrary1.cel[0].cev[373].cevr";
connectAttr "animCurveTA3280.a" "clipLibrary1.cel[0].cev[374].cevr";
connectAttr "animCurveTL1150.a" "clipLibrary1.cel[0].cev[375].cevr";
connectAttr "animCurveTL1151.a" "clipLibrary1.cel[0].cev[376].cevr";
connectAttr "animCurveTL1152.a" "clipLibrary1.cel[0].cev[377].cevr";
connectAttr "animCurveTA3281.a" "clipLibrary1.cel[0].cev[378].cevr";
connectAttr "animCurveTA3282.a" "clipLibrary1.cel[0].cev[379].cevr";
connectAttr "animCurveTA3283.a" "clipLibrary1.cel[0].cev[380].cevr";
connectAttr "animCurveTU1726.a" "clipLibrary1.cel[0].cev[381].cevr";
connectAttr "animCurveTU1727.a" "clipLibrary1.cel[0].cev[382].cevr";
connectAttr "animCurveTU1728.a" "clipLibrary1.cel[0].cev[383].cevr";
connectAttr "animCurveTA3284.a" "clipLibrary1.cel[0].cev[384].cevr";
connectAttr "animCurveTA3285.a" "clipLibrary1.cel[0].cev[385].cevr";
connectAttr "animCurveTA3286.a" "clipLibrary1.cel[0].cev[386].cevr";
connectAttr "animCurveTA3287.a" "clipLibrary1.cel[0].cev[387].cevr";
connectAttr "animCurveTA3288.a" "clipLibrary1.cel[0].cev[388].cevr";
connectAttr "animCurveTA3289.a" "clipLibrary1.cel[0].cev[389].cevr";
connectAttr "animCurveTU1729.a" "clipLibrary1.cel[0].cev[390].cevr";
connectAttr "animCurveTU1730.a" "clipLibrary1.cel[0].cev[391].cevr";
connectAttr "animCurveTU1731.a" "clipLibrary1.cel[0].cev[392].cevr";
connectAttr "animCurveTA3290.a" "clipLibrary1.cel[0].cev[393].cevr";
connectAttr "animCurveTA3291.a" "clipLibrary1.cel[0].cev[394].cevr";
connectAttr "animCurveTA3292.a" "clipLibrary1.cel[0].cev[395].cevr";
connectAttr "animCurveTA3293.a" "clipLibrary1.cel[0].cev[396].cevr";
connectAttr "animCurveTA3294.a" "clipLibrary1.cel[0].cev[397].cevr";
connectAttr "animCurveTA3295.a" "clipLibrary1.cel[0].cev[398].cevr";
connectAttr "animCurveTU1732.a" "clipLibrary1.cel[0].cev[399].cevr";
connectAttr "animCurveTU1733.a" "clipLibrary1.cel[0].cev[400].cevr";
connectAttr "animCurveTU1734.a" "clipLibrary1.cel[0].cev[401].cevr";
connectAttr "animCurveTA3296.a" "clipLibrary1.cel[0].cev[402].cevr";
connectAttr "animCurveTA3297.a" "clipLibrary1.cel[0].cev[403].cevr";
connectAttr "animCurveTA3298.a" "clipLibrary1.cel[0].cev[404].cevr";
connectAttr "animCurveTA3299.a" "clipLibrary1.cel[0].cev[405].cevr";
connectAttr "animCurveTA3300.a" "clipLibrary1.cel[0].cev[406].cevr";
connectAttr "animCurveTA3301.a" "clipLibrary1.cel[0].cev[407].cevr";
connectAttr "animCurveTU1735.a" "clipLibrary1.cel[0].cev[408].cevr";
connectAttr "animCurveTU1736.a" "clipLibrary1.cel[0].cev[409].cevr";
connectAttr "animCurveTU1737.a" "clipLibrary1.cel[0].cev[410].cevr";
connectAttr "animCurveTA3302.a" "clipLibrary1.cel[0].cev[411].cevr";
connectAttr "animCurveTA3303.a" "clipLibrary1.cel[0].cev[412].cevr";
connectAttr "animCurveTA3304.a" "clipLibrary1.cel[0].cev[413].cevr";
connectAttr "animCurveTA3305.a" "clipLibrary1.cel[0].cev[414].cevr";
connectAttr "animCurveTA3306.a" "clipLibrary1.cel[0].cev[415].cevr";
connectAttr "animCurveTA3307.a" "clipLibrary1.cel[0].cev[416].cevr";
connectAttr "animCurveTU1738.a" "clipLibrary1.cel[0].cev[417].cevr";
connectAttr "animCurveTU1739.a" "clipLibrary1.cel[0].cev[418].cevr";
connectAttr "animCurveTU1740.a" "clipLibrary1.cel[0].cev[419].cevr";
connectAttr "animCurveTA3308.a" "clipLibrary1.cel[0].cev[420].cevr";
connectAttr "animCurveTA3309.a" "clipLibrary1.cel[0].cev[421].cevr";
connectAttr "animCurveTA3310.a" "clipLibrary1.cel[0].cev[422].cevr";
connectAttr "animCurveTA3311.a" "clipLibrary1.cel[0].cev[423].cevr";
connectAttr "animCurveTA3312.a" "clipLibrary1.cel[0].cev[424].cevr";
connectAttr "animCurveTA3313.a" "clipLibrary1.cel[0].cev[425].cevr";
connectAttr "animCurveTU1741.a" "clipLibrary1.cel[0].cev[426].cevr";
connectAttr "animCurveTU1742.a" "clipLibrary1.cel[0].cev[427].cevr";
connectAttr "animCurveTU1743.a" "clipLibrary1.cel[0].cev[428].cevr";
connectAttr "animCurveTA3314.a" "clipLibrary1.cel[0].cev[429].cevr";
connectAttr "animCurveTA3315.a" "clipLibrary1.cel[0].cev[430].cevr";
connectAttr "animCurveTA3316.a" "clipLibrary1.cel[0].cev[431].cevr";
connectAttr "animCurveTA3317.a" "clipLibrary1.cel[0].cev[432].cevr";
connectAttr "animCurveTA3318.a" "clipLibrary1.cel[0].cev[433].cevr";
connectAttr "animCurveTA3319.a" "clipLibrary1.cel[0].cev[434].cevr";
connectAttr "animCurveTU1744.a" "clipLibrary1.cel[0].cev[435].cevr";
connectAttr "animCurveTU1745.a" "clipLibrary1.cel[0].cev[436].cevr";
connectAttr "animCurveTU1746.a" "clipLibrary1.cel[0].cev[437].cevr";
connectAttr "animCurveTA3320.a" "clipLibrary1.cel[0].cev[438].cevr";
connectAttr "animCurveTA3321.a" "clipLibrary1.cel[0].cev[439].cevr";
connectAttr "animCurveTA3322.a" "clipLibrary1.cel[0].cev[440].cevr";
connectAttr "animCurveTA3323.a" "clipLibrary1.cel[0].cev[441].cevr";
connectAttr "animCurveTA3324.a" "clipLibrary1.cel[0].cev[442].cevr";
connectAttr "animCurveTA3325.a" "clipLibrary1.cel[0].cev[443].cevr";
connectAttr "animCurveTU1747.a" "clipLibrary1.cel[0].cev[444].cevr";
connectAttr "animCurveTU1748.a" "clipLibrary1.cel[0].cev[445].cevr";
connectAttr "animCurveTU1749.a" "clipLibrary1.cel[0].cev[446].cevr";
connectAttr "animCurveTA3326.a" "clipLibrary1.cel[0].cev[447].cevr";
connectAttr "animCurveTA3327.a" "clipLibrary1.cel[0].cev[448].cevr";
connectAttr "animCurveTA3328.a" "clipLibrary1.cel[0].cev[449].cevr";
connectAttr "animCurveTA3329.a" "clipLibrary1.cel[0].cev[450].cevr";
connectAttr "animCurveTA3330.a" "clipLibrary1.cel[0].cev[451].cevr";
connectAttr "animCurveTA3331.a" "clipLibrary1.cel[0].cev[452].cevr";
connectAttr "animCurveTU1750.a" "clipLibrary1.cel[0].cev[453].cevr";
connectAttr "animCurveTU1751.a" "clipLibrary1.cel[0].cev[454].cevr";
connectAttr "animCurveTU1752.a" "clipLibrary1.cel[0].cev[455].cevr";
connectAttr "animCurveTA3332.a" "clipLibrary1.cel[0].cev[456].cevr";
connectAttr "animCurveTA3333.a" "clipLibrary1.cel[0].cev[457].cevr";
connectAttr "animCurveTA3334.a" "clipLibrary1.cel[0].cev[458].cevr";
connectAttr "animCurveTA3335.a" "clipLibrary1.cel[0].cev[459].cevr";
connectAttr "animCurveTA3336.a" "clipLibrary1.cel[0].cev[460].cevr";
connectAttr "animCurveTA3337.a" "clipLibrary1.cel[0].cev[461].cevr";
connectAttr "animCurveTU1753.a" "clipLibrary1.cel[0].cev[462].cevr";
connectAttr "animCurveTU1754.a" "clipLibrary1.cel[0].cev[463].cevr";
connectAttr "animCurveTU1755.a" "clipLibrary1.cel[0].cev[464].cevr";
connectAttr "animCurveTA3338.a" "clipLibrary1.cel[0].cev[465].cevr";
connectAttr "animCurveTA3339.a" "clipLibrary1.cel[0].cev[466].cevr";
connectAttr "animCurveTA3340.a" "clipLibrary1.cel[0].cev[467].cevr";
connectAttr "animCurveTA3341.a" "clipLibrary1.cel[0].cev[468].cevr";
connectAttr "animCurveTA3342.a" "clipLibrary1.cel[0].cev[469].cevr";
connectAttr "animCurveTA3343.a" "clipLibrary1.cel[0].cev[470].cevr";
connectAttr "animCurveTU1756.a" "clipLibrary1.cel[0].cev[471].cevr";
connectAttr "animCurveTU1757.a" "clipLibrary1.cel[0].cev[472].cevr";
connectAttr "animCurveTU1758.a" "clipLibrary1.cel[0].cev[473].cevr";
connectAttr "animCurveTA3344.a" "clipLibrary1.cel[0].cev[474].cevr";
connectAttr "animCurveTA3345.a" "clipLibrary1.cel[0].cev[475].cevr";
connectAttr "animCurveTA3346.a" "clipLibrary1.cel[0].cev[476].cevr";
connectAttr "animCurveTA3347.a" "clipLibrary1.cel[0].cev[477].cevr";
connectAttr "animCurveTA3348.a" "clipLibrary1.cel[0].cev[478].cevr";
connectAttr "animCurveTA3349.a" "clipLibrary1.cel[0].cev[479].cevr";
connectAttr "animCurveTU1759.a" "clipLibrary1.cel[0].cev[480].cevr";
connectAttr "animCurveTU1760.a" "clipLibrary1.cel[0].cev[481].cevr";
connectAttr "animCurveTU1761.a" "clipLibrary1.cel[0].cev[482].cevr";
connectAttr "animCurveTA3350.a" "clipLibrary1.cel[0].cev[483].cevr";
connectAttr "animCurveTA3351.a" "clipLibrary1.cel[0].cev[484].cevr";
connectAttr "animCurveTA3352.a" "clipLibrary1.cel[0].cev[485].cevr";
connectAttr "animCurveTA3353.a" "clipLibrary1.cel[0].cev[486].cevr";
connectAttr "animCurveTA3354.a" "clipLibrary1.cel[0].cev[487].cevr";
connectAttr "animCurveTA3355.a" "clipLibrary1.cel[0].cev[488].cevr";
connectAttr "animCurveTU1762.a" "clipLibrary1.cel[0].cev[489].cevr";
connectAttr "animCurveTU1763.a" "clipLibrary1.cel[0].cev[490].cevr";
connectAttr "animCurveTU1764.a" "clipLibrary1.cel[0].cev[491].cevr";
connectAttr "animCurveTA3356.a" "clipLibrary1.cel[0].cev[492].cevr";
connectAttr "animCurveTA3357.a" "clipLibrary1.cel[0].cev[493].cevr";
connectAttr "animCurveTA3358.a" "clipLibrary1.cel[0].cev[494].cevr";
connectAttr "animCurveTA3359.a" "clipLibrary1.cel[0].cev[495].cevr";
connectAttr "animCurveTA3360.a" "clipLibrary1.cel[0].cev[496].cevr";
connectAttr "animCurveTA3361.a" "clipLibrary1.cel[0].cev[497].cevr";
connectAttr "animCurveTU1765.a" "clipLibrary1.cel[0].cev[498].cevr";
connectAttr "animCurveTU1766.a" "clipLibrary1.cel[0].cev[499].cevr";
connectAttr "animCurveTU1767.a" "clipLibrary1.cel[0].cev[500].cevr";
connectAttr "animCurveTA3362.a" "clipLibrary1.cel[0].cev[501].cevr";
connectAttr "animCurveTA3363.a" "clipLibrary1.cel[0].cev[502].cevr";
connectAttr "animCurveTA3364.a" "clipLibrary1.cel[0].cev[503].cevr";
connectAttr "animCurveTA3365.a" "clipLibrary1.cel[0].cev[504].cevr";
connectAttr "animCurveTA3366.a" "clipLibrary1.cel[0].cev[505].cevr";
connectAttr "animCurveTA3367.a" "clipLibrary1.cel[0].cev[506].cevr";
connectAttr "animCurveTU1768.a" "clipLibrary1.cel[0].cev[507].cevr";
connectAttr "animCurveTU1769.a" "clipLibrary1.cel[0].cev[508].cevr";
connectAttr "animCurveTU1770.a" "clipLibrary1.cel[0].cev[509].cevr";
connectAttr "animCurveTA3368.a" "clipLibrary1.cel[0].cev[510].cevr";
connectAttr "animCurveTA3369.a" "clipLibrary1.cel[0].cev[511].cevr";
connectAttr "animCurveTA3370.a" "clipLibrary1.cel[0].cev[512].cevr";
connectAttr "animCurveTA3371.a" "clipLibrary1.cel[0].cev[513].cevr";
connectAttr "animCurveTA3372.a" "clipLibrary1.cel[0].cev[514].cevr";
connectAttr "animCurveTA3373.a" "clipLibrary1.cel[0].cev[515].cevr";
connectAttr "animCurveTU1771.a" "clipLibrary1.cel[0].cev[516].cevr";
connectAttr "animCurveTU1772.a" "clipLibrary1.cel[0].cev[517].cevr";
connectAttr "animCurveTU1773.a" "clipLibrary1.cel[0].cev[518].cevr";
connectAttr "animCurveTA3374.a" "clipLibrary1.cel[0].cev[519].cevr";
connectAttr "animCurveTA3375.a" "clipLibrary1.cel[0].cev[520].cevr";
connectAttr "animCurveTA3376.a" "clipLibrary1.cel[0].cev[521].cevr";
connectAttr "animCurveTA3377.a" "clipLibrary1.cel[0].cev[522].cevr";
connectAttr "animCurveTA3378.a" "clipLibrary1.cel[0].cev[523].cevr";
connectAttr "animCurveTA3379.a" "clipLibrary1.cel[0].cev[524].cevr";
connectAttr "animCurveTU1774.a" "clipLibrary1.cel[0].cev[525].cevr";
connectAttr "animCurveTU1775.a" "clipLibrary1.cel[0].cev[526].cevr";
connectAttr "animCurveTU1776.a" "clipLibrary1.cel[0].cev[527].cevr";
connectAttr "animCurveTA3380.a" "clipLibrary1.cel[0].cev[528].cevr";
connectAttr "animCurveTA3381.a" "clipLibrary1.cel[0].cev[529].cevr";
connectAttr "animCurveTA3382.a" "clipLibrary1.cel[0].cev[530].cevr";
connectAttr "animCurveTA3383.a" "clipLibrary1.cel[0].cev[531].cevr";
connectAttr "animCurveTA3384.a" "clipLibrary1.cel[0].cev[532].cevr";
connectAttr "animCurveTA3385.a" "clipLibrary1.cel[0].cev[533].cevr";
connectAttr "animCurveTU1777.a" "clipLibrary1.cel[0].cev[534].cevr";
connectAttr "animCurveTU1778.a" "clipLibrary1.cel[0].cev[535].cevr";
connectAttr "animCurveTU1779.a" "clipLibrary1.cel[0].cev[536].cevr";
connectAttr "animCurveTA3386.a" "clipLibrary1.cel[0].cev[537].cevr";
connectAttr "animCurveTA3387.a" "clipLibrary1.cel[0].cev[538].cevr";
connectAttr "animCurveTA3388.a" "clipLibrary1.cel[0].cev[539].cevr";
connectAttr "animCurveTU1780.a" "clipLibrary1.cel[0].cev[540].cevr";
connectAttr "animCurveTU1781.a" "clipLibrary1.cel[0].cev[541].cevr";
connectAttr "animCurveTU1782.a" "clipLibrary1.cel[0].cev[542].cevr";
connectAttr "animCurveTA3389.a" "clipLibrary1.cel[0].cev[543].cevr";
connectAttr "animCurveTA3390.a" "clipLibrary1.cel[0].cev[544].cevr";
connectAttr "animCurveTA3391.a" "clipLibrary1.cel[0].cev[545].cevr";
connectAttr "animCurveTL1153.a" "clipLibrary1.cel[0].cev[546].cevr";
connectAttr "animCurveTL1154.a" "clipLibrary1.cel[0].cev[547].cevr";
connectAttr "animCurveTL1155.a" "clipLibrary1.cel[0].cev[548].cevr";
connectAttr "animCurveTU1783.a" "clipLibrary1.cel[0].cev[549].cevr";
connectAttr "animCurveTU1784.a" "clipLibrary1.cel[0].cev[550].cevr";
connectAttr "animCurveTU1785.a" "clipLibrary1.cel[0].cev[551].cevr";
connectAttr "animCurveTA3392.a" "clipLibrary1.cel[0].cev[552].cevr";
connectAttr "animCurveTA3393.a" "clipLibrary1.cel[0].cev[553].cevr";
connectAttr "animCurveTA3394.a" "clipLibrary1.cel[0].cev[554].cevr";
connectAttr "animCurveTL1156.a" "clipLibrary1.cel[0].cev[555].cevr";
connectAttr "animCurveTL1157.a" "clipLibrary1.cel[0].cev[556].cevr";
connectAttr "animCurveTL1158.a" "clipLibrary1.cel[0].cev[557].cevr";
connectAttr "animCurveTA3395.a" "clipLibrary1.cel[0].cev[558].cevr";
connectAttr "animCurveTA3396.a" "clipLibrary1.cel[0].cev[559].cevr";
connectAttr "animCurveTA3397.a" "clipLibrary1.cel[0].cev[560].cevr";
connectAttr "animCurveTU1786.a" "clipLibrary1.cel[0].cev[561].cevr";
connectAttr "animCurveTU1787.a" "clipLibrary1.cel[0].cev[562].cevr";
connectAttr "animCurveTU1788.a" "clipLibrary1.cel[0].cev[563].cevr";
connectAttr "animCurveTA3398.a" "clipLibrary1.cel[0].cev[564].cevr";
connectAttr "animCurveTA3399.a" "clipLibrary1.cel[0].cev[565].cevr";
connectAttr "animCurveTA3400.a" "clipLibrary1.cel[0].cev[566].cevr";
connectAttr "animCurveTA3401.a" "clipLibrary1.cel[0].cev[567].cevr";
connectAttr "animCurveTA3402.a" "clipLibrary1.cel[0].cev[568].cevr";
connectAttr "animCurveTA3403.a" "clipLibrary1.cel[0].cev[569].cevr";
connectAttr "animCurveTU1789.a" "clipLibrary1.cel[0].cev[570].cevr";
connectAttr "animCurveTU1790.a" "clipLibrary1.cel[0].cev[571].cevr";
connectAttr "animCurveTU1791.a" "clipLibrary1.cel[0].cev[572].cevr";
connectAttr "animCurveTA3404.a" "clipLibrary1.cel[0].cev[573].cevr";
connectAttr "animCurveTA3405.a" "clipLibrary1.cel[0].cev[574].cevr";
connectAttr "animCurveTA3406.a" "clipLibrary1.cel[0].cev[575].cevr";
connectAttr "animCurveTA3407.a" "clipLibrary1.cel[0].cev[576].cevr";
connectAttr "animCurveTA3408.a" "clipLibrary1.cel[0].cev[577].cevr";
connectAttr "animCurveTA3409.a" "clipLibrary1.cel[0].cev[578].cevr";
connectAttr "animCurveTU1792.a" "clipLibrary1.cel[0].cev[579].cevr";
connectAttr "animCurveTU1793.a" "clipLibrary1.cel[0].cev[580].cevr";
connectAttr "animCurveTU1794.a" "clipLibrary1.cel[0].cev[581].cevr";
connectAttr "animCurveTA3410.a" "clipLibrary1.cel[0].cev[582].cevr";
connectAttr "animCurveTA3411.a" "clipLibrary1.cel[0].cev[583].cevr";
connectAttr "animCurveTA3412.a" "clipLibrary1.cel[0].cev[584].cevr";
connectAttr "animCurveTA3413.a" "clipLibrary1.cel[0].cev[585].cevr";
connectAttr "animCurveTA3414.a" "clipLibrary1.cel[0].cev[586].cevr";
connectAttr "animCurveTA3415.a" "clipLibrary1.cel[0].cev[587].cevr";
connectAttr "animCurveTU1795.a" "clipLibrary1.cel[0].cev[588].cevr";
connectAttr "animCurveTU1796.a" "clipLibrary1.cel[0].cev[589].cevr";
connectAttr "animCurveTU1797.a" "clipLibrary1.cel[0].cev[590].cevr";
connectAttr "animCurveTA3416.a" "clipLibrary1.cel[0].cev[591].cevr";
connectAttr "animCurveTA3417.a" "clipLibrary1.cel[0].cev[592].cevr";
connectAttr "animCurveTA3418.a" "clipLibrary1.cel[0].cev[593].cevr";
connectAttr "animCurveTA3419.a" "clipLibrary1.cel[0].cev[594].cevr";
connectAttr "animCurveTA3420.a" "clipLibrary1.cel[0].cev[595].cevr";
connectAttr "animCurveTA3421.a" "clipLibrary1.cel[0].cev[596].cevr";
connectAttr "animCurveTU1798.a" "clipLibrary1.cel[0].cev[597].cevr";
connectAttr "animCurveTU1799.a" "clipLibrary1.cel[0].cev[598].cevr";
connectAttr "animCurveTU1800.a" "clipLibrary1.cel[0].cev[599].cevr";
connectAttr "animCurveTA3422.a" "clipLibrary1.cel[0].cev[600].cevr";
connectAttr "animCurveTA3423.a" "clipLibrary1.cel[0].cev[601].cevr";
connectAttr "animCurveTA3424.a" "clipLibrary1.cel[0].cev[602].cevr";
connectAttr "animCurveTA3425.a" "clipLibrary1.cel[0].cev[603].cevr";
connectAttr "animCurveTA3426.a" "clipLibrary1.cel[0].cev[604].cevr";
connectAttr "animCurveTA3427.a" "clipLibrary1.cel[0].cev[605].cevr";
connectAttr "animCurveTU1801.a" "clipLibrary1.cel[0].cev[606].cevr";
connectAttr "animCurveTU1802.a" "clipLibrary1.cel[0].cev[607].cevr";
connectAttr "animCurveTU1803.a" "clipLibrary1.cel[0].cev[608].cevr";
connectAttr "animCurveTA3428.a" "clipLibrary1.cel[0].cev[609].cevr";
connectAttr "animCurveTA3429.a" "clipLibrary1.cel[0].cev[610].cevr";
connectAttr "animCurveTA3430.a" "clipLibrary1.cel[0].cev[611].cevr";
connectAttr "animCurveTA3431.a" "clipLibrary1.cel[0].cev[612].cevr";
connectAttr "animCurveTA3432.a" "clipLibrary1.cel[0].cev[613].cevr";
connectAttr "animCurveTA3433.a" "clipLibrary1.cel[0].cev[614].cevr";
connectAttr "animCurveTU1804.a" "clipLibrary1.cel[0].cev[615].cevr";
connectAttr "animCurveTU1805.a" "clipLibrary1.cel[0].cev[616].cevr";
connectAttr "animCurveTU1806.a" "clipLibrary1.cel[0].cev[617].cevr";
connectAttr "animCurveTA3434.a" "clipLibrary1.cel[0].cev[618].cevr";
connectAttr "animCurveTA3435.a" "clipLibrary1.cel[0].cev[619].cevr";
connectAttr "animCurveTA3436.a" "clipLibrary1.cel[0].cev[620].cevr";
connectAttr "animCurveTA3437.a" "clipLibrary1.cel[0].cev[621].cevr";
connectAttr "animCurveTA3438.a" "clipLibrary1.cel[0].cev[622].cevr";
connectAttr "animCurveTA3439.a" "clipLibrary1.cel[0].cev[623].cevr";
connectAttr "animCurveTU1807.a" "clipLibrary1.cel[0].cev[624].cevr";
connectAttr "animCurveTU1808.a" "clipLibrary1.cel[0].cev[625].cevr";
connectAttr "animCurveTU1809.a" "clipLibrary1.cel[0].cev[626].cevr";
connectAttr "animCurveTA3440.a" "clipLibrary1.cel[0].cev[627].cevr";
connectAttr "animCurveTA3441.a" "clipLibrary1.cel[0].cev[628].cevr";
connectAttr "animCurveTA3442.a" "clipLibrary1.cel[0].cev[629].cevr";
connectAttr "animCurveTA3443.a" "clipLibrary1.cel[0].cev[630].cevr";
connectAttr "animCurveTA3444.a" "clipLibrary1.cel[0].cev[631].cevr";
connectAttr "animCurveTA3445.a" "clipLibrary1.cel[0].cev[632].cevr";
connectAttr "animCurveTU1810.a" "clipLibrary1.cel[0].cev[633].cevr";
connectAttr "animCurveTU1811.a" "clipLibrary1.cel[0].cev[634].cevr";
connectAttr "animCurveTU1812.a" "clipLibrary1.cel[0].cev[635].cevr";
connectAttr "animCurveTA3446.a" "clipLibrary1.cel[0].cev[636].cevr";
connectAttr "animCurveTA3447.a" "clipLibrary1.cel[0].cev[637].cevr";
connectAttr "animCurveTA3448.a" "clipLibrary1.cel[0].cev[638].cevr";
connectAttr "animCurveTU1813.a" "clipLibrary1.cel[0].cev[639].cevr";
connectAttr "animCurveTU1814.a" "clipLibrary1.cel[0].cev[640].cevr";
connectAttr "animCurveTU1815.a" "clipLibrary1.cel[0].cev[641].cevr";
connectAttr "animCurveTA3449.a" "clipLibrary1.cel[0].cev[642].cevr";
connectAttr "animCurveTA3450.a" "clipLibrary1.cel[0].cev[643].cevr";
connectAttr "animCurveTA3451.a" "clipLibrary1.cel[0].cev[644].cevr";
connectAttr "animCurveTL1159.a" "clipLibrary1.cel[0].cev[645].cevr";
connectAttr "animCurveTL1160.a" "clipLibrary1.cel[0].cev[646].cevr";
connectAttr "animCurveTL1161.a" "clipLibrary1.cel[0].cev[647].cevr";
connectAttr "animCurveTU1816.a" "clipLibrary1.cel[0].cev[648].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of death.ma
