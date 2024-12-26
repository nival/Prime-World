//Maya ASCII 2008 scene
//Name: attack3A.ma
//Last modified: Mon, Nov 23, 2009 11:07:51 AM
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
createNode animClip -n "attack3ASource";
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
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 9 9 9 9 9 9 9 
		9;
	setAttr -s 9 ".kot[0:8]"  3 5 5 5 5 5 5 5 
		5;
createNode animCurveTU -n "animCurveTU485";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 9 9 9 9 9 9 9 
		9;
	setAttr -s 9 ".kot[0:8]"  3 5 5 5 5 5 5 5 
		5;
createNode animCurveTU -n "animCurveTU486";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 3 1 4 1 6 1 10 1 16 1 32 1 44 1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU487";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 9 9 9 9 9 9 9 
		9;
	setAttr -s 9 ".kot[0:8]"  3 5 5 5 5 5 5 5 
		5;
createNode animCurveTA -n "animCurveTA1549";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1550";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1551";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU488";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU489";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL493";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.40930268174563 2 -0.094833842298427368 
		3 -0.51804269649286949 4 -0.50579365212221905 6 -0.16242686600098211 10 0.27814266879449157 
		16 -0.081775864099168705 32 0.40930268174563 44 0.40930268174563;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL494";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.25860394298924627 2 -1.1702511370520021 
		3 -1.9374504738854821 4 -1.9032415165077299 6 -0.2357132989777293 10 0.39150317760336084 
		16 0.71660148737179807 32 0.25860394298924627 44 0.25860394298924627;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL495";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.29847095663485657 2 -0.22458600188643554 
		3 0.070281355485890096 4 0.068212516310124774 6 0.033948436175669783 10 -0.013051049265007109 
		16 0.11016588475190847 32 -0.29847095663485657 44 -0.29847095663485657;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
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
	setAttr -s 9 ".ktv[0:8]"  0 25.675870473757751 2 25.675870473757751 
		3 25.675870473757751 4 25.675870473757751 6 25.675870473757751 10 25.675870473757751 
		16 25.675870473757751 32 25.675870473757751 44 25.675870473757751;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1556";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -3.0739741698828946 2 -3.0739741698828946 
		3 -3.0739741698828946 4 -3.0739741698828946 6 -3.0739741698828946 10 -3.0739741698828946 
		16 -3.0739741698828946 32 -3.0739741698828946 44 -3.0739741698828946;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU490";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 3 2 3 3 3 4 3 6 3 7 3 10 3 16 3 32 3 
		44 3;
createNode animCurveTU -n "animCurveTU491";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 3 0 4 0 6 0 7 0 10 0 16 0 32 0 
		44 0;
createNode animCurveTU -n "animCurveTU492";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 2 1 3 1 4 1 6 1 7 1 10 1 16 1 32 1 
		44 1;
	setAttr -s 10 ".kot[0:9]"  5 5 5 5 5 5 5 5 
		5 5;
createNode animCurveTU -n "animCurveTU493";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 3 0 4 0 6 0 7 0 10 0 16 0 32 0 
		44 0;
createNode animCurveTA -n "animCurveTA1557";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 93.144161708979723 1 54.141847468109148 
		2 34.624110191974658 3 -25.904595586596827 4 -24.469328193044984 5 29.580290256269276 
		6 82.516139456198289 7 126.38289932808421 8 163.72994088402348 10 209.2244434606518 
		16 159.67641536807452 32 90.829666034003637 44 93.144161708979723;
createNode animCurveTA -n "animCurveTA1558";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 95.049826002206416 1 145.77105232576935 
		2 188.9926152913863 3 294.86440959550879 4 292.55013138378337 5 216.84682199760812 
		6 170.20181499805147 7 170.94904643910286 8 180.94527541525233 10 196.32502971083704 
		16 174.55477613790393 32 91.228100587039862 44 95.049826002206416;
createNode animCurveTA -n "animCurveTA1559";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 1.1812364035166698 1 -2.6437247233897456 
		2 -52.990145102955672 3 -63.430020842341904 4 -62.154990332282701 5 -45.990990884795302 
		6 -6.7608586497737759 7 13.11550942100769 8 28.017122555935664 10 52.118530822865132 
		16 47.359805908741258 32 1.5462678303000612 44 1.1812364035166698;
createNode animCurveTL -n "animCurveTL496";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -0.23689498628395578 1 0.17610032053930211 
		2 0.87067410397399359 3 0.76734394674922957 4 0.7416474199556734 6 0.65313575252332168 
		7 0.46061924485576061 8 0.11210409002485809 10 -0.5941246180081009 16 -0.69705316985687971 
		32 -0.30046246223890594 44 -0.23689498628395578;
createNode animCurveTL -n "animCurveTL497";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -0.30633990936382105 1 0.22840038161142093 
		2 -0.56153981538907005 3 -1.3712857302513048 4 -1.3643852366658658 6 -0.20173767463767092 
		7 0.21275097233581852 8 0.68866970762926238 10 0.39205876872436657 16 0.30648298358026121 
		32 -0.30534117474053168 44 -0.30633990936382105;
