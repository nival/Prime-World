//Maya ASCII 2008 scene
//Name: attackSpecialA.ma
//Last modified: Thu, Nov 12, 2009 02:33:24 PM
//Codeset: 1251
requires maya "2008";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Complete 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200802250025-718075";
fileInfo "osv" "Microsoft Windows XP Service Pack 3 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 325 ".cel[0].cev";
	setAttr ".cd[0].cm" -type "characterMapping" 325 "Ratcatcher_rt_upArm_fk_ctrl_Align.align" 
		0 1 "Ratcatcher_rt_upArm_fk_ctrl_Align.rotateZ" 2 1 "Ratcatcher_rt_upArm_fk_ctrl_Align.rotateY" 
		2 2 "Ratcatcher_rt_upArm_fk_ctrl_Align.rotateX" 2 3 "Ratcatcher_rt_hand_ctrl.fkVis" 
		0 2 "Ratcatcher_rt_hand_ctrl.ikVis" 0 3 "Ratcatcher_rt_hand_ctrl.ikFkBlend" 
		0 4 "Ratcatcher_rt_hand_ctrl.fkAlign" 0 5 "Ratcatcher_rt_hand_ctrl.rotateZ" 
		2 4 "Ratcatcher_rt_hand_ctrl.rotateY" 2 5 "Ratcatcher_rt_hand_ctrl.rotateX" 
		2 6 "Ratcatcher_rt_elbow_pv_ctrl.rtArmIkCtrl" 0 6 "Ratcatcher_rt_elbow_pv_ctrl.snapElbow" 
		0 7 "Ratcatcher_rt_elbow_pv_ctrl.translateZ" 1 1 "Ratcatcher_rt_elbow_pv_ctrl.translateY" 
		1 2 "Ratcatcher_rt_elbow_pv_ctrl.translateX" 1 3 "Ratcatcher_rt_elbow_fk_ctrl.rotateZ" 
		2 7 "Ratcatcher_rt_elbow_fk_ctrl.rotateY" 2 8 "Ratcatcher_rt_elbow_fk_ctrl.rotateX" 
		2 9 "Ratcatcher_rt_clavicle_fk_ctrl.rotateZ" 2 10 "Ratcatcher_rt_clavicle_fk_ctrl.rotateY" 
		2 11 "Ratcatcher_rt_arm_ik_ctrl.maxStretch" 0 8 "Ratcatcher_rt_arm_ik_ctrl.stretchyArm" 
		0 9 "Ratcatcher_rt_arm_ik_ctrl.pvControl" 0 10 "Ratcatcher_rt_arm_ik_ctrl.armTwist" 
		0 11 "Ratcatcher_rt_arm_ik_ctrl.rotateZ" 2 12 "Ratcatcher_rt_arm_ik_ctrl.rotateY" 
		2 13 "Ratcatcher_rt_arm_ik_ctrl.rotateX" 2 14 "Ratcatcher_rt_arm_ik_ctrl.translateZ" 
		1 4 "Ratcatcher_rt_arm_ik_ctrl.translateY" 1 5 "Ratcatcher_rt_arm_ik_ctrl.translateX" 
		1 6 "Ratcatcher_lf_upArm_fk_ctrl.align" 0 12 "Ratcatcher_lf_upArm_fk_ctrl.rotateZ" 
		2 15 "Ratcatcher_lf_upArm_fk_ctrl.rotateY" 2 16 "Ratcatcher_lf_upArm_fk_ctrl.rotateX" 
		2 17 "Ratcatcher_lf_hand_ctrl.fkVis" 0 13 "Ratcatcher_lf_hand_ctrl.ikVis" 
		0 14 "Ratcatcher_lf_hand_ctrl.ikFkBlend" 0 15 "Ratcatcher_lf_hand_ctrl.fkAlign" 
		0 16 "Ratcatcher_lf_hand_ctrl.rotateZ" 2 18 "Ratcatcher_lf_hand_ctrl.rotateY" 
		2 19 "Ratcatcher_lf_hand_ctrl.rotateX" 2 20 "Ratcatcher_lf_elbow_pv_ctrl.lfArmIkCtrl" 
		0 17 "Ratcatcher_lf_elbow_pv_ctrl.snapElbow" 0 18 "Ratcatcher_lf_elbow_pv_ctrl.translateZ" 
		1 7 "Ratcatcher_lf_elbow_pv_ctrl.translateY" 1 8 "Ratcatcher_lf_elbow_pv_ctrl.translateX" 
		1 9 "Ratcatcher_lf_elbow_fk_ctrl.rotateZ" 2 21 "Ratcatcher_lf_elbow_fk_ctrl.rotateY" 
		2 22 "Ratcatcher_lf_elbow_fk_ctrl.rotateX" 2 23 "Ratcatcher_lf_clavicle_fk_ctrl.rotateZ" 
		2 24 "Ratcatcher_lf_clavicle_fk_ctrl.rotateY" 2 25 "Ratcatcher_lf_arm_ik_ctrl.Follow" 
		0 19 "Ratcatcher_lf_arm_ik_ctrl.maxStretch" 0 20 "Ratcatcher_lf_arm_ik_ctrl.stretchyArm" 
		0 21 "Ratcatcher_lf_arm_ik_ctrl.pvControl" 0 22 "Ratcatcher_lf_arm_ik_ctrl.armTwist" 
		0 23 "Ratcatcher_lf_arm_ik_ctrl.rotateZ" 2 26 "Ratcatcher_lf_arm_ik_ctrl.rotateY" 
		2 27 "Ratcatcher_lf_arm_ik_ctrl.rotateX" 2 28 "Ratcatcher_lf_arm_ik_ctrl.translateZ" 
		1 10 "Ratcatcher_lf_arm_ik_ctrl.translateY" 1 11 "Ratcatcher_lf_arm_ik_ctrl.translateX" 
		1 12 "UPPER_TORSO_CONTROL.Free_Orient" 0 24 "UPPER_TORSO_CONTROL.rotateZ" 
		2 29 "UPPER_TORSO_CONTROL.rotateY" 2 30 "UPPER_TORSO_CONTROL.rotateX" 
		2 31 "Ratcatcher_rf_thumb_b_jnt_CONTROL.Free_Orient" 0 25 "Ratcatcher_rf_thumb_b_jnt_CONTROL.rotateZ" 
		2 32 "Ratcatcher_rf_thumb_b_jnt_CONTROL.rotateY" 2 33 "Ratcatcher_rf_thumb_b_jnt_CONTROL.rotateX" 
		2 34 "Ratcatcher_rf_thumb_a_jnt_CONTROL.rotateZ" 2 35 "Ratcatcher_rf_thumb_a_jnt_CONTROL.rotateY" 
		2 36 "Ratcatcher_rf_thumb_a_jnt_CONTROL.rotateX" 2 37 "Ratcatcher_rf_ring_b_jnt_CONTROL.Free_Orient" 
		0 26 "Ratcatcher_rf_ring_b_jnt_CONTROL.rotateZ" 2 38 "Ratcatcher_rf_ring_b_jnt_CONTROL.rotateY" 
		2 39 "Ratcatcher_rf_ring_b_jnt_CONTROL.rotateX" 2 40 "Ratcatcher_rf_ring_a_jnt_CONTROL.rotateZ" 
		2 41 "Ratcatcher_rf_ring_a_jnt_CONTROL.rotateY" 2 42 "Ratcatcher_rf_ring_a_jnt_CONTROL.rotateX" 
		2 43 "Ratcatcher_rf_pinky_b_jnt_CONTROL.Free_Orient" 0 27 "Ratcatcher_rf_pinky_b_jnt_CONTROL.rotateZ" 
		2 44 "Ratcatcher_rf_pinky_b_jnt_CONTROL.rotateY" 2 45 "Ratcatcher_rf_pinky_b_jnt_CONTROL.rotateX" 
		2 46 "Ratcatcher_rf_pinky_a_jnt_CONTROL.rotateZ" 2 47 "Ratcatcher_rf_pinky_a_jnt_CONTROL.rotateY" 
		2 48 "Ratcatcher_rf_pinky_a_jnt_CONTROL.rotateX" 2 49 "Ratcatcher_rf_middle_b_jnt_CONTROL.Free_Orient" 
		0 28 "Ratcatcher_rf_middle_b_jnt_CONTROL.rotateZ" 2 50 "Ratcatcher_rf_middle_b_jnt_CONTROL.rotateY" 
		2 51 "Ratcatcher_rf_middle_b_jnt_CONTROL.rotateX" 2 52 "Ratcatcher_rf_middle_a_jnt_CONTROL.rotateZ" 
		2 53 "Ratcatcher_rf_middle_a_jnt_CONTROL.rotateY" 2 54 "Ratcatcher_rf_middle_a_jnt_CONTROL.rotateX" 
		2 55 "Ratcatcher_rf_index_b_jnt_CONTROL.Free_Orient" 0 29 "Ratcatcher_rf_index_b_jnt_CONTROL.rotateZ" 
		2 56 "Ratcatcher_rf_index_b_jnt_CONTROL.rotateY" 2 57 "Ratcatcher_rf_index_b_jnt_CONTROL.rotateX" 
		2 58 "Ratcatcher_rf_index_a_jnt_CONTROL.rotateZ" 2 59 "Ratcatcher_rf_index_a_jnt_CONTROL.rotateY" 
		2 60 "Ratcatcher_rf_index_a_jnt_CONTROL.rotateX" 2 61 "Ratcatcher_rf_ball_jnt_CONTROL.rotateZ" 
		2 62 "Ratcatcher_rf_ball_jnt_CONTROL.rotateY" 2 63 "Ratcatcher_rf_ball_jnt_CONTROL.rotateX" 
		2 64 "Ratcatcher_lf_thumb_b_jnt_CONTROL.Free_Orient" 0 30 "Ratcatcher_lf_thumb_b_jnt_CONTROL.rotateZ" 
		2 65 "Ratcatcher_lf_thumb_b_jnt_CONTROL.rotateY" 2 66 "Ratcatcher_lf_thumb_b_jnt_CONTROL.rotateX" 
		2 67 "Ratcatcher_lf_thumb_a_jnt_CONTROL.rotateZ" 2 68 "Ratcatcher_lf_thumb_a_jnt_CONTROL.rotateY" 
		2 69 "Ratcatcher_lf_thumb_a_jnt_CONTROL.rotateX" 2 70 "Ratcatcher_lf_ring_b_jnt_CONTROL.Free_Orient" 
		0 31 "Ratcatcher_lf_ring_b_jnt_CONTROL.rotateZ" 2 71 "Ratcatcher_lf_ring_b_jnt_CONTROL.rotateY" 
		2 72 "Ratcatcher_lf_ring_b_jnt_CONTROL.rotateX" 2 73 "Ratcatcher_lf_ring_a_jnt_CONTROL.rotateZ" 
		2 74 "Ratcatcher_lf_ring_a_jnt_CONTROL.rotateY" 2 75 "Ratcatcher_lf_ring_a_jnt_CONTROL.rotateX" 
		2 76 "Ratcatcher_lf_pinky_b_jnt_CONTROL.Free_Orient" 0 32 "Ratcatcher_lf_pinky_b_jnt_CONTROL.rotateZ" 
		2 77 "Ratcatcher_lf_pinky_b_jnt_CONTROL.rotateY" 2 78 "Ratcatcher_lf_pinky_b_jnt_CONTROL.rotateX" 
		2 79 "Ratcatcher_lf_pinky_a_jnt_CONTROL.rotateZ" 2 80 "Ratcatcher_lf_pinky_a_jnt_CONTROL.rotateY" 
		2 81 "Ratcatcher_lf_pinky_a_jnt_CONTROL.rotateX" 2 82 "Ratcatcher_lf_middle_b_jnt_CONTROL.Free_Orient" 
		0 33 "Ratcatcher_lf_middle_b_jnt_CONTROL.rotateZ" 2 83 "Ratcatcher_lf_middle_b_jnt_CONTROL.rotateY" 
		2 84 "Ratcatcher_lf_middle_b_jnt_CONTROL.rotateX" 2 85 "Ratcatcher_lf_middle_a_jnt_CONTROL.rotateZ" 
		2 86 "Ratcatcher_lf_middle_a_jnt_CONTROL.rotateY" 2 87 "Ratcatcher_lf_middle_a_jnt_CONTROL.rotateX" 
		2 88 "Ratcatcher_lf_index_b_jnt_CONTROL.Free_Orient" 0 34 "Ratcatcher_lf_index_b_jnt_CONTROL.rotateZ" 
		2 89 "Ratcatcher_lf_index_b_jnt_CONTROL.rotateY" 2 90 "Ratcatcher_lf_index_b_jnt_CONTROL.rotateX" 
		2 91 "Ratcatcher_lf_index_a_jnt_CONTROL.rotateZ" 2 92 "Ratcatcher_lf_index_a_jnt_CONTROL.rotateY" 
		2 93 "Ratcatcher_lf_index_a_jnt_CONTROL.rotateX" 2 94 "Ratcatcher_lf_ball_jnt_CONTROL.rotateZ" 
		2 95 "Ratcatcher_lf_ball_jnt_CONTROL.rotateY" 2 96 "Ratcatcher_lf_ball_jnt_CONTROL.rotateX" 
		2 97 "R_IKFootControl.FKLeg_Visibility" 0 35 "R_IKFootControl.IKLeg_Visibility" 
		0 36 "R_IKFootControl.IKFK_Blend" 0 37 "R_IKFootControl.rotateZ" 
		2 98 "R_IKFootControl.rotateY" 2 99 "R_IKFootControl.rotateX" 2 
		100 "R_IKFootControl.translateZ" 1 13 "R_IKFootControl.translateY" 1 
		14 "R_IKFootControl.translateX" 1 15 "R_FK_KNEE_CONTROL.rotateZ" 2 
		101 "R_FK_KNEE_CONTROL.rotateY" 2 102 "R_FK_KNEE_CONTROL.rotateX" 2 
		103 "R_FK_FEMUR_CONTROL.Free_Orient" 0 38 "R_FK_FEMUR_CONTROL.rotateZ" 
		2 104 "R_FK_FEMUR_CONTROL.rotateY" 2 105 "R_FK_FEMUR_CONTROL.rotateX" 
		2 106 "R_FK_BALL_CONTROL.rotateZ" 2 107 "R_FK_BALL_CONTROL.rotateY" 
		2 108 "R_FK_BALL_CONTROL.rotateX" 2 109 "R_FK_ANKLE_CONTROL.rotateZ" 
		2 110 "R_FK_ANKLE_CONTROL.rotateY" 2 111 "R_FK_ANKLE_CONTROL.rotateX" 
		2 112 "NECK_CONTROL.Free_Orient" 0 39 "NECK_CONTROL.rotateZ" 2 
		113 "NECK_CONTROL.rotateY" 2 114 "NECK_CONTROL.rotateX" 2 115 "L_IKFootControl.FKLeg_Visibility" 
		0 40 "L_IKFootControl.IKLeg_Visibility" 0 41 "L_IKFootControl.IKFK_Blend" 
		0 42 "L_IKFootControl.rotateZ" 2 116 "L_IKFootControl.rotateY" 2 
		117 "L_IKFootControl.rotateX" 2 118 "L_IKFootControl.translateZ" 1 
		16 "L_IKFootControl.translateY" 1 17 "L_IKFootControl.translateX" 1 
		18 "L_FK_KNEE_CONTROL.rotateZ" 2 119 "L_FK_KNEE_CONTROL.rotateY" 2 
		120 "L_FK_KNEE_CONTROL.rotateX" 2 121 "L_FK_FEMUR_CONTROL.Free_Orient" 
		0 43 "L_FK_FEMUR_CONTROL.rotateZ" 2 122 "L_FK_FEMUR_CONTROL.rotateY" 
		2 123 "L_FK_FEMUR_CONTROL.rotateX" 2 124 "L_FK_BALL_CONTROL.rotateZ" 
		2 125 "L_FK_BALL_CONTROL.rotateY" 2 126 "L_FK_BALL_CONTROL.rotateX" 
		2 127 "L_FK_ANKLE_CONTROL.rotateZ" 2 128 "L_FK_ANKLE_CONTROL.rotateY" 
		2 129 "L_FK_ANKLE_CONTROL.rotateX" 2 130 "LOWER_TORSO_CONTROL.rotateZ" 
		2 131 "LOWER_TORSO_CONTROL.rotateY" 2 132 "LOWER_TORSO_CONTROL.rotateX" 
		2 133 "HIP_CONTROL.rotateZ" 2 134 "HIP_CONTROL.rotateY" 2 135 "HIP_CONTROL.rotateX" 
		2 136 "HEAD_CONTROL.Free_Orient" 0 44 "HEAD_CONTROL.rotateZ" 2 
		137 "HEAD_CONTROL.rotateY" 2 138 "HEAD_CONTROL.rotateX" 2 139 "CTRL_TRAP02.Free_Orient" 
		0 45 "CTRL_TRAP02.rotateZ" 2 140 "CTRL_TRAP02.rotateY" 2 141 "CTRL_TRAP02.rotateX" 
		2 142 "CTRL_TRAP01.rotateZ" 2 143 "CTRL_TRAP01.rotateY" 2 144 "CTRL_TRAP01.rotateX" 
		2 145 "CTRL_STUFF_LAT.rotateZ" 2 146 "CTRL_STUFF_LAT.rotateY" 2 
		147 "CTRL_STUFF_LAT.rotateX" 2 148 "CTRL_STUFF_LAT.translateZ" 1 
		19 "CTRL_STUFF_LAT.translateY" 1 20 "CTRL_STUFF_LAT.translateX" 1 
		21 "CTRL_STUFF.Follow" 0 46 "CTRL_STUFF.Ikfollow" 0 47 "CTRL_STUFF.rotateZ" 
		2 149 "CTRL_STUFF.rotateY" 2 150 "CTRL_STUFF.rotateX" 2 151 "CTRL_STUFF.translateZ" 
		1 22 "CTRL_STUFF.translateY" 1 23 "CTRL_STUFF.translateX" 1 
		24 "CTRL_POLEV_STUFF.translateZ" 1 25 "CTRL_POLEV_STUFF.translateY" 
		1 26 "CTRL_POLEV_STUFF.translateX" 1 27 "CTRL_JAR.rotateZ" 2 
		152 "CTRL_JAR.rotateY" 2 153 "CTRL_JAR.rotateX" 2 154 "CTRL_JAR.translateZ" 
		1 28 "CTRL_JAR.translateY" 1 29 "CTRL_JAR.translateX" 1 30 "CTRL_IK_STUFF.rotateZ" 
		2 155 "CTRL_IK_STUFF.rotateY" 2 156 "CTRL_IK_STUFF.rotateX" 2 
		157 "CTRL_IK_STUFF.translateZ" 1 31 "CTRL_IK_STUFF.translateY" 1 
		32 "CTRL_IK_STUFF.translateX" 1 33 "CTRL_FLUTE.Follow" 0 48 "CTRL_FLUTE.rotateZ" 
		2 158 "CTRL_FLUTE.rotateY" 2 159 "CTRL_FLUTE.rotateX" 2 160 "CTRL_FLUTE.translateZ" 
		1 34 "CTRL_FLUTE.translateY" 1 35 "CTRL_FLUTE.translateX" 1 
		36 "CTRL_BAG.rotateZ" 2 161 "CTRL_BAG.rotateY" 2 162 "CTRL_BAG.rotateX" 
		2 163 "CTRL_BAG.translateZ" 1 37 "CTRL_BAG.translateY" 1 38 "CTRL_BAG.translateX" 
		1 39 "CTRL_ALL.rotateZ" 2 164 "CTRL_ALL.rotateY" 2 165 "CTRL_ALL.rotateX" 
		2 166 "CTRL_ALL.translateZ" 1 40 "CTRL_ALL.translateY" 1 41 "CTRL_ALL.translateX" 
		1 42 "COG_CONTROL.rotateZ" 2 167 "COG_CONTROL.rotateY" 2 168 "COG_CONTROL.rotateX" 
		2 169 "COG_CONTROL.translateZ" 1 43 "COG_CONTROL.translateY" 1 
		44 "COG_CONTROL.translateX" 1 45 "L_Leg_Pole_Vector.Follow" 0 49 "L_Leg_Pole_Vector.Control_Radius" 
		0 50 "L_Leg_Pole_Vector.translateZ" 1 46 "L_Leg_Pole_Vector.translateY" 
		1 47 "L_Leg_Pole_Vector.translateX" 1 48 "R_Leg_Pole_Vector.Follow" 
		0 51 "R_Leg_Pole_Vector.Control_Radius" 0 52 "R_Leg_Pole_Vector.translateZ" 
		1 49 "R_Leg_Pole_Vector.translateY" 1 50 "R_Leg_Pole_Vector.translateX" 
		1 51 "CTRRL_BR_01.rotateZ" 2 170 "CTRRL_BR_01.rotateY" 2 171 "CTRRL_BR_01.rotateX" 
		2 172 "CTRRL_BR_02.rotateZ" 2 173 "CTRRL_BR_02.rotateY" 2 174 "CTRRL_BR_02.rotateX" 
		2 175 "CTRRL_BR_03.rotateZ" 2 176 "CTRRL_BR_03.rotateY" 2 177 "CTRRL_BR_03.rotateX" 
		2 178 "CTRRL_FEATHER.rotateZ" 2 179 "CTRRL_FEATHER.rotateY" 2 
		180 "CTRRL_FEATHER.rotateX" 2 181 "CTRRL_BR_04.rotateZ" 2 182 "CTRRL_BR_04.rotateY" 
		2 183 "CTRRL_BR_04.rotateX" 2 184 "CTRL_SHOULD_L.scaleZ" 0 53 "CTRL_SHOULD_L.scaleY" 
		0 54 "CTRL_SHOULD_L.scaleX" 0 55 "CTRL_SHOULD_L.rotateZ" 2 
		185 "CTRL_SHOULD_L.rotateY" 2 186 "CTRL_SHOULD_L.rotateX" 2 187 "CTRL_SHOULD_L.translateZ" 
		1 52 "CTRL_SHOULD_L.translateY" 1 53 "CTRL_SHOULD_L.translateX" 
		1 54 "CTRL_SHOULD_R.scaleZ" 0 56 "CTRL_SHOULD_R.scaleY" 0 
		57 "CTRL_SHOULD_R.scaleX" 0 58 "CTRL_SHOULD_R.rotateZ" 2 188 "CTRL_SHOULD_R.rotateY" 
		2 189 "CTRL_SHOULD_R.rotateX" 2 190 "CTRL_SHOULD_R.translateZ" 1 
		55 "CTRL_SHOULD_R.translateY" 1 56 "CTRL_SHOULD_R.translateX" 1 
		57 "CTRL_HAT.rotateZ" 2 191 "CTRL_HAT.rotateY" 2 192 "CTRL_HAT.rotateX" 
		2 193 "CTRL_HAT.translateZ" 1 58 "CTRL_HAT.translateY" 1 59 "CTRL_HAT.translateX" 
		1 60 "CTRL_TRAP01.translateZ" 1 61 "CTRL_TRAP01.translateY" 1 
		62 "CTRL_TRAP01.translateX" 1 63 "CTRL_STUFF.scaleZ" 0 59 "CTRL_STUFF.scaleY" 
		0 60 "CTRL_STUFF.scaleX" 0 61 "CTRL_STUFF_LAT.scaleZ" 0 62 "CTRL_STUFF_LAT.scaleY" 
		0 63 "CTRL_STUFF_LAT.scaleX" 0 64 "CTRL_TwistR.rotateX" 2 
		194 "CTRL_TwistL.rotateX" 2 195 "CTRL_JAR.scaleZ" 0 65 "CTRL_JAR.scaleY" 
		0 66 "CTRL_JAR.scaleX" 0 67  ;
	setAttr ".cd[0].cim" -type "Int32Array" 325 0 1 2 3 4
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
		 317 318 319 320 321 322 323 324 ;
