//Maya ASCII 2008 scene
//Name: death.ma
//Last modified: Wed, Aug 26, 2009 11:02:04 AM
//Codeset: 1251
requires maya "2008";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Complete 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200802250025-718075";
fileInfo "osv" "Microsoft Windows Vista Service Pack 2 (Build 6002)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 672 ".cel[0].cev";
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
createNode animClip -n "deathSource";
	setAttr ".ihi" 0;
	setAttr -s 672 ".ac";
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
	setAttr ".ac[500:671]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes no no no yes yes yes no no no no;
	setAttr ".se" 31;
	setAttr ".ci" no;
createNode animCurveTU -n "animCurveTU703";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 10 2 10;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  2;
createNode animCurveTA -n "animCurveTA858";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 0 2 0;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  2;
createNode animCurveTA -n "animCurveTA859";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 0 2 0;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  2;
createNode animCurveTA -n "animCurveTA860";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 0 2 0;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  2;
createNode animCurveTL -n "animCurveTL418";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 0 2 0;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  2;
createNode animCurveTL -n "animCurveTL419";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 0 2 0;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  2;
createNode animCurveTL -n "animCurveTL420";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 0 2 0;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  2;
createNode animCurveTU -n "animCurveTU704";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1 1 1 2 1 4 1 7 1 10 1 13 1 16 1 18 1 
		20 1 23 1;
createNode animCurveTU -n "animCurveTU705";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1 1 1 2 1 4 1 7 1 10 1 13 1 16 1 18 1 
		20 1 23 1;
createNode animCurveTU -n "animCurveTU706";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1 1 1 2 1 4 1 7 1 10 1 13 1 16 1 18 1 
		20 1 23 1;
createNode animCurveTU -n "animCurveTU707";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
	setAttr -s 11 ".kit[10]"  9;
	setAttr -s 11 ".kot[10]"  5;
createNode animCurveTA -n "animCurveTA861";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTA -n "animCurveTA862";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTA -n "animCurveTA863";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTU -n "animCurveTU708";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1 1 1 2 1 4 1 7 1 10 1 13 1 16 1 18 1 
		20 1 23 1;
	setAttr -s 11 ".kit[10]"  9;
	setAttr -s 11 ".kot[10]"  5;
createNode animCurveTU -n "animCurveTU709";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
	setAttr -s 11 ".kit[10]"  9;
	setAttr -s 11 ".kot[10]"  5;
createNode animCurveTU -n "animCurveTU710";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 10 1 10 2 10 4 10 7 10 10 10 13 10 16 
		10 18 10 20 10 23 10;
createNode animCurveTU -n "animCurveTU711";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1 1 1 2 1 4 1 7 1 10 1 13 1 16 1 18 1 
		20 1 23 1;
	setAttr -s 11 ".kit[10]"  9;
	setAttr -s 11 ".kot[10]"  5;
createNode animCurveTU -n "animCurveTU712";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
	setAttr -s 11 ".kit[10]"  9;
	setAttr -s 11 ".kot[10]"  5;
createNode animCurveTU -n "animCurveTU713";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 10 1 10 2 10 4 10 7 10 10 10 13 10 16 
		10 18 10 20 10 23 10;
createNode animCurveTU -n "animCurveTU714";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1 1 1 2 1 4 1 7 1 10 1 13 1 16 1 18 1 
		20 1 23 1;
	setAttr -s 11 ".kit[10]"  9;
	setAttr -s 11 ".kot[10]"  5;
createNode animCurveTU -n "animCurveTU715";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
	setAttr -s 11 ".kit[10]"  9;
	setAttr -s 11 ".kot[10]"  5;
createNode animCurveTU -n "animCurveTU716";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTU -n "animCurveTU717";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1 1 1 2 1 4 1 7 1 10 1 13 1 16 1 18 1 
		20 1 23 1;
	setAttr -s 11 ".kit[10]"  9;
	setAttr -s 11 ".kot[10]"  5;
createNode animCurveTU -n "animCurveTU718";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
	setAttr -s 11 ".kit[10]"  9;
	setAttr -s 11 ".kot[10]"  5;
createNode animCurveTU -n "animCurveTU719";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 10 1 10 2 10 4 10 7 10 10 10 13 10 16 
		10 18 10 20 10 23 10;
createNode animCurveTU -n "animCurveTU720";
	setAttr ".tan" 2;
	setAttr -s 10 ".ktv[0:9]"  0 1 1 1 2 1 4 1 7 1 10 1 13 1 18 1 20 1 
		23 1;
	setAttr -s 10 ".kit[9]"  9;
	setAttr -s 10 ".kot[9]"  5;
createNode animCurveTU -n "animCurveTU721";
	setAttr ".tan" 2;
	setAttr -s 10 ".ktv[0:9]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 18 0 20 0 
		23 0;
	setAttr -s 10 ".kit[9]"  9;
	setAttr -s 10 ".kot[9]"  5;
createNode animCurveTU -n "animCurveTU722";
	setAttr ".tan" 2;
	setAttr -s 10 ".ktv[0:9]"  0 10 1 10 2 10 4 10 7 10 10 10 13 10 18 
		10 20 10 23 10;
createNode animCurveTU -n "animCurveTU723";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1 1 1 2 1 4 1 7 1 10 1 13 1 16 1 18 1 
		20 1 23 1;
	setAttr -s 11 ".kit[10]"  9;
	setAttr -s 11 ".kot[10]"  5;
createNode animCurveTU -n "animCurveTU724";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
	setAttr -s 11 ".kit[10]"  9;
	setAttr -s 11 ".kot[10]"  5;
createNode animCurveTU -n "animCurveTU725";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 10 1 10 2 10 4 10 7 10 10 10 13 10 16 
		10 18 10 20 10 23 10;
createNode animCurveTU -n "animCurveTU726";
	setAttr ".tan" 2;
	setAttr -s 10 ".ktv[0:9]"  0 10 1 10 2 10 4 10 7 10 10 10 13 10 16 
		10 18 10 20 10;
createNode animCurveTL -n "animCurveTL421";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.0051987098671592413 1 0.0051987098671592413 
		2 0.0051987098671592413 4 0.0051987098671592413 7 0.0051987098671592413 10 0.0051987098671592413 
		13 0.0051987098671592413 16 0.0051987098671592413 18 0.0051987098671592413 20 0.0051987098671592413 
		25 0.21558372035904674;
	setAttr -s 11 ".kit[10]"  3;
	setAttr -s 11 ".kot[10]"  3;
createNode animCurveTL -n "animCurveTL422";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 -0.0029658564141476066 1 -0.0029658564141476066 
		2 -0.0029658564141476066 4 -0.0029658564141476066 7 -0.0029658564141476066 10 -0.0029658564141476066 
		13 -0.0029658564141476066 16 -0.0029658564141476066 18 -0.0029658564141476066 20 
		-0.0029658564141476066 25 0.017038059211734097;
	setAttr -s 11 ".kit[10]"  3;
	setAttr -s 11 ".kot[10]"  3;
createNode animCurveTL -n "animCurveTL423";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 -0.088864011310046689 1 -0.088864011310046689 
		2 -0.088864011310046689 4 -0.088864011310046689 7 -0.088864011310046689 10 -0.088864011310046689 
		13 -0.088864011310046689 16 -0.088864011310046689 18 -0.088864011310046689 20 -0.088864011310046689 
		25 0.30930552936738481;
	setAttr -s 11 ".kit[10]"  3;
	setAttr -s 11 ".kot[10]"  3;
createNode animCurveTL -n "animCurveTL424";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL425";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL426";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA864";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 1 0 2 0;
createNode animCurveTA -n "animCurveTA865";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA866";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 3.975693351829394e-016;
createNode animCurveTA -n "animCurveTA867";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA868";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTA -n "animCurveTA869";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTA -n "animCurveTA870";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTA -n "animCurveTA871";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA872";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA873";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU727";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 1 1 1 2 1 4 1;
createNode animCurveTU -n "animCurveTU728";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 1 1 1 2 1 4 1;
createNode animCurveTU -n "animCurveTU729";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 0 1 0 2 0 4 0;
createNode animCurveTU -n "animCurveTU730";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 0 1 0 2 0 4 0;
createNode animCurveTU -n "animCurveTU731";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 10 1 10 2 10 4 10;
createNode animCurveTU -n "animCurveTU732";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 30 1 30 2 30 4 30;
createNode animCurveTU -n "animCurveTU733";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 0 1 0 2 0 4 0;
createNode animCurveTU -n "animCurveTU734";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 0 1 0 2 0 4 0;
createNode animCurveTA -n "animCurveTA874";
	setAttr ".tan" 9;
	setAttr -s 14 ".ktv[0:13]"  0 10.65881532857289 1 10.65881532857289 
		2 5.2095984616257516 3 -1.1097981999882267 4 -6.0375361319409908 5 -8.8968039094100053 
		7 -7.7199238109440405 9 2.3260853046948737 13 0.10783508296826383 15 -9.4589827870464092 
		19 -25.265705912607476 21 -33.932937622606026 24 -48.417851952657649 25 -54.261146485273208;
	setAttr -s 14 ".kit[7:13]"  1 1 9 9 9 9 9;
	setAttr -s 14 ".kot[7:13]"  1 1 9 9 9 9 9;
	setAttr -s 14 ".kix[7:13]"  0.060524065047502518 0.12530438601970673 
		0.066666662693023682 0.13333332538604736 0.066666662693023682 0.10000002384185791 
		0.033333301544189453;
	setAttr -s 14 ".kiy[7:13]"  0.12901203334331512 -0.33521151542663574 
		-0.14761728048324585 -0.28476738929748535 -0.16163244843482971 -0.26609569787979126 
		-0.10198473185300827;
	setAttr -s 14 ".kox[7:13]"  0.12718969583511353 0.025306489318609238 
		0.13333332538604736 0.066666662693023682 0.10000002384185791 0.033333301544189453 
		0.033333301544189453;
	setAttr -s 14 ".koy[7:13]"  0.27111536264419556 -0.067699357867240906 
		-0.2952345609664917 -0.14238369464874268 -0.24244873225688934 -0.088698461651802063 
		-0.10198473185300827;
createNode animCurveTA -n "animCurveTA875";
	setAttr ".tan" 9;
	setAttr -s 15 ".ktv[0:14]"  0 0 1 0 2 -7.8050752073379188 3 -10.214797991558637 
		4 -8.4873916982886097 5 -4.7650511756933049 7 1.4252597888281788 9 4.7928048618707049 
		13 -1.4479625346559284 15 -7.5817939000604486 17 -14.62561064114781 19 -26.997361485890309 
		21 -53.045500903571877 24 -84.872812668989184 25 -93.565065612396495;
	setAttr -s 15 ".kit[0:14]"  3 3 9 9 9 9 1 3 
		1 9 1 9 9 9 9;
	setAttr -s 15 ".kot[0:14]"  3 3 9 9 9 9 1 3 
		1 9 1 9 9 9 9;
	setAttr -s 15 ".kix[6:14]"  0.06232060119509697 0.066666677594184875 
		0.12286743521690369 0.066666662693023682 0.070732258260250092 0.066666662693023682 
		0.066666662693023682 0.10000002384185791 0.033333301544189453;
	setAttr -s 15 ".kiy[6:14]"  0.11043737083673477 0 -0.20777586102485657 
		-0.11499667167663574 -0.15724413096904755 -0.33527678251266479 -0.40404680371284485 
		-0.53040003776550293 -0.15170843899250031;
	setAttr -s 15 ".kox[6:14]"  0.062320616096258163 0.13333332538604736 
		0.056202910840511322 0.066666662693023682 0.070732258260250092 0.066666662693023682 
		0.10000002384185791 0.033333301544189453 0.033333301544189453;
	setAttr -s 15 ".koy[6:14]"  0.11043740808963776 0 -0.095042333006858826 
		-0.11499667167663574 -0.15724414587020874 -0.33527678251266479 -0.60607039928436279 
		-0.17679978907108307 -0.15170843899250031;
createNode animCurveTA -n "animCurveTA876";
	setAttr ".tan" 9;
	setAttr -s 20 ".ktv[0:19]"  0 0 1 0 2 49.77217349244016 3 98.361457311871106 
		4 142.94521122009914 6 220.6642084125528 8 290.28847935619626 9 322.46797633930413 
		11 387.89847893941635 12 425.73116928380927 13 458.54207184309092 14 482.7730752015504 
		15 499.86339413692809 17 524.84852210446354 19 538.24621269965166 21 553.89940136260441 
		24 620.26194084781844 25 640.29498683707914 28 622.20771633137031 31 641.01929194871559;
	setAttr -s 20 ".kit[7:19]"  1 9 9 9 9 9 1 1 
		9 1 3 3 3;
	setAttr -s 20 ".kot[7:19]"  1 9 9 9 9 9 1 1 
		9 1 3 3 3;
	setAttr -s 20 ".kix[7:19]"  0.033287867903709412 0.066666662693023682 
		0.033333331346511841 0.033333331346511841 0.033333331346511841 0.033333331346511841 
		0.066529802978038788 0.067718960344791412 0.066666662693023682 0.094124533236026764 
		0.033333301544189453 0.10000002384185791 0.099999964237213135;
	setAttr -s 20 ".kiy[7:19]"  0.52681678533554077 1.2015217542648315 
		0.61648166179656982 0.49778452515602112 0.36059656739234924 0.24478502571582794 0.34225597977638245 
		0.13065671920776367 0.57257771492004395 1.5364524126052856 0 0 0;
	setAttr -s 20 ".kox[7:19]"  0.066621206700801849 0.033333331346511841 
		0.033333331346511841 0.033333331346511841 0.033333331346511841 0.066666662693023682 
		0.066529788076877594 0.067718960344791412 0.10000002384185791 0.027459299191832542 
		0.10000002384185791 0.099999964237213135 0.099999964237213135;
	setAttr -s 20 ".koy[7:19]"  1.0543527603149414 0.60076087713241577 
		0.61648166179656982 0.49778452515602112 0.36059656739234924 0.48957005143165588 0.34225594997406006 
		0.13065671920776367 0.85886681079864502 0.44823497533798218 0 0 0;
createNode animCurveTL -n "animCurveTL427";
	setAttr ".tan" 9;
	setAttr -s 24 ".ktv[0:23]"  0 0 1 0 2 0.78588348632064609 3 1.3525300593282006 
		4 1.9686197157907876 5 2.5306748615589063 6 2.9971561692723125 7 3.0846050663799378 
		8 2.5094686536052024 9 1.6939674983568955 10 0.91617147276057243 11 0.58538456796975313 
		12 0.50968556450621705 13 0.69095305842121124 14 0.86864472808020698 15 1.0597470897889381 
		17 1.2294079192655978 19 1.1973948048565892 21 1.0147440682948172 23 0.60932902799454502 
		24 0.42400126558334533 25 0.2740665382166681 28 0.35547442656168809 31 0.28468495843558478;
	setAttr -s 24 ".kit[7:23]"  1 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9;
	setAttr -s 24 ".kot[7:23]"  1 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9;
	setAttr -s 24 ".kix[7:23]"  0.033281669020652771 0.033333346247673035 
		0.033333331346511841 0.033333331346511841 0.033333331346511841 0.033333331346511841 
		0.033333331346511841 0.033333331346511841 0.033333331346511841 0.066666662693023682 
		0.066666662693023682 0.066666662693023682 0.066666662693023682 0.033333361148834229 
		0.033333301544189453 0.10000002384185791 0.099999964237213135;
	setAttr -s 24 ".kiy[7:23]"  -0.094382621347904205 -0.69531893730163574 
		-0.79664856195449829 -0.5542914867401123 -0.2032429575920105 0.05278424546122551 
		0.17947958409786224 0.18439701199531555 0.12025439739227295 0.068823859095573425 
		-0.10733192414045334 -0.29403290152549744 -0.39382842183113098 -0.16763138771057129 
		-0.017131693661212921 0.0053092115558683872 -0.07078947126865387;
	setAttr -s 24 ".kox[7:23]"  0.033281683921813965 0.033333331346511841 
		0.033333331346511841 0.033333331346511841 0.033333331346511841 0.033333331346511841 
		0.033333331346511841 0.033333331346511841 0.066666662693023682 0.066666662693023682 
		0.066666662693023682 0.066666662693023682 0.033333361148834229 0.033333301544189453 
		0.10000002384185791 0.099999964237213135 0.099999964237213135;
	setAttr -s 24 ".koy[7:23]"  -0.09438265860080719 -0.69531863927841187 
		-0.79664856195449829 -0.5542914867401123 -0.2032429575920105 0.05278424546122551 
		0.17947958409786224 0.18439701199531555 0.2405087947845459 0.068823859095573425 -0.10733192414045334 
		-0.29403290152549744 -0.19691438972949982 -0.16763108968734741 -0.051395144313573837 
		0.0053092082962393761 -0.07078947126865387;
createNode animCurveTL -n "animCurveTL428";
	setAttr ".tan" 9;
	setAttr -s 24 ".ktv[0:23]"  0 -0.055827347319821544 1 -0.055827347319821544 
		2 -0.65125495745758666 3 -0.89932018969746452 4 -1.243068194457049 5 -1.6426174033410053 
		6 -2.2452286173992104 7 -3.0837546265635352 8 -3.907430956638918 9 -4.0993521655671241 
		10 -3.9503108803608562 11 -3.7170024527194965 12 -3.6916198242040617 13 -3.8237937150021155 
		14 -4.0987129020216893 15 -4.5285665535444357 17 -5.316379797158695 19 -5.7415197607729951 
		21 -6.0006158649332626 23 -6.1770806487715282 24 -6.2651337339952535 25 -6.3755947987953094 
		28 -6.4165744734605532 31 -6.4675947190241834;
	setAttr -s 24 ".kit[21:23]"  1 1 3;
	setAttr -s 24 ".kot[21:23]"  1 1 3;
	setAttr -s 24 ".kix[21:23]"  0.030516406521201134 0.097479365766048431 
		0.099999964237213135;
	setAttr -s 24 ".kiy[21:23]"  -0.028770959004759789 -0.047863852232694626 
		0;
	setAttr -s 24 ".kox[21:23]"  0.091549314558506012 0.097479306161403656 
		0.099999964237213135;
	setAttr -s 24 ".koy[21:23]"  -0.086312979459762573 -0.047863822430372238 
		0;
createNode animCurveTL -n "animCurveTL429";
	setAttr ".tan" 9;
	setAttr -s 13 ".ktv[0:12]"  0 -0.057269223867906088 1 -0.057269223867906088 
		2 0.022769083851066282 6 0.12166148838262833 9 0.10184584904129858 13 0.01758582282271845 
		15 -0.25465303093289432 17 -0.73850813722850506 19 -1.1797409988417422 21 -1.5578771923007722 
		23 -1.8111421353760475 25 -1.9154998041501798 31 -1.9496232692738107;
	setAttr -s 13 ".kit[2:12]"  1 3 1 9 9 9 9 9 
		9 1 3;
	setAttr -s 13 ".kot[2:12]"  1 3 1 9 9 9 9 9 
		9 1 3;
	setAttr -s 13 ".kix[2:12]"  0.032198663800954819 0.13333332538604736 
		0.10065150260925293 0.13333332538604736 0.066666662693023682 0.066666662693023682 
		0.066666662693023682 0.066666662693023682 0.066666662693023682 0.064530223608016968 
		0.19999998807907104;
	setAttr -s 13 ".kiy[2:12]"  0.058629941195249557 0 -0.037733960896730423 
		-0.23766592144966125 -0.37804698944091797 -0.46254399418830872 -0.40968453884124756 
		-0.31570056080818176 -0.17881131172180176 -0.040547288954257965 0;
	setAttr -s 13 ".kox[2:12]"  0.12879464030265808 0.10000000894069672 
		0.13420198857784271 0.066666662693023682 0.066666662693023682 0.066666662693023682 
		0.066666662693023682 0.066666662693023682 0.066666662693023682 0.19359064102172852 
		0.19999998807907104;
	setAttr -s 13 ".koy[2:12]"  0.23451973497867584 0 -0.05031193420290947 
		-0.11883296072483063 -0.37804698944091797 -0.46254399418830872 -0.40968453884124756 
		-0.31570056080818176 -0.17881131172180176 -0.1216418668627739 0;
createNode animCurveTA -n "animCurveTA877";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA878";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA879";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL430";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL431";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.1102230246251565e-016;
createNode animCurveTL -n "animCurveTL432";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU735";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 10 1 10 2 10 4 10 7 10 10 10 13 10 16 
		10 18 10 20 10 23 10;
createNode animCurveTL -n "animCurveTL433";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.0012535188113739458 1 0.0012535188113739458 
		2 0.0012535188113739458 4 0.0012535188113739458 7 0.0012535188113739458 10 0.0012535188113739458 
		13 0.0012535188113739458 16 0.0012535188113739458 18 0.0012535188113739458 20 -0.3021483637757435 
		23 -0.3021483637757435;
createNode animCurveTL -n "animCurveTL434";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 -0.0030683908186687247 1 -0.0030683908186687247 
		2 -0.0030683908186687247 4 -0.0030683908186687247 7 -0.0030683908186687247 10 -0.0030683908186687247 
		13 -0.0030683908186687247 16 -0.0030683908186687247 18 -0.0030683908186687247 20 
		-0.30504905356359657 23 -0.30504905356359657;
createNode animCurveTL -n "animCurveTL435";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 -0.0037897911519002383 1 -0.0037897911519002383 
		2 -0.0037897911519002383 4 -0.0037897911519002383 7 -0.0037897911519002383 10 -0.0037897911519002383 
		13 -0.0037897911519002383 16 -0.0037897911519002383 18 -0.0037897911519002383 20 
		0.34286039967359988 23 0.34286039967359988;
createNode animCurveTL -n "animCurveTL436";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL437";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL438";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA880";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 0 1 -27.393044308042384 2 -27.393044308042384 
		3 0;
	setAttr -s 4 ".kit[3]"  3;
	setAttr -s 4 ".kot[3]"  3;
createNode animCurveTA -n "animCurveTA881";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA882";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 7.951386703658785e-016;
createNode animCurveTA -n "animCurveTA883";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA884";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTA -n "animCurveTA885";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTA -n "animCurveTA886";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTA -n "animCurveTA887";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA888";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA889";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU736";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1 1 1 2 1 4 1 7 1 10 1 13 1 16 1 18 1 
		21 1 24 1;
createNode animCurveTU -n "animCurveTU737";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1 1 1 2 1 4 1 7 1 10 1 13 1 16 1 18 1 
		21 1 24 1;
createNode animCurveTU -n "animCurveTU738";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		21 0 24 0;
createNode animCurveTU -n "animCurveTU739";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		21 0 24 0;
createNode animCurveTU -n "animCurveTU740";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 10 1 10 2 10 4 10 7 10 10 10 13 10 16 
		10 18 10 21 10 24 10;
createNode animCurveTU -n "animCurveTU741";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 25 1 25 2 25 4 25 7 25 10 25 13 25 16 
		25 18 25 21 25 24 25;
createNode animCurveTU -n "animCurveTU742";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		21 0 24 0;
createNode animCurveTU -n "animCurveTU743";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		21 0 24 0;
createNode animCurveTA -n "animCurveTA890";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 -8.5560819804359109 1 -8.5560819804359109 
		2 -8.5560819804359109 3 0.23310236299487674 4 -0.064386568964475518 5 1.2988809020886349 
		6 -4.5292914818778121 7 7.0073440894372476 9 2.2643655687007835 10 4.215373209606744 
		13 -12.900507803698448 16 -27.029146628439456 18 -22.972596895512396 21 -45.941924821533568 
		24 -45.941924821533568 28 -36.9485040772377;
	setAttr -s 16 ".kit[3:15]"  3 2 3 3 2 3 2 2 
		2 2 2 2 3;
	setAttr -s 16 ".kot[3:15]"  3 2 3 3 2 3 2 2 
		2 2 2 2 3;
createNode animCurveTA -n "animCurveTA891";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 -0.31694341854885294 1 -0.31694341854885294 
		2 -0.31694341854885294 3 5.9569926963293112 4 8.5616662772617449 5 -2.9188292175432533 
		6 -0.59449735104186041 7 -4.932021307020424 9 -5.3778603928569293 10 3.3757847260507883 
		13 -3.8549969969009688 16 2.1694374806401395 18 -29.883503289920288 21 -73.111956654793843 
		24 -73.111956654793843 28 -109.56295788353152;
	setAttr -s 16 ".kit[3:15]"  3 2 3 3 2 3 2 2 
		2 2 2 2 3;
	setAttr -s 16 ".kot[3:15]"  3 2 3 3 2 3 2 2 
		2 2 2 2 3;
createNode animCurveTA -n "animCurveTA892";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 -0.51931341167670197 1 -0.51931341167670197 
		2 -0.51931341167670197 3 93.764204257340651 4 91.182383656617148 5 102.98355018077335 
		6 113.71230955589782 7 -143.11659244237626 9 -116.52685391269897 10 -41.29454157220313 
		13 133.26922834304921 16 170.0029665786013 18 168.14071965948713 21 244.81004652997822 
		24 294.43829380408596 28 252.1988684819818;
	setAttr -s 16 ".kit[3:15]"  3 2 3 3 2 3 2 2 
		2 2 2 2 3;
	setAttr -s 16 ".kot[3:15]"  3 2 3 3 2 3 2 2 
		2 2 2 2 3;
