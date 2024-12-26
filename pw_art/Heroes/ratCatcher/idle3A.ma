//Maya ASCII 2008 scene
//Name: idle3A.ma
//Last modified: Mon, Dec 28, 2009 03:18:16 PM
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
createNode animClip -n "idle03Source";
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
	setAttr ".se" 150;
	setAttr ".ci" no;
createNode animCurveTU -n "animCurveTU546";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1740";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1741";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 3.1805546814635176e-015;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1742";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 9.9392333795734924e-017;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU547";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU548";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU549";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 11 1 25 1 40 1 50 1 85 1 95 1 120 1 
		135 1 150 1;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU550";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1743";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 3.1805546814635168e-015 11 0 25 0 40 
		2.8497769727521749e-015 50 2.7273256707060641e-015 85 2.7273256707060641e-015 95 
		2.1866309786572937e-015 120 2.1866309786572937e-015 135 0 150 3.1805546814635168e-015;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1744";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1745";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 4.7708320221952728e-015 11 0 25 0 40 
		4.2746654591282603e-015 50 4.0909885060590932e-015 85 4.0909885060590932e-015 95 
		3.2799464679859378e-015 120 3.2799464679859378e-015 135 0 150 4.7708320221952728e-015;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU551";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU552";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL556";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.40930268174563 11 0.27215343887090881 
		25 0.27215343887090881 40 0.27215343887090881 50 0.27215343887090881 85 0.27215343887090881 
		95 0.27215343887090881 120 0.27215343887090881 135 0.40930268174563 150 0.40930268174563;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL557";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.25860394298924627 11 0.28928992319322655 
		25 0.28928992319322655 40 0.28928992319322655 50 0.28928992319322655 85 0.28928992319322655 
		95 0.28928992319322655 120 0.28928992319322655 135 0.25860394298924627 150 0.25860394298924627;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL558";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.29847095663485657 11 -0.29434312118436035 
		25 -0.29434312118436035 40 -0.29434312118436035 50 -0.29434312118436035 85 -0.29434312118436035 
		95 -0.29434312118436035 120 -0.29434312118436035 135 -0.29847095663485657 150 -0.29847095663485657;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1746";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1747";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 3.1805546814635168e-015;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1748";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -7.9513867036587899e-016;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1749";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 25.675870473757751 11 25.675870473757751 
		25 25.675870473757751 40 25.675870473757751 50 25.675870473757751 85 25.675870473757751 
		95 25.675870473757751 120 25.675870473757751 135 25.675870473757751 150 25.675870473757751;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1750";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -3.0739741698828946 11 -3.0739741698828946 
		25 -3.0739741698828946 40 -3.0739741698828946 50 -3.0739741698828946 85 -3.0739741698828946 
		95 -3.0739741698828946 120 -3.0739741698828946 135 -3.0739741698828946 150 -3.0739741698828946;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "Ratcatcher_Ratcatcher_rt_arm_ik_ctrl_maxStretch";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 3 11 3 25 3 40 3 50 3 85 3 95 3 120 3 
		135 3 150 3;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
createNode animCurveTU -n "Ratcatcher_Ratcatcher_rt_arm_ik_ctrl_stretchyArm";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
createNode animCurveTU -n "Ratcatcher_Ratcatcher_rt_arm_ik_ctrl_pvControl";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 11 1 25 1 40 1 50 1 85 1 95 1 120 1 
		135 1 150 1;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
createNode animCurveTU -n "Ratcatcher_Ratcatcher_rt_arm_ik_ctrl_armTwist";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
createNode animCurveTA -n "animCurveTA1751";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 93.144161708979723 11 126.3235101346617 
		25 120.65335145877127 40 119.98749792148767 50 117.49629453594112 85 116.51741561688861 
		95 121.46718433094573 120 120.06734168140227 135 93.144161708979723 150 93.144161708979723;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1752";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 95.049826002206416 11 137.47881760237064 
		25 127.03145642172701 40 125.80461034207781 50 122.95765206379731 85 122.27112009796613 
		95 130.23171446977869 120 128.76518180251625 135 95.049826002206416 150 95.049826002206416;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1753";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1.1812364035166698 11 35.739510735803336 
		25 35.63643060464927 40 35.624325781806974 50 36.783119420089356 85 36.8830918516691 
		95 35.612511283773095 120 34.952188613906976 135 1.1812364035166698 150 1.1812364035166698;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL559";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -0.23689498628395578 5 -0.55520881938820821 
		11 -0.69497234545255149 25 -0.63436662270991451 40 -0.62724961995405593 50 -0.6334776853244346 
		85 -0.64939114086993333 95 -0.60231887301353049 120 -0.61966709033571987 128 -0.56191502603338916 
		135 -0.23689498628395578 150 -0.23689498628395578;
	setAttr -s 12 ".kit[0:11]"  3 10 9 9 9 9 9 9 
		3 10 9 3;
	setAttr -s 12 ".kot[0:11]"  3 10 9 9 9 9 9 9 
		3 10 9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL560";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -0.30633990936382105 5 -0.2617505613008711 
		11 -0.37069500202211031 25 -0.31465528140638305 40 -0.30807446986912718 50 -0.31637513453792043 
		85 -0.3305261323904673 95 -0.29755311850247412 120 -0.30269663292824639 128 -0.22803845097462722 
		135 -0.30633990936382105 150 -0.30633990936382105;
	setAttr -s 12 ".kit[0:11]"  3 10 9 9 1 1 9 1 
		9 10 9 3;
	setAttr -s 12 ".kot[0:11]"  3 10 9 9 1 1 9 1 
		9 10 9 3;
	setAttr -s 12 ".kix[4:11]"  0.99989545345306396 0.99964612722396851 
		0.99992132186889648 0.99990987777709961 0.99800914525985718 0.99997353553771973 0.99434787034988403 
		1;
	setAttr -s 12 ".kiy[4:11]"  -0.014459051191806793 -0.026602268218994141 
		0.01254702266305685 0.013426017947494984 0.063069336116313934 -0.0072863600216805935 
		-0.10617124289274216 0;
	setAttr -s 12 ".kox[4:11]"  0.99989545345306396 0.99964612722396851 
		0.99992132186889648 0.99990987777709961 0.99800914525985718 0.99997353553771973 0.99434787034988403 
		1;
	setAttr -s 12 ".koy[4:11]"  -0.014459051191806793 -0.026602273806929588 
		0.01254702266305685 0.013426018878817558 0.063069336116313934 -0.0072863600216805935 
		-0.10617124289274216 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL561";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0.52899036848843184 5 0.49111333349168218 
		11 0.31667702724172947 25 0.28361742935355416 40 0.2797352011155988 50 0.26450360111752863 
		85 0.26246459319041737 95 0.23673384026515495 120 0.22199647867452424 128 0.440738378418571 
		135 0.52899036848843184 150 0.52899036848843184;
	setAttr -s 12 ".kit[0:11]"  3 10 9 9 9 9 9 9 
		3 10 9 3;
	setAttr -s 12 ".kot[0:11]"  3 10 9 9 9 9 9 9 
		3 10 9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU553";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1754";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -24.884454396993167 11 5.8642409724235964 
		25 1.2126594500207368 40 0.66641867005989508 50 3.5141564604959026 85 3.5141564604959026 
		95 4.1836977062130627 120 4.1836977062130627 135 -24.884454396993167 150 -24.884454396993167;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1755";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -43.339475474578435 11 -15.015377997591536 
		25 -20.339124223871089 40 -20.964298132143682 50 -26.567488871658075 85 -26.567488871658075 
		95 -24.711577958000952 120 -24.711577958000952 135 -43.339475474578435 150 -43.339475474578435;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1756";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 11.606559612787883 11 -15.639911270134734 
		25 -13.837515466937644 40 -13.625857965497026 50 -18.905415851980653 85 -18.905415851980653 
		95 -17.786811312136962 120 -17.786811312136962 135 11.606559612787883 150 11.606559612787883;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU554";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU555";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU556";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU557";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1757";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 3.9531091186723013 11 -9.6461201241950612 
		25 -9.6461201241950612 40 -9.6461201241950612 50 -10.441178674244219 85 -10.441178674244219 
		95 -11.87781871907417 120 -11.87781871907417 135 3.9531091186723013 150 3.9531091186723013;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1758";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.62018686761647346 11 -5.4246027514559305 
		25 -5.4246027514559305 40 -5.4246027514559305 50 -7.6717492785582584 85 -7.6717492785582584 
		95 -2.6305296180878295 120 -2.6305296180878295 135 0.62018686761647346 150 0.62018686761647346;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1759";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 5.3292188742882338 11 -15.695958707884294 
		25 -15.695958707884294 40 -15.695958707884294 50 -19.140353096583798 85 -19.140353096583798 
		95 -13.515681183695488 120 -13.515681183695488 135 5.3292188742882338 150 5.3292188742882338;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU558";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU559";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL562";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL563";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL564";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.1102230246251565e-016;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1760";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -44.757110789561033 11 -12.467725197776717 
		25 -12.467725197776717 40 -12.467725197776717 50 -10.467915730313122 85 -10.467915730313122 
		95 -17.460560608474477 120 -17.460560608474477 135 -44.757110789561033 150 -44.757110789561033;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "Ratcatcher_Ratcatcher_lf_elbow_fk_ctrl_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 -0.20445810425168612 
		85 -0.20445810425168612 95 -1.3289341633742529 120 -1.3289341633742529 135 0 150 
		0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
