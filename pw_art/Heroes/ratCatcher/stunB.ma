//Maya ASCII 2008 scene
//Name: stunB.ma
//Last modified: Wed, Dec 23, 2009 11:07:41 AM
//Codeset: 1251
requires maya "2008";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Complete 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200802250025-718075";
fileInfo "osv" "Microsoft Windows XP Service Pack 3 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 322 ".cel[0].cev";
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
		1 51 "CTRL_SHOULD_L.scaleZ" 0 53 "CTRL_SHOULD_L.scaleY" 0 
		54 "CTRL_SHOULD_L.scaleX" 0 55 "CTRL_SHOULD_L.rotateZ" 2 170 "CTRL_SHOULD_L.rotateY" 
		2 171 "CTRL_SHOULD_L.rotateX" 2 172 "CTRL_SHOULD_L.translateZ" 1 
		52 "CTRL_SHOULD_L.translateY" 1 53 "CTRL_SHOULD_L.translateX" 1 
		54 "CTRL_SHOULD_R.scaleZ" 0 56 "CTRL_SHOULD_R.scaleY" 0 57 "CTRL_SHOULD_R.scaleX" 
		0 58 "CTRL_SHOULD_R.rotateZ" 2 173 "CTRL_SHOULD_R.rotateY" 2 
		174 "CTRL_SHOULD_R.rotateX" 2 175 "CTRL_SHOULD_R.translateZ" 1 55 "CTRL_SHOULD_R.translateY" 
		1 56 "CTRL_SHOULD_R.translateX" 1 57 "CTRRL_BR_01.rotateZ" 2 
		176 "CTRRL_BR_01.rotateY" 2 177 "CTRRL_BR_01.rotateX" 2 178 "CTRRL_BR_02.rotateZ" 
		2 179 "CTRRL_BR_02.rotateY" 2 180 "CTRRL_BR_02.rotateX" 2 181 "CTRRL_BR_04.rotateZ" 
		2 182 "CTRRL_BR_04.rotateY" 2 183 "CTRRL_BR_04.rotateX" 2 184 "CTRRL_FEATHER.rotateZ" 
		2 185 "CTRRL_FEATHER.rotateY" 2 186 "CTRRL_FEATHER.rotateX" 2 
		187 "CTRRL_BR_03.rotateZ" 2 188 "CTRRL_BR_03.rotateY" 2 189 "CTRRL_BR_03.rotateX" 
		2 190 "CTRL_HAT.rotateZ" 2 191 "CTRL_HAT.rotateY" 2 192 "CTRL_HAT.rotateX" 
		2 193 "CTRL_HAT.translateZ" 1 58 "CTRL_HAT.translateY" 1 59 "CTRL_HAT.translateX" 
		1 60 "CTRL_SKIRT.rotateZ" 2 194 "CTRL_SKIRT.rotateY" 2 195 "CTRL_SKIRT.rotateX" 
		2 196 "CTRL_STUFF_LAT.scaleZ" 0 59 "CTRL_STUFF_LAT.scaleY" 0 
		60 "CTRL_STUFF_LAT.scaleX" 0 61 "CTRL_STUFF.scaleZ" 0 62 "CTRL_STUFF.scaleY" 
		0 63 "CTRL_STUFF.scaleX" 0 64 "CTRL_TwistL.rotateX" 2 197 "CTRL_TwistR.rotateX" 
		2 198 "CTRL_JAR.scaleZ" 0 65 "CTRL_JAR.scaleY" 0 66 "CTRL_JAR.scaleX" 
		0 67  ;
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
createNode animClip -n "stunBSource";
	setAttr ".ihi" 0;
	setAttr -s 322 ".ac";
	setAttr ".ac[0:310]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
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
		yes yes yes yes yes yes yes yes yes no no no yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes;
	setAttr ".ac[314:324]" yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".se" 100;
	setAttr ".ci" no;
createNode animCurveTU -n "animCurveTU68";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA199";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA200";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA201";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU69";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  9 3 9 3;
	setAttr -s 5 ".kot[1:4]"  5 3 5 3;
createNode animCurveTU -n "animCurveTU70";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  9 3 9 3;
	setAttr -s 5 ".kot[1:4]"  5 3 5 3;
createNode animCurveTU -n "animCurveTU71";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 25 1 50 1 75 1 100 1;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU72";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  9 3 9 3;
	setAttr -s 5 ".kot[1:4]"  5 3 5 3;
createNode animCurveTA -n "animCurveTA202";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA203";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA204";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU73";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU74";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL61";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.042082501787981119 25 0.042082501787980675 
		50 0.042082501787980675 75 0.042082501787980675 100 0.042082501787980675;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL62";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.053443292051404856 25 -0.053443292051404856 
		50 -0.053443292051404856 75 -0.053443292051404856 100 -0.053443292051404856;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL63";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.71993951938499301 25 -0.71993951938499301 
		50 -0.71993951938499301 75 -0.71993951938499301 100 -0.71993951938499301;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA205";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA206";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA207";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA208";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 25.675870473757751 25 25.675870473757751 
		50 25.675870473757751 75 25.675870473757751 100 25.675870473757751;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA209";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -3.0739741698828946 25 -3.0739741698828946 
		50 -3.0739741698828946 75 -3.0739741698828946 100 -3.0739741698828946;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU75";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 3 25 3 50 3 75 3 100 3;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU76";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU77";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 25 1 50 1 75 1 100 1;
	setAttr -s 5 ".kit[1:4]"  9 3 9 3;
	setAttr -s 5 ".kot[1:4]"  5 3 5 3;
createNode animCurveTU -n "animCurveTU78";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA210";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 126.7431285088454 25 150.99017194134979 
		50 138.44922547221111 75 142.75753587541487 100 126.7431285088454;
	setAttr -s 5 ".kit[1:4]"  9 3 10 3;
	setAttr -s 5 ".kot[1:4]"  9 3 10 3;
createNode animCurveTA -n "animCurveTA211";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 142.70296869623189 25 142.84305970881675 
		50 152.73831333030421 75 145.13205841739776 100 142.70296869623189;
	setAttr -s 5 ".kit[0:4]"  3 1 9 9 3;
	setAttr -s 5 ".kot[0:4]"  3 1 9 9 3;
	setAttr -s 5 ".kix[1:4]"  0.99795073270797729 0.99971276521682739 
		0.99452340602874756 1;
	setAttr -s 5 ".kiy[1:4]"  0.063987374305725098 0.023963453248143196 
		-0.10451435297727585 0;
	setAttr -s 5 ".kox[1:4]"  0.99795073270797729 0.99971276521682739 
		0.99452340602874756 1;
	setAttr -s 5 ".koy[1:4]"  0.063987359404563904 0.023963453248143196 
		-0.10451435297727585 0;
createNode animCurveTA -n "animCurveTA212";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 23.860828789287218 25 26.298975190059984 
		50 26.801175313981197 75 18.722792287129845 100 23.860828789287218;
	setAttr -s 5 ".kit[3:4]"  10 9;
	setAttr -s 5 ".kot[3:4]"  10 9;
createNode animCurveTL -n "animCurveTL64";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.33559840814244318 25 -0.44310876975092828 
		50 -0.42065521519231219 75 -0.24800762654006162 100 -0.33559840814244318;
createNode animCurveTL -n "animCurveTL65";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.32552473160937945 25 -0.38511257186340692 
		50 -0.41966526561909379 75 -0.40474042378594854 100 -0.32552473160937945;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 9 9 3;
