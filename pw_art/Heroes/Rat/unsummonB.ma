//Maya ASCII 2008 scene
//Name: unsummonB.ma
//Last modified: Mon, Feb 01, 2010 09:06:23 PM
//Codeset: 1251
requires maya "2008";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Complete 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200802250025-718075";
fileInfo "osv" "Microsoft Windows XP Service Pack 3 (Build 2600)\n";
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
createNode animClip -n "clip00Source";
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
	setAttr ".se" 10;
	setAttr ".ci" no;
createNode animCurveTU -n "animCurveTU1049";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10 3 10 4.5 10 6 10 7.5 10 9 10 10 10;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1341";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1342";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1343";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL697";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL698";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL699";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1050";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 4.5 1 6 1 7.5 1 9 1 10 1;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1051";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 4.5 1 6 1 7.5 1 9 1 10 1;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1052";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 4.5 1 6 1 7.5 1 9 1 10 1;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1053";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1344";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1345";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1346";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1054";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 4.5 1 6 1 7.5 1 9 1 10 1;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1055";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1056";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10 3 10 4.5 10 6 10 7.5 10 9 10 10 10;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1057";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 4.5 1 6 1 7.5 1 9 1 10 1;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1058";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1059";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10 3 10 4.5 10 6 10 7.5 10 9 10 10 10;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1060";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 4.5 1 6 1 7.5 1 9 1 10 1;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1061";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1062";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1063";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 4.5 1 6 1 7.5 1 9 1 10 1;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1064";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1065";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10 3 10 4.5 10 6 10 7.5 10 9 10 10 10;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1066";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 4.5 1 6 1 7.5 1 9 1 10 1;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1067";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1068";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10 3 10 4.5 10 6 10 7.5 10 9 10 10 10;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1069";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 4.5 1 6 1 7.5 1 9 1 10 1;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1070";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1071";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10 3 10 4.5 10 6 10 7.5 10 9 10 10 10;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1072";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10 3 10 4.5 10 6 10 7.5 10 9 10 10 10;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL700";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.0051987098671592413 9 0.0051987098671592413 
		10 0.0051987098671592413;
	setAttr -s 3 ".kix[0:2]"  1 1 1;
	setAttr -s 3 ".kiy[0:2]"  0 0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode animCurveTL -n "animCurveTL701";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.0029658564141476066 9 -0.0029658564141476066 
		10 -0.0029658564141476066;
	setAttr -s 3 ".kix[0:2]"  1 1 1;
	setAttr -s 3 ".kiy[0:2]"  0 0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode animCurveTL -n "animCurveTL702";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.088864011310046689 4.5 -0.088864011310046689 
		7.5 0.13936607757462444 9 0.13053956191308774 10 0.13053956191308774;
	setAttr -s 5 ".kit[0:4]"  3 3 1 1 1;
	setAttr -s 5 ".kot[1:4]"  3 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 0.94934725761413574 0.94934725761413574;
	setAttr -s 5 ".kiy[2:4]"  0 -0.31422892212867737 -0.31422892212867737;
	setAttr -s 5 ".kox[0:4]"  1 1 1 0.94934737682342529 0.94934737682342529;
	setAttr -s 5 ".koy[0:4]"  0 0 0 -0.31422856450080872 -0.31422856450080872;
createNode animCurveTA -n "animCurveTA1347";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 -67.42563633242807 7.5 
		0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 3 3 3 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1348";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1349";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1350";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1073";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 4.5 1 6 1 7.5 1 9 1 10 1;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1074";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 4.5 1 6 1 7.5 1 9 1 10 1;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1075";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1076";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1077";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10 3 10 4.5 10 6 10 7.5 10 9 10 10 10;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1078";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 30 3 30 4.5 30 6 30 7.5 30 9 30 10 30;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1079";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1080";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1351";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10.65881532857289 3 10.65881532857289 
		4.5 10.65881532857289 6 10.57211623849588 7.5 10.532593162695148 9 9.8769430688483109 
		10 9.8769430688483109;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.99990487098693848 0.97479617595672607 
		0.97479617595672607;
	setAttr -s 7 ".kiy[4:6]"  -0.013794844970107079 -0.22309714555740356 
		-0.22309714555740356;
	setAttr -s 7 ".kox[0:6]"  1 1 0.99954235553741455 0.99990487098693848 
		0.9747963547706604 0.97479629516601563 0.97479629516601563;
	setAttr -s 7 ".koy[0:6]"  0 0 -0.030249845236539841 -0.013794844970107079 
		-0.22309668362140656 -0.22309693694114685 -0.22309693694114685;
createNode animCurveTA -n "animCurveTA1352";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 -1.3645079130196978 7.5 
		1.6448009331432116 9 3.5069663653145491 10 3.5069663653145491;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.68950122594833374 0.8384365439414978 
		0.8384365439414978;
	setAttr -s 7 ".kiy[4:6]"  0.72428452968597412 0.54499918222427368 
		0.54499918222427368;
	setAttr -s 7 ".kox[0:6]"  1 1 0.90282100439071655 0.68950122594833374 
		0.8384365439414978 0.8384365439414978 0.8384365439414978;
	setAttr -s 7 ".koy[0:6]"  0 0 -0.43001645803451538 0.72428452968597412 
		0.54499918222427368 0.54499918222427368 0.54499918222427368;
createNode animCurveTA -n "animCurveTA1353";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 7.3971380101551016 7.5 
		51.642781722008131 9 40.910919536786942 10 40.910919536786942;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.064612068235874176 0.25791123509407043 
		0.25791123509407043;
	setAttr -s 7 ".kiy[4:6]"  0.99791043996810913 -0.96616858243942261 
		-0.96616858243942261;
	setAttr -s 7 ".kox[0:6]"  1 1 0.36114543676376343 0.064612068235874176 
		0.25791144371032715 0.25791138410568237 0.25791138410568237;
	setAttr -s 7 ".koy[0:6]"  0 0 0.93250948190689087 0.99791043996810913 
		-0.96616858243942261 -0.96616858243942261 -0.96616858243942261;
createNode animCurveTL -n "animCurveTL703";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0.20070987294766468 7.5 
		1.6416955953564867 9 2.0289557135430516 10 2.0289557135430516;
	setAttr -s 7 ".kit[0:6]"  9 9 3 1 1 1 1;
	setAttr -s 7 ".kot[1:6]"  9 3 1 1 1 1;
	setAttr -s 7 ".kix[3:6]"  0.085159353911876678 0.076753780245780945 
		0.23203712701797485 0.23203712701797485;
	setAttr -s 7 ".kiy[3:6]"  0.99636733531951904 0.99705010652542114 
		0.97270691394805908 0.97270691394805908;
	setAttr -s 7 ".kox[0:6]"  1 1 1 0.085159339010715485 0.07675374299287796 
		0.23203708231449127 0.23203708231449127;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0.99636733531951904 0.99705010652542114 
		0.97270697355270386 0.97270697355270386;
createNode animCurveTL -n "animCurveTL704";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.055827347319821544 4.5 -0.055827347319821544 
		6 -0.24720076965759646 7.5 -0.71400936252256242 9 -0.94867393676623224 10 -0.94867393676623224;
	setAttr -s 6 ".kit[0:5]"  9 3 9 1 1 1;
	setAttr -s 6 ".kot[1:5]"  3 9 1 1 1;
	setAttr -s 6 ".kix[3:5]"  0.17007406055927277 0.26301798224449158 
		0.26301798224449158;
	setAttr -s 6 ".kiy[3:5]"  -0.98543131351470947 -0.964790940284729 
		-0.964790940284729;
	setAttr -s 6 ".kox[0:5]"  1 1 0.15020982921123505 0.17007400095462799 
		0.26301771402359009 0.26301771402359009;
	setAttr -s 6 ".koy[0:5]"  0 0 -0.98865413665771484 -0.98543131351470947 
		-0.96479099988937378 -0.96479099988937378;
createNode animCurveTL -n "animCurveTL705";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.057269223867906088 3 -0.057269223867906088 
		4.5 -0.057269223867906088 6 -0.1251307590242198 7.5 -0.19022759748187021 9 -0.2174131627177763 
		10 -0.2174131627177763;
	setAttr -s 7 ".kit[0:6]"  9 3 3 1 1 1 1;
	setAttr -s 7 ".kot[1:6]"  3 3 1 1 1 1;
	setAttr -s 7 ".kix[3:6]"  0.48905870318412781 0.80227714776992798 
		0.94323766231536865 0.94323766231536865;
	setAttr -s 7 ".kiy[3:6]"  -0.87225085496902466 -0.59695172309875488 
		-0.33211866021156311 -0.33211866021156311;
	setAttr -s 7 ".kox[0:6]"  1 1 1 0.48905858397483826 0.80227738618850708 
		0.94323772192001343 0.94323772192001343;
	setAttr -s 7 ".koy[0:6]"  0 0 0 -0.87225091457366943 -0.59695142507553101 
		-0.33211836218833923 -0.33211836218833923;
createNode animCurveTU -n "animCurveTU1081";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10 3 10 4.5 10 6 10 7.5 10 9 10 10 10;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL706";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.0086735638741271305 3 -0.0086735638741271305 
		4.5 0.00078745538975081675 6 -0.12054138075917435 7.5 -0.069888881546967693 9 -0.081369782510297986 
		10 -0.081369782510297986;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.70250809192657471 0.9746364951133728 
		0.9746364951133728;
	setAttr -s 7 ".kiy[4:6]"  0.71167582273483276 -0.22379390895366669 
		-0.22379390895366669;
	setAttr -s 7 ".kox[0:6]"  1 0.98256462812423706 0.38101735711097717 
		0.70250809192657471 0.97463643550872803 0.97463643550872803 0.97463643550872803;
	setAttr -s 7 ".koy[0:6]"  0 0.18592123687267303 -0.92456787824630737 
		0.71167582273483276 -0.22379423677921295 -0.22379410266876221 -0.22379410266876221;
createNode animCurveTL -n "animCurveTL707";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.0097724910328683117 3 0.0097724910328683117 
		4.5 0.037891044928013477 6 -0.48970795961251123 7.5 -0.65088171677159834 9 -0.65629119306873018 
		10 -0.65629119306873018;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.29629409313201904 0.99419832229614258 
		0.99419832229614258;
	setAttr -s 7 ".kiy[4:6]"  -0.95509672164916992 -0.10756228119134903 
		-0.10756228119134903;
	setAttr -s 7 ".kox[0:6]"  1 0.87162357568740845 0.094346225261688232 
		0.29629409313201904 0.99419838190078735 0.99419844150543213 0.99419844150543213;
	setAttr -s 7 ".koy[0:6]"  0 0.49017584323883057 -0.99553948640823364 
		-0.95509672164916992 -0.1075613722205162 -0.1075618714094162 -0.1075618714094162;
createNode animCurveTL -n "animCurveTL708";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.096690034935401112 3 0.096690034935401112 
		4.5 0.28128625219035092 6 0.46794941298598824 7.5 0.624754248537843 9 0.61338999226850066 
		10 0.61338999226850066;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.30379700660705566 0.97513014078140259 
		0.97513014078140259;
	setAttr -s 7 ".kiy[4:6]"  0.95273679494857788 -0.22163285315036774 
		-0.22163285315036774;
	setAttr -s 7 ".kox[0:6]"  1 0.26144078373908997 0.25874060392379761 
		0.30379700660705566 0.97512990236282349 0.97513025999069214 0.97513025999069214;
	setAttr -s 7 ".koy[0:6]"  0 0.96521949768066406 0.96594685316085815 
		0.95273679494857788 -0.22163408994674683 -0.2216324508190155 -0.2216324508190155;
createNode animCurveTA -n "animCurveTA1354";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 3 3 3 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1355";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1356";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 3.9756933518293979e-016 3 0 4.5 3.9756933518293979e-016 
		6 3.9756933518293979e-016 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1357";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1082";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 4.5 1 6 1 7.5 1 9 1 10 1;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1083";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 4.5 1 6 1 7.5 1 9 1 10 1;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1084";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1085";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1086";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10 3 10 4.5 10 6 10 7.5 10 9 10 10 10;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1087";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 25 3 25 4.5 25 6 25 7.5 25 9 25 10 25;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1088";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1089";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1358";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -8.5560819804359109 3 -8.5560819804359109 
		4.5 -8.1330312550227344 6 -19.972584811533423 7.5 -6.0000000000000009 9 -6.0000000000000009 
		10 -6.0000000000000009;
	setAttr -s 7 ".kit[0:6]"  9 3 3 3 1 1 1;
	setAttr -s 7 ".kot[1:6]"  3 3 3 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1359";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.31694341854885294 3 -0.31694341854885294 
		4.5 2.6848714312750235 6 90.875687714895989 7.5 87.859094226536513 9 87.859092972395544 
		10 87.859092972395544;
	setAttr -s 7 ".kit[0:6]"  3 3 1 3 1 1 1;
	setAttr -s 7 ".kot[1:6]"  3 1 3 1 1 1;
	setAttr -s 7 ".kix[2:6]"  0.31163319945335388 1 1 1 1;
	setAttr -s 7 ".kiy[2:6]"  0.95020240545272827 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 0.31163319945335388 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0.95020252466201782 0 0 0 0;
createNode animCurveTA -n "animCurveTA1360";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.51931341167670197 3 -0.51931341167670197 
		4.5 34.228713973191695 6 -28.360674735783309 7.5 2.0038969302325578 9 2.0038969302325578 
		10 2.0038969302325578;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 3 3 3 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL709";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.00076651281650793874 3 0.00076651281650793874 
		4.5 0.066724881900981969 6 1.7105289321104409 7.5 2.7485989567659326 9 2.8108373069646975 
		10 2.8108373069646975;
	setAttr -s 7 ".kit[0:6]"  3 3 1 1 1 1 1;
	setAttr -s 7 ".kot[1:6]"  3 1 1 1 1 1;
	setAttr -s 7 ".kix[2:6]"  0.21127822995185852 0.030087631195783615 
		0.39159411191940308 0.84140127897262573 0.84140127897262573;
	setAttr -s 7 ".kiy[2:6]"  0.97742593288421631 0.99954724311828613 
		0.92013806104660034 0.54041075706481934 0.54041075706481934;
	setAttr -s 7 ".kox[0:6]"  1 1 0.21127821505069733 0.030087621882557869 
		0.39159411191940308 0.84140115976333618 0.84140115976333618;
	setAttr -s 7 ".koy[0:6]"  0 0 0.97742593288421631 0.99954724311828613 
		0.92013812065124512 0.54041093587875366 0.54041093587875366;
createNode animCurveTL -n "animCurveTL710";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.27472958484748605 3 0.27472958484748605 
		4.5 0.21856929524583127 6 -0.47568651224625103 7.5 -0.91456660325909456 9 -0.92961907444774849 
		10 -0.92961907444774849;
	setAttr -s 7 ".kit[0:6]"  3 3 1 1 1 1 1;
	setAttr -s 7 ".kot[1:6]"  3 1 1 1 1 1;
	setAttr -s 7 ".kix[2:6]"  0.27231359481811523 0.070196539163589478 
		0.75885111093521118 0.99802166223526001 0.99802166223526001;
	setAttr -s 7 ".kiy[2:6]"  -0.96220856904983521 -0.99753314256668091 
		-0.65126407146453857 -0.062870688736438751 -0.062870688736438751;
	setAttr -s 7 ".kox[0:6]"  1 1 0.27231359481811523 0.070196524262428284 
		0.75885117053985596 0.99802166223526001 0.99802166223526001;
	setAttr -s 7 ".koy[0:6]"  0 0 -0.96220856904983521 -0.99753314256668091 
		-0.65126413106918335 -0.062870681285858154 -0.062870681285858154;
