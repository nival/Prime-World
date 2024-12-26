//Maya ASCII 2008 scene
//Name: attack1B.ma
//Last modified: Tue, Oct 06, 2009 03:10:56 PM
//Codeset: 1251
requires maya "2008";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Complete 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200802250025-718075";
fileInfo "osv" "Microsoft Windows XP Service Pack 3 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 317 ".cel[0].cev";
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
createNode animClip -n "attack01aSource";
	setAttr ".ihi" 0;
	setAttr -s 317 ".ac";
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
	setAttr ".ac[314:319]" yes yes yes yes yes yes;
	setAttr ".se" 45;
	setAttr ".ci" no;
createNode animCurveTU -n "animCurveTU68";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 1;
	setAttr -s 5 ".kot[0:4]"  3 5 5 5 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA199";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA200";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA201";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU69";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 1;
	setAttr -s 5 ".kot[0:4]"  3 5 5 5 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU70";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 1;
	setAttr -s 5 ".kot[0:4]"  3 5 5 5 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU71";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 4 1 10 1 19 1 45 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU72";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 1;
	setAttr -s 5 ".kot[0:4]"  3 5 5 5 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA202";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA203";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA204";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU73";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 4 0 13 0 17 0 26 0 34 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 9 1 10 10 9 9 1;
	setAttr -s 8 ".kot[0:7]"  3 9 1 10 10 9 9 1;
	setAttr -s 8 ".kix[2:7]"  1 1 1 1 1 1;
	setAttr -s 8 ".kiy[2:7]"  0 0 0 0 0 0;
	setAttr -s 8 ".kox[2:7]"  1 1 1 1 1 1;
	setAttr -s 8 ".koy[2:7]"  0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU74";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 4 0 13 0 17 0 26 0 34 0 45 0;
	setAttr -s 8 ".kit[0:7]"  3 9 1 10 10 9 9 1;
	setAttr -s 8 ".kot[0:7]"  3 9 1 10 10 9 9 1;
	setAttr -s 8 ".kix[2:7]"  1 1 1 1 1 1;
	setAttr -s 8 ".kiy[2:7]"  0 0 0 0 0 0;
	setAttr -s 8 ".kox[2:7]"  1 1 1 1 1 1;
	setAttr -s 8 ".koy[2:7]"  0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL61";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.40930268174563 3 0.43468541737393829 
		4 0.43468541737393829 8 0.072990606175917239 13 -0.49762924884143822 17 -0.42638398384086595 
		26 0.80424254335103407 30 1.1540413670596952 34 1.0986115253875914 45 0.40930268174563;
	setAttr -s 10 ".kit[0:9]"  3 9 1 10 10 10 9 10 
		9 1;
	setAttr -s 10 ".kot[0:9]"  3 9 1 10 10 10 9 10 
		9 1;
	setAttr -s 10 ".kix[2:9]"  0.97902441024780273 0.30631217360496521 
		0.51496928930282593 0.31581848859786987 0.26442816853523254 0.67137396335601807 0.55740433931350708 
		1;
	setAttr -s 10 ".kiy[2:9]"  0.20374293625354767 -0.95193111896514893 
		-0.85720866918563843 0.94881963729858398 0.96440541744232178 0.74111878871917725 
		-0.83024120330810547 0;
	setAttr -s 10 ".kox[2:9]"  0.97902441024780273 0.30631217360496521 
		0.51496928930282593 0.31581848859786987 0.26442816853523254 0.67137396335601807 0.55740433931350708 
		1;
	setAttr -s 10 ".koy[2:9]"  0.20374293625354767 -0.95193111896514893 
		-0.85720866918563843 0.94881963729858398 0.96440541744232178 0.74111878871917725 
		-0.83024120330810547 0;
createNode animCurveTL -n "animCurveTL62";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.25860394298924627 3 -1.5172814583221161 
		4 -1.5172814583221161 8 -1.4495647507737277 13 -1.6488926559539987 17 -0.2947069262335843 
		26 0.53102390532875088 30 -0.19544114503558352 34 -0.59565039750148174 45 0.25860394298924627;
	setAttr -s 10 ".kit[0:9]"  3 9 1 10 10 10 9 10 
		1 1;
	setAttr -s 10 ".kot[0:9]"  3 9 1 10 10 10 9 10 
		1 1;
	setAttr -s 10 ".kix[2:9]"  0.097372099757194519 0.91575199365615845 
		0.25142732262611389 0.1949695497751236 0.97475183010101318 0.23032140731811523 0.24748298525810242 
		1;
	setAttr -s 10 ".kiy[2:9]"  -0.99524807929992676 -0.40174406766891479 
		0.967876136302948 0.98080933094024658 0.22329115867614746 -0.97311466932296753 -0.96889221668243408 
		0;
	setAttr -s 10 ".kox[2:9]"  0.097372099757194519 0.91575199365615845 
		0.25142732262611389 0.1949695497751236 0.97475183010101318 0.23032140731811523 0.24748298525810242 
		1;
	setAttr -s 10 ".koy[2:9]"  -0.99524807929992676 -0.40174406766891479 
		0.967876136302948 0.98080933094024658 0.22329115867614746 -0.97311466932296753 -0.96889221668243408 
		0;
createNode animCurveTL -n "animCurveTL63";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.29847095663485657 3 -0.44213239623314415 
		4 -0.44213239623314415 8 -0.089589082477795012 13 -0.35020232045543198 17 -0.18683364829388605 
		26 0.087771596425776699 30 -0.17641728083955543 34 -0.46129500754560604 45 -0.29847095663485657;
	setAttr -s 10 ".kit[0:9]"  3 9 1 10 10 10 9 10 
		9 1;
	setAttr -s 10 ".kot[0:9]"  3 9 1 10 10 10 9 10 
		9 1;
	setAttr -s 10 ".kix[2:9]"  0.33150917291641235 0.95611667633056641 
		0.95127195119857788 0.70333075523376465 0.99971121549606323 0.43687373399734497 0.97147446870803833 
		1;
	setAttr -s 10 ".kiy[2:9]"  0.94345200061798096 0.29298624396324158 
		-0.30835342407226563 0.71086275577545166 0.024030828848481178 -0.89952290058135986 
		-0.23714405298233032 0;
	setAttr -s 10 ".kox[2:9]"  0.33150917291641235 0.95611667633056641 
		0.95127195119857788 0.70333075523376465 0.99971121549606323 0.43687373399734497 0.97147446870803833 
		1;
	setAttr -s 10 ".koy[2:9]"  0.94345200061798096 0.29298624396324158 
		-0.30835342407226563 0.71086275577545166 0.024030828848481178 -0.89952290058135986 
		-0.23714405298233032 0;
createNode animCurveTA -n "animCurveTA205";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA206";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA207";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA208";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 25.675870473757751 2 76.862768227924661 
		6 12.748610096036266 10 6.0358713913742275 14 9.6363069238148356 19 9.5152805067183728 
		32 11.151010145367716 45 25.675870473757751;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 1;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTA -n "animCurveTA209";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -3.0739741698828946 2 14.326794910562832 
		6 -3.8746970603376254 10 -1.9540687078575565 14 4.4686456746889549 19 12.773230885377428 
		32 -2.5446001549209805 45 -3.0739741698828946;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 1;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTU -n "animCurveTU75";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 3 1 3 3 3 10 3 21 3 37 3 40 3 42 3 45 
		3;
	setAttr -s 9 ".kit[2:8]"  1 1 10 9 1 10 1;
	setAttr -s 9 ".kot[2:8]"  1 1 10 9 1 10 1;
	setAttr -s 9 ".kix[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[2:8]"  0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[2:8]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU76";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 1 0 3 0 10 0 21 0 37 0 40 0 42 0 45 
		0;
	setAttr -s 9 ".kit[2:8]"  1 1 10 9 1 10 1;
	setAttr -s 9 ".kot[2:8]"  1 1 10 9 1 10 1;
	setAttr -s 9 ".kix[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[2:8]"  0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[2:8]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU77";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 1 1 3 1 10 1 21 1 37 1 40 1 42 1 45 
		1;
	setAttr -s 9 ".kit[2:8]"  1 1 9 9 9 9 1;
	setAttr -s 9 ".kot[0:8]"  5 5 1 1 5 9 9 5 
		5;
	setAttr -s 9 ".kix[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[2:8]"  0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  1 1 0 1 1 0 0;
	setAttr -s 9 ".koy[2:8]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU78";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 1 0 3 0 10 0 21 0 37 0 40 0 42 0 45 
		0;
	setAttr -s 9 ".kit[2:8]"  1 1 10 9 1 10 1;
	setAttr -s 9 ".kot[2:8]"  1 1 10 9 1 10 1;
	setAttr -s 9 ".kix[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".kiy[2:8]"  0 0 0 0 0 0 0;
	setAttr -s 9 ".kox[2:8]"  1 1 1 1 1 1 1;
	setAttr -s 9 ".koy[2:8]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA210";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 93.144161708979723 3 115.75785937936566 
		4 117.20261507476941 10 117.26954675542166 14 215.37378656645274 19 266.72145119700525 
		21 295.82257351641829 25 309.83522676233412 28 327.62744476710748 33 280.9160688831131 
		37 170.13875085714341 39 148.0738572364375 45 93.144161708979752;
	setAttr -s 13 ".kit[1:12]"  1 10 1 10 10 10 9 9 
		9 9 9 3;
	setAttr -s 13 ".kot[1:12]"  1 10 1 10 10 10 9 9 
		9 9 9 3;
	setAttr -s 13 ".kix[1:12]"  0.27825146913528442 1 1 0.11425859481096268 
		0.16393227875232697 0.25687041878700256 0.38750272989273071 0.46714091300964355 0.10849834978580475 
		0.085942216217517853 0.19464543461799622 1;
	setAttr -s 13 ".kiy[1:12]"  0.96050828695297241 0 0 0.99345105886459351 
		0.98647159337997437 0.96644586324691772 0.92186850309371948 -0.88418292999267578 
		-0.99409657716751099 -0.9963001012802124 -0.980873703956604 0;
	setAttr -s 13 ".kox[1:12]"  0.27825146913528442 1 1 0.11425859481096268 
		0.16393227875232697 0.25687041878700256 0.38750272989273071 0.46714091300964355 0.10849834978580475 
		0.085942216217517853 0.19464543461799622 1;
	setAttr -s 13 ".koy[1:12]"  0.96050828695297241 0 0 0.99345105886459351 
		0.98647159337997437 0.96644586324691772 0.92186850309371948 -0.88418292999267578 
		-0.99409657716751099 -0.9963001012802124 -0.980873703956604 0;
