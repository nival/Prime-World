//Maya ASCII 2008 scene
//Name: attack.ma
//Last modified: Mon, Aug 17, 2009 11:06:38 PM
//Codeset: 1251
requires maya "2008";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Unlimited 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200802250025-718075";
fileInfo "osv" "Microsoft Windows XP Service Pack 2 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 290 ".cel[0].cev";
	setAttr ".cd[0].cm" -type "characterMapping" 672 "money_world_CTRL.woldCharSwitch" 
		0 1 "money_world_CTRL.rotateZ" 2 1 "money_world_CTRL.rotateY" 
		2 2 "money_world_CTRL.rotateX" 2 3 "money_world_CTRL.translateZ" 
		1 1 "money_world_CTRL.translateY" 1 2 "money_world_CTRL.translateX" 
		1 3 "WagCurveSplineTail_M.increment" 0 2 "WagCurveSplineTail_M.multiply" 
		0 3 "WagCurveSplineTail_M.timeOffset" 0 4 "WagCurveSplineTail_M.enable" 
		0 5 "WagCurveSplineTail_M.rotateZ" 2 4 "WagCurveSplineTail_M.rotateY" 
		2 5 "WagCurveSplineTail_M.rotateX" 2 6 "FKIKLegBack_L.IKVis" 
		0 6 "FKIKLegBack_L.FKVis" 0 7 "FKIKLegBack_L.FKIKBlend" 0 
		8 "FKIKLegFront_L.IKVis" 0 9 "FKIKLegFront_L.FKVis" 0 10 "FKIKLegFront_L.FKIKBlend" 
		0 11 "FKIKSpine_M.IKVis" 0 12 "FKIKSpine_M.FKVis" 0 13 "FKIKSpine_M.FKIKBlend" 
		0 14 "FKIKLegBack_R.IKVis" 0 15 "FKIKLegBack_R.FKVis" 0 16 "FKIKLegBack_R.FKIKBlend" 
		0 17 "FKIKSplineTail_M.IKVis" 0 18 "FKIKSplineTail_M.FKVis" 0 
		19 "FKIKSplineTail_M.FKIKBlend" 0 20 "FKIKLegFront_R.IKVis" 0 21 "FKIKLegFront_R.FKVis" 
		0 22 "FKIKLegFront_R.FKIKBlend" 0 23 "PoleLegBack_L.follow" 0 
		24 "PoleLegBack_L.translateZ" 1 4 "PoleLegBack_L.translateY" 1 
		5 "PoleLegBack_L.translateX" 1 6 "PoleExtraLegBack_L.translateZ" 1 
		7 "PoleExtraLegBack_L.translateY" 1 8 "PoleExtraLegBack_L.translateX" 
		1 9 "IKLegBackBall_L.rotateX" 2 7 "IKExtraLegBackBall_L.rotateZ" 
		2 8 "IKExtraLegBackBall_L.rotateY" 2 9 "IKExtraLegBackBall_L.rotateX" 
		2 10 "IKLegBackHeel_L.rotateZ" 2 11 "IKLegBackHeel_L.rotateY" 2 
		12 "IKLegBackHeel_L.rotateX" 2 13 "IKExtraLegBackHeel_L.rotateZ" 2 
		14 "IKExtraLegBackHeel_L.rotateY" 2 15 "IKExtraLegBackHeel_L.rotateX" 
		2 16 "IKLegBack_L.Lenght2" 0 25 "IKLegBack_L.Lenght1" 0 26 "IKLegBack_L.antiPop" 
		0 27 "IKLegBack_L.stretchy" 0 28 "IKLegBack_L.legAim" 0 29 "IKLegBack_L.rollAngle" 
		0 30 "IKLegBack_L.roll" 0 31 "IKLegBack_L.swivel" 0 32 "IKLegBack_L.rotateZ" 
		2 17 "IKLegBack_L.rotateY" 2 18 "IKLegBack_L.rotateX" 2 19 "IKLegBack_L.translateZ" 
		1 10 "IKLegBack_L.translateY" 1 11 "IKLegBack_L.translateX" 1 
		12 "IKExtraLegBack_L.rotateZ" 2 20 "IKExtraLegBack_L.rotateY" 2 
		21 "IKExtraLegBack_L.rotateX" 2 22 "IKExtraLegBack_L.translateZ" 1 
		13 "IKExtraLegBack_L.translateY" 1 14 "IKExtraLegBack_L.translateX" 
		1 15 "PoleLegFront_L.follow" 0 33 "PoleLegFront_L.translateZ" 1 
		16 "PoleLegFront_L.translateY" 1 17 "PoleLegFront_L.translateX" 1 
		18 "PoleExtraLegFront_L.translateZ" 1 19 "PoleExtraLegFront_L.translateY" 
		1 20 "PoleExtraLegFront_L.translateX" 1 21 "IKLegFrontBall_L.rotateX" 
		2 23 "IKExtraLegFrontBall_L.rotateZ" 2 24 "IKExtraLegFrontBall_L.rotateY" 
		2 25 "IKExtraLegFrontBall_L.rotateX" 2 26 "IKLegFrontHeel_L.rotateZ" 
		2 27 "IKLegFrontHeel_L.rotateY" 2 28 "IKLegFrontHeel_L.rotateX" 
		2 29 "IKExtraLegFrontHeel_L.rotateZ" 2 30 "IKExtraLegFrontHeel_L.rotateY" 
		2 31 "IKExtraLegFrontHeel_L.rotateX" 2 32 "IKLegFront_L.Lenght2" 
		0 34 "IKLegFront_L.Lenght1" 0 35 "IKLegFront_L.antiPop" 0 
		36 "IKLegFront_L.stretchy" 0 37 "IKLegFront_L.legAim" 0 38 "IKLegFront_L.rollAngle" 
		0 39 "IKLegFront_L.roll" 0 40 "IKLegFront_L.swivel" 0 41 "IKLegFront_L.rotateZ" 
		2 33 "IKLegFront_L.rotateY" 2 34 "IKLegFront_L.rotateX" 2 
		35 "IKLegFront_L.translateZ" 1 22 "IKLegFront_L.translateY" 1 23 "IKLegFront_L.translateX" 
		1 24 "IKExtraLegFront_L.rotateZ" 2 36 "IKExtraLegFront_L.rotateY" 
		2 37 "IKExtraLegFront_L.rotateX" 2 38 "IKExtraLegFront_L.translateZ" 
		1 25 "IKExtraLegFront_L.translateY" 1 26 "IKExtraLegFront_L.translateX" 
		1 27 "IKSpine4_M.stretchy" 0 42 "IKSpine4_M.stiff" 0 43 "IKSpine4_M.rotateZ" 
		2 39 "IKSpine4_M.rotateY" 2 40 "IKSpine4_M.rotateX" 2 41 "IKSpine4_M.translateZ" 
		1 28 "IKSpine4_M.translateY" 1 29 "IKSpine4_M.translateX" 1 
		30 "IKExtraSpine4_M.scaleZ" 0 44 "IKExtraSpine4_M.scaleY" 0 45 "IKExtraSpine4_M.scaleX" 
		0 46 "IKExtraSpine4_M.rotateZ" 2 42 "IKExtraSpine4_M.rotateY" 2 
		43 "IKExtraSpine4_M.rotateX" 2 44 "IKExtraSpine4_M.translateZ" 1 
		31 "IKExtraSpine4_M.translateY" 1 32 "IKExtraSpine4_M.translateX" 1 
		33 "IKExtraSpine4_M.visibility" 0 47 "IKSpine2_M.stiff" 0 48 "IKSpine2_M.rotateZ" 
		2 45 "IKSpine2_M.rotateY" 2 46 "IKSpine2_M.rotateX" 2 47 "IKSpine2_M.translateZ" 
		1 34 "IKSpine2_M.translateY" 1 35 "IKSpine2_M.translateX" 1 
		36 "IKExtraSpine2_M.scaleZ" 0 49 "IKExtraSpine2_M.scaleY" 0 50 "IKExtraSpine2_M.scaleX" 
		0 51 "IKExtraSpine2_M.rotateZ" 2 48 "IKExtraSpine2_M.rotateY" 2 
		49 "IKExtraSpine2_M.rotateX" 2 50 "IKExtraSpine2_M.translateZ" 1 
		37 "IKExtraSpine2_M.translateY" 1 38 "IKExtraSpine2_M.translateX" 1 
		39 "IKExtraSpine2_M.visibility" 0 52 "IKSpine0_M.stiff" 0 53 "IKSpine0_M.rotateZ" 
		2 51 "IKSpine0_M.rotateY" 2 52 "IKSpine0_M.rotateX" 2 53 "IKSpine0_M.translateZ" 
		1 40 "IKSpine0_M.translateY" 1 41 "IKSpine0_M.translateX" 1 
		42 "IKExtraSpine0_M.scaleZ" 0 54 "IKExtraSpine0_M.scaleY" 0 55 "IKExtraSpine0_M.scaleX" 
		0 56 "IKExtraSpine0_M.rotateZ" 2 54 "IKExtraSpine0_M.rotateY" 2 
		55 "IKExtraSpine0_M.rotateX" 2 56 "IKExtraSpine0_M.translateZ" 1 
		43 "IKExtraSpine0_M.translateY" 1 44 "IKExtraSpine0_M.translateX" 1 
		45 "IKExtraSpine0_M.visibility" 0 57 "PoleLegBack_R.follow" 0 58 "PoleLegBack_R.translateZ" 
		1 46 "PoleLegBack_R.translateY" 1 47 "PoleLegBack_R.translateX" 
		1 48 "PoleExtraLegBack_R.translateZ" 1 49 "PoleExtraLegBack_R.translateY" 
		1 50 "PoleExtraLegBack_R.translateX" 1 51 "IKLegBackBall_R.rotateX" 
		2 57 "IKExtraLegBackBall_R.rotateZ" 2 58 "IKExtraLegBackBall_R.rotateY" 
		2 59 "IKExtraLegBackBall_R.rotateX" 2 60 "IKLegBackHeel_R.rotateZ" 
		2 61 "IKLegBackHeel_R.rotateY" 2 62 "IKLegBackHeel_R.rotateX" 2 
		63 "IKExtraLegBackHeel_R.rotateZ" 2 64 "IKExtraLegBackHeel_R.rotateY" 
		2 65 "IKExtraLegBackHeel_R.rotateX" 2 66 "IKLegBack_R.Lenght2" 
		0 59 "IKLegBack_R.Lenght1" 0 60 "IKLegBack_R.antiPop" 0 61 "IKLegBack_R.stretchy" 
		0 62 "IKLegBack_R.legAim" 0 63 "IKLegBack_R.rollAngle" 0 64 "IKLegBack_R.roll" 
		0 65 "IKLegBack_R.swivel" 0 66 "IKLegBack_R.rotateZ" 2 67 "IKLegBack_R.rotateY" 
		2 68 "IKLegBack_R.rotateX" 2 69 "IKLegBack_R.translateZ" 1 
		52 "IKLegBack_R.translateY" 1 53 "IKLegBack_R.translateX" 1 54 "IKExtraLegBack_R.rotateZ" 
		2 70 "IKExtraLegBack_R.rotateY" 2 71 "IKExtraLegBack_R.rotateX" 
		2 72 "IKExtraLegBack_R.translateZ" 1 55 "IKExtraLegBack_R.translateY" 
		1 56 "IKExtraLegBack_R.translateX" 1 57 "IKSplineTail3_M.stretchy" 
		0 67 "IKSplineTail3_M.twist" 0 68 "IKSplineTail3_M.follow" 0 
		69 "IKSplineTail3_M.rotateZ" 2 73 "IKSplineTail3_M.rotateY" 2 74 "IKSplineTail3_M.rotateX" 
		2 75 "IKSplineTail3_M.translateZ" 1 58 "IKSplineTail3_M.translateY" 
		1 59 "IKSplineTail3_M.translateX" 1 60 "IKExtraSplineTail3_M.scaleZ" 
		0 70 "IKExtraSplineTail3_M.scaleY" 0 71 "IKExtraSplineTail3_M.scaleX" 
		0 72 "IKExtraSplineTail3_M.rotateZ" 2 76 "IKExtraSplineTail3_M.rotateY" 
		2 77 "IKExtraSplineTail3_M.rotateX" 2 78 "IKExtraSplineTail3_M.translateZ" 
		1 61 "IKExtraSplineTail3_M.translateY" 1 62 "IKExtraSplineTail3_M.translateX" 
		1 63 "IKExtraSplineTail3_M.visibility" 0 73 "IKSplineTail2_M.follow" 
		0 74 "IKSplineTail2_M.translateZ" 1 64 "IKSplineTail2_M.translateY" 
		1 65 "IKSplineTail2_M.translateX" 1 66 "IKExtraSplineTail2_M.scaleZ" 
		0 75 "IKExtraSplineTail2_M.scaleY" 0 76 "IKExtraSplineTail2_M.scaleX" 
		0 77 "IKExtraSplineTail2_M.rotateZ" 2 79 "IKExtraSplineTail2_M.rotateY" 
		2 80 "IKExtraSplineTail2_M.rotateX" 2 81 "IKExtraSplineTail2_M.translateZ" 
		1 67 "IKExtraSplineTail2_M.translateY" 1 68 "IKExtraSplineTail2_M.translateX" 
		1 69 "IKExtraSplineTail2_M.visibility" 0 78 "IKSplineTail1_M.follow" 
		0 79 "IKSplineTail1_M.translateZ" 1 70 "IKSplineTail1_M.translateY" 
		1 71 "IKSplineTail1_M.translateX" 1 72 "IKExtraSplineTail1_M.scaleZ" 
		0 80 "IKExtraSplineTail1_M.scaleY" 0 81 "IKExtraSplineTail1_M.scaleX" 
		0 82 "IKExtraSplineTail1_M.rotateZ" 2 82 "IKExtraSplineTail1_M.rotateY" 
		2 83 "IKExtraSplineTail1_M.rotateX" 2 84 "IKExtraSplineTail1_M.translateZ" 
		1 73 "IKExtraSplineTail1_M.translateY" 1 74 "IKExtraSplineTail1_M.translateX" 
		1 75 "IKExtraSplineTail1_M.visibility" 0 83 "PoleLegFront_R.follow" 
		0 84 "PoleLegFront_R.translateZ" 1 76 "PoleLegFront_R.translateY" 
		1 77 "PoleLegFront_R.translateX" 1 78 "PoleExtraLegFront_R.translateZ" 
		1 79 "PoleExtraLegFront_R.translateY" 1 80 "PoleExtraLegFront_R.translateX" 
		1 81 "IKLegFrontBall_R.rotateX" 2 85 "IKExtraLegFrontBall_R.rotateZ" 
		2 86 "IKExtraLegFrontBall_R.rotateY" 2 87 "IKExtraLegFrontBall_R.rotateX" 
		2 88 "IKLegFrontHeel_R.rotateZ" 2 89 "IKLegFrontHeel_R.rotateY" 
		2 90 "IKLegFrontHeel_R.rotateX" 2 91 "IKExtraLegFrontHeel_R.rotateZ" 
		2 92 "IKExtraLegFrontHeel_R.rotateY" 2 93 "IKExtraLegFrontHeel_R.rotateX" 
		2 94 "IKLegFront_R.Lenght2" 0 85 "IKLegFront_R.Lenght1" 0 
		86 "IKLegFront_R.antiPop" 0 87 "IKLegFront_R.stretchy" 0 88 "IKLegFront_R.legAim" 
		0 89 "IKLegFront_R.rollAngle" 0 90 "IKLegFront_R.roll" 0 91 "IKLegFront_R.swivel" 
		0 92 "IKLegFront_R.rotateZ" 2 95 "IKLegFront_R.rotateY" 2 
		96 "IKLegFront_R.rotateX" 2 97 "IKLegFront_R.translateZ" 1 82 "IKLegFront_R.translateY" 
		1 83 "IKLegFront_R.translateX" 1 84 "IKExtraLegFront_R.rotateZ" 
		2 98 "IKExtraLegFront_R.rotateY" 2 99 "IKExtraLegFront_R.rotateX" 
		2 100 "IKExtraLegFront_R.translateZ" 1 85 "IKExtraLegFront_R.translateY" 
		1 86 "IKExtraLegFront_R.translateX" 1 87 "HipSwingerRoot_M.rotateZ" 
		2 101 "HipSwingerRoot_M.rotateY" 2 102 "HipSwingerRoot_M.rotateX" 
		2 103 "money_CTRL.rotateZ" 2 104 "money_CTRL.rotateY" 2 105 "money_CTRL.rotateX" 
		2 106 "money_CTRL.translateZ" 1 88 "money_CTRL.translateY" 1 
		89 "money_CTRL.translateX" 1 90 "bag_CTRL.rotateZ" 2 107 "bag_CTRL.rotateY" 
		2 108 "bag_CTRL.rotateX" 2 109 "bag_CTRL.translateZ" 1 91 "bag_CTRL.translateY" 
		1 92 "bag_CTRL.translateX" 1 93 "FKChest_M.scaleZ" 0 93 "FKChest_M.scaleY" 
		0 94 "FKChest_M.scaleX" 0 95 "FKChest_M.rotateZ" 2 110 "FKChest_M.rotateY" 
		2 111 "FKChest_M.rotateX" 2 112 "FKExtraChest_M.rotateZ" 2 113 "FKExtraChest_M.rotateY" 
		2 114 "FKExtraChest_M.rotateX" 2 115 "FKBackB_M.scaleZ" 0 96 "FKBackB_M.scaleY" 
		0 97 "FKBackB_M.scaleX" 0 98 "FKBackB_M.rotateZ" 2 116 "FKBackB_M.rotateY" 
		2 117 "FKBackB_M.rotateX" 2 118 "FKExtraBackB_M.rotateZ" 2 119 "FKExtraBackB_M.rotateY" 
		2 120 "FKExtraBackB_M.rotateX" 2 121 "FKBackA_M.scaleZ" 0 99 "FKBackA_M.scaleY" 
		0 100 "FKBackA_M.scaleX" 0 101 "FKBackA_M.rotateZ" 2 122 "FKBackA_M.rotateY" 
		2 123 "FKBackA_M.rotateX" 2 124 "FKExtraBackA_M.rotateZ" 2 125 "FKExtraBackA_M.rotateY" 
		2 126 "FKExtraBackA_M.rotateX" 2 127 "Center_M.CenterBtwFeet" 0 
		102 "Center_M.rotateZ" 2 128 "Center_M.rotateY" 2 129 "Center_M.rotateX" 
		2 130 "Center_M.translateZ" 1 94 "Center_M.translateY" 1 95 "Center_M.translateX" 
		1 96 "CenterExtra_M.rotateZ" 2 131 "CenterExtra_M.rotateY" 2 
		132 "CenterExtra_M.rotateX" 2 133 "CenterExtra_M.translateZ" 1 97 "CenterExtra_M.translateY" 
		1 98 "CenterExtra_M.translateX" 1 99 "FKbackFoot_L.scaleZ" 0 
		103 "FKbackFoot_L.scaleY" 0 104 "FKbackFoot_L.scaleX" 0 105 "FKbackFoot_L.rotateZ" 
		2 134 "FKbackFoot_L.rotateY" 2 135 "FKbackFoot_L.rotateX" 2 
		136 "FKExtrabackFoot_L.rotateZ" 2 137 "FKExtrabackFoot_L.rotateY" 2 
		138 "FKExtrabackFoot_L.rotateX" 2 139 "FKbackKnee_L.scaleZ" 0 106 "FKbackKnee_L.scaleY" 
		0 107 "FKbackKnee_L.scaleX" 0 108 "FKbackKnee_L.rotateZ" 2 140 "FKbackKnee_L.rotateY" 
		2 141 "FKbackKnee_L.rotateX" 2 142 "FKExtrabackKnee_L.rotateZ" 2 
		143 "FKExtrabackKnee_L.rotateY" 2 144 "FKExtrabackKnee_L.rotateX" 2 
		145 "FKbackHip_L.scaleZ" 0 109 "FKbackHip_L.scaleY" 0 110 "FKbackHip_L.scaleX" 
		0 111 "FKbackHip_L.rotateZ" 2 146 "FKbackHip_L.rotateY" 2 147 "FKbackHip_L.rotateX" 
		2 148 "FKExtrabackHip_L.rotateZ" 2 149 "FKExtrabackHip_L.rotateY" 
		2 150 "FKExtrabackHip_L.rotateX" 2 151 "FKRump_L.scaleZ" 0 112 "FKRump_L.scaleY" 
		0 113 "FKRump_L.scaleX" 0 114 "FKRump_L.rotateZ" 2 152 "FKRump_L.rotateY" 
		2 153 "FKRump_L.rotateX" 2 154 "FKRump_L.translateZ" 1 100 "FKRump_L.translateY" 
		1 101 "FKRump_L.translateX" 1 102 "FKExtraRump_L.scaleZ" 0 115 "FKExtraRump_L.scaleY" 
		0 116 "FKExtraRump_L.scaleX" 0 117 "FKExtraRump_L.rotateZ" 2 
		155 "FKExtraRump_L.rotateY" 2 156 "FKExtraRump_L.rotateX" 2 157 "FKExtraRump_L.translateZ" 
		1 103 "FKExtraRump_L.translateY" 1 104 "FKExtraRump_L.translateX" 
		1 105 "FKbackFoot_R.scaleZ" 0 118 "FKbackFoot_R.scaleY" 0 119 "FKbackFoot_R.scaleX" 
		0 120 "FKbackFoot_R.rotateZ" 2 158 "FKbackFoot_R.rotateY" 2 
		159 "FKbackFoot_R.rotateX" 2 160 "FKExtrabackFoot_R.rotateZ" 2 161 "FKExtrabackFoot_R.rotateY" 
		2 162 "FKExtrabackFoot_R.rotateX" 2 163 "FKbackKnee_R.scaleZ" 0 
		121 "FKbackKnee_R.scaleY" 0 122 "FKbackKnee_R.scaleX" 0 123 "FKbackKnee_R.rotateZ" 
		2 164 "FKbackKnee_R.rotateY" 2 165 "FKbackKnee_R.rotateX" 2 
		166 "FKExtrabackKnee_R.rotateZ" 2 167 "FKExtrabackKnee_R.rotateY" 2 
		168 "FKExtrabackKnee_R.rotateX" 2 169 "FKbackHip_R.scaleZ" 0 124 "FKbackHip_R.scaleY" 
		0 125 "FKbackHip_R.scaleX" 0 126 "FKbackHip_R.rotateZ" 2 170 "FKbackHip_R.rotateY" 
		2 171 "FKbackHip_R.rotateX" 2 172 "FKExtrabackHip_R.rotateZ" 2 
		173 "FKExtrabackHip_R.rotateY" 2 174 "FKExtrabackHip_R.rotateX" 2 
		175 "FKRump_R.scaleZ" 0 127 "FKRump_R.scaleY" 0 128 "FKRump_R.scaleX" 
		0 129 "FKRump_R.rotateZ" 2 176 "FKRump_R.rotateY" 2 177 "FKRump_R.rotateX" 
		2 178 "FKRump_R.translateZ" 1 106 "FKRump_R.translateY" 1 107 "FKRump_R.translateX" 
		1 108 "FKExtraRump_R.scaleZ" 0 130 "FKExtraRump_R.scaleY" 0 
		131 "FKExtraRump_R.scaleX" 0 132 "FKExtraRump_R.rotateZ" 2 179 "FKExtraRump_R.rotateY" 
		2 180 "FKExtraRump_R.rotateX" 2 181 "FKExtraRump_R.translateZ" 1 
		109 "FKExtraRump_R.translateY" 1 110 "FKExtraRump_R.translateX" 1 
		111 "FKTail5_M.scaleZ" 0 133 "FKTail5_M.scaleY" 0 134 "FKTail5_M.scaleX" 
		0 135 "FKTail5_M.rotateZ" 2 182 "FKTail5_M.rotateY" 2 183 "FKTail5_M.rotateX" 
		2 184 "FKExtraTail5_M.rotateZ" 2 185 "FKExtraTail5_M.rotateY" 2 
		186 "FKExtraTail5_M.rotateX" 2 187 "FKTail4_M.scaleZ" 0 136 "FKTail4_M.scaleY" 
		0 137 "FKTail4_M.scaleX" 0 138 "FKTail4_M.rotateZ" 2 188 "FKTail4_M.rotateY" 
		2 189 "FKTail4_M.rotateX" 2 190 "FKExtraTail4_M.rotateZ" 2 191 "FKExtraTail4_M.rotateY" 
		2 192 "FKExtraTail4_M.rotateX" 2 193 "FKTail3_M.scaleZ" 0 139 "FKTail3_M.scaleY" 
		0 140 "FKTail3_M.scaleX" 0 141 "FKTail3_M.rotateZ" 2 194 "FKTail3_M.rotateY" 
		2 195 "FKTail3_M.rotateX" 2 196 "FKExtraTail3_M.rotateZ" 2 197 "FKExtraTail3_M.rotateY" 
		2 198 "FKExtraTail3_M.rotateX" 2 199 "FKTail2_M.scaleZ" 0 142 "FKTail2_M.scaleY" 
		0 143 "FKTail2_M.scaleX" 0 144 "FKTail2_M.rotateZ" 2 200 "FKTail2_M.rotateY" 
		2 201 "FKTail2_M.rotateX" 2 202 "FKExtraTail2_M.rotateZ" 2 203 "FKExtraTail2_M.rotateY" 
		2 204 "FKExtraTail2_M.rotateX" 2 205 "FKTail1_M.scaleZ" 0 145 "FKTail1_M.scaleY" 
		0 146 "FKTail1_M.scaleX" 0 147 "FKTail1_M.rotateZ" 2 206 "FKTail1_M.rotateY" 
		2 207 "FKTail1_M.rotateX" 2 208 "FKExtraTail1_M.rotateZ" 2 209 "FKExtraTail1_M.rotateY" 
		2 210 "FKExtraTail1_M.rotateX" 2 211 "FKTail0_M.scaleZ" 0 148 "FKTail0_M.scaleY" 
		0 149 "FKTail0_M.scaleX" 0 150 "FKTail0_M.rotateZ" 2 212 "FKTail0_M.rotateY" 
		2 213 "FKTail0_M.rotateX" 2 214 "FKExtraTail0_M.rotateZ" 2 215 "FKExtraTail0_M.rotateY" 
		2 216 "FKExtraTail0_M.rotateX" 2 217 "FKfrontFoot_L.scaleZ" 0 
		151 "FKfrontFoot_L.scaleY" 0 152 "FKfrontFoot_L.scaleX" 0 153 "FKfrontFoot_L.rotateZ" 
		2 218 "FKfrontFoot_L.rotateY" 2 219 "FKfrontFoot_L.rotateX" 2 
		220 "FKExtrafrontFoot_L.rotateZ" 2 221 "FKExtrafrontFoot_L.rotateY" 2 
		222 "FKExtrafrontFoot_L.rotateX" 2 223 "FKfrontKnee_L.scaleZ" 0 154 "FKfrontKnee_L.scaleY" 
		0 155 "FKfrontKnee_L.scaleX" 0 156 "FKfrontKnee_L.rotateZ" 2 
		224 "FKfrontKnee_L.rotateY" 2 225 "FKfrontKnee_L.rotateX" 2 226 "FKExtrafrontKnee_L.rotateZ" 
		2 227 "FKExtrafrontKnee_L.rotateY" 2 228 "FKExtrafrontKnee_L.rotateX" 
		2 229 "FKfrontHip_L.scaleZ" 0 157 "FKfrontHip_L.scaleY" 0 158 "FKfrontHip_L.scaleX" 
		0 159 "FKfrontHip_L.rotateZ" 2 230 "FKfrontHip_L.rotateY" 2 
		231 "FKfrontHip_L.rotateX" 2 232 "FKExtrafrontHip_L.rotateZ" 2 233 "FKExtrafrontHip_L.rotateY" 
		2 234 "FKExtrafrontHip_L.rotateX" 2 235 "FKScapula_L.scaleZ" 0 
		160 "FKScapula_L.scaleY" 0 161 "FKScapula_L.scaleX" 0 162 "FKScapula_L.rotateZ" 
		2 236 "FKScapula_L.rotateY" 2 237 "FKScapula_L.rotateX" 2 238 "FKScapula_L.translateZ" 
		1 112 "FKScapula_L.translateY" 1 113 "FKScapula_L.translateX" 1 
		114 "FKExtraScapula_L.scaleZ" 0 163 "FKExtraScapula_L.scaleY" 0 164 "FKExtraScapula_L.scaleX" 
		0 165 "FKExtraScapula_L.rotateZ" 2 239 "FKExtraScapula_L.rotateY" 
		2 240 "FKExtraScapula_L.rotateX" 2 241 "FKExtraScapula_L.translateZ" 
		1 115 "FKExtraScapula_L.translateY" 1 116 "FKExtraScapula_L.translateX" 
		1 117 "FKfrontFoot_R.scaleZ" 0 166 "FKfrontFoot_R.scaleY" 0 
		167 "FKfrontFoot_R.scaleX" 0 168 "FKfrontFoot_R.rotateZ" 2 242 "FKfrontFoot_R.rotateY" 
		2 243 "FKfrontFoot_R.rotateX" 2 244 "FKExtrafrontFoot_R.rotateZ" 
		2 245 "FKExtrafrontFoot_R.rotateY" 2 246 "FKExtrafrontFoot_R.rotateX" 
		2 247 "FKfrontKnee_R.scaleZ" 0 169 "FKfrontKnee_R.scaleY" 0 
		170 "FKfrontKnee_R.scaleX" 0 171 "FKfrontKnee_R.rotateZ" 2 248 "FKfrontKnee_R.rotateY" 
		2 249 "FKfrontKnee_R.rotateX" 2 250 "FKExtrafrontKnee_R.rotateZ" 
		2 251 "FKExtrafrontKnee_R.rotateY" 2 252 "FKExtrafrontKnee_R.rotateX" 
		2 253 "FKfrontHip_R.scaleZ" 0 172 "FKfrontHip_R.scaleY" 0 173 "FKfrontHip_R.scaleX" 
		0 174 "FKfrontHip_R.rotateZ" 2 254 "FKfrontHip_R.rotateY" 2 
		255 "FKfrontHip_R.rotateX" 2 256 "FKExtrafrontHip_R.rotateZ" 2 257 "FKExtrafrontHip_R.rotateY" 
		2 258 "FKExtrafrontHip_R.rotateX" 2 259 "FKScapula_R.scaleZ" 0 
		175 "FKScapula_R.scaleY" 0 176 "FKScapula_R.scaleX" 0 177 "FKScapula_R.rotateZ" 
		2 260 "FKScapula_R.rotateY" 2 261 "FKScapula_R.rotateX" 2 262 "FKScapula_R.translateZ" 
		1 118 "FKScapula_R.translateY" 1 119 "FKScapula_R.translateX" 1 
		120 "FKExtraScapula_R.scaleZ" 0 178 "FKExtraScapula_R.scaleY" 0 179 "FKExtraScapula_R.scaleX" 
		0 180 "FKExtraScapula_R.rotateZ" 2 263 "FKExtraScapula_R.rotateY" 
		2 264 "FKExtraScapula_R.rotateX" 2 265 "FKExtraScapula_R.translateZ" 
		1 121 "FKExtraScapula_R.translateY" 1 122 "FKExtraScapula_R.translateX" 
		1 123 "sharf_L_C_CTRL.rotateZ" 2 266 "sharf_L_C_CTRL.rotateY" 2 
		267 "sharf_L_C_CTRL.rotateX" 2 268 "sharf_L_B_CTRL.rotateZ" 2 269 "sharf_L_B_CTRL.rotateY" 
		2 270 "sharf_L_B_CTRL.rotateX" 2 271 "sharf_L_A_CTRL.rotateZ" 2 
		272 "sharf_L_A_CTRL.rotateY" 2 273 "sharf_L_A_CTRL.rotateX" 2 274 "sharf_R_C_CTRL.rotateZ" 
		2 275 "sharf_R_C_CTRL.rotateY" 2 276 "sharf_R_C_CTRL.rotateX" 2 
		277 "sharf_R_B_CTRL.rotateZ" 2 278 "sharf_R_B_CTRL.rotateY" 2 279 "sharf_R_B_CTRL.rotateX" 
		2 280 "sharf_R_A_CTRL.rotateZ" 2 281 "sharf_R_A_CTRL.rotateY" 2 
		282 "sharf_R_A_CTRL.rotateX" 2 283 "us_L_CTRL.rotateZ" 2 284 "us_L_CTRL.rotateY" 
		2 285 "us_L_CTRL.rotateX" 2 286 "us_R_CTRL.rotateZ" 2 287 "us_R_CTRL.rotateY" 
		2 288 "us_R_CTRL.rotateX" 2 289 "FKEar_L.scaleZ" 0 181 "FKEar_L.scaleY" 
		0 182 "FKEar_L.scaleX" 0 183 "FKEar_L.rotateZ" 2 290 "FKEar_L.rotateY" 
		2 291 "FKEar_L.rotateX" 2 292 "FKExtraEar_L.rotateZ" 2 293 "FKExtraEar_L.rotateY" 
		2 294 "FKExtraEar_L.rotateX" 2 295 "FKEar_R.scaleZ" 0 184 "FKEar_R.scaleY" 
		0 185 "FKEar_R.scaleX" 0 186 "FKEar_R.rotateZ" 2 296 "FKEar_R.rotateY" 
		2 297 "FKEar_R.rotateX" 2 298 "FKExtraEar_R.rotateZ" 2 299 "FKExtraEar_R.rotateY" 
		2 300 "FKExtraEar_R.rotateX" 2 301 "hair_CTRL.rotateZ" 2 302 "hair_CTRL.rotateY" 
		2 303 "hair_CTRL.rotateX" 2 304 "hair_CTRL.translateZ" 1 124 "hair_CTRL.translateY" 
		1 125 "hair_CTRL.translateX" 1 126 "FKJaw_M.scaleZ" 0 187 "FKJaw_M.scaleY" 
		0 188 "FKJaw_M.scaleX" 0 189 "FKJaw_M.rotateZ" 2 305 "FKJaw_M.rotateY" 
		2 306 "FKJaw_M.rotateX" 2 307 "FKJaw_M.translateZ" 1 127 "FKJaw_M.translateY" 
		1 128 "FKJaw_M.translateX" 1 129 "FKExtraJaw_M.scaleZ" 0 190 "FKExtraJaw_M.scaleY" 
		0 191 "FKExtraJaw_M.scaleX" 0 192 "FKExtraJaw_M.rotateZ" 2 308 "FKExtraJaw_M.rotateY" 
		2 309 "FKExtraJaw_M.rotateX" 2 310 "FKExtraJaw_M.translateZ" 1 
		130 "FKExtraJaw_M.translateY" 1 131 "FKExtraJaw_M.translateX" 1 132 "FKHead_M.Global" 
		0 193 "FKHead_M.scaleZ" 0 194 "FKHead_M.scaleY" 0 195 "FKHead_M.scaleX" 
		0 196 "FKHead_M.rotateZ" 2 311 "FKHead_M.rotateY" 2 312 "FKHead_M.rotateX" 
		2 313 "FKHead_M.translateZ" 1 133 "FKHead_M.translateY" 1 134 "FKHead_M.translateX" 
		1 135 "FKExtraHead_M.scaleZ" 0 197 "FKExtraHead_M.scaleY" 0 
		198 "FKExtraHead_M.scaleX" 0 199 "FKExtraHead_M.rotateZ" 2 314 "FKExtraHead_M.rotateY" 
		2 315 "FKExtraHead_M.rotateX" 2 316 "FKExtraHead_M.translateZ" 1 
		136 "FKExtraHead_M.translateY" 1 137 "FKExtraHead_M.translateX" 1 
		138 "FKNeck_M.scaleZ" 0 200 "FKNeck_M.scaleY" 0 201 "FKNeck_M.scaleX" 
		0 202 "FKNeck_M.rotateZ" 2 317 "FKNeck_M.rotateY" 2 318 "FKNeck_M.rotateX" 
		2 319 "FKExtraNeck_M.rotateZ" 2 320 "FKExtraNeck_M.rotateY" 2 
		321 "FKExtraNeck_M.rotateX" 2 322 "Main.scaleZ" 0 203 "Main.scaleY" 
		0 204 "Main.scaleX" 0 205 "Main.rotateZ" 2 323 "Main.rotateY" 
		2 324 "Main.rotateX" 2 325 "Main.translateZ" 1 139 "Main.translateY" 
		1 140 "Main.translateX" 1 141 "Main.visibility" 0 206  ;
	setAttr ".cd[0].cim" -type "Int32Array" 672 0 1 2 3 4
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
		 641 642 643 644 645 646 647 648 649 650 651 652
		 653 654 655 656 657 658 659 660 661 662 663 664
		 665 666 667 668 669 670 671 ;