createNode animClip -n "attackSpecialASource";
	setAttr ".ihi" 0;
	setAttr -s 325 ".ac[0:324]" yes yes yes yes yes yes yes yes yes yes yes 
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
		yes yes yes yes yes yes yes yes yes yes yes no no no yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".se" 45;
	setAttr ".ci" no;
createNode animCurveTU -n "animCurveTU483";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 1;
	setAttr -s 5 ".kot[0:4]"  3 5 5 5 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1546";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1547";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1548";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU484";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kot[0:5]"  1 5 5 5 5 5;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0 0 0 0 0;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU485";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kot[0:5]"  1 5 5 5 5 5;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0 0 0 0 0;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU486";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 4 1 6 1 10 1 26 1 44 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU487";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kot[0:5]"  1 5 5 5 5 5;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0 0 0 0 0;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1549";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1550";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1551";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU488";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 0 6 0 10 0 23 0 26 0 44 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU489";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 0 6 0 10 0 23 0 26 0 44 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL493";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0.09792605086325179 2 -0.47437476130194434 
		4 0.28724603162256657 6 -0.18470812915012169 10 -0.59001897891834254 23 -0.68816614398793652 
		26 -0.43448689751695935 27 -0.52149058164038908 30 0.15511246568776726 36 0.62967845021172675 
		41 0.51005562490872258 44 0.40930268174563;
	setAttr -s 12 ".kit[0:11]"  1 10 10 10 10 10 10 10 
		10 10 10 10;
	setAttr -s 12 ".kot[0:11]"  1 10 10 10 10 10 10 10 
		10 10 10 10;
	setAttr -s 12 ".kix[0:11]"  0.6058078408241272 0.57580578327178955 
		0.41812992095947266 0.22227796912193298 0.7475702166557312 0.96001136302947998 0.62467473745346069 
		0.22057248651981354 0.25218191742897034 0.71849983930587769 0.77083981037139893 0.70444983243942261;
	setAttr -s 12 ".kiy[0:11]"  0.79561108350753784 0.81758654117584229 
		0.90838724374771118 -0.97498339414596558 -0.66418272256851196 0.27996107935905457 
		0.78088510036468506 0.97537058591842651 0.96767979860305786 0.69552707672119141 -0.63702911138534546 
		-0.70975381135940552;
	setAttr -s 12 ".kox[0:11]"  0.60580778121948242 0.57580578327178955 
		0.41812992095947266 0.22227796912193298 0.7475702166557312 0.96001136302947998 0.62467473745346069 
		0.22057248651981354 0.25218191742897034 0.71849983930587769 0.77083981037139893 0.70444983243942261;
	setAttr -s 12 ".koy[0:11]"  0.79561102390289307 0.81758654117584229 
		0.90838724374771118 -0.97498339414596558 -0.66418272256851196 0.27996107935905457 
		0.78088510036468506 0.97537058591842651 0.96767979860305786 0.69552707672119141 -0.63702911138534546 
		-0.70975381135940552;
createNode animCurveTL -n "animCurveTL494";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -0.1314644698860612 2 -1.2212679285691728 
		4 -2.6103677238223097 6 -3.6359626599487918 10 -3.5966163906967772 23 -2.8539821476937193 
		26 -2.7806862961557766 27 -1.8009169248066383 30 -0.952538511297227 36 -0.22257430933510208 
		41 0.22378308930226121 44 0.25860394298924627;
	setAttr -s 12 ".kit[0:11]"  1 10 10 10 10 10 10 10 
		10 10 10 10;
	setAttr -s 12 ".kot[0:11]"  1 10 10 10 10 10 10 10 
		10 10 10 10;
	setAttr -s 12 ".kix[0:11]"  0.097902461886405945 0.053709592670202255 
		0.055133476853370667 1 1 0.54713475704193115 0.12561164796352386 0.072740353643894196 
		0.18672969937324524 0.29758447408676147 1 1;
	setAttr -s 12 ".kiy[0:11]"  -0.99519604444503784 -0.99855655431747437 
		-0.99847900867462158 0 0 0.83704453706741333 0.99207949638366699 0.99735093116760254 
		0.98241126537322998 0.95469552278518677 0 0;
	setAttr -s 12 ".kox[0:11]"  0.097902454435825348 0.053709592670202255 
		0.055133476853370667 1 1 0.54713475704193115 0.12561164796352386 0.072740353643894196 
		0.18672969937324524 0.29758447408676147 1 1;
	setAttr -s 12 ".koy[0:11]"  -0.99519598484039307 -0.99855655431747437 
		-0.99847900867462158 0 0 0.83704453706741333 0.99207949638366699 0.99735093116760254 
		0.98241126537322998 0.95469552278518677 0 0;
createNode animCurveTL -n "animCurveTL495";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -0.54884510804502618 2 0.31283724573734956 
		4 0.01868212539862768 6 -0.79209974732764721 10 -1.1345514868754893 23 -1.0508597246861531 
		26 -0.46666492771444112 27 0.016928554955333457 30 0.004997704680675473 36 0.1767441596624727 
		41 -0.20863333028927411 44 -0.29847095663485657;
	setAttr -s 12 ".kit[0:11]"  1 10 10 10 10 10 10 10 
		10 10 10 10;
	setAttr -s 12 ".kot[0:11]"  1 10 10 10 10 10 10 10 
		10 10 10 10;
	setAttr -s 12 ".kix[0:11]"  0.31335929036140442 0.22871021926403046 
		0.11980143934488297 0.17087477445602417 0.90964895486831665 0.62399858236312866 0.12390644103288651 
		1 1 0.86404323577880859 0.48936620354652405 0.74389451742172241;
	setAttr -s 12 ".kiy[0:11]"  -0.94963467121124268 0.97349452972412109 
		-0.99279791116714478 -0.98529273271560669 -0.41537779569625854 0.78142553567886353 
		0.99229389429092407 0 0 -0.50341761112213135 -0.87207841873168945 -0.66829699277877808;
	setAttr -s 12 ".kox[0:11]"  0.31335929036140442 0.22871021926403046 
		0.11980143934488297 0.17087477445602417 0.90964895486831665 0.62399858236312866 0.12390644103288651 
		1 1 0.86404323577880859 0.48936620354652405 0.74389457702636719;
	setAttr -s 12 ".koy[0:11]"  -0.94963467121124268 0.97349452972412109 
		-0.99279791116714478 -0.98529273271560669 -0.41537779569625854 0.78142553567886353 
		0.99229389429092407 0 0 -0.50341761112213135 -0.87207841873168945 -0.66829705238342285;
createNode animCurveTA -n "animCurveTA1552";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1553";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1554";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1555";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 16.605943421077143 4 25.675870473757751 
		6 25.675870473757751 10 25.675870473757751 26 25.675870473757751 44 25.675870473757751;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1556";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -7.5398172157720449 4 -3.0739741698828946 
		6 -3.0739741698828946 10 -3.0739741698828946 26 -3.0739741698828946 44 -3.0739741698828946;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU490";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 3 4 3 6 3 10 3 26 3 44 3;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU491";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU492";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 4 1 6 1 10 1 26 1 44 1;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kot[0:5]"  1 5 5 5 5 5;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0 0 0 0 0;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU493";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1557";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 17 ".ktv[0:16]"  0 94.758907495741269 1 122.44248540813392 
		2 234.28607387526793 3 288.39424559215945 4 -45.002416114745195 5 -34.568647854728013 
		6 -31.983111192500814 10 -31.147106309237099 23 -30.890545881150942 26 -30.580423547275142 
		30 -94.839361968805505 36 -67.746370176445694 40 -164.00879834873444 41 -196.1792014394193 
		42 -220.72852452942723 43 -279.25088762972513 44 93.144161708979723;
	setAttr -s 17 ".kit[0:16]"  1 10 10 10 10 10 10 10 
		2 1 2 10 10 10 10 10 10;
	setAttr -s 17 ".kot[0:16]"  1 10 10 10 10 10 10 10 
		2 1 2 10 10 10 10 10 10;
	setAttr -s 17 ".kix[0:16]"  0.015739323571324348 0.02736591175198555 
		0.023010944947600365 0.0136753274127841 0.011826287023723125 1 1 1 0.99994665384292603 
		0.99996918439865112 0.1180538609623909 0.2661539614200592 0.074147768318653107 0.067191489040851593 
		0.045932423323392868 0.012168752029538155 0.0051285303197801113;
	setAttr -s 17 ".kiy[0:16]"  0.99987614154815674 0.99962544441223145 
		0.99973517656326294 -0.99990653991699219 -0.99993008375167847 0 0 0 0.010332888923585415 
		0.0078458571806550026 -0.99300718307495117 -0.96393048763275146 -0.99724727869033813 
		-0.99774014949798584 -0.99894458055496216 0.99992591142654419 0.99998688697814941;
	setAttr -s 17 ".kox[0:16]"  0.015739323571324348 0.02736591175198555 
		0.023010944947600365 0.0136753274127841 0.011826287023723125 1 1 1 0.9985383152961731 
		0.14696627855300903 0.38954594731330872 0.2661539614200592 0.074147768318653107 0.067191489040851593 
		0.045932423323392868 0.012168752029538155 0.0051285303197801113;
	setAttr -s 17 ".koy[0:16]"  0.99987614154815674 0.99962544441223145 
		0.99973517656326294 -0.99990653991699219 -0.99993008375167847 0 0 0 0.054047431796789169 
		-0.98914146423339844 0.92100697755813599 -0.96393048763275146 -0.99724727869033813 
		-0.99774014949798584 -0.99894458055496216 0.99992591142654419 0.99998688697814941;
createNode animCurveTA -n "animCurveTA1558";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 17 ".ktv[0:16]"  0 91.797648196296976 1 118.99211238624623 
		2 93.697276615906972 3 117.63100985318619 4 141.07922996228331 5 131.67295035258675 
		6 130.09321066671339 10 138.72795132415499 23 134.155517352294 26 133.03534954989794 
		30 40.423582145152459 36 -62.761048833688875 40 -130.84418890272863 41 -152.28574356849245 
		42 -179.36560564843455 43 -222.28408391335884 44 95.049826002206416;
	setAttr -s 17 ".kit[0:16]"  1 10 10 10 10 10 10 10 
		2 1 2 10 10 10 10 10 10;
	setAttr -s 17 ".kot[0:16]"  1 10 10 10 10 10 10 10 
		2 1 2 10 10 10 10 10 10;
	setAttr -s 17 ".kix[0:16]"  0.04727882519364357 0.89538443088531494 
		0.9419824481010437 0.080354787409305573 0.26248404383659363 1 1 0.9922633171081543 
		0.98346149921417236 0.99969881772994995 0.082209616899490356 0.11082612723112106 
		0.10606490820646286 0.078479446470737457 0.05448758602142334 0.013918137177824974 
		0.0060183601453900337;
	setAttr -s 17 ".kiy[0:16]"  0.9988817572593689 0.44529399275779724 
		-0.33566209673881531 0.99676626920700073 0.96493631601333618 0 0 0.12415074557065964 
		-0.18111737072467804 -0.024542657658457756 -0.99661505222320557 -0.99383985996246338 
		-0.99435919523239136 -0.99691569805145264 -0.99851447343826294 0.99990314245223999 
		0.99998193979263306;
	setAttr -s 17 ".kox[0:16]"  0.047278821468353271 0.89538443088531494 
		0.9419824481010437 0.080354787409305573 0.26248404383659363 1 1 0.9922633171081543 
		0.98141968250274658 0.090971335768699646 0.11037633568048477 0.11082612723112106 
		0.10606490820646286 0.078479446470737457 0.05448758602142334 0.013918137177824974 
		0.0060183601453900337;
	setAttr -s 17 ".koy[0:16]"  0.99888169765472412 0.44529399275779724 
		-0.33566209673881531 0.99676626920700073 0.96493631601333618 0 0 0.12415074557065964 
		-0.19187355041503906 -0.9958534836769104 -0.99388986825942993 -0.99383985996246338 
		-0.99435919523239136 -0.99691569805145264 -0.99851447343826294 0.99990314245223999 
		0.99998193979263306;
createNode animCurveTA -n "animCurveTA1559";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 17 ".ktv[0:16]"  0 3.9417760850270773 1 9.8399465271256901 
		2 8.6727833826104224 3 11.030433066720869 4 13.920504169421031 5 6.5401635044629334 
		6 7.5414839385800025 10 12.071483707826669 23 8.7733713824450668 26 8.3002376545547136 
		30 -13.977636331237177 36 33.23619484334148 40 16.726148181324834 41 11.555021997685099 
		42 19.822731914464217 43 22.091150473207339 44 1.1812364035166698;
	setAttr -s 17 ".kit[0:16]"  1 10 10 10 10 10 10 10 
		2 1 2 10 10 10 10 10 10;
	setAttr -s 17 ".kot[0:16]"  1 10 10 10 10 10 10 10 
		2 1 2 10 10 10 10 10 10;
	setAttr -s 17 ".kix[0:16]"  0.045689117163419724 1 1 1 0.64794278144836426 
		1 1 0.99928098917007446 0.99129217863082886 0.99916362762451172 0.32437402009963989 
		0.52818262577056885 0.40307730436325073 0.77680373191833496 1 1 0.090959109365940094;
	setAttr -s 17 ".kiy[0:16]"  0.99895572662353516 0 0 0 -0.7616889476776123 
		0 0 0.037914764136075974 -0.13168078660964966 -0.040890451520681381 -0.94592887163162231 
		0.84913080930709839 -0.91516596078872681 0.62974274158477783 0 0 -0.99585461616516113;
	setAttr -s 17 ".kox[0:16]"  0.045689117163419724 1 1 1 0.64794278144836426 
		1 1 0.99928098917007446 0.99660784006118774 0.31400600075721741 0.23586015403270721 
		0.52818262577056885 0.40307730436325073 0.77680373191833496 1 1 0.090959109365940094;
	setAttr -s 17 ".koy[0:16]"  0.99895572662353516 0 0 0 -0.7616889476776123 
		0 0 0.037914764136075974 -0.082297272980213165 -0.9494209885597229 0.9717869758605957 
		0.84913080930709839 -0.91516596078872681 0.62974274158477783 0 0 -0.99585461616516113;
createNode animCurveTL -n "animCurveTL496";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0.31090636676756656 2 0.58795858862909833 
		3 1.5459135225428366 4 1.5674236850131176 5 2.3967560574020967 6 2.6409530537775008 
		10 2.5053017155895656 23 2.4296608892953833 26 2.146328267720075 30 0.7793020451483651 
		32 0.58198475314610532 36 0.062590499767542482 44 -0.23689498628395578;
	setAttr -s 13 ".kit[0:12]"  1 10 10 10 10 10 10 2 
		1 10 10 10 10;
	setAttr -s 13 ".kot[0:12]"  1 10 10 10 10 10 10 2 
		1 10 10 10 10;
	setAttr -s 13 ".kix[0:12]"  0.40722426772117615 0.080707058310508728 
		1 1 0.061981059610843658 0.83795547485351563 0.93698412179946899 0.98510468006134033 
		0.95091617107391357 0.12681694328784943 0.26878339052200317 0.43890789151191711 0.66500073671340942;
	setAttr -s 13 ".kiy[0:12]"  0.91332823038101196 0.99673783779144287 
		0 0 0.998077392578125 0.54573851823806763 -0.34937191009521484 -0.17195568978786469 
		-0.30944857001304626 -0.99192613363265991 -0.96320062875747681 -0.89853203296661377 
		-0.74684274196624756;
	setAttr -s 13 ".kox[0:12]"  0.40722426772117615 0.080707058310508728 
		1 1 0.061981059610843658 0.83795547485351563 0.93698412179946899 0.33282092213630676 
		0.098995424807071686 0.12681694328784943 0.26878339052200317 0.43890789151191711 
		0.66500073671340942;
	setAttr -s 13 ".koy[0:12]"  0.91332823038101196 0.99673783779144287 
		0 0 0.998077392578125 0.54573851823806763 -0.34937191009521484 -0.9429900050163269 
		-0.99508792161941528 -0.99192613363265991 -0.96320062875747681 -0.89853203296661377 
		-0.74684274196624756;
