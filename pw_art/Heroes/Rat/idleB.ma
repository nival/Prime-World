//Maya ASCII 2008 scene
//Name: idle.ma
//Last modified: Wed, Aug 05, 2009 05:37:16 PM
//Codeset: 1251
requires maya "2008";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Complete 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200802250025-718075";
fileInfo "osv" "Microsoft Windows XP Service Pack 3 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 326 ".cel[0].cev";
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
createNode animClip -n "idle2Source";
	setAttr ".ihi" 0;
	setAttr -s 326 ".ac";
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
	setAttr ".ac[424:429]" yes yes yes yes yes yes;
	setAttr ".ac[433:438]" yes yes yes yes yes yes;
	setAttr ".ac[442:447]" yes yes yes yes yes yes;
	setAttr ".ac[451:456]" yes yes yes yes yes yes;
	setAttr ".ac[460:465]" yes yes yes yes yes yes;
	setAttr ".ac[469:474]" yes yes yes yes yes yes;
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
	setAttr ".se" 37;
	setAttr ".ci" no;
createNode animCurveTU -n "animCurveTU373";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 10 18.75 10 37 10;
createNode animCurveTA -n "animCurveTA400";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA401";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA402";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTL -n "animCurveTL208";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTL -n "animCurveTL209";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTL -n "animCurveTL210";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTU -n "animCurveTU374";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 1 18.75 1 37 1;
createNode animCurveTU -n "animCurveTU375";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 1 18.75 1 37 1;
createNode animCurveTU -n "animCurveTU376";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 1 18.75 1 37 1;
createNode animCurveTU -n "animCurveTU377";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA403";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA404";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA405";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTU -n "animCurveTU378";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 1 18.75 1 37 1;
createNode animCurveTU -n "animCurveTU379";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTU -n "animCurveTU380";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 10 18.75 10 37 10;
createNode animCurveTU -n "animCurveTU381";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 1 18.75 1 37 1;
createNode animCurveTU -n "animCurveTU382";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTU -n "animCurveTU383";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 10 18.75 10 37 10;
createNode animCurveTU -n "animCurveTU384";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 1 18.75 1 37 1;
createNode animCurveTU -n "animCurveTU385";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTU -n "animCurveTU386";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTU -n "animCurveTU387";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 1 18.75 1 37 1;
createNode animCurveTU -n "animCurveTU388";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTU -n "animCurveTU389";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 10 18.75 10 37 10;
createNode animCurveTU -n "animCurveTU390";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 1 18.75 1 37 1;
createNode animCurveTU -n "animCurveTU391";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTU -n "animCurveTU392";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 10 18.75 10 37 10;
createNode animCurveTU -n "animCurveTU393";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 1 18.75 1 37 1;
createNode animCurveTU -n "animCurveTU394";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTU -n "animCurveTU395";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 10 18.75 10 37 10;
createNode animCurveTU -n "animCurveTU396";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 10 18.75 10 37 10;
createNode animCurveTL -n "animCurveTL211";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0.0051987098671592413 18.75 0.0051987098671592413 
		37 0.0051987098671592413;
createNode animCurveTL -n "animCurveTL212";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 -0.0029658564141476066 18.75 -0.0029658564141476066 
		37 -0.0029658564141476066;
createNode animCurveTL -n "animCurveTL213";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 -0.088864011310046689 18.75 -0.088864011310046689 
		37 -0.088864011310046689;
createNode animCurveTA -n "animCurveTA406";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA407";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA408";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA409";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTU -n "animCurveTU397";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 1 18.75 1 37 1;
createNode animCurveTU -n "animCurveTU398";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 1 18.75 1 37 1;
createNode animCurveTU -n "animCurveTU399";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTU -n "animCurveTU400";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTU -n "animCurveTU401";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 10 18.75 10 37 10;
createNode animCurveTU -n "animCurveTU402";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 30 18.75 30 37 30;
createNode animCurveTU -n "animCurveTU403";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTU -n "animCurveTU404";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA410";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 10.65881532857289 18.75 10.65881532857289 
		37 10.65881532857289;
createNode animCurveTA -n "animCurveTA411";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA412";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTL -n "animCurveTL214";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTL -n "animCurveTL215";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 -0.055827347319821544 18.75 -0.055827347319821544 
		37 -0.055827347319821544;
createNode animCurveTL -n "animCurveTL216";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 -0.057269223867906088 18.75 -0.057269223867906088 
		37 -0.057269223867906088;
createNode animCurveTU -n "animCurveTU405";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 10 18.75 10 37 10;
createNode animCurveTL -n "animCurveTL217";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0.0012535188113739458 18.75 0.0012535188113739458 
		37 0.0012535188113739458;
createNode animCurveTL -n "animCurveTL218";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 -0.0030683908186687247 18.75 -0.0030683908186687247 
		37 -0.0030683908186687247;
createNode animCurveTL -n "animCurveTL219";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 -0.0037897911519002383 18.75 -0.0037897911519002383 
		37 -0.0037897911519002383;
createNode animCurveTA -n "animCurveTA413";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA414";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA415";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA416";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTU -n "animCurveTU406";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 1 18.75 1 37 1;
createNode animCurveTU -n "animCurveTU407";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 1 18.75 1 37 1;
createNode animCurveTU -n "animCurveTU408";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTU -n "animCurveTU409";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTU -n "animCurveTU410";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 10 18.75 10 37 10;
createNode animCurveTU -n "animCurveTU411";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 25 18.75 25 37 25;
createNode animCurveTU -n "animCurveTU412";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTU -n "animCurveTU413";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA417";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 -8.5560819804359109 18.75 -8.5560819804359109 
		37 -8.5560819804359109;
createNode animCurveTA -n "animCurveTA418";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 -0.31694341854885294 18.75 -0.31694341854885294 
		37 -0.31694341854885294;
createNode animCurveTA -n "animCurveTA419";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 -0.51931341167670197 18.75 -0.51931341167670197 
		37 -0.51931341167670197;
createNode animCurveTL -n "animCurveTL220";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0.00076651281650793874 18.75 0.00076651281650793874 
		37 0.00076651281650793874;
createNode animCurveTL -n "animCurveTL221";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0.27472958484748605 18.75 0.27472958484748605 
		37 0.27472958484748605;
createNode animCurveTL -n "animCurveTL222";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 -0.071005957816697135 18.75 -0.071005957816697135 
		37 -0.071005957816697135;
createNode animCurveTU -n "animCurveTU414";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 10 18.75 10 37 10;
createNode animCurveTL -n "animCurveTL223";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0.0054999194138878266 18.75 0.0054999194138878266 
		37 0.0054999194138878266;
createNode animCurveTL -n "animCurveTL224";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 -0.0031376960222415048 18.75 -0.0031376960222415048 
		37 -0.0031376960222415048;
createNode animCurveTL -n "animCurveTL225";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0.083911116250119933 18.75 0.083911116250119933 
		37 0.083911116250119933;
createNode animCurveTA -n "animCurveTA420";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA421";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA422";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA423";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTU -n "animCurveTU415";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU416";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU417";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU418";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU419";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 10;
createNode animCurveTU -n "animCurveTU420";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 30;
createNode animCurveTU -n "animCurveTU421";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU422";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA424";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 -9.8142060506602;
createNode animCurveTA -n "animCurveTA425";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA426";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL226";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL227";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 -0.26728461461584108;
createNode animCurveTL -n "animCurveTL228";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0.017033828181619803;
createNode animCurveTU -n "animCurveTU423";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU424";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU425";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA427";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA428";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA429";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL229";
	setAttr ".tan" 1;
	setAttr ".ktv[0]"  0 -0.77177341453224102;
	setAttr ".kix[0]"  0.4166666567325592;
	setAttr ".kiy[0]"  -0.77177339792251587;
	setAttr ".kox[0]"  1;
	setAttr ".koy[0]"  0;
createNode animCurveTL -n "animCurveTL230";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL231";
	setAttr ".tan" 1;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kix[0]"  0.4166666567325592;
	setAttr ".kiy[0]"  0.026503134518861771;
	setAttr ".kox[0]"  1;
	setAttr ".koy[0]"  0;
createNode animCurveTU -n "animCurveTU426";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL232";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 -0.75537025498543575;
createNode animCurveTL -n "animCurveTL233";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 -0.073475021782978711;
createNode animCurveTL -n "animCurveTL234";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0.15459877332636279;
createNode animCurveTU -n "animCurveTU427";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL235";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 -0.8594552290779115;
createNode animCurveTL -n "animCurveTL236";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL237";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 -0.14721316863839706;
createNode animCurveTU -n "animCurveTU428";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 10 18.75 10 37 10;
createNode animCurveTL -n "animCurveTL238";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 -0.0024830586491624029 18.75 -0.0024830586491624029 
		37 -0.0024830586491624029;
createNode animCurveTL -n "animCurveTL239";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0.0061262151441996713 18.75 0.0061262151441996713 
		37 0.0061262151441996713;
createNode animCurveTL -n "animCurveTL240";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 -0.027195247513723396 18.75 -0.027195247513723396 
		37 -0.027195247513723396;
createNode animCurveTA -n "animCurveTA430";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA431";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA432";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA433";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTU -n "animCurveTU429";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 1 18.75 1 37 1;
createNode animCurveTU -n "animCurveTU430";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 1 18.75 1 37 1;
createNode animCurveTU -n "animCurveTU431";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTU -n "animCurveTU432";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTU -n "animCurveTU433";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 10 18.75 10 37 10;
createNode animCurveTU -n "animCurveTU434";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 25 18.75 25 37 25;
createNode animCurveTU -n "animCurveTU435";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTU -n "animCurveTU436";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA434";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 10.555261301844832 18.75 10.555261301844832 
		37 10.555261301844832;
createNode animCurveTA -n "animCurveTA435";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA436";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTL -n "animCurveTL241";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTL -n "animCurveTL242";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0.38582961184709008 18.75 0.38582961184709008 
		37 0.38582961184709008;
createNode animCurveTL -n "animCurveTL243";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 -0.012835510537475885 18.75 -0.012835510537475885 
		37 -0.012835510537475885;
createNode animCurveTA -n "animCurveTA437";
	setAttr ".tan" 1;
	setAttr -s 7 ".ktv[0:6]"  0 -4.1272878036759 6.25 -6.0852057402191493 
		11.25 -10.015134861690393 18.75 -13.468020450854596 25 -11.820678469353659 31.25 
		-6.839054929983523 37 -4.1272878036759;
	setAttr -s 7 ".kit[0:6]"  3 1 1 9 1 1 3;
	setAttr -s 7 ".kot[0:6]"  3 1 1 9 1 1 3;
	setAttr -s 7 ".kix[1:6]"  0.20171301066875458 0.15923339128494263 
		0.25 0.19810299575328827 0.20460161566734314 0.19166672229766846;
	setAttr -s 7 ".kiy[1:6]"  -0.066882334649562836 -0.062178116291761398 
		-0.01718873530626297 0.072151601314544678 0.078589536249637604 0;
	setAttr -s 7 ".kox[1:6]"  0.16004684567451477 0.24256570637226105 
		0.20833331346511841 0.19810301065444946 0.20460167527198792 0.19166672229766846;
	setAttr -s 7 ".koy[1:6]"  -0.053066998720169067 -0.094718083739280701 
		-0.0143239451572299 0.072151601314544678 0.078589558601379395 0;
