//Maya ASCII 2008 scene
//Name: move.ma
//Last modified: Mon, Aug 10, 2009 05:36:34 PM
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
createNode animClip -n "moveSource";
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
	setAttr ".se" 6;
	setAttr ".ci" no;
createNode animCurveTU -n "rat_money_world_CTRL_woldCharSwitch1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 10 1 10 2 10 3 10 4 10 5 10 6 10;
createNode animCurveTA -n "rat_money_world_CTRL_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_money_world_CTRL_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_money_world_CTRL_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTL -n "rat_money_world_CTRL_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTL -n "rat_money_world_CTRL_translateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTL -n "rat_money_world_CTRL_translateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTU -n "rat_WagCurveSplineTail_M_increment1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1 1 1 2 1 3 1 4 1 5 1 6 1;
createNode animCurveTU -n "rat_WagCurveSplineTail_M_multiply1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1 1 1 2 1 3 1 4 1 5 1 6 1;
createNode animCurveTU -n "rat_WagCurveSplineTail_M_timeOffset1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1 1 1 2 1 3 1 4 1 5 1 6 1;
createNode animCurveTU -n "rat_WagCurveSplineTail_M_enable1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_WagCurveSplineTail_M_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_WagCurveSplineTail_M_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_WagCurveSplineTail_M_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTU -n "rat_FKIKLegBack_L_IKVis1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1 1 1 2 1 3 1 4 1 5 1 6 1;
createNode animCurveTU -n "rat_FKIKLegBack_L_FKVis1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTU -n "rat_FKIKLegBack_L_FKIKBlend1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 10 1 10 2 10 3 10 4 10 5 10 6 10;
createNode animCurveTU -n "rat_FKIKLegFront_L_IKVis1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1 1 1 2 1 3 1 4 1 5 1 6 1;
createNode animCurveTU -n "rat_FKIKLegFront_L_FKVis1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTU -n "rat_FKIKLegFront_L_FKIKBlend1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 10 1 10 2 10 3 10 4 10 5 10 6 10;
createNode animCurveTU -n "rat_FKIKSpine_M_IKVis1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1 1 1 2 1 3 1 4 1 5 1 6 1;
createNode animCurveTU -n "rat_FKIKSpine_M_FKVis1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTU -n "rat_FKIKSpine_M_FKIKBlend1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTU -n "rat_FKIKLegBack_R_IKVis1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1 1 1 2 1 3 1 4 1 5 1 6 1;
createNode animCurveTU -n "rat_FKIKLegBack_R_FKVis1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTU -n "rat_FKIKLegBack_R_FKIKBlend1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 10 1 10 2 10 3 10 4 10 5 10 6 10;
createNode animCurveTU -n "rat_FKIKSplineTail_M_IKVis1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1 1 1 2 1 3 1 4 1 5 1 6 1;
createNode animCurveTU -n "rat_FKIKSplineTail_M_FKVis1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTU -n "rat_FKIKSplineTail_M_FKIKBlend1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 10 1 10 2 10 3 10 4 10 5 10 6 10;
createNode animCurveTU -n "rat_FKIKLegFront_R_IKVis1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1 1 1 2 1 3 1 4 1 5 1 6 1;
createNode animCurveTU -n "rat_FKIKLegFront_R_FKVis1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTU -n "rat_FKIKLegFront_R_FKIKBlend1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 10 1 10 2 10 3 10 4 10 5 10 6 10;
createNode animCurveTU -n "rat_PoleLegBack_L_follow1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 10 1 10 2 10 3 10 4 10 5 10 6 10;
createNode animCurveTL -n "rat_PoleLegBack_L_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0.013642718447768366 4 0 
		5 0 6 0;
createNode animCurveTL -n "rat_PoleLegBack_L_translateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0.0066453651179417773 4 0 
		5 0 6 0;
createNode animCurveTL -n "rat_PoleLegBack_L_translateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0.06754999600448984 4 0 5 
		0 6 0;
createNode animCurveTA -n "rat_IKLegBackBall_L_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 -14.360984155892018 2 -14.360984155892018 
		3 -14.360984155892018 4 -14.360984155892018 5 -14.360984155892018 6 0;
createNode animCurveTA -n "rat_IKLegBackHeel_L_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_IKLegBackHeel_L_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_IKLegBackHeel_L_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTU -n "rat_IKLegBack_L_Lenght4";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1 1 1 2 1 3 1 4 1 5 1 6 1;
createNode animCurveTU -n "rat_IKLegBack_L_Lenght3";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1 1 1 2 1 3 1 4 1 5 1 6 1;
createNode animCurveTU -n "rat_IKLegBack_L_antiPop1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTU -n "rat_IKLegBack_L_stretchy1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTU -n "rat_IKLegBack_L_legAim1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 10 1 10 2 10 3 10 4 10 5 10 6 10;
createNode animCurveTU -n "rat_IKLegBack_L_rollAngle1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 30 1 30 2 30 3 30 4 30 5 30 6 30;
createNode animCurveTU -n "rat_IKLegBack_L_roll1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTU -n "rat_IKLegBack_L_swivel1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_IKLegBack_L_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 12.621973586642335 1 6.3394722847314231 
		2 1.1661128064086186 3 3.6501554087992889 4 -9.040130657936631 5 21.848834920135285 
		6 12.621973586642335;
createNode animCurveTA -n "rat_IKLegBack_L_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 5.1514011070657029 3 13.871603549296303 
		4 0.88774356603662175 5 2.3728309562298167 6 0;
createNode animCurveTA -n "rat_IKLegBack_L_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 38.974611578516701 3 104.45623005820202 
		4 83.874204912912376 5 -30.753156306352974 6 0;
createNode animCurveTL -n "rat_IKLegBack_L_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0.12702532236555147 3 0.37436102212046962 
		4 0.34189238663638194 5 0.11568858444040267 6 0;
createNode animCurveTL -n "rat_IKLegBack_L_translateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -0.67544146673037786 1 -0.059829823943495439 
		2 0.17460037474817006 3 0.44510862912069149 4 0.13900847986851017 5 -0.46430420629775365 
		6 -0.67544146673037786;
createNode animCurveTL -n "rat_IKLegBack_L_translateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -0.014315483407831731 1 -0.063610189248731006 
		2 -0.075566309824884451 3 -0.06400437314340697 4 0.027794545263634576 5 0.053751480813211863 
		6 -0.014315483407831731;
createNode animCurveTU -n "rat_PoleLegFront_L_follow1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 10 1 10 2 10 3 10 4 10 5 10 6 10;
createNode animCurveTL -n "rat_PoleLegFront_L_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTL -n "rat_PoleLegFront_L_translateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTL -n "rat_PoleLegFront_L_translateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_IKLegFrontBall_L_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 -72.222334173529589 2 0 3 0 4 -5.1907393073887853 
		5 -5.1907393073887853 6 0;