createNode animCurveTA -n "animCurveTA211";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 95.049826002206416 3 173.55955899786747 
		4 175.64803719016186 10 175.37995316885375 14 192.61460612578645 19 305.38518167694758 
		21 364.89851668291112 25 375.82959430914042 28 299.37818183465942 33 206.41607818722179 
		37 67.203085306164624 39 80.397457609257145 45 95.049826002206402;
	setAttr -s 13 ".kit[1:12]"  1 10 1 10 10 10 9 9 
		9 9 3 3;
	setAttr -s 13 ".kot[1:12]"  1 10 1 10 10 10 9 9 
		9 9 3 3;
	setAttr -s 13 ".kix[1:12]"  0.092073298990726471 1 1 0.13107500970363617 
		0.077366158366203308 0.1605590432882309 0.19992437958717346 0.089822329580783844 
		0.073831439018249512 0.09055858850479126 1 1;
	setAttr -s 13 ".kiy[1:12]"  0.99575221538543701 0 0 0.99137246608734131 
		0.99700272083282471 0.98702627420425415 -0.97981131076812744 -0.99595779180526733 
		-0.99727070331573486 -0.99589115381240845 0 0;
	setAttr -s 13 ".kox[1:12]"  0.092073298990726471 1 1 0.13107500970363617 
		0.077366158366203308 0.1605590432882309 0.19992437958717346 0.089822329580783844 
		0.073831439018249512 0.09055858850479126 1 1;
	setAttr -s 13 ".koy[1:12]"  0.99575221538543701 0 0 0.99137246608734131 
		0.99700272083282471 0.98702627420425415 -0.97981131076812744 -0.99595779180526733 
		-0.99727070331573486 -0.99589115381240845 0 0;
createNode animCurveTA -n "animCurveTA212";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 1.1812364035166698 3 -11.216627280647769 
		4 -10.505014183911358 10 -6.6031710164928326 14 5.2244220267108696 19 42.699201647009339 
		21 38.348771318179509 25 -34.823793435974146 28 -43.636652547435098 33 39.685876219529675 
		37 17.324853078332858 39 -25.019009793538466 45 1.181236403516621;
	setAttr -s 13 ".kit[1:12]"  1 10 1 10 10 10 9 9 
		9 9 1 3;
	setAttr -s 13 ".kot[1:12]"  1 10 1 10 10 10 9 9 
		9 9 1 3;
	setAttr -s 13 ".kix[1:12]"  0.4471079409122467 1 1 0.32920536398887634 
		0.37426742911338806 0.14622732996940613 0.16094008088111877 0.20087906718254089 0.27137917280197144 
		0.17438513040542603 0.86986458301544189 1;
	setAttr -s 13 ".kiy[1:12]"  -0.89447993040084839 0 0 0.94425839185714722 
		0.92732083797454834 -0.98925101757049561 -0.98696416616439819 0.97961604595184326 
		0.96247249841690063 -0.98467761278152466 -0.49329060316085815 0;
	setAttr -s 13 ".kox[1:12]"  0.4471079409122467 1 1 0.32920536398887634 
		0.37426742911338806 0.14622732996940613 0.16094008088111877 0.20087906718254089 0.27137917280197144 
		0.17438513040542603 0.86986458301544189 1;
	setAttr -s 13 ".koy[1:12]"  -0.89447993040084839 0 0 0.94425839185714722 
		0.92732083797454834 -0.98925101757049561 -0.98696416616439819 0.97961604595184326 
		0.96247249841690063 -0.98467761278152466 -0.49329060316085815 0;
createNode animCurveTL -n "animCurveTL64";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -0.23689498628395578 1 -0.2128646999433948 
		2 0.064398309741281801 3 1.0097209316906457 4 1.7291202695547405 10 1.2994355863876532 
		16 1.1181300488575305 21 0.59378987356292279 25 0.047951499458424494 28 -0.21848756688669554 
		37 -0.5402539709559947 40 -0.30339286342549099 45 -0.23689498628395578;
	setAttr -s 13 ".kit[3:12]"  1 10 1 10 10 9 9 9 
		1 3;
	setAttr -s 13 ".kot[3:12]"  1 10 1 10 10 9 9 9 
		1 3;
	setAttr -s 13 ".kix[3:12]"  0.12530678510665894 0.62725144624710083 
		1 0.46108633279800415 0.26992189884185791 0.2760927677154541 0.56232953071594238 
		0.97820591926574707 0.85772937536239624 1;
	setAttr -s 13 ".kiy[3:12]"  0.99211806058883667 0.778816819190979 0 
		-0.8873552680015564 -0.96288228034973145 -0.96113103628158569 -0.82691317796707153 
		-0.20763714611530304 0.51410144567489624 0;
	setAttr -s 13 ".kox[3:12]"  0.12530678510665894 0.62725144624710083 
		1 0.46108633279800415 0.26992189884185791 0.2760927677154541 0.56232953071594238 
		0.97820591926574707 0.85772937536239624 1;
	setAttr -s 13 ".koy[3:12]"  0.99211806058883667 0.778816819190979 0 
		-0.8873552680015564 -0.96288228034973145 -0.96113103628158569 -0.82691317796707153 
		-0.20763714611530304 0.51410144567489624 0;
createNode animCurveTL -n "animCurveTL65";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -0.30633990936382105 1 0.22782711359842409 
		2 0.10580081012049375 3 0.086729218870389799 4 0.12093662595050947 10 0.26801548173452044 
		16 0.23335781242611142 21 0.91298985674339217 25 1.0151326797915814 28 0.89336837020505444 
		37 0.17704220315245664 40 -0.37208267793724614 45 -0.30633990936382105;
	setAttr -s 13 ".kit[1:12]"  3 10 1 10 1 10 10 9 
		9 9 1 3;
	setAttr -s 13 ".kot[1:12]"  3 10 1 10 1 10 10 9 
		9 9 1 3;
	setAttr -s 13 ".kix[3:12]"  0.3881697952747345 1 1 1 0.35826873779296875 
		0.99648284912109375 0.43073159456253052 0.30139440298080444 0.92107653617858887 1;
	setAttr -s 13 ".kiy[3:12]"  -0.92158788442611694 0 0 0 0.93361848592758179 
		-0.083796314895153046 -0.90248006582260132 -0.95349961519241333 -0.38938167691230774 
		0;
	setAttr -s 13 ".kox[3:12]"  0.3881697952747345 1 1 1 0.35826873779296875 
		0.99648284912109375 0.43073159456253052 0.30139440298080444 0.92107653617858887 1;
	setAttr -s 13 ".koy[3:12]"  -0.92158788442611694 0 0 0 0.93361848592758179 
		-0.083796314895153046 -0.90248006582260132 -0.95349961519241333 -0.38938167691230774 
		0;
createNode animCurveTL -n "animCurveTL66";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0.52899036848843184 1 0.35739904050772053 
		2 0.32675547652910331 3 0.073230791132674042 4 -0.28802974048043062 10 -0.28001385610125062 
		16 -0.15353052502289952 21 0.73936776605834531 25 1.0886579062843691 28 0.96917009523612541 
		37 0.44477343992688761 40 0.53392408725970408 45 0.52899036848843184;
	setAttr -s 13 ".kit[3:12]"  1 10 1 10 10 9 9 9 
		1 3;
	setAttr -s 13 ".kot[3:12]"  1 10 1 10 10 9 9 9 
		1 3;
	setAttr -s 13 ".kix[3:12]"  0.24686276912689209 1 1 0.33846554160118103 
		0.2347598522901535 0.71247720718383789 0.52769386768341064 0.67666584253311157 0.90755754709243774 
		1;
	setAttr -s 13 ".kiy[3:12]"  -0.96905046701431274 0 0 0.94097882509231567 
		0.9720534086227417 0.70169526338577271 -0.84943467378616333 -0.73629021644592285 
		-0.41992771625518799 0;
	setAttr -s 13 ".kox[3:12]"  0.24686276912689209 1 1 0.33846554160118103 
		0.2347598522901535 0.71247720718383789 0.52769386768341064 0.67666584253311157 0.90755754709243774 
		1;
	setAttr -s 13 ".koy[3:12]"  -0.96905046701431274 0 0 0.94097882509231567 
		0.9720534086227417 0.70169526338577271 -0.84943467378616333 -0.73629021644592285 
		-0.41992771625518799 0;
createNode animCurveTU -n "animCurveTU79";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 7 0 10 0 14 0 18 0 45 0;
	setAttr -s 6 ".kit[5]"  1;
	setAttr -s 6 ".kot[1:5]"  5 9 5 5 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTA -n "animCurveTA213";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -24.884454396993167 2 -23.596579016535774 
		7 9.3264575368872933 10 16.827846407881136 12 28.474934488331233 14 38.524436495285912 
		18 20.610233317087964 22 4.9504473093272088 29 -23.10837546156726 36 -53.953937927493648 
		45 -24.884454396993167;
	setAttr -s 11 ".kit[0:10]"  9 10 10 9 10 10 10 10 
		10 3 1;
	setAttr -s 11 ".kot[0:10]"  9 10 10 9 10 10 10 10 
		10 3 1;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[10]"  1;
	setAttr -s 11 ".koy[10]"  0;
createNode animCurveTA -n "animCurveTA214";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -43.339475474578435 2 -25.199412457173366 
		7 -47.324575072465393 10 -36.656933255354943 12 -31.564472922535231 14 -19.055562571646114 
		18 -31.910152325321995 22 -36.517798200318971 29 -35.872851007488762 36 -36.031426811607595 
		45 -43.339475474578435;
	setAttr -s 11 ".kit[0:10]"  9 10 10 9 10 3 10 10 
		10 10 1;
	setAttr -s 11 ".kot[0:10]"  9 10 10 9 10 3 10 10 
		10 10 1;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[10]"  1;
	setAttr -s 11 ".koy[10]"  0;
createNode animCurveTA -n "animCurveTA215";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 11.606559612787883 2 -2.2529800054162816 
		7 -43.45258516787149 10 -53.103810847512378 12 -80.142135798080801 14 -95.793003124918144 
		18 -86.661022733743948 22 -20.307282570327626 29 28.564013508359697 36 47.43985067069525 
		45 11.606559612787882;
	setAttr -s 11 ".kit[0:10]"  9 10 10 9 10 10 10 10 
		10 3 1;
	setAttr -s 11 ".kot[0:10]"  9 10 10 9 10 10 10 10 
		10 3 1;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[10]"  1;
	setAttr -s 11 ".koy[10]"  0;