createNode animCurveTA -n "animCurveTA438";
	setAttr ".tan" 2;
	setAttr -s 6 ".ktv[0:5]"  0 -3.9401506072152763 6.25 -3.9183195477908361 
		18.75 -3.9308679633223984 25 -3.9317357713931922 31.25 -3.9444668849641205 37 -3.9401506072152763;
createNode animCurveTA -n "animCurveTA439";
	setAttr ".tan" 2;
	setAttr -s 6 ".ktv[0:5]"  0 1.5206250006361597 6.25 1.5112057276777493 
		18.75 1.519990401296631 25 1.5193293943803403 31.25 1.5239270215664427 37 1.5206250006361597;
createNode animCurveTA -n "animCurveTA440";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA441";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA442";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTL -n "animCurveTL244";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTL -n "animCurveTL245";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTL -n "animCurveTL246";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA443";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 7.8212153369064472;
createNode animCurveTA -n "animCurveTA444";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 -0.038068429571548837;
createNode animCurveTA -n "animCurveTA445";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0.027851559758348458;
createNode animCurveTL -n "animCurveTL247";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL248";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL249";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU437";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 1 37 1;
createNode animCurveTU -n "animCurveTU438";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999978 37 0.99999999999999978;
createNode animCurveTU -n "animCurveTU439";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999978 37 0.99999999999999978;
createNode animCurveTA -n "animCurveTA446";
	setAttr ".tan" 1;
	setAttr -s 7 ".ktv[0:6]"  0 4.922870201962569 5 3.2214991174723999 
		10 1.8259784584253524 16.25 1.4187578652291859 23.75 3.007586087359746 31.25 5.0926579834743126 
		37 4.9234188775959868;
	setAttr -s 7 ".kit[3:6]"  3 1 1 1;
	setAttr -s 7 ".kot[3:6]"  3 1 1 1;
	setAttr -s 7 ".kix[0:6]"  0.18111559748649597 0.081161290407180786 
		0.16275832056999207 0.2083333432674408 0.22086799144744873 0.2545035183429718 0.1931661069393158;
	setAttr -s 7 ".kiy[0:6]"  -0.024477075785398483 -0.014329255558550358 
		-0.015849463641643524 0 0.04132688045501709 0.017135761678218842 -0.021209262311458588;
	setAttr -s 7 ".kox[0:6]"  0.18111559748649597 0.1644940972328186 
		0.20442473888397217 0.25 0.22086797654628754 0.21283666789531708 0.068169407546520233;
	setAttr -s 7 ".koy[0:6]"  -0.024477075785398483 -0.029041904956102371 
		-0.019906943663954735 0 0.04132688045501709 0.014330320060253143 -0.0074848695658147335;
createNode animCurveTA -n "animCurveTA447";
	setAttr ".tan" 1;
	setAttr -s 10 ".ktv[0:9]"  0 -0.87714675457798974 2.5 -1.1146467246639711 
		5 -1.5201681610327227 7.5 -2.0187227381891901 13.75 -2.9589140580094364 20 -2.7235108429944401 
		26.25 -1.6800850728913492 31.25 -0.90930957795934209 36.25 -0.81299138719423802 37 
		-0.87813170370358984;
	setAttr -s 10 ".kit[2:9]"  9 1 1 1 9 9 1 2;
	setAttr -s 10 ".kot[2:9]"  9 1 1 1 9 9 1 2;
	setAttr -s 10 ".kix[0:9]"  0.084181532263755798 0.089467264711856842 
		0.083333335816860199 0.07005627453327179 0.2147277444601059 0.19816252589225769 0.20833331346511841 
		0.16666662693023682 0.1730780303478241 0.02499997615814209;
	setAttr -s 10 ".kiy[0:9]"  -0.0022924302611500025 -0.0049517620354890823 
		-0.007889552041888237 -0.0074754981324076653 -0.0030617322772741318 0.013901788741350174 
		0.017590992152690887 0.0075668171048164368 -0.0042314492166042328 -0.00113691296428442;
	setAttr -s 10 ".kox[0:9]"  0.084181532263755798 0.089467272162437439 
		0.083333328366279602 0.19505248963832855 0.2147277444601059 0.19816252589225769 0.16666662693023682 
		0.16666674613952637 0.29807895421981812 1;
	setAttr -s 10 ".koy[0:9]"  -0.0022924302611500025 -0.0049517620354890823 
		-0.0078895511105656624 -0.020813478156924248 -0.0030617336742579937 0.013901777565479279 
		0.01407279260456562 0.0075668226927518845 -0.0072874967008829117 0;
createNode animCurveTA -n "animCurveTA448";
	setAttr ".tan" 1;
	setAttr -s 8 ".ktv[0:7]"  0 2.2332421979438823 7.5 1.1072132055345669 
		13.75 0.15410083361833501 20 0.38950402482173657 26.25 1.4329296893798247 31.25 2.2037051063460527 
		36.25 2.3000232873683424 37 2.232422897661468;
	setAttr -s 8 ".kit[4:7]"  9 9 1 2;
	setAttr -s 8 ".kot[4:7]"  9 9 1 2;
	setAttr -s 8 ".kix[0:7]"  0.17887134850025177 0.2024768590927124 
		0.2147277444601059 0.19816252589225769 0.20833331346511841 0.16666662693023682 0.1730780303478241 
		0.02499997615814209;
	setAttr -s 8 ".kiy[0:7]"  -0.0060551641508936882 -0.019540710374712944 
		-0.0030617325101047754 0.013901778496801853 0.017590990290045738 0.0075668161734938622 
		-0.0042314492166042328 -0.0011798493796959519;
	setAttr -s 8 ".kox[0:7]"  0.17887136340141296 0.20247681438922882 
		0.2147277444601059 0.19816252589225769 0.16666662693023682 0.16666674613952637 0.29807895421981812 
		1;
	setAttr -s 8 ".koy[0:7]"  -0.0060551613569259644 -0.019540697336196899 
		-0.0030617325101047754 0.013901778496801853 0.014072790741920471 0.0075668217614293098 
		-0.0072874925099313259 0;
createNode animCurveTU -n "animCurveTU440";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 1 2.5 1 21.25 1 37 1;
createNode animCurveTU -n "animCurveTU441";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 0.99999999999999978 2.5 0.99999999999999978 
		21.25 0.99999999999999978 37 0.99999999999999978;
createNode animCurveTU -n "animCurveTU442";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 0.99999999999999978 2.5 0.99999999999999978 
		21.25 0.99999999999999978 37 0.99999999999999978;
createNode animCurveTA -n "animCurveTA449";
	setAttr ".tan" 1;
	setAttr -s 8 ".ktv[0:7]"  0 7.1500018217381927 2.5 6.110167267870465 
		7.5 4.7146468445612433 13.75 4.307426320154657 21.25 5.8962542738930122 28.75 7.9813258177875426 
		35 7.8120867404978842 37 7.1503379618228013;
	setAttr -s 8 ".kit[0:7]"  2 1 1 3 1 1 1 2;
	setAttr -s 8 ".kot[0:7]"  2 1 1 3 1 1 1 2;
	setAttr -s 8 ".kix[1:7]"  0.081161290407180786 0.16275832056999207 
		0.2083333432674408 0.22086799144744873 0.2545035183429718 0.1931661069393158 0.066666722297668457;
	setAttr -s 8 ".kiy[1:7]"  -0.014329250901937485 -0.015849456191062927 
		0 0.041326887905597687 0.017135756090283394 -0.021209260448813438 -0.011549695394933224;
	setAttr -s 8 ".kox[1:7]"  0.1644940972328186 0.20442473888397217 
		0.24999997019767761 0.22086797654628754 0.21283666789531708 0.068169407546520233 
		1;
	setAttr -s 8 ".koy[1:7]"  -0.02904188260436058 -0.019906943663954735 
		0 0.041326876729726791 0.014330320060253143 -0.0074848667718470097 0;
createNode animCurveTA -n "animCurveTA450";
	setAttr ".tan" 1;
	setAttr -s 9 ".ktv[0:8]"  0 -0.91877148719301893 2.5 -1.324292914415683 
		5 -1.8228474803278072 11.25 -2.7630387789430793 17.5 -2.5276355692373431 23.75 -1.4842098226675626 
		28.75 -0.71343434511954085 33.75 -0.61711615652678653 37 -0.91923482507559395;
	setAttr -s 9 ".kit[1:8]"  9 1 1 1 9 9 1 2;
	setAttr -s 9 ".kot[1:8]"  9 1 1 1 9 9 1 2;
	setAttr -s 9 ".kix[0:8]"  0.089467264711856842 0.083333335816860199 
		0.07005627453327179 0.2147277444601059 0.19816252589225769 0.20833337306976318 0.16666662693023682 
		0.1730780303478241 0.10833334922790527;
	setAttr -s 9 ".kiy[0:8]"  -0.0049517625011503696 -0.0078895511105656624 
		-0.0074754953384399414 -0.0030617320444434881 0.013901778496801853 0.017590994015336037 
		0.0075668185018002987 -0.0042314473539590836 -0.0052729654125869274;
	setAttr -s 9 ".kox[0:8]"  0.089467272162437439 0.083333335816860199 
		0.19505248963832855 0.2147277444601059 0.19816252589225769 0.16666662693023682 0.16666668653488159 
		0.29807895421981812 1;
	setAttr -s 9 ".koy[0:8]"  -0.0049517625011503696 -0.0078895511105656624 
		-0.020813478156924248 -0.0030617336742579937 0.013901778496801853 0.014072789810597897 
		0.0075668208301067352 -0.0072874967008829117 0;
createNode animCurveTA -n "animCurveTA451";
	setAttr ".tan" 1;
	setAttr -s 9 ".ktv[0:8]"  0 2.1046441474014963 2.5 1.7696441642315448 
		5 1.2611151004020478 11.25 0.3080026942917759 17.5 0.54340589394054262 23.75 1.5868315959327781 
		28.75 2.3576070405514944 33.75 2.4539252250293155 37 2.1056806742671252;
	setAttr -s 9 ".kit[0:8]"  2 9 1 1 1 9 9 1 
		2;
	setAttr -s 9 ".kot[0:8]"  2 9 1 1 1 9 9 1 
		2;
	setAttr -s 9 ".kix[2:8]"  0.18688793480396271 0.2147277444601059 
		0.19816252589225769 0.20833337306976318 0.16666662693023682 0.1730780303478241 0.10833334922790527;
	setAttr -s 9 ".kiy[2:8]"  -0.022276556119322777 -0.0030617325101047754 
		0.013901778496801853 0.017590994015336037 0.0075668180361390114 -0.0042314482852816582 
		-0.006078014150261879;
	setAttr -s 9 ".kox[2:8]"  0.18688791990280151 0.2147277444601059 
		0.19816252589225769 0.16666662693023682 0.16666668653488159 0.29807895421981812 1;
	setAttr -s 9 ".koy[2:8]"  -0.022276556119322777 -0.0030617325101047754 
		0.013901778496801853 0.014072788879275322 0.0075668208301067352 -0.0072874948382377625 
		0;
createNode animCurveTU -n "animCurveTU443";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 1 18.75 1 37 1;
createNode animCurveTU -n "animCurveTU444";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999978 18.75 0.99999999999999978 
		37 0.99999999999999978;
createNode animCurveTU -n "animCurveTU445";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999978 18.75 0.99999999999999978 
		37 0.99999999999999978;
