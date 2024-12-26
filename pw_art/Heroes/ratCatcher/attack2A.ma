//Maya ASCII 2008 scene
//Name: attack2A.ma
//Last modified: Mon, Nov 23, 2009 12:41:28 PM
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
createNode animClip -n "attack2ASource1";
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
	setAttr ".se" 44;
	setAttr ".ci" no;
createNode animCurveTU -n "animCurveTU419";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1352";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1353";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1354";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU420";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 6 0 9 0 14 0 36 0;
	setAttr -s 6 ".kit[1:5]"  9 9 3 3 9;
	setAttr -s 6 ".kot[1:5]"  5 5 3 5 9;
createNode animCurveTU -n "animCurveTU421";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 6 0 9 0 14 0 36 0;
	setAttr -s 6 ".kit[1:5]"  9 9 3 3 9;
	setAttr -s 6 ".kot[1:5]"  5 5 3 5 9;
createNode animCurveTU -n "animCurveTU422";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 2 1 6 1 9 1 14 1 36 1;
	setAttr -s 6 ".kit[1:5]"  10 10 3 3 9;
	setAttr -s 6 ".kot[1:5]"  10 10 3 3 9;
createNode animCurveTU -n "animCurveTU423";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 6 0 9 0 14 0 36 0;
	setAttr -s 6 ".kit[1:5]"  9 9 3 3 9;
	setAttr -s 6 ".kot[1:5]"  5 5 3 5 9;
createNode animCurveTA -n "animCurveTA1355";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 6 0 9 0 14 0 36 0;
	setAttr -s 6 ".kit[1:5]"  10 10 3 3 9;
	setAttr -s 6 ".kot[1:5]"  10 10 3 5 9;
createNode animCurveTA -n "animCurveTA1356";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 6 0 9 0 14 0 36 0;
	setAttr -s 6 ".kit[1:5]"  10 10 3 3 9;
	setAttr -s 6 ".kot[1:5]"  10 10 3 5 9;
createNode animCurveTA -n "animCurveTA1357";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 6 0 9 0 14 0 36 0;
	setAttr -s 6 ".kit[1:5]"  10 10 3 3 9;
	setAttr -s 6 ".kot[1:5]"  10 10 3 5 9;
createNode animCurveTU -n "animCurveTU424";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 9 9 9 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU425";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 2 0 4 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 9 9 9 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL430";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.40930268174563 2 -0.61872902160428578 
		4 -0.59318574508316357 6 -0.4340453134852893 9 -0.4340453134852893 14 -0.4340453134852893 
		17 0.16232947549134824 36 0.40930268174563 44 0.40930268174563;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 9 9 10 9 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 9 9 10 9 
		10;
createNode animCurveTL -n "animCurveTL431";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.25860394298924627 2 0.44819252667981968 
		4 0.51255864367351855 6 -0.56084248139615656 9 -0.56084248139615656 14 -0.56084248139615656 
		17 -0.4553528609874325 36 0.25860394298924627 44 0.25860394298924627;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 9 9 10 9 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 9 9 10 9 
		10;
createNode animCurveTL -n "animCurveTL432";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.29847095663485657 2 1.2337793973512658 
		4 0.57197187615689704 6 0.035889982012940247 9 0.035889982012940247 14 0.035889982012940247 
		17 -0.40963347230608582 36 -0.29847095663485657 44 -0.29847095663485657;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 9 9 10 9 
		10;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 9 9 10 9 
		10;
createNode animCurveTA -n "animCurveTA1358";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1359";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1360";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1361";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 25.675870473757751 2 25.675870473757751 
		6 25.675870473757751 9 25.675870473757751 14 25.675870473757751 36 25.675870473757751 
		44 25.675870473757751;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1362";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -3.0739741698828946 2 -3.0739741698828946 
		6 -3.0739741698828946 9 -3.0739741698828946 14 -3.0739741698828946 36 -3.0739741698828946 
		44 -3.0739741698828946;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU426";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 3 2 3 6 3 9 3 14 3 23 3 26 3 29 3 36 
		3 44 3;
	setAttr -s 10 ".kit[3:9]"  3 3 10 10 10 9 10;
	setAttr -s 10 ".kot[3:9]"  3 3 10 10 10 9 10;
createNode animCurveTU -n "animCurveTU427";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 9 0 14 0 23 0 26 0 29 0 36 
		0 44 0;
	setAttr -s 10 ".kit[3:9]"  3 3 10 10 10 9 10;
	setAttr -s 10 ".kot[3:9]"  3 3 10 10 10 9 10;
createNode animCurveTU -n "animCurveTU428";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 2 1 6 1 9 1 14 1 23 1 26 1 29 1 36 
		1 44 1;
	setAttr -s 10 ".kit[3:9]"  3 3 9 9 9 9 9;
	setAttr -s 10 ".kot[0:9]"  5 5 5 3 3 5 5 5 
		9 5;
createNode animCurveTU -n "animCurveTU429";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 2 0 6 0 9 0 14 0 23 0 26 0 29 0 36 
		0 44 0;
	setAttr -s 10 ".kit[3:9]"  3 3 10 10 10 9 10;
	setAttr -s 10 ".kot[3:9]"  3 3 10 10 10 9 10;
createNode animCurveTA -n "animCurveTA1363";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 93.144161708979723 2 130.254308417934 
		3 154.61782522289406 4 189.21930605241297 5 240.12036052024993 6 262.17317184714585 
		9 261.68675587585147 14 261.68675587585147 17 311.12095647364248 19 390.56093048922526 
		20 437.77812843702839 21 289.99793824239521 22 282.88993453563171 23 283.53008326376892 
		26 217.51319395027633 29 232.81888527018316 31 276.67075822349614 32 226.63454183818081 
		33 347.2513335448906 34 326.3048158782338 36 273.14416170897971 44 273.14416170897971;
	setAttr -s 22 ".kit[6:21]"  3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 9 10;
	setAttr -s 22 ".kot[6:21]"  3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 9 10;
createNode animCurveTA -n "animCurveTA1364";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 95.049826002206416 2 191.91448996089679 
		3 237.77197330278821 4 272.62693582865654 5 334.73263760951562 6 351.78526109252465 
		9 354.54792195564835 14 354.54792195564835 17 447.33649953129469 19 490.26587419104601 
		20 504.67534757005097 21 356.17595026436288 22 359.61791885430665 23 382.83150656241543 
		26 497.3451252555584 29 568.35381152974503 31 614.28122980884825 32 572.16488737582949 
		33 704.36489584814706 34 675.49776654004972 36 635.04982600220649 44 635.04982600220649;
	setAttr -s 22 ".kit[6:21]"  3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 9 10;
	setAttr -s 22 ".kot[6:21]"  3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 9 10;
createNode animCurveTA -n "animCurveTA1365";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 1.1812364035166698 2 118.27034717588086 
		3 105.55232006180559 4 109.0158688579496 5 138.69276860264017 6 183.93443748393037 
		9 182.34860926529603 14 182.34860926529603 17 155.6790378644387 19 145.55584070089444 
		20 137.41559627058263 21 36.788501036230983 22 20.501026643325659 23 -9.8468158956939664 
		26 -68.735728680612468 29 18.249739708869669 31 38.25946510666364 32 55.168943393804334 
		33 116.63158073353813 34 122.52677615634995 36 178.81876359648331 44 178.81876359648331;
	setAttr -s 22 ".kit[6:21]"  3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 9 10;
	setAttr -s 22 ".kot[6:21]"  3 3 10 10 10 10 10 10 
		10 10 10 10 10 10 9 10;
createNode animCurveTL -n "animCurveTL433";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 -0.23689498628395578 2 -1.1174337681856488 
		4 -0.33770891664424973 5 0.32922016349055111 6 1.0375988380389067 9 0.95567413449667049 
		14 0.91081220542463315 17 0.50403484449892377 23 0.23488073800004422 26 0.1845589930162353 
		29 -0.050269097295831573 31 -0.54272860709707182 34 -0.51871585034293677 36 -0.23689498628395578 
		44 -0.23689498628395578;
	setAttr -s 15 ".kit[4:14]"  3 3 3 10 10 10 10 10 
		10 9 10;
	setAttr -s 15 ".kot[4:14]"  3 3 3 10 10 10 10 10 
		10 9 10;
createNode animCurveTL -n "animCurveTL434";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 -0.30633990936382105 2 -0.41851569990443238 
		4 0.059317243097923258 5 0.05374078943917962 6 -0.3047042189650741 9 -0.16993816670842782 
		14 -0.17759382920525585 17 0.36021719499698263 23 0.31216875950996975 26 0.23443677338863567 
		29 0.55111925455786004 31 0.56559341627522075 34 0.46032691220164657 36 -0.30633990936382105 
		44 -0.30633990936382105;
	setAttr -s 15 ".kit[4:14]"  3 3 3 10 10 10 10 10 
		10 9 10;
	setAttr -s 15 ".kot[4:14]"  3 3 3 10 10 10 10 10 
		10 9 10;
