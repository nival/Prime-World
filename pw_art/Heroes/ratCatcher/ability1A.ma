//Maya ASCII 2008 scene
//Name: ability01.ma
//Last modified: Thu, Sep 17, 2009 06:50:16 PM
//Codeset: 1251
requires maya "2008";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Unlimited 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200802250025-718075";
fileInfo "osv" "Microsoft Windows XP Service Pack 3 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 323 ".cel[0].cev";
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
createNode animClip -n "ability1Source";
	setAttr ".ihi" 0;
	setAttr -s 323 ".ac";
	setAttr ".ac[0:319]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
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
		yes yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[322:324]" yes yes yes;
	setAttr ".se" 60;
	setAttr ".ci" no;
createNode animCurveTU -n "animCurveTU483";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 9 9 9 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 5 5 5 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1545";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1546";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 3.1805546814635176e-015 3 0 7 0 12 0 
		20 0 21 0 26 0 31 0 37 0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1547";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 9.9392333795734924e-017 3 0 7 0 12 0 
		20 0 21 0 26 0 31 0 37 0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU484";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 9 9 9 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 5 5 5 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU485";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 9 9 9 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 5 5 5 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU486";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 3 1 7 1 12 1 20 1 21 1 26 1 31 1 37 
		1 49 1 60 1;
	setAttr -s 11 ".kit[0:10]"  9 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  9 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU487";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 9 9 9 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 5 5 5 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1548";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 3.1805546814635168e-015 3 0 7 0 12 0 
		20 0 21 0 26 0 31 0 37 0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1549";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1550";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 4.7708320221952728e-015 3 0 7 0 12 0 
		20 0 21 0 26 0 31 0 37 0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU488";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 54 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 10 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 10 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU489";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 54 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 10 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 10 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL493";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0.40930268174563 3 0.40930268174563 7 
		0.40930268174563 12 0.40930268174563 20 0.40930268174562823 21 0.40930268174562823 
		26 0.40930268174562823 31 0.40930268174562823 37 0.40930268174562823 49 0.32490473654970353 
		54 0.35669253258238554 60 0.40930268174563;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 1 1 3 1 
		1 10 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 1 1 3 1 
		1 10 10 3;
	setAttr -s 12 ".kix[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[4:11]"  0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[4:11]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL494";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0.25860394298924627 3 0.25860394298924627 
		7 0.25860394298924627 12 0.25860394298924627 20 0.25238686300933011 21 0.25238686300933011 
		26 0.25238686300933011 31 0.25238686300933011 37 0.25238686300933011 49 0.52365430502534571 
		54 0.23817867763955614 60 0.25860394298924627;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 1 1 3 1 
		1 10 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 1 1 3 1 
		1 10 10 3;
	setAttr -s 12 ".kix[4:11]"  1 1 1 1 1 0.99968576431274414 1 1;
	setAttr -s 12 ".kiy[4:11]"  0 0 0 0 0 -0.025065392255783081 0 0;
	setAttr -s 12 ".kox[4:11]"  1 1 1 1 1 0.99968576431274414 1 1;
	setAttr -s 12 ".koy[4:11]"  0 0 0 0 0 -0.025065392255783081 0 0;
createNode animCurveTL -n "animCurveTL495";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -0.29847095663485657 3 -0.080805848826778326 
		7 0.40688673760680316 12 0.40688673760680316 20 -0.72473709845870171 21 -0.72473709845870171 
		26 -0.72473709845870171 31 -0.72473709845870171 37 -0.72473709845870171 49 0.52240220574312357 
		54 -0.34575207538711433 60 -0.29847095663485657;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 1 1 3 1 
		1 10 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 1 1 3 1 
		1 10 10 3;
	setAttr -s 12 ".kix[4:11]"  1 1 1 1 1 0.83123201131820679 1 1;
	setAttr -s 12 ".kiy[4:11]"  0 0 0 0 0 0.55592560768127441 0 0;
	setAttr -s 12 ".kox[4:11]"  1 1 1 1 1 0.83123201131820679 1 1;
	setAttr -s 12 ".koy[4:11]"  0 0 0 0 0 0.55592560768127441 0 0;
createNode animCurveTA -n "animCurveTA1551";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1552";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 3.1805546814635168e-015 3 0 7 0 12 0 
		20 0 21 0 26 0 31 0 37 0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1553";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -7.9513867036587899e-016 3 0 7 0 12 0 
		20 0 21 0 26 0 31 0 37 0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1554";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 25.675870473757751 3 25.675870473757751 
		7 25.675870473757751 12 -10.270524972968653 21 25.675870473757751 26 25.675870473757751 
		31 25.675870473757751 44 9.8419354023397823 49 41.562474252549642 60 25.675870473757751;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 1 3 1 10 
		10 3;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 1 3 1 10 
		10 3;
	setAttr -s 10 ".kix[4:9]"  1 1 1 0.90775752067565918 0.88788306713104248 
		1;
	setAttr -s 10 ".kiy[4:9]"  0 0 0 0.41949522495269775 0.46006932854652405 
		0;
	setAttr -s 10 ".kox[4:9]"  1 1 1 0.90775752067565918 0.88788306713104248 
		1;
	setAttr -s 10 ".koy[4:9]"  0 0 0 0.41949522495269775 0.46006932854652405 
		0;
createNode animCurveTA -n "animCurveTA1555";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -3.0739741698828946 3 -3.0739741698828946 
		7 -3.0739741698828946 12 -10.732206329215355 21 -3.0739741698828946 26 -3.0739741698828946 
		31 -3.0739741698828946 44 -21.36363556022425 49 -16.760680992840772 60 -3.0739741698828946;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 1 3 1 10 
		10 3;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 1 3 1 10 
		10 3;
	setAttr -s 10 ".kix[4:9]"  1 1 1 0.92907446622848511 0.85804969072341919 
		1;
	setAttr -s 10 ".kiy[4:9]"  0 0 0 -0.36989256739616394 0.51356661319732666 
		0;
	setAttr -s 10 ".kox[4:9]"  1 1 1 0.92907446622848511 0.85804969072341919 
		1;
	setAttr -s 10 ".koy[4:9]"  0 0 0 -0.36989256739616394 0.51356661319732666 
		0;
createNode animCurveTU -n "animCurveTU490";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  7 3 12 3 21 3 26 3 31 3 37 3 49 3;
	setAttr -s 7 ".kit[3:6]"  3 1 1 3;
	setAttr -s 7 ".kot[3:6]"  3 1 1 3;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[4:6]"  1 1 1;
	setAttr -s 7 ".koy[4:6]"  0 0 0;
createNode animCurveTU -n "animCurveTU491";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  7 0 12 0 21 0 26 0 31 0 37 0 49 0;
	setAttr -s 7 ".kit[3:6]"  3 1 1 3;
	setAttr -s 7 ".kot[3:6]"  3 1 1 3;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[4:6]"  1 1 1;
	setAttr -s 7 ".koy[4:6]"  0 0 0;
createNode animCurveTU -n "animCurveTU492";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  7 1 12 1 21 1 26 1 31 1 37 1 49 1;
	setAttr -s 7 ".kit[0:6]"  9 9 9 3 1 1 3;
	setAttr -s 7 ".kot[0:6]"  5 5 5 3 1 1 3;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[4:6]"  1 1 1;
	setAttr -s 7 ".koy[4:6]"  0 0 0;
createNode animCurveTU -n "animCurveTU493";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  7 0 12 0 21 0 26 0 31 0 37 0 49 0;
	setAttr -s 7 ".kit[3:6]"  3 1 1 3;
	setAttr -s 7 ".kot[3:6]"  3 1 1 3;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[4:6]"  1 1 1;
	setAttr -s 7 ".koy[4:6]"  0 0 0;
createNode animCurveTA -n "animCurveTA1556";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 93.144161708979723 3 115.67063816524453 
		7 81.97909850357712 12 83.147772453398289 17 99.503500434087996 21 69.896092515064709 
		26 81.97909850357712 31 81.97909850357712 37 93.543234047041679 43 100.54560935081793 
		49 86.522459557203078 60 93.144161708979723;
	setAttr -s 12 ".kit[0:11]"  9 10 10 10 10 3 3 1 
		1 1 3 3;
	setAttr -s 12 ".kot[0:11]"  9 10 10 10 10 3 3 1 
		1 1 3 3;
	setAttr -s 12 ".kix[7:11]"  1 1 0.98836433887481689 1 1;
	setAttr -s 12 ".kiy[7:11]"  0 0 -0.15210516750812531 0 0;
	setAttr -s 12 ".kox[7:11]"  1 1 0.98836433887481689 1 1;
	setAttr -s 12 ".koy[7:11]"  0 0 -0.15210516750812531 0 0;
createNode animCurveTA -n "animCurveTA1557";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 95.049826002206416 3 85.398815479828968 
		7 74.933338714057456 12 74.847166723635354 17 59.890527013147647 21 65.171572832481658 
		26 74.933338714057456 31 74.933338714057456 37 87.097626836214019 43 70.927202714301188 
		49 79.931272185624294 60 95.049826002206416;
	setAttr -s 12 ".kit[0:11]"  9 10 10 10 10 10 3 1 
		1 3 9 3;
	setAttr -s 12 ".kot[0:11]"  9 10 10 10 10 10 3 1 
		1 3 9 3;
	setAttr -s 12 ".kix[7:11]"  1 1 1 0.80269861221313477 1;
	setAttr -s 12 ".kiy[7:11]"  0 0 0 0.59638500213623047 0;
	setAttr -s 12 ".kox[7:11]"  1 1 1 0.80269861221313477 1;
	setAttr -s 12 ".koy[7:11]"  0 0 0 0.59638500213623047 0;
createNode animCurveTA -n "animCurveTA1558";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 1.1812364035166698 3 8.3248574183071984 
		7 19.834164688438154 12 27.712342777702769 17 14.110536853504321 21 19.497490761137001 
		26 19.834164688438154 31 19.834164688438154 37 16.702900299076301 43 23.318835942767862 
		49 18.189925115246695 60 1.1812364035166698;
	setAttr -s 12 ".kit[0:11]"  9 10 10 10 10 10 3 1 
		1 10 9 3;
	setAttr -s 12 ".kot[0:11]"  9 10 10 10 10 10 3 1 
		1 10 9 3;
	setAttr -s 12 ".kix[7:11]"  1 1 0.99790167808532715 0.82622027397155762 
		1;
	setAttr -s 12 ".kiy[7:11]"  0 0 0.064747557044029236 -0.56334710121154785 
		0;
	setAttr -s 12 ".kox[7:11]"  1 1 0.99790167808532715 0.82622027397155762 
		1;
	setAttr -s 12 ".koy[7:11]"  0 0 0.064747557044029236 -0.56334710121154785 
		0;
createNode animCurveTL -n "animCurveTL496";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -0.23689498628395578 3 -0.58461804437205434 
		7 -0.70906209291727074 12 -0.50944975844492635 17 0.019421713968431877 21 0.31678026733673026 
		26 0.47225381625219548 31 0.47225381625219548 37 0.14279564600541986 43 -0.42826281232265567 
		49 -0.64043258922654644 54 -0.40488957449476687 60 -0.23689498628395578;
	setAttr -s 13 ".kit[0:12]"  9 10 10 10 10 10 3 1 
		9 10 3 10 3;
	setAttr -s 13 ".kot[0:12]"  9 10 10 10 10 10 3 1 
		9 10 3 10 3;
	setAttr -s 13 ".kix[7:12]"  1 0.40594384074211121 0.45482552051544189 
		1 0.67248630523681641 1;
	setAttr -s 13 ".kiy[7:12]"  0 -0.9138980507850647 -0.89058053493499756 
		0 0.74010956287384033 0;
	setAttr -s 13 ".kox[7:12]"  1 0.40594384074211121 0.45482552051544189 
		1 0.67248630523681641 1;
	setAttr -s 13 ".koy[7:12]"  0 -0.9138980507850647 -0.89058053493499756 
		0 0.74010956287384033 0;
createNode animCurveTL -n "animCurveTL497";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -0.30633990936382105 3 -0.21883121972944936 
		7 -0.43978528109779996 12 -0.45430844085999394 17 -0.29579493749129582 21 -0.35857385719963702 
		26 -0.33493150612079675 31 -0.33493150612079675 37 -0.29283152671313845 43 -0.22735828827325397 
		49 -0.42807369560763242 54 -0.19610719149566561 60 -0.30633990936382105;
	setAttr -s 13 ".kit[0:12]"  9 10 10 10 10 10 3 1 
		9 3 3 10 3;
	setAttr -s 13 ".kot[0:12]"  9 10 10 10 10 10 3 1 
		9 3 3 10 3;
	setAttr -s 13 ".kix[7:12]"  1 0.96568787097930908 1 1 0.94906187057495117 
		1;
	setAttr -s 13 ".kiy[7:12]"  0 0.25970539450645447 0 0 0.31508973240852356 
		0;
	setAttr -s 13 ".kox[7:12]"  1 0.96568787097930908 1 1 0.94906187057495117 
		1;
	setAttr -s 13 ".koy[7:12]"  0 0.25970539450645447 0 0 0.31508973240852356 
		0;
createNode animCurveTL -n "animCurveTL498";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0.52899036848843184 3 0.44607585874713818 
		7 0.54826228657872778 12 0.34678228204110784 17 0.004734510528346514 21 -0.32525538304565443 
		26 -0.39677818164878087 31 -0.39677818164878087 37 0.13455383166063486 43 0.49448946959599016 
		49 0.51889511083841566 54 0.54724808685236226 60 0.52899036848843184;
	setAttr -s 13 ".kit[0:12]"  9 10 10 10 10 10 3 1 
		9 10 3 10 3;
	setAttr -s 13 ".kot[0:12]"  9 10 10 10 10 10 3 1 
		9 10 3 10 3;
	setAttr -s 13 ".kix[7:12]"  1 0.40945324301719666 1 1 1 1;
	setAttr -s 13 ".kiy[7:12]"  0 0.91233110427856445 0 0 0 0;
	setAttr -s 13 ".kox[7:12]"  1 0.40945324301719666 1 1 1 1;
	setAttr -s 13 ".koy[7:12]"  0 0.91233110427856445 0 0 0 0;
createNode animCurveTU -n "animCurveTU494";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  9 9 9 9 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  9 5 5 5 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1559";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -24.884454396993167 3 -24.884454396993167 
		7 -24.884454396993167 12 -24.884454396993167 20 -24.884454396993167 21 -24.884454396993167 
		26 -24.884454396993167 31 -24.884454396993167 37 -24.884454396993167 49 -24.884454396993167 
		55 -48.40686265572522 60 -24.884454396993167;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 1 1 3 1 
		1 3 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 1 1 3 1 
		1 3 10 3;
	setAttr -s 12 ".kix[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[4:11]"  0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[4:11]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1560";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -43.339475474578435 3 -43.339475474578435 
		7 -43.339475474578435 12 -43.339475474578435 20 -43.339475474578435 21 -43.339475474578435 
		26 -43.339475474578435 31 -43.339475474578435 37 -43.339475474578435 49 -43.339475474578435 
		55 -23.131592227091954 60 -43.339475474578435;
	setAttr -s 12 ".kit[1:11]"  10 10 10 1 1 3 1 1 
		3 10 3;
	setAttr -s 12 ".kot[1:11]"  10 10 10 1 1 3 1 1 
		3 10 3;
	setAttr -s 12 ".kix[0:11]"  0.98886251449584961 1 1 1 1 1 1 1 1 1 1 
		1;
	setAttr -s 12 ".kiy[0:11]"  -0.14883163571357727 0 0 0 0 0 0 0 0 0 
		0 0;
	setAttr -s 12 ".kox[0:11]"  0.98886251449584961 1 1 1 1 1 1 1 1 1 1 
		1;
	setAttr -s 12 ".koy[0:11]"  -0.14883166551589966 0 0 0 0 0 0 0 0 0 
		0 0;
createNode animCurveTA -n "animCurveTA1561";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 11.606559612787883 3 11.606559612787883 
		7 11.606559612787883 12 11.606559612787883 20 11.606559612787883 21 11.606559612787883 
		26 11.606559612787883 31 11.606559612787883 37 11.606559612787883 49 11.606559612787883 
		55 38.075195827047658 60 11.606559612787883;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 1 1 3 1 
		1 3 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 1 1 3 1 
		1 3 10 3;
	setAttr -s 12 ".kix[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[4:11]"  0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[4:11]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU495";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 9 9 9 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 5 5 5 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU496";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 9 9 9 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 5 5 5 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU497";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 1 1 3 1 7 1 12 1 20 1 21 1 26 1 31 
		1 37 1 49 1 53 1 56 0 60 0;
	setAttr -s 14 ".kit[0:13]"  9 10 10 10 10 3 3 3 
		3 1 3 10 10 3;
	setAttr -s 14 ".kot[0:13]"  9 10 10 10 10 3 3 3 
		3 1 3 10 10 3;
	setAttr -s 14 ".kix[9:13]"  1 1 1 1 1;
	setAttr -s 14 ".kiy[9:13]"  0 0 0 0 0;
	setAttr -s 14 ".kox[9:13]"  1 1 1 1 1;
	setAttr -s 14 ".koy[9:13]"  0 0 0 0 0;
createNode animCurveTU -n "animCurveTU498";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 9 9 9 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 5 5 5 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1562";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 3.9531091186723013 3 3.9531091186723013 
		7 3.9531091186723013 12 3.9531091186723013 20 3.9531091186723013 21 3.9531091186723013 
		26 3.9531091186723013 31 3.9531091186723013 37 3.9531091186723013 49 3.9531091186723013 
		60 3.9531091186723013;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1563";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0.62018686761647346 3 0.62018686761647346 
		7 0.62018686761647346 12 0.62018686761647346 20 0.62018686761647346 21 0.62018686761647346 
		26 0.62018686761647346 31 0.62018686761647346 37 0.62018686761647346 49 0.62018686761647346 
		60 0.62018686761647346;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1564";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 5.3292188742882338 3 5.3292188742882338 
		7 5.3292188742882338 12 5.3292188742882338 20 5.3292188742882338 21 5.3292188742882338 
		26 5.3292188742882338 31 5.3292188742882338 37 5.3292188742882338 49 5.3292188742882338 
		60 5.3292188742882338;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU499";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 1 0 3 0 7 0 12 0 19 0 20 0 23 0 26 
		0 31 0 44 0 49 0 55 0 60 0;
	setAttr -s 14 ".kit[0:13]"  3 10 10 10 10 10 1 10 
		3 1 10 3 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 10 10 10 10 1 10 
		3 1 10 3 10 3;
	setAttr -s 14 ".kix[6:13]"  1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[6:13]"  0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[6:13]"  1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[6:13]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU500";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 1 0 3 0 7 0 12 0 19 0 20 0 23 0 26 
		0 31 0 44 0 49 0 55 0 60 0;
	setAttr -s 14 ".kit[0:13]"  3 10 10 10 10 10 1 10 
		3 1 10 3 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 10 10 10 10 1 10 
		3 1 10 3 10 3;
	setAttr -s 14 ".kix[6:13]"  1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[6:13]"  0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[6:13]"  1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[6:13]"  0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL499";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 18 ".ktv[0:17]"  0 0 1 -0.7451418112363698 3 -0.84935577295519482 
		7 -0.1585746134420809 12 1.3438858315455851 17 0.18756662142761193 19 -0.22940606671208297 
		20 -0.83918939570766771 23 -1.1633960348876118 26 -0.83918939570766771 31 -0.83918939570766771 
		34 -0.98655918916883756 37 -0.28115390943132335 38 0.020216844540524193 44 -1.0788918907059581 
		49 -0.80105800343421851 55 -0.88189383289525636 60 0;
	setAttr -s 18 ".kit[0:17]"  3 10 10 10 10 10 10 1 
		10 3 1 10 10 10 10 3 10 3;
	setAttr -s 18 ".kot[0:17]"  3 10 10 10 10 10 10 1 
		10 3 1 10 10 10 10 3 10 3;
	setAttr -s 18 ".kix[7:17]"  1 1 1 1 0.33738592267036438 0.13128957152366638 
		0.28073146939277649 0.40767505764961243 1 0.41619980335235596 1;
	setAttr -s 18 ".kiy[7:17]"  0 0 0 0 0.94136643409729004 0.99134403467178345 
		-0.95978635549545288 -0.91312706470489502 0 0.90927320718765259 0;
	setAttr -s 18 ".kox[7:17]"  1 1 1 1 0.33738592267036438 0.13128957152366638 
		0.28073146939277649 0.40767505764961243 1 0.41619980335235596 1;
	setAttr -s 18 ".koy[7:17]"  0 0 0 0 0.94136643409729004 0.99134403467178345 
		-0.95978635549545288 -0.91312706470489502 0 0.90927320718765259 0;
