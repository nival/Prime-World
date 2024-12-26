//Maya ASCII 2008 scene
//Name: ability02.ma
//Last modified: Sun, Aug 16, 2009 10:20:37 PM
//Codeset: 1251
requires maya "2008";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Unlimited 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200802250025-718075";
fileInfo "osv" "Microsoft Windows Vista Service Pack 1 (Build 6001)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 322 ".cel[0].cev";
	setAttr ".cd[0].cm" -type "characterMapping" 322 "Ratcatcher_rt_upArm_fk_ctrl_Align.align" 
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
		194 "CTRL_TwistL.rotateX" 2 195  ;
	setAttr ".cd[0].cim" -type "Int32Array" 322 0 1 2 3 4
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
		 317 318 319 320 321 ;
createNode animClip -n "ability2Source";
	setAttr ".ihi" 0;
	setAttr -s 322 ".ac[0:321]" yes yes yes yes yes yes yes yes yes yes yes 
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
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".se" 30;
	setAttr ".ci" no;
createNode animCurveTU -n "animCurveTU483";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 28 0 30 0;
	setAttr -s 6 ".kit[0:5]"  3 9 1 1 9 1;
	setAttr -s 6 ".kot[0:5]"  3 5 1 1 5 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 0 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1545";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 1 17.983980990438564 2 -0.06313663002560492 
		4 9.8505633374316908 12 8.7496215628272811 19 11.375216001704487 25 9.8505633374316908 
		28 17.405410034903333 30 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 1 9 10 1 10 
		1;
	setAttr -s 9 ".kot[0:8]"  3 10 10 1 9 10 1 10 
		1;
	setAttr -s 9 ".kix[3:8]"  1 0.99858677387237549 1 1 0.69604194164276123 
		1;
	setAttr -s 9 ".kiy[3:8]"  0 0.053145203739404678 0 0 -0.71800106763839722 
		0;
	setAttr -s 9 ".kox[3:8]"  1 0.99858677387237549 1 1 0.69604194164276123 
		1;
	setAttr -s 9 ".koy[3:8]"  0 0.053145203739404678 0 0 -0.71800106763839722 
		0;
createNode animCurveTA -n "animCurveTA1546";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 1 43.022651806336718 2 52.266104805120897 
		4 32.52974899396547 12 31.885413336680489 19 41.655154540326649 25 32.52974899396547 
		28 0.79348225220649549 30 0;
	setAttr -s 9 ".kit[0:8]"  3 10 3 1 10 10 1 10 
		1;
	setAttr -s 9 ".kot[0:8]"  3 10 3 1 10 10 1 10 
		1;
	setAttr -s 9 ".kix[3:8]"  0.55568689107894897 1 0.99966335296630859 
		0.57800018787384033 1 1;
	setAttr -s 9 ".kiy[3:8]"  -0.83139169216156006 0 0.025943061336874962 
		-0.81603670120239258 0 0;
	setAttr -s 9 ".kox[3:8]"  0.55568695068359375 1 0.99966335296630859 
		0.57800012826919556 1 1;
	setAttr -s 9 ".koy[3:8]"  -0.83139163255691528 0 0.025943061336874962 
		-0.8160366415977478 0 0;
createNode animCurveTA -n "animCurveTA1547";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 1 -77.077849582446433 2 -22.49158278832823 
		4 33.180043515826242 12 37.416486168361502 19 52.454043584179985 25 33.180043515826242 
		28 -35.402388070561059 30 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 1 10 10 1 10 
		1;
	setAttr -s 9 ".kot[0:8]"  3 10 10 1 10 10 1 10 
		1;
	setAttr -s 9 ".kix[3:8]"  1 0.82969820499420166 0.98575299978256226 
		1 0.27657589316368103 1;
	setAttr -s 9 ".kiy[3:8]"  0 0.55821222066879272 -0.16819950938224792 
		0 -0.96099209785461426 0;
	setAttr -s 9 ".kox[3:8]"  1 0.82969820499420166 0.98575299978256226 
		1 0.27657589316368103 1;
	setAttr -s 9 ".koy[3:8]"  0 0.55821222066879272 -0.16819950938224792 
		0 -0.96099209785461426 0;
createNode animCurveTU -n "animCurveTU484";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 28 0 30 0;
	setAttr -s 6 ".kit[0:5]"  3 9 1 1 9 1;
	setAttr -s 6 ".kot[0:5]"  3 5 1 1 5 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 0 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTU -n "animCurveTU485";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 28 0 30 0;
	setAttr -s 6 ".kit[0:5]"  3 9 1 1 9 1;
	setAttr -s 6 ".kot[0:5]"  3 5 1 1 5 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 0 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTU -n "animCurveTU486";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 1 0 4 0 25 0 28 0.68427672192402955 
		30 1;
	setAttr -s 6 ".kit[0:5]"  9 10 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  9 10 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 0.16439899802207947 0.55176162719726563;
	setAttr -s 6 ".kiy[2:5]"  0 0 0.98639386892318726 -0.83400177955627441;
	setAttr -s 6 ".kox[2:5]"  1 1 0.16439899802207947 0.55176162719726563;
	setAttr -s 6 ".koy[2:5]"  0 0 0.98639386892318726 -0.83400177955627441;
createNode animCurveTU -n "animCurveTU487";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 28 0 30 0;
	setAttr -s 6 ".kit[0:5]"  3 9 1 1 9 1;
	setAttr -s 6 ".kot[0:5]"  3 5 1 1 5 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 0 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1548";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 1 -61.606994410438375 2 -137.99901841819744 
		4 -252.84049563335682 17 -252.80391640482625 21 -252.78238481744347 25 -252.84049563335682 
		26 -187.47357474525086 27 -309.42472191649165 28 -224.17206001577603 29 -181.92588982604826 
		30 -180.00000000000003;
	setAttr -s 12 ".kit[0:11]"  3 10 10 1 10 10 1 10 
		10 10 10 1;
	setAttr -s 12 ".kot[0:11]"  3 10 10 1 10 10 1 10 
		10 10 10 1;
	setAttr -s 12 ".kix[3:11]"  1 1 1 1 0.067351721227169037 0.10352456569671631 
		0.029945412650704384 1 1;
	setAttr -s 12 ".kiy[3:11]"  0 0 0 0 -0.99772930145263672 -0.99462687969207764 
		0.99955153465270996 0 0;
	setAttr -s 12 ".kox[3:11]"  1 1 1 1 0.067351721227169037 0.10352456569671631 
		0.029945412650704384 1 1;
	setAttr -s 12 ".koy[3:11]"  0 0 0 0 -0.99772930145263672 -0.99462687969207764 
		0.99955153465270996 0 0;
createNode animCurveTA -n "animCurveTA1549";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 1 22.763781824317537 2 103.7186814126237 
		4 168.03995309430235 17 167.06353517276258 21 166.84648068107907 25 168.03995309430235 
		26 191.07341303852033 27 230.9743763928326 28 208.89349386197188 29 181.15581025422247 
		30 180;
	setAttr -s 12 ".kit[0:11]"  3 10 10 1 10 10 1 10 
		10 10 10 1;
	setAttr -s 12 ".kot[0:11]"  3 10 10 1 10 10 1 10 
		10 10 10 1;
	setAttr -s 12 ".kix[3:11]"  1 1 1 1 0.060582146048545837 0.20958836376667023 
		0.076448209583759308 1 1;
	setAttr -s 12 ".kiy[3:11]"  0 0 0 0 0.99816322326660156 0.97778975963592529 
		-0.99707353115081787 0 0;
	setAttr -s 12 ".kox[3:11]"  1 1 1 1 0.060582146048545837 0.20958836376667023 
		0.076448209583759308 1 1;
	setAttr -s 12 ".koy[3:11]"  0 0 0 0 0.99816322326660156 0.97778975963592529 
		-0.99707353115081787 0 0;
createNode animCurveTA -n "animCurveTA1550";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 1 -164.79875029151449 2 -151.35627704346362 
		4 -179.43235630586318 17 -176.27546630536861 21 -175.57855833217607 25 -179.43235630586318 
		26 -326.6019436100961 27 -272.43300456672262 28 -332.41958525935536 29 -186.09927606534595 
		30 -180.00000000000006;
	setAttr -s 12 ".kit[0:11]"  3 10 10 1 10 10 1 10 
		10 10 10 1;
	setAttr -s 12 ".kot[0:11]"  3 10 10 1 10 10 1 10 
		10 10 10 1;
	setAttr -s 12 ".kix[3:11]"  1 1 1 1 0.041037354618310928 0.54884636402130127 
		0.044200398027896881 0.025052685290575027 1;
	setAttr -s 12 ".kiy[3:11]"  0 0 0 0 -0.9991576075553894 -0.83592325448989868 
		0.99902266263961792 0.99968618154525757 0;
	setAttr -s 12 ".kox[3:11]"  1 1 1 1 0.041037354618310928 0.54884636402130127 
		0.044200398027896881 0.025052685290575027 1;
	setAttr -s 12 ".koy[3:11]"  0 0 0 0 -0.9991576075553894 -0.83592325448989868 
		0.99902266263961792 0.99968618154525757 0;
createNode animCurveTU -n "animCurveTU488";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0.71712508848813183 4 1 25 1 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU489";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL493";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.40930268174563 1 0.18768768817864401 
		4 0.30479054294452235 25 0.30479054294452235 30 0.40930268174563;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL494";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.25860394298924627 1 -0.35035924150265307 
		4 -0.56895678389721482 25 -0.56895678389721482 30 0.25860394298924627;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL495";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.29847095663485657 1 -0.016586321099043448 
		4 -0.026934925046430722 25 -0.026934925046430722 30 -0.29847095663485657;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1551";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 -99.667991152560347 4 -106.10069147585469 
		25 -106.10069147585469 27 -29.236820049092412 28 -37.34743247146799 30 0;
	setAttr -s 7 ".kit[0:6]"  3 10 1 1 10 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 1 1 10 10 1;
	setAttr -s 7 ".kix[2:6]"  1 1 0.08304750919342041 0.19231326878070831 
		1;
	setAttr -s 7 ".kiy[2:6]"  0 0 0.99654561281204224 0.98133355379104614 
		0;
	setAttr -s 7 ".kox[2:6]"  1 1 0.08304750919342041 0.19231326878070831 
		1;
	setAttr -s 7 ".koy[2:6]"  0 0 0.99654561281204224 0.98133355379104614 
		0;
createNode animCurveTA -n "animCurveTA1552";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 2.5032518326113373 4 4.7017575350877889 
		25 4.7017575350877889 27 9.5191965656035276 28 1.6550181680848697 30 0;
	setAttr -s 7 ".kit[0:6]"  3 10 1 1 10 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 1 1 10 10 1;
	setAttr -s 7 ".kix[2:6]"  1 1 0.88293051719665527 1 1;
	setAttr -s 7 ".kiy[2:6]"  0 0 -0.46950379014015198 0 0;
	setAttr -s 7 ".kox[2:6]"  1 1 0.88293051719665527 1 1;
	setAttr -s 7 ".koy[2:6]"  0 0 -0.46950379014015198 0 0;
createNode animCurveTA -n "animCurveTA1553";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 3.8613406334523548 4 6.3745549550027745 
		25 6.3745549550027745 27 111.10218942736894 28 2.2438426876021462 30 0;
	setAttr -s 7 ".kit[0:6]"  3 10 1 1 10 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 1 1 10 10 1;
	setAttr -s 7 ".kix[2:6]"  1 1 0.81117057800292969 1 1;
	setAttr -s 7 ".kiy[2:6]"  0 0 -0.58480948209762573 0 0;
	setAttr -s 7 ".kox[2:6]"  1 1 0.81117057800292969 1 1;
	setAttr -s 7 ".koy[2:6]"  0 0 -0.58480948209762573 0 0;
createNode animCurveTA -n "animCurveTA1554";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 25.675870473757751 1 30.595374286178881 
		4 13.363642600983988 25 13.363642600983988 28 21.341967530661591 30 25.675870473757751;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 0.612865149974823 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0.79018747806549072 0;
	setAttr -s 6 ".kox[2:5]"  1 1 0.612865149974823 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0.79018747806549072 0;
createNode animCurveTA -n "animCurveTA1555";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -3.0739741698828946 1 13.476135582578237 
		4 9.1823667640558462 25 9.1823667640558462 28 1.2402565764995159 30 -3.0739741698828951;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 0.6146056056022644 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 -0.78883451223373413 0;
	setAttr -s 6 ".kox[2:5]"  1 1 0.6146056056022644 1;
	setAttr -s 6 ".koy[2:5]"  0 0 -0.78883451223373413 0;
createNode animCurveTU -n "animCurveTU490";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 3 1 3 4 3 25 3 30 3;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU491";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU492";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 1 1 4 1 25 1 30 1;
	setAttr -s 5 ".kit[0:4]"  3 9 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 5 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU493";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1556";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 93.144161708979723 1 -21.510995947366457 
		4 -34.932222766976643 25 -34.932222766976643 30 93.144161708979723;
	setAttr -s 5 ".kit[0:4]"  9 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  9 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 0.31777191162109375;
	setAttr -s 5 ".kiy[2:4]"  0 0 -0.94816720485687256;
	setAttr -s 5 ".kox[2:4]"  1 1 0.31777191162109375;
	setAttr -s 5 ".koy[2:4]"  0 0 -0.94816720485687256;
createNode animCurveTA -n "animCurveTA1557";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 95.049826002206416 1 134.6915245551406 
		4 187.82152027859755 25 187.82152027859755 30 95.049826002206416;
	setAttr -s 5 ".kit[0:4]"  9 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  9 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 0.31202685832977295;
	setAttr -s 5 ".kiy[2:4]"  0 0 -0.9500732421875;
	setAttr -s 5 ".kox[2:4]"  1 1 0.31202685832977295;
	setAttr -s 5 ".koy[2:4]"  0 0 -0.9500732421875;
createNode animCurveTA -n "animCurveTA1558";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.1812364035166698 1 -27.193386996325334 
		4 -44.159994017410412 25 -44.159994017410412 30 1.1812364035166698;
	setAttr -s 5 ".kit[0:4]"  9 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  9 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 0.99928486347198486;
	setAttr -s 5 ".kiy[2:4]"  0 0 -0.037812888622283936;
	setAttr -s 5 ".kox[2:4]"  1 1 0.99928486347198486;
	setAttr -s 5 ".koy[2:4]"  0 0 -0.037812888622283936;
createNode animCurveTL -n "animCurveTL496";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.23689498628395578 1 0.45507832682116767 
		4 0.73901262070044915 25 0.73901262070044915 29 -0.078702552664778339 30 -0.23689498628395578;
	setAttr -s 6 ".kit[0:5]"  9 10 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  9 10 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 0.16834388673305511 0.91706329584121704;
	setAttr -s 6 ".kiy[2:5]"  0 0 -0.98572832345962524 0.39874157309532166;
	setAttr -s 6 ".kox[2:5]"  1 1 0.16834388673305511 0.91706329584121704;
	setAttr -s 6 ".koy[2:5]"  0 0 -0.98572832345962524 0.39874157309532166;
createNode animCurveTL -n "animCurveTL497";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.30633990936382105 1 0.035927604262727814 
		4 0.058343699132305325 25 0.058343699132305325 29 -0.23730107240037501 30 -0.30633990936382105;
	setAttr -s 6 ".kit[0:5]"  9 10 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  9 10 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 0.41566526889801025 0.87166357040405273;
	setAttr -s 6 ".kiy[2:5]"  0 0 -0.90951770544052124 0.49010470509529114;
	setAttr -s 6 ".kox[2:5]"  1 1 0.41566526889801025 0.87166357040405273;
	setAttr -s 6 ".koy[2:5]"  0 0 -0.90951770544052124 0.49010470509529114;
createNode animCurveTL -n "animCurveTL498";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.52899036848843184 1 0.54469780185042005 
		4 0.88454783783504309 25 0.88454783783504309 29 0.54557883611927427 30 0.52899036848843184;
	setAttr -s 6 ".kit[0:5]"  9 10 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  9 10 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 0.71746116876602173;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 -0.69659852981567383;
	setAttr -s 6 ".kox[2:5]"  1 1 1 0.71746116876602173;
	setAttr -s 6 ".koy[2:5]"  0 0 0 -0.69659852981567383;