createNode animCurveTL -n "animCurveTL498";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0.52899036848843184 1 -0.099695078733926551 
		2 -0.079463618781830919 3 0.0095615378322408667 4 0.023640264635652695 6 -0.054686464582899212 
		7 0.059110001010592231 8 0.11622808371444515 10 0.45706114014158944 16 0.18116797701229234 
		32 0.56821485312605569 44 0.52899036848843184;
createNode animCurveTU -n "animCurveTU494";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kot[1:8]"  5 5 5 5 5 5 5 5;
createNode animCurveTA -n "animCurveTA1560";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -24.884454396993167 2 4.0522251156844895 
		3 -25.429937762119746 4 -25.428980093111218 6 -34.232377238647729 10 26.935853283673584 
		16 28.507756207984524 32 -43.655121577080067 44 -24.884454396993167;
	setAttr -s 9 ".kit[0:8]"  9 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  9 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1561";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -43.339475474578435 2 -32.979648077916117 
		3 -25.506157766234107 4 -25.756433610933133 6 -45.370586933256469 10 -38.245797414247932 
		16 -44.589137138068004 32 -51.223766917491098 44 -43.339475474578435;
	setAttr -s 9 ".kit[0:8]"  9 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  9 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1562";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 11.606559612787883 2 -19.307952310111851 
		3 17.010351615289785 4 17.6883003413467 6 22.868455276578917 10 -26.620562644500058 
		16 -31.101372962759442 32 26.120519844381587 44 11.606559612787883;
	setAttr -s 9 ".kit[0:8]"  9 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  9 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU495";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 9 9 9 9 9 9 9 
		9;
	setAttr -s 9 ".kot[0:8]"  3 5 5 5 5 5 5 5 
		5;
createNode animCurveTU -n "animCurveTU496";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 9 9 9 9 9 9 9 
		9;
	setAttr -s 9 ".kot[0:8]"  3 5 5 5 5 5 5 5 
		5;
createNode animCurveTU -n "animCurveTU497";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  9 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  9 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU498";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 9 9 9 9 9 9 9 
		9;
	setAttr -s 9 ".kot[0:8]"  3 5 5 5 5 5 5 5 
		5;
