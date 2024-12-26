//Maya ASCII 2008 scene
//Name: death.ma
//Last modified: Fri, Aug 14, 2009 05:37:06 PM
//Codeset: 1251
requires maya "2008";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Unlimited 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200802250025-718075";
fileInfo "osv" "Microsoft Windows XP Service Pack 3 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 320 ".cel[0].cev";
	setAttr ".cd[0].cm" -type "characterMapping" 320 "Ratcatcher_rt_upArm_fk_ctrl_Align.align" 
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
		0 63 "CTRL_STUFF_LAT.scaleX" 0 64  ;
	setAttr ".cd[0].cim" -type "Int32Array" 320 0 1 2 3 4
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
		 317 318 319 ;
createNode animClip -n "deathSource1";
	setAttr ".ihi" 0;
	setAttr -s 320 ".ac[0:319]" yes yes yes yes yes yes yes yes yes yes yes 
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
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".se" 43;
	setAttr ".ci" no;
createNode animCurveTU -n "animCurveTU233";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 9 1 9 9 9 9 9 
		9 9 1 9 3;
	setAttr -s 13 ".kot[0:12]"  3 5 5 5 5 5 5 5 
		5 5 5 5 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA773";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA774";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 3.1805546814635176e-015 2 0 5 0 7 0 11 
		0 22 0 27 0 31 0 33 0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA775";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 9.9392333795734924e-017 2 0 5 0 7 0 11 
		0 22 0 27 0 31 0 33 0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU234";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 9 1 9 9 9 9 9 
		9 9 1 9 3;
	setAttr -s 13 ".kot[0:12]"  3 5 5 5 5 5 5 5 
		5 5 5 5 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU235";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 9 1 9 9 9 9 9 
		9 9 1 9 3;
	setAttr -s 13 ".kot[0:12]"  3 5 5 5 5 5 5 5 
		5 5 5 5 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU236";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 1 2 1 5 1 7 1 11 1 22 1 27 1 31 1 33 
		1 36 1 39 1 41 1 43 1;
	setAttr -s 13 ".kit[0:12]"  9 10 1 10 10 10 10 3 
		3 3 3 10 3;
	setAttr -s 13 ".kot[0:12]"  9 10 1 10 10 10 10 3 
		3 3 3 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU237";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 9 1 9 9 9 9 9 
		9 9 1 9 3;
	setAttr -s 13 ".kot[0:12]"  3 5 5 5 5 5 5 5 
		5 5 5 5 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA776";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 3.1805546814635168e-015 2 0 5 0 7 0 11 
		0 22 0 27 0 31 0 33 0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA777";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA778";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 4.7708320221952728e-015 2 0 5 0 7 0 11 
		0 22 0 27 0 31 0 33 0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU238";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 2 0 5 0 7 0 11 0 16 0 19 0 31 0 33 
		0 38 0 41 0 43 0;
	setAttr -s 12 ".kit[0:11]"  3 10 1 10 10 10 10 10 
		1 1 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 1 10 10 10 10 10 
		1 1 10 3;
	setAttr -s 12 ".kix[2:11]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[2:11]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[2:11]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[2:11]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU239";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 2 0 5 0 7 0 11 0 16 0 19 0 31 0 33 
		0 38 0 41 0 43 0;
	setAttr -s 12 ".kit[0:11]"  3 10 1 10 10 10 10 10 
		1 1 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 1 10 10 10 10 10 
		1 1 10 3;
	setAttr -s 12 ".kix[2:11]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[2:11]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[2:11]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[2:11]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL247";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0.40930268174563 2 0.40930268174563 5 
		0.40930268174563 7 0.40930268174563 11 0.40930268174563 16 -0.14264384674101638 19 
		-0.2733840170447045 24 -0.23969504691996502 27 -1.1441267747678592 31 -2.6151872173586188 
		33 -2.3822454679921456 38 -2.3822454679921456 41 -2.3822454679921456 43 -2.3822454679921456;
	setAttr -s 14 ".kit[0:13]"  3 10 1 10 10 10 10 10 
		10 10 1 1 1 3;
	setAttr -s 14 ".kot[0:13]"  3 10 1 10 10 10 10 10 
		10 10 1 1 1 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 0.36384123563766479 1 1 0.097754798829555511 
		0.15946829319000244 1 1 1 1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 -0.93146097660064697 0 0 -0.99521052837371826 
		-0.98720306158065796 0 0 0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 0.36384123563766479 1 1 0.097754798829555511 
		0.15946829319000244 1 1 1 1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 -0.93146097660064697 0 0 -0.99521052837371826 
		-0.98720306158065796 0 0 0 0;
createNode animCurveTL -n "animCurveTL248";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0.25860394298924627 2 0.25860394298924627 
		5 0.25860394298924627 7 0.25860394298924627 11 0.25860394298924627 16 0.043962614864251542 
		19 -0.32244132862891406 27 0.70517909635932785 31 2.3920239954989824 33 2.3920239954989824 
		38 2.3920239954989824 41 2.3920239954989824 43 2.3920239954989824;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 1 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 1 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 0.4171125590801239 0.48495972156524658 
		0.14578433334827423 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 -0.90885478258132935 0.87453651428222656 
		0.98931640386581421 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 0.4171125590801239 0.48495972156524658 
		0.14578433334827423 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 -0.90885478258132935 0.87453651428222656 
		0.98931640386581421 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL249";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -0.29847095663485657 2 -0.29847095663485657 
		5 -0.29847095663485657 7 -0.29847095663485657 11 -0.29847095663485657 16 -0.15615866665534653 
		19 0.1488188325414827 27 1.5638100199096989 31 2.2320021923054867 33 2.2320021923054867 
		38 2.2320021923054867 41 2.2320021923054867 43 2.2320021923054867;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 1 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 1 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 0.51208311319351196 0.20849703252315521 
		0.18856906890869141 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0.8589358925819397 0.9780229926109314 
		0.98205989599227905 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 0.51208311319351196 0.20849703252315521 
		0.18856906890869141 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0.8589358925819397 0.9780229926109314 
		0.98205989599227905 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA779";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA780";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 3.1805546814635168e-015 2 0 5 0 7 0 11 
		0 22 0 27 0 31 0 33 0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA781";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -7.9513867036587899e-016 2 0 5 0 7 0 
		11 0 22 0 27 0 31 0 33 0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA782";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 25.675870473757751 2 -3.1885912119463087 
		5 25.675870473757751 7 25.675870473757751 11 25.675870473757751 17 -2.4108453047351244 
		22 -34.837747800671799 25 -11.120788631338607 27 25.675870473757751 31 31.685914089189179 
		33 31.685914089189179 36 31.685914089189179 39 31.685914089189179 41 31.685914089189179 
		43 31.685914089189179;
	setAttr -s 15 ".kit[0:14]"  3 10 1 10 10 10 10 10 
		10 10 1 10 1 10 3;
	setAttr -s 15 ".kot[0:14]"  3 10 1 10 10 10 10 10 
		10 10 1 10 1 10 3;
	setAttr -s 15 ".kix[2:14]"  1 1 1 0.3279668390750885 0.86875319480895996 
		0.15587517619132996 0.25859025120735168 1 1 1 1 1 1;
	setAttr -s 15 ".kiy[2:14]"  0 0 0 -0.94468927383422852 -0.49524533748626709 
		0.98777675628662109 0.96598714590072632 0 0 0 0 0 0;
	setAttr -s 15 ".kox[2:14]"  1 1 1 0.3279668390750885 0.86875319480895996 
		0.15587517619132996 0.25859025120735168 1 1 1 1 1 1;
	setAttr -s 15 ".koy[2:14]"  0 0 0 -0.94468927383422852 -0.49524533748626709 
		0.98777675628662109 0.96598714590072632 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA783";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 -3.0739741698828946 2 15.873220738915142 
		5 -3.0739741698828946 7 -3.0739741698828946 11 -3.0739741698828946 17 -9.1940528802750681 
		22 19.302878401122847 25 -3.0273571384041196 27 -3.0739741698828946 31 16.46333359402475 
		33 16.46333359402475 36 16.46333359402475 39 16.46333359402475 41 16.46333359402475 
		43 16.46333359402475;
	setAttr -s 15 ".kit[0:14]"  3 10 1 10 10 10 10 10 
		10 10 1 10 1 10 3;
	setAttr -s 15 ".kot[0:14]"  3 10 1 10 10 10 10 10 
		10 10 1 10 1 10 3;
	setAttr -s 15 ".kix[2:14]"  1 1 1 0.68446385860443115 0.9273180365562439 
		1 1 1 1 1 1 1 1;
	setAttr -s 15 ".kiy[2:14]"  0 0 0 0.72904688119888306 0.37427419424057007 
		0 0 0 0 0 0 0 0;
	setAttr -s 15 ".kox[2:14]"  1 1 1 0.68446385860443115 0.9273180365562439 
		1 1 1 1 1 1 1 1;
	setAttr -s 15 ".koy[2:14]"  0 0 0 0.72904688119888306 0.37427419424057007 
		0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU240";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  2 3 5 3 11 3 30 3 32 3 33 3 36 3 39 3 41 
		3 43 3;
	setAttr -s 10 ".kit[0:9]"  10 1 1 10 3 3 3 3 
		10 3;
	setAttr -s 10 ".kot[0:9]"  10 1 1 10 3 3 3 3 
		10 3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU241";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  2 0 5 0 11 0 30 0 32 0 33 0 36 0 39 0 41 
		0 43 0;
	setAttr -s 10 ".kit[0:9]"  10 1 1 10 3 3 3 3 
		10 3;
	setAttr -s 10 ".kot[0:9]"  10 1 1 10 3 3 3 3 
		10 3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU242";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  2 1 5 1 11 1 30 1 32 1 33 1 36 1 39 1 41 
		1 43 1;
	setAttr -s 10 ".kit[0:9]"  9 1 1 9 3 3 3 3 
		9 3;
	setAttr -s 10 ".kot[0:9]"  5 5 5 5 3 3 3 3 
		5 3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU243";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  2 0 5 0 11 0 30 0 32 0 33 0 36 0 39 0 41 
		0 43 0;
	setAttr -s 10 ".kit[0:9]"  10 1 1 10 3 3 3 3 
		10 3;
	setAttr -s 10 ".kot[0:9]"  10 1 1 10 3 3 3 3 
		10 3;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA784";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 93.144161708979723 2 99.1904564086813 
		5 92.928428806906425 11 91.532437604391433 17 154.93380595359207 20 43.589371499690259 
		25 43.498256072980972 27 24.859330700886197 30 -88.158571168762734 32 -13.800623522465497 
		33 -13.800623522465497 36 -13.800623522465497 39 -13.800623522465497 41 -13.800623522465497 
		43 -13.800623522465497;
	setAttr -s 15 ".kit[0:14]"  9 10 1 1 10 10 10 10 
		10 3 3 3 3 10 3;
	setAttr -s 15 ".kot[0:14]"  9 10 1 1 10 10 10 10 
		10 3 3 3 3 10 3;
	setAttr -s 15 ".kix[2:14]"  1 1 0.33748909831047058 1 1 0.072341687977313995 
		0.23980042338371277 1 1 1 1 1 1;
	setAttr -s 15 ".kiy[2:14]"  0 0 -0.94132941961288452 0 0 -0.99737989902496338 
		-0.97082215547561646 0 0 0 0 0 0;
	setAttr -s 15 ".kox[2:14]"  1 1 0.33748909831047058 1 1 0.072341687977313995 
		0.23980042338371277 1 1 1 1 1 1;
	setAttr -s 15 ".koy[2:14]"  0 0 -0.94132941961288452 0 0 -0.99737989902496338 
		-0.97082215547561646 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA785";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 95.049826002206416 2 101.8944955677039 
		5 98.320530379975807 11 98.836731683996561 17 144.53923905170646 20 105.32192721328931 
		25 149.77711807264322 27 194.4916239683476 30 306.97931370310499 32 279.82541323612065 
		33 279.82541323612065 36 279.82541323612065 39 279.82541323612065 41 279.82541323612065 
		43 279.82541323612065;
	setAttr -s 15 ".kit[0:14]"  9 10 1 1 10 10 10 10 
		10 3 3 3 3 10 3;
	setAttr -s 15 ".kot[0:14]"  9 10 1 1 10 10 10 10 
		10 3 3 3 3 10 3;
	setAttr -s 15 ".kix[2:14]"  1 1 0.93562185764312744 0.94595712423324585 
		0.14827057719230652 0.06063355877995491 0.11121109873056412 1 1 1 1 1 1;
	setAttr -s 15 ".kiy[2:14]"  0 0 0.35300394892692566 0.32429152727127075 
		0.98894685506820679 0.99816012382507324 0.99379682540893555 0 0 0 0 0 0;
	setAttr -s 15 ".kox[2:14]"  1 1 0.93562185764312744 0.94595712423324585 
		0.14827057719230652 0.06063355877995491 0.11121109873056412 1 1 1 1 1 1;
	setAttr -s 15 ".koy[2:14]"  0 0 0.35300394892692566 0.32429152727127075 
		0.98894685506820679 0.99816012382507324 0.99379682540893555 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA786";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 1.1812364035166698 2 -0.9329817939205024 
		5 -2.05034770782258 11 -6.2749694509305352 17 45.678831250647754 20 64.846101203807265 
		25 -30.460687863351545 27 -10.311488800238164 30 -82.369613543926491 32 -59.475732560213167 
		33 -59.475732560213167 36 -59.475732560213167 39 -59.475732560213167 41 -59.475732560213167 
		43 -59.475732560213167;
	setAttr -s 15 ".kit[0:14]"  9 10 1 1 10 10 10 10 
		10 3 3 3 3 10 3;
	setAttr -s 15 ".kot[0:14]"  9 10 1 1 10 10 10 10 
		10 3 3 3 3 10 3;
	setAttr -s 15 ".kix[2:14]"  1 0.57812178134918213 0.23491920530796051 
		0.19674718379974365 0.17513065040111542 0.18092653155326843 0.19066931307315826 1 
		1 1 1 1 1;
	setAttr -s 15 ".kiy[2:14]"  0 -0.81595045328140259 0.97201496362686157 
		-0.9804542064666748 -0.98454517126083374 -0.98349660634994507 -0.98165434598922729 
		0 0 0 0 0 0;
	setAttr -s 15 ".kox[2:14]"  1 0.57812178134918213 0.23491920530796051 
		0.19674718379974365 0.17513065040111542 0.18092653155326843 0.19066931307315826 1 
		1 1 1 1 1;
	setAttr -s 15 ".koy[2:14]"  0 -0.81595045328140259 0.97201496362686157 
		-0.9804542064666748 -0.98454517126083374 -0.98349660634994507 -0.98165434598922729 
		0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL250";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 -0.23689498628395578 2 -0.28038599853325119 
		5 -0.31686353866138783 11 -0.37395569253884797 17 0.00088799003576089594 20 0.3316808833009085 
		23 -0.022768734563886721 27 -1.4297203049239935 30 -2.7364417001078736 32 -3.0356841150924518 
		35 -3.0754653960166483 38 -3.0754653960166483 41 -3.0754653960166483 43 -3.0754653960166483;
	setAttr -s 14 ".kit[0:13]"  9 10 1 1 10 10 10 10 
		10 3 3 3 3 3;
	setAttr -s 14 ".kot[0:13]"  9 10 1 1 10 10 10 10 
		10 3 3 3 3 3;
	setAttr -s 14 ".kix[2:13]"  1 1 0.39125606417655945 0.99307703971862793 
		0.13132302463054657 0.085668228566646576 0.10322549194097519 1 1 1 1 1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0.92028188705444336 -0.11746475100517273 
		-0.99133962392807007 -0.99632370471954346 -0.99465793371200562 0 0 0 0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 0.39125606417655945 0.99307703971862793 
		0.13132302463054657 0.085668228566646576 0.10322549194097519 1 1 1 1 1;
	setAttr -s 14 ".koy[2:13]"  0 0 0.92028188705444336 -0.11746475100517273 
		-0.99133962392807007 -0.99632370471954346 -0.99465793371200562 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL251";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 -0.30633990936382105 2 -0.30680302469217013 
		5 -0.25242871820302193 11 -0.20268064803757252 17 -0.28230724457612072 20 -0.79109417391852588 
		23 -1.8963746734888001 25 -2.0894601014292626 27 -2.2080132156451313 30 -2.7616260113251476 
		32 -2.8423819066976348 33 -2.8423819066976348 36 -2.8423819066976348 39 -2.8423819066976348 
		41 -2.8423819066976348 43 -2.8423819066976348;
	setAttr -s 16 ".kit[0:15]"  9 10 1 1 10 10 10 10 
		10 10 3 3 3 3 10 3;
	setAttr -s 16 ".kot[0:15]"  9 10 1 1 10 10 10 10 
		10 10 3 3 3 3 10 3;
	setAttr -s 16 ".kix[2:15]"  1 1 0.45421686768531799 0.12297012656927109 
		0.12732173502445221 0.39335581660270691 0.24066677689552307 0.25410491228103638 1 
		1 1 1 1 1;
	setAttr -s 16 ".kiy[2:15]"  0 0 -0.89089113473892212 -0.99241042137145996 
		-0.99186146259307861 -0.91938626766204834 -0.97060781717300415 -0.96717667579650879 
		0 0 0 0 0 0;
	setAttr -s 16 ".kox[2:15]"  1 1 0.45421686768531799 0.12297012656927109 
		0.12732173502445221 0.39335581660270691 0.24066677689552307 0.25410491228103638 1 
		1 1 1 1 1;
	setAttr -s 16 ".koy[2:15]"  0 0 -0.89089113473892212 -0.99241042137145996 
		-0.99186146259307861 -0.91938626766204834 -0.97060781717300415 -0.96717667579650879 
		0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL252";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 0.52899036848843184 2 0.49367865309827513 
		5 0.47580506764715458 11 0.30816897396934012 17 0.001879322039559875 20 0.13368097820557828 
		23 0.94526335772394421 25 1.28141966106157 27 1.2437698578791228 30 0.63505160952038187 
		32 0.36128601150367978 33 0.36128601150367978 36 0.36128601150367978 39 0.36128601150367978 
		41 0.36128601150367978 43 0.36128601150367978;
	setAttr -s 16 ".kit[0:15]"  9 10 1 1 10 10 10 10 
		10 10 3 3 3 3 10 3;
	setAttr -s 16 ".kot[0:15]"  9 10 1 1 10 10 10 10 
		10 10 3 3 3 3 10 3;
	setAttr -s 16 ".kix[2:15]"  0.94643145799636841 0.89834105968475342 
		0.86442023515701294 0.20739328861236572 0.14370580017566681 1 1 0.18558028340339661 
		1 1 1 1 1 1;
	setAttr -s 16 ".kiy[2:15]"  -0.32290467619895935 -0.43929886817932129 
		-0.5027698278427124 0.97825759649276733 0.98962050676345825 0 0 -0.98262912034988403 
		0 0 0 0 0 0;
	setAttr -s 16 ".kox[2:15]"  0.94643145799636841 0.89834105968475342 
		0.86442023515701294 0.20739328861236572 0.14370580017566681 1 1 0.18558028340339661 
		1 1 1 1 1 1;
	setAttr -s 16 ".koy[2:15]"  -0.32290467619895935 -0.43929886817932129 
		-0.5027698278427124 0.97825759649276733 0.98962050676345825 0 0 -0.98262912034988403 
		0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU244";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 24 0 27 0 31 0 33 0 36 0 39 0 
		41 0 43 0;
	setAttr -s 10 ".kit[7:9]"  1 9 3;
	setAttr -s 10 ".kot[2:9]"  5 5 5 5 5 5 5 3;
	setAttr -s 10 ".kix[7:9]"  1 1 1;
	setAttr -s 10 ".kiy[7:9]"  0 0 0;
createNode animCurveTA -n "animCurveTA787";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 -24.884454396993167 2 -32.044687089063324 
		5 -20.590441845544511 11 -9.8246132853700114 17 -1.9496652338758678 21 -4.3902540840472852 
		24 17.875110546345454 27 73.17138398648342 31 73.17138398648342 33 73.17138398648342 
		36 73.17138398648342 39 73.17138398648342 41 73.17138398648342 43 73.17138398648342;
	setAttr -s 14 ".kit[0:13]"  3 3 10 9 9 9 10 10 
		10 10 10 1 10 3;
	setAttr -s 14 ".kot[0:13]"  3 3 10 9 9 9 10 10 
		10 10 10 1 10 3;
	setAttr -s 14 ".kix[11:13]"  1 1 1;
	setAttr -s 14 ".kiy[11:13]"  0 0 0;
	setAttr -s 14 ".kox[11:13]"  1 1 1;
	setAttr -s 14 ".koy[11:13]"  0 0 0;
createNode animCurveTA -n "animCurveTA788";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 -43.339475474578435 2 -15.657808992123773 
		5 -15.202078582860109 11 -31.713756694615164 17 -60.975198351481247 21 -46.758747123757644 
		24 -66.788693616579536 27 -38.349760112489754 31 -38.349760112489754 33 -38.349760112489754 
		36 -38.349760112489754 39 -38.349760112489754 41 -38.349760112489754 43 -38.349760112489754;
	setAttr -s 14 ".kit[0:13]"  1 3 10 9 9 9 10 10 
		10 10 10 1 10 3;
	setAttr -s 14 ".kot[0:13]"  1 3 10 9 9 9 10 10 
		10 10 10 1 10 3;
	setAttr -s 14 ".kix[0:13]"  0.97562801837921143 1 1 0.44770970940589905 
		0.78553938865661621 0.91704803705215454 0.80621683597564697 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[0:13]"  -0.21943102777004242 0 0 -0.89417892694473267 
		-0.61881172657012939 -0.39877685904502869 0.59162014722824097 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[0:13]"  0.97562801837921143 1 1 0.44770970940589905 
		0.78553938865661621 0.91704803705215454 0.80621683597564697 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[0:13]"  -0.21943105757236481 0 0 -0.89417892694473267 
		-0.61881172657012939 -0.39877685904502869 0.59162014722824097 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA789";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 11.606559612787883 2 25.033296363587215 
		5 -15.121147894455008 11 -4.8394118747832673 17 -47.280840200318387 21 -64.511320476316101 
		24 -83.75881406530759 27 -148.70937524948479 31 -148.70937524948479 33 -148.70937524948479 
		36 -148.70937524948479 39 -148.70937524948479 41 -148.70937524948479 43 -148.70937524948479;
	setAttr -s 14 ".kit[0:13]"  3 3 10 9 9 9 10 10 
		10 10 10 1 10 3;
	setAttr -s 14 ".kot[0:13]"  3 3 10 9 9 9 10 10 
		10 10 10 1 10 3;
	setAttr -s 14 ".kix[11:13]"  1 1 1;
	setAttr -s 14 ".kiy[11:13]"  0 0 0;
	setAttr -s 14 ".kox[11:13]"  1 1 1;
	setAttr -s 14 ".koy[11:13]"  0 0 0;
createNode animCurveTU -n "animCurveTU245";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 7 0 11 0 24 0 27 0 31 0 33 0 36 0 39 
		0 41 0 43 0;
	setAttr -s 11 ".kit[0:10]"  3 9 9 9 9 9 9 9 
		1 9 3;
	setAttr -s 11 ".kot[0:10]"  3 5 5 5 5 5 5 5 
		5 5 3;
	setAttr -s 11 ".kix[8:10]"  1 1 1;
	setAttr -s 11 ".kiy[8:10]"  0 0 0;
createNode animCurveTU -n "animCurveTU246";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 7 0 11 0 24 0 27 0 31 0 33 0 36 0 39 
		0 41 0 43 0;
	setAttr -s 11 ".kit[0:10]"  3 9 9 9 9 9 9 9 
		1 9 3;
	setAttr -s 11 ".kot[0:10]"  3 5 5 5 5 5 5 5 
		5 5 3;
	setAttr -s 11 ".kix[8:10]"  1 1 1;
	setAttr -s 11 ".kiy[8:10]"  0 0 0;
createNode animCurveTU -n "animCurveTU247";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 7 0 11 0 24 0 27 1 31 1 33 1 36 1 39 
		1 41 1 43 1;
	setAttr -s 11 ".kit[0:10]"  9 10 9 10 10 10 3 3 
		1 10 3;
	setAttr -s 11 ".kot[0:10]"  9 10 9 10 10 10 3 3 
		1 10 3;
	setAttr -s 11 ".kix[8:10]"  1 1 1;
	setAttr -s 11 ".kiy[8:10]"  0 0 0;
	setAttr -s 11 ".kox[8:10]"  1 1 1;
	setAttr -s 11 ".koy[8:10]"  0 0 0;