createNode animCurveTU -n "animCurveTU80";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 7 0 10 0 14 0 18 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 9 9 1 9 1;
	setAttr -s 6 ".kot[0:5]"  3 5 9 5 5 1;
	setAttr -s 6 ".kix[3:5]"  1 1 1;
	setAttr -s 6 ".kiy[3:5]"  0 0 0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTU -n "animCurveTU81";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 7 0 10 0 14 0 18 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 9 9 1 9 1;
	setAttr -s 6 ".kot[0:5]"  3 5 9 5 5 1;
	setAttr -s 6 ".kix[3:5]"  1 1 1;
	setAttr -s 6 ".kiy[3:5]"  0 0 0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTU -n "animCurveTU82";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 7 0 10 0 14 0 18 0 45 0;
	setAttr -s 6 ".kit[1:5]"  10 9 1 10 1;
	setAttr -s 6 ".kot[1:5]"  10 9 1 10 1;
	setAttr -s 6 ".kix[3:5]"  1 1 1;
	setAttr -s 6 ".kiy[3:5]"  0 0 0;
	setAttr -s 6 ".kox[3:5]"  1 1 1;
	setAttr -s 6 ".koy[3:5]"  0 0 0;
createNode animCurveTU -n "animCurveTU83";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 7 0 10 0 14 0 18 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 9 9 1 9 1;
	setAttr -s 6 ".kot[0:5]"  3 5 9 5 5 1;
	setAttr -s 6 ".kix[3:5]"  1 1 1;
	setAttr -s 6 ".kiy[3:5]"  0 0 0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTA -n "animCurveTA216";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 3.9531091186723013 7 -35.277090013886912 
		10 -30.441129304420858 12 -32.489082737801446 14 -30.441129304420858 18 5.5416715900147855 
		29 -0.51423255767806719 45 3.9531091186723013;
	setAttr -s 8 ".kit[0:7]"  3 10 9 10 1 10 10 1;
	setAttr -s 8 ".kot[0:7]"  3 10 9 10 1 10 10 1;
	setAttr -s 8 ".kix[4:7]"  1 0.6915019154548645 0.99952578544616699 
		1;
	setAttr -s 8 ".kiy[4:7]"  0 0.72237461805343628 -0.030791664496064186 
		0;
	setAttr -s 8 ".kox[4:7]"  1 0.6915019154548645 0.99952578544616699 
		1;
	setAttr -s 8 ".koy[4:7]"  0 0.72237461805343628 -0.030791664496064186 
		0;
createNode animCurveTA -n "animCurveTA217";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.62018686761647346 7 1.2026165595568494 
		10 -10.249718912968683 12 -5.1251629918220134 14 -10.249718912968683 18 2.2254300294803797 
		29 13.782654825417296 45 0.62018686761647335;
	setAttr -s 8 ".kit[0:7]"  3 10 9 10 1 10 10 1;
	setAttr -s 8 ".kot[0:7]"  3 10 9 10 1 10 10 1;
	setAttr -s 8 ".kix[4:7]"  1 0.7661241888999939 0.99951577186584473 
		1;
	setAttr -s 8 ".kiy[4:7]"  0 0.64269250631332397 -0.03111468069255352 
		0;
	setAttr -s 8 ".kox[4:7]"  1 0.7661241888999939 0.99951577186584473 
		1;
	setAttr -s 8 ".koy[4:7]"  0 0.64269250631332397 -0.03111468069255352 
		0;
createNode animCurveTA -n "animCurveTA218";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 5.3292188742882338 7 -17.280867501195583 
		10 -22.546939929681116 12 -28.702058706266623 14 -22.546939929681116 18 5.7357257974619413 
		29 -9.9304761227447944 45 5.329218874288232;
	setAttr -s 8 ".kit[0:7]"  3 10 9 10 1 10 10 1;
	setAttr -s 8 ".kot[0:7]"  3 10 9 10 1 10 10 1;
	setAttr -s 8 ".kix[4:7]"  1 0.91518086194992065 0.9999690055847168 
		1;
	setAttr -s 8 ".kiy[4:7]"  0 0.40304350852966309 -0.0078829610720276833 
		0;
	setAttr -s 8 ".kox[4:7]"  1 0.91518086194992065 0.9999690055847168 
		1;
	setAttr -s 8 ".koy[4:7]"  0 0.40304350852966309 -0.0078829610720276833 
		0;
createNode animCurveTU -n "animCurveTU84";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU85";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL67";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 18 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL68";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 18 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL69";
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
createNode animCurveTA -n "animCurveTA219";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -44.757110789561033 2 -63.409319917022401 
		7 13.13555804954896 10 19.226365416662496 12 15.776861732524532 14 1.6008858753013815 
		18 -30.728142239701675 22 -54.45543427369185 36 -58.291144714201216 45 -44.757110789561033;
	setAttr -s 10 ".kit[0:9]"  3 10 10 9 10 10 10 10 
		10 1;
	setAttr -s 10 ".kot[0:9]"  3 10 10 9 10 10 10 10 
		10 1;
	setAttr -s 10 ".kix[9]"  1;
	setAttr -s 10 ".kiy[9]"  0;
	setAttr -s 10 ".kox[9]"  1;
	setAttr -s 10 ".koy[9]"  0;
createNode animCurveTA -n "animCurveTA220";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.10616870005340093 4 0 7 -0.21664053470564906 
		10 0 12 -1.4385192003922338 14 -1.5989936705445666 18 -1.7051623705979673 45 0.10616870005340093;
	setAttr -s 8 ".kit[1:7]"  3 10 9 10 10 10 1;
	setAttr -s 8 ".kot[1:7]"  3 10 9 10 10 10 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA221";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -4.9406171614869088 4 0 7 6.2444500700939116 
		10 0 12 -0.84528342911993304 14 3.780235141320003 18 8.7208523028069109 45 -4.9406171614869088;
	setAttr -s 8 ".kit[1:7]"  3 10 9 10 10 10 1;
	setAttr -s 8 ".kot[1:7]"  3 10 9 10 10 10 1;
	setAttr -s 8 ".kix[7]"  0.83969789743423462;
	setAttr -s 8 ".kiy[7]"  0.54305386543273926;
	setAttr -s 8 ".kox[7]"  0.83969783782958984;
	setAttr -s 8 ".koy[7]"  0.54305380582809448;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA222";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -27.604588158357807 2 -50.202770284903863 
		5 -21.54835747330322 7 -8.2833454810374096 9 -12.428247766795797 13 -38.646668087640471 
		14 -46.17901999284561 18 -54.729383898134422 36 13.560195645834412 45 -27.604588158357807;
	setAttr -s 10 ".kit[0:9]"  3 10 10 3 10 10 10 10 
		1 1;
	setAttr -s 10 ".kot[0:9]"  3 10 10 3 10 10 10 10 
		1 1;
	setAttr -s 10 ".kix[8:9]"  0.93832641839981079 1;
	setAttr -s 10 ".kiy[8:9]"  -0.34575065970420837 0;
	setAttr -s 10 ".kox[8:9]"  0.93832641839981079 1;
	setAttr -s 10 ".koy[8:9]"  -0.34575068950653076 0;
createNode animCurveTA -n "animCurveTA223";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.70641431476594085 2 -21.669243440807016 
		5 -4.3822319574232695 7 5.6969679318527424 9 10.144665084115807 13 9.6440025537290772 
		14 6.4406652360253904 18 -2.1689763810546103 36 17.430167149121225 45 0.70641431476594152;
	setAttr -s 10 ".kit[0:9]"  3 10 10 3 10 10 10 10 
		10 1;
	setAttr -s 10 ".kot[0:9]"  3 10 10 3 10 10 10 10 
		10 1;
	setAttr -s 10 ".kix[9]"  1;
	setAttr -s 10 ".kiy[9]"  0;
	setAttr -s 10 ".kox[9]"  1;
	setAttr -s 10 ".koy[9]"  0;
createNode animCurveTU -n "animCurveTU86";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 1;
	setAttr -s 5 ".kot[0:4]"  3 5 5 5 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU87";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 3 4 3 10 3 19 3 45 3;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU88";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU89";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 4 1 10 1 19 1 45 1;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 1;
	setAttr -s 5 ".kot[0:4]"  3 5 5 5 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU90";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA224";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA225";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA226";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL70";
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
createNode animCurveTL -n "animCurveTL71";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 18 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL72";
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
createNode animCurveTU -n "animCurveTU91";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 4 1 10 1 45 1;
	setAttr -s 4 ".kit[0:3]"  9 10 10 1;
	setAttr -s 4 ".kot[0:3]"  9 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "animCurveTA227";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.1288109940741509 4 58.703867264479328 
		6 35.698244125548406 10 11.378996241334185 45 1.128810994074152;
	setAttr -s 5 ".kit[0:4]"  9 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  9 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.75574880838394165;
	setAttr -s 5 ".kiy[4]"  0.65486156940460205;
	setAttr -s 5 ".kox[4]"  0.75574880838394165;
	setAttr -s 5 ".koy[4]"  0.65486156940460205;
createNode animCurveTA -n "animCurveTA228";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 4.8219581414201906 4 22.533836891509715 
		6 21.628207703138841 10 3.9143607508826594 45 4.8219581414201906;
	setAttr -s 5 ".kit[0:4]"  9 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  9 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.99842506647109985;
	setAttr -s 5 ".kiy[4]"  0.056102175265550613;
	setAttr -s 5 ".kox[4]"  0.99842506647109985;
	setAttr -s 5 ".koy[4]"  0.056102175265550613;
createNode animCurveTA -n "animCurveTA229";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 28.08558650754679 4 21.154673882900841 
		6 24.873023129176985 10 21.081725064297036 45 28.08558650754679;
	setAttr -s 5 ".kit[0:4]"  9 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  9 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.98474812507629395;
	setAttr -s 5 ".kiy[4]"  -0.17398592829704285;
	setAttr -s 5 ".kox[4]"  0.98474812507629395;
	setAttr -s 5 ".koy[4]"  -0.17398592829704285;