createNode animCurveTA -n "rat_IKLegFrontHeel_L_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_IKLegFrontHeel_L_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_IKLegFrontHeel_L_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTU -n "rat_IKLegFront_L_Lenght4";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1 1 1 2 1 3 1 4 1 5 1 6 1;
	setAttr -s 7 ".kit[6]"  1;
	setAttr -s 7 ".kot[6]"  1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  0.033333335071802139;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTU -n "rat_IKLegFront_L_Lenght3";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1 1 1 2 1 3 1 4 1 5 1 6 1;
	setAttr -s 7 ".kit[6]"  1;
	setAttr -s 7 ".kot[6]"  1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  0.033333335071802139;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTU -n "rat_IKLegFront_L_antiPop1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
	setAttr -s 7 ".kit[6]"  1;
	setAttr -s 7 ".kot[6]"  1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  0.033333335071802139;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTU -n "rat_IKLegFront_L_stretchy1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
	setAttr -s 7 ".kit[6]"  1;
	setAttr -s 7 ".kot[6]"  1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  0.033333335071802139;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTU -n "rat_IKLegFront_L_legAim1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 10 1 10 2 10 3 10 4 10 5 10 6 10;
	setAttr -s 7 ".kit[6]"  1;
	setAttr -s 7 ".kot[6]"  1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  0.033333335071802139;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTU -n "rat_IKLegFront_L_rollAngle1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 25 1 25 2 25 3 25 4 25 5 25 6 25;
	setAttr -s 7 ".kit[6]"  1;
	setAttr -s 7 ".kot[6]"  1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  0.033333335071802139;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTU -n "rat_IKLegFront_L_roll1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
	setAttr -s 7 ".kit[6]"  1;
	setAttr -s 7 ".kot[6]"  1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  0.033333335071802139;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTU -n "rat_IKLegFront_L_swivel1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
	setAttr -s 7 ".kit[6]"  1;
	setAttr -s 7 ".kot[6]"  1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  0.033333335071802139;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "rat_IKLegFront_L_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -9.3127945697564893 1 -9.2516759763690022 
		2 -0.91193065070603752 3 -5.895744027013742 4 -9.3127945697564893 5 -9.3127945697564893 
		6 -9.3127945697564893;
	setAttr -s 7 ".kit[6]"  1;
	setAttr -s 7 ".kot[6]"  1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  0.033333335071802139;
	setAttr -s 7 ".koy[6]"  0.0010667206952348351;
createNode animCurveTA -n "rat_IKLegFront_L_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 6.6256195342719844 2 14.49480182202881 
		3 3.1859980716640051 4 0 5 0 6 0;
	setAttr -s 7 ".kit[6]"  1;
	setAttr -s 7 ".kot[6]"  1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  0.033333335071802139;
	setAttr -s 7 ".koy[6]"  0.11563887447118759;
createNode animCurveTA -n "rat_IKLegFront_L_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 1.0698596692499862 2 86.477100756701759 
		3 28.453394789177047 4 0 5 0 6 0;
	setAttr -s 7 ".kit[6]"  1;
	setAttr -s 7 ".kot[6]"  1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  0.033333335071802139;
	setAttr -s 7 ".koy[6]"  0.018672574311494827;
createNode animCurveTL -n "rat_IKLegFront_L_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0.39608892914080096 3 0.24539704357663183 
		4 0 5 0 6 0;
	setAttr -s 7 ".kit[6]"  1;
	setAttr -s 7 ".kot[6]"  1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  0.033333335071802139;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTL -n "rat_IKLegFront_L_translateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.42564370218305425 1 0.75605494845726939 
		2 0.36269863013698628 3 0.12569863013698629 4 0.18369863013698629 5 0.31069863013698629 
		6 0.42564370218305425;
createNode animCurveTL -n "rat_IKLegFront_L_translateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -0.05177318722569263 1 -0.045356985079810994 
		2 -0.021558448151026893 3 0.0033583778811812279 4 0.012613233506474791 5 -0.024478858074561224 
		6 -0.05177318722569263;
createNode animCurveTU -n "rat_PoleLegBack_R_follow1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 10 1 10 2 10 3 10 4 10 5 10 6 10;
createNode animCurveTL -n "rat_PoleLegBack_R_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTL -n "rat_PoleLegBack_R_translateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTL -n "rat_PoleLegBack_R_translateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_IKLegBackBall_R_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 -14.28352808897311 2 -14.28352808897311 
		3 -14.28352808897311 4 -14.28352808897311 5 -14.28352808897311 6 0;
createNode animCurveTA -n "rat_IKLegBackHeel_R_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_IKLegBackHeel_R_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_IKLegBackHeel_R_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTU -n "rat_IKLegBack_R_Lenght4";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1 1 1 2 1 3 1 4 1 5 1 6 1;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegBack_R_Lenght3";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1 1 1 2 1 3 1 4 1 5 1 6 1;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegBack_R_antiPop1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegBack_R_stretchy1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegBack_R_legAim1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 10 1 10 2 10 3 10 4 10 5 10 6 10;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegBack_R_rollAngle1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 30 1 30 2 30 3 30 4 30 5 30 6 30;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegBack_R_roll1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegBack_R_swivel1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "rat_IKLegBack_R_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -18.201566444358416 1 -6.0565277946882601 
		2 -7.9696024380364863 3 1.8885317709764009 4 -2.1769864694160468 5 2.6079099363550511 
		6 -18.201566444358416;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  -0.48640519380569458 0.21197091042995453 
		-0.03338945284485817 0.1720568984746933 -0.070956677198410034 0.083512194454669952 
		-0.36319386959075928;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0.21197091042995453 -0.03338945284485817 
		0.1720568984746933 -0.070956677198410034 0.083512194454669952 -0.36319386959075928 
		0;
createNode animCurveTA -n "rat_IKLegBack_R_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 2.2190633356797855 1 0 2 0 3 -1.5122786683185867 
		4 -8.2135230462125595 5 -1.7007936749853447 6 2.2190633356797855;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  -0.11693450808525085 -0.038729961961507797 
		0 -0.02639424242079258 -0.11695878207683563 0.11366856843233109 0.068414412438869476;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  -0.038729961961507797 0 -0.02639424242079258 
		-0.11695878207683563 0.11366856843233109 0.068414412438869476 0;
createNode animCurveTA -n "rat_IKLegBack_R_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -33.413154898558098 1 0 2 0 3 38.698237580499715 
		4 104.63364715115777 5 96.068403442912071 6 -33.413154898558098;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  -2.0425479412078857 0.58316957950592041 
		0 0.6754116415977478 1.1507899761199951 -0.14949169754981995 -2.2598795890808105;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0.58316957950592041 0 0.6754116415977478 
		1.1507899761199951 -0.14949169754981995 -2.2598795890808105 0;
createNode animCurveTL -n "rat_IKLegBack_R_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.1675802411665743 1 0 2 0 3 0.12702532236555145 
		4 0.48712539267228161 5 0.25249032035749436 6 0.1675802411665743;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  -0.13347494602203369 -0.167580246925354 
		0 0.12702532112598419 0.36010006070137024 -0.23463506996631622 -0.084910079836845398;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  -0.167580246925354 0 0.12702532112598419 
		0.36010006070137024 -0.23463506996631622 -0.084910079836845398 0;
createNode animCurveTL -n "rat_IKLegBack_R_translateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -0.475249729633823 1 -0.67429827099077233 
		2 -0.16603882474172538 3 0.052865248850161528 4 0.40907651622130986 5 0.085359378845896033 
		6 -0.475249729633823;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  -0.514354407787323 -0.19904853403568268 
		0.50825947523117065 0.21890407800674438 0.35621127486228943 -0.3237171471118927 -0.56060910224914551;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  -0.19904853403568268 0.50825947523117065 
		0.21890407800674438 0.35621127486228943 -0.3237171471118927 -0.56060910224914551 
		0;
createNode animCurveTL -n "rat_IKLegBack_R_translateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -0.050785966377423442 1 0.024759614998420498 
		2 0.079591777780376238 3 0.081142855367481448 4 0.092118481570585581 5 0.0078133419141554472 
		6 -0.050785966377423442;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0.075545579195022583 0.054832164198160172 
		0.0015510775847360492 0.010975626297295094 -0.084305137395858765 -0.058599308133125305;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0.10342971980571747 0.054832164198160172 
		0.0015510775847360492 0.010975626297295094 -0.084305137395858765 -0.058599308133125305 
		0;
createNode animCurveTU -n "rat_IKSplineTail3_M_stretchy1";
	setAttr ".tan" 1;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kix[0]"  0.20000000298023224;
	setAttr ".kiy[0]"  0;
	setAttr ".kox[0]"  1;
	setAttr ".koy[0]"  0;