createNode animCurveTL -n "animCurveTL497";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -0.16109949055640188 2 0.42268100217724203 
		3 0.50847577402878963 4 0.191200446518763 5 0.55773279098684336 6 0.56616558696821384 
		10 0.35200008126672683 23 0.44603232124647846 26 0.5378070322258266 30 0.78669306458345023 
		32 0.71693196482330046 36 0.68938724035232801 44 -0.30633990936382105;
	setAttr -s 13 ".kit[0:12]"  1 10 10 10 10 10 10 2 
		1 10 10 10 10;
	setAttr -s 13 ".kot[0:12]"  1 10 10 10 10 10 10 2 
		1 10 10 10 10;
	setAttr -s 13 ".kix[0:12]"  0.060241285711526871 0.1477101594209671 
		0.27675220370292664 0.80428189039230347 1 1 0.97825819253921509 0.97725611925125122 
		0.99977564811706543 0.74491262435913086 1 1 0.25869449973106384;
	setAttr -s 13 ".kiy[0:12]"  0.99818384647369385 0.98903065919876099 
		-0.96094131469726563 0.59424787759780884 0 0 -0.20739062130451202 0.21206213533878326 
		-0.021183669567108154 0.66716200113296509 0 0 -0.96595925092697144;
	setAttr -s 13 ".kox[0:12]"  0.060241285711526871 0.1477101594209671 
		0.27675220370292664 0.80428189039230347 1 1 0.97825819253921509 0.73675763607025146 
		0.37475395202636719 0.74491262435913086 1 1 0.25869449973106384;
	setAttr -s 13 ".koy[0:12]"  0.99818384647369385 0.98903065919876099 
		-0.96094131469726563 0.59424787759780884 0 0 -0.20739062130451202 0.67615699768066406 
		0.92712432146072388 0.66716200113296509 0 0 -0.96595925092697144;
createNode animCurveTL -n "animCurveTL498";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0.30404901298049425 2 0.44538825751620997 
		3 0.72400372020356296 4 1.2491072551851476 5 0.78004445098336905 6 -0.16851471745723151 
		10 -0.5709334501400003 23 -0.23067621608308253 26 0.19584938019960052 30 0.15054836349981901 
		32 0.031621234959099818 36 0.3310975767458289 44 0.52899036848843184;
	setAttr -s 13 ".kit[0:12]"  1 10 10 10 10 10 10 2 
		1 10 10 10 10;
	setAttr -s 13 ".kot[0:12]"  1 10 10 10 10 10 10 2 
		1 10 10 10 10;
	setAttr -s 13 ".kix[0:12]"  0.077039673924446106 0.2316441684961319 
		0.082663848996162415 0.76547443866729736 0.046975195407867432 0.12243920564651489 
		0.99403703212738037 0.78651136159896851 0.94744753837585449 1 0.74227982759475708 
		0.62670367956161499 0.80303555727005005;
	setAttr -s 13 ".kiy[0:12]"  -0.99702805280685425 0.97280049324035645 
		0.99657750129699707 0.64346617460250854 -0.99889606237411499 -0.99247598648071289 
		-0.10904264450073242 0.61757582426071167 0.31991115212440491 0 0.67009001970291138 
		0.77925771474838257 0.59593111276626587;
	setAttr -s 13 ".kox[0:12]"  0.077039666473865509 0.2316441684961319 
		0.082663848996162415 0.76547443866729736 0.046975195407867432 0.12243920564651489 
		0.99403703212738037 0.22826293110847473 0.42844080924987793 1 0.74227982759475708 
		0.62670367956161499 0.80303555727005005;
	setAttr -s 13 ".koy[0:12]"  -0.99702799320220947 0.97280049324035645 
		0.99657750129699707 0.64346617460250854 -0.99889606237411499 -0.99247598648071289 
		-0.10904264450073242 0.97359955310821533 0.90356981754302979 0 0.67009001970291138 
		0.77925771474838257 0.59593111276626587;
createNode animCurveTU -n "animCurveTU494";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kot[0:5]"  1 5 5 5 5 5;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0 0 0 0 0;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1560";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -1.7412705252035758 4 36.443883486827964 
		6 4.7760671355902398 10 10.162883943689385 17 -9.3993785827633651 26 -72.886252862364856 
		28 -76.110432310912799 44 -24.884454396993167;
	setAttr -s 8 ".kit[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kix[0:7]"  0.09213634580373764 0.86924618482589722 
		0.39968317747116089 0.8289448618888855 0.34531429409980774 0.30037465691566467 0.58225232362747192 
		0.51230186223983765;
	setAttr -s 8 ".kiy[0:7]"  0.9957464337348938 0.4943794310092926 -0.9166533350944519 
		-0.55933022499084473 -0.93848711252212524 -0.95382130146026611 0.81300806999206543 
		0.85880547761917114;
	setAttr -s 8 ".kox[0:7]"  0.092136338353157043 0.86924618482589722 
		0.39968317747116089 0.8289448618888855 0.34531429409980774 0.30037465691566467 0.58225232362747192 
		0.51230186223983765;
	setAttr -s 8 ".koy[0:7]"  0.99574631452560425 0.4943794310092926 
		-0.9166533350944519 -0.55933022499084473 -0.93848711252212524 -0.95382130146026611 
		0.81300806999206543 0.85880547761917114;
createNode animCurveTA -n "animCurveTA1561";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -18.444525587046371 4 -30.459201038164249 
		6 -31.608161714453441 10 -43.967965221240398 17 -19.635535787988648 26 -22.227097635903824 
		28 -22.379071922332528 44 -43.339475474578435;
	setAttr -s 8 ".kit[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kix[0:7]"  0.44021478295326233 1 1 0.86881625652313232 
		1 1 1 0.82464677095413208;
	setAttr -s 8 ".kiy[0:7]"  -0.8978925347328186 0 0 0.49513459205627441 
		0 0 0 -0.56564795970916748;
	setAttr -s 8 ".kox[0:7]"  0.44021478295326233 1 1 0.86881625652313232 
		1 1 1 0.82464683055877686;
	setAttr -s 8 ".koy[0:7]"  -0.8978925347328186 0 0 0.49513459205627441 
		0 0 0 -0.56564801931381226;
createNode animCurveTA -n "animCurveTA1562";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 28.467085029148141 4 -53.059230629896661 
		6 -35.159737366835905 10 -104.41513983106373 17 -73.318550277215053 26 11.898408170159955 
		28 16.536663642450865 44 11.606559612787883;
	setAttr -s 8 ".kit[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kix[0:7]"  0.13057886064052582 0.1772477924823761 
		0.21777670085430145 0.48229071497917175 0.25409603118896484 0.22766365110874176 0.99996399879455566 
		0.98723381757736206;
	setAttr -s 8 ".kiy[0:7]"  -0.99143791198730469 -0.98416626453399658 
		-0.9759986400604248 -0.87601131200790405 0.96717900037765503 0.97373980283737183 
		-0.0084892250597476959 -0.15927760303020477;
	setAttr -s 8 ".kox[0:7]"  0.13057886064052582 0.1772477924823761 
		0.21777670085430145 0.48229071497917175 0.25409603118896484 0.22766365110874176 0.99996399879455566 
		0.98723387718200684;
	setAttr -s 8 ".koy[0:7]"  -0.99143791198730469 -0.98416626453399658 
		-0.9759986400604248 -0.87601131200790405 0.96717900037765503 0.97373980283737183 
		-0.0084892250597476959 -0.15927761793136597;
createNode animCurveTU -n "animCurveTU495";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kot[0:5]"  1 5 5 5 5 5;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0 0 0 0 0;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU496";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kot[0:5]"  1 5 5 5 5 5;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0 0 0 0 0;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU497";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU498";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kot[0:5]"  1 5 5 5 5 5;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0 0 0 0 0;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1563";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -14.820894728888412 4 3.9531091186723013 
		6 3.9531091186723013 10 3.9531091186723013 26 3.9531091186723013 44 3.9531091186723013;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1564";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -12.087543376126076 4 0.62018686761647346 
		6 0.62018686761647346 10 0.62018686761647346 26 0.62018686761647346 44 0.62018686761647346;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1565";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -1.6394740266005658 4 5.3292188742882338 
		6 5.3292188742882338 10 5.3292188742882338 26 5.3292188742882338 44 5.3292188742882338;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU499";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU500";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL499";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 18 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL500";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 18 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL501";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.1102230246251565e-016 4 0 10 0 18 
		0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1566";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -8.7849674209066766 4 -2.5484119496516913 
		6 -17.536379970210337 10 -17.536379970210337 14 -12.870764345421884 26 -24.49230293219529 
		44 -44.757110789561033;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 0.79474157094955444 1 1 0.97505706548690796 
		0.87379860877990723 0.8614654541015625;
	setAttr -s 7 ".kiy[0:6]"  0 -0.60694795846939087 0 0 -0.22195424139499664 
		-0.48628789186477661 -0.50781607627868652;
	setAttr -s 7 ".kox[0:6]"  1 0.79474157094955444 1 1 0.97505706548690796 
		0.87379860877990723 0.86146551370620728;
	setAttr -s 7 ".koy[0:6]"  0 -0.60694795846939087 0 0 -0.22195424139499664 
		-0.48628789186477661 -0.5078161358833313;
createNode animCurveTA -n "animCurveTA1567";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 -0.25849447904553391 6 12.59030242718786 
		10 12.59030242718786 14 20.408420111465936 26 13.624824305686055 44 0.10616870005340093;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 0.9994274377822876 0.94257551431655884 
		0.93062961101531982;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0.033835265785455704 -0.33399325609207153 
		-0.36596238613128662;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 0.9994274377822876 0.94257551431655884 
		0.9306296706199646;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0.033835265785455704 -0.33399325609207153 
		-0.36596241593360901;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1568";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 8.8156908752220851 6 20.541263466481265 
		10 20.541263466481265 14 28.34787458184061 26 16.588323078323885 44 -4.9406171614869088;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 0.48718026280403137 1 1 0.99173659086227417 
		0.86465805768966675 0.84752130508422852;
	setAttr -s 7 ".kiy[0:6]"  0 0.87330150604248047 0 0 -0.12829072773456573 
		-0.50236093997955322 -0.5307614803314209;
	setAttr -s 7 ".kox[0:6]"  1 0.48718026280403137 1 1 0.99173659086227417 
		0.86465805768966675 0.84752130508422852;
	setAttr -s 7 ".koy[0:6]"  0 0.87330150604248047 0 0 -0.12829072773456573 
		-0.50236093997955322 -0.5307614803314209;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1569";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -10.055041351987731 4 -27.604588158357807 
		6 -27.604588158357807 10 -27.604588158357807 26 -27.604588158357807 44 -27.604588158357807;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1570";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -15.159890268671695 4 0.70641431476594085 
		6 0.70641431476594085 10 0.70641431476594085 26 0.70641431476594085 44 0.70641431476594085;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU501";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 1;
	setAttr -s 5 ".kot[0:4]"  3 5 5 5 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU502";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 3 4 3 10 3 19 3 45 3;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU503";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU504";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 4 1 10 1 19 1 45 1;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 1;
	setAttr -s 5 ".kot[0:4]"  3 5 5 5 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU505";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1571";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1572";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1573";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL502";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 2.2204460492503131e-016 4 0 10 0 18 0 
		45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL503";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 18 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL504";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 4.4408920985006262e-016 4 0 10 0 18 0 
		45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU506";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 4 1 6 1 10 1 23 1 26 1 44 1;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  0.066519021987915039 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  -0.99778515100479126 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.066519014537334442 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  -0.99778509140014648 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1574";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -8.6505976218338478 4 0.76679361260277867 
		6 92.765234057481436 10 92.765234057481436 14 92.740346322868362 23 92.740346322868362 
		26 70.715121713467965 29 53.576833852242892 32 51.176274045850853 44 1.1288109940741509;
	setAttr -s 10 ".kit[0:9]"  1 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  1 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kix[0:9]"  0.4039304256439209 0.11227733641862869 
		1 1 1 1 0.28082343935966492 1 1 0.416352778673172;
	setAttr -s 10 ".kiy[0:9]"  0.91478973627090454 0.99367696046829224 
		0 0 0 0 -0.95975947380065918 0 0 -0.9092031717300415;
	setAttr -s 10 ".kox[0:9]"  0.4039304256439209 0.11227733641862869 
		1 1 1 1 0.28082343935966492 1 1 0.416352778673172;
	setAttr -s 10 ".koy[0:9]"  0.91478973627090454 0.99367696046829224 
		0 0 0 0 -0.95975947380065918 0 0 -0.9092031717300415;
createNode animCurveTA -n "animCurveTA1575";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 15.838213326893062 4 -4.5990637440523727 
		6 24.021178984677956 10 24.021178984677956 14 18.189521439665949 23 18.189521439665949 
		26 12.1927203150943 29 5.0107113644510095 32 11.078239232918001 44 4.8219581414201906;
	setAttr -s 10 ".kit[0:9]"  1 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  1 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kix[0:9]"  0.23444923758506775 0.81380552053451538 
		1 1 1 1 0.65615653991699219 0.99530386924743652 0.99997830390930176 0.96470147371292114;
	setAttr -s 10 ".kiy[0:9]"  -0.97212839126586914 0.58113723993301392 
		0 0 0 0 -0.75462478399276733 -0.096800066530704498 -0.0065885866060853004 -0.26334592700004578;
	setAttr -s 10 ".kox[0:9]"  0.23444923758506775 0.81380552053451538 
		1 1 1 1 0.65615653991699219 0.99530386924743652 0.99997830390930176 0.96470147371292114;
	setAttr -s 10 ".koy[0:9]"  -0.97212839126586914 0.58113723993301392 
		0 0 0 0 -0.75462478399276733 -0.096800066530704498 -0.0065885866060853004 -0.26334592700004578;
createNode animCurveTA -n "animCurveTA1576";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 10.762406735190176 4 11.104789779715167 
		6 49.42521098803882 10 49.42521098803882 14 48.047820009451506 23 48.047820009451506 
		26 37.240239884510849 29 23.950312392007842 32 33.153670369894712 44 28.08558650754679;
	setAttr -s 10 ".kit[0:9]"  1 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  1 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kix[0:9]"  0.33447209000587463 1 1 1 1 1 0.42944937944412231 
		0.94189774990081787 0.98974180221557617 0.97641092538833618;
	setAttr -s 10 ".kiy[0:9]"  -0.94240570068359375 0 0 0 0 0 -0.9030909538269043 
		-0.33589991927146912 0.14286752045154572 -0.21592047810554504;
	setAttr -s 10 ".kox[0:9]"  0.33447209000587463 1 1 1 1 1 0.42944937944412231 
		0.94189774990081787 0.98974180221557617 0.97641098499298096;
	setAttr -s 10 ".koy[0:9]"  -0.94240570068359375 0 0 0 0 0 -0.9030909538269043 
		-0.33589991927146912 0.14286752045154572 -0.21592049300670624;
createNode animCurveTU -n "animCurveTU507";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1577";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 68.629003384766676 4 68.629003384766676 
		6 68.629003384766676 10 68.629003384766676 26 68.629003384766676 44 68.629003384766676;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1578";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 5.1251585428584878 4 5.1251585428584878 
		6 5.1251585428584878 10 5.1251585428584878 26 5.1251585428584878 44 5.1251585428584878;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1579";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -1.4794141658124507 4 -1.4794141658124507 
		6 -1.4794141658124507 10 -1.4794141658124507 26 -1.4794141658124507 44 -1.4794141658124507;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1580";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 2.9967431843380723 4 2.9967431843380723 
		6 2.9967431843380723 10 2.9967431843380723 26 2.9967431843380723 44 2.9967431843380723;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1581";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 27.356153209428296 4 27.356153209428296 
		6 27.356153209428296 10 27.356153209428296 26 27.356153209428296 44 27.356153209428296;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1582";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 4.8891453517792058 4 4.8891453517792058 
		6 4.8891453517792058 10 4.8891453517792058 26 4.8891453517792058 44 4.8891453517792058;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU508";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1583";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 59.032884886088816 4 59.032884886088816 
		6 59.032884886088816 10 59.032884886088816 26 59.032884886088816 44 59.032884886088816;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1584";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1585";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1586";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 61.945270723308987 4 61.945270723308987 
		6 61.945270723308987 10 61.945270723308987 26 61.945270723308987 44 61.945270723308987;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1587";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1588";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU509";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1589";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 59.032884886088816 4 59.032884886088816 
		6 59.032884886088816 10 59.032884886088816 26 59.032884886088816 44 59.032884886088816;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1590";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1591";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1592";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 61.945270723308987 4 61.945270723308987 
		6 61.945270723308987 10 61.945270723308987 26 61.945270723308987 44 61.945270723308987;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1593";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1594";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU510";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1595";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 59.032884886088816 4 59.032884886088816 
		6 59.032884886088816 10 59.032884886088816 26 59.032884886088816 44 59.032884886088816;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1596";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1597";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1598";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 72.878304588436421 4 72.878304588436421 
		6 72.878304588436421 10 72.878304588436421 26 72.878304588436421 44 72.878304588436421;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1599";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1600";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU511";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1601";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 77.67986202714836 4 77.67986202714836 
		6 77.67986202714836 10 77.67986202714836 26 77.67986202714836 44 77.67986202714836;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1602";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1603";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1604";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 65.952779168408995 4 65.952779168408995 
		6 65.952779168408995 10 65.952779168408995 26 65.952779168408995 44 65.952779168408995;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1605";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 12.091864976351665 4 12.091864976351665 
		6 12.091864976351665 10 12.091864976351665 26 12.091864976351665 44 12.091864976351665;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1606";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -6.5683373417752975 4 -6.5683373417752975 
		6 -6.5683373417752975 10 -6.5683373417752975 26 -6.5683373417752975 44 -6.5683373417752975;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1607";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.57893286595851967 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1608";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -4.5578755537194704 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  0.64231449365615845 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0.76644116640090942 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.64231449365615845 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0.76644116640090942 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1609";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.1289926250832889 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU512";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1610";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 12.436365705996726 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1611";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.55239751696409989 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1612";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 5.5723921216378782 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1613";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 2.5510261497954789 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1614";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 4.8043734669388636 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1615";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 8.7207044940299987 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU513";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1616";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -4.5021554579173007 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1617";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.2459795055942019 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1618";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.16357092053072281 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1619";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -14.578714620161918 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1620";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -3.4204184938876607 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1621";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.65862152992218592 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU514";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1622";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -4.5021554579173007 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1623";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.2459795055942019 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1624";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.16357092053072281 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1625";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.89248319003315801 4 0 6 0 10 0 26 
		0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1626";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -11.515058104020095 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1627";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -1.2365187367536914 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU515";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1628";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -2.1004465864078719 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1629";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.28992172907953628 4 0 6 0 10 0 26 
		0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1630";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.19137342544300212 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1631";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -8.3840962551119969 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1632";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1.3516241321759586 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1633";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -3.8136069870865348 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU516";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1634";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 3.2853565462636904 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1635";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.81342046096625198 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1636";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -2.9554166985410752 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1637";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -7.9354987277988531 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1638";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 2.5214267420205454 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1639";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -1.1722682251174086 4 0 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1640";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 -8.7460441640059194 6 0 10 0 26 0 
		44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 1 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 1 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1641";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 1 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 1 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1642";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 1 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 1 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU517";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 10 0 26 0 27 0 34 0 44 0;
	setAttr -s 8 ".kit[0:7]"  3 9 9 9 9 9 1 9;
	setAttr -s 8 ".kot[0:7]"  3 9 5 5 5 5 1 5;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 0;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTU -n "animCurveTU518";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 0 6 0 10 0 26 0 27 0 34 0 44 0;
	setAttr -s 8 ".kit[0:7]"  3 9 9 9 9 9 1 9;
	setAttr -s 8 ".kot[0:7]"  3 9 5 5 5 5 1 5;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 0;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTU -n "animCurveTU519";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 4 1 6 1 10 1 26 1 27 1 34 1 44 1;
	setAttr -s 8 ".kit[0:7]"  3 9 10 10 10 10 1 10;
	setAttr -s 8 ".kot[0:7]"  3 9 10 10 10 10 1 10;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTA -n "animCurveTA1643";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 28.14555601239433 4 13.737506765447598 
		6 -10.173354040024311 10 -10.173354040024311 26 -10.173354040024311 27 -10.173354040024311 
		34 -10.173354040024311 44 -10.173354040024311;
	setAttr -s 8 ".kit[0:7]"  3 9 10 10 10 10 1 10;
	setAttr -s 8 ".kot[0:7]"  3 9 10 10 10 10 1 10;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTA -n "animCurveTA1644";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 38.868361152285679 4 15.20314349929488 
		6 0 10 0 26 0 27 0 34 0 44 0;
	setAttr -s 8 ".kit[0:7]"  3 9 10 10 10 10 1 10;
	setAttr -s 8 ".kot[0:7]"  3 9 10 10 10 10 1 10;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTA -n "animCurveTA1645";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 118.9780524356643 4 70.228054192881785 
		6 0 10 0 26 0 27 0 34 0 44 0;
	setAttr -s 8 ".kit[0:7]"  3 9 10 10 10 10 1 10;
	setAttr -s 8 ".kot[0:7]"  3 9 10 10 10 10 1 10;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTL -n "animCurveTL505";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1.3303951496237045 4 0.89045424371437965 
		6 0.00066709276309923071 10 0.00066709276309923071 26 0.00066709276309923071 27 0.00066709276309923071 
		34 0 44 0;
	setAttr -s 8 ".kit[0:7]"  3 9 10 10 10 10 1 10;
	setAttr -s 8 ".kot[0:7]"  3 9 10 10 10 10 1 10;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTL -n "animCurveTL506";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.44401465677304064 4 -0.3948524468929121 
		6 -2.4406014456148721 10 -2.4406014456148721 26 -2.4406014456148721 27 -2.4406014456148721 
		34 0.643246524321337 44 0.643246524321337;
	setAttr -s 8 ".kit[0:7]"  3 9 10 10 10 2 1 10;
	setAttr -s 8 ".kot[0:7]"  3 9 10 10 10 2 1 10;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTL -n "animCurveTL507";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.37358224361033587 4 0.26033544778631162 
		6 0.1498051191647134 10 0.1498051191647134 26 0.1498051191647134 27 0.1498051191647134 
		34 0.10481400598920043 44 0.10481400598920043;
	setAttr -s 8 ".kit[0:7]"  3 9 10 10 10 10 1 10;
	setAttr -s 8 ".kot[0:7]"  3 9 10 10 10 10 1 10;
	setAttr -s 8 ".kix[6:7]"  1 1;
	setAttr -s 8 ".kiy[6:7]"  0 0;
	setAttr -s 8 ".kox[6:7]"  1 1;
	setAttr -s 8 ".koy[6:7]"  0 0;