createNode animCurveTL -n "animCurveTL66";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.10276529281629167 25 -0.041771143953616786 
		50 0.034111588715668814 75 0.01947429348656772 100 -0.10276529281629167;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 9 9 3;
createNode animCurveTU -n "animCurveTU79";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA213";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -24.884454396993167;
createNode animCurveTA -n "animCurveTA214";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -43.339475474578435;
createNode animCurveTA -n "animCurveTA215";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 11.606559612787883;
createNode animCurveTU -n "animCurveTU80";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  9 3 9 3;
	setAttr -s 5 ".kot[1:4]"  5 3 5 3;
createNode animCurveTU -n "animCurveTU81";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  9 3 9 3;
	setAttr -s 5 ".kot[1:4]"  5 3 5 3;
createNode animCurveTU -n "animCurveTU82";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 25 1 50 1 75 1 100 1;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU83";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  9 3 9 3;
	setAttr -s 5 ".kot[1:4]"  5 3 5 3;
createNode animCurveTA -n "animCurveTA216";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 3.9531091186723013 25 3.9531091186723013 
		50 3.9531091186723013 75 3.9531091186723013 100 3.9531091186723013;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA217";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.62018686761647346 25 0.62018686761647346 
		50 0.62018686761647346 75 0.62018686761647346 100 0.62018686761647346;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA218";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 5.3292188742882338 25 5.3292188742882338 
		50 5.3292188742882338 75 5.3292188742882338 100 5.3292188742882338;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU84";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU85";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL67";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.270886803809812 25 -0.270886803809812 
		50 -0.270886803809812 75 -0.270886803809812 100 -0.270886803809812;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL68";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.54307570932269766 25 -0.54307570932269766 
		50 -0.54307570932269766 75 -0.54307570932269766 100 -0.54307570932269766;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL69";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.44591504333408183 25 0.44591504333408183 
		50 0.44591504333408183 75 0.44591504333408183 100 0.44591504333408183;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA219";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -44.757110789561033;
createNode animCurveTA -n "animCurveTA220";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.10616870005340093;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA221";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -4.9406171614869088;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA222";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -27.604588158357807 25 -27.604588158357807 
		50 -27.604588158357807 75 -27.604588158357807 100 -27.604588158357807;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA223";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.70641431476594085 25 0.70641431476594085 
		50 0.70641431476594085 75 0.70641431476594085 100 0.70641431476594085;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU86";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  9 3 9 3;
	setAttr -s 5 ".kot[1:4]"  5 3 5 3;
createNode animCurveTU -n "animCurveTU87";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 3 25 3 50 3 75 3 100 3;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU88";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU89";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 25 1 50 1 75 1 100 1;
	setAttr -s 5 ".kit[1:4]"  9 3 9 3;
	setAttr -s 5 ".kot[1:4]"  5 3 5 3;
createNode animCurveTU -n "animCurveTU90";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA224";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 62.888221513301495 25 47.446575378242514 
		50 52.151018815924161 75 44.708703995505594 100 62.888221513301495;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA225";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 58.507018153278167 25 48.913972680320917 
		50 57.807448354911678 75 47.256264222117785 100 58.507018153278167;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA226";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 63.38252080745827 25 64.331345475257251 
		50 65.432039607020442 75 61.200322166851976 100 63.38252080745827;
	setAttr -s 5 ".kit[2:4]"  3 10 1;
	setAttr -s 5 ".kot[2:4]"  3 10 1;
	setAttr -s 5 ".kix[4]"  0.99945127964019775;
	setAttr -s 5 ".kiy[4]"  0.033123351633548737;
	setAttr -s 5 ".kox[4]"  0.99945133924484253;
	setAttr -s 5 ".koy[4]"  0.033123347908258438;
createNode animCurveTL -n "animCurveTL70";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.37401783182854675 25 -0.31382098297721311 
		50 -0.28075355291401272 75 -0.30251388204009211 100 -0.37401783182854675;
	setAttr -s 5 ".kit[1:4]"  9 3 9 3;
	setAttr -s 5 ".kot[1:4]"  9 3 9 3;
createNode animCurveTL -n "animCurveTL71";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.42341050063650137 25 0.50610430854427457 
		50 0.44317935292133742 75 0.39005857706645619 100 0.42341050063650137;
	setAttr -s 5 ".kit[1:4]"  10 9 10 1;
	setAttr -s 5 ".kot[1:4]"  10 9 10 1;
	setAttr -s 5 ".kix[4]"  0.99675500392913818;
	setAttr -s 5 ".kiy[4]"  0.08049561083316803;
	setAttr -s 5 ".kox[4]"  0.99675494432449341;
	setAttr -s 5 ".koy[4]"  0.080495603382587433;
createNode animCurveTL -n "animCurveTL72";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.46092578982132271 25 0.42802708794138183 
		50 0.42722051124864352 75 0.45254241066812451 100 0.46092578982132271;
	setAttr -s 5 ".kit[3:4]"  10 9;
	setAttr -s 5 ".kot[3:4]"  10 9;
createNode animCurveTU -n "animCurveTU91";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 25 1 50 1 75 1 100 1;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA227";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.1288109940741509 25 1.1288109940741509 
		50 1.1288109940741509 75 1.1288109940741509 100 1.1288109940741509;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA228";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 4.8219581414201906 25 4.8219581414201906 
		50 4.8219581414201906 75 4.8219581414201906 100 4.8219581414201906;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA229";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 28.08558650754679 25 28.08558650754679 
		50 28.08558650754679 75 28.08558650754679 100 28.08558650754679;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU92";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA230";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 68.629003384766676 25 68.629003384766676 
		50 68.629003384766676 75 68.629003384766676 100 68.629003384766676;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA231";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 5.1251585428584878 25 5.1251585428584878 
		50 5.1251585428584878 75 5.1251585428584878 100 5.1251585428584878;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA232";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.4794141658124507 25 -1.4794141658124507 
		50 -1.4794141658124507 75 -1.4794141658124507 100 -1.4794141658124507;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA233";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 2.9967431843380723 25 2.9967431843380723 
		50 2.9967431843380723 75 2.9967431843380723 100 2.9967431843380723;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA234";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 27.356153209428296 25 27.356153209428296 
		50 27.356153209428296 75 27.356153209428296 100 27.356153209428296;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA235";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 4.8891453517792058 25 4.8891453517792058 
		50 4.8891453517792058 75 4.8891453517792058 100 4.8891453517792058;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU93";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA236";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 59.032884886088816 25 59.032884886088816 
		50 59.032884886088816 75 59.032884886088816 100 59.032884886088816;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA237";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA238";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA239";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 61.945270723308987 25 61.945270723308987 
		50 61.945270723308987 75 61.945270723308987 100 61.945270723308987;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA240";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA241";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU94";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA242";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 59.032884886088816 25 59.032884886088816 
		50 59.032884886088816 75 59.032884886088816 100 59.032884886088816;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA243";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA244";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA245";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 61.945270723308987 25 61.945270723308987 
		50 61.945270723308987 75 61.945270723308987 100 61.945270723308987;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA246";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA247";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU95";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA248";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 59.032884886088816 25 59.032884886088816 
		50 59.032884886088816 75 59.032884886088816 100 59.032884886088816;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA249";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA250";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA251";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 72.878304588436421 25 72.878304588436421 
		50 72.878304588436421 75 72.878304588436421 100 72.878304588436421;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA252";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA253";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU96";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA254";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 77.67986202714836 25 77.67986202714836 
		50 77.67986202714836 75 77.67986202714836 100 77.67986202714836;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA255";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA256";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA257";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 65.952779168408995 25 65.952779168408995 
		50 65.952779168408995 75 65.952779168408995 100 65.952779168408995;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA258";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 12.091864976351665 25 12.091864976351665 
		50 12.091864976351665 75 12.091864976351665 100 12.091864976351665;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA259";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -6.5683373417752975 25 -6.5683373417752975 
		50 -6.5683373417752975 75 -6.5683373417752975 100 -6.5683373417752975;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA260";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA261";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA262";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU97";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA263";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -26.882863257800128 25 -29.438432813723626 
		50 -32.863090668864217 75 -26.882863257800128 100 -26.882863257800128;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA264";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -28.432206275992066 25 -30.652642108557824 
		50 -30.612193622993367 75 -28.432206275992066 100 -28.432206275992066;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA265";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -4.033199101892186 25 -11.156136636548757 
		50 -25.098701552448283 75 -4.033199101892186 100 -4.033199101892186;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA266";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 -3.8205125273415095 50 -3.2614305705451407 
		75 -2.6640403358143594 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA267";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 -7.9188080800106961 50 -12.737014311097418 
		75 -9.1759183741423342 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA268";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 -12.011186961660613 50 -9.8871545168513002 
		75 -12.949327318846901 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU98";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA269";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA270";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA271";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA272";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -7.6097662637136221 25 -7.6097662637136221 
		50 -7.6097662637136221 75 -7.6097662637136221 100 -7.6097662637136221;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA273";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA274";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU99";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA275";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA276";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA277";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA278";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -7.6097662637136221 25 -7.6097662637136221 
		50 -7.6097662637136221 75 -7.6097662637136221 100 -7.6097662637136221;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA279";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA280";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU100";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA281";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA282";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA283";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA284";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -7.6097662637136221 25 -7.6097662637136221 
		50 -7.6097662637136221 75 -7.6097662637136221 100 -7.6097662637136221;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA285";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA286";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU101";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA287";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA288";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA289";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA290";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -7.6097662637136221 25 -7.6097662637136221 
		50 -7.6097662637136221 75 -7.6097662637136221 100 -7.6097662637136221;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA291";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA292";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA293";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA294";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA295";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU102";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  9 3 9 3;
	setAttr -s 5 ".kot[1:4]"  5 3 5 3;