createNode animCurveTL -n "animCurveTL439";
	setAttr ".tan" 2;
	setAttr -s 17 ".ktv[0:16]"  0 0.00076651281650793874 1 0.00076651281650793874 
		2 0.00076651281650793874 3 0.50229383862919497 4 0.95963094981894281 5 1.5764456520700108 
		6 2.220576646537133 7 2.8243645577350098 8 2.7699301768337476 9 2.3708539117892751 
		10 1.4872682806004685 13 0.20986156168341594 16 0.9186434494736756 18 0.98324426153631805 
		21 0.71522048653463466 24 0.73751054110457837 28 0.68727752454978353;
	setAttr -s 17 ".kit[5:16]"  3 3 2 3 3 2 2 2 
		2 2 2 3;
	setAttr -s 17 ".kot[5:16]"  3 3 2 3 3 2 2 2 
		2 2 2 3;
createNode animCurveTL -n "animCurveTL440";
	setAttr ".tan" 2;
	setAttr -s 17 ".ktv[0:16]"  0 0.27472958484748605 1 0.27472958484748605 
		2 0.27472958484748605 3 0.23005795041763999 4 0.14483916713676559 5 0.020462230102717471 
		6 -0.27226035259165349 7 -1.1694969027055124 8 -1.9367016916937154 9 -2.6788824866456413 
		10 -2.8673420419117708 13 -3.1013011102266179 16 -3.7291660175186925 18 -3.8952118827742912 
		21 -4.3469403359292595 24 -4.4207085214330197 28 -4.4228405446971877;
	setAttr -s 17 ".kit[5:16]"  3 3 2 3 3 2 2 2 
		2 2 2 3;
	setAttr -s 17 ".kot[5:16]"  3 3 2 3 3 2 2 2 
		2 2 2 3;
createNode animCurveTL -n "animCurveTL441";
	setAttr ".tan" 2;
	setAttr -s 15 ".ktv[0:14]"  0 -0.071005957816697135 1 -0.071005957816697135 
		2 -0.071005957816697135 4 -0.071005957816697135 5 0.060323375316077329 7 0.16456639198364756 
		8 0.2012133771571267 9 0.12882277651100454 10 -0.017762753785427243 13 0.22751728351554423 
		16 -0.12913025257930716 18 -0.57332979291822905 21 -0.96241610348095985 24 -0.97802141959221955 
		28 -0.99357745449800228;
	setAttr -s 15 ".kit[4:14]"  3 2 3 3 2 2 2 2 
		2 2 3;
	setAttr -s 15 ".kot[4:14]"  3 2 3 3 2 2 2 2 
		2 2 3;
createNode animCurveTA -n "animCurveTA893";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA894";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA895";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL442";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL443";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL444";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU744";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU745";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA896";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA897";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA898";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL445";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL446";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL447";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU746";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU747";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU748";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA899";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA900";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA901";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL448";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL449";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL450";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU749";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU750";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA902";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA903";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA904";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL451";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL452";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL453";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU751";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU752";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU753";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA905";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA906";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA907";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL454";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL455";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL456";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU754";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU755";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA908";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA909";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA910";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL457";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL458";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL459";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU756";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU757";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU758";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA911";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA912";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA913";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL460";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL461";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL462";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU759";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU760";
	setAttr ".tan" 2;
	setAttr -s 10 ".ktv[0:9]"  0 10 1 10 2 10 4 10 7 10 10 10 13 10 18 
		10 20 10 23 10;
createNode animCurveTL -n "animCurveTL463";
	setAttr ".tan" 2;
	setAttr -s 10 ".ktv[0:9]"  0 0.0054999194138878266 1 0.0054999194138878266 
		2 0.0054999194138878266 4 0.0054999194138878266 7 0.0054999194138878266 10 0.0054999194138878266 
		13 0.0054999194138878266 18 0.0054999194138878266 20 0.0054999194138878266 23 0.0054999194138878266;
createNode animCurveTL -n "animCurveTL464";
	setAttr ".tan" 2;
	setAttr -s 10 ".ktv[0:9]"  0 -0.0031376960222415048 1 -0.0031376960222415048 
		2 -0.0031376960222415048 4 -0.0031376960222415048 7 -0.0031376960222415048 10 -0.0031376960222415048 
		13 -0.0031376960222415048 18 -0.0031376960222415048 20 -0.0031376960222415048 23 
		-0.0031376960222415048;
createNode animCurveTL -n "animCurveTL465";
	setAttr ".tan" 2;
	setAttr -s 10 ".ktv[0:9]"  0 0.083911116250119933 1 0.083911116250119933 
		2 0.083911116250119933 4 0.083911116250119933 7 0.083911116250119933 10 0.083911116250119933 
		13 0.083911116250119933 18 0.083911116250119933 20 0.083911116250119933 23 0.083911116250119933;
createNode animCurveTL -n "animCurveTL466";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL467";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL468";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA914";
	setAttr ".tan" 2;
	setAttr -s 3 ".ktv[0:2]"  0 0 1 0 2 0;
createNode animCurveTA -n "animCurveTA915";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA916";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA917";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA918";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTA -n "animCurveTA919";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTA -n "animCurveTA920";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTA -n "animCurveTA921";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA922";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA923";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU761";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 1 1 1 2 1 4 1;
createNode animCurveTU -n "animCurveTU762";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 1 1 1 2 1 4 1;
createNode animCurveTU -n "animCurveTU763";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 0 1 0 2 0 4 0;
createNode animCurveTU -n "animCurveTU764";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 0 1 0 2 0 4 0;
createNode animCurveTU -n "animCurveTU765";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 10 1 10 2 10 4 10;
createNode animCurveTU -n "animCurveTU766";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 30 1 30 2 30 4 30;
createNode animCurveTU -n "animCurveTU767";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 0 1 0 2 0 4 0;
createNode animCurveTU -n "animCurveTU768";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 0 1 0 2 0 4 0;
createNode animCurveTA -n "animCurveTA924";
	setAttr ".tan" 1;
	setAttr -s 19 ".ktv[0:18]"  0 -9.8142060506602 1 -9.8142060506602 2 
		-3.8115836824339921 4 5.1972299056979372 5 7.6042551373529363 7 8.9209993365603264 
		8 0.6842701618567677 9 -6.3844004457761239 11 -8.8539625353193792 12 -1.9613843521261018 
		13 3.1027917348978207 14 3.6140554791094979 15 0.57005700452117036 17 -11.883917666504669 
		19 -17.610416614365608 21 -16.894686002262642 22 -8.3943857998352964 25 15.406429429518322 
		28 -3.0246132832643147;
	setAttr -s 19 ".kit[0:18]"  9 9 1 1 1 3 1 9 
		3 1 1 1 9 9 1 1 1 3 3;
	setAttr -s 19 ".kot[0:18]"  9 9 1 1 1 3 1 9 
		3 1 1 1 9 9 1 1 1 3 3;
	setAttr -s 19 ".kix[2:18]"  0.026351386681199074 0.067301549017429352 
		0.032432250678539276 0.066666662693023682 0.032977648079395294 0.033333331346511841 
		0.066666662693023682 0.032923988997936249 0.033563371747732162 0.033318944275379181 
		0.033333331346511841 0.066666662693023682 0.066900573670864105 0.067161634564399719 
		0.031722042709589005 0.099999964237213135 0.10000002384185791;
	setAttr -s 19 ".kiy[2:18]"  0.090732462704181671 0.1014883741736412 
		0.031447645276784897 0 -0.16148200631141663 -0.055491186678409576 0 0.12910324335098267 
		0.037661314010620117 -0.0077756261453032494 -0.090163551270961761 -0.15865455567836761 
		-0.036495555192232132 0.08133842796087265 0.17750616371631622 0 0;
	setAttr -s 19 ".kox[2:18]"  0.059682451188564301 0.033968117088079453 
		0.065765440464019775 0.033333346247673035 0.0329776331782341 0.066666662693023682 
		0.033333331346511841 0.032923988997936249 0.033563371747732162 0.033318944275379181 
		0.066666662693023682 0.066666662693023682 0.066900573670864105 0.0338282510638237 
		0.098388299345970154 0.10000002384185791 0.10000002384185791;
	setAttr -s 19 ".koy[2:18]"  0.20549722015857697 0.051222722977399826 
		0.063768878579139709 0 -0.16148190200328827 -0.11098237335681915 0 0.12910325825214386 
		0.037661314010620117 -0.007775627076625824 -0.18032710254192352 -0.15865455567836761 
		-0.036495547741651535 0.040968894958496094 0.55054867267608643 0 0;
createNode animCurveTA -n "animCurveTA925";
	setAttr ".tan" 9;
	setAttr -s 20 ".ktv[0:19]"  0 0 1 0 2 9.64361633534463 3 9.6148878113345191 
		4 7.7782663769280624 5 5.5033623357701451 7 -0.5587313025918561 8 -3.5766482557124726 
		9 -3.6386016927060179 11 1.2301608645320545 12 5.3450298337414273 13 8.3866223617862445 
		14 4.0841902738939968 15 -1.2883861712411455 17 -5.8811207406764749 19 2.6989301734548166 
		21 -34.090241908886675 22 -58.580423317341051 25 -74.483039137938022 28 -74.229392424401652;
	setAttr -s 20 ".kit[6:19]"  1 9 9 9 9 3 9 9 
		9 3 1 9 9 9;
	setAttr -s 20 ".kot[6:19]"  1 9 9 9 9 3 9 9 
		9 3 1 9 9 9;
	setAttr -s 20 ".kix[6:19]"  0.06735624372959137 0.033333346247673035 
		0.033333331346511841 0.066666662693023682 0.033333331346511841 0.033333331346511841 
		0.033333331346511841 0.033333331346511841 0.066666662693023682 0.066666662693023682 
		0.065443083643913269 0.033333361148834229 0.099999964237213135 0.10000002384185791;
	setAttr -s 20 ".kiy[6:19]"  -0.083353236317634583 -0.026876945048570633 
		0.027964882552623749 0.10452929884195328 0.062451906502246857 0 -0.084430374205112457 
		-0.057975828647613525 0.034795898944139481 0 -0.95423728227615356 -0.17624698579311371 
		-0.13656297326087952 0.0044269701465964317;
	setAttr -s 20 ".kox[6:19]"  0.034022815525531769 0.033333331346511841 
		0.066666662693023682 0.033333331346511841 0.033333331346511841 0.033333331346511841 
		0.033333331346511841 0.066666662693023682 0.066666662693023682 0.066666662693023682 
		0.032109979540109634 0.099999964237213135 0.10000002384185791 0.10000002384185791;
	setAttr -s 20 ".koy[6:19]"  -0.042103167623281479 -0.026876933872699738 
		0.055929765105247498 0.052264649420976639 0.062451906502246857 0 -0.084430374205112457 
		-0.11595165729522705 0.034795898944139481 0 -0.46820124983787537 -0.52874034643173218 
		-0.13656306266784668 0.0044269701465964317;
createNode animCurveTA -n "animCurveTA926";
	setAttr ".tan" 9;
	setAttr -s 19 ".ktv[0:18]"  0 0 1 0 2 59.065485809691374 3 101.57033660524334 
		4 130.96681468404526 5 154.82313022764035 7 213.69384226458982 8 248.26960566323774 
		9 288.06363852864877 11 380.38789641271092 12 425.65213808311847 13 465.99764479066977 
		14 490.94717425156165 15 507.063376145186 17 531.69553261795227 19 546.74024379789637 
		21 553.87426197688796 25 569.08718927938867 28 582.4351352617357;
	setAttr -s 19 ".kit[5:18]"  1 9 9 9 9 9 9 9 
		9 9 1 1 9 9;
	setAttr -s 19 ".kot[5:18]"  1 9 9 9 9 9 9 9 
		9 9 1 1 9 9;
	setAttr -s 19 ".kix[5:18]"  0.033490587025880814 0.066666662693023682 
		0.033333346247673035 0.033333331346511841 0.066666662693023682 0.033333331346511841 
		0.033333331346511841 0.033333331346511841 0.033333331346511841 0.066666662693023682 
		0.066377051174640656 0.067630477249622345 0.13333332538604736 0.10000002384185791;
	setAttr -s 19 ".kiy[5:18]"  0.45696386694908142 1.0872989892959595 
		0.64899903535842896 0.76863306760787964 1.6009148359298706 0.74708598852157593 0.56980669498443604 
		0.35836610198020935 0.23706434667110443 0.34624597430229187 0.21978434920310974 0.10832425951957703 
		0.28484639525413513 0.23296560347080231;
	setAttr -s 19 ".kox[5:18]"  0.066823944449424744 0.033333346247673035 
		0.033333331346511841 0.066666662693023682 0.033333331346511841 0.033333331346511841 
		0.033333331346511841 0.033333331346511841 0.066666662693023682 0.066666662693023682 
		0.066377066075801849 0.13429729640483856 0.10000002384185791 0.10000002384185791;
	setAttr -s 19 ".koy[5:18]"  0.91178256273269653 0.54364973306655884 
		0.64899873733520508 1.5372661352157593 0.8004574179649353 0.74708598852157593 0.56980669498443604 
		0.35836610198020935 0.47412869334220886 0.34624597430229187 0.21978436410427094 0.21510504186153412 
		0.21363486349582672 0.23296560347080231;
createNode animCurveTL -n "animCurveTL469";
	setAttr ".tan" 9;
	setAttr -s 22 ".ktv[0:21]"  0 0 1 0 2 0.7118470430465631 3 1.4017768322185253 
		4 2.040262242639415 5 2.6100770519483789 6 3.0327752550789682 7 3.2220916491740716 
		8 2.8250188172484054 9 1.9147339500302358 10 1.1071411962989943 11 0.62267821937155488 
		12 0.53389226169740678 13 0.63943880686163135 14 0.86096100917791318 15 1.0520633708866443 
		17 1.0082184313344351 19 0.84855628140345918 21 0.44232505724281102 22 0.069380269736324787 
		25 0.15716938120963328 28 0.080489422962251977;
	setAttr -s 22 ".kit[15:21]"  3 9 9 9 9 9 9;
	setAttr -s 22 ".kot[15:21]"  3 9 9 9 9 9 9;
createNode animCurveTL -n "animCurveTL470";
	setAttr ".tan" 9;
	setAttr -s 22 ".ktv[0:21]"  0 -0.26728461461584108 1 -0.26728461461584108 
		2 -0.35756959100660013 3 -0.65248201826245222 4 -1.0323252505302882 5 -1.4552747431751383 
		6 -2.0202537460636942 7 -2.8308579354871672 8 -3.9075977644658506 9 -4.2530103600291129 
		10 -4.1471020035040844 11 -3.9295959149394575 12 -3.779465570960383 13 -3.7891397250091989 
		14 -4.0640589120287736 15 -4.4194422513467604 17 -5.1747626135811959 19 -5.5553118085343494 
		21 -5.8050326027193471 22 -5.8967899661809939 25 -6.0536638102497191 28 -6.1235372908225099;
createNode animCurveTL -n "animCurveTL471";
	setAttr ".tan" 1;
	setAttr -s 13 ".ktv[0:12]"  0 0.017033828181619803 1 0.017033828181619803 
		2 0.017473394352701652 4 0.02094174809927437 5 0.041099883612760062 9 0.27546593744332176 
		13 0.14011185110585944 15 -0.1203254390557684 17 -0.5898880711359078 19 -1.0971877828325451 
		21 -1.4138847362109315 25 -1.5450775848598601 28 -1.5566205782703046;
	setAttr -s 13 ".kit[0:12]"  9 3 1 1 1 1 1 1 
		9 9 9 1 3;
	setAttr -s 13 ".kot[0:12]"  9 3 1 1 1 1 1 1 
		9 9 9 1 3;
	setAttr -s 13 ".kix[2:12]"  0.033640038222074509 0.066106006503105164 
		0.027948202565312386 0.1331048458814621 0.12883609533309937 0.066197827458381653 
		0.066666662693023682 0.066666662693023682 0.066666662693023682 0.13238289952278137 
		0.10000002384185791;
	setAttr -s 13 ".kiy[2:12]"  0.00092312268679961562 0.0051524760201573372 
		0.044258479028940201 0.031976468861103058 -0.29025900363922119 -0.41693773865699768 
		-0.4884311854839325 -0.41199833154678345 -0.1492965966463089 -0.045383565127849579 
		0;
	setAttr -s 13 ".kox[2:12]"  0.067280054092407227 0.033052999526262283 
		0.11179283261299133 0.1331048458814621 0.032209001481533051 0.066197827458381653 
		0.066666662693023682 0.066666662693023682 0.13333332538604736 0.099287211894989014 
		0.10000002384185791;
	setAttr -s 13 ".koy[2:12]"  0.0018462451407685876 0.002576237078756094 
		0.17703396081924438 0.031976472586393356 -0.072564706206321716 -0.41693779826164246 
		-0.4884311854839325 -0.41199833154678345 -0.2985931932926178 -0.034037686884403229 
		0;
createNode animCurveTA -n "animCurveTA927";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA928";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA929";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL472";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.3877787807814457e-017;
createNode animCurveTL -n "animCurveTL473";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.1102230246251565e-016;
createNode animCurveTL -n "animCurveTL474";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -5.5511151231257827e-017;
createNode animCurveTU -n "animCurveTU769";
	setAttr ".tan" 2;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 2 0 4 0 6 0;
	setAttr -s 5 ".kit[3:4]"  3 3;
	setAttr -s 5 ".kot[3:4]"  3 3;
createNode animCurveTU -n "animCurveTU770";
	setAttr ".tan" 2;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 2 0 4 0 6 0;
	setAttr -s 5 ".kit[3:4]"  3 3;
	setAttr -s 5 ".kot[3:4]"  3 3;
createNode animCurveTU -n "animCurveTU771";
	setAttr ".tan" 2;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 2 0 4 0 6 0;
	setAttr -s 5 ".kit[3:4]"  3 3;
	setAttr -s 5 ".kot[3:4]"  3 3;
createNode animCurveTA -n "animCurveTA930";
	setAttr ".tan" 2;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 2 0 4 0 6 0;
	setAttr -s 5 ".kit[3:4]"  3 3;
	setAttr -s 5 ".kot[3:4]"  3 3;
createNode animCurveTA -n "animCurveTA931";
	setAttr ".tan" 2;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 2 0 4 0 6 0;
	setAttr -s 5 ".kit[3:4]"  3 3;
	setAttr -s 5 ".kot[3:4]"  3 3;
createNode animCurveTA -n "animCurveTA932";
	setAttr ".tan" 2;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 2 0 4 0 6 0;
	setAttr -s 5 ".kit[3:4]"  3 3;
	setAttr -s 5 ".kot[3:4]"  3 3;
createNode animCurveTL -n "animCurveTL475";
	setAttr ".tan" 3;
	setAttr -s 17 ".ktv[0:16]"  0 -0.77177341453224102 1 -0.77177341453224102 
		2 -0.76568437111374177 4 0.37905579156410152 6 1.6699329962859248 8 2.7172484642677812 
		9 2.21185786053235 10 1.6942891699599203 12 -0.059355334567839702 13 -0.74741724085824568 
		14 -0.55256785146627185 16 -0.39425272258529354 18 0.2633639666126163 21 0.49982406047115446 
		24 0.071077989850094614 28 -0.33078328689358177 30 -0.6549726215927496;
	setAttr -s 17 ".kit[0:16]"  2 2 2 3 3 3 3 3 
		3 3 3 3 3 3 3 3 3;
	setAttr -s 17 ".kot[0:16]"  2 2 2 3 3 3 3 3 
		3 3 3 3 3 3 3 3 3;
createNode animCurveTL -n "animCurveTL476";
	setAttr ".tan" 3;
	setAttr -s 18 ".ktv[0:17]"  0 0 1 0 2 -1.8693363294792438 4 -3.1723916210380665 
		6 -3.4707547485445267 8 -4.5058921296893875 9 -6.262581155926398 10 -7.0937355825515329 
		12 -7.4225439271504898 13 -6.7649272379525822 14 -6.2656256776356472 16 -6.2778037644726457 
		18 -7.5362213634024524 21 -8.4130214416496916 24 -8.8306825500840294 26 -8.5435406145001966 
		27 -8.5613926854067017 28 -8.3097807589102253;
	setAttr -s 18 ".kit[0:17]"  2 2 2 3 3 3 3 3 
		3 3 3 3 3 3 3 3 3 3;
	setAttr -s 18 ".kot[0:17]"  2 2 2 3 3 3 3 3 
		3 3 3 3 3 3 3 3 3 3;
createNode animCurveTL -n "animCurveTL477";
	setAttr ".tan" 3;
	setAttr -s 14 ".ktv[0:13]"  0 0 1 0 2 0 4 0 6 0 14 -0.33048421399736372 
		16 -0.30525652423864308 18 -0.22757421877928211 21 -1.8216577860056284 24 -2.6158619349000478 
		26 -2.8571932240786677 27 -3.0955815455963274 28 -3.575075438403188 30 -3.6158275545048828;
	setAttr -s 14 ".kit[0:13]"  2 2 2 3 3 3 3 3 
		3 3 3 3 3 3;
	setAttr -s 14 ".kot[0:13]"  2 2 2 3 3 3 3 3 
		3 3 3 3 3 3;
createNode animCurveTU -n "animCurveTU772";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU773";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU774";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA933";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA934";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA935";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL478";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL479";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL480";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU775";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU776";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 0 1 0 2 0 6 0;
	setAttr -s 4 ".kit[3]"  3;
	setAttr -s 4 ".kot[3]"  3;
createNode animCurveTL -n "animCurveTL481";
	setAttr ".tan" 3;
	setAttr -s 16 ".ktv[0:15]"  0 -0.75537025498543575 1 -0.75537025498543575 
		2 -0.48136330115297316 3 0.99040416065220405 4 2.0735586105523289 5 2.2365210873348924 
		6 2.9041448395325644 8 3.1659737065280282 9 1.430596332255766 10 0.40154799452940715 
		12 -1.5895692033198201 14 -0.34131530252749093 16 0.43199321162190335 18 1.1748565086788016 
		21 0.91622643560255379 24 -0.66021561399672146;
	setAttr -s 16 ".kit[0:15]"  2 2 2 2 3 2 3 3 
		3 3 3 3 3 3 3 3;
	setAttr -s 16 ".kot[0:15]"  2 2 2 2 3 2 3 3 
		3 3 3 3 3 3 3 3;
createNode animCurveTL -n "animCurveTL482";
	setAttr ".tan" 3;
	setAttr -s 16 ".ktv[0:15]"  0 -0.073475021782978711 1 -0.073475021782978711 
		2 -2.040236045958209 3 -1.9837788075783018 4 -2.1039589878058473 5 -2.3669072889673854 
		6 -2.8866130811295947 8 -5.5049017510842368 9 -6.6283302617973341 10 -6.4974158282996006 
		12 -5.9433128772161794 14 -5.1030248854632969 16 -6.1259841797711569 18 -6.7592446952950711 
		21 -8.0708493727160313 24 -7.9763560453906646;
	setAttr -s 16 ".kit[0:15]"  2 2 2 2 3 2 3 3 
		3 3 3 3 3 3 3 3;
	setAttr -s 16 ".kot[0:15]"  2 2 2 2 3 2 3 3 
		3 3 3 3 3 3 3 3;
createNode animCurveTL -n "animCurveTL483";
	setAttr ".tan" 3;
	setAttr -s 9 ".ktv[0:8]"  0 0.15459877332636279 1 0.15459877332636279 
		2 0.15459877332636279 6 0.15459877332636279 14 -0.040181838855899321 16 0.48493449956392082 
		18 -0.34746857623837674 21 -2.512526043101369 24 -3.2160830118704866;
	setAttr -s 9 ".kit[0:8]"  2 2 2 3 3 3 3 3 
		3;
	setAttr -s 9 ".kot[0:8]"  2 2 2 3 3 3 3 3 
		3;
createNode animCurveTU -n "animCurveTU777";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU778";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU779";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA936";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA937";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA938";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL484";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL485";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL486";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU780";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU781";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 0 1 0 2 0 6 0;
	setAttr -s 4 ".kit[3]"  3;
	setAttr -s 4 ".kot[3]"  3;
createNode animCurveTL -n "animCurveTL487";
	setAttr ".tan" 3;
	setAttr -s 13 ".ktv[0:12]"  0 -0.8594552290779115 1 -0.8594552290779115 
		2 0.89418927544984839 4 2.3738268261451463 5 3.0280173683499179 6 3.0801558626910501 
		8 2.0937308288941847 10 -0.061790541254519882 12 -0.46366740687546515 14 1.1133948385158188 
		16 1.1194838819343176 18 0.98552492672733627 21 -0.56312644696086211;
	setAttr -s 13 ".kit[0:12]"  2 2 2 3 2 3 3 3 
		3 3 3 3 3;
	setAttr -s 13 ".kot[0:12]"  2 2 2 3 2 3 3 3 
		3 3 3 3 3;