createNode animCurveTA -n "animCurveTA1646";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1647";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1648";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU520";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1649";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1650";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1651";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1652";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1653";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1654";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1655";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1656";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1657";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU521";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 4 1 16 1 23 1 26 1 44 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1658";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -21.36067253562004 4 23.080108337297727 
		16 23.080108337297727 23 20.792006243779376 26 23.748608531868172 44 40.718223104721211;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  0.118117555975914 1 1 1 0.89556139707565308 
		0.89670169353485107;
	setAttr -s 6 ".kiy[0:5]"  0.9929996132850647 0 0 0 0.44493800401687622 
		0.44263532757759094;
	setAttr -s 6 ".kox[0:5]"  0.118117555975914 1 1 1 0.89556139707565308 
		0.89670175313949585;
	setAttr -s 6 ".koy[0:5]"  0.9929996132850647 0 0 0 0.44493800401687622 
		0.44263535737991333;
createNode animCurveTA -n "animCurveTA1659";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -51.332055240203708 4 6.0724697441587665 
		16 6.0724697441587665 23 -2.9724700021471198 26 4.3906490968047516 44 -38.301705751263519;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  0.077674515545368195 1 1 0.99614512920379639 
		0.75038838386535645 0.62717908620834351;
	setAttr -s 6 ".kiy[0:5]"  0.99697881937026978 0 0 -0.087720476090908051 
		-0.66099721193313599 -0.77887505292892456;
	setAttr -s 6 ".kox[0:5]"  0.077674515545368195 1 1 0.99614512920379639 
		0.75038838386535645 0.62717914581298828;
	setAttr -s 6 ".koy[0:5]"  0.99697881937026978 0 0 -0.087720476090908051 
		-0.66099721193313599 -0.77887511253356934;
createNode animCurveTA -n "animCurveTA1660";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 36.433413269808511 4 25.319937034748129 
		16 25.319937034748129 23 3.3825952545998841 26 25.184024778715841 44 21.733945627788874;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  0.14800889790058136 1 1 0.99997472763061523 
		0.90933126211166382 0.99500173330307007;
	setAttr -s 6 ".kiy[0:5]"  -0.98898607492446899 0 0 -0.0071161696687340736 
		0.41607290506362915 -0.099857114255428314;
	setAttr -s 6 ".kox[0:5]"  0.14800888299942017 1 1 0.99997472763061523 
		0.90933126211166382 0.99500179290771484;
	setAttr -s 6 ".koy[0:5]"  -0.98898601531982422 0 0 -0.0071161696687340736 
		0.41607290506362915 -0.099857121706008911;
createNode animCurveTU -n "animCurveTU522";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[1:5]"  9 9 1 9 9;
	setAttr -s 6 ".kot[1:5]"  5 5 1 5 5;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0 0 1 0 0;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU523";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[1:5]"  9 9 1 9 9;
	setAttr -s 6 ".kot[1:5]"  5 5 1 5 5;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0 0 1 0 0;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU524";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 4 1 6 1 10 1 26 1 44 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 1 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 1 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1661";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -6.3804869847670806 4 18.314207549318294 
		6 17.962181958626559 10 17.962181958626559 26 17.962181958626559 44 17.962181958626559;
	setAttr -s 6 ".kit[0:5]"  1 10 10 1 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 1 10 10;
	setAttr -s 6 ".kix[0:5]"  0.15501770377159119 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0.98791170120239258 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.15501770377159119 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0.98791170120239258 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1662";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.61643020983111696 4 3.2163812846877238 
		6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 1 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 1 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1663";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -7.5548205933147043 4 9.7553081810621389 
		6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 1 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 1 10 10;
	setAttr -s 6 ".kix[0:5]"  0.45120730996131897 0.8348846435546875 
		1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0.89241921901702881 0.55042481422424316 
		0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.45120730996131897 0.8348846435546875 
		1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0.89241921901702881 0.55042481422424316 
		0 0 0 0;
createNode animCurveTL -n "animCurveTL508";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.0064652672593350008 4 0 6 0 10 0 26 
		0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 1 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 1 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL509";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.94047489156519803 4 -0.64789329560123088 
		6 -0.64789329560123088 10 -0.64789329560123088 26 -0.64789329560123088 44 -0.64789329560123088;
	setAttr -s 6 ".kit[0:5]"  1 10 10 1 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 1 10 10;
	setAttr -s 6 ".kix[0:5]"  0.22216247022151947 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0.97500967979431152 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.22216245532035828 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0.97500962018966675 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL510";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.30764143032739516 4 -0.07395615046270454 
		6 -0.07395615046270454 10 -0.07395615046270454 26 -0.07395615046270454 44 -0.07395615046270454;
	setAttr -s 6 ".kit[0:5]"  1 10 10 1 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 1 10 10;
	setAttr -s 6 ".kix[0:5]"  0.27433857321739197 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0.96163320541381836 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.27433854341506958 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0.96163314580917358 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1664";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1665";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1666";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU525";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1667";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1668";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1669";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1670";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1671";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1672";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1673";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1674";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1675";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA1676";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -19.709932078847114 4 -1.8185873962557837 
		6 65.284393841893177 10 65.284393841893177 14 65.206837535084617 23 66.889158181069277 
		26 42.836719736097557 31 15.064351354089135 44 -10.753373031419716;
	setAttr -s 9 ".kit[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kix[0:8]"  0.14100326597690582 0.13361372053623199 
		1 1 1 1 0.28278434276580811 0.53994268178939819 0.69315862655639648;
	setAttr -s 9 ".kiy[0:8]"  0.9900091290473938 0.99103349447250366 
		0 0 0 0 -0.95918351411819458 -0.84170180559158325 -0.72078514099121094;
	setAttr -s 9 ".kox[0:8]"  0.14100326597690582 0.13361372053623199 
		1 1 1 1 0.28278434276580811 0.53994268178939819 0.69315862655639648;
	setAttr -s 9 ".koy[0:8]"  0.9900091290473938 0.99103349447250366 
		0 0 0 0 -0.95918351411819458 -0.84170180559158325 -0.72078514099121094;
createNode animCurveTA -n "animCurveTA1677";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -6.6575606989330449 4 -1.1509153277299553 
		6 9.3291324091576655 10 9.3291324091576655 14 5.3680302455532303 23 0.89003954221755543 
		26 2.987172233517295 31 -1.6965877918083296 44 -4.9387346018875373;
	setAttr -s 9 ".kit[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kix[0:8]"  0.3755321204662323 0.58258694410324097 
		1 1 0.94680166244506836 1 1 0.97443681955337524 0.9915814995765686;
	setAttr -s 9 ".kiy[0:8]"  0.92680937051773071 0.81276834011077881 
		0 0 -0.32181781530380249 0 0 -0.22466155886650085 -0.12948405742645264;
	setAttr -s 9 ".kox[0:8]"  0.3755321204662323 0.58258694410324097 
		1 1 0.94680166244506836 1 1 0.97443681955337524 0.9915814995765686;
	setAttr -s 9 ".koy[0:8]"  0.92680937051773071 0.81276834011077881 
		0 0 -0.32181781530380249 0 0 -0.22466155886650085 -0.12948405742645264;
createNode animCurveTA -n "animCurveTA1678";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 23.845913475584862 4 -3.3852577667579644 
		6 30.072696886110503 10 30.072696886110503 14 24.828347448813926 23 13.526372842839907 
		26 23.326265544938778 31 25.3816894835578 44 22.393157938684443;
	setAttr -s 9 ".kit[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kix[0:8]"  1 0.87865728139877319 1 1 0.83213984966278076 
		0.99785906076431274 1 1 0.99283349514007568;
	setAttr -s 9 ".kiy[0:8]"  0 0.47745305299758911 0 0 -0.5545659065246582 
		-0.065400369465351105 0 0 -0.11950593441724777;
	setAttr -s 9 ".kox[0:8]"  1 0.87865728139877319 1 1 0.83213984966278076 
		0.99785906076431274 1 1 0.99283349514007568;
	setAttr -s 9 ".koy[0:8]"  0 0.47745305299758911 0 0 -0.5545659065246582 
		-0.065400369465351105 0 0 -0.11950593441724777;
createNode animCurveTA -n "animCurveTA1679";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -32.293142763401718 4 -0.56948517541848631 
		6 36.815139456583864 10 36.815139456583864 14 42.915328092443723 23 49.19586308154026 
		26 26.223178594809763 31 5.0676437832637555 44 -4.0865779949808214;
	setAttr -s 9 ".kit[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kix[0:8]"  0.11746381223201752 0.16358098387718201 
		1 1 0.89490771293640137 0.80832844972610474 0.32718172669410706 0.75009006261825562 
		0.93825727701187134;
	setAttr -s 9 ".kiy[0:8]"  0.99307715892791748 0.98652994632720947 
		0 0 0.44625136256217957 -0.58873182535171509 -0.94496148824691772 -0.66133570671081543 
		-0.34593823552131653;
	setAttr -s 9 ".kox[0:8]"  0.11746381223201752 0.16358098387718201 
		1 1 0.89490771293640137 0.80832844972610474 0.32718172669410706 0.75009006261825562 
		0.93825727701187134;
	setAttr -s 9 ".koy[0:8]"  0.99307715892791748 0.98652994632720947 
		0 0 0.44625136256217957 -0.58873182535171509 -0.94496148824691772 -0.66133570671081543 
		-0.34593823552131653;
createNode animCurveTA -n "animCurveTA1680";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 4.9019548161657793 4 -1.8660136159248275 
		6 5.5314322655765356 10 5.5314322655765356 14 -2.1077543650597748 23 -8.3223885631531385 
		26 -6.2894716989371489 31 -5.6525834669006318 44 -10.471027640707172;
	setAttr -s 9 ".kit[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kix[0:8]"  0.61465102434158325 0.99849462509155273 
		1 1 0.87325400114059448 1 1 1 0.98168396949768066;
	setAttr -s 9 ".kiy[0:8]"  -0.7887992262840271 0.054849576205015182 
		0 0 -0.48726522922515869 0 0 0 -0.19051699340343475;
	setAttr -s 9 ".kox[0:8]"  0.61465096473693848 0.99849462509155273 
		1 1 0.87325400114059448 1 1 1 0.98168396949768066;
	setAttr -s 9 ".koy[0:8]"  -0.78879916667938232 0.054849576205015182 
		0 0 -0.48726522922515869 0 0 0 -0.19051699340343475;
createNode animCurveTA -n "animCurveTA1681";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 4.0063764392862797 4 8.8340711825715168 
		6 7.6063288745731166 10 7.6063288745731166 14 11.099829379218455 23 8.7670431244130551 
		26 14.138635681287987 31 4.5022003155126553 44 -1.7475532445702493;
	setAttr -s 9 ".kit[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kix[0:8]"  0.69004559516906738 1 1 1 1 1 0.96318042278289795 
		0.90776175260543823 0.96974873542785645;
	setAttr -s 9 ".kiy[0:8]"  -0.72376596927642822 0 0 0 0 0 -0.2688557505607605 
		-0.41948622465133667 -0.24410536885261536;
	setAttr -s 9 ".kox[0:8]"  0.69004553556442261 1 1 1 1 1 0.96318042278289795 
		0.90776175260543823 0.96974873542785645;
	setAttr -s 9 ".koy[0:8]"  -0.72376590967178345 0 0 0 0 0 -0.2688557505607605 
		-0.41948622465133667 -0.24410536885261536;
createNode animCurveTU -n "animCurveTU526";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 6 1 10 1 23 1 26 1 41 1 44 1;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 1 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 1 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1682";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.86856001399602611 4 2.4773791123327471 
		6 21.393470316751547 26 21.014539952917577 44 20.69101533741409;
	setAttr -s 5 ".kit[0:4]"  1 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  1 10 10 10 10;
	setAttr -s 5 ".kix[0:4]"  0.2603071928024292 0.45766735076904297 
		1 1 1;
	setAttr -s 5 ".kiy[0:4]"  0.96552586555480957 0.88912349939346313 
		0 0 0;
	setAttr -s 5 ".kox[0:4]"  0.26030716300010681 0.45766735076904297 
		1 1 1;
	setAttr -s 5 ".koy[0:4]"  0.96552580595016479 0.88912349939346313 
		0 0 0;
createNode animCurveTA -n "animCurveTA1683";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 2.5947308277573864 4 7.3059259288256309 
		6 2.8774123490786696 26 -3.4871907173850674 44 -8.3978566024888135;
	setAttr -s 5 ".kit[0:4]"  1 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  1 10 10 10 10;
	setAttr -s 5 ".kix[0:4]"  1 0.99969589710235596 0.9685552716255188 
		0.98814570903778076 0.98995113372802734;
	setAttr -s 5 ".kiy[0:4]"  0 0.024661112576723099 -0.2487981915473938 
		-0.15351928770542145 -0.14141003787517548;
	setAttr -s 5 ".kox[0:4]"  1 0.99969589710235596 0.9685552716255188 
		0.98814570903778076 0.98995113372802734;
	setAttr -s 5 ".koy[0:4]"  0 0.024661112576723099 -0.2487981915473938 
		-0.15351928770542145 -0.14141003787517548;
createNode animCurveTA -n "animCurveTA1684";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 2.5046305339829242 4 5.936617765230082 
		6 15.06321819440139 26 9.7185133835331499 44 2.8255796210686652;
	setAttr -s 5 ".kit[0:4]"  1 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  1 10 10 10 10;
	setAttr -s 5 ".kix[0:4]"  0.14232367277145386 0.67403256893157959 
		0.99597364664077759 0.98607951402664185 0.98048496246337891;
	setAttr -s 5 ".kiy[0:4]"  0.98982018232345581 0.73870164155960083 
		0.089646495878696442 -0.16627410054206848 -0.19659440219402313;
	setAttr -s 5 ".kox[0:4]"  0.14232367277145386 0.67403256893157959 
		0.99597364664077759 0.98607951402664185 0.98048496246337891;
	setAttr -s 5 ".koy[0:4]"  0.98982018232345581 0.73870164155960083 
		0.089646495878696442 -0.16627410054206848 -0.19659440219402313;
createNode animCurveTU -n "animCurveTU527";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 7 0 44 0;
	setAttr -s 3 ".kit[0:2]"  1 10 10;
	setAttr -s 3 ".kot[0:2]"  1 10 10;
	setAttr -s 3 ".kix[0:2]"  1 1 1;
	setAttr -s 3 ".kiy[0:2]"  0 0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode animCurveTA -n "animCurveTA1685";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 17.187017398618714 4 28.410819212843201 
		7 -20.065202961361503 11 10.992361435541907 15 26.981698881883226 19 7.2848193879080982 
		24 12.087003261741879 28 29.076104260163152 44 0;
	setAttr -s 9 ".kit[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kix[0:8]"  0.093092598021030426 0.33778470754623413 
		0.60885781049728394 0.30887818336486816 0.97179800271987915 0.75573712587356567 0.61931324005126953 
		0.95340520143508911 0.72445172071456909;
	setAttr -s 9 ".kiy[0:8]"  -0.99565744400024414 -0.9412233829498291 
		-0.79327934980392456 0.95110166072845459 -0.23581463098526001 -0.65487509965896606 
		0.78514397144317627 -0.30169269442558289 -0.68932545185089111;
	setAttr -s 9 ".kox[0:8]"  0.093092590570449829 0.33778470754623413 
		0.60885781049728394 0.30887818336486816 0.97179800271987915 0.75573712587356567 0.61931324005126953 
		0.95340520143508911 0.72445178031921387;
	setAttr -s 9 ".koy[0:8]"  -0.99565738439559937 -0.9412233829498291 
		-0.79327934980392456 0.95110166072845459 -0.23581463098526001 -0.65487509965896606 
		0.78514397144317627 -0.30169269442558289 -0.68932551145553589;
createNode animCurveTA -n "animCurveTA1686";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 23.0741074655642 4 19.062209228390081 
		7 -23.287472940540571 11 -57.474210046667608 15 5.6291221658666286 19 -5.6996735827113501 
		24 22.455549180985397 28 24.513517894119818 44 0;
	setAttr -s 9 ".kit[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kix[0:8]"  0.11119039356708527 0.27707421779632568 
		0.17206989228725433 0.46717321872711182 0.28303694725036621 0.71459788084030151 1 
		1 0.78002989292144775;
	setAttr -s 9 ".kiy[0:8]"  -0.99379914999008179 -0.96084851026535034 
		-0.98508477210998535 0.88416588306427002 0.95910906791687012 0.69953548908233643 
		0 0 -0.62574225664138794;
	setAttr -s 9 ".kox[0:8]"  0.11119038611650467 0.27707421779632568 
		0.17206989228725433 0.46717321872711182 0.28303694725036621 0.71459788084030151 1 
		1 0.78002989292144775;
	setAttr -s 9 ".koy[0:8]"  -0.99379909038543701 -0.96084851026535034 
		-0.98508477210998535 0.88416588306427002 0.95910906791687012 0.69953548908233643 
		0 0 -0.62574225664138794;
createNode animCurveTA -n "animCurveTA1687";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 4.955132075049673 4 -30.052357559513322 
		7 -47.91390089109462 11 -43.046848676876742 15 -66.611305972585924 19 -14.720452050992598 
		24 -67.552684276097025 28 -79.613492071941067 44 0;
	setAttr -s 9 ".kit[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kix[0:8]"  0.10004948079586029 0.24515388906002045 
		0.71707969903945923 0.6327662467956543 0.4747307300567627 0.99850368499755859 0.25604799389839172 
		0.49220600724220276 0.35833722352981567;
	setAttr -s 9 ".kiy[0:8]"  0.99498248100280762 -0.96948415040969849 
		-0.6969912052154541 -0.77434283494949341 0.8801310658454895 -0.054685220122337341 
		-0.96666407585144043 0.87047868967056274 0.93359220027923584;
	setAttr -s 9 ".kox[0:8]"  0.10004948079586029 0.24515388906002045 
		0.71707969903945923 0.6327662467956543 0.4747307300567627 0.99850368499755859 0.25604799389839172 
		0.49220600724220276 0.35833725333213806;
	setAttr -s 9 ".koy[0:8]"  0.99498248100280762 -0.96948415040969849 
		-0.6969912052154541 -0.77434283494949341 0.8801310658454895 -0.054685220122337341 
		-0.96666407585144043 0.87047868967056274 0.93359225988388062;