createNode animCurveTA -n "animCurveTA1563";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 3.9531091186723013 2 3.9531091186723013 
		3 3.9531091186723013 4 3.9531091186723013 6 3.9531091186723013 10 -20.469282353836814 
		16 -20.469282353836814 32 3.9531091186723013 44 3.9531091186723013;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1564";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.62018686761647346 2 0.62018686761647346 
		3 0.62018686761647346 4 0.62018686761647346 6 0.62018686761647346 10 1.3026517411628151 
		16 1.3026517411628151 32 0.62018686761647346 44 0.62018686761647346;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1565";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 5.3292188742882338 2 5.3292188742882338 
		3 5.3292188742882338 4 5.3292188742882338 6 5.3292188742882338 10 -9.5717167522534279 
		16 -9.5717167522534279 32 5.3292188742882338 44 5.3292188742882338;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
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
	setAttr -s 9 ".ktv[0:8]"  0 -44.757110789561033 2 -35.306562584284926 
		3 -8.3049986114051926 4 -8.5570292474590666 6 -8.7335046183276628 10 -11.157388871190163 
		16 -14.947180105377107 32 -52.251062600717042 44 -44.757110789561033;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1567";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.10616870005340093 2 2.3548257308832836 
		3 5.6255992590384123 4 5.5693379757651948 6 5.5427050287573136 10 2.9157778850639047 
		16 -6.3525904578415542 32 3.7201031271197902 44 0.10616870005340093;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1568";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -4.9406171614869088 2 -8.5041245454747525 
		3 -13.687407620817627 4 -13.598248854524755 6 -13.5560429061214 10 -14.085301006557417 
		16 -17.518803824284443 32 -4.0334744307320998 44 -4.9406171614869088;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1569";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -27.604588158357807 2 -27.604588158357807 
		3 -27.604588158357807 4 -27.604588158357807 6 -27.604588158357807 10 -27.604588158357807 
		16 -27.604588158357807 32 -27.604588158357807 44 -27.604588158357807;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1570";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.70641431476594085 2 0.70641431476594085 
		3 0.70641431476594085 4 0.70641431476594085 6 0.70641431476594085 10 0.70641431476594085 
		16 0.70641431476594085 32 0.70641431476594085 44 0.70641431476594085;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
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
	setAttr -s 9 ".ktv[0:8]"  0 1 2 0.59259258048393737 3 0 4 0.010193311705143168 
		6 0 10 0 16 0 32 1 44 1;
	setAttr -s 9 ".kit[0:8]"  9 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  9 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1574";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1.1288109940741509 2 7.7309718923724651 
		3 17.334113878841436 4 17.168928154334271 6 0 10 0 16 0 32 1.1288109940741509 44 
		1.1288109940741509;
	setAttr -s 9 ".kit[0:8]"  9 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  9 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1575";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 4.8219581414201906 2 -2.3465783168489325 
		3 -12.773539564315577 4 -12.594183151943316 6 0 10 0 16 0 32 4.8219581414201906 44 
		4.8219581414201906;
	setAttr -s 9 ".kit[0:8]"  9 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  9 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1576";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 28.08558650754679 2 26.789285639866719 
		3 24.903757211755693 4 24.907496685115866 6 0 10 0 16 0 32 28.08558650754679 44 28.08558650754679;
	setAttr -s 9 ".kit[0:8]"  9 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  9 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU507";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1577";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 68.629003384766676 2 68.629003384766676 
		3 68.629003384766676 4 68.629003384766676 6 68.629003384766676 10 68.629003384766676 
		16 68.629003384766676 32 68.629003384766676 44 68.629003384766676;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1578";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 5.1251585428584878 2 5.1251585428584878 
		3 5.1251585428584878 4 5.1251585428584878 6 5.1251585428584878 10 5.1251585428584878 
		16 5.1251585428584878 32 5.1251585428584878 44 5.1251585428584878;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1579";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -1.4794141658124507 2 -1.4794141658124507 
		3 -1.4794141658124507 4 -1.4794141658124507 6 -1.4794141658124507 10 -1.4794141658124507 
		16 -1.4794141658124507 32 -1.4794141658124507 44 -1.4794141658124507;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1580";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 2.9967431843380723 2 2.9967431843380723 
		3 2.9967431843380723 4 2.9967431843380723 6 2.9967431843380723 10 2.9967431843380723 
		16 2.9967431843380723 32 2.9967431843380723 44 2.9967431843380723;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1581";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 27.356153209428296 2 27.356153209428296 
		3 27.356153209428296 4 27.356153209428296 6 27.356153209428296 10 27.356153209428296 
		16 27.356153209428296 32 27.356153209428296 44 27.356153209428296;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1582";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 4.8891453517792058 2 4.8891453517792058 
		3 4.8891453517792058 4 4.8891453517792058 6 4.8891453517792058 10 4.8891453517792058 
		16 4.8891453517792058 32 4.8891453517792058 44 4.8891453517792058;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU508";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1583";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 59.032884886088816 2 59.032884886088816 
		3 59.032884886088816 4 59.032884886088816 6 59.032884886088816 10 59.032884886088816 
		16 59.032884886088816 32 59.032884886088816 44 59.032884886088816;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1584";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1585";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1586";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 61.945270723308987 2 61.945270723308987 
		3 61.945270723308987 4 61.945270723308987 6 61.945270723308987 10 61.945270723308987 
		16 61.945270723308987 32 61.945270723308987 44 61.945270723308987;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1587";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1588";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU509";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1589";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 59.032884886088816 2 59.032884886088816 
		3 59.032884886088816 4 59.032884886088816 6 59.032884886088816 10 59.032884886088816 
		16 59.032884886088816 32 59.032884886088816 44 59.032884886088816;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1590";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1591";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1592";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 61.945270723308987 2 61.945270723308987 
		3 61.945270723308987 4 61.945270723308987 6 61.945270723308987 10 61.945270723308987 
		16 61.945270723308987 32 61.945270723308987 44 61.945270723308987;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1593";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1594";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU510";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1595";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 59.032884886088816 2 59.032884886088816 
		3 59.032884886088816 4 59.032884886088816 6 59.032884886088816 10 59.032884886088816 
		16 59.032884886088816 32 59.032884886088816 44 59.032884886088816;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1596";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1597";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1598";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 72.878304588436421 2 72.878304588436421 
		3 72.878304588436421 4 72.878304588436421 6 72.878304588436421 10 72.878304588436421 
		16 72.878304588436421 32 72.878304588436421 44 72.878304588436421;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1599";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1600";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU511";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1601";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 77.67986202714836 2 77.67986202714836 
		3 77.67986202714836 4 77.67986202714836 6 77.67986202714836 10 77.67986202714836 
		16 77.67986202714836 32 77.67986202714836 44 77.67986202714836;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1602";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1603";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1604";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 65.952779168408995 2 65.952779168408995 
		3 65.952779168408995 4 65.952779168408995 6 65.952779168408995 10 65.952779168408995 
		16 65.952779168408995 32 65.952779168408995 44 65.952779168408995;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1605";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 12.091864976351665 2 12.091864976351665 
		3 12.091864976351665 4 12.091864976351665 6 12.091864976351665 10 12.091864976351665 
		16 12.091864976351665 32 12.091864976351665 44 12.091864976351665;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1606";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -6.5683373417752975 2 -6.5683373417752975 
		3 -6.5683373417752975 4 -6.5683373417752975 6 -6.5683373417752975 10 -6.5683373417752975 
		16 -6.5683373417752975 32 -6.5683373417752975 44 -6.5683373417752975;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1607";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1608";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1609";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU512";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1610";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1611";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1612";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1613";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1614";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1615";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU513";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1616";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1617";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1618";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1619";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1620";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1621";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU514";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1622";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1623";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1624";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1625";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1626";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1627";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU515";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1628";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1629";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1630";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1631";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1632";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1633";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU516";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1634";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1635";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1636";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1637";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1638";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1639";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1640";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1641";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1642";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU517";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 9 9 9 9 9 9 9 
		9;
	setAttr -s 9 ".kot[0:8]"  3 5 5 5 5 5 5 5 
		5;