createNode animCurveTU -n "animCurveTU494";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  9 9 1 1 1;
	setAttr -s 5 ".kot[0:4]"  9 5 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1559";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -24.884454396993167 1 -25.365837047134434 
		4 -40.045542970399922 25 -40.045542970399922 26 -43.091646621246994 30 -24.884454396993167;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 0.53295022249221802 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0.84614658355712891 0;
	setAttr -s 6 ".kox[2:5]"  1 1 0.53295022249221802 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0.84614658355712891 0;
createNode animCurveTA -n "animCurveTA1560";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -43.339475474578435 1 2.705596525304367 
		4 3.4984280518281916 25 3.4984280518281916 26 -5.9765970458168773 30 -43.339475474578435;
	setAttr -s 6 ".kit[1:5]"  10 1 1 10 1;
	setAttr -s 6 ".kot[1:5]"  10 1 1 10 1;
	setAttr -s 6 ".kix[0:5]"  0.96759837865829468 1 1 1 0.19977004826068878 
		0.97591996192932129;
	setAttr -s 6 ".kiy[0:5]"  -0.25249439477920532 0 0 0 -0.97984278202056885 
		-0.21812927722930908;
	setAttr -s 6 ".kox[0:5]"  0.96759837865829468 1 1 1 0.19977004826068878 
		0.97591996192932129;
	setAttr -s 6 ".koy[0:5]"  -0.25249442458152771 0 0 0 -0.97984278202056885 
		-0.21812930703163147;
createNode animCurveTA -n "animCurveTA1561";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 11.606559612787883 1 -1.2534781615484711 
		4 -6.283138691267415 25 -6.283138691267415 26 17.568671746640838 30 11.606559612787883;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 0.47090017795562744 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0.88218653202056885 0;
	setAttr -s 6 ".kox[2:5]"  1 1 0.47090017795562744 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0.88218653202056885 0;
createNode animCurveTU -n "animCurveTU495";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 9 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 5 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU496";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 9 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 5 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU497";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 1 4 1 25 1 26 0 30 0;
	setAttr -s 6 ".kit[0:5]"  9 3 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  9 3 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTU -n "animCurveTU498";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 9 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 5 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1562";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 3.9531091186723013 1 -32.682263660870227 
		4 -34.931558378024221 25 -34.931558378024221 28 11.78622083997967 30 3.9531091186723022;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 0.23849360644817352 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0.97114413976669312 0;
	setAttr -s 6 ".kox[2:5]"  1 1 0.23849360644817352 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0.97114413976669312 0;
createNode animCurveTA -n "animCurveTA1563";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.62018686761647346 1 5.2068733827808513 
		4 59.783587514726065 25 59.783587514726065 28 14.578483099776433 30 0.62018686761647335;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 0.15934324264526367 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 -0.98722320795059204 0;
	setAttr -s 6 ".kox[2:5]"  1 1 0.15934324264526367 1;
	setAttr -s 6 ".koy[2:5]"  0 0 -0.98722320795059204 0;
createNode animCurveTA -n "animCurveTA1564";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 5.3292188742882338 1 -10.345779738701511 
		4 -59.829478914740484 25 -59.829478914740484 28 22.596078835972001 30 5.3292188742882356;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 0.14500550925731659 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0.98943084478378296 0;
	setAttr -s 6 ".kox[2:5]"  1 1 0.14500550925731659 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0.98943084478378296 0;
createNode animCurveTU -n "animCurveTU499";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0.60325425572023383 2 0.99702165943543108 
		4 1 25 1 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 3 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 3 1 1 1;
	setAttr -s 6 ".kix[3:5]"  1 1 1;
	setAttr -s 6 ".kiy[3:5]"  0 0 0;
	setAttr -s 6 ".kox[3:5]"  1 1 1;
	setAttr -s 6 ".koy[3:5]"  0 0 0;
createNode animCurveTU -n "animCurveTU500";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 2 0 4 0 25 0 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 3 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 3 1 1 1;
	setAttr -s 6 ".kix[3:5]"  1 1 1;
	setAttr -s 6 ".kiy[3:5]"  0 0 0;
	setAttr -s 6 ".kox[3:5]"  1 1 1;
	setAttr -s 6 ".koy[3:5]"  0 0 0;
createNode animCurveTL -n "animCurveTL499";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 -0.76276375711302091 2 0.13125915003906677 
		4 -0.051232471008689773 25 -0.051232471008689773 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 3 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 3 1 1 1;
	setAttr -s 6 ".kix[3:5]"  1 1 1;
	setAttr -s 6 ".kiy[3:5]"  0 0 0;
	setAttr -s 6 ".kox[3:5]"  1 1 1;
	setAttr -s 6 ".koy[3:5]"  0 0 0;
createNode animCurveTL -n "animCurveTL500";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 -0.2344641680822819 2 0.28093170592456318 
		4 0.11600668093898568 25 0.11600668093898568 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 3 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 3 1 1 1;
	setAttr -s 6 ".kix[3:5]"  1 1 1;
	setAttr -s 6 ".kiy[3:5]"  0 0 0;
	setAttr -s 6 ".kox[3:5]"  1 1 1;
	setAttr -s 6 ".koy[3:5]"  0 0 0;
createNode animCurveTL -n "animCurveTL501";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0.06020536928084963 2 -0.2906484612073455 
		4 0.24479574736835913 25 0.24479574736835913 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 3 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 3 1 1 1;
	setAttr -s 6 ".kix[3:5]"  1 1 1;
	setAttr -s 6 ".kiy[3:5]"  0 0 0;
	setAttr -s 6 ".kox[3:5]"  1 1 1;
	setAttr -s 6 ".koy[3:5]"  0 0 0;
createNode animCurveTA -n "animCurveTA1565";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -44.757110789561033 1 -69.313613553404053 
		4 -96.654842836573295 25 -96.654842836573295 30 -44.757110789561033;
	setAttr -s 5 ".kit[1:4]"  10 1 1 1;
	setAttr -s 5 ".kot[1:4]"  10 1 1 1;
	setAttr -s 5 ".kix[0:4]"  0.78480303287506104 0.14563241600990295 
		1 1 0.82831525802612305;
	setAttr -s 5 ".kiy[0:4]"  -0.61974531412124634 -0.98933875560760498 
		0 0 -0.56026232242584229;
	setAttr -s 5 ".kox[0:4]"  0.78480309247970581 0.14563241600990295 
		1 1 0.82831525802612305;
	setAttr -s 5 ".koy[0:4]"  -0.61974519491195679 -0.98933875560760498 
		0 0 -0.56026214361190796;
createNode animCurveTA -n "animCurveTA1566";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 14 0 25 0 30 0;
	setAttr -s 4 ".kit[2:3]"  1 10;
	setAttr -s 4 ".kot[2:3]"  1 10;
	setAttr -s 4 ".kix[2:3]"  1 1;
	setAttr -s 4 ".kiy[2:3]"  0 0;
	setAttr -s 4 ".kox[2:3]"  1 1;
	setAttr -s 4 ".koy[2:3]"  0 0;
createNode animCurveTA -n "animCurveTA1567";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 14 0 25 0 30 0;
	setAttr -s 4 ".kit[2:3]"  1 10;
	setAttr -s 4 ".kot[2:3]"  1 10;
	setAttr -s 4 ".kix[2:3]"  1 1;
	setAttr -s 4 ".kiy[2:3]"  0 0;
	setAttr -s 4 ".kox[2:3]"  1 1;
	setAttr -s 4 ".koy[2:3]"  0 0;
createNode animCurveTA -n "animCurveTA1568";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -27.604588158357807 1 -2.7998996552579913 
		4 -4.5468242717338008 25 -4.5468242717338008 30 -27.604588158357807;
	setAttr -s 5 ".kit[0:4]"  9 10 1 1 3;
	setAttr -s 5 ".kot[0:4]"  9 10 1 1 3;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1569";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.70641431476594085 1 5.0581351993315193 
		4 6.5341541089456596 25 6.5341541089456596 30 0.70641431476594085;
	setAttr -s 5 ".kit[1:4]"  10 1 1 3;
	setAttr -s 5 ".kot[1:4]"  10 1 1 3;
	setAttr -s 5 ".kix[0:4]"  0.98481625318527222 1 1 1 1;
	setAttr -s 5 ".kiy[0:4]"  0.17360018193721771 0 0 0 0;
	setAttr -s 5 ".kox[0:4]"  0.98481625318527222 1 1 1 1;
	setAttr -s 5 ".koy[0:4]"  0.17360010743141174 0 0 0 0;
createNode animCurveTU -n "animCurveTU501";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 1 25 1 30 0;
	setAttr -s 5 ".kit[0:4]"  3 9 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 5 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU502";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 3 1 3 4 3 25 3 30 3;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU503";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU504";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 1 1 4 1 25 1 30 1;
	setAttr -s 5 ".kit[0:4]"  3 9 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 5 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU505";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1570";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 11.326093106149948 3 15.387665928897947 
		4 83.142870900408028 25 83.142870900408028 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 10 1 1 1;
	setAttr -s 6 ".kix[3:5]"  1 1 1;
	setAttr -s 6 ".kiy[3:5]"  0 0 0;
	setAttr -s 6 ".kox[3:5]"  1 1 1;
	setAttr -s 6 ".koy[3:5]"  0 0 0;
createNode animCurveTA -n "animCurveTA1571";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 -7.9418521858311557 3 128.9548548630442 
		4 70.074940345729459 25 70.074940345729459 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 10 1 1 1;
	setAttr -s 6 ".kix[3:5]"  1 1 1;
	setAttr -s 6 ".kiy[3:5]"  0 0 0;
	setAttr -s 6 ".kox[3:5]"  1 1 1;
	setAttr -s 6 ".koy[3:5]"  0 0 0;
createNode animCurveTA -n "animCurveTA1572";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 34.778816435530423 3 12.547378581462191 
		4 62.862804771158565 25 62.862804771158565 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 10 1 1 1;
	setAttr -s 6 ".kix[3:5]"  1 1 1;
	setAttr -s 6 ".kiy[3:5]"  0 0 0;
	setAttr -s 6 ".kox[3:5]"  1 1 1;
	setAttr -s 6 ".koy[3:5]"  0 0 0;
createNode animCurveTL -n "animCurveTL502";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 -0.13943332605469302 3 -1.1418340667373801 
		4 -0.84551914312642307 25 -0.84551914312642307 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 10 1 1 1;
	setAttr -s 6 ".kix[3:5]"  1 1 1;
	setAttr -s 6 ".kiy[3:5]"  0 0 0;
	setAttr -s 6 ".kox[3:5]"  1 1 1;
	setAttr -s 6 ".koy[3:5]"  0 0 0;
createNode animCurveTL -n "animCurveTL503";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0.064473956236704669 3 -0.30772937620699209 
		4 0.88192585055613415 25 0.88192585055613415 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 10 1 1 1;
	setAttr -s 6 ".kix[3:5]"  1 1 1;
	setAttr -s 6 ".kiy[3:5]"  0 0 0;
	setAttr -s 6 ".kox[3:5]"  1 1 1;
	setAttr -s 6 ".koy[3:5]"  0 0 0;
createNode animCurveTL -n "animCurveTL504";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0.1337664508683524 3 -0.47157577305448772 
		4 -0.25650261215412329 25 -0.25650261215412329 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 10 1 1 1;
	setAttr -s 6 ".kix[3:5]"  1 1 1;
	setAttr -s 6 ".kiy[3:5]"  0 0 0;
	setAttr -s 6 ".kox[3:5]"  1 1 1;
	setAttr -s 6 ".koy[3:5]"  0 0 0;
createNode animCurveTU -n "animCurveTU506";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 4 1 8 1 25 1 30 1;
	setAttr -s 5 ".kit[0:4]"  9 1 10 1 1;
	setAttr -s 5 ".kot[0:4]"  9 1 10 1 1;
	setAttr -s 5 ".kix[1:4]"  1 1 1 1;
	setAttr -s 5 ".kiy[1:4]"  0 0 0 0;
	setAttr -s 5 ".kox[1:4]"  1 1 1 1;
	setAttr -s 5 ".koy[1:4]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1573";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1.1288109940741509 4 4.0635247822381206 
		8 5.4453593419844122 19 1.9932425935314799 25 4.0635247822381206 30 1.1288109940741509;
	setAttr -s 6 ".kit[0:5]"  3 1 10 10 1 1;
	setAttr -s 6 ".kot[0:5]"  3 1 10 10 1 1;
	setAttr -s 6 ".kix[1:5]"  0.98954695463180542 1 1 0.996024489402771 
		1;
	setAttr -s 6 ".kiy[1:5]"  0.14421133697032928 0 0 0.089080192148685455 
		0;
	setAttr -s 6 ".kox[1:5]"  0.98954695463180542 1 1 0.996024489402771 
		1;
	setAttr -s 6 ".koy[1:5]"  0.14421135187149048 0 0 0.089080207049846649 
		0;
createNode animCurveTA -n "animCurveTA1574";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 4.8219581414201906 4 -12.100209285499583 
		8 -14.131133020296311 19 -8.5234725026455891 25 -12.100209285499583 30 4.8219581414201906;
	setAttr -s 6 ".kit[0:5]"  3 1 10 10 1 1;
	setAttr -s 6 ".kot[0:5]"  3 1 10 10 1 1;
	setAttr -s 6 ".kix[1:5]"  0.93675905466079712 1 0.99804937839508057 
		0.98895519971847534 1;
	setAttr -s 6 ".kiy[1:5]"  -0.34997507929801941 0 0.062430296093225479 
		-0.14821501076221466 0;
	setAttr -s 6 ".kox[1:5]"  0.93675905466079712 1 0.99804937839508057 
		0.98895519971847534 1;
	setAttr -s 6 ".koy[1:5]"  -0.34997504949569702 0 0.062430296093225479 
		-0.14821501076221466 0;
createNode animCurveTA -n "animCurveTA1575";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 28.08558650754679 4 -1.6056933583577964 
		8 3.7747390159002765 19 6.6999780693142243 25 -1.6056933583577964 30 28.08558650754679;
	setAttr -s 6 ".kit[0:5]"  3 1 10 10 1 1;
	setAttr -s 6 ".kot[0:5]"  3 1 10 10 1 1;
	setAttr -s 6 ".kix[1:5]"  1 0.96044903993606567 0.98654550313949585 
		1 1;
	setAttr -s 6 ".kiy[1:5]"  0 0.27845591306686401 -0.16348730027675629 
		0 0;
	setAttr -s 6 ".kox[1:5]"  1 0.96044903993606567 0.98654550313949585 
		1 1;
	setAttr -s 6 ".koy[1:5]"  0 0.27845591306686401 -0.16348730027675629 
		0 0;