createNode animClip -n "attackSource";
	setAttr ".ihi" 0;
	setAttr -s 290 ".ac";
	setAttr ".ac[0:35]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes;
	setAttr ".ac[39]" yes;
	setAttr ".ac[43:45]" yes yes yes;
	setAttr ".ac[49:62]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes;
	setAttr ".ac[69:72]" yes yes yes yes;
	setAttr ".ac[76]" yes;
	setAttr ".ac[80:82]" yes yes yes;
	setAttr ".ac[86:99]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes;
	setAttr ".ac[158:161]" yes yes yes yes;
	setAttr ".ac[165]" yes;
	setAttr ".ac[169:171]" yes yes yes;
	setAttr ".ac[175:188]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes;
	setAttr ".ac[195:203]" yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[214:217]" yes yes yes yes;
	setAttr ".ac[228:231]" yes yes yes yes;
	setAttr ".ac[242:245]" yes yes yes yes;
	setAttr ".ac[249]" yes;
	setAttr ".ac[253:255]" yes yes yes;
	setAttr ".ac[259:272]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes;
	setAttr ".ac[279:299]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes;
	setAttr ".ac[303:308]" yes yes yes yes yes yes;
	setAttr ".ac[312:317]" yes yes yes yes yes yes;
	setAttr ".ac[321:327]" yes yes yes yes yes yes yes;
	setAttr ".ac[361:369]" yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[406:414]" yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[505:513]" yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[550:558]" yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[568:597]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[601:606]" yes yes yes yes yes yes;
	setAttr ".ac[610:624]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes;
	setAttr ".ac[634:643]" yes yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[653:658]" yes yes yes yes yes yes;
	setAttr ".ac[662:671]" no no no yes yes yes no no no no;
	setAttr ".se" 45;
	setAttr ".ci" no;
createNode animCurveTU -n "rat_money_world_CTRL_woldCharSwitch1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 10 2 10 3 10 4 10 5 10 7 10 9 10 11 10 
		13 10 15 10 16 10 17 10 19 10 23 10 29 10 35 10 40 10 45 10;
createNode animCurveTA -n "rat_money_world_CTRL_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_money_world_CTRL_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_money_world_CTRL_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTL -n "rat_money_world_CTRL_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTL -n "rat_money_world_CTRL_translateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTL -n "rat_money_world_CTRL_translateX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTU -n "rat_WagCurveSplineTail_M_increment1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 1 2 1 3 1 4 1 5 1 7 1 9 1 11 1 13 1 15 
		1 16 1 17 1 19 1 23 1 29 1 35 1 40 1 45 1;
createNode animCurveTU -n "rat_WagCurveSplineTail_M_multiply1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 1 2 1 3 1 4 1 5 1 7 1 9 1 11 1 13 1 15 
		1 16 1 17 1 19 1 23 1 29 1 35 1 40 1 45 1;
createNode animCurveTU -n "rat_WagCurveSplineTail_M_timeOffset1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 1 2 1 3 1 4 1 5 1 7 1 9 1 11 1 13 1 15 
		1 16 1 17 1 19 1 23 1 29 1 35 1 40 1 45 1;
createNode animCurveTU -n "rat_WagCurveSplineTail_M_enable1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_WagCurveSplineTail_M_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_WagCurveSplineTail_M_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_WagCurveSplineTail_M_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTU -n "rat_FKIKLegBack_L_IKVis1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 1 2 1 3 1 4 1 5 1 7 1 9 1 11 1 13 1 15 
		1 16 1 17 1 19 1 23 1 29 1 35 1 40 1 45 1;
createNode animCurveTU -n "rat_FKIKLegBack_L_FKVis1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTU -n "rat_FKIKLegBack_L_FKIKBlend1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 10 2 10 3 10 4 10 5 10 7 10 9 10 11 10 
		13 10 15 10 16 10 17 10 19 10 23 10 29 10 35 10 40 10 45 10;
createNode animCurveTU -n "rat_FKIKLegFront_L_IKVis1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 1 2 1 3 1 4 1 5 1 7 1 9 1 11 1 13 1 15 
		1 16 1 17 1 19 1 23 1 29 1 35 1 40 1 45 1;
createNode animCurveTU -n "rat_FKIKLegFront_L_FKVis1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTU -n "rat_FKIKLegFront_L_FKIKBlend1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 10 2 10 3 10 4 10 5 10 7 10 9 10 11 10 
		13 10 15 10 16 10 17 10 19 10 23 10 29 10 35 10 40 10 45 10;
createNode animCurveTU -n "rat_FKIKSpine_M_IKVis1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 1 2 1 3 1 4 1 5 1 7 1 9 1 11 1 13 1 15 
		1 16 1 17 1 19 1 23 1 29 1 35 1 40 1 45 1;
createNode animCurveTU -n "rat_FKIKSpine_M_FKVis1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTU -n "rat_FKIKSpine_M_FKIKBlend1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTU -n "rat_FKIKLegBack_R_IKVis1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 1 2 1 3 1 4 1 5 1 7 1 9 1 11 1 13 1 15 
		1 16 1 17 1 19 1 23 1 29 1 35 1 40 1 45 1;
createNode animCurveTU -n "rat_FKIKLegBack_R_FKVis1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTU -n "rat_FKIKLegBack_R_FKIKBlend1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 10 2 10 3 10 4 10 5 10 7 10 9 10 11 10 
		13 10 15 10 16 10 17 10 19 10 23 10 29 10 35 10 40 10 45 10;
createNode animCurveTU -n "rat_FKIKSplineTail_M_IKVis1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 1 2 1 3 1 4 1 5 1 7 1 9 1 11 1 13 1 15 
		1 16 1 17 1 19 1 23 1 29 1 35 1 40 1 45 1;
createNode animCurveTU -n "rat_FKIKSplineTail_M_FKVis1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTU -n "rat_FKIKSplineTail_M_FKIKBlend1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 10 2 10 3 10 4 10 5 10 7 10 9 10 11 10 
		13 10 15 10 16 10 17 10 19 10 23 10 29 10 35 10 40 10 45 10;
createNode animCurveTU -n "rat_FKIKLegFront_R_IKVis1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 1 2 1 3 1 4 1 5 1 7 1 9 1 11 1 13 1 15 
		1 16 1 17 1 19 1 23 1 29 1 35 1 40 1 45 1;
createNode animCurveTU -n "rat_FKIKLegFront_R_FKVis1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTU -n "rat_FKIKLegFront_R_FKIKBlend1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 10 2 10 3 10 4 10 5 10 7 10 9 10 11 10 
		13 10 15 10 16 10 17 10 19 10 23 10 29 10 35 10 40 10 45 10;
createNode animCurveTU -n "rat_PoleLegBack_L_follow1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 10 2 10 3 10 4 10 5 10 7 10 9 10 11 10 
		13 10 15 10 16 10 17 10 19 10 23 10 29 10 35 10 40 10 45 10;
createNode animCurveTL -n "rat_PoleLegBack_L_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 0.0051987098671592413 45 0.0051987098671592413;
createNode animCurveTL -n "rat_PoleLegBack_L_translateY1";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 -0.0029658564141476066 45 -0.0029658564141476066;
createNode animCurveTL -n "rat_PoleLegBack_L_translateX1";
	setAttr ".tan" 3;
	setAttr -s 8 ".ktv[0:7]"  0 -0.088864011310046689 3 -0.088864011310046689 
		5 0.13936607757462444 11 0.02020809949770272 15 0.15793513653516106 19 -0.17279487926729947 
		23 -0.0889 45 -0.088864011310046689;
createNode animCurveTA -n "rat_IKLegBackBall_L_rotateX1";
	setAttr ".tan" 3;
	setAttr -s 24 ".ktv[0:23]"  0 0 2 0 3 0 4 -67.42563633242807 5 0 7 
		0 9 0 11 0 13 0 15 -19.89865952618209 16 0 17 0 20 0 21 -4.0209662109503812 22 -3.5712958503089065 
		23 0 29 0 30 -0.35665054580011213 32 -6.9340922001341037 33 -13.36927861534253 34 
		-13.348485631218377 35 0 40 0 45 0;
	setAttr -s 24 ".kit[13:23]"  1 1 3 3 3 1 9 1 
		3 3 3;
	setAttr -s 24 ".kot[13:23]"  1 1 3 3 3 1 9 1 
		3 3 3;
	setAttr -s 24 ".kix[13:23]"  0.03224765881896019 0.029191950336098671 
		0.033333301544189453 0.19999998807907104 0.033333361148834229 0.045220483094453812 
		0.033333301544189453 0.03565804660320282 0.033333301544189453 0.16666674613952637 
		0.16666662693023682;
	setAttr -s 24 ".kiy[13:23]"  -0.018281273543834686 0.034863956272602081 
		0 0 0 -0.18490096926689148 -0.05597614124417305 0.04809921607375145 0 0 0;
	setAttr -s 24 ".kox[13:23]"  0.032247722148895264 0.029191888868808746 
		0.19999998807907104 0.033333361148834229 0.066666722297668457 0.011899559758603573 
		0.033333301544189453 0.03565804660320282 0.16666674613952637 0.16666662693023682 
		0.16666662693023682;
	setAttr -s 24 ".koy[13:23]"  -0.018281307071447372 0.034863881766796112 
		0 0 0 -0.048655830323696136 -0.05597614124417305 0.048099197447299957 0 0 0;
createNode animCurveTA -n "rat_IKLegBackHeel_L_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_IKLegBackHeel_L_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_IKLegBackHeel_L_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTU -n "rat_IKLegBack_L_Lenght4";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 1 2 1 3 1 4 1 5 1 7 1 9 1 11 1 13 1 15 
		1 16 1 17 1 20 1 24 1 29 1 35 1 40 1 45 1;
createNode animCurveTU -n "rat_IKLegBack_L_Lenght3";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 1 2 1 3 1 4 1 5 1 7 1 9 1 11 1 13 1 15 
		1 16 1 17 1 20 1 24 1 29 1 35 1 40 1 45 1;
createNode animCurveTU -n "rat_IKLegBack_L_antiPop1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 20 0 24 0 29 0 35 0 40 0 45 0;
createNode animCurveTU -n "rat_IKLegBack_L_stretchy1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 20 0 24 0 29 0 35 0 40 0 45 0;
createNode animCurveTU -n "rat_IKLegBack_L_legAim1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 10 2 10 3 10 4 10 5 10 7 10 9 10 11 10 
		13 10 15 10 16 10 17 10 20 10 24 10 29 10 35 10 40 10 45 10;
createNode animCurveTU -n "rat_IKLegBack_L_rollAngle1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 30 2 30 3 30 4 30 5 30 7 30 9 30 11 30 
		13 30 15 30 16 30 17 30 20 30 24 30 29 30 35 30 40 30 45 30;
createNode animCurveTU -n "rat_IKLegBack_L_roll1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 20 0 24 0 29 0 35 0 40 0 45 0;
createNode animCurveTU -n "rat_IKLegBack_L_swivel1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 20 0 24 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_IKLegBack_L_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 10.65881532857289 2 10.65881532857289 
		3 10.65881532857289 4 10.57211623849588 5 10.532593162695148 7 9.2212929750014716 
		9 7.566468950140691 11 8.2617991434980347 13 9.229048676650617 15 0 16 0 17 0 20 
		0 24 0 29 0 35 10.65881532857289 40 10.65881532857289 45 10.65881532857289;
createNode animCurveTA -n "rat_IKLegBack_L_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 -1.3645079130196978 5 1.6448009331432116 
		7 5.3691317974858856 9 7.5292233084668441 11 6.7579791863860805 13 5.35571219570945 
		15 0 16 0 17 0 20 0 24 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_IKLegBack_L_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 19 ".ktv[0:18]"  0 0 2 0 3 0 4 7.3971380101551016 5 51.642781722008131 
		7 30.17905735156576 9 15.462846918388959 11 21.059727073721195 13 30.2627651346614 
		14 22.337352109936496 15 0 16 0 17 0 20 0 24 0 29 0 35 0 40 0 45 0;
createNode animCurveTL -n "rat_IKLegBack_L_translateZ1";
	setAttr ".tan" 9;
	setAttr -s 17 ".ktv[0:16]"  0 0 2 0 3 0 4 0.20070987294766468 5 1.6416955953564867 
		7 2.1492459128742474 9 2.2114885601278536 10 2.1459647256422336 11 1.8945950438470343 
		13 0.75216902226616311 15 0 29 0 32 0.0073650653493767711 33 -0.0029736883570253732 
		34 -0.0059473767140507741 35 0 45 0;
	setAttr -s 17 ".kit[2:16]"  3 1 9 1 3 9 9 9 
		3 3 3 1 1 3 9;
	setAttr -s 17 ".kot[2:16]"  3 1 9 1 3 9 9 9 
		3 3 3 1 1 3 9;
	setAttr -s 17 ".kix[3:16]"  0.019511912018060684 0.033333331346511841 
		0.044912643730640411 0.066666677594184875 0.033333331346511841 0.033333331346511841 
		0.066666662693023682 0.066666662693023682 0.46666663885116577 0.10000008344650269 
		0.032390538603067398 0.033080194145441055 0.033333301544189453 0.33333337306976318;
	setAttr -s 17 ".kiy[3:16]"  0.34243506193161011 0.64951199293136597 
		0.10077042877674103 0 -0.15844675898551941 -0.46459856629371643 -0.94729751348495483 
		0 0 0 -0.011080509051680565 0.0057714376598596573 0 0;
	setAttr -s 17 ".kox[3:16]"  0.019511910155415535 0.066666662693023682 
		0.044912654906511307 0.033333331346511841 0.033333331346511841 0.066666662693023682 
		0.066666662693023682 0.46666663885116577 0.10000008344650269 0.033333301544189453 
		0.032390538603067398 0.033080197870731354 0.33333337306976318 0.33333337306976318;
	setAttr -s 17 ".koy[3:16]"  0.3424350917339325 1.2990239858627319 0.10077045857906342 
		0 -0.15844675898551941 -0.92919713258743286 -0.94729751348495483 0 0 0 -0.011080509983003139 
		0.0057714381255209446 0 0;
createNode animCurveTL -n "rat_IKLegBack_L_translateY1";
	setAttr ".tan" 1;
	setAttr -s 16 ".ktv[0:15]"  0 -0.055827347319821544 3 -0.055827347319821544 
		4 -0.24720076965759646 5 -0.71400936252256242 7 -1.0894675374687863 9 -1.2533510659512865 
		11 -1.387141356184745 13 -1.6400985425282446 15 -1.7505784108064231 20 -1.7505784108064231 
		22 -1.751 24 -1.0234031982777847 29 -1.0234031982777847 31 -1.023 35 -0.055827347319821544 
		45 -0.055827347319821544;
	setAttr -s 16 ".kit[0:15]"  9 3 9 1 1 1 9 9 
		3 1 3 1 1 3 1 3;
	setAttr -s 16 ".kot[0:15]"  9 3 9 1 1 1 9 9 
		3 1 3 1 1 3 1 3;
	setAttr -s 16 ".kix[3:15]"  0.033129889518022537 0.067933373153209686 
		0.067960739135742188 0.066666662693023682 0.066666662693023682 0.066666662693023682 
		0.16666668653488159 0.066666662693023682 0.066666662693023682 0.16666662693023682 
		0.066666662693023682 0.13333332538604736 0.33333337306976318;
	setAttr -s 16 ".kiy[3:15]"  -0.28793835639953613 -0.2096162736415863 
		-0.12461405992507935 -0.19337373971939087 -0.18171852827072144 0 0 0 0 0 0 0 0;
	setAttr -s 16 ".kox[3:15]"  0.066259786486625671 0.06793338805437088 
		0.067960716784000397 0.066666662693023682 0.066666662693023682 0.16666668653488159 
		0.066666662693023682 0.066666662693023682 0.16666662693023682 0.066666662693023682 
		0.13333332538604736 0.33333337306976318 0.33333337306976318;
	setAttr -s 16 ".koy[3:15]"  -0.57587683200836182 -0.20961630344390869 
		-0.12461399286985397 -0.19337373971939087 -0.18171852827072144 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "rat_IKLegBack_L_translateX1";
	setAttr ".tan" 3;
	setAttr -s 15 ".ktv[0:14]"  0 -0.057269223867906088 2 -0.057269223867906088 
		3 -0.057269223867906088 4 -0.1251307590242198 5 -0.19022759748187021 7 -0.22609846239678263 
		9 -0.22327750115376374 11 -0.21149798639572551 13 -0.17114034439844228 15 -0.070414481281044397 
		16 -0.057269223867906088 20 -0.057269223867906088 24 -0.037051856000119704 29 -0.057269223867906088 
		45 -0.057269223867906088;
	setAttr -s 15 ".kit[0:14]"  9 3 3 1 1 3 1 1 
		9 9 3 3 3 3 3;
	setAttr -s 15 ".kot[0:14]"  9 3 3 1 1 3 1 1 
		9 9 3 3 3 3 3;
	setAttr -s 15 ".kix[3:14]"  0.03258046880364418 0.032987561076879501 
		0.066666662693023682 0.06832093745470047 0.052617717534303665 0.066666662693023682 
		0.066666662693023682 0.033333361148834229 0.13333332538604736 0.13333332538604736 
		0.16666662693023682 0.53333336114883423;
	setAttr -s 15 ".kiy[3:14]"  -0.08716236799955368 -0.03681766614317894 
		0 0.0052700052037835121 0.013839124701917171 0.070541754364967346 0.075914055109024048 
		0 0 0 0 0;
	setAttr -s 15 ".kox[3:14]"  0.032580461353063583 0.065975107252597809 
		0.066666677594184875 0.068320930004119873 0.052617710083723068 0.066666662693023682 
		0.033333361148834229 0.13333332538604736 0.13333332538604736 0.16666662693023682 
		0.53333336114883423 0.53333336114883423;
	setAttr -s 15 ".koy[3:14]"  -0.08716236799955368 -0.073635317385196686 
		0 0.0052700052037835121 0.013839124701917171 0.070541754364967346 0.03795706108212471 
		0 0 0 0 0;
createNode animCurveTU -n "rat_PoleLegFront_L_follow1";
	setAttr ".tan" 2;
	setAttr -s 13 ".ktv[0:12]"  0 10 2 10 3 10 4 10 5 10 15 10 17 10 19 
		10 23 10 29 10 35 10 40 10 45 10;
createNode animCurveTL -n "rat_PoleLegFront_L_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 15 ".ktv[0:14]"  0 -0.0086735638741271305 2 -0.0086735638741271305 
		3 0.00078745538975081675 4 -0.12054138075917435 5 -0.069888881546967693 15 -0.18469789631263364 
		16 -0.10148926016584772 17 -0.078549174330105512 18 -0.15203024374827825 19 -0.13783053047229968 
		23 -0.13171877415281891 29 -0.13171877415281891 35 -0.13171877415281891 40 -0.13171877415281891 
		45 -0.0086735638741271305;
createNode animCurveTL -n "rat_PoleLegFront_L_translateY1";
	setAttr ".tan" 2;
	setAttr -s 15 ".ktv[0:14]"  0 0.0097724910328683117 2 0.0097724910328683117 
		3 0.037891044928013477 4 -0.48970795961251123 5 -0.65088171677159834 15 -0.70497648216114084 
		16 -0.50235598399905201 17 0.19679770478038258 18 0.23461661720916102 19 0.34505048453212955 
		23 0.34636118322863241 29 0.34636118322863241 35 0.34636118322863241 40 0.34636118322863241 
		45 0.0097724910328683117;
createNode animCurveTL -n "rat_PoleLegFront_L_translateX1";
	setAttr ".tan" 2;
	setAttr -s 15 ".ktv[0:14]"  0 0.096690034935401112 2 0.096690034935401112 
		3 0.28128625219035092 4 0.46794941298598824 5 0.624754248537843 15 0.51111168076420044 
		16 0.66225380509588083 17 0.60748908091601017 18 0.27663998846808407 19 0.36006402925196956 
		23 0.24056229591546077 29 0.21525116837611155 35 0.17909241474846979 40 0.12485428430700718 
		45 0.096690034935401112;
createNode animCurveTA -n "rat_IKLegFrontBall_L_rotateX1";
	setAttr ".tan" 3;
	setAttr -s 22 ".ktv[0:21]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 25 0 26 -2.2947699300421118 29 0 35 0 37 -6.5288927607011233 
		39 -6.8057412148185081 40 0 45 0;
	setAttr -s 22 ".kit[18:21]"  1 1 3 3;
	setAttr -s 22 ".kot[18:21]"  1 1 3 3;
	setAttr -s 22 ".kix[18:21]"  0.063694611191749573 0.064275592565536499 
		0.033333420753479004 0.16666662693023682;
	setAttr -s 22 ".kiy[18:21]"  -0.043308824300765991 0.03893125057220459 
		0 0;
	setAttr -s 22 ".kox[18:21]"  0.063694484531879425 0.03094279021024704 
		0.16666662693023682 0.16666662693023682;
	setAttr -s 22 ".koy[18:21]"  -0.04330875352025032 0.018741821870207787 
		0 0;
createNode animCurveTA -n "rat_IKLegFrontHeel_L_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_IKLegFrontHeel_L_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 3.9756933518293979e-016 2 0 3 3.9756933518293979e-016 
		4 3.9756933518293979e-016 5 0 7 0 9 0 11 0 13 0 15 0 16 0 17 0 19 0 23 0 29 0 35 
		0 40 0 45 3.9756933518293979e-016;
createNode animCurveTA -n "rat_IKLegFrontHeel_L_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTU -n "rat_IKLegFront_L_Lenght4";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 1 2 1 3 1 4 1 5 1 10 1 11 1 12 1 14 1 
		16 1 19 1 23 1 29 1 34 1 40 1 45 1;
	setAttr -s 16 ".kit[4:15]"  3 2 2 2 2 1 2 2 
		2 2 2 2;
	setAttr -s 16 ".kot[4:15]"  3 2 2 2 2 1 2 2 
		2 2 2 2;
	setAttr -s 16 ".kix[9:15]"  0.066666662693023682 0.099999964237213135 
		0.13333332538604736 0.19999998807907104 0.16666668653488159 0.20000004768371582 0.16666662693023682;
	setAttr -s 16 ".kiy[9:15]"  0 0 0 0 0 0 0;
	setAttr -s 16 ".kox[9:15]"  0.1666666567325592 0.13333332538604736 
		0.19999998807907104 0.16666668653488159 0.20000004768371582 0.16666662693023682 0;
	setAttr -s 16 ".koy[9:15]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegFront_L_Lenght3";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 1 2 1 3 1 4 1 5 1 10 1 11 1 12 1 14 1 
		16 1 19 1 23 1 29 1 34 1 40 1 45 1;
	setAttr -s 16 ".kit[4:15]"  3 2 2 2 2 1 2 2 
		2 2 2 2;
	setAttr -s 16 ".kot[4:15]"  3 2 2 2 2 1 2 2 
		2 2 2 2;
	setAttr -s 16 ".kix[9:15]"  0.066666662693023682 0.099999964237213135 
		0.13333332538604736 0.19999998807907104 0.16666668653488159 0.20000004768371582 0.16666662693023682;
	setAttr -s 16 ".kiy[9:15]"  0 0 0 0 0 0 0;
	setAttr -s 16 ".kox[9:15]"  0.1666666567325592 0.13333332538604736 
		0.19999998807907104 0.16666668653488159 0.20000004768371582 0.16666662693023682 0;
	setAttr -s 16 ".koy[9:15]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegFront_L_antiPop1";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 0 2 0 3 0 4 0 5 0 10 0 11 0 12 0 14 0 
		16 0 19 0 23 0 29 0 34 0 40 0 45 0;
	setAttr -s 16 ".kit[4:15]"  3 2 2 2 2 1 2 2 
		2 2 2 2;
	setAttr -s 16 ".kot[4:15]"  3 2 2 2 2 1 2 2 
		2 2 2 2;
	setAttr -s 16 ".kix[9:15]"  0.066666662693023682 0.099999964237213135 
		0.13333332538604736 0.19999998807907104 0.16666668653488159 0.20000004768371582 0.16666662693023682;
	setAttr -s 16 ".kiy[9:15]"  0 0 0 0 0 0 0;
	setAttr -s 16 ".kox[9:15]"  0.1666666567325592 0.13333332538604736 
		0.19999998807907104 0.16666668653488159 0.20000004768371582 0.16666662693023682 0;
	setAttr -s 16 ".koy[9:15]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegFront_L_stretchy1";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 0 2 0 3 0 4 0 5 0 10 0 11 0 12 0 14 0 
		16 0 19 0 23 0 29 0 34 0 40 0 45 0;
	setAttr -s 16 ".kit[4:15]"  3 2 2 2 2 1 2 2 
		2 2 2 2;
	setAttr -s 16 ".kot[4:15]"  3 2 2 2 2 1 2 2 
		2 2 2 2;
	setAttr -s 16 ".kix[9:15]"  0.066666662693023682 0.099999964237213135 
		0.13333332538604736 0.19999998807907104 0.16666668653488159 0.20000004768371582 0.16666662693023682;
	setAttr -s 16 ".kiy[9:15]"  0 0 0 0 0 0 0;
	setAttr -s 16 ".kox[9:15]"  0.1666666567325592 0.13333332538604736 
		0.19999998807907104 0.16666668653488159 0.20000004768371582 0.16666662693023682 0;
	setAttr -s 16 ".koy[9:15]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegFront_L_legAim1";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 10 2 10 3 10 4 10 5 10 10 10 11 10 12 
		10 14 10 16 10 19 10 23 10 29 10 34 10 40 10 45 10;
	setAttr -s 16 ".kit[4:15]"  3 2 2 2 2 1 2 2 
		2 2 2 2;
	setAttr -s 16 ".kot[4:15]"  3 2 2 2 2 1 2 2 
		2 2 2 2;
	setAttr -s 16 ".kix[9:15]"  0.066666662693023682 0.099999964237213135 
		0.13333332538604736 0.19999998807907104 0.16666668653488159 0.20000004768371582 0.16666662693023682;
	setAttr -s 16 ".kiy[9:15]"  0 0 0 0 0 0 0;
	setAttr -s 16 ".kox[9:15]"  0.1666666567325592 0.13333332538604736 
		0.19999998807907104 0.16666668653488159 0.20000004768371582 0.16666662693023682 0;
	setAttr -s 16 ".koy[9:15]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegFront_L_rollAngle1";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 25 2 25 3 25 4 25 5 25 10 25 11 25 12 
		25 14 25 16 25 19 25 23 25 29 25 34 25 40 25 45 25;
	setAttr -s 16 ".kit[4:15]"  3 2 2 2 2 1 2 2 
		2 2 2 2;
	setAttr -s 16 ".kot[4:15]"  3 2 2 2 2 1 2 2 
		2 2 2 2;
	setAttr -s 16 ".kix[9:15]"  0.066666662693023682 0.099999964237213135 
		0.13333332538604736 0.19999998807907104 0.16666668653488159 0.20000004768371582 0.16666662693023682;
	setAttr -s 16 ".kiy[9:15]"  0 0 0 0 0 0 0;
	setAttr -s 16 ".kox[9:15]"  0.1666666567325592 0.13333332538604736 
		0.19999998807907104 0.16666668653488159 0.20000004768371582 0.16666662693023682 0;
	setAttr -s 16 ".koy[9:15]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegFront_L_roll1";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 0 2 0 3 0 4 0 5 0 10 0 11 0 12 0 14 0 
		16 0 19 0 23 0 29 0 34 0 40 0 45 0;
	setAttr -s 16 ".kit[4:15]"  3 2 2 2 2 1 2 2 
		2 2 2 2;
	setAttr -s 16 ".kot[4:15]"  3 2 2 2 2 1 2 2 
		2 2 2 2;
	setAttr -s 16 ".kix[9:15]"  0.066666662693023682 0.099999964237213135 
		0.13333332538604736 0.19999998807907104 0.16666668653488159 0.20000004768371582 0.16666662693023682;
	setAttr -s 16 ".kiy[9:15]"  0 0 0 0 0 0 0;
	setAttr -s 16 ".kox[9:15]"  0.1666666567325592 0.13333332538604736 
		0.19999998807907104 0.16666668653488159 0.20000004768371582 0.16666662693023682 0;
	setAttr -s 16 ".koy[9:15]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegFront_L_swivel1";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 0 2 0 3 0 4 0 5 0 10 0 11 0 12 0 14 0 
		16 0 19 0 23 0 29 0 34 0 40 0 45 0;
	setAttr -s 16 ".kit[4:15]"  3 2 2 2 2 1 2 2 
		2 2 2 2;
	setAttr -s 16 ".kot[4:15]"  3 2 2 2 2 1 2 2 
		2 2 2 2;
	setAttr -s 16 ".kix[9:15]"  0.066666662693023682 0.099999964237213135 
		0.13333332538604736 0.19999998807907104 0.16666668653488159 0.20000004768371582 0.16666662693023682;
	setAttr -s 16 ".kiy[9:15]"  0 0 0 0 0 0 0;
	setAttr -s 16 ".kox[9:15]"  0.1666666567325592 0.13333332538604736 
		0.19999998807907104 0.16666668653488159 0.20000004768371582 0.16666662693023682 0;
	setAttr -s 16 ".koy[9:15]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "rat_IKLegFront_L_rotateZ1";
	setAttr ".tan" 3;
	setAttr -s 15 ".ktv[0:14]"  0 -8.5560819804359109 2 -8.5560819804359109 
		3 -8.1330312550227344 4 -19.972584811533423 5 -6.0000000000000009 10 -6.0000000000000009 
		11 -9.4187126391668663 14 -9.4187126391668663 16 -6.0000000000000009 19 0 23 0 29 
		0 34 0 40 -8.5560819804359109 45 -8.5560819804359109;
	setAttr -s 15 ".kit[0:14]"  9 3 3 3 3 10 1 1 
		1 3 9 9 3 3 3;
	setAttr -s 15 ".kot[0:14]"  9 3 3 3 3 10 1 1 
		1 3 9 9 3 3 3;
	setAttr -s 15 ".kix[6:14]"  0.014440202154219151 0.083364821970462799 
		0.064283348619937897 0.099999964237213135 0.13333332538604736 0.19999998807907104 
		0.16666668653488159 0.20000004768371582 0.16666662693023682;
	setAttr -s 15 ".kiy[6:14]"  -0.010857813060283661 0.047785576432943344 
		0.084955781698226929 0 0 0 0 0 0;
	setAttr -s 15 ".kox[6:14]"  0.081099480390548706 0.050034482032060623 
		0.097616203129291534 0.13333332538604736 0.19999998807907104 0.16666668653488159 
		0.20000004768371582 0.16666662693023682 0.16666662693023682;
	setAttr -s 15 ".koy[6:14]"  -0.060979951173067093 0.028680289164185524 
		0.12900790572166443 0 0 0 0 0 0;