createNode animCurveTL -n "animCurveTL500";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 18 ".ktv[0:17]"  0 0 1 -0.77079710615206054 3 -1.4387340277013532 
		7 -1.9616417996408195 12 -1.362071854551165 17 -2.4707873149910391 19 -2.6876947091314638 
		20 -2.8822808083213034 23 -2.752989495479031 26 -2.8822808083213034 31 -2.8822808083213034 
		34 -2.637631251528493 37 -2.2079634360656 38 -2.0515203889887137 44 -1.8361037332990828 
		49 -1.9373142083231683 55 -1.0142058776758798 60 0;
	setAttr -s 18 ".kit[0:17]"  3 10 10 10 10 10 10 1 
		10 3 1 10 10 10 10 3 10 3;
	setAttr -s 18 ".kot[0:17]"  3 10 10 10 10 10 10 1 
		10 3 1 10 10 10 10 3 10 3;
	setAttr -s 18 ".kix[7:17]"  1 1 1 1 0.28435271978378296 0.22182092070579529 
		0.53150677680969238 0.95475912094116211 1 0.18596401810646057 1;
	setAttr -s 18 ".kiy[7:17]"  0 0 0 0 0.95871973037719727 0.97508740425109863 
		0.84705406427383423 0.29738014936447144 0 0.98255658149719238 0;
	setAttr -s 18 ".kox[7:17]"  1 1 1 1 0.28435271978378296 0.22182092070579529 
		0.53150677680969238 0.95475912094116211 1 0.18596401810646057 1;
	setAttr -s 18 ".koy[7:17]"  0 0 0 0 0.95871973037719727 0.97508740425109863 
		0.84705406427383423 0.29738014936447144 0 0.98255658149719238 0;
createNode animCurveTL -n "animCurveTL501";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 18 ".ktv[0:17]"  0 -1.1102230246251565e-016 1 0.5233739595066913 
		3 0.258956146753336 7 -0.55674835596986816 12 0.3573067460702461 17 0.35850410586456605 
		19 0.62602139529846679 20 0.41906838752298109 23 0.42933891062359747 26 0.41906838752298109 
		31 0.41906838752298109 34 0.4532351225813106 37 0.22617290023023112 38 0.13317658156415219 
		44 -0.065451044608235143 49 -1.1686701349751865 55 0.3125195014601222 60 0;
	setAttr -s 18 ".kit[0:17]"  3 10 10 10 10 10 10 1 
		10 3 1 10 10 10 10 3 10 3;
	setAttr -s 18 ".kot[0:17]"  3 10 10 10 10 10 10 1 
		10 3 1 10 10 10 10 3 10 3;
	setAttr -s 18 ".kix[7:17]"  1 1 1 1 1 0.38455542922019958 0.62475085258483887 
		0.27110341191291809 1 0.29935869574546814 1;
	setAttr -s 18 ".kiy[7:17]"  0 0 0 0 0 -0.92310190200805664 -0.78082412481307983 
		-0.96255022287368774 0 0.95414060354232788 0;
	setAttr -s 18 ".kox[7:17]"  1 1 1 1 1 0.38455542922019958 0.62475085258483887 
		0.27110341191291809 1 0.29935869574546814 1;
	setAttr -s 18 ".koy[7:17]"  0 0 0 0 0 -0.92310190200805664 -0.78082412481307983 
		-0.96255022287368774 0 0.95414060354232788 0;
createNode animCurveTA -n "animCurveTA1565";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -44.757110789561033 3 -44.757110789561033 
		7 -44.757110789561033 12 -44.757110789561033 20 -44.757110789561033 21 -44.757110789561033 
		26 -44.757110789561033 31 -44.757110789561033 37 -44.757110789561033 49 -44.757110789561033 
		60 -44.757110789561033;
	setAttr -s 11 ".kit[1:10]"  10 10 10 1 1 3 1 1 
		3 3;
	setAttr -s 11 ".kot[1:10]"  10 10 10 1 1 3 1 1 
		3 3;
	setAttr -s 11 ".kix[0:10]"  0.91005086898803711 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[0:10]"  -0.41449657082557678 0 0 0 0 0 0 0 0 0 
		0;
	setAttr -s 11 ".kox[0:10]"  0.91005092859268188 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[0:10]"  -0.41449645161628723 0 0 0 0 0 0 0 0 0 
		0;
createNode animCurveTA -n "animCurveTA1566";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  4 0;
createNode animCurveTA -n "animCurveTA1567";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  4 0;
createNode animCurveTA -n "animCurveTA1568";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 -27.604588158357807 3 -9.5149775743853393 
		7 -7.8441856676998407 12 -7.8441856676998407 17 39.947964789438451 19 26.269003625337348 
		21 -14.948664602456574 26 -16.988937266982365 31 -14.948664602456574 35 1.5040310429936559 
		38 7.2198512341603527 42 -12.884736862777935 49 -41.195101432828551 55 -5.7018652256433917 
		60 -27.604588158357807;
	setAttr -s 15 ".kit[0:14]"  9 10 10 10 10 10 1 3 
		1 10 10 10 3 10 3;
	setAttr -s 15 ".kot[0:14]"  9 10 10 10 10 10 1 3 
		1 10 10 10 3 10 3;
	setAttr -s 15 ".kix[6:14]"  1 1 1 0.51642322540283203 0.68067032098770142 
		0.3980642557144165 1 0.83962827920913696 1;
	setAttr -s 15 ".kiy[6:14]"  0 0 0 0.85633349418640137 -0.7325899600982666 
		-0.91735756397247314 0 0.54316133260726929 0;
	setAttr -s 15 ".kox[6:14]"  1 1 1 0.51642322540283203 0.68067032098770142 
		0.3980642557144165 1 0.83962827920913696 1;
	setAttr -s 15 ".koy[6:14]"  0 0 0 0.85633349418640137 -0.7325899600982666 
		-0.91735756397247314 0 0.54316133260726929 0;
createNode animCurveTA -n "animCurveTA1569";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 0.70641431476594085 3 -23.706829201490834 
		7 2.9622523588405931 10 -13.483088935428496 12 2.9622523588405931 17 -20.309977754349433 
		19 -17.481320111965001 21 -21.66672391287749 26 -15.441741140433894 31 -21.66672391287749 
		35 -11.785097314729173 38 -23.717052961802111 42 13.432658000040162 49 -0.47150314754174338 
		55 -4.1725000656204907 60 0.70641431476594085;
	setAttr -s 16 ".kit[0:15]"  1 10 10 10 10 10 10 1 
		3 1 10 10 10 3 10 3;
	setAttr -s 16 ".kot[0:15]"  1 10 10 10 10 10 10 1 
		3 1 10 10 10 3 10 3;
	setAttr -s 16 ".kix[0:15]"  0.99487119913101196 0.9860609769821167 
		0.79434710741043091 1 0.89060097932815552 1 1 1 1 1 0.98844319581985474 0.46839228272438049 
		0.67050546407699585 1 0.99843186140060425 1;
	setAttr -s 16 ".kiy[0:15]"  0.10114967077970505 0.16638427972793579 
		0.60746413469314575 0 -0.45478546619415283 0 0 0 0 0 -0.15159183740615845 0.88352066278457642 
		0.741904616355896 0 0.055980812758207321 0;
	setAttr -s 16 ".kox[0:15]"  0.99487125873565674 0.9860609769821167 
		0.79434710741043091 1 0.89060097932815552 1 1 1 1 1 0.98844319581985474 0.46839228272438049 
		0.67050546407699585 1 0.99843186140060425 1;
	setAttr -s 16 ".koy[0:15]"  0.10114962607622147 0.16638427972793579 
		0.60746413469314575 0 -0.45478546619415283 0 0 0 0 0 -0.15159183740615845 0.88352066278457642 
		0.741904616355896 0 0.055980812758207321 0;
createNode animCurveTU -n "animCurveTU501";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 0 1 0 3 0 7 0 13 0 21 0 22 0 23 0 24 
		0 25 0 31 0 34 0 41 0 49 0 55 0 60 0;
	setAttr -s 16 ".kit[0:15]"  3 9 9 9 9 3 3 9 
		9 9 1 9 9 3 1 3;
	setAttr -s 16 ".kot[0:15]"  3 5 5 5 5 3 3 5 
		5 5 1 5 5 3 5 3;
	setAttr -s 16 ".kix[10:15]"  1 1 1 1 1 1;
	setAttr -s 16 ".kiy[10:15]"  0 0 0 0 0 0;
	setAttr -s 16 ".kox[10:15]"  1 0 0 1 0 1;
	setAttr -s 16 ".koy[10:15]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU502";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 3 1 3 3 3 7 3 13 3 21 3 22 3 23 3 24 
		3 25 3 31 3 34 3 41 3 49 3 55 3 60 3;
	setAttr -s 16 ".kit[0:15]"  3 10 10 10 10 3 3 10 
		10 10 1 10 10 3 1 3;
	setAttr -s 16 ".kot[0:15]"  3 10 10 10 10 3 3 10 
		10 10 1 10 10 3 1 3;
	setAttr -s 16 ".kix[10:15]"  1 1 1 1 1 1;
	setAttr -s 16 ".kiy[10:15]"  0 0 0 0 0 0;
	setAttr -s 16 ".kox[10:15]"  1 1 1 1 1 1;
	setAttr -s 16 ".koy[10:15]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU503";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 0 1 0 3 0 7 0 13 0 21 0 22 0 23 0 24 
		0 25 0 31 0 34 0 41 0 49 0 55 0 60 0;
	setAttr -s 16 ".kit[0:15]"  3 10 10 10 10 3 3 10 
		10 10 1 10 10 3 1 3;
	setAttr -s 16 ".kot[0:15]"  3 10 10 10 10 3 3 10 
		10 10 1 10 10 3 1 3;
	setAttr -s 16 ".kix[10:15]"  1 1 1 1 1 1;
	setAttr -s 16 ".kiy[10:15]"  0 0 0 0 0 0;
	setAttr -s 16 ".kox[10:15]"  1 1 1 1 1 1;
	setAttr -s 16 ".koy[10:15]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU504";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 1 1 1 3 1 7 1 13 1 21 1 22 1 23 1 24 
		1 25 1 31 1 34 1 41 1 49 1 55 1 60 1;
	setAttr -s 16 ".kit[0:15]"  3 9 9 9 9 3 3 9 
		9 9 1 9 9 3 1 3;
	setAttr -s 16 ".kot[0:15]"  3 5 5 5 5 3 3 5 
		5 5 1 5 5 3 5 3;
	setAttr -s 16 ".kix[10:15]"  1 1 1 1 1 1;
	setAttr -s 16 ".kiy[10:15]"  0 0 0 0 0 0;
	setAttr -s 16 ".kox[10:15]"  1 0 0 1 0 1;
	setAttr -s 16 ".koy[10:15]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU505";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 0 1 0 3 0 7 0 13 0 21 0 22 0 23 0 24 
		0 25 0 31 0 34 0 41 0 49 0 55 0 60 0;
	setAttr -s 16 ".kit[0:15]"  3 10 10 10 10 3 3 10 
		10 10 1 10 10 3 1 3;
	setAttr -s 16 ".kot[0:15]"  3 10 10 10 10 3 3 10 
		10 10 1 10 10 3 1 3;
	setAttr -s 16 ".kix[10:15]"  1 1 1 1 1 1;
	setAttr -s 16 ".kiy[10:15]"  0 0 0 0 0 0;
	setAttr -s 16 ".kox[10:15]"  1 1 1 1 1 1;
	setAttr -s 16 ".koy[10:15]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1570";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 1 42.247970640831923 3 63.259479996749818 
		7 87.055207074849562 9 143.25116054375536 10 112.2515665803419 11 115.39429199542832 
		13 67.462469328865566 17 74.040108241955778 21 75.73446932698161 22 75.73446932698161 
		23 75.73446932698161 24 75.73446932698161 25 75.73446932698161 31 75.73446932698161 
		34 56.888373782389181 38 77.711080088917129 43 103.50381929024776 46 108.94153253062289 
		49 87.055207074849577 55 61.471570164614867 60 0;
	setAttr -s 22 ".kit[0:21]"  3 10 10 10 10 10 10 10 
		10 3 3 10 10 10 1 1 10 10 10 3 1 3;
	setAttr -s 22 ".kot[0:21]"  3 10 10 10 10 10 10 10 
		10 3 3 10 10 10 1 1 10 10 10 3 1 3;
	setAttr -s 22 ".kix[14:21]"  1 1 0.34596443176269531 0.43945738673210144 
		0.57162392139434814 1 0.17075517773628235 1;
	setAttr -s 22 ".kiy[14:21]"  0 0 0.93824762105941772 0.89826345443725586 
		-0.82051575183868408 0 -0.9853135347366333 0;
	setAttr -s 22 ".kox[14:21]"  1 1 0.34596443176269531 0.43945738673210144 
		0.57162392139434814 1 0.17075517773628235 1;
	setAttr -s 22 ".koy[14:21]"  0 0 0.93824762105941772 0.89826345443725586 
		-0.82051575183868408 0 -0.9853135347366333 0;
createNode animCurveTA -n "animCurveTA1571";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 1 76.195921491839073 3 89.914884239437228 
		7 116.66295173948482 9 101.56975512464227 10 142.07005283281555 11 117.14474544810173 
		13 67.600752835294344 17 103.72659566453522 21 78.070005714415856 22 78.070005714415856 
		23 78.070005714415856 24 78.070005714415856 25 78.070005714415856 31 78.070005714415856 
		34 74.799632765752236 38 72.76906999807251 43 129.05167686340306 46 116.46998741074778 
		49 116.66295173948482 55 88.094508531640685 60 0;
	setAttr -s 22 ".kit[0:21]"  3 10 10 10 10 10 10 10 
		10 3 3 10 10 10 1 1 10 10 10 3 1 3;
	setAttr -s 22 ".kot[0:21]"  3 10 10 10 10 10 10 10 
		10 3 3 10 10 10 1 1 10 10 10 3 1 3;
	setAttr -s 22 ".kix[14:21]"  1 1 1 0.33003389835357666 1 1 0.17870062589645386 
		1;
	setAttr -s 22 ".kiy[14:21]"  0 0 0 0.94396907091140747 0 0 -0.98390352725982666 
		0;
	setAttr -s 22 ".kox[14:21]"  1 1 1 0.33003389835357666 1 1 0.17870062589645386 
		1;
	setAttr -s 22 ".koy[14:21]"  0 0 0 0.94396907091140747 0 0 -0.98390352725982666 
		0;
createNode animCurveTA -n "animCurveTA1572";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 0 1 17.487271316954757 3 -7.0056226002325852 
		7 -118.58851721652434 9 -84.715333393907912 10 -66.334664974189565 11 8.8898861635130171 
		13 32.444800156177109 17 65.827168627875395 21 65.331988259208629 22 65.331988259208629 
		23 65.331988259208629 24 65.331988259208629 25 65.331988259208629 31 65.331988259208629 
		34 69.612289222750078 38 43.255527629493393 43 -53.384770843789603 46 -110.14621603186673 
		49 -118.58851721652434 55 -2.5910712046741158 60 0;
	setAttr -s 22 ".kit[0:21]"  3 10 10 10 10 10 10 10 
		10 3 3 10 10 10 1 1 10 10 10 3 3 3;
	setAttr -s 22 ".kot[0:21]"  3 10 10 10 10 10 10 10 
		10 3 3 10 10 10 1 1 10 10 10 3 3 3;
	setAttr -s 22 ".kix[14:21]"  1 1 0.13840414583683014 0.099110014736652374 
		0.17309117317199707 1 1 1;
	setAttr -s 22 ".kiy[14:21]"  0 0 -0.990375816822052 -0.99507653713226318 
		-0.98490583896636963 0 0 0;
	setAttr -s 22 ".kox[14:21]"  1 1 0.13840414583683014 0.099110014736652374 
		0.17309117317199707 1 1 1;
	setAttr -s 22 ".koy[14:21]"  0 0 -0.990375816822052 -0.99507653713226318 
		-0.98490583896636963 0 0 0;
createNode animCurveTL -n "animCurveTL502";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 2.2204460492503131e-016 1 -0.65959603391477073 
		3 -0.24453272919671132 7 0.17617071220977387 9 -0.34874300091565541 10 -0.57586888010587767 
		13 -1.2699005135307004 17 -1.9894294293280348 21 -1.8974870430082791 22 -1.9380448707994216 
		23 -1.9382170085137118 24 -1.9382170085137118 25 -1.9382170085137118 31 -1.9382170085137118 
		34 -1.7293627336495223 38 -1.4525897026369528 41 -1.0198861575186917 46 -0.097075584791979919 
		49 0.17617071220977387 55 -0.60867492548054869 60 0;
	setAttr -s 21 ".kit[0:20]"  3 10 10 10 10 10 10 10 
		3 3 10 10 10 1 10 10 10 10 3 1 3;
	setAttr -s 21 ".kot[0:20]"  3 10 10 10 10 10 10 10 
		3 3 10 10 10 1 10 10 10 10 3 1 3;
	setAttr -s 21 ".kix[13:20]"  1 0.43308138847351074 0.31241866946220398 
		0.19302754104137421 0.21761178970336914 1 0.32040885090827942 1;
	setAttr -s 21 ".kiy[13:20]"  0 0.90135484933853149 0.94994443655014038 
		0.98119336366653442 0.97603535652160645 0 -0.94727939367294312 0;
	setAttr -s 21 ".kox[13:20]"  1 0.43308138847351074 0.31241866946220398 
		0.19302754104137421 0.21761178970336914 1 0.32040885090827942 1;
	setAttr -s 21 ".koy[13:20]"  0 0.90135484933853149 0.94994443655014038 
		0.98119336366653442 0.97603535652160645 0 -0.94727939367294312 0;
createNode animCurveTL -n "animCurveTL503";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 0 1 0.67320580666617424 3 1.2845164352671781 
		7 1.1534184542082386 9 1.2878220035331316 10 1.1443111273770119 13 0.013416965388726948 
		17 -0.14015193458251951 21 0.82647797429037406 22 0.76244552304385649 23 0.76217375307001167 
		24 0.76217375307001167 25 0.76217375307001167 31 0.76217375307001167 34 0.73503410355895393 
		38 0.50850255647963771 41 0.94410804036208151 46 1.2482087351386226 49 1.1534184542082386 
		55 0.77128249179151698 60 0;
	setAttr -s 21 ".kit[0:20]"  3 10 10 10 10 10 10 10 
		3 3 10 10 10 1 10 10 10 10 3 1 3;
	setAttr -s 21 ".kot[0:20]"  3 10 10 10 10 10 10 10 
		3 3 10 10 10 1 10 10 10 10 3 1 3;
	setAttr -s 21 ".kix[13:20]"  1 1 0.744762122631073 0.33913871645927429 
		0.78662407398223877 1 0.28371071815490723 1;
	setAttr -s 21 ".kiy[13:20]"  0 0 0.66733002662658691 0.94073635339736938 
		0.61743229627609253 0 -0.95890992879867554 0;
	setAttr -s 21 ".kox[13:20]"  1 1 0.744762122631073 0.33913871645927429 
		0.78662407398223877 1 0.28371071815490723 1;
	setAttr -s 21 ".koy[13:20]"  0 0 0.66733002662658691 0.94073635339736938 
		0.61743229627609253 0 -0.95890992879867554 0;
createNode animCurveTL -n "animCurveTL504";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 4.4408920985006262e-016 1 0.044241712174482514 
		3 -0.32747887119795255 7 -0.55690248271741627 9 -0.60133489327217393 10 -0.53783870501881093 
		13 -0.82071493831133435 17 0.15199816711667383 21 1.7153344626413773 22 1.5950169642805014 
		23 1.5945063062821572 24 1.5945063062821572 25 1.5945063062821572 31 1.5945063062821572 
		34 1.38498606247564 38 0.37397334736892263 40 0.15271692102048506 46 -0.59030444775860957 
		49 -0.55690248271741627 55 0.068323522064654141 60 0;
	setAttr -s 21 ".kit[0:20]"  3 10 10 10 10 10 10 10 
		3 3 10 10 10 1 10 10 10 10 3 1 3;
	setAttr -s 21 ".kot[0:20]"  3 10 10 10 10 10 10 10 
		3 3 10 10 10 1 10 10 10 10 3 1 3;
	setAttr -s 21 ".kix[13:20]"  1 0.18777284026145935 0.16020588576793671 
		0.26654103398323059 1 1 0.21755437552928925 1;
	setAttr -s 21 ".kiy[13:20]"  0 -0.98221248388290405 -0.98708361387252808 
		-0.96382355690002441 0 0 0.97604823112487793 0;
	setAttr -s 21 ".kox[13:20]"  1 0.18777284026145935 0.16020588576793671 
		0.26654103398323059 1 1 0.21755437552928925 1;
	setAttr -s 21 ".koy[13:20]"  0 -0.98221248388290405 -0.98708361387252808 
		-0.96382355690002441 0 0 0.97604823112487793 0;