createNode animCurveTA -n "animCurveTA452";
	setAttr ".tan" 1;
	setAttr -s 7 ".ktv[0:6]"  0 12.247781642514175 5 10.852261157228105 
		11.25 10.445040614736344 18.75 12.033868639036564 26.25 14.118940275531777 32.5 13.949701190725984 
		37 12.247781642514175;
	setAttr -s 7 ".kit[0:6]"  9 9 3 1 1 1 1;
	setAttr -s 7 ".kot[0:6]"  9 9 3 1 1 1 1;
	setAttr -s 7 ".kix[3:6]"  0.22086799144744873 0.2545035183429718 
		0.19712486863136292 0.14930908381938934;
	setAttr -s 7 ".kiy[3:6]"  0.04132688045501709 0.017135756090283394 
		-0.015585409477353096 -0.037576645612716675;
	setAttr -s 7 ".kox[3:6]"  0.22086797654628754 0.21283666789531708 
		0.15545886754989624 0.14930908381938934;
	setAttr -s 7 ".koy[3:6]"  0.041326861828565598 0.014330320060253143 
		-0.012291144579648972 -0.037576645612716675;
createNode animCurveTA -n "animCurveTA453";
	setAttr ".tan" 1;
	setAttr -s 8 ".ktv[0:7]"  0 -1.1610633997754873 2.5 -1.6829366003110835 
		8.75 -2.6231281576331633 15 -2.3877248831529347 21.25 -1.3442988494699426 26.25 -0.5735231598322531 
		31.25 -0.47720494473620051 37 -1.1611085959575647;
	setAttr -s 8 ".kit[0:7]"  9 1 1 1 9 9 1 1;
	setAttr -s 8 ".kot[0:7]"  9 1 1 1 9 9 1 1;
	setAttr -s 8 ".kix[1:7]"  0.07005627453327179 0.2147277444601059 
		0.19816252589225769 0.20833331346511841 0.16666668653488159 0.1730780303478241 0.19043938815593719;
	setAttr -s 8 ".kiy[1:7]"  -0.0074755018576979637 -0.0030617325101047754 
		0.01390178594738245 0.017590994015336037 0.0075668231584131718 -0.0042314496822655201 
		-0.016642488539218903;
	setAttr -s 8 ".kox[1:7]"  0.19505248963832855 0.2147277444601059 
		0.19816252589225769 0.16666668653488159 0.16666662693023682 0.29807895421981812 0.19043938815593719;
	setAttr -s 8 ".koy[1:7]"  -0.020813478156924248 -0.0030617336742579937 
		0.01390178594738245 0.014072799123823643 0.0075668203644454479 -0.0072874990291893482 
		-0.016642488539218903;
createNode animCurveTA -n "animCurveTA454";
	setAttr ".tan" 1;
	setAttr -s 8 ".ktv[0:7]"  0 1.839599558714774 2.5 1.3310705264415112 
		8.75 0.37795817947561117 15 0.61336136451668721 21.25 1.6567870017602486 26.25 2.4275623985493149 
		31.25 2.5238805770502108 37 1.83997718178799;
	setAttr -s 8 ".kit[0:7]"  9 1 1 1 9 9 1 2;
	setAttr -s 8 ".kot[0:7]"  9 1 1 1 9 9 1 2;
	setAttr -s 8 ".kix[1:7]"  0.18688793480396271 0.2147277444601059 
		0.19816252589225769 0.20833331346511841 0.16666668653488159 0.1730780303478241 0.19166672229766846;
	setAttr -s 8 ".kiy[1:7]"  -0.022276556119322777 -0.0030617325101047754 
		0.013901778496801853 0.017590988427400589 0.0075668203644454479 -0.0042314496822655201 
		-0.011936365626752377;
	setAttr -s 8 ".kox[1:7]"  0.18688791990280151 0.2147277444601059 
		0.19816252589225769 0.16666668653488159 0.16666662693023682 0.29807895421981812 1;
	setAttr -s 8 ".koy[1:7]"  -0.022276554256677628 -0.0030617325101047754 
		0.013901778496801853 0.014072793535888195 0.0075668175704777241 -0.0072874948382377625 
		0;
createNode animCurveTU -n "animCurveTU446";
	setAttr ".tan" 2;
	setAttr -s 5 ".ktv[0:4]"  0 0 6.25 0 18.75 0 23.75 0 37 0;
createNode animCurveTA -n "animCurveTA455";
	setAttr ".tan" 1;
	setAttr -s 8 ".ktv[0:7]"  0 -0.031511657810396665 6.25 -0.23939301863881593 
		12.5 -0.2563558584268405 18.75 -0.086387506069309741 23.75 0.090777069021443793 28.75 
		0.18302089196205482 32.5 0.14246611850508725 37 -0.031511657810396665;
	setAttr -s 8 ".kit[2:7]"  9 1 1 9 1 9;
	setAttr -s 8 ".kot[2:7]"  9 1 1 9 1 9;
	setAttr -s 8 ".kix[0:7]"  0.19482295215129852 0.20834384858608246 
		0.2083333283662796 0.20020510256290436 0.15892566740512848 0.16666662693023682 0.11975276470184326 
		0.14999997615814209;
	setAttr -s 8 ".kiy[0:7]"  -0.0041890949942171574 -0.0020714255515486002 
		0.0013352248352020979 0.0036638597957789898 0.0026677995920181274 0.00051551073556765914 
		-0.0017655885312706232 -0.0030364850535988808;
	setAttr -s 8 ".kox[0:7]"  0.19482293725013733 0.20834386348724365 
		0.2083333432674408 0.15853917598724365 0.1589256078004837 0.12500005960464478 0.16141879558563232 
		0.14999997615814209;
	setAttr -s 8 ".koy[0:7]"  -0.0041890940628945827 -0.0020714248530566692 
		0.0013352249516174197 0.0029013506136834621 0.0026677995920181274 0.00038663335726596415 
		-0.0023798963520675898 -0.0030364850535988808;
createNode animCurveTA -n "animCurveTA456";
	setAttr ".tan" 1;
	setAttr -s 7 ".ktv[0:6]"  0 -0.014814737488693401 6.25 -2.2650272024663547 
		12.5 -1.7746039676982497 18.75 0.3991991444714828 23.75 2.0049810004264339 28.75 
		2.2056438447254205 37 -0.014923996211233569;
	setAttr -s 7 ".kit[3:6]"  9 9 1 1;
	setAttr -s 7 ".kot[3:6]"  9 9 1 1;
	setAttr -s 7 ".kix[0:6]"  0.18688793480396271 0.2147277444601059 
		0.19816252589225769 0.2083333432674408 0.16666668653488159 0.1730780303478241 0.27707117795944214;
	setAttr -s 7 ".kiy[0:6]"  -0.046409465372562408 -0.0063786068931221962 
		0.028962044045329094 0.036647889763116837 0.015764206647872925 -0.0088155157864093781 
		-0.045835256576538086;
	setAttr -s 7 ".kox[0:6]"  0.18688791990280151 0.2147277444601059 
		0.19816252589225769 0.16666668653488159 0.16666662693023682 0.29807895421981812 0.27707117795944214;
	setAttr -s 7 ".koy[0:6]"  -0.046409446746110916 -0.0063786068931221962 
		0.028962044045329094 0.029318314045667648 0.015764201059937477 -0.015182279050350189 
		-0.0458352230489254;
createNode animCurveTA -n "animCurveTA457";
	setAttr ".tan" 1;
	setAttr -s 7 ".ktv[0:6]"  0 -13.23257395238204 6.25 -10.33183870908111 
		12.5 -6.7499426276475072 18.75 -6.1097303751722398 23.75 -10.564376081093965 32.5 
		-14.528475440442579 37 -13.23257395238204;
	setAttr -s 7 ".kit[1:6]"  9 1 9 1 3 1;
	setAttr -s 7 ".kot[1:6]"  9 1 9 1 3 1;
	setAttr -s 7 ".kix[0:6]"  0.21174144744873047 0.2083333283662796 
		0.19178201258182526 0.2083333432674408 0.13215525448322296 0.29166668653488159 0.16157282888889313;
	setAttr -s 7 ".kiy[0:6]"  0.047091066837310791 0.056571628898382187 
		0.05517355352640152 -0.036985788494348526 -0.059909965842962265 0 0.030647551640868187;
	setAttr -s 7 ".kox[0:6]"  0.21174144744873047 0.2083333283662796 
		0.19178204238414764 0.16666668653488159 0.25714758038520813 0.14999997615814209 0.16157282888889313;
	setAttr -s 7 ".koy[0:6]"  0.047091066837310791 0.056571628898382187 
		0.05517355352640152 -0.029588634148240089 -0.11657264828681946 0 0.030647551640868187;
createNode animCurveTL -n "animCurveTL250";
	setAttr ".tan" 1;
	setAttr -s 8 ".ktv[0:7]"  0 -0.16387457122081528 6.25 -0.18382722381622685 
		12.5 -0.16622156121425197 18.75 -0.10813009049045401 23.75 -0.079306498675052933 
		28.75 -0.09343396816138469 32.5 -0.13074941443287971 37 -0.16387457122081528;
	setAttr -s 8 ".kit[1:7]"  3 1 9 1 1 1 1;
	setAttr -s 8 ".kot[1:7]"  3 1 9 1 1 1 1;
	setAttr -s 8 ".kix[0:7]"  0.19965973496437073 0.2083333283662796 
		0.20091351866722107 0.2083333432674408 0.16705174744129181 0.14897234737873077 0.12538100779056549 
		0.17300510406494141;
	setAttr -s 8 ".kiy[0:7]"  -0.029260348528623581 0 0.042726654559373856 
		0.048286143690347672 0.0061121918261051178 -0.041232403367757797 -0.029975537210702896 
		-0.022142104804515839;
	setAttr -s 8 ".kox[0:7]"  0.19965973496437073 0.2083333283662796 
		0.20091351866722107 0.16666668653488159 0.16705168783664703 0.11172932386398315 0.1671745628118515 
		0.17300510406494141;
	setAttr -s 8 ".koy[0:7]"  -0.029260348528623581 0 0.042726654559373856 
		0.038628917187452316 0.0061121904291212559 -0.030924312770366669 -0.0399673692882061 
		-0.022142104804515839;
createNode animCurveTL -n "animCurveTL251";
	setAttr ".tan" 1;
	setAttr -s 7 ".ktv[0:6]"  0 0.16584656609996762 6.25 0.18784019407455796 
		12.5 0.23283845602209169 18.75 0.24616529589160266 23.75 0.22841737804724113 28.75 
		0.19221687641256846 37 0.16584656609996762;
	setAttr -s 7 ".kit[0:6]"  3 1 9 9 1 1 3;
	setAttr -s 7 ".kot[0:6]"  3 1 9 9 1 1 3;
	setAttr -s 7 ".kix[1:6]"  0.19148465991020203 0.2083333283662796 
		0.2083333432674408 0.16111120581626892 0.16141681373119354 0.27500003576278687;
	setAttr -s 7 ".kiy[1:6]"  0.039445940405130386 0.02916254848241806 
		-0.0024561544414609671 -0.029270943254232407 -0.025535251945257187 0;
	setAttr -s 7 ".kox[1:6]"  0.19148467481136322 0.2083333432674408 
		0.16666668653488159 0.16111113131046295 0.28247952461242676 0.27500003576278687;
	setAttr -s 7 ".koy[1:6]"  0.039445940405130386 0.02916255034506321 
		-0.0019649236928671598 -0.029270943254232407 -0.044686753302812576 0;