createNode animCurveTA -n "rat_IKLegFront_L_rotateY1";
	setAttr ".tan" 3;
	setAttr -s 12 ".ktv[0:11]"  0 -0.31694341854885294 2 -0.31694341854885294 
		3 2.6848714312750235 4 90.875687714895989 5 87.859094226536513 16 87.859040379373937 
		19 0 23 0 29 0 34 0 40 -0.31694341854885294 45 -0.31694341854885294;
	setAttr -s 12 ".kit[2:11]"  1 3 3 3 3 9 9 9 
		9 9;
	setAttr -s 12 ".kot[2:11]"  1 3 3 3 3 9 9 9 
		9 9;
	setAttr -s 12 ".kix[2:11]"  0.033177319914102554 0.033333338797092438 
		0.033333331346511841 0.36666667461395264 0.099999964237213135 0.13333332538604736 
		0.19999998807907104 0.16666668653488159 0.20000004768371582 0.16666662693023682;
	setAttr -s 12 ".kiy[2:11]"  0.15174171328544617 0 0 0 0 0 0 -0.0025144116953015327 
		-0.0030172949191182852 0;
	setAttr -s 12 ".kox[2:11]"  0.033177327364683151 0.033333331346511841 
		0.36666667461395264 0.099999964237213135 0.13333332538604736 0.19999998807907104 
		0.16666668653488159 0.20000004768371582 0.16666662693023682 0.16666662693023682;
	setAttr -s 12 ".koy[2:11]"  0.15174175798892975 0 0 0 0 0 0 -0.0030172944534569979 
		-0.0025144112296402454 0;
createNode animCurveTA -n "rat_IKLegFront_L_rotateX1";
	setAttr ".tan" 3;
	setAttr -s 17 ".ktv[0:16]"  0 -0.51931341167670197 2 -0.51931341167670197 
		3 34.228713973191695 4 -28.360674735783309 5 2.0038969302325578 10 2.0038969302325578 
		11 2.0038969302325578 12 2.0038969302325578 14 2.0038969302325578 16 2.0038969302325578 
		18 23.505453800676388 19 0 23 0 29 0 34 0 40 -0.51931341167670197 45 -0.51931341167670197;
	setAttr -s 17 ".kit[12:16]"  9 9 9 9 9;
	setAttr -s 17 ".kot[12:16]"  9 9 9 9 9;
createNode animCurveTL -n "rat_IKLegFront_L_translateZ1";
	setAttr ".tan" 1;
	setAttr -s 17 ".ktv[0:16]"  0 0.00076651281650793874 2 0.00076651281650793874 
		3 0.066724881900981969 4 1.7105289321104409 5 2.7485989567659326 6 2.8108373069646975 
		7 2.8319414203276021 8 2.8350398840734066 9 2.8222860398908898 10 2.7421873170466067 
		11 2.5366977351058142 12 2.1576443834679937 14 1.3864348123770582 16 0.7227523774995076 
		18 0.085914014834012453 19 0 45 0.00076651281650793874;
	setAttr -s 17 ".kit[0:16]"  3 3 1 1 1 1 1 1 
		1 1 1 2 2 9 9 3 9;
	setAttr -s 17 ".kot[0:16]"  3 3 1 1 1 1 1 1 
		1 1 1 2 2 9 9 3 9;
	setAttr -s 17 ".kix[2:16]"  0.033140983432531357 0.032518379390239716 
		0.03491988405585289 0.03729778528213501 0.032612085342407227 0.033292297273874283 
		0.034336388111114502 0.033673819154500961 0.032911472022533417 0.033333331346511841 
		0.066666662693023682 0.066666692495346069 0.066666662693023682 0.033333301544189453 
		0.86666667461395264;
	setAttr -s 17 ".kiy[2:16]"  0.22997771203517914 1.620449423789978 0.1230781227350235 
		0.035933136940002441 0.0089645404368638992 -0.00080255192006006837 -0.026601033285260201 
		-0.12806214392185211 -0.32542306184768677 -0.37905335426330566 -0.77120959758758545 
		-0.6502605676651001 -0.48183506727218628 0 0.00076651282142847776;
	setAttr -s 17 ".kox[2:16]"  0.033140987157821655 0.032518371939659119 
		0.034919876605272293 0.037297781556844711 0.03261210024356842 0.033292286098003387 
		0.034336384385824203 0.033673815429210663 0.032911472022533417 0.066666662693023682 
		0.066666692495346069 0.066666662693023682 0.033333301544189453 0.86666667461395264 
		0.86666667461395264;
	setAttr -s 17 ".koy[2:16]"  0.22997777163982391 1.6204495429992676 
		0.1230781152844429 0.035933148115873337 0.0089645460247993469 -0.00080255168722942472 
		-0.02660103514790535 -0.12806214392185211 -0.32542309165000916 -0.77120959758758545 
		-0.66368246078491211 -0.65026026964187622 -0.24091731011867523 0 0.00076651282142847776;
createNode animCurveTL -n "rat_IKLegFront_L_translateY1";
	setAttr ".tan" 3;
	setAttr -s 18 ".ktv[0:17]"  0 0.27472958484748605 2 0.27472958484748605 
		3 0.21856929524583127 4 -0.47568651224625103 5 -0.91456660325909456 6 -0.92961907444774849 
		7 -0.93215523724214722 10 -0.93811204291858974 11 -0.94715767565438835 12 -0.98064997210277305 
		14 -1.1643451041868147 16 -1.4082932424120771 19 -1.0456469253784644 24 -1.0456469253784644 
		29 -0.46200158254884927 34 -0.46200158254884927 40 0.27472958484748605 45 0.27472958484748605;
	setAttr -s 18 ".kit[2:17]"  1 1 1 1 1 1 1 1 
		9 3 3 3 3 3 3 3;
	setAttr -s 18 ".kot[2:17]"  1 1 1 1 1 1 1 1 
		9 3 3 3 3 3 3 3;
	setAttr -s 18 ".kix[2:17]"  0.032371658831834793 0.032241839915513992 
		0.034620806574821472 0.03790711984038353 0.033401742577552795 0.10084977000951767 
		0.034122459590435028 0.037969827651977539 0.066666662693023682 0.066666692495346069 
		0.099999964237213135 0.16666668653488159 0.16666662693023682 0.16666668653488159 
		0.20000004768371582 0.16666662693023682;
	setAttr -s 18 ".kiy[2:17]"  -0.17157582938671112 -0.68726265430450439 
		-0.044568601995706558 -0.0035819562617689371 -0.0015179357724264264 -0.010296089574694633 
		-0.015678398311138153 -0.062915347516536713 -0.21382158994674683 0 0 0 0 0 0 0;
	setAttr -s 18 ".kox[2:17]"  0.032371658831834793 0.032241832464933395 
		0.034620814025402069 0.037907116115093231 0.1002051904797554 0.033616591244935989 
		0.034122459590435028 0.075939647853374481 0.066666692495346069 0.099999964237213135 
		0.16666668653488159 0.16666662693023682 0.16666668653488159 0.20000004768371582 0.16666662693023682 
		0.16666662693023682;
	setAttr -s 18 ".koy[2:17]"  -0.17157582938671112 -0.68726253509521484 
		-0.044568609446287155 -0.0035819555632770061 -0.0045538065023720264 -0.0034320303238928318 
		-0.015678400173783302 -0.12583068013191223 -0.21382167935371399 0 0 0 0 0 0 0;
createNode animCurveTL -n "rat_IKLegFront_L_translateX1";
	setAttr ".tan" 3;
	setAttr -s 16 ".ktv[0:15]"  0 -0.071005957816697135 2 -0.071005957816697135 
		3 -0.071005957816697135 4 0.20352880426187342 5 -0.10641419568342655 10 -0.10641419568342655 
		11 -0.10641419568342655 12 -0.10641419568342655 14 -0.10641419568342655 16 -0.10641419568342655 
		19 -0.11342265762008824 23 -0.11342265762008824 29 -0.11342265762008824 34 -0.11342265762008824 
		40 -0.071005957816697135 45 -0.071005957816697135;
	setAttr -s 16 ".kit[0:15]"  9 3 3 3 3 2 2 2 
		2 1 3 3 3 3 3 3;
	setAttr -s 16 ".kot[0:15]"  9 3 3 3 3 2 2 2 
		2 1 3 3 3 3 3 3;
	setAttr -s 16 ".kix[9:15]"  0.066666662693023682 0.099999964237213135 
		0.13333332538604736 0.19999998807907104 0.16666668653488159 0.20000004768371582 0.16666662693023682;
	setAttr -s 16 ".kiy[9:15]"  0 0 0 0 0 0 0;
	setAttr -s 16 ".kox[9:15]"  0.1666666567325592 0.13333332538604736 
		0.19999998807907104 0.16666668653488159 0.20000004768371582 0.16666662693023682 0.16666662693023682;
	setAttr -s 16 ".koy[9:15]"  -0.0070084617473185062 0 0 0 0 0 0;
createNode animCurveTU -n "rat_PoleLegBack_R_follow1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 10 2 10 3 10 4 10 5 10 7 10 9 10 11 10 
		13 10 15 10 16 10 17 10 19 10 23 10 29 10 35 10 40 10 45 10;
createNode animCurveTL -n "rat_PoleLegBack_R_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 6 ".ktv[0:5]"  0 0.0054999194138878266 5 0.025287625120427822 
		13 0.032049747197630013 17 0.028905244351423682 23 0.02867822301980848 45 0.0054999194138878266;
createNode animCurveTL -n "rat_PoleLegBack_R_translateY1";
	setAttr ".tan" 2;
	setAttr -s 6 ".ktv[0:5]"  0 -0.0031376960222415048 5 -0.088351817436808269 
		13 -0.094526775178810654 17 -0.083202536283324413 23 -0.06877756404767281 45 -0.0031376960222415048;
createNode animCurveTL -n "rat_PoleLegBack_R_translateX1";
	setAttr ".tan" 9;
	setAttr -s 8 ".ktv[0:7]"  0 0.083911116250119933 2 0.083911116250119933 
		3 0.083911116250119933 5 -0.36511477763692141 13 -0.39446439697663571 17 -0.14357473129565648 
		23 -0.0014287343198703048 45 0.083911116250119933;
	setAttr -s 8 ".kit[1:7]"  3 3 1 1 9 9 3;
	setAttr -s 8 ".kot[1:7]"  3 3 1 1 9 9 3;
	setAttr -s 8 ".kix[3:7]"  0.063929028809070587 0.25814571976661682 
		0.13333332538604736 0.19999998807907104 0.73333334922790527;
	setAttr -s 8 ".kiy[3:7]"  -0.059837505221366882 0.15552051365375519 
		0.15721426904201508 0.048746965825557709 0;
	setAttr -s 8 ".kox[3:7]"  0.25571635365486145 0.1290728747844696 
		0.19999998807907104 0.73333334922790527 0.73333334922790527;
	setAttr -s 8 ".koy[3:7]"  -0.23935025930404663 0.077760323882102966 
		0.23582139611244202 0.17873887717723846 0;
createNode animCurveTA -n "rat_IKLegBackBall_R_rotateX1";
	setAttr ".tan" 3;
	setAttr -s 20 ".ktv[0:19]"  0 0 2 0 3 0 4 -56.158281016241887 5 0 7 
		0 9 0 11 0 13 0 15 -11.677649314111186 16 0 17 0 19 0 24 0 26 -12.143455345171995 
		30 0 36 0 38 -10.842949029934998 41 0 45 0;
createNode animCurveTA -n "rat_IKLegBackHeel_R_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_IKLegBackHeel_R_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_IKLegBackHeel_R_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTU -n "rat_IKLegBack_R_Lenght4";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 1 2 1 3 1 4 1 5 1 7 1 9 1 11 1 13 1 15 
		1 16 1 24 1 29 1 35 1 40 1 45 1;
createNode animCurveTU -n "rat_IKLegBack_R_Lenght3";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 1 2 1 3 1 4 1 5 1 7 1 9 1 11 1 13 1 15 
		1 16 1 24 1 29 1 35 1 40 1 45 1;
createNode animCurveTU -n "rat_IKLegBack_R_antiPop1";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 24 0 29 0 35 0 40 0 45 0;
createNode animCurveTU -n "rat_IKLegBack_R_stretchy1";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 24 0 29 0 35 0 40 0 45 0;
createNode animCurveTU -n "rat_IKLegBack_R_legAim1";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 10 2 10 3 10 4 10 5 10 7 10 9 10 11 10 
		13 10 15 10 16 10 24 10 29 10 35 10 40 10 45 10;
createNode animCurveTU -n "rat_IKLegBack_R_rollAngle1";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 30 2 30 3 30 4 30 5 30 7 30 9 30 11 30 
		13 30 15 30 16 30 24 30 29 30 35 30 40 30 45 30;
createNode animCurveTU -n "rat_IKLegBack_R_roll1";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 24 0 29 0 35 0 40 0 45 0;
createNode animCurveTU -n "rat_IKLegBack_R_swivel1";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 24 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_IKLegBack_R_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 -9.8142060506602 2 -9.8142060506602 3 
		-9.8142060506602 4 -9.7345174348678807 5 -6.0285839154421907 7 -8.4206406906566489 
		9 -9.4241782386285582 11 -9.1113493599416451 13 -8.4133134572645112 15 0 16 0 24 
		0 29 0 35 0 40 -9.8142060506602 45 -9.8142060506602;
createNode animCurveTA -n "rat_IKLegBack_R_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 0 2 0 3 0 4 1.2541831870505133 5 7.7586983242345342 
		7 5.0592588745884859 9 2.7517129355724195 11 3.6626845586744108 13 5.071490692760471 
		15 0 16 0 24 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_IKLegBack_R_rotateX1";
	setAttr ".tan" 3;
	setAttr -s 12 ".ktv[0:11]"  0 0 2 0 3 0 4 7.3776891349705744 5 52.373873280641568 
		7 31.155345407496391 9 16.358591849719598 11 22.010604767490655 13 31.238909677239924 
		14 25.119831852317734 15 0 45 0;
	setAttr -s 12 ".kit[0:11]"  9 3 3 1 3 1 3 1 
		3 9 3 9;
	setAttr -s 12 ".kot[0:11]"  9 3 3 1 3 1 3 1 
		3 9 3 9;
	setAttr -s 12 ".kix[3:11]"  0.032317429780960083 0.033333331346511841 
		0.062916979193687439 0.066666677594184875 0.063290409743785858 0.066666662693023682 
		0.033333331346511841 0.033333331346511841 1;
	setAttr -s 12 ".kiy[3:11]"  0.34569650888442993 0 -0.44911760091781616 
		0 0.18090997636318207 0 -0.27261090278625488 0 0;
	setAttr -s 12 ".kox[3:11]"  0.032317422330379486 0.066666662693023682 
		0.062916994094848633 0.066666662693023682 0.063290409743785858 0.033333331346511841 
		0.033333331346511841 1 1;
	setAttr -s 12 ".koy[3:11]"  0.34569641947746277 0 -0.44911760091781616 
		0 0.18090997636318207 0 -0.27261090278625488 0 0;
createNode animCurveTL -n "rat_IKLegBack_R_translateZ1";
	setAttr ".tan" 10;
	setAttr -s 17 ".ktv[0:16]"  0 0 2 0 3 0 4 0.20070987294766462 5 1.7158056456924935 
		7 2.2444805887686559 9 2.2855986104638601 10 2.2282626143166069 11 1.9400476548484002 
		13 0.64278895558434057 15 0 16 0 24 0 29 0 35 0 40 0 45 0;
	setAttr -s 17 ".kit[2:16]"  3 1 1 1 1 1 1 10 
		10 10 10 10 10 10 10;
	setAttr -s 17 ".kot[2:16]"  3 1 1 1 1 1 1 10 
		10 10 10 10 10 10 10;
	setAttr -s 17 ".kix[3:16]"  0.034779850393533707 0.037004601210355759 
		0.069234758615493774 0.066642172634601593 0.034274566918611526 0.034688431769609451 
		0.066666662693023682 0.066666662693023682 0.033333361148834229 0.26666665077209473 
		0.16666662693023682 0.19999998807907104 0.16666674613952637 0.16666662693023682;
	setAttr -s 17 ".kiy[3:16]"  0.65680193901062012 0.64532238245010376 
		0.12938196957111359 -0.024554485455155373 -0.11557883769273758 -0.51213997602462769 
		-0.97002381086349487 0 0 0 0 0 0 0;
	setAttr -s 17 ".kox[3:16]"  0.034779839217662811 0.074009247124195099 
		0.069234788417816162 0.0333210788667202 0.034274566918611526 0.069376863539218903 
		0.066666662693023682 0.033333361148834229 0.26666665077209473 0.16666662693023682 
		0.19999998807907104 0.16666674613952637 0.16666662693023682 0.16666662693023682;
	setAttr -s 17 ".koy[3:16]"  0.65680199861526489 1.2906454801559448 
		0.12938199937343597 -0.012277241796255112 -0.11557881534099579 -1.0242799520492554 
		-0.97002381086349487 0 0 0 0 0 0 0;
createNode animCurveTL -n "rat_IKLegBack_R_translateY1";
	setAttr ".tan" 10;
	setAttr -s 16 ".ktv[0:15]"  0 -0.26728461461584108 2 -0.26728461461584108 
		3 -0.26728461461584108 4 -0.27652543129177598 5 -0.47282600632805738 7 -0.86682000102718071 
		9 -1.1041384862159649 11 -1.3256985098705676 13 -1.5105625321117355 15 -1.5558160482262997 
		16 -1.5353159753762557 25 -1.5353159753762557 29 -0.67078219192447897 36 -0.67078219192447897 
		40 -0.26728461461584108 45 -0.26728461461584108;
	setAttr -s 16 ".kit[3:15]"  1 1 10 1 10 1 3 10 
		10 10 10 10 10;
	setAttr -s 16 ".kot[3:15]"  1 1 10 1 10 1 3 10 
		10 10 10 10 10;
	setAttr -s 16 ".kix[3:15]"  0.034920264035463333 0.032415367662906647 
		0.066666662693023682 0.066860772669315338 0.066666662693023682 0.064742311835289001 
		0.066666662693023682 0.033333361148834229 0.29999995231628418 0.13333332538604736 
		0.23333340883255005 0.13333332538604736 0.16666662693023682;
	setAttr -s 16 ".kiy[3:15]"  -0.027367344126105309 -0.24240466952323914 
		-0.31565621495246887 -0.22297216951847076 -0.20321202278137207 -0.11244962364435196 
		0 0 0 0 0 0 0;
	setAttr -s 16 ".kox[3:15]"  0.034920249134302139 0.06483074277639389 
		0.066666677594184875 0.066860765218734741 0.066666662693023682 0.064742304384708405 
		0.033333361148834229 0.29999995231628418 0.13333332538604736 0.23333340883255005 
		0.13333332538604736 0.16666662693023682 0.16666662693023682;
	setAttr -s 16 ".koy[3:15]"  -0.027367325499653816 -0.48480939865112305 
		-0.31565627455711365 -0.22297213971614838 -0.20321202278137207 -0.11244962364435196 
		0 0 0 0 0 0 0;
createNode animCurveTL -n "rat_IKLegBack_R_translateX1";
	setAttr ".tan" 9;
	setAttr -s 16 ".ktv[0:15]"  0 0.017033828181619803 2 0.017033828181619803 
		3 0.017033828181619803 4 0.042647717310292932 5 0.063673769289359694 7 0.074625108123345635 
		9 0.077170104472167225 11 0.077688431008323691 13 0.071468512574445281 15 0.017033828181619803 
		16 0.017033828181619803 24 0.017033828181619803 29 0.017033828181619803 35 0.017033828181619803 
		40 0.017033828181619803 45 0.017033828181619803;
	setAttr -s 16 ".kit[2:15]"  3 1 9 1 1 3 1 3 
		3 9 9 9 9 9;
	setAttr -s 16 ".kot[2:15]"  3 1 9 1 1 3 1 3 
		3 9 9 9 9 9;
	setAttr -s 16 ".kix[3:15]"  0.029779717326164246 0.033333331346511841 
		0.068438373506069183 0.068671829998493195 0.066666662693023682 0.052850399166345596 
		0.066666662693023682 0.033333361148834229 0.26666665077209473 0.16666662693023682 
		0.19999998807907104 0.16666674613952637 0.16666662693023682;
	setAttr -s 16 ".kiy[3:15]"  0.025915667414665222 0.010659130290150642 
		0.00470774807035923 0.0011401347583159804 0 -0.012698543258011341 0 0 0 0 0 0 0;
	setAttr -s 16 ".kox[3:15]"  0.029779711738228798 0.066666662693023682 
		0.068438388407230377 0.068671822547912598 0.066666662693023682 0.052850402891635895 
		0.033333361148834229 0.26666665077209473 0.16666662693023682 0.19999998807907104 
		0.16666674613952637 0.16666662693023682 0.16666662693023682;
	setAttr -s 16 ".koy[3:15]"  0.025915661826729774 0.021318260580301285 
		0.0047077490016818047 0.0011401340598240495 0 -0.012698543258011341 0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKSplineTail3_M_stretchy1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 16 0 29 0 32 0 43 0 45 0;
createNode animCurveTU -n "rat_IKSplineTail3_M_twist1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 16 0 29 0 32 0 43 0 45 0;
createNode animCurveTU -n "rat_IKSplineTail3_M_follow1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 16 0 29 0 32 0 43 0 45 0;
createNode animCurveTA -n "rat_IKSplineTail3_M_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 16 0 29 0 32 0 43 0 45 0;
createNode animCurveTA -n "rat_IKSplineTail3_M_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 16 0 29 0 32 0 43 0 45 0;
createNode animCurveTA -n "rat_IKSplineTail3_M_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 16 0 29 0 32 0 43 0 45 0;
createNode animCurveTL -n "rat_IKSplineTail3_M_translateZ1";
	setAttr ".tan" 3;
	setAttr -s 20 ".ktv[0:19]"  0 -0.77177341453224102 3 -0.77177341453224102 
		4 -0.73495683909989151 7 0.065558476524402387 11 0.10435544152218412 13 -0.076701699134998802 
		14 -0.26430955152098023 16 -0.18127001030095558 19 0.47381970376812677 21 0.14265685004294004 
		22 -0.75332018315001381 29 -0.75332018315001381 32 -0.75332018315001381 36 -0.76889378653856455 
		37 -0.84877166728383124 38 -0.013260997399146324 40 -0.29140555300602761 41 -0.772 
		43 -0.77177341453224102 45 -0.77177341453224102;
	setAttr -s 20 ".kit[2:19]"  1 1 1 1 3 1 3 9 
		3 3 3 3 3 3 9 3 3 9;
	setAttr -s 20 ".kot[2:19]"  1 1 1 1 3 1 3 9 
		3 3 3 3 3 3 9 3 3 9;
	setAttr -s 20 ".kix[2:19]"  0.034426789730787277 0.11105134338140488 
		0.13133914768695831 0.05618174746632576 0.033333331346511841 0.077713191509246826 
		0.099999964237213135 0.066666662693023682 0.033333361148834229 0.2333332896232605 
		0.10000008344650269 0.13333332538604736 0.033333301544189453 0.033333301544189453 
		0.066666722297668457 0.033333301544189453 0.066666603088378906 0.066666722297668457;
	setAttr -s 20 ".kiy[2:19]"  0.11719494313001633 0.21832367777824402 
		-0.13919836282730103 -0.2928156852722168 0 0.23622795939445496 0 -0.81809300184249878 
		0 0 0 0 0 0 -0.50582629442214966 0 0 0;
	setAttr -s 20 ".kox[2:19]"  0.10328035056591034 0.14806844294071198 
		0.065669558942317963 0.028090881183743477 0.066666692495346069 0.11656968295574188 
		0.066666662693023682 0.033333361148834229 0.2333332896232605 0.10000008344650269 
		0.13333332538604736 0.033333301544189453 0.033333301544189453 0.066666722297668457 
		0.033333301544189453 0.066666603088378906 0.066666722297668457 0.066666722297668457;
	setAttr -s 20 ".koy[2:19]"  0.35158452391624451 0.29109811782836914 
		-0.069599173963069916 -0.14640787243843079 0 0.35434165596961975 0 -0.40904685854911804 
		0 0 0 0 0 0 -0.25291270017623901 0 0 0;
createNode animCurveTL -n "rat_IKSplineTail3_M_translateY1";
	setAttr ".tan" 3;
	setAttr -s 16 ".ktv[0:15]"  0 0 3 0 4 -0.3272133569971965 7 -2.4265999267629392 
		11 -3.1647291820520485 13 -2.5957545477666959 14 -1.7438303656205179 16 -1.3932189693581918 
		19 -1.9929489892805918 22 -2.0229865519320978 29 -2.0422784142673693 32 -2.0422784142673693 
		34 -2.1381899325880234 38 -0.46506677966104437 43 0 45 0;
	setAttr -s 16 ".kit[2:15]"  9 1 3 1 1 3 1 9 
		3 3 3 9 3 3;
	setAttr -s 16 ".kot[2:15]"  9 1 3 1 1 3 1 9 
		3 3 3 9 3 3;
	setAttr -s 16 ".kix[3:15]"  0.099210470914840698 0.13333334028720856 
		0.052542846649885178 0.027346070855855942 0.066666692495346069 0.099904514849185944 
		0.10000002384185791 0.2333332896232605 0.10000008344650269 0.066666603088378906 0.13333332538604736 
		0.16666662693023682 0.066666722297668457;
	setAttr -s 16 ".kiy[3:15]"  -1.3040446043014526 0 1.0616779327392578 
		0.45855492353439331 0 -0.042081084102392197 -0.014798832125961781 0 0 0 0.95030671358108521 
		0 0;
	setAttr -s 16 ".kox[3:15]"  0.132280632853508 0.066666662693023682 
		0.026271423324942589 0.054692160338163376 0.099999964237213135 0.099904574453830719 
		0.2333332896232605 0.10000008344650269 0.066666603088378906 0.13333332538604736 0.16666662693023682 
		0.066666722297668457 0.066666722297668457;
	setAttr -s 16 ".koy[3:15]"  -1.7387262582778931 0 0.53083914518356323 
		0.91711050271987915 0 -0.042081113904714584 -0.03453059121966362 0 0 0 1.1878832578659058 
		0 0;
createNode animCurveTL -n "rat_IKSplineTail3_M_translateX1";
	setAttr ".tan" 1;
	setAttr -s 14 ".ktv[0:13]"  0 0.066422756288499141 3 0.066422756288499141 
		7 0.011963994642707032 11 -0.81336972634945981 16 -0.063589293016446891 19 0.77876444361724373 
		29 1.3319737285673283 32 1.2924782561260897 34 1.0903056975078536 38 0.2800788960747328 
		40 -0.3938056597246099 41 -0.37474809729307856 43 -0.025886799275630312 45 0.066422756288499141;
	setAttr -s 14 ".kit[0:13]"  3 3 1 3 1 1 3 1 
		1 1 1 1 1 3;
	setAttr -s 14 ".kot[0:13]"  3 3 1 3 1 1 3 1 
		1 1 1 1 1 3;
	setAttr -s 14 ".kix[2:13]"  0.13849703967571259 0.13333334028720856 
		0.14468695223331451 0.094400182366371155 0.33333331346511841 0.09939313679933548 
		0.067662350833415985 0.12798750400543213 0.067787133157253265 0.033989634364843369 
		0.064722135663032532 0.066666722297668457;
	setAttr -s 14 ".kiy[2:13]"  -0.12561279535293579 0 1.2250423431396484 
		0.4232504665851593 0 -0.073195256292819977 -0.28498876094818115 -1.0388021469116211 
		-0.26962253451347351 0.03578866645693779 0.18172217905521393 0;
	setAttr -s 14 ".kox[2:13]"  0.13849708437919617 0.16666668653488159 
		0.086812146008014679 0.31466752290725708 0.10000008344650269 0.066261954605579376 
		0.13532479107379913 0.06399381160736084 0.033893503248691559 0.067979268729686737 
		0.064722247421741486 0.066666722297668457;
	setAttr -s 14 ".koy[2:13]"  -0.12561279535293579 0 0.73502492904663086 
		1.4108359813690186 0 -0.048796750605106354 -0.56997805833816528 -0.51940149068832397 
		-0.13481101393699646 0.07157733291387558 0.18172250688076019 0;
createNode animCurveTU -n "rat_IKSplineTail2_M_follow1";
	setAttr ".tan" 2;
	setAttr -s 6 ".ktv[0:5]"  0 0 3 0 7 0 32 0 34 0 43 0;
createNode animCurveTL -n "rat_IKSplineTail2_M_translateZ1";
	setAttr ".tan" 3;
	setAttr -s 14 ".ktv[0:13]"  0 -0.75537025498543575 3 -0.75537025498543575 
		4 -0.88734118782256388 7 0.65630194575498058 11 0.42563655347713469 14 0.6932084085194361 
		16 0.77624794973946087 19 -0.43243870579645172 23 -0.75537025498543608 32 -0.75537025498543608 
		34 -0.47756762887552162 37 0.088416616887539989 39 -0.755 43 -0.75537025498543575;
	setAttr -s 14 ".kit[5:13]"  1 3 9 3 3 9 3 3 
		3;
	setAttr -s 14 ".kot[5:13]"  1 3 9 3 3 9 3 3 
		3;
	setAttr -s 14 ".kix[5:13]"  0.09804224967956543 0.066666692495346069 
		0.099999964237213135 0.13333332538604736 0.30000007152557373 0.066666603088378906 
		0.10000002384185791 0.066666603088378906 0.13333332538604736;
	setAttr -s 14 ".kiy[5:13]"  0.37442675232887268 0 -0.65640771389007568 
		0 0 0.33751451969146729 0 0 0;
	setAttr -s 14 ".kox[5:13]"  0.065361544489860535 0.099999964237213135 
		0.13333332538604736 0.30000007152557373 0.066666603088378906 0.10000002384185791 
		0.066666603088378906 0.13333332538604736 0.13333332538604736;
	setAttr -s 14 ".koy[5:13]"  0.24961799383163452 0 -0.87521052360534668 
		0 0 0.50627237558364868 0 0 0;
createNode animCurveTL -n "rat_IKSplineTail2_M_translateY1";
	setAttr ".tan" 3;
	setAttr -s 14 ".ktv[0:13]"  0 -0.073475021782978711 3 -0.073475021782978711 
		4 -0.65111432363320798 7 -1.937251391387973 11 -1.8357586187857207 14 -1.0791761321143876 
		16 -1.7250392304923561 19 -1.4759206068322821 29 -0.81169304394729469 32 -0.81169304394729469 
		34 -0.35344912308194365 37 0.21136315147302387 41 -0.076371403488940004 43 -0.073475021782978711;
	setAttr -s 14 ".kit[2:13]"  1 1 9 3 3 1 3 3 
		1 3 3 1;
	setAttr -s 14 ".kot[2:13]"  1 1 9 3 3 1 3 3 
		1 3 3 1;
	setAttr -s 14 ".kix[2:13]"  0.012540606781840324 0.11892738193273544 
		0.13333334028720856 0.099999994039535522 0.066666692495346069 0.083351261913776398 
		0.33333331346511841 0.10000008344650269 0.055331334471702576 0.10000002384185791 
		0.13333332538604736 0.066267214715480804;
	setAttr -s 14 ".kiy[2:13]"  -0.48737308382987976 -0.41111916303634644 
		0.49032872915267944 0 0 0.33136239647865295 0 0 0.4439365565776825 0 0 0.00097732141148298979;
	setAttr -s 14 ".kox[2:13]"  0.037621799856424332 0.15856984257698059 
		0.099999994039535522 0.066666692495346069 0.099999964237213135 0.2778376042842865 
		0.10000008344650269 0.066666603088378906 0.082997076213359833 0.13333332538604736 
		0.066666603088378906 0.066267214715480804;
	setAttr -s 14 ".koy[2:13]"  -1.4621185064315796 -0.54815876483917236 
		0.367746502161026 0 0 1.104541540145874 0 0 0.66590571403503418 0 0 0.00097732129506766796;
