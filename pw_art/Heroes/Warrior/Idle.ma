//Maya ASCII 2008 scene
//Name: Idle.ma
//Last modified: Mon, Oct 06, 2008 12:56:19 PM
//Codeset: 1251
requires maya "2008";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Complete 2008";
fileInfo "version" "2008";
fileInfo "cutIdentifier" "200708022245-704165";
fileInfo "osv" "Microsoft Windows XP Service Pack 2 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 9 ".cel[0].cev";
	setAttr ".cd[0].cm" -type "characterMapping" 571 "FKIKControlCurveLeg_L.IKVis" 
		0 1 "FKIKControlCurveLeg_L.FKVis" 0 2 "FKIKControlCurveLeg_L.FKIKBlend" 
		0 3 "FKIKControlCurveArm_L.IKVis" 0 4 "FKIKControlCurveArm_L.FKVis" 
		0 5 "FKIKControlCurveArm_L.FKIKBlend" 0 6 "FKIKControlCurveSpine_M.IKVis" 
		0 7 "FKIKControlCurveSpine_M.FKVis" 0 8 "FKIKControlCurveSpine_M.FKIKBlend" 
		0 9 "FKIKControlCurveLeg_R.IKVis" 0 10 "FKIKControlCurveLeg_R.FKVis" 
		0 11 "FKIKControlCurveLeg_R.FKIKBlend" 0 12 "FKIKControlCurveArm_R.IKVis" 
		0 13 "FKIKControlCurveArm_R.FKVis" 0 14 "FKIKControlCurveArm_R.FKIKBlend" 
		0 15 "IKPoleVectorCurveLeg_L.follow" 0 16 "IKPoleVectorCurveLeg_L.translateZ" 
		1 1 "IKPoleVectorCurveLeg_L.translateY" 1 2 "IKPoleVectorCurveLeg_L.translateX" 
		1 3 "IKPoleVectorExtraLeg_L.translateZ" 1 4 "IKPoleVectorExtraLeg_L.translateY" 
		1 5 "IKPoleVectorExtraLeg_L.translateX" 1 6 "IKCurveLeg_L.antiPop" 
		0 17 "IKCurveLeg_L.stretchy" 0 18 "IKCurveLeg_L.swivel" 0 
		19 "IKCurveLeg_L.rotateZ" 2 1 "IKCurveLeg_L.rotateY" 2 2 "IKCurveLeg_L.rotateX" 
		2 3 "IKCurveLeg_L.translateZ" 1 7 "IKCurveLeg_L.translateY" 1 
		8 "IKCurveLeg_L.translateX" 1 9 "IKExtraLeg_L.rotateZ" 2 4 "IKExtraLeg_L.rotateY" 
		2 5 "IKExtraLeg_L.rotateX" 2 6 "IKExtraLeg_L.translateZ" 1 
		10 "IKExtraLeg_L.translateY" 1 11 "IKExtraLeg_L.translateX" 1 12 "IKPoleVectorCurveArm_L.follow" 
		0 20 "IKPoleVectorCurveArm_L.translateZ" 1 13 "IKPoleVectorCurveArm_L.translateY" 
		1 14 "IKPoleVectorCurveArm_L.translateX" 1 15 "IKPoleVectorExtraArm_L.translateZ" 
		1 16 "IKPoleVectorExtraArm_L.translateY" 1 17 "IKPoleVectorExtraArm_L.translateX" 
		1 18 "IKCurveArm_L.antiPop" 0 21 "IKCurveArm_L.stretchy" 0 
		22 "IKCurveArm_L.follow" 0 23 "IKCurveArm_L.rotateZ" 2 7 "IKCurveArm_L.rotateY" 
		2 8 "IKCurveArm_L.rotateX" 2 9 "IKCurveArm_L.translateZ" 1 
		19 "IKCurveArm_L.translateY" 1 20 "IKCurveArm_L.translateX" 1 21 "IKExtraArm_L.rotateZ" 
		2 10 "IKExtraArm_L.rotateY" 2 11 "IKExtraArm_L.rotateX" 2 
		12 "IKExtraArm_L.translateZ" 1 22 "IKExtraArm_L.translateY" 1 23 "IKExtraArm_L.translateX" 
		1 24 "IKCurveSpine4_M.stretchy" 0 24 "IKCurveSpine4_M.stiff" 0 
		25 "IKCurveSpine4_M.rotateZ" 2 13 "IKCurveSpine4_M.rotateY" 2 14 "IKCurveSpine4_M.rotateX" 
		2 15 "IKCurveSpine4_M.translateZ" 1 25 "IKCurveSpine4_M.translateY" 
		1 26 "IKCurveSpine4_M.translateX" 1 27 "IKExtraSpine4_M.scaleZ" 
		0 26 "IKExtraSpine4_M.scaleY" 0 27 "IKExtraSpine4_M.scaleX" 0 
		28 "IKExtraSpine4_M.rotateZ" 2 16 "IKExtraSpine4_M.rotateY" 2 17 "IKExtraSpine4_M.rotateX" 
		2 18 "IKExtraSpine4_M.translateZ" 1 28 "IKExtraSpine4_M.translateY" 
		1 29 "IKExtraSpine4_M.translateX" 1 30 "IKExtraSpine4_M.visibility" 
		0 29 "IKCurveSpine0_M.stiff" 0 30 "IKCurveSpine0_M.rotateZ" 2 
		19 "IKCurveSpine0_M.rotateY" 2 20 "IKCurveSpine0_M.rotateX" 2 21 "IKCurveSpine0_M.translateZ" 
		1 31 "IKCurveSpine0_M.translateY" 1 32 "IKCurveSpine0_M.translateX" 
		1 33 "IKExtraSpine0_M.scaleZ" 0 31 "IKExtraSpine0_M.scaleY" 0 
		32 "IKExtraSpine0_M.scaleX" 0 33 "IKExtraSpine0_M.rotateZ" 2 22 "IKExtraSpine0_M.rotateY" 
		2 23 "IKExtraSpine0_M.rotateX" 2 24 "IKExtraSpine0_M.translateZ" 
		1 34 "IKExtraSpine0_M.translateY" 1 35 "IKExtraSpine0_M.translateX" 
		1 36 "IKExtraSpine0_M.visibility" 0 34 "IKPoleVectorCurveLeg_R.follow" 
		0 35 "IKPoleVectorCurveLeg_R.translateZ" 1 37 "IKPoleVectorCurveLeg_R.translateY" 
		1 38 "IKPoleVectorCurveLeg_R.translateX" 1 39 "IKPoleVectorExtraLeg_R.translateZ" 
		1 40 "IKPoleVectorExtraLeg_R.translateY" 1 41 "IKPoleVectorExtraLeg_R.translateX" 
		1 42 "IKCurveLeg_R.antiPop" 0 36 "IKCurveLeg_R.stretchy" 0 
		37 "IKCurveLeg_R.swivel" 0 38 "IKCurveLeg_R.rotateZ" 2 25 "IKCurveLeg_R.rotateY" 
		2 26 "IKCurveLeg_R.rotateX" 2 27 "IKCurveLeg_R.translateZ" 1 
		43 "IKCurveLeg_R.translateY" 1 44 "IKCurveLeg_R.translateX" 1 45 "IKExtraLeg_R.rotateZ" 
		2 28 "IKExtraLeg_R.rotateY" 2 29 "IKExtraLeg_R.rotateX" 2 
		30 "IKExtraLeg_R.translateZ" 1 46 "IKExtraLeg_R.translateY" 1 47 "IKExtraLeg_R.translateX" 
		1 48 "IKPoleVectorCurveArm_R.follow" 0 39 "IKPoleVectorCurveArm_R.translateZ" 
		1 49 "IKPoleVectorCurveArm_R.translateY" 1 50 "IKPoleVectorCurveArm_R.translateX" 
		1 51 "IKPoleVectorExtraArm_R.translateZ" 1 52 "IKPoleVectorExtraArm_R.translateY" 
		1 53 "IKPoleVectorExtraArm_R.translateX" 1 54 "IKCurveArm_R.antiPop" 
		0 40 "IKCurveArm_R.stretchy" 0 41 "IKCurveArm_R.follow" 0 
		42 "IKCurveArm_R.rotateZ" 2 31 "IKCurveArm_R.rotateY" 2 32 "IKCurveArm_R.rotateX" 
		2 33 "IKCurveArm_R.translateZ" 1 55 "IKCurveArm_R.translateY" 1 
		56 "IKCurveArm_R.translateX" 1 57 "IKExtraArm_R.rotateZ" 2 34 "IKExtraArm_R.rotateY" 
		2 35 "IKExtraArm_R.rotateX" 2 36 "IKExtraArm_R.translateZ" 1 
		58 "IKExtraArm_R.translateY" 1 59 "IKExtraArm_R.translateX" 1 60 "HipSwingerroot1_M.rotateZ" 
		2 37 "HipSwingerroot1_M.rotateY" 2 38 "HipSwingerroot1_M.rotateX" 
		2 39 "RootCurveroot1_M.CenterBtwFeet" 0 43 "RootCurveroot1_M.rotateZ" 
		2 40 "RootCurveroot1_M.rotateY" 2 41 "RootCurveroot1_M.rotateX" 
		2 42 "RootCurveroot1_M.translateZ" 1 61 "RootCurveroot1_M.translateY" 
		1 62 "RootCurveroot1_M.translateX" 1 63 "RootExtraroot1_M.rotateZ" 
		2 43 "RootExtraroot1_M.rotateY" 2 44 "RootExtraroot1_M.rotateX" 
		2 45 "RootExtraroot1_M.translateZ" 1 64 "RootExtraroot1_M.translateY" 
		1 65 "RootExtraroot1_M.translateX" 1 66 "FKCurveright_hip_joint1_L.scaleZ" 
		0 44 "FKCurveright_hip_joint1_L.scaleY" 0 45 "FKCurveright_hip_joint1_L.scaleX" 
		0 46 "FKCurveright_hip_joint1_L.rotateZ" 2 46 "FKCurveright_hip_joint1_L.rotateY" 
		2 47 "FKCurveright_hip_joint1_L.rotateX" 2 48 "FKExtraright_hip_joint1_L.rotateZ" 
		2 49 "FKExtraright_hip_joint1_L.rotateY" 2 50 "FKExtraright_hip_joint1_L.rotateX" 
		2 51 "FKCurveright_knee_1_joint1_L.scaleZ" 0 47 "FKCurveright_knee_1_joint1_L.scaleY" 
		0 48 "FKCurveright_knee_1_joint1_L.scaleX" 0 49 "FKCurveright_knee_1_joint1_L.rotateZ" 
		2 52 "FKExtraright_knee_1_joint1_L.rotateZ" 2 53 "FKExtraright_knee_1_joint1_L.rotateY" 
		2 54 "FKExtraright_knee_1_joint1_L.rotateX" 2 55 "FKCurveright_knee_2_joint1_L.scaleZ" 
		0 50 "FKCurveright_knee_2_joint1_L.scaleY" 0 51 "FKCurveright_knee_2_joint1_L.scaleX" 
		0 52 "FKCurveright_knee_2_joint1_L.rotateZ" 2 56 "FKExtraright_knee_2_joint1_L.rotateZ" 
		2 57 "FKExtraright_knee_2_joint1_L.rotateY" 2 58 "FKExtraright_knee_2_joint1_L.rotateX" 
		2 59 "FKCurveright_feet_joint1_L.scaleZ" 0 53 "FKCurveright_feet_joint1_L.scaleY" 
		0 54 "FKCurveright_feet_joint1_L.scaleX" 0 55 "FKCurveright_feet_joint1_L.rotateZ" 
		2 60 "FKCurveright_feet_joint1_L.rotateY" 2 61 "FKCurveright_feet_joint1_L.rotateX" 
		2 62 "FKExtraright_feet_joint1_L.rotateZ" 2 63 "FKExtraright_feet_joint1_L.rotateY" 
		2 64 "FKExtraright_feet_joint1_L.rotateX" 2 65 "FKCurveright_feet_2_joint1_L.scaleZ" 
		0 56 "FKCurveright_feet_2_joint1_L.scaleY" 0 57 "FKCurveright_feet_2_joint1_L.scaleX" 
		0 58 "FKCurveright_feet_2_joint1_L.rotateZ" 2 66 "FKCurveright_feet_2_joint1_L.rotateY" 
		2 67 "FKCurveright_feet_2_joint1_L.rotateX" 2 68 "FKExtraright_feet_2_joint1_L.rotateZ" 
		2 69 "FKExtraright_feet_2_joint1_L.rotateY" 2 70 "FKExtraright_feet_2_joint1_L.rotateX" 
		2 71 "FKCurveright_shoulder_joint1_L.scaleZ" 0 59 "FKCurveright_shoulder_joint1_L.scaleY" 
		0 60 "FKCurveright_shoulder_joint1_L.scaleX" 0 61 "FKCurveright_shoulder_joint1_L.rotateZ" 
		2 72 "FKCurveright_shoulder_joint1_L.rotateY" 2 73 "FKCurveright_shoulder_joint1_L.rotateX" 
		2 74 "FKExtraright_shoulder_joint1_L.rotateZ" 2 75 "FKExtraright_shoulder_joint1_L.rotateY" 
		2 76 "FKExtraright_shoulder_joint1_L.rotateX" 2 77 "FKCurveright_elbow_1_joint1_L.scaleZ" 
		0 62 "FKCurveright_elbow_1_joint1_L.scaleY" 0 63 "FKCurveright_elbow_1_joint1_L.scaleX" 
		0 64 "FKCurveright_elbow_1_joint1_L.rotateY" 2 78 "FKExtraright_elbow_1_joint1_L.rotateZ" 
		2 79 "FKExtraright_elbow_1_joint1_L.rotateY" 2 80 "FKExtraright_elbow_1_joint1_L.rotateX" 
		2 81 "FKCurveright_elbow_2_joint1_L.scaleZ" 0 65 "FKCurveright_elbow_2_joint1_L.scaleY" 
		0 66 "FKCurveright_elbow_2_joint1_L.scaleX" 0 67 "FKCurveright_elbow_2_joint1_L.rotateY" 
		2 82 "FKExtraright_elbow_2_joint1_L.rotateZ" 2 83 "FKExtraright_elbow_2_joint1_L.rotateY" 
		2 84 "FKExtraright_elbow_2_joint1_L.rotateX" 2 85 "FKCurveright_thumb_1_joint1_L.scaleZ" 
		0 68 "FKCurveright_thumb_1_joint1_L.scaleY" 0 69 "FKCurveright_thumb_1_joint1_L.scaleX" 
		0 70 "FKCurveright_thumb_1_joint1_L.rotateZ" 2 86 "FKCurveright_thumb_1_joint1_L.rotateY" 
		2 87 "FKCurveright_thumb_1_joint1_L.rotateX" 2 88 "FKExtraright_thumb_1_joint1_L.rotateZ" 
		2 89 "FKExtraright_thumb_1_joint1_L.rotateY" 2 90 "FKExtraright_thumb_1_joint1_L.rotateX" 
		2 91 "FKCurveright_thumb_joint1_L.scaleZ" 0 71 "FKCurveright_thumb_joint1_L.scaleY" 
		0 72 "FKCurveright_thumb_joint1_L.scaleX" 0 73 "FKCurveright_thumb_joint1_L.rotateZ" 
		2 92 "FKCurveright_thumb_joint1_L.rotateY" 2 93 "FKCurveright_thumb_joint1_L.rotateX" 
		2 94 "FKExtraright_thumb_joint1_L.rotateZ" 2 95 "FKExtraright_thumb_joint1_L.rotateY" 
		2 96 "FKExtraright_thumb_joint1_L.rotateX" 2 97 "FKCurveright_fingrs_2_joint1_L.scaleZ" 
		0 74 "FKCurveright_fingrs_2_joint1_L.scaleY" 0 75 "FKCurveright_fingrs_2_joint1_L.scaleX" 
		0 76 "FKCurveright_fingrs_2_joint1_L.rotateZ" 2 98 "FKCurveright_fingrs_2_joint1_L.rotateY" 
		2 99 "FKCurveright_fingrs_2_joint1_L.rotateX" 2 100 "FKExtraright_fingrs_2_joint1_L.rotateZ" 
		2 101 "FKExtraright_fingrs_2_joint1_L.rotateY" 2 102 "FKExtraright_fingrs_2_joint1_L.rotateX" 
		2 103 "FKCurveright_fingrs_1_joint1_L.scaleZ" 0 77 "FKCurveright_fingrs_1_joint1_L.scaleY" 
		0 78 "FKCurveright_fingrs_1_joint1_L.scaleX" 0 79 "FKCurveright_fingrs_1_joint1_L.rotateZ" 
		2 104 "FKCurveright_fingrs_1_joint1_L.rotateY" 2 105 "FKCurveright_fingrs_1_joint1_L.rotateX" 
		2 106 "FKExtraright_fingrs_1_joint1_L.rotateZ" 2 107 "FKExtraright_fingrs_1_joint1_L.rotateY" 
		2 108 "FKExtraright_fingrs_1_joint1_L.rotateX" 2 109 "FKCurveright_fist_joint1_L.scaleZ" 
		0 80 "FKCurveright_fist_joint1_L.scaleY" 0 81 "FKCurveright_fist_joint1_L.scaleX" 
		0 82 "FKCurveright_fist_joint1_L.rotateZ" 2 110 "FKCurveright_fist_joint1_L.rotateY" 
		2 111 "FKCurveright_fist_joint1_L.rotateX" 2 112 "FKExtraright_fist_joint1_L.rotateZ" 
		2 113 "FKExtraright_fist_joint1_L.rotateY" 2 114 "FKExtraright_fist_joint1_L.rotateX" 
		2 115 "FKCurveright_hip_joint1_R.scaleZ" 0 83 "FKCurveright_hip_joint1_R.scaleY" 
		0 84 "FKCurveright_hip_joint1_R.scaleX" 0 85 "FKCurveright_hip_joint1_R.rotateZ" 
		2 116 "FKCurveright_hip_joint1_R.rotateY" 2 117 "FKCurveright_hip_joint1_R.rotateX" 
		2 118 "FKExtraright_hip_joint1_R.rotateZ" 2 119 "FKExtraright_hip_joint1_R.rotateY" 
		2 120 "FKExtraright_hip_joint1_R.rotateX" 2 121 "FKCurveright_knee_1_joint1_R.scaleZ" 
		0 86 "FKCurveright_knee_1_joint1_R.scaleY" 0 87 "FKCurveright_knee_1_joint1_R.scaleX" 
		0 88 "FKCurveright_knee_1_joint1_R.rotateZ" 2 122 "FKExtraright_knee_1_joint1_R.rotateZ" 
		2 123 "FKExtraright_knee_1_joint1_R.rotateY" 2 124 "FKExtraright_knee_1_joint1_R.rotateX" 
		2 125 "FKCurveright_knee_2_joint1_R.scaleZ" 0 89 "FKCurveright_knee_2_joint1_R.scaleY" 
		0 90 "FKCurveright_knee_2_joint1_R.scaleX" 0 91 "FKCurveright_knee_2_joint1_R.rotateZ" 
		2 126 "FKExtraright_knee_2_joint1_R.rotateZ" 2 127 "FKExtraright_knee_2_joint1_R.rotateY" 
		2 128 "FKExtraright_knee_2_joint1_R.rotateX" 2 129 "FKCurveright_feet_joint1_R.scaleZ" 
		0 92 "FKCurveright_feet_joint1_R.scaleY" 0 93 "FKCurveright_feet_joint1_R.scaleX" 
		0 94 "FKCurveright_feet_joint1_R.rotateZ" 2 130 "FKCurveright_feet_joint1_R.rotateY" 
		2 131 "FKCurveright_feet_joint1_R.rotateX" 2 132 "FKExtraright_feet_joint1_R.rotateZ" 
		2 133 "FKExtraright_feet_joint1_R.rotateY" 2 134 "FKExtraright_feet_joint1_R.rotateX" 
		2 135 "FKCurveright_feet_2_joint1_R.scaleZ" 0 95 "FKCurveright_feet_2_joint1_R.scaleY" 
		0 96 "FKCurveright_feet_2_joint1_R.scaleX" 0 97 "FKCurveright_feet_2_joint1_R.rotateZ" 
		2 136 "FKCurveright_feet_2_joint1_R.rotateY" 2 137 "FKCurveright_feet_2_joint1_R.rotateX" 
		2 138 "FKExtraright_feet_2_joint1_R.rotateZ" 2 139 "FKExtraright_feet_2_joint1_R.rotateY" 
		2 140 "FKExtraright_feet_2_joint1_R.rotateX" 2 141 "FKCurvefront_cloth_2_joint1_M.scaleZ" 
		0 98 "FKCurvefront_cloth_2_joint1_M.scaleY" 0 99 "FKCurvefront_cloth_2_joint1_M.scaleX" 
		0 100 "FKCurvefront_cloth_2_joint1_M.rotateZ" 2 142 "FKCurvefront_cloth_2_joint1_M.rotateY" 
		2 143 "FKCurvefront_cloth_2_joint1_M.rotateX" 2 144 "FKExtrafront_cloth_2_joint1_M.rotateZ" 
		2 145 "FKExtrafront_cloth_2_joint1_M.rotateY" 2 146 "FKExtrafront_cloth_2_joint1_M.rotateX" 
		2 147 "FKCurvefront_cloth_1_joint1_M.scaleZ" 0 101 "FKCurvefront_cloth_1_joint1_M.scaleY" 
		0 102 "FKCurvefront_cloth_1_joint1_M.scaleX" 0 103 "FKCurvefront_cloth_1_joint1_M.rotateZ" 
		2 148 "FKCurvefront_cloth_1_joint1_M.rotateY" 2 149 "FKCurvefront_cloth_1_joint1_M.rotateX" 
		2 150 "FKExtrafront_cloth_1_joint1_M.rotateZ" 2 151 "FKExtrafront_cloth_1_joint1_M.rotateY" 
		2 152 "FKExtrafront_cloth_1_joint1_M.rotateX" 2 153 "FKCurvefront_cloth_joint1_M.scaleZ" 
		0 104 "FKCurvefront_cloth_joint1_M.scaleY" 0 105 "FKCurvefront_cloth_joint1_M.scaleX" 
		0 106 "FKCurvefront_cloth_joint1_M.rotateZ" 2 154 "FKCurvefront_cloth_joint1_M.rotateY" 
		2 155 "FKCurvefront_cloth_joint1_M.rotateX" 2 156 "FKExtrafront_cloth_joint1_M.rotateZ" 
		2 157 "FKExtrafront_cloth_joint1_M.rotateY" 2 158 "FKExtrafront_cloth_joint1_M.rotateX" 
		2 159 "FKCurveback_cloth_1_joint1_M.scaleZ" 0 107 "FKCurveback_cloth_1_joint1_M.scaleY" 
		0 108 "FKCurveback_cloth_1_joint1_M.scaleX" 0 109 "FKCurveback_cloth_1_joint1_M.rotateZ" 
		2 160 "FKCurveback_cloth_1_joint1_M.rotateY" 2 161 "FKCurveback_cloth_1_joint1_M.rotateX" 
		2 162 "FKExtraback_cloth_1_joint1_M.rotateZ" 2 163 "FKExtraback_cloth_1_joint1_M.rotateY" 
		2 164 "FKExtraback_cloth_1_joint1_M.rotateX" 2 165 "FKCurveback_cloth_joint1_M.scaleZ" 
		0 110 "FKCurveback_cloth_joint1_M.scaleY" 0 111 "FKCurveback_cloth_joint1_M.scaleX" 
		0 112 "FKCurveback_cloth_joint1_M.rotateZ" 2 166 "FKCurveback_cloth_joint1_M.rotateY" 
		2 167 "FKCurveback_cloth_joint1_M.rotateX" 2 168 "FKExtraback_cloth_joint1_M.rotateZ" 
		2 169 "FKExtraback_cloth_joint1_M.rotateY" 2 170 "FKExtraback_cloth_joint1_M.rotateX" 
		2 171 "FKCurvechest_joint1_M.scaleZ" 0 113 "FKCurvechest_joint1_M.scaleY" 
		0 114 "FKCurvechest_joint1_M.scaleX" 0 115 "FKCurvechest_joint1_M.rotateZ" 
		2 172 "FKCurvechest_joint1_M.rotateY" 2 173 "FKCurvechest_joint1_M.rotateX" 
		2 174 "FKExtrachest_joint1_M.rotateZ" 2 175 "FKExtrachest_joint1_M.rotateY" 
		2 176 "FKExtrachest_joint1_M.rotateX" 2 177 "FKCurvetiger_arm_joint1_L.scaleZ" 
		0 116 "FKCurvetiger_arm_joint1_L.scaleY" 0 117 "FKCurvetiger_arm_joint1_L.scaleX" 
		0 118 "FKCurvetiger_arm_joint1_L.rotateZ" 2 178 "FKCurvetiger_arm_joint1_L.rotateY" 
		2 179 "FKCurvetiger_arm_joint1_L.rotateX" 2 180 "FKCurvetiger_arm_joint1_L.translateZ" 
		1 67 "FKCurvetiger_arm_joint1_L.translateY" 1 68 "FKCurvetiger_arm_joint1_L.translateX" 
		1 69 "FKExtratiger_arm_joint1_L.scaleZ" 0 119 "FKExtratiger_arm_joint1_L.scaleY" 
		0 120 "FKExtratiger_arm_joint1_L.scaleX" 0 121 "FKExtratiger_arm_joint1_L.rotateZ" 
		2 181 "FKExtratiger_arm_joint1_L.rotateY" 2 182 "FKExtratiger_arm_joint1_L.rotateX" 
		2 183 "FKExtratiger_arm_joint1_L.translateZ" 1 70 "FKExtratiger_arm_joint1_L.translateY" 
		1 71 "FKExtratiger_arm_joint1_L.translateX" 1 72 "FKCurveleft_arm_joint1_joint1_L.scaleZ" 
		0 122 "FKCurveleft_arm_joint1_joint1_L.scaleY" 0 123 "FKCurveleft_arm_joint1_joint1_L.scaleX" 
		0 124 "FKCurveleft_arm_joint1_joint1_L.rotateZ" 2 184 "FKCurveleft_arm_joint1_joint1_L.rotateY" 
		2 185 "FKCurveleft_arm_joint1_joint1_L.rotateX" 2 186 "FKCurveleft_arm_joint1_joint1_L.translateZ" 
		1 73 "FKCurveleft_arm_joint1_joint1_L.translateY" 1 74 "FKCurveleft_arm_joint1_joint1_L.translateX" 
		1 75 "FKExtraleft_arm_joint1_joint1_L.scaleZ" 0 125 "FKExtraleft_arm_joint1_joint1_L.scaleY" 
		0 126 "FKExtraleft_arm_joint1_joint1_L.scaleX" 0 127 "FKExtraleft_arm_joint1_joint1_L.rotateZ" 
		2 187 "FKExtraleft_arm_joint1_joint1_L.rotateY" 2 188 "FKExtraleft_arm_joint1_joint1_L.rotateX" 
		2 189 "FKExtraleft_arm_joint1_joint1_L.translateZ" 1 76 "FKExtraleft_arm_joint1_joint1_L.translateY" 
		1 77 "FKExtraleft_arm_joint1_joint1_L.translateX" 1 78 "FKCurvetiger_arm_2_joint1_R.scaleZ" 
		0 128 "FKCurvetiger_arm_2_joint1_R.scaleY" 0 129 "FKCurvetiger_arm_2_joint1_R.scaleX" 
		0 130 "FKCurvetiger_arm_2_joint1_R.rotateZ" 2 190 "FKCurvetiger_arm_2_joint1_R.rotateY" 
		2 191 "FKCurvetiger_arm_2_joint1_R.rotateX" 2 192 "FKCurvetiger_arm_2_joint1_R.translateZ" 
		1 79 "FKCurvetiger_arm_2_joint1_R.translateY" 1 80 "FKCurvetiger_arm_2_joint1_R.translateX" 
		1 81 "FKExtratiger_arm_2_joint1_R.scaleZ" 0 131 "FKExtratiger_arm_2_joint1_R.scaleY" 
		0 132 "FKExtratiger_arm_2_joint1_R.scaleX" 0 133 "FKExtratiger_arm_2_joint1_R.rotateZ" 
		2 193 "FKExtratiger_arm_2_joint1_R.rotateY" 2 194 "FKExtratiger_arm_2_joint1_R.rotateX" 
		2 195 "FKExtratiger_arm_2_joint1_R.translateZ" 1 82 "FKExtratiger_arm_2_joint1_R.translateY" 
		1 83 "FKExtratiger_arm_2_joint1_R.translateX" 1 84 "FKCurvetiger_arm_1_joint1_R.scaleZ" 
		0 134 "FKCurvetiger_arm_1_joint1_R.scaleY" 0 135 "FKCurvetiger_arm_1_joint1_R.scaleX" 
		0 136 "FKCurvetiger_arm_1_joint1_R.rotateZ" 2 196 "FKCurvetiger_arm_1_joint1_R.rotateY" 
		2 197 "FKCurvetiger_arm_1_joint1_R.rotateX" 2 198 "FKCurvetiger_arm_1_joint1_R.translateZ" 
		1 85 "FKCurvetiger_arm_1_joint1_R.translateY" 1 86 "FKCurvetiger_arm_1_joint1_R.translateX" 
		1 87 "FKExtratiger_arm_1_joint1_R.scaleZ" 0 137 "FKExtratiger_arm_1_joint1_R.scaleY" 
		0 138 "FKExtratiger_arm_1_joint1_R.scaleX" 0 139 "FKExtratiger_arm_1_joint1_R.rotateZ" 
		2 199 "FKExtratiger_arm_1_joint1_R.rotateY" 2 200 "FKExtratiger_arm_1_joint1_R.rotateX" 
		2 201 "FKExtratiger_arm_1_joint1_R.translateZ" 1 88 "FKExtratiger_arm_1_joint1_R.translateY" 
		1 89 "FKExtratiger_arm_1_joint1_R.translateX" 1 90 "FKCurvetiger_arm_joint1_R.scaleZ" 
		0 140 "FKCurvetiger_arm_joint1_R.scaleY" 0 141 "FKCurvetiger_arm_joint1_R.scaleX" 
		0 142 "FKCurvetiger_arm_joint1_R.rotateZ" 2 202 "FKCurvetiger_arm_joint1_R.rotateY" 
		2 203 "FKCurvetiger_arm_joint1_R.rotateX" 2 204 "FKCurvetiger_arm_joint1_R.translateZ" 
		1 91 "FKCurvetiger_arm_joint1_R.translateY" 1 92 "FKCurvetiger_arm_joint1_R.translateX" 
		1 93 "FKExtratiger_arm_joint1_R.scaleZ" 0 143 "FKExtratiger_arm_joint1_R.scaleY" 
		0 144 "FKExtratiger_arm_joint1_R.scaleX" 0 145 "FKExtratiger_arm_joint1_R.rotateZ" 
		2 205 "FKExtratiger_arm_joint1_R.rotateY" 2 206 "FKExtratiger_arm_joint1_R.rotateX" 
		2 207 "FKExtratiger_arm_joint1_R.translateZ" 1 94 "FKExtratiger_arm_joint1_R.translateY" 
		1 95 "FKExtratiger_arm_joint1_R.translateX" 1 96 "FKCurveleft_arm_joint1_joint1_R.scaleZ" 
		0 146 "FKCurveleft_arm_joint1_joint1_R.scaleY" 0 147 "FKCurveleft_arm_joint1_joint1_R.scaleX" 
		0 148 "FKCurveleft_arm_joint1_joint1_R.rotateZ" 2 208 "FKCurveleft_arm_joint1_joint1_R.rotateY" 
		2 209 "FKCurveleft_arm_joint1_joint1_R.rotateX" 2 210 "FKCurveleft_arm_joint1_joint1_R.translateZ" 
		1 97 "FKCurveleft_arm_joint1_joint1_R.translateY" 1 98 "FKCurveleft_arm_joint1_joint1_R.translateX" 
		1 99 "FKExtraleft_arm_joint1_joint1_R.scaleZ" 0 149 "FKExtraleft_arm_joint1_joint1_R.scaleY" 
		0 150 "FKExtraleft_arm_joint1_joint1_R.scaleX" 0 151 "FKExtraleft_arm_joint1_joint1_R.rotateZ" 
		2 211 "FKExtraleft_arm_joint1_joint1_R.rotateY" 2 212 "FKExtraleft_arm_joint1_joint1_R.rotateX" 
		2 213 "FKExtraleft_arm_joint1_joint1_R.translateZ" 1 100 "FKExtraleft_arm_joint1_joint1_R.translateY" 
		1 101 "FKExtraleft_arm_joint1_joint1_R.translateX" 1 102 "FKCurvehead_joint1_M.scaleZ" 
		0 152 "FKCurvehead_joint1_M.scaleY" 0 153 "FKCurvehead_joint1_M.scaleX" 
		0 154 "FKCurvehead_joint1_M.rotateZ" 2 214 "FKCurvehead_joint1_M.rotateY" 
		2 215 "FKCurvehead_joint1_M.rotateX" 2 216 "FKExtrahead_joint1_M.rotateZ" 
		2 217 "FKExtrahead_joint1_M.rotateY" 2 218 "FKExtrahead_joint1_M.rotateX" 
		2 219 "FKCurveneck_joint1_M.scaleZ" 0 155 "FKCurveneck_joint1_M.scaleY" 
		0 156 "FKCurveneck_joint1_M.scaleX" 0 157 "FKCurveneck_joint1_M.rotateZ" 
		2 220 "FKCurveneck_joint1_M.rotateY" 2 221 "FKCurveneck_joint1_M.rotateX" 
		2 222 "FKExtraneck_joint1_M.rotateZ" 2 223 "FKExtraneck_joint1_M.rotateY" 
		2 224 "FKExtraneck_joint1_M.rotateX" 2 225 "FKCurveshoulders_joint1_M.scaleZ" 
		0 158 "FKCurveshoulders_joint1_M.scaleY" 0 159 "FKCurveshoulders_joint1_M.scaleX" 
		0 160 "FKCurveshoulders_joint1_M.rotateZ" 2 226 "FKCurveshoulders_joint1_M.rotateY" 
		2 227 "FKCurveshoulders_joint1_M.rotateX" 2 228 "FKExtrashoulders_joint1_M.rotateZ" 
		2 229 "FKExtrashoulders_joint1_M.rotateY" 2 230 "FKExtrashoulders_joint1_M.rotateX" 
		2 231 "FKCurveright_shoulder_joint1_R.scaleZ" 0 161 "FKCurveright_shoulder_joint1_R.scaleY" 
		0 162 "FKCurveright_shoulder_joint1_R.scaleX" 0 163 "FKCurveright_shoulder_joint1_R.rotateZ" 
		2 232 "FKCurveright_shoulder_joint1_R.rotateY" 2 233 "FKCurveright_shoulder_joint1_R.rotateX" 
		2 234 "FKExtraright_shoulder_joint1_R.rotateZ" 2 235 "FKExtraright_shoulder_joint1_R.rotateY" 
		2 236 "FKExtraright_shoulder_joint1_R.rotateX" 2 237 "FKCurveright_elbow_1_joint1_R.scaleZ" 
		0 164 "FKCurveright_elbow_1_joint1_R.scaleY" 0 165 "FKCurveright_elbow_1_joint1_R.scaleX" 
		0 166 "FKCurveright_elbow_1_joint1_R.rotateY" 2 238 "FKExtraright_elbow_1_joint1_R.rotateZ" 
		2 239 "FKExtraright_elbow_1_joint1_R.rotateY" 2 240 "FKExtraright_elbow_1_joint1_R.rotateX" 
		2 241 "FKCurveright_elbow_2_joint1_R.scaleZ" 0 167 "FKCurveright_elbow_2_joint1_R.scaleY" 
		0 168 "FKCurveright_elbow_2_joint1_R.scaleX" 0 169 "FKCurveright_elbow_2_joint1_R.rotateY" 
		2 242 "FKExtraright_elbow_2_joint1_R.rotateZ" 2 243 "FKExtraright_elbow_2_joint1_R.rotateY" 
		2 244 "FKExtraright_elbow_2_joint1_R.rotateX" 2 245 "FKCurveright_thumb_1_joint1_R.scaleZ" 
		0 170 "FKCurveright_thumb_1_joint1_R.scaleY" 0 171 "FKCurveright_thumb_1_joint1_R.scaleX" 
		0 172 "FKCurveright_thumb_1_joint1_R.rotateZ" 2 246 "FKCurveright_thumb_1_joint1_R.rotateY" 
		2 247 "FKCurveright_thumb_1_joint1_R.rotateX" 2 248 "FKExtraright_thumb_1_joint1_R.rotateZ" 
		2 249 "FKExtraright_thumb_1_joint1_R.rotateY" 2 250 "FKExtraright_thumb_1_joint1_R.rotateX" 
		2 251 "FKCurveright_thumb_joint1_R.scaleZ" 0 173 "FKCurveright_thumb_joint1_R.scaleY" 
		0 174 "FKCurveright_thumb_joint1_R.scaleX" 0 175 "FKCurveright_thumb_joint1_R.rotateZ" 
		2 252 "FKCurveright_thumb_joint1_R.rotateY" 2 253 "FKCurveright_thumb_joint1_R.rotateX" 
		2 254 "FKExtraright_thumb_joint1_R.rotateZ" 2 255 "FKExtraright_thumb_joint1_R.rotateY" 
		2 256 "FKExtraright_thumb_joint1_R.rotateX" 2 257 "FKCurveright_fingrs_2_joint1_R.scaleZ" 
		0 176 "FKCurveright_fingrs_2_joint1_R.scaleY" 0 177 "FKCurveright_fingrs_2_joint1_R.scaleX" 
		0 178 "FKCurveright_fingrs_2_joint1_R.rotateZ" 2 258 "FKCurveright_fingrs_2_joint1_R.rotateY" 
		2 259 "FKCurveright_fingrs_2_joint1_R.rotateX" 2 260 "FKExtraright_fingrs_2_joint1_R.rotateZ" 
		2 261 "FKExtraright_fingrs_2_joint1_R.rotateY" 2 262 "FKExtraright_fingrs_2_joint1_R.rotateX" 
		2 263 "FKCurveright_fingrs_1_joint1_R.scaleZ" 0 179 "FKCurveright_fingrs_1_joint1_R.scaleY" 
		0 180 "FKCurveright_fingrs_1_joint1_R.scaleX" 0 181 "FKCurveright_fingrs_1_joint1_R.rotateZ" 
		2 264 "FKCurveright_fingrs_1_joint1_R.rotateY" 2 265 "FKCurveright_fingrs_1_joint1_R.rotateX" 
		2 266 "FKExtraright_fingrs_1_joint1_R.rotateZ" 2 267 "FKExtraright_fingrs_1_joint1_R.rotateY" 
		2 268 "FKExtraright_fingrs_1_joint1_R.rotateX" 2 269 "FKCurveright_fist_joint1_R.scaleZ" 
		0 182 "FKCurveright_fist_joint1_R.scaleY" 0 183 "FKCurveright_fist_joint1_R.scaleX" 
		0 184 "FKCurveright_fist_joint1_R.rotateZ" 2 270 "FKCurveright_fist_joint1_R.rotateY" 
		2 271 "FKCurveright_fist_joint1_R.rotateX" 2 272 "FKExtraright_fist_joint1_R.rotateZ" 
		2 273 "FKExtraright_fist_joint1_R.rotateY" 2 274 "FKExtraright_fist_joint1_R.rotateX" 
		2 275 "All.scaleZ" 0 185 "All.scaleY" 0 186 "All.scaleX" 
		0 187 "All.rotateZ" 2 276 "All.rotateY" 2 277 "All.rotateX" 
		2 278 "All.translateZ" 1 103 "All.translateY" 1 104 "All.translateX" 
		1 105 "All.visibility" 0 188  ;
	setAttr ".cd[0].cim" -type "Int32Array" 571 0 1 2 3 4
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
		 569 570 ;