createNode animCurveTL -n "animCurveTL252";
	setAttr ".tan" 9;
	setAttr -s 8 ".ktv[0:7]"  0 -0.034824194676283823 6.25 -0.027813681082379242 
		12.5 -0.011679153129718036 18.75 -0.0056604581256404357 23.75 -0.014559137641260281 
		28.75 -0.032150251067935447 32.5 -0.036759946904949603 37 -0.034824194676283823;
	setAttr -s 8 ".kit[0:7]"  1 1 1 9 9 9 9 1;
	setAttr -s 8 ".kot[0:7]"  1 1 1 9 9 9 9 1;
	setAttr -s 8 ".kix[0:7]"  0.21506011486053467 0.21099571883678436 
		0.20120272040367126 0.2083333432674408 0.16666668653488159 0.16666662693023682 0.12500005960464478 
		0.16187617182731628;
	setAttr -s 8 ".kiy[0:7]"  0.0040631536394357681 0.012345650233328342 
		0.012619603425264359 -0.0015999913448467851 -0.013244898989796638 -0.012686172500252724 
		-0.0012154292780905962 0.0046672327443957329;
	setAttr -s 8 ".kox[0:7]"  0.21506011486053467 0.21099573373794556 
		0.20120273530483246 0.16666668653488159 0.16666662693023682 0.12500005960464478 0.14999997615814209 
		0.16187618672847748;
	setAttr -s 8 ".koy[0:7]"  0.0040631536394357681 0.012345650233328342 
		0.012619608081877232 -0.0012799932155758142 -0.013244894333183765 -0.0095146363601088524 
		-0.0014585142489522696 0.0046672327443957329;
createNode animCurveTU -n "animCurveTU447";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 1.0000000000000002 28.75 1.0000000000000002 
		37 1.0000000000000002;
createNode animCurveTU -n "animCurveTU448";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999989 28.75 0.99999999999999989 
		37 0.99999999999999989;
createNode animCurveTU -n "animCurveTU449";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 1 28.75 1 37 1;
createNode animCurveTA -n "animCurveTA458";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 28.75 0 37 0;
createNode animCurveTA -n "animCurveTA459";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 28.75 0 37 0;
createNode animCurveTA -n "animCurveTA460";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 28.75 0 37 0;
createNode animCurveTL -n "animCurveTL253";
	setAttr ".tan" 3;
	setAttr -s 5 ".ktv[0:4]"  0 -0.0037938670493906099 10 -0.0044235505336175894 
		18.75 -0.0058436273584157707 28.75 -0.0043817563755240464 37 -0.0037938670493906099;
	setAttr -s 5 ".kit[1:4]"  9 3 1 3;
	setAttr -s 5 ".kot[1:4]"  9 3 1 3;
	setAttr -s 5 ".kix[3:4]"  0.31045538187026978 0.27500003576278687;
	setAttr -s 5 ".kiy[3:4]"  0.0013886375818401575 0;
	setAttr -s 5 ".kox[3:4]"  0.27164849638938904 0.27500003576278687;
	setAttr -s 5 ".koy[3:4]"  0.0012150577967986465 0;
createNode animCurveTL -n "animCurveTL254";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 0.028270536201956117 10 0.032925759015601783 
		18.75 0.042896834305187002 28.75 0.032659884841320604 37 0.028270536201956117;
	setAttr -s 5 ".kit[0:4]"  3 9 9 1 3;
	setAttr -s 5 ".kot[0:4]"  3 9 9 1 3;
	setAttr -s 5 ".kix[3:4]"  0.31156018376350403 0.27500003576278687;
	setAttr -s 5 ".kiy[3:4]"  -0.0098895803093910217 0;
	setAttr -s 5 ".kox[3:4]"  0.27261519432067871 0.27500003576278687;
	setAttr -s 5 ".koy[3:4]"  -0.0086533855646848679 0;
createNode animCurveTL -n "animCurveTL255";
	setAttr ".tan" 3;
	setAttr -s 5 ".ktv[0:4]"  0 0.030144636354398527 10 0.035196265504376156 
		18.75 0.045602861408421271 28.75 0.034420454580344151 37 0.030144636354398527;
	setAttr -s 5 ".kit[1:4]"  9 3 1 3;
	setAttr -s 5 ".kot[1:4]"  9 3 1 3;
	setAttr -s 5 ".kix[3:4]"  0.31929671764373779 0.27500003576278687;
	setAttr -s 5 ".kiy[3:4]"  -0.0096905380487442017 0;
	setAttr -s 5 ".kox[3:4]"  0.27938470244407654 0.27500003576278687;
	setAttr -s 5 ".koy[3:4]"  -0.0084792235866189003 0;
createNode animCurveTU -n "animCurveTU450";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 1.0000000000000002 28.75 1.0000000000000002 
		37 1.0000000000000002;
createNode animCurveTU -n "animCurveTU451";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 1.0000000000000002 28.75 1.0000000000000002 
		37 1.0000000000000002;
createNode animCurveTU -n "animCurveTU452";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 1.0000000000000002 28.75 1.0000000000000002 
		37 1.0000000000000002;
createNode animCurveTA -n "animCurveTA461";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 28.75 0 37 0;
createNode animCurveTA -n "animCurveTA462";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 28.75 0 37 0;
createNode animCurveTA -n "animCurveTA463";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 28.75 0 37 0;
createNode animCurveTL -n "animCurveTL256";
	setAttr ".tan" 1;
	setAttr -s 5 ".ktv[0:4]"  0 -0.001923613571608176 10 -0.00044714531402392788 
		18.75 0.002644369410573816 28.75 -0.0007912764463788738 37 -0.001923613571608176;
	setAttr -s 5 ".kit[0:4]"  3 1 9 1 3;
	setAttr -s 5 ".kot[0:4]"  3 1 9 1 3;
	setAttr -s 5 ".kix[1:4]"  0.32534998655319214 0.2916666567325592 
		0.32538235187530518 0.27500003576278687;
	setAttr -s 5 ".kiy[1:4]"  0.0026898800861090422 -0.00016059452900663018 
		-0.0026976431254297495 0;
	setAttr -s 5 ".kox[1:4]"  0.28468120098114014 0.33333331346511841 
		0.28470960259437561 0.27500003576278687;
	setAttr -s 5 ".koy[1:4]"  0.002353644696995616 -0.00018353659834247082 
		-0.0023604377638548613 0;
createNode animCurveTL -n "animCurveTL257";
	setAttr ".tan" 3;
	setAttr -s 5 ".ktv[0:4]"  0 0.0066269326197570793 10 0.0004738341390859574 
		18.75 -0.012350065121229239 28.75 0.001184162377371999 37 0.0066269326197570793;
	setAttr -s 5 ".kit[1:4]"  1 3 1 3;
	setAttr -s 5 ".kot[1:4]"  1 3 1 3;
	setAttr -s 5 ".kix[1:4]"  0.2791077196598053 0.2916666567325592 0.32057845592498779 
		0.27500003576278687;
	setAttr -s 5 ".kiy[1:4]"  -0.011904062703251839 0 0.011748399585485458 
		0;
	setAttr -s 5 ".kox[1:4]"  0.24421924352645874 0.33333331346511841 
		0.2805061936378479 0.27500003576278687;
	setAttr -s 5 ".koy[1:4]"  -0.010416054166853428 0 0.010279850102961063 
		0;
createNode animCurveTL -n "animCurveTL258";
	setAttr ".tan" 3;
	setAttr -s 5 ".ktv[0:4]"  0 0.0049374768107375662 10 0.0021904823849318448 
		18.75 -0.0037866693947937371 28.75 0.002613358572061348 37 0.0049374768107375662;
	setAttr -s 5 ".kit[1:4]"  9 3 1 3;
	setAttr -s 5 ".kot[1:4]"  9 3 1 3;
	setAttr -s 5 ".kix[3:4]"  0.31889805197715759 0.27500003576278687;
	setAttr -s 5 ".kiy[3:4]"  0.0054899775423109531 0;
	setAttr -s 5 ".kox[3:4]"  0.27903586626052856 0.27500003576278687;
	setAttr -s 5 ".koy[3:4]"  0.0048037306405603886 0;
createNode animCurveTU -n "animCurveTU453";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 0.99999999999999989;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU454";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 0.99999999999999989;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU455";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 0.99999999999999989;
	setAttr ".kot[0]"  5;
createNode animCurveTA -n "animCurveTA464";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 6.7582974697168874;
	setAttr ".kot[0]"  5;
createNode animCurveTA -n "animCurveTA465";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 -32.755492312213462;
	setAttr ".kot[0]"  5;
createNode animCurveTA -n "animCurveTA466";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 3.135892765447319;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU456";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 1;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU457";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 1;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU458";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 1;
	setAttr ".kot[0]"  5;
createNode animCurveTA -n "animCurveTA467";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 -20.644023147781237;
	setAttr ".kot[0]"  5;
createNode animCurveTA -n "animCurveTA468";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 -32.618323385355389;
	setAttr ".kot[0]"  5;
createNode animCurveTA -n "animCurveTA469";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 6.0988986656034179;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU459";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 1;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU460";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 1;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU461";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 1;
	setAttr ".kot[0]"  5;
createNode animCurveTA -n "animCurveTA470";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 18.599464898778805;
	setAttr ".kot[0]"  5;
createNode animCurveTA -n "animCurveTA471";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 -50.307625382481127;
	setAttr ".kot[0]"  5;
createNode animCurveTA -n "animCurveTA472";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 -8.87658141042089;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU462";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 1;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU463";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 1;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU464";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 1;
	setAttr ".kot[0]"  5;
createNode animCurveTA -n "animCurveTA473";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 11.405323921234361;
	setAttr ".kot[0]"  5;
createNode animCurveTA -n "animCurveTA474";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 -8.6326481176969239;
	setAttr ".kot[0]"  5;
createNode animCurveTA -n "animCurveTA475";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 -1.1811359859764405;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU465";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 1;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU466";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 1;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU467";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 1;
	setAttr ".kot[0]"  5;
createNode animCurveTA -n "animCurveTA476";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 26.714188169279709;
	setAttr ".kot[0]"  5;
createNode animCurveTA -n "animCurveTA477";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 17.892675928963428;
	setAttr ".kot[0]"  5;
createNode animCurveTA -n "animCurveTA478";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 -6.5316266771457903;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU468";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 1;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU469";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 1;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU470";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 1;
	setAttr ".kot[0]"  5;
createNode animCurveTA -n "animCurveTA479";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 -23.788950893554738;
	setAttr ".kot[0]"  5;
createNode animCurveTA -n "animCurveTA480";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 -6.2429737996198726;
	setAttr ".kot[0]"  5;
createNode animCurveTA -n "animCurveTA481";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  1.25 6.1601524832728929;
	setAttr ".kot[0]"  5;