createNode animCurveTL -n "animCurveTL711";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.071005957816697135 3 -0.071005957816697135 
		4.5 -0.071005957816697135 6 0.20352880426187342 7.5 -0.10641419568342655 9 -0.10641419568342655 
		10 -0.10641419568342655;
	setAttr -s 7 ".kit[0:6]"  9 3 3 3 1 1 1;
	setAttr -s 7 ".kot[1:6]"  3 3 3 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1090";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10 3 10 4.5 10 6 10 7.5 10 9 10 10 10;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL712";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.0054999194138878266 7.5 0.025287625120427822 
		9 0.026132890332845219 10 0.026132890332845219;
	setAttr -s 4 ".kit[0:3]"  2 1 1 1;
	setAttr -s 4 ".kix[1:3]"  0.99688231945037842 0.99985712766647339 
		0.99985712766647339;
	setAttr -s 4 ".kiy[1:3]"  0.078904055058956146 0.016902841627597809 
		0.016902841627597809;
	setAttr -s 4 ".kox[0:3]"  0.99688231945037842 0.99985712766647339 
		0.99985712766647339 0.99985712766647339;
	setAttr -s 4 ".koy[0:3]"  0.078904055058956146 0.01690283790230751 
		0.016902880743145943 0.016902880743145943;
createNode animCurveTL -n "animCurveTL713";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -0.0031376960222415048 7.5 -0.088351817436808269 
		9 -0.089123687111426986 10 -0.089123687111426986;
	setAttr -s 4 ".kit[0:3]"  2 1 1 1;
	setAttr -s 4 ".kix[1:3]"  0.94652539491653442 0.99988085031509399 
		0.99988085031509399;
	setAttr -s 4 ".kiy[1:3]"  -0.32262933254241943 -0.015435525216162205 
		-0.015435525216162205;
	setAttr -s 4 ".kox[0:3]"  0.94652539491653442 0.99988085031509399 
		0.99988090991973877 0.99988090991973877;
	setAttr -s 4 ".koy[0:3]"  -0.32262933254241943 -0.015435526147484779 
		-0.015435562469065189 -0.015435562469065189;
createNode animCurveTL -n "animCurveTL714";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.083911116250119933 3 0.083911116250119933 
		4.5 0.083911116250119933 7.5 -0.36511477763692141 9 -0.39205082314821982 10 -0.39205082314821982;
	setAttr -s 6 ".kit[0:5]"  9 3 3 1 1 1;
	setAttr -s 6 ".kot[1:5]"  3 3 1 1 1;
	setAttr -s 6 ".kix[3:5]"  0.84837967157363892 0.90939140319824219 
		0.90939140319824219;
	setAttr -s 6 ".kiy[3:5]"  -0.52938830852508545 -0.41594138741493225 
		-0.41594138741493225;
	setAttr -s 6 ".kox[0:5]"  1 1 1 0.84837961196899414 0.90939152240753174 
		0.90939152240753174;
	setAttr -s 6 ".koy[0:5]"  0 0 0 -0.529388427734375 -0.41594105958938599 
		-0.41594105958938599;
createNode animCurveTA -n "animCurveTA1361";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 -56.158281016241887 7.5 
		0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 3 3 3 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1362";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1363";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1364";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1091";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 4.5 1 6 1 7.5 1 9 1 10 1;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1092";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 4.5 1 6 1 7.5 1 9 1 10 1;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1093";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1094";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1095";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10 3 10 4.5 10 6 10 7.5 10 9 10 10 10;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1096";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 30 3 30 4.5 30 6 30 7.5 30 9 30 10 30;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1097";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1098";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1365";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -9.8142060506602 3 -9.8142060506602 4.5 
		-9.8142060506602 6 -9.7345174348678807 7.5 -6.0285839154421907 9 -7.2246123030494198 
		10 -7.2246123030494198;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.61159622669219971 0.9228060245513916 
		0.9228060245513916;
	setAttr -s 7 ".kiy[4:6]"  0.79117000102996826 -0.38526487350463867 
		-0.38526487350463867;
	setAttr -s 7 ".kox[0:6]"  1 1 0.99961334466934204 0.61159622669219971 
		0.9228060245513916 0.9228060245513916 0.9228060245513916;
	setAttr -s 7 ".koy[0:6]"  0 0 0.027805820107460022 0.79117000102996826 
		-0.38526484370231628 -0.38526487350463867 -0.38526487350463867;
createNode animCurveTA -n "animCurveTA1366";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 1.2541831870505133 7.5 
		7.7586983242345342 9 6.40897859941151 10 6.40897859941151;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.4030689001083374 0.90462589263916016 
		0.90462589263916016;
	setAttr -s 7 ".kiy[4:6]"  0.91516965627670288 -0.42620658874511719 
		-0.42620658874511719;
	setAttr -s 7 ".kox[0:6]"  1 1 0.91605889797210693 0.4030689001083374 
		0.90462589263916016 0.90462595224380493 0.90462595224380493;
	setAttr -s 7 ".koy[0:6]"  0 0 0.40104374289512634 0.91516965627670288 
		-0.42620652914047241 -0.42620649933815002 -0.42620649933815002;
createNode animCurveTA -n "animCurveTA1367";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 7.3776891349705744 7.5 
		52.373873280641568 9 45.156585461724809 10 45.156585461724809;
	setAttr -s 7 ".kit[0:6]"  9 3 3 1 1 1 1;
	setAttr -s 7 ".kot[1:6]"  3 3 1 1 1 1;
	setAttr -s 7 ".kix[3:6]"  0.13886876404285431 1 0.22463010251522064 
		0.22463010251522064;
	setAttr -s 7 ".kiy[3:6]"  0.99031078815460205 0 -0.97444409132003784 
		-0.97444409132003784;
	setAttr -s 7 ".kox[0:6]"  1 1 1 0.1388687789440155 1 0.22462986409664154 
		0.22462986409664154;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0.99031078815460205 0 -0.97444415092468262 
		-0.97444415092468262;
createNode animCurveTL -n "animCurveTL715";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0.20070987294766462 7.5 
		1.7158056456924935 9 2.1211796166940289 10 2.1211796166940289;
	setAttr -s 7 ".kit[0:6]"  10 10 3 1 1 1 1;
	setAttr -s 7 ".kot[1:6]"  10 3 1 1 1 1;
	setAttr -s 7 ".kix[3:6]"  0.079180613160133362 0.085697785019874573 
		0.20986726880073547 0.20986726880073547;
	setAttr -s 7 ".kiy[3:6]"  0.9968603253364563 0.99632114171981812 
		0.9777299165725708 0.9777299165725708;
	setAttr -s 7 ".kox[0:6]"  1 1 1 0.079180575907230377 0.085697770118713379 
		0.20986767113208771 0.20986767113208771;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0.9968603253364563 0.99632114171981812 
		0.97772979736328125 0.97772979736328125;
createNode animCurveTL -n "animCurveTL716";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.26728461461584108 3 -0.26728461461584108 
		4.5 -0.26728461461584108 6 -0.27652543129177598 7.5 -0.47282600632805738 9 -0.69230242858000002 
		10 -0.69230242858000002;
	setAttr -s 7 ".kit[0:6]"  10 10 10 1 1 1 1;
	setAttr -s 7 ".kot[1:6]"  10 10 1 1 1 1;
	setAttr -s 7 ".kix[3:6]"  0.8863179087638855 0.1966688334941864 0.24982237815856934 
		0.24982237815856934;
	setAttr -s 7 ".kiy[3:6]"  -0.46307718753814697 -0.98047000169754028 
		-0.96829169988632202 -0.96829169988632202;
	setAttr -s 7 ".kox[0:6]"  1 1 1 0.88631802797317505 0.19666872918605804 
		0.24982227385044098 0.24982227385044098;
	setAttr -s 7 ".koy[0:6]"  0 0 0 -0.4630771279335022 -0.98047000169754028 
		-0.96829169988632202 -0.96829169988632202;
createNode animCurveTL -n "animCurveTL717";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.017033828181619803 3 0.017033828181619803 
		4.5 0.017033828181619803 6 0.042647717310292932 7.5 0.063673769289359694 9 0.071258834479131228 
		10 0.071258834479131228;
	setAttr -s 7 ".kit[0:6]"  9 9 3 1 1 1 1;
	setAttr -s 7 ".kot[1:6]"  9 3 1 1 1 1;
	setAttr -s 7 ".kix[3:6]"  0.86496973037719727 0.97802287340164185 
		0.99510574340820313 0.99510574340820313;
	setAttr -s 7 ".kiy[3:6]"  0.50182408094406128 0.20849747955799103 
		0.098816029727458954 0.098816029727458954;
	setAttr -s 7 ".kox[0:6]"  1 1 1 0.86496973037719727 0.97802287340164185 
		0.9951058030128479 0.9951058030128479;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0.5018240213394165 0.20849725604057312 
		0.098815560340881348 0.098815560340881348;
createNode animCurveTU -n "animCurveTU1099";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 4.5 0 9 0 10 0;
	setAttr -s 4 ".kit[0:3]"  2 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[0:3]"  1 1 1 1;
	setAttr -s 4 ".koy[0:3]"  0 0 0 0;
createNode animCurveTU -n "animCurveTU1100";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 4.5 0 9 0 10 0;
	setAttr -s 4 ".kit[0:3]"  2 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[0:3]"  1 1 1 1;
	setAttr -s 4 ".koy[0:3]"  0 0 0 0;
createNode animCurveTU -n "animCurveTU1101";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 4.5 0 9 0 10 0;
	setAttr -s 4 ".kit[0:3]"  2 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[0:3]"  1 1 1 1;
	setAttr -s 4 ".koy[0:3]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1368";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 4.5 0 9 0 10 0;
	setAttr -s 4 ".kit[0:3]"  2 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[0:3]"  1 1 1 1;
	setAttr -s 4 ".koy[0:3]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1369";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 4.5 0 9 0 10 0;
	setAttr -s 4 ".kit[0:3]"  2 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[0:3]"  1 1 1 1;
	setAttr -s 4 ".koy[0:3]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1370";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 4.5 0 9 0 10 0;
	setAttr -s 4 ".kit[0:3]"  2 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[0:3]"  1 1 1 1;
	setAttr -s 4 ".koy[0:3]"  0 0 0 0;
createNode animCurveTL -n "animCurveTL718";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.77177341453224102 4.5 -0.77177341453224102 
		6 -0.73495683909989151 9 -0.13502906424867167 10 -0.13502906424867167;
	setAttr -s 5 ".kit[0:4]"  3 3 1 1 1;
	setAttr -s 5 ".kot[1:4]"  3 1 1 1;
	setAttr -s 5 ".kix[2:4]"  0.40322533249855042 0.15750947594642639 
		0.15750947594642639;
	setAttr -s 5 ".kiy[2:4]"  0.91510075330734253 0.98751741647720337 
		0.98751741647720337;
	setAttr -s 5 ".kox[0:4]"  1 1 0.40322551131248474 0.157509446144104 
		0.157509446144104;
	setAttr -s 5 ".koy[0:4]"  0 0 0.91510063409805298 0.98751747608184814 
		0.98751747608184814;
createNode animCurveTL -n "animCurveTL719";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4.5 0 6 -0.3272133569971965 9 -1.8213682480274525 
		10 -1.8213682480274525;
	setAttr -s 5 ".kit[0:4]"  3 3 1 1 1;
	setAttr -s 5 ".kot[1:4]"  3 1 1 1;
	setAttr -s 5 ".kix[2:4]"  0.082141324877738953 0.06819828599691391 
		0.06819828599691391;
	setAttr -s 5 ".kiy[2:4]"  -0.99662065505981445 -0.99767178297042847 
		-0.99767178297042847;
	setAttr -s 5 ".kox[0:4]"  1 1 0.082141347229480743 0.068198248744010925 
		0.068198248744010925;
	setAttr -s 5 ".koy[0:4]"  0 0 -0.99662071466445923 -0.99767184257507324 
		-0.99767184257507324;
createNode animCurveTL -n "animCurveTL720";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.066422756288499141 4.5 0.066422756288499141 
		9 0.037676790392209031 10 0.037676790392209031;
	setAttr -s 4 ".kit[0:3]"  3 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 0.92037642002105713 0.92037642002105713;
	setAttr -s 4 ".kiy[1:3]"  0 -0.39103361964225769 -0.39103361964225769;
	setAttr -s 4 ".kox[0:3]"  1 1 0.92037630081176758 0.92037630081176758;
	setAttr -s 4 ".koy[0:3]"  0 0 -0.3910338282585144 -0.3910338282585144;
createNode animCurveTU -n "animCurveTU1102";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 4.5 0 9 0 10 0;
	setAttr -s 4 ".kit[0:3]"  2 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[0:3]"  1 1 1 1;
	setAttr -s 4 ".koy[0:3]"  0 0 0 0;
createNode animCurveTL -n "animCurveTL721";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.75537025498543575 4.5 -0.75537025498543575 
		6 -0.88734118782256388 9 0.25609817038302429 10 0.25609817038302429;
	setAttr -s 5 ".kit[0:4]"  3 3 1 1 1;
	setAttr -s 5 ".kot[1:4]"  3 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 0.072686761617660522 0.072686761617660522;
	setAttr -s 5 ".kiy[2:4]"  0 0.99735486507415771 0.99735486507415771;
	setAttr -s 5 ".kox[0:4]"  1 1 1 0.072686761617660522 0.072686761617660522;
	setAttr -s 5 ".koy[0:4]"  0 0 0 0.99735486507415771 0.99735486507415771;
createNode animCurveTL -n "animCurveTL722";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.073475021782978711 4.5 -0.073475021782978711 
		6 -0.65111432363320798 9 -1.7226297923166418 10 -1.7226297923166418;
	setAttr -s 5 ".kit[0:4]"  3 3 1 1 1;
	setAttr -s 5 ".kot[1:4]"  3 1 1 1;
	setAttr -s 5 ".kix[2:4]"  0.038567814975976944 0.16304092109203339 
		0.16304092109203339;
	setAttr -s 5 ".kiy[2:4]"  -0.99925601482391357 -0.98661929368972778 
		-0.98661929368972778;
	setAttr -s 5 ".kox[0:4]"  1 1 0.038567788898944855 0.16304099559783936 
		0.16304099559783936;
	setAttr -s 5 ".koy[0:4]"  0 0 -0.9992559552192688 -0.98661929368972778 
		-0.98661929368972778;
createNode animCurveTL -n "animCurveTL723";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -0.10278940729156966 4.5 -0.10278940729156966 
		9 -0.3930046773400398 10 -0.3930046773400398;
	setAttr -s 4 ".kit[0:3]"  3 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 0.45915400981903076 0.45915400981903076;
	setAttr -s 4 ".kiy[1:3]"  0 -0.88835668563842773 -0.88835668563842773;
	setAttr -s 4 ".kox[0:3]"  1 1 0.45915386080741882 0.45915386080741882;
	setAttr -s 4 ".koy[0:3]"  0 0 -0.88835674524307251 -0.88835674524307251;