createNode animCurveTA -n "Ratcatcher_Ratcatcher_lf_elbow_fk_ctrl_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 -1.9691704716219942 
		85 -1.9691704716219942 95 3.134370312284553 120 3.134370312284553 135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
createNode animCurveTA -n "animCurveTA1763";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -27.604588158357807 11 -27.604588158357807 
		25 -27.604588158357807 40 -27.604588158357807 50 -27.604588158357807 85 -27.604588158357807 
		95 -27.604588158357807 120 -27.604588158357807 135 -27.604588158357807 150 -27.604588158357807;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1764";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.70641431476594085 11 0.70641431476594085 
		25 0.70641431476594085 40 0.70641431476594085 50 0.70641431476594085 85 0.70641431476594085 
		95 0.70641431476594085 120 0.70641431476594085 135 0.70641431476594085 150 0.70641431476594085;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU560";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU561";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 3;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU562";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU563";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU564";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1765";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1766";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1767";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL565";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 2.2204460492503131e-016;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL566";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL567";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 4.4408920985006262e-016;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU565";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 11 1 25 1 40 1 50 1 85 1 95 1 120 1 
		135 1 150 1;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1768";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1.1288109940741509 11 6.5212821470394617 
		25 6.5212821470394617 40 6.5212821470394617 50 6.5212821470394617 85 6.5212821470394617 
		95 6.5212821470394617 120 6.5212821470394617 135 1.1288109940741509 150 1.1288109940741509;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1769";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 4.8219581414201906 11 3.6599559232645924 
		25 3.6599559232645924 40 3.6599559232645924 50 3.6599559232645924 85 3.6599559232645924 
		95 3.6599559232645924 120 3.6599559232645924 135 4.8219581414201906 150 4.8219581414201906;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1770";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 28.08558650754679 11 21.908941951235406 
		25 21.908941951235406 40 21.908941951235406 50 21.908941951235406 85 21.908941951235406 
		95 21.908941951235406 120 21.908941951235406 135 28.08558650754679 150 28.08558650754679;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU566";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1771";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 68.629003384766676 11 68.629003384766676 
		25 68.629003384766676 40 68.629003384766676 50 68.629003384766676 85 68.629003384766676 
		95 68.629003384766676 120 68.629003384766676 135 68.629003384766676 150 68.629003384766676;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1772";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 5.1251585428584878 11 5.1251585428584878 
		25 5.1251585428584878 40 5.1251585428584878 50 5.1251585428584878 85 5.1251585428584878 
		95 5.1251585428584878 120 5.1251585428584878 135 5.1251585428584878 150 5.1251585428584878;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1773";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -1.4794141658124507 11 -1.4794141658124507 
		25 -1.4794141658124507 40 -1.4794141658124507 50 -1.4794141658124507 85 -1.4794141658124507 
		95 -1.4794141658124507 120 -1.4794141658124507 135 -1.4794141658124507 150 -1.4794141658124507;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1774";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 2.9967431843380723 11 2.9967431843380723 
		25 2.9967431843380723 40 2.9967431843380723 50 2.9967431843380723 85 2.9967431843380723 
		95 2.9967431843380723 120 2.9967431843380723 135 2.9967431843380723 150 2.9967431843380723;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1775";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 27.356153209428296 11 27.356153209428296 
		25 27.356153209428296 40 27.356153209428296 50 27.356153209428296 85 27.356153209428296 
		95 27.356153209428296 120 27.356153209428296 135 27.356153209428296 150 27.356153209428296;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1776";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 4.8891453517792058 11 4.8891453517792058 
		25 4.8891453517792058 40 4.8891453517792058 50 4.8891453517792058 85 4.8891453517792058 
		95 4.8891453517792058 120 4.8891453517792058 135 4.8891453517792058 150 4.8891453517792058;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU567";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1777";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 59.032884886088816 11 59.032884886088816 
		25 59.032884886088816 40 59.032884886088816 50 59.032884886088816 85 59.032884886088816 
		95 59.032884886088816 120 59.032884886088816 135 59.032884886088816 150 59.032884886088816;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1778";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1779";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1780";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 61.945270723308987 11 61.945270723308987 
		25 61.945270723308987 40 61.945270723308987 50 61.945270723308987 85 61.945270723308987 
		95 61.945270723308987 120 61.945270723308987 135 61.945270723308987 150 61.945270723308987;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1781";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1782";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU568";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1783";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 59.032884886088816 11 59.032884886088816 
		25 59.032884886088816 40 59.032884886088816 50 59.032884886088816 85 59.032884886088816 
		95 59.032884886088816 120 59.032884886088816 135 59.032884886088816 150 59.032884886088816;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1784";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1785";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1786";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 61.945270723308987 11 61.945270723308987 
		25 61.945270723308987 40 61.945270723308987 50 61.945270723308987 85 61.945270723308987 
		95 61.945270723308987 120 61.945270723308987 135 61.945270723308987 150 61.945270723308987;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1787";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1788";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU569";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1789";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 59.032884886088816 11 59.032884886088816 
		25 59.032884886088816 40 59.032884886088816 50 59.032884886088816 85 59.032884886088816 
		95 59.032884886088816 120 59.032884886088816 135 59.032884886088816 150 59.032884886088816;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1790";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1791";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1792";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 72.878304588436421 11 72.878304588436421 
		25 72.878304588436421 40 72.878304588436421 50 72.878304588436421 85 72.878304588436421 
		95 72.878304588436421 120 72.878304588436421 135 72.878304588436421 150 72.878304588436421;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1793";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1794";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU570";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1795";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 77.67986202714836 11 77.67986202714836 
		25 77.67986202714836 40 77.67986202714836 50 77.67986202714836 85 77.67986202714836 
		95 77.67986202714836 120 77.67986202714836 135 77.67986202714836 150 77.67986202714836;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1796";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1797";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1798";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 65.952779168408995 11 65.952779168408995 
		25 65.952779168408995 40 65.952779168408995 50 65.952779168408995 85 65.952779168408995 
		95 65.952779168408995 120 65.952779168408995 135 65.952779168408995 150 65.952779168408995;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1799";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 12.091864976351665 11 12.091864976351665 
		25 12.091864976351665 40 12.091864976351665 50 12.091864976351665 85 12.091864976351665 
		95 12.091864976351665 120 12.091864976351665 135 12.091864976351665 150 12.091864976351665;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1800";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -6.5683373417752975 11 -6.5683373417752975 
		25 -6.5683373417752975 40 -6.5683373417752975 50 -6.5683373417752975 85 -6.5683373417752975 
		95 -6.5683373417752975 120 -6.5683373417752975 135 -6.5683373417752975 150 -6.5683373417752975;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1801";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1802";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1803";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU571";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1804";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 -17.794570176717205 25 10.914435463845011 
		40 0 50 -5.5975963921837559 85 -6.111284706895896 95 9.7130461321871149 120 5.7697882829445772 
		135 -8.8265672858744253 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1805";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 -0.56846098612986351 25 0 40 0 50 
		1.2375570474076674 85 1.1917647411581431 95 -1.0822738672071588 120 -1.054563920346705 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1806";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 3.5598874834537142 25 0 40 0 50 
		0.065698846216695264 85 1.6583161444419803 95 3.0689696698358264 120 2.1491137948388586 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1807";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1808";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1809";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU572";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1810";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 -6.596562865194608 25 5.7327317365079109 
		40 0 50 0 85 3.9488175570114916 95 19.314904526400593 120 13.434748066410918 135 
		-4.8146706001045869 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1811";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1812";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1813";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 -6.596562865194608 25 5.7327317365079109 
		40 0 50 0 85 3.9488175570114916 95 19.314904526400593 120 13.434748066410918 135 
		-4.8146706001045869 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1814";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1815";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU573";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1816";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 -6.596562865194608 25 5.7327317365079109 
		40 0 50 0 85 3.9488175570114916 95 19.314904526400593 120 13.434748066410918 135 
		-4.8146706001045869 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1817";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1818";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1819";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 -6.596562865194608 25 5.7327317365079109 
		40 0 50 0 85 3.9488175570114916 95 19.314904526400593 120 13.434748066410918 135 
		-4.8146706001045869 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1820";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1821";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU574";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1822";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 -6.596562865194608 25 5.7327317365079109 
		40 0 50 0 85 3.9488175570114916 95 19.314904526400593 120 13.434748066410918 135 
		-4.8146706001045869 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1823";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1824";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1825";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 -6.596562865194608 25 5.7327317365079109 
		40 0 50 0 85 3.9488175570114916 95 19.314904526400593 120 13.434748066410918 135 
		-4.8146706001045869 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1826";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1827";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU575";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1828";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 -6.596562865194608 25 5.7327317365079109 
		40 0 50 0 85 3.9488175570114916 95 19.314904526400593 120 13.434748066410918 135 
		-4.8146706001045869 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1829";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1830";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1831";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 -6.596562865194608 25 5.7327317365079109 
		40 0 50 0 85 3.9488175570114916 95 19.314904526400593 120 13.434748066410918 135 
		-4.8146706001045869 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1832";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1833";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1834";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1835";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1836";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU576";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU577";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU578";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 11 1 25 1 40 1 50 1 85 1 95 1 120 1 
		135 1 150 1;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1837";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -10.173354040024311 11 -10.173354040024311 
		25 -10.173354040024311 40 -10.173354040024311 50 -10.173354040024311 85 -10.173354040024311 
		95 -10.173354040024311 120 -10.173354040024311 135 -10.173354040024311 150 -10.173354040024311;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1838";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1839";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL568";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL569";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.643246524321337 11 0.643246524321337 
		25 0.643246524321337 40 0.643246524321337 50 0.643246524321337 85 0.643246524321337 
		95 0.643246524321337 120 0.643246524321337 135 0.643246524321337 150 0.643246524321337;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL570";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.10481400598920043 11 0.10481400598920043 
		25 0.10481400598920043 40 0.10481400598920043 50 0.10481400598920043 85 0.10481400598920043 
		95 0.10481400598920043 120 0.10481400598920043 135 0.10481400598920043 150 0.10481400598920043;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1840";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1841";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1842";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU579";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1843";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1844";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1845";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1846";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1847";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1848";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1849";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1850";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1851";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU580";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 11 1 25 1 40 1 50 1 85 1 95 1 120 1 
		135 1 150 1;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1852";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 40.718223104721211 11 0 25 0 40 0 50 
		0 85 0 95 0 120 0 135 40.718223104721211 150 40.718223104721211;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1853";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -38.301705751263519 11 0 25 0 40 0 50 
		0 85 0 95 0 120 0 135 -38.301705751263519 150 -38.301705751263519;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1854";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 21.733945627788874 11 0 25 0 40 0 50 
		0 85 0 95 0 120 0 135 21.733945627788874 150 21.733945627788874;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU581";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU582";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU583";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 11 1 25 1 40 1 50 1 85 1 95 1 120 1 
		135 1 150 1;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1855";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 17.962181958626559 11 17.962181958626559 
		25 17.962181958626559 40 17.962181958626559 50 17.962181958626559 85 17.962181958626559 
		95 17.962181958626559 120 17.962181958626559 135 17.962181958626559 150 17.962181958626559;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1856";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1857";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL571";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL572";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.64789329560123088 11 -0.64789329560123088 
		25 -0.64789329560123088 40 -0.64789329560123088 50 -0.64789329560123088 85 -0.64789329560123088 
		95 -0.64789329560123088 120 -0.64789329560123088 135 -0.64789329560123088 150 -0.64789329560123088;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL573";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.07395615046270454 11 -0.07395615046270454 
		25 -0.07395615046270454 40 -0.07395615046270454 50 -0.07395615046270454 85 -0.07395615046270454 
		95 -0.07395615046270454 120 -0.07395615046270454 135 -0.07395615046270454 150 -0.07395615046270454;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1858";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1859";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1860";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU584";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1861";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1862";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1863";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1864";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1865";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1866";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1867";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1868";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1869";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1870";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -10.753373031419716 11 0 25 0 40 0 50 
		0 85 0 95 1.6727271674184243 120 1.6727271674184243 135 -10.753373031419716 150 -10.753373031419716;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1871";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -4.9387346018875373 11 0 25 0 40 0 50 
		0 85 0 95 -0.37608731251561645 120 -0.37608731251561645 135 -4.9387346018875373 150 
		-4.9387346018875373;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1872";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 22.393157938684443 11 0 25 0 40 0 50 
		0 85 0 95 0.39978346285793237 120 0.39978346285793237 135 22.393157938684443 150 
		22.393157938684443;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1873";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -4.0865779949808214 11 0 25 0 40 0 50 
		0 85 0 95 0 120 0 135 -4.0865779949808214 150 -4.0865779949808214;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1874";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -10.471027640707172 11 0 25 0 40 0 50 
		0 85 0 95 0 120 0 135 -10.471027640707172 150 -10.471027640707172;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1875";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -1.7475532445702493 11 0 25 0 40 0 50 
		0 85 0 95 0 120 0 135 -1.7475532445702493 150 -1.7475532445702493;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU585";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 11 1 25 1 40 1 50 1 85 1 95 1 120 1 
		135 1 150 1;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1876";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 20.69101533741409 11 20.848459182445371 
		25 20.848459182445371 40 20.848459182445371 50 -10.064002685443159 85 -10.064002685443159 
		95 55.901450409778583 120 55.901450409778583 135 20.69101533741409 150 20.69101533741409;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1877";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -8.3978566024888135 11 1.8451055005225232 
		25 1.8451055005225232 40 1.8451055005225232 50 7.4621485032601322 85 7.4621485032601322 
		95 -11.562603680756865 120 -11.562603680756865 135 -8.3978566024888135 150 -8.3978566024888135;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1878";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 2.8255796210686652 11 -1.0698396187215313 
		25 -1.0698396187215313 40 -1.0698396187215313 50 -8.5128859305418061 85 -8.5128859305418061 
		95 1.8521932477821659 120 1.8521932477821659 135 2.8255796210686652 150 2.8255796210686652;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU586";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 11 0 40 0 50 0 85 0 95 0 120 0 135 
		0 150 0;
	setAttr -s 9 ".kit[0:8]"  3 9 9 9 9 9 9 9 
		3;
	setAttr -s 9 ".kot[0:8]"  3 9 9 9 9 9 9 9 
		3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1879";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 11 0.57685692349760365 19 -0.55980200806970115 
		30 -0.91912024543184245 40 0 50 0 85 0 95 0 120 0 129 0.70292218835639397 135 -0.67160204003789414 
		143 4.1201993251276958 150 0;
	setAttr -s 13 ".kit[0:12]"  3 9 10 10 9 9 9 9 
		9 10 9 10 3;
	setAttr -s 13 ".kot[0:12]"  3 9 10 10 9 9 9 9 
		9 10 9 10 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1880";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 11 -7.8497968786593377 19 4.5587302014087578 
		30 -1.9051096943478643 40 0 50 0 85 0 95 0 120 0 129 -4.9744579681075241 135 4.4531221934565464 
		143 -1.9440889554512633 150 0;
	setAttr -s 13 ".kit[0:12]"  3 9 10 10 9 9 9 9 
		9 10 9 10 3;
	setAttr -s 13 ".kot[0:12]"  3 9 10 10 9 9 9 9 
		9 10 9 10 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1881";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 11 2.9421019443436514 19 -1.8505937242473276 
		30 0.40896631938727807 40 0 50 0 85 0 95 0 120 0 129 2.8403495755386841 135 -4.7021718240109385 
		143 -5.9892689276118984 150 0;
	setAttr -s 13 ".kit[0:12]"  3 9 10 10 9 9 9 9 
		9 10 9 10 3;
	setAttr -s 13 ".kot[0:12]"  3 9 10 10 9 9 9 9 
		9 10 9 10 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1882";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -17.821366541589882 11 -17.821366541589882 
		25 -17.821366541589882 40 -17.821366541589882 50 -17.821366541589882 85 -17.821366541589882 
		95 -17.821366541589882 120 -17.821366541589882 135 -17.821366541589882 150 -17.821366541589882;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1883";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -12.005893876475762 11 -12.005893876475762 
		25 -12.005893876475762 40 -12.005893876475762 50 -12.005893876475762 85 -12.005893876475762 
		95 -12.005893876475762 120 -12.005893876475762 135 -12.005893876475762 150 -12.005893876475762;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1884";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 9.1378572146953019 11 9.1378572146953019 
		25 9.1378572146953019 40 9.1378572146953019 50 9.1378572146953019 85 9.1378572146953019 
		95 9.1378572146953019 120 9.1378572146953019 135 9.1378572146953019 150 9.1378572146953019;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1885";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 -28.841216077843235 5 1.6024502633811255 
		11 23.477740980382233 20 38.288052185240836 30 28.716068248104577 40 23.373348635227018 
		50 31.515186163734221 65 35.303095343847218 85 30.732743458210734 95 30.732743458210734 
		120 30.732743458210734 130 -10.638084692606359 135 -8.4173707599515559 141 -28.407732284036157 
		150 -28.841216077843235;
	setAttr -s 15 ".kit[0:14]"  3 10 9 10 10 9 9 10 
		9 9 9 10 9 10 3;
	setAttr -s 15 ".kot[0:14]"  3 10 9 10 10 9 9 10 
		9 9 9 10 9 10 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1886";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 -21.716766331039956 5 -0.99931114165744817 
		11 8.1140197740611217 20 10.423764369674336 30 4.0912215946117154 40 11.199415850965988 
		50 8.3576847792857656 65 7.57650952351909 85 12.712105654813614 95 12.712105654813614 
		120 12.712105654813614 130 -11.196846297734837 135 -14.072237311725345 141 -27.511980767444243 
		150 -21.716766331039956;
	setAttr -s 15 ".kit[0:14]"  3 10 9 10 10 9 9 10 
		9 9 9 10 9 10 3;
	setAttr -s 15 ".kot[0:14]"  3 10 9 10 10 9 9 10 
		9 9 9 10 9 10 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1887";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 23.535235892507558 5 40.298481235535327 
		11 74.681766139293515 20 117.39162029279662 30 68.024750399226974 40 91.167683511762675 
		50 72.978676169485951 65 85.894005497787575 85 83.672463881413989 95 83.672463881413989 
		120 83.672463881413989 130 41.910476838907165 135 12.367159858434752 141 29.756234531981796 
		150 23.535235892507558;
	setAttr -s 15 ".kit[0:14]"  3 10 9 10 10 9 9 10 
		9 9 9 10 9 10 3;
	setAttr -s 15 ".kot[0:14]"  3 10 9 10 10 9 9 10 
		9 9 9 10 9 10 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL574";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 40 0 50 0 85 0 95 0 120 0 130 
		0 135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 10 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 10 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL575";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 40 0 50 0 85 0 95 0 120 0 130 
		0 135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 10 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 10 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL576";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 40 0 50 0 85 0 95 0 120 0 130 
		0 135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 10 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 10 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU587";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 2 11 2 25 2 40 2 50 2 85 2 95 2 120 2 
		135 2 150 2;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU588";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1888";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -24.093441664171177 11 -24.093441664171177 
		25 -24.093441664171177 40 -24.093441664171177 50 -24.093441664171177 85 -24.093441664171177 
		95 -24.093441664171177 120 -24.093441664171177 135 -24.093441664171177 150 -24.093441664171177;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1889";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 49.48465546224881 11 49.48465546224881 
		25 49.48465546224881 40 49.48465546224881 50 49.48465546224881 85 49.48465546224881 
		95 49.48465546224881 120 49.48465546224881 135 49.48465546224881 150 49.48465546224881;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1890";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 58.801792680015588 11 58.801792680015588 
		25 58.801792680015588 40 58.801792680015588 50 58.801792680015588 85 58.801792680015588 
		95 58.801792680015588 120 58.801792680015588 135 58.801792680015588 150 58.801792680015588;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL577";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -1.2755255474500937 11 -1.2755255474500937 
		25 -1.2755255474500937 40 -1.2755255474500937 50 -1.2755255474500937 85 -1.2755255474500937 
		95 -1.2755255474500937 120 -1.2755255474500937 135 -1.2755255474500937 150 -1.2755255474500937;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL578";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -1.4392043230118035 11 -1.4392043230118035 
		25 -1.4392043230118035 40 -1.4392043230118035 50 -1.4392043230118035 85 -1.4392043230118035 
		95 -1.4392043230118035 120 -1.4392043230118035 135 -1.4392043230118035 150 -1.4392043230118035;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL579";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -2.1802956492995231 11 -2.1802956492995231 
		25 -2.1802956492995231 40 -2.1802956492995231 50 -2.1802956492995231 85 -2.1802956492995231 
		95 -2.1802956492995231 120 -2.1802956492995231 135 -2.1802956492995231 150 -2.1802956492995231;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL580";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL581";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL582";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1891";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1.1134085745786892 11 1.1134085745786892 
		25 1.1134085745786892 40 1.1134085745786892 50 1.1134085745786892 85 1.1134085745786892 
		95 1.1134085745786892 120 1.1134085745786892 135 1.1134085745786892 150 1.1134085745786892;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1892";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -5.3180374758492821 11 -5.3180374758492821 
		25 -5.3180374758492821 40 -5.3180374758492821 50 -5.3180374758492821 85 -5.3180374758492821 
		95 -5.3180374758492821 120 -5.3180374758492821 135 -5.3180374758492821 150 -5.3180374758492821;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1893";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 7.8609313736722894 11 7.8609313736722894 
		25 7.8609313736722894 40 7.8609313736722894 50 7.8609313736722894 85 7.8609313736722894 
		95 7.8609313736722894 120 7.8609313736722894 135 7.8609313736722894 150 7.8609313736722894;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL583";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL584";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL585";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1894";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1895";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1896";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL586";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL587";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL588";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU589";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1897";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -5.1107219305963252 11 -5.1107219305963252 
		25 -5.1107219305963252 40 -5.1107219305963252 50 -5.1107219305963252 85 -5.1107219305963252 
		95 -5.1107219305963252 120 -5.1107219305963252 135 -5.1107219305963252 150 -5.1107219305963252;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1898";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 8.2811672786141717 11 8.2811672786141717 
		25 8.2811672786141717 40 8.2811672786141717 50 8.2811672786141717 85 8.2811672786141717 
		95 8.2811672786141717 120 8.2811672786141717 135 8.2811672786141717 150 8.2811672786141717;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1899";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.92645454014921158 11 -0.92645454014921158 
		25 -0.92645454014921158 40 -0.92645454014921158 50 -0.92645454014921158 85 -0.92645454014921158 
		95 -0.92645454014921158 120 -0.92645454014921158 135 -0.92645454014921158 150 -0.92645454014921158;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL589";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.046856395845859107 11 -0.046856395845859107 
		25 -0.046856395845859107 40 -0.046856395845859107 50 -0.046856395845859107 85 -0.046856395845859107 
		95 -0.046856395845859107 120 -0.046856395845859107 135 -0.046856395845859107 150 
		-0.046856395845859107;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL590";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.023348763690700665 11 -0.023348763690700665 
		25 -0.023348763690700665 40 -0.023348763690700665 50 -0.023348763690700665 85 -0.023348763690700665 
		95 -0.023348763690700665 120 -0.023348763690700665 135 -0.023348763690700665 150 
		-0.023348763690700665;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL591";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.13506113021862395 11 -0.13506113021862395 
		25 -0.13506113021862395 40 -0.13506113021862395 50 -0.13506113021862395 85 -0.13506113021862395 
		95 -0.13506113021862395 120 -0.13506113021862395 135 -0.13506113021862395 150 -0.13506113021862395;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1900";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -1.6266160090263075 11 -1.6266160090263075 
		25 -1.6266160090263075 40 -1.6266160090263075 50 -1.6266160090263075 85 -1.6266160090263075 
		95 -1.6266160090263075 120 -1.6266160090263075 135 -1.6266160090263075 150 -1.6266160090263075;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1901";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 2.8499857758927387 11 2.8499857758927387 
		25 2.8499857758927387 40 2.8499857758927387 50 2.8499857758927387 85 2.8499857758927387 
		95 2.8499857758927387 120 2.8499857758927387 135 2.8499857758927387 150 2.8499857758927387;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1902";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -25.210898828531619 11 -25.210898828531619 
		25 -25.210898828531619 40 -25.210898828531619 50 -25.210898828531619 85 -25.210898828531619 
		95 -25.210898828531619 120 -25.210898828531619 135 -25.210898828531619 150 -25.210898828531619;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL592";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.011193700785458628 11 -0.011193700785458628 
		25 -0.011193700785458628 40 -0.011193700785458628 50 -0.011193700785458628 85 -0.011193700785458628 
		95 -0.011193700785458628 120 -0.011193700785458628 135 -0.011193700785458628 150 
		-0.011193700785458628;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL593";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.020021267836214246 11 -0.020021267836214246 
		25 -0.020021267836214246 40 -0.020021267836214246 50 -0.020021267836214246 85 -0.020021267836214246 
		95 -0.020021267836214246 120 -0.020021267836214246 135 -0.020021267836214246 150 
		-0.020021267836214246;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL594";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.032441787830836878 11 0.032441787830836878 
		25 0.032441787830836878 40 0.032441787830836878 50 0.032441787830836878 85 0.032441787830836878 
		95 0.032441787830836878 120 0.032441787830836878 135 0.032441787830836878 150 0.032441787830836878;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1903";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1904";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1905";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL595";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL596";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL597";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1906";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -15.609971163878811 11 -19.182130850386674 
		25 -19.182130850386674 40 -19.182130850386674 50 -20.016961352650501 85 -20.016961352650501 
		95 -17.825738082878946 120 -17.825738082878946 135 -15.609971163878811 150 -15.609971163878811;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1907";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 8.3116042646716988 11 1.5259731238638783 
		25 1.5259731238638783 40 1.5259731238638783 50 1.4721432693381058 85 1.4721432693381058 
		95 0.75331618821593305 120 0.75331618821593305 135 8.3116042646716988 150 8.3116042646716988;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1908";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 14.458598883932659 11 7.7100426356068805 
		25 7.7100426356068805 40 7.7100426356068805 50 8.0133674877306209 85 8.0133674877306209 
		95 9.527373446446548 120 9.527373446446548 135 14.458598883932659 150 14.458598883932659;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL598";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.18868131369562219 11 -0.17971983233386463 
		25 -0.16694391812958614 40 -0.16544362721936337 50 -0.18251365169812056 85 -0.18380141239564179 
		95 -0.16803597961961914 120 -0.17939940391643905 135 -0.18868131369562219 150 -0.18868131369562219;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL599";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.23059098815955009 11 0.23506826665402511 
		25 0.20575804207826348 40 0.20231610749360726 50 0.19844359677706563 85 0.20362727730590885 
		95 0.20118947453533434 120 0.19921110887830054 135 0.23059098815955009 150 0.23059098815955009;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL600";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.049918713102953649 11 0.0032248044831217348 
		25 0.026618578355018185 40 0.029365737154230312 50 0.00050275110711454907 85 0.022739902040235058 
		95 0.022764156320009027 120 0.0071652901706062699 135 0.049918713102953649 150 0.049918713102953649;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU590";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU591";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.084155571970393403;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL601";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.067207227343123899;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL602";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.20472824713235571;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL603";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.20941646546924442;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU592";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU593";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.084155864375844894;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL604";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL605";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.40088449385078673;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL606";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.69609418843799409;
	setAttr ".kit[2]"  4;
	setAttr ".kot[2]"  4;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1909";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1910";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1911";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1912";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1913";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1914";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1915";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1916";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1917";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1918";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -18.592620239620459 11 -18.592620239620459 
		25 -18.592620239620459 40 -18.592620239620459 50 -18.592620239620459 85 -18.592620239620459 
		95 -18.592620239620459 120 -18.592620239620459 135 -18.592620239620459 150 -18.592620239620459;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