createNode animClip -n "clip00Source";
	setAttr ".ihi" 0;
	setAttr -s 9 ".ac[561:569]" no no no yes yes yes no no no;
	setAttr ".se" 1;
	setAttr ".ci" no;
createNode animCurveTU -n "warrior_All_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 2.3;
createNode animCurveTU -n "warrior_All_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 2.3;
createNode animCurveTU -n "warrior_All_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 2.3;
createNode animCurveTA -n "warrior_All_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "warrior_All_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "warrior_All_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "warrior_All_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "warrior_All_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "warrior_All_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode lightLinker -n "lightLinker1";
	setAttr -s 4 ".lnk";
	setAttr -s 4 ".slnk";
select -ne :time1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 0;
select -ne :renderPartition;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 4 ".st";
select -ne :renderGlobalsList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
select -ne :defaultShaderList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 3 ".s";
select -ne :postProcessList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
	setAttr -s 3 ".u";
select -ne :lightList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
select -ne :defaultTextureList1;
	setAttr -s 2 ".tx";
select -ne :lambert1;
	setAttr ".miic" -type "float3" 3.1415927 3.1415927 3.1415927 ;
select -ne :initialShadingGroup;
	addAttr -ci true -uac -sn "frint" -ln "frInteriorShader" -bt "UNKN" -at "float3" 
		-nc 3;
	addAttr -ci true -sn "frintr" -ln "frInteriorShaderR" -bt "UNKN" -at "float" -p "frInteriorShader";
	addAttr -ci true -sn "frintg" -ln "frInteriorShaderG" -bt "UNKN" -at "float" -p "frInteriorShader";
	addAttr -ci true -sn "frintb" -ln "frInteriorShaderB" -bt "UNKN" -at "float" -p "frInteriorShader";
	addAttr -ci true -uac -sn "frext" -ln "frExteriorShader" -bt "UNKN" -at "float3" 
		-nc 3;
	addAttr -ci true -sn "frextr" -ln "frExteriorShaderR" -bt "UNKN" -at "float" -p "frExteriorShader";
	addAttr -ci true -sn "frextg" -ln "frExteriorShaderG" -bt "UNKN" -at "float" -p "frExteriorShader";
	addAttr -ci true -sn "frextb" -ln "frExteriorShaderB" -bt "UNKN" -at "float" -p "frExteriorShader";
	addAttr -ci true -uac -sn "frrad" -ln "frRadianceShader" -bt "UNKN" -at "float3" 
		-nc 3;
	addAttr -ci true -sn "frradr" -ln "frRadianceShaderR" -bt "UNKN" -at "float" -p "frRadianceShader";
	addAttr -ci true -sn "frradg" -ln "frRadianceShaderG" -bt "UNKN" -at "float" -p "frRadianceShader";
	addAttr -ci true -sn "frradb" -ln "frRadianceShaderB" -bt "UNKN" -at "float" -p "frRadianceShader";
	addAttr -ci true -uac -sn "frdp" -ln "frDiffuse" -bt "UNKN" -at "float3" -nc 3;
	addAttr -ci true -sn "frdpr" -ln "frDiffuseR" -bt "UNKN" -at "float" -p "frDiffuse";
	addAttr -ci true -sn "frdpg" -ln "frDiffuseG" -bt "UNKN" -at "float" -p "frDiffuse";
	addAttr -ci true -sn "frdpb" -ln "frDiffuseB" -bt "UNKN" -at "float" -p "frDiffuse";
	addAttr -ci true -uac -sn "frdnp" -ln "frDiffuseNS" -bt "UNKN" -at "float3" -nc 
		3;
	addAttr -ci true -sn "frdnpr" -ln "frDiffuseNSR" -bt "UNKN" -at "float" -p "frDiffuseNS";
	addAttr -ci true -sn "frdnpg" -ln "frDiffuseNSG" -bt "UNKN" -at "float" -p "frDiffuseNS";
	addAttr -ci true -sn "frdnpb" -ln "frDiffuseNSB" -bt "UNKN" -at "float" -p "frDiffuseNS";
	addAttr -ci true -uac -sn "frspp" -ln "frSpecular" -bt "UNKN" -at "float3" -nc 3;
	addAttr -ci true -sn "frsppr" -ln "frSpecularR" -bt "UNKN" -at "float" -p "frSpecular";
	addAttr -ci true -sn "frsppg" -ln "frSpecularG" -bt "UNKN" -at "float" -p "frSpecular";
	addAttr -ci true -sn "frsppb" -ln "frSpecularB" -bt "UNKN" -at "float" -p "frSpecular";
	addAttr -ci true -uac -sn "frspnp" -ln "frSpecularNS" -bt "UNKN" -at "float3" -nc 
		3;
	addAttr -ci true -sn "frspnpr" -ln "frSpecularNSR" -bt "UNKN" -at "float" -p "frSpecularNS";
	addAttr -ci true -sn "frspnpg" -ln "frSpecularNSG" -bt "UNKN" -at "float" -p "frSpecularNS";
	addAttr -ci true -sn "frspnpb" -ln "frSpecularNSB" -bt "UNKN" -at "float" -p "frSpecularNS";
	addAttr -ci true -uac -sn "frambp" -ln "frAmbient" -bt "UNKN" -at "float3" -nc 3;
	addAttr -ci true -sn "frambpr" -ln "frAmbientR" -bt "UNKN" -at "float" -p "frAmbient";
	addAttr -ci true -sn "frambpg" -ln "frAmbientG" -bt "UNKN" -at "float" -p "frAmbient";
	addAttr -ci true -sn "frambpb" -ln "frAmbientB" -bt "UNKN" -at "float" -p "frAmbient";
	addAttr -ci true -uac -sn "frip" -ln "frIncandescence" -bt "UNKN" -at "float3" -nc 
		3;
	addAttr -ci true -sn "fripr" -ln "frIncandescenceR" -bt "UNKN" -at "float" -p "frIncandescence";
	addAttr -ci true -sn "fripg" -ln "frIncandescenceG" -bt "UNKN" -at "float" -p "frIncandescence";
	addAttr -ci true -sn "fripb" -ln "frIncandescenceB" -bt "UNKN" -at "float" -p "frIncandescence";
	addAttr -ci true -uac -sn "frgip" -ln "frGI" -bt "UNKN" -at "float3" -nc 3;
	addAttr -ci true -sn "frgipr" -ln "frGIR" -bt "UNKN" -at "float" -p "frGI";
	addAttr -ci true -sn "frgipg" -ln "frGIG" -bt "UNKN" -at "float" -p "frGI";
	addAttr -ci true -sn "frgipb" -ln "frGIB" -bt "UNKN" -at "float" -p "frGI";
	addAttr -ci true -uac -sn "frcsp" -ln "frCaustics" -bt "UNKN" -at "float3" -nc 3;
	addAttr -ci true -sn "frcspr" -ln "frCausticsR" -bt "UNKN" -at "float" -p "frCaustics";
	addAttr -ci true -sn "frcspg" -ln "frCausticsG" -bt "UNKN" -at "float" -p "frCaustics";
	addAttr -ci true -sn "frcspb" -ln "frCausticsB" -bt "UNKN" -at "float" -p "frCaustics";
	addAttr -ci true -uac -sn "frsssp" -ln "frSSS" -bt "UNKN" -at "float3" -nc 3;
	addAttr -ci true -sn "frssspr" -ln "frSSSR" -bt "UNKN" -at "float" -p "frSSS";
	addAttr -ci true -sn "frssspg" -ln "frSSSG" -bt "UNKN" -at "float" -p "frSSS";
	addAttr -ci true -sn "frssspb" -ln "frSSSB" -bt "UNKN" -at "float" -p "frSSS";
	addAttr -ci true -uac -sn "frrflp" -ln "frReflection" -bt "UNKN" -at "float3" -nc 
		3;
	addAttr -ci true -sn "frrflpr" -ln "frReflectionR" -bt "UNKN" -at "float" -p "frReflection";
	addAttr -ci true -sn "frrflpg" -ln "frReflectionG" -bt "UNKN" -at "float" -p "frReflection";
	addAttr -ci true -sn "frrflpb" -ln "frReflectionB" -bt "UNKN" -at "float" -p "frReflection";
	addAttr -ci true -uac -sn "frrfrp" -ln "frRefraction" -bt "UNKN" -at "float3" -nc 
		3;
	addAttr -ci true -sn "frrfrpr" -ln "frRefractionR" -bt "UNKN" -at "float" -p "frRefraction";
	addAttr -ci true -sn "frrfrpg" -ln "frRefractionG" -bt "UNKN" -at "float" -p "frRefraction";
	addAttr -ci true -sn "frrfrpb" -ln "frRefractionB" -bt "UNKN" -at "float" -p "frRefraction";
	addAttr -ci true -sn "frnp" -ln "frNormal" -bt "UNKN" -at "float3" -nc 3;
	addAttr -ci true -sn "frnpx" -ln "frNormalX" -bt "UNKN" -at "float" -p "frNormal";
	addAttr -ci true -sn "frnpy" -ln "frNormalY" -bt "UNKN" -at "float" -p "frNormal";
	addAttr -ci true -sn "frnpz" -ln "frNormalZ" -bt "UNKN" -at "float" -p "frNormal";
	addAttr -ci true -sn "ilrPhotonShader" -ln "ilrPhotonShader" -dt "float3";
	addAttr -ci true -sn "ilrSurfaceShaderOverride" -ln "ilrSurfaceShaderOverride" -dt "float3";
	setAttr -k on ".cch";
	setAttr -av -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -k on ".mwc";
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
	addAttr -ci true -uac -sn "frint" -ln "frInteriorShader" -bt "UNKN" -at "float3" 
		-nc 3;
	addAttr -ci true -sn "frintr" -ln "frInteriorShaderR" -bt "UNKN" -at "float" -p "frInteriorShader";
	addAttr -ci true -sn "frintg" -ln "frInteriorShaderG" -bt "UNKN" -at "float" -p "frInteriorShader";
	addAttr -ci true -sn "frintb" -ln "frInteriorShaderB" -bt "UNKN" -at "float" -p "frInteriorShader";
	addAttr -ci true -uac -sn "frext" -ln "frExteriorShader" -bt "UNKN" -at "float3" 
		-nc 3;
	addAttr -ci true -sn "frextr" -ln "frExteriorShaderR" -bt "UNKN" -at "float" -p "frExteriorShader";
	addAttr -ci true -sn "frextg" -ln "frExteriorShaderG" -bt "UNKN" -at "float" -p "frExteriorShader";
	addAttr -ci true -sn "frextb" -ln "frExteriorShaderB" -bt "UNKN" -at "float" -p "frExteriorShader";
	addAttr -ci true -uac -sn "frrad" -ln "frRadianceShader" -bt "UNKN" -at "float3" 
		-nc 3;
	addAttr -ci true -sn "frradr" -ln "frRadianceShaderR" -bt "UNKN" -at "float" -p "frRadianceShader";
	addAttr -ci true -sn "frradg" -ln "frRadianceShaderG" -bt "UNKN" -at "float" -p "frRadianceShader";
	addAttr -ci true -sn "frradb" -ln "frRadianceShaderB" -bt "UNKN" -at "float" -p "frRadianceShader";
	addAttr -ci true -uac -sn "frdp" -ln "frDiffuse" -bt "UNKN" -at "float3" -nc 3;
	addAttr -ci true -sn "frdpr" -ln "frDiffuseR" -bt "UNKN" -at "float" -p "frDiffuse";
	addAttr -ci true -sn "frdpg" -ln "frDiffuseG" -bt "UNKN" -at "float" -p "frDiffuse";
	addAttr -ci true -sn "frdpb" -ln "frDiffuseB" -bt "UNKN" -at "float" -p "frDiffuse";
	addAttr -ci true -uac -sn "frdnp" -ln "frDiffuseNS" -bt "UNKN" -at "float3" -nc 
		3;
	addAttr -ci true -sn "frdnpr" -ln "frDiffuseNSR" -bt "UNKN" -at "float" -p "frDiffuseNS";
	addAttr -ci true -sn "frdnpg" -ln "frDiffuseNSG" -bt "UNKN" -at "float" -p "frDiffuseNS";
	addAttr -ci true -sn "frdnpb" -ln "frDiffuseNSB" -bt "UNKN" -at "float" -p "frDiffuseNS";
	addAttr -ci true -uac -sn "frspp" -ln "frSpecular" -bt "UNKN" -at "float3" -nc 3;
	addAttr -ci true -sn "frsppr" -ln "frSpecularR" -bt "UNKN" -at "float" -p "frSpecular";
	addAttr -ci true -sn "frsppg" -ln "frSpecularG" -bt "UNKN" -at "float" -p "frSpecular";
	addAttr -ci true -sn "frsppb" -ln "frSpecularB" -bt "UNKN" -at "float" -p "frSpecular";
	addAttr -ci true -uac -sn "frspnp" -ln "frSpecularNS" -bt "UNKN" -at "float3" -nc 
		3;
	addAttr -ci true -sn "frspnpr" -ln "frSpecularNSR" -bt "UNKN" -at "float" -p "frSpecularNS";
	addAttr -ci true -sn "frspnpg" -ln "frSpecularNSG" -bt "UNKN" -at "float" -p "frSpecularNS";
	addAttr -ci true -sn "frspnpb" -ln "frSpecularNSB" -bt "UNKN" -at "float" -p "frSpecularNS";
	addAttr -ci true -uac -sn "frambp" -ln "frAmbient" -bt "UNKN" -at "float3" -nc 3;
	addAttr -ci true -sn "frambpr" -ln "frAmbientR" -bt "UNKN" -at "float" -p "frAmbient";
	addAttr -ci true -sn "frambpg" -ln "frAmbientG" -bt "UNKN" -at "float" -p "frAmbient";
	addAttr -ci true -sn "frambpb" -ln "frAmbientB" -bt "UNKN" -at "float" -p "frAmbient";
	addAttr -ci true -uac -sn "frip" -ln "frIncandescence" -bt "UNKN" -at "float3" -nc 
		3;
	addAttr -ci true -sn "fripr" -ln "frIncandescenceR" -bt "UNKN" -at "float" -p "frIncandescence";
	addAttr -ci true -sn "fripg" -ln "frIncandescenceG" -bt "UNKN" -at "float" -p "frIncandescence";
	addAttr -ci true -sn "fripb" -ln "frIncandescenceB" -bt "UNKN" -at "float" -p "frIncandescence";
	addAttr -ci true -uac -sn "frgip" -ln "frGI" -bt "UNKN" -at "float3" -nc 3;
	addAttr -ci true -sn "frgipr" -ln "frGIR" -bt "UNKN" -at "float" -p "frGI";
	addAttr -ci true -sn "frgipg" -ln "frGIG" -bt "UNKN" -at "float" -p "frGI";
	addAttr -ci true -sn "frgipb" -ln "frGIB" -bt "UNKN" -at "float" -p "frGI";
	addAttr -ci true -uac -sn "frcsp" -ln "frCaustics" -bt "UNKN" -at "float3" -nc 3;
	addAttr -ci true -sn "frcspr" -ln "frCausticsR" -bt "UNKN" -at "float" -p "frCaustics";
	addAttr -ci true -sn "frcspg" -ln "frCausticsG" -bt "UNKN" -at "float" -p "frCaustics";
	addAttr -ci true -sn "frcspb" -ln "frCausticsB" -bt "UNKN" -at "float" -p "frCaustics";
	addAttr -ci true -uac -sn "frsssp" -ln "frSSS" -bt "UNKN" -at "float3" -nc 3;
	addAttr -ci true -sn "frssspr" -ln "frSSSR" -bt "UNKN" -at "float" -p "frSSS";
	addAttr -ci true -sn "frssspg" -ln "frSSSG" -bt "UNKN" -at "float" -p "frSSS";
	addAttr -ci true -sn "frssspb" -ln "frSSSB" -bt "UNKN" -at "float" -p "frSSS";
	addAttr -ci true -uac -sn "frrflp" -ln "frReflection" -bt "UNKN" -at "float3" -nc 
		3;
	addAttr -ci true -sn "frrflpr" -ln "frReflectionR" -bt "UNKN" -at "float" -p "frReflection";
	addAttr -ci true -sn "frrflpg" -ln "frReflectionG" -bt "UNKN" -at "float" -p "frReflection";
	addAttr -ci true -sn "frrflpb" -ln "frReflectionB" -bt "UNKN" -at "float" -p "frReflection";
	addAttr -ci true -uac -sn "frrfrp" -ln "frRefraction" -bt "UNKN" -at "float3" -nc 
		3;
	addAttr -ci true -sn "frrfrpr" -ln "frRefractionR" -bt "UNKN" -at "float" -p "frRefraction";
	addAttr -ci true -sn "frrfrpg" -ln "frRefractionG" -bt "UNKN" -at "float" -p "frRefraction";
	addAttr -ci true -sn "frrfrpb" -ln "frRefractionB" -bt "UNKN" -at "float" -p "frRefraction";
	addAttr -ci true -sn "frnp" -ln "frNormal" -bt "UNKN" -at "float3" -nc 3;
	addAttr -ci true -sn "frnpx" -ln "frNormalX" -bt "UNKN" -at "float" -p "frNormal";
	addAttr -ci true -sn "frnpy" -ln "frNormalY" -bt "UNKN" -at "float" -p "frNormal";
	addAttr -ci true -sn "frnpz" -ln "frNormalZ" -bt "UNKN" -at "float" -p "frNormal";
	addAttr -ci true -sn "ilrPhotonShader" -ln "ilrPhotonShader" -dt "float3";
	addAttr -ci true -sn "ilrSurfaceShaderOverride" -ln "ilrSurfaceShaderOverride" -dt "float3";
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -k on ".mwc";
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
	setAttr -k on ".bfs";
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
	setAttr -s 4 ".sol";