createNode animCurveTL -n "animCurveTL488";
	setAttr ".tan" 3;
	setAttr -s 14 ".ktv[0:13]"  0 0 1 0 2 -1.2056305968628351 4 -2.1311651964747105 
		5 -3.0206234859162553 6 -3.3611519670115442 8 -5.1208855149578039 10 -4.9747484729138236 
		12 -4.0553029167204508 14 -4.2866865666234188 16 -6.0951324619176734 18 -6.7162148906045891 
		21 -7.4127461314064993 24 -7.9000855688709937;
	setAttr -s 14 ".kit[0:13]"  2 2 2 3 2 3 3 3 
		3 3 3 3 3 3;
	setAttr -s 14 ".kot[0:13]"  2 2 2 3 2 3 3 3 
		3 3 3 3 3 3;
createNode animCurveTL -n "animCurveTL489";
	setAttr ".tan" 3;
	setAttr -s 8 ".ktv[0:7]"  0 -0.14721316863839706 1 -0.14721316863839706 
		2 -0.14721316863839706 6 -0.14721316863839706 14 0.22933485945159982 16 -0.53354678738995265 
		18 -1.5346873743364506 21 -2.6263719382734476;
	setAttr -s 8 ".kit[0:7]"  2 2 2 3 3 3 3 3;
	setAttr -s 8 ".kot[0:7]"  2 2 2 3 3 3 3 3;
createNode animCurveTU -n "animCurveTU782";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU783";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU784";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA939";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA940";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA941";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL490";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL491";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL492";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU785";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU786";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 10 1 10 2 10 4 10 7 10 10 10 13 10 16 
		10 18 10 20 10 23 10;
createNode animCurveTL -n "animCurveTL493";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 -0.0024830586491624029 1 -0.0024830586491624029 
		2 -0.0024830586491624029 4 -0.0024830586491624029 7 -0.0024830586491624029 10 -0.0024830586491624029 
		13 -0.0024830586491624029 16 -0.0024830586491624029 18 -0.0024830586491624029 20 
		-0.0024830586491624029 23 -0.0024830586491624029;
createNode animCurveTL -n "animCurveTL494";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.0061262151441996713 1 0.0061262151441996713 
		2 0.0061262151441996713 4 0.0061262151441996713 7 0.0061262151441996713 10 0.0061262151441996713 
		13 0.0061262151441996713 16 0.0061262151441996713 18 0.0061262151441996713 20 0.0061262151441996713 
		23 0.0061262151441996713;
createNode animCurveTL -n "animCurveTL495";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 -0.027195247513723396 1 -0.027195247513723396 
		2 -0.027195247513723396 4 -0.027195247513723396 7 -0.027195247513723396 10 -0.027195247513723396 
		13 -0.027195247513723396 16 -0.027195247513723396 18 -0.027195247513723396 20 -0.027195247513723396 
		23 -0.027195247513723396;
createNode animCurveTL -n "animCurveTL496";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL497";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL498";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA942";
	setAttr ".tan" 2;
	setAttr -s 4 ".ktv[0:3]"  0 0 1 -27.228748358672426 2 -27.228748358672426 
		3 0;
	setAttr -s 4 ".kit[3]"  3;
	setAttr -s 4 ".kot[3]"  3;
createNode animCurveTA -n "animCurveTA943";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA944";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -7.951386703658785e-016;
createNode animCurveTA -n "animCurveTA945";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA946";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTA -n "animCurveTA947";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTA -n "animCurveTA948";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTA -n "animCurveTA949";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA950";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -3.9756933518293925e-016;
createNode animCurveTA -n "animCurveTA951";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU787";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1 1 1 2 1 4 1 7 1 10 1 13 1 16 1 19 1 
		22 1 25 1;
createNode animCurveTU -n "animCurveTU788";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1 1 1 2 1 4 1 7 1 10 1 13 1 16 1 19 1 
		22 1 25 1;
createNode animCurveTU -n "animCurveTU789";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 19 0 
		22 0 25 0;
createNode animCurveTU -n "animCurveTU790";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 19 0 
		22 0 25 0;
createNode animCurveTU -n "animCurveTU791";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 10 1 10 2 10 4 10 7 10 10 10 13 10 16 
		10 19 10 22 10 25 10;
createNode animCurveTU -n "animCurveTU792";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 25 1 25 2 25 4 25 7 25 10 25 13 25 16 
		25 19 25 22 25 25 25;
createNode animCurveTU -n "animCurveTU793";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 19 0 
		22 0 25 0;
createNode animCurveTU -n "animCurveTU794";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 19 0 
		22 0 25 0;
createNode animCurveTA -n "animCurveTA952";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 10.555261301844832 1 10.555261301844832 
		2 10.555261301844832 3 -0.24480676416351504 4 0.60194579179417862 5 -1.7768995766729327 
		6 5.4441581905310086 7 -8.9256085663283464 9 -2.5203692715235246 10 7.9894986696616792 
		13 16.58163665740414 16 18.148392249501576 19 7.1434392934075515 22 -30.809910625380144 
		25 -30.809910625380144 28 -41.480642365522385;
	setAttr -s 16 ".kit[3:15]"  3 2 3 3 2 3 2 2 
		2 2 2 2 3;
	setAttr -s 16 ".kot[3:15]"  3 2 3 3 2 3 2 2 
		2 2 2 2 3;
createNode animCurveTA -n "animCurveTA953";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 0 1 0 2 0 3 -7.6640218793430863 4 -10.538277733413841 
		5 3.5124378194731647 6 -1.4499624864680487 7 5.6574331543242664 9 6.4359384813771712 
		10 6.9204457982324863 13 6.8461357844522697 16 -41.584956020067018 19 -46.63274210258691 
		22 -70.92886841397042 25 -70.92886841397042 28 -66.744975234198165;
	setAttr -s 16 ".kit[3:15]"  3 2 3 3 2 3 2 2 
		2 2 2 2 3;
	setAttr -s 16 ".kot[3:15]"  3 2 3 3 2 3 2 2 
		2 2 2 2 3;
createNode animCurveTA -n "animCurveTA954";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 0 1 0 2 0 3 91.710575154017022 4 86.767749580336982 
		5 98.629780635499642 6 134.56790967183048 7 -147.44216851519155 9 -117.66788939511322 
		10 -41.129314099532195 13 121.68979688489438 16 158.69756285027887 19 216.52596735923731 
		22 286.36052107770934 25 286.36052107770934 28 288.83977965637416;
	setAttr -s 16 ".kit[3:15]"  3 2 3 3 2 3 2 2 
		2 2 2 2 3;
	setAttr -s 16 ".kot[3:15]"  3 2 3 3 2 3 2 2 
		2 2 2 2 3;
createNode animCurveTL -n "animCurveTL499";
	setAttr ".tan" 2;
	setAttr -s 17 ".ktv[0:16]"  0 0 1 0 2 0 3 0.53675960822541913 4 1.079660833846088 
		5 1.8288657237387829 6 2.3805683479546276 7 2.8235980449185014 8 2.7691636640172392 
		9 2.3700873989727671 10 1.4865017677839605 13 0.23850606028860763 16 0.50360582235806384 
		19 0.35899069437616538 22 -0.028403612067599227 25 0.048638470956267346 28 0.025401615095142896;
	setAttr -s 17 ".kit[5:16]"  3 3 2 3 3 2 2 2 
		2 2 2 3;
	setAttr -s 17 ".kot[5:16]"  3 3 2 3 3 2 2 2 
		2 2 2 3;
createNode animCurveTL -n "animCurveTL500";
	setAttr ".tan" 2;
	setAttr -s 16 ".ktv[0:15]"  0 0.38582961184709008 1 0.38582961184709008 
		2 0.38582961184709008 3 0.28830955379814527 4 0.18799122091181369 5 0.086263608285950699 
		6 -0.22218767775759174 7 -1.058396875705909 8 -1.825601664694112 9 -2.5677824596460375 
		10 -2.7562420149121665 13 -2.9902010832270136 16 -3.7456235711733554 19 -4.0706273863847375 
		22 -4.3041852496967099 25 -4.3702317383502214;
	setAttr -s 16 ".kit[5:15]"  3 3 2 3 3 2 2 2 
		2 2 2;
	setAttr -s 16 ".kot[5:15]"  3 3 2 3 3 2 2 2 
		2 2 2;
createNode animCurveTL -n "animCurveTL501";
	setAttr ".tan" 2;
	setAttr -s 14 ".ktv[0:13]"  0 -0.012835510537475885 1 -0.012835510537475885 
		2 -0.012835510537475885 4 -0.012835510537475885 5 0.11849382259529859 7 0.2227368392628688 
		8 0.25938382443634794 9 0.24471524720962082 10 0.15674460003939836 13 -0.20382316419002733 
		16 -0.57828216918128783 19 -0.75858766661684907 22 -0.82073921326289645 25 -0.82073921326289645;
	setAttr -s 14 ".kit[4:13]"  3 2 3 3 2 2 2 2 
		2 2;
	setAttr -s 14 ".kot[4:13]"  3 2 3 3 2 2 2 2 
		2 2;
createNode animCurveTA -n "animCurveTA955";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA956";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA957";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL502";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.3877787807814457e-017;
createNode animCurveTL -n "animCurveTL503";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL504";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA958";
	setAttr ".tan" 3;
	setAttr -s 14 ".ktv[0:13]"  0 -4.1272878036759 1 -15.647766682221036 
		2 -45.369955302971618 4 -108.44480281937642 5 -110.65906693260943 7 -127.56119775945018 
		9 -58.067388101381241 11 -28.125513196313527 13 -43.045640023526076 16 -56.769633677672552 
		18 -48.094942644516777 20 -29.873097202595893 21 -21.298100380760467 22 -19.638421983660727;
	setAttr -s 14 ".kit[1:13]"  9 9 1 3 3 1 3 1 
		3 9 9 1 3;
	setAttr -s 14 ".kot[1:13]"  9 9 1 3 3 1 3 1 
		3 9 9 1 3;
	setAttr -s 14 ".kix[3:13]"  0.066535428166389465 0.033333331346511841 
		0.066666662693023682 0.055629454553127289 0.066666662693023682 0.063652180135250092 
		0.10000002384185791 0.066666662693023682 0.066666662693023682 0.033485107123851776 
		0.033333361148834229;
	setAttr -s 14 ".kiy[3:13]"  -0.22221153974533081 0 0 1.0031664371490479 
		0 -0.2980230450630188 0 0.23471656441688538 0.31179550290107727 0.079956695437431335 
		0;
	setAttr -s 14 ".kox[3:13]"  0.033202111721038818 0.066666662693023682 
		0.066666677594184875 0.055629439651966095 0.066666662693023682 0.096985206007957458 
		0.066666662693023682 0.066666662693023682 0.033333301544189453 0.033485163003206253 
		0.033333361148834229;
	setAttr -s 14 ".koy[3:13]"  -0.11088666319847107 0 0 1.0031661987304687 
		0 -0.45408999919891357 0 0.23471656441688538 0.15589761734008789 0.079956822097301483 
		0;
createNode animCurveTA -n "animCurveTA959";
	setAttr ".tan" 3;
	setAttr -s 14 ".ktv[0:13]"  0 -3.9401506072152763 1 -3.9404018153544236 
		2 10.189118775401939 4 4.2215604722316957 5 2.2384901392358807 7 1.7738388376767222 
		9 8.7714467804538003 11 8.2306013715283015 13 13.666095042773469 16 22.50598318610654 
		18 7.2067354517021958 20 -3.259904544334888 21 -4.6140558967811272 22 -3.565350852357656;
	setAttr -s 14 ".kit[2:13]"  9 9 1 1 3 3 1 3 
		1 1 3 1;
	setAttr -s 14 ".kot[2:13]"  9 9 1 1 3 3 1 3 
		1 1 3 1;
	setAttr -s 14 ".kix[4:13]"  0.03382505476474762 0.066595882177352905 
		0.066666677594184875 0.066666662693023682 0.064430892467498779 0.10000002384185791 
		0.066240124404430389 0.06714465469121933 0.033333301544189453 0.063775382936000824;
	setAttr -s 14 ".kiy[4:13]"  -0.021483089774847031 0.016921158879995346 
		0 0 0.13799341022968292 0 -0.2820931077003479 -0.11400125175714493 0 0.054405879229307175;
	setAttr -s 14 ".kox[4:13]"  0.067158475518226624 0.066595897078514099 
		0.066666662693023682 0.066666662693023682 0.097764015197753906 0.066666662693023682 
		0.066240131855010986 0.033811219036579132 0.033333361148834229 0.063775382936000824;
	setAttr -s 14 ".koy[4:13]"  -0.042653933167457581 0.016921158879995346 
		0 0 0.20938387513160706 0 -0.28209316730499268 -0.057406224310398102 0 0.054405879229307175;
createNode animCurveTA -n "animCurveTA960";
	setAttr ".tan" 9;
	setAttr -s 14 ".ktv[0:13]"  0 1.5206250006361597 1 1.5276263060288124 
		2 -1.5353646812653845 4 3.2084623625588908 5 1.7928228286750114 7 2.284718442491787 
		9 4.8899266564619639 11 7.3647231116120375 13 5.7911601278234697 16 6.1707554889778979 
		18 9.2673825602451672 20 13.059943802662016 21 14.415399175562971 22 14.161309133701577;
	setAttr -s 14 ".kit[4:13]"  3 9 9 3 1 1 1 9 
		3 3;
	setAttr -s 14 ".kot[4:13]"  3 9 9 3 1 1 1 9 
		3 3;
	setAttr -s 14 ".kix[8:13]"  0.065991401672363281 0.098537527024745941 
		0.066698484122753143 0.066666662693023682 0.033333301544189453 0.033333361148834229;
	setAttr -s 14 ".kiy[8:13]"  -0.019045541062951088 0.037886414676904678 
		0.071074545383453369 0.059899911284446716 0 0;
	setAttr -s 14 ".kox[8:13]"  0.099324703216552734 0.065204314887523651 
		0.066698476672172546 0.033333301544189453 0.033333361148834229 0.033333361148834229;
	setAttr -s 14 ".koy[8:13]"  -0.028665753081440926 0.025070220232009888 
		0.071074537932872772 0.029949929565191269 0 0;
createNode animCurveTA -n "animCurveTA961";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 0 2 0;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  2;
createNode animCurveTA -n "animCurveTA962";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 0 2 0;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  2;
createNode animCurveTA -n "animCurveTA963";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 0 2 0;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  2;
createNode animCurveTL -n "animCurveTL505";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 0 2 0;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  2;
createNode animCurveTL -n "animCurveTL506";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 0 2 0;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  2;
createNode animCurveTL -n "animCurveTL507";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 0 2 0;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  2;
createNode animCurveTA -n "animCurveTA964";
	setAttr ".tan" 2;
	setAttr -s 9 ".ktv[0:8]"  0 7.8212153369064472 13 7.8212153369064472 
		14 -12.792657259633218 15 0.96231417276819409 16 4.2383897600272462 17 3.4729767179380673 
		18 3.4524426262928549 20 3.138160947540694 23 10.810175949027215;
createNode animCurveTA -n "animCurveTA965";
	setAttr ".tan" 2;
	setAttr -s 9 ".ktv[0:8]"  0 -0.038068429571548837 13 -0.038068429571548837 
		14 -0.02582542230544202 15 7.6399481165957042 16 10.619306174716471 17 18.442769187980591 
		18 19.524988050288439 20 21.834546196512541 23 25.349173175920406;
createNode animCurveTA -n "animCurveTA966";
	setAttr ".tan" 2;
	setAttr -s 9 ".ktv[0:8]"  0 0.027851559758348458 13 0.027851559758348458 
		14 0.039471030707645995 15 -1.2187005893980558 16 -4.7732321385514185 17 -6.0942195099134446 
		18 -7.2003510610615864 20 2.6631598993252497 23 26.163896992542618;
createNode animCurveTL -n "animCurveTL508";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 0 13 0;
createNode animCurveTL -n "animCurveTL509";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 0 13 0;
createNode animCurveTL -n "animCurveTL510";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 0 13 0;
createNode animCurveTU -n "animCurveTU795";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1 1 1 2 1 4 1 7 1 10 1 13 1 16 1 18 1 
		20 1 23 1;
createNode animCurveTU -n "animCurveTU796";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.99999999999999978 1 0.99999999999999978 
		2 0.99999999999999978 4 0.99999999999999978 7 0.99999999999999978 10 0.99999999999999978 
		13 0.99999999999999978 16 0.99999999999999978 18 0.99999999999999978 20 0.99999999999999978 
		23 0.99999999999999978;
createNode animCurveTU -n "animCurveTU797";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.99999999999999978 1 0.99999999999999978 
		2 0.99999999999999978 4 0.99999999999999978 7 0.99999999999999978 10 0.99999999999999978 
		13 0.99999999999999978 16 0.99999999999999978 18 0.99999999999999978 20 0.99999999999999978 
		23 0.99999999999999978;
createNode animCurveTA -n "animCurveTA967";
	setAttr ".tan" 9;
	setAttr -s 12 ".ktv[0:11]"  0 4.922870201962569 1 6.3005033094369924 
		2 -7.5727753248136196 3 -8.9365630983065891 4 -7.4086505459878262 7 0.42918909435227071 
		10 11.385222474854896 13 16.144897864339836 16 18.468557467705597 18 19.637058121154311 
		20 21.250240793587782 23 22.185041316346744;
	setAttr -s 12 ".kit[0:11]"  3 3 1 1 9 9 9 9 
		9 9 9 9;
	setAttr -s 12 ".kot[0:11]"  3 3 1 1 9 9 9 9 
		9 9 9 9;
	setAttr -s 12 ".kix[2:11]"  0.03757144883275032 0.033332772552967072 
		0.033333338797092438 0.099999994039535522 0.10000000894069672 0.099999994039535522 
		0.10000002384185791 0.066666662693023682 0.066666662693023682 0.099999964237213135;
	setAttr -s 12 ".kiy[2:11]"  -0.065364427864551544 0.0019182410323992372 
		0.040865812450647354 0.16400747001171112 0.13714544475078583 0.061813749372959137 
		0.036569822579622269 0.024274766445159912 0.017788281664252281 0.016315346583724022;
	setAttr -s 12 ".kox[2:11]"  0.037571437656879425 0.033332780003547668 
		0.099999994039535522 0.10000000894069672 0.099999994039535522 0.10000002384185791 
		0.066666662693023682 0.066666662693023682 0.099999964237213135 0.099999964237213135;
	setAttr -s 12 ".koy[2:11]"  -0.065364405512809753 0.0019182409159839153 
		0.12259741127490997 0.16400749981403351 0.13714541494846344 0.061813767999410629 
		0.024379873648285866 0.024274766445159912 0.02668241411447525 0.016315346583724022;
createNode animCurveTA -n "animCurveTA968";
	setAttr ".tan" 9;
	setAttr -s 13 ".ktv[0:12]"  0 -0.87714675457798974 1 -0.37950075611674094 
		2 -0.26561697910434062 3 -1.8723847701919816 4 -1.1162060610691524 7 -1.1849491940569599 
		9 -0.39303238133487733 10 0.41989534792182798 13 4.5795886566977222 16 11.170680400321876 
		18 11.170680400321876 20 -11.238891439170171 23 -11.238891439170171;
	setAttr -s 13 ".kit[10:12]"  1 3 3;
	setAttr -s 13 ".kot[10:12]"  1 3 3;
	setAttr -s 13 ".kix[10:12]"  0.07000868022441864 0.066666662693023682 
		0.099999964237213135;
	setAttr -s 13 ".kiy[10:12]"  -0.015789782628417015 0 0;
	setAttr -s 13 ".kox[10:12]"  0.07000868022441864 0.099999964237213135 
		0.099999964237213135;
	setAttr -s 13 ".koy[10:12]"  -0.015789788216352463 0 0;
createNode animCurveTA -n "animCurveTA969";
	setAttr ".tan" 9;
	setAttr -s 13 ".ktv[0:12]"  0 2.2332421979438823 1 2.4956349859380444 
		2 2.4021811137429392 3 1.9225556493425997 4 1.3257455410032553 7 2.1084875834773653 
		9 1.2006999374012604 10 0.85670817325158499 13 0.81540879392774801 16 2.503858981929751 
		18 11.657707722765167 20 7.325838744872744 23 7.325838744872744;
createNode animCurveTA -n "animCurveTA970";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA971";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA972";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU798";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1 1 1 2 1 4 1 7 1 10 1 13 1 16 1 18 1 
		20 1 23 1;
createNode animCurveTU -n "animCurveTU799";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.99999999999999978 1 0.99999999999999978 
		2 0.99999999999999978 4 0.99999999999999978 7 0.99999999999999978 10 0.99999999999999978 
		13 0.99999999999999978 16 0.99999999999999978 18 0.99999999999999978 20 0.99999999999999978 
		23 0.99999999999999978;
createNode animCurveTU -n "animCurveTU800";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.99999999999999978 1 0.99999999999999978 
		2 0.99999999999999978 4 0.99999999999999978 7 0.99999999999999978 10 0.99999999999999978 
		13 0.99999999999999978 16 0.99999999999999978 18 0.99999999999999978 20 0.99999999999999978 
		23 0.99999999999999978;
createNode animCurveTA -n "animCurveTA973";
	setAttr ".tan" 9;
	setAttr -s 15 ".ktv[0:14]"  0 7.1500018217381927 1 19.533942495748363 
		2 19.426884175129079 3 0.2110217877328249 4 -17.350003006071788 6 -35.510933904974131 
		7 -34.289661632274665 9 -13.287060698437688 10 11.153090012333269 12 35.084408202260299 
		13 33.909074886769154 16 19.511498243108317 18 15.041080800961549 20 14.269812365311582 
		23 14.269812365311582;
	setAttr -s 15 ".kit[5:14]"  1 1 1 1 1 9 9 1 
		3 3;
	setAttr -s 15 ".kot[5:14]"  1 1 1 1 1 9 9 1 
		3 3;
	setAttr -s 15 ".kix[5:14]"  0.067492969334125519 0.03270392119884491 
		0.065890297293663025 0.03059110976755619 0.06662171334028244 0.033333331346511841 
		0.10000002384185791 0.065940298140048981 0.066666662693023682 0.099999964237213135;
	setAttr -s 15 ".kiy[5:14]"  -0.096661128103733063 0.086479172110557556 
		0.64836907386779785 0.44688394665718079 0.05271463468670845 -0.067949622869491577 
		-0.19758519530296326 -0.032018721103668213 0 0;
	setAttr -s 15 ".kox[5:14]"  0.03415951132774353 0.066037170588970184 
		0.032557077705860138 0.063923977315425873 0.033288389444351196 0.10000002384185791 
		0.066666662693023682 0.065940283238887787 0.099999964237213135 0.099999964237213135;
	setAttr -s 15 ".koy[5:14]"  -0.048922099173069 0.17462247610092163 
		0.32036581635475159 0.93382024765014648 0.026339538395404816 -0.20384892821311951 
		-0.13172341883182526 -0.032018732279539108 0 0;
createNode animCurveTA -n "animCurveTA974";
	setAttr ".tan" 2;
	setAttr -s 15 ".ktv[0:14]"  0 -0.91877148719301893 1 -0.55991770026869681 
		2 -0.56272631929702144 3 -1.6266648914766595 4 -2.274556295247355 6 -3.8915826690690616 
		7 -3.2696981830356169 9 -1.2930659340220263 10 -0.6208134386677292 12 -3.1269230918726203 
		13 3.6978346937750715 16 -0.68245153057261776 18 -0.68245153057261776 20 12.781107732613288 
		23 12.781107732613288;
createNode animCurveTA -n "animCurveTA975";
	setAttr ".tan" 2;
	setAttr -s 15 ".ktv[0:14]"  0 2.1046441474014963 1 2.4088670010560045 
		2 2.4059148133625441 3 2.0156631123550506 4 1.388392675605455 6 2.3553597781497237 
		7 1.7812028172695102 9 2.3486613698540335 10 1.4733736200450767 12 0.88230757663476767 
		13 -1.6138781118054766 16 2.2897160727922641 18 2.2897160727922641 20 14.185326819412207 
		23 29.939141510008778;
createNode animCurveTA -n "animCurveTA976";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.5902773407317584e-015;
createNode animCurveTA -n "animCurveTA977";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 2.8249000307521015e-030;
createNode animCurveTA -n "animCurveTA978";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU801";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1 1 1 2 1 4 1 7 1 10 1 13 1 16 1 18 1 
		20 1 23 1;
createNode animCurveTU -n "animCurveTU802";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.99999999999999978 1 0.99999999999999978 
		2 0.99999999999999978 4 0.99999999999999978 7 0.99999999999999978 10 0.99999999999999978 
		13 0.99999999999999978 16 0.99999999999999978 18 0.99999999999999978 20 0.99999999999999978 
		23 0.99999999999999978;