createNode animCurveTU -n "animCurveTU507";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1576";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 68.629003384766676 1 18.881008631250989 
		4 0 25 0 30 68.629003384766676;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1577";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 5.1251585428584878 1 0 4 0 25 0 30 5.1251585428584878;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1578";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.4794141658124507 1 0 4 0 25 0 30 -1.4794141658124507;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1579";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 2.9967431843380723 1 7.8228153835569314 
		4 7.0339948367446494 25 7.0339948367446494 30 2.9967431843380723;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1580";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 27.356153209428296 1 21.459069048681055 
		4 29.218826525027897 25 29.218826525027897 30 27.356153209428296;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1581";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 4.8891453517792058 1 18.61304014025232 
		4 34.963222422573708 25 34.963222422573708 30 4.8891453517792058;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU508";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 27 0 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1582";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 59.032884886088816 1 41.762547175586739 
		4 23.403108553694622 25 23.403108553694622 27 23.403108553694622 30 59.032884886088816;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1583";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 27 0 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1584";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 27 0 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1585";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 61.945270723308987 1 23.308143269554346 
		4 12.009863808886353 25 12.009863808886353 27 12.009863808886353 30 61.945270723308987;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1586";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 27 0 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1587";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 27 0 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTU -n "animCurveTU509";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 27 0 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1588";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 59.032884886088816 1 32.093178513427333 
		4 16.671836397265952 25 16.671836397265952 27 16.671836397265952 30 59.032884886088816;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1589";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 2.2172427326362611 4 3.6006337063343792 
		25 3.6006337063343792 27 3.6006337063343792 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1590";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 -2.6987123360871395 4 -4.3825037547703767 
		25 -4.3825037547703767 27 -4.3825037547703767 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1591";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 61.945270723308987 1 15.104974921432856 
		4 -1.3114582178919605 25 -1.3114582178919605 27 -1.3114582178919605 30 61.945270723308987;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1592";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 27 0 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1593";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 27 0 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTU -n "animCurveTU510";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 1 0 4 0 8 0 14 0 19 0 23 0 25 0 27 
		0 30 0;
	setAttr -s 10 ".kit[0:9]"  3 10 1 10 1 1 1 1 
		1 1;
	setAttr -s 10 ".kot[0:9]"  3 10 1 10 1 1 1 1 
		1 1;
	setAttr -s 10 ".kix[2:9]"  1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[2:9]"  0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[2:9]"  1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[2:9]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1594";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 59.032884886088816 1 54.178763134464432 
		4 43.566099744788517 8 43.566099744788517 11 9.0770047558156666 14 43.566099744788517 
		17 9.0770047558156666 19 43.566099744788517 21 9.0770047558156666 23 43.566099744788517 
		25 43.566099744788517 27 43.566099744788517 30 59.032884886088816;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 1 1 1 
		1 1 1 1 1;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 1 1 1 
		1 1 1 1 1;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1595";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 1 0 4 0 8 0 14 0 19 0 23 0 25 0 27 
		0 30 0;
	setAttr -s 10 ".kit[0:9]"  3 10 1 10 1 1 1 1 
		1 1;
	setAttr -s 10 ".kot[0:9]"  3 10 1 10 1 1 1 1 
		1 1;
	setAttr -s 10 ".kix[2:9]"  1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[2:9]"  0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[2:9]"  1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[2:9]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1596";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 1 0 4 0 8 0 14 0 19 0 23 0 25 0 27 
		0 30 0;
	setAttr -s 10 ".kit[0:9]"  3 10 1 10 1 1 1 1 
		1 1;
	setAttr -s 10 ".kot[0:9]"  3 10 1 10 1 1 1 1 
		1 1;
	setAttr -s 10 ".kix[2:9]"  1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[2:9]"  0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[2:9]"  1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[2:9]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1597";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 72.878304588436421 1 28.370321315577556 
		4 20.230456273431468 8 20.230456273431468 11 -14.25863871554138 14 20.230456273431468 
		17 -14.25863871554138 19 20.230456273431468 21 -14.25863871554138 23 20.230456273431468 
		25 20.230456273431468 27 20.230456273431468 30 72.878304588436421;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 1 1 1 
		1 1 1 1 1;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 1 1 1 
		1 1 1 1 1;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1598";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 1 0 4 0 8 0 14 0 19 0 23 0 25 0 27 
		0 30 0;
	setAttr -s 10 ".kit[0:9]"  3 10 1 10 1 1 1 1 
		1 1;
	setAttr -s 10 ".kot[0:9]"  3 10 1 10 1 1 1 1 
		1 1;
	setAttr -s 10 ".kix[2:9]"  1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[2:9]"  0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[2:9]"  1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[2:9]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1599";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 1 0 4 0 8 0 14 0 19 0 23 0 25 0 27 
		0 30 0;
	setAttr -s 10 ".kit[0:9]"  3 10 1 10 1 1 1 1 
		1 1;
	setAttr -s 10 ".kot[0:9]"  3 10 1 10 1 1 1 1 
		1 1;
	setAttr -s 10 ".kix[2:9]"  1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[2:9]"  0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[2:9]"  1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[2:9]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU511";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 1 0 4 0 11 0 17 0 21 0 25 0 27 0 30 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 1 3 3 1 1 1 
		1;
	setAttr -s 9 ".kot[0:8]"  3 10 1 3 3 3 1 1 
		1;
	setAttr -s 9 ".kix[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[2:8]"  0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[2:8]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1600";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 77.67986202714836 1 58.377096446541891 
		4 50.38387400621054 8 12.695338100108387 11 50.38387400621054 14 12.695338100108387 
		17 50.38387400621054 19 12.695338100108387 21 50.38387400621054 25 50.38387400621054 
		27 50.38387400621054 30 77.67986202714836;
	setAttr -s 12 ".kit[1:11]"  10 1 3 3 3 3 3 1 
		1 1 1;
	setAttr -s 12 ".kot[1:11]"  10 1 3 3 3 3 3 3 
		1 1 1;
	setAttr -s 12 ".kix[2:11]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[2:11]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[2:11]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[2:11]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1601";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 1 0 4 0 11 0 17 0 21 0 25 0 27 0 30 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 1 3 3 1 1 1 
		1;
	setAttr -s 9 ".kot[0:8]"  3 10 1 3 3 3 1 1 
		1;
	setAttr -s 9 ".kix[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[2:8]"  0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[2:8]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1602";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 1 0 4 0 11 0 17 0 21 0 25 0 27 0 30 
		0;
	setAttr -s 9 ".kit[0:8]"  3 10 1 3 3 1 1 1 
		1;
	setAttr -s 9 ".kot[0:8]"  3 10 1 3 3 3 1 1 
		1;
	setAttr -s 9 ".kix[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[2:8]"  0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[2:8]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1603";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 65.952779168408995 1 34.940488161042929 
		4 20.230456273431468 8 -17.458079632670703 11 20.230456273431468 14 -17.458079632670703 
		17 20.230456273431468 19 -17.458079632670703 21 20.230456273431468 25 20.230456273431468 
		27 20.230456273431468 30 65.952779168408995;
	setAttr -s 12 ".kit[1:11]"  10 1 3 3 3 3 3 1 
		1 1 1;
	setAttr -s 12 ".kot[1:11]"  10 1 3 3 3 3 3 3 
		1 1 1;
	setAttr -s 12 ".kix[2:11]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[2:11]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[2:11]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[2:11]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1604";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 12.091864976351665 1 0 4 0 11 0 17 0 
		21 0 25 0 27 0 30 12.091864976351665;
	setAttr -s 9 ".kit[0:8]"  3 10 1 3 3 1 1 1 
		1;
	setAttr -s 9 ".kot[0:8]"  3 10 1 3 3 3 1 1 
		1;
	setAttr -s 9 ".kix[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[2:8]"  0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[2:8]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1605";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -6.5683373417752975 1 0 4 0 11 0 17 0 
		21 0 25 0 27 0 30 -6.5683373417752975;
	setAttr -s 9 ".kit[0:8]"  3 10 1 3 3 1 1 1 
		1;
	setAttr -s 9 ".kot[0:8]"  3 10 1 3 3 3 1 1 
		1;
	setAttr -s 9 ".kix[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[2:8]"  0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[2:8]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1606";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 -4.2796889674878678 25 -4.2796889674878678 
		30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1607";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 8.883005900984065 25 8.883005900984065 
		30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1608";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 13.701884762541479 25 13.701884762541479 
		30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU512";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1609";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 4.3501408210499193 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1610";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1611";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1612";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 4.709285869680949 2 1.0521458932675016 
		4 -1.3338411325848583 25 -1.3338411325848583 26 -4.3720847054207228 30 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 1 1 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 10 1 1 10 1;
	setAttr -s 7 ".kix[3:6]"  1 1 0.99038529396057129 1;
	setAttr -s 7 ".kiy[3:6]"  0 0 0.13833652436733246 0;
	setAttr -s 7 ".kox[3:6]"  1 1 0.99038529396057129 1;
	setAttr -s 7 ".koy[3:6]"  0 0 0.13833652436733246 0;
createNode animCurveTA -n "animCurveTA1613";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 29.704197978361123 2 -3.9609513539090249 
		4 46.088304197029217 25 46.088304197029217 26 -9.5516953021394233 30 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 1 1 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 10 1 1 10 1;
	setAttr -s 7 ".kix[3:6]"  1 1 0.20288649201393127 1;
	setAttr -s 7 ".kiy[3:6]"  0 0 -0.97920233011245728 0;
	setAttr -s 7 ".kox[3:6]"  1 1 0.20288649201393127 1;
	setAttr -s 7 ".koy[3:6]"  0 0 -0.97920233011245728 0;
createNode animCurveTA -n "animCurveTA1614";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 51.03538573076694 2 5.9085376182609153 
		4 65.441815686464849 25 65.441815686464849 26 58.547389740926171 30 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 1 1 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 10 1 1 10 1;
	setAttr -s 7 ".kix[3:6]"  1 1 0.144391268491745 1;
	setAttr -s 7 ".kiy[3:6]"  0 0 -0.98952066898345947 0;
	setAttr -s 7 ".kox[3:6]"  1 1 0.144391268491745 1;
	setAttr -s 7 ".koy[3:6]"  0 0 -0.98952066898345947 0;
createNode animCurveTU -n "animCurveTU513";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1615";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 38.802807435000226 2 13.904727043973011 
		4 50.803231417526469 25 50.803231417526469 26 -16.696146687524603 30 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 1 1 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 10 1 1 10 1;
	setAttr -s 7 ".kix[3:6]"  1 1 0.18473127484321594 1;
	setAttr -s 7 ".kiy[3:6]"  0 0 -0.98278909921646118 0;
	setAttr -s 7 ".kox[3:6]"  1 1 0.18473127484321594 1;
	setAttr -s 7 ".koy[3:6]"  0 0 -0.98278909921646118 0;
createNode animCurveTA -n "animCurveTA1616";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 26 1.2912829130413934 
		30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1617";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 26 -0.0048098420035463775 
		30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1618";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 -1.3851339776789451 2 -37.146556177401685 
		4 -9.5133584819852928 25 -9.5133584819852928 26 -34.069859743217762 30 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 1 1 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 10 1 1 10 1;
	setAttr -s 7 ".kix[3:6]"  1 1 0.70843863487243652 1;
	setAttr -s 7 ".kiy[3:6]"  0 0 0.70577239990234375 0;
	setAttr -s 7 ".kox[3:6]"  1 1 0.70843863487243652 1;
	setAttr -s 7 ".koy[3:6]"  0 0 0.70577239990234375 0;
createNode animCurveTA -n "animCurveTA1619";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 -1.457826974658097 4 -2.3674002244744461 
		25 -2.3674002244744461 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1620";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 -6.6016009424021549 4 -10.720498265302675 
		25 -10.720498265302675 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU514";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1621";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 4.9179905203215561 2 -31.575273364567366 
		4 -4.2231362958981356 25 -4.2231362958981356 26 -27.345886386679172 30 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 1 1 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 10 1 1 10 1;
	setAttr -s 7 ".kix[3:6]"  1 1 0.91455626487731934 1;
	setAttr -s 7 ".kiy[3:6]"  0 0 0.40445861220359802 0;
	setAttr -s 7 ".kox[3:6]"  1 1 0.91455626487731934 1;
	setAttr -s 7 ".koy[3:6]"  0 0 0.40445861220359802 0;
createNode animCurveTA -n "animCurveTA1622";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 26 -6.3527789127207983 
		30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1623";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 26 -20.516100309138157 
		30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1624";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 11.394592307835506 2 -23.462882339482796 
		4 11.239945855893694 25 11.239945855893694 26 -15.474901906511207 30 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 1 1 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 10 1 1 10 1;
	setAttr -s 7 ".kix[3:6]"  1 1 0.64746510982513428 1;
	setAttr -s 7 ".kiy[3:6]"  0 0 -0.76209509372711182 0;
	setAttr -s 7 ".kox[3:6]"  1 1 0.64746510982513428 1;
	setAttr -s 7 ".koy[3:6]"  0 0 -0.76209509372711182 0;
createNode animCurveTA -n "animCurveTA1625";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 2 -17.632205150681017 4 0 25 0 
		30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 10 1 1 1;
	setAttr -s 6 ".kix[3:5]"  1 1 1;
	setAttr -s 6 ".kiy[3:5]"  0 0 0;
	setAttr -s 6 ".kox[3:5]"  1 1 1;
	setAttr -s 6 ".koy[3:5]"  0 0 0;
createNode animCurveTA -n "animCurveTA1626";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 2 -7.4899382495520914 4 0 25 0 
		30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 10 1 1 1;
	setAttr -s 6 ".kix[3:5]"  1 1 1;
	setAttr -s 6 ".kiy[3:5]"  0 0 0;
	setAttr -s 6 ".kox[3:5]"  1 1 1;
	setAttr -s 6 ".koy[3:5]"  0 0 0;
createNode animCurveTU -n "animCurveTU515";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1627";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 42.985783046811157 2 19.519092383545317 
		4 57.596065940769414 25 57.596065940769414 26 -20.698308801560437 30 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 1 1 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 10 1 1 10 1;
	setAttr -s 7 ".kix[3:6]"  1 1 0.16356487572193146 1;
	setAttr -s 7 ".kiy[3:6]"  0 0 -0.98653256893157959 0;
	setAttr -s 7 ".kox[3:6]"  1 1 0.16356487572193146 1;
	setAttr -s 7 ".koy[3:6]"  0 0 -0.98653256893157959 0;
createNode animCurveTA -n "animCurveTA1628";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 26 1.2834929849455694 
		30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1629";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 26 -0.14171735716763528 
		30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1630";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 4.4731195069887804 2 -30.340682878614658 
		4 0 25 0 26 -25.60991126870384 30 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 1 1 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 10 1 1 10 1;
	setAttr -s 7 ".kix[3:6]"  1 1 1 1;
	setAttr -s 7 ".kiy[3:6]"  0 0 0 0;
	setAttr -s 7 ".kox[3:6]"  1 1 1 1;
	setAttr -s 7 ".koy[3:6]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1631";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 26 -3.913418462516431 
		30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1632";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 26 -1.8737020011686354 
		30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTU -n "animCurveTU516";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1633";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 66.941101049888871 2 47.645727138816959 
		4 85.62734520086515 25 85.62734520086515 26 -1.8728609081878462 30 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 1 1 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 10 1 1 10 1;
	setAttr -s 7 ".kix[3:6]"  1 1 1 1;
	setAttr -s 7 ".kiy[3:6]"  0 0 0 0;
	setAttr -s 7 ".kox[3:6]"  1 1 1 1;
	setAttr -s 7 ".koy[3:6]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1634";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 4.0861711619335068 4 6.6356314529514968 
		25 6.6356314529514968 26 7.0470847118632731 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1635";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 -0.76475616636152355 4 -1.241905899249188 
		25 -1.241905899249188 26 -1.7909083856016477 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1636";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 4.4731195069887804 2 -30.340682878614658 
		4 0 25 0 26 -25.545891849820098 30 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 1 1 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 10 1 1 10 1;
	setAttr -s 7 ".kix[3:6]"  1 1 1 1;
	setAttr -s 7 ".kiy[3:6]"  0 0 0 0;
	setAttr -s 7 ".kox[3:6]"  1 1 1 1;
	setAttr -s 7 ".koy[3:6]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1637";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1638";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1639";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1640";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1641";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU517";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 9 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 5 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU518";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 9 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 5 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU519";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 1 1 4 1 25 1 30 1;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1642";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -10.173354040024311 1 -10.173354040024311 
		4 -0.86377732513172101 25 -0.86377732513172101 30 -10.173354040024311;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1643";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 9.3755748860878221 25 9.3755748860878221 
		30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1644";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 66.475394773543286 25 66.475394773543286 
		30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL505";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0.52009433893713641 25 0.52009433893713641 
		30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL506";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.643246524321337 1 0.643246524321337 
		4 0.40064553909449413 25 0.40064553909449413 30 0.643246524321337;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL507";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.10481400598920043 1 0.10481400598920043 
		4 0.15143327037911147 25 0.15143327037911147 30 0.10481400598920043;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1645";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1646";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1647";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU520";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1648";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1649";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1650";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1651";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1652";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1653";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1654";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1655";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1656";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU521";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 4 1 8 1 25 1 30 1;
	setAttr -s 5 ".kit[0:4]"  3 1 10 1 1;
	setAttr -s 5 ".kot[0:4]"  3 1 10 1 1;
	setAttr -s 5 ".kix[1:4]"  1 1 1 1;
	setAttr -s 5 ".kiy[1:4]"  0 0 0 0;
	setAttr -s 5 ".kox[1:4]"  1 1 1 1;
	setAttr -s 5 ".koy[1:4]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1657";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 40.718223104721211 4 0.21102783354584345 
		8 0.39205606839981311 25 0.21102783354584345 30 40.718223104721211;
	setAttr -s 5 ".kit[0:4]"  3 1 10 1 1;
	setAttr -s 5 ".kot[0:4]"  3 1 10 1 1;
	setAttr -s 5 ".kix[1:4]"  1 1 1 1;
	setAttr -s 5 ".kiy[1:4]"  0 0 0 0;
	setAttr -s 5 ".kox[1:4]"  1 1 1 1;
	setAttr -s 5 ".koy[1:4]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1658";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -38.301705751263519 4 1.4028404017653284 
		8 -7.916476499646695 25 1.4028404017653284 30 -38.301705751263519;
	setAttr -s 5 ".kit[0:4]"  3 1 10 1 1;
	setAttr -s 5 ".kot[0:4]"  3 1 10 1 1;
	setAttr -s 5 ".kix[1:4]"  1 1 1 1;
	setAttr -s 5 ".kiy[1:4]"  0 0 0 0;
	setAttr -s 5 ".kox[1:4]"  1 1 1 1;
	setAttr -s 5 ".koy[1:4]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1659";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 21.733945627788874 4 -0.89067137950329778 
		8 -3.6302006144686487 25 -0.89067137950329778 30 21.733945627788874;
	setAttr -s 5 ".kit[0:4]"  3 1 10 1 1;
	setAttr -s 5 ".kot[0:4]"  3 1 10 1 1;
	setAttr -s 5 ".kix[1:4]"  1 1 1 1;
	setAttr -s 5 ".kiy[1:4]"  0 0 0 0;
	setAttr -s 5 ".kox[1:4]"  1 1 1 1;
	setAttr -s 5 ".koy[1:4]"  0 0 0 0;