createNode animCurveTU -n "animCurveTU248";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 7 0 11 0 24 0 27 0 31 0 33 0 36 0 39 
		0 41 0 43 0;
	setAttr -s 11 ".kit[0:10]"  3 9 9 9 9 9 9 9 
		1 9 3;
	setAttr -s 11 ".kot[0:10]"  3 5 5 5 5 5 5 5 
		5 5 3;
	setAttr -s 11 ".kix[8:10]"  1 1 1;
	setAttr -s 11 ".kiy[8:10]"  0 0 0;
createNode animCurveTA -n "animCurveTA790";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 3.9531091186723013 4 37.000349835270072 
		7 3.9531091186723013 11 -4.0669128830054655 18 -4.7938553777995239 22 -37.442700264103479 
		24 -50.565933311627958 27 3.9531091186723013 31 3.9531091186723013 33 3.9531091186723013 
		36 3.9531091186723013 39 3.9531091186723013 41 3.9531091186723013 43 3.9531091186723013;
	setAttr -s 14 ".kit[0:13]"  3 10 10 10 10 10 10 10 
		10 10 10 1 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 10 10 10 10 10 10 
		10 10 10 1 10 3;
	setAttr -s 14 ".kix[11:13]"  1 1 1;
	setAttr -s 14 ".kiy[11:13]"  0 0 0;
	setAttr -s 14 ".kox[11:13]"  1 1 1;
	setAttr -s 14 ".koy[11:13]"  0 0 0;
createNode animCurveTA -n "animCurveTA791";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0.62018686761647346 4 11.300842266847898 
		7 0.62018686761647346 11 -13.562369277897043 18 -16.282273928852419 22 7.2346039002032017 
		24 -3.1908986165069941 27 0.62018686761647346 31 0.62018686761647346 33 0.62018686761647346 
		36 0.62018686761647346 39 0.62018686761647346 41 0.62018686761647346 43 0.62018686761647346;
	setAttr -s 14 ".kit[0:13]"  3 10 10 10 10 10 10 10 
		10 10 10 1 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 10 10 10 10 10 10 
		10 10 10 1 10 3;
	setAttr -s 14 ".kix[11:13]"  1 1 1;
	setAttr -s 14 ".kiy[11:13]"  0 0 0;
	setAttr -s 14 ".kox[11:13]"  1 1 1;
	setAttr -s 14 ".koy[11:13]"  0 0 0;
createNode animCurveTA -n "animCurveTA792";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 5.3292188742882338 4 -11.617702590383955 
		7 5.3292188742882338 11 -9.289366570928598 18 25.289286528790395 22 28.955699481699106 
		24 38.663384385804157 27 5.3292188742882338 31 5.3292188742882338 33 5.3292188742882338 
		36 5.3292188742882338 39 5.3292188742882338 41 5.3292188742882338 43 5.3292188742882338;
	setAttr -s 14 ".kit[0:13]"  3 10 10 10 10 10 10 10 
		10 10 10 1 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 10 10 10 10 10 10 
		10 10 10 1 10 3;
	setAttr -s 14 ".kix[11:13]"  1 1 1;
	setAttr -s 14 ".kiy[11:13]"  0 0 0;
	setAttr -s 14 ".kox[11:13]"  1 1 1;
	setAttr -s 14 ".koy[11:13]"  0 0 0;
createNode animCurveTU -n "animCurveTU249";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 2 0 5 0 7 0 11 0 22 0 25 0 27 0 31 
		0 33 0 36 0 39 0 41 0 43 0;
	setAttr -s 14 ".kit[0:13]"  3 10 1 10 10 10 10 10 
		1 3 3 1 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 1 10 10 10 10 10 
		1 3 3 1 10 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU250";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 2 0 5 0 7 0 11 0 22 0 25 0 27 0 31 
		0 33 0 36 0 39 0 41 0 43 0;
	setAttr -s 14 ".kit[0:13]"  3 10 1 10 10 10 10 10 
		1 3 3 1 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 1 10 10 10 10 10 
		1 3 3 1 10 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL253";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 24 0 27 -2.166207553745835 
		29 -2.3149335789664987 33 -2.3149335789664987 35 -2.1063676859306129 38 -2.1063676859306129 
		41 -2.1063676859306129 43 -2.1063676859306129;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		1 3 3 1 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		1 3 3 1 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 0.071810416877269745 1 1 1 1 1 
		1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 -0.99741828441619873 0 0 0 0 0 
		0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 0.071810416877269745 1 1 1 1 1 
		1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 -0.99741828441619873 0 0 0 0 0 
		0;
createNode animCurveTL -n "animCurveTL254";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 2 0 5 0 7 0 11 0 22 0 25 1.1869685444721134 
		27 1.7722132318316031 31 1.7722132318316031 33 1.8907174932527058 36 1.8907174932527058 
		39 1.8907174932527058 41 1.8907174932527058 43 1.8907174932527058;
	setAttr -s 14 ".kit[0:13]"  3 10 1 10 10 10 10 10 
		1 3 3 1 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 1 10 10 10 10 10 
		1 3 3 1 10 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 1 0.09363120049238205 1 1 1 1 1 1 
		1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0 0.99560695886611938 0 0 0 0 0 0 
		0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 1 0.09363120049238205 1 1 1 1 1 1 
		1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0 0.99560695886611938 0 0 0 0 0 0 
		0;
createNode animCurveTL -n "animCurveTL255";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 -1.1102230246251565e-016 2 0 5 0 7 0 
		11 0 22 0 25 -1.1595109497168556 27 -1.636311299873237 31 -1.636311299873237 33 -1.6359487974722959 
		36 -1.6359487974722959 39 -1.6359487974722959 41 -1.6359487974722959 43 -1.6359487974722959;
	setAttr -s 14 ".kit[0:13]"  3 10 1 10 10 10 10 10 
		1 3 3 1 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 1 10 10 10 10 10 
		1 3 3 1 10 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 1 0.10133082419633865 1 1 1 1 1 1 
		1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0 -0.99485284090042114 0 0 0 0 0 
		0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 1 0.10133082419633865 1 1 1 1 1 1 
		1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0 -0.99485284090042114 0 0 0 0 0 
		0 0;
createNode animCurveTA -n "animCurveTA793";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -44.757110789561033 4 -59.82871655477048 
		7 -44.757110789561033 11 -52.487828463721641 17 -47.896524704713286 24 -41.284834281882617 
		27 -44.757110789561033 31 -44.757110789561033 33 -44.757110789561033 36 -44.757110789561033 
		39 -44.757110789561033 41 -44.757110789561033 43 -44.757110789561033;
	setAttr -s 13 ".kit[0:12]"  1 10 10 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  1 10 10 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[0:12]"  0.82668501138687134 1 0.87654989957809448 
		0.98675751686096191 0.91150450706481934 0.98675751686096191 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[0:12]"  -0.56266492605209351 0 0.48131102323532104 
		-0.16220255196094513 0.41129004955291748 0.16220255196094513 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[0:12]"  0.82668513059616089 1 0.87654989957809448 
		0.98675751686096191 0.91150450706481934 0.98675751686096191 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[0:12]"  -0.56266486644744873 0 0.48131102323532104 
		-0.16220255196094513 0.41129004955291748 0.16220255196094513 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA794";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  4 0 15 0;
createNode animCurveTA -n "animCurveTA795";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  4 0 15 0;
createNode animCurveTA -n "animCurveTA796";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -27.604588158357807 2 31.866409929661817 
		7 15.080932515116421 15 6.4313184466227957 24 4.2276700947590289 27 -5.4748052678266914 
		31 -39.480347712369849 33 -53.121264718818239 36 -53.121264718818239 39 -53.121264718818239 
		41 -53.121264718818239 43 -53.121264718818239;
	setAttr -s 12 ".kit[0:11]"  9 10 10 10 10 10 3 3 
		3 1 10 3;
	setAttr -s 12 ".kot[0:11]"  9 10 10 10 10 10 3 3 
		3 1 10 3;
	setAttr -s 12 ".kix[9:11]"  1 1 1;
	setAttr -s 12 ".kiy[9:11]"  0 0 0;
	setAttr -s 12 ".kox[9:11]"  1 1 1;
	setAttr -s 12 ".koy[9:11]"  0 0 0;
createNode animCurveTA -n "animCurveTA797";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0.70641431476594085 2 -21.30007846824634 
		7 -28.934546156065529 15 -18.341283977700432 24 -13.659457720796466 27 6.7108396447444667 
		31 -2.0082208427924679 33 12.141532718268085 36 12.141532718268085 39 12.141532718268085 
		41 12.141532718268085 43 12.141532718268085;
	setAttr -s 12 ".kit[0:11]"  1 10 10 10 10 10 3 3 
		3 1 10 3;
	setAttr -s 12 ".kot[0:11]"  1 10 10 10 10 10 3 3 
		3 1 10 3;
	setAttr -s 12 ".kix[0:11]"  0.98865425586700439 0.41114667057991028 
		0.9929739236831665 0.90485936403274536 0.67498588562011719 0.75387883186340332 1 
		1 1 1 1 1;
	setAttr -s 12 ".kiy[0:11]"  0.15020918846130371 -0.91156917810440063 
		0.11833355575799942 0.42571064829826355 0.73783057928085327 0.6570134162902832 0 
		0 0 0 0 0;
	setAttr -s 12 ".kox[0:11]"  0.98865425586700439 0.41114667057991028 
		0.9929739236831665 0.90485936403274536 0.67498588562011719 0.75387883186340332 1 
		1 1 1 1 1;
	setAttr -s 12 ".koy[0:11]"  0.15020912885665894 -0.91156917810440063 
		0.11833355575799942 0.42571064829826355 0.73783057928085327 0.6570134162902832 0 
		0 0 0 0 0;
createNode animCurveTU -n "animCurveTU251";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 2 0 5 0 7 0 11 0 22 0 25 0 33 0 36 
		0 39 0 41 0 43 0;
	setAttr -s 12 ".kit[0:11]"  3 9 1 9 9 1 9 1 
		3 1 9 3;
	setAttr -s 12 ".kot[0:11]"  3 5 5 5 5 5 5 1 
		3 1 5 3;
	setAttr -s 12 ".kix[2:11]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[2:11]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[7:11]"  1 1 1 0 1;
	setAttr -s 12 ".koy[7:11]"  0 0 0 0 0;
createNode animCurveTU -n "animCurveTU252";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 3 2 3 5 3 7 3 11 3 22 3 25 3 33 3 36 
		3 39 3 41 3 43 3;
	setAttr -s 12 ".kit[0:11]"  3 10 1 10 10 1 10 1 
		3 1 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 1 10 10 1 10 1 
		3 1 10 3;
	setAttr -s 12 ".kix[2:11]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[2:11]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[2:11]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[2:11]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU253";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 2 0 5 0 7 0 11 0 22 0 25 0 33 0 36 
		0 39 0 41 0 43 0;
	setAttr -s 12 ".kit[0:11]"  3 10 1 10 10 1 10 1 
		3 1 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 1 10 10 1 10 1 
		3 1 10 3;
	setAttr -s 12 ".kix[2:11]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[2:11]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[2:11]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[2:11]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU254";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 1 2 1 5 1 7 1 11 1 22 1 25 1 33 1 36 
		1 39 1 41 1 43 1;
	setAttr -s 12 ".kit[0:11]"  3 9 1 9 9 1 9 1 
		3 1 9 3;
	setAttr -s 12 ".kot[0:11]"  3 5 5 5 5 5 5 1 
		3 1 5 3;
	setAttr -s 12 ".kix[2:11]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[2:11]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[7:11]"  1 1 1 0 1;
	setAttr -s 12 ".koy[7:11]"  0 0 0 0 0;
createNode animCurveTU -n "animCurveTU255";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 2 0 5 0 7 0 11 0 22 0 25 0 33 0 36 
		0 39 0 41 0 43 0;
	setAttr -s 12 ".kit[0:11]"  3 10 1 10 10 1 10 1 
		3 1 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 1 10 10 1 10 1 
		3 1 10 3;
	setAttr -s 12 ".kix[2:11]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[2:11]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[2:11]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[2:11]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA798";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 2 0 5 0 7 0 11 0 22 8.3073959197922598 
		25 8.3073959197922598 33 286.64579121031312 36 286.64579121031312 39 286.64579121031312 
		41 286.64579121031312 43 286.64579121031312;
	setAttr -s 12 ".kit[0:11]"  3 10 1 10 10 1 10 1 
		3 1 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 1 10 10 1 10 1 
		3 1 10 3;
	setAttr -s 12 ".kix[2:11]"  1 1 1 0.56775581836700439 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[2:11]"  0 0 0 0.82319700717926025 0 0 0 0 0 0;
	setAttr -s 12 ".kox[2:11]"  1 1 1 0.56775581836700439 1 1 1 1 1 1;
	setAttr -s 12 ".koy[2:11]"  0 0 0 0.82319700717926025 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA799";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 2 0 5 0 7 0 11 0 22 -143.65845118050362 
		25 -143.65845118050362 33 -399.40417802150165 36 -399.40417802150165 39 -399.40417802150165 
		41 -399.40417802150165 43 -399.40417802150165;
	setAttr -s 12 ".kit[0:11]"  3 10 1 10 10 1 10 1 
		3 1 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 1 10 10 1 10 1 
		3 1 10 3;
	setAttr -s 12 ".kix[2:11]"  1 1 1 0.039851658046245575 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[2:11]"  0 0 0 -0.99920558929443359 0 0 0 0 0 0;
	setAttr -s 12 ".kox[2:11]"  1 1 1 0.039851661771535873 1 1 1 1 1 1;
	setAttr -s 12 ".koy[2:11]"  0 0 0 -0.99920564889907837 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA800";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 2 0 5 0 7 0 11 0 22 -60.364845688789011 
		25 -60.364845688789011 33 -48.219300431155055 36 -48.219300431155055 39 -48.219300431155055 
		41 -48.219300431155055 43 -48.219300431155055;
	setAttr -s 12 ".kit[0:11]"  3 10 1 10 10 1 10 1 
		3 1 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 1 10 10 1 10 1 
		3 1 10 3;
	setAttr -s 12 ".kix[2:11]"  1 1 1 0.094491153955459595 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[2:11]"  0 0 0 -0.99552571773529053 0 0 0 0 0 0;
	setAttr -s 12 ".kox[2:11]"  1 1 1 0.094491153955459595 1 1 1 1 1 1;
	setAttr -s 12 ".koy[2:11]"  0 0 0 -0.99552571773529053 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL256";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 2.2204460492503131e-016 2 0 5 0 7 0 11 
		0 24 3.070971996313216 27 2.8049916989864099 35 3.103145745957256 38 3.103145745957256 
		41 3.103145745957256 43 3.103145745957256;
	setAttr -s 11 ".kit[0:10]"  3 10 1 10 10 1 10 1 
		3 1 3;
	setAttr -s 11 ".kot[0:10]"  3 10 1 10 10 1 10 1 
		3 1 3;
	setAttr -s 11 ".kix[2:10]"  1 1 1 0.03254573792219162 0.99617236852645874 
		1 1 1 1;
	setAttr -s 11 ".kiy[2:10]"  0 0 0 0.99947023391723633 0.087410740554332733 
		0 0 0 0;
	setAttr -s 11 ".kox[2:10]"  1 1 1 0.03254573792219162 0.99617236852645874 
		1 1 1 1;
	setAttr -s 11 ".koy[2:10]"  0 0 0 0.99947023391723633 0.087410740554332733 
		0 0 0 0;
createNode animCurveTL -n "animCurveTL257";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 2 0 5 0 7 0 11 0 22 2.0410883867037293 
		25 2.2299042949666505 33 2.1515825797171204 36 2.1515825797171204 39 2.1515825797171204 
		41 2.1515825797171204 43 2.1515825797171204;
	setAttr -s 12 ".kit[0:11]"  3 10 1 10 10 1 10 1 
		3 1 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 1 10 10 1 10 1 
		3 1 10 3;
	setAttr -s 12 ".kix[2:11]"  1 1 1 0.048934787511825562 0.95747029781341553 
		1 1 1 1 1;
	setAttr -s 12 ".kiy[2:11]"  0 0 0 0.9988020658493042 0.28853157162666321 
		0 0 0 0 0;
	setAttr -s 12 ".kox[2:11]"  1 1 1 0.048934780061244965 0.95747029781341553 
		1 1 1 1 1;
	setAttr -s 12 ".koy[2:11]"  0 0 0 0.99880194664001465 0.28853157162666321 
		0 0 0 0 0;
createNode animCurveTL -n "animCurveTL258";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 4.4408920985006262e-016 2 0 5 0 7 0 11 
		0 22 0.1481641126500626 25 0.16059862853271134 33 0.061443386383766785 36 0.061443386383766785 
		39 0.061443386383766785 41 0.061443386383766785 43 0.061443386383766785;
	setAttr -s 12 ".kit[0:11]"  3 10 1 10 10 1 10 1 
		3 1 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 1 10 10 1 10 1 
		3 1 10 3;
	setAttr -s 12 ".kix[2:11]"  1 1 1 0.55943155288696289 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[2:11]"  0 0 0 0.8288765549659729 0 0 0 0 0 0;
	setAttr -s 12 ".kox[2:11]"  1 1 1 0.55943155288696289 1 1 1 1 1 1;
	setAttr -s 12 ".koy[2:11]"  0 0 0 0.8288765549659729 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU256";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 1 2 1 5 1 7 1 18 1 24 1 27 1 31 1 36 
		1 39 1 41 1 43 1;
	setAttr -s 12 ".kit[0:11]"  9 10 1 10 10 10 10 1 
		3 1 10 3;
	setAttr -s 12 ".kot[0:11]"  9 10 1 10 10 10 10 1 
		3 1 10 3;
	setAttr -s 12 ".kix[2:11]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[2:11]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[2:11]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[2:11]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA801";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 1.1288109940741509 2 8.4849204715091222 
		5 10.025013420630829 7 8.3120774415698211 13 11.04306418224229 18 16.098732749638547 
		24 27.277603047790127 27 45.248260696945131 29 29.5197762254646 31 22.469634786851902 
		36 22.528056651186247 39 22.528056651186247 41 22.510493311084293 43 22.528056651186247;
	setAttr -s 14 ".kit[0:13]"  3 10 1 10 10 10 10 10 
		2 1 3 1 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 1 10 10 10 10 10 
		2 1 3 1 10 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 0.79127156734466553 0.50794082880020142 
		0.97352433204650879 0.23599404096603394 1 1 1 1 1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0.61146479845046997 0.86139196157455444 
		0.22858339548110962 -0.97175449132919312 0 0 0 0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 0.79127156734466553 0.50794082880020142 
		0.97352433204650879 0.47636911273002625 1 1 1 1 1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0.61146479845046997 0.86139196157455444 
		0.22858339548110962 -0.8792453408241272 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA802";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 4.8219581414201906 2 2.1515473806517713 
		5 7.3871461837345915 7 4.9657859530847963 13 10.029677288281388 18 16.632562101942796 
		24 0.24398697774555833 27 8.1419581267668395 29 -0.29644875165061652 31 -0.44304005090975845 
		36 -2.5418312681922308 39 -2.5418312681922308 41 -1.9144849561529 43 -2.5418312681922308;
	setAttr -s 14 ".kit[0:13]"  3 10 1 10 10 10 10 10 
		2 1 3 1 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 1 10 10 10 10 10 
		2 1 3 1 10 3;
	setAttr -s 14 ".kix[2:13]"  0.99059087038040161 1 0.87423825263977051 
		0.90648472309112549 0.89658164978027344 0.99840241670608521 0.41237792372703552 1 
		1 1 1 1;
	setAttr -s 14 ".kiy[2:13]"  0.13685663044452667 0 0.48549705743789673 
		-0.4222385585308075 -0.44287851452827454 -0.056503899395465851 -0.91101288795471191 
		0 0 0 0 0;
	setAttr -s 14 ".kox[2:13]"  0.99059087038040161 1 0.87423825263977051 
		0.90648472309112549 0.89658164978027344 0.99840241670608521 0.99926435947418213 1 
		1 1 1 1;
	setAttr -s 14 ".koy[2:13]"  0.13685663044452667 0 0.48549705743789673 
		-0.4222385585308075 -0.44287851452827454 -0.056503899395465851 -0.038349281996488571 
		0 0 0 0 0;