createNode animCurveTU -n "animCurveTU471";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0.99999999999999967;
createNode animCurveTU -n "animCurveTU472";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU473";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0.99999999999999956;
createNode animCurveTA -n "animCurveTA482";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA483";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA484";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL259";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 -0.064750274191756343;
createNode animCurveTL -n "animCurveTL260";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0.024385943061354078;
createNode animCurveTL -n "animCurveTL261";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0.035953051842049576;
createNode animCurveTU -n "animCurveTU474";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0.99999999999999933;
createNode animCurveTU -n "animCurveTU475";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0.99999999999999933;
createNode animCurveTU -n "animCurveTU476";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0.99999999999999956;
createNode animCurveTA -n "animCurveTA485";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA486";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA487";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL262";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0.064750274212058229;
createNode animCurveTL -n "animCurveTL263";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 -0.024385943062840029;
createNode animCurveTL -n "animCurveTL264";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 -0.035953051804478865;
createNode animCurveTA -n "animCurveTA488";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 21.103584815469421;
createNode animCurveTA -n "animCurveTA489";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 -28.028992562750005;
createNode animCurveTA -n "animCurveTA490";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 -9.6181804646839844;
createNode animCurveTA -n "animCurveTA491";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 42.791524096461359;
createNode animCurveTA -n "animCurveTA492";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 -4.4998573323006914;
createNode animCurveTA -n "animCurveTA493";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 -39.324063842663705;
createNode animCurveTA -n "animCurveTA494";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  0 -5.0408136271337556;
createNode animCurveTA -n "animCurveTA495";
	setAttr ".tan" 3;
	setAttr ".ktv[0]"  0 -21.842118947011262;
createNode animCurveTA -n "animCurveTA496";
	setAttr ".tan" 9;
	setAttr ".ktv[0]"  0 -29.992455857544382;
createNode animCurveTA -n "animCurveTA497";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 -7.1645607220777814;
createNode animCurveTA -n "animCurveTA498";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 -32.79603430261303;
createNode animCurveTA -n "animCurveTA499";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 14.3626833378967;
createNode animCurveTA -n "animCurveTA500";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 39.523803760820186;
createNode animCurveTA -n "animCurveTA501";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 9.9496719665548827;
createNode animCurveTA -n "animCurveTA502";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 -81.87769569515082;
createNode animCurveTA -n "animCurveTA503";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 -4.7957238099981074;
createNode animCurveTA -n "animCurveTA504";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 -19.054103784046834;
createNode animCurveTA -n "animCurveTA505";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 -9.4889103204074896;
createNode animCurveTA -n "animCurveTA506";
	setAttr ".tan" 1;
	setAttr -s 6 ".ktv[0:5]"  0 -1.4988823189270042 5 -2.1622052377637995 
		11.25 -1.795832772159057 21.25 -0.029090707336918643 27.5 0.49726645942742892 37 
		-1.4988823189270042;
	setAttr -s 6 ".kit[1:5]"  9 9 1 3 1;
	setAttr -s 6 ".kot[1:5]"  9 9 1 3 1;
	setAttr -s 6 ".kix[0:5]"  0.15804870426654816 0.1666666716337204 
		0.2083333283662796 0.32708302140235901 0.20833337306976318 0.32464683055877686;
	setAttr -s 6 ".kiy[0:5]"  -0.013458483852446079 -0.0023034503683447838 
		0.014319182373583317 0.026430174708366394 0 -0.036193668842315674;
	setAttr -s 6 ".kox[0:5]"  0.15804870426654816 0.2083333283662796 
		0.33333331346511841 0.20208404958248138 0.31666666269302368 0.32464683055877686;
	setAttr -s 6 ".koy[0:5]"  -0.013458483852446079 -0.0028793127276003361 
		0.022910689935088158 0.016329547390341759 0 -0.036193668842315674;
createNode animCurveTA -n "animCurveTA507";
	setAttr ".tan" 1;
	setAttr -s 6 ".ktv[0:5]"  0 -3.1561835551211876 5 0.32868842931057035 
		11.25 -1.4048079262071567 21.25 -13.500447642831233 27.5 -17.745320628693388 37 -3.1561835551211876;
	setAttr -s 6 ".kit[0:5]"  9 1 9 1 3 1;
	setAttr -s 6 ".kot[0:5]"  9 1 9 1 3 1;
	setAttr -s 6 ".kix[1:5]"  0.16394640505313873 0.2083333283662796 
		0.32145392894744873 0.20833337306976318 0.28361845016479492;
	setAttr -s 6 ".kiy[1:5]"  0.026496188715100288 -0.092832297086715698 
		-0.21606700122356415 0 0.31821167469024658;
	setAttr -s 6 ".kox[1:5]"  0.20561288297176361 0.33333331346511841 
		0.19645583629608154 0.31666666269302368 0.2836185097694397;
	setAttr -s 6 ".koy[1:5]"  0.033230103552341461 -0.14853167533874512 
		-0.13204886019229889 0 0.31821173429489136;
createNode animCurveTA -n "animCurveTA508";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.25301525319534846 5 -0.52560336016798692 
		11.25 -0.45326772134804039 21.25 1.2102161065825772 27.5 1.5414982602423963 37 0.25301525319534846;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 3 1;
	setAttr -s 6 ".kot[0:5]"  1 9 9 9 3 1;
	setAttr -s 6 ".kix[0:5]"  0.11699502170085907 0.1666666716337204 
		0.2083333283662796 0.33333331346511841 0.20833337306976318 0.29915103316307068;
	setAttr -s 6 ".kiy[0:5]"  -0.011967708356678486 -0.0054786503314971924 
		0.011652218177914619 0.021424757316708565 0 -0.033471275120973587;
	setAttr -s 6 ".kox[0:5]"  0.11699502915143967 0.2083333283662796 
		0.33333331346511841 0.20833337306976318 0.31666666269302368 0.29915100336074829;
	setAttr -s 6 ".koy[0:5]"  -0.01196770928800106 -0.0068483129143714905 
		0.018643548712134361 0.013390476815402508 0 -0.033471271395683289;
createNode animCurveTA -n "animCurveTA509";
	setAttr ".tan" 9;
	setAttr -s 7 ".ktv[0:6]"  0 -0.26251674276142306 2.5 -1.7262169757451238 
		7.5 -2.7717277352470031 13.75 -1.9479804977484925 23.75 2.2111716409939461 30 3.4596888457108754 
		37 -0.26143164024324256;
	setAttr -s 7 ".kit[4:6]"  1 1 1;
	setAttr -s 7 ".kot[4:6]"  1 1 1;
	setAttr -s 7 ".kix[4:6]"  0.30726948380470276 0.20326811075210571 
		0.24169673025608063;
	setAttr -s 7 ".kiy[4:6]"  0.072257295250892639 -0.015029655769467354 
		-0.064810231328010559;
	setAttr -s 7 ".kox[4:6]"  0.18227365612983704 0.24493452906608582 
		0.24169673025608063;
	setAttr -s 7 ".koy[4:6]"  0.042863354086875916 -0.018110467121005058 
		-0.06481015682220459;
createNode animCurveTA -n "animCurveTA510";
	setAttr ".tan" 9;
	setAttr -s 7 ".ktv[0:6]"  0 -7.320334150302255 2.5 -2.3779305842339453 
		7.5 1.5317142704949385 13.75 -0.22104333967174891 23.75 -12.451080337249055 30 -16.046479105393772 
		37 -7.3195247823608449;
	setAttr -s 7 ".kit[2:6]"  1 9 1 3 1;
	setAttr -s 7 ".kot[2:6]"  1 9 1 3 1;
	setAttr -s 7 ".kix[2:6]"  0.16394640505313873 0.2083333432674408 
		0.30918556451797485 0.20833331346511841 0.21613115072250366;
	setAttr -s 7 ".kiy[2:6]"  0.026790589094161987 -0.093863770365715027 
		-0.12852135300636292 0 0.2181287407875061;
	setAttr -s 7 ".kox[2:6]"  0.20561288297176361 0.3333333432674408 
		0.18418861925601959 0.23333334922790527 0.21613116562366486;
	setAttr -s 7 ".koy[2:6]"  0.033599331974983215 -0.15018203854560852 
		-0.076563000679016113 0 0.2181287407875061;
createNode animCurveTA -n "animCurveTA511";
	setAttr ".tan" 9;
	setAttr -s 7 ".ktv[0:6]"  0 0.75000000000000011 2.5 0.25301525319534846 
		7.5 -0.52560336016798692 13.75 -0.45326772134804039 23.75 1.2102161065825772 30 1.3797874624553677 
		37 0.75047407617136153;
	setAttr -s 7 ".kit[0:6]"  2 9 9 9 9 3 2;
	setAttr -s 7 ".kot[0:6]"  2 9 9 9 9 3 2;
createNode animCurveTU -n "animCurveTU477";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999978 37 0.99999999999999978;
createNode animCurveTU -n "animCurveTU478";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999978 37 0.99999999999999978;
createNode animCurveTU -n "animCurveTU479";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 1 37 1;
createNode animCurveTA -n "animCurveTA512";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  0 2.2003467794248865 12.5 3.8488770449317107 
		27.5 0.73133527731076298 37 2.2003467794248865;
	setAttr -s 4 ".kit[0:3]"  1 3 3 1;
	setAttr -s 4 ".kot[0:3]"  1 3 3 1;
	setAttr -s 4 ".kix[0:3]"  0.37735733389854431 0.4166666567325592 
		0.5 0.29397943615913391;
	setAttr -s 4 ".kiy[0:3]"  0.04384911060333252 0 0 0.039030246436595917;
	setAttr -s 4 ".kox[0:3]"  0.3773573637008667 0.5 0.31666666269302368 
		0.29397943615913391;
	setAttr -s 4 ".koy[0:3]"  0.043849106878042221 0 0 0.039030242711305618;
createNode animCurveTA -n "animCurveTA513";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  0 -3.9727062121129415 12.5 -7.7273709193082984 
		27.5 -1.3461140312570812 37 -3.9727062121129415;
	setAttr -s 4 ".kit[0:3]"  1 3 3 1;
	setAttr -s 4 ".kot[0:3]"  1 3 3 1;
	setAttr -s 4 ".kix[0:3]"  0.39064756035804749 0.4166666567325592 
		0.5 0.29996880888938904;
	setAttr -s 4 ".kiy[0:3]"  -0.085916168987751007 0 0 -0.072159826755523682;
	setAttr -s 4 ".kox[0:3]"  0.39064756035804749 0.5 0.31666666269302368 
		0.29996877908706665;
	setAttr -s 4 ".koy[0:3]"  -0.085916168987751007 0 0 -0.072159834206104279;
createNode animCurveTA -n "animCurveTA514";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  0 0.97128227707550852 12.5 1.8182825979227397 
		27.5 0.33460256705436614 37 0.97128227707550852;
	setAttr -s 4 ".kit[0:3]"  1 3 3 1;
	setAttr -s 4 ".kot[0:3]"  1 3 3 1;
	setAttr -s 4 ".kix[0:3]"  0.38123011589050293 0.4166666567325592 
		0.5 0.30387145280838013;
	setAttr -s 4 ".kiy[0:3]"  0.021051907911896706 0 0 0.0165117047727108;
	setAttr -s 4 ".kox[0:3]"  0.38123011589050293 0.5 0.31666666269302368 
		0.30387145280838013;
	setAttr -s 4 ".koy[0:3]"  0.021051906049251556 0 0 0.0165117047727108;
createNode animCurveTU -n "animCurveTU480";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999978 37 0.99999999999999978;
createNode animCurveTU -n "animCurveTU481";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999978 37 0.99999999999999978;
createNode animCurveTU -n "animCurveTU482";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 1 37 1;
createNode animCurveTA -n "animCurveTA515";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  0 2.2003467794248865 12.5 3.8488770449317107 
		27.5 0.73133527731076298 37 2.2003467794248865;
	setAttr -s 4 ".kit[0:3]"  1 3 3 1;
	setAttr -s 4 ".kot[0:3]"  1 3 3 1;
	setAttr -s 4 ".kix[0:3]"  0.37735733389854431 0.4166666567325592 
		0.5 0.29397943615913391;
	setAttr -s 4 ".kiy[0:3]"  0.04384911060333252 0 0 0.039030246436595917;
	setAttr -s 4 ".kox[0:3]"  0.3773573637008667 0.5 0.31666666269302368 
		0.29397943615913391;
	setAttr -s 4 ".koy[0:3]"  0.043849106878042221 0 0 0.039030242711305618;