createNode animCurveTL -n "rat_IKSplineTail2_M_translateX1";
	setAttr ".tan" 3;
	setAttr -s 12 ".ktv[0:11]"  0 -0.10278940729156966 3 -0.10278940729156966 
		7 -0.44674823946080194 11 0.18510828116089786 16 0.6035767753902932 19 0.63051602993439626 
		29 0.07688894345542685 32 0.07688894345542685 34 0.63104438264143292 37 -0.46660966036161788 
		41 -0.1149340931858831 43 -0.10278940729156966;
	setAttr -s 12 ".kit[3:11]"  1 1 3 9 1 3 3 1 
		3;
	setAttr -s 12 ".kot[3:11]"  1 1 3 9 1 3 3 1 
		3;
	setAttr -s 12 ".kix[3:11]"  0.12274777889251709 0.1723015159368515 
		0.099999964237213135 0.33333331346511841 0.092323862016201019 0.066666603088378906 
		0.10000002384185791 0.13271208107471466 0.066666603088378906;
	setAttr -s 12 ".kiy[3:11]"  0.46484488248825073 0.13358895480632782 
		0 -0.42586690187454224 0.17495307326316833 0 0 0.077811062335968018 0;
	setAttr -s 12 ".kox[3:11]"  0.15343472361564636 0.10338086634874344 
		0.33333331346511841 0.10000008344650269 0.061549142003059387 0.10000002384185791 
		0.13333332538604736 0.066355988383293152 0.066666603088378906;
	setAttr -s 12 ".koy[3:11]"  0.58105611801147461 0.080153346061706543 
		0 -0.12776018679141998 0.11663516610860825 0 0 0.038905501365661621 0;
createNode animCurveTU -n "rat_IKSplineTail1_M_follow1";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 0 3 0 33 0 45 0;
createNode animCurveTL -n "rat_IKSplineTail1_M_translateZ1";
	setAttr ".tan" 3;
	setAttr -s 12 ".ktv[0:11]"  0 -0.8594552290779115 3 -0.8594552290779115 
		4 -0.78787869380628373 7 1.3826123838627511 11 1.6040511604494834 14 0.69061620702921345 
		16 -0.41657767590444661 19 -0.85945522907791072 33 -0.85945522907791116 37 -0.68655461124631267 
		39 -0.859 45 -0.8594552290779115;
	setAttr -s 12 ".kit[0:11]"  9 3 1 9 9 1 9 3 
		2 3 3 3;
	setAttr -s 12 ".kot[0:11]"  9 3 1 9 9 1 9 3 
		2 3 3 3;
	setAttr -s 12 ".kix[2:11]"  0.033138401806354523 0.099999994039535522 
		0.13333334028720856 0.096512824296951294 0.066666692495346069 0.099999964237213135 
		0.46666669845581055 0.13333332538604736 0.066666603088378906 0.20000004768371582;
	setAttr -s 12 ".kiy[2:11]"  0.19648356735706329 1.0251127481460571 
		-0.39542639255523682 -1.558799147605896 -0.62002885341644287 0 0 0 0 0;
	setAttr -s 12 ".kox[2:11]"  0.099415160715579987 0.13333334028720856 
		0.099999994039535522 0.064341902732849121 0.099999964237213135 0.46666669845581055 
		0.13333332538604736 0.066666603088378906 0.20000004768371582 0.20000004768371582;
	setAttr -s 12 ".koy[2:11]"  0.58945035934448242 1.3668171167373657 
		-0.29656976461410522 -1.0391998291015625 -0.930042564868927 0 0.17290061712265015 
		0 0 0;
createNode animCurveTL -n "rat_IKSplineTail1_M_translateY1";
	setAttr ".tan" 1;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 4 -0.70389752596393351 7 -1.1256471143158877 
		11 -0.8580752592735863 14 -1.1256471143158879 16 -1.6238843616360332 19 -1.614657745944919 
		29 -0.87494100257118956 33 -0.50537210698551371 45 0;
	setAttr -s 11 ".kit[0:10]"  3 3 9 9 3 1 1 1 
		1 2 3;
	setAttr -s 11 ".kot[0:10]"  3 3 9 9 3 1 1 1 
		1 2 3;
	setAttr -s 11 ".kix[5:10]"  0.078234605491161346 0.065660685300827026 
		0.097513444721698761 0.2730908989906311 0.13333338499069214 0.39999997615814209;
	setAttr -s 11 ".kiy[5:10]"  -0.506081223487854 -0.061562199145555496 
		0.11824755370616913 0.89092254638671875 0.36956888437271118 0;
	setAttr -s 11 ".kox[5:10]"  0.052156433463096619 0.098490968346595764 
		0.32504478096961975 0.43694549798965454 0.39999997615814209 0.39999997615814209;
	setAttr -s 11 ".koy[5:10]"  -0.33738762140274048 -0.092343144118785858 
		0.39415857195854187 1.4254759550094604 0.50537210702896118 0;
createNode animCurveTL -n "rat_IKSplineTail1_M_translateX1";
	setAttr ".tan" 3;
	setAttr -s 7 ".ktv[0:6]"  0 -0.14721316863839706 3 -0.14721316863839706 
		19 -0.082691500924327754 29 -0.22257609314888288 33 -0.37109503324247556 37 -0.45475906958614831 
		45 -0.14721316863839706;
	setAttr -s 7 ".kit[3:6]"  1 2 3 3;
	setAttr -s 7 ".kot[3:6]"  1 2 3 3;
	setAttr -s 7 ".kix[3:6]"  0.26850911974906921 0.13333338499069214 
		0.13333332538604736 0.26666665077209473;
	setAttr -s 7 ".kiy[3:6]"  -0.25613364577293396 -0.14851893484592438 
		0 0;
	setAttr -s 7 ".kox[3:6]"  0.21480737626552582 0.13333332538604736 
		0.26666665077209473 0.26666665077209473;
	setAttr -s 7 ".koy[3:6]"  -0.20490695536136627 -0.08366403728723526 
		0 0;
createNode animCurveTU -n "rat_PoleLegFront_R_follow1";
	setAttr ".tan" 2;
	setAttr -s 13 ".ktv[0:12]"  0 10 2 10 3 10 4 10 5 10 15 10 17 10 19 
		10 23 10 29 10 35 10 40 10 45 10;
createNode animCurveTL -n "rat_PoleLegFront_R_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 15 ".ktv[0:14]"  0 -0.02737012108107054 2 -0.02737012108107054 
		3 -0.019132126145601638 4 0.030442791673862182 5 0.016414508653775778 15 0.00087630681570737641 
		16 -0.045053698052402266 17 -0.21745309387103634 18 -0.24029303953088185 19 -0.25824615195659006 
		23 -0.25824615195659006 29 -0.25824615195659006 35 -0.20226849358494869 40 -0.051559413353606559 
		45 -0.02737012108107054;
createNode animCurveTL -n "rat_PoleLegFront_R_translateY1";
	setAttr ".tan" 2;
	setAttr -s 15 ".ktv[0:14]"  0 0.023202672652752949 2 0.023202672652752949 
		3 0.053936934258455874 4 -0.37524737869345742 5 -0.70316516679612395 15 -0.6035455468585621 
		16 -0.57802063300620277 17 -0.32961814407109519 18 -0.228304590575931 19 -0.10598681833191442 
		23 -0.10598681833191442 29 -0.10598681833191442 35 -0.084456949727436947 40 -0.0069494227513181572 
		45 0.023202672652752949;
createNode animCurveTL -n "rat_PoleLegFront_R_translateX1";
	setAttr ".tan" 2;
	setAttr -s 15 ".ktv[0:14]"  0 -0.14312606150235696 2 -0.14312606150235696 
		3 -0.29728347987865289 4 -0.5939668736178475 5 -0.69325915181667841 15 -0.39693999885069087 
		16 -0.53995289489559817 17 -0.31375819575716424 18 -0.11355832297115084 19 -0.045084737472198384 
		23 -0.045084737472198384 29 -0.045084737472198384 35 -0.045084737472198384 40 -0.096756422122944163 
		45 -0.14312606150235696;
createNode animCurveTA -n "rat_IKLegFrontBall_R_rotateX1";
	setAttr ".tan" 3;
	setAttr -s 20 ".ktv[0:19]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 31 -8.5939630863551102 35 0 40 0 43 -3.4172424027695398 
		45 0;
createNode animCurveTA -n "rat_IKLegFrontHeel_R_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_IKLegFrontHeel_R_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 -3.9756933518293979e-016 2 0 3 -3.9756933518293979e-016 
		4 -3.9756933518293979e-016 5 0 7 0 9 0 11 0 13 0 15 0 16 0 17 0 19 0 23 0 29 0 35 
		0 40 0 45 -3.9756933518293979e-016;
createNode animCurveTA -n "rat_IKLegFrontHeel_R_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTU -n "rat_IKLegFront_R_Lenght4";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 1 2 1 3 1 4 1 5 1 10 1 11 1 12 1 14 1 
		16 1 19 1 23 1 29 1 35 1 40 1 45 1;
	setAttr -s 16 ".kit[2:15]"  1 2 3 2 2 2 2 1 
		2 2 2 2 2 2;
	setAttr -s 16 ".kot[2:15]"  1 2 3 2 2 2 2 1 
		2 2 2 2 2 2;
	setAttr -s 16 ".kix[2:15]"  0.066666670143604279 0.033333338797092438 
		0.033333331346511841 0.1666666716337204 0.033333331346511841 0.033333331346511841 
		0.066666662693023682 0.066666662693023682 0.099999964237213135 0.13333332538604736 
		0.19999998807907104 0.19999998807907104 0.16666674613952637 0.16666662693023682;
	setAttr -s 16 ".kiy[2:15]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 16 ".kox[2:15]"  0.033333331346511841 0.033333331346511841 
		0.1666666716337204 0.033333331346511841 0.033333331346511841 0.066666662693023682 
		0.066666692495346069 0.1666666567325592 0.13333332538604736 0.19999998807907104 0.19999998807907104 
		0.16666674613952637 0.16666662693023682 0;
	setAttr -s 16 ".koy[2:15]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegFront_R_Lenght3";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 1 2 1 3 1 4 1 5 1 10 1 11 1 12 1 14 1 
		16 1 19 1 23 1 29 1 35 1 40 1 45 1;
	setAttr -s 16 ".kit[2:15]"  1 2 3 2 2 2 2 1 
		2 2 2 2 2 2;
	setAttr -s 16 ".kot[2:15]"  1 2 3 2 2 2 2 1 
		2 2 2 2 2 2;
	setAttr -s 16 ".kix[2:15]"  0.066666670143604279 0.033333338797092438 
		0.033333331346511841 0.1666666716337204 0.033333331346511841 0.033333331346511841 
		0.066666662693023682 0.066666662693023682 0.099999964237213135 0.13333332538604736 
		0.19999998807907104 0.19999998807907104 0.16666674613952637 0.16666662693023682;
	setAttr -s 16 ".kiy[2:15]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 16 ".kox[2:15]"  0.033333331346511841 0.033333331346511841 
		0.1666666716337204 0.033333331346511841 0.033333331346511841 0.066666662693023682 
		0.066666692495346069 0.1666666567325592 0.13333332538604736 0.19999998807907104 0.19999998807907104 
		0.16666674613952637 0.16666662693023682 0;
	setAttr -s 16 ".koy[2:15]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegFront_R_antiPop1";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 0 2 0 3 0 4 0 5 0 10 0 11 0 12 0 14 0 
		16 0 19 0 23 0 29 0 35 0 40 0 45 0;
	setAttr -s 16 ".kit[2:15]"  1 2 3 2 2 2 2 1 
		2 2 2 2 2 2;
	setAttr -s 16 ".kot[2:15]"  1 2 3 2 2 2 2 1 
		2 2 2 2 2 2;
	setAttr -s 16 ".kix[2:15]"  0.066666670143604279 0.033333338797092438 
		0.033333331346511841 0.1666666716337204 0.033333331346511841 0.033333331346511841 
		0.066666662693023682 0.066666662693023682 0.099999964237213135 0.13333332538604736 
		0.19999998807907104 0.19999998807907104 0.16666674613952637 0.16666662693023682;
	setAttr -s 16 ".kiy[2:15]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 16 ".kox[2:15]"  0.033333331346511841 0.033333331346511841 
		0.1666666716337204 0.033333331346511841 0.033333331346511841 0.066666662693023682 
		0.066666692495346069 0.1666666567325592 0.13333332538604736 0.19999998807907104 0.19999998807907104 
		0.16666674613952637 0.16666662693023682 0;
	setAttr -s 16 ".koy[2:15]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegFront_R_stretchy1";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 0 2 0 3 0 4 0 5 0 10 0 11 0 12 0 14 0 
		16 0 19 0 23 0 29 0 35 0 40 0 45 0;
	setAttr -s 16 ".kit[2:15]"  1 2 3 2 2 2 2 1 
		2 2 2 2 2 2;
	setAttr -s 16 ".kot[2:15]"  1 2 3 2 2 2 2 1 
		2 2 2 2 2 2;
	setAttr -s 16 ".kix[2:15]"  0.066666670143604279 0.033333338797092438 
		0.033333331346511841 0.1666666716337204 0.033333331346511841 0.033333331346511841 
		0.066666662693023682 0.066666662693023682 0.099999964237213135 0.13333332538604736 
		0.19999998807907104 0.19999998807907104 0.16666674613952637 0.16666662693023682;
	setAttr -s 16 ".kiy[2:15]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 16 ".kox[2:15]"  0.033333331346511841 0.033333331346511841 
		0.1666666716337204 0.033333331346511841 0.033333331346511841 0.066666662693023682 
		0.066666692495346069 0.1666666567325592 0.13333332538604736 0.19999998807907104 0.19999998807907104 
		0.16666674613952637 0.16666662693023682 0;
	setAttr -s 16 ".koy[2:15]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegFront_R_legAim1";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 10 2 10 3 10 4 10 5 10 10 10 11 10 12 
		10 14 10 16 10 19 10 23 10 29 10 35 10 40 10 45 10;
	setAttr -s 16 ".kit[2:15]"  1 2 3 2 2 2 2 1 
		2 2 2 2 2 2;
	setAttr -s 16 ".kot[2:15]"  1 2 3 2 2 2 2 1 
		2 2 2 2 2 2;
	setAttr -s 16 ".kix[2:15]"  0.066666670143604279 0.033333338797092438 
		0.033333331346511841 0.1666666716337204 0.033333331346511841 0.033333331346511841 
		0.066666662693023682 0.066666662693023682 0.099999964237213135 0.13333332538604736 
		0.19999998807907104 0.19999998807907104 0.16666674613952637 0.16666662693023682;
	setAttr -s 16 ".kiy[2:15]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 16 ".kox[2:15]"  0.033333331346511841 0.033333331346511841 
		0.1666666716337204 0.033333331346511841 0.033333331346511841 0.066666662693023682 
		0.066666692495346069 0.1666666567325592 0.13333332538604736 0.19999998807907104 0.19999998807907104 
		0.16666674613952637 0.16666662693023682 0;
	setAttr -s 16 ".koy[2:15]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegFront_R_rollAngle1";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 25 2 25 3 25 4 25 5 25 10 25 11 25 12 
		25 14 25 16 25 19 25 23 25 29 25 35 25 40 25 45 25;
	setAttr -s 16 ".kit[2:15]"  1 2 3 2 2 2 2 1 
		2 2 2 2 2 2;
	setAttr -s 16 ".kot[2:15]"  1 2 3 2 2 2 2 1 
		2 2 2 2 2 2;
	setAttr -s 16 ".kix[2:15]"  0.066666670143604279 0.033333338797092438 
		0.033333331346511841 0.1666666716337204 0.033333331346511841 0.033333331346511841 
		0.066666662693023682 0.066666662693023682 0.099999964237213135 0.13333332538604736 
		0.19999998807907104 0.19999998807907104 0.16666674613952637 0.16666662693023682;
	setAttr -s 16 ".kiy[2:15]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 16 ".kox[2:15]"  0.033333331346511841 0.033333331346511841 
		0.1666666716337204 0.033333331346511841 0.033333331346511841 0.066666662693023682 
		0.066666692495346069 0.1666666567325592 0.13333332538604736 0.19999998807907104 0.19999998807907104 
		0.16666674613952637 0.16666662693023682 0;
	setAttr -s 16 ".koy[2:15]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegFront_R_roll1";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 0 2 0 3 0 4 0 5 0 10 0 11 0 12 0 14 0 
		16 0 19 0 23 0 29 0 35 0 40 0 45 0;
	setAttr -s 16 ".kit[2:15]"  1 2 3 2 2 2 2 1 
		2 2 2 2 2 2;
	setAttr -s 16 ".kot[2:15]"  1 2 3 2 2 2 2 1 
		2 2 2 2 2 2;
	setAttr -s 16 ".kix[2:15]"  0.066666670143604279 0.033333338797092438 
		0.033333331346511841 0.1666666716337204 0.033333331346511841 0.033333331346511841 
		0.066666662693023682 0.066666662693023682 0.099999964237213135 0.13333332538604736 
		0.19999998807907104 0.19999998807907104 0.16666674613952637 0.16666662693023682;
	setAttr -s 16 ".kiy[2:15]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 16 ".kox[2:15]"  0.033333331346511841 0.033333331346511841 
		0.1666666716337204 0.033333331346511841 0.033333331346511841 0.066666662693023682 
		0.066666692495346069 0.1666666567325592 0.13333332538604736 0.19999998807907104 0.19999998807907104 
		0.16666674613952637 0.16666662693023682 0;
	setAttr -s 16 ".koy[2:15]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegFront_R_swivel1";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 0 2 0 3 0 4 0 5 0 10 0 11 0 12 0 14 0 
		16 0 19 0 23 0 29 0 35 0 40 0 45 0;
	setAttr -s 16 ".kit[2:15]"  1 2 3 2 2 2 2 1 
		2 2 2 2 2 2;
	setAttr -s 16 ".kot[2:15]"  1 2 3 2 2 2 2 1 
		2 2 2 2 2 2;
	setAttr -s 16 ".kix[2:15]"  0.066666670143604279 0.033333338797092438 
		0.033333331346511841 0.1666666716337204 0.033333331346511841 0.033333331346511841 
		0.066666662693023682 0.066666662693023682 0.099999964237213135 0.13333332538604736 
		0.19999998807907104 0.19999998807907104 0.16666674613952637 0.16666662693023682;
	setAttr -s 16 ".kiy[2:15]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 16 ".kox[2:15]"  0.033333331346511841 0.033333331346511841 
		0.1666666716337204 0.033333331346511841 0.033333331346511841 0.066666662693023682 
		0.066666692495346069 0.1666666567325592 0.13333332538604736 0.19999998807907104 0.19999998807907104 
		0.16666674613952637 0.16666662693023682 0;
	setAttr -s 16 ".koy[2:15]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "rat_IKLegFront_R_rotateZ1";
	setAttr ".tan" 3;
	setAttr -s 15 ".ktv[0:14]"  0 10.555261301844832 2 10.555261301844832 
		3 10.555261301844832 4 14.976527870158488 5 -3.181 10 -3.181 11 0.5030977953962904 
		14 3.0860638425128957 16 1.5949572306793851 19 0 23 0 29 0 35 10.555261301844832 
		40 10.555261301844832 45 10.555261301844832;
	setAttr -s 15 ".kit[0:14]"  9 3 1 3 3 3 1 1 
		1 3 9 3 3 3 3;
	setAttr -s 15 ".kot[0:14]"  9 3 1 3 3 3 1 1 
		1 3 9 3 3 3 3;
	setAttr -s 15 ".kix[2:14]"  0.066666670143604279 0.033333338797092438 
		0.033333331346511841 0.1666666716337204 0.020866744220256805 0.099342234432697296 
		0.062678419053554535 0.099999964237213135 0.13333332538604736 0.19999998807907104 
		0.19999998807907104 0.16666674613952637 0.16666662693023682;
	setAttr -s 15 ".kiy[2:14]"  0 0 0 0 0.03514152392745018 -0.01158327329903841 
		-0.027870642021298409 0 0 0 0 0 0;
	setAttr -s 15 ".kox[2:14]"  0.033333331346511841 0.033333331346511841 
		0.1666666716337204 0.033333331346511841 0.087529979646205902 0.066009007394313812 
		0.096011228859424591 0.13333332538604736 0.19999998807907104 0.19999998807907104 
		0.16666674613952637 0.16666662693023682 0.16666662693023682;
	setAttr -s 15 ".koy[2:14]"  0 0 0 0 0.1474086195230484 -0.0076966285705566406 
		-0.04269244521856308 0 0 0 0 0 0;
createNode animCurveTA -n "rat_IKLegFront_R_rotateY1";
	setAttr ".tan" 9;
	setAttr -s 12 ".ktv[0:11]"  0 0 2 0 3 0 4 -79.955842450653279 5 -84.076579976699051 
		16 -84.088233539150934 19 0 23 0 29 0 35 0 40 0 45 0;
	setAttr -s 12 ".kit[1:11]"  3 1 1 3 3 3 9 9 
		9 9 9;
	setAttr -s 12 ".kot[1:11]"  3 1 1 3 3 3 9 9 
		9 9 9;
	setAttr -s 12 ".kix[2:11]"  0.066666670143604279 0.03308727964758873 
		0.033333331346511841 0.36666667461395264 0.099999964237213135 0.13333332538604736 
		0.19999998807907104 0.19999998807907104 0.16666674613952637 0.16666662693023682;
	setAttr -s 12 ".kiy[2:11]"  0 -0.2878032922744751 0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[2:11]"  0.033333331346511841 0.033087272197008133 
		0.36666667461395264 0.099999964237213135 0.13333332538604736 0.19999998807907104 
		0.19999998807907104 0.16666674613952637 0.16666662693023682 0.16666662693023682;
	setAttr -s 12 ".koy[2:11]"  0 -0.28780320286750793 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "rat_IKLegFront_R_rotateX1";
	setAttr ".tan" 3;
	setAttr -s 17 ".ktv[0:16]"  0 0 2 0 3 0 4 -22.020171467781655 5 2.4 
		10 2.4 11 2.4 12 2.4 14 2.4 16 2.4 18 19.589623383087762 19 0 23 0 29 0 35 0 40 0 
		45 0;
	setAttr -s 17 ".kit[0:16]"  9 3 1 3 3 2 2 2 
		2 3 3 3 3 9 9 9 9;
	setAttr -s 17 ".kot[0:16]"  9 3 1 3 3 2 2 2 
		2 3 3 3 3 9 9 9 9;
	setAttr -s 17 ".kix[2:16]"  0.066666670143604279 0.033333338797092438 
		0.033333331346511841 0.1666666716337204 0.033333331346511841 0.033333331346511841 
		0.066666662693023682 0.066666692495346069 0.066666662693023682 0.033333301544189453 
		0.13333332538604736 0.19999998807907104 0.19999998807907104 0.16666674613952637 0.16666662693023682;
	setAttr -s 17 ".kiy[2:16]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 17 ".kox[2:16]"  0.033333331346511841 0.033333331346511841 
		0.1666666716337204 0.033333331346511841 0.033333331346511841 0.066666662693023682 
		0.066666692495346069 0.066666662693023682 0.033333301544189453 0.13333332538604736 
		0.19999998807907104 0.19999998807907104 0.16666674613952637 0.16666662693023682 0.16666662693023682;
	setAttr -s 17 ".koy[2:16]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "rat_IKLegFront_R_translateZ1";
	setAttr ".tan" 9;
	setAttr -s 21 ".ktv[0:20]"  0 0 2 0 3 0 4 1.8546978835084267 5 2.7606932496084395 
		6 2.8299577885538647 7 2.8454367921390333 8 2.8471341769159135 9 2.8294690963910782 
		10 2.7542816098891136 11 2.5487920279483212 12 2.1697386763105007 14 1.3985291052195652 
		16 0.70709379088266389 18 0.07255819771726113 19 0 23 0 29 0 35 0 40 0 45 0;
	setAttr -s 21 ".kit[1:20]"  3 1 1 1 1 1 1 1 
		1 9 9 9 9 9 3 3 9 9 9 9;
	setAttr -s 21 ".kot[1:20]"  3 1 1 1 1 1 1 1 
		1 9 9 9 9 9 3 3 9 9 9 9;
	setAttr -s 21 ".kix[2:20]"  0.066666670143604279 0.032141245901584625 
		0.034944109618663788 0.03190748393535614 0.034395582973957062 0.033264875411987305 
		0.034120079129934311 0.033590178936719894 0.033333331346511841 0.033333331346511841 
		0.066666662693023682 0.066666692495346069 0.066666662693023682 0.033333301544189453 
		0.13333332538604736 0.19999998807907104 0.19999998807907104 0.16666674613952637 0.16666662693023682;
	setAttr -s 21 ".kiy[2:20]"  0 1.7623783349990845 0.11449543386697769 
		0.027485804632306099 0.0046747499145567417 -0.0017467838479205966 -0.034267030656337738 
		-0.12958011031150818 -0.29227146506309509 -0.38342097401618958 -0.73132228851318359 
		-0.66298562288284302 -0.47139599919319153 0 0 0 0 0 0;
	setAttr -s 21 ".kox[2:20]"  0.033333331346511841 0.032141231000423431 
		0.03494412824511528 0.031907480210065842 0.034395594149827957 0.033264860510826111 
		0.034120075404644012 0.033590178936719894 0.033333331346511841 0.066666662693023682 
		0.066666692495346069 0.066666662693023682 0.033333301544189453 0.13333332538604736 
		0.19999998807907104 0.19999998807907104 0.16666674613952637 0.16666662693023682 0.16666662693023682;
	setAttr -s 21 ".koy[2:20]"  0 1.7623777389526367 0.1144954040646553 
		0.027485813945531845 0.0046747513115406036 -0.0017467832658439875 -0.034267034381628036 
		-0.12958009541034698 -0.29227146506309509 -0.76684194803237915 -0.73132258653640747 
		-0.66298532485961914 -0.23569779098033905 0 0 0 0 0 0;
createNode animCurveTL -n "rat_IKLegFront_R_translateY1";
	setAttr ".tan" 3;
	setAttr -s 18 ".ktv[0:17]"  0 0.38582961184709008 2 0.38582961184709008 
		3 0.38582961184709008 4 -0.48150644714806412 5 -0.92910910063845875 6 -0.94616938881324031 
		7 -0.94828179389289113 10 -0.94957947289570943 11 -0.9584164177449126 12 -0.99519246948213724 
		14 -1.1788876015661789 16 -1.4228357397914413 19 -0.92793809201912913 23 -0.87503857141588903 
		29 -0.87503857141588903 35 0.10942071138071396 40 0.10942071138071396 45 0.38582961184709008;
	setAttr -s 18 ".kit[3:17]"  1 1 1 9 1 1 1 1 
		3 1 3 3 3 3 3;
	setAttr -s 18 ".kot[3:17]"  1 1 1 9 1 1 1 1 
		3 1 3 3 3 3 3;
	setAttr -s 18 ".kix[3:17]"  0.031736496835947037 0.034636437892913818 
		0.03315730020403862 0.033333331346511841 0.10347055643796921 0.034146137535572052 
		0.036409322172403336 0.065938495099544525 0.066666692495346069 0.059190861880779266 
		0.13333332538604736 0.19999998807907104 0.19999998807907104 0.16666674613952637 0.16666662693023682;
	setAttr -s 18 ".kiy[3:17]"  -0.77896636724472046 -0.045157440006732941 
		-0.0030375546775758266 -0.00085252092685550451 -0.0032349992543458939 -0.016595935449004173 
		-0.066661030054092407 -0.23491832613945007 0 0.076234012842178345 0 0 0 0 0;
	setAttr -s 18 ".kox[3:17]"  0.031736493110656738 0.034636441618204117 
		0.03315730020403862 0.10000000894069672 0.034490201622247696 0.034146137535572052 
		0.072818651795387268 0.065938524901866913 0.099999964237213135 0.11838173121213913 
		0.19999998807907104 0.19999998807907104 0.16666674613952637 0.16666662693023682 0.16666662693023682;
	setAttr -s 18 ".koy[3:17]"  -0.77896630764007568 -0.045157469809055328 
		-0.0030375546775758266 -0.002557563129812479 -0.0010783335892483592 -0.016595937311649323 
		-0.13332207500934601 -0.23491840064525604 0 0.1524680107831955 0 0 0 0 0;
createNode animCurveTL -n "rat_IKLegFront_R_translateX1";
	setAttr ".tan" 3;
	setAttr -s 12 ".ktv[0:11]"  0 -0.012835510537475885 2 -0.012835510537475885 
		3 -0.012835510537475885 4 -0.229779956765025 5 0.14338604707707642 16 0.14338604707707642 
		19 0.01862562818975172 23 0.01862562818975172 29 0.01862562818975172 35 -0.012835510537475885 
		40 -0.012835510537475885 45 -0.012835510537475885;
	setAttr -s 12 ".kit[0:11]"  9 3 3 3 3 3 3 3 
		3 3 3 3;
	setAttr -s 12 ".kot[0:11]"  9 3 3 3 3 3 3 3 
		3 3 3 3;
createNode animCurveTA -n "rat_HipSwingerRoot_M_rotateZ1";
	setAttr ".tan" 1;
	setAttr -s 12 ".ktv[0:11]"  0 -10.507309270186466 3 -10.507309270186466 
		4 8.9470213436801043 6 0.24349147277486524 9 -0.092722348551968342 13 6.334224974432586 
		16 5.3534579139982412 19 -13.307345027796835 23 -26.224891869134584 27 -19.801746219279785 
		31 -14.391472798602672 45 -10.507309270186466;
	setAttr -s 12 ".kit[0:11]"  10 3 3 1 1 9 1 1 
		3 1 1 3;
	setAttr -s 12 ".kot[0:11]"  10 3 3 1 1 9 1 1 
		3 1 1 3;
	setAttr -s 12 ".kix[3:11]"  0.05854024738073349 0.097143195569515228 
		0.13333332538604736 0.10483418405056 0.095796473324298859 0.13333332538604736 0.12647083401679993 
		0.10724912583827972 0.46666669845581055;
	setAttr -s 12 ".kiy[3:11]"  -0.040853314101696014 0.038530886173248291 
		0.054316438734531403 -0.13012121617794037 -0.29475435614585876 0 0.13467571139335632 
		0.045301534235477448 0;
	setAttr -s 12 ".kox[3:11]"  0.091872654855251312 0.13047619163990021 
		0.10000002384185791 0.10483412444591522 0.12912943959236145 0.13333332538604736 0.12647083401679993 
		0.44057631492614746 0.46666669845581055;
	setAttr -s 12 ".koy[3:11]"  -0.06411491334438324 0.051752090454101563 
		0.040737338364124298 -0.13012112677097321 -0.39731603860855103 0 0.13467571139335632 
		0.1860973984003067 0;
createNode animCurveTA -n "rat_HipSwingerRoot_M_rotateY1";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 -3.9401506072152763 19 -3.9401506072152763 
		23 -2.5146932038420697 27 -2.696365253208135 45 -3.9401506072152763;
	setAttr -s 5 ".kit[2:4]"  3 1 10;
	setAttr -s 5 ".kot[2:4]"  3 1 10;
	setAttr -s 5 ".kix[3:4]"  0.057730209082365036 0.60000002384185791;
	setAttr -s 5 ".kiy[3:4]"  -0.0027793666813522577 0;
	setAttr -s 5 ".kox[3:4]"  0.52436524629592896 0.60000002384185791;
	setAttr -s 5 ".koy[3:4]"  -0.025245076045393944 0;
createNode animCurveTA -n "rat_HipSwingerRoot_M_rotateX1";
	setAttr ".tan" 1;
	setAttr -s 8 ".ktv[0:7]"  0 1.5206250006361597 19 1.5206250006361597 
		23 11.897325831700185 27 11.544303218602339 31 5.1178753342248093 35 1.7527464333615617 
		40 6.6319807230170555 45 1.5206250006361597;
	setAttr -s 8 ".kit[0:7]"  10 10 1 1 1 3 3 3;
	setAttr -s 8 ".kot[0:7]"  10 10 1 1 1 3 3 3;
	setAttr -s 8 ".kix[2:7]"  0.12777304649353027 0.12920477986335754 
		0.12865722179412842 0.13333332538604736 0.16666674613952637 0.16666662693023682;
	setAttr -s 8 ".kiy[2:7]"  0.053259965032339096 -0.046019304543733597 
		-0.11099029332399368 0 0 0;
	setAttr -s 8 ".kox[2:7]"  0.12777304649353027 0.12920476496219635 
		0.12865722179412842 0.16666674613952637 0.16666662693023682 0.16666662693023682;
	setAttr -s 8 ".koy[2:7]"  0.053259957581758499 -0.046019300818443298 
		-0.11099029332399368 0 0 0;