createNode animCurveTU -n "animCurveTU1103";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 4.5 0 9 0 10 0;
	setAttr -s 4 ".kit[0:3]"  2 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[0:3]"  1 1 1 1;
	setAttr -s 4 ".koy[0:3]"  0 0 0 0;
createNode animCurveTL -n "animCurveTL724";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.8594552290779115 4.5 -0.8594552290779115 
		6 -0.78787869380628373 9 0.71285300684694819 10 0.71285300684694819;
	setAttr -s 5 ".kit[0:4]"  9 3 1 1 1;
	setAttr -s 5 ".kot[1:4]"  3 1 1 1;
	setAttr -s 5 ".kix[2:4]"  0.24525924026966095 0.055649463087320328 
		0.055649463087320328;
	setAttr -s 5 ".kiy[2:4]"  0.96945756673812866 0.99845033884048462 
		0.99845033884048462;
	setAttr -s 5 ".kox[0:4]"  1 1 0.24525932967662811 0.055649518966674805 
		0.055649518966674805;
	setAttr -s 5 ".koy[0:4]"  0 0 0.96945750713348389 0.99845039844512939 
		0.99845039844512939;
createNode animCurveTL -n "animCurveTL725";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4.5 0 6 -0.70389752596393351 9 -1.0690515193184758 
		10 -1.0690515193184758;
	setAttr -s 5 ".kit[0:4]"  3 3 1 1 1;
	setAttr -s 5 ".kot[1:4]"  3 1 1 1;
	setAttr -s 5 ".kix[2:4]"  0.17493578791618347 0.47101682424545288 
		0.47101682424545288;
	setAttr -s 5 ".kiy[2:4]"  -0.98457986116409302 -0.88212418556213379 
		-0.88212418556213379;
	setAttr -s 5 ".kox[0:4]"  1 1 0.17493580281734467 0.47101780772209167 
		0.47101780772209167;
	setAttr -s 5 ".koy[0:4]"  0 0 -0.98457986116409302 -0.88212376832962036 
		-0.88212376832962036;
createNode animCurveTL -n "animCurveTL726";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -0.14721316863839706 4.5 -0.14721316863839706 
		9 -0.14125877609143869 10 -0.14125877609143869;
	setAttr -s 4 ".kit[0:3]"  3 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 0.99729365110397339 0.99729365110397339;
	setAttr -s 4 ".kiy[1:3]"  0 0.073521599173545837 0.073521599173545837;
	setAttr -s 4 ".kox[0:3]"  1 1 0.99729359149932861 0.99729359149932861;
	setAttr -s 4 ".koy[0:3]"  0 0 0.073521547019481659 0.073521547019481659;
createNode animCurveTU -n "animCurveTU1104";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10 3 10 4.5 10 6 10 7.5 10 9 10 10 10;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL727";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.02737012108107054 3 -0.02737012108107054 
		4.5 -0.019132126145601638 6 0.030442791673862182 7.5 0.016414508653775778 9 0.014860688539430114 
		10 0.014860688539430114;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.96282243728637695 0.99951744079589844 
		0.99951744079589844;
	setAttr -s 7 ".kiy[4:6]"  -0.27013492584228516 -0.031061423942446709 
		-0.031061423942446709;
	setAttr -s 7 ".kox[0:6]"  1 0.98669731616973877 0.71011894941329956 
		0.96282243728637695 0.99951744079589844 0.99951750040054321 0.99951750040054321;
	setAttr -s 7 ".koy[0:6]"  0 0.16256813704967499 0.70408183336257935 
		-0.27013492584228516 -0.031061440706253052 -0.031061405315995216 -0.031061405315995216;
createNode animCurveTL -n "animCurveTL728";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.023202672652752949 3 0.023202672652752949 
		4.5 0.053936934258455874 6 -0.37524737869345742 7.5 -0.70316516679612395 9 -0.69320320524770218 
		10 -0.69320320524770218;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.15073506534099579 0.980724036693573 0.980724036693573;
	setAttr -s 7 ".kiy[4:6]"  -0.98857420682907104 0.19539789855480194 
		0.19539789855480194;
	setAttr -s 7 ".kox[0:6]"  1 0.85192418098449707 0.11571742594242096 
		0.15073506534099579 0.98072415590286255 0.98072391748428345 0.98072391748428345;
	setAttr -s 7 ".koy[0:6]"  0 0.52366513013839722 -0.99328219890594482 
		-0.98857420682907104 0.19539718329906464 0.19539865851402283 0.19539865851402283;
createNode animCurveTL -n "animCurveTL729";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.14312606150235696 3 -0.14312606150235696 
		4.5 -0.29728347987865289 6 -0.5939668736178475 7.5 -0.69325915181667841 9 -0.66362723784472955 
		10 -0.66362723784472955;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.44975820183753967 0.8602745532989502 
		0.8602745532989502;
	setAttr -s 7 ".kiy[4:6]"  -0.89315032958984375 0.50983107089996338 
		0.50983107089996338;
	setAttr -s 7 ".kox[0:6]"  1 0.30852147936820984 0.16618630290031433 
		0.44975820183753967 0.86027449369430542 0.86027419567108154 0.86027419567108154;
	setAttr -s 7 ".koy[0:6]"  0 -0.9512174129486084 -0.98609441518783569 
		-0.89315032958984375 0.50983119010925293 0.50983154773712158 0.50983154773712158;
createNode animCurveTA -n "animCurveTA1371";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 3 3 3 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1372";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1373";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -3.9756933518293979e-016 3 0 4.5 -3.9756933518293979e-016 
		6 -3.9756933518293979e-016 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1374";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1105";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 4.5 1 6 1 7.5 1 9 1 10 1;
	setAttr -s 7 ".kit[0:6]"  2 2 1 2 1 1 1;
	setAttr -s 7 ".kot[1:6]"  2 1 2 1 1 1;
	setAttr -s 7 ".kix[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".kiy[2:6]"  0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1106";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 4.5 1 6 1 7.5 1 9 1 10 1;
	setAttr -s 7 ".kit[0:6]"  2 2 1 2 1 1 1;
	setAttr -s 7 ".kot[1:6]"  2 1 2 1 1 1;
	setAttr -s 7 ".kix[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".kiy[2:6]"  0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1107";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[0:6]"  2 2 1 2 1 1 1;
	setAttr -s 7 ".kot[1:6]"  2 1 2 1 1 1;
	setAttr -s 7 ".kix[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".kiy[2:6]"  0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1108";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[0:6]"  2 2 1 2 1 1 1;
	setAttr -s 7 ".kot[1:6]"  2 1 2 1 1 1;
	setAttr -s 7 ".kix[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".kiy[2:6]"  0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1109";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10 3 10 4.5 10 6 10 7.5 10 9 10 10 10;
	setAttr -s 7 ".kit[0:6]"  2 2 1 2 1 1 1;
	setAttr -s 7 ".kot[1:6]"  2 1 2 1 1 1;
	setAttr -s 7 ".kix[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".kiy[2:6]"  0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1110";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 25 3 25 4.5 25 6 25 7.5 25 9 25 10 25;
	setAttr -s 7 ".kit[0:6]"  2 2 1 2 1 1 1;
	setAttr -s 7 ".kot[1:6]"  2 1 2 1 1 1;
	setAttr -s 7 ".kix[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".kiy[2:6]"  0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1111";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[0:6]"  2 2 1 2 1 1 1;
	setAttr -s 7 ".kot[1:6]"  2 1 2 1 1 1;
	setAttr -s 7 ".kix[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".kiy[2:6]"  0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1112";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[0:6]"  2 2 1 2 1 1 1;
	setAttr -s 7 ".kot[1:6]"  2 1 2 1 1 1;
	setAttr -s 7 ".kix[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".kiy[2:6]"  0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1375";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10.555261301844832 3 10.555261301844832 
		4.5 10.555261301844832 6 14.976527870158488 7.5 -3.181 9 -3.181 10 -3.181;
	setAttr -s 7 ".kit[0:6]"  9 3 1 3 1 1 1;
	setAttr -s 7 ".kot[1:6]"  3 1 3 1 1 1;
	setAttr -s 7 ".kix[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".kiy[2:6]"  0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1376";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 -79.955842450653293 7.5 
		-84.076579976699051 9 -84.076851396947546 10 -84.076851396947546;
	setAttr -s 7 ".kit[0:6]"  9 3 1 1 1 1 1;
	setAttr -s 7 ".kot[1:6]"  3 1 1 1 1 1;
	setAttr -s 7 ".kix[2:6]"  1 0.16993902623653412 1 1 1;
	setAttr -s 7 ".kiy[2:6]"  0 -0.98545455932617188 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 0.16993905603885651 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 -0.9854544997215271 0 -0.00018354831263422966 
		-0.00018354831263422966;
createNode animCurveTA -n "animCurveTA1377";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 -22.020171467781655 7.5 
		2.4 9 2.4 10 2.4;
	setAttr -s 7 ".kit[0:6]"  9 3 1 3 1 1 1;
	setAttr -s 7 ".kot[1:6]"  3 1 3 1 1 1;
	setAttr -s 7 ".kix[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".kiy[2:6]"  0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL730";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 1.8546978835084267 7.5 
		2.7606932496084395 9 2.8299577885538647 10 2.8299577885538647;
	setAttr -s 7 ".kit[0:6]"  9 3 1 1 1 1 1;
	setAttr -s 7 ".kot[1:6]"  3 1 1 1 1 1;
	setAttr -s 7 ".kix[2:6]"  1 0.027345908805727959 0.41625490784645081 
		0.86717551946640015 0.86717551946640015;
	setAttr -s 7 ".kiy[2:6]"  0 0.9996260404586792 0.90924787521362305 
		0.49800264835357666 0.49800264835357666;
	setAttr -s 7 ".kox[0:6]"  1 1 1 0.027345906943082809 0.41625517606735229 
		0.86717545986175537 0.86717545986175537;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0.9996260404586792 0.9092477560043335 
		0.49800282716751099 0.49800282716751099;
createNode animCurveTL -n "animCurveTL731";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.38582961184709008 3 0.38582961184709008 
		4.5 0.38582961184709008 6 -0.48150644714806412 7.5 -0.92910910063845875 9 -0.94616938881324031 
		10 -0.94616938881324031;
	setAttr -s 7 ".kit[0:6]"  3 3 3 1 1 1 1;
	setAttr -s 7 ".kot[1:6]"  3 3 1 1 1 1;
	setAttr -s 7 ".kix[3:6]"  0.060998909175395966 0.75475317239761353 
		0.99814021587371826 0.99814021587371826;
	setAttr -s 7 ".kiy[3:6]"  -0.99813783168792725 -0.65600895881652832 
		-0.060960043221712112 -0.060960043221712112;
	setAttr -s 7 ".kox[0:6]"  1 1 1 0.060998905450105667 0.7547529935836792 
		0.99814021587371826 0.99814021587371826;
	setAttr -s 7 ".koy[0:6]"  0 0 0 -0.99813783168792725 -0.65600919723510742 
		-0.060960043221712112 -0.060960043221712112;
createNode animCurveTL -n "animCurveTL732";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.012835510537475885 3 -0.012835510537475885 
		4.5 -0.012835510537475885 6 -0.229779956765025 7.5 0.14338604707707642 9 0.14338604707707642 
		10 0.14338604707707642;
	setAttr -s 7 ".kit[0:6]"  9 3 3 3 1 1 1;
	setAttr -s 7 ".kot[1:6]"  3 3 3 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1378";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -10.507309270186466 4.5 -10.507309270186466 
		6 8.9470213436801043 9 0.24349147277486524 10 0.24349147277486524;
	setAttr -s 5 ".kit[0:4]"  10 3 3 1 1;
	setAttr -s 5 ".kot[1:4]"  3 3 1 1;
	setAttr -s 5 ".kix[3:4]"  0.9066765308380127 0.9066765308380127;
	setAttr -s 5 ".kiy[3:4]"  -0.42182651162147522 -0.42182651162147522;
	setAttr -s 5 ".kox[0:4]"  1 1 1 0.9066765308380127 0.9066765308380127;
	setAttr -s 5 ".koy[0:4]"  0 0 0 -0.42182657122612 -0.42182657122612;
createNode animCurveTA -n "animCurveTA1379";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -3.9401506072152763 9 -3.9401506072152763 
		10 -3.9401506072152763;
	setAttr -s 3 ".kix[0:2]"  1 1 1;
	setAttr -s 3 ".kiy[0:2]"  0 0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode animCurveTA -n "animCurveTA1380";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1.5206250006361597 9 1.5206250006361597 
		10 1.5206250006361597;
	setAttr -s 3 ".kix[0:2]"  1 1 1;
	setAttr -s 3 ".kiy[0:2]"  0 0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode animCurveTA -n "animCurveTA1381";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1382";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1383";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL733";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL734";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL735";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1384";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 8.8554843256175495 9 1.1117528411912649 
		10 1.1117528411912649;
	setAttr -s 5 ".kit[0:4]"  3 3 1 1 1;
	setAttr -s 5 ".kot[1:4]"  3 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 0.42785269021987915 0.42785269021987915;
	setAttr -s 5 ".kiy[2:4]"  0 -0.90384840965270996 -0.90384840965270996;
	setAttr -s 5 ".kox[0:4]"  1 1 1 0.42785272002220154 0.42785272002220154;
	setAttr -s 5 ".koy[0:4]"  0 0 0 -0.90384840965270996 -0.90384840965270996;
createNode animCurveTA -n "animCurveTA1385";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 -0.28184689715697175 9 -1.6033940176820145 
		10 -1.6033940176820145;
	setAttr -s 5 ".kit[0:4]"  3 3 1 1 1;
	setAttr -s 5 ".kot[1:4]"  3 1 1 1;
	setAttr -s 5 ".kix[2:4]"  0.9881439208984375 0.97019833326339722 
		0.97019833326339722;
	setAttr -s 5 ".kiy[2:4]"  -0.1535303145647049 -0.24231232702732086 
		-0.24231232702732086;
	setAttr -s 5 ".kox[0:4]"  1 1 0.9881439208984375 0.97019833326339722 
		0.97019833326339722;
	setAttr -s 5 ".koy[0:4]"  0 0 -0.1535302996635437 -0.24231226742267609 
		-0.24231226742267609;
createNode animCurveTA -n "animCurveTA1386";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0.34388367435125866 9 0.17982368586510949 
		10 0.17982368586510949;
	setAttr -s 5 ".kit[0:4]"  3 3 1 1 1;
	setAttr -s 5 ".kot[1:4]"  3 1 1 1;
	setAttr -s 5 ".kix[2:4]"  0.99997401237487793 0.99921125173568726 
		0.99921125173568726;
	setAttr -s 5 ".kiy[2:4]"  0.007204864639788866 -0.039709363132715225 
		-0.039709363132715225;
	setAttr -s 5 ".kox[0:4]"  1 1 0.99997407197952271 0.99921125173568726 
		0.99921125173568726;
	setAttr -s 5 ".koy[0:4]"  0 0 0.0072048674337565899 -0.039709355682134628 
		-0.039709355682134628;
createNode animCurveTL -n "animCurveTL736";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 9 0 10 0;
	setAttr -s 5 ".kit[0:4]"  2 2 1 1 1;
	setAttr -s 5 ".kot[1:4]"  2 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".koy[0:4]"  0 0 0 0 0;