createNode animCurveTA -n "animCurveTA1919";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -4.0495369920864128 11 -4.0495369920864128 
		25 -4.0495369920864128 40 -4.0495369920864128 50 -4.0495369920864128 85 -4.0495369920864128 
		95 -4.0495369920864128 120 -4.0495369920864128 135 -4.0495369920864128 150 -4.0495369920864128;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1920";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -24.718935474963271 11 -24.718935474963271 
		25 -24.718935474963271 40 -24.718935474963271 50 -24.718935474963271 85 -24.718935474963271 
		95 -24.718935474963271 120 -24.718935474963271 135 -24.718935474963271 150 -24.718935474963271;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1921";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1922";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1923";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU594";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 11 1 25 1 40 1 50 1 85 1 95 1 120 1 
		135 1 150 1;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU595";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 11 1 25 1 40 1 50 1 85 1 95 1 120 1 
		135 1 150 1;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU596";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 11 1 25 1 40 1 50 1 85 1 95 1 120 1 
		135 1 150 1;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1924";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1925";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1926";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL607";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL608";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL609";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU597";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 11 1 25 1 40 1 50 1 85 1 95 1 120 1 
		135 1 150 1;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU598";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 11 1 25 1 40 1 50 1 85 1 95 1 120 1 
		135 1 150 1;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU599";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 11 1 25 1 40 1 50 1 85 1 95 1 120 1 
		135 1 150 1;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1927";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1928";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1929";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL610";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL611";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL612";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1930";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1931";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1932";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 7.2644697342894906 11 7.2644697342894906 
		25 7.2644697342894906 40 7.2644697342894906 50 7.2644697342894906 85 7.2644697342894906 
		95 7.2644697342894906 120 7.2644697342894906 135 7.2644697342894906 150 7.2644697342894906;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL613";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL614";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL615";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL616";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.000119480405310887 11 -0.000119480405310887 
		25 -0.000119480405310887 40 -0.000119480405310887 50 -0.000119480405310887 85 -0.000119480405310887 
		95 -0.000119480405310887 120 -0.000119480405310887 135 -0.000119480405310887 150 
		-0.000119480405310887;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL617";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.1152566135867675 11 0.1152566135867675 
		25 0.1152566135867675 40 0.1152566135867675 50 0.1152566135867675 85 0.1152566135867675 
		95 0.1152566135867675 120 0.1152566135867675 135 0.1152566135867675 150 0.1152566135867675;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL618";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.19515846066137013 11 0.19515846066137013 
		25 0.19515846066137013 40 0.19515846066137013 50 0.19515846066137013 85 0.19515846066137013 
		95 0.19515846066137013 120 0.19515846066137013 135 0.19515846066137013 150 0.19515846066137013;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU600";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 11 1 25 1 40 1 50 1 85 1 95 1 120 1 
		135 1 150 1;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