createNode animCurveTU -n "animCurveTU522";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 9 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 5 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU523";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 9 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 5 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU524";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 1 1 4 1 25 1 30 1;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1660";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 17.962181958626559 1 17.962181958626559 
		4 17.962181958626559 25 17.962181958626559 30 17.962181958626559;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1661";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1662";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL508";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL509";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.64789329560123088 1 -0.64789329560123088 
		4 -0.64789329560123088 25 -0.64789329560123088 30 -0.64789329560123088;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL510";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.07395615046270454 1 -0.07395615046270454 
		4 -0.07395615046270454 25 -0.07395615046270454 30 -0.07395615046270454;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1663";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1664";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1665";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU525";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1666";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1667";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1668";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1669";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1670";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1671";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1672";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1673";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1674";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1675";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -10.753373031419716 4 -26.175651763703058 
		8 -28.400214641487747 19 -24.134000171745235 25 -26.175651763703058 30 -10.753373031419716;
	setAttr -s 6 ".kit[0:5]"  9 1 9 10 1 1;
	setAttr -s 6 ".kot[0:5]"  9 1 9 10 1 1;
	setAttr -s 6 ".kix[1:5]"  0.95487356185913086 0.99747014045715332 
		1 0.9818340539932251 0.9938805103302002;
	setAttr -s 6 ".kiy[1:5]"  -0.29701277613639832 0.071086786687374115 
		0 -0.18974177539348602 -0.11046028137207031;
	setAttr -s 6 ".kox[1:5]"  0.95487356185913086 0.99747014045715332 
		1 0.9818340539932251 0.9938805103302002;
	setAttr -s 6 ".koy[1:5]"  -0.29701277613639832 0.071086786687374115 
		0 -0.18974176049232483 -0.11046028137207031;
createNode animCurveTA -n "animCurveTA1676";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -4.9387346018875373 4 -4.5585796299862027 
		8 -8.8436243885853028 19 -0.21506643383436586 25 -4.5585796299862027 30 -4.9387346018875373;
	setAttr -s 6 ".kit[2:5]"  3 3 1 1;
	setAttr -s 6 ".kot[2:5]"  3 3 1 1;
	setAttr -s 6 ".kix[0:5]"  0.99992257356643677 0.96137261390686035 
		1 1 0.92759203910827637 0.99994325637817383;
	setAttr -s 6 ".kiy[0:5]"  0.012444101274013519 -0.27525043487548828 
		0 0 -0.37359476089477539 0.010658980347216129;
	setAttr -s 6 ".kox[0:5]"  0.99992257356643677 0.96137255430221558 
		1 1 0.92759209871292114 0.99994325637817383;
	setAttr -s 6 ".koy[0:5]"  0.012444097548723221 -0.27525046467781067 
		0 0 -0.373594731092453 0.010658976621925831;
createNode animCurveTA -n "animCurveTA1677";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 22.393157938684443 4 2.0861474592408418 
		8 2.3866377352949018 19 1.3419446957226928 25 2.0861474592408418 30 22.393157938684443;
	setAttr -s 6 ".kit[0:5]"  9 1 1 10 1 1;
	setAttr -s 6 ".kot[0:5]"  9 1 1 10 1 1;
	setAttr -s 6 ".kix[1:5]"  1 0.99033647775650024 1 1 0.60239154100418091;
	setAttr -s 6 ".kiy[1:5]"  0 -0.13868546485900879 0 0 -0.79820066690444946;
	setAttr -s 6 ".kox[1:5]"  1 0.99033653736114502 1 1 0.60239154100418091;
	setAttr -s 6 ".koy[1:5]"  0 -0.13868549466133118 0 0 -0.79820066690444946;
createNode animCurveTA -n "animCurveTA1678";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -4.0865779949808214 4 -27.48419219117255 
		18 -29.126871422469886 25 -27.48419219117255 30 -4.0865779949808214;
	setAttr -s 5 ".kit[0:4]"  3 1 10 1 1;
	setAttr -s 5 ".kot[0:4]"  3 1 10 1 1;
	setAttr -s 5 ".kix[1:4]"  1 1 1 1;
	setAttr -s 5 ".kiy[1:4]"  0 0 0 0;
	setAttr -s 5 ".kox[1:4]"  1 1 1 1;
	setAttr -s 5 ".koy[1:4]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1679";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -10.471027640707172 4 4.4740808567273787 
		18 3.4400482475454388 25 4.4740808567273787 30 -10.471027640707172;
	setAttr -s 5 ".kit[0:4]"  3 1 10 1 1;
	setAttr -s 5 ".kot[0:4]"  3 1 10 1 1;
	setAttr -s 5 ".kix[1:4]"  1 1 1 1;
	setAttr -s 5 ".kiy[1:4]"  0 0 0 0;
	setAttr -s 5 ".kox[1:4]"  1 1 1 1;
	setAttr -s 5 ".koy[1:4]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1680";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.7475532445702493 4 -6.817085379917005 
		18 -11.183289235744859 25 -6.817085379917005 30 -1.7475532445702493;
	setAttr -s 5 ".kit[0:4]"  3 1 10 1 1;
	setAttr -s 5 ".kot[0:4]"  3 1 10 1 1;
	setAttr -s 5 ".kix[1:4]"  1 1 1 1;
	setAttr -s 5 ".kiy[1:4]"  0 0 0 0;
	setAttr -s 5 ".kox[1:4]"  1 1 1 1;
	setAttr -s 5 ".koy[1:4]"  0 0 0 0;
createNode animCurveTU -n "animCurveTU526";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 4 1 8 1 25 1 30 1;
	setAttr -s 5 ".kit[0:4]"  3 1 10 1 1;
	setAttr -s 5 ".kot[0:4]"  3 1 10 1 1;
	setAttr -s 5 ".kix[1:4]"  1 1 1 1;
	setAttr -s 5 ".kiy[1:4]"  0 0 0 0;
	setAttr -s 5 ".kox[1:4]"  1 1 1 1;
	setAttr -s 5 ".koy[1:4]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1681";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 20.69101533741409 4 0.37998941617523435 
		8 -0.078468617291328327 19 -8.4929104202566954 25 0.37998941617523435 30 20.69101533741409;
	setAttr -s 6 ".kit[0:5]"  3 1 10 10 1 1;
	setAttr -s 6 ".kot[0:5]"  3 1 10 10 1 1;
	setAttr -s 6 ".kix[1:5]"  1 1 0.99990034103393555 1 1;
	setAttr -s 6 ".kiy[1:5]"  0 0 0.014119069091975689 0 0;
	setAttr -s 6 ".kox[1:5]"  1 1 0.99990034103393555 1 1;
	setAttr -s 6 ".koy[1:5]"  0 0 0.014119069091975689 0 0;
createNode animCurveTA -n "animCurveTA1682";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -8.3978566024888135 4 -6.4366856164795321 
		8 -13.869574206242925 19 11.891159798141986 25 -6.4366856164795321 30 -8.3978566024888135;
	setAttr -s 6 ".kit[0:5]"  3 1 10 10 1 1;
	setAttr -s 6 ".kot[0:5]"  3 1 10 10 1 1;
	setAttr -s 6 ".kix[1:5]"  1 0.84236222505569458 0.97478193044662476 
		1 1;
	setAttr -s 6 ".kiy[1:5]"  0 0.53891181945800781 0.22315922379493713 
		0 0;
	setAttr -s 6 ".kox[1:5]"  1 0.84236222505569458 0.97478193044662476 
		1 1;
	setAttr -s 6 ".koy[1:5]"  0 0.53891181945800781 0.22315922379493713 
		0 0;
createNode animCurveTA -n "animCurveTA1683";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 2.8255796210686652 4 -1.5753599557041278 
		8 -4.6622382257816835 19 -5.2368316526437102 25 -1.5753599557041278 30 2.8255796210686652;
	setAttr -s 6 ".kit[0:5]"  3 1 10 10 1 1;
	setAttr -s 6 ".kot[0:5]"  3 1 10 10 1 1;
	setAttr -s 6 ".kix[1:5]"  1 1 1 1 1;
	setAttr -s 6 ".kiy[1:5]"  0 0 0 0 0;
	setAttr -s 6 ".kox[1:5]"  1 1 1 1 1;
	setAttr -s 6 ".koy[1:5]"  0 0 0 0 0;
createNode animCurveTU -n "animCurveTU527";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 4 0 10 0 16 0 25 0 30 0;
	setAttr -s 7 ".kit[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kot[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kix[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".kiy[2:6]"  0 0 0 0 0;
	setAttr -s 7 ".kox[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".koy[2:6]"  0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1684";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 1 0 4 0.59256571541536207 10 13.247980762875626 
		16 8.9214414679838772 25 0.59256571541536207 27 1.6314456591286159 30 0;
	setAttr -s 8 ".kit[0:7]"  3 10 1 10 10 1 10 1;
	setAttr -s 8 ".kot[0:7]"  3 10 1 10 10 1 10 1;
	setAttr -s 8 ".kix[2:7]"  1 0.93986004590988159 0.91472148895263672 
		1 1 1;
	setAttr -s 8 ".kiy[2:7]"  0 0.34155991673469543 -0.4040849506855011 
		0 0 0;
	setAttr -s 8 ".kox[2:7]"  1 0.93986004590988159 0.91472148895263672 
		1 1 1;
	setAttr -s 8 ".koy[2:7]"  0 0.34155991673469543 -0.4040849506855011 
		0 0 0;
createNode animCurveTA -n "animCurveTA1685";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 1 0 4 2.8907127367970138 10 -16.285030304890295 
		16 9.7351705510645292 25 2.8907127367970138 27 -12.851534551738734 30 0;
	setAttr -s 8 ".kit[0:7]"  1 10 1 10 10 1 10 1;
	setAttr -s 8 ".kot[0:7]"  1 10 1 10 10 1 10 1;
	setAttr -s 8 ".kix[0:7]"  0.85911184549331665 1 1 0.958182692527771 
		0.831015944480896 1 0.95710813999176025 0.89074522256851196;
	setAttr -s 8 ".kiy[0:7]"  0.51178783178329468 0 0 0.28615725040435791 
		0.55624860525131226 0 -0.2897307276725769 0.45450311899185181;
	setAttr -s 8 ".kox[0:7]"  0.85911184549331665 1 1 0.958182692527771 
		0.831015944480896 1 0.95710813999176025 0.89074510335922241;
	setAttr -s 8 ".koy[0:7]"  0.51178789138793945 0 0 0.28615725040435791 
		0.55624860525131226 0 -0.2897307276725769 0.45450314879417419;
createNode animCurveTA -n "animCurveTA1686";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 1 0 4 -6.550665859190187 10 -6.4665627072370357 
		16 -16.599560157166945 25 -6.550665859190187 27 1.5514938265130132 30 0;
	setAttr -s 8 ".kit[0:7]"  1 10 1 10 10 1 10 1;
	setAttr -s 8 ".kot[0:7]"  1 10 1 10 10 1 10 1;
	setAttr -s 8 ".kix[0:7]"  0.99525856971740723 1 1 1 0.99999570846557617 
		1 1 0.99651491641998291;
	setAttr -s 8 ".kiy[0:7]"  -0.097264587879180908 0 0 0 -0.0029357413295656443 
		0 0 -0.083415307104587555;
	setAttr -s 8 ".kox[0:7]"  0.99525856971740723 1 1 1 0.99999570846557617 
		1 1 0.99651491641998291;
	setAttr -s 8 ".koy[0:7]"  -0.097264558076858521 0 0 0 -0.0029357413295656443 
		0 0 -0.083415284752845764;
createNode animCurveTA -n "animCurveTA1687";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -17.821366541589882 4 -1.2419210076360223 
		12 -12.985653829196403 25 -1.2419210076360223 30 -17.821366541589882;
	setAttr -s 5 ".kit[0:4]"  9 1 10 1 1;
	setAttr -s 5 ".kot[0:4]"  9 1 10 1 1;
	setAttr -s 5 ".kix[1:4]"  1 1 1 0.67754131555557251;
	setAttr -s 5 ".kiy[1:4]"  0 0 0 0.735484778881073;
	setAttr -s 5 ".kox[1:4]"  1 1 1 0.67754131555557251;
	setAttr -s 5 ".koy[1:4]"  0 0 0 0.735484778881073;
createNode animCurveTA -n "animCurveTA1688";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -12.005893876475762 4 -3.1504229058662481 
		12 1.587866449615847 25 -3.1504229058662481 30 -12.005893876475762;
	setAttr -s 5 ".kit[2:4]"  10 1 1;
	setAttr -s 5 ".kot[2:4]"  10 1 1;
	setAttr -s 5 ".kix[0:4]"  0.99989551305770874 1 1 1 0.99992328882217407;
	setAttr -s 5 ".kiy[0:4]"  0.014458378776907921 0 0 0 0.012384395115077496;
	setAttr -s 5 ".kox[0:4]"  0.99989551305770874 1 1 1 0.99992328882217407;
	setAttr -s 5 ".koy[0:4]"  0.01445838063955307 0 0 0 0.012384396977722645;
createNode animCurveTA -n "animCurveTA1689";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 9.1378572146953019 4 47.911738664713972 
		12 25.745723523797981 25 47.911738664713972 30 9.1378572146953019;
	setAttr -s 5 ".kit[0:4]"  9 1 10 1 1;
	setAttr -s 5 ".kot[0:4]"  9 1 10 1 1;
	setAttr -s 5 ".kix[1:4]"  1 1 1 0.94339656829833984;
	setAttr -s 5 ".kiy[1:4]"  0 0 0 -0.33166682720184326;
	setAttr -s 5 ".kox[1:4]"  1 1 1 0.94339656829833984;
	setAttr -s 5 ".koy[1:4]"  0 0 0 -0.33166682720184326;
createNode animCurveTA -n "Ratcatcher_CTRL_STUFF_LAT_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -28.841216077843235 30 -28.841216077843235;
createNode animCurveTA -n "Ratcatcher_CTRL_STUFF_LAT_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -21.716766331039956 30 -21.716766331039956;
createNode animCurveTA -n "Ratcatcher_CTRL_STUFF_LAT_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 23.535235892507558 30 23.535235892507558;
createNode animCurveTL -n "Ratcatcher_CTRL_STUFF_LAT_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 30 0;
createNode animCurveTL -n "Ratcatcher_CTRL_STUFF_LAT_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 30 0;
createNode animCurveTL -n "Ratcatcher_CTRL_STUFF_LAT_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 30 0;
createNode animCurveTU -n "Ratcatcher_CTRL_STUFF_Follow";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 2 30 2;
	setAttr -s 2 ".kot[0:1]"  5 5;