createNode animCurveTL -n "animCurveTL737";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 9 0 10 0;
	setAttr -s 5 ".kit[0:4]"  2 2 1 1 1;
	setAttr -s 5 ".kot[1:4]"  2 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".koy[0:4]"  0 0 0 0 0;
createNode animCurveTL -n "animCurveTL738";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 9 0 10 0;
	setAttr -s 5 ".kit[0:4]"  2 2 1 1 1;
	setAttr -s 5 ".kot[1:4]"  2 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".koy[0:4]"  0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1113";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 4.5 1 6 1 7.5 1 9 1 10 1;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1114";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 3 0.99999999999999978 
		4.5 0.99999999999999978 6 0.99999999999999978 7.5 0.99999999999999978 9 0.99999999999999978 
		10 0.99999999999999978;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1115";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 3 0.99999999999999978 
		4.5 0.99999999999999978 6 0.99999999999999978 7.5 0.99999999999999978 9 0.99999999999999978 
		10 0.99999999999999978;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1387";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -5.066428676758755 3 -7.9742969355151141 
		4.5 2.5443835051808312 6 -1.0514066988216162 7.5 9.7365497364077367 9 11.043243992222633 
		10 11.043243992222633;
	setAttr -s 7 ".kit[0:6]"  3 1 1 3 1 1 1;
	setAttr -s 7 ".kot[3:6]"  3 1 1 1;
	setAttr -s 7 ".kix[1:6]"  0.41834452748298645 0.39563491940498352 
		1 1 0.77673959732055664 0.77673959732055664;
	setAttr -s 7 ".kiy[1:6]"  0.90828841924667358 0.9184078574180603 
		0 0 0.62982195615768433 0.62982195615768433;
	setAttr -s 7 ".kox[0:6]"  1 0.41834452748298645 0.3956349790096283 
		1 1 0.77673971652984619 0.77673971652984619;
	setAttr -s 7 ".koy[0:6]"  0 0.90828841924667358 0.9184078574180603 
		0 0 0.62982165813446045 0.62982165813446045;
createNode animCurveTA -n "animCurveTA1388";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.47627649301494307 3 -0.88756830316988744 
		4.5 -0.73438532572664839 6 -1.2340444501908163 9 -1.197080161612033 10 -1.197080161612033;
	setAttr -s 6 ".kit[3:5]"  1 1 1;
	setAttr -s 6 ".kot[3:5]"  1 1 1;
	setAttr -s 6 ".kix[3:5]"  0.98512834310531616 0.99997919797897339 
		0.99997919797897339;
	setAttr -s 6 ".kiy[3:5]"  -0.17182008922100067 0.0064513776451349258 
		0.0064513776451349258;
	setAttr -s 6 ".kox[3:5]"  0.99997919797897339 0.99997913837432861 
		0.99997913837432861;
	setAttr -s 6 ".koy[3:5]"  0.0064513729885220528 0.0064513511024415493 
		0.0064513511024415493;
createNode animCurveTA -n "animCurveTA1389";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.99253490036387859 3 -0.60840687335504728 
		4.5 -0.42598891893283158 6 -0.35669589660069045 9 0.89722995849952469 10 0.89722995849952469;
	setAttr -s 6 ".kit[0:5]"  3 1 2 1 1 1;
	setAttr -s 6 ".kot[2:5]"  2 1 1 1;
	setAttr -s 6 ".kix[1:5]"  0.99377286434173584 0.99797886610031128 
		0.98634886741638184 0.97445213794708252 0.97445213794708252;
	setAttr -s 6 ".kiy[1:5]"  0.11142513155937195 0.063547179102897644 
		0.16466906666755676 0.22459538280963898 0.22459538280963898;
	setAttr -s 6 ".kox[0:5]"  1 0.99377280473709106 0.99970757961273193 
		0.98634886741638184 0.97445213794708252 0.97445213794708252;
	setAttr -s 6 ".koy[0:5]"  0 0.11142513900995255 0.024180756881833076 
		0.16466906666755676 0.22459544241428375 0.22459544241428375;
createNode animCurveTU -n "animCurveTU1116";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 4.5 1 6 1 7.5 1 9 1 10 1;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1117";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 3 0.99999999999999978 
		4.5 0.99999999999999978 6 0.99999999999999978 7.5 0.99999999999999978 9 0.99999999999999978 
		10 0.99999999999999978;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1118";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 3 0.99999999999999978 
		4.5 0.99999999999999978 6 0.99999999999999978 7.5 0.99999999999999978 9 0.99999999999999978 
		10 0.99999999999999978;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1390";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -9.8819625697636226 3 -5.775034621920903 
		4.5 10.798043637600381 6 25.356313969061251 7.5 21.459983772404655 9 15.457396968532876 
		10 15.457396968532876;
	setAttr -s 7 ".kit[0:6]"  3 9 1 3 1 1 1;
	setAttr -s 7 ".kot[1:6]"  9 1 3 1 1 1;
	setAttr -s 7 ".kix[2:6]"  0.12551510334014893 1 0.40402814745903015 
		0.47525817155838013 0.47525817155838013;
	setAttr -s 7 ".kiy[2:6]"  0.99209171533584595 0 -0.91474658250808716 
		-0.87984639406204224 -0.87984639406204224;
	setAttr -s 7 ".kox[0:6]"  1 0.38376668095588684 0.12551511824131012 
		1 0.40402832627296448 0.4752582311630249 0.4752582311630249;
	setAttr -s 7 ".koy[0:6]"  0 0.92343008518218994 0.99209171533584595 
		0 -0.91474646329879761 -0.87984633445739746 -0.87984633445739746;
createNode animCurveTA -n "animCurveTA1391";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.26173116802236968 4.5 -0.37407078704431984 
		6 -0.79817565838126914 7.5 -1.2131566902952104 9 -1.4906568354550596 10 -1.4906568354550596;
	setAttr -s 6 ".kit[3:5]"  9 1 1;
	setAttr -s 6 ".kot[3:5]"  9 1 1;
	setAttr -s 6 ".kix[0:5]"  0.99982178211212158 0.99516171216964722 
		0.98687392473220825 0.99277544021606445 0.9976460337638855 0.9976460337638855;
	setAttr -s 6 ".kiy[0:5]"  0.018881967291235924 -0.098250336945056915 
		-0.16149251163005829 -0.11998759210109711 -0.068573951721191406 -0.068573951721191406;
	setAttr -s 6 ".kox[0:5]"  0.99982178211212158 0.99516171216964722 
		0.98687392473220825 0.99277544021606445 0.9976460337638855 0.9976460337638855;
	setAttr -s 6 ".koy[0:5]"  0.018881967291235924 -0.098250336945056915 
		-0.16149255633354187 -0.11998759210109711 -0.068573951721191406 -0.068573951721191406;
createNode animCurveTA -n "animCurveTA1392";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.191 4.5 0.24011176253271962 6 0.16116947428706457 
		7.5 -0.34835330912265317 9 -1.630184515517997 10 -1.630184515517997;
	setAttr -s 6 ".kit[0:5]"  3 3 1 1 1 1;
	setAttr -s 6 ".kot[1:5]"  3 1 1 9 1;
	setAttr -s 6 ".kix[2:5]"  0.99712288379669189 0.96850508451461792 
		0.82048618793487549 0.82048618793487549;
	setAttr -s 6 ".kiy[2:5]"  -0.075802572071552277 -0.24899381399154663 
		-0.57166630029678345 -0.57166630029678345;
	setAttr -s 6 ".kox[0:5]"  1 1 0.99712288379669189 0.96850508451461792 
		0.965800940990448 0.91279268264770508;
	setAttr -s 6 ".koy[0:5]"  0 0 -0.075802557170391083 -0.24899384379386902 
		-0.25928476452827454 -0.40842306613922119;
createNode animCurveTU -n "animCurveTU1119";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 4.5 1 6 1 7.5 1 9 1 10 1;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1120";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 3 0.99999999999999978 
		4.5 0.99999999999999978 6 0.99999999999999978 7.5 0.99999999999999978 9 0.99999999999999978 
		10 0.99999999999999978;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1121";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 3 0.99999999999999978 
		4.5 0.99999999999999978 6 0.99999999999999978 7.5 0.99999999999999978 9 0.99999999999999978 
		10 0.99999999999999978;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1393";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 16.291300957444619 3 19.496885562820307 
		4.5 -13.358102528501233 6 -8.2254682714182081 7.5 2.0692189015832492 9 11.754301862289594 
		10 11.754301862289594;
	setAttr -s 7 ".kit[0:6]"  3 3 3 1 1 1 1;
	setAttr -s 7 ".kot[1:6]"  3 3 1 1 1 1;
	setAttr -s 7 ".kix[3:6]"  0.25088435411453247 0.28341913223266602 
		0.30023851990699768 0.30023851990699768;
	setAttr -s 7 ".kiy[3:6]"  0.96801704168319702 0.95899617671966553 
		0.95386409759521484 0.95386409759521484;
	setAttr -s 7 ".kox[0:6]"  1 1 1 0.25088435411453247 0.28341904282569885 
		0.30023893713951111 0.30023893713951111;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0.96801704168319702 0.95899617671966553 
		0.95386409759521484 0.95386409759521484;
createNode animCurveTA -n "animCurveTA1394";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.94704837463169422 3 0.83470875560974422 
		4.5 0.41060388427279487 6 -0.0043771476411465513 7.5 -0.28187729280099555 9 -0.45474852617299621 
		10 -0.45474852617299621;
	setAttr -s 7 ".kit[0:6]"  3 1 1 9 1 1 1;
	setAttr -s 7 ".kot[3:6]"  9 1 1 1;
	setAttr -s 7 ".kix[1:6]"  0.99633932113647461 0.98687392473220825 
		0.99277544021606445 0.9976460337638855 0.99876618385314941 0.99876618385314941;
	setAttr -s 7 ".kiy[1:6]"  -0.085486948490142822 -0.16149251163005829 
		-0.1199876070022583 -0.068573951721191406 -0.049660272896289825 -0.049660272896289825;
	setAttr -s 7 ".kox[0:6]"  1 0.99633932113647461 0.98687392473220825 
		0.99277544021606445 0.9976460337638855 0.99876612424850464 0.99876612424850464;
	setAttr -s 7 ".koy[0:6]"  0 -0.085486955940723419 -0.16149255633354187 
		-0.1199876070022583 -0.068574003875255585 -0.049660295248031616 -0.049660295248031616;
createNode animCurveTA -n "animCurveTA1395";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.7544888543665405 3 1.8038223978008963 
		4.5 1.7248801095552411 6 1.2153573261455235 7.5 -0.066473880249820372 9 -2.8422279258583223 
		10 -2.8422279258583223;
	setAttr -s 7 ".kit[0:6]"  3 3 1 1 1 1 1;
	setAttr -s 7 ".kot[1:6]"  3 1 1 1 1 1;
	setAttr -s 7 ".kix[2:6]"  0.99712288379669189 0.96850508451461792 
		0.82048618793487549 0.69974333047866821 0.69974333047866821;
	setAttr -s 7 ".kiy[2:6]"  -0.075802572071552277 -0.24899381399154663 
		-0.57166635990142822 -0.71439433097839355 -0.71439433097839355;
	setAttr -s 7 ".kox[0:6]"  1 1 0.99712288379669189 0.96850508451461792 
		0.82048636674880981 0.69974333047866821 0.69974333047866821;
	setAttr -s 7 ".koy[0:6]"  0 0 -0.075802557170391083 -0.24899384379386902 
		-0.57166606187820435 -0.71439427137374878 -0.71439427137374878;
createNode animCurveTU -n "animCurveTU1122";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1396";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.0973359671968677 3 1.0973359671968677 
		4.5 1.0930775412988094 6 1.0774674731814673 7.5 1.0118874135411711 9 0.71679387719347254 
		10 0.71679387719347254;
	setAttr -s 7 ".kit[0:6]"  3 3 1 1 1 1 1;
	setAttr -s 7 ".kot[1:6]"  3 1 1 1 1 1;
	setAttr -s 7 ".kix[2:6]"  0.99999576807022095 0.99995237588882446 
		0.99865204095840454 0.99228119850158691 0.99228119850158691;
	setAttr -s 7 ".kiy[2:6]"  -0.0029149278998374939 -0.0097546931356191635 
		-0.051904991269111633 -0.12400774657726288 -0.12400774657726288;
	setAttr -s 7 ".kox[0:6]"  1 1 0.99999576807022095 0.99995237588882446 
		0.99865204095840454 0.99228125810623169 0.99228125810623169;
	setAttr -s 7 ".koy[0:6]"  0 0 -0.0029149288311600685 -0.0097546903416514397 
		-0.051904939115047455 -0.12400773912668228 -0.12400773912668228;
createNode animCurveTA -n "animCurveTA1397";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -0.010805299436553227 4.5 -0.087090400581147462 
		9 -0.51108696571050338 10 -0.51108696571050338;
	setAttr -s 4 ".kit[0:3]"  3 1 1 1;
	setAttr -s 4 ".kix[1:3]"  0.99976629018783569 0.99655187129974365 
		0.99655187129974365;
	setAttr -s 4 ".kiy[1:3]"  -0.021622352302074432 -0.082971520721912384 
		-0.082971520721912384;
	setAttr -s 4 ".kox[0:3]"  1 0.99976617097854614 0.99655193090438843 
		0.99655193090438843;
	setAttr -s 4 ".koy[0:3]"  0 -0.021622354164719582 -0.082971565425395966 
		-0.082971565425395966;
createNode animCurveTA -n "animCurveTA1398";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.20351528028967278 3 -1.8661911945472858 
		4.5 -6.9021321143927405 6 -57.220446349227508 7.5 -55.186276505489758 9 -54.532297647440124 
		10 -54.532297647440124;
	setAttr -s 7 ".kit[0:6]"  3 1 1 3 1 1 1;
	setAttr -s 7 ".kot[3:6]"  3 1 1 1;
	setAttr -s 7 ".kix[1:6]"  0.82622569799423218 0.2758694589138031 
		1 0.9542345404624939 0.99175655841827393 0.99175655841827393;
	setAttr -s 7 ".kiy[1:6]"  -0.56333917379379272 -0.96119511127471924 
		0 0.29905915260314941 0.12813620269298553 0.12813620269298553;
	setAttr -s 7 ".kox[0:6]"  1 0.8262256383895874 0.2758694589138031 
		1 0.95423489809036255 0.9917566180229187 0.9917566180229187;
	setAttr -s 7 ".koy[0:6]"  0 -0.56333929300308228 -0.96119505167007446 
		0 0.29905807971954346 0.12813644111156464 0.12813644111156464;
createNode animCurveTL -n "animCurveTL739";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.078873239085785252 3 -0.10317029840541565 
		4.5 -0.052454018224000032 6 0.61233830689838409 7.5 1.8902764518264439 9 2.2086623630018529 
		10 2.2086623630018529;
	setAttr -s 7 ".kit[0:6]"  3 3 1 1 1 1 1;
	setAttr -s 7 ".kot[1:6]"  3 1 1 1 1 1;
	setAttr -s 7 ".kix[2:6]"  0.34067344665527344 0.041066505014896393 
		0.10356932133436203 0.25590935349464417 0.25590935349464417;
	setAttr -s 7 ".kiy[2:6]"  0.9401816725730896 0.99915647506713867 
		0.99462223052978516 0.96670073270797729 0.96670073270797729;
	setAttr -s 7 ".kox[0:6]"  1 1 0.34067344665527344 0.041066497564315796 
		0.10356941074132919 0.25590947270393372 0.25590947270393372;
	setAttr -s 7 ".koy[0:6]"  0 0 0.9401816725730896 0.99915647506713867 
		0.99462223052978516 0.96670079231262207 0.96670079231262207;