createNode animCurveTU -n "animCurveTU601";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 11 1 25 1 40 1 50 1 85 1 95 1 120 1 
		135 1 150 1;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
createNode animCurveTU -n "animCurveTU602";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 11 1 25 1 40 1 50 1 85 1 95 1 120 1 
		135 1 150 1;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
createNode animCurveTU -n "animCurveTU603";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 11 1 40 1 50 1 85 1 95 1 120 1 130 
		1 135 1 150 1;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 10 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 10 
		9 3;
createNode animCurveTU -n "animCurveTU604";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 11 1 40 1 50 1 85 1 95 1 120 1 130 
		1 135 1 150 1;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 10 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 10 
		9 3;
createNode animCurveTU -n "animCurveTU605";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 11 1 40 1 50 1 85 1 95 1 120 1 130 
		1 135 1 150 1;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 10 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 10 
		9 3;
createNode animCurveTA -n "Ratcatcher_CTRL_TwistR_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
createNode animCurveTA -n "Ratcatcher_CTRL_TwistL_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 11 0 25 0 40 0 50 0 85 0 95 0 120 0 
		135 0 150 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
createNode animCurveTU -n "Ratcatcher_CTRL_JAR_scaleZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 11 1 25 1 40 1 50 1 85 1 95 1 120 1 
		135 1 150 1;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