createNode animCurveTA -n "rat_money_CTRL_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_money_CTRL_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_money_CTRL_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTL -n "rat_money_CTRL_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTL -n "rat_money_CTRL_translateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTL -n "rat_money_CTRL_translateX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_bag_CTRL_rotateZ1";
	setAttr ".tan" 3;
	setAttr -s 15 ".ktv[0:14]"  0 0 2 0 4 8.8554843256175495 7 -4.872072927159099 
		10 -16.833936814548562 14 -23.615665023036005 16 -17.426361216846253 17 3.8432852844164325 
		19 5.3746629759876052 22 -2.167449309960749 25 2.779986752478214 29 2.2910220913498369 
		33 0.96939247802498907 38 0.21491546177938933 45 0;
	setAttr -s 15 ".kit[3:14]"  1 9 3 9 9 9 3 3 
		1 9 1 3;
	setAttr -s 15 ".kot[3:14]"  1 9 3 9 9 9 3 3 
		1 9 1 3;
	setAttr -s 15 ".kix[3:14]"  0.08350721001625061 0.10000000894069672 
		0.13333332538604736 0.066666692495346069 0.033333301544189453 0.066666662693023682 
		0.10000002384185791 0.099999964237213135 0.13279047608375549 0.13333338499069214 
		0.16978992521762848 0.23333334922790527;
	setAttr -s 15 ".kiy[3:14]"  -0.23318536579608917 -0.14020174741744995 
		0 0.31949955224990845 0.13265089690685272 -0.041962835937738419 0 0 -0.015702037140727043 
		-0.016104403883218765 -0.0061091543175280094 0;
	setAttr -s 15 ".kox[3:14]"  0.083507224917411804 0.13333332538604736 
		0.066666692495346069 0.033333301544189453 0.066666662693023682 0.10000002384185791 
		0.099999964237213135 0.13333332538604736 0.13279053568840027 0.16666662693023682 
		0.23645693063735962 0.23333334922790527;
	setAttr -s 15 ".koy[3:14]"  -0.23318541049957275 -0.18693564832210541 
		0 0.15974955260753632 0.26530203223228455 -0.062944270670413971 0 0 -0.015702046453952789 
		-0.020130492746829987 -0.0085078766569495201 0;
createNode animCurveTA -n "rat_bag_CTRL_rotateY1";
	setAttr ".tan" 3;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 0 4 -0.28184689715697175 7 -2.225546017088941 
		10 -3.2132796820043623 17 -3.1171152796888535 25 -1.1726895763676379 29 3.0671234944687034 
		33 -0.51553388616414275 38 1.02956072213922 45 0;
	setAttr -s 11 ".kit[2:10]"  9 9 1 1 1 9 3 3 
		3;
	setAttr -s 11 ".kot[2:10]"  9 9 1 1 1 9 3 3 
		3;
	setAttr -s 11 ".kix[4:10]"  0.10181514918804169 0.23859629034996033 
		0.28814730048179626 0.13333332538604736 0.13333338499069214 0.16666662693023682 0.23333334922790527;
	setAttr -s 11 ".kiy[4:10]"  -0.0037587382830679417 0.012910970486700535 
		0.066524654626846313 0.005734764039516449 0 0 0;
	setAttr -s 11 ".kox[4:10]"  0.23514878749847412 0.27192983031272888 
		0.15480700135231018 0.13333338499069214 0.16666662693023682 0.23333334922790527 0.23333334922790527;
	setAttr -s 11 ".koy[4:10]"  -0.0086810551583766937 0.014714721590280533 
		0.035740338265895844 0.0057347663678228855 0 0 0;
createNode animCurveTA -n "rat_bag_CTRL_rotateX1";
	setAttr ".tan" 9;
	setAttr -s 15 ".ktv[0:14]"  0 0 2 0 4 0.34388367435125866 7 0.10320476103174911 
		10 0.21382722672499313 14 1.0226398908114287 16 1.3886853636617953 17 1.4952574914789654 
		19 1.5116143498974965 22 1.3928969736975674 25 1.0756558575473354 29 0.58172431962553495 
		33 0.34512918722984759 38 0.045084229872652412 45 0;
	setAttr -s 15 ".kit[0:14]"  3 3 9 9 9 9 9 1 
		1 9 9 9 9 9 3;
	setAttr -s 15 ".kot[0:14]"  3 3 9 9 9 9 9 1 
		1 9 9 9 9 9 3;
	setAttr -s 15 ".kix[7:14]"  0.031827758997678757 0.06581580638885498 
		0.10000002384185791 0.099999964237213135 0.13333332538604736 0.13333338499069214 
		0.16666662693023682 0.23333334922790527;
	setAttr -s 15 ".kiy[7:14]"  0.00084962148685008287 -0.00060707330703735352 
		-0.0038044566754251719 -0.0060675563290715218 -0.0063750464469194412 -0.0041627287864685059 
		-0.0025098498445004225 0;
	setAttr -s 15 ".kox[7:14]"  0.065160855650901794 0.099149078130722046 
		0.099999964237213135 0.13333332538604736 0.13333338499069214 0.16666662693023682 
		0.23333334922790527 0.23333334922790527;
	setAttr -s 15 ".koy[7:14]"  0.0017394268652424216 -0.00091453321510925889 
		-0.0038044543471187353 -0.0080900769680738449 -0.0063750492408871651 -0.0052034077234566212 
		-0.003513790899887681 0;
createNode animCurveTL -n "rat_bag_CTRL_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 0 4 0 29 0 45 0;
createNode animCurveTL -n "rat_bag_CTRL_translateY1";
	setAttr ".tan" 2;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 0 4 0 29 0 45 0;
createNode animCurveTL -n "rat_bag_CTRL_translateX1";
	setAttr ".tan" 2;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 0 4 0 29 0 45 0;
createNode animCurveTU -n "rat_FKChest_M_scaleZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 1 2 1 3 1 4 1 5 1 7 1 9 1 11 1 13 1 15 
		1 16 1 17 1 19 1 23 1 29 1 35 1 40 1 45 1;
createNode animCurveTU -n "rat_FKChest_M_scaleY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0.99999999999999978 2 0.99999999999999978 
		3 0.99999999999999978 4 0.99999999999999978 5 0.99999999999999978 7 0.99999999999999978 
		9 0.99999999999999978 11 0.99999999999999978 13 0.99999999999999978 15 0.99999999999999978 
		16 0.99999999999999978 17 0.99999999999999978 19 0.99999999999999978 23 0.99999999999999978 
		29 0.99999999999999978 35 0.99999999999999978 40 0.99999999999999978 45 0.99999999999999978;
createNode animCurveTU -n "rat_FKChest_M_scaleX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0.99999999999999978 2 0.99999999999999978 
		3 0.99999999999999978 4 0.99999999999999978 5 0.99999999999999978 7 0.99999999999999978 
		9 0.99999999999999978 11 0.99999999999999978 13 0.99999999999999978 15 0.99999999999999978 
		16 0.99999999999999978 17 0.99999999999999978 19 0.99999999999999978 23 0.99999999999999978 
		29 0.99999999999999978 35 0.99999999999999978 40 0.99999999999999978 45 0.99999999999999978;
createNode animCurveTA -n "rat_FKChest_M_rotateZ1";
	setAttr ".tan" 9;
	setAttr -s 17 ".ktv[0:16]"  0 -5.066428676758755 2 -7.9742969355151141 
		3 2.5443835051808312 4 -1.0514066988216162 5 9.7365497364077367 7 13.872462408457922 
		9 18.30333236977096 11 17.333905404588759 13 12.335272833776347 17 8.6471447671549839 
		19 8.1397719672742284 21 21.7640310362513 23 8.4364786876540077 29 -2.94430447297544 
		35 -6.4730340114296849 40 -6.4730340114296849 45 -5.066428676758755;
	setAttr -s 17 ".kit[0:16]"  3 1 1 3 3 1 9 9 
		1 1 3 9 9 9 9 9 3;
	setAttr -s 17 ".kot[0:16]"  3 1 1 3 3 1 9 9 
		1 1 3 9 9 9 9 9 3;
	setAttr -s 17 ".kix[1:16]"  0.064654462039470673 0.03277096152305603 
		0.033333338797092438 0.033333331346511841 0.063521489500999451 0.066666677594184875 
		0.066666662693023682 0.063031934201717377 0.13645486533641815 0.066666662693023682 
		0.066666662693023682 0.066666662693023682 0.19999998807907104 0.19999998807907104 
		0.16666674613952637 0.16666662693023682;
	setAttr -s 17 ".kiy[1:16]"  0.21056172251701355 0.11410939693450928 
		0 0 0.10245227068662643 0.030206792056560516 -0.052081145346164703 -0.051767833530902863 
		-0.034776374697685242 0 0.0025892546400427818 -0.10781045258045197 -0.13011004030704498 
		-0.033593419939279556 0.012274951674044132 0;
	setAttr -s 17 ".kox[1:16]"  0.031321477144956589 0.032770968973636627 
		0.033333331346511841 0.066666662693023682 0.063521504402160645 0.066666662693023682 
		0.066666662693023682 0.12969772517681122 0.069787696003913879 0.066666662693023682 
		0.066666662693023682 0.19999998807907104 0.19999998807907104 0.16666674613952637 
		0.16666662693023682 0.16666662693023682;
	setAttr -s 17 ".koy[1:16]"  0.10200539976358414 0.11410940438508987 
		0 0 0.10245226323604584 0.030206784605979919 -0.052081145346164703 -0.10652013123035431 
		-0.017785826697945595 0 0.0025892546400427818 -0.3234313428401947 -0.13011004030704498 
		-0.027994530275464058 0.012274942360818386 0;
createNode animCurveTA -n "rat_FKChest_M_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 5 ".ktv[0:4]"  0 -0.47627649301494307 2 -0.88756830316988733 
		3 -0.73438532572664839 4 -1.2340444501908163 45 -0.47627649301494307;
createNode animCurveTA -n "rat_FKChest_M_rotateX1";
	setAttr ".tan" 9;
	setAttr -s 17 ".ktv[0:16]"  0 -0.99253490036387859 2 -0.60840687335504728 
		3 -0.42598891893283158 4 -0.35669589660069045 7 1.4870951769315657 9 2.3958627166373234 
		11 2.7789090813208994 13 2.5677670855614321 15 1.3175707992996974 16 -0.71782566483095123 
		17 -0.99920367987004921 19 -1.0498282627182642 23 -1.0772858613950624 29 -1.0772858613950624 
		35 -1.0594053809442687 40 -1.0196709755145139 45 -0.99253490036387859;
	setAttr -s 17 ".kit[0:16]"  3 1 2 9 1 9 1 1 
		1 1 1 9 9 9 9 9 9;
	setAttr -s 17 ".kot[0:16]"  3 1 2 9 1 9 1 1 
		1 1 1 9 9 9 9 9 9;
	setAttr -s 17 ".kix[1:16]"  0.065541930496692657 0.033333331346511841 
		0.033333338797092438 0.099321350455284119 0.066666677594184875 0.066568776965141296 
		0.080727934837341309 0.065613232553005219 0.041374586522579193 0.032604336738586426 
		0.066666662693023682 0.13333332538604736 0.19999998807907104 0.19999998807907104 
		0.16666674613952637 0.16666662693023682;
	setAttr -s 17 ".kiy[1:16]"  0.011023170314729214 0.0031837939750403166 
		0.0083474060520529747 0.025462990626692772 0.01127320434898138 0.00060629379004240036 
		-0.010208164341747761 -0.043568674474954605 -0.012596995569765568 -0.00093040335923433304 
		-0.00045426373253576458 -0.00019169019651599228 0.0001560366217745468 0.00054849230218678713 
		0.00058355525834485888 0.00047361385077238083;
	setAttr -s 17 ".kox[1:16]"  0.065541923046112061 0.033333338797092438 
		0.099999994039535522 0.065988115966320038 0.066666662693023682 0.066568776965141296 
		0.080727934837341309 0.03228011354804039 0.041374534368515015 0.0659375861287117 
		0.13333332538604736 0.19999998807907104 0.19999998807907104 0.16666674613952637 0.16666662693023682 
		0.16666662693023682;
	setAttr -s 17 ".koy[1:16]"  0.011023170314729214 0.0012093913974240422 
		0.025042211636900902 0.016917357221245766 0.011273201555013657 0.00060629379004240036 
		-0.010208161547780037 -0.021434726193547249 -0.012596984393894672 -0.0018816071096807718 
		-0.00090852746507152915 -0.00028753530932590365 0.0001560366217745468 0.00045707717072218657 
		0.00058355479268357158 0.00047361385077238083;
createNode animCurveTU -n "rat_FKBackB_M_scaleZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 1 2 1 3 1 4 1 5 1 7 1 9 1 11 1 13 1 15 
		1 16 1 17 1 19 1 23 1 29 1 35 1 40 1 45 1;
createNode animCurveTU -n "rat_FKBackB_M_scaleY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0.99999999999999978 2 0.99999999999999978 
		3 0.99999999999999978 4 0.99999999999999978 5 0.99999999999999978 7 0.99999999999999978 
		9 0.99999999999999978 11 0.99999999999999978 13 0.99999999999999978 15 0.99999999999999978 
		16 0.99999999999999978 17 0.99999999999999978 19 0.99999999999999978 23 0.99999999999999978 
		29 0.99999999999999978 35 0.99999999999999978 40 0.99999999999999978 45 0.99999999999999978;
createNode animCurveTU -n "rat_FKBackB_M_scaleX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0.99999999999999978 2 0.99999999999999978 
		3 0.99999999999999978 4 0.99999999999999978 5 0.99999999999999978 7 0.99999999999999978 
		9 0.99999999999999978 11 0.99999999999999978 13 0.99999999999999978 15 0.99999999999999978 
		16 0.99999999999999978 17 0.99999999999999978 19 0.99999999999999978 23 0.99999999999999978 
		29 0.99999999999999978 35 0.99999999999999978 40 0.99999999999999978 45 0.99999999999999978;
createNode animCurveTA -n "rat_FKBackB_M_rotateZ1";
	setAttr ".tan" 1;
	setAttr -s 20 ".ktv[0:19]"  0 -9.8819625697636226 2 -5.775034621920903 
		3 10.798043637600381 4 25.356313969061251 5 21.459983772404655 7 11.275360033144754 
		9 6.346306900376387 11 3.1388544647171304 13 0.82779180784459483 15 -0.18384952417946995 
		16 -0.0093499328630976663 17 7.5999026605710132 19 8.7969867601679326 21 3.2084316025278605 
		23 -5.7666152350542648 25 -8.125086523113394 29 -9.2077568811639701 35 -9.6809804985215617 
		40 -9.8420223653146497 45 -9.8819625697636226;
	setAttr -s 20 ".kit[0:19]"  3 9 1 3 1 1 9 9 
		9 1 1 9 9 1 9 9 1 1 1 3;
	setAttr -s 20 ".kot[0:19]"  3 9 1 3 1 1 9 9 
		9 1 1 9 9 1 9 9 1 1 1 3;
	setAttr -s 20 ".kix[2:19]"  0.029145773500204086 0.033333338797092438 
		0.031358934938907623 0.067553363740444183 0.066666677594184875 0.066666662693023682 
		0.066666662693023682 0.066446110606193542 0.031639110296964645 0.033333301544189453 
		0.066666662693023682 0.065826863050460815 0.066666662693023682 0.066666662693023682 
		0.145742267370224 0.20273783802986145 0.1628434807062149 0.16666662693023682;
	setAttr -s 20 ".kiy[2:19]"  0.34555935859680176 0 -0.10649807006120682 
		-0.10056251287460327 -0.071004413068294525 -0.048158127814531326 -0.028996061533689499 
		-0.010774986818432808 0.024009782820940018 0.051233161240816116 -0.038322813808917999 
		-0.14144328236579895 -0.098903603851795197 -0.020019751042127609 -0.010408153757452965 
		-0.005287831649184227 -0.0011531210038810968 0;
	setAttr -s 20 ".kox[2:19]"  0.029145777225494385 0.033333331346511841 
		0.064691923558712006 0.067553378641605377 0.066666662693023682 0.066666662693023682 
		0.066666662693023682 0.033112842589616776 0.031639043241739273 0.066666662693023682 
		0.066666662693023682 0.065826870501041412 0.066666662693023682 0.13333332538604736 
		0.21241030097007751 0.16940446197986603 0.16284336149692535 0.16666662693023682;
	setAttr -s 20 ".koy[2:19]"  0.34555938839912415 0 -0.21970020234584808 
		-0.10056255757808685 -0.071004398167133331 -0.048158127814531326 -0.028996061533689499 
		-0.0053696217946708202 0.024009726941585541 0.1024664118885994 -0.038322813808917999 
		-0.14144329726696014 -0.098903603851795197 -0.040039502084255219 -0.015169237740337849 
		-0.0044184261932969093 -0.0011531203053891659 0;
createNode animCurveTA -n "rat_FKBackB_M_rotateY1";
	setAttr ".tan" 1;
	setAttr -s 21 ".ktv[0:20]"  0 -0.26173116802236968 3 -0.37407078704431984 
		4 -0.79817565838126903 5 -1.2131566902952104 6 -1.4906568354550596 8 -1.7633678060980158 
		10 -1.7497932225022339 12 -1.3665319417439281 14 -0.80449844595018538 16 -0.58020928279562967 
		18 -0.55141306656813882 20 -0.63010884549863833 24 2.0741416012454952 27 -0.78560233903170373 
		30 -6.9146611199630064 32 -5.3643714370139897 36 3.1087859024053039 38 2.2546263667773183 
		41 -2.9368403716017792 43 -2.3935207862624588 45 -0.26173116802236968;
	setAttr -s 21 ".kit[3:20]"  9 1 1 1 1 9 1 3 
		3 3 1 3 9 1 9 1 1 1;
	setAttr -s 21 ".kot[3:20]"  9 1 1 1 1 9 1 3 
		3 3 1 3 9 1 9 1 1 1;
	setAttr -s 21 ".kix[0:20]"  0.099026717245578766 0.062175355851650238 
		0.03215431421995163 0.033333331346511841 0.032855138182640076 0.0674448162317276 
		0.06887286901473999 0.062891356647014618 0.066666662693023682 0.06769300252199173 
		0.066666662693023682 0.066666662693023682 0.13333332538604736 0.089201979339122772 
		0.10000002384185791 0.066666722297668457 0.1430380642414093 0.066666603088378906 
		0.10891308635473251 0.064977273344993591 0.066513866186141968;
	setAttr -s 21 ".kiy[0:20]"  0.0028052288107573986 -0.0092076733708381653 
		-0.007892620749771595 -0.0060430383309721947 -0.0033874842338263988 -0.0018195238662883639 
		0.0026126441080123186 0.0087465168908238411 0.0068619581870734692 0.0015796020161360502 
		0 0 0 -0.084039725363254547 0 0.058314085006713867 0.035804323852062225 -0.042206402868032455 
		-0.014938648790121078 0.022616572678089142 0.0077741728164255619;
	setAttr -s 21 ".kox[0:20]"  0.099026717245578766 0.028842959553003311 
		0.032154321670532227 0.033333331346511841 0.066188380122184753 0.067444831132888794 
		0.068872861564159393 0.062891356647014618 0.066666692495346069 0.067693009972572327 
		0.066666662693023682 0.13333332538604736 0.099999964237213135 0.0892019122838974 
		0.066666722297668457 0.13333332538604736 0.076368175446987152 0.10000002384185791 
		0.075578704476356506 0.098310507833957672 0.066513858735561371;
	setAttr -s 21 ".koy[0:20]"  0.0028052290435880423 -0.004271412268280983 
		-0.0078926244750618935 -0.0060430383309721947 -0.0068242624402046204 -0.0018195242155343294 
		0.0026126434095203876 0.0087465159595012665 0.0068619614467024803 0.0015796020161360502 
		0 0 0 -0.084039650857448578 0 0.11662806570529938 0.019115956500172615 -0.063309676945209503 
		-0.010366464965045452 0.034218836575746536 0.0077741718851029873;
createNode animCurveTA -n "rat_FKBackB_M_rotateX1";
	setAttr ".tan" 1;
	setAttr -s 22 ".ktv[0:21]"  0 0.191 3 0.24011176253271962 4 0.16116947428706457 
		5 -0.34835330912265317 6 -1.630184515517997 8 -6.3364004403993404 10 -6.4716513596784386 
		12 -4.6125460462559529 14 -3.5364290392631434 16 -2.8657935297465111 18 -1.5991495028120217 
		20 -0.62793886424358003 22 -0.22904266134037213 24 -0.6352115463587894 27 -2.1929249895035214 
		30 -1.4253655737517419 33 2.5684702314041594 36 -0.92216472385737036 39 -2.9529679806003899 
		41 -1.618240051485587 44 0.8478008318179584 45 0.19077821909836376;
	setAttr -s 22 ".kit[0:21]"  3 3 1 1 9 1 1 1 
		1 9 1 1 3 1 9 9 3 1 3 1 3 3;
	setAttr -s 22 ".kot[0:21]"  3 3 1 1 9 1 1 1 
		1 9 1 1 3 1 9 9 3 1 3 1 3 3;
	setAttr -s 22 ".kix[2:21]"  0.032469462603330612 0.033857986330986023 
		0.033333331346511841 0.074993237853050232 0.066266559064388275 0.06506095826625824 
		0.068520583212375641 0.066666692495346069 0.066320061683654785 0.066397756338119507 
		0.066666662693023682 0.065399192273616791 0.099999964237213135 0.10000002384185791 
		0.10000002384185791 0.088863439857959747 0.099999904632568359 0.060862801969051361 
		0.10000002384185791 0.033333301544189453;
	setAttr -s 22 ".kiy[2:21]"  -0.0037025557830929756 -0.013056868687272072 
		-0.034837041050195694 -0.023479633033275604 0.016791069880127907 0.029620066285133362 
		0.010367175564169884 0.016905957832932472 0.019859271124005318 0.012406693771481514 
		0 -0.015169966965913773 -0.0068953926675021648 0.041551012545824051 0 -0.05251060426235199 
		0 0.027547650039196014 0 0;
	setAttr -s 22 ".kox[2:21]"  0.032469470053911209 0.033857978880405426 
		0.066666677594184875 0.074993252754211426 0.066266544163227081 0.065060965716838837 
		0.068520575761795044 0.066666662693023682 0.066320069134235382 0.066397756338119507 
		0.066666662693023682 0.098732411861419678 0.10000002384185791 0.10000002384185791 
		0.10000002384185791 0.088863544166088104 0.066666722297668457 0.094194844365119934 
		0.033333301544189453 0.033333301544189453;
	setAttr -s 22 ".koy[2:21]"  -0.0037025560159236193 -0.013056867755949497 
		-0.069674097001552582 -0.023479634895920753 0.016791064292192459 0.029620066285133362 
		0.010367174632847309 0.016905948519706726 0.019859276711940765 0.012406692840158939 
		0 -0.022901926189661026 -0.0068953968584537506 0.041551012545824051 0 -0.052510667592287064 
		0 0.042634371668100357 0 0;
createNode animCurveTU -n "rat_FKBackA_M_scaleZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 1 2 1 3 1 4 1 5 1 7 1 9 1 11 1 13 1 15 
		1 16 1 17 1 19 1 23 1 29 1 35 1 40 1 45 1;
createNode animCurveTU -n "rat_FKBackA_M_scaleY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0.99999999999999978 2 0.99999999999999978 
		3 0.99999999999999978 4 0.99999999999999978 5 0.99999999999999978 7 0.99999999999999978 
		9 0.99999999999999978 11 0.99999999999999978 13 0.99999999999999978 15 0.99999999999999978 
		16 0.99999999999999978 17 0.99999999999999978 19 0.99999999999999978 23 0.99999999999999978 
		29 0.99999999999999978 35 0.99999999999999978 40 0.99999999999999978 45 0.99999999999999978;
createNode animCurveTU -n "rat_FKBackA_M_scaleX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0.99999999999999978 2 0.99999999999999978 
		3 0.99999999999999978 4 0.99999999999999978 5 0.99999999999999978 7 0.99999999999999978 
		9 0.99999999999999978 11 0.99999999999999978 13 0.99999999999999978 15 0.99999999999999978 
		16 0.99999999999999978 17 0.99999999999999978 19 0.99999999999999978 23 0.99999999999999978 
		29 0.99999999999999978 35 0.99999999999999978 40 0.99999999999999978 45 0.99999999999999978;
createNode animCurveTA -n "rat_FKBackA_M_rotateZ1";
	setAttr ".tan" 1;
	setAttr -s 18 ".ktv[0:17]"  0 16.291300957444619 2 19.496885562820307 
		3 -13.358102528501233 4 -8.2254682714182081 5 2.0692189015832492 7 19.134465926475265 
		9 22.985096592617133 11 21.898721618791093 13 15.130051446945963 17 0.45899939422024716 
		19 -10.034248374324795 21 -9.9592302995413462 23 -1.7703817232989072 29 5.626212068196593 
		35 11.218625982433119 40 15.199820704576172 43 16.21926911078992 45 16.291300957444619;
	setAttr -s 18 ".kit[0:17]"  3 3 3 1 1 1 1 1 
		9 1 1 1 9 1 9 1 1 3;
	setAttr -s 18 ".kot[0:17]"  3 3 3 1 1 1 1 1 
		9 1 1 1 9 1 9 1 1 3;
	setAttr -s 18 ".kix[3:17]"  0.031781595200300217 0.032926518470048904 
		0.066833198070526123 0.066187150776386261 0.067808911204338074 0.066666662693023682 
		0.13209801912307739 0.06844647228717804 0.068189926445484161 0.066666662693023682 
		0.20275254547595978 0.19999998807907104 0.18519316613674164 0.10633011907339096 0.066666722297668457;
	setAttr -s 18 ".kiy[3:17]"  0.18394008278846741 0.1671186089515686 
		0.17812131345272064 0.013906076550483704 -0.055178239941596985 -0.12473125010728836 
		-0.31749281287193298 -0.075201518833637238 0.054504238069057465 0.068004317581653595 
		0.095733910799026489 0.091140516102313995 0.064158916473388672 0.0041173337958753109 
		0;
	setAttr -s 18 ".kox[3:17]"  0.03178158774971962 0.066259786486625671 
		0.066833212971687317 0.066187135875225067 0.067808918654918671 0.13333332538604736 
		0.065431572496891022 0.068446464836597443 0.068189926445484161 0.19999998807907104 
		0.20275254547595978 0.16666674613952637 0.11851823329925537 0.072996243834495544 
		0.066666722297668457;
	setAttr -s 18 ".koy[3:17]"  0.18394003808498383 0.33630165457725525 
		0.17812135815620422 0.013906072825193405 -0.055178236216306686 -0.24946250021457672 
		-0.1572624146938324 -0.075201503932476044 0.054504234343767166 0.20401296019554138 
		0.095733903348445892 0.075950473546981812 0.041059833019971848 0.0028265744913369417 
		0;
createNode animCurveTA -n "rat_FKBackA_M_rotateY1";
	setAttr ".tan" 1;
	setAttr -s 21 ".ktv[0:20]"  0 0.94704837463169422 2 0.83470875560974411 
		3 0.41060388427279487 4 -0.0043771476411465513 5 -0.28187729280099555 7 -0.55458826344395196 
		9 -0.54101367984816995 11 -0.15775239908986419 13 0.40428109670387857 15 0.62857025985843429 
		17 0.65736647608592502 19 0.57867069715542563 23 3.2829211438995589 26 0.42317720362236022 
		29 -5.7058815773089417 31 -4.155591894359925 35 4.3175654450593681 37 3.4634059094313825 
		40 -1.7280608289477153 42 -1.1847412436083946 45 0.94704837463169422;
	setAttr -s 21 ".kit[0:20]"  3 1 1 9 1 1 1 1 
		9 1 3 3 3 1 3 9 1 9 1 1 3;
	setAttr -s 21 ".kot[0:20]"  3 1 1 9 1 1 1 1 
		9 1 3 3 3 1 3 9 1 9 1 1 3;
	setAttr -s 21 ".kix[1:20]"  0.065027482807636261 0.03215431421995163 
		0.033333338797092438 0.032855138182640076 0.0674448162317276 0.06887286901473999 
		0.062891356647014618 0.066666662693023682 0.06769300252199173 0.066666662693023682 
		0.066666662693023682 0.13333332538604736 0.089201979339122772 0.099999964237213135 
		0.066666662693023682 0.1430380642414093 0.066666722297668457 0.10891308635473251 
		0.064977273344993591 0.10000002384185791;
	setAttr -s 21 ".kiy[1:20]"  -0.0083691384643316269 -0.007892620749771595 
		-0.006043038796633482 -0.0033874842338263988 -0.0018195238662883639 0.0026126441080123186 
		0.0087465168908238411 0.0068619595840573311 0.0015796020161360502 0 0 0 -0.084039725363254547 
		0 0.058314051479101181 0.035804323852062225 -0.042206447571516037 -0.014938648790121078 
		0.022616572678089142 0;
	setAttr -s 21 ".kox[1:20]"  0.031694419682025909 0.032154321670532227 
		0.033333331346511841 0.066188380122184753 0.067444831132888794 0.068872861564159393 
		0.062891356647014618 0.066666662693023682 0.067693009972572327 0.066666662693023682 
		0.13333332538604736 0.10000002384185791 0.0892019122838974 0.066666662693023682 0.13333332538604736 
		0.076368175446987152 0.10000002384185791 0.075578704476356506 0.098310507833957672 
		0.10000002384185791;
	setAttr -s 21 ".koy[1:20]"  -0.0040791216306388378 -0.0078926244750618935 
		-0.0060430373996496201 -0.0068242624402046204 -0.0018195242155343294 0.0026126434095203876 
		0.0087465159595012665 0.0068619595840573311 0.0015796020161360502 0 0 0 -0.084039650857448578 
		0 0.11662810295820236 0.019115956500172615 -0.063309632241725922 -0.010366464965045452 
		0.034218836575746536 0;
createNode animCurveTA -n "rat_FKBackA_M_rotateX1";
	setAttr ".tan" 1;
	setAttr -s 22 ".ktv[0:21]"  0 1.7544888543665405 2 1.8038223978008963 
		3 1.7248801095552411 4 1.2153573261455235 5 -0.066473880249820372 7 -4.7726898051311641 
		9 -4.9079407244102615 11 -3.0488354109877771 13 -1.9727184039949666 15 -1.3020828944783347 
		17 -0.0354388675438451 19 0.93577177102459663 21 1.3346679739278045 23 0.92849908890938715 
		26 -0.629214354235345 29 0.13834506151643469 32 4.1321808666723356 35 0.64154591141080619 
		38 -1.3892573453322132 40 -0.054529416217410386 43 2.4115114670861351 45 1.7544888543665405;
	setAttr -s 22 ".kit[0:21]"  3 3 1 1 9 1 1 1 
		1 9 1 1 3 1 9 9 3 1 3 1 3 3;
	setAttr -s 22 ".kot[0:21]"  3 3 1 1 9 1 1 1 
		1 9 1 1 3 1 9 9 3 1 3 1 3 3;
	setAttr -s 22 ".kix[2:21]"  0.032469462603330612 0.033857986330986023 
		0.033333331346511841 0.074993237853050232 0.066266559064388275 0.06506095826625824 
		0.068520583212375641 0.066666662693023682 0.066320061683654785 0.066397756338119507 
		0.066666662693023682 0.065399192273616791 0.10000002384185791 0.099999964237213135 
		0.10000008344650269 0.088863439857959747 0.10000002384185791 0.060862801969051361 
		0.099999904632568359 0.066666722297668457;
	setAttr -s 22 ".kiy[2:21]"  -0.0037025557830929756 -0.013056868687272072 
		-0.034837044775485992 -0.023479633033275604 0.016791069880127907 0.029620066285133362 
		0.010367175564169884 0.016905954107642174 0.019859271124005318 0.012406693771481514 
		0 -0.015169966965913773 -0.0068953968584537506 0.041550986468791962 0 -0.05251060426235199 
		0 0.027547650039196014 0 0;
	setAttr -s 22 ".kox[2:21]"  0.032469470053911209 0.033857978880405426 
		0.066666662693023682 0.074993252754211426 0.066266544163227081 0.065060965716838837 
		0.068520575761795044 0.066666662693023682 0.066320069134235382 0.066397756338119507 
		0.066666662693023682 0.098732411861419678 0.099999964237213135 0.10000008344650269 
		0.099999904632568359 0.088863544166088104 0.066666722297668457 0.094194844365119934 
		0.066666722297668457 0.066666722297668457;
	setAttr -s 22 ".koy[2:21]"  -0.0037025560159236193 -0.013056867755949497 
		-0.069674089550971985 -0.023479634895920753 0.016791064292192459 0.029620066285133362 
		0.010367174632847309 0.016905954107642174 0.019859276711940765 0.012406692840158939 
		0 -0.022901926189661026 -0.0068953926675021648 0.041551034897565842 0 -0.052510667592287064 
		0 0.042634371668100357 0 0;
createNode animCurveTU -n "rat_Center_M_CenterBtwFeet1";
	setAttr ".tan" 2;
	setAttr -s 19 ".ktv[0:18]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 43 0 45 0;