createNode animCurveTL -n "animCurveTL740";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.26682379778056281 3 0.36812442132160555 
		4.5 0.20767937836558015 6 -0.11504570389057286 7.5 -0.40376674979396554 9 -0.53753657327866677 
		10 -0.53753657327866677;
	setAttr -s 7 ".kit[0:6]"  3 3 1 1 1 1 1;
	setAttr -s 7 ".kot[1:6]"  3 1 1 1 1 1;
	setAttr -s 7 ".kix[2:6]"  0.16719202697277069 0.13863472640514374 
		0.26537612080574036 0.4794081449508667 0.4794081449508667;
	setAttr -s 7 ".kiy[2:6]"  -0.9859243631362915 -0.99034357070922852 
		-0.96414494514465332 -0.87759202718734741 -0.87759202718734741;
	setAttr -s 7 ".kox[0:6]"  1 1 0.16719202697277069 0.13863469660282135 
		0.26537597179412842 0.47940900921821594 0.47940900921821594;
	setAttr -s 7 ".koy[0:6]"  0 0 -0.9859243631362915 -0.99034357070922852 
		-0.9641450047492981 -0.87759160995483398 -0.87759160995483398;
createNode animCurveTL -n "animCurveTL741";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.034824194676283823 3 -0.048647181024443771 
		4.5 -0.048647181024443771 6 -0.034824194676283823 7.5 0.0046514531307749463 9 0.014628394704107154 
		10 0.014628394704107154;
	setAttr -s 7 ".kit[0:6]"  3 1 1 9 1 1 1;
	setAttr -s 7 ".kot[3:6]"  9 1 1 1;
	setAttr -s 7 ".kix[1:6]"  0.99621891975402832 0.99656909704208374 
		0.88248002529144287 0.9651908278465271 0.99087965488433838 0.99087965488433838;
	setAttr -s 7 ".kiy[1:6]"  -0.086877979338169098 0.082764714956283569 
		0.47034984827041626 0.26154664158821106 0.13474975526332855 0.13474975526332855;
	setAttr -s 7 ".kox[0:6]"  1 0.99621903896331787 0.99656909704208374 
		0.88248002529144287 0.96519088745117188 0.9908795952796936 0.9908795952796936;
	setAttr -s 7 ".koy[0:6]"  0 -0.086877994239330292 0.082764714956283569 
		0.47034984827041626 0.2615465521812439 0.1347498893737793 0.1347498893737793;
createNode animCurveTU -n "animCurveTU1123";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.0000000000000002 3 1.0000000000000002 
		4.5 1.0000000000000002 6 1.0000000000000002 7.5 1.0000000000000002 9 1.0000000000000002 
		10 1.0000000000000002;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1124";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999989 3 0.99999999999999989 
		4.5 0.99999999999999989 6 0.99999999999999989 7.5 0.99999999999999989 9 0.99999999999999989 
		10 0.99999999999999989;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1125";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 4.5 1 6 1 7.5 1 9 1 10 1;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1399";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1400";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1401";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL742";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.0078247081510850677 3 -0.0078247081510850677 
		4.5 -0.017795719106728999 6 -0.026045692090018994 7.5 -0.0048617906241890975 9 0.0068269090290659674 
		10 0.0068269090290659674;
	setAttr -s 7 ".kit[0:6]"  3 3 1 3 1 1 1;
	setAttr -s 7 ".kot[1:6]"  3 1 3 1 1 1;
	setAttr -s 7 ".kix[2:6]"  0.95986270904541016 1 0.95732587575912476 
		0.98549079895019531 0.98549079895019531;
	setAttr -s 7 ".kiy[2:6]"  -0.28047043085098267 0 0.28901064395904541 
		0.16972911357879639 0.16972911357879639;
	setAttr -s 7 ".kox[0:6]"  1 1 0.95986264944076538 1 0.95732587575912476 
		0.98549079895019531 0.98549079895019531;
	setAttr -s 7 ".koy[0:6]"  0 0 -0.28047046065330505 0 0.28901058435440063 
		0.16972909867763519 0.16972909867763519;
createNode animCurveTL -n "animCurveTL743";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.06041488693119227 3 0.06041488693119227 
		4.5 0.06041488693119227 6 0.022652185434174212 7.5 -0.071490942060334836 9 -0.064076793242415955 
		10 -0.064076793242415955;
	setAttr -s 7 ".kit[0:6]"  9 3 3 1 1 1 1;
	setAttr -s 7 ".kot[1:6]"  3 3 1 1 1 1;
	setAttr -s 7 ".kix[3:6]"  0.49036777019500732 1 0.96373832225799561 
		0.96373832225799561;
	setAttr -s 7 ".kiy[3:6]"  -0.87151557207107544 0 0.26684895157814026 
		0.26684895157814026;
	setAttr -s 7 ".kox[0:6]"  1 1 1 0.49036774039268494 1 0.96373838186264038 
		0.96373838186264038;
	setAttr -s 7 ".koy[0:6]"  0 0 0 -0.87151557207107544 0 0.26684901118278503 
		0.26684901118278503;
createNode animCurveTL -n "animCurveTL744";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.045916714597033288 3 0.045916714597033288 
		4.5 0.029006937440774601 6 -0.043374583139982062 7.5 -0.030842140083647423 9 -0.003722228260567461 
		10 -0.003722228260567461;
	setAttr -s 7 ".kit[0:6]"  3 3 9 3 1 1 1;
	setAttr -s 7 ".kot[1:6]"  3 9 3 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.89821577072143555 0.87573081254959106 
		0.87573081254959106;
	setAttr -s 7 ".kiy[4:6]"  0.43955487012863159 0.48279979825019836 
		0.48279979825019836;
	setAttr -s 7 ".kox[0:6]"  1 1 0.74591702222824097 1 0.89821577072143555 
		0.87573093175888062 0.87573093175888062;
	setAttr -s 7 ".koy[0:6]"  0 0 -0.66603899002075195 0 0.43955492973327637 
		0.48279955983161926 0.48279955983161926;
createNode animCurveTU -n "animCurveTU1126";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.0000000000000002 3 1.0000000000000002 
		4.5 1.0000000000000002 6 1.0000000000000002 7.5 1.0000000000000002 9 1.0000000000000002 
		10 1.0000000000000002;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1127";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.0000000000000002 3 1.0000000000000002 
		4.5 1.0000000000000002 6 1.0000000000000002 7.5 1.0000000000000002 9 1.0000000000000002 
		10 1.0000000000000002;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1128";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.0000000000000002 3 1.0000000000000002 
		4.5 1.0000000000000002 6 1.0000000000000002 7.5 1.0000000000000002 9 1.0000000000000002 
		10 1.0000000000000002;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1402";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1403";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1404";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL745";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.0016820758713359874 3 0.0016820758713359874 
		4.5 0.0016820758713359874 6 2.599391102387619e-005 7.5 -0.019212174946063934 9 -0.040203391071040047 
		10 -0.040203391071040047;
	setAttr -s 7 ".kit[0:6]"  9 9 3 1 1 1 1;
	setAttr -s 7 ".kot[1:6]"  9 3 1 1 1 1;
	setAttr -s 7 ".kix[3:6]"  0.99663054943084717 0.90737664699554443 
		0.93966883420944214 0.93966883420944214;
	setAttr -s 7 ".kiy[3:6]"  -0.082021325826644897 -0.42031857371330261 
		-0.34208548069000244 -0.34208548069000244;
	setAttr -s 7 ".kox[0:6]"  1 1 1 0.99663054943084717 0.90737652778625488 
		0.93966895341873169 0.93966895341873169;
	setAttr -s 7 ".koy[0:6]"  0 0 0 -0.082021333277225494 -0.420318603515625 
		-0.34208524227142334 -0.34208524227142334;
createNode animCurveTL -n "animCurveTL746";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.00036695532294986821 3 -0.00036695532294986821 
		4.5 -0.00036695532294986821 6 0.048989025760847939 7.5 0.15048260386554188 9 0.15397420549740812 
		10 0.15397420549740812;
	setAttr -s 7 ".kit[0:6]"  9 3 3 1 1 1 1;
	setAttr -s 7 ".kot[1:6]"  3 3 1 1 1 1;
	setAttr -s 7 ".kix[3:6]"  0.48731821775436401 0.94341021776199341 
		0.9821009635925293 0.9821009635925293;
	setAttr -s 7 ".kiy[3:6]"  0.87322443723678589 0.33162799477577209 
		-0.18835505843162537 -0.18835505843162537;
	setAttr -s 7 ".kox[0:6]"  1 1 1 0.48731812834739685 0.94341027736663818 
		0.9821009635925293 0.9821009635925293;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0.87322443723678589 0.33162793517112732 
		-0.18835535645484924 -0.18835535645484924;
createNode animCurveTL -n "animCurveTL747";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.066560894777387858 3 -0.066560894777387858 
		4.5 -0.066560894777387858 6 0.025029303769686151 7.5 -0.046970284341162336 9 -0.13581386367258905 
		10 -0.13581386367258905;
	setAttr -s 7 ".kit[0:6]"  9 3 3 3 1 1 1;
	setAttr -s 7 ".kot[1:6]"  3 3 3 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.43778881430625916 0.54858934879302979 
		0.54858934879302979;
	setAttr -s 7 ".kiy[4:6]"  -0.89907777309417725 -0.83609193563461304 
		-0.83609193563461304;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 0.43778887391090393 0.54858911037445068 
		0.54858911037445068;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 -0.89907777309417725 -0.83609205484390259 
		-0.83609205484390259;
createNode animCurveTU -n "animCurveTU1129";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999967 3 0.99999999999999967 
		4.5 0.99999999999999967 6 0.99999999999999967 7.5 0.99999999999999967 9 0.99999999999999967 
		10 0.99999999999999967;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1130";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999989 3 0.99999999999999989 
		4.5 0.99999999999999989 6 0.99999999999999989 7.5 0.99999999999999989 9 0.99999999999999989 
		10 0.99999999999999989;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1131";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999956 3 0.99999999999999956 
		4.5 0.99999999999999956 6 0.99999999999999956 7.5 0.99999999999999956 9 0.99999999999999956 
		10 0.99999999999999956;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1405";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -2.4790172850168215 3 -2.4790172850168215 
		4.5 -2.33085249423161 6 -37.441547020768851 7.5 -22.147199842291414 9 -22.079945797573952 
		10 -22.079945797573952;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.18410840630531311 0.99972456693649292 
		0.99972456693649292;
	setAttr -s 7 ".kiy[4:6]"  0.98290592432022095 0.023469915613532066 
		0.023469915613532066;
	setAttr -s 7 ".kox[0:6]"  1 0.9986652135848999 0.081322804093360901 
		0.18410840630531311 0.99972456693649292 0.99972456693649292 0.99972456693649292;
	setAttr -s 7 ".koy[0:6]"  0 0.051650229841470718 -0.99668776988983154 
		0.98290592432022095 0.023468945175409317 0.023469576612114906 0.023469576612114906;
createNode animCurveTA -n "animCurveTA1406";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 -19.903644720219873 6 -26.757902378394999 
		7.5 -21.548727024745848 9 -21.655948551885487 10 -21.655948551885487;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.48188549280166626 0.99930030107498169 
		0.99930030107498169;
	setAttr -s 7 ".kiy[4:6]"  0.87623423337936401 -0.037401884794235229 
		-0.037401884794235229;
	setAttr -s 7 ".kox[0:6]"  1 0.14246475696563721 0.3856300413608551 
		0.48188549280166626 0.99930036067962646 0.99930036067962646 0.99930036067962646;
	setAttr -s 7 ".koy[0:6]"  0 -0.9897998571395874 -0.92265355587005615 
		0.87623423337936401 -0.037400320172309875 -0.037401288747787476 -0.037401288747787476;
createNode animCurveTA -n "animCurveTA1407";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 -0.84442095567177922 6 -19.017807245700439 
		7.5 -14.486560725543789 9 -13.256719042573783 10 -13.256719042573783;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.53438615798950195 0.91890382766723633 
		0.91890382766723633;
	setAttr -s 7 ".kiy[4:6]"  0.84524047374725342 0.39448162913322449 
		0.39448162913322449;
	setAttr -s 7 ".kox[0:6]"  1 0.95919889211654663 0.15571366250514984 
		0.53438615798950195 0.9189038872718811 0.9189038872718811 0.9189038872718811;
	setAttr -s 7 ".koy[0:6]"  0 -0.28273200988769531 -0.98780220746994019 
		0.84524047374725342 0.39448153972625732 0.39448150992393494 0.39448150992393494;
createNode animCurveTL -n "animCurveTL748";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.014617768625972012 3 -0.014617768625972012 
		4.5 -0.044447127389627368 6 -0.026318810018810968 7.5 -0.078601024967925218 9 -0.042237736826220604 
		10 -0.042237736826220604;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.69115710258483887 0.80873870849609375 
		0.80873870849609375;
	setAttr -s 7 ".kiy[4:6]"  -0.72270452976226807 0.58816802501678467 
		0.58816802501678467;
	setAttr -s 7 ".kox[0:6]"  1 0.85878324508666992 0.94011604785919189 
		0.69115710258483887 0.80873870849609375 0.80873870849609375 0.80873870849609375;
	setAttr -s 7 ".koy[0:6]"  0 -0.51233905553817749 0.3408544659614563 
		-0.72270452976226807 0.58816802501678467 0.58816802501678467 0.58816802501678467;
createNode animCurveTL -n "animCurveTL749";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.048890236498641375 3 0.048890236498641375 
		4.5 0.05260427744148663 6 0.0060425142140090402 7.5 0.019494822935181469 9 -0.0035637621598730018 
		10 -0.0035637621598730018;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.9656604528427124 0.90808606147766113 
		0.90808606147766113;
	setAttr -s 7 ".kiy[4:6]"  0.259807288646698 -0.41878360509872437 
		-0.41878360509872437;
	setAttr -s 7 ".kox[0:6]"  1 0.99725258350372314 0.73182070255279541 
		0.9656604528427124 0.90808606147766113 0.90808606147766113 0.90808606147766113;
	setAttr -s 7 ".koy[0:6]"  0 0.074076727032661438 -0.68149727582931519 
		0.259807288646698 -0.41878366470336914 -0.41878360509872437 -0.41878360509872437;
createNode animCurveTL -n "animCurveTL750";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.015444448179427845 3 0.015444448179427845 
		4.5 0.024948471413495821 6 0.054255047073166487 7.5 0.059955119411078416 9 0.04982832757525002 
		10 0.04982832757525002;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.99356454610824585 0.98009979724884033 
		0.98009979724884033;
	setAttr -s 7 ".kiy[4:6]"  0.11326780170202255 -0.19850538671016693 
		-0.19850538671016693;
	setAttr -s 7 ".kox[0:6]"  1 0.98240995407104492 0.86272627115249634 
		0.99356454610824585 0.98009979724884033 0.98009979724884033 0.98009979724884033;
	setAttr -s 7 ".koy[0:6]"  0 0.18673691153526306 0.50567108392715454 
		0.11326780170202255 -0.19850531220436096 -0.19850531220436096 -0.19850531220436096;