createNode animCurveTU -n "Ratcatcher_CTRL_JAR_scaleY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 11 1 25 1 40 1 50 1 85 1 95 1 120 1 
		135 1 150 1;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
createNode animCurveTU -n "Ratcatcher_CTRL_JAR_scaleX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 11 1 25 1 40 1 50 1 85 1 95 1 120 1 
		135 1 150 1;
	setAttr -s 10 ".kit[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
	setAttr -s 10 ".kot[0:9]"  3 9 9 9 9 9 9 9 
		9 3;
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
connectAttr "idle03Source.cl" "clipLibrary1.sc[0]";
connectAttr "animCurveTU546.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "animCurveTA1740.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "animCurveTA1741.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "animCurveTA1742.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "animCurveTU547.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "animCurveTU548.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "animCurveTU549.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "animCurveTU550.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "animCurveTA1743.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "animCurveTA1744.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "animCurveTA1745.a" "clipLibrary1.cel[0].cev[10].cevr";
connectAttr "animCurveTU551.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "animCurveTU552.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "animCurveTL556.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "animCurveTL557.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "animCurveTL558.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "animCurveTA1746.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "animCurveTA1747.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "animCurveTA1748.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "animCurveTA1749.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "animCurveTA1750.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "Ratcatcher_Ratcatcher_rt_arm_ik_ctrl_maxStretch.a" "clipLibrary1.cel[0].cev[21].cevr"
		;
connectAttr "Ratcatcher_Ratcatcher_rt_arm_ik_ctrl_stretchyArm.a" "clipLibrary1.cel[0].cev[22].cevr"
		;