createNode animCurveTU -n "animCurveTU803";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.99999999999999978 1 0.99999999999999978 
		2 0.99999999999999978 4 0.99999999999999978 7 0.99999999999999978 10 0.99999999999999978 
		13 0.99999999999999978 16 0.99999999999999978 18 0.99999999999999978 20 0.99999999999999978 
		23 0.99999999999999978;
createNode animCurveTA -n "animCurveTA979";
	setAttr ".tan" 9;
	setAttr -s 12 ".ktv[0:11]"  0 12.247781642514175 1 26.11502842664267 
		2 14.011197802643675 3 -20.69949307108492 4 -37.766772346463654 7 -25.172590563212317 
		10 32.476101050511431 13 4.353107081462567 16 -2.3304756356645697 18 -3.2503725371683632 
		20 -3.3116045997624801 23 -3.0222114720429705;
	setAttr -s 12 ".kit[1:11]"  3 9 9 9 9 3 1 1 
		1 9 3;
	setAttr -s 12 ".kot[1:11]"  3 9 9 9 9 3 1 1 
		1 9 3;
	setAttr -s 12 ".kix[7:11]"  0.10062020272016525 0.10167246311903 0.067791886627674103 
		0.066666662693023682 0.099999964237213135;
	setAttr -s 12 ".kiy[7:11]"  -0.25585970282554626 -0.041096474975347519 
		-0.0058156442828476429 0.0015928649809211493 0;
	setAttr -s 12 ".kox[7:11]"  0.10062022507190704 0.068338930606842041 
		0.067791871726512909 0.099999964237213135 0.099999964237213135;
	setAttr -s 12 ".koy[7:11]"  -0.25585982203483582 -0.027622900903224945 
		-0.0058156442828476429 0.0023892968893051147 0;
createNode animCurveTA -n "animCurveTA980";
	setAttr ".tan" 2;
	setAttr -s 12 ".ktv[0:11]"  0 -1.1610633997754873 1 -2.8103355108290571 
		2 -1.1613309459102361 3 -1.166444094216414 4 -1.1650101132082826 7 -1.6090081392959357 
		10 -0.8650284403207944 13 -3.2065807274179674 16 -2.03040987381564 18 -2.03040987381564 
		20 -2.03040987381564 23 -2.03040987381564;
createNode animCurveTA -n "animCurveTA981";
	setAttr ".tan" 2;
	setAttr -s 12 ".ktv[0:11]"  0 1.839599558714774 1 1.3388189425810415 
		2 1.8399458669671123 3 1.8536781899135901 4 1.8761923017881779 7 1.8976779060008109 
		10 1.6348591733122511 13 1.8507896284019181 16 1.8484109154675716 18 1.8484109154675716 
		20 1.8484109154675716 23 8.0097838049734591;
createNode animCurveTA -n "animCurveTA982";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA983";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA984";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU804";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTA -n "animCurveTA985";
	setAttr ".tan" 9;
	setAttr -s 15 ".ktv[0:14]"  0 -0.031511657810396665 1 -1.7131978422250058 
		2 -2.6562451006505037 3 -2.0189268755930034 4 0.9617801607488744 7 1.4287830774982322 
		10 -0.66682613151982906 12 0.99212519415140654 13 0.95383094232890386 15 -2.2468816971896706 
		16 -5.2513418981080351 18 -9.0394578547184619 20 -11.315881702283344 23 -12.472308863933751 
		26 -10.87375421579781;
	setAttr -s 15 ".kit[7:14]"  1 1 1 9 9 9 9 9;
	setAttr -s 15 ".kot[7:14]"  1 1 1 9 9 9 9 9;
	setAttr -s 15 ".kix[7:14]"  0.066683143377304077 0.034006677567958832 
		0.063866063952445984 0.033333361148834229 0.066666662693023682 0.066666662693023682 
		0.099999964237213135 0.10000002384185791;
	setAttr -s 15 ".kiy[7:14]"  0.018361039459705353 -0.012996344827115536 
		-0.091014139354228973 -0.039517629891633987 -0.052923094481229782 -0.023965826258063316 
		0.0038582889828830957 0.02790004201233387;
	setAttr -s 15 ".kox[7:14]"  0.033349804580211639 0.06734011322259903 
		0.030533285811543465 0.066666662693023682 0.066666662693023682 0.099999964237213135 
		0.10000002384185791 0.10000002384185791;
	setAttr -s 15 ".koy[7:14]"  0.0091827865689992905 -0.025735393166542053 
		-0.04351232573390007 -0.079035185277462006 -0.052923094481229782 -0.035948727279901505 
		0.0038582913111895323 0.02790004201233387;
createNode animCurveTA -n "animCurveTA986";
	setAttr ".tan" 9;
	setAttr -s 15 ".ktv[0:14]"  0 -0.014814737488693401 1 -5.2969797014915585 
		2 -5.3949363237419377 3 -1.2867164063265899 4 3.3708788973101762 7 6.072046666148446 
		10 6.338363649491785 12 3.1086597826360185 13 -11.122935785165037 15 -24.551955256682845 
		16 -32.387808528889842 18 -51.077696749435454 20 -65.137451092698967 23 -77.767486478293051 
		26 -77.51026791242613;
	setAttr -s 15 ".kit[0:14]"  3 9 9 9 9 1 3 1 
		9 1 9 9 9 1 3;
	setAttr -s 15 ".kot[0:14]"  3 9 9 9 9 1 3 1 
		9 1 9 9 9 1 3;
	setAttr -s 15 ".kix[5:14]"  0.10158107429742813 0.10000000894069672 
		0.067327603697776794 0.033333331346511841 0.067222185432910919 0.033333361148834229 
		0.066666662693023682 0.066666662693023682 0.099662177264690399 0.10000002384185791;
	setAttr -s 15 ".kiy[5:14]"  0.011466155759990215 0 -0.14842656254768372 
		-0.16092292964458466 -0.1973244696855545 -0.15432059764862061 -0.28579455614089966 
		-0.1863299161195755 -0.042213372886180878 0;
	setAttr -s 15 ".kox[5:14]"  0.10158111155033112 0.066666662693023682 
		0.033994171768426895 0.066666662693023682 0.033888794481754303 0.066666662693023682 
		0.066666662693023682 0.099999964237213135 0.099662214517593384 0.10000002384185791;
	setAttr -s 15 ".koy[5:14]"  0.011466155759990215 0 -0.074941597878932953 
		-0.32184585928916931 -0.099477410316467285 -0.30864092707633972 -0.28579455614089966 
		-0.27949479222297668 -0.042213387787342072 0;
createNode animCurveTA -n "animCurveTA987";
	setAttr ".tan" 1;
	setAttr -s 13 ".ktv[0:12]"  0 -13.23257395238204 1 -19.687958249370311 
		2 62.491648490891258 4 165.28681732640445 7 244.31723970345459 10 304.21271047786621 
		12 377.6339434741555 14 460.71338374287512 16 501.87990469794767 18 512.30830306838948 
		20 503.23144843126789 23 499.32819817155899 26 499.21124733992133;
	setAttr -s 13 ".kit[0:12]"  3 3 1 1 1 9 9 1 
		9 3 1 1 3;
	setAttr -s 13 ".kot[0:12]"  3 3 1 1 1 9 9 1 
		9 3 1 1 3;
	setAttr -s 13 ".kix[2:12]"  0.032548397779464722 0.06705029308795929 
		0.10057151317596436 0.10000000894069672 0.066666662693023682 0.066835574805736542 
		0.066666692495346069 0.066666662693023682 0.066500760614871979 0.099924392998218536 
		0.10000002384185791;
	setAttr -s 13 ".kiy[2:12]"  1.3063032627105713 1.1606190204620361 1.0504058599472046 
		1.3960893154144287 1.3657259941101074 1.0045369863510132 0.45025071501731873 0 -0.095391340553760529 
		-0.0072357542812824249 0;
	setAttr -s 13 ".kox[2:12]"  0.065881602466106415 0.10038366913795471 
		0.10057152807712555 0.066666662693023682 0.066666662693023682 0.066835604608058929 
		0.066666662693023682 0.066666662693023682 0.099834032356739044 0.099924452602863312 
		0.10000002384185791;
	setAttr -s 13 ".koy[2:12]"  2.6441044807434082 1.7376084327697754 1.0504059791564941 
		0.93072611093521118 1.3657259941101074 1.0045371055603027 0.45025050640106201 0 -0.143205925822258 
		-0.0072357584722340107 0;
createNode animCurveTL -n "animCurveTL511";
	setAttr ".tan" 9;
	setAttr -s 11 ".ktv[0:10]"  0 -0.16387457122081528 1 0.09764141585080055 
		2 0.78861616944478774 4 1.0792277305321158 7 1.1581100226312357 10 0.99030596592813747 
		12 0.68165970280785437 16 -0.14226303426782272 18 -0.32257147560509669 20 -0.40734095334884013 
		23 -0.45283200389272116;
	setAttr -s 11 ".kit[0:10]"  3 9 1 9 9 9 9 1 
		1 9 3;
	setAttr -s 11 ".kot[0:10]"  3 9 1 9 9 9 9 1 
		1 9 3;
	setAttr -s 11 ".kix[2:10]"  0.033527810126543045 0.066666670143604279 
		0.099999994039535522 0.10000000894069672 0.066666662693023682 0.14299030601978302 
		0.067063771188259125 0.066666662693023682 0.099999964237213135;
	setAttr -s 11 ".kiy[2:10]"  0.28250232338905334 0.14779755473136902 
		-0.044460877776145935 -0.28587019443511963 -0.37752294540405273 -0.55108338594436646 
		-0.11189070343971252 -0.052104219794273376 0;
	setAttr -s 11 ".kox[2:10]"  0.06705562025308609 0.099999994039535522 
		0.10000000894069672 0.066666662693023682 0.13333335518836975 0.071495130658149719 
		0.067063771188259125 0.099999964237213135 0.099999964237213135;
	setAttr -s 11 ".koy[2:10]"  0.56500464677810669 0.22169631719589233 
		-0.044460885226726532 -0.19058011472225189 -0.75504606962203979 -0.27554160356521606 
		-0.11189068108797073 -0.078156307339668274 0;
createNode animCurveTL -n "animCurveTL512";
	setAttr ".tan" 1;
	setAttr -s 13 ".ktv[0:12]"  0 0.16584656609996762 1 -0.23196148677958733 
		2 -1.0131274786954569 4 -1.9077185594191333 7 -2.4831372037183335 10 -2.8154099175358445 
		12 -3.642360163502683 13 -4.4303076377720929 16 -5.4852141017180731 18 -5.7033886225033248 
		20 -5.7901069366397717 23 -5.8694316147124477 26 -5.9094185106229915;
	setAttr -s 13 ".kit[0:12]"  3 1 9 9 9 1 1 1 
		1 1 1 9 3;
	setAttr -s 13 ".kot[0:12]"  3 1 9 9 9 1 1 1 
		1 1 1 9 3;
	setAttr -s 13 ".kix[1:12]"  0.032922480255365372 0.033333335071802139 
		0.066666670143604279 0.099999994039535522 0.10115144401788712 0.065857231616973877 
		0.033018365502357483 0.1011321097612381 0.067044280469417572 0.066781885921955109 
		0.099999964237213135 0.10000002384185791;
	setAttr -s 13 ".kiy[1:12]"  -0.72983813285827637 -0.55858564376831055 
		-0.58800393342971802 -0.45384564995765686 -0.48996356129646301 -1.3294817209243774 
		-0.54689067602157593 -0.53476625680923462 -0.13227856159210205 -0.061772920191287994 
		-0.059655770659446716 0;
	setAttr -s 13 ".kox[1:12]"  0.032922480255365372 0.066666670143604279 
		0.099999994039535522 0.10000000894069672 0.067434296011924744 0.032928623259067535 
		0.099055126309394836 0.067421391606330872 0.067044280469417572 0.10017278790473938 
		0.10000002384185791 0.10000002384185791;
	setAttr -s 13 ".koy[1:12]"  -0.72983813285827637 -1.1171712875366211 
		-0.88200581073760986 -0.45384570956230164 -0.32664242386817932 -0.66474103927612305 
		-1.6406722068786621 -0.35651075839996338 -0.13227854669094086 -0.092659339308738708 
		-0.059655804187059402 0;
createNode animCurveTL -n "animCurveTL513";
	setAttr ".tan" 1;
	setAttr -s 13 ".ktv[0:12]"  0 -0.034824194676283823 1 -0.055740653729448239 
		2 -0.070149441219574282 3 -0.042759272611437804 4 -0.0075174465280617147 7 0.011047375548907744 
		10 0.0097664044453775363 12 -0.0056601377253333446 13 -0.14880193619891441 16 -0.44360279801695301 
		18 -0.57885452455432507 20 -0.66621110304428277 23 -0.70679785624224767;
	setAttr -s 13 ".kit[0:12]"  3 1 3 1 1 1 1 1 
		9 1 9 9 3;
	setAttr -s 13 ".kot[0:12]"  3 1 3 1 1 1 1 1 
		9 1 9 9 3;
	setAttr -s 13 ".kix[1:12]"  0.032990399748086929 0.033333335071802139 
		0.033138494938611984 0.032359611243009567 0.10150453448295593 0.099720396101474762 
		0.066080577671527863 0.033333331346511841 0.10059268027544022 0.066666662693023682 
		0.066666662693023682 0.099999964237213135;
	setAttr -s 13 ".kiy[1:12]"  -0.023888422176241875 0 0.070817820727825165 
		0.012388106435537338 0.0010309487115591764 -0.0039245546795427799 -0.029587749391794205 
		-0.10948564112186432 -0.21724717319011688 -0.1113041490316391 -0.051177341490983963 
		0;
	setAttr -s 13 ".kox[1:12]"  0.032990407198667526 0.033333331346511841 
		0.033138502389192581 0.097078755497932434 0.10150454193353653 0.066480256617069244 
		0.033040281385183334 0.10000002384185791 0.067061766982078552 0.066666662693023682 
		0.099999964237213135 0.099999964237213135;
	setAttr -s 13 ".koy[1:12]"  -0.023888425901532173 0 0.070817843079566956 
		0.037164308130741119 0.0010309501085430384 -0.0026163682341575623 -0.014793870039284229 
		-0.32845702767372131 -0.14483141899108887 -0.1113041490316391 -0.076765991747379303 
		0;
createNode animCurveTA -n "animCurveTA988";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA989";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA990";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL514";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL515";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL516";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU805";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU806";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU807";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA991";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA992";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA993";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA994";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 3.1805546814635176e-015;
createNode animCurveTA -n "animCurveTA995";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -9.5416640443905503e-015;
createNode animCurveTA -n "animCurveTA996";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -6.3611093629270335e-015;
createNode animCurveTU -n "animCurveTU808";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU809";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999967;
createNode animCurveTU -n "animCurveTU810";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA997";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA998";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA999";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1000";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -3.9756933518293817e-016;
createNode animCurveTA -n "animCurveTA1001";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.2175560889977525e-014;
createNode animCurveTA -n "animCurveTA1002";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.3119788061037007e-014;
createNode animCurveTU -n "animCurveTU811";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU812";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999978;
createNode animCurveTU -n "animCurveTU813";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999956;
createNode animCurveTA -n "animCurveTA1003";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1004";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1005";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1006";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -6.3611093629270335e-015;
createNode animCurveTA -n "animCurveTA1007";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 6.3611093629270335e-015;
createNode animCurveTA -n "animCurveTA1008";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 6.3611093629270335e-015;
createNode animCurveTU -n "animCurveTU814";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1.0000000000000002 1 1.0000000000000002 
		2 1.0000000000000002 4 1.0000000000000002 7 1.0000000000000002 10 1.0000000000000002 
		13 1.0000000000000002 16 1.0000000000000002 18 1.0000000000000002 20 1.0000000000000002 
		23 1.0000000000000002;
createNode animCurveTU -n "animCurveTU815";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.99999999999999989 1 0.99999999999999989 
		2 0.99999999999999989 4 0.99999999999999989 7 0.99999999999999989 10 0.99999999999999989 
		13 0.99999999999999989 16 0.99999999999999989 18 0.99999999999999989 20 0.99999999999999989 
		23 0.99999999999999989;
createNode animCurveTU -n "animCurveTU816";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1 1 1 2 1 4 1 7 1 10 1 13 1 16 1 18 1 
		20 1 23 1;
createNode animCurveTA -n "animCurveTA1009";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTA -n "animCurveTA1010";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTA -n "animCurveTA1011";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTL -n "animCurveTL517";
	setAttr ".tan" 2;
	setAttr -s 13 ".ktv[0:12]"  0 -0.0037938670493906099 1 0.0099303547371249225 
		2 0.042163577664568394 3 0.053640220489846152 4 -0.0037938670493906099 7 -0.0037938670493906099 
		10 -0.0037938670493906099 11 0.00042625396828957583 13 -0.017565570755411198 16 -0.0037938670493906099 
		18 -0.0037938670493906099 20 -0.0037938670493906099 23 -0.0037938670493906099;
	setAttr -s 13 ".kit[3:12]"  3 2 2 2 3 2 2 2 
		2 2;
	setAttr -s 13 ".kot[3:12]"  3 2 2 2 3 2 2 2 
		2 2;
createNode animCurveTL -n "animCurveTL518";
	setAttr ".tan" 2;
	setAttr -s 13 ".ktv[0:12]"  0 0.028270536201956117 1 -0.030092999203619498 
		2 -0.093824263164119168 3 -0.13298289786218176 4 0.028270536201956117 7 0.028270536201956117 
		10 0.028270536201956117 11 -0.087724814012400634 13 -0.12480550569958078 16 0.028270536201956117 
		18 0.028270536201956117 20 0.028270536201956117 23 0.028270536201956117;
	setAttr -s 13 ".kit[3:12]"  3 2 2 2 3 2 2 2 
		2 2;
	setAttr -s 13 ".kot[3:12]"  3 2 2 2 3 2 2 2 
		2 2;
createNode animCurveTL -n "animCurveTL519";
	setAttr ".tan" 2;
	setAttr -s 13 ".ktv[0:12]"  0 0.030144636354398527 1 -0.0021206941743355107 
		2 0.029637938591636385 3 0.0058998378337608319 4 0.030144636354398527 7 0.030144636354398527 
		10 0.030144636354398527 11 0.073475953367949168 13 -0.095529552827196385 16 0.030144636354398527 
		18 0.030144636354398527 20 0.030144636354398527 23 0.030144636354398527;
	setAttr -s 13 ".kit[3:12]"  3 2 2 2 3 2 2 2 
		2 2;
	setAttr -s 13 ".kot[3:12]"  3 2 2 2 3 2 2 2 
		2 2;
createNode animCurveTU -n "animCurveTU817";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU818";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU819";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA1012";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 3.1805546814635128e-015;
createNode animCurveTA -n "animCurveTA1013";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 2.5444437451708134e-014;
createNode animCurveTA -n "animCurveTA1014";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.7493050748049341e-014;
createNode animCurveTL -n "animCurveTL520";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -5.5511151231257827e-017;
createNode animCurveTL -n "animCurveTL521";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.1102230246251565e-016;
createNode animCurveTL -n "animCurveTL522";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.1102230246251565e-016;
createNode animCurveTU -n "animCurveTU820";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU821";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU822";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999978;
createNode animCurveTA -n "animCurveTA1015";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1016";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1017";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1018";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1019";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1020";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU823";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999956;
createNode animCurveTU -n "animCurveTU824";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999956;
createNode animCurveTU -n "animCurveTU825";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999967;
createNode animCurveTA -n "animCurveTA1021";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1022";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1023";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1024";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1025";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1026";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU826";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU827";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999967;
createNode animCurveTU -n "animCurveTU828";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999956;
createNode animCurveTA -n "animCurveTA1027";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1028";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1029";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1030";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1031";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1032";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU829";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1.0000000000000002 1 1.0000000000000002 
		2 1.0000000000000002 4 1.0000000000000002 7 1.0000000000000002 10 1.0000000000000002 
		13 1.0000000000000002 16 1.0000000000000002 18 1.0000000000000002 20 1.0000000000000002 
		23 1.0000000000000002;
createNode animCurveTU -n "animCurveTU830";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1.0000000000000002 1 1.0000000000000002 
		2 1.0000000000000002 4 1.0000000000000002 7 1.0000000000000002 10 1.0000000000000002 
		13 1.0000000000000002 16 1.0000000000000002 18 1.0000000000000002 20 1.0000000000000002 
		23 1.0000000000000002;
createNode animCurveTU -n "animCurveTU831";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1.0000000000000002 1 1.0000000000000002 
		2 1.0000000000000002 4 1.0000000000000002 7 1.0000000000000002 10 1.0000000000000002 
		13 1.0000000000000002 16 1.0000000000000002 18 1.0000000000000002 20 1.0000000000000002 
		23 1.0000000000000002;
createNode animCurveTA -n "animCurveTA1033";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTA -n "animCurveTA1034";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTA -n "animCurveTA1035";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTL -n "animCurveTL523";
	setAttr ".tan" 2;
	setAttr -s 12 ".ktv[0:11]"  0 -0.001923613571608176 1 -0.023584130845482866 
		2 -0.034939320154758931 3 -0.051335388812284902 4 -0.001923613571608176 7 -0.001923613571608176 
		10 -0.001923613571608176 13 -0.06369487205611947 16 -0.001923613571608176 18 -0.001923613571608176 
		20 -0.001923613571608176 23 -0.001923613571608176;
	setAttr -s 12 ".kit[3:11]"  3 2 2 2 2 2 2 2 
		2;
	setAttr -s 12 ".kot[3:11]"  3 2 2 2 2 2 2 2 
		2;
createNode animCurveTL -n "animCurveTL524";
	setAttr ".tan" 2;
	setAttr -s 12 ".ktv[0:11]"  0 0.0066269326197570793 1 0.067578287108572971 
		2 0.13277038191736293 3 0.16934884185145344 4 0.0066269326197570793 7 0.0066269326197570793 
		10 0.0066269326197570793 13 0.08309412505412983 16 0.0066269326197570793 18 0.0066269326197570793 
		20 0.0066269326197570793 23 0.0066269326197570793;
	setAttr -s 12 ".kit[3:11]"  3 2 2 2 2 2 2 2 
		2;
	setAttr -s 12 ".kot[3:11]"  3 2 2 2 2 2 2 2 
		2;
createNode animCurveTL -n "animCurveTL525";
	setAttr ".tan" 2;
	setAttr -s 12 ".ktv[0:11]"  0 0.0049374768107375662 1 0.026185122803145212 
		2 0.00078093767111692136 3 0.036069636835456456 4 0.0049374768107375662 7 0.0049374768107375662 
		10 0.0049374768107375662 13 0.046889449747473028 16 0.0049374768107375662 18 0.0049374768107375662 
		20 0.0049374768107375662 23 0.0049374768107375662;
	setAttr -s 12 ".kit[3:11]"  3 2 2 2 2 2 2 2 
		2;
	setAttr -s 12 ".kot[3:11]"  3 2 2 2 2 2 2 2 
		2;
