//Maya ASCII 2008 scene
//Name: blockedA.ma
//Last modified: Tue, Oct 27, 2009 05:39:14 PM
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
createNode animClip -n "blockedASource";
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
	setAttr ".se" 16;
	setAttr ".ci" no;
createNode animCurveTU -n "animCurveTU419";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kot[0]"  5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1352";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1353";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 3.1805546814635176e-015;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1354";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 9.9392333795734924e-017;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU420";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 9;
	setAttr -s 6 ".kot[1:5]"  5 5 5 3 5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU421";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 9;
	setAttr -s 6 ".kot[1:5]"  5 5 5 3 5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU422";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 2 1 5 1 8 1 12 1 16 1;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU423";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 9;
	setAttr -s 6 ".kot[1:5]"  5 5 5 3 5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1355";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 3.1805546814635168e-015 2 2.9449580219359096e-015 
		5 2.3088470809038107e-015 8 1.4001170564519138e-015 12 0 16 8.2458846138961865e-016;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1356";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1357";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 4.7708320221952728e-015 2 4.4174370329038625e-015 
		5 3.4632706213557149e-015 8 2.1001755846778696e-015 12 0 16 1.2368826920844277e-015;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU424";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU425";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL430";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.40930268174563 2 0.43633170354839218 
		5 0.1618165489035982 8 0.25657589996926844 12 0.40930268174563 16 0.40930268174563;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  0.99975031614303589 1 0.74374556541442871 
		0.68599617481231689 1 1;
	setAttr -s 6 ".kiy[0:5]"  0.022343836724758148 0 -0.66846281290054321 
		0.72760516405105591 0 0;
	setAttr -s 6 ".kox[0:5]"  0.99975031614303589 1 0.74374556541442871 
		0.68599617481231689 1 1;
	setAttr -s 6 ".koy[0:5]"  0.022343836724758148 0 -0.66846281290054321 
		0.72760516405105591 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL431";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.057823715136270243 2 -0.35965157435578288 
		5 0.022859315603532743 8 0.17620891654238557 12 0.25860394298924627 16 0.25860394298924627;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 0.90007907152175903 0.34967043995857239 
		0.70346260070800781 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0.43572661280632019 0.93687278032302856 
		0.71073228120803833 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.90007907152175903 0.34967043995857239 
		0.70346260070800781 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0.43572661280632019 0.93687278032302856 
		0.71073228120803833 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL432";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.22451480617215203 2 -0.46630924510716609 
		5 -0.58531807432950056 8 -0.4559777482666092 12 -0.29847095663485657 16 -0.29847095663485657;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  0.99498391151428223 0.41935288906097412 
		0.99866843223571777 0.63103246688842773 1 1;
	setAttr -s 6 ".kiy[0:5]"  -0.10003558546304703 -0.90782332420349121 
		0.051588691771030426 0.77575641870498657 0 0;
	setAttr -s 6 ".kox[0:5]"  0.99498391151428223 0.41935288906097412 
		0.99866843223571777 0.63103246688842773 1 1;
	setAttr -s 6 ".koy[0:5]"  -0.10003558546304703 -0.90782332420349121 
		0.051588691771030426 0.77575641870498657 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1358";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1359";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 3.1805546814635168e-015;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1360";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -7.9513867036587899e-016;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1361";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 21.459131300514464 2 21.771482372201806 
		5 22.614830213133892 8 23.819612987139031 12 25.675870473757751 16 25.675870473757751;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1362";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.72089968334967991 2 -0.89520150934179621 
		5 -1.3658164101547934 8 -2.0381234917298006 12 -3.0739741698828946 16 -3.0739741698828946;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU426";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 3 2 3 5 3 8 3 12 3 16 3;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU427";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU428";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 2 1 5 1 8 1 12 1 16 1;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 3 9;
	setAttr -s 6 ".kot[4:5]"  3 5;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU429";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1363";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 95.027912018899102 2 113.34733150024269 
		5 99.051258524198488 8 104.90089596424389 12 95.36952323207133 16 93.144161708979723;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  0.99910265207290649 0.92154598236083984 
		0.80496031045913696 0.96410840749740601 1 1;
	setAttr -s 6 ".kiy[0:5]"  -0.042353671044111252 0.38826927542686462 
		-0.59332853555679321 -0.26550886034965515 0 0;
	setAttr -s 6 ".kox[0:5]"  0.99910265207290649 0.92154598236083984 
		0.80496031045913696 0.96410840749740601 1 1;
	setAttr -s 6 ".koy[0:5]"  -0.042353671044111252 0.38826927542686462 
		-0.59332853555679321 -0.26550886034965515 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1364";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 91.954078189911641 2 118.51746448151721 
		5 146.34329984831345 8 144.26358945656426 12 107.97263516718726 16 95.049826002206416;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 0.17292822897434235 1 1 1 0.50888890027999878;
	setAttr -s 6 ".kiy[0:5]"  0 0.98493450880050659 0 0 0 -0.86083221435546875;
	setAttr -s 6 ".kox[0:5]"  1 0.17292822897434235 1 1 1 0.50888890027999878;
	setAttr -s 6 ".koy[0:5]"  0 0.98493450880050659 0 0 0 -0.86083221435546875;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1365";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 7.3475119642090769 2 7.4081229562893132 
		5 25.921728986623496 8 35.906186803844449 12 -0.81581349734337649 16 1.1812364035166698;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 1 0.37307211756706238 0.44722011685371399 
		1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0.92780232429504395 -0.89442390203475952 
		0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 0.37307211756706238 0.44722011685371399 
		1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0.92780232429504395 -0.89442390203475952 
		0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL433";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.19751656702699438 2 0.040209986364579266 
		5 -0.34982292814684668 8 -0.49409924848805281 12 -0.36963403491041708 16 -0.23689498628395578;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