createNode animCurveTU -n "animCurveTU92";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA230";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 68.629003384766676 4 68.629003384766676 
		10 68.629003384766676 19 68.629003384766676 45 68.629003384766676;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA231";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 5.1251585428584878 4 5.1251585428584878 
		10 5.1251585428584878 19 5.1251585428584878 45 5.1251585428584878;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA232";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.4794141658124507 4 -1.4794141658124507 
		10 -1.4794141658124507 19 -1.4794141658124507 45 -1.4794141658124507;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA233";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 2.9967431843380723 4 2.9967431843380723 
		10 2.9967431843380723 19 2.9967431843380723 45 2.9967431843380723;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA234";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 27.356153209428296 4 27.356153209428296 
		10 27.356153209428296 19 27.356153209428296 45 27.356153209428296;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA235";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 4.8891453517792058 4 4.8891453517792058 
		10 4.8891453517792058 19 4.8891453517792058 45 4.8891453517792058;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU93";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA236";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 59.032884886088816 4 59.032884886088816 
		10 59.032884886088816 19 59.032884886088816 45 59.032884886088816;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA237";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA238";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA239";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 61.945270723308987 4 61.945270723308987 
		10 61.945270723308987 19 61.945270723308987 45 61.945270723308987;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA240";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA241";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU94";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA242";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 59.032884886088816 4 59.032884886088816 
		10 59.032884886088816 19 59.032884886088816 45 59.032884886088816;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA243";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA244";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA245";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 61.945270723308987 4 61.945270723308987 
		10 61.945270723308987 19 61.945270723308987 45 61.945270723308987;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA246";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA247";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU95";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA248";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 59.032884886088816 4 59.032884886088816 
		10 59.032884886088816 19 59.032884886088816 45 59.032884886088816;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA249";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA250";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA251";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 72.878304588436421 4 72.878304588436421 
		10 72.878304588436421 19 72.878304588436421 45 72.878304588436421;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA252";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA253";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU96";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA254";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 77.67986202714836 4 77.67986202714836 
		10 77.67986202714836 19 77.67986202714836 45 77.67986202714836;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA255";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA256";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA257";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 65.952779168408995 4 65.952779168408995 
		10 65.952779168408995 19 65.952779168408995 45 65.952779168408995;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA258";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 12.091864976351665 4 12.091864976351665 
		10 12.091864976351665 19 12.091864976351665 45 12.091864976351665;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA259";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -6.5683373417752975 4 -6.5683373417752975 
		10 -6.5683373417752975 19 -6.5683373417752975 45 -6.5683373417752975;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA260";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 4 -2.7468650574888867 14 -2.4933702259208617 
		20 0 24 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 3 10 1 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 3 10 1 10 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[4:6]"  1 1 1;
	setAttr -s 7 ".koy[4:6]"  0 0 0;
createNode animCurveTA -n "animCurveTA261";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 4 19.996838159631746 14 18.151427112828106 
		20 0 24 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 3 10 1 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 3 10 1 10 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[4:6]"  1 1 1;
	setAttr -s 7 ".koy[4:6]"  0 0 0;
createNode animCurveTA -n "animCurveTA262";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 4 10.865577604100588 14 9.8628462332487725 
		20 0 24 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 3 10 1 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 3 10 1 10 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[4:6]"  1 1 1;
	setAttr -s 7 ".koy[4:6]"  0 0 0;
createNode animCurveTU -n "animCurveTU97";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 0 12 0 19 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA263";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 0 12 0 19 34.262393603929802 
		45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA264";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 0 12 0 19 -0.70376266287504119 
		45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA265";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 0 12 0 19 1.6064960187851509 
		45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA266";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 -6.3204850620411932 12 -6.3204850620411932 
		19 13.768213520563359 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  0.90131151676177979 1 0.99500906467437744 
		1;
	setAttr -s 6 ".kiy[2:5]"  0.43317148089408875 0 0.099784277379512787 
		0;
	setAttr -s 6 ".kox[2:5]"  0.90131151676177979 1 0.99500906467437744 
		1;
	setAttr -s 6 ".koy[2:5]"  0.43317148089408875 0 0.099784277379512787 
		0;
createNode animCurveTA -n "animCurveTA267";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 21.315462643276618 12 21.315462643276618 
		19 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA268";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 -12.343675790905083 12 -12.343675790905083 
		19 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTU -n "animCurveTU98";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 0 12 0 19 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA269";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 -32.527010599495426 12 -32.527010599495426 
		19 49.181903298131225 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  0.5033261775970459 1 0.88863331079483032 
		1;
	setAttr -s 6 ".kiy[2:5]"  0.86409646272659302 0 0.45861834287643433 
		0;
	setAttr -s 6 ".kox[2:5]"  0.5033261775970459 1 0.88863331079483032 
		1;
	setAttr -s 6 ".koy[2:5]"  0.86409646272659302 0 0.45861834287643433 
		0;
createNode animCurveTA -n "animCurveTA270";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 -8.3128345339977621 12 -8.3128345339977621 
		19 -6.0913285304031328 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA271";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 -4.6621369302498028 12 -4.6621369302498028 
		19 -7.2331308749262124 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA272";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 0 8 0 12 0 16 -15.752147933113269 
		19 30.718357554511652 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 1 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 1 10 10 10 1;
	setAttr -s 7 ".kix[2:6]"  1 1 0.39905762672424316 0.96185535192489624 
		1;
	setAttr -s 7 ".kiy[2:6]"  0 0 0.91692584753036499 0.27355846762657166 
		0;
	setAttr -s 7 ".kox[2:6]"  1 1 0.39905762672424316 0.96185535192489624 
		1;
	setAttr -s 7 ".koy[2:6]"  0 0 0.91692584753036499 0.27355846762657166 
		0;
createNode animCurveTA -n "animCurveTA273";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 0 12 0 19 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA274";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 0 12 0 19 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTU -n "animCurveTU99";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 0 12 0 19 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA275";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 0 12 0 19 49.181903298131225 
		45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA276";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 0 12 0 19 -6.0913285304031328 
		45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA277";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 0 12 0 19 -7.2331308749262124 
		45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA278";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 0 8 0 12 0 16 -15.752147933113269 
		19 30.718357554511652 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 1 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 1 10 10 10 1;
	setAttr -s 7 ".kix[2:6]"  1 1 0.39905762672424316 0.96185535192489624 
		1;
	setAttr -s 7 ".kiy[2:6]"  0 0 0.91692584753036499 0.27355846762657166 
		0;
	setAttr -s 7 ".kox[2:6]"  1 1 0.39905762672424316 0.96185535192489624 
		1;
	setAttr -s 7 ".koy[2:6]"  0 0 0.91692584753036499 0.27355846762657166 
		0;
createNode animCurveTA -n "animCurveTA279";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 0 12 0 19 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA280";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 0 12 0 19 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTU -n "animCurveTU100";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 0 12 0 19 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA281";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 0 12 0 19 49.181903298131225 
		45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA282";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 0 12 0 19 -6.0913285304031328 
		45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA283";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 0 12 0 19 -7.2331308749262124 
		45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA284";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 0 8 -9.2955691717245319 12 -9.2955691717245319 
		16 -21.171375502362814 19 30.718357554511652 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 1 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 1 10 10 10 1;
	setAttr -s 7 ".kix[2:6]"  0.66982376575469971 1 0.31688985228538513 
		0.93408328294754028 1;
	setAttr -s 7 ".kiy[2:6]"  -0.74252015352249146 0 0.94846236705780029 
		0.35705515742301941 0;
	setAttr -s 7 ".kox[2:6]"  0.66982376575469971 1 0.31688985228538513 
		0.93408328294754028 1;
	setAttr -s 7 ".koy[2:6]"  -0.74252015352249146 0 0.94846236705780029 
		0.35705515742301941 0;
createNode animCurveTA -n "animCurveTA285";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 -1.7440539091500165 12 -1.7440539091500165 
		19 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA286";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 -14.987567693188675 12 -14.987567693188675 
		19 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTU -n "animCurveTU101";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 0 12 0 19 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA287";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 0 12 0 19 49.181903298131225 
		45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA288";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 0 12 0 19 -6.0913285304031328 
		45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA289";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 0 12 0 19 -7.2331308749262124 
		45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA290";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 0 8 -19.565933259329025 12 -19.565933259329025 
		16 -27.158899147399751 19 30.718357554511652 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 1 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 1 10 10 10 1;
	setAttr -s 7 ".kix[2:6]"  0.57522696256637573 1 0.2569425106048584 
		0.89786344766616821 1;
	setAttr -s 7 ".kiy[2:6]"  -0.81799381971359253 0 0.96642673015594482 
		0.44027405977249146 0;
	setAttr -s 7 ".kox[2:6]"  0.57522696256637573 1 0.2569425106048584 
		0.89786344766616821 1;
	setAttr -s 7 ".koy[2:6]"  -0.81799381971359253 0 0.96642673015594482 
		0.44027405977249146 0;
createNode animCurveTA -n "animCurveTA291";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 0.61141773871906702 12 0.61141773871906702 
		19 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA292";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 8 -8.137677140888032 12 -8.137677140888032 
		19 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA293";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 1 -8.6508985296913412 2 -14.793425773845479 
		4 -18.232831356347365 6 -16.279185656119388 9 -7.2864106944049247 13 -7.5545979367468234 
		17 -13.52785924345277 20 0 45 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 9 3 10 3 
		1 1;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 9 3 10 3 
		1 1;
	setAttr -s 10 ".kix[8:9]"  1 1;
	setAttr -s 10 ".kiy[8:9]"  0 0;
	setAttr -s 10 ".kox[8:9]"  1 1;
	setAttr -s 10 ".koy[8:9]"  0 0;
createNode animCurveTA -n "animCurveTA294";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 1 0.38376847488949584 2 1.2386439752347831 
		4 3.3302252630933284 6 2.8987178048511066 9 1.6651124454558293 13 1.6989700169119566 
		17 2.4530704720711571 20 0 45 0;
	setAttr -s 10 ".kit[0:9]"  3 9 9 10 9 3 10 3 
		1 1;
	setAttr -s 10 ".kot[0:9]"  3 9 9 10 9 3 10 3 
		1 1;
	setAttr -s 10 ".kix[8:9]"  1 1;
	setAttr -s 10 ".kiy[8:9]"  0 0;
	setAttr -s 10 ".kox[8:9]"  1 1;
	setAttr -s 10 ".koy[8:9]"  0 0;
createNode animCurveTA -n "animCurveTA295";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 1 -3.9413973635081536 2 -5.6431070046173613 
		4 -3.7759522761659556 6 -3.5247002554827782 9 -1.887975927085205 13 -1.9462817985530785 
		17 -3.2449125721557119 20 0 45 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 1 3 10 3 
		1 1;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 1 3 10 3 
		1 1;
	setAttr -s 10 ".kix[4:9]"  0.99607956409454346 1 1 1 1 1;
	setAttr -s 10 ".kiy[4:9]"  0.088462166488170624 0 0 0 0 0;
	setAttr -s 10 ".kox[4:9]"  0.99607956409454346 1 1 1 1 1;
	setAttr -s 10 ".koy[4:9]"  0.088462159037590027 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU102";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 4 0 14 0 20 0 24 0 45 0;
	setAttr -s 7 ".kit[1:6]"  9 3 9 1 3 1;
	setAttr -s 7 ".kot[1:6]"  5 3 5 1 3 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[4:6]"  1 1 1;
	setAttr -s 7 ".koy[4:6]"  0 0 0;