createNode animCurveTU -n "Ratcatcher_CTRL_STUFF_Ikfollow";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 30 0;
	setAttr -s 2 ".kot[0:1]"  5 5;
createNode animCurveTA -n "Ratcatcher_CTRL_STUFF_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -24.093441664171177 1 -44.930770022385055 
		2 176.60665678900111 27 176.60665678900111 28 178.10825184565653 29 -28.596503782722966 
		30 -24.093441664171177;
	setAttr -s 7 ".kit[2:6]"  2 2 10 10 1;
	setAttr -s 7 ".kot[2:6]"  2 2 10 10 1;
	setAttr -s 7 ".kix[6]"  0.091273099184036255;
	setAttr -s 7 ".kiy[6]"  -0.99582594633102417;
	setAttr -s 7 ".kox[6]"  0.091273099184036255;
	setAttr -s 7 ".koy[6]"  -0.99582594633102417;
createNode animCurveTA -n "Ratcatcher_CTRL_STUFF_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 49.48465546224881 1 49.984823797467691 
		2 9.9195483638146733 27 9.9195483638146733 28 9.7859867435568191 29 -17.665204135015539 
		30 49.48465546224881;
	setAttr -s 7 ".kit[2:6]"  2 2 10 10 1;
	setAttr -s 7 ".kot[2:6]"  2 2 10 10 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "Ratcatcher_CTRL_STUFF_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 58.801792680015588 1 105.03271819628286 
		2 124.38991069567028 27 124.38991069567028 28 142.89738689537856 29 81.168254637525166 
		30 58.801792680015588;
	setAttr -s 7 ".kit[2:6]"  2 2 10 10 1;
	setAttr -s 7 ".kot[2:6]"  2 2 10 10 1;
	setAttr -s 7 ".kix[6]"  0.041276093572378159;
	setAttr -s 7 ".kiy[6]"  0.99914783239364624;
	setAttr -s 7 ".kox[6]"  0.041276093572378159;
	setAttr -s 7 ".koy[6]"  0.99914783239364624;
createNode animCurveTL -n "Ratcatcher_CTRL_STUFF_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -1.2755255474500937 1 -1.8870941055579062 
		2 -1.951316630929592 27 -1.951316630929592 28 -2.0828977210365891 29 -1.4985274402799638 
		30 -1.2755255474500937;
	setAttr -s 7 ".kit[2:6]"  2 2 10 10 1;
	setAttr -s 7 ".kot[2:6]"  2 2 10 10 1;
	setAttr -s 7 ".kix[6]"  0.054423879832029343;
	setAttr -s 7 ".kiy[6]"  -0.99851793050765991;
	setAttr -s 7 ".kox[6]"  0.054423879832029343;
	setAttr -s 7 ".koy[6]"  -0.99851793050765991;
createNode animCurveTL -n "Ratcatcher_CTRL_STUFF_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -1.4392043230118035 1 -0.76682681986541246 
		2 0.050656756336730183 27 0.050656756336730183 28 0.045978760743063167 29 -1.289777033037713 
		30 -1.4392043230118035;
	setAttr -s 7 ".kit[2:6]"  2 2 10 10 1;
	setAttr -s 7 ".kot[2:6]"  2 2 10 10 1;
	setAttr -s 7 ".kix[6]"  0.049514517188072205;
	setAttr -s 7 ".kiy[6]"  0.99877339601516724;
	setAttr -s 7 ".kox[6]"  0.049514517188072205;
	setAttr -s 7 ".koy[6]"  0.99877339601516724;
createNode animCurveTL -n "Ratcatcher_CTRL_STUFF_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -2.1802956492995231 1 -2.8011226019909579 
		2 -2.1307105797988917 27 -2.1307105797988917 28 -2.1237302211591254 29 -2.7616734926144644 
		30 -2.1802956492995231;
	setAttr -s 7 ".kit[2:6]"  2 2 10 10 1;
	setAttr -s 7 ".kot[2:6]"  2 2 10 10 1;
	setAttr -s 7 ".kix[6]"  0.053614605218172073;
	setAttr -s 7 ".kiy[6]"  -0.99856173992156982;
	setAttr -s 7 ".kox[6]"  0.053614601492881775;
	setAttr -s 7 ".koy[6]"  -0.99856168031692505;
createNode animCurveTL -n "Ratcatcher_CTRL_POLEV_STUFF_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 30 0;
createNode animCurveTL -n "Ratcatcher_CTRL_POLEV_STUFF_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 30 0;
createNode animCurveTL -n "Ratcatcher_CTRL_POLEV_STUFF_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 30 0;
createNode animCurveTA -n "animCurveTA1696";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1.1134085745786892 1 -3.3387029268937667 
		4 5.4620663693904747 16 -29.30482947941476 25 5.4620663693904747 30 1.1134085745786892;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1697";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -5.3180374758492821 1 0.19763548006323398 
		4 -4.8046750635038622 16 11.95465731029855 25 -4.8046750635038622 30 -5.3180374758492821;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1698";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 7.8609313736722894 1 -9.4753377055041916 
		4 -22.979519707617992 16 -6.6000372179042346 25 -22.979519707617992 30 7.8609313736722894;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTL -n "animCurveTL520";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL521";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL522";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "Ratcatcher_CTRL_IK_STUFF_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 30 0;
createNode animCurveTA -n "Ratcatcher_CTRL_IK_STUFF_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 30 0;
createNode animCurveTA -n "Ratcatcher_CTRL_IK_STUFF_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 30 0;
createNode animCurveTL -n "Ratcatcher_CTRL_IK_STUFF_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 30 0;
createNode animCurveTL -n "Ratcatcher_CTRL_IK_STUFF_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 30 0;
createNode animCurveTL -n "Ratcatcher_CTRL_IK_STUFF_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 30 0;
createNode animCurveTU -n "animCurveTU530";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 1 2 2 2 4 2 25 2 27 2 28 2 29 0 30 
		0;
	setAttr -s 9 ".kit[0:8]"  3 1 9 1 1 1 1 9 
		1;
	setAttr -s 9 ".kot[0:8]"  3 1 5 1 1 1 1 5 
		1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 0.03331482782959938 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 -0.99944490194320679 0;
	setAttr -s 9 ".kox[1:8]"  1 0 1 1 1 1 0 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1702";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -5.1107219305963252 1 167.38055085130816 
		2 147.49830225683607 3 -113.52989178220581 4 -97.634461735480158 25 -97.634461735480158 
		27 -90.353815274197444 28 -125.07586289322535 29 -13.346268316456465 30 -5.1107219305963199;
	setAttr -s 10 ".kit[0:9]"  3 1 10 10 1 1 1 1 
		10 1;
	setAttr -s 10 ".kot[0:9]"  3 1 10 10 1 1 1 1 
		10 1;
	setAttr -s 10 ".kix[1:9]"  1 0.013596381060779095 0.015580353327095509 
		1 1 1 1 0.031824108213186264 1;
	setAttr -s 10 ".kiy[1:9]"  0 -0.99990755319595337 -0.9998786449432373 
		0 0 0 0 0.99949353933334351 0;
	setAttr -s 10 ".kox[1:9]"  1 0.013596381060779095 0.015580353327095509 
		1 1 1 1 0.031824108213186264 1;
	setAttr -s 10 ".koy[1:9]"  0 -0.99990755319595337 -0.9998786449432373 
		0 0 0 0 0.99949353933334351 0;
createNode animCurveTA -n "animCurveTA1703";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 8.2811672786141717 1 -48.3670658039795 
		2 -6.5844688343435367 3 24.946778732488884 4 22.079889054909092 25 22.079889054909092 
		27 13.095879796843478 28 -4.7936286351636124 29 5.8823955054104013 30 8.2811672786141752;
	setAttr -s 10 ".kit[0:9]"  3 1 10 10 1 1 1 1 
		10 1;
	setAttr -s 10 ".kot[0:9]"  3 1 10 10 1 1 1 1 
		10 1;
	setAttr -s 10 ".kix[1:9]"  1 0.05203033983707428 0.13208912312984467 
		1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0.99864548444747925 0.9912378191947937 
		0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 0.05203033983707428 0.13208912312984467 
		1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0.99864548444747925 0.9912378191947937 
		0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1704";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.92645454014921158 1 -152.12414270297589 
		2 -186.54748218486435 3 -250.72975767434264 4 -133.78599490539997 25 -133.78599490539997 
		27 -129.41044717499418 28 -130.05070068860712 29 -41.629101993652768 30 -0.92645454014924256;
	setAttr -s 10 ".kit[0:9]"  3 1 10 10 1 1 1 1 
		10 1;
	setAttr -s 10 ".kot[0:9]"  3 1 10 10 1 1 1 1 
		10 1;
	setAttr -s 10 ".kix[1:9]"  1 0.038708299398422241 0.072206988930702209 
		1 1 1 1 0.02956879697740078 1;
	setAttr -s 10 ".kiy[1:9]"  0 -0.99925053119659424 0.99738967418670654 
		0 0 0 0 0.99956279993057251 0;
	setAttr -s 10 ".kox[1:9]"  1 0.038708299398422241 0.072206988930702209 
		1 1 1 1 0.02956879697740078 1;
	setAttr -s 10 ".koy[1:9]"  0 -0.99925053119659424 0.99738967418670654 
		0 0 0 0 0.99956279993057251 0;
createNode animCurveTL -n "animCurveTL526";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.046856395845859107 1 0.59319642763621927 
		2 0.65695608790629201 4 0.78670154815399518 25 0.78670154815399518 27 0.7835852495028377 
		28 0.62894864507178694 29 0.019254878171548157 30 -0.046856395845859107;
	setAttr -s 9 ".kit[0:8]"  3 1 10 1 1 1 1 10 
		1;
	setAttr -s 9 ".kot[0:8]"  3 1 10 1 1 1 1 10 
		1;
	setAttr -s 9 ".kix[1:8]"  1 0.45910105109214783 1 1 1 1 0.098171263933181763 
		1;
	setAttr -s 9 ".kiy[1:8]"  0 0.88838398456573486 0 0 0 0 -0.99516957998275757 
		0;
	setAttr -s 9 ".kox[1:8]"  1 0.45910105109214783 1 1 1 1 0.098171263933181763 
		1;
	setAttr -s 9 ".koy[1:8]"  0 0.88838398456573486 0 0 0 0 -0.99516957998275757 
		0;
createNode animCurveTL -n "animCurveTL527";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.023348763690700665 1 -0.53230086298262136 
		2 -0.60396492358272735 4 -0.41128384551646974 25 -0.41128384551646974 27 -0.32482204394540987 
		28 -0.49825444242324818 29 0.029352286177623199 30 -0.023348763690700665;
	setAttr -s 9 ".kit[0:8]"  3 1 10 1 1 1 1 10 
		1;
	setAttr -s 9 ".kot[0:8]"  3 1 10 1 1 1 1 10 
		1;
	setAttr -s 9 ".kix[1:8]"  1 0.6369929313659668 1 1 1 1 0.13901568949222565 
		1;
	setAttr -s 9 ".kiy[1:8]"  0 0.77086973190307617 0 0 0 0 0.99029022455215454 
		0;
	setAttr -s 9 ".kox[1:8]"  1 0.6369929313659668 1 1 1 1 0.13901568949222565 
		1;
	setAttr -s 9 ".koy[1:8]"  0 0.77086973190307617 0 0 0 0 0.99029022455215454 
		0;
createNode animCurveTL -n "animCurveTL528";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.13506113021862395 1 0.89971301043015794 
		2 0.88580428741861117 4 0.7315407270626898 25 0.7315407270626898 27 0.71021537141497049 
		28 0.85078562451633222 29 -0.057207558457152308 30 -0.13506113021862395;
	setAttr -s 9 ".kit[0:8]"  3 1 10 1 1 1 1 10 
		1;
	setAttr -s 9 ".kot[0:8]"  3 1 10 1 1 1 1 10 
		1;
	setAttr -s 9 ".kix[1:8]"  1 1 1 1 1 1 0.067469663918018341 1;
	setAttr -s 9 ".kiy[1:8]"  0 0 0 0 0 0 -0.99772131443023682 0;
	setAttr -s 9 ".kox[1:8]"  1 1 1 1 1 1 0.067469663918018341 1;
	setAttr -s 9 ".koy[1:8]"  0 0 0 0 0 0 -0.99772131443023682 0;
createNode animCurveTA -n "animCurveTA1705";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -1.6266160090263075 1 0 4 -7.4530676207647177 
		11 5.0494709432890508 19 -15.672742800993456 25 -7.4530676207647177 30 -1.6266160090263075;
	setAttr -s 7 ".kit[0:6]"  9 10 1 10 10 1 1;
	setAttr -s 7 ".kot[0:6]"  9 10 1 10 10 1 1;
	setAttr -s 7 ".kix[2:6]"  1 0.96121698617935181 0.9058610200881958 
		1 0.99864518642425537;
	setAttr -s 7 ".kiy[2:6]"  0 -0.27579313516616821 -0.42357504367828369 
		0 0.05203673243522644;
	setAttr -s 7 ".kox[2:6]"  1 0.96121698617935181 0.9058610200881958 
		1 0.99864518642425537;
	setAttr -s 7 ".koy[2:6]"  0 -0.27579313516616821 -0.42357504367828369 
		0 0.05203673243522644;
createNode animCurveTA -n "animCurveTA1706";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 2.8499857758927387 1 0 4 -20.208303169797514 
		11 -24.433393103166146 19 -2.0066726217607984 25 -20.208303169797514 30 2.8499857758927387;
	setAttr -s 7 ".kit[0:6]"  9 10 1 10 10 1 1;
	setAttr -s 7 ".kot[0:6]"  9 10 1 10 10 1 1;
	setAttr -s 7 ".kix[2:6]"  1 0.84404617547988892 0.98774415254592896 
		1 0.99585831165313721;
	setAttr -s 7 ".kiy[2:6]"  0 0.53627049922943115 0.15608136355876923 
		0 -0.090918853878974915;
	setAttr -s 7 ".kox[2:6]"  1 0.84404617547988892 0.98774415254592896 
		1 0.99585831165313721;
	setAttr -s 7 ".koy[2:6]"  0 0.53627049922943115 0.15608136355876923 
		0 -0.090918853878974915;
createNode animCurveTA -n "animCurveTA1707";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -25.210898828531619 1 0 4 12.682209663595732 
		11 5.7532317994504671 19 3.0212245659893417 25 12.682209663595732 30 -25.210898828531619;
	setAttr -s 7 ".kit[1:6]"  10 1 10 10 1 1;
	setAttr -s 7 ".kot[1:6]"  10 1 10 10 1 1;
	setAttr -s 7 ".kix[0:6]"  0.99369430541992188 0.19762866199016571 
		1 1 1 1 0.99536222219467163;
	setAttr -s 7 ".kiy[0:6]"  0.1121232733130455 0.98027694225311279 
		0 0 0 0 0.096198268234729767;
	setAttr -s 7 ".kox[0:6]"  0.99369430541992188 0.19762866199016571 
		1 1 1 1 0.99536222219467163;
	setAttr -s 7 ".koy[0:6]"  0.1121232733130455 0.98027694225311279 
		0 0 0 0 0.096198268234729767;
createNode animCurveTL -n "animCurveTL529";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.011193700785458628 1 0 4 0.004625545042650404 
		11 0 19 0.012080637726778934 25 0.004625545042650404 30 -0.011193700785458628;
	setAttr -s 7 ".kit[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kot[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kix[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".kiy[2:6]"  0 0 0 0 0;
	setAttr -s 7 ".kox[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".koy[2:6]"  0 0 0 0 0;
createNode animCurveTL -n "animCurveTL530";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.020021267836214246 1 0 4 -0.045993339939598171 
		11 0 19 -0.059809334421216588 25 -0.045993339939598171 30 -0.020021267836214246;
	setAttr -s 7 ".kit[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kot[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kix[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".kiy[2:6]"  0 0 0 0 0;
	setAttr -s 7 ".kox[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".koy[2:6]"  0 0 0 0 0;