createNode animCurveTA -n "animCurveTA803";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 28.08558650754679 2 21.308061725836495 
		5 26.04201242981334 7 18.031102022595405 13 8.667762452696552 18 6.4655398543822615 
		24 21.682761007007038 27 11.46565209561324 29 -4.2312776835601786 31 -9.5502883753324834 
		36 -9.576283464829018 39 -9.576283464829018 41 -9.5687349231777734 43 -9.576283464829018;
	setAttr -s 14 ".kit[0:13]"  3 10 1 10 10 10 10 10 
		2 1 3 1 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 1 10 10 10 10 10 
		2 1 3 1 10 3;
	setAttr -s 14 ".kix[2:13]"  0.75185447931289673 0.66037291288375854 
		1 1 0.96019905805587769 0.34576967358589172 0.2364419549703598 1 1 1 1 1;
	setAttr -s 14 ".kiy[2:13]"  -0.65932905673980713 -0.750937819480896 
		0 0 0.27931687235832214 -0.93831944465637207 -0.97164559364318848 0 0 0 0 0;
	setAttr -s 14 ".kox[2:13]"  0.75185447931289673 0.66037291288375854 
		1 1 0.96019905805587769 0.34576967358589172 0.58330166339874268 1 1 1 1 1;
	setAttr -s 14 ".koy[2:13]"  -0.65932905673980713 -0.750937819480896 
		0 0 0.27931687235832214 -0.93831944465637207 -0.8122556209564209 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU257";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 13 0 22 0 27 0 31 
		0 33 0 36 0 41 0 43 0;
	setAttr -s 13 ".kit[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kot[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA804";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 68.629003384766676 2 68.629003384766676 
		5 68.629003384766676 7 68.629003384766676 11 68.629003384766676 13 0 22 0 27 0 31 
		0 33 0 36 0 41 0 43 0;
	setAttr -s 13 ".kit[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kot[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA805";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 5.1251585428584878 2 5.1251585428584878 
		5 5.1251585428584878 7 5.1251585428584878 11 5.1251585428584878 13 0 22 0 27 0 31 
		0 33 0 36 0 41 0 43 0;
	setAttr -s 13 ".kit[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kot[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA806";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -1.4794141658124507 2 -1.4794141658124507 
		5 -1.4794141658124507 7 -1.4794141658124507 11 -1.4794141658124507 13 0 22 0 27 0 
		31 0 33 0 36 0 41 0 43 0;
	setAttr -s 13 ".kit[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kot[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA807";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 2.9967431843380723 2 2.9967431843380723 
		5 2.9967431843380723 7 2.9967431843380723 11 2.9967431843380723 13 0 22 0 27 0 31 
		0 33 -4.4033846197414626 34 -12.165150319657149 36 -4.4033846197414626 41 -4.4033846197414626 
		43 -4.4033846197414626;
	setAttr -s 14 ".kit[1:13]"  10 1 3 3 3 3 10 3 
		3 10 10 3 3;
	setAttr -s 14 ".kot[1:13]"  10 1 3 3 3 3 10 3 
		3 10 10 3 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA808";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 27.356153209428296 2 27.356153209428296 
		5 27.356153209428296 7 27.356153209428296 11 27.356153209428296 13 0 22 0 27 0 31 
		0 33 -18.682943955453336 36 -18.682943955453336 41 -18.682943955453336 43 -18.682943955453336;
	setAttr -s 13 ".kit[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kot[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA809";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 4.8891453517792058 2 4.8891453517792058 
		5 4.8891453517792058 7 4.8891453517792058 11 4.8891453517792058 13 0 22 0 27 0 31 
		0 33 16.892457810830809 36 16.892457810830809 41 16.892457810830809 43 16.892457810830809;
	setAttr -s 13 ".kit[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kot[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU258";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 13 0 22 0 27 0 31 
		0 33 0 36 0 41 0 43 0;
	setAttr -s 13 ".kit[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kot[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA810";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 59.032884886088816 2 59.032884886088816 
		5 59.032884886088816 7 59.032884886088816 11 59.032884886088816 13 0 19 21.542956940288235 
		22 0 27 0 31 0 33 0 36 0 41 0 43 0;
	setAttr -s 14 ".kit[1:13]"  10 1 3 3 3 10 3 10 
		3 3 10 3 3;
	setAttr -s 14 ".kot[1:13]"  10 1 3 3 3 10 3 10 
		3 3 10 3 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA811";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 13 0 22 0 27 0 31 
		0 33 0 36 0 41 0 43 0;
	setAttr -s 13 ".kit[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kot[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA812";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 13 0 22 0 27 0 31 
		0 33 0 36 0 41 0 43 0;
	setAttr -s 13 ".kit[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kot[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA813";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 61.945270723308987 2 61.945270723308987 
		5 61.945270723308987 7 61.945270723308987 11 61.945270723308987 13 -40.312309692601005 
		19 -18.769352752312816 22 -40.312309692601012 27 -40.312309692601012 31 -40.312309692601012 
		33 -45.88526113388405 34 -50.198884371337499 36 -45.88526113388405 41 -45.88526113388405 
		43 -45.88526113388405;
	setAttr -s 15 ".kit[1:14]"  10 1 3 3 3 10 3 10 
		3 3 10 10 3 3;
	setAttr -s 15 ".kot[1:14]"  10 1 3 3 3 10 3 10 
		3 3 10 10 3 3;
	setAttr -s 15 ".kix[2:14]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 15 ".kiy[2:14]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 15 ".kox[2:14]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 15 ".koy[2:14]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA814";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 2 0 5 0 7 0 11 0 13 0 22 0 27 0 31 
		0 33 0 34 -0.90987971702741655 36 0 41 0 43 0;
	setAttr -s 14 ".kit[1:13]"  10 1 3 3 3 3 10 3 
		3 10 10 3 3;
	setAttr -s 14 ".kot[1:13]"  10 1 3 3 3 3 10 3 
		3 10 10 3 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA815";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 2 0 5 0 7 0 11 0 13 0 22 0 27 0 31 
		0 33 0 34 -1.0029835633837971 36 0 41 0 43 0;
	setAttr -s 14 ".kit[1:13]"  10 1 3 3 3 3 10 3 
		3 10 10 3 3;
	setAttr -s 14 ".kot[1:13]"  10 1 3 3 3 3 10 3 
		3 10 10 3 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU259";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 13 0 22 0 27 0 31 
		0 33 0 36 0 41 0 43 0;
	setAttr -s 13 ".kit[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kot[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA816";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 59.032884886088816 2 59.032884886088816 
		5 59.032884886088816 7 59.032884886088816 11 59.032884886088816 13 0 19 21.542956940288235 
		22 0 27 0 31 0 33 0 36 0 41 0 43 0;
	setAttr -s 14 ".kit[1:13]"  10 1 3 3 3 10 3 10 
		3 3 10 3 3;
	setAttr -s 14 ".kot[1:13]"  10 1 3 3 3 10 3 10 
		3 3 10 3 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA817";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 13 0 22 0 27 0 31 
		0 33 0 36 0 41 0 43 0;
	setAttr -s 13 ".kit[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kot[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA818";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 13 0 22 0 27 0 31 
		0 33 0 36 0 41 0 43 0;
	setAttr -s 13 ".kit[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kot[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA819";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 61.945270723308987 2 61.945270723308987 
		5 61.945270723308987 7 61.945270723308987 11 61.945270723308987 13 -40.312309692601005 
		19 -18.769352752312816 22 -40.312309692601012 27 -40.312309692601012 31 -40.312309692601012 
		33 -58.617610400810783 34 -63.083074778526239 36 -58.617610400810783 41 -58.617610400810783 
		43 -58.617610400810783;
	setAttr -s 15 ".kit[1:14]"  10 1 3 3 3 10 3 10 
		3 3 10 10 3 3;
	setAttr -s 15 ".kot[1:14]"  10 1 3 3 3 10 3 10 
		3 3 10 10 3 3;
	setAttr -s 15 ".kix[2:14]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 15 ".kiy[2:14]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 15 ".kox[2:14]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 15 ".koy[2:14]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA820";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 2 0 5 0 7 0 11 0 13 0 22 0 27 0 31 
		0 33 -7.3816056564844104 34 -8.0465006532767109 36 -7.3816056564844104 41 -7.3816056564844104 
		43 -7.3816056564844104;
	setAttr -s 14 ".kit[1:13]"  10 1 3 3 3 3 10 3 
		3 10 10 3 3;
	setAttr -s 14 ".kot[1:13]"  10 1 3 3 3 3 10 3 
		3 10 10 3 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA821";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 2 0 5 0 7 0 11 0 13 0 22 0 27 0 31 
		0 33 -2.9484080596279227 34 -4.1388868225429407 36 -2.9484080596279227 41 -2.9484080596279227 
		43 -2.9484080596279227;
	setAttr -s 14 ".kit[1:13]"  10 1 3 3 3 3 10 3 
		3 10 10 3 3;
	setAttr -s 14 ".kot[1:13]"  10 1 3 3 3 3 10 3 
		3 10 10 3 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU260";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 13 0 22 0 27 0 31 
		0 33 0 36 0 41 0 43 0;
	setAttr -s 13 ".kit[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kot[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA822";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 59.032884886088816 2 59.032884886088816 
		5 59.032884886088816 7 59.032884886088816 11 59.032884886088816 13 0 19 21.542956940288235 
		22 0 27 0 31 0 33 0 36 0 41 0 43 0;
	setAttr -s 14 ".kit[1:13]"  10 1 3 3 3 10 3 10 
		3 3 10 3 3;
	setAttr -s 14 ".kot[1:13]"  10 1 3 3 3 10 3 10 
		3 3 10 3 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA823";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 13 0 22 0 27 0 31 
		0 33 0 36 0 41 0 43 0;
	setAttr -s 13 ".kit[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kot[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA824";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 13 0 22 0 27 0 31 
		0 33 0 36 0 41 0 43 0;
	setAttr -s 13 ".kit[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kot[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA825";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 72.878304588436421 2 72.878304588436421 
		5 72.878304588436421 7 72.878304588436421 11 72.878304588436421 13 -40.312309692601026 
		19 -18.769352752312816 22 -40.312309692601012 27 -40.312309692601012 31 -40.312309692601012 
		33 -25.819075488801342 34 -30.131324412794104 36 -25.819075488801342 41 -25.819075488801342 
		43 -25.819075488801342;
	setAttr -s 15 ".kit[1:14]"  10 1 3 3 3 10 3 10 
		3 3 10 10 3 3;
	setAttr -s 15 ".kot[1:14]"  10 1 3 3 3 10 3 10 
		3 3 10 10 3 3;
	setAttr -s 15 ".kix[2:14]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 15 ".kiy[2:14]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 15 ".kox[2:14]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 15 ".koy[2:14]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA826";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 2 0 5 0 7 0 11 0 13 0 22 0 27 0 31 
		0 33 0 34 -1.198766859918025 36 0 41 0 43 0;
	setAttr -s 14 ".kit[1:13]"  10 1 3 3 3 3 10 3 
		3 10 10 3 3;
	setAttr -s 14 ".kot[1:13]"  10 1 3 3 3 3 10 3 
		3 10 10 3 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA827";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 2 0 5 0 7 0 11 0 13 0 22 0 27 0 31 
		0 33 0 34 -0.62991148230639593 36 0 41 0 43 0;
	setAttr -s 14 ".kit[1:13]"  10 1 3 3 3 3 10 3 
		3 10 10 3 3;
	setAttr -s 14 ".kot[1:13]"  10 1 3 3 3 3 10 3 
		3 10 10 3 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU261";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 13 0 22 0 27 0 31 
		0 33 0 36 0 41 0 43 0;
	setAttr -s 13 ".kit[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kot[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA828";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 77.67986202714836 2 77.67986202714836 
		5 77.67986202714836 7 77.67986202714836 11 77.67986202714836 13 0 19 21.542956940288235 
		22 0 27 0 31 0 33 0 36 0 41 0 43 0;
	setAttr -s 14 ".kit[1:13]"  10 1 3 3 3 10 3 10 
		3 3 10 3 3;
	setAttr -s 14 ".kot[1:13]"  10 1 3 3 3 10 3 10 
		3 3 10 3 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA829";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 13 0 22 0 27 0 31 
		0 33 0 36 0 41 0 43 0;
	setAttr -s 13 ".kit[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kot[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA830";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 13 0 22 0 27 0 31 
		0 33 0 36 0 41 0 43 0;
	setAttr -s 13 ".kit[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kot[1:12]"  10 1 3 3 3 3 10 3 
		3 10 3 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA831";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 65.952779168408995 2 65.952779168408995 
		5 65.952779168408995 7 65.952779168408995 11 65.952779168408995 13 -40.312309692601026 
		19 -18.769352752312816 22 -40.312309692601012 27 -40.312309692601012 31 -40.312309692601012 
		33 -17.259181924678142 34 -21.569802418546857 36 -17.259181924678142 41 -17.259181924678142 
		43 -17.259181924678142;
	setAttr -s 15 ".kit[1:14]"  10 1 3 3 3 10 3 10 
		3 3 10 10 3 3;
	setAttr -s 15 ".kot[1:14]"  10 1 3 3 3 10 3 10 
		3 3 10 10 3 3;
	setAttr -s 15 ".kix[2:14]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 15 ".kiy[2:14]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 15 ".kox[2:14]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 15 ".koy[2:14]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA832";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 12.091864976351665 2 12.091864976351665 
		5 12.091864976351665 7 12.091864976351665 11 12.091864976351665 13 0 22 0 27 0 31 
		0 33 0 34 -1.2791689729134357 36 0 41 0 43 0;
	setAttr -s 14 ".kit[1:13]"  10 1 3 3 3 3 10 3 
		3 10 10 3 3;
	setAttr -s 14 ".kot[1:13]"  10 1 3 3 3 3 10 3 
		3 10 10 3 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA833";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 -6.5683373417752975 2 -6.5683373417752975 
		5 -6.5683373417752975 7 -6.5683373417752975 11 -6.5683373417752975 13 0 22 0 27 0 
		31 0 33 0 34 -0.44444585622849475 36 0 41 0 43 0;
	setAttr -s 14 ".kit[1:13]"  10 1 3 3 3 3 10 3 
		3 10 10 3 3;
	setAttr -s 14 ".kot[1:13]"  10 1 3 3 3 3 10 3 
		3 10 10 3 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA834";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 14 0 22 0 27 0 31 0 33 
		0 36 25.977720228103731 39 25.977720228103731 41 25.977720228103731 43 25.977720228103731;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 3 3 3 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 3 3 3 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA835";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 14 0 22 18.004504581041498 
		27 0 31 0 33 0 36 -5.5107762795220516 39 -5.5107762795220516 41 -5.5107762795220516 
		43 -5.5107762795220516;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 3 3 3 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 3 3 3 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA836";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 14 0 22 0 27 0 31 0 33 
		0 36 1.8630866784210587 39 1.8630866784210587 41 1.8630866784210587 43 1.8630866784210587;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 3 3 3 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 3 3 3 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU262";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA837";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		-7.7796350933991016 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA838";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA839";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA840";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		-7.7796350933991016 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA841";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA842";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU263";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA843";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		-7.7796350933991016 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA844";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA845";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA846";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		-17.679367413754001 41 -12.084363608786136 43 -12.084363608786136;
	setAttr -s 11 ".kit[0:10]"  3 10 1 10 10 10 10 10 
		10 10 3;
	setAttr -s 11 ".kot[0:10]"  3 10 1 10 10 10 10 10 
		10 10 3;
	setAttr -s 11 ".kix[2:10]"  1 1 1 1 1 1 0.84504729509353638 1 1;
	setAttr -s 11 ".kiy[2:10]"  0 0 0 0 0 0 -0.53469163179397583 0 0;
	setAttr -s 11 ".kox[2:10]"  1 1 1 1 1 1 0.84504729509353638 1 1;
	setAttr -s 11 ".koy[2:10]"  0 0 0 0 0 0 -0.53469163179397583 0 0;
createNode animCurveTA -n "animCurveTA847";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 41 -1.7592609364212668 43 -1.7592609364212668;
	setAttr -s 11 ".kit[0:10]"  3 10 1 10 10 10 10 10 
		10 10 3;
	setAttr -s 11 ".kot[0:10]"  3 10 1 10 10 10 10 10 
		10 10 3;
	setAttr -s 11 ".kix[2:10]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[2:10]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[2:10]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[2:10]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA848";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 41 1.8233482159530252 43 1.8233482159530252;
	setAttr -s 11 ".kit[0:10]"  3 10 1 10 10 10 10 10 
		10 10 3;
	setAttr -s 11 ".kot[0:10]"  3 10 1 10 10 10 10 10 
		10 10 3;
	setAttr -s 11 ".kix[2:10]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[2:10]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[2:10]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[2:10]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU264";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA849";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		-7.7796350933991016 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA850";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA851";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA852";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		-17.679367413754001 41 -22.353444833342461 43 -22.353444833342461;
	setAttr -s 11 ".kit[0:10]"  3 10 1 10 10 10 10 10 
		10 10 3;
	setAttr -s 11 ".kot[0:10]"  3 10 1 10 10 10 10 10 
		10 10 3;
	setAttr -s 11 ".kix[2:10]"  1 1 1 1 1 1 0.64958471059799194 1 1;
	setAttr -s 11 ".kiy[2:10]"  0 0 0 0 0 0 -0.76028925180435181 0 0;
	setAttr -s 11 ".kox[2:10]"  1 1 1 1 1 1 0.64958471059799194 1 1;
	setAttr -s 11 ".koy[2:10]"  0 0 0 0 0 0 -0.76028925180435181 0 0;
createNode animCurveTA -n "animCurveTA853";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 41 -1.7592609364212668 43 -1.7592609364212668;
	setAttr -s 11 ".kit[0:10]"  3 10 1 10 10 10 10 10 
		10 10 3;
	setAttr -s 11 ".kot[0:10]"  3 10 1 10 10 10 10 10 
		10 10 3;
	setAttr -s 11 ".kix[2:10]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[2:10]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[2:10]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[2:10]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA854";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 41 1.8233482159530252 43 1.8233482159530252;
	setAttr -s 11 ".kit[0:10]"  3 10 1 10 10 10 10 10 
		10 10 3;
	setAttr -s 11 ".kot[0:10]"  3 10 1 10 10 10 10 10 
		10 10 3;
	setAttr -s 11 ".kix[2:10]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[2:10]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[2:10]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[2:10]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU265";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA855";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		-7.7796350933991016 36 37.385239462945776 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 0.24748380482196808 0.82734888792037964 
		1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0.96889197826385498 0.56168842315673828 
		0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 0.24748380482196808 0.82734888792037964 
		1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0.96889197826385498 0.56168842315673828 
		0 0 0;
createNode animCurveTA -n "animCurveTA856";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA857";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA858";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		-7.7796350933991016 36 -13.187754695667278 39 6.5101023961039228 41 6.5101023961039228 
		43 6.5101023961039228;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 0.58649158477783203 0.62560546398162842 
		0.47642701864242554 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 -0.80995535850524902 0.78013956546783447 
		-0.87921398878097534 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 0.58649158477783203 0.62560546398162842 
		0.47642704844474792 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 -0.80995535850524902 0.78013956546783447 
		-0.87921404838562012 0 0;
createNode animCurveTA -n "animCurveTA859";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 -2.7315066280018936 39 -2.7315066280018936 41 -2.7315066280018936 43 -2.7315066280018936;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA860";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 -10.287310747697958 39 -10.287310747697958 41 -10.287310747697958 43 -10.287310747697958;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU266";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA861";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		-7.7796350933991016 36 15.647942002745436 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 0.52092045545578003 0.82734888792037964 
		1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0.85360521078109741 0.56168842315673828 
		0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 0.52092045545578003 0.82734888792037964 
		1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0.85360521078109741 0.56168842315673828 
		0 0 0;
createNode animCurveTA -n "animCurveTA862";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 -6.461923906653797 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA863";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 -3.134443087799351 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA864";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		-7.7796350933991016 36 14.018822345216234 39 24.136688867290676 41 24.136688867290676 
		43 24.136688867290676;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 0.56297510862350464 0.3379172682762146 
		1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0.8264738917350769 0.94117581844329834 
		0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 0.56297510862350464 0.3379172682762146 
		1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0.8264738917350769 0.94117581844329834 
		0 0 0;
createNode animCurveTA -n "animCurveTA865";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 10.015141006517378 39 10.015141006517378 41 10.015141006517378 43 10.015141006517378;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA866";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 -2.1426042859260206 39 -2.1426042859260206 41 -2.1426042859260206 43 -2.1426042859260206;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA867";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 2 0 5 0 7 0 11 0 16 -6.3359854732410907 
		22 0 27 11.32160258868922 31 -14.836988903376895 33 11.972477638934345 37 0 39 0 
		41 0 43 0;
	setAttr -s 14 ".kit[0:13]"  3 10 1 10 10 10 10 10 
		10 10 10 1 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 1 10 10 10 10 10 
		10 10 10 1 10 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 1 0.76551657915115356 0.75699341297149658 
		0.998390793800354 0.61125421524047852 1 1 1 1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0 0.64341616630554199 -0.65342247486114502 
		0.056708145886659622 0.79143428802490234 0 0 0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 1 0.76551657915115356 0.75699341297149658 
		0.998390793800354 0.61125421524047852 1 1 1 1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0 0.64341616630554199 -0.65342247486114502 
		0.056708145886659622 0.79143428802490234 0 0 0 0;
createNode animCurveTA -n "animCurveTA868";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 2 0 5 0 7 0 11 0 16 -4.7348207203390285 
		22 0 27 0.35175206288418864 31 -0.35653127113968325 33 10.419656931649664 37 0 39 
		0 41 0 43 0;
	setAttr -s 14 ".kit[0:13]"  3 10 1 10 10 10 10 10 
		10 10 10 1 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 1 10 10 10 10 10 
		10 10 10 1 10 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 1 1 1 1 0.99951636791229248 1 1 1 
		1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0 0 0 0 0.031098166480660439 0 0 
		0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 1 1 1 1 0.99951636791229248 1 1 1 
		1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0 0 0 0 0.031098166480660439 0 0 
		0 0;
createNode animCurveTA -n "animCurveTA869";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 2 0 5 0 7 0 11 0 16 -0.15803542055089459 
		22 0 27 1.276697354356348 31 -6.2985800827681722 33 -8.9004156517433248 37 0 39 0 
		41 0 43 0;
	setAttr -s 14 ".kit[0:13]"  3 10 1 10 10 10 10 10 
		10 10 10 1 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 1 10 10 10 10 10 
		10 10 10 1 10 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU267";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 14 0 22 0 27 0 31 0 34 
		0 35 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[1:12]"  9 1 9 9 9 9 9 3 
		3 1 1 3;
	setAttr -s 13 ".kot[1:12]"  5 5 5 5 5 5 5 3 
		3 1 1 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[10:12]"  1 1 1;
	setAttr -s 13 ".koy[10:12]"  0 0 0;
createNode animCurveTU -n "animCurveTU268";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 14 0 22 0 27 0 31 0 34 
		0 35 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[1:12]"  9 1 9 9 9 9 9 3 
		3 1 1 3;
	setAttr -s 13 ".kot[1:12]"  5 5 5 5 5 5 5 3 
		3 1 1 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[10:12]"  1 1 1;
	setAttr -s 13 ".koy[10:12]"  0 0 0;
createNode animCurveTU -n "animCurveTU269";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 1 2 1 5 1 7 1 14 1 22 1 27 1 31 1 34 
		1 35 1 39 1 41 1 43 1;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		3 3 1 1 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		3 3 1 1 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA870";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 -10.173354040024311 2 -10.173354040024311 
		5 -10.173354040024311 7 -10.173354040024311 14 -10.173354040024311 19 26.874845992985339 
		22 41.760201708340183 24 18.873474692313504 27 14.210194521372204 29 2.3696164636205399 
		31 21.073126575175873 34 -0.038488493993573854 35 0.76835332578339133 39 -5.7306576477871412 
		41 -5.7306576477871412 43 -5.7306576477871412;
	setAttr -s 16 ".kit[0:15]"  3 10 1 10 10 10 10 10 
		10 10 10 3 9 1 1 3;
	setAttr -s 16 ".kot[0:15]"  3 10 1 10 10 10 10 10 
		10 10 10 3 9 1 1 3;
	setAttr -s 16 ".kix[2:15]"  1 1 1 0.28223943710327148 0.76649647951126099 
		0.32750111818313599 0.50081741809844971 0.74390202760696411 0.96964395046234131 1 
		0.85897386074066162 1 1 1;
	setAttr -s 16 ".kiy[2:15]"  0 0 0 0.95934396982192993 -0.64224857091903687 
		-0.94485080242156982 -0.86555290222167969 0.66828864812850952 -0.24452106654644012 
		0 -0.51201945543289185 0 0 0;
	setAttr -s 16 ".kox[2:15]"  1 1 1 0.28223943710327148 0.76649647951126099 
		0.32750111818313599 0.50081741809844971 0.74390202760696411 0.96964395046234131 1 
		0.85897386074066162 1 1 1;
	setAttr -s 16 ".koy[2:15]"  0 0 0 0.95934396982192993 -0.64224857091903687 
		-0.94485080242156982 -0.86555290222167969 0.66828864812850952 -0.24452106654644012 
		0 -0.51201945543289185 0 0 0;
createNode animCurveTA -n "animCurveTA871";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 0 2 0 5 0 7 0 14 0 19 10.498595664458044 
		22 23.111344583807231 24 57.865108479211763 27 72.32594518575047 29 105.85897209498501 
		31 147.19841630429411 34 144.90370095942225 35 141.25012332775012 39 142.79143716190964 
		41 142.79143716190964 43 142.79143716190964;
	setAttr -s 16 ".kit[0:15]"  3 10 1 10 10 10 10 10 
		10 10 10 9 9 1 1 3;
	setAttr -s 16 ".kot[0:15]"  3 10 1 10 10 10 10 10 
		10 10 10 9 9 1 1 3;
	setAttr -s 16 ".kix[2:15]"  1 1 1 0.55148035287857056 0.19762818515300751 
		0.19048117101192474 0.19514381885528564 0.10150565207004547 1 0.78902631998062134 
		0.97639888525009155 1 1 1;
	setAttr -s 16 ".kiy[2:15]"  0 0 0 0.83418792486190796 0.98027706146240234 
		0.98169088363647461 0.9807746410369873 0.99483495950698853 0 -0.61435937881469727 
		-0.2159753292798996 0 0 0;
	setAttr -s 16 ".kox[2:15]"  1 1 1 0.55148035287857056 0.19762818515300751 
		0.19048117101192474 0.19514381885528564 0.10150565207004547 1 0.78902631998062134 
		0.97639888525009155 1 1 1;
	setAttr -s 16 ".koy[2:15]"  0 0 0 0.83418792486190796 0.98027706146240234 
		0.98169088363647461 0.9807746410369873 0.99483495950698853 0 -0.61435937881469727 
		-0.2159753292798996 0 0 0;
createNode animCurveTA -n "animCurveTA872";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 0 2 0 5 0 7 0 14 0 19 19.590923307382219 
		22 23.572372207411131 24 19.601319095044968 27 27.060085593876281 29 -17.696147042524014 
		31 -31.888159535024592 34 -51.793829728069362 35 -52.787795741725127 39 -44.466320376705113 
		41 -44.466320376705113 43 -44.466320376705113;
	setAttr -s 16 ".kit[0:15]"  3 10 1 10 10 10 10 10 
		3 10 10 1 9 1 1 3;
	setAttr -s 16 ".kot[0:15]"  3 10 1 10 10 10 10 10 
		3 10 10 1 9 1 1 3;
	setAttr -s 16 ".kix[2:15]"  1 1 1 0.54390764236450195 0.99999940395355225 
		0.93931102752685547 1 0.1285209059715271 0.26968091726303101 0.6954084038734436 0.79335016012191772 
		1 1 1;
	setAttr -s 16 ".kiy[2:15]"  0 0 0 0.83914506435394287 0.0010886435629799962 
		0.3430669903755188 0 -0.99170678853988647 -0.96294981241226196 -0.71861481666564941 
		0.60876548290252686 0 0 0;
	setAttr -s 16 ".kox[2:15]"  1 1 1 0.54390764236450195 0.99999940395355225 
		0.93931102752685547 1 0.1285209059715271 0.26968091726303101 0.69540822505950928 
		0.79335016012191772 1 1 1;
	setAttr -s 16 ".koy[2:15]"  0 0 0 0.83914506435394287 0.0010886435629799962 
		0.3430669903755188 0 -0.99170678853988647 -0.96294981241226196 -0.71861493587493896 
		0.60876548290252686 0 0 0;