createNode animCurveTU -n "animCurveTU103";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 4 0 14 0 20 0 24 0 45 0;
	setAttr -s 7 ".kit[1:6]"  9 3 9 1 3 1;
	setAttr -s 7 ".kot[1:6]"  5 3 5 1 3 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[4:6]"  1 1 1;
	setAttr -s 7 ".koy[4:6]"  0 0 0;
createNode animCurveTU -n "animCurveTU104";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 1 1 4 1 14 1 20 1 24 1 45 1;
	setAttr -s 7 ".kit[1:6]"  10 3 10 1 3 1;
	setAttr -s 7 ".kot[1:6]"  10 3 10 1 3 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[4:6]"  1 1 1;
	setAttr -s 7 ".koy[4:6]"  0 0 0;
createNode animCurveTA -n "animCurveTA296";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -10.173354040024311 1 -10.173354040024311 
		4 -10.173354040024311 14 -10.173354040024311 20 -10.173354040024311 24 -10.173354040024311 
		45 -10.173354040024311;
	setAttr -s 7 ".kit[1:6]"  10 3 10 1 3 1;
	setAttr -s 7 ".kot[1:6]"  10 3 10 1 3 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[4:6]"  1 1 1;
	setAttr -s 7 ".koy[4:6]"  0 0 0;
createNode animCurveTA -n "animCurveTA297";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 4 0 14 0 20 0 24 0 45 0;
	setAttr -s 7 ".kit[1:6]"  10 3 10 1 3 1;
	setAttr -s 7 ".kot[1:6]"  10 3 10 1 3 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[4:6]"  1 1 1;
	setAttr -s 7 ".koy[4:6]"  0 0 0;
createNode animCurveTA -n "animCurveTA298";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 4 26.194203538147455 14 23.776867748077208 
		20 0 24 0 45 0;
	setAttr -s 7 ".kit[1:6]"  10 3 10 1 3 1;
	setAttr -s 7 ".kot[1:6]"  10 3 10 1 3 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[4:6]"  1 1 1;
	setAttr -s 7 ".koy[4:6]"  0 0 0;
createNode animCurveTL -n "animCurveTL73";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 4 0.1698973042298913 14 0.15421830740323628 
		20 0 24 0 45 0;
	setAttr -s 7 ".kit[0:6]"  3 10 3 10 1 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 3 10 1 10 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[4:6]"  1 1 1;
	setAttr -s 7 ".koy[4:6]"  0 0 0;
createNode animCurveTL -n "animCurveTL74";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.643246524321337 1 0.643246524321337 
		4 0.60384207285350455 14 0.60747851824809562 20 0.643246524321337 24 0.643246524321337 
		45 0.643246524321337;
	setAttr -s 7 ".kit[0:6]"  3 10 3 10 1 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 3 10 1 10 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[4:6]"  1 1 1;
	setAttr -s 7 ".koy[4:6]"  0 0 0;
createNode animCurveTL -n "animCurveTL75";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.10481400598920043 1 0.10481400598920043 
		4 0.10481400598920043 14 0.10481400598920043 20 0.10481400598920043 24 0.10481400598920043 
		45 0.10481400598920043;
	setAttr -s 7 ".kit[0:6]"  3 10 3 10 1 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 3 10 1 10 1;
	setAttr -s 7 ".kix[4:6]"  1 1 1;
	setAttr -s 7 ".kiy[4:6]"  0 0 0;
	setAttr -s 7 ".kox[4:6]"  1 1 1;
	setAttr -s 7 ".koy[4:6]"  0 0 0;
createNode animCurveTA -n "animCurveTA299";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA300";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA301";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU105";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA302";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA303";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA304";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA305";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA306";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA307";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA308";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA309";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA310";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU106";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 4 1 10 1 19 1 45 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA311";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 40.718223104721211 4 21.354752174428203 
		10 11.592985498093574 19 8.9028094124160635 35 18.637438270559283 45 40.718223104721211;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTA -n "animCurveTA312";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -38.301705751263519 4 -24.583334489533748 
		10 0.067678307541174904 19 -3.4732393266198107 35 -28.250765434535548 45 -38.301705751263512;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTA -n "animCurveTA313";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 21.733945627788874 4 9.4554176126178522 
		10 67.784404904594169 19 34.55161596033394 35 45.137010172284633 45 21.733945627788874;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTU -n "animCurveTU107";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 0 9 0 13 0 17 0 28 0 45 0;
	setAttr -s 7 ".kit[1:6]"  9 3 9 3 1 1;
	setAttr -s 7 ".kot[1:6]"  5 3 5 3 1 1;
	setAttr -s 7 ".kix[5:6]"  1 1;
	setAttr -s 7 ".kiy[5:6]"  0 0;
	setAttr -s 7 ".kox[5:6]"  1 1;
	setAttr -s 7 ".koy[5:6]"  0 0;
createNode animCurveTU -n "animCurveTU108";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 4 0 9 0 13 0 17 0 28 0 45 0;
	setAttr -s 7 ".kit[1:6]"  9 3 9 3 1 1;
	setAttr -s 7 ".kot[1:6]"  5 3 5 3 1 1;
	setAttr -s 7 ".kix[5:6]"  1 1;
	setAttr -s 7 ".kiy[5:6]"  0 0;
	setAttr -s 7 ".kox[5:6]"  1 1;
	setAttr -s 7 ".koy[5:6]"  0 0;
createNode animCurveTU -n "animCurveTU109";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1 4 1 9 1 13 1 17 1 28 1 45 1;
	setAttr -s 7 ".kit[1:6]"  10 3 10 3 1 1;
	setAttr -s 7 ".kot[1:6]"  10 3 10 3 1 1;
	setAttr -s 7 ".kix[5:6]"  1 1;
	setAttr -s 7 ".kiy[5:6]"  0 0;
	setAttr -s 7 ".kox[5:6]"  1 1;
	setAttr -s 7 ".koy[5:6]"  0 0;
createNode animCurveTA -n "animCurveTA314";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 17.962181958626559 2 3.5146983960577018 
		4 -3.1380595582234241 9 -6.4757932824263307 13 -6.5126228392440453 17 -7.3329175138203935 
		20 8.409751516106601 22 5.077163487108785 26 12.813392486993376 28 17.962181958626559 
		45 17.962181958626559;
	setAttr -s 11 ".kit[0:10]"  3 10 10 3 10 3 3 10 
		10 1 1;
	setAttr -s 11 ".kot[0:10]"  3 10 10 3 10 3 3 10 
		10 1 1;
	setAttr -s 11 ".kix[9:10]"  1 1;
	setAttr -s 11 ".kiy[9:10]"  0 0;
	setAttr -s 11 ".kox[9:10]"  1 1;
	setAttr -s 11 ".koy[9:10]"  0 0;
createNode animCurveTA -n "animCurveTA315";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 1.5528128972019624 4 1.8346295661915579 
		9 -4.0148059051521345 13 -4.0286854055559216 17 -4.3378197327311785 20 -3.8204108349514478 
		22 -4.6093703299581268 26 -0.70860819574910383 28 0 45 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 3 10 3 3 10 
		10 1 1;
	setAttr -s 11 ".kot[0:10]"  3 10 10 3 10 3 3 10 
		10 1 1;
	setAttr -s 11 ".kix[9:10]"  1 1;
	setAttr -s 11 ".kiy[9:10]"  0 0;
	setAttr -s 11 ".kox[9:10]"  1 1;
	setAttr -s 11 ".koy[9:10]"  0 0;
createNode animCurveTA -n "animCurveTA316";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 1 12.553976955410148 2 16.727183360902249 
		4 28.062927174304779 9 8.2631876734566809 13 8.7384411989293884 17 19.323633357185148 
		20 9.9740342946581144 22 -5.8517794706186583 26 -11.000730159389036 28 0 45 0;
	setAttr -s 12 ".kit[0:11]"  3 10 10 9 3 10 3 10 
		10 3 1 1;
	setAttr -s 12 ".kot[0:11]"  3 10 10 9 3 10 3 10 
		10 3 1 1;
	setAttr -s 12 ".kix[10:11]"  1 1;
	setAttr -s 12 ".kiy[10:11]"  0 0;
	setAttr -s 12 ".kox[10:11]"  1 1;
	setAttr -s 12 ".koy[10:11]"  0 0;
createNode animCurveTL -n "animCurveTL76";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 2 0.22670329451854343 4 0.21476938631835435 
		9 0.055051504122974465 13 0.058019324086085573 17 0.13781525642442499 20 0.11423126093056886 
		22 0.065314513044128816 25 0.015581937916209827 26 0 45 0;
	setAttr -s 11 ".kit[0:10]"  3 3 9 3 10 9 9 9 
		10 1 1;
	setAttr -s 11 ".kot[0:10]"  3 3 9 3 10 9 9 9 
		10 1 1;
	setAttr -s 11 ".kix[9:10]"  1 1;
	setAttr -s 11 ".kiy[9:10]"  0 0;
	setAttr -s 11 ".kox[9:10]"  1 1;
	setAttr -s 11 ".koy[9:10]"  0 0;
createNode animCurveTL -n "animCurveTL77";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.64789329560123088 1 -0.65192482088618187 
		2 -0.7513737111731793 4 -0.93494089623535126 9 -0.90265593302622937 13 -0.90288765990244724 
		17 -0.92450263679031741 20 -0.82869717577038293 26 -0.64789329560123088 45 -0.64789329560123088;
	setAttr -s 10 ".kit[1:9]"  10 10 10 3 3 3 1 1 
		1;
	setAttr -s 10 ".kot[1:9]"  10 10 10 3 3 3 1 1 
		1;
	setAttr -s 10 ".kix[7:9]"  0.59309172630310059 1 1;
	setAttr -s 10 ".kiy[7:9]"  0.80513495206832886 0 0;
	setAttr -s 10 ".kox[7:9]"  0.59309172630310059 1 1;
	setAttr -s 10 ".koy[7:9]"  0.80513489246368408 0 0;
createNode animCurveTL -n "animCurveTL78";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.07395615046270454 2 -0.047721001070511818 
		4 -0.021485851678319096 9 -0.021485851678319096 13 -0.021485851678319096 17 -0.021485851678319096 
		20 -0.14720845457560561 26 -0.07395615046270454 45 -0.07395615046270454;
	setAttr -s 9 ".kit[0:8]"  3 10 10 3 10 3 9 1 
		1;
	setAttr -s 9 ".kot[0:8]"  3 10 10 3 10 3 9 1 
		1;
	setAttr -s 9 ".kix[7:8]"  1 1;
	setAttr -s 9 ".kiy[7:8]"  0 0;
	setAttr -s 9 ".kox[7:8]"  1 1;
	setAttr -s 9 ".koy[7:8]"  0 0;