createNode animCurveTA -n "animCurveTA1688";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 4.5343776784216434 4 16.37063133358599 
		7 12.548593581127088 11 -11.955957906526104 15 -13.349756473756969 19 -11.731288132136298 
		24 -16.420527869483493 28 -11.442950525787227 44 -17.821366541589882;
	setAttr -s 9 ".kit[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kix[0:8]"  0.10452017933130264 0.85769647359848022 
		0.42681232094764709 1 1 1 0.99985933303833008 0.99932825565338135 0.97890216112136841;
	setAttr -s 9 ".kiy[0:8]"  0.9945228099822998 0.51415646076202393 
		-0.90434020757675171 0 0 0 0.016772441565990448 -0.036649234592914581 -0.20432935655117035;
	setAttr -s 9 ".kox[0:8]"  0.10452017933130264 0.85769647359848022 
		0.42681232094764709 1 1 1 0.99985933303833008 0.99932825565338135 0.97890222072601318;
	setAttr -s 9 ".koy[0:8]"  0.9945228099822998 0.51415646076202393 
		-0.90434020757675171 0 0 0 0.016772441565990448 -0.036649234592914581 -0.20432937145233154;
createNode animCurveTA -n "animCurveTA1689";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -17.268385207561831 4 -2.5799703105257685 
		7 -25.189815537097726 11 40.17880525876987 15 10.876620836222882 19 20.003412171115407 
		24 15.992924363444008 28 -21.30651883673757 44 -12.005893876475762;
	setAttr -s 9 ".kit[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kix[0:8]"  0.20210361480712891 0.86031836271286011 
		0.29841524362564087 0.39007297158241272 0.60371923446655273 0.95844286680221558 0.38416329026222229 
		0.80653035640716553 0.95667004585266113;
	setAttr -s 9 ".kiy[0:8]"  0.97936415672302246 -0.50975722074508667 
		0.95443612337112427 0.92078393697738647 -0.79719698429107666 0.28528478741645813 
		-0.92326515913009644 -0.59119266271591187 0.29117423295974731;
	setAttr -s 9 ".kox[0:8]"  0.20210359990596771 0.86031836271286011 
		0.29841524362564087 0.39007297158241272 0.60371923446655273 0.95844286680221558 0.38416329026222229 
		0.80653035640716553 0.95667004585266113;
	setAttr -s 9 ".koy[0:8]"  0.97936409711837769 -0.50975722074508667 
		0.95443612337112427 0.92078393697738647 -0.79719698429107666 0.28528478741645813 
		-0.92326515913009644 -0.59119266271591187 0.29117423295974731;
createNode animCurveTA -n "animCurveTA1690";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 25.186126903345176 4 7.7260759413967248 
		7 3.6840197687923069 11 -0.52496390196147291 15 5.5468943410715301 19 4.1268888362327791 
		24 5.7146476194196705 28 19.151079267295348 44 9.1378572146953019;
	setAttr -s 9 ".kit[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kix[0:8]"  1 0.52801507711410522 0.85097700357437134 
		0.99264901876449585 1 1 1 0.99600815773010254 0.95028215646743774;
	setAttr -s 9 ".kiy[0:8]"  0 -0.84923505783081055 -0.52520287036895752 
		0.1210285946726799 0 0 0 0.089261665940284729 -0.31139025092124939;
	setAttr -s 9 ".kox[0:8]"  1 0.52801507711410522 0.85097700357437134 
		0.99264901876449585 1 1 1 0.99600815773010254 0.95028215646743774;
	setAttr -s 9 ".koy[0:8]"  0 -0.84923505783081055 -0.52520287036895752 
		0.1210285946726799 0 0 0 0.089261665940284729 -0.31139025092124939;
createNode animCurveTA -n "animCurveTA1691";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -16.993199050461126 4 13.444801812254342 
		6 -28.841216077843235 10 65.754387905803 16 108.45035387343215 22 50.321862703868533 
		26 69.892087402835557 44 -28.841216077843235;
	setAttr -s 8 ".kit[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kix[0:7]"  0.38708198070526123 0.69521254301071167 
		0.2139897495508194 0.13778297603130341 0.8294748067855835 0.44385382533073425 0.46882033348083496 
		0.32882308959960938;
	setAttr -s 8 ".kiy[0:7]"  -0.92204529047012329 -0.71880424022674561 
		0.97683590650558472 0.99046248197555542 -0.55854421854019165 -0.89609915018081665 
		-0.88329356908798218 -0.94439154863357544;
	setAttr -s 8 ".kox[0:7]"  0.38708198070526123 0.69521254301071167 
		0.2139897495508194 0.13778297603130341 0.8294748067855835 0.44385382533073425 0.46882033348083496 
		0.32882308959960938;
	setAttr -s 8 ".koy[0:7]"  -0.92204529047012329 -0.71880424022674561 
		0.97683590650558472 0.99046248197555542 -0.55854421854019165 -0.89609915018081665 
		-0.88329356908798218 -0.94439154863357544;
createNode animCurveTA -n "animCurveTA1692";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -21.503801653905896 4 14.212913776763768 
		6 -21.716766331039956 10 68.161822707594368 16 81.847498958178846 22 29.495937084537374 
		26 17.963716263250973 44 -21.716766331039956;
	setAttr -s 8 ".kit[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kix[0:7]"  0.50739854574203491 0.99982738494873047 
		0.20777224004268646 0.18135499954223633 0.5098879337310791 0.28643214702606201 0.63428258895874023 
		0.65479689836502075;
	setAttr -s 8 ".kiy[0:7]"  -0.86171156167984009 -0.018581466749310493 
		0.97817724943161011 0.98341774940490723 -0.86024081707000732 -0.95810049772262573 
		-0.7731013298034668 -0.75580483675003052;
	setAttr -s 8 ".kox[0:7]"  0.50739848613739014 0.99982738494873047 
		0.20777224004268646 0.18135499954223633 0.5098879337310791 0.28643214702606201 0.63428258895874023 
		0.65479695796966553;
	setAttr -s 8 ".koy[0:7]"  -0.86171150207519531 -0.018581466749310493 
		0.97817724943161011 0.98341774940490723 -0.86024081707000732 -0.95810049772262573 
		-0.7731013298034668 -0.75580489635467529;
createNode animCurveTA -n "animCurveTA1693";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 31.859968629980841 4 63.776054388308907 
		6 23.535235892507558 10 85.766529787499721 16 152.931259000593 22 68.089830333701826 
		26 68.412239811775834 44 23.535235892507558;
	setAttr -s 8 ".kit[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kix[0:7]"  0.42472162842750549 0.80904489755630493 
		0.46211785078048706 0.14601609110832214 0.79183477163314819 1 1 0.60811692476272583;
	setAttr -s 8 ".kiy[0:7]"  0.90532404184341431 -0.58774685859680176 
		0.88681846857070923 0.98928219079971313 -0.61073541641235352 0 0 -0.79384744167327881;
	setAttr -s 8 ".kox[0:7]"  0.42472162842750549 0.80904489755630493 
		0.46211785078048706 0.14601609110832214 0.79183477163314819 1 1 0.60811698436737061;
	setAttr -s 8 ".koy[0:7]"  0.90532404184341431 -0.58774685859680176 
		0.88681846857070923 0.98928219079971313 -0.61073541641235352 0 0 -0.79384750127792358;
createNode animCurveTL -n "animCurveTL511";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL512";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL513";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU528";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 2 4 2 6 2 10 2 26 2 44 2;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kot[0:5]"  1 5 5 5 5 5;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0 0 0 0 0;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU529";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kot[0:5]"  1 5 5 5 5 5;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0 0 0 0 0;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1694";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -24.093441664171177 4 -24.093441664171177 
		6 -24.093441664171177 10 -24.093441664171177 26 -24.093441664171177 44 -24.093441664171177;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1695";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 49.48465546224881 4 49.48465546224881 
		6 49.48465546224881 10 49.48465546224881 26 49.48465546224881 44 49.48465546224881;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1696";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 58.801792680015588 4 58.801792680015588 
		6 58.801792680015588 10 58.801792680015588 26 58.801792680015588 44 58.801792680015588;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL514";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -1.2755255474500937 4 -1.2755255474500937 
		6 -1.2755255474500937 10 -1.2755255474500937 26 -1.2755255474500937 44 -1.2755255474500937;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL515";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -1.4392043230118035 4 -1.4392043230118035 
		6 -1.4392043230118035 10 -1.4392043230118035 26 -1.4392043230118035 44 -1.4392043230118035;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL516";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -2.1802956492995231 4 -2.1802956492995231 
		6 -2.1802956492995231 10 -2.1802956492995231 26 -2.1802956492995231 44 -2.1802956492995231;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL517";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 20 ".ktv[0:19]"  0 0 4 0.046922973802833945 6 0.94818264046046552 
		10 0.94818264046046552 16 1.2367424139849732 22 0.79952339302351516 23 0.77167487436547644 
		24 0.78855006421809559 25 0.42158565303039602 26 -0.91738557941474419 27 -2.2241534320043495 
		28 -3.7536016629639835 30 -2.0434050668731363 31 -1.8705655146198934 32 -1.6605419843756466 
		33 -1.5641981923715109 34 -1.4000998535069691 35 -1.2042950993318731 40 0.11969909564641107 
		44 0;
	setAttr -s 20 ".kit[0:19]"  1 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10;
	setAttr -s 20 ".kot[0:19]"  1 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10;
	setAttr -s 20 ".kix[0:19]"  1 1 1 1 0.93735808134078979 1 1 1 0.039049427956342697 
		0.025189751759171486 0.023499002680182457 0.48410424590110779 0.053030978888273239 
		0.17154556512832642 0.21262799203395844 0.24797941744327545 0.18213649094104767 0.13047149777412415 
		0.24172130227088928 0.7441285252571106;
	setAttr -s 20 ".kiy[0:19]"  0 0 0 0 -0.3483673632144928 0 0 0 -0.99923723936080933 
		-0.9996827244758606 -0.99972379207611084 0.87501031160354614 0.9985927939414978 0.98517614603042603 
		0.97713327407836914 0.9687652587890625 0.9832732081413269 0.99145203828811646 0.97034567594528198 
		-0.66803640127182007;
	setAttr -s 20 ".kox[0:19]"  1 1 1 1 0.93735808134078979 1 1 1 0.039049427956342697 
		0.025189751759171486 0.023499002680182457 0.48410424590110779 0.053030978888273239 
		0.17154556512832642 0.21262799203395844 0.24797941744327545 0.18213649094104767 0.13047149777412415 
		0.24172130227088928 0.74412858486175537;
	setAttr -s 20 ".koy[0:19]"  0 0 0 0 -0.3483673632144928 0 0 0 -0.99923723936080933 
		-0.9996827244758606 -0.99972379207611084 0.87501031160354614 0.9985927939414978 0.98517614603042603 
		0.97713327407836914 0.9687652587890625 0.9832732081413269 0.99145203828811646 0.97034567594528198 
		-0.66803646087646484;
createNode animCurveTL -n "animCurveTL518";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 20 ".ktv[0:19]"  0 0 4 -2.1626721166417773 6 -2.6455856919624954 
		10 -2.6455856919624954 16 -2.8594473804848177 22 -2.9202205187744377 23 -2.8558868712379324 
		24 -3.1043748899019072 25 -2.9980010420505594 26 -3.2551253201630881 27 -4.0566847367356882 
		28 -3.9778765400509855 30 -1.6148068833259399 31 -1.5482106642382429 32 -1.4314396008575068 
		33 -1.6061455671103602 34 -1.8479302614297675 35 -1.9044594920612243 40 2.3724564697762185 
		44 0;
	setAttr -s 20 ".kit[0:19]"  1 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10;
	setAttr -s 20 ".kot[0:19]"  1 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10;
	setAttr -s 20 ".kix[0:19]"  1 0.075382523238658905 1 1 0.82439309358596802 
		0.99988365173339844 0.34039631485939026 0.4246983528137207 0.40444809198379517 0.06284678727388382 
		0.091850213706493378 0.04091779887676239 0.041123095899820328 0.34168741106987 0.75480812788009644 
		0.15805543959140778 0.21809817850589752 0.0473359115421772 0.15560625493526459 0.056111987680196762;
	setAttr -s 20 ".kiy[0:19]"  0 -0.99715465307235718 0 0 -0.56601762771606445 
		0.015257553197443485 -0.94028204679489136 -0.90533488988876343 -0.91456097364425659 
		-0.99802315235137939 -0.9957728385925293 0.99916249513626099 0.99915415048599243 
		0.93981361389160156 -0.6559455394744873 -0.98743021488189697 -0.97592681646347046 
		0.99887901544570923 0.9878191351890564 -0.99842441082000732;
	setAttr -s 20 ".kox[0:19]"  1 0.075382523238658905 1 1 0.82439309358596802 
		0.99988365173339844 0.34039631485939026 0.4246983528137207 0.40444809198379517 0.06284678727388382 
		0.091850213706493378 0.04091779887676239 0.041123095899820328 0.34168741106987 0.75480812788009644 
		0.15805543959140778 0.21809817850589752 0.0473359115421772 0.15560625493526459 0.056111991405487061;
	setAttr -s 20 ".koy[0:19]"  0 -0.99715465307235718 0 0 -0.56601762771606445 
		0.015257553197443485 -0.94028204679489136 -0.90533488988876343 -0.91456097364425659 
		-0.99802315235137939 -0.9957728385925293 0.99916249513626099 0.99915415048599243 
		0.93981361389160156 -0.6559455394744873 -0.98743021488189697 -0.97592681646347046 
		0.99887901544570923 0.9878191351890564 -0.9984244704246521;
createNode animCurveTL -n "animCurveTL519";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 20 ".ktv[0:19]"  0 0 4 -1.2017455337849794 6 -2.4166664573558867 
		10 -2.4166664573558867 16 -2.3067593336580678 22 -2.1868806208803302 23 -2.342579950178528 
		24 -2.1758959985506792 25 -2.1738262902948793 26 -1.9961695172140868 27 -0.35607974626167049 
		28 2.2186873105869389 30 2.412782043621148 31 2.4007342895162394 32 2.7340875646679788 
		33 3.121158775849624 34 3.3725964798166168 35 3.4084377784935467 40 1.0847541349953436 
		44 0;
	setAttr -s 20 ".kit[0:19]"  1 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10;
	setAttr -s 20 ".kot[0:19]"  1 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10;
	setAttr -s 20 ".kix[0:19]"  1 0.082476675510406494 1 1 0.86710679531097412 
		0.98842060565948486 0.98669588565826416 1 1 0.036650802940130234 0.015815086662769318 
		0.036092396825551987 1 1 0.092144422233104706 0.10384533554315567 1 1 0.087677918374538422 
		0.12199757993221283;
	setAttr -s 20 ".kiy[0:19]"  0 -0.99659299850463867 0 0 0.49812212586402893 
		-0.15173932909965515 0.16257724165916443 0 0 0.9993281364440918 0.99987494945526123 
		0.99934840202331543 0 0 0.99574565887451172 0.99459350109100342 0 0 -0.99614888429641724 
		-0.99253034591674805;
	setAttr -s 20 ".kox[0:19]"  1 0.082476675510406494 1 1 0.86710679531097412 
		0.98842060565948486 0.98669588565826416 1 1 0.036650802940130234 0.015815086662769318 
		0.036092396825551987 1 1 0.092144422233104706 0.10384533554315567 1 1 0.087677918374538422 
		0.12199758738279343;
	setAttr -s 20 ".koy[0:19]"  0 -0.99659299850463867 0 0 0.49812212586402893 
		-0.15173932909965515 0.16257724165916443 0 0 0.9993281364440918 0.99987494945526123 
		0.99934840202331543 0 0 0.99574565887451172 0.99459350109100342 0 0 -0.99614888429641724 
		-0.99253040552139282;
createNode animCurveTA -n "animCurveTA1697";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1.6837025260855096 4 -7.1040262088592385 
		6 -20.28267165239345 10 -36.47447266980528 14 -31.146061441155588 18 -32.886287558103405 
		23 -30.613322987969635 27 -30.672522950181449 32 -25.642578226896468 37 5.745296714672623 
		44 1.1134085745786892;
	setAttr -s 11 ".kit[0:10]"  1 10 10 10 10 10 10 10 
		10 10 10;
	setAttr -s 11 ".kot[0:10]"  1 10 10 10 10 10 10 10 
		10 10 10;
	setAttr -s 11 ".kix[0:10]"  0.3291662335395813 0.46251648664474487 
		0.36347416043281555 0.81499528884887695 1 1 1 1 0.46443808078765869 0.65053951740264893 
		0.94489532709121704;
	setAttr -s 11 ".kiy[0:10]"  -0.94427204132080078 -0.88661068677902222 
		-0.93160432577133179 -0.5794675350189209 0 0 0 0 0.88560551404953003 0.75947248935699463 
		-0.32737258076667786;
	setAttr -s 11 ".kox[0:10]"  0.32916620373725891 0.46251648664474487 
		0.36347416043281555 0.81499528884887695 1 1 1 1 0.46443808078765869 0.65053951740264893 
		0.94489532709121704;
	setAttr -s 11 ".koy[0:10]"  -0.94427198171615601 -0.88661068677902222 
		-0.93160432577133179 -0.5794675350189209 0 0 0 0 0.88560551404953003 0.75947248935699463 
		-0.32737258076667786;
createNode animCurveTA -n "animCurveTA1698";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 2.7205216869638127 4 16.422979122628785 
		6 10.474896319218431 10 34.455581395996347 14 -2.2156622361075469 18 9.5022602139930665 
		23 8.1741719157576487 27 35.66693941766701 32 23.550458487434639 37 -6.5597242831629048 
		44 -5.3180374758492821;
	setAttr -s 11 ".kit[0:10]"  1 10 10 10 10 10 10 10 
		10 10 10;
	setAttr -s 11 ".kot[0:10]"  1 10 10 10 10 10 10 10 
		10 10 10;
	setAttr -s 11 ".kix[0:10]"  0.35855570435523987 0.82819646596908569 
		0.53633785247802734 0.76925617456436157 0.52218693494796753 1 1 0.74530833959579468 
		0.41209724545478821 1 1;
	setAttr -s 11 ".kiy[0:10]"  0.93350833654403687 0.56043791770935059 
		0.84400343894958496 -0.63894045352935791 -0.85283100605010986 0 0 0.66671997308731079 
		-0.9111398458480835 0 0;
	setAttr -s 11 ".kox[0:10]"  0.35855567455291748 0.82819646596908569 
		0.53633785247802734 0.76925617456436157 0.52218693494796753 1 1 0.74530833959579468 
		0.41209724545478821 1 1;
	setAttr -s 11 ".koy[0:10]"  0.93350827693939209 0.56043791770935059 
		0.84400343894958496 -0.63894045352935791 -0.85283100605010986 0 0 0.66671997308731079 
		-0.9111398458480835 0 0;
createNode animCurveTA -n "animCurveTA1699";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -3.6085873434754232 4 -33.637166423628251 
		6 -62.745406267558124 10 16.430390851976618 14 0.040930973421416807 18 11.074601850984035 
		23 11.710011428040316 27 9.5165355661980033 32 7.9068262507011067 37 -15.66992836725302 
		44 7.8609313736722894;
	setAttr -s 11 ".kit[0:10]"  1 10 10 10 10 10 10 10 
		10 10 10;
	setAttr -s 11 ".kot[0:10]"  1 10 10 10 10 10 10 10 
		10 10 10;
	setAttr -s 11 ".kix[0:10]"  0.071679279208183289 0.19023504853248596 
		0.22310499846935272 0.23644687235355377 0.94370067119598389 1 1 1 1 0.99999797344207764 
		0.4939873218536377;
	setAttr -s 11 ".kiy[0:10]"  -0.99742776155471802 -0.98173856735229492 
		0.97479444742202759 0.97164446115493774 -0.3308006227016449 0 0 0 0 -0.0020025379490107298 
		0.86946910619735718;
	setAttr -s 11 ".kox[0:10]"  0.071679271757602692 0.19023504853248596 
		0.22310499846935272 0.23644687235355377 0.94370067119598389 1 1 1 1 0.99999797344207764 
		0.4939873218536377;
	setAttr -s 11 ".koy[0:10]"  -0.99742770195007324 -0.98173856735229492 
		0.97479444742202759 0.97164446115493774 -0.3308006227016449 0 0 0 0 -0.0020025379490107298 
		0.86946910619735718;