createNode animCurveTL -n "animCurveTL259";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 2 0 5 0 7 0 14 0 22 0.20639485667367813 
		24 0.23160215959813155 27 0.34573637022443471 29 0.74463913491472766 33 0.61732363491245645 
		35 0.30805011133602223 39 0.28490511393758888 41 0.28490511393758888 43 0.28490511393758888;
	setAttr -s 14 ".kit[0:13]"  3 10 1 10 10 9 9 9 
		9 10 3 1 1 3;
	setAttr -s 14 ".kot[0:13]"  3 10 1 10 10 9 9 9 
		9 10 3 1 1 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 0.82123064994812012 0.76719552278518677 
		0.30896803736686707 0.59297442436218262 0.41647690534591675 1 1 1 1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0.57059633731842041 0.64141327142715454 
		0.95107239484786987 0.8052213191986084 -0.90914630889892578 0 0 0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 0.82123064994812012 0.76719552278518677 
		0.30896803736686707 0.59297442436218262 0.41647690534591675 1 1 1 1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0.57059633731842041 0.64141327142715454 
		0.95107239484786987 0.8052213191986084 -0.90914630889892578 0 0 0 0;
createNode animCurveTL -n "animCurveTL260";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 0.643246524321337 2 0.643246524321337 
		5 0.643246524321337 7 0.643246524321337 14 0.643246524321337 22 0.63644746782980466 
		24 0.61917303365589049 27 0.434690133871797 29 -0.17038012626889609 31 -0.53899717747888176 
		33 -0.53489998510165471 34 -0.56502169766696486 35 -0.56164703158684048 39 -0.54883168169071606 
		41 -0.54883168169071606 43 -0.54883168169071606;
	setAttr -s 16 ".kit[0:15]"  3 10 1 10 10 9 1 10 
		10 10 10 9 9 1 1 3;
	setAttr -s 16 ".kot[0:15]"  3 10 1 10 10 9 1 10 
		10 10 10 9 9 1 1 3;
	setAttr -s 16 ".kix[2:15]"  1 1 1 0.99740231037139893 0.87663519382476807 
		0.20653840899467468 0.13567039370536804 1 1 0.92809015512466431 0.99531495571136475 
		1 1 1;
	setAttr -s 16 ".kiy[2:15]"  0 0 0 -0.072032861411571503 -0.4811556339263916 
		-0.97843855619430542 -0.99075406789779663 0 0 -0.37235543131828308 0.096685014665126801 
		0 0 0;
	setAttr -s 16 ".kox[2:15]"  1 1 1 0.99740231037139893 0.87663531303405762 
		0.20653840899467468 0.13567039370536804 1 1 0.92809015512466431 0.99531495571136475 
		1 1 1;
	setAttr -s 16 ".koy[2:15]"  0 0 0 -0.072032861411571503 -0.48115545511245728 
		-0.97843855619430542 -0.99075406789779663 0 0 -0.37235543131828308 0.096685014665126801 
		0 0 0;
createNode animCurveTL -n "animCurveTL261";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 18 ".ktv[0:17]"  0 0.10481400598920043 2 0.10481400598920043 
		5 0.10481400598920043 7 0.10481400598920043 14 0.10481400598920043 17 -0.030348689185831557 
		19 -0.16719718818278245 22 -0.2584683169082666 24 -0.27525604929472347 27 0.066876764061359617 
		29 0.34755110965711711 31 1.0489522395774686 33 1.3269321472167463 34 1.2906868379017793 
		35 1.3969004126048967 39 1.4659355404608401 41 1.4659355404608401 43 1.4659355404608401;
	setAttr -s 18 ".kit[0:17]"  3 10 1 10 10 10 10 9 
		10 10 10 10 10 9 9 1 1 3;
	setAttr -s 18 ".kot[0:17]"  3 10 1 10 10 10 10 9 
		10 10 10 10 10 9 9 1 1 3;
	setAttr -s 18 ".kix[2:17]"  1 1 1 0.52244842052459717 0.58993327617645264 
		0.83907449245452881 1 0.25850927829742432 0.13453264534473419 0.13489609956741333 
		1 0.68981879949569702 0.68914133310317993 1 1 1;
	setAttr -s 18 ".kiy[2:17]"  0 0 0 -0.85267090797424316 -0.80745202302932739 
		-0.54401654005050659 0 0.96600878238677979 0.9909091591835022 0.9908597469329834 
		0 0.72398209571838379 0.72462689876556396 0 0 0;
	setAttr -s 18 ".kox[2:17]"  1 1 1 0.52244842052459717 0.58993327617645264 
		0.83907449245452881 1 0.25850927829742432 0.13453264534473419 0.13489609956741333 
		1 0.68981879949569702 0.68914133310317993 1 1 1;
	setAttr -s 18 ".koy[2:17]"  0 0 0 -0.85267090797424316 -0.80745202302932739 
		-0.54401654005050659 0 0.96600878238677979 0.9909091591835022 0.9908597469329834 
		0 0.72398209571838379 0.72462689876556396 0 0 0;
createNode animCurveTA -n "animCurveTA873";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA874";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA875";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU270";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA876";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA877";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA878";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA879";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA880";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA881";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA882";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA883";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA884";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU271";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 2 1 7 1 22 1 27 1 31 1 36 1 39 1 41 
		1 43 1;
	setAttr -s 10 ".kit[0:9]"  3 10 1 10 10 10 10 1 
		10 3;
	setAttr -s 10 ".kot[0:9]"  3 10 1 10 10 10 10 1 
		10 3;
	setAttr -s 10 ".kix[2:9]"  1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[2:9]"  0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[2:9]"  1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[2:9]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA885";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 40.718223104721211 2 14.155327014276583 
		7 -7.7677686993310147 11 -20.889881033642812 22 14.835398462975625 27 79.863416532545415 
		31 29.677643866558302 36 0 39 0 41 0 43 0;
	setAttr -s 11 ".kit[0:10]"  3 10 1 10 10 10 10 10 
		1 10 3;
	setAttr -s 11 ".kot[0:10]"  3 10 1 10 10 10 10 10 
		1 10 3;
	setAttr -s 11 ".kix[2:10]"  0.83881372213363647 0.78506380319595337 
		0.29023745656013489 0.75687891244888306 0.2104085236787796 1 1 1 1;
	setAttr -s 11 ".kiy[2:10]"  -0.5444185733795166 0.61941486597061157 
		0.9569547176361084 0.65355509519577026 -0.97761350870132446 0 0 0 0;
	setAttr -s 11 ".kox[2:10]"  0.83881372213363647 0.78506380319595337 
		0.29023745656013489 0.75687891244888306 0.2104085236787796 1 1 1 1;
	setAttr -s 11 ".koy[2:10]"  -0.5444185733795166 0.61941486597061157 
		0.9569547176361084 0.65355509519577026 -0.97761350870132446 0 0 0 0;
createNode animCurveTA -n "animCurveTA886";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -38.301705751263519 2 -27.431138339915236 
		7 -25.032529204280031 11 -26.424364097467482 22 2.8590788360712351 27 -35.592604347620409 
		31 -0.45903637568014266 36 -21.576012510092962 39 -21.576012510092962 41 -21.576012510092962 
		43 -21.576012510092962;
	setAttr -s 11 ".kit[0:10]"  3 10 1 10 10 10 10 10 
		1 10 3;
	setAttr -s 11 ".kot[0:10]"  3 10 1 10 10 10 10 10 
		1 10 3;
	setAttr -s 11 ".kix[2:10]"  0.8530048131942749 1 0.95781838893890381 
		0.98187285661697388 0.77499306201934814 1 1 1 1;
	setAttr -s 11 ".kiy[2:10]"  0.52190303802490234 0 -0.28737425804138184 
		-0.18954087793827057 0.63196969032287598 0 0 0 0;
	setAttr -s 11 ".kox[2:10]"  0.8530048131942749 1 0.95781838893890381 
		0.98187285661697388 0.77499306201934814 1 1 1 1;
	setAttr -s 11 ".koy[2:10]"  0.52190303802490234 0 -0.28737425804138184 
		-0.18954087793827057 0.63196969032287598 0 0 0 0;
createNode animCurveTA -n "animCurveTA887";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 21.733945627788874 2 25.502999873108472 
		7 17.03639974327983 11 14.336032114420771 22 -4.2186992098418568 27 3.9297518598546173 
		31 -4.9472784741842135 36 0 39 0 41 0 43 0;
	setAttr -s 11 ".kit[0:10]"  3 10 1 10 10 10 10 10 
		1 10 3;
	setAttr -s 11 ".kot[0:10]"  3 10 1 10 10 10 10 10 
		1 10 3;
	setAttr -s 11 ".kix[2:10]"  0.99658918380737305 1 0.94661545753479004 
		0.99910295009613037 0.97484743595123291 1 1 1 1;
	setAttr -s 11 ".kiy[2:10]"  -0.082522429525852203 0 -0.32236489653587341 
		-0.042349006980657578 -0.22287316620349884 0 0 0 0;
	setAttr -s 11 ".kox[2:10]"  0.99658918380737305 1 0.94661545753479004 
		0.99910295009613037 0.97484743595123291 1 1 1 1;
	setAttr -s 11 ".koy[2:10]"  -0.082522429525852203 0 -0.32236489653587341 
		-0.042349006980657578 -0.22287316620349884 0 0 0 0;
createNode animCurveTU -n "animCurveTU272";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 36 0 41 
		0 43 0;
	setAttr -s 10 ".kit[0:9]"  3 9 1 9 9 9 9 1 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 5 5 5 5 5 5 5 
		5 3;
	setAttr -s 10 ".kix[2:9]"  1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[2:9]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU273";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 36 0 41 
		0 43 0;
	setAttr -s 10 ".kit[0:9]"  3 9 1 9 9 9 9 1 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 5 5 5 5 5 5 5 
		5 3;
	setAttr -s 10 ".kix[2:9]"  1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[2:9]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU274";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 2 1 5 1 7 1 11 1 22 1 27 1 36 1 41 
		1 43 1;
	setAttr -s 10 ".kit[0:9]"  3 10 1 10 10 10 10 1 
		10 3;
	setAttr -s 10 ".kot[0:9]"  3 10 1 10 10 10 10 1 
		10 3;
	setAttr -s 10 ".kix[2:9]"  1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[2:9]"  0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[2:9]"  1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[2:9]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA888";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 17.962181958626559 2 17.962181958626559 
		5 17.962181958626559 7 17.962181958626559 11 17.962181958626559 18 26.276553397927874 
		22 5.4876153991424177 27 -27.80794504784684 34 -23.479231876963315 36 -39.061920741797849 
		41 -39.061920741797849 43 -39.061920741797849;
	setAttr -s 12 ".kit[0:11]"  3 10 1 10 10 10 10 10 
		10 1 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 1 10 10 10 10 10 
		10 1 10 3;
	setAttr -s 12 ".kix[2:11]"  1 1 1 0.85984039306640625 0.30288404226303101 
		0.62047362327575684 0.83663094043731689 1 1 1;
	setAttr -s 12 ".kiy[2:11]"  0 0 0 -0.51056289672851563 -0.95302742719650269 
		-0.78422731161117554 -0.5477670431137085 0 0 0;
	setAttr -s 12 ".kox[2:11]"  1 1 1 0.85984039306640625 0.30288404226303101 
		0.62047362327575684 0.83663094043731689 1 1 1;
	setAttr -s 12 ".koy[2:11]"  0 0 0 -0.51056289672851563 -0.95302742719650269 
		-0.78422731161117554 -0.5477670431137085 0 0 0;
createNode animCurveTA -n "animCurveTA889";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 2 0 5 0 7 0 11 0 18 6.0329894037795402 
		22 56.342651081902133 27 88.04570325467509 34 147.76650323660223 36 143.61505267095049 
		41 143.61505267095049 43 143.61505267095049;
	setAttr -s 12 ".kit[0:11]"  3 10 1 10 10 10 10 10 
		10 1 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 1 10 10 10 10 10 
		10 1 10 3;
	setAttr -s 12 ".kix[2:11]"  1 1 1 0.34937265515327454 0.20512931048870087 
		0.24315814673900604 0.29550644755363464 0.71480226516723633 1 1;
	setAttr -s 12 ".kiy[2:11]"  0 0 0 0.93698388338088989 0.97873491048812866 
		0.96998661756515503 0.95534074306488037 -0.69932663440704346 0 0;
	setAttr -s 12 ".kox[2:11]"  1 1 1 0.34937265515327454 0.20512931048870087 
		0.24315814673900604 0.29550644755363464 0.71480226516723633 1 1;
	setAttr -s 12 ".koy[2:11]"  0 0 0 0.93698388338088989 0.97873491048812866 
		0.96998661756515503 0.95534074306488037 -0.69932663440704346 0 0;
createNode animCurveTA -n "animCurveTA890";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 2 0 5 0 7 0 11 0 18 5.1944745973390498 
		22 -42.957778470723092 27 -46.099785342431936 34 -47.992279315443625 36 -55.144898693340743 
		41 -55.144898693340743 43 -55.144898693340743;
	setAttr -s 12 ".kit[0:11]"  3 10 1 10 10 10 10 10 
		10 1 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 1 10 10 10 10 10 
		10 1 10 3;
	setAttr -s 12 ".kix[2:11]"  1 1 1 0.43932610750198364 0.31773540377616882 
		1 1 1 1 1;
	setAttr -s 12 ".kiy[2:11]"  0 0 0 -0.89832764863967896 -0.94817948341369629 
		0 0 0 0 0;
	setAttr -s 12 ".kox[2:11]"  1 1 1 0.43932610750198364 0.31773540377616882 
		1 1 1 1 1;
	setAttr -s 12 ".koy[2:11]"  0 0 0 -0.89832764863967896 -0.94817948341369629 
		0 0 0 0 0;
createNode animCurveTL -n "animCurveTL262";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 2 0 5 0 7 0 11 0 18 0.051002271902041763 
		22 0.1575876523378934 24 0.08427385300345025 29 0.19114583959061263 30 0.13085722794591531 
		34 0.42545525358378078 36 0.28499931203334922 41 0.28499931203334922 43 0.28499931203334922;
	setAttr -s 14 ".kit[0:13]"  3 10 1 10 10 10 10 10 
		10 10 10 1 1 3;
	setAttr -s 14 ".kot[0:13]"  3 10 1 10 10 10 10 10 
		10 10 10 1 1 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 0.91874098777770996 0.98644328117370605 
		0.98981547355651855 0.97393089532852173 0.57963156700134277 0.7920573353767395 1 
		1 1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0.3948606550693512 0.16410264372825623 
		0.14235608279705048 0.22684495151042938 0.81487870216369629 0.61044669151306152 0 
		0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 0.91874098777770996 0.98644328117370605 
		0.98981547355651855 0.97393089532852173 0.57963156700134277 0.7920573353767395 1 
		1 1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0.3948606550693512 0.16410264372825623 
		0.14235608279705048 0.22684495151042938 0.81487870216369629 0.61044669151306152 0 
		0 0;
createNode animCurveTL -n "animCurveTL263";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -0.64789329560123088 2 -0.64789329560123088 
		5 -0.64789329560123088 7 -0.64789329560123088 11 -0.64789329560123088 18 -0.66717844898079781 
		22 -0.87307017624687577 24 -0.82057826059931593 27 -0.70869487877302895 30 -0.62770047011280727 
		36 -0.71613731906619638 41 -0.71613731906619638 43 -0.71613731906619638;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 0.79347896575927734 0.71198403835296631 
		0.71980714797973633 0.99969244003295898 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 -0.60859769582748413 0.70219570398330688 
		0.69417411088943481 -0.02480049803853035 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 0.79347896575927734 0.71198403835296631 
		0.71980714797973633 0.99969244003295898 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 -0.60859769582748413 0.70219570398330688 
		0.69417411088943481 -0.02480049803853035 0 0 0;
createNode animCurveTL -n "animCurveTL264";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.07395615046270454 2 -0.07395615046270454 
		5 -0.07395615046270454 7 -0.07395615046270454 11 -0.07395615046270454 22 -0.23756082065896955 
		27 -0.23756082065896955 36 -0.36660946121094978 41 -0.36660946121094978 43 -0.36660946121094978;
	setAttr -s 10 ".kit[0:9]"  3 10 1 10 10 10 10 1 
		10 3;
	setAttr -s 10 ".kot[0:9]"  3 10 1 10 10 10 10 1 
		10 3;
	setAttr -s 10 ".kix[2:9]"  1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[2:9]"  0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[2:9]"  1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[2:9]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA891";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA892";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA893";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU275";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA894";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA895";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA896";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA897";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA898";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA899";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA900";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA901";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA902";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA903";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 -10.753373031419716 3 -1.9501433417389924 
		7 -3.4930039768760692 13 3.1866516484630991 17 26.487460942260185 22 63.122136094822707 
		25 49.730396792163383 27 34.679322952887169 29 4.2788837496943009 31 -16.212834398993351 
		36 -16.157540682017203 39 -16.073869818675245 41 -16.045966342123616 43 -16.073869818675245;
	setAttr -s 14 ".kit[0:13]"  9 3 3 9 10 10 10 3 
		2 1 3 1 10 3;
	setAttr -s 14 ".kot[0:13]"  9 3 3 9 10 10 10 3 
		2 1 3 1 10 3;
	setAttr -s 14 ".kix[9:13]"  1 1 1 1 1;
	setAttr -s 14 ".kiy[9:13]"  0 0 0 0 0;
	setAttr -s 14 ".kox[9:13]"  1 1 1 1 1;
	setAttr -s 14 ".koy[9:13]"  0 0 0 0 0;
createNode animCurveTA -n "animCurveTA904";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 -4.9387346018875373 3 -3.289382636640517 
		7 -8.483064876784514 13 -0.12793061430269645 17 1.98001588162076 22 5.2370863535559282 
		25 -0.46963600544740658 27 -1.5806743920788788 29 -4.1387254466452168 31 4.505741575475664 
		36 2.4206537381723527 39 2.4177732845622524 41 1.3826075793098094 43 2.4177732845622524;
	setAttr -s 14 ".kit[0:13]"  1 3 3 9 10 10 10 10 
		2 1 3 1 10 3;
	setAttr -s 14 ".kot[0:13]"  1 3 3 9 10 10 10 10 
		2 1 3 1 10 3;
	setAttr -s 14 ".kix[0:13]"  0.99994248151779175 1 1 0.87701249122619629 
		1 0.98738992214202881 1 1 0.83088672161102295 1 1 1 1 1;
	setAttr -s 14 ".kiy[0:13]"  0.01072579063475132 0 0 0.48046749830245972 
		0 -0.15830759704113007 0 0 -0.55644166469573975 0 0 0 0 0;
	setAttr -s 14 ".kox[0:13]"  0.99994248151779175 1 1 0.87701249122619629 
		1 0.98738992214202881 1 1 0.40417009592056274 1 1 1 1 1;
	setAttr -s 14 ".koy[0:13]"  0.010725787840783596 0 0 0.48046749830245972 
		0 -0.15830759704113007 0 0 0.91468387842178345 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA905";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 22.393157938684443 3 15.277115113179541 
		7 16.021771054001892 13 9.5210825970960862 17 7.7929386994385856 22 10.656273357677291 
		25 17.662255813920716 27 14.609241931695808 29 -0.37371957931212058 31 4.161139670371548 
		36 4.1302651563012738 39 4.9506292734258137 41 4.9360472669682061 43 4.9506292734258137;
	setAttr -s 14 ".kit[0:13]"  9 3 3 9 10 10 10 10 
		2 1 3 1 10 3;
	setAttr -s 14 ".kot[0:13]"  9 3 3 9 10 10 10 10 
		2 1 3 1 10 3;
	setAttr -s 14 ".kix[9:13]"  1 1 1 1 1;
	setAttr -s 14 ".kiy[9:13]"  0 0 0 0 0;
	setAttr -s 14 ".kox[9:13]"  1 1 1 1 1;
	setAttr -s 14 ".koy[9:13]"  0 0 0 0 0;
createNode animCurveTA -n "animCurveTA906";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 -4.0865779949808214 2 -4.0865779949808214 
		5 -4.0865779949808214 7 -4.0865779949808214 11 -4.0865779949808214 20 -3.0470501087705171 
		24 -4.233784871045394 27 -4.382923647190113 29 -23.809857541903298 31 -36.415035944177276 
		34 -7.987669708604427 37 -10.446824649845244 39 -4.969659574270616 41 -5.1422171466161615 
		43 -4.969659574270616;
	setAttr -s 15 ".kit[0:14]"  3 10 1 10 10 10 10 10 
		10 10 10 3 1 10 3;
	setAttr -s 15 ".kot[0:14]"  3 10 1 10 10 10 10 10 
		10 10 10 3 1 10 3;
	setAttr -s 15 ".kix[2:14]"  1 1 1 1 1 1 0.23198671638965607 0.51672154664993286 
		1 1 1 1 1;
	setAttr -s 15 ".kiy[2:14]"  0 0 0 0 0 0 -0.97271889448165894 0.85615348815917969 
		0 0 0 0 0;
	setAttr -s 15 ".kox[2:14]"  1 1 1 1 1 1 0.23198671638965607 0.51672154664993286 
		1 1 1 1 1;
	setAttr -s 15 ".koy[2:14]"  0 0 0 0 0 0 -0.97271889448165894 0.85615348815917969 
		0 0 0 0 0;
createNode animCurveTA -n "animCurveTA907";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 -10.471027640707172 2 -10.471027640707172 
		5 -10.471027640707172 7 -10.471027640707172 11 -10.471027640707172 20 5.7558044578069518 
		24 11.533551362638168 27 3.1451982112498791 29 -5.9973912503388505 31 -1.6126676676883687 
		34 0.19172349170582706 37 1.7572248406709525 39 3.307140364953407 41 4.3796538020587921 
		43 3.307140364953407;
	setAttr -s 15 ".kit[0:14]"  3 10 1 10 10 10 10 10 
		10 10 10 3 1 10 3;
	setAttr -s 15 ".kot[0:14]"  3 10 1 10 10 10 10 10 
		10 10 10 3 1 10 3;
	setAttr -s 15 ".kix[2:14]"  1 1 1 0.74838000535964966 0.98146271705627441 
		0.47834870219230652 0.848835289478302 1 1 1 1 1 1;
	setAttr -s 15 ".kiy[2:14]"  0 0 0 0.66327023506164551 -0.19165308773517609 
		-0.8781699538230896 -0.52865731716156006 0 0 0 0 0 0;
	setAttr -s 15 ".kox[2:14]"  1 1 1 0.74838000535964966 0.98146271705627441 
		0.47834870219230652 0.848835289478302 1 1 1 1 1 1;
	setAttr -s 15 ".koy[2:14]"  0 0 0 0.66327023506164551 -0.19165308773517609 
		-0.8781699538230896 -0.52865731716156006 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA908";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 -1.7475532445702493 2 -1.7475532445702493 
		5 -1.7475532445702493 7 -1.7475532445702493 11 -1.7475532445702493 20 -13.951724649456352 
		24 -8.6058460495458196 27 -0.73478923693706755 29 -13.825245030537978 31 -15.347450757353995 
		34 -10.94966024951434 37 -8.6627935757595331 39 -9.3051652115318486 41 -9.2115105989009667 
		43 -9.3051652115318486;
	setAttr -s 15 ".kit[0:14]"  3 10 1 10 10 10 10 10 
		10 10 10 3 1 10 3;
	setAttr -s 15 ".kot[0:14]"  3 10 1 10 10 10 10 10 
		10 10 10 3 1 10 3;
	setAttr -s 15 ".kix[2:14]"  1 1 1 0.9639015793800354 0.711139976978302 
		0.87748223543167114 1 1 1 1 1 1 1;
	setAttr -s 15 ".kiy[2:14]"  0 0 0 -0.26625880599021912 0.70305049419403076 
		-0.47960922122001648 0 0 0 0 0 0 0;
	setAttr -s 15 ".kox[2:14]"  1 1 1 0.9639015793800354 0.711139976978302 
		0.87748223543167114 1 1 1 1 1 1 1;
	setAttr -s 15 ".koy[2:14]"  0 0 0 -0.26625880599021912 0.70305049419403076 
		-0.47960922122001648 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU276";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1 22 1 27 1 31 1 36 1 39 1 41 1 43 1;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 1 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 1 10 3;
	setAttr -s 8 ".kix[5:7]"  1 1 1;
	setAttr -s 8 ".kiy[5:7]"  0 0 0;
	setAttr -s 8 ".kox[5:7]"  1 1 1;
	setAttr -s 8 ".koy[5:7]"  0 0 0;