createNode animCurveTA -n "animCurveTA317";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA318";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA319";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU110";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA320";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA321";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA322";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA323";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA324";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA325";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA326";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA327";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA328";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA329";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -10.753373031419716 6 9.1018738191185093 
		11 -5.2551956399186777 16 -51.595105046324221 23 -21.636285691827716 30 -9.6220112915636413 
		36 -1.7047935355202779 45 -10.753373031419716;
	setAttr -s 8 ".kit[0:7]"  9 10 10 3 10 10 10 1;
	setAttr -s 8 ".kot[0:7]"  9 10 10 3 10 10 10 1;
	setAttr -s 8 ".kix[7]"  0.90613621473312378;
	setAttr -s 8 ".kiy[7]"  0.42298597097396851;
	setAttr -s 8 ".kox[7]"  0.90613621473312378;
	setAttr -s 8 ".koy[7]"  0.42298597097396851;
createNode animCurveTA -n "animCurveTA330";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -4.9387346018875373 6 7.1630010534880899 
		11 4.4771524255181623 16 2.367195465618277 23 3.4147380496708313 30 2.4148058222619961 
		36 9.831089020803363 45 -4.9387346018875373;
	setAttr -s 8 ".kit[0:7]"  9 10 9 10 10 10 10 1;
	setAttr -s 8 ".kot[0:7]"  9 10 9 10 10 10 10 1;
	setAttr -s 8 ".kix[7]"  0.96680086851119995;
	setAttr -s 8 ".kiy[7]"  0.25553107261657715;
	setAttr -s 8 ".kox[7]"  0.96680086851119995;
	setAttr -s 8 ".koy[7]"  0.25553107261657715;
createNode animCurveTA -n "animCurveTA331";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 22.393157938684443 6 29.674297079877046 
		11 29.441558932381174 16 26.932884976298588 23 26.002185311954605 30 18.523449450317781 
		36 27.409017791347789 45 22.393157938684443;
	setAttr -s 8 ".kit[0:7]"  9 1 10 9 10 10 10 1;
	setAttr -s 8 ".kot[0:7]"  9 1 10 9 10 10 10 1;
	setAttr -s 8 ".kix[1:7]"  0.99134081602096558 1 0.98892605304718018 
		1 0.99839848279953003 0.99099987745285034 0.99922788143157959;
	setAttr -s 8 ".kiy[1:7]"  0.13131427764892578 0 -0.14840912818908691 
		0 0.056571997702121735 0.13386258482933044 -0.039289865642786026;
	setAttr -s 8 ".kox[1:7]"  0.99134081602096558 1 0.98892605304718018 
		1 0.99839848279953003 0.99099987745285034 0.99922788143157959;
	setAttr -s 8 ".koy[1:7]"  0.13131426274776459 0 -0.14840912818908691 
		0 0.056571997702121735 0.13386258482933044 -0.039289865642786026;
createNode animCurveTA -n "animCurveTA332";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -4.0865779949808214 4 -20.506252846786612 
		9 -57.980884942279786 15 -32.527103651767654 25 -4.1270044832173385 45 -4.0865779949808232;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA333";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -10.471027640707172 4 -8.0411895451543689 
		9 -5.1208821830827205 15 6.6207538140206159 25 -1.5060205700733693 45 -10.471027640707174;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 0.95827138423919678 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 -0.28585988283157349 0;
	setAttr -s 6 ".kox[2:5]"  1 1 0.95827138423919678 1;
	setAttr -s 6 ".koy[2:5]"  0 0 -0.28585988283157349 0;
createNode animCurveTA -n "animCurveTA334";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -1.7475532445702493 4 -1.9774684670235461 
		9 11.836878268409473 15 1.6197655693571409 25 14.131377387149604 45 -1.7475532445702497;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 0.99827742576599121 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 -0.058669563382863998 0;
	setAttr -s 6 ".kox[2:5]"  1 1 0.99827742576599121 1;
	setAttr -s 6 ".koy[2:5]"  0 0 -0.058669563382863998 0;
createNode animCurveTU -n "animCurveTU111";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 4 1 10 1 19 1 45 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA335";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 20.69101533741409 4 -1.6162052039129922 
		10 -40.486340253709876 19 -4.208420756426106 26 24.869445515812927 35 36.003874475868926 
		45 20.69101533741409;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "animCurveTA336";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -8.3978566024888135 4 9.5687834797906905 
		10 19.6709327674339 19 8.9485768867083326 26 4.7864081777033709 35 -2.0323765001757699 
		45 -8.3978566024888117;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "animCurveTA337";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 2.8255796210686652 4 2.4202675016350841 
		10 19.512682344036346 19 18.608882869436535 26 14.054274703764998 35 8.234257850293675 
		45 2.8255796210686639;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTU -n "animCurveTU112";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 4 0 22 0 45 0;
	setAttr -s 4 ".kit[0:3]"  3 10 10 1;
	setAttr -s 4 ".kot[0:3]"  3 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
createNode animCurveTA -n "animCurveTA338";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 4 12.486809844169095 7 17.348395508776054 
		12 -8.6125875171619324 15 -11.518464117428801 22 19.61636995605399 26 -0.88058308746996727 
		32 1.8195536654098392 37 -6.0083948649878067 40 7.1153899092335005 45 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[10]"  1;
	setAttr -s 11 ".koy[10]"  0;
createNode animCurveTA -n "animCurveTA339";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 4 -15.36506783577841 7 5.3217156147175206 
		12 55.793193622000203 22 -41.337056071338687 26 35.166610815317718 32 -18.749490771454788 
		37 10.390079607987868 40 28.054644587938629 45 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 1;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 1;
	setAttr -s 10 ".kix[9]"  1;
	setAttr -s 10 ".kiy[9]"  0;
	setAttr -s 10 ".kox[9]"  1;
	setAttr -s 10 ".koy[9]"  0;
createNode animCurveTA -n "animCurveTA340";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 4 0.29076111825651108 7 -8.1287252109865733 
		12 8.461833013221284 22 21.709394560506905 26 14.648254326297751 32 6.5833453752832263 
		37 8.4785185599320823 40 -1.4700064446883332 45 0;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 1;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 1;
	setAttr -s 10 ".kix[9]"  1;
	setAttr -s 10 ".kiy[9]"  0;
	setAttr -s 10 ".kox[9]"  1;
	setAttr -s 10 ".koy[9]"  0;
createNode animCurveTA -n "animCurveTA341";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -17.821366541589882 3 -5.1839966950136525 
		6 16.618408566455155 8 15.345202947465511 11 9.5664205939580942 16 -6.4026719535116436 
		19 -15.255846048874433 22 -4.195816406775684 26 -12.933812660041635 32 -19.962776076693714 
		40 -16.720130856089654 45 -17.821366541589882;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 12 ".kix[11]"  1;
	setAttr -s 12 ".kiy[11]"  0;
	setAttr -s 12 ".kox[11]"  1;
	setAttr -s 12 ".koy[11]"  0;
createNode animCurveTA -n "animCurveTA342";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -12.005893876475762 3 -34.042495585626988 
		6 -18.132948300768934 8 -7.9504587099700803 11 4.1161607517448147 16 43.497031646834451 
		19 34.029681229711016 22 17.259293391785846 26 4.6200543675445136 32 24.656830254782257 
		40 -1.4707341746816123 45 -12.005893876475762;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 12 ".kix[11]"  1;
	setAttr -s 12 ".kiy[11]"  0;
	setAttr -s 12 ".kox[11]"  1;
	setAttr -s 12 ".koy[11]"  0;
createNode animCurveTA -n "animCurveTA343";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 9.1378572146953019 3 59.245256159494701 
		6 83.468916142008737 8 60.842938197102377 11 53.041838852235387 16 26.451710857842663 
		19 39.614867268829947 22 40.263806928173018 26 20.429024220112705 32 19.759667100247817 
		40 4.3751402962617618 45 9.1378572146953019;
	setAttr -s 12 ".kit[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 12 ".kot[0:11]"  3 10 10 10 10 10 10 10 
		10 10 10 1;
	setAttr -s 12 ".kix[11]"  1;
	setAttr -s 12 ".kiy[11]"  0;
	setAttr -s 12 ".kox[11]"  1;
	setAttr -s 12 ".koy[11]"  0;
createNode animCurveTA -n "animCurveTA344";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 -28.841216077843235 2 -121.5370686461485 
		3 -59.521102649395282 5 -104.2734544736637 9 -90.604964448472401 12 -60.448252507209112 
		18 -151.34541846970026 21 -163.83368413568118 28 -164.4281157272992 30 -254.67411260447349 
		32 -180.73774714646024 35 -154.13587054230263 40 -193.628055611935 43 -196.38853420774086 
		45 -208.84121607784328;
	setAttr -s 15 ".kit[0:14]"  1 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 15 ".kot[0:14]"  1 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 15 ".kix[0:14]"  1 0.18357963860034943 0.31499248743057251 
		0.34589689970016479 0.29177898168563843 0.27229374647140503 0.16400745511054993 1 
		1 0.42417439818382263 0.094556152820587158 0.76432210206985474 1 1 1;
	setAttr -s 15 ".kiy[0:14]"  0 -0.9830048680305481 0.94909417629241943 
		-0.93827253580093384 0.9564858078956604 -0.96221423149108887 -0.98645907640457153 
		0 0 -0.90558052062988281 0.99551951885223389 -0.64483469724655151 0 0 0;
	setAttr -s 15 ".kox[0:14]"  1 0.18357963860034943 0.31499248743057251 
		0.34589689970016479 0.29177898168563843 0.27229374647140503 0.16400745511054993 1 
		1 0.42417439818382263 0.094556152820587158 0.76432210206985474 1 1 1;
	setAttr -s 15 ".koy[0:14]"  0 -0.9830048680305481 0.94909417629241943 
		-0.93827253580093384 0.9564858078956604 -0.96221423149108887 -0.98645907640457153 
		0 0 -0.90558052062988281 0.99551951885223389 -0.64483469724655151 0 0 0;