createNode animCurveTL -n "animCurveTL434";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.18549442709713693 2 -0.081399268225532714 
		5 0.23499327305421258 8 -0.12429107300561648 12 -0.27007866234030553 16 -0.30633990936382105;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  0.99999934434890747 0.36847582459449768 
		0.97776764631271362 0.41938892006874084 1 1;
	setAttr -s 6 ".kiy[0:5]"  -0.0011301732156425714 0.92963731288909912 
		-0.20969107747077942 -0.90780669450759888 0 0;
	setAttr -s 6 ".kox[0:5]"  0.99999934434890747 0.36847582459449768 
		0.97776764631271362 0.41938892006874084 1 1;
	setAttr -s 6 ".koy[0:5]"  -0.0011301732156425714 0.92963731288909912 
		-0.20969107747077942 -0.90780669450759888 0 0;
createNode animCurveTL -n "animCurveTL435";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.26334592628767134 2 0.36381769246993828 
		5 -0.10015311132219004 8 -0.025148933711661801 12 0.63254486700036361 16 0.52899036848843184;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
createNode animCurveTU -n "animCurveTU430";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 9;
	setAttr -s 6 ".kot[1:5]"  5 5 5 3 5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1366";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -9.2343529322129996 2 7.6379324218070694 
		5 50.518661067945622 8 59.527557128151848 12 -23.005790458061856 16 -24.884454396993167;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1367";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -15.11110170915666 2 -58.419279025678719 
		5 -34.494521975418358 8 -34.577256613630993 12 -35.663137500819623 16 -43.339475474578435;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1368";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 18.196383878722202 2 -4.5167534973241619 
		5 -69.598513327560809 8 -83.75334443644897 12 15.521541257797558 16 11.606559612787883;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU431";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 9;
	setAttr -s 6 ".kot[0:5]"  5 5 5 5 3 5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU432";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 9;
	setAttr -s 6 ".kot[0:5]"  5 5 5 5 3 5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU433";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU434";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 9;
	setAttr -s 6 ".kot[0:5]"  5 5 5 5 3 5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1369";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 3.9531091186723013 2 38.617144398564079 
		5 23.764594445699885 8 -49.916980066170439 12 -36.209203078805118 16 3.9531091186723013;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1370";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.62018686761647346 2 0.62018686761647346 
		5 0.62018686761647346 8 0.62018686761647346 12 0.62018686761647346 16 0.62018686761647346;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1371";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 5.3292188742882338 2 5.3292188742882338 
		5 5.3292188742882338 8 5.3292188742882338 12 5.3292188742882338 16 5.3292188742882338;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU435";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU436";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL436";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL437";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL438";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.1102230246251565e-016;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1372";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -19.513757781440109 2 -24.305320469447004 
		5 -31.815217808033236 8 -38.912407048461617 12 -35.169549530392395 16 -44.757110789561033;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1373";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 1.542421710003496 16 
		0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1374";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 -3.5406735993917851 
		16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1375";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -11.226354836536574 2 -14.335186281618633 
		5 -19.207710833046168 8 -23.812464344133936 12 -27.604588158357807 16 -27.604588158357807;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1376";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.99923745724103941 2 -0.87289287271175198 
		5 -0.53176251576873679 8 -0.044433376132907466 12 0.70641431476594085 16 0.70641431476594085;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU437";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".kot[0]"  5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU438";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU439";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU440";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
	setAttr ".kot[0]"  5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU441";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1377";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1378";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1379";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL439";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 2.2204460492503131e-016;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL440";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL441";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 4.4408920985006262e-016;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU442";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 2 1 5 1 8 1 12 1 16 1;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1380";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -3.8674792585271232 2 -2.9191093139877133 
		5 -2.0447585160461141 8 -0.79568579815851015 12 1.1288109940741509 16 1.1288109940741509;
	setAttr -s 6 ".kit[0:5]"  9 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  9 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1381";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 12.134175752092313 2 11.59252996532012 
		5 10.130086432289643 8 8.0408811352167167 12 4.8219581414201906 16 4.8219581414201906;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1382";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 10.746835796865771 2 14.037987768955128 
		5 19.196266120521162 8 24.07106997771535 12 28.08558650754679 16 28.08558650754679;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU443";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1383";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 68.629003384766676 2 68.629003384766676 
		5 68.629003384766676 8 68.629003384766676 12 68.629003384766676 16 68.629003384766676;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1384";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 5.1251585428584878 2 5.1251585428584878 
		5 5.1251585428584878 8 5.1251585428584878 12 5.1251585428584878 16 5.1251585428584878;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1385";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -1.4794141658124507 2 -1.4794141658124507 
		5 -1.4794141658124507 8 -1.4794141658124507 12 -1.4794141658124507 16 -1.4794141658124507;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1386";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 2.9967431843380723 2 2.9967431843380723 
		5 2.9967431843380723 8 2.9967431843380723 12 2.9967431843380723 16 2.9967431843380723;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1387";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 27.356153209428296 2 27.356153209428296 
		5 27.356153209428296 8 27.356153209428296 12 27.356153209428296 16 27.356153209428296;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1388";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 4.8891453517792058 2 4.8891453517792058 
		5 4.8891453517792058 8 4.8891453517792058 12 4.8891453517792058 16 4.8891453517792058;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU444";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1389";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 59.032884886088816 2 59.032884886088816 
		5 59.032884886088816 8 59.032884886088816 12 59.032884886088816 16 59.032884886088816;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1390";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1391";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1392";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 61.945270723308987 2 61.945270723308987 
		5 61.945270723308987 8 61.945270723308987 12 61.945270723308987 16 61.945270723308987;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1393";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1394";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU445";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1395";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 59.032884886088816 2 59.032884886088816 
		5 59.032884886088816 8 59.032884886088816 12 59.032884886088816 16 59.032884886088816;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1396";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1397";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1398";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 61.945270723308987 2 61.945270723308987 
		5 61.945270723308987 8 61.945270723308987 12 61.945270723308987 16 61.945270723308987;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1399";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1400";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU446";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1401";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 59.032884886088816 2 59.032884886088816 
		5 59.032884886088816 8 59.032884886088816 12 59.032884886088816 16 59.032884886088816;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1402";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1403";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1404";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 72.878304588436421 2 72.878304588436421 
		5 72.878304588436421 8 72.878304588436421 12 72.878304588436421 16 72.878304588436421;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1405";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1406";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU447";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1407";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 77.67986202714836 2 77.67986202714836 
		5 77.67986202714836 8 77.67986202714836 12 77.67986202714836 16 77.67986202714836;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1408";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1409";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1410";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 65.952779168408995 2 65.952779168408995 
		5 65.952779168408995 8 65.952779168408995 12 65.952779168408995 16 65.952779168408995;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1411";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 12.091864976351665 2 12.091864976351665 
		5 12.091864976351665 8 12.091864976351665 12 12.091864976351665 16 12.091864976351665;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1412";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -6.5683373417752975 2 -6.5683373417752975 
		5 -6.5683373417752975 8 -6.5683373417752975 12 -6.5683373417752975 16 -6.5683373417752975;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1413";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1414";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1415";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU448";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1416";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 -23.400000056205045 12 -15.480000035337881 
		16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1417";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1418";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1419";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1420";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1421";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU449";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1422";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 -23.400000056205045 12 -15.480000035337881 
		16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1423";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1424";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1425";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 -23.400000056205045 12 -15.480000035337881 
		16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1426";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1427";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU450";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1428";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 -23.400000056205045 12 -15.480000035337881 
		16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1429";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1430";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1431";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 -23.400000056205045 12 -15.480000035337881 
		16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1432";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1433";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU451";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1434";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 -23.400000056205045 12 -15.480000035337881 
		16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1435";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1436";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1437";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 -23.400000056205045 12 -15.480000035337881 
		16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1438";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1439";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU452";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1440";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 -23.400000056205045 12 -15.480000035337881 
		16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1441";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1442";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1443";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 -23.400000056205045 12 -15.480000035337881 
		16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1444";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1445";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1446";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1447";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1448";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU453";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[1:5]"  9 9 9 3 9;
	setAttr -s 6 ".kot[1:5]"  5 5 5 3 5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU454";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[1:5]"  9 9 9 3 9;
	setAttr -s 6 ".kot[1:5]"  5 5 5 3 5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU455";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 2 1 5 1 8 1 12 1 16 1;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1449";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.92590198521464373 2 0.10373481480627098 
		5 -2.1161164067807006 8 -10.173354040024311 12 -10.173354040024311 16 -10.173354040024311;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1450";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1451";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL442";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL443";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.36869042509528277 2 0.042233408597678601 
		5 0.29601451554481295 8 0.643246524321337 12 0.643246524321337 16 0.643246524321337;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  0.13651072978973389 0.24320913851261139 
		0.3157479465007782 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0.9906386137008667 0.9699738621711731 0.94884312152862549 
		0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.13651072978973389 0.24320913851261139 
		0.3157479465007782 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0.9906386137008667 0.9699738621711731 0.94884312152862549 
		0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL444";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.32507334843177282 2 0.31461791934130451 
		5 0.2693002734663752 8 0.10481400598920043 12 0.10481400598920043 16 0.10481400598920043;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  0.9920840859413147 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0.12557573616504669 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.9920840859413147 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0.1255757212638855 0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1452";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 12 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1453";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 12 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1454";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 12 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU456";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 12 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1455";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 12 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1456";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 12 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1457";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 12 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1458";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 12 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1459";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 12 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1460";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 12 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1461";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 12 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1462";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 12 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1463";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 12 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU457";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 2 1 5 1 8 1 12 1 16 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1464";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 4.2739658544589174 2 6.9735406541525657 
		5 14.262392158511201 8 27.980639860936925 12 40.718223104721211 16 40.718223104721211;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 1 0.47887590527534485 0.45101770758628845 
		1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0.87788254022598267 0.89251506328582764 
		0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 0.47887590527534485 0.45101770758628845 
		1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0.87788254022598267 0.89251506328582764 
		0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1465";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -41.531258985004385 2 -41.292032802832345 
		5 -40.646122151271761 8 -39.72339253867613 12 -38.301705751263519 16 -38.301705751263519;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1466";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 43.535238447847377 2 41.920327755783582 
		5 37.560069159285426 8 29.353686238099506 12 21.733945627788874 16 21.733945627788874;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU458";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 3 9;
	setAttr -s 6 ".kot[0:5]"  1 5 5 5 3 5;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0 0 0 1 0;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU459";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 3 9;
	setAttr -s 6 ".kot[0:5]"  1 5 5 5 3 5;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0 0 0 1 0;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU460";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 2 1 5 1 8 1 12 1 16 1;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1467";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -2.5120182699055205 2 0.46804126879442443 
		5 5.6227220553128854 8 17.962181958626559 12 17.962181958626559 16 17.962181958626559;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 0.76123714447021484 0.54794192314147949 
		1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0.64847356081008911 0.83651638031005859 
		0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.76123714447021484 0.54794192314147949 
		1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0.64847356081008911 0.83651638031005859 
		0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1468";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -1.4434920278151244 2 -1.577266471401749 
		5 -4.8302797635790187 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  0.85406249761581421 1 0.99065977334976196 
		1 1 1;
	setAttr -s 6 ".kiy[0:5]"  -0.52017033100128174 0 0.13635684549808502 
		0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.85406249761581421 1 0.99065977334976196 
		1 1 1;
	setAttr -s 6 ".koy[0:5]"  -0.52017039060592651 0 0.13635684549808502 
		0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1469";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 111.72754493272389 2 60.349417657642064 
		5 1.6164184113303393 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 0.086399883031845093 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 -0.99626058340072632 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.086399883031845093 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 -0.99626058340072632 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL445";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1.1038762275260849 2 0.78744473420686933 
		5 0.63904334521000317 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  0.2796078622341156 0.33751240372657776 
		0.24617008864879608 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  -0.96011430025100708 -0.94132113456726074 
		-0.96922659873962402 0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.2796078622341156 0.33751240372657776 
		0.24617008864879608 1 1 1;
	setAttr -s 6 ".koy[0:5]"  -0.96011430025100708 -0.94132113456726074 
		-0.96922659873962402 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL446";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.078254692248154289 2 -0.183939383316153 
		5 -0.6365566652337068 8 -0.64789329560123088 12 -0.64789329560123088 16 -0.64789329560123088;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  0.19317714869976044 0.22707115113735199 
		1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  -0.98116385936737061 -0.97387820482254028 
		0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.19317714869976044 0.22707115113735199 
		1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  -0.98116385936737061 -0.97387820482254028 
		0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL447";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.3584706980247494 2 -0.035800624528763647 
		5 -0.12346908486322856 8 -0.07395615046270454 12 -0.07395615046270454 16 -0.07395615046270454;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 0.57849609851837158 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0.81568509340286255 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.57849609851837158 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0.81568509340286255 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1470";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 12 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1471";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 12 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1472";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 12 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU461";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 12 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1473";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 12 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1474";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 12 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1475";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 12 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1476";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 12 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1477";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 12 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1478";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 12 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1479";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 12 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1480";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 12 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1481";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 5 0 12 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1482";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -29.311636586952385 2 -22.070472830510194 
		5 -7.2839551050357016 8 1.4585665008673419 12 -10.753373031419716 16 -10.753373031419716;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  0.41200023889541626 0.39774656295776367 
		0.43785488605499268 0.96793746948242188 1 1;
	setAttr -s 6 ".kiy[0:5]"  0.91118377447128296 0.91749531030654907 
		0.89904564619064331 -0.25119125843048096 0 0;
	setAttr -s 6 ".kox[0:5]"  0.41200023889541626 0.39774656295776367 
		0.43785488605499268 0.96793746948242188 1 1;
	setAttr -s 6 ".koy[0:5]"  0.91118377447128296 0.91749531030654907 
		0.89904564619064331 -0.25119125843048096 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1483";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -5.7546656733329762 2 -4.7565423371553166 
		5 -3.0463221879042677 8 -3.0843858730103513 12 -4.9387346018875373 16 -4.9387346018875373;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  0.94282537698745728 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0.33328738808631897 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.9428253173828125 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0.33328735828399658 0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1484";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 24.135668239007668 2 24.006593392930917 
		5 14.054070727173354 8 20.844886211894316 12 22.393157938684443 16 22.393157938684443;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 1 0.96398055553436279 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 -0.26597282290458679 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 0.96398055553436279 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 -0.26597282290458679 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1485";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -28.064725223295074 2 -23.513317450657084 
		5 -16.379818634180378 8 -9.638343167867788 12 -4.0865779949808214 16 -4.0865779949808214;
	setAttr -s 6 ".kit[0:5]"  9 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  9 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1486";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 8.1722234572666252 2 6.7912417979933029 
		5 3.0625915506179351 8 -3.9550500210498605 12 -10.471027640707172 16 -10.471027640707172;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1487";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 3.5236391014183068 2 3.1331803818496335 
		5 2.0789419047972335 8 0.57288675744265449 12 -1.7475532445702493 16 -1.7475532445702493;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU462";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 2 1 5 1 8 1 12 1 16 1;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1488";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.011476194518726878 2 -1.3498670557888655 
		5 6.3565052225654251 8 21.148501410591905 12 21.524625747024565 16 20.69101533741409;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1489";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -3.621145868974136 2 1.28196863270182 
		5 -7.4578989461104062 8 -24.61268300479535 12 -5.4811122285072003 16 -8.3978566024888135;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1490";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 2.5085875540734017 2 32.699400548588642 
		5 -17.727036635076146 8 -34.766314611250174 12 9.3591022674925881 16 2.8255796210686652;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU463";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1491";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 -9.2685927150355791 5 -15.947797781592705 
		8 25.797396787474639 12 15.51889898417225 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1492";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 -22.806437378554673 5 -38.661430256805552 
		8 36.716102747288978 12 12.886455096289039 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1493";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 35.065837550057907 5 -5.0608460251231522 
		8 -3.3023043894750379 12 -13.257674650085491 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1494";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 10.793181446349577 2 8.6735851510427224 
		5 14.379744370410123 8 10.120891901923793 12 -17.821366541589882 16 -17.821366541589882;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1495";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -11.069096393638221 2 -11.138488804621337 
		5 10.873025207117147 8 11.369652940500599 12 -12.005893876475762 16 -12.005893876475762;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1496";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 46.971202074790767 2 44.168731889403801 
		5 39.722558316098905 8 24.792582278914349 12 9.1378572146953019 16 9.1378572146953019;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1497";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -35.396144853650526 2 -41.366008606995891 
		5 -37.857674640500385 8 30.324509018154551 12 14.263357009863125 16 -28.841216077843235;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  0.38007229566574097 0.96834611892700195 
		0.15783838927745819 0.24845641851425171 1 0.17451080679893494;
	setAttr -s 6 ".kiy[0:5]"  -0.92495673894882202 -0.24961133301258087 
		0.98746496438980103 0.96864306926727295 0 -0.98465526103973389;
	setAttr -s 6 ".kox[0:5]"  0.38007229566574097 0.96834611892700195 
		0.15783838927745819 0.24845641851425171 1 0.17451080679893494;
	setAttr -s 6 ".koy[0:5]"  -0.92495673894882202 -0.24961133301258087 
		0.98746496438980103 0.96864306926727295 0 -0.98465526103973389;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1498";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -34.018174792048853 2 -25.519326861270947 
		5 -23.191051265371655 8 4.162336746420408 12 -0.30192869909459963 16 -21.716766331039956;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  0.33000805974006653 1 1 0.50435024499893188 
		1 0.33599632978439331;
	setAttr -s 6 ".kiy[0:5]"  0.94397813081741333 0 0 0.8634992241859436 
		0 -0.94186323881149292;
	setAttr -s 6 ".kox[0:5]"  0.33000805974006653 1 1 0.50435024499893188 
		1 0.3359963595867157;
	setAttr -s 6 ".koy[0:5]"  0.94397813081741333 0 0 0.8634992241859436 
		0 -0.9418632984161377;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1499";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -1.9884446047337234 2 2.8563284035375296 
		5 10.449623200271366 8 97.728228672945278 12 71.305290095276519 16 23.535235892507558;
	setAttr -s 6 ".kit[0:5]"  9 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  9 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL448";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  9 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  9 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL449";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  9 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  9 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL450";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  9 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  9 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU464";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 2 2 2 5 2 8 2 12 2 16 2;
	setAttr -s 6 ".kit[4:5]"  3 9;
	setAttr -s 6 ".kot[1:5]"  5 5 5 3 5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU465";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 9;
	setAttr -s 6 ".kot[1:5]"  5 5 5 3 5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1500";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -24.093441664171177 2 -24.093441664171177 
		5 -24.093441664171177 8 -24.093441664171177 12 -24.093441664171177 16 -24.093441664171177;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1501";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 49.48465546224881 2 49.48465546224881 
		5 49.48465546224881 8 49.48465546224881 12 49.48465546224881 16 49.48465546224881;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1502";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 58.801792680015588 2 58.801792680015588 
		5 58.801792680015588 8 58.801792680015588 12 58.801792680015588 16 58.801792680015588;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL451";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -1.2755255474500937 2 -1.2755255474500937 
		5 -1.2755255474500937 8 -1.2755255474500937 12 -1.2755255474500937 16 -1.2755255474500937;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL452";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -1.4392043230118035 2 -1.4392043230118035 
		5 -1.4392043230118035 8 -1.4392043230118035 12 -1.4392043230118035 16 -1.4392043230118035;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL453";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -2.1802956492995231 2 -2.1802956492995231 
		5 -2.1802956492995231 8 -2.1802956492995231 12 -2.1802956492995231 16 -2.1802956492995231;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL454";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL455";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL456";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1503";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1.1134085745786892 2 10.139794095591188 
		5 1.1134085745786892 8 13.153529556047603 12 0.66432740662321865 16 1.1134085745786892;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1504";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -5.3180374758492821 2 13.701106287538446 
		5 -5.3180374758492821 8 -9.8752435832438952 12 3.2036362799380877 16 -5.3180374758492821;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1505";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 7.8609313736722894 2 -18.414821800505738 
		5 7.8609313736722894 8 -7.1894312668565048 12 -18.796707154397467 16 7.8609313736722894;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL457";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL458";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL459";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1506";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1507";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1508";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL460";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL461";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL462";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU466";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 9;
	setAttr -s 6 ".kot[0:5]"  5 5 5 5 3 5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1509";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -5.1107219305963252 2 -5.1107219305963252 
		5 -5.1107219305963252 8 -5.1107219305963252 12 -5.1107219305963252 16 -5.1107219305963252;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1510";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 8.2811672786141717 2 8.2811672786141717 
		5 8.2811672786141717 8 8.2811672786141717 12 8.2811672786141717 16 8.2811672786141717;
	setAttr -s 6 ".kit[0:5]"  9 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  9 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1511";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.92645454014921158 2 -0.92645454014921158 
		5 -0.92645454014921158 8 -0.92645454014921158 12 -0.92645454014921158 16 -0.92645454014921158;
	setAttr -s 6 ".kit[0:5]"  9 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  9 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL463";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.040515110247265507 2 -0.040984835139230492 
		5 -0.042253092268398462 8 -0.044064888383915909 12 -0.046856395845859107 16 -0.046856395845859107;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL464";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.041176417316286837 2 -0.039855850288817697 
		5 -0.036290319537135192 8 -0.031196703568349429 12 -0.023348763690700665 16 -0.023348763690700665;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL465";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.019976476006593587 2 0.0084922080766329008 
		5 -0.022515313399434633 8 -0.066811777949189494 12 -0.13506113021862395 16 -0.13506113021862395;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1512";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -1.2399711943881462 2 -25.764258986184366 
		5 -39.110796940136538 8 16.252082401597431 12 25.716639065056981 16 -1.6266160090263075;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  0.92331308126449585 0.24450130760669708 
		0.26312071084976196 0.20197451114654541 1 0.26908531785011292;
	setAttr -s 6 ".kiy[0:5]"  0.38404801487922668 -0.96964901685714722 
		0.96476292610168457 0.97939074039459229 0 -0.9631163477897644;
	setAttr -s 6 ".kox[0:5]"  0.92331314086914063 0.24450130760669708 
		0.26312071084976196 0.20197451114654541 1 0.26908531785011292;
	setAttr -s 6 ".koy[0:5]"  0.38404804468154907 -0.96964901685714722 
		0.96476292610168457 0.97939074039459229 0 -0.9631163477897644;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1513";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -35.889138953044828 2 -32.139638397396887 
		5 -34.660814195233677 8 -10.850271944408924 12 -16.449503297867615 16 2.8499857758927387;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1514";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -3.5262114410899876 2 13.156848592157232 
		5 14.25171669180958 8 -31.390602301231969 12 -7.9915673180907065 16 -25.210898828531619;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  0.60353332757949829 1 1 0.51514852046966553 
		1 0.40553557872772217;
	setAttr -s 6 ".kiy[0:5]"  -0.79733783006668091 0 0 -0.85710090398788452 
		0 -0.91407918930053711;
	setAttr -s 6 ".kox[0:5]"  0.60353332757949829 1 1 0.51514852046966553 
		1 0.40553560853004456;
	setAttr -s 6 ".koy[0:5]"  -0.79733783006668091 0 0 -0.85710090398788452 
		0 -0.91407924890518188;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL466";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 -0.00082916307906145156 5 -0.0030679032528330907 
		8 -0.0062661038836099902 12 -0.011193700785458628 16 -0.011193700785458628;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL467";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0.026055577858671002 5 0.01610297905880867 
		8 0.0018849790726986528 12 -0.020021267836214246 16 -0.020021267836214246;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  0.85944533348083496 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0.51122772693634033 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.85944533348083496 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0.51122772693634033 0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL468";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0.012400821539454373 5 0.016729670314834758 
		8 0.022913740733616437 12 0.032441787830836878 16 0.032441787830836878;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  0.97746771574020386 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0.2110850065946579 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.97746771574020386 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0.2110850065946579 0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1515";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1516";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1517";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL469";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL470";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL471";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1518";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -3.4820313138629455 2 -4.3593472367953741 
		5 -7.5438530194459403 8 -14.344609330667874 12 -15.609971163878811 16 -15.609971163878811;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  0.99019926786422729 1 0.75392824411392212 
		1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0.13966159522533417 0 -0.65695679187774658 
		0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.99019932746887207 1 0.75392824411392212 
		1 1 1;
	setAttr -s 6 ".koy[0:5]"  0.13966159522533417 0 -0.65695679187774658 
		0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1519";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1.2721832506814086 2 -0.20313784670824367 
		5 -8.4037565953133555 8 -0.97842807012150157 12 8.3116042646716988 16 8.3116042646716988;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 1 0.99771910905838013 0.62460184097290039 
		1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 -0.067502513527870178 0.78094339370727539 
		0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 0.99771910905838013 0.62460184097290039 
		1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 -0.067502513527870178 0.78094339370727539 
		0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1520";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 13.092921420682925 2 -11.523418853839278 
		5 -11.694607233793468 8 -10.543943049754873 12 14.458598883932659 16 14.458598883932659;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL472";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.189 2 -0.18897639360543425 5 -0.23458100565981463 
		8 -0.28436686583136772 12 -0.28043738456120265 16 -0.18868131369562219;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 0.82378405332565308;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0.56690376996994019;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 0.82378405332565308;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0.56690376996994019;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL473";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.27905490988822479 2 -0.24130335924777074 
		5 0.19574845960676696 8 0.29061612712965518 12 0.16493775540587458 16 0.23059098815955009;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 1 0.35194128751754761 0.99139434099197388 
		1 0.89713811874389648;
	setAttr -s 6 ".kiy[0:5]"  0 0 0.93602204322814941 -0.13090954720973969 
		0 0.44175007939338684;
	setAttr -s 6 ".kox[0:5]"  1 1 0.35194128751754761 0.99139434099197388 
		1 0.89713817834854126;
	setAttr -s 6 ".koy[0:5]"  0 0 0.93602204322814941 -0.13090954720973969 
		0 0.44175010919570923;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL474";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.0035205622938596082 2 0.00043790282684435557 
		5 -0.0057031953869992307 8 0.025677044541643809 12 0.045427551905797781 16 0.049918713102953649;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU467";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[1:5]"  9 9 9 3 9;
	setAttr -s 6 ".kot[1:5]"  5 5 5 3 5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU468";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.084155571970393403 2 0.084155571970393403 
		5 0.084155571970393403 8 0.084155571970393403 12 0.084155571970393403 16 0.084155571970393403;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL475";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0.24814849011792889 5 0.76988455153046376 
		8 0.47559569435171511 12 0.067207227343123899 16 0.067207227343123899;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL476";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.8360926868100278 2 -0.83253986741685071 
		5 -0.73475052853227429 8 -0.46464123608831798 12 -0.20472824713235571 16 -0.20472824713235571;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL477";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 2.7755575615628914e-017 2 0.18067791687232782 
		5 0.12897995250868963 8 0.16345384742688288 12 0.20941646546924442 16 0.20941646546924442;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU469";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 3 9;
	setAttr -s 6 ".kot[0:5]"  1 5 5 5 3 5;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0 0 0 1 0;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU470";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.084155864375844894 2 0.084155864375844894 
		5 0.084155864375844894 8 0.084155864375844894 12 0.084155864375844894 16 0.084155864375844894;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL478";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0.055536153879434558 5 0.043540344485069146 
		8 0.026403471871975861 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL479";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.8360926868100278 2 -0.78709421329184226 
		5 -0.70367291280488431 8 -0.54666682176411552 12 -0.40088449385078673 16 -0.40088449385078673;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 1 0.63951206207275391 0.61039942502975464 
		1 1;
	setAttr -s 6 ".kiy[0:5]"  0 0 0.76878106594085693 0.79209381341934204 
		0 0;
	setAttr -s 6 ".kox[0:5]"  1 1 0.63951206207275391 0.61039942502975464 
		1 1;
	setAttr -s 6 ".koy[0:5]"  0 0 0.76878106594085693 0.79209381341934204 
		0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL480";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.073926484418881333 2 -0.22538809811397406 
		5 -0.4032761608076636 8 -0.56463523499640267 12 -0.69609418843799409 16 -0.69609418843799409;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 0.45152536034584045 0.50785541534423828 
		0.62319386005401611 1 1;
	setAttr -s 6 ".kiy[0:5]"  0 -0.89225834608078003 -0.86144232749938965 
		-0.78206741809844971 0 0;
	setAttr -s 6 ".kox[0:5]"  1 0.45152536034584045 0.50785541534423828 
		0.62319386005401611 1 1;
	setAttr -s 6 ".koy[0:5]"  0 -0.89225834608078003 -0.86144232749938965 
		-0.78206741809844971 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1521";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 -22.608661715757478 5 -30.391694026447738 
		8 0 12 28.382063549187663 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1522";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0.0087985316409879329 5 -6.9558262829700217 
		8 0 12 -6.4771800737510352 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1523";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 1.8342541048631926 5 -2.3045562947127678 
		8 0 12 -0.48112708273426946 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1524";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1525";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 10.320621744681866 5 15.344488333984978 
		8 0 12 -19.350994366813705 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1526";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1527";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1528";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1529";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1530";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -18.592620239620459 2 -54.409642256572894 
		5 -69.930267982955286 8 -18.592620239620459 12 -0.80909392662648294 16 -18.592620239620459;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 0.18287286162376404 0.30472049117088318 
		0.189894899725914 1 0.39470168948173523;
	setAttr -s 6 ".kiy[0:5]"  0 -0.98313653469085693 0.9524417519569397 
		0.9818044900894165 0 -0.91880935430526733;
	setAttr -s 6 ".kox[0:5]"  1 0.18287286162376404 0.30472049117088318 
		0.189894899725914 1 0.39470168948173523;
	setAttr -s 6 ".koy[0:5]"  0 -0.98313653469085693 0.9524417519569397 
		0.9818044900894165 0 -0.91880935430526733;