createNode animCurveTU -n "animCurveTU1132";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999933 3 0.99999999999999933 
		4.5 0.99999999999999933 6 0.99999999999999933 7.5 0.99999999999999933 9 0.99999999999999933 
		10 0.99999999999999933;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1133";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999933 3 0.99999999999999933 
		4.5 0.99999999999999933 6 0.99999999999999933 7.5 0.99999999999999933 9 0.99999999999999933 
		10 0.99999999999999933;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1134";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999956 3 0.99999999999999956 
		4.5 0.99999999999999956 6 0.99999999999999956 7.5 0.99999999999999956 9 0.99999999999999956 
		10 0.99999999999999956;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1408";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 2.932404808116428 3 2.932404808116428 
		4.5 2.7572218424211425 6 -27.852700260152005 7.5 -24.726579660705678 9 -23.132657948169065 
		10 -23.132657948169065;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.67561930418014526 0.87384974956512451 
		0.87384974956512451;
	setAttr -s 7 ".kiy[4:6]"  0.73725062608718872 0.48619610071182251 
		0.48619610071182251;
	setAttr -s 7 ".kox[0:6]"  1 0.99813556671142578 0.093182988464832306 
		0.67561930418014526 0.87384986877441406 0.87384992837905884 0.87384992837905884;
	setAttr -s 7 ".koy[0:6]"  0 -0.061036370694637299 -0.99564898014068604 
		0.73725062608718872 0.48619583249092102 0.48619577288627625 0.48619577288627625;
createNode animCurveTA -n "animCurveTA1409";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 -19.896786965356391 6 -29.881143392478613 
		7.5 -17.681198418649252 9 -16.073816940196291 10 -16.073816940196291;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.22860179841518402 0.87210321426391602 
		0.87210321426391602;
	setAttr -s 7 ".kiy[4:6]"  0.97352004051208496 0.48932191729545593 
		0.48932191729545593;
	setAttr -s 7 ".kox[0:6]"  1 0.14251287281513214 0.27579933404922485 
		0.22860179841518402 0.87210315465927124 0.87210339307785034 0.87210339307785034;
	setAttr -s 7 ".koy[0:6]"  0 -0.98979294300079346 -0.96121525764465332 
		0.97352004051208496 0.48932209610939026 0.4893215000629425 0.4893215000629425;
createNode animCurveTA -n "animCurveTA1410";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0.99874711512021563 6 -7.9406523337198056 
		7.5 -8.9359270709553513 9 -8.1235701635462814 10 -8.1235701635462814;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.94461679458618164 0.96206808090209961 
		0.96206808090209961;
	setAttr -s 7 ".kiy[4:6]"  -0.32817542552947998 0.2728094756603241 
		0.2728094756603241;
	setAttr -s 7 ".kox[0:6]"  1 0.94426149129867554 0.30517971515655518 
		0.94461679458618164 0.96206808090209961 0.96206796169281006 0.96206796169281006;
	setAttr -s 7 ".koy[0:6]"  0 0.32919642329216003 -0.95229476690292358 
		-0.32817542552947998 0.27280959486961365 0.27280983328819275 0.27280983328819275;
createNode animCurveTL -n "animCurveTL751";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.018070021209980833 3 0.018070021209980833 
		4.5 0.093784080176392337 6 0.037338941875032033 7.5 0.13168332137837399 9 0.099306330468311055 
		10 0.099306330468311055;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.46827518939971924 0.83938592672348022 
		0.83938592672348022;
	setAttr -s 7 ".kiy[4:6]"  0.8835827112197876 -0.54353582859039307 
		-0.54353582859039307;
	setAttr -s 7 ".kox[0:6]"  1 0.55106270313262939 0.66307783126831055 
		0.46827518939971924 0.83938592672348022 0.83938592672348022 0.83938592672348022;
	setAttr -s 7 ".koy[0:6]"  0 0.83446383476257324 -0.7485504150390625 
		0.8835827112197876 -0.54353588819503784 -0.54353582859039307 -0.54353582859039307;
createNode animCurveTL -n "animCurveTL752";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.029511160393227057 3 -0.029511160393227057 
		4.5 -0.056479754719149622 6 -0.040772268012696539 7.5 -0.015346910119111393 9 0.0014219409285032951 
		10 0.0014219409285032951;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.8913733959197998 0.94810038805007935 
		0.94810038805007935;
	setAttr -s 7 ".kiy[4:6]"  0.45326977968215942 0.31797111034393311 
		0.31797111034393311;
	setAttr -s 7 ".kox[0:6]"  1 0.88013643026351929 0.95403081178665161 
		0.8913733959197998 0.94810038805007935 0.94810038805007935 0.94810038805007935;
	setAttr -s 7 ".koy[0:6]"  0 -0.47472080588340759 0.29970854520797729 
		0.45326977968215942 0.31797111034393311 0.31797111034393311 0.31797111034393311;
createNode animCurveTL -n "animCurveTL753";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.00050263996420009459 3 0.00050263996420009459 
		4.5 -0.026397757909710686 6 -0.029599939002876861 7.5 -0.028638391711151619 9 -0.031914775947536098 
		10 -0.031914775947536098;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.99981510639190674 0.99785995483398438 
		0.99785995483398438;
	setAttr -s 7 ".kiy[4:6]"  0.019227391108870506 -0.065387465059757233 
		-0.065387465059757233;
	setAttr -s 7 ".kox[0:6]"  1 0.88063782453536987 0.99795550107955933 
		0.99981510639190674 0.99785995483398438 0.99785995483398438 0.99785995483398438;
	setAttr -s 7 ".koy[0:6]"  0 -0.47379010915756226 -0.063912689685821533 
		0.019227391108870506 -0.065387427806854248 -0.065387383103370667 -0.065387383103370667;
createNode animCurveTA -n "animCurveTA1411";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1412";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1413";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1414";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1415";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1416";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1417";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1418";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1419";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1420";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1421";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1422";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1423";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1424";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1425";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1426";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1427";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1428";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1429";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1430";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1431";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1432";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1433";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1434";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1135";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999978 9 0.99999999999999978 
		10 0.99999999999999978;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[1:2]"  9 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode animCurveTU -n "animCurveTU1136";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999978 9 0.99999999999999978 
		10 0.99999999999999978;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[1:2]"  9 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode animCurveTU -n "animCurveTU1137";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 9 1 10 1;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[1:2]"  9 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode animCurveTA -n "animCurveTA1435";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -8.8461353916935046 3 8.8302317126502619 
		6 -14.690962840714434 9 -14.405849322159229 10 -14.405849322159229;
	setAttr -s 5 ".kit[3:4]"  1 1;
	setAttr -s 5 ".kot[0:4]"  1 9 9 9 1;
	setAttr -s 5 ".kix[3:4]"  0.66405904293060303 0.66405904293060303;
	setAttr -s 5 ".kiy[3:4]"  0.74768006801605225 0.74768006801605225;
	setAttr -s 5 ".kox[0:4]"  0.30834412574768066 0.89081472158432007 
		0.44230079650878906 0.99930429458618164 0.99876421689987183;
	setAttr -s 5 ".koy[0:4]"  0.9512748122215271 -0.45436662435531616 
		-0.89686679840087891 0.037295304238796234 0.049700196832418442;
createNode animCurveTA -n "animCurveTA1436";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -10.558746121377578 3 -38.061727074543896 
		6 1.0733154324927088 9 0.50589782665213989 10 0.50589782665213989;
	setAttr -s 5 ".kit[3:4]"  1 1;
	setAttr -s 5 ".kot[0:4]"  1 9 9 9 1;
	setAttr -s 5 ".kix[3:4]"  0.44185525178909302 0.44185525178909302;
	setAttr -s 5 ".kiy[3:4]"  -0.89708632230758667 -0.89708632230758667;
	setAttr -s 5 ".kox[0:4]"  0.20394712686538696 0.70179235935211182 
		0.2848128080368042 0.99725300073623657 0.9951319694519043;
	setAttr -s 5 ".koy[0:4]"  -0.97898191213607788 0.71238154172897339 
		0.95858311653137207 -0.074070751667022705 -0.098550945520401001;
createNode animCurveTA -n "animCurveTA1437";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -27.029421236799305 3 -34.570209519885424 
		6 -26.774784610774564 9 -26.787205908927874 10 -26.787205908927874;
	setAttr -s 5 ".kit[3:4]"  1 1;
	setAttr -s 5 ".kot[0:4]"  1 9 9 9 1;
	setAttr -s 5 ".kix[3:4]"  0.96416878700256348 0.96416878700256348;
	setAttr -s 5 ".kiy[3:4]"  -0.2652895450592041 -0.2652895450592041;
	setAttr -s 5 ".kox[0:4]"  0.60498815774917603 0.99975317716598511 
		0.82723599672317505 0.99999868869781494 0.99999761581420898;
	setAttr -s 5 ".koy[0:4]"  -0.79623448848724365 0.022215751931071281 
		0.56185466051101685 -0.0016259419498965144 -0.0021679201163351536;
createNode animCurveTU -n "animCurveTU1138";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999989 9 0.99999999999999989 
		10 0.99999999999999989;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[1:2]"  9 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode animCurveTU -n "animCurveTU1139";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 9 1 10 1;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[1:2]"  9 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode animCurveTU -n "animCurveTU1140";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999989 9 0.99999999999999989 
		10 0.99999999999999989;
	setAttr -s 3 ".kit[0:2]"  9 1 1;
	setAttr -s 3 ".kot[1:2]"  9 1;
	setAttr -s 3 ".kix[1:2]"  1 1;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode animCurveTA -n "animCurveTA1438";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -9.7900007771411719 3 14.84356905337205 
		6 -8.1937943685876942 9 -8.2716580915893516 10 -8.2716580915893516;
	setAttr -s 5 ".kit[3:4]"  1 1;
	setAttr -s 5 ".kot[0:4]"  1 9 9 9 1;
	setAttr -s 5 ".kix[3:4]"  0.66898691654205322 0.66898691654205322;
	setAttr -s 5 ".kiy[3:4]"  0.74327421188354492 0.74327421188354492;
	setAttr -s 5 ".kox[0:4]"  0.2265450656414032 0.99043732881546021 
		0.44415801763534546 0.99994814395904541 0.99990767240524292;
	setAttr -s 5 ".koy[0:4]"  0.97400075197219849 0.13796325027942657 
		-0.89594841003417969 -0.010191808454692364 -0.013588528148829937;
createNode animCurveTA -n "animCurveTA1439";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 6.4805770496356896 3 -33.752428620423444 
		6 3.5081226989801051 9 3.6531204642780541 10 3.6531204642780541;
	setAttr -s 5 ".kit[3:4]"  1 1;
	setAttr -s 5 ".kot[0:4]"  1 9 9 9 1;
	setAttr -s 5 ".kix[3:4]"  0.46445193886756897 0.46445193886756897;
	setAttr -s 5 ".kiy[3:4]"  -0.88559830188751221 -0.88559830188751221;
	setAttr -s 5 ".kox[0:4]"  0.14098742604255676 0.96796482801437378 
		0.29291242361068726 0.99981993436813354 0.99967992305755615;
	setAttr -s 5 ".koy[0:4]"  -0.99001145362854004 -0.2510857880115509 
		0.95613932609558105 0.018976744264364243 0.02529878169298172;
createNode animCurveTA -n "animCurveTA1440";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -28.534785159741237 3 -34.810263829813969 
		6 -28.821945343192926 9 -28.807937530129671 10 -28.807937530129671;
	setAttr -s 5 ".kit[3:4]"  1 1;
	setAttr -s 5 ".kot[0:4]"  1 9 9 9 1;
	setAttr -s 5 ".kix[3:4]"  0.98071056604385376 0.98071056604385376;
	setAttr -s 5 ".kiy[3:4]"  -0.19546552002429962 -0.19546552002429962;
	setAttr -s 5 ".kox[0:4]"  0.6742560863494873 0.99968612194061279 
		0.88583439588546753 0.99999833106994629 0.99999701976776123;
	setAttr -s 5 ".koy[0:4]"  -0.73849755525588989 -0.025051586329936981 
		0.46400159597396851 0.0018336153589189053 0.0024448169860988855;
createNode animCurveTA -n "animCurveTA1441";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1442";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1443";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL754";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL755";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL756";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1141";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 3 0.99999999999999978 
		4.5 0.99999999999999978 6 0.99999999999999978 7.5 0.99999999999999978 9 0.99999999999999978 
		10 0.99999999999999978;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1142";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999989 3 0.99999999999999989 
		4.5 0.99999999999999989 6 0.99999999999999989 7.5 0.99999999999999989 9 0.99999999999999989 
		10 0.99999999999999989;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1143";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.0000000000000002 3 1.0000000000000002 
		4.5 1.0000000000000002 6 1.0000000000000002 7.5 1.0000000000000002 9 1.0000000000000002 
		10 1.0000000000000002;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1444";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -13.463662348216772 3 -13.463662348216772 
		4.5 -13.463662348216772 6 -13.463662348216772 7.5 -11.668401400807454 9 -11.668401400807454 
		10 -11.668401400807454;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.84736382961273193 1 1;
	setAttr -s 7 ".kiy[4:6]"  0.53101271390914917 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 0.84736382961273193 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0.53101271390914917 0 0 0;
createNode animCurveTA -n "animCurveTA1445";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1446";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL757";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL758";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL759";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1144";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 10 3 10 4.5 10 6 10 7.5 10 9 10 10 10;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1145";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999989 3 0.99999999999999989 
		4.5 0.99999999999999989 6 0.99999999999999989 7.5 0.99999999999999989 9 0.99999999999999989 
		10 0.99999999999999989;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1146";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 4.5 1 6 1 7.5 1 9 1 10 1;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1147";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 4.5 1 6 1 7.5 1 9 1 10 1;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1447";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -11.733703531610509 1.5 -8.0333082911297247 
		3 -23.845730250059223 4.5 -31.658530587650915 6 24.456455684647647 7.5 57.407975882768142 
		9 65.8063487959068 10 65.8063487959068;
	setAttr -s 8 ".kit[0:7]"  3 2 1 1 1 1 1 1;
	setAttr -s 8 ".kot[1:7]"  2 1 1 1 1 1 1;
	setAttr -s 8 ".kix[2:7]"  0.95454752445220947 0.86813837289810181 
		0.10202382504940033 0.26028749346733093 0.38137093186378479 0.38137093186378479;
	setAttr -s 8 ".kiy[2:7]"  0.29805865883827209 0.49632230401039124 
		0.9947819709777832 0.96553117036819458 0.92442214488983154 0.92442214488983154;
	setAttr -s 8 ".kox[0:7]"  1 0.17827117443084717 0.95454758405685425 
		0.86813831329345703 0.10202382504940033 0.26028755307197571 0.38137084245681763 0.38137084245681763;
	setAttr -s 8 ".koy[0:7]"  0 -0.9839814305305481 0.29805868864059448 
		0.49632233381271362 0.99478191137313843 0.9655311107635498 0.92442208528518677 0.92442208528518677;