createNode animCurveTA -n "animCurveTA909";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 20.69101533741409 2 19.370846453924266 
		6 9.0560252816530191 11 10.455182422399385 22 26.720921383756423 27 93.773500469510822 
		31 47.539979358323215 36 10.531344244448103 39 10.531344244448105 41 10.531344244448105 
		43 10.531344244448105;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 10 10 10 10 
		1 10 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 10 10 10 10 
		1 10 3;
	setAttr -s 11 ".kix[8:10]"  1 1 1;
	setAttr -s 11 ".kiy[8:10]"  0 0 0;
	setAttr -s 11 ".kox[8:10]"  1 1 1;
	setAttr -s 11 ".koy[8:10]"  0 0 0;
createNode animCurveTA -n "animCurveTA910";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -8.3978566024888135 2 -3.0736403927269054 
		6 -7.7147536688660479 11 -0.35546546933556694 22 -27.685350307991307 27 -50.930064467771132 
		31 -8.4942299013340126 36 -7.4833279264716541 39 -7.4833279264716541 41 -7.4833279264716541 
		43 -7.4833279264716541;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 10 10 10 10 
		1 10 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 10 10 10 10 
		1 10 3;
	setAttr -s 11 ".kix[8:10]"  1 1 1;
	setAttr -s 11 ".kiy[8:10]"  0 0 0;
	setAttr -s 11 ".kox[8:10]"  1 1 1;
	setAttr -s 11 ".koy[8:10]"  0 0 0;
createNode animCurveTA -n "animCurveTA911";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 2.8255796210686652 2 17.497718412413239 
		6 -11.861118069510525 11 -7.3162921599107866 22 7.1067160847574442 27 -12.581496134333229 
		31 -37.005779473144337 36 -17.681285493842925 39 -17.681285493842925 41 -17.681285493842925 
		43 -17.681285493842925;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 10 10 10 10 
		1 10 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 10 10 10 10 
		1 10 3;
	setAttr -s 11 ".kix[8:10]"  1 1 1;
	setAttr -s 11 ".kiy[8:10]"  0 0 0;
	setAttr -s 11 ".kox[8:10]"  1 1 1;
	setAttr -s 11 ".koy[8:10]"  0 0 0;
createNode animCurveTU -n "animCurveTU277";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 13 0 22 0 29 0 33 0 37 0 40 
		0 43 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 1 
		10 3;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 1 
		10 3;
	setAttr -s 10 ".kix[7:9]"  1 1 1;
	setAttr -s 10 ".kiy[7:9]"  0 0 0;
	setAttr -s 10 ".kox[7:9]"  1 1 1;
	setAttr -s 10 ".koy[7:9]"  0 0 0;
createNode animCurveTA -n "animCurveTA912";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 0 6 0 13 -4.3205113976013392 17 -1.9607446647988891 
		22 0 29 0 33 13.094291708401913 37 -4.2252149688204081 40 -6.4054203202216229 43 
		-9.2116702354819644;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 10 10 10 10 
		1 10 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 10 10 10 10 
		1 10 3;
	setAttr -s 11 ".kix[8:10]"  1 1 1;
	setAttr -s 11 ".kiy[8:10]"  0 0 0;
	setAttr -s 11 ".kox[8:10]"  1 1 1;
	setAttr -s 11 ".koy[8:10]"  0 0 0;
createNode animCurveTA -n "animCurveTA913";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 -38.697668698252727 6 9.7448467719793577 
		13 -20.457033068113887 17 -21.149396956236906 22 54.245558576568726 29 54.832328621439451 
		33 -48.179125025603966 37 13.273248218157088 40 -4.9866915541552608 43 5.4413291994513289;
	setAttr -s 11 ".kit[0:10]"  1 10 10 10 10 10 10 10 
		1 10 3;
	setAttr -s 11 ".kot[0:10]"  1 10 10 10 10 10 10 10 
		1 10 3;
	setAttr -s 11 ".kix[0:10]"  0.88959032297134399 0.76178956031799316 
		0.75509625673294067 1 1 1 1 0.34506171941757202 1 0.82559430599212646 1;
	setAttr -s 11 ".kiy[0:10]"  0.45675933361053467 0.64782452583312988 
		0.65561395883560181 0 0 0 0 -0.93858003616333008 0 -0.56426411867141724 0;
	setAttr -s 11 ".kox[0:10]"  0.88959026336669922 0.76178956031799316 
		0.75509625673294067 1 1 1 1 0.34506171941757202 1 0.82559430599212646 1;
	setAttr -s 11 ".koy[0:10]"  0.45675936341285706 0.64782452583312988 
		0.65561395883560181 0 0 0 0 -0.93858003616333008 0 -0.56426411867141724 0;
createNode animCurveTA -n "animCurveTA914";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 -0.040217693333277578 6 0 13 -9.5275322760031926 
		17 -4.4495429532871285 22 0 29 0 33 -3.4368573765476551 37 5.68046413269425 40 9.7670412053414104 
		43 2.796208942329399;
	setAttr -s 11 ".kit[0:10]"  1 10 10 10 10 10 10 10 
		1 10 3;
	setAttr -s 11 ".kot[0:10]"  1 10 10 10 10 10 10 10 
		1 10 3;
	setAttr -s 11 ".kix[0:10]"  0.99647122621536255 1 1 0.97829824686050415 
		0.87462699413299561 1 1 0.93731600046157837 1 0.96975356340408325 1;
	setAttr -s 11 ".kiy[0:10]"  -0.083934523165225983 0 0 -0.20720136165618896 
		0.4847964346408844 0 0 0.3484804630279541 0 -0.24408586323261261 0;
	setAttr -s 11 ".kox[0:10]"  0.99647122621536255 1 1 0.97829824686050415 
		0.87462699413299561 1 1 0.93731600046157837 1 0.96975356340408325 1;
	setAttr -s 11 ".koy[0:10]"  -0.083934500813484192 0 0 -0.20720136165618896 
		0.4847964346408844 0 0 0.3484804630279541 0 -0.24408586323261261 0;
createNode animCurveTA -n "animCurveTA915";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -17.821366541589882 2 -11.671852597761585 
		7 -14.50437399646696 11 -6.0101703605301058 18 12.035748206015478 22 33.892612983757729 
		27 31.239071247708324 30 11.034053214654882 38 -4.6150948459199999 41 -4.1196245503943016 
		43 -4.1196245503943016;
	setAttr -s 11 ".kit[0:10]"  9 10 10 10 10 10 10 10 
		10 1 3;
	setAttr -s 11 ".kot[0:10]"  9 10 10 10 10 10 10 10 
		10 1 3;
	setAttr -s 11 ".kix[9:10]"  1 1;
	setAttr -s 11 ".kiy[9:10]"  0 0;
	setAttr -s 11 ".kox[9:10]"  1 1;
	setAttr -s 11 ".koy[9:10]"  0 0;
createNode animCurveTA -n "animCurveTA916";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -12.005893876475762 2 -6.7408197492938706 
		7 -5.0283404610664526 11 -17.580885260959082 18 -19.619298533883871 22 -8.4317036797661746 
		27 0.99544799754471114 30 -33.371100952127954 38 0.97539430298761376 41 2.2991831572848676 
		43 2.2991831572848676;
	setAttr -s 11 ".kit[0:10]"  1 10 10 10 10 10 10 10 
		10 1 3;
	setAttr -s 11 ".kot[0:10]"  1 10 10 10 10 10 10 10 
		10 1 3;
	setAttr -s 11 ".kix[0:10]"  0.99992233514785767 1 1 1 1 0.64039933681488037 
		0.52239888906478882 0.9999995231628418 1 1 1;
	setAttr -s 11 ".kiy[0:10]"  0.012462018989026546 0 0 0 0 0.76804214715957642 
		-0.85270124673843384 -0.00095455313567072153 0 0 0;
	setAttr -s 11 ".kox[0:10]"  0.99992233514785767 1 1 1 1 0.64039933681488037 
		0.52239888906478882 0.9999995231628418 1 1 1;
	setAttr -s 11 ".koy[0:10]"  0.012462020851671696 0 0 0 0 0.76804214715957642 
		-0.85270124673843384 -0.00095455313567072153 0 0 0;
createNode animCurveTA -n "animCurveTA917";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 9.1378572146953019 2 -2.0453944477329813 
		7 -10.77827645840617 11 5.6945658954933469 18 21.788577954088609 22 52.01505151978774 
		27 -28.333939775630359 30 -5.7191023542392019 38 17.363421244612265 41 0.15403097959161099 
		43 0.15403097959161099;
	setAttr -s 11 ".kit[0:10]"  9 10 10 10 10 10 10 10 
		10 1 3;
	setAttr -s 11 ".kot[0:10]"  9 10 10 10 10 10 10 10 
		10 1 3;
	setAttr -s 11 ".kix[9:10]"  1 1;
	setAttr -s 11 ".kiy[9:10]"  0 0;
	setAttr -s 11 ".kox[9:10]"  1 1;
	setAttr -s 11 ".koy[9:10]"  0 0;
createNode animCurveTA -n "animCurveTA918";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 -28.841216077843235 2 -30.3906038112383 
		7 -22.570624878775188 11 -28.841216077843235 14 -20.026496077093654 18 -23.180383444590479 
		22 -28.841216077843235 25 -24.008693651880399 27 -28.841216077843235 31 1.5151481545731806 
		33 -84.398236930885062 37 -6.3840644964629387 41 -0.11407960717252776 43 -12.982174266974598;
	setAttr -s 14 ".kit[0:13]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 3;
	setAttr -s 14 ".kot[0:13]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA919";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 -21.716766331039956 2 -39.452370685293154 
		7 -10.354235073606064 11 -21.716766331039956 14 -12.963259120166652 18 -20.289478423552499 
		22 -21.716766331039956 25 -44.36843490152593 27 -21.716766331039956 31 31.191365015309412 
		33 -57.265311059099979 37 7.6263655980249352 41 -12.542254372710177 43 -0.26540937236918372;
	setAttr -s 14 ".kit[0:13]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 3;
	setAttr -s 14 ".kot[0:13]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA920";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 23.535235892507558 2 -6.0323019171427736 
		7 46.295157241968703 11 23.535235892507558 14 -8.7757967796097311 18 -25.051397476879185 
		22 23.535235892507558 25 -6.7016955664394269 27 23.535235892507558 31 -34.956359842192484 
		33 14.055892122416974 37 56.028971605089104 41 -6.5781306422509971 43 -4.0728754508485201;
	setAttr -s 14 ".kit[0:13]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 3;
	setAttr -s 14 ".kot[0:13]"  9 10 10 10 10 10 10 10 
		10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL265";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 0 7 0 11 0 25 0 29 0 33 0 35 0 37 
		0 41 0.034032333595854232 43 0.034032333595854232;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 10 10 10 10 
		10 1 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 10 10 10 10 
		10 1 3;
	setAttr -s 11 ".kix[9:10]"  1 1;
	setAttr -s 11 ".kiy[9:10]"  0 0;
	setAttr -s 11 ".kox[9:10]"  1 1;
	setAttr -s 11 ".koy[9:10]"  0 0;
createNode animCurveTL -n "animCurveTL266";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 2 0 7 0 11 0 22 0 25 0 27 0 31 0 33 
		0 37 0 41 -0.075138079758700294 43 -0.075138079758700294;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 3;
createNode animCurveTL -n "animCurveTL267";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 2 0 7 0 11 0 22 0 25 0 27 0 31 0 33 
		0 37 0 41 0.013968752667852061 43 0.013968752667852061;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 3;
createNode animCurveTU -n "animCurveTU278";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 2 2 2 5 2 7 2 11 2 12 0 21 0 37 0 40 
		0 41 0 43 0;
	setAttr -s 11 ".kit[0:10]"  3 9 1 9 9 9 9 9 
		1 9 3;
	setAttr -s 11 ".kot[0:10]"  3 5 5 5 5 5 5 5 
		5 5 3;
	setAttr -s 11 ".kix[2:10]"  1 1 0.083045482635498047 0.16439896821975708 
		1 1 1 1 1;
	setAttr -s 11 ".kiy[2:10]"  0 0 -0.99654579162597656 -0.98639386892318726 
		0 0 0 0 0;
createNode animCurveTU -n "animCurveTU279";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 0 5 0 7 0 11 0 12 1 21 1 37 1 40 
		1 41 1 43 1;
	setAttr -s 11 ".kit[0:10]"  3 9 1 9 9 9 9 9 
		1 9 3;
	setAttr -s 11 ".kot[0:10]"  3 5 5 5 5 5 5 5 
		5 5 3;
	setAttr -s 11 ".kix[2:10]"  1 1 0.16439898312091827 0.31622773408889771 
		1 1 1 1 1;
	setAttr -s 11 ".kiy[2:10]"  0 0 0.98639386892318726 0.94868326187133789 
		0 0 0 0 0;
createNode animCurveTA -n "animCurveTA921";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -24.093441664171177 2 -24.093441664171177 
		5 -24.093441664171177 7 -24.093441664171177 11 -24.093441664171177 12 -52.321484593807895 
		21 -52.321484593807895 37 -52.321484593807895 40 -52.321484593807895 41 -52.321484593807895 
		43 -52.321484593807895;
	setAttr -s 11 ".kit[0:10]"  3 10 1 10 10 10 10 10 
		1 10 3;
	setAttr -s 11 ".kot[0:10]"  3 10 1 10 10 10 10 10 
		1 10 3;
	setAttr -s 11 ".kix[2:10]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[2:10]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[2:10]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[2:10]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA922";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 49.48465546224881 2 49.48465546224881 
		5 49.48465546224881 7 49.48465546224881 11 49.48465546224881 12 8.5937642825728489 
		21 8.5937642825728489 37 8.5937642825728489 40 8.5937642825728489 41 8.5937642825728489 
		43 8.5937642825728489;
	setAttr -s 11 ".kit[0:10]"  3 10 1 10 10 10 10 10 
		1 10 3;
	setAttr -s 11 ".kot[0:10]"  3 10 1 10 10 10 10 10 
		1 10 3;
	setAttr -s 11 ".kix[2:10]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[2:10]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[2:10]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[2:10]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA923";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 58.801792680015588 2 58.801792680015588 
		5 58.801792680015588 7 58.801792680015588 11 58.801792680015588 12 -21.088438783874015 
		21 -21.088438783874015 37 -21.088438783874015 40 -21.088438783874015 41 -21.088438783874015 
		43 -21.088438783874015;
	setAttr -s 11 ".kit[0:10]"  3 10 1 10 10 10 10 10 
		1 10 3;
	setAttr -s 11 ".kot[0:10]"  3 10 1 10 10 10 10 10 
		1 10 3;
	setAttr -s 11 ".kix[2:10]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[2:10]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[2:10]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[2:10]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL268";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 -1.2755255474500937 2 -1.2755255474500937 
		5 -1.2755255474500937 7 -1.2755255474500937 11 -1.2755255474500937 12 -0.41309954139648486 
		21 -0.27540553727249184 24 -0.24990663546108083 31 -1.3934113079851751 34 -3.379562486007047 
		37 -2.8496477520209873 40 -3.4408568588645028 41 -3.4408568588645028 43 -3.4408568588645028;
	setAttr -s 14 ".kit[0:13]"  3 10 1 10 10 3 10 3 
		10 10 10 1 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 1 10 10 3 10 3 
		10 10 10 1 10 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 1 1 1 0.10590896010398865 0.13606312870979309 
		0.95610642433166504 1 1 1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0 0 0 -0.99437588453292847 -0.99070018529891968 
		-0.29301965236663818 0 0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 1 1 1 0.10590896010398865 0.13606312870979309 
		0.95610642433166504 1 1 1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0 0 0 -0.99437588453292847 -0.99070018529891968 
		-0.29301965236663818 0 0 0;
createNode animCurveTL -n "animCurveTL269";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 -1.4392043230118035 2 -1.4392043230118035 
		5 -1.4392043230118035 7 -1.4392043230118035 11 -1.4392043230118035 12 0.7641291910128577 
		21 0.89787825379791597 24 0.92264661056858066 31 1.6310018239502422 34 1.9821985597814316 
		37 1.8700066586115762 40 1.9202745337806841 41 1.9202745337806841 43 1.9202745337806841;
	setAttr -s 14 ".kit[0:13]"  3 10 1 10 10 3 10 3 
		10 10 10 1 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 1 10 10 3 10 3 
		10 10 10 1 10 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 1 1 1 0.3000980019569397 0.64175361394882202 
		0.95525985956192017 1 1 1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0 0 0 0.95390838384628296 0.76691091060638428 
		-0.29576760530471802 0 0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 1 1 1 0.3000980019569397 0.64175361394882202 
		0.95525985956192017 1 1 1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0 0 0 0.95390838384628296 0.76691091060638428 
		-0.29576760530471802 0 0 0;
createNode animCurveTL -n "animCurveTL270";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 -2.1802956492995231 2 -2.1802956492995231 
		5 -2.1802956492995231 7 -2.1802956492995231 11 -2.1802956492995231 12 -1.4457621118326656 
		16 -1.6660965080147629 21 -1.9283648037499141 24 -2.0598573016764239 31 -2.2150400231899341 
		37 -2.3526783752957412 40 -2.4856083032861362 41 -2.4856083032861362 43 -2.4856083032861362;
	setAttr -s 14 ".kit[0:13]"  3 10 1 10 10 3 10 10 
		10 10 10 1 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 1 10 10 3 10 10 
		10 10 10 1 10 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 1 0.5279388427734375 0.56074070930480957 
		0.75817561149597168 0.82856392860412598 0.74259436130523682 1 1 1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0 -0.84928244352340698 -0.82799148559570313 
		-0.65205049514770508 -0.55989456176757813 -0.66974139213562012 0 0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 1 0.5279388427734375 0.56074070930480957 
		0.75817561149597168 0.82856392860412598 0.74259436130523682 1 1 1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0 -0.84928244352340698 -0.82799148559570313 
		-0.65205049514770508 -0.55989456176757813 -0.66974139213562012 0 0 0;
createNode animCurveTL -n "animCurveTL271";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 2 0 5 0 7 0 11 0 12 0.35060762232809523 
		19 -1.8724184444218386 26 -0.63255090421126503 31 -2.4651609918089581 38 -2.9120595891102359 
		39 -0.83418581521766288 40 -2.5132919537062337 41 -2.5132919537062337 43 -2.5132919537062337;
	setAttr -s 14 ".kit[0:13]"  3 10 1 10 10 10 10 10 
		1 10 10 10 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 1 10 10 10 10 10 
		1 10 10 10 10 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 0.1409955620765686 0.42880663275718689 
		0.5593755841255188 0.32041081786155701 0.16135880351066589 0.16489338874816895 1 
		1 1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 -0.99001020193099976 -0.90339624881744385 
		-0.8289143443107605 0.94727867841720581 0.98689579963684082 0.98631137609481812 0 
		0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 0.1409955620765686 0.42880663275718689 
		0.5593755841255188 0.32041081786155701 0.16135880351066589 0.16489338874816895 1 
		1 1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 -0.99001020193099976 -0.90339624881744385 
		-0.8289143443107605 0.94727867841720581 0.98689579963684082 0.98631137609481812 0 
		0 0;
createNode animCurveTL -n "animCurveTL272";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 0 2 0 5 0 7 0 11 0 12 1.1119197873898803 
		19 -0.54142364148731237 26 -0.54459682733908166 31 1.6275889063555564 36 0 38 1.3429169806325854 
		39 -0.8851395649760152 40 1.4798279141623796 41 1.4798279141623796 43 1.4798279141623796;
	setAttr -s 15 ".kit[0:14]"  3 10 1 10 10 10 10 10 
		1 10 10 1 10 10 3;
	setAttr -s 15 ".kot[0:14]"  3 10 1 10 10 10 10 10 
		1 10 10 1 10 10 3;
	setAttr -s 15 ".kix[2:14]"  1 1 1 0.44184356927871704 1 1 1 0.63392096757888794 
		0.11226224899291992 1 1 1 1;
	setAttr -s 15 ".kiy[2:14]"  0 0 0 -0.89709216356277466 0 0 0 -0.77339786291122437 
		-0.99367856979370117 0 0 0 0;
	setAttr -s 15 ".kox[2:14]"  1 1 1 0.44184356927871704 1 1 1 0.63392096757888794 
		0.11226224899291992 1 1 1 1;
	setAttr -s 15 ".koy[2:14]"  0 0 0 -0.89709216356277466 0 0 0 -0.77339786291122437 
		-0.99367856979370117 0 0 0 0;
createNode animCurveTL -n "animCurveTL273";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 0 2 0 5 0 7 0 11 0 12 -1.1757420118712054 
		19 -4.6223040959931261 26 -3.8649308299104637 31 -4.7866673013523231 36 0 38 -0.91834101202999896 
		39 0.6107516333690467 40 0.91162690534037627 41 0.91162690534037627 43 0.91162690534037627;
	setAttr -s 15 ".kit[0:14]"  3 10 1 10 10 10 10 10 
		1 10 10 1 10 10 3;
	setAttr -s 15 ".kot[0:14]"  3 10 1 10 10 10 10 10 
		1 10 10 1 10 10 3;
	setAttr -s 15 ".kix[2:14]"  1 1 1 0.057595513761043549 0.17097900807857513 
		0.9249567985534668 0.12168300151824951 0.060209505259990692 0.16158097982406616 1 
		1 1 1;
	setAttr -s 15 ".kiy[2:14]"  0 0 0 -0.99834001064300537 -0.98527461290359497 
		-0.38007217645645142 0.9925689697265625 0.99818575382232666 0.98685944080352783 0 
		0 0 0;
	setAttr -s 15 ".kox[2:14]"  1 1 1 0.057595513761043549 0.17097900807857513 
		0.9249567985534668 0.12168300151824951 0.060209505259990692 0.16158097982406616 1 
		1 1 1;
	setAttr -s 15 ".koy[2:14]"  0 0 0 -0.99834001064300537 -0.98527461290359497 
		-0.38007217645645142 0.9925689697265625 0.99818575382232666 0.98685944080352783 0 
		0 0 0;
createNode animCurveTA -n "animCurveTA924";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 1.1134085745786892 2 -49.956490649992304 
		11 1.1134085745786892 18 9.7885105392082785 22 -32.38556373810524 26 -33.607842421450584 
		30 0.99877194271770731 34 -7.6328842698500976 37 -20.207369288361946 39 -8.4510912821832136 
		41 -8.4510912821832136 43 -8.4510912821832136;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 10 10 10 
		10 3 3 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 10 10 10 
		10 3 3 3;
createNode animCurveTA -n "animCurveTA925";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -5.3180374758492821 2 9.9845784805651263 
		11 -5.3180374758492821 18 26.612471479278689 22 0.08537301592392095 26 46.020321525584833 
		30 -19.739216140471292 34 1.2990383542316108 37 61.167592333154026 39 61.748948197518338 
		41 61.748948197518338 43 61.748948197518338;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 10 10 10 
		10 3 3 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 10 10 10 
		10 3 3 3;
createNode animCurveTA -n "animCurveTA926";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 7.8609313736722894 2 -4.9986996946561693 
		11 7.8609313736722894 18 -33.853151849103128 22 -60.837281516687206 26 -28.747315648229669 
		30 -26.09748678288237 34 -48.98642043949215 37 18.59939877897985 39 51.243086590018478 
		41 51.243086590018478 43 51.243086590018478;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 10 10 10 
		10 3 3 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 10 10 10 
		10 3 3 3;
createNode animCurveTL -n "animCurveTL274";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 11 0.034326427149150185 39 0 41 
		0 43 0;
	setAttr -s 6 ".kit[1:5]"  10 10 3 3 3;
	setAttr -s 6 ".kot[1:5]"  10 10 3 3 3;
createNode animCurveTL -n "animCurveTL275";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 11 -0.016889486596713646 22 0 39 
		0 41 0 43 0;
	setAttr -s 7 ".kit[1:6]"  10 10 10 3 3 3;
	setAttr -s 7 ".kot[1:6]"  10 10 10 3 3 3;
createNode animCurveTL -n "animCurveTL276";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 11 -0.070446646393842294 22 0 39 
		0 41 0 43 0;
	setAttr -s 7 ".kit[1:6]"  10 10 10 3 3 3;
	setAttr -s 7 ".kot[1:6]"  10 10 10 3 3 3;