createNode animCurveTL -n "animCurveTL520";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.037534362686846373 23 0 44 0;
	setAttr -s 3 ".kit[0:2]"  1 10 10;
	setAttr -s 3 ".kot[0:2]"  1 10 10;
	setAttr -s 3 ".kix[0:2]"  1 1 1;
	setAttr -s 3 ".kiy[0:2]"  0 0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode animCurveTL -n "animCurveTL521";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.0030823913851238133 23 0 44 0;
	setAttr -s 3 ".kit[0:2]"  1 10 10;
	setAttr -s 3 ".kot[0:2]"  1 10 10;
	setAttr -s 3 ".kix[0:2]"  1 1 1;
	setAttr -s 3 ".kiy[0:2]"  0 0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode animCurveTL -n "animCurveTL522";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.00068273056637632766 23 0 44 0;
	setAttr -s 3 ".kit[0:2]"  1 10 10;
	setAttr -s 3 ".kot[0:2]"  1 10 10;
	setAttr -s 3 ".kix[0:2]"  1 1 1;
	setAttr -s 3 ".kiy[0:2]"  0 0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode animCurveTA -n "animCurveTA1700";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1701";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1702";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL523";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL524";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL525";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU530";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 9;
	setAttr -s 6 ".kot[0:5]"  1 5 5 5 5 5;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0 0 0 0 0;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1703";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -14.144514188209598 4 -5.1107219305963252 
		6 -5.1107219305963252 10 -5.1107219305963252 26 -5.1107219305963252 44 -5.1107219305963252;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1704";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 15.874257618795077 4 8.2811672786141717 
		6 8.2811672786141717 10 8.2811672786141717 26 8.2811672786141717 44 8.2811672786141717;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1705";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 4.45831687435627 4 -0.92645454014921158 
		6 -0.92645454014921158 10 -0.92645454014921158 26 -0.92645454014921158 44 -0.92645454014921158;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL526";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.026428031826747314 4 -0.046856395845859107 
		6 -0.046856395845859107 10 -0.046856395845859107 26 -0.046856395845859107 44 -0.046856395845859107;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL527";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.0038712554641169919 4 -0.023348763690700665 
		6 -0.023348763690700665 10 -0.023348763690700665 26 -0.023348763690700665 44 -0.023348763690700665;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL528";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.031317869941039495 4 -0.13506113021862395 
		6 -0.13506113021862395 10 -0.13506113021862395 26 -0.13506113021862395 44 -0.13506113021862395;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1706";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 9.9791658431452266 4 24.943216647091731 
		6 36.289522252076488 9 13.749680069769095 16 4.1143600411752299 20 17.425593621937399 
		24 5.2311830417939946 44 -1.6266160090263075;
	setAttr -s 8 ".kit[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kix[0:7]"  0.26640716195106506 0.39930838346481323 
		0.64902013540267944 0.51043188571929932 0.98503494262695313 0.99733918905258179 0.92340832948684692 
		0.98426270484924316;
	setAttr -s 8 ".kiy[0:7]"  0.96386063098907471 0.91681671142578125 
		-0.76077127456665039 -0.85991817712783813 0.17235459387302399 0.072901397943496704 
		-0.38381904363632202 -0.1767113208770752;
	setAttr -s 8 ".kox[0:7]"  0.26640716195106506 0.39930838346481323 
		0.64902013540267944 0.51043188571929932 0.98503494262695313 0.99733918905258179 0.92340832948684692 
		0.98426276445388794;
	setAttr -s 8 ".koy[0:7]"  0.96386063098907471 0.91681671142578125 
		-0.76077127456665039 -0.85991817712783813 0.17235459387302399 0.072901397943496704 
		-0.38381904363632202 -0.17671133577823639;
createNode animCurveTA -n "animCurveTA1707";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -15.583017783527731 4 -12.503031790742643 
		6 -34.491062179369251 9 -14.372621098410619 16 1.0518651718745948 20 -21.741145259085382 
		24 -9.3641569636081776 44 2.8499857758927387;
	setAttr -s 8 ".kit[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kix[0:7]"  0.38064512610435486 0.51829296350479126 
		0.98136848211288452 0.47333294153213501 0.94364017248153687 0.82626235485076904 0.88119333982467651 
		0.95248895883560181;
	setAttr -s 8 ".kiy[0:7]"  -0.92472118139266968 -0.85520315170288086 
		-0.19213518500328064 0.88088351488113403 -0.33097320795059204 -0.5632854700088501 
		0.47275605797767639 0.30457311868667603;
	setAttr -s 8 ".kox[0:7]"  0.38064512610435486 0.51829296350479126 
		0.98136848211288452 0.47333294153213501 0.94364017248153687 0.82626235485076904 0.88119333982467651 
		0.95248895883560181;
	setAttr -s 8 ".koy[0:7]"  -0.92472118139266968 -0.85520315170288086 
		-0.19213518500328064 0.88088351488113403 -0.33097320795059204 -0.5632854700088501 
		0.47275605797767639 0.30457311868667603;
createNode animCurveTA -n "animCurveTA1708";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -8.6558175842077496 4 -25.30793290120771 
		6 -24.445487940623103 9 -37.013562718310368 16 -38.826055614772379 20 -42.370808828149251 
		24 -38.816749505002093 44 -25.210898828531619;
	setAttr -s 8 ".kit[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kix[0:7]"  0.42261308431625366 1 1 1 1 0.99999988079071045 
		0.9365227222442627 0.94202280044555664;
	setAttr -s 8 ".kiy[0:7]"  -0.90631020069122314 0 0 0 0 0.0006090834503993392 
		0.35060706734657288 0.33554881811141968;
	setAttr -s 8 ".kox[0:7]"  0.42261308431625366 1 1 1 1 0.99999988079071045 
		0.9365227222442627 0.94202286005020142;
	setAttr -s 8 ".koy[0:7]"  -0.90631020069122314 0 0 0 0 0.0006090834503993392 
		0.35060706734657288 0.33554884791374207;
createNode animCurveTL -n "animCurveTL529";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.0044539087538226479 44 -0.011193700785458628;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
	setAttr -s 2 ".kix[0:1]"  1 1;
	setAttr -s 2 ".kiy[0:1]"  0 0;
	setAttr -s 2 ".kox[0:1]"  1 1;
	setAttr -s 2 ".koy[0:1]"  0 0;
createNode animCurveTL -n "animCurveTL530";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.011603435393514661 44 -0.020021267836214246;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
	setAttr -s 2 ".kix[0:1]"  1 1;
	setAttr -s 2 ".kiy[0:1]"  0 0;
	setAttr -s 2 ".kox[0:1]"  1 1;
	setAttr -s 2 ".koy[0:1]"  0 0;
createNode animCurveTL -n "animCurveTL531";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.042647659991967492 44 0.032441787830836878;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
	setAttr -s 2 ".kix[0:1]"  1 1;
	setAttr -s 2 ".kiy[0:1]"  0 0;
	setAttr -s 2 ".kox[0:1]"  1 1;
	setAttr -s 2 ".koy[0:1]"  0 0;
createNode animCurveTA -n "animCurveTA1709";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1710";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1711";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL532";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL533";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL534";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1712";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 5.1542767531105751 4 -1.6848004260532123 
		6 -15.223172950814471 10 -15.223172950814471 14 -15.139445620124498 23 -15.139445620124498 
		26 -15.165323216644429 31 -12.00345844889693 35 -15.305062149008407 44 -15.609971163878811;
	setAttr -s 10 ".kit[0:9]"  1 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  1 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kix[0:9]"  0.19803524017333984 0.4901585578918457 
		1 1 1 1 1 0.99996697902679443 1 1;
	setAttr -s 10 ".kiy[0:9]"  -0.98019492626190186 -0.87163329124450684 
		0 0 0 0 0 -0.0081294141709804535 0 0;
	setAttr -s 10 ".kox[0:9]"  0.19803524017333984 0.4901585578918457 
		1 1 1 1 1 0.99996697902679443 1 1;
	setAttr -s 10 ".koy[0:9]"  -0.98019492626190186 -0.87163329124450684 
		0 0 0 0 0 -0.0081294141709804535 0 0;
createNode animCurveTA -n "animCurveTA1713";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 5.2322067179937664 4 7.6321181937450335 
		6 10.167159405083396 10 10.167159405083396 14 13.355715245454855 23 13.355715245454855 
		26 13.16497400272109 31 9.3209696100599029 35 12.134971946816608 44 8.3116042646716988;
	setAttr -s 10 ".kit[0:9]"  1 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  1 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kix[0:9]"  1 1 1 1 1 1 1 1 1 0.97614318132400513;
	setAttr -s 10 ".kiy[0:9]"  0 0 0 0 0 0 0 0 0 -0.21712788939476013;
	setAttr -s 10 ".kox[0:9]"  1 1 1 1 1 1 1 1 1 0.97614318132400513;
	setAttr -s 10 ".koy[0:9]"  0 0 0 0 0 0 0 0 0 -0.21712788939476013;
createNode animCurveTA -n "animCurveTA1714";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 12.896297905620839 4 10.904884872716545 
		6 -1.6941338883146335 10 -1.6941338883146335 14 -3.8979227717016793 23 -3.8979227717016793 
		26 -3.6947466958478565 31 7.6234435739218229 35 0.54923506455412396 44 14.458598883932659;
	setAttr -s 10 ".kit[0:9]"  1 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  1 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kix[0:9]"  0.25181841850280762 1 1 1 1 1 1 0.97084540128707886 
		0.96413177251815796 0.77736270427703857;
	setAttr -s 10 ".kiy[0:9]"  -0.96777451038360596 0 0 0 0 0 0 0.23970647156238556 
		0.26542386412620544 0.62905263900756836;
	setAttr -s 10 ".kox[0:9]"  0.25181838870048523 1 1 1 1 1 1 0.97084540128707886 
		0.96413177251815796 0.77736270427703857;
	setAttr -s 10 ".koy[0:9]"  -0.96777445077896118 0 0 0 0 0 0 0.23970647156238556 
		0.26542386412620544 0.62905263900756836;
createNode animCurveTL -n "animCurveTL535";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -0.11785145743023109 4 -0.15949525569196843 
		6 -0.34161992939920194 10 -0.50706112852588325 14 -0.283699173476609 19 -0.24339629397116225 
		23 -0.24339629397116225 26 -0.41474091240109223 31 -0.29944018194108801 35 -0.41805177443256758 
		44 -0.18868131369562219;
	setAttr -s 11 ".kit[0:10]"  1 10 10 10 1 10 1 10 
		10 10 10;
	setAttr -s 11 ".kot[0:10]"  1 10 10 10 1 10 1 10 
		10 10 10;
	setAttr -s 11 ".kix[0:10]"  0.20270821452140808 1 0.49875149130821228 
		0.977214515209198 0.82899874448776245 1 1 0.97862112522125244 0.99993908405303955 
		0.96885305643081665 0.79441070556640625;
	setAttr -s 11 ".kiy[0:10]"  -0.97923922538757324 0 -0.86674493551254272 
		0.21225377917289734 0.55925047397613525 0 0 -0.20567150413990021 -0.011035536415874958 
		0.24763628840446472 0.60738098621368408;
	setAttr -s 11 ".kox[0:10]"  0.20270821452140808 1 0.49875149130821228 
		0.977214515209198 0.82899880409240723 1 1 0.97862112522125244 0.99993908405303955 
		0.96885305643081665 0.79441070556640625;
	setAttr -s 11 ".koy[0:10]"  -0.97923922538757324 0 -0.86674493551254272 
		0.21225377917289734 0.55925047397613525 0 0 -0.20567150413990021 -0.011035536415874958 
		0.24763628840446472 0.60738098621368408;
createNode animCurveTL -n "animCurveTL536";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -0.32562836738562206 4 -1.0556205908446799 
		6 -1.2889106503900234 10 -1.6599624521690206 14 -1.5038812702099063 19 -1.328079074066786 
		23 -1.3502524000919662 26 -1.3043584566155404 28 -1.1687932894812039 31 -0.55367951762873135 
		35 -0.17586358895404097 44 0.23059098815955009;
	setAttr -s 12 ".kit[0:11]"  1 10 10 10 10 10 1 10 
		10 10 10 10;
	setAttr -s 12 ".kot[0:11]"  1 10 10 10 10 10 1 10 
		10 10 10 10;
	setAttr -s 12 ".kix[0:11]"  0.13219662010669708 0.20328806340694427 
		0.31418085098266602 0.77853161096572876 0.67057472467422485 1 1 1 0.21674342453479767 
		0.22876319289207458 0.4836183488368988 0.5938495397567749;
	setAttr -s 12 ".kiy[0:11]"  -0.99122357368469238 -0.9791189432144165 
		-0.94936317205429077 -0.6276053786277771 0.74184203147888184 0 0 0 0.97622859477996826 
		0.97348207235336304 0.87527894973754883 0.80457603931427002;
	setAttr -s 12 ".kox[0:11]"  0.13219662010669708 0.20328806340694427 
		0.31418085098266602 0.77853161096572876 0.67057472467422485 1 1 1 0.21674342453479767 
		0.22876319289207458 0.4836183488368988 0.59384959936141968;
	setAttr -s 12 ".koy[0:11]"  -0.99122357368469238 -0.9791189432144165 
		-0.94936317205429077 -0.6276053786277771 0.74184203147888184 0 0 0 0.97622859477996826 
		0.97348207235336304 0.87527894973754883 0.80457609891891479;
createNode animCurveTL -n "animCurveTL537";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0.024189830447151672 4 0.48715780955203636 
		6 -0.021904753406435218 10 -0.022492712523652314 14 -0.041356078547702124 19 -0.040819813603834965 
		23 -0.040819813603834965 26 0.069343046419941712 28 0.1442134986528405 31 0.067388446278287592 
		35 0.063444438749499996 44 0.049918713102953649;
	setAttr -s 12 ".kit[0:11]"  1 10 10 10 10 10 1 10 
		10 10 10 10;
	setAttr -s 12 ".kot[0:11]"  1 10 10 10 10 10 1 10 
		10 10 10 10;
	setAttr -s 12 ".kix[0:11]"  0.70498102903366089 0.97445434331893921 
		1 1 1 1 1 0.66926795244216919 0.9999312162399292 1 1 1;
	setAttr -s 12 ".kiy[0:11]"  0.70922625064849854 -0.22458533942699432 
		0 0 0 0 0 0.74302107095718384 -0.011726797558367252 0 0 0;
	setAttr -s 12 ".kox[0:11]"  0.70498096942901611 0.97445434331893921 
		1 1 1 1 1 0.66926795244216919 0.9999312162399292 1 1 1;
	setAttr -s 12 ".koy[0:11]"  0.70922619104385376 -0.22458533942699432 
		0 0 0 0 0 0.74302107095718384 -0.011726797558367252 0 0 0;
createNode animCurveTU -n "animCurveTU531";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 0 6 0 10 0 23 0 26 0 44 0;
	setAttr -s 7 ".kit[0:6]"  1 9 9 9 9 9 3;
	setAttr -s 7 ".kot[0:6]"  1 5 5 5 5 5 3;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 0 0 0 0 0 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU532";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.084155571970393403 4 0.084155571970393403 
		6 0.084155571970393403 10 0.084155571970393403 23 0.084155571970393403 26 0.084155571970393403 
		44 0.084155571970393403;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 3;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL538";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 -0.044922195169555104 6 -0.25134225678040134 
		10 -0.25134225678040134 23 -0.25134225678040134 26 -0.2351874115263079 44 0.067207227343123899;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kix[0:6]"  0.6400681734085083 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  -0.76831817626953125 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.64006811380386353 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  -0.76831811666488647 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL539";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.8360926868100278 4 -0.53892105082334529 
		6 -1.1541395865292186 10 -1.1541395865292186 23 -1.1541395865292186 26 -1.105991358279411 
		44 -0.20472824713235571;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kix[0:6]"  0.14856168627738953 0.53233331441879272 
		1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  -0.98890316486358643 -0.8465348482131958 
		0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.14856168627738953 0.53233331441879272 
		1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  -0.98890316486358643 -0.8465348482131958 
		0 0 0 0 0;
createNode animCurveTL -n "animCurveTL540";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.059843565101963071 4 0.39447282343292445 
		6 0.73514473590997553 10 0.73514473590997553 23 0.73514473590997553 26 0.70848307334900651 
		44 0.20941646546924442;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kix[0:6]"  0.10313946753740311 0.28397184610366821 
		1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0.9946669340133667 0.95883262157440186 
		0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.10313946008682251 0.28397184610366821 
		1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0.99466687440872192 0.95883262157440186 
		0 0 0 0 0;
createNode animCurveTU -n "animCurveTU533";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 0 6 0 10 0 23 0 26 0 44 0;
	setAttr -s 7 ".kit[0:6]"  1 9 9 9 9 9 3;
	setAttr -s 7 ".kot[0:6]"  1 5 5 5 5 5 3;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 0 0 0 0 0 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU534";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.084155864375844894 4 0.084155864375844894 
		6 0.084155864375844894 10 0.084155864375844894 23 0.084155864375844894 26 0.084155864375844894 
		44 0.084155864375844894;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 3;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL541";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 -0.07908014267111918 6 0.075704787804598217 
		10 0.075704787804598217 23 -0.20161839778685531 26 -0.19623349206641966 44 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kix[0:6]"  0.096972651779651642 0.93524116277694702 
		1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  -0.99528706073760986 0.3540111780166626 
		0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.096972651779651642 0.93524116277694702 
		1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  -0.99528706073760986 0.3540111780166626 
		0 0 0 0 0;
createNode animCurveTL -n "animCurveTL542";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.8360926868100278 4 -1.5123123506563128 
		6 -2.593719049023095 10 -2.593719049023095 23 -1.9334972650306625 26 -1.715581413894425 
		44 -0.40088449385078673;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kix[0:6]"  0.038212396204471588 0.11306022107601166 
		1 1 0.51910495758056641 0.41545391082763672 1;
	setAttr -s 7 ".kiy[0:6]"  -0.99926966428756714 -0.99358808994293213 
		0 0 0.85471051931381226 0.9096142053604126 0;
	setAttr -s 7 ".kox[0:6]"  0.03821239247918129 0.11306022107601166 
		1 1 0.51910495758056641 0.41545391082763672 1;
	setAttr -s 7 ".koy[0:6]"  -0.99926960468292236 -0.99358808994293213 
		0 0 0.85471051931381226 0.9096142053604126 0;
createNode animCurveTL -n "animCurveTL543";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.069244615545660318 4 0.027013789130760357 
		6 -0.24906881192753777 10 -0.24906881192753777 23 -0.25950451724544754 26 -0.28164562539088139 
		44 -0.69609418843799409;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kix[0:6]"  1 0.74361908435821533 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 -0.66860353946685791 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 0.74361908435821533 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 -0.66860353946685791 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1715";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 -12.892755369273527 6 25.756620160523102 
		10 25.756620160523102 12 36.837554694265826 18 -8.6134001803627882 26 -11.647341418220071 
		44 0;
	setAttr -s 8 ".kit[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kix[0:7]"  0.12998750805854797 0.40648707747459412 
		1 1 0.4062119722366333 0.48290765285491943 0.98528695106506348 0.94711649417877197;
	setAttr -s 8 ".kiy[0:7]"  0.9915156364440918 0.91365653276443481 
		0 0 -0.91377890110015869 -0.87567132711410522 0.17090809345245361 0.32089009881019592;
	setAttr -s 8 ".kox[0:7]"  0.12998750805854797 0.40648707747459412 
		1 1 0.4062119722366333 0.48290765285491943 0.98528695106506348 0.94711649417877197;
	setAttr -s 8 ".koy[0:7]"  0.9915156364440918 0.91365653276443481 
		0 0 -0.91377890110015869 -0.87567132711410522 0.17090809345245361 0.32089009881019592;