createNode animCurveTA -n "animCurveTA1531";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -4.0495369920864128 2 4.610339901132007 
		5 18.441609334091606 8 -4.0495369920864128 12 -12.217149664279406 16 -4.0495369920864128;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 0.39081335067749023 0.79780548810958862 
		0.39970952272415161 1 0.68309837579727173;
	setAttr -s 6 ".kiy[0:5]"  0 0.92046993970870972 -0.60291498899459839 
		-0.91664183139801025 0 0.73032635450363159;
	setAttr -s 6 ".kox[0:5]"  1 0.39081335067749023 0.79780548810958862 
		0.39970952272415161 1 0.68309837579727173;
	setAttr -s 6 ".koy[0:5]"  0 0.92046993970870972 -0.60291498899459839 
		-0.91664183139801025 0 0.73032635450363159;
createNode animCurveTA -n "animCurveTA1532";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -24.718935474963271 2 -1.9242421256580473 
		5 13.484278438953128 8 -24.718935474963271 12 -30.781356026467012 16 -24.718935474963271;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  1 0.24249961972236633 0.44915071129798889 
		0.28911963105201721 1 0.78332018852233887;
	setAttr -s 6 ".kiy[0:5]"  0 0.97015148401260376 -0.89345598220825195 
		-0.95729291439056396 0 0.62161850929260254;
	setAttr -s 6 ".kox[0:5]"  1 0.24249961972236633 0.44915071129798889 
		0.28911963105201721 1 0.78332018852233887;
	setAttr -s 6 ".koy[0:5]"  0 0.97015148401260376 -0.89345598220825195 
		-0.95729291439056396 0 0.62161850929260254;