createNode animCurveTA -n "animCurveTA516";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  0 -3.9727062121129415 12.5 -7.7273709193082984 
		27.5 -1.3461140312570812 37 -3.9727062121129415;
	setAttr -s 4 ".kit[0:3]"  1 3 3 1;
	setAttr -s 4 ".kot[0:3]"  1 3 3 1;
	setAttr -s 4 ".kix[0:3]"  0.39064756035804749 0.4166666567325592 
		0.5 0.29996880888938904;
	setAttr -s 4 ".kiy[0:3]"  -0.085916168987751007 0 0 -0.072159826755523682;
	setAttr -s 4 ".kox[0:3]"  0.39064756035804749 0.5 0.31666666269302368 
		0.29996877908706665;
	setAttr -s 4 ".koy[0:3]"  -0.085916168987751007 0 0 -0.072159834206104279;
createNode animCurveTA -n "animCurveTA517";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  0 0.97128227707550852 12.5 1.8182825979227397 
		27.5 0.33460256705436614 37 0.97128227707550852;
	setAttr -s 4 ".kit[0:3]"  1 3 3 1;
	setAttr -s 4 ".kot[0:3]"  1 3 3 1;
	setAttr -s 4 ".kix[0:3]"  0.38123011589050293 0.4166666567325592 
		0.5 0.30387145280838013;
	setAttr -s 4 ".kiy[0:3]"  0.021051907911896706 0 0 0.0165117047727108;
	setAttr -s 4 ".kox[0:3]"  0.38123011589050293 0.5 0.31666666269302368 
		0.30387145280838013;
	setAttr -s 4 ".koy[0:3]"  0.021051906049251556 0 0 0.0165117047727108;
createNode animCurveTA -n "animCurveTA518";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA519";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA520";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTL -n "animCurveTL265";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTL -n "animCurveTL266";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTL -n "animCurveTL267";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTU -n "animCurveTU483";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999978 37 0.99999999999999978;
createNode animCurveTU -n "animCurveTU484";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999989 37 0.99999999999999989;
createNode animCurveTU -n "animCurveTU485";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 1.0000000000000002 37 1.0000000000000002;
createNode animCurveTA -n "animCurveTA521";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  0 -4.3754849756788365 5 0 11.25 0 23.75 
		-11.689319748800775 27.5 -11.689319748800775 37 -4.3754849756788365;
	setAttr -s 6 ".kit[0:5]"  9 10 10 10 10 9;
	setAttr -s 6 ".kot[0:5]"  9 10 10 10 10 9;
createNode animCurveTA -n "animCurveTA522";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  0 -0.19266477519316091 5 0 11.25 0 23.75 
		-0.27312330245514976 27.5 -0.27312330245514976 37 -0.19266477519316091;
	setAttr -s 6 ".kit[0:5]"  9 10 10 10 10 9;
	setAttr -s 6 ".kot[0:5]"  9 10 10 10 10 9;
createNode animCurveTA -n "animCurveTA523";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  0 0.090203517949951684 5 0 11.25 0 23.75 
		0.2091135660941337 27.5 0.2091135660941337 37 0.090203517949951684;
	setAttr -s 6 ".kit[0:5]"  9 10 10 10 10 9;
	setAttr -s 6 ".kot[0:5]"  9 10 10 10 10 9;
createNode animCurveTL -n "animCurveTL268";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 0 37 0;
createNode animCurveTL -n "animCurveTL269";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 0 37 0;
createNode animCurveTL -n "animCurveTL270";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 0 37 0;
createNode animCurveTU -n "animCurveTU486";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 10 37 10;
createNode animCurveTU -n "animCurveTU487";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999989 37 0.99999999999999989;
createNode animCurveTU -n "animCurveTU488";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 1 37 1;
createNode animCurveTU -n "animCurveTU489";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 1 37 1;
createNode animCurveTA -n "animCurveTA524";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 21.900463788106144 7.5 20.066046585936746 
		12.5 21.957295461100067 21.25 27.839661234923508 27.5 27.46914149189033 37 21.900463788106144;
	setAttr -s 6 ".kit[0:5]"  1 3 1 9 9 9;
	setAttr -s 6 ".kot[0:5]"  1 3 1 9 9 9;
	setAttr -s 6 ".kix[0:5]"  0.24359011650085449 0.25 0.14930500090122223 
		0.2916666567325592 0.20833337306976318 0.31666666269302368;
	setAttr -s 6 ".kiy[0:5]"  -0.042962156236171722 0 0.054441049695014954 
		0.056116584688425064 -0.041134350001811981 -0.097191758453845978;
	setAttr -s 6 ".kox[0:5]"  0.2435901015996933 0.1666666567325592 0.27430170774459839 
		0.20833337306976318 0.31666666269302368 0.31666666269302368;
	setAttr -s 6 ".koy[0:5]"  -0.042962156236171722 0 0.10001852363348007 
		0.040083281695842743 -0.062524199485778809 -0.097191758453845978;
createNode animCurveTA -n "animCurveTA525";
	setAttr ".tan" 2;
	setAttr -s 5 ".ktv[0:4]"  0 2.0742991664280344 12.5 2.1000322749270692 
		21.25 2.0790591929992455 27.5 2.083712677630297 37 2.0742991664280344;
createNode animCurveTA -n "animCurveTA526";
	setAttr ".tan" 2;
	setAttr -s 5 ".ktv[0:4]"  0 -0.56933707768807773 12.5 -0.48288236900892545 
		21.25 -0.5593380174518614 27.5 -0.52616930609775925 37 -0.56933707768807773;
createNode animCurveTL -n "animCurveTL271";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 0 37 0;
createNode animCurveTL -n "animCurveTL272";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 0 37 0;
createNode animCurveTL -n "animCurveTL273";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 0 37 0;
createNode animCurveTU -n "animCurveTU490";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999967 18.75 0.99999999999999967 
		37 0.99999999999999967;
createNode animCurveTU -n "animCurveTU491";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999933 18.75 0.99999999999999933 
		37 0.99999999999999933;
createNode animCurveTU -n "animCurveTU492";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0.99999999999999978 18.75 0.99999999999999978 
		37 0.99999999999999978;
createNode animCurveTA -n "animCurveTA527";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 13.295205178867663 18.75 13.295205178867663 
		37 13.295205178867663;
createNode animCurveTA -n "animCurveTA528";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 -3.1611573557342734 18.75 -3.1611573557342734 
		37 -3.1611573557342734;
createNode animCurveTA -n "animCurveTA529";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 -5.2867926828993701 18.75 -5.2867926828993701 
		37 -5.2867926828993701;
createNode animCurveTU -n "animCurveTU493";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 1 18.75 1 37 1;
createNode animCurveTU -n "animCurveTU494";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 1 18.75 1 37 1;
createNode animCurveTU -n "animCurveTU495";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 1 18.75 1 37 1;
createNode animCurveTA -n "animCurveTA530";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA531";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTA -n "animCurveTA532";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTL -n "animCurveTL274";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTL -n "animCurveTL275";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTL -n "animCurveTL276";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 18.75 0 37 0;
createNode animCurveTU -n "animCurveTU496";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 1 18.75 1 37 1;
createNode lightLinker -n "lightLinker1";
	setAttr -s 5 ".lnk";
	setAttr -s 5 ".slnk";