createNode animCurveTU -n "animCurveTU506";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 3 1 7 1 14 1 16 1 21 1 26 1 33 1 38 
		1 54 1 60 1;
	setAttr -s 11 ".kit[0:10]"  9 10 10 10 10 10 3 1 
		10 10 3;
	setAttr -s 11 ".kot[0:10]"  9 10 10 10 10 10 3 1 
		10 10 3;
	setAttr -s 11 ".kix[7:10]"  1 1 1 1;
	setAttr -s 11 ".kiy[7:10]"  0 0 0 0;
	setAttr -s 11 ".kox[7:10]"  1 1 1 1;
	setAttr -s 11 ".koy[7:10]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1573";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 1.1288109940741509 3 -54.739118772427645 
		7 -77.471117349469253 10 -32.720578845690866 14 -22.915757420087704 16 -21.651815496736589 
		21 -17.552105223223801 23 -13.703483761767922 26 -21.445779971989115 33 -21.445779971989115 
		38 -9.5446562386730278 54 -10.33178906818039 60 1.1288109940741509;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 10 10 10 10 
		3 1 10 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 10 10 10 10 
		3 1 10 10 3;
	setAttr -s 13 ".kix[9:12]"  1 1 1 1;
	setAttr -s 13 ".kiy[9:12]"  0 0 0 0;
	setAttr -s 13 ".kox[9:12]"  1 1 1 1;
	setAttr -s 13 ".koy[9:12]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA1574";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 4.8219581414201906 3 -17.765413951914681 
		7 -40.845204239957766 10 -24.148261464994917 14 -7.728185789632386 16 1.4201308402684929 
		21 6.1565311688718731 23 6.7980560414408071 26 7.3695227270431047 33 7.3695227270431047 
		38 1.2004403056554629 54 -3.8533922974249215 60 4.8219581414201906;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 10 10 10 10 
		3 1 10 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 10 10 10 10 
		3 1 10 10 3;
	setAttr -s 13 ".kix[9:12]"  1 0.96300792694091797 0.99630606174468994 
		1;
	setAttr -s 13 ".kiy[9:12]"  0 -0.26947277784347534 0.085873536765575409 
		0;
	setAttr -s 13 ".kox[9:12]"  1 0.96300792694091797 0.99630606174468994 
		1;
	setAttr -s 13 ".koy[9:12]"  0 -0.26947277784347534 0.085873536765575409 
		0;
createNode animCurveTA -n "animCurveTA1575";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 28.08558650754679 3 29.403998116001137 
		7 26.320131100880506 10 -1.2212580403480309 14 -8.5183410848617775 16 8.2879316726228875 
		21 36.564533244385196 23 31.3537644454949 26 28.493881457748252 33 28.493881457748252 
		38 10.443353588722058 54 37.084028286023852 60 28.08558650754679;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 10 10 10 10 
		3 1 10 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 10 10 10 10 
		3 1 10 10 3;
	setAttr -s 13 ".kix[9:12]"  1 0.97782349586486816 0.92202019691467285 
		1;
	setAttr -s 13 ".kiy[9:12]"  0 0.20943073928356171 0.38714167475700378 
		0;
	setAttr -s 13 ".kox[9:12]"  1 0.97782349586486816 0.92202019691467285 
		1;
	setAttr -s 13 ".koy[9:12]"  0 0.20943073928356171 0.38714167475700378 
		0;
createNode animCurveTU -n "animCurveTU507";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1576";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 68.629003384766676 3 68.629003384766676 
		7 68.629003384766676 12 68.629003384766676 20 68.629003384766676 21 68.629003384766676 
		26 68.629003384766676 31 68.629003384766676 37 68.629003384766676 49 68.629003384766676 
		60 68.629003384766676;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1577";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 5.1251585428584878 3 5.1251585428584878 
		7 5.1251585428584878 12 5.1251585428584878 20 5.1251585428584878 21 5.1251585428584878 
		26 5.1251585428584878 31 5.1251585428584878 37 5.1251585428584878 49 5.1251585428584878 
		60 5.1251585428584878;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1578";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -1.4794141658124507 3 -1.4794141658124507 
		7 -1.4794141658124507 12 -1.4794141658124507 20 -1.4794141658124507 21 -1.4794141658124507 
		26 -1.4794141658124507 31 -1.4794141658124507 37 -1.4794141658124507 49 -1.4794141658124507 
		60 -1.4794141658124507;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1579";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 2.9967431843380723 3 2.9967431843380723 
		7 2.9967431843380723 12 2.9967431843380723 20 2.9967431843380723 21 2.9967431843380723 
		26 2.9967431843380723 31 2.9967431843380723 37 2.9967431843380723 49 2.9967431843380723 
		60 2.9967431843380723;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1580";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 27.356153209428296 3 27.356153209428296 
		7 27.356153209428296 12 27.356153209428296 20 27.356153209428296 21 27.356153209428296 
		26 27.356153209428296 31 27.356153209428296 37 27.356153209428296 49 27.356153209428296 
		60 27.356153209428296;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1581";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 4.8891453517792058 3 4.8891453517792058 
		7 4.8891453517792058 12 4.8891453517792058 20 4.8891453517792058 21 4.8891453517792058 
		26 4.8891453517792058 31 4.8891453517792058 37 4.8891453517792058 49 4.8891453517792058 
		60 4.8891453517792058;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU508";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1582";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 59.032884886088816 3 59.032884886088816 
		7 59.032884886088816 12 59.032884886088816 20 59.032884886088816 21 59.032884886088816 
		26 59.032884886088816 31 59.032884886088816 37 59.032884886088816 49 59.032884886088816 
		60 59.032884886088816;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1583";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1584";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1585";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 61.945270723308987 3 61.945270723308987 
		7 61.945270723308987 12 61.945270723308987 20 61.945270723308987 21 61.945270723308987 
		26 61.945270723308987 31 61.945270723308987 37 61.945270723308987 49 61.945270723308987 
		60 61.945270723308987;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1586";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1587";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU509";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1588";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 59.032884886088816 3 59.032884886088816 
		7 59.032884886088816 12 59.032884886088816 20 59.032884886088816 21 59.032884886088816 
		26 59.032884886088816 31 59.032884886088816 37 59.032884886088816 49 59.032884886088816 
		60 59.032884886088816;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1589";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1590";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1591";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 61.945270723308987 3 61.945270723308987 
		7 61.945270723308987 12 61.945270723308987 20 61.945270723308987 21 61.945270723308987 
		26 61.945270723308987 31 61.945270723308987 37 61.945270723308987 49 61.945270723308987 
		60 61.945270723308987;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1592";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1593";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU510";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1594";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 59.032884886088816 3 59.032884886088816 
		7 59.032884886088816 12 59.032884886088816 20 59.032884886088816 21 59.032884886088816 
		26 59.032884886088816 31 59.032884886088816 37 59.032884886088816 49 59.032884886088816 
		60 59.032884886088816;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1595";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1596";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1597";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 72.878304588436421 3 72.878304588436421 
		7 72.878304588436421 12 72.878304588436421 20 72.878304588436421 21 72.878304588436421 
		26 72.878304588436421 31 72.878304588436421 37 72.878304588436421 49 72.878304588436421 
		60 72.878304588436421;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1598";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1599";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU511";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1600";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 77.67986202714836 3 77.67986202714836 
		7 77.67986202714836 12 77.67986202714836 20 77.67986202714836 21 77.67986202714836 
		26 77.67986202714836 31 77.67986202714836 37 77.67986202714836 49 77.67986202714836 
		60 77.67986202714836;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1601";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1602";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1603";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 65.952779168408995 3 65.952779168408995 
		7 65.952779168408995 12 65.952779168408995 20 65.952779168408995 21 65.952779168408995 
		26 65.952779168408995 31 65.952779168408995 37 65.952779168408995 49 65.952779168408995 
		60 65.952779168408995;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1604";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 12.091864976351665 3 12.091864976351665 
		7 12.091864976351665 12 12.091864976351665 20 12.091864976351665 21 12.091864976351665 
		26 12.091864976351665 31 12.091864976351665 37 12.091864976351665 49 12.091864976351665 
		60 12.091864976351665;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1605";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -6.5683373417752975 3 -6.5683373417752975 
		7 -6.5683373417752975 12 -6.5683373417752975 20 -6.5683373417752975 21 -6.5683373417752975 
		26 -6.5683373417752975 31 -6.5683373417752975 37 -6.5683373417752975 49 -6.5683373417752975 
		60 -6.5683373417752975;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1606";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 3 0 7 0 12 -1.8376917233715468 21 5.7973529124519319 
		26 5.7973529124519319 31 5.7973529124519319 34 -8.2123521404807498 37 -6.5274419403882016 
		41 -3.5227312104019357 44 0 49 0 60 0;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 1 1 1 10 
		1 10 1 3 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 1 1 1 10 
		1 10 1 3 3;
	setAttr -s 13 ".kix[4:12]"  1 1 1 1 0.65968233346939087 0.89861029386520386 
		1 1 1;
	setAttr -s 13 ".kiy[4:12]"  0 0 0 0 0.75154459476470947 0.43874779343605042 
		0 0 0;
	setAttr -s 13 ".kox[4:12]"  1 1 1 1 0.65968233346939087 0.89861029386520386 
		1 1 1;
	setAttr -s 13 ".koy[4:12]"  0 0 0 0 0.75154459476470947 0.43874779343605042 
		0 0 0;
createNode animCurveTA -n "animCurveTA1607";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 3 0 7 0 12 15.918719287959572 21 40.276434349292877 
		26 40.276434349292877 31 40.276434349292877 34 45.534421939718875 37 21.020483796034181 
		41 19.240754912155321 44 0 49 0 60 0;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 1 1 1 10 
		1 10 1 3 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 1 1 1 10 
		1 10 1 3 3;
	setAttr -s 13 ".kix[4:12]"  1 1 1 0.51139432191848755 0.2629774808883667 
		1 1 1 1;
	setAttr -s 13 ".kiy[4:12]"  0 0 0 -0.85934615135192871 -0.96480196714401245 
		0 0 0 0;
	setAttr -s 13 ".kox[4:12]"  1 1 1 0.51139432191848755 0.2629774808883667 
		1 1 1 1;
	setAttr -s 13 ".koy[4:12]"  0 0 0 -0.85934615135192871 -0.96480196714401245 
		0 0 0 0;
createNode animCurveTA -n "animCurveTA1608";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 3 0 7 0 12 8.4642709270099044 21 31.475241017034776 
		26 31.475241017034776 31 31.475241017034776 34 28.39950570120952 37 14.269769163524355 
		41 10.977516481270939 44 0 49 0 60 0;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 1 1 1 10 
		1 10 1 3 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 1 1 1 10 
		1 10 1 3 3;
	setAttr -s 13 ".kix[4:12]"  1 1 1 0.55432653427124023 0.37260562181472778 
		0.68369907140731812 1 1 1;
	setAttr -s 13 ".kiy[4:12]"  0 0 0 -0.83229929208755493 -0.92798984050750732 
		-0.72976404428482056 0 0 0;
	setAttr -s 13 ".kox[4:12]"  1 1 1 0.55432653427124023 0.37260562181472778 
		0.68369907140731812 1 1 1;
	setAttr -s 13 ".koy[4:12]"  0 0 0 -0.83229929208755493 -0.92798984050750732 
		-0.72976404428482056 0 0 0;