createNode animCurveTA -n "animCurveTA1448";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -3.6764156790093838 1.5 -0.78978953227095272 
		3 2.0598491512770467 4.5 -3.1695036271036177 6 -4.7029111769396543 7.5 -5.5173761485150239 
		9 -5.1119706126471209 10 -5.1119706126471209;
	setAttr -s 8 ".kit[0:7]"  3 2 3 1 1 1 1 1;
	setAttr -s 8 ".kot[1:7]"  2 3 1 1 1 1 1;
	setAttr -s 8 ".kix[3:7]"  0.50374358892440796 0.99871724843978882 
		0.99895626306533813 0.97780066728591919 0.97780066728591919;
	setAttr -s 8 ".kiy[3:7]"  -0.86385315656661987 -0.050634764134883881 
		0.045676611363887787 0.20953716337680817 0.20953716337680817;
	setAttr -s 8 ".kox[0:7]"  1 0.70897907018661499 1 0.50374358892440796 
		0.99871724843978882 0.99895626306533813 0.97780066728591919 0.97780066728591919;
	setAttr -s 8 ".koy[0:7]"  0 0.70522958040237427 0 -0.86385321617126465 
		-0.050634764134883881 0.045676730573177338 0.20953716337680817 0.20953716337680817;
createNode animCurveTA -n "animCurveTA1449";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.93306364833274735 1.5 -0.92574589071159719 
		3 -1.347770076187407 4.5 -2.8146410335004455 6 5.8209148773225481 7.5 6.590888169869161 
		9 6.8911930377983373 10 6.8911930377983373;
	setAttr -s 8 ".kit[0:7]"  3 2 1 1 9 1 1 1;
	setAttr -s 8 ".kot[1:7]"  2 1 1 9 1 1 1;
	setAttr -s 8 ".kix[2:7]"  0.99128633737564087 0.73698931932449341 
		0.52024322748184204 0.9959334135055542 0.99192345142364502 0.99192345142364502;
	setAttr -s 8 ".kiy[2:7]"  -0.13172441720962524 0.67590445280075073 
		0.85401809215545654 0.090092189610004425 0.12683796882629395 0.12683796882629395;
	setAttr -s 8 ".kox[0:7]"  1 0.98932278156280518 0.99128639698028564 
		0.73698931932449341 0.52024322748184204 0.9959334135055542 0.99192345142364502 0.99192345142364502;
	setAttr -s 8 ".koy[0:7]"  0 -0.14574131369590759 -0.13172441720962524 
		0.67590439319610596 0.85401809215545654 0.090092182159423828 0.12683799862861633 
		0.12683799862861633;
createNode animCurveTL -n "animCurveTL760";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 2.4651903288156619e-032 3 0 4.5 2.4651903288156619e-032 
		6 2.4651903288156619e-032 7.5 -0.003199087635962512 9 -0.003199087635962512 10 -0.003199087635962512;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.9979594349861145 1 1;
	setAttr -s 7 ".kiy[4:6]"  -0.063851200044155121 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 0.9979594349861145 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 -0.063851200044155121 0 0 0;
createNode animCurveTL -n "animCurveTL761";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 2.2204460492503131e-016 3 0 4.5 2.2204460492503131e-016 
		6 2.2204460492503131e-016 7.5 0.057828495207515165 9 0.057828495207515165 10 0.057828495207515165;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.65404844284057617 1 1;
	setAttr -s 7 ".kiy[4:6]"  0.75645273923873901 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 0.65404844284057617 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0.75645273923873901 0 0 0;
createNode animCurveTL -n "animCurveTL762";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.1102230246251565e-016 3 0 4.5 1.1102230246251565e-016 
		6 1.1102230246251565e-016 7.5 0.0074129138537487819 9 0.0074129138537487819 10 0.0074129138537487819;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.98918765783309937 1 1;
	setAttr -s 7 ".kiy[4:6]"  0.14665526151657104 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 0.98918765783309937 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0.14665526151657104 0 0 0;
createNode animCurveTU -n "animCurveTU1148";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999967 3 0.99999999999999967 
		4.5 0.99999999999999967 6 0.99999999999999967 7.5 0.99999999999999967 9 0.99999999999999967 
		10 0.99999999999999967;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1149";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999933 3 0.99999999999999933 
		4.5 0.99999999999999933 6 0.99999999999999933 7.5 0.99999999999999933 9 0.99999999999999933 
		10 0.99999999999999933;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1150";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.99999999999999978 3 0.99999999999999978 
		4.5 0.99999999999999978 6 0.99999999999999978 7.5 0.99999999999999978 9 0.99999999999999978 
		10 0.99999999999999978;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1450";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -2.6270949091333513 3 -11.733164189793055 
		4.5 -2.6270949091333513 6 -2.6270949091333513 7.5 -5.9487848831383792 9 -5.9487848831383792 
		10 -5.9487848831383792;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.65310478210449219 1 1;
	setAttr -s 7 ".kiy[4:6]"  -0.7572675347328186 0 0;
	setAttr -s 7 ".kox[0:6]"  0.53255546092987061 0.30010131001472473 
		1 0.65310478210449219 1 1 1;
	setAttr -s 7 ".koy[0:6]"  -0.84639513492584229 0.953907310962677 
		0 -0.7572675347328186 0 0 0;
createNode animCurveTA -n "animCurveTA1451";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 -0.14708646589732674 4.5 0 6 0 7.5 
		0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.99967062473297119 0.99868452548980713 
		1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  -0.025662975385785103 0.05127532035112381 
		0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1452";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 -0.072879869102526529 4.5 0 6 0 7.5 
		0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.99991917610168457 0.99967658519744873 
		1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  -0.012718906626105309 0.025431642308831215 
		0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1151";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 7 1 9 0.0001 10 0.0001;
	setAttr -s 4 ".kit[0:3]"  2 16 1 1;
	setAttr -s 4 ".kot[1:3]"  16 1 1;
	setAttr -s 4 ".kix[2:3]"  1 1;
	setAttr -s 4 ".kiy[2:3]"  0 0;
	setAttr -s 4 ".kox[0:3]"  1 1 1 1;
	setAttr -s 4 ".koy[0:3]"  0 0 0 0;
createNode animCurveTU -n "animCurveTU1152";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 7 1 9 0.0001 10 0.0001;
	setAttr -s 4 ".kit[0:3]"  2 16 1 1;
	setAttr -s 4 ".kot[1:3]"  16 1 1;
	setAttr -s 4 ".kix[2:3]"  1 1;
	setAttr -s 4 ".kiy[2:3]"  0 0;
	setAttr -s 4 ".kox[0:3]"  1 1 1 1;
	setAttr -s 4 ".koy[0:3]"  0 0 0 0;