createNode animCurveTU -n "animCurveTU832";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU833";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU834";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA1036";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.9083328088781101e-014;
createNode animCurveTA -n "animCurveTA1037";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -2.1071174764695797e-014;
createNode animCurveTA -n "animCurveTA1038";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 7.2556403670886469e-015;
createNode animCurveTL -n "animCurveTL526";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL527";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.6653345369377348e-016;
createNode animCurveTL -n "animCurveTL528";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 2.2204460492503131e-016;
createNode animCurveTU -n "animCurveTU835";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999989 1.25 0.99999999999999989;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTU -n "animCurveTU836";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999989 1.25 0.99999999999999989;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTU -n "animCurveTU837";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 0.99999999999999989 1.25 0.99999999999999989;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTA -n "animCurveTA1039";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 6.7582974697168874 1.25 6.7582974697168874;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTA -n "animCurveTA1040";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 -32.755492312213462 1.25 -32.755492312213462;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTA -n "animCurveTA1041";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 3.135892765447319 1.25 3.135892765447319;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTA -n "animCurveTA1042";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -9.9392333795734899e-017;
createNode animCurveTA -n "animCurveTA1043";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.1034765745125397e-032;
createNode animCurveTA -n "animCurveTA1044";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU838";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 1 1.25 1;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTU -n "animCurveTU839";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 1 1.25 1;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTU -n "animCurveTU840";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 1 1.25 1;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTA -n "animCurveTA1045";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 -20.644023147781237 1.25 -20.644023147781237;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTA -n "animCurveTA1046";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 -32.618323385355389 1.25 -32.618323385355389;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTA -n "animCurveTA1047";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 6.0988986656034179 1.25 6.0988986656034179;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTA -n "animCurveTA1048";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1049";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1050";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU841";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 1 1.25 1;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTU -n "animCurveTU842";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 1 1.25 1;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTU -n "animCurveTU843";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 1 1.25 1;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTA -n "animCurveTA1051";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 18.599464898778805 1.25 18.599464898778805;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTA -n "animCurveTA1052";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 -50.307625382481127 1.25 -50.307625382481127;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTA -n "animCurveTA1053";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 -8.87658141042089 1.25 -8.87658141042089;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTA -n "animCurveTA1054";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1055";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1056";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU844";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 1 1.25 1;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTU -n "animCurveTU845";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 1 1.25 1;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTU -n "animCurveTU846";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 1 1.25 1;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTA -n "animCurveTA1057";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 11.405323921234361 1.25 11.405323921234361;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTA -n "animCurveTA1058";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 -8.6326481176969239 1.25 -8.6326481176969239;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTA -n "animCurveTA1059";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 -1.1811359859764405 1.25 -1.1811359859764405;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTA -n "animCurveTA1060";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1061";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1062";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU847";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 1 1.25 1;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTU -n "animCurveTU848";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 1 1.25 1;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTU -n "animCurveTU849";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 1 1.25 1;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTA -n "animCurveTA1063";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 26.714188169279709 1.25 26.714188169279709;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTA -n "animCurveTA1064";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 17.892675928963428 1.25 17.892675928963428;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTA -n "animCurveTA1065";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 -6.5316266771457903 1.25 -6.5316266771457903;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTA -n "animCurveTA1066";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1067";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1068";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU850";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 1 1.25 1;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTU -n "animCurveTU851";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 1 1.25 1;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTU -n "animCurveTU852";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 1 1.25 1;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTA -n "animCurveTA1069";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 -23.788950893554738 1.25 -23.788950893554738;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTA -n "animCurveTA1070";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 -6.2429737996198726 1.25 -6.2429737996198726;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTA -n "animCurveTA1071";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 6.1601524832728929 1.25 6.1601524832728929;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTA -n "animCurveTA1072";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.2722218725854067e-014;
createNode animCurveTA -n "animCurveTA1073";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1074";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.2722218725854067e-014;
createNode animCurveTU -n "animCurveTU853";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU854";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU855";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999978;
createNode animCurveTA -n "animCurveTA1075";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -33.589627120876649;
createNode animCurveTA -n "animCurveTA1076";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -19.03453346665188;
createNode animCurveTA -n "animCurveTA1077";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 43.96932582133153;
createNode animCurveTA -n "animCurveTA1078";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1079";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1080";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU856";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU857";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU858";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA1081";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -7.5074837646833341;
createNode animCurveTA -n "animCurveTA1082";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -10.346470817697327;
createNode animCurveTA -n "animCurveTA1083";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 4.3798330173701681;
createNode animCurveTA -n "animCurveTA1084";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -5.2966875576601877e-031;
createNode animCurveTA -n "animCurveTA1085";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -4.7708320221952744e-015;
createNode animCurveTA -n "animCurveTA1086";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.2722218725854064e-014;
createNode animCurveTU -n "animCurveTU859";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000004;
createNode animCurveTU -n "animCurveTU860";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU861";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTA -n "animCurveTA1087";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 24.58530134019081;
createNode animCurveTA -n "animCurveTA1088";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -22.886729050355829;
createNode animCurveTA -n "animCurveTA1089";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -6.2685861188654126;
createNode animCurveTA -n "animCurveTA1090";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 8.7465253740246719e-015;
createNode animCurveTA -n "animCurveTA1091";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.3716142063811415e-014;
createNode animCurveTA -n "animCurveTA1092";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 7.9513867036587903e-015;
createNode animCurveTU -n "animCurveTU862";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.99999999999999967 1 0.99999999999999967 
		2 0.99999999999999967 4 0.99999999999999967 7 0.99999999999999967 10 0.99999999999999967 
		13 0.99999999999999967 16 0.99999999999999967 18 0.99999999999999967 20 0.99999999999999967 
		23 0.99999999999999967;
createNode animCurveTU -n "animCurveTU863";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.99999999999999989 1 0.99999999999999989 
		2 0.99999999999999989 4 0.99999999999999989 7 0.99999999999999989 10 0.99999999999999989 
		13 0.99999999999999989 16 0.99999999999999989 18 0.99999999999999989 20 0.99999999999999989 
		23 0.99999999999999989;
createNode animCurveTU -n "animCurveTU864";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.99999999999999956 1 0.99999999999999956 
		2 0.99999999999999956 4 0.99999999999999956 7 0.99999999999999956 10 0.99999999999999956 
		13 0.99999999999999956 16 0.99999999999999956 18 0.99999999999999956 20 0.99999999999999956 
		23 0.99999999999999956;
createNode animCurveTA -n "animCurveTA1093";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTA -n "animCurveTA1094";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTA -n "animCurveTA1095";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTL -n "animCurveTL529";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 -0.064750274191756343 1 -0.064750274191756343 
		2 -0.064750274191756343 4 -0.064750274191756343 7 -0.064750274191756343 10 -0.064750274191756343 
		13 -0.064750274191756343 16 -0.064750274191756343 18 -0.064750274191756343 20 -0.064750274191756343 
		23 -0.064750274191756343;
createNode animCurveTL -n "animCurveTL530";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.024385943061354078 1 0.024385943061354078 
		2 0.024385943061354078 4 0.024385943061354078 7 0.024385943061354078 10 0.024385943061354078 
		13 0.024385943061354078 16 0.024385943061354078 18 0.024385943061354078 20 0.024385943061354078 
		23 0.024385943061354078;
createNode animCurveTL -n "animCurveTL531";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.035953051842049576 1 0.035953051842049576 
		2 0.035953051842049576 4 0.035953051842049576 7 0.035953051842049576 10 0.035953051842049576 
		13 0.035953051842049576 16 0.035953051842049576 18 0.035953051842049576 20 0.035953051842049576 
		23 0.035953051842049576;
createNode animCurveTU -n "animCurveTU865";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU866";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU867";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA1096";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -2.3792039902354045e-015;
createNode animCurveTA -n "animCurveTA1097";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.5902773407317578e-014;
createNode animCurveTA -n "animCurveTA1098";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -7.9762347871077225e-015;
createNode animCurveTL -n "animCurveTL532";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL533";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.1102230246251565e-016;
createNode animCurveTL -n "animCurveTL534";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU868";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000004;
createNode animCurveTU -n "animCurveTU869";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTU -n "animCurveTU870";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA1099";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -31.655989638190562;
createNode animCurveTA -n "animCurveTA1100";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 47.231445370306972;
createNode animCurveTA -n "animCurveTA1101";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 139.79825199198061;
createNode animCurveTA -n "animCurveTA1102";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1103";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1104";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU871";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU872";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU873";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA1105";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 37.881649908340925;
createNode animCurveTA -n "animCurveTA1106";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -2.7616140696926403;
createNode animCurveTA -n "animCurveTA1107";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -7.1312228569395604;
createNode animCurveTA -n "animCurveTA1108";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1109";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1110";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU874";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTU -n "animCurveTU875";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTU -n "animCurveTU876";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTA -n "animCurveTA1111";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -23.102839935356279;
createNode animCurveTA -n "animCurveTA1112";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 20.599256465231285;
createNode animCurveTA -n "animCurveTA1113";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -9.5770423274217062;
createNode animCurveTA -n "animCurveTA1114";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1115";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1116";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU877";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.99999999999999933 1 0.99999999999999933 
		2 0.99999999999999933 4 0.99999999999999933 7 0.99999999999999933 10 0.99999999999999933 
		13 0.99999999999999933 16 0.99999999999999933 18 0.99999999999999933 20 0.99999999999999933 
		23 0.99999999999999933;
createNode animCurveTU -n "animCurveTU878";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.99999999999999933 1 0.99999999999999933 
		2 0.99999999999999933 4 0.99999999999999933 7 0.99999999999999933 10 0.99999999999999933 
		13 0.99999999999999933 16 0.99999999999999933 18 0.99999999999999933 20 0.99999999999999933 
		23 0.99999999999999933;
createNode animCurveTU -n "animCurveTU879";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.99999999999999956 1 0.99999999999999956 
		2 0.99999999999999956 4 0.99999999999999956 7 0.99999999999999956 10 0.99999999999999956 
		13 0.99999999999999956 16 0.99999999999999956 18 0.99999999999999956 20 0.99999999999999956 
		23 0.99999999999999956;
createNode animCurveTA -n "animCurveTA1117";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTA -n "animCurveTA1118";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTA -n "animCurveTA1119";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTL -n "animCurveTL535";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.064750274212058229 1 0.064750274212058229 
		2 0.064750274212058229 4 0.064750274212058229 7 0.064750274212058229 10 0.064750274212058229 
		13 0.064750274212058229 16 0.064750274212058229 18 0.064750274212058229 20 0.064750274212058229 
		23 0.064750274212058229;
createNode animCurveTL -n "animCurveTL536";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 -0.024385943062840029 1 -0.024385943062840029 
		2 -0.024385943062840029 4 -0.024385943062840029 7 -0.024385943062840029 10 -0.024385943062840029 
		13 -0.024385943062840029 16 -0.024385943062840029 18 -0.024385943062840029 20 -0.024385943062840029 
		23 -0.024385943062840029;
createNode animCurveTL -n "animCurveTL537";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 -0.035953051804478865 1 -0.035953051804478865 
		2 -0.035953051804478865 4 -0.035953051804478865 7 -0.035953051804478865 10 -0.035953051804478865 
		13 -0.035953051804478865 16 -0.035953051804478865 18 -0.035953051804478865 20 -0.035953051804478865 
		23 -0.035953051804478865;
createNode animCurveTU -n "animCurveTU880";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999978;
createNode animCurveTU -n "animCurveTU881";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU882";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA1120";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1121";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1122";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL538";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 5.5511151231257827e-017;
createNode animCurveTL -n "animCurveTL539";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL540";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1123";
	setAttr ".tan" 2;
	setAttr -s 12 ".ktv[0:11]"  0 21.103584815469421 1 17.389409344114874 
		2 -0.87240221014316699 3 -3.1029498074535424 5 -20.718519957621222 9 -0.12108888732806379 
		11 37.654818456842364 15 37.654818456842364 17 53.117313591098359 20 44.149281100252473 
		22 20.607254335377689 25 11.03055575331868;
createNode animCurveTA -n "animCurveTA1124";
	setAttr ".tan" 2;
	setAttr -s 12 ".ktv[0:11]"  0 -28.028992562750005 1 -20.891016072255596 
		2 20.902719013796272 3 25.254490361119348 5 13.644716994912017 9 13.121947641141924 
		11 31.429623829145864 15 31.429623829145864 17 53.140412781016252 20 64.171515054643237 
		22 42.817755625489461 25 21.079039054994261;
createNode animCurveTA -n "animCurveTA1125";
	setAttr ".tan" 2;
	setAttr -s 12 ".ktv[0:11]"  0 -9.6181804646839844 1 -7.6630678482278913 
		2 -6.8104960096061422 3 -7.769278262348899 5 -12.902895948582664 9 -11.404244305924884 
		11 22.757357030214184 15 22.757357030214184 17 33.384565107328598 20 103.00306553324383 
		22 98.822261783823237 25 109.295381405686;
createNode animCurveTA -n "animCurveTA1126";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 42.791524096461359 1 26.764655554527483 
		2 -23.768779074787837 3 -32.088305095250512 5 -15.591417863965132 9 -76.891665953886076 
		11 -80.901672815763277 15 -80.901672815763277 17 -50.399402846132446 20 -51.264688768263625 
		22 -38.719929007809384;
createNode animCurveTA -n "animCurveTA1127";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 -4.4998573323006914 1 4.1336984366389897 
		2 20.057979295238837 3 20.73943172234457 5 16.112117938113443 9 6.7964513880846624 
		11 8.1841193729117645 15 8.1841193729117645 17 -2.9976185547896264 20 -32.003964212283087 
		22 -31.486228370076102;
createNode animCurveTA -n "animCurveTA1128";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 -39.324063842663705 1 -41.158699810959277 
		2 -59.88465033077091 3 -64.132512235236774 5 -60.005450210136821 9 -70.505723878226874 
		11 -71.028708905052625 15 -71.028708905052625 17 1.5127995190572556 20 27.395401597432851 
		22 24.673066225969215;
createNode animCurveTA -n "animCurveTA1129";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 -5.0408136271337556 1 -26.725371111983428 
		2 -46.433386155118988 3 -49.029137360645713 5 -87.447586487817901 7 -71.855245771418339 
		9 -132.57486271963361 11 -166.27102940821936 15 -166.27102940821936 17 -183.60384975809322 
		20 -173.04594668992652;
createNode animCurveTA -n "animCurveTA1130";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 -21.842118947011262 1 -24.68457725455696 
		2 -27.301235903258544 3 -27.558336249832223 5 4.8545275133561976 7 12.272838204070313 
		9 27.567904366353062 11 29.649844028770325 15 29.649844028770325 17 19.885320803981859 
		20 11.794054517579696;
createNode animCurveTA -n "animCurveTA1131";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 -29.992455857544382 1 -28.753562450891163 
		2 -27.023393927213618 3 -26.819909491199947 5 -26.709993572266754 7 -24.369145448996008 
		9 -14.483094425308249 11 -27.922116061582543 15 -27.922116061582543 17 -35.256005144736442 
		20 -30.669847817478363;
createNode animCurveTA -n "animCurveTA1132";
	setAttr ".tan" 2;
	setAttr -s 8 ".ktv[0:7]"  0 -7.1645607220777814 1 -5.6270281019969097 
		2 9.5273022765806203 5 14.685955476482176 9 22.313102260080534 11 31.687653478572447 
		15 31.687653478572447 18 19.527184125400133;
createNode animCurveTA -n "animCurveTA1133";
	setAttr ".tan" 2;
	setAttr -s 8 ".ktv[0:7]"  0 -32.79603430261303 1 -29.351145686918166 
		2 8.1193697333083001 5 24.078600808128531 9 21.582497145328038 11 40.249673092979691 
		15 40.249673092979691 18 14.518539064755842;
createNode animCurveTA -n "animCurveTA1134";
	setAttr ".tan" 2;
	setAttr -s 8 ".ktv[0:7]"  0 14.3626833378967 1 13.933115409149742 
		2 16.593760756210557 5 18.039129059175949 9 21.002935934037946 11 25.891984206595954 
		15 25.891984206595954 18 20.137907303381557;
createNode animCurveTA -n "animCurveTA1135";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 39.523803760820186 1 39.523803760820186 
		2 9.870349615676874 5 -22.278327846125777 9 -37.458619751333131 11 -95.161432880532232 
		15 -95.161432880532232 18 -50.431367512650205 20 -81.66822755572602 23 -71.810608153236018 
		28 -74.232550152814341;
createNode animCurveTA -n "animCurveTA1136";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 9.9496719665548827 1 9.9496719665548827 
		2 24.006113181973767 5 16.100214958171673 9 32.651534110043499 11 47.579946680352478 
		15 47.579946680352478 18 47.434167742688828 20 50.43217112130521 23 49.699105753670651 
		28 49.95541861778289;
createNode animCurveTA -n "animCurveTA1137";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 -81.87769569515082 1 -81.87769569515082 
		2 -90.23888729788797 5 -98.134238004516149 9 -97.920196003375423 11 -106.61512960306858 
		15 -106.61512960306858 18 -72.860373670752054 20 -95.627411028862937 23 -89.275739294731153 
		28 -90.834052397343299;
createNode animCurveTA -n "animCurveTA1138";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -4.7957238099981074 1 -38.21353077504201 
		2 -76.842732654908204 5 -83.262817426385467 9 -161.01534160100513 15 -161.01534160100513 
		18 -187.25207125964363;
createNode animCurveTA -n "animCurveTA1139";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -19.054103784046834 1 -15.604292967288325 
		2 -14.426421060141635 5 1.7900951877818005 9 22.477880731250259 15 22.477880731250259 
		18 28.373110817796658;
createNode animCurveTA -n "animCurveTA1140";
	setAttr ".tan" 2;
	setAttr -s 7 ".ktv[0:6]"  0 -9.4889103204074896 1 -14.789833484452426 
		2 -21.922288220629518 5 -21.207889172868811 9 -34.521373575345507 15 -34.521373575345507 
		18 -52.45353915923905;
createNode animCurveTA -n "animCurveTA1141";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 -1.4988823189270042 1 -1.4988823189270042 
		2 -1.4988823189270042 4 -1.4988823189270042 7 -1.4988823189270042 10 -1.4988823189270042 
		13 -1.4988823189270042 16 -1.4988823189270042 18 -1.4988823189270042 20 -1.4988823189270042 
		23 -1.4988823189270042;
createNode animCurveTA -n "animCurveTA1142";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 -3.1561835551211876 1 -3.1561835551211876 
		2 -3.1561835551211876 4 -3.1561835551211876 7 -3.1561835551211876 10 -3.1561835551211876 
		13 -3.1561835551211876 16 -3.1561835551211876 18 -3.1561835551211876 20 -3.1561835551211876 
		23 -3.1561835551211876;
createNode animCurveTA -n "animCurveTA1143";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.25301525319534846 1 0.25301525319534846 
		2 0.25301525319534846 4 0.25301525319534846 7 0.25301525319534846 10 0.25301525319534846 
		13 0.25301525319534846 16 0.25301525319534846 18 0.25301525319534846 20 0.25301525319534846 
		23 0.25301525319534846;
createNode animCurveTA -n "animCurveTA1144";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 -0.26251674276142306 1 -0.26251674276142306 
		2 -0.26251674276142306 4 -0.26251674276142306 7 -0.26251674276142306 10 -0.26251674276142306 
		13 -0.26251674276142306 16 -0.26251674276142306 18 -0.26251674276142306 20 -0.26251674276142306 
		23 -0.26251674276142306;
createNode animCurveTA -n "animCurveTA1145";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 -7.320334150302255 1 -7.320334150302255 
		2 -7.320334150302255 4 -7.320334150302255 7 -7.320334150302255 10 -7.320334150302255 
		13 -7.320334150302255 16 -7.320334150302255 18 -7.320334150302255 20 -7.320334150302255 
		23 -7.320334150302255;
createNode animCurveTA -n "animCurveTA1146";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.75000000000000011 1 0.75000000000000011 
		2 0.75000000000000011 4 0.75000000000000011 7 0.75000000000000011 10 0.75000000000000011 
		13 0.75000000000000011 16 0.75000000000000011 18 0.75000000000000011 20 0.75000000000000011 
		23 0.75000000000000011;
createNode animCurveTU -n "animCurveTU883";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.99999999999999978 1 0.99999999999999978 
		2 0.99999999999999978 4 0.99999999999999978 7 0.99999999999999978 10 0.99999999999999978 
		13 0.99999999999999978 16 0.99999999999999978 18 0.99999999999999978 20 0.99999999999999978 
		23 0.99999999999999978;
createNode animCurveTU -n "animCurveTU884";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.99999999999999978 1 0.99999999999999978 
		2 0.99999999999999978 4 0.99999999999999978 7 0.99999999999999978 10 0.99999999999999978 
		13 0.99999999999999978 16 0.99999999999999978 18 0.99999999999999978 20 0.99999999999999978 
		23 0.99999999999999978;
createNode animCurveTU -n "animCurveTU885";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1 1 1 2 1 4 1 7 1 10 1 13 1 16 1 18 1 
		20 1 23 1;
createNode animCurveTA -n "animCurveTA1147";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 2.2003467794248865 1 2.2003467794248865 
		2 2.2003467794248865 4 2.2003467794248865 7 2.2003467794248865 10 2.2003467794248865 
		13 2.2003467794248865 16 2.2003467794248865 18 2.2003467794248865 20 2.2003467794248865 
		23 2.2003467794248865;
createNode animCurveTA -n "animCurveTA1148";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 -3.9727062121129415 1 -3.9727062121129415 
		2 -3.9727062121129415 4 -3.9727062121129415 7 -3.9727062121129415 10 -3.9727062121129415 
		13 -3.9727062121129415 16 -3.9727062121129415 18 -3.9727062121129415 20 -3.9727062121129415 
		23 -3.9727062121129415;
createNode animCurveTA -n "animCurveTA1149";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.97128227707550852 1 0.97128227707550852 
		2 0.97128227707550852 4 0.97128227707550852 7 0.97128227707550852 10 0.97128227707550852 
		13 0.97128227707550852 16 0.97128227707550852 18 0.97128227707550852 20 0.97128227707550852 
		23 0.97128227707550852;
createNode animCurveTA -n "animCurveTA1150";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.5902773407317588e-015;
createNode animCurveTA -n "animCurveTA1151";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 6.3611093629270335e-015;
createNode animCurveTA -n "animCurveTA1152";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 6.3611093629270335e-015;
createNode animCurveTU -n "animCurveTU886";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.99999999999999978 1 0.99999999999999978 
		2 0.99999999999999978 4 0.99999999999999978 7 0.99999999999999978 10 0.99999999999999978 
		13 0.99999999999999978 16 0.99999999999999978 18 0.99999999999999978 20 0.99999999999999978 
		23 0.99999999999999978;
createNode animCurveTU -n "animCurveTU887";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.99999999999999978 1 0.99999999999999978 
		2 0.99999999999999978 4 0.99999999999999978 7 0.99999999999999978 10 0.99999999999999978 
		13 0.99999999999999978 16 0.99999999999999978 18 0.99999999999999978 20 0.99999999999999978 
		23 0.99999999999999978;
createNode animCurveTU -n "animCurveTU888";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1 1 1 2 1 4 1 7 1 10 1 13 1 16 1 18 1 
		20 1 23 1;
createNode animCurveTA -n "animCurveTA1153";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 2.2003467794248865 1 2.2003467794248865 
		2 2.2003467794248865 4 2.2003467794248865 7 2.2003467794248865 10 2.2003467794248865 
		13 2.2003467794248865 16 2.2003467794248865 18 2.2003467794248865 20 2.2003467794248865 
		23 2.2003467794248865;
createNode animCurveTA -n "animCurveTA1154";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 -3.9727062121129415 1 -3.9727062121129415 
		2 -3.9727062121129415 4 -3.9727062121129415 7 -3.9727062121129415 10 -3.9727062121129415 
		13 -3.9727062121129415 16 -3.9727062121129415 18 -3.9727062121129415 20 -3.9727062121129415 
		23 -3.9727062121129415;
createNode animCurveTA -n "animCurveTA1155";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.97128227707550852 1 0.97128227707550852 
		2 0.97128227707550852 4 0.97128227707550852 7 0.97128227707550852 10 0.97128227707550852 
		13 0.97128227707550852 16 0.97128227707550852 18 0.97128227707550852 20 0.97128227707550852 
		23 0.97128227707550852;
createNode animCurveTA -n "animCurveTA1156";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.1554358803754182e-015;
createNode animCurveTA -n "animCurveTA1157";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 8.5725887898821347e-016;
createNode animCurveTA -n "animCurveTA1158";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -3.1805546814635168e-015;
createNode animCurveTA -n "animCurveTA1159";
	setAttr ".tan" 2;
	setAttr -s 21 ".ktv[0:20]"  0 0 9 0 10 5.7615656571436418 12 47.440632767109989 
		13 75.239666391521538 14 32.116748826551436 15 7.2890283644539711 16 -13.227347704934155 
		17 -67.875050642720353 18 -124.26789491305453 19 -158.52186021160816 20 -184.76617617323754 
		21 -209.38257323808963 22 -229.68725767661394 23 -245.7838926397452 24 -227.67081165742496 
		25 -194.00586999636388 26 -177.22803699842342 27 -166.3996210066268 28 -159.46813316728975 
		29 -193.60522797891647;
createNode animCurveTA -n "animCurveTA1160";
	setAttr ".tan" 2;
	setAttr -s 21 ".ktv[0:20]"  0 0 9 0 10 0.26588349395841548 12 1.1024644256039082 
		13 9.1683188327463316 14 -4.8274391067138325 15 -23.978893374728941 16 -38.555789391615072 
		17 -21.662252783687673 18 7.9275257435529518 19 20.315061948450243 20 23.855924186512574 
		21 23.847744866068208 22 21.400784439891392 23 17.61568709632968 24 21.818818241688025 
		25 24.076001953941141 26 22.548200347245103 27 20.628188147459198 28 19.023386518984193 
		29 24.060165231212583;
createNode animCurveTA -n "animCurveTA1161";
	setAttr ".tan" 2;
	setAttr -s 21 ".ktv[0:20]"  0 0 9 0 10 -0.34707722505710936 12 1.6574319702374667 
		13 1.3656560816221459 14 6.3149850316412994 15 13.313751846783322 16 31.139290526634394 
		17 66.210152496762177 18 71.508767528592344 19 61.639022834769115 20 52.420878648272456 
		21 43.44264659965345 22 36.113980263445676 23 30.833762781468391 24 36.90182819132346 
		25 50.019280761294972 26 56.463837824927516 27 60.303084668476629 28 62.55486747330562 
		29 50.177122484843494;
createNode animCurveTL -n "animCurveTL541";
	setAttr ".tan" 2;
	setAttr -s 22 ".ktv[0:21]"  0 0 9 0 10 0.0041131879833218882 11 0.0028190095727196407 
		12 -0.010932339218701709 13 -0.053703693486612969 14 -0.45687780711492321 15 -0.79387834860759099 
		16 -1.035224782929862 17 -1.1188219110779267 18 -1.2451215426899667 19 -1.2660351420524709 
		20 -1.2864726963006996 21 -1.3528005736619877 22 -1.3882134248403943 23 -1.3900964722211775 
		24 -1.4044080781779511 25 -1.4409065654118276 26 -1.4900768823114605 27 -1.489153557220825 
		28 -1.503648248305077 29 -1.4987123293144866;