createNode animCurveTU -n "rat_IKSplineTail3_M_twist1";
	setAttr ".tan" 1;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kix[0]"  0.20000000298023224;
	setAttr ".kiy[0]"  0;
	setAttr ".kox[0]"  1;
	setAttr ".koy[0]"  0;
createNode animCurveTU -n "rat_IKSplineTail3_M_follow1";
	setAttr ".tan" 1;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kix[0]"  0.10000000149011612;
	setAttr ".kiy[0]"  0;
	setAttr ".kox[0]"  0.033333331346511841;
	setAttr ".koy[0]"  0;
createNode animCurveTA -n "rat_IKSplineTail3_M_rotateZ1";
	setAttr ".tan" 1;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kix[0]"  0.20000000298023224;
	setAttr ".kiy[0]"  0;
	setAttr ".kox[0]"  1;
	setAttr ".koy[0]"  0;
createNode animCurveTA -n "rat_IKSplineTail3_M_rotateY1";
	setAttr ".tan" 1;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kix[0]"  0.20000000298023224;
	setAttr ".kiy[0]"  0;
	setAttr ".kox[0]"  1;
	setAttr ".koy[0]"  0;
createNode animCurveTA -n "rat_IKSplineTail3_M_rotateX1";
	setAttr ".tan" 1;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kix[0]"  0.20000000298023224;
	setAttr ".kiy[0]"  0;
	setAttr ".kox[0]"  1;
	setAttr ".koy[0]"  0;
createNode animCurveTL -n "rat_IKSplineTail3_M_translateZ1";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  0 0.061993750044314733 3 -0.63813786095141256 
		6 0.061993750044314733;
	setAttr -s 3 ".kit[1:2]"  9 3;
	setAttr -s 3 ".kot[1:2]"  9 3;
createNode animCurveTL -n "rat_IKSplineTail3_M_translateY1";
	setAttr ".tan" 1;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kix[0]"  0.10000000149011612;
	setAttr ".kiy[0]"  0;
	setAttr ".kox[0]"  0.033333331346511841;
	setAttr ".koy[0]"  0;
createNode animCurveTL -n "rat_IKSplineTail3_M_translateX1";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  0 -0.0685 3 0.137 6 -0.068479452054794498;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "rat_IKSplineTail2_M_follow1";
	setAttr ".tan" 9;
	setAttr -s 2 ".ktv[0:1]"  0 0 6 0;
createNode animCurveTL -n "rat_IKSplineTail2_M_translateZ1";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  0 -0.172115054625852 2 -0.63813786095141256 
		5 0.061993750044314733 6 -0.172115054625852;
	setAttr -s 4 ".kit[0:3]"  1 3 3 1;
	setAttr -s 4 ".kot[0:3]"  1 3 3 1;
	setAttr -s 4 ".kix[0:3]"  0.059259649366140366 0.066666670143604279 
		0.10000000149011612 0.027487188577651978;
	setAttr -s 4 ".kiy[0:3]"  -0.56760483980178833 0 0 -0.30794915556907654;
	setAttr -s 4 ".kox[0:3]"  0.059259649366140366 0.10000000149011612 
		0.033333331346511841 0.027487192302942276;
	setAttr -s 4 ".koy[0:3]"  -0.56760478019714355 0 0 -0.30794918537139893;
createNode animCurveTL -n "rat_IKSplineTail2_M_translateY1";
	setAttr ".tan" 9;
	setAttr -s 2 ".ktv[0:1]"  0 0 6 0;
createNode animCurveTL -n "rat_IKSplineTail2_M_translateX1";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  0 -0.060055638956652307 2 0.076944361043347703 
		5 -0.12853509101144681 6 -0.060041940326515303;
	setAttr -s 4 ".kit[0:3]"  1 3 3 1;
	setAttr -s 4 ".kot[0:3]"  1 3 3 1;
	setAttr -s 4 ".kix[0:3]"  0.058263335376977921 0.066666670143604279 
		0.10000000149011612 0.026887796819210052;
	setAttr -s 4 ".kiy[0:3]"  0.17014192044734955 0 0 0.091950654983520508;
	setAttr -s 4 ".kox[0:3]"  0.058263324201107025 0.10000000149011612 
		0.033333331346511841 0.026887796819210052;
	setAttr -s 4 ".koy[0:3]"  0.17014189064502716 0 0 0.091950647532939911;
createNode animCurveTU -n "rat_IKSplineTail1_M_follow1";
	setAttr ".tan" 9;
	setAttr -s 2 ".ktv[0:1]"  0 0 6 0;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  2;
createNode animCurveTL -n "rat_IKSplineTail1_M_translateZ1";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  0 -0.40476065728617011 1 -0.63813786095141256 
		4 0.061993750044314733 6 -0.40476065728617011;
	setAttr -s 4 ".kit[0:3]"  1 3 3 1;
	setAttr -s 4 ".kot[0:3]"  1 3 3 1;
	setAttr -s 4 ".kix[0:3]"  0.031778290867805481 0.033333335071802139 
		0.10000000894069672 0.059758756309747696;
	setAttr -s 4 ".kiy[0:3]"  -0.2506767213344574 0 0 -0.53859823942184448;
	setAttr -s 4 ".kox[0:3]"  0.031778290867805481 0.10000000894069672 
		0.066666662693023682 0.059758763760328293;
	setAttr -s 4 ".koy[0:3]"  -0.2506767213344574 0 0 -0.53859817981719971;
createNode animCurveTL -n "rat_IKSplineTail1_M_translateY1";
	setAttr ".tan" 9;
	setAttr -s 2 ".ktv[0:1]"  0 0 6 0;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  2;
createNode animCurveTL -n "rat_IKSplineTail1_M_translateX1";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  0 0.014294799353749634 1 0.15129478994606241 
		4 -0.25966408594328688 6 0.014308497982945961;
	setAttr -s 4 ".kit[0:3]"  1 3 3 1;
	setAttr -s 4 ".kot[0:3]"  1 3 3 1;
	setAttr -s 4 ".kix[0:3]"  0.028635133057832718 0.033333335071802139 
		0.10000000894069672 0.059226930141448975;
	setAttr -s 4 ".kiy[0:3]"  0.17338025569915771 0 0 0.33374702930450439;
	setAttr -s 4 ".kox[0:3]"  0.028635131195187569 0.10000000894069672 
		0.066666662693023682 0.059226937592029572;
	setAttr -s 4 ".koy[0:3]"  0.17338025569915771 0 0 0.33374705910682678;
createNode animCurveTU -n "rat_PoleLegFront_R_follow1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 10 1 10 2 10 3 10 4 10 5 10 6 10;
createNode animCurveTL -n "rat_PoleLegFront_R_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTL -n "rat_PoleLegFront_R_translateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTL -n "rat_PoleLegFront_R_translateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_IKLegFrontBall_R_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -5.1972114013085351 1 0 2 -72.312283858468533 
		3 0 4 0 5 -5.1972114013085351 6 -5.1972114013085351;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0.090708449482917786 -1.2620874643325806 
		1.2620874643325806 0 -0.090708449482917786 0;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0.090708449482917786 -1.2620874643325806 
		1.2620874643325806 0 -0.090708449482917786 0 0;