createNode animCurveTA -n "animCurveTA345";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 -21.716766331039956 2 -23.519484184576363 
		3 -17.019913797008073 5 42.587874462448276 9 97.354690836672034 12 78.630422359950074 
		18 -124.83856826332993 21 -200.00497473439398 28 -139.86947085115875 30 -63.130987076790298 
		32 -195.02597605123665 35 -195.50002595349443 40 -126.81874177882618 43 -170.64764437236576 
		45 -158.28323366896001;
	setAttr -s 15 ".kit[0:14]"  1 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 15 ".kot[0:14]"  1 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 15 ".kix[0:14]"  1 1 0.086347095668315887 0.099690593779087067 
		0.34777006506919861 0.07712893933057785 0.061571929603815079 0.78582102060317993 
		0.1246020570397377 0.13719509541988373 1 1 0.5237269401550293 0.29041403532028198 
		1;
	setAttr -s 15 ".kiy[0:14]"  0 0 0.99626505374908447 0.99501848220825195 
		0.93757987022399902 -0.9970211386680603 -0.99810266494750977 -0.61845391988754272 
		0.992206871509552 -0.99054402112960815 0 0 0.85188615322113037 -0.95690107345581055 
		0;
	setAttr -s 15 ".kox[0:14]"  1 1 0.086347095668315887 0.099690593779087067 
		0.34777006506919861 0.07712893933057785 0.061571929603815079 0.78582102060317993 
		0.1246020570397377 0.13719509541988373 1 1 0.5237269401550293 0.29041403532028198 
		1;
	setAttr -s 15 ".koy[0:14]"  0 0 0.99626505374908447 0.99501848220825195 
		0.93757987022399902 -0.9970211386680603 -0.99810266494750977 -0.61845391988754272 
		0.992206871509552 -0.99054402112960815 0 0 0.85188615322113037 -0.95690107345581055 
		0;
createNode animCurveTA -n "animCurveTA346";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 23.535235892507558 2 73.183210352803798 
		3 109.70644469526771 5 34.422973219257663 9 116.91277486604085 12 104.61248337972127 
		18 77.104547006131256 21 82.284495123870272 28 219.06614653649081 30 237.42248793492956 
		32 243.01377433638189 35 261.62334228121256 40 168.57295548435374 43 202.56524178898229 
		45 203.53523589250759;
	setAttr -s 15 ".kit[0:14]"  1 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 15 ".kot[0:14]"  1 10 10 10 10 10 10 10 
		10 10 10 10 10 10 1;
	setAttr -s 15 ".kix[0:14]"  1 0.066344134509563446 0.1462319940328598 
		0.84652233123779297 0.18710650503635406 0.39641302824020386 0.61000853776931763 0.13333231210708618 
		0.11012256145477295 0.30391669273376465 0.36704432964324951 0.2010573148727417 0.25046312808990479 
		1 1;
	setAttr -s 15 ".kiy[0:14]"  0 0.99779677391052246 -0.9892503023147583 
		0.53235328197479248 0.98233968019485474 -0.91807228326797485 -0.79239487648010254 
		0.99107140302658081 0.99391800165176392 0.95269858837127686 0.93020343780517578 -0.97957944869995117 
		-0.96812611818313599 0 0;
	setAttr -s 15 ".kox[0:14]"  1 0.066344134509563446 0.1462319940328598 
		0.84652233123779297 0.18710650503635406 0.39641302824020386 0.61000853776931763 0.13333231210708618 
		0.11012256145477295 0.30391669273376465 0.36704432964324951 0.2010573148727417 0.25046312808990479 
		1 1;
	setAttr -s 15 ".koy[0:14]"  0 0.99779677391052246 -0.9892503023147583 
		0.53235328197479248 0.98233968019485474 -0.91807228326797485 -0.79239487648010254 
		0.99107140302658081 0.99391800165176392 0.95269858837127686 0.93020343780517578 -0.97957944869995117 
		-0.96812611818313599 0 0;
createNode animCurveTL -n "animCurveTL79";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 9 0 18 0 32 0 35 0 45 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL80";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 9 0 18 0 32 0 35 0 45 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL81";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 2 0 9 0 18 0 32 0 35 0 45 0;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "animCurveTU113";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 2 4 2 10 2 19 2 45 2;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 1;
	setAttr -s 5 ".kot[0:4]"  3 5 5 5 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU114";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 1;
	setAttr -s 5 ".kot[0:4]"  3 5 5 5 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA347";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -24.093441664171177 4 -24.093441664171177 
		10 -24.093441664171177 19 -24.093441664171177 45 -24.093441664171177;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA348";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 49.48465546224881 4 49.48465546224881 
		10 49.48465546224881 19 49.48465546224881 45 49.48465546224881;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA349";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 58.801792680015588 4 58.801792680015588 
		10 58.801792680015588 19 58.801792680015588 45 58.801792680015588;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL82";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.2755255474500937 4 -1.2755255474500937 
		10 -1.2755255474500937 18 -1.2755255474500937 45 -1.2755255474500937;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL83";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.4392043230118035 4 -1.4392043230118035 
		10 -1.4392043230118035 18 -1.4392043230118035 45 -1.4392043230118035;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL84";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -2.1802956492995231 4 -2.1802956492995231 
		10 -2.1802956492995231 18 -2.1802956492995231 45 -2.1802956492995231;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL85";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 4 0.73920465205973374 6 -0.62638337470158412 
		10 -0.46435553086218284 12 -0.57581223473908749 14 0.41637436613386059 16 -1.650252097525998 
		22 0 31 0 38 -0.51478767014608917 45 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[10]"  1;
	setAttr -s 11 ".koy[10]"  0;
createNode animCurveTL -n "animCurveTL86";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 4 1.8117386561850224 6 1.0854143702362711 
		10 1.6072285307941179 12 -1.0007141055303468 14 -2.8628566793893486 16 -2.5645657179675987 
		22 0 31 0 38 -0.93272119380132978 45 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[10]"  1;
	setAttr -s 11 ".koy[10]"  0;
createNode animCurveTL -n "animCurveTL87";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 4 2.5760549047536934 6 2.9823994816928159 
		10 2.8116109882702602 12 2.9582674152648814 14 1.175706211434741 16 0.95697602196437637 
		22 0 31 0 38 -0.35663423120542703 45 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kot[0:10]"  3 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[10]"  1;
	setAttr -s 11 ".koy[10]"  0;
createNode animCurveTA -n "animCurveTA350";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1.1134085745786892 6 0.27695230167517748 
		10 -32.968730989372823 14 -25.797795932458222 19 -81.365607037112781 26 -9.9680300524797687 
		30 8.0323403456533882 35 -12.113255656368882 39 -6.9126267350631228 45 1.1134085745786884;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 3;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 3;
createNode animCurveTA -n "animCurveTA351";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -5.3180374758492821 6 -12.525391436779376 
		10 23.908895596838398 14 55.300038788941642 19 36.3257162621749 26 -11.016988994813479 
		30 10.170063197187226 35 -7.126848066638277 39 1.6945068213787111 45 -5.3180374758492821;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 3;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 3;
createNode animCurveTA -n "animCurveTA352";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 7.8609313736722894 6 -51.548148464637343 
		10 -53.591967744193056 14 -35.161249065805926 19 -38.811653092391992 26 -9.0230239720726466 
		30 -0.77673362340982532 35 3.6893002675193074 39 9.8235627295404484 45 7.8609313736722894;
	setAttr -s 10 ".kit[0:9]"  3 10 10 10 10 10 10 10 
		10 3;
	setAttr -s 10 ".kot[0:9]"  3 10 10 10 10 10 10 10 
		10 3;
createNode animCurveTL -n "animCurveTL88";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 6 0.1413568745915092 14 0.11025317728192763 
		19 0.115838177921988 26 0.13035140993612263 30 0.13433335079971895 35 0.085518088285319746 
		45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL89";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 6 0.03676153298087112 14 0.051599933954219537 
		19 0.028837477107761099 26 -0.044995594934579206 30 -0.04654220530040222 35 -0.031834832836201553 
		45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 3;
createNode animCurveTL -n "animCurveTL90";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 6 -0.1241750985362477 14 -0.15607872185617666 
		19 -0.14302015225020492 26 -0.065525036776614171 30 -0.099775662595908407 35 -0.043268325958244869 
		45 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 3;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA353";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA354";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA355";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL91";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 18 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL92";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 18 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL93";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 18 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU115";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 8 0 16 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 1;
	setAttr -s 5 ".kot[0:4]"  3 5 5 5 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA356";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -5.1107219305963252 4 -5.1107219305963252 
		8 -14.047847344021836 16 -8.4120223294582903 26 -0.58331128272999144 33 -10.090173467483643 
		38 -10.346259378860639 45 -5.1107219305963252;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 1;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTA -n "animCurveTA357";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 8.2811672786141717 4 8.2811672786141717 
		8 20.007973036497003 16 1.2378349094211929 26 10.945142463014767 33 4.6903384228206821 
		38 5.1590597409050991 45 8.2811672786141717;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 1;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTA -n "animCurveTA358";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.92645454014921158 4 -0.92645454014921158 
		8 1.4651478643416371 16 -7.9969206892813158 26 -1.8408537601179968 33 -2.3145275992173358 
		38 -2.0017405493261062 45 -0.92645454014921158;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 1;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTL -n "animCurveTL94";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.046856395845859107 4 -0.046856395845859107 
		8 0.027456835983275522 16 -0.037717435356428977 33 -0.038400581879427971 45 -0.046856395845859107;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTL -n "animCurveTL95";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.023348763690700665 4 -0.023348763690700665 
		8 0.072003948591616102 16 0.010473576798310336 33 0.0011774635061893059 45 -0.023348763690700665;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTL -n "animCurveTL96";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.13506113021862395 4 -0.13506113021862395 
		8 -0.022249163855837195 16 -0.11976456324880895 33 -0.12357615742481698 45 -0.13506113021862395;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTA -n "animCurveTA359";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -1.6266160090263075 4 -15.083130918865537 
		10 36.382017748196411 18 -13.815251161824971 27 -9.1357215458083143 34 -12.553389182939027 
		45 -1.6266160090263075;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "animCurveTA360";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 2.8499857758927387 4 2.1798617974099983 
		10 -17.25867149246778 18 -7.3146941888837533 27 -16.746980162532562 34 -7.593189163439849 
		45 2.8499857758927387;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "animCurveTA361";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -25.210898828531619 4 6.3984429747700657 
		10 -18.944143073630912 18 20.888614508079222 27 -13.464143819614455 34 0.31882320404365522 
		45 -25.210898828531619;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTL -n "animCurveTL97";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.011193700785458628 4 -0.011193700785458628 
		10 -0.01938279934020655 18 -0.011193700785458628 27 0.051525557728545113 45 -0.011193700785458628;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTL -n "animCurveTL98";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.020021267836214246 4 -0.020021267836214246 
		10 0.15630002769459087 18 -0.020021267836214246 27 -0.08318625485089412 45 -0.020021267836214246;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTL -n "animCurveTL99";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.032441787830836878 4 0.032441787830836878 
		10 0.081755044062836707 18 0.032441787830836878 27 0.13011260338720571 45 0.032441787830836878;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTA -n "animCurveTA362";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA363";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA364";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL100";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 18 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL101";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 18 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL102";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 18 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA365";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -15.609971163878811 4 49.823660253718593 
		9 52.147297274099472 15 29.155459283880422 30 -29.564228093943846 45 -15.609971163878811;
	setAttr -s 6 ".kit[0:5]"  3 10 3 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 3 10 10 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTA -n "animCurveTA366";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 8.3116042646716988 4 -18.776618753527689 
		9 -19.738558301398992 15 -7.3487692814886785 30 5.8448219024503691 45 8.3116042646716988;
	setAttr -s 6 ".kit[0:5]"  3 10 3 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 3 10 10 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTA -n "animCurveTA367";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 14.458598883932659 4 1.3423975869706912 
		9 -0.11163702821892882 15 -3.6595133156698987 30 2.128869364838712 45 14.458598883932655;
	setAttr -s 6 ".kit[0:5]"  3 10 9 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 9 10 10 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTL -n "animCurveTL103";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.18868131369562219 4 -0.25386789708634933 
		9 -0.25618276109614507 15 -0.24689090984872458 24 -0.14226230513446031 38 -0.24591165334999202 
		45 -0.18868131369562219;
	setAttr -s 7 ".kit[0:6]"  3 10 3 1 10 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 3 1 10 10 1;
	setAttr -s 7 ".kix[3:6]"  0.98843270540237427 0.99999916553497314 
		0.99780851602554321 1;
	setAttr -s 7 ".kiy[3:6]"  0.15166012942790985 0.0012772900518029928 
		-0.066167548298835754 0;
	setAttr -s 7 ".kox[3:6]"  0.98843276500701904 0.99999916553497314 
		0.99780851602554321 1;
	setAttr -s 7 ".koy[3:6]"  0.15166015923023224 0.0012772900518029928 
		-0.066167548298835754 0;