createNode animCurveTL -n "animCurveTL435";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 0.52899036848843184 2 0.62255779357031382 
		4 0.15248981941443565 5 -0.00053783208613290422 6 -0.091645590705331084 9 -0.26415508815155414 
		14 -0.24495826922882019 17 -0.088391510270258197 23 0.1084804488645366 26 0.25205341229864447 
		29 0.51870375238876099 31 0.70172166312626205 34 0.47504422054060624 36 0.52899036848843184 
		44 0.52899036848843184;
	setAttr -s 15 ".kit[5:14]"  3 3 10 10 10 10 10 10 
		9 10;
	setAttr -s 15 ".kot[5:14]"  3 3 10 10 10 10 10 10 
		9 10;
createNode animCurveTU -n "animCurveTU430";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 6 0 14 0 36 0 44 0;
	setAttr -s 6 ".kot[1:5]"  5 5 9 9 5;
createNode animCurveTA -n "animCurveTA1366";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -24.884454396993167 2 -9.5213101702491603 
		6 41.332039070142933 14 28.33742630144965 26 8.2043287341796738 36 -24.884454396993167 
		44 -24.884454396993167;
	setAttr -s 7 ".kit[0:6]"  9 10 10 9 10 9 10;
	setAttr -s 7 ".kot[0:6]"  9 10 10 9 10 9 10;
createNode animCurveTA -n "animCurveTA1367";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -43.339475474578435 2 -27.039666536079483 
		6 -22.961466294089803 14 -15.439448213270042 26 -35.100005006663913 36 -43.339475474578435 
		44 -43.339475474578435;
	setAttr -s 7 ".kit[0:6]"  9 10 10 9 10 9 10;
	setAttr -s 7 ".kot[0:6]"  9 10 10 9 10 9 10;
createNode animCurveTA -n "animCurveTA1368";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 11.606559612787883 2 2.5335730292680818 
		6 -43.847661039788619 14 -30.83729137133426 26 -21.76001639731815 36 11.606559612787883 
		44 11.606559612787883;
	setAttr -s 7 ".kit[0:6]"  9 10 10 9 10 9 10;
	setAttr -s 7 ".kot[0:6]"  9 10 10 9 10 9 10;
createNode animCurveTU -n "animCurveTU431";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 9;
	setAttr -s 7 ".kot[0:6]"  3 5 5 9 9 9 5;
createNode animCurveTU -n "animCurveTU432";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 9;
	setAttr -s 7 ".kot[0:6]"  3 5 5 9 9 9 5;
createNode animCurveTU -n "animCurveTU433";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[1:6]"  10 10 9 9 9 10;
	setAttr -s 7 ".kot[1:6]"  10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU434";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 9;
	setAttr -s 7 ".kot[0:6]"  3 5 5 9 9 9 5;
createNode animCurveTA -n "animCurveTA1369";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 3.9531091186723013 2 3.9531091186723013 
		6 -14.637962849997619 9 -14.518847873924969 14 -14.518847873924969 26 -21.437639526377588 
		36 3.9531091186723013 44 3.9531091186723013;
	setAttr -s 8 ".kit[0:7]"  3 10 10 9 9 10 9 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 9 9 10 9 10;
createNode animCurveTA -n "animCurveTA1370";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.62018686761647346 2 0.62018686761647346 
		6 -16.857717918663866 9 -27.3093660258745 14 -27.3093660258745 26 -7.3501440550302366 
		36 0.62018686761647346 44 0.62018686761647346;
	setAttr -s 8 ".kit[0:7]"  3 10 10 9 9 10 9 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 9 9 10 9 10;
createNode animCurveTA -n "animCurveTA1371";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 5.3292188742882338 2 5.3292188742882338 
		6 -29.173173265872954 9 -19.210891698246936 14 -19.210891698246936 26 -10.246784629332097 
		36 5.3292188742882338 44 5.3292188742882338;
	setAttr -s 8 ".kit[0:7]"  3 10 10 9 9 10 9 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 9 9 10 9 10;
createNode animCurveTU -n "animCurveTU435";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU436";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
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
	setAttr ".ktv[0]"  0 -1.1102230246251565e-016;
createNode animCurveTA -n "animCurveTA1372";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -44.757110789561033 2 -53.275457156994136 
		6 -35.275794960500093 14 -39.364867570150238 26 -26.402288603848898 36 -44.757110789561033 
		44 -44.757110789561033;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 10 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 10 9 10;
createNode animCurveTA -n "animCurveTA1373";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.10616870005340093 2 -5.5814313454202651 
		6 -10.689682521140393 14 -9.6374459335841696 26 -8.6336205067808649 36 0.10616870005340093 
		44 0.10616870005340093;
	setAttr -s 7 ".kit[3:6]"  9 10 9 10;
	setAttr -s 7 ".kot[3:6]"  9 10 9 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1374";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -4.9406171614869088 2 9.6807371080191995 
		6 11.016323524197215 14 1.1806403741681644 26 -7.635121556782499 36 -4.9406171614869088 
		44 -4.9406171614869088;
	setAttr -s 7 ".kit[3:6]"  9 10 9 10;
	setAttr -s 7 ".kot[3:6]"  9 10 9 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1375";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -27.604588158357807 2 -27.604588158357807 
		6 -27.604588158357807 9 -27.604588158357807 14 -27.604588158357807 36 -27.604588158357807 
		44 -27.604588158357807;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1376";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.70641431476594085 2 0.70641431476594085 
		6 0.70641431476594085 9 0.70641431476594085 14 0.70641431476594085 36 0.70641431476594085 
		44 0.70641431476594085;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU437";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU438";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 3;
createNode animCurveTU -n "animCurveTU439";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU440";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "animCurveTU441";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1377";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1378";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1379";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL439";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 2.2204460492503131e-016;
createNode animCurveTL -n "animCurveTL440";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "animCurveTL441";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 4.4408920985006262e-016;
createNode animCurveTU -n "animCurveTU442";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 2 0 6 0 9 0 14 0 36 1 44 1;
	setAttr -s 7 ".kit[1:6]"  10 10 9 9 9 10;
	setAttr -s 7 ".kot[1:6]"  10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1380";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.1288109940741509 2 0 6 0 9 0 14 0 36 
		1.1288109940741509 44 1.1288109940741509;
	setAttr -s 7 ".kit[1:6]"  10 10 9 9 9 10;
	setAttr -s 7 ".kot[1:6]"  10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1381";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 4.8219581414201906 2 0 6 0 9 0 14 0 36 
		4.8219581414201906 44 4.8219581414201906;
	setAttr -s 7 ".kit[1:6]"  10 10 9 9 9 10;
	setAttr -s 7 ".kot[1:6]"  10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1382";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 28.08558650754679 2 0 6 0 9 0 14 0 36 
		28.08558650754679 44 28.08558650754679;
	setAttr -s 7 ".kit[1:6]"  10 10 9 9 9 10;
	setAttr -s 7 ".kot[1:6]"  10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU443";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1383";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 68.629003384766676 2 68.629003384766676 
		6 68.629003384766676 9 68.629003384766676 14 68.629003384766676 36 68.629003384766676 
		44 68.629003384766676;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1384";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 5.1251585428584878 2 5.1251585428584878 
		6 5.1251585428584878 9 5.1251585428584878 14 5.1251585428584878 36 5.1251585428584878 
		44 5.1251585428584878;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1385";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -1.4794141658124507 2 -1.4794141658124507 
		6 -1.4794141658124507 9 -1.4794141658124507 14 -1.4794141658124507 36 -1.4794141658124507 
		44 -1.4794141658124507;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1386";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 2.9967431843380723 2 2.9967431843380723 
		6 2.9967431843380723 9 2.9967431843380723 14 2.9967431843380723 36 2.9967431843380723 
		44 2.9967431843380723;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1387";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 27.356153209428296 2 27.356153209428296 
		6 27.356153209428296 9 27.356153209428296 14 27.356153209428296 36 27.356153209428296 
		44 27.356153209428296;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1388";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 4.8891453517792058 2 4.8891453517792058 
		6 4.8891453517792058 9 4.8891453517792058 14 4.8891453517792058 36 4.8891453517792058 
		44 4.8891453517792058;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU444";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1389";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 59.032884886088816 2 59.032884886088816 
		6 59.032884886088816 9 59.032884886088816 14 59.032884886088816 36 59.032884886088816 
		44 59.032884886088816;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1390";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1391";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1392";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 61.945270723308987 2 61.945270723308987 
		6 61.945270723308987 9 61.945270723308987 14 61.945270723308987 36 61.945270723308987 
		44 61.945270723308987;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1393";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1394";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU445";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1395";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 59.032884886088816 2 59.032884886088816 
		6 59.032884886088816 9 59.032884886088816 14 59.032884886088816 36 59.032884886088816 
		44 59.032884886088816;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1396";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1397";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1398";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 61.945270723308987 2 61.945270723308987 
		6 61.945270723308987 9 61.945270723308987 14 61.945270723308987 36 61.945270723308987 
		44 61.945270723308987;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1399";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1400";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU446";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1401";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 59.032884886088816 2 59.032884886088816 
		6 59.032884886088816 9 59.032884886088816 14 59.032884886088816 36 59.032884886088816 
		44 59.032884886088816;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1402";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1403";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1404";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 72.878304588436421 2 72.878304588436421 
		6 72.878304588436421 9 72.878304588436421 14 72.878304588436421 36 72.878304588436421 
		44 72.878304588436421;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1405";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1406";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU447";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1407";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 77.67986202714836 2 77.67986202714836 
		6 77.67986202714836 9 77.67986202714836 14 77.67986202714836 36 77.67986202714836 
		44 77.67986202714836;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1408";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1409";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1410";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 65.952779168408995 2 65.952779168408995 
		6 65.952779168408995 9 65.952779168408995 14 65.952779168408995 36 65.952779168408995 
		44 65.952779168408995;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1411";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 12.091864976351665 2 12.091864976351665 
		6 12.091864976351665 9 12.091864976351665 14 12.091864976351665 36 12.091864976351665 
		44 12.091864976351665;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1412";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -6.5683373417752975 2 -6.5683373417752975 
		6 -6.5683373417752975 9 -6.5683373417752975 14 -6.5683373417752975 36 -6.5683373417752975 
		44 -6.5683373417752975;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1413";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1414";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1415";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU448";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1416";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 -41.794044607487734 9 0 14 0 
		36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1417";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 3.9610634349325946 9 0 14 0 36 
		0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1418";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 -16.457894349566757 9 0 14 0 
		36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1419";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1420";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1421";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU449";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1422";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1423";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1424";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1425";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 -18.894432693115164 9 0 14 0 
		36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1426";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 -1.3304134744315801 9 0 14 0 
		36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1427";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 2.4250471853845035 9 0 14 0 36 
		0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU450";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1428";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1429";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1430";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1431";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 -20.64388457687766 9 0 14 0 36 
		0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1432";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 -17.581141137818914 9 0 14 0 
		36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1433";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 -9.2727018485787109 9 0 14 0 
		36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU451";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1434";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1435";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1436";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1437";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 -18.894432693115164 9 0 14 0 
		36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1438";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 -1.3304134744315801 9 0 14 0 
		36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1439";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 2.4250471853845035 9 0 14 0 36 
		0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU452";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1440";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1441";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1442";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1443";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 -22.829916979978496 9 0 14 0 
		36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1444";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 5.9064999916047594 9 0 14 0 36 
		0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1445";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 7.6747381419597698 9 0 14 0 36 
		0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1446";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1447";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1448";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU453";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 9;
	setAttr -s 7 ".kot[0:6]"  3 5 5 9 9 9 5;