createNode animCurveTA -n "rat_IKLegFrontHeel_R_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_IKLegFrontHeel_R_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_IKLegFrontHeel_R_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTU -n "rat_IKLegFront_R_Lenght4";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1 1 1 2 1 3 1 4 1 5 1 6 1;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegFront_R_Lenght3";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1 1 1 2 1 3 1 4 1 5 1 6 1;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegFront_R_antiPop1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegFront_R_stretchy1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegFront_R_legAim1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 10 1 10 2 10 3 10 4 10 5 10 6 10;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegFront_R_rollAngle1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 25 1 25 2 25 3 25 4 25 5 25 6 25;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegFront_R_roll1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_IKLegFront_R_swivel1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "rat_IKLegFront_R_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 12.437329700509506 1 8.8653462352436101 
		2 8.8432047596362153 3 1.1475358207931643 4 5.7852403221119415 5 15.575461877917986 
		6 12.437329700509506;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  -0.054770737886428833 -0.062342870980501175 
		-0.00038644165033474565 -0.13431476056575775 0.080943211913108826 0.17087160050868988 
		-0.054770737886428833;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  -0.062342870980501175 -0.00038644165033474565 
		-0.13431476056575775 0.080943211913108826 0.17087160050868988 -0.054770737886428833 
		0;
createNode animCurveTA -n "rat_IKLegFront_R_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 -4.0827129276913903 3 -18.359173810196083 
		4 -3.12581101403133 5 0 6 0;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 -0.071256786584854126 -0.24917124211788177 
		0.26587232947349548 0.054555695503950119 0;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0 -0.071256786584854126 -0.24917124211788177 
		0.26587232947349548 0.054555695503950119 0 0;
createNode animCurveTA -n "rat_IKLegFront_R_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0.62867868187314457 3 86.546574897480752 
		4 28.447270188359493 5 0 6 0;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0.010972512885928154 1.4995502233505249 
		-1.0140241384506226 -0.49649852514266968 0;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0 0.010972512885928154 1.4995502233505249 
		-1.0140241384506226 -0.49649852514266968 0 0;
createNode animCurveTL -n "rat_IKLegFront_R_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0.39608892914080096 4 0.24539704357663183 
		5 0 6 0;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0.39608892798423767 -0.15069188177585602 
		-0.24539704620838165 0;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0 0 0.39608892798423767 -0.15069188177585602 
		-0.24539704620838165 0 0;
createNode animCurveTL -n "rat_IKLegFront_R_translateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.167 1 0.2821026793301738 2 0.748 3 
		0.219 4 -0.018 5 0.04 6 0.167;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0.12700000405311584 0.11510267853736877 
		0.4658973217010498 -0.52899998426437378 -0.2370000034570694 0.057999998331069946 
		0.12700000405311584;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0.11510267853736877 0.4658973217010498 
		-0.52899998426437378 -0.2370000034570694 0.057999998331069946 0.12700000405311584 
		0;
createNode animCurveTL -n "rat_IKLegFront_R_translateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.050160302155033532 1 0.047525821460673301 
		2 0.044260019870330208 3 0.05072143770564172 4 0.010892725213678539 5 0.0495135741977491 
		6 0.050160302155033532;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0.00064672797452658415 -0.0026344805955886841 
		-0.0032658015843480825 0.006461417768150568 -0.039828713983297348 0.038620848208665848 
		0.00064672797452658415;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  -0.0026344805955886841 -0.0032658015843480825 
		0.006461417768150568 -0.039828713983297348 0.038620848208665848 0.00064672797452658415 
		0;
createNode animCurveTA -n "rat_HipSwingerRoot_M_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -1.6136796277686034 1 -4.5437540418769986 
		2 -2.7304119825787123 3 5.6663810515659838 4 7.6806082876626682 5 0.021581566982107885 
		6 -1.6136796277686034;
createNode animCurveTA -n "rat_HipSwingerRoot_M_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.038441165342370014 1 0.19800482963408866 
		2 -0.61444256391550101 3 -1.9438066973671131 4 -0.79938619341990313 5 0.2075870389745717 
		6 0.038441165342370014;
createNode animCurveTA -n "rat_HipSwingerRoot_M_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.14737015645620172 1 0.65732095226638843 
		2 0.92096730041380148 3 -0.19861108303754013 4 -0.66825404765853114 5 0.44800686614330032 
		6 0.14737015645620172;
createNode animCurveTA -n "rat_money_CTRL_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_money_CTRL_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_money_CTRL_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTL -n "rat_money_CTRL_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTL -n "rat_money_CTRL_translateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTL -n "rat_money_CTRL_translateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_bag_CTRL_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 3.6672759404163608 1 12.551603465053445 
		2 2.6953503200741045 3 -3.520962737927205 4 -4.346887083218884 5 3.4975121089170171 
		6 3.6672759404163608;
createNode animCurveTA -n "rat_bag_CTRL_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -2.0993794092522049 1 -0.40437784204691474 
		2 2.6161683738156225 3 3.0687413122602418 4 1.8460134667723282 5 -0.77312906029544692 
		6 -2.0993794092522049;
createNode animCurveTA -n "rat_bag_CTRL_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -1.1884397284792854 1 3.0509319818307001 
		2 5.20216103654246 3 3.7371455347249714 4 -0.50366582167425866 5 -4.3507737873693895 
		6 -1.1884397284792854;
createNode animCurveTL -n "rat_bag_CTRL_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTL -n "rat_bag_CTRL_translateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTL -n "rat_bag_CTRL_translateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTU -n "rat_FKChest_M_scaleZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1 1 1 2 1 3 1 4 1 5 1 6 1;
createNode animCurveTU -n "rat_FKChest_M_scaleY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 1 0.99999999999999978 
		2 0.99999999999999978 3 0.99999999999999978 4 0.99999999999999978 5 0.99999999999999978 
		6 0.99999999999999978;
createNode animCurveTU -n "rat_FKChest_M_scaleX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 1 0.99999999999999978 
		2 0.99999999999999978 3 0.99999999999999978 4 0.99999999999999978 5 0.99999999999999978 
		6 0.99999999999999978;
createNode animCurveTA -n "rat_FKChest_M_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 12.754164351599339 1 16.091245759269903 
		2 17.854639409652442 3 16.688866112795491 4 11.472190127388712 5 9.3756814070134116 
		6 12.754164351599339;
createNode animCurveTA -n "rat_FKChest_M_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_FKChest_M_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTU -n "rat_FKBackB_M_scaleZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1 1 1 2 1 3 1 4 1 5 1 6 1;
createNode animCurveTU -n "rat_FKBackB_M_scaleY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 1 0.99999999999999978 
		2 0.99999999999999978 3 0.99999999999999978 4 0.99999999999999978 5 0.99999999999999978 
		6 0.99999999999999978;
createNode animCurveTU -n "rat_FKBackB_M_scaleX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 1 0.99999999999999978 
		2 0.99999999999999978 3 0.99999999999999978 4 0.99999999999999978 5 0.99999999999999978 
		6 0.99999999999999978;
createNode animCurveTA -n "rat_FKBackB_M_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 3.2109779059782393 1 13.362763227412014 
		2 10.256919652374943 3 6.5897386937825635 4 4.4027442554826122 5 3.6938775160025825 
		6 3.2109779059782393;
createNode animCurveTA -n "rat_FKBackB_M_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -1.1927250120035384 1 -1.3906493117630561 
		2 -1.1820367647959649 3 -1.2688972984997979 4 -1.2042009134684064 5 -1.1795639043753272 
		6 -1.1927250120035384;
createNode animCurveTA -n "rat_FKBackB_M_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.001053061753483571 1 0.47112572916825723 
		2 0.037264467721838751 3 -0.076419115805509349 4 0.025980348314999555 5 0.058927611920968778 
		6 0.001053061753483571;
createNode animCurveTU -n "rat_FKBackA_M_scaleZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1 1 1 2 1 3 1 4 1 5 1 6 1;
createNode animCurveTU -n "rat_FKBackA_M_scaleY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 1 0.99999999999999978 
		2 0.99999999999999978 3 0.99999999999999978 4 0.99999999999999978 5 0.99999999999999978 
		6 0.99999999999999978;