createNode animCurveTA -n "animCurveTA1533";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1534";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 11.282554258022039 5 9.6503392925310543 
		8 0 12 -23.587312510756774 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1535";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU471";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 2 1 5 1 8 1 12 1 16 1;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU472";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 2 1 5 1 8 1 12 1 16 1;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU473";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 2 1 5 1 8 1 12 1 16 1;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1536";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1537";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1538";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL481";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL482";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL483";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU474";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 2 1 5 1 8 1 12 1 16 1;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU475";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 2 1 5 1 8 1 12 1 16 1;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU476";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 2 1 5 1 8 1 12 1 16 1;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1539";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1540";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1541";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL484";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL485";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL486";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1542";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1543";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1544";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 7.2644697342894906 2 8.9460601400269084 
		5 8.5828366076517302 8 8.0639457850520539 12 7.2644697342894906 16 7.2644697342894906;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 3 10;
	setAttr -s 6 ".kix[0:5]"  0.8445855975151062 1 1 1 1 1;
	setAttr -s 6 ".kiy[0:5]"  0.53542047739028931 0 0 0 0 0;
	setAttr -s 6 ".kox[0:5]"  0.84458565711975098 1 1 1 1 1;
	setAttr -s 6 ".koy[0:5]"  0.53542053699493408 0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL487";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL488";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL489";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL490";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.026619555792534968 2 0.024638886306198232 
		5 0.019291079026784792 8 0.011651353428133001 12 -0.000119480405310887 16 -0.000119480405310887;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL491";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.063502212298763738 2 0.067335871921208698 
		5 0.077686752255929512 8 0.092473725931319986 12 0.1152566135867675 16 0.1152566135867675;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL492";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.1400224852942063 2 0.14410663190297424 
		5 0.15513382705856602 8 0.1708869648793335 12 0.19515846066137013 16 0.19515846066137013;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 3 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "Ratcatcher_CTRL_STUFF_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 2 1 5 1 8 1 12 1 16 1;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