createNode animCurveTU -n "animCurveTU512";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 7 0 10 0 20 0 21 0 26 0 31 0 37 
		0 49 0 51 0 60 0;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kix[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[4:11]"  0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[4:11]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1609";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 7 0 10 32.646328135945431 20 32.646328135945431 
		21 32.646328135945431 26 32.646328135945431 31 32.646328135945431 37 32.646328135945431 
		49 32.646328135945431 51 0 60 0;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kix[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[4:11]"  0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[4:11]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1610";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 7 0 10 0 20 0 21 0 26 0 31 0 37 
		0 49 0 51 0 60 0;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kix[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[4:11]"  0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[4:11]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1611";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 7 0 10 0 20 0 21 0 26 0 31 0 37 
		0 49 0 51 0 60 0;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kix[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[4:11]"  0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[4:11]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1612";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 7 0 10 0 20 0 21 0 26 0 31 0 37 
		0 49 0 51 0 60 0;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kix[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[4:11]"  0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[4:11]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1613";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 7 0 10 0 20 0 21 0 26 0 31 0 37 
		0 49 0 51 0 60 0;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kix[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[4:11]"  0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[4:11]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1614";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 7 0 10 0 20 0 21 0 26 0 31 0 37 
		0 49 0 51 0 60 0;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kix[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[4:11]"  0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[4:11]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU513";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 3 0 7 0 10 0 20 0 21 0 23 0 27 0 31 
		0 37 0 49 0 51 0 60 0;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kix[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[4:12]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[4:12]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1615";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 3 0 7 0 10 51.856152857436655 20 51.856152857436655 
		21 74.621289666227057 23 51.856152857436655 27 52.834343999322861 31 74.621289666227057 
		37 51.856152857436655 49 51.856152857436655 51 0 60 0;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kix[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[4:12]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[4:12]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1616";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 3 0 7 0 10 0 20 0 21 0 23 0 27 0 31 
		0 37 0 49 0 51 0 60 0;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kix[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[4:12]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[4:12]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1617";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 3 0 7 0 10 0 20 0 21 0 23 0 27 0 31 
		0 37 0 49 0 51 0 60 0;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kix[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[4:12]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[4:12]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1618";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 7 0 10 61.564909269022749 20 61.564909269022749 
		21 61.564909269022749 26 61.564909269022749 31 61.564909269022749 37 61.564909269022749 
		49 61.564909269022749 51 0 60 0;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kix[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[4:11]"  0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[4:11]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1619";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 7 0 10 0 20 0 21 0 26 0 31 0 37 
		0 49 0 51 0 60 0;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kix[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[4:11]"  0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[4:11]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1620";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 7 0 10 0 20 0 21 0 26 0 31 0 37 
		0 49 0 51 0 60 0;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kix[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[4:11]"  0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[4:11]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU514";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 3 0 7 0 10 0 20 0 21 0 23 0 27 0 31 
		0 37 0 49 0 51 0 60 0;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kix[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[4:12]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[4:12]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1621";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 3 0 7 0 10 51.856152857436655 20 51.856152857436655 
		21 74.621289666227057 23 51.856152857436655 27 52.834343999322861 31 74.621289666227057 
		37 51.856152857436655 49 51.856152857436655 51 0 60 0;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kix[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[4:12]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[4:12]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1622";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 3 0 7 0 10 0 20 0 21 0 23 0 27 0 31 
		0 37 0 49 0 51 0 60 0;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kix[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[4:12]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[4:12]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1623";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 3 0 7 0 10 0 20 0 21 0 23 0 27 0 31 
		0 37 0 49 0 51 0 60 0;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kix[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[4:12]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[4:12]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1624";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 7 0 10 61.564909269022749 20 61.564909269022749 
		21 61.564909269022749 26 61.564909269022749 31 61.564909269022749 37 61.564909269022749 
		49 61.564909269022749 51 0 60 0;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kix[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[4:11]"  0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[4:11]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1625";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 7 0 10 0 20 0 21 0 26 0 31 0 37 
		0 49 0 51 0 60 0;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kix[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[4:11]"  0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[4:11]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1626";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 7 0 10 0 20 0 21 0 26 0 31 0 37 
		0 49 0 51 0 60 0;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kix[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[4:11]"  0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[4:11]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU515";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 3 0 7 0 10 0 20 0 21 0 23 0 27 0 31 
		0 37 0 49 0 51 0 60 0;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kix[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[4:12]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[4:12]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1627";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 3 0 7 0 10 51.856152857436655 20 51.856152857436655 
		21 74.621289666227057 23 51.856152857436655 27 52.834343999322861 31 74.621289666227057 
		37 51.856152857436655 49 51.856152857436655 51 0 60 0;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kix[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[4:12]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[4:12]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1628";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 3 0 7 0 10 0 20 0 21 0 23 0 27 0 31 
		0 37 0 49 0 51 0 60 0;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kix[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[4:12]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[4:12]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1629";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 3 0 7 0 10 0 20 0 21 0 23 0 27 0 31 
		0 37 0 49 0 51 0 60 0;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kix[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[4:12]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[4:12]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1630";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 7 0 10 82.662858912048875 20 82.662858912048875 
		21 82.662858912048875 26 82.662858912048875 31 82.662858912048875 37 82.662858912048875 
		49 82.662858912048875 51 0 60 0;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kix[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[4:11]"  0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[4:11]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1631";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 7 0 10 0 20 0 21 0 26 0 31 0 37 
		0 49 0 51 0 60 0;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kix[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[4:11]"  0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[4:11]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1632";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 7 0 10 0 20 0 21 0 26 0 31 0 37 
		0 49 0 51 0 60 0;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kix[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[4:11]"  0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[4:11]"  0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU516";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 3 0 7 0 10 0 20 0 21 0 23 0 27 0 31 
		0 37 0 49 0 51 0 60 0;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kix[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[4:12]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[4:12]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1633";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 3 0 7 0 10 51.856152857436655 20 51.856152857436655 
		21 74.621289666227057 23 51.856152857436655 27 52.834343999322861 31 74.621289666227057 
		37 51.856152857436655 49 51.856152857436655 51 0 60 0;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kix[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[4:12]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[4:12]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1634";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 3 0 7 0 10 0 20 0 21 0 23 0 27 0 31 
		0 37 0 49 0 51 0 60 0;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kix[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[4:12]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[4:12]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1635";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 3 0 7 0 10 0 20 0 21 0 23 0 27 0 31 
		0 37 0 49 0 51 0 60 0;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 1 1 1 10 
		1 1 3 10 3;
	setAttr -s 13 ".kix[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[4:12]"  0 0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[4:12]"  1 1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[4:12]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1636";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 7 0 10 82.662858912048875 20 82.662858912048875 
		21 82.662858912048875 26 82.662858912048875 31 82.662858912048875 37 82.662858912048875 
		49 82.662858912048875 51 0 60 0;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kix[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[4:11]"  0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[4:11]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1637";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 7 0 10 0 20 0 21 0 26 0 31 0 37 
		0 49 0 51 0 60 0;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kix[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[4:11]"  0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[4:11]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1638";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 7 0 10 0 20 0 21 0 26 0 31 0 37 
		0 49 0 51 0 60 0;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 1 1 1 1 
		1 3 10 3;
	setAttr -s 12 ".kix[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[4:11]"  0 0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[4:11]"  1 1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[4:11]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1639";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 32 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1640";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 32 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1641";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 32 0 38 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU517";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 7 0 12 0 19 0 21 0 26 0 31 0 38 
		0 45 0 49 0 60 0;
	setAttr -s 12 ".kit[1:11]"  9 9 9 9 1 3 1 9 
		1 3 3;
	setAttr -s 12 ".kot[1:11]"  5 5 5 5 1 3 1 9 
		1 3 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU518";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 7 0 12 0 19 0 21 0 26 0 31 0 38 
		0 45 0 49 0 60 0;
	setAttr -s 12 ".kit[1:11]"  9 9 9 9 1 3 1 9 
		1 3 3;
	setAttr -s 12 ".kot[1:11]"  5 5 5 5 1 3 1 9 
		1 3 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU519";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 1 3 1 7 1 12 1 19 1 21 1 26 1 31 1 38 
		1 45 1 49 1 60 1;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 1 3 1 
		9 1 3 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 1 3 1 
		9 1 3 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1642";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -10.173354040024311 3 -10.173354040024311 
		7 -10.173354040024311 12 -10.173354040024311 19 -46.45850884223416 21 -51.699064951815494 
		26 -51.699064951815494 31 -51.699064951815494 38 -10.173354040024313 45 -10.173354040024311 
		49 -10.173354040024311 60 -10.173354040024311;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 1 3 1 
		9 1 3 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 1 3 1 
		9 1 3 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 0.54137247800827026 1 1 1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0.84078282117843628 0 0 0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 0.54137247800827026 1 1 1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0.84078282117843628 0 0 0;
createNode animCurveTA -n "animCurveTA1643";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 7 0 12 0 19 -40.439405226971076 
		21 -46.279947269170997 26 -46.279947269170997 31 -46.279947269170997 38 0 45 0 49 
		0 60 0;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 1 3 1 
		9 1 3 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 1 3 1 
		9 1 3 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 0.50025665760040283 1 1 1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0.86587715148925781 0 0 0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 0.50025665760040283 1 1 1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0.86587715148925781 0 0 0;
createNode animCurveTA -n "animCurveTA1644";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 3 0 7 0 12 19.890921912256175 19 107.88606745181217 
		21 117.28088317151287 26 117.28088317151287 31 117.28088317151287 38 52.184713538943832 
		41 29.001755220659156 45 0 49 0 60 0;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 10 1 3 1 
		9 9 1 3 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 10 1 3 1 
		9 9 1 3 3;
	setAttr -s 13 ".kix[5:12]"  1 1 1 0.21145142614841461 0.24817192554473877 
		1 1 1;
	setAttr -s 13 ".kiy[5:12]"  0 0 0 -0.97738856077194214 -0.96871602535247803 
		0 0 0;
	setAttr -s 13 ".kox[5:12]"  1 1 1 0.21145142614841461 0.24817192554473877 
		1 1 1;
	setAttr -s 13 ".koy[5:12]"  0 0 0 -0.97738856077194214 -0.96871602535247803 
		0 0 0;
createNode animCurveTL -n "animCurveTL505";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 0 3 0 7 0 12 0.11219082499145633 15 0.40850166158055223 
		16 0.47965984072707413 19 0.53079077835766619 21 0.51259389704126757 26 0.51259389704126757 
		31 0.51259389704126757 38 0.40004183588245806 41 0.19284228212219487 45 0 49 0 60 
		0;
	setAttr -s 15 ".kit[0:14]"  3 10 10 10 10 10 10 1 
		3 1 9 9 1 3 3;
	setAttr -s 15 ".kot[0:14]"  3 10 10 10 10 10 10 1 
		3 1 9 9 1 3 3;
	setAttr -s 15 ".kix[7:14]"  1 1 1 0.72165596485137939 0.50383174419403076 
		1 1 1;
	setAttr -s 15 ".kiy[7:14]"  0 0 0 -0.69225186109542847 -0.86380183696746826 
		0 0 0;
	setAttr -s 15 ".kox[7:14]"  1 1 1 0.72165596485137939 0.50383174419403076 
		1 1 1;
	setAttr -s 15 ".koy[7:14]"  0 0 0 -0.69225186109542847 -0.86380183696746826 
		0 0 0;
createNode animCurveTL -n "animCurveTL506";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0.643246524321337 3 0.643246524321337 
		7 0.643246524321337 12 0.643246524321337 19 0.25994501625972405 21 0.20458592875318016 
		26 0.20458592875318016 31 0.20458592875318016 38 0.58611161178547566 41 0.64777507083016939 
		45 0.643246524321337 49 0.643246524321337 60 0.643246524321337;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 10 1 3 1 
		9 9 1 3 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 10 1 3 1 
		9 9 1 3 3;
	setAttr -s 13 ".kix[5:12]"  1 1 1 0.60108602046966553 0.97130495309829712 
		1 1 1;
	setAttr -s 13 ".kiy[5:12]"  0 0 0 0.79918432235717773 0.23783750832080841 
		0 0 0;
	setAttr -s 13 ".kox[5:12]"  1 1 1 0.60108602046966553 0.97130495309829712 
		1 1 1;
	setAttr -s 13 ".koy[5:12]"  0 0 0 0.79918432235717773 0.23783750832080841 
		0 0 0;
createNode animCurveTL -n "animCurveTL507";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0.10481400598920043 3 0.10481400598920043 
		7 0.10481400598920043 12 0.10481400598920043 19 0.070658759977924993 21 0.065725820208635599 
		26 0.065725820208635599 31 0.065725820208635599 38 0.10737795643447266 41 0.10070796154540126 
		45 0.10481400598920043 49 0.10481400598920043 60 0.10481400598920043;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 10 1 3 1 
		9 9 1 3 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 10 1 3 1 
		9 9 1 3 3;
	setAttr -s 13 ".kix[5:12]"  1 1 1 0.99453812837600708 0.9999396800994873 
		1 1 1;
	setAttr -s 13 ".kiy[5:12]"  0 0 0 0.10437320917844772 -0.010987695306539536 
		0 0 0;
	setAttr -s 13 ".kox[5:12]"  1 1 1 0.99453812837600708 0.9999396800994873 
		1 1 1;
	setAttr -s 13 ".koy[5:12]"  0 0 0 0.10437320917844772 -0.010987695306539536 
		0 0 0;
createNode animCurveTA -n "animCurveTA1645";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1646";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1647";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU520";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1648";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1649";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1650";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1651";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1652";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1653";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1654";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1655";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1656";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU521";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 3 1 7 1 12 1 17 1 21 1 26 1 31 1 37 
		1 52 1 60 1;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 10 1 3 1 
		1 1 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 10 1 3 1 
		1 1 3;
	setAttr -s 11 ".kix[5:10]"  1 1 1 1 1 1;
	setAttr -s 11 ".kiy[5:10]"  0 0 0 0 0 0;
	setAttr -s 11 ".kox[5:10]"  1 1 1 1 1 1;
	setAttr -s 11 ".koy[5:10]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1657";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 40.718223104721211 3 40.718223104721211 
		7 24.747986792355729 12 39.05877626837524 17 31.422866570443322 21 15.385264890958146 
		26 15.385264890958146 31 15.385264890958146 37 48.854399931698993 46 33.9612833025027 
		52 23.514100394338559 60 40.718223104721211;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 1 3 1 
		1 10 1 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 1 3 1 
		1 10 1 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 1 0.74902337789535522 0.99883699417114258 
		1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0 -0.66254359483718872 -0.04821520671248436 
		0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 1 0.74902337789535522 0.99883699417114258 
		1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0 -0.66254359483718872 -0.04821520671248436 
		0;
createNode animCurveTA -n "animCurveTA1658";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -38.301705751263519 3 -38.301705751263519 
		7 -58.978785055179344 12 -29.324040639727556 17 -43.687530170686003 21 -44.810097447739011 
		26 -44.810097447739011 31 -44.810097447739011 37 -41.732924810201759 46 -47.876016169064066 
		52 -44.327465418235562 60 -38.301705751263519;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 1 3 1 
		1 10 1 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 1 3 1 
		1 10 1 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 1 0.99592387676239014 0.96755099296569824 
		1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0 -0.09019739180803299 0.2526756227016449 
		0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 1 0.99592387676239014 0.96755099296569824 
		1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0 -0.09019739180803299 0.2526756227016449 
		0;
createNode animCurveTA -n "animCurveTA1659";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 21.733945627788874 3 21.733945627788874 
		7 16.051147530530582 12 8.6990295573924694 17 -0.21549974631624569 21 13.682061935066033 
		26 13.682061935066033 31 13.682061935066033 37 -10.344141019660622 46 -2.1382662148560896 
		52 15.484134095117488 60 21.733945627788874;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 1 3 1 
		1 10 1 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 1 3 1 
		1 10 1 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 1 0.74271154403686523 0.93504089117050171 
		1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0 0.66961151361465454 -0.35453978180885315 
		0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 1 0.74271154403686523 0.93504089117050171 
		1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0 0.66961151361465454 -0.35453978180885315 
		0;
createNode animCurveTU -n "animCurveTU522";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 3 0 7 0 10 0 12 0 16 0 20 0 21 0 26 
		0 34 0 38 0 40 0 44 0 60 0;
	setAttr -s 14 ".kit[0:13]"  3 9 9 1 9 1 1 1 
		3 1 1 1 1 3;
	setAttr -s 14 ".kot[0:13]"  3 5 5 5 5 1 1 1 
		3 1 1 1 5 3;
	setAttr -s 14 ".kix[3:13]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[3:13]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[5:13]"  1 1 1 1 1 1 1 0 1;
	setAttr -s 14 ".koy[5:13]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU523";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 3 0 7 0 10 0 12 0 16 0 20 0 21 0 26 
		0 34 0 38 0 40 0 44 0 60 0;
	setAttr -s 14 ".kit[0:13]"  3 9 9 1 9 1 1 1 
		3 1 1 1 1 3;
	setAttr -s 14 ".kot[0:13]"  3 5 5 5 5 1 1 1 
		3 1 1 1 5 3;
	setAttr -s 14 ".kix[3:13]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[3:13]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[5:13]"  1 1 1 1 1 1 1 0 1;
	setAttr -s 14 ".koy[5:13]"  0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU524";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 1 3 1 7 1 10 1 12 1 16 1 20 1 21 1 26 
		1 34 1 38 1 40 1 44 1 60 1;
	setAttr -s 14 ".kit[0:13]"  3 10 10 1 10 1 1 1 
		3 1 1 1 1 3;
	setAttr -s 14 ".kot[0:13]"  3 10 10 1 10 1 1 1 
		3 1 1 1 1 3;
	setAttr -s 14 ".kix[3:13]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[3:13]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[3:13]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[3:13]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1660";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 17.962181958626559 3 17.962181958626559 
		7 17.962181958626559 10 17.962181958626559 12 17.962181958626559 15 -8.9974461886921198 
		16 -8.6149990499724947 20 -8.6149990499724947 21 -8.6149990499724947 26 -8.6149990499724947 
		34 -8.6149990499724947 38 -8.6149990499724947 40 -5.7042654420360988 44 17.962181958626559 
		60 17.962181958626559;
	setAttr -s 15 ".kit[0:14]"  3 10 10 1 10 10 1 1 
		1 3 1 1 10 1 3;
	setAttr -s 15 ".kot[0:14]"  3 10 10 1 10 10 1 1 
		1 3 1 1 10 1 3;
	setAttr -s 15 ".kix[3:14]"  1 1 1 1 1 1 1 1 1 0.39593064785003662 1 
		1;
	setAttr -s 15 ".kiy[3:14]"  0 0 0 0 0 0 0 0 0 0.91828042268753052 0 
		0;
	setAttr -s 15 ".kox[3:14]"  1 1 1 1 1 1 1 1 1 0.39593064785003662 1 
		1;
	setAttr -s 15 ".koy[3:14]"  0 0 0 0 0 0 0 0 0 0.91828042268753052 0 
		0;
createNode animCurveTA -n "animCurveTA1661";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 0 3 0 7 0 10 0 12 0 15 8.9356110308510388 
		16 0 20 0 21 0 26 0 34 0 38 0 40 -5.5254626583815405 44 0 60 0;
	setAttr -s 15 ".kit[0:14]"  3 10 10 1 10 10 1 1 
		1 3 1 1 10 1 3;
	setAttr -s 15 ".kot[0:14]"  3 10 10 1 10 10 1 1 
		1 3 1 1 10 1 3;
	setAttr -s 15 ".kix[3:14]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 15 ".kiy[3:14]"  0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 15 ".kox[3:14]"  1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 15 ".koy[3:14]"  0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1662";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 0 3 0 7 0 10 0 12 12.233819257411062 
		15 -8.2491554574126873 16 0 20 0 21 0 26 0 34 0 38 -32.714345428693051 40 -53.879654839847738 
		44 0 60 0;
	setAttr -s 15 ".kit[0:14]"  3 10 10 1 10 10 1 1 
		1 3 1 1 1 1 3;
	setAttr -s 15 ".kot[0:14]"  3 10 10 1 10 10 1 1 
		1 3 1 1 1 1 3;
	setAttr -s 15 ".kix[3:14]"  1 0.75674319267272949 0.52966493368148804 
		1 1 1 1 1 1 1 1 1;
	setAttr -s 15 ".kiy[3:14]"  0 -0.65371227264404297 -0.84820693731307983 
		0 0 0 0 0 0 0 0 0;
	setAttr -s 15 ".kox[3:14]"  1 0.75674319267272949 0.52966493368148804 
		1 1 1 1 1 1 1 1 1;
	setAttr -s 15 ".koy[3:14]"  0 -0.65371227264404297 -0.84820693731307983 
		0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL508";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 0 3 0 7 0 10 0 12 0.15355986913518349 
		15 0.27814885825457492 16 0 20 0 21 0 26 0 34 0 38 0 40 -0.010413539357063906 44 
		0 60 0;
	setAttr -s 15 ".kit[0:14]"  3 10 10 1 10 10 1 1 
		1 3 1 1 1 1 3;
	setAttr -s 15 ".kot[0:14]"  3 10 10 1 10 10 1 1 
		1 3 1 1 1 1 3;
	setAttr -s 15 ".kix[3:14]"  1 0.51399075984954834 0.65562701225280762 
		1 1 1 1 1 1 1 1 1;
	setAttr -s 15 ".kiy[3:14]"  0 0.85779571533203125 -0.75508487224578857 
		0 0 0 0 0 0 0 0 0;
	setAttr -s 15 ".kox[3:14]"  1 0.51399075984954834 0.65562701225280762 
		1 1 1 1 1 1 1 1 1;
	setAttr -s 15 ".koy[3:14]"  0 0.85779571533203125 -0.75508487224578857 
		0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL509";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 -0.64789329560123088 3 -0.64789329560123088 
		7 -0.64789329560123088 10 -0.64789329560123088 12 -0.64789329560123088 16 -1.784764753882466 
		20 -1.784764753882466 21 -1.784764753882466 26 -1.784764753882466 34 -1.784764753882466 
		38 -1.784764753882466 40 -1.6784284845269675 44 -0.64789329560123088 60 -0.64789329560123088;
	setAttr -s 14 ".kit[0:13]"  3 10 10 1 10 1 1 1 
		3 1 1 1 1 3;
	setAttr -s 14 ".kot[0:13]"  3 10 10 1 10 1 1 1 
		3 1 1 1 1 3;
	setAttr -s 14 ".kix[3:13]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[3:13]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[3:13]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[3:13]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL510";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 -0.07395615046270454 3 -0.07395615046270454 
		7 -0.07395615046270454 10 -0.07395615046270454 12 -0.07395615046270454 16 -0.07395615046270454 
		20 -0.07395615046270454 21 -0.07395615046270454 26 -0.07395615046270454 34 -0.07395615046270454 
		38 -0.07395615046270454 40 -0.07395615046270454 44 -0.07395615046270454 60 -0.07395615046270454;
	setAttr -s 14 ".kit[0:13]"  3 10 10 1 10 1 1 1 
		3 1 1 1 1 3;
	setAttr -s 14 ".kot[0:13]"  3 10 10 1 10 1 1 1 
		3 1 1 1 1 3;
	setAttr -s 14 ".kix[3:13]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[3:13]"  0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 14 ".kox[3:13]"  1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[3:13]"  0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1663";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1664";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1665";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU525";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1666";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1667";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1668";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1669";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1670";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1671";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1672";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1673";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1674";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1675";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 -10.753373031419716 3 -57.702332603929889 
		7 -82.945796322910297 12 -33.444055328834821 17 2.4116987568930339 19 -35.083522913800202 
		21 -36.848723884446123 23 -37.389343574825347 26 -45.263240421303486 33 -45.263240421303486 
		38 -14.808950476678904 45 -52.736256335345409 49 -77.726132998222027 54 -21.827515135403374 
		60 -10.753373031419716;
	setAttr -s 15 ".kit[0:14]"  9 10 10 10 10 10 10 10 
		3 1 10 10 3 10 3;
	setAttr -s 15 ".kot[0:14]"  9 10 10 10 10 10 10 10 
		3 1 10 10 3 10 3;
	setAttr -s 15 ".kix[9:14]"  1 0.95073407888412476 0.31671696901321411 
		1 0.2993062436580658 1;
	setAttr -s 15 ".kiy[9:14]"  0 -0.31000763177871704 -0.94852006435394287 
		0 0.95415711402893066 0;
	setAttr -s 15 ".kox[9:14]"  1 0.95073407888412476 0.31671696901321411 
		1 0.2993062436580658 1;
	setAttr -s 15 ".koy[9:14]"  0 -0.31000763177871704 -0.94852006435394287 
		0 0.95415711402893066 0;
createNode animCurveTA -n "animCurveTA1676";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 -4.9387346018875373 3 -13.433190842317826 
		7 -23.327623574459835 12 1.0206172287973914 17 -8.0648758205494389 19 -13.15072578864134 
		21 -14.709963549466226 23 -12.763145630673705 26 -13.071917540030517 33 -13.071917540030517 
		38 -4.5577415385115732 45 -16.668130320263479 49 -22.987591155501953 54 -11.926925617912946 
		60 -4.9387346018875373;
	setAttr -s 15 ".kit[0:14]"  1 10 10 10 10 10 10 10 
		3 1 10 10 3 10 3;
	setAttr -s 15 ".kot[0:14]"  1 10 10 10 10 10 10 10 
		3 1 10 10 3 10 3;
	setAttr -s 15 ".kix[0:14]"  0.99997425079345703 0.58803582191467285 
		0.76536989212036133 0.78119051456451416 0.68621563911437988 1 1 1 1 1 0.98791170120239258 
		0.75173461437225342 1 0.75851380825042725 1;
	setAttr -s 15 ".kiy[0:14]"  0.0071777543053030968 -0.80883485078811646 
		0.64359068870544434 0.62429279088973999 -0.72739815711975098 0 0 0 0 0 -0.15501756966114044 
		-0.65946578979492188 0 0.65165704488754272 0;
	setAttr -s 15 ".kox[0:14]"  0.99997425079345703 0.58803582191467285 
		0.76536989212036133 0.78119051456451416 0.68621563911437988 1 1 1 1 1 0.98791170120239258 
		0.75173461437225342 1 0.75851380825042725 1;
	setAttr -s 15 ".koy[0:14]"  0.0071777533739805222 -0.80883485078811646 
		0.64359068870544434 0.62429279088973999 -0.72739815711975098 0 0 0 0 0 -0.15501756966114044 
		-0.65946578979492188 0 0.65165704488754272 0;
createNode animCurveTA -n "animCurveTA1677";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 22.393157938684443 3 16.440001298404074 
		7 18.456419105874154 12 -7.8921857193239511 17 -5.1654142339502265 19 19.068561336351067 
		21 26.342500843163744 23 23.902064632155586 26 23.22185693638756 33 23.22185693638756 
		38 14.639542472780485 45 15.843409842212782 49 32.481104129726909 54 30.505002630481311 
		60 22.393157938684443;
	setAttr -s 15 ".kit[0:14]"  9 10 10 10 10 10 10 10 
		3 1 10 10 3 10 3;
	setAttr -s 15 ".kot[0:14]"  9 10 10 10 10 10 10 10 
		3 1 10 10 3 10 3;
	setAttr -s 15 ".kix[9:14]"  1 1 1 1 1 1;
	setAttr -s 15 ".kiy[9:14]"  0 0 0 0 0 0;
	setAttr -s 15 ".kox[9:14]"  1 1 1 1 1 1;
	setAttr -s 15 ".koy[9:14]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1678";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  17 -4.0865779949808214 21 -7.9628379855699869 
		23 -5.7011918664567993 26 -4.0865779949808214 31 -4.0865779949808214 39 -25.900216286271565 
		44 -20.212570374092273 49 -4.0865779949808214 55 -0.21574374539485985 60 -4.0865779949808214;
	setAttr -s 10 ".kit[0:9]"  1 1 10 10 10 10 10 10 
		10 1;
	setAttr -s 10 ".kot[0:9]"  1 1 10 10 10 10 10 10 
		10 1;
	setAttr -s 10 ".kix[0:9]"  1 1 1 1 1 0.83863377571105957 0.65873235464096069 
		0.72433114051818848 1 1;
	setAttr -s 10 ".kiy[0:9]"  0 0 0 0 0 -0.54469579458236694 0.75237733125686646 
		0.68945223093032837 0 0;
	setAttr -s 10 ".kox[0:9]"  1 1 1 1 1 0.83863377571105957 0.65873235464096069 
		0.72433114051818848 1 1;
	setAttr -s 10 ".koy[0:9]"  0 0 0 0 0 -0.54469579458236694 0.75237733125686646 
		0.68945223093032837 0 0;
createNode animCurveTA -n "animCurveTA1679";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  17 -10.471027640707172 21 -4.4243341946860397 
		23 -9.6068972907339969 26 -10.471027640707172 31 -10.471027640707172 39 -5.5067169970149914 
		44 -12.985343427427461 49 -10.471027640707172 55 -14.922280966031964 60 -10.471027640707172;
	setAttr -s 10 ".kit[0:9]"  1 1 10 10 10 10 10 10 
		10 1;
	setAttr -s 10 ".kot[0:9]"  1 1 10 10 10 10 10 10 
		10 1;
	setAttr -s 10 ".kix[0:9]"  1 1 1 1 1 0.99491149187088013 1 1 1 1;
	setAttr -s 10 ".kiy[0:9]"  0 0 0 0 0 -0.10075333714485168 0 0 0 0;
	setAttr -s 10 ".kox[0:9]"  1 1 1 1 1 0.99491149187088013 1 1 1 1;
	setAttr -s 10 ".koy[0:9]"  0 0 0 0 0 -0.10075333714485168 0 0 0 0;
createNode animCurveTA -n "animCurveTA1680";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  17 -1.7475532445702493 21 -4.3097761594184281 
		23 -8.4411200091633507 26 -1.7475532445702493 31 -1.7475532445702493 39 -0.49039694837116404 
		44 6.6380709059287204 49 -1.7475532445702493 55 2.5943658644357228 60 -1.7475532445702493;
	setAttr -s 10 ".kit[0:9]"  1 1 10 10 10 10 10 10 
		10 1;
	setAttr -s 10 ".kot[0:9]"  1 1 10 10 10 10 10 10 
		10 1;
	setAttr -s 10 ".kix[0:9]"  1 1 0.96583741903305054 1 1 1 0.9978405237197876 
		0.98197513818740845 1 1;
	setAttr -s 10 ".kiy[0:9]"  0 0 0.2591489851474762 0 0 0 -0.065682396292686462 
		-0.18901048600673676 0 0;
	setAttr -s 10 ".kox[0:9]"  1 1 0.96583741903305054 1 1 1 0.9978405237197876 
		0.98197513818740845 1 1;
	setAttr -s 10 ".koy[0:9]"  0 0 0.2591489851474762 0 0 0 -0.065682396292686462 
		-0.18901048600673676 0 0;
createNode animCurveTU -n "animCurveTU526";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 3 1 7 1 12 1 17 1 21 1 26 1 31 1 37 
		1 52 1 60 1;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 10 1 3 1 
		1 1 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 10 1 3 1 
		1 1 3;
	setAttr -s 11 ".kix[5:10]"  1 1 1 1 1 1;
	setAttr -s 11 ".kiy[5:10]"  0 0 0 0 0 0;
	setAttr -s 11 ".kox[5:10]"  1 1 1 1 1 1;
	setAttr -s 11 ".koy[5:10]"  0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1681";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 20.69101533741409 3 20.69101533741409 
		7 4.8336474338268616 12 12.735169162159774 17 21.502562098250682 21 19.634455373372397 
		26 19.634455373372397 31 19.634455373372397 37 31.347086536556688 46 6.9180686523245143 
		52 14.977243086404677 60 20.69101533741409;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 1 3 1 
		1 10 1 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 1 3 1 
		1 10 1 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 1 0.8682481050491333 0.97425079345703125 
		1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0 -0.49613025784492493 -0.22546713054180145 
		0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 1 0.8682481050491333 0.97425079345703125 
		1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0 -0.49613025784492493 -0.22546713054180145 
		0;
createNode animCurveTA -n "animCurveTA1682";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -8.3978566024888135 3 -8.3978566024888135 
		7 -25.100846610900863 12 1.3540599152275117 17 -15.504786391923442 21 -14.810312400363657 
		26 -14.810312400363657 31 -14.810312400363657 37 -3.0034029131597277 46 -5.48567841838166 
		52 -10.408728379222243 60 -8.3978566024888135;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 1 3 1 
		1 10 1 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 1 3 1 
		1 10 1 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 1 1 0.96204125881195068 1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0 0 0.27290394902229309 0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 1 1 0.96204125881195068 1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0 0 0.27290394902229309 0;
createNode animCurveTA -n "animCurveTA1683";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 2.8255796210686652 3 2.8255796210686652 
		7 6.0372110974914595 12 -7.6363691735810351 17 -21.82815867138822 21 -5.3366987653323941 
		26 -5.3366987653323941 31 -5.3366987653323941 37 -13.677508227252984 46 0.45800109002847433 
		52 6.9931359419615067 60 2.8255796210686652;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 1 3 1 
		1 10 1 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 1 3 1 
		1 10 1 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 1 0.81094115972518921 0.95667976140975952 
		1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0 0.58512777090072632 -0.29114225506782532 
		0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 1 0.81094115972518921 0.95667976140975952 
		1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0 0.58512777090072632 -0.29114225506782532 
		0;
createNode animCurveTU -n "animCurveTU527";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 17 0 26 0 31 0 33 0 44 
		0 49 0 60 0;
	setAttr -s 11 ".kit[1:10]"  10 10 10 1 3 1 1 9 
		3 3;
	setAttr -s 11 ".kot[1:10]"  10 10 10 1 3 1 1 9 
		3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1684";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 0 3 -1.8593327032449962 7 -3.9540625393671047 
		12 -10.223932902155894 17 0 21 -2.8151127547113131 26 0 31 0 33 0 37 16.767536413765658 
		44 1.9162882963388437 49 -1.3899545688552823 54 -0.77828246344617658 57 -0.40519553537586878 
		60 0;
	setAttr -s 15 ".kit[0:14]"  3 10 10 10 1 10 3 1 
		1 10 9 3 10 10 3;
	setAttr -s 15 ".kot[0:14]"  3 10 10 10 1 10 3 1 
		1 10 9 3 10 10 3;
	setAttr -s 15 ".kix[4:14]"  1 1 1 1 1 0.99586570262908936 0.78381562232971191 
		1 1 1 1;
	setAttr -s 15 ".kiy[4:14]"  0 0 0 0 0 0.090838000178337097 -0.62099367380142212 
		0 0 0 0;
	setAttr -s 15 ".kox[4:14]"  1 1 1 1 1 0.99586570262908936 0.78381562232971191 
		1 1 1 1;
	setAttr -s 15 ".koy[4:14]"  0 0 0 0 0 0.090838000178337097 -0.62099367380142212 
		0 0 0 0;
createNode animCurveTA -n "animCurveTA1685";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 0 3 30.360521754527241 7 -22.423684223277569 
		12 31.45903406241862 17 0 21 -35.350518396689381 26 -10.715566374916852 31 -10.71556637491685 
		33 -10.71556637491685 37 -38.667993635750122 44 17.655215885094979 49 -20.403219688547992 
		54 6.4272702111412796 57 16.80807798405689 60 0;
	setAttr -s 15 ".kit[0:14]"  1 10 10 10 1 10 3 1 
		1 10 10 3 10 10 3;
	setAttr -s 15 ".kot[0:14]"  1 10 10 10 1 10 3 1 
		1 10 10 3 10 10 3;
	setAttr -s 15 ".kix[0:14]"  0.94573259353637695 0.51209419965744019 
		0.99796402454376221 0.64840614795684814 1 0.84860551357269287 1 1 1 0.59510058164596558 
		0.78203058242797852 1 0.37982657551765442 0.87217670679092407 1;
	setAttr -s 15 ".kiy[0:14]"  0.32494601607322693 -0.8589293360710144 
		0.06377873569726944 0.76129460334777832 0 -0.5290260910987854 0 0 0 0.80365127325057983 
		0.62324017286300659 0 0.92505770921707153 -0.48919084668159485 0;
	setAttr -s 15 ".kox[0:14]"  0.94573259353637695 0.51209419965744019 
		0.99796402454376221 0.64840614795684814 1 0.84860551357269287 1 1 1 0.59510058164596558 
		0.78203058242797852 1 0.37982657551765442 0.87217670679092407 1;
	setAttr -s 15 ".koy[0:14]"  0.32494604587554932 -0.8589293360710144 
		0.06377873569726944 0.76129460334777832 0 -0.5290260910987854 0 0 0 0.80365127325057983 
		0.62324017286300659 0 0.92505770921707153 -0.48919084668159485 0;
createNode animCurveTA -n "animCurveTA1686";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 0 3 -1.7009505366740691 7 -10.270844859733897 
		12 16.354268643291306 17 0 21 -1.3815909355855422 26 0 31 0 33 0 37 -8.924355486448075 
		44 -6.9541423415406802 49 1.2493087714257802 54 0.95533557000959268 57 0.56359684802982613 
		60 0;
	setAttr -s 15 ".kit[0:14]"  1 10 3 10 1 10 3 1 
		1 10 9 3 10 10 3;
	setAttr -s 15 ".kot[0:14]"  1 10 3 10 1 10 3 1 
		1 10 9 3 10 10 3;
	setAttr -s 15 ".kix[0:14]"  0.99841517210006714 1 1 0.88072150945663452 
		1 1 1 1 1 1 0.91399282217025757 1 1 1 1;
	setAttr -s 15 ".kiy[0:14]"  -0.05627722293138504 0 0 0.47363460063934326 
		0 0 0 0 0 0 0.40573045611381531 0 0 0 0;
	setAttr -s 15 ".kox[0:14]"  0.99841517210006714 1 1 0.88072150945663452 
		1 1 1 1 1 1 0.91399282217025757 1 1 1 1;
	setAttr -s 15 ".koy[0:14]"  -0.056277208030223846 0 0 0.47363460063934326 
		0 0 0 0 0 0 0.40573045611381531 0 0 0 0;
createNode animCurveTA -n "animCurveTA1687";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -17.821366541589882 3 -24.028324810415413 
		7 -34.493472503818907 10 -21.885044153090078 12 -14.403244116907024 20 -17.821366541589882 
		23 -10.251149004725599 26 -10.315776137104526 31 -10.315776137104526 38 -10.288308247017909 
		45 -8.4250535354098481 49 -8.968845416187138 60 -17.821366541589882;
	setAttr -s 13 ".kit[0:12]"  9 10 10 10 10 1 10 1 
		1 10 10 3 3;
	setAttr -s 13 ".kot[0:12]"  9 10 10 10 10 1 10 1 
		1 10 10 3 3;
	setAttr -s 13 ".kix[5:12]"  1 1 1 1 1 1 1 1;
	setAttr -s 13 ".kiy[5:12]"  0 0 0 0 0 0 0 0;
	setAttr -s 13 ".kox[5:12]"  1 1 1 1 1 1 1 1;
	setAttr -s 13 ".koy[5:12]"  0 0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1688";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -12.005893876475762 3 6.267703906598646 
		7 21.00958183353778 10 25.820425875311013 12 24.140847403903585 20 -12.005893876475762 
		23 -14.403481110151739 26 -12.005893876475767 31 -12.005893876475767 38 -1.4339485573505408 
		45 -18.933105969512827 49 -7.5271449987926324 60 -12.005893876475762;
	setAttr -s 13 ".kit[0:12]"  1 10 10 10 10 1 10 1 
		1 10 10 3 3;
	setAttr -s 13 ".kot[0:12]"  1 10 10 10 10 1 10 1 
		1 10 10 3 3;
	setAttr -s 13 ".kix[0:12]"  0.99996519088745117 0.37532803416252136 
		0.56442046165466309 1 1 1 1 1 1 0.96803969144821167 0.96042001247406006 1 1;
	setAttr -s 13 ".kiy[0:12]"  0.0083397403359413147 0.92689204216003418 
		0.82548749446868896 0 0 0 0 0 0 -0.25079691410064697 -0.27855587005615234 0 0;
	setAttr -s 13 ".kox[0:12]"  0.99996519088745117 0.37532803416252136 
		0.56442046165466309 1 1 1 1 1 1 0.96803969144821167 0.96042001247406006 1 1;
	setAttr -s 13 ".koy[0:12]"  0.0083397403359413147 0.92689204216003418 
		0.82548749446868896 0 0 0 0 0 0 -0.25079691410064697 -0.27855587005615234 0 0;
createNode animCurveTA -n "animCurveTA1689";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 9.1378572146953019 3 17.312120310479369 
		7 16.165430737212287 10 21.922486657251909 12 24.449128341819105 20 9.1378572146953019 
		23 11.32788719305398 26 9.1378572146953143 31 9.1378572146953143 38 22.408323284433575 
		45 34.481273772632548 49 28.908496888440226 60 9.1378572146953019;
	setAttr -s 13 ".kit[0:12]"  9 10 10 10 10 1 10 1 
		1 10 10 3 3;
	setAttr -s 13 ".kot[0:12]"  9 10 10 10 10 1 10 1 
		1 10 10 3 3;
	setAttr -s 13 ".kix[5:12]"  1 1 1 1 0.72578126192092896 0.95531719923019409 
		1 1;
	setAttr -s 13 ".kiy[5:12]"  0 0 0 0 0.68792563676834106 0.2955823540687561 
		0 0;
	setAttr -s 13 ".kox[5:12]"  1 1 1 1 0.72578126192092896 0.95531719923019409 
		1 1;
	setAttr -s 13 ".koy[5:12]"  0 0 0 0 0.68792563676834106 0.2955823540687561 
		0 0;
createNode animCurveTA -n "animCurveTA1690";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -28.841216077843235 4 -52.682497747652235 
		7 -51.948728225083656 12 -28.841216077843235 16 -14.411436008916876 22 -43.097765517614803 
		31 12.455024745614898 37 -1.2358850007797255 42 3.4147464690714933 49 -38.53294646432213 
		52 -45.450223099257478 56 -32.279380195952307 60 -28.841216077843235;
	setAttr -s 13 ".kit[0:12]"  9 10 10 10 10 10 1 1 
		10 3 10 10 3;
	setAttr -s 13 ".kot[0:12]"  9 10 10 10 10 10 1 1 
		10 3 10 10 3;
	setAttr -s 13 ".kix[6:12]"  1 1 0.52353847026824951 1 0.90580135583877563 
		0.67702263593673706 1;
	setAttr -s 13 ".kiy[6:12]"  0 0 -0.85200208425521851 0 0.42370271682739258 
		0.73596221208572388 0;
	setAttr -s 13 ".kox[6:12]"  1 1 0.52353847026824951 1 0.90580135583877563 
		0.67702263593673706 1;
	setAttr -s 13 ".koy[6:12]"  0 0 -0.85200208425521851 0 0.42370271682739258 
		0.73596221208572388 0;
createNode animCurveTA -n "animCurveTA1691";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -21.716766331039956 4 -46.220378325628275 
		7 -45.816376308701763 12 -21.716766331039956 16 -48.440483517320516 22 4.5425262198186687 
		31 -33.463227617426853 37 -8.7431956941885076 42 -56.7466222411595 49 -52.824552060626495 
		52 -41.542012620940469 56 -23.575109285658421 60 -21.716766331039956;
	setAttr -s 13 ".kit[0:12]"  9 10 10 10 10 10 1 1 
		10 3 10 10 3;
	setAttr -s 13 ".kot[0:12]"  9 10 10 10 10 10 1 1 
		10 3 10 10 3;
	setAttr -s 13 ".kix[6:12]"  1 1 0.46128946542739868 1 0.41570428013801575 
		1 1;
	setAttr -s 13 ".kiy[6:12]"  0 0 -0.88724970817565918 0 0.9094998836517334 
		0 0;
	setAttr -s 13 ".kox[6:12]"  1 1 0.46128946542739868 1 0.41570428013801575 
		1 1;
	setAttr -s 13 ".koy[6:12]"  0 0 -0.88724970817565918 0 0.9094998836517334 
		0 0;
createNode animCurveTA -n "animCurveTA1692";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 23.535235892507558 4 52.513697785886393 
		7 15.764160117697044 12 23.535235892507558 16 -25.266777063217486 22 -80.396363162923421 
		31 -45.399603242971963 37 -47.581392492882692 42 -56.214235512398083 49 -5.6181026895639832 
		52 48.873718194975041 56 5.9473951831911167 60 23.535235892507558;
	setAttr -s 13 ".kit[0:12]"  9 10 10 10 10 10 1 1 
		10 3 10 10 3;
	setAttr -s 13 ".kot[0:12]"  9 10 10 10 10 10 1 1 
		10 3 10 10 3;
	setAttr -s 13 ".kix[6:12]"  1 1 0.47932344675064087 1 0.75627624988555908 
		0.51637774705886841 1;
	setAttr -s 13 ".kiy[6:12]"  0 0 0.87763833999633789 0 0.65425246953964233 
		-0.85636085271835327 0;
	setAttr -s 13 ".kox[6:12]"  1 1 0.47932344675064087 1 0.75627624988555908 
		0.51637774705886841 1;
	setAttr -s 13 ".koy[6:12]"  0 0 0.87763833999633789 0 0.65425246953964233 
		-0.85636085271835327 0;
createNode animCurveTL -n "animCurveTL511";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 7 0 12 0 16 0.00062895865886335319 
		31 0.0010788490877914928 37 0.0010788490877914928 49 0 60 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 1 1 3 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 1 1 3 3;
	setAttr -s 8 ".kix[4:7]"  1 1 1 1;
	setAttr -s 8 ".kiy[4:7]"  0 0 0 0;
	setAttr -s 8 ".kox[4:7]"  1 1 1 1;
	setAttr -s 8 ".koy[4:7]"  0 0 0 0;
createNode animCurveTL -n "animCurveTL512";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 7 0 12 0 16 -0.0030111205526390408 
		31 -0.0051649573714679072 37 -0.0051649573714679072 49 0 60 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 1 1 3 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 1 1 3 3;
	setAttr -s 8 ".kix[4:7]"  1 1 1 1;
	setAttr -s 8 ".kiy[4:7]"  0 0 0 0;
	setAttr -s 8 ".kox[4:7]"  1 1 1 1;
	setAttr -s 8 ".koy[4:7]"  0 0 0 0;
createNode animCurveTL -n "animCurveTL513";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 7 0 12 0 16 -0.0019408779997604011 
		31 -0.0033291766160596058 37 -0.0033291766160596058 49 0 60 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 1 1 3 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 1 1 3 3;
	setAttr -s 8 ".kix[4:7]"  1 1 1 1;
	setAttr -s 8 ".kiy[4:7]"  0 0 0 0;
	setAttr -s 8 ".kox[4:7]"  1 1 1 1;
	setAttr -s 8 ".koy[4:7]"  0 0 0 0;
createNode animCurveTU -n "animCurveTU528";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 2 3 2 7 2 12 2 20 2 21 2 26 2 31 2 37 
		2 49 2 60 2;
	setAttr -s 11 ".kit[0:10]"  3 9 9 9 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 5 5 5 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU529";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 9 9 9 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 5 5 5 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1693";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -24.093441664171177 3 -24.093441664171177 
		7 -24.093441664171177 12 -24.093441664171177 20 -24.093441664171177 21 -24.093441664171177 
		26 -24.093441664171177 31 -24.093441664171177 37 -24.093441664171177 49 -24.093441664171177 
		60 -24.093441664171177;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1694";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 49.48465546224881 3 49.48465546224881 
		7 49.48465546224881 12 49.48465546224881 20 49.48465546224881 21 49.48465546224881 
		26 49.48465546224881 31 49.48465546224881 37 49.48465546224881 49 49.48465546224881 
		60 49.48465546224881;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1695";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 58.801792680015588 3 58.801792680015588 
		7 58.801792680015588 12 58.801792680015588 20 58.801792680015588 21 58.801792680015588 
		26 58.801792680015588 31 58.801792680015588 37 58.801792680015588 49 58.801792680015588 
		60 58.801792680015588;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL514";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -1.2755255474500937 3 -1.2755255474500937 
		7 -1.2755255474500937 12 -1.2755255474500937 20 -1.2734862259193831 21 -1.2734862259193831 
		26 -1.2734862259193831 31 -1.2734862259193831 37 -1.2734862259193831 49 -1.2755255474500937 
		60 -1.2755255474500937;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL515";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -1.4392043230118035 3 -1.4392043230118035 
		7 -1.4392043230118035 12 -1.4392043230118035 20 -1.4396928676445395 21 -1.4396928676445395 
		26 -1.4396928676445395 31 -1.4396928676445395 37 -1.4396928676445395 49 -1.4392043230118035 
		60 -1.4392043230118035;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL516";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -2.1802956492995231 3 -2.1802956492995231 
		7 -2.1802956492995231 12 -2.1802956492995231 20 -2.1861715840149905 21 -2.1861715840149905 
		26 -2.1861715840149905 31 -2.1861715840149905 37 -2.1861715840149905 49 -2.1802956492995231 
		60 -2.1802956492995231;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL517";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0.001085747848091054 
		21 0.001085747848091054 26 0.001085747848091054 31 0.001085747848091054 37 0.001085747848091054 
		49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL518";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 -0.0036987718299101024 
		21 -0.0036987718299101024 26 -0.0036987718299101024 31 -0.0036987718299101024 37 
		-0.0036987718299101024 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL519";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 -0.0049055433445089856 
		21 -0.0049055433445089856 26 -0.0049055433445089856 31 -0.0049055433445089856 37 
		-0.0049055433445089856 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1696";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 61 ".ktv[0:60]"  0 1.1134085745787063 1 1.1134085745786921 
		2 1.1134085745786972 3 1.1134085745787121 4 1.1134085745787121 5 1.1134085745787121 
		6 1.1134085745787121 7 1.1134085745787121 8 -0.85619000722221128 9 -14.806469520864825 
		10 -29.928410166831494 11 -107.88035830489517 12 -139.4938831425352 13 -157.78698996976968 
		14 -159.45555702546935 15 -159.05662789559034 16 -161.92605166776298 17 -165.16217879837617 
		18 -165.80396245399436 19 -166.6148397581369 20 -171.27155651152449 21 -179.23209543560702 
		22 -181.30772222280584 23 -185.1719127433982 24 -183.84238885129852 25 -180.52047645266245 
		26 -178.63517889124697 27 -178.97629643894385 28 -179.86388593447114 29 -181.09315454933076 
		30 -182.45557793829551 31 -183.73923921651894 32 -187.91371391359701 33 -195.19448097681465 
		34 -200.72933025455384 35 -201.68463883428825 36 -199.32036662657748 37 -194.58659234719849 
		38 -187.17970120185112 39 -173.10476252164852 40 -150.46825297058592 41 -124.55868849659878 
		42 -97.182548968363221 43 -70.739734837413323 44 -47.684780842832254 45 -25.937616364144223 
		46 -8.9829873711044002 47 -0.81379196096331996 48 0.71785598582652688 49 1.113408574578703 
		50 1.1134085745786944 51 1.1134085745787063 52 1.1134085745787086 53 1.1134085745787128 
		54 1.1134085745786975 55 1.1134085745786999 56 1.113408574578691 57 1.1134085745787103 
		58 1.1134085745786917 59 1.113408574578693 60 1.1134085745787063;
	setAttr -s 61 ".kit[21:60]"  3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10;
	setAttr -s 61 ".kot[21:60]"  3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA1697";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 61 ".ktv[0:60]"  0 -5.3180374758492839 1 -5.3180374758492857 
		2 -5.3180374758492768 3 -5.3180374758492839 4 -5.3180374758492839 5 -5.3180374758492839 
		6 -5.3180374758492839 7 -5.3180374758492839 8 -6.796642028053304 9 -20.4958755787904 
		10 -13.246604181466049 11 -9.334715496593029 12 -21.582835182940137 13 -23.94385305209957 
		14 -10.354338276591983 15 7.1346540832668115 16 21.938473991063269 17 29.242963892891186 
		18 29.905151077648728 19 27.219926622847417 20 24.626902319444319 21 25.301488364790522 
		22 27.016779986802852 23 24.205511464564029 24 24.042374176516756 25 24.083209943065185 
		26 24.229600703692661 27 24.247210331253882 28 24.269934597899677 29 24.253071862247044 
		30 24.157324095830109 31 23.950634938117847 32 24.725012935838762 33 26.035598616669635 
		34 25.839234368394056 35 22.593902216939142 36 15.852850804182978 37 5.8645422387487534 
		38 -6.1861586982123242 39 -14.509132359541288 40 -12.36306217944886 41 -1.0715693135818944 
		42 9.0049510351618665 43 9.0028092531036545 44 1.0130782266891964 45 -4.060262784676623 
		46 -4.1645304945596928 47 -4.4736008703019721 48 -5.4287041958781392 49 -5.3180374758492821 
		50 -5.3180374758492786 51 -5.3180374758492741 52 -5.318037475849283 53 -5.318037475849283 
		54 -5.3180374758492759 55 -5.3180374758492706 56 -5.3180374758492777 57 -5.3180374758492768 
		58 -5.3180374758492777 59 -5.3180374758492821 60 -5.3180374758492839;
	setAttr -s 61 ".kit[21:60]"  3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10;
	setAttr -s 61 ".kot[21:60]"  3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA1698";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 61 ".ktv[0:60]"  0 7.8609313736722699 1 7.8609313736722655 
		2 7.8609313736722815 3 7.8609313736722699 4 7.8609313736722699 5 7.8609313736722699 
		6 7.8609313736722699 7 7.8609313736722699 8 2.5792344775972791 9 -24.478581052753277 
		10 -36.588978818702799 11 -24.650894409703483 12 -34.902813058820101 13 -40.399073670397648 
		14 -44.338699819185514 15 -51.458904856175316 16 -61.3472239842894 17 -70.879336540278828 
		18 -71.931442600166292 19 -64.625290602752472 20 -55.697777655569048 21 -51.842309604362612 
		22 -50.97192234059834 23 -47.16699250880405 24 -48.821702961691706 25 -51.243377461333424 
		26 -52.456758773513236 27 -52.776959791470595 28 -53.566774142723041 29 -54.568390777842559 
		30 -55.522971625944976 31 -56.173149428110705 32 -60.971937800818239 33 -69.211833714716661 
		34 -72.605466334168767 35 -67.792988898271702 36 -59.403220635470838 37 -51.431550698236435 
		38 -47.53680641463923 39 -51.612802413313972 40 -60.160454036572297 41 -62.517502069803299 
		42 -53.974734995383557 43 -42.47014157957851 44 -33.915906653053753 45 -24.925885613234708 
		46 -11.047803581365461 47 2.3074869752602374 48 9.0836286108641406 49 7.8609313736722735 
		50 7.8609313736722699 51 7.8609313736722592 52 7.8609313736722619 53 7.8609313736722761 
		54 7.8609313736722664 55 7.8609313736722717 56 7.8609313736722841 57 7.8609313736722735 
		58 7.8609313736722841 59 7.8609313736722655 60 7.8609313736722699;
	setAttr -s 61 ".kit[21:60]"  3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10;
	setAttr -s 61 ".kot[21:60]"  3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10;
createNode animCurveTL -n "animCurveTL520";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 61 ".ktv[0:60]"  0 0 1 6.6613381477509392e-016 2 2.2204460492503131e-016 
		3 -4.4408920985006262e-016 4 2.2204460492503131e-016 5 2.2204460492503131e-016 6 
		2.2204460492503131e-016 7 0 8 0.023162152961506255 9 -0.046564771045121134 10 -0.11096999745342306 
		11 -0.41672217339153983 12 -0.82883539224232772 13 -1.1384261502930877 14 -1.3008092215509426 
		15 -1.4250898304027801 16 -1.5071304601004527 17 -1.5275453232548395 18 -1.4159615682103683 
		19 -1.128086476136426 20 -0.88500747773292388 21 -0.80642119156845504 22 -0.80835676592556738 
		23 -0.77247362586158808 24 -0.79768372780606223 25 -0.83201005829876995 26 -0.84971442782687356 
		27 -0.85562378347997026 28 -0.87044019536253359 29 -0.88991341519838985 30 -0.91011394676605661 
		31 -0.92730707168830007 32 -0.92108524509290679 33 -0.88492052813055522 34 -0.83190746364639701 
		35 -0.79201101818665109 36 -0.7729015478118082 37 -0.75981314096031793 38 -0.72955068473724172 
		39 -0.63599809864110979 40 -0.52232175962699934 41 -0.45304136345349688 42 -0.38404678310870799 
		43 -0.29259510817992318 44 -0.20244183907657876 45 -0.11934905919175454 46 -0.031001694176870043 
		47 0.028751261470185696 48 0.031546268669824462 49 2.2204460492503131e-016 50 0 51 
		4.4408920985006262e-016 52 0 53 2.2204460492503131e-016 54 2.2204460492503131e-016 
		55 -2.2204460492503131e-016 56 4.4408920985006262e-016 57 2.2204460492503131e-016 
		58 4.4408920985006262e-016 59 -2.2204460492503131e-016 60 0;
	setAttr -s 61 ".kit[21:60]"  3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10;
	setAttr -s 61 ".kot[21:60]"  3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10;
createNode animCurveTL -n "animCurveTL521";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 61 ".ktv[0:60]"  0 0 1 -4.4408920985006262e-016 2 -4.4408920985006262e-016 
		3 2.2204460492503131e-016 4 -2.2204460492503131e-016 5 0 6 2.2204460492503131e-016 
		7 -2.2204460492503131e-016 8 -0.16780270300055355 9 -0.4202096479329811 10 -0.57068962475741447 
		11 -0.6054805698667618 12 -0.53578801214708127 13 -0.47491479119216984 14 -0.42270484619634174 
		15 -0.3765371598608479 16 -0.34625066934663373 17 -0.34407335300389053 18 -0.50902605972194048 
		19 -0.99801055483742007 20 -1.4211324531105012 21 -1.5422023647769851 22 -1.5024512786170436 
		23 -1.4693965529819999 24 -1.4874090534983861 25 -1.5215096928151395 26 -1.5369572532846998 
		27 -1.5305509535625985 28 -1.5158853543138857 29 -1.4996864288286904 30 -1.488710067339952 
		31 -1.4898752492462912 32 -1.4747758266039104 33 -1.4143652774079638 34 -1.327031382176731 
		35 -1.1908689513732718 36 -1.0108686805343172 37 -0.84811522049605992 38 -0.75462998461973874 
		39 -0.79435993934465821 40 -0.87913145776853474 41 -0.87569041823939942 42 -0.78606523164084097 
		43 -0.66912488147613458 44 -0.52494264873098917 45 -0.37850764216019273 46 -0.26452357785060188 
		47 -0.15337172855902725 48 -0.044530942468849366 49 -2.2204460492503131e-016 50 -2.2204460492503131e-016 
		51 -6.6613381477509392e-016 52 0 53 -4.4408920985006262e-016 54 0 55 0 56 -4.4408920985006262e-016 
		57 -2.2204460492503131e-016 58 -4.4408920985006262e-016 59 2.2204460492503131e-016 
		60 0;
	setAttr -s 61 ".kit[21:60]"  3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10;
	setAttr -s 61 ".kot[21:60]"  3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10;
createNode animCurveTL -n "animCurveTL522";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 61 ".ktv[0:60]"  0 -1.1102230246251565e-016 1 -1.1102230246251565e-016 
		2 -2.2204460492503131e-016 3 1.1102230246251565e-016 4 -1.1102230246251565e-016 5 
		2.2204460492503131e-016 6 1.1102230246251565e-016 7 0 8 0.093988902236979421 9 0.2278141407340909 
		10 0.13740919332487722 11 -0.053137919609361928 12 -0.31583223726505882 13 -0.53677838156423086 
		14 -0.68936450170157904 15 -0.80263469199060322 16 -0.86784131493963901 17 -0.87563076919231642 
		18 -0.79984550962473855 19 -0.70049684042413451 20 -0.70991796177060351 21 -0.83743223304270964 
		22 -0.91759670632742396 23 -0.98525430436302042 24 -0.93330336907427369 25 -0.82599759652974236 
		26 -0.76460350874603278 27 -0.76877087739723671 28 -0.78097136073201434 29 -0.80082544782727316 
		30 -0.82830070704163083 31 -0.86386332543481981 32 -0.92912541761006562 33 -1.0106853626844083 
		34 -1.0655335524699203 35 -1.0883818592134895 36 -1.085684019357172 37 -1.0480686161037034 
		38 -0.98334572080389526 39 -0.91095159113804858 40 -0.77826638873721943 41 -0.56954069124993789 
		42 -0.35835013412804329 43 -0.16397581842662912 44 -0.0038384039260580538 45 0.098957617539326526 
		46 0.12980601487661991 47 0.094488895720136856 48 0.034993566478726756 49 -1.1102230246251565e-016 
		50 -2.2204460492503131e-016 51 -1.1102230246251565e-016 52 0 53 0 54 -3.3306690738754696e-016 
		55 0 56 -2.2204460492503131e-016 57 1.1102230246251565e-016 58 -2.2204460492503131e-016 
		59 0 60 -1.1102230246251565e-016;
	setAttr -s 61 ".kit[21:60]"  3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10;
	setAttr -s 61 ".kot[21:60]"  3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA1699";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1700";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1701";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL523";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0.0010857478480910537 
		21 0.0010857478480910537 26 0.0010857478480910537 31 0.0010857478480910537 37 0.0010857478480910537 
		49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL524";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 -0.0036987718299101042 
		21 -0.0036987718299101042 26 -0.0036987718299101042 31 -0.0036987718299101042 37 
		-0.0036987718299101042 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL525";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 -0.0049055433445089865 
		21 -0.0049055433445089865 26 -0.0049055433445089865 31 -0.0049055433445089865 37 
		-0.0049055433445089865 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU530";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 9 9 9 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 5 5 5 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1702";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -5.1107219305963252 3 -5.1107219305963252 
		7 -5.1107219305963252 12 -5.1107219305963252 20 -5.1107219305963252 21 -5.1107219305963252 
		26 -5.1107219305963252 31 -5.1107219305963252 37 -5.1107219305963252 49 -5.1107219305963252 
		60 -5.1107219305963252;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1703";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 8.2811672786141717 3 8.2811672786141717 
		7 8.2811672786141717 12 8.2811672786141717 20 8.2811672786141717 21 8.2811672786141717 
		26 8.2811672786141717 31 8.2811672786141717 37 8.2811672786141717 49 8.2811672786141717 
		60 8.2811672786141717;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1704";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -0.92645454014921158 3 -0.92645454014921158 
		7 -0.92645454014921158 12 -0.92645454014921158 20 -0.92645454014921158 21 -0.92645454014921158 
		26 -0.92645454014921158 31 -0.92645454014921158 37 -0.92645454014921158 49 -0.92645454014921158 
		60 -0.92645454014921158;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL526";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -0.046856395845859107 3 -0.046856395845859107 
		7 -0.046856395845859107 12 -0.046856395845859107 20 -0.047718261129989496 21 -0.047718261129989496 
		26 -0.047718261129989496 31 -0.047718261129989496 37 -0.047718261129989496 49 -0.046856395845859107 
		60 -0.046856395845859107;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL527";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -0.023348763690700665 3 -0.023348763690700665 
		7 -0.023348763690700665 12 -0.023348763690700665 20 -0.028512066740404032 21 -0.028512066740404032 
		26 -0.028512066740404032 31 -0.028512066740404032 37 -0.028512066740404032 49 -0.023348763690700665 
		60 -0.023348763690700665;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL528";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -0.13506113021862395 3 -0.13506113021862395 
		7 -0.13506113021862395 12 -0.13506113021862395 20 -0.13845547946305389 21 -0.13845547946305389 
		26 -0.13845547946305389 31 -0.13845547946305389 37 -0.13845547946305389 49 -0.13506113021862395 
		60 -0.13506113021862395;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1705";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -1.6266160090263075 4 -74.705039774405606 
		7 -85.594217797103809 10 -41.222627075073376 12 -40.769019690538961 15 -37.044630739911547 
		21 -6.8148671812012873 26 -32.16068940292952 31 -32.16068940292952 37 -1.6266160090263075 
		49 -1.6266160090263075 60 -1.6266160090263075;
	setAttr -s 12 ".kit[0:11]"  9 10 10 10 10 10 10 1 
		1 1 3 3;
	setAttr -s 12 ".kot[0:11]"  9 10 10 10 10 10 10 1 
		1 1 3 3;
	setAttr -s 12 ".kix[7:11]"  1 1 1 1 1;
	setAttr -s 12 ".kiy[7:11]"  0 0 0 0 0;
	setAttr -s 12 ".kox[7:11]"  1 1 1 1 1;
	setAttr -s 12 ".koy[7:11]"  0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1706";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 2.8499857758927387 4 -34.358347990015588 
		7 -22.781491950878177 10 3.6393119753415308 12 -0.18202519637933962 15 -62.539396560809401 
		21 -37.349038606468511 26 -10.85671593774973 31 -10.85671593774973 37 2.8499857758927387 
		49 2.8499857758927387 60 2.8499857758927387;
	setAttr -s 12 ".kit[0:11]"  9 10 10 10 10 10 10 1 
		1 1 3 3;
	setAttr -s 12 ".kot[0:11]"  9 10 10 10 10 10 10 1 
		1 1 3 3;
	setAttr -s 12 ".kix[7:11]"  1 1 1 1 1;
	setAttr -s 12 ".kiy[7:11]"  0 0 0 0 0;
	setAttr -s 12 ".kox[7:11]"  1 1 1 1 1;
	setAttr -s 12 ".koy[7:11]"  0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1707";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -25.210898828531619 4 41.13791547939249 
		7 87.877358915932518 10 33.0566265160477 12 44.348923037322706 15 12.779046781403144 
		21 -39.6466192531093 26 -31.881524612848605 31 -31.881524612848605 37 -25.210898828531619 
		49 -25.210898828531619 60 -25.210898828531619;
	setAttr -s 12 ".kit[0:11]"  1 10 10 10 10 10 10 1 
		1 1 3 3;
	setAttr -s 12 ".kot[0:11]"  1 10 10 10 10 10 10 1 
		1 1 3 3;
	setAttr -s 12 ".kix[0:11]"  0.99788904190063477 0.11740003526210785 
		0.81722068786621094 0.21428471803665161 0.42604923248291016 0.20048385858535767 0.42565953731536865 
		1 1 1 1 1;
	setAttr -s 12 ".kiy[0:11]"  0.064942330121994019 0.99308472871780396 
		-0.57632488012313843 -0.97677123546600342 -0.90469998121261597 -0.97969704866409302 
		-0.90488332509994507 0 0 0 0 0;
	setAttr -s 12 ".kox[0:11]"  0.99788904190063477 0.11740003526210785 
		0.81722068786621094 0.21428471803665161 0.42604923248291016 0.20048385858535767 0.42565953731536865 
		1 1 1 1 1;
	setAttr -s 12 ".koy[0:11]"  0.064942330121994019 0.99308472871780396 
		-0.57632488012313843 -0.97677123546600342 -0.90469998121261597 -0.97969704866409302 
		-0.90488332509994507 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL529";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.011193700785458628 7 -0.2516667625179968 
		12 -0.11230628755597952 15 0.028508423871070818 21 0.022709348013876265 26 0.0046916381238480678 
		31 0.0046916381238480678 37 -0.0098687514676483439 49 -0.011193700785458628 60 -0.011193700785458628;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 1 1 1 
		3 3;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 1 1 1 
		3 3;
	setAttr -s 10 ".kix[5:9]"  1 1 1 1 1;
	setAttr -s 10 ".kiy[5:9]"  0 0 0 0 0;
	setAttr -s 10 ".kox[5:9]"  1 1 1 1 1;
	setAttr -s 10 ".koy[5:9]"  0 0 0 0 0;
createNode animCurveTL -n "animCurveTL530";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.020021267836214246 7 -0.30513513683547783 
		12 -0.25325175528837601 15 -0.11813953175893756 21 -0.040602054944926282 26 -0.023430737417971581 
		31 -0.023430737417971581 37 -0.026012774447344764 49 -0.020021267836214246 60 -0.020021267836214246;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 1 1 1 
		3 3;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 1 1 1 
		3 3;
	setAttr -s 10 ".kix[5:9]"  1 1 1 1 1;
	setAttr -s 10 ".kiy[5:9]"  0 0 0 0 0;
	setAttr -s 10 ".kox[5:9]"  1 1 1 1 1;
	setAttr -s 10 ".koy[5:9]"  0 0 0 0 0;
createNode animCurveTL -n "animCurveTL531";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.032441787830836878 7 -0.14546807136314527 
		12 -0.17873475426107771 15 -0.10691604554062226 21 -0.094707634243627992 26 -0.17505845952015256 
		31 -0.17505845952015256 37 0.031314634434780865 49 0.032441787830836878 60 0.032441787830836878;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 1 1 1 
		3 3;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 1 1 1 
		3 3;
	setAttr -s 10 ".kix[5:9]"  1 1 1 1 1;
	setAttr -s 10 ".kiy[5:9]"  0 0 0 0 0;
	setAttr -s 10 ".kox[5:9]"  1 1 1 1 1;
	setAttr -s 10 ".koy[5:9]"  0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1708";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 10 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 10 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1709";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 10 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 10 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1710";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 10 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 10 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL532";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 10 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 10 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL533";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 10 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 10 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL534";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 10 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 10 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1711";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -15.609971163878811 3 -15.999937565713314 
		7 -15.999937565713314 12 -17.875498403797526 19 -9.3083748170083531 23 -18.036761491677126 
		26 -13.9073386617123 33 -19.433746167929154 41 -25.933617034429822 49 -15.382187831757127 
		54 -15.626727618510081 60 -15.609971163878811;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 1 10 3 10 
		10 3 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 1 10 3 10 
		10 3 10 3;
	setAttr -s 12 ".kix[4:11]"  1 0.94561338424682617 1 0.92204910516738892 
		0.99132454395294189 1 1 1;
	setAttr -s 12 ".kiy[4:11]"  0 -0.32529258728027344 0 -0.38707280158996582 
		0.13143669068813324 0 0 0;
	setAttr -s 12 ".kox[4:11]"  1 0.94561338424682617 1 0.92204910516738892 
		0.99132454395294189 1 1 1;
	setAttr -s 12 ".koy[4:11]"  0 -0.32529258728027344 0 -0.38707280158996582 
		0.13143669068813324 0 0 0;
createNode animCurveTA -n "animCurveTA1712";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 8.3116042646716988 3 11.14937897169629 
		7 11.14937897169629 12 -2.1727636717891965 19 -10.443206317083822 23 5.8796033458433259 
		26 3.8092734454556938 33 3.803207036620305 41 0.27531747204780815 49 11.282019902860512 
		54 8.4335405209961767 60 8.3116042646716988;
	setAttr -s 12 ".kit[0:11]"  9 10 10 3 9 10 3 10 
		10 3 10 3;
	setAttr -s 12 ".kot[0:11]"  9 10 10 3 9 10 3 10 
		10 3 10 3;
createNode animCurveTA -n "animCurveTA1713";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 14.458598883932659 3 10.872744288102249 
		7 10.872744288102249 12 2.0736159609136675 19 32.175510788904134 23 35.758465624657639 
		26 34.016783965626352 33 36.752992113025115 41 16.586480605009005 49 13.915906577352576 
		54 14.304518405289608 60 14.458598883932659;
	setAttr -s 12 ".kit[0:11]"  3 10 10 3 1 10 3 9 
		10 3 10 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 3 1 10 3 9 
		10 3 10 3;
	setAttr -s 12 ".kix[4:11]"  0.87762343883514404 1 1 0.85429847240447998 
		1 1 1 1;
	setAttr -s 12 ".kiy[4:11]"  0.47935080528259277 0 0 -0.51978284120559692 
		0 0 0 0;
	setAttr -s 12 ".kox[4:11]"  0.87762337923049927 1 1 0.85429847240447998 
		1 1 1 1;
	setAttr -s 12 ".koy[4:11]"  0.47935080528259277 0 0 -0.51978284120559692 
		0 0 0 0;
createNode animCurveTL -n "animCurveTL535";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 -0.18868131369562219 3 -0.28191841704213044 
		6 -0.4643359406809861 7 -0.40588556073994758 12 -0.093792895783944619 19 -0.92586385831559748 
		23 -0.88288483011777352 26 -0.8217918948959001 33 -0.73097516446270983 39 -0.31797866549064868 
		41 -0.23824378062333687 43 -0.21015968825121228 49 -0.40588556073994758 54 -0.27118493473674554 
		60 -0.18868131369562219;
	setAttr -s 15 ".kit[0:14]"  3 10 10 10 10 1 10 3 
		10 1 9 10 3 1 3;
	setAttr -s 15 ".kot[0:14]"  3 10 10 10 10 1 10 3 
		10 1 9 10 3 1 3;
	setAttr -s 15 ".kix[5:14]"  0.73123329877853394 1 1 0.65208590030670166 
		0.50020688772201538 0.77757996320724487 1 1 0.62554067373275757 1;
	setAttr -s 15 ".kiy[5:14]"  -0.68212753534317017 0 0 0.75814509391784668 
		0.8659060001373291 0.62878412008285522 0 0 0.78019154071807861 0;
	setAttr -s 15 ".kox[5:14]"  0.73123329877853394 1 1 0.65208590030670166 
		0.50020688772201538 0.77757996320724487 1 1 0.62554067373275757 1;
	setAttr -s 15 ".koy[5:14]"  -0.68212747573852539 0 0 0.75814509391784668 
		0.86590594053268433 0.62878412008285522 0 0 0.78019154071807861 0;
createNode animCurveTL -n "animCurveTL536";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0.23059098815955009 3 0.15187852342310387 
		7 0.2504740654160087 12 -0.10819850467656417 19 -0.87813252031527755 26 -0.85841881518426244 
		33 -0.76191863913798208 41 -0.1105295162657785 45 0.13952503619501766 49 0.2504740654160087 
		54 0.22880142864685429 60 0.23059098815955009;
	setAttr -s 12 ".kit[0:11]"  1 10 10 10 1 3 10 10 
		10 3 10 3;
	setAttr -s 12 ".kot[0:11]"  1 10 10 10 1 3 10 10 
		10 3 10 3;
	setAttr -s 12 ".kix[0:11]"  0.99345618486404419 0.99638903141021729 
		0.75559306144714355 0.33405876159667969 1 1 0.55578261613845825 0.40559506416320801 
		0.59415751695632935 1 1 1;
	setAttr -s 12 ".kiy[0:11]"  0.11421383172273636 0.084905482828617096 
		-0.65504133701324463 -0.94255226850509644 0 0 0.83132767677307129 0.91405284404754639 
		0.80434870719909668 0 0 0;
	setAttr -s 12 ".kox[0:11]"  0.99345618486404419 0.99638903141021729 
		0.75559306144714355 0.33405876159667969 1 1 0.55578261613845825 0.40559506416320801 
		0.59415751695632935 1 1 1;
	setAttr -s 12 ".koy[0:11]"  0.11421385407447815 0.084905482828617096 
		-0.65504133701324463 -0.94255226850509644 0 0 0.83132767677307129 0.91405284404754639 
		0.80434870719909668 0 0 0;
createNode animCurveTL -n "animCurveTL537";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0.049918713102953649 3 0.024863501813899791 
		7 0.024863501813899791 12 0.045299846273314681 19 0.091474453233878802 23 0.11637833104785154 
		26 0.16761857808923397 33 0.15963537067632338 37 0.0991562500856287 41 0.0033583696571843607 
		49 0.024863501813899791 54 0.074355430222040067 60 0.049918713102953649;
	setAttr -s 13 ".kit[0:12]"  1 10 10 9 9 9 3 9 
		10 10 3 10 3;
	setAttr -s 13 ".kot[0:12]"  1 10 10 9 9 9 3 9 
		10 10 3 10 3;
	setAttr -s 13 ".kix[0:12]"  0.9780927300453186 1 1 0.98641610145568848 
		0.98172450065612793 0.95066124200820923 1 0.98301160335540771 0.86276125907897949 
		1 1 1 1;
	setAttr -s 13 ".kiy[0:12]"  -0.20816941559314728 0 0 0.16426530480384827 
		0.19030770659446716 0.31023111939430237 0 -0.18354344367980957 -0.50561153888702393 
		0 0 0 0;
	setAttr -s 13 ".kox[0:12]"  0.9780927300453186 1 1 0.98641610145568848 
		0.98172450065612793 0.95066124200820923 1 0.98301160335540771 0.86276125907897949 
		1 1 1 1;
	setAttr -s 13 ".koy[0:12]"  -0.20816941559314728 0 0 0.16426530480384827 
		0.19030770659446716 0.31023111939430237 0 -0.18354344367980957 -0.50561153888702393 
		0 0 0 0;
createNode animCurveTU -n "animCurveTU531";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 7 0 12 0 15 0 20 0 23 0 26 0 31 
		0 37 0 49 0 60 0;
	setAttr -s 12 ".kit[1:11]"  9 9 9 9 1 9 3 1 
		1 3 3;
	setAttr -s 12 ".kot[1:11]"  5 5 5 5 1 5 3 1 
		1 3 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[5:11]"  1 0 1 1 1 1 1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU532";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0.084155571970393403 3 0.084155571970393403 
		7 0.084155571970393403 12 0.084155571970393403 15 0.084155571970393403 20 0.084155571970393403 
		23 0.084155571970393403 26 0.084155571970393403 31 0.084155571970393403 37 0.084155571970393403 
		49 0.084155571970393403 60 0.084155571970393403;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 1 10 3 
		1 1 3 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 1 10 3 
		1 1 3 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL538";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0.067207227343123899 3 0.067207227343123899 
		7 0.067207227343123899 12 0.067207227343123899 15 0.21937342065550364 20 -0.41041943362316846 
		23 -0.38492329074603998 26 -0.37599964073904502 31 -0.37599964073904502 37 -0.37599964073904502 
		43 -0.16948217823291439 49 0.15978625566070526 60 0.067207227343123899;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 10 1 10 3 
		1 1 10 3 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 10 1 10 3 
		1 1 10 3 3;
	setAttr -s 13 ".kix[5:12]"  1 1 1 1 1 0.59823787212371826 1 1;
	setAttr -s 13 ".kiy[5:12]"  0 0 0 0 0 0.80131852626800537 0 0;
	setAttr -s 13 ".kox[5:12]"  1 1 1 1 1 0.59823787212371826 1 1;
	setAttr -s 13 ".koy[5:12]"  0 0 0 0 0 0.80131852626800537 0 0;
createNode animCurveTL -n "animCurveTL539";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -0.20472824713235571 3 -0.20472824713235571 
		7 -0.20472824713235571 12 -0.20472824713235571 15 -0.45205913450405277 20 -0.97989253118769182 
		23 -0.99197443075233926 26 -0.99620309559996589 31 -0.99620309559996589 37 -0.99620309559996589 
		43 -0.56530392608559166 49 -0.45363002839348088 60 -0.20472824713235571;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 10 1 10 3 
		1 1 10 3 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 10 1 10 3 
		1 1 10 3 3;
	setAttr -s 13 ".kix[5:12]"  1 1 1 1 1 0.59340018033981323 1 1;
	setAttr -s 13 ".kiy[5:12]"  0 0 0 0 0 0.80490750074386597 0 0;
	setAttr -s 13 ".kox[5:12]"  1 1 1 1 1 0.59340018033981323 1 1;
	setAttr -s 13 ".koy[5:12]"  0 0 0 0 0 0.80490750074386597 0 0;
createNode animCurveTL -n "animCurveTL540";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0.20941646546924442 3 0.20941646546924442 
		7 0.20941646546924442 12 0.20941646546924442 15 0.10002671395838875 20 0.11759165103031638 
		23 0.069198154869167805 26 0.090219751688556671 31 0.090219751688556671 37 0.090219751688556671 
		43 0.38974292495055729 49 0.20941646546924442 60 0.20941646546924442;
	setAttr -s 13 ".kit[0:12]"  3 10 10 10 10 1 10 3 
		1 1 10 3 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 10 10 1 10 3 
		1 1 10 3 3;
	setAttr -s 13 ".kix[5:12]"  1 1 1 1 1 0.95835435390472412 1 1;
	setAttr -s 13 ".kiy[5:12]"  0 0 0 0 0 0.28558176755905151 0 0;
	setAttr -s 13 ".kox[5:12]"  1 1 1 1 1 0.95835435390472412 1 1;
	setAttr -s 13 ".koy[5:12]"  0 0 0 0 0 0.28558176755905151 0 0;
createNode animCurveTU -n "animCurveTU533";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 7 0 12 0 20 0 31 0 35 0 49 0 60 
		0;
	setAttr -s 9 ".kit[0:8]"  3 9 9 9 9 1 1 3 
		3;
	setAttr -s 9 ".kot[0:8]"  3 5 5 5 5 5 5 3 
		3;
	setAttr -s 9 ".kix[5:8]"  1 1 1 1;
	setAttr -s 9 ".kiy[5:8]"  0 0 0 0;
createNode animCurveTU -n "animCurveTU534";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.084155864375844894 3 0.084155864375844894 
		7 0.084155864375844894 12 0.084155864375844894 20 0.084155864375844894 31 0.084155864375844894 
		35 0.084155864375844894 49 0.084155864375844894 60 0.084155864375844894;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 1 1 3 
		3;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 1 1 3 
		3;
	setAttr -s 9 ".kix[5:8]"  1 1 1 1;
	setAttr -s 9 ".kiy[5:8]"  0 0 0 0;
	setAttr -s 9 ".kox[5:8]"  1 1 1 1;
	setAttr -s 9 ".koy[5:8]"  0 0 0 0;
createNode animCurveTL -n "animCurveTL541";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 3 0 7 0 12 0.2297786949410261 15 -0.60313439068370889 
		20 -1.2469082496507757 31 -1.2469082496507757 35 -1.2469082496507757 49 0 60 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 1 1 
		3 3;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 1 1 
		3 3;
	setAttr -s 10 ".kix[6:9]"  0.40646973252296448 0.40646973252296448 
		1 1;
	setAttr -s 10 ".kiy[6:9]"  -0.91366422176361084 -0.91366422176361084 
		0 0;
	setAttr -s 10 ".kox[6:9]"  0.40646973252296448 0.40646973252296448 
		1 1;
	setAttr -s 10 ".koy[6:9]"  -0.91366422176361084 -0.91366422176361084 
		0 0;
createNode animCurveTL -n "animCurveTL542";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.40088449385078673 3 -0.40088449385078673 
		7 -0.40088449385078673 12 -0.44206606297010365 15 -0.29141592167924557 20 -0.017480946988826851 
		31 -0.017480946988826851 35 -0.017480946988826851 49 -0.40088449385078673 60 -0.40088449385078673;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 1 1 
		3 3;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 1 1 
		3 3;
	setAttr -s 10 ".kix[6:9]"  1 1 1 1;
	setAttr -s 10 ".kiy[6:9]"  0 0 0 0;
	setAttr -s 10 ".kox[6:9]"  1 1 1 1;
	setAttr -s 10 ".koy[6:9]"  0 0 0 0;
createNode animCurveTL -n "animCurveTL543";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -0.69609418843799409 3 -0.69609418843799409 
		7 -0.69609418843799409 12 -0.92345860309397931 15 -0.40006607163761077 20 -0.36652039457072549 
		31 -0.36652039457072549 35 -0.36652039457072549 43 -0.5382715501820764 49 -0.69609418843799409 
		60 -0.69609418843799409;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 10 10 1 1 
		10 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 10 10 1 1 
		10 3 3;
	setAttr -s 11 ".kix[6:10]"  1 1 0.8168342113494873 1 1;
	setAttr -s 11 ".kiy[6:10]"  0 0 -0.57687240839004517 0 0;
	setAttr -s 11 ".kox[6:10]"  1 1 0.8168342113494873 1 1;
	setAttr -s 11 ".koy[6:10]"  0 0 -0.57687240839004517 0 0;
createNode animCurveTA -n "animCurveTA1714";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 5 26.712271646890017 10 -26.279794579501544 
		15 43.73580089196502 20 0 22 -53.459335626837998 24 -15.688028800591402 26 0 31 0 
		37 -57.643377339735345 44 8.3324053496339801 52 -41.218532252238546 60 0;
	setAttr -s 13 ".kit[0:12]"  9 10 10 1 1 10 10 3 
		1 1 10 10 3;
	setAttr -s 13 ".kot[0:12]"  9 10 10 1 1 10 10 3 
		1 1 10 10 3;
	setAttr -s 13 ".kix[3:12]"  0.58789008855819702 1 0.43780964612960815 
		0.1414647102355957 1 1 0.74649637937545776 0.86752969026565552 0.96477603912353516 
		1;
	setAttr -s 13 ".kiy[3:12]"  -0.8089408278465271 0 -0.89906764030456543 
		0.98994332551956177 0 0 0.66538947820663452 0.49738535284996033 -0.26307255029678345 
		0;
	setAttr -s 13 ".kox[3:12]"  0.58789008855819702 1 0.43780964612960815 
		0.1414647102355957 1 1 0.74649637937545776 0.86752969026565552 0.96477603912353516 
		1;
	setAttr -s 13 ".koy[3:12]"  -0.8089408278465271 0 -0.89906764030456543 
		0.98994332551956177 0 0 0.66538947820663452 0.49738535284996033 -0.26307255029678345 
		0;
createNode animCurveTA -n "animCurveTA1715";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 5 3.7298012982445021 10 -1.247223546744525 
		15 -10.081737493636515 20 0 22 2.666880117062703 24 6.3513136450891512 26 0 31 0 
		37 -0.23465213642999835 44 -2.2685668216753045 52 6.3882114802350012 60 0;
	setAttr -s 13 ".kit[0:12]"  3 10 10 1 1 10 10 3 
		1 1 10 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 1 1 10 10 3 
		1 1 10 10 3;
	setAttr -s 13 ".kix[3:12]"  0.99787449836730957 1 1 0.94412487745285034 
		1 1 0.81031429767608643 1 0.99725562334060669 1;
	setAttr -s 13 ".kiy[3:12]"  -0.065165668725967407 0 0 -0.32958817481994629 
		0 0 -0.58599543571472168 0 0.074034936726093292 0;
	setAttr -s 13 ".kox[3:12]"  0.99787449836730957 1 1 0.94412487745285034 
		1 1 0.81031429767608643 1 0.99725562334060669 1;
	setAttr -s 13 ".koy[3:12]"  -0.065165668725967407 0 0 -0.32958817481994629 
		0 0 -0.58599543571472168 0 0.074034936726093292 0;
createNode animCurveTA -n "animCurveTA1716";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 5 0.69591355335910232 10 -4.9430429289393336 
		15 -31.030997906375969 20 0 22 33.021030055383001 24 15.971320044800335 26 0 31 0 
		37 -2.6971084877187601 44 8.8750990889753165 52 -7.1315788527925221 60 0;
	setAttr -s 13 ".kit[0:12]"  9 10 10 1 1 10 10 3 
		1 1 10 10 3;
	setAttr -s 13 ".kot[0:12]"  9 10 10 1 1 10 10 3 
		1 1 10 10 3;
	setAttr -s 13 ".kix[3:12]"  1 1 0.43150049448013306 0.22539728879928589 
		1 1 0.51573508977890015 0.98823082447052002 0.96031689643859863 1;
	setAttr -s 13 ".kiy[3:12]"  0 0 0.90211266279220581 -0.97426688671112061 
		0 0 -0.85674810409545898 -0.15297043323516846 -0.27891150116920471 0;
	setAttr -s 13 ".kox[3:12]"  1 1 0.43150049448013306 0.22539728879928589 
		1 1 0.51573508977890015 0.98823082447052002 0.96031689643859863 1;
	setAttr -s 13 ".koy[3:12]"  0 0 0.90211266279220581 -0.97426688671112061 
		0 0 -0.85674810409545898 -0.15297043323516846 -0.27891150116920471 0;
createNode animCurveTA -n "animCurveTA1717";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 5 12.58492334431789 10 -17.154359682367385 
		15 12.58492334431789 20 0 21 0 22 8.5356844923408008 26 0 31 0 37 -0.71491477578087848 
		44 0.47208520090330186 52 3.1313420739375388 56 -2.0330819843917562 60 0;
	setAttr -s 14 ".kit[0:13]"  3 10 10 1 1 1 10 3 
		1 1 10 10 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 10 1 1 1 10 3 
		1 1 10 10 10 3;
	setAttr -s 14 ".kix[3:13]"  0.74395960569381714 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".kiy[3:13]"  -0.66822463274002075 0 0 0 0 0 0 0 0 0 
		0;
	setAttr -s 14 ".kox[3:13]"  0.74395960569381714 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 14 ".koy[3:13]"  -0.66822463274002075 0 0 0 0 0 0 0 0 0 
		0;
createNode animCurveTA -n "animCurveTA1718";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 5 -39.644875744902606 10 34.992343210865634 
		15 -39.644875744902606 20 0 21 0 22 13.936848041632743 26 0 31 0 37 41.052618583364783 
		44 0.61012216045246082 52 25.451810936438754 56 -6.9095274864183835 60 0;
	setAttr -s 14 ".kit[0:13]"  3 10 10 1 1 1 10 3 
		1 1 10 10 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 10 1 1 1 10 3 
		1 1 10 10 10 3;
	setAttr -s 14 ".kix[3:13]"  0.47908139228820801 1 1 1 1 1 1 0.87822157144546509 
		0.95016264915466309 0.51468861103057861 1;
	setAttr -s 14 ".kiy[3:13]"  0.87777042388916016 0 0 0 0 0 0 -0.47825393080711365 
		-0.31175467371940613 -0.85737717151641846 0;
	setAttr -s 14 ".kox[3:13]"  0.47908139228820801 1 1 1 1 1 1 0.87822157144546509 
		0.95016264915466309 0.51468861103057861 1;
	setAttr -s 14 ".koy[3:13]"  0.87777042388916016 0 0 0 0 0 0 -0.47825393080711365 
		-0.31175467371940613 -0.85737717151641846 0;
createNode animCurveTA -n "animCurveTA1719";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 5 -0.58572988561787642 10 1.498448646425157 
		15 -0.58572988561787642 20 0 21 0 22 26.247474219153794 26 0 31 0 37 11.861722495295878 
		44 -18.875170062595846 52 33.889460997243738 56 2.2565412109234213 60 0;
	setAttr -s 14 ".kit[0:13]"  3 10 10 1 1 1 10 3 
		1 1 10 10 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 10 1 1 1 10 3 
		1 1 10 10 10 3;
	setAttr -s 14 ".kix[3:13]"  1 1 1 1 1 1 1 0.79274564981460571 0.73518145084381104 
		1 1;
	setAttr -s 14 ".kiy[3:13]"  0 0 0 0 0 0 0 0.60955256223678589 0.67787027359008789 
		0 0;
	setAttr -s 14 ".kox[3:13]"  1 1 1 1 1 1 1 0.79274564981460571 0.73518145084381104 
		1 1;
	setAttr -s 14 ".koy[3:13]"  0 0 0 0 0 0 0 0.60955256223678589 0.67787027359008789 
		0 0;
createNode animCurveTA -n "animCurveTA1720";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 5 25.51560055522004 10 -17.665342906511107 
		15 25.51560055522004 20 0 22 41.350824669442858 24 8.6638639144165186 26 0 31 0 37 
		36.737488452370741 44 -33.078425039082049 48 22.833384522477292 52 15.851342123365063 
		60 0;
	setAttr -s 14 ".kit[0:13]"  3 10 10 1 1 10 10 3 
		1 1 10 10 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 10 1 1 10 10 3 
		1 1 10 10 10 3;
	setAttr -s 14 ".kix[3:13]"  0.7341158390045166 1 0.66137099266052246 
		0.18167254328727722 1 1 1 0.83390575647354126 0.29806742072105408 0.70841813087463379 
		1;
	setAttr -s 14 ".kiy[3:13]"  -0.67902421951293945 0 0.75005900859832764 
		-0.98335903882980347 0 0 0 -0.55190694332122803 0.95454484224319458 -0.70579302310943604 
		0;
	setAttr -s 14 ".kox[3:13]"  0.7341158390045166 1 0.66137099266052246 
		0.18167254328727722 1 1 1 0.83390575647354126 0.29806742072105408 0.70841813087463379 
		1;
	setAttr -s 14 ".koy[3:13]"  -0.67902421951293945 0 0.75005900859832764 
		-0.98335903882980347 0 0 0 -0.55190694332122803 0.95454484224319458 -0.70579302310943604 
		0;
createNode animCurveTA -n "animCurveTA1721";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 5 -2.5652157825959296 10 1.8689092763831858 
		15 -2.5652157825959296 20 0 22 -6.2526139907030176 24 -1.6128664278789404 26 0 31 
		0 37 14.634154094060815 44 14.718126222929691 48 -35.663665386910949 52 -0.88432678515564878 
		60 0;
	setAttr -s 14 ".kit[0:13]"  3 10 10 1 1 10 10 3 
		1 1 10 10 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 10 1 1 10 10 3 
		1 1 10 10 10 3;
	setAttr -s 14 ".kix[3:13]"  1 1 0.97843188047409058 1 1 1 1 1 0.69965916872024536 
		1 1;
	setAttr -s 14 ".kiy[3:13]"  0 0 -0.20657019317150116 0 0 0 0 0 -0.71447676420211792 
		0 0;
	setAttr -s 14 ".kox[3:13]"  1 1 0.97843188047409058 1 1 1 1 1 0.69965916872024536 
		1 1;
	setAttr -s 14 ".koy[3:13]"  0 0 -0.20657019317150116 0 0 0 0 0 -0.71447676420211792 
		0 0;
createNode animCurveTA -n "animCurveTA1722";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 5 2.5495799847117988 10 -3.0520949958905828 
		15 2.5495799847117988 20 0 22 2.5365781801342693 24 0.32343749014021161 26 0 31 0 
		37 -30.360496599500241 44 31.778881885835482 48 1.3754263337624106 52 -6.8126916670198998 
		60 0;
	setAttr -s 14 ".kit[0:13]"  3 10 10 1 1 10 10 3 
		1 1 10 10 10 3;
	setAttr -s 14 ".kot[0:13]"  3 10 10 1 1 10 10 3 
		1 1 10 10 10 3;
	setAttr -s 14 ".kix[3:13]"  1 1 1 1 1 1 1 0.55199003219604492 0.36811184883117676 
		0.99820399284362793 1;
	setAttr -s 14 ".kiy[3:13]"  0 0 0 0 0 0 0 0.8338506817817688 -0.92978155612945557 
		-0.059906516224145889 0;
	setAttr -s 14 ".kox[3:13]"  1 1 1 1 1 1 1 0.55199003219604492 0.36811184883117676 
		0.99820399284362793 1;
	setAttr -s 14 ".koy[3:13]"  0 0 0 0 0 0 0 0.8338506817817688 -0.92978155612945557 
		-0.059906516224145889 0;
createNode animCurveTA -n "animCurveTA1723";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 -18.592620239620459 3 -18.592620239620459 
		7 -26.297602552964037 10 7.1383663631386707 12 15.498709082520833 16 -33.57609446636085 
		18 -31.938926037089111 21 -48.593444358818374 24 -26.775567727172554 31 -3.2668516791574973 
		35 -32.890705804074997 39 -2.0376400645235297 42 -4.8361921574653 49 -17.239996492549441 
		60 -18.592620239620459;
	setAttr -s 15 ".kit[0:14]"  3 10 10 10 10 10 10 10 
		10 1 10 10 10 3 3;
	setAttr -s 15 ".kot[0:14]"  3 10 10 10 10 10 10 10 
		10 1 10 10 10 3 3;
	setAttr -s 15 ".kix[9:14]"  1 0.99677938222885132 1 1 1 1;
	setAttr -s 15 ".kiy[9:14]"  0 0.080192610621452332 0 0 0 0;
	setAttr -s 15 ".kox[9:14]"  1 0.99677938222885132 1 1 1 1;
	setAttr -s 15 ".koy[9:14]"  0 0.080192610621452332 0 0 0 0;
createNode animCurveTA -n "animCurveTA1724";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 -4.0495369920864128 3 -4.0495369920864128 
		7 3.1825666942151591 10 7.7995623741787199 12 -5.6637647838021179 16 0.89571839711514589 
		18 8.6758618699401318 21 -14.774455772635251 24 -10.133733678751366 31 -8.658349639179594 
		35 5.0431761695460215 39 18.695725550953028 42 1.847806113090575 49 -27.02126017677972 
		60 -4.0495369920864128;
	setAttr -s 15 ".kit[0:14]"  1 10 10 10 10 10 10 10 
		10 1 10 10 10 3 3;
	setAttr -s 15 ".kot[0:14]"  1 10 10 10 10 10 10 10 
		10 1 10 10 10 3 3;
	setAttr -s 15 ".kix[0:14]"  0.98620122671127319 1 0.74836665391921997 
		0.73359256982803345 0.85655659437179565 0.62427818775177002 0.5203813910484314 0.52027279138565063 
		1 1 0.48764556646347046 0.97260475158691406 0.38547253608703613 1 1;
	setAttr -s 15 ".kiy[0:14]"  0.16555078327655792 0 0.66328525543212891 
		-0.67958956956863403 -0.51605302095413208 0.78120201826095581 -0.85393399000167847 
		-0.85400015115737915 0 0 0.87304168939590454 -0.23246528208255768 -0.92271929979324341 
		0 0;
	setAttr -s 15 ".kox[0:14]"  0.98620122671127319 1 0.74836665391921997 
		0.73359256982803345 0.85655659437179565 0.62427818775177002 0.5203813910484314 0.52027279138565063 
		1 1 0.48764556646347046 0.97260475158691406 0.38547253608703613 1 1;
	setAttr -s 15 ".koy[0:14]"  0.16555075347423553 0 0.66328525543212891 
		-0.67958956956863403 -0.51605302095413208 0.78120201826095581 -0.85393399000167847 
		-0.85400015115737915 0 0 0.87304168939590454 -0.23246528208255768 -0.92271929979324341 
		0 0;
createNode animCurveTA -n "animCurveTA1725";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 -24.718935474963271 3 -24.718935474963271 
		7 -54.097983969681245 10 -29.568803996529134 12 -30.189733676999893 16 -24.136745889125173 
		18 7.5148405210704246 21 -14.817541461207203 24 -46.243923986014373 31 -35.138089698684716 
		35 -35.491575734809892 39 -53.543253183674864 42 -36.883078549809127 49 -11.258932413433637 
		60 -24.718935474963271;
	setAttr -s 15 ".kit[0:14]"  3 10 10 10 10 10 10 10 
		10 1 10 10 10 3 3;
	setAttr -s 15 ".kot[0:14]"  3 10 10 10 10 10 10 10 
		10 1 10 10 10 3 3;
	setAttr -s 15 ".kix[9:14]"  1 1 0.99462682008743286 0.41163057088851929 
		1 1;
	setAttr -s 15 ".kiy[9:14]"  0 0 -0.10352489352226257 0.9113507866859436 
		0 0;
	setAttr -s 15 ".kox[9:14]"  1 1 0.99462682008743286 0.41163057088851929 
		1 1;
	setAttr -s 15 ".koy[9:14]"  0 0 -0.10352489352226257 0.9113507866859436 
		0 0;
createNode animCurveTA -n "animCurveTA1726";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 5 6.7824702298166155 10 2.555979875253465 
		15 6.7824702298166155 20 0 22 19.525453177059017 24 10.517643179924777 26 0 31 0 
		37 2.555979875253465 44 20.890150259815201 52 10.880964012373962 60 0;
	setAttr -s 13 ".kit[0:12]"  3 10 10 1 1 10 10 3 
		1 1 10 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 1 1 10 10 3 
		1 1 10 10 3;
	setAttr -s 13 ".kix[3:12]"  0.99116313457489014 1 0.5876806378364563 
		0.36435973644256592 1 1 1 0.96027576923370361 0.825531005859375 1;
	setAttr -s 13 ".kiy[3:12]"  0.13264814019203186 0 0.80909299850463867 
		-0.93125826120376587 0 0 0 0.27905303239822388 -0.56435662508010864 0;
	setAttr -s 13 ".kox[3:12]"  0.99116313457489014 1 0.5876806378364563 
		0.36435973644256592 1 1 1 0.96027576923370361 0.825531005859375 1;
	setAttr -s 13 ".koy[3:12]"  0.13264814019203186 0 0.80909299850463867 
		-0.93125826120376587 0 0 0 0.27905303239822388 -0.56435662508010864 0;
createNode animCurveTA -n "animCurveTA1727";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 5 -19.088722079633548 10 36.168919095785604 
		15 -19.088722079633548 20 0 22 14.92307861155259 24 7.4720758327139727 26 0 31 0 
		37 36.168919095785604 44 -22.691968665235919 52 -13.488260062748203 60 0;
	setAttr -s 13 ".kit[0:12]"  3 10 10 1 1 10 10 3 
		1 1 10 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 1 1 10 10 3 
		1 1 10 10 3;
	setAttr -s 13 ".kix[3:12]"  0.46693918108940125 1 0.71489423513412476 
		0.45568254590034485 1 1 1 0.4997161328792572 0.80284541845321655 1;
	setAttr -s 13 ".kiy[3:12]"  0.8842894434928894 0 0.69923263788223267 
		-0.89014232158660889 0 0 0 -0.86618924140930176 0.59618735313415527 0;
	setAttr -s 13 ".kox[3:12]"  0.46693918108940125 1 0.71489423513412476 
		0.45568254590034485 1 1 1 0.4997161328792572 0.80284541845321655 1;
	setAttr -s 13 ".koy[3:12]"  0.8842894434928894 0 0.69923263788223267 
		-0.89014232158660889 0 0 0 -0.86618924140930176 0.59618735313415527 0;
createNode animCurveTA -n "animCurveTA1728";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 5 2.5332672347740206 10 4.9873515920137956 
		15 2.5332672347740206 20 0 22 41.364133595499808 24 8.5029019371973487 26 0 31 0 
		37 4.9873515920137956 44 -16.228426727811247 52 18.131949499371451 60 0;
	setAttr -s 13 ".kit[0:12]"  3 10 10 1 1 10 10 3 
		1 1 10 10 3;
	setAttr -s 13 ".kot[0:12]"  3 10 10 1 1 10 10 3 
		1 1 10 10 3;
	setAttr -s 13 ".kix[3:12]"  1 1 0.6683276891708374 0.18161602318286896 
		1 1 1 0.90889269113540649 0.88318008184432983 1;
	setAttr -s 13 ".kiy[3:12]"  0 0 0.74386698007583618 -0.98336952924728394 
		0 0 0 0.41703000664710999 0.46903404593467712 0;
	setAttr -s 13 ".kox[3:12]"  1 1 0.6683276891708374 0.18161602318286896 
		1 1 1 0.90889269113540649 0.88318008184432983 1;
	setAttr -s 13 ".koy[3:12]"  0 0 0.74386698007583618 -0.98336952924728394 
		0 0 0 0.41703000664710999 0.46903404593467712 0;
createNode animCurveTU -n "animCurveTU535";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 3 1 7 1 12 1 20 1 21 1 26 1 31 1 37 
		1 49 1 60 1;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU536";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 3 1 7 1 12 1 20 1 21 1 26 1 31 1 37 
		1 49 1 60 1;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU537";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 3 1 7 1 12 1 20 1 21 1 26 1 31 1 37 
		1 49 1 60 1;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1729";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1730";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1731";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL544";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 1.0187128762509812e-005 
		21 1.0187128762509812e-005 26 1.0187128762509812e-005 31 1.0187128762509812e-005 
		37 1.0187128762509812e-005 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL545";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 -0.0040756565985249045 
		21 -0.0040756565985249045 26 -0.0040756565985249045 31 -0.0040756565985249045 37 
		-0.0040756565985249045 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL546";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0.0047236676912686473 
		21 0.0047236676912686473 26 0.0047236676912686473 31 0.0047236676912686473 37 0.0047236676912686473 
		49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU538";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 3 1 7 1 12 1 20 1 21 1 26 1 31 1 37 
		1 49 1 60 1;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU539";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 3 1 7 1 12 1 20 1 21 1 26 1 31 1 37 
		1 49 1 60 1;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU540";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 3 1 7 1 12 1 20 1 21 1 26 1 31 1 37 
		1 49 1 60 1;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1732";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1733";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1734";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 0 31 0 37 
		0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL547";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0.00094118920567442036 
		21 0.00094118920567442036 26 0.00094118920567442036 31 0.00094118920567442036 37 
		0.00094118920567442036 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL548";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0.0024052336458700225 
		21 0.0024052336458700225 26 0.0024052336458700225 31 0.0024052336458700225 37 0.0024052336458700225 
		49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL549";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0.0056791840023126582 
		21 0.0056791840023126582 26 0.0056791840023126582 31 0.0056791840023126582 37 0.0056791840023126582 
		49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1735";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 -1.5216569306951431 
		31 -1.5216569306951431 37 0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1736";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0 21 0 26 -0.25237918813884697 
		31 -0.25237918813884697 37 0 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA1737";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 7.2644697342894906 3 7.2644697342894906 
		7 7.2644697342894906 12 7.2644697342894906 20 7.2644697342894906 21 7.2644697342894906 
		26 16.189130260288962 31 16.189130260288962 37 7.2644697342894906 49 7.2644697342894906 
		60 7.2644697342894906;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL550";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 -0.00050498770585966318 
		21 -0.00050498770585966318 26 -0.00050498770585966318 31 -0.00050498770585966318 
		37 -0.00050498770585966318 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL551";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 -0.0061249985522714061 
		21 -0.0061249985522714061 26 -0.0061249985522714061 31 -0.0061249985522714061 37 
		-0.0061249985522714061 49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL552";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 7 0 12 0 20 0.0010740098211054956 
		21 0.0010740098211054956 26 0.0010740098211054956 31 0.0010740098211054956 37 0.0010740098211054956 
		49 0 60 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 1 1 3 1 
		1 3 3;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
	setAttr -s 11 ".kox[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL553";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -0.000119480405310887 3 -0.000119480405310887 
		7 -0.000119480405310887 10 0.24293211521692087 12 0.14822818199098811 20 0.0034820144655119557 
		26 0.0034820144655119557 31 0.0034820144655119557 38 0.055290961561290305 45 0.16639630503221278 
		49 0.18950204099633725 60 -0.000119480405310887;
	setAttr -s 12 ".kit[0:11]"  9 10 10 10 10 1 1 1 
		10 10 3 3;
	setAttr -s 12 ".kot[0:11]"  9 10 10 10 10 1 1 1 
		10 10 3 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 0.94412243366241455 1 1 1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0.32959505915641785 0 0 0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 0.94412243366241455 1 1 1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0.32959505915641785 0 0 0;
createNode animCurveTL -n "animCurveTL554";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0.1152566135867675 3 0.1152566135867675 
		7 0.1152566135867675 10 0.07590417052345777 12 -0.034119798878255919 20 0.1101622800264451 
		26 0.1101622800264451 31 0.1101622800264451 38 0.029418811427716858 45 0.078633993219202475 
		49 0.10832572533151351 60 0.1152566135867675;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 1 1 1 
		10 10 3 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 1 1 1 
		10 10 3 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0 0 0 0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 1 1 1 1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL555";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0.19515846066137013 3 0.19515846066137013 
		7 0.19515846066137013 10 0.23402874935940998 12 0.26740383497702741 20 0.19512503588258506 
		26 0.19512503588258506 31 0.19512503588258506 38 0.21615802070349066 45 0.26756384369125175 
		49 0.13501015738941732 60 0.19515846066137013;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 1 1 1 
		10 10 3 3;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 1 1 1 
		10 10 3 3;
	setAttr -s 12 ".kix[5:11]"  1 1 1 1 0.97637480497360229 1 1;
	setAttr -s 12 ".kiy[5:11]"  0 0 0 0 -0.21608379483222961 0 0;
	setAttr -s 12 ".kox[5:11]"  1 1 1 1 0.97637480497360229 1 1;
	setAttr -s 12 ".koy[5:11]"  0 0 0 0 -0.21608379483222961 0 0;
createNode animCurveTU -n "animCurveTU541";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 60 1;
createNode animCurveTU -n "animCurveTU542";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 60 1;
createNode animCurveTU -n "animCurveTU543";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 60 1;
createNode animCurveTU -n "animCurveTU544";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 60 1;
createNode animCurveTU -n "animCurveTU545";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 60 1;
createNode animCurveTU -n "animCurveTU546";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 60 1;
createNode animCurveTU -n "Ratcatcher_CTRL_JAR_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 20 1 21 1.6089499488068764 22 1.6121214525086798 
		25 1 26 1 60 1;
	setAttr -s 7 ".kit[2:6]"  3 10 1 1 10;
	setAttr -s 7 ".kot[2:6]"  3 10 1 1 10;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[4:6]"  1 1 1;
	setAttr -s 7 ".koy[4:6]"  0 0 0;
createNode animCurveTU -n "Ratcatcher_CTRL_JAR_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 20 1 21 1.6089499488068764 22 1.6121214525086798 
		25 1 26 1 60 1;
	setAttr -s 7 ".kit[2:6]"  3 10 1 1 10;
	setAttr -s 7 ".kot[2:6]"  3 10 1 1 10;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[4:6]"  1 1 1;
	setAttr -s 7 ".koy[4:6]"  0 0 0;
createNode animCurveTU -n "Ratcatcher_CTRL_JAR_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 20 1 21 0.79862812997196342 23 1.0185073545618062 
		24 1 26 1 60 1;
	setAttr -s 7 ".kit[2:6]"  3 10 1 1 10;
	setAttr -s 7 ".kot[2:6]"  3 10 1 1 10;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[4:6]"  1 1 1;
	setAttr -s 7 ".koy[4:6]"  0 0 0;
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
connectAttr "ability1Source.cl" "clipLibrary1.sc[0]";
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
connectAttr "animCurveTA1690.a" "clipLibrary1.cel[0].cev[208].cevr";
connectAttr "animCurveTA1691.a" "clipLibrary1.cel[0].cev[209].cevr";
connectAttr "animCurveTA1692.a" "clipLibrary1.cel[0].cev[210].cevr";
connectAttr "animCurveTL511.a" "clipLibrary1.cel[0].cev[211].cevr";
connectAttr "animCurveTL512.a" "clipLibrary1.cel[0].cev[212].cevr";
connectAttr "animCurveTL513.a" "clipLibrary1.cel[0].cev[213].cevr";
connectAttr "animCurveTU528.a" "clipLibrary1.cel[0].cev[214].cevr";
connectAttr "animCurveTU529.a" "clipLibrary1.cel[0].cev[215].cevr";
connectAttr "animCurveTA1693.a" "clipLibrary1.cel[0].cev[216].cevr";
connectAttr "animCurveTA1694.a" "clipLibrary1.cel[0].cev[217].cevr";
connectAttr "animCurveTA1695.a" "clipLibrary1.cel[0].cev[218].cevr";
connectAttr "animCurveTL514.a" "clipLibrary1.cel[0].cev[219].cevr";
connectAttr "animCurveTL515.a" "clipLibrary1.cel[0].cev[220].cevr";
connectAttr "animCurveTL516.a" "clipLibrary1.cel[0].cev[221].cevr";
connectAttr "animCurveTL517.a" "clipLibrary1.cel[0].cev[222].cevr";
connectAttr "animCurveTL518.a" "clipLibrary1.cel[0].cev[223].cevr";
connectAttr "animCurveTL519.a" "clipLibrary1.cel[0].cev[224].cevr";
connectAttr "animCurveTA1696.a" "clipLibrary1.cel[0].cev[225].cevr";
connectAttr "animCurveTA1697.a" "clipLibrary1.cel[0].cev[226].cevr";
connectAttr "animCurveTA1698.a" "clipLibrary1.cel[0].cev[227].cevr";
connectAttr "animCurveTL520.a" "clipLibrary1.cel[0].cev[228].cevr";
connectAttr "animCurveTL521.a" "clipLibrary1.cel[0].cev[229].cevr";
connectAttr "animCurveTL522.a" "clipLibrary1.cel[0].cev[230].cevr";
connectAttr "animCurveTA1699.a" "clipLibrary1.cel[0].cev[231].cevr";
connectAttr "animCurveTA1700.a" "clipLibrary1.cel[0].cev[232].cevr";
connectAttr "animCurveTA1701.a" "clipLibrary1.cel[0].cev[233].cevr";
connectAttr "animCurveTL523.a" "clipLibrary1.cel[0].cev[234].cevr";
connectAttr "animCurveTL524.a" "clipLibrary1.cel[0].cev[235].cevr";
connectAttr "animCurveTL525.a" "clipLibrary1.cel[0].cev[236].cevr";
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
connectAttr "animCurveTU541.a" "clipLibrary1.cel[0].cev[314].cevr";
connectAttr "animCurveTU542.a" "clipLibrary1.cel[0].cev[315].cevr";
connectAttr "animCurveTU543.a" "clipLibrary1.cel[0].cev[316].cevr";
connectAttr "animCurveTU544.a" "clipLibrary1.cel[0].cev[317].cevr";
connectAttr "animCurveTU545.a" "clipLibrary1.cel[0].cev[318].cevr";
connectAttr "animCurveTU546.a" "clipLibrary1.cel[0].cev[319].cevr";
connectAttr "Ratcatcher_CTRL_JAR_scaleZ.a" "clipLibrary1.cel[0].cev[322].cevr";
connectAttr "Ratcatcher_CTRL_JAR_scaleY.a" "clipLibrary1.cel[0].cev[323].cevr";
connectAttr "Ratcatcher_CTRL_JAR_scaleX.a" "clipLibrary1.cel[0].cev[324].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of ability01.ma