createNode animCurveTU -n "animCurveTU103";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  9 3 9 3;
	setAttr -s 5 ".kot[1:4]"  5 3 5 3;
createNode animCurveTU -n "animCurveTU104";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 25 1 50 1 75 1 100 1;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA296";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -10.173354040024311 25 -10.173354040024311 
		50 -10.173354040024311 75 -10.173354040024311 100 -10.173354040024311;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA297";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA298";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL73";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL74";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.643246524321337 25 0.643246524321337 
		50 0.643246524321337 75 0.643246524321337 100 0.643246524321337;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL75";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.10481400598920043 25 0.10481400598920043 
		50 0.10481400598920043 75 0.10481400598920043 100 0.10481400598920043;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA299";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA300";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA301";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU105";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA302";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA303";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA304";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA305";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA306";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA307";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA308";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA309";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA310";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU106";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 25 1 50 1 75 1 100 1;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA311";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 40.718223104721211 25 40.718223104721211 
		50 40.718223104721211 75 40.718223104721211 100 40.718223104721211;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA312";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -38.301705751263519 25 -38.301705751263519 
		50 -38.301705751263519 75 -38.301705751263519 100 -38.301705751263519;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA313";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 21.733945627788874 25 21.733945627788874 
		50 21.733945627788874 75 21.733945627788874 100 21.733945627788874;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU107";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  9 3 9 3;
	setAttr -s 5 ".kot[1:4]"  5 3 5 3;
createNode animCurveTU -n "animCurveTU108";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  9 3 9 3;
	setAttr -s 5 ".kot[1:4]"  5 3 5 3;
createNode animCurveTU -n "animCurveTU109";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 25 1 50 1 75 1 100 1;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA314";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 17.962181958626559 25 17.962181958626559 
		50 17.962181958626559 75 17.962181958626559 100 17.962181958626559;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA315";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA316";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL76";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL77";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.64789329560123088 25 -0.64789329560123088 
		50 -0.64789329560123088 75 -0.64789329560123088 100 -0.64789329560123088;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL78";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.07395615046270454 25 -0.07395615046270454 
		50 -0.07395615046270454 75 -0.07395615046270454 100 -0.07395615046270454;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA317";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA318";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA319";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "animCurveTU110";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA320";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA321";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA322";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA323";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA324";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA325";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA326";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA327";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA328";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA329";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.90240726097224566 25 -12.728992833635141 
		50 -0.88107118029980203 75 7.0327666281639889 100 -0.90240726097224566;
	setAttr -s 5 ".kit[1:4]"  10 9 10 9;
	setAttr -s 5 ".kot[1:4]"  10 9 10 9;
createNode animCurveTA -n "animCurveTA330";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -2.8528600574964948 25 -6.8637336076332138 
		50 -3.0266038574224452 75 2.2467293418770882 100 -2.8528600574964948;
	setAttr -s 5 ".kit[1:4]"  10 9 10 9;
	setAttr -s 5 ".kot[1:4]"  10 9 10 9;
createNode animCurveTA -n "animCurveTA331";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 34.074130559466894 25 29.788428103224479 
		50 31.338135056749582 75 35.258149054427491 100 34.074130559466894;
	setAttr -s 5 ".kit[1:4]"  1 9 9 1;
	setAttr -s 5 ".kot[1:4]"  1 9 9 1;
	setAttr -s 5 ".kix[1:4]"  0.99958264827728271 0.99836355447769165 
		0.99958986043930054 0.99701660871505737;
	setAttr -s 5 ".kiy[1:4]"  -0.028889738023281097 0.05718505010008812 
		0.028639527037739754 -0.077187366783618927;
	setAttr -s 5 ".kox[1:4]"  0.99958264827728271 0.99836355447769165 
		0.99958986043930054 0.99701660871505737;
	setAttr -s 5 ".koy[1:4]"  -0.028889739885926247 0.05718505010008812 
		0.028639527037739754 -0.077187381684780121;
createNode animCurveTA -n "animCurveTA332";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -4.0865779949808214 25 -4.0865779949808214 
		50 -4.0865779949808214 75 -4.0865779949808214 100 -4.0865779949808214;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA333";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -10.471027640707172 25 -10.471027640707172 
		50 -10.471027640707172 75 -10.471027640707172 100 -10.471027640707172;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA334";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.7475532445702493 25 -1.7475532445702493 
		50 -1.7475532445702493 75 -1.7475532445702493 100 -1.7475532445702493;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU111";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 25 1 50 1 75 1 100 1;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA335";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 29.589202657086762 25 23.295089984006594 
		50 12.767580912390809 75 17.131204167699153 100 29.589202657086762;
	setAttr -s 5 ".kit[1:4]"  10 9 10 9;
	setAttr -s 5 ".kot[1:4]"  10 9 10 9;
createNode animCurveTA -n "animCurveTA336";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 15.418038832921921 25 4.4251531685960126 
		50 -11.313464830430719 75 -5.7900918249325422 100 15.418038832921921;
	setAttr -s 5 ".kit[0:4]"  3 10 9 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 9 10 3;
createNode animCurveTA -n "animCurveTA337";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 34.226524929581736 25 47.503713703351544 
		50 42.50476888186391 75 24.91156343804537 100 34.226524929581736;
	setAttr -s 5 ".kit[1:4]"  10 9 10 9;
	setAttr -s 5 ".kot[1:4]"  10 9 10 9;