connectAttr "Ratcatcher_Ratcatcher_rt_arm_ik_ctrl_pvControl.a" "clipLibrary1.cel[0].cev[23].cevr"
		;
connectAttr "Ratcatcher_Ratcatcher_rt_arm_ik_ctrl_armTwist.a" "clipLibrary1.cel[0].cev[24].cevr"
		;
connectAttr "animCurveTA1751.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "animCurveTA1752.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "animCurveTA1753.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "animCurveTL559.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "animCurveTL560.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "animCurveTL561.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "animCurveTU553.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "animCurveTA1754.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "animCurveTA1755.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "animCurveTA1756.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "animCurveTU554.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "animCurveTU555.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "animCurveTU556.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "animCurveTU557.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "animCurveTA1757.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "animCurveTA1758.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "animCurveTA1759.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "animCurveTU558.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "animCurveTU559.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "animCurveTL562.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "animCurveTL563.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "animCurveTL564.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "animCurveTA1760.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "Ratcatcher_Ratcatcher_lf_elbow_fk_ctrl_rotateY.a" "clipLibrary1.cel[0].cev[48].cevr"
		;
connectAttr "Ratcatcher_Ratcatcher_lf_elbow_fk_ctrl_rotateX.a" "clipLibrary1.cel[0].cev[49].cevr"
		;