createNode animCurveTA -n "rat_Center_M_rotateZ1";
	setAttr ".tan" 1;
	setAttr -s 19 ".ktv[0:18]"  0 1.0973359671968677 2 1.0973359671968677 
		3 1.0930775412988094 4 1.0774674731814673 5 1.0118874135411711 7 0.39111457685933065 
		9 0.020766487623446791 11 0.010880794004037806 13 1.2252258853560927 15 2.0117875746396212 
		19 2.6801197173677527 23 2.8962696880349461 26 1.0539215242433801 29 -4.3133682747979334 
		32 -2.6689478974888412 35 3.6315669356759894 40 1.584887995383689 43 1.1357635474667449 
		45 1.0973359671968677;
	setAttr -s 19 ".kit[0:18]"  3 3 1 1 1 9 1 1 
		1 9 9 3 9 3 1 3 1 1 3;
	setAttr -s 19 ".kot[0:18]"  3 3 1 1 1 9 1 1 
		1 9 9 3 9 3 1 3 1 1 3;
	setAttr -s 19 ".kix[2:18]"  0.033807616680860519 0.034175928682088852 
		0.021291911602020264 0.066666662693023682 0.065690279006958008 0.065507441759109497 
		0.065835095942020416 0.066666662693023682 0.13333332538604736 0.13333332538604736 
		0.10000002384185791 0.099999964237213135 0.11371990293264389 0.099999904632568359 
		0.17596013844013214 0.10368496924638748 0.066666722297668457;
	setAttr -s 19 ".kiy[2:18]"  -0.00014782077050767839 -0.00050008733524009585 
		-0.0016599723603576422 -0.008649161085486412 -0.0026689963415265083 0.0029061497189104557 
		0.01893145963549614 0.0084642292931675911 0.0077185626141726971 0 -0.062915980815887451 
		0 0.068101026117801666 0 -0.02380051463842392 -0.0027238484472036362 0;
	setAttr -s 19 ".kox[2:18]"  0.033807616680860519 0.034175924956798553 
		0.054617878049612045 0.066666677594184875 0.065690264105796814 0.065507441759109497 
		0.065835095942020416 0.13333332538604736 0.13333332538604736 0.10000002384185791 
		0.099999964237213135 0.10000008344650269 0.11371970921754837 0.16666674613952637 
		0.10928987711668015 0.070351384580135345 0.066666722297668457;
	setAttr -s 19 ".koy[2:18]"  -0.00014782081416342407 -0.00050008716061711311 
		-0.0042581507004797459 -0.0086491629481315613 -0.002668995875865221 0.0029061497189104557 
		0.01893145777285099 0.016928458586335182 0.0077185626141726971 0 -0.062915943562984467 
		0 0.068100906908512115 0 -0.014782638289034367 -0.0018481607548892498 0;
createNode animCurveTA -n "rat_Center_M_rotateY1";
	setAttr ".tan" 1;
	setAttr -s 18 ".ktv[0:17]"  0 -0.010805299436553227 3 -0.087090400581147462 
		7 -0.79054249517200792 9 -2.0236406111327585 11 -4.0468659124969264 13 -4.5866984383833369 
		15 -4.2862683154163452 16 -3.6582151937065364 17 -2.7546062402793283 19 -1.1363082936398665 
		21 -0.15782010082508527 23 0.13267561949344653 26 -0.064715002019733819 29 -2.2536349721765463 
		33 -2.9778841917988363 36 -0.51624927435766355 41 -0.003130932097319811 45 -0.010805299436553227;
	setAttr -s 18 ".kit[0:17]"  3 1 9 1 9 9 1 9 
		1 9 1 1 1 1 1 1 3 3;
	setAttr -s 18 ".kot[0:17]"  3 1 9 1 9 9 1 9 
		1 9 1 1 1 1 1 1 3 3;
	setAttr -s 18 ".kix[1:17]"  0.098415426909923553 0.13333332538604736 
		0.066213376820087433 0.066666662693023682 0.066666662693023682 0.063544332981109619 
		0.033333361148834229 0.032927121967077255 0.066666662693023682 0.067005917429924011 
		0.065784044563770294 0.089410260319709778 0.096064433455467224 0.13133251667022705 
		0.094605952501296997 0.16666662693023682 0.13333332538604736;
	setAttr -s 18 ".kiy[1:17]"  -0.0031927058007568121 -0.022532781586050987 
		-0.03019627183675766 -0.022366898134350777 -0.002089180052280426 0.015224743634462357 
		0.013366284780204296 0.015403099358081818 0.022661233320832253 0.010521738789975643 
		0.00093094969633966684 -0.0085066957399249077 -0.026891807094216347 0.015480649657547474 
		0.015068293549120426 0 0;
	setAttr -s 18 ".kox[1:17]"  0.13174854218959808 0.066666677594184875 
		0.066213369369506836 0.066666662693023682 0.066666662693023682 0.030211595818400383 
		0.033333301544189453 0.06626041978597641 0.066666662693023682 0.067005909979343414 
		0.09911731630563736 0.089410208165645599 0.12939751148223877 0.097999297082424164 
		0.16127185523509979 0.13333332538604736 0.13333332538604736;
	setAttr -s 18 ".koy[1:17]"  -0.0042740693315863609 -0.011266393586993217 
		-0.030196260660886765 -0.022366898134350777 -0.002089180052280426 0.0072384700179100037 
		0.013366261497139931 0.030996203422546387 0.022661233320832253 0.010521737858653069 
		0.0014026688877493143 -0.0085066929459571838 -0.0362229123711586 0.011551539413630962 
		0.025686455890536308 0 0;
createNode animCurveTA -n "rat_Center_M_rotateX1";
	setAttr ".tan" 1;
	setAttr -s 22 ".ktv[0:21]"  0 -0.20351528028967278 2 -1.8661911945472858 
		3 -6.9021321143927405 4 -57.220446349227508 5 -55.186276505489758 7 -54.526953494275695 
		9 -58.97748902389803 11 -64.128433970379547 13 -64.811524590418045 15 -60.067688054071198 
		16 -50.942441150333117 17 -27.06123121222868 18 -9.6821072812504898 21 6.575976780244928 
		23 10.485639959641244 26 9.989095599959894 29 8.7638776980989199 32 7.1777381824244841 
		35 5.1420117926379323 40 1.7565660554777798 43 0.049786744495762404 45 -0.20351528028967278;
	setAttr -s 22 ".kit[0:21]"  3 1 1 3 9 1 1 1 
		1 1 1 1 1 1 3 1 1 1 1 1 1 3;
	setAttr -s 22 ".kot[0:21]"  3 1 1 3 9 1 1 1 
		1 1 1 1 1 1 3 1 1 1 1 1 1 3;
	setAttr -s 22 ".kix[1:21]"  0.067422397434711456 0.033138498663902283 
		0.033333338797092438 0.033333331346511841 0.066569477319717407 0.061094168573617935 
		0.065997347235679626 0.069528840482234955 0.058406282216310501 0.032969705760478973 
		0.033153671771287918 0.027741996571421623 0.10614320635795593 0.066666662693023682 
		0.10452517867088318 0.098978012800216675 0.096230342984199524 0.096082404255867004 
		0.16501788794994354 0.10161871463060379 0.066666722297668457;
	setAttr -s 22 ".kiy[1:21]"  -0.068955153226852417 -0.17319367825984955 
		0 0.015670105814933777 -0.013961861841380596 -0.10330923646688461 -0.023331101983785629 
		0.027229811996221542 0.12552985548973083 0.31642279028892517 0.37805730104446411 
		0.1308131068944931 0.16089561581611633 0 -0.018344895914196968 -0.019754806533455849 
		-0.029176060110330582 -0.038107618689537048 -0.061571564525365829 -0.013893510214984417 
		0;
	setAttr -s 22 ".kox[1:21]"  0.034088935703039169 0.03313850611448288 
		0.033333331346511841 0.066666662693023682 0.066569477319717407 0.061094153672456741 
		0.065997332334518433 0.069528840482234955 0.025074517354369164 0.032969649881124496 
		0.033153731375932693 0.094405360519886017 0.072809129953384399 0.10000002384185791 
		0.10452511161565781 0.098978139460086823 0.096230126917362213 0.16274872422218323 
		0.098351262509822845 0.068285346031188965 0.066666722297668457;
	setAttr -s 22 ".koy[1:21]"  -0.034863907843828201 -0.17319369316101074 
		0 0.031340211629867554 -0.013961863704025745 -0.10330922901630402 -0.023331096395850182 
		0.027229825034737587 0.05389147624373436 0.31642225384712219 0.37805801630020142 
		0.44515389204025269 0.11036664992570877 0 -0.018344871699810028 -0.019754830747842789 
		-0.029175996780395508 -0.064548410475254059 -0.036696881055831909 -0.0093361083418130875 
		0;
createNode animCurveTL -n "rat_Center_M_translateZ1";
	setAttr ".tan" 1;
	setAttr -s 23 ".ktv[0:22]"  0 -0.078873239085785252 2 -0.10317029840541565 
		3 -0.052454018224000032 4 0.61233830689838409 5 1.8902764518264439 7 2.3174178369892853 
		9 2.2949754697713081 11 1.858075655670123 13 1.0083163580435643 15 0.26580540612430653 
		16 0.052785874077718509 17 0.0085287796739630523 19 -0.14382835366571178 21 -0.06095242929950756 
		23 0.018417968963077236 26 -0.02081738243159989 29 -0.041840986093214461 32 -0.019478268134125315 
		35 -0.06626981487893277 38 -0.023349059025687527 40 -0.045278741876464246 43 -0.072972663299480447 
		45 -0.078873239085785252;
	setAttr -s 23 ".kit[0:22]"  3 3 1 1 1 1 1 1 
		9 9 1 1 1 1 3 1 3 3 3 3 1 1 3;
	setAttr -s 23 ".kot[0:22]"  3 3 1 1 1 1 1 1 
		9 9 1 1 1 1 3 1 3 3 3 3 1 1 3;
	setAttr -s 23 ".kix[2:22]"  0.033082060515880585 0.032468561083078384 
		0.032151173800230026 0.066069327294826508 0.068414397537708282 0.066111743450164795 
		0.066666662693023682 0.066666662693023682 0.034251295030117035 0.033674616366624832 
		0.066524848341941833 0.043735358864068985 0.066666662693023682 0.09833052009344101 
		0.099999964237213135 0.10000008344650269 0.099999904632568359 0.10000002384185791 
		0.06463313102722168 0.084035769104957581 0.066666722297668457;
	setAttr -s 23 ".kiy[2:22]"  0.13694851100444794 1.1849501132965088 
		0.463142991065979 0.09781239926815033 -0.1530841588973999 -0.69229269027709961 -0.79613512754440308 
		-0.63702011108398438 -0.087987698614597321 -0.058758709579706192 -0.017607785761356354 
		0.12569074332714081 0 -0.044442947953939438 0 0 0 0 -0.023607064038515091 -0.014177020639181137 
		0;
	setAttr -s 23 ".kox[2:22]"  0.033082067966461182 0.032468553632497787 
		0.064302362501621246 0.066069349646568298 0.068414390087127686 0.066111743450164795 
		0.066666662693023682 0.033333361148834229 0.034251239150762558 0.067349299788475037 
		0.066524840891361237 0.043735355138778687 0.10000002384185791 0.098330460488796234 
		0.10000008344650269 0.099999904632568359 0.10000002384185791 0.066666722297668457 
		0.096949532628059387 0.056023955345153809 0.066666722297668457;
	setAttr -s 23 ".koy[2:22]"  0.13694854080677032 1.1849499940872192 
		0.92628616094589233 0.09781242161989212 -0.15308414399623871 -0.69229269027709961 
		-0.79613512754440308 -0.31851035356521606 -0.087987527251243591 -0.11751753836870193 
		-0.017607783898711205 0.12569071352481842 0 -0.044442921876907349 0 0 0 0 -0.035410530865192413 
		-0.0094513660296797752 0;
createNode animCurveTL -n "rat_Center_M_translateY1";
	setAttr ".tan" 1;
	setAttr -s 22 ".ktv[0:21]"  0 0.26682379778056281 2 0.36812442132160555 
		3 0.20767937836558015 4 -0.11504570389057286 5 -0.40376674979396554 7 -0.5990467364098031 
		9 -0.65108498547163163 11 -0.72811879916340216 13 -0.90487541376171221 15 -1.0851850340782527 
		17 -1.2836956581428338 19 -1.3617930138883672 21 -1.2986435435605685 23 -1.0537765105740975 
		26 -0.79764164812352167 29 -0.58345497295587945 32 -0.31731549269106563 35 -0.1174325796134327 
		38 0.091090781024867479 40 0.19854380070373367 43 0.25942412228312217 45 0.26682379778056281;
	setAttr -s 22 ".kit[0:21]"  3 3 1 1 1 1 1 9 
		9 1 1 3 9 1 1 1 1 1 1 1 1 3;
	setAttr -s 22 ".kot[0:21]"  3 3 1 1 1 1 1 9 
		9 1 1 3 9 1 1 1 1 1 1 1 1 3;
	setAttr -s 22 ".kix[2:21]"  0.032584544271230698 0.032770369201898575 
		0.032917402684688568 0.068748109042644501 0.068669304251670837 0.066666662693023682 
		0.066666662693023682 0.06601705402135849 0.065487153828144073 0.066666662693023682 
		0.066666662693023682 0.065670832991600037 0.10079068690538406 0.10034897178411484 
		0.10171268135309219 0.10025941580533981 0.099891066551208496 0.066737167537212372 
		0.10332347452640533 0.066666722297668457;
	setAttr -s 22 ".kiy[2:21]"  -0.28822451829910278 -0.35114499926567078 
		-0.17938962578773499 -0.077774845063686371 -0.041764352470636368 -0.12689521908760071 
		-0.17853312194347382 -0.20617279410362244 -0.15975584089756012 0 0.15400825440883636 
		0.22695890069007874 0.19585046172142029 0.23585525155067444 0.2132880836725235 0.19908146560192108 
		0.20771069824695587 0.065708339214324951 0.024441935122013092 0;
	setAttr -s 22 ".kox[2:21]"  0.032584555447101593 0.032770361751317978 
		0.06583482027053833 0.068748123943805695 0.068669289350509644 0.066666662693023682 
		0.066666662693023682 0.066017061471939087 0.06548716127872467 0.066666662693023682 
		0.066666662693023682 0.098506271839141846 0.10079061985015869 0.10034909099340439 
		0.10171250253915787 0.10025954246520996 0.066594086587429047 0.10010557621717453 
		0.06888243556022644 0.066666722297668457;
	setAttr -s 22 ".koy[2:21]"  -0.28822463750839233 -0.351144939661026 
		-0.35877931118011475 -0.077774859964847565 -0.041764352470636368 -0.12689521908760071 
		-0.17853312194347382 -0.20617282390594482 -0.15975585579872131 0 0.15400825440883636 
		0.34043842554092407 0.19585035741329193 0.23585553467273712 0.21328777074813843 0.19908171892166138 
		0.13847388327121735 0.098562337458133698 0.016294652596116066 0;
createNode animCurveTL -n "rat_Center_M_translateX1";
	setAttr ".tan" 1;
	setAttr -s 18 ".ktv[0:17]"  0 -0.034824194676283823 2 -0.048647181024443771 
		3 -0.048647181024443771 4 -0.034824194676283823 5 0.0046514531307749463 7 0.01935432756855944 
		9 0.023836895632480766 11 0.022986062315134462 13 0.013180378499381883 15 0.0099393211744330835 
		19 -0.00012291423624350047 23 -0.0044094191020726016 26 0.034499232025379141 32 -0.033455073200980179 
		38 0.026254945078966592 40 -0.0013880962559671499 43 -0.030372474383996685 45 -0.034824194676283823;
	setAttr -s 18 ".kit[0:17]"  3 1 1 9 1 1 1 1 
		1 1 1 1 3 3 3 1 1 3;
	setAttr -s 18 ".kot[0:17]"  3 1 1 9 1 1 1 1 
		1 1 1 1 3 3 3 1 1 3;
	setAttr -s 18 ".kix[1:17]"  0.064478233456611633 0.035028636455535889 
		0.033333338797092438 0.034047476947307587 0.068414747714996338 0.065900497138500214 
		0.072930946946144104 0.075917802751064301 0.067726008594036102 0.1320047527551651 
		0.13061678409576416 0.10000002384185791 0.20000004768371582 0.19999992847442627 0.065830402076244354 
		0.10000328719615936 0.066666722297668457;
	setAttr -s 18 ".kiy[1:17]"  -0.0084344996139407158 0.0043636737391352654 
		0.026649320498108864 0.0138392373919487 0.0067397044040262699 0.0012619346380233765 
		-0.0038314380217343569 -0.0046769203618168831 -0.003360705217346549 -0.0093405600637197495 
		0.0064925705082714558 0 0 0 -0.024482812732458115 -0.018861845135688782 0;
	setAttr -s 18 ".kox[1:17]"  0.032239120453596115 0.035028643906116486 
		0.033333331346511841 0.06809496134519577 0.068414755165576935 0.065900467336177826 
		0.072930954396724701 0.075917802751064301 0.13545206189155579 0.1320047527551651 
		0.097962625324726105 0.20000004768371582 0.19999992847442627 0.066666722297668457 
		0.098745405673980713 0.066668979823589325 0.066666722297668457;
	setAttr -s 18 ".koy[1:17]"  -0.0042172502726316452 0.00436367467045784 
		0.026649314910173416 0.027678476646542549 0.0067397048696875572 0.0012619346380233765 
		-0.0038314384873956442 -0.0046769203618168831 -0.0067214127629995346 -0.0093405609950423241 
		0.004869428463280201 0 0 0 -0.036724139004945755 -0.012574585154652596 0;
createNode animCurveTU -n "rat_FKRump_L_scaleZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 1.0000000000000002 2 1.0000000000000002 
		3 1.0000000000000002 4 1.0000000000000002 5 1.0000000000000002 7 1.0000000000000002 
		9 1.0000000000000002 11 1.0000000000000002 13 1.0000000000000002 15 1.0000000000000002 
		16 1.0000000000000002 17 1.0000000000000002 19 1.0000000000000002 23 1.0000000000000002 
		29 1.0000000000000002 35 1.0000000000000002 40 1.0000000000000002 45 1.0000000000000002;
createNode animCurveTU -n "rat_FKRump_L_scaleY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0.99999999999999989 2 0.99999999999999989 
		3 0.99999999999999989 4 0.99999999999999989 5 0.99999999999999989 7 0.99999999999999989 
		9 0.99999999999999989 11 0.99999999999999989 13 0.99999999999999989 15 0.99999999999999989 
		16 0.99999999999999989 17 0.99999999999999989 19 0.99999999999999989 23 0.99999999999999989 
		29 0.99999999999999989 35 0.99999999999999989 40 0.99999999999999989 45 0.99999999999999989;
createNode animCurveTU -n "rat_FKRump_L_scaleX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 1 2 1 3 1 4 1 5 1 7 1 9 1 11 1 13 1 15 
		1 16 1 17 1 19 1 23 1 29 1 35 1 40 1 45 1;
createNode animCurveTA -n "rat_FKRump_L_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_FKRump_L_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_FKRump_L_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTL -n "rat_FKRump_L_translateZ1";
	setAttr ".tan" 1;
	setAttr -s 18 ".ktv[0:17]"  0 -0.0078247081510850677 2 -0.0078247081510850677 
		3 -0.017795719106728999 4 -0.026045692090018994 5 -0.0048617906241890975 7 0.013064541106074055 
		9 0.021939737753354338 11 0.039650374801460692 13 0.045930993272647595 15 0.053466342317563309 
		17 0.056762672003128643 19 0.056813033438266623 21 0.052424924311208432 23 0.041075834748831482 
		29 0.01307938056495098 35 -0.0039299910652651551 40 -0.0075419524659566658 45 -0.0078247081510850677;
	setAttr -s 18 ".kit[0:17]"  3 3 1 3 1 1 9 1 
		1 9 1 9 1 1 9 9 1 3;
	setAttr -s 18 ".kot[0:17]"  3 3 1 3 1 1 9 1 
		1 9 1 9 1 1 9 9 1 3;
	setAttr -s 18 ".kix[2:17]"  0.031473863869905472 0.033333338797092438 
		0.032806959003210068 0.068660713732242584 0.066666677594184875 0.067974060773849487 
		0.065541915595531464 0.066666662693023682 0.067374244332313538 0.066666662693023682 
		0.075171492993831635 0.066061981022357941 0.19999998807907104 0.19999998807907104 
		0.17331224679946899 0.16666662693023682;
	setAttr -s 18 ".kiy[2:17]"  -0.013794924132525921 0 0.01485631987452507 
		0.0086983470246195793 0.013292917981743813 0.0087239658460021019 0.0079332990571856499 
		0.0054158391430974007 0.0011121617862954736 -0.0021688737906515598 -0.0094768553972244263 
		-0.010649257339537144 -0.02250291220843792 -0.011247997172176838 -0.00092329701874405146 
		0;
	setAttr -s 18 ".kox[2:17]"  0.031473871320486069 0.033333331346511841 
		0.065613925457000732 0.068660736083984375 0.066666662693023682 0.067974060773849487 
		0.065541915595531464 0.066666662693023682 0.067374244332313538 0.066666662693023682 
		0.075171500444412231 0.19818596541881561 0.19999998807907104 0.16666674613952637 
		0.17331211268901825 0.16666662693023682;
	setAttr -s 18 ".koy[2:17]"  -0.013794927857816219 0 0.029712645336985588 
		0.0086983516812324524 0.013292915187776089 0.0087239649146795273 0.0079332990571856499 
		0.0054158391430974007 0.0011121619027107954 -0.0021688737906515598 -0.0094768544659018517 
		-0.031947772949934006 -0.02250291220843792 -0.009373336099088192 -0.00092329649487510324 
		0;
createNode animCurveTL -n "rat_FKRump_L_translateY1";
	setAttr ".tan" 1;
	setAttr -s 19 ".ktv[0:18]"  0 0.06041488693119227 2 0.06041488693119227 
		3 0.06041488693119227 4 0.022652185434174212 5 -0.071490942060334836 7 -0.045223584461422002 
		9 -0.0070915779890309352 11 -0.017342054416209084 13 -0.22289687438530373 15 -0.133332261668267 
		16 -0.061767488402118695 17 0.0061413935442242856 19 0.092661077011131604 21 0.048377614096788139 
		23 0.011693019529758149 29 0.0016814473850808006 35 0.0016814473850808006 40 0.030301819721036554 
		45 0.06041488693119227;
	setAttr -s 19 ".kit[0:18]"  9 3 3 1 3 1 1 1 
		3 1 9 1 3 1 1 3 3 9 3;
	setAttr -s 19 ".kot[0:18]"  9 3 3 1 3 1 1 1 
		3 1 9 1 3 1 1 3 3 9 3;
	setAttr -s 19 ".kix[3:18]"  0.032113213092088699 0.033333331346511841 
		0.06343378871679306 0.066003769636154175 0.058378648012876511 0.066666662693023682 
		0.064301237463951111 0.033333361148834229 0.032729063183069229 0.066666662693023682 
		0.063419759273529053 0.094555169343948364 0.19999998807907104 0.19999998807907104 
		0.16666674613952637 0.16666662693023682;
	setAttr -s 19 ".kiy[3:18]"  -0.085610747337341309 0 0.044406931847333908 
		0.019661290571093559 -0.047592826187610626 0 0.13396130502223969 0.069736890494823456 
		0.059641357511281967 0 -0.055888094007968903 -0.0099872099235653877 0 0 0.029366729781031609 
		0;
	setAttr -s 19 ".kox[3:18]"  0.032113209366798401 0.066666662693023682 
		0.063433803617954254 0.066003739833831787 0.058378662914037704 0.066666662693023682 
		0.032150648534297943 0.033333301544189453 0.065458178520202637 0.066666662693023682 
		0.063419759273529053 0.28366529941558838 0.19999998807907104 0.16666674613952637 
		0.16666662693023682 0.16666662693023682;
	setAttr -s 19 ".koy[3:18]"  -0.085610739886760712 0 0.044406954199075699 
		0.019661283120512962 -0.047592833638191223 0 0.066980727016925812 0.069736763834953308 
		0.1192827969789505 0 -0.055888090282678604 -0.029961608350276947 0 0 0.029366709291934967 
		0;
createNode animCurveTL -n "rat_FKRump_L_translateX1";
	setAttr ".tan" 1;
	setAttr -s 18 ".ktv[0:17]"  0 0.045916714597033288 2 0.045916714597033288 
		3 0.029006937440774601 4 -0.043374583139982062 5 -0.030842140083647423 7 0.02002796086900558 
		9 0.040268898651478313 11 0.033204254419397443 13 -0.16030359175274503 15 -0.031347790734949449 
		17 0.034296441372461739 19 0.053886918893198396 21 0.05429801551555255 23 0.036632188393488647 
		29 0.0091639669087335632 35 0.0091639669087335632 40 0.022742397249468506 45 0.045916714597033288;
	setAttr -s 18 ".kit[0:17]"  3 3 9 3 1 9 1 1 
		3 1 1 1 1 1 1 1 1 3;
	setAttr -s 18 ".kot[0:17]"  3 3 9 3 1 9 1 1 
		3 1 1 1 1 1 1 1 1 3;
	setAttr -s 18 ".kix[4:17]"  0.032807309180498123 0.066666662693023682 
		0.066380314528942108 0.062273669987916946 0.066666662693023682 0.066121235489845276 
		0.067399613559246063 0.065643511712551117 0.06607113778591156 0.062863312661647797 
		0.19767026603221893 0.19767026603221893 0.15011437237262726 0.16666662693023682;
	setAttr -s 18 ".kiy[4:17]"  0.024082096293568611 0.035555515438318253 
		0.0066600670106709003 -0.025682415813207626 0 0.10458337515592575 0.037861756980419159 
		0.006175696849822998 -0.0047191441990435123 -0.016312902793288231 -0.0045549618080258369 
		0.0045549613423645496 0.024648258462548256 0;
	setAttr -s 18 ".kox[4:17]"  0.06561463326215744 0.066666677594184875 
		0.066380307078361511 0.062273681163787842 0.066666662693023682 0.066121235489845276 
		0.067399613559246063 0.065643511712551117 0.066071130335330963 0.18859004974365234 
		0.19767026603221893 0.16472530364990234 0.1501142680644989 0.16666662693023682;
	setAttr -s 18 ".koy[4:17]"  0.048164203763008118 0.035555522888898849 
		0.0066600660793483257 -0.025682417675852776 0 0.10458336770534515 0.037861749529838562 
		0.0061756954528391361 -0.0047191441990435123 -0.048938725143671036 -0.0045549613423645496 
		0.0037958037573844194 0.024648245424032211 0;
createNode animCurveTU -n "rat_FKRump_R_scaleZ1";
	setAttr ".tan" 2;
	setAttr -s 19 ".ktv[0:18]"  0 1.0000000000000002 2 1.0000000000000002 
		3 1.0000000000000002 4 1.0000000000000002 5 1.0000000000000002 7 1.0000000000000002 
		9 1.0000000000000002 11 1.0000000000000002 13 1.0000000000000002 15 1.0000000000000002 
		16 1.0000000000000002 17 1.0000000000000002 19 1.0000000000000002 23 1.0000000000000002 
		25 1.0000000000000002 29 1.0000000000000002 35 1.0000000000000002 40 1.0000000000000002 
		45 1.0000000000000002;
createNode animCurveTU -n "rat_FKRump_R_scaleY1";
	setAttr ".tan" 2;
	setAttr -s 19 ".ktv[0:18]"  0 1.0000000000000002 2 1.0000000000000002 
		3 1.0000000000000002 4 1.0000000000000002 5 1.0000000000000002 7 1.0000000000000002 
		9 1.0000000000000002 11 1.0000000000000002 13 1.0000000000000002 15 1.0000000000000002 
		16 1.0000000000000002 17 1.0000000000000002 19 1.0000000000000002 23 1.0000000000000002 
		25 1.0000000000000002 29 1.0000000000000002 35 1.0000000000000002 40 1.0000000000000002 
		45 1.0000000000000002;
createNode animCurveTU -n "rat_FKRump_R_scaleX1";
	setAttr ".tan" 2;
	setAttr -s 19 ".ktv[0:18]"  0 1.0000000000000002 2 1.0000000000000002 
		3 1.0000000000000002 4 1.0000000000000002 5 1.0000000000000002 7 1.0000000000000002 
		9 1.0000000000000002 11 1.0000000000000002 13 1.0000000000000002 15 1.0000000000000002 
		16 1.0000000000000002 17 1.0000000000000002 19 1.0000000000000002 23 1.0000000000000002 
		25 1.0000000000000002 29 1.0000000000000002 35 1.0000000000000002 40 1.0000000000000002 
		45 1.0000000000000002;
createNode animCurveTA -n "rat_FKRump_R_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 19 ".ktv[0:18]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 25 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_FKRump_R_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 19 ".ktv[0:18]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 25 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_FKRump_R_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 19 ".ktv[0:18]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 25 0 29 0 35 0 40 0 45 0;
createNode animCurveTL -n "rat_FKRump_R_translateZ1";
	setAttr ".tan" 1;
	setAttr -s 21 ".ktv[0:20]"  0 0.0016820758713359874 2 0.0016820758713359874 
		3 0.0016820758713359874 4 2.599391102387619e-005 5 -0.019212174946063934 7 -0.054420542646534287 
		9 -0.068522289379060936 11 -0.074205245693659036 13 -0.074020911287605962 15 -0.065728664446995003 
		16 -0.05883343263870526 17 -0.057714409057556301 19 -0.06540054531169015 21 -0.086461366957675007 
		23 -0.10135821895567884 25 -0.10302798754403317 27 -0.095164235627226007 29 -0.045442286958650824 
		35 -0.012501268789582624 40 -0.0007683842115229593 45 0.0016820758713359874;
	setAttr -s 21 ".kit[0:20]"  9 9 3 1 1 1 1 1 
		1 1 9 1 9 9 1 3 1 1 1 9 3;
	setAttr -s 21 ".kot[0:20]"  9 9 3 1 1 1 1 1 
		1 1 9 1 9 9 1 3 1 1 1 9 3;
	setAttr -s 21 ".kix[3:20]"  0.031985718756914139 0.0323808453977108 
		0.067933157086372375 0.067252218723297119 0.068326510488986969 0.070644602179527283 
		0.057190947234630585 0.033333361148834229 0.03241405263543129 0.066666662693023682 
		0.066666662693023682 0.062151536345481873 0.066666662693023682 0.022855775430798531 
		0.067702688276767731 0.20408341288566589 0.16666674613952637 0.16666662693023682;
	setAttr -s 21 ".kiy[3:20]"  -0.0039485711604356766 -0.022499373182654381 
		-0.019638175144791603 -0.0090223643928766251 -0.0013493305305019021 0.0019938200712203979 
		0.011513924226164818 0.0040071313269436359 -0.0012440809514373541 -0.014373479411005974 
		-0.017978837713599205 -0.0038593730423599482 0 0.010021877475082874 0.016582347452640533 
		0.018327588215470314 0.0070916749536991119 0;
	setAttr -s 21 ".kox[3:20]"  0.031985711306333542 0.064761705696582794 
		0.067933171987533569 0.067252203822135925 0.068326510488986969 0.070644617080688477 
		0.028595495969057083 0.033333301544189453 0.064828157424926758 0.066666662693023682 
		0.066666662693023682 0.062151532620191574 0.066666662693023682 0.022855773568153381 
		0.20310814678668976 0.17006959021091461 0.16666662693023682 0.16666662693023682;
	setAttr -s 21 ".koy[3:20]"  -0.003948570229113102 -0.044998757541179657 
		-0.019638178870081902 -0.0090223625302314758 -0.0013493306469172239 0.001993819372728467 
		0.0057569672353565693 0.0040071243420243263 -0.0024881642311811447 -0.014373479411005974 
		-0.017978837713599205 -0.0038593728095293045 0 0.010021877475082874 0.049747060984373093 
		0.015272999182343483 0.0070916698314249516 0;
createNode animCurveTL -n "rat_FKRump_R_translateY1";
	setAttr ".tan" 1;
	setAttr -s 21 ".ktv[0:20]"  0 -0.00036695532294986821 2 -0.00036695532294986821 
		3 -0.00036695532294986821 4 0.048989025760847939 5 0.15048260386554188 7 0.13301300801184593 
		9 0.024084251516973985 11 -0.040667926574114756 13 0.27607723789973254 15 0.21291245900050548 
		16 0.13566213170148386 17 0.059501216494622408 19 -0.016943550063767195 21 -0.004435834919789803 
		23 0.0017943591558692105 25 -0.0048874266749686941 27 -0.067418842473669555 29 -0.015067007080274636 
		35 0.0059797739731366432 40 0.0011641054666501694 45 -0.00036695532294986821;
	setAttr -s 21 ".kit[0:20]"  9 3 3 1 1 9 1 3 
		3 1 9 1 3 1 3 1 3 1 3 1 3;
	setAttr -s 21 ".kot[0:20]"  9 3 3 1 1 9 1 3 
		3 1 9 1 3 1 3 1 3 1 3 1 3;
	setAttr -s 21 ".kix[3:20]"  0.032701253890991211 0.033001650124788284 
		0.066666662693023682 0.065174654126167297 0.066666662693023682 0.066666662693023682 
		0.06561463326215744 0.033333361148834229 0.032314911484718323 0.066666662693023682 
		0.064022734761238098 0.066666662693023682 0.065889321267604828 0.066666662693023682 
		0.066120214760303497 0.19999998807907104 0.16621223092079163 0.16666662693023682;
	setAttr -s 21 ".kiy[3:20]"  0.087895959615707397 0.017401132732629776 
		-0.063199169933795929 -0.11156605184078217 0 0 -0.097722321748733521 -0.076705686748027802 
		-0.063808418810367584 0 0.012383130379021168 0 -0.016267690807580948 0 0.019725628197193146 
		0 -0.003254683455452323 0;
	setAttr -s 21 ".kox[3:20]"  0.032701246440410614 0.066003300249576569 
		0.066666677594184875 0.065174631774425507 0.066666662693023682 0.066666662693023682 
		0.032807342708110809 0.033333301544189453 0.064629890024662018 0.066666662693023682 
		0.064022727310657501 0.066666662693023682 0.065889328718185425 0.066666662693023682 
		0.19836069643497467 0.16666674613952637 0.16621211171150208 0.16666662693023682;
	setAttr -s 21 ".koy[3:20]"  0.087895952165126801 0.034802261739969254 
		-0.063199184834957123 -0.11156601458787918 0 0 -0.048861194401979446 -0.076705552637577057 
		-0.12761694192886353 0 0.012383128516376019 0 -0.016267688944935799 0 0.059176906943321228 
		0 -0.0032546815928071737 0;