createNode animCurveTU -n "rat_FKBackA_M_scaleX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 1 0.99999999999999978 
		2 0.99999999999999978 3 0.99999999999999978 4 0.99999999999999978 5 0.99999999999999978 
		6 0.99999999999999978;
createNode animCurveTA -n "rat_FKBackA_M_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 32.288556401355336 1 36.710646551765848 
		2 30.686459555855102 3 20.648632927222064 4 14.848962822036921 5 19.860446517978822 
		6 32.288556401355336;
createNode animCurveTA -n "rat_FKBackA_M_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_FKBackA_M_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.135 1 -0.3841051246080518 2 0.034013051913737671 
		3 1.4298933505166849 4 1.7849591713317507 5 1.3514341533711602 6 0.13531659761552051;
createNode animCurveTU -n "rat_Center_M_CenterBtwFeet1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_Center_M_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_Center_M_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 2.7787628344708928 1 1.1441964612527222 
		2 -3.5960460210799754 3 -5.0754867293679728 4 -3.2691327464363451 5 1.7980230105399917 
		6 2.7787628344708928;
createNode animCurveTA -n "rat_Center_M_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -22.485759365314792 1 -21.442909944464262 
		2 -19.405447503481291 3 -15.159928392358088 4 -6.9132384464196903 5 -9.3186730380531078 
		6 -22.485759365314792;
createNode animCurveTL -n "rat_Center_M_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -0.085470167153313195 1 0.12620239252849927 
		2 0.20346370804787406 3 0.1824382082176349 4 0.092817886945042297 5 -0.027462056954599461 
		6 -0.085470167153313195;
createNode animCurveTL -n "rat_Center_M_translateY1";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "rat_Center_M_translateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTU -n "rat_FKRump_L_scaleZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1.0000000000000002 1 1.0000000000000002 
		2 1.0000000000000002 3 1.0000000000000002 4 1.0000000000000002 5 1.0000000000000002 
		6 1.0000000000000002;
createNode animCurveTU -n "rat_FKRump_L_scaleY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999989 1 0.99999999999999989 
		2 0.99999999999999989 3 0.99999999999999989 4 0.99999999999999989 5 0.99999999999999989 
		6 0.99999999999999989;
createNode animCurveTU -n "rat_FKRump_L_scaleX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1 1 1 2 1 3 1 4 1 5 1 6 1;
createNode animCurveTA -n "rat_FKRump_L_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_FKRump_L_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_FKRump_L_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTL -n "rat_FKRump_L_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -0.0081728640813699283 1 -0.010382570831665281 
		2 0.0089192467791209869 3 0.012093813579139037 4 -0.010076730778967287 5 -0.0033758975785769022 
		6 -0.0081728640813699283;
createNode animCurveTL -n "rat_FKRump_L_translateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -0.015939520734782834 1 -0.0082191109384427037 
		2 -0.16387179429090817 3 -0.18560243795312822 4 0.00093788773781619018 5 0.053984347156594344 
		6 -0.015939520734782834;
createNode animCurveTL -n "rat_FKRump_L_translateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.14809358525139321 1 0.17280136645615338 
		2 0.15803810051813144 3 0.10946699596216279 4 0.088187558680001554 5 0.16265846729926012 
		6 0.14809358525139321;
createNode animCurveTU -n "rat_FKRump_R_scaleZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1.0000000000000002 1 1.0000000000000002 
		2 1.0000000000000002 3 1.0000000000000002 4 1.0000000000000002 5 1.0000000000000002 
		6 1.0000000000000002;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_FKRump_R_scaleY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1.0000000000000002 1 1.0000000000000002 
		2 1.0000000000000002 3 1.0000000000000002 4 1.0000000000000002 5 1.0000000000000002 
		6 1.0000000000000002;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_FKRump_R_scaleX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1.0000000000000002 1 1.0000000000000002 
		2 1.0000000000000002 3 1.0000000000000002 4 1.0000000000000002 5 1.0000000000000002 
		6 1.0000000000000002;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "rat_FKRump_R_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "rat_FKRump_R_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "rat_FKRump_R_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "rat_FKRump_R_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.032192498465523238 1 0.020517309740684535 
		2 0.021886589939847021 3 0.00075308581881384454 4 0.0048001869082976217 5 0.061342817347101661 
		6 0.032192498465523238;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  -0.0093962736427783966 -0.011675188317894936 
		0.0013692801585420966 -0.021133504807949066 0.0040471008978784084 0.056542631238698959 
		-0.02915031835436821;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  -0.011675188317894936 0.0013692801585420966 
		-0.021133504807949066 0.0040471008978784084 0.056542631238698959 -0.02915031835436821 
		0;
createNode animCurveTL -n "rat_FKRump_R_translateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -0.064884977176051031 1 0.0058881320888014366 
		2 -0.003032781490295693 3 0.15331766967474761 4 0.12881319313809292 5 -0.083199308626682511 
		6 -0.064884977176051031;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  -0.051462102681398392 0.070773109793663025 
		-0.0089209135621786118 0.15635044872760773 -0.02450447715818882 -0.21201249957084656 
		0.018314331769943237;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0.070773109793663025 -0.0089209135621786118 
		0.15635044872760773 -0.02450447715818882 -0.21201249957084656 0.018314331769943237 
		0;
createNode animCurveTL -n "rat_FKRump_R_translateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -0.14578222742399807 1 -0.12875133636361474 
		2 -0.15311328119686823 3 -0.14193192557219403 4 -0.10520578586028133 5 -0.19890714703092585 
		6 -0.14578222742399807;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  -0.077774420380592346 0.01703089103102684 
		-0.024361945688724518 0.011181355454027653 0.036726139485836029 -0.093701362609863281 
		0.053124919533729553;
	setAttr -s 7 ".kox[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333331346511841 0.033333338797092438 0.033333331346511841 0.033333331346511841 
		1;
	setAttr -s 7 ".koy[0:6]"  0.01703089103102684 -0.024361945688724518 
		0.011181355454027653 0.036726139485836029 -0.093701362609863281 0.053124919533729553 
		0;
createNode animCurveTU -n "rat_FKScapula_L_scaleZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999967 1 0.99999999999999967 
		2 0.99999999999999967 3 0.99999999999999967 4 0.99999999999999967 5 0.99999999999999967 
		6 0.99999999999999967;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0 0.033333335071802139 0.033333331346511841 
		0.033333338797092438 0.033333331346511841 0.033333331346511841 0;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_FKScapula_L_scaleY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999989 1 0.99999999999999989 
		2 0.99999999999999989 3 0.99999999999999989 4 0.99999999999999989 5 0.99999999999999989 
		6 0.99999999999999989;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0 0.033333335071802139 0.033333331346511841 
		0.033333338797092438 0.033333331346511841 0.033333331346511841 0;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_FKScapula_L_scaleX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999956 1 0.99999999999999956 
		2 0.99999999999999956 3 0.99999999999999956 4 0.99999999999999956 5 0.99999999999999956 
		6 0.99999999999999956;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0 0.033333335071802139 0.033333331346511841 
		0.033333338797092438 0.033333331346511841 0.033333331346511841 0;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "rat_FKScapula_L_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0 0.033333335071802139 0.033333331346511841 
		0.033333338797092438 0.033333331346511841 0.033333331346511841 0;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "rat_FKScapula_L_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0 0.033333335071802139 0.033333331346511841 
		0.033333338797092438 0.033333331346511841 0.033333331346511841 0;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "rat_FKScapula_L_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0 0.033333335071802139 0.033333331346511841 
		0.033333338797092438 0.033333331346511841 0.033333331346511841 0;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "rat_FKScapula_L_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.0072370711604261371 1 -0.036384099553026537 
		2 0.068407452833559743 3 0.078675244146322529 4 0.0049600216570254872 5 0.025102783051229385 
		6 0.0072370711604261371;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  -0.017865711823105812 -0.04362117126584053 
		0.1047915518283844 0.010267791338264942 -0.073715224862098694 0.020142761990427971 
		-0.017865711823105812;
	setAttr -s 7 ".kox[0:6]"  1 0.033333335071802139 0.033333331346511841 
		0.033333338797092438 0.033333331346511841 0.033333331346511841 1;
	setAttr -s 7 ".koy[0:6]"  0 0.1047915518283844 0.010267791338264942 
		-0.073715224862098694 0.020142761990427971 -0.017865711823105812 0;