createNode animCurveTU -n "animCurveTU1153";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 7 1 9 0.0001 10 0.0001;
	setAttr -s 4 ".kit[0:3]"  2 16 1 1;
	setAttr -s 4 ".kot[1:3]"  16 1 1;
	setAttr -s 4 ".kix[2:3]"  1 1;
	setAttr -s 4 ".kiy[2:3]"  0 0;
	setAttr -s 4 ".kox[0:3]"  1 1 1 1;
	setAttr -s 4 ".koy[0:3]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1453";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1454";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1455";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL763";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL764";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL765";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 4.5 0 6 0 7.5 0 9 0 10 0;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU1154";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 3 1 4.5 1 6 1 7.5 1 9 1 10 1;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[0:6]"  1 2 2 2 1 1 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
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
connectAttr "clip00Source.cl" "clipLibrary1.sc[0]";
connectAttr "animCurveTU1049.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "animCurveTA1341.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "animCurveTA1342.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "animCurveTA1343.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "animCurveTL697.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "animCurveTL698.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "animCurveTL699.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "animCurveTU1050.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "animCurveTU1051.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "animCurveTU1052.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "animCurveTU1053.a" "clipLibrary1.cel[0].cev[10].cevr";
connectAttr "animCurveTA1344.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "animCurveTA1345.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "animCurveTA1346.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "animCurveTU1054.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "animCurveTU1055.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "animCurveTU1056.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "animCurveTU1057.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "animCurveTU1058.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "animCurveTU1059.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "animCurveTU1060.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "animCurveTU1061.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "animCurveTU1062.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "animCurveTU1063.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "animCurveTU1064.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "animCurveTU1065.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "animCurveTU1066.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "animCurveTU1067.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "animCurveTU1068.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "animCurveTU1069.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "animCurveTU1070.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "animCurveTU1071.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "animCurveTU1072.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "animCurveTL700.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "animCurveTL701.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "animCurveTL702.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "animCurveTA1347.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "animCurveTA1348.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "animCurveTA1349.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "animCurveTA1350.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "animCurveTU1073.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "animCurveTU1074.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "animCurveTU1075.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "animCurveTU1076.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "animCurveTU1077.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "animCurveTU1078.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "animCurveTU1079.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "animCurveTU1080.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "animCurveTA1351.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "animCurveTA1352.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "animCurveTA1353.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "animCurveTL703.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "animCurveTL704.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "animCurveTL705.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "animCurveTU1081.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "animCurveTL706.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "animCurveTL707.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "animCurveTL708.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "animCurveTA1354.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "animCurveTA1355.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "animCurveTA1356.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "animCurveTA1357.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "animCurveTU1082.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "animCurveTU1083.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "animCurveTU1084.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "animCurveTU1085.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr "animCurveTU1086.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "animCurveTU1087.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "animCurveTU1088.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "animCurveTU1089.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "animCurveTA1358.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "animCurveTA1359.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "animCurveTA1360.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "animCurveTL709.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "animCurveTL710.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "animCurveTL711.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "animCurveTU1090.a" "clipLibrary1.cel[0].cev[158].cevr";
connectAttr "animCurveTL712.a" "clipLibrary1.cel[0].cev[159].cevr";
connectAttr "animCurveTL713.a" "clipLibrary1.cel[0].cev[160].cevr";
connectAttr "animCurveTL714.a" "clipLibrary1.cel[0].cev[161].cevr";
connectAttr "animCurveTA1361.a" "clipLibrary1.cel[0].cev[165].cevr";
connectAttr "animCurveTA1362.a" "clipLibrary1.cel[0].cev[169].cevr";
connectAttr "animCurveTA1363.a" "clipLibrary1.cel[0].cev[170].cevr";
connectAttr "animCurveTA1364.a" "clipLibrary1.cel[0].cev[171].cevr";
connectAttr "animCurveTU1091.a" "clipLibrary1.cel[0].cev[175].cevr";
connectAttr "animCurveTU1092.a" "clipLibrary1.cel[0].cev[176].cevr";
connectAttr "animCurveTU1093.a" "clipLibrary1.cel[0].cev[177].cevr";
connectAttr "animCurveTU1094.a" "clipLibrary1.cel[0].cev[178].cevr";
connectAttr "animCurveTU1095.a" "clipLibrary1.cel[0].cev[179].cevr";
connectAttr "animCurveTU1096.a" "clipLibrary1.cel[0].cev[180].cevr";
connectAttr "animCurveTU1097.a" "clipLibrary1.cel[0].cev[181].cevr";
connectAttr "animCurveTU1098.a" "clipLibrary1.cel[0].cev[182].cevr";
connectAttr "animCurveTA1365.a" "clipLibrary1.cel[0].cev[183].cevr";
connectAttr "animCurveTA1366.a" "clipLibrary1.cel[0].cev[184].cevr";
connectAttr "animCurveTA1367.a" "clipLibrary1.cel[0].cev[185].cevr";
connectAttr "animCurveTL715.a" "clipLibrary1.cel[0].cev[186].cevr";
connectAttr "animCurveTL716.a" "clipLibrary1.cel[0].cev[187].cevr";
connectAttr "animCurveTL717.a" "clipLibrary1.cel[0].cev[188].cevr";
connectAttr "animCurveTU1099.a" "clipLibrary1.cel[0].cev[195].cevr";
connectAttr "animCurveTU1100.a" "clipLibrary1.cel[0].cev[196].cevr";
connectAttr "animCurveTU1101.a" "clipLibrary1.cel[0].cev[197].cevr";
connectAttr "animCurveTA1368.a" "clipLibrary1.cel[0].cev[198].cevr";
connectAttr "animCurveTA1369.a" "clipLibrary1.cel[0].cev[199].cevr";
connectAttr "animCurveTA1370.a" "clipLibrary1.cel[0].cev[200].cevr";
connectAttr "animCurveTL718.a" "clipLibrary1.cel[0].cev[201].cevr";
connectAttr "animCurveTL719.a" "clipLibrary1.cel[0].cev[202].cevr";
connectAttr "animCurveTL720.a" "clipLibrary1.cel[0].cev[203].cevr";
connectAttr "animCurveTU1102.a" "clipLibrary1.cel[0].cev[214].cevr";
connectAttr "animCurveTL721.a" "clipLibrary1.cel[0].cev[215].cevr";
connectAttr "animCurveTL722.a" "clipLibrary1.cel[0].cev[216].cevr";
connectAttr "animCurveTL723.a" "clipLibrary1.cel[0].cev[217].cevr";
connectAttr "animCurveTU1103.a" "clipLibrary1.cel[0].cev[228].cevr";
connectAttr "animCurveTL724.a" "clipLibrary1.cel[0].cev[229].cevr";
connectAttr "animCurveTL725.a" "clipLibrary1.cel[0].cev[230].cevr";
connectAttr "animCurveTL726.a" "clipLibrary1.cel[0].cev[231].cevr";
connectAttr "animCurveTU1104.a" "clipLibrary1.cel[0].cev[242].cevr";
connectAttr "animCurveTL727.a" "clipLibrary1.cel[0].cev[243].cevr";
connectAttr "animCurveTL728.a" "clipLibrary1.cel[0].cev[244].cevr";
connectAttr "animCurveTL729.a" "clipLibrary1.cel[0].cev[245].cevr";
connectAttr "animCurveTA1371.a" "clipLibrary1.cel[0].cev[249].cevr";
connectAttr "animCurveTA1372.a" "clipLibrary1.cel[0].cev[253].cevr";
connectAttr "animCurveTA1373.a" "clipLibrary1.cel[0].cev[254].cevr";
connectAttr "animCurveTA1374.a" "clipLibrary1.cel[0].cev[255].cevr";
connectAttr "animCurveTU1105.a" "clipLibrary1.cel[0].cev[259].cevr";
connectAttr "animCurveTU1106.a" "clipLibrary1.cel[0].cev[260].cevr";
connectAttr "animCurveTU1107.a" "clipLibrary1.cel[0].cev[261].cevr";
connectAttr "animCurveTU1108.a" "clipLibrary1.cel[0].cev[262].cevr";
connectAttr "animCurveTU1109.a" "clipLibrary1.cel[0].cev[263].cevr";
connectAttr "animCurveTU1110.a" "clipLibrary1.cel[0].cev[264].cevr";
connectAttr "animCurveTU1111.a" "clipLibrary1.cel[0].cev[265].cevr";
connectAttr "animCurveTU1112.a" "clipLibrary1.cel[0].cev[266].cevr";
connectAttr "animCurveTA1375.a" "clipLibrary1.cel[0].cev[267].cevr";
connectAttr "animCurveTA1376.a" "clipLibrary1.cel[0].cev[268].cevr";
connectAttr "animCurveTA1377.a" "clipLibrary1.cel[0].cev[269].cevr";
connectAttr "animCurveTL730.a" "clipLibrary1.cel[0].cev[270].cevr";
connectAttr "animCurveTL731.a" "clipLibrary1.cel[0].cev[271].cevr";
connectAttr "animCurveTL732.a" "clipLibrary1.cel[0].cev[272].cevr";
connectAttr "animCurveTA1378.a" "clipLibrary1.cel[0].cev[279].cevr";
connectAttr "animCurveTA1379.a" "clipLibrary1.cel[0].cev[280].cevr";
connectAttr "animCurveTA1380.a" "clipLibrary1.cel[0].cev[281].cevr";
connectAttr "animCurveTA1381.a" "clipLibrary1.cel[0].cev[282].cevr";
connectAttr "animCurveTA1382.a" "clipLibrary1.cel[0].cev[283].cevr";
connectAttr "animCurveTA1383.a" "clipLibrary1.cel[0].cev[284].cevr";
connectAttr "animCurveTL733.a" "clipLibrary1.cel[0].cev[285].cevr";
connectAttr "animCurveTL734.a" "clipLibrary1.cel[0].cev[286].cevr";
connectAttr "animCurveTL735.a" "clipLibrary1.cel[0].cev[287].cevr";
connectAttr "animCurveTA1384.a" "clipLibrary1.cel[0].cev[288].cevr";
connectAttr "animCurveTA1385.a" "clipLibrary1.cel[0].cev[289].cevr";
connectAttr "animCurveTA1386.a" "clipLibrary1.cel[0].cev[290].cevr";
connectAttr "animCurveTL736.a" "clipLibrary1.cel[0].cev[291].cevr";
connectAttr "animCurveTL737.a" "clipLibrary1.cel[0].cev[292].cevr";
connectAttr "animCurveTL738.a" "clipLibrary1.cel[0].cev[293].cevr";
connectAttr "animCurveTU1113.a" "clipLibrary1.cel[0].cev[294].cevr";
connectAttr "animCurveTU1114.a" "clipLibrary1.cel[0].cev[295].cevr";
connectAttr "animCurveTU1115.a" "clipLibrary1.cel[0].cev[296].cevr";
connectAttr "animCurveTA1387.a" "clipLibrary1.cel[0].cev[297].cevr";
connectAttr "animCurveTA1388.a" "clipLibrary1.cel[0].cev[298].cevr";
connectAttr "animCurveTA1389.a" "clipLibrary1.cel[0].cev[299].cevr";
connectAttr "animCurveTU1116.a" "clipLibrary1.cel[0].cev[303].cevr";
connectAttr "animCurveTU1117.a" "clipLibrary1.cel[0].cev[304].cevr";
connectAttr "animCurveTU1118.a" "clipLibrary1.cel[0].cev[305].cevr";
connectAttr "animCurveTA1390.a" "clipLibrary1.cel[0].cev[306].cevr";
connectAttr "animCurveTA1391.a" "clipLibrary1.cel[0].cev[307].cevr";
connectAttr "animCurveTA1392.a" "clipLibrary1.cel[0].cev[308].cevr";
connectAttr "animCurveTU1119.a" "clipLibrary1.cel[0].cev[312].cevr";
connectAttr "animCurveTU1120.a" "clipLibrary1.cel[0].cev[313].cevr";
connectAttr "animCurveTU1121.a" "clipLibrary1.cel[0].cev[314].cevr";
connectAttr "animCurveTA1393.a" "clipLibrary1.cel[0].cev[315].cevr";
connectAttr "animCurveTA1394.a" "clipLibrary1.cel[0].cev[316].cevr";
connectAttr "animCurveTA1395.a" "clipLibrary1.cel[0].cev[317].cevr";
connectAttr "animCurveTU1122.a" "clipLibrary1.cel[0].cev[321].cevr";
connectAttr "animCurveTA1396.a" "clipLibrary1.cel[0].cev[322].cevr";
connectAttr "animCurveTA1397.a" "clipLibrary1.cel[0].cev[323].cevr";
connectAttr "animCurveTA1398.a" "clipLibrary1.cel[0].cev[324].cevr";
connectAttr "animCurveTL739.a" "clipLibrary1.cel[0].cev[325].cevr";
connectAttr "animCurveTL740.a" "clipLibrary1.cel[0].cev[326].cevr";
connectAttr "animCurveTL741.a" "clipLibrary1.cel[0].cev[327].cevr";
connectAttr "animCurveTU1123.a" "clipLibrary1.cel[0].cev[361].cevr";
connectAttr "animCurveTU1124.a" "clipLibrary1.cel[0].cev[362].cevr";
connectAttr "animCurveTU1125.a" "clipLibrary1.cel[0].cev[363].cevr";
connectAttr "animCurveTA1399.a" "clipLibrary1.cel[0].cev[364].cevr";
connectAttr "animCurveTA1400.a" "clipLibrary1.cel[0].cev[365].cevr";
connectAttr "animCurveTA1401.a" "clipLibrary1.cel[0].cev[366].cevr";
connectAttr "animCurveTL742.a" "clipLibrary1.cel[0].cev[367].cevr";
connectAttr "animCurveTL743.a" "clipLibrary1.cel[0].cev[368].cevr";
connectAttr "animCurveTL744.a" "clipLibrary1.cel[0].cev[369].cevr";
connectAttr "animCurveTU1126.a" "clipLibrary1.cel[0].cev[406].cevr";
connectAttr "animCurveTU1127.a" "clipLibrary1.cel[0].cev[407].cevr";
connectAttr "animCurveTU1128.a" "clipLibrary1.cel[0].cev[408].cevr";
connectAttr "animCurveTA1402.a" "clipLibrary1.cel[0].cev[409].cevr";
connectAttr "animCurveTA1403.a" "clipLibrary1.cel[0].cev[410].cevr";
connectAttr "animCurveTA1404.a" "clipLibrary1.cel[0].cev[411].cevr";
connectAttr "animCurveTL745.a" "clipLibrary1.cel[0].cev[412].cevr";
connectAttr "animCurveTL746.a" "clipLibrary1.cel[0].cev[413].cevr";
connectAttr "animCurveTL747.a" "clipLibrary1.cel[0].cev[414].cevr";
connectAttr "animCurveTU1129.a" "clipLibrary1.cel[0].cev[505].cevr";
connectAttr "animCurveTU1130.a" "clipLibrary1.cel[0].cev[506].cevr";
connectAttr "animCurveTU1131.a" "clipLibrary1.cel[0].cev[507].cevr";
connectAttr "animCurveTA1405.a" "clipLibrary1.cel[0].cev[508].cevr";
connectAttr "animCurveTA1406.a" "clipLibrary1.cel[0].cev[509].cevr";
connectAttr "animCurveTA1407.a" "clipLibrary1.cel[0].cev[510].cevr";
connectAttr "animCurveTL748.a" "clipLibrary1.cel[0].cev[511].cevr";
connectAttr "animCurveTL749.a" "clipLibrary1.cel[0].cev[512].cevr";
connectAttr "animCurveTL750.a" "clipLibrary1.cel[0].cev[513].cevr";
connectAttr "animCurveTU1132.a" "clipLibrary1.cel[0].cev[550].cevr";
connectAttr "animCurveTU1133.a" "clipLibrary1.cel[0].cev[551].cevr";
connectAttr "animCurveTU1134.a" "clipLibrary1.cel[0].cev[552].cevr";
connectAttr "animCurveTA1408.a" "clipLibrary1.cel[0].cev[553].cevr";
connectAttr "animCurveTA1409.a" "clipLibrary1.cel[0].cev[554].cevr";
connectAttr "animCurveTA1410.a" "clipLibrary1.cel[0].cev[555].cevr";
connectAttr "animCurveTL751.a" "clipLibrary1.cel[0].cev[556].cevr";
connectAttr "animCurveTL752.a" "clipLibrary1.cel[0].cev[557].cevr";
connectAttr "animCurveTL753.a" "clipLibrary1.cel[0].cev[558].cevr";
connectAttr "animCurveTA1411.a" "clipLibrary1.cel[0].cev[568].cevr";
connectAttr "animCurveTA1412.a" "clipLibrary1.cel[0].cev[569].cevr";
connectAttr "animCurveTA1413.a" "clipLibrary1.cel[0].cev[570].cevr";
connectAttr "animCurveTA1414.a" "clipLibrary1.cel[0].cev[571].cevr";
connectAttr "animCurveTA1415.a" "clipLibrary1.cel[0].cev[572].cevr";
connectAttr "animCurveTA1416.a" "clipLibrary1.cel[0].cev[573].cevr";
connectAttr "animCurveTA1417.a" "clipLibrary1.cel[0].cev[574].cevr";
connectAttr "animCurveTA1418.a" "clipLibrary1.cel[0].cev[575].cevr";
connectAttr "animCurveTA1419.a" "clipLibrary1.cel[0].cev[576].cevr";
connectAttr "animCurveTA1420.a" "clipLibrary1.cel[0].cev[577].cevr";
connectAttr "animCurveTA1421.a" "clipLibrary1.cel[0].cev[578].cevr";
connectAttr "animCurveTA1422.a" "clipLibrary1.cel[0].cev[579].cevr";
connectAttr "animCurveTA1423.a" "clipLibrary1.cel[0].cev[580].cevr";
connectAttr "animCurveTA1424.a" "clipLibrary1.cel[0].cev[581].cevr";
connectAttr "animCurveTA1425.a" "clipLibrary1.cel[0].cev[582].cevr";
connectAttr "animCurveTA1426.a" "clipLibrary1.cel[0].cev[583].cevr";
connectAttr "animCurveTA1427.a" "clipLibrary1.cel[0].cev[584].cevr";
connectAttr "animCurveTA1428.a" "clipLibrary1.cel[0].cev[585].cevr";
connectAttr "animCurveTA1429.a" "clipLibrary1.cel[0].cev[586].cevr";
connectAttr "animCurveTA1430.a" "clipLibrary1.cel[0].cev[587].cevr";
connectAttr "animCurveTA1431.a" "clipLibrary1.cel[0].cev[588].cevr";
connectAttr "animCurveTA1432.a" "clipLibrary1.cel[0].cev[589].cevr";
connectAttr "animCurveTA1433.a" "clipLibrary1.cel[0].cev[590].cevr";
connectAttr "animCurveTA1434.a" "clipLibrary1.cel[0].cev[591].cevr";
connectAttr "animCurveTU1135.a" "clipLibrary1.cel[0].cev[592].cevr";
connectAttr "animCurveTU1136.a" "clipLibrary1.cel[0].cev[593].cevr";
connectAttr "animCurveTU1137.a" "clipLibrary1.cel[0].cev[594].cevr";
connectAttr "animCurveTA1435.a" "clipLibrary1.cel[0].cev[595].cevr";
connectAttr "animCurveTA1436.a" "clipLibrary1.cel[0].cev[596].cevr";
connectAttr "animCurveTA1437.a" "clipLibrary1.cel[0].cev[597].cevr";
connectAttr "animCurveTU1138.a" "clipLibrary1.cel[0].cev[601].cevr";
connectAttr "animCurveTU1139.a" "clipLibrary1.cel[0].cev[602].cevr";
connectAttr "animCurveTU1140.a" "clipLibrary1.cel[0].cev[603].cevr";
connectAttr "animCurveTA1438.a" "clipLibrary1.cel[0].cev[604].cevr";
connectAttr "animCurveTA1439.a" "clipLibrary1.cel[0].cev[605].cevr";
connectAttr "animCurveTA1440.a" "clipLibrary1.cel[0].cev[606].cevr";
connectAttr "animCurveTA1441.a" "clipLibrary1.cel[0].cev[610].cevr";
connectAttr "animCurveTA1442.a" "clipLibrary1.cel[0].cev[611].cevr";
connectAttr "animCurveTA1443.a" "clipLibrary1.cel[0].cev[612].cevr";
connectAttr "animCurveTL754.a" "clipLibrary1.cel[0].cev[613].cevr";
connectAttr "animCurveTL755.a" "clipLibrary1.cel[0].cev[614].cevr";
connectAttr "animCurveTL756.a" "clipLibrary1.cel[0].cev[615].cevr";
connectAttr "animCurveTU1141.a" "clipLibrary1.cel[0].cev[616].cevr";
connectAttr "animCurveTU1142.a" "clipLibrary1.cel[0].cev[617].cevr";
connectAttr "animCurveTU1143.a" "clipLibrary1.cel[0].cev[618].cevr";
connectAttr "animCurveTA1444.a" "clipLibrary1.cel[0].cev[619].cevr";
connectAttr "animCurveTA1445.a" "clipLibrary1.cel[0].cev[620].cevr";
connectAttr "animCurveTA1446.a" "clipLibrary1.cel[0].cev[621].cevr";
connectAttr "animCurveTL757.a" "clipLibrary1.cel[0].cev[622].cevr";
connectAttr "animCurveTL758.a" "clipLibrary1.cel[0].cev[623].cevr";
connectAttr "animCurveTL759.a" "clipLibrary1.cel[0].cev[624].cevr";
connectAttr "animCurveTU1144.a" "clipLibrary1.cel[0].cev[634].cevr";
connectAttr "animCurveTU1145.a" "clipLibrary1.cel[0].cev[635].cevr";
connectAttr "animCurveTU1146.a" "clipLibrary1.cel[0].cev[636].cevr";
connectAttr "animCurveTU1147.a" "clipLibrary1.cel[0].cev[637].cevr";
connectAttr "animCurveTA1447.a" "clipLibrary1.cel[0].cev[638].cevr";
connectAttr "animCurveTA1448.a" "clipLibrary1.cel[0].cev[639].cevr";
connectAttr "animCurveTA1449.a" "clipLibrary1.cel[0].cev[640].cevr";
connectAttr "animCurveTL760.a" "clipLibrary1.cel[0].cev[641].cevr";
connectAttr "animCurveTL761.a" "clipLibrary1.cel[0].cev[642].cevr";
connectAttr "animCurveTL762.a" "clipLibrary1.cel[0].cev[643].cevr";
connectAttr "animCurveTU1148.a" "clipLibrary1.cel[0].cev[653].cevr";
connectAttr "animCurveTU1149.a" "clipLibrary1.cel[0].cev[654].cevr";
connectAttr "animCurveTU1150.a" "clipLibrary1.cel[0].cev[655].cevr";
connectAttr "animCurveTA1450.a" "clipLibrary1.cel[0].cev[656].cevr";
connectAttr "animCurveTA1451.a" "clipLibrary1.cel[0].cev[657].cevr";
connectAttr "animCurveTA1452.a" "clipLibrary1.cel[0].cev[658].cevr";
connectAttr "animCurveTU1151.a" "clipLibrary1.cel[0].cev[662].cevr";
connectAttr "animCurveTU1152.a" "clipLibrary1.cel[0].cev[663].cevr";
connectAttr "animCurveTU1153.a" "clipLibrary1.cel[0].cev[664].cevr";
connectAttr "animCurveTA1453.a" "clipLibrary1.cel[0].cev[665].cevr";
connectAttr "animCurveTA1454.a" "clipLibrary1.cel[0].cev[666].cevr";
connectAttr "animCurveTA1455.a" "clipLibrary1.cel[0].cev[667].cevr";
connectAttr "animCurveTL763.a" "clipLibrary1.cel[0].cev[668].cevr";
connectAttr "animCurveTL764.a" "clipLibrary1.cel[0].cev[669].cevr";
connectAttr "animCurveTL765.a" "clipLibrary1.cel[0].cev[670].cevr";
connectAttr "animCurveTU1154.a" "clipLibrary1.cel[0].cev[671].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of unsummonB.ma