createNode animCurveTU -n "animCurveTU454";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 9;
	setAttr -s 7 ".kot[0:6]"  3 5 5 9 9 9 5;
createNode animCurveTU -n "animCurveTU455";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 2 1 6 1 9 1 14 1 36 1 44 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1449";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -10.173354040024311 2 -10.173354040024311 
		6 -10.173354040024311 9 -10.173354040024311 14 -10.173354040024311 36 -10.173354040024311 
		44 -10.173354040024311;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1450";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1451";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL442";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL443";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.643246524321337 2 0.643246524321337 
		6 0.643246524321337 9 0.643246524321337 14 0.643246524321337 36 0.643246524321337 
		44 0.643246524321337;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL444";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.10481400598920043 2 0.10481400598920043 
		6 0.10481400598920043 9 0.10481400598920043 14 0.10481400598920043 36 0.10481400598920043 
		44 0.10481400598920043;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1452";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1453";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1454";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU456";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1455";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1456";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1457";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1458";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1459";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1460";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1461";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1462";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1463";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU457";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 2 1 6 1 9 1 14 1 36 1 44 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1464";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 40.718223104721211 2 40.718223104721211 
		6 42.389414205104963 9 40.718223104721211 14 40.718223104721211 36 40.718223104721211 
		44 40.718223104721211;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1465";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -38.301705751263519 2 -38.301705751263519 
		6 -0.092675643272788211 9 -38.301705751263519 14 -38.301705751263519 36 -38.301705751263519 
		44 -38.301705751263519;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1466";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 21.733945627788874 2 21.733945627788874 
		6 -9.0530932077411563 9 21.733945627788874 14 21.733945627788874 36 21.733945627788874 
		44 21.733945627788874;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU458";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 9;
	setAttr -s 7 ".kot[0:6]"  3 5 5 9 9 9 5;
createNode animCurveTU -n "animCurveTU459";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 9;
	setAttr -s 7 ".kot[0:6]"  3 5 5 9 9 9 5;
createNode animCurveTU -n "animCurveTU460";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 2 1 6 1 9 1 14 1 36 1 44 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1467";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 17.962181958626559 2 17.962181958626559 
		6 17.962181958626559 9 17.962181958626559 14 17.962181958626559 36 17.962181958626559 
		44 17.962181958626559;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1468";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1469";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL445";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL446";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.64789329560123088 2 -0.64789329560123088 
		6 -0.64789329560123088 9 -0.64789329560123088 14 -0.64789329560123088 36 -0.64789329560123088 
		44 -0.64789329560123088;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL447";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.07395615046270454 2 -0.07395615046270454 
		6 -0.07395615046270454 9 -0.07395615046270454 14 -0.07395615046270454 36 -0.07395615046270454 
		44 -0.07395615046270454;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1470";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1471";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1472";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU461";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1473";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1474";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1475";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1476";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1477";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1478";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1479";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1480";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1481";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA1482";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -10.753373031419716 2 -17.734731751322037 
		6 6.743800174452649 9 7.6893258541134886 14 6.543056645738603 36 -10.753373031419716 
		44 -10.753373031419716;
	setAttr -s 7 ".kit[1:6]"  10 10 9 9 9 10;
	setAttr -s 7 ".kot[1:6]"  10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1483";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -4.9387346018875373 2 -9.5934827644846532 
		6 8.0106790017717522 9 -6.3256490803967935 14 -13.147855742636581 36 -4.9387346018875373 
		44 -4.9387346018875373;
	setAttr -s 7 ".kit[1:6]"  10 10 9 9 9 10;
	setAttr -s 7 ".kot[1:6]"  10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1484";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 22.393157938684443 2 -0.39775679267641406 
		6 -19.686900223970859 9 -12.003788434107978 14 -12.765682327538606 36 22.393157938684443 
		44 22.393157938684443;
	setAttr -s 7 ".kit[1:6]"  10 10 9 9 9 10;
	setAttr -s 7 ".kot[1:6]"  10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1485";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -4.0865779949808214 2 -4.2450945433717804 
		6 -35.602293297326803 9 -35.602293297326803 14 -35.602293297326803 36 -4.0865779949808214 
		44 -4.0865779949808214;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1486";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -10.471027640707172 2 -4.5459021136507047 
		6 -4.5459021136507101 9 -4.5459021136507101 14 -4.5459021136507101 36 -10.471027640707172 
		44 -10.471027640707172;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1487";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -1.7475532445702493 2 -1.3157593888328765 
		6 -1.3157593888328663 9 -1.3157593888328663 14 -1.3157593888328663 36 -1.7475532445702493 
		44 -1.7475532445702493;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU462";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 2 1 6 1 9 1 14 1 36 1 44 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1488";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 20.69101533741409 2 21.906438891509826 
		6 -7.8697534080980178 9 -7.521840036072275 14 -7.521840036072275 36 20.69101533741409 
		44 20.69101533741409;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1489";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -8.3978566024888135 2 -0.8354225779840545 
		6 -0.46917076279576375 9 -0.11453527407705044 14 -0.11453527407705044 36 -8.3978566024888135 
		44 -8.3978566024888135;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1490";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 2.8255796210686652 2 16.828782908791208 
		6 -3.9428792263985941 9 -0.99731958790472186 14 -0.99731958790472186 36 2.8255796210686652 
		44 2.8255796210686652;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU463";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 8 0 11 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1491";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 22.12152969098814 6 -19.020028462560138 
		8 45.677698880875923 11 22.22617041317131 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1492";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 11.588136453822246 6 14.846652384163541 
		8 -21.325917355021673 11 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1493";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 -19.399885431676186 6 0.077927817468460212 
		8 14.481735565844534 11 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1494";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -17.821366541589882 2 -20.135660035309265 
		6 30.310071991162978 8 22.480569972030203 11 -17.821366541589882 36 -17.821366541589882 
		44 -17.821366541589882;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1495";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -12.005893876475762 2 -1.4735818444474962 
		6 -36.52066469093252 8 -19.584969256775519 11 -12.005893876475762 36 -12.005893876475762 
		44 -12.005893876475762;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1496";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 9.1378572146953019 2 -6.1933330552905339 
		6 9.5229640598438383 8 32.853469246553615 11 9.1378572146953019 36 9.1378572146953019 
		44 9.1378572146953019;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1497";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -28.841216077843235 2 -21.398758882884259 
		6 -70.056331073725474 7 -41.377630909207952 9 -30.693272092489384 14 5.614471073841564 
		16 -13.316019347789899 18 -16.974610611406654 24 9.2740928950464347 30 37.799995382172838 
		36 -28.841216077843235 44 -28.841216077843235;
	setAttr -s 12 ".kit[0:11]"  1 10 10 10 9 9 10 10 
		10 10 9 10;
	setAttr -s 12 ".kot[0:11]"  1 10 10 10 9 9 10 10 
		10 10 9 10;
	setAttr -s 12 ".kix[0:11]"  1 0.26787200570106506 0.4312417209148407 
		0.14403936266899109 0.27363663911819458 0.60976517200469971 0.32036674022674561 0.56024211645126343 
		0.38598626852035522 0.51530778408050537 0.37236949801445007 1;
	setAttr -s 12 ".kiy[0:11]"  0 -0.96345454454421997 -0.9022364616394043 
		0.98957192897796631 0.96183311939239502 0.79258215427398682 -0.94729357957839966 
		0.82832890748977661 0.92250454425811768 -0.85700523853302002 -0.92808455228805542 
		0;
	setAttr -s 12 ".kox[0:11]"  1 0.26787200570106506 0.4312417209148407 
		0.14403936266899109 0.27363663911819458 0.60976517200469971 0.32036674022674561 0.56024211645126343 
		0.38598626852035522 0.51530778408050537 0.37236949801445007 1;
	setAttr -s 12 ".koy[0:11]"  0 -0.96345454454421997 -0.9022364616394043 
		0.98957192897796631 0.96183311939239502 0.79258215427398682 -0.94729357957839966 
		0.82832890748977661 0.92250454425811768 -0.85700523853302002 -0.92808455228805542 
		0;