connectAttr "animCurveTA1763.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "animCurveTA1764.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "animCurveTU560.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "animCurveTU561.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "animCurveTU562.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "animCurveTU563.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "animCurveTU564.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "animCurveTA1765.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "animCurveTA1766.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "animCurveTA1767.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "animCurveTL565.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "animCurveTL566.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "animCurveTL567.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "animCurveTU565.a" "clipLibrary1.cel[0].cev[63].cevr";
connectAttr "animCurveTA1768.a" "clipLibrary1.cel[0].cev[64].cevr";
connectAttr "animCurveTA1769.a" "clipLibrary1.cel[0].cev[65].cevr";
connectAttr "animCurveTA1770.a" "clipLibrary1.cel[0].cev[66].cevr";
connectAttr "animCurveTU566.a" "clipLibrary1.cel[0].cev[67].cevr";
connectAttr "animCurveTA1771.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "animCurveTA1772.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "animCurveTA1773.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "animCurveTA1774.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "animCurveTA1775.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "animCurveTA1776.a" "clipLibrary1.cel[0].cev[73].cevr";
connectAttr "animCurveTU567.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "animCurveTA1777.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "animCurveTA1778.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "animCurveTA1779.a" "clipLibrary1.cel[0].cev[77].cevr";
connectAttr "animCurveTA1780.a" "clipLibrary1.cel[0].cev[78].cevr";
connectAttr "animCurveTA1781.a" "clipLibrary1.cel[0].cev[79].cevr";
connectAttr "animCurveTA1782.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "animCurveTU568.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "animCurveTA1783.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "animCurveTA1784.a" "clipLibrary1.cel[0].cev[83].cevr";
connectAttr "animCurveTA1785.a" "clipLibrary1.cel[0].cev[84].cevr";
connectAttr "animCurveTA1786.a" "clipLibrary1.cel[0].cev[85].cevr";
connectAttr "animCurveTA1787.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "animCurveTA1788.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "animCurveTU569.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "animCurveTA1789.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr "animCurveTA1790.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "animCurveTA1791.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "animCurveTA1792.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "animCurveTA1793.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "animCurveTA1794.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "animCurveTU570.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "animCurveTA1795.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "animCurveTA1796.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "animCurveTA1797.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "animCurveTA1798.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "animCurveTA1799.a" "clipLibrary1.cel[0].cev[100].cevr";
connectAttr "animCurveTA1800.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "animCurveTA1801.a" "clipLibrary1.cel[0].cev[102].cevr";
connectAttr "animCurveTA1802.a" "clipLibrary1.cel[0].cev[103].cevr";
connectAttr "animCurveTA1803.a" "clipLibrary1.cel[0].cev[104].cevr";
connectAttr "animCurveTU571.a" "clipLibrary1.cel[0].cev[105].cevr";
connectAttr "animCurveTA1804.a" "clipLibrary1.cel[0].cev[106].cevr";
connectAttr "animCurveTA1805.a" "clipLibrary1.cel[0].cev[107].cevr";
connectAttr "animCurveTA1806.a" "clipLibrary1.cel[0].cev[108].cevr";
connectAttr "animCurveTA1807.a" "clipLibrary1.cel[0].cev[109].cevr";
connectAttr "animCurveTA1808.a" "clipLibrary1.cel[0].cev[110].cevr";
connectAttr "animCurveTA1809.a" "clipLibrary1.cel[0].cev[111].cevr";
connectAttr "animCurveTU572.a" "clipLibrary1.cel[0].cev[112].cevr";
connectAttr "animCurveTA1810.a" "clipLibrary1.cel[0].cev[113].cevr";
connectAttr "animCurveTA1811.a" "clipLibrary1.cel[0].cev[114].cevr";
connectAttr "animCurveTA1812.a" "clipLibrary1.cel[0].cev[115].cevr";
connectAttr "animCurveTA1813.a" "clipLibrary1.cel[0].cev[116].cevr";
connectAttr "animCurveTA1814.a" "clipLibrary1.cel[0].cev[117].cevr";
connectAttr "animCurveTA1815.a" "clipLibrary1.cel[0].cev[118].cevr";
connectAttr "animCurveTU573.a" "clipLibrary1.cel[0].cev[119].cevr";
connectAttr "animCurveTA1816.a" "clipLibrary1.cel[0].cev[120].cevr";
connectAttr "animCurveTA1817.a" "clipLibrary1.cel[0].cev[121].cevr";
connectAttr "animCurveTA1818.a" "clipLibrary1.cel[0].cev[122].cevr";
connectAttr "animCurveTA1819.a" "clipLibrary1.cel[0].cev[123].cevr";
connectAttr "animCurveTA1820.a" "clipLibrary1.cel[0].cev[124].cevr";
connectAttr "animCurveTA1821.a" "clipLibrary1.cel[0].cev[125].cevr";
connectAttr "animCurveTU574.a" "clipLibrary1.cel[0].cev[126].cevr";
connectAttr "animCurveTA1822.a" "clipLibrary1.cel[0].cev[127].cevr";
connectAttr "animCurveTA1823.a" "clipLibrary1.cel[0].cev[128].cevr";
connectAttr "animCurveTA1824.a" "clipLibrary1.cel[0].cev[129].cevr";
connectAttr "animCurveTA1825.a" "clipLibrary1.cel[0].cev[130].cevr";
connectAttr "animCurveTA1826.a" "clipLibrary1.cel[0].cev[131].cevr";
connectAttr "animCurveTA1827.a" "clipLibrary1.cel[0].cev[132].cevr";
connectAttr "animCurveTU575.a" "clipLibrary1.cel[0].cev[133].cevr";
connectAttr "animCurveTA1828.a" "clipLibrary1.cel[0].cev[134].cevr";
connectAttr "animCurveTA1829.a" "clipLibrary1.cel[0].cev[135].cevr";
connectAttr "animCurveTA1830.a" "clipLibrary1.cel[0].cev[136].cevr";
connectAttr "animCurveTA1831.a" "clipLibrary1.cel[0].cev[137].cevr";
connectAttr "animCurveTA1832.a" "clipLibrary1.cel[0].cev[138].cevr";
connectAttr "animCurveTA1833.a" "clipLibrary1.cel[0].cev[139].cevr";
connectAttr "animCurveTA1834.a" "clipLibrary1.cel[0].cev[140].cevr";
connectAttr "animCurveTA1835.a" "clipLibrary1.cel[0].cev[141].cevr";
connectAttr "animCurveTA1836.a" "clipLibrary1.cel[0].cev[142].cevr";
connectAttr "animCurveTU576.a" "clipLibrary1.cel[0].cev[143].cevr";
connectAttr "animCurveTU577.a" "clipLibrary1.cel[0].cev[144].cevr";
connectAttr "animCurveTU578.a" "clipLibrary1.cel[0].cev[145].cevr";
connectAttr "animCurveTA1837.a" "clipLibrary1.cel[0].cev[146].cevr";
connectAttr "animCurveTA1838.a" "clipLibrary1.cel[0].cev[147].cevr";
connectAttr "animCurveTA1839.a" "clipLibrary1.cel[0].cev[148].cevr";
connectAttr "animCurveTL568.a" "clipLibrary1.cel[0].cev[149].cevr";
connectAttr "animCurveTL569.a" "clipLibrary1.cel[0].cev[150].cevr";
connectAttr "animCurveTL570.a" "clipLibrary1.cel[0].cev[151].cevr";
connectAttr "animCurveTA1840.a" "clipLibrary1.cel[0].cev[152].cevr";
connectAttr "animCurveTA1841.a" "clipLibrary1.cel[0].cev[153].cevr";
connectAttr "animCurveTA1842.a" "clipLibrary1.cel[0].cev[154].cevr";
connectAttr "animCurveTU579.a" "clipLibrary1.cel[0].cev[155].cevr";
connectAttr "animCurveTA1843.a" "clipLibrary1.cel[0].cev[156].cevr";
connectAttr "animCurveTA1844.a" "clipLibrary1.cel[0].cev[157].cevr";
connectAttr "animCurveTA1845.a" "clipLibrary1.cel[0].cev[158].cevr";
connectAttr "animCurveTA1846.a" "clipLibrary1.cel[0].cev[159].cevr";
connectAttr "animCurveTA1847.a" "clipLibrary1.cel[0].cev[160].cevr";
connectAttr "animCurveTA1848.a" "clipLibrary1.cel[0].cev[161].cevr";
connectAttr "animCurveTA1849.a" "clipLibrary1.cel[0].cev[162].cevr";
connectAttr "animCurveTA1850.a" "clipLibrary1.cel[0].cev[163].cevr";
connectAttr "animCurveTA1851.a" "clipLibrary1.cel[0].cev[164].cevr";
connectAttr "animCurveTU580.a" "clipLibrary1.cel[0].cev[165].cevr";
connectAttr "animCurveTA1852.a" "clipLibrary1.cel[0].cev[166].cevr";
connectAttr "animCurveTA1853.a" "clipLibrary1.cel[0].cev[167].cevr";
connectAttr "animCurveTA1854.a" "clipLibrary1.cel[0].cev[168].cevr";
connectAttr "animCurveTU581.a" "clipLibrary1.cel[0].cev[169].cevr";
connectAttr "animCurveTU582.a" "clipLibrary1.cel[0].cev[170].cevr";
connectAttr "animCurveTU583.a" "clipLibrary1.cel[0].cev[171].cevr";
connectAttr "animCurveTA1855.a" "clipLibrary1.cel[0].cev[172].cevr";
connectAttr "animCurveTA1856.a" "clipLibrary1.cel[0].cev[173].cevr";
connectAttr "animCurveTA1857.a" "clipLibrary1.cel[0].cev[174].cevr";
connectAttr "animCurveTL571.a" "clipLibrary1.cel[0].cev[175].cevr";
connectAttr "animCurveTL572.a" "clipLibrary1.cel[0].cev[176].cevr";
connectAttr "animCurveTL573.a" "clipLibrary1.cel[0].cev[177].cevr";
connectAttr "animCurveTA1858.a" "clipLibrary1.cel[0].cev[178].cevr";
connectAttr "animCurveTA1859.a" "clipLibrary1.cel[0].cev[179].cevr";
connectAttr "animCurveTA1860.a" "clipLibrary1.cel[0].cev[180].cevr";
connectAttr "animCurveTU584.a" "clipLibrary1.cel[0].cev[181].cevr";
connectAttr "animCurveTA1861.a" "clipLibrary1.cel[0].cev[182].cevr";
connectAttr "animCurveTA1862.a" "clipLibrary1.cel[0].cev[183].cevr";
connectAttr "animCurveTA1863.a" "clipLibrary1.cel[0].cev[184].cevr";
connectAttr "animCurveTA1864.a" "clipLibrary1.cel[0].cev[185].cevr";
connectAttr "animCurveTA1865.a" "clipLibrary1.cel[0].cev[186].cevr";
connectAttr "animCurveTA1866.a" "clipLibrary1.cel[0].cev[187].cevr";
connectAttr "animCurveTA1867.a" "clipLibrary1.cel[0].cev[188].cevr";
connectAttr "animCurveTA1868.a" "clipLibrary1.cel[0].cev[189].cevr";
connectAttr "animCurveTA1869.a" "clipLibrary1.cel[0].cev[190].cevr";
connectAttr "animCurveTA1870.a" "clipLibrary1.cel[0].cev[191].cevr";
connectAttr "animCurveTA1871.a" "clipLibrary1.cel[0].cev[192].cevr";
connectAttr "animCurveTA1872.a" "clipLibrary1.cel[0].cev[193].cevr";
connectAttr "animCurveTA1873.a" "clipLibrary1.cel[0].cev[194].cevr";
connectAttr "animCurveTA1874.a" "clipLibrary1.cel[0].cev[195].cevr";
connectAttr "animCurveTA1875.a" "clipLibrary1.cel[0].cev[196].cevr";
connectAttr "animCurveTU585.a" "clipLibrary1.cel[0].cev[197].cevr";
connectAttr "animCurveTA1876.a" "clipLibrary1.cel[0].cev[198].cevr";
connectAttr "animCurveTA1877.a" "clipLibrary1.cel[0].cev[199].cevr";
connectAttr "animCurveTA1878.a" "clipLibrary1.cel[0].cev[200].cevr";
connectAttr "animCurveTU586.a" "clipLibrary1.cel[0].cev[201].cevr";
connectAttr "animCurveTA1879.a" "clipLibrary1.cel[0].cev[202].cevr";
connectAttr "animCurveTA1880.a" "clipLibrary1.cel[0].cev[203].cevr";
connectAttr "animCurveTA1881.a" "clipLibrary1.cel[0].cev[204].cevr";
connectAttr "animCurveTA1882.a" "clipLibrary1.cel[0].cev[205].cevr";
connectAttr "animCurveTA1883.a" "clipLibrary1.cel[0].cev[206].cevr";
connectAttr "animCurveTA1884.a" "clipLibrary1.cel[0].cev[207].cevr";
connectAttr "animCurveTA1885.a" "clipLibrary1.cel[0].cev[208].cevr";
connectAttr "animCurveTA1886.a" "clipLibrary1.cel[0].cev[209].cevr";
connectAttr "animCurveTA1887.a" "clipLibrary1.cel[0].cev[210].cevr";
connectAttr "animCurveTL574.a" "clipLibrary1.cel[0].cev[211].cevr";
connectAttr "animCurveTL575.a" "clipLibrary1.cel[0].cev[212].cevr";
connectAttr "animCurveTL576.a" "clipLibrary1.cel[0].cev[213].cevr";
connectAttr "animCurveTU587.a" "clipLibrary1.cel[0].cev[214].cevr";
connectAttr "animCurveTU588.a" "clipLibrary1.cel[0].cev[215].cevr";
connectAttr "animCurveTA1888.a" "clipLibrary1.cel[0].cev[216].cevr";
connectAttr "animCurveTA1889.a" "clipLibrary1.cel[0].cev[217].cevr";
connectAttr "animCurveTA1890.a" "clipLibrary1.cel[0].cev[218].cevr";
connectAttr "animCurveTL577.a" "clipLibrary1.cel[0].cev[219].cevr";
connectAttr "animCurveTL578.a" "clipLibrary1.cel[0].cev[220].cevr";
connectAttr "animCurveTL579.a" "clipLibrary1.cel[0].cev[221].cevr";
connectAttr "animCurveTL580.a" "clipLibrary1.cel[0].cev[222].cevr";
connectAttr "animCurveTL581.a" "clipLibrary1.cel[0].cev[223].cevr";
connectAttr "animCurveTL582.a" "clipLibrary1.cel[0].cev[224].cevr";
connectAttr "animCurveTA1891.a" "clipLibrary1.cel[0].cev[225].cevr";
connectAttr "animCurveTA1892.a" "clipLibrary1.cel[0].cev[226].cevr";
connectAttr "animCurveTA1893.a" "clipLibrary1.cel[0].cev[227].cevr";
connectAttr "animCurveTL583.a" "clipLibrary1.cel[0].cev[228].cevr";
connectAttr "animCurveTL584.a" "clipLibrary1.cel[0].cev[229].cevr";
connectAttr "animCurveTL585.a" "clipLibrary1.cel[0].cev[230].cevr";
connectAttr "animCurveTA1894.a" "clipLibrary1.cel[0].cev[231].cevr";
connectAttr "animCurveTA1895.a" "clipLibrary1.cel[0].cev[232].cevr";
connectAttr "animCurveTA1896.a" "clipLibrary1.cel[0].cev[233].cevr";
connectAttr "animCurveTL586.a" "clipLibrary1.cel[0].cev[234].cevr";
connectAttr "animCurveTL587.a" "clipLibrary1.cel[0].cev[235].cevr";
connectAttr "animCurveTL588.a" "clipLibrary1.cel[0].cev[236].cevr";
connectAttr "animCurveTU589.a" "clipLibrary1.cel[0].cev[237].cevr";
connectAttr "animCurveTA1897.a" "clipLibrary1.cel[0].cev[238].cevr";
connectAttr "animCurveTA1898.a" "clipLibrary1.cel[0].cev[239].cevr";
connectAttr "animCurveTA1899.a" "clipLibrary1.cel[0].cev[240].cevr";
connectAttr "animCurveTL589.a" "clipLibrary1.cel[0].cev[241].cevr";
connectAttr "animCurveTL590.a" "clipLibrary1.cel[0].cev[242].cevr";
connectAttr "animCurveTL591.a" "clipLibrary1.cel[0].cev[243].cevr";
connectAttr "animCurveTA1900.a" "clipLibrary1.cel[0].cev[244].cevr";
connectAttr "animCurveTA1901.a" "clipLibrary1.cel[0].cev[245].cevr";
connectAttr "animCurveTA1902.a" "clipLibrary1.cel[0].cev[246].cevr";
connectAttr "animCurveTL592.a" "clipLibrary1.cel[0].cev[247].cevr";
connectAttr "animCurveTL593.a" "clipLibrary1.cel[0].cev[248].cevr";
connectAttr "animCurveTL594.a" "clipLibrary1.cel[0].cev[249].cevr";
connectAttr "animCurveTA1903.a" "clipLibrary1.cel[0].cev[250].cevr";
connectAttr "animCurveTA1904.a" "clipLibrary1.cel[0].cev[251].cevr";
connectAttr "animCurveTA1905.a" "clipLibrary1.cel[0].cev[252].cevr";
connectAttr "animCurveTL595.a" "clipLibrary1.cel[0].cev[253].cevr";
connectAttr "animCurveTL596.a" "clipLibrary1.cel[0].cev[254].cevr";
connectAttr "animCurveTL597.a" "clipLibrary1.cel[0].cev[255].cevr";
connectAttr "animCurveTA1906.a" "clipLibrary1.cel[0].cev[256].cevr";
connectAttr "animCurveTA1907.a" "clipLibrary1.cel[0].cev[257].cevr";
connectAttr "animCurveTA1908.a" "clipLibrary1.cel[0].cev[258].cevr";
connectAttr "animCurveTL598.a" "clipLibrary1.cel[0].cev[259].cevr";
connectAttr "animCurveTL599.a" "clipLibrary1.cel[0].cev[260].cevr";
connectAttr "animCurveTL600.a" "clipLibrary1.cel[0].cev[261].cevr";
connectAttr "animCurveTU590.a" "clipLibrary1.cel[0].cev[262].cevr";
connectAttr "animCurveTU591.a" "clipLibrary1.cel[0].cev[263].cevr";
connectAttr "animCurveTL601.a" "clipLibrary1.cel[0].cev[264].cevr";
connectAttr "animCurveTL602.a" "clipLibrary1.cel[0].cev[265].cevr";
connectAttr "animCurveTL603.a" "clipLibrary1.cel[0].cev[266].cevr";
connectAttr "animCurveTU592.a" "clipLibrary1.cel[0].cev[267].cevr";
connectAttr "animCurveTU593.a" "clipLibrary1.cel[0].cev[268].cevr";
connectAttr "animCurveTL604.a" "clipLibrary1.cel[0].cev[269].cevr";
connectAttr "animCurveTL605.a" "clipLibrary1.cel[0].cev[270].cevr";
connectAttr "animCurveTL606.a" "clipLibrary1.cel[0].cev[271].cevr";
connectAttr "animCurveTA1909.a" "clipLibrary1.cel[0].cev[272].cevr";
connectAttr "animCurveTA1910.a" "clipLibrary1.cel[0].cev[273].cevr";
connectAttr "animCurveTA1911.a" "clipLibrary1.cel[0].cev[274].cevr";
connectAttr "animCurveTA1912.a" "clipLibrary1.cel[0].cev[275].cevr";
connectAttr "animCurveTA1913.a" "clipLibrary1.cel[0].cev[276].cevr";
connectAttr "animCurveTA1914.a" "clipLibrary1.cel[0].cev[277].cevr";
connectAttr "animCurveTA1915.a" "clipLibrary1.cel[0].cev[278].cevr";
connectAttr "animCurveTA1916.a" "clipLibrary1.cel[0].cev[279].cevr";
connectAttr "animCurveTA1917.a" "clipLibrary1.cel[0].cev[280].cevr";
connectAttr "animCurveTA1918.a" "clipLibrary1.cel[0].cev[281].cevr";
connectAttr "animCurveTA1919.a" "clipLibrary1.cel[0].cev[282].cevr";
connectAttr "animCurveTA1920.a" "clipLibrary1.cel[0].cev[283].cevr";
connectAttr "animCurveTA1921.a" "clipLibrary1.cel[0].cev[284].cevr";
connectAttr "animCurveTA1922.a" "clipLibrary1.cel[0].cev[285].cevr";
connectAttr "animCurveTA1923.a" "clipLibrary1.cel[0].cev[286].cevr";
connectAttr "animCurveTU594.a" "clipLibrary1.cel[0].cev[287].cevr";
connectAttr "animCurveTU595.a" "clipLibrary1.cel[0].cev[288].cevr";
connectAttr "animCurveTU596.a" "clipLibrary1.cel[0].cev[289].cevr";
connectAttr "animCurveTA1924.a" "clipLibrary1.cel[0].cev[290].cevr";
connectAttr "animCurveTA1925.a" "clipLibrary1.cel[0].cev[291].cevr";
connectAttr "animCurveTA1926.a" "clipLibrary1.cel[0].cev[292].cevr";
connectAttr "animCurveTL607.a" "clipLibrary1.cel[0].cev[293].cevr";
connectAttr "animCurveTL608.a" "clipLibrary1.cel[0].cev[294].cevr";
connectAttr "animCurveTL609.a" "clipLibrary1.cel[0].cev[295].cevr";
connectAttr "animCurveTU597.a" "clipLibrary1.cel[0].cev[296].cevr";
connectAttr "animCurveTU598.a" "clipLibrary1.cel[0].cev[297].cevr";
connectAttr "animCurveTU599.a" "clipLibrary1.cel[0].cev[298].cevr";
connectAttr "animCurveTA1927.a" "clipLibrary1.cel[0].cev[299].cevr";
connectAttr "animCurveTA1928.a" "clipLibrary1.cel[0].cev[300].cevr";
connectAttr "animCurveTA1929.a" "clipLibrary1.cel[0].cev[301].cevr";
connectAttr "animCurveTL610.a" "clipLibrary1.cel[0].cev[302].cevr";
connectAttr "animCurveTL611.a" "clipLibrary1.cel[0].cev[303].cevr";
connectAttr "animCurveTL612.a" "clipLibrary1.cel[0].cev[304].cevr";
connectAttr "animCurveTA1930.a" "clipLibrary1.cel[0].cev[305].cevr";
connectAttr "animCurveTA1931.a" "clipLibrary1.cel[0].cev[306].cevr";
connectAttr "animCurveTA1932.a" "clipLibrary1.cel[0].cev[307].cevr";
connectAttr "animCurveTL613.a" "clipLibrary1.cel[0].cev[308].cevr";
connectAttr "animCurveTL614.a" "clipLibrary1.cel[0].cev[309].cevr";
connectAttr "animCurveTL615.a" "clipLibrary1.cel[0].cev[310].cevr";
connectAttr "animCurveTL616.a" "clipLibrary1.cel[0].cev[311].cevr";
connectAttr "animCurveTL617.a" "clipLibrary1.cel[0].cev[312].cevr";
connectAttr "animCurveTL618.a" "clipLibrary1.cel[0].cev[313].cevr";
connectAttr "animCurveTU600.a" "clipLibrary1.cel[0].cev[314].cevr";
connectAttr "animCurveTU601.a" "clipLibrary1.cel[0].cev[315].cevr";
connectAttr "animCurveTU602.a" "clipLibrary1.cel[0].cev[316].cevr";
connectAttr "animCurveTU603.a" "clipLibrary1.cel[0].cev[317].cevr";
connectAttr "animCurveTU604.a" "clipLibrary1.cel[0].cev[318].cevr";
connectAttr "animCurveTU605.a" "clipLibrary1.cel[0].cev[319].cevr";
connectAttr "Ratcatcher_CTRL_TwistR_rotateX.a" "clipLibrary1.cel[0].cev[320].cevr"
		;
connectAttr "Ratcatcher_CTRL_TwistL_rotateX.a" "clipLibrary1.cel[0].cev[321].cevr"
		;
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
// End of idle3A.ma