createNode animCurveTL -n "animCurveTL542";
	setAttr ".tan" 2;
	setAttr -s 22 ".ktv[0:21]"  0 0 9 0 10 -0.01083650123941246 11 -0.026279329750837827 
		12 0.21697555322198292 13 0.52534124005636218 14 1.0814174775365393 15 1.2450922078511784 
		16 1.3514555557668968 17 1.5203782293829431 18 1.5761494163497978 19 1.717231700854188 
		20 1.7849047532195834 21 1.8920587120485364 22 1.9117554015584073 23 1.9877493380906279 
		24 1.8540809127644007 25 1.7306341921054753 26 1.5761866883127338 27 1.4460153733244119 
		28 1.3825907239862605 29 1.4188605249305775;
createNode animCurveTL -n "animCurveTL543";
	setAttr ".tan" 2;
	setAttr -s 22 ".ktv[0:21]"  0 0 9 0 10 0.058341663286548613 11 0.18271232954830871 
		12 0.39310548102078191 13 0.11549363014075975 14 -0.14398422429609747 15 -0.086526574995783367 
		16 0.1607083347772138 17 0.56994204119624026 18 0.64352765274442614 19 0.67455336994176895 
		20 0.62966955849090911 21 0.68184161994119563 22 0.76525620610563971 23 0.85760094250718288 
		24 0.81847802912606926 25 0.84331271667333585 26 0.83805253099488852 27 0.88480787733998156 
		28 0.92939146484341284 29 1.0008612228945719;
createNode animCurveTU -n "animCurveTU889";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.99999999999999978 1 0.99999999999999978 
		2 0.99999999999999978 4 0.99999999999999978 7 0.99999999999999978 10 0.99999999999999978 
		13 0.99999999999999978 16 0.99999999999999978 18 0.99999999999999978 20 0.99999999999999978 
		23 0.99999999999999978;
createNode animCurveTU -n "animCurveTU890";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.99999999999999989 1 0.99999999999999989 
		2 0.99999999999999989 4 0.99999999999999989 7 0.99999999999999989 10 0.99999999999999989 
		13 0.99999999999999989 16 0.99999999999999989 18 0.99999999999999989 20 0.99999999999999989 
		23 0.99999999999999989;
createNode animCurveTU -n "animCurveTU891";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1.0000000000000002 1 1.0000000000000002 
		2 1.0000000000000002 4 1.0000000000000002 7 1.0000000000000002 10 1.0000000000000002 
		13 1.0000000000000002 16 1.0000000000000002 18 1.0000000000000002 20 1.0000000000000002 
		23 1.0000000000000002;
createNode animCurveTA -n "animCurveTA1162";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 -4.3754849756788365 1 -4.3754849756788365 
		2 -4.3754849756788365 4 -4.3754849756788365 7 -4.3754849756788365 10 -4.3754849756788365 
		13 -4.3754849756788365 16 -4.3754849756788365 18 -4.3754849756788365 20 -4.3754849756788365 
		23 -4.3754849756788365;
createNode animCurveTA -n "animCurveTA1163";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 -0.19266477519316091 1 -0.19266477519316091 
		2 -0.19266477519316091 4 -0.19266477519316091 7 -0.19266477519316091 10 -0.19266477519316091 
		13 -0.19266477519316091 16 -0.19266477519316091 18 -0.19266477519316091 20 -0.19266477519316091 
		23 -0.19266477519316091;
createNode animCurveTA -n "animCurveTA1164";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.090203517949951684 1 0.090203517949951684 
		2 0.090203517949951684 4 0.090203517949951684 7 0.090203517949951684 10 0.090203517949951684 
		13 0.090203517949951684 16 0.090203517949951684 18 0.090203517949951684 20 0.090203517949951684 
		23 0.090203517949951684;
createNode animCurveTL -n "animCurveTL544";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTL -n "animCurveTL545";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTL -n "animCurveTL546";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTU -n "animCurveTU892";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU893";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU894";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "animCurveTA1165";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1166";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 4.2373500461281523e-030;
createNode animCurveTA -n "animCurveTA1167";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -5.649800061504203e-030;
createNode animCurveTL -n "animCurveTL547";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL548";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL549";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU895";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 10 1 10 2 10 4 10 7 10 10 10 13 10 16 
		10 18 10 20 10 23 10;
createNode animCurveTU -n "animCurveTU896";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.99999999999999989 1 0.99999999999999989 
		2 0.99999999999999989 4 0.99999999999999989 7 0.99999999999999989 10 0.99999999999999989 
		13 0.99999999999999989 16 0.99999999999999989 18 0.99999999999999989 20 0.99999999999999989 
		23 0.99999999999999989;
createNode animCurveTU -n "animCurveTU897";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1 1 1 2 1 4 1 7 1 10 1 13 1 16 1 18 1 
		20 1 23 1;
createNode animCurveTU -n "animCurveTU898";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1 1 1 2 1 4 1 7 1 10 1 13 1 16 1 18 1 
		20 1 23 1;
createNode animCurveTA -n "animCurveTA1168";
	setAttr ".tan" 1;
	setAttr -s 15 ".ktv[0:14]"  0 21.900463788106144 1 54.424712651520764 
		2 -0.64876977128980406 4 -72.674201704429308 6 -75.154535722460793 7 -62.071975953149689 
		9 11.306628193662885 10 67.761268335846111 12 89.027674435438158 13 80.793088905030658 
		14 62.283790269454464 16 29.907882467677496 18 14.423740702825134 20 21.306235549371149 
		23 28.451213745165969;
	setAttr -s 15 ".kit[0:14]"  3 3 1 1 1 1 1 9 
		3 9 1 9 9 1 3;
	setAttr -s 15 ".kot[0:14]"  3 3 1 1 1 1 1 9 
		3 9 1 9 9 1 3;
	setAttr -s 15 ".kix[2:14]"  0.032992832362651825 0.068509571254253387 
		0.066986292600631714 0.033786516636610031 0.056393057107925415 0.033333331346511841 
		0.066666662693023682 0.033333331346511841 0.033181816339492798 0.066666692495346069 
		0.066666662693023682 0.063662603497505188 0.099999964237213135;
	setAttr -s 15 ".kiy[2:14]"  -0.89346891641616821 -0.28004863858222961 
		0.085540123283863068 0.42466548085212708 1.584559440612793 0.45216271281242371 0 
		-0.23338441550731659 -0.30960842967033386 -0.41765782237052917 -0.075063526630401611 
		0.15437883138656616 0;
	setAttr -s 15 ".kox[2:14]"  0.06632666289806366 0.068509563803672791 
		0.033652916550636292 0.067119933664798737 0.023064902052283287 0.066666662693023682 
		0.033333331346511841 0.033333331346511841 0.066515147686004639 0.066666662693023682 
		0.066666662693023682 0.096995584666728973 0.099999964237213135;
	setAttr -s 15 ".koy[2:14]"  -1.7961723804473877 -0.28004872798919678 
		0.042974073439836502 0.84363585710525513 0.64808881282806396 0.90432542562484741 
		0 -0.23338441550731659 -0.62063080072402954 -0.41765764355659485 -0.075063526630401611 
		0.23520970344543457 0;
createNode animCurveTA -n "animCurveTA1169";
	setAttr ".tan" 9;
	setAttr -s 13 ".ktv[0:12]"  0 2.0742991664280344 2 2.1333777119739699 
		3 1.4262944886585536 4 -0.45108668597418811 6 -2.5725742540517476 9 4.7542080778883111 
		12 5.0205224502700387 13 2.5298380896237864 14 2.6176261093587812 16 8.4869644512804623 
		18 17.545274694098428 20 25.605550902743325 23 32.874226919459531;
	setAttr -s 13 ".kit[3:12]"  1 3 9 1 9 9 9 9 
		1 3;
	setAttr -s 13 ".kot[3:12]"  1 3 9 1 9 9 9 9 
		1 3;
	setAttr -s 13 ".kix[3:12]"  0.028772884979844093 0.066666662693023682 
		0.10000000894069672 0.098857104778289795 0.033333331346511841 0.033333331346511841 
		0.066666692495346069 0.066666662693023682 0.065414920449256897 0.099999964237213135;
	setAttr -s 13 ".kiy[3:12]"  -0.033264290541410446 0 0.066262274980545044 
		-0.043352074921131134 -0.020969226956367493 0.034657146781682968 0.13026833534240723 
		0.14938785135746002 0.13201224803924561 0;
	setAttr -s 13 ".kox[3:12]"  0.062105361372232437 0.10000000894069672 
		0.099999994039535522 0.032190684229135513 0.033333331346511841 0.066666692495346069 
		0.066666662693023682 0.066666662693023682 0.098748080432415009 0.099999964237213135;
	setAttr -s 13 ".koy[3:12]"  -0.071799904108047485 0 0.066262267529964447 
		-0.014116669073700905 -0.020969226956367493 0.069314323365688324 0.13026827573776245 
		0.14938785135746002 0.19928111135959625 0;
createNode animCurveTA -n "animCurveTA1170";
	setAttr ".tan" 9;
	setAttr -s 12 ".ktv[0:11]"  0 -0.56933707768807773 1 -1.781152149019702 
		2 0.37426939993923969 6 4.0355996745610883 9 -0.11518737885536712 12 -1.9929180332243217 
		13 0.21936813357508606 14 0.78264156240067351 16 -1.8229677560631441 18 -13.238152575916132 
		20 -36.741147609429859 23 -46.146969672683284;
	setAttr -s 12 ".kit[2:11]"  1 3 1 3 1 3 9 9 
		9 3;
	setAttr -s 12 ".kot[2:11]"  1 3 1 3 1 3 9 9 
		9 3;
	setAttr -s 12 ".kix[2:11]"  0.019196365028619766 0.13333332538604736 
		0.096891611814498901 0.099999994039535522 0.03164224699139595 0.033333331346511841 
		0.066666692495346069 0.066666662693023682 0.066666662693023682 0.099999964237213135;
	setAttr -s 12 ".kiy[2:11]"  0.024229392409324646 0 -0.074270971119403839 
		0 0.019981922581791878 0 -0.12235453724861145 -0.30471861362457275 -0.22974692285060883 
		0;
	setAttr -s 12 ".kox[2:11]"  0.1191922202706337 0.10000000894069672 
		0.096891604363918304 0.033333331346511841 0.031642243266105652 0.066666692495346069 
		0.066666662693023682 0.066666662693023682 0.099999964237213135 0.099999964237213135;
	setAttr -s 12 ".koy[2:11]"  0.15044279396533966 0 -0.074270963668823242 
		0 0.019981924444437027 0 -0.12235448509454727 -0.30471861362457275 -0.34462028741836548 
		0;
createNode animCurveTL -n "animCurveTL550";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTL -n "animCurveTL551";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTL -n "animCurveTL552";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTU -n "animCurveTU899";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000002;
createNode animCurveTU -n "animCurveTU900";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTU -n "animCurveTU901";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.99999999999999989;
createNode animCurveTA -n "animCurveTA1171";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1172";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1173";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL553";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL554";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.1102230246251565e-016;
createNode animCurveTL -n "animCurveTL555";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.1102230246251565e-016;
createNode animCurveTU -n "animCurveTU902";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.99999999999999967 1 0.99999999999999967 
		2 0.99999999999999967 4 0.99999999999999967 7 0.99999999999999967 10 0.99999999999999967 
		13 0.99999999999999967 16 0.99999999999999967 18 0.99999999999999967 20 0.99999999999999967 
		23 0.99999999999999967;
createNode animCurveTU -n "animCurveTU903";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.99999999999999933 1 0.99999999999999933 
		2 0.99999999999999933 4 0.99999999999999933 7 0.99999999999999933 10 0.99999999999999933 
		13 0.99999999999999933 16 0.99999999999999933 18 0.99999999999999933 20 0.99999999999999933 
		23 0.99999999999999933;
createNode animCurveTU -n "animCurveTU904";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0.99999999999999978 1 0.99999999999999978 
		2 0.99999999999999978 4 0.99999999999999978 7 0.99999999999999978 10 0.99999999999999978 
		13 0.99999999999999978 16 0.99999999999999978 18 0.99999999999999978 20 0.99999999999999978 
		23 0.99999999999999978;
createNode animCurveTA -n "animCurveTA1174";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 13.295205178867663 1 13.295205178867663 
		2 13.295205178867663 4 13.295205178867663 7 13.295205178867663 10 13.295205178867663 
		13 13.295205178867663 16 13.295205178867663 18 13.295205178867663 20 13.295205178867663 
		23 13.295205178867663;
createNode animCurveTA -n "animCurveTA1175";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 -3.1611573557342734 1 -3.1611573557342734 
		2 -3.1611573557342734 4 -3.1611573557342734 7 -3.1611573557342734 10 -3.1611573557342734 
		13 -3.1611573557342734 16 -3.1611573557342734 18 -3.1611573557342734 20 -3.1611573557342734 
		23 -3.1611573557342734;
createNode animCurveTA -n "animCurveTA1176";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 -5.2867926828993701 1 -5.2867926828993701 
		2 -5.2867926828993701 4 -5.2867926828993701 7 -5.2867926828993701 10 -5.2867926828993701 
		13 -5.2867926828993701 16 -5.2867926828993701 18 -5.2867926828993701 20 -5.2867926828993701 
		23 -5.2867926828993701;
createNode animCurveTA -n "animCurveTA1177";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1178";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1179";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU905";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1 1 1 2 1 4 1 7 1 10 1 13 1 16 1 18 1 
		20 1 23 1;
createNode animCurveTU -n "animCurveTU906";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1 1 1 2 1 4 1 7 1 10 1 13 1 16 1 18 1 
		20 1 23 1;
createNode animCurveTU -n "animCurveTU907";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1 1 1 2 1 4 1 7 1 10 1 13 1 16 1 18 1 
		20 1 23 1;
createNode animCurveTA -n "animCurveTA1180";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTA -n "animCurveTA1181";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTA -n "animCurveTA1182";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTL -n "animCurveTL556";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTL -n "animCurveTL557";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  0 0 16 4.46175515744227 17 4.6697520383343676 
		18 4.7309361137698813 19 4.8256454978848975 20 4.9514082085044064 24 5.0710513185297321;
	setAttr -s 7 ".kit[0:6]"  2 2 10 16 10 10 10;
	setAttr -s 7 ".kot[0:6]"  2 2 10 16 10 10 10;
createNode animCurveTL -n "animCurveTL558";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 0 2 0 4 0 7 0 10 0 13 0 16 0 18 0 
		20 0 23 0;
createNode animCurveTU -n "animCurveTU908";
	setAttr ".tan" 2;
	setAttr -s 11 ".ktv[0:10]"  0 1 1 1 2 1 4 1 7 1 10 1 13 1 16 1 18 1 
		20 1 23 1;
	setAttr -s 11 ".kit[10]"  9;
	setAttr -s 11 ".kot[10]"  5;
createNode lightLinker -n "lightLinker1";
	setAttr -s 5 ".lnk";
	setAttr -s 5 ".slnk";