createNode animCurveTU -n "animCurveTU518";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 9 9 9 9 9 9 9 
		9;
	setAttr -s 9 ".kot[0:8]"  3 5 5 5 5 5 5 5 
		5;
createNode animCurveTU -n "animCurveTU519";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 3 1 4 1 6 1 10 1 16 1 32 1 44 1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1643";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -10.173354040024311 2 -10.173354040024311 
		3 -10.173354040024311 4 -10.173354040024311 6 -10.173354040024311 10 -10.173354040024311 
		16 -10.173354040024311 32 -10.173354040024311 44 -10.173354040024311;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1644";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1645";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL505";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL506";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.643246524321337 2 0.643246524321337 
		3 0.643246524321337 4 0.643246524321337 6 0.643246524321337 10 0.643246524321337 
		16 0.643246524321337 32 0.643246524321337 44 0.643246524321337;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL507";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.10481400598920043 2 0.10481400598920043 
		3 0.10481400598920043 4 0.10481400598920043 6 0.10481400598920043 10 0.10481400598920043 
		16 0.10481400598920043 32 0.10481400598920043 44 0.10481400598920043;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
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
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 3 1 4 1 6 1 10 1 16 1 32 1 44 1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1658";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 40.718223104721211 2 40.718223104721211 
		3 40.718223104721211 4 40.718223104721211 6 40.718223104721211 10 40.718223104721211 
		16 40.718223104721211 32 40.718223104721211 44 40.718223104721211;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1659";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -38.301705751263519 2 -38.301705751263519 
		3 -38.301705751263519 4 -38.301705751263519 6 -38.301705751263519 10 -38.301705751263519 
		16 -38.301705751263519 32 -38.301705751263519 44 -38.301705751263519;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1660";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 21.733945627788874 2 21.733945627788874 
		3 21.733945627788874 4 21.733945627788874 6 21.733945627788874 10 21.733945627788874 
		16 21.733945627788874 32 21.733945627788874 44 21.733945627788874;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU522";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 9 9 9 9 9 9 9 
		9;
	setAttr -s 9 ".kot[0:8]"  3 5 5 5 5 5 5 5 
		5;
createNode animCurveTU -n "animCurveTU523";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 9 9 9 9 9 9 9 
		9;
	setAttr -s 9 ".kot[0:8]"  3 5 5 5 5 5 5 5 
		5;
createNode animCurveTU -n "animCurveTU524";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 3 1 4 1 6 1 10 1 16 1 32 1 44 1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1661";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 17.962181958626559 2 17.962181958626559 
		3 17.962181958626559 4 17.962181958626559 6 17.962181958626559 10 17.962181958626559 
		16 17.962181958626559 32 17.962181958626559 44 17.962181958626559;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1662";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1663";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL508";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL509";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.64789329560123088 2 -0.64789329560123088 
		3 -0.64789329560123088 4 -0.64789329560123088 6 -0.64789329560123088 10 -0.64789329560123088 
		16 -0.64789329560123088 32 -0.64789329560123088 44 -0.64789329560123088;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL510";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.07395615046270454 2 -0.07395615046270454 
		3 -0.07395615046270454 4 -0.07395615046270454 6 -0.07395615046270454 10 -0.07395615046270454 
		16 -0.07395615046270454 32 -0.07395615046270454 44 -0.07395615046270454;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
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
	setAttr -s 9 ".ktv[0:8]"  0 -10.753373031419716 2 55.386708886047387 
		3 51.98783591148176 4 50.450073345959076 6 40.112507323442273 10 31.49719749226178 
		16 31.49719749226178 32 -10.753373031419716 44 -10.753373031419716;
	setAttr -s 9 ".kit[0:8]"  9 3 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  9 3 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1677";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -4.9387346018875373 2 -5.6269833207583755 
		3 2.0863065811267987 4 2.0932848768315861 6 25.12560013764438 10 17.250483513982392 
		16 17.250483513982392 32 -4.9387346018875373 44 -4.9387346018875373;
	setAttr -s 9 ".kit[0:8]"  9 10 10 10 10 10 9 10 
		10;
	setAttr -s 9 ".kot[0:8]"  9 10 10 10 10 10 9 10 
		10;
createNode animCurveTA -n "animCurveTA1678";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 22.393157938684443 2 15.810243551730299 
		3 18.218057917893841 4 18.222964741639991 6 28.650917305122007 10 21.492351788843198 
		16 21.492351788843198 32 22.393157938684443 44 22.393157938684443;
	setAttr -s 9 ".kit[0:8]"  9 10 10 10 10 1 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  9 10 10 10 10 1 10 10 
		10;
	setAttr -s 9 ".kix[5:8]"  0.92206978797912598 1 1 1;
	setAttr -s 9 ".kiy[5:8]"  0.3870236873626709 0 0 0;
	setAttr -s 9 ".kox[5:8]"  0.92206978797912598 1 1 1;
	setAttr -s 9 ".koy[5:8]"  0.38702371716499329 0 0 0;