createNode animCurveTA -n "animCurveTA1716";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 0.38634885244535827 6 1.439209404234149 
		10 1.439209404234149 18 3.0613946418054283 26 2.5709027208119615 44 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1717";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 1.8252283533085836 6 6.8663079418957693 
		10 6.8663079418957693 18 14.462950428151007 26 11.371377091882538 44 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 0.98930650949478149 0.96010464429855347 
		0.94940811395645142;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0.14585153758525848 -0.27964094281196594 
		-0.31404516100883484;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 0.98930650949478149 0.96010464429855347 
		0.94940811395645142;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0.14585153758525848 -0.27964094281196594 
		-0.31404516100883484;
createNode animCurveTA -n "animCurveTA1718";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 -12.892755369273527 6 25.756620160523102 
		10 25.756620160523102 12 36.837554694265826 18 -8.6134001803627882 26 -11.647341418220071 
		44 0;
	setAttr -s 8 ".kit[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kix[0:7]"  1 0.40648707747459412 1 1 0.4062119722366333 
		0.48290765285491943 0.98528695106506348 0.94711649417877197;
	setAttr -s 8 ".kiy[0:7]"  0 0.91365653276443481 0 0 -0.91377890110015869 
		-0.87567132711410522 0.17090809345245361 0.32089009881019592;
	setAttr -s 8 ".kox[0:7]"  1 0.40648707747459412 1 1 0.4062119722366333 
		0.48290765285491943 0.98528695106506348 0.94711649417877197;
	setAttr -s 8 ".koy[0:7]"  0 0.91365653276443481 0 0 -0.91377890110015869 
		-0.87567132711410522 0.17090809345245361 0.32089009881019592;
createNode animCurveTA -n "animCurveTA1719";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 0.38634885244535827 6 1.439209404234149 
		10 1.439209404234149 18 3.0613946418054283 26 2.5709027208119615 44 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  0.42026692628860474 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  -0.90740054845809937 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.42026689648628235 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  -0.90740048885345459 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1720";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 1.8252283533085836 6 6.8663079418957693 
		10 6.8663079418957693 18 14.462950428151007 26 11.371377091882538 44 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 0.98930650949478149 0.96010464429855347 
		0.94940811395645142;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0.14585153758525848 -0.27964094281196594 
		-0.31404516100883484;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 0.98930650949478149 0.96010464429855347 
		0.94940811395645142;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0.14585153758525848 -0.27964094281196594 
		-0.31404516100883484;
createNode animCurveTA -n "animCurveTA1721";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 -12.892755369273527 6 25.756620160523102 
		10 25.756620160523102 12 36.837554694265826 18 -8.6134001803627882 26 -11.647341418220071 
		44 0;
	setAttr -s 8 ".kit[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kix[0:7]"  0.20493665337562561 0.40648707747459412 
		1 1 0.4062119722366333 0.48290765285491943 0.98528695106506348 0.94711649417877197;
	setAttr -s 8 ".kiy[0:7]"  -0.9787752628326416 0.91365653276443481 
		0 0 -0.91377890110015869 -0.87567132711410522 0.17090809345245361 0.32089009881019592;
	setAttr -s 8 ".kox[0:7]"  0.20493665337562561 0.40648707747459412 
		1 1 0.4062119722366333 0.48290765285491943 0.98528695106506348 0.94711649417877197;
	setAttr -s 8 ".koy[0:7]"  -0.9787752628326416 0.91365653276443481 
		0 0 -0.91377890110015869 -0.87567132711410522 0.17090809345245361 0.32089009881019592;
createNode animCurveTA -n "animCurveTA1722";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 0.38634885244535827 6 1.439209404234149 
		10 1.439209404234149 18 3.0613946418054283 26 2.5709027208119615 44 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  0.35783648490905762 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  -0.93378430604934692 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.35783645510673523 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  -0.93378424644470215 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1723";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 1.8252283533085836 6 6.8663079418957693 
		10 6.8663079418957693 18 14.462950428151007 26 11.371377091882538 44 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  0.79047870635986328 1 1 1 0.98930650949478149 
		0.96010464429855347 0.94940811395645142;
	setAttr -s 7 ".kiy[0:6]"  -0.61248952150344849 0 0 0 0.14585153758525848 
		-0.27964094281196594 -0.31404516100883484;
	setAttr -s 7 ".kox[0:6]"  0.79047870635986328 1 1 1 0.98930650949478149 
		0.96010464429855347 0.94940811395645142;
	setAttr -s 7 ".koy[0:6]"  -0.61248952150344849 0 0 0 0.14585153758525848 
		-0.27964094281196594 -0.31404516100883484;
createNode animCurveTA -n "animCurveTA1724";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -17.756729677074045 4 -12.256158482365986 
		6 -32.092657935286063 10 -32.092657935286063 14 -45.857454836014902 22 -1.9058247674193602 
		26 -0.47523211529705012 44 -18.592620239620459;
	setAttr -s 8 ".kit[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kix[0:7]"  0.23020893335342407 0.62437647581100464 
		1 1 0.60468709468841553 1 1 0.88466370105743408;
	setAttr -s 8 ".kiy[0:7]"  0.97314125299453735 -0.78112351894378662 
		0 0 0.79646307229995728 0 0 -0.466229647397995;
	setAttr -s 8 ".kox[0:7]"  0.23020893335342407 0.62437647581100464 
		1 1 0.60468709468841553 1 1 0.88466376066207886;
	setAttr -s 8 ".koy[0:7]"  0.97314125299453735 -0.78112351894378662 
		0 0 0.79646307229995728 0 0 -0.46622967720031738;
createNode animCurveTA -n "animCurveTA1725";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -19.18680568549097 4 -11.140320239188839 
		6 -10.84516638203533 10 -10.84516638203533 26 -8.5435325785168121 44 -4.0495369920864128;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  0.47367534041404724 1 1 1 1 0.99156343936920166;
	setAttr -s 6 ".kiy[0:5]"  -0.88069957494735718 0 0 0 0 0.12962214648723602;
	setAttr -s 6 ".kox[0:5]"  0.47367531061172485 1 1 1 1 0.99156349897384644;
	setAttr -s 6 ".koy[0:5]"  -0.8806995153427124 0 0 0 0 0.12962216138839722;
createNode animCurveTA -n "animCurveTA1726";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -18.293817522007586 4 -24.193452733144017 
		6 -24.225375809484905 10 -24.225375809484905 26 -24.450406058095506 44 -24.718935474963271;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1727";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 4 -12.892755369273527 6 25.756620160523102 
		10 25.756620160523102 12 36.837554694265826 18 -8.6134001803627882 26 -11.647341418220071 
		44 0;
	setAttr -s 8 ".kit[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kix[0:7]"  1 0.40648707747459412 1 1 0.4062119722366333 
		0.48290765285491943 0.98528695106506348 0.94711649417877197;
	setAttr -s 8 ".kiy[0:7]"  0 0.91365653276443481 0 0 -0.91377890110015869 
		-0.87567132711410522 0.17090809345245361 0.32089009881019592;
	setAttr -s 8 ".kox[0:7]"  1 0.40648707747459412 1 1 0.4062119722366333 
		0.48290765285491943 0.98528695106506348 0.94711649417877197;
	setAttr -s 8 ".koy[0:7]"  0 0.91365653276443481 0 0 -0.91377890110015869 
		-0.87567132711410522 0.17090809345245361 0.32089009881019592;
createNode animCurveTA -n "animCurveTA1728";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 0.38634885244535827 6 1.439209404234149 
		10 1.439209404234149 18 3.0613946418054283 26 2.5709027208119615 44 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  0.35565841197967529 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  -0.93461602926254272 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.35565841197967529 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  -0.93461602926254272 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1729";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 1.8252283533085836 6 6.8663079418957693 
		10 6.8663079418957693 18 14.462950428151007 26 11.371377091882538 44 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 0.98930650949478149 0.96010464429855347 
		0.94940811395645142;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0.14585153758525848 -0.27964094281196594 
		-0.31404516100883484;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 0.98930650949478149 0.96010464429855347 
		0.94940811395645142;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0.14585153758525848 -0.27964094281196594 
		-0.31404516100883484;
createNode animCurveTU -n "animCurveTU535";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 4 1 6 1 10 1 26 1 44 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU536";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 4 1 6 1 10 1 26 1 44 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU537";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 4 1 6 1 10 1 26 1 44 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1730";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  0.20083066821098328 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0.97962599992752075 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.20083066821098328 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0.97962599992752075 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1731";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  0.42576462030410767 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  -0.90483403205871582 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.42576462030410767 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  -0.90483403205871582 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1732";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  0.49280363321304321 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0.87014055252075195 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.49280360341072083 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0.87014049291610718 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL544";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL545";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL546";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU538";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 4 1 6 1 10 1 26 1 44 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU539";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 4 1 6 1 10 1 26 1 44 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU540";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 4 1 6 1 10 1 26 1 44 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1733";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  0.51848310232162476 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  -0.85508793592453003 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.51848304271697998 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  -0.85508787631988525 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1734";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  0.3059728741645813 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  -0.95204025506973267 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.3059728741645813 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  -0.95204025506973267 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1735";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  0.32207554578781128 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  -0.94671398401260376 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.32207554578781128 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  -0.94671398401260376 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL547";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL548";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL549";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1736";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1737";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1738";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 7.2644697342894906 4 -7.7166861178788215 
		6 8.6463109526121524 10 8.6463109526121524 13 20.199184015794074 20 -0.66529562233216821 
		26 -1.2061924973032629 44 7.2644697342894906;
	setAttr -s 8 ".kit[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  1 10 10 10 10 10 10 10;
	setAttr -s 8 ".kix[0:7]"  1 0.99280762672424316 1 1 0.89885705709457397 
		1 1 0.97095900774002075;
	setAttr -s 8 ".kiy[0:7]"  0 0.11972107738256454 0 0 -0.43824189901351929 
		0 0 0.23924581706523895;
	setAttr -s 8 ".kox[0:7]"  1 0.99280762672424316 1 1 0.89885705709457397 
		1 1 0.97095906734466553;
	setAttr -s 8 ".koy[0:7]"  0 0.11972107738256454 0 0 -0.43824189901351929 
		0 0 0.23924583196640015;
createNode animCurveTL -n "animCurveTL550";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 0.023144048626401969 6 0.036009749959927395 
		10 0.036009749959927395 13 0.040512744909033817 26 0.025114611329052419 44 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL551";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 0.0038613935251439768 6 -0.0043593314234235472 
		10 -0.0043593314234235472 13 -0.0072365848246766498 26 -0.0044860948234822394 44 
		0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL552";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 -0.00083633255489669127 6 0.0091828511034681842 
		10 0.0091828511034681842 13 0.01268956498079273 26 0.007866499619883803 44 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL553";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.000119480405310887 7 -0.000119480405310887 
		44 -0.000119480405310887;
createNode animCurveTL -n "animCurveTL554";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.1152566135867675 7 0.1152566135867675 
		44 0.1152566135867675;
createNode animCurveTL -n "animCurveTL555";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.19515846066137013 7 0.19515846066137013 
		44 0.19515846066137013;
createNode animCurveTU -n "animCurveTU541";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 4 1 6 1 10 1 26 1 44 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU542";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 4 1 6 1 10 1 26 1 44 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU543";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 4 1 6 1 10 1 26 1 44 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU544";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 4 1 6 1 10 1 26 1 44 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU545";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 4 1 6 1 10 1 26 1 44 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU546";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 4 1 6 1 10 1 26 1 44 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1739";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 4 -63.36005238955493 6 -44.795765529393783 
		10 -44.795765529393783 23 -42.175769430058381 26 -26.840089404374805 34 27.356331823863048 
		40 47.391768134904879 44 0;
	setAttr -s 9 ".kit[0:8]"  1 10 10 10 1 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  1 10 10 10 1 10 10 10 
		10;
	setAttr -s 9 ".kix[0:8]"  1 0.2478286474943161 1 1 0.46458807587623596 
		0.28922700881958008 0.33888286352157593 0.57243925333023071 0.15914316475391388;
	setAttr -s 9 ".kiy[0:8]"  0 -0.96880382299423218 0 0 0.88552695512771606 
		0.95726054906845093 0.94082856178283691 -0.81994712352752686 -0.9872555136680603;
	setAttr -s 9 ".kox[0:8]"  1 0.2478286474943161 1 1 0.46458807587623596 
		0.28922700881958008 0.33888286352157593 0.57243925333023071 0.15914316475391388;
	setAttr -s 9 ".koy[0:8]"  0 -0.96880382299423218 0 0 0.88552695512771606 
		0.95726054906845093 0.94082856178283691 -0.81994712352752686 -0.9872555136680603;
createNode animCurveTA -n "animCurveTA1740";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 6 0 10 0 26 0 44 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU547";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 23 1 44 1;
	setAttr -s 3 ".kit[0:2]"  1 10 10;
	setAttr -s 3 ".kot[0:2]"  1 10 10;
	setAttr -s 3 ".kix[0:2]"  1 1 1;
	setAttr -s 3 ".kiy[0:2]"  0 0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode animCurveTU -n "animCurveTU548";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 23 1 44 1;
	setAttr -s 3 ".kit[0:2]"  1 10 10;
	setAttr -s 3 ".kot[0:2]"  1 10 10;
	setAttr -s 3 ".kix[0:2]"  1 1 1;
	setAttr -s 3 ".kiy[0:2]"  0 0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode animCurveTU -n "animCurveTU549";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 23 1 44 1;
	setAttr -s 3 ".kit[0:2]"  1 10 10;
	setAttr -s 3 ".kot[0:2]"  1 10 10;
	setAttr -s 3 ".kix[0:2]"  1 1 1;
	setAttr -s 3 ".kiy[0:2]"  0 0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
createNode lightLinker -n "lightLinker1";
	setAttr -s 3 ".lnk";
	setAttr -s 3 ".slnk";
select -ne :time1;
	setAttr -av -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 44;
select -ne :renderPartition;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 3 ".st";
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
	setAttr -s 3 ".s";