createNode animCurveTL -n "animCurveTL531";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.032441787830836878 1 0 4 -0.0055782736904722782 
		11 0 19 -0.0064929294360162896 25 -0.0055782736904722782 30 0.032441787830836878;
	setAttr -s 7 ".kit[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kot[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kix[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".kiy[2:6]"  0 0 0 0 0;
	setAttr -s 7 ".kox[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".koy[2:6]"  0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1708";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1709";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1710";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL532";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL533";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL534";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1711";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -15.609971163878811 4 18.375255713183677 
		15 14.000866848196052 25 18.375255713183677 30 -15.609971163878811;
	setAttr -s 5 ".kit[0:4]"  3 1 10 1 1;
	setAttr -s 5 ".kot[0:4]"  3 1 10 1 1;
	setAttr -s 5 ".kix[1:4]"  1 1 1 1;
	setAttr -s 5 ".kiy[1:4]"  0 0 0 0;
	setAttr -s 5 ".kox[1:4]"  1 1 1 1;
	setAttr -s 5 ".koy[1:4]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1712";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 8.3116042646716988 4 4.8262645773999049 
		15 6.7980288456046107 25 4.8262645773999049 30 8.3116042646716988;
	setAttr -s 5 ".kit[0:4]"  9 1 10 1 3;
	setAttr -s 5 ".kot[0:4]"  9 1 10 1 3;
	setAttr -s 5 ".kix[1:4]"  1 1 1 1;
	setAttr -s 5 ".kiy[1:4]"  0 0 0 0;
	setAttr -s 5 ".kox[1:4]"  1 1 1 1;
	setAttr -s 5 ".koy[1:4]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1713";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 14.458598883932659 4 -1.0479898046100278 
		15 1.0094049230288358 25 -1.0479898046100278 30 14.458598883932659;
	setAttr -s 5 ".kit[0:4]"  3 1 10 1 1;
	setAttr -s 5 ".kot[0:4]"  3 1 10 1 1;
	setAttr -s 5 ".kix[1:4]"  1 1 1 1;
	setAttr -s 5 ".kiy[1:4]"  0 0 0 0;
	setAttr -s 5 ".kox[1:4]"  1 1 1 1;
	setAttr -s 5 ".koy[1:4]"  0 0 0 0;
createNode animCurveTL -n "animCurveTL535";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.18868131369562219 1 -0.21601561520939999 
		4 0.031673942042528491 15 0.016173102116699069 25 0.031673942042528491 30 -0.18868131369562219;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTL -n "animCurveTL536";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.23059098815955009 1 0.12918874947661574 
		4 -0.43202791391412798 15 -0.46635257821700332 25 -0.43202791391412798 30 0.23059098815955009;
	setAttr -s 6 ".kit[1:5]"  10 1 10 1 1;
	setAttr -s 6 ".kot[1:5]"  10 1 10 1 1;
	setAttr -s 6 ".kix[0:5]"  0.98070734739303589 0.19726766645908356 
		1 1 1 0.9857366681098938;
	setAttr -s 6 ".kiy[0:5]"  0.19548198580741882 -0.98034965991973877 
		0 0 0 0.16829505562782288;
	setAttr -s 6 ".kox[0:5]"  0.98070728778839111 0.19726766645908356 
		1 1 1 0.9857366681098938;
	setAttr -s 6 ".koy[0:5]"  0.19548198580741882 -0.98034965991973877 
		0 0 0 0.16829507052898407;
createNode animCurveTL -n "animCurveTL537";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.049918713102953649 1 0.0032200423389712549 
		2 0.14287951412728911 4 0.25318664860113566 15 0.14862201030292307 25 0.25318664860113566 
		30 0.049918713102953649;
	setAttr -s 7 ".kit[1:6]"  10 10 1 10 1 1;
	setAttr -s 7 ".kot[1:6]"  10 10 1 10 1 1;
	setAttr -s 7 ".kix[0:6]"  0.93816483020782471 1 0.37143349647521973 
		1 1 1 0.95350700616836548;
	setAttr -s 7 ".kiy[0:6]"  -0.34618902206420898 0 0.92845958471298218 
		0 0 0 -0.30137079954147339;
	setAttr -s 7 ".kox[0:6]"  0.93816477060317993 1 0.37143349647521973 
		1 1 1 0.95350700616836548;
	setAttr -s 7 ".koy[0:6]"  -0.34618902206420898 0 0.92845958471298218 
		0 0 0 -0.30137082934379578;
createNode animCurveTU -n "animCurveTU531";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 9 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 5 5 5 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU532";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.084155571970393403 1 0.090404173182794284 
		4 0.090404173182794284 25 0.090404173182794284 30 0.084155571970393403;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL538";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.067207227343123899 1 -0.10959129807919486 
		4 0.11100241105043018 25 0.11100241105043018 30 0.067207227343123899;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL539";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.20472824713235571 1 -0.067808421173543215 
		4 -0.23349643651839411 25 -0.23349643651839411 30 -0.20472824713235571;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL540";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.20941646546924442 1 0.16948502678081656 
		4 0.19857776477439582 25 0.19857776477439582 30 0.20941646546924442;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU533";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 9 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 5 5 5 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU534";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.084155864375844894 1 0.090403813328038901 
		4 0.090403813328038901 25 0.090403813328038901 30 0.084155864375844894;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL541";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 -0.2501854286797639 25 -0.2501854286797639 
		30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL542";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.40088449385078673 1 0.028920306116140847 
		4 0.079736607157515002 25 0.079736607157515002 30 -0.40088449385078673;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL543";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.69609418843799409 1 -0.23902912508602667 
		4 -0.027011509566143732 25 -0.027011509566143732 30 -0.69609418843799409;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1714";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 1 0 4 11.265346833351362 9 2.2741539624929166 
		18 -38.299751302535135 25 11.265346833351362 27 24.888941746907648 29 -15.531035783412783 
		30 0;
	setAttr -s 9 ".kit[0:8]"  9 10 1 10 10 1 10 10 
		1;
	setAttr -s 9 ".kot[0:8]"  9 10 1 10 10 1 10 10 
		1;
	setAttr -s 9 ".kix[2:8]"  1 0.47477602958679199 0.95933473110198975 
		1 0.27416789531707764 0.22433818876743317 0.79825937747955322;
	setAttr -s 9 ".kiy[2:8]"  0 -0.88010668754577637 0.28227093815803528 
		0 -0.96168184280395508 -0.97451138496398926 -0.60231387615203857;
	setAttr -s 9 ".kox[2:8]"  1 0.47477602958679199 0.95933473110198975 
		1 0.27416789531707764 0.22433818876743317 0.79825937747955322;
	setAttr -s 9 ".koy[2:8]"  0 -0.88010668754577637 0.28227093815803528 
		0 -0.96168184280395508 -0.97451138496398926 -0.60231387615203857;
createNode animCurveTA -n "animCurveTA1715";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 1 0 4 -3.1070920065638399 9 27.587686960688377 
		18 5.5553619494336592 25 -3.1070920065638399 27 19.010908466676948 29 3.4618021777959047 
		30 0;
	setAttr -s 9 ".kit[0:8]"  3 10 1 10 10 1 10 10 
		1;
	setAttr -s 9 ".kot[0:8]"  3 10 1 10 10 1 10 10 
		1;
	setAttr -s 9 ".kix[2:8]"  1 0.95132029056549072 0.70552313327789307 
		1 0.75823533535003662 0.28856316208839417 1;
	setAttr -s 9 ".kiy[2:8]"  0 0.30820399522781372 -0.70868688821792603 
		0 0.65198099613189697 -0.95746088027954102 0;
	setAttr -s 9 ".kox[2:8]"  1 0.95132029056549072 0.70552313327789307 
		1 0.75823533535003662 0.28856316208839417 1;
	setAttr -s 9 ".koy[2:8]"  0 0.30820399522781372 -0.70868688821792603 
		0 0.65198099613189697 -0.95746088027954102 0;
createNode animCurveTA -n "animCurveTA1716";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 1 0 4 -1.9390874256641724 9 -22.797525627637512 
		18 -3.1089209964481888 25 -1.9390874256641724 27 15.654548745536825 29 0.90658655119409715 
		30 0;
	setAttr -s 9 ".kit[0:8]"  9 10 1 10 10 1 10 10 
		1;
	setAttr -s 9 ".kot[0:8]"  9 10 1 10 10 1 10 10 
		1;
	setAttr -s 9 ".kix[2:8]"  1 0.99904423952102661 1 1 0.93709778785705566 
		1 0.66784071922302246;
	setAttr -s 9 ".kiy[2:8]"  0 -0.043709855526685715 0 0 0.34906694293022156 
		0 -0.74430429935455322;
	setAttr -s 9 ".kox[2:8]"  1 0.99904423952102661 1 1 0.93709778785705566 
		1 0.66784071922302246;
	setAttr -s 9 ".koy[2:8]"  0 -0.043709855526685715 0 0 0.34906694293022156 
		0 -0.74430429935455322;
createNode animCurveTA -n "animCurveTA1717";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 1 0 4 4.0152650792436599 9 2.7786116653050459 
		15 7.473726891417332 21 1.9732125287093998 25 4.0152650792436599 30 0;
	setAttr -s 8 ".kit[0:7]"  3 10 1 10 10 10 1 1;
	setAttr -s 8 ".kot[0:7]"  3 10 1 10 10 10 1 1;
	setAttr -s 8 ".kix[2:7]"  1 1 0.99938309192657471 1 1 1;
	setAttr -s 8 ".kiy[2:7]"  0 0 -0.035120490938425064 0 0 0;
	setAttr -s 8 ".kox[2:7]"  1 1 0.99938309192657471 1 1 1;
	setAttr -s 8 ".koy[2:7]"  0 0 -0.035120490938425064 0 0 0;
createNode animCurveTA -n "animCurveTA1718";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 1 0 4 -21.570281189877615 9 15.483650356173481 
		15 36.220351189010891 21 -24.380631385385492 25 -21.570281189877615 30 0;
	setAttr -s 8 ".kit[0:7]"  3 10 1 10 10 10 1 1;
	setAttr -s 8 ".kot[0:7]"  3 10 1 10 10 10 1 1;
	setAttr -s 8 ".kix[2:7]"  1 0.3416522741317749 0.49841147661209106 
		1 1 1;
	setAttr -s 8 ".kiy[2:7]"  0 0.93982648849487305 -0.86694067716598511 
		0 0 0;
	setAttr -s 8 ".kox[2:7]"  1 0.3416522741317749 0.49841147661209106 
		1 1 1;
	setAttr -s 8 ".koy[2:7]"  0 0.93982648849487305 -0.86694067716598511 
		0 0 0;
createNode animCurveTA -n "animCurveTA1719";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 1 0 4 11.940401903998355 9 -1.4985407372977197 
		15 -7.4324495778866071 21 0.2966302542767521 25 11.940401903998355 30 0;
	setAttr -s 8 ".kit[0:7]"  3 10 1 10 10 10 1 1;
	setAttr -s 8 ".kot[0:7]"  3 10 1 10 10 10 1 1;
	setAttr -s 8 ".kix[2:7]"  1 0.73514461517333984 0.99694627523422241 
		0.70204806327819824 1 1;
	setAttr -s 8 ".kiy[2:7]"  0 -0.67791032791137695 0.078089922666549683 
		0.71212959289550781 0 0;
	setAttr -s 8 ".kox[2:7]"  1 0.73514461517333984 0.99694627523422241 
		0.70204806327819824 1 1;
	setAttr -s 8 ".koy[2:7]"  0 -0.67791032791137695 0.078089922666549683 
		0.71212959289550781 0 0;
createNode animCurveTA -n "animCurveTA1720";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 4 -2.4432659646466193 9 -21.280796018323482 
		17 -9.3667122023000111 25 -2.4432659646466193 30 0;
	setAttr -s 7 ".kit[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kot[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kix[2:6]"  1 0.96324998140335083 0.85125064849853516 
		1 1;
	setAttr -s 7 ".kiy[2:6]"  0 -0.26860654354095459 0.52475923299789429 
		0 0;
	setAttr -s 7 ".kox[2:6]"  1 0.96324998140335083 0.85125064849853516 
		1 1;
	setAttr -s 7 ".koy[2:6]"  0 -0.26860654354095459 0.52475923299789429 
		0 0;
createNode animCurveTA -n "animCurveTA1721";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 4 8.3039721797661237 9 2.7080285839460774 
		17 -6.1799088100269737 25 8.3039721797661237 30 0;
	setAttr -s 7 ".kit[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kot[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kix[2:6]"  1 0.86376708745956421 0.983642578125 1 
		1;
	setAttr -s 7 ".kiy[2:6]"  0 -0.50389128923416138 0.18013134598731995 
		0 0;
	setAttr -s 7 ".kox[2:6]"  1 0.86376708745956421 0.983642578125 1 
		1;
	setAttr -s 7 ".koy[2:6]"  0 -0.50389128923416138 0.18013134598731995 
		0 0;
createNode animCurveTA -n "animCurveTA1722";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 4 28.580299093270092 9 1.6099263213500914 
		17 0.6238108611727986 25 28.580299093270092 30 0;
	setAttr -s 7 ".kit[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kot[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kix[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".kiy[2:6]"  0 0 0 0 0;
	setAttr -s 7 ".kox[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".koy[2:6]"  0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1723";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -18.592620239620459 4 29.864277786685772 
		9 -9.2270264168065577 15 -9.0250793204975963 25 29.864277786685772 28 -17.034454221892684 
		30 -18.592620239620459;
	setAttr -s 7 ".kit[0:6]"  3 1 9 10 1 9 1;
	setAttr -s 7 ".kot[0:6]"  3 1 9 10 1 9 1;
	setAttr -s 7 ".kix[1:6]"  0.99993216991424561 0.47529253363609314 
		1 0.99993216991424561 0.1933492124080658 1;
	setAttr -s 7 ".kiy[1:6]"  -0.011649205349385738 -0.87982779741287231 
		0 -0.011649205349385738 -0.98113006353378296 0;
	setAttr -s 7 ".kox[1:6]"  0.99993216991424561 0.47529253363609314 
		1 0.99993216991424561 0.1933492124080658 1;
	setAttr -s 7 ".koy[1:6]"  -0.011649205349385738 -0.87982779741287231 
		0 -0.011649205349385738 -0.98113006353378296 0;
createNode animCurveTA -n "animCurveTA1724";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -4.0495369920864128 4 35.570255898446021 
		9 44.256999488326628 15 15.454186335713974 25 35.570255898446021 28 18.002510148949103 
		30 -4.0495369920864146;
	setAttr -s 7 ".kit[2:6]"  9 10 1 9 1;
	setAttr -s 7 ".kot[2:6]"  9 10 1 9 1;
	setAttr -s 7 ".kix[0:6]"  0.9601597785949707 0.37508708238601685 
		0.72228068113327026 0.96188932657241821 0.37508708238601685 0.23431357741355896 0.97030419111251831;
	setAttr -s 7 ".kiy[0:6]"  0.27945157885551453 0.92698961496353149 
		-0.69160008430480957 -0.2734391987323761 0.92698961496353149 -0.97216105461120605 
		0.24188788235187531;
	setAttr -s 7 ".kox[0:6]"  0.96015983819961548 0.37508708238601685 
		0.72228068113327026 0.96188932657241821 0.37508708238601685 0.23431357741355896 0.97030419111251831;
	setAttr -s 7 ".koy[0:6]"  0.27945151925086975 0.92698961496353149 
		-0.69160008430480957 -0.2734391987323761 0.92698961496353149 -0.97216105461120605 
		0.24188783764839172;