createNode animCurveTL -n "animCurveTL104";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0.23059098815955009 4 -0.35133319401423763 
		9 -0.36522744778615657 15 -0.19831754122519929 24 0.28590811588972564 30 0.18216961355656508 
		38 0.25194133081444992 45 0.23059098815955009;
	setAttr -s 8 ".kit[0:7]"  9 10 3 10 10 10 10 1;
	setAttr -s 8 ".kot[0:7]"  9 10 3 10 10 10 10 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTL -n "animCurveTL105";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.049918713102953649 4 -0.020123968697297892 
		9 -0.022611279349508628 15 -0.11352333130285971 24 -0.15150611101677752 38 0.0012273667251312959 
		45 0.049918713102953649;
	setAttr -s 7 ".kit[0:6]"  3 10 3 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 3 10 10 10 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTU -n "animCurveTU116";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 7 0 17 0 34 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 9 9 1 1;
	setAttr -s 5 ".kot[0:4]"  3 5 5 1 1;
	setAttr -s 5 ".kix[3:4]"  1 1;
	setAttr -s 5 ".kiy[3:4]"  0 0;
	setAttr -s 5 ".kox[3:4]"  1 1;
	setAttr -s 5 ".koy[3:4]"  0 0;
createNode animCurveTU -n "animCurveTU117";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.084155571970393403 7 0.084155571970393403 
		17 0.084155571970393403 34 0.084155571970393403 45 0.084155571970393403;
	setAttr -s 5 ".kit[0:4]"  3 10 10 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 1 1;
	setAttr -s 5 ".kix[3:4]"  1 1;
	setAttr -s 5 ".kiy[3:4]"  0 0;
	setAttr -s 5 ".kox[3:4]"  1 1;
	setAttr -s 5 ".koy[3:4]"  0 0;
createNode animCurveTL -n "animCurveTL106";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.067207227343123899 7 -0.24461147574916514 
		17 -0.2918200170932147 32 0.067207227343123899 45 0.067207227343123899;
	setAttr -s 5 ".kit[0:4]"  3 10 10 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 1 1;
	setAttr -s 5 ".kix[3:4]"  1 1;
	setAttr -s 5 ".kiy[3:4]"  0 0;
	setAttr -s 5 ".kox[3:4]"  1 1;
	setAttr -s 5 ".koy[3:4]"  0 0;
createNode animCurveTL -n "animCurveTL107";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.20472824713235571 7 -0.29248940580645189 
		17 -0.27376652023203329 32 -0.20472824713235571 45 -0.20472824713235571;
	setAttr -s 5 ".kit[0:4]"  3 10 10 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 1 1;
	setAttr -s 5 ".kix[3:4]"  1 1;
	setAttr -s 5 ".kiy[3:4]"  0 0;
	setAttr -s 5 ".kox[3:4]"  1 1;
	setAttr -s 5 ".koy[3:4]"  0 0;
createNode animCurveTL -n "animCurveTL108";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.20941646546924442 7 -0.017675745878774518 
		17 -0.019632420943457213 23 -0.091564331254932282 32 0.20941646546924442 45 0.20941646546924442;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 1 1;
	setAttr -s 6 ".kix[4:5]"  1 1;
	setAttr -s 6 ".kiy[4:5]"  0 0;
	setAttr -s 6 ".kox[4:5]"  1 1;
	setAttr -s 6 ".koy[4:5]"  0 0;
createNode animCurveTU -n "animCurveTU118";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 22 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 1;
	setAttr -s 5 ".kot[0:4]"  3 5 5 5 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU119";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.084155864375844894 4 0.084155864375844894 
		10 0.084155864375844894 22 0.084155864375844894 45 0.084155864375844894;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL109";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0 10 0 18 0 22 0 45 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTL -n "animCurveTL110";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.40088449385078673 4 -0.40088449385078673 
		10 -0.40088449385078673 18 -0.40088449385078673 22 -0.40088449385078673 45 -0.40088449385078673;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTL -n "animCurveTL111";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 -0.69609418843799409 4 -0.69609418843799409 
		10 -0.75341648483050139 18 -0.69609418843799409 22 -0.47578599046124803 32 -0.67617707906907221 
		39 -0.79210615385516792 45 -0.69609418843799409;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 1;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 1;
	setAttr -s 8 ".kix[7]"  1;
	setAttr -s 8 ".kiy[7]"  0;
	setAttr -s 8 ".kox[7]"  1;
	setAttr -s 8 ".koy[7]"  0;
createNode animCurveTU -n "animCurveTU120";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 4 1 10 1 19 1 45 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU121";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 4 1 10 1 19 1 45 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU122";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 4 1 10 1 19 1 45 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA383";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA384";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA385";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL112";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 18 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL113";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 18 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL114";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 18 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU123";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 4 1 10 1 19 1 45 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU124";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 4 1 10 1 19 1 45 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU125";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 4 1 10 1 19 1 45 1;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA386";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA387";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA388";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL115";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 18 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL116";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 18 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL117";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 18 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA368";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 45 0;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr -s 2 ".kox[1]"  1;
	setAttr -s 2 ".koy[1]"  0;
createNode animCurveTA -n "animCurveTA369";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 45 0;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr -s 2 ".kox[1]"  1;
	setAttr -s 2 ".koy[1]"  0;
createNode animCurveTA -n "animCurveTA370";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 45 0;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr -s 2 ".kox[1]"  1;
	setAttr -s 2 ".koy[1]"  0;
createNode animCurveTA -n "animCurveTA371";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 45 0;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr -s 2 ".kox[1]"  1;
	setAttr -s 2 ".koy[1]"  0;
createNode animCurveTA -n "animCurveTA372";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 45 0;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr -s 2 ".kox[1]"  1;
	setAttr -s 2 ".koy[1]"  0;
createNode animCurveTA -n "animCurveTA373";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 45 0;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr -s 2 ".kox[1]"  1;
	setAttr -s 2 ".koy[1]"  0;
createNode animCurveTA -n "animCurveTA380";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 45 0;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr -s 2 ".kox[1]"  1;
	setAttr -s 2 ".koy[1]"  0;
createNode animCurveTA -n "animCurveTA381";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 45 0;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr -s 2 ".kox[1]"  1;
	setAttr -s 2 ".koy[1]"  0;
createNode animCurveTA -n "animCurveTA382";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 45 0;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr -s 2 ".kox[1]"  1;
	setAttr -s 2 ".koy[1]"  0;
createNode animCurveTA -n "animCurveTA377";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -18.592620239620459 4 -12.702162368105455 
		10 -18.300551863250487 19 -16.410219683961525 26 -17.597149228720681 34 -13.593619960823295 
		45 -18.592620239620459;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "animCurveTA378";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -4.0495369920864128 4 -27.82912796761719 
		10 -13.870037367659586 19 13.354885732643053 26 11.611425199306886 34 -5.9711924098825779 
		45 -4.0495369920864128;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "animCurveTA379";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -24.718935474963271 4 -35.631337497417363 
		10 -37.362052663575824 19 -29.210822535159604 26 -1.8310357815158769 34 -53.835238305350423 
		45 -24.718935474963271;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 1;
	setAttr -s 7 ".kix[6]"  1;
	setAttr -s 7 ".kiy[6]"  0;
	setAttr -s 7 ".kox[6]"  1;
	setAttr -s 7 ".koy[6]"  0;
createNode animCurveTA -n "animCurveTA374";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 45 0;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr -s 2 ".kox[1]"  1;
	setAttr -s 2 ".koy[1]"  0;
createNode animCurveTA -n "animCurveTA375";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 45 0;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr -s 2 ".kox[1]"  1;
	setAttr -s 2 ".koy[1]"  0;
createNode animCurveTA -n "animCurveTA376";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 45 0;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr -s 2 ".kox[1]"  1;
	setAttr -s 2 ".koy[1]"  0;
createNode animCurveTA -n "animCurveTA389";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA390";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 19 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTA -n "animCurveTA391";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 7.2644697342894906 4 7.2644697342894906 
		10 7.2644697342894906 19 7.2644697342894906 45 7.2644697342894906;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL118";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 18 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL119";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 18 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTL -n "animCurveTL120";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0 10 0 18 0 45 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU129";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 9 1 45 1;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "animCurveTU130";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 9 1 45 1;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "animCurveTU131";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 9 1 45 1;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "animCurveTU126";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 45 1;
createNode animCurveTU -n "animCurveTU127";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 45 1;
createNode animCurveTU -n "animCurveTU128";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 45 1;
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
connectAttr "attack01aSource.cl" "clipLibrary1.sc[0]";
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
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of attack1B.ma