createNode animCurveTU -n "Ratcatcher_CTRL_STUFF_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 2 1 5 1 8 1 12 1 16 1;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
createNode animCurveTU -n "Ratcatcher_CTRL_STUFF_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 2 1 5 1 8 1 12 1 16 1;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
createNode animCurveTU -n "Ratcatcher_CTRL_STUFF_LAT_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 2 1 5 1 8 1 12 1 16 1;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
createNode animCurveTU -n "Ratcatcher_CTRL_STUFF_LAT_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 2 1 5 1 8 1 12 1 16 1;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
createNode animCurveTU -n "Ratcatcher_CTRL_STUFF_LAT_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 2 1 5 1 8 1 12 1 16 1;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
createNode animCurveTA -n "Ratcatcher_CTRL_TwistR_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
createNode animCurveTA -n "Ratcatcher_CTRL_TwistL_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 2 0 5 0 8 0 12 0 16 0;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
createNode animCurveTU -n "Ratcatcher_CTRL_JAR_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 2 1 5 1 8 1 12 1 16 1;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
createNode animCurveTU -n "Ratcatcher_CTRL_JAR_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 2 1 5 1 8 1 12 1 16 1;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
createNode animCurveTU -n "Ratcatcher_CTRL_JAR_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1 2 1 5 1 8 1 12 1 16 1;
	setAttr -s 6 ".kit[4:5]"  3 10;
	setAttr -s 6 ".kot[4:5]"  3 10;
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
connectAttr "blockedASource.cl" "clipLibrary1.sc[0]";
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
// End of blockedA.ma