createNode animCurveTA -n "animCurveTA1725";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -24.718935474963271 4 -42.488432986864019 
		9 -16.70671945481352 15 -56.202906949904268 25 -42.488432986864019 28 -41.94706426793789 
		30 -24.718935474963271;
	setAttr -s 7 ".kit[0:6]"  3 1 9 10 1 9 1;
	setAttr -s 7 ".kot[0:6]"  3 1 9 10 1 9 1;
	setAttr -s 7 ".kix[1:6]"  0.93155646324157715 0.83736777305603027 
		0.76430851221084595 0.93155646324157715 0.47337359189987183 1;
	setAttr -s 7 ".kiy[1:6]"  0.36359679698944092 -0.54663991928100586 
		-0.64485067129135132 0.36359679698944092 0.88086169958114624 0;
	setAttr -s 7 ".kox[1:6]"  0.93155646324157715 0.83736777305603027 
		0.76430851221084595 0.93155646324157715 0.47337359189987183 1;
	setAttr -s 7 ".koy[1:6]"  0.36359679698944092 -0.54663991928100586 
		-0.64485067129135132 0.36359679698944092 0.88086169958114624 0;
createNode animCurveTA -n "animCurveTA1726";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 4 -1.1591421285958521 11 -0.91500109422426712 
		19 11.010914873825085 25 -1.1591421285958521 30 0;
	setAttr -s 7 ".kit[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kot[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kix[2:6]"  1 1 0.99995839595794678 1 1;
	setAttr -s 7 ".kiy[2:6]"  0 0 -0.009130474179983139 0 0;
	setAttr -s 7 ".kox[2:6]"  1 1 0.99995839595794678 1 1;
	setAttr -s 7 ".koy[2:6]"  0 0 -0.009130474179983139 0 0;
createNode animCurveTA -n "animCurveTA1727";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 4 26.166546899511932 11 -11.699642626884824 
		19 37.126328643160377 25 26.166546899511932 30 0;
	setAttr -s 7 ".kit[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kot[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kix[2:6]"  1 0.93398463726043701 0.57681208848953247 
		1 1;
	setAttr -s 7 ".kiy[2:6]"  0 0.35731315612792969 0.81687688827514648 
		0 0;
	setAttr -s 7 ".kox[2:6]"  1 0.93398463726043701 0.57681208848953247 
		1 1;
	setAttr -s 7 ".koy[2:6]"  0 0.35731315612792969 0.81687688827514648 
		0 0;
createNode animCurveTA -n "animCurveTA1728";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 4 9.2726962129529831 11 -12.175064243759611 
		19 -7.9612948641950121 25 9.2726962129529831 30 0;
	setAttr -s 7 ".kit[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kot[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kix[2:6]"  1 0.8568950891494751 0.78005218505859375 
		1 1;
	setAttr -s 7 ".kiy[2:6]"  0 -0.51549077033996582 0.62571448087692261 
		0 0;
	setAttr -s 7 ".kox[2:6]"  1 0.8568950891494751 0.78005218505859375 
		1 1;
	setAttr -s 7 ".koy[2:6]"  0 -0.51549077033996582 0.62571448087692261 
		0 0;
createNode animCurveTU -n "animCurveTU535";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 1 1 4 1 25 1 30 1;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU536";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 1 1 4 1 25 1 30 1;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU537";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 1 1 4 1 25 1 30 1;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1729";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1730";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1731";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL544";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL545";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL546";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU538";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 1 1 4 1 25 1 30 1;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU539";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 1 1 4 1 25 1 30 1;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU540";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 1 1 4 1 25 1 30 1;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1732";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1733";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1734";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL547";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL548";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL549";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1735";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1736";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA1737";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 7.2644697342894906 1 1.3417637467815047 
		4 0 25 0 30 7.2644697342894906;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL550";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL551";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL552";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL553";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -0.000119480405310887 4 0.13666756395673033 
		25 0.13666756395673033 30 -0.000119480405310887;
	setAttr -s 4 ".kit[0:3]"  9 1 1 1;
	setAttr -s 4 ".kot[0:3]"  9 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 0.99999982118606567;
	setAttr -s 4 ".kiy[1:3]"  0 0 0.00061403191648423672;
	setAttr -s 4 ".kox[1:3]"  1 1 0.99999982118606567;
	setAttr -s 4 ".koy[1:3]"  0 0 0.00061403191648423672;
createNode animCurveTL -n "animCurveTL554";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.1152566135867675 4 0.056476742475794602 
		25 0.056476742475794602 30 0.1152566135867675;
	setAttr -s 4 ".kit[0:3]"  3 1 1 1;
	setAttr -s 4 ".kot[0:3]"  3 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTL -n "animCurveTL555";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.19515846066137013 4 0.15484202796220975 
		25 0.15484202796220975 30 0.19515846066137013;
	setAttr -s 4 ".kit[0:3]"  3 1 1 1;
	setAttr -s 4 ".kot[0:3]"  3 1 1 1;
	setAttr -s 4 ".kix[1:3]"  1 1 1;
	setAttr -s 4 ".kiy[1:3]"  0 0 0;
	setAttr -s 4 ".kox[1:3]"  1 1 1;
	setAttr -s 4 ".koy[1:3]"  0 0 0;
createNode animCurveTU -n "Ratcatcher_CTRL_STUFF_scaleZ";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 3 1e-005 26 1e-005 30 1;
createNode animCurveTU -n "Ratcatcher_CTRL_STUFF_scaleY";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 3 1e-005 26 1e-005 30 1;
createNode animCurveTU -n "Ratcatcher_CTRL_STUFF_scaleX";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 3 1e-005 26 1e-005 30 1;
createNode animCurveTU -n "Ratcatcher_CTRL_STUFF_LAT_scaleZ";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 2 0 28 0 30 1;
createNode animCurveTU -n "Ratcatcher_CTRL_STUFF_LAT_scaleY";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 2 0 28 0 30 1;
createNode animCurveTU -n "Ratcatcher_CTRL_STUFF_LAT_scaleX";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 2 0 28 0 30 1;
createNode animCurveTA -n "Ratcatcher_CTRL_TwistR_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 1 -94.115794976645915 2 -76.768006769935312 
		4 -9.7528096396578317 25 14.113736899148128 26 -20.260973089625299 28 -63.098293750661526 
		29 -12.248980860498346 30 0;
createNode animCurveTA -n "Ratcatcher_CTRL_TwistL_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 -1.506339312750437 3 -57.684687843205765 
		27 -57.684687843205765 30 0;
	setAttr -s 5 ".kit[3:4]"  1 1;
	setAttr -s 5 ".kot[3:4]"  1 1;
	setAttr -s 5 ".kix[3:4]"  0.99960356950759888 1;
	setAttr -s 5 ".kiy[3:4]"  0.028157312422990799 0;
	setAttr -s 5 ".kox[3:4]"  0.99960356950759888 1;
	setAttr -s 5 ".koy[3:4]"  0.028157312422990799 0;
createNode lightLinker -n "lightLinker1";
	setAttr -s 3 ".lnk";
	setAttr -s 3 ".slnk";
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
connectAttr "ability2Source.cl" "clipLibrary1.sc[0]";
connectAttr "animCurveTU483.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "animCurveTA1545.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "animCurveTA1546.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "animCurveTA1547.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "animCurveTU484.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "animCurveTU485.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "animCurveTU486.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "animCurveTU487.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "animCurveTA1548.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "animCurveTA1549.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "animCurveTA1550.a" "clipLibrary1.cel[0].cev[10].cevr";
connectAttr "animCurveTU488.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "animCurveTU489.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "animCurveTL493.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "animCurveTL494.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "animCurveTL495.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "animCurveTA1551.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "animCurveTA1552.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "animCurveTA1553.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "animCurveTA1554.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "animCurveTA1555.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "animCurveTU490.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "animCurveTU491.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "animCurveTU492.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "animCurveTU493.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "animCurveTA1556.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "animCurveTA1557.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "animCurveTA1558.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "animCurveTL496.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "animCurveTL497.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "animCurveTL498.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "animCurveTU494.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "animCurveTA1559.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "animCurveTA1560.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "animCurveTA1561.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "animCurveTU495.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "animCurveTU496.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "animCurveTU497.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "animCurveTU498.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "animCurveTA1562.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "animCurveTA1563.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "animCurveTA1564.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "animCurveTU499.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "animCurveTU500.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "animCurveTL499.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "animCurveTL500.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "animCurveTL501.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "animCurveTA1565.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "animCurveTA1566.a" "clipLibrary1.cel[0].cev[48].cevr";
connectAttr "animCurveTA1567.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "animCurveTA1568.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "animCurveTA1569.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "animCurveTU501.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "animCurveTU502.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "animCurveTU503.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "animCurveTU504.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "animCurveTU505.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "animCurveTA1570.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "animCurveTA1571.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "animCurveTA1572.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "animCurveTL502.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "animCurveTL503.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "animCurveTL504.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "animCurveTU506.a" "clipLibrary1.cel[0].cev[63].cevr";
connectAttr "animCurveTA1573.a" "clipLibrary1.cel[0].cev[64].cevr";
connectAttr "animCurveTA1574.a" "clipLibrary1.cel[0].cev[65].cevr";
connectAttr "animCurveTA1575.a" "clipLibrary1.cel[0].cev[66].cevr";
connectAttr "animCurveTU507.a" "clipLibrary1.cel[0].cev[67].cevr";
connectAttr "animCurveTA1576.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "animCurveTA1577.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "animCurveTA1578.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "animCurveTA1579.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "animCurveTA1580.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "animCurveTA1581.a" "clipLibrary1.cel[0].cev[73].cevr";
connectAttr "animCurveTU508.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "animCurveTA1582.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "animCurveTA1583.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "animCurveTA1584.a" "clipLibrary1.cel[0].cev[77].cevr";
connectAttr "animCurveTA1585.a" "clipLibrary1.cel[0].cev[78].cevr";
connectAttr "animCurveTA1586.a" "clipLibrary1.cel[0].cev[79].cevr";
connectAttr "animCurveTA1587.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "animCurveTU509.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "animCurveTA1588.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "animCurveTA1589.a" "clipLibrary1.cel[0].cev[83].cevr";
connectAttr "animCurveTA1590.a" "clipLibrary1.cel[0].cev[84].cevr";
connectAttr "animCurveTA1591.a" "clipLibrary1.cel[0].cev[85].cevr";
connectAttr "animCurveTA1592.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "animCurveTA1593.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "animCurveTU510.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "animCurveTA1594.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr "animCurveTA1595.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "animCurveTA1596.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "animCurveTA1597.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "animCurveTA1598.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "animCurveTA1599.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "animCurveTU511.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "animCurveTA1600.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "animCurveTA1601.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "animCurveTA1602.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "animCurveTA1603.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "animCurveTA1604.a" "clipLibrary1.cel[0].cev[100].cevr";
connectAttr "animCurveTA1605.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "animCurveTA1606.a" "clipLibrary1.cel[0].cev[102].cevr";
connectAttr "animCurveTA1607.a" "clipLibrary1.cel[0].cev[103].cevr";
connectAttr "animCurveTA1608.a" "clipLibrary1.cel[0].cev[104].cevr";
connectAttr "animCurveTU512.a" "clipLibrary1.cel[0].cev[105].cevr";
connectAttr "animCurveTA1609.a" "clipLibrary1.cel[0].cev[106].cevr";
connectAttr "animCurveTA1610.a" "clipLibrary1.cel[0].cev[107].cevr";
connectAttr "animCurveTA1611.a" "clipLibrary1.cel[0].cev[108].cevr";
connectAttr "animCurveTA1612.a" "clipLibrary1.cel[0].cev[109].cevr";
connectAttr "animCurveTA1613.a" "clipLibrary1.cel[0].cev[110].cevr";
connectAttr "animCurveTA1614.a" "clipLibrary1.cel[0].cev[111].cevr";
connectAttr "animCurveTU513.a" "clipLibrary1.cel[0].cev[112].cevr";
connectAttr "animCurveTA1615.a" "clipLibrary1.cel[0].cev[113].cevr";
connectAttr "animCurveTA1616.a" "clipLibrary1.cel[0].cev[114].cevr";
connectAttr "animCurveTA1617.a" "clipLibrary1.cel[0].cev[115].cevr";
connectAttr "animCurveTA1618.a" "clipLibrary1.cel[0].cev[116].cevr";
connectAttr "animCurveTA1619.a" "clipLibrary1.cel[0].cev[117].cevr";
connectAttr "animCurveTA1620.a" "clipLibrary1.cel[0].cev[118].cevr";
connectAttr "animCurveTU514.a" "clipLibrary1.cel[0].cev[119].cevr";
connectAttr "animCurveTA1621.a" "clipLibrary1.cel[0].cev[120].cevr";
connectAttr "animCurveTA1622.a" "clipLibrary1.cel[0].cev[121].cevr";
connectAttr "animCurveTA1623.a" "clipLibrary1.cel[0].cev[122].cevr";
connectAttr "animCurveTA1624.a" "clipLibrary1.cel[0].cev[123].cevr";
connectAttr "animCurveTA1625.a" "clipLibrary1.cel[0].cev[124].cevr";
connectAttr "animCurveTA1626.a" "clipLibrary1.cel[0].cev[125].cevr";
connectAttr "animCurveTU515.a" "clipLibrary1.cel[0].cev[126].cevr";
connectAttr "animCurveTA1627.a" "clipLibrary1.cel[0].cev[127].cevr";
connectAttr "animCurveTA1628.a" "clipLibrary1.cel[0].cev[128].cevr";
connectAttr "animCurveTA1629.a" "clipLibrary1.cel[0].cev[129].cevr";
connectAttr "animCurveTA1630.a" "clipLibrary1.cel[0].cev[130].cevr";
connectAttr "animCurveTA1631.a" "clipLibrary1.cel[0].cev[131].cevr";
connectAttr "animCurveTA1632.a" "clipLibrary1.cel[0].cev[132].cevr";
connectAttr "animCurveTU516.a" "clipLibrary1.cel[0].cev[133].cevr";
connectAttr "animCurveTA1633.a" "clipLibrary1.cel[0].cev[134].cevr";
connectAttr "animCurveTA1634.a" "clipLibrary1.cel[0].cev[135].cevr";
connectAttr "animCurveTA1635.a" "clipLibrary1.cel[0].cev[136].cevr";
connectAttr "animCurveTA1636.a" "clipLibrary1.cel[0].cev[137].cevr";
connectAttr "animCurveTA1637.a" "clipLibrary1.cel[0].cev[138].cevr";
connectAttr "animCurveTA1638.a" "clipLibrary1.cel[0].cev[139].cevr";
connectAttr "animCurveTA1639.a" "clipLibrary1.cel[0].cev[140].cevr";
connectAttr "animCurveTA1640.a" "clipLibrary1.cel[0].cev[141].cevr";
connectAttr "animCurveTA1641.a" "clipLibrary1.cel[0].cev[142].cevr";
connectAttr "animCurveTU517.a" "clipLibrary1.cel[0].cev[143].cevr";
connectAttr "animCurveTU518.a" "clipLibrary1.cel[0].cev[144].cevr";
connectAttr "animCurveTU519.a" "clipLibrary1.cel[0].cev[145].cevr";
connectAttr "animCurveTA1642.a" "clipLibrary1.cel[0].cev[146].cevr";
connectAttr "animCurveTA1643.a" "clipLibrary1.cel[0].cev[147].cevr";
connectAttr "animCurveTA1644.a" "clipLibrary1.cel[0].cev[148].cevr";
connectAttr "animCurveTL505.a" "clipLibrary1.cel[0].cev[149].cevr";
connectAttr "animCurveTL506.a" "clipLibrary1.cel[0].cev[150].cevr";
connectAttr "animCurveTL507.a" "clipLibrary1.cel[0].cev[151].cevr";
connectAttr "animCurveTA1645.a" "clipLibrary1.cel[0].cev[152].cevr";
connectAttr "animCurveTA1646.a" "clipLibrary1.cel[0].cev[153].cevr";
connectAttr "animCurveTA1647.a" "clipLibrary1.cel[0].cev[154].cevr";
connectAttr "animCurveTU520.a" "clipLibrary1.cel[0].cev[155].cevr";
connectAttr "animCurveTA1648.a" "clipLibrary1.cel[0].cev[156].cevr";
connectAttr "animCurveTA1649.a" "clipLibrary1.cel[0].cev[157].cevr";
connectAttr "animCurveTA1650.a" "clipLibrary1.cel[0].cev[158].cevr";
connectAttr "animCurveTA1651.a" "clipLibrary1.cel[0].cev[159].cevr";
connectAttr "animCurveTA1652.a" "clipLibrary1.cel[0].cev[160].cevr";
connectAttr "animCurveTA1653.a" "clipLibrary1.cel[0].cev[161].cevr";
connectAttr "animCurveTA1654.a" "clipLibrary1.cel[0].cev[162].cevr";
connectAttr "animCurveTA1655.a" "clipLibrary1.cel[0].cev[163].cevr";
connectAttr "animCurveTA1656.a" "clipLibrary1.cel[0].cev[164].cevr";
connectAttr "animCurveTU521.a" "clipLibrary1.cel[0].cev[165].cevr";
connectAttr "animCurveTA1657.a" "clipLibrary1.cel[0].cev[166].cevr";
connectAttr "animCurveTA1658.a" "clipLibrary1.cel[0].cev[167].cevr";
connectAttr "animCurveTA1659.a" "clipLibrary1.cel[0].cev[168].cevr";
connectAttr "animCurveTU522.a" "clipLibrary1.cel[0].cev[169].cevr";
connectAttr "animCurveTU523.a" "clipLibrary1.cel[0].cev[170].cevr";
connectAttr "animCurveTU524.a" "clipLibrary1.cel[0].cev[171].cevr";
connectAttr "animCurveTA1660.a" "clipLibrary1.cel[0].cev[172].cevr";
connectAttr "animCurveTA1661.a" "clipLibrary1.cel[0].cev[173].cevr";
connectAttr "animCurveTA1662.a" "clipLibrary1.cel[0].cev[174].cevr";
connectAttr "animCurveTL508.a" "clipLibrary1.cel[0].cev[175].cevr";
connectAttr "animCurveTL509.a" "clipLibrary1.cel[0].cev[176].cevr";
connectAttr "animCurveTL510.a" "clipLibrary1.cel[0].cev[177].cevr";
connectAttr "animCurveTA1663.a" "clipLibrary1.cel[0].cev[178].cevr";
connectAttr "animCurveTA1664.a" "clipLibrary1.cel[0].cev[179].cevr";
connectAttr "animCurveTA1665.a" "clipLibrary1.cel[0].cev[180].cevr";
connectAttr "animCurveTU525.a" "clipLibrary1.cel[0].cev[181].cevr";
connectAttr "animCurveTA1666.a" "clipLibrary1.cel[0].cev[182].cevr";
connectAttr "animCurveTA1667.a" "clipLibrary1.cel[0].cev[183].cevr";
connectAttr "animCurveTA1668.a" "clipLibrary1.cel[0].cev[184].cevr";
connectAttr "animCurveTA1669.a" "clipLibrary1.cel[0].cev[185].cevr";
connectAttr "animCurveTA1670.a" "clipLibrary1.cel[0].cev[186].cevr";
connectAttr "animCurveTA1671.a" "clipLibrary1.cel[0].cev[187].cevr";
connectAttr "animCurveTA1672.a" "clipLibrary1.cel[0].cev[188].cevr";
connectAttr "animCurveTA1673.a" "clipLibrary1.cel[0].cev[189].cevr";
connectAttr "animCurveTA1674.a" "clipLibrary1.cel[0].cev[190].cevr";
connectAttr "animCurveTA1675.a" "clipLibrary1.cel[0].cev[191].cevr";
connectAttr "animCurveTA1676.a" "clipLibrary1.cel[0].cev[192].cevr";
connectAttr "animCurveTA1677.a" "clipLibrary1.cel[0].cev[193].cevr";
connectAttr "animCurveTA1678.a" "clipLibrary1.cel[0].cev[194].cevr";
connectAttr "animCurveTA1679.a" "clipLibrary1.cel[0].cev[195].cevr";
connectAttr "animCurveTA1680.a" "clipLibrary1.cel[0].cev[196].cevr";
connectAttr "animCurveTU526.a" "clipLibrary1.cel[0].cev[197].cevr";
connectAttr "animCurveTA1681.a" "clipLibrary1.cel[0].cev[198].cevr";
connectAttr "animCurveTA1682.a" "clipLibrary1.cel[0].cev[199].cevr";
connectAttr "animCurveTA1683.a" "clipLibrary1.cel[0].cev[200].cevr";
connectAttr "animCurveTU527.a" "clipLibrary1.cel[0].cev[201].cevr";
connectAttr "animCurveTA1684.a" "clipLibrary1.cel[0].cev[202].cevr";
connectAttr "animCurveTA1685.a" "clipLibrary1.cel[0].cev[203].cevr";
connectAttr "animCurveTA1686.a" "clipLibrary1.cel[0].cev[204].cevr";
connectAttr "animCurveTA1687.a" "clipLibrary1.cel[0].cev[205].cevr";
connectAttr "animCurveTA1688.a" "clipLibrary1.cel[0].cev[206].cevr";
connectAttr "animCurveTA1689.a" "clipLibrary1.cel[0].cev[207].cevr";
connectAttr "Ratcatcher_CTRL_STUFF_LAT_rotateZ.a" "clipLibrary1.cel[0].cev[208].cevr"
		;