createNode animCurveTA -n "animCurveTA927";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 2 0 5 0 7 0 11 0 12 4.5050410775003025 
		21 0.70391295156557465 24 0 37 0 40 0 41 0 43 0;
	setAttr -s 12 ".kit[0:11]"  3 10 1 10 10 10 10 10 
		10 1 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 1 10 10 10 10 10 
		10 1 10 3;
	setAttr -s 12 ".kix[2:11]"  1 1 1 0.99932146072387695 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[2:11]"  0 0 0 0.036831788718700409 0 0 0 0 0 0;
	setAttr -s 12 ".kox[2:11]"  1 1 1 0.99932146072387695 1 1 1 1 1 1;
	setAttr -s 12 ".koy[2:11]"  0 0 0 0.036831788718700409 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA928";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 2 0 5 0 7 0 11 0 12 33.868884127673738 
		21 5.292015274091951 24 0 37 0 40 0 41 0 43 0;
	setAttr -s 12 ".kit[0:11]"  3 10 1 10 10 10 10 10 
		10 1 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 1 10 10 10 10 10 
		10 1 10 3;
	setAttr -s 12 ".kix[2:11]"  1 1 1 0.96368873119354248 0.56042689085006714 
		1 1 1 1 1;
	setAttr -s 12 ".kiy[2:11]"  0 0 0 0.26702782511711121 -0.82820385694503784 
		0 0 0 0 0;
	setAttr -s 12 ".kox[2:11]"  1 1 1 0.96368873119354248 0.56042689085006714 
		1 1 1 1 1;
	setAttr -s 12 ".koy[2:11]"  0 0 0 0.26702782511711121 -0.82820385694503784 
		0 0 0 0 0;
createNode animCurveTA -n "animCurveTA929";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 2 0 5 0 7 0 11 0 12 -9.5637700017372893 
		21 -1.4943396639909408 24 0 37 0 40 0 41 0 43 0;
	setAttr -s 12 ".kit[0:11]"  3 10 1 10 10 10 10 10 
		10 1 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 1 10 10 10 10 10 
		10 1 10 3;
	setAttr -s 12 ".kix[2:11]"  1 1 1 0.99695301055908203 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[2:11]"  0 0 0 -0.078005045652389526 0 0 0 0 0 0;
	setAttr -s 12 ".kox[2:11]"  1 1 1 0.99695301055908203 1 1 1 1 1 1;
	setAttr -s 12 ".koy[2:11]"  0 0 0 -0.078005045652389526 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL277";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 2 0 5 0 7 0 11 0 12 -0.024101501434020636 
		21 -0.13503471528358671 24 -0.017769670228858558 31 0.34786381507796627 34 0.52756514830385015 
		37 -0.062199781610524418 40 0.05214260611272481 41 0.05214260611272481 43 0.05214260611272481;
	setAttr -s 14 ".kit[0:13]"  3 10 1 10 10 10 10 10 
		10 10 10 1 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 1 10 10 10 10 10 
		10 10 10 1 10 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 1 0.99987471103668213 0.56807917356491089 
		0.5215333104133606 0.43836876749992371 0.38776406645774841 0.27987185120582581 1 
		1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0 0.015827594324946404 0.82297384738922119 
		0.85323089361190796 -0.89879518747329712 -0.92175871133804321 0.96003735065460205 
		0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 1 0.99987471103668213 0.56807917356491089 
		0.5215333104133606 0.43836876749992371 0.38776406645774841 0.27987188100814819 1 
		1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0 0.015827594324946404 0.82297384738922119 
		0.85323089361190796 -0.89879518747329712 -0.92175871133804321 0.96003741025924683 
		0 0;
createNode animCurveTL -n "animCurveTL278";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 2 0 5 0 7 0 11 0 12 -0.14144317574744722 
		21 -0.15928692410019191 24 -0.14106001773906729 31 -1.2876505597516175 34 -1.5005364031219892 
		37 -1.6127283042918445 40 -1.6464702716018644 41 -1.6464702716018644 43 -1.6464702716018644;
	setAttr -s 14 ".kit[0:13]"  3 10 1 10 10 10 10 10 
		10 10 10 1 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 1 10 10 10 10 10 
		10 10 10 1 10 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 1 1 1 0.23813854157924652 0.52400660514831543 
		1 1 1 1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0 0 0 -0.97123116254806519 -0.85171419382095337 
		0 0 0 0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 1 1 1 0.23813854157924652 0.52400660514831543 
		1 1 1 1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0 0 0 -0.97123116254806519 -0.85171419382095337 
		0 0 0 0;
createNode animCurveTL -n "animCurveTL279";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 2 0 5 0 7 0 11 0 12 -2.7491488405452937 
		16 -2.4365637224626329 21 -2.4617776863308709 24 -2.3266172393437126 31 -1.6771937166650224 
		37 -1.6771937166650224 40 -1.6771937166650224 41 -1.6771937166650224 43 -1.6771937166650224;
	setAttr -s 14 ".kit[0:13]"  3 10 1 10 10 3 10 10 
		10 10 10 1 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 1 10 10 3 10 10 
		10 10 10 1 10 3;
	setAttr -s 14 ".kix[2:13]"  1 1 1 1 1 1 0.39102646708488464 1 1 1 1 
		1;
	setAttr -s 14 ".kiy[2:13]"  0 0 0 0 0 0 0.9203794002532959 0 0 0 0 
		0;
	setAttr -s 14 ".kox[2:13]"  1 1 1 1 1 1 0.39102646708488464 1 1 1 1 
		1;
	setAttr -s 14 ".koy[2:13]"  0 0 0 0 0 0 0.9203794002532959 0 0 0 0 
		0;
createNode animCurveTU -n "animCurveTU280";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 9 1 9 9 9 9 9 
		9 9 1 9 3;
	setAttr -s 13 ".kot[0:12]"  3 5 5 5 5 5 5 5 
		5 5 5 5 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA930";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -5.1107219305963252 2 -5.1107219305963252 
		5 -5.1107219305963252 7 -5.1107219305963252 11 -5.1107219305963252 22 -5.1107219305963252 
		27 -5.1107219305963252 31 -5.1107219305963252 33 -5.1107219305963252 36 -5.1107219305963252 
		39 -5.1107219305963252 41 -5.1107219305963252 43 -5.1107219305963252;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA931";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 8.2811672786141717 2 8.2811672786141717 
		5 8.2811672786141717 7 8.2811672786141717 11 8.2811672786141717 22 8.2811672786141717 
		27 8.2811672786141717 31 8.2811672786141717 33 8.2811672786141717 36 8.2811672786141717 
		39 8.2811672786141717 41 8.2811672786141717 43 8.2811672786141717;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA932";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -0.92645454014921158 2 -0.92645454014921158 
		5 -0.92645454014921158 7 -0.92645454014921158 11 -0.92645454014921158 22 -0.92645454014921158 
		27 -0.92645454014921158 31 -0.92645454014921158 33 -0.92645454014921158 36 -0.92645454014921158 
		39 -0.92645454014921158 41 -0.92645454014921158 43 -0.92645454014921158;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL280";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -0.046856395845859107 2 -0.046856395845859107 
		5 -0.046856395845859107 7 -0.046856395845859107 11 -0.046856395845859107 24 -0.046856395845859107 
		29 -0.046856395845859107 33 -0.046856395845859107 35 -0.046856395845859107 38 -0.046856395845859107 
		41 -0.046856395845859107 43 -0.046856395845859107;
	setAttr -s 12 ".kit[0:11]"  3 10 1 10 10 10 10 10 
		10 10 1 3;
	setAttr -s 12 ".kot[0:11]"  3 10 1 10 10 10 10 10 
		10 10 1 3;
	setAttr -s 12 ".kix[2:11]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[2:11]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[2:11]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[2:11]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL281";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -0.023348763690700665 2 -0.023348763690700665 
		5 -0.023348763690700665 7 -0.023348763690700665 11 -0.023348763690700665 22 -0.023348763690700665 
		27 -0.023348763690700665 31 -0.023348763690700665 33 -0.023348763690700665 36 -0.023348763690700665 
		39 -0.023348763690700665 41 -0.023348763690700665 43 -0.023348763690700665;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL282";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -0.13506113021862395 2 -0.13506113021862395 
		5 -0.13506113021862395 7 -0.13506113021862395 11 -0.13506113021862395 22 -0.13506113021862395 
		27 -0.13506113021862395 31 -0.13506113021862395 33 -0.13506113021862395 36 -0.13506113021862395 
		39 -0.13506113021862395 41 -0.13506113021862395 43 -0.13506113021862395;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA933";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -1.6266160090263075 4 4.3762291879362918 
		7 -1.6266160090263075 11 -8.5604328817963946 19 6.2949562891596349 22 3.9105488644150754 
		27 -21.717579157327922 29 18.110156755604567 31 9.9330547820837989 36 -1.6266160090263075 
		39 -24.695480030754066 41 -24.695480030754066 43 -24.695480030754066;
	setAttr -s 13 ".kit[0:12]"  9 10 10 10 10 10 10 10 
		10 3 3 3 3;
	setAttr -s 13 ".kot[0:12]"  9 10 10 10 10 10 10 10 
		10 3 3 3 3;
createNode animCurveTA -n "animCurveTA934";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 2.8499857758927387 4 -11.947396327301574 
		7 2.8499857758927387 11 -0.42900285088281281 19 -16.70871807024724 22 -8.8474814316853454 
		27 35.755816256285307 29 16.038618118834471 31 -14.293070655379493 36 2.8499857758927387 
		39 -0.88087303619030455 41 -0.88087303619030455 43 -0.88087303619030455;
	setAttr -s 13 ".kit[0:12]"  9 10 10 10 10 10 10 10 
		10 3 3 3 3;
	setAttr -s 13 ".kot[0:12]"  9 10 10 10 10 10 10 10 
		10 3 3 3 3;
createNode animCurveTA -n "animCurveTA935";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -25.210898828531619 4 -22.627470100618694 
		7 -25.210898828531619 11 -25.357618122616444 19 -26.4122287402983 22 -25.502312825299821 
		27 -85.058781465336139 29 -5.6365568691084151 31 -3.6881215966514915 36 -25.210898828531619 
		39 -11.675517548240952 41 -11.675517548240952 43 -11.675517548240952;
	setAttr -s 13 ".kit[0:12]"  1 10 10 10 10 10 10 10 
		10 3 3 3 3;
	setAttr -s 13 ".kot[0:12]"  1 10 10 10 10 10 10 10 
		10 3 3 3 3;
	setAttr -s 13 ".kix[0:12]"  0.99530422687530518 1 1 1 1 1 0.55831402540206909 
		1 1 1 1 1 1;
	setAttr -s 13 ".kiy[0:12]"  0.09679567813873291 0 0 0 0 0 0.82962971925735474 
		0 0 0 0 0 0;
	setAttr -s 13 ".kox[0:12]"  0.99530422687530518 1 1 1 1 1 0.55831402540206909 
		1 1 1 1 1 1;
	setAttr -s 13 ".koy[0:12]"  0.09679567813873291 0 0 0 0 0 0.82962971925735474 
		0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL283";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -0.011193700785458628 7 -0.011193700785458628 
		11 -0.010821820825551123 19 0.092653893203967982 22 0.15099465174860291 24 -0.011193700785458628 
		27 -0.13862010084824025 29 -0.061447156161854616 31 0.053792744637790199 35 -0.011193700785458628 
		39 -0.011193700785458628 41 -0.011193700785458628 43 -0.011193700785458628;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 10 10 10 10 
		10 10 3 3 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 10 10 10 10 
		10 10 3 3 3;
createNode animCurveTL -n "animCurveTL284";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -0.020021267836214246 7 -0.020021267836214246 
		11 -0.077782796424982106 19 0.023462770283230003 22 0.011402695551952721 27 0.60808172351333079 
		29 0.3772297271841929 31 0.14339750662000017 36 -0.020021267836214246 39 -0.020021267836214246 
		41 -0.020021267836214246 43 -0.020021267836214246;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 10 10 10 
		3 3 3 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 10 10 10 
		3 3 3 3;
createNode animCurveTL -n "animCurveTL285";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0.032441787830836878 7 0.032441787830836878 
		11 0.029195032129103196 19 0.027218275821967893 22 -0.0069884129500235913 27 -0.18931366296582797 
		29 0.071041713023565572 31 0.083688839334120302 36 0.032441787830836878 39 0.032441787830836878 
		41 0.032441787830836878 43 0.032441787830836878;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 10 10 10 
		3 3 3 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 10 10 10 
		3 3 3 3;
createNode animCurveTA -n "animCurveTA936";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA937";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA938";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL286";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 2 0 5 0 7 0 11 0 24 0 29 0 33 0 35 
		0 38 0 41 0 43 0;
	setAttr -s 12 ".kit[0:11]"  3 10 1 10 10 10 10 10 
		10 10 1 3;
	setAttr -s 12 ".kot[0:11]"  3 10 1 10 10 10 10 10 
		10 10 1 3;
	setAttr -s 12 ".kix[2:11]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[2:11]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[2:11]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[2:11]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL287";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL288";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA939";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -15.609971163878811 2 -15.455599994012509 
		7 -6.9560643263625623 12 13.70373319501044 20 38.496681718694433 24 62.15226140439713 
		27 83.664929871511731 30 111.98298640932396 32 115.46063607376848 36 115.46063607376848 
		39 115.46063607376848 41 115.46063607376848 43 115.46063607376848;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 10 10 2 10 
		10 3 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 10 10 2 10 
		10 3 1 10 3;
	setAttr -s 13 ".kix[10:12]"  1 1 1;
	setAttr -s 13 ".kiy[10:12]"  0 0 0;
	setAttr -s 13 ".kox[10:12]"  1 1 1;
	setAttr -s 13 ".koy[10:12]"  0 0 0;
createNode animCurveTA -n "animCurveTA940";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 8.3116042646716988 2 6.4358943453436757 
		7 4.1205254354134144 12 0.88357860527548293 20 -2.4421304790086351 24 -4.0948577229896976 
		27 -5.7761503741531044 30 57.478923230774548 32 65.247075905024715 36 65.247075905024715 
		39 65.247075905024715 41 65.247075905024715 43 65.247075905024715;
	setAttr -s 13 ".kit[0:12]"  9 10 10 10 10 10 2 10 
		10 3 1 10 3;
	setAttr -s 13 ".kot[0:12]"  9 10 10 10 10 10 2 10 
		10 3 1 10 3;
	setAttr -s 13 ".kix[10:12]"  1 1 1;
	setAttr -s 13 ".kiy[10:12]"  0 0 0;
	setAttr -s 13 ".kox[10:12]"  1 1 1;
	setAttr -s 13 ".koy[10:12]"  0 0 0;
createNode animCurveTA -n "animCurveTA941";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 14.458598883932659 2 3.0514890951498281 
		7 2.8966861189025908 12 2.6802674734287222 20 -14.930997816042733 24 -45.263999405906617 
		27 -73.093652617886022 30 -91.47209854221758 32 -93.729096469771903 36 -93.729096469771903 
		39 -93.729096469771903 41 -93.729096469771903 43 -93.729096469771903;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 10 10 2 10 
		10 1 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 10 10 2 10 
		10 1 1 10 3;
	setAttr -s 13 ".kix[9:12]"  1 1 1 1;
	setAttr -s 13 ".kiy[9:12]"  0 0 0 0;
	setAttr -s 13 ".kox[9:12]"  1 1 1 1;
	setAttr -s 13 ".koy[9:12]"  0 0 0 0;
createNode animCurveTL -n "animCurveTL289";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 -0.18868131369562219 2 -0.14784983232755539 
		7 -0.16005597490898307 12 -0.20924849421780412 20 -0.81110032648432839 24 -1.249765647274889 
		27 -1.7360947324430083 30 -1.6140060590125904 32 -1.6789541044234086 36 -1.6789541044234086 
		38 -1.6746102093271555 39 -1.6746102093271555 41 -1.6746102093271555 43 -1.6746102093271555;
	setAttr -s 14 ".kit[0:13]"  3 10 10 1 10 10 2 10 
		10 10 1 1 1 3;
	setAttr -s 14 ".kot[0:13]"  3 10 10 1 10 10 2 10 
		10 10 1 1 1 3;
	setAttr -s 14 ".kix[3:13]"  0.9262387752532959 0.35882365703582764 
		0.24459181725978851 0.20140828192234039 0.94594991207122803 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[3:13]"  -0.37693729996681213 -0.93340539932250977 
		-0.96962618827819824 -0.97950738668441772 0.32431286573410034 0 0 0 0 0 0;
	setAttr -s 14 ".kox[3:13]"  0.92623883485794067 0.35882365703582764 
		0.24459181725978851 0.63365256786346436 0.94594991207122803 1 1 1 1 1 1;
	setAttr -s 14 ".koy[3:13]"  -0.3769371509552002 -0.93340539932250977 
		-0.96962618827819824 0.77361780405044556 0.32431286573410034 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL290";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0.23059098815955009 2 0.12309789283836045 
		7 0.12660638347472514 12 0.21898584865553794 20 0.76211351148269102 24 0.86518391420805774 
		27 1.2363590465901562 30 1.3849645123573828 32 1.3952869159970382 36 1.3952869159970382 
		39 1.3952869159970382 41 1.3952869159970382 43 1.3952869159970382;
	setAttr -s 13 ".kit[0:12]"  1 10 10 10 10 10 2 10 
		10 1 1 10 3;
	setAttr -s 13 ".kot[0:12]"  1 10 10 10 10 10 2 10 
		10 1 1 10 3;
	setAttr -s 13 ".kix[0:12]"  0.98556113243103027 1 1 0.5633661150932312 
		0.52632856369018555 0.44146859645843506 0.26013889908790588 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[0:12]"  0.16931989789009094 0 0 0.82620733976364136 
		0.8502812385559082 0.89727663993835449 0.96557122468948364 0 0 0 0 0 0;
	setAttr -s 13 ".kox[0:12]"  0.98556113243103027 1 1 0.5633661150932312 
		0.52632856369018555 0.44146859645843506 0.55828839540481567 1 1 1 1 1 1;
	setAttr -s 13 ".koy[0:12]"  0.16931991279125214 0 0 0.82620733976364136 
		0.8502812385559082 0.89727663993835449 0.82964688539505005 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL291";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0.049918713102953649 2 0.060899065930670612 
		7 0.14709668188750463 12 0.1262265810543719 16 0.22191786990759865 20 0.19524574857032842 
		24 0.17447066748929493 27 0.19064459881398926 30 0.35279279850251527 32 0.37270569816352989 
		36 0.37270569816352989 39 0.37270569816352989 41 0.37270569816352989 43 0.37270569816352989;
	setAttr -s 14 ".kit[0:13]"  1 10 10 10 10 10 10 2 
		10 10 1 1 10 3;
	setAttr -s 14 ".kot[0:13]"  1 10 10 10 10 10 10 2 
		10 10 1 1 10 3;
	setAttr -s 14 ".kix[0:13]"  0.95296293497085571 1 1 1 1 1 1 0.98717135190963745 
		1 1 1 1 1 1;
	setAttr -s 14 ".kiy[0:13]"  -0.30308693647384644 0 0 0 0 0 0 0.15966446697711945 
		0 0 0 0 0 0;
	setAttr -s 14 ".kox[0:13]"  0.95296293497085571 1 1 1 1 1 1 0.52492153644561768 
		1 1 1 1 1 1;
	setAttr -s 14 ".koy[0:13]"  -0.30308693647384644 0 0 0 0 0 0 0.85115063190460205 
		0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU281";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 0 5 0 15 0 22 0 27 0 30 0 36 0 39 
		0 41 0 43 0;
	setAttr -s 11 ".kit[0:10]"  3 9 1 9 9 9 9 1 
		1 9 3;
	setAttr -s 11 ".kot[0:10]"  3 5 5 5 5 5 5 5 
		5 5 3;
	setAttr -s 11 ".kix[2:10]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[2:10]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU282";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0.084155571970393403 2 0.084155571970393403 
		5 0.084155571970393403 15 0.084155571970393403 22 0.084155571970393403 27 0.084155571970393403 
		30 0.084155571970393403 36 0.084155571970393403 39 0.084155571970393403 41 0.084155571970393403 
		43 0.084155571970393403;
	setAttr -s 11 ".kit[0:10]"  3 10 1 10 10 10 10 1 
		1 10 3;
	setAttr -s 11 ".kot[0:10]"  3 10 1 10 10 10 10 1 
		1 10 3;
	setAttr -s 11 ".kix[2:10]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[2:10]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[2:10]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[2:10]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL292";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0.067207227343123899 2 0.067207227343123899 
		5 0.067207227343123899 15 -0.032246896338246789 20 -0.51140145726557995 24 -0.76736806945692615 
		30 -1.0315028687324495 33 -0.90330798806437518 38 -1.0631693460657574 41 -1.0631693460657574 
		43 -1.0631693460657574;
	setAttr -s 11 ".kit[0:10]"  3 10 1 10 10 10 10 10 
		1 1 3;
	setAttr -s 11 ".kot[0:10]"  3 10 1 10 10 10 10 10 
		1 1 3;
	setAttr -s 11 ".kix[2:10]"  1 0.65383893251419067 0.37784361839294434 
		0.53959155082702637 0.91085052490234375 0.99302303791046143 1 1 1;
	setAttr -s 11 ".kiy[2:10]"  0 -0.75663375854492188 -0.92586946487426758 
		-0.84192699193954468 -0.41273647546768188 -0.11792079359292984 0 0 0;
	setAttr -s 11 ".kox[2:10]"  1 0.65383893251419067 0.37784361839294434 
		0.53959155082702637 0.91085052490234375 0.99302303791046143 1 1 1;
	setAttr -s 11 ".koy[2:10]"  0 -0.75663375854492188 -0.92586946487426758 
		-0.84192699193954468 -0.41273647546768188 -0.11792079359292984 0 0 0;
createNode animCurveTL -n "animCurveTL293";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -0.20472824713235571 2 -0.20472824713235571 
		5 -0.20472824713235571 15 -0.062614842692367778 20 0.65576182115871129 22 0.5159258985882067 
		24 0.7441693393803881 27 0.5159258985882067 30 0.99773220216580627 36 1.0579462566534619 
		39 1.0579462566534619 41 1.0579462566534619 43 1.0579462566534619;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 1 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 1 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 0.50240647792816162 0.37403833866119385 
		0.83343636989593506 1 0.61929851770401001 0.48425790667533875 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0.86463159322738647 0.92741316556930542 
		0.55261534452438354 0 0.78515559434890747 0.87492525577545166 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 0.50240647792816162 0.37403833866119385 
		0.83343636989593506 1 0.61929851770401001 0.48425790667533875 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0.86463159322738647 0.92741316556930542 
		0.55261534452438354 0 0.78515559434890747 0.87492525577545166 0 0 0 0;
createNode animCurveTL -n "animCurveTL294";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0.20941646546924442 2 0.20941646546924442 
		5 0.20941646546924442 15 0.67450935065521134 20 0.83210814772520802 22 0.45014842177370673 
		24 0.62329226928788428 27 0.45014842177370673 30 0.6887691429926267 36 0.072638839444557124 
		39 0.072638839444557124 41 0.072638839444557124 43 0.072638839444557124;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 1 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 1 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 0.62610399723052979 0.72083008289337158 
		0.53816908597946167 1 0.95036578178405762 0.62215304374694824 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0.77973955869674683 -0.6931118369102478 
		-0.84283691644668579 0 0.31113490462303162 -0.78289556503295898 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 0.62610399723052979 0.72083008289337158 
		0.53816908597946167 1 0.95036578178405762 0.62215304374694824 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0.77973955869674683 -0.6931118369102478 
		-0.84283691644668579 0 0.31113490462303162 -0.78289556503295898 0 0 0 0;
createNode animCurveTU -n "animCurveTU283";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 5 0 7 0 32 0 36 0 43 0;
	setAttr -s 7 ".kit[1:6]"  9 1 9 3 3 3;
	setAttr -s 7 ".kot[1:6]"  5 5 5 3 3 3;
	setAttr -s 7 ".kix[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".kiy[2:6]"  0 0 0 0 0;
createNode animCurveTU -n "animCurveTU284";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.084155864375844894 2 0.084155864375844894 
		5 0.084155864375844894 7 0.084155864375844894 32 0.084155864375844894 36 0.084155864375844894 
		43 0.084155864375844894;
	setAttr -s 7 ".kit[1:6]"  10 1 10 3 3 3;
	setAttr -s 7 ".kot[1:6]"  10 1 10 3 3 3;
	setAttr -s 7 ".kix[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".kiy[2:6]"  0 0 0 0 0;
	setAttr -s 7 ".kox[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".koy[2:6]"  0 0 0 0 0;