createNode animCurveTU -n "animCurveTU112";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA338";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 -0.5719555547516697 50 0 75 0 100 
		0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA339";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 2.9215973577805432 50 0 75 0 100 
		0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA340";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 -1.0456463516613121 50 0 75 0 100 
		0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA341";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -17.821366541589882 25 -17.821366541589882 
		50 -17.821366541589882 75 -17.821366541589882 100 -17.821366541589882;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA342";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -12.005893876475762 25 -12.005893876475762 
		50 -12.005893876475762 75 -12.005893876475762 100 -12.005893876475762;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA343";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 9.1378572146953019 25 9.1378572146953019 
		50 9.1378572146953019 75 9.1378572146953019 100 9.1378572146953019;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA344";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -92.341385901593654 18 -54.350945011424059 
		36 -135.53501363381025 50 -98.88706724570028 65 -131.06880521376894 84 -58.80578648526469 
		100 -92.341385901593654;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA345";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -70.881160922006117 18 -61.222107013660384 
		36 -65.756025814771334 50 -70.135718712703181 65 -73.45321114053057 84 -55.189206123752847 
		100 -70.881160922006117;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA346";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 226.62655536292792 18 168.86328953299156 
		36 267.50245191263156 50 208.86607852440022 65 258.13496254334541 84 174.72221966908944 
		100 226.62655536292792;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL79";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 100 0;
createNode animCurveTL -n "animCurveTL80";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 100 0;
createNode animCurveTL -n "animCurveTL81";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 100 0;
createNode animCurveTU -n "animCurveTU113";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 2 25 2 50 2 75 2 100 2;
	setAttr -s 5 ".kit[1:4]"  9 3 9 3;
	setAttr -s 5 ".kot[1:4]"  5 3 5 3;
createNode animCurveTU -n "animCurveTU114";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  9 3 9 3;
	setAttr -s 5 ".kot[1:4]"  5 3 5 3;
createNode animCurveTA -n "animCurveTA347";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -24.093441664171177 25 -24.093441664171177 
		50 -24.093441664171177 75 -24.093441664171177 100 -24.093441664171177;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA348";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 49.48465546224881 25 49.48465546224881 
		50 49.48465546224881 75 49.48465546224881 100 49.48465546224881;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA349";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 58.801792680015588 25 58.801792680015588 
		50 58.801792680015588 75 58.801792680015588 100 58.801792680015588;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL82";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.2755255474500937 25 -1.2755255474500937 
		50 -1.2755255474500937 75 -1.2755255474500937 100 -1.2755255474500937;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL83";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.4392043230118035 25 -1.4392043230118035 
		50 -1.4392043230118035 75 -1.4392043230118035 100 -1.4392043230118035;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL84";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -2.1802956492995231 25 -2.1802956492995231 
		50 -2.1802956492995231 75 -2.1802956492995231 100 -2.1802956492995231;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL85";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL86";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL87";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA350";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.66311859869759693 25 -4.6998394547726887 
		50 -0.66311859869759693 75 -4.9294664480495056 100 -0.66311859869759693;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA351";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 7.2616576080590134 25 21.445771977116568 
		50 7.2616576080590134 75 13.583640881601418 100 7.2616576080590134;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA352";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 12.693011860549026 25 16.132739323653965 
		50 12.693011860549026 75 13.458664663617329 100 12.693011860549026;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL88";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL89";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL90";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA353";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA354";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA355";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL91";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL92";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL93";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU115";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  9 3 9 3;
	setAttr -s 5 ".kot[1:4]"  5 3 5 3;
createNode animCurveTA -n "animCurveTA356";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -5.1107219305963252 25 -5.1107219305963252 
		50 -5.1107219305963252 75 -5.1107219305963252 100 -5.1107219305963252;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA357";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 8.2811672786141717 25 8.2811672786141717 
		50 8.2811672786141717 75 8.2811672786141717 100 8.2811672786141717;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA358";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.92645454014921158 25 -0.92645454014921158 
		50 -0.92645454014921158 75 -0.92645454014921158 100 -0.92645454014921158;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL94";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.046856395845859107 25 -0.046856395845859107 
		50 -0.046856395845859107 75 -0.046856395845859107 100 -0.046856395845859107;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL95";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.023348763690700665 25 -0.023348763690700665 
		50 -0.023348763690700665 75 -0.023348763690700665 100 -0.023348763690700665;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL96";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.13506113021862395 25 -0.13506113021862395 
		50 -0.13506113021862395 75 -0.13506113021862395 100 -0.13506113021862395;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA359";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.6266160090263075 25 -1.6266160090263075 
		50 -1.6266160090263075 75 -1.6266160090263075 100 -1.6266160090263075;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA360";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 2.8499857758927387 25 2.8499857758927387 
		50 2.8499857758927387 75 2.8499857758927387 100 2.8499857758927387;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA361";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -25.210898828531619 25 -18.124521026589662 
		50 -25.210898828531619 75 -18.806839926378512 100 -25.210898828531619;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL97";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.011193700785458628 25 -0.011193700785458628 
		50 -0.011193700785458628 75 -0.011193700785458628 100 -0.011193700785458628;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL98";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.020021267836214246 25 -0.020021267836214246 
		50 -0.020021267836214246 75 -0.020021267836214246 100 -0.020021267836214246;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL99";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.032441787830836878 25 0.032441787830836878 
		50 0.032441787830836878 75 0.032441787830836878 100 0.032441787830836878;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA362";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA363";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA364";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL100";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL101";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL102";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA365";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -17.127161773748963 25 -20.960895351104899 
		50 -15.688774854333316 75 -11.710311530286921 100 -17.127161773748963;
	setAttr -s 5 ".kit[0:4]"  2 10 9 10 2;
	setAttr -s 5 ".kot[0:4]"  2 10 9 10 2;
createNode animCurveTA -n "animCurveTA366";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.16287824683821922 25 -5.313650307754294 
		50 3.4969600010409505 75 9.8333268294880973 100 0.16287824683821922;
	setAttr -s 5 ".kit[0:4]"  2 10 9 10 2;
	setAttr -s 5 ".kot[0:4]"  2 10 9 10 2;
createNode animCurveTA -n "animCurveTA367";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 27.628709011506228 25 22.199623638519689 
		50 13.878609840433381 75 21.262580198876837 100 27.628709011506228;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL103";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.18868131369562219 25 -0.20989449130940613 
		50 -0.23110766892319007 75 -0.20989448903347901 100 -0.18868131369562219;
	setAttr -s 5 ".kit[1:4]"  9 3 9 3;
	setAttr -s 5 ".kot[1:4]"  9 3 9 3;
createNode animCurveTL -n "animCurveTL104";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.23059098815955009 25 0.27139041849255907 
		50 0.31218984882556805 75 0.271390414115255 100 0.23059098815955009;
	setAttr -s 5 ".kit[1:4]"  9 3 9 3;
	setAttr -s 5 ".kot[1:4]"  9 3 9 3;
createNode animCurveTL -n "animCurveTL105";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.049918713102953649 25 -0.025400361938424931 
		50 0.052311809606694293 75 0.14795728177666023 100 0.049918713102953649;
	setAttr -s 5 ".kit[0:4]"  2 10 9 10 2;
	setAttr -s 5 ".kot[0:4]"  2 10 9 10 2;
createNode animCurveTU -n "animCurveTU116";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  9 3 9 3;
	setAttr -s 5 ".kot[1:4]"  5 3 5 3;