createNode animCurveTL -n "rat_FKScapula_L_translateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -0.054942773458866612 1 -0.057683559922815306 
		2 -0.063170871678965596 3 -0.0016281682203108229 4 0.013518266946008986 5 -0.037851087042838752 
		6 -0.054942773458866612;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  -0.017091685906052589 -0.0027407864108681679 
		-0.0054873116314411163 0.061542704701423645 0.015146435238420963 -0.051369354128837585 
		-0.017091685906052589;
	setAttr -s 7 ".kox[0:6]"  1 0.033333335071802139 0.033333331346511841 
		0.033333338797092438 0.033333331346511841 0.033333331346511841 1;
	setAttr -s 7 ".koy[0:6]"  0 -0.0054873116314411163 0.061542704701423645 
		0.015146435238420963 -0.051369354128837585 -0.017091685906052589 0;
createNode animCurveTL -n "rat_FKScapula_L_translateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -0.015277389550237472 1 -0.0077300660129284351 
		2 -0.066566553768078657 3 -0.044532039764196334 4 -0.0096024028027799115 5 -0.021019868979807368 
		6 -0.015277389550237472;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0.0057424795813858509 0.0075473235920071602 
		-0.05883648619055748 0.02203451469540596 0.034929636865854263 -0.011417466215789318 
		0.0057424795813858509;
	setAttr -s 7 ".kox[0:6]"  1 0.033333335071802139 0.033333331346511841 
		0.033333338797092438 0.033333331346511841 0.033333331346511841 1;
	setAttr -s 7 ".koy[0:6]"  0 -0.05883648619055748 0.02203451469540596 
		0.034929636865854263 -0.011417466215789318 0.0057424795813858509 0;
createNode animCurveTU -n "rat_FKScapula_R_scaleZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999933 1 0.99999999999999933 
		2 0.99999999999999933 3 0.99999999999999933 4 0.99999999999999933 5 0.99999999999999933 
		6 0.99999999999999933;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0 0.033333335071802139 0.033333331346511841 
		0.033333338797092438 0.033333331346511841 0.033333331346511841 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_FKScapula_R_scaleY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999933 1 0.99999999999999933 
		2 0.99999999999999933 3 0.99999999999999933 4 0.99999999999999933 5 0.99999999999999933 
		6 0.99999999999999933;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0 0.033333335071802139 0.033333331346511841 
		0.033333338797092438 0.033333331346511841 0.033333331346511841 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "rat_FKScapula_R_scaleX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999956 1 0.99999999999999956 
		2 0.99999999999999956 3 0.99999999999999956 4 0.99999999999999956 5 0.99999999999999956 
		6 0.99999999999999956;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0 0.033333335071802139 0.033333331346511841 
		0.033333338797092438 0.033333331346511841 0.033333331346511841 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "rat_FKScapula_R_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0 0.033333335071802139 0.033333331346511841 
		0.033333338797092438 0.033333331346511841 0.033333331346511841 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "rat_FKScapula_R_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0 0.033333335071802139 0.033333331346511841 
		0.033333338797092438 0.033333331346511841 0.033333331346511841 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "rat_FKScapula_R_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0 0.033333335071802139 0.033333331346511841 
		0.033333338797092438 0.033333331346511841 0.033333331346511841 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "rat_FKScapula_R_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -0.015017141375467146 1 0.027268802423411793 
		2 -0.073891783314737475 3 -0.076033545710855813 4 -0.0050047321040731759 5 -0.031114108802310331 
		6 -0.015017141375467146;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0.016096968203783035 0.042285945266485214 
		-0.10116058588027954 -0.0021417622920125723 0.071028813719749451 -0.026109376922249794 
		0.016096968203783035;
	setAttr -s 7 ".kox[0:6]"  1 0.033333335071802139 0.033333331346511841 
		0.033333338797092438 0.033333331346511841 0.033333331346511841 1;
	setAttr -s 7 ".koy[0:6]"  0 -0.10116058588027954 -0.0021417622920125723 
		0.071028813719749451 -0.026109376922249794 0.016096968203783035 0;
createNode animCurveTL -n "rat_FKScapula_R_translateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.051588300105194662 1 0.013434771960190918 
		2 0.042942903476512487 3 -0.016293377004933739 4 -0.015793884283777791 5 0.032144352311986611 
		6 0.051588300105194662;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  0.019443947821855545 -0.038153529167175293 
		0.029508130624890327 -0.059236280620098114 0.00049949274398386478 0.047938235104084015 
		0.019443947821855545;
	setAttr -s 7 ".kox[0:6]"  1 0.033333335071802139 0.033333331346511841 
		0.033333338797092438 0.033333331346511841 0.033333331346511841 1;
	setAttr -s 7 ".koy[0:6]"  0 0.029508130624890327 -0.059236280620098114 
		0.00049949274398386478 0.047938235104084015 0.019443947821855545 0;
createNode animCurveTL -n "rat_FKScapula_R_translateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.018770653916283717 1 0.0030595955694168991 
		2 0.078325842682701804 3 0.046723795637149373 4 0.0069714888298215722 5 0.022918209418731589 
		6 0.018770653916283717;
	setAttr -s 7 ".kit[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 2 2 2;
	setAttr -s 7 ".kix[0:6]"  0.033333331346511841 0.033333335071802139 
		0.033333335071802139 0.033333331346511841 0.033333338797092438 0.033333331346511841 
		0.033333331346511841;
	setAttr -s 7 ".kiy[0:6]"  -0.0041475556790828705 -0.015711057931184769 
		0.075266249477863312 -0.031602047383785248 -0.039752308279275894 0.015946719795465469 
		-0.0041475556790828705;
	setAttr -s 7 ".kox[0:6]"  1 0.033333335071802139 0.033333331346511841 
		0.033333338797092438 0.033333331346511841 0.033333331346511841 1;
	setAttr -s 7 ".koy[0:6]"  0 0.075266249477863312 -0.031602047383785248 
		-0.039752308279275894 0.015946719795465469 -0.0041475556790828705 0;
createNode animCurveTA -n "rat_sharf_L_C_CTRL_rotateZ1";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  0 5.0116904554907107 1 11.467125534141196 
		4 -13.429226739602319 6 5.0125089849007241;
	setAttr -s 4 ".kit[0:3]"  9 3 3 1;
	setAttr -s 4 ".kot[0:3]"  9 3 3 1;
	setAttr -s 4 ".kix[3]"  0.064638338983058929;
	setAttr -s 4 ".kiy[3]"  0.51652336120605469;
	setAttr -s 4 ".kox[3]"  0.064638331532478333;
	setAttr -s 4 ".koy[3]"  0.51652336120605469;
createNode animCurveTA -n "rat_sharf_L_C_CTRL_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 6.1398869867660775 1 8.6144270911844671 
		2 -2.0063283575260979 3 -22.929385755724859 4 -27.064264764224522 5 -6.9048129619643142 
		6 6.1398251717031096;
createNode animCurveTA -n "rat_sharf_L_C_CTRL_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 14.756095213388454 1 14.756095213388454 
		2 14.756095213388454 6 14.756095213388454;
	setAttr -s 4 ".kot[1:3]"  1 2 2;
	setAttr -s 4 ".kox[1:3]"  0.033333335071802139 0.13333332538604736 
		1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "rat_sharf_L_B_CTRL_rotateZ1";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  0 8.0353533405430166 3 -5.7959554800766231 
		6 8.0353483151731826;