createNode animCurveTA -n "animCurveTA1498";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -21.716766331039956 2 -44.493336826887109 
		6 -34.335394717579412 7 -35.242836808524345 9 -31.053777095640672 14 7.12588334741063 
		16 11.69880883353275 18 7.350968230268478 24 -11.252092329939861 30 37.783382217637325 
		36 -21.716766331039956 44 -21.716766331039956;
	setAttr -s 12 ".kit[0:11]"  1 10 10 10 9 9 10 10 
		10 10 9 10;
	setAttr -s 12 ".kot[0:11]"  1 10 10 10 9 9 10 10 
		10 10 9 10;
	setAttr -s 12 ".kix[0:11]"  1 0.67227685451507568 1 1 0.30091479420661926 
		0.2984546422958374 0.99956625699996948 0.55415451526641846 0.60157793760299683 0.90965855121612549 
		0.4098924994468689 1;
	setAttr -s 12 ".kiy[0:11]"  0 -0.74029988050460815 0 0 0.95365101099014282 
		0.95442384481430054 0.029450757429003716 -0.83241385221481323 0.79881405830383301 
		-0.41535690426826477 -0.91213387250900269 0;
	setAttr -s 12 ".kox[0:11]"  1 0.67227685451507568 1 1 0.30091479420661926 
		0.2984546422958374 0.99956625699996948 0.55415451526641846 0.60157793760299683 0.90965855121612549 
		0.4098924994468689 1;
	setAttr -s 12 ".koy[0:11]"  0 -0.74029988050460815 0 0 0.95365101099014282 
		0.95442384481430054 0.029450757429003716 -0.83241385221481323 0.79881405830383301 
		-0.41535690426826477 -0.91213387250900269 0;
createNode animCurveTA -n "animCurveTA1499";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 23.535235892507558 2 -54.121608764578532 
		6 55.842140816483784 7 67.526237960347586 9 46.107073452306814 14 -21.411977821235347 
		16 -69.673223518289333 18 -71.757862764492842 24 -35.488194023533438 30 -43.974464974548177 
		36 23.535235892507558 44 23.535235892507558;
	setAttr -s 12 ".kit[0:11]"  1 10 10 10 9 9 10 10 
		10 10 9 10;
	setAttr -s 12 ".kot[0:11]"  1 10 10 10 9 9 10 10 
		10 10 9 10;
	setAttr -s 12 ".kix[0:11]"  1 0.33429107069969177 0.078258752822875977 
		0.50722193717956543 0.14864799380302429 0.11470667272806168 1 1 0.63633352518081665 
		0.36196273565292358 0.36823230981826782 1;
	setAttr -s 12 ".kiy[0:11]"  0 0.94246989488601685 0.99693310260772705 
		-0.86181551218032837 -0.98889017105102539 -0.99339932203292847 0 0 0.77141404151916504 
		0.93219256401062012 0.92973381280899048 0;
	setAttr -s 12 ".kox[0:11]"  1 0.33429107069969177 0.078258752822875977 
		0.50722193717956543 0.14864799380302429 0.11470667272806168 1 1 0.63633352518081665 
		0.36196273565292358 0.36823230981826782 1;
	setAttr -s 12 ".koy[0:11]"  0 0.94246989488601685 0.99693310260772705 
		-0.86181551218032837 -0.98889017105102539 -0.99339932203292847 0 0 0.77141404151916504 
		0.93219256401062012 0.92973381280899048 0;
createNode animCurveTL -n "animCurveTL448";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 9 9 9 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL449";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 9 9 9 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL450";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 9 9 9 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU464";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 2 2 2 6 2 9 2 14 2 36 2 44 2;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 9;
	setAttr -s 7 ".kot[0:6]"  3 5 5 9 9 9 5;
createNode animCurveTU -n "animCurveTU465";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 9;
	setAttr -s 7 ".kot[0:6]"  3 5 5 9 9 9 5;
createNode animCurveTA -n "animCurveTA1500";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -24.093441664171177 2 -24.093441664171177 
		6 -24.093441664171177 9 -24.093441664171177 14 -24.093441664171177 36 -24.093441664171177 
		44 -24.093441664171177;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1501";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 49.48465546224881 2 49.48465546224881 
		6 49.48465546224881 9 49.48465546224881 14 49.48465546224881 36 49.48465546224881 
		44 49.48465546224881;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1502";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 58.801792680015588 2 58.801792680015588 
		6 58.801792680015588 9 58.801792680015588 14 58.801792680015588 36 58.801792680015588 
		44 58.801792680015588;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL451";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -1.2755255474500937 2 -1.2755255474500937 
		6 -1.2755255474500937 9 -1.2755255474500937 14 -1.2755255474500937 36 -1.2755255474500937 
		44 -1.2755255474500937;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL452";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -1.4392043230118035 2 -1.4392043230118035 
		6 -1.4392043230118035 9 -1.4392043230118035 14 -1.4392043230118035 36 -1.4392043230118035 
		44 -1.4392043230118035;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL453";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -2.1802956492995231 2 -2.1802956492995231 
		6 -2.1802956492995231 9 -2.1802956492995231 14 -2.1802956492995231 36 -2.1802956492995231 
		44 -2.1802956492995231;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL454";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL455";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL456";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1503";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 1.1134085745786892 2 27.808642121000393 
		6 0.4309670077449772 9 -1.8103088980788413 13 12.292985692487527 18 -4.3061082813810456 
		36 1.1134085745786892 44 1.1134085745786892;
	setAttr -s 8 ".kit[0:7]"  3 10 10 9 10 9 9 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 9 10 9 9 10;
createNode animCurveTA -n "animCurveTA1504";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -5.3180374758492821 2 13.880484826688257 
		6 9.1565073560847843 9 6.0613234283353439 13 5.3184519947018956 18 -0.11289924918444746 
		36 -5.3180374758492821 44 -5.3180374758492821;
	setAttr -s 8 ".kit[0:7]"  3 10 10 9 10 9 9 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 9 10 9 9 10;
createNode animCurveTA -n "animCurveTA1505";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 7.8609313736722894 2 -10.001356418026088 
		6 -9.0303005168671309 9 27.044880328271653 13 8.2082425745644798 18 21.78255486592473 
		36 7.8609313736722894 44 7.8609313736722894;
	setAttr -s 8 ".kit[0:7]"  3 10 10 9 10 9 9 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 9 10 9 9 10;
createNode animCurveTL -n "animCurveTL457";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 18 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL458";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 18 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL459";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 18 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1506";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1507";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1508";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL460";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL461";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL462";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU466";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 9;
	setAttr -s 7 ".kot[0:6]"  3 5 5 9 9 9 5;