createNode animCurveTL -n "rat_FKRump_R_translateX1";
	setAttr ".tan" 1;
	setAttr -s 21 ".ktv[0:20]"  0 -0.066560894777387858 2 -0.066560894777387858 
		3 -0.066560894777387858 4 0.025029303769686151 5 -0.046970284341162336 7 -0.20070185780777283 
		9 -0.27554212993161048 11 -0.29694344290590086 13 -0.0030165172890890268 15 0.017798650032817456 
		16 -0.10328381917066171 17 -0.18761648107723156 19 -0.24581848030493061 21 -0.2370671565347453 
		23 -0.17293715704213328 25 -0.16878257972340965 27 -0.22239024730248019 29 -0.16047342508596241 
		35 -0.090584402080633092 40 -0.069853521806911748 45 -0.066560894777387858;
	setAttr -s 21 ".kit[0:20]"  9 3 3 3 1 1 1 3 
		1 1 9 9 1 1 9 9 3 9 1 1 3;
	setAttr -s 21 ".kot[0:20]"  9 3 3 3 1 1 1 3 
		1 1 9 9 1 1 9 9 3 9 1 1 3;
	setAttr -s 21 ".kix[4:20]"  0.032046996057033539 0.066796585917472839 
		0.066111594438552856 0.066666662693023682 0.063184037804603577 0.065878070890903473 
		0.033333361148834229 0.033333301544189453 0.066365018486976624 0.066199496388435364 
		0.066666662693023682 0.066666662693023682 0.066666662693023682 0.066666662693023682 
		0.20711077749729156 0.1715676486492157 0.16666662693023682;
	setAttr -s 21 ".kiy[4:20]"  -0.098721377551555634 -0.10780852288007736 
		-0.043679755181074142 0 0.10819695144891739 -0.052017491310834885 -0.10270765423774719 
		-0.047511525452136993 -0.032230813056230545 0.054173272103071213 0.034142289310693741 
		-0.024726545438170433 0 0.032951463013887405 0.04820583388209343 0.007200716994702816 
		0;
	setAttr -s 21 ".kox[4:20]"  0.064093992114067078 0.066796600818634033 
		0.066111601889133453 0.066666662693023682 0.063184015452861786 0.032939072698354721 
		0.033333301544189453 0.066666662693023682 0.066365018486976624 0.066199488937854767 
		0.066666662693023682 0.066666662693023682 0.066666662693023682 0.19999998807907104 
		0.17259243130683899 0.17156751453876495 0.16666662693023682;
	setAttr -s 21 ".koy[4:20]"  -0.19744277000427246 -0.10780853778123856 
		-0.043679766356945038 0 0.1081969141960144 -0.02600877545773983 -0.10270747542381287 
		-0.095023132860660553 -0.032230816781520844 0.054173246026039124 0.034142289310693741 
		-0.024726545438170433 0 0.098854385316371918 0.040171552449464798 0.0072007104754447937 
		0;
createNode animCurveTU -n "rat_FKScapula_L_scaleZ1";
	setAttr ".tan" 2;
	setAttr -s 14 ".ktv[0:13]"  0 0.99999999999999967 2 0.99999999999999967 
		3 0.99999999999999967 4 0.99999999999999967 5 0.99999999999999967 14 0.99999999999999967 
		16 0.99999999999999967 17 0.99999999999999967 19 0.99999999999999967 23 0.99999999999999967 
		29 0.99999999999999967 35 0.99999999999999967 40 0.99999999999999967 45 0.99999999999999967;
createNode animCurveTU -n "rat_FKScapula_L_scaleY1";
	setAttr ".tan" 2;
	setAttr -s 14 ".ktv[0:13]"  0 0.99999999999999989 2 0.99999999999999989 
		3 0.99999999999999989 4 0.99999999999999989 5 0.99999999999999989 14 0.99999999999999989 
		16 0.99999999999999989 17 0.99999999999999989 19 0.99999999999999989 23 0.99999999999999989 
		29 0.99999999999999989 35 0.99999999999999989 40 0.99999999999999989 45 0.99999999999999989;
createNode animCurveTU -n "rat_FKScapula_L_scaleX1";
	setAttr ".tan" 2;
	setAttr -s 14 ".ktv[0:13]"  0 0.99999999999999956 2 0.99999999999999956 
		3 0.99999999999999956 4 0.99999999999999956 5 0.99999999999999956 14 0.99999999999999956 
		16 0.99999999999999956 17 0.99999999999999956 19 0.99999999999999956 23 0.99999999999999956 
		29 0.99999999999999956 35 0.99999999999999956 40 0.99999999999999956 45 0.99999999999999956;
createNode animCurveTA -n "rat_FKScapula_L_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 14 ".ktv[0:13]"  0 -2.4790172850168215 2 -2.4790172850168215 
		3 -2.33085249423161 4 -37.441547020768851 5 -22.147199842291414 14 -21.541913409769375 
		16 -56.436719827767732 17 -33.412125975525782 19 -2.4790172850168215 23 -2.4790172850168215 
		29 -2.4790172850168215 35 -2.4790172850168215 40 -2.4790172850168215 45 -2.4790172850168215;
createNode animCurveTA -n "rat_FKScapula_L_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 14 ".ktv[0:13]"  0 0 2 0 3 -19.903644720219873 4 -26.757902378394999 
		5 -21.548727024745848 14 -22.513720816934377 16 -22.72816396707718 17 0 19 0 23 0 
		29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_FKScapula_L_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 14 ".ktv[0:13]"  0 0 2 0 3 -0.84442095567177922 4 -19.017807245700439 
		5 -14.486560725543789 14 -3.4179850290316263 16 -0.95830056352739712 17 0 19 0 23 
		0 29 0 35 0 40 0 45 0;
createNode animCurveTL -n "rat_FKScapula_L_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 19 ".ktv[0:18]"  0 -0.014617768625972012 2 -0.014617768625972012 
		3 -0.044447127389627368 4 -0.026318810018810968 5 -0.078601024967925218 7 -0.005874448684515996 
		11 0.041854370029492355 14 0.00097586722863445224 16 -0.020460140544378422 17 -0.084593892118287509 
		18 -0.056905277913375421 19 -0.033723445370299657 23 -0.026665784240702782 26 0.051672921985961268 
		29 -0.018522329091167938 32 0.021006148434008064 35 0.010464319283773544 40 -0.015264947031353986 
		45 -0.014617768625972012;
createNode animCurveTL -n "rat_FKScapula_L_translateY1";
	setAttr ".tan" 2;
	setAttr -s 19 ".ktv[0:18]"  0 0.048890236498641375 2 0.048890236498641375 
		3 0.05260427744148663 4 0.0060425142140090402 5 0.019494822935181469 7 -0.026622347254927473 
		11 -0.082114899008257941 14 -0.11171828404375576 16 -0.051398210427251151 17 -0.15174824855903368 
		18 -0.20074809297575782 19 -0.17173861400411167 23 -0.17173861400411167 26 -0.11943623065171931 
		29 -0.12321794213331948 32 -0.048539767395623996 35 0.0092313260776463405 40 0.030169988296926811 
		45 0.048890236498641375;
createNode animCurveTL -n "rat_FKScapula_L_translateX1";
	setAttr ".tan" 2;
	setAttr -s 19 ".ktv[0:18]"  0 0.015444448179427845 2 0.015444448179427845 
		3 0.024948471413495821 4 0.054255047073166487 5 0.059955119411078416 7 0.039701535739421631 
		11 0.022306333189632259 14 -0.020826049017583628 16 -0.055839895659219881 17 0.025401001820014143 
		18 0.018942998302772154 19 0.018193008881353417 23 0.01550279116216078 26 0.0030668228696692106 
		29 0.01550279116216078 32 0.0085062133073922595 35 0.012805468676090562 40 0.01550279116216078 
		45 0.015444448179427845;
createNode animCurveTU -n "rat_FKScapula_R_scaleZ1";
	setAttr ".tan" 2;
	setAttr -s 13 ".ktv[0:12]"  0 0.99999999999999933 2 0.99999999999999933 
		3 0.99999999999999933 4 0.99999999999999933 5 0.99999999999999933 16 0.99999999999999933 
		17 0.99999999999999933 19 0.99999999999999933 23 0.99999999999999933 29 0.99999999999999933 
		35 0.99999999999999933 40 0.99999999999999933 45 0.99999999999999933;
createNode animCurveTU -n "rat_FKScapula_R_scaleY1";
	setAttr ".tan" 2;
	setAttr -s 13 ".ktv[0:12]"  0 0.99999999999999933 2 0.99999999999999933 
		3 0.99999999999999933 4 0.99999999999999933 5 0.99999999999999933 16 0.99999999999999933 
		17 0.99999999999999933 19 0.99999999999999933 23 0.99999999999999933 29 0.99999999999999933 
		35 0.99999999999999933 40 0.99999999999999933 45 0.99999999999999933;
createNode animCurveTU -n "rat_FKScapula_R_scaleX1";
	setAttr ".tan" 2;
	setAttr -s 13 ".ktv[0:12]"  0 0.99999999999999956 2 0.99999999999999956 
		3 0.99999999999999956 4 0.99999999999999956 5 0.99999999999999956 16 0.99999999999999956 
		17 0.99999999999999956 19 0.99999999999999956 23 0.99999999999999956 29 0.99999999999999956 
		35 0.99999999999999956 40 0.99999999999999956 45 0.99999999999999956;
createNode animCurveTA -n "rat_FKScapula_R_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 14 ".ktv[0:13]"  0 2.932404808116428 2 2.932404808116428 
		3 2.7572218424211425 4 -27.852700260152005 5 -24.726579660705678 14 -10.381283535337586 
		16 -33.670015708598093 17 -62.268648627583737 19 2.932404808116428 23 2.932404808116428 
		29 2.932404808116428 35 2.932404808116428 40 2.932404808116428 45 2.932404808116428;
createNode animCurveTA -n "rat_FKScapula_R_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 3 -19.896786965356391 4 -29.881143392478613 
		5 -17.681198418649252 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_FKScapula_R_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 3 0.99874711512021563 4 -7.9406523337198056 
		5 -8.9359270709553513 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTL -n "rat_FKScapula_R_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0.018070021209980833 2 0.018070021209980833 
		3 0.093784080176392337 4 0.037338941875032033 5 0.13168332137837399 7 0.066929339558248105 
		11 0.034991558146546919 14 0.084405727043532955 16 0.11533010002728288 17 0.09775435673289018 
		18 0.1078657147973536 19 0.12165446458837958 23 0.056078879217073496 27 0.045941107251130986 
		29 0.059647261533964019 35 0.025979923233428071 40 0.019805778416270042 45 0.018070021209980833;
createNode animCurveTL -n "rat_FKScapula_R_translateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 -0.029511160393227057 2 -0.029511160393227057 
		3 -0.056479754719149622 4 -0.040772268012696539 5 -0.015346910119111393 7 0.018190791976117983 
		11 0.047898299330204883 14 0.062929807616553368 16 0.054959115501567735 17 0.079991123668954556 
		18 0.14206327925777451 19 -0.0031752226469326998 23 0.033807167394818732 27 -0.047952428998845324 
		29 -0.076213107554722187 35 -0.01447605961905048 40 -0.023922777947850957 45 -0.029511160393227057;
createNode animCurveTL -n "rat_FKScapula_R_translateX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0.00050263996420009459 2 0.00050263996420009459 
		3 -0.026397757909710686 4 -0.029599939002876861 5 -0.028638391711151619 7 -0.035191160183920572 
		11 -0.071586327925844823 14 -0.060990996324478422 16 -0.06330102641322588 17 0.010002033860088227 
		18 0.035486008525241572 19 -0.029096316584012981 23 0.012635139676156261 27 -0.012024595211330305 
		29 -0.033390470851540059 35 0.0030470542138405525 40 0.0012975540238176347 45 0.00050263996420009459;
createNode animCurveTA -n "rat_sharf_L_C_CTRL_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_sharf_L_C_CTRL_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_sharf_L_C_CTRL_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_sharf_L_B_CTRL_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_sharf_L_B_CTRL_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_sharf_L_B_CTRL_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_sharf_L_A_CTRL_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_sharf_L_A_CTRL_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_sharf_L_A_CTRL_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_sharf_R_C_CTRL_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_sharf_R_C_CTRL_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_sharf_R_C_CTRL_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_sharf_R_B_CTRL_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_sharf_R_B_CTRL_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_sharf_R_B_CTRL_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_sharf_R_A_CTRL_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_sharf_R_A_CTRL_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_sharf_R_A_CTRL_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_us_L_CTRL_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_us_L_CTRL_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_us_L_CTRL_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_us_R_CTRL_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_us_R_CTRL_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_us_R_CTRL_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTU -n "rat_FKEar_L_scaleZ1";
	setAttr ".tan" 9;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 6 0.99999999999999978 
		9 0.99999999999999978 17 0.99999999999999978 21 0.99999999999999978 28 0.99999999999999978 
		45 0.99999999999999978;
	setAttr -s 7 ".kit[5:6]"  3 3;
	setAttr -s 7 ".kot[5:6]"  3 3;
createNode animCurveTU -n "rat_FKEar_L_scaleY1";
	setAttr ".tan" 9;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 6 0.99999999999999978 
		9 0.99999999999999978 17 0.99999999999999978 21 0.99999999999999978 28 0.99999999999999978 
		45 0.99999999999999978;
	setAttr -s 7 ".kit[5:6]"  3 3;
	setAttr -s 7 ".kot[5:6]"  3 3;
createNode animCurveTU -n "rat_FKEar_L_scaleX1";
	setAttr ".tan" 9;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 9 1 17 1 21 1 28 1 45 1;
	setAttr -s 7 ".kit[5:6]"  3 3;
	setAttr -s 7 ".kot[5:6]"  3 3;
createNode animCurveTA -n "rat_FKEar_L_rotateZ1";
	setAttr ".tan" 9;
	setAttr -s 11 ".ktv[0:10]"  0 -8.8461353916935046 2 8.8302317126502619 
		4 -14.690962840714434 6 -14.405849322159229 9 1.436711823240822 12 5.5068654860127895 
		17 3.332168501168244 21 -7.105996965456904 23 4.2923558299600604 28 -8.8461353916935046 
		45 -8.8461353916935046;
	setAttr -s 11 ".kit[9:10]"  3 3;
	setAttr -s 11 ".kot[9:10]"  3 3;
createNode animCurveTA -n "rat_FKEar_L_rotateY1";
	setAttr ".tan" 9;
	setAttr -s 11 ".ktv[0:10]"  0 -10.558746121377578 2 -38.061727074543896 
		4 1.0733154324927088 6 0.50589782665213989 9 -28.008190690706947 12 -33.485090237732223 
		17 -30.011401923479671 21 -12.88788130708514 23 -32.332556214220858 28 -10.558746121377578 
		45 -10.558746121377578;
	setAttr -s 11 ".kit[9:10]"  3 3;
	setAttr -s 11 ".kot[9:10]"  3 3;
createNode animCurveTA -n "rat_FKEar_L_rotateX1";
	setAttr ".tan" 9;
	setAttr -s 11 ".ktv[0:10]"  0 -27.029421236799305 2 -34.570209519885424 
		4 -26.774784610774564 6 -26.787205908927874 9 -30.715996200867103 12 -32.879424307453412 
		17 -31.993060253867718 21 -28.271731277483092 23 -31.978574377079699 28 -27.029421236799305 
		45 -27.029421236799305;
	setAttr -s 11 ".kit[9:10]"  3 3;
	setAttr -s 11 ".kot[9:10]"  3 3;
createNode animCurveTU -n "rat_FKEar_R_scaleZ1";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.99999999999999989 6 0.99999999999999989 
		17 0.99999999999999989 21 0.99999999999999989 28 0.99999999999999989 45 0.99999999999999989;
	setAttr -s 6 ".kit[4:5]"  3 3;
	setAttr -s 6 ".kot[4:5]"  3 3;
createNode animCurveTU -n "rat_FKEar_R_scaleY1";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 1 6 1 17 1 21 1 28 1 45 1;
	setAttr -s 6 ".kit[4:5]"  3 3;
	setAttr -s 6 ".kot[4:5]"  3 3;
createNode animCurveTU -n "rat_FKEar_R_scaleX1";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.99999999999999989 6 0.99999999999999989 
		17 0.99999999999999989 21 0.99999999999999989 28 0.99999999999999989 45 0.99999999999999989;
	setAttr -s 6 ".kit[4:5]"  3 3;
	setAttr -s 6 ".kot[4:5]"  3 3;
createNode animCurveTA -n "rat_FKEar_R_rotateZ1";
	setAttr ".tan" 9;
	setAttr -s 11 ".ktv[0:10]"  0 -9.7900007771411701 2 14.84356905337205 
		4 -8.1937943685876942 6 -8.2716580915893516 9 7.7207460287759222 12 15.179938324920013 
		17 11.396614423550462 21 -4.2205986902906707 23 2.52046822281382 28 -9.7900007771411701 
		45 -9.7900007771411701;
	setAttr -s 11 ".kit[9:10]"  3 3;
	setAttr -s 11 ".kot[9:10]"  3 3;
createNode animCurveTA -n "rat_FKEar_R_rotateY1";
	setAttr ".tan" 9;
	setAttr -s 11 ".ktv[0:10]"  0 6.4805770496356896 2 -33.752428620423444 
		4 3.5081226989801051 6 3.6531204642780541 9 -23.804201609568416 12 -33.312232718090954 
		17 -27.283019443619466 21 -2.7920054574531528 23 -15.681608031921552 28 6.4805770496356896 
		45 6.4805770496356896;
	setAttr -s 11 ".kit[9:10]"  3 3;
	setAttr -s 11 ".kot[9:10]"  3 3;
createNode animCurveTA -n "rat_FKEar_R_rotateX1";
	setAttr ".tan" 9;
	setAttr -s 11 ".ktv[0:10]"  0 -28.534785159741237 2 -34.810263829813969 
		4 -28.821945343192926 6 -28.807937530129671 9 -31.676852407065006 12 -35.534135757137101 
		17 -34.473628148329716 21 -30.821366199775134 23 -29.67775935262307 28 -28.534785159741237 
		45 -28.534785159741237;
	setAttr -s 11 ".kit[9:10]"  3 3;
	setAttr -s 11 ".kot[9:10]"  3 3;
createNode animCurveTA -n "rat_hair_CTRL_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_hair_CTRL_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_hair_CTRL_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTL -n "rat_hair_CTRL_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTL -n "rat_hair_CTRL_translateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTL -n "rat_hair_CTRL_translateX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTU -n "rat_FKJaw_M_scaleZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0.99999999999999978 2 0.99999999999999978 
		3 0.99999999999999978 4 0.99999999999999978 5 0.99999999999999978 7 0.99999999999999978 
		9 0.99999999999999978 11 0.99999999999999978 13 0.99999999999999978 15 0.99999999999999978 
		16 0.99999999999999978 17 0.99999999999999978 19 0.99999999999999978 23 0.99999999999999978 
		29 0.99999999999999978 35 0.99999999999999978 40 0.99999999999999978 45 0.99999999999999978;
createNode animCurveTU -n "rat_FKJaw_M_scaleY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0.99999999999999989 2 0.99999999999999989 
		3 0.99999999999999989 4 0.99999999999999989 5 0.99999999999999989 7 0.99999999999999989 
		9 0.99999999999999989 11 0.99999999999999989 13 0.99999999999999989 15 0.99999999999999989 
		16 0.99999999999999989 17 0.99999999999999989 19 0.99999999999999989 23 0.99999999999999989 
		29 0.99999999999999989 35 0.99999999999999989 40 0.99999999999999989 45 0.99999999999999989;
createNode animCurveTU -n "rat_FKJaw_M_scaleX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 1.0000000000000002 2 1.0000000000000002 
		3 1.0000000000000002 4 1.0000000000000002 5 1.0000000000000002 7 1.0000000000000002 
		9 1.0000000000000002 11 1.0000000000000002 13 1.0000000000000002 15 1.0000000000000002 
		16 1.0000000000000002 17 1.0000000000000002 19 1.0000000000000002 23 1.0000000000000002 
		29 1.0000000000000002 35 1.0000000000000002 40 1.0000000000000002 45 1.0000000000000002;
createNode animCurveTA -n "rat_FKJaw_M_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 -13.463662348216772 2 -13.463662348216772 
		3 -13.463662348216772 4 -13.463662348216772 5 -11.668401400807454 7 -11.668401400807454 
		9 -11.668401400807454 11 -11.668401400807454 13 -11.668401400807454 15 -11.668401400807454 
		16 -11.668401400807454 17 -11.668401400807454 19 -11.668401400807454 23 -11.668401400807454 
		29 -11.668401400807454 35 -11.668401400807454 40 -11.668401400807454 45 -13.463662348216772;
createNode animCurveTA -n "rat_FKJaw_M_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_FKJaw_M_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTL -n "rat_FKJaw_M_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTL -n "rat_FKJaw_M_translateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTL -n "rat_FKJaw_M_translateX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTU -n "rat_FKHead_M_Global1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 10 2 10 3 10 4 10 5 10 7 10 9 10 11 10 
		13 10 15 10 16 10 17 10 19 10 23 10 29 10 35 10 40 10 45 10;
createNode animCurveTU -n "rat_FKHead_M_scaleZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0.99999999999999989 2 0.99999999999999989 
		3 0.99999999999999989 4 0.99999999999999989 5 0.99999999999999989 7 0.99999999999999989 
		9 0.99999999999999989 11 0.99999999999999989 13 0.99999999999999989 15 0.99999999999999989 
		16 0.99999999999999989 17 0.99999999999999989 19 0.99999999999999989 23 0.99999999999999989 
		29 0.99999999999999989 35 0.99999999999999989 40 0.99999999999999989 45 0.99999999999999989;
createNode animCurveTU -n "rat_FKHead_M_scaleY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 1 2 1 3 1 4 1 5 1 7 1 9 1 11 1 13 1 15 
		1 16 1 17 1 19 1 23 1 29 1 35 1 40 1 45 1;
createNode animCurveTU -n "rat_FKHead_M_scaleX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 1 2 1 3 1 4 1 5 1 7 1 9 1 11 1 13 1 15 
		1 16 1 17 1 19 1 23 1 29 1 35 1 40 1 45 1;
createNode animCurveTA -n "rat_FKHead_M_rotateZ1";
	setAttr ".tan" 1;
	setAttr -s 19 ".ktv[0:18]"  0 -11.733703531610507 1 -8.0333082911297247 
		2 -23.845730250059223 3 -31.658530587650915 4 24.456455684647647 5 57.407975882768142 
		7 72.844659367677579 9 77.846222370951509 11 81.675557672892253 13 83.409394266838049 
		15 67.542385913990827 17 40.984977665740246 19 16.917591036274562 21 -4.3419741537409573 
		23 -14.056954265854756 29 -15.329032358726559 35 -14.574327681456003 40 -12.306547696498129 
		45 -11.733703531610507;
	setAttr -s 19 ".kit[0:18]"  3 2 1 1 1 1 1 1 
		1 1 1 9 9 9 1 3 9 9 3;
	setAttr -s 19 ".kot[0:18]"  3 2 1 1 1 1 1 1 
		1 1 1 9 9 9 1 3 9 9 3;
	setAttr -s 19 ".kix[2:18]"  0.066243715584278107 0.033257734030485153 
		0.032142732292413712 0.033892754465341568 0.064216643571853638 0.06834828108549118 
		0.067939125001430511 0.066210448741912842 0.060756515711545944 0.066666662693023682 
		0.066666662693023682 0.066666662693023682 0.063241444528102875 0.19999998807907104 
		0.19999998807907104 0.16666674613952637 0.16666662693023682;
	setAttr -s 19 ".kiy[2:18]"  0.031027026474475861 0.028520606458187103 
		0.47011092305183411 0.18858674168586731 0.26818075776100159 0.21229852735996246 0.059567835181951523 
		-0.067424952983856201 -0.34666386246681213 -0.44178467988967896 -0.39555227756500244 
		-0.27030390501022339 -0.026325980201363564 0 0.028773980215191841 0.024789130315184593 
		0;
	setAttr -s 19 ".kox[2:18]"  0.032910443842411041 0.03325774148106575 
		0.032142724841833115 0.06722617894411087 0.064216651022434235 0.068348273634910583 
		0.067939125001430511 0.066210441291332245 0.02742476761341095 0.066666662693023682 
		0.066666662693023682 0.066666662693023682 0.19657407701015472 0.19999998807907104 
		0.16666674613952637 0.16666662693023682 0.16666662693023682;
	setAttr -s 19 ".koy[2:18]"  0.015414491295814514 0.028520615771412849 
		0.47011080384254456 0.3740612268447876 0.26818078756332397 0.2122984379529953 0.059567831456661224 
		-0.067424945533275604 -0.15647993981838226 -0.44178467988967896 -0.39555227756500244 
		-0.27030390501022339 -0.08182932436466217 0 0.023978330194950104 0.02478911355137825 
		0;
createNode animCurveTA -n "rat_FKHead_M_rotateY1";
	setAttr ".tan" 9;
	setAttr -s 19 ".ktv[0:18]"  0 -3.6764156790093838 1 -0.78978953227095272 
		2 2.0598491512770467 3 -3.1695036271036177 4 -4.7029111769396543 5 -5.5173761485150239 
		7 -4.4146443504563102 9 -2.6387660069608434 11 -1.334649451112655 13 -0.91495531537886965 
		15 -1.5417279972166538 16 -2.6544592626106183 17 -5.6390599191968525 19 -8.8319843702850349 
		23 -10.171350940642215 29 -10.285977280098969 35 -9.1378194458277893 40 -5.7157304931835 
		45 -3.6764156790093838;
	setAttr -s 19 ".kit[0:18]"  3 2 3 1 1 1 9 9 
		9 9 9 9 9 9 9 9 9 9 3;
	setAttr -s 19 ".kot[0:18]"  3 2 3 1 1 1 9 9 
		9 9 9 9 9 9 9 9 9 9 3;
	setAttr -s 19 ".kix[3:18]"  0.03246987983584404 0.032925352454185486 
		0.032667461782693863 0.066666662693023682 0.066666677594184875 0.066666662693023682 
		0.066666662693023682 0.066666662693023682 0.033333361148834229 0.033333301544189453 
		0.066666662693023682 0.13333332538604736 0.19999998807907104 0.19999998807907104 
		0.16666674613952637 0.16666662693023682;
	setAttr -s 19 ".kiy[3:18]"  -0.08352227509021759 -0.0025039631873369217 
		0.0022405469790101051 0.025120610371232033 0.026878029108047485 0.015043086372315884 
		-0.0018071011872962117 -0.020240042358636856 -0.035755999386310577 -0.035939361900091171 
		-0.026367800310254097 -0.010150785557925701 0.0090192640200257301 0.043508637696504593 
		0.047659754753112793 0;
	setAttr -s 19 ".kox[3:18]"  0.032469883561134338 0.032925352454185486 
		0.066000699996948242 0.066666677594184875 0.066666662693023682 0.066666662693023682 
		0.066666662693023682 0.033333361148834229 0.033333301544189453 0.066666662693023682 
		0.13333332538604736 0.19999998807907104 0.19999998807907104 0.16666674613952637 0.16666662693023682 
		0.16666662693023682;
	setAttr -s 19 ".koy[3:18]"  -0.083522297441959381 -0.0025039631873369217 
		0.0045267571695148945 0.02512061595916748 0.026878023520112038 0.015043086372315884 
		-0.0018071011872962117 -0.0101200295612216 -0.035755936056375504 -0.071878790855407715 
		-0.052735600620508194 -0.015226177871227264 0.0090192640200257301 0.036257218569517136 
		0.047659721225500107 0;
createNode animCurveTA -n "rat_FKHead_M_rotateX1";
	setAttr ".tan" 3;
	setAttr -s 18 ".ktv[0:17]"  0 -0.93306364833274735 1 -0.92574589071159719 
		2 -1.347770076187407 3 -2.8146410335004455 4 5.8209148773225481 5 6.5908881698691602 
		7 7.3038768617830554 9 6.7937047341438674 13 6.1432118867226819 15 5.1465755920974283 
		16 4.4475118210790443 17 3.5593731764622456 19 1.4848776125455039 23 -1.2523411388324148 
		29 2.941016499770257 35 -7.1205112993371023 40 2.941016499770257 45 -0.93306364833274735;
	setAttr -s 18 ".kit[1:17]"  2 1 1 9 1 2 3 1 
		1 9 9 1 3 3 3 3 3;
	setAttr -s 18 ".kot[1:17]"  2 1 1 9 1 2 3 1 
		1 9 9 1 3 3 3 3 3;
	setAttr -s 18 ".kix[2:17]"  0.066513814032077789 0.03544890508055687 
		0.033333338797092438 0.03043547086417675 0.066666662693023682 0.066666677594184875 
		0.13252083957195282 0.06583482027053833 0.033333361148834229 0.033333301544189453 
		0.065335579216480255 0.13333332538604736 0.19999998807907104 0.19999998807907104 
		0.16666674613952637 0.16666662693023682;
	setAttr -s 18 ".kiy[2:17]"  -0.013257763348519802 0.048766117542982101 
		0.082078732550144196 0.0041297911666333675 0.012443999759852886 0 -0.020244495943188667 
		-0.021938521414995193 -0.013850966468453407 -0.017235897481441498 -0.030418891459703445 
		0 0 0 0 0;
	setAttr -s 18 ".kox[2:17]"  0.033180497586727142 0.035448916256427765 
		0.033333331346511841 0.1304347962141037 0.066666677594184875 0.13333332538604736 
		0.065854303538799286 0.03250165656208992 0.033333301544189453 0.066666662693023682 
		0.13200201094150543 0.19999998807907104 0.19999998807907104 0.16666674613952637 0.16666662693023682 
		0.16666662693023682;
	setAttr -s 18 ".koy[2:17]"  -0.0066136512905359268 0.048766128718852997 
		0.082078717648983002 0.017698705196380615 -0.0089041832834482193 0 -0.010060207918286324 
		-0.010830717161297798 -0.013850941322743893 -0.034471824765205383 -0.061457399278879166 
		0 0 0 0 0;
createNode animCurveTL -n "rat_FKHead_M_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 2.4651903288156619e-032 2 0 3 2.4651903288156619e-032 
		4 2.4651903288156619e-032 5 -0.003199087635962512 7 -0.003199087635962512 9 -0.003199087635962512 
		11 -0.003199087635962512 13 -0.003199087635962512 15 0.0093165588172469931 16 -0.003199087635962512 
		17 -0.003199087635962512 19 -0.003199087635962512 23 -0.003199087635962512 29 -0.003199087635962512 
		35 -0.003199087635962512 40 -0.003199087635962512 45 2.4651903288156619e-032;
createNode animCurveTL -n "rat_FKHead_M_translateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 2.2204460492503131e-016 2 0 3 2.2204460492503131e-016 
		4 2.2204460492503131e-016 5 0.057828495207515165 7 0.057828495207515165 9 0.057828495207515165 
		11 0.057828495207515165 13 0.057828495207515165 15 0.057366301409345941 16 0.057828495207515165 
		17 0.057828495207515165 19 0.057828495207515165 23 0.057828495207515165 29 0.057828495207515165 
		35 0.057828495207515165 40 0.057828495207515165 45 2.2204460492503131e-016;
createNode animCurveTL -n "rat_FKHead_M_translateX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 1.1102230246251565e-016 2 0 3 1.1102230246251565e-016 
		4 1.1102230246251565e-016 5 0.0074129138537487819 7 0.0074129138537487819 9 0.0074129138537487819 
		11 0.0074129138537487819 13 0.0074129138537487819 15 0.0067008764868594336 16 0.0074129138537487819 
		17 0.0074129138537487819 19 0.0074129138537487819 23 0.0074129138537487819 29 0.0074129138537487819 
		35 0.0074129138537487819 40 0.0074129138537487819 45 1.1102230246251565e-016;
createNode animCurveTU -n "rat_FKNeck_M_scaleZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0.99999999999999967 2 0.99999999999999967 
		3 0.99999999999999967 4 0.99999999999999967 5 0.99999999999999967 7 0.99999999999999967 
		9 0.99999999999999967 11 0.99999999999999967 13 0.99999999999999967 15 0.99999999999999967 
		16 0.99999999999999967 17 0.99999999999999967 19 0.99999999999999967 23 0.99999999999999967 
		29 0.99999999999999967 35 0.99999999999999967 40 0.99999999999999967 45 0.99999999999999967;