createNode animCurveTA -n "animCurveTA1679";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -4.0865779949808214 2 -7.1447003970887861 
		3 -15.882192221247193 4 -15.800637102062987 6 -15.743531070535084 10 28.833282209954707 
		16 26.468188010134913 32 -4.0865779949808214 44 -4.0865779949808214;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1680";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -10.471027640707172 2 -9.560873570274449 
		3 -6.9604335932320724 4 -6.9645594502624268 6 -6.9816534800972114 10 -2.4917720806699637 
		16 -3.8719345681296322 32 -10.471027640707172 44 -10.471027640707172;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1681";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -1.7475532445702493 2 -0.1196535895028505 
		3 4.5314878811254165 4 4.4880744622669262 6 4.4576757824239355 10 2.2171879760012998 
		16 2.3059747376266406 32 -1.7475532445702493 44 -1.7475532445702493;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU526";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 3 1 4 1 6 1 10 1 16 1 32 1 44 1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1682";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 20.69101533741409 2 17.20655976022292 
		3 7.2509732551291428 4 7.3438979757347624 6 2.6480641297884957 10 51.402272395629836 
		16 48.346081025611866 32 20.231825483747954 44 20.69101533741409;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1683";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -8.3978566024888135 2 -8.8857712974790495 
		3 -10.279813162979707 4 -10.276509136516941 6 13.612026599257481 10 3.6936902748123548 
		16 -1.4436397757686652 32 -7.2475020471708085 44 -8.3978566024888135;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1684";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 2.8255796210686652 2 4.2496413314714276 
		3 8.3183887246968897 4 8.2804113295642523 6 -7.893617749676336 10 -6.338312372451357 
		16 5.7512765978597278 32 7.1152482630677394 44 2.8255796210686652;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU527";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 8 0 14 0 22 0 30 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1685";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 -42.52889422086826 8 27.968998100227505 
		14 44.73720949507679 22 0 30 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1686";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 16.355923914401359 8 -6.398664218415778 
		14 13.729174731778382 22 0 30 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1687";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 3.171975457428942 8 5.7527589455042474 
		14 -2.2996172608481769 22 0 30 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1688";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -17.821366541589882 2 -17.821366541589882 
		3 -17.821366541589882 4 17.957220026014085 8 34.945180963685836 14 -17.821366541589882 
		22 -19.289156434173741 30 -17.821366541589882 38 -17.821366541589882 44 -17.821366541589882;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1689";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -12.005893876475762 2 -12.005893876475762 
		3 -12.005893876475762 4 -20.711871391362973 8 -28.554106724194472 14 -12.005893876475762 
		22 7.0895872242641671 30 -12.005893876475762 38 -12.005893876475762 44 -12.005893876475762;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1690";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 9.1378572146953019 2 9.1378572146953019 
		3 9.1378572146953019 4 18.876742525483944 8 4.2675314193407283 14 9.1378572146953019 
		22 8.7729870150940084 30 9.1378572146953019 38 9.1378572146953019 44 9.1378572146953019;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTA -n "animCurveTA1691";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -28.841216077843235 2 -28.841216077843235 
		3 -28.841216077843235 4 -28.841216077843235 6 -28.841216077843235 10 -28.841216077843235 
		16 -28.841216077843235 32 -28.841216077843235 44 -28.841216077843235;
	setAttr -s 9 ".kit[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kix[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[0:8]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1692";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -21.716766331039956 2 -21.716766331039956 
		3 -21.716766331039956 4 -21.716766331039956 6 -21.716766331039956 10 -21.716766331039956 
		16 -21.716766331039956 32 -21.716766331039956 44 -21.716766331039956;
	setAttr -s 9 ".kit[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kix[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[0:8]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1693";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 23.535235892507558 2 23.535235892507558 
		3 23.535235892507558 4 23.535235892507558 6 23.535235892507558 10 23.535235892507558 
		16 23.535235892507558 32 23.535235892507558 44 23.535235892507558;
	setAttr -s 9 ".kit[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kix[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[0:8]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL511";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kix[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[0:8]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL512";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kix[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[0:8]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL513";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  1 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kix[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[0:8]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[0:8]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[0:8]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU528";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 2 2 2 3 2 4 2 6 2 10 2 16 2 32 2 44 2;
	setAttr -s 9 ".kit[0:8]"  3 9 9 9 9 9 9 9 
		9;
	setAttr -s 9 ".kot[0:8]"  3 5 5 5 5 5 5 5 
		5;
createNode animCurveTU -n "animCurveTU529";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 9 9 9 9 9 9 9 
		9;
	setAttr -s 9 ".kot[0:8]"  3 5 5 5 5 5 5 5 
		5;
createNode animCurveTA -n "animCurveTA1694";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -24.093441664171177 2 -24.093441664171177 
		3 -24.093441664171177 4 -24.093441664171177 6 -24.093441664171177 10 -24.093441664171177 
		16 -24.093441664171177 32 -24.093441664171177 44 -24.093441664171177;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1695";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 49.48465546224881 2 49.48465546224881 
		3 49.48465546224881 4 49.48465546224881 6 49.48465546224881 10 49.48465546224881 
		16 49.48465546224881 32 49.48465546224881 44 49.48465546224881;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1696";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 58.801792680015588 2 58.801792680015588 
		3 58.801792680015588 4 58.801792680015588 6 58.801792680015588 10 58.801792680015588 
		16 58.801792680015588 32 58.801792680015588 44 58.801792680015588;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL514";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -1.2755255474500937 2 -1.2755255474500937 
		3 -1.2755255474500937 4 -1.2755255474500937 6 -1.2755255474500937 10 -1.2755255474500937 
		16 -1.2755255474500937 32 -1.2755255474500937 44 -1.2755255474500937;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL515";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -1.4392043230118035 2 -1.4392043230118035 
		3 -1.4392043230118035 4 -1.4392043230118035 6 -1.4392043230118035 10 -1.4392043230118035 
		16 -1.4392043230118035 32 -1.4392043230118035 44 -1.4392043230118035;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL516";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -2.1802956492995231 2 -2.1802956492995231 
		3 -2.1802956492995231 4 -2.1802956492995231 6 -2.1802956492995231 10 -2.1802956492995231 
		16 -2.1802956492995231 32 -2.1802956492995231 44 -2.1802956492995231;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL517";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL518";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL519";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1697";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.1134085745786892 4 5.0681602718692886 
		6 1.1134085745786892 10 1.1134085745786892 16 1.1134085745786892 32 4.0403109631670997 
		44 1.1134085745786892;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA1698";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -5.3180374758492821 4 9.9860072874988273 
		6 -5.3180374758492821 10 -5.3180374758492821 16 -5.3180374758492821 32 -11.069192470825783 
		44 -5.3180374758492821;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA1699";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 7.8609313736722894 4 -20.189926927429539 
		6 7.8609313736722894 10 -27.541159036436291 16 7.8609313736722894 32 4.9181237743209776 
		44 7.8609313736722894;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTL -n "animCurveTL520";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTL -n "animCurveTL521";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTL -n "animCurveTL522";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA1700";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1701";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1702";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL523";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL524";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL525";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU530";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 9 9 9 9 9 9 9 
		9;
	setAttr -s 9 ".kot[0:8]"  3 5 5 5 5 5 5 5 
		5;
createNode animCurveTA -n "animCurveTA1703";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -5.1107219305963252 2 -5.1107219305963252 
		3 -5.1107219305963252 4 -5.1107219305963252 6 -5.1107219305963252 10 -5.1107219305963252 
		16 -5.1107219305963252 32 -5.1107219305963252 44 -5.1107219305963252;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1704";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 8.2811672786141717 2 8.2811672786141717 
		3 8.2811672786141717 4 8.2811672786141717 6 8.2811672786141717 10 8.2811672786141717 
		16 8.2811672786141717 32 8.2811672786141717 44 8.2811672786141717;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1705";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.92645454014921158 2 -0.92645454014921158 
		3 -0.92645454014921158 4 -0.92645454014921158 6 -0.92645454014921158 10 -0.92645454014921158 
		16 -0.92645454014921158 32 -0.92645454014921158 44 -0.92645454014921158;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL526";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.046856395845859107 2 -0.046856395845859107 
		3 -0.046856395845859107 4 -0.046856395845859107 6 -0.046856395845859107 10 -0.046856395845859107 
		16 -0.046856395845859107 32 -0.046856395845859107 44 -0.046856395845859107;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL527";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.023348763690700665 2 -0.023348763690700665 
		3 -0.023348763690700665 4 -0.023348763690700665 6 -0.023348763690700665 10 -0.023348763690700665 
		16 -0.023348763690700665 32 -0.023348763690700665 44 -0.023348763690700665;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL528";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.13506113021862395 2 -0.13506113021862395 
		3 -0.13506113021862395 4 -0.13506113021862395 6 -0.13506113021862395 10 -0.13506113021862395 
		16 -0.13506113021862395 32 -0.13506113021862395 44 -0.13506113021862395;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1706";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -1.6266160090263075 2 -1.6266160090263075 
		3 -1.6266160090263075 4 -1.6266160090263075 6 -0.56224168053615053 10 11.226960836843418 
		16 -21.371648725781281 32 -1.6266160090263075 44 -1.6266160090263075;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1707";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 2.8499857758927387 2 2.8499857758927387 
		3 2.8499857758927387 4 2.8499857758927387 6 9.2092505607893482 10 -20.790630914481934 
		16 -18.424412551656808 32 2.8499857758927387 44 2.8499857758927387;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1708";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -25.210898828531619 2 -25.210898828531619 
		3 -25.210898828531619 4 -25.210898828531619 6 -29.368891809790064 10 -42.015256350726858 
		16 -30.546310268820974 32 -25.210898828531619 44 -25.210898828531619;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL529";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.011193700785458628 2 -0.011193700785458628 
		3 -0.011193700785458628 4 -0.011193700785458628 6 -0.011193700785458628 10 -0.011193700785458628 
		16 -0.011193700785458628 32 -0.011193700785458628 44 -0.011193700785458628;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL530";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.020021267836214246 2 -0.020021267836214246 
		3 -0.020021267836214246 4 -0.020021267836214246 6 -0.020021267836214246 10 -0.020021267836214246 
		16 -0.020021267836214246 32 -0.020021267836214246 44 -0.020021267836214246;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL531";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.032441787830836878 2 0.032441787830836878 
		3 0.032441787830836878 4 0.032441787830836878 6 0.032441787830836878 10 0.032441787830836878 
		16 0.032441787830836878 32 0.032441787830836878 44 0.032441787830836878;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1709";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1710";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1711";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL532";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL533";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL534";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1712";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -15.609971163878811 2 -10.95924915563312 
		3 1.289775591809053 4 1.1669692545102328 6 -0.68006237044093243 10 -54.208279742329772 
		16 -54.208279742329772 32 -15.609971163878811 44 -15.609971163878811;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1713";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 8.3116042646716988 2 7.7444891224907826 
		3 1.0505087842156258 4 1.0715956703502365 6 0.39178894174035839 10 0.12594526489310931 
		16 0.12594526489310931 32 8.3116042646716988 44 8.3116042646716988;
	setAttr -s 9 ".kit[0:8]"  3 1 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 1 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kix[1:8]"  0.98598784208297729 1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[1:8]"  -0.16681718826293945 0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[1:8]"  0.98598790168762207 1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[1:8]"  -0.16681720316410065 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1714";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 14.458598883932659 2 8.5084279529715037 
		3 16.851899548094515 4 16.847697788662998 6 11.013662249309455 10 17.609319625346345 
		16 17.609319625346345 32 14.458598883932659 44 14.458598883932659;
	setAttr -s 9 ".kit[0:8]"  3 3 10 10 10 10 1 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 3 10 10 10 10 1 10 
		10;
	setAttr -s 9 ".kix[6:8]"  0.97271400690078735 1 1;
	setAttr -s 9 ".kiy[6:8]"  0.23200750350952148 0 0;
	setAttr -s 9 ".kox[6:8]"  0.97271400690078735 1 1;
	setAttr -s 9 ".koy[6:8]"  0.23200754821300507 0 0;
createNode animCurveTL -n "animCurveTL535";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.18868131369562219 2 -0.23385290990938803 
		3 -0.36291460225038347 4 -0.40888986920054454 6 -0.27570144939928176 10 -0.28154931606525113 
		16 -0.28154931606525113 32 -0.21395459514386589 44 -0.18868131369562219;
	setAttr -s 9 ".kit[0:8]"  3 9 9 10 10 10 10 9 
		10;
	setAttr -s 9 ".kot[0:8]"  3 9 9 10 10 10 10 9 
		10;
createNode animCurveTL -n "animCurveTL536";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.23059098815955009 2 0.14103936045235135 
		3 0.010782455763551024 4 0.013023032668975348 6 0.29541912608519677 10 0.29541912608519677 
		16 0.29541912608519677 32 0.30642751827182835 44 0.23059098815955009;
	setAttr -s 9 ".kit[0:8]"  9 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  9 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL537";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.049918713102953649 2 0.045007403063963045 
		3 0.030975089876626949 4 0.031008347941002316 6 -0.030387164957472845 10 -0.030387164957472845 
		16 -0.030387164957472845 32 0.045148764678818398 44 0.049918713102953649;
	setAttr -s 9 ".kit[0:8]"  3 9 10 10 10 10 10 9 
		10;
	setAttr -s 9 ".kot[0:8]"  3 9 10 10 10 10 10 9 
		10;
createNode animCurveTU -n "animCurveTU531";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 9 9 9 9 9 9 9 
		9;
	setAttr -s 9 ".kot[0:8]"  3 5 5 5 5 5 5 5 
		5;
createNode animCurveTU -n "animCurveTU532";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.084155571970393403 2 0.084155571970393403 
		3 0.084155571970393403 4 0.084155571970393403 6 0.084155571970393403 10 0.084155571970393403 
		16 0.084155571970393403 32 0.084155571970393403 44 0.084155571970393403;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL538";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.067207227343123899 2 0.067207227343123899 
		3 0.067207227343123899 4 0.067207227343123899 6 0.067207227343123899 10 0.067207227343123899 
		16 0.067207227343123899 32 0.067207227343123899 44 0.067207227343123899;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL539";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.20472824713235571 2 -0.20472824713235571 
		3 -0.20472824713235571 4 -0.20472824713235571 6 -0.20472824713235571 10 -0.20472824713235571 
		16 -0.20472824713235571 32 -0.20472824713235571 44 -0.20472824713235571;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL540";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.20941646546924442 2 0.20941646546924442 
		3 0.20941646546924442 4 0.20941646546924442 6 0.20941646546924442 10 0.20941646546924442 
		16 0.20941646546924442 32 0.20941646546924442 44 0.20941646546924442;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU533";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 9 9 9 9 9 9 9 
		9;
	setAttr -s 9 ".kot[0:8]"  3 5 5 5 5 5 5 5 
		5;
createNode animCurveTU -n "animCurveTU534";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.084155864375844894 2 0.084155864375844894 
		3 0.084155864375844894 4 0.084155864375844894 6 0.084155864375844894 10 0.084155864375844894 
		16 0.084155864375844894 32 0.084155864375844894 44 0.084155864375844894;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL541";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL542";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.40088449385078673 2 -0.40088449385078673 
		3 -0.40088449385078673 4 -0.40088449385078673 6 -0.40088449385078673 10 -0.40088449385078673 
		16 -0.40088449385078673 32 -0.40088449385078673 44 -0.40088449385078673;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL543";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.69609418843799409 2 -0.69609418843799409 
		3 -0.69609418843799409 4 -0.69609418843799409 6 -0.69609418843799409 10 -0.69609418843799409 
		16 -0.69609418843799409 32 -0.69609418843799409 44 -0.69609418843799409;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1715";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 14.255651060312635 6 -15.111149728053332 
		10 13.464190606921466 16 13.569272489838719 32 0 44 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA1716";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 -6.1452081572710275 6 0 10 0 
		16 0 32 0 44 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA1717";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 -1.2912643771432435 6 0 10 0 
		16 0 32 0 44 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA1718";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1719";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1720";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1721";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 15.244055449368698 6 -8.6427077911027403 
		10 19.201300170978502 16 8.0521958611787436 32 0 44 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA1722";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA1723";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA1724";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -18.592620239620459 3 -9.9242436385090347 
		6 -33.711577022782123 10 -6.9158247002603153 16 -22.407315833816483 32 -18.592620239620459 
		44 -18.592620239620459;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA1725";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -4.0495369920864128 3 -9.2383557968473689 
		6 3.7687087524130711 10 -7.5258022672121809 16 -1.0362678615371348 32 -4.0495369920864128 
		44 -4.0495369920864128;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA1726";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -24.718935474963271 3 -25.776808605189167 
		6 -19.426057835375328 10 -29.411007504436775 16 -22.946313460432716 32 -24.718935474963271 
		44 -24.718935474963271;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA1727";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1728";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1729";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU535";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 3 1 4 1 6 1 10 1 16 1 32 1 44 1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU536";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 3 1 4 1 6 1 10 1 16 1 32 1 44 1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU537";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 3 1 4 1 6 1 10 1 16 1 32 1 44 1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1730";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1731";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1732";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL544";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL545";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL546";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU538";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 3 1 4 1 6 1 10 1 16 1 32 1 44 1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU539";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 3 1 4 1 6 1 10 1 16 1 32 1 44 1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU540";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 3 1 4 1 6 1 10 1 16 1 32 1 44 1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1733";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1734";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1735";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL547";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL548";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL549";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1736";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1737";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1738";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 7.2644697342894906 2 7.2644697342894906 
		3 7.2644697342894906 4 7.2644697342894906 6 7.2644697342894906 10 7.2644697342894906 
		16 7.2644697342894906 32 7.2644697342894906 44 7.2644697342894906;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL550";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL551";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL552";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTL -n "animCurveTL553";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.000119480405310887 2 -0.000119480405310887 
		3 -0.000119480405310887 4 -0.000119480405310887 8 -0.000119480405310887 14 -0.000119480405310887 
		22 -0.000119480405310887 30 -0.000119480405310887 38 -0.000119480405310887 44 -0.000119480405310887;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL554";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.1152566135867675 2 0.1152566135867675 
		3 0.1152566135867675 4 0.1152566135867675 8 0.1152566135867675 14 0.1152566135867675 
		22 0.1152566135867675 30 0.1152566135867675 38 0.1152566135867675 44 0.1152566135867675;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTL -n "animCurveTL555";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.19515846066137013 2 0.19515846066137013 
		3 0.19515846066137013 4 0.19515846066137013 8 0.19515846066137013 14 0.19515846066137013 
		22 0.19515846066137013 30 0.19515846066137013 38 0.19515846066137013 44 0.19515846066137013;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 10;
createNode animCurveTU -n "animCurveTU541";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 3 1 4 1 6 1 10 1 16 1 32 1 44 1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU542";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 3 1 4 1 6 1 10 1 16 1 32 1 44 1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU543";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 3 1 4 1 6 1 10 1 16 1 32 1 44 1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU544";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 3 1 4 1 6 1 10 1 16 1 32 1 44 1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU545";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 3 1 4 1 6 1 10 1 16 1 32 1 44 1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTU -n "animCurveTU546";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 2 1 3 1 4 1 6 1 10 1 16 1 32 1 44 1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 10 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 10 
		10;
createNode animCurveTA -n "animCurveTA1739";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
createNode animCurveTA -n "Ratcatcher_CTRL_TwistL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  2 0 3 0 4 0 6 0 10 0 16 0 32 0 44 0;
createNode animCurveTU -n "animCurveTU547";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 4 1 6 1 10 1 16 1 32 1 44 1;
createNode animCurveTU -n "animCurveTU548";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 4 1 6 1 10 1 16 1 32 1 44 1;
createNode animCurveTU -n "animCurveTU549";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 4 1 6 1 10 1 16 1 32 1 44 1;
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
connectAttr "attack3ASource.cl" "clipLibrary1.sc[0]";
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
connectAttr "Ratcatcher_CTRL_TwistL_rotateX1.a" "clipLibrary1.cel[0].cev[321].cevr"
		;
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
// End of attack3A.ma