select -ne :time1;
	setAttr -av -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 25;
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
	setAttr ".mcfr" 15;
	setAttr -k on ".clip";
	setAttr -k on ".edm";
	setAttr -k on ".edl";
	setAttr -av -k on ".esr";
	setAttr -k on ".ors";
	setAttr -k on ".outf";
	setAttr -k on ".gama";
	setAttr -av -k on ".bfs";
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
connectAttr "deathSource.cl" "clipLibrary1.sc[0]";
connectAttr "animCurveTU703.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "animCurveTA858.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "animCurveTA859.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "animCurveTA860.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "animCurveTL418.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "animCurveTL419.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "animCurveTL420.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "animCurveTU704.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "animCurveTU705.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "animCurveTU706.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "animCurveTU707.a" "clipLibrary1.cel[0].cev[10].cevr";
connectAttr "animCurveTA861.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "animCurveTA862.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "animCurveTA863.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "animCurveTU708.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "animCurveTU709.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "animCurveTU710.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "animCurveTU711.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "animCurveTU712.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "animCurveTU713.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "animCurveTU714.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "animCurveTU715.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "animCurveTU716.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "animCurveTU717.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "animCurveTU718.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "animCurveTU719.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "animCurveTU720.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "animCurveTU721.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "animCurveTU722.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "animCurveTU723.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "animCurveTU724.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "animCurveTU725.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "animCurveTU726.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "animCurveTL421.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "animCurveTL422.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "animCurveTL423.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "animCurveTL424.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "animCurveTL425.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "animCurveTL426.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "animCurveTA864.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "animCurveTA865.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "animCurveTA866.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "animCurveTA867.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "animCurveTA868.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "animCurveTA869.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "animCurveTA870.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "animCurveTA871.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "animCurveTA872.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "animCurveTA873.a" "clipLibrary1.cel[0].cev[48].cevr";
connectAttr "animCurveTU727.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "animCurveTU728.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "animCurveTU729.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "animCurveTU730.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "animCurveTU731.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "animCurveTU732.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "animCurveTU733.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "animCurveTU734.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "animCurveTA874.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "animCurveTA875.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "animCurveTA876.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "animCurveTL427.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "animCurveTL428.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "animCurveTL429.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "animCurveTA877.a" "clipLibrary1.cel[0].cev[63].cevr";
connectAttr "animCurveTA878.a" "clipLibrary1.cel[0].cev[64].cevr";
connectAttr "animCurveTA879.a" "clipLibrary1.cel[0].cev[65].cevr";
connectAttr "animCurveTL430.a" "clipLibrary1.cel[0].cev[66].cevr";
connectAttr "animCurveTL431.a" "clipLibrary1.cel[0].cev[67].cevr";
connectAttr "animCurveTL432.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "animCurveTU735.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "animCurveTL433.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "animCurveTL434.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "animCurveTL435.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "animCurveTL436.a" "clipLibrary1.cel[0].cev[73].cevr";
connectAttr "animCurveTL437.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "animCurveTL438.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "animCurveTA880.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "animCurveTA881.a" "clipLibrary1.cel[0].cev[77].cevr";
connectAttr "animCurveTA882.a" "clipLibrary1.cel[0].cev[78].cevr";
connectAttr "animCurveTA883.a" "clipLibrary1.cel[0].cev[79].cevr";
connectAttr "animCurveTA884.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "animCurveTA885.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "animCurveTA886.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "animCurveTA887.a" "clipLibrary1.cel[0].cev[83].cevr";
connectAttr "animCurveTA888.a" "clipLibrary1.cel[0].cev[84].cevr";
connectAttr "animCurveTA889.a" "clipLibrary1.cel[0].cev[85].cevr";
connectAttr "animCurveTU736.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "animCurveTU737.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "animCurveTU738.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "animCurveTU739.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr "animCurveTU740.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "animCurveTU741.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "animCurveTU742.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "animCurveTU743.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "animCurveTA890.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "animCurveTA891.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "animCurveTA892.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "animCurveTL439.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "animCurveTL440.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "animCurveTL441.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "animCurveTA893.a" "clipLibrary1.cel[0].cev[100].cevr";
connectAttr "animCurveTA894.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "animCurveTA895.a" "clipLibrary1.cel[0].cev[102].cevr";
connectAttr "animCurveTL442.a" "clipLibrary1.cel[0].cev[103].cevr";
connectAttr "animCurveTL443.a" "clipLibrary1.cel[0].cev[104].cevr";
connectAttr "animCurveTL444.a" "clipLibrary1.cel[0].cev[105].cevr";
connectAttr "animCurveTU744.a" "clipLibrary1.cel[0].cev[106].cevr";
connectAttr "animCurveTU745.a" "clipLibrary1.cel[0].cev[107].cevr";
connectAttr "animCurveTA896.a" "clipLibrary1.cel[0].cev[108].cevr";
connectAttr "animCurveTA897.a" "clipLibrary1.cel[0].cev[109].cevr";
connectAttr "animCurveTA898.a" "clipLibrary1.cel[0].cev[110].cevr";
connectAttr "animCurveTL445.a" "clipLibrary1.cel[0].cev[111].cevr";
connectAttr "animCurveTL446.a" "clipLibrary1.cel[0].cev[112].cevr";
connectAttr "animCurveTL447.a" "clipLibrary1.cel[0].cev[113].cevr";
connectAttr "animCurveTU746.a" "clipLibrary1.cel[0].cev[114].cevr";
connectAttr "animCurveTU747.a" "clipLibrary1.cel[0].cev[115].cevr";
connectAttr "animCurveTU748.a" "clipLibrary1.cel[0].cev[116].cevr";
connectAttr "animCurveTA899.a" "clipLibrary1.cel[0].cev[117].cevr";
connectAttr "animCurveTA900.a" "clipLibrary1.cel[0].cev[118].cevr";
connectAttr "animCurveTA901.a" "clipLibrary1.cel[0].cev[119].cevr";
connectAttr "animCurveTL448.a" "clipLibrary1.cel[0].cev[120].cevr";
connectAttr "animCurveTL449.a" "clipLibrary1.cel[0].cev[121].cevr";
connectAttr "animCurveTL450.a" "clipLibrary1.cel[0].cev[122].cevr";
connectAttr "animCurveTU749.a" "clipLibrary1.cel[0].cev[123].cevr";
connectAttr "animCurveTU750.a" "clipLibrary1.cel[0].cev[124].cevr";
connectAttr "animCurveTA902.a" "clipLibrary1.cel[0].cev[125].cevr";
connectAttr "animCurveTA903.a" "clipLibrary1.cel[0].cev[126].cevr";
connectAttr "animCurveTA904.a" "clipLibrary1.cel[0].cev[127].cevr";
connectAttr "animCurveTL451.a" "clipLibrary1.cel[0].cev[128].cevr";
connectAttr "animCurveTL452.a" "clipLibrary1.cel[0].cev[129].cevr";
connectAttr "animCurveTL453.a" "clipLibrary1.cel[0].cev[130].cevr";
connectAttr "animCurveTU751.a" "clipLibrary1.cel[0].cev[131].cevr";
connectAttr "animCurveTU752.a" "clipLibrary1.cel[0].cev[132].cevr";
connectAttr "animCurveTU753.a" "clipLibrary1.cel[0].cev[133].cevr";
connectAttr "animCurveTA905.a" "clipLibrary1.cel[0].cev[134].cevr";
connectAttr "animCurveTA906.a" "clipLibrary1.cel[0].cev[135].cevr";
connectAttr "animCurveTA907.a" "clipLibrary1.cel[0].cev[136].cevr";
connectAttr "animCurveTL454.a" "clipLibrary1.cel[0].cev[137].cevr";
connectAttr "animCurveTL455.a" "clipLibrary1.cel[0].cev[138].cevr";
connectAttr "animCurveTL456.a" "clipLibrary1.cel[0].cev[139].cevr";
connectAttr "animCurveTU754.a" "clipLibrary1.cel[0].cev[140].cevr";
connectAttr "animCurveTU755.a" "clipLibrary1.cel[0].cev[141].cevr";
connectAttr "animCurveTA908.a" "clipLibrary1.cel[0].cev[142].cevr";
connectAttr "animCurveTA909.a" "clipLibrary1.cel[0].cev[143].cevr";
connectAttr "animCurveTA910.a" "clipLibrary1.cel[0].cev[144].cevr";
connectAttr "animCurveTL457.a" "clipLibrary1.cel[0].cev[145].cevr";
connectAttr "animCurveTL458.a" "clipLibrary1.cel[0].cev[146].cevr";
connectAttr "animCurveTL459.a" "clipLibrary1.cel[0].cev[147].cevr";
connectAttr "animCurveTU756.a" "clipLibrary1.cel[0].cev[148].cevr";
connectAttr "animCurveTU757.a" "clipLibrary1.cel[0].cev[149].cevr";
connectAttr "animCurveTU758.a" "clipLibrary1.cel[0].cev[150].cevr";
connectAttr "animCurveTA911.a" "clipLibrary1.cel[0].cev[151].cevr";
connectAttr "animCurveTA912.a" "clipLibrary1.cel[0].cev[152].cevr";
connectAttr "animCurveTA913.a" "clipLibrary1.cel[0].cev[153].cevr";
connectAttr "animCurveTL460.a" "clipLibrary1.cel[0].cev[154].cevr";
connectAttr "animCurveTL461.a" "clipLibrary1.cel[0].cev[155].cevr";
connectAttr "animCurveTL462.a" "clipLibrary1.cel[0].cev[156].cevr";
connectAttr "animCurveTU759.a" "clipLibrary1.cel[0].cev[157].cevr";
connectAttr "animCurveTU760.a" "clipLibrary1.cel[0].cev[158].cevr";
connectAttr "animCurveTL463.a" "clipLibrary1.cel[0].cev[159].cevr";
connectAttr "animCurveTL464.a" "clipLibrary1.cel[0].cev[160].cevr";
connectAttr "animCurveTL465.a" "clipLibrary1.cel[0].cev[161].cevr";
connectAttr "animCurveTL466.a" "clipLibrary1.cel[0].cev[162].cevr";
connectAttr "animCurveTL467.a" "clipLibrary1.cel[0].cev[163].cevr";
connectAttr "animCurveTL468.a" "clipLibrary1.cel[0].cev[164].cevr";
connectAttr "animCurveTA914.a" "clipLibrary1.cel[0].cev[165].cevr";
connectAttr "animCurveTA915.a" "clipLibrary1.cel[0].cev[166].cevr";
connectAttr "animCurveTA916.a" "clipLibrary1.cel[0].cev[167].cevr";
connectAttr "animCurveTA917.a" "clipLibrary1.cel[0].cev[168].cevr";
connectAttr "animCurveTA918.a" "clipLibrary1.cel[0].cev[169].cevr";
connectAttr "animCurveTA919.a" "clipLibrary1.cel[0].cev[170].cevr";
connectAttr "animCurveTA920.a" "clipLibrary1.cel[0].cev[171].cevr";
connectAttr "animCurveTA921.a" "clipLibrary1.cel[0].cev[172].cevr";
connectAttr "animCurveTA922.a" "clipLibrary1.cel[0].cev[173].cevr";
connectAttr "animCurveTA923.a" "clipLibrary1.cel[0].cev[174].cevr";
connectAttr "animCurveTU761.a" "clipLibrary1.cel[0].cev[175].cevr";
connectAttr "animCurveTU762.a" "clipLibrary1.cel[0].cev[176].cevr";
connectAttr "animCurveTU763.a" "clipLibrary1.cel[0].cev[177].cevr";
connectAttr "animCurveTU764.a" "clipLibrary1.cel[0].cev[178].cevr";
connectAttr "animCurveTU765.a" "clipLibrary1.cel[0].cev[179].cevr";
connectAttr "animCurveTU766.a" "clipLibrary1.cel[0].cev[180].cevr";
connectAttr "animCurveTU767.a" "clipLibrary1.cel[0].cev[181].cevr";
connectAttr "animCurveTU768.a" "clipLibrary1.cel[0].cev[182].cevr";
connectAttr "animCurveTA924.a" "clipLibrary1.cel[0].cev[183].cevr";
connectAttr "animCurveTA925.a" "clipLibrary1.cel[0].cev[184].cevr";
connectAttr "animCurveTA926.a" "clipLibrary1.cel[0].cev[185].cevr";
connectAttr "animCurveTL469.a" "clipLibrary1.cel[0].cev[186].cevr";
connectAttr "animCurveTL470.a" "clipLibrary1.cel[0].cev[187].cevr";
connectAttr "animCurveTL471.a" "clipLibrary1.cel[0].cev[188].cevr";
connectAttr "animCurveTA927.a" "clipLibrary1.cel[0].cev[189].cevr";
connectAttr "animCurveTA928.a" "clipLibrary1.cel[0].cev[190].cevr";
connectAttr "animCurveTA929.a" "clipLibrary1.cel[0].cev[191].cevr";
connectAttr "animCurveTL472.a" "clipLibrary1.cel[0].cev[192].cevr";
connectAttr "animCurveTL473.a" "clipLibrary1.cel[0].cev[193].cevr";
connectAttr "animCurveTL474.a" "clipLibrary1.cel[0].cev[194].cevr";
connectAttr "animCurveTU769.a" "clipLibrary1.cel[0].cev[195].cevr";
connectAttr "animCurveTU770.a" "clipLibrary1.cel[0].cev[196].cevr";
connectAttr "animCurveTU771.a" "clipLibrary1.cel[0].cev[197].cevr";
connectAttr "animCurveTA930.a" "clipLibrary1.cel[0].cev[198].cevr";
connectAttr "animCurveTA931.a" "clipLibrary1.cel[0].cev[199].cevr";
connectAttr "animCurveTA932.a" "clipLibrary1.cel[0].cev[200].cevr";
connectAttr "animCurveTL475.a" "clipLibrary1.cel[0].cev[201].cevr";
connectAttr "animCurveTL476.a" "clipLibrary1.cel[0].cev[202].cevr";
connectAttr "animCurveTL477.a" "clipLibrary1.cel[0].cev[203].cevr";
connectAttr "animCurveTU772.a" "clipLibrary1.cel[0].cev[204].cevr";
connectAttr "animCurveTU773.a" "clipLibrary1.cel[0].cev[205].cevr";
connectAttr "animCurveTU774.a" "clipLibrary1.cel[0].cev[206].cevr";
connectAttr "animCurveTA933.a" "clipLibrary1.cel[0].cev[207].cevr";
connectAttr "animCurveTA934.a" "clipLibrary1.cel[0].cev[208].cevr";
connectAttr "animCurveTA935.a" "clipLibrary1.cel[0].cev[209].cevr";
connectAttr "animCurveTL478.a" "clipLibrary1.cel[0].cev[210].cevr";
connectAttr "animCurveTL479.a" "clipLibrary1.cel[0].cev[211].cevr";
connectAttr "animCurveTL480.a" "clipLibrary1.cel[0].cev[212].cevr";
connectAttr "animCurveTU775.a" "clipLibrary1.cel[0].cev[213].cevr";
connectAttr "animCurveTU776.a" "clipLibrary1.cel[0].cev[214].cevr";
connectAttr "animCurveTL481.a" "clipLibrary1.cel[0].cev[215].cevr";
connectAttr "animCurveTL482.a" "clipLibrary1.cel[0].cev[216].cevr";
connectAttr "animCurveTL483.a" "clipLibrary1.cel[0].cev[217].cevr";
connectAttr "animCurveTU777.a" "clipLibrary1.cel[0].cev[218].cevr";
connectAttr "animCurveTU778.a" "clipLibrary1.cel[0].cev[219].cevr";
connectAttr "animCurveTU779.a" "clipLibrary1.cel[0].cev[220].cevr";
connectAttr "animCurveTA936.a" "clipLibrary1.cel[0].cev[221].cevr";
connectAttr "animCurveTA937.a" "clipLibrary1.cel[0].cev[222].cevr";
connectAttr "animCurveTA938.a" "clipLibrary1.cel[0].cev[223].cevr";
connectAttr "animCurveTL484.a" "clipLibrary1.cel[0].cev[224].cevr";
connectAttr "animCurveTL485.a" "clipLibrary1.cel[0].cev[225].cevr";
connectAttr "animCurveTL486.a" "clipLibrary1.cel[0].cev[226].cevr";
connectAttr "animCurveTU780.a" "clipLibrary1.cel[0].cev[227].cevr";
connectAttr "animCurveTU781.a" "clipLibrary1.cel[0].cev[228].cevr";
connectAttr "animCurveTL487.a" "clipLibrary1.cel[0].cev[229].cevr";
connectAttr "animCurveTL488.a" "clipLibrary1.cel[0].cev[230].cevr";
connectAttr "animCurveTL489.a" "clipLibrary1.cel[0].cev[231].cevr";
connectAttr "animCurveTU782.a" "clipLibrary1.cel[0].cev[232].cevr";
connectAttr "animCurveTU783.a" "clipLibrary1.cel[0].cev[233].cevr";
connectAttr "animCurveTU784.a" "clipLibrary1.cel[0].cev[234].cevr";
connectAttr "animCurveTA939.a" "clipLibrary1.cel[0].cev[235].cevr";
connectAttr "animCurveTA940.a" "clipLibrary1.cel[0].cev[236].cevr";
connectAttr "animCurveTA941.a" "clipLibrary1.cel[0].cev[237].cevr";
connectAttr "animCurveTL490.a" "clipLibrary1.cel[0].cev[238].cevr";
connectAttr "animCurveTL491.a" "clipLibrary1.cel[0].cev[239].cevr";
connectAttr "animCurveTL492.a" "clipLibrary1.cel[0].cev[240].cevr";
connectAttr "animCurveTU785.a" "clipLibrary1.cel[0].cev[241].cevr";
connectAttr "animCurveTU786.a" "clipLibrary1.cel[0].cev[242].cevr";
connectAttr "animCurveTL493.a" "clipLibrary1.cel[0].cev[243].cevr";
connectAttr "animCurveTL494.a" "clipLibrary1.cel[0].cev[244].cevr";
connectAttr "animCurveTL495.a" "clipLibrary1.cel[0].cev[245].cevr";
connectAttr "animCurveTL496.a" "clipLibrary1.cel[0].cev[246].cevr";
connectAttr "animCurveTL497.a" "clipLibrary1.cel[0].cev[247].cevr";
connectAttr "animCurveTL498.a" "clipLibrary1.cel[0].cev[248].cevr";
connectAttr "animCurveTA942.a" "clipLibrary1.cel[0].cev[249].cevr";
connectAttr "animCurveTA943.a" "clipLibrary1.cel[0].cev[250].cevr";
connectAttr "animCurveTA944.a" "clipLibrary1.cel[0].cev[251].cevr";
connectAttr "animCurveTA945.a" "clipLibrary1.cel[0].cev[252].cevr";
connectAttr "animCurveTA946.a" "clipLibrary1.cel[0].cev[253].cevr";
connectAttr "animCurveTA947.a" "clipLibrary1.cel[0].cev[254].cevr";
connectAttr "animCurveTA948.a" "clipLibrary1.cel[0].cev[255].cevr";
connectAttr "animCurveTA949.a" "clipLibrary1.cel[0].cev[256].cevr";
connectAttr "animCurveTA950.a" "clipLibrary1.cel[0].cev[257].cevr";
connectAttr "animCurveTA951.a" "clipLibrary1.cel[0].cev[258].cevr";
connectAttr "animCurveTU787.a" "clipLibrary1.cel[0].cev[259].cevr";
connectAttr "animCurveTU788.a" "clipLibrary1.cel[0].cev[260].cevr";
connectAttr "animCurveTU789.a" "clipLibrary1.cel[0].cev[261].cevr";
connectAttr "animCurveTU790.a" "clipLibrary1.cel[0].cev[262].cevr";
connectAttr "animCurveTU791.a" "clipLibrary1.cel[0].cev[263].cevr";
connectAttr "animCurveTU792.a" "clipLibrary1.cel[0].cev[264].cevr";
connectAttr "animCurveTU793.a" "clipLibrary1.cel[0].cev[265].cevr";
connectAttr "animCurveTU794.a" "clipLibrary1.cel[0].cev[266].cevr";
connectAttr "animCurveTA952.a" "clipLibrary1.cel[0].cev[267].cevr";
connectAttr "animCurveTA953.a" "clipLibrary1.cel[0].cev[268].cevr";
connectAttr "animCurveTA954.a" "clipLibrary1.cel[0].cev[269].cevr";
connectAttr "animCurveTL499.a" "clipLibrary1.cel[0].cev[270].cevr";
connectAttr "animCurveTL500.a" "clipLibrary1.cel[0].cev[271].cevr";
connectAttr "animCurveTL501.a" "clipLibrary1.cel[0].cev[272].cevr";
connectAttr "animCurveTA955.a" "clipLibrary1.cel[0].cev[273].cevr";
connectAttr "animCurveTA956.a" "clipLibrary1.cel[0].cev[274].cevr";
connectAttr "animCurveTA957.a" "clipLibrary1.cel[0].cev[275].cevr";
connectAttr "animCurveTL502.a" "clipLibrary1.cel[0].cev[276].cevr";
connectAttr "animCurveTL503.a" "clipLibrary1.cel[0].cev[277].cevr";
connectAttr "animCurveTL504.a" "clipLibrary1.cel[0].cev[278].cevr";
connectAttr "animCurveTA958.a" "clipLibrary1.cel[0].cev[279].cevr";
connectAttr "animCurveTA959.a" "clipLibrary1.cel[0].cev[280].cevr";
connectAttr "animCurveTA960.a" "clipLibrary1.cel[0].cev[281].cevr";
connectAttr "animCurveTA961.a" "clipLibrary1.cel[0].cev[282].cevr";
connectAttr "animCurveTA962.a" "clipLibrary1.cel[0].cev[283].cevr";
connectAttr "animCurveTA963.a" "clipLibrary1.cel[0].cev[284].cevr";
connectAttr "animCurveTL505.a" "clipLibrary1.cel[0].cev[285].cevr";
connectAttr "animCurveTL506.a" "clipLibrary1.cel[0].cev[286].cevr";
connectAttr "animCurveTL507.a" "clipLibrary1.cel[0].cev[287].cevr";
connectAttr "animCurveTA964.a" "clipLibrary1.cel[0].cev[288].cevr";
connectAttr "animCurveTA965.a" "clipLibrary1.cel[0].cev[289].cevr";
connectAttr "animCurveTA966.a" "clipLibrary1.cel[0].cev[290].cevr";
connectAttr "animCurveTL508.a" "clipLibrary1.cel[0].cev[291].cevr";
connectAttr "animCurveTL509.a" "clipLibrary1.cel[0].cev[292].cevr";
connectAttr "animCurveTL510.a" "clipLibrary1.cel[0].cev[293].cevr";
connectAttr "animCurveTU795.a" "clipLibrary1.cel[0].cev[294].cevr";
connectAttr "animCurveTU796.a" "clipLibrary1.cel[0].cev[295].cevr";
connectAttr "animCurveTU797.a" "clipLibrary1.cel[0].cev[296].cevr";
connectAttr "animCurveTA967.a" "clipLibrary1.cel[0].cev[297].cevr";
connectAttr "animCurveTA968.a" "clipLibrary1.cel[0].cev[298].cevr";
connectAttr "animCurveTA969.a" "clipLibrary1.cel[0].cev[299].cevr";
connectAttr "animCurveTA970.a" "clipLibrary1.cel[0].cev[300].cevr";
connectAttr "animCurveTA971.a" "clipLibrary1.cel[0].cev[301].cevr";
connectAttr "animCurveTA972.a" "clipLibrary1.cel[0].cev[302].cevr";
connectAttr "animCurveTU798.a" "clipLibrary1.cel[0].cev[303].cevr";
connectAttr "animCurveTU799.a" "clipLibrary1.cel[0].cev[304].cevr";
connectAttr "animCurveTU800.a" "clipLibrary1.cel[0].cev[305].cevr";
connectAttr "animCurveTA973.a" "clipLibrary1.cel[0].cev[306].cevr";
connectAttr "animCurveTA974.a" "clipLibrary1.cel[0].cev[307].cevr";
connectAttr "animCurveTA975.a" "clipLibrary1.cel[0].cev[308].cevr";
connectAttr "animCurveTA976.a" "clipLibrary1.cel[0].cev[309].cevr";
connectAttr "animCurveTA977.a" "clipLibrary1.cel[0].cev[310].cevr";
connectAttr "animCurveTA978.a" "clipLibrary1.cel[0].cev[311].cevr";
connectAttr "animCurveTU801.a" "clipLibrary1.cel[0].cev[312].cevr";
connectAttr "animCurveTU802.a" "clipLibrary1.cel[0].cev[313].cevr";
connectAttr "animCurveTU803.a" "clipLibrary1.cel[0].cev[314].cevr";
connectAttr "animCurveTA979.a" "clipLibrary1.cel[0].cev[315].cevr";
connectAttr "animCurveTA980.a" "clipLibrary1.cel[0].cev[316].cevr";
connectAttr "animCurveTA981.a" "clipLibrary1.cel[0].cev[317].cevr";
connectAttr "animCurveTA982.a" "clipLibrary1.cel[0].cev[318].cevr";
connectAttr "animCurveTA983.a" "clipLibrary1.cel[0].cev[319].cevr";
connectAttr "animCurveTA984.a" "clipLibrary1.cel[0].cev[320].cevr";
connectAttr "animCurveTU804.a" "clipLibrary1.cel[0].cev[321].cevr";
connectAttr "animCurveTA985.a" "clipLibrary1.cel[0].cev[322].cevr";
connectAttr "animCurveTA986.a" "clipLibrary1.cel[0].cev[323].cevr";
connectAttr "animCurveTA987.a" "clipLibrary1.cel[0].cev[324].cevr";
connectAttr "animCurveTL511.a" "clipLibrary1.cel[0].cev[325].cevr";
connectAttr "animCurveTL512.a" "clipLibrary1.cel[0].cev[326].cevr";
connectAttr "animCurveTL513.a" "clipLibrary1.cel[0].cev[327].cevr";
connectAttr "animCurveTA988.a" "clipLibrary1.cel[0].cev[328].cevr";
connectAttr "animCurveTA989.a" "clipLibrary1.cel[0].cev[329].cevr";
connectAttr "animCurveTA990.a" "clipLibrary1.cel[0].cev[330].cevr";
connectAttr "animCurveTL514.a" "clipLibrary1.cel[0].cev[331].cevr";
connectAttr "animCurveTL515.a" "clipLibrary1.cel[0].cev[332].cevr";
connectAttr "animCurveTL516.a" "clipLibrary1.cel[0].cev[333].cevr";
connectAttr "animCurveTU805.a" "clipLibrary1.cel[0].cev[334].cevr";
connectAttr "animCurveTU806.a" "clipLibrary1.cel[0].cev[335].cevr";
connectAttr "animCurveTU807.a" "clipLibrary1.cel[0].cev[336].cevr";
connectAttr "animCurveTA991.a" "clipLibrary1.cel[0].cev[337].cevr";
connectAttr "animCurveTA992.a" "clipLibrary1.cel[0].cev[338].cevr";
connectAttr "animCurveTA993.a" "clipLibrary1.cel[0].cev[339].cevr";
connectAttr "animCurveTA994.a" "clipLibrary1.cel[0].cev[340].cevr";
connectAttr "animCurveTA995.a" "clipLibrary1.cel[0].cev[341].cevr";
connectAttr "animCurveTA996.a" "clipLibrary1.cel[0].cev[342].cevr";
connectAttr "animCurveTU808.a" "clipLibrary1.cel[0].cev[343].cevr";
connectAttr "animCurveTU809.a" "clipLibrary1.cel[0].cev[344].cevr";
connectAttr "animCurveTU810.a" "clipLibrary1.cel[0].cev[345].cevr";
connectAttr "animCurveTA997.a" "clipLibrary1.cel[0].cev[346].cevr";
connectAttr "animCurveTA998.a" "clipLibrary1.cel[0].cev[347].cevr";
connectAttr "animCurveTA999.a" "clipLibrary1.cel[0].cev[348].cevr";
connectAttr "animCurveTA1000.a" "clipLibrary1.cel[0].cev[349].cevr";
connectAttr "animCurveTA1001.a" "clipLibrary1.cel[0].cev[350].cevr";
connectAttr "animCurveTA1002.a" "clipLibrary1.cel[0].cev[351].cevr";
connectAttr "animCurveTU811.a" "clipLibrary1.cel[0].cev[352].cevr";
connectAttr "animCurveTU812.a" "clipLibrary1.cel[0].cev[353].cevr";
connectAttr "animCurveTU813.a" "clipLibrary1.cel[0].cev[354].cevr";
connectAttr "animCurveTA1003.a" "clipLibrary1.cel[0].cev[355].cevr";
connectAttr "animCurveTA1004.a" "clipLibrary1.cel[0].cev[356].cevr";
connectAttr "animCurveTA1005.a" "clipLibrary1.cel[0].cev[357].cevr";
connectAttr "animCurveTA1006.a" "clipLibrary1.cel[0].cev[358].cevr";
connectAttr "animCurveTA1007.a" "clipLibrary1.cel[0].cev[359].cevr";
connectAttr "animCurveTA1008.a" "clipLibrary1.cel[0].cev[360].cevr";
connectAttr "animCurveTU814.a" "clipLibrary1.cel[0].cev[361].cevr";
connectAttr "animCurveTU815.a" "clipLibrary1.cel[0].cev[362].cevr";
connectAttr "animCurveTU816.a" "clipLibrary1.cel[0].cev[363].cevr";
connectAttr "animCurveTA1009.a" "clipLibrary1.cel[0].cev[364].cevr";
connectAttr "animCurveTA1010.a" "clipLibrary1.cel[0].cev[365].cevr";
connectAttr "animCurveTA1011.a" "clipLibrary1.cel[0].cev[366].cevr";
connectAttr "animCurveTL517.a" "clipLibrary1.cel[0].cev[367].cevr";
connectAttr "animCurveTL518.a" "clipLibrary1.cel[0].cev[368].cevr";
connectAttr "animCurveTL519.a" "clipLibrary1.cel[0].cev[369].cevr";
connectAttr "animCurveTU817.a" "clipLibrary1.cel[0].cev[370].cevr";
connectAttr "animCurveTU818.a" "clipLibrary1.cel[0].cev[371].cevr";
connectAttr "animCurveTU819.a" "clipLibrary1.cel[0].cev[372].cevr";
connectAttr "animCurveTA1012.a" "clipLibrary1.cel[0].cev[373].cevr";
connectAttr "animCurveTA1013.a" "clipLibrary1.cel[0].cev[374].cevr";
connectAttr "animCurveTA1014.a" "clipLibrary1.cel[0].cev[375].cevr";
connectAttr "animCurveTL520.a" "clipLibrary1.cel[0].cev[376].cevr";
connectAttr "animCurveTL521.a" "clipLibrary1.cel[0].cev[377].cevr";
connectAttr "animCurveTL522.a" "clipLibrary1.cel[0].cev[378].cevr";
connectAttr "animCurveTU820.a" "clipLibrary1.cel[0].cev[379].cevr";
connectAttr "animCurveTU821.a" "clipLibrary1.cel[0].cev[380].cevr";
connectAttr "animCurveTU822.a" "clipLibrary1.cel[0].cev[381].cevr";
connectAttr "animCurveTA1015.a" "clipLibrary1.cel[0].cev[382].cevr";
connectAttr "animCurveTA1016.a" "clipLibrary1.cel[0].cev[383].cevr";
connectAttr "animCurveTA1017.a" "clipLibrary1.cel[0].cev[384].cevr";
connectAttr "animCurveTA1018.a" "clipLibrary1.cel[0].cev[385].cevr";
connectAttr "animCurveTA1019.a" "clipLibrary1.cel[0].cev[386].cevr";
connectAttr "animCurveTA1020.a" "clipLibrary1.cel[0].cev[387].cevr";
connectAttr "animCurveTU823.a" "clipLibrary1.cel[0].cev[388].cevr";
connectAttr "animCurveTU824.a" "clipLibrary1.cel[0].cev[389].cevr";
connectAttr "animCurveTU825.a" "clipLibrary1.cel[0].cev[390].cevr";
connectAttr "animCurveTA1021.a" "clipLibrary1.cel[0].cev[391].cevr";
connectAttr "animCurveTA1022.a" "clipLibrary1.cel[0].cev[392].cevr";
connectAttr "animCurveTA1023.a" "clipLibrary1.cel[0].cev[393].cevr";
connectAttr "animCurveTA1024.a" "clipLibrary1.cel[0].cev[394].cevr";
connectAttr "animCurveTA1025.a" "clipLibrary1.cel[0].cev[395].cevr";
connectAttr "animCurveTA1026.a" "clipLibrary1.cel[0].cev[396].cevr";
connectAttr "animCurveTU826.a" "clipLibrary1.cel[0].cev[397].cevr";
connectAttr "animCurveTU827.a" "clipLibrary1.cel[0].cev[398].cevr";
connectAttr "animCurveTU828.a" "clipLibrary1.cel[0].cev[399].cevr";
connectAttr "animCurveTA1027.a" "clipLibrary1.cel[0].cev[400].cevr";
connectAttr "animCurveTA1028.a" "clipLibrary1.cel[0].cev[401].cevr";
connectAttr "animCurveTA1029.a" "clipLibrary1.cel[0].cev[402].cevr";
connectAttr "animCurveTA1030.a" "clipLibrary1.cel[0].cev[403].cevr";
connectAttr "animCurveTA1031.a" "clipLibrary1.cel[0].cev[404].cevr";
connectAttr "animCurveTA1032.a" "clipLibrary1.cel[0].cev[405].cevr";
connectAttr "animCurveTU829.a" "clipLibrary1.cel[0].cev[406].cevr";
connectAttr "animCurveTU830.a" "clipLibrary1.cel[0].cev[407].cevr";
connectAttr "animCurveTU831.a" "clipLibrary1.cel[0].cev[408].cevr";
connectAttr "animCurveTA1033.a" "clipLibrary1.cel[0].cev[409].cevr";
connectAttr "animCurveTA1034.a" "clipLibrary1.cel[0].cev[410].cevr";
connectAttr "animCurveTA1035.a" "clipLibrary1.cel[0].cev[411].cevr";
connectAttr "animCurveTL523.a" "clipLibrary1.cel[0].cev[412].cevr";
connectAttr "animCurveTL524.a" "clipLibrary1.cel[0].cev[413].cevr";
connectAttr "animCurveTL525.a" "clipLibrary1.cel[0].cev[414].cevr";
connectAttr "animCurveTU832.a" "clipLibrary1.cel[0].cev[415].cevr";
connectAttr "animCurveTU833.a" "clipLibrary1.cel[0].cev[416].cevr";
connectAttr "animCurveTU834.a" "clipLibrary1.cel[0].cev[417].cevr";
connectAttr "animCurveTA1036.a" "clipLibrary1.cel[0].cev[418].cevr";
connectAttr "animCurveTA1037.a" "clipLibrary1.cel[0].cev[419].cevr";
connectAttr "animCurveTA1038.a" "clipLibrary1.cel[0].cev[420].cevr";
connectAttr "animCurveTL526.a" "clipLibrary1.cel[0].cev[421].cevr";
connectAttr "animCurveTL527.a" "clipLibrary1.cel[0].cev[422].cevr";
connectAttr "animCurveTL528.a" "clipLibrary1.cel[0].cev[423].cevr";
connectAttr "animCurveTU835.a" "clipLibrary1.cel[0].cev[424].cevr";
connectAttr "animCurveTU836.a" "clipLibrary1.cel[0].cev[425].cevr";
connectAttr "animCurveTU837.a" "clipLibrary1.cel[0].cev[426].cevr";
connectAttr "animCurveTA1039.a" "clipLibrary1.cel[0].cev[427].cevr";
connectAttr "animCurveTA1040.a" "clipLibrary1.cel[0].cev[428].cevr";
connectAttr "animCurveTA1041.a" "clipLibrary1.cel[0].cev[429].cevr";
connectAttr "animCurveTA1042.a" "clipLibrary1.cel[0].cev[430].cevr";
connectAttr "animCurveTA1043.a" "clipLibrary1.cel[0].cev[431].cevr";
connectAttr "animCurveTA1044.a" "clipLibrary1.cel[0].cev[432].cevr";
connectAttr "animCurveTU838.a" "clipLibrary1.cel[0].cev[433].cevr";
connectAttr "animCurveTU839.a" "clipLibrary1.cel[0].cev[434].cevr";
connectAttr "animCurveTU840.a" "clipLibrary1.cel[0].cev[435].cevr";
connectAttr "animCurveTA1045.a" "clipLibrary1.cel[0].cev[436].cevr";
connectAttr "animCurveTA1046.a" "clipLibrary1.cel[0].cev[437].cevr";
connectAttr "animCurveTA1047.a" "clipLibrary1.cel[0].cev[438].cevr";
connectAttr "animCurveTA1048.a" "clipLibrary1.cel[0].cev[439].cevr";
connectAttr "animCurveTA1049.a" "clipLibrary1.cel[0].cev[440].cevr";
connectAttr "animCurveTA1050.a" "clipLibrary1.cel[0].cev[441].cevr";
connectAttr "animCurveTU841.a" "clipLibrary1.cel[0].cev[442].cevr";
connectAttr "animCurveTU842.a" "clipLibrary1.cel[0].cev[443].cevr";
connectAttr "animCurveTU843.a" "clipLibrary1.cel[0].cev[444].cevr";
connectAttr "animCurveTA1051.a" "clipLibrary1.cel[0].cev[445].cevr";
connectAttr "animCurveTA1052.a" "clipLibrary1.cel[0].cev[446].cevr";
connectAttr "animCurveTA1053.a" "clipLibrary1.cel[0].cev[447].cevr";
connectAttr "animCurveTA1054.a" "clipLibrary1.cel[0].cev[448].cevr";
connectAttr "animCurveTA1055.a" "clipLibrary1.cel[0].cev[449].cevr";
connectAttr "animCurveTA1056.a" "clipLibrary1.cel[0].cev[450].cevr";
connectAttr "animCurveTU844.a" "clipLibrary1.cel[0].cev[451].cevr";
connectAttr "animCurveTU845.a" "clipLibrary1.cel[0].cev[452].cevr";
connectAttr "animCurveTU846.a" "clipLibrary1.cel[0].cev[453].cevr";
connectAttr "animCurveTA1057.a" "clipLibrary1.cel[0].cev[454].cevr";
connectAttr "animCurveTA1058.a" "clipLibrary1.cel[0].cev[455].cevr";
connectAttr "animCurveTA1059.a" "clipLibrary1.cel[0].cev[456].cevr";
connectAttr "animCurveTA1060.a" "clipLibrary1.cel[0].cev[457].cevr";
connectAttr "animCurveTA1061.a" "clipLibrary1.cel[0].cev[458].cevr";
connectAttr "animCurveTA1062.a" "clipLibrary1.cel[0].cev[459].cevr";
connectAttr "animCurveTU847.a" "clipLibrary1.cel[0].cev[460].cevr";
connectAttr "animCurveTU848.a" "clipLibrary1.cel[0].cev[461].cevr";
connectAttr "animCurveTU849.a" "clipLibrary1.cel[0].cev[462].cevr";
connectAttr "animCurveTA1063.a" "clipLibrary1.cel[0].cev[463].cevr";
connectAttr "animCurveTA1064.a" "clipLibrary1.cel[0].cev[464].cevr";
connectAttr "animCurveTA1065.a" "clipLibrary1.cel[0].cev[465].cevr";
connectAttr "animCurveTA1066.a" "clipLibrary1.cel[0].cev[466].cevr";
connectAttr "animCurveTA1067.a" "clipLibrary1.cel[0].cev[467].cevr";
connectAttr "animCurveTA1068.a" "clipLibrary1.cel[0].cev[468].cevr";
connectAttr "animCurveTU850.a" "clipLibrary1.cel[0].cev[469].cevr";
connectAttr "animCurveTU851.a" "clipLibrary1.cel[0].cev[470].cevr";
connectAttr "animCurveTU852.a" "clipLibrary1.cel[0].cev[471].cevr";
connectAttr "animCurveTA1069.a" "clipLibrary1.cel[0].cev[472].cevr";
connectAttr "animCurveTA1070.a" "clipLibrary1.cel[0].cev[473].cevr";
connectAttr "animCurveTA1071.a" "clipLibrary1.cel[0].cev[474].cevr";
connectAttr "animCurveTA1072.a" "clipLibrary1.cel[0].cev[475].cevr";
connectAttr "animCurveTA1073.a" "clipLibrary1.cel[0].cev[476].cevr";
connectAttr "animCurveTA1074.a" "clipLibrary1.cel[0].cev[477].cevr";
connectAttr "animCurveTU853.a" "clipLibrary1.cel[0].cev[478].cevr";
connectAttr "animCurveTU854.a" "clipLibrary1.cel[0].cev[479].cevr";
connectAttr "animCurveTU855.a" "clipLibrary1.cel[0].cev[480].cevr";
connectAttr "animCurveTA1075.a" "clipLibrary1.cel[0].cev[481].cevr";
connectAttr "animCurveTA1076.a" "clipLibrary1.cel[0].cev[482].cevr";
connectAttr "animCurveTA1077.a" "clipLibrary1.cel[0].cev[483].cevr";
connectAttr "animCurveTA1078.a" "clipLibrary1.cel[0].cev[484].cevr";
connectAttr "animCurveTA1079.a" "clipLibrary1.cel[0].cev[485].cevr";
connectAttr "animCurveTA1080.a" "clipLibrary1.cel[0].cev[486].cevr";
connectAttr "animCurveTU856.a" "clipLibrary1.cel[0].cev[487].cevr";
connectAttr "animCurveTU857.a" "clipLibrary1.cel[0].cev[488].cevr";
connectAttr "animCurveTU858.a" "clipLibrary1.cel[0].cev[489].cevr";
connectAttr "animCurveTA1081.a" "clipLibrary1.cel[0].cev[490].cevr";
connectAttr "animCurveTA1082.a" "clipLibrary1.cel[0].cev[491].cevr";
connectAttr "animCurveTA1083.a" "clipLibrary1.cel[0].cev[492].cevr";
connectAttr "animCurveTA1084.a" "clipLibrary1.cel[0].cev[493].cevr";
connectAttr "animCurveTA1085.a" "clipLibrary1.cel[0].cev[494].cevr";
connectAttr "animCurveTA1086.a" "clipLibrary1.cel[0].cev[495].cevr";
connectAttr "animCurveTU859.a" "clipLibrary1.cel[0].cev[496].cevr";
connectAttr "animCurveTU860.a" "clipLibrary1.cel[0].cev[497].cevr";
connectAttr "animCurveTU861.a" "clipLibrary1.cel[0].cev[498].cevr";
connectAttr "animCurveTA1087.a" "clipLibrary1.cel[0].cev[499].cevr";
connectAttr "animCurveTA1088.a" "clipLibrary1.cel[0].cev[500].cevr";
connectAttr "animCurveTA1089.a" "clipLibrary1.cel[0].cev[501].cevr";
connectAttr "animCurveTA1090.a" "clipLibrary1.cel[0].cev[502].cevr";
connectAttr "animCurveTA1091.a" "clipLibrary1.cel[0].cev[503].cevr";
connectAttr "animCurveTA1092.a" "clipLibrary1.cel[0].cev[504].cevr";
connectAttr "animCurveTU862.a" "clipLibrary1.cel[0].cev[505].cevr";
connectAttr "animCurveTU863.a" "clipLibrary1.cel[0].cev[506].cevr";
connectAttr "animCurveTU864.a" "clipLibrary1.cel[0].cev[507].cevr";
connectAttr "animCurveTA1093.a" "clipLibrary1.cel[0].cev[508].cevr";
connectAttr "animCurveTA1094.a" "clipLibrary1.cel[0].cev[509].cevr";
connectAttr "animCurveTA1095.a" "clipLibrary1.cel[0].cev[510].cevr";
connectAttr "animCurveTL529.a" "clipLibrary1.cel[0].cev[511].cevr";
connectAttr "animCurveTL530.a" "clipLibrary1.cel[0].cev[512].cevr";
connectAttr "animCurveTL531.a" "clipLibrary1.cel[0].cev[513].cevr";
connectAttr "animCurveTU865.a" "clipLibrary1.cel[0].cev[514].cevr";
connectAttr "animCurveTU866.a" "clipLibrary1.cel[0].cev[515].cevr";
connectAttr "animCurveTU867.a" "clipLibrary1.cel[0].cev[516].cevr";
connectAttr "animCurveTA1096.a" "clipLibrary1.cel[0].cev[517].cevr";
connectAttr "animCurveTA1097.a" "clipLibrary1.cel[0].cev[518].cevr";
connectAttr "animCurveTA1098.a" "clipLibrary1.cel[0].cev[519].cevr";
connectAttr "animCurveTL532.a" "clipLibrary1.cel[0].cev[520].cevr";
connectAttr "animCurveTL533.a" "clipLibrary1.cel[0].cev[521].cevr";
connectAttr "animCurveTL534.a" "clipLibrary1.cel[0].cev[522].cevr";
connectAttr "animCurveTU868.a" "clipLibrary1.cel[0].cev[523].cevr";
connectAttr "animCurveTU869.a" "clipLibrary1.cel[0].cev[524].cevr";
connectAttr "animCurveTU870.a" "clipLibrary1.cel[0].cev[525].cevr";
connectAttr "animCurveTA1099.a" "clipLibrary1.cel[0].cev[526].cevr";
connectAttr "animCurveTA1100.a" "clipLibrary1.cel[0].cev[527].cevr";
connectAttr "animCurveTA1101.a" "clipLibrary1.cel[0].cev[528].cevr";
connectAttr "animCurveTA1102.a" "clipLibrary1.cel[0].cev[529].cevr";
connectAttr "animCurveTA1103.a" "clipLibrary1.cel[0].cev[530].cevr";
connectAttr "animCurveTA1104.a" "clipLibrary1.cel[0].cev[531].cevr";
connectAttr "animCurveTU871.a" "clipLibrary1.cel[0].cev[532].cevr";
connectAttr "animCurveTU872.a" "clipLibrary1.cel[0].cev[533].cevr";
connectAttr "animCurveTU873.a" "clipLibrary1.cel[0].cev[534].cevr";
connectAttr "animCurveTA1105.a" "clipLibrary1.cel[0].cev[535].cevr";
connectAttr "animCurveTA1106.a" "clipLibrary1.cel[0].cev[536].cevr";
connectAttr "animCurveTA1107.a" "clipLibrary1.cel[0].cev[537].cevr";
connectAttr "animCurveTA1108.a" "clipLibrary1.cel[0].cev[538].cevr";
connectAttr "animCurveTA1109.a" "clipLibrary1.cel[0].cev[539].cevr";
connectAttr "animCurveTA1110.a" "clipLibrary1.cel[0].cev[540].cevr";
connectAttr "animCurveTU874.a" "clipLibrary1.cel[0].cev[541].cevr";
connectAttr "animCurveTU875.a" "clipLibrary1.cel[0].cev[542].cevr";
connectAttr "animCurveTU876.a" "clipLibrary1.cel[0].cev[543].cevr";
connectAttr "animCurveTA1111.a" "clipLibrary1.cel[0].cev[544].cevr";
connectAttr "animCurveTA1112.a" "clipLibrary1.cel[0].cev[545].cevr";
connectAttr "animCurveTA1113.a" "clipLibrary1.cel[0].cev[546].cevr";
connectAttr "animCurveTA1114.a" "clipLibrary1.cel[0].cev[547].cevr";
connectAttr "animCurveTA1115.a" "clipLibrary1.cel[0].cev[548].cevr";
connectAttr "animCurveTA1116.a" "clipLibrary1.cel[0].cev[549].cevr";
connectAttr "animCurveTU877.a" "clipLibrary1.cel[0].cev[550].cevr";
connectAttr "animCurveTU878.a" "clipLibrary1.cel[0].cev[551].cevr";
connectAttr "animCurveTU879.a" "clipLibrary1.cel[0].cev[552].cevr";
connectAttr "animCurveTA1117.a" "clipLibrary1.cel[0].cev[553].cevr";
connectAttr "animCurveTA1118.a" "clipLibrary1.cel[0].cev[554].cevr";
connectAttr "animCurveTA1119.a" "clipLibrary1.cel[0].cev[555].cevr";
connectAttr "animCurveTL535.a" "clipLibrary1.cel[0].cev[556].cevr";
connectAttr "animCurveTL536.a" "clipLibrary1.cel[0].cev[557].cevr";
connectAttr "animCurveTL537.a" "clipLibrary1.cel[0].cev[558].cevr";
connectAttr "animCurveTU880.a" "clipLibrary1.cel[0].cev[559].cevr";
connectAttr "animCurveTU881.a" "clipLibrary1.cel[0].cev[560].cevr";
connectAttr "animCurveTU882.a" "clipLibrary1.cel[0].cev[561].cevr";
connectAttr "animCurveTA1120.a" "clipLibrary1.cel[0].cev[562].cevr";
connectAttr "animCurveTA1121.a" "clipLibrary1.cel[0].cev[563].cevr";
connectAttr "animCurveTA1122.a" "clipLibrary1.cel[0].cev[564].cevr";
connectAttr "animCurveTL538.a" "clipLibrary1.cel[0].cev[565].cevr";
connectAttr "animCurveTL539.a" "clipLibrary1.cel[0].cev[566].cevr";
connectAttr "animCurveTL540.a" "clipLibrary1.cel[0].cev[567].cevr";
connectAttr "animCurveTA1123.a" "clipLibrary1.cel[0].cev[568].cevr";
connectAttr "animCurveTA1124.a" "clipLibrary1.cel[0].cev[569].cevr";
connectAttr "animCurveTA1125.a" "clipLibrary1.cel[0].cev[570].cevr";
connectAttr "animCurveTA1126.a" "clipLibrary1.cel[0].cev[571].cevr";
connectAttr "animCurveTA1127.a" "clipLibrary1.cel[0].cev[572].cevr";
connectAttr "animCurveTA1128.a" "clipLibrary1.cel[0].cev[573].cevr";
connectAttr "animCurveTA1129.a" "clipLibrary1.cel[0].cev[574].cevr";
connectAttr "animCurveTA1130.a" "clipLibrary1.cel[0].cev[575].cevr";
connectAttr "animCurveTA1131.a" "clipLibrary1.cel[0].cev[576].cevr";
connectAttr "animCurveTA1132.a" "clipLibrary1.cel[0].cev[577].cevr";
connectAttr "animCurveTA1133.a" "clipLibrary1.cel[0].cev[578].cevr";
connectAttr "animCurveTA1134.a" "clipLibrary1.cel[0].cev[579].cevr";
connectAttr "animCurveTA1135.a" "clipLibrary1.cel[0].cev[580].cevr";
connectAttr "animCurveTA1136.a" "clipLibrary1.cel[0].cev[581].cevr";
connectAttr "animCurveTA1137.a" "clipLibrary1.cel[0].cev[582].cevr";
connectAttr "animCurveTA1138.a" "clipLibrary1.cel[0].cev[583].cevr";
connectAttr "animCurveTA1139.a" "clipLibrary1.cel[0].cev[584].cevr";
connectAttr "animCurveTA1140.a" "clipLibrary1.cel[0].cev[585].cevr";
connectAttr "animCurveTA1141.a" "clipLibrary1.cel[0].cev[586].cevr";
connectAttr "animCurveTA1142.a" "clipLibrary1.cel[0].cev[587].cevr";
connectAttr "animCurveTA1143.a" "clipLibrary1.cel[0].cev[588].cevr";
connectAttr "animCurveTA1144.a" "clipLibrary1.cel[0].cev[589].cevr";
connectAttr "animCurveTA1145.a" "clipLibrary1.cel[0].cev[590].cevr";
connectAttr "animCurveTA1146.a" "clipLibrary1.cel[0].cev[591].cevr";
connectAttr "animCurveTU883.a" "clipLibrary1.cel[0].cev[592].cevr";
connectAttr "animCurveTU884.a" "clipLibrary1.cel[0].cev[593].cevr";
connectAttr "animCurveTU885.a" "clipLibrary1.cel[0].cev[594].cevr";
connectAttr "animCurveTA1147.a" "clipLibrary1.cel[0].cev[595].cevr";
connectAttr "animCurveTA1148.a" "clipLibrary1.cel[0].cev[596].cevr";
connectAttr "animCurveTA1149.a" "clipLibrary1.cel[0].cev[597].cevr";
connectAttr "animCurveTA1150.a" "clipLibrary1.cel[0].cev[598].cevr";
connectAttr "animCurveTA1151.a" "clipLibrary1.cel[0].cev[599].cevr";
connectAttr "animCurveTA1152.a" "clipLibrary1.cel[0].cev[600].cevr";
connectAttr "animCurveTU886.a" "clipLibrary1.cel[0].cev[601].cevr";
connectAttr "animCurveTU887.a" "clipLibrary1.cel[0].cev[602].cevr";
connectAttr "animCurveTU888.a" "clipLibrary1.cel[0].cev[603].cevr";
connectAttr "animCurveTA1153.a" "clipLibrary1.cel[0].cev[604].cevr";
connectAttr "animCurveTA1154.a" "clipLibrary1.cel[0].cev[605].cevr";
connectAttr "animCurveTA1155.a" "clipLibrary1.cel[0].cev[606].cevr";
connectAttr "animCurveTA1156.a" "clipLibrary1.cel[0].cev[607].cevr";
connectAttr "animCurveTA1157.a" "clipLibrary1.cel[0].cev[608].cevr";
connectAttr "animCurveTA1158.a" "clipLibrary1.cel[0].cev[609].cevr";
connectAttr "animCurveTA1159.a" "clipLibrary1.cel[0].cev[610].cevr";
connectAttr "animCurveTA1160.a" "clipLibrary1.cel[0].cev[611].cevr";
connectAttr "animCurveTA1161.a" "clipLibrary1.cel[0].cev[612].cevr";
connectAttr "animCurveTL541.a" "clipLibrary1.cel[0].cev[613].cevr";
connectAttr "animCurveTL542.a" "clipLibrary1.cel[0].cev[614].cevr";
connectAttr "animCurveTL543.a" "clipLibrary1.cel[0].cev[615].cevr";
connectAttr "animCurveTU889.a" "clipLibrary1.cel[0].cev[616].cevr";
connectAttr "animCurveTU890.a" "clipLibrary1.cel[0].cev[617].cevr";
connectAttr "animCurveTU891.a" "clipLibrary1.cel[0].cev[618].cevr";
connectAttr "animCurveTA1162.a" "clipLibrary1.cel[0].cev[619].cevr";
connectAttr "animCurveTA1163.a" "clipLibrary1.cel[0].cev[620].cevr";
connectAttr "animCurveTA1164.a" "clipLibrary1.cel[0].cev[621].cevr";
connectAttr "animCurveTL544.a" "clipLibrary1.cel[0].cev[622].cevr";
connectAttr "animCurveTL545.a" "clipLibrary1.cel[0].cev[623].cevr";
connectAttr "animCurveTL546.a" "clipLibrary1.cel[0].cev[624].cevr";
connectAttr "animCurveTU892.a" "clipLibrary1.cel[0].cev[625].cevr";
connectAttr "animCurveTU893.a" "clipLibrary1.cel[0].cev[626].cevr";
connectAttr "animCurveTU894.a" "clipLibrary1.cel[0].cev[627].cevr";
connectAttr "animCurveTA1165.a" "clipLibrary1.cel[0].cev[628].cevr";
connectAttr "animCurveTA1166.a" "clipLibrary1.cel[0].cev[629].cevr";
connectAttr "animCurveTA1167.a" "clipLibrary1.cel[0].cev[630].cevr";
connectAttr "animCurveTL547.a" "clipLibrary1.cel[0].cev[631].cevr";
connectAttr "animCurveTL548.a" "clipLibrary1.cel[0].cev[632].cevr";
connectAttr "animCurveTL549.a" "clipLibrary1.cel[0].cev[633].cevr";
connectAttr "animCurveTU895.a" "clipLibrary1.cel[0].cev[634].cevr";
connectAttr "animCurveTU896.a" "clipLibrary1.cel[0].cev[635].cevr";
connectAttr "animCurveTU897.a" "clipLibrary1.cel[0].cev[636].cevr";
connectAttr "animCurveTU898.a" "clipLibrary1.cel[0].cev[637].cevr";
connectAttr "animCurveTA1168.a" "clipLibrary1.cel[0].cev[638].cevr";
connectAttr "animCurveTA1169.a" "clipLibrary1.cel[0].cev[639].cevr";
connectAttr "animCurveTA1170.a" "clipLibrary1.cel[0].cev[640].cevr";
connectAttr "animCurveTL550.a" "clipLibrary1.cel[0].cev[641].cevr";
connectAttr "animCurveTL551.a" "clipLibrary1.cel[0].cev[642].cevr";
connectAttr "animCurveTL552.a" "clipLibrary1.cel[0].cev[643].cevr";
connectAttr "animCurveTU899.a" "clipLibrary1.cel[0].cev[644].cevr";
connectAttr "animCurveTU900.a" "clipLibrary1.cel[0].cev[645].cevr";
connectAttr "animCurveTU901.a" "clipLibrary1.cel[0].cev[646].cevr";
connectAttr "animCurveTA1171.a" "clipLibrary1.cel[0].cev[647].cevr";
connectAttr "animCurveTA1172.a" "clipLibrary1.cel[0].cev[648].cevr";
connectAttr "animCurveTA1173.a" "clipLibrary1.cel[0].cev[649].cevr";
connectAttr "animCurveTL553.a" "clipLibrary1.cel[0].cev[650].cevr";
connectAttr "animCurveTL554.a" "clipLibrary1.cel[0].cev[651].cevr";
connectAttr "animCurveTL555.a" "clipLibrary1.cel[0].cev[652].cevr";
connectAttr "animCurveTU902.a" "clipLibrary1.cel[0].cev[653].cevr";
connectAttr "animCurveTU903.a" "clipLibrary1.cel[0].cev[654].cevr";
connectAttr "animCurveTU904.a" "clipLibrary1.cel[0].cev[655].cevr";
connectAttr "animCurveTA1174.a" "clipLibrary1.cel[0].cev[656].cevr";
connectAttr "animCurveTA1175.a" "clipLibrary1.cel[0].cev[657].cevr";
connectAttr "animCurveTA1176.a" "clipLibrary1.cel[0].cev[658].cevr";
connectAttr "animCurveTA1177.a" "clipLibrary1.cel[0].cev[659].cevr";
connectAttr "animCurveTA1178.a" "clipLibrary1.cel[0].cev[660].cevr";
connectAttr "animCurveTA1179.a" "clipLibrary1.cel[0].cev[661].cevr";
connectAttr "animCurveTU905.a" "clipLibrary1.cel[0].cev[662].cevr";
connectAttr "animCurveTU906.a" "clipLibrary1.cel[0].cev[663].cevr";
connectAttr "animCurveTU907.a" "clipLibrary1.cel[0].cev[664].cevr";
connectAttr "animCurveTA1180.a" "clipLibrary1.cel[0].cev[665].cevr";
connectAttr "animCurveTA1181.a" "clipLibrary1.cel[0].cev[666].cevr";
connectAttr "animCurveTA1182.a" "clipLibrary1.cel[0].cev[667].cevr";
connectAttr "animCurveTL556.a" "clipLibrary1.cel[0].cev[668].cevr";
connectAttr "animCurveTL557.a" "clipLibrary1.cel[0].cev[669].cevr";
connectAttr "animCurveTL558.a" "clipLibrary1.cel[0].cev[670].cevr";
connectAttr "animCurveTU908.a" "clipLibrary1.cel[0].cev[671].cevr";
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