createNode animCurveTU -n "rat_FKNeck_M_scaleY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0.99999999999999933 2 0.99999999999999933 
		3 0.99999999999999933 4 0.99999999999999933 5 0.99999999999999933 7 0.99999999999999933 
		9 0.99999999999999933 11 0.99999999999999933 13 0.99999999999999933 15 0.99999999999999933 
		16 0.99999999999999933 17 0.99999999999999933 19 0.99999999999999933 23 0.99999999999999933 
		29 0.99999999999999933 35 0.99999999999999933 40 0.99999999999999933 45 0.99999999999999933;
createNode animCurveTU -n "rat_FKNeck_M_scaleX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0.99999999999999978 2 0.99999999999999978 
		3 0.99999999999999978 4 0.99999999999999978 5 0.99999999999999978 7 0.99999999999999978 
		9 0.99999999999999978 11 0.99999999999999978 13 0.99999999999999978 15 0.99999999999999978 
		16 0.99999999999999978 17 0.99999999999999978 19 0.99999999999999978 23 0.99999999999999978 
		29 0.99999999999999978 35 0.99999999999999978 40 0.99999999999999978 45 0.99999999999999978;
createNode animCurveTA -n "rat_FKNeck_M_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 -2.6270949091333513 2 -11.733164189793055 
		3 -2.6270949091333513 4 -2.6270949091333513 5 -5.9487848831383783 7 -5.9487848831383783 
		9 -5.9487848831383783 11 -5.9487848831383783 13 -5.9487848831383783 15 -5.9487848831383783 
		16 -5.9487848831383783 17 -5.9487848831383783 19 -5.9487848831383783 23 -5.9487848831383783 
		29 -5.9487848831383783 35 -5.9487848831383783 40 -5.9487848831383783 45 -2.6270949091333513;
createNode animCurveTA -n "rat_FKNeck_M_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 -0.14708646589732674 3 0 4 0 5 0 
		7 0 9 0 11 0 13 0 15 0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_FKNeck_M_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 -0.072879869102526529 3 0 4 0 5 0 
		7 0 9 0 11 0 13 0 15 0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTU -n "rat_Main_scaleZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 1 2 1 3 1 4 1 5 1 7 1 9 1 11 1 13 1 15 
		1 16 1 17 1 19 1 23 1 29 1 35 1 40 1 45 1;
createNode animCurveTU -n "rat_Main_scaleY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 1 2 1 3 1 4 1 5 1 7 1 9 1 11 1 13 1 15 
		1 16 1 17 1 19 1 23 1 29 1 35 1 40 1 45 1;
createNode animCurveTU -n "rat_Main_scaleX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 1 2 1 3 1 4 1 5 1 7 1 9 1 11 1 13 1 15 
		1 16 1 17 1 19 1 23 1 29 1 35 1 40 1 45 1;
createNode animCurveTA -n "rat_Main_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_Main_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTA -n "rat_Main_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTL -n "rat_Main_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTL -n "rat_Main_translateY1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTL -n "rat_Main_translateX1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 0 2 0 3 0 4 0 5 0 7 0 9 0 11 0 13 0 15 
		0 16 0 17 0 19 0 23 0 29 0 35 0 40 0 45 0;
createNode animCurveTU -n "rat_Main_visibility1";
	setAttr ".tan" 2;
	setAttr -s 18 ".ktv[0:17]"  0 1 2 1 3 1 4 1 5 1 7 1 9 1 11 1 13 1 15 
		1 16 1 17 1 19 1 23 1 29 1 35 1 40 1 45 1;
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
	setAttr -s 3 ".sol";
connectAttr "attackSource.cl" "clipLibrary1.sc[0]";
connectAttr "rat_money_world_CTRL_woldCharSwitch1.a" "clipLibrary1.cel[0].cev[0].cevr"
		;
connectAttr "rat_money_world_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "rat_money_world_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "rat_money_world_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "rat_money_world_CTRL_translateZ1.a" "clipLibrary1.cel[0].cev[4].cevr"
		;
connectAttr "rat_money_world_CTRL_translateY1.a" "clipLibrary1.cel[0].cev[5].cevr"
		;
connectAttr "rat_money_world_CTRL_translateX1.a" "clipLibrary1.cel[0].cev[6].cevr"
		;
connectAttr "rat_WagCurveSplineTail_M_increment1.a" "clipLibrary1.cel[0].cev[7].cevr"
		;
connectAttr "rat_WagCurveSplineTail_M_multiply1.a" "clipLibrary1.cel[0].cev[8].cevr"
		;
connectAttr "rat_WagCurveSplineTail_M_timeOffset1.a" "clipLibrary1.cel[0].cev[9].cevr"
		;
connectAttr "rat_WagCurveSplineTail_M_enable1.a" "clipLibrary1.cel[0].cev[10].cevr"
		;
connectAttr "rat_WagCurveSplineTail_M_rotateZ1.a" "clipLibrary1.cel[0].cev[11].cevr"
		;
connectAttr "rat_WagCurveSplineTail_M_rotateY1.a" "clipLibrary1.cel[0].cev[12].cevr"
		;
connectAttr "rat_WagCurveSplineTail_M_rotateX1.a" "clipLibrary1.cel[0].cev[13].cevr"
		;
connectAttr "rat_FKIKLegBack_L_IKVis1.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "rat_FKIKLegBack_L_FKVis1.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "rat_FKIKLegBack_L_FKIKBlend1.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "rat_FKIKLegFront_L_IKVis1.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "rat_FKIKLegFront_L_FKVis1.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "rat_FKIKLegFront_L_FKIKBlend1.a" "clipLibrary1.cel[0].cev[19].cevr"
		;
connectAttr "rat_FKIKSpine_M_IKVis1.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "rat_FKIKSpine_M_FKVis1.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "rat_FKIKSpine_M_FKIKBlend1.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "rat_FKIKLegBack_R_IKVis1.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "rat_FKIKLegBack_R_FKVis1.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "rat_FKIKLegBack_R_FKIKBlend1.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "rat_FKIKSplineTail_M_IKVis1.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "rat_FKIKSplineTail_M_FKVis1.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "rat_FKIKSplineTail_M_FKIKBlend1.a" "clipLibrary1.cel[0].cev[28].cevr"
		;
connectAttr "rat_FKIKLegFront_R_IKVis1.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "rat_FKIKLegFront_R_FKVis1.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "rat_FKIKLegFront_R_FKIKBlend1.a" "clipLibrary1.cel[0].cev[31].cevr"
		;
connectAttr "rat_PoleLegBack_L_follow1.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "rat_PoleLegBack_L_translateZ1.a" "clipLibrary1.cel[0].cev[33].cevr"
		;
connectAttr "rat_PoleLegBack_L_translateY1.a" "clipLibrary1.cel[0].cev[34].cevr"
		;
connectAttr "rat_PoleLegBack_L_translateX1.a" "clipLibrary1.cel[0].cev[35].cevr"
		;
connectAttr "rat_IKLegBackBall_L_rotateX1.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "rat_IKLegBackHeel_L_rotateZ1.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "rat_IKLegBackHeel_L_rotateY1.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "rat_IKLegBackHeel_L_rotateX1.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "rat_IKLegBack_L_Lenght4.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "rat_IKLegBack_L_Lenght3.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "rat_IKLegBack_L_antiPop1.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "rat_IKLegBack_L_stretchy1.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "rat_IKLegBack_L_legAim1.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "rat_IKLegBack_L_rollAngle1.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "rat_IKLegBack_L_roll1.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "rat_IKLegBack_L_swivel1.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "rat_IKLegBack_L_rotateZ1.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "rat_IKLegBack_L_rotateY1.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "rat_IKLegBack_L_rotateX1.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "rat_IKLegBack_L_translateZ1.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "rat_IKLegBack_L_translateY1.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "rat_IKLegBack_L_translateX1.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "rat_PoleLegFront_L_follow1.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "rat_PoleLegFront_L_translateZ1.a" "clipLibrary1.cel[0].cev[70].cevr"
		;
connectAttr "rat_PoleLegFront_L_translateY1.a" "clipLibrary1.cel[0].cev[71].cevr"
		;
connectAttr "rat_PoleLegFront_L_translateX1.a" "clipLibrary1.cel[0].cev[72].cevr"
		;
connectAttr "rat_IKLegFrontBall_L_rotateX1.a" "clipLibrary1.cel[0].cev[76].cevr"
		;
connectAttr "rat_IKLegFrontHeel_L_rotateZ1.a" "clipLibrary1.cel[0].cev[80].cevr"
		;
connectAttr "rat_IKLegFrontHeel_L_rotateY1.a" "clipLibrary1.cel[0].cev[81].cevr"
		;
connectAttr "rat_IKLegFrontHeel_L_rotateX1.a" "clipLibrary1.cel[0].cev[82].cevr"
		;
connectAttr "rat_IKLegFront_L_Lenght4.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "rat_IKLegFront_L_Lenght3.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "rat_IKLegFront_L_antiPop1.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "rat_IKLegFront_L_stretchy1.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr "rat_IKLegFront_L_legAim1.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "rat_IKLegFront_L_rollAngle1.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "rat_IKLegFront_L_roll1.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "rat_IKLegFront_L_swivel1.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "rat_IKLegFront_L_rotateZ1.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "rat_IKLegFront_L_rotateY1.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "rat_IKLegFront_L_rotateX1.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "rat_IKLegFront_L_translateZ1.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "rat_IKLegFront_L_translateY1.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "rat_IKLegFront_L_translateX1.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "rat_PoleLegBack_R_follow1.a" "clipLibrary1.cel[0].cev[158].cevr";
connectAttr "rat_PoleLegBack_R_translateZ1.a" "clipLibrary1.cel[0].cev[159].cevr"
		;
connectAttr "rat_PoleLegBack_R_translateY1.a" "clipLibrary1.cel[0].cev[160].cevr"
		;
connectAttr "rat_PoleLegBack_R_translateX1.a" "clipLibrary1.cel[0].cev[161].cevr"
		;
connectAttr "rat_IKLegBackBall_R_rotateX1.a" "clipLibrary1.cel[0].cev[165].cevr"
		;
connectAttr "rat_IKLegBackHeel_R_rotateZ1.a" "clipLibrary1.cel[0].cev[169].cevr"
		;
connectAttr "rat_IKLegBackHeel_R_rotateY1.a" "clipLibrary1.cel[0].cev[170].cevr"
		;
connectAttr "rat_IKLegBackHeel_R_rotateX1.a" "clipLibrary1.cel[0].cev[171].cevr"
		;
connectAttr "rat_IKLegBack_R_Lenght4.a" "clipLibrary1.cel[0].cev[175].cevr";
connectAttr "rat_IKLegBack_R_Lenght3.a" "clipLibrary1.cel[0].cev[176].cevr";
connectAttr "rat_IKLegBack_R_antiPop1.a" "clipLibrary1.cel[0].cev[177].cevr";
connectAttr "rat_IKLegBack_R_stretchy1.a" "clipLibrary1.cel[0].cev[178].cevr";
connectAttr "rat_IKLegBack_R_legAim1.a" "clipLibrary1.cel[0].cev[179].cevr";
connectAttr "rat_IKLegBack_R_rollAngle1.a" "clipLibrary1.cel[0].cev[180].cevr";
connectAttr "rat_IKLegBack_R_roll1.a" "clipLibrary1.cel[0].cev[181].cevr";
connectAttr "rat_IKLegBack_R_swivel1.a" "clipLibrary1.cel[0].cev[182].cevr";
connectAttr "rat_IKLegBack_R_rotateZ1.a" "clipLibrary1.cel[0].cev[183].cevr";
connectAttr "rat_IKLegBack_R_rotateY1.a" "clipLibrary1.cel[0].cev[184].cevr";
connectAttr "rat_IKLegBack_R_rotateX1.a" "clipLibrary1.cel[0].cev[185].cevr";
connectAttr "rat_IKLegBack_R_translateZ1.a" "clipLibrary1.cel[0].cev[186].cevr";
connectAttr "rat_IKLegBack_R_translateY1.a" "clipLibrary1.cel[0].cev[187].cevr";
connectAttr "rat_IKLegBack_R_translateX1.a" "clipLibrary1.cel[0].cev[188].cevr";
connectAttr "rat_IKSplineTail3_M_stretchy1.a" "clipLibrary1.cel[0].cev[195].cevr"
		;
connectAttr "rat_IKSplineTail3_M_twist1.a" "clipLibrary1.cel[0].cev[196].cevr";
connectAttr "rat_IKSplineTail3_M_follow1.a" "clipLibrary1.cel[0].cev[197].cevr";
connectAttr "rat_IKSplineTail3_M_rotateZ1.a" "clipLibrary1.cel[0].cev[198].cevr"
		;
connectAttr "rat_IKSplineTail3_M_rotateY1.a" "clipLibrary1.cel[0].cev[199].cevr"
		;
connectAttr "rat_IKSplineTail3_M_rotateX1.a" "clipLibrary1.cel[0].cev[200].cevr"
		;
connectAttr "rat_IKSplineTail3_M_translateZ1.a" "clipLibrary1.cel[0].cev[201].cevr"
		;
connectAttr "rat_IKSplineTail3_M_translateY1.a" "clipLibrary1.cel[0].cev[202].cevr"
		;
connectAttr "rat_IKSplineTail3_M_translateX1.a" "clipLibrary1.cel[0].cev[203].cevr"
		;
connectAttr "rat_IKSplineTail2_M_follow1.a" "clipLibrary1.cel[0].cev[214].cevr";
connectAttr "rat_IKSplineTail2_M_translateZ1.a" "clipLibrary1.cel[0].cev[215].cevr"
		;
connectAttr "rat_IKSplineTail2_M_translateY1.a" "clipLibrary1.cel[0].cev[216].cevr"
		;
connectAttr "rat_IKSplineTail2_M_translateX1.a" "clipLibrary1.cel[0].cev[217].cevr"
		;
connectAttr "rat_IKSplineTail1_M_follow1.a" "clipLibrary1.cel[0].cev[228].cevr";
connectAttr "rat_IKSplineTail1_M_translateZ1.a" "clipLibrary1.cel[0].cev[229].cevr"
		;
connectAttr "rat_IKSplineTail1_M_translateY1.a" "clipLibrary1.cel[0].cev[230].cevr"
		;
connectAttr "rat_IKSplineTail1_M_translateX1.a" "clipLibrary1.cel[0].cev[231].cevr"
		;
connectAttr "rat_PoleLegFront_R_follow1.a" "clipLibrary1.cel[0].cev[242].cevr";
connectAttr "rat_PoleLegFront_R_translateZ1.a" "clipLibrary1.cel[0].cev[243].cevr"
		;
connectAttr "rat_PoleLegFront_R_translateY1.a" "clipLibrary1.cel[0].cev[244].cevr"
		;
connectAttr "rat_PoleLegFront_R_translateX1.a" "clipLibrary1.cel[0].cev[245].cevr"
		;
connectAttr "rat_IKLegFrontBall_R_rotateX1.a" "clipLibrary1.cel[0].cev[249].cevr"
		;
connectAttr "rat_IKLegFrontHeel_R_rotateZ1.a" "clipLibrary1.cel[0].cev[253].cevr"
		;
connectAttr "rat_IKLegFrontHeel_R_rotateY1.a" "clipLibrary1.cel[0].cev[254].cevr"
		;
connectAttr "rat_IKLegFrontHeel_R_rotateX1.a" "clipLibrary1.cel[0].cev[255].cevr"
		;
connectAttr "rat_IKLegFront_R_Lenght4.a" "clipLibrary1.cel[0].cev[259].cevr";
connectAttr "rat_IKLegFront_R_Lenght3.a" "clipLibrary1.cel[0].cev[260].cevr";
connectAttr "rat_IKLegFront_R_antiPop1.a" "clipLibrary1.cel[0].cev[261].cevr";
connectAttr "rat_IKLegFront_R_stretchy1.a" "clipLibrary1.cel[0].cev[262].cevr";
connectAttr "rat_IKLegFront_R_legAim1.a" "clipLibrary1.cel[0].cev[263].cevr";
connectAttr "rat_IKLegFront_R_rollAngle1.a" "clipLibrary1.cel[0].cev[264].cevr";
connectAttr "rat_IKLegFront_R_roll1.a" "clipLibrary1.cel[0].cev[265].cevr";
connectAttr "rat_IKLegFront_R_swivel1.a" "clipLibrary1.cel[0].cev[266].cevr";
connectAttr "rat_IKLegFront_R_rotateZ1.a" "clipLibrary1.cel[0].cev[267].cevr";
connectAttr "rat_IKLegFront_R_rotateY1.a" "clipLibrary1.cel[0].cev[268].cevr";
connectAttr "rat_IKLegFront_R_rotateX1.a" "clipLibrary1.cel[0].cev[269].cevr";
connectAttr "rat_IKLegFront_R_translateZ1.a" "clipLibrary1.cel[0].cev[270].cevr"
		;
connectAttr "rat_IKLegFront_R_translateY1.a" "clipLibrary1.cel[0].cev[271].cevr"
		;
connectAttr "rat_IKLegFront_R_translateX1.a" "clipLibrary1.cel[0].cev[272].cevr"
		;
connectAttr "rat_HipSwingerRoot_M_rotateZ1.a" "clipLibrary1.cel[0].cev[279].cevr"
		;
connectAttr "rat_HipSwingerRoot_M_rotateY1.a" "clipLibrary1.cel[0].cev[280].cevr"
		;
connectAttr "rat_HipSwingerRoot_M_rotateX1.a" "clipLibrary1.cel[0].cev[281].cevr"
		;
connectAttr "rat_money_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[282].cevr";
connectAttr "rat_money_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[283].cevr";
connectAttr "rat_money_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[284].cevr";
connectAttr "rat_money_CTRL_translateZ1.a" "clipLibrary1.cel[0].cev[285].cevr";
connectAttr "rat_money_CTRL_translateY1.a" "clipLibrary1.cel[0].cev[286].cevr";
connectAttr "rat_money_CTRL_translateX1.a" "clipLibrary1.cel[0].cev[287].cevr";
connectAttr "rat_bag_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[288].cevr";
connectAttr "rat_bag_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[289].cevr";
connectAttr "rat_bag_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[290].cevr";
connectAttr "rat_bag_CTRL_translateZ1.a" "clipLibrary1.cel[0].cev[291].cevr";
connectAttr "rat_bag_CTRL_translateY1.a" "clipLibrary1.cel[0].cev[292].cevr";
connectAttr "rat_bag_CTRL_translateX1.a" "clipLibrary1.cel[0].cev[293].cevr";
connectAttr "rat_FKChest_M_scaleZ1.a" "clipLibrary1.cel[0].cev[294].cevr";
connectAttr "rat_FKChest_M_scaleY1.a" "clipLibrary1.cel[0].cev[295].cevr";
connectAttr "rat_FKChest_M_scaleX1.a" "clipLibrary1.cel[0].cev[296].cevr";
connectAttr "rat_FKChest_M_rotateZ1.a" "clipLibrary1.cel[0].cev[297].cevr";
connectAttr "rat_FKChest_M_rotateY1.a" "clipLibrary1.cel[0].cev[298].cevr";
connectAttr "rat_FKChest_M_rotateX1.a" "clipLibrary1.cel[0].cev[299].cevr";
connectAttr "rat_FKBackB_M_scaleZ1.a" "clipLibrary1.cel[0].cev[303].cevr";
connectAttr "rat_FKBackB_M_scaleY1.a" "clipLibrary1.cel[0].cev[304].cevr";
connectAttr "rat_FKBackB_M_scaleX1.a" "clipLibrary1.cel[0].cev[305].cevr";
connectAttr "rat_FKBackB_M_rotateZ1.a" "clipLibrary1.cel[0].cev[306].cevr";
connectAttr "rat_FKBackB_M_rotateY1.a" "clipLibrary1.cel[0].cev[307].cevr";
connectAttr "rat_FKBackB_M_rotateX1.a" "clipLibrary1.cel[0].cev[308].cevr";
connectAttr "rat_FKBackA_M_scaleZ1.a" "clipLibrary1.cel[0].cev[312].cevr";
connectAttr "rat_FKBackA_M_scaleY1.a" "clipLibrary1.cel[0].cev[313].cevr";
connectAttr "rat_FKBackA_M_scaleX1.a" "clipLibrary1.cel[0].cev[314].cevr";
connectAttr "rat_FKBackA_M_rotateZ1.a" "clipLibrary1.cel[0].cev[315].cevr";
connectAttr "rat_FKBackA_M_rotateY1.a" "clipLibrary1.cel[0].cev[316].cevr";
connectAttr "rat_FKBackA_M_rotateX1.a" "clipLibrary1.cel[0].cev[317].cevr";
connectAttr "rat_Center_M_CenterBtwFeet1.a" "clipLibrary1.cel[0].cev[321].cevr";
connectAttr "rat_Center_M_rotateZ1.a" "clipLibrary1.cel[0].cev[322].cevr";
connectAttr "rat_Center_M_rotateY1.a" "clipLibrary1.cel[0].cev[323].cevr";
connectAttr "rat_Center_M_rotateX1.a" "clipLibrary1.cel[0].cev[324].cevr";
connectAttr "rat_Center_M_translateZ1.a" "clipLibrary1.cel[0].cev[325].cevr";
connectAttr "rat_Center_M_translateY1.a" "clipLibrary1.cel[0].cev[326].cevr";
connectAttr "rat_Center_M_translateX1.a" "clipLibrary1.cel[0].cev[327].cevr";
connectAttr "rat_FKRump_L_scaleZ1.a" "clipLibrary1.cel[0].cev[361].cevr";
connectAttr "rat_FKRump_L_scaleY1.a" "clipLibrary1.cel[0].cev[362].cevr";
connectAttr "rat_FKRump_L_scaleX1.a" "clipLibrary1.cel[0].cev[363].cevr";
connectAttr "rat_FKRump_L_rotateZ1.a" "clipLibrary1.cel[0].cev[364].cevr";
connectAttr "rat_FKRump_L_rotateY1.a" "clipLibrary1.cel[0].cev[365].cevr";
connectAttr "rat_FKRump_L_rotateX1.a" "clipLibrary1.cel[0].cev[366].cevr";
connectAttr "rat_FKRump_L_translateZ1.a" "clipLibrary1.cel[0].cev[367].cevr";
connectAttr "rat_FKRump_L_translateY1.a" "clipLibrary1.cel[0].cev[368].cevr";
connectAttr "rat_FKRump_L_translateX1.a" "clipLibrary1.cel[0].cev[369].cevr";
connectAttr "rat_FKRump_R_scaleZ1.a" "clipLibrary1.cel[0].cev[406].cevr";
connectAttr "rat_FKRump_R_scaleY1.a" "clipLibrary1.cel[0].cev[407].cevr";
connectAttr "rat_FKRump_R_scaleX1.a" "clipLibrary1.cel[0].cev[408].cevr";
connectAttr "rat_FKRump_R_rotateZ1.a" "clipLibrary1.cel[0].cev[409].cevr";
connectAttr "rat_FKRump_R_rotateY1.a" "clipLibrary1.cel[0].cev[410].cevr";
connectAttr "rat_FKRump_R_rotateX1.a" "clipLibrary1.cel[0].cev[411].cevr";
connectAttr "rat_FKRump_R_translateZ1.a" "clipLibrary1.cel[0].cev[412].cevr";
connectAttr "rat_FKRump_R_translateY1.a" "clipLibrary1.cel[0].cev[413].cevr";
connectAttr "rat_FKRump_R_translateX1.a" "clipLibrary1.cel[0].cev[414].cevr";
connectAttr "rat_FKScapula_L_scaleZ1.a" "clipLibrary1.cel[0].cev[505].cevr";
connectAttr "rat_FKScapula_L_scaleY1.a" "clipLibrary1.cel[0].cev[506].cevr";
connectAttr "rat_FKScapula_L_scaleX1.a" "clipLibrary1.cel[0].cev[507].cevr";
connectAttr "rat_FKScapula_L_rotateZ1.a" "clipLibrary1.cel[0].cev[508].cevr";
connectAttr "rat_FKScapula_L_rotateY1.a" "clipLibrary1.cel[0].cev[509].cevr";
connectAttr "rat_FKScapula_L_rotateX1.a" "clipLibrary1.cel[0].cev[510].cevr";
connectAttr "rat_FKScapula_L_translateZ1.a" "clipLibrary1.cel[0].cev[511].cevr";
connectAttr "rat_FKScapula_L_translateY1.a" "clipLibrary1.cel[0].cev[512].cevr";
connectAttr "rat_FKScapula_L_translateX1.a" "clipLibrary1.cel[0].cev[513].cevr";
connectAttr "rat_FKScapula_R_scaleZ1.a" "clipLibrary1.cel[0].cev[550].cevr";
connectAttr "rat_FKScapula_R_scaleY1.a" "clipLibrary1.cel[0].cev[551].cevr";
connectAttr "rat_FKScapula_R_scaleX1.a" "clipLibrary1.cel[0].cev[552].cevr";
connectAttr "rat_FKScapula_R_rotateZ1.a" "clipLibrary1.cel[0].cev[553].cevr";
connectAttr "rat_FKScapula_R_rotateY1.a" "clipLibrary1.cel[0].cev[554].cevr";
connectAttr "rat_FKScapula_R_rotateX1.a" "clipLibrary1.cel[0].cev[555].cevr";
connectAttr "rat_FKScapula_R_translateZ1.a" "clipLibrary1.cel[0].cev[556].cevr";
connectAttr "rat_FKScapula_R_translateY1.a" "clipLibrary1.cel[0].cev[557].cevr";
connectAttr "rat_FKScapula_R_translateX1.a" "clipLibrary1.cel[0].cev[558].cevr";
connectAttr "rat_sharf_L_C_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[568].cevr";
connectAttr "rat_sharf_L_C_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[569].cevr";
connectAttr "rat_sharf_L_C_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[570].cevr";
connectAttr "rat_sharf_L_B_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[571].cevr";
connectAttr "rat_sharf_L_B_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[572].cevr";
connectAttr "rat_sharf_L_B_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[573].cevr";
connectAttr "rat_sharf_L_A_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[574].cevr";
connectAttr "rat_sharf_L_A_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[575].cevr";
connectAttr "rat_sharf_L_A_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[576].cevr";
connectAttr "rat_sharf_R_C_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[577].cevr";
connectAttr "rat_sharf_R_C_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[578].cevr";
connectAttr "rat_sharf_R_C_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[579].cevr";
connectAttr "rat_sharf_R_B_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[580].cevr";
connectAttr "rat_sharf_R_B_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[581].cevr";
connectAttr "rat_sharf_R_B_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[582].cevr";
connectAttr "rat_sharf_R_A_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[583].cevr";
connectAttr "rat_sharf_R_A_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[584].cevr";
connectAttr "rat_sharf_R_A_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[585].cevr";
connectAttr "rat_us_L_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[586].cevr";
connectAttr "rat_us_L_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[587].cevr";
connectAttr "rat_us_L_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[588].cevr";
connectAttr "rat_us_R_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[589].cevr";
connectAttr "rat_us_R_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[590].cevr";
connectAttr "rat_us_R_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[591].cevr";
connectAttr "rat_FKEar_L_scaleZ1.a" "clipLibrary1.cel[0].cev[592].cevr";
connectAttr "rat_FKEar_L_scaleY1.a" "clipLibrary1.cel[0].cev[593].cevr";
connectAttr "rat_FKEar_L_scaleX1.a" "clipLibrary1.cel[0].cev[594].cevr";
connectAttr "rat_FKEar_L_rotateZ1.a" "clipLibrary1.cel[0].cev[595].cevr";
connectAttr "rat_FKEar_L_rotateY1.a" "clipLibrary1.cel[0].cev[596].cevr";
connectAttr "rat_FKEar_L_rotateX1.a" "clipLibrary1.cel[0].cev[597].cevr";
connectAttr "rat_FKEar_R_scaleZ1.a" "clipLibrary1.cel[0].cev[601].cevr";
connectAttr "rat_FKEar_R_scaleY1.a" "clipLibrary1.cel[0].cev[602].cevr";
connectAttr "rat_FKEar_R_scaleX1.a" "clipLibrary1.cel[0].cev[603].cevr";
connectAttr "rat_FKEar_R_rotateZ1.a" "clipLibrary1.cel[0].cev[604].cevr";
connectAttr "rat_FKEar_R_rotateY1.a" "clipLibrary1.cel[0].cev[605].cevr";
connectAttr "rat_FKEar_R_rotateX1.a" "clipLibrary1.cel[0].cev[606].cevr";
connectAttr "rat_hair_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[610].cevr";
connectAttr "rat_hair_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[611].cevr";
connectAttr "rat_hair_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[612].cevr";
connectAttr "rat_hair_CTRL_translateZ1.a" "clipLibrary1.cel[0].cev[613].cevr";
connectAttr "rat_hair_CTRL_translateY1.a" "clipLibrary1.cel[0].cev[614].cevr";
connectAttr "rat_hair_CTRL_translateX1.a" "clipLibrary1.cel[0].cev[615].cevr";
connectAttr "rat_FKJaw_M_scaleZ1.a" "clipLibrary1.cel[0].cev[616].cevr";
connectAttr "rat_FKJaw_M_scaleY1.a" "clipLibrary1.cel[0].cev[617].cevr";
connectAttr "rat_FKJaw_M_scaleX1.a" "clipLibrary1.cel[0].cev[618].cevr";
connectAttr "rat_FKJaw_M_rotateZ1.a" "clipLibrary1.cel[0].cev[619].cevr";
connectAttr "rat_FKJaw_M_rotateY1.a" "clipLibrary1.cel[0].cev[620].cevr";
connectAttr "rat_FKJaw_M_rotateX1.a" "clipLibrary1.cel[0].cev[621].cevr";
connectAttr "rat_FKJaw_M_translateZ1.a" "clipLibrary1.cel[0].cev[622].cevr";
connectAttr "rat_FKJaw_M_translateY1.a" "clipLibrary1.cel[0].cev[623].cevr";
connectAttr "rat_FKJaw_M_translateX1.a" "clipLibrary1.cel[0].cev[624].cevr";
connectAttr "rat_FKHead_M_Global1.a" "clipLibrary1.cel[0].cev[634].cevr";
connectAttr "rat_FKHead_M_scaleZ1.a" "clipLibrary1.cel[0].cev[635].cevr";
connectAttr "rat_FKHead_M_scaleY1.a" "clipLibrary1.cel[0].cev[636].cevr";
connectAttr "rat_FKHead_M_scaleX1.a" "clipLibrary1.cel[0].cev[637].cevr";
connectAttr "rat_FKHead_M_rotateZ1.a" "clipLibrary1.cel[0].cev[638].cevr";
connectAttr "rat_FKHead_M_rotateY1.a" "clipLibrary1.cel[0].cev[639].cevr";
connectAttr "rat_FKHead_M_rotateX1.a" "clipLibrary1.cel[0].cev[640].cevr";
connectAttr "rat_FKHead_M_translateZ1.a" "clipLibrary1.cel[0].cev[641].cevr";
connectAttr "rat_FKHead_M_translateY1.a" "clipLibrary1.cel[0].cev[642].cevr";
connectAttr "rat_FKHead_M_translateX1.a" "clipLibrary1.cel[0].cev[643].cevr";
connectAttr "rat_FKNeck_M_scaleZ1.a" "clipLibrary1.cel[0].cev[653].cevr";
connectAttr "rat_FKNeck_M_scaleY1.a" "clipLibrary1.cel[0].cev[654].cevr";
connectAttr "rat_FKNeck_M_scaleX1.a" "clipLibrary1.cel[0].cev[655].cevr";
connectAttr "rat_FKNeck_M_rotateZ1.a" "clipLibrary1.cel[0].cev[656].cevr";
connectAttr "rat_FKNeck_M_rotateY1.a" "clipLibrary1.cel[0].cev[657].cevr";
connectAttr "rat_FKNeck_M_rotateX1.a" "clipLibrary1.cel[0].cev[658].cevr";
connectAttr "rat_Main_scaleZ1.a" "clipLibrary1.cel[0].cev[662].cevr";
connectAttr "rat_Main_scaleY1.a" "clipLibrary1.cel[0].cev[663].cevr";
connectAttr "rat_Main_scaleX1.a" "clipLibrary1.cel[0].cev[664].cevr";
connectAttr "rat_Main_rotateZ1.a" "clipLibrary1.cel[0].cev[665].cevr";
connectAttr "rat_Main_rotateY1.a" "clipLibrary1.cel[0].cev[666].cevr";
connectAttr "rat_Main_rotateX1.a" "clipLibrary1.cel[0].cev[667].cevr";
connectAttr "rat_Main_translateZ1.a" "clipLibrary1.cel[0].cev[668].cevr";
connectAttr "rat_Main_translateY1.a" "clipLibrary1.cel[0].cev[669].cevr";
connectAttr "rat_Main_translateX1.a" "clipLibrary1.cel[0].cev[670].cevr";
connectAttr "rat_Main_visibility1.a" "clipLibrary1.cel[0].cev[671].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of attack.ma