createNode animCurveTA -n "animCurveTA1509";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -5.1107219305963252 2 -5.1107219305963252 
		6 -5.1107219305963252 9 -5.1107219305963252 14 -5.1107219305963252 36 -5.1107219305963252 
		44 -5.1107219305963252;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1510";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 8.2811672786141717 2 8.2811672786141717 
		6 8.2811672786141717 9 8.2811672786141717 14 8.2811672786141717 36 8.2811672786141717 
		44 8.2811672786141717;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1511";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.92645454014921158 2 -0.92645454014921158 
		6 -0.92645454014921158 9 -0.92645454014921158 14 -0.92645454014921158 36 -0.92645454014921158 
		44 -0.92645454014921158;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL463";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.046856395845859107 2 -0.046856395845859107 
		6 -0.046856395845859107 9 -0.046856395845859107 14 -0.046856395845859107 36 -0.046856395845859107 
		44 -0.046856395845859107;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL464";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.023348763690700665 2 -0.023348763690700665 
		6 -0.023348763690700665 9 -0.023348763690700665 14 -0.023348763690700665 36 -0.023348763690700665 
		44 -0.023348763690700665;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL465";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.13506113021862395 2 -0.13506113021862395 
		6 -0.13506113021862395 9 -0.13506113021862395 14 -0.13506113021862395 36 -0.13506113021862395 
		44 -0.13506113021862395;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1512";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -1.6266160090263075 2 11.951230590525794 
		6 -28.322347383459473 9 3.5905954302828986 14 -17.15327938952138 36 -1.6266160090263075 
		44 -1.6266160090263075;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1513";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 2.8499857758927387 2 5.526097947981941 
		6 -22.468757199635384 9 -3.670909483054849 14 -4.4373906413582889 36 2.8499857758927387 
		44 2.8499857758927387;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1514";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -25.210898828531619 2 -17.980023322602221 
		6 -23.744181079082555 9 -44.57734613947553 14 -14.276812009242056 36 -25.210898828531619 
		44 -25.210898828531619;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL466";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.011193700785458628 2 -0.011193700785458628 
		6 -0.011193700785458628 9 -0.011193700785458628 14 -0.011193700785458628 36 -0.011193700785458628 
		44 -0.011193700785458628;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL467";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.020021267836214246 2 -0.020021267836214246 
		6 -0.020021267836214246 9 -0.020021267836214246 14 -0.020021267836214246 36 -0.020021267836214246 
		44 -0.020021267836214246;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL468";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.032441787830836878 2 0.032441787830836878 
		6 0.032441787830836878 9 0.032441787830836878 14 0.032441787830836878 36 0.032441787830836878 
		44 0.032441787830836878;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1515";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1516";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1517";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL469";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL470";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL471";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1518";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -15.609971163878811 2 -32.76444835429448 
		6 13.375867439420622 9 12.229003315813577 14 12.229003315813577 26 -15.285032679618853 
		36 -15.609971163878811 44 -15.609971163878811;
	setAttr -s 8 ".kit[0:7]"  3 10 10 9 9 10 9 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 9 9 10 9 10;
createNode animCurveTA -n "animCurveTA1519";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 8.3116042646716988 2 -6.1994046207302214 
		6 3.7920543184943849 9 0.68683487368693619 14 0.68683487368693619 26 9.5144902952458903 
		36 8.3116042646716988 44 8.3116042646716988;
	setAttr -s 8 ".kit[0:7]"  3 10 10 9 9 10 9 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 9 9 10 9 10;
createNode animCurveTA -n "animCurveTA1520";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 14.458598883932659 2 9.2273507351466595 
		6 21.341420023406254 9 21.997344845742571 14 21.997344845742571 26 8.123944317134546 
		36 14.458598883932659 44 14.458598883932659;
	setAttr -s 8 ".kit[0:7]"  3 10 10 9 9 10 9 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 9 9 10 9 10;
createNode animCurveTL -n "animCurveTL472";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.18868131369562219 2 -0.29215109882808127 
		6 -0.29215109882808171 9 -0.37048938720157992 14 -0.37048938720157992 26 -0.18868131369562219 
		36 -0.18868131369562219 44 -0.18868131369562219;
	setAttr -s 8 ".kit[0:7]"  3 10 10 3 3 10 9 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 3 3 10 9 10;
createNode animCurveTL -n "animCurveTL473";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.23059098815955009 2 0.10292958691644806 
		6 -0.15024217379267524 9 -0.096381739290106516 14 -0.0099810605034167388 26 0.29644066879462166 
		36 0.23059098815955009 44 0.23059098815955009;
	setAttr -s 8 ".kit[0:7]"  9 10 10 3 3 10 9 10;
	setAttr -s 8 ".kot[0:7]"  9 10 10 3 3 10 9 10;
createNode animCurveTL -n "animCurveTL474";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.049918713102953649 2 0.19967362080880191 
		6 0.15360893517512042 9 0.08585971284693561 14 0.08585971284693561 26 0.051298067279156701 
		36 0.049918713102953649 44 0.049918713102953649;
	setAttr -s 8 ".kit[0:7]"  3 10 9 3 9 10 9 10;
	setAttr -s 8 ".kot[0:7]"  3 10 9 3 9 10 9 10;
createNode animCurveTU -n "animCurveTU467";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 9;
	setAttr -s 7 ".kot[0:6]"  3 5 5 9 9 9 5;
createNode animCurveTU -n "animCurveTU468";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.084155571970393403 2 0.084155571970393403 
		6 0.084155571970393403 9 0.084155571970393403 14 0.084155571970393403 36 0.084155571970393403 
		44 0.084155571970393403;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL475";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.067207227343123899 2 0.067207227343123899 
		6 0.067207227343123899 9 0.067207227343123899 14 0.067207227343123899 36 0.067207227343123899 
		44 0.067207227343123899;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL476";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.20472824713235571 2 -0.20472824713235571 
		6 -0.20472824713235571 9 -0.20472824713235571 14 -0.20472824713235571 36 -0.20472824713235571 
		44 -0.20472824713235571;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL477";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.20941646546924442 2 0.20941646546924442 
		6 0.20941646546924442 9 0.20941646546924442 14 0.20941646546924442 36 0.20941646546924442 
		44 0.20941646546924442;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU469";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 9;
	setAttr -s 7 ".kot[0:6]"  3 5 5 9 9 9 5;
createNode animCurveTU -n "animCurveTU470";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.084155864375844894 2 0.084155864375844894 
		6 0.084155864375844894 9 0.084155864375844894 14 0.084155864375844894 36 0.084155864375844894 
		44 0.084155864375844894;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL478";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL479";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.40088449385078673 2 -0.40088449385078673 
		6 -0.40088449385078673 9 -0.40088449385078673 14 -0.40088449385078673 36 -0.40088449385078673 
		44 -0.40088449385078673;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL480";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.69609418843799409 2 -0.69609418843799409 
		6 -0.69609418843799409 9 -0.69609418843799409 14 -0.69609418843799409 36 -0.69609418843799409 
		44 -0.69609418843799409;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1521";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 -10.656062022499983 6 -11.748383483616394 
		9 20.161266001110242 14 -14.633931480610586 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1522";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1523";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1524";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1525";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1526";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1527";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 22.903067681661962 6 -16.439769594586831 
		9 -11.162168711121657 14 9.9350106506455855 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1528";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1529";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1530";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -18.592620239620459 2 -37.827745330028023 
		6 11.286543079505625 9 -21.816888096390684 12 -1.9092770260664989 17 -18.592620239620459 
		36 -18.592620239620459 44 -18.592620239620459;
	setAttr -s 8 ".kit[0:7]"  3 10 10 9 10 9 9 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 9 10 9 9 10;
createNode animCurveTA -n "animCurveTA1531";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -4.0495369920864128 2 4.0354703502923419 
		6 -16.614714586469958 9 -3.746317185385506 12 -11.351291780283574 17 -4.0495369920864128 
		36 -4.0495369920864128 44 -4.0495369920864128;
	setAttr -s 8 ".kit[0:7]"  3 10 10 9 10 9 9 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 9 10 9 9 10;
createNode animCurveTA -n "animCurveTA1532";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -24.718935474963271 2 -11.032334769665507 
		6 -32.095632055612754 9 -27.61496966539756 12 -28.446813130617105 17 -24.718935474963271 
		36 -24.718935474963271 44 -24.718935474963271;
	setAttr -s 8 ".kit[0:7]"  3 10 10 9 10 9 9 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 9 10 9 9 10;
createNode animCurveTA -n "animCurveTA1533";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1534";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1535";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU471";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 2 1 6 1 9 1 14 1 36 1 44 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU472";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 2 1 6 1 9 1 14 1 36 1 44 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU473";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 2 1 6 1 9 1 14 1 36 1 44 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1536";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1537";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1538";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL481";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL482";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL483";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU474";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 2 1 6 1 9 1 14 1 36 1 44 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU475";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 2 1 6 1 9 1 14 1 36 1 44 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU476";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 2 1 6 1 9 1 14 1 36 1 44 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1539";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1540";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1541";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL484";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL485";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL486";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1542";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1543";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1544";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 7.2644697342894906 2 7.2644697342894906 
		6 7.2644697342894906 9 7.2644697342894906 14 7.2644697342894906 36 7.2644697342894906 
		44 7.2644697342894906;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL487";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL488";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL489";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL490";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.000119480405310887 2 -0.000119480405310887 
		6 -0.000119480405310887 8 -0.000119480405310887 11 -0.000119480405310887 36 -0.000119480405310887 
		44 -0.000119480405310887;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL491";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.1152566135867675 2 0.1152566135867675 
		6 0.1152566135867675 8 0.1152566135867675 11 0.1152566135867675 36 0.1152566135867675 
		44 0.1152566135867675;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTL -n "animCurveTL492";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.19515846066137013 2 0.19515846066137013 
		6 0.19515846066137013 8 0.19515846066137013 11 0.19515846066137013 36 0.19515846066137013 
		44 0.19515846066137013;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU477";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 2 1 6 1 9 1 14 1 36 1 44 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU478";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 2 1 6 1 9 1 14 1 36 1 44 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU479";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 2 1 6 1 9 1 14 1 36 1 44 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU480";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 2 1 6 1 9 1 14 1 36 1 44 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU481";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 2 1 6 1 9 1 14 1 36 1 44 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTU -n "animCurveTU482";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 2 1 6 1 9 1 14 1 36 1 44 1;
	setAttr -s 7 ".kit[0:6]"  3 10 10 9 9 9 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 9 9 9 10;