createNode animCurveTL -n "animCurveTL295";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 0 5 0 7 0 17 -0.51334774129946414 
		20 -0.71491481065250695 23 -1.0375332542997506 29 -0.31730087101618198 32 -0.86452786617669031 
		36 -0.88435206953989309 43 -0.90819949354339136;
	setAttr -s 11 ".kit[0:10]"  3 10 1 10 10 10 10 10 
		10 10 3;
	setAttr -s 11 ".kot[0:10]"  3 10 1 10 10 10 10 10 
		10 10 3;
	setAttr -s 11 ".kix[2:10]"  1 1 0.51834684610366821 0.35647821426391602 
		0.60229682922363281 0.86627501249313354 1 1 1;
	setAttr -s 11 ".kiy[2:10]"  0 0 -0.85517042875289917 -0.9343036413192749 
		0.79827219247817993 0.49956735968589783 0 0 0;
	setAttr -s 11 ".kox[2:10]"  1 1 0.51834684610366821 0.35647821426391602 
		0.60229682922363281 0.86627501249313354 1 1 1;
	setAttr -s 11 ".koy[2:10]"  0 0 -0.85517042875289917 -0.9343036413192749 
		0.79827219247817993 0.49956735968589783 0 0 0;
createNode animCurveTL -n "animCurveTL296";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.40088449385078673 2 -0.40088449385078673 
		5 -0.40088449385078673 7 -0.40088449385078673 17 -0.44222360882854606 20 -0.32676428290310378 
		23 -0.10784604258249864 32 1.0580129028132175 36 1.164174951832943 43 1.2108391908488743;
	setAttr -s 10 ".kit[0:9]"  3 10 1 10 10 10 10 3 
		3 3;
	setAttr -s 10 ".kot[0:9]"  3 10 1 10 10 10 10 3 
		3 3;
	setAttr -s 10 ".kix[2:9]"  1 1 1 0.51331287622451782 0.27750974893569946 
		1 1 1;
	setAttr -s 10 ".kiy[2:9]"  0 0 0 0.85820156335830688 0.96072286367416382 
		0 0 0;
	setAttr -s 10 ".kox[2:9]"  1 1 1 0.51331287622451782 0.27750974893569946 
		1 1 1;
	setAttr -s 10 ".koy[2:9]"  0 0 0 0.85820156335830688 0.96072286367416382 
		0 0 0;
createNode animCurveTL -n "animCurveTL297";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.69609418843799409 2 -0.69609418843799409 
		5 -0.69609418843799409 7 -0.69609418843799409 17 -0.02783884208685472 20 0.66684276654179897 
		23 1.9136860734718204 32 1.3535870816856057 36 1.4706984286299161 43 1.5143772136139084;
	setAttr -s 10 ".kit[0:9]"  3 10 1 10 10 10 10 3 
		3 3;
	setAttr -s 10 ".kot[0:9]"  3 10 1 10 10 10 10 3 
		3 3;
	setAttr -s 10 ".kix[2:9]"  1 1 0.30299511551856995 0.10246957093477249 
		0.50330686569213867 1 1 1;
	setAttr -s 10 ".kiy[2:9]"  0 0 0.95299208164215088 0.9947361946105957 
		0.86410772800445557 0 0 0;
	setAttr -s 10 ".kox[2:9]"  1 1 0.30299511551856995 0.10246957093477249 
		0.50330686569213867 1 1 1;
	setAttr -s 10 ".koy[2:9]"  0 0 0.95299208164215088 0.9947361946105957 
		0.86410772800445557 0 0 0;
createNode animCurveTA -n "animCurveTA942";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 -42.979928207632717 5 0 7 32.08764063267337 
		11 0 14 -44.681823791784915 22 0 27 36.364214229179019 31 0 33 38.380217984413505 
		39 43.148374416966405;
	setAttr -s 11 ".kit[0:10]"  9 10 1 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kot[0:10]"  9 10 1 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kix[2:10]"  1 1 0.17156292498111725 1 0.2929101288318634 
		1 0.9848746657371521 0.33379197120666504 1;
	setAttr -s 11 ".kiy[2:10]"  0 0 -0.98517310619354248 0 0.95613998174667358 
		0 0.17326848208904266 0.94264680147171021 0;
	setAttr -s 11 ".kox[2:10]"  1 1 0.17156292498111725 1 0.2929101288318634 
		1 0.9848746657371521 0.33379197120666504 1;
	setAttr -s 11 ".koy[2:10]"  0 0 -0.98517310619354248 0 0.95613998174667358 
		0 0.17326848208904266 0.94264680147171021 0;
createNode animCurveTA -n "animCurveTA943";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 0 5 0 7 -4.3805486921383689 11 0 
		14 22.779063864418671 22 0 27 20.118160033225784 31 0 33 -5.8115729684226434 39 22.588536482673312;
	setAttr -s 11 ".kit[0:10]"  3 10 1 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kot[0:10]"  3 10 1 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kix[2:10]"  1 1 0.44163432717323303 1 0.99430602788925171 
		1 0.40421801805496216 0.56026893854141235 1;
	setAttr -s 11 ".kiy[2:10]"  0 0 0.89719521999359131 0 -0.1065625324845314 
		0 -0.91466271877288818 0.82831078767776489 0;
	setAttr -s 11 ".kox[2:10]"  1 1 0.44163432717323303 1 0.99430602788925171 
		1 0.40421801805496216 0.56026893854141235 1;
	setAttr -s 11 ".koy[2:10]"  0 0 0.89719521999359131 0 -0.1065625324845314 
		0 -0.91466271877288818 0.82831078767776489 0;
createNode animCurveTA -n "animCurveTA944";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 0 5 0 7 -6.1268014305743463 11 0 
		14 2.3310347580612039 22 0 27 -11.136529021332354 31 0 33 -10.150089519274829 39 
		14.446365063254145;
	setAttr -s 11 ".kit[0:10]"  9 10 1 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kot[0:10]"  9 10 1 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kix[2:10]"  1 1 1 1 1 1 0.99631530046463013 0.72662568092346191 
		1;
	setAttr -s 11 ".kiy[2:10]"  0 0 0 0 0 0 0.085765868425369263 0.68703359365463257 
		0;
	setAttr -s 11 ".kox[2:10]"  1 1 1 1 1 1 0.99631530046463013 0.72662568092346191 
		1;
	setAttr -s 11 ".koy[2:10]"  0 0 0 0 0 0 0.085765868425369263 0.68703359365463257 
		0;
createNode animCurveTA -n "animCurveTA945";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 2.5807357528911581 7 18.571735136016461 
		11 0 22 29.528079861972945 27 0 33 -3.8431012440925492 37 -9.5916245365312367 40 
		-7.1353714806333466 42 -7.3487134897917388;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 1 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 1 
		10 10;
	setAttr -s 10 ".kix[7:9]"  1 1 1;
	setAttr -s 10 ".kiy[7:9]"  0 0 0;
	setAttr -s 10 ".kox[7:9]"  1 1 1;
	setAttr -s 10 ".koy[7:9]"  0 0 0;
createNode animCurveTA -n "animCurveTA946";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 -3.4053614989577987 7 -15.686885206407013 
		11 0 14 48.211360475999605 22 -2.0078076864021965 27 -40.439888786182607 33 -39.622410565957615 
		37 14.335823174328775 40 32.323857425208097 42 13.746704760472461;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 10 10 10 10 
		1 10 10;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 10 10 10 10 
		1 10 10;
	setAttr -s 11 ".kix[8:10]"  1 0.99810248613357544 0.20140035450458527;
	setAttr -s 11 ".kiy[8:10]"  0 -0.061575286090373993 -0.97950899600982666;
	setAttr -s 11 ".kox[8:10]"  1 0.99810248613357544 0.20140035450458527;
	setAttr -s 11 ".koy[8:10]"  0 -0.061575286090373993 -0.97950899600982666;
createNode animCurveTA -n "animCurveTA947";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 14.132360386371346 7 0.77230141094775717 
		11 0 22 15.281612187846184 27 0 33 -20.150165446331378 37 -8.0192099687410998 40 
		-6.1024608650043515 42 -10.880717533339125;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 1 
		10 10;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 1 
		10 10;
	setAttr -s 10 ".kix[7:9]"  1 1 0.62440693378448486;
	setAttr -s 10 ".kiy[7:9]"  0 0 -0.78109925985336304;
	setAttr -s 10 ".kox[7:9]"  1 1 0.62440693378448486;
	setAttr -s 10 ".koy[7:9]"  0 0 -0.78109925985336304;
createNode animCurveTA -n "animCurveTA948";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 18.882587574135272 5 0 7 0 11 0 22 
		-29.194999235866728 27 20.196364565402785 31 0 33 0 39 -29.213073046503467;
	setAttr -s 10 ".kit[0:9]"  3 10 1 10 10 10 10 10 
		10 1;
	setAttr -s 10 ".kot[0:9]"  3 10 1 10 10 10 10 10 
		10 1;
	setAttr -s 10 ".kix[2:9]"  1 1 1 0.83425462245941162 0.50735348463058472 
		1 1 1;
	setAttr -s 10 ".kiy[2:9]"  0 0 0 0.55137938261032104 0.86173808574676514 
		0 0 0;
	setAttr -s 10 ".kox[2:9]"  1 1 1 0.83425462245941162 0.50735348463058472 
		1 1 1;
	setAttr -s 10 ".koy[2:9]"  0 0 0 0.55137938261032104 0.86173808574676514 
		0 0 0;
createNode animCurveTA -n "animCurveTA949";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 -14.579041309193606 5 0 7 0 11 0 
		22 -8.4797493101690815 27 -23.148264893892989 31 0 33 0 39 -21.536655260179444;
	setAttr -s 10 ".kit[0:9]"  3 10 1 10 10 10 10 10 
		10 1;
	setAttr -s 10 ".kot[0:9]"  3 10 1 10 10 10 10 10 
		10 1;
	setAttr -s 10 ".kix[2:9]"  1 1 1 0.79711151123046875 0.89680641889572144 
		1 1 1;
	setAttr -s 10 ".kiy[2:9]"  0 0 0 -0.60383212566375732 0.44242322444915771 
		0 0 0;
	setAttr -s 10 ".kox[2:9]"  1 1 1 0.79711151123046875 0.89680641889572144 
		1 1 1;
	setAttr -s 10 ".koy[2:9]"  0 0 0 -0.60383212566375732 0.44242322444915771 
		0 0 0;
createNode animCurveTA -n "animCurveTA950";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 -15.390048212970234 5 0 7 0 11 0 
		22 -23.068247714780075 27 -16.443675301189817 31 59.23373079778905 33 0 39 10.534409668552819;
	setAttr -s 10 ".kit[0:9]"  3 10 1 10 10 10 10 10 
		10 1;
	setAttr -s 10 ".kot[0:9]"  3 10 1 10 10 10 10 10 
		10 1;
	setAttr -s 10 ".kix[2:9]"  1 1 1 0.88059735298156738 0.20443852245807648 
		0.57173943519592285 0.29935175180435181 1;
	setAttr -s 10 ".kiy[2:9]"  0 0 0 -0.4738653302192688 0.97887945175170898 
		0.82043522596359253 -0.95414280891418457 0;
	setAttr -s 10 ".kox[2:9]"  1 1 1 0.88059735298156738 0.20443852245807648 
		0.57173943519592285 0.29935175180435181 1;
	setAttr -s 10 ".koy[2:9]"  0 0 0 -0.4738653302192688 0.97887945175170898 
		0.82043522596359253 -0.95414280891418457 0;
createNode animCurveTA -n "animCurveTA951";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -18.592620239620459 3 -22.558743637443708 
		6 -41.359457731556006 8 -26.563038779837093 11 -5.340796492120111 16 -12.87666300343232 
		20 -14.124433844887845 25 36.560302742356335 28 43.746924687730306 33 -15.491858076370928 
		38 -6.6961256559856306 41 -18.592620239620459 43 -18.592620239620459;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 10 10 10 10 
		10 10 10 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 10 10 10 10 
		10 10 10 10 3;
createNode animCurveTA -n "animCurveTA952";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -4.0495369920864128 3 10.834153184777993 
		6 13.519400807732703 8 20.46190805682896 11 27.559043398950326 16 31.501155627176114 
		20 68.781473138660743 25 55.103529900944118 28 39.247507412252688 33 6.4462117326363941 
		38 1.5219093663733114 41 -4.0495369920864128 43 -4.0495369920864128;
	setAttr -s 13 ".kit[0:12]"  1 10 10 10 10 10 10 10 
		10 10 10 10 3;
	setAttr -s 13 ".kot[0:12]"  1 10 10 10 10 10 10 10 
		10 10 10 10 3;
	setAttr -s 13 ".kix[0:12]"  0.96994739770889282 1 1 0.56240427494049072 
		0.81056582927703857 0.38485810160636902 0.58869504928588867 0.45948660373687744 0.29958707094192505 
		0.45166909694671631 0.82425534725189209 1 1;
	setAttr -s 13 ".kiy[0:12]"  0.24331474304199219 0 0 0.82686245441436768 
		0.5856475830078125 0.92297577857971191 0.80835521221160889 -0.88818466663360596 -0.95406901836395264 
		-0.8921855092048645 -0.56621825695037842 0 0;
	setAttr -s 13 ".kox[0:12]"  0.9699474573135376 1 1 0.56240427494049072 
		0.81056582927703857 0.38485810160636902 0.58869504928588867 0.45948660373687744 0.29958707094192505 
		0.45166909694671631 0.82425534725189209 1 1;
	setAttr -s 13 ".koy[0:12]"  0.24331468343734741 0 0 0.82686245441436768 
		0.5856475830078125 0.92297577857971191 0.80835521221160889 -0.88818466663360596 -0.95406901836395264 
		-0.8921855092048645 -0.56621825695037842 0 0;
createNode animCurveTA -n "animCurveTA953";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -24.718935474963271 3 -38.46532847853689 
		6 15.617667339195982 8 9.6944887082811757 11 -35.757108743076969 16 -42.599445954370609 
		20 -46.947604917289716 25 -85.462283154928542 28 -87.173346711547183 33 -42.427271729080282 
		38 -19.376483407754751 41 -24.718935474963271 43 -24.718935474963271;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 10 10 10 10 
		10 10 10 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 10 10 10 10 
		10 10 10 10 3;
createNode animCurveTA -n "animCurveTA954";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 3.0491961178757743 5 0 7 0 11 0 14 
		11.07235572302179 22 0 27 0 31 21.518893316436039 33 9.3493588668611913 39 -8.2409711628210349;
	setAttr -s 11 ".kit[0:10]"  3 10 1 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kot[0:10]"  3 10 1 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kix[2:10]"  1 1 1 1 1 1 0.77482867240905762 0.45672854781150818 
		1;
	setAttr -s 11 ".kiy[2:10]"  0 0 0 0 0 0 0.63217133283615112 -0.88960611820220947 
		0;
	setAttr -s 11 ".kox[2:10]"  1 1 1 1 1 1 0.77482867240905762 0.45672854781150818 
		1;
	setAttr -s 11 ".koy[2:10]"  0 0 0 0 0 0 0.63217133283615112 -0.88960611820220947 
		0;
createNode animCurveTA -n "animCurveTA955";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 14.876505202409938 5 0 7 0 11 0 14 
		-11.679625021633161 22 -46.142595992612996 27 0 31 51.5922097373548 33 -35.465132715038898 
		39 30.553774798112826;
	setAttr -s 11 ".kit[0:10]"  3 10 1 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kot[0:10]"  3 10 1 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kix[2:10]"  1 1 1 0.41436758637428284 0.90487796068191528 
		0.17321275174617767 0.30745947360992432 0.58762305974960327 1;
	setAttr -s 11 ".kiy[2:10]"  0 0 0 -0.91010957956314087 0.42567113041877747 
		0.98488444089889526 -0.95156121253967285 -0.809134840965271 0;
	setAttr -s 11 ".kox[2:10]"  1 1 1 0.41436758637428284 0.90487796068191528 
		0.17321275174617767 0.30745947360992432 0.58762305974960327 1;
	setAttr -s 11 ".koy[2:10]"  0 0 0 -0.91010957956314087 0.42567113041877747 
		0.98488444089889526 -0.95156121253967285 -0.809134840965271 0;
createNode animCurveTA -n "animCurveTA956";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 6.1751049064842185 5 0 7 0 11 0 14 
		-26.471220232159098 22 0 27 0 31 10.614062920666544 33 12.972095335223852 39 -37.514737599640796;
	setAttr -s 11 ".kit[0:10]"  3 10 1 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kot[0:10]"  3 10 1 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kix[2:10]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[2:10]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[2:10]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[2:10]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU285";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 1 2 1 5 1 7 1 11 1 22 1 27 1 31 1 33 
		1 36 1 39 1 41 1 43 1;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU286";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 1 2 1 5 1 7 1 11 1 22 1 27 1 31 1 33 
		1 36 1 39 1 41 1 43 1;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU287";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 1 2 1 5 1 7 1 11 1 22 1 27 1 31 1 33 
		1 36 1 39 1 41 1 43 1;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA957";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA958";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA959";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL298";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 2 0 5 0 7 0 11 0 24 0 29 0 33 0 35 
		0 38 0 41 0 43 0;
	setAttr -s 12 ".kit[0:11]"  3 10 1 10 10 10 10 10 
		10 10 1 3;
	setAttr -s 12 ".kot[0:11]"  3 10 1 10 10 10 10 10 
		10 10 1 3;
	setAttr -s 12 ".kix[2:11]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[2:11]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[2:11]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[2:11]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL299";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL300";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU288";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 1 2 1 5 1 7 1 11 1 22 1 27 1 31 1 33 
		1 36 1 39 1 41 1 43 1;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU289";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 1 2 1 5 1 7 1 11 1 22 1 27 1 31 1 33 
		1 36 1 39 1 41 1 43 1;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU290";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 1 2 1 5 1 7 1 11 1 22 1 27 1 31 1 33 
		1 36 1 39 1 41 1 43 1;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA960";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA961";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA962";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL301";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 2 0 5 0 7 0 11 0 24 0 29 0 33 0 35 
		0 38 0 41 0 43 0;
	setAttr -s 12 ".kit[0:11]"  3 10 1 10 10 10 10 10 
		10 10 1 3;
	setAttr -s 12 ".kot[0:11]"  3 10 1 10 10 10 10 10 
		10 10 1 3;
	setAttr -s 12 ".kix[2:11]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[2:11]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[2:11]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[2:11]"  0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL302";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL303";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 2 0 5 0 7 0 11 0 22 0 27 0 31 0 33 
		0 36 0 39 0 41 0 43 0;
	setAttr -s 13 ".kit[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 1 10 10 10 10 10 
		10 10 1 10 3;
	setAttr -s 13 ".kix[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[2:12]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[2:12]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA963";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 25 0 29 -36.624098106069589 35 -14.906095203487858 
		37 -8.4447373395613461 40 -9.1263968176494501 42 -8.4447373395613461;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 1 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 1 10;
	setAttr -s 7 ".kix[5:6]"  1 1;
	setAttr -s 7 ".kiy[5:6]"  0 0;
	setAttr -s 7 ".kox[5:6]"  1 1;
	setAttr -s 7 ".koy[5:6]"  0 0;
createNode animCurveTA -n "animCurveTA964";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 25 0 29 -5.8393973731721349 35 7.1163277735743042 
		37 5.1621794548516915 40 6.9519768128416475 42 5.1621794548516915;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 1 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 1 10;
	setAttr -s 7 ".kix[5:6]"  1 1;
	setAttr -s 7 ".kiy[5:6]"  0 0;
	setAttr -s 7 ".kox[5:6]"  1 1;
	setAttr -s 7 ".koy[5:6]"  0 0;
createNode animCurveTA -n "animCurveTA965";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 7.2644697342894906 25 7.2644697342894906 
		29 -23.301242139760252 35 -31.459459520261117 37 -22.581490988001981 40 -20.780256571544722 
		42 -20.708318825772643;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 1 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 1 10;
	setAttr -s 7 ".kix[5:6]"  1 1;
	setAttr -s 7 ".kiy[5:6]"  0 0;
	setAttr -s 7 ".kox[5:6]"  1 1;
	setAttr -s 7 ".koy[5:6]"  0 0;
createNode animCurveTL -n "animCurveTL304";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 25 0 29 0.086615163484050003 35 0.10477632264924169 
		37 0.078111888668497706 40 0.059773441971283293 42 0.059773441971283293;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 1 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 1 10;
	setAttr -s 7 ".kix[5:6]"  1 1;
	setAttr -s 7 ".kiy[5:6]"  0 0;
	setAttr -s 7 ".kox[5:6]"  1 1;
	setAttr -s 7 ".koy[5:6]"  0 0;
createNode animCurveTL -n "animCurveTL305";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 25 0 29 0.11940709945512173 35 0.038623123526992847 
		37 0.017099188808574819 40 -0.0068076149771530538 42 -0.0068076149771530538;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 1 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 1 10;
	setAttr -s 7 ".kix[5:6]"  1 1;
	setAttr -s 7 ".kiy[5:6]"  0 0;
	setAttr -s 7 ".kox[5:6]"  1 1;
	setAttr -s 7 ".koy[5:6]"  0 0;
createNode animCurveTL -n "animCurveTL306";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 25 0 29 0.0037797799334779183 35 0.029952881686137453 
		37 0.037015168229084676 40 0.026638093195002814 42 0.026638093195002814;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 1 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 1 10;
	setAttr -s 7 ".kix[5:6]"  1 1;
	setAttr -s 7 ".kiy[5:6]"  0 0;
	setAttr -s 7 ".kox[5:6]"  1 1;
	setAttr -s 7 ".koy[5:6]"  0 0;
createNode animCurveTL -n "animCurveTL307";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.000119480405310887 2 -0.000119480405310887 
		7 -0.000119480405310887 11 -0.000119480405310887 18 0.03456785331196717 22 -0.17873433107707837 
		27 0.049578283550783045 41 0.17483528421843303 43 0.17483528421843303;
	setAttr -s 9 ".kit[0:8]"  9 10 10 10 10 10 10 1 
		3;
	setAttr -s 9 ".kot[0:8]"  9 10 10 10 10 10 10 1 
		3;
	setAttr -s 9 ".kix[7:8]"  1 1;
	setAttr -s 9 ".kiy[7:8]"  0 0;
	setAttr -s 9 ".kox[7:8]"  1 1;
	setAttr -s 9 ".koy[7:8]"  0 0;
createNode animCurveTL -n "animCurveTL308";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.1152566135867675 2 0.1152566135867675 
		7 0.1152566135867675 11 0.1152566135867675 18 0.052049039495153382 22 -0.058977937604569639 
		27 -0.043010500858181283 41 0.068484812290084643 43 0.068484812290084643;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 1 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 1 
		3;
	setAttr -s 9 ".kix[7:8]"  1 1;
	setAttr -s 9 ".kiy[7:8]"  0 0;
	setAttr -s 9 ".kox[7:8]"  1 1;
	setAttr -s 9 ".koy[7:8]"  0 0;
createNode animCurveTL -n "animCurveTL309";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.19515846066137013 2 0.19515846066137013 
		7 0.19515846066137013 11 0.19515846066137013 18 0.29721250197714122 22 0.22370368254187867 
		27 0.26000693659094304 41 0.29597166685289444 43 0.29597166685289444;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 10 10 1 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 10 10 1 
		3;
	setAttr -s 9 ".kix[7:8]"  1 1;
	setAttr -s 9 ".kiy[7:8]"  0 0;
	setAttr -s 9 ".kox[7:8]"  1 1;
	setAttr -s 9 ".koy[7:8]"  0 0;
createNode animCurveTU -n "Ratcatcher_CTRL_STUFF_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 43 1;
createNode animCurveTU -n "Ratcatcher_CTRL_STUFF_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 43 1;
createNode animCurveTU -n "Ratcatcher_CTRL_STUFF_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 43 1;
createNode animCurveTU -n "Ratcatcher_CTRL_STUFF_LAT_scaleZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 43 1;
createNode animCurveTU -n "Ratcatcher_CTRL_STUFF_LAT_scaleY";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 43 1;
createNode animCurveTU -n "Ratcatcher_CTRL_STUFF_LAT_scaleX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 43 1;
createNode lightLinker -n "lightLinker1";
	setAttr -s 3 ".lnk";
	setAttr -s 3 ".slnk";