select -ne :hyperGraphLayout;
	setAttr -s 34 ".hyp";
	setAttr ".hyp[34].isc" yes;
	setAttr ".hyp[34].isf" no;
	setAttr ".hyp[44].isc" yes;
	setAttr ".hyp[44].isf" no;
	setAttr ".hyp[45].isc" yes;
	setAttr ".hyp[45].isf" no;
	setAttr ".hyp[67].isc" yes;
	setAttr ".hyp[67].isf" no;
	setAttr ".hyp[68].isc" yes;
	setAttr ".hyp[68].isf" no;
	setAttr ".hyp[75].isc" yes;
	setAttr ".hyp[75].isf" no;
	setAttr ".hyp[76].isc" yes;
	setAttr ".hyp[76].isf" no;
	setAttr ".hyp[84].isc" yes;
	setAttr ".hyp[84].isf" no;
	setAttr ".hyp[95].isc" yes;
	setAttr ".hyp[95].isf" no;
	setAttr ".hyp[96].isc" yes;
	setAttr ".hyp[96].isf" no;
	setAttr ".hyp[97].isc" yes;
	setAttr ".hyp[97].isf" no;
	setAttr ".hyp[98].isc" yes;
	setAttr ".hyp[98].isf" no;
	setAttr ".hyp[99].isc" yes;
	setAttr ".hyp[99].isf" no;
	setAttr ".hyp[100].isc" yes;
	setAttr ".hyp[100].isf" no;
	setAttr ".hyp[101].isc" yes;
	setAttr ".hyp[101].isf" no;
	setAttr ".hyp[102].isc" yes;
	setAttr ".hyp[102].isf" no;
	setAttr ".hyp[103].isc" yes;
	setAttr ".hyp[103].isf" no;
	setAttr ".hyp[104].isc" yes;
	setAttr ".hyp[104].isf" no;
	setAttr ".hyp[105].isc" yes;
	setAttr ".hyp[105].isf" no;
	setAttr ".hyp[106].isc" yes;
	setAttr ".hyp[106].isf" no;
	setAttr ".hyp[107].isc" yes;
	setAttr ".hyp[107].isf" no;
	setAttr ".hyp[108].isc" yes;
	setAttr ".hyp[108].isf" no;
	setAttr ".hyp[109].isc" yes;
	setAttr ".hyp[109].isf" no;
	setAttr ".hyp[110].isc" yes;
	setAttr ".hyp[110].isf" no;
	setAttr ".hyp[111].isc" yes;
	setAttr ".hyp[111].isf" no;
	setAttr ".hyp[112].isc" yes;
	setAttr ".hyp[112].isf" no;
	setAttr ".hyp[113].isc" yes;
	setAttr ".hyp[113].isf" no;
	setAttr ".hyp[114].isc" yes;
	setAttr ".hyp[114].isf" no;
	setAttr ".hyp[115].isc" yes;
	setAttr ".hyp[115].isf" no;
	setAttr ".hyp[116].isc" yes;
	setAttr ".hyp[116].isf" no;
	setAttr ".hyp[117].isc" yes;
	setAttr ".hyp[117].isf" no;
	setAttr ".hyp[118].isc" yes;
	setAttr ".hyp[118].isf" no;
	setAttr ".hyp[119].isc" yes;
	setAttr ".hyp[119].isf" no;
	setAttr ".hyp[121].isc" yes;
	setAttr ".hyp[121].isf" no;
connectAttr "clip00Source.cl" "clipLibrary1.sc[0]";
connectAttr "warrior_All_scaleZ.a" "clipLibrary1.cel[0].cev[561].cevr";
connectAttr "warrior_All_scaleY.a" "clipLibrary1.cel[0].cev[562].cevr";
connectAttr "warrior_All_scaleX.a" "clipLibrary1.cel[0].cev[563].cevr";
connectAttr "warrior_All_rotateZ.a" "clipLibrary1.cel[0].cev[564].cevr";
connectAttr "warrior_All_rotateY.a" "clipLibrary1.cel[0].cev[565].cevr";
connectAttr "warrior_All_rotateX.a" "clipLibrary1.cel[0].cev[566].cevr";
connectAttr "warrior_All_translateZ.a" "clipLibrary1.cel[0].cev[567].cevr";
connectAttr "warrior_All_translateY.a" "clipLibrary1.cel[0].cev[568].cevr";
connectAttr "warrior_All_translateX.a" "clipLibrary1.cel[0].cev[569].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[2].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[2].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[1].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[2].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[2].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of Idle.ma