createNode animCurveTA -n "animCurveTA1545";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 6 0 9 0 14 0 36 0 44 0;
	setAttr -s 7 ".kit[3:6]"  9 9 9 10;
	setAttr -s 7 ".kot[3:6]"  9 9 9 10;
createNode animCurveTA -n "Ratcatcher_CTRL_TwistL_rotateX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  36 0;
createNode animCurveTU -n "Ratcatcher_CTRL_JAR_scaleZ1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  36 1;
createNode animCurveTU -n "Ratcatcher_CTRL_JAR_scaleY1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  36 1;
createNode animCurveTU -n "Ratcatcher_CTRL_JAR_scaleX1";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  36 1;
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
connectAttr "attack2ASource1.cl" "clipLibrary1.sc[0]";
connectAttr "animCurveTU419.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "animCurveTA1352.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "animCurveTA1353.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "animCurveTA1354.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "animCurveTU420.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "animCurveTU421.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "animCurveTU422.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "animCurveTU423.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "animCurveTA1355.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "animCurveTA1356.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "animCurveTA1357.a" "clipLibrary1.cel[0].cev[10].cevr";
connectAttr "animCurveTU424.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "animCurveTU425.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "animCurveTL430.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "animCurveTL431.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "animCurveTL432.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "animCurveTA1358.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "animCurveTA1359.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "animCurveTA1360.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "animCurveTA1361.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "animCurveTA1362.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "animCurveTU426.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "animCurveTU427.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "animCurveTU428.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "animCurveTU429.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "animCurveTA1363.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "animCurveTA1364.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "animCurveTA1365.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "animCurveTL433.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "animCurveTL434.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "animCurveTL435.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "animCurveTU430.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "animCurveTA1366.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "animCurveTA1367.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "animCurveTA1368.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "animCurveTU431.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "animCurveTU432.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "animCurveTU433.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "animCurveTU434.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "animCurveTA1369.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "animCurveTA1370.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "animCurveTA1371.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "animCurveTU435.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "animCurveTU436.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "animCurveTL436.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "animCurveTL437.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "animCurveTL438.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "animCurveTA1372.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "animCurveTA1373.a" "clipLibrary1.cel[0].cev[48].cevr";
connectAttr "animCurveTA1374.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "animCurveTA1375.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "animCurveTA1376.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "animCurveTU437.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "animCurveTU438.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "animCurveTU439.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "animCurveTU440.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "animCurveTU441.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "animCurveTA1377.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "animCurveTA1378.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "animCurveTA1379.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "animCurveTL439.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "animCurveTL440.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "animCurveTL441.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "animCurveTU442.a" "clipLibrary1.cel[0].cev[63].cevr";
connectAttr "animCurveTA1380.a" "clipLibrary1.cel[0].cev[64].cevr";
connectAttr "animCurveTA1381.a" "clipLibrary1.cel[0].cev[65].cevr";
connectAttr "animCurveTA1382.a" "clipLibrary1.cel[0].cev[66].cevr";
connectAttr "animCurveTU443.a" "clipLibrary1.cel[0].cev[67].cevr";
connectAttr "animCurveTA1383.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "animCurveTA1384.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "animCurveTA1385.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "animCurveTA1386.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "animCurveTA1387.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "animCurveTA1388.a" "clipLibrary1.cel[0].cev[73].cevr";
connectAttr "animCurveTU444.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "animCurveTA1389.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "animCurveTA1390.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "animCurveTA1391.a" "clipLibrary1.cel[0].cev[77].cevr";
connectAttr "animCurveTA1392.a" "clipLibrary1.cel[0].cev[78].cevr";
connectAttr "animCurveTA1393.a" "clipLibrary1.cel[0].cev[79].cevr";
connectAttr "animCurveTA1394.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "animCurveTU445.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "animCurveTA1395.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "animCurveTA1396.a" "clipLibrary1.cel[0].cev[83].cevr";
connectAttr "animCurveTA1397.a" "clipLibrary1.cel[0].cev[84].cevr";
connectAttr "animCurveTA1398.a" "clipLibrary1.cel[0].cev[85].cevr";
connectAttr "animCurveTA1399.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "animCurveTA1400.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "animCurveTU446.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "animCurveTA1401.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr "animCurveTA1402.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "animCurveTA1403.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "animCurveTA1404.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "animCurveTA1405.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "animCurveTA1406.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "animCurveTU447.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "animCurveTA1407.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "animCurveTA1408.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "animCurveTA1409.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "animCurveTA1410.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "animCurveTA1411.a" "clipLibrary1.cel[0].cev[100].cevr";
connectAttr "animCurveTA1412.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "animCurveTA1413.a" "clipLibrary1.cel[0].cev[102].cevr";
connectAttr "animCurveTA1414.a" "clipLibrary1.cel[0].cev[103].cevr";
connectAttr "animCurveTA1415.a" "clipLibrary1.cel[0].cev[104].cevr";
connectAttr "animCurveTU448.a" "clipLibrary1.cel[0].cev[105].cevr";
connectAttr "animCurveTA1416.a" "clipLibrary1.cel[0].cev[106].cevr";
connectAttr "animCurveTA1417.a" "clipLibrary1.cel[0].cev[107].cevr";
connectAttr "animCurveTA1418.a" "clipLibrary1.cel[0].cev[108].cevr";
connectAttr "animCurveTA1419.a" "clipLibrary1.cel[0].cev[109].cevr";
connectAttr "animCurveTA1420.a" "clipLibrary1.cel[0].cev[110].cevr";
connectAttr "animCurveTA1421.a" "clipLibrary1.cel[0].cev[111].cevr";
connectAttr "animCurveTU449.a" "clipLibrary1.cel[0].cev[112].cevr";
connectAttr "animCurveTA1422.a" "clipLibrary1.cel[0].cev[113].cevr";
connectAttr "animCurveTA1423.a" "clipLibrary1.cel[0].cev[114].cevr";
connectAttr "animCurveTA1424.a" "clipLibrary1.cel[0].cev[115].cevr";
connectAttr "animCurveTA1425.a" "clipLibrary1.cel[0].cev[116].cevr";
connectAttr "animCurveTA1426.a" "clipLibrary1.cel[0].cev[117].cevr";
connectAttr "animCurveTA1427.a" "clipLibrary1.cel[0].cev[118].cevr";
connectAttr "animCurveTU450.a" "clipLibrary1.cel[0].cev[119].cevr";
connectAttr "animCurveTA1428.a" "clipLibrary1.cel[0].cev[120].cevr";
connectAttr "animCurveTA1429.a" "clipLibrary1.cel[0].cev[121].cevr";
connectAttr "animCurveTA1430.a" "clipLibrary1.cel[0].cev[122].cevr";
connectAttr "animCurveTA1431.a" "clipLibrary1.cel[0].cev[123].cevr";
connectAttr "animCurveTA1432.a" "clipLibrary1.cel[0].cev[124].cevr";
connectAttr "animCurveTA1433.a" "clipLibrary1.cel[0].cev[125].cevr";
connectAttr "animCurveTU451.a" "clipLibrary1.cel[0].cev[126].cevr";
connectAttr "animCurveTA1434.a" "clipLibrary1.cel[0].cev[127].cevr";
connectAttr "animCurveTA1435.a" "clipLibrary1.cel[0].cev[128].cevr";
connectAttr "animCurveTA1436.a" "clipLibrary1.cel[0].cev[129].cevr";
connectAttr "animCurveTA1437.a" "clipLibrary1.cel[0].cev[130].cevr";
connectAttr "animCurveTA1438.a" "clipLibrary1.cel[0].cev[131].cevr";
connectAttr "animCurveTA1439.a" "clipLibrary1.cel[0].cev[132].cevr";
connectAttr "animCurveTU452.a" "clipLibrary1.cel[0].cev[133].cevr";
connectAttr "animCurveTA1440.a" "clipLibrary1.cel[0].cev[134].cevr";
connectAttr "animCurveTA1441.a" "clipLibrary1.cel[0].cev[135].cevr";
connectAttr "animCurveTA1442.a" "clipLibrary1.cel[0].cev[136].cevr";
connectAttr "animCurveTA1443.a" "clipLibrary1.cel[0].cev[137].cevr";
connectAttr "animCurveTA1444.a" "clipLibrary1.cel[0].cev[138].cevr";
connectAttr "animCurveTA1445.a" "clipLibrary1.cel[0].cev[139].cevr";
connectAttr "animCurveTA1446.a" "clipLibrary1.cel[0].cev[140].cevr";
connectAttr "animCurveTA1447.a" "clipLibrary1.cel[0].cev[141].cevr";
connectAttr "animCurveTA1448.a" "clipLibrary1.cel[0].cev[142].cevr";
connectAttr "animCurveTU453.a" "clipLibrary1.cel[0].cev[143].cevr";
connectAttr "animCurveTU454.a" "clipLibrary1.cel[0].cev[144].cevr";
connectAttr "animCurveTU455.a" "clipLibrary1.cel[0].cev[145].cevr";
connectAttr "animCurveTA1449.a" "clipLibrary1.cel[0].cev[146].cevr";
connectAttr "animCurveTA1450.a" "clipLibrary1.cel[0].cev[147].cevr";
connectAttr "animCurveTA1451.a" "clipLibrary1.cel[0].cev[148].cevr";
connectAttr "animCurveTL442.a" "clipLibrary1.cel[0].cev[149].cevr";
connectAttr "animCurveTL443.a" "clipLibrary1.cel[0].cev[150].cevr";
connectAttr "animCurveTL444.a" "clipLibrary1.cel[0].cev[151].cevr";
connectAttr "animCurveTA1452.a" "clipLibrary1.cel[0].cev[152].cevr";
connectAttr "animCurveTA1453.a" "clipLibrary1.cel[0].cev[153].cevr";
connectAttr "animCurveTA1454.a" "clipLibrary1.cel[0].cev[154].cevr";
connectAttr "animCurveTU456.a" "clipLibrary1.cel[0].cev[155].cevr";
connectAttr "animCurveTA1455.a" "clipLibrary1.cel[0].cev[156].cevr";
connectAttr "animCurveTA1456.a" "clipLibrary1.cel[0].cev[157].cevr";
connectAttr "animCurveTA1457.a" "clipLibrary1.cel[0].cev[158].cevr";
connectAttr "animCurveTA1458.a" "clipLibrary1.cel[0].cev[159].cevr";
connectAttr "animCurveTA1459.a" "clipLibrary1.cel[0].cev[160].cevr";
connectAttr "animCurveTA1460.a" "clipLibrary1.cel[0].cev[161].cevr";
connectAttr "animCurveTA1461.a" "clipLibrary1.cel[0].cev[162].cevr";
connectAttr "animCurveTA1462.a" "clipLibrary1.cel[0].cev[163].cevr";
connectAttr "animCurveTA1463.a" "clipLibrary1.cel[0].cev[164].cevr";
connectAttr "animCurveTU457.a" "clipLibrary1.cel[0].cev[165].cevr";
connectAttr "animCurveTA1464.a" "clipLibrary1.cel[0].cev[166].cevr";
connectAttr "animCurveTA1465.a" "clipLibrary1.cel[0].cev[167].cevr";
connectAttr "animCurveTA1466.a" "clipLibrary1.cel[0].cev[168].cevr";
connectAttr "animCurveTU458.a" "clipLibrary1.cel[0].cev[169].cevr";
connectAttr "animCurveTU459.a" "clipLibrary1.cel[0].cev[170].cevr";
connectAttr "animCurveTU460.a" "clipLibrary1.cel[0].cev[171].cevr";
connectAttr "animCurveTA1467.a" "clipLibrary1.cel[0].cev[172].cevr";
connectAttr "animCurveTA1468.a" "clipLibrary1.cel[0].cev[173].cevr";
connectAttr "animCurveTA1469.a" "clipLibrary1.cel[0].cev[174].cevr";
connectAttr "animCurveTL445.a" "clipLibrary1.cel[0].cev[175].cevr";
connectAttr "animCurveTL446.a" "clipLibrary1.cel[0].cev[176].cevr";
connectAttr "animCurveTL447.a" "clipLibrary1.cel[0].cev[177].cevr";
connectAttr "animCurveTA1470.a" "clipLibrary1.cel[0].cev[178].cevr";
connectAttr "animCurveTA1471.a" "clipLibrary1.cel[0].cev[179].cevr";
connectAttr "animCurveTA1472.a" "clipLibrary1.cel[0].cev[180].cevr";
connectAttr "animCurveTU461.a" "clipLibrary1.cel[0].cev[181].cevr";
connectAttr "animCurveTA1473.a" "clipLibrary1.cel[0].cev[182].cevr";
connectAttr "animCurveTA1474.a" "clipLibrary1.cel[0].cev[183].cevr";
connectAttr "animCurveTA1475.a" "clipLibrary1.cel[0].cev[184].cevr";
connectAttr "animCurveTA1476.a" "clipLibrary1.cel[0].cev[185].cevr";
connectAttr "animCurveTA1477.a" "clipLibrary1.cel[0].cev[186].cevr";
connectAttr "animCurveTA1478.a" "clipLibrary1.cel[0].cev[187].cevr";
connectAttr "animCurveTA1479.a" "clipLibrary1.cel[0].cev[188].cevr";
connectAttr "animCurveTA1480.a" "clipLibrary1.cel[0].cev[189].cevr";
connectAttr "animCurveTA1481.a" "clipLibrary1.cel[0].cev[190].cevr";
connectAttr "animCurveTA1482.a" "clipLibrary1.cel[0].cev[191].cevr";
connectAttr "animCurveTA1483.a" "clipLibrary1.cel[0].cev[192].cevr";
connectAttr "animCurveTA1484.a" "clipLibrary1.cel[0].cev[193].cevr";
connectAttr "animCurveTA1485.a" "clipLibrary1.cel[0].cev[194].cevr";
connectAttr "animCurveTA1486.a" "clipLibrary1.cel[0].cev[195].cevr";
connectAttr "animCurveTA1487.a" "clipLibrary1.cel[0].cev[196].cevr";
connectAttr "animCurveTU462.a" "clipLibrary1.cel[0].cev[197].cevr";
connectAttr "animCurveTA1488.a" "clipLibrary1.cel[0].cev[198].cevr";
connectAttr "animCurveTA1489.a" "clipLibrary1.cel[0].cev[199].cevr";
connectAttr "animCurveTA1490.a" "clipLibrary1.cel[0].cev[200].cevr";
connectAttr "animCurveTU463.a" "clipLibrary1.cel[0].cev[201].cevr";
connectAttr "animCurveTA1491.a" "clipLibrary1.cel[0].cev[202].cevr";
connectAttr "animCurveTA1492.a" "clipLibrary1.cel[0].cev[203].cevr";
connectAttr "animCurveTA1493.a" "clipLibrary1.cel[0].cev[204].cevr";
connectAttr "animCurveTA1494.a" "clipLibrary1.cel[0].cev[205].cevr";
connectAttr "animCurveTA1495.a" "clipLibrary1.cel[0].cev[206].cevr";
connectAttr "animCurveTA1496.a" "clipLibrary1.cel[0].cev[207].cevr";
connectAttr "animCurveTA1497.a" "clipLibrary1.cel[0].cev[208].cevr";
connectAttr "animCurveTA1498.a" "clipLibrary1.cel[0].cev[209].cevr";
connectAttr "animCurveTA1499.a" "clipLibrary1.cel[0].cev[210].cevr";
connectAttr "animCurveTL448.a" "clipLibrary1.cel[0].cev[211].cevr";
connectAttr "animCurveTL449.a" "clipLibrary1.cel[0].cev[212].cevr";
connectAttr "animCurveTL450.a" "clipLibrary1.cel[0].cev[213].cevr";
connectAttr "animCurveTU464.a" "clipLibrary1.cel[0].cev[214].cevr";
connectAttr "animCurveTU465.a" "clipLibrary1.cel[0].cev[215].cevr";
connectAttr "animCurveTA1500.a" "clipLibrary1.cel[0].cev[216].cevr";
connectAttr "animCurveTA1501.a" "clipLibrary1.cel[0].cev[217].cevr";
connectAttr "animCurveTA1502.a" "clipLibrary1.cel[0].cev[218].cevr";
connectAttr "animCurveTL451.a" "clipLibrary1.cel[0].cev[219].cevr";
connectAttr "animCurveTL452.a" "clipLibrary1.cel[0].cev[220].cevr";
connectAttr "animCurveTL453.a" "clipLibrary1.cel[0].cev[221].cevr";
connectAttr "animCurveTL454.a" "clipLibrary1.cel[0].cev[222].cevr";
connectAttr "animCurveTL455.a" "clipLibrary1.cel[0].cev[223].cevr";
connectAttr "animCurveTL456.a" "clipLibrary1.cel[0].cev[224].cevr";
connectAttr "animCurveTA1503.a" "clipLibrary1.cel[0].cev[225].cevr";
connectAttr "animCurveTA1504.a" "clipLibrary1.cel[0].cev[226].cevr";
connectAttr "animCurveTA1505.a" "clipLibrary1.cel[0].cev[227].cevr";
connectAttr "animCurveTL457.a" "clipLibrary1.cel[0].cev[228].cevr";
connectAttr "animCurveTL458.a" "clipLibrary1.cel[0].cev[229].cevr";
connectAttr "animCurveTL459.a" "clipLibrary1.cel[0].cev[230].cevr";
connectAttr "animCurveTA1506.a" "clipLibrary1.cel[0].cev[231].cevr";
connectAttr "animCurveTA1507.a" "clipLibrary1.cel[0].cev[232].cevr";
connectAttr "animCurveTA1508.a" "clipLibrary1.cel[0].cev[233].cevr";
connectAttr "animCurveTL460.a" "clipLibrary1.cel[0].cev[234].cevr";
connectAttr "animCurveTL461.a" "clipLibrary1.cel[0].cev[235].cevr";
connectAttr "animCurveTL462.a" "clipLibrary1.cel[0].cev[236].cevr";
connectAttr "animCurveTU466.a" "clipLibrary1.cel[0].cev[237].cevr";
connectAttr "animCurveTA1509.a" "clipLibrary1.cel[0].cev[238].cevr";
connectAttr "animCurveTA1510.a" "clipLibrary1.cel[0].cev[239].cevr";
connectAttr "animCurveTA1511.a" "clipLibrary1.cel[0].cev[240].cevr";
connectAttr "animCurveTL463.a" "clipLibrary1.cel[0].cev[241].cevr";
connectAttr "animCurveTL464.a" "clipLibrary1.cel[0].cev[242].cevr";
connectAttr "animCurveTL465.a" "clipLibrary1.cel[0].cev[243].cevr";
connectAttr "animCurveTA1512.a" "clipLibrary1.cel[0].cev[244].cevr";
connectAttr "animCurveTA1513.a" "clipLibrary1.cel[0].cev[245].cevr";
connectAttr "animCurveTA1514.a" "clipLibrary1.cel[0].cev[246].cevr";
connectAttr "animCurveTL466.a" "clipLibrary1.cel[0].cev[247].cevr";
connectAttr "animCurveTL467.a" "clipLibrary1.cel[0].cev[248].cevr";
connectAttr "animCurveTL468.a" "clipLibrary1.cel[0].cev[249].cevr";
connectAttr "animCurveTA1515.a" "clipLibrary1.cel[0].cev[250].cevr";
connectAttr "animCurveTA1516.a" "clipLibrary1.cel[0].cev[251].cevr";
connectAttr "animCurveTA1517.a" "clipLibrary1.cel[0].cev[252].cevr";
connectAttr "animCurveTL469.a" "clipLibrary1.cel[0].cev[253].cevr";
connectAttr "animCurveTL470.a" "clipLibrary1.cel[0].cev[254].cevr";
connectAttr "animCurveTL471.a" "clipLibrary1.cel[0].cev[255].cevr";
connectAttr "animCurveTA1518.a" "clipLibrary1.cel[0].cev[256].cevr";
connectAttr "animCurveTA1519.a" "clipLibrary1.cel[0].cev[257].cevr";
connectAttr "animCurveTA1520.a" "clipLibrary1.cel[0].cev[258].cevr";
connectAttr "animCurveTL472.a" "clipLibrary1.cel[0].cev[259].cevr";
connectAttr "animCurveTL473.a" "clipLibrary1.cel[0].cev[260].cevr";
connectAttr "animCurveTL474.a" "clipLibrary1.cel[0].cev[261].cevr";
connectAttr "animCurveTU467.a" "clipLibrary1.cel[0].cev[262].cevr";
connectAttr "animCurveTU468.a" "clipLibrary1.cel[0].cev[263].cevr";
connectAttr "animCurveTL475.a" "clipLibrary1.cel[0].cev[264].cevr";
connectAttr "animCurveTL476.a" "clipLibrary1.cel[0].cev[265].cevr";
connectAttr "animCurveTL477.a" "clipLibrary1.cel[0].cev[266].cevr";
connectAttr "animCurveTU469.a" "clipLibrary1.cel[0].cev[267].cevr";
connectAttr "animCurveTU470.a" "clipLibrary1.cel[0].cev[268].cevr";
connectAttr "animCurveTL478.a" "clipLibrary1.cel[0].cev[269].cevr";
connectAttr "animCurveTL479.a" "clipLibrary1.cel[0].cev[270].cevr";
connectAttr "animCurveTL480.a" "clipLibrary1.cel[0].cev[271].cevr";
connectAttr "animCurveTA1521.a" "clipLibrary1.cel[0].cev[272].cevr";
connectAttr "animCurveTA1522.a" "clipLibrary1.cel[0].cev[273].cevr";
connectAttr "animCurveTA1523.a" "clipLibrary1.cel[0].cev[274].cevr";
connectAttr "animCurveTA1524.a" "clipLibrary1.cel[0].cev[275].cevr";
connectAttr "animCurveTA1525.a" "clipLibrary1.cel[0].cev[276].cevr";
connectAttr "animCurveTA1526.a" "clipLibrary1.cel[0].cev[277].cevr";
connectAttr "animCurveTA1527.a" "clipLibrary1.cel[0].cev[278].cevr";
connectAttr "animCurveTA1528.a" "clipLibrary1.cel[0].cev[279].cevr";
connectAttr "animCurveTA1529.a" "clipLibrary1.cel[0].cev[280].cevr";
connectAttr "animCurveTA1530.a" "clipLibrary1.cel[0].cev[281].cevr";
connectAttr "animCurveTA1531.a" "clipLibrary1.cel[0].cev[282].cevr";
connectAttr "animCurveTA1532.a" "clipLibrary1.cel[0].cev[283].cevr";
connectAttr "animCurveTA1533.a" "clipLibrary1.cel[0].cev[284].cevr";
connectAttr "animCurveTA1534.a" "clipLibrary1.cel[0].cev[285].cevr";
connectAttr "animCurveTA1535.a" "clipLibrary1.cel[0].cev[286].cevr";
connectAttr "animCurveTU471.a" "clipLibrary1.cel[0].cev[287].cevr";
connectAttr "animCurveTU472.a" "clipLibrary1.cel[0].cev[288].cevr";
connectAttr "animCurveTU473.a" "clipLibrary1.cel[0].cev[289].cevr";
connectAttr "animCurveTA1536.a" "clipLibrary1.cel[0].cev[290].cevr";
connectAttr "animCurveTA1537.a" "clipLibrary1.cel[0].cev[291].cevr";
connectAttr "animCurveTA1538.a" "clipLibrary1.cel[0].cev[292].cevr";
connectAttr "animCurveTL481.a" "clipLibrary1.cel[0].cev[293].cevr";
connectAttr "animCurveTL482.a" "clipLibrary1.cel[0].cev[294].cevr";
connectAttr "animCurveTL483.a" "clipLibrary1.cel[0].cev[295].cevr";
connectAttr "animCurveTU474.a" "clipLibrary1.cel[0].cev[296].cevr";
connectAttr "animCurveTU475.a" "clipLibrary1.cel[0].cev[297].cevr";
connectAttr "animCurveTU476.a" "clipLibrary1.cel[0].cev[298].cevr";
connectAttr "animCurveTA1539.a" "clipLibrary1.cel[0].cev[299].cevr";
connectAttr "animCurveTA1540.a" "clipLibrary1.cel[0].cev[300].cevr";
connectAttr "animCurveTA1541.a" "clipLibrary1.cel[0].cev[301].cevr";
connectAttr "animCurveTL484.a" "clipLibrary1.cel[0].cev[302].cevr";
connectAttr "animCurveTL485.a" "clipLibrary1.cel[0].cev[303].cevr";
connectAttr "animCurveTL486.a" "clipLibrary1.cel[0].cev[304].cevr";
connectAttr "animCurveTA1542.a" "clipLibrary1.cel[0].cev[305].cevr";
connectAttr "animCurveTA1543.a" "clipLibrary1.cel[0].cev[306].cevr";
connectAttr "animCurveTA1544.a" "clipLibrary1.cel[0].cev[307].cevr";
connectAttr "animCurveTL487.a" "clipLibrary1.cel[0].cev[308].cevr";
connectAttr "animCurveTL488.a" "clipLibrary1.cel[0].cev[309].cevr";
connectAttr "animCurveTL489.a" "clipLibrary1.cel[0].cev[310].cevr";
connectAttr "animCurveTL490.a" "clipLibrary1.cel[0].cev[311].cevr";
connectAttr "animCurveTL491.a" "clipLibrary1.cel[0].cev[312].cevr";
connectAttr "animCurveTL492.a" "clipLibrary1.cel[0].cev[313].cevr";
connectAttr "animCurveTU477.a" "clipLibrary1.cel[0].cev[314].cevr";
connectAttr "animCurveTU478.a" "clipLibrary1.cel[0].cev[315].cevr";
connectAttr "animCurveTU479.a" "clipLibrary1.cel[0].cev[316].cevr";
connectAttr "animCurveTU480.a" "clipLibrary1.cel[0].cev[317].cevr";
connectAttr "animCurveTU481.a" "clipLibrary1.cel[0].cev[318].cevr";
connectAttr "animCurveTU482.a" "clipLibrary1.cel[0].cev[319].cevr";
connectAttr "animCurveTA1545.a" "clipLibrary1.cel[0].cev[320].cevr";
connectAttr "Ratcatcher_CTRL_TwistL_rotateX1.a" "clipLibrary1.cel[0].cev[321].cevr"
		;
connectAttr "Ratcatcher_CTRL_JAR_scaleZ1.a" "clipLibrary1.cel[0].cev[322].cevr";
connectAttr "Ratcatcher_CTRL_JAR_scaleY1.a" "clipLibrary1.cel[0].cev[323].cevr";
connectAttr "Ratcatcher_CTRL_JAR_scaleX1.a" "clipLibrary1.cel[0].cev[324].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of attack2A.ma