select -ne :time1;
	setAttr -av -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 14;
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
connectAttr "deathSource1.cl" "clipLibrary1.sc[0]";
connectAttr "animCurveTU233.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "animCurveTA773.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "animCurveTA774.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "animCurveTA775.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "animCurveTU234.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "animCurveTU235.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "animCurveTU236.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "animCurveTU237.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "animCurveTA776.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "animCurveTA777.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "animCurveTA778.a" "clipLibrary1.cel[0].cev[10].cevr";
connectAttr "animCurveTU238.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "animCurveTU239.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "animCurveTL247.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "animCurveTL248.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "animCurveTL249.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "animCurveTA779.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "animCurveTA780.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "animCurveTA781.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "animCurveTA782.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "animCurveTA783.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "animCurveTU240.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "animCurveTU241.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "animCurveTU242.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "animCurveTU243.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "animCurveTA784.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "animCurveTA785.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "animCurveTA786.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "animCurveTL250.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "animCurveTL251.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "animCurveTL252.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "animCurveTU244.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "animCurveTA787.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "animCurveTA788.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "animCurveTA789.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "animCurveTU245.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "animCurveTU246.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "animCurveTU247.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "animCurveTU248.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "animCurveTA790.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "animCurveTA791.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "animCurveTA792.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "animCurveTU249.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "animCurveTU250.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "animCurveTL253.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "animCurveTL254.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "animCurveTL255.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "animCurveTA793.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "animCurveTA794.a" "clipLibrary1.cel[0].cev[48].cevr";
connectAttr "animCurveTA795.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "animCurveTA796.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "animCurveTA797.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "animCurveTU251.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "animCurveTU252.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "animCurveTU253.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "animCurveTU254.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "animCurveTU255.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "animCurveTA798.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "animCurveTA799.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "animCurveTA800.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "animCurveTL256.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "animCurveTL257.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "animCurveTL258.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "animCurveTU256.a" "clipLibrary1.cel[0].cev[63].cevr";
connectAttr "animCurveTA801.a" "clipLibrary1.cel[0].cev[64].cevr";
connectAttr "animCurveTA802.a" "clipLibrary1.cel[0].cev[65].cevr";
connectAttr "animCurveTA803.a" "clipLibrary1.cel[0].cev[66].cevr";
connectAttr "animCurveTU257.a" "clipLibrary1.cel[0].cev[67].cevr";
connectAttr "animCurveTA804.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "animCurveTA805.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "animCurveTA806.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "animCurveTA807.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "animCurveTA808.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "animCurveTA809.a" "clipLibrary1.cel[0].cev[73].cevr";
connectAttr "animCurveTU258.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "animCurveTA810.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "animCurveTA811.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "animCurveTA812.a" "clipLibrary1.cel[0].cev[77].cevr";
connectAttr "animCurveTA813.a" "clipLibrary1.cel[0].cev[78].cevr";
connectAttr "animCurveTA814.a" "clipLibrary1.cel[0].cev[79].cevr";
connectAttr "animCurveTA815.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "animCurveTU259.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "animCurveTA816.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "animCurveTA817.a" "clipLibrary1.cel[0].cev[83].cevr";
connectAttr "animCurveTA818.a" "clipLibrary1.cel[0].cev[84].cevr";
connectAttr "animCurveTA819.a" "clipLibrary1.cel[0].cev[85].cevr";
connectAttr "animCurveTA820.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "animCurveTA821.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "animCurveTU260.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "animCurveTA822.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr "animCurveTA823.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "animCurveTA824.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "animCurveTA825.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "animCurveTA826.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "animCurveTA827.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "animCurveTU261.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "animCurveTA828.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "animCurveTA829.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "animCurveTA830.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "animCurveTA831.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "animCurveTA832.a" "clipLibrary1.cel[0].cev[100].cevr";
connectAttr "animCurveTA833.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "animCurveTA834.a" "clipLibrary1.cel[0].cev[102].cevr";
connectAttr "animCurveTA835.a" "clipLibrary1.cel[0].cev[103].cevr";
connectAttr "animCurveTA836.a" "clipLibrary1.cel[0].cev[104].cevr";
connectAttr "animCurveTU262.a" "clipLibrary1.cel[0].cev[105].cevr";
connectAttr "animCurveTA837.a" "clipLibrary1.cel[0].cev[106].cevr";
connectAttr "animCurveTA838.a" "clipLibrary1.cel[0].cev[107].cevr";
connectAttr "animCurveTA839.a" "clipLibrary1.cel[0].cev[108].cevr";
connectAttr "animCurveTA840.a" "clipLibrary1.cel[0].cev[109].cevr";
connectAttr "animCurveTA841.a" "clipLibrary1.cel[0].cev[110].cevr";
connectAttr "animCurveTA842.a" "clipLibrary1.cel[0].cev[111].cevr";
connectAttr "animCurveTU263.a" "clipLibrary1.cel[0].cev[112].cevr";
connectAttr "animCurveTA843.a" "clipLibrary1.cel[0].cev[113].cevr";
connectAttr "animCurveTA844.a" "clipLibrary1.cel[0].cev[114].cevr";
connectAttr "animCurveTA845.a" "clipLibrary1.cel[0].cev[115].cevr";
connectAttr "animCurveTA846.a" "clipLibrary1.cel[0].cev[116].cevr";
connectAttr "animCurveTA847.a" "clipLibrary1.cel[0].cev[117].cevr";
connectAttr "animCurveTA848.a" "clipLibrary1.cel[0].cev[118].cevr";
connectAttr "animCurveTU264.a" "clipLibrary1.cel[0].cev[119].cevr";
connectAttr "animCurveTA849.a" "clipLibrary1.cel[0].cev[120].cevr";
connectAttr "animCurveTA850.a" "clipLibrary1.cel[0].cev[121].cevr";
connectAttr "animCurveTA851.a" "clipLibrary1.cel[0].cev[122].cevr";
connectAttr "animCurveTA852.a" "clipLibrary1.cel[0].cev[123].cevr";
connectAttr "animCurveTA853.a" "clipLibrary1.cel[0].cev[124].cevr";
connectAttr "animCurveTA854.a" "clipLibrary1.cel[0].cev[125].cevr";
connectAttr "animCurveTU265.a" "clipLibrary1.cel[0].cev[126].cevr";
connectAttr "animCurveTA855.a" "clipLibrary1.cel[0].cev[127].cevr";
connectAttr "animCurveTA856.a" "clipLibrary1.cel[0].cev[128].cevr";
connectAttr "animCurveTA857.a" "clipLibrary1.cel[0].cev[129].cevr";
connectAttr "animCurveTA858.a" "clipLibrary1.cel[0].cev[130].cevr";
connectAttr "animCurveTA859.a" "clipLibrary1.cel[0].cev[131].cevr";
connectAttr "animCurveTA860.a" "clipLibrary1.cel[0].cev[132].cevr";
connectAttr "animCurveTU266.a" "clipLibrary1.cel[0].cev[133].cevr";
connectAttr "animCurveTA861.a" "clipLibrary1.cel[0].cev[134].cevr";
connectAttr "animCurveTA862.a" "clipLibrary1.cel[0].cev[135].cevr";
connectAttr "animCurveTA863.a" "clipLibrary1.cel[0].cev[136].cevr";
connectAttr "animCurveTA864.a" "clipLibrary1.cel[0].cev[137].cevr";
connectAttr "animCurveTA865.a" "clipLibrary1.cel[0].cev[138].cevr";
connectAttr "animCurveTA866.a" "clipLibrary1.cel[0].cev[139].cevr";
connectAttr "animCurveTA867.a" "clipLibrary1.cel[0].cev[140].cevr";
connectAttr "animCurveTA868.a" "clipLibrary1.cel[0].cev[141].cevr";
connectAttr "animCurveTA869.a" "clipLibrary1.cel[0].cev[142].cevr";
connectAttr "animCurveTU267.a" "clipLibrary1.cel[0].cev[143].cevr";
connectAttr "animCurveTU268.a" "clipLibrary1.cel[0].cev[144].cevr";
connectAttr "animCurveTU269.a" "clipLibrary1.cel[0].cev[145].cevr";
connectAttr "animCurveTA870.a" "clipLibrary1.cel[0].cev[146].cevr";
connectAttr "animCurveTA871.a" "clipLibrary1.cel[0].cev[147].cevr";
connectAttr "animCurveTA872.a" "clipLibrary1.cel[0].cev[148].cevr";
connectAttr "animCurveTL259.a" "clipLibrary1.cel[0].cev[149].cevr";
connectAttr "animCurveTL260.a" "clipLibrary1.cel[0].cev[150].cevr";
connectAttr "animCurveTL261.a" "clipLibrary1.cel[0].cev[151].cevr";
connectAttr "animCurveTA873.a" "clipLibrary1.cel[0].cev[152].cevr";
connectAttr "animCurveTA874.a" "clipLibrary1.cel[0].cev[153].cevr";
connectAttr "animCurveTA875.a" "clipLibrary1.cel[0].cev[154].cevr";
connectAttr "animCurveTU270.a" "clipLibrary1.cel[0].cev[155].cevr";
connectAttr "animCurveTA876.a" "clipLibrary1.cel[0].cev[156].cevr";
connectAttr "animCurveTA877.a" "clipLibrary1.cel[0].cev[157].cevr";
connectAttr "animCurveTA878.a" "clipLibrary1.cel[0].cev[158].cevr";
connectAttr "animCurveTA879.a" "clipLibrary1.cel[0].cev[159].cevr";
connectAttr "animCurveTA880.a" "clipLibrary1.cel[0].cev[160].cevr";
connectAttr "animCurveTA881.a" "clipLibrary1.cel[0].cev[161].cevr";
connectAttr "animCurveTA882.a" "clipLibrary1.cel[0].cev[162].cevr";
connectAttr "animCurveTA883.a" "clipLibrary1.cel[0].cev[163].cevr";
connectAttr "animCurveTA884.a" "clipLibrary1.cel[0].cev[164].cevr";
connectAttr "animCurveTU271.a" "clipLibrary1.cel[0].cev[165].cevr";
connectAttr "animCurveTA885.a" "clipLibrary1.cel[0].cev[166].cevr";
connectAttr "animCurveTA886.a" "clipLibrary1.cel[0].cev[167].cevr";
connectAttr "animCurveTA887.a" "clipLibrary1.cel[0].cev[168].cevr";
connectAttr "animCurveTU272.a" "clipLibrary1.cel[0].cev[169].cevr";
connectAttr "animCurveTU273.a" "clipLibrary1.cel[0].cev[170].cevr";
connectAttr "animCurveTU274.a" "clipLibrary1.cel[0].cev[171].cevr";
connectAttr "animCurveTA888.a" "clipLibrary1.cel[0].cev[172].cevr";
connectAttr "animCurveTA889.a" "clipLibrary1.cel[0].cev[173].cevr";
connectAttr "animCurveTA890.a" "clipLibrary1.cel[0].cev[174].cevr";
connectAttr "animCurveTL262.a" "clipLibrary1.cel[0].cev[175].cevr";
connectAttr "animCurveTL263.a" "clipLibrary1.cel[0].cev[176].cevr";
connectAttr "animCurveTL264.a" "clipLibrary1.cel[0].cev[177].cevr";
connectAttr "animCurveTA891.a" "clipLibrary1.cel[0].cev[178].cevr";
connectAttr "animCurveTA892.a" "clipLibrary1.cel[0].cev[179].cevr";
connectAttr "animCurveTA893.a" "clipLibrary1.cel[0].cev[180].cevr";
connectAttr "animCurveTU275.a" "clipLibrary1.cel[0].cev[181].cevr";
connectAttr "animCurveTA894.a" "clipLibrary1.cel[0].cev[182].cevr";
connectAttr "animCurveTA895.a" "clipLibrary1.cel[0].cev[183].cevr";
connectAttr "animCurveTA896.a" "clipLibrary1.cel[0].cev[184].cevr";
connectAttr "animCurveTA897.a" "clipLibrary1.cel[0].cev[185].cevr";
connectAttr "animCurveTA898.a" "clipLibrary1.cel[0].cev[186].cevr";
connectAttr "animCurveTA899.a" "clipLibrary1.cel[0].cev[187].cevr";
connectAttr "animCurveTA900.a" "clipLibrary1.cel[0].cev[188].cevr";
connectAttr "animCurveTA901.a" "clipLibrary1.cel[0].cev[189].cevr";
connectAttr "animCurveTA902.a" "clipLibrary1.cel[0].cev[190].cevr";
connectAttr "animCurveTA903.a" "clipLibrary1.cel[0].cev[191].cevr";
connectAttr "animCurveTA904.a" "clipLibrary1.cel[0].cev[192].cevr";
connectAttr "animCurveTA905.a" "clipLibrary1.cel[0].cev[193].cevr";
connectAttr "animCurveTA906.a" "clipLibrary1.cel[0].cev[194].cevr";
connectAttr "animCurveTA907.a" "clipLibrary1.cel[0].cev[195].cevr";
connectAttr "animCurveTA908.a" "clipLibrary1.cel[0].cev[196].cevr";
connectAttr "animCurveTU276.a" "clipLibrary1.cel[0].cev[197].cevr";
connectAttr "animCurveTA909.a" "clipLibrary1.cel[0].cev[198].cevr";
connectAttr "animCurveTA910.a" "clipLibrary1.cel[0].cev[199].cevr";
connectAttr "animCurveTA911.a" "clipLibrary1.cel[0].cev[200].cevr";
connectAttr "animCurveTU277.a" "clipLibrary1.cel[0].cev[201].cevr";
connectAttr "animCurveTA912.a" "clipLibrary1.cel[0].cev[202].cevr";
connectAttr "animCurveTA913.a" "clipLibrary1.cel[0].cev[203].cevr";
connectAttr "animCurveTA914.a" "clipLibrary1.cel[0].cev[204].cevr";
connectAttr "animCurveTA915.a" "clipLibrary1.cel[0].cev[205].cevr";
connectAttr "animCurveTA916.a" "clipLibrary1.cel[0].cev[206].cevr";
connectAttr "animCurveTA917.a" "clipLibrary1.cel[0].cev[207].cevr";
connectAttr "animCurveTA918.a" "clipLibrary1.cel[0].cev[208].cevr";
connectAttr "animCurveTA919.a" "clipLibrary1.cel[0].cev[209].cevr";
connectAttr "animCurveTA920.a" "clipLibrary1.cel[0].cev[210].cevr";
connectAttr "animCurveTL265.a" "clipLibrary1.cel[0].cev[211].cevr";
connectAttr "animCurveTL266.a" "clipLibrary1.cel[0].cev[212].cevr";
connectAttr "animCurveTL267.a" "clipLibrary1.cel[0].cev[213].cevr";
connectAttr "animCurveTU278.a" "clipLibrary1.cel[0].cev[214].cevr";
connectAttr "animCurveTU279.a" "clipLibrary1.cel[0].cev[215].cevr";
connectAttr "animCurveTA921.a" "clipLibrary1.cel[0].cev[216].cevr";
connectAttr "animCurveTA922.a" "clipLibrary1.cel[0].cev[217].cevr";
connectAttr "animCurveTA923.a" "clipLibrary1.cel[0].cev[218].cevr";
connectAttr "animCurveTL268.a" "clipLibrary1.cel[0].cev[219].cevr";
connectAttr "animCurveTL269.a" "clipLibrary1.cel[0].cev[220].cevr";
connectAttr "animCurveTL270.a" "clipLibrary1.cel[0].cev[221].cevr";
connectAttr "animCurveTL271.a" "clipLibrary1.cel[0].cev[222].cevr";
connectAttr "animCurveTL272.a" "clipLibrary1.cel[0].cev[223].cevr";
connectAttr "animCurveTL273.a" "clipLibrary1.cel[0].cev[224].cevr";
connectAttr "animCurveTA924.a" "clipLibrary1.cel[0].cev[225].cevr";
connectAttr "animCurveTA925.a" "clipLibrary1.cel[0].cev[226].cevr";
connectAttr "animCurveTA926.a" "clipLibrary1.cel[0].cev[227].cevr";
connectAttr "animCurveTL274.a" "clipLibrary1.cel[0].cev[228].cevr";
connectAttr "animCurveTL275.a" "clipLibrary1.cel[0].cev[229].cevr";
connectAttr "animCurveTL276.a" "clipLibrary1.cel[0].cev[230].cevr";
connectAttr "animCurveTA927.a" "clipLibrary1.cel[0].cev[231].cevr";
connectAttr "animCurveTA928.a" "clipLibrary1.cel[0].cev[232].cevr";
connectAttr "animCurveTA929.a" "clipLibrary1.cel[0].cev[233].cevr";
connectAttr "animCurveTL277.a" "clipLibrary1.cel[0].cev[234].cevr";
connectAttr "animCurveTL278.a" "clipLibrary1.cel[0].cev[235].cevr";
connectAttr "animCurveTL279.a" "clipLibrary1.cel[0].cev[236].cevr";
connectAttr "animCurveTU280.a" "clipLibrary1.cel[0].cev[237].cevr";
connectAttr "animCurveTA930.a" "clipLibrary1.cel[0].cev[238].cevr";
connectAttr "animCurveTA931.a" "clipLibrary1.cel[0].cev[239].cevr";
connectAttr "animCurveTA932.a" "clipLibrary1.cel[0].cev[240].cevr";
connectAttr "animCurveTL280.a" "clipLibrary1.cel[0].cev[241].cevr";
connectAttr "animCurveTL281.a" "clipLibrary1.cel[0].cev[242].cevr";
connectAttr "animCurveTL282.a" "clipLibrary1.cel[0].cev[243].cevr";
connectAttr "animCurveTA933.a" "clipLibrary1.cel[0].cev[244].cevr";
connectAttr "animCurveTA934.a" "clipLibrary1.cel[0].cev[245].cevr";
connectAttr "animCurveTA935.a" "clipLibrary1.cel[0].cev[246].cevr";
connectAttr "animCurveTL283.a" "clipLibrary1.cel[0].cev[247].cevr";
connectAttr "animCurveTL284.a" "clipLibrary1.cel[0].cev[248].cevr";
connectAttr "animCurveTL285.a" "clipLibrary1.cel[0].cev[249].cevr";
connectAttr "animCurveTA936.a" "clipLibrary1.cel[0].cev[250].cevr";
connectAttr "animCurveTA937.a" "clipLibrary1.cel[0].cev[251].cevr";
connectAttr "animCurveTA938.a" "clipLibrary1.cel[0].cev[252].cevr";
connectAttr "animCurveTL286.a" "clipLibrary1.cel[0].cev[253].cevr";
connectAttr "animCurveTL287.a" "clipLibrary1.cel[0].cev[254].cevr";
connectAttr "animCurveTL288.a" "clipLibrary1.cel[0].cev[255].cevr";
connectAttr "animCurveTA939.a" "clipLibrary1.cel[0].cev[256].cevr";
connectAttr "animCurveTA940.a" "clipLibrary1.cel[0].cev[257].cevr";
connectAttr "animCurveTA941.a" "clipLibrary1.cel[0].cev[258].cevr";
connectAttr "animCurveTL289.a" "clipLibrary1.cel[0].cev[259].cevr";
connectAttr "animCurveTL290.a" "clipLibrary1.cel[0].cev[260].cevr";
connectAttr "animCurveTL291.a" "clipLibrary1.cel[0].cev[261].cevr";
connectAttr "animCurveTU281.a" "clipLibrary1.cel[0].cev[262].cevr";
connectAttr "animCurveTU282.a" "clipLibrary1.cel[0].cev[263].cevr";
connectAttr "animCurveTL292.a" "clipLibrary1.cel[0].cev[264].cevr";
connectAttr "animCurveTL293.a" "clipLibrary1.cel[0].cev[265].cevr";
connectAttr "animCurveTL294.a" "clipLibrary1.cel[0].cev[266].cevr";
connectAttr "animCurveTU283.a" "clipLibrary1.cel[0].cev[267].cevr";
connectAttr "animCurveTU284.a" "clipLibrary1.cel[0].cev[268].cevr";
connectAttr "animCurveTL295.a" "clipLibrary1.cel[0].cev[269].cevr";
connectAttr "animCurveTL296.a" "clipLibrary1.cel[0].cev[270].cevr";
connectAttr "animCurveTL297.a" "clipLibrary1.cel[0].cev[271].cevr";
connectAttr "animCurveTA942.a" "clipLibrary1.cel[0].cev[272].cevr";
connectAttr "animCurveTA943.a" "clipLibrary1.cel[0].cev[273].cevr";
connectAttr "animCurveTA944.a" "clipLibrary1.cel[0].cev[274].cevr";
connectAttr "animCurveTA945.a" "clipLibrary1.cel[0].cev[275].cevr";
connectAttr "animCurveTA946.a" "clipLibrary1.cel[0].cev[276].cevr";
connectAttr "animCurveTA947.a" "clipLibrary1.cel[0].cev[277].cevr";
connectAttr "animCurveTA948.a" "clipLibrary1.cel[0].cev[278].cevr";
connectAttr "animCurveTA949.a" "clipLibrary1.cel[0].cev[279].cevr";
connectAttr "animCurveTA950.a" "clipLibrary1.cel[0].cev[280].cevr";
connectAttr "animCurveTA951.a" "clipLibrary1.cel[0].cev[281].cevr";
connectAttr "animCurveTA952.a" "clipLibrary1.cel[0].cev[282].cevr";
connectAttr "animCurveTA953.a" "clipLibrary1.cel[0].cev[283].cevr";
connectAttr "animCurveTA954.a" "clipLibrary1.cel[0].cev[284].cevr";
connectAttr "animCurveTA955.a" "clipLibrary1.cel[0].cev[285].cevr";
connectAttr "animCurveTA956.a" "clipLibrary1.cel[0].cev[286].cevr";
connectAttr "animCurveTU285.a" "clipLibrary1.cel[0].cev[287].cevr";
connectAttr "animCurveTU286.a" "clipLibrary1.cel[0].cev[288].cevr";
connectAttr "animCurveTU287.a" "clipLibrary1.cel[0].cev[289].cevr";
connectAttr "animCurveTA957.a" "clipLibrary1.cel[0].cev[290].cevr";
connectAttr "animCurveTA958.a" "clipLibrary1.cel[0].cev[291].cevr";
connectAttr "animCurveTA959.a" "clipLibrary1.cel[0].cev[292].cevr";
connectAttr "animCurveTL298.a" "clipLibrary1.cel[0].cev[293].cevr";
connectAttr "animCurveTL299.a" "clipLibrary1.cel[0].cev[294].cevr";
connectAttr "animCurveTL300.a" "clipLibrary1.cel[0].cev[295].cevr";
connectAttr "animCurveTU288.a" "clipLibrary1.cel[0].cev[296].cevr";
connectAttr "animCurveTU289.a" "clipLibrary1.cel[0].cev[297].cevr";
connectAttr "animCurveTU290.a" "clipLibrary1.cel[0].cev[298].cevr";
connectAttr "animCurveTA960.a" "clipLibrary1.cel[0].cev[299].cevr";
connectAttr "animCurveTA961.a" "clipLibrary1.cel[0].cev[300].cevr";
connectAttr "animCurveTA962.a" "clipLibrary1.cel[0].cev[301].cevr";
connectAttr "animCurveTL301.a" "clipLibrary1.cel[0].cev[302].cevr";
connectAttr "animCurveTL302.a" "clipLibrary1.cel[0].cev[303].cevr";
connectAttr "animCurveTL303.a" "clipLibrary1.cel[0].cev[304].cevr";
connectAttr "animCurveTA963.a" "clipLibrary1.cel[0].cev[305].cevr";
connectAttr "animCurveTA964.a" "clipLibrary1.cel[0].cev[306].cevr";
connectAttr "animCurveTA965.a" "clipLibrary1.cel[0].cev[307].cevr";
connectAttr "animCurveTL304.a" "clipLibrary1.cel[0].cev[308].cevr";
connectAttr "animCurveTL305.a" "clipLibrary1.cel[0].cev[309].cevr";
connectAttr "animCurveTL306.a" "clipLibrary1.cel[0].cev[310].cevr";
connectAttr "animCurveTL307.a" "clipLibrary1.cel[0].cev[311].cevr";
connectAttr "animCurveTL308.a" "clipLibrary1.cel[0].cev[312].cevr";
connectAttr "animCurveTL309.a" "clipLibrary1.cel[0].cev[313].cevr";
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