createNode animCurveTA -n "rat_sharf_L_B_CTRL_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -54.745 1 -38.334784583497544 2 -34.674907637898464 
		3 -34.013464960259761 4 -57.435172697912748 5 -66.139817792835387 6 -54.744523496281658;
createNode animCurveTA -n "rat_sharf_L_B_CTRL_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 14.756095213388454 1 14.756095213388454 
		6 14.756095213388454;
createNode animCurveTA -n "rat_sharf_L_A_CTRL_rotateZ1";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  0 53.27067939918085 2 9.1629443448047425 
		5 72.032509369112518 6 53.27067939918085;
	setAttr -s 4 ".kit[0:3]"  1 3 3 1;
	setAttr -s 4 ".kot[0:3]"  1 3 3 1;
	setAttr -s 4 ".kix[0:3]"  0.058793239295482635 0.066666670143604279 
		0.10000000149011612 0.028265183791518211;
	setAttr -s 4 ".kiy[0:3]"  -0.930461585521698 0 0 -0.43994122743606567;
	setAttr -s 4 ".kox[0:3]"  0.058793246746063232 0.10000000149011612 
		0.033333331346511841 0.028265181928873062;
	setAttr -s 4 ".koy[0:3]"  -0.93046170473098755 0 0 -0.4399411678314209;
createNode animCurveTA -n "rat_sharf_L_A_CTRL_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 59.410599077266141 1 41.081854742338436 
		2 33.453467612687817 3 53.920821637860435 4 88.098010478017869 5 85.492719765129038 
		6 59.410599077266141;
createNode animCurveTA -n "rat_sharf_L_A_CTRL_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 -21.166475528470833 5 -21.166475528470833 
		6 -21.166475528470833;
createNode animCurveTA -n "rat_sharf_R_C_CTRL_rotateZ1";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  0 5.0116904554907107 1 11.467125534141196 
		4 -13.429226739602319 6 5.0125089849007241;
	setAttr -s 4 ".kit[0:3]"  9 3 3 1;
	setAttr -s 4 ".kot[0:3]"  9 3 3 1;
	setAttr -s 4 ".kix[3]"  0.064638338983058929;
	setAttr -s 4 ".kiy[3]"  0.51652336120605469;
	setAttr -s 4 ".kox[3]"  0.064638331532478333;
	setAttr -s 4 ".koy[3]"  0.51652336120605469;
createNode animCurveTA -n "rat_sharf_R_C_CTRL_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -5.7746620733580389 1 17.725552843044095 
		2 7.1047973943335059 3 -17.322539139195857 4 -27.064264764224522 5 -13.913371232625554 
		6 -5.7747238884210077;
createNode animCurveTA -n "rat_sharf_R_C_CTRL_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 14.756095213388454 1 14.756095213388454 
		2 14.756095213388454 6 14.756095213388454;
	setAttr -s 4 ".kot[1:3]"  1 2 2;
	setAttr -s 4 ".kox[1:3]"  0.033333335071802139 0.13333332538604736 
		1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTA -n "rat_sharf_R_B_CTRL_rotateZ1";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  0 8.0353533405430166 3 -5.7959554800766231 
		6 8.0353483151731826;
createNode animCurveTA -n "rat_sharf_R_B_CTRL_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -87.56885553826568 1 -80.110600723108405 
		2 -53.303202226994856 3 -30.339641475835776 4 -62.651095182859706 5 -78.807058436130887 
		6 -87.568379034547334;
createNode animCurveTA -n "rat_sharf_R_B_CTRL_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 14.756095213388454 1 14.756095213388454 
		6 14.756095213388454;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[0:2]"  1 2 2;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[0:2]"  0.033333335071802139 0.1666666716337204 
		1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode animCurveTA -n "rat_sharf_R_A_CTRL_rotateZ1";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  0 53.27067939918085 2 9.1629443448047425 
		5 72.032509369112518 6 53.27067939918085;
	setAttr -s 4 ".kit[0:3]"  1 3 3 1;
	setAttr -s 4 ".kot[0:3]"  1 3 3 1;
	setAttr -s 4 ".kix[0:3]"  0.058793239295482635 0.066666670143604279 
		0.10000000149011612 0.028265183791518211;
	setAttr -s 4 ".kiy[0:3]"  -0.930461585521698 0 0 -0.43994122743606567;
	setAttr -s 4 ".kox[0:3]"  0.058793246746063232 0.10000000149011612 
		0.033333331346511841 0.028265181928873062;
	setAttr -s 4 ".koy[0:3]"  -0.93046170473098755 0 0 -0.4399411678314209;
createNode animCurveTA -n "rat_sharf_R_A_CTRL_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 88.098 1 84.23171600500865 2 59.410599077266141 
		3 50.780949695849351 4 70.094492992617916 5 83.018106498393195 6 88.098010478017869;
createNode animCurveTA -n "rat_sharf_R_A_CTRL_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 -21.166475528470833 5 -21.166475528470833 
		6 -21.166475528470833;
createNode animCurveTA -n "rat_us_L_CTRL_rotateZ1";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  0 15.825929173790309 1 14.466504670069826 
		3 20.319131987215144 6 15.825929173790309;
	setAttr -s 4 ".kit[0:3]"  1 3 3 1;
	setAttr -s 4 ".kot[0:3]"  1 3 3 1;
	setAttr -s 4 ".kix[0:3]"  0.028465684503316879 0.033333335071802139 
		0.066666662693023682 0.028839204460382462;
	setAttr -s 4 ".kiy[0:3]"  -0.035829443484544754 0 0 -0.03181123360991478;
	setAttr -s 4 ".kox[0:3]"  0.028465684503316879 0.066666662693023682 
		0.10000000149011612 0.028839204460382462;
	setAttr -s 4 ".koy[0:3]"  -0.035829447209835052 0 0 -0.031811222434043884;
createNode animCurveTA -n "rat_us_L_CTRL_rotateY1";
	setAttr ".tan" 3;
	setAttr -s 5 ".ktv[0:4]"  0 -2.1217802425818335 1 -15.090765761091983 
		3 -42.550415748312737 5 5.8047740534361383 6 -2.1217802425818335;
	setAttr -s 5 ".kit[0:4]"  9 1 3 3 1;
	setAttr -s 5 ".kot[0:4]"  9 1 3 3 1;
	setAttr -s 5 ".kix[1:4]"  0.031524516642093658 0.066666662693023682 
		0.066666670143604279 0.031986862421035767;
	setAttr -s 5 ".kiy[1:4]"  -0.26153728365898132 0 0 -0.18309919536113739;
	setAttr -s 5 ".kox[1:4]"  0.064857251942157745 0.066666670143604279 
		0.033333331346511841 0.031986858695745468;
	setAttr -s 5 ".koy[1:4]"  -0.53807598352432251 0 0 -0.1830991804599762;
createNode animCurveTA -n "rat_us_L_CTRL_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 -1.0000548989993181 1 -1.0024991662648155 
		5 -1.0040014174608893 6 -1.0000548989993181;
createNode animCurveTA -n "rat_us_R_CTRL_rotateZ1";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  0 15.825929173790309 1 14.466504670069826 
		3 20.319131987215144 6 15.825929173790309;
	setAttr -s 4 ".kit[0:3]"  1 3 3 1;
	setAttr -s 4 ".kot[0:3]"  1 3 3 1;
	setAttr -s 4 ".kix[0:3]"  0.028465684503316879 0.033333335071802139 
		0.066666662693023682 0.028839204460382462;
	setAttr -s 4 ".kiy[0:3]"  -0.035829443484544754 0 0 -0.03181123360991478;
	setAttr -s 4 ".kox[0:3]"  0.028465684503316879 0.066666662693023682 
		0.10000000149011612 0.028839204460382462;
	setAttr -s 4 ".koy[0:3]"  -0.035829447209835052 0 0 -0.031811222434043884;