createNode animCurveTU -n "animCurveTU117";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.084155571970393403 25 0.084155571970393403 
		50 0.084155571970393403 75 0.084155571970393403 100 0.084155571970393403;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL106";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.067207227343123899 25 0.067207227343123899 
		50 0.067207227343123899 75 0.067207227343123899 100 0.067207227343123899;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL107";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.20472824713235571 25 -0.20472824713235571 
		50 -0.20472824713235571 75 -0.20472824713235571 100 -0.20472824713235571;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL108";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.20941646546924442 25 0.20941646546924442 
		50 0.20941646546924442 75 0.20941646546924442 100 0.20941646546924442;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU118";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  9 3 9 3;
	setAttr -s 5 ".kot[1:4]"  5 3 5 3;
createNode animCurveTU -n "animCurveTU119";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.084155864375844894 25 0.084155864375844894 
		50 0.084155864375844894 75 0.084155864375844894 100 0.084155864375844894;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL109";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL110";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.40088449385078673 25 -0.40088449385078673 
		50 -0.40088449385078673 75 -0.40088449385078673 100 -0.40088449385078673;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL111";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.69609418843799409 25 -0.69609418843799409 
		50 -0.69609418843799409 75 -0.69609418843799409 100 -0.69609418843799409;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU120";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 100 1;
createNode animCurveTU -n "animCurveTU121";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 100 1;
createNode animCurveTU -n "animCurveTU122";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 100 1;
createNode animCurveTA -n "animCurveTA383";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 21.02011414788603 50 4.8246884527610527 
		100 21.02011414788603;
createNode animCurveTA -n "animCurveTA384";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -2.0161111706699346 50 -6.4406156243960853 
		100 -2.0161111706699346;
createNode animCurveTA -n "animCurveTA385";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -1.8351699297057871 50 -0.13286974308398039 
		100 -1.8351699297057871;
createNode animCurveTL -n "animCurveTL112";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 100 0;
createNode animCurveTL -n "animCurveTL113";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 100 0;
createNode animCurveTL -n "animCurveTL114";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 100 0;
createNode animCurveTU -n "animCurveTU123";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 100 1;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTU -n "animCurveTU124";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 100 1;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTU -n "animCurveTU125";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 100 1;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA386";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -34.21913058718718 100 -34.21913058718718;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA387";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 16.016981128258138 100 16.016981128258138;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA388";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -5.7155407998690091 100 -5.7155407998690091;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTL -n "animCurveTL115";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 100 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTL -n "animCurveTL116";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 100 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTL -n "animCurveTL117";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 100 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA368";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA369";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA370";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA371";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA372";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA373";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA380";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA381";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA382";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA377";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -18.592620239620459 25 -25.300277898076271 
		50 -18.592620239620459 75 -9.7304381918991734 100 -18.592620239620459;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA378";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -4.0495369920864128 25 3.1573161404952779 
		50 -4.0495369920864128 75 -10.072994651020446 100 -4.0495369920864128;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA379";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -24.718935474963271 25 -25.47239688864267 
		50 -24.718935474963271 75 -28.249683123950312 100 -24.718935474963271;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA374";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA375";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA376";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA389";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA390";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA391";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 7.2644697342894906 25 7.2644697342894906 
		50 7.2644697342894906 75 7.2644697342894906 100 7.2644697342894906;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL118";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL119";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTL -n "animCurveTL120";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU129";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 100 1;