select -ne :postProcessList1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -s 23 ".u";
select -ne :lightList1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
select -ne :defaultTextureList1;
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
	setAttr -s 108 ".gn";
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
connectAttr "attackSpecialASource.cl" "clipLibrary1.sc[0]";
connectAttr "animCurveTU483.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "animCurveTA1546.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "animCurveTA1547.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "animCurveTA1548.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "animCurveTU484.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "animCurveTU485.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "animCurveTU486.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "animCurveTU487.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "animCurveTA1549.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "animCurveTA1550.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "animCurveTA1551.a" "clipLibrary1.cel[0].cev[10].cevr";
connectAttr "animCurveTU488.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "animCurveTU489.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "animCurveTL493.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "animCurveTL494.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "animCurveTL495.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "animCurveTA1552.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "animCurveTA1553.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "animCurveTA1554.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "animCurveTA1555.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "animCurveTA1556.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "animCurveTU490.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "animCurveTU491.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "animCurveTU492.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "animCurveTU493.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "animCurveTA1557.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "animCurveTA1558.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "animCurveTA1559.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "animCurveTL496.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "animCurveTL497.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "animCurveTL498.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "animCurveTU494.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "animCurveTA1560.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "animCurveTA1561.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "animCurveTA1562.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "animCurveTU495.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "animCurveTU496.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "animCurveTU497.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "animCurveTU498.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "animCurveTA1563.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "animCurveTA1564.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "animCurveTA1565.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "animCurveTU499.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "animCurveTU500.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "animCurveTL499.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "animCurveTL500.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "animCurveTL501.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "animCurveTA1566.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "animCurveTA1567.a" "clipLibrary1.cel[0].cev[48].cevr";
connectAttr "animCurveTA1568.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "animCurveTA1569.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "animCurveTA1570.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "animCurveTU501.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "animCurveTU502.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "animCurveTU503.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "animCurveTU504.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "animCurveTU505.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "animCurveTA1571.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "animCurveTA1572.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "animCurveTA1573.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "animCurveTL502.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "animCurveTL503.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "animCurveTL504.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "animCurveTU506.a" "clipLibrary1.cel[0].cev[63].cevr";
connectAttr "animCurveTA1574.a" "clipLibrary1.cel[0].cev[64].cevr";
connectAttr "animCurveTA1575.a" "clipLibrary1.cel[0].cev[65].cevr";
connectAttr "animCurveTA1576.a" "clipLibrary1.cel[0].cev[66].cevr";
connectAttr "animCurveTU507.a" "clipLibrary1.cel[0].cev[67].cevr";
connectAttr "animCurveTA1577.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "animCurveTA1578.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "animCurveTA1579.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "animCurveTA1580.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "animCurveTA1581.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "animCurveTA1582.a" "clipLibrary1.cel[0].cev[73].cevr";
connectAttr "animCurveTU508.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "animCurveTA1583.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "animCurveTA1584.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "animCurveTA1585.a" "clipLibrary1.cel[0].cev[77].cevr";
connectAttr "animCurveTA1586.a" "clipLibrary1.cel[0].cev[78].cevr";
connectAttr "animCurveTA1587.a" "clipLibrary1.cel[0].cev[79].cevr";
connectAttr "animCurveTA1588.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "animCurveTU509.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "animCurveTA1589.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "animCurveTA1590.a" "clipLibrary1.cel[0].cev[83].cevr";
connectAttr "animCurveTA1591.a" "clipLibrary1.cel[0].cev[84].cevr";
connectAttr "animCurveTA1592.a" "clipLibrary1.cel[0].cev[85].cevr";
connectAttr "animCurveTA1593.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "animCurveTA1594.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "animCurveTU510.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "animCurveTA1595.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr "animCurveTA1596.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "animCurveTA1597.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "animCurveTA1598.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "animCurveTA1599.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "animCurveTA1600.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "animCurveTU511.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "animCurveTA1601.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "animCurveTA1602.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "animCurveTA1603.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "animCurveTA1604.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "animCurveTA1605.a" "clipLibrary1.cel[0].cev[100].cevr";
connectAttr "animCurveTA1606.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "animCurveTA1607.a" "clipLibrary1.cel[0].cev[102].cevr";
connectAttr "animCurveTA1608.a" "clipLibrary1.cel[0].cev[103].cevr";
connectAttr "animCurveTA1609.a" "clipLibrary1.cel[0].cev[104].cevr";
connectAttr "animCurveTU512.a" "clipLibrary1.cel[0].cev[105].cevr";
connectAttr "animCurveTA1610.a" "clipLibrary1.cel[0].cev[106].cevr";
connectAttr "animCurveTA1611.a" "clipLibrary1.cel[0].cev[107].cevr";
connectAttr "animCurveTA1612.a" "clipLibrary1.cel[0].cev[108].cevr";
connectAttr "animCurveTA1613.a" "clipLibrary1.cel[0].cev[109].cevr";
connectAttr "animCurveTA1614.a" "clipLibrary1.cel[0].cev[110].cevr";
connectAttr "animCurveTA1615.a" "clipLibrary1.cel[0].cev[111].cevr";
connectAttr "animCurveTU513.a" "clipLibrary1.cel[0].cev[112].cevr";
connectAttr "animCurveTA1616.a" "clipLibrary1.cel[0].cev[113].cevr";
connectAttr "animCurveTA1617.a" "clipLibrary1.cel[0].cev[114].cevr";
connectAttr "animCurveTA1618.a" "clipLibrary1.cel[0].cev[115].cevr";
connectAttr "animCurveTA1619.a" "clipLibrary1.cel[0].cev[116].cevr";
connectAttr "animCurveTA1620.a" "clipLibrary1.cel[0].cev[117].cevr";
connectAttr "animCurveTA1621.a" "clipLibrary1.cel[0].cev[118].cevr";
connectAttr "animCurveTU514.a" "clipLibrary1.cel[0].cev[119].cevr";
connectAttr "animCurveTA1622.a" "clipLibrary1.cel[0].cev[120].cevr";
connectAttr "animCurveTA1623.a" "clipLibrary1.cel[0].cev[121].cevr";
connectAttr "animCurveTA1624.a" "clipLibrary1.cel[0].cev[122].cevr";
connectAttr "animCurveTA1625.a" "clipLibrary1.cel[0].cev[123].cevr";
connectAttr "animCurveTA1626.a" "clipLibrary1.cel[0].cev[124].cevr";
connectAttr "animCurveTA1627.a" "clipLibrary1.cel[0].cev[125].cevr";
connectAttr "animCurveTU515.a" "clipLibrary1.cel[0].cev[126].cevr";
connectAttr "animCurveTA1628.a" "clipLibrary1.cel[0].cev[127].cevr";
connectAttr "animCurveTA1629.a" "clipLibrary1.cel[0].cev[128].cevr";
connectAttr "animCurveTA1630.a" "clipLibrary1.cel[0].cev[129].cevr";
connectAttr "animCurveTA1631.a" "clipLibrary1.cel[0].cev[130].cevr";
connectAttr "animCurveTA1632.a" "clipLibrary1.cel[0].cev[131].cevr";
connectAttr "animCurveTA1633.a" "clipLibrary1.cel[0].cev[132].cevr";
connectAttr "animCurveTU516.a" "clipLibrary1.cel[0].cev[133].cevr";
connectAttr "animCurveTA1634.a" "clipLibrary1.cel[0].cev[134].cevr";
connectAttr "animCurveTA1635.a" "clipLibrary1.cel[0].cev[135].cevr";
connectAttr "animCurveTA1636.a" "clipLibrary1.cel[0].cev[136].cevr";
connectAttr "animCurveTA1637.a" "clipLibrary1.cel[0].cev[137].cevr";
connectAttr "animCurveTA1638.a" "clipLibrary1.cel[0].cev[138].cevr";
connectAttr "animCurveTA1639.a" "clipLibrary1.cel[0].cev[139].cevr";
connectAttr "animCurveTA1640.a" "clipLibrary1.cel[0].cev[140].cevr";
connectAttr "animCurveTA1641.a" "clipLibrary1.cel[0].cev[141].cevr";
connectAttr "animCurveTA1642.a" "clipLibrary1.cel[0].cev[142].cevr";
connectAttr "animCurveTU517.a" "clipLibrary1.cel[0].cev[143].cevr";
connectAttr "animCurveTU518.a" "clipLibrary1.cel[0].cev[144].cevr";
connectAttr "animCurveTU519.a" "clipLibrary1.cel[0].cev[145].cevr";
connectAttr "animCurveTA1643.a" "clipLibrary1.cel[0].cev[146].cevr";
connectAttr "animCurveTA1644.a" "clipLibrary1.cel[0].cev[147].cevr";
connectAttr "animCurveTA1645.a" "clipLibrary1.cel[0].cev[148].cevr";
connectAttr "animCurveTL505.a" "clipLibrary1.cel[0].cev[149].cevr";
connectAttr "animCurveTL506.a" "clipLibrary1.cel[0].cev[150].cevr";
connectAttr "animCurveTL507.a" "clipLibrary1.cel[0].cev[151].cevr";
connectAttr "animCurveTA1646.a" "clipLibrary1.cel[0].cev[152].cevr";
connectAttr "animCurveTA1647.a" "clipLibrary1.cel[0].cev[153].cevr";
connectAttr "animCurveTA1648.a" "clipLibrary1.cel[0].cev[154].cevr";
connectAttr "animCurveTU520.a" "clipLibrary1.cel[0].cev[155].cevr";
connectAttr "animCurveTA1649.a" "clipLibrary1.cel[0].cev[156].cevr";
connectAttr "animCurveTA1650.a" "clipLibrary1.cel[0].cev[157].cevr";
connectAttr "animCurveTA1651.a" "clipLibrary1.cel[0].cev[158].cevr";
connectAttr "animCurveTA1652.a" "clipLibrary1.cel[0].cev[159].cevr";
connectAttr "animCurveTA1653.a" "clipLibrary1.cel[0].cev[160].cevr";
connectAttr "animCurveTA1654.a" "clipLibrary1.cel[0].cev[161].cevr";
connectAttr "animCurveTA1655.a" "clipLibrary1.cel[0].cev[162].cevr";
connectAttr "animCurveTA1656.a" "clipLibrary1.cel[0].cev[163].cevr";
connectAttr "animCurveTA1657.a" "clipLibrary1.cel[0].cev[164].cevr";
connectAttr "animCurveTU521.a" "clipLibrary1.cel[0].cev[165].cevr";
connectAttr "animCurveTA1658.a" "clipLibrary1.cel[0].cev[166].cevr";
connectAttr "animCurveTA1659.a" "clipLibrary1.cel[0].cev[167].cevr";
connectAttr "animCurveTA1660.a" "clipLibrary1.cel[0].cev[168].cevr";
connectAttr "animCurveTU522.a" "clipLibrary1.cel[0].cev[169].cevr";
connectAttr "animCurveTU523.a" "clipLibrary1.cel[0].cev[170].cevr";
connectAttr "animCurveTU524.a" "clipLibrary1.cel[0].cev[171].cevr";
connectAttr "animCurveTA1661.a" "clipLibrary1.cel[0].cev[172].cevr";
connectAttr "animCurveTA1662.a" "clipLibrary1.cel[0].cev[173].cevr";
connectAttr "animCurveTA1663.a" "clipLibrary1.cel[0].cev[174].cevr";
connectAttr "animCurveTL508.a" "clipLibrary1.cel[0].cev[175].cevr";
connectAttr "animCurveTL509.a" "clipLibrary1.cel[0].cev[176].cevr";
connectAttr "animCurveTL510.a" "clipLibrary1.cel[0].cev[177].cevr";
connectAttr "animCurveTA1664.a" "clipLibrary1.cel[0].cev[178].cevr";
connectAttr "animCurveTA1665.a" "clipLibrary1.cel[0].cev[179].cevr";
connectAttr "animCurveTA1666.a" "clipLibrary1.cel[0].cev[180].cevr";
connectAttr "animCurveTU525.a" "clipLibrary1.cel[0].cev[181].cevr";
connectAttr "animCurveTA1667.a" "clipLibrary1.cel[0].cev[182].cevr";
connectAttr "animCurveTA1668.a" "clipLibrary1.cel[0].cev[183].cevr";
connectAttr "animCurveTA1669.a" "clipLibrary1.cel[0].cev[184].cevr";
connectAttr "animCurveTA1670.a" "clipLibrary1.cel[0].cev[185].cevr";
connectAttr "animCurveTA1671.a" "clipLibrary1.cel[0].cev[186].cevr";
connectAttr "animCurveTA1672.a" "clipLibrary1.cel[0].cev[187].cevr";
connectAttr "animCurveTA1673.a" "clipLibrary1.cel[0].cev[188].cevr";
connectAttr "animCurveTA1674.a" "clipLibrary1.cel[0].cev[189].cevr";
connectAttr "animCurveTA1675.a" "clipLibrary1.cel[0].cev[190].cevr";
connectAttr "animCurveTA1676.a" "clipLibrary1.cel[0].cev[191].cevr";
connectAttr "animCurveTA1677.a" "clipLibrary1.cel[0].cev[192].cevr";
connectAttr "animCurveTA1678.a" "clipLibrary1.cel[0].cev[193].cevr";
connectAttr "animCurveTA1679.a" "clipLibrary1.cel[0].cev[194].cevr";
connectAttr "animCurveTA1680.a" "clipLibrary1.cel[0].cev[195].cevr";
connectAttr "animCurveTA1681.a" "clipLibrary1.cel[0].cev[196].cevr";
connectAttr "animCurveTU526.a" "clipLibrary1.cel[0].cev[197].cevr";
connectAttr "animCurveTA1682.a" "clipLibrary1.cel[0].cev[198].cevr";
connectAttr "animCurveTA1683.a" "clipLibrary1.cel[0].cev[199].cevr";
connectAttr "animCurveTA1684.a" "clipLibrary1.cel[0].cev[200].cevr";
connectAttr "animCurveTU527.a" "clipLibrary1.cel[0].cev[201].cevr";
connectAttr "animCurveTA1685.a" "clipLibrary1.cel[0].cev[202].cevr";
connectAttr "animCurveTA1686.a" "clipLibrary1.cel[0].cev[203].cevr";
connectAttr "animCurveTA1687.a" "clipLibrary1.cel[0].cev[204].cevr";
connectAttr "animCurveTA1688.a" "clipLibrary1.cel[0].cev[205].cevr";
connectAttr "animCurveTA1689.a" "clipLibrary1.cel[0].cev[206].cevr";
connectAttr "animCurveTA1690.a" "clipLibrary1.cel[0].cev[207].cevr";
connectAttr "animCurveTA1691.a" "clipLibrary1.cel[0].cev[208].cevr";
connectAttr "animCurveTA1692.a" "clipLibrary1.cel[0].cev[209].cevr";
connectAttr "animCurveTA1693.a" "clipLibrary1.cel[0].cev[210].cevr";
connectAttr "animCurveTL511.a" "clipLibrary1.cel[0].cev[211].cevr";
connectAttr "animCurveTL512.a" "clipLibrary1.cel[0].cev[212].cevr";
connectAttr "animCurveTL513.a" "clipLibrary1.cel[0].cev[213].cevr";
connectAttr "animCurveTU528.a" "clipLibrary1.cel[0].cev[214].cevr";
connectAttr "animCurveTU529.a" "clipLibrary1.cel[0].cev[215].cevr";
connectAttr "animCurveTA1694.a" "clipLibrary1.cel[0].cev[216].cevr";
connectAttr "animCurveTA1695.a" "clipLibrary1.cel[0].cev[217].cevr";
connectAttr "animCurveTA1696.a" "clipLibrary1.cel[0].cev[218].cevr";
connectAttr "animCurveTL514.a" "clipLibrary1.cel[0].cev[219].cevr";
connectAttr "animCurveTL515.a" "clipLibrary1.cel[0].cev[220].cevr";
connectAttr "animCurveTL516.a" "clipLibrary1.cel[0].cev[221].cevr";
connectAttr "animCurveTL517.a" "clipLibrary1.cel[0].cev[222].cevr";
connectAttr "animCurveTL518.a" "clipLibrary1.cel[0].cev[223].cevr";
connectAttr "animCurveTL519.a" "clipLibrary1.cel[0].cev[224].cevr";
connectAttr "animCurveTA1697.a" "clipLibrary1.cel[0].cev[225].cevr";
connectAttr "animCurveTA1698.a" "clipLibrary1.cel[0].cev[226].cevr";
connectAttr "animCurveTA1699.a" "clipLibrary1.cel[0].cev[227].cevr";
connectAttr "animCurveTL520.a" "clipLibrary1.cel[0].cev[228].cevr";
connectAttr "animCurveTL521.a" "clipLibrary1.cel[0].cev[229].cevr";
connectAttr "animCurveTL522.a" "clipLibrary1.cel[0].cev[230].cevr";
connectAttr "animCurveTA1700.a" "clipLibrary1.cel[0].cev[231].cevr";
connectAttr "animCurveTA1701.a" "clipLibrary1.cel[0].cev[232].cevr";
connectAttr "animCurveTA1702.a" "clipLibrary1.cel[0].cev[233].cevr";
connectAttr "animCurveTL523.a" "clipLibrary1.cel[0].cev[234].cevr";
connectAttr "animCurveTL524.a" "clipLibrary1.cel[0].cev[235].cevr";
connectAttr "animCurveTL525.a" "clipLibrary1.cel[0].cev[236].cevr";
connectAttr "animCurveTU530.a" "clipLibrary1.cel[0].cev[237].cevr";
connectAttr "animCurveTA1703.a" "clipLibrary1.cel[0].cev[238].cevr";
connectAttr "animCurveTA1704.a" "clipLibrary1.cel[0].cev[239].cevr";
connectAttr "animCurveTA1705.a" "clipLibrary1.cel[0].cev[240].cevr";
connectAttr "animCurveTL526.a" "clipLibrary1.cel[0].cev[241].cevr";
connectAttr "animCurveTL527.a" "clipLibrary1.cel[0].cev[242].cevr";
connectAttr "animCurveTL528.a" "clipLibrary1.cel[0].cev[243].cevr";
connectAttr "animCurveTA1706.a" "clipLibrary1.cel[0].cev[244].cevr";
connectAttr "animCurveTA1707.a" "clipLibrary1.cel[0].cev[245].cevr";
connectAttr "animCurveTA1708.a" "clipLibrary1.cel[0].cev[246].cevr";
connectAttr "animCurveTL529.a" "clipLibrary1.cel[0].cev[247].cevr";
connectAttr "animCurveTL530.a" "clipLibrary1.cel[0].cev[248].cevr";
connectAttr "animCurveTL531.a" "clipLibrary1.cel[0].cev[249].cevr";
connectAttr "animCurveTA1709.a" "clipLibrary1.cel[0].cev[250].cevr";
connectAttr "animCurveTA1710.a" "clipLibrary1.cel[0].cev[251].cevr";
connectAttr "animCurveTA1711.a" "clipLibrary1.cel[0].cev[252].cevr";
connectAttr "animCurveTL532.a" "clipLibrary1.cel[0].cev[253].cevr";
connectAttr "animCurveTL533.a" "clipLibrary1.cel[0].cev[254].cevr";
connectAttr "animCurveTL534.a" "clipLibrary1.cel[0].cev[255].cevr";
connectAttr "animCurveTA1712.a" "clipLibrary1.cel[0].cev[256].cevr";
connectAttr "animCurveTA1713.a" "clipLibrary1.cel[0].cev[257].cevr";
connectAttr "animCurveTA1714.a" "clipLibrary1.cel[0].cev[258].cevr";
connectAttr "animCurveTL535.a" "clipLibrary1.cel[0].cev[259].cevr";
connectAttr "animCurveTL536.a" "clipLibrary1.cel[0].cev[260].cevr";
connectAttr "animCurveTL537.a" "clipLibrary1.cel[0].cev[261].cevr";
connectAttr "animCurveTU531.a" "clipLibrary1.cel[0].cev[262].cevr";
connectAttr "animCurveTU532.a" "clipLibrary1.cel[0].cev[263].cevr";
connectAttr "animCurveTL538.a" "clipLibrary1.cel[0].cev[264].cevr";
connectAttr "animCurveTL539.a" "clipLibrary1.cel[0].cev[265].cevr";
connectAttr "animCurveTL540.a" "clipLibrary1.cel[0].cev[266].cevr";
connectAttr "animCurveTU533.a" "clipLibrary1.cel[0].cev[267].cevr";
connectAttr "animCurveTU534.a" "clipLibrary1.cel[0].cev[268].cevr";
connectAttr "animCurveTL541.a" "clipLibrary1.cel[0].cev[269].cevr";
connectAttr "animCurveTL542.a" "clipLibrary1.cel[0].cev[270].cevr";
connectAttr "animCurveTL543.a" "clipLibrary1.cel[0].cev[271].cevr";
connectAttr "animCurveTA1715.a" "clipLibrary1.cel[0].cev[272].cevr";
connectAttr "animCurveTA1716.a" "clipLibrary1.cel[0].cev[273].cevr";
connectAttr "animCurveTA1717.a" "clipLibrary1.cel[0].cev[274].cevr";
connectAttr "animCurveTA1718.a" "clipLibrary1.cel[0].cev[275].cevr";
connectAttr "animCurveTA1719.a" "clipLibrary1.cel[0].cev[276].cevr";
connectAttr "animCurveTA1720.a" "clipLibrary1.cel[0].cev[277].cevr";
connectAttr "animCurveTA1721.a" "clipLibrary1.cel[0].cev[278].cevr";
connectAttr "animCurveTA1722.a" "clipLibrary1.cel[0].cev[279].cevr";
connectAttr "animCurveTA1723.a" "clipLibrary1.cel[0].cev[280].cevr";
connectAttr "animCurveTA1724.a" "clipLibrary1.cel[0].cev[281].cevr";
connectAttr "animCurveTA1725.a" "clipLibrary1.cel[0].cev[282].cevr";
connectAttr "animCurveTA1726.a" "clipLibrary1.cel[0].cev[283].cevr";
connectAttr "animCurveTA1727.a" "clipLibrary1.cel[0].cev[284].cevr";
connectAttr "animCurveTA1728.a" "clipLibrary1.cel[0].cev[285].cevr";
connectAttr "animCurveTA1729.a" "clipLibrary1.cel[0].cev[286].cevr";
connectAttr "animCurveTU535.a" "clipLibrary1.cel[0].cev[287].cevr";
connectAttr "animCurveTU536.a" "clipLibrary1.cel[0].cev[288].cevr";
connectAttr "animCurveTU537.a" "clipLibrary1.cel[0].cev[289].cevr";
connectAttr "animCurveTA1730.a" "clipLibrary1.cel[0].cev[290].cevr";
connectAttr "animCurveTA1731.a" "clipLibrary1.cel[0].cev[291].cevr";
connectAttr "animCurveTA1732.a" "clipLibrary1.cel[0].cev[292].cevr";
connectAttr "animCurveTL544.a" "clipLibrary1.cel[0].cev[293].cevr";
connectAttr "animCurveTL545.a" "clipLibrary1.cel[0].cev[294].cevr";
connectAttr "animCurveTL546.a" "clipLibrary1.cel[0].cev[295].cevr";
connectAttr "animCurveTU538.a" "clipLibrary1.cel[0].cev[296].cevr";
connectAttr "animCurveTU539.a" "clipLibrary1.cel[0].cev[297].cevr";
connectAttr "animCurveTU540.a" "clipLibrary1.cel[0].cev[298].cevr";
connectAttr "animCurveTA1733.a" "clipLibrary1.cel[0].cev[299].cevr";
connectAttr "animCurveTA1734.a" "clipLibrary1.cel[0].cev[300].cevr";
connectAttr "animCurveTA1735.a" "clipLibrary1.cel[0].cev[301].cevr";
connectAttr "animCurveTL547.a" "clipLibrary1.cel[0].cev[302].cevr";
connectAttr "animCurveTL548.a" "clipLibrary1.cel[0].cev[303].cevr";
connectAttr "animCurveTL549.a" "clipLibrary1.cel[0].cev[304].cevr";
connectAttr "animCurveTA1736.a" "clipLibrary1.cel[0].cev[305].cevr";
connectAttr "animCurveTA1737.a" "clipLibrary1.cel[0].cev[306].cevr";
connectAttr "animCurveTA1738.a" "clipLibrary1.cel[0].cev[307].cevr";
connectAttr "animCurveTL550.a" "clipLibrary1.cel[0].cev[308].cevr";
connectAttr "animCurveTL551.a" "clipLibrary1.cel[0].cev[309].cevr";
connectAttr "animCurveTL552.a" "clipLibrary1.cel[0].cev[310].cevr";
connectAttr "animCurveTL553.a" "clipLibrary1.cel[0].cev[311].cevr";
connectAttr "animCurveTL554.a" "clipLibrary1.cel[0].cev[312].cevr";
connectAttr "animCurveTL555.a" "clipLibrary1.cel[0].cev[313].cevr";
connectAttr "animCurveTU541.a" "clipLibrary1.cel[0].cev[314].cevr";
connectAttr "animCurveTU542.a" "clipLibrary1.cel[0].cev[315].cevr";
connectAttr "animCurveTU543.a" "clipLibrary1.cel[0].cev[316].cevr";
connectAttr "animCurveTU544.a" "clipLibrary1.cel[0].cev[317].cevr";
connectAttr "animCurveTU545.a" "clipLibrary1.cel[0].cev[318].cevr";
connectAttr "animCurveTU546.a" "clipLibrary1.cel[0].cev[319].cevr";
connectAttr "animCurveTA1739.a" "clipLibrary1.cel[0].cev[320].cevr";
connectAttr "animCurveTA1740.a" "clipLibrary1.cel[0].cev[321].cevr";
connectAttr "animCurveTU547.a" "clipLibrary1.cel[0].cev[322].cevr";
connectAttr "animCurveTU548.a" "clipLibrary1.cel[0].cev[323].cevr";
connectAttr "animCurveTU549.a" "clipLibrary1.cel[0].cev[324].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of attackSpecialA.ma