createNode animCurveTA -n "rat_us_R_CTRL_rotateY1";
	setAttr ".tan" 3;
	setAttr -s 5 ".ktv[0:4]"  0 -2.1217802425818335 1 -15.090765761091983 
		3 -42.550415748312737 5 5.8047740534361383 6 -2.1217802425818335;
	setAttr -s 5 ".kit[0:4]"  9 1 3 3 1;
	setAttr -s 5 ".kot[0:4]"  9 1 3 3 1;
	setAttr -s 5 ".kix[1:4]"  0.031524516642093658 0.066666662693023682 
		0.066666670143604279 0.031986862421035767;
	setAttr -s 5 ".kiy[1:4]"  -0.26153728365898132 0 0 -0.18309919536113739;
	setAttr -s 5 ".kox[1:4]"  0.064857251942157745 0.066666670143604279 
		0.033333331346511841 0.031986858695745468;
	setAttr -s 5 ".koy[1:4]"  -0.53807598352432251 0 0 -0.1830991804599762;
createNode animCurveTA -n "rat_us_R_CTRL_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 -1.0000548989993181 1 -1.0024991662648155 
		5 -1.0040014174608893 6 -1.0000548989993181;
createNode animCurveTU -n "rat_FKEar_L_scaleZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 1 0.99999999999999978 
		2 0.99999999999999978 3 0.99999999999999978 4 0.99999999999999978 5 0.99999999999999978 
		6 0.99999999999999978;
createNode animCurveTU -n "rat_FKEar_L_scaleY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 1 0.99999999999999978 
		2 0.99999999999999978 3 0.99999999999999978 4 0.99999999999999978 5 0.99999999999999978 
		6 0.99999999999999978;
createNode animCurveTU -n "rat_FKEar_L_scaleX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1 1 1 2 1 3 1 4 1 5 1 6 1;
createNode animCurveTA -n "rat_FKEar_L_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_FKEar_L_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_FKEar_L_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTU -n "rat_FKEar_R_scaleZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999989 1 0.99999999999999989 
		2 0.99999999999999989 3 0.99999999999999989 4 0.99999999999999989 5 0.99999999999999989 
		6 0.99999999999999989;
createNode animCurveTU -n "rat_FKEar_R_scaleY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1 1 1 2 1 3 1 4 1 5 1 6 1;
createNode animCurveTU -n "rat_FKEar_R_scaleX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999989 1 0.99999999999999989 
		2 0.99999999999999989 3 0.99999999999999989 4 0.99999999999999989 5 0.99999999999999989 
		6 0.99999999999999989;
createNode animCurveTA -n "rat_FKEar_R_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_FKEar_R_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_FKEar_R_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_hair_CTRL_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_hair_CTRL_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_hair_CTRL_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTL -n "rat_hair_CTRL_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTL -n "rat_hair_CTRL_translateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTL -n "rat_hair_CTRL_translateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTU -n "rat_FKJaw_M_scaleZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 1 0.99999999999999978 
		2 0.99999999999999978 3 0.99999999999999978 4 0.99999999999999978 5 0.99999999999999978 
		6 0.99999999999999978;
createNode animCurveTU -n "rat_FKJaw_M_scaleY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999989 1 0.99999999999999989 
		2 0.99999999999999989 3 0.99999999999999989 4 0.99999999999999989 5 0.99999999999999989 
		6 0.99999999999999989;
createNode animCurveTU -n "rat_FKJaw_M_scaleX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1.0000000000000002 1 1.0000000000000002 
		2 1.0000000000000002 3 1.0000000000000002 4 1.0000000000000002 5 1.0000000000000002 
		6 1.0000000000000002;
createNode animCurveTA -n "rat_FKJaw_M_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_FKJaw_M_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_FKJaw_M_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTL -n "rat_FKJaw_M_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTL -n "rat_FKJaw_M_translateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTL -n "rat_FKJaw_M_translateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTU -n "rat_FKHead_M_Global1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 10 1 10 2 10 3 10 4 10 5 10 6 10;
createNode animCurveTU -n "rat_FKHead_M_scaleZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999989 1 0.99999999999999989 
		2 0.99999999999999989 3 0.99999999999999989 4 0.99999999999999989 5 0.99999999999999989 
		6 0.99999999999999989;
createNode animCurveTU -n "rat_FKHead_M_scaleY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1 1 1 2 1 3 1 4 1 5 1 6 1;
createNode animCurveTU -n "rat_FKHead_M_scaleX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 1 1 1 2 1 3 1 4 1 5 1 6 1;
createNode animCurveTA -n "rat_FKHead_M_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 29.655407610645099 1 36.091098756891874 
		2 39.88640450169099 3 34.538248600835104 4 18.227216306816405 5 18.467397638912001 
		6 29.655407610645099;
createNode animCurveTA -n "rat_FKHead_M_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 2.1992544839601145 1 -0.061110637408422305 
		2 -1.6580294782488869 3 -0.7194023502190392 4 3.1099939330920665 5 3.5214247452568141 
		6 2.1992544839601145;
createNode animCurveTA -n "rat_FKHead_M_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -1.3892891554913034 1 1.4177964070334377 
		2 0.75775480578671706 3 0.24877937222639335 4 0.14302373760464318 5 -2.8396595575929089 
		6 -1.3892891554913034;
createNode animCurveTL -n "rat_FKHead_M_translateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0.0018497590503185944 2 -0.00049144506801815705 
		3 0.0010023835500856963 4 0 5 0 6 0;
createNode animCurveTL -n "rat_FKHead_M_translateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0.021065523304394658 2 -0.011223769261817706 
		3 0.0021662822473130935 4 0 5 0 6 0;
createNode animCurveTL -n "rat_FKHead_M_translateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0.00027541059060214469 2 -0.026054600404319769 
		3 -0.035935195423956193 4 0 5 0 6 0;
createNode animCurveTU -n "rat_FKNeck_M_scaleZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999967 1 0.99999999999999967 
		2 0.99999999999999967 3 0.99999999999999967 4 0.99999999999999967 5 0.99999999999999967 
		6 0.99999999999999967;
createNode animCurveTU -n "rat_FKNeck_M_scaleY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999933 1 0.99999999999999933 
		2 0.99999999999999933 3 0.99999999999999933 4 0.99999999999999933 5 0.99999999999999933 
		6 0.99999999999999933;
createNode animCurveTU -n "rat_FKNeck_M_scaleX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 1 0.99999999999999978 
		2 0.99999999999999978 3 0.99999999999999978 4 0.99999999999999978 5 0.99999999999999978 
		6 0.99999999999999978;
createNode animCurveTA -n "rat_FKNeck_M_rotateZ1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_FKNeck_M_rotateY1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTA -n "rat_FKNeck_M_rotateX1";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 2 0 3 0 4 0 5 0 6 0;
createNode animCurveTU -n "rat_Main_scaleZ1";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "rat_Main_scaleY1";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "rat_Main_scaleX1";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "rat_Main_rotateZ1";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "rat_Main_rotateY1";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "rat_Main_rotateX1";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "rat_Main_translateZ1";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "rat_Main_translateY1";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "rat_Main_translateX1";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "rat_Main_visibility1";
	setAttr ".tan" 9;
	setAttr ".ktv[0]"  0 1;
	setAttr ".kot[0]"  5;
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
select -ne :defaultRenderGlobals;
	setAttr ".mcfr" 30;
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
	setAttr -s 3 ".sol";
connectAttr "moveSource.cl" "clipLibrary1.sc[0]";
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
// End of move.ma