select -ne :time1;
	setAttr -av -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 27;
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
	setAttr ".mcfr" 15;
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
	setAttr ".hwfr" 15;
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
connectAttr "idle2Source.cl" "clipLibrary1.sc[0]";
connectAttr "animCurveTU373.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "animCurveTA400.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "animCurveTA401.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "animCurveTA402.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "animCurveTL208.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "animCurveTL209.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "animCurveTL210.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "animCurveTU374.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "animCurveTU375.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "animCurveTU376.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "animCurveTU377.a" "clipLibrary1.cel[0].cev[10].cevr";
connectAttr "animCurveTA403.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "animCurveTA404.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "animCurveTA405.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "animCurveTU378.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "animCurveTU379.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "animCurveTU380.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "animCurveTU381.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "animCurveTU382.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "animCurveTU383.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "animCurveTU384.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "animCurveTU385.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "animCurveTU386.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "animCurveTU387.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "animCurveTU388.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "animCurveTU389.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "animCurveTU390.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "animCurveTU391.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "animCurveTU392.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "animCurveTU393.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "animCurveTU394.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "animCurveTU395.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "animCurveTU396.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "animCurveTL211.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "animCurveTL212.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "animCurveTL213.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "animCurveTA406.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "animCurveTA407.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "animCurveTA408.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "animCurveTA409.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "animCurveTU397.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "animCurveTU398.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "animCurveTU399.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "animCurveTU400.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "animCurveTU401.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "animCurveTU402.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "animCurveTU403.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "animCurveTU404.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "animCurveTA410.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "animCurveTA411.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "animCurveTA412.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "animCurveTL214.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "animCurveTL215.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "animCurveTL216.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "animCurveTU405.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "animCurveTL217.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "animCurveTL218.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "animCurveTL219.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "animCurveTA413.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "animCurveTA414.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "animCurveTA415.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "animCurveTA416.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "animCurveTU406.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "animCurveTU407.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "animCurveTU408.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "animCurveTU409.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr "animCurveTU410.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "animCurveTU411.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "animCurveTU412.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "animCurveTU413.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "animCurveTA417.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "animCurveTA418.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "animCurveTA419.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "animCurveTL220.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "animCurveTL221.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "animCurveTL222.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "animCurveTU414.a" "clipLibrary1.cel[0].cev[158].cevr";
connectAttr "animCurveTL223.a" "clipLibrary1.cel[0].cev[159].cevr";
connectAttr "animCurveTL224.a" "clipLibrary1.cel[0].cev[160].cevr";
connectAttr "animCurveTL225.a" "clipLibrary1.cel[0].cev[161].cevr";
connectAttr "animCurveTA420.a" "clipLibrary1.cel[0].cev[165].cevr";
connectAttr "animCurveTA421.a" "clipLibrary1.cel[0].cev[169].cevr";
connectAttr "animCurveTA422.a" "clipLibrary1.cel[0].cev[170].cevr";
connectAttr "animCurveTA423.a" "clipLibrary1.cel[0].cev[171].cevr";
connectAttr "animCurveTU415.a" "clipLibrary1.cel[0].cev[175].cevr";
connectAttr "animCurveTU416.a" "clipLibrary1.cel[0].cev[176].cevr";
connectAttr "animCurveTU417.a" "clipLibrary1.cel[0].cev[177].cevr";
connectAttr "animCurveTU418.a" "clipLibrary1.cel[0].cev[178].cevr";
connectAttr "animCurveTU419.a" "clipLibrary1.cel[0].cev[179].cevr";
connectAttr "animCurveTU420.a" "clipLibrary1.cel[0].cev[180].cevr";
connectAttr "animCurveTU421.a" "clipLibrary1.cel[0].cev[181].cevr";
connectAttr "animCurveTU422.a" "clipLibrary1.cel[0].cev[182].cevr";
connectAttr "animCurveTA424.a" "clipLibrary1.cel[0].cev[183].cevr";
connectAttr "animCurveTA425.a" "clipLibrary1.cel[0].cev[184].cevr";
connectAttr "animCurveTA426.a" "clipLibrary1.cel[0].cev[185].cevr";
connectAttr "animCurveTL226.a" "clipLibrary1.cel[0].cev[186].cevr";
connectAttr "animCurveTL227.a" "clipLibrary1.cel[0].cev[187].cevr";
connectAttr "animCurveTL228.a" "clipLibrary1.cel[0].cev[188].cevr";
connectAttr "animCurveTU423.a" "clipLibrary1.cel[0].cev[195].cevr";
connectAttr "animCurveTU424.a" "clipLibrary1.cel[0].cev[196].cevr";
connectAttr "animCurveTU425.a" "clipLibrary1.cel[0].cev[197].cevr";
connectAttr "animCurveTA427.a" "clipLibrary1.cel[0].cev[198].cevr";
connectAttr "animCurveTA428.a" "clipLibrary1.cel[0].cev[199].cevr";
connectAttr "animCurveTA429.a" "clipLibrary1.cel[0].cev[200].cevr";
connectAttr "animCurveTL229.a" "clipLibrary1.cel[0].cev[201].cevr";
connectAttr "animCurveTL230.a" "clipLibrary1.cel[0].cev[202].cevr";
connectAttr "animCurveTL231.a" "clipLibrary1.cel[0].cev[203].cevr";
connectAttr "animCurveTU426.a" "clipLibrary1.cel[0].cev[214].cevr";
connectAttr "animCurveTL232.a" "clipLibrary1.cel[0].cev[215].cevr";
connectAttr "animCurveTL233.a" "clipLibrary1.cel[0].cev[216].cevr";
connectAttr "animCurveTL234.a" "clipLibrary1.cel[0].cev[217].cevr";
connectAttr "animCurveTU427.a" "clipLibrary1.cel[0].cev[228].cevr";
connectAttr "animCurveTL235.a" "clipLibrary1.cel[0].cev[229].cevr";
connectAttr "animCurveTL236.a" "clipLibrary1.cel[0].cev[230].cevr";
connectAttr "animCurveTL237.a" "clipLibrary1.cel[0].cev[231].cevr";
connectAttr "animCurveTU428.a" "clipLibrary1.cel[0].cev[242].cevr";
connectAttr "animCurveTL238.a" "clipLibrary1.cel[0].cev[243].cevr";
connectAttr "animCurveTL239.a" "clipLibrary1.cel[0].cev[244].cevr";
connectAttr "animCurveTL240.a" "clipLibrary1.cel[0].cev[245].cevr";
connectAttr "animCurveTA430.a" "clipLibrary1.cel[0].cev[249].cevr";
connectAttr "animCurveTA431.a" "clipLibrary1.cel[0].cev[253].cevr";
connectAttr "animCurveTA432.a" "clipLibrary1.cel[0].cev[254].cevr";
connectAttr "animCurveTA433.a" "clipLibrary1.cel[0].cev[255].cevr";
connectAttr "animCurveTU429.a" "clipLibrary1.cel[0].cev[259].cevr";
connectAttr "animCurveTU430.a" "clipLibrary1.cel[0].cev[260].cevr";
connectAttr "animCurveTU431.a" "clipLibrary1.cel[0].cev[261].cevr";
connectAttr "animCurveTU432.a" "clipLibrary1.cel[0].cev[262].cevr";
connectAttr "animCurveTU433.a" "clipLibrary1.cel[0].cev[263].cevr";
connectAttr "animCurveTU434.a" "clipLibrary1.cel[0].cev[264].cevr";
connectAttr "animCurveTU435.a" "clipLibrary1.cel[0].cev[265].cevr";
connectAttr "animCurveTU436.a" "clipLibrary1.cel[0].cev[266].cevr";
connectAttr "animCurveTA434.a" "clipLibrary1.cel[0].cev[267].cevr";
connectAttr "animCurveTA435.a" "clipLibrary1.cel[0].cev[268].cevr";
connectAttr "animCurveTA436.a" "clipLibrary1.cel[0].cev[269].cevr";
connectAttr "animCurveTL241.a" "clipLibrary1.cel[0].cev[270].cevr";
connectAttr "animCurveTL242.a" "clipLibrary1.cel[0].cev[271].cevr";
connectAttr "animCurveTL243.a" "clipLibrary1.cel[0].cev[272].cevr";
connectAttr "animCurveTA437.a" "clipLibrary1.cel[0].cev[279].cevr";
connectAttr "animCurveTA438.a" "clipLibrary1.cel[0].cev[280].cevr";
connectAttr "animCurveTA439.a" "clipLibrary1.cel[0].cev[281].cevr";
connectAttr "animCurveTA440.a" "clipLibrary1.cel[0].cev[282].cevr";
connectAttr "animCurveTA441.a" "clipLibrary1.cel[0].cev[283].cevr";
connectAttr "animCurveTA442.a" "clipLibrary1.cel[0].cev[284].cevr";
connectAttr "animCurveTL244.a" "clipLibrary1.cel[0].cev[285].cevr";
connectAttr "animCurveTL245.a" "clipLibrary1.cel[0].cev[286].cevr";
connectAttr "animCurveTL246.a" "clipLibrary1.cel[0].cev[287].cevr";
connectAttr "animCurveTA443.a" "clipLibrary1.cel[0].cev[288].cevr";
connectAttr "animCurveTA444.a" "clipLibrary1.cel[0].cev[289].cevr";
connectAttr "animCurveTA445.a" "clipLibrary1.cel[0].cev[290].cevr";
connectAttr "animCurveTL247.a" "clipLibrary1.cel[0].cev[291].cevr";
connectAttr "animCurveTL248.a" "clipLibrary1.cel[0].cev[292].cevr";
connectAttr "animCurveTL249.a" "clipLibrary1.cel[0].cev[293].cevr";
connectAttr "animCurveTU437.a" "clipLibrary1.cel[0].cev[294].cevr";
connectAttr "animCurveTU438.a" "clipLibrary1.cel[0].cev[295].cevr";
connectAttr "animCurveTU439.a" "clipLibrary1.cel[0].cev[296].cevr";
connectAttr "animCurveTA446.a" "clipLibrary1.cel[0].cev[297].cevr";
connectAttr "animCurveTA447.a" "clipLibrary1.cel[0].cev[298].cevr";
connectAttr "animCurveTA448.a" "clipLibrary1.cel[0].cev[299].cevr";
connectAttr "animCurveTU440.a" "clipLibrary1.cel[0].cev[303].cevr";
connectAttr "animCurveTU441.a" "clipLibrary1.cel[0].cev[304].cevr";
connectAttr "animCurveTU442.a" "clipLibrary1.cel[0].cev[305].cevr";
connectAttr "animCurveTA449.a" "clipLibrary1.cel[0].cev[306].cevr";
connectAttr "animCurveTA450.a" "clipLibrary1.cel[0].cev[307].cevr";
connectAttr "animCurveTA451.a" "clipLibrary1.cel[0].cev[308].cevr";
connectAttr "animCurveTU443.a" "clipLibrary1.cel[0].cev[312].cevr";
connectAttr "animCurveTU444.a" "clipLibrary1.cel[0].cev[313].cevr";
connectAttr "animCurveTU445.a" "clipLibrary1.cel[0].cev[314].cevr";
connectAttr "animCurveTA452.a" "clipLibrary1.cel[0].cev[315].cevr";
connectAttr "animCurveTA453.a" "clipLibrary1.cel[0].cev[316].cevr";
connectAttr "animCurveTA454.a" "clipLibrary1.cel[0].cev[317].cevr";
connectAttr "animCurveTU446.a" "clipLibrary1.cel[0].cev[321].cevr";
connectAttr "animCurveTA455.a" "clipLibrary1.cel[0].cev[322].cevr";
connectAttr "animCurveTA456.a" "clipLibrary1.cel[0].cev[323].cevr";
connectAttr "animCurveTA457.a" "clipLibrary1.cel[0].cev[324].cevr";
connectAttr "animCurveTL250.a" "clipLibrary1.cel[0].cev[325].cevr";
connectAttr "animCurveTL251.a" "clipLibrary1.cel[0].cev[326].cevr";
connectAttr "animCurveTL252.a" "clipLibrary1.cel[0].cev[327].cevr";
connectAttr "animCurveTU447.a" "clipLibrary1.cel[0].cev[361].cevr";
connectAttr "animCurveTU448.a" "clipLibrary1.cel[0].cev[362].cevr";
connectAttr "animCurveTU449.a" "clipLibrary1.cel[0].cev[363].cevr";
connectAttr "animCurveTA458.a" "clipLibrary1.cel[0].cev[364].cevr";
connectAttr "animCurveTA459.a" "clipLibrary1.cel[0].cev[365].cevr";
connectAttr "animCurveTA460.a" "clipLibrary1.cel[0].cev[366].cevr";
connectAttr "animCurveTL253.a" "clipLibrary1.cel[0].cev[367].cevr";
connectAttr "animCurveTL254.a" "clipLibrary1.cel[0].cev[368].cevr";
connectAttr "animCurveTL255.a" "clipLibrary1.cel[0].cev[369].cevr";
connectAttr "animCurveTU450.a" "clipLibrary1.cel[0].cev[406].cevr";
connectAttr "animCurveTU451.a" "clipLibrary1.cel[0].cev[407].cevr";
connectAttr "animCurveTU452.a" "clipLibrary1.cel[0].cev[408].cevr";
connectAttr "animCurveTA461.a" "clipLibrary1.cel[0].cev[409].cevr";
connectAttr "animCurveTA462.a" "clipLibrary1.cel[0].cev[410].cevr";
connectAttr "animCurveTA463.a" "clipLibrary1.cel[0].cev[411].cevr";
connectAttr "animCurveTL256.a" "clipLibrary1.cel[0].cev[412].cevr";
connectAttr "animCurveTL257.a" "clipLibrary1.cel[0].cev[413].cevr";
connectAttr "animCurveTL258.a" "clipLibrary1.cel[0].cev[414].cevr";
connectAttr "animCurveTU453.a" "clipLibrary1.cel[0].cev[424].cevr";
connectAttr "animCurveTU454.a" "clipLibrary1.cel[0].cev[425].cevr";
connectAttr "animCurveTU455.a" "clipLibrary1.cel[0].cev[426].cevr";
connectAttr "animCurveTA464.a" "clipLibrary1.cel[0].cev[427].cevr";
connectAttr "animCurveTA465.a" "clipLibrary1.cel[0].cev[428].cevr";
connectAttr "animCurveTA466.a" "clipLibrary1.cel[0].cev[429].cevr";
connectAttr "animCurveTU456.a" "clipLibrary1.cel[0].cev[433].cevr";
connectAttr "animCurveTU457.a" "clipLibrary1.cel[0].cev[434].cevr";
connectAttr "animCurveTU458.a" "clipLibrary1.cel[0].cev[435].cevr";
connectAttr "animCurveTA467.a" "clipLibrary1.cel[0].cev[436].cevr";
connectAttr "animCurveTA468.a" "clipLibrary1.cel[0].cev[437].cevr";
connectAttr "animCurveTA469.a" "clipLibrary1.cel[0].cev[438].cevr";
connectAttr "animCurveTU459.a" "clipLibrary1.cel[0].cev[442].cevr";
connectAttr "animCurveTU460.a" "clipLibrary1.cel[0].cev[443].cevr";
connectAttr "animCurveTU461.a" "clipLibrary1.cel[0].cev[444].cevr";
connectAttr "animCurveTA470.a" "clipLibrary1.cel[0].cev[445].cevr";
connectAttr "animCurveTA471.a" "clipLibrary1.cel[0].cev[446].cevr";
connectAttr "animCurveTA472.a" "clipLibrary1.cel[0].cev[447].cevr";
connectAttr "animCurveTU462.a" "clipLibrary1.cel[0].cev[451].cevr";
connectAttr "animCurveTU463.a" "clipLibrary1.cel[0].cev[452].cevr";
connectAttr "animCurveTU464.a" "clipLibrary1.cel[0].cev[453].cevr";
connectAttr "animCurveTA473.a" "clipLibrary1.cel[0].cev[454].cevr";
connectAttr "animCurveTA474.a" "clipLibrary1.cel[0].cev[455].cevr";
connectAttr "animCurveTA475.a" "clipLibrary1.cel[0].cev[456].cevr";
connectAttr "animCurveTU465.a" "clipLibrary1.cel[0].cev[460].cevr";
connectAttr "animCurveTU466.a" "clipLibrary1.cel[0].cev[461].cevr";
connectAttr "animCurveTU467.a" "clipLibrary1.cel[0].cev[462].cevr";
connectAttr "animCurveTA476.a" "clipLibrary1.cel[0].cev[463].cevr";
connectAttr "animCurveTA477.a" "clipLibrary1.cel[0].cev[464].cevr";
connectAttr "animCurveTA478.a" "clipLibrary1.cel[0].cev[465].cevr";
connectAttr "animCurveTU468.a" "clipLibrary1.cel[0].cev[469].cevr";
connectAttr "animCurveTU469.a" "clipLibrary1.cel[0].cev[470].cevr";
connectAttr "animCurveTU470.a" "clipLibrary1.cel[0].cev[471].cevr";
connectAttr "animCurveTA479.a" "clipLibrary1.cel[0].cev[472].cevr";
connectAttr "animCurveTA480.a" "clipLibrary1.cel[0].cev[473].cevr";
connectAttr "animCurveTA481.a" "clipLibrary1.cel[0].cev[474].cevr";
connectAttr "animCurveTU471.a" "clipLibrary1.cel[0].cev[505].cevr";
connectAttr "animCurveTU472.a" "clipLibrary1.cel[0].cev[506].cevr";
connectAttr "animCurveTU473.a" "clipLibrary1.cel[0].cev[507].cevr";
connectAttr "animCurveTA482.a" "clipLibrary1.cel[0].cev[508].cevr";
connectAttr "animCurveTA483.a" "clipLibrary1.cel[0].cev[509].cevr";
connectAttr "animCurveTA484.a" "clipLibrary1.cel[0].cev[510].cevr";
connectAttr "animCurveTL259.a" "clipLibrary1.cel[0].cev[511].cevr";
connectAttr "animCurveTL260.a" "clipLibrary1.cel[0].cev[512].cevr";
connectAttr "animCurveTL261.a" "clipLibrary1.cel[0].cev[513].cevr";
connectAttr "animCurveTU474.a" "clipLibrary1.cel[0].cev[550].cevr";
connectAttr "animCurveTU475.a" "clipLibrary1.cel[0].cev[551].cevr";
connectAttr "animCurveTU476.a" "clipLibrary1.cel[0].cev[552].cevr";
connectAttr "animCurveTA485.a" "clipLibrary1.cel[0].cev[553].cevr";
connectAttr "animCurveTA486.a" "clipLibrary1.cel[0].cev[554].cevr";
connectAttr "animCurveTA487.a" "clipLibrary1.cel[0].cev[555].cevr";
connectAttr "animCurveTL262.a" "clipLibrary1.cel[0].cev[556].cevr";
connectAttr "animCurveTL263.a" "clipLibrary1.cel[0].cev[557].cevr";
connectAttr "animCurveTL264.a" "clipLibrary1.cel[0].cev[558].cevr";
connectAttr "animCurveTA488.a" "clipLibrary1.cel[0].cev[568].cevr";
connectAttr "animCurveTA489.a" "clipLibrary1.cel[0].cev[569].cevr";
connectAttr "animCurveTA490.a" "clipLibrary1.cel[0].cev[570].cevr";
connectAttr "animCurveTA491.a" "clipLibrary1.cel[0].cev[571].cevr";
connectAttr "animCurveTA492.a" "clipLibrary1.cel[0].cev[572].cevr";
connectAttr "animCurveTA493.a" "clipLibrary1.cel[0].cev[573].cevr";
connectAttr "animCurveTA494.a" "clipLibrary1.cel[0].cev[574].cevr";
connectAttr "animCurveTA495.a" "clipLibrary1.cel[0].cev[575].cevr";
connectAttr "animCurveTA496.a" "clipLibrary1.cel[0].cev[576].cevr";
connectAttr "animCurveTA497.a" "clipLibrary1.cel[0].cev[577].cevr";
connectAttr "animCurveTA498.a" "clipLibrary1.cel[0].cev[578].cevr";
connectAttr "animCurveTA499.a" "clipLibrary1.cel[0].cev[579].cevr";
connectAttr "animCurveTA500.a" "clipLibrary1.cel[0].cev[580].cevr";
connectAttr "animCurveTA501.a" "clipLibrary1.cel[0].cev[581].cevr";
connectAttr "animCurveTA502.a" "clipLibrary1.cel[0].cev[582].cevr";
connectAttr "animCurveTA503.a" "clipLibrary1.cel[0].cev[583].cevr";
connectAttr "animCurveTA504.a" "clipLibrary1.cel[0].cev[584].cevr";
connectAttr "animCurveTA505.a" "clipLibrary1.cel[0].cev[585].cevr";
connectAttr "animCurveTA506.a" "clipLibrary1.cel[0].cev[586].cevr";
connectAttr "animCurveTA507.a" "clipLibrary1.cel[0].cev[587].cevr";
connectAttr "animCurveTA508.a" "clipLibrary1.cel[0].cev[588].cevr";
connectAttr "animCurveTA509.a" "clipLibrary1.cel[0].cev[589].cevr";
connectAttr "animCurveTA510.a" "clipLibrary1.cel[0].cev[590].cevr";
connectAttr "animCurveTA511.a" "clipLibrary1.cel[0].cev[591].cevr";
connectAttr "animCurveTU477.a" "clipLibrary1.cel[0].cev[592].cevr";
connectAttr "animCurveTU478.a" "clipLibrary1.cel[0].cev[593].cevr";
connectAttr "animCurveTU479.a" "clipLibrary1.cel[0].cev[594].cevr";
connectAttr "animCurveTA512.a" "clipLibrary1.cel[0].cev[595].cevr";
connectAttr "animCurveTA513.a" "clipLibrary1.cel[0].cev[596].cevr";
connectAttr "animCurveTA514.a" "clipLibrary1.cel[0].cev[597].cevr";
connectAttr "animCurveTU480.a" "clipLibrary1.cel[0].cev[601].cevr";
connectAttr "animCurveTU481.a" "clipLibrary1.cel[0].cev[602].cevr";
connectAttr "animCurveTU482.a" "clipLibrary1.cel[0].cev[603].cevr";
connectAttr "animCurveTA515.a" "clipLibrary1.cel[0].cev[604].cevr";
connectAttr "animCurveTA516.a" "clipLibrary1.cel[0].cev[605].cevr";
connectAttr "animCurveTA517.a" "clipLibrary1.cel[0].cev[606].cevr";
connectAttr "animCurveTA518.a" "clipLibrary1.cel[0].cev[610].cevr";
connectAttr "animCurveTA519.a" "clipLibrary1.cel[0].cev[611].cevr";
connectAttr "animCurveTA520.a" "clipLibrary1.cel[0].cev[612].cevr";
connectAttr "animCurveTL265.a" "clipLibrary1.cel[0].cev[613].cevr";
connectAttr "animCurveTL266.a" "clipLibrary1.cel[0].cev[614].cevr";
connectAttr "animCurveTL267.a" "clipLibrary1.cel[0].cev[615].cevr";
connectAttr "animCurveTU483.a" "clipLibrary1.cel[0].cev[616].cevr";
connectAttr "animCurveTU484.a" "clipLibrary1.cel[0].cev[617].cevr";
connectAttr "animCurveTU485.a" "clipLibrary1.cel[0].cev[618].cevr";
connectAttr "animCurveTA521.a" "clipLibrary1.cel[0].cev[619].cevr";
connectAttr "animCurveTA522.a" "clipLibrary1.cel[0].cev[620].cevr";
connectAttr "animCurveTA523.a" "clipLibrary1.cel[0].cev[621].cevr";
connectAttr "animCurveTL268.a" "clipLibrary1.cel[0].cev[622].cevr";
connectAttr "animCurveTL269.a" "clipLibrary1.cel[0].cev[623].cevr";
connectAttr "animCurveTL270.a" "clipLibrary1.cel[0].cev[624].cevr";
connectAttr "animCurveTU486.a" "clipLibrary1.cel[0].cev[634].cevr";
connectAttr "animCurveTU487.a" "clipLibrary1.cel[0].cev[635].cevr";
connectAttr "animCurveTU488.a" "clipLibrary1.cel[0].cev[636].cevr";
connectAttr "animCurveTU489.a" "clipLibrary1.cel[0].cev[637].cevr";
connectAttr "animCurveTA524.a" "clipLibrary1.cel[0].cev[638].cevr";
connectAttr "animCurveTA525.a" "clipLibrary1.cel[0].cev[639].cevr";
connectAttr "animCurveTA526.a" "clipLibrary1.cel[0].cev[640].cevr";
connectAttr "animCurveTL271.a" "clipLibrary1.cel[0].cev[641].cevr";
connectAttr "animCurveTL272.a" "clipLibrary1.cel[0].cev[642].cevr";
connectAttr "animCurveTL273.a" "clipLibrary1.cel[0].cev[643].cevr";
connectAttr "animCurveTU490.a" "clipLibrary1.cel[0].cev[653].cevr";
connectAttr "animCurveTU491.a" "clipLibrary1.cel[0].cev[654].cevr";
connectAttr "animCurveTU492.a" "clipLibrary1.cel[0].cev[655].cevr";
connectAttr "animCurveTA527.a" "clipLibrary1.cel[0].cev[656].cevr";
connectAttr "animCurveTA528.a" "clipLibrary1.cel[0].cev[657].cevr";
connectAttr "animCurveTA529.a" "clipLibrary1.cel[0].cev[658].cevr";
connectAttr "animCurveTU493.a" "clipLibrary1.cel[0].cev[662].cevr";
connectAttr "animCurveTU494.a" "clipLibrary1.cel[0].cev[663].cevr";
connectAttr "animCurveTU495.a" "clipLibrary1.cel[0].cev[664].cevr";
connectAttr "animCurveTA530.a" "clipLibrary1.cel[0].cev[665].cevr";
connectAttr "animCurveTA531.a" "clipLibrary1.cel[0].cev[666].cevr";
connectAttr "animCurveTA532.a" "clipLibrary1.cel[0].cev[667].cevr";
connectAttr "animCurveTL274.a" "clipLibrary1.cel[0].cev[668].cevr";
connectAttr "animCurveTL275.a" "clipLibrary1.cel[0].cev[669].cevr";
connectAttr "animCurveTL276.a" "clipLibrary1.cel[0].cev[670].cevr";
connectAttr "animCurveTU496.a" "clipLibrary1.cel[0].cev[671].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of idle.ma