connectAttr "Ratcatcher_CTRL_STUFF_LAT_rotateY.a" "clipLibrary1.cel[0].cev[209].cevr"
		;
connectAttr "Ratcatcher_CTRL_STUFF_LAT_rotateX.a" "clipLibrary1.cel[0].cev[210].cevr"
		;
connectAttr "Ratcatcher_CTRL_STUFF_LAT_translateZ.a" "clipLibrary1.cel[0].cev[211].cevr"
		;
connectAttr "Ratcatcher_CTRL_STUFF_LAT_translateY.a" "clipLibrary1.cel[0].cev[212].cevr"
		;
connectAttr "Ratcatcher_CTRL_STUFF_LAT_translateX.a" "clipLibrary1.cel[0].cev[213].cevr"
		;
connectAttr "Ratcatcher_CTRL_STUFF_Follow.a" "clipLibrary1.cel[0].cev[214].cevr"
		;
connectAttr "Ratcatcher_CTRL_STUFF_Ikfollow.a" "clipLibrary1.cel[0].cev[215].cevr"
		;
connectAttr "Ratcatcher_CTRL_STUFF_rotateZ.a" "clipLibrary1.cel[0].cev[216].cevr"
		;
connectAttr "Ratcatcher_CTRL_STUFF_rotateY.a" "clipLibrary1.cel[0].cev[217].cevr"
		;
connectAttr "Ratcatcher_CTRL_STUFF_rotateX.a" "clipLibrary1.cel[0].cev[218].cevr"
		;
connectAttr "Ratcatcher_CTRL_STUFF_translateZ.a" "clipLibrary1.cel[0].cev[219].cevr"
		;
connectAttr "Ratcatcher_CTRL_STUFF_translateY.a" "clipLibrary1.cel[0].cev[220].cevr"
		;
connectAttr "Ratcatcher_CTRL_STUFF_translateX.a" "clipLibrary1.cel[0].cev[221].cevr"
		;
connectAttr "Ratcatcher_CTRL_POLEV_STUFF_translateZ.a" "clipLibrary1.cel[0].cev[222].cevr"
		;
connectAttr "Ratcatcher_CTRL_POLEV_STUFF_translateY.a" "clipLibrary1.cel[0].cev[223].cevr"
		;
connectAttr "Ratcatcher_CTRL_POLEV_STUFF_translateX.a" "clipLibrary1.cel[0].cev[224].cevr"
		;
connectAttr "animCurveTA1696.a" "clipLibrary1.cel[0].cev[225].cevr";
connectAttr "animCurveTA1697.a" "clipLibrary1.cel[0].cev[226].cevr";
connectAttr "animCurveTA1698.a" "clipLibrary1.cel[0].cev[227].cevr";
connectAttr "animCurveTL520.a" "clipLibrary1.cel[0].cev[228].cevr";
connectAttr "animCurveTL521.a" "clipLibrary1.cel[0].cev[229].cevr";
connectAttr "animCurveTL522.a" "clipLibrary1.cel[0].cev[230].cevr";
connectAttr "Ratcatcher_CTRL_IK_STUFF_rotateZ.a" "clipLibrary1.cel[0].cev[231].cevr"
		;
connectAttr "Ratcatcher_CTRL_IK_STUFF_rotateY.a" "clipLibrary1.cel[0].cev[232].cevr"
		;
connectAttr "Ratcatcher_CTRL_IK_STUFF_rotateX.a" "clipLibrary1.cel[0].cev[233].cevr"
		;
connectAttr "Ratcatcher_CTRL_IK_STUFF_translateZ.a" "clipLibrary1.cel[0].cev[234].cevr"
		;
connectAttr "Ratcatcher_CTRL_IK_STUFF_translateY.a" "clipLibrary1.cel[0].cev[235].cevr"
		;
connectAttr "Ratcatcher_CTRL_IK_STUFF_translateX.a" "clipLibrary1.cel[0].cev[236].cevr"
		;
connectAttr "animCurveTU530.a" "clipLibrary1.cel[0].cev[237].cevr";
connectAttr "animCurveTA1702.a" "clipLibrary1.cel[0].cev[238].cevr";
connectAttr "animCurveTA1703.a" "clipLibrary1.cel[0].cev[239].cevr";
connectAttr "animCurveTA1704.a" "clipLibrary1.cel[0].cev[240].cevr";
connectAttr "animCurveTL526.a" "clipLibrary1.cel[0].cev[241].cevr";
connectAttr "animCurveTL527.a" "clipLibrary1.cel[0].cev[242].cevr";
connectAttr "animCurveTL528.a" "clipLibrary1.cel[0].cev[243].cevr";
connectAttr "animCurveTA1705.a" "clipLibrary1.cel[0].cev[244].cevr";
connectAttr "animCurveTA1706.a" "clipLibrary1.cel[0].cev[245].cevr";
connectAttr "animCurveTA1707.a" "clipLibrary1.cel[0].cev[246].cevr";
connectAttr "animCurveTL529.a" "clipLibrary1.cel[0].cev[247].cevr";
connectAttr "animCurveTL530.a" "clipLibrary1.cel[0].cev[248].cevr";
connectAttr "animCurveTL531.a" "clipLibrary1.cel[0].cev[249].cevr";
connectAttr "animCurveTA1708.a" "clipLibrary1.cel[0].cev[250].cevr";
connectAttr "animCurveTA1709.a" "clipLibrary1.cel[0].cev[251].cevr";
connectAttr "animCurveTA1710.a" "clipLibrary1.cel[0].cev[252].cevr";
connectAttr "animCurveTL532.a" "clipLibrary1.cel[0].cev[253].cevr";
connectAttr "animCurveTL533.a" "clipLibrary1.cel[0].cev[254].cevr";
connectAttr "animCurveTL534.a" "clipLibrary1.cel[0].cev[255].cevr";
connectAttr "animCurveTA1711.a" "clipLibrary1.cel[0].cev[256].cevr";
connectAttr "animCurveTA1712.a" "clipLibrary1.cel[0].cev[257].cevr";
connectAttr "animCurveTA1713.a" "clipLibrary1.cel[0].cev[258].cevr";
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
connectAttr "animCurveTA1714.a" "clipLibrary1.cel[0].cev[272].cevr";
connectAttr "animCurveTA1715.a" "clipLibrary1.cel[0].cev[273].cevr";
connectAttr "animCurveTA1716.a" "clipLibrary1.cel[0].cev[274].cevr";
connectAttr "animCurveTA1717.a" "clipLibrary1.cel[0].cev[275].cevr";
connectAttr "animCurveTA1718.a" "clipLibrary1.cel[0].cev[276].cevr";
connectAttr "animCurveTA1719.a" "clipLibrary1.cel[0].cev[277].cevr";
connectAttr "animCurveTA1720.a" "clipLibrary1.cel[0].cev[278].cevr";
connectAttr "animCurveTA1721.a" "clipLibrary1.cel[0].cev[279].cevr";
connectAttr "animCurveTA1722.a" "clipLibrary1.cel[0].cev[280].cevr";
connectAttr "animCurveTA1723.a" "clipLibrary1.cel[0].cev[281].cevr";
connectAttr "animCurveTA1724.a" "clipLibrary1.cel[0].cev[282].cevr";
connectAttr "animCurveTA1725.a" "clipLibrary1.cel[0].cev[283].cevr";
connectAttr "animCurveTA1726.a" "clipLibrary1.cel[0].cev[284].cevr";
connectAttr "animCurveTA1727.a" "clipLibrary1.cel[0].cev[285].cevr";
connectAttr "animCurveTA1728.a" "clipLibrary1.cel[0].cev[286].cevr";
connectAttr "animCurveTU535.a" "clipLibrary1.cel[0].cev[287].cevr";
connectAttr "animCurveTU536.a" "clipLibrary1.cel[0].cev[288].cevr";
connectAttr "animCurveTU537.a" "clipLibrary1.cel[0].cev[289].cevr";
connectAttr "animCurveTA1729.a" "clipLibrary1.cel[0].cev[290].cevr";
connectAttr "animCurveTA1730.a" "clipLibrary1.cel[0].cev[291].cevr";
connectAttr "animCurveTA1731.a" "clipLibrary1.cel[0].cev[292].cevr";
connectAttr "animCurveTL544.a" "clipLibrary1.cel[0].cev[293].cevr";
connectAttr "animCurveTL545.a" "clipLibrary1.cel[0].cev[294].cevr";
connectAttr "animCurveTL546.a" "clipLibrary1.cel[0].cev[295].cevr";
connectAttr "animCurveTU538.a" "clipLibrary1.cel[0].cev[296].cevr";
connectAttr "animCurveTU539.a" "clipLibrary1.cel[0].cev[297].cevr";
connectAttr "animCurveTU540.a" "clipLibrary1.cel[0].cev[298].cevr";
connectAttr "animCurveTA1732.a" "clipLibrary1.cel[0].cev[299].cevr";
connectAttr "animCurveTA1733.a" "clipLibrary1.cel[0].cev[300].cevr";
connectAttr "animCurveTA1734.a" "clipLibrary1.cel[0].cev[301].cevr";
connectAttr "animCurveTL547.a" "clipLibrary1.cel[0].cev[302].cevr";
connectAttr "animCurveTL548.a" "clipLibrary1.cel[0].cev[303].cevr";
connectAttr "animCurveTL549.a" "clipLibrary1.cel[0].cev[304].cevr";
connectAttr "animCurveTA1735.a" "clipLibrary1.cel[0].cev[305].cevr";
connectAttr "animCurveTA1736.a" "clipLibrary1.cel[0].cev[306].cevr";
connectAttr "animCurveTA1737.a" "clipLibrary1.cel[0].cev[307].cevr";
connectAttr "animCurveTL550.a" "clipLibrary1.cel[0].cev[308].cevr";
connectAttr "animCurveTL551.a" "clipLibrary1.cel[0].cev[309].cevr";
connectAttr "animCurveTL552.a" "clipLibrary1.cel[0].cev[310].cevr";
connectAttr "animCurveTL553.a" "clipLibrary1.cel[0].cev[311].cevr";
connectAttr "animCurveTL554.a" "clipLibrary1.cel[0].cev[312].cevr";
connectAttr "animCurveTL555.a" "clipLibrary1.cel[0].cev[313].cevr";
connectAttr "Ratcatcher_CTRL_STUFF_scaleZ.a" "clipLibrary1.cel[0].cev[314].cevr"
		;
connectAttr "Ratcatcher_CTRL_STUFF_scaleY.a" "clipLibrary1.cel[0].cev[315].cevr"
		;
connectAttr "Ratcatcher_CTRL_STUFF_scaleX.a" "clipLibrary1.cel[0].cev[316].cevr"
		;
connectAttr "Ratcatcher_CTRL_STUFF_LAT_scaleZ.a" "clipLibrary1.cel[0].cev[317].cevr"
		;
connectAttr "Ratcatcher_CTRL_STUFF_LAT_scaleY.a" "clipLibrary1.cel[0].cev[318].cevr"
		;
connectAttr "Ratcatcher_CTRL_STUFF_LAT_scaleX.a" "clipLibrary1.cel[0].cev[319].cevr"
		;
connectAttr "Ratcatcher_CTRL_TwistR_rotateX.a" "clipLibrary1.cel[0].cev[320].cevr"
		;
connectAttr "Ratcatcher_CTRL_TwistL_rotateX.a" "clipLibrary1.cel[0].cev[321].cevr"
		;
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of ability02.ma