createNode animCurveTU -n "animCurveTU130";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 100 1;
createNode animCurveTU -n "animCurveTU131";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 100 1;
createNode animCurveTU -n "animCurveTU126";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 25 1 50 1 75 1 100 1;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU127";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 25 1 50 1 75 1 100 1;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU128";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 25 1 50 1 75 1 100 1;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA393";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTA -n "animCurveTA392";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 25 0 50 0 75 0 100 0;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU132";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 25 1 50 1 75 1 100 1;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU133";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 25 1 50 1 75 1 100 1;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
createNode animCurveTU -n "animCurveTU134";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 25 1 50 1 75 1 100 1;
	setAttr -s 5 ".kit[1:4]"  10 3 10 3;
	setAttr -s 5 ".kot[1:4]"  10 3 10 3;
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
	setAttr -s 24 ".gn";
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
select -ne :defaultResolution;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -av ".w";
	setAttr -av ".h";
	setAttr ".pa" 1;
	setAttr -k on ".al";
	setAttr -av ".dar";
	setAttr -k on ".off";
	setAttr -k on ".fld";
	setAttr -k on ".zsl";
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
connectAttr "stunBSource.cl" "clipLibrary1.sc[0]";
connectAttr "animCurveTU68.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "animCurveTA199.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "animCurveTA200.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "animCurveTA201.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "animCurveTU69.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "animCurveTU70.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "animCurveTU71.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "animCurveTU72.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "animCurveTA202.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "animCurveTA203.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "animCurveTA204.a" "clipLibrary1.cel[0].cev[10].cevr";
connectAttr "animCurveTU73.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "animCurveTU74.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "animCurveTL61.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "animCurveTL62.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "animCurveTL63.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "animCurveTA205.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "animCurveTA206.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "animCurveTA207.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "animCurveTA208.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "animCurveTA209.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "animCurveTU75.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "animCurveTU76.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "animCurveTU77.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "animCurveTU78.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "animCurveTA210.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "animCurveTA211.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "animCurveTA212.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "animCurveTL64.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "animCurveTL65.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "animCurveTL66.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "animCurveTU79.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "animCurveTA213.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "animCurveTA214.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "animCurveTA215.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "animCurveTU80.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "animCurveTU81.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "animCurveTU82.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "animCurveTU83.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "animCurveTA216.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "animCurveTA217.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "animCurveTA218.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "animCurveTU84.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "animCurveTU85.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "animCurveTL67.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "animCurveTL68.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "animCurveTL69.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "animCurveTA219.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "animCurveTA220.a" "clipLibrary1.cel[0].cev[48].cevr";
connectAttr "animCurveTA221.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "animCurveTA222.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "animCurveTA223.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "animCurveTU86.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "animCurveTU87.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "animCurveTU88.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "animCurveTU89.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "animCurveTU90.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "animCurveTA224.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "animCurveTA225.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "animCurveTA226.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "animCurveTL70.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "animCurveTL71.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "animCurveTL72.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "animCurveTU91.a" "clipLibrary1.cel[0].cev[63].cevr";
connectAttr "animCurveTA227.a" "clipLibrary1.cel[0].cev[64].cevr";
connectAttr "animCurveTA228.a" "clipLibrary1.cel[0].cev[65].cevr";
connectAttr "animCurveTA229.a" "clipLibrary1.cel[0].cev[66].cevr";
connectAttr "animCurveTU92.a" "clipLibrary1.cel[0].cev[67].cevr";
connectAttr "animCurveTA230.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "animCurveTA231.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "animCurveTA232.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "animCurveTA233.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "animCurveTA234.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "animCurveTA235.a" "clipLibrary1.cel[0].cev[73].cevr";
connectAttr "animCurveTU93.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "animCurveTA236.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "animCurveTA237.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "animCurveTA238.a" "clipLibrary1.cel[0].cev[77].cevr";
connectAttr "animCurveTA239.a" "clipLibrary1.cel[0].cev[78].cevr";
connectAttr "animCurveTA240.a" "clipLibrary1.cel[0].cev[79].cevr";
connectAttr "animCurveTA241.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "animCurveTU94.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "animCurveTA242.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "animCurveTA243.a" "clipLibrary1.cel[0].cev[83].cevr";
connectAttr "animCurveTA244.a" "clipLibrary1.cel[0].cev[84].cevr";
connectAttr "animCurveTA245.a" "clipLibrary1.cel[0].cev[85].cevr";
connectAttr "animCurveTA246.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "animCurveTA247.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "animCurveTU95.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "animCurveTA248.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr "animCurveTA249.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "animCurveTA250.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "animCurveTA251.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "animCurveTA252.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "animCurveTA253.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "animCurveTU96.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "animCurveTA254.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "animCurveTA255.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "animCurveTA256.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "animCurveTA257.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "animCurveTA258.a" "clipLibrary1.cel[0].cev[100].cevr";
connectAttr "animCurveTA259.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "animCurveTA260.a" "clipLibrary1.cel[0].cev[102].cevr";
connectAttr "animCurveTA261.a" "clipLibrary1.cel[0].cev[103].cevr";
connectAttr "animCurveTA262.a" "clipLibrary1.cel[0].cev[104].cevr";
connectAttr "animCurveTU97.a" "clipLibrary1.cel[0].cev[105].cevr";
connectAttr "animCurveTA263.a" "clipLibrary1.cel[0].cev[106].cevr";
connectAttr "animCurveTA264.a" "clipLibrary1.cel[0].cev[107].cevr";
connectAttr "animCurveTA265.a" "clipLibrary1.cel[0].cev[108].cevr";
connectAttr "animCurveTA266.a" "clipLibrary1.cel[0].cev[109].cevr";
connectAttr "animCurveTA267.a" "clipLibrary1.cel[0].cev[110].cevr";
connectAttr "animCurveTA268.a" "clipLibrary1.cel[0].cev[111].cevr";
connectAttr "animCurveTU98.a" "clipLibrary1.cel[0].cev[112].cevr";
connectAttr "animCurveTA269.a" "clipLibrary1.cel[0].cev[113].cevr";
connectAttr "animCurveTA270.a" "clipLibrary1.cel[0].cev[114].cevr";
connectAttr "animCurveTA271.a" "clipLibrary1.cel[0].cev[115].cevr";
connectAttr "animCurveTA272.a" "clipLibrary1.cel[0].cev[116].cevr";
connectAttr "animCurveTA273.a" "clipLibrary1.cel[0].cev[117].cevr";
connectAttr "animCurveTA274.a" "clipLibrary1.cel[0].cev[118].cevr";
connectAttr "animCurveTU99.a" "clipLibrary1.cel[0].cev[119].cevr";
connectAttr "animCurveTA275.a" "clipLibrary1.cel[0].cev[120].cevr";
connectAttr "animCurveTA276.a" "clipLibrary1.cel[0].cev[121].cevr";
connectAttr "animCurveTA277.a" "clipLibrary1.cel[0].cev[122].cevr";
connectAttr "animCurveTA278.a" "clipLibrary1.cel[0].cev[123].cevr";
connectAttr "animCurveTA279.a" "clipLibrary1.cel[0].cev[124].cevr";
connectAttr "animCurveTA280.a" "clipLibrary1.cel[0].cev[125].cevr";
connectAttr "animCurveTU100.a" "clipLibrary1.cel[0].cev[126].cevr";
connectAttr "animCurveTA281.a" "clipLibrary1.cel[0].cev[127].cevr";
connectAttr "animCurveTA282.a" "clipLibrary1.cel[0].cev[128].cevr";
connectAttr "animCurveTA283.a" "clipLibrary1.cel[0].cev[129].cevr";
connectAttr "animCurveTA284.a" "clipLibrary1.cel[0].cev[130].cevr";
connectAttr "animCurveTA285.a" "clipLibrary1.cel[0].cev[131].cevr";
connectAttr "animCurveTA286.a" "clipLibrary1.cel[0].cev[132].cevr";
connectAttr "animCurveTU101.a" "clipLibrary1.cel[0].cev[133].cevr";
connectAttr "animCurveTA287.a" "clipLibrary1.cel[0].cev[134].cevr";
connectAttr "animCurveTA288.a" "clipLibrary1.cel[0].cev[135].cevr";
connectAttr "animCurveTA289.a" "clipLibrary1.cel[0].cev[136].cevr";
connectAttr "animCurveTA290.a" "clipLibrary1.cel[0].cev[137].cevr";
connectAttr "animCurveTA291.a" "clipLibrary1.cel[0].cev[138].cevr";
connectAttr "animCurveTA292.a" "clipLibrary1.cel[0].cev[139].cevr";
connectAttr "animCurveTA293.a" "clipLibrary1.cel[0].cev[140].cevr";
connectAttr "animCurveTA294.a" "clipLibrary1.cel[0].cev[141].cevr";
connectAttr "animCurveTA295.a" "clipLibrary1.cel[0].cev[142].cevr";
connectAttr "animCurveTU102.a" "clipLibrary1.cel[0].cev[143].cevr";
connectAttr "animCurveTU103.a" "clipLibrary1.cel[0].cev[144].cevr";
connectAttr "animCurveTU104.a" "clipLibrary1.cel[0].cev[145].cevr";
connectAttr "animCurveTA296.a" "clipLibrary1.cel[0].cev[146].cevr";
connectAttr "animCurveTA297.a" "clipLibrary1.cel[0].cev[147].cevr";
connectAttr "animCurveTA298.a" "clipLibrary1.cel[0].cev[148].cevr";
connectAttr "animCurveTL73.a" "clipLibrary1.cel[0].cev[149].cevr";
connectAttr "animCurveTL74.a" "clipLibrary1.cel[0].cev[150].cevr";
connectAttr "animCurveTL75.a" "clipLibrary1.cel[0].cev[151].cevr";
connectAttr "animCurveTA299.a" "clipLibrary1.cel[0].cev[152].cevr";
connectAttr "animCurveTA300.a" "clipLibrary1.cel[0].cev[153].cevr";
connectAttr "animCurveTA301.a" "clipLibrary1.cel[0].cev[154].cevr";
connectAttr "animCurveTU105.a" "clipLibrary1.cel[0].cev[155].cevr";
connectAttr "animCurveTA302.a" "clipLibrary1.cel[0].cev[156].cevr";
connectAttr "animCurveTA303.a" "clipLibrary1.cel[0].cev[157].cevr";
connectAttr "animCurveTA304.a" "clipLibrary1.cel[0].cev[158].cevr";
connectAttr "animCurveTA305.a" "clipLibrary1.cel[0].cev[159].cevr";
connectAttr "animCurveTA306.a" "clipLibrary1.cel[0].cev[160].cevr";
connectAttr "animCurveTA307.a" "clipLibrary1.cel[0].cev[161].cevr";
connectAttr "animCurveTA308.a" "clipLibrary1.cel[0].cev[162].cevr";
connectAttr "animCurveTA309.a" "clipLibrary1.cel[0].cev[163].cevr";
connectAttr "animCurveTA310.a" "clipLibrary1.cel[0].cev[164].cevr";
connectAttr "animCurveTU106.a" "clipLibrary1.cel[0].cev[165].cevr";
connectAttr "animCurveTA311.a" "clipLibrary1.cel[0].cev[166].cevr";
connectAttr "animCurveTA312.a" "clipLibrary1.cel[0].cev[167].cevr";
connectAttr "animCurveTA313.a" "clipLibrary1.cel[0].cev[168].cevr";
connectAttr "animCurveTU107.a" "clipLibrary1.cel[0].cev[169].cevr";
connectAttr "animCurveTU108.a" "clipLibrary1.cel[0].cev[170].cevr";
connectAttr "animCurveTU109.a" "clipLibrary1.cel[0].cev[171].cevr";
connectAttr "animCurveTA314.a" "clipLibrary1.cel[0].cev[172].cevr";
connectAttr "animCurveTA315.a" "clipLibrary1.cel[0].cev[173].cevr";
connectAttr "animCurveTA316.a" "clipLibrary1.cel[0].cev[174].cevr";
connectAttr "animCurveTL76.a" "clipLibrary1.cel[0].cev[175].cevr";
connectAttr "animCurveTL77.a" "clipLibrary1.cel[0].cev[176].cevr";
connectAttr "animCurveTL78.a" "clipLibrary1.cel[0].cev[177].cevr";
connectAttr "animCurveTA317.a" "clipLibrary1.cel[0].cev[178].cevr";
connectAttr "animCurveTA318.a" "clipLibrary1.cel[0].cev[179].cevr";
connectAttr "animCurveTA319.a" "clipLibrary1.cel[0].cev[180].cevr";
connectAttr "animCurveTU110.a" "clipLibrary1.cel[0].cev[181].cevr";
connectAttr "animCurveTA320.a" "clipLibrary1.cel[0].cev[182].cevr";
connectAttr "animCurveTA321.a" "clipLibrary1.cel[0].cev[183].cevr";
connectAttr "animCurveTA322.a" "clipLibrary1.cel[0].cev[184].cevr";
connectAttr "animCurveTA323.a" "clipLibrary1.cel[0].cev[185].cevr";
connectAttr "animCurveTA324.a" "clipLibrary1.cel[0].cev[186].cevr";
connectAttr "animCurveTA325.a" "clipLibrary1.cel[0].cev[187].cevr";
connectAttr "animCurveTA326.a" "clipLibrary1.cel[0].cev[188].cevr";
connectAttr "animCurveTA327.a" "clipLibrary1.cel[0].cev[189].cevr";
connectAttr "animCurveTA328.a" "clipLibrary1.cel[0].cev[190].cevr";
connectAttr "animCurveTA329.a" "clipLibrary1.cel[0].cev[191].cevr";
connectAttr "animCurveTA330.a" "clipLibrary1.cel[0].cev[192].cevr";
connectAttr "animCurveTA331.a" "clipLibrary1.cel[0].cev[193].cevr";
connectAttr "animCurveTA332.a" "clipLibrary1.cel[0].cev[194].cevr";
connectAttr "animCurveTA333.a" "clipLibrary1.cel[0].cev[195].cevr";
connectAttr "animCurveTA334.a" "clipLibrary1.cel[0].cev[196].cevr";
connectAttr "animCurveTU111.a" "clipLibrary1.cel[0].cev[197].cevr";
connectAttr "animCurveTA335.a" "clipLibrary1.cel[0].cev[198].cevr";
connectAttr "animCurveTA336.a" "clipLibrary1.cel[0].cev[199].cevr";
connectAttr "animCurveTA337.a" "clipLibrary1.cel[0].cev[200].cevr";
connectAttr "animCurveTU112.a" "clipLibrary1.cel[0].cev[201].cevr";
connectAttr "animCurveTA338.a" "clipLibrary1.cel[0].cev[202].cevr";
connectAttr "animCurveTA339.a" "clipLibrary1.cel[0].cev[203].cevr";
connectAttr "animCurveTA340.a" "clipLibrary1.cel[0].cev[204].cevr";
connectAttr "animCurveTA341.a" "clipLibrary1.cel[0].cev[205].cevr";
connectAttr "animCurveTA342.a" "clipLibrary1.cel[0].cev[206].cevr";
connectAttr "animCurveTA343.a" "clipLibrary1.cel[0].cev[207].cevr";
connectAttr "animCurveTA344.a" "clipLibrary1.cel[0].cev[208].cevr";
connectAttr "animCurveTA345.a" "clipLibrary1.cel[0].cev[209].cevr";
connectAttr "animCurveTA346.a" "clipLibrary1.cel[0].cev[210].cevr";
connectAttr "animCurveTL79.a" "clipLibrary1.cel[0].cev[211].cevr";
connectAttr "animCurveTL80.a" "clipLibrary1.cel[0].cev[212].cevr";
connectAttr "animCurveTL81.a" "clipLibrary1.cel[0].cev[213].cevr";
connectAttr "animCurveTU113.a" "clipLibrary1.cel[0].cev[214].cevr";
connectAttr "animCurveTU114.a" "clipLibrary1.cel[0].cev[215].cevr";
connectAttr "animCurveTA347.a" "clipLibrary1.cel[0].cev[216].cevr";
connectAttr "animCurveTA348.a" "clipLibrary1.cel[0].cev[217].cevr";
connectAttr "animCurveTA349.a" "clipLibrary1.cel[0].cev[218].cevr";
connectAttr "animCurveTL82.a" "clipLibrary1.cel[0].cev[219].cevr";
connectAttr "animCurveTL83.a" "clipLibrary1.cel[0].cev[220].cevr";
connectAttr "animCurveTL84.a" "clipLibrary1.cel[0].cev[221].cevr";
connectAttr "animCurveTL85.a" "clipLibrary1.cel[0].cev[222].cevr";
connectAttr "animCurveTL86.a" "clipLibrary1.cel[0].cev[223].cevr";
connectAttr "animCurveTL87.a" "clipLibrary1.cel[0].cev[224].cevr";
connectAttr "animCurveTA350.a" "clipLibrary1.cel[0].cev[225].cevr";
connectAttr "animCurveTA351.a" "clipLibrary1.cel[0].cev[226].cevr";
connectAttr "animCurveTA352.a" "clipLibrary1.cel[0].cev[227].cevr";
connectAttr "animCurveTL88.a" "clipLibrary1.cel[0].cev[228].cevr";
connectAttr "animCurveTL89.a" "clipLibrary1.cel[0].cev[229].cevr";
connectAttr "animCurveTL90.a" "clipLibrary1.cel[0].cev[230].cevr";
connectAttr "animCurveTA353.a" "clipLibrary1.cel[0].cev[231].cevr";
connectAttr "animCurveTA354.a" "clipLibrary1.cel[0].cev[232].cevr";
connectAttr "animCurveTA355.a" "clipLibrary1.cel[0].cev[233].cevr";
connectAttr "animCurveTL91.a" "clipLibrary1.cel[0].cev[234].cevr";
connectAttr "animCurveTL92.a" "clipLibrary1.cel[0].cev[235].cevr";
connectAttr "animCurveTL93.a" "clipLibrary1.cel[0].cev[236].cevr";
connectAttr "animCurveTU115.a" "clipLibrary1.cel[0].cev[237].cevr";
connectAttr "animCurveTA356.a" "clipLibrary1.cel[0].cev[238].cevr";
connectAttr "animCurveTA357.a" "clipLibrary1.cel[0].cev[239].cevr";
connectAttr "animCurveTA358.a" "clipLibrary1.cel[0].cev[240].cevr";
connectAttr "animCurveTL94.a" "clipLibrary1.cel[0].cev[241].cevr";
connectAttr "animCurveTL95.a" "clipLibrary1.cel[0].cev[242].cevr";
connectAttr "animCurveTL96.a" "clipLibrary1.cel[0].cev[243].cevr";
connectAttr "animCurveTA359.a" "clipLibrary1.cel[0].cev[244].cevr";
connectAttr "animCurveTA360.a" "clipLibrary1.cel[0].cev[245].cevr";
connectAttr "animCurveTA361.a" "clipLibrary1.cel[0].cev[246].cevr";
connectAttr "animCurveTL97.a" "clipLibrary1.cel[0].cev[247].cevr";
connectAttr "animCurveTL98.a" "clipLibrary1.cel[0].cev[248].cevr";
connectAttr "animCurveTL99.a" "clipLibrary1.cel[0].cev[249].cevr";
connectAttr "animCurveTA362.a" "clipLibrary1.cel[0].cev[250].cevr";
connectAttr "animCurveTA363.a" "clipLibrary1.cel[0].cev[251].cevr";
connectAttr "animCurveTA364.a" "clipLibrary1.cel[0].cev[252].cevr";
connectAttr "animCurveTL100.a" "clipLibrary1.cel[0].cev[253].cevr";
connectAttr "animCurveTL101.a" "clipLibrary1.cel[0].cev[254].cevr";
connectAttr "animCurveTL102.a" "clipLibrary1.cel[0].cev[255].cevr";
connectAttr "animCurveTA365.a" "clipLibrary1.cel[0].cev[256].cevr";
connectAttr "animCurveTA366.a" "clipLibrary1.cel[0].cev[257].cevr";
connectAttr "animCurveTA367.a" "clipLibrary1.cel[0].cev[258].cevr";
connectAttr "animCurveTL103.a" "clipLibrary1.cel[0].cev[259].cevr";
connectAttr "animCurveTL104.a" "clipLibrary1.cel[0].cev[260].cevr";
connectAttr "animCurveTL105.a" "clipLibrary1.cel[0].cev[261].cevr";
connectAttr "animCurveTU116.a" "clipLibrary1.cel[0].cev[262].cevr";
connectAttr "animCurveTU117.a" "clipLibrary1.cel[0].cev[263].cevr";
connectAttr "animCurveTL106.a" "clipLibrary1.cel[0].cev[264].cevr";
connectAttr "animCurveTL107.a" "clipLibrary1.cel[0].cev[265].cevr";
connectAttr "animCurveTL108.a" "clipLibrary1.cel[0].cev[266].cevr";
connectAttr "animCurveTU118.a" "clipLibrary1.cel[0].cev[267].cevr";
connectAttr "animCurveTU119.a" "clipLibrary1.cel[0].cev[268].cevr";
connectAttr "animCurveTL109.a" "clipLibrary1.cel[0].cev[269].cevr";
connectAttr "animCurveTL110.a" "clipLibrary1.cel[0].cev[270].cevr";
connectAttr "animCurveTL111.a" "clipLibrary1.cel[0].cev[271].cevr";
connectAttr "animCurveTU120.a" "clipLibrary1.cel[0].cev[272].cevr";
connectAttr "animCurveTU121.a" "clipLibrary1.cel[0].cev[273].cevr";
connectAttr "animCurveTU122.a" "clipLibrary1.cel[0].cev[274].cevr";
connectAttr "animCurveTA383.a" "clipLibrary1.cel[0].cev[275].cevr";
connectAttr "animCurveTA384.a" "clipLibrary1.cel[0].cev[276].cevr";
connectAttr "animCurveTA385.a" "clipLibrary1.cel[0].cev[277].cevr";
connectAttr "animCurveTL112.a" "clipLibrary1.cel[0].cev[278].cevr";
connectAttr "animCurveTL113.a" "clipLibrary1.cel[0].cev[279].cevr";
connectAttr "animCurveTL114.a" "clipLibrary1.cel[0].cev[280].cevr";
connectAttr "animCurveTU123.a" "clipLibrary1.cel[0].cev[281].cevr";
connectAttr "animCurveTU124.a" "clipLibrary1.cel[0].cev[282].cevr";
connectAttr "animCurveTU125.a" "clipLibrary1.cel[0].cev[283].cevr";
connectAttr "animCurveTA386.a" "clipLibrary1.cel[0].cev[284].cevr";
connectAttr "animCurveTA387.a" "clipLibrary1.cel[0].cev[285].cevr";
connectAttr "animCurveTA388.a" "clipLibrary1.cel[0].cev[286].cevr";
connectAttr "animCurveTL115.a" "clipLibrary1.cel[0].cev[287].cevr";
connectAttr "animCurveTL116.a" "clipLibrary1.cel[0].cev[288].cevr";
connectAttr "animCurveTL117.a" "clipLibrary1.cel[0].cev[289].cevr";
connectAttr "animCurveTA368.a" "clipLibrary1.cel[0].cev[290].cevr";
connectAttr "animCurveTA369.a" "clipLibrary1.cel[0].cev[291].cevr";
connectAttr "animCurveTA370.a" "clipLibrary1.cel[0].cev[292].cevr";
connectAttr "animCurveTA371.a" "clipLibrary1.cel[0].cev[293].cevr";
connectAttr "animCurveTA372.a" "clipLibrary1.cel[0].cev[294].cevr";
connectAttr "animCurveTA373.a" "clipLibrary1.cel[0].cev[295].cevr";
connectAttr "animCurveTA380.a" "clipLibrary1.cel[0].cev[296].cevr";
connectAttr "animCurveTA381.a" "clipLibrary1.cel[0].cev[297].cevr";
connectAttr "animCurveTA382.a" "clipLibrary1.cel[0].cev[298].cevr";
connectAttr "animCurveTA377.a" "clipLibrary1.cel[0].cev[299].cevr";
connectAttr "animCurveTA378.a" "clipLibrary1.cel[0].cev[300].cevr";
connectAttr "animCurveTA379.a" "clipLibrary1.cel[0].cev[301].cevr";
connectAttr "animCurveTA374.a" "clipLibrary1.cel[0].cev[302].cevr";
connectAttr "animCurveTA375.a" "clipLibrary1.cel[0].cev[303].cevr";
connectAttr "animCurveTA376.a" "clipLibrary1.cel[0].cev[304].cevr";
connectAttr "animCurveTA389.a" "clipLibrary1.cel[0].cev[305].cevr";
connectAttr "animCurveTA390.a" "clipLibrary1.cel[0].cev[306].cevr";
connectAttr "animCurveTA391.a" "clipLibrary1.cel[0].cev[307].cevr";
connectAttr "animCurveTL118.a" "clipLibrary1.cel[0].cev[308].cevr";
connectAttr "animCurveTL119.a" "clipLibrary1.cel[0].cev[309].cevr";
connectAttr "animCurveTL120.a" "clipLibrary1.cel[0].cev[310].cevr";
connectAttr "animCurveTU129.a" "clipLibrary1.cel[0].cev[314].cevr";
connectAttr "animCurveTU130.a" "clipLibrary1.cel[0].cev[315].cevr";
connectAttr "animCurveTU131.a" "clipLibrary1.cel[0].cev[316].cevr";
connectAttr "animCurveTU126.a" "clipLibrary1.cel[0].cev[317].cevr";
connectAttr "animCurveTU127.a" "clipLibrary1.cel[0].cev[318].cevr";
connectAttr "animCurveTU128.a" "clipLibrary1.cel[0].cev[319].cevr";
connectAttr "animCurveTA393.a" "clipLibrary1.cel[0].cev[320].cevr";
connectAttr "animCurveTA392.a" "clipLibrary1.cel[0].cev[321].cevr";
connectAttr "animCurveTU132.a" "clipLibrary1.cel[0].cev[322].cevr";
connectAttr "animCurveTU133.a" "clipLibrary1.cel[0].cev[323].cevr";
connectAttr "animCurveTU134.a" "clipLibrary1.cel[0].cev[324].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of stunB.ma
